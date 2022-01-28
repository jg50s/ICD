#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CObj__ManiFold_TEST__DEF.h"


// ...
#define  ALID__MD_X__STATUS_IS_NOT_MAINT		1		// ~ 5

#define  CFG__MD_SIZE							5


class CObj__ManiFold_TEST : public __IOBJ__STD_TYPE
{
private:
	//------------------------------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xLOG_CTRL;


	//------------------------------------------------------------------------------
	// INTERNAL PROPERTY ...

	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL  sCH__OBJ_ACTIVE_MODE;

	// ...
	CX__VAR_ANALOG_CTRL  aCH__CYCLE_TEST_CFG_COUNT_ALL;
	CX__VAR_STRING_CTRL  sCH__CYCLE_TEST_CUR_COUNT_ALL;

	// ...
	CX__VAR_DIGITAL_CTRL dCH__CYCLE_TEST_CFG_ACTIVE_X[CFG__MD_SIZE];
	CX__VAR_STRING_CTRL  sCH__CYCLE_TEST_CUR_ACTIVE_X[CFG__MD_SIZE];

	CX__VAR_STRING_CTRL  sCH__CYCLE_TEST_CUR_COUNT_X[CFG__MD_SIZE];

	CX__VAR_DIGITAL_CTRL dCH__CYCLE_TEST_CFG_VENT_X[CFG__MD_SIZE];
	CX__VAR_STRING_CTRL  sCH__CYCLE_TEST_CUR_VENT_X[CFG__MD_SIZE];
	//

	//------------------------------------------------------------------------------
	// EXTERNAL PROPERTY ...

	// ...
	int iMD_SIZE;

	CString sMD_NAME_X[CFG__MD_SIZE];
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__MD_FNC_X[CFG__MD_SIZE];

	CX__VAR_DIGITAL_CTRL dEXT_CH__MD_OBJ_STATUS_X[CFG__MD_SIZE];
	//

	//------------------------------------------------------------------------------
	// OBJ FNC ...
	CString sMODE__PUMPING_CYCLE_TEST;
	int  Call__PUMPING_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	int  Fnc__PUMPING_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int vlv_type,const int lbx_index);

	CString Get__AVG_DATA(const int n_count, const double cur_data, const double pre_avg);
	void Fnc__Check_MIN_MAX_DATA(const int n_count, CII__VAR_STRING_CTRL* p_ch_min, CII__VAR_STRING_CTRL* p_ch_max, const double cur_data);
	//


public:
	CObj__ManiFold_TEST();
	~CObj__ManiFold_TEST();

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

