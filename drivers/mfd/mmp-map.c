/*
 * Base driver for Marvell MAP
 *
 * Copyright (C) 2014 Marvell International Ltd.
 * Nenghua Cao <nhcao@marvell.com>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the main directory of this
 * archive for more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/irq.h>
#include <linux/fs.h>
#include <linux/mfd/core.h>
#include <linux/of_platform.h>
#include <linux/regmap.h>
#include <linux/mfd/mmp-map.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/mmp_dspaux.h>
#include <linux/uaccess.h>
#include "mmp_map_pram.h"

#define DRV_NAME      "mmp-map"
#define DRIVER_VERSION  "1.00"
#define DRIVER_RELEASE_DATE     "Jun.17 2013"

static int map_offset, aux_offset;
static struct map_private *audio_map_priv;
static void *regmap_aux;

#define to_clk_audio(clk) (container_of(clk, struct clk_audio, hw))

/* tdm platform data */
static struct tdm_platform_data tdm_pdata = {
	.use_4_wires = 1,
	.slot_size = 20,
	.slot_space = 1,
	.start_slot = 0,
	.fsyn_pulse_width = 20,
};

static struct mfd_cell sub_devs[] = {
	{
		.of_compatible = "marvell,mmp-map-be",
		.name = "mmp-map-be",
		.id = -1,
	},
	{
		.of_compatible = "marvell,mmp-map-be-tdm",
		.name = "mmp-map-be-tdm",
		.platform_data = &tdm_pdata,
		.pdata_size = sizeof(struct tdm_platform_data),
		.id = -1,
	},
	{
		.of_compatible = "marvell,mmp-map-codec",
		.name = "mmp-map-codec",
		.id = -1,
	},
};

static struct regmap_config mmp_map_regmap_config = {
	.name = "mmp-map",
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_register = MAP_DAC_ANA_MISC,
	.cache_type = REGCACHE_RBTREE,
};

#define MAP_FW	"/data/log/audio/firmware"
static u32 firmware_reg;

static ssize_t firmware_update_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	u32 val, i;

	if (firmware_reg != 0) {
		if (firmware_reg == 0xffff) {
			for (i = 0x2000; i <= 0x7ffc; i = i + 4) {
				val = map_raw_read(audio_map_priv, i);
				pr_info("firmware reg 0x%x, value 0x%x\n",
						i, val);
			}
			return 0;
		}
		val = map_raw_read(audio_map_priv, firmware_reg);
		pr_info("firmware reg 0x%x, value 0x%x\n", firmware_reg, val);
		return 0;
	}

	pr_info("audio firmware file is in /data/log/audio/firmware\n");
	return 0;
}

static int find_number_end(const char *buf)
{
	int i = 0;
	while (buf[0] != ' ' && buf[0] != '\n') {
		buf++;
		i++;
	}
	return i;
}

static ssize_t firmware_update_set(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	char number[20];
	struct file *p;
	int ret;
	mm_segment_t old_fs;
	char *buffer = NULL;
	char *tmp_buf = NULL;
	u32 addr, val;
	unsigned int reg;

	if (buf[0] == '0' && buf[1] == 'x') {
		memset(number, '\0', 20);
		memcpy(number, buf, find_number_end(buf));
		ret = kstrtouint((const char *)number, 16, &addr);
		firmware_reg = addr;
		if (firmware_reg == 0xffff) {
			pr_info("firmware = 0xffff\n");
		} else if (firmware_reg < 0x2000 || firmware_reg > 0x7ffc) {
			pr_info("It's not a valid reg value\n");
			firmware_reg = 0;
		}
	}

	/* echo 'f' can update the firmware */
	if (buf[0] != 'f')
		return count;

	if (audio_map_priv == NULL)
		return -EINVAL;

	/* currently our firmware file is 23k */
	buffer = kmalloc(30000, GFP_ATOMIC);
	if (buf == NULL) {
		pr_err("firmware_update: %s: malloc error\n", __func__);
		return -EINVAL;
	}

	tmp_buf = buffer;
	memset(number, '\0', 20);
	memset(buffer, '\0', 30000);

	p = filp_open(MAP_FW, O_RDWR | O_CREAT
				| O_LARGEFILE | O_APPEND, 0777);

	if (IS_ERR(p)) {
		pr_err("firmware file open failed\n");
		return -EINVAL;
	}

	old_fs = get_fs();
	set_fs(get_ds());
	p->f_op->llseek(p, 0, 0);
	ret = p->f_op->read(p, buffer, 30000, &p->f_pos);
	set_fs(old_fs);

	/* Load MAP DSP firmware */
	reg = MAP_TOP_CTRL_REG_2;
	val = map_raw_read(audio_map_priv, reg);
	val &= ~(1 << 6); /* choose apb pclk */
	map_raw_write(audio_map_priv, reg, val);

	while (tmp_buf - buffer < p->f_pos) {
		memset(number, '\0', 20);
		memcpy(number, tmp_buf, find_number_end(tmp_buf));
		ret = kstrtouint((const char *)number, 16, &addr);
		if (ret < 0)
			return ret;

		tmp_buf += find_number_end(tmp_buf) + 1;
		while (tmp_buf[0] == ' ' || tmp_buf[0] == '0')
			tmp_buf++;

		memset(number, '\0', 20);
		memcpy(number, tmp_buf, find_number_end(tmp_buf));
		ret = kstrtouint((const char *)number, 16, &val);
		if (ret < 0)
			return ret;


		tmp_buf += find_number_end(tmp_buf) + 1;
		while (tmp_buf[0] == ' ' || tmp_buf[0] == '0')
			tmp_buf++;

		map_raw_write(audio_map_priv, addr, val);
	}

	audio_map_priv->dsp1_sw_id =
		map_raw_read(audio_map_priv, MAP_DSP1_FW_LOCATE);
	audio_map_priv->dsp2_sw_id =
		map_raw_read(audio_map_priv, MAP_DSP2_FW_LOCATE);
	audio_map_priv->dsp1a_sw_id =
		map_raw_read(audio_map_priv, MAP_DSP1A_FW_LOCATE);

	val |= (1 << 6); /* choose dig_clk */
	map_raw_write(audio_map_priv, reg, val);

	filp_close(p, NULL);
	kfree(buffer);

	pr_info("audio firmware updated success\n");

	return count;
}

static DEVICE_ATTR(firmware_update, 0644,
	firmware_update_show, firmware_update_set);

static void create_update_firmware_file(struct platform_device *pdev)
{
	int ret;

	/* add firmware_update sysfs entries */
	ret = device_create_file(&pdev->dev,
		&dev_attr_firmware_update);
	if (ret < 0) {
		dev_err(&pdev->dev,
			"%s: failed to add firmware_update sysfs files: %d\n",
			__func__, ret);
		return;
	}
}


static int map_32k_apll_enable(struct map_private *map_priv)
{
	void __iomem *reg_addr, *dspaux_base;
	u32 refdiv, post_div, vco_div, fbdec_div, fbdec_int, vco_en, div_en;
	u32 ICP, ICP_DLL, CTUNE, TEST_MON, KVCO, FD_SEL, VDDL;
	u32 val, time_out = 2000;
	unsigned long fvco;
	u32 srate = 48000;

	dspaux_base = map_priv->regs_aux;
	if (dspaux_base == NULL) {
		pr_err("wrong audio aux base\n");
		return -EINVAL;
	}

	/* power on audio island */
	map_priv->poweron(map_priv->apmu_base, map_priv->puclk, 1);
	/* below value are fixed */
	KVCO = 1;
	ICP = 2;
	FD_SEL = 1;
	CTUNE = 1;
	ICP_DLL = 1;
	VDDL = 1;
	TEST_MON = 0;
	/* 32K crysto input */
	refdiv = 1;
	vco_en = 1;
	div_en = 1;

	if ((srate % 8000) == 0) {
		/* 8k famliy */
		fbdec_div = 0;
		fbdec_int = 0xb4;
		/* over-sample rate = 192 */
		post_div = 0x18;
		vco_div = 4;
		fvco = 589824000 / vco_div;
	} else if ((srate % 11025) == 0) {
		/* 8k famliy */
		fbdec_div = 6;
		fbdec_int = 0xa5;
		/* over-sample rate = 192 */
		post_div = 0x18;
		vco_div = 4;
		fvco = 541900800 / vco_div;
	} else {
		pr_err("error: no pll setting for such clock!\n");
		return -EINVAL;
	}

	/*
	 * 1: Assert reset for the APLL and PU: apll1_config1
	 */
	reg_addr = dspaux_base + DSP_AUDIO_PLL1_CONF_1;
	val = readl(reg_addr);
	/* set power up, and also set reset */
	val |= 3;
	writel(val, reg_addr);
	val = readl(reg_addr);
	dev_dbg(map_priv->dev, "reset apll1: DSP_AUDIO_PLL1_CONF_1[0x%x] = 0x%x\n",
		DSP_AUDIO_PLL1_CONF_1, val);

	/*
	 * 2: set ICP, REV_DIV, FBDIV_INT, FBDIV_DEC, ICP_PLL, KVCO
	 */
	reg_addr = dspaux_base + DSP_AUDIO_PLL1_CONF_1;
	val = readl(reg_addr);
	/* clear bits: [31-2] */
	val &= 3;
	val |=
	    ((KVCO << 31) | (ICP << 27) | (fbdec_div << 23) | (fbdec_int << 15)
	     | (refdiv << 6) | (FD_SEL << 4) | (CTUNE << 2));
	writel(val, reg_addr);
	val = readl(reg_addr);
	dev_dbg(map_priv->dev, "conf F_VCO: DSP_AUDIO_PLL1_CONF_1[0x%x] = 0x%x\n",
		DSP_AUDIO_PLL1_CONF_1, val);

	/*
	 * 3: Set the required POSTDIV_AUDIO value
	 * POSTDIV_AUDIO = 0x93(147) for 48KHz, over-sample rate 64
	 */
	/* 3.1: config apll1 fast clock: VCO_DIV = 1 */
	reg_addr = dspaux_base + DSP_AUDIO_PLL1_CONF_4;
	val = readl(reg_addr);
	val &= ~(0xfff);
	val |= vco_div;
	writel(val, reg_addr);
	val = readl(reg_addr);

	dev_dbg(map_priv->dev, "conf fast clk POSTDIV: DSP_AUDIO_PLL1_CONF_4[0x%x] = 0x%x\n",
		DSP_AUDIO_PLL1_CONF_4, val);

	/* 3.2: config apll1 slow clock */
	reg_addr = dspaux_base + DSP_AUDIO_PLL1_CONF_2;
	val = readl(reg_addr);
	val &= (0xf << 28);
	val |=
	    ((TEST_MON << 24) | (vco_en << 23) | (post_div << 11) |
	     (div_en << 10) | (ICP_DLL << 5) | (0x1 << 4) | VDDL);
	writel(val, reg_addr);
	val = readl(reg_addr);
	dev_dbg(map_priv->dev, "conf slow clk POSTDIV: DSP_AUDIO_PLL1_CONF_2[0x%x] = 0x%x\n",
		DSP_AUDIO_PLL1_CONF_2, val);
	/*
	 * 4: de-assert reset
	 */
	reg_addr = dspaux_base + DSP_AUDIO_PLL1_CONF_1;
	val = readl(reg_addr);
	/* release reset */
	val &= ~(0x1 << 1);
	writel(val, reg_addr);
	val = readl(reg_addr);
	dev_dbg(map_priv->dev, "de-assert apll1: DSP_AUDIO_PLL1_CONF_1[0x%x] = 0x%x\n",
		DSP_AUDIO_PLL1_CONF_1, val);

	/*
	 * 5: check DLL lock status
	 */
	reg_addr = dspaux_base + DSP_AUDIO_PLL1_CONF_2;
	val = readl(reg_addr);
	while ((!(val & (0x1 << 28))) && time_out) {
		udelay(10);
		val = readl(reg_addr);
		time_out--;
	}
	if (time_out == 0) {
		pr_err("32K-PLL: DLL lock fail!\n");
		return -EBUSY;
	}

	dev_dbg(map_priv->dev, "apll1 DLL locked: DSP_AUDIO_PLL1_CONF_2[0x%x] = 0x%x\n",
		DSP_AUDIO_PLL1_CONF_2, val);
	/*
	 * 6: check PLL lock status
	 */
	time_out = 2000;
	while ((!(val & (0x1 << 29))) && time_out) {
		udelay(10);
		val = readl(reg_addr);
		time_out--;
	}

	if (time_out == 0) {
		pr_err("32K-PLL: PLL lock fail!\n");
		return -EBUSY;
	}
	dev_dbg(map_priv->dev, "apll1 PLL locked: DSP_AUDIO_PLL1_CONF_2[0x%x] = 0x%x\n",
		DSP_AUDIO_PLL1_CONF_2, val);

	return 0;
}

static int map_32k_apll_disable(struct map_private *map_priv)
{
	void __iomem *reg_addr, *dspaux_base;
	u32 val;
	dspaux_base = map_priv->regs_aux;

	reg_addr = dspaux_base + DSP_AUDIO_PLL1_CONF_1;
	val = readl(reg_addr);
	/* reset & power off */
	val &= ~0x1;
	val |= (0x1 << 1);
	writel(val, reg_addr);

	/* power off audio island */
	map_priv->poweron(map_priv->apmu_base, map_priv->puclk, 0);

	return 0;
}

static int map_26m_apll_enable(struct map_private *map_priv)
{
	void __iomem *reg_addr, *dspaux_base;
	u32 refdiv, post_div, vco_div, fbdiv, freq_off;
	u32 vco_en, vco_div_en, post_div_en, val;
	u32 ICP, CTUNE, TEST_MON, FD_SEL, CLK_DET_EN, INTPI, PI_EN;
	u32 time_out = 2000;
	u32 srate = 48000;
	unsigned long fvco;
	struct clk *clk;

	dspaux_base = map_priv->regs_aux;
	if (dspaux_base == NULL) {
		pr_err("wrong audio aux base\n");
		return -EINVAL;
	}

	/* power on audio island */
	map_priv->poweron(map_priv->apmu_base, map_priv->puclk, 1);
	/* below value are fixed */
	ICP = 6;
	FD_SEL = 1;
	CTUNE = 1;
	TEST_MON = 0;
	INTPI = 2;
	CLK_DET_EN = 1;
	PI_EN = 1;
	/* 26M clock input */
	refdiv = 6;
	vco_en = 1;
	vco_div_en = 1;
	post_div_en = 1;

	if ((srate % 8000) == 0) {
		/* 8k famliy */
		fbdiv = 34;
		freq_off = 0x1b5;
		/* over-sample rate = 192 */
		post_div = 0x6;
		vco_div = 1;
		fvco = 589824000 / vco_div;
	} else if ((srate % 11025) == 0) {
		/* 8k famliy */
		fbdiv = 31;
		freq_off = 0x1169;
		/* over-sample rate = 192 */
		post_div = 0x6;
		vco_div = 1;
		fvco = 541900800 / vco_div;
	} else {
		dev_dbg(map_priv->dev, "error: no pll setting for such clock!\n");
		return -EINVAL;
	}

	/*
	 * 1: power up and reset pll
	 */
	reg_addr = dspaux_base + DSP_AUDIO_PLL2_CONF_1;
	val = readl(reg_addr);
	/* set power up, and also set reset */
	val |= 3;
	writel(val, reg_addr);
	val = readl(reg_addr);
	dev_dbg(map_priv->dev, "reset apll1: DSP_AUDIO_PLL2_CONF_1[0x%x] = 0x%x\n",
		DSP_AUDIO_PLL2_CONF_1, val);

	/*
	 * 2: set ICP, REV_DIV, FBDIV_IN, FBDIV_DEC, ICP_PLL, KVCO
	 */
	reg_addr = dspaux_base + DSP_AUDIO_PLL2_CONF_1;
	val = readl(reg_addr);
	val &= 3;
	val |=
	    ((ICP << 27) | (fbdiv << 18) | (refdiv << 9) | (CLK_DET_EN << 8) |
	     (INTPI << 6) | (FD_SEL << 4) | (CTUNE << 2));
	writel(val, reg_addr);
	val = readl(reg_addr);
	dev_dbg(map_priv->dev, "reset apll1: DSP_AUDIO_PLL2_CONF_1[0x%x] = 0x%x\n",
		DSP_AUDIO_PLL2_CONF_1, val);

	/*
	 * 3: enable clk_vco
	 */
	reg_addr = dspaux_base + DSP_AUDIO_PLL2_CONF_3;
	val = readl(reg_addr);
	val &= ~(0x7ff << 14);
	val |=
	    ((vco_div_en << 24) | (vco_div << 15) | (vco_en << 14) |
	     (TEST_MON << 0));
	writel(val, reg_addr);
	val = readl(reg_addr);
	dev_dbg(map_priv->dev, "reset apll1: DSP_AUDIO_PLL2_CONF_3[0x%x] = 0x%x\n",
		DSP_AUDIO_PLL2_CONF_3, val);

	/*
	 * 4: enable clk_audio
	 */
	reg_addr = dspaux_base + DSP_AUDIO_PLL2_CONF_2;
	val = readl(reg_addr);
	val &= ~((0x7fffff << 4) | 0xf);
	val |=
	    ((post_div << 20) | (freq_off << 4) | (post_div_en << 0x1) |
	     (PI_EN << 0));
	writel(val, reg_addr);
	val = readl(reg_addr);
	dev_dbg(map_priv->dev, "reset apll2: DSP_AUDIO_PLL2_CONF_2[0x%x] = 0x%x\n",
		DSP_AUDIO_PLL2_CONF_2, val);

	/*
	 * 5: de-assert reset
	 */
	reg_addr = dspaux_base + DSP_AUDIO_PLL2_CONF_1;
	val = readl(reg_addr);
	/* release reset */
	val &= ~(0x1 << 1);
	writel(val, reg_addr);
	val = readl(reg_addr);
	dev_dbg(map_priv->dev, "de-assert apll2: DSP_AUDIO_PLL2_CONF_1[0x%x] = 0x%x\n",
		DSP_AUDIO_PLL2_CONF_1, val);

	/*
	 * 6: apply freq_offset_valid: wait 50us according to DE
	 */
	udelay(50);
	reg_addr = dspaux_base + DSP_AUDIO_PLL2_CONF_2;
	val = readl(reg_addr);
	val |= (1 << 2);
	writel(val, reg_addr);
	val = readl(reg_addr);
	dev_dbg(map_priv->dev, "apply freq_offset_valid: DSP_AUDIO_PLL2_CONF_2[0x%x] = 0x%x\n",
		DSP_AUDIO_PLL2_CONF_2, val);

	/*
	 * 7: check PLL lock status
	 */
	reg_addr = dspaux_base + DSP_AUDIO_PLL2_CONF_1;
	val = readl(reg_addr);
	while (!(val & (0x1 << 31)) && time_out) {
		udelay(10);
		val = readl(reg_addr);
		time_out--;
	}
	if (time_out == 0) {
		pr_err("26M-PLL: PLL lock fail!\n");
		return -EBUSY;
	}

	dev_dbg(map_priv->dev, "apll2 locked: DSP_AUDIO_PLL2_CONF_1[0x%x] = 0x%x\n",
		DSP_AUDIO_PLL2_CONF_1, val);

	clk = clk_get(NULL, "apll2_fast");
	if (IS_ERR(clk)) {
		pr_err("apll2_fast may not be ready\n");
		return 0;
	} else {
		/*
		 * clock framework may remember the old value and not really
		 * write register. forcely change it to ensure actual write
		 */
		clk_set_rate(clk, fvco);
		clk_set_rate(clk, fvco / 4);
	}

	return 0;
}

static int map_26m_apll_disable(struct map_private *map_priv)
{
	void __iomem *reg_addr, *dspaux_base;
	u32 val;

	dspaux_base = map_priv->regs_aux;
	if (dspaux_base == NULL) {
		pr_err("wrong audio aux base\n");
		return -EINVAL;
	}

	reg_addr = dspaux_base + DSP_AUDIO_PLL2_CONF_1;
	val = readl(reg_addr);
	/* reset & power off */
	val &= ~0x1;
	val |= (0x1 << 1);
	writel(val, reg_addr);

	/* power off audio island */
	map_priv->poweron(map_priv->apmu_base, map_priv->puclk, 0);

	dev_dbg(map_priv->dev, "pll disabled\n");

	return 0;
}

/* set port frame clock frequence */
void map_set_port_freq(struct map_private *map_priv, enum mmp_map_port port,
						unsigned int rate)
{
	unsigned int val = 0, reg, value;
	unsigned int mask = 0;

	/* sample rate */
	switch (rate) {
	case 8000:
		val = MAP_SAMPLE_RATE_8000;
		break;
	case 11025:
		val = MAP_SAMPLE_RATE_11025;
		break;
	case 16000:
		val = MAP_SAMPLE_RATE_16000;
		break;
	case 22050:
		val = MAP_SAMPLE_RATE_22050;
		break;
	case 32000:
		val = MAP_SAMPLE_RATE_32000;
		break;
	case 44100:
		val = MAP_SAMPLE_RATE_44100;
		break;
	case 48000:
		val = MAP_SAMPLE_RATE_48000;
		break;
	default:
		return;
	}

	reg = MAP_LRCLK_RATE_REG;
	value = map_raw_read(map_priv, reg);
	mask = 0xf << ((I2S_OUT - port) * 0x4);
	value &= (~mask);
	value |= (val << ((I2S_OUT - port) * 0x4));
	map_raw_write(map_priv, reg, value);
	return;
}
EXPORT_SYMBOL(map_set_port_freq);

void map_reset_port(struct map_private *map_priv, enum mmp_map_port port)
{
	unsigned int reg, val = 0;

	switch (port) {
	case I2S1:
		/* reset i2s1 interface(audio) */
		reg = MAP_TOP_CTRL_REG_1;
		val = map_raw_read(map_priv, reg);
		val |= (I2S1_RESET | ASRC1_RESET);
		map_raw_write(map_priv, reg, val);

		/* out of reset */
		val &= ~(I2S1_RESET | ASRC1_RESET);
		map_raw_write(map_priv, reg, val);
		break;
	case I2S2:
		/* reset i2s2 interface(audio) */
		reg = MAP_TOP_CTRL_REG_1;
		val = map_raw_read(map_priv, reg);
		val |= (I2S2_RESET | ASRC2_RESET);
		map_raw_write(map_priv, reg, val);

		/* out of reset */
		val &= ~(I2S2_RESET | ASRC2_RESET);
		map_raw_write(map_priv, reg, val);
		break;
	case I2S3:
		/* reset i2s3 interface(audio) */
		reg = MAP_TOP_CTRL_REG_1;
		val = map_raw_read(map_priv, reg);
		val |= (I2S3_RESET | ASRC3_RESET);
		map_raw_write(map_priv, reg, val);

		/* out of reset */
		val &= ~(I2S3_RESET | ASRC3_RESET);
		map_raw_write(map_priv, reg, val);
		break;
	case I2S4:
		/* reset i2s4 interface (hifi) */
		reg = MAP_TOP_CTRL_REG_1;
		val = map_raw_read(map_priv, reg);
		val |= (I2S4_RESET | ASRC4_RESET);
		map_raw_write(map_priv, reg, val);

		/* out of reset */
		val &= ~(I2S4_RESET | ASRC4_RESET);
		map_raw_write(map_priv, reg, val);
		break;
	case I2S_OUT:
		/* reset dei2s interface */
		reg = MAP_TOP_CTRL_REG_1;
		val = map_raw_read(map_priv, reg);
		val |= I2S_OUT_RESET;
		map_raw_write(map_priv, reg, val);

		/* out of reset */
		val &= ~I2S_OUT_RESET;
		map_raw_write(map_priv, reg, val);
		break;
	default:
		return;
	}

	return;
}
EXPORT_SYMBOL(map_reset_port);

/* apply the change */
void map_apply_change(struct map_private *map_priv)
{
	unsigned int val, reg;

	reg = MAP_DAC_ANA_MISC;
	val = APPLY_CHANGES;
	map_raw_write(map_priv, reg, val);
	return;
}
EXPORT_SYMBOL(map_apply_change);

int map_raw_write(struct map_private *map_priv, unsigned int reg,
					unsigned int value)
{
	writel(value, map_priv->regs_map + reg);
	return 0;
}
EXPORT_SYMBOL(map_raw_write);

int map_raw_bulk_write(struct map_private *map_priv, unsigned int reg,
				void *val, int val_count)
{
	unsigned int ival, i;

	for (i = 0; i < val_count; i++) {
		ival = *(u32 *)(val + (i * 32));
		writel(ival, map_priv->regs_map + reg);
	}
	return 0;
}
EXPORT_SYMBOL(map_raw_bulk_write);

unsigned int map_raw_read(struct map_private *map_priv,
					unsigned int reg)
{
	unsigned int value;

	value = readl(map_priv->regs_map + reg);
	return value;
}
EXPORT_SYMBOL(map_raw_read);

unsigned int map_raw_bulk_read(struct map_private *map_priv,
		unsigned int reg, void *val, int val_count)
{
	unsigned int i;

	for (i = 0; i < val_count; i++) {
		*(u32 *)(val + (i * 32))
			= readl(map_priv->regs_map + reg + (i * 4));
	}
	return 0;
}
EXPORT_SYMBOL(map_raw_bulk_read);

/*
 * Fixme: heat on pxa1928 A0 and helan2 Z1: if want to use dsp1a,
 * the dsp1 must be enabled first
 */
DEFINE_SPINLOCK(dsp1_en_lock);
DEFINE_SPINLOCK(dsp2_en_lock);
DEFINE_SPINLOCK(dsp1a_en_lock);

static void mmp_map_dsp_mute(struct map_private *map_priv, int port,
				int mute, int do_enable, int do_mute)
{
	unsigned int enable_reg, mute_reg, val, mask;
	unsigned int reg;
	bool mono_en = false;

	if (port == 1) {
		enable_reg = MAP_DSP1_DAC_CTRL_REG;
		mute_reg = MAP_DSP1_DAC_PROCESSING_REG;
		/* reset dsp1 */
		if ((mute == 0) && do_enable) {
			reg = MAP_TOP_CTRL_REG_1;
			val = map_raw_read(map_priv, reg);
			val |= (1 << 8);
			map_raw_write(map_priv, reg, val);

			mask = 1 << 8;
			val &= (~mask);
			map_raw_write(map_priv, reg, val);

			if (map_priv->dsp1_mono_en)
				mono_en = true;
		}
	} else if (port == 2) {
		enable_reg = MAP_DSP2_DAC_CTRL_REG;
		mute_reg = MAP_DSP2_DAC_PROCESSING_REG;
		/* reset dsp1 */
		if ((mute == 0) && do_enable) {
			reg = MAP_TOP_CTRL_REG_1;
			val = map_raw_read(map_priv, reg);
			val |= (1 << 9);
			map_raw_write(map_priv, reg, val);

			mask = 1 << 9;
			val &= (~mask);
			map_raw_write(map_priv, reg, val);

			if (map_priv->dsp2_mono_en)
				mono_en = true;
		}
	} else if (port == 3) {
		enable_reg = MAP_ADC_CTRL_REG;
		mute_reg = MAP_ADC_PROCESSING_REG;
		/* reset dsp1 */
		if ((mute == 0) && do_enable) {
			reg = MAP_TOP_CTRL_REG_1;
			val = map_raw_read(map_priv, reg);
			val |= (1 << 10);
			map_raw_write(map_priv, reg, val);

			mask = 1 << 10;
			val &= (~mask);
			map_raw_write(map_priv, reg, val);

			if (map_priv->dsp1a_mono_en)
				mono_en = true;
		}
	} else
		return;

	if (mute) {
		/* mute dsp */
		if (do_mute) {
			val = map_raw_read(map_priv, mute_reg);
			mask = 0x20;
			val &= (~mask);
			map_raw_write(map_priv, mute_reg, val);

			/*
			 * Fixme: Per DE's suggestion, add two sample delay here
			 * to make sure unmute is done.
			 */
			udelay(42);

		}

		/* disable dsp */
		if (do_enable) {
			val = map_raw_read(map_priv, enable_reg);
			if (!map_priv->b0_fix)
				mask = 0x13;
			else
				mask = 0x3;
			val &= (~mask);
			map_raw_write(map_priv, enable_reg, val);
		}
	} else {
		/* enable dsp */
		if (do_enable) {
			val = map_raw_read(map_priv, enable_reg);
			if (mono_en && !map_priv->b0_fix)
				val |= 0x10;
			if (!map_priv->b0_fix)
				mask = 0x13;
			else
				mask = 0x3;
			val &= (~mask);
			val |= 0x3;
			map_raw_write(map_priv, enable_reg, val);
		}

		/* unmute dsp */
		if (do_mute) {
			val = map_raw_read(map_priv, mute_reg);
			val |= 0x20;
			map_raw_write(map_priv, mute_reg, val);
		}
	}
}

static int mmp_map_add_port(enum mmp_map_be_port *dsp_user_port,
				enum mmp_map_be_port port)
{
	int i = 0, j = 0;
	bool found_location = false;

	for (i = 0; i < AUX; i++) {
		if ((dsp_user_port[i] == NO_BE_CONN) && !found_location) {
			j = i;
			found_location = true;
		}

		/* this port has been recorded */
		if (dsp_user_port[i] == port)
			return 0;
	}
	dsp_user_port[j] = port;

	return 0;
}

static int mmp_map_remove_port(enum mmp_map_be_port *dsp_user_port,
				enum mmp_map_be_port port)
{
	int i = 0, j = 0;

	for (i = 0; i < AUX; i++) {
		if (dsp_user_port[i] == port) {
			j = i;
			break;
		}
	}
	/* re-arrange the array */
	for (i = j; i < (AUX - 1); i++)
		dsp_user_port[i] = dsp_user_port[i + 1];
	dsp_user_port[AUX - 1] = NO_BE_CONN;

	return 0;
}

static int mmp_map_dsp_user_count(enum mmp_map_be_port *dsp_user_port)
{
	int i = 0;

	for (i = 0; i < AUX; i++) {
		if (dsp_user_port[i] == NO_BE_CONN)
			break;
	}
	return i;
}

void mmp_map_dsp1_mute(struct map_private *map_priv, int mute,
				enum mmp_map_be_port port)
{
	spin_lock(&dsp1_en_lock);
	if (mute)
		mmp_map_remove_port(map_priv->dsp1_user_port, port);
	else
		mmp_map_add_port(map_priv->dsp1_user_port, port);

	if (mute && !map_priv->dsp1_mute &&
			!mmp_map_dsp_user_count(map_priv->dsp1_user_port)) {
		/* mute dsp */
		mmp_map_dsp_mute(map_priv, 1, mute, 0, 1);
		if (map_priv->dsp1_en_cnt == 1)
			mmp_map_dsp_mute(map_priv, 1, mute, 1, 0);
		map_priv->dsp1_en_cnt--;
		map_priv->dsp1_mute = true;
	} else if (!mute && map_priv->dsp1_mute) {
		if (map_priv->dsp1_en_cnt == 0)
			mmp_map_dsp_mute(map_priv, 1, mute, 1, 0);
		mmp_map_dsp_mute(map_priv, 1, mute, 0, 1);
		map_priv->dsp1_en_cnt++;
		map_priv->dsp1_mute = false;
	}
	spin_unlock(&dsp1_en_lock);
}
EXPORT_SYMBOL(mmp_map_dsp1_mute);

void mmp_map_dsp2_mute(struct map_private *map_priv, int mute,
				enum mmp_map_be_port port)
{
	spin_lock(&dsp2_en_lock);
	if (mute)
		mmp_map_remove_port(map_priv->dsp2_user_port, port);
	else
		mmp_map_add_port(map_priv->dsp2_user_port, port);

	if (mute && !map_priv->dsp2_mute &&
			!mmp_map_dsp_user_count(map_priv->dsp2_user_port)) {
		/* mute dsp */
		mmp_map_dsp_mute(map_priv, 2, mute, 1, 1);
		map_priv->dsp2_mute = true;
	} else if (!mute && map_priv->dsp2_mute) {
		mmp_map_dsp_mute(map_priv, 2, mute, 1, 1);
		map_priv->dsp2_mute = false;
	}
	spin_unlock(&dsp2_en_lock);
}
EXPORT_SYMBOL(mmp_map_dsp2_mute);

void mmp_map_dsp1a_mute(struct map_private *map_priv, int mute,
				enum mmp_map_be_port port)
{
	spin_lock(&dsp1a_en_lock);
	if (mute)
		mmp_map_remove_port(map_priv->dsp1a_user_port, port);
	else
		mmp_map_add_port(map_priv->dsp1a_user_port, port);
	spin_unlock(&dsp1a_en_lock);

	if (mute && !map_priv->dsp1a_mute &&
			!mmp_map_dsp_user_count(map_priv->dsp1a_user_port)) {
		/* mute dsp */
		spin_lock(&dsp1a_en_lock);
		mmp_map_dsp_mute(map_priv, 3, mute, 1, 1);
		map_priv->dsp1a_mute = true;
		spin_unlock(&dsp1a_en_lock);

		/* will finally remove below WA */
		if (!map_priv->b0_fix) {
			/* disable dsp1 */
			spin_lock(&dsp1_en_lock);
			if (map_priv->dsp1_en_cnt == 1)
				mmp_map_dsp_mute(map_priv, 1, mute, 1, 0);
			map_priv->dsp1_en_cnt--;
			spin_unlock(&dsp1_en_lock);
		}
	} else if (!mute && map_priv->dsp1a_mute) {
		if (!map_priv->b0_fix) {
			spin_lock(&dsp1_en_lock);
			if (map_priv->dsp1_en_cnt == 0)
				mmp_map_dsp_mute(map_priv, 1, mute, 1, 0);
			map_priv->dsp1_en_cnt++;
			spin_unlock(&dsp1_en_lock);
		}

		spin_lock(&dsp1a_en_lock);
		mmp_map_dsp_mute(map_priv, 3, mute, 1, 1);
		map_priv->dsp1a_mute = false;
		spin_unlock(&dsp1a_en_lock);
	}
}
EXPORT_SYMBOL(mmp_map_dsp1a_mute);

/*
 * save dsp aux register and disable peripheral clock
 */
static int map_save_aux_reg(struct map_private *map_priv)
{
	u32 val, bit_sram, bit_apb;
	void __iomem *reg_addr, *regs_aux, *regs_apmu;

	regs_aux = map_priv->regs_aux;
	regs_apmu = map_priv->regs_apmu;
	bit_sram = map_priv->bit_sram;
	bit_apb = map_priv->bit_apb;

	/* save dsp aux register */
	reg_addr = regs_aux + DSP_AUDIO_ADMA_CLK;
	val = readl(reg_addr);
	map_priv->adma = val;

	reg_addr = regs_aux + DSP_AUDIO_SSPA1_CLK;
	val = readl(reg_addr);
	map_priv->sspa1 = val;

	reg_addr = regs_aux + DSP_AUDIO_SSPA2_CLK;
	val = readl(reg_addr);
	map_priv->sspa2 = val;

	reg_addr = regs_aux + DSP_AUDIO_WAKEUP_MASK;
	val = readl(reg_addr);
	map_priv->wakeup = val;

	reg_addr = regs_aux + DSP_AUDIO_MAP_CONF;
	val = readl(reg_addr);
	map_priv->conf = val;

	/* save dsp aux register */
	reg_addr = regs_aux + DSP_AUDIO_SRAM_CLK;
	val = readl(reg_addr);
	map_priv->sram = val;

	reg_addr = regs_aux + DSP_AUDIO_APB_CLK;
	val = readl(reg_addr);
	map_priv->apb = val;

	/* switch map_apb & sram clock source to vctcxo */
	reg_addr = regs_apmu;
	val = readl(reg_addr);
	val |= ((1 << bit_sram) | (1 << bit_apb));
	writel(val, reg_addr);

	reg_addr = regs_aux + DSP_AUDIO_SRAM_CLK;
	val = readl(reg_addr);
	val &= ~0xf;
	writel(val, reg_addr);

	reg_addr = regs_aux + DSP_AUDIO_APB_CLK;
	val = readl(reg_addr);
	val &= ~0x3;
	writel(val, reg_addr);

	return 0;
}

static int map_restore_aux_reg(struct map_private *map_priv)
{
	u32 val = 0, bit_sram, bit_apb;
	void __iomem *reg_addr, *regs_aux, *regs_apmu;

	regs_aux = map_priv->regs_aux;
	regs_apmu = map_priv->regs_apmu;
	bit_sram = map_priv->bit_sram;
	bit_apb = map_priv->bit_apb;

	/* restore dsp aux registers */
	reg_addr = regs_aux + DSP_AUDIO_ADMA_CLK;
	val = map_priv->adma;
	writel(val, reg_addr);

	reg_addr = regs_aux + DSP_AUDIO_SSPA1_CLK;
	val = map_priv->sspa1;
	writel(val, reg_addr);

	reg_addr = regs_aux + DSP_AUDIO_SSPA2_CLK;
	val = map_priv->sspa2;
	writel(val, reg_addr);

	reg_addr = regs_aux + DSP_AUDIO_WAKEUP_MASK;
	val = map_priv->wakeup;
	writel(val, reg_addr);

	reg_addr = regs_aux + DSP_AUDIO_MAP_CONF;
	val = map_priv->conf;
	writel(val, reg_addr);

	/* restore dsp aux registers */
	reg_addr = regs_aux + DSP_AUDIO_SRAM_CLK;
	val = map_priv->sram;
	writel(val, reg_addr);
	val = readl(reg_addr);
	while (!(val & 0x6))
		val = readl(reg_addr);

	reg_addr = regs_aux + DSP_AUDIO_APB_CLK;
	val = map_priv->apb;
	writel(val, reg_addr);
	val = readl(reg_addr);
	while (!(val & 0x3))
		val = readl(reg_addr);

	/* switch map_apb & sram clock source to apll */
	if (map_priv->apll == APLL_32K) {
		reg_addr = regs_apmu;
		val = readl(reg_addr);
		val &= ~((1 << bit_sram) | (1 << bit_apb));
		writel(val, reg_addr);
	}

	return 0;
}

static int map_aux_clk_init(struct map_private *map_priv)
{
	struct clk *clk1, *clk2, *clk3, *fclk, *sclk, *fclks;
	void *regs_aux = map_priv->regs_aux;
	void __iomem *reg_addr;
	u32 fclk_rate, sclk_rate, val;

	/*
	 * configure MAP wake up source
	 * only allow ADMA interrupt will wake up system from low power.
	 * disable sspa1/2, map interrupt wake up.
	 * ADMA: bit 31~28
	 * SSPA: bit 15~14
	 * MAP: bit 13
	 */
	reg_addr = regs_aux + DSP_AUDIO_WAKEUP_MASK;
	val = readl(reg_addr);
	val &= ~(0xf << 28);
	val |= (0x7 << 13);
	writel(val, reg_addr);

	/* get apll1(2) fast clock */
	if (map_priv->apll == APLL_32K)
		fclk = clk_get(NULL, "apll1_fast");
	else
		fclk = clk_get(NULL, "apll2_fast");
	if (IS_ERR(fclk)) {
		pr_err("get apll1(2)_fast failed\n");
		return -EINVAL;
	}
	/* set to apll1_rate first to forcely change default value */
	fclk_rate = clk_get_rate(fclk);
	clk_prepare_enable(fclk);

	/* get apll1(2) slow clock */
	if (map_priv->apll == APLL_32K)
		sclk = clk_get(NULL, "apll1_slow");
	else
		sclk = clk_get(NULL, "apll2_slow");
	if (IS_ERR(sclk)) {
		pr_err("get apll1(2)_slow failed\n");
		return -EINVAL;
	}
	sclk_rate = clk_get_rate(sclk);
	clk_prepare_enable(sclk);

	/* map_apll_fast: choose apll1_fast */
	fclks = clk_get(NULL, "map_apll_fast");
	if (IS_ERR(fclks)) {
		pr_err("get map_apll_fast failed\n");
		return -EINVAL;
	}
	clk_set_parent(fclks, fclk);

	/*
	 * fix high level clock parent
	 * including: sram, apb, adma, sspa
	 */
	/* appl1_mux: choose fast clock(not slow clock) */
	if (map_priv->apll == APLL_32K) {
		clk1 = clk_get(NULL, "apll1_mux");
		if (IS_ERR(clk1)) {
			pr_err("get apll1_mux failed\n");
			return -EINVAL;
		}
		clk_set_parent(clk1, fclk);
	} else {
		/* 26m apll has no clock to apb/sram */
		clk1 = clk_get(NULL, "vctcxo");
		if (IS_ERR(clk1)) {
			pr_err("get vctcxo failed\n");
			return -EINVAL;
		}
	}

	/* sram_mux: choose apll1_mux(not vctcxo) */
	clk2 = clk_get(NULL, "sram_mux");
	if (IS_ERR(clk2)) {
		pr_err("get sram_mux failed\n");
		return -EINVAL;
	}
	clk_set_parent(clk2, clk1);

	/* mmp-sram rate */
	clk3 = clk_get(NULL, "mmp-sram");
	if (IS_ERR(clk3)) {
		pr_err("get mmp-sram failed\n");
		return -EINVAL;
	}
	/* set clk div to 0x1 */
	clk_set_rate(clk3, clk2->rate);
	/* set fast clock as parent */
	clk_prepare_enable(clk3);

	/* map_apb_mux: choose apll1_mux(not vctcxo) */
	clk2 = clk_get(NULL, "map_apb_mux");
	if (IS_ERR(clk2)) {
		pr_err("get map_apb_mux failed\n");
		return -EINVAL;
	}
	clk_set_parent(clk2, clk1);

	/* map_apb rate */
	clk3 = clk_get(NULL, "map_apb");
	if (IS_ERR(clk3)) {
		pr_err("get map_apb failed\n");
		return -EINVAL;
	}
	/* set clk div to 0x1 */
	clk_set_rate(clk3, clk2->rate);
	/* enable apb clock for register r/w */
	clk_prepare_enable(clk3);

	/* adma_mux: choose apll1 slow clock */
	clk2 = clk_get(NULL, "adma_mux");
	if (IS_ERR(clk2)) {
		pr_err("get adma_mux failed\n");
		return -EINVAL;
	}
	clk_set_parent(clk2, sclk);

	/* adma rate */
	clk2 = clk_get(NULL, "mmp-adma");
	if (IS_ERR(clk2)) {
		pr_err("get mmp-adma failed\n");
		return -EINVAL;
	}
	clk_prepare_enable(clk2);

	/* sspa1_mux: choose apll1 slow clock */
	clk2 = clk_get(NULL, "sspa1_mux");
	if (IS_ERR(clk2)) {
		pr_err("get sspa1_mux failed\n");
		return -EINVAL;
	}
	clk_set_parent(clk2, sclk);

	clk1 = clk_get(NULL, "sspa1_bypass");
	if (IS_ERR(clk1)) {
		pr_err("get sspa1_bypass failed\n");
		return -EINVAL;
	}
	clk_set_parent(clk1, clk2);

	/* sspa1 rate */
	clk2 = clk_get(NULL, "mmp-sspa-dai.0");
	if (IS_ERR(clk2)) {
		pr_err("get mmp-sspa-dai.0 failed\n");
		return -EINVAL;
	}

	/* sspa2_mux: choose apll2 slow clock */
	clk2 = clk_get(NULL, "sspa2_mux");
	if (IS_ERR(clk2)) {
		pr_err("get sspa2_mux failed\n");
		return -EINVAL;
	}
	clk_set_parent(clk2, sclk);

	clk1 = clk_get(NULL, "sspa2_bypass");
	if (IS_ERR(clk1)) {
		pr_err("get sspa2_bypass failed\n");
		return -EINVAL;
	}
	clk_set_parent(clk1, clk2);

	/* sspa1 rate */
	clk2 = clk_get(NULL, "mmp-sspa-dai.1");
	if (IS_ERR(clk2)) {
		pr_err("get mmp-sspa-dai.1 failed\n");
		return -EINVAL;
	}

	return 0;
}

static int map_internal_clk_init(void)
{
	struct clk *clk1, *clk2, *fclks;

	fclks = clk_get(NULL, "map_apll_fast");
	if (IS_ERR(fclks)) {
		pr_err("get map_apll_fast failed\n");
		return -EINVAL;
	}

	/* map_mclk_high: choose map_apll_fast */
	clk1 = clk_get(NULL, "map_mclk_high");
	if (IS_ERR(clk1)) {
		pr_err("get map_mclk_high failed\n");
		return -EINVAL;
	}
	clk_set_parent(clk1, fclks);

	/* map_bclk: choose map_mclk_high */
	clk2 = clk_get(NULL, "map_bclk");
	if (IS_ERR(clk2)) {
		pr_err("get map_bclk failed\n");
		return -EINVAL;
	}
	clk_set_parent(clk2, clk1);

	/* map-tdm: choose map_apll_fast */
	clk2 = clk_get(NULL, "map-tdm");
	if (IS_ERR(clk2)) {
		pr_err("get map-tdm failed\n");
		return -EINVAL;
	}
	clk_set_parent(clk2, fclks);

	/* map_digit_div: choose map_apll_fast */
	clk1 = clk_get(NULL, "map_digit_div");
	if (IS_ERR(clk1)) {
		pr_err("get map_digit_div failed\n");
		return -EINVAL;
	}
	clk_set_parent(clk1, fclks);

	/* map_digit_clk: choose map_digit_div */
	clk2 = clk_get(NULL, "map_digit_clk");
	if (IS_ERR(clk2)) {
		pr_err("get map_digit_clk failed\n");
		return -EINVAL;
	}
	clk_set_parent(clk2, clk1);

	/* map_dsp_clk: choose map_digit_clk */
	clk1 = clk_get(NULL, "map_dsp_clk");
	if (IS_ERR(clk1)) {
		pr_err("get map_dsp_clk failed\n");
		return -EINVAL;
	}
	clk_set_parent(clk1, clk2);

	clk1 = clk_get(NULL, "tdm_mn_div");
	if (IS_ERR(clk1)) {
		pr_err("get tdm_mn_div failed\n");
		return -EINVAL;
	}
	clk2 = clk_get(NULL, "tdm_fclk");
	if (IS_ERR(clk2)) {
		pr_err("get tdm_fclk failed\n");
		return -EINVAL;
	}
	clk_set_parent(clk2, clk1);

	return 0;
}

void map_load_dsp_pram(struct map_private *map_priv)
{
	int i;
	u32 off;

	for (i = 0; i < ARRAY_SIZE(map_pram); i++) {
		off = map_pram[i].addr;
		map_raw_write(map_priv, off, map_pram[i].val);
	}
	map_priv->dsp1_sw_id =
		map_raw_read(map_priv, MAP_DSP1_FW_LOCATE);
	map_priv->dsp2_sw_id =
		map_raw_read(map_priv, MAP_DSP2_FW_LOCATE);
	map_priv->dsp1a_sw_id =
		map_raw_read(map_priv, MAP_DSP1A_FW_LOCATE);

}

static void map_reg_dump_all(void)
{
	unsigned int i, reg_val = 0;

	for (i = 0; i <= 0x8c; i += 4) {
		reg_val = map_raw_read(audio_map_priv, i);
		pr_info("%3x = %x\n", i, reg_val);
	}
	for (i = 0x100; i <= 0x1b4; i += 4) {
		reg_val = map_raw_read(audio_map_priv, i);
		pr_info("%3x = %x\n", i, reg_val);
	}
	for (i = 0x200; i <= 0x2b4; i += 4) {
		reg_val = map_raw_read(audio_map_priv, i);
		pr_info("%3x = %x\n", i, reg_val);
	}
	for (i = 0x300; i <= 0x35c; i += 4) {
		reg_val = map_raw_read(audio_map_priv, i);
		pr_info("%3x = %x\n", i, reg_val);
	}
	for (i = 0x400; i <= 0x40c; i += 4) {
		reg_val = map_raw_read(audio_map_priv, i);
		pr_info("%3x = %x\n", i, reg_val);
	}
}

static ssize_t map_reg_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	unsigned int reg_val = 0;
	size_t len = 0;

	if (map_offset == 0xfff) {
		map_reg_dump_all();
		len = sprintf(buf, "dump all registers\n");
		return len;
	} else if (map_offset > 0x40c) {
		pr_info("map_offset 0x%x is invalid\n", map_offset);
		return -EINVAL;
	}

	reg_val = map_raw_read(audio_map_priv, map_offset);

	len = sprintf(buf, "map_offset=0x%x, val=0x%x\n", map_offset, reg_val);

	return len;
}

static ssize_t map_reg_set(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	int reg_val, reg, val;

	char index[20], *val_str;
	memset(index, '\0', 20);

	/* write register: find whether it has blank */
	val_str = strchr(buf, 32);
	if (val_str) {
		/* set the register index */
		memcpy(index, buf, (val_str - buf));

		if (kstrtouint(index, 16, &map_offset) < 0)
			return -EINVAL;

		if (map_offset > 0x40c) {
			pr_info("map_offset 0x%x is invalid\n", map_offset);
			return -EINVAL;
		}

		memcpy(index, val_str + 1, (strlen(val_str) - 1));

		if (kstrtouint(index, 16, &reg_val) < 0)
			return -EINVAL;
		reg_val &= 0xFFFFFFFF;

		map_raw_write(audio_map_priv, map_offset, reg_val);

		pr_info("map_offset is 0x%x val 0x%x\n", map_offset, reg_val);

		/* apply changes */
		reg = MAP_DAC_ANA_MISC;
		val = map_raw_read(audio_map_priv, reg);
		val |= APPLY_CHANGES;
		map_raw_write(audio_map_priv, reg, val);
	} else {
		if (kstrtouint(buf, 16, &map_offset) < 0)
			return -EINVAL;

		if (map_offset == 0xfff) {
			map_reg_dump_all();
			return count;
		}

		if (map_offset > 0x40c) {
			pr_info("map_offset 0x%x is invalid\n", map_offset);
			return -EINVAL;
		}

		pr_info("map_offset is 0x%x\n", map_offset);
	}

	return count;
}

static void dspaux_reg_dump_all(void)
{
	unsigned int i, reg_val = 0;

	for (i = 0; i <= 0x2c; i += 4) {
		reg_val = readl(regmap_aux + i);
		pr_info("%2x = %x\n", i, reg_val);
	}
	for (i = 0x68; i <= 0x80; i += 4) {
		reg_val = readl(regmap_aux + i);
		pr_info("%2x = %x\n", i, reg_val);
	}
}

static ssize_t dspaux_reg_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	unsigned int reg_val = 0;
	size_t len = 0;

	if (aux_offset == 0xfff) {
		dspaux_reg_dump_all();
		len = sprintf(buf, "dump all registers\n");
		return len;
	} else if (aux_offset > 0x80) {
		pr_info("aux_offset 0x%x is invalid\n", map_offset);
		return -EINVAL;
	}

	reg_val = readl(regmap_aux + aux_offset);

	len = sprintf(buf, "aux_offset=0x%x, val=0x%x\n", aux_offset, reg_val);

	return len;
}

static ssize_t dspaux_reg_set(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	int reg_val;

	char index[20], *val_str;
	memset(index, '\0', 20);

	/* write register: find whether it has blank */
	val_str = strchr(buf, 32);
	if (val_str) {
		/* set the register index */
		memcpy(index, buf, (val_str - buf));

		if (kstrtouint(index, 16, &aux_offset) < 0)
			return -EINVAL;

		if (aux_offset > 0x80) {
			pr_info("aux_offset 0x%x is invalid\n", map_offset);
			return -EINVAL;
		}

		memcpy(index, val_str + 1, (strlen(val_str) - 1));

		if (kstrtouint(index, 16, &reg_val) < 0)
			return -EINVAL;
		reg_val &= 0xFFFFFFFF;

		writel(reg_val, regmap_aux + aux_offset);

		pr_info("aux_offset is 0x%x val 0x%x\n", aux_offset, reg_val);
	} else {
		if (kstrtouint(buf, 16, &aux_offset) < 0)
			return -EINVAL;

		if (aux_offset == 0xfff) {
			dspaux_reg_dump_all();
			return count;
		}

		if (aux_offset > 0x80) {
			pr_info("aux_offset 0x%x is invalid\n", aux_offset);
			return -EINVAL;
		}

		pr_info("aux_offset is 0x%x\n", aux_offset);
	}

	return count;
}

static DEVICE_ATTR(map_reg, 0644, map_reg_show, map_reg_set);
static DEVICE_ATTR(dspaux_reg, 0644, dspaux_reg_show, dspaux_reg_set);

static int map_config(struct map_private *map_priv)
{
	/*struct regmap *regmap = map_priv->regmap;*/
	unsigned int val, reg;

	/* configure pad */
	val = readl(map_priv->regs_aux + DSP_AUDIO_MAP_CONF);
	val &=  ~MAP_RESET;
	writel(val, map_priv->regs_aux + DSP_AUDIO_MAP_CONF);
	val = readl(map_priv->regs_aux + DSP_AUDIO_MAP_CONF);
	val |=  MAP_RESET;
	writel(val, map_priv->regs_aux + DSP_AUDIO_MAP_CONF);

#ifndef CONFIG_MAP_BYPASS
	val = readl(map_priv->regs_aux + DSP_AUDIO_MAP_CONF);
	val &= ~(SSPA1_PAD_OUT_SRC_MASK | SSPA2_PAD_OUT_SRC_MASK);
	val |= TDM_DRIVE_SSPA1_PAD;
	val |= I2S4_DRIVE_SSPA2_PAD;
	val &= ~AUD_SSPA1_INPUT_SRC;
	val &= ~AUD_SSPA2_INPUT_SRC;
	val |= CP_GSSP_INPUT_FROM_I2S2;
	writel(val, map_priv->regs_aux + DSP_AUDIO_MAP_CONF);
#endif

	/* Load MAP DSP firmware */
	reg = MAP_TOP_CTRL_REG_2;
	/*regmap_read(regmap, reg, &val);*/
	val = map_raw_read(map_priv, reg);
	val &= ~(1 << 6); /* choose apb pclk */
	/*regmap_write(regmap, reg, val);*/
	map_raw_write(map_priv, reg, val);
	map_load_dsp_pram(map_priv);
	val |= (1 << 6); /* choose dig_clk */
	/*regmap_write(regmap, reg, val);*/
	map_raw_write(map_priv, reg, val);
	return 0;
}

/* put map into active state*/
void map_be_active(struct map_private *map_priv)
{
	unsigned int reg, val;
	bool map_is_active = false;

	spin_lock(&map_priv->map_lock);
	if (!map_priv->user_count) {
		/* put map into active state */
		reg = MAP_TOP_CTRL_REG_1;
		val = 0x3;
		map_raw_write(map_priv, reg, val);

		/* set clock here */
		reg = MAP_TOP_CTRL_REG_2;
		val = (0x4d | (map_priv->pll_sel << 1));
		map_raw_write(map_priv, reg, val);

		reg = MAP_ASRC_CTRL_REG;
		val = 0xff;
		map_raw_write(map_priv, reg, val);

		map_is_active = true;
	}
	map_priv->user_count++;
	spin_unlock(&map_priv->map_lock);

	if (map_is_active) {
		/* get constrain out of spinlock since it may sleep */
		if (map_priv->lpm_qos >= 0)
			pm_qos_update_request(&map_priv->qos_idle, map_priv->lpm_qos);
	}

	return;
}
EXPORT_SYMBOL(map_be_active);

/* put map into reset state*/
void map_be_reset(struct map_private *map_priv)
{
	unsigned int reg, val;
	bool map_is_reset = false;

	spin_lock(&map_priv->map_lock);
	map_priv->user_count--;
	if (!map_priv->user_count) {
		/* reset map */
		reg = MAP_TOP_CTRL_REG_1;
		val = 0xfff10;
		/*regmap_write(regmap, reg, val);*/
		map_raw_write(map_priv, reg, val);

		reg = MAP_TOP_CTRL_REG_1;
		val = 0x1;
		/*regmap_write(regmap, reg, val);*/
		map_raw_write(map_priv, reg, val);

		map_is_reset = true;
	}
	spin_unlock(&map_priv->map_lock);

	if (map_is_reset) {
		/* release constaint to allow LPM if needed */
		if (map_priv->lpm_qos >= 0)
			pm_qos_update_request(&map_priv->qos_idle,
				PM_QOS_CPUIDLE_BLOCK_DEFAULT_VALUE);
	}
	return;
}
EXPORT_SYMBOL(map_be_reset);

/* check if map is used by CP(i2s2) or FM(i2s3) */
static int map_i2s2_i2s3_active(struct map_private *map_priv)
{
	unsigned int reg, val;

	reg = MAP_I2S2_CTRL_REG;
	val = map_raw_read(map_priv, reg);
	if ((val & I2S_GEN_EN) || (val & I2S_REC_EN))
		return 1;

	reg = MAP_I2S3_CTRL_REG;
	val = map_raw_read(map_priv, reg);
	if ((val & I2S_GEN_EN) || (val & I2S_REC_EN))
		return 1;

	return 0;
}

static int device_map_init(struct map_private *map_priv)
{
	int ret = 0;
	unsigned int val = 0;
	struct regmap *regmap = map_priv->regmap;

	if (!regmap) {
		dev_err(map_priv->dev, "regmap is invalid\n");
		return -EINVAL;
	}

	val = map_raw_read(map_priv, MMP_MAP_REV);
	if (val == 0) {
		dev_err(map_priv->dev, "Failed to read MAP REV: %d\n", val);
		return -EINVAL;
	}
	map_priv->id = val;

	map_aux_clk_init(map_priv);

	dev_info(map_priv->dev, "MAP config, please wait...\r\n");
	map_config(map_priv);

	map_internal_clk_init();

	dev_info(map_priv->dev, "DSP1 firmware version: 0x%x\r\n",
						map_priv->dsp1_sw_id);
	dev_info(map_priv->dev, "DSP2 firmware version: 0x%x\r\n",
						map_priv->dsp2_sw_id);
	dev_info(map_priv->dev, "DSP1A firmware version: 0x%x\r\n",
						map_priv->dsp1a_sw_id);

	ret = mfd_add_devices(map_priv->dev, 0, &sub_devs[0],
			      ARRAY_SIZE(sub_devs), 0, 0, NULL);
	if (ret < 0) {
		dev_err(map_priv->dev, "Failed to add sub_devs\n");
		return ret;
	}

	return ret;
}

#ifdef CONFIG_OF
static const struct of_device_id mmp_map_of_match[] = {
	{ .compatible = "marvell,mmp-map"},
	{},
};
#endif

static int mmp_map_parse_dt(struct platform_device *pdev,
			    struct map_private *map_priv)
{
	struct device_node *np = pdev->dev.of_node;
	u32 pmu_audio_reg, bit_sram, bit_apb, pll_sel;
	int ret = 0;

	if (!np) {
		dev_err(&pdev->dev, "could not find marvell,mmp-map node\n");
		return -ENODEV;
	}

	ret = of_property_read_u32(np, "audio_reg", &pmu_audio_reg);
	if (ret < 0) {
		dev_err(&pdev->dev, "could not get audio_reg in dt\n");
		return ret;
	}
	map_priv->audio_reg = pmu_audio_reg;

	ret = of_property_read_u32(np, "bit_sram", &bit_sram);
	if (ret < 0) {
		dev_err(&pdev->dev, "could not get bit_sram in dt\n");
		return ret;
	}
	map_priv->bit_sram = bit_sram;

	ret = of_property_read_u32(np, "bit_apb", &bit_apb);
	if (ret < 0) {
		dev_err(&pdev->dev, "could not get bit_apb in dt\n");
		return ret;
	}
	map_priv->bit_apb = bit_apb;

	ret = of_property_read_u32(np, "pll_sel", &pll_sel);
	if (ret < 0) {
		dev_err(&pdev->dev, "could not get pll_sel in dt\n");
		return ret;
	}
	map_priv->pll_sel = pll_sel;

	if (of_property_read_bool(np, "marvell,b0_fix"))
		map_priv->b0_fix = true;
	else
		map_priv->b0_fix = false;

	return ret;
}

static int mmp_map_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct map_private *map_priv;
	struct resource *res0, *res1, *region;
	struct clk *clk;
	struct clk_audio *clk_audio;
	int ret = 0;
	s32 lpm_qos;

	map_priv = devm_kzalloc(&pdev->dev,
		sizeof(struct map_private), GFP_KERNEL);
	if (map_priv == NULL)
		return -ENOMEM;

	/* MAP AUX register area */
	res0 = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res0 == NULL) {
		dev_err(map_priv->dev, "resource for %s not exist\n",
				pdev->name);
		return -ENXIO;
	}

	/* map MAP register area */
	res1 = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (res1 == NULL) {
		dev_err(map_priv->dev, "resource for %s not exist\n",
				pdev->name);
		return -ENXIO;
	}

	region = devm_request_mem_region(&pdev->dev, res0->start,
					 resource_size(res0), DRV_NAME);
	if (!region) {
		dev_err(&pdev->dev, "request region aux failed\n");
		return -EBUSY;
	}

	map_priv->regs_aux = devm_ioremap(&pdev->dev, res0->start,
				  resource_size(res0));
	if (!map_priv->regs_aux) {
		dev_err(&pdev->dev, "ioremap aux failed\n");
		return -ENOMEM;
	}

	region = devm_request_mem_region(&pdev->dev, res1->start,
					 resource_size(res1), DRV_NAME);
	if (!region) {
		dev_err(&pdev->dev, "request region map failed\n");
		return -EBUSY;
	}

	map_priv->regs_map = devm_ioremap(&pdev->dev, res1->start,
				  resource_size(res1));
	if (!map_priv->regs_map) {
		dev_err(&pdev->dev, "ioremap map failed\n");
		return -ENOMEM;
	}

	map_priv->dev = &pdev->dev;
	map_priv->regmap = devm_regmap_init_mmio(&pdev->dev, map_priv->regs_map,
					&mmp_map_regmap_config);
	if (IS_ERR(map_priv->regmap)) {
		ret = PTR_ERR(map_priv->regmap);
		dev_err(map_priv->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	ret = of_property_read_u32(np, "marvell,apll", &map_priv->apll);
	if (ret < 0) {
		dev_err(&pdev->dev, "could not get marvell,apll in dt\n");
		return ret;
	}

	map_priv->map_tdm = devm_clk_get(&pdev->dev, "map-tdm");
	if (IS_ERR(map_priv->map_tdm)) {
		ret = PTR_ERR(map_priv->map_tdm);
		return ret;
	}

	map_priv->map_bclk = devm_clk_get(&pdev->dev, "map_bclk");
	if (IS_ERR(map_priv->map_bclk)) {
		ret = PTR_ERR(map_priv->map_bclk);
		return ret;
	}

	map_priv->dsp_clk = devm_clk_get(&pdev->dev, "map_dsp_clk");
	if (IS_ERR(map_priv->dsp_clk)) {
		ret = PTR_ERR(map_priv->dsp_clk);
		return ret;
	}

	ret = mmp_map_parse_dt(pdev, map_priv);
	if (ret < 0) {
		dev_err(&pdev->dev, "parse dt fail\n");
		return ret;
	}

	if (map_priv->apll == APLL_32K)
		clk = clk_get(NULL, "map_apll1");
	else
		clk = clk_get(NULL, "map_apll2");
	if (IS_ERR(clk)) {
		pr_err("get map_apll failed\n");
		return PTR_ERR(clk);
	}
	clk_audio = to_clk_audio(clk->hw);
	map_priv->apmu_base = clk_audio->apmu_base;
	map_priv->regs_apmu = clk_audio->apmu_base + map_priv->audio_reg;
	map_priv->poweron = clk_audio->poweron;
	map_priv->puclk = clk_audio->puclk;

	map_priv->user_count = 0;
	map_priv->path_enabled = false;
	map_priv->dsp1_mute = true;
	map_priv->dsp2_mute = true;
	map_priv->dsp1a_mute = true;
	map_priv->map_i2s2_i2s3_active = false;
	spin_lock_init(&map_priv->map_lock);
	/* Fixme: do we need to bypass the cache in regmap? */
	/* regcache_cache_bypass(map_priv->regmap, true); */
	platform_set_drvdata(pdev, map_priv);

	ret = device_map_init(map_priv);
	if (ret) {
		dev_err(map_priv->dev, "%s id 0x%x failed!\n",
				__func__, map_priv->id);
	}

	ret = of_property_read_u32(np, "lpm-qos", &lpm_qos);
	if (ret == 0) {
		map_priv->lpm_qos = lpm_qos;
		map_priv->qos_idle.name = pdev->name;
		pm_qos_add_request(&map_priv->qos_idle, PM_QOS_CPUIDLE_BLOCK,
		PM_QOS_CPUIDLE_BLOCK_DEFAULT_VALUE);
	} else {
		map_priv->lpm_qos = -1;
		dev_dbg(&pdev->dev, "no lpm_qos required in dt\n");
	}

	/* add debug interface */
	audio_map_priv = map_priv;
	regmap_aux = map_priv->regs_aux;
	/* add map_reg sysfs entries */
	ret = device_create_file(&pdev->dev, &dev_attr_map_reg);
	if (ret < 0) {
		dev_err(&pdev->dev,
			"%s: failed to add map_reg sysfs files: %d\n",
			__func__, ret);
		return ret;
	}

	/* add dspaux_reg sysfs entries */
	ret = device_create_file(&pdev->dev, &dev_attr_dspaux_reg);
	if (ret < 0) {
		dev_err(&pdev->dev,
			"%s: failed to add map_reg sysfs files: %d\n",
			__func__, ret);
		return ret;
	}

	create_update_firmware_file(pdev);

	return ret;
}

static int mmp_map_remove(struct platform_device *pdev)
{
	struct map_private *map_priv;

	map_priv = platform_get_drvdata(pdev);
	if (map_priv->lpm_qos >= 0)
		pm_qos_remove_request(&map_priv->qos_idle);
	platform_set_drvdata(pdev, NULL);

	return 0;
}

/*
 * On pxa1928, the register are cleared when entering D2
 * So need to re-config them. But on pxa1U88, it use retaining mode
 * so do nothing for entering/exiting D2
 */
static int map_suspend(struct device *dev)
{
	struct map_private *map_priv = dev_get_drvdata(dev);

	if (map_i2s2_i2s3_active(map_priv)) {
		map_priv->map_i2s2_i2s3_active = true;
		return 0;
	}

	map_priv->map_i2s2_i2s3_active = false;
	map_save_aux_reg(map_priv);

	if (map_priv->apll == APLL_32K)
		map_32k_apll_disable(map_priv);
	else
		map_26m_apll_disable(map_priv);

	return 0;
}

static int map_resume(struct device *dev)
{
	struct map_private *map_priv = dev_get_drvdata(dev);

	if (map_priv->map_i2s2_i2s3_active)
		return 0;

	map_priv->map_i2s2_i2s3_active = false;
	if (map_priv->apll == APLL_32K)
		map_32k_apll_enable(map_priv);
	else
		map_26m_apll_enable(map_priv);
	map_restore_aux_reg(map_priv);
	map_config(map_priv);
	return 0;
}

static UNIVERSAL_DEV_PM_OPS(map_pm_ops, map_suspend, map_resume,
			    NULL);

static struct platform_driver mmp_map_driver = {
	.probe		= mmp_map_probe,
	.remove		= mmp_map_remove,
	.driver		= {
		.name	= DRV_NAME,
		.owner	= THIS_MODULE,
		.pm = &map_pm_ops,
#ifdef CONFIG_OF
		.of_match_table = of_match_ptr(mmp_map_of_match),
#endif
	},
};

module_platform_driver(mmp_map_driver);

MODULE_DESCRIPTION("Marvell MAP MFD driver");
MODULE_AUTHOR("Nenghua Cao <nhcao@marvell.com>");
MODULE_LICENSE("GPL");
