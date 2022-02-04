#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__FRC_CHECK__ALID.h"
#include "CObj__FRC_CHECK__DEF.h"


class CObj__FRC_CHECK : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	// ...
	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;
	CCommon_Error__USER_FNC     mERROR__USER_FNC;
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

	CX__VAR_ANALOG_CTRL  aCH_CFG__FLOW_STABLE_SEC;
	CX__VAR_STRING_CTRL  sCH__CUR_CHECK_TIME_COUNT;

	CX__VAR_ANALOG_CTRL  aCH_CFG__CHECK_ERROR_PERCENT;
	CX__VAR_STRING_CTRL  sCH__CUR_CHECK_ERROR_PERCENT;

	// CFG : Check List ...
	CX__VAR_STRING_CTRL  sCH__CFG_CH1_RATE_X[CFG_FRC__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH__CFG_CH2_RATE_X[CFG_FRC__TEST_LIST];

	CX__VAR_STRING_CTRL  sCH__TEST_CH1_NEW_X[CFG_FRC__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH__TEST_CH2_NEW_X[CFG_FRC__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH__TEST_RATE_NEW_X[CFG_FRC__TEST_LIST];

	CX__VAR_STRING_CTRL  sCH__TEST_CH1_REF_X[CFG_FRC__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH__TEST_CH2_REF_X[CFG_FRC__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH__TEST_RATE_REF_X[CFG_FRC__TEST_LIST];

	CX__VAR_STRING_CTRL  sCH__TEST_RESULT_ERROR_X[CFG_FRC__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH__TEST_RESULT_PASS_X[CFG_FRC__TEST_LIST];

	//
	CX__VAR_STRING_CTRL  sCH__LAST_TEST_DATE;
	CX__VAR_STRING_CTRL  sCH__LAST_TEST_TIME;

	//
	CX__VAR_STRING_CTRL  sCH__RESULT_STRING;
	CX__VAR_STRING_CTRL  sCH__REF_STRING;
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// FRC INFO ...
	int iFRC_ID;

	CX__VAR_ANALOG_CTRL  aEXT_CH__CH1_RATIO_SET;
	CX__VAR_ANALOG_CTRL  aEXT_CH__CH2_RATIO_SET;

	CX__VAR_ANALOG_CTRL  aEXT_CH__CH1_RATIO_GET;
	CX__VAR_ANALOG_CTRL  aEXT_CH__CH2_RATIO_GET;

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
	CString sMODE__FLOW_TEST;
	int  Call__FLOW_TEST(CII_OBJECT__VARIABLE *p_variable,
						 CII_OBJECT__ALARM *p_alarm);

	int  Fnc__FLOW_TEST(CII_OBJECT__VARIABLE *p_variable,
		                CII_OBJECT__ALARM *p_alarm);

	//-------------------------------------------------------------------------
	void Mon__STATUS_CTRL(CII_OBJECT__VARIABLE *p_variable, 
		                  CII_OBJECT__ALARM *p_alarm);

	// ...
	int  Get__Gas_Type_Index(const CString& str_gas_type);
	//


public:
	CObj__FRC_CHECK();
	~CObj__FRC_CHECK();

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
