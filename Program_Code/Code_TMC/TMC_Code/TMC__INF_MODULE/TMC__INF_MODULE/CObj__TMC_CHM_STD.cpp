#include "StdAfx.h"
#include "CObj__TMC_CHM_STD.h"


//-------------------------------------------------------------------------
CObj__TMC_CHM_STD::CObj__TMC_CHM_STD()
{

}
CObj__TMC_CHM_STD::~CObj__TMC_CHM_STD()
{

}

//-------------------------------------------------------------------------
int CObj__TMC_CHM_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,  "INIT");
		ADD__CTRL_VAR(sMODE__MAINT, "MAINT");

		ADD__CTRL_VAR(sMODE__PUMP, "PUMP");
		ADD__CTRL_VAR(sMODE__VENT, "VENT");

		ADD__CTRL_VAR(sMODE__PMx_SV_OPEN,  "PMx.SV_OPEN");
		ADD__CTRL_VAR(sMODE__PMx_SV_CLOSE, "PMx.SV_CLOSE");
	}
	return 1;
}
int CObj__TMC_CHM_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__TMC_CHM_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CString var_name;

	// PARA ...
	{
		var_name = "PARA.PMx.ID";
		STD__ADD_DIGITAL(var_name, "1 2 3 4 5 6 7 8 9 10");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_PMx_ID, var_name);
	}

	return 1;
}

int CObj__TMC_CHM_STD::__DEFINE__ALARM(p_alarm)
{

	return 1;
}

int CObj__TMC_CHM_STD::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__TMC_CHM_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	// ...
	{
		def_name = "OBJ__TMC_CHM";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);

		pTMC_CHM__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

		//
		str_name = "OBJ.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__OBJ_STATUS, def_data,str_name);

		str_name = "PARA.PMx.ID";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PARA_PMx_ID, def_data,str_name);
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
int CObj__TMC_CHM_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
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
		     IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__MAINT)				flag = Call__MAINT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PUMP)					flag = Call__PUMP(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__VENT)					flag = Call__VENT(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__PMx_SV_OPEN)			flag = Call__PMx_SV_OPEN(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PMx_SV_CLOSE)			flag = Call__PMx_SV_CLOSE(p_variable);
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
int CObj__TMC_CHM_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
