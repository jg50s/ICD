#include "StdAfx.h"
#include "CObj_Phy__ROBOT_ATM.h"

#include "Macro_Function.h"


//-------------------------------------------------------------------------
CObj_Phy__ROBOT_ATM::CObj_Phy__ROBOT_ATM()
{

}
CObj_Phy__ROBOT_ATM::~CObj_Phy__ROBOT_ATM()
{

}

//-------------------------------------------------------------------------
int CObj_Phy__ROBOT_ATM::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");
		ADD__CTRL_VAR(sMODE__HOME, "HOME");

		ADD__CTRL_VAR(sMODE__MAINT, "MAINT");

		ADD__CTRL_VAR(sMODE__PICK,   "PICK");
		ADD__CTRL_VAR(sMODE__XPICK,  "XPICK");
		ADD__CTRL_VAR(sMODE__PLACE,  "PLACE");
		ADD__CTRL_VAR(sMODE__XPLACE, "XPLACE");
		ADD__CTRL_VAR(sMODE__ROTATE, "ROTATE");

		ADD__CTRL_VAR(sMODE__SWAP_PMx, "SWAP_PMx");
		ADD__CTRL_VAR(sMODE__SWAP_ALx, "SWAP_ALx" );
		ADD__CTRL_VAR(sMODE__SWAP_LBx, "SWAP_LBx" );
		ADD__CTRL_VAR(sMODE__SWAP_VISx,"SWAP_VISx");

		ADD__CTRL_VAR(sMODE__LP_MAP, "LP_MAP");

		ADD__CTRL_VAR(sMODE__SCH_TEST_CFG, "SCH_TEST.CFG");
	}

	return 1;
}

int CObj_Phy__ROBOT_ATM::__DEFINE__VERSION_HISTORY(version)
{
	version  = "JG.Lee \n";

	return 1;
}


// ...
#define  MON_ID__MODULE_STATUS							1

// ...
#define  APP_DSP__UPPER_MODE							\
"SWAP_LBx  SWAP_VISx  SWAP_ALx "

#define  DSP__MODE										\
"INIT	HOME											\
MAINT	         										\
ROTATE  READY											\
PICK    X_PICK											\
PLACE   X_PLACE											\
SWAP    LP_MAP"

#define  DSP__ARM_TYPE									\
"A    B    C    D										\
AB   BC   CD   AD										\
ABC  BCD  ACD  ABD										\
ABCD													\
UPPER  A_UPPER"

#define  DSP__STATION									\
"AL1  AL2  AL1_AL2										\
SUSCEPTOR1  SUSCEPTOR2									\
LBA  LBB  LBC  LBD										\
LL_TOP  LL_BTM											\
CL1  CL2  CL3  CL4										\
LP1  LP2  LP3  LP4  LP5									\
LA  LB													\
PM1  PM2  PM3  PM4  PM5  PM6  PM7  PM8  PM9  PM10		\
VIS1  VIS1_BUF											\
BUF1  BUF2												\
BUFF1 BUFF2												\
STG1  STG2"

#define  DSP__SLOT										\
"1  2  3  4  5  6  7  8  9 10							\
11 12 13 14 15 16 17 18 19 20							\
21 22 23 24 25 26 27 28 29 30"

#define  DSP__POS										\
"1  2  3  4  5  6  7  8  9 10							\
11 12 13 14 15 16 17 18"

#define  DSP__TRG_MOVE									\
"UNKNOWN HOME READY										\
PM1 PM2 PM3 PM4 PM5 PM6 PM7 PM8 PM9 PM10				\
BUF1 BUF2												\
BUFF1 BUFF2												\
STG1 STG2												\
CL1 CL2 CL3 CL4											\
AL1 AL2 AL1_AL2											\
SUSCEPTOR1  SUSCEPTOR2									\
SLA SLB LA LB									        \
LBA LBB LBC LBD									        \
LBA-1 LBA-2 									        \
LBB-1 LBB-2 									        \
LBC-1 LBC-2 									        \
LBD-1 LBD-2 									        \
LL_TOP  LL_BTM											\
LP1 LP2 LP3 LP4 VIS1 VIS1_BUF"

#define  DSP__TRG_ROTE									\
"UNKNOWN HOME READY										\
PM1 PM2 PM3 PM4 PM5 PM6 PM7 PM8 PM9 PM10				\
BUF1 BUF2												\
BUFF1 BUFF2												\
STG1 STG2												\
CL1 CL2 CL3 CL4											\
AL1 AL2	AL1_AL2											\
SUSCEPTOR1  SUSCEPTOR2									\
SLA SLB LA LB								         	\
LBA LBB LBC LBD									        \
LBA-1 LBA-2 									        \
LBB-1 LBB-2 									        \
LBC-1 LBC-2 									        \
LBD-1 LBD-2 									        \
LL_TOP  LL_BTM											\
LP1 LP2 LP3 LP4 VIS1 VIS1_BUF"

#define  DSP__ARM_ACT									\
"UNKNOWN RETRACT EXTEND"

#define  DSP__ENABLE_DISABLE							\
"ENABLE  DISABLE"


int CObj_Phy__ROBOT_ATM::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString dsc_item_list;
	CString dsc__obj_ctrl;
	CString dsc__obj_sts;

	CString str_name;
	int i;

	// REMOTE CONTROL ...
	{
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_CTRL",    dsc__obj_ctrl);
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_STATUS",  dsc__obj_sts );
		p_variable->Get__STD_DESCRIPTION("STD_SLOT_STATUS", dsc_item_list);
	}

	// SWAP - LBx ...
	{
		iUPPER_OBJ__FLAG = -1;

		str_name = "UPPER.ROBOT.CTRL";
		STD__ADD_DIGITAL(str_name,dsc__obj_ctrl);
		LINK__VAR_DIGITAL_CTRL(xCH__UPPER_OBJ__CTRL,str_name);

		str_name = "UPPER.ROBOT.MODE";
		STD__ADD_DIGITAL(str_name,APP_DSP__UPPER_MODE);
		LINK__VAR_DIGITAL_CTRL(xCH__UPPER_OBJ__MODE,str_name);

		str_name = "UPPER.OBJ.STATUS";
		STD__ADD_DIGITAL(str_name,dsc__obj_sts);
		LINK__VAR_STRING_CTRL(xCH__UPPER_OBJ__STATUS,str_name);

		//
		str_name = "UPPER.PARA.MODULE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__UPPER_OBJ__PARA_MODULE,str_name);

		str_name = "UPPER.PARA.PLACE_ARM";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__UPPER_OBJ__PARA_PLACE_ARM,str_name);

		str_name = "UPPER.PARA.PLACE_SLOT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__UPPER_OBJ__PARA_PLACE_SLOT,str_name);

		str_name = "UPPER.PARA.PICK_ARM";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__UPPER_OBJ__PARA_PICK_ARM,str_name);

		str_name = "UPPER.PARA.PICK_SLOT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__UPPER_OBJ__PARA_PICK_SLOT,str_name);
	}

	// ...
	{
		str_name = "ROBOT.CTRL";
		STD__ADD_DIGITAL(str_name,dsc__obj_ctrl);
		LINK__VAR_DIGITAL_CTRL(xCH__OBJ_CTRL, str_name);

		str_name = "ROBOT.MODE";
		STD__ADD_DIGITAL(str_name, DSP__MODE);
		LINK__VAR_DIGITAL_CTRL(dCH__OBJ_MODE, str_name);

		//
		str_name = "PARA.ARM_TYPE";
		STD__ADD_DIGITAL(str_name, DSP__ARM_TYPE);
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_ARM_TYPE, str_name);

		str_name = "PARA.MODULE";
		STD__ADD_DIGITAL(str_name, DSP__STATION);
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_MODULE, str_name);

		str_name = "PARA.SLOT";
		STD__ADD_DIGITAL(str_name, DSP__SLOT);
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_SLOT, str_name);

		str_name = "PARA.POS";
		STD__ADD_DIGITAL(str_name, DSP__POS);
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_POS, str_name);
	}

	// ALIGN PARAMETER ...
	{
		str_name = "CFG.ALIGN.RETRY";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "count", 0, 1, 5, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ALIGN_RETRY, str_name);

		str_name = "CUR.ALIGN.RETRY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_ALIGN_RETRY, str_name);

		//
		str_name = "TARGET.PMx.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE  ENABLE","");
		LINK__VAR_DIGITAL_CTRL(dCH__TARGET_PMx_MODE, str_name);

		//
		str_name = "TARGET.LLx.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE  ENABLE","");
		LINK__VAR_DIGITAL_CTRL(dCH__TARGET_LLx_MODE, str_name);

		str_name = "TARGET.LLx.SLOT.CHECK";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE  ENABLE","");
		LINK__VAR_DIGITAL_CTRL(dCH__TARGET_LLx_SLOT_CHECK, str_name);

		// ARM_A
		str_name = "TARGET.LLx.NAME.SET_OF_ARM_A";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TARGET_LLx_NAME_SET_OF_ARM_A, str_name);

		str_name = "TARGET.LLx.SLOT.SET_OF_ARM_A";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TARGET_LLx_SLOT_SET_OF_ARM_A, str_name);

		// ARM_B
		str_name = "TARGET.LLx.NAME.SET_OF_ARM_B";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TARGET_LLx_NAME_SET_OF_ARM_B, str_name);

		str_name = "TARGET.LLx.SLOT.SET_OF_ARM_B";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TARGET_LLx_SLOT_SET_OF_ARM_B, str_name);

		//
		str_name = "TARGET.LLx.NAME.SET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TARGET_LLx_NAME_SET_AL, str_name);

		str_name = "TARGET.LLx.SLOT.SET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TARGET_LLx_SLOT_SET_AL, str_name);

		//
		str_name = "TARGET.LLx.NAME.GET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TARGET_LLx_NAME_GET, str_name);

		str_name = "TARGET.LLx.SLOT.GET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TARGET_LLx_SLOT_GET, str_name);

		//
		str_name = "TARGET.LLx.ANGLE.GET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TARGET_LLx_ANGLE_GET, str_name);
	}

	// STATUS ...
	{
		str_name = "OBJ.STATUS";
		STD__ADD_DIGITAL(str_name,dsc__obj_sts);
		LINK__VAR_STRING_CTRL(xCH__OBJ_STATUS,str_name);
	}

	for(i=0; i<CFG_ROBOT__ARM_SIZE; i++)
	{
		int slot_id = i + 1;

		//
		str_name.Format("ARM.SLOT%002d.STATUS",slot_id);
		STD__ADD_DIGITAL(str_name,dsc_item_list);
		LINK__VAR_DIGITAL_CTRL(xCH__SLOT_STATUS[i],str_name);

		str_name.Format("ARM.SLOT%002d.TITLE",slot_id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__SLOT_TITLE[i],str_name);

		str_name.Format("SLOT%002d.MATERIAL_SIZE",slot_id);
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__MATERIAL_SIZE[i],str_name);

		//
		str_name.Format("SLOT%002d.LPx_PTN",slot_id);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SLOT_LPx_PTN[i],str_name);

		str_name.Format("DVID.SLOT%002d.LPx_PTN",slot_id);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__DVID_SLOT_LPx_PTN[i],str_name);

		//
		str_name.Format("SLOT%002d.LPx_STN",slot_id);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SLOT_LPx_STN[i],str_name);

		str_name.Format("DVID.SLOT%002d.LPx_STN",slot_id);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__DVID_SLOT_LPx_STN[i],str_name);

		//
		str_name.Format("SLOT%002d.PPID",slot_id);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SLOT_PPID[i],str_name);

		str_name.Format("DVID.SLOT%002d.PPID",slot_id);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__DVID_SLOT_PPID[i],str_name);

		//
		str_name.Format("SLOT%002d.LOTID",slot_id);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SLOT_LOTID[i],str_name);

		str_name.Format("DVID.SLOT%002d.LOTID",slot_id);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__DVID_SLOT_LOTID[i],str_name);

		//
		str_name.Format("SLOT%002d.MATERIALID",slot_id);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SLOT_MATERIALID[i],str_name);

		str_name.Format("DVID.SLOT%002d.MATERIALID",slot_id);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__DVID_SLOT_MATERIALID[i],str_name);
	}

	// ANIMATION ...
	{
		str_name = "VIRTUAL.ANI.TRG.MOVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ANI_VIRTUAL_TRG_MOVE, str_name);

		str_name = "ANI.TRG.MOVE";
		STD__ADD_DIGITAL(str_name, DSP__TRG_MOVE);
		LINK__VAR_DIGITAL_CTRL(dCH__ANI_TRG_MOVE, str_name);

		//
		str_name = "VIRTUAL.ANI.TRG.ROTE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ANI_VIRTUAL_TRG_ROTE, str_name);

		str_name = "ANI.TRG.ROTE";
		STD__ADD_DIGITAL(str_name, DSP__TRG_ROTE);
		LINK__VAR_DIGITAL_CTRL(dCH__ANI_TRG_ROTE, str_name);

		//
		str_name = "ANI.ROTE.ARM";
		STD__ADD_DIGITAL(str_name, "A  B  AB");
		LINK__VAR_DIGITAL_CTRL(dCH__ANI_ROTE_ARM, str_name);

		//
		str_name = "ANI.ARM.A.ACT";
		STD__ADD_DIGITAL(str_name, DSP__ARM_ACT);
		LINK__VAR_DIGITAL_CTRL(dCH__ANI_ARM_A_ACT, str_name);

		str_name = "ANI.ARM.B.ACT";
		STD__ADD_DIGITAL(str_name, DSP__ARM_ACT);
		LINK__VAR_DIGITAL_CTRL(dCH__ANI_ARM_B_ACT, str_name);

		str_name = "ANI.ARM.C.ACT";
		STD__ADD_DIGITAL(str_name, DSP__ARM_ACT);
		LINK__VAR_DIGITAL_CTRL(dCH__ANI_ARM_C_ACT, str_name);

		str_name = "ANI.ARM.D.ACT";
		STD__ADD_DIGITAL(str_name, DSP__ARM_ACT);
		LINK__VAR_DIGITAL_CTRL(dCH__ANI_ARM_D_ACT, str_name);
	}

	// LLx : Scheduler - Dual Only Input & Output ...
	{
		str_name = "CFG.LLx_CTRL.ONLY_INPUT_OUTPUT.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "SINGLE DUAL", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_LLx_CTRL_ONLY_INPUT_OUTPUT_MODE, str_name);

		//
		str_name = "CFG.DUAL_ARM_MOVING_AT_THE_SAME_TIME";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE ENABLE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_DUAL_ARM_MOVING_AT_THE_SAME_TIME, str_name);

		str_name = "CFG.DUAL_ARM_MOVING_AT_LPx";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_DUAL_ARM_MOVING_AT_LPx, str_name);

		str_name = "CFG.DUAL_ARM_MOVING_AT_STx";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_DUAL_ARM_MOVING_AT_STx, str_name);

		str_name = "CFG.DUAL_ARM_MOVING_AT_LLx";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_DUAL_ARM_MOVING_AT_LLx, str_name);
	}

	// LLx : CONTRAINT ...
	{
		str_name = "CFG.LL.CONSTRAINT.1";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "ALL ODD EVEN", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_LL_CONSTRAINT_1, str_name);

		str_name = "CFG.LL.CONSTRAINT.2";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "ALL ODD EVEN", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_LL_CONSTRAINT_2, str_name);
	}

	// CFG : WAFER PICK PARAMETER ...
	{
		str_name = "CFG.PICK_WAFER_CONDITION";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "ALL  ONLY.PROCESSED", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PICK_WAFER_CONDITION, str_name);
	}

	// CONFIG ...
	for(i=0; i<CFG_ROBOT__ARM_SIZE; i++)
	{
		CString arm_name;

			 if(i == 0)			arm_name = "A";
		else if(i == 1)			arm_name = "B";
		else					continue;

		str_name.Format("CFG.%s.ARM.USE.FLAG", arm_name);
		STD__ADD_DIGITAL(str_name, DSP__ENABLE_DISABLE);
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_ARM_USE_FLAG_X[i], str_name);
	}

	// SIM CFG ...
	{
		str_name = "SCH_TEST.CFG.PICK_LPx.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PICK_LPx_SEC, str_name);

		str_name = "SCH_TEST.CFG.PICK_ALx.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PICK_ALx_SEC, str_name);

		str_name = "SCH_TEST.CFG.PICK_LLx.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PICK_LLx_SEC, str_name);

		str_name = "SCH_TEST.CFG.PICK_STx.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PICK_STx_SEC, str_name);

		//
		str_name = "SCH_TEST.CFG.PLACE_LPx.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PLACE_LPx_SEC, str_name);

		str_name = "SCH_TEST.CFG.PLACE_ALx.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PLACE_ALx_SEC, str_name);

		str_name = "SCH_TEST.CFG.PLACE_LLx.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PLACE_LLx_SEC, str_name);

		str_name = "SCH_TEST.CFG.PLACE_STx.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PLACE_STx_SEC, str_name);

		//
		str_name = "SCH_TEST.CFG.INIT.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_INIT_SEC, str_name);

		str_name = "SCH_TEST.CFG.HOME.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_HOME_SEC, str_name);

		str_name = "SCH_TEST.CFG.LP_MAP.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_LP_MAP_SEC, str_name);
	}

	// INFO ...
	{
		str_name = "MODULE.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__MODULE_TIME, str_name);

		//
		str_name = "TIME.ACT.START";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TIME_ACT_START, str_name);

		str_name = "TIME.ACT.END";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TIME_ACT_END, str_name);

		str_name = "TIME.ACT.TACK";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TIME_ACT_TACK, str_name);

		str_name = "TIME.ACT.RESULT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TIME_ACT_RESULT, str_name);
	}

	// ...
	{
		SCX__FILE_CTRL x_file_ctrl;
		x_file_ctrl->DISABLE__TIME_LOG();

		//
		SCX__SEQ_INFO x_seq_info;
		x_seq_info->Get__DIR_ROOT(sDir_ROOT);

		CString ref_root;

		ref_root  = sDir_ROOT;
		ref_root += "\\EQP_LOG";
		x_file_ctrl->Create__LOG_DIR(ref_root);

		ref_root += "\\Wafer_Data";
		x_file_ctrl->Create__LOG_DIR(ref_root);

		sDir_WFR_DATA = ref_root;
	}

	// INFO.LLx ...
	for(i=0; i<CFG_LLx_LIMIT; i++)
	{
		int id = i + 1;

		str_name.Format("INFO.LL%1d.RESERVE", id);
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__INFO_LL_RESERVE_X[i], str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__MODULE_STATUS);
	}
	return 1;
}

int CObj_Phy__ROBOT_ATM::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// ...
	ALARM_DEFINE__MODULE_OBJECT;

	// ...
	{
		alarm_title  = title;
		alarm_title += "OBJECT MODE : UNKNOWN";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(ALID__OBJECT_MODE_UNKNOWN,alarm_title,alarm_msg,l_act);
	}
	return 1;
}


//-------------------------------------------------------------------------
int CObj_Phy__ROBOT_ATM::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;

	// ...
	{
		sSCH_NAME = "ATM_RB1";

		def_name = "OBJ__SCH_NAME";
		if(p_ext_obj_create->Get__DEF_CONST_DATA_EX(def_name,def_data,-1) > 0)
		{
			sSCH_NAME = def_data;
		}
	}
	// ...
	{
		bActive__LLx_MULTI_SLOT_VALVE = false;

		def_name = "LLx.MULTI_SLOT_VALVE";
		if(p_ext_obj_create->Get__DEF_CONST_DATA_EX(def_name,def_data,-1) > 0)
		{
			if(def_data.CompareNoCase("YES") == 0)
				bActive__LLx_MULTI_SLOT_VALVE = true;
		}
	}

	// ...
	{
		CString obj_name;
		CString var_name;
		int i;

		// DB_CFG ...
		{
			def_name = "DB_CFG_NAME";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			var_name = "SCH_TEST.CFG.TMC_DUMMY_BY_CTC";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC, obj_name,var_name);
		}
		// OBJ_LPx ...
		{
			def_name = "LP_SIZE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			iLPx_SIZE = atoi(def_data);
			if(iLPx_SIZE > CFG_LP_LIMIT)		iLPx_SIZE = CFG_LP_LIMIT;

			for(i=0; i<iLPx_SIZE; i++)
			{
				def_name.Format("OBJ_LP%1d", i+1);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
				pOBJ_CTRL__LPx[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

				var_name = "DOOR.STS";
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LPx_DOOR_STATUS[i], obj_name,var_name);

				for(int k=0; k<CFG_LP__SLOT_MAX; k++)
				{
					var_name.Format("SLOT%02d.STATUS", k+1);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LPx_SLOTx_STATUS[i][k], obj_name,var_name);
				}
			}
		}
		// OBJ_ALx ...
		{
			def_name = "OBJ_AL1";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
			pOBJ_CTRL__AL1 = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			for(i=0; i<CFG_AL__SLOT_MAX; i++)
			{
				var_name.Format("SLOT%02d.STATUS", i+1);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__AL1_SLOTx_STATUS[i], obj_name,var_name);

				var_name.Format("SLOT%02d.TITLE", i+1);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__AL1_SLOTx_TITLE[i], obj_name,var_name);
			}
		}
		// OBJ_LLx ...
		{
			def_name = "LLx_SIZE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			iLLx_SIZE = atoi(def_data);
			if(iLLx_SIZE > CFG_LLx_LIMIT)		iLLx_SIZE = CFG_LLx_LIMIT;

			for(int ll_i=0; ll_i<iLLx_SIZE; ll_i++)
			{
				def_name.Format("OBJ_LL%1d", ll_i+1);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
				pOBJ_CTRL__LLx[ll_i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

				var_name = "DOOR.STS";
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LLx_DOOR_STATUS[ll_i], obj_name,var_name);

				for(i=0; i<CFG_LLx__SLOT_MAX; i++)
				{
					int id = i + 1;

					var_name.Format("DOOR.STS.%1d", id);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LLx_DOOR_STATUS_X[ll_i][i], obj_name,var_name);

					//
					var_name.Format("SLOT%02d.STATUS", id);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LLx_SLOTx_STATUS[ll_i][i], obj_name,var_name);
	
					var_name.Format("SLOT%02d.TITLE", id);
					LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LLx_SLOTx_TITLE[ll_i][i], obj_name,var_name);
				}
			}
		}
		// OBJ_STx ...
		{
			def_name = "OBJ_ST1";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
			pOBJ_CTRL__ST1 = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			for(i=0; i<CFG_LP__SLOT_MAX; i++)
			{
				var_name.Format("SLOT%02d.STATUS", i+1);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ST1_SLOTx_STATUS[i], obj_name,var_name);

				var_name.Format("SLOT%02d.TITLE", i+1);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ST1_SLOTx_TITLE[i], obj_name,var_name);
			}

			//
			def_name = "OBJ_ST2";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
			pOBJ_CTRL__ST2 = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			for(i=0; i<CFG_LP__SLOT_MAX; i++)
			{
				var_name.Format("SLOT%02d.STATUS", i+1);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ST2_SLOTx_STATUS[i], obj_name,var_name);

				var_name.Format("SLOT%02d.TITLE", i+1);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ST2_SLOTx_TITLE[i], obj_name,var_name);
			}
		}
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xI_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xI_LOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xI_LOG_CTRL->DISABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG(log_msg);

		xI_LOG_CTRL->ENABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	{
		xI_Module_Obj->Link__ERROR_FEEDBACK(&mERROR__MODULE_OBJ);

		//
		xI_Module_Obj->Link__Object_Name(sObject_Name);

		xI_Module_Obj->Register__Module_Status_Channel(xCH__OBJ_STATUS->Get__VARIABLE_NAME());
		xI_Module_Obj->Register__Module_Mode_Channel(dCH__OBJ_MODE->Get__VARIABLE_NAME());;
		xI_Module_Obj->Register__Module_Ctrl_Channel(xCH__OBJ_CTRL->Get__VARIABLE_NAME());

		xI_Module_Obj->Disable__CTCINUSE_TO_STANDBY();

		// ...
		{
			CString data_const;
			p_ext_obj_create->Get__DEF_CONST_DATA_EX("FLAG.REPORT_ABORTED_ALARM",data_const,-1);

			if(data_const.CompareNoCase("DISABLE") == 0)
			{
				xI_Module_Obj->Disable__REPORT_ABORTED_ALARM();
			}
		}
	}

	// ...
	{
		p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

		p_ext_obj_create->Get__DEF_CONST_DATA_EX("UPPER__OBJ_USE",def_data,-1);

		if(def_data.CompareNoCase("ENABLE") == 0)		iUPPER_OBJ__FLAG =  1;
		else											iUPPER_OBJ__FLAG = -1;
	}

	if(iUPPER_OBJ__FLAG > 0)
	{
		xI_Upper_Obj->Link__ERROR_FEEDBACK(&mERROR__MODULE_OBJ);

		//
		xI_Upper_Obj->Link__Object_Name(sObject_Name);

		xI_Upper_Obj->Register__Module_Status_Channel(xCH__UPPER_OBJ__STATUS->Get__VARIABLE_NAME());
		xI_Upper_Obj->Register__Module_Mode_Channel(xCH__UPPER_OBJ__MODE->Get__VARIABLE_NAME());
		xI_Upper_Obj->Register__Module_Ctrl_Channel(xCH__UPPER_OBJ__CTRL->Get__VARIABLE_NAME());
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;
		iACTIVE__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	// ...
	{
		xCH__UPPER_OBJ__PARA_MODULE->Set__DATA("LBA");

		xCH__UPPER_OBJ__PARA_PLACE_ARM->Set__DATA("A");
		xCH__UPPER_OBJ__PARA_PLACE_SLOT->Set__DATA("1");

		xCH__UPPER_OBJ__PARA_PICK_ARM->Set__DATA("A");
		xCH__UPPER_OBJ__PARA_PICK_SLOT->Set__DATA("1");
	}

	iPRC_STS = -1;
	return 1;
}
int CObj_Phy__ROBOT_ATM::__START__OBJECT()
{
	xI_SCH_MATERIAL_CTRL->Link__SERVICE_DB("");

	xI_SCH_MATERIAL_CTRL->Define__ROBOT_NAME(sSCH_NAME);
	xI_SCH_MATERIAL_CTRL->Define__ROBOT_ARM("A");
	xI_SCH_MATERIAL_CTRL->Define__ROBOT_ARM("B");
	return 1;
}


//-------------------------------------------------------------------------
int CObj_Phy__ROBOT_ATM
::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	// ...
	{
		xI_Sync_Ctrl.Thread__LOCK();
		iPRC_STS = 1;
	}

	// ...
	CStringArray l_para;
	CString para_data;

	xI_Module_Obj->Enable__ERROR_CHECK__NOT_STANDBY();

	// ...
	{
		p_variable->Get__FNC_PARAMETER(l_para);

		sPara0__Arm_Type = "";
		sPara1__Module   = "";
		sPara2__Slot     = "";
		sPara3__Pos      = "";
	}

	if(mode.CompareNoCase(sMODE__LP_MAP) == 0)
	{
		if(l_para.GetSize() > 0)
		{
			para_data = l_para[0];

			sPara1__Module = para_data;	

			if(para_data.GetLength() > 0)
			{
				dCH__PARA_MODULE->Set__DATA(sPara1__Module);
			}
		}
	}
	else if((mode.CompareNoCase(sMODE__SWAP_ALx)  == 0)
		 || (mode.CompareNoCase(sMODE__SWAP_LBx)  == 0)
		 || (mode.CompareNoCase(sMODE__SWAP_VISx) == 0))
	{
		int limit = l_para.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			para_data = l_para[i];

			switch(i)
			{
				case 0:
					if(para_data.GetLength() > 0)
					{
						xCH__UPPER_OBJ__PARA_MODULE->Set__DATA(para_data);
					}
					break;

				case 1:
					if(para_data.GetLength() > 0)
					{
						xCH__UPPER_OBJ__PARA_PLACE_ARM->Set__DATA(para_data);
					}
					break;

				case 2:
					if(para_data.GetLength() > 0)
					{
						xCH__UPPER_OBJ__PARA_PLACE_SLOT->Set__DATA(para_data);
					}
					break;

				case 3:
					if(para_data.GetLength() > 0)
					{
						xCH__UPPER_OBJ__PARA_PICK_ARM->Set__DATA(para_data);
					}
					break;

				case 4:
					if(para_data.GetLength() > 0)
					{
						xCH__UPPER_OBJ__PARA_PICK_SLOT->Set__DATA(para_data);
					}
					break;
			}
		}
	}
	else
	{
		int limit = l_para.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			para_data = l_para[i];

			switch(i)
			{
				case 0:
					sPara0__Arm_Type = para_data;		

					if(para_data.GetLength() > 0)
					{
						dCH__PARA_ARM_TYPE->Set__DATA(sPara0__Arm_Type);
					}
					break;

				case 1:	
					sPara1__Module = para_data;	

					if(para_data.GetLength() > 0)
					{
						dCH__PARA_MODULE->Set__DATA(sPara1__Module);
					}
					break;

				case 2:	
					sPara2__Slot = para_data;		

					if(para_data.GetLength() > 0)
					{
						dCH__PARA_SLOT->Set__DATA(sPara2__Slot);
					}
					break;

				case 3:	
					sPara3__Pos = para_data;		

					if(para_data.GetLength() > 0)
					{
						dCH__PARA_POS->Set__DATA(sPara3__Pos);
					}
					break;
			}
		}
	}

	// ...
	CString str__trg_llx_name;
	CString str__trg_llx_slot;

	sCH__TARGET_LLx_NAME_SET_AL->Get__DATA(str__trg_llx_name);
	sCH__TARGET_LLx_SLOT_SET_AL->Get__DATA(str__trg_llx_slot);

	if(mode.CompareNoCase(sMODE__LP_MAP) == 0)
	{
		CString log_string;

		log_string.Format("START : [%s] - (%s)", mode,sPara1__Module);

		xI_LOG_CTRL->WRITE__LOG(log_string);
	}
	else if((mode.CompareNoCase(sMODE__SWAP_ALx)  == 0)
		 || (mode.CompareNoCase(sMODE__SWAP_LBx)  == 0)
		 || (mode.CompareNoCase(sMODE__SWAP_VISx) == 0))
	{
		CString log_string;
		CString para_module;
		CString para_place_arm;
		CString para_place_slot;
		CString para_pick_arm;
		CString para_pick_slot;

		CString slot1_status = "??";
		CString slot1_title  = "??";
		CString slot2_status = "??";
		CString slot2_title  = "??";

		xCH__UPPER_OBJ__PARA_MODULE->Get__DATA(para_module);
		xCH__UPPER_OBJ__PARA_PLACE_ARM->Get__DATA(para_place_arm);
		xCH__UPPER_OBJ__PARA_PLACE_SLOT->Get__DATA(para_place_slot);
		xCH__UPPER_OBJ__PARA_PICK_ARM->Get__DATA(para_pick_arm);
		xCH__UPPER_OBJ__PARA_PICK_SLOT->Get__DATA(para_pick_slot);

		xCH__SLOT_STATUS[0]->Get__DATA(slot1_status);
		xCH__SLOT_TITLE[0]->Get__DATA(slot1_title);
		xCH__SLOT_STATUS[1]->Get__DATA(slot2_status);
		xCH__SLOT_TITLE[1]->Get__DATA(slot2_title);

		log_string.Format("START : [%s] - (%s,%s,%s,%s,%s) (%s,%s) (%s,%s)",
							mode,
							para_module,
							para_place_arm,
							para_place_slot,
							para_pick_arm,
							para_pick_slot,
							slot1_status,
							slot1_title,
							slot2_status,
							slot2_title);

		xI_LOG_CTRL->WRITE__LOG(log_string);
	}
	else
	{
		CString log_string;
		CString log_bff;

		CString slot1_status = "??";
		CString slot1_title  = "??";
		CString slot2_status = "??";
		CString slot2_title  = "??";

		// ...
		{
			xCH__SLOT_STATUS[0]->Get__DATA(slot1_status);
			xCH__SLOT_TITLE[0]->Get__DATA(slot1_title);

			xCH__SLOT_STATUS[1]->Get__DATA(slot2_status);
			xCH__SLOT_TITLE[1]->Get__DATA(slot2_title);
		}

		if(sPara0__Arm_Type.CompareNoCase("UPPER") == 0)
		{
			log_string.Format("START : [%s] - (%s : %s : %s, %s) (%s : %s)",
								mode,
								sPara0__Arm_Type,
								sPara1__Module,
								sPara2__Slot,
								sPara3__Pos,
								slot2_status,
								slot2_title);
		}
		else if(sPara0__Arm_Type.CompareNoCase("A_UPPER") == 0)
		{
			log_string.Format("START : [%s] - (%s : %s : %s, %s) (%s : %s)(%s : %s)",
								mode,
								sPara0__Arm_Type,
								sPara1__Module,
								sPara2__Slot,
								sPara3__Pos,
								slot1_status,
								slot1_title,
								slot2_status,
								slot2_title);
		}
		else if(sPara0__Arm_Type.CompareNoCase("AB") == 0)
		{
			log_string.Format("START : [%s] - (%s : %s : %s, %s) (%s : %s)(%s : %s) \n",
								mode,
								sPara0__Arm_Type,
								sPara1__Module,
								sPara2__Slot,
								sPara3__Pos,
								slot1_status,
								slot1_title,
								slot2_status,
								slot2_title);
		}
		else
		{
			log_string.Format("START : [%s] - (%s : %s : %s, %s) (%s : %s)(%s : %s) \n",
								mode,
								sPara0__Arm_Type,
								sPara1__Module,
								sPara2__Slot,
								sPara3__Pos,
								slot1_status,
								slot1_title,
								slot2_status,
								slot2_title);
		}

		if((mode.CompareNoCase(sMODE__PICK) == 0)
		&& ((sPara1__Module.CompareNoCase("AL1") == 0) || (sPara1__Module.CompareNoCase("AL2") == 0)))
		{
			log_bff.Format(" * Target LPx Name : %s(%s)", str__trg_llx_name,str__trg_llx_slot);
			log_string += log_bff;
		}

		xI_LOG_CTRL->WRITE__LOG(log_string);
	}

	Update__MATERIAL_INFO();

	// ...
	int flag = -1;

	// ...
	{
		// ROBOT ...
			 IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__HOME)				flag = Call__HOME(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__MAINT)			flag = Call__MAINT(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PICK)				flag = Call__PICK(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__XPICK)			flag = Call__XPICK(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PLACE)			flag = Call__PLACE(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__XPLACE)			flag = Call__XPLACE(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__ROTATE)			flag = Call__ROTATE(p_variable);

		// SWAP
		ELSE_IF__CTRL_MODE(sMODE__SWAP_PMx)			flag = Call__SWAP_PMx(p_variable);

		// ROBOT & MODULE
		ELSE_IF__CTRL_MODE(sMODE__SWAP_ALx)			flag = Call__SWAP_ALx(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__SWAP_LBx)			flag = Call__SWAP_LBx(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__SWAP_VISx)		flag = Call__SWAP_VISx(p_variable);

		//
		ELSE_IF__CTRL_MODE(sMODE__LP_MAP)			flag = Call__LP_MAP(p_variable);

		// SCH_TEST : CONFIG ...
		ELSE_IF__CTRL_MODE(sMODE__SCH_TEST_CFG)		flag = Call__SCH_TEST_CFG(p_variable);

		else
		{
			CString bff;
			CString alarm_msg;
			CString r_act;

			bff.Format("Object Name : %s\n",sObject_Name);
			alarm_msg  = bff;
			bff.Format("Unknown Object Mode : \"%s\"\n",mode);
			alarm_msg += bff;

			p_alarm->Popup__ALARM_With_MESSAGE(ALID__OBJECT_MODE_UNKNOWN,alarm_msg,r_act);		
		}
	}


	// ...
	bool active__pick_act  = false;
	bool active__place_act = false;

	if((mode.CompareNoCase(sMODE__PICK)  == 0)		
	|| (mode.CompareNoCase(sMODE__XPICK) == 0))
	{
		active__pick_act = true;
	}
	else if((mode.CompareNoCase(sMODE__PLACE)  == 0)		
		 || (mode.CompareNoCase(sMODE__XPLACE) == 0))
	{
		active__place_act = true;
	}

	if(active__pick_act)
	{
		// ALx ...
		{
			int al_id = Macro__ALx_ID(sPara1__Module);
			int al_slot = atoi(sPara2__Slot);

			if(al_id > 0)
			{
				CString arm_type = sPara0__Arm_Type;

				CString str__trg_name = sCH__TARGET_LLx_NAME_SET_AL->Get__STRING();
				CString str__trg_slot = sCH__TARGET_LLx_SLOT_SET_AL->Get__STRING();

				if(arm_type.CompareNoCase(_ARM__A) == 0)
				{
					if(xCH__SLOT_STATUS[0]->Check__DATA(STR__NONE) < 0)
					{
						sCH__TARGET_LLx_NAME_SET_OF_ARM_A->Set__DATA(str__trg_name);
						sCH__TARGET_LLx_SLOT_SET_OF_ARM_A->Set__DATA(str__trg_slot);
					}
				}
				else if(arm_type.CompareNoCase(_ARM__B) == 0)
				{
					if(xCH__SLOT_STATUS[1]->Check__DATA(STR__NONE) < 0)
					{
						sCH__TARGET_LLx_NAME_SET_OF_ARM_B->Set__DATA(str__trg_name);
						sCH__TARGET_LLx_SLOT_SET_OF_ARM_B->Set__DATA(str__trg_slot);
					}
				}
			}
		}	
	}
	else if(active__place_act)
	{
		CString arm_type = sPara0__Arm_Type;

		if(arm_type.CompareNoCase(_ARM__A) == 0)
		{
			if(xCH__SLOT_STATUS[0]->Check__DATA(STR__NONE) > 0)
			{
				sCH__TARGET_LLx_NAME_SET_OF_ARM_A->Set__DATA("");
				sCH__TARGET_LLx_SLOT_SET_OF_ARM_A->Set__DATA("");
			}
		}
		else if(arm_type.CompareNoCase(_ARM__B) == 0)
		{
			if(xCH__SLOT_STATUS[1]->Check__DATA(STR__NONE) > 0)
			{
				sCH__TARGET_LLx_NAME_SET_OF_ARM_B->Set__DATA("");
				sCH__TARGET_LLx_SLOT_SET_OF_ARM_B->Set__DATA("");
			}
		}	
	}

	if((active__pick_act)
	|| (active__place_act))
	{
		Report__MATERIAL_INFO(mode);
	}

	if(active__place_act)
	{
		// LL.Index ...
		int ll_index = Macro__Get_LLx_INDEX(sPara1__Module);
		if(ll_index >= 0)
		{
			dCH__INFO_LL_RESERVE_X[ll_index]->Set__DATA(STR__OFF);
		}

		// Wafer.Count ...
		int wfr_count = 0;
		int i;

		for(i=0; i<CFG_ROBOT__ARM_SIZE; i++)
		{
			if(dCH__CFG_ARM_USE_FLAG_X[i]->Check__DATA(STR__ENABLE) < 0)	continue;
			if(xCH__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)				continue;

			wfr_count++;
		}

		if(wfr_count < 1)
		{
			for(i=0; i<CFG_LLx_LIMIT; i++)
			{
				dCH__INFO_LL_RESERVE_X[i]->Set__DATA(STR__OFF);	
			}
		}
	}

	//
	if(mode.CompareNoCase(sMODE__LP_MAP) == 0)
	{
		CString log_string;

		if(flag > 0)		log_string.Format("COMPLETE : [%s]",mode);
		else				log_string.Format("ABORTED  : [%s]",mode);

		// ...
		{
			CString bff_log;

			bff_log.Format(" - (%s)", sPara1__Module);
			log_string += bff_log;

			xI_LOG_CTRL->WRITE__LOG(log_string);
		}
	}
	else if((mode.CompareNoCase(sMODE__SWAP_ALx)  == 0)
		 || (mode.CompareNoCase(sMODE__SWAP_LBx)  == 0)
		 || (mode.CompareNoCase(sMODE__SWAP_VISx) == 0))
	{
		CString log_string;
		CString para_module;
		CString para_place_arm;
		CString para_place_slot;
		CString para_pick_arm;
		CString para_pick_slot;

		CString slot1_status = "??";
		CString slot1_title  = "??";
		CString slot2_status = "??";
		CString slot2_title  = "??";

		xCH__UPPER_OBJ__PARA_MODULE->Get__DATA(para_module);
		xCH__UPPER_OBJ__PARA_PLACE_ARM->Get__DATA(para_place_arm);
		xCH__UPPER_OBJ__PARA_PLACE_SLOT->Get__DATA(para_place_slot);
		xCH__UPPER_OBJ__PARA_PICK_ARM->Get__DATA(para_pick_arm);
		xCH__UPPER_OBJ__PARA_PICK_SLOT->Get__DATA(para_pick_slot);

		xCH__SLOT_STATUS[0]->Get__DATA(slot1_status);
		xCH__SLOT_TITLE[0]->Get__DATA(slot1_title);
		xCH__SLOT_STATUS[1]->Get__DATA(slot2_status);
		xCH__SLOT_TITLE[1]->Get__DATA(slot2_title);

		if(flag > 0)		log_string.Format("COMPLETE : [%s]",mode);
		else				log_string.Format("ABORTED  : [%s]",mode);

		// ...
		{
			CString bff_log;

			bff_log.Format(" - (%s,%s,%s,%s,%s) (%s,%s) (%s,%s)",
							mode,
							para_module,
							para_place_arm,
							para_place_slot,
							para_pick_arm,
							para_pick_slot,
							slot1_status,
							slot1_title,
							slot2_status,
							slot2_title);
			log_string += bff_log;

			xI_LOG_CTRL->WRITE__LOG(log_string);
		}
	}
	else
	{
		CString log_string;
		CString slot1_status = "??";
		CString slot1_title  = "??";
		CString slot2_status = "??";
		CString slot2_title  = "??";

		// ...
		{
			xCH__SLOT_STATUS[0]->Get__DATA(slot1_status);
			xCH__SLOT_TITLE[0]->Get__DATA(slot1_title);

			xCH__SLOT_STATUS[1]->Get__DATA(slot2_status);
			xCH__SLOT_TITLE[1]->Get__DATA(slot2_title);
		}

		if(flag > 0)		log_string.Format("COMPLETE : [%s]",mode);
		else				log_string.Format("ABORTED  : [%s]",mode);

		// ...
		CString bff_log;

		if(sPara0__Arm_Type.CompareNoCase("UPPER") == 0)
		{
			bff_log.Format(" - (%s : %s : %s, %s) (%s : %s)",
							sPara0__Arm_Type,
							sPara1__Module,
							sPara2__Slot,
							sPara3__Pos,
							slot2_status,
							slot2_title);
		}
		else if(sPara0__Arm_Type.CompareNoCase("A_UPPER") == 0)
		{
			bff_log.Format(" - (%s : %s : %s, %s) (%s : %s)(%s : %s)",
							sPara0__Arm_Type,
							sPara1__Module,
							sPara2__Slot,
							sPara3__Pos,
							slot1_status,
							slot1_title,
							slot2_status,
							slot2_title);
		}
		else if(sPara0__Arm_Type.CompareNoCase("AB") == 0)
		{
			bff_log.Format(" - (%s : %s : %s, %s) (%s : %s)(%s : %s)",
							sPara0__Arm_Type,
							sPara1__Module,
							sPara2__Slot,
							sPara3__Pos,
							slot1_status,
							slot1_title,
							slot2_status,
							slot2_title);
		}
		else
		{
			bff_log.Format(" - (%s : %s : %s, %s) (%s : %s)(%s : %s)",
							sPara0__Arm_Type,
							sPara1__Module,
							sPara2__Slot,
							sPara3__Pos,
							slot1_status,
							slot1_title,
							slot2_status,
							slot2_title);
		}
		log_string += bff_log;

		xI_LOG_CTRL->WRITE__LOG(log_string);
	}

	// ALx Result ...
	{
		if((mode.CompareNoCase(sMODE__PICK) == 0)
		&& ((sPara1__Module.CompareNoCase("AL1") == 0) || (sPara1__Module.CompareNoCase("AL2") == 0)))
		{
			CString log_msg;
			CString log_bff;

			log_msg  = "\n";
			log_msg += " Align Result ... \n";

			// ...
			int arm_index = -1;

				 if(sPara0__Arm_Type.CompareNoCase(_ARM__A) == 0)		arm_index = 0;
			else if(sPara0__Arm_Type.CompareNoCase(_ARM__B) == 0)		arm_index = 1;

			if(arm_index >= 0)
			{
				log_bff.Format(" * %s [%s : %s] -> ARM(%s) \n", 
								sPara1__Module,
								xCH__SLOT_STATUS[arm_index]->Get__STRING(),
								xCH__SLOT_TITLE[arm_index]->Get__STRING(),
								sPara0__Arm_Type);
				log_msg += log_bff;
			}
			else
			{
				log_bff.Format(" * %s [?? : ??] -> ARM(%s) \n", 
								sPara1__Module,
								sPara0__Arm_Type);
				log_msg += log_bff;
			}

			// ...
			{
				log_bff.Format("  ** %s <- %s \n", 
								dCH__TARGET_PMx_MODE->Get__CHANNEL_NAME(), 
								dCH__TARGET_PMx_MODE->Get__STRING());
				log_msg += log_bff;

				log_bff.Format("  ** %s <- %s \n", 
								dCH__TARGET_LLx_MODE->Get__CHANNEL_NAME(), 
								dCH__TARGET_LLx_MODE->Get__STRING());
				log_msg += log_bff;

				log_bff.Format("  ** %s <- %s \n", 
								dCH__TARGET_LLx_SLOT_CHECK->Get__CHANNEL_NAME(),
								dCH__TARGET_LLx_SLOT_CHECK->Get__STRING());
				log_msg += log_bff;

				log_bff.Format("  ** %s <- %s \n", 
								sCH__TARGET_LLx_NAME_SET_AL->Get__CHANNEL_NAME(),
								sCH__TARGET_LLx_NAME_SET_AL->Get__STRING());
				log_msg += log_bff;

				log_bff.Format("  ** %s <- %s \n", 
								sCH__TARGET_LLx_SLOT_SET_AL->Get__CHANNEL_NAME(),
								sCH__TARGET_LLx_SLOT_SET_AL->Get__STRING());
				log_msg += log_bff;

				log_bff.Format("  ** %s <- %s \n", 
								sCH__TARGET_LLx_NAME_GET->Get__CHANNEL_NAME(),
								sCH__TARGET_LLx_NAME_GET->Get__STRING());
				log_msg += log_bff;

				log_bff.Format("  ** %s <- %s \n", 
								sCH__TARGET_LLx_SLOT_GET->Get__CHANNEL_NAME(),
								sCH__TARGET_LLx_SLOT_GET->Get__STRING());
				log_msg += log_bff;

				log_bff.Format("  ** %s <- %s \n", 
								sCH__TARGET_LLx_ANGLE_GET->Get__CHANNEL_NAME(),
								sCH__TARGET_LLx_ANGLE_GET->Get__STRING());
				log_msg += log_bff;
			}

			xI_LOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// ...
	{
		iPRC_STS = -1;
		xI_Sync_Ctrl.Thread__UNLOCK();
	}
	return flag;
}
int CObj_Phy__ROBOT_ATM::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__MODULE_STATUS:
			Mon__MODULE_STATUS(p_variable,p_alarm);
			break;
	}

	return 1;
}
