#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CObj__SYSTEM__DEF.h"


class CObj__SYSTEM : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//------------------------------------------------------------------------------
	CString sObject_Name;

	SCX__SEQ_INFO mSeq_Info;


	//------------------------------------------------------------------------------
	// INTERNAL PROPERTY


	//------------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	CX__VAR_DIGITAL_CTRL diEXT_CH__IO_DNET_COMM_STS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__IO_AIR_SNS;

	CX__VAR_ANALOG_CTRL  aCFG_FFU_DIFFERENTIAL_PRESSURE_VAL;

	CX__VAR_DIGITAL_CTRL dCFG_N2_CHECK;
	CX__VAR_DIGITAL_CTRL dCFG_CDA_CHECK;

	CX__VAR_DIGITAL_CTRL dEXT_CH__IO_N2_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__IO_EFEM_DOOR_SNS;


	//------------------------------------------------------------------------------
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	void Mon__N2_SENSOR_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	void Mon__EFEM_DOORS_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);


public:
	CObj__SYSTEM();
	~CObj__SYSTEM();

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
