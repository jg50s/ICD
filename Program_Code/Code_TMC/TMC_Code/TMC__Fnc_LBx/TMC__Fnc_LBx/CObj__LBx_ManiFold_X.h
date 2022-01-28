#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CObj__LBx_ManiFold_X__DEF.h"


// ...
#define  _CFG__OTHER_CHM_SIZE						5
#define  CFG_LEAK_RATE__STEP_SIZE					7

#define  ALID__SV_DOOR_OPEN_ERROR					11
#define  ALID__LEAK_CHECK_BAD_RESULT_ALARM          12


class CObj__LBx_ManiFold_X : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//------------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;
	SCX__USER_LOG_CTRL xLOG_CTRL__LeakCheck_LLx;


	//------------------------------------------------------------------------------
	// INTERNAL PROPERTY

	CX__VAR_STRING_CTRL  sCH__OBJ_STATUS;
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	CX__VAR_STRING_CTRL  sCH__OBJ_ACTIVE_MODE;

	//
	CX__VAR_ANALOG_CTRL  aCH__PARA_SLOT_ID;

	//
	CX__VAR_ANALOG_CTRL  aCH__PARA_PREHEAT_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_COOLING_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_PREMATERIAL_SLOT;	

	//
	CX__VAR_ANALOG_CTRL  aCH__PARA_HANDSHAKE_SLOT;

	CX__VAR_STRING_CTRL  sCH__PRESSURE_STATUS;
	CX__VAR_STRING_CTRL  sCH__ROBOT_TRANSFER_FLAG;

	//
	CX__VAR_DIGITAL_CTRL dCH__CFG_LEAK_CHECK;

	// LEAK_CHECK PARA ...
	CX__VAR_ANALOG_CTRL  aCH__MON_LEAK_CHECK__TIME_COUNT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_LEAK_CHECK__OVER_PUMPING_TIME;
	CX__VAR_ANALOG_CTRL  aCH__CFG_LEAK_CHECK__STABLE_TIME;
	CX__VAR_ANALOG_CTRL  aCH__CFG_LEAK_CHECK__CHECK_TIME_MIN;
	CX__VAR_STRING_CTRL  sCH__MON_LEAK_CHECK__START_TIME;
	CX__VAR_STRING_CTRL  sCH__MON_LEAK_CHECK__END_TIME;
	CX__VAR_STRING_CTRL  sCH__MON_LEAK_CHECK__START_PRESSURE_TORR;
	CX__VAR_STRING_CTRL  sCH__MON_LEAK_CHECK__END_PRESSURE_TORR;
	CX__VAR_STRING_CTRL  sCH__MON_LEAK_CHECK__STEP_PRESSURE_TORR[CFG_LEAK_RATE__STEP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_LEAK_CHECK__STEP_LEAK_RATE[CFG_LEAK_RATE__STEP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_LEAK_CHECK__TOTAL_LEAK_RATE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_LEAK_CHECK__ALARM_RATE;

	// State ...
	CX__VAR_DIGITAL_CTRL dCH__PUMPING_STS_FLAG;
	CX__VAR_DIGITAL_CTRL dCH__VENTING_STS_FLAG;

	// Cycle Purge ...
	CX__VAR_ANALOG_CTRL  aCFG_CH__CYCLE_PURGE_PUMPDOWN_TIME_LIMIT;
	CX__VAR_ANALOG_CTRL  aCFG_CH__CYCLE_PURGE_COUNT;
	CX__VAR_STRING_CTRL  sCFG_CH__CYCLE_PURGE_CURRENT_COUNT;
	CX__VAR_STRING_CTRL  sCFG_CH__CYCLE_PURGE_SEQ_MSG;

	CX__VAR_ANALOG_CTRL  aCFG_PARTICLE_CHECK_SV_OP_CL_COUNT;
	CX__VAR_ANALOG_CTRL  aCFG_PARTICLE_CHECK_DV_OP_CL_COUNT;
	CX__VAR_ANALOG_CTRL  aCFG_PARTICLE_CHECK_PUMP_VENT_COUNT;
	//

	//------------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	CString sLLx_NAME;
	int iLBx_SLOT_SIZE;

	// LINK__OBJ_PHY ...
	CII_EXT_OBJECT__CTRL *pLBx_CHM__OBJ_CTRL;

	CX__VAR_STRING_CTRL  sEXT_CH__OBJ_STATUS;

	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_SLOT_ID;

	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_PREHEAT_TIME;
	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_COOLING_TIME;
	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_PREMATERIAL_SLOT;	

	CX__VAR_ANALOG_CTRL  aEXT_CH__PRESSURE_TORR;
	CX__VAR_DIGITAL_CTRL dEXT_CH__PRESSURE_STATUS;

	CX__VAR_DIGITAL_CTRL dEXT_CH__DOOR_VLV_STATUS_X[CFG_LLx__SLOT_SIZE];
	CX__VAR_DIGITAL_CTRL dEXT_CH__VAC_VLV_STATUS_X[CFG_LLx__SLOT_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__SLIT_VALVE_LOCK_FLAG_X[CFG_LLx__SLOT_SIZE];

	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_HEATER_USE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_HEATER_SOFT_VENT_USE;

	// OTHER OBJ_CHM ...
	int iOTHER_CHM__SIZE;

	CII_EXT_OBJECT__CTRL *pOther_CHM__OBJ_FNC_X[_CFG__OTHER_CHM_SIZE];
	CX__VAR_DIGITAL_CTRL dEXT_CH__OTHER_CHM__PUMPING_STS_FLAG_X[_CFG__OTHER_CHM_SIZE];

	CII_EXT_OBJECT__CTRL *pOther_CHM__OBJ_PHY_X[_CFG__OTHER_CHM_SIZE];
	CX__VAR_DIGITAL_CTRL dEXT_CH__Other_CHM__PRESSURE_STATUS_X[_CFG__OTHER_CHM_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__Other_CHM__PRESSURE_CTRL_FLAG_X[_CFG__OTHER_CHM_SIZE];

	// DB CFG ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_SETUP_TEST_MODE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_SETUP_AUTO_VENTING_PUMPING;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_SETUP_LLx_DOOR_SLOT_VLV_CONTROL;
	//


	//------------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable);

	// ...
	CString sMODE__PICK_READY;
	int  Call__PICK_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PICK_EXTEND;
	int  Call__PICK_EXTEND(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PICK_COMPLETE;
	int  Call__PICK_COMPLETE(CII_OBJECT__VARIABLE* p_variable);

	// ...
	CString sMODE__PLACE_READY;
	int  Call__PLACE_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PLACE_EXTEND;
	int  Call__PLACE_EXTEND(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PLACE_COMPLETE;
	int  Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE* p_variable);

	// ...
	CString sMODE__PUMP;
	int  Call__PUMP(CII_OBJECT__ALARM* p_alarm,CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__TRANSFER_PUMP;
	int  Call__TRANSFER_PUMP(CII_OBJECT__ALARM* p_alarm,CII_OBJECT__VARIABLE* p_variable);

	int  Fnc__PUMP(CII_OBJECT__ALARM* p_alarm,CII_OBJECT__VARIABLE* p_variable,const int transfer_flag = -1);

	// ...
	CString sMODE__VENT;
	int  Call__VENT(CII_OBJECT__VARIABLE* p_variable);

	// ...
	CString sMODE__LEAK_CHECK;
	int  Call__LEAK_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int  Fnc__LEAK_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	CString sMODE__PREPMATER;
	int  Call__PREPMATER(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__COMPMATER;
	int  Call__COMPMATER(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__IN_PROC;
	int  Call__IN_PROC(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__OUT_PROC;
	int  Call__OUT_PROC(CII_OBJECT__VARIABLE* p_variable);

	int  Fnc__OUT_PROC_With_ManiFoldType(CII_OBJECT__VARIABLE* p_variable);
	int  Fnc__OUT_PROC_With_SingleType(CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__DV_OPEN;
	CString sMODE__DV_TRANSFER_OPEN;
	int  Call__DV_OPEN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__DV_CLOSE;
	CString sMODE__DV_TRANSFER_CLOSE;
	int  Call__DV_CLOSE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm);

	//
	CString sMODE__SV_OPEN;
	CString sMODE__SV_TRANSFER_OPEN;
	int  Call__SV_OPEN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__SV_CLOSE;
	CString sMODE__SV_TRANSFER_CLOSE;
	int  Call__SV_CLOSE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm);

	//
	CString sMODE__ISOLATE;
	int  Call__ISOLATE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm);

	//
	CString sMODE__CYCLE_PURGE;
	int  Call__CYCLE_PURGE(CII_OBJECT__ALARM* p_alarm, CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__LIFT_PIN_UP;
	int  Call__LIFT_PIN_UP(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__LIFT_PIN_DOWN;
	int  Call__LIFT_PIN_DOWN(CII_OBJECT__VARIABLE* p_variable);

	// ...
	SCI__USER_LOG_CTRL* Get_Ptr__USER_LOG_CTRL(const CString& module_name);

	int  LeakCheck__LOG_MakeFile(const CString& module_name);
	int  LeakCheck__LOG_WriteMsg(const CString& module_name,const CString& log_msg);

	// ...
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Check__OBJECT_BUSY(const CString& obj_sts);

	// ...
	bool Is__ALL_DV_OPEN();
	bool Is__ANY_DV_OPEN();
	bool Is__SLOT_DV_OPEN();

	bool Is__ALL_SV_OPEN();
	bool Is__ALL_SV_CLOSE();
	bool Is__ANY_SV_OPEN();
	bool Is__SLOT_SV_OPEN();
	//


public:
	CObj__LBx_ManiFold_X();
	~CObj__LBx_ManiFold_X();

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
