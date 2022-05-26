#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Def.h"

#include "CObj__RF_CONDUCT__ALID.h"
#include "CObj__RF_CONDUCT__DEF.h"


class CObj__RF_CONDUCT : public __IOBJ__STD_TYPE
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
	//
	CX__VAR_DIGITAL_CTRL dCH_PARA__TEST_MODE;

	CX__VAR_STRING_CTRL  sCH_PARA__ACT_ACTIVE_FLAG;
	CX__VAR_STRING_CTRL  sCH_PARA__NEXT_TEST_REQ;
	CX__VAR_STRING_CTRL  sCH_PARA__END_TEST_REQ;

	CX__VAR_STRING_CTRL  sCH__DB_UPDATE_REQUEST;

	//
	CX__VAR_DIGITAL_CTRL dCH_PARA__RF_TYPE;


	// SET POWER
	CX__VAR_ANALOG_CTRL  aCH_PARA__SET_PWR_LIST[CFG__TEST_LIST];

	// NEW POWER
	CX__VAR_STRING_CTRL  sCH_PARA__NEW_POWER_LIST[CFG__TEST_LIST];

	// NEW METER 
	CX__VAR_STRING_CTRL  sCH_PARA__NEW_METER_LIST[CFG__TEST_LIST];

	// NEW OFFSET 
	CX__VAR_STRING_CTRL  sCH_PARA__NEW_OFFSET_LIST[CFG__TEST_LIST];

	// NOW POWER
	CX__VAR_STRING_CTRL  sCH_PARA__NOW_POWER_LIST[CFG__TEST_LIST];

	// NOW METER 
	CX__VAR_STRING_CTRL  sCH_PARA__NOW_METER_LIST[CFG__TEST_LIST];

	// NOW OFFSET 
	CX__VAR_STRING_CTRL  sCH_PARA__NOW_OFFSET_LIST[CFG__TEST_LIST];


	// RESULT STRING
	CX__VAR_STRING_CTRL  sCH__RESULT_STRING;

	// REF STRING
	CX__VAR_STRING_CTRL  sCH__REF_STRING;

	// CHECK TIME COUNT
	CX__VAR_STRING_CTRL  sCH_PARA__CHECK_TIME_COUNT;

	// CONFIG .....
	CX__VAR_ANALOG_CTRL  aCH_CFG__STABLE_DELAY_SEC;

	// Offset CAL ...
	CX__VAR_STRING_CTRL  sCH__OFFSET_CAL_REQ_FLAG;
	CX__VAR_STRING_CTRL  sCH__OFFSET_CAL_ACTIVE_FLAG;

	CX__VAR_STRING_CTRL  sCH__CFG_AVERAGE_NEW_OFFSET;
	CX__VAR_STRING_CTRL  sCH__CFG_AVERAGE_NOW_OFFSET;

	// RF_SAVE.X ...
	CX__VAR_STRING_CTRL  sCH__SAVE_ACTIVE_FLAG__RF_X[_MAX__RF_SIZE];
	CX__VAR_STRING_CTRL  sCH__SAVE_REQ_FLAG__RF_X[_MAX__RF_SIZE];
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

	// IO SENSOR
	CX__VAR_DIGITAL_CTRL dEXT_CH__VAC_IO_SENSOR;

	// OBJ - RF_X ...
	int iRF_SIZE;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__RF_X[_MAX__RF_SIZE];
	CString sTITLE__RF_X[_MAX__RF_SIZE];

	CX__VAR_ANALOG_CTRL  aEXT_CH__SET_POWER__RF_X[_MAX__RF_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__GET_POWER__RF_X[_MAX__RF_SIZE];

	CX__VAR_DIGITAL_CTRL dEXT_CH__INTERLOCK_SKIP__RF_X[_MAX__RF_SIZE];

	CX__VAR_ANALOG_CTRL  aEXT_CH__CAL_CFG_SET_POWER__RF_X[_MAX__RF_SIZE][CFG__TEST_LIST];
	CX__VAR_STRING_CTRL  sEXT_CH__CAL_CFG_NEW_POWER__RF_X[_MAX__RF_SIZE][CFG__TEST_LIST];
	CX__VAR_STRING_CTRL  sEXT_CH__CAL_CFG_NEW_METER__RF_X[_MAX__RF_SIZE][CFG__TEST_LIST];
	CX__VAR_STRING_CTRL  sEXT_CH__CAL_CFG_NEW_OFFSET__RF_X[_MAX__RF_SIZE][CFG__TEST_LIST];
	CX__VAR_STRING_CTRL  sEXT_CH__CAL_CFG_NOW_POWER__RF_X[_MAX__RF_SIZE][CFG__TEST_LIST];
	CX__VAR_STRING_CTRL  sEXT_CH__CAL_CFG_NOW_METER__RF_X[_MAX__RF_SIZE][CFG__TEST_LIST];
	CX__VAR_STRING_CTRL  sEXT_CH__CAL_CFG_NOW_OFFSET__RF_X[_MAX__RF_SIZE][CFG__TEST_LIST];

	CX__VAR_STRING_CTRL  sEXT_CH__CAL_CFG_NEW_AVG_OFFSET__RF_X[_MAX__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__CAL_CFG_NOW_AVG_OFFSET__RF_X[_MAX__RF_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__CAL_OFFSET_SAVE_DATE__RF_X[_MAX__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__CAL_TEST_FLAG__RF_X[_MAX__RF_SIZE];
	//


	//-------------------------------------------------------------------------
	int iFLAG__RF_CHECK;
	CString sMODE__RF_CHECK;
	int  Call__RF_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int  _Call__RF_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	int  Fnc__RF_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm, const int rf_index);

	int  Fnc__LOWER_RF_CHECK(CII_OBJECT__VARIABLE *p_variable,
						CII_OBJECT__ALARM *p_alarm,
						CII_EXT_OBJECT__CTRL *p_rf_ctrl,
						CII__VAR_ANALOG_CTRL *p_rf_set,
						CII__VAR_ANALOG_CTRL *p_rf_get,
						const CString& set_pwr,
						const int db_index);

	//-------------------------------------------------------------------------
	void  Mon__STATUS_CTRL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	void  Fnc__RFx_CAL(const int rf_index);
	void  Fnc__RFx_SAVE(const int rf_index);
	//


public:
	CObj__RF_CONDUCT();
	~CObj__RF_CONDUCT();

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

