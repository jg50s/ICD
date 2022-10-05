#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


class CObj__ACTIVE_HANDOFF_INF : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;	

	SCX__USER_LOG_CTRL xLOG_CTRL;
	//

	//-------------------------------------------------------------------------
	// OBJ ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// CFG ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_TRANSFER_END_LIFT_PIN_DOWN;

	// LINK.TEST ...
	CX__VAR_DIGITAL_CTRL dCH__LINK_TEST_USE_LIFT_PIN_DOWN;
	//

	//-------------------------------------------------------------------------
	// OBJ.OPR_PMC ...
	CII_EXT_OBJECT__CTRL* pOBJ_CTRL__OPR_PMC;

	CX__VAR_DIGITAL_CTRL  dEXT_CH__OPR_OBJ_STATE;

	// OBJ.PM_SLOT ...
	bool bActive__OBJ_CTRL__PM_SLOT;
	CII_EXT_OBJECT__CTRL* pOBJ_CTRL__PM_SLOT;

	CString sLINK_MODE__PM_SLOT__CLOSE;
	CString sLINK_MODE__PM_SLOT__OPEN;

	// OBJ.SHUTTER ...
	bool bActive__OBJ_CTRL__SHUTTER;
	CII_EXT_OBJECT__CTRL* pOBJ_CTRL__SHUTTER;

	CString sLINK_MODE__SHUTTER__OPEN;
	CString sLINK_MODE__SHUTTER__CLOSE;

	// OBJ.LIFT_PIN ...
	bool bActive__OBJ_CTRL__LIFT_PIN;
	CII_EXT_OBJECT__CTRL* pOBJ_CTRL__LIFT_PIN;

	CString sLINK_MODE__LIFT_PIN_UP;
	CString sLIST_MODE__LIFT_PIN_DOWN;

	// LINK.SX & RX ...
	CString sEXT_MODE__S1;
	CString sEXT_MODE__S2;
	CString sEXT_MODE__S3;

	CString sEXT_MODE__R1;
	CString sEXT_MODE__R2;
	CString sEXT_MODE__R3;
	//

	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	CString	sMODE__TRANSFER_READY;
	int Call__TRANSFER_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__TRANSFER_END;
	int Call__TRANSFER_END(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	CString	sMODE__S1;
	int Call__S1(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__S2;
	int Call__S2(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__S3;
	int Call__S3(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__R1;
	int Call__R1(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__R2;
	int Call__R2(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__R3;
	int Call__R3(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__SX1;
	int Call__SX1(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__SX2;
	int Call__SX2(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__SX3;
	int Call__SX3(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__SX4;
	int Call__SX4(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__SX5;
	int Call__SX5(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__SX6;
	int Call__SX6(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__RX1;
	int Call__RX1(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__RX2;
	int Call__RX2(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__RX3;
	int Call__RX3(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__RX4;
	int Call__RX4(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__RX5;
	int Call__RX5(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString	sMODE__RX6;
	int Call__RX6(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	//

public:
	CObj__ACTIVE_HANDOFF_INF();
	~CObj__ACTIVE_HANDOFF_INF();

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
