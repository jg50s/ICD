#include "StdAfx.h"
#include "CObj__DEBUG_STD.h"


//-------------------------------------------------------------------------
CObj__DEBUG_STD::CObj__DEBUG_STD()
{

}
CObj__DEBUG_STD::~CObj__DEBUG_STD()
{

}

//-------------------------------------------------------------------------
int CObj__DEBUG_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__TEST, "TEST");
	}
	return 1;
}
int CObj__DEBUG_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__DEBUG_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CString str_name;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	return 1;
}
int CObj__DEBUG_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

//-------------------------------------------------------------------------
int CObj__DEBUG_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{

	return 1;
}

//-------------------------------------------------------------------------
int CObj__DEBUG_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__TEST)		flag = Call__TEST(p_variable,p_alarm);
	}

	return flag;
}
int CObj__DEBUG_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
