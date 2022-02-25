#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"


class CObj_FA__E94_CTRL : public __IOBJ__STD_TYPE
{
private:
	//---------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;


	//---------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_STRING_CTRL xCH__CJOB_ACTION;
	CX__VAR_STRING_CTRL xCH__CJOB_NAME;
	CX__VAR_STRING_CTRL xCH__UPDATE_FLAG;

	CX__VAR_STRING_CTRL xCH_SCR__CJOB_START__WIN_NAME[CFG_LP_LIMIT];
	CX__VAR_STRING_CTRL xCH_SCR__CJOB_START__CJOB_NAME[CFG_LP_LIMIT];


	//---------------------------------------------------------
	//  EXTERNAL PROPERTY


	//---------------------------------------------------------
	void Mon__E94_CTRL(CII_OBJECT__VARIABLE* p_variable);
	//


public:
	CObj_FA__E94_CTRL();
	~CObj_FA__E94_CTRL();

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
