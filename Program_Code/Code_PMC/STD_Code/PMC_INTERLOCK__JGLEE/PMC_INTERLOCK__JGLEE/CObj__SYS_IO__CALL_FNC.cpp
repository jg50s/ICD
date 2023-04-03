#include "StdAfx.h"
#include "CObj__SYS_IO.h"
#include "CObj__SYS_IO__DEF.h"


//-------------------------------------------------------------------------	
int  CObj__SYS_IO
::Call__TEST_1(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}


//-------------------------------------------------------------------------	
int  CObj__SYS_IO
::Check__Interlock_Use(const int lock_id)
{
	if((lock_id == ALID__VENT_Fast_Valve__OPEN)
	|| (lock_id == ALID__VENT_Soft_Valve__OPEN))
	{
		if(dEXT_CH__ACTIVE_INTERLOCK_CHAMBER_VENT->Check__DATA(STR__OFF) > 0)			return -1;

	}

	return 1;
}

void CObj__SYS_IO
::Post_Alarm(const int alarm_id, const CString err_msg)
{
	CString r_act;

	pII_ALARM->Check__ALARM(alarm_id, r_act);
	pII_ALARM->Post__ALARM_WITH_MESSAGE(alarm_id, err_msg);
}
