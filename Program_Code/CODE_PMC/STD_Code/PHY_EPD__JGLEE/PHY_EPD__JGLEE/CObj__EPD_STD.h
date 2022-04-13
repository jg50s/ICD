#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__EPD_STD__ALID.h"
#include "CObj__EPD_STD__DEF.h"


class CObj__EPD_STD : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xLOG_CTRL;

	int iActive__SIM_MODE;
	//

	//-------------------------------------------------------------------
	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	//
	CX__VAR_DIGITAL_CTRL dCH__CFG_EPD_MODE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_EPD_TIMEOUT_MINIMUM;
	CX__VAR_ANALOG_CTRL  aCH__CFG_EPD_TIMEOUT_MAXIMUM;

	CX__VAR_ANALOG_CTRL  aCH__CFG_DELAY_TIME;

	//
	CX__VAR_STRING_CTRL  sCH__CFG_PARAMETER_VALUE_TO_CHANGE;
	CX__VAR_STRING_CTRL  sCH__CFG_PARAMETER_PERCENT_TO_CHANGE;
	CX__VAR_STRING_CTRL  sCH__CFG_PARAMETER_NORMALIZE_TIME;

	CX__VAR_STRING_CTRL  sCH__CFG_PARAMETER_SLOPE_COUNT;
	CX__VAR_STRING_CTRL  sCH__CFG_PARAMETER_SLOPE_DIRECTION;
	CX__VAR_STRING_CTRL  sCH__CFG_PARAMETER_VALIDATION_TIME;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH_INFO__EPD_START_FLAG;

	CX__VAR_STRING_CTRL  sCH_INFO__CUR_SEQ_MSG;
	CX__VAR_STRING_CTRL  sCH_INFO__CUR_DELAY_TIME_COUNT;
	CX__VAR_STRING_CTRL  sCH_INFO__CUR_NORMALIZE_TIME_COUNT;
	CX__VAR_STRING_CTRL  sCH_INFO__CUR_EPD_TIME_COUNT;
	CX__VAR_STRING_CTRL  sCH_INFO__CUR_NORMALIZE_VALUE;
	CX__VAR_STRING_CTRL  sCH_INFO__CUR_THRESHOLD_VALUE;
	CX__VAR_STRING_CTRL  sCH_INFO__CUR_CAL_SLOPE_COUNT;
	CX__VAR_STRING_CTRL  sCH_INFO__CUR_IBx_LIST;
	CX__VAR_STRING_CTRL  sCH_INFO__CUR_IBx_DATA;

	CX__VAR_STRING_CTRL  sCH_INFO__CUR_EPD_START_SEC;

	//
	CX__VAR_STRING_CTRL  sCH__EPD_EXCEPTION_REQ;		// ABORT END

	// External Valve IO .....
	CII_EXT_OBJECT__CTRL *pOBJ__OES_CTRL;
	
	CX__VAR_ANALOG_CTRL  aEXT_CH__EPD_SIGNAL;
	CX__VAR_ANALOG_CTRL  aEXT_CH__IBx_SPEC_DATA[MAX__IBx_SPEC_DATA];
	//

	//-------------------------------------------------------------------
	// ...
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__EPD_DETECT;
	int Call__EPD_DETECT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	int Fnc__EPD_DETECT__ValueChange(CII_OBJECT__VARIABLE *p_variable,
									 CII_OBJECT__ALARM *p_alarm);
	int Fnc__EPD_DETECT__PercentChange(CII_OBJECT__VARIABLE *p_variable,
									   CII_OBJECT__ALARM *p_alarm);

	int Fnc__EPD_DETECT__CheckDelayTime(CII_OBJECT__VARIABLE *p_variable);
	int Fnc__EPD_DETECT__CheckNormalizeTime(CII_OBJECT__VARIABLE *p_variable);

	int Fnc__EPD_DETECT__CheckValueChange(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Fnc__EPD_DETECT__CheckPercentChange(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Fnc__EPD_DETECT__CheckSlope(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	int  Alarm_Post__EPD_MAX_TIMEOUT(CII_OBJECT__ALARM* p_alarm,const CString& alarm_msg);
	int  Alarm_Post__EPD_MIN_TIMEOUT(CII_OBJECT__ALARM* p_alarm,const CString& alarm_msg);

	int	 Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id);
	void Alarm__POST_CHECK(CII_OBJECT__ALARM *p_alarm, CString msg, const int alarm_id);

	// ...
	double Get__IBx_SPEC_DATA();
	double Get__EPD_CUR_SEC();

	// ...
	void Fnc__WRITE_LOG(const CString& log_msg);
	//
	

public:
	CObj__EPD_STD();
	~CObj__EPD_STD();
	
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
