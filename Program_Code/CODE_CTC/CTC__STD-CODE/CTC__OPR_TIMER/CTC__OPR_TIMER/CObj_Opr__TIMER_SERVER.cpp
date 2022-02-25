#include "StdAfx.h"
#include "CObj_Opr__TIMER_SERVER.h"


//-------------------------------------------------------------------------
CObj_Opr__TIMER_SERVER::CObj_Opr__TIMER_SERVER()
{

}
CObj_Opr__TIMER_SERVER::~CObj_Opr__TIMER_SERVER()
{

}

//-------------------------------------------------------------------------
int CObj_Opr__TIMER_SERVER::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	return 1;
}
int CObj_Opr__TIMER_SERVER::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__TIME_SYNC_SERVER					1


int CObj_Opr__TIMER_SERVER::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CString str_name;

	// ...
	{
		str_name = "SYNC.COUNT";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SYNC_COUNT,str_name);

		//
		str_name = "MODULE.TIME";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(xCH__MODULE_TIME,str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__TIME_SYNC_SERVER);
	}
	return 1;
}

int CObj_Opr__TIMER_SERVER::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	
	// ...
	{
		alarm_title  = title;
		alarm_title += "OBJECT MODE : UNKNOWN";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("ABORT");
		
		ADD__ALARM_EX(ALID__OBJECT_MODE_UNKNOWN,alarm_title,alarm_msg,l_act);
	}
	return 1;
}

int CObj_Opr__TIMER_SERVER::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj_Opr__TIMER_SERVER::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{

	return 1;
}

//-------------------------------------------------------------------------
int CObj_Opr__TIMER_SERVER::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	return flag;
}

int CObj_Opr__TIMER_SERVER::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__TIME_SYNC_SERVER:
			Mon__Time_Sync_Server(p_variable);		
			break;
	}

	return 1;
}
