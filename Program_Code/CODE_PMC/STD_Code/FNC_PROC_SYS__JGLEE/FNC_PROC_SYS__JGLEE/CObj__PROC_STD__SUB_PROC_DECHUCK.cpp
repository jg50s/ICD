#include "StdAfx.h"
#include "Ccommon_Def.h"

#include "CObj__PROC_STD.h"


// ...
int CObj__PROC_STD
::Fnc__PROC_DECHUCK(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int r_flag;

	// READY.CHECK ...
	{
		r_flag = Fnc__PROC_READY(p_variable, p_alarm, true);
		if(r_flag < 0)			return -11;
	}

	// PROCESS.START ...
	{
		r_flag = Fnc__PROC_START(p_variable, p_alarm, true);
		if(r_flag < 0)			return -21;
	}
	return 1;
}

