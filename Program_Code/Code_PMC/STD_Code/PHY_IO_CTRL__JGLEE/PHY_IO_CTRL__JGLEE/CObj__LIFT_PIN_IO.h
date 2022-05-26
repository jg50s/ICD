#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"

#include "CObj__LIFT_PIN_IO__ALID.h"
#include "CObj__LIFT_PIN_IO__DEF.h"


class CObj__LIFT_PIN_IO : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;	

	SCX__USER_LOG_CTRL xLOG_CTRL;
	int iActive__SIM_MODE;

	CUIntArray iLIST_ALID__PIN;
	//

	//-------------------------------------------------------------------------
	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL  sCH__OBJ_TIMER;

	// MON.PART ... 
	CX__VAR_DIGITAL_CTRL dCH__MON_PIN_ERROR_ACTIVE;

	// MON ... 
	CX__VAR_STRING_CTRL  sCH__MON_ACT_NAME;

	CX__VAR_STRING_CTRL  sCH__MON_LIFT_STATE;
	CX__VAR_STRING_CTRL  sCH__LIFT_STS_LINK;

	//
	CX__VAR_STRING_CTRL  sCH__MON_POS_UP_ACTIVE_PIN_X[_CFG__PIN_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_POS_DOWN_ACTIVE_PIN_X[_CFG__PIN_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_POS_MIDDLE_ACTIVE_PIN_X[_CFG__PIN_SIZE];

	// LINK IO ...
	CX__VAR_STRING_CTRL  sEXT_CH__LIFT_PIN_STATE;

	//
	bool bActive__ESC_CHUCK_STATE;
	CX__VAR_STRING_CTRL  sEXT_CH__ESC_CHUCK_STATE;

	int iDATA__ESC_CH_SIZE;
	CX__VAR_ANALOG_CTRL  aEXT_CH__ESC_AI_VOLTAGE_X[_CFG__ESC_CH_SIZE];

	//
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_TRANSFER_PIN_UP;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_TRANSFER_PIN_DOWN;

	bool bActive__DO_MIDDLE_PIN_UP;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_MIDDLE_PIN_UP;
	
	bool bActive__DO_MIDDLE_PIN_DOWN;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_MIDDLE_PIN_DOWN;

	//
	int iDATA__PIN_SNS_TYPE;

	// DI.SNS ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_PIN_UP;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_PIN_MIDDLE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_PIN_DOWN;

	// AI.SNS ...
	int iSIZE__AI_PIN__POS;
	CX__VAR_ANALOG_CTRL  aEXT_CH__AI_PIN_POS_X[_CFG__PIN_SIZE];

	// CFG ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_LIFT_PIN_ACTION_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_ESC_VOLTAGE_PIN_UP_THRESHOLD;

	//
	CX__VAR_ANALOG_CTRL  aCH__CFG_DOWN_POS_MIN__PIN_X[_CFG__PIN_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_DOWN_POS_MAX__PIN_X[_CFG__PIN_SIZE];

	CX__VAR_ANALOG_CTRL  aCH__CFG_UP_POS_MIN__PIN_X[_CFG__PIN_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_UP_POS_MAX__PIN_X[_CFG__PIN_SIZE];

	CX__VAR_ANALOG_CTRL  aCH__CFG_MIDDLE_POS_MIN__PIN_X[_CFG__PIN_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_MIDDLE_POS_MAX__PIN_X[_CFG__PIN_SIZE];

	// TEST ...
	CX__VAR_ANALOG_CTRL  aCH__UPDOWN_TEST_CFG_CYCLE_COUNT;
	CX__VAR_STRING_CTRL  sCH__UPDOWN_TEST_CUR_CYCLE_COUNT;

	CX__VAR_ANALOG_CTRL  aCH__UPDOWN_TEST_CFG_UP_STAY_SEC;
	CX__VAR_STRING_CTRL  sCH__UPDOWN_TEST_CUR_UP_STAY_SEC;

	CX__VAR_ANALOG_CTRL  aCH__UPDOWN_TEST_CFG_DOWN_STAY_SEC;
	CX__VAR_STRING_CTRL  sCH__UPDOWN_TEST_CUR_DOWN_STAY_SEC;

	CX__VAR_STRING_CTRL  sCH__UPDOWN_TEST_MSG;

	// ...
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_UP_NOW_UP;
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_UP_AVG_UP;
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_UP_MIN_UP;
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_UP_MAX_UP;

	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_UP_NOW_DOWN;
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_UP_AVG_DOWN;
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_UP_MIN_DOWN;
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_UP_MAX_DOWN;

	//
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_MIDDLE_NOW_MIDDLE;
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_MIDDLE_AVG_MIDDLE;
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_MIDDLE_MIN_MIDDLE;
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_MIDDLE_MAX_MIDDLE;

	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_MIDDLE_NOW_DOWN;
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_MIDDLE_AVG_DOWN;
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_MIDDLE_MIN_DOWN;
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_DOWN_MIDDLE_MAX_DOWN;
	//


	//-------------------------------------------------------------------------
	// ...
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__UP;
	int Call__UP(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__MIDDLE;
	int Call__MIDDLE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm, const bool active__middle_up = true);

	CString sMODE__DOWN;
	int Call__DOWN(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	//
	CString sMODE__TRANSFER_UP;
	int Call__TRANSFER_UP(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__TRANSFER_DOWN;
	int Call__TRANSFER_DOWN(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	//
	CString sMODE__MIDDLE_UP;
	int Call__MIDDLE_UP(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__MIDDLE_DOWN;
	int Call__MIDDLE_DOWN(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	//
	CString sMODE__CYCLE_UpToDown;
	int Call__CYCLE_UpToDown(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__CYCLE_MiddleToDown;
	int Call__CYCLE_MiddleToDown(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	int  Fnc__CYCLE_TEST(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm, const int i_cycle_mode);

	CString Get__AVG_DATA(const int n_count, const double cur_data, const double pre_avg);
	void Fnc__Check_MIN_MAX_DATA(const int n_count, CII__VAR_STRING_CTRL* p_ch_min, CII__VAR_STRING_CTRL* p_ch_max, const double cur_data);

	// ...
	void _Fnc__SIM_PIN_POD(const bool active_up, const bool active_down, const bool active_middle);
	//


	//-------------------------------------------------------------------------
	int Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Fnc__CHECK_CHUCKING(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	int	 Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id);
	int	 Alarm__POST_CHECK(CII_OBJECT__ALARM *p_alarm, CString msg, const int alarm_id);

	void Fnc__WRITE_LOG(const CString& log_msg);
	//


public:
	CObj__LIFT_PIN_IO();
	~CObj__LIFT_PIN_IO();

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
