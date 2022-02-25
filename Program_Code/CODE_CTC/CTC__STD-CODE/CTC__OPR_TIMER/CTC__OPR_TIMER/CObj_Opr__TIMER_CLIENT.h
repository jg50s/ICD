#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"


#define  ALID__OBJECT_MODE_UNKNOWN					11


class CObj_Opr__TIMER_CLIENT : public __IOBJ__STD_TYPE
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
	CX__VAR_STRING_CTRL  xCH__SYNC_REQ_FLAG;

	CX__VAR_DIGITAL_CTRL xCH__CFG__SYNC_USE;		// DISABLE  ENABLE
	CX__VAR_DIGITAL_CTRL xCH__CFG__REF_TYPE;		// HOUR  DAY
	CX__VAR_ANALOG_CTRL  xCH__CFG__REF_TIME;		// 0 ~ 60


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	CString sMODE__TIME_SYNC;
	int Call__TIME_SYNC(CII_OBJECT__VARIABLE *p_variable);

	//.....
	void Mon__TIme_Sync_Client(CII_OBJECT__VARIABLE* p_variable);
	void Fnc__Set_Module_Time();
	//


public:
	CObj_Opr__TIMER_CLIENT();
	~CObj_Opr__TIMER_CLIENT();

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
