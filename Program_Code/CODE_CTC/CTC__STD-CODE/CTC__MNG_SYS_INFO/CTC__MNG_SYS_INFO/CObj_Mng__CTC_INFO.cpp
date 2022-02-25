#include "StdAfx.h"
#include "CObj_Mng__CTC_INFO.h"


//-------------------------------------------------------------------------
CObj_Mng__CTC_INFO::CObj_Mng__CTC_INFO()
{

}
CObj_Mng__CTC_INFO::~CObj_Mng__CTC_INFO()
{

}

//-------------------------------------------------------------------------
int CObj_Mng__CTC_INFO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{

	}
	return 1;
}
int CObj_Mng__CTC_INFO::__DEFINE__VERSION_HISTORY(version)
{
	// ...
	{

	}
	return 1;
}


// #define MON_ID__INFO_CTRL							1


int CObj_Mng__CTC_INFO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	{
		// p_variable->Add__MONITORING_PROC(3.0,MON_ID__INFO_CTRL);
	}
	return 1;
}
int CObj_Mng__CTC_INFO::__DEFINE__ALARM(p_alarm)
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

int CObj_Mng__CTC_INFO::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	// ...
	{
		mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
		p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj_Mng__CTC_INFO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString obj_name;
	CString var_name;

	// ...
	{
		obj_name = "__EQP";
		var_name = "##SEQ0.CONNECT.STATUS";

		LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__CTC_CONNECT_STATUS, obj_name,var_name);
	}

	xEXT_CH__CTC_CONNECT_STATUS->Set__DATA(STR__ONLINE);
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Mng__CTC_INFO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	/*
	IF__OBJ_MODE(sMODE__PRO_START)		flag = Call__PRO_START(p_variable);

	else
	*/
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
int CObj_Mng__CTC_INFO::__CALL__MONITORING(id,p_variable,p_alarm)
{
	/*
	switch(id)
	{
		case MON_ID__INFO_CTRL:
			Mon__INFO_CTRL(p_variable,p_alarm);
			break;
	}
	*/

	return 1;
}
