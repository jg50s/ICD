#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Def.h"

#include "CObj__GAUGE_CHECK__ALID.h"
#include "CObj__GAUGE_CHECK__DEF.h"


class CObj__GAUGE_CHECK : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	// ...
	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;
	CCommon_Error__USER_FNC     mERROR__USER_FNC;

	// ...
	int iSIM_MODE;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// SYSTEM CHANNEL .....
	CX__VAR_STRING_CTRL  xCH__OBJ_MSG;
	CX__VAR_STRING_CTRL  xCH__OBJ_ERROR_MSG;

	CX__VAR_STRING_CTRL  xCH__AUTO_START_CTRL;
	CX__VAR_STRING_CTRL  sCH__RESULT_SAVE_REQ;
	CX__VAR_STRING_CTRL  sCH__CHECK_TYPE_UPDATE_REQ;
	CX__VAR_STRING_CTRL  sCH__RESULT_ERROR_RANGE_CHECK_REQ;

	// PARAMETER .....
	CX__VAR_DIGITAL_CTRL dCH_PARA__TEST_GAS_TYPE;
	CX__VAR_ANALOG_CTRL  aCH_PARA__TEST_GAS_FLOW;
	CX__VAR_STRING_CTRL  sCH__CUR_TEST_GAS_NAME;

	CX__VAR_ANALOG_CTRL  aCH_CFG__PRESSURE_STABLE_SEC;
	CX__VAR_STRING_CTRL  sCH__CUR_CHECK_TIME_COUNT;

	CX__VAR_ANALOG_CTRL  aCH__CFG_CHECK_COUNT;
	CX__VAR_STRING_CTRL  sCH__CUR_CHECK_COUNT;
	CX__VAR_STRING_CTRL  sCH__CUR_LOW_PRESSURE_COUNT;

	CX__VAR_ANALOG_CTRL  aCH__CFG_UPPER_PRESSURE;
	CX__VAR_STRING_CTRL  sCH__CUR_UPPER_PRESSURE;

	CX__VAR_STRING_CTRL  sCH__TEST_INTERVAL_TIME;
	CX__VAR_STRING_CTRL  sCH__TEST_INTERVAL_CUR;

	CX__VAR_ANALOG_CTRL  aCH_CFG__CHECK_ERROR_PERCENT;
	CX__VAR_STRING_CTRL  sCH__CUR_CHECK_ERROR_PERCENT;

	// CFG : Check List ...
	CX__VAR_STRING_CTRL  sCH__TEST_TIME_NEW_X[CFG_GAUGE__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH__TEST_PRESS_NEW_X[CFG_GAUGE__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH__TEST_RATE_NEW_X[CFG_GAUGE__TEST_LIST];

	CX__VAR_STRING_CTRL  sCH__TEST_TIME_REF_X[CFG_GAUGE__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH__TEST_PRESS_REF_X[CFG_GAUGE__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH__TEST_RATE_REF_X[CFG_GAUGE__TEST_LIST];

	//
	CX__VAR_STRING_CTRL  sCH__TEST_LOW_PRESS_MIN_NEW;
	CX__VAR_STRING_CTRL  sCH__TEST_LOW_PRESS_AVG_NEW;
	CX__VAR_STRING_CTRL  sCH__TEST_LOW_PRESS_MAX_NEW;

	CX__VAR_STRING_CTRL  sCH__TEST_LOW_PRESS_MIN_REF;
	CX__VAR_STRING_CTRL  sCH__TEST_LOW_PRESS_AVG_REF;
	CX__VAR_STRING_CTRL  sCH__TEST_LOW_PRESS_MAX_REF;

	//
	CX__VAR_STRING_CTRL  sCH__TEST_LINEAR_CHECK_RESULT_NEW;
	CX__VAR_STRING_CTRL  sCH__TEST_LINEAR_CHECK_RESULT_REF;

	CX__VAR_STRING_CTRL  sCH__TEST_LINEAR_CHECK_ERROR_NEW;

	//
	CX__VAR_STRING_CTRL  sCH__LAST_TEST_DATE;
	CX__VAR_STRING_CTRL  sCH__LAST_TEST_TIME;

	//
	CX__VAR_STRING_CTRL  sCH__RESULT_STRING;
	CX__VAR_STRING_CTRL  sCH__REF_STRING;

	//
	CX__VAR_STRING_CTRL  sCH__CHECK_TYPE_SAVE_REQ;
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// CH.CHM.PRESSURE
	CX__VAR_STRING_CTRL  sEXT_CH__CHM_PRESSURE;

	// OBJ - CHM CTRL
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__CHM;

	// OBJ - GAS VLV
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__GAS_VLV;

	// DB - SYS
	CX__VAR_STRING_CTRL  sEXT_CH__SYSTEM_MSG;
	CX__VAR_STRING_CTRL  sEXT_CH__FNC_MSG;

	// SYSTEM CHANNEL
	CX__VAR_STRING_CTRL  sEXT_CH__SYS_FNC_NAME;
	CX__VAR_STRING_CTRL  sEXT_CH__SYS_FNC_MSG;
	CX__VAR_STRING_CTRL  sEXT_CH__SYS_FNC_LOCK;

	// OBJ - MFCx CTRL
	int iSIZE__OBJ_MFCx;

	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__MFC_X[CFG__MFC_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__MFCx_PARA_SET_FLOW[CFG__MFC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__MFCx_CFG_GAS_NAME[CFG__MFC_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__MFCx_CFG_GAS_MAX[CFG__MFC_SIZE];
	//


	//-------------------------------------------------------------------------
	CString sMODE__ALL_CHECK;
	int  Call__ALL_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__LOW_PRESSURE_CHECK;
	int  Call__LOW_PRESSURE_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__LINEAR_CHECK;
	int  Call__LINEAR_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	int  _Fnc__LINEAR_CHECK(CII_OBJECT__VARIABLE *p_variable, const int loop_index);
	//

	//-------------------------------------------------------------------------
	void Mon__STATUS_CTRL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	int  Get__Gas_Type_Index(const CString& str_gas_type);
	//


public:
	CObj__GAUGE_CHECK();
	~CObj__GAUGE_CHECK();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_def_fnc);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
