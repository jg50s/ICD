#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CClass__Error_Timer.h"

#include "CObj__HEATER_MDx_LINK__DEF.h"


class CObj__HEATER_MDx_LINK : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	SCX__USER_LOG_CTRL xI_LOG_CTRL;

	int iActive__SIM_MODE;

	CUIntArray iLIST_ALID__HTR;
	//

	//-------------------------------------------------------------------------
	// OBJ ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL  sCH__OBJ_STATUS;
	CX__VAR_STRING_CTRL  sCH__OBJ_TIMER;

	// LINK.IO ...
	CX__VAR_STRING_CTRL  sCH__MON_IO_TEMPERATURE_SP;
	CX__VAR_STRING_CTRL  sCH__MON_IO_TEMPERATURE_PV;
	//

	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//


public:
	CObj__HEATER_MDx_LINK();
	~CObj__HEATER_MDx_LINK();

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
