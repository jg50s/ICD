#include "StdAfx.h"
#include "CObj__PMC_OPR.h"

#include "CObj__PMC_OPR__ALID.h"
#include "CObj__PMC_OPR__DEF.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__PMC_OPR::CObj__PMC_OPR()
{

}
CObj__PMC_OPR::~CObj__PMC_OPR()
{

}

//-------------------------------------------------------------------------
int CObj__PMC_OPR::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,				"SYSTEM_INIT");
		ADD__CTRL_VAR(sMODE__TRANSFER_INIT,		"TRANSFER_INIT");

		ADD__CTRL_VAR(sMODE__MAINT,				"SYSTEM_MAINT");
		ADD__CTRL_VAR(sMODE__SETUP,				"SYSTEM_SETUP");

		ADD__CTRL_VAR(sMODE__PUMP,				"PUMP");
		ADD__CTRL_VAR(sMODE__VENT,				"VENT");
		ADD__CTRL_VAR(sMODE__LEAK_CHECK,		"LEAK_CHECK");
		ADD__CTRL_VAR(sMODE__AUTO_PM,		    "AUTO_PM");
		ADD__CTRL_VAR(sMODE__PURGE,				"PURGE");

		ADD__CTRL_VAR(sMODE__PICK_READY,		"PICK_READY");
		ADD__CTRL_VAR(sMODE__PICK_X_READY,		"PICK_X_READY");
		ADD__CTRL_VAR(sMODE__PICK_COMPLETE,		"PICK_COMPLETE");
		ADD__CTRL_VAR(sMODE__PICK_X_COMPLETE,	"PICK_X_COMPLETE");
		ADD__CTRL_VAR(sMODE__PLACE_READY,		"PLACE_READY");
		ADD__CTRL_VAR(sMODE__PLACE_X_READY,		"PLACE_X_READY");
		ADD__CTRL_VAR(sMODE__PLACE_COMPLETE,	"PLACE_COMPLETE");
		ADD__CTRL_VAR(sMODE__PLACE_X_COMPLETE,	"PLACE_X_COMPLETE");
		ADD__CTRL_VAR(sMODE__PRO_READY,			"PRO_READY");
		ADD__CTRL_VAR(sMODE__PRO_START,			"PRO_START");
		ADD__CTRL_VAR(sMODE__CLN_READY,			"CLN_READY");
		ADD__CTRL_VAR(sMODE__CLN_START,			"CLN_START");
		ADD__CTRL_VAR(sMODE__MNT_READY,			"MNT_READY");
		ADD__CTRL_VAR(sMODE__MNT_START,			"MNT_START");

		ADD__CTRL_VAR(sMODE__JOB_START_READY,	"JOB_START_READY");
		ADD__CTRL_VAR(sMODE__JOB_END_READY,		"JOB_END_READY");
	}
	return 1;
}
int CObj__PMC_OPR::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATUS							1

#define APP_DSP__DISABLE_ENABLE					\
"DISABLE ENABLE"


int CObj__PMC_OPR::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString dsp_list;
	p_variable->Get__STD_DESCRIPTION("STD_OBJ_STATUS",dsp_list);

	// ...
	{
		str_name = "OBJ.STATUS";
		STD__ADD_DIGITAL(str_name,dsp_list);
		LINK__VAR_DIGITAL_CTRL(xCH__OBJ_STATUS, str_name);

		str_name = "OBJ.STATUS.VIRTUAL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS_VIRTUAL, str_name);

		//
		str_name = "PARA.PROCESS.TIME.SEC";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_PROCESS_TIME_SEC, str_name);

		str_name = "APP.PROCESS.TIME.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__APP_PROCESS_TIME_COUNT, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATUS);
	}
	return 1;
}
int CObj__PMC_OPR::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	int alarm_id;
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// ...
	{
		alarm_id = ALID__NOT_PROCESSED_WAFER_IN_PMC;

		alarm_title  = title;
		alarm_title += "In PMC, there is a wafer that not processed.";

		alarm_msg  = "If you click \"IGNORE\", the status of system will be converted to \"STANDBY\". \n";
		alarm_msg += "If you click \"ABORT\",  the status of system will be not initialized. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	return 1;
}

int CObj__PMC_OPR::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	// ...
	{
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__INIT,			"OBJ_MODE__INIT",  "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__MAINT,		"OBJ_MODE__MAINT", "");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PUMP,			"OBJ_MODE__PUMP",  "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__VENT,			"OBJ_MODE__VENT",  "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__LEAK_CHECK,	"OBJ_MODE__LEAK_CHECK", "");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PURGE,		"OBJ_MODE__PURGE", "");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PRO_READY,	"OBJ_MODE__PRO_READY", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PRO_START,	"OBJ_MODE__PRO_START", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__CLN_READY,	"OBJ_MODE__CLN_READY", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__CLN_START,	"OBJ_MODE__CLN_START", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__MNT_READY,	"OBJ_MODE__MNT_READY", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__MNT_START,	"OBJ_MODE__MNT_START", "");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__JOB_START_READY, "OBJ_MODE__JOB_START_READY", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__JOB_END_READY,   "OBJ_MODE__JOB_END_READY",   "");
	}
	return 1;
}


//-------------------------------------------------------------------------
int CObj__PMC_OPR::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString obj_name;
	CString var_name;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name = sObject_Name+".log";

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name, 24*5, 60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CCommon_Utility x_utility;
	bool def_check;

	// OBJ DB_INF ...
	{
		def_name = "OBJ__DB_INF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		// ...
		{
			var_name = "CFG.TRANSFER.MODE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_TRANSFER_MODE, def_data,var_name);
		}

		// ...
		{
			var_name = "SLOT01.STATUS";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__WAFER_STATUS, def_data,var_name);

			var_name = "SLOT01.RECIPE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RECIPE_NAME, def_data,var_name);

			//
			var_name = "CHM.STATE.REPORT_TO_CTC";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_STAGE_REPORT_TO_CTC, def_data,var_name);

			//
			var_name = "CHM.PRESSURE.VALUE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PRESSURE_VALUE, def_data,var_name);
		}

		// ...
		{
			var_name = "SHUTTER.STATUS";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SHUTTER_STATUS, def_data,var_name);

			var_name = "LIFT_PIN.STATUS";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LIFT_PIN_STATUS, def_data,var_name);

			//
			var_name = "CHM.VAC.SNS";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_VAC_SNS, def_data,var_name);

			var_name = "CHM.ATM.SNS";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_ATM_SNS, def_data,var_name);

			//
			var_name = "CHM.PRC.STS";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CHM_PRC_STS, def_data,var_name);

			var_name = "CHM.PRC.TOTAL.TIME.TO.CTC";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PRC_TOTAL_TIME_TO_CTC, def_data,var_name);

			var_name = "CHM.PRC.CHANGE.TIME.TO.CTC";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PRC_CHANGE_TIME_TO_CTC, def_data,var_name);
		}
	}

	// OBJ DB_SYS ...
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		// ...
		{
			var_name = "SYSTEM.MSG";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_MSG, obj_name,var_name);

			var_name = "FUNCTION.MSG";		
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__FNC_MSG, obj_name,var_name);
		}

		// ...
		{
			var_name = "SYSTEM.SETUP.REQ";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_SETUP_REQ, obj_name,var_name);
		}
	}

	// OBJ.AUTO_PM ...
	{
		def_name = "OBJ__AUTO_PM";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__AUTO_PM = def_check;

		if(def_check)
		{
			pOBJ_CTRL__AUTO_PM = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			def_name = "AUTO_PM.INIT";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sLINK_MODE__AUTO_PM = def_data;
		}
	}

	// OBJ.LIFT_PIN ...
	{
		def_name = "OBJ__LIFT_PIN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__LIFT_PIN = def_check;

		if(def_check)
		{
			pOBJ_CTRL__LIFT_PIN = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			def_name = "LIFT_PIN.TRANSFER_READY";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sLINK_MODE__LIFT_PIN__TRANSFER_READY = def_data;

			def_name = "LIFT_PIN.TRANSFER_COMPLETE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sLINK_MODE__LIFT_PIN__TRANSFER_COMPLETE = def_data;

			def_name = "LIFT_PIN.PROCESS_READY";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sLINK_MODE__LIFT_PIN__PROCESS_READY;
		}
	}

	// OBJ.SHUTTER ...
	{
		def_name = "OBJ__SHUTTER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__SHUTTER = def_check;

		if(def_check)
		{
			pOBJ_CTRL__SHUTTER = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			def_name = "SHUTTER.CLOSE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sLINK_MODE__SHUTTER__CLOSE = def_data;

			def_name = "SHUTTER.OPEN";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sLINK_MODE__SHUTTER__OPEN = def_data;
		}
	}

	// OBJ.PM_SLOT ...
	{
		def_name = "OBJ__PM_SLOT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__PM_SLOT = def_check;

		if(def_check)
		{
			pOBJ_CTRL__PM_SLOT = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			def_name = "PM_SLOT.CLOSE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sLINK_MODE__PM_SLOT__CLOSE = def_data;
			
			def_name = "PM_SLOT.OPEN";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sLINK_MODE__PM_SLOT__OPEN = def_data;
		}
	}

	// ...
	{
		sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__Idle);
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		if(x_seq_info->Is__SIMULATION_MODE() > 0)			iSIM_FLAG =  1;
		else												iSIM_FLAG = -1;
	}

	if(iSIM_FLAG > 0)
	{
		dEXT_CH__CFG_TRANSFER_MODE->Set__DATA("VAC");
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__PMC_OPR::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	// ...
	{
		CString log_msg;

		log_msg.Format("Start ... :  [%s]", mode);
		xLOG_CTRL->WRITE__LOG(log_msg);

		sEXT_CH__SYSTEM_MSG->Set__DATA(log_msg);
		sEXT_CH__FNC_MSG->Set__DATA("");
	}

	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__Initializing);

			flag = Call__INIT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__TRANSFER_INIT)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__Initializing);

			flag = Call__TRANSFER_INIT(p_variable);
		}

		ELSE_IF__CTRL_MODE(sMODE__MAINT)
		{
			flag = Call__MAINT(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__SETUP)
		{
			flag = Call__SETUP(p_variable, p_alarm);
		}

		ELSE_IF__CTRL_MODE(sMODE__PUMP)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__Pumping);

			flag = Call__PUMP(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__VENT)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__Venting);

			flag = Call__VENT(p_variable);
		}

		ELSE_IF__CTRL_MODE(sMODE__LEAK_CHECK)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__LeakChecking);

			flag = Call__LEAK_CHECK(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__AUTO_PM)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__AutoPM);

			flag = Call__AUTO_PM(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__PURGE)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__Purging);

			flag = Call__PURGE(p_variable);
		}

		ELSE_IF__CTRL_MODE(sMODE__PICK_READY)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__SendingMaterial);

			flag = Call__PICK_READY(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__PICK_X_READY)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__SendingMaterial);

			flag = Call__PICK_X_READY(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__PICK_COMPLETE)
		{
			flag = Call__PICK_COMPLETE(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__PICK_X_COMPLETE)
		{
			flag = Call__PICK_X_COMPLETE(p_variable);
		}

		ELSE_IF__CTRL_MODE(sMODE__PLACE_READY)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__ReceivingMaterial);

			flag = Call__PLACE_READY(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__PLACE_X_READY)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__ReceivingMaterial);

			flag = Call__PLACE_X_READY(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__PLACE_COMPLETE)
		{
			flag = Call__PLACE_COMPLETE(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__PLACE_X_COMPLETE)
		{
			flag = Call__PLACE_X_COMPLETE(p_variable);
		}

		ELSE_IF__CTRL_MODE(sMODE__PRO_READY)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__PreparingForProcess);

			flag = Call__PRO_READY(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__PRO_START)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__Processing);

			flag = Call__PRO_START(p_variable);
		}

		ELSE_IF__CTRL_MODE(sMODE__CLN_READY)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__PreparingForProcess);

			flag = Call__CLN_READY(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__CLN_START)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__Processing);

			flag = Call__CLN_START(p_variable);
		}

		ELSE_IF__CTRL_MODE(sMODE__MNT_READY)		
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__PreparingForProcess);

			flag = Call__MNT_READY(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__MNT_START)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__Processing);

			flag = Call__MNT_START(p_variable);
		}

		ELSE_IF__CTRL_MODE(sMODE__JOB_START_READY)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__Processing);

			flag = Call__JOB_START_READY(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__JOB_END_READY)
		{
			sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__Processing);

			flag = Call__JOB_END_READY(p_variable);
		}
	}

	// ...
	{
		sEXT_CH__CHM_STAGE_REPORT_TO_CTC->Set__DATA(STR__Idle);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("[%s] Aborted ... [%1d]", mode,flag);

		xLOG_CTRL->WRITE__LOG(log_msg);
		xCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
	}
	else
	{
		CString log_msg;
		log_msg.Format("[%s] Completed ... ", mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	sEXT_CH__SYSTEM_MSG->Set__DATA("");
	return flag;
}
int CObj__PMC_OPR::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATUS)		Mon__STATUS(p_variable);

	return 1;
}
