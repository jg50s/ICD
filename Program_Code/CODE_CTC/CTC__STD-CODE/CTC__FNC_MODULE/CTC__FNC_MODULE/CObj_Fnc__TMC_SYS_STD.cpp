#include "StdAfx.h"
#include "CObj_Fnc__TMC_SYS_STD.h"


//-------------------------------------------------------------------------
CObj_Fnc__TMC_SYS_STD::CObj_Fnc__TMC_SYS_STD()
{

}
CObj_Fnc__TMC_SYS_STD::~CObj_Fnc__TMC_SYS_STD()
{

}

//-------------------------------------------------------------------------
int CObj_Fnc__TMC_SYS_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__ALL_INIT, "ALL_INIT");

		ADD__CTRL_VAR(sMODE__TIME_INIT,  "TIME_INIT");
		ADD__CTRL_VAR(sMODE__SYSTEM_INIT,"SYSTEM_INIT");

		//
		ADD__CTRL_VAR(sMODE__CTC_TO_TMC,"CTC_TO_TMC");
		ADD__CTRL_VAR(sMODE__TMC_TO_CTC,"TMC_TO_CTC");

		//
		ADD__CTRL_VAR(sMODE__WAFER_RESYNC_CLEAR_SYS, "WAFER_RESYNC.CLEAR_SYS");
		ADD__CTRL_VAR(sMODE__WAFER_RESYNC_CLEAR_PMx, "WAFER_RESYNC.CLEAR_PMx");
		ADD__CTRL_VAR(sMODE__WAFER_RESYNC_CLEAR_LLx, "WAFER_RESYNC.CLEAR_LLx");

		//
		ADD__CTRL_VAR(sMODE__SYSTEM_MAINT,"SYSTEM_MAINT");
	}
	return 1;
}

int CObj_Fnc__TMC_SYS_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define DSP__INIT_MODE						\
"ONLY_SYSTEM  TIME_SYSTEM  AUTO"


int CObj_Fnc__TMC_SYS_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// CFG ...
	{
		str_name = "CFG.INIT_MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__INIT_MODE,"");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__INIT_MODE,str_name);
	}

	return 1;
}

int CObj_Fnc__TMC_SYS_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	{

	}
	return 1;
}

int CObj_Fnc__TMC_SYS_STD::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	// ...
	{
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__AUTO_INIT,    "OBJ_MODE__AUTO_INIT",    "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__SYSTEM_INIT,  "OBJ_MODE__SYSTEM_INIT",  "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__TIME_INIT,    "OBJ_MODE__TIME_INIT",    "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__SYSTEM_MAINT, "OBJ_MODE__SYSTEM_MAINT", "");

		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__CTC_TO_TMC, "OBJ_MODE__CTC_TO_TMC", "");
		ADD__EXT_FNC_MODE_WITH_COMMENT(sEXT_MODE__TMC_TO_CTC, "OBJ_MODE__TMC_TO_CTC", "");
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Fnc__TMC_SYS_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString obj_name;

	// OBJ - ATM_ROBOT ...
	{
		def_name = "OBJ__ATM_ROBOT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
	
		pOBJ_CTRL__ATM_ROBOT = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}
	// OBJ - VAC_ROBOT
	{
		def_name = "OBJ__VAC_ROBOT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__VAC_ROBOT = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj_Fnc__TMC_SYS_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		     IF__CTRL_MODE(sMODE__ALL_INIT)						flag = Call__ALL_INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__TIME_INIT)					flag = Call__TIME_INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__SYSTEM_INIT)					flag = Call__SYSTEM_INIT(p_variable);
		
		ELSE_IF__CTRL_MODE(sMODE__CTC_TO_TMC)					flag = Call__CTC_TO_TMC(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__TMC_TO_CTC)					flag = Call__TMC_TO_CTC(p_variable);
		
		ELSE_IF__CTRL_MODE(sMODE__WAFER_RESYNC_CLEAR_SYS)		flag = Call__WAFER_RESYNC_CLEAR_SYS(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__WAFER_RESYNC_CLEAR_PMx)		flag = Call__WAFER_RESYNC_CLEAR_PMx(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__WAFER_RESYNC_CLEAR_LLx)		flag = Call__WAFER_RESYNC_CLEAR_LLx(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__SYSTEM_MAINT)					flag = Call__SYSTEM_MAINT(p_variable);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{

	}
	return flag;
}
int CObj_Fnc__TMC_SYS_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
