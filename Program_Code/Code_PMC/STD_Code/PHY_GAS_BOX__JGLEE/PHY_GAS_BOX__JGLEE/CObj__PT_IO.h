#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Def.h"

#include "CClass__Error_Timer.h"

#include "CObj__PT_IO__DEF.h"
#include "CObj__PT_IO__ALID.h"


class CObj__PT_IO : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//-------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;
	int iActive__SIM_MODE;
	//

	//-------------------------------------------------------------------------
	// INTERNAL PROPERTY

	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// MON.INFO ...
	CX__VAR_ANALOG_CTRL  aCH__MON_PRESSURE__PT_X[_CFG__PT_MAX];

	// CFG ...
	CX__VAR_STRING_CTRL  sCH__CFG_NAME__PT_X[_CFG__PT_MAX];
	CX__VAR_DIGITAL_CTRL dCH__CFG_USE__PT_X[_CFG__PT_MAX];

	CX__VAR_ANALOG_CTRL  aCH__CFG_MIN_VALUE__PT_X[_CFG__PT_MAX];
	CX__VAR_ANALOG_CTRL  aCH__CFG_MAX_VALUE__PT_X[_CFG__PT_MAX];
	CX__VAR_ANALOG_CTRL  aCH__CFG_DEC_VALUE__PT_X[_CFG__PT_MAX];
	CX__VAR_DIGITAL_CTRL dCH__CFG_UNIT__PT_X[_CFG__PT_MAX];

	CX__VAR_ANALOG_CTRL  aCH__CFG_SETPOINT__PT_X[_CFG__PT_MAX];

	CX__VAR_ANALOG_CTRL  aCH__CFG_STABLE_CHECK_TIMEOUT__PT_X[_CFG__PT_MAX];
	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_TOLERANCE_TIMEOUT__PT_X[_CFG__PT_MAX];
	CX__VAR_ANALOG_CTRL  aCH__CFG_HARD_TOLERANCE_TIMEOUT__PT_X[_CFG__PT_MAX];

	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_TOLERANCE_THRESHOLD__PT_X[_CFG__PT_MAX];
	CX__VAR_ANALOG_CTRL  aCH__CFG_HARD_TOLERANCE_THRESHOLD__PT_X[_CFG__PT_MAX];

	// CFG : ZERO-CAL ...
	CX__VAR_ANALOG_CTRL  aCH__ZERO_CAL_OFFSET__PT_X[_CFG__PT_MAX];
	CX__VAR_STRING_CTRL  sCH__ZERO_CAL_REQ_PRESSURE__PT_X[_CFG__PT_MAX];
	CX__VAR_STRING_CTRL  sCH__ZERO_CAL_RESET_PRESSURE__PT_X[_CFG__PT_MAX];

	// MON.STABLE ...
	CX__VAR_DIGITAL_CTRL dCH__MON_ERROR_CHECK_ACTIVE__PT_X[_CFG__PT_MAX];
	CX__VAR_DIGITAL_CTRL dCH__MON_ABORT_ACTIVE__PT_X[_CFG__PT_MAX];
	CX__VAR_DIGITAL_CTRL dCH__MON_STABLE_ACTIVE__PT_X[_CFG__PT_MAX];

	CX__VAR_STRING_CTRL  sCH__MON_STABLE_CHECK_TIME__PT_X[_CFG__PT_MAX];
	CX__VAR_STRING_CTRL  sCH__MON_WARNING_MIN__PT_X[_CFG__PT_MAX];
	CX__VAR_STRING_CTRL  sCH__MON_WARNING_MAX__PT_X[_CFG__PT_MAX];
	CX__VAR_STRING_CTRL  sCH__MON_WARNING_CHECK_TIME__PT_X[_CFG__PT_MAX];
	CX__VAR_STRING_CTRL  sCH__MON_ABORT_MIN__PT_X[_CFG__PT_MAX];
	CX__VAR_STRING_CTRL  sCH__MON_ABORT_MAX__PT_X[_CFG__PT_MAX];
	CX__VAR_STRING_CTRL  sCH__MON_ABORT_CHECK_TIME__PT_X[_CFG__PT_MAX];
	//

	//-------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	// DB_SYS ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_PMC_ATM_MAINT_ACTIVE;

	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_SYSTEM_PROCESS_ACTIVE;

	// PT ...
	int iPT_SIZE;
	CX__VAR_ANALOG_CTRL  aEXT_CH__AI_PT_PRESSURE_X[_CFG__PT_MAX];
	//


	//------------------------------------------------------------------------------
	// CONTROL MODE ...

	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//

	// ...
	int  Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	int  Mon__PT_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);
	CString Get__PT_MSG(const CString& pt_name, CClass__Error_Timer* p_error);
	//


public:
	CObj__PT_IO();
	~CObj__PT_IO();

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
