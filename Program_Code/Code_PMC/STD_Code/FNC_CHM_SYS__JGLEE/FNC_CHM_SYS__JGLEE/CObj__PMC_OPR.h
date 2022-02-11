#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Def.h"


class CObj__PMC_OPR : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;
	CCommon_Error__USER_FNC     mERROR__USER_FNC;

	//-------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL  xLOG_CTRL;
	int iSIM_FLAG;


	//-------------------------------------------------------------------------
	CX__VAR_DIGITAL_CTRL xCH__OBJ_STATUS;
	CX__VAR_STRING_CTRL  sCH__OBJ_STATUS_VIRTUAL;

	CX__VAR_STRING_CTRL  sCH__PARA_PROCESS_TIME_SEC;
	CX__VAR_STRING_CTRL  sCH__APP_PROCESS_TIME_COUNT;


	//-------------------------------------------------------------------------
	CX__VAR_STRING_CTRL  sEXT_CH__SYSTEM_MSG;
	CX__VAR_STRING_CTRL  sEXT_CH__FNC_MSG;

	CX__VAR_STRING_CTRL  sEXT_CH__SYSTEM_SETUP_REQ;

	//
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_TRANSFER_MODE;

	CX__VAR_STRING_CTRL  sEXT_CH__SHUTTER_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__LIFT_PIN_STATUS;

	CX__VAR_STRING_CTRL  sEXT_CH__CHM_VAC_SNS;
	CX__VAR_STRING_CTRL  sEXT_CH__CHM_ATM_SNS;

	CX__VAR_DIGITAL_CTRL dEXT_CH__WAFER_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__RECIPE_NAME;
	CX__VAR_STRING_CTRL  sEXT_CH__CHM_STAGE_REPORT_TO_CTC;
	CX__VAR_STRING_CTRL  sEXT_CH__CHM_PRESSURE_VALUE;

	CX__VAR_DIGITAL_CTRL dEXT_CH__CHM_PRC_STS;
	CX__VAR_STRING_CTRL  sEXT_CH__CHM_PRC_TOTAL_TIME_TO_CTC;
	CX__VAR_STRING_CTRL  sEXT_CH__CHM_PRC_CHANGE_TIME_TO_CTC;


	//-------------------------------------------------------------------------
	// ...
	bool bActive__OBJ_CTRL__AUTO_PM;
	CII_EXT_OBJECT__CTRL* pOBJ_CTRL__AUTO_PM;
	CString sLINK_MODE__AUTO_PM;

	bool bActive__OBJ_CTRL__SHUTTER;
	CII_EXT_OBJECT__CTRL* pOBJ_CTRL__SHUTTER;
	CString sLINK_MODE__SHUTTER__CLOSE;
	CString sLINK_MODE__SHUTTER__OPEN;

	bool bActive__OBJ_CTRL__LIFT_PIN;
	CII_EXT_OBJECT__CTRL* pOBJ_CTRL__LIFT_PIN;
	CString sLINK_MODE__LIFT_PIN__TRANSFER_READY;
	CString sLINK_MODE__LIFT_PIN__TRANSFER_COMPLETE;
	CString sLINK_MODE__LIFT_PIN__PROCESS_READY;

	bool bActive__OBJ_CTRL__PM_SLOT;
	CII_EXT_OBJECT__CTRL* pOBJ_CTRL__PM_SLOT;
	CString sLINK_MODE__PM_SLOT__CLOSE;
	CString sLINK_MODE__PM_SLOT__OPEN;

	bool bActive__OBJ_CTRL__CHAMBER;
	CII_EXT_OBJECT__CTRL* pOBJ_CTRL__CHAMBER;

	// ...
	CString sEXT_MODE__INIT;
	CString sEXT_MODE__MAINT;
	CString sEXT_MODE__PUMP;
	CString sEXT_MODE__VENT;
	CString sEXT_MODE__LEAK_CHECK;
	CString sEXT_MODE__PURGE;

	CString sEXT_MODE__PRO_READY;
	CString sEXT_MODE__PRO_START;
	CString sEXT_MODE__CLN_READY;
	CString sEXT_MODE__CLN_START;
	CString sEXT_MODE__MNT_READY;
	CString sEXT_MODE__MNT_START;
	CString sEXT_MODE__JOB_START_READY;
	CString sEXT_MODE__JOB_END_READY;
	//

	// ...
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__TRANSFER_INIT;
	int Call__TRANSFER_INIT(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__MAINT;
	int Call__MAINT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__SETUP;
	int Call__SETUP(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PUMP;
	int Call__PUMP(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__VENT;
	int Call__VENT(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__LEAK_CHECK;
	int Call__LEAK_CHECK(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__AUTO_PM;
	int Call__AUTO_PM(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PURGE;
	int Call__PURGE(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PICK_READY;
	int Call__PICK_READY(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PICK_X_READY;
	int Call__PICK_X_READY(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PICK_COMPLETE;
	int Call__PICK_COMPLETE(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PICK_X_COMPLETE;
	int Call__PICK_X_COMPLETE(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PLACE_READY;
	int Call__PLACE_READY(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PLACE_X_READY;
	int Call__PLACE_X_READY(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PLACE_COMPLETE;
	int Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PLACE_X_COMPLETE;
	int Call__PLACE_X_COMPLETE(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PRO_READY;
	int Call__PRO_READY(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PRO_START;
	int Call__PRO_START(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__CLN_READY;
	int Call__CLN_READY(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__CLN_START;
	int Call__CLN_START(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__MNT_READY;
	int Call__MNT_READY(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__MNT_START;
	int Call__MNT_START(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__JOB_START_READY;
	int Call__JOB_START_READY(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__JOB_END_READY;
	int Call__JOB_END_READY(CII_OBJECT__VARIABLE *p_variable);

	// ...
	void Mon__STATUS(CII_OBJECT__VARIABLE *p_variable);

	// ...
	int Fnc__TRANSFER_READY(CII_OBJECT__VARIABLE *p_variable);
	int Fnc__TRANSFER_COMPLETE(CII_OBJECT__VARIABLE *p_variable);
	//


public:
	CObj__PMC_OPR();
	~CObj__PMC_OPR();

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
