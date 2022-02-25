#include "StdAfx.h"
#include "CObj_FA__E94_CTRL.h"


//-------------------------------------------------------------------------
CObj_FA__E94_CTRL::CObj_FA__E94_CTRL()
{

}
CObj_FA__E94_CTRL::~CObj_FA__E94_CTRL()
{

}

//-------------------------------------------------------------------------
int CObj_FA__E94_CTRL::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	return 1;
}

int CObj_FA__E94_CTRL::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__E94_CTRL					1


int CObj_FA__E94_CTRL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	// ...
	CString str_name;

	str_name = "CJOB.ACTION";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	LINK__VAR_STRING_CTRL(xCH__CJOB_ACTION,str_name);

	str_name = "CJOB.NAME";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	LINK__VAR_STRING_CTRL(xCH__CJOB_NAME,str_name);

	str_name = "UPDATE.FLAG";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	LINK__VAR_STRING_CTRL(xCH__UPDATE_FLAG,str_name);

	for(int i=0;i<CFG_LP_LIMIT;i++)
	{
		str_name.Format("SCR.CJOB_START.WIN_NAME.%1d",i+1);
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(xCH_SCR__CJOB_START__WIN_NAME[i],str_name);

		str_name.Format("SCR.CJOB_START.CJOB_NAME.%1d",i+1);
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(xCH_SCR__CJOB_START__CJOB_NAME[i],str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3,MON_ID__E94_CTRL);
	}
	return 1;
}

int CObj_FA__E94_CTRL::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

int CObj_FA__E94_CTRL::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{

	return 1;
}

//-------------------------------------------------------------------------
int CObj_FA__E94_CTRL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	return 1;
}

//-------------------------------------------------------------------------
int CObj_FA__E94_CTRL::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	return flag;
}
int CObj_FA__E94_CTRL::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__E94_CTRL:
			Mon__E94_CTRL(p_variable);
			break;
	}

	return 1;
}
