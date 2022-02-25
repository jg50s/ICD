#include "StdAfx.h"
#include "CObj_Fnc__PMC_SYS_STD.h"


//-------------------------------------------------------------------------
CObj_Fnc__PMC_SYS_STD::CObj_Fnc__PMC_SYS_STD()
{

}
CObj_Fnc__PMC_SYS_STD::~CObj_Fnc__PMC_SYS_STD()
{

}

//-------------------------------------------------------------------------
int CObj_Fnc__PMC_SYS_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;
	iPMx_SIZE = 0;

	// ...
	{
		ADD__CTRL_VAR(sMODE__ALL_INIT,     "ALL_INIT");
		ADD__CTRL_VAR(sMODE__TIME_INIT,    "TIME_INIT");
		ADD__CTRL_VAR(sMODE__SYSTEM_INIT,  "SYSTEM_INIT");
		ADD__CTRL_VAR(sMODE__SYSTEM_MAINT, "SYSTEM_MAINT");
	}
	return 1;
}

int CObj_Fnc__PMC_SYS_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define DSP__INIT_MODE					\
"ONLY_SYSTEM  TIME_SYSTEM  AUTO"


int CObj_Fnc__PMC_SYS_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// ...
	{
		str_name = "ACTIVE.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ACTIVE_STATE, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.INIT_MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__INIT_MODE,"");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__INIT_MODE, str_name);
	}
	return 1;
}

int CObj_Fnc__PMC_SYS_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	{

	}
	return 1;
}

int CObj_Fnc__PMC_SYS_STD::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{

	return 1;
}

//-------------------------------------------------------------------------
int CObj_Fnc__PMC_SYS_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString def_name;
	CString def_data;
	CString obj_name;
	CString var_name;
	int i;

	// ...
	{
		def_name = "PM_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iPMx_SIZE = atoi(def_data);
		if(iPMx_SIZE > CFG_PM_LIMIT)		iPMx_SIZE = CFG_PM_LIMIT;

		for(i=0; i<iPMx_SIZE; i++)
		{
			obj_name.Format("PHY_PM%1d", i+1);
			pOBJ_CTRL__PMx[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			var_name = "OBJ.VIRTUAL.STATUS";
			LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__PMx__OBJ_STATUS[i], obj_name,var_name);
		}
	}

	sCH__ACTIVE_STATE->Set__DATA("ALL");
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Fnc__PMC_SYS_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	sCH__ACTIVE_STATE->Set__DATA("INIT");

	// ...
	{
			 IF__CTRL_MODE(sMODE__ALL_INIT)			flag = Call__ALL_INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__TIME_INIT)		flag = Call__TIME_INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__SYSTEM_INIT)		flag = Call__SYSTEM_INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__SYSTEM_MAINT)
		{
			sCH__ACTIVE_STATE->Set__DATA("MAINT");
			flag = Call__SYSTEM_MAINT(p_variable);
		}
	}

	sCH__ACTIVE_STATE->Set__DATA("ALL");

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{

	}
	return flag;
}
int CObj_Fnc__PMC_SYS_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
