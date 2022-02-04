#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__DGF_CHECK__ALID.h"
#include "CObj__DGF_CHECK__DEF.h"


class CObj__DGF_CHECK : public __IOBJ__STD_TYPE
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

	CX__VAR_STRING_CTRL  xCH__AUTO_START_CTRL;

	// PARAMETER .....
	// TEST INFO
	CX__VAR_STRING_CTRL  sCH_PARA__TEST_DATE;
	CX__VAR_STRING_CTRL  sCH_PARA__TEST_TIME;

	// CURRENT LIST
	CX__VAR_STRING_CTRL  sCH_PARA__CUR_RESULT_LIST[CFG__TEST_LIST];

	// NEW LIST
	CX__VAR_STRING_CTRL  sCH_PARA__NEW_RESULT_LIST[CFG__TEST_LIST];

	// DELTA LIST
	CX__VAR_STRING_CTRL  sCH_PARA__DELTA_RESULT_LIST[CFG__TEST_LIST];

	// CHECK TIME COUNT
	CX__VAR_STRING_CTRL  sCH_PARA__CHECK_TIME_COUNT;

	CX__VAR_STRING_CTRL  sCH_RESULT__START_PRESSURE;
	CX__VAR_STRING_CTRL  sCH_RESULT__END_PRESSURE;

	// RESULT STRING
	CX__VAR_STRING_CTRL  sCH__RESULT_STRING;

	// REF STRING
	CX__VAR_STRING_CTRL  sCH__REF_STRING;


	// CONFIG .....
	CX__VAR_ANALOG_CTRL  aCH_CFG__ORIFICE_SIZE[CFG__TEST_LIST];
	CX__VAR_ANALOG_CTRL  aCH_CFG__BASELINE[CFG__TEST_LIST];

	CX__VAR_DIGITAL_CTRL dCH_CFG__HIGH_FLOW_GAS_NAME;
	CX__VAR_ANALOG_CTRL  aCH_CFG__HIGH_FLOW_GAS_SET;

	CX__VAR_DIGITAL_CTRL dCH_CFG__LOW_FLOW_GAS_NAME;
	CX__VAR_ANALOG_CTRL  aCH_CFG__LOW_FLOW_GAS_SET;

	CX__VAR_ANALOG_CTRL  aCH_CFG__BASELINE_TOLERANCE;

	CX__VAR_ANALOG_CTRL  aCH_CFG__STABLE_DELAY_SEC;
	CX__VAR_ANALOG_CTRL  aCH_CFG__CHECK_DELAY_SEC;
	CX__VAR_ANALOG_CTRL  aCH_CFG__PUMPING_DELAY_SEC;
	CX__VAR_DIGITAL_CTRL dCH_CFG__TEST_ORDER;
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// DB - SYS
	CX__VAR_STRING_CTRL  sEXT_CH__SYSTEM_MSG;
	CX__VAR_STRING_CTRL  sEXT_CH__FNC_MSG;

	// SYSTEM CHANNEL
	CX__VAR_STRING_CTRL  sEXT_CH__SYS_FNC_NAME;
	CX__VAR_STRING_CTRL  sEXT_CH__SYS_FNC_MSG;
	CX__VAR_STRING_CTRL  sEXT_CH__SYS_FNC_LOCK;

	// CH.PRESSURE
	CX__VAR_STRING_CTRL  sEXT_CH__PRESSURE;

	// OBJ - CHM CTRL .....
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__CHM;

	// OBJ - FNC MFCx .....
	CII_EXT_OBJECT__CTRL* pOBJ_CTRL__FNC_MFC;

	CX__VAR_DIGITAL_CTRL dEXT_CH__FNC_MFC__PARA_MFC_TYPE;
	CX__VAR_ANALOG_CTRL  aEXT_CH__FNC_MFC__PARA_MFC_FLOW;

	// OBJ - DGF CTRL .....
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__DGF;

	CX__VAR_DIGITAL_CTRL dEXT_CH__PARA_ORIFICE_VLV;
	//


	//-------------------------------------------------------------------------
	CString sMODE__ORIFICE_CHECK;
	int  Call__ORIFICE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	int  Fnc__ORIFICE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int  Fnc__LOWER_ORIFICE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm,const int db_index);

	//-------------------------------------------------------------------------
	void  Mon__STATUS_CTRL(CII_OBJECT__VARIABLE *p_variable);
	//


public:
	CObj__DGF_CHECK();
	~CObj__DGF_CHECK();

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
