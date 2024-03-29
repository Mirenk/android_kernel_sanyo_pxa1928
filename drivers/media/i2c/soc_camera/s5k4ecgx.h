#ifndef __S5K4ECGX_H__
#define __S5K4ECGX_H__

#define S5K4ECGX_DRIVER_NAME	"s5k4ecgx"
#define S5K4ECGX_I2C_DEV_NAME	"s5k4ecgx"
#define S5K4ECGX_SENSOR_ID		0x4EC0

#define S5K4ECGX_OUT_WIDTH_DEF		640
#define S5K4ECGX_OUT_HEIGHT_DEF		480

typedef struct reg_value {
	u16		addr;
	u16		data;
	u32		delay;
} reg_value_t;

typedef enum {
	REG_FWverControlStr_usFWsenID			= 0x01A4,
	REG_FWverControlStr_usHWversion			= 0x01A6,
	REG_TC_UserSaturation					= 0x0234,
	REG_TC_GP_SpecialEffects				= 0x023C,
	REG_TC_GP_EnablePreview					= 0x023E,
	REG_TC_GP_EnablePreviewChanged			= 0x0240,
	REG_TC_GP_EnableCapture					= 0x0242,
	REG_TC_GP_EnableCaptureChanged			= 0x0244,
	REG_TC_GP_NewConfigSync					= 0x024E,
	REG_TC_GP_ActivePrevConfig				= 0x0266,
	REG_TC_GP_PrevConfigChanged				= 0x0268,
	REG_TC_GP_PrevOpenAfterChange			= 0x026A,
	REG_TC_GP_ActiveCapConfig				= 0x026E,
	REG_TC_GP_CapConfigChanged				= 0x0270,
	REG_TC_AF_AfCmd							= 0x028C,
	REG_TC_AF_AfCmdParam					= 0x028E,
	REG_TC_AF_FstWinStartX					= 0x0294,
	REG_TC_AF_FstWinStartY					= 0x0296,
	REG_TC_AF_FstWinSizeX					= 0x0298,
	REG_TC_AF_FstWinSizeY					= 0x029A,
	REG_TC_AF_ScndWinStartX					= 0x029C,
	REG_TC_AF_ScndWinStartY					= 0x029E,
	REG_TC_AF_ScndWinSizeX					= 0x02A0,
	REG_TC_AF_ScndWinSizeY					= 0x02A2,
	REG_TC_AF_WinSizesUpdated				= 0x02A4,
	REG_0TC_PCFG_usWidth					= 0x02A6,
	REG_0TC_PCFG_usHeight					= 0x02A8,
	REG_0TC_CCFG_usWidth					= 0x0398,
	REG_0TC_CCFG_usHeight					= 0x039A,
	REG_SF_USER_Rgain						= 0x04BA,
	REG_SF_USER_Ggain						= 0x04BE,
	REG_SF_USER_Bgain						= 0x04C2,
	REG_SF_USER_RGBGainChanged				= 0x04C6,
	REG_SF_USER_IsoType						= 0x04D0,
	REG_SF_USER_IsoVal						= 0x04D2,
	REG_SF_USER_IsoChanged					= 0x04D4,
	REG_SF_USER_FlickerQuant				= 0x04D6,
	REG_SF_USER_FlickerQuantChanged			= 0x04D8,
	REG_TC_DBG_AutoAlgEnBits				= 0x04E6,
	lt_bUseSecISODgain						= 0x06C2,
	afit_bUseNB_Afit						= 0x0938,
	_ccm_oscar_iSaturation					= 0x0A1E,
	TVAR_ae_BrAve							= 0x1484,
	oif_usMipiCapturePreviewVirtualChannel	= 0x1780,
	Mon_LT_uStableCntr						= 0x210C,
	Mon_AAIO_bAE							= 0x2C5E,
	Mon_AF_search_usStatus					= 0x2EEE,
} s5k4ecgx_register_t;

#define V4L2_CID_S5K4ECGX_CAP_MODE \
		(V4L2_CID_CAMERA_CLASS_BASE + 0x2001)

#define V4L2_CID_S5K4ECGX_SCENE_MODE \
		(V4L2_CID_CAMERA_CLASS_BASE + 0x2002)

#define V4L2_CID_S5K4ECGX_FOCUS_MODE \
		(V4L2_CID_CAMERA_CLASS_BASE + 0x2003)

enum v4l2_s5k4ecgx_cap_mode {
	V4L2_S5K4ECGX_CAP_MODE_PREVIEW,
	V4L2_S5K4ECGX_CAP_MODE_STILL,
};

enum s5k4ecgx_res_support {
	S5K4ECGX_FMT_INVALID = -1,

	S5K4ECGX_FMT_QCIF = 0,
	S5K4ECGX_FMT_QVGA,
	S5K4ECGX_FMT_VGA,
	S5K4ECGX_FMT_SVGA,
	S5K4ECGX_FMT_XGA,
	S5K4ECGX_FMT_QUAD_VGA,
	S5K4ECGX_FMT_2560x1920,
	S5K4ECGX_FMT_480P,
	S5K4ECGX_FMT_720P,

	S5K4ECGX_FMT_END,
};

typedef enum {
	S5K4ECGX_SCENE_MODE_AUTO,
	S5K4ECGX_SCENE_MODE_ACTION,
	S5K4ECGX_SCENE_MODE_NIGHT,
	S5K4ECGX_SCENE_MODE_SUNSET,
	S5K4ECGX_SCENE_MODE_PARTY,
	S5K4ECGX_SCENE_MODE_BARCODE,
} v4l2_s5k4ecgx_scene_mode_t;

// focus mode
typedef enum
{
	S5K4ECGX_FOCUS_AUTO_ONESHOT            = 0x0,  // need CAM_CMD_START_FOCUS trigger focus
	S5K4ECGX_FOCUS_AUTO_CONTINUOUS_VIDEO,
	S5K4ECGX_FOCUS_AUTO_CONTINUOUS_PICTURE,  // use CAM_CMD_START_FOCUS to pasue CAF, CAM_CMD_CANCEL_FOCUS to resume CAF
	S5K4ECGX_FOCUS_SUPERMACRO,
	S5K4ECGX_FOCUS_MACRO,  // need CAM_CMD_START_FOCUS trigger focus
	S5K4ECGX_FOCUS_HYPERFOCAL,
	S5K4ECGX_FOCUS_INFINITY,
	S5K4ECGX_FOCUS_MANUAL,

	S5K4ECGX_FOCUS_NUM,

	S5K4ECGX_FOCUS_LIMIT                  = 0x7fffffff,
} v4l2_s5k4ecgx_FocusMode;


struct s5k4ecgx_ctrls {
	struct v4l2_ctrl_handler ctrl_handler;
	struct v4l2_ctrl *af_mode;
	struct v4l2_ctrl *af_start;
	struct v4l2_ctrl *af_stop;
	struct v4l2_ctrl *af_status;
	struct v4l2_ctrl *cap_mode;
	struct v4l2_ctrl *scn_mode;
};

struct s5k4ecgx {
	struct v4l2_subdev subdev;
	int model;	/* V4L2_IDENT_S5K4ECGX codes from v4l2-chip-ident.h */
	struct v4l2_rect rect;
	u32 pixfmt;
	int frame_rate;
	struct i2c_client *client;
	struct soc_camera_device icd;
	struct s5k4ecgx_ctrls ctrls;
#ifdef DEBUG_ENABLE_SYSFS
	s5k4ecgx_register_t sysfs_reg;
#endif /* DEBUG_ENABLE_SYSFS */
};

struct s5k4ecgx_datafmt {
	enum v4l2_mbus_pixelcode	code;
	enum v4l2_colorspace		colorspace;
};

struct s5k4ecgx_resolution_table {
	int width;
	int height;
	enum s5k4ecgx_res_support res_code;
};

static const reg_value_t g_s5k4ecgx_i2cseq_init[] = {

/////////////////////////////////////////////////////////////////////////////////////// 
//   Initial 2014.04.03版
///////////////////////////////////////////////////////////////////////////////////////

//// Sanyo_Edu_s5k4ecgx_initial
//==================================================================================
// 00.History
//==================================================================================
//2010 : EVT1.1
//20110429 : LSI CSE Standard
//20110728 : Sequence Changed
//20110728 : ESD Check Register Address Changed
//20110829 : TnP Changed by S.Y.Lee
//20120104 : init Parm Update sequence changed
//20120201 : Flash獣 爽痕採 Green Noise 鯵識 setting 
//20120228 : Add Brightness Block
//20120717 : AWB Bypass Mode low temp bypass
//==================================================================================
 
//$MIPI[Width:640,Height:480,Format:YUV422,Lane:2,ErrorCheck:0,PolarityData:0,PolarityClock:0,Buffer:2,DataRate:600] 

//==================================================================================
// 01.Start Setting
//==================================================================================

{0xFCFC, 0xD000},
{0x0010, 0x0001},	//S/W Reset
{0x1030, 0x0000},	//contint_host_int
{0x0014, 0x0001, 10},	//sw_load_complete - Release CORE (Arm) from reset state

//p10 //Delay 10ms

//==================================================================================                
//02.ETC Setting
//==================================================================================                

{0x0028, 0xD000},	//Driving Current                                                                   
{0x002A, 0x1082},                                                                                           
{0x0f12, 0x0000}, 	//cregs_d0_d4_cd10 //D4[9:8], D3[7:6], D2[5:4], D1[3:2], D0[1:0]                    
{0x002A, 0x1084},                                                                                           
{0x0f12, 0x0000}, 	//cregs_d5_d9_cd10 //D9[9:8], D8[7:6], D7[5:4], D6[3:2], D5[1:0]                    
{0x002A, 0x1088},                                                                                           
{0x0f12, 0x0000},	//cregs_clks_output_cd10 //SDA[11:10], SCL[9:8], PCLK[7:6], VSYNC[3:2], HSYNC[1:0]  

//==================================================================================
// 03.Analog Setting1 & ASP Control
//==================================================================================
//This register is for FACTORY ONLY.
//If you change it without prior notification
//YOU are RESPONSIBLE for the FAILURE that will happen in the future

{0x0028, 0xD000},
{0x002A, 0x007A},
{0x0f12, 0x0000},	
{0x002A, 0xE406},	//[7]f_ladlc_en [6:5]f max [4]fadlc_en [3:2]L max [1]ladlc_en [0]adlc_ch_sel
{0x0F12, 0x0092},
{0x002A, 0xE410},
{0x0F12, 0x3804},	//[15:8]fadlc_filter_co_b, [7:0]fadlc_filter_co_a	
{0x002A, 0xE41A},
{0x0F12, 0x0010},	 	
{0x002A, 0xE420},
{0x0F12, 0x0003},	//adlc_fadlc_filter_refresh 	
{0x0F12, 0x0060},	//adlc_filter_level_diff_threshold
{0x002A, 0xE42E},
{0x0F12, 0x0004},	//dithered l-ADLC(4bit)
{0x002A, 0xF400},
{0x0F12, 0x5A3C},	//[15:8]stx_width, [7:0]dstx_width 
{0x0F12, 0x0023},	//[14]binning_test [13]gain_mode [11:12]row_id [10]cfpn_test [9]pd_pix [8]teg_en, [7]adc_res, [6]smp_en, [5]ldb_en, [4]ld_en, [3]clp_en [2]srx_en, [1]dshut_en, [0]dcds_en 
{0x0F12, 0x8080},	//CDS option 
{0x0F12, 0x03AF},	//[11:6]rst_mx, [5:0]sig_mx
{0x0F12, 0x000A},	//Avg mode
{0x0F12, 0xAA54},	//x1‾x1.49:No MS, x1.5‾x3.99:MS2, x4‾x16:MS4
{0x0F12, 0x0040},	//RMP option [6]1: RES gain
{0x0F12, 0x464E},	//[14]msoff_en, [13:8]off_rst, [7:0]adc_sat
{0x0F12, 0x0240},	//bist_sig_width_e
{0x0F12, 0x0240},	//bist_sig_width_o
{0x0F12, 0x0040},	//[9]dbs_bist_en, [8:0]bist_rst_width
{0x0F12, 0x1000},	//[15]aac_en, [14]GCLK_DIV2_EN, [13:10]dl_cont [9:8]dbs_mode, [7:0]dbs_option
{0x0F12, 0x55FF},	//bias [15:12]pix, [11:8]pix_bst [7:4]comp2, [3:0]comp1  	
{0x0F12, 0xD000},	//[15:8]clp_lvl, [7:0]ref_option, [5]pix_bst_en
{0x0F12, 0x0010},	//[7:0]monit
{0x0F12, 0x0202},	//[15:8]dbr_tune_tgsl, [7:0]dbr_tune_pix
{0x0F12, 0x0401},	//[15:8]dbr_tune_ntg, [7:0]dbr_tune_rg                                                                       
{0x0F12, 0x0022},	//[15:8]reg_option, [7:4]rosc_tune_ncp, [3:0]rosc_tune_cp                                                    
{0x0F12, 0x0088},	//PD [8]inrush_ctrl, [7]fblv, [6]reg_ntg, [5]reg_tgsl, [4]reg_rg, [3]reg_pix, [2]ncp_rosc, [1]cp_rosc, [0]cp 
{0x0F12, 0x009F},	//[9]capa_ctrl_en, [8:7]fb_lv, [6:5]dbr_clk_sel, [4:0]cp_capa                                                
{0x0F12, 0x0000},	//[15:0]blst_en_cintr                                                                                        
{0x0F12, 0x1800},	//[11]blst_en, [10]rfpn_test, [9]sl_off, [8]tx_off, [7:0]rdv_option                                          
{0x0F12, 0x0088},	//[15:0]pmg_reg_tune                                                                                         
{0x0F12, 0x0000},	//[15:1]analog_dummy, [0]pd_reg_test 
{0x0F12, 0x2428},	//[13:11]srx_gap1, [10:8]srx_gap0, [7:0]stx_gap
{0x0F12, 0x0000},	//[0]atx_option       
{0x0F12, 0x03EE},	//aig_avg_half
{0x0F12, 0x0000},	//[0]hvs_test_reg     
{0x0F12, 0x0000},	//[0]dbus_bist_auto   
{0x0F12, 0x0000},	//[7:0]dbr_option	    
{0x002A, 0xF552},
{0x0F12, 0x0708},	//[7:0]lat_st, [15:8]lat_width  
{0x0F12, 0x080C},	//[7:0]hold_st, [15:8]hold_width
	

//==================================================================================
// 07. Analog Setting 2 
//==================================================================================   
//This register is for FACTORY ONLY. 
//If you change it without prior notification
//YOU are RESPONSIBLE for the FAILURE that will happen in the future      
//For subsampling Size	
	
{0x0028, 0x7000},	
{0x002A, 0x18BC},
{0x0F12, 0x0004},
{0x0F12, 0x05B6},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0001},
{0x0F12, 0x05BA},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0007},
{0x0F12, 0x05BA},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x01F4},
{0x0F12, 0x024E},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x01F4},
{0x0F12, 0x05B6},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x01F4},
{0x0F12, 0x05BA},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x01F4},
{0x0F12, 0x024F},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0075},
{0x0F12, 0x00CF},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0075},
{0x0F12, 0x00D6},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0004},
{0x0F12, 0x01F4},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x00F0},
{0x0F12, 0x01F4},
{0x0F12, 0x029E},
{0x0F12, 0x05B2},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x01F8},
{0x0F12, 0x0228},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0208},
{0x0F12, 0x0238},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0218},
{0x0F12, 0x0238},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0001},
{0x0F12, 0x0009},
{0x0F12, 0x00DE},
{0x0F12, 0x05C0},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x00DF},
{0x0F12, 0x00E4},
{0x0F12, 0x01F8},
{0x0F12, 0x01FD},
{0x0F12, 0x05B6},
{0x0F12, 0x05BB},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x01F8},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0077},
{0x0F12, 0x007E},
{0x0F12, 0x024F},
{0x0F12, 0x025E},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
	
 // For Capture 	
	
{0x0F12, 0x0004},
{0x0F12, 0x09D1},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0001},
{0x0F12, 0x09D5},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0008},
{0x0F12, 0x09D5},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x02AA},
{0x0F12, 0x0326},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x02AA},
{0x0F12, 0x09D1},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x02AA},
{0x0F12, 0x09D5},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x02AA},
{0x0F12, 0x0327},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0008},
{0x0F12, 0x0084},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0008},
{0x0F12, 0x008D},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0008},
{0x0F12, 0x02AA},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x00AA},
{0x0F12, 0x02AA},
{0x0F12, 0x03AD},
{0x0F12, 0x09CD},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x02AE},
{0x0F12, 0x02DE},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x02BE},
{0x0F12, 0x02EE},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x02CE},
{0x0F12, 0x02EE},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0001},
{0x0F12, 0x0009},
{0x0F12, 0x0095},
{0x0F12, 0x09DB},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0096},
{0x0F12, 0x009B},
{0x0F12, 0x02AE},
{0x0F12, 0x02B3},
{0x0F12, 0x09D1},
{0x0F12, 0x09D6},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x02AE},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0009},
{0x0F12, 0x0010},
{0x0F12, 0x0327},
{0x0F12, 0x0336},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
	
{0x002A, 0x1AF8},
{0x0F12, 0x5A3C},	//senHal_TuneStr_AngTuneData1_2_D000F400 register at subsampling
{0x002A, 0x1896},
{0x0F12, 0x0002},	//senHal_SamplingType	0002 03EE: PLA setting          
{0x0F12, 0x0000},	//senHal_SamplingMode 0 : 2 PLA / 1 : 4PLA              
{0x0F12, 0x0003},	//senHal_PLAOption	[0] VPLA enable  [1] HPLA enable

{0x002A, 0x1B00},  //Green Noise 鯵識
{0x0F12, 0xF428},
{0x0F12, 0xFFFF},
{0x0F12, 0x0000},

{0x002A, 0x189E},
{0x0F12, 0x0FB0},	//senHal_ExpMinPixels
{0x002A, 0x18AC},
{0x0F12, 0x0060},	//senHal_uAddColsBin  
{0x0F12, 0x0060},	//senHal_uAddColsNoBin
{0x0F12, 0x05C0},	//senHal_uMinColsBin  , Note: When use 1280x960 binning,to avoid abnormal image,value should be changed to 0x07DC or bigger value
{0x0F12, 0x05C0},	//senHal_uMinColsNoBin
{0x002A, 0x1AEA},
{0x0F12, 0x8080},	//senHal_SubF404Tune 
{0x0F12, 0x0080},	//senHal_FullF404Tune
{0x002A, 0x1AE0},
{0x0F12, 0x0000},	//senHal_bSenAAC     
{0x002A, 0x1A72},
{0x0F12, 0x0000},	//senHal_bSRX	SRX off
{0x002A, 0x18A2},
{0x0F12, 0x0004},	//senHal_NExpLinesCheckFine extend Forbidden area line       
{0x002A, 0x1A6A},
{0x0F12, 0x009A},	//senHal_usForbiddenRightOfs extend right Forbidden area line
{0x002A, 0x385E},
{0x0F12, 0x024C},	//Mon_Sen_uExpPixelsOfs                                      
{0x002A, 0x0EE6},
{0x0F12, 0x0000},	//setot_bUseDigitalHbin
{0x002A, 0x1B2A},
{0x0F12, 0x0300},	//70001B2A //senHal_TuneStr2_usAngTuneGainTh	
{0x0F12, 0x00D6},	//70001B2C //senHal_TuneStr2_AngTuneF4CA_0_ 
{0x0F12, 0x008D},	//70001B2E //senHal_TuneStr2_AngTuneF4CA_1_ 
{0x0F12, 0x00CF},	//70001B30 //senHal_TuneStr2_AngTuneF4C2_0_ 
{0x0F12, 0x0084},	//70001B32 //senHal_TuneStr2_AngTuneF4C2_1_ 

//==================================================================================
// 05.OTP Control 
//==================================================================================

{0x0028, 0x7000},
{0x002A, 0x0722},
{0x0F12, 0x0100},	//skl_OTP_usWaitTime This register should be positioned in fornt of D0001000	
{0x002A, 0x0726},
{0x0F12, 0x0001},	//skl_bUseOTPfunc This is OTP on/off function	
{0x002A, 0x08D6},
{0x0F12, 0x0001},	//ash_bUseOTPData	
{0x002A, 0x146E},
{0x0F12, 0x0000},	//awbb_otp_disable	
{0x002A, 0x08DC},
{0x0F12, 0x0000},	//ash_bUseGasAlphaOTP	

{0x0028, 0xD000},
{0x002A, 0x1000},
{0x0F12, 0x0001},

//=================================================================================
// 04.Trap and Patch
//=================================================================================
// Start of Patch data

{0x0028, 0x7000},
{0x002A, 0x3AF8},
{0x0F12, 0xB5F8},    // 70003AF8
{0x0F12, 0x4B44},    // 70003AFA
{0x0F12, 0x4944},    // 70003AFC
{0x0F12, 0x4845},    // 70003AFE
{0x0F12, 0x2200},    // 70003B00
{0x0F12, 0xC008},    // 70003B02
{0x0F12, 0x6001},    // 70003B04
{0x0F12, 0x4944},    // 70003B06
{0x0F12, 0x4844},    // 70003B08
{0x0F12, 0x2401},    // 70003B0A
{0x0F12, 0xF000},    // 70003B0C
{0x0F12, 0xFCA4},    // 70003B0E
{0x0F12, 0x4943},    // 70003B10
{0x0F12, 0x4844},    // 70003B12
{0x0F12, 0x2702},    // 70003B14
{0x0F12, 0x0022},    // 70003B16
{0x0F12, 0xF000},    // 70003B18
{0x0F12, 0xFC9E},    // 70003B1A
{0x0F12, 0x0260},    // 70003B1C
{0x0F12, 0x4C42},    // 70003B1E
{0x0F12, 0x8020},    // 70003B20
{0x0F12, 0x2600},    // 70003B22
{0x0F12, 0x8066},    // 70003B24
{0x0F12, 0x4941},    // 70003B26
{0x0F12, 0x4841},    // 70003B28
{0x0F12, 0x6041},    // 70003B2A
{0x0F12, 0x4941},    // 70003B2C
{0x0F12, 0x4842},    // 70003B2E
{0x0F12, 0x003A},    // 70003B30
{0x0F12, 0x2503},    // 70003B32
{0x0F12, 0xF000},    // 70003B34
{0x0F12, 0xFC90},    // 70003B36
{0x0F12, 0x483D},    // 70003B38
{0x0F12, 0x4940},    // 70003B3A
{0x0F12, 0x30C0},    // 70003B3C
{0x0F12, 0x63C1},    // 70003B3E
{0x0F12, 0x4F3B},    // 70003B40
{0x0F12, 0x483F},    // 70003B42
{0x0F12, 0x3F80},    // 70003B44
{0x0F12, 0x6438},    // 70003B46
{0x0F12, 0x483E},    // 70003B48
{0x0F12, 0x493F},    // 70003B4A
{0x0F12, 0x6388},    // 70003B4C
{0x0F12, 0x002A},    // 70003B4E
{0x0F12, 0x493E},    // 70003B50
{0x0F12, 0x483F},    // 70003B52
{0x0F12, 0x2504},    // 70003B54
{0x0F12, 0xF000},    // 70003B56
{0x0F12, 0xFC7F},    // 70003B58
{0x0F12, 0x002A},    // 70003B5A
{0x0F12, 0x493D},    // 70003B5C
{0x0F12, 0x483E},    // 70003B5E
{0x0F12, 0x2505},    // 70003B60
{0x0F12, 0xF000},    // 70003B62
{0x0F12, 0xF8A7},    // 70003B64
{0x0F12, 0x483C},    // 70003B66
{0x0F12, 0x002A},    // 70003B68
{0x0F12, 0x493C},    // 70003B6A
{0x0F12, 0x2506},    // 70003B6C
{0x0F12, 0x1D80},    // 70003B6E
{0x0F12, 0xF000},    // 70003B70
{0x0F12, 0xF8A0},    // 70003B72
{0x0F12, 0x4838},    // 70003B74
{0x0F12, 0x002A},    // 70003B76
{0x0F12, 0x4939},    // 70003B78
{0x0F12, 0x2507},    // 70003B7A
{0x0F12, 0x300C},    // 70003B7C
{0x0F12, 0xF000},    // 70003B7E
{0x0F12, 0xF899},    // 70003B80
{0x0F12, 0x4835},    // 70003B82
{0x0F12, 0x002A},    // 70003B84
{0x0F12, 0x4937},    // 70003B86
{0x0F12, 0x2508},    // 70003B88
{0x0F12, 0x3010},    // 70003B8A
{0x0F12, 0xF000},    // 70003B8C
{0x0F12, 0xF892},    // 70003B8E
{0x0F12, 0x002A},    // 70003B90
{0x0F12, 0x4935},    // 70003B92
{0x0F12, 0x4835},    // 70003B94
{0x0F12, 0x2509},    // 70003B96
{0x0F12, 0xF000},    // 70003B98
{0x0F12, 0xFC5E},    // 70003B9A
{0x0F12, 0x002A},    // 70003B9C
{0x0F12, 0x4934},    // 70003B9E
{0x0F12, 0x4834},    // 70003BA0
{0x0F12, 0x250A},    // 70003BA2
{0x0F12, 0xF000},    // 70003BA4
{0x0F12, 0xFC58},    // 70003BA6
{0x0F12, 0x002A},    // 70003BA8
{0x0F12, 0x4933},    // 70003BAA
{0x0F12, 0x4833},    // 70003BAC
{0x0F12, 0x250B},    // 70003BAE
{0x0F12, 0xF000},    // 70003BB0
{0x0F12, 0xFC52},    // 70003BB2
{0x0F12, 0x002A},    // 70003BB4
{0x0F12, 0x4932},    // 70003BB6
{0x0F12, 0x4832},    // 70003BB8
{0x0F12, 0x250C},    // 70003BBA
{0x0F12, 0xF000},    // 70003BBC
{0x0F12, 0xFC4C},    // 70003BBE
{0x0F12, 0x002A},    // 70003BC0
{0x0F12, 0x4931},    // 70003BC2
{0x0F12, 0x4831},    // 70003BC4
{0x0F12, 0x250D},    // 70003BC6
{0x0F12, 0xF000},    // 70003BC8
{0x0F12, 0xFC46},    // 70003BCA
{0x0F12, 0x002A},    // 70003BCC
{0x0F12, 0x4930},    // 70003BCE
{0x0F12, 0x4830},    // 70003BD0
{0x0F12, 0x250E},    // 70003BD2
{0x0F12, 0xF000},    // 70003BD4
{0x0F12, 0xFC40},    // 70003BD6
{0x0F12, 0x002A},    // 70003BD8
{0x0F12, 0x492F},    // 70003BDA
{0x0F12, 0x482F},    // 70003BDC
{0x0F12, 0x250F},    // 70003BDE
{0x0F12, 0xF000},    // 70003BE0
{0x0F12, 0xFC3A},    // 70003BE2
{0x0F12, 0x8626},    // 70003BE4
{0x0F12, 0x20FF},    // 70003BE6
{0x0F12, 0x1C40},    // 70003BE8
{0x0F12, 0x8660},    // 70003BEA
{0x0F12, 0x482C},    // 70003BEC
{0x0F12, 0x64F8},    // 70003BEE
{0x0F12, 0x492C},    // 70003BF0
{0x0F12, 0x482D},    // 70003BF2
{0x0F12, 0x2410},    // 70003BF4
{0x0F12, 0x002A},    // 70003BF6
{0x0F12, 0xF000},    // 70003BF8
{0x0F12, 0xFC2E},    // 70003BFA
{0x0F12, 0x492B},    // 70003BFC
{0x0F12, 0x482C},    // 70003BFE
{0x0F12, 0x0022},    // 70003C00
{0x0F12, 0xF000},    // 70003C02
{0x0F12, 0xFC29},    // 70003C04
{0x0F12, 0xBCF8},    // 70003C06
{0x0F12, 0xBC08},    // 70003C08
{0x0F12, 0x4718},    // 70003C0A
{0x0F12, 0x019C},    // 70003C0C
{0x0F12, 0x4EC2},    // 70003C0E
{0x0F12, 0x73FF},    // 70003C10
{0x0F12, 0x0000},    // 70003C12
{0x0F12, 0x1F90},    // 70003C14
{0x0F12, 0x7000},    // 70003C16
{0x0F12, 0x3CCD},    // 70003C18
{0x0F12, 0x7000},    // 70003C1A
{0x0F12, 0xE38B},    // 70003C1C
{0x0F12, 0x0000},    // 70003C1E
{0x0F12, 0x3D05},    // 70003C20
{0x0F12, 0x7000},    // 70003C22
{0x0F12, 0xC3B1},    // 70003C24
{0x0F12, 0x0000},    // 70003C26
{0x0F12, 0x4780},    // 70003C28
{0x0F12, 0x7000},    // 70003C2A
{0x0F12, 0x3D63},    // 70003C2C
{0x0F12, 0x7000},    // 70003C2E
{0x0F12, 0x0080},    // 70003C30
{0x0F12, 0x7000},    // 70003C32
{0x0F12, 0x3D9F},    // 70003C34
{0x0F12, 0x7000},    // 70003C36
{0x0F12, 0xB49D},    // 70003C38
{0x0F12, 0x0000},    // 70003C3A
{0x0F12, 0x3E4B},    // 70003C3C
{0x0F12, 0x7000},    // 70003C3E
{0x0F12, 0x3DFF},    // 70003C40
{0x0F12, 0x7000},    // 70003C42
{0x0F12, 0xFFFF},    // 70003C44
{0x0F12, 0x00FF},    // 70003C46
{0x0F12, 0x17E0},    // 70003C48
{0x0F12, 0x7000},    // 70003C4A
{0x0F12, 0x3FC7},    // 70003C4C
{0x0F12, 0x7000},    // 70003C4E
{0x0F12, 0x053D},    // 70003C50
{0x0F12, 0x0000},    // 70003C52
{0x0F12, 0x0000},    // 70003C54
{0x0F12, 0x0A89},    // 70003C56
{0x0F12, 0x6CD2},    // 70003C58
{0x0F12, 0x0000},    // 70003C5A
{0x0F12, 0x02C9},    // 70003C5C
{0x0F12, 0x0000},    // 70003C5E
{0x0F12, 0x0000},    // 70003C60
{0x0F12, 0x0A9A},    // 70003C62
{0x0F12, 0x0000},    // 70003C64
{0x0F12, 0x02D2},    // 70003C66
{0x0F12, 0x4015},    // 70003C68
{0x0F12, 0x7000},    // 70003C6A
{0x0F12, 0x9E65},    // 70003C6C
{0x0F12, 0x0000},    // 70003C6E
{0x0F12, 0x4089},    // 70003C70
{0x0F12, 0x7000},    // 70003C72
{0x0F12, 0x7C49},    // 70003C74
{0x0F12, 0x0000},    // 70003C76
{0x0F12, 0x40FD},    // 70003C78
{0x0F12, 0x7000},    // 70003C7A
{0x0F12, 0x7C63},    // 70003C7C
{0x0F12, 0x0000},    // 70003C7E
{0x0F12, 0x4119},    // 70003C80
{0x0F12, 0x7000},    // 70003C82
{0x0F12, 0x8F01},    // 70003C84
{0x0F12, 0x0000},    // 70003C86
{0x0F12, 0x41BB},    // 70003C88
{0x0F12, 0x7000},    // 70003C8A
{0x0F12, 0x7F3F},    // 70003C8C
{0x0F12, 0x0000},    // 70003C8E
{0x0F12, 0x4249},    // 70003C90
{0x0F12, 0x7000},    // 70003C92
{0x0F12, 0x98C5},    // 70003C94
{0x0F12, 0x0000},    // 70003C96
{0x0F12, 0x43B5},    // 70003C98
{0x0F12, 0x7000},    // 70003C9A
{0x0F12, 0x6099},    // 70003C9C
{0x0F12, 0x0000},    // 70003C9E
{0x0F12, 0x430F},    // 70003CA0
{0x0F12, 0x7000},    // 70003CA2
{0x0F12, 0x4365},    // 70003CA4
{0x0F12, 0x7000},    // 70003CA6
{0x0F12, 0xA70B},    // 70003CA8
{0x0F12, 0x0000},    // 70003CAA
{0x0F12, 0x4387},    // 70003CAC
{0x0F12, 0x7000},    // 70003CAE
{0x0F12, 0x400D},    // 70003CB0
{0x0F12, 0x0000},    // 70003CB2
{0x0F12, 0xB570},    // 70003CB4
{0x0F12, 0x000C},    // 70003CB6
{0x0F12, 0x0015},    // 70003CB8
{0x0F12, 0x0029},    // 70003CBA
{0x0F12, 0xF000},    // 70003CBC
{0x0F12, 0xFBD4},    // 70003CBE
{0x0F12, 0x49F8},    // 70003CC0
{0x0F12, 0x00A8},    // 70003CC2
{0x0F12, 0x500C},    // 70003CC4
{0x0F12, 0xBC70},    // 70003CC6
{0x0F12, 0xBC08},    // 70003CC8
{0x0F12, 0x4718},    // 70003CCA
{0x0F12, 0x6808},    // 70003CCC
{0x0F12, 0x0400},    // 70003CCE
{0x0F12, 0x0C00},    // 70003CD0
{0x0F12, 0x6849},    // 70003CD2
{0x0F12, 0x0409},    // 70003CD4
{0x0F12, 0x0C09},    // 70003CD6
{0x0F12, 0x4AF3},    // 70003CD8
{0x0F12, 0x8992},    // 70003CDA
{0x0F12, 0x2A00},    // 70003CDC
{0x0F12, 0xD00D},    // 70003CDE
{0x0F12, 0x2300},    // 70003CE0
{0x0F12, 0x1A89},    // 70003CE2
{0x0F12, 0xD400},    // 70003CE4
{0x0F12, 0x000B},    // 70003CE6
{0x0F12, 0x0419},    // 70003CE8
{0x0F12, 0x0C09},    // 70003CEA
{0x0F12, 0x23FF},    // 70003CEC
{0x0F12, 0x33C1},    // 70003CEE
{0x0F12, 0x1810},    // 70003CF0
{0x0F12, 0x4298},    // 70003CF2
{0x0F12, 0xD800},    // 70003CF4
{0x0F12, 0x0003},    // 70003CF6
{0x0F12, 0x0418},    // 70003CF8
{0x0F12, 0x0C00},    // 70003CFA
{0x0F12, 0x4AEB},    // 70003CFC
{0x0F12, 0x8150},    // 70003CFE
{0x0F12, 0x8191},    // 70003D00
{0x0F12, 0x4770},    // 70003D02
{0x0F12, 0xB5F3},    // 70003D04
{0x0F12, 0x0004},    // 70003D06
{0x0F12, 0xB081},    // 70003D08
{0x0F12, 0x9802},    // 70003D0A
{0x0F12, 0x6800},    // 70003D0C
{0x0F12, 0x0600},    // 70003D0E
{0x0F12, 0x0E00},    // 70003D10
{0x0F12, 0x2201},    // 70003D12
{0x0F12, 0x0015},    // 70003D14
{0x0F12, 0x0021},    // 70003D16
{0x0F12, 0x3910},    // 70003D18
{0x0F12, 0x408A},    // 70003D1A
{0x0F12, 0x40A5},    // 70003D1C
{0x0F12, 0x4FE4},    // 70003D1E
{0x0F12, 0x0016},    // 70003D20
{0x0F12, 0x2C10},    // 70003D22
{0x0F12, 0xDA03},    // 70003D24
{0x0F12, 0x8839},    // 70003D26
{0x0F12, 0x43A9},    // 70003D28
{0x0F12, 0x8039},    // 70003D2A
{0x0F12, 0xE002},    // 70003D2C
{0x0F12, 0x8879},    // 70003D2E
{0x0F12, 0x43B1},    // 70003D30
{0x0F12, 0x8079},    // 70003D32
{0x0F12, 0xF000},    // 70003D34
{0x0F12, 0xFBA0},    // 70003D36
{0x0F12, 0x2C10},    // 70003D38
{0x0F12, 0xDA03},    // 70003D3A
{0x0F12, 0x8839},    // 70003D3C
{0x0F12, 0x4329},    // 70003D3E
{0x0F12, 0x8039},    // 70003D40
{0x0F12, 0xE002},    // 70003D42
{0x0F12, 0x8879},    // 70003D44
{0x0F12, 0x4331},    // 70003D46
{0x0F12, 0x8079},    // 70003D48
{0x0F12, 0x49DA},    // 70003D4A
{0x0F12, 0x8809},    // 70003D4C
{0x0F12, 0x2900},    // 70003D4E
{0x0F12, 0xD102},    // 70003D50
{0x0F12, 0xF000},    // 70003D52
{0x0F12, 0xFB99},    // 70003D54
{0x0F12, 0x2000},    // 70003D56
{0x0F12, 0x9902},    // 70003D58
{0x0F12, 0x6008},    // 70003D5A
{0x0F12, 0xBCFE},    // 70003D5C
{0x0F12, 0xBC08},    // 70003D5E
{0x0F12, 0x4718},    // 70003D60
{0x0F12, 0xB538},    // 70003D62
{0x0F12, 0x9C04},    // 70003D64
{0x0F12, 0x0015},    // 70003D66
{0x0F12, 0x002A},    // 70003D68
{0x0F12, 0x9400},    // 70003D6A
{0x0F12, 0xF000},    // 70003D6C
{0x0F12, 0xFB94},    // 70003D6E
{0x0F12, 0x4AD1},    // 70003D70
{0x0F12, 0x8811},    // 70003D72
{0x0F12, 0x2900},    // 70003D74
{0x0F12, 0xD00F},    // 70003D76
{0x0F12, 0x8820},    // 70003D78
{0x0F12, 0x4281},    // 70003D7A
{0x0F12, 0xD20C},    // 70003D7C
{0x0F12, 0x8861},    // 70003D7E
{0x0F12, 0x8853},    // 70003D80
{0x0F12, 0x4299},    // 70003D82
{0x0F12, 0xD200},    // 70003D84
{0x0F12, 0x1E40},    // 70003D86
{0x0F12, 0x0400},    // 70003D88
{0x0F12, 0x0C00},    // 70003D8A
{0x0F12, 0x8020},    // 70003D8C
{0x0F12, 0x8851},    // 70003D8E
{0x0F12, 0x8061},    // 70003D90
{0x0F12, 0x4368},    // 70003D92
{0x0F12, 0x1840},    // 70003D94
{0x0F12, 0x6060},    // 70003D96
{0x0F12, 0xBC38},    // 70003D98
{0x0F12, 0xBC08},    // 70003D9A
{0x0F12, 0x4718},    // 70003D9C
{0x0F12, 0xB5F8},    // 70003D9E
{0x0F12, 0x0004},    // 70003DA0
{0x0F12, 0x6808},    // 70003DA2
{0x0F12, 0x0400},    // 70003DA4
{0x0F12, 0x0C00},    // 70003DA6
{0x0F12, 0x2201},    // 70003DA8
{0x0F12, 0x0015},    // 70003DAA
{0x0F12, 0x0021},    // 70003DAC
{0x0F12, 0x3910},    // 70003DAE
{0x0F12, 0x408A},    // 70003DB0
{0x0F12, 0x40A5},    // 70003DB2
{0x0F12, 0x4FBE},    // 70003DB4
{0x0F12, 0x0016},    // 70003DB6
{0x0F12, 0x2C10},    // 70003DB8
{0x0F12, 0xDA03},    // 70003DBA
{0x0F12, 0x8839},    // 70003DBC
{0x0F12, 0x43A9},    // 70003DBE
{0x0F12, 0x8039},    // 70003DC0
{0x0F12, 0xE002},    // 70003DC2
{0x0F12, 0x8879},    // 70003DC4
{0x0F12, 0x43B1},    // 70003DC6
{0x0F12, 0x8079},    // 70003DC8
{0x0F12, 0xF000},    // 70003DCA
{0x0F12, 0xFB6D},    // 70003DCC
{0x0F12, 0x2C10},    // 70003DCE
{0x0F12, 0xDA03},    // 70003DD0
{0x0F12, 0x8838},    // 70003DD2
{0x0F12, 0x4328},    // 70003DD4
{0x0F12, 0x8038},    // 70003DD6
{0x0F12, 0xE002},    // 70003DD8
{0x0F12, 0x8878},    // 70003DDA
{0x0F12, 0x4330},    // 70003DDC
{0x0F12, 0x8078},    // 70003DDE
{0x0F12, 0x48B6},    // 70003DE0
{0x0F12, 0x8800},    // 70003DE2
{0x0F12, 0x0400},    // 70003DE4
{0x0F12, 0xD507},    // 70003DE6
{0x0F12, 0x4BB5},    // 70003DE8
{0x0F12, 0x7819},    // 70003DEA
{0x0F12, 0x4AB5},    // 70003DEC
{0x0F12, 0x7810},    // 70003DEE
{0x0F12, 0x7018},    // 70003DF0
{0x0F12, 0x7011},    // 70003DF2
{0x0F12, 0x49B4},    // 70003DF4
{0x0F12, 0x8188},    // 70003DF6
{0x0F12, 0xBCF8},    // 70003DF8
{0x0F12, 0xBC08},    // 70003DFA
{0x0F12, 0x4718},    // 70003DFC
{0x0F12, 0xB538},    // 70003DFE
{0x0F12, 0x48B2},    // 70003E00
{0x0F12, 0x4669},    // 70003E02
{0x0F12, 0xF000},    // 70003E04
{0x0F12, 0xFB58},    // 70003E06
{0x0F12, 0x48B1},    // 70003E08
{0x0F12, 0x49B0},    // 70003E0A
{0x0F12, 0x69C2},    // 70003E0C
{0x0F12, 0x2400},    // 70003E0E
{0x0F12, 0x31A8},    // 70003E10
{0x0F12, 0x2A00},    // 70003E12
{0x0F12, 0xD008},    // 70003E14
{0x0F12, 0x61C4},    // 70003E16
{0x0F12, 0x684A},    // 70003E18
{0x0F12, 0x6242},    // 70003E1A
{0x0F12, 0x6282},    // 70003E1C
{0x0F12, 0x466B},    // 70003E1E
{0x0F12, 0x881A},    // 70003E20
{0x0F12, 0x6302},    // 70003E22
{0x0F12, 0x885A},    // 70003E24
{0x0F12, 0x6342},    // 70003E26
{0x0F12, 0x6A02},    // 70003E28
{0x0F12, 0x2A00},    // 70003E2A
{0x0F12, 0xD00A},    // 70003E2C
{0x0F12, 0x6204},    // 70003E2E
{0x0F12, 0x6849},    // 70003E30
{0x0F12, 0x6281},    // 70003E32
{0x0F12, 0x466B},    // 70003E34
{0x0F12, 0x8819},    // 70003E36
{0x0F12, 0x6301},    // 70003E38
{0x0F12, 0x8859},    // 70003E3A
{0x0F12, 0x6341},    // 70003E3C
{0x0F12, 0x49A5},    // 70003E3E
{0x0F12, 0x88C9},    // 70003E40
{0x0F12, 0x63C1},    // 70003E42
{0x0F12, 0xF000},    // 70003E44
{0x0F12, 0xFB40},    // 70003E46
{0x0F12, 0xE7A6},    // 70003E48
{0x0F12, 0xB5F0},    // 70003E4A
{0x0F12, 0xB08B},    // 70003E4C
{0x0F12, 0x20FF},    // 70003E4E
{0x0F12, 0x1C40},    // 70003E50
{0x0F12, 0x49A1},    // 70003E52
{0x0F12, 0x89CC},    // 70003E54
{0x0F12, 0x4E9E},    // 70003E56
{0x0F12, 0x6AB1},    // 70003E58
{0x0F12, 0x4284},    // 70003E5A
{0x0F12, 0xD101},    // 70003E5C
{0x0F12, 0x489F},    // 70003E5E
{0x0F12, 0x6081},    // 70003E60
{0x0F12, 0x6A70},    // 70003E62
{0x0F12, 0x0200},    // 70003E64
{0x0F12, 0xF000},    // 70003E66
{0x0F12, 0xFB37},    // 70003E68
{0x0F12, 0x0400},    // 70003E6A
{0x0F12, 0x0C00},    // 70003E6C
{0x0F12, 0x4A96},    // 70003E6E
{0x0F12, 0x8A11},    // 70003E70
{0x0F12, 0x9109},    // 70003E72
{0x0F12, 0x2101},    // 70003E74
{0x0F12, 0x0349},    // 70003E76
{0x0F12, 0x4288},    // 70003E78
{0x0F12, 0xD200},    // 70003E7A
{0x0F12, 0x0001},    // 70003E7C
{0x0F12, 0x4A92},    // 70003E7E
{0x0F12, 0x8211},    // 70003E80
{0x0F12, 0x4D97},    // 70003E82
{0x0F12, 0x8829},    // 70003E84
{0x0F12, 0x9108},    // 70003E86
{0x0F12, 0x4A8B},    // 70003E88
{0x0F12, 0x2303},    // 70003E8A
{0x0F12, 0x3222},    // 70003E8C
{0x0F12, 0x1F91},    // 70003E8E
{0x0F12, 0xF000},    // 70003E90
{0x0F12, 0xFB28},    // 70003E92
{0x0F12, 0x8028},    // 70003E94
{0x0F12, 0x488E},    // 70003E96
{0x0F12, 0x4987},    // 70003E98
{0x0F12, 0x6BC2},    // 70003E9A
{0x0F12, 0x6AC0},    // 70003E9C
{0x0F12, 0x4282},    // 70003E9E
{0x0F12, 0xD201},    // 70003EA0
{0x0F12, 0x8CC8},    // 70003EA2
{0x0F12, 0x8028},    // 70003EA4
{0x0F12, 0x88E8},    // 70003EA6
{0x0F12, 0x9007},    // 70003EA8
{0x0F12, 0x2240},    // 70003EAA
{0x0F12, 0x4310},    // 70003EAC
{0x0F12, 0x80E8},    // 70003EAE
{0x0F12, 0x2000},    // 70003EB0
{0x0F12, 0x0041},    // 70003EB2
{0x0F12, 0x194B},    // 70003EB4
{0x0F12, 0x001E},    // 70003EB6
{0x0F12, 0x3680},    // 70003EB8
{0x0F12, 0x8BB2},    // 70003EBA
{0x0F12, 0xAF04},    // 70003EBC
{0x0F12, 0x527A},    // 70003EBE
{0x0F12, 0x4A7D},    // 70003EC0
{0x0F12, 0x188A},    // 70003EC2
{0x0F12, 0x8897},    // 70003EC4
{0x0F12, 0x83B7},    // 70003EC6
{0x0F12, 0x33A0},    // 70003EC8
{0x0F12, 0x891F},    // 70003ECA
{0x0F12, 0xAE01},    // 70003ECC
{0x0F12, 0x5277},    // 70003ECE
{0x0F12, 0x8A11},    // 70003ED0
{0x0F12, 0x8119},    // 70003ED2
{0x0F12, 0x1C40},    // 70003ED4
{0x0F12, 0x0400},    // 70003ED6
{0x0F12, 0x0C00},    // 70003ED8
{0x0F12, 0x2806},    // 70003EDA
{0x0F12, 0xD3E9},    // 70003EDC
{0x0F12, 0xF000},    // 70003EDE
{0x0F12, 0xFB09},    // 70003EE0
{0x0F12, 0xF000},    // 70003EE2
{0x0F12, 0xFB0F},    // 70003EE4
{0x0F12, 0x4F79},    // 70003EE6
{0x0F12, 0x37A8},    // 70003EE8
{0x0F12, 0x2800},    // 70003EEA
{0x0F12, 0xD10A},    // 70003EEC
{0x0F12, 0x1FE0},    // 70003EEE
{0x0F12, 0x38FD},    // 70003EF0
{0x0F12, 0xD001},    // 70003EF2
{0x0F12, 0x1CC0},    // 70003EF4
{0x0F12, 0xD105},    // 70003EF6
{0x0F12, 0x4874},    // 70003EF8
{0x0F12, 0x8829},    // 70003EFA
{0x0F12, 0x3818},    // 70003EFC
{0x0F12, 0x6840},    // 70003EFE
{0x0F12, 0x4348},    // 70003F00
{0x0F12, 0x6078},    // 70003F02
{0x0F12, 0x4972},    // 70003F04
{0x0F12, 0x6878},    // 70003F06
{0x0F12, 0x6B89},    // 70003F08
{0x0F12, 0x4288},    // 70003F0A
{0x0F12, 0xD300},    // 70003F0C
{0x0F12, 0x0008},    // 70003F0E
{0x0F12, 0x6078},    // 70003F10
{0x0F12, 0x2000},    // 70003F12
{0x0F12, 0x0041},    // 70003F14
{0x0F12, 0xAA04},    // 70003F16
{0x0F12, 0x5A53},    // 70003F18
{0x0F12, 0x194A},    // 70003F1A
{0x0F12, 0x269C},    // 70003F1C
{0x0F12, 0x52B3},    // 70003F1E
{0x0F12, 0xAB01},    // 70003F20
{0x0F12, 0x5A59},    // 70003F22
{0x0F12, 0x32A0},    // 70003F24
{0x0F12, 0x8111},    // 70003F26
{0x0F12, 0x1C40},    // 70003F28
{0x0F12, 0x0400},    // 70003F2A
{0x0F12, 0x0C00},    // 70003F2C
{0x0F12, 0x2806},    // 70003F2E
{0x0F12, 0xD3F0},    // 70003F30
{0x0F12, 0x4965},    // 70003F32
{0x0F12, 0x9809},    // 70003F34
{0x0F12, 0x8208},    // 70003F36
{0x0F12, 0x9808},    // 70003F38
{0x0F12, 0x8028},    // 70003F3A
{0x0F12, 0x9807},    // 70003F3C
{0x0F12, 0x80E8},    // 70003F3E
{0x0F12, 0x1FE0},    // 70003F40
{0x0F12, 0x38FD},    // 70003F42
{0x0F12, 0xD13B},    // 70003F44
{0x0F12, 0x4D64},    // 70003F46
{0x0F12, 0x89E8},    // 70003F48
{0x0F12, 0x1FC1},    // 70003F4A
{0x0F12, 0x39FF},    // 70003F4C
{0x0F12, 0xD136},    // 70003F4E
{0x0F12, 0x4C5F},    // 70003F50
{0x0F12, 0x8AE0},    // 70003F52
{0x0F12, 0xF000},    // 70003F54
{0x0F12, 0xFADE},    // 70003F56
{0x0F12, 0x0006},    // 70003F58
{0x0F12, 0x8B20},    // 70003F5A
{0x0F12, 0xF000},    // 70003F5C
{0x0F12, 0xFAE2},    // 70003F5E
{0x0F12, 0x9000},    // 70003F60
{0x0F12, 0x6AA1},    // 70003F62
{0x0F12, 0x6878},    // 70003F64
{0x0F12, 0x1809},    // 70003F66
{0x0F12, 0x0200},    // 70003F68
{0x0F12, 0xF000},    // 70003F6A
{0x0F12, 0xFAB5},    // 70003F6C
{0x0F12, 0x0400},    // 70003F6E
{0x0F12, 0x0C00},    // 70003F70
{0x0F12, 0x0022},    // 70003F72
{0x0F12, 0x3246},    // 70003F74
{0x0F12, 0x0011},    // 70003F76
{0x0F12, 0x310A},    // 70003F78
{0x0F12, 0x2305},    // 70003F7A
{0x0F12, 0xF000},    // 70003F7C
{0x0F12, 0xFAB2},    // 70003F7E
{0x0F12, 0x66E8},    // 70003F80
{0x0F12, 0x6B23},    // 70003F82
{0x0F12, 0x0002},    // 70003F84
{0x0F12, 0x0031},    // 70003F86
{0x0F12, 0x0018},    // 70003F88
{0x0F12, 0xF000},    // 70003F8A
{0x0F12, 0xFAD3},    // 70003F8C
{0x0F12, 0x466B},    // 70003F8E
{0x0F12, 0x8518},    // 70003F90
{0x0F12, 0x6EEA},    // 70003F92
{0x0F12, 0x6B60},    // 70003F94
{0x0F12, 0x9900},    // 70003F96
{0x0F12, 0xF000},    // 70003F98
{0x0F12, 0xFACC},    // 70003F9A
{0x0F12, 0x466B},    // 70003F9C
{0x0F12, 0x8558},    // 70003F9E
{0x0F12, 0x0029},    // 70003FA0
{0x0F12, 0x980A},    // 70003FA2
{0x0F12, 0x3170},    // 70003FA4
{0x0F12, 0xF000},    // 70003FA6
{0x0F12, 0xFACD},    // 70003FA8
{0x0F12, 0x0028},    // 70003FAA
{0x0F12, 0x3060},    // 70003FAC
{0x0F12, 0x8A02},    // 70003FAE
{0x0F12, 0x4946},    // 70003FB0
{0x0F12, 0x3128},    // 70003FB2
{0x0F12, 0x808A},    // 70003FB4
{0x0F12, 0x8A42},    // 70003FB6
{0x0F12, 0x80CA},    // 70003FB8
{0x0F12, 0x8A80},    // 70003FBA
{0x0F12, 0x8108},    // 70003FBC
{0x0F12, 0xB00B},    // 70003FBE
{0x0F12, 0xBCF0},    // 70003FC0
{0x0F12, 0xBC08},    // 70003FC2
{0x0F12, 0x4718},    // 70003FC4
{0x0F12, 0xB570},    // 70003FC6
{0x0F12, 0x2400},    // 70003FC8
{0x0F12, 0x4D46},    // 70003FCA
{0x0F12, 0x4846},    // 70003FCC
{0x0F12, 0x8881},    // 70003FCE
{0x0F12, 0x4846},    // 70003FD0
{0x0F12, 0x8041},    // 70003FD2
{0x0F12, 0x2101},    // 70003FD4
{0x0F12, 0x8001},    // 70003FD6
{0x0F12, 0xF000},    // 70003FD8
{0x0F12, 0xFABC},    // 70003FDA
{0x0F12, 0x4842},    // 70003FDC
{0x0F12, 0x3820},    // 70003FDE
{0x0F12, 0x8BC0},    // 70003FE0
{0x0F12, 0xF000},    // 70003FE2
{0x0F12, 0xFABF},    // 70003FE4
{0x0F12, 0x4B42},    // 70003FE6
{0x0F12, 0x220D},    // 70003FE8
{0x0F12, 0x0712},    // 70003FEA
{0x0F12, 0x18A8},    // 70003FEC
{0x0F12, 0x8806},    // 70003FEE
{0x0F12, 0x00E1},    // 70003FF0
{0x0F12, 0x18C9},    // 70003FF2
{0x0F12, 0x81CE},    // 70003FF4
{0x0F12, 0x8846},    // 70003FF6
{0x0F12, 0x818E},    // 70003FF8
{0x0F12, 0x8886},    // 70003FFA
{0x0F12, 0x824E},    // 70003FFC
{0x0F12, 0x88C0},    // 70003FFE
{0x0F12, 0x8208},    // 70004000
{0x0F12, 0x3508},    // 70004002
{0x0F12, 0x042D},    // 70004004
{0x0F12, 0x0C2D},    // 70004006
{0x0F12, 0x1C64},    // 70004008
{0x0F12, 0x0424},    // 7000400A
{0x0F12, 0x0C24},    // 7000400C
{0x0F12, 0x2C07},    // 7000400E
{0x0F12, 0xD3EC},    // 70004010
{0x0F12, 0xE658},    // 70004012
{0x0F12, 0xB510},    // 70004014
{0x0F12, 0x4834},    // 70004016
{0x0F12, 0x4C34},    // 70004018
{0x0F12, 0x88C0},    // 7000401A
{0x0F12, 0x8060},    // 7000401C
{0x0F12, 0x2001},    // 7000401E
{0x0F12, 0x8020},    // 70004020
{0x0F12, 0x4831},    // 70004022
{0x0F12, 0x3820},    // 70004024
{0x0F12, 0x8BC0},    // 70004026
{0x0F12, 0xF000},    // 70004028
{0x0F12, 0xFA9C},    // 7000402A
{0x0F12, 0x88E0},    // 7000402C
{0x0F12, 0x4A31},    // 7000402E
{0x0F12, 0x2800},    // 70004030
{0x0F12, 0xD003},    // 70004032
{0x0F12, 0x4930},    // 70004034
{0x0F12, 0x8849},    // 70004036
{0x0F12, 0x2900},    // 70004038
{0x0F12, 0xD009},    // 7000403A
{0x0F12, 0x2001},    // 7000403C
{0x0F12, 0x03C0},    // 7000403E
{0x0F12, 0x8050},    // 70004040
{0x0F12, 0x80D0},    // 70004042
{0x0F12, 0x2000},    // 70004044
{0x0F12, 0x8090},    // 70004046
{0x0F12, 0x8110},    // 70004048
{0x0F12, 0xBC10},    // 7000404A
{0x0F12, 0xBC08},    // 7000404C
{0x0F12, 0x4718},    // 7000404E
{0x0F12, 0x8050},    // 70004050
{0x0F12, 0x8920},    // 70004052
{0x0F12, 0x80D0},    // 70004054
{0x0F12, 0x8960},    // 70004056
{0x0F12, 0x0400},    // 70004058
{0x0F12, 0x1400},    // 7000405A
{0x0F12, 0x8090},    // 7000405C
{0x0F12, 0x89A1},    // 7000405E
{0x0F12, 0x0409},    // 70004060
{0x0F12, 0x1409},    // 70004062
{0x0F12, 0x8111},    // 70004064
{0x0F12, 0x89E3},    // 70004066
{0x0F12, 0x8A24},    // 70004068
{0x0F12, 0x2B00},    // 7000406A
{0x0F12, 0xD104},    // 7000406C
{0x0F12, 0x17C3},    // 7000406E
{0x0F12, 0x0F5B},    // 70004070
{0x0F12, 0x1818},    // 70004072
{0x0F12, 0x10C0},    // 70004074
{0x0F12, 0x8090},    // 70004076
{0x0F12, 0x2C00},    // 70004078
{0x0F12, 0xD1E6},    // 7000407A
{0x0F12, 0x17C8},    // 7000407C
{0x0F12, 0x0F40},    // 7000407E
{0x0F12, 0x1840},    // 70004080
{0x0F12, 0x10C0},    // 70004082
{0x0F12, 0x8110},    // 70004084
{0x0F12, 0xE7E0},    // 70004086
{0x0F12, 0xB510},    // 70004088
{0x0F12, 0x000C},    // 7000408A
{0x0F12, 0x4919},    // 7000408C
{0x0F12, 0x2204},    // 7000408E
{0x0F12, 0x6820},    // 70004090
{0x0F12, 0x5E8A},    // 70004092
{0x0F12, 0x0140},    // 70004094
{0x0F12, 0x1A80},    // 70004096
{0x0F12, 0x0280},    // 70004098
{0x0F12, 0x8849},    // 7000409A
{0x0F12, 0xF000},    // 7000409C
{0x0F12, 0xFA6A},    // 7000409E
{0x0F12, 0x6020},    // 700040A0
{0x0F12, 0xE7D2},    // 700040A2
{0x0F12, 0x38D4},    // 700040A4
{0x0F12, 0x7000},    // 700040A6
{0x0F12, 0x17D0},    // 700040A8
{0x0F12, 0x7000},    // 700040AA
{0x0F12, 0x5000},    // 700040AC
{0x0F12, 0xD000},    // 700040AE
{0x0F12, 0x1100},    // 700040B0
{0x0F12, 0xD000},    // 700040B2
{0x0F12, 0x171A},    // 700040B4
{0x0F12, 0x7000},    // 700040B6
{0x0F12, 0x4780},    // 700040B8
{0x0F12, 0x7000},    // 700040BA
{0x0F12, 0x2FCA},    // 700040BC
{0x0F12, 0x7000},    // 700040BE
{0x0F12, 0x2FC5},    // 700040C0
{0x0F12, 0x7000},    // 700040C2
{0x0F12, 0x2FC6},    // 700040C4
{0x0F12, 0x7000},    // 700040C6
{0x0F12, 0x2ED8},    // 700040C8
{0x0F12, 0x7000},    // 700040CA
{0x0F12, 0x2BD0},    // 700040CC
{0x0F12, 0x7000},    // 700040CE
{0x0F12, 0x17E0},    // 700040D0
{0x0F12, 0x7000},    // 700040D2
{0x0F12, 0x2DE8},    // 700040D4
{0x0F12, 0x7000},    // 700040D6
{0x0F12, 0x37E0},    // 700040D8
{0x0F12, 0x7000},    // 700040DA
{0x0F12, 0x210C},    // 700040DC
{0x0F12, 0x7000},    // 700040DE
{0x0F12, 0x1484},    // 700040E0
{0x0F12, 0x7000},    // 700040E2
{0x0F12, 0xA006},    // 700040E4
{0x0F12, 0x0000},    // 700040E6
{0x0F12, 0x0724},    // 700040E8
{0x0F12, 0x7000},    // 700040EA
{0x0F12, 0xA000},    // 700040EC
{0x0F12, 0xD000},    // 700040EE
{0x0F12, 0x2270},    // 700040F0
{0x0F12, 0x7000},    // 700040F2
{0x0F12, 0x2558},    // 700040F4
{0x0F12, 0x7000},    // 700040F6
{0x0F12, 0x146C},    // 700040F8
{0x0F12, 0x7000},    // 700040FA
{0x0F12, 0xB510},    // 700040FC
{0x0F12, 0x000C},    // 700040FE
{0x0F12, 0x49C7},    // 70004100
{0x0F12, 0x2208},    // 70004102
{0x0F12, 0x6820},    // 70004104
{0x0F12, 0x5E8A},    // 70004106
{0x0F12, 0x0140},    // 70004108
{0x0F12, 0x1A80},    // 7000410A
{0x0F12, 0x0280},    // 7000410C
{0x0F12, 0x88C9},    // 7000410E
{0x0F12, 0xF000},    // 70004110
{0x0F12, 0xFA30},    // 70004112
{0x0F12, 0x6020},    // 70004114
{0x0F12, 0xE798},    // 70004116
{0x0F12, 0xB5FE},    // 70004118
{0x0F12, 0x000C},    // 7000411A
{0x0F12, 0x6825},    // 7000411C
{0x0F12, 0x6866},    // 7000411E
{0x0F12, 0x68A0},    // 70004120
{0x0F12, 0x9001},    // 70004122
{0x0F12, 0x68E7},    // 70004124
{0x0F12, 0x1BA8},    // 70004126
{0x0F12, 0x42B5},    // 70004128
{0x0F12, 0xDA00},    // 7000412A
{0x0F12, 0x1B70},    // 7000412C
{0x0F12, 0x9000},    // 7000412E
{0x0F12, 0x49BB},    // 70004130
{0x0F12, 0x48BC},    // 70004132
{0x0F12, 0x884A},    // 70004134
{0x0F12, 0x8843},    // 70004136
{0x0F12, 0x435A},    // 70004138
{0x0F12, 0x2304},    // 7000413A
{0x0F12, 0x5ECB},    // 7000413C
{0x0F12, 0x0A92},    // 7000413E
{0x0F12, 0x18D2},    // 70004140
{0x0F12, 0x02D2},    // 70004142
{0x0F12, 0x0C12},    // 70004144
{0x0F12, 0x88CB},    // 70004146
{0x0F12, 0x8880},    // 70004148
{0x0F12, 0x4343},    // 7000414A
{0x0F12, 0x0A98},    // 7000414C
{0x0F12, 0x2308},    // 7000414E
{0x0F12, 0x5ECB},    // 70004150
{0x0F12, 0x18C0},    // 70004152
{0x0F12, 0x02C0},    // 70004154
{0x0F12, 0x0C00},    // 70004156
{0x0F12, 0x0411},    // 70004158
{0x0F12, 0x0400},    // 7000415A
{0x0F12, 0x1409},    // 7000415C
{0x0F12, 0x1400},    // 7000415E
{0x0F12, 0x1A08},    // 70004160
{0x0F12, 0x49B0},    // 70004162
{0x0F12, 0x39E0},    // 70004164
{0x0F12, 0x6148},    // 70004166
{0x0F12, 0x9801},    // 70004168
{0x0F12, 0x3040},    // 7000416A
{0x0F12, 0x7880},    // 7000416C
{0x0F12, 0x2800},    // 7000416E
{0x0F12, 0xD103},    // 70004170
{0x0F12, 0x9801},    // 70004172
{0x0F12, 0x0029},    // 70004174
{0x0F12, 0xF000},    // 70004176
{0x0F12, 0xFA03},    // 70004178
{0x0F12, 0x8839},    // 7000417A
{0x0F12, 0x9800},    // 7000417C
{0x0F12, 0x4281},    // 7000417E
{0x0F12, 0xD814},    // 70004180
{0x0F12, 0x8879},    // 70004182
{0x0F12, 0x9800},    // 70004184
{0x0F12, 0x4281},    // 70004186
{0x0F12, 0xD20C},    // 70004188
{0x0F12, 0x9801},    // 7000418A
{0x0F12, 0x0029},    // 7000418C
{0x0F12, 0xF000},    // 7000418E
{0x0F12, 0xF9FF},    // 70004190
{0x0F12, 0x9801},    // 70004192
{0x0F12, 0x0029},    // 70004194
{0x0F12, 0xF000},    // 70004196
{0x0F12, 0xF9FB},    // 70004198
{0x0F12, 0x9801},    // 7000419A
{0x0F12, 0x0029},    // 7000419C
{0x0F12, 0xF000},    // 7000419E
{0x0F12, 0xF9F7},    // 700041A0
{0x0F12, 0xE003},    // 700041A2
{0x0F12, 0x9801},    // 700041A4
{0x0F12, 0x0029},    // 700041A6
{0x0F12, 0xF000},    // 700041A8
{0x0F12, 0xF9F2},    // 700041AA
{0x0F12, 0x9801},    // 700041AC
{0x0F12, 0x0032},    // 700041AE
{0x0F12, 0x0039},    // 700041B0
{0x0F12, 0xF000},    // 700041B2
{0x0F12, 0xF9F5},    // 700041B4
{0x0F12, 0x6020},    // 700041B6
{0x0F12, 0xE5D0},    // 700041B8
{0x0F12, 0xB57C},    // 700041BA
{0x0F12, 0x489A},    // 700041BC
{0x0F12, 0xA901},    // 700041BE
{0x0F12, 0x0004},    // 700041C0
{0x0F12, 0xF000},    // 700041C2
{0x0F12, 0xF979},    // 700041C4
{0x0F12, 0x466B},    // 700041C6
{0x0F12, 0x88D9},    // 700041C8
{0x0F12, 0x8898},    // 700041CA
{0x0F12, 0x4B95},    // 700041CC
{0x0F12, 0x3346},    // 700041CE
{0x0F12, 0x1E9A},    // 700041D0
{0x0F12, 0xF000},    // 700041D2
{0x0F12, 0xF9ED},    // 700041D4
{0x0F12, 0x4894},    // 700041D6
{0x0F12, 0x4992},    // 700041D8
{0x0F12, 0x3812},    // 700041DA
{0x0F12, 0x3140},    // 700041DC
{0x0F12, 0x8A42},    // 700041DE
{0x0F12, 0x888B},    // 700041E0
{0x0F12, 0x18D2},    // 700041E2
{0x0F12, 0x8242},    // 700041E4
{0x0F12, 0x8AC2},    // 700041E6
{0x0F12, 0x88C9},    // 700041E8
{0x0F12, 0x1851},    // 700041EA
{0x0F12, 0x82C1},    // 700041EC
{0x0F12, 0x0020},    // 700041EE
{0x0F12, 0x4669},    // 700041F0
{0x0F12, 0xF000},    // 700041F2
{0x0F12, 0xF961},    // 700041F4
{0x0F12, 0x488D},    // 700041F6
{0x0F12, 0x214D},    // 700041F8
{0x0F12, 0x8301},    // 700041FA
{0x0F12, 0x2196},    // 700041FC
{0x0F12, 0x8381},    // 700041FE
{0x0F12, 0x211D},    // 70004200
{0x0F12, 0x3020},    // 70004202
{0x0F12, 0x8001},    // 70004204
{0x0F12, 0xF000},    // 70004206
{0x0F12, 0xF9DB},    // 70004208
{0x0F12, 0xF000},    // 7000420A
{0x0F12, 0xF9E1},    // 7000420C
{0x0F12, 0x4888},    // 7000420E
{0x0F12, 0x4C88},    // 70004210
{0x0F12, 0x6E00},    // 70004212
{0x0F12, 0x60E0},    // 70004214
{0x0F12, 0x466B},    // 70004216
{0x0F12, 0x8818},    // 70004218
{0x0F12, 0x8859},    // 7000421A
{0x0F12, 0x0025},    // 7000421C
{0x0F12, 0x1A40},    // 7000421E
{0x0F12, 0x3540},    // 70004220
{0x0F12, 0x61A8},    // 70004222
{0x0F12, 0x487F},    // 70004224
{0x0F12, 0x9900},    // 70004226
{0x0F12, 0x3060},    // 70004228
{0x0F12, 0xF000},    // 7000422A
{0x0F12, 0xF9D9},    // 7000422C
{0x0F12, 0x466B},    // 7000422E
{0x0F12, 0x8819},    // 70004230
{0x0F12, 0x1DE0},    // 70004232
{0x0F12, 0x30F9},    // 70004234
{0x0F12, 0x8741},    // 70004236
{0x0F12, 0x8859},    // 70004238
{0x0F12, 0x8781},    // 7000423A
{0x0F12, 0x2000},    // 7000423C
{0x0F12, 0x71A0},    // 7000423E
{0x0F12, 0x74A8},    // 70004240
{0x0F12, 0xBC7C},    // 70004242
{0x0F12, 0xBC08},    // 70004244
{0x0F12, 0x4718},    // 70004246
{0x0F12, 0xB5F8},    // 70004248
{0x0F12, 0x0005},    // 7000424A
{0x0F12, 0x6808},    // 7000424C
{0x0F12, 0x0400},    // 7000424E
{0x0F12, 0x0C00},    // 70004250
{0x0F12, 0x684A},    // 70004252
{0x0F12, 0x0412},    // 70004254
{0x0F12, 0x0C12},    // 70004256
{0x0F12, 0x688E},    // 70004258
{0x0F12, 0x68CC},    // 7000425A
{0x0F12, 0x4970},    // 7000425C
{0x0F12, 0x884B},    // 7000425E
{0x0F12, 0x4343},    // 70004260
{0x0F12, 0x0A98},    // 70004262
{0x0F12, 0x2304},    // 70004264
{0x0F12, 0x5ECB},    // 70004266
{0x0F12, 0x18C0},    // 70004268
{0x0F12, 0x02C0},    // 7000426A
{0x0F12, 0x0C00},    // 7000426C
{0x0F12, 0x88CB},    // 7000426E
{0x0F12, 0x4353},    // 70004270
{0x0F12, 0x0A9A},    // 70004272
{0x0F12, 0x2308},    // 70004274
{0x0F12, 0x5ECB},    // 70004276
{0x0F12, 0x18D1},    // 70004278
{0x0F12, 0x02C9},    // 7000427A
{0x0F12, 0x0C09},    // 7000427C
{0x0F12, 0x2701},    // 7000427E
{0x0F12, 0x003A},    // 70004280
{0x0F12, 0x40AA},    // 70004282
{0x0F12, 0x9200},    // 70004284
{0x0F12, 0x002A},    // 70004286
{0x0F12, 0x3A10},    // 70004288
{0x0F12, 0x4097},    // 7000428A
{0x0F12, 0x2D10},    // 7000428C
{0x0F12, 0xDA06},    // 7000428E
{0x0F12, 0x4A69},    // 70004290
{0x0F12, 0x9B00},    // 70004292
{0x0F12, 0x8812},    // 70004294
{0x0F12, 0x439A},    // 70004296
{0x0F12, 0x4B67},    // 70004298
{0x0F12, 0x801A},    // 7000429A
{0x0F12, 0xE003},    // 7000429C
{0x0F12, 0x4B66},    // 7000429E
{0x0F12, 0x885A},    // 700042A0
{0x0F12, 0x43BA},    // 700042A2
{0x0F12, 0x805A},    // 700042A4
{0x0F12, 0x0023},    // 700042A6
{0x0F12, 0x0032},    // 700042A8
{0x0F12, 0xF000},    // 700042AA
{0x0F12, 0xF981},    // 700042AC
{0x0F12, 0x2D10},    // 700042AE
{0x0F12, 0xDA05},    // 700042B0
{0x0F12, 0x4961},    // 700042B2
{0x0F12, 0x9A00},    // 700042B4
{0x0F12, 0x8808},    // 700042B6
{0x0F12, 0x4310},    // 700042B8
{0x0F12, 0x8008},    // 700042BA
{0x0F12, 0xE003},    // 700042BC
{0x0F12, 0x485E},    // 700042BE
{0x0F12, 0x8841},    // 700042C0
{0x0F12, 0x4339},    // 700042C2
{0x0F12, 0x8041},    // 700042C4
{0x0F12, 0x4D5B},    // 700042C6
{0x0F12, 0x2000},    // 700042C8
{0x0F12, 0x3580},    // 700042CA
{0x0F12, 0x88AA},    // 700042CC
{0x0F12, 0x5E30},    // 700042CE
{0x0F12, 0x2100},    // 700042D0
{0x0F12, 0xF000},    // 700042D2
{0x0F12, 0xF98D},    // 700042D4
{0x0F12, 0x8030},    // 700042D6
{0x0F12, 0x2000},    // 700042D8
{0x0F12, 0x88AA},    // 700042DA
{0x0F12, 0x5E20},    // 700042DC
{0x0F12, 0x2100},    // 700042DE
{0x0F12, 0xF000},    // 700042E0
{0x0F12, 0xF986},    // 700042E2
{0x0F12, 0x8020},    // 700042E4
{0x0F12, 0xE587},    // 700042E6
{0x0F12, 0xB510},    // 700042E8
{0x0F12, 0xF000},    // 700042EA
{0x0F12, 0xF989},    // 700042EC
{0x0F12, 0x4A53},    // 700042EE
{0x0F12, 0x8D50},    // 700042F0
{0x0F12, 0x2800},    // 700042F2
{0x0F12, 0xD007},    // 700042F4
{0x0F12, 0x494E},    // 700042F6
{0x0F12, 0x31C0},    // 700042F8
{0x0F12, 0x684B},    // 700042FA
{0x0F12, 0x4950},    // 700042FC
{0x0F12, 0x4283},    // 700042FE
{0x0F12, 0xD202},    // 70004300
{0x0F12, 0x8D90},    // 70004302
{0x0F12, 0x81C8},    // 70004304
{0x0F12, 0xE6A0},    // 70004306
{0x0F12, 0x8DD0},    // 70004308
{0x0F12, 0x81C8},    // 7000430A
{0x0F12, 0xE69D},    // 7000430C
{0x0F12, 0xB5F8},    // 7000430E
{0x0F12, 0xF000},    // 70004310
{0x0F12, 0xF97E},    // 70004312
{0x0F12, 0x4D49},    // 70004314
{0x0F12, 0x8E28},    // 70004316
{0x0F12, 0x2800},    // 70004318
{0x0F12, 0xD01F},    // 7000431A
{0x0F12, 0x4E49},    // 7000431C
{0x0F12, 0x4844},    // 7000431E
{0x0F12, 0x68B4},    // 70004320
{0x0F12, 0x6800},    // 70004322
{0x0F12, 0x4284},    // 70004324
{0x0F12, 0xD903},    // 70004326
{0x0F12, 0x1A21},    // 70004328
{0x0F12, 0x0849},    // 7000432A
{0x0F12, 0x1847},    // 7000432C
{0x0F12, 0xE006},    // 7000432E
{0x0F12, 0x4284},    // 70004330
{0x0F12, 0xD203},    // 70004332
{0x0F12, 0x1B01},    // 70004334
{0x0F12, 0x0849},    // 70004336
{0x0F12, 0x1A47},    // 70004338
{0x0F12, 0xE000},    // 7000433A
{0x0F12, 0x0027},    // 7000433C
{0x0F12, 0x0020},    // 7000433E
{0x0F12, 0x493B},    // 70004340
{0x0F12, 0x3120},    // 70004342
{0x0F12, 0x7A0C},    // 70004344
{0x0F12, 0x2C00},    // 70004346
{0x0F12, 0xD004},    // 70004348
{0x0F12, 0x0200},    // 7000434A
{0x0F12, 0x0039},    // 7000434C
{0x0F12, 0xF000},    // 7000434E
{0x0F12, 0xF8C3},    // 70004350
{0x0F12, 0x8668},    // 70004352
{0x0F12, 0x2C00},    // 70004354
{0x0F12, 0xD000},    // 70004356
{0x0F12, 0x60B7},    // 70004358
{0x0F12, 0xE54D},    // 7000435A
{0x0F12, 0x20FF},    // 7000435C
{0x0F12, 0x1C40},    // 7000435E
{0x0F12, 0x8668},    // 70004360
{0x0F12, 0xE549},    // 70004362
{0x0F12, 0xB510},    // 70004364
{0x0F12, 0x000C},    // 70004366
{0x0F12, 0x6820},    // 70004368
{0x0F12, 0x0400},    // 7000436A
{0x0F12, 0x0C00},    // 7000436C
{0x0F12, 0x4933},    // 7000436E
{0x0F12, 0x8E0A},    // 70004370
{0x0F12, 0x2A00},    // 70004372
{0x0F12, 0xD003},    // 70004374
{0x0F12, 0x8E49},    // 70004376
{0x0F12, 0x0200},    // 70004378
{0x0F12, 0xF000},    // 7000437A
{0x0F12, 0xF8AD},    // 7000437C
{0x0F12, 0x6020},    // 7000437E
{0x0F12, 0x0400},    // 70004380
{0x0F12, 0x0C00},    // 70004382
{0x0F12, 0xE661},    // 70004384
{0x0F12, 0xB570},    // 70004386
{0x0F12, 0x680C},    // 70004388
{0x0F12, 0x4D2F},    // 7000438A
{0x0F12, 0x0020},    // 7000438C
{0x0F12, 0x6F29},    // 7000438E
{0x0F12, 0xF000},    // 70004390
{0x0F12, 0xF946},    // 70004392
{0x0F12, 0x6F69},    // 70004394
{0x0F12, 0x1D20},    // 70004396
{0x0F12, 0xF000},    // 70004398
{0x0F12, 0xF942},    // 7000439A
{0x0F12, 0x4827},    // 7000439C
{0x0F12, 0x8E00},    // 7000439E
{0x0F12, 0x2800},    // 700043A0
{0x0F12, 0xD006},    // 700043A2
{0x0F12, 0x4922},    // 700043A4
{0x0F12, 0x2214},    // 700043A6
{0x0F12, 0x3168},    // 700043A8
{0x0F12, 0x0008},    // 700043AA
{0x0F12, 0x383C},    // 700043AC
{0x0F12, 0xF000},    // 700043AE
{0x0F12, 0xF93F},    // 700043B0
{0x0F12, 0xE488},    // 700043B2
{0x0F12, 0xB5F8},    // 700043B4
{0x0F12, 0x0004},    // 700043B6
{0x0F12, 0x4D24},    // 700043B8
{0x0F12, 0x8B68},    // 700043BA
{0x0F12, 0x2800},    // 700043BC
{0x0F12, 0xD012},    // 700043BE
{0x0F12, 0x4823},    // 700043C0
{0x0F12, 0x8A00},    // 700043C2
{0x0F12, 0x06C0},    // 700043C4
{0x0F12, 0xD50E},    // 700043C6
{0x0F12, 0x4822},    // 700043C8
{0x0F12, 0x7800},    // 700043CA
{0x0F12, 0x2800},    // 700043CC
{0x0F12, 0xD00A},    // 700043CE
{0x0F12, 0x481D},    // 700043D0
{0x0F12, 0x6FC1},    // 700043D2
{0x0F12, 0x2000},    // 700043D4
{0x0F12, 0xF000},    // 700043D6
{0x0F12, 0xF923},    // 700043D8
{0x0F12, 0x8B28},    // 700043DA
{0x0F12, 0x2201},    // 700043DC
{0x0F12, 0x2180},    // 700043DE
{0x0F12, 0xF000},    // 700043E0
{0x0F12, 0xF92C},    // 700043E2
{0x0F12, 0x8328},    // 700043E4
{0x0F12, 0x2101},    // 700043E6
{0x0F12, 0x000D},    // 700043E8
{0x0F12, 0x0020},    // 700043EA
{0x0F12, 0x3810},    // 700043EC
{0x0F12, 0x4081},    // 700043EE
{0x0F12, 0x40A5},    // 700043F0
{0x0F12, 0x4F11},    // 700043F2
{0x0F12, 0x000E},    // 700043F4
{0x0F12, 0x2C10},    // 700043F6
{0x0F12, 0xDA03},    // 700043F8
{0x0F12, 0x8838},    // 700043FA
{0x0F12, 0x43A8},    // 700043FC
{0x0F12, 0x8038},    // 700043FE
{0x0F12, 0xE002},    // 70004400
{0x0F12, 0x8878},    // 70004402
{0x0F12, 0x43B0},    // 70004404
{0x0F12, 0x8078},    // 70004406
{0x0F12, 0xF000},    // 70004408
{0x0F12, 0xF920},    // 7000440A
{0x0F12, 0x2C10},    // 7000440C
{0x0F12, 0xDA03},    // 7000440E
{0x0F12, 0x8838},    // 70004410
{0x0F12, 0x4328},    // 70004412
{0x0F12, 0x8038},    // 70004414
{0x0F12, 0xE4EF},    // 70004416
{0x0F12, 0x8878},    // 70004418
{0x0F12, 0x4330},    // 7000441A
{0x0F12, 0x8078},    // 7000441C
{0x0F12, 0xE4EB},    // 7000441E
{0x0F12, 0x2558},    // 70004420
{0x0F12, 0x7000},    // 70004422
{0x0F12, 0x2AB8},    // 70004424
{0x0F12, 0x7000},    // 70004426
{0x0F12, 0x145E},    // 70004428
{0x0F12, 0x7000},    // 7000442A
{0x0F12, 0x2698},    // 7000442C
{0x0F12, 0x7000},    // 7000442E
{0x0F12, 0x2BB8},    // 70004430
{0x0F12, 0x7000},    // 70004432
{0x0F12, 0x2998},    // 70004434
{0x0F12, 0x7000},    // 70004436
{0x0F12, 0x1100},    // 70004438
{0x0F12, 0xD000},    // 7000443A
{0x0F12, 0x4780},    // 7000443C
{0x0F12, 0x7000},    // 7000443E
{0x0F12, 0xE200},    // 70004440
{0x0F12, 0xD000},    // 70004442
{0x0F12, 0x210C},    // 70004444
{0x0F12, 0x7000},    // 70004446
{0x0F12, 0x0000},    // 70004448
{0x0F12, 0x7000},    // 7000444A
{0x0F12, 0x308C},    // 7000444C
{0x0F12, 0x7000},    // 7000444E
{0x0F12, 0xB040},    // 70004450
{0x0F12, 0xD000},    // 70004452
{0x0F12, 0x3858},    // 70004454
{0x0F12, 0x7000},    // 70004456
{0x0F12, 0x4778},    // 70004458
{0x0F12, 0x46C0},    // 7000445A
{0x0F12, 0xC000},    // 7000445C
{0x0F12, 0xE59F},    // 7000445E
{0x0F12, 0xFF1C},    // 70004460
{0x0F12, 0xE12F},    // 70004462
{0x0F12, 0x1789},    // 70004464
{0x0F12, 0x0001},    // 70004466
{0x0F12, 0x4778},    // 70004468
{0x0F12, 0x46C0},    // 7000446A
{0x0F12, 0xC000},    // 7000446C
{0x0F12, 0xE59F},    // 7000446E
{0x0F12, 0xFF1C},    // 70004470
{0x0F12, 0xE12F},    // 70004472
{0x0F12, 0x16F1},    // 70004474
{0x0F12, 0x0001},    // 70004476
{0x0F12, 0x4778},    // 70004478
{0x0F12, 0x46C0},    // 7000447A
{0x0F12, 0xC000},    // 7000447C
{0x0F12, 0xE59F},    // 7000447E
{0x0F12, 0xFF1C},    // 70004480
{0x0F12, 0xE12F},    // 70004482
{0x0F12, 0xC3B1},    // 70004484
{0x0F12, 0x0000},    // 70004486
{0x0F12, 0x4778},    // 70004488
{0x0F12, 0x46C0},    // 7000448A
{0x0F12, 0xC000},    // 7000448C
{0x0F12, 0xE59F},    // 7000448E
{0x0F12, 0xFF1C},    // 70004490
{0x0F12, 0xE12F},    // 70004492
{0x0F12, 0xC36D},    // 70004494
{0x0F12, 0x0000},    // 70004496
{0x0F12, 0x4778},    // 70004498
{0x0F12, 0x46C0},    // 7000449A
{0x0F12, 0xC000},    // 7000449C
{0x0F12, 0xE59F},    // 7000449E
{0x0F12, 0xFF1C},    // 700044A0
{0x0F12, 0xE12F},    // 700044A2
{0x0F12, 0xF6D7},    // 700044A4
{0x0F12, 0x0000},    // 700044A6
{0x0F12, 0x4778},    // 700044A8
{0x0F12, 0x46C0},    // 700044AA
{0x0F12, 0xC000},    // 700044AC
{0x0F12, 0xE59F},    // 700044AE
{0x0F12, 0xFF1C},    // 700044B0
{0x0F12, 0xE12F},    // 700044B2
{0x0F12, 0xB49D},    // 700044B4
{0x0F12, 0x0000},    // 700044B6
{0x0F12, 0x4778},    // 700044B8
{0x0F12, 0x46C0},    // 700044BA
{0x0F12, 0xC000},    // 700044BC
{0x0F12, 0xE59F},    // 700044BE
{0x0F12, 0xFF1C},    // 700044C0
{0x0F12, 0xE12F},    // 700044C2
{0x0F12, 0x7EDF},    // 700044C4
{0x0F12, 0x0000},    // 700044C6
{0x0F12, 0x4778},    // 700044C8
{0x0F12, 0x46C0},    // 700044CA
{0x0F12, 0xC000},    // 700044CC
{0x0F12, 0xE59F},    // 700044CE
{0x0F12, 0xFF1C},    // 700044D0
{0x0F12, 0xE12F},    // 700044D2
{0x0F12, 0x448D},    // 700044D4
{0x0F12, 0x0000},    // 700044D6
{0x0F12, 0x4778},    // 700044D8
{0x0F12, 0x46C0},    // 700044DA
{0x0F12, 0xF004},    // 700044DC
{0x0F12, 0xE51F},    // 700044DE
{0x0F12, 0x29EC},    // 700044E0
{0x0F12, 0x0001},    // 700044E2
{0x0F12, 0x4778},    // 700044E4
{0x0F12, 0x46C0},    // 700044E6
{0x0F12, 0xC000},    // 700044E8
{0x0F12, 0xE59F},    // 700044EA
{0x0F12, 0xFF1C},    // 700044EC
{0x0F12, 0xE12F},    // 700044EE
{0x0F12, 0x2EF1},    // 700044F0
{0x0F12, 0x0000},    // 700044F2
{0x0F12, 0x4778},    // 700044F4
{0x0F12, 0x46C0},    // 700044F6
{0x0F12, 0xC000},    // 700044F8
{0x0F12, 0xE59F},    // 700044FA
{0x0F12, 0xFF1C},    // 700044FC
{0x0F12, 0xE12F},    // 700044FE
{0x0F12, 0xEE03},    // 70004500
{0x0F12, 0x0000},    // 70004502
{0x0F12, 0x4778},    // 70004504
{0x0F12, 0x46C0},    // 70004506
{0x0F12, 0xC000},    // 70004508
{0x0F12, 0xE59F},    // 7000450A
{0x0F12, 0xFF1C},    // 7000450C
{0x0F12, 0xE12F},    // 7000450E
{0x0F12, 0xA58B},    // 70004510
{0x0F12, 0x0000},    // 70004512
{0x0F12, 0x4778},    // 70004514
{0x0F12, 0x46C0},    // 70004516
{0x0F12, 0xC000},    // 70004518
{0x0F12, 0xE59F},    // 7000451A
{0x0F12, 0xFF1C},    // 7000451C
{0x0F12, 0xE12F},    // 7000451E
{0x0F12, 0x7C49},    // 70004520
{0x0F12, 0x0000},    // 70004522
{0x0F12, 0x4778},    // 70004524
{0x0F12, 0x46C0},    // 70004526
{0x0F12, 0xC000},    // 70004528
{0x0F12, 0xE59F},    // 7000452A
{0x0F12, 0xFF1C},    // 7000452C
{0x0F12, 0xE12F},    // 7000452E
{0x0F12, 0x7C63},    // 70004530
{0x0F12, 0x0000},    // 70004532
{0x0F12, 0x4778},    // 70004534
{0x0F12, 0x46C0},    // 70004536
{0x0F12, 0xC000},    // 70004538
{0x0F12, 0xE59F},    // 7000453A
{0x0F12, 0xFF1C},    // 7000453C
{0x0F12, 0xE12F},    // 7000453E
{0x0F12, 0x2DB7},    // 70004540
{0x0F12, 0x0000},    // 70004542
{0x0F12, 0x4778},    // 70004544
{0x0F12, 0x46C0},    // 70004546
{0x0F12, 0xC000},    // 70004548
{0x0F12, 0xE59F},    // 7000454A
{0x0F12, 0xFF1C},    // 7000454C
{0x0F12, 0xE12F},    // 7000454E
{0x0F12, 0xEB3D},    // 70004550
{0x0F12, 0x0000},    // 70004552
{0x0F12, 0x4778},    // 70004554
{0x0F12, 0x46C0},    // 70004556
{0x0F12, 0xC000},    // 70004558
{0x0F12, 0xE59F},    // 7000455A
{0x0F12, 0xFF1C},    // 7000455C
{0x0F12, 0xE12F},    // 7000455E
{0x0F12, 0xF061},    // 70004560
{0x0F12, 0x0000},    // 70004562
{0x0F12, 0x4778},    // 70004564
{0x0F12, 0x46C0},    // 70004566
{0x0F12, 0xC000},    // 70004568
{0x0F12, 0xE59F},    // 7000456A
{0x0F12, 0xFF1C},    // 7000456C
{0x0F12, 0xE12F},    // 7000456E
{0x0F12, 0xF0EF},    // 70004570
{0x0F12, 0x0000},    // 70004572
{0x0F12, 0x4778},    // 70004574
{0x0F12, 0x46C0},    // 70004576
{0x0F12, 0xF004},    // 70004578
{0x0F12, 0xE51F},    // 7000457A
{0x0F12, 0x2824},    // 7000457C
{0x0F12, 0x0001},    // 7000457E
{0x0F12, 0x4778},    // 70004580
{0x0F12, 0x46C0},    // 70004582
{0x0F12, 0xC000},    // 70004584
{0x0F12, 0xE59F},    // 70004586
{0x0F12, 0xFF1C},    // 70004588
{0x0F12, 0xE12F},    // 7000458A
{0x0F12, 0x8EDD},    // 7000458C
{0x0F12, 0x0000},    // 7000458E
{0x0F12, 0x4778},    // 70004590
{0x0F12, 0x46C0},    // 70004592
{0x0F12, 0xC000},    // 70004594
{0x0F12, 0xE59F},    // 70004596
{0x0F12, 0xFF1C},    // 70004598
{0x0F12, 0xE12F},    // 7000459A
{0x0F12, 0x8DCB},    // 7000459C
{0x0F12, 0x0000},    // 7000459E
{0x0F12, 0x4778},    // 700045A0
{0x0F12, 0x46C0},    // 700045A2
{0x0F12, 0xC000},    // 700045A4
{0x0F12, 0xE59F},    // 700045A6
{0x0F12, 0xFF1C},    // 700045A8
{0x0F12, 0xE12F},    // 700045AA
{0x0F12, 0x8E17},    // 700045AC
{0x0F12, 0x0000},    // 700045AE
{0x0F12, 0x4778},    // 700045B0
{0x0F12, 0x46C0},    // 700045B2
{0x0F12, 0xC000},    // 700045B4
{0x0F12, 0xE59F},    // 700045B6
{0x0F12, 0xFF1C},    // 700045B8
{0x0F12, 0xE12F},    // 700045BA
{0x0F12, 0x98C5},    // 700045BC
{0x0F12, 0x0000},    // 700045BE
{0x0F12, 0x4778},    // 700045C0
{0x0F12, 0x46C0},    // 700045C2
{0x0F12, 0xC000},    // 700045C4
{0x0F12, 0xE59F},    // 700045C6
{0x0F12, 0xFF1C},    // 700045C8
{0x0F12, 0xE12F},    // 700045CA
{0x0F12, 0x7C7D},    // 700045CC
{0x0F12, 0x0000},    // 700045CE
{0x0F12, 0x4778},    // 700045D0
{0x0F12, 0x46C0},    // 700045D2
{0x0F12, 0xC000},    // 700045D4
{0x0F12, 0xE59F},    // 700045D6
{0x0F12, 0xFF1C},    // 700045D8
{0x0F12, 0xE12F},    // 700045DA
{0x0F12, 0x7E31},    // 700045DC
{0x0F12, 0x0000},    // 700045DE
{0x0F12, 0x4778},    // 700045E0
{0x0F12, 0x46C0},    // 700045E2
{0x0F12, 0xC000},    // 700045E4
{0x0F12, 0xE59F},    // 700045E6
{0x0F12, 0xFF1C},    // 700045E8
{0x0F12, 0xE12F},    // 700045EA
{0x0F12, 0x7EAB},    // 700045EC
{0x0F12, 0x0000},    // 700045EE
{0x0F12, 0x4778},    // 700045F0
{0x0F12, 0x46C0},    // 700045F2
{0x0F12, 0xC000},    // 700045F4
{0x0F12, 0xE59F},    // 700045F6
{0x0F12, 0xFF1C},    // 700045F8
{0x0F12, 0xE12F},    // 700045FA
{0x0F12, 0x7501},    // 700045FC
{0x0F12, 0x0000},    // 700045FE
{0x0F12, 0x4778},    // 70004600
{0x0F12, 0x46C0},    // 70004602
{0x0F12, 0xC000},    // 70004604
{0x0F12, 0xE59F},    // 70004606
{0x0F12, 0xFF1C},    // 70004608
{0x0F12, 0xE12F},    // 7000460A
{0x0F12, 0xF63F},    // 7000460C
{0x0F12, 0x0000},    // 7000460E
{0x0F12, 0x4778},    // 70004610
{0x0F12, 0x46C0},    // 70004612
{0x0F12, 0xC000},    // 70004614
{0x0F12, 0xE59F},    // 70004616
{0x0F12, 0xFF1C},    // 70004618
{0x0F12, 0xE12F},    // 7000461A
{0x0F12, 0x3D0B},    // 7000461C
{0x0F12, 0x0000},    // 7000461E
{0x0F12, 0x4778},    // 70004620
{0x0F12, 0x46C0},    // 70004622
{0x0F12, 0xC000},    // 70004624
{0x0F12, 0xE59F},    // 70004626
{0x0F12, 0xFF1C},    // 70004628
{0x0F12, 0xE12F},    // 7000462A
{0x0F12, 0x29BF},    // 7000462C
{0x0F12, 0x0001},    // 7000462E
{0x0F12, 0x4778},    // 70004630
{0x0F12, 0x46C0},    // 70004632
{0x0F12, 0xF004},    // 70004634
{0x0F12, 0xE51F},    // 70004636
{0x0F12, 0x26D8},    // 70004638
{0x0F12, 0x0001},    // 7000463A
{0x0F12, 0x4778},    // 7000463C
{0x0F12, 0x46C0},    // 7000463E
{0x0F12, 0xC000},    // 70004640
{0x0F12, 0xE59F},    // 70004642
{0x0F12, 0xFF1C},    // 70004644
{0x0F12, 0xE12F},    // 70004646
{0x0F12, 0x306B},    // 70004648
{0x0F12, 0x0000},    // 7000464A
{0x0F12, 0x4778},    // 7000464C
{0x0F12, 0x46C0},    // 7000464E
{0x0F12, 0xC000},    // 70004650
{0x0F12, 0xE59F},    // 70004652
{0x0F12, 0xFF1C},    // 70004654
{0x0F12, 0xE12F},    // 70004656
{0x0F12, 0x6099},    // 70004658
{0x0F12, 0x0000},    // 7000465A
// End of Patch Data(Last : 7000465Ah)
// Total Size 2916 (0x0B64)
// Addr : 3AF8 , Size : 2914(B62h)

//TNP_USER_MBCV_CONTROL
//TNP_4EC_MBR_TUNE
//TNP_4EC_FORBIDDEN_TUNE
//TNP_AF_FINESEARCH_DRIVEBACK
//TNP_FLASH_ALG
//TNP_GAS_ALPHA_OTP
//TNP_AWB_MODUL_COMP
//TNP_AWB_INIT_QUEUE
//TNP_AWB_GRID_LOWBR
// TNP_AWB_GRID_MODULECOMP
// TNP_ADLC_TUNE
// TNP_1FRAME_AE
// TNP_TG_OFF_CFG_CHG_IN_SPOOF_MODE


//==================================================================================
// 08.AF Setting
//==================================================================================

//AF interface setting	
{0x0028, 0x7000},
{0x002A, 0x01FC},
{0x0F12, 0x0001},	//REG_TC_IPRM_LedGpio, for Flash control           
//{0x002A, 0x1720},	                                                    
//{0x0F12, 0x0100},	//afd_usFlags, Low voltage AF enable               
{0x002A, 0x01FE},
{0x0F12, 0x0003},	//REG_TC_IPRM_CM_Init_AfModeType, VCM IIC          
{0x0F12, 0x0000},	//REG_TC_IPRM_CM_Init_PwmConfig1                   
{0x002A, 0x0204},
{0x0F12, 0x0061},	//REG_TC_IPRM_CM_Init_GpioConfig1, AF Enable GPIO 6
{0x002A, 0x020C},
{0x0F12, 0x2F0C},	//REG_TC_IPRM_CM_Init_Mi2cBit                      
{0x0F12, 0x0190},	//REG_TC_IPRM_CM_Init_Mi2cRateKhz, IIC Speed       
	
	
//AF Window Settings	
{0x002A, 0x0294},
{0x0F12, 0x0100},	//REG_TC_AF_FstWinStartX   
{0x0F12, 0x00E3},	//REG_TC_AF_FstWinStartY   
{0x0F12, 0x0200},	//REG_TC_AF_FstWinSizeX    
{0x0F12, 0x0238},	//REG_TC_AF_FstWinSizeY    
{0x0F12, 0x018C},	//REG_TC_AF_ScndWinStartX  
{0x0F12, 0x0166},	//REG_TC_AF_ScndWinStartY  
{0x0F12, 0x00E6},	//REG_TC_AF_ScndWinSizeX   
{0x0F12, 0x0132},	//REG_TC_AF_ScndWinSizeY   
{0x0F12, 0x0001},	//REG_TC_AF_WinSizesUpdated
	

//2nd search setting	
{0x002A, 0x070E},
{0x0F12, 0x00C0},	//skl_af_StatOvlpExpFactor 
{0x002A, 0x071E},
{0x0F12, 0x0000},	//skl_af_bAfStatOff        
{0x002A, 0x163C},
{0x0F12, 0x0000},	//af_search_usAeStable     
{0x002A, 0x1648},
{0x0F12, 0x9002},	//af_search_usSingleAfFlags
{0x002A, 0x1652},
{0x0F12, 0x0002},	//af_search_usFinePeakCount
{0x0F12, 0x0000},	//af_search_usFineMaxScale 
{0x002A, 0x15E0},
{0x0F12, 0x0403},	//af_pos_usFineStepNumSize 
{0x002A, 0x1656},	                            
{0x0F12, 0x0000},	//af_search_usCapturePolicy
	

//Peak Threshold	
{0x002A, 0x164C},
{0x0F12, 0x0003},	//af_search_usMinPeakSamples  
{0x002A, 0x163E},
{0x0F12, 0x00C0},	//af_search_usPeakThr         
{0x0F12, 0x0080},	//af_search_usPeakThrLow      
{0x002A, 0x47A8},	                               
{0x0F12, 0x0080},	//TNP, Macro Threshold register
	
	
//Home Pos	
{0x002A, 0x15D4},
{0x0F12, 0x0000},	//af_pos_usHomePos   
{0x0F12, 0xD000},	//af_pos_usLowConfPos
	
	
//AF statistics	
{0x002A, 0x169A},
{0x0F12, 0xFF95}, 	//af_search_usConfCheckOrder_1_
{0x002A, 0x166A},
{0x0F12, 0x0280}, 	//af_search_usConfThr_4_       
{0x002A, 0x1676},
{0x0F12, 0x03A0}, 	//af_search_usConfThr_10_      
{0x0F12, 0x0320}, 	//af_search_usConfThr_11_      
{0x002A, 0x16BC},
{0x0F12, 0x0030}, 	//af_stat_usMinStatVal         
{0x002A, 0x16E0},
{0x0F12, 0x0060}, 	//af_scene_usSceneLowNormBrThr 
{0x002A, 0x16D4},
{0x0F12, 0x0010}, 	//af_stat_usBpfThresh          
	
	
//AF Lens Position Table Settings
{0x002A, 0x15E8}, //af_pos_usTableLastInd
{0x0F12, 0x0017}, //af_pos_usTable       
{0x0F12, 0x0026}, //af_pos_usTable       
{0x0F12, 0x002C}, //af_pos_usTable       
{0x0F12, 0x0032}, //af_pos_usTable       
{0x0F12, 0x0038}, //af_pos_usTable       
{0x0F12, 0x003E}, //af_pos_usTable       
{0x0F12, 0x0044}, //af_pos_usTable       
{0x0F12, 0x004A}, //af_pos_usTable       
{0x0F12, 0x0050}, //af_pos_usTable       
{0x0F12, 0x0056}, //af_pos_usTable       
{0x0F12, 0x005C}, //af_pos_usTable       
{0x0F12, 0x0062}, //af_pos_usTable       
{0x0F12, 0x0068}, //af_pos_usTable       
{0x0F12, 0x006E}, //af_pos_usTable       
{0x0F12, 0x0074}, //af_pos_usTable       
{0x0F12, 0x007A}, //af_pos_usTable       
{0x0F12, 0x0080}, //af_pos_usTable       
{0x0F12, 0x0086}, //af_pos_usTable 
{0x0F12, 0x008C}, //af_pos_usTable 
{0x0F12, 0x0092}, //af_pos_usTable 
{0x0F12, 0x0098}, //af_pos_usTable 
{0x0F12, 0x009E}, //af_pos_usTable 
{0x0F12, 0x00A4}, //af_pos_usTable 
{0x0F12, 0x00AA}, //af_pos_usTable 
{0x0F12, 0x00B0}, //af_pos_usTable 
	

//VCM AF driver with PWM/I2C	
{0x002A, 0x1722},
{0x0F12, 0x8000},	//afd_usParam[0] I2C power down command                          
{0x0F12, 0x0006},	//afd_usParam[1] Position Right Shift                            
{0x0F12, 0x3FF0},	//afd_usParam[2] I2C Data Mask                                   
{0x0F12, 0x03E8},	//afd_usParam[3] PWM Period                                      
{0x0F12, 0x0000},	//afd_usParam[4] PWM Divider                                     
{0x0F12, 0x0020},	//afd_usParam[5] SlowMotion Delay 4. reduce lens collision noise.
{0x0F12, 0x0010},	//afd_usParam[6] SlowMotion Threshold                            
{0x0F12, 0x0008},	//afd_usParam[7] Signal Shaping                                  
{0x0F12, 0x0040},	//afd_usParam[8] Signal Shaping level                            
{0x0F12, 0x0080},	//afd_usParam[9] Signal Shaping level                            
{0x0F12, 0x00C0},	//afd_usParam[10] Signal Shaping level                           
{0x0F12, 0x00E0},	//afd_usParam[11] Signal Shaping level                           

{0x002A, 0x028C},
{0x0F12, 0x0003},	//REG_TC_AF_AfCmd


//==================================================================================
// 06.Gas_Anti Shading
//==================================================================================
{0x002A, 0x08B4},
{0x0F12, 0x0001},	//wbt_bUseOutdoorASH

// Refer Mon_AWB_RotGain
{0x0028, 0x7000},         	


{0x002A, 0x08BC},
{0x0F12, 0x00C0},	//TVAR_ash_AwbAshCord_0_ 2300K	
{0x0F12, 0x00DF},	//TVAR_ash_AwbAshCord_1_ 2750K	
{0x0F12, 0x0100},	//TVAR_ash_AwbAshCord_2_ 3300K	
{0x0F12, 0x0125},	//TVAR_ash_AwbAshCord_3_ 4150K	
{0x0F12, 0x015F},	//TVAR_ash_AwbAshCord_4_ 5250K	
{0x0F12, 0x017C},	//TVAR_ash_AwbAshCord_5_ 6400K	
{0x0F12, 0x0194},	//TVAR_ash_AwbAshCord_6_ 7500K	

// GAS Alpha Table//
{0x002A, 0x08F6},
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_0__0_ R  // 2300K //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_0__1_ GR //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_0__2_ GB //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_0__3_ B //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_1__0_ R  // 2750K //

{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_1__1_ GR //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_1__2_ GB //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_1__3_ B //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_2__0_ R  // 3300K //

{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_2__1_ GR //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_2__2_ GB //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_2__3_ B //
{0x0F12, 0x3C00},		//TVAR_ash_GASAlpha_3__0_ R  // 4150K //

{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_3__1_ GR //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_3__2_ GB //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_3__3_ B //
{0x0F12, 0x3E00},		//TVAR_ash_GASAlpha_4__0_ R  // 5250K //

{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_4__1_ GR //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_4__2_ GB //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_4__3_ B //
{0x0F12, 0x4100},		//TVAR_ash_GASAlpha_5__0_ R  // 6400K //

{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_5__1_ GR //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_5__2_ GB //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_5__3_ B //
{0x0F12, 0x4200},		//TVAR_ash_GASAlpha_6__0_ R  // 7500K //

{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_6__1_ GR //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_6__2_ GB //
{0x0F12, 0x4000},		//TVAR_ash_GASAlpha_6__3_ B //

// Outdoor GAS Alpha//
{0x0F12, 0x4500},		//TVAR_ash_GASOutdoorAlpha_0_ R //
{0x0F12, 0x4000},		//TVAR_ash_GASOutdoorAlpha_1_ GR //
{0x0F12, 0x4000},		//TVAR_ash_GASOutdoorAlpha_2_ GB //
{0x0F12, 0x4000},		//TVAR_ash_GASOutdoorAlpha_3_ B //

{0x002A, 0x08F4},
{0x0F12, 0x0001},	//ash_bUseGasAlpha

//==================================================================================
// 11.Auto Flicker Detection
//==================================================================================

{0x002A, 0x0F30},
{0x0F12, 0x0001},   	//AFC_D_ConvAccelerPower 

// Auto Flicker (Auto Flicker:On and 60Mhz start)	
#if 0
{0x002A, 0x0F2A},
{0x0F12, 0x0000},	//AFC_Default BIT[0] 1:60Hz 0:50Hz //
{0x002A, 0x04E6},
{0x0F12, 0x075F},	//REG_TC_DBG 7F: 60Hz  5F:50Hz // [5]bit_AA-Flicker //
#else
{0x002A, 0x0F2A},
{0x0F12, 0x0001},	//AFC_Default BIT[0] 1:60Hz 0:50Hz //
{0x002A, 0x04E6},
{0x0F12, 0x077F},	//REG_TC_DBG 7F: 60Hz  5F:50Hz // [5]bit_AA-Flicker //
#endif



{0x7000, 0x04D6}, 
{0x0F12, 0x0000}, //REG_SF_USER_FlickerQuant //0 = no AFC, 1 = 50Hz, 2 = 60Hz
{0x0F12, 0x0001},	//REG_SF_USER_FlickerQuantChanged

//{0x002A, 0x04E6 },                                      
//{0x0F12, 0x075F },//REG_TC_DBG 7F:Flicker on   5F:Flicker off
//{0x002A, 0x04D6 },                                      
//{0x0F12, 0x0000 },//REG_SF_USER_FlickerQuant
//{0x0F12, 0x0001 },//REG_SF_USER_FlickerQuantChanged




//===========================================================
// 10.AE Setting
//==========================================================//
{0x002A, 0x1484},
{0x0F12, 0x003C},	  //TVAR_ae_BrAve //
{0x002A, 0x148A},
{0x0F12, 0x000F},	  //ae_StatMode //
{0x002A, 0x058C},
{0x0F12, 0x3520},
{0x0F12, 0x0000},		//lt_uMaxExp1 //
{0x0F12, 0xC350},
{0x0F12, 0x0000},		//lt_uMaxExp2 //
{0x0F12, 0x3520},
{0x0F12, 0x0000},		//lt_uCapMaxExp1 //
{0x0F12, 0xC350},
{0x0F12, 0x0000},		//lt_uCapMaxExp2//
{0x002A, 0x059C},
{0x0F12, 0x0470},		//lt_uMaxAnGain1 //
{0x0F12, 0x0C00},		//lt_uMaxAnGain2 //
{0x0F12, 0x0100},		//lt_uMaxDigGain //
{0x0F12, 0x1000},		//lt_uMaxTotGain //

{0x002A, 0x0544},
{0x0F12, 0x0111},	  //lt_uLimitHigh //
{0x0F12, 0x00EF},		//lt_uLimitLow //

{0x002A, 0x0608},
{0x0F12, 0x0001},	  //lt_ExpGain_uSubsamplingmode //
{0x0F12, 0x0001},		//lt_ExpGain_uNonSubsampling //
{0x0F12, 0x0800},		//lt_ExpGain_ExpCurveGainMaxStr //
{0x0F12, 0x0100},   //0100 //lt_ExpGain_ExpCurveGainMaxStr_0_uMaxDigGain//
{0x0F12, 0x0001},		//0001 //
{0x0F12, 0x0000},   //0000 //lt_ExpGain_ExpCurveGainMaxStr_0__ulExpIn_0_ //
{0x0F12, 0x0A3C},		//0A3C //
{0x0F12, 0x0000},		//0000 //
{0x0F12, 0x0D05},		//0D05 //
{0x0F12, 0x0000},		//0000 //
{0x0F12, 0x4008},		//4008 //
{0x0F12, 0x0000},		//0000 //
{0x0F12, 0x7000},		//7400  //?? //700Lux //
{0x0F12, 0x0000},		//0000 //
{0x0F12, 0x9C00},		//C000  //?? //9C00->9F->A5 //400Lux //
{0x0F12, 0x0000},		//0000 //
{0x0F12, 0xAD00},		//AD00 //
{0x0F12, 0x0001},		//0001 //
{0x0F12, 0xF1D4},		//F1D4 //
{0x0F12, 0x0002},		//0002 //
{0x0F12, 0xDC00},		//DC00 //
{0x0F12, 0x0005},		//0005 //
{0x0F12, 0xDC00},		//DC00 //
{0x0F12, 0x0005},		//0005 //

{0x002A, 0x0638},		//0638 //
{0x0F12, 0x0001},		//0001 //
{0x0F12, 0x0000},   //0000 //lt_ExpGain_ExpCurveGainMaxStr_0__ulExpOut_0_//
{0x0F12, 0x0A3C},		//0A3C //
{0x0F12, 0x0000},		//0000 //
{0x0F12, 0x0D05},		//0D05 //
{0x0F12, 0x0000},		//0000 //
{0x0F12, 0x3408},		//3408 //
{0x0F12, 0x0000},		//0000 //
{0x0F12, 0x3408},		//3408 //
{0x0F12, 0x0000},		//0000 //
{0x0F12, 0x6810},		//6810 //
{0x0F12, 0x0000},		//0000 //
{0x0F12, 0x8214},		//8214 //
{0x0F12, 0x0000},		//0000 //
{0x0F12, 0xC350},		//C350 //
{0x0F12, 0x0000},		//0000 //
{0x0F12, 0xC350},		//C350 //
{0x0F12, 0x0000},		//0000 //
{0x0F12, 0xC350},		//C350 //
{0x0F12, 0x0000},		//0000 //
{0x002A, 0x0660},
{0x0F12, 0x0650},		//lt_ExpGain_ExpCurveGainMaxStr_1_ //
{0x0F12, 0x0100}, //lt_ExpGain_ExpCurveGainMaxStr_1__uMaxDigGain //

{0x002A, 0x06B8},
{0x0F12, 0x452C},
{0x0F12, 0x0005},	//lt_uMaxLei //

//===========================================================
// 11.AE Weight (Normal)
//==========================================================//
{0x002A, 0x1492},
{0x0F12, 0x0100},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0001},
{0x0F12, 0x0101},
{0x0F12, 0x0201},
{0x0F12, 0x0102},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0202},
{0x0F12, 0x0202},
{0x0F12, 0x0101},
{0x0F12, 0x0201},
{0x0F12, 0x0302},
{0x0F12, 0x0203},
{0x0F12, 0x0102},
{0x0F12, 0x0201},
{0x0F12, 0x0302},
{0x0F12, 0x0203},
{0x0F12, 0x0102},
{0x0F12, 0x0201},
{0x0F12, 0x0202},
{0x0F12, 0x0202},
{0x0F12, 0x0102},
{0x0F12, 0x0101},
{0x0F12, 0x0202},
{0x0F12, 0x0202},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0101},
{0x0F12, 0x0101},

//============================================
// 14.AWB-BASIC setting
//============================================//

//AWB init Start point//
{0x002A, 0x145E},
{0x0F12, 0x0580},
{0x0F12, 0x0428},
{0x0F12, 0x07B0},

//AWB Init //
//White Locus//
{0x002A, 0x11F0},
{0x0F12, 0x0120},		//awbb_IntcR //
{0x0F12, 0x0121},		//awbb_IntcB //

//Indoor Zone//
{0x002A, 0x101C},
{0x0F12, 0x0386},
{0x0F12, 0x03A8},
{0x0F12, 0x033C},
{0x0F12, 0x0394},
{0x0F12, 0x02FE},
{0x0F12, 0x0372},
{0x0F12, 0x02A8},
{0x0F12, 0x0352},
{0x0F12, 0x027C},
{0x0F12, 0x0300},
{0x0F12, 0x0264},
{0x0F12, 0x02C8},
{0x0F12, 0x0244},
{0x0F12, 0x02A8},
{0x0F12, 0x022C},
{0x0F12, 0x02A0},
{0x0F12, 0x020C},
{0x0F12, 0x02A0},
{0x0F12, 0x01F4},
{0x0F12, 0x0298},
{0x0F12, 0x01D4},
{0x0F12, 0x0290},
{0x0F12, 0x01CC},
{0x0F12, 0x0276},
{0x0F12, 0x01D2},
{0x0F12, 0x0260},
{0x0F12, 0x01F6},
{0x0F12, 0x023A},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},	  //awbb_IndoorGrZones_m_GridStep //
{0x0F12, 0x0005},
{0x002A, 0x1070},		//awbb_IndoorGrZones_ZInfo_m_GridSz //
{0x0F12, 0x000F},
{0x002A, 0x1074},		//awbb_IndoorGrZones_m_Boffs //
{0x0F12, 0x0126},
// Outdoor Zone//
{0x002A, 0x1078},
{0x0F12, 0x0270},
{0x0F12, 0x0296},
{0x0F12, 0x024A},
{0x0F12, 0x02AC},
{0x0F12, 0x0240},
{0x0F12, 0x02B0},
{0x0F12, 0x0234},
{0x0F12, 0x02B0},
{0x0F12, 0x0228},
{0x0F12, 0x02AE},
{0x0F12, 0x021E},
{0x0F12, 0x02A8},
{0x0F12, 0x0212},
{0x0F12, 0x02A0},
{0x0F12, 0x0210},
{0x0F12, 0x0294},
{0x0F12, 0x020E},
{0x0F12, 0x0288},
{0x0F12, 0x0218},
{0x0F12, 0x027E},
{0x0F12, 0x0234},
{0x0F12, 0x0256},
{0x0F12, 0x0000},
{0x0F12, 0x0000},

{0x0F12, 0x0004},		//awbb_OutdoorGrZones_m_GridStep //
{0x002A, 0x10AC},
{0x0F12, 0x000B},		//awbb_OutdoorGrZones_ZInfo_m_GridSz //
{0x002A, 0x10B0},
{0x0F12, 0x01E8},		//awbb_OutdoorGrZones_m_Boffs //

	//LowBR Zone //
{0x002A, 0x10B4},
{0x0F12, 0x0350},
{0x0F12, 0x0422},
{0x0F12, 0x02C4},
{0x0F12, 0x0452},
{0x0F12, 0x0278},
{0x0F12, 0x041C},
{0x0F12, 0x0230},
{0x0F12, 0x03EE},
{0x0F12, 0x01F0},
{0x0F12, 0x0392},
{0x0F12, 0x01C0},
{0x0F12, 0x0340},
{0x0F12, 0x0194},
{0x0F12, 0x0302},
{0x0F12, 0x016E},
{0x0F12, 0x02C2},
{0x0F12, 0x0148},
{0x0F12, 0x0286},
{0x0F12, 0x018A},
{0x0F12, 0x0242},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0x0000},

{0x0F12, 0x0006},		//awbb_LowBrGrZones_m_GridStep //
{0x002A, 0x10E8},
{0x0F12, 0x000A},		//awbb_LowBrGrZones_ZInfo_m_GridSz //
{0x002A, 0x10EC},
{0x0F12, 0x0106},		//awbb_LowBrGrZones_m_Boffs //

	//LowTemp Zone //
{0x002A, 0x10F0},
{0x0F12, 0x0380},
{0x0F12, 0x0000},		//awbb_CrclLowT_R_c //
{0x0F12, 0x0168},
{0x0F12, 0x0000},		//awbb_CrclLowT_B_c //
{0x0F12, 0x2D90},
{0x0F12, 0x0000},		//awbb_CrclLowT_Rad_c //

	//AWB Convergence Speed //
{0x002A, 0x1464},
{0x0F12, 0x0008},
{0x0F12, 0x0190},
{0x0F12, 0x00A0},

{0x002A, 0x1228},
{0x0F12, 0x00C0},
{0x002A, 0x122C},
{0x0F12, 0x0010},
{0x002A, 0x122A},
{0x0F12, 0x0010},

{0x002A, 0x120A},
{0x0F12, 0x05D5},		//awbb_MvEq_RBthresh //
{0x002A, 0x120E},
{0x0F12, 0x0000},

{0x0F12, 0x0771},
{0x0F12, 0x03A4},
{0x0F12, 0x0036},
{0x0F12, 0x002A},

{0x002A, 0x1278},
{0x0F12, 0xFEF7},
{0x0F12, 0x0021},
{0x0F12, 0x0AF0},		//0E74 //
{0x0F12, 0x0AF0},		//0E74 //
{0x0F12, 0x018F},
{0x0F12, 0x0096},
{0x0F12, 0x000E},
{0x002A, 0x1224},
{0x0F12, 0x0032},
{0x0F12, 0x001E},
{0x0F12, 0x00C0},
{0x0F12, 0x0010},
{0x0F12, 0x0002},		//awbb_YThreshLow_Low //
{0x002A, 0x2BA4},
{0x0F12, 0x0006},		//Mon_AWB_ByPassMode //

{0x002A, 0x146C},
{0x0F12, 0x0002},		//awbb_GridEnable //

	//Grid //
{0x002A, 0x1434},
{0x0F12, 0x02CE},		// awbb_GridConst_1 //
{0x0F12, 0x0347},		// awbb_GridConst_1_1_ //
{0x0F12, 0x03C2},		// awbb_GridConst_1_2_ //
{0x0F12, 0x10A0},		// awbb_GridConst_2 //
{0x0F12, 0x10A1},		// awbb_GridConst_2_1_ //
{0x0F12, 0x1185},		// awbb_GridConst_2_2_ //
{0x0F12, 0x1186},		// awbb_GridConst_2_3_ //
{0x0F12, 0x11E5},		// awbb_GridConst_2_4_ //
{0x0F12, 0x11E6},		// awbb_GridConst_2_5_ //
{0x0F12, 0x00AB},		// awbb_GridCoeff_R_1 //
{0x0F12, 0x00BF},		// awbb_GridCoeff_B_1 //
{0x0F12, 0x00D2},		// awbb_GridCoeff_R_2 //
{0x0F12, 0x0093},		// awbb_GridCoeff_B_2 //

	//Indoor Grid Offset //
{0x002A, 0x13A4},
{0x0F12, 0x0000},		//0000 //
{0x0F12, 0xFFE8},		//FFD8 //
{0x0F12, 0xFFE8},		//FFD8 //
{0x0F12, 0xFFC0},		//FFD8 //
{0x0F12, 0xFFC0},		//FFD8 //
{0x0F12, 0xFFD0},		//FFF6 B //

{0x0F12, 0x0000},	//0000 //
{0x0F12, 0xFFD8},		//FFD8 //
{0x0F12, 0xFFD8},		//FFD8 //
{0x0F12, 0xFFC0},		//FFD8 //
{0x0F12, 0xFFC0},		//FFD8 //
{0x0F12, 0xFFD0},		//FFF6 //

{0x0F12, 0x0000},	//0000 //
{0x0F12, 0xFFD8},		//FFD8 //
{0x0F12, 0xFFD8},		//FFD8 //
{0x0F12, 0xFFC0},		//FFD8 //
{0x0F12, 0xFFC0},		//FFD8 //
{0x0F12, 0xFFD0},		//FFF6 //

{0x0F12, 0xFFEC}, //FFEC//
{0x0F12, 0x0010},	//000A //
{0x0F12, 0x0010},		//000A //
{0x0F12, 0xFFC0},		//FFC4 //
{0x0F12, 0xFFC0},		//FFC4 //
{0x0F12, 0xFFBC},		//FF56 7 //

{0x0F12, 0xFFEC}, //FFEC//
{0x0F12, 0x0010},	//000A //
{0x0F12, 0x0010},		//000A //
{0x0F12, 0xFFC0},		//FFC4 //
{0x0F12, 0xFFC0},		//FFC4 //
{0x0F12, 0xFFBC},		//FF56 //

{0x0F12, 0xFFEC}, //FFEC//
{0x0F12, 0x0010},	//000A //
{0x0F12, 0x0010},		//000A //
{0x0F12, 0xFFC0},		//FFC4 //
{0x0F12, 0xFFC0},		//FFC4 //
{0x0F12, 0xFFBC},		//FF56 //

//Outdoor Grid Offset//
{0x0F12, 0xFFE0},
{0x0F12, 0xFFE0},
{0x0F12, 0xFFE0},
{0x0F12, 0xFFE0},
{0x0F12, 0x0000},
{0x0F12, 0x0000},

{0x0F12, 0xFFE0},
{0x0F12, 0xFFE0},
{0x0F12, 0xFFE0},
{0x0F12, 0xFFE0},
{0x0F12, 0x0000},
{0x0F12, 0x0000},

{0x0F12, 0xFFE0},
{0x0F12, 0xFFE0},
{0x0F12, 0xFFE0},
{0x0F12, 0xFFE0},
{0x0F12, 0x0000},
{0x0F12, 0x0000},

{0x0F12, 0xFFB0},
{0x0F12, 0xFFA8},
{0x0F12, 0xFFA8},
{0x0F12, 0xFFA8},
{0x0F12, 0x0000},
{0x0F12, 0x0000},

{0x0F12, 0xFFB0},
{0x0F12, 0xFFA8},
{0x0F12, 0xFFA8},
{0x0F12, 0xFFA8},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x0F12, 0xFFB0},
{0x0F12, 0xFFA8},
{0x0F12, 0xFFA8},
{0x0F12, 0xFFA8},
{0x0F12, 0x0000},
{0x0F12, 0x0000},
{0x002A, 0x1208},
{0x0F12, 0x0020},

{0x002A, 0x144E},
{0x0F12, 0x0000},		//awbb_RGainOff //
{0x0F12, 0xFFE0},		//awbb_BGainOff //
{0x0F12, 0x0000},		//awbb_GGainOff //

//=======================================================
// 15.CCM Setting
//======================================================//
	 //CCM//
{0x002A, 0x08A6},
{0x0F12, 0x00C0},
{0x0F12, 0x0100},
{0x0F12, 0x0125},
{0x0F12, 0x015F},
{0x0F12, 0x017C},
{0x0F12, 0x0194},

{0x0F12, 0x0001},

{0x002A, 0x0898},
{0x0F12, 0x4800},
{0x0F12, 0x7000},
{0x002A, 0x08A0},
{0x0F12, 0x48D8},
{0x0F12, 0x7000},
{0x002A, 0x4800},	//Horizon //
{0x0F12, 0x0208},
{0x0F12, 0xFFB5},
{0x0F12, 0xFFE8},
{0x0F12, 0xFF20},
{0x0F12, 0x01BF},
{0x0F12, 0xFF53},
{0x0F12, 0x0022},
{0x0F12, 0xFFEA},
{0x0F12, 0x01C2},
{0x0F12, 0x00C6},
{0x0F12, 0x0095},
{0x0F12, 0xFEFD},
{0x0F12, 0x0206},
{0x0F12, 0xFF7F},
{0x0F12, 0x0191},
{0x0F12, 0xFF06},
{0x0F12, 0x01BA},
{0x0F12, 0x0108},

{0x0F12, 0x0208},		// inca A //
{0x0F12, 0xFFB5},
{0x0F12, 0xFFE8},
{0x0F12, 0xFF20},
{0x0F12, 0x01BF},
{0x0F12, 0xFF53},
{0x0F12, 0x0022},
{0x0F12, 0xFFEA},
{0x0F12, 0x01C2},
{0x0F12, 0x00C6},
{0x0F12, 0x0095},
{0x0F12, 0xFEFD},
{0x0F12, 0x0206},
{0x0F12, 0xFF7F},
{0x0F12, 0x0191},
{0x0F12, 0xFF06},
{0x0F12, 0x01BA},
{0x0F12, 0x0108},

{0x0F12, 0x0208},	//WW//
{0x0F12, 0xFFB5},
{0x0F12, 0xFFE8},
{0x0F12, 0xFF20},
{0x0F12, 0x01BF},
{0x0F12, 0xFF53},
{0x0F12, 0x0022},
{0x0F12, 0xFFEA},
{0x0F12, 0x01C2},
{0x0F12, 0x00C6},
{0x0F12, 0x0095},
{0x0F12, 0xFEFD},
{0x0F12, 0x0206},
{0x0F12, 0xFF7F},
{0x0F12, 0x0191},
{0x0F12, 0xFF06},
{0x0F12, 0x01BA},
{0x0F12, 0x0108},

{0x0F12, 0x0204},	//CW//
{0x0F12, 0xFFB2},
{0x0F12, 0xFFF5},
{0x0F12, 0xFEF1},
{0x0F12, 0x014E},
{0x0F12, 0xFF18},
{0x0F12, 0xFFE6},
{0x0F12, 0xFFDD},
{0x0F12, 0x01B2},
{0x0F12, 0x00F2},
{0x0F12, 0x00CA},
{0x0F12, 0xFF48},
{0x0F12, 0x0151},
{0x0F12, 0xFF50},
{0x0F12, 0x0147},
{0x0F12, 0xFF75},
{0x0F12, 0x0187},
{0x0F12, 0x01BF},

{0x0F12, 0x01F5},	//D50//
{0x0F12, 0xFFB4},
{0x0F12, 0x0001},
{0x0F12, 0xFED7},
{0x0F12, 0x014B},
{0x0F12, 0xFF35},
{0x0F12, 0xFFE6},
{0x0F12, 0xFFDD},
{0x0F12, 0x01B2},
{0x0F12, 0x00F2},
{0x0F12, 0x00CA},
{0x0F12, 0xFF48},
{0x0F12, 0x0151},
{0x0F12, 0xFF50},
{0x0F12, 0x0147},
{0x0F12, 0xFF75},
{0x0F12, 0x0187},
{0x0F12, 0x01BF},

{0x0F12, 0x01F5},	//D65 //
{0x0F12, 0xFFB4},
{0x0F12, 0x0001},
{0x0F12, 0xFED7},
{0x0F12, 0x014B},
{0x0F12, 0xFF35},
{0x0F12, 0xFFE6},
{0x0F12, 0xFFDD},
{0x0F12, 0x01B2},
{0x0F12, 0x00F2},
{0x0F12, 0x00CA},
{0x0F12, 0xFF48},
{0x0F12, 0x0151},
{0x0F12, 0xFF50},
{0x0F12, 0x0147},
{0x0F12, 0xFF75},
{0x0F12, 0x0187},
{0x0F12, 0x01BF},

{0x0F12, 0x01E5},	//Y hue-5. TVAR_wbt_pOutdoorCcm[0] //
{0x0F12, 0xFFA4},
{0x0F12, 0xFFDC},
{0x0F12, 0xFE90},
{0x0F12, 0x013F},
{0x0F12, 0xFF1B},
{0x0F12, 0xFFD2},
{0x0F12, 0xFFDF},
{0x0F12, 0x0236},
{0x0F12, 0x00F0},
{0x0F12, 0x00C9},
{0x0F12, 0xFF59},
{0x0F12, 0x01CE},
{0x0F12, 0xFF83},
{0x0F12, 0x0195},
{0x0F12, 0xFEF3},
{0x0F12, 0x0126},
{0x0F12, 0x0162},

//===================================================================
// 16.GAMMA
//=================================================================//
{0x002A, 0x0734}, //R//
{0x0F12, 0x0000},
{0x0F12, 0x0001},
{0x0F12, 0x0006},
{0x0F12, 0x0017},
{0x0F12, 0x004A},
{0x0F12, 0x00C9},
{0x0F12, 0x0138},
{0x0F12, 0x0163},
{0x0F12, 0x0189},
{0x0F12, 0x01C6},
{0x0F12, 0x01F8},
{0x0F12, 0x0222},
{0x0F12, 0x0247},
{0x0F12, 0x0282},
{0x0F12, 0x02B5},
{0x0F12, 0x030F},
{0x0F12, 0x035F},
{0x0F12, 0x03A2},
{0x0F12, 0x03D8},
{0x0F12, 0x03FF},

{0x0F12, 0x0000}, //G//
{0x0F12, 0x0001},
{0x0F12, 0x0006},
{0x0F12, 0x0017},
{0x0F12, 0x004A},
{0x0F12, 0x00C9},
{0x0F12, 0x0138},
{0x0F12, 0x0163},
{0x0F12, 0x0189},
{0x0F12, 0x01C6},
{0x0F12, 0x01F8},
{0x0F12, 0x0222},
{0x0F12, 0x0247},
{0x0F12, 0x0282},
{0x0F12, 0x02B5},
{0x0F12, 0x030F},
{0x0F12, 0x035F},
{0x0F12, 0x03A2},
{0x0F12, 0x03D8},
{0x0F12, 0x03FF},

{0x0F12, 0x0000}, //B//
{0x0F12, 0x0001},
{0x0F12, 0x0006},
{0x0F12, 0x0017},
{0x0F12, 0x004A},
{0x0F12, 0x00C9},
{0x0F12, 0x0138},
{0x0F12, 0x0163},
{0x0F12, 0x0189},
{0x0F12, 0x01C6},
{0x0F12, 0x01F8},
{0x0F12, 0x0222},
{0x0F12, 0x0247},
{0x0F12, 0x0282},
{0x0F12, 0x02B5},
{0x0F12, 0x030F},
{0x0F12, 0x035F},
{0x0F12, 0x03A2},
{0x0F12, 0x03D8},
{0x0F12, 0x03FF},

//RGB Outdoor Gamma//
{0x0F12, 0x0000},
{0x0F12, 0x000B},
{0x0F12, 0x0019},
{0x0F12, 0x0036},
{0x0F12, 0x006F},
{0x0F12, 0x00D8},
{0x0F12, 0x0135},
{0x0F12, 0x015F},
{0x0F12, 0x0185},
{0x0F12, 0x01C1},
{0x0F12, 0x01F3},
{0x0F12, 0x0220},
{0x0F12, 0x024A},
{0x0F12, 0x0291},
{0x0F12, 0x02D0},
{0x0F12, 0x032A},
{0x0F12, 0x036A},
{0x0F12, 0x039F},
{0x0F12, 0x03CC},
{0x0F12, 0x03F9},

{0x0F12, 0x0000},
{0x0F12, 0x000B},
{0x0F12, 0x0019},
{0x0F12, 0x0036},
{0x0F12, 0x006F},
{0x0F12, 0x00D8},
{0x0F12, 0x0135},
{0x0F12, 0x015F},
{0x0F12, 0x0185},
{0x0F12, 0x01C1},
{0x0F12, 0x01F3},
{0x0F12, 0x0220},
{0x0F12, 0x024A},
{0x0F12, 0x0291},
{0x0F12, 0x02D0},
{0x0F12, 0x032A},
{0x0F12, 0x036A},
{0x0F12, 0x039F},
{0x0F12, 0x03CC},
{0x0F12, 0x03F9},

{0x0F12, 0x0000},
{0x0F12, 0x000B},
{0x0F12, 0x0019},
{0x0F12, 0x0036},
{0x0F12, 0x006F},
{0x0F12, 0x00D8},
{0x0F12, 0x0135},
{0x0F12, 0x015F},
{0x0F12, 0x0185},
{0x0F12, 0x01C1},
{0x0F12, 0x01F3},
{0x0F12, 0x0220},
{0x0F12, 0x024A},
{0x0F12, 0x0291},
{0x0F12, 0x02D0},
{0x0F12, 0x032A},
{0x0F12, 0x036A},
{0x0F12, 0x039F},
{0x0F12, 0x03CC},
{0x0F12, 0x03F9},
//============================================================
// 17.AFIT
//===========================================================//
{0x002A, 0x0944},
{0x0F12, 0x0050},	  //afit_uNoiseIndInDoor //
{0x0F12, 0x00B0},		//afit_uNoiseIndInDoor //
{0x0F12, 0x0196},		//afit_uNoiseIndInDoor //
{0x0F12, 0x0245},		//afit_uNoiseIndInDoor //
{0x0F12, 0x0300},		//afit_uNoiseIndInDoor //

{0x002A, 0x0938},
{0x0F12, 0x0000},	  // on/off AFIT by NB option //
{0x0F12, 0x0014},		//SARR_uNormBrInDoor //
{0x0F12, 0x00D2},		//SARR_uNormBrInDoor //
{0x0F12, 0x0384},		//SARR_uNormBrInDoor //
{0x0F12, 0x07D0},		//SARR_uNormBrInDoor //
{0x0F12, 0x1388},		//SARR_uNormBrInDoor //

{0x002A, 0x0976},
{0x0F12, 0x0070},	  //afit_usGamutTh //
{0x0F12, 0x0005},		//afit_usNeargrayOffset //
{0x0F12, 0x0000},		//afit_bUseSenBpr //
{0x0F12, 0x01CC},		//afit_usBprThr_0_ //
{0x0F12, 0x01CC},		//afit_usBprThr_1_ //
{0x0F12, 0x01CC},		//afit_usBprThr_2_ //
{0x0F12, 0x01CC},		//afit_usBprThr_3_ //
{0x0F12, 0x01CC},		//afit_usBprThr_4_ //
{0x0F12, 0x0180},		//afit_NIContrastAFITValue //
{0x0F12, 0x0196},		//afit_NIContrastTh //

{0x002A, 0x098C},
{0x0F12, 0xFFEC},		//7000098C//AFIT16_BRIGHTNESS                                                               
{0x0F12, 0x0000},		//7000098E//AFIT16_CONTRAST                                                                 
{0x0F12, 0x0000},		//70000990//AFIT16_SATURATION                                                               
{0x0F12, 0x0000},		//70000992//AFIT16_SHARP_BLUR                                                               
{0x0F12, 0x0000},		//70000994//AFIT16_GLAMOUR                                                                  
{0x0F12, 0x00C0},		//70000996//AFIT16_bnr_edge_high                                                            
{0x0F12, 0x0064},		//70000998//AFIT16_postdmsc_iLowBright                                                      
{0x0F12, 0x0384},		//7000099A//AFIT16_postdmsc_iHighBright                                                     
{0x0F12, 0x005F},		//7000099C//AFIT16_postdmsc_iLowSat                                                         
{0x0F12, 0x01F4},		//7000099E//AFIT16_postdmsc_iHighSat                                                        
{0x0F12, 0x0070},		//700009A0//AFIT16_postdmsc_iTune                                                           
{0x0F12, 0x0040},		//700009A2//AFIT16_yuvemix_mNegRanges_0                                                     
{0x0F12, 0x00A0},		//700009A4//AFIT16_yuvemix_mNegRanges_1                                                     
{0x0F12, 0x0100},		//700009A6//AFIT16_yuvemix_mNegRanges_2                                                     
{0x0F12, 0x0010},		//700009A8//AFIT16_yuvemix_mPosRanges_0                                                     
{0x0F12, 0x0040},		//700009AA//AFIT16_yuvemix_mPosRanges_1                                                     
{0x0F12, 0x00A0},		//700009AC//AFIT16_yuvemix_mPosRanges_2                                                     
{0x0F12, 0x1430},		//700009AE//AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh                                 
{0x0F12, 0x0201},		//700009B0//AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh                            
{0x0F12, 0x0204},		//700009B2//AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh                       
{0x0F12, 0x3604},		//700009B4//AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low                           
{0x0F12, 0x032A},		//700009B6//AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low                          
{0x0F12, 0x0403},		//700009B8//AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin                       
{0x0F12, 0x1B06},		//700009BA//AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow                         
{0x0F12, 0x6015},		//700009BC//AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH                    
{0x0F12, 0x00C0},		//700009BE//AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune                     
{0x0F12, 0x6080},		//700009C0//AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh                   
{0x0F12, 0x4080},		//700009C2//AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh             
{0x0F12, 0x0640},		//700009C4//AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed              
{0x0F12, 0x0306},		//700009C6//AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh                
{0x0F12, 0x2003},		//700009C8//AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH                       
{0x0F12, 0xFF01},		//700009CA//AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit                  
{0x0F12, 0x0000},		//700009CC//AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2                       
{0x0F12, 0x0400},		//700009CE//AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower                            
{0x0F12, 0x365A},		//700009D0//AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow                             
{0x0F12, 0x102A},		//700009D2//AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow                              
{0x0F12, 0x000B},		//700009D4//AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow                                 
{0x0F12, 0x0600},		//700009D6//AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower                                 
{0x0F12, 0x5A0F},		//700009D8//AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit                            
{0x0F12, 0x0505},		//700009DA//AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope                         
{0x0F12, 0x1802},		//700009DC//AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR                                 
{0x0F12, 0x0000},		//700009DE//AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres                           
{0x0F12, 0x2006},		//700009E0//AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR                           
{0x0F12, 0x3028},		//700009E2//AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen                            
{0x0F12, 0x0418},		//700009E4//AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh                                  
{0x0F12, 0x0101},		//700009E6//AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative                            
{0x0F12, 0x0800},		//700009E8//AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle                           
{0x0F12, 0x1804},		//700009EA//AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh                        
{0x0F12, 0x4008},		//700009EC//AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh                         
{0x0F12, 0x0540},		//700009EE//AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange                         
{0x0F12, 0x8006},		//700009F0//AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad                         
{0x0F12, 0x0020},		//700009F2//AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal                          
{0x0F12, 0x0000},		//700009F4//AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh                   
{0x0F12, 0x2000},		//700009F6//AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat                       
{0x0F12, 0x0000},		//700009F8//AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit                    
{0x0F12, 0x1E10},		//700009FA//AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff                           
{0x0F12, 0x000B},		//700009FC//AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0                     
{0x0F12, 0x0607},		//700009FE//AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2                   
{0x0F12, 0x0005},		//70000A00//AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0                   
{0x0F12, 0x0607},		//70000A02//AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2                   
{0x0F12, 0x0705},		//70000A04//AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY                    
{0x0F12, 0x0206},		//70000A06//AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm                     
{0x0F12, 0x0304},		//70000A08//AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm                     
{0x0F12, 0x0309},		//70000A0A//AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift                   
{0x0F12, 0x0305},		//70000A0C//AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y                
{0x0F12, 0x2006},		//70000A0E//AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y             
{0x0F12, 0x1320},		//70000A10//AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV            
{0x0F12, 0x1014},		//70000A12//AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y             
{0x0F12, 0x1010},		//70000A14//AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV              
{0x0F12, 0x0C10},		//70000A16//AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL              
{0x0F12, 0x1A0C},		//70000A18//AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL              
{0x0F12, 0x4A18},		//70000A1A//AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower              
{0x0F12, 0x0080},		//70000A1C//AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce                  
{0x0F12, 0x0350},		//70000A1E//AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset                      
{0x0F12, 0x0180},		//70000A20//AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H                          
{0x0F12, 0x0A0A},		//70000A22//AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C                           
{0x0F12, 0x0101},		//70000A24//AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C                       
{0x0F12, 0x2A36},		//70000A26//AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh                        
{0x0F12, 0x6024},		//70000A28//AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower                        
{0x0F12, 0x2A36},		//70000A2A//AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise                          
{0x0F12, 0xFFFF},		//70000A2C//AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp                        
{0x0F12, 0x0808},		//70000A2E//AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope                   
{0x0F12, 0x0A01},		//70000A30//AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin                  
{0x0F12, 0x010A},		//70000A32//AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin                 
{0x0F12, 0x2701},		//70000A34//AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin                
{0x0F12, 0x241E},		//70000A36//AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin                
{0x0F12, 0x2E60},		//70000A38//AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin                 
{0x0F12, 0xFF22},		//70000A3A//AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin                 
{0x0F12, 0x40FF},		//70000A3C//AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin            
{0x0F12, 0x0009},		//70000A3E//AFIT8_ee_iReduceEdgeSlope_Bin [7:0]                                             
{0x0F12, 0x0001},		//70000A40//AFITB_bnr_nClustLevel_C      [0]                                                
                                                                                                        
{0x0F12, 0x0000},		//70000A42//AFIT16_BRIGHTNESS                                                               
{0x0F12, 0x0000},		//70000A44//AFIT16_CONTRAST                                                                 
{0x0F12, 0x0000},		//70000A46//AFIT16_SATURATION                                                               
{0x0F12, 0x0000},		//70000A48//AFIT16_SHARP_BLUR                                                               
{0x0F12, 0x0000},		//70000A4A//AFIT16_GLAMOUR                                                                  
{0x0F12, 0x00C0},		//70000A4C//AFIT16_bnr_edge_high                                                            
{0x0F12, 0x0064},		//70000A4E//AFIT16_postdmsc_iLowBright                                                      
{0x0F12, 0x0384},		//70000A50//AFIT16_postdmsc_iHighBright                                                     
{0x0F12, 0x0051},		//70000A52//AFIT16_postdmsc_iLowSat                                                         
{0x0F12, 0x01F4},		//70000A54//AFIT16_postdmsc_iHighSat                                                        
{0x0F12, 0x0070},		//70000A56//AFIT16_postdmsc_iTune                                                           
{0x0F12, 0x0040},		//70000A58//AFIT16_yuvemix_mNegRanges_0                                                     
{0x0F12, 0x00A0},		//70000A5A//AFIT16_yuvemix_mNegRanges_1                                                     
{0x0F12, 0x0100},		//70000A5C//AFIT16_yuvemix_mNegRanges_2                                                     
{0x0F12, 0x0010},		//70000A5E//AFIT16_yuvemix_mPosRanges_0                                                     
{0x0F12, 0x0060},		//70000A60//AFIT16_yuvemix_mPosRanges_1                                                     
{0x0F12, 0x0100},		//70000A62//AFIT16_yuvemix_mPosRanges_2                                                     
{0x0F12, 0x1430},		//70000A64//AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh                                 
{0x0F12, 0x0201},		//70000A66//AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh                            
{0x0F12, 0x0204},		//70000A68//AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh                       
{0x0F12, 0x2404},		//70000A6A//AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low                           
{0x0F12, 0x031B},		//70000A6C//AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low                          
{0x0F12, 0x0103},		//70000A6E//AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin                       
{0x0F12, 0x1205},		//70000A70//AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow                         
{0x0F12, 0x400D},		//70000A72//AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH                    
{0x0F12, 0x0080},		//70000A74//AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune                     
{0x0F12, 0x1980},		//70000A76//AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh                   
{0x0F12, 0x272E},		//70000A78//AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh             
{0x0F12, 0x0629},		//70000A7A//AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed              
{0x0F12, 0x0306},		//70000A7C//AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh                
{0x0F12, 0x2003},		//70000A7E//AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH                       
{0x0F12, 0xFF01},		//70000A80//AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit                  
{0x0F12, 0x0404},		//70000A82//AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2                       
{0x0F12, 0x0300},		//70000A84//AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower                            
{0x0F12, 0x245A},		//70000A86//AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow                             
{0x0F12, 0x1018},		//70000A88//AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow                              
{0x0F12, 0x000B},		//70000A8A//AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow                                 
{0x0F12, 0x0B00},		//70000A8C//AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower                                 
{0x0F12, 0x5A0F},		//70000A8E//AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit                            
{0x0F12, 0x0505},		//70000A90//AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope                         
{0x0F12, 0x1802},		//70000A92//AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR                                 
{0x0F12, 0x0000},		//70000A94//AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres                           
{0x0F12, 0x2006},		//70000A96//AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR                           
{0x0F12, 0x3828},		//70000A98//AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen                            
{0x0F12, 0x0425},		//70000A9A//AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh                                  
{0x0F12, 0x0101},		//70000A9C//AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative                            
{0x0F12, 0x0800},		//70000A9E//AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle                           
{0x0F12, 0x1004},		//70000AA0//AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh                        
{0x0F12, 0x4008},		//70000AA2//AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh                         
{0x0F12, 0x0540},		//70000AA4//AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange                         
{0x0F12, 0x8006},		//70000AA6//AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad                         
{0x0F12, 0x0020},		//70000AA8//AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal                          
{0x0F12, 0x0000},		//70000AAA//AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh                   
{0x0F12, 0x2000},		//70000AAC//AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat                       
{0x0F12, 0x0000},		//70000AAE//AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit                    
{0x0F12, 0x1E10},		//70000AB0//AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff                           
{0x0F12, 0x000B},		//70000AB2//AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0                     
{0x0F12, 0x0607},		//70000AB4//AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2                   
{0x0F12, 0x0005},		//70000AB6//AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0                   
{0x0F12, 0x0607},		//70000AB8//AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2                   
{0x0F12, 0x0405},		//70000ABA//AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY                    
{0x0F12, 0x0205},		//70000ABC//AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm                     
{0x0F12, 0x0304},		//70000ABE//AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm                     
{0x0F12, 0x0409},		//70000AC0//AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift                   
{0x0F12, 0x0306},		//70000AC2//AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y                
{0x0F12, 0x0407},		//70000AC4//AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y             
{0x0F12, 0x2204},		//70000AC6//AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV            
{0x0F12, 0x021C},		//70000AC8//AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y             
{0x0F12, 0x1102},		//70000ACA//AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV              
{0x0F12, 0x0611},		//70000ACC//AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL              
{0x0F12, 0x1A02},		//70000ACE//AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL              
{0x0F12, 0x8018},		//70000AD0//AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower              
{0x0F12, 0x0080},		//70000AD2//AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce                  
{0x0F12, 0x0374},		//70000AD4//AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset                      
{0x0F12, 0x0180},		//70000AD6//AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H                          
{0x0F12, 0x0A0A},		//70000AD8//AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C                           
{0x0F12, 0x0101},		//70000ADA//AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C                       
{0x0F12, 0x141D},		//70000ADC//AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh                        
{0x0F12, 0x6024},		//70000ADE//AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower                        
{0x0F12, 0x1217},		//70000AE0//AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise                          
{0x0F12, 0xFFFF},		//70000AE2//AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp                        
{0x0F12, 0x0808},		//70000AE4//AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope                   
{0x0F12, 0x0A01},		//70000AE6//AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin                  
{0x0F12, 0x010A},		//70000AE8//AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin                 
{0x0F12, 0x0001},		//70000AEA//AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin                
{0x0F12, 0x2400},		//70000AEC//AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin                
{0x0F12, 0x1660},		//70000AEE//AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin                 
{0x0F12, 0xFF10},		//70000AF0//AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin                 
{0x0F12, 0x40FF},		//70000AF2//AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin            
{0x0F12, 0x0009},		//70000AF4//AFIT8_ee_iReduceEdgeSlope_Bin [7:0]                                             
{0x0F12, 0x0001},		//70000AF6//AFITB_bnr_nClustLevel_C      [0]                                                
                                                                                                        
{0x0F12, 0x0000},		//70000AF8//AFIT16_BRIGHTNESS                                                               
{0x0F12, 0x0000},		//70000AFA//AFIT16_CONTRAST                                                                 
{0x0F12, 0x0000},		//70000AFC//AFIT16_SATURATION                                                               
{0x0F12, 0x0000},		//70000AFE//AFIT16_SHARP_BLUR                                                               
{0x0F12, 0x0000},		//70000B00//AFIT16_GLAMOUR                                                                  
{0x0F12, 0x00C0},		//70000B02//AFIT16_bnr_edge_high                                                            
{0x0F12, 0x0064},		//70000B04//AFIT16_postdmsc_iLowBright                                                      
{0x0F12, 0x0384},		//70000B06//AFIT16_postdmsc_iHighBright                                                     
{0x0F12, 0x0043},		//70000B08//AFIT16_postdmsc_iLowSat                                                         
{0x0F12, 0x01F4},		//70000B0A//AFIT16_postdmsc_iHighSat                                                        
{0x0F12, 0x0070},		//70000B0C//AFIT16_postdmsc_iTune                                                           
{0x0F12, 0x0040},		//70000B0E//AFIT16_yuvemix_mNegRanges_0                                                     
{0x0F12, 0x00A0},		//70000B10//AFIT16_yuvemix_mNegRanges_1                                                     
{0x0F12, 0x0100},		//70000B12//AFIT16_yuvemix_mNegRanges_2                                                     
{0x0F12, 0x0010},		//70000B14//AFIT16_yuvemix_mPosRanges_0                                                     
{0x0F12, 0x0060},		//70000B16//AFIT16_yuvemix_mPosRanges_1                                                     
{0x0F12, 0x0100},		//70000B18//AFIT16_yuvemix_mPosRanges_2                                                     
{0x0F12, 0x1430},		//70000B1A//AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh                                 
{0x0F12, 0x0201},		//70000B1C//AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh                            
{0x0F12, 0x0204},		//70000B1E//AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh                       
{0x0F12, 0x1B04},		//70000B20//AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low                           
{0x0F12, 0x0312},		//70000B22//AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low                          
{0x0F12, 0x0003},		//70000B24//AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin                       
{0x0F12, 0x0C03},		//70000B26//AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow                         
{0x0F12, 0x2806},		//70000B28//AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH                    
{0x0F12, 0x0060},		//70000B2A//AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune                     
{0x0F12, 0x1580},		//70000B2C//AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh                   
{0x0F12, 0x2020},		//70000B2E//AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh             
{0x0F12, 0x0620},		//70000B30//AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed              
{0x0F12, 0x0306},		//70000B32//AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh                
{0x0F12, 0x2003},		//70000B34//AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH                       
{0x0F12, 0xFF01},		//70000B36//AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit                  
{0x0F12, 0x0404},		//70000B38//AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2                       
{0x0F12, 0x0300},		//70000B3A//AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower                            
{0x0F12, 0x145A},		//70000B3C//AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow                             
{0x0F12, 0x1010},		//70000B3E//AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow                              
{0x0F12, 0x000B},		//70000B40//AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow                                 
{0x0F12, 0x0E00},		//70000B42//AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower                                 
{0x0F12, 0x5A0F},		//70000B44//AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit                            
{0x0F12, 0x0504},		//70000B46//AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope                         
{0x0F12, 0x1802},		//70000B48//AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR                                 
{0x0F12, 0x0000},		//70000B4A//AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres                           
{0x0F12, 0x2006},		//70000B4C//AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR                           
{0x0F12, 0x3828},		//70000B4E//AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen                            
{0x0F12, 0x0428},		//70000B50//AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh                                  
{0x0F12, 0x0101},		//70000B52//AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative                            
{0x0F12, 0x8000},		//70000B54//AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle                           
{0x0F12, 0x0A04},		//70000B56//AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh                        
{0x0F12, 0x4008},		//70000B58//AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh                         
{0x0F12, 0x0540},		//70000B5A//AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange                         
{0x0F12, 0x8006},		//70000B5C//AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad                         
{0x0F12, 0x0020},		//70000B5E//AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal                          
{0x0F12, 0x0000},		//70000B60//AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh                   
{0x0F12, 0x2000},		//70000B62//AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat                       
{0x0F12, 0x0000},		//70000B64//AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit                    
{0x0F12, 0x1E10},		//70000B66//AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff                           
{0x0F12, 0x000B},		//70000B68//AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0                     
{0x0F12, 0x0607},		//70000B6A//AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2                   
{0x0F12, 0x0005},		//70000B6C//AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0                   
{0x0F12, 0x0607},		//70000B6E//AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2                   
{0x0F12, 0x0405},		//70000B70//AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY                    
{0x0F12, 0x0207},		//70000B72//AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm                     
{0x0F12, 0x0304},		//70000B74//AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm                     
{0x0F12, 0x0409},		//70000B76//AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift                   
{0x0F12, 0x0306},		//70000B78//AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y                
{0x0F12, 0x0407},		//70000B7A//AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y             
{0x0F12, 0x2404},		//70000B7C//AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV            
{0x0F12, 0x0221},		//70000B7E//AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y             
{0x0F12, 0x1202},		//70000B80//AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV              
{0x0F12, 0x0613},		//70000B82//AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL              
{0x0F12, 0x1A02},		//70000B84//AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL              
{0x0F12, 0x8018},		//70000B86//AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower              
{0x0F12, 0x0080},		//70000B88//AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce                  
{0x0F12, 0x0080},		//70000B8A//AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset                      
{0x0F12, 0x0180},		//70000B8C//AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H                          
{0x0F12, 0x0A0A},		//70000B8E//AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C                           
{0x0F12, 0x0101},		//70000B90//AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C                       
{0x0F12, 0x121B},		//70000B92//AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh                        
{0x0F12, 0x6024},		//70000B94//AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower                        
{0x0F12, 0x0C0C},		//70000B96//AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise                          
{0x0F12, 0xFFFF},		//70000B98//AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp                        
{0x0F12, 0x0808},		//70000B9A//AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope                   
{0x0F12, 0x0A01},		//70000B9C//AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin                  
{0x0F12, 0x010A},		//70000B9E//AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin                 
{0x0F12, 0x0001},		//70000BA0//AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin                
{0x0F12, 0x2400},		//70000BA2//AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin                
{0x0F12, 0x0460},		//70000BA4//AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin                 
{0x0F12, 0xFF04},		//70000BA6//AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin                 
{0x0F12, 0x40FF},		//70000BA8//AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin            
{0x0F12, 0x0009},		//70000BAA//AFIT8_ee_iReduceEdgeSlope_Bin [7:0]                                             
{0x0F12, 0x0001},		//70000BAC//AFITB_bnr_nClustLevel_C      [0]                                                
                                                                                                        
{0x0F12, 0x0000},		//70000BAE//AFIT16_BRIGHTNESS                                                               
{0x0F12, 0x0000},		//70000BB0//AFIT16_CONTRAST                                                                 
{0x0F12, 0x0000},		//70000BB2//AFIT16_SATURATION                                                               
{0x0F12, 0x0000},		//70000BB4//AFIT16_SHARP_BLUR                                                               
{0x0F12, 0x0000},		//70000BB6//AFIT16_GLAMOUR                                                                  
{0x0F12, 0x00C0},		//70000BB8//AFIT16_bnr_edge_high                                                            
{0x0F12, 0x0064},		//70000BBA//AFIT16_postdmsc_iLowBright                                                      
{0x0F12, 0x0384},		//70000BBC//AFIT16_postdmsc_iHighBright                                                     
{0x0F12, 0x0032},		//70000BBE//AFIT16_postdmsc_iLowSat                                                         
{0x0F12, 0x01F4},		//70000BC0//AFIT16_postdmsc_iHighSat                                                        
{0x0F12, 0x0070},		//70000BC2//AFIT16_postdmsc_iTune                                                           
{0x0F12, 0x0040},		//70000BC4//AFIT16_yuvemix_mNegRanges_0                                                     
{0x0F12, 0x00A0},		//70000BC6//AFIT16_yuvemix_mNegRanges_1                                                     
{0x0F12, 0x0100},		//70000BC8//AFIT16_yuvemix_mNegRanges_2                                                     
{0x0F12, 0x0010},		//70000BCA//AFIT16_yuvemix_mPosRanges_0                                                     
{0x0F12, 0x0060},		//70000BCC//AFIT16_yuvemix_mPosRanges_1                                                     
{0x0F12, 0x0100},		//70000BCE//AFIT16_yuvemix_mPosRanges_2                                                     
{0x0F12, 0x1430},		//70000BD0//AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh                                 
{0x0F12, 0x0201},		//70000BD2//AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh                            
{0x0F12, 0x0204},		//70000BD4//AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh                       
{0x0F12, 0x1504},		//70000BD6//AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low                           
{0x0F12, 0x030F},		//70000BD8//AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low                          
{0x0F12, 0x0003},		//70000BDA//AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin                       
{0x0F12, 0x0902},		//70000BDC//AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow                         
{0x0F12, 0x2004},		//70000BDE//AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH                    
{0x0F12, 0x0050},		//70000BE0//AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune                     
{0x0F12, 0x1140},		//70000BE2//AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh                   
{0x0F12, 0x201C},		//70000BE4//AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh             
{0x0F12, 0x0620},		//70000BE6//AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed              
{0x0F12, 0x0306},		//70000BE8//AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh                
{0x0F12, 0x2003},		//70000BEA//AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH                       
{0x0F12, 0xFF01},		//70000BEC//AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit                  
{0x0F12, 0x0404},		//70000BEE//AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2                       
{0x0F12, 0x0300},		//70000BF0//AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower                            
{0x0F12, 0x145A},		//70000BF2//AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow                             
{0x0F12, 0x1010},		//70000BF4//AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow                              
{0x0F12, 0x000B},		//70000BF6//AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow                                 
{0x0F12, 0x1000},		//70000BF8//AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower                                 
{0x0F12, 0x5A0F},		//70000BFA//AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit                            
{0x0F12, 0x0503},		//70000BFC//AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope                         
{0x0F12, 0x1802},		//70000BFE//AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR                                 
{0x0F12, 0x0000},		//70000C00//AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres                           
{0x0F12, 0x2006},		//70000C02//AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR                           
{0x0F12, 0x3C28},		//70000C04//AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen                            
{0x0F12, 0x042C},		//70000C06//AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh                                  
{0x0F12, 0x0101},		//70000C08//AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative                            
{0x0F12, 0xFF00},		//70000C0A//AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle                           
{0x0F12, 0x0904},		//70000C0C//AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh                        
{0x0F12, 0x4008},		//70000C0E//AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh                         
{0x0F12, 0x0540},		//70000C10//AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange                         
{0x0F12, 0x8006},		//70000C12//AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad                         
{0x0F12, 0x0020},		//70000C14//AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal                          
{0x0F12, 0x0000},		//70000C16//AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh                   
{0x0F12, 0x2000},		//70000C18//AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat                       
{0x0F12, 0x0000},		//70000C1A//AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit                    
{0x0F12, 0x1E10},		//70000C1C//AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff                           
{0x0F12, 0x000B},		//70000C1E//AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0                     
{0x0F12, 0x0607},		//70000C20//AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2                   
{0x0F12, 0x0005},		//70000C22//AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0                   
{0x0F12, 0x0607},		//70000C24//AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2                   
{0x0F12, 0x0405},		//70000C26//AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY                    
{0x0F12, 0x0206},		//70000C28//AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm                     
{0x0F12, 0x0304},		//70000C2A//AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm                     
{0x0F12, 0x0409},		//70000C2C//AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift                   
{0x0F12, 0x0305},		//70000C2E//AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y                
{0x0F12, 0x0406},		//70000C30//AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y             
{0x0F12, 0x2804},		//70000C32//AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV            
{0x0F12, 0x0228},		//70000C34//AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y             
{0x0F12, 0x1402},		//70000C36//AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV              
{0x0F12, 0x0618},		//70000C38//AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL              
{0x0F12, 0x1A02},		//70000C3A//AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL              
{0x0F12, 0x8018},		//70000C3C//AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower              
{0x0F12, 0x0080},		//70000C3E//AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce                  
{0x0F12, 0x0080},		//70000C40//AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset                      
{0x0F12, 0x0180},		//70000C42//AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H                          
{0x0F12, 0x0A0A},		//70000C44//AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C                           
{0x0F12, 0x0101},		//70000C46//AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C                       
{0x0F12, 0x0F15},		//70000C48//AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh                        
{0x0F12, 0x6024},		//70000C4A//AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower                        
{0x0F12, 0x0A0A},		//70000C4C//AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise                          
{0x0F12, 0xFFFF},		//70000C4E//AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp                        
{0x0F12, 0x0808},		//70000C50//AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope                   
{0x0F12, 0x0A01},		//70000C52//AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin                  
{0x0F12, 0x010A},		//70000C54//AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin                 
{0x0F12, 0x0001},		//70000C56//AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin                
{0x0F12, 0x2400},		//70000C58//AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin                
{0x0F12, 0x0260},		//70000C5A//AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin                 
{0x0F12, 0xFF02},		//70000C5C//AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin                 
{0x0F12, 0x40FF},		//70000C5E//AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin            
{0x0F12, 0x0009},		//70000C60//AFIT8_ee_iReduceEdgeSlope_Bin [7:0]                                             
{0x0F12, 0x0001},		//70000C62//AFITB_bnr_nClustLevel_C      [0]                                                
                                                                                                        
{0x0F12, 0x0000},		//70000C64//AFIT16_BRIGHTNESS                                                               
{0x0F12, 0x0000},		//70000C66//AFIT16_CONTRAST                                                                 
{0x0F12, 0x0000},		//70000C68//AFIT16_SATURATION                                                               
{0x0F12, 0x0000},		//70000C6A//AFIT16_SHARP_BLUR                                                               
{0x0F12, 0x0000},		//70000C6C//AFIT16_GLAMOUR                                                                  
{0x0F12, 0x00C0},		//70000C6E//AFIT16_bnr_edge_high                                                            
{0x0F12, 0x0064},		//70000C70//AFIT16_postdmsc_iLowBright                                                      
{0x0F12, 0x0384},		//70000C72//AFIT16_postdmsc_iHighBright                                                     
{0x0F12, 0x0032},		//70000C74//AFIT16_postdmsc_iLowSat                                                         
{0x0F12, 0x01F4},		//70000C76//AFIT16_postdmsc_iHighSat                                                        
{0x0F12, 0x0070},		//70000C78//AFIT16_postdmsc_iTune                                                           
{0x0F12, 0x0040},		//70000C7A//AFIT16_yuvemix_mNegRanges_0                                                     
{0x0F12, 0x00A0},		//70000C7C//AFIT16_yuvemix_mNegRanges_1                                                     
{0x0F12, 0x0100},		//70000C7E//AFIT16_yuvemix_mNegRanges_2                                                     
{0x0F12, 0x0010},		//70000C80//AFIT16_yuvemix_mPosRanges_0                                                     
{0x0F12, 0x0060},		//70000C82//AFIT16_yuvemix_mPosRanges_1                                                     
{0x0F12, 0x0100},		//70000C84//AFIT16_yuvemix_mPosRanges_2                                                     
{0x0F12, 0x1430},		//70000C86//AFIT8_bnr_edge_low  [7:0] AFIT8_bnr_repl_thresh                                 
{0x0F12, 0x0201},		//70000C88//AFIT8_bnr_repl_force  [7:0] AFIT8_bnr_iHotThreshHigh                            
{0x0F12, 0x0204},		//70000C8A//AFIT8_bnr_iHotThreshLow   [7:0] AFIT8_bnr_iColdThreshHigh                       
{0x0F12, 0x0F04},		//70000C8C//AFIT8_bnr_iColdThreshLow   [7:0] AFIT8_bnr_DispTH_Low                           
{0x0F12, 0x030C},		//70000C8E//AFIT8_bnr_DispTH_High   [7:0] AFIT8_bnr_DISP_Limit_Low                          
{0x0F12, 0x0003},		//70000C90//AFIT8_bnr_DISP_Limit_High   [7:0] AFIT8_bnr_iDistSigmaMin                       
{0x0F12, 0x0602},		//70000C92//AFIT8_bnr_iDistSigmaMax   [7:0] AFIT8_bnr_iDiffSigmaLow                         
{0x0F12, 0x1803},		//70000C94//AFIT8_bnr_iDiffSigmaHigh   [7:0] AFIT8_bnr_iNormalizedSTD_TH                    
{0x0F12, 0x0040},		//70000C96//AFIT8_bnr_iNormalizedSTD_Limit   [7:0] AFIT8_bnr_iDirNRTune                     
{0x0F12, 0x0E20},		//70000C98//AFIT8_bnr_iDirMinThres   [7:0] AFIT8_bnr_iDirFltDiffThresHigh                   
{0x0F12, 0x2018},		//70000C9A//AFIT8_bnr_iDirFltDiffThresLow   [7:0] AFIT8_bnr_iDirSmoothPowerHigh             
{0x0F12, 0x0620},		//70000C9C//AFIT8_bnr_iDirSmoothPowerLow   [7:0] AFIT8_bnr_iLowMaxSlopeAllowed              
{0x0F12, 0x0306},		//70000C9E//AFIT8_bnr_iHighMaxSlopeAllowed   [7:0] AFIT8_bnr_iLowSlopeThresh                
{0x0F12, 0x2003},		//70000CA0//AFIT8_bnr_iHighSlopeThresh   [7:0] AFIT8_bnr_iSlopenessTH                       
{0x0F12, 0xFF01},		//70000CA2//AFIT8_bnr_iSlopeBlurStrength   [7:0] AFIT8_bnr_iSlopenessLimit                  
{0x0F12, 0x0404},		//70000CA4//AFIT8_bnr_AddNoisePower1   [7:0] AFIT8_bnr_AddNoisePower2                       
{0x0F12, 0x0200},		//70000CA6//AFIT8_bnr_iRadialTune   [7:0] AFIT8_bnr_iRadialPower                            
{0x0F12, 0x145A},		//70000CA8//AFIT8_bnr_iRadialLimit   [7:0] AFIT8_ee_iFSMagThLow                             
{0x0F12, 0x1010},		//70000CAA//AFIT8_ee_iFSMagThHigh   [7:0] AFIT8_ee_iFSVarThLow                              
{0x0F12, 0x000B},		//70000CAC//AFIT8_ee_iFSVarThHigh   [7:0] AFIT8_ee_iFSThLow                                 
{0x0F12, 0x1200},		//70000CAE//AFIT8_ee_iFSThHigh   [7:0] AFIT8_ee_iFSmagPower                                 
{0x0F12, 0x5A0F},		//70000CB0//AFIT8_ee_iFSVarCountTh   [7:0] AFIT8_ee_iRadialLimit                            
{0x0F12, 0x0502},		//70000CB2//AFIT8_ee_iRadialPower   [7:0] AFIT8_ee_iSmoothEdgeSlope                         
{0x0F12, 0x1802},		//70000CB4//AFIT8_ee_iROADThres   [7:0] AFIT8_ee_iROADMaxNR                                 
{0x0F12, 0x0000},		//70000CB6//AFIT8_ee_iROADSubMaxNR   [7:0] AFIT8_ee_iROADSubThres                           
{0x0F12, 0x2006},		//70000CB8//AFIT8_ee_iROADNeiThres   [7:0] AFIT8_ee_iROADNeiMaxNR                           
{0x0F12, 0x4028},		//70000CBA//AFIT8_ee_iSmoothEdgeThres   [7:0] AFIT8_ee_iMSharpen                            
{0x0F12, 0x0430},		//70000CBC//AFIT8_ee_iWSharpen   [7:0] AFIT8_ee_iMShThresh                                  
{0x0F12, 0x0101},		//70000CBE//AFIT8_ee_iWShThresh   [7:0] AFIT8_ee_iReduceNegative                            
{0x0F12, 0xFF00},		//70000CC0//AFIT8_ee_iEmbossCentAdd   [7:0] AFIT8_ee_iShDespeckle                           
{0x0F12, 0x0804},		//70000CC2//AFIT8_ee_iReduceEdgeThresh   [7:0] AFIT8_dmsc_iEnhThresh                        
{0x0F12, 0x4008},		//70000CC4//AFIT8_dmsc_iDesatThresh   [7:0] AFIT8_dmsc_iDemBlurHigh                         
{0x0F12, 0x0540},		//70000CC6//AFIT8_dmsc_iDemBlurLow   [7:0] AFIT8_dmsc_iDemBlurRange                         
{0x0F12, 0x8006},		//70000CC8//AFIT8_dmsc_iDecisionThresh   [7:0] AFIT8_dmsc_iCentGrad                         
{0x0F12, 0x0020},		//70000CCA//AFIT8_dmsc_iMonochrom   [7:0] AFIT8_dmsc_iGBDenoiseVal                          
{0x0F12, 0x0000},		//70000CCC//AFIT8_dmsc_iGRDenoiseVal   [7:0] AFIT8_dmsc_iEdgeDesatThrHigh                   
{0x0F12, 0x2000},		//70000CCE//AFIT8_dmsc_iEdgeDesatThrLow   [7:0] AFIT8_dmsc_iEdgeDesat                       
{0x0F12, 0x0000},		//70000CD0//AFIT8_dmsc_iNearGrayDesat   [7:0] AFIT8_dmsc_iEdgeDesatLimit                    
{0x0F12, 0x1E10},		//70000CD2//AFIT8_postdmsc_iBCoeff   [7:0] AFIT8_postdmsc_iGCoeff                           
{0x0F12, 0x000B},		//70000CD4//AFIT8_postdmsc_iWideMult   [7:0] AFIT8_yuvemix_mNegSlopes_0                     
{0x0F12, 0x0607},		//70000CD6//AFIT8_yuvemix_mNegSlopes_1   [7:0] AFIT8_yuvemix_mNegSlopes_2                   
{0x0F12, 0x0005},		//70000CD8//AFIT8_yuvemix_mNegSlopes_3   [7:0] AFIT8_yuvemix_mPosSlopes_0                   
{0x0F12, 0x0607},		//70000CDA//AFIT8_yuvemix_mPosSlopes_1   [7:0] AFIT8_yuvemix_mPosSlopes_2                   
{0x0F12, 0x0405},		//70000CDC//AFIT8_yuvemix_mPosSlopes_3   [7:0] AFIT8_yuviirnr_iXSupportY                    
{0x0F12, 0x0205},		//70000CDE//AFIT8_yuviirnr_iXSupportUV   [7:0] AFIT8_yuviirnr_iLowYNorm                     
{0x0F12, 0x0304},		//70000CE0//AFIT8_yuviirnr_iHighYNorm   [7:0] AFIT8_yuviirnr_iLowUVNorm                     
{0x0F12, 0x0409},		//70000CE2//AFIT8_yuviirnr_iHighUVNorm   [7:0] AFIT8_yuviirnr_iYNormShift                   
{0x0F12, 0x0306},		//70000CE4//AFIT8_yuviirnr_iUVNormShift   [7:0] AFIT8_yuviirnr_iVertLength_Y                
{0x0F12, 0x0407},		//70000CE6//AFIT8_yuviirnr_iVertLength_UV   [7:0] AFIT8_yuviirnr_iDiffThreshL_Y             
{0x0F12, 0x2C04},		//70000CE8//AFIT8_yuviirnr_iDiffThreshH_Y   [7:0] AFIT8_yuviirnr_iDiffThreshL_UV            
{0x0F12, 0x022C},		//70000CEA//AFIT8_yuviirnr_iDiffThreshH_UV   [7:0] AFIT8_yuviirnr_iMaxThreshL_Y             
{0x0F12, 0x1402},		//70000CEC//AFIT8_yuviirnr_iMaxThreshH_Y   [7:0] AFIT8_yuviirnr_iMaxThreshL_UV              
{0x0F12, 0x0618},		//70000CEE//AFIT8_yuviirnr_iMaxThreshH_UV   [7:0] AFIT8_yuviirnr_iYNRStrengthL              
{0x0F12, 0x1A02},		//70000CF0//AFIT8_yuviirnr_iYNRStrengthH   [7:0] AFIT8_yuviirnr_iUVNRStrengthL              
{0x0F12, 0x8018},		//70000CF2//AFIT8_yuviirnr_iUVNRStrengthH   [7:0] AFIT8_byr_gras_iShadingPower              
{0x0F12, 0x0080},		//70000CF4//AFIT8_RGBGamma2_iLinearity   [7:0] AFIT8_RGBGamma2_iDarkReduce                  
{0x0F12, 0x0080},		//70000CF6//AFIT8_ccm_oscar_iSaturation   [7:0] AFIT8_RGB2YUV_iYOffset                      
{0x0F12, 0x0180},		//70000CF8//AFIT8_RGB2YUV_iRGBGain   [7:0] AFIT8_bnr_nClustLevel_H                          
{0x0F12, 0x0A0A},		//70000CFA//AFIT8_bnr_iClustMulT_H   [7:0] AFIT8_bnr_iClustMulT_C                           
{0x0F12, 0x0101},		//70000CFC//AFIT8_bnr_iClustThresh_H   [7:0] AFIT8_bnr_iClustThresh_C                       
{0x0F12, 0x0C0F},		//70000CFE//AFIT8_bnr_iDenThreshLow   [7:0] AFIT8_bnr_iDenThreshHigh                        
{0x0F12, 0x6024},		//70000D00//AFIT8_ee_iLowSharpPower   [7:0] AFIT8_ee_iHighSharpPower                        
{0x0F12, 0x0808},		//70000D02//AFIT8_ee_iLowShDenoise   [7:0] AFIT8_ee_iHighShDenoise                          
{0x0F12, 0xFFFF},		//70000D04//AFIT8_ee_iLowSharpClamp   [7:0] AFIT8_ee_iHighSharpClamp                        
{0x0F12, 0x0808},		//70000D06//AFIT8_ee_iReduceEdgeMinMult   [7:0] AFIT8_ee_iReduceEdgeSlope                   
{0x0F12, 0x0A01},		//70000D08//AFIT8_bnr_nClustLevel_H_Bin   [7:0] AFIT8_bnr_iClustMulT_H_Bin                  
{0x0F12, 0x010A},		//70000D0A//AFIT8_bnr_iClustMulT_C_Bin   [7:0] AFIT8_bnr_iClustThresh_H_Bin                 
{0x0F12, 0x0001},		//70000D0C//AFIT8_bnr_iClustThresh_C_Bin   [7:0] AFIT8_bnr_iDenThreshLow_Bin                
{0x0F12, 0x2400},		//70000D0E//AFIT8_bnr_iDenThreshHigh_Bin   [7:0] AFIT8_ee_iLowSharpPower_Bin                
{0x0F12, 0x0060},		//70000D10//AFIT8_ee_iHighSharpPower_Bin   [7:0] AFIT8_ee_iLowShDenoise_Bin                 
{0x0F12, 0xFF00},		//70000D12//AFIT8_ee_iHighShDenoise_Bin   [7:0] AFIT8_ee_iLowSharpClamp_Bin                 
{0x0F12, 0x40FF},		//70000D14//AFIT8_ee_iHighSharpClamp_Bin   [7:0] AFIT8_ee_iReduceEdgeMinMult_Bin            
{0x0F12, 0x0009},		//70000D16//AFIT8_ee_iReduceEdgeSlope_Bin [7:0]                                             
{0x0F12, 0x0001},		//70000D18//AFITB_bnr_nClustLevel_C      [0]                                                
                                                                                                        
{0x0F12, 0x23CE},		//70000D19//ConstAfitBaseVals                                                               
{0x0F12, 0xFDC8},		//70000D1A//ConstAfitBaseVals                                                               
{0x0F12, 0x112E},		//70000D1B//ConstAfitBaseVals                                                               
{0x0F12, 0x93A5},		//70000D1C//ConstAfitBaseVals                                                               
{0x0F12, 0xFE67},		//70000D1D//ConstAfitBaseVals                                                               
{0x0F12, 0x0000},		//70000D1E//ConstAfitBaseVals                                                               

//==================================================================================
// 10.Clock Setting
//==================================================================================

//Input Clock (Mclk)	
{0x002A, 0x01F8},
{0x0F12, 0x6590},	//REG_TC_IPRM_InClockLSBs
{0x002A, 0x0212},
{0x0F12, 0x0000},	//REG_TC_IPRM_UseNPviClocks          
{0x0F12, 0x0002},	//REG_TC_IPRM_UseNMipiClocks         
{0x0F12, 0x0002},	//REG_TC_IPRM_NumberOfMipiLanes

{0x002A, 0x1780},                                                                                    
{0x0F12, 0x0101}, //oif_usMipiCapturePreviewVirtualChannel, [15:8] : for capture, [7:0] : for preview

//System Clock & Output clock (Pclk)//

{0x002A, 0x021A},
{0x0F12, 0x3A98},	//REG_TC_IPRM_OpClk4KHz_0 //               
{0x0F12, 0x2AD8},		//4F1A  //REG_TC_IPRM_MinOutRate4KHz_0 //
{0x0F12, 0x2AD9},		//4F1A  //REG_TC_IPRM_MaxOutRate4KHz_0 //

{0x0F12, 0x34BC},	//REG_TC_IPRM_OpClk4KHz_1 
{0x0F12, 0x4C2C}, 	//REG_TC_IPRM_MinOutRate4KHz_1
{0x0F12, 0x4C2C}, 	//REG_TC_IPRM_MaxOutRate4KHz_1	

//==================================================================================
// 18.JPEG Thumnail Setting
//==================================================================================
	
//{0x002A, 0x0478},	
//{0x0F12, 0x005F},	//REG_TC_BRC_usPrevQuality    
//{0x0F12, 0x005F},	//REG_TC_BRC_usCaptureQuality 
//{0x0F12, 0x0001},	//REG_TC_THUMB_Thumb_bActive  
//{0x0F12, 0x0280},	//REG_TC_THUMB_Thumb_uWidth   
//{0x0F12, 0x01E0},	//REG_TC_THUMB_Thumb_uHeight  
//{0x0F12, 0x0005},	//REG_TC_THUMB_Thumb_Format   
	
//{0x002A, 0x17DC},	
//{0x0F12, 0x0054},	//jpeg_ManualMBCV                
//{0x002A, 0x1AE4},	                                 
//{0x0F12, 0x001C},	//senHal_bExtraAddLine           
//{0x002A, 0x0284},	                                 
//{0x0F12, 0x0001},	//REG_TC_GP_bBypassScalerJpg     
//{0x002A, 0x028A},	                                 
//{0x0F12, 0x0000},	//REG_TC_GP_bUse1FrameCaptureMode

//{0x002A, 0x1CC2},	//DRx_uDRxWeight for AutoCont function  
//{0x0F12, 0x0100},                                           
//{0x0F12, 0x0100},                                           
//{0x0F12, 0x0100},                                           
//{0x0F12, 0x0100},                           

//==================================================================================
// 19.Input Size Setting
//==================================================================================
//Input Size	
{0x002A, 0x0250},
{0x0F12, 0x0A00},	//REG_TC_GP_PrevReqInputWidth
{0x0F12, 0x0780},	//REG_TC_GP_PrevReqInputHeight
{0x0F12, 0x0010},	//REG_TC_GP_PrevInputWidthOfs
{0x0F12, 0x000C},	//REG_TC_GP_PrevInputHeightOfs
{0x0F12, 0x0A00},	//REG_TC_GP_CapReqInputWidth
{0x0F12, 0x0780},	//REG_TC_GP_CapReqInputHeight
{0x0F12, 0x0010},	//REG_TC_GP_CapInputWidthOfs
{0x0F12, 0x000C},	//REG_TC_GP_CapInputHeightOfs

{0x002A, 0x0262},
{0x0F12, 0x0001},	//REG_TC_GP_bUseReqInputInPre  
{0x0F12, 0x0001},	//REG_TC_GP_bUseReqInputInCap  

{0x002A, 0x0494},
{0x0F12, 0x0A00},	//REG_TC_PZOOM_ZoomInputWidth    
{0x0F12, 0x0780},	//REG_TC_PZOOM_ZoomInputHeight   
{0x0F12, 0x0000},	//REG_TC_PZOOM_ZoomInputWidthOfs 
{0x0F12, 0x0000},	//REG_TC_PZOOM_ZoomInputHeightOfs
{0x0F12, 0x0A00},	//REG_TC_CZOOM_ZoomInputWidth    
{0x0F12, 0x0780},	//REG_TC_CZOOM_ZoomInputHeight   
{0x0F12, 0x0000},	//REG_TC_CZOOM_ZoomInputWidthOfs 
{0x0F12, 0x0000},	//REG_TC_CZOOM_ZoomInputHeightOfs


//==================================================================================
// 20.Preview & Capture Configration Setting
//==================================================================================
//Preview config[0] 640x480  10‾30fps	
{0x002A, 0x02A6},
{0x0F12, 0x0280},	//REG_0TC_PCFG_usWidth              	
{0x0F12, 0x01E0},	//REG_0TC_PCFG_usHeight             	
{0x0F12, 0x0005},	//REG_0TC_PCFG_Format	                
{0x0F12, 0x2AD9},	//4F1A  //REG_0TC_PCFG_usMaxOut4KHzRate //   	
{0x0F12, 0x2AD8},	//4F1A  //REG_0TC_PCFG_usMinOut4KHzRate //   	
{0x0F12, 0x0100},	//REG_0TC_PCFG_OutClkPerPix88       	
{0x0F12, 0x0300},	//REG_0TC_PCFG_uBpp88               	
{0x0F12, 0x0012},	//REG_0TC_PCFG_PVIMask              	
{0x0F12, 0x0000},	//REG_0TC_PCFG_OIFMask              	
{0x0F12, 0x01E0},	//REG_0TC_PCFG_usJpegPacketSize     	
{0x0F12, 0x0000},	//REG_0TC_PCFG_usJpegTotalPackets   	
{0x0F12, 0x0000},	//REG_0TC_PCFG_uClockInd            	
{0x0F12, 0x0000},	//REG_0TC_PCFG_usFrTimeType         	
{0x0F12, 0x0001},	//REG_0TC_PCFG_FrRateQualityType    	
{0x0F12, 0x03E8},	//REG_0TC_PCFG_usMaxFrTimeMsecMult10	
{0x0F12, 0x014A},	//REG_0TC_PCFG_usMinFrTimeMsecMult10	
{0x002A, 0x02D0},
//{0x0F12, 0x000F},	//REG_0TC_PCFG_uPrevMirror  Flip&Mirror:ON
//{0x0F12, 0x000F},	//REG_0TC_PCFG_uCaptureMirror  Flip&Mirror:ON
{0x0F12, 0x0000},	//REG_0TC_PCFG_uPrevMirror  Flip&Mirror:OFF
{0x0F12, 0x0000},	//REG_0TC_PCFG_uCaptureMirror  Flip&Mirror:OFF

//Capture Config[0] 2560x1920   5‾10fps                           	
{0x002A, 0x0396},                                     	
{0x0F12, 0x0000},	//REG_0TC_CCFG_uCaptureMode         
{0x0F12, 0x0A00},	//REG_0TC_CCFG_usWidth              
{0x0F12, 0x0780},	//REG_0TC_CCFG_usHeight             
{0x0F12, 0x0005},	//REG_0TC_CCFG_Format               
{0x0F12, 0x4C2C},	//REG_0TC_CCFG_usMaxOut4KHzRate     
{0x0F12, 0x4C2C},	//REG_0TC_CCFG_usMinOut4KHzRate     
{0x0F12, 0x0100},	//REG_0TC_CCFG_OutClkPerPix88       
{0x0F12, 0x0300},	//REG_0TC_CCFG_uBpp88               
{0x0F12, 0x0012},	//REG_0TC_CCFG_PVIMask              
{0x0F12, 0x0070},	//REG_0TC_CCFG_OIFMask              
{0x0F12, 0x01E0},	//REG_0TC_CCFG_usJpegPacketSize     
{0x0F12, 0x0000},	//REG_0TC_CCFG_usJpegTotalPackets   
{0x0F12, 0x0001},	//REG_0TC_CCFG_uClockInd            
{0x0F12, 0x0000},	//REG_0TC_CCFG_usFrTimeType         
{0x0F12, 0x0002},	//REG_0TC_CCFG_FrRateQualityType    
{0x0F12, 0x07D0},	//REG_0TC_CCFG_usMaxFrTimeMsecMult10
{0x0F12, 0x03E8},	//REG_0TC_CCFG_usMinFrTimeMsecMult10 


{0x002A, 0x022C},	
{0x0F12, 0x0001, 100},	//REG_TC_IPRM_InitParamsUpdated

// Delay 100ms//
//p100
//===========================================================
// 19.Select Cofigration Display
//===========================================================//
	 //PREVIEW//
{0x002A, 0x0266},
{0x0F12, 0x0000},//REG_TC_GP_ActivePrevConfig //
{0x002A, 0x026A},
{0x0F12, 0x0001},	//REG_TC_GP_PrevOpenAfterChange //

{0x002A, 0x0268},
{0x0F12, 0x0001},	//REG_TC_GP_PrevConfigChanged //
{0x002A, 0x026E},                                          
{0x0F12, 0x0000},       //REG_TC_GP_ActiveCapConfig          
{0x002A, 0x026A},	                                         
{0x0F12, 0x0001},	//REG_TC_GP_CapOpenAfterChange           
{0x002A, 0x0270},
{0x0F12, 0x0001},		//REG_TC_GP_CapConfigChanged //

{0x002A, 0x024E},
{0x0F12, 0x0001},	//REG_TC_GP_NewConfigSync //

{0x002A, 0x023E},
{0x0F12, 0x0001},	//REG_TC_GP_EnablePreview //
{0x0F12, 0x0001},		//REG_TC_GP_EnablePreviewChanged //

{0x0028, 0x7000},
{0x002A, 0x0484},
{0x0F12, 0x0002},		// capture flash on //

{0x002A, 0x183A},
{0x0F12, 0x0001},		// one frame AE //

{0x002A, 0x17F6},
{0x0F12, 0x023C},		//210 258 // AWB R point //
{0x0F12, 0x020C},		//288 228 ->258 -> 208 // AWB B point //

{0x002A, 0x1840},
{0x0F12, 0x0001},	// Fls AE tune start                       
{0x0F12, 0x0100},	// fls_afl_FlsAFIn  Rin                    
{0x0F12, 0x0120},
{0x0F12, 0x0180},
{0x0F12, 0x0200},
{0x0F12, 0x0400},
{0x0F12, 0x0800},
{0x0F12, 0x0A00},
{0x0F12, 0x1000},
{0x0F12, 0x0100},	// fls_afl_FlsAFOut  Rout                  
{0x0F12, 0x00A0},
{0x0F12, 0x0090},
{0x0F12, 0x0080},
{0x0F12, 0x0070},
{0x0F12, 0x0045},
{0x0F12, 0x0030},
{0x0F12, 0x0010},
{0x002A, 0x1884},
{0x0F12, 0x0100},	// fls_afl_FlsNBOut  flash NB default      
{0x0F12, 0x0100},
{0x0F12, 0x0100},
{0x0F12, 0x0100},
{0x0F12, 0x0100},
{0x0F12, 0x0100},
{0x0F12, 0x0100},
{0x0F12, 0x0100},
{0x002A, 0x1826},
{0x0F12, 0x0100},	// fls_afl_FlashWP_Weight  flash NB default
{0x0F12, 0x00C0},
{0x0F12, 0x0080},
{0x0F12, 0x000A},
{0x0F12, 0x0000},
{0x0F12, 0x0030},	// fls_afl_FlashWP_Weight  flash NB default
{0x0F12, 0x0040},
{0x0F12, 0x0048},
{0x0F12, 0x0050},
{0x0F12, 0x0060},
{0x002A, 0x4784},
{0x0F12, 0x00A0},	// TNP_Regs_FlsWeightRIn  weight tune start in    
{0x0F12, 0x00C0},
{0x0F12, 0x00D0},
{0x0F12, 0x0100},
{0x0F12, 0x0200},
{0x0F12, 0x0300},
{0x0F12, 0x0088},	// TNP_Regs_FlsWeightROut  weight tune start out  
{0x0F12, 0x00B0},
{0x0F12, 0x00C0},
{0x0F12, 0x0100},
{0x0F12, 0x0200},
{0x0F12, 0x0300},
{0x002A, 0x479C},
{0x0F12, 0x0120},	//Fls  BRIn
{0x0F12, 0x0150},
{0x0F12, 0x0200},
{0x0F12, 0x003C},	// Fls  BROut
{0x0F12, 0x003B},	    
{0x0F12, 0x0026},	//brightness

//===================================================================================
// 22. ESD Check
//===================================================================================

{0x0028, 0x7000},	                                                                                    
{0x002A, 0x01A8},	//ESD Check                                                                         
{0x0F12, 0xAAAA},

//===================================================================================
// 23. Brightness min/Max
//===================================================================================
{0x0028, 0x147C},
{0x0F12, 0x0180}, //bp_uMaxBrightnessFactor	
{0x0028, 0x1482},
{0x0F12, 0x0180}, //bp_uMinBrightnessFactor	
};

static const reg_value_t g_s5k4ecgx_i2cseq_capture_4to3[] =
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x0258},
{0x0F12, 0x0A00},		//REG_TC_GP_CapReqInputWidth //2560 //
{0x0F12, 0x0780},		//REG_TC_GP_CapReqInputHeight //1920 //
{0x0F12, 0x0010},		//REG_TC_GP_CapInputWidthOfs //(2592-2560)/2 //
{0x0F12, 0x000C},		//REG_TC_GP_CapInputHeightOfs //(1944-1920)/2 //

{0x002A, 0x0264},
{0x0F12, 0x0001},		//REG_TC_GP_bUseReqInputInCap //

{0x002A, 0x049C},
{0x0F12, 0x0A00},		//REG_TC_PZOOM_CapZoomReqInputWidth //2560 //
{0x0F12, 0x0780},		//REG_TC_PZOOM_CapZoomReqInputHeight //1920 //
{0x0F12, 0x0000},		//REG_TC_PZOOM_CapZoomReqInputWidthOfs //
{0x0F12, 0x0000},		//REG_TC_PZOOM_CapZoomReqInputHeightOfs //

//{0x002A, 0x047C},
//{0x0F12, 0x0001},		//REG_TC_THUMB_Thumb_bActive //
//{0x0F12, 0x0280},		//REG_TC_THUMB_Thumb_uWidth //640 //
//{0x0F12, 0x01E0},		//REG_TC_THUMB_Thumb_uHeight //480 //
};

static const reg_value_t g_s5k4ecgx_i2cseq_capture_480p[] =
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x0258},
{0x0F12, 0x0A00},		//REG_TC_GP_CapReqInputWidth //2560 //
{0x0F12, 0x06A8},		//REG_TC_GP_CapReqInputHeight //1704 //
{0x0F12, 0x0010},		//REG_TC_GP_CapInputWidthOfs //(2592-2560)/2 //
{0x0F12, 0x0078},		//REG_TC_GP_CapInputHeightOfs //(1944-1704)/2 //

{0x002A, 0x0264},
{0x0F12, 0x0001},		//REG_TC_GP_bUseReqInputInCap //

{0x002A, 0x049C},
{0x0F12, 0x0A00},		//REG_TC_PZOOM_CapZoomReqInputWidth //2560 //
{0x0F12, 0x06A8},		//REG_TC_PZOOM_CapZoomReqInputHeight //1704 //
{0x0F12, 0x0000},		//REG_TC_PZOOM_CapZoomReqInputWidthOfs //
{0x0F12, 0x0000},		//REG_TC_PZOOM_CapZoomReqInputHeightOfs //

//{0x002A, 0x047C},
//{0x0F12, 0x0001},		//REG_TC_THUMB_Thumb_bActive //
//{0x0F12, 0x0280},		//REG_TC_THUMB_Thumb_uWidth //640 //
//{0x0F12, 0x01E0},		//REG_TC_THUMB_Thumb_uHeight //480 //
};

static const reg_value_t g_s5k4ecgx_i2cseq_capture_720p[] =
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x0258},
{0x0F12, 0x0A00},		//REG_TC_GP_CapReqInputWidth //2560 //
{0x0F12, 0x05A0},		//REG_TC_GP_CapReqInputHeight //1440 //
{0x0F12, 0x0010},		//REG_TC_GP_CapInputWidthOfs //(2592-2560)/2 //
{0x0F12, 0x00FC},		//REG_TC_GP_CapInputHeightOfs //(1944-1440)/2 //

{0x002A, 0x0264},
{0x0F12, 0x0001},		//REG_TC_GP_bUseReqInputInCap //

{0x002A, 0x049C},
{0x0F12, 0x0A00},		//REG_TC_PZOOM_CapZoomReqInputWidth //2560 //
{0x0F12, 0x05A0},		//REG_TC_PZOOM_CapZoomReqInputHeight //1440 //
{0x0F12, 0x0000},		//REG_TC_PZOOM_CapZoomReqInputWidthOfs //
{0x0F12, 0x0000},		//REG_TC_PZOOM_CapZoomReqInputHeightOfs //

//{0x002A, 0x047C},
//{0x0F12, 0x0001},		//REG_TC_THUMB_Thumb_bActive //
//{0x0F12, 0x0280},		//REG_TC_THUMB_Thumb_uWidth //640 //
//{0x0F12, 0x01E0},		//REG_TC_THUMB_Thumb_uHeight //480 //
};

static const reg_value_t g_s5k4ecgx_i2cseq_preview_4to3[] =
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},

{0x002A, 0x18AC},
{0x0F12, 0x0060},		//senHal_uAddColsBin //
{0x0F12, 0x0060},		//senHal_uAddColsNoBin //
{0x0F12, 0x05C0},		//senHal_uMinColsBin //
{0x0F12, 0x05C0},		//senHal_uMinColsNoBin //
{0x002A, 0x0250},
{0x0F12, 0x0A00},		//REG_TC_GP_PrevReqInputWidth //2560 //
{0x0F12, 0x0780},		//REG_TC_GP_PrevReqInputHeight //1920 //
{0x0F12, 0x0010},		//REG_TC_GP_PrevInputWidthOfs/(2592-2560)/2//
{0x0F12, 0x000C},		//REG_TC_GP_PrevInputHeightOfs/(1944-1920)/2//

{0x002A, 0x0262},
{0x0F12, 0x0001},		//REG_TC_GP_bUseReqInputInPre //

{0x002A, 0x0494},
{0x0F12, 0x0A00},		//REG_TC_PZOOM_PrevZoomReqInputWidth //2560 //
{0x0F12, 0x0780},		//REG_TC_PZOOM_PrevZoomReqInputHeight //1920 //
{0x0F12, 0x0000},		//REG_TC_PZOOM_PrevZoomReqInputWidthOfs //
{0x0F12, 0x0000},		//REG_TC_PZOOM_PrevZoomReqInputHeightOfs //

{0x002A, 0x02AB},
{0x0F12, 0x0005},		//REG_0TC_PCFG_Format   05 : yuv (0~255)  06:yuv (16~234) 07: raw 09 : jpeg

{0x002A, 0x02BE},
{0x0F12, 0x0000},		//REG_0TC_PCFG_usFrTimeType //
{0x0F12, 0x0001},		//REG_0TC_PCFG_FrRateQualityType //
{0x0F12, 0x03E8},		//REG_0TC_PCFG_usMaxFrTimeMsecMult10 //03E8h:10fps //
{0x0F12, 0x014A},		//REG_0TC_PCFG_usMinFrTimeMsecMult10 //014Ah:30fps //
};

static const reg_value_t g_s5k4ecgx_i2cseq_preview_quad[] =
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},

{0x002A, 0x18AC},
{0x0F12, 0x0060},		//senHal_uAddColsBin //
{0x0F12, 0x0060},		//senHal_uAddColsNoBin //
{0x0F12, 0x07DC},		//senHal_uMinColsBin //
{0x0F12, 0x05C0},		//senHal_uMinColsNoBin //
{0x002A, 0x0250},
{0x0F12, 0x0A00},		//REG_TC_GP_PrevReqInputWidth //2560 //
{0x0F12, 0x0780},		//REG_TC_GP_PrevReqInputHeight //1920 //
{0x0F12, 0x0010},		//REG_TC_GP_PrevInputWidthOfs/(2592-2560)/2//
{0x0F12, 0x000C},		//REG_TC_GP_PrevInputHeightOfs/(1944-1920)/2//

{0x002A, 0x0262},
{0x0F12, 0x0001},		//REG_TC_GP_bUseReqInputInPre //

{0x002A, 0x0494},
{0x0F12, 0x0A00},		//REG_TC_PZOOM_PrevZoomReqInputWidth //2560 //
{0x0F12, 0x0780},		//REG_TC_PZOOM_PrevZoomReqInputHeight //1920 //
{0x0F12, 0x0000},		//REG_TC_PZOOM_PrevZoomReqInputWidthOfs //
{0x0F12, 0x0000},		//REG_TC_PZOOM_PrevZoomReqInputHeightOfs //

{0x002A, 0x02AB},
{0x0F12, 0x0005},		//REG_0TC_PCFG_Format   05 : yuv (0~255)  06:yuv (16~234) 07: raw 09 : jpeg

{0x002A, 0x02BE},
{0x0F12, 0x0000},		//REG_0TC_PCFG_usFrTimeType //
{0x0F12, 0x0001},		//REG_0TC_PCFG_FrRateQualityType //
{0x0F12, 0x03E8},		//REG_0TC_PCFG_usMaxFrTimeMsecMult10 //03E8h:10fps //
{0x0F12, 0x014A},		//REG_0TC_PCFG_usMinFrTimeMsecMult10 //014Ah:30fps //
};

static const reg_value_t g_s5k4ecgx_i2cseq_preview_480p[] =
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},

{0x002A, 0x18AC},
{0x0F12, 0x0060},		//senHal_uAddColsBin //
{0x0F12, 0x0060},		//senHal_uAddColsNoBin //
{0x0F12, 0x05C0},		//senHal_uMinColsBin //
{0x0F12, 0x05C0},		//senHal_uMinColsNoBin //
{0x002A, 0x0250},
{0x0F12, 0x0A00},		//REG_TC_GP_PrevReqInputWidth //2560 //
{0x0F12, 0x06A8},		//REG_TC_GP_PrevReqInputHeight //1704 //
{0x0F12, 0x0010},		//REG_TC_GP_PrevInputWidthOfs/(2592-2560)/2//
{0x0F12, 0x0078},		//REG_TC_GP_PrevInputHeightOfs/(1944-1704)/2//

{0x002A, 0x0262},
{0x0F12, 0x0001},		//REG_TC_GP_bUseReqInputInPre //

{0x002A, 0x0494},
{0x0F12, 0x0A00},		//REG_TC_PZOOM_PrevZoomReqInputWidth //2560 //
{0x0F12, 0x06A8},		//REG_TC_PZOOM_PrevZoomReqInputHeight //1704 //
{0x0F12, 0x0000},		//REG_TC_PZOOM_PrevZoomReqInputWidthOfs //
{0x0F12, 0x0000},		//REG_TC_PZOOM_PrevZoomReqInputHeightOfs //

{0x002A, 0x02AB},
{0x0F12, 0x0005},		//REG_0TC_PCFG_Format   05 : yuv (0~255)  06:yuv (16~234) 07: raw 09 : jpeg

{0x002A, 0x02BE},
{0x0F12, 0x0000},		//REG_0TC_PCFG_usFrTimeType //
{0x0F12, 0x0001},		//REG_0TC_PCFG_FrRateQualityType //
{0x0F12, 0x03E8},		//REG_0TC_PCFG_usMaxFrTimeMsecMult10 //03E8h:10fps //
{0x0F12, 0x014A},		//REG_0TC_PCFG_usMinFrTimeMsecMult10 //014Ah:30fps //
};

static const reg_value_t g_s5k4ecgx_i2cseq_preview_720p[] =
{
{0xFCFC, 0xD000},
{0x0028, 0x7000},

{0x002A, 0x18AC},
{0x0F12, 0x0060},		//senHal_uAddColsBin //
{0x0F12, 0x0060},		//senHal_uAddColsNoBin //
{0x0F12, 0x07DC},		//senHal_uMinColsBin //
{0x0F12, 0x05C0},		//senHal_uMinColsNoBin //

{0x002A, 0x0250},
{0x0F12, 0x0A00},		//REG_TC_GP_PrevReqInputWidth //2560 //
{0x0F12, 0x05A0},		//REG_TC_GP_PrevReqInputHeight //1440 //
{0x0F12, 0x0010},		//REG_TC_GP_PrevInputWidthOfs/(2592-2560)/2//
{0x0F12, 0x00FC},		//REG_TC_GP_PrevInputHeightOfs/(1944-1440)/2//

{0x002A, 0x0262},
{0x0F12, 0x0001},		//REG_TC_GP_bUseReqInputInPre //

{0x002A, 0x0494},
{0x0F12, 0x0A00},		//REG_TC_PZOOM_PrevZoomReqInputWidth //2560 //
{0x0F12, 0x05A0},		//REG_TC_PZOOM_PrevZoomReqInputHeight //1440 //
{0x0F12, 0x0000},		//REG_TC_PZOOM_PrevZoomReqInputWidthOfs //
{0x0F12, 0x0000},		//REG_TC_PZOOM_PrevZoomReqInputHeightOfs //

{0x002A, 0x02AB},
{0x0F12, 0x0005},		//REG_0TC_PCFG_Format   05 : yuv (0~255)  06:yuv (16~234) 07: raw 09 : jpeg

{0x002A, 0x02BE},
{0x0F12, 0x0000},		//REG_0TC_PCFG_usFrTimeType //
{0x0F12, 0x0001},		//REG_0TC_PCFG_FrRateQualityType //
{0x0F12, 0x03E8},		//REG_0TC_PCFG_usMaxFrTimeMsecMult10 //03E8h:10fps //
{0x0F12, 0x014A},		//REG_0TC_PCFG_usMinFrTimeMsecMult10 //014Ah:30fps //
};

/*
// FIXME
static const reg_value_t g_s5k4ecgx_i2cseq_preview_1080p[] =
{
{0xFCFC, 0xD000},
{0x0028, 0xD000},
{0x002A, 0xE410},
{0x0F12, 0x3E01},	

{0x0028, 0x7000},
{0x002A, 0x18AC},
{0x0F12, 0x0060},		//senHal_uAddColsBin //
{0x0F12, 0x0060},		//senHal_uAddColsNoBin //
//{0x0F12, 0x07DC},		//senHal_uMinColsBin //
{0x0F12, 0x05C0},		//senHal_uMinColsBin //
{0x0F12, 0x05C0},		//senHal_uMinColsNoBin //

{0x002A, 0x0250},
{0x0F12, 0x0A00},		//REG_TC_GP_PrevReqInputWidth //2560 //
{0x0F12, 0x05A0},		//REG_TC_GP_PrevReqInputHeight //1440 //
{0x0F12, 0x0010},		//REG_TC_GP_PrevInputWidthOfs/(2592-2560)/2//
//{0x0F12, 0x00FC},		//REG_TC_GP_PrevInputHeightOfs/(1944-1440)/2//
{0x0F12, 0x00F0},		//REG_TC_GP_PrevInputHeightOfs/(1944-1440)/2//
{0x0F12, 0x0A00},		//REG_TC_GP_CapReqInputWidth //2560 //
{0x0F12, 0x05A0},		//REG_TC_GP_CapReqInputHeight //1440 //
{0x0F12, 0x0010},		//REG_TC_GP_CapInputWidthOfs/(2592-2560)/2//
{0x0F12, 0x00F0},		//REG_TC_GP_CapInputHeightOfs/(1944-1440)/2//

{0x002A, 0x0262},
{0x0F12, 0x0001},		//REG_TC_GP_bUseReqInputInPre //
{0x0F12, 0x0001},		//REG_TC_GP_bUseReqInputInCap //

{0x002A, 0x0494},
{0x0F12, 0x0A00},		//REG_TC_PZOOM_PrevZoomReqInputWidth //2560 //
{0x0F12, 0x05A0},		//REG_TC_PZOOM_PrevZoomReqInputHeight //1440 //
{0x0F12, 0x0000},		//REG_TC_PZOOM_PrevZoomReqInputWidthOfs //
{0x0F12, 0x0000},		//REG_TC_PZOOM_PrevZoomReqInputHeightOfs //
{0x0F12, 0x0A00},		//REG_TC_PZOOM_CapZoomReqInputWidth //2560 //
{0x0F12, 0x05A0},		//REG_TC_PZOOM_CapZoomReqInputHeight //1440 //
{0x0F12, 0x0000},		//REG_TC_PZOOM_CapZoomReqInputWidthOfs //
{0x0F12, 0x0000},		//REG_TC_PZOOM_CapZoomReqInputHeightOfs //

{0x002A, 0x02AB},
{0x0F12, 0x0006},		//REG_0TC_PCFG_Format   05 : yuv (0~255)  06:yuv (16~234) 07: raw 09 : jpeg

{0x002A, 0x02BE},
{0x0F12, 0x0000},		//REG_0TC_PCFG_usFrTimeType //
//{0x0F12, 0x0001},		//REG_0TC_PCFG_FrRateQualityType //
{0x0F12, 0x0002},		//REG_0TC_PCFG_FrRateQualityType // 1: binning, 2: No binning
//{0x0F12, 0x01A4},		//REG_0TC_PCFG_usMaxFrTimeMsecMult10 //014Ah:30fps
{0x0F12, 0x03E8},		//REG_0TC_PCFG_usMaxFrTimeMsecMult10 //03E8h:10fps
//{0x0F12, 0x014A},		//REG_0TC_PCFG_usMinFrTimeMsecMult10 //014Ah:30fps
{0x0F12, 0x03E8},		//REG_0TC_PCFG_usMinFrTimeMsecMult10 //02E8h:10fps
};
*/

static const reg_value_t g_s5k4ecgx_i2cseq_af_normal[] = {
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x028E},
{0x0F12, 0x0000},

{0x0028, 0x7000},
{0x002A, 0x028C},
{0x0F12, 0x0004, 10},

//delay 10ms

{0x0028, 0x7000},
{0x002A, 0x1648},
{0x0F12, 0x9002},

{0x002A, 0x15E8},
{0x0F12, 0x0015},   //af_pos_usTableLastInd
{0x0F12, 0x0032},
{0x0F12, 0x0038},
{0x0F12, 0x003E},
{0x0F12, 0x0044},
{0x0F12, 0x004A},
{0x0F12, 0x0050},
{0x0F12, 0x0056},
{0x0F12, 0x005C},
{0x0F12, 0x0062},
{0x0F12, 0x0068},
{0x0F12, 0x006E},
{0x0F12, 0x0074},
{0x0F12, 0x007A},
{0x0F12, 0x0080},
{0x0F12, 0x0086},
{0x0F12, 0x008C},
{0x0F12, 0x0092},
{0x0F12, 0x0098},
{0x0F12, 0x009E},
{0x0F12, 0x00A4},
{0x0F12, 0x00AA},
{0x0F12, 0x00B0},

{0x0028, 0x7000},
{0x002A, 0x1648},
{0x0F12, 0x9002},
};

static const reg_value_t g_s5k4ecgx_i2cseq_af_macro[] = {
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x028E},
{0x0F12, 0x00D0},

{0x0028, 0x7000},
{0x002A, 0x028C},
{0x0F12, 0x0004, 10},

//delay 10ms

{0x0028, 0x7000},
{0x002A, 0x1648},
{0x0F12, 0x9042},	

{0x002A, 0x15E8},
{0x0F12, 0x0015},   //af_pos_usTableLastInd
{0x0F12, 0x0032},
{0x0F12, 0x0038},
{0x0F12, 0x003E},
{0x0F12, 0x0044},
{0x0F12, 0x004A},
{0x0F12, 0x0050},
{0x0F12, 0x0056},
{0x0F12, 0x005C},
{0x0F12, 0x0062},
{0x0F12, 0x0068},
{0x0F12, 0x006E},
{0x0F12, 0x0074},
{0x0F12, 0x007A},
{0x0F12, 0x0080},
{0x0F12, 0x0086},
{0x0F12, 0x008C},
{0x0F12, 0x0092},
{0x0F12, 0x0098},
{0x0F12, 0x009E},
{0x0F12, 0x00A4},
{0x0F12, 0x00AA},
{0x0F12, 0x00B0},

{0x0028, 0x7000},
{0x002A, 0x1648},
{0x0F12, 0x9042},

{0x002A, 0x15DA},
{0x0F12, 0x1500},
};

static const reg_value_t g_s5k4ecgx_i2cseq_af_fix[] = {
{0xFCFC, 0xD000},
{0x0028, 0x7000},
{0x002A, 0x028E},
//{0x0F12, 0x0010},
{0x0F12, 0x0050},

{0x0028, 0x7000},
{0x002A, 0x028C},
{0x0F12, 0x0004, 10},
};
#endif /* !__S5K4ECGX_H__ */
