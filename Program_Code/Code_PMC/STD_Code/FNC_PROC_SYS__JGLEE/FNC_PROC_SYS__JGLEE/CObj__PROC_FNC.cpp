#include "StdAfx.h"
#include "CObj__PROC_FNC.h"

#include "CObj__PROC_FNC__ALID.h"
#include "CObj__PROC_FNC__DEF.h"


//-------------------------------------------------------------------------
CObj__PROC_FNC::CObj__PROC_FNC()
{

}
CObj__PROC_FNC::~CObj__PROC_FNC()
{

}

//-------------------------------------------------------------------------
int CObj__PROC_FNC::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__PROC_READY, "PROC_READY");
		ADD__CTRL_VAR(sMODE__PROC_START, "PROC_START");

		ADD__CTRL_VAR(sMODE__CLN_READY,	"CLN_READY");
		ADD__CTRL_VAR(sMODE__CLN_START,	"CLN_START");

		ADD__CTRL_VAR(sMODE__MNT_READY,	"MNT_READY");
		ADD__CTRL_VAR(sMODE__MNT_START,	"MNT_START");

		ADD__CTRL_VAR(sMODE__JOB_STRT_READY, "JOB_START_READY");
		ADD__CTRL_VAR(sMODE__JOB_END_READY,	 "JOB_END_READY"  );
	}
	return 1;
}
int CObj__PROC_FNC::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define MON_ID__PROC_EXCEPTION_CTRL					1
#define MON_ID__SYSTEM_LOCK_CTRL					2


int CObj__PROC_FNC::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	//
	str_name.Format("OBJ.MSG");
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

	//
	str_name = "sPRC.TOTAL.TIME.TO.CTC";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(xCH__PRC_TOTAL_TIME_TO_CTC, str_name);
	
	str_name = "sPRC.CHANGE.TIME.TO.CTC";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(xCH__PRC_CHANGE_TIME_TO_CTC, str_name);

	//
	str_name = "sPRC.TOTAL.TIME";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(xCH__PRC_TOTAL_TIME, str_name);

	str_name = "sPRC.CUR.TIME";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(xCH__PRC_CUR_TIME, str_name);

	//
	str_name = "STEP.TOTAL.NUM";
	STD__ADD_ANALOG(str_name, "", 0, 0, 999);
	LINK__VAR_ANALOG_CTRL(xCH__STEP_TOTAL_NUM, str_name);

	str_name = "STEP.CUR.NUM";
	STD__ADD_ANALOG_WITH_OPTION(str_name, "", 0, -1, 999, -1, "L", "");
	LINK__VAR_ANALOG_CTRL(xCH__STEP_CUR_NUM, str_name);

	str_name = "LAST.STEP.FLAG";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(xCH__LAST_STEP_FLAG, str_name);

	//
	str_name = "LOOP.MSG";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(xCH__LOOP_MSG, str_name);

	//
	str_name = "PARA.PROCESS.TYPE";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__PARA_PROCESS_TYPE, str_name);

	//
	str_name = "SVID.PROCESS_STATE";
	STD__ADD_ANALOG(str_name,"state",0,0,1);
	LINK__VAR_ANALOG_CTRL(aCH__SVID_PROCESS_STATE, str_name);

	str_name = "SVID.CLEAN_COUNT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"count",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__SVID_CLEAN_COUNT, str_name);

	//
	str_name = "REPORT.TOTAL.ERROR.SEC";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__REPORT_TOTAL_ERROR_SEC, str_name);
	
	str_name = "REPORT.AVG.ERROR.SEC";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__REPORT_AVG_ERROR_SEC, str_name);

	//
	str_name = "dPRC.STS";
	STD__ADD_STRING(str_name,);
	LINK__VAR_STRING_CTRL(xCH__PRC_STS, str_name);

	str_name = "CHM.STATE";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(xCH__CHM_STATE, str_name);

	str_name = "RCP_FILE.UPLOAD_FLAG";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__RCP_FILE_UPLOAD_FLAG, str_name);
	
	//
	str_name = "ACT_RECOVERY.RESTART_FLAG";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__ACT_RECOVERY_RESTART_FLAG, str_name);

	//
	{
		str_name = "NEXT_STEP_CTRL.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__NEXT_STEP_CTRL_FLAG, str_name);
	
		str_name = "NEXT_STEP_CTRL.REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__NEXT_STEP_CTRL_REQ, str_name);
	}

	//
	{
		str_name = "PROCESS.STATUS.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PROCESS_STATUS_FLAG, str_name);
	}

	//
	{
		str_name = "PMC_RECV.APC.APPLY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_RECV_APC_APPLY, str_name);
		
		str_name = "PMC_RECV.APC.DATA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PMC_RECV_APC_DATA, str_name);
	}

	// ...
	{
		str_name = "ABORT.LOCK_FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LOCK_FLAG__ABORT, str_name);

		str_name = "END.LOCK_FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LOCK_FLAG__END, str_name);

		str_name = "SKIP.LOCK_FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LOCK_FLAG__SKIP, str_name);

		str_name = "JUMP.LOCK_FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LOCK_FLAG__JUMP, str_name);

		str_name = "PAUSE.LOCK_FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LOCK_FLAG__PAUSE, str_name);

		str_name = "RESUME.LOCK_FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LOCK_FLAG__RESUME, str_name);

		//
		str_name = "EXCEPTION.ACT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__EXCEPTION_ACT, str_name);

		str_name = "EXCEPTION.LAST.ACT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__EXCEPTION_LAST_ACT, str_name);

		str_name = "EXCEPTION.MSG";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__EXCEPTION_MSG, str_name);

		//
		str_name = "JUMP.STEP.ID";
		STD__ADD_ANALOG(str_name,"step",0,1,100);
		LINK__VAR_ANALOG_CTRL(aCH__JUMP_STEP_ID, str_name);

		str_name = "CONTINUE.OVER.STEP.TIME";
		STD__ADD_ANALOG(str_name,"sec",0,0,100);
		LINK__VAR_ANALOG_CTRL(aCH__CONTINUE_OVER_STEP_TIME, str_name);

		str_name = "WIN_CTRL.JUMP_PAGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WIN_CTRL_JUMP_PAGE, str_name);

		str_name = "WIN_CTRL.LOCK";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WIN_CTRL_LOCK, str_name);

		str_name = "WIN_CTRL.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WIN_CTRL_MSG, str_name);

		//
		str_name = "RCP.PROCESS.DATA.SUMMARY";
		STD__ADD_DIGITAL(str_name, "Enable Disable");
		LINK__VAR_DIGITAL_CTRL(dRCP_CH__PROCESS_DATA_SUMMARY, str_name);

		//
		str_name = "sPRC.REAL.CHART.START";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PRC_REAL_CHART_START, str_name);

		//
		str_name = "sCFG.PLASMA.DECHUCK.RECIPE.NAME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__CFG_PLASMA_DECHUCK_RCP_NAME, str_name);

		//
		str_name = "dDATALOG.GATHERING";
		STD__ADD_DIGITAL(str_name, "DISABLE ENABLE");
		LINK__VAR_DIGITAL_CTRL(dCH__DATALOG_GATHERING_ENABLE_DISABLE, str_name);
	}

	// ...
	{
		str_name = "WAFER_STATUS_CONVERTED_TO_PROCESSED.BY.PMC_REQ_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WAFER_STATUS_CONVERTED_TO_PROCESSED_BY_PMC_REQ_COUNT, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3, MON_ID__PROC_EXCEPTION_CTRL);
		p_variable->Add__MONITORING_PROC(1, MON_ID__SYSTEM_LOCK_CTRL);
	}
	return 1;
}
int CObj__PROC_FNC::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	int alarm_id;
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;


	// Process Recipe does not exist ...
	{
		alarm_id = ALID__PROCESS_RECIPE_NOT_EXIST;

		alarm_title  = title;
		alarm_title += "Process recipe does not exist.";

		alarm_msg = "Please, check process recipe file.\n";

		l_act.RemoveAll();
		l_act.Add("ABORT");
		l_act.Add("RETRY");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// Process Recovery Action ...
	{
		alarm_id = ALID__PROCESS_RECOVERY_CHECK;

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

	// Process Plasma Dechuck Recipe does not exist ...
	{
		alarm_id = ALID__PLSAMA_DECHUCK_RECIPE_NOT_EXIST;

		alarm_title  = title;
		alarm_title += "Process [Plasma Dechuck] recipe does not exist.";

		alarm_msg = "Please, check [Plasma Dechuck] recipe file.\n";

		l_act.RemoveAll();
		l_act.Add(STR__RETRY);
		l_act.Add(STR__ABORT);
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// Plasma.Dechuck Process Failed ...
	{
		CString str_temp;

		alarm_id = ALID__PLSAMA_DECHUCK_PROCESS_FAILED;

		alarm_title  = title;
		alarm_title += "Process [Plasma Dechuck] Sequence Failed.";

		str_temp  = "You must execute plasma dechuck sequence \n\n";
		str_temp += "If you don't, Wafer may be broken in the chamber. \n";
		alarm_msg = str_temp;

		l_act.RemoveAll();
		l_act.Add("CLEAR");
			
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
		l_act.Add("CLEAR");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__WAFER_STATUS_CONVERT_TO_PROCESSED;

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
		
		alarm_title  = title;
		alarm_title += "The step size of process recipe is not correct !";

		alarm_msg = "";
		
		l_act.RemoveAll();
		l_act.Add(STR__RETRY);
		l_act.Add(STR__ABORT);
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PROCESS_NOT_READY;

		alarm_title  = title;
		alarm_title += "Process를 진행할 상태가 아닙니다.";

		alarm_msg = "Shutter는 Close 상태이어야 합니다. \n";
		alarm_msg = "Lift_Pin은 Dwon 상태이어야 합니다. \n";

		l_act.RemoveAll();
		l_act.Add(STR__RETRY);
		l_act.Add(STR__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__PROC_FNC::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);

	// LOG INFO .....
	{
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__LOG_ENABLE,  "MODE__LOG_ENABLE", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__LOG_DISABLE, "MODE__LOG_DISABLE","");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__LOG_PAUSE,  "MODE__LOG_PAUSE", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__LOG_RESUME, "MODE__LOG_RESUME","");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__LOG_STEP_END_START, "MODE__LOG_STEP_END_START","");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__LOG_STEP_START, "MODE__LOG_STEP_START","");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__LOG_STEP_END,   "MODE__LOG_STEP_END",  "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__LOG_STEP_ABORT, "MODE__LOG_STEP_ABORT",""); 
	}

	// STEP INFO .....
	{
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__STEP_READY, "MODE__STEP_READY", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__STEP_START, "MODE__STEP_START", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__STEP_PROC,  "MODE__STEP_PROC",  "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__STEP_ABORT, "MODE__STEP_ABORT", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__STEP_END,   "MODE__STEP_END",   "");
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__PROC_FNC::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString str_name;
	CString def_name;
	CString def_data;
	CString obj_name;
	CString var_name;
	CString ch_name;

	//.....
	{
		CString file_name;
		CString log_msg;
		
		file_name.Format("%s.log", sObject_Name);
		
		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";
		
		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name, 24*5, 60);
		
		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);
		
		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	/*
	// DCOP
	{
		xDCOP_CTRL->Create__PROCESS_DB("");
		xDCOP_CTRL->Link__PROCESS_DB("");
	}
	*/

	// OBJ INF .....
	{
		def_name = "DB__INF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		// ...
		{
			str_name = "SLOT01.RECIPE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RCP_NAME, obj_name,str_name);

			//
			str_name = "CHM.PRC.TOTAL.TIME.TO.CTC";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PRC_TOTAL_TIME_TO_CTC, obj_name,str_name);

			str_name = "CHM.PRC.CHANGE.TIME.TO.CTC";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PRC_CHANGE_TIME_TO_CTC, obj_name,str_name);

			//
			str_name = "SLOT01.STATUS";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SLOT01_STATUS, obj_name,str_name);

			str_name = "SLOT01.TITLE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT01_TITLE, obj_name,str_name);

			//
			str_name = "SLOT01.LOTID";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT01_LOTID, obj_name,str_name);

			str_name = "SLOT01.MATERIALID";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT01_MATERIALID, obj_name,str_name);

			// 
			str_name = "SLOT01.PORTID";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT01_PORTID, obj_name,str_name);

			str_name = "SLOT01.SLOTID";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT01_SLOTID, obj_name,str_name);

			//
			str_name = "CFG.DECHUCK.CTRL.MODE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_DECHUCK_CTRL_MODE, obj_name,str_name);

			str_name = "CFG.DECHUCK.RECIPE.ABORT";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CFG_DECHUCK_RECIPE_ABORT, obj_name,str_name);
		}
	}

	// DB SYS .....
	{
		def_name = "DB__SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		str_name = "MON.SYSTEM.PROCESS.ACTIVE";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MON_SYSTEM_PROCESS_ACTIVE, obj_name,str_name);

		//
		str_name = "SYSTEM.PROCESS.STEP.ID";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_PROCESS_STEP_ID, obj_name,str_name);

		str_name = "SYSTEM.PROCESS.LAST.STEP.FLAG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_PROCESS_LAST_STEP_FLAG, obj_name,str_name);
	}

	// Channel Link : OPR_OBJ ...
	{
		def_name = "CH__SYSTEM_OBJ_STATUS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SYSTEM_OBJ_STATUS, obj_name,var_name);
	}

	// OBJ : CHM
	{
		def_name = "OBJ__CHM";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__CHM = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	// ...
	{
		xCH__CHM_STATE->Set__DATA(STR__Idle);
	}

	// Channel Link .....
	{
		//
		{
			obj_name = "FNC_PM_DATALOG";

			//
			var_name = "LOG.LOTID";
			LINK__EXT_VAR_STRING_CTRL(xEXT_CH__LOG_LOTID, obj_name,var_name);
			
			var_name = "LOG.RECIPEID";
			LINK__EXT_VAR_STRING_CTRL(xEXT_CH__LOG_RECIPEID, obj_name,var_name);
			
			var_name = "LOG.PORTID";
			LINK__EXT_VAR_STRING_CTRL(xEXT_CH__LOG_PORTID, obj_name,var_name);
			
			var_name = "LOG.SLOTID";
			LINK__EXT_VAR_STRING_CTRL(xEXT_CH__LOG_SLOTID, obj_name,var_name);

			//
			var_name = "sVAR.SUB_DIR";
			LINK__EXT_VAR_STRING_CTRL(xEXT_CH__LOG_SUB_DIR, obj_name,var_name);

			var_name = "sVAR.FILE_NAME";
			LINK__EXT_VAR_STRING_CTRL(xEXT_CH__LOG_FILE_NAME, obj_name,var_name);
		}

		// 
		{
			obj_name = "FNC_STEP";

			//
			pOBJ__STEP_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			// ...
			{
				var_name = "CUR.PROC.TYPE";
				LINK__EXT_VAR_STRING_CTRL(xEXT_CH__CUR_PROC_TYPE, obj_name,var_name);

				var_name = "RCP.FILE.PATH";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RCP_FILE_PATH, obj_name,var_name);
			}

			// ...
			{
				var_name = "RCP.LOOP_START";
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RCP__LOOP_START, obj_name,var_name);
				
				var_name = "RCP.LOOP_REPEAT";
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RCP__LOOP_REPEAT, obj_name,var_name);
			}

			// ...
			{
				var_name = "EXCEPTION_CONTINUE.REQ";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EXCEPTION_CONTINUE_REQ, obj_name,var_name);
				
				var_name = "EXCEPTION_CONTINUE.STEP_OVER_TIME";
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EXCEPTION_CONTINUE_STEP_OVER_TIME, obj_name,var_name);
			}
		}

		//
		{
			def_name = "CH__STEP_TIME";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__STEP_TIME, obj_name,var_name);
		}

		//
		{
			def_name = "CH__STEP_EXCEPTION_COMMAND";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__STEP_EXCEPTION_COMMAND, obj_name,var_name);
		}

		//
		{
			def_name = "CH__STEP_STABLE_REQ";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__STEP_STABLE_REQ, obj_name,var_name);
		}

		//
		{
			def_name = "CH__SYS_CTRL_LOCK";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYS_CTRL_LOCK, obj_name,var_name);
		}

		//
		{
			def_name = "CH__SYS_FNC_LOCK";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYS_FNC_LOCK, obj_name,var_name);
		}

		//
		{
			def_name = "CH__SYS_STATUS";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SYS_STATUS, obj_name,var_name);
		}

		//
		{
			// ....
			def_name = "CH__SLOT_TITLE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT_TITLE, obj_name,var_name);

			// ....
			def_name = "CH__SLOT_LOTID";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SLOT_LOTID, obj_name,var_name);
		}
	}

	// INTERLOCK CHANNEL ...
	{
		def_name = "CH__SHUTTER_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SHUTTER_STATE, obj_name,var_name);

		def_name = "CH__LIFT_PIN_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LIFT_PIN_STATE, obj_name,var_name);

		def_name = "CH__CHUCK_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHUCK_STATE, obj_name,var_name);
	}

	// ...
	{
		sCH__NEXT_STEP_CTRL_REQ->Set__DATA(STR__LOCK);

		xTIMER_ASYNC->REGISTER__COUNT_CHANNEL(sObject_Name,xCH__PRC_CUR_TIME->Get__VARIABLE_NAME());

		iPROC_START_FLAG = -1;
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();

		x_seq_info->Get__DIR_PROCESS(sDIR_PROC);
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__PROC_FNC::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = 1;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		// xCMMD_LOG_CTRL->Write__LOG(log_msg);

		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	// ...
	{
		sEXT_CH__STEP_STABLE_REQ->Set__DATA("");
		sCH__PROCESS_STATUS_FLAG->Set__DATA("");
		// sEXT_CH__LEARNED_RESULT->Set__DATA("");

		// iFLAG__HE_DECHUCK = -1;
	}


	if((mode.CompareNoCase(sMODE__PROC_READY) == 0)
    || (mode.CompareNoCase(sMODE__PROC_START) == 0)
	|| (mode.CompareNoCase(sMODE__CLN_READY)  == 0)
	|| (mode.CompareNoCase(sMODE__CLN_START)  == 0)
	|| (mode.CompareNoCase(sMODE__MNT_READY)  == 0)
	|| (mode.CompareNoCase(sMODE__MNT_START)  == 0))
	{
LOOP_RETRY:

		// ...
		{
			sCH__NEXT_STEP_CTRL_FLAG->Set__DATA("");
			sCH__NEXT_STEP_CTRL_REQ->Set__DATA(STR__LOCK);
		}

		// ...
		{
			xLOG_CTRL->WRITE__LOG("SHUTTER : Close Check Start ...");

			int loop_count = 0;
			CString ch_data;

			while(1)
			{
				if(sEXT_CH__SHUTTER_STATE->Check__DATA("CLOSE") > 0)
				{
					break;
				}

				Sleep(500);

				loop_count++;
				if(loop_count < 20)
				{
					continue;
				}

				// ...
				{
					int alm_id = ALID__PROCESS_NOT_READY;
					CString alm_msg;
					CString r_act;

					alm_msg.Format(" * %s <- %s \n", 
								   sEXT_CH__SHUTTER_STATE->Get__CHANNEL_NAME(),
								   sEXT_CH__SHUTTER_STATE->Get__STRING());

					p_alarm->Popup__ALARM_With_MESSAGE(alm_id,alm_msg,r_act);

					if(r_act.CompareNoCase("RETRY") == 0)
					{
						goto LOOP_RETRY;
					}
					else
					{
						flag = -1;
					}
				}
				break;
			}

			xLOG_CTRL->WRITE__LOG("SHUTTER : Close Check End ...");
		}

		// ...
		{
			xLOG_CTRL->WRITE__LOG("LIFT_PIN : Down Check Start ...");

			int loop_count = 0;
			CString ch_data;

			while(1)
			{
				ch_data = sEXT_CH__LIFT_PIN_STATE->Get__STRING();
				if((ch_data.CompareNoCase("DOWN") == 0)
				|| (ch_data.CompareNoCase("PROC.DOWN") == 0))
				{
					break;
				}

				Sleep(500);

				loop_count++;
				if(loop_count < 20)
				{
					continue;
				}

				// ...
				{
					int alm_id = ALID__PROCESS_NOT_READY;
					CString alm_msg;
					CString r_act;

					alm_msg.Format(" * %s <- %s \n", 
									sEXT_CH__LIFT_PIN_STATE->Get__CHANNEL_NAME(),
									sEXT_CH__LIFT_PIN_STATE->Get__STRING());

					p_alarm->Popup__ALARM_With_MESSAGE(alm_id,alm_msg,r_act);

					if(r_act.CompareNoCase("RETRY") == 0)
					{
						goto LOOP_RETRY;
					}
					else
					{
						flag = -1;
					}			
				}
				break;
			}

			xLOG_CTRL->WRITE__LOG("LIFT_PIN : Down Check End ...");
		}
	}

	if((mode.CompareNoCase(sMODE__PROC_START) == 0)
	|| (mode.CompareNoCase(sMODE__CLN_START)  == 0)
	|| (mode.CompareNoCase(sMODE__MNT_START)  == 0))
	{
		iPROC_START_FLAG = 1;

		// ...
		{
			aCH__SVID_PROCESS_STATE->Set__DATA("1");
			sCH__PRC_REAL_CHART_START->Set__DATA("START");		// Real Chart Start
		}

		if(mode.CompareNoCase(sMODE__PROC_START) == 0)
		{
			aCH__SVID_CLEAN_COUNT->Set__VALUE(0);
		}
		else if(mode.CompareNoCase(sMODE__CLN_START) == 0)
		{
			aCH__SVID_CLEAN_COUNT->Inc__VALUE(1);
		}
	}
	else if((mode.CompareNoCase(sMODE__PROC_READY) == 0)
		 || (mode.CompareNoCase(sMODE__CLN_READY)  == 0)
		 || (mode.CompareNoCase(sMODE__MNT_READY)  == 0))
	{
		iPROC_START_FLAG = 1;
	}


	if(flag > 0)
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__PROC_READY)
		{
			xEXT_CH__CUR_PROC_TYPE->Set__DATA(STR__PRC);

			flag = Call__PROC_READY(p_variable,p_alarm);

			xEXT_CH__CUR_PROC_TYPE->Set__DATA("");
		}
		ELSE_IF__CTRL_MODE(sMODE__PROC_START)
		{
			xEXT_CH__CUR_PROC_TYPE->Set__DATA(STR__PRC);

			flag = Call__PROC_START(p_variable,p_alarm);

			xEXT_CH__CUR_PROC_TYPE->Set__DATA("");
		}
		
		ELSE_IF__CTRL_MODE(sMODE__CLN_READY)
		{
			xEXT_CH__CUR_PROC_TYPE->Set__DATA(STR__CLN);

			flag = Call__CLN_READY(p_variable,p_alarm);

			xEXT_CH__CUR_PROC_TYPE->Set__DATA("");
		}
		ELSE_IF__CTRL_MODE(sMODE__CLN_START)
		{
			xEXT_CH__CUR_PROC_TYPE->Set__DATA(STR__CLN);

			flag = Call__CLN_START(p_variable,p_alarm);

			xEXT_CH__CUR_PROC_TYPE->Set__DATA("");
		}

		ELSE_IF__CTRL_MODE(sMODE__MNT_READY)
		{
			int change_flag = -1;
			
			if(sEXT_CH__SYS_CTRL_LOCK->Check__DATA("") > 0)
			{
				change_flag = 1;
				
				if(sCH__PARA_PROCESS_TYPE->Check__DATA("DECHUCK") > 0)		sEXT_CH__SYS_CTRL_LOCK->Set__DATA("DECHUCK.PROC");
				else														sEXT_CH__SYS_CTRL_LOCK->Set__DATA("MAINT.PROC");
			}

			// ...
			{
				flag = Call__MNT_READY(p_variable,p_alarm);
			}

			if(change_flag > 0)
			{
				sEXT_CH__SYS_CTRL_LOCK->Set__DATA("");
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__MNT_START)
		{
			int change_flag = -1;
			int flag = 1;

			if(sEXT_CH__SYS_CTRL_LOCK->Check__DATA("") > 0)
			{
				change_flag = 1;

				if(sCH__PARA_PROCESS_TYPE->Check__DATA("DECHUCK") > 0)		sEXT_CH__SYS_CTRL_LOCK->Set__DATA("DECHUCK.PROC");
				else														sEXT_CH__SYS_CTRL_LOCK->Set__DATA("MAINT.PROC");
			}

			if(dEXT_CH__SYSTEM_OBJ_STATUS->Check__DATA(STR__MAINTMODE) > 0)
			{
				CString cur_sts;
				dEXT_CH__SLOT01_STATUS->Get__DATA(cur_sts);
				
				if(cur_sts.CompareNoCase(STR__PROCESSED) == 0)
				{
					// Yes ? or No ? 
					{
						int alarm_id = ALID__WAFER_ALREADY_PROCESSED;
						CString alm_msg;
						CString alm_bff;
						CString r_act;
						CString var_data;
						
						// ...
						{
							sEXT_CH__SLOT01_LOTID->Get__DATA(var_data);
							alm_bff.Format("The lot ID of wafer is \"%s\". \n", var_data);
							alm_msg += alm_bff;
							
							sEXT_CH__SLOT01_PORTID->Get__DATA(var_data);
							alm_bff.Format("The port ID of wafer is \"%s\". \n", var_data);
							alm_msg += alm_bff;
							
							sEXT_CH__SLOT01_SLOTID->Get__DATA(var_data);
							alm_bff.Format("The slot ID of wafer is \"%s\". \n", var_data);
							alm_msg += alm_bff;
							
							sEXT_CH__RCP_NAME->Get__DATA(var_data);
							alm_bff.Format("The recipe name of wafer is \"%s\". \n", var_data);
							alm_msg += alm_bff;
						}
						
						p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alm_msg,r_act);
						if(r_act.CompareNoCase(STR__YES) != 0)
						{
							flag = -1;
						}
					}
				}
			}

			if(flag > 0)
			{
				flag = Call__MNT_START(p_variable,p_alarm);
			}

			if(change_flag > 0)
			{
				sEXT_CH__SYS_CTRL_LOCK->Set__DATA("");
			}

			if(flag > 0)
			{
				if(dEXT_CH__SYSTEM_OBJ_STATUS->Check__DATA(STR__MAINTMODE) > 0)
				{
					CString cur_sts;
					dEXT_CH__SLOT01_STATUS->Get__DATA(cur_sts);
					
					if((cur_sts.CompareNoCase(STR__UNKNOWN) == 0)
					|| (cur_sts.CompareNoCase(STR__EXIST)   == 0)
					|| (cur_sts.CompareNoCase(STR__PROCESSING) == 0)
					|| (cur_sts.CompareNoCase(STR__ABORTED) == 0)
					|| (cur_sts.CompareNoCase(STR__MAPPED)  == 0))
					{
						// Yes ? or No ? 
						{
							int alarm_id = ALID__WAFER_STATUS_CONVERT_TO_PROCESSED;
							CString alm_msg;
							CString alm_bff;
							CString r_act;
							CString var_data;
							
							// ...
							{
								sEXT_CH__SLOT01_LOTID->Get__DATA(var_data);
								alm_bff.Format("The lot ID of wafer is \"%s\". \n", var_data);
								alm_msg += alm_bff;
								
								sEXT_CH__SLOT01_PORTID->Get__DATA(var_data);
								alm_bff.Format("The port ID of wafer is \"%s\". \n", var_data);
								alm_msg += alm_bff;
								
								sEXT_CH__SLOT01_SLOTID->Get__DATA(var_data);
								alm_bff.Format("The slot ID of wafer is \"%s\". \n", var_data);
								alm_msg += alm_bff;
								
								sEXT_CH__RCP_NAME->Get__DATA(var_data);
								alm_bff.Format("The recipe name of wafer is \"%s\". \n", var_data);
								alm_msg += alm_bff;
							}
							
							p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alm_msg,r_act);
							if(r_act.CompareNoCase(STR__YES) == 0)
							{
								int cur_count;
								
								sCH__WAFER_STATUS_CONVERTED_TO_PROCESSED_BY_PMC_REQ_COUNT->Get__DATA(var_data);
								cur_count = atoi(var_data) + 1;
								var_data.Format("%1d.REQ", cur_count);								
								sCH__WAFER_STATUS_CONVERTED_TO_PROCESSED_BY_PMC_REQ_COUNT->Set__DATA(var_data);
							}
						}
					}
				}
			}

			// ...
			{
				sCH__NEXT_STEP_CTRL_FLAG->Set__DATA("");
				sCH__NEXT_STEP_CTRL_REQ->Set__DATA(STR__LOCK);
			}
		}
		
		ELSE_IF__CTRL_MODE(sMODE__JOB_STRT_READY)		flag = Call__JOB_START_READY(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__JOB_END_READY)		flag = Call__JOB_END_READY(p_variable,p_alarm);

		else
		{
			flag = -1;
		}
	}


	if(flag < 0)
	{
		if(dEXT_CH__SLOT01_STATUS->Check__DATA(STR__NONE) < 0)
		{
			// iFLAG__HE_DECHUCK = 1;
		}
	}

	// ...
	{
		iPROC_START_FLAG = -1;

		aCH__SVID_PROCESS_STATE->Set__DATA("0");
		sCH__PRC_REAL_CHART_START->Set__DATA("STOP");		// Real Chart Stop
	
		sEXT_CH__MON_SYSTEM_PROCESS_ACTIVE->Set__DATA(STR__OFF);
		sEXT_CH__SYSTEM_PROCESS_STEP_ID->Set__DATA("");
		sEXT_CH__SYSTEM_PROCESS_LAST_STEP_FLAG->Set__DATA("");

		xCH__LAST_STEP_FLAG->Set__DATA("");
	}

	Fnc__PRC_LOG__DISABLE(p_variable);

	// ...
	{
		sEXT_CH__STEP_STABLE_REQ->Set__DATA("");
	}


	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		xCH__PRC_STS->Set__DATA("IDLE");

		// ...
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);
		
		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	
	return flag;
}

int CObj__PROC_FNC::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__PROC_EXCEPTION_CTRL:
			Mon__PROC_EXCEPTION_CTRL(id, p_variable,p_alarm);
			break;

		case MON_ID__SYSTEM_LOCK_CTRL:
			Mon__SYSTEM_LOCK_CTRL(id, p_variable,p_alarm);
			break;
	}

	return 1;
}
