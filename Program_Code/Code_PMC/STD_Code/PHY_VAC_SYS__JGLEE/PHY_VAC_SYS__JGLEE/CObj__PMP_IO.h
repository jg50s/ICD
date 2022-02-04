#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Def.h"


#define _PMP_CTRL_TYPE__MANUAL				1
#define _PMP_CTRL_TYPE__OBJECT				2
#define _PMP_CTRL_TYPE__IO					3


class CObj__PMP_IO : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;
	
	// ...
	SCX__USER_LOG_CTRL xI_LOG_CTRL;
	//
	
	//-------------------------------------------------------------------------
	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_COMM_STATE;
	CX__VAR_DIGITAL_CTRL dCH__MON_PUMP_POWER_SNS;
	CX__VAR_DIGITAL_CTRL dCH__MON_VAC_ON_SNS;

	// CFG ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_PUMP_PRESSURE_HIGH_LIMIT;
	//

	//-------------------------------------------------------------------------
	int iPUMP__CTRL_TYPE;

	// OBJ.TYPE
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__PUMP;

	// IO.TYPE 
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_PUMP_SET;

	//
	bool bActive__DI_PUMP_POWER_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_PUMP_POWER_SNS;

	bool bActive__DI_PUMP_VAC_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_PUMP_VAC_SNS;

	bool bActive__AI_PUMP_PRESSURE_TORR;
	CX__VAR_ANALOG_CTRL  aEXT_CH__AI_PUMP_PRESSURE_TORR;
	//
	
	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PUMP_ON;
	int Call__PUMP_ON(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PUMP_OFF;
	int Call__PUMP_OFF(CII_OBJECT__VARIABLE *p_variable);

	// ...
	void Fnc__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//

public:
	CObj__PMP_IO();
	~CObj__PMP_IO();

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
