#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


class CObj__LLx_PROC : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;
	CCommon_Error__USER_FNC     mERROR__USER_FNC;

	//-------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL  xLOG_CTRL;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// ...
	CX__VAR_STRING_CTRL	 sCH__OBJ_MSG;

	CX__VAR_ANALOG_CTRL  aCH__CFG_AGING_TEST;
	CX__VAR_STRING_CTRL  sCH__CUR_AGING_COUNT;

	CX__VAR_STRING_CTRL  sCH__SEL_RECIPE_NAME;

	CX__VAR_DIGITAL_CTRL dCH__CFG_NEXT_STEP_CTRL_MODE;
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// ...
	CX__VAR_STRING_CTRL  sEXT_CH__SYSTEM_MSG;
	CX__VAR_STRING_CTRL  sEXT_CH__FNC_MSG;

	CX__VAR_STRING_CTRL  sEXT_CH__RCP_NAME;

	// ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__PROC;

	CX__VAR_STRING_CTRL  sEXT_CH__NEXT_STEP_CTRL_FLAG;
	CX__VAR_STRING_CTRL  sEXT_CH__NEXT_STEP_CTRL_REQ;
	//


	//-------------------------------------------------------------------------
	CString sMODE__MANUAL_PROCESS;
	int Call__MANUAL_PROCESS(CII_OBJECT__VARIABLE* p_variable);
	//


public:
	CObj__LLx_PROC();
	~CObj__LLx_PROC();

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
