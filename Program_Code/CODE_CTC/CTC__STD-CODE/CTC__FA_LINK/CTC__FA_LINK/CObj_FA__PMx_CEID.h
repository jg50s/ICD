#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"


class CObj_FA__PMx_CEID : public __IOBJ__STD_TYPE
{
private:
	//---------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;


	//---------------------------------------------------------
	//  INTERNAL PROPERTY

	int iPMx_SIZE;	
	CString sPMx_OBJ_NAME[CFG_PM_LIMIT];


	//---------------------------------------------------------
	//  EXTERNAL PROPERTY

	CX__VAR_DIGITAL_CTRL xEXT_CH__PMx_CFG_USE[CFG_PM_LIMIT];
	CX__VAR_DIGITAL_CTRL xEXT_CH__PMx_OBJ_STATUS[CFG_PM_LIMIT];
	CX__VAR_DIGITAL_CTRL xEXT_CH__PMx_DOOR_STS[CFG_PM_LIMIT];
	CX__VAR_STRING_CTRL  xEXT_CH__PMx_LIFT_PIN_STS[CFG_PM_LIMIT];


	//---------------------------------------------------------
	void Mon__REPORT_CEID(CII_OBJECT__VARIABLE* p_variable);
	//


public:
	CObj_FA__PMx_CEID();
	~CObj_FA__PMx_CEID();

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
