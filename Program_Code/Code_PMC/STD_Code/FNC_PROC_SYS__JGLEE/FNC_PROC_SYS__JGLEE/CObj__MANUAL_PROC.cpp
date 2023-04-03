#include "StdAfx.h"
#include "CObj__MANUAL_PROC.h"


//-------------------------------------------------------------------------
CObj__MANUAL_PROC::CObj__MANUAL_PROC()
{

}
CObj__MANUAL_PROC::~CObj__MANUAL_PROC()
{

}

//-------------------------------------------------------------------------
int CObj__MANUAL_PROC::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__MANUAL_PROCESS, "MANUAL_PROCESS");

		ADD__CTRL_VAR(sMODE__ABORT_DECHUCK,  "ABORT_DECHUCK");
		ADD__CTRL_VAR(sMODE__DECHUCK_LIST,   "DECHUCK_LIST");
	}
	return 1;
}
int CObj__MANUAL_PROC::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}

int CObj__MANUAL_PROC::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// PARA ...
	{
		str_name = "PARA.RECIPE.NAME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_RECIPE_NAME, str_name);

		str_name = "PARA.DECHUCK.LIST";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_DECHUCK_LIST, str_name);

		str_name = "CFG.MANUAL.STEP.CTRL";
		STD__ADD_DIGITAL(str_name, "DISABLE  ENABLE");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_MANUAL_STEP_CTRL, str_name);
	}
	
	// CFG ...
	{
		str_name = "CFG.AGING.COUNT";
		STD__ADD_ANALOG(str_name, "num", 0, 1, 9999);
		LINK__VAR_ANALOG_CTRL(aCH__CFG_AGING_COUNT, str_name);

		str_name = "CUR.AGING.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_AGING_COUNT, str_name);
	}

	return 1;
}
int CObj__MANUAL_PROC::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	/*
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// Process Recipe does not exist .....
	{
		alarm_title  = title;
		alarm_title += "Process recipe does not exist.";

		alarm_msg = "Please, check process recipe file.\n";

		l_act.RemoveAll();
		l_act.Add("ABORT");
		l_act.Add("RETRY");
	
		ADD__ALARM_EX(ALID__PROCESS_RECIPE_NOT_EXIST,alarm_title,alarm_msg,l_act);
	}
	*/
	return 1;
}

int CObj__MANUAL_PROC::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__MANUAL_PROC::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString str_name;
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;

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

	// OBJ - DB_SYS ...
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		//
		var_name = "SYSTEM.MSG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_MSG,def_data,var_name);

		var_name = "FUNCTION.MSG";		
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__FNC_MSG,def_data,var_name);
	}

	// CH LINK .....
	{
		def_name = "CH__SYSTEM_LOCK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_LOCK, obj_name,var_name);

		def_name = "CH__RCP_NAME";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RCP_NAME, obj_name,var_name);

		def_name = "CH__RCP_ABORT_DECHUCK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RCP_ABORT_DECHUCK, obj_name,var_name);
	}

	// OBJ PROC .....
	{
		def_name = "OBJ__PROC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
		
		pOBJ_CTRL__PROC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		str_name = "PARA.MANUAL.STEP.CTRL.ACTIVE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PARA_MANUAL_STEP_CTRL_ACTIVE, obj_name,str_name);
		
		str_name = "PARA.MANUAL.STEP.CTRL.REQ";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PARA_MANUAL_STEP_CTRL_REQ, obj_name,str_name);

		//
		str_name = "PARA.MANUAL.PROCESS.DECHUCK.ACTIVE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PARA_MANUAL_PROCESS_DECHUCK_ACTIVE, obj_name,str_name);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__MANUAL_PROC::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	// ...
	{
		CString log_msg;
		log_msg.Format("[%s] Start", mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__MANUAL_PROCESS)
		{
			dEXT_CH__PARA_MANUAL_PROCESS_DECHUCK_ACTIVE->Set__DATA(STR__OFF);

			flag = Call__MANUAL_PROCESS(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__ABORT_DECHUCK)
		{
			dEXT_CH__PARA_MANUAL_PROCESS_DECHUCK_ACTIVE->Set__DATA(STR__ON);

			flag = Call__ABORTL_DECHUCK(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__DECHUCK_LIST)
		{
			dEXT_CH__PARA_MANUAL_PROCESS_DECHUCK_ACTIVE->Set__DATA(STR__ON);

			flag = Call__DECHUCK_LIST(p_variable);
		}
	}

	// ...
	{
		dCH__CFG_MANUAL_STEP_CTRL->Set__DATA(STR__DISABLE);
		
		dEXT_CH__PARA_MANUAL_STEP_CTRL_ACTIVE->Set__DATA(STR__OFF);
		sEXT_CH__PARA_MANUAL_STEP_CTRL_REQ->Set__DATA("");

		dEXT_CH__PARA_MANUAL_PROCESS_DECHUCK_ACTIVE->Set__DATA(STR__OFF);
		sEXT_CH__SYSTEM_MSG->Set__DATA("");
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("[%s] Aborted", mode);
		
		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("[%s] Completed", mode);
		
		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	return flag;
}

int CObj__MANUAL_PROC::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
