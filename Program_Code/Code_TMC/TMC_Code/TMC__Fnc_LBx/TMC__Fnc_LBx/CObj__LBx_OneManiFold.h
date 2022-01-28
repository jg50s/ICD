#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CObj__LBx_OneManiFold__DEF.h"


#define CFG_ACTION__SIZE			2
#define _ACT_INDEX__UP				0
#define _ACT_INDEX__DOWN			1


class CObj__LBx_OneManiFold : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//------------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;


	//------------------------------------------------------------------------------
	// INTERNAL PROPERTY

	CX__VAR_STRING_CTRL  sCH__OBJ_STATUS;
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	CX__VAR_STRING_CTRL  sCH__OBJ_ACTIVE_MODE;

	//
	CX__VAR_ANALOG_CTRL  aCH__PARA_PREHEAT_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_COOLING_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_PREMATERIAL_SLOT;	

	CX__VAR_ANALOG_CTRL  aCH__PARA_HANDSHAKE_SLOT;

	CX__VAR_STRING_CTRL  sCH__PRESSURE_STATUS;
	CX__VAR_STRING_CTRL  sCH__ROBOT_TRANSFER_FLAG;

	CX__VAR_DIGITAL_CTRL dCH__PUMPING_STS_FLAG;
	CX__VAR_DIGITAL_CTRL dCH__VENTING_STS_FLAG;
	//

	//------------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	// LLx MANIFOLD ...
	CII_EXT_OBJECT__CTRL *pLLx_UTILITY__OBJ_CTRL;

	// LLx CHM OBJECT ...
	CII_EXT_OBJECT__CTRL *pLLx_CHM__OBJ_CTRL;

	CX__VAR_STRING_CTRL  sEXT_CH__OBJ_STATUS;

	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_PREHEAT_TIME;
	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_COOLING_TIME;
	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_PREMATERIAL_SLOT;	

	CX__VAR_DIGITAL_CTRL dEXT_CH__PRESSURE_STATUS;

	CX__VAR_DIGITAL_CTRL dEXT_CH__VAC_VLV_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__SLIT_VALVE_LOCK_FLAG;

	// Cycle Purge ...
	CX__VAR_ANALOG_CTRL  aCFG_CH__CYCLE_PURGE_PUMPDOWN_TIME_LIMIT;
	CX__VAR_ANALOG_CTRL  aCFG_CH__CYCLE_PURGE_COUNT;
	CX__VAR_STRING_CTRL  sCFG_CH__CYCLE_PURGE_CURRENT_COUNT;
	CX__VAR_STRING_CTRL  sCFG_CH__CYCLE_PURGE_SEQ_MSG;

	CX__VAR_ANALOG_CTRL  aCFG_PARTICLE_CHECK_SV_OP_CL_COUNT;
	CX__VAR_ANALOG_CTRL  aCFG_PARTICLE_CHECK_DV_OP_CL_COUNT;
	CX__VAR_ANALOG_CTRL  aCFG_PARTICLE_CHECK_PUMP_VENT_COUNT;

	// Cycle Lift_Pin ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_CYCLE_LIFT_PIN__COUNT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_CYCLE_LIFT_PIN__UP_DELAY_SEC;
	CX__VAR_ANALOG_CTRL  aCH__CFG_CYCLE_LIFT_PIN__DOWN_DELAY_SEC;

	CX__VAR_STRING_CTRL  sCH__CUR_CYCLE_LIFT_PIN__COUNT;
	CX__VAR_STRING_CTRL  sCH__CUR_CYCLE_LIFT_PIN__UP_DELAY_SEC;
	CX__VAR_STRING_CTRL  sCH__CUR_CYCLE_LIFT_PIN__DOWN_DELAY_SEC;

	CX__VAR_STRING_CTRL  sCH__ACTIVE_CYCLE_LIFT_PIN;

	CX__VAR_STRING_CTRL  sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_CUR[CFG_ACTION__SIZE];
	CX__VAR_STRING_CTRL  sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_AVG[CFG_ACTION__SIZE];
	CX__VAR_STRING_CTRL  sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_MIN[CFG_ACTION__SIZE];
	CX__VAR_STRING_CTRL  sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_MAX[CFG_ACTION__SIZE];
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
	int  Call__LEAK_CHECK(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PREPMATER;
	int  Call__PREPMATER(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__COMPMATER;
	int  Call__COMPMATER(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__IN_PROC;
	int  Call__IN_PROC(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__OUT_PROC;
	int  Call__OUT_PROC(CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__DV_OPEN;
	CString sMODE__DV_TRANSFER_OPEN;
	int  Call__DV_OPEN(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__DV_CLOSE;
	CString sMODE__DV_TRANSFER_CLOSE;
	int  Call__DV_CLOSE(CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__SV_OPEN;
	CString sMODE__SV_TRANSFER_OPEN;
	int  Call__SV_OPEN(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__SV_CLOSE;
	CString sMODE__SV_TRANSFER_CLOSE;
	int  Call__SV_CLOSE(CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__ISOLATE;
	int  Call__ISOLATE(CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__CYCLE_PURGE;
	int  Call__CYCLE_PURGE(CII_OBJECT__ALARM* p_alarm, CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__LIFT_PIN_UP;
	int  Call__LIFT_PIN_UP(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__LIFT_PIN_DOWN;
	int  Call__LIFT_PIN_DOWN(CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__CYCLE_LIFT_PIN;
	int  Call__CYCLE_LIFT_PIN(CII_OBJECT__VARIABLE* p_variable);
	int  Fnc__CYCLE_LIFT_PIN(CII_OBJECT__VARIABLE* p_variable);

	int  _Update__ACTION_AVG_MIN_MAX(const int db_i,const double cur_sec,const int n_count);
	//

	// ...
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Check__OBJECT_BUSY(const CString& obj_sts);
	//


public:
	CObj__LBx_OneManiFold();
	~CObj__LBx_OneManiFold();

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
