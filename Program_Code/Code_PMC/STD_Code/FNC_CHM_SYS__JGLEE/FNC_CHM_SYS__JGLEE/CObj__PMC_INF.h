#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


// ...
#define STR__YES			"YES"


class CObj__PMC_INF : public __IOBJ__STD_TYPE
{
private:
	//------------------------------------------------------------
	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;
	CCommon_Error__USER_FNC     mERROR__USER_FNC;

	//------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL  xLOG_CTRL;
	//

	//------------------------------------------------------------
	// INTERNAL PROPERTY

	// TIME ...
	CX__VAR_STRING_CTRL  sCH__MODULE_TIME;
	CX__VAR_STRING_CTRL  sCH__LINK_NET_IP;
	CX__VAR_STRING_CTRL  sCH__LINK_TIME_ACTIVE;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_EQP_ID;
	CX__VAR_STRING_CTRL  sCH__INFO_EQP_NAME;

	CX__VAR_STRING_CTRL  sCH__INFO_EQP_NET_IP;
	CX__VAR_STRING_CTRL  sCH__INFO_EQP_NET_PORT;
	//

	//------------------------------------------------------------
	// EXTERNAL PROPERTY

	// OBJ_DB ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__ACTIVE_CALL_BY_CTC;

	// STEP.INFO ...
	CX__VAR_STRING_CTRL xEXT_CH__STEP_START;
	CX__VAR_STRING_CTRL xEXT_CH__STEP_END;


	// LINK.OBJ_MODE ...
	CString sEXT_MODE__SYSTEM_INIT;
	CString sEXT_MODE__SYSTEM_MAINT;

	CString sEXT_MODE__PUMP;
	CString sEXT_MODE__VENT;
	CString sEXT_MODE__LEAK_CHECK;
	CString sEXT_MODE__AUTO_PM;
	CString sEXT_MODE__PURGE;

	CString sEXT_MODE__SLOT_OPEN;
	CString sEXT_MODE__SLOT_CLOSE;
	CString sEXT_MODE__PIN_UP;
	CString sEXT_MODE__PIN_DOWN;

	CString sEXT_MODE__PICK_READY;
	CString sEXT_MODE__PICK_X_READY;
	CString sEXT_MODE__PICK_COMPLETE;
	CString sEXT_MODE__PICK_X_COMPLETE;

	CString sEXT_MODE__PLACE_READY;
	CString sEXT_MODE__PLACE_X_READY;
	CString sEXT_MODE__PLACE_COMPLETE;
	CString sEXT_MODE__PLACE_X_COMPLETE;

	CString sEXT_MODE__PRO_READY;
	CString sEXT_MODE__PRO_START;	
	CString sEXT_MODE__CLN_READY;
	CString sEXT_MODE__CLN_START;
	CString sEXT_MODE__PRE_READY;
	CString sEXT_MODE__PRE_START;
	CString sEXT_MODE__MNT_READY;
	CString sEXT_MODE__MNT_START;
	CString sEXT_MODE__JOB_START_READY;
	CString sEXT_MODE__JOB_END_READY;
	//

	//-------------------------------------------------------------------------
	// ...
	CString sMODE__AUTO_INIT;
	int  Call__AUTO_INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__TIME_INIT;
	int  Call__TIME_INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm);
	int  Fnc__TIME_INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__SYSTEM_INIT;
	int  Call__SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__SYSTEM_MAINT;
	int  Call__SYSTEM_MAINT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	CString sMODE__PUMP;
	int  Call__PUMP(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__VENT;
	int  Call__VENT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__LEAK_CHECK;
	int  Call__LEAK_CHECK(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__AUTO_PM;
	int  Call__AUTO_PM(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PURGE;
	int Call__PURGE(CII_OBJECT__VARIABLE *p_variable);

	// ...
	CString sMODE__SLOT_OPEN;
	int Call__SLOT_OPEN(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__SLOT_CLOSE;
	int Call__SLOT_CLOSE(CII_OBJECT__VARIABLE *p_variable);

	// ...
	CString sMODE__PIN_UP;
	int Call__PIN_UP(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PIN_DOWN;
	int Call__PIN_DOWN(CII_OBJECT__VARIABLE *p_variable);

	// ...
	CString sMODE__PICK_READY;
	int  Call__PICK_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PICK_X_READY;
	int  Call__PICK_X_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PICK_COMPLETE;
	int  Call__PICK_COMPLETE(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PICK_X_COMPLETE;
	int  Call__PICK_X_COMPLETE(CII_OBJECT__VARIABLE* p_variable);

	// ...
	CString sMODE__PLACE_READY;
	int  Call__PLACE_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PLACE_X_READY;
	int  Call__PLACE_X_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PLACE_COMPLETE;
	int  Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PLACE_X_CONPLETE;
	int  Call__PLACE_X_COMPLETE(CII_OBJECT__VARIABLE* p_variable);

	// ...
	CString sMODE__PRO_READY;
	int  Call__PRO_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PRO_START;
	int  Call__PRO_START(CII_OBJECT__VARIABLE* p_variable);

	// ...
	CString sMODE__CLN_READY;
	int  Call__CLN_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__CLN_START;
	int  Call__CLN_START(CII_OBJECT__VARIABLE* p_variable);

	// ...
	CString sMODE__PRE_READY;
	int  Call__PRE_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PRE_START;
	int  Call__PRE_START(CII_OBJECT__VARIABLE* p_variable);

	// ...
	CString sMODE__MNT_READY;
	int  Call__MNT_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__MNT_START;
	int  Call__MNT_START(CII_OBJECT__VARIABLE* p_variable);

	// ...
	CString sMODE__JOB_START_READY;
	int  Call__JOB_START_READY(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__JOB_END_READY;
	int  Call__JOB_END_READY(CII_OBJECT__VARIABLE* p_variable);
	//

	//-------------------------------------------------------------------------
	void Mon__STATUS(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	//

public:
	CObj__PMC_INF();
	~CObj__PMC_INF();

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
