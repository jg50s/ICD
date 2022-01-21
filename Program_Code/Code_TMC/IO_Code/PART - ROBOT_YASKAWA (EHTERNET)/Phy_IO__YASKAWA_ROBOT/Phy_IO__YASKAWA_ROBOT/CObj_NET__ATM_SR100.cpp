#include "StdAfx.h"
#include "CObj_NET__ATM_SR100.h"
#include "CObj_NET__ATM_SR100__DEF.h"
#include "CObj_NET__ATM_SR100__ALID.h"

#include "CCommon_DEF.h"
#include "Macro_Function.h"


//--------------------------------------------------------------------------------
CObj_NET__ATM_SR100::CObj_NET__ATM_SR100()
{
	
}
CObj_NET__ATM_SR100::~CObj_NET__ATM_SR100()
{

}

//--------------------------------------------------------------------------------
int CObj_NET__ATM_SR100::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,   "INIT");				
		ADD__CTRL_VAR(sMODE__HOME,   "HOME");				

		ADD__CTRL_VAR(sMODE__PICK,	 "PICK");			
		ADD__CTRL_VAR(sMODE__PLACE,	 "PLACE");			
		ADD__CTRL_VAR(sMODE__ROTATE, "ROTATE");			

		ADD__CTRL_VAR(sMODE__CHECK_ERROR_CODE, "CHECK.ERROR_CODE");
	}

	return 1;
}
int CObj_NET__ATM_SR100::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR									1
#define  MON_ID__PROC_RSP_MSG								2


// ...
#define APP_DSP__RB_TARGET_MOVE								\
"UNKNOWN HOME READY											\
PM1 PM2 PM3 PM4 PM5 PM6										\
LBA LBB														\
AL1 AL2														\
VIS1 VIS2													\
LP1 LP2 LP3 LP4 LP5											\
BUFF1 BUFF2"

#define APP_DSP__STN_NAME									\
"LP1 LP2 LP3 LP4 LP5										\
VIS1														\
LBA LBB														\
LBC LBD														\
AL1 AL2														\
BUFF1 BUFF2 FULL_BUFF"

#define APP_DSP__DSlot										\
"1  2  3  4  5  6  7  8  9  10								\
11 12 13 14 15 16 17 18 19  20								\
21 22 23 24 25 26 27 28 29  30"

#define APP_DSP__ARM_TYPE									\
"A B"

#define APP_DSP__RET_EXT									\
"Retract Extend"

#define APP_DSP__DOWN_UP									\
"Down Up"

#define APP_DSP__ARM_STS_ANI								\
"UNKNOWN RETRACT EXTEND"

#define APP_DSP__LP_WFR_SLOT_STS							\
"UNKNOWN INVALID ABSENT PRESENT DOUBLE CROSSED"


int CObj_NET__ATM_SR100::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	int i;

	// ...
	{
		str_name = "MON.COMMUNICATION.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMMUNICATION_STATE, str_name);

		str_name = "MON.COMMUNICATION.INFO";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMMUNICATION_INFO, str_name);
	}

	// ...
	{
		str_name = "dHYPER.TERMINAL.LOCK.FLAG";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, "YES NO","");
		LINK__VAR_DIGITAL_CTRL(xCH__LOCK_FLAG, str_name);
	}

	// ERROR TEST ...
	{
		str_name = "CFG.ACTIVE.ACKN.SEND";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_ACTIVE_ACKN_SEND, str_name);

		str_name = "CFG.ACTIVE.RECV_CNT.SINGLE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_ACTIVE_RECV_CNT_SINGLE, str_name);

		//
		str_name = "ERROR_TEST.ACTIVE";
		STD__ADD_DIGITAL(str_name, "NO YES");
		LINK__VAR_DIGITAL_CTRL(dCH__ERROR_TEST__ACTIVE, str_name);

		str_name = "ERROR_TEST.ERROR_CODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ERROR_TEST__ERROR_CODE, str_name);
	}

	// ...
	{
		str_name = "INFO,Ver_System";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_VER_SYSTEM, str_name);

		str_name = "INFO.Ver_Servo";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_VER_SERVO, str_name);
	}

	// Simulation ...
	{
		str_name = "OTR.IN.CFG.dSIMUL.FLAG";
		STD__ADD_DIGITAL(str_name, "NO YES");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_CFG__SIMUL_FLAG,str_name);

		// 
		str_name = "OTR.IN.CFG.sSIMUL.ALIGN.TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__OTR_IN_CFG__SIMUL_ALIGN_TIME,str_name);
	}

	// ...
	{
		str_name = "INR.RB1.ACT.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ACT_MSG, str_name);

		str_name = "OTR.OUT.MON.sCOMM.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OTR_OUT_MON__COMM_STS,str_name);

		str_name = "INR.sERROR.ID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INR__ERROR_ID,str_name);

		str_name = "INR.FLAG.dALGN.STS";
		STD__ADD_DIGITAL(str_name, "ALIGNING ALIGNED");
		LINK__VAR_DIGITAL_CTRL(dCH__INR_FLAG__ALGN_STS,str_name);
	}

	// PARA CHANNEL ...
	{
		str_name = "OTR.IN.PARA.dSTN.NAME";
		STD__ADD_DIGITAL(str_name, APP_DSP__STN_NAME);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__STN_NAME,str_name);

		str_name = "OTR.IN.PARA.dSTN.SLOT";
		STD__ADD_DIGITAL(str_name, APP_DSP__DSlot);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__STN_SLOT,str_name);

		str_name = "OTR.IN.PARA.dARM.TYPE";
		STD__ADD_DIGITAL(str_name, APP_DSP__ARM_TYPE);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__ARM_TYPE,str_name);

		// ...
		str_name = "PARA.AL1.CCD.POS";
		STD__ADD_ANALOG(str_name, "deg", 1, 0.0, 360.0);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_AL1_CCD_POS, str_name);
	}

	// MATERIAL CHANNEL ...
	{
		CString dsp_slot_sts;
		p_variable->Get__STD_DESCRIPTION("STD_SLOT_STATUS", dsp_slot_sts);

		// Material Status
		str_name = "MON.ARM_A.MATERIAL.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, dsp_slot_sts, "");
		LINK__VAR_DIGITAL_CTRL(dCH__MON__ARM_A_MATERIAL_STATUS, str_name);

		str_name = "MON.ARM_B.MATERIAL.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, dsp_slot_sts, "");
		LINK__VAR_DIGITAL_CTRL(dCH__MON__ARM_B_MATERIAL_STATUS, str_name);

		// Material Title
		str_name = "MON.ARM_A.MATERIAL.TITLE";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__MON__ARM_A_MATERIAL_TITLE, str_name);

		str_name = "MON.ARM_B.MATERIAL.TITLE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__MON__ARM_B_MATERIAL_TITLE, str_name);
	}

	// CURRENT INFO ...
	{
		// ALx ...
		{
			str_name = "CUR.AL1.STN.NUM";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__CUR_AL1_STN_NUM, str_name);
		}

		// LLx ...
		{
			int ll_i;

			for(ll_i=0; ll_i<CFG_LLx__SIZE; ll_i++)
			{
				CString ll_name = Macro__Get_LLx_NAME(ll_i);

				str_name.Format("CUR.%s.STN.NUM", ll_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__CUR_LLx_STN_NUM[ll_i], str_name);
			}

			for(ll_i=0; ll_i<CFG_LLx__SIZE; ll_i++)
			{
				int id = ll_i + 1;

				str_name.Format("CUR.LL%1d.1.STN.NUM", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__CUR_LLx_1_STN_NUM[ll_i], str_name);

				str_name.Format("CUR.LL%1d.2.STN.NUM", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__CUR_LLx_2_STN_NUM[ll_i], str_name);
			}
		}

		// STx ...
		{
			str_name = "CUR.ST1.STN.NUM";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__CUR_ST1_STN_NUM, str_name);
		}

		// LPx ...
		for(i=0; i<CFG_LPx__SIZE; i++)
		{
			str_name.Format("CUR.LP%1d.STN.NUM", i+1);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__CUR_LPx_STN_NUM[i], str_name);
		}
	}

	// ROBOT ...
	{
		str_name = "CFG.ACTION.CONFIRM.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"DISABLE ENABLE","");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_ACTION_CONFIRM_FLAG,str_name);

		//
		str_name = "OTR.OUT.CFG.ROM.RATE";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__OTR_OUT_CFG__ROM_DATE, str_name);

		str_name = "OTR.OUT.CFG.ROM.VERSION";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__OTR_OUT_CFG__ROM_VERSION, str_name);
	}

	// SIMULATION CHANNEL ...
	{
		str_name = "SIM.CFG.aROTATE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__ROTATE_TIME, str_name);

		// LPx ...
		str_name = "SIM.CFG.aLPx.PICK.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__LPx_PICK_TIME, str_name);

		str_name = "SIM.CFG.aLPx.PLACE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__LPx_PLACE_TIME, str_name);

		// ALx
		str_name = "SIM.CFG.aALx.PICK.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__ALx_PICK_TIME, str_name);

		str_name = "SIM.CFG.aALx.PLACE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__ALx_PLACE_TIME, str_name);

		// LBx
		str_name = "SIM.CFG.aLBx.PICK.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__LBx_PICK_TIME, str_name);

		str_name = "SIM.CFG.aLBx.PLACE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__LBx_PLACE_TIME, str_name);

		// VISx
		str_name = "SIM.CFG.aVISx.PICK.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__VISx_PICK_TIME, str_name);

		str_name = "SIM.CFG.aVISx.PLACE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__VISx_PLACE_TIME, str_name);
	}

	// SYSTEM STATUS ...
	{
		str_name = "MON.SYS_STS.MANIPULATOR_BATTERY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SYS_STS__MANIPULATOR_BATTERY, str_name);

		str_name = "MON.SYS_STS.UNIT_STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SYS_STS__UNIT_STATUS, str_name);

		str_name = "MON.SYS_STS.SERVO_STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SYS_STS__SERVO_STATUS, str_name);

		str_name = "MON.SYS_STS.ERROR_STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SYS_STS__ERROR_STATUS, str_name);

		//
		str_name = "MON.SYS_STS.CONTROLLRT_BATTERY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SYS_STS__CONTROLLRT_BATTERY, str_name);

		str_name = "MON.SYS_STS.WAFER_PRESENCE_STS1";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SYS_STS__WAFER_PRESENCE_STS1, str_name);

		str_name = "MON.SYS_STS.WAFER_PRESENCE_STS2";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SYS_STS__WAFER_PRESENCE_STS2, str_name);
	}

	// ERROR CODE ...
	{
		str_name = "MON.ERR_SYS.LEVEL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ERR_SYS__LEVEL, str_name);

		str_name = "MON.ERR_STS.CODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ERR_STS__CODE, str_name);
	}

	// ROBOT_STATUS ...
	{
		str_name = "MON.RB_STS.WAFER_SNS_ON_BLADE.1";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_RB_STS__WAFER_SNS_ON_BLADE_1, str_name);

		str_name = "MON.RB_STS.WAFER_SNS_ON_BLADE.2";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_RB_STS__WAFER_SNS_ON_BLADE_2, str_name);

		//
		str_name = "MON.RB_STS.WAFER_GRIP_ON_BLADE.1";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_RB_STS__WAFER_GRIP_ON_BLADE_1, str_name);

		str_name = "MON.RB_STS.WAFER_GRIP_ON_BLADE.2";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_RB_STS__WAFER_GRIP_ON_BLADE_2, str_name);

		//
		for(i=0; i<_CFG__INTERLOCK_SIZE; i++)
		{
			str_name.Format("MON.RB_STS.INTERLOCK_SIGNAL.%1d", i+1);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_RB_STS__INTERLOCK_SIGNAL_X[i], str_name);
		}
	}

	// ...
	{
		str_name = "ROM.VERSION";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__ROM_VER,str_name);

		str_name = "ROM.DATE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__ROM_DATE,str_name);
	}

	for(i=0;i<CFG_LPx__SLOT_SIZE;i++)
	{
		str_name.Format("OTR.OUT.MON.dSLOT%02d.MAP.RESULT", i+1);
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__LP_WFR_SLOT_STS,"");
		LINK__VAR_DIGITAL_CTRL(dCH__LPx_SLOT_STATUS[i],str_name);
	}

	// ATMAlignAndPickTime		: Excel Num 82
	str_name = "CFG.aALIGN.AND.PICK.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0.5,100.0,"recommand:9 sec");
	LINK__VAR_ANALOG_CTRL(aCH__CFG__ALIGN_AND_PICK_TIMEOUT, str_name);

	// ATMAlignOCRTime
	str_name = "CFG.aALIGN.OCR.TIME";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0.5,100.0,"recommand:4 sec");

	// AtmDynamicAlignmentDirection
	str_name.Format("CFG.dDYNAMIC.ALIGN.DIRECTION");	// 자동으로 da 하지만, 명령어 끝에 option을 줘야한다.
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"RETRACT EXTEND","REC:RETRACT");
	LINK__VAR_DIGITAL_CTRL(dCFG__CH__DYNAMIC_ALIGN_DIRECTION,str_name);

	// ATMPadType
	str_name = "CFG.dPAD.TYPE";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "UNKNOWN", "");
	LINK__VAR_DIGITAL_CTRL(dCH__CFG_PAD_TYPE,str_name);

	// ATMPickTime
	str_name = "CFG.aPICK.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0.5,100.0,"recommand:4.2 sec");
	LINK__VAR_ANALOG_CTRL(aCH__CFG__PICK_TIMEOUT, str_name);

	// ATMPlaceTime
	str_name = "CFG.aPLACE.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0.5,100.0,"recommand:4.4 sec");
	LINK__VAR_ANALOG_CTRL(aCH__CFG__PLACE_TIMEOUT, str_name);

	// ATMPlaceToAlignerTime
	str_name = "CFG.aPLACE.AND.ALIGN.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0.5,100.0,"recommand:9 sec");
	LINK__VAR_ANALOG_CTRL(aCH__CFG__PLACE_AND_ALIGN_TIMEOUT, str_name);

	// CheckWaferSlideOut
	str_name = "CFG.dMAPPING.ACTION.SLIDEOUT.CHECK";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"NO YES","");
	LINK__VAR_DIGITAL_CTRL(dCH__CFG_MAPPING_ACTION_SLIDE_OUT_CHECK,str_name);

	// CoverWaferAlignmentBeforeReturnToPort
	str_name = "CFG.dBEFORE.PLACE.TO.LP.ALIGN";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"NO YES", "");

	// DAAlignerRadialHardTolerance
	str_name = "CFG.aDA.ALIGNER.R.HARD.TOLE";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"-",0,1000,8000,"recommand:4000");

	// DAAlignerRadialSoftTolerance
	str_name = "CFG.aDA.ALIGNER.R.SOFT.TOLE";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"-",0,500,4000,"recommand:2000");

	// DAAlignerRadialThetaHardTolerance
	str_name = "CFG.aDA.ALIGNER.T.HARD.TOLE";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"-",0,75,600,"recommand:300");

	// DAAlignerRadialThetaSoftTolerance
	str_name = "CFG.aDA.ALIGNER.T.SOFT.TOLE";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"-",0,37,300,"recommand:150");

	// DisableExtendedAlign : 103
	str_name = "CFG.dDISABLE.EXTEND.ALIGN";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"FALSE TRUE", "");

	//
	str_name = "CFG.aBEFORE.PLACE.TO.LP.ALIGN.ANGLE";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name, "angle", 0, 0, 360, "recommand:180");

	// ...
	str_name = "CFG.aPADDLE.DOWN.CHECK.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 12, "rec:2");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_LP__PADDLE_CHECK_TIME,str_name);

	// ...
	str_name = "CFG.dMAPPING.DISABLE";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "");
	LINK__VAR_DIGITAL_CTRL(dCH__CFG_MAPPING_DISABLE,str_name);

	// ...
	str_name = "CFG.dALIGN.SKIP";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "");
	LINK__VAR_DIGITAL_CTRL(dCH__CFG_ALIGN_SKIP,str_name);

	// UseSlowPickPlaceFromAirLockToCool
	str_name = "CFG.dSLOW.PICK.PLACE.FROM.LLx.TO.COOL.STN";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "rec:NO");

	// WaferAlignmentBeforePostProcessedIMMMeasurement
	str_name = "CFG.dWFR.ALGN.BEFORE.IMM.MEASURE";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "rec:TRUE");
	//

	// ...	
	{
		p_variable->Add__MONITORING_PROC(7.0, MON_ID__IO_MONITOR);
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__PROC_RSP_MSG);
	}
	return 1;
}


// ...
#define  ACT__RETRY_ABORT						\
l_act.RemoveAll();								\
l_act.Add("RETRY");								\
l_act.Add("ABORT");

#define  ACT__ABORT_ALARM						\
l_act.RemoveAll();								\
l_act.Add("ABORT");

#define  ACT__NO_YES_ALARM						\
l_act.RemoveAll();								\
l_act.Add("NO");								\
l_act.Add("YES");


int CObj_NET__ATM_SR100::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CString alarm_bff;
	CStringArray l_act;
	int alarm_id;
	int i;

	// ...
	{
		alarm_id = ALID__OFFLINE_ALARM;

		alarm_title  = title;
		alarm_title += "Offline.";

		alarm_msg  = "Controller is Offline.\n";
		alarm_msg += "Please, Check Communication Status !\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__ERROR_CODE;

		alarm_title  = title;
		alarm_title += "Error Code !";

		alarm_msg = "Please, check HW status !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);	
	}

	// ...
	{
		alarm_id = ALID__ALGN_AND_PICK_TIMEOUT_ALARM;

		alarm_title  = title;
		alarm_title += "Align and Pick Action Timeout Occur.";

		alarm_msg  = "Align and Pick Action Timeout Occur.\n";
		alarm_msg += "Please, Check ATM Robot Status !\n";

		ACT__ABORT_ALARM;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__MAPPING_DISABLE_CONFIG_ALARM;

		alarm_title  = title;
		alarm_title += "Config Option, Mapping Disable Alarm.";

		alarm_msg  = "Now, Mapping Disable Config Option Selected.\n";
		alarm_msg += "Would you like to continue ??\n";

		ACT__NO_YES_ALARM;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	for(i=0; i<5; i++)
	{
		// DOOR NOT OPEN
		{
			alarm_id = ALID__LP1__NOT_DOOR_OPEN + i;

			alarm_title  = title;
			alarm_bff.Format("LP%1d's door status is not open.",i+1);
			alarm_title += alarm_bff;

			alarm_msg.Format("Please, check LP%1d's door status !\n",i+1);

			ACT__RETRY_ABORT;
			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}

		// FOUP NOT EXIST
		{
			alarm_id = ALID__LP1__FOUP_NOT_EXIST + i;

			alarm_title  = title;
			alarm_bff.Format("LP%1d's foup does not exist.",i+1);
			alarm_title += alarm_bff;

			alarm_msg.Format("Please, check LP%1d's foup does not exist !\n",i+1);

			ACT__RETRY_ABORT;
			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}

		// FOUP NOT CLAMP
		{
			alarm_id = ALID__LP1__FOUP_NOT_CLAMP + i;

			alarm_title  = title;
			alarm_bff.Format("LP%1d's foup does not clamp.",i+1);
			alarm_title += alarm_bff;

			alarm_msg.Format("Please, check LP%1d's foup does not clamp !\n",i+1);

			ACT__RETRY_ABORT;
			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}

		// FOUP NOT LOAD
		{
			alarm_id = ALID__LP1__FOUP_NOT_LOAD + i;

			alarm_title  = title;
			alarm_bff.Format("LP%1d's foup position is not load.",i+1);
			alarm_title += alarm_bff;

			alarm_msg.Format("Please, check LP%1d's foup position is not load !\n",i+1);

			ACT__RETRY_ABORT;
			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}

		// LP1, 2, 3, 4, 5... WAFER SLIDE OUT SNS
		{
			alarm_id = ALID__LP1_WFR_SLIDE_SNS_ALARM + i;

			alarm_title  = title;
			alarm_bff.Format("LP%1d's Wafer Slide Out Sns is On Status.",i+1);
			alarm_title += alarm_bff;

			alarm_msg.Format("Please, check LP%1d's Wafer Slide Status... !\n",i+1);

			ACT__RETRY_ABORT;
			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
	}

	// LLx : ALID ...
	for(i=0; i<CFG_LLx__SIZE; i++)
	{
		// ...
		{
			alarm_id = ALID__LLx__NOT_ATM_PRESSURE + i;

			alarm_title = title;
			alarm_bff.Format("%s's Pressure is not ATM.", Macro__Get_LLx_NAME(i));
			alarm_title += alarm_bff;

			alarm_msg = "Please, Check LBA's Pressure !\n";
			alarm_bff.Format("%s's Pressure must be ATM.\n", Macro__Get_LLx_NAME(i));
			alarm_msg += alarm_bff;

			ACT__RETRY_ABORT;
			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}

		// DOOR NOT OPEN ...
		{
			alarm_id = ALID__LLx__NOT_DOOR_OPEN + i;

			alarm_title = title;
			alarm_bff.Format("%s's door status is not open.", Macro__Get_LLx_NAME(i));
			alarm_title += alarm_bff;

			alarm_msg = "Please, check LBA's door status !\n";
	
			ACT__RETRY_ABORT;
			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
	}

	// ...
	{
		alarm_id = ALID__INVALID__NOT_AL1_STATION;

		alarm_title  = title;
		alarm_title += "Invalid Target Station Eorror.";

		alarm_msg = "Please, check Target Station's Name !\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);	
	}

	return 1;
}


// ...
#define APP_DSP__Arm_ID				"A  B"
#define APP_DSP__Wfr    			"Unknown  Absent  Present"
#define APP_DSP__StrLoc 			"Normal  Retract2  NoRetract"
#define APP_DSP__Axises				"ALL  R  T  Z  W  S"

#define APP_DSP__Stn									\
"1  2  3  4  5  6  7  8  9  10							\
11 12 13 14 15 16 17 18 19 20							\
21 22 23 24 25 26 27 28 29 30"

#define APP_DSP__CurStn									\
"0														\
1  2  3  4  5  6  7  8  9  10							\
11 12 13 14 15 16 17 18 19 20							\
21 22 23 24 25 26 27 28 29 30"

#define APP_DSP__DDnUp				"DN  UP"
#define APP_DSP__OffOn              "OFF ON"
#define APP_DSP__RetExt             "RE  EX"
#define APP_DSP__ComSts             "Offline Online"
#define APP_DSP__YesNo              "Y   N"
#define APP_DSP__PrsAbs				"ON  OFF"
#define APP_DSP__ALWfr				"?  NO  YES"

#define APP_DSP__Material								\
"? 0 1 2 3 4 5 6 7 20 21 22 23 FP"

#define APP_DSP__Substrates								\
"1 2 3 4 5 6 7 20 21 22 23"

#define APP_DSP__FDCLs				"None  Flat  Ntch"
#define APP_DSP__WfrShapes			"Round  Square"
#define APP_DSP__CCDPos				"1  2  3"
#define APP_DSP__DOffOn				"Off  On"
#define APP_DSP__DZPos				"Unknown  Up  Down"
#define APP_DSP__DRPos				"Unknown  Retract  Extend"

#define APP_DSP__DTPos									\
"Unknown												\
1  2  3  4  5  6  7  8  9  10							\
11 12 13 14 15 16 17 18 19 20							\
21 22 23 24 25 26 27 28 29 30"

#define APP_DSP__DSPos									\
"Unknown												\
1  2  3  4  5  6  7  8  9  10							\
11 12 13 14 15 16 17 18 19 20							\
21 22 23 24 25 26 27 28 29 30"


int CObj_NET__ATM_SR100::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;
	CString d_list;

	// DO
	{
		d_list  = _CMMD__Goto;
		d_list += " ";
		d_list += _CMMD__Pick;
		d_list += " ";
		d_list += _CMMD__Place;
		d_list += " ";
		d_list += _CMMD__RBSrvOn;
		d_list += " ";
		d_list += _CMMD__RBSrvOff;
		d_list += " ";
		d_list += _CMMD__RBInit;
		d_list += " ";
		d_list += _CMMD__RBErrClr;
		d_list += " ";

		str_name = "do.Command";
		IO__ADD_DIGITAL_WRITE(str_name, d_list);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__COMMAND, str_name);
	}

	// DI
	{
		str_name = "di.RB.Sts";
		IO__ADD_DIGITAL_READ__MANUAL(str_name, APP_DSP__DOffOn);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__RB_STS, str_name);
	}

	// SI
	{
		str_name = "si.Version";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__VERSION, str_name);
	}

	return 1;
}

//--------------------------------------------------------------------------------
int CObj_NET__ATM_SR100::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString obj_name;
	CString var_name;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xAPP_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xAPP_LOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xAPP_LOG_CTRL->DISABLE__TIME_LOG();
		xAPP_LOG_CTRL->WRITE__LOG(log_msg);

		xAPP_LOG_CTRL->ENABLE__TIME_LOG();
		xAPP_LOG_CTRL->WRITE__LOG("   START   \n");
	}
	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_Drv.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xDRV_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xDRV_LOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xDRV_LOG_CTRL->DISABLE__TIME_LOG();
		xDRV_LOG_CTRL->WRITE__LOG(log_msg);

		xDRV_LOG_CTRL->ENABLE__TIME_LOG();
		xDRV_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// LLx ...
	{
		bActive__LLx_MULTI_DOOR_VALVE = false;
		iLLx__MULTI_SLOT_SIZE = 0;

		//
		def_name = "LLx.MULTI_DOOR_VALVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		if(def_data.CompareNoCase("YES") == 0)
		{
			bActive__LLx_MULTI_DOOR_VALVE = true;

			//
			def_name = "LLx.SLOT_SIZE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			iLLx__MULTI_SLOT_SIZE = atoi(def_data);
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq;

		iSim_Flag = x_seq->Is__SIMULATION_MODE();

		iFlag__APP_LOG = 1;
		iFlag__DRV_LOG = 1;
	}

	// ...
	{
		sDRV_UnitID = "1";
	}

	// ...
	{
		CString stn_name;
		CString stn_slot;
		CString stn_id;
		int i;

		// ALx ...
		{
			stn_name = STR__AL1;
			stn_slot = "1";

			stn_id = _Get__TRG_STN(stn_name, stn_slot);

			sCH__CUR_AL1_STN_NUM->Set__DATA(stn_id);
		}
		// STx ...
		{
			stn_name = STR__BUFF1;
			stn_slot = "1";

			stn_id = _Get__TRG_STN(stn_name, stn_slot);

			sCH__CUR_ST1_STN_NUM->Set__DATA(stn_id);
		}
		// LLx ...
		for(i=0; i<CFG_LLx__SIZE; i++)
		{
			stn_name = Macro__Get_LLx_NAME(i);

			if(bActive__LLx_MULTI_DOOR_VALVE)
			{
				CString stn_slot;

				for(int k=0; k<2; k++)
				{
					int slot_id = k + 1;

					stn_slot.Format("%1d", slot_id);
					stn_id = _Get__TRG_STN(stn_name, stn_slot);

						 if(slot_id == 1)		sCH__CUR_LLx_1_STN_NUM[i]->Set__DATA(stn_id);
					else if(slot_id == 2)		sCH__CUR_LLx_2_STN_NUM[i]->Set__DATA(stn_id);
				}
			}
			else
			{
				stn_id = _Get__TRG_STN(stn_name, "1");

				sCH__CUR_LLx_STN_NUM[i]->Set__DATA(stn_id);
			}
		}
		// LPx ...
		for(i=0; i<CFG_LPx__SIZE; i++)
		{
		    stn_name = Macro__Get_LPx_NAME(i);
			stn_slot = "1";

			stn_id = _Get__TRG_STN(stn_name, stn_slot);

			sCH__CUR_LPx_STN_NUM[i]->Set__DATA(stn_id);
		}
	}

	return 1;
}
int CObj_NET__ATM_SR100::__INITIALIZE__IO(p_io_para)
{
	CString net_ip   = "";
	CString net_port = "";
	
	// ...
	{
		CString para_cmmd;
		CString para_data;

		// 1.
		{
			para_cmmd = "IP";
			
			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				net_ip = para_data;
			}
		}
		// 2.
		{
			para_cmmd = "PORT";

			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				net_port = para_data;
			}
		}
	}

	// ...
	{
		CString end_str = "";

		end_str = (char) __CR;

		int end_len = end_str.GetLength();

		mX_Net->SET__TERMINAL_InSTRING( end_str, end_len);
		mX_Net->SET__TERMINAL_OutSTRING(end_str, end_len);
	}

	// ...
	CString log_msg;
	CString log_bff;

	CString str_data;

	// ...
	{
		sEnd_InStr  = mX_Net->GET__TERMINAL_InSTRING();	
		sEnd_OutStr = mX_Net->GET__TERMINAL_OutSTRING();
	}

	// ...
	{
		log_msg.Format("Connecting to Ethernet ... \n");

		log_bff.Format("Net_IP : %s \n", net_ip);
		log_msg += log_bff;

		log_bff.Format("Net_Port : %s \n", net_port);
		log_msg += log_bff;

		//
		m_nRetryCount = 2;

		log_bff.Format(" * Retry Count: %1d \n", m_nRetryCount);
		log_msg += log_bff;

		//
		m_nTimeout = 1;			// 1 sec
		m_Rcv_Time = m_nTimeout;

		log_bff.Format(" * Recv_Timeout: %1d sec \n", m_nTimeout);
		log_msg += log_bff;

		//
		m_Out_Time = 10;		// 10 sec

		log_bff.Format("Action_Timeout: %1d sec \n", m_Out_Time);
		log_msg += log_bff;

		//
		log_bff.Format("End_InStr  : %s \n", sEnd_InStr);
		log_msg += log_bff;

		log_bff.Format("End_OutStr : %s \n", sEnd_OutStr);
		log_msg += log_bff;

		//
		xAPP_LOG_CTRL->WRITE__LOG(log_msg);
		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		CString str_info;

		str_info.Format("IP(%s) Port(%s)", net_ip,net_port);

		sCH__MON_COMMUNICATION_INFO->Set__DATA(str_info);
	}

	if(iSim_Flag > 0)
	{
		log_msg = "Simulation Mode !!! \n";

		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
		return 1;
	}

	// ...
	CString err_msg;

	mX_Net->INIT__PROPERTY(net_ip, atoi(net_port));
	if(mX_Net->CONNECT(&err_msg) < 0)
	{
		log_msg = "Connection Result ... \n";
		log_bff.Format("Fail to do INIT__ETHERNET: %s(%s), ret(-1) \n", net_ip,net_port);
		log_msg += log_bff;
		log_bff.Format(" * Error Message <- \"%s\" \n", err_msg);
		log_msg += log_bff;

		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		log_msg = "Connection Result ... \n";
		log_msg += "Init-Ethernet Completed ... \n";

		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj_NET__ATM_SR100::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
LOOP_RETRY:

	// ...
	mMNG__ERR_CODE.Clear__Error_Code();

	// ...
	int flag = -1;

	CString para__arm_type;
	CString para__stn_name;
	CString para__stn_slot;

	CString szUpperObj;

	CStringArray l_para;
	p_variable->Get__FNC_PARAMETER(l_para);

	if(l_para.GetSize() > 0)
	{
		CString para_data;
		int limit = l_para.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			para_data = l_para[i];

			switch(i)
			{
				case 0:		
					dCH__OTR_IN_PARA__ARM_TYPE->Set__DATA(para_data);
					break;

				case 1:
					dCH__OTR_IN_PARA__STN_NAME->Set__DATA(para_data);
					break;

				case 2:
					dCH__OTR_IN_PARA__STN_SLOT->Set__DATA(para_data);
					break;
			}	
		}
	} 

	dCH__OTR_IN_PARA__ARM_TYPE->Get__DATA(para__arm_type);
	dCH__OTR_IN_PARA__STN_NAME->Get__DATA(para__stn_name);
	dCH__OTR_IN_PARA__STN_SLOT->Get__DATA(para__stn_slot);

	// ...
	{
		CString log_msg;

		log_msg.Format("Start ... :  [%s] (%s,%s,%s)",
						mode,
						para__arm_type,
						para__stn_name,
						para__stn_slot);

		Fnc__APP_LOG(log_msg);
		Fnc__ACT_MSG(log_msg);
	}

	// ...
	int seq_flag = 1;

	if(dCH__CFG_ACTION_CONFIRM_FLAG->Check__DATA(STR__ENABLE) > 0)
	{
		CString log_msg;

		CString str_title;
		CString str_msg;
		CString str_bff;
		CStringArray l_act;
		CString r_act;

		str_title.Format("%s - Action Confirm Flag", sObject_Name);

		str_bff.Format("Object Mode : [%s] \n", mode);
		str_msg += str_bff;
		str_bff.Format("Arm Type : [%s] \n", para__arm_type);
		str_msg += str_bff;
		str_bff.Format("Station Name : [%s] \n", para__stn_name);
		str_msg += str_bff;
		str_bff.Format("Station Slot : [%s] \n", para__stn_slot);
		str_msg += str_bff;

		l_act.RemoveAll();
		l_act.Add(STR__YES);
		l_act.Add(STR__NO);

		p_alarm->Popup__MESSAGE_BOX(str_title,str_msg,l_act,r_act);

		if(r_act.CompareNoCase(STR__NO) == 0)
		{
			seq_flag = -1;

			CString log_msg = "Confirm : Action No Clicked !";

			Fnc__APP_LOG(log_msg);
			Fnc__ACT_MSG(log_msg);
		}
	}

	// Driver Option ...
	{
		if(dCH__CFG_ACTIVE_ACKN_SEND->Check__DATA(STR__YES) > 0)
			bActive__ACKN_Single = TRUE;
		else
			bActive__ACKN_Single = FALSE;

		if(dCH__CFG_ACTIVE_RECV_CNT_SINGLE->Check__DATA(STR__YES) > 0)	
			bActive__Recv_Cnt_Single = TRUE;
		else
			bActive__Recv_Cnt_Single = FALSE;
	}

	if(seq_flag > 0)
	{
		pII__EXT_MODE_CTRL = p_variable->Get__EXT_FNC_MODE_CTRL();

		// ...
		{
			CString log_msg;

			szUpperObj = pII__EXT_MODE_CTRL->Get__UPPER_OBJECT_NAME();	
		
			log_msg.Format("Object Call: [%s] ==> [%s]",  szUpperObj,sObject_Name);
			Fnc__APP_LOG(log_msg);
		}

			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__HOME)					flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PICK)					flag = Call__PICK(p_variable,p_alarm,  para__arm_type,para__stn_name,para__stn_slot);
		ELSE_IF__CTRL_MODE(sMODE__PLACE)				flag = Call__PLACE(p_variable,p_alarm, para__arm_type,para__stn_name,para__stn_slot);
		ELSE_IF__CTRL_MODE(sMODE__ROTATE)				flag = Call__ROTATE(p_variable,p_alarm, para__arm_type,para__stn_name,para__stn_slot);

		ELSE_IF__CTRL_MODE(sMODE__CHECK_ERROR_CODE)		flag = Call__CHECK_ERROR_CODE(p_variable,p_alarm);
	}
	else
	{
		flag = -1;
	}

	// ERR_CHECK ...
	{
		CString err_code;
		CString err_msg;

		if(dCH__ERROR_TEST__ACTIVE->Check__DATA(STR__YES) > 0)
		{
			CString err_code = sCH__ERROR_TEST__ERROR_CODE->Get__STRING();
			_Check__ERROR_CODE(err_code);
		}

		while(mMNG__ERR_CODE.Get__Error_Code(err_code,err_msg) > 0)
		{
			int i_error = atoi(err_code);
			if(i_error == 0)		continue;

			sCH__INR__ERROR_ID->Set__DATA(err_code);

			// ...
			{
				CString log_msg;
				CString log_bff;

				log_msg = "Error_Code Occurred !!!";

				log_bff.Format("Error_Code : [%s] \n", err_code);
				log_msg += log_bff;
				log_bff.Format("Error_Msg  : [%s] \n", err_msg);
				log_msg += log_bff;

				Fnc__APP_LOG(log_msg);
			}

			// ...
			int alm_id = ALID__ERROR_CODE;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			alm_msg.Format("Control_Mode : %s \n", mode);

			alm_bff.Format("Error_Code : %s \n", err_code);
			alm_msg += alm_bff;
			alm_bff.Format("Error_Message \n");
			alm_msg += alm_bff;
			alm_msg += "  * ";
			alm_msg += err_msg;

			// ...
			{
				CString log_msg;

				log_msg.Format("Alarm Post : %1d \n", alm_id);
				log_msg += alm_msg;

				Fnc__APP_LOG(log_msg);
			}

			p_alarm->Popup__ALARM_With_MESSAGE(alm_id,alm_msg,r_act);			

			if(r_act.CompareNoCase(ACT__RETRY) == 0)
			{
				CString log_msg = "Alarm Selection <- Retry";
				Fnc__APP_LOG(log_msg);

				goto LOOP_RETRY;
			}
			if(r_act.CompareNoCase(ACT__ABORT) == 0)
			{
				CString log_msg = "Alarm Selection <- Abort";
				Fnc__APP_LOG(log_msg);

				flag = -1;
			}

			if(r_act.CompareNoCase(ACT__IGNORE) == 0)
			{
				// ...
			}
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;	
		log_msg.Format("Aborted ... :  [%s]\n", mode);

		Fnc__APP_LOG(log_msg);
		Fnc__ACT_MSG(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]\n", mode);

		Fnc__APP_LOG(log_msg);
		Fnc__ACT_MSG(log_msg);
	}
	return flag;
}

int CObj_NET__ATM_SR100::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable,p_alarm);
			break;

		case MON_ID__PROC_RSP_MSG:
			Mon__PROC_RSP_MSG(p_variable, p_alarm);
			break;
	}

	return 1;
}
