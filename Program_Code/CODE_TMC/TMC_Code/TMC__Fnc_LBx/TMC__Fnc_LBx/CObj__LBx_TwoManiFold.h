#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CObj__LBx_TwoManiFold__DEF.h"


#define  ALID__SV_DOOR_OPEN_ERROR					11


class CObj__LBx_TwoManiFold : public __IOBJ__STD_TYPE
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

	//
	CX__VAR_ANALOG_CTRL  aCH__PARA_HANDSHAKE_SLOT;

	CX__VAR_STRING_CTRL  sCH__PRESSURE_STATUS;
	CX__VAR_STRING_CTRL  sCH__ROBOT_TRANSFER_FLAG;
	//

	//------------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	// OBJ INFO -----
	CString sLBx__MODULE_NAME;

	// LBx MANIFOLD ...
	CII_EXT_OBJECT__CTRL *pLBx_MANIFOLD__OBJ_CTRL;

	// LBx CHM OBJECT -----
	CII_EXT_OBJECT__CTRL *pLBx_CHM__OBJ_CTRL;

	CX__VAR_STRING_CTRL  sEXT_CH__OBJ_STATUS;

	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_PREHEAT_TIME;
	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_COOLING_TIME;
	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_PREMATERIAL_SLOT;	

	CX__VAR_DIGITAL_CTRL dEXT_CH__PRESSURE_STATUS;

	CX__VAR_DIGITAL_CTRL dEXT_CH__DOOR_VLV_STATUS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__VAC_VLV_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__SLIT_VALVE_LOCK_FLAG;

	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_HEATER_USE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_HEATER_SOFT_VENT_USE;

	//
	CII_EXT_OBJECT__CTRL *pOther_LBx_CHM__OBJ_CTRL;

	CX__VAR_DIGITAL_CTRL dEXT_CH__Other_LBx__PRESSURE_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__Other_LBx__PRESSURE_CTRL_FLAG;
	CX__VAR_DIGITAL_CTRL dEXT_CH__OTHER_LBX_PUMPING_STS_FLAG;
	CX__VAR_DIGITAL_CTRL dEXT_CH__OTHER_LBX_VENTING_STS_FLAG;
	CX__VAR_DIGITAL_CTRL dEXT_CH__Other_LBx__VAC_VLV_STATUS;

	// LBx VLV OBJECT -----
	
	// Press VLV OBJECT -----
	CII_EXT_OBJECT__CTRL *pPress_VLV__OBJ_CTRL;

	CX__VAR_DIGITAL_CTRL dCH__PUMPING_STS_FLAG;
	CX__VAR_DIGITAL_CTRL dCH__VENTING_STS_FLAG;

	// Cycle Purge !!
	CX__VAR_ANALOG_CTRL  aCFG_CH__CYCLE_PURGE_PUMPDOWN_TIME_LIMIT;
	CX__VAR_ANALOG_CTRL  aCFG_CH__CYCLE_PURGE_COUNT;
	CX__VAR_STRING_CTRL  sCFG_CH__CYCLE_PURGE_CURRENT_COUNT;
	CX__VAR_STRING_CTRL  sCFG_CH__CYCLE_PURGE_SEQ_MSG;

	CX__VAR_ANALOG_CTRL  aCFG_PARTICLE_CHECK_SV_OP_CL_COUNT;
	CX__VAR_ANALOG_CTRL  aCFG_PARTICLE_CHECK_DV_OP_CL_COUNT;
	CX__VAR_ANALOG_CTRL  aCFG_PARTICLE_CHECK_PUMP_VENT_COUNT;


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
	int  Call__LEAK_CHECK(CII_OBJECT__VARIABLE* p_variable);

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


	//.....
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Check__OBJECT_BUSY(const CString& obj_sts);
	//


public:
	CObj__LBx_TwoManiFold();
	~CObj__LBx_TwoManiFold();

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
