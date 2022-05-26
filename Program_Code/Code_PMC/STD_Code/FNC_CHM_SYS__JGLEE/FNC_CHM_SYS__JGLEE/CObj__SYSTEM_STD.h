#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__SYSTEM_STD__DEF.h"


class CObj__SYSTEM_STD : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;
	CCommon_Error__USER_FNC     mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xLOG_CTRL;
	//

	//-------------------------------------------------------------------------
	// OBJ ...
	CX__VAR_STRING_CTRL  sCH__OBJ_TIMER;

	// CFG :SYSTEM ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_CHAMBER_MODE;
	CX__VAR_DIGITAL_CTRL dCH__CFG_WAFER_STATUS;

	CX__VAR_ANALOG_CTRL  aCH__CFG_PART_STABLE_SEC;

	// CFG : RF_SYS ..
	CX__VAR_DIGITAL_CTRL dCH__CFG_SYS_INIT__RF_GEN_X[_RF_SYS__GEN_SIZE];
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_NAME__RF_GEN_X[_RF_SYS__GEN_SIZE];
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_ACTIVE__RF_GEN_X[_RF_SYS__GEN_SIZE];

	CX__VAR_DIGITAL_CTRL dCH__CFG_SYS_INIT__RF_MAT_X[_RF_SYS__MAT_SIZE];
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_NAME__RF_MAT_X[_RF_SYS__MAT_SIZE];
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_ACTIVE__RF_MAT_X[_RF_SYS__MAT_SIZE];

	CX__VAR_DIGITAL_CTRL dCH__CFG_SYS_INIT__ESC_DC_SUPPLY;
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_NAME__ESC_DC_SUPPLY;
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_ACTIVE__ESC_DC_SUPPLY;

	CX__VAR_DIGITAL_CTRL dCH__CFG_SYS_INIT__ESC_BACK_HE;
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_NAME__ESC_BACK_HE;
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_ACTIVE__ESC_BACK_HE;

	// CFG : HEATER_SYS ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_SYS_INIT__HEATER_X[_HTR_SYS__PART_SIZE];
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_NAME__HEATER_X[_HTR_SYS__PART_SIZE];
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_ACTIVE__HEATER_X[_HTR_SYS__PART_SIZE];

	// CFG : CHAMBER ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_SYS_INIT_CHM_SLOT_VALVE_CLOSE;
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_NAME_CHM_SLOT_VALVE_CLOSE;
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_ACTIVE_CHM_SLOT_VALVE_CLOSE;

	CX__VAR_DIGITAL_CTRL dCH__CFG_SYS_INIT_CHM_LIFT_PIN_DOWN;
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_NAME_CHM_LIFT_PIN_DOWN;
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_ACTIVE_CHM_LIFT_PIN_DOWN;

	CX__VAR_DIGITAL_CTRL dCH__CFG_SYS_INIT_CHM_DECHUCK;
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_NAME_CHM_DECHUCK;
	CX__VAR_STRING_CTRL  sCH__LINK_OBJ_ACTIVE_CHM_DECHUCK;
	//

	//-------------------------------------------------------------------------
	// OBJ : DB_INF
	CX__VAR_DIGITAL_CTRL dEXT_CH__WAFER_STATUS;
	
	// OBJ : DB_SYS
	CX__VAR_STRING_CTRL	 sEXT_CH__FNC_MSG;

	// OBJ : LINK ...
	int iOBJ_SIZE;

	CStringArray sList__OBJ_NAME;	
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__LIST[_LINK_OBJ__MAX];

	// OBJ : RF_SYS ...
	int iRF_SYS__GEN_SIZE;
	CStringArray sList__RF_SYS__GEN_NAME;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__RF_SYS__GEN_X[_RF_SYS__GEN_SIZE];

	int iRF_SYS__MAT_SIZE;
	CStringArray sList__RF_SYS__MAT_NAME;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__RF_SYS__MAT_X[_RF_SYS__MAT_SIZE];

	bool bACTIVE_RF_SYS__ESC_DC_SUPPLY;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__RF_SYS_ESC_DC_SUPPLY;

	bool bACTIVE_RF_SYS__ESC_BACK_HE;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__RF_SYS_ESC_BACK_HE;

	// OBJ : HTR_SYS ...
	int iHTR_SYS__PART_SIZE;
	CStringArray sList__HTR_SYS__PART_NAME;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__HTR_SYS__PART_X[_HTR_SYS__PART_SIZE];

	// OBJ : CHAMBER ...
	BOOL bACTIVE_CHM__SLOT_VALVE;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__CHM_SLOT_VALVE;

	BOOL bACTIVE_CHM__LIFT_PIN;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__CHM_LIFT_PIN;

	BOOL bACTIVE_CHM__DECHUCK;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__CHM_DECHUCK;
	//

	//-------------------------------------------------------------------------
	CString sMODE__SYSTEM_INIT;
	int Call__SYSTEM_INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Fnc__SYSTEM_INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__SYSTEM_MAINT;
	int Call__SYSTEM_MAINT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__TRANSFER_INIT;
	int Call__TRANSFER_INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__WAFER_UPDATE;
	int Call__WAFER_UPDATE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	int	 Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id);
	void Alarm__POST_CHECK(CII_OBJECT__ALARM *p_alarm, CString msg, const int alarm_id);
	//

public:
	CObj__SYSTEM_STD();
	~CObj__SYSTEM_STD();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
