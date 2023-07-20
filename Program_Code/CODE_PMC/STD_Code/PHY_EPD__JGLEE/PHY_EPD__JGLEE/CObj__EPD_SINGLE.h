#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__EPD_SINGLE__ALID.h"
#include "CObj__EPD_SINGLE__DEF.h"

#include "CClass__Error_Timer.h"
#include "CClass__EPD_CHART.h"


class CObj__EPD_SINGLE : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xLOG_CTRL;
	int iActive__SIM_MODE;

	CUIntArray iLIST_ALID__EPD;

	// ...
	CClass__EPD_CHART mEPD_CHART;
	//

	//-------------------------------------------------------------------
	// OBJ ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// PARA ...
	CX__VAR_DIGITAL_CTRL dCH__PARA_EPD_MODE;

	CX__VAR_STRING_CTRL  sCH__PARA_VALUE_TO_CHANGE;
	CX__VAR_STRING_CTRL  sCH__PARA_PERCENT_TO_CHANGE;

	CX__VAR_ANALOG_CTRL  aCH__PARA_DELAY_TIME;
	CX__VAR_STRING_CTRL  sCH__PARA_NORMALIZE_TIME;

	CX__VAR_ANALOG_CTRL  aCH__PARA_EPD_TIMEOUT_MINIMUM;
	CX__VAR_ANALOG_CTRL  aCH__PARA_EPD_TIMEOUT_MAXIMUM;

	CX__VAR_STRING_CTRL  sCH__PARA_EPD_THRESHOLD_MIN;
	CX__VAR_STRING_CTRL  sCH__PARA_EPD_THRESHOLD_MAX;

	CX__VAR_STRING_CTRL  sCH__PARA_SLOPE_COUNT;
	CX__VAR_STRING_CTRL  sCH__PARA_SLOPE_DIRECTION;
	CX__VAR_STRING_CTRL  sCH__PARA_VALID_TIME;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH_INFO__EPD_START_FLAG;
	CX__VAR_DIGITAL_CTRL dCH_INFO__EPD_CHECK_ACTIVE;

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

	CX__VAR_STRING_CTRL  sCH__EPD_EXCEPTION_REQ;		// ABORT END

	// CFG : SYSTEM ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_USE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_INTENSITY_MIN_VALUE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_INTENSITY_MAX_VALUE;
	CX__VAR_STRING_CTRL  sCH__INFO_INTENSITY_MAX_MINUS;

	CX__VAR_ANALOG_CTRL  aCH__CFG_INTENSITY_DEC_VALUE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_INTENSITY_STABLE_DELAY_TIME;
	CX__VAR_ANALOG_CTRL  aCH__CFG_INTENSITY_STABLE_CHECK_TIME;
	CX__VAR_ANALOG_CTRL  aCH__CFG_INTENSITY_ERROR_TIMEOUT;

	// MON : STABLE_IDLE ...
	CX__VAR_DIGITAL_CTRL dCH__MON_PART_ERROR_ACTIVE;

	CX__VAR_DIGITAL_CTRL dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE;
	CX__VAR_DIGITAL_CTRL dCH__MON_IDLE_INTENSITY_STABLE_ACTIVE;
	CX__VAR_DIGITAL_CTRL dCH__MON_IDLE_INTENSITY_ERROR_ACTIVE;

	CX__VAR_STRING_CTRL  sCH__MON_IDLE_INTENSITY_STABLE_DELAY_TIME;

	CX__VAR_STRING_CTRL  sCH__MON_IDLE_INTENSITY_STABLE_MIN;
	CX__VAR_STRING_CTRL  sCH__MON_IDLE_INTENSITY_STABLE_MAX;
	
	CX__VAR_STRING_CTRL  sCH__MON_IDLE_INTENSITY_STABLE_CHECK_TIME;
	CX__VAR_STRING_CTRL  sCH__MON_IDLE_INTENSITY_ERROR_CHECK_TIME;

	// CHART ...
	CX__VAR_STRING_CTRL  sCH__CHART_DATE_TIME;
	CX__VAR_STRING_CTRL  sCH__CHART_TIME_COUNT;
	CX__VAR_STRING_CTRL  sCH__CHART_TEST_INFO;

	CX__VAR_STRING_CTRL  sCH__CHART_EPD;
	CX__VAR_STRING_CTRL  sCH__CHART_INTENSITY_X[_CFG__CHART_INTENSITY];

	CX__VAR_STRING_CTRL  sCH__REPORT_EPD_RESULT;
	CX__VAR_STRING_CTRL  sCH__REPORT_EPD_SEC;
	//

	//-------------------------------------------------------------------
	// LINK.EPD_SIGNAL ...

	bool bActive__EPD_SIGNAL_MAIN;
	CX__VAR_ANALOG_CTRL aEXT_CH__EPD_SIGNAL_MAIN;

	int iSIZE__EPD_SIGNAL;
	CX__VAR_ANALOG_CTRL aEXT_CH__EPD_SIGNAL_X[_CFG__CHART_INTENSITY];
	//

	//-------------------------------------------------------------------
	// ...
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__IDLE;
	int Call__IDLE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__EPD_DETECT;
	int Call__EPD_DETECT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__ERROR_CHECK;
	int Call__ERROR_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__EPD_TEST;
	int Call__EPD_TEST(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	int Fnc__EPD_TEST(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	int Fnc__EPD_DETECT__ValueCheck(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const bool active__over_check);
	int _Fnc__EPD_DETECT__ValueCheck(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const bool active__over_check);

	int Fnc__EPD_DETECT__ValueSlope(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const bool active__over_check);
	int _Fnc__EPD_DETECT__ValueSlope(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const bool active__over_check);

	// ...
	int Fnc__EPD_DETECT__ValueChange(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	int Fnc__EPD_DETECT__PercentChange(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	int Fnc__EPD_DETECT__CheckDelayTime(CII_OBJECT__VARIABLE *p_variable);
	int Fnc__EPD_DETECT__CheckNormalizeTime(CII_OBJECT__VARIABLE *p_variable);

	int Fnc__EPD_DETECT__CheckValueChange(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Fnc__EPD_DETECT__CheckPercentChange(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Fnc__EPD_DETECT__CheckSlope(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//

	//-------------------------------------------------------------------
	// ...
	int Mon__EPD_CHART(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	int Mon__ERROR_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString Get__ERROR_MSG(CClass__Error_Timer* p_error);
	//

	// ...
	int  Alarm_Post__EPD_MAX_TIMEOUT(CII_OBJECT__ALARM* p_alarm,const CString& alarm_msg);
	int  Alarm_Post__EPD_MIN_TIMEOUT(CII_OBJECT__ALARM* p_alarm,const CString& alarm_msg);

	int	 Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id);
	void Alarm__POST_CHECK(CII_OBJECT__ALARM *p_alarm, CString msg, const int alarm_id);

	// ...
	double Get__EPD_CUR_DATA();
	double Get__EPD_CUR_SEC();

	// ...
	void Fnc__WRITE_LOG(const CString& log_msg);
	//


public:
	CObj__EPD_SINGLE();
	~CObj__EPD_SINGLE();

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
