#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Def.h"

#include "CObj__APC_POS_CONDUCT__ALID.h"
#include "CObj__APC_POS_CONDUCT__DEF.h"


// ...
#define  _SIZE__TEST_TYPE			    3
#define  _TEST_TYPE__INDEX_AR			0
#define  _TEST_TYPE__INDEX_N2			1
#define  _TEST_TYPE__INDEX_USER			2


class CObj__APC_POS_CONDUCT : public __IOBJ__STD_TYPE
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
	CX__VAR_STRING_CTRL  sCH__CHECK_TYPE_SAVE_REQ;
	CX__VAR_STRING_CTRL  sCH__CURRENT_REF_COPY_REQ;
	CX__VAR_STRING_CTRL  sCH__RESULT_ERROR_RANGE_CHECK_REQ;


	// PARAMETER .....
	CX__VAR_DIGITAL_CTRL dCH__CFG_CHECK_TYPE;
	CX__VAR_DIGITAL_CTRL dCH__CFG_RESULT_ERROR_TYPE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_RESULT_ERROR_RANGE;

	CX__VAR_DIGITAL_CTRL dCH_PARA__TEST_GAS_TYPE;
	CX__VAR_ANALOG_CTRL  aCH_PARA__TEST_GAS_FLOW;

	CX__VAR_STRING_CTRL  sCH__CUR_TEST_GAS_NAME;

	// New Parameter ...
	CX__VAR_ANALOG_CTRL  aCH_PARA__VLV_POS_LIST[CFG__TEST_LIST];
	CX__VAR_ANALOG_CTRL  aCH_USER__VLV_POS_LIST[CFG__TEST_LIST];

	CX__VAR_STRING_CTRL  sCH_PARA__CONDUCT_RESULT[CFG__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH_PARA__CONDUCT_RESULT_OF_TYPE[_SIZE__TEST_TYPE][CFG__TEST_LIST];

	CX__VAR_STRING_CTRL  sCH_PARA__TEST_DATE;
	CX__VAR_STRING_CTRL  sCH_PARA__TEST_TIME;

	// Current Parameter ...
	CX__VAR_STRING_CTRL  sCH__CUR_VLV_POS_LIST_OF_TYPE[_SIZE__TEST_TYPE][CFG__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH__CUR_CONDUCT_RESULT_OF_TYPE[_SIZE__TEST_TYPE][CFG__TEST_LIST];

	CX__VAR_STRING_CTRL  sCH__CUR_VLV_POS_LIST[CFG__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH__CUR_CONDUCT_RESULT[CFG__TEST_LIST];

	CX__VAR_STRING_CTRL  sCH__CUR_TEST_DATE;
	CX__VAR_STRING_CTRL  sCH__CUR_TEST_TIME;

	// Reference Parameter ...
	CX__VAR_ANALOG_CTRL  aCH_PARA__VLV_REF_LIST[CFG__TEST_LIST];
	CX__VAR_ANALOG_CTRL  aCH_N2_5PER__VLV_REF_LIST[CFG__TEST_LIST];
	CX__VAR_ANALOG_CTRL  aCH_USER__VLV_REF_LIST[CFG__TEST_LIST];


	// Result List ...
	CX__VAR_STRING_CTRL  sCH__RESULT_STRING;
	CX__VAR_STRING_CTRL  sCH__CUR_STRING;
	CX__VAR_STRING_CTRL  sCH__REF_STRING;

	// CHECK TIME COUNT
	CX__VAR_STRING_CTRL  sCH__CUR_CHECK_TIME_COUNT;


	// CONFIG .....
	CX__VAR_ANALOG_CTRL  aCH_CFG__FLOW_DELAY_SEC;
	CX__VAR_ANALOG_CTRL  aCH_CFG__PRESSURE_STABLE_DELAY_SEC;
	CX__VAR_DIGITAL_CTRL dCH_CFG__TEST_ORDER;
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// OBJ - VAT CTRL ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__VAT;

	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_VLV_POS_DATA;

	// CH.CHM.PRESSURE ...
	CX__VAR_STRING_CTRL  sEXT_CH__CHM_PRESSURE;

	// OBJ - CHM CTRL ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__CHM;

	// OBJ - GAS_VLV ...
	CII_EXT_OBJECT__CTRL* pOBJ_CTRL__GAS_VLV;

	CX__VAR_DIGITAL_CTRL dEXT_CH__GAS_VLV__PARA_MFC_TYPE;
	CX__VAR_ANALOG_CTRL  aEXT_CH__GAS_VLV__PARA_MFC_FLOW;

	// DB - SYS ...
	CX__VAR_STRING_CTRL  sEXT_CH__SYSTEM_MSG;
	CX__VAR_STRING_CTRL  sEXT_CH__FNC_MSG;

	// SYSTEM CHANNEL ...
	CX__VAR_STRING_CTRL  sEXT_CH__SYS_FNC_NAME;
	CX__VAR_STRING_CTRL  sEXT_CH__SYS_FNC_MSG;
	CX__VAR_STRING_CTRL  sEXT_CH__SYS_FNC_LOCK;

	// OBJ - MFCx CTRL ...
	int iSIZE__OBJ_MFCx;

	CX__VAR_STRING_CTRL  sEXT_CH__MFCx_CFG_GAS_NAME[CFG__MFC_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__MFCx_CFG_GAS_MAX[CFG__MFC_SIZE];
	//


	//-------------------------------------------------------------------------
	CString sMODE__POS_CONDUCT;
	int  Call__POS_CONDUCT(CII_OBJECT__VARIABLE *p_variable,
					       CII_OBJECT__ALARM *p_alarm);

	int  Fnc__POS_CONDUCT(CII_OBJECT__VARIABLE *p_variable,
						  CII_OBJECT__ALARM *p_alarm);
	int  Fnc__LOWER_POS_CONDUCT(CII_OBJECT__VARIABLE *p_variable,
								CII_OBJECT__ALARM *p_alarm,
								const CString& vlv_pos,
								const CString& gas_name,
								const CString& gas_flow,
								const int db_index);

	//-------------------------------------------------------------------------
	void Mon__STATUS_CTRL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	int  Get__Gas_Type_Index(const CString& str_gas_type);
	void Update__CHECK_TYPE(const CString& cur__check_type, const CString& pre__check_type);
	void Save__CHECK_TYPE(const CString& str__check_type);
	void Copy__CURRENT_REF(const CString& str__check_type);
	//


public:
	CObj__APC_POS_CONDUCT();
	~CObj__APC_POS_CONDUCT();

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
