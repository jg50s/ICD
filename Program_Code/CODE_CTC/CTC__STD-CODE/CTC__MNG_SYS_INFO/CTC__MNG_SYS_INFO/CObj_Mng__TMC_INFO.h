#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj_Mng__TMC_INFO__DEF.h"


// ...
#define  ALID__OBJECT_MODE_UNKNOWN					11


class CObj_Mng__TMC_INFO : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;
	CCommon_Error__USER_FNC     mERROR__USER_FNC;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_STRING_CTRL sCH__UTILITY_CFG_TO_CSV_REQ;
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	CX__VAR_DIGITAL_CTRL xEXT_CH__TMC_CONNECT_STATUS;
	//


	// ...
	void Mon__INFO_CTRL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//


public:
	CObj_Mng__TMC_INFO();
	~CObj_Mng__TMC_INFO();

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
