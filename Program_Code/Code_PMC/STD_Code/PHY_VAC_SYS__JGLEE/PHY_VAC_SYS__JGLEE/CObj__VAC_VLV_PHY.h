#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Def.h"


class CObj__VAC_VLV_PHY : public __IOBJ__STD_TYPE
{
private:
	//------------------------------------------------------------
	CString	sObject_Name;

	// ...
	SCX__USER_LOG_CTRL xI_LOG_CTRL;
	//

	//------------------------------------------------------------
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	CX__VAR_STRING_CTRL  sCH__MON_PUMPING_STATE;

	CX__VAR_DIGITAL_CTRL dCH__CFG_USE_SR_OPEN_SNS;
	CX__VAR_DIGITAL_CTRL dCH__CFG_USE_SR_CLOSE_SNS;

	CX__VAR_DIGITAL_CTRL dCH__CFG_USE_FR_OPEN_SNS;
	CX__VAR_DIGITAL_CTRL dCH__CFG_USE_FR_CLOSE_SNS;

	CX__VAR_ANALOG_CTRL  aCH__CFG_USE_SR_OPEN_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_USE_SR_CLOSE_TIMEOUT;

	CX__VAR_ANALOG_CTRL  aCH__CFG_USE_FR_OPEN_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_USE_FR_CLOSE_TIMEOUT;

	//------------------------------------------------------------
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_SR_VALVE_CTRL;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_FR_VALVE_CTRL;

	bool bActive__DO_EXHAUST_VALVE_CTRL;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_EXHAUST_VALVE_CTRL;

	//
	bool bActive__DI_SR_OPEN_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_SR_OPEN_SNS;

	bool bActive__DI_SR_CLOSE_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_SR_CLOSE_SNS;

	//
	bool bActive__DI_FR_OPEN_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_FR_OPEN_SNS;

	bool bActive__DI_FR_CLOSE_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_FR_CLOSE_SNS;

	//
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_DRY_PMP_PWR_SNS;
	//

	//------------------------------------------------------------
	CString sMODE__ALL_CLOSE;
	int Call__ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__SR_OPEN;
	int Call__SR_OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__SR_CLOSE;
	int Call__SR_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__FR_OPEN;
	int Call__FR_OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__FR_CLOSE;
	int Call__FR_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__EXHAUST_OPEN;
	int Call__EXHAUST_OPEN(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__EXHAUST_CLOSE;
	int Call__EXHAUST_CLOSE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	int Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	int Check__SR_OPEN_SENSOR_TIMEOUT(CII_OBJECT__ALARM* p_alarm);
	int Check__SR_CLOSE_SENSOR_TIMEOUT(CII_OBJECT__ALARM* p_alarm);

	int Check__FR_OPEN_SENSOR_TIMEOUT(CII_OBJECT__ALARM* p_alarm);
	int Check__FR_CLOSE_SENSOR_TIMEOUT(CII_OBJECT__ALARM* p_alarm);
	//

public:
	//------------------------------------------------------------
	CObj__VAC_VLV_PHY();
	~CObj__VAC_VLV_PHY();

	//------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	//------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
