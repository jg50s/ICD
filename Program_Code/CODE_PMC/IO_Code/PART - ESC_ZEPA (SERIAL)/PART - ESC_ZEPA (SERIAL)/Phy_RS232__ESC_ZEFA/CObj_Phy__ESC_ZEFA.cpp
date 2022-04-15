#include "StdAfx.h"
#include "CObj_Phy__ESC_ZEFA.h"
#include "CCommon_DEF.h"


//--------------------------------------------------------------------------------
CObj_Phy__ESC_ZEFA::CObj_Phy__ESC_ZEFA()
{
	m_nCommState = OFFLINE;
	m_Rcv_Time	 = 1000;
	m_RetryCnt	 = 3;
	mon_flag	 = 0;
     
}
CObj_Phy__ESC_ZEFA::~CObj_Phy__ESC_ZEFA()
{

}

//--------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	// ...
	{
		sObject_Name = obj;
	}

	// ...
	{
		ADD__CTRL_VAR(sMODE__INITIAL,		"INIT");
		ADD__CTRL_VAR(sMODE__PROC_SEQ,		"PROC_START");
		ADD__CTRL_VAR(sMODE__PROC_READY,	"PROC_READY");
		ADD__CTRL_VAR(sMODE__ON,	        "OUTPUT_ON");
		ADD__CTRL_VAR(sMODE__OFF,	        "OUTPUT_OFF");
		ADD__CTRL_VAR(sMODE__TOGGLE_ON,     "TOGGLE_ON");
		ADD__CTRL_VAR(sMODE__TOGGLE_OFF,    "TOGGLE_OFF");
		ADD__CTRL_VAR(sMODE__LOCAL,	        "LOCAL");
		ADD__CTRL_VAR(sMODE__REMOTE,	    "REMOTE");
		ADD__CTRL_VAR(sMODE__VOLT_SET,	    "VOLT_SET");
		ADD__CTRL_VAR(sMODE__RAMPUP_SET,	"RAMPUP_SET");
		ADD__CTRL_VAR(sMODE__RAMPDN_SET,	"RAMPDN_SET");
		ADD__CTRL_VAR(sMODE__STATE_READ,	"STATUS_READ");
		ADD__CTRL_VAR(sMODE__CURRLIMIT_SET,	"CUR_LIM_SET");
	}

	return 1;
}
int CObj_Phy__ESC_ZEFA::__DEFINE__VERSION_HISTORY(version)
{
	version = "@pck 20180914 \n";

	return 1;
}


//.....
#define  MON_ID__MONITOR				1
#define  MON_ID__MONITOR_1				2
#define  MON_ID__MONITOR_2				3

#define APP_DSP__COMM_STATUS            "OFFLINE  ONLINE"
#define  APP_DSP__MON_MODE				"IDLE	  RUN"
#define  APP_DSP__OFF_ON				"OFF	  ON"
#define  APP_DSP__LOCAL_REMOTE			"LOCAL	  REMOTE"
#define  APP_DSP__USE_NOTUSE			"NOTUSE	  USE"
#define  APP_DSP__READING				"1"


int CObj_Phy__ESC_ZEFA::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	//-----------------------------------------------------------------------------------
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// Analog ...
	{
		str_name = "aAPP.ESC.VOLT.CH1.SET";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "V", 0, -2500, 2500, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__VOLT_SET_CH1, str_name);

		str_name = "aAPP.ESC.VOLT.CH2.SET";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "V", 0, -2500, 2500, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__VOLT_SET_CH2, str_name);

		str_name = "aAPP.ESC.VOLT.CH1.READ";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "V", 0, -2500, 2500, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__VOLT_READ_CH1, str_name);

		str_name = "aAPP.ESC.VOLT.CH2.READ";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "V", 0, -2500, 2500, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__VOLT_READ_CH2, str_name);

		str_name = "aAPP.ESC.CURR.CH1.READ";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "mA", 2, 0.00, 2.00, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__CURR_READ_CH1, str_name);

		str_name = "aAPP.ESC.CURR.CH2.READ";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "mA", 2, 0.00, 2.00, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__CURR_READ_CH2, str_name);

		str_name = "aAPP.ESC.RAMPUP.SET";
		STD__ADD_ANALOG(str_name, "sec", 1, 0.3, 9.9);
		LINK__VAR_ANALOG_CTRL(aCH__RAMPUP_SET, str_name);

		str_name = "aAPP.ESC.RAMPUP.READ";
		STD__ADD_ANALOG(str_name, "sec", 1, 0.3, 9.9);
		LINK__VAR_ANALOG_CTRL(aCH__RAMPUP_READ, str_name);

		str_name = "aAPP.ESC.RAMPDN.SET";
		STD__ADD_ANALOG(str_name, "sec", 1, 0.3, 9.9);
		LINK__VAR_ANALOG_CTRL(aCH__RAMPDN_SET, str_name);

		str_name = "aAPP.ESC.RAMPDN.READ";
		STD__ADD_ANALOG(str_name, "sec", 1, 0.3, 9.9);
		LINK__VAR_ANALOG_CTRL(aCH__RAMPDN_READ, str_name);

		str_name = "aAPP.ESC.CURRLIMIT.SET.CH1";
		STD__ADD_ANALOG(str_name,  "mA", 1, 0.3, 1.0);
		LINK__VAR_ANALOG_CTRL(aCH__CURRLIMIT_SET_CH1, str_name);

		str_name = "aAPP.ESC.CURRLIMIT.SET.CH2";
		STD__ADD_ANALOG(str_name,  "mA", 1, 0.3, 1.0);
		LINK__VAR_ANALOG_CTRL(aCH__CURRLIMIT_SET_CH2, str_name);

		str_name = "aAPP.ESC.CURRLIMIT.CH1.READ";
		STD__ADD_ANALOG(str_name,  "mA", 1, 0.3, 1.0);
		LINK__VAR_ANALOG_CTRL(aCH__CURRLIMIT_READ_CH1, str_name);

		str_name = "aAPP.ESC.CURRLIMIT.CH2.READ";
		STD__ADD_ANALOG(str_name,  "mA", 1, 0.3, 1.0);
		LINK__VAR_ANALOG_CTRL(aCH__CURRLIMIT_READ_CH2, str_name);

		str_name = "aAPP.ESC.AUTO.TOGGLE.CNT";
		STD__ADD_ANALOG(str_name,  "times", 0, 1, 10);
		LINK__VAR_ANALOG_CTRL(aCH__AUTO_TOGGLE_CNT, str_name);

		str_name = "aAPP.ESC.AUTO.TOGGLE.CNT.READ";
		STD__ADD_ANALOG(str_name,  "times", 0, 1, 10);
		LINK__VAR_ANALOG_CTRL(aCH__AUTO_TOGGLE_CNT_READ, str_name);

		str_name = "aAPP.ESC.AUTO.TOGGLE.VOLT";
		STD__ADD_ANALOG(str_name,  "V", 0, 0, 2500);
		LINK__VAR_ANALOG_CTRL(aCH__AUTO_TOGGLE_VOLT, str_name);

		str_name = "aAPP.ESC.AUTO.TOGGLE.VOLT.READ";
		STD__ADD_ANALOG(str_name,  "V", 0, 0, 2500);
		LINK__VAR_ANALOG_CTRL(aCH__AUTO_TOGGLE_VOLT_READ, str_name);
	}
	// Digital ...
	{
		str_name = "dAPP.ESC.OUTPUT";
		STD__ADD_DIGITAL_WITH_OPTION(str_name, APP_DSP__OFF_ON, -1, "E", "");		//HV Off On
		LINK__VAR_DIGITAL_CTRL(dCH__OUTPUT, str_name);

		str_name = "dAPP.ESC.TOGGLE";
		STD__ADD_DIGITAL_WITH_OPTION(str_name, APP_DSP__OFF_ON, -1, "E", "");		//Toggle Off On
		LINK__VAR_DIGITAL_CTRL(dCH__TOGGLE, str_name);

		str_name = "dAPP.ESC.AUTO.TOGGLE";
		STD__ADD_DIGITAL(str_name, APP_DSP__OFF_ON);								//Auto Toggle Off On
		LINK__VAR_DIGITAL_CTRL(dCH__AUTO_TOGGLE, str_name);

		str_name = "dAPP.ESC.ERROR.RESET";
		STD__ADD_DIGITAL(str_name, APP_DSP__OFF_ON);								//Error Reset
		LINK__VAR_DIGITAL_CTRL(dCH__ERROR_RESET, str_name);

		str_name = "dAPP.ESC.POWER.RESET";
		STD__ADD_DIGITAL(str_name, APP_DSP__OFF_ON);								//Power Supply Reset
		LINK__VAR_DIGITAL_CTRL(dCH__POWER_SUPPLY_RESET, str_name);

		str_name = "dAPP.COMM.STS";
		STD__ADD_DIGITAL(str_name, APP_DSP__COMM_STATUS);							//OffLine	OnLine
		LINK__VAR_DIGITAL_CTRL(dCH__COMM_STS, str_name);
	}
	// String ...
	{
		str_name = "sAPP.OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "sAPP.ESC.SETVOLT.CH1.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SETVOLT_READ_CH1, str_name);

		str_name = "sAPP.ESC.SETVOLT.CH2.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SETVOLT_READ_CH2, str_name);

		str_name = "sAPP.ESC.SETCURR.CH1.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SETCURR_READ_CH1, str_name);

		str_name = "sAPP.ESC.SETCURR.CH2.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SETCURR_READ_CH2, str_name);

		str_name = "sAPP.ESC.SETRAMPUP.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SETRAMPUP_READ, str_name);

		str_name = "sAPP.ESC.SETRAMPDN.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SETRAMPDN_READ, str_name);

		str_name = "sAPP.ESC.OUTPUT.READ";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__OUTPUT_STATUS, str_name);

		str_name = "sAPP.ESC.TOGGLE.READ";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__TOGGLE_STATUS, str_name);

		str_name = "sAPP.ESC.REMOTE.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__REMOTE_STATUS, str_name);

		str_name = "sAPP.ESC.AUTO.TOGGLE.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__AUTO_TOGGLE_READ, str_name);	

		str_name = "sAPP.ESC.ERROR.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ERROR_READ, str_name);	

		str_name = "sAPP.ESC.STATE.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__STATE_READ, str_name);	
	}

	// ...
	{
		str_name = "sAPP.ESC.COMM.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__COMM_STS,str_name);
	}

	// Config...
	{
		str_name = "aAPP.ESC.CFG.RAMPUP.TIME";
		STD__ADD_ANALOG(str_name, "sec", 1, 0.3, 9.9);
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RAMPUP_TIME, str_name);

		str_name = "aAPP.ESC.CFG.RAMPDN.TIME";
		STD__ADD_ANALOG(str_name, "sec", 1, 0.3, 9.9);
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RAMPDN_TIME, str_name);

		str_name = "aAPP.ESC.CFG.CURR.LIMIT.CH1";
		STD__ADD_ANALOG(str_name, "mA", 1, 0.3, 1.0);
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CURRLIMIT_CH1, str_name);

		str_name = "aAPP.ESC.CFG.CURR.LIMIT.CH2";
		STD__ADD_ANALOG(str_name, "mA", 1, 0.3, 1.0);
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CURRLIMIT_CH2, str_name);

		str_name = "aAPP.ESC.CFG.AUTO.TOGGLE.CNT";
		STD__ADD_ANALOG(str_name, "times", 0, 1, 10);
		LINK__VAR_ANALOG_CTRL(aCH__CFG_AUTO_TOGGLE_CNT, str_name);

		str_name = "aAPP.ESC.CFG.AUTO.TOGGLE.VOLT";
		STD__ADD_ANALOG(str_name, "V", 0, 0, 2500);
		LINK__VAR_ANALOG_CTRL(aCH__CFG_AUTO_TOGGLE_VOLT, str_name);

		str_name = "dAPP.ESC.CFG.AUTO.TOGGLE";
		STD__ADD_DIGITAL(str_name, APP_DSP__USE_NOTUSE);							//Config에서 AutoToggle 사용여부 판단
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_AUTO_TOGGLE_USE, str_name);

		str_name = "dAPP.ESC.CFG.TOGGLE";
		STD__ADD_DIGITAL(str_name, APP_DSP__USE_NOTUSE);							//Config에서 Toggle 사용여부 판단
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_TOGGLE_USE, str_name);

		str_name = "dAPP.ESC.CFG.NEED.REPLY";
		STD__ADD_DIGITAL(str_name, APP_DSP__OFF_ON);								//Config에서 명령에 대한 read값을 바로 전송할 때
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_NEED_REPLY, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0,MON_ID__MONITOR);
		//p_variable->Add__MONITORING_PROC(3.0,MON_ID__MONITOR_1);
		p_variable->Add__MONITORING_PROC(3.0,MON_ID__MONITOR_2);
	}
	return 1;
}
int CObj_Phy__ESC_ZEFA::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;


	// ...
	{
		alarm_id = ALID__ESCCON_OFFLINE_ALARM;

		alarm_title  = title;
		alarm_title += "ESC CONTROLLER Offline";

		alarm_msg = "ESC CONTROLLER Offline.";

		l_act.RemoveAll();
		l_act.Add("RETRY");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ESC_DATA_TYPE_ERROR;

		alarm_title  = title;
		alarm_title += "ESC_DATA_TYPE_ERROR";

		alarm_msg = "파라미터의 데이터 타입이 잘못 되었습니다.";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ESC_PARAMETER_NOT_ALLOWED;

		alarm_title  = title;
		alarm_title += "ESC_PARAMETER_NOT_ALLOWED";

		alarm_msg = "명령어에 필요한 파라미터 보다 많은 파라미터가 수신되었습니다.";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ESC_MISSING_PARAMETER;

		alarm_title  = title;
		alarm_title += "ESC_MISSING_PARAMETER";

		alarm_msg = "명령어에 필요한 파라미터 보다 적은 파라미터가 수신되었습니다.";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ESC_UNDEFINED_HEADER;

		alarm_title  = title;
		alarm_title += "ESC_UNDEFINED_HEADER";

		alarm_msg = "유효하지 않은 명령이 수신되었습니다.";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ESC_DATA_OUT_OF_RANGE;

		alarm_title  = title;
		alarm_title += "ESC_DATA_OUT_OF_RANGE";

		alarm_msg = "지정된  파라미터의 허용치를 초과했습니다";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ESC_QUERY_DEADLOCKED;

		alarm_title  = title;
		alarm_title += "ESC_QUERY_DEADLOCKED";

		alarm_msg = "출력 버퍼에 비해 너무 많은 데이터를 작성하는 명령이 수신되었으며, 입력 버퍼 역시 가득 찼습니다. 명령은 실행되지만 모든 데이터가 손신됩니다.";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ESC_QUERY_UNTERMINATED;

		alarm_title  = title;
		alarm_title += "ESC_QUERY_UNTERMINATED";

		alarm_msg = "데이터를 읽도록 지정되었지만, 출력버퍼에 데이터를 전송하는 명령이 수신되지 않았습니다.";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ESC_QUERY_INTERRUPED;

		alarm_title  = title;
		alarm_title += "ESC_QUERY_INTERRUPED";

		alarm_msg = "10개 이상의 오류가 발생하여 Error Buffer가 가득찼습니다. Error Clear가 필요합니다.";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ESC_TOO_MANY_ERRORS;

		alarm_title  = title;
		alarm_title += "ESC_TOO_MANY_ERRORS";

		alarm_msg = "10개 이상의 오류가 발생하여 Error Buffer가 가득찼습니다. Error Clear가 필요합니다.";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

// ...
int CObj_Phy__ESC_ZEFA::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	//-------------------------------------------------------
	CString str_name;

	// Analog ...
	{
		// AO
		str_name = "eao.ESC.VOLT.CH1.SET";
		IO__ADD_ANALOG_WRITE(str_name, "V", 0, -2500, 2500);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__VOLT_SET_CH1, str_name);

		str_name = "eao.ESC.VOLT.CH2.SET";
		IO__ADD_ANALOG_WRITE(str_name, "V", 0, -2500, 2500);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__VOLT_SET_CH2, str_name);

		// AI
		str_name = "eai.ESC.SETVOLT.READ";
		IO__ADD_ANALOG_READ_EX(str_name, "V", 0, -2500, 2500, "1", "2", "3");
		LINK__IO_VAR_ANALOG_CTRL(aiCH__SETVOLT_READ, str_name);

		str_name = "eai.ESC.CURRLIMIT.READ";
		IO__ADD_ANALOG_READ_EX(str_name, "mA", 1, 0.3, 1.0, "1", "2", "3");
		LINK__IO_VAR_ANALOG_CTRL(aiCH__CURRLIMIT_READ, str_name);

		str_name = "eai.ESC.RAMPUP.READ";
		IO__ADD_ANALOG_READ_EX(str_name, "sec", 1, 0.3, 9.9, "1", "2", "3");
		LINK__IO_VAR_ANALOG_CTRL(aiCH__RAMPUP_READ, str_name);

		str_name = "eai.ESC.RAMPDN.READ";
		IO__ADD_ANALOG_READ_EX(str_name, "sec", 1, 0.3, 9.9, "1", "2", "3");
		LINK__IO_VAR_ANALOG_CTRL(aiCH__RAMPDN_READ, str_name);
	}

	// Digital ...
	{
		// DI

		// DO
		str_name = "edo.ESC.OUTPUT";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);			//Off	On
		LINK__IO_VAR_DIGITAL_CTRL(doCH__OUTPUT, str_name);	

		str_name = "edo.ESC.TOGGLE";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);			//Off	On
		LINK__IO_VAR_DIGITAL_CTRL(doCH__TOGGLE, str_name);

		str_name = "edo.ESC.REMOTE";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__LOCAL_REMOTE);		//Off	On
		LINK__IO_VAR_DIGITAL_CTRL(doCH__LOCAL_REMOTE, str_name);

		//str_name = "edo.ESC.STATE.READ";
		//IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__READING);			//
		//LINK__IO_VAR_DIGITAL_CTRL(doCH__STATE_READ, str_name);

		// DI
	}

	// Stirng ...
	{
		// SO
		str_name = "eso.ESC.VOLT.SET.ALL";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(sCH__VOLT_SET_ALL, str_name);

		str_name = "eso.ESC.VOLT.CH1.SET";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__VOLT_SET_CH1, str_name);

		str_name = "eso.ESC.VOLT.CH2.SET";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__VOLT_SET_CH2, str_name);

		str_name = "eso.ESC.CURRLIMIT.SET";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__CURRLIMIT_SET, str_name);

		str_name = "eso.ESC.RAMPUP.SET";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__RAMPUP_SET, str_name);

		str_name = "eso.ESC.RAMPDN.SET";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__RAMPDN_SET, str_name);

		str_name = "eso.ESC.AUTO.TOGGLE.CNT.SET";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__AUTO_TOGGLE_CNT, str_name);

		str_name = "eso.ESC.AUTO.TOGGLE.VOLT.SET";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__AUTO_TOGGLE_VOLT, str_name);

		str_name = "eso.ESC.STATE.READ";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__STATE_READ, str_name);

		str_name = "eso.ESC.ERROR.READ";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__ERROR_READ, str_name);

		// SI
	}


	return 1;
}

//--------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;

	// ...
	{
		CString file_name;
		CString log_msg;

		// APP Log ...
		{
			file_name.Format("%s__APP.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xI__APP_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xI__APP_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

			xI__APP_LOG_CTRL->DISABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG(log_msg);

			xI__APP_LOG_CTRL->ENABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG("   START   \n");
		}

		// DRV Log ...
		{
			file_name.Format("%s__DRV.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xI__DRV_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xI__DRV_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

			xI__DRV_LOG_CTRL->DISABLE__TIME_LOG();
			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);

			xI__DRV_LOG_CTRL->ENABLE__TIME_LOG();
			xI__DRV_LOG_CTRL->WRITE__LOG("   START   \n");
		}
	}

	// ...
	{
		def_name = "FLAG__DRV_LOG";

		if(p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data) > 0)
		{
			if(def_data.CompareNoCase("YES") == 0)		iFLAG__DRV_FLAG =  1;
			else										iFLAG__DRV_FLAG = -1;
		}
		else
		{
			iFLAG__DRV_FLAG = -1;
		}
	}

	// RESOLUTION TYPE ...
	/*
	{
		def_name = "RESOLUTION.TYPE";
		def_data = "";

		p_ext_obj_create->Get__DEF_CONST_DATA_EX(def_name, def_data, -1);

		if(def_data.CompareNoCase("FULL") == 0)
		{
			iResolution_type = RESOULTION_TYPE__FULL;
		}
		else
		{
			iResolution_type = RESOULTION_TYPE__INT;
		}
	}
	*/

	return 1;
}
int CObj_Phy__ESC_ZEFA::__INITIALIZE__IO(p_io_para)
{
	int com_port = -1;

	int nRate   = 19200;
	int nByte   = 8;			// 5, 6, 7, 8
	int nStop   = 1;			// 1, 2
	int nParity = 0;			// 0 ~ 4 : None, Odd, Even, Mark, Space

	m_Term_Str[0] = LF;	

	// ...
	{
		CString str_cmmd;
		CString str_data;

		// 1.
		{
			str_cmmd = "COM_PORT";

			if(p_io_para->Get__PARAMETER_DATA(str_cmmd, str_data) > 0)
			{
				com_port = atoi(str_data);
			}
		}
	}

	// ...
	{
		sPROTOCOL_INFO.Format("Rate[%1d] DataBit[%1d] StopBit[%1d] Parity[%1d] \n",
			                  nRate, nByte, nStop, nParity);

		sPROTOCOL_INFO += "Terminal String : [CR] \n";
	}

	// ...
	{
		mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity);
	}

	//Fnc__Initial_CRC_ETC();

	return 1;
}


//--------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	CString msg;
	int flag = -1;

	// ...
	{
		msg.Format("%s Started...",mode);
		sCH__OBJ_MSG->Set__DATA(msg);

		Write__APP_LOG(msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INITIAL)			flag = FNC__INITIAL(p_variable,p_alarm);
		//ELSE_IF__CTRL_MODE(sMODE__ON)				flag = Call__ON(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ON)				flag = FNC__ON_SEQ(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__OFF)				flag = Call__OFF(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__TOGGLE_ON)		flag = Call__TOGGLE(p_variable,p_alarm,MODE__ON);
		ELSE_IF__CTRL_MODE(sMODE__TOGGLE_OFF)		flag = Call__TOGGLE(p_variable,p_alarm,MODE__OFF);
		ELSE_IF__CTRL_MODE(sMODE__LOCAL)			flag = Call__LOCAL(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__REMOTE)			flag = Call__REMOTE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__VOLT_SET)			flag = Call__VOLT_SET(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CURRLIMIT_SET)	flag = Call__CURRLIMIT_SET(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__RAMPUP_SET)		flag = Call__RAMPUP_SET(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__RAMPDN_SET)		flag = Call__RAMPDN_SET(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__STATE_READ)		flag = Call__STATE_READ(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PROC_SEQ)			flag = FNC__PROC_SEQ(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PROC_READY)		flag = FNC__PROC_READY(p_variable,p_alarm);

		else									
		{

		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		msg.Format("%s Aborted (%1d)", mode, flag);
	}
	else
	{
		msg.Format("%s Completed (%1d)", mode, flag);
	}	

	// ...
	{
		sCH__OBJ_MSG->Set__DATA(msg);

		Write__APP_LOG(msg);
	}

	return flag;
}

int CObj_Phy__ESC_ZEFA::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__MONITOR:
			Mon__MONITOR(p_variable,p_alarm);
			break;
		/*case MON_ID__MONITOR_1:
			Mon__MONITOR_1(p_variable,p_alarm);
			break;
		*/
		case MON_ID__MONITOR_2:
			Mon__MONITOR_2(p_variable,p_alarm);
			break;
	}

	return 1;
}
