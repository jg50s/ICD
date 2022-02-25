#include "StdAfx.h"
#include "CObj_Opr__TIMER_CLIENT.h"


//-------------------------------------------------------------------------
CObj_Opr__TIMER_CLIENT::CObj_Opr__TIMER_CLIENT()
{

}
CObj_Opr__TIMER_CLIENT::~CObj_Opr__TIMER_CLIENT()
{

}

//-------------------------------------------------------------------------
int CObj_Opr__TIMER_CLIENT::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		CString str_name;

		str_name = "TIME_SYNC";
		ADD__CTRL_VAR(sMODE__TIME_SYNC,str_name);
	}
	return 1;
}
int CObj_Opr__TIMER_CLIENT::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__TIME_SYNC_SERVER			1

// ...
#define  APP_DSP__SYNC_USE					"DISABLE  ENABLE"
#define  APP_DSP__REF_TYPE					"HOUR  MIN"


int CObj_Opr__TIMER_CLIENT::__DEFINE__VARIABLE_STD(p_variable)
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

		//
		str_name = "SYNC.REQ.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SYNC_REQ_FLAG,str_name);

		// .....
		str_name = "CFG.SYNC.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__SYNC_USE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG__SYNC_USE,str_name);

		// 
		str_name = "CFG.SYNC.REF_TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__REF_TYPE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG__REF_TYPE,str_name);

		// 
		str_name = "CFG.SYNC.REF_TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"Hour/Min",0,1,60,"");
		LINK__VAR_ANALOG_CTRL(xCH__CFG__REF_TIME,str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(5.0,MON_ID__TIME_SYNC_SERVER);
	}
	return 1;
}

int CObj_Opr__TIMER_CLIENT::__DEFINE__ALARM(p_alarm)
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

int CObj_Opr__TIMER_CLIENT::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj_Opr__TIMER_CLIENT::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{

	return 1;
}

//-------------------------------------------------------------------------
int CObj_Opr__TIMER_CLIENT::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	IF__CTRL_MODE(sMODE__TIME_SYNC)		flag = Call__TIME_SYNC(p_variable);

	else
	{
		CString bff;
		CString alarm_msg;
		CString r_act;

		bff.Format("Object Name : %s\n",sObject_Name);
		alarm_msg  = bff;
		bff.Format("Unknown Object Mode : \"%s\"\n",mode);
		alarm_msg += bff;

		p_alarm->Popup__ALARM_With_MESSAGE(ALID__OBJECT_MODE_UNKNOWN,alarm_msg,r_act);
	}

	return flag;
}

int CObj_Opr__TIMER_CLIENT::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__TIME_SYNC_SERVER:
			Mon__TIme_Sync_Client(p_variable);
			break;
	}

	return 1;
}
