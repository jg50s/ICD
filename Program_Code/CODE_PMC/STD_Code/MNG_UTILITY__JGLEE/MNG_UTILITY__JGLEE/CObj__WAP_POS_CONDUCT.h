#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__WAP_POS_CONDUCT__ALID.h"
#include "CObj__WAP_POS_CONDUCT__DEF.h"


class CObj__WAP_POS_CONDUCT : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	// ...
	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;
	CCommon_Error__USER_FNC     mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xLOG_CTRL;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// SYSTEM CHANNEL .....
	CX__VAR_STRING_CTRL  xCH__OBJ_MSG;

	CX__VAR_STRING_CTRL  xCH__AUTO_START_CTRL;

	// PARAMETER .....
	// C-RING Gap Type
	CX__VAR_DIGITAL_CTRL dCH_CFG__C_RING_GAP_TYPE;

	// TEST GAS TYPE
	CX__VAR_DIGITAL_CTRL dCH_PARA__TEST_GAS_TYPE;
	CX__VAR_ANALOG_CTRL  aCH_PARA__TEST_GAS_FLOW;

	CX__VAR_STRING_CTRL  sCH__CUR_TEST_GAS_NAME;

	// TEST INFO
	CX__VAR_STRING_CTRL  sCH_PARA__TEST_DATE;
	CX__VAR_STRING_CTRL  sCH_PARA__TEST_TIME;

	// VLV POS LIST
	CX__VAR_ANALOG_CTRL  aCH_PARA__VLV_POS_LIST[CFG__TEST_LIST];

	// CUR PRESSURE
	CX__VAR_STRING_CTRL  sCH_PARA__CUR_PRESS_LIST[CFG__TEST_LIST];

	// CONDUCT RESULT
	CX__VAR_STRING_CTRL  sCH_SIM__CONDUCT_RESULT[CFG__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH_NEW__CONDUCT_RESULT[CFG__TEST_LIST];
	CX__VAR_STRING_CTRL  sCH_PARA__CONDUCT_RESULT[CFG__TEST_LIST];

	// VLV REF LIST
	CX__VAR_ANALOG_CTRL  aCH_PARA__VLV_REF_LIST[CFG__TEST_LIST];

	// RESULT 
	CX__VAR_STRING_CTRL  sCH__RESULT_NEW_STRING;
	CX__VAR_STRING_CTRL  sCH__RESULT_CUR_STRING;
	CX__VAR_STRING_CTRL  sCH__RESULT_MOVE_STRING;

	CX__VAR_STRING_CTRL  sCH__RESULT_MSG;

	CX__VAR_STRING_CTRL  sCH__RESULT_SAVE_FLAG;
	CX__VAR_STRING_CTRL  sCH__RESULT_SAVE_DATE;

	// REF STRING
	CX__VAR_STRING_CTRL  sCH__REF_STRING;

	// CHECK TIME COUNT
	CX__VAR_STRING_CTRL  sCH_PARA__CHECK_TIME_COUNT;
	CX__VAR_STRING_CTRL  sCH_PARA__POS_PRESS_CHECK__TIME_COUNT;

	// SIM - MOVE
	CX__VAR_ANALOG_CTRL  aCH__SIM_MOVE_OFFSET;
	CX__VAR_DIGITAL_CTRL dCH__SIM_MOVE_LOOKUP;
	CX__VAR_DIGITAL_CTRL dCH__SIM_MOVE_DATA_TYPE;

	CX__VAR_ANALOG_CTRL  aCH__SIM_MOVE_ERROR_RANGE;
	CX__VAR_ANALOG_CTRL  aCH__SIM_MOVE_ERROR_X_MIN;
	CX__VAR_ANALOG_CTRL  aCH__SIM_MOVE_ERROR_X_MAX;

	CX__VAR_STRING_CTRL  sCH__SIM_MOVE_CHECK_FLAG;
	CX__VAR_STRING_CTRL  sCH__SIM_MOVE_SCAN_FLAG;

	// CONFIG ...
	CX__VAR_ANALOG_CTRL  aCH_CFG__FLOW_DELAY_SEC;
	CX__VAR_ANALOG_CTRL  aCH_CFG__POS_PRESS_CHECK__FLOW_DELAY_SEC;

	CX__VAR_ANALOG_CTRL  aCH_CFG__PRESSURE_STABLE_DELAY_SEC;
	CX__VAR_ANALOG_CTRL  aCH_CFG__POS_PRESS_CHECK__PRESSURE_STABLE_DELAY_SEC;

	CX__VAR_DIGITAL_CTRL dCH_CFG__TEST_ORDER;

	// SPEC TEST ...
	CX__VAR_DIGITAL_CTRL dCH_CFG__WAP_SPEC_TEST__APPLY_MODE;

	CX__VAR_ANALOG_CTRL  aCH_CFG__WAP_SPEC_TEST__GAS_FLOW;
	CX__VAR_ANALOG_CTRL  aCH_CFG__WAP_SPEC_TEST__POSITION;
	CX__VAR_ANALOG_CTRL  aCH_CFG__WAP_SPEC_TEST__PRESSURE_MIN;
	CX__VAR_ANALOG_CTRL  aCH_CFG__WAP_SPEC_TEST__PRESSURE_MAX;
	CX__VAR_ANALOG_CTRL  aCH_CFG__WAP_SPEC_TEST__STABLE_TIME;
	CX__VAR_ANALOG_CTRL  aCH_CFG__WAP_SPEC_TEST__CHECK_TIME;

	// RESULT : POSITION & PRESSURE ...
	CX__VAR_STRING_CTRL  sCH__RESULT_REF_POSITION_PRESSURE_STRING;
	CX__VAR_STRING_CTRL  sCH__RESULT_CUR_POSITION_PRESSURE_STRING;

	CX__VAR_DIGITAL_CTRL dCH_CFG__POS_PRESS_CHECK__GAS_TYPE;
	CX__VAR_ANALOG_CTRL  aCH_CFG__POS_PRESS_CHECK__GAS_FLOW;
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// DB - SYS
	CX__VAR_STRING_CTRL  sEXT_CH__SYSTEM_MSG;
	CX__VAR_STRING_CTRL	 sEXT_CH__FNC_MSG;

	CX__VAR_STRING_CTRL  sEXT_CH__CHM_PM_ITEM__WAP_CONDUCTANCE_FLAG;

	// SYSTEM CHANNEL
	CX__VAR_STRING_CTRL  sEXT_CH__SYS_FNC_NAME;
	CX__VAR_STRING_CTRL  sEXT_CH__SYS_FNC_MSG;
	CX__VAR_STRING_CTRL  sEXT_CH__SYS_FNC_LOCK;

	// CH.CHM.PRESSURE
	CX__VAR_STRING_CTRL  sEXT_CH__CHM_PRESSURE;

	// CH.DGF_CENTER_WT_SP
	CX__VAR_STRING_CTRL  sEXT_CH__DGF_CENTER_WT_SP;

	// OBJ - CHM CTRL .....
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__CHM;

	// OBJ - WAP CTRL .....
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__WAP;

	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_TRG_POS;
	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_PRESET_POS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__PARA_CONTROL_TYPE;

	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_C_Ring_Offset_Move;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_C_Ring_Offset_Check_Auto_Mode;	

	CX__VAR_STRING_CTRL  sEXT_CH__WAP__PARA_INITIAL_CALL_FLAG;

	// OBJ - FNC MFCx .....
	CII_EXT_OBJECT__CTRL* pOBJ_CTRL__FNC_MFC;

	CX__VAR_DIGITAL_CTRL dEXT_CH__FNC_MFC__PARA_MFC_TYPE;
	CX__VAR_ANALOG_CTRL  aEXT_CH__FNC_MFC__PARA_MFC_FLOW;

	// OBJ - MFCx CTRL .....
	int iSIZE__OBJ_MFCx;

	CX__VAR_STRING_CTRL  sEXT_CH__PARA_MFCx_GAS_NAME[CFG__MFC_SIZE];
	//


	//-------------------------------------------------------------------------
	// ...
	CString sMODE__POS_CONDUCT;
	int  Call__POS_CONDUCT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	int  Fnc__POS_CONDUCT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int  Fnc__LOWER_POS_CONDUCT(CII_OBJECT__VARIABLE *p_variable,
								CII_OBJECT__ALARM *p_alarm,
								const CString& vlv_pos,
								const CString& gas_name,
								const CString& gas_flow,
								const int db_index);
	int  Fnc__SPEC_TEST(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	int  Get__REF_CONDUCTANCE(const CString& gap_type,
							  CStringArray& l_ref_pos,
							  CStringArray& l_ref_data);

	// ...
	CString sMODE__POSITION_PRESSURE_CHECK;
	int  Call__POSITION_PRESSURE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	int  Init__POSITION_PRESSURE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	int  Fnc__POSITION_PRESSURE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	int  End__POSITION_PRESSURE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	int  Fnc_Move__POSITION_PRESSURE_CHECK(CII_OBJECT__VARIABLE *p_variable,
										   CII_OBJECT__ALARM *p_alarm,
										   const CString& str_pos);

	int  Fnc__REF_POS_PRESS_DATA(CStringArray& l_ref_pos,CStringArray& l_ref_press);
	int  _Fnc__REF_POS_PRESS_DATA(CStringArray& l_pos,CStringArray& l_press);

	// ...
	CString sMODE__DATA_SIM;
	int  Call__DATA_SIM(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	double Fnc__GET_DATA_FROM_LOOKUP_TABLE(const double x_pos,
										   const CStringArray& l_x,
										   const CStringArray& l_y);

	int   Fnc__SIM_MOVE_CAL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int   Fnc__SIM_MOVE_CAL(CII_OBJECT__VARIABLE *p_variable,
							CII_OBJECT__ALARM *p_alarm,
							const int scan_flag,
							int& r_result,
							double& r_x_err,
							double& r_y_err);

	int   Fnc__SIM_SCAN_CAL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	CString sMODE__PULSE_SCAN;
	int  Call__PULSE_SCAN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//

	//-------------------------------------------------------------------------
	void  Mon__STATUS_CTRL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	int   Get__Gas_Type_Index(const CString& str_gas_type);
	//


public:
	CObj__WAP_POS_CONDUCT();
	~CObj__WAP_POS_CONDUCT();

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
