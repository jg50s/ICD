#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


class CObj__TMC_SYSTEM_STD : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//------------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;


	//------------------------------------------------------------------------------
	// INTRENAL PROPERTY

	CX__VAR_STRING_CTRL sCH__MODULE_TIME;


	//------------------------------------------------------------------------------
	// EXTRENAL PROPERTY

	CII_EXT_OBJECT__CTRL *pTMC_SYS__OBJ_CTRL;

	CX__VAR_DIGITAL_CTRL dEXT_CH__OBJ_STATUS;


	//------------------------------------------------------------------------------
	CString sMODE__AUTO_INIT;
	int  Call__AUTO_INIT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__TIME_INIT;
	int  Call__TIME_INIT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__SYSTEM_INIT;
	int  Call__SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__SYSTEM_MAINT;
	int  Call__SYSTEM_MAINT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__CTC_TO_TMC;
	int  Call__CTC_TO_TMC(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__TMC_TO_CTC;
	int  Call__TMC_TO_CTC(CII_OBJECT__VARIABLE* p_variable);


public:
	CObj__TMC_SYSTEM_STD();
	~CObj__TMC_SYSTEM_STD();

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
