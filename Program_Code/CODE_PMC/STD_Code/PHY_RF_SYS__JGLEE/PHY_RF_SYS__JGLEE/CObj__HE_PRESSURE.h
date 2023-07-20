#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__HE_PRESSURE__DEF.h"


class CObj__HE_PRESSURE : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	SCX__USER_LOG_CTRL xI_LOG_CTRL;

	int iActive__SIM_MODE;
	//


	//-------------------------------------------------------------------------
	// INTERNAL PROPERTY

	// OBJ ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// PARA ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_PRESSURE_SET_X[_CFG__ZONE_SIZE];

	// USER ...
	CX__VAR_ANALOG_CTRL  aCH__USER_IO_PRESSURE_SET_X[_CFG__ZONE_SIZE];

	// MON ...
	CX__VAR_ANALOG_CTRL  aCH__MON_IO_PRESSURE_SET_X[_CFG__ZONE_SIZE];

	CX__VAR_STRING_CTRL  sCH__MON_IO_STATUS_X[_CFG__ZONE_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__MON_IO_PRESSURE_GET_X[_CFG__ZONE_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__MON_IO_FLOW_X[_CFG__ZONE_SIZE];
	//

	//-------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	// Zone.Size ...
	int iZONE_SIZE;

	// Input.HEXA ...
	CX__VAR_STRING_CTRL  siEXT_CH__STATE_HEXA_X[_CFG__ZONE_SIZE];
	CX__VAR_STRING_CTRL  siEXT_CH__PRESSURE_HEXA_X[_CFG__ZONE_SIZE];
	CX__VAR_STRING_CTRL  siEXT_CH__FLOW_HEXA_X[_CFG__ZONE_SIZE];

	// Output.HEXA ...
	CX__VAR_STRING_CTRL  soEXT_CH__PRESSURE_HEXA_X[_CFG__ZONE_SIZE];
	//


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__CLOSE;
	int Call__CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__PRESSURE_SET;
	int Call__PRESSURE_SET(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	int Fnc__PRESSURE_SET(const int zone_index, const double set_pressure);

	// ...
	int Mon__STATUS(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//


public:
	CObj__HE_PRESSURE();
	~CObj__HE_PRESSURE();

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
