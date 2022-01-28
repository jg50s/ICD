#include "StdAfx.h"
#include "CObj__TMC_SYSTEM_STD.h"


//-------------------------------------------------------------------------
CObj__TMC_SYSTEM_STD::CObj__TMC_SYSTEM_STD()
{

}
CObj__TMC_SYSTEM_STD::~CObj__TMC_SYSTEM_STD()
{

}

//-------------------------------------------------------------------------
int CObj__TMC_SYSTEM_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__AUTO_INIT,    "AUTO_INIT");
		ADD__CTRL_VAR(sMODE__TIME_INIT,    "TIME_INIT");
		ADD__CTRL_VAR(sMODE__SYSTEM_INIT,  "SYSTEM_INIT");
		ADD__CTRL_VAR(sMODE__SYSTEM_MAINT, "SYSTEM_MAINT");

		ADD__CTRL_VAR(sMODE__CTC_TO_TMC,   "CTC_TO_TMC");
		ADD__CTRL_VAR(sMODE__TMC_TO_CTC,   "TMC_TO_CTC");
	}
	return 1;
}
int CObj__TMC_SYSTEM_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__TMC_SYSTEM_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	str_name = "MODULE.TIME";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__MODULE_TIME,str_name);
	
	return 1;
}
int CObj__TMC_SYSTEM_STD::__DEFINE__ALARM(p_alarm)
{

	return 1;
}

int CObj__TMC_SYSTEM_STD::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__TMC_SYSTEM_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	// ...
	{
		def_name = "OBJ__TMC_SYS";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);

		pTMC_SYS__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

		//
		str_name = "OBJ.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__OBJ_STATUS, def_data,str_name);
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__TMC_SYSTEM_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	// ...
	{
		CString log_msg;

		log_msg.Format("Start ... :  [%s]",mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	int flag = -1;

	// ...
	{
		     IF__CTRL_MODE(sMODE__SYSTEM_INIT)		flag = Call__SYSTEM_INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__SYSTEM_MAINT)		flag = Call__SYSTEM_MAINT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__AUTO_INIT)		flag = Call__AUTO_INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__TIME_INIT)		flag = Call__TIME_INIT(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__CTC_TO_TMC)		flag = Call__CTC_TO_TMC(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__TMC_TO_CTC)		flag = Call__TMC_TO_CTC(p_variable);

		else									
		{

		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		dEXT_CH__OBJ_STATUS->Set__DATA("MAINTMODE");

		// ...
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

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
int CObj__TMC_SYSTEM_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
