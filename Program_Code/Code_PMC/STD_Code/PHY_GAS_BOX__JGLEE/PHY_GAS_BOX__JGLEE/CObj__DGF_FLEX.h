#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Def.h"

#include "CObj__DGF_FLEX__DEF.h"


class CObj__DGF_FLEX : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;	

	SCX__USER_LOG_CTRL xLOG_CTRL;
	int iActive__SIM_MODE;
	//


	//-------------------------------------------------------------------------
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;
	CX__VAR_DIGITAL_CTRL dCFG_CH__VALVE_STATUS[_CFG__MAX_DGF_LEVEL][_CFG__MAX_VALVE];

	CX__VAR_ANALOG_CTRL  aCH__CENTER_Wt_SET_POINT;
	CX__VAR_STRING_CTRL  sCH__CTRL_OPEN_REQ;

	CX__VAR_ANALOG_CTRL	 aCH__MIN_LEVELx[_CFG__MAX_DGF_LEVEL];
	CX__VAR_ANALOG_CTRL  aCH__MAX_LEVELx[_CFG__MAX_DGF_LEVEL];

	CX__VAR_DIGITAL_CTRL dCH_PARA__ORIFICE_TYPE;

	// CFG ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_DGF_DEFAULT_CENTER_WEIGHT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_DGF_TEST_ROUTINE_GAS_NUMBER;
	CX__VAR_ANALOG_CTRL  aCH__CFG_DGF_TEST_ROUTINE_LOW_FLOW_GAS_NUMBER;
	CX__VAR_ANALOG_CTRL  aCH__CFG_DGF_TEST_ROUTINE_LOW_FLOW_ORIFICE_FLOWRATE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_DGF_TEST_ROUTINE_HIGH_FLOW_ORIFICE_FLOWRATE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_DGF_TEST_ROUTINE_FLOW_TIME;
	CX__VAR_ANALOG_CTRL  aCH__CFG_DGF_TEST_ROUTINE_BASELINE_TOLERANCE;
	CX__VAR_DIGITAL_CTRL dCH__CFG_DGF_INLET_PRESSURE_SAVE_TO_RECIPE;
	CX__VAR_DIGITAL_CTRL dCH__CFG_DGF_INLET_PRESSURE_CHECK;
	CX__VAR_ANALOG_CTRL  aCH__CFG_DGF_TOLERANCE_CHECK_DELAY;
	CX__VAR_ANALOG_CTRL  aCH__CFG_DGF_SOFT_TOLERANCE_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_DGF_HARD_TOLERANCE_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_DGF_WAFER_300M_PARTION;
	CX__VAR_ANALOG_CTRL  aCH__CFG_DGF_SOFT_TOLERANCE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_DGF_HARD_TOLERANCE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_DGF_DELAY_TIMER;
	CX__VAR_STRING_CTRL  sCH__CFG_DGF_MANOMETER_TYPE;
	//

	//-------------------------------------------------------------------------
	// LINK IO ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__ORIFICE_VALVE[_CFG__MAX_ORIFICE];

	CX__VAR_DIGITAL_CTRL dEXT_CH__BRANCH1_CENTER_VALVE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__BRANCH1_EDGE_VALVE;

	CX__VAR_DIGITAL_CTRL dEXT_CH__BRANCH2_CENTER_VALVE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__BRANCH2_EDGE_VALVE;

	CX__VAR_DIGITAL_CTRL dEXT_CH__CHAMBER_CENTER_VALVE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CHAMBER_EDGE_VALVE;

	CX__VAR_DIGITAL_CTRL dEXT_CH__VLV_2;
	CX__VAR_DIGITAL_CTRL dEXT_CH__VLV_4;

	//
	CX__VAR_DIGITAL_CTRL dEXT_CH__IO_VAC_SNS;

	// For Simulator Interlock Channel Initialize ...
	/*
	CX__VAR_DIGITAL_CTRL dEXT_CH__GasPerchg_ManVac_PSH2;
	CX__VAR_DIGITAL_CTRL dEXT_CH__Chamber_DeliverVac_PSH3;
	CX__VAR_DIGITAL_CTRL dEXT_CH__TunningGas_DeliverVac_PSH4;
	CX__VAR_DIGITAL_CTRL dEXT_CH__Scrubber_Switch_PSH8;
	CX__VAR_DIGITAL_CTRL dEXT_CH__N2Purge_Supply_PSH9;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CDAPress_Switch_Sts;
	CX__VAR_DIGITAL_CTRL dEXT_CH__Customer_GasDetect_Switch;
	CX__VAR_DIGITAL_CTRL dEXT_CH__Customer_Intlk_Switch;
	CX__VAR_DIGITAL_CTRL dEXT_CH__H2_Intlk_Switch;
	CX__VAR_DIGITAL_CTRL dEXT_CH__H2_Intlk_Switch_Installed;
	CX__VAR_DIGITAL_CTRL dEXT_CH__Conver_Intlk;
	CX__VAR_DIGITAL_CTRL dEXT_CH__WaterLeak_Detection_Sts;
	*/
	//

	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__ALL_CLOSE;
	int Call__ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__CONTROL;
	int Call__CONTROL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__ORIFICE_CTRL;
	int Call__ORIFICE_CTRL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__ALL_OPEN;
	int Call__ALL_OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__GASLINE_PUMP;
	int Call__GASLINE_PUMP(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__SAVE_LEVEL_VLV;
	int Call__SAVE_LEVEL_VLV(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	//
	int Fnc__CONTROL(const int level);

	void Fnc__WRITE_LOG(const CString& log_msg);
	//

	//-------------------------------------------------------------------------
	int Mon__STATUS(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//


public:
	CObj__DGF_FLEX();
	~CObj__DGF_FLEX();

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
