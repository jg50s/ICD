#include "StdAfx.h"
#include "CObj__STD_TYPE.h"
#include "CObj__STD_TYPE__ALID.h"


//-------------------------------------------------------------------------
CObj__STD_TYPE::CObj__STD_TYPE()
{

}
CObj__STD_TYPE::~CObj__STD_TYPE()
{

}

//-------------------------------------------------------------------------
int CObj__STD_TYPE::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		// LIGHT RED -----
		ADD__CTRL_VAR(sMODE__RED_ON,	"RED_ON");
		ADD__CTRL_VAR(sMODE__RED_OFF,	"RED_OFF");
		ADD__CTRL_VAR(sMODE__RED_BLINK, "RED_BLINK");

		// LIGHT YELLOW -----
		ADD__CTRL_VAR(sMODE__YELLOW_ON,   "YELLOW_ON");
		ADD__CTRL_VAR(sMODE__YELLOW_OFF,  "YELLOW_OFF");
		ADD__CTRL_VAR(sMODE__YELLOW_BLINK,"YELLOW_BLINK");

		// LIGHT GREEN -----
		ADD__CTRL_VAR(sMODE__GREEN_ON,    "GREEN_ON");
		ADD__CTRL_VAR(sMODE__GREEN_OFF,   "GREEN_OFF");
		ADD__CTRL_VAR(sMODE__GREEN_BLINK, "GREEN_BLINK");

		// LIGHT BLUE -----
		ADD__CTRL_VAR(sMODE__BLUE_ON,     "BLUE_ON");
		ADD__CTRL_VAR(sMODE__BLUE_OFF,    "BLUE_OFF");
		ADD__CTRL_VAR(sMODE__BLUE_BLINK,  "BLUE_BLINK");

		// WHITE BLUE -----
		ADD__CTRL_VAR(sMODE__WHITE_ON,    "WHITE_ON");
		ADD__CTRL_VAR(sMODE__WHITE_OFF,   "WHITE_OFF");
		ADD__CTRL_VAR(sMODE__WHITE_BLINK, "WHITE_BLINK");

		// ALARM BUZZER -----
		ADD__CTRL_VAR(sMODE__ALARM_BUZZER_ON, "ALARM_BUZZER_ON");
		ADD__CTRL_VAR(sMODE__ALARM_BUZZER_OFF,"ALARM_BUZZER_OFF");
		ADD__CTRL_VAR(sMODE__ALARM_BUZZER_RESET_ON, "ALARM_BUZZER_RESET_ON");
		ADD__CTRL_VAR(sMODE__ALARM_BUZZER_RESET_OFF,"ALARM_BUZZER_RESET_OFF");

		// MELODY -----
		ADD__CTRL_VAR(sMODE__MELODY_ON,   "MELODY_ON");
		ADD__CTRL_VAR(sMODE__MELODY_OFF,  "MELODY_OFF");
	}

	return 1;
}
int CObj__STD_TYPE::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR				1

// ...
#define APP_DSP__OFF_ON_BLINK			"OFF  ON  BLINK  IDLE"
#define APP_DSP__OFF_ON					"OFF  ON"
#define APP_DSP__ENABLE_DISABLE			"ENABLE  DISABLE"
#define APP_DSP__YES_NO					"YES  NO"
#define APP_DSP__MELODY_NUM				"1	2	3	4"


int CObj__STD_TYPE::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// ...
	{
		str_name = "CFG.IO_MONITOR.ACTIVE.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__ENABLE_DISABLE, "");
		LINK__VAR_DIGITAL_CTRL(dCH__IO_MONITOR__ACTIVE_FLAG, str_name);

		str_name = "CFG.BLINK.PERIOD.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.1, 2.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_BLINK_PERIOD_SEC, str_name);

		str_name = "CFG.BLINK.MODE.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__ENABLE_DISABLE, "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_BLINK_MODE_USE, str_name);
	}

	// LINK REMOTE...
	{
		str_name = "OTR.IN.MON.dLIGHT.RED";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__OFF_ON_BLINK,"");
		LINK__VAR_DIGITAL_CTRL(dCH__LIGHT_RED,str_name);

		str_name = "OTR.IN.MON.dLIGHT.YELLOW";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__OFF_ON_BLINK,"");
		LINK__VAR_DIGITAL_CTRL(dCH__LIGHT_YELLOW,str_name);

		str_name = "OTR.IN.MON.dLIGHT.GREEN";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__OFF_ON_BLINK,"");
		LINK__VAR_DIGITAL_CTRL(dCH__LIGHT_GREEN,str_name);

		str_name = "OTR.IN.MON.dLIGHT.BLUE";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__OFF_ON_BLINK,"");
		LINK__VAR_DIGITAL_CTRL(dCH__LIGHT_BLUE,str_name);

		str_name = "OTR.IN.MON.dLIGHT.WHITE";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__OFF_ON_BLINK,"");
		LINK__VAR_DIGITAL_CTRL(dCH__LIGHT_WHITE,str_name);

		//.....
		str_name = "CFG.BUZZER.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__YES_NO,"");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_BUZZER_USE,str_name);

		str_name = "OTR.IN.MON.dALARM.BUZZER";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__OFF_ON,"");
		LINK__VAR_DIGITAL_CTRL(dCH__ALARM_BUZZER,str_name);

		// ...
		str_name = "CFG.MELODY.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__YES_NO,"");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_MELODY_USE,str_name);

		str_name = "CFG.MELODY.NUM";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__MELODY_NUM,"");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_MELODY_NUM,str_name);

		str_name = "OTR.IN.MON.dMELODY.BUZZER";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__OFF_ON,"");
		LINK__VAR_DIGITAL_CTRL(dCH__MELODY_BUZZER,str_name);
	}

	// LINK LOCAL...
	{
		str_name = "LINK_LOCAL.LIGHT.RED";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, APP_DSP__OFF_ON_BLINK,"");
		LINK__VAR_DIGITAL_CTRL(dCH__LINK_LOCAL_LIGHT_RED,str_name);

		str_name = "LINK_LOCAL.LIGHT.YELLOW";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, APP_DSP__OFF_ON_BLINK,"");
		LINK__VAR_DIGITAL_CTRL(dCH__LINK_LOCAL_LIGHT_YELLOW,str_name);

		str_name = "LINK_LOCAL.LIGHT.GREEN";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, APP_DSP__OFF_ON_BLINK,"");
		LINK__VAR_DIGITAL_CTRL(dCH__LINK_LOCAL_LIGHT_GREEN,str_name);

		str_name = "LINK_LOCAL.LIGHT.BLUE";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, APP_DSP__OFF_ON_BLINK,"");
		LINK__VAR_DIGITAL_CTRL(dCH__LINK_LOCAL_LIGHT_BLUE,str_name);

		str_name = "LINK_LOCAL.LIGHT.WHITE";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, APP_DSP__OFF_ON_BLINK,"");
		LINK__VAR_DIGITAL_CTRL(dCH__LINK_LOCAL_LIGHT_WHITE,str_name);

		//
		str_name = "LINK_LOCAL.ALARM.BUZZER";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__OFF_ON,"");
		LINK__VAR_DIGITAL_CTRL(dCH__LINK_LOCAL_ALARM_BUZZER, str_name);

		str_name = "LINK_LOCAL.MELODY.BUZZER";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__OFF_ON,"");
		LINK__VAR_DIGITAL_CTRL(dCH__LINK_LOCAL_MELODY_BUZZER, str_name);
	}

	// LINK SET...
	{
		str_name = "LINK_SET.LIGHT.RED";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_SET_LIGHT_RED, str_name);

		str_name = "LINK_SET.LIGHT.YELLOW";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_SET_LIGHT_YELLOW, str_name);

		str_name = "LINK_SET.LIGHT.GREEN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_SET_LIGHT_GREEN, str_name);

		str_name = "LINK_SET.LIGHT.BLUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_SET_LIGHT_BLUE, str_name);

		str_name = "LINK_SET.LIGHT.WHITE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_SET_LIGHT_WHITE, str_name);

		//
		str_name = "LINK_SET.ALARM.BUZZER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_SET_ALARM_BUZZER, str_name);

		str_name = "LINK_SET.MELODY.BUZZER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_SET_MELODY_BUZZER, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.5, MON_ID__IO_MONITOR);
	}
	return 1;
}
int CObj__STD_TYPE::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

int CObj__STD_TYPE::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__STD_TYPE::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;

	CString ch_name;
	CString obj_name;
	CString var_name;


	// CHANNEL LINK...
	{
		def_name = "CH.LIGHT.RED.ON_OFF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LIGHT_RED__ON_OFF, obj_name,var_name);

		def_name = "CH.LIGHT.YELLOW.ON_OFF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LIGHT_YELLOW__ON_OFF, obj_name,var_name);

		def_name = "CH.LIGHT.GREEN.ON_OFF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LIGHT_GREEN__ON_OFF, obj_name,var_name);

		def_name = "CH.LIGHT.BLUE.ON_OFF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LIGHT_BLUE__ON_OFF, obj_name,var_name);

		def_name = "CH.LIGHT.WHITE.ON_OFF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LIGHT_WHITE__ON_OFF, obj_name,var_name);

		//
		def_name = "CH.LIGHT.RED.BLINK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LIGHT_RED__BLINK, obj_name,var_name);

		def_name = "CH.LIGHT.YELLOW.BLINK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LIGHT_YELLOW__BLINK, obj_name,var_name);

		def_name = "CH.LIGHT.GREEN.BLINK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LIGHT_GREEN__BLINK, obj_name,var_name);

		def_name = "CH.LIGHT.BLUE.BLINK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LIGHT_BLUE__BLINK, obj_name,var_name);

		def_name = "CH.LIGHT.WHITE.BLINK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LIGHT_WHITE__BLINK, obj_name,var_name);

		//
		def_name = "CH.ALARM.BUZZER";			// Buzzer On !!
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__ALARM_BUZZER, obj_name,var_name);

		def_name = "CH.ALARM.BUZZER.RESET";		// Buzzer Off !!
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__ALARM_BUZZER_RESET, obj_name,var_name);

		//
		for(int i=0; i<CFG_MELODY_MAX; i++)
		{
			def_name.Format("CH.MELODY%d.CTRL", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__MELODY[i], obj_name,var_name);
		}
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
int CObj__STD_TYPE::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	// ...
	{
		CString log_msg;

		log_msg.Format("Start ... :  [%s]", mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	int flag = -1;

	// ...
	{
		// LIGHT RED -----
		     IF__CTRL_MODE(sMODE__RED_ON)					flag = Call__RED_ON();
		ELSE_IF__CTRL_MODE(sMODE__RED_OFF)					flag = Call__RED_OFF();
		ELSE_IF__CTRL_MODE(sMODE__RED_BLINK)				flag = Call__RED_BLINK();

		// LIGHT YELLOW -----
		ELSE_IF__CTRL_MODE(sMODE__YELLOW_ON)				flag = Call__YELLOW_ON();
		ELSE_IF__CTRL_MODE(sMODE__YELLOW_OFF)				flag = Call__YELLOW_OFF();
		ELSE_IF__CTRL_MODE(sMODE__YELLOW_BLINK)				flag = Call__YELLOW_BLINK();

		// LIGHT GREEN -----
		ELSE_IF__CTRL_MODE(sMODE__GREEN_ON)					flag = Call__GREEN_ON();
		ELSE_IF__CTRL_MODE(sMODE__GREEN_OFF)				flag = Call__GREEN_OFF();
		ELSE_IF__CTRL_MODE(sMODE__GREEN_BLINK)				flag = Call__GREEN_BLINK();

		// LIGHT BLUE -----
		ELSE_IF__CTRL_MODE(sMODE__BLUE_ON)					flag = Call__BLUE_ON();
		ELSE_IF__CTRL_MODE(sMODE__BLUE_OFF)					flag = Call__BLUE_OFF();
		ELSE_IF__CTRL_MODE(sMODE__BLUE_BLINK)				flag = Call__BLUE_BLINK();

		// LIGHT WHITE -----
		ELSE_IF__CTRL_MODE(sMODE__WHITE_ON)					flag = Call__WHITE_ON();
		ELSE_IF__CTRL_MODE(sMODE__WHITE_OFF)				flag = Call__WHITE_OFF();
		ELSE_IF__CTRL_MODE(sMODE__WHITE_BLINK)				flag = Call__WHITE_BLINK();

		// ALARM BUZZER -----
		ELSE_IF__CTRL_MODE(sMODE__ALARM_BUZZER_ON)			flag = Call__ALARM_BUZZER_ON();
		ELSE_IF__CTRL_MODE(sMODE__ALARM_BUZZER_OFF)			flag = Call__ALARM_BUZZER_OFF();
		ELSE_IF__CTRL_MODE(sMODE__ALARM_BUZZER_RESET_ON)	flag = Call__ALARM_BUZZER_RESET_ON();
		ELSE_IF__CTRL_MODE(sMODE__ALARM_BUZZER_RESET_OFF)	flag = Call__ALARM_BUZZER_RESET_OFF();

		// MELODY -----
		ELSE_IF__CTRL_MODE(sMODE__MELODY_ON)				flag = Call__MELODY_ON();
		ELSE_IF__CTRL_MODE(sMODE__MELODY_OFF)				flag = Call__MELODY_OFF();
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;

		log_msg.Format("Aborted ... :  [%s]", mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		CString log_msg;

		log_msg.Format("Completed ... :  [%s]", mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__STD_TYPE::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable,p_alarm);
			break;
	}
	return 1;
}
