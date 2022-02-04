#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


class CObj__RF_IO : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	SCX__USER_LOG_CTRL xI_LOG_CTRL;
	int iSIM_MODE;


	//-------------------------------------------------------------------------
	CX__VAR_STRING_CTRL   sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL   sCH__OBJ_STATUS;
	
	CX__VAR_STRING_CTRL   sCH__OBJ_ONLINE;
	CX__VAR_STRING_CTRL   sCH__OBJ_CTRL_MODE;

	CX__VAR_ANALOG_CTRL   aCH__PARA_POWER_SET;

	CX__VAR_STRING_CTRL   sCH__MON_POWER_ON_SET;
	CX__VAR_STRING_CTRL   sCH__MON_POWER_ON_SNS;
	CX__VAR_STRING_CTRL   sCH__MON_OVERTEMP_SNS;

	CX__VAR_STRING_CTRL   sCH__MON_POWER_SET;
	CX__VAR_STRING_CTRL   sCH__MON_FORWARD_POWER;
	CX__VAR_STRING_CTRL   sCH__MON_REFLECT_POWER;


	//-------------------------------------------------------------------------
	CX__VAR_DIGITAL_CTRL  dEXT_CH__DO_SOURCE_ON;
	CX__VAR_ANALOG_CTRL   aEXT_CH__AO_SOURCE_POWER;

	CX__VAR_DIGITAL_CTRL  dEXT_CH__DI_SOURCE_ON;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__DI_SOURCE_OVERTEMP_ALARM;

	CX__VAR_ANALOG_CTRL   aEXT_CH__AI_FORWARD_POWER;
	CX__VAR_ANALOG_CTRL   aEXT_CH__AI_REFLECT_POWER;


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__OFF;
	int Call__OFF(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__SET_POWER;
	int Call__SET_POWER(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	int Mon__STATUS(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//


public:
	CObj__RF_IO();
	~CObj__RF_IO();

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
