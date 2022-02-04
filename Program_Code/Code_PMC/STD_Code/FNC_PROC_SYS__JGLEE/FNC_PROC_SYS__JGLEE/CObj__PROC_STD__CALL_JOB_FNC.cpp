#include "StdAfx.h"
#include "CObj__PROC_STD.h"


// ...
int CObj__PROC_STD
::Call__JOB_START_READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__PROC_READY(p_variable, p_alarm);
}

int CObj__PROC_STD
::Call__JOB_END_READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__PROC_START(p_variable, p_alarm);
}
