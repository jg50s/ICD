#include "StdAfx.h"
#include "CObj__ACTIVE_HANDOFF_INF.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__ACTIVE_HANDOFF_INF::CObj__ACTIVE_HANDOFF_INF()
{

}
CObj__ACTIVE_HANDOFF_INF::~CObj__ACTIVE_HANDOFF_INF()
{

}

//-------------------------------------------------------------------------
int CObj__ACTIVE_HANDOFF_INF::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__S1, "S1");
		ADD__CTRL_VAR(sMODE__S2, "S2");
		ADD__CTRL_VAR(sMODE__S3, "S3");

		ADD__CTRL_VAR(sMODE__R1, "R1");
		ADD__CTRL_VAR(sMODE__R2, "R2");
		ADD__CTRL_VAR(sMODE__R3, "R3");

		ADD__CTRL_VAR(sMODE__SX1, "SX1");
		ADD__CTRL_VAR(sMODE__SX2, "SX2");
		ADD__CTRL_VAR(sMODE__SX3, "SX3");
		ADD__CTRL_VAR(sMODE__SX4, "SX4");
		ADD__CTRL_VAR(sMODE__SX5, "SX5");
		ADD__CTRL_VAR(sMODE__SX6, "SX6");

		ADD__CTRL_VAR(sMODE__RX1, "RX1");
		ADD__CTRL_VAR(sMODE__RX2, "RX2");
		ADD__CTRL_VAR(sMODE__RX3, "RX3");
		ADD__CTRL_VAR(sMODE__RX4, "RX4");
		ADD__CTRL_VAR(sMODE__RX5, "RX5");
		ADD__CTRL_VAR(sMODE__RX6, "RX6");
	}
	return 1;
}
int CObj__ACTIVE_HANDOFF_INF::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__ACTIVE_HANDOFF_INF::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	return 1;
}

int CObj__ACTIVE_HANDOFF_INF::__DEFINE__ALARM(p_alarm)
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

	}
	return 1;
}

int CObj__ACTIVE_HANDOFF_INF::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	// ...
	{
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__S1, "OBJ_MODE__S1",  "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__S2, "OBJ_MODE__S2",  "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__S3, "OBJ_MODE__S3",  "");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__R1, "OBJ_MODE__R1",  "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__R2, "OBJ_MODE__R2",  "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__R3, "OBJ_MODE__R3",  "");
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__ACTIVE_HANDOFF_INF::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,12*1,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CString def_name;
	CString def_data;
	CString obj_name;
	CString var_name;

	// ...
	CCommon_Utility x_utility;
	bool def_check;

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

	return 1;
}

//-------------------------------------------------------------------------
int CObj__ACTIVE_HANDOFF_INF::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;
	CString str_data;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

LOOP_RETRY:

	// ...
	{
		     IF__CTRL_MODE(sMODE__INIT)		flag = Call__INIT(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__S1)		flag = Call__S1(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__S2)		flag = Call__S2(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__S3)		flag = Call__S3(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__R1)		flag = Call__R1(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__R2)		flag = Call__R2(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__R3)		flag = Call__R3(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__SX1)		flag = Call__SX1(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SX2)		flag = Call__SX2(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SX3)		flag = Call__SX3(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SX4)		flag = Call__SX4(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SX5)		flag = Call__SX5(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SX6)		flag = Call__SX6(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__RX1)		flag = Call__RX1(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__RX2)		flag = Call__RX2(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__RX3)		flag = Call__RX3(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__RX4)		flag = Call__RX4(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__RX5)		flag = Call__RX5(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__RX6)		flag = Call__RX6(p_variable, p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__ACTIVE_HANDOFF_INF::__CALL__MONITORING(id,p_variable,p_alarm)
{
	return 1;
}
