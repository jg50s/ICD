#include "StdAfx.h"
#include "CObj__PROC_STD.h"


//-------------------------------------------------------------------------
CObj__PROC_STD::CObj__PROC_STD()
{

}
CObj__PROC_STD::~CObj__PROC_STD()
{

}

//-------------------------------------------------------------------------
int CObj__PROC_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
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
int CObj__PROC_STD::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}

// ...
#define MON_ID__EXCEPTION_ACT					1


int CObj__PROC_STD::__DEFINE__VARIABLE_STD(p_variable)
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

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__EXCEPTION_ACT);
	}
	return 1;
}
int CObj__PROC_STD::__DEFINE__ALARM(p_alarm)
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

	// Process Recipe does not exist ...
	{
		alarm_id = ALID__PROCESS_RECIPE_NOT_EXIST;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Process recipe does not exist.";

		alarm_msg = "Please, check process recipe file.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__RETRY);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// Process Recovery Action With Wafer ...
	{
		alarm_id = ALID__PROCESS_RECOVERY_CHECK_WITH_WAFER;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Check Process Recovery Action !";

		alarm_msg  = "Please, check process recovery action.\n";
		alarm_msg += "If you select [RESTART],				the process will restart after system initialize.\n";
		alarm_msg += "If you select [ABORT],				the process will be aborted.\n";
		// alarm_msg += "If you select [CONTIUNE],				after current step time elapse, the next step will be executed.\n";
		alarm_msg += "If you select [JUMP],					the step that you select will be executed.\n";
		alarm_msg += "If you select [END],					Without Plasma Dechuck.. the process will be normally completed.\n";
		alarm_msg += "If you select [END_WITH_PLASMA_DECHUCK],       With Plasma Dechuck recipe will be executed.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RESTART);
		l_act.Add(ACT__ABORT);
		// l_act.Add(ACT__CONTINUE);
		l_act.Add(ACT__JUMP);
		l_act.Add(ACT__END);
		l_act.Add(ACT__END_WITH_PLASMA_DECHUCK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// Process Recovery Action ...
	{
		alarm_id = ALID__PROCESS_RECOVERY_CHECK_NO_WAFER;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Check Process Recovery Action !";

		alarm_msg  = "Please, check process recovery action.\n";
		alarm_msg += "If you select [RESTART],				the process will restart after system initialize.\n";
		alarm_msg += "If you select [ABORT],				the process will be aborted.\n";
		// alarm_msg += "If you select [CONTIUNE],				after current step time elapse, the next step will be executed.\n";
		alarm_msg += "If you select [JUMP],					the step that you select will be executed.\n";
		alarm_msg += "If you select [END],					Without Plasma Dechuck.. the process will be normally completed.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RESTART);
		l_act.Add(ACT__ABORT);
		// l_act.Add(ACT__CONTINUE);
		l_act.Add(ACT__JUMP);
		l_act.Add(ACT__END);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// Process Plasma Dechuck Recipe does not exist ...
	{
		alarm_id = ALID__PLSAMA_DECHUCK_RECIPE_NOT_EXIST;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Process [Plasma Dechuck] recipe does not exist.";

		alarm_msg = "Please, check [Plasma Dechuck] recipe file.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// Plasma.Dechuck Process Failed ...
	{
		CString str_temp;

		alarm_id = ALID__PLSAMA_DECHUCK_PROCESS_FAILED;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Process [Plasma Dechuck] Sequence Failed.";

		str_temp  = "You must execute plasma dechuck sequence \n\n";
		str_temp += "If you don't, Wafer may be broken in the chamber. \n";
		alarm_msg = str_temp;

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PROCESS_RECIPE_FILE_CHANGING_NOW;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Process recipe file is being changed, now. \n";

		alarm_msg  = "The process will run after recipe file save. \n";
		alarm_msg += "Please, wait or recipe file. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__WAFER_STATUS_CONVERT_TO_PROCESSED;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Do you want to convert the status of wafer ? \n";

		alarm_msg  = "If you click \"YES\", the status of wafer will be converted to \"PROCESSED\". \n";
		alarm_msg += "If you click \"NO\",  the status of wafer will be not changed. \n";

		l_act.RemoveAll();
		l_act.Add(STR__YES);
		l_act.Add(STR__NO);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__WAFER_ALREADY_PROCESSED;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Do you want to proceed the re-processing of wafer ?";

		alarm_msg  = "If you click \"YES\", the process will be proceeded. \n";
		alarm_msg += "If you click \"NO\",  the process will be aborted. \n";

		l_act.RemoveAll();
		l_act.Add(STR__YES);
		l_act.Add(STR__NO);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__RECIPE_STEP_SIZE_ERROR;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "The step size of process recipe is not correct !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PROCESS_NOT_READY;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Process를 진행할 상태가 아닙니다.";

		alarm_msg = "PM Slot은 Close 상태이어야 합니다. \n";
		alarm_msg = "Lift_Pin은 Down 상태이어야 합니다. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__PROC_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

	// OBJ.THIS ...
	{
		obj_name = sObject_Name;
		var_name = "CTRL";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__OBJ_CTRL, obj_name,var_name);
	}

	// OBJ : DB_INF .....
	{
		def_name = "OBJ__DB_INF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		// ...
		{
			var_name = "PMC.PROCESS.STATUS";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMC_PROCESS_STATUS, obj_name,var_name);

			//
			var_name = "SLOT01.RECIPE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RCP_NAME, obj_name,var_name);

			//
			var_name = "CHM.PRC.TOTAL.TIME.TO.CTC";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PRC_TOTAL_TIME_TO_CTC, obj_name,var_name);

			var_name = "CHM.PRC.CHANGE.TIME.TO.CTC";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PRC_CHANGE_TIME_TO_CTC, obj_name,var_name);

			//
			var_name = "SLOT01.STATUS";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SLOT01_STATUS, obj_name,var_name);

			var_name = "SLOT01.TITLE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT01_TITLE, obj_name,var_name);

			//
			var_name = "SLOT01.LOTID";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT01_LOTID, obj_name,var_name);

			var_name = "SLOT01.MATERIALID";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT01_MATERIALID, obj_name,var_name);

			// 
			var_name = "SLOT01.PORTID";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT01_PORTID, obj_name,var_name);

			var_name = "SLOT01.SLOTID";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT01_SLOTID, obj_name,var_name);

			//
			var_name = "CFG.DECHUCK.CTRL.MODE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_DECHUCK_CTRL_MODE, obj_name,var_name);

			var_name = "CFG.DECHUCK.RECIPE.ABORT";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CFG_DECHUCK_RECIPE_ABORT, obj_name,var_name);
		}
	}

	// OBJ : DB_SYS 
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		// ...
		{
			var_name = "MON.SYSTEM.PROCESS.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_SYSTEM_PROCESS_ACTIVE, obj_name,var_name);

			//
			var_name = "MON.INTERLOCK.HEAVY.ACTIVE.SYSTEM";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_SYSTEM, obj_name,var_name);

			var_name = "MON.INTERLOCK.LIGHT.ACTIVE.SYSTEM";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_INTERLOCK_LIGHT_ACTIVE_SYSTEM, obj_name,var_name);

			//
			var_name = "MON.INTERLOCK.HEAVY.ACTIVE.CHAMBER";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_CHAMBER, obj_name,var_name);

			var_name = "MON.INTERLOCK.LIGHT.ACTIVE.CHAMBER";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_INTERLOCK_LIGHT_ACTIVE_CHAMBER, obj_name,var_name);
		}
	}

	// OBJ : CHM ...
	{
		def_name = "OBJ__CHM";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__CHM = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	// OBJ : STEP ...
	{
		def_name = "OBJ__STEP";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__STEP = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		var_name = "MON.STEP.EXCEPTION.ACT";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MON_STEP_EXCEPTION_ACT, obj_name,var_name);

		//
		var_name = "RCP.STEP.MODE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RCP_STEP_MODE, obj_name,var_name);

		var_name = "RCP.STEP.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RCP_STEP_TIME, obj_name,var_name);

		//
		var_name = "INFO.STEP.CUR_NUM";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__INFO_STEP_CUR_NUM, obj_name,var_name);
	}

	// OBJ : DATALOG ...
	{
		def_name = "OBJ__PROC_LOG";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__PROC_LOG = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		// ...
		{
			var_name = "LOG.LOTID";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PROC_LOG__LOTID, obj_name,var_name);

			var_name = "LOG.RECIPEID";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PROC_LOG__RECIPEID, obj_name,var_name);

			var_name = "LOG.PORTID";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PROC_LOG__PORTID, obj_name,var_name);

			var_name = "LOG.SLOTID";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PROC_LOG__SLOTID, obj_name,var_name);

			//
			var_name = "sVAR.SUB_DIR";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PROC_LOG__SUB_DIR, obj_name,var_name);

			var_name = "sVAR.FILE_NAME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PROC_LOG__FILE_NAME, obj_name,var_name);
		}
	}

	// LINK CHANNEL ...
	{
		def_name = "CH__SYS_CTRL_LOCK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYS_CTRL_LOCK, obj_name,var_name);
	}

	// LEARNED.INFO ...
	{
		CString io_title;
		CString rcp_name;
		CString io_obj;
		CString io_var;

		def_name = "LEARNED_ITEM.SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		int i_limit = atoi(def_data);

		for(i=0; i<i_limit; i++)
		{
			int id = i + 1;

			def_name.Format("LEARNED_ITEM.TITLE.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			io_title = def_data;

			def_name.Format("LEARNED_ITEM.RCP_NAME.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			rcp_name = def_data;

			//
			def_name.Format("LEARNED_ITEM.IO_NAME.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, io_obj,io_var);

			mCTRL__LEARNED_ITEM.Load__IO_ITEM(p_ext_obj_create, io_title,rcp_name, io_obj,io_var);
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
		x_seq_info->Get__DIR_PROCESS(sDir_PROC);
	}

	// ...
	{
		iActive__PROC_START = -1;

		//
		bActive__PROC_LOG__STEP_START = false;

		//
		dCH__PARA_MANUAL_PROCESS_DECHUCK_ACTIVE->Set__DATA(STR__OFF);

		dCH__PARA_MANUAL_STEP_CTRL_ACTIVE->Set__DATA(STR__OFF);
		sCH__PARA_MANUAL_STEP_CTRL_REQ->Set__DATA("");
	}

	// Total Count ...
	if(sCH__MON_WAFER_INFO_TOTAL_COUNT_START_DATE->Check__DATA("") > 0)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		ch_data.Format("%00004d.%002d.%002d", st.wYear,st.wMonth,st.wDay);
		sCH__MON_WAFER_INFO_TOTAL_COUNT_START_DATE->Set__DATA(ch_data);
	}
	// Current Count ...
	if(sCH__MON_WAFER_INFO_CURRENT_COUNT_START_DATE->Check__DATA("") > 0)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		ch_data.Format("%00004d.%002d.%002d", st.wYear,st.wMonth,st.wDay);
		sCH__MON_WAFER_INFO_CURRENT_COUNT_START_DATE->Set__DATA(ch_data);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__PROC_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
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

		/*
		aCH__SVID_PROCESS_STATE->Set__DATA("0");

		sEXT_CH__MON_SYSTEM_PROCESS_ACTIVE->Set__DATA(STR__OFF);
		sEXT_CH__SYSTEM_PROCESS_STEP_ID->Set__DATA("");
		sEXT_CH__SYSTEM_PROCESS_LAST_STEP_FLAG->Set__DATA("");

		xCH__LAST_STEP_FLAG->Set__DATA("");
		*/
	}

	Fnc__PRC_LOG__DISABLE(p_variable);

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

int CObj__PROC_STD::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__EXCEPTION_ACT)				Mon__EXCEPTION_ACT(p_variable, p_alarm);

	return 1;
}
