#include "StdAfx.h"
#include "CObj_Mng__SIGNAL_TOWER_EX.h"


//-------------------------------------------------------------------------
CObj_Mng__SIGNAL_TOWER_EX::CObj_Mng__SIGNAL_TOWER_EX()
{

}
CObj_Mng__SIGNAL_TOWER_EX::~CObj_Mng__SIGNAL_TOWER_EX()
{

}


//-------------------------------------------------------------------------
int CObj_Mng__SIGNAL_TOWER_EX::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	return 1;
}
int CObj_Mng__SIGNAL_TOWER_EX::__DEFINE__VERSION_HISTORY(version)
{
	return 1;
}


// ...
#define  MON_ID__SIGNAL_TOWER_CTRL					1


#define  DSP__RED_LIGHT_COLOR						\
"RED_ON     RED_OFF      RED_FLASH					\
 NOT_USE"

#define  DSP__YELLOW_LIGHT_COLOR					\
"YELLOW_ON   YELLOW_OFF   YELLOW_FLASH				\
 NOT_USE"

#define  DSP__GREEN_LIGHT_COLOR						\
"GREEN_ON    GREEN_OFF    GREEN_FLASH				\
 NOT_USE"

#define  DSP__BLUE_LIGHT_COLOR						\
"BLUE_ON     BLUE_OFF     BLUE_FLASH				\
 NOT_USE"

#define  DSP__LIGHT_CTRL		"OFF  ON  BLINK  IDLE"
#define  DSP__ON_OFF			"OFF  ON"
#define  DSP__MELODY_CTRL		"FOUP_ON  ALWAYS_ON"


int CObj_Mng__SIGNAL_TOWER_EX::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CString str_name;

	// RED ...
	{
		str_name = "CFG.RED.DEFAULT.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__RED_LIGHT_COLOR,"");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__RED_DEFAULT_LIGHT_COLOR,str_name);

		//
		str_name = "CFG.RED.STATUS1.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__RED_LIGHT_COLOR,"");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__RED_STATUS1_LIGHT_COLOR,str_name);

		str_name = "CFG.RED.STATUS2.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__RED_LIGHT_COLOR,"");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__RED_STATUS2_LIGHT_COLOR,str_name);

		str_name = "CFG.RED.STATUS3.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__RED_LIGHT_COLOR,"");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__RED_STATUS3_LIGHT_COLOR,str_name);
	}

	// AMBER ...
	{
		str_name = "CFG.AMBER.DEFAULT.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__YELLOW_LIGHT_COLOR, "");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__AMBER_DEFAULT_LIGHT_COLOR, str_name);

		//
		str_name = "CFG.AMBER.STATUS1.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__YELLOW_LIGHT_COLOR, "");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__AMBER_STATUS1_LIGHT_COLOR, str_name);

		str_name = "CFG.AMBER.STATUS2.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__YELLOW_LIGHT_COLOR, "");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__AMBER_STATUS2_LIGHT_COLOR, str_name);

		str_name = "CFG.AMBER.STATUS3.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__YELLOW_LIGHT_COLOR, "");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__AMBER_STATUS3_LIGHT_COLOR, str_name);

		str_name = "CFG.AMBER.STATUS4.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__YELLOW_LIGHT_COLOR, "");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__AMBER_STATUS4_LIGHT_COLOR, str_name);
	}

	// GREEN ...
	{
		str_name = "CFG.GREEN.DEFAULT.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__GREEN_LIGHT_COLOR, "");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__GREEN_DEFAULT_LIGHT_COLOR, str_name);

		//
		str_name = "CFG.GREEN.STATUS1.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__GREEN_LIGHT_COLOR, "");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__GREEN_STATUS1_LIGHT_COLOR,str_name);

		str_name = "CFG.GREEN.STATUS2.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__GREEN_LIGHT_COLOR, "");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__GREEN_STATUS2_LIGHT_COLOR,str_name);

		str_name = "CFG.GREEN.STATUS3.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__GREEN_LIGHT_COLOR, "");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__GREEN_STATUS3_LIGHT_COLOR,str_name);
	}

	// BLUE ...
	{
		str_name = "CFG.BLUE.DEFAULT.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__BLUE_LIGHT_COLOR,"");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__BLUE_DEFAULT_LIGHT_COLOR,str_name);

		//
		str_name = "CFG.BLUE.STATUS1.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__BLUE_LIGHT_COLOR,"");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__BLUE_STATUS1_LIGHT_COLOR,str_name);

		str_name = "CFG.BLUE.STATUS2.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__BLUE_LIGHT_COLOR,"");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__BLUE_STATUS2_LIGHT_COLOR,str_name);

		str_name = "CFG.BLUE.STATUS3.LIGHT_COLOR";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__BLUE_LIGHT_COLOR,"");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__BLUE_STATUS3_LIGHT_COLOR,str_name);
	}

	// LIGHT LED ...
	{
		str_name = "LIGHT.RED";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,DSP__LIGHT_CTRL,"");
		LINK__VAR_DIGITAL_CTRL(xCH__LIGHT_RED,str_name);

		str_name = "LIGHT.YELLOW";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,DSP__LIGHT_CTRL,"");
		LINK__VAR_DIGITAL_CTRL(xCH__LIGHT_YELLOW,str_name);

		str_name = "LIGHT.GREEN";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,DSP__LIGHT_CTRL,"");
		LINK__VAR_DIGITAL_CTRL(xCH__LIGHT_GREEN,str_name);

		str_name = "LIGHT.BLUE";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,DSP__LIGHT_CTRL,"");
		LINK__VAR_DIGITAL_CTRL(xCH__LIGHT_BLUE,str_name);
	}

	// MELODY ...
	{
		str_name = "MELODY.BUZZER";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,DSP__ON_OFF,"");
		LINK__VAR_DIGITAL_CTRL(xCH__MELODY_BUZZER,str_name);

		str_name = "MELODY.CTRL";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__MELODY_CTRL,"");
		LINK__VAR_DIGITAL_CTRL(xCH__MELODY_CTRL,str_name);
	}

	// STS ...
	{
		str_name = "PROCESS.END_TIME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__PROCESS_END_TIME,str_name);

		//
		str_name = "RED.STS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__RED_STS,str_name);

		str_name = "YELLOW.STS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__YELLOW_STS,str_name);

		str_name = "GREEN.STS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__GREEN_STS,str_name);

		str_name = "BLUE.STS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__BLUE_STS,str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0,MON_ID__SIGNAL_TOWER_CTRL);
	}
	return 1;
}

int CObj_Mng__SIGNAL_TOWER_EX::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s [CObj_Mng__SIGNAL_TOWER_EX] : ",sObject_Name);

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


//-------------------------------------------------------------------------
int CObj_Mng__SIGNAL_TOWER_EX::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	// ...
	{
		xSCH_MATERIAL_CTRL->Create__SERVICE_DB("");
		xSCH_MATERIAL_CTRL->Link__SERVICE_DB("");
	}
	return 1;
}


//-------------------------------------------------------------------------
int CObj_Mng__SIGNAL_TOWER_EX::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
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
int CObj_Mng__SIGNAL_TOWER_EX::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__SIGNAL_TOWER_CTRL:
			Mon__SIGNAL_TOWER_CTRL(p_variable);
			break;
	}
	return 1;
}
