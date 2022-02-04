#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"

#include "CObj__STEP_SAMPLE__ALID.h"
#include "CObj__STEP_SAMPLE__DEF.h"


class CObj__STEP_SAMPLE : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xLOG_CTRL;
	int iActive__SIM_MODE;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// OBJ ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL  sCH__OBJ_SUB_MSG;

	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_STEP_EXCEPTION_ACT;

	// CFG ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_STEP_ALARM_TEST_ACTIVE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_STEP_STABLE_MIN_SEC;
	CX__VAR_ANALOG_CTRL  aCH__CFG_CHM_PRESSURE_HIGH_LIMIT;

	// RCP ...
	CX__VAR_STRING_CTRL  sCH__RCP_STEP_MESSAGE;		
	CX__VAR_DIGITAL_CTRL dCH__RCP_STEP_MODE;	
	CX__VAR_ANALOG_CTRL	 aCH__RCP_STEP_TIME;	

	CX__VAR_DIGITAL_CTRL dCH__RCP_APC_MODE;		
	CX__VAR_ANALOG_CTRL  aCH__RCP_APC_POSITION;		
	CX__VAR_ANALOG_CTRL  aCH__RCP_APC_PRESSURE;		
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// DB INF ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__SLOT01_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__CUR_LOTID;

	// OBJ APC ...
	int APC_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data);

	bool bActive__OBJ_CTRL__APC;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__APC;

	CX__VAR_ANALOG_CTRL	 aEXT_CH__APC_OBJ__PARA_PRESSURE;
	CX__VAR_ANALOG_CTRL	 aEXT_CH__APC_OBJ__PARA_POSITION;

	CX__VAR_STRING_CTRL  sEXT_CH__APC_OBJ__MON_PRESSURE_TORR;

	CX__VAR_DIGITAL_CTRL dEXT_CH__APC_OBJ__MON_PRESSURE_ABORT_ACTIVE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__APC_OBJ__MON_PRESSURE_STABLE_ACTIVE;
	//


	//-------------------------------------------------------------------------
	// OBJ.MODE ...

	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__READY;
	int Call__READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__START;
	int Call__START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PROC;
	int Call__PROC(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__ABORT;
	int Call__ABORT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__END;
	int Call__END(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	int Get__STEP_CTRL();
	//

public:
	CObj__STEP_SAMPLE();
	~CObj__STEP_SAMPLE();

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
