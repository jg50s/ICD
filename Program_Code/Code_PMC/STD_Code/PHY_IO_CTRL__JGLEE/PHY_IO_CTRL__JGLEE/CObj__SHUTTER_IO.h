#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


class CObj__SHUTTER_IO : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	SCX__USER_LOG_CTRL xI_LOG_CTRL;
	int iActive__SIM_MODE;

	CUIntArray iLIST_ALID__PIN;
	//

	//-------------------------------------------------------------------------	
	// OBJ ...
	CX__VAR_STRING_CTRL   sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL   sCH__OBJ_STATUS;

	// CFG ...
	CX__VAR_ANALOG_CTRL   aCH__CFG_OPEN_TIMEOUT;
	CX__VAR_ANALOG_CTRL   aCH__CFG_CLOSE_TIMEOUT;

	// MON.PART ... 
	CX__VAR_DIGITAL_CTRL  dCH__MON_PART_ERROR_ACTIVE;

	// MON ...
	CX__VAR_STRING_CTRL   sCH__MON_ACT_TIME_COUNT;
	//

	//-------------------------------------------------------------------------
	// OBJ__DB_SYS ...
	CX__VAR_DIGITAL_CTRL  dEXT_CH__CFG_USE_SHUTTER_CLOSE_CHECK;

	// LINK_CHANNEL ...
	CX__VAR_STRING_CTRL   sEXT_CH__SHUTTER_STATE;

	CX__VAR_DIGITAL_CTRL  dEXT_CH__DO_SHUTTER_CLOSE;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__DO_SHUTTER_OPEN;

	CX__VAR_DIGITAL_CTRL  dEXT_CH__DI_SHUTTER_CLOSE;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__DI_SHUTTER_OPEN;
	//

	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__SHUTTER_OPEN;
	int Call__SHUTTER_OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__SHUTTER_CLOSE;
	int Call__SHUTTER_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	int Mon__STATUS(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//

public:
	CObj__SHUTTER_IO();
	~CObj__SHUTTER_IO();

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
