#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


#define  ALID__OBJECT_MODE_UNKNOWN					11


class CObj_Mng__SIGNAL_TOWER_EX : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;

	// ...
	SCX__CTC__SCH_MATERIAL_CTRL xSCH_MATERIAL_CTRL;
	int iPROCESS_PRE_FLAG;

	// ...
	SCX__ASYNC_TIMER_CTRL xTIMER_CTRL;
	CX__VAR_STRING_CTRL   xCH__PROCESS_END_TIME;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// RED -----
	CX__VAR_DIGITAL_CTRL xCH_CFG__RED_DEFAULT_LIGHT_COLOR;
	
	CX__VAR_DIGITAL_CTRL xCH_CFG__RED_STATUS1_LIGHT_COLOR;
	CX__VAR_DIGITAL_CTRL xCH_CFG__RED_STATUS2_LIGHT_COLOR;
	CX__VAR_DIGITAL_CTRL xCH_CFG__RED_STATUS3_LIGHT_COLOR;

	// AMBER -----
	CX__VAR_DIGITAL_CTRL xCH_CFG__AMBER_DEFAULT_LIGHT_COLOR;

	CX__VAR_DIGITAL_CTRL xCH_CFG__AMBER_STATUS1_LIGHT_COLOR;
	CX__VAR_DIGITAL_CTRL xCH_CFG__AMBER_STATUS2_LIGHT_COLOR;
	CX__VAR_DIGITAL_CTRL xCH_CFG__AMBER_STATUS3_LIGHT_COLOR;
	CX__VAR_DIGITAL_CTRL xCH_CFG__AMBER_STATUS4_LIGHT_COLOR;

	// GRREN -----
	CX__VAR_DIGITAL_CTRL xCH_CFG__GREEN_DEFAULT_LIGHT_COLOR;

	CX__VAR_DIGITAL_CTRL xCH_CFG__GREEN_STATUS1_LIGHT_COLOR;
	CX__VAR_DIGITAL_CTRL xCH_CFG__GREEN_STATUS2_LIGHT_COLOR;
	CX__VAR_DIGITAL_CTRL xCH_CFG__GREEN_STATUS3_LIGHT_COLOR;

	// BLUE -----
	CX__VAR_DIGITAL_CTRL xCH_CFG__BLUE_DEFAULT_LIGHT_COLOR;
	
	CX__VAR_DIGITAL_CTRL xCH_CFG__BLUE_STATUS1_LIGHT_COLOR;
	CX__VAR_DIGITAL_CTRL xCH_CFG__BLUE_STATUS2_LIGHT_COLOR;
	CX__VAR_DIGITAL_CTRL xCH_CFG__BLUE_STATUS3_LIGHT_COLOR;

	// ...
	CX__VAR_DIGITAL_CTRL xCH__LIGHT_RED;
	CX__VAR_DIGITAL_CTRL xCH__LIGHT_YELLOW;
	CX__VAR_DIGITAL_CTRL xCH__LIGHT_GREEN;
	CX__VAR_DIGITAL_CTRL xCH__LIGHT_BLUE;

	CX__VAR_DIGITAL_CTRL xCH__MELODY_BUZZER;
	CX__VAR_DIGITAL_CTRL xCH__MELODY_CTRL;

	// ...
	CX__VAR_STRING_CTRL  xCH__RED_STS;
	CX__VAR_STRING_CTRL  xCH__YELLOW_STS;
	CX__VAR_STRING_CTRL  xCH__GREEN_STS;
	CX__VAR_STRING_CTRL  xCH__BLUE_STS;
	//

	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	//


	//-------------------------------------------------------------------------
	int Mon__SIGNAL_TOWER_CTRL(CII_OBJECT__VARIABLE *p_variable);

	// Alarm & Maint
	int Check__ALARM_Or_MAINT();

	// Cassette Status
	int Check__LOAD_REQ_Or_UNLOAD_REQ();

	// Process & Idle 
	int Check__PROCESS_Or_IDLE();

	// Control State
	int Check__FA_STATUS();

	// ...
	int Fnc__Control_Light_Color(const CString& status);
	int Fnc__Set_Off_Light_Color(const CString& status);
	//


public:
	CObj_Mng__SIGNAL_TOWER_EX();
	~CObj_Mng__SIGNAL_TOWER_EX();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
