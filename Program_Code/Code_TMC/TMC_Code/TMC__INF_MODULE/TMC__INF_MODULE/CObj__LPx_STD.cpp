#include "StdAfx.h"
#include "CObj__LPx_STD.h"


//-------------------------------------------------------------------------
CObj__LPx_STD::CObj__LPx_STD()
{

}
CObj__LPx_STD::~CObj__LPx_STD()
{

}

//-------------------------------------------------------------------------
int CObj__LPx_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__PREPLOAD, "PREPLOAD");
		ADD__CTRL_VAR(sMODE__LOAD,     "LOAD");

		ADD__CTRL_VAR(sMODE__RLSUNLOAD, "RLSUNLOAD");
		ADD__CTRL_VAR(sMODE__UNLOAD,    "UNLOAD");

		ADD__CTRL_VAR(sMODE__CID_READ,     "CID_READ");
		ADD__CTRL_VAR(sMODE__RF_CID_READ,  "RF_CID_READ");
		ADD__CTRL_VAR(sMODE__RF_PAGE_READ, "RF_PAGE_READ");
		ADD__CTRL_VAR(sMODE__RF_CID_WRITE, "RF_CID_WRITE");
		ADD__CTRL_VAR(sMODE__RF_PAGE_WRITE,"RF_PAGE_WRITE");
	}
	return 1;
}
int CObj__LPx_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__LPx_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	LINK__VAR_DIGITAL_CTRL(dCH__OBJ_CTRL, "CTRL");

	return 1;
}
int CObj__LPx_STD::__DEFINE__ALARM(p_alarm)
{

	return 1;
}

int CObj__LPx_STD::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	ADD__EXT_VARIABLE(sEXT_VAR__LPx_RELOAD_FLAG, "VAR__LP_RELOAD_FLAG");
	
	return 1;
}

//-------------------------------------------------------------------------
int CObj__LPx_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	// ...
	{
		def_name = "OBJ.LPx";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);

		pLPx__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

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
int CObj__LPx_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;
	int available_flag = -1;

	// ...
	{
		CString log_msg;

		log_msg.Format("Start ... :  [%s]",mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__PREPLOAD)				flag = Call__PREPLOAD(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__LOAD)					flag = Call__LOAD(mode,p_variable);
		ELSE_IF__CTRL_MODE(sMODE__RLSUNLOAD)			flag = Call__RLSUNLOAD(mode,p_variable);

		ELSE_IF__CTRL_MODE(sMODE__UNLOAD)
		{
			flag = Call__UNLOAD(mode,p_variable);

			if(p_variable->Check__EXT_FNC_VARIABLE(sEXT_VAR__LPx_RELOAD_FLAG,"YES") > 0)
			{
				available_flag = 1;
				flag = 1;
			}
		}

		ELSE_IF__CTRL_MODE(sMODE__CID_READ)				flag = Call__CID_READ(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__RF_CID_READ)			flag = Call__RF_CID_READ(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__RF_PAGE_READ)			flag = Call__RF_PAGE_READ(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__RF_CID_WRITE)			flag = Call__RF_CID_WRITE(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__RF_PAGE_WRITE)		flag = Call__RF_PAGE_WRITE(p_variable);

		else									
		{

		}
	}

	if((available_flag < 0)
	&& ((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0)))
	{
		dEXT_CH__OBJ_STATUS->Set__DATA("MAINTMODE");

		// ...
		{
			CString log_msg;

			log_msg.Format("Aborted ... :  [%s]",mode);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}
	else
	{
		if(available_flag > 0)
		{
			dCH__OBJ_CTRL->Set__DATA("RUN");
			dEXT_CH__OBJ_STATUS->Set__DATA("STANDBY");
		}

		// ...
		{
			CString log_msg;
			
			log_msg.Format("Completed ... :  [%s]",mode);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	return flag;
}

int CObj__LPx_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
