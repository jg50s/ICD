#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"


class CObj__STD_TYPE : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//-------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;


	//-------------------------------------------------------------------------
	// INTERNAL PROPERTY

	// CONFIG ...
	CX__VAR_DIGITAL_CTRL dCH__IO_MONITOR__ACTIVE_FLAG;
	CX__VAR_ANALOG_CTRL  aCH__CFG_BLINK_PERIOD_SEC;
	CX__VAR_DIGITAL_CTRL dCH__CFG_BLINK_MODE_USE;

	// LINK REMOTE ...
	CX__VAR_DIGITAL_CTRL dCH__LIGHT_RED;
	CX__VAR_DIGITAL_CTRL dCH__LIGHT_YELLOW;
	CX__VAR_DIGITAL_CTRL dCH__LIGHT_GREEN;
	CX__VAR_DIGITAL_CTRL dCH__LIGHT_BLUE;
	CX__VAR_DIGITAL_CTRL dCH__LIGHT_WHITE;

	CX__VAR_DIGITAL_CTRL dCH__CFG_BUZZER_USE;
	CX__VAR_DIGITAL_CTRL dCH__ALARM_BUZZER;

	CX__VAR_DIGITAL_CTRL dCH__CFG_MELODY_USE;
	CX__VAR_DIGITAL_CTRL dCH__CFG_MELODY_NUM;
	CX__VAR_DIGITAL_CTRL dCH__MELODY_BUZZER;

	// LINK LOCAL ...
	CX__VAR_DIGITAL_CTRL dCH__LINK_LOCAL_LIGHT_RED;
	CX__VAR_DIGITAL_CTRL dCH__LINK_LOCAL_LIGHT_YELLOW;
	CX__VAR_DIGITAL_CTRL dCH__LINK_LOCAL_LIGHT_GREEN;
	CX__VAR_DIGITAL_CTRL dCH__LINK_LOCAL_LIGHT_BLUE;
	CX__VAR_DIGITAL_CTRL dCH__LINK_LOCAL_LIGHT_WHITE;

	CX__VAR_DIGITAL_CTRL dCH__LINK_LOCAL_ALARM_BUZZER;
	CX__VAR_DIGITAL_CTRL dCH__LINK_LOCAL_MELODY_BUZZER;

	// LINK SET ...
	CX__VAR_STRING_CTRL  sCH__LINK_SET_LIGHT_RED;
	CX__VAR_STRING_CTRL  sCH__LINK_SET_LIGHT_YELLOW;
	CX__VAR_STRING_CTRL  sCH__LINK_SET_LIGHT_GREEN;
	CX__VAR_STRING_CTRL  sCH__LINK_SET_LIGHT_BLUE;
	CX__VAR_STRING_CTRL  sCH__LINK_SET_LIGHT_WHITE;

	CX__VAR_STRING_CTRL  sCH__LINK_SET_ALARM_BUZZER;
	CX__VAR_STRING_CTRL  sCH__LINK_SET_MELODY_BUZZER;
	//

	//-------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	// LIGHT : ON_OFF ...
	bool bActive__LIGHT_RED__ON_OFF;
	CX__VAR_DIGITAL_CTRL doEXT_CH__LIGHT_RED__ON_OFF;

	bool bActive__LIGHT_YELLOW__ON_OFF;
	CX__VAR_DIGITAL_CTRL doEXT_CH__LIGHT_YELLOW__ON_OFF;

	bool bActive__LIGHT_GREEN__ON_OFF;
	CX__VAR_DIGITAL_CTRL doEXT_CH__LIGHT_GREEN__ON_OFF;

	bool bActive__LIGHT_BLUE__ON_OFF;
	CX__VAR_DIGITAL_CTRL doEXT_CH__LIGHT_BLUE__ON_OFF;

	bool bActive__LIGHT_WHITE__ON_OFF;
	CX__VAR_DIGITAL_CTRL doEXT_CH__LIGHT_WHITE__ON_OFF;

	// LIGHT : BLINK ...
	bool bActive__LIGHT_RED__BLINK;
	CX__VAR_DIGITAL_CTRL doEXT_CH__LIGHT_RED__BLINK;

	bool bActive__LIGHT_YELLOW__BLINK;
	CX__VAR_DIGITAL_CTRL doEXT_CH__LIGHT_YELLOW__BLINK;

	bool bActive__LIGHT_GREEN__BLINK;
	CX__VAR_DIGITAL_CTRL doEXT_CH__LIGHT_GREEN__BLINK;

	bool bActive__LIGHT_BLUE__BLINK;
	CX__VAR_DIGITAL_CTRL doEXT_CH__LIGHT_BLUE__BLINK;

	bool bActive__LIGHT_WHITE__BLINK;
	CX__VAR_DIGITAL_CTRL doEXT_CH__LIGHT_WHITE__BLINK;

	// ALARM_BUZZER ...
	bool bActive__ALARM_BUZZER_SET;
	CX__VAR_DIGITAL_CTRL doEXT_CH__ALARM_BUZZER_SET;

	bool bActive__ALARM_BUZZER_RESET;
	CX__VAR_DIGITAL_CTRL doEXT_CH__ALARM_BUZZER_RESET;

	// MELODY ...
	int iSIZE_MELODY;
	CX__VAR_DIGITAL_CTRL doEXT_CH__MELODY[CFG_MELODY_MAX];
	//


	//------------------------------------------------------------------------------
	// LIGHT RED -----
	CString sMODE__RED_ON;
	int  Call__RED_ON();

	CString sMODE__RED_OFF;
	int  Call__RED_OFF();

	CString sMODE__RED_BLINK;
	int  Call__RED_BLINK();
	//

	// LIGHT YELLOW -----
	CString sMODE__YELLOW_ON;
	int  Call__YELLOW_ON();

	CString sMODE__YELLOW_OFF;
	int  Call__YELLOW_OFF();

	CString sMODE__YELLOW_BLINK;
	int  Call__YELLOW_BLINK();
	//

	// LIGHT GREEN -----
	CString sMODE__GREEN_ON;
	int  Call__GREEN_ON();

	CString sMODE__GREEN_OFF;
	int  Call__GREEN_OFF();

	CString sMODE__GREEN_BLINK;
	int  Call__GREEN_BLINK();
	//

	// LIGHT BLUE -----
	CString sMODE__BLUE_ON;
	int  Call__BLUE_ON();

	CString sMODE__BLUE_OFF;
	int  Call__BLUE_OFF();

	CString sMODE__BLUE_BLINK;
	int  Call__BLUE_BLINK();
	//

	// WHITE BLUE -----
	CString sMODE__WHITE_ON;
	int  Call__WHITE_ON();

	CString sMODE__WHITE_OFF;
	int  Call__WHITE_OFF();

	CString sMODE__WHITE_BLINK;
	int  Call__WHITE_BLINK();

	// ALARM BUZZER -----
	CString sMODE__ALARM_BUZZER_ON;
	int  Call__ALARM_BUZZER_ON();
	int  Is__ALARM_BUZZER_ON();

	CString sMODE__ALARM_BUZZER_OFF;
	int  Call__ALARM_BUZZER_OFF();

	CString sMODE__ALARM_BUZZER_RESET_ON;
	int  Call__ALARM_BUZZER_RESET_ON();
	int  Is__ALARM_BUZZER_RESET_ON();

	CString sMODE__ALARM_BUZZER_RESET_OFF;
	int  Call__ALARM_BUZZER_RESET_OFF();
	//

	// MDLODY -----
	CString sMODE__MELODY_ON;
	int  Call__MELODY_ON();

	CString sMODE__MELODY_OFF;
	int  Call__MELODY_OFF();

	// ...
	int Seq__SET_BUZZER_ON();
	int Seq__SET_BUZZER_OFF();
	//

	//------------------------------------------------------------------------------
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	bool Check__DEF(const CString& def_data);
	//


public:
	CObj__STD_TYPE();
	~CObj__STD_TYPE();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);
	
	int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
