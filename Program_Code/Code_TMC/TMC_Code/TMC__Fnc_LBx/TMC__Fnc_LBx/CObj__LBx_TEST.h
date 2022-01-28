#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CObj__LBx_TEST__DEF.h"


// ...
#define  ALID__LBA_STATUS_IS_NOT_MAINT				1
#define  ALID__LBB_STATUS_IS_NOT_MAINT				2
#define  ALID__LBC_STATUS_IS_NOT_MAINT				3
#define  ALID__LBD_STATUS_IS_NOT_MAINT				4

// ...
#define  VLV_TYPE__SV					1
#define  VLV_TYPE__DV					2

#define  _LLx_INDEX__LBA				0
#define  _LLx_INDEX__LBB				1
#define  _LLx_INDEX__LBC				2
#define  _LLx_INDEX__LBD				3

#define  CFG__LLx_SIZE					4


class CObj__LBx_TEST : public __IOBJ__STD_TYPE
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
	CX__VAR_ANALOG_CTRL  aCH__CYCLE_TEST_CFG_CYCLE_COUNT;
	CX__VAR_STRING_CTRL  sCH__CYCLE_TEST_CUR_CYCLE_COUNT;

	CX__VAR_ANALOG_CTRL  aCH__CYCLE_TEST_CFG_DELAY_SEC;
	CX__VAR_STRING_CTRL  sCH__CYCLE_TEST_CUR_DELAY_SEC;

	// ...
	CX__VAR_STRING_CTRL  sCH__CYCLE_TEST_OP_TIME_CUR;
	CX__VAR_STRING_CTRL  sCH__CYCLE_TEST_OP_TIME_AVG;
	CX__VAR_STRING_CTRL  sCH__CYCLE_TEST_OP_TIME_MIN;
	CX__VAR_STRING_CTRL  sCH__CYCLE_TEST_OP_TIME_MAX;

	CX__VAR_STRING_CTRL  sCH__CYCLE_TEST_CL_TIME_CUR;
	CX__VAR_STRING_CTRL  sCH__CYCLE_TEST_CL_TIME_AVG;
	CX__VAR_STRING_CTRL  sCH__CYCLE_TEST_CL_TIME_MIN;
	CX__VAR_STRING_CTRL  sCH__CYCLE_TEST_CL_TIME_MAX;


	//------------------------------------------------------------------------------
	// EXTERNAL PROPERTY ...

	int iLLx_SIZE;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__LLx_FNC[CFG__LLx_SIZE];

	CX__VAR_DIGITAL_CTRL dEXT_CH__LLx_OBJ_STATUS[CFG__LLx_SIZE];
	//

	//------------------------------------------------------------------------------
	// OBJ FNC ...
	CString sMODE__LBA_SV_CYCLE_TEST;
	int  Call__LBA_SV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__LBB_SV_CYCLE_TEST;
	int  Call__LBB_SV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__LBC_SV_CYCLE_TEST;
	int  Call__LBC_SV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__LBD_SV_CYCLE_TEST;
	int  Call__LBD_SV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__LBA_DV_CYCLE_TEST;
	int  Call__LBA_DV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__LBB_DV_CYCLE_TEST;
	int  Call__LBB_DV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__LBC_DV_CYCLE_TEST;
	int  Call__LBC_DV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__LBD_DV_CYCLE_TEST;
	int  Call__LBD_DV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	int  Fnc__LBx_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int vlv_type,const int lbx_index);

	CString Get__AVG_DATA(const int n_count, const double cur_data, const double pre_avg);
	void Fnc__Check_MIN_MAX_DATA(const int n_count, CII__VAR_STRING_CTRL* p_ch_min, CII__VAR_STRING_CTRL* p_ch_max, const double cur_data);
	//


public:
	CObj__LBx_TEST();
	~CObj__LBx_TEST();

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

