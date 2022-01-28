#pragma once

#include "Interface_Code.h"

#include "Ccommon_Error.h"
#include "CCommon_System.h"


class CObj__TwoManiFold_TM : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//-------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;


	//-------------------------------------------------------------------------
	// INTERNAL PROPERTY

	CX__VAR_ANALOG_CTRL  aCH__CFG_PUMP_VALVE_CLOSE_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_VENT_VALVE_CLOSE_TIMEOUT;


	//-------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	// I/O OBJECT -----
	// TMC_CHM -----
	CX__VAR_DIGITAL_CTRL doEXT_CH__TMC_CHM__FAST_PUMP_VLV__SET;
	CX__VAR_DIGITAL_CTRL doEXT_CH__TMC_CHM__FAST_VENT_VLV__SET;


	//------------------------------------------------------------------------------
	// ALL : PUMP VLV CLOSE -----
	CString sMODE__ALL_PUMP_VLV_CLOSE;
	int  Call__ALL_PUMP_VLV_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// TMC_CHM : PUMP VLV OPEN -----
	CString sMODE__TMC_CHM_PUMP_VLV_OPEN;
	int  Call__TMC_CHM_PUMP_VLV_OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// TMC_CHM -----
	// VAC_VLV_OPEN 
	CString sMODE__TMC_CHM_VAC_VLV_OPEN;
	int  Call__TMC_CHM_VLV_OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// VAC_VLV_CLOSE
	CString sMODE__TMC_CHM_VAC_VLV_CLOSE;
	int  Call__TMC_CHM_VLV_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// TMC_CHM_ALL_CLOSE
	CString sMODE__TMC_CHM__VLV_ALL_CLOSE;
	int  Call__TMC_CHM_VLV_ALL_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);



	//------------------------------------------------------------------------------
	// TMC_CHM -----
	int  Fnc__TMC_CHM__PUMP_VLV_CLOSE();
	int  Fnc__TMC_CHM__PUMP_VLV_OPEN(const int close_flag);

	int  Fnc__TMC_CHM__VENT_VLV_CLOSE();
	int  Check__TMC_CHM__VENT_VLV_CLOSE();

	// ...
	void Fnc__PUMP_VLV_CLOSE_DELAY();
	void Fnc__VENT_VLV_CLOSE_DELAY();


public:
	CObj__TwoManiFold_TM();
	~CObj__TwoManiFold_TM();

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
