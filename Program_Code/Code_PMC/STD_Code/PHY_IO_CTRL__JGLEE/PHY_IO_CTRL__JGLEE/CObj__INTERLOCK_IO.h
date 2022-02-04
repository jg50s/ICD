#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__INTERLOCK_IO__ALID.h"
#include "CObj__INTERLOCK_IO__DEF.h"


class CObj__INTERLOCK_IO : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	SCX__USER_LOG_CTRL xI_LOG_CTRL;
	int iActive__SIM_MODE;
	

	//-------------------------------------------------------------------------
	CX__VAR_STRING_CTRL sCH__OBJ_MSG;


	//-------------------------------------------------------------------------
	// OBJ : DB_SYS ...
	
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_INTERLOCK_USE_MODE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_INTERLOCK_USE__INTERLOCK_SNS_ALL;
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_INTERLOCK_CHECK_SEC;

	//
	CX__VAR_DIGITAL_CTRL dEXT_CH__INTERLOCK_HEAVY_ACTIVE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__INTERLOCK_LIGHT_ACTIVE;

	CX__VAR_STRING_CTRL  sEXT_CH__INTERLOCK_HEAVY_MESSAGE;
	CX__VAR_STRING_CTRL  sEXT_CH__INTERLOCK_LIGHT_MESSAGE;

	//
	int iSIZE__INTERLOCK_SENSOR;
	
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_USE_X[DEF_SIZE__INTERLOCK_SENSOR];
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_SENSOR_X[DEF_SIZE__INTERLOCK_SENSOR];

	CString sDATA__NORMAL_STATE_X[DEF_SIZE__INTERLOCK_SENSOR];
	CString sDATA__ERROR_MSG_X[DEF_SIZE__INTERLOCK_SENSOR];
	int iDATA__ERROR_LEVEL_X[DEF_SIZE__INTERLOCK_SENSOR];
	//


	//-------------------------------------------------------------------------
	// ...
	int Mon__INTERLOCK_SENSOR(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//


public:
	CObj__INTERLOCK_IO();
	~CObj__INTERLOCK_IO();

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
