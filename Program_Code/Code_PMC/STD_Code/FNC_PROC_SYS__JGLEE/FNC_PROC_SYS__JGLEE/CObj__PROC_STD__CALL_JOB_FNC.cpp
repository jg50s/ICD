#include "StdAfx.h"
#include "CObj__PROC_STD.h"


// ...
int CObj__PROC_STD
::Call__JOB_START_READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	// JOB.READY ...
	{
		int r_flag = Fnc__PROC_READY(p_variable, p_alarm, false);
		if(r_flag < 0)			return -11;
	}

	// JOB.START ...
	{
		int r_flag = Fnc__PROC_START(p_variable, p_alarm, false);
		if(r_flag < 0)			return -12;
	}

	return 1;
}

int CObj__PROC_STD
::Call__JOB_END_READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	// JOB.READY ...
	{
		int r_flag = Fnc__PROC_READY(p_variable, p_alarm, false);
		if(r_flag < 0)			return -11;
	}

	// JOB.START ...
	{
		int r_flag = Fnc__PROC_START(p_variable, p_alarm, false);
		if(r_flag < 0)			return -12;
	}

	return 1;
}

