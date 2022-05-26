#include "StdAfx.h"
#include "CObj__PMC_INF.h"


//-------------------------------------------------------------------------
CObj__PMC_INF::CObj__PMC_INF()
{

}
CObj__PMC_INF::~CObj__PMC_INF()
{

}

//-------------------------------------------------------------------------
int CObj__PMC_INF::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__AUTO_INIT,			"AUTO_INIT");
		ADD__CTRL_VAR(sMODE__TIME_INIT,			"TIME_INIT");
		ADD__CTRL_VAR(sMODE__SYSTEM_INIT,		"SYSTEM_INIT");
		ADD__CTRL_VAR(sMODE__SYSTEM_MAINT,		"SYSTEM_MAINT");

		ADD__CTRL_VAR(sMODE__PUMP,				"PUMP");
		ADD__CTRL_VAR(sMODE__VENT,				"VENT");
		ADD__CTRL_VAR(sMODE__LEAK_CHECK,		"LEAK_CHECK");
		ADD__CTRL_VAR(sMODE__AUTO_PM,		    "AUTO_PM");
		ADD__CTRL_VAR(sMODE__PURGE,				"PURGE");

		ADD__CTRL_VAR(sMODE__SLOT_OPEN,			"SLOT.OPEN");
		ADD__CTRL_VAR(sMODE__SLOT_CLOSE,		"SLOT.CLOSE");

		ADD__CTRL_VAR(sMODE__PIN_UP,			"PIN.UP");
		ADD__CTRL_VAR(sMODE__PIN_DOWN,			"PIN.DOWN");

		ADD__CTRL_VAR(sMODE__PICK_READY,		"PICK_READY");
		ADD__CTRL_VAR(sMODE__PICK_X_READY,		"PICK_X_READY");
		ADD__CTRL_VAR(sMODE__PICK_COMPLETE,		"PICK_COMPLETE");
		ADD__CTRL_VAR(sMODE__PICK_X_COMPLETE,	"PICK_X_COMPLETE");

		ADD__CTRL_VAR(sMODE__PLACE_READY,		"PLACE_READY");
		ADD__CTRL_VAR(sMODE__PLACE_X_READY,		"PLACE_X_READY");
		ADD__CTRL_VAR(sMODE__PLACE_COMPLETE,	"PLACE_COMPLETE");
		ADD__CTRL_VAR(sMODE__PLACE_X_CONPLETE,	"PLACE_X_COMPLETE");

		ADD__CTRL_VAR(sMODE__PRO_READY,			"PRO_READY");
		ADD__CTRL_VAR(sMODE__PRO_START,			"PRO_START");
		ADD__CTRL_VAR(sMODE__CLN_READY,			"CLN_READY");
		ADD__CTRL_VAR(sMODE__CLN_START,			"CLN_START");
		ADD__CTRL_VAR(sMODE__PRE_READY,			"PRE_READY");
		ADD__CTRL_VAR(sMODE__PRE_START,			"PRE_START");

		ADD__CTRL_VAR(sMODE__MNT_READY,			"MNT_READY");
		ADD__CTRL_VAR(sMODE__MNT_START,			"MNT_START");	

		ADD__CTRL_VAR(sMODE__JOB_START_READY,	"JOB_START_READY");
		ADD__CTRL_VAR(sMODE__JOB_END_READY,		"JOB_END_READY");
	}
	return 1;
}
int CObj__PMC_INF::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__PMC_INF::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString dsp_list;

	// ...
	{
		str_name = "MODULE.TIME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__MODULE_TIME,str_name);
	}

	return 1;
}
int CObj__PMC_INF::__DEFINE__ALARM(p_alarm)
{

	return 1;
}

int CObj__PMC_INF::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	// EXT MODE ...
	{
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__SYSTEM_INIT,  "OBJ_MODE__SYSTEM_INIT", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__SYSTEM_MAINT, "OBJ_MODE__SYSTEM_MAINT","");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PUMP,       "OBJ_MODE__PUMP","");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__VENT,       "OBJ_MODE__VENT","");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__LEAK_CHECK, "OBJ_MODE__LEAK_CHECK","");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__AUTO_PM,    "OBJ_MODE__AUTO_PM","");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PURGE,      "OBJ_MODE__PURGE", "");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__SLOT_OPEN,  "OBJ_MODE__SLOT_OPEN",  "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__SLOT_CLOSE, "OBJ_MODE__SLOT_CLOSE", "");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PIN_UP,     "OBJ_MODE__PIN_UP",   "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PIN_DOWN,   "OBJ_MODE__PIN_DOWN", "");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PICK_READY,      "OBJ_MODE__PICK_READY",    "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PICK_X_READY,    "OBJ_MODE__XPICK_READY",   "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PICK_COMPLETE,   "OBJ_MODE__PICK_COMPLETE", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PICK_X_COMPLETE, "OBJ_MODE__XPICK_COMPLETE","");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PLACE_READY,     "OBJ_MODE__PLACE_READY",    "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PLACE_X_READY,   "OBJ_MODE__XPLACE_READY",   "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PLACE_COMPLETE,  "OBJ_MODE__PLACE_COMPLETE", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PLACE_X_COMPLETE,"OBJ_MODE__XPLACE_COMPLETE","");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PRO_READY, "OBJ_MODE__PRO_READY", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PRO_START, "OBJ_MODE__PRO_START", "");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__CLN_READY, "OBJ_MODE__CLN_READY", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__CLN_START, "OBJ_MODE__CLN_START", "");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PRE_READY, "OBJ_MODE__PRE_READY", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__PRE_START, "OBJ_MODE__PRE_START", "");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__MNT_READY, "OBJ_MODE__MNT_READY", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__MNT_START, "OBJ_MODE__MNT_START", "");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__JOB_START_READY,"OBJ_MODE__JOB_START_READY","");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__JOB_END_READY,  "OBJ_MODE__JOB_END_READY","");
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__PMC_INF::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString str_name;
	CString def_name;
	CString def_value;
	CString obj_name;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

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
	{
		CString obj_name = "__EQP";

		LINK__EXT_VAR_STRING_CTRL(xEXT_CH__STEP_START, obj_name,"##PMC.STEP.START");
		LINK__EXT_VAR_STRING_CTRL(xEXT_CH__STEP_END,   obj_name,"##PMC.STEP.END");
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__PMC_INF::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	{
		CString log_msg;
		log_msg.Format("Start [%s] ... By %s \n", mode, p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	int flag = -1;

	// ...
	{
			 IF__CTRL_MODE(sMODE__AUTO_INIT)			flag = Call__AUTO_INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__TIME_INIT)			flag = Call__TIME_INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__SYSTEM_INIT)			flag = Call__SYSTEM_INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__SYSTEM_MAINT)			flag = Call__SYSTEM_MAINT(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PUMP)					flag = Call__PUMP(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__VENT)					flag = Call__VENT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__LEAK_CHECK)			flag = Call__LEAK_CHECK(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__AUTO_PM)		     	flag = Call__AUTO_PM(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PURGE)				flag = Call__PURGE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__SLOT_OPEN)			flag = Call__SLOT_OPEN(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__SLOT_CLOSE)			flag = Call__SLOT_CLOSE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PIN_UP)				flag = Call__PIN_UP(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PIN_DOWN)				flag = Call__PIN_DOWN(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PICK_READY)			flag = Call__PICK_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PICK_X_READY)			flag = Call__PICK_X_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PICK_COMPLETE)		flag = Call__PICK_COMPLETE(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PICK_X_COMPLETE)		flag = Call__PICK_X_COMPLETE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PLACE_READY)			flag = Call__PLACE_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_X_READY)		flag = Call__PLACE_X_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_COMPLETE)		flag = Call__PLACE_COMPLETE(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_X_CONPLETE)		flag = Call__PLACE_X_COMPLETE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PRO_READY)			flag = Call__PRO_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PRO_START)			flag = Call__PRO_START(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__CLN_READY)			flag = Call__CLN_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__CLN_START)			flag = Call__CLN_START(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PRE_READY)			flag = Call__PRE_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PRE_START)			flag = Call__PRE_START(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__MNT_READY)			flag = Call__MNT_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__MNT_START)			flag = Call__MNT_START(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__JOB_START_READY)		flag = Call__JOB_START_READY(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__JOB_END_READY)		flag = Call__JOB_END_READY(p_variable);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;

		log_msg.Format("[%s] Aborted ... :  Flag [%1d], Ctrl [%1d]",
						mode,
						flag,
						p_variable->Check__CTRL_ABORT());

		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		CString log_msg;

		log_msg.Format("Completed ... :  [%s]",mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__PMC_INF::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
