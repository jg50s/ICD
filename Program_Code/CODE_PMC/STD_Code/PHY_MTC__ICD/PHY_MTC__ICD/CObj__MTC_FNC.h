#pragma once

#include "Interface_Code.h"

#include "CCommon_Def.h"


class CObj__MTC_FNC : public __IOBJ__STD_TYPE
{
private:
	//------------------------------------------------------------
	CString sObject_Name;

	// ...
	SCX__USER_LOG_CTRL xLOG_CTRL;

	int iActive__SIM_MODE;
	//

	//------------------------------------------------------------
	// INTERNAL PROPERTY

	// OBJ PARAMETER ...
	CX__VAR_STRING_CTRL	 sCH__OBJ_STATUS;
	CX__VAR_STRING_CTRL	 sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL  sCH__OBJ_TIMER;

	// MON PARAMETER ...
	CX__VAR_STRING_CTRL  sCH__MON_PUMPING_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_MTC_STATUS;

	// CFG - VENTING PARAMETER ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_VENT_PRESSURE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_ATM_VENT_PRESSURE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_VENT_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_ATM_VENT_TIMEOUT;

	// CFG - PUMPING PARAMETER ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_PUMP_PRESSURE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_VAC_PUMP_PRESSURE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_PUMP_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_VAC_PUMP_TIMEOUT;

	// CFG - GATE VLV PARAMETER ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_GATE_VLV_OPEN_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_GATE_VLV_CLOSE_TIMEOUT;

	// MTC PRESSURE GAUGE ...
	CX__VAR_ANALOG_CTRL	 aCH__MTC_PRESSURE_TORR;
	CX__VAR_STRING_CTRL	 sCH__MTC_PRESSURE_DISPLAY;

	CX__VAR_ANALOG_CTRL  aCH__MTC_PRESSURE_SIM_MODE;
	//

	//------------------------------------------------------------
	// EXTERNAL PROPERTY

	// Channel Link ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_GATE_STATE;

	// DI...
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_CHM_VAC_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_CHM_ATM_SNS;

	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_MTC_VAC_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_MTC_ATM_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_MTC_GATE_OPEN_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_MTC_GATE_CLOSE_SNS;

	// DO...
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_MTC_GATE_OPEN;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_MTC_GATE_CLOSE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_MTC_2STAGE_SLOW;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_MTC_2STAGE_FAST;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_MTC_CHECK_VV;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_MTC_N2PURGE_SLOW;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_MTC_N2PURGE_FAST;

	// SI...
	CX__VAR_STRING_CTRL  sEXT_CH__SI_MTC_GAUGE_STATUS_HEXA;
	CX__VAR_STRING_CTRL	 sEXT_CH__SI_MTC_GAUGE_PRESSURE_HEXA;
	//

	//------------------------------------------------------------
	// ...
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	int Fnc__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Fnc__ALL_VV_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	CString sMODE__MAINT;
	int Call__MAINTMODE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	CString sMODE__GATE_OPEN;
	CString sMODE__GATE_CLOSE;
	int Call__GATE_CTL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const bool bOpen);
	int Fnc__GATE_CTL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const bool bOpen);

	// ...
	CString sMODE__PUMPING;
	int Call__PUMPING(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Fnc__SOFT_PUMPING(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Fnc__FAST_PUMPING(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	CString sMODE__VENT;
	int Call__VENT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Fnc__SOFT_VENT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Fnc__FAST_VENT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// MON Function .....
	void Mon__PRESSURE_STATUS(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	//

public:
	CObj__MTC_FNC();
	~CObj__MTC_FNC();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
