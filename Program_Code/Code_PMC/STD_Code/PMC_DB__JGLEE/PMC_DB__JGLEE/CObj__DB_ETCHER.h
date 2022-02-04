#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


class CObj__DB_ETCHER : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// SYSTEM CHANNEL ...
	CX__VAR_ANALOG_CTRL aCH__SYS_CHM_TEMPERATURE;
	CX__VAR_ANALOG_CTRL aCH__SYS_CHM_VOLUMN;

	CX__VAR_STRING_CTRL sCH__SYS_CTRL_NAME;
	CX__VAR_STRING_CTRL sCH__SYS_CTRL_MSG;
	CX__VAR_STRING_CTRL sCH__SYS_CTRL_LOCK;

	CX__VAR_STRING_CTRL sCH__SYS_ALWAYS_LOCK_FLAG;

	CX__VAR_STRING_CTRL sCH__SYS_FNC_NAME;
	CX__VAR_STRING_CTRL sCH__SYS_FNC_MSG;
	CX__VAR_STRING_CTRL sCH__SYS_FNC_CATEGORY;
	CX__VAR_STRING_CTRL sCH__SYS_FNC_LOCK;

	// RECIPE PARAMETER RANGE ...
	CX__VAR_ANALOG_CTRL aCH_RCP__EPD_TRIGGER_MIN;
	CX__VAR_ANALOG_CTRL aCH_RCP__EPD_TRIGGER_MAX;
	CX__VAR_ANALOG_CTRL aCH_RCP__EPD_TRIGGER_DEC;


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY


	//-------------------------------------------------------------------------
	CString sMODE__DB_CHECK;
	int  Call__DB_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//


public:
	CObj__DB_ETCHER();
	~CObj__DB_ETCHER();

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
