#pragma once

#include "Interface_Code.h"

#include "Ccommon_Error.h"
#include "CCommon_System.h"


class CObj__OneManiFold_LL : public __IOBJ__STD_TYPE
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

	// LLx ...
	CX__VAR_DIGITAL_CTRL doEXT_CH__LLx__SOFT_PUMP_VLV__SET;
	CX__VAR_DIGITAL_CTRL doEXT_CH__LLx__FAST_PUMP_VLV__SET;

	CX__VAR_DIGITAL_CTRL doEXT_CH__LLx__SOFT_VENT_VLV__SET;
	CX__VAR_DIGITAL_CTRL doEXT_CH__LLx__FAST_VENT_VLV__SET;
	//


	//------------------------------------------------------------------------------
	CString sMODE__ALL_PUMP_VLV_CLOSE;
	int  Call__ALL_PUMP_VLV_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__LLx_PUMP_VLV_OPEN;
	int  Call__LLx_PUMP_VLV_OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__LLx_VAC_VLV_OPEN;
	int  Call__LLx_VLV_OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__LLx_VAC_VLV_CLOSE;
	int  Call__LLx_VLV_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__LLx_VLV_ALL_CLOSE;
	int  Call__LLx_VLV_ALL_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// LLx ...
	int  Fnc__LLx__PUMP_VLV_CLOSE();
	int  Fnc__LLx__PUMP_VLV_OPEN(const int close_flag);

	int  Fnc__LLx__VENT_VLV_CLOSE();
	int  Check__LLx__VENT_VLV_CLOSE();

	void Fnc__PUMP_VLV_CLOSE_DELAY();
	void Fnc__VENT_VLV_CLOSE_DELAY();
	//


public:
	CObj__OneManiFold_LL();
	~CObj__OneManiFold_LL();

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
