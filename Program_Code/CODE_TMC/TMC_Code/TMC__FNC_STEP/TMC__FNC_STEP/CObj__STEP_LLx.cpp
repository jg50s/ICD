#include "StdAfx.h"
#include "CObj__STEP_LLx.h"


//-------------------------------------------------------------------------
CObj__STEP_LLx::CObj__STEP_LLx()
{
	iPRC_FLAG = -1;
	iSTEP_CHANGE_FLAG = -1;
	iSTEP_COUNT = 0;
}
CObj__STEP_LLx::~CObj__STEP_LLx()
{

}

//-------------------------------------------------------------------------
int CObj__STEP_LLx::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	"INIT");
		ADD__CTRL_VAR(sMODE__RCP_DATA_INIT, "RCP_DATA_INIT");

		ADD__CTRL_VAR(sMODE__READY,	"READY");
		ADD__CTRL_VAR(sMODE__START, "START");
		ADD__CTRL_VAR(sMODE__PROC,	"PROC");
		
		ADD__CTRL_VAR(sMODE__CFG_PROC, "CFG_PROC");

		ADD__CTRL_VAR(sMODE__PROC_SYSTEN_INIT, "PROC.SYSTEM_INIT");
		ADD__CTRL_VAR(sMODE__ABORT,	"ABORT");
		
		ADD__CTRL_VAR(sMODE__END,	"END");

		ADD__CTRL_VAR(sMODE__STEP_DB_CHECK,	"STEP_DB_CHECK");
	}
	return 1;
}
int CObj__STEP_LLx::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__WAFER_COUNT_CTRL					1


// ...
#define  APP_DSP__DISABLE_ENABLE					\
"DISABLE ENABLE"

#define  APP_DSP__ENABLE_DISABLE					\
"ENABLE DISABLE"

#define  APP_DSP__TEMPERATURE_MODE					\
"DISABLE ENABLE STEP_CTRL"

#define  APP_DSP__RETURN_RESET						\
"RETURN RESET"

#define  APP_DSP__NEXT_LEARNED_MODE					\
"DISABLE ENABLE WAP_POS VAT_POS"


int CObj__STEP_LLx::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString var_name;
	CString item_list;
	int i;

	CString def_name;
	CString log_type = "L";
	CString evt_type = "E";
	int evt_id = -1;

	def_name = "DATA.LOG_TYPE";
	p_variable->Get__DEF_CONST_DATA(def_name, log_type);

		 if(log_type.CompareNoCase("L1") == 0)		evt_id = 1;
	else if(log_type.CompareNoCase("L2") == 0)		evt_id = 2;
	else if(log_type.CompareNoCase("L3") == 0)		evt_id = 3;
	else if(log_type.CompareNoCase("L4") == 0)		evt_id = 4;

	if(evt_id > 0)		evt_type.Format("E%1d", evt_id);

	// ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "OBJ.SUB.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_SUB_MSG, str_name);
	}

	// Config Channel ...
	{
		str_name = "CFG.ESC.MAX.TEMP.DIFFERENCE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "C", 0, 10, 50, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_MAX_TEMP_DIFFERENCE, str_name);
	}

	// ...
	{
		str_name = "CUR.PROC.TYPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_PROC_TYPE, str_name);
		
		str_name = "XFER.BALLAST_CTRL.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__XFER_BALLAST_CTRL_FLAG, str_name);

		//
		str_name = "RCP.FILE.PATH";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RCP_FILE_PATH, str_name);

		str_name = "RCP.DATA.APP.LOG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "Disable Enable", "");
		LINK__VAR_DIGITAL_CTRL(dCH__RCP_DATA_APP_LOG, str_name);
	
		str_name = "RCP.MON.STEP.NO";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "sec", 0, 0, 10000, -1, log_type, "");
		LINK__VAR_ANALOG_CTRL(aCH__RCP_MON_STEP_NO, str_name);

		str_name = "RCP.FDC.STEP.TIME";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "sec", 0, 0, 10000, -1, log_type, "");
		LINK__VAR_ANALOG_CTRL(aCH__RCP_FDC_STEP_TIME, str_name);
	}

	// ...
	{
		str_name = "STEP.TIME.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__STEP_TIME_COUNT, str_name);
	}

	// ...
	{
		str_name = "EXCEPTION.COMMAND";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__EXCEPTION_COMMAND, str_name);

		//
		str_name = "EXCEPTION_CONTINUE.REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__EXCEPTION_CONTINUE_REQ, str_name);

		str_name = "EXCEPTION_CONTINUE.STEP_OVER_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__EXCEPTION_CONTINUE_STEP_OVER_TIME, str_name);

		//
		str_name = "STEP.TIME.ABORT.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__STEP_TIME_ABORT_FLAG, str_name);
	}

	// ...
	{
		str_name = "FDC.PIN.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__FDC_PIN_STATUS, str_name);
	}

	// WAFER INFO ...
	{
		str_name = "TOTAL.COUNT.START.DATE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__TOTAL_COUNT_START_DATE, str_name);

		str_name = "WAFER.TOTAL.COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"count",0,0,9999999,"");
		LINK__VAR_ANALOG_CTRL(aCH__WAFER_TOTAL_COUNT, str_name);

		//
		str_name = "CURRENT.COUNT.START.DATE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__CURRENT_COUNT_START_DATE, str_name);

		str_name = "WAFER.CURRENT.COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"count",0,0,9999999,"");
		LINK__VAR_ANALOG_CTRL(aCH__WAFER_CURRENT_COUNT, str_name);

		str_name = "WAFER.COUNT.COUNT.RESET";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__RETURN_RESET,"");
		LINK__VAR_DIGITAL_CTRL(dCH__WAFER_CURRENT_COUNT_RESET, str_name);

		str_name = "WAFER.TOTAL.COUNT.RESET";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__RETURN_RESET,"");
		LINK__VAR_DIGITAL_CTRL(dCH__WAFER_TOTAL_COUNT_RESET, str_name);
	}

	// ...
	{	
		str_name = "ACTIVE.MFC.CLOSE.DELAY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ACTIVE__MFC_CLOSE_DELAY, str_name);

		str_name = "CFG.STEP_DELAY.MFC_CLOSE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 1.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_DELAY_MFC_CLOSE, str_name);
	}

	// RECIPE : STEP ...
	{
		var_name = "RCP.STEP.MESSAGE";
		STD__ADD_STRING_WITH_OPTION(var_name, -1, evt_type, "");
		LINK__VAR_STRING_CTRL(sCH__RCP_STEP_MESSAGE, var_name);

		var_name = "RCP.STEP.MODE";
		STD__ADD_DIGITAL_WITH_OPTION(var_name, "Time Stable End", -1, evt_type, "");
		LINK__VAR_DIGITAL_CTRL(dCH__RCP_STEP_MODE, var_name);

		var_name = "RCP.STEP.TIME";
		STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0, 9999, -1, evt_type, "");
		LINK__VAR_ANALOG_CTRL(aCH__RCP_STEP_TIME, var_name);

		//
		var_name = "RCP.APC.MODE";
		STD__ADD_DIGITAL_WITH_OPTION(var_name, "Position Pressure", -1, evt_type, "");
		LINK__VAR_DIGITAL_CTRL(dCH__RCP_APC_MODE, var_name);

		var_name = "RCP.APC.PRESSURE";
		STD__ADD_ANALOG_WITH_OPTION(var_name, "torr", 3, 0, 10, -1, evt_type, "");
		LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_PRESSURE, var_name);

		var_name = "RCP.APC.POSITION";
		STD__ADD_ANALOG_WITH_OPTION(var_name, "%", 3, 0, 100, -1, evt_type, "");
		LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_POSITION, var_name);

		var_name = "RCP.APC.PRESET.POS";
		STD__ADD_ANALOG_WITH_OPTION(var_name, "%", 3, 0, 100, -1, evt_type, "");
		LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_PRESET_POS, var_name);

		var_name = "RCP.APC.HOLD.DELAY";
		STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0, 10, -1, evt_type, "");
		LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_HOLD_DELAY, var_name);

		//
		var_name = "RCP.GAS.N2.FLOW";
		STD__ADD_ANALOG_WITH_OPTION(var_name, "sccm", 3, 0, 10000, -1, evt_type, "");
		LINK__VAR_ANALOG_CTRL(aCH__RCP_GAS_N2_FLOW, var_name);

		//
		var_name = "RCP.LIFT_PIN.MODE";
		STD__ADD_DIGITAL_WITH_OPTION(var_name, "Down Up", -1, evt_type, "");
		LINK__VAR_DIGITAL_CTRL(dCH__RCP_LIFT_PIN_MODE, var_name);

		//
		var_name = "RCP.LOOP_START";
		STD__ADD_ANALOG_WITH_OPTION(var_name, "step", 0, 0, 100, -1, evt_type, "");
		LINK__VAR_ANALOG_CTRL(aCH__RCP_LOOP_START, var_name);

		var_name = "RCP.LOOP_REPEAT";
		STD__ADD_ANALOG_WITH_OPTION(var_name, "step", 0, 0, 1000, -1, evt_type, "");
		LINK__VAR_ANALOG_CTRL(aCH__RCP_LOOP_REPEAT, var_name);
	}

	// RECIPE : CFG ...
	{
		var_name = "CFG.PARA.STEP.TIME";
		STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0, 9999, 1, evt_type, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PARA_STEP_TIME, var_name);

		//
		var_name = "CFG.PARA.APC.MODE";
		STD__ADD_DIGITAL_WITH_OPTION(var_name, "Position Pressure", 1, evt_type, "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PARA_APC_MODE, var_name);

		var_name = "CFG.PARA.APC.PRESSURE";
		STD__ADD_ANALOG_WITH_OPTION(var_name, "torr", 3, 0, 10, 1, evt_type, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PARA_APC_PRESSURE, var_name);

		var_name = "CFG.PARA.APC.POSITION";
		STD__ADD_ANALOG_WITH_OPTION(var_name, "%", 3, 0, 100, 1, evt_type, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PARA_APC_POSITION, var_name);

		//
		var_name = "CFG.PARA.GAS.N2.FLOW";
		STD__ADD_ANALOG_WITH_OPTION(var_name, "sccm", 3, 0, 10000, 1, evt_type, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PARA_GAS_N2_FLOW, var_name);

		//
		var_name = "CFG.PARA.LIFT_PIN.MODE";
		STD__ADD_DIGITAL_WITH_OPTION(var_name, "Down Up", 1, evt_type, "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PARA_LIFT_PIN_MODE, var_name);
	}

	// LEARNED INFO ... 
	{
		str_name = "CUR.LOTID";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__CUR_LOTID, str_name);

		str_name = "PRE.LOTID";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__PRE_LOTID, str_name);

		str_name = "LEARNED.APPLY.STATUS";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__LEARNED_APPLY_STATUS, str_name);
	}

	// LEARNED DATA ... 
	{
		// APPLY MODE ...
		{
			str_name = "CFG.LEARNED.APPLY.MODE";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "ENABLE DISABLE", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_LEARNED_APPLY_MODE, str_name);
		}
		// RESULT ...
		{
			str_name = "LEARNED_RESULT";
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__LEARNED_RESULT, str_name);
		}
	}

	// RANGE PARAETER ...
	{
		str_name = "CFG.RANGE.ZERO";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"num",0,0,0,"");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RANGE_ZERO, str_name);
	}
	// Process IO Interlock Check ...
	{
		str_name = "CFG.IO.INTERLOCK.SKIP";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "Disable Enable", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_IO_INTERLOCK_SKIP, str_name);
	}

	// PRE_RECIPE ...
	{
		str_name = "PRE_RCP.APC.CTRL";	
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PRE_RCP_APC_CTRL, str_name);

		str_name = "PRE_RCP.MFC.GAS.N2.FLOW";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PRE_RCP_MFC_SET_FLOW, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__WAFER_COUNT_CTRL);
	}	
	return 1;
}

int CObj__STEP_LLx::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;
	
	// ...
	CString title;
	title.Format("%s : ",sObject_Name);
	
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;
	
	// ...
	{
		alarm_id = ALID__PROCESS_STEP_OVERTIME;
		alarm_title  = title;
		alarm_title += " SYSTEM - PROCESS STEP OVERTIME ALARM.";
	
		alarm_msg = "Process Step Timeover Alarm Message.\n";
		alarm_msg += "Check Process Step time and Control time.";
	
		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PROCESS_STABLE_OVERTIME;
		alarm_title  = title;
		alarm_title += " SYSTEM - PROCESS STEP STABLE OVERTIME ALARM.";
	
		alarm_msg = "Process Stable Step Timeover Alarm Message.\n";
		alarm_msg += "Check Process Stable Step time and Control time.";
	
		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PROCESS_CH_INTERLOCK_ALARM;
		alarm_title  = title;
		alarm_title += " SYSTEM - PROCESS INTERLOCK CHANNEL ALARM.";
	
		alarm_msg = "Process Interlock Channel Alarm Message.\n";
		alarm_msg += "Check Interlock Switch Status.";
	
		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	
	// ...
	{
		alarm_id = ALID__SYSTEM_INTERLOCK_SENSOR_ERROR;

		alarm_title  = title;
		alarm_title += " SYSTEM - Interlock Sensor Error !";

		alarm_msg = "Please, check interlock sensor. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__MFC_INTERLOCK_CLOSE_ERROR;

		alarm_title  = title;
		alarm_title += " - MFC Interlock Close Error !";

		alarm_msg = "Please, check mfc interlock page. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PROCESS_RECIPE_FILE_CHANGING_NOW;
		
		alarm_title  = title;
		alarm_title += "Process recipe file is being changed, now. \n";
		
		alarm_msg  = "The process will run after recipe file save. \n";
		alarm_msg += "Please, wait or recipe file. \n";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	
	// CHM PRESSURE ...
	// ...
	{
		alarm_id = ALID__CHM_PRESSURE_TOLERANCE_WARNING;

		alarm_title  = title;
		alarm_title += "Chamber Pressure Tolerance Warning !";

		alarm_msg  = "During process run, chamber pressure tolerance warning occurred !\n";
		alarm_msg += "Please, check chamber pressure.\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__CHM_PRESSURE_TOLERANCE_FAULT;

		alarm_title  = title;
		alarm_title += "Chamber Pressure Tolerance Fault !";

		alarm_msg  = "During process run, chamber pressure tolerance fault occurred !\n";
		alarm_msg += "Please, check chamber pressure.\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__MIDDLE_PIN_UP_TIMEOUT;
	
		alarm_title  = title;
		alarm_title += "Middle-Pin Up Timeout !";
		
		alarm_msg  = "Please, check recipe step about middle-pin, or pin sensor. \n";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__GAS_BOX__ERROR_SENSOR_DETECTED;
		
		alarm_title  = title;
		alarm_title += "The door of gas box is not closed !";
		
		alarm_msg  = "If chamber's status is \"processing\", process will be aborted. \n";
		alarm_msg += "If chamber's status is \"idle\", chamber's status will be \"maint\". \n";
		alarm_msg += "Please, check the status of gas box. \n";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PROC_RESTART_SYSTEM_INIT_ERROR;

		alarm_title  = title;
		alarm_title += "\"Restart\" Recovery Action : System Init Error";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		int alarm_id = ALID__CHAMBER_LID__OPEN;
		
		alarm_title  = title;
		alarm_title += "\"Chamber's lid is not close !";
		
		alarm_msg  = "After chamber PM, you must check \"WAP Conductance\". \n";
		alarm_msg += "\n";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		int alarm_id = ALID__SYSTEM_INTERLOCK_OCCUR;

		alarm_title  = title;
		alarm_title += "System interlock occurred !";
		
		alarm_msg = "";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__STEP_LLx::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__STEP_LLx::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	xI_TIMER->REGISTER__ABORT_OBJECT(sObject_Name);

	// ...
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;
	int i;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log",sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name, 24*5, 60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// LINK_DB : STEP ...
	{
		def_name = "LINK_DB.STEP";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "SLOT01.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SLOT01_STATUS, obj_name,var_name);

		var_name = "SLOT01.LOTID";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CUR_LOTID, obj_name,var_name);
	}
	// LINK_DB : RCP ...
	{
		def_name = "LINK_DB.RCP";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "CFG.PARA.MFC.N2.RANGE.MIN";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_PARA_MFC_N2_RANGE_MIN, obj_name,var_name);

		var_name = "CFG.PARA.MFC.N2.RANGE.MAX";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_PARA_MFC_N2_RANGE_MAX, obj_name,var_name);

		var_name = "CFG.PARA.MFC.N2.RANGE.DEC";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_PARA_MFC_N2_RANGE_DEC, obj_name,var_name);
	}

	// FNC PROC
	{
		def_name = "OBJ__FNC_PROC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__PROC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		var_name = "EXCEPTION.ACT";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EXCEPTION_ACT, obj_name,var_name);

		var_name = "STEP.CUR.NUM";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__STEP_CUR_NUM, obj_name,var_name);

		var_name = "LAST.STEP.FLAG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LAST_STEP_FLAG, obj_name,var_name);

		var_name = "RCP_FILE.UPLOAD_FLAG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RCP_FILE_UPLOAD_FLAG, obj_name,var_name);
	}

	// OBJ : LLx_CHM ...
	{
		def_name = "OBJ__LLx_CHM";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__LLx_CHM = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}
	// OBJ : APC ...
	{
		def_name = "OBJ__APC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
		
		pOBJ_CTRL__APC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		var_name = STR__CTRL;
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__CTRL, obj_name,var_name);

		var_name = "PARA.PRESSURE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_PRESSURE, obj_name,var_name);

		var_name = "PARA.POSITION";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_POSITION, obj_name,var_name);

		var_name = "PARA.PRE_POS.VALUE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_PRE_POS_VALUE,	obj_name,var_name);

		var_name = "PARA.PRE_POS.SEC";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_PRE_POS_SEC, obj_name,var_name);

		var_name = "INR.OUT.dAPC.ABORT.FLAG";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__ABORT_FLAG, obj_name,var_name);

		var_name = "APC.STABLE.FLAG";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__STABLE_FLAG, obj_name,var_name);
	}
	// OBJ - MFC_N2
	{
		def_name = "OBJ__MFC_N2";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__MFC_N2 = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		var_name = STR__CTRL;
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MFC_N2__OBJ_CTRL, obj_name,var_name);

		var_name = "CFG.MFC.USE.FLAG";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MFC_N2__CFG_USE_FLAG, obj_name,var_name);

		var_name = "PARA.SET.FLOW";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MFC_N2__SET_FLOW, obj_name,var_name);

		var_name = "MON.MFC.READ.FLOW";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MFC_N2__GET_FLOW, obj_name,var_name);

		var_name = "CFG.GAS.NAME";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MFC_N2__CFG_GASx_NAME, obj_name,var_name);

		var_name = "MFC.ABORT.FLAG";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MFC_N2__ABORT_FLAG, obj_name,var_name);

		var_name = "MFC.STABLE.FLAG";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MFC_N2__STABLE_FLAG, obj_name,var_name);
	}

	// ...
	{
		iOBJ_BUSY_FLAG = -1;
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;
		iSIM_FLAG = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__STEP_LLx::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		iOBJ_BUSY_FLAG = 1;
	}

	// ...
	{
		CString log_msg;
		CString obj_msg;

		obj_msg.Format("Start ... :  [%s]", mode);

		log_msg.Format("\n%s  --------------------------------------------------------------",
					   obj_msg);

		xLOG_CTRL->WRITE__LOG(log_msg);

		//
		sCH__OBJ_MSG->Set__DATA(obj_msg);
		sCH__OBJ_SUB_MSG->Set__DATA("");
	}

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__RCP_DATA_INIT)
		{
			flag = Call__RCP_DATA_INIT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__READY)
		{
			flag = Call__READY(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__START)
		{
			flag = Call__START(p_variable,p_alarm);

			iSTEP_COUNT = 0;
		}
		ELSE_IF__CTRL_MODE(sMODE__PROC)
		{
			iSTEP_COUNT++;

			flag = Call__PROC(p_variable,p_alarm, false);
		}
		ELSE_IF__CTRL_MODE(sMODE__CFG_PROC)
		{
			flag = Call__PROC(p_variable, p_alarm, true);
		}
		ELSE_IF__CTRL_MODE(sMODE__PROC_SYSTEN_INIT)
		{
			flag = Call__PROC_SYSTEM_INIT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__ABORT)
		{
			flag = Call__ABORT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__END)
		{
			flag = Call__END(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__STEP_DB_CHECK)
		{
			flag = Call__STEP_DB_CHECK(p_variable,p_alarm);
		}
	}

	// ...
	{
		sCH__EXCEPTION_CONTINUE_REQ->Set__DATA("");
		sCH__EXCEPTION_CONTINUE_STEP_OVER_TIME->Set__DATA("");
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		
		log_msg.Format("Aborted [%d] ... : [%s] -- Ctrl [%1d]", 
				       flag, 
					   mode,
					   p_variable->Check__CTRL_ABORT());

		xLOG_CTRL->WRITE__LOG(log_msg);	
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed [%d] ... :  [%s]", flag, mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	iOBJ_BUSY_FLAG = -1;
	return flag;
}

int CObj__STEP_LLx::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__WAFER_COUNT_CTRL)
	{
		Mon__Wafer_Count_Ctrl(p_variable,p_alarm);
		return 1;
	}

	return 1;
}
