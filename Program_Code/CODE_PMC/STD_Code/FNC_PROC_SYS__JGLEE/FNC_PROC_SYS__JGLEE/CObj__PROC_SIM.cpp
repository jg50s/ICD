#include "StdAfx.h"
#include "CObj__PROC_SIM.h"


//-------------------------------------------------------------------------
CObj__PROC_SIM::CObj__PROC_SIM()
{

}
CObj__PROC_SIM::~CObj__PROC_SIM()
{

}

//-------------------------------------------------------------------------
int CObj__PROC_SIM::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__PRE_READY, "PRE.READY");
		ADD__CTRL_VAR(sMODE__PRE_START, "PRE.START");

		ADD__CTRL_VAR(sMODE__MAIN_READY, "MAIN.READY");
		ADD__CTRL_VAR(sMODE__MAIN_START, "MAIN.START");

		ADD__CTRL_VAR(sMODE__POST_READY, "POST.READY");
		ADD__CTRL_VAR(sMODE__POST_START, "POST.START");

		ADD__CTRL_VAR(sMODE__MANUAL_READY, "MANUAL.READY");
		ADD__CTRL_VAR(sMODE__MANUAL_START, "MANUAL.START");

		ADD__CTRL_VAR(sMODE__JOB_STRT_READY, "JOB_START.READY");
		ADD__CTRL_VAR(sMODE__JOB_END_READY,  "JOB_END.READY");
	}
	return 1;
}
int CObj__PROC_SIM::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}

int CObj__PROC_SIM::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString var_name;
	int i;

	// OBJ ...
	{
		var_name = "OBJ.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, var_name);

		var_name = "OBJ.TIMER";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_TIMER, var_name);
	}

	// CFG ...
	{
		var_name = "CFG.DA_OFFSET_CHECK_BEFORE_PROCESSING";
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "NO  YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_DA_OFFSET_CHECK_BEFORE_PROCESSING, var_name);
	}

	// CTC REPORT ...
	{
		var_name = "sPRC.TOTAL.TIME.TO.CTC";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__PRC_TOTAL_TIME_TO_CTC, var_name);

		var_name = "sPRC.CHANGE.TIME.TO.CTC";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__PRC_CHANGE_TIME_TO_CTC, var_name);
	}

	// PARA ...
	{
		var_name = "PARA.MANUAL.PROCESS.DECHUCK.ACTIVE";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_MANUAL_PROCESS_DECHUCK_ACTIVE, var_name);

		// Manual - Step.Ctrl ...
		var_name = "PARA.MANUAL.STEP.CTRL.ACTIVE";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_MANUAL_STEP_CTRL_ACTIVE, var_name);

		var_name = "PARA.MANUAL.STEP.CTRL.REQ";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_MANUAL_STEP_CTRL_REQ, var_name);

		// Recovery.Restart ...
		var_name = "ACT_RECOVERY.RESTART_FLAG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__ACT_RECOVERY_RESTART_FLAG, var_name);
	}

	// LEARNED INFO ... 
	{
		var_name = "CFG.LEARNED.APPLY.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "DISABLE  ENABLE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_LEARNED_APPLY_MODE, var_name);

		var_name = "CUR.LEARNED_RESULT";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_LEARNED_RESULT, var_name);

		//
		var_name = "PRE.LOTID";
		STD__ADD_STRING_WITH_X_OPTION(var_name, "");
		LINK__VAR_STRING_CTRL(sCH__PRE_LOTID, var_name);

		var_name = "CUR.LEARNED.APPLY.STATUS";
		STD__ADD_STRING_WITH_X_OPTION(var_name,"");
		LINK__VAR_STRING_CTRL(sCH__CUR_LEARNED_APPLY_STATUS, var_name);

		//
		var_name = "RCP_FILE.UPLOAD_FLAG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__RCP_FILE_UPLOAD_FLAG, var_name);
	}

	// WIN.JUMP_STEP ...
	{
		var_name = "JUMP.STEP.ID";
		STD__ADD_ANALOG(var_name, "step", 0, 1, 100);
		LINK__VAR_ANALOG_CTRL(aCH__JUMP_STEP_ID, var_name);

		var_name = "CONTINUE.OVER.STEP.TIME";
		STD__ADD_ANALOG(var_name, "sec", 0, 0, 100);
		LINK__VAR_ANALOG_CTRL(aCH__CONTINUE_OVER_STEP_TIME, var_name);

		var_name = "EXCEPTION.CONTINUE.REQ";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__EXCEPTION_CONTINUE_REQ, var_name);

		//
		var_name = "WIN_CTRL.JUMP_PAGE";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__WIN_CTRL_JUMP_PAGE, var_name);

		var_name = "WIN_CTRL.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__WIN_CTRL_MSG, var_name);

		//
		var_name = "WIN_CTRL.LOCK.ACTIVE.JUMP";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__WIN_CTRL_LOCK_ACTIVE_JUMP, var_name);

		var_name = "WIN_CTRL.LOCK.ACTIVE.CONTINUE";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__WIN_CTRL_LOCK_ACTIVE_CONTINUE, var_name);

		var_name = "WIN_CTRL.LOCK.ACTIVE.ABORT";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__WIN_CTRL_LOCK_ACTIVE_ABORT, var_name);
	}

	// MON.PART ...
	{
		var_name = "MON.PART.ERROR.ACTIVE";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PART_ERROR_ACTIVE, var_name);
	}

	// MON ...
	{
		var_name = "MON.LOCK.ACTIVE.ABORT";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_LOCK_ACTIVE_ABORT, var_name);

		var_name = "MON.LOCK.ACTIVE.END";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_LOCK_ACTIVE_END, var_name);

		var_name = "MON.LOCK.ACTIVE.SKIP";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_LOCK_ACTIVE_SKIP, var_name);

		var_name = "MON.LOCK.ACTIVE.JUMP";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_LOCK_ACTIVE_JUMP, var_name);

		var_name = "MON.LOCK.ACTIVE.PAUSE";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_LOCK_ACTIVE_PAUSE, var_name);

		var_name = "MON.LOCK.ACTIVE.RESUME";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_LOCK_ACTIVE_RESUME, var_name);

		//
		var_name = "MON.EXCEPTION.ACT";
		STD__ADD_DIGITAL(var_name, "IDLE  START  RESTART  ABORT  END  SKIP  PAUSE  RESUME  JUMP  ALARM  PLASMA_DECHUCK");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_EXCEPTION_ACT, var_name);

		var_name = "MON.EXCEPTION.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_EXCEPTION_MSG, var_name);
	}

	// MON.WAFER_INFO ...
	{
		var_name = "MON.WAFER_INFO.TOTAL_COUNT.START_DATE";
		STD__ADD_STRING_WITH_X_OPTION(var_name, "");
		LINK__VAR_STRING_CTRL(sCH__MON_WAFER_INFO_TOTAL_COUNT_START_DATE, var_name);

		var_name = "MON.WAFER_INFO.TOTAL_COUNT.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "count", 0, 0, 9999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__MON_WAFER_INFO_TOTAL_COUNT_VALUE, var_name);

		var_name = "MON.WAFER_INFO.TOTAL_COUNT.RESET";
		STD__ADD_DIGITAL_WITH_COMMENT(var_name, "RETURN RESET", "");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_WAFER_INFO_TOTAL_COUNT_RESET, var_name);

		//
		var_name = "MON.WAFER_INFO.CURRENT_COUNT.START_DATE";
		STD__ADD_STRING_WITH_X_OPTION(var_name, "");
		LINK__VAR_STRING_CTRL(sCH__MON_WAFER_INFO_CURRENT_COUNT_START_DATE, var_name);

		var_name = "MON.WAFER_INFO.CURRENT_COUNT.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "count", 0, 0, 9999999, "");
		LINK__VAR_ANALOG_CTRL(aCH__MON_WAFER_INFO_CURRENT_COUNT_VALUE, var_name);

		var_name = "MON.WAFER_INFO.CURRENT_COUNT.RESET";
		STD__ADD_DIGITAL_WITH_COMMENT(var_name, "RETURN RESET", "");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_WAFER_INFO_CURRENT_COUNT_RESET, var_name);
	}

	// CUR ...
	{
		var_name = "CUR.RCP.FILE.PATH";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_RCP_FILE_PATH, var_name);

		var_name = "CUR.PROCESS.TYPE";
		STD__ADD_DIGITAL(var_name, "PRE  MAIN  POST  MANUAL");
		LINK__VAR_DIGITAL_CTRL(dCH__CUR_PROCESS_TYPE, var_name);
	}

	// Recipe Info ...
	{
		var_name = "PRC.TOTAL.TIME";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__PRC_TOTAL_TIME, var_name);

		var_name = "PRC.CUR.TIME";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__PRC_CUR_TIME, var_name);

		var_name = "STEP.CUR.TIME";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__STEP_CUR_TIME, var_name);

		//
		var_name = "STEP.TOTAL.NUM";
		STD__ADD_ANALOG(var_name, "", 0, 0, 999);
		LINK__VAR_ANALOG_CTRL(aCH__STEP_TOTAL_NUM, var_name);

		var_name = "STEP.CUR.NUM";
		STD__ADD_ANALOG(var_name, "", 0, -1, 999);
		LINK__VAR_ANALOG_CTRL(aCH__STEP_CUR_NUM, var_name);

		//
		var_name = "LOOP.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__STEP_LOOP_MSG, var_name);

		//
		var_name = "RCP.JUMP.STEP.ID";
		STD__ADD_ANALOG(var_name, "", 0, 1, 999);
		LINK__VAR_ANALOG_CTRL(aCH__RCP_JUMP_STEP_ID, var_name);
	}
	// Recipe Channel ...
	{
		// RCP - STEP ...
		{
			var_name = "RCP.STEP.MODE";
			STD__ADD_DIGITAL(var_name, "Time  Stable  Fast.Vac");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_STEP_MODE, var_name);
		}

		// RCP - LOOP ...
		{
			var_name = "RCP.LOOP_START";
			STD__ADD_ANALOG(var_name, "step", 0, 0, 100);
			LINK__VAR_ANALOG_CTRL(aCH__RCP_LOOP_START, var_name);

			var_name = "RCP.LOOP_REPEAT";
			STD__ADD_ANALOG(var_name, "cycle", 0, 0, 100);
			LINK__VAR_ANALOG_CTRL(aCH__RCP_LOOP_REPEAT, var_name);
		}
	}

	return 1;
}
int CObj__PROC_SIM::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ", sObject_Name);

	// ...
	int alarm_id;
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int i;

	iLIST_ALID__PART.RemoveAll();

	// ...
	{

	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__PROC_SIM::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString obj_name;
	CString var_name;
	CString ch_name;
	CString ch_data;
	int i;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xI_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xI_LOG_CTRL->SET__PROPERTY(file_name, 24*5, 60);

		xI_LOG_CTRL->DISABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG(log_msg);

		xI_LOG_CTRL->ENABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__PROC_SIM::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = 1;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		xI_LOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	if(flag > 0)
	{
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PRE_READY)			flag = Call__PRE_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PRE_START)			flag = Call__PRE_START(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__MAIN_READY)			flag = Call__MAIN_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MAIN_START)			flag = Call__MAIN_START(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__POST_READY)			flag = Call__POST_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__POST_START)			flag = Call__POST_START(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__MANUAL_READY)			flag = Call__MANUAL_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MANUAL_START)			flag = Call__MANUAL_START(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__JOB_STRT_READY)		flag = Call__JOB_START_READY(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__JOB_END_READY)		flag = Call__JOB_END_READY(p_variable, p_alarm);
	}

	// ...
	{
		iActive__PROC_START = -1;
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s] (%1d)", mode,flag);

		xI_LOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]", mode);

		xI_LOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	return flag;
}

int CObj__PROC_SIM::__CALL__MONITORING(id, p_variable, p_alarm)
{

	return 1;
}
