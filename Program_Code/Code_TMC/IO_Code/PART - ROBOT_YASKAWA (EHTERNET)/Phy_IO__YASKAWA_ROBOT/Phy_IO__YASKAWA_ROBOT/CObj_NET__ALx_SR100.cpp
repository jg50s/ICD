#include "StdAfx.h"
#include "CObj_NET__ALx_SR100.h"
#include "CObj_NET__ALx_SR100__DEF.h"
#include "CObj_NET__ALx_SR100__ALID.h"

#include "CCommon_DEF.h"
#include "Macro_Function.h"


//--------------------------------------------------------------------------------
CObj_NET__ALx_SR100::CObj_NET__ALx_SR100()
{

	m_nCommState = ONLINE;
}
CObj_NET__ALx_SR100::~CObj_NET__ALx_SR100()
{

}

//--------------------------------------------------------------------------------
int CObj_NET__ALx_SR100::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,    "INIT");				

		ADD__CTRL_VAR(sMODE__ALGN,	  "ALGN");	
		ADD__CTRL_VAR(sMODE__ALIGN,	  "ALIGN");	

		ADD__CTRL_VAR(sMODE__VAC_ON,  "VAC_ON");
		ADD__CTRL_VAR(sMODE__VAC_OFF, "VAC_OFF");

		ADD__CTRL_VAR(sMODE__CHECK_ERROR_CODE, "CHECK.ERROR_CODE");
	}
	return 1;
}
int CObj_NET__ALx_SR100::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR									1
#define  MON_ID__PROC_RSP_MSG								2

// ...
#define APP_DSP__DSlot										\
"1  2  3  4  5  6  7  8  9  10								\
11 12 13 14 15 16 17 18 19  20								\
21 22 23 24 25 26 27 28 29  30"


int CObj_NET__ALx_SR100::__DEFINE__VARIABLE_STD(p_variable)
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

	// Simulation ...
	{
		str_name = "OTR.IN.CFG.dSIMUL.FLAG";
		STD__ADD_DIGITAL(str_name, "NO YES");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_CFG__SIMUL_FLAG,str_name);

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

		str_name = "INR.sALGINER.ERROR.ID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INR__ALGINER_ERROR_ID,str_name);
	}

	// PARA CHANNEL ...
	{
		str_name = "PARA.CCD.POS";
		STD__ADD_ANALOG(str_name,"deg",1,0.0,360.0);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_CCD_POS, str_name);
	
		// ALx È£È¯¿ë Channel ...
		str_name = "PARA.STN.SLOT";
		STD__ADD_DIGITAL(str_name, APP_DSP__DSlot);
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_STN_SLOT, str_name);
	}

	// CONFIG CHANNEL ...
	{
		str_name = "CFG.ACTION.CONFIRM.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"DISABLE ENABLE","");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_ACTION_CONFIRM_FLAG,str_name);
	}

	// ROBOT ...
	{
		str_name = "OTR.OUT.CFG.ROM.RATE";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__OTR_OUT_CFG__ROM_DATE, str_name);

		str_name = "OTR.OUT.CFG.ROM.VERSION";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__OTR_OUT_CFG__ROM_VERSION, str_name);
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

	// ERROR TEST ...
	{
		str_name = "ERROR_TEST.ACTIVE";
		STD__ADD_DIGITAL(str_name, "NO YES");
		LINK__VAR_DIGITAL_CTRL(dCH__ERROR_TEST__ACTIVE, str_name);

		str_name = "ERROR_TEST.ERROR_CODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ERROR_TEST__ERROR_CODE, str_name);
	}

	// PRE-ALIGNER ...
	{
		str_name = "MON.PA_STS.VACUUM_STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PA_STS__VACUUM_STS, str_name);

		str_name = "MON.PA_STS.WAFER_SNS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PA_STS__WAFER_SNS, str_name);

		str_name = "MON.PA_STS.CHUCKING_CMMD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PA_STS__CHUCKING_CMMD, str_name);
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

	// ATMAlignOCRTime
	str_name = "CFG.aALIGN.OCR.TIME";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0.5,100.0,"recommand:4 sec");

	// ATMPadType
	str_name = "CFG.dPAD.TYPE";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "UNKNOWN", "");
	LINK__VAR_DIGITAL_CTRL(dCH__CFG_PAD_TYPE,str_name);

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

	// ...
	str_name = "CFG.dALIGN.SKIP";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "");
	LINK__VAR_DIGITAL_CTRL(dCH__CFG_ALIGN_SKIP,str_name);

	// WaferAlignmentBeforePostProcessedIMMMeasurement
	str_name = "CFG.dWFR.ALGN.BEFORE.IMM.MEASURE";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "rec:TRUE");

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


int CObj_NET__ALx_SR100::__DEFINE__ALARM(p_alarm)
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


int CObj_NET__ALx_SR100::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	CString str_name;

	// Digital ...
	{
		CString d_list;

		// DO
		{
			d_list  = _CMMD__Align;
			d_list += " ";
			d_list += _CMMD__VacOn;
			d_list += " ";
			d_list += _CMMD__VacOff;
			d_list += " ";
			d_list += _CMMD__ALErrClr;
			d_list += " ";

			str_name = "do.AL_Command";
			IO__ADD_DIGITAL_WRITE(str_name, d_list);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__AL_CMMD, str_name);
		}

		// DI
		{
			str_name = "di.PA.Sts";
			IO__ADD_DIGITAL_READ__MANUAL(str_name, APP_DSP__DOffOn);
			LINK__IO_VAR_DIGITAL_CTRL(diCH__PA_STS, str_name);
		}
	}

	return 1;
}

//--------------------------------------------------------------------------------
int CObj_NET__ALx_SR100::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
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

	// ...
	{
		SCX__SEQ_INFO x_seq;

		iSim_Flag = x_seq->Is__SIMULATION_MODE();

		iFlag__APP_LOG = 1;
		iFlag__DRV_LOG = 1;

		dPARA__TRG_ANGLE = 0.0;
	}

	// ...
	{
		sDRV_UnitID = "2";
	}
	return 1;
}
int CObj_NET__ALx_SR100::__INITIALIZE__IO(p_io_para)
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
int CObj_NET__ALx_SR100::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
LOOP_RETRY:

	// ...
	mMNG__ERR_CODE.Clear__Error_Code();

	// ...
	int flag = -1;

	// ...
	{
		CString log_msg;

		log_msg.Format("Start : [%s] ...", mode);

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

	if(seq_flag > 0)
	{
		pII__EXT_MODE_CTRL = p_variable->Get__EXT_FNC_MODE_CTRL();

		// ...
		{
			CString log_msg;

			CString upper_obj = pII__EXT_MODE_CTRL->Get__UPPER_OBJECT_NAME();	
		
			log_msg.Format("Object Call: [%s] ==> [%s]",  upper_obj,sObject_Name);
			Fnc__APP_LOG(log_msg);
		}

			 IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ALGN)		    	flag = Call__ALIGN(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ALIGN)			flag = Call__ALIGN(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__VAC_ON)			flag = Call__VAC_ON(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__VAC_OFF)			flag = Call__VAC_OFF(p_variable,p_alarm);

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

int CObj_NET__ALx_SR100::__CALL__MONITORING(id, p_variable, p_alarm)
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
