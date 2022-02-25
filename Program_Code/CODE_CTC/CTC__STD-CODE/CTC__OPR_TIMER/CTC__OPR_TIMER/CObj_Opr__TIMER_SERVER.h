#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"


#define  ALID__OBJECT_MODE_UNKNOWN					11


class CObj_Opr__TIMER_SERVER : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;
	CCommon_Error__USER_FNC     mERROR__USER_FNC;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_STRING_CTRL  xCH__SYNC_COUNT;
	CX__VAR_STRING_CTRL  xCH__MODULE_TIME;


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// ...
	void Mon__Time_Sync_Server(CII_OBJECT__VARIABLE* p_variable);		
	void Fnc__Time_Sync(const CString& sync_time);
	//


public:
	CObj_Opr__TIMER_SERVER();
	~CObj_Opr__TIMER_SERVER();

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
