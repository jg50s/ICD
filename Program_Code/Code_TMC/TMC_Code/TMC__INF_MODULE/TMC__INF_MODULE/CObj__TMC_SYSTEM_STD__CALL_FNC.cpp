#include "StdAfx.h"
#include "CObj__TMC_SYSTEM_STD.h"


// ...
int  CObj__TMC_SYSTEM_STD
::Call__TIME_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	CString time;
	sCH__MODULE_TIME->Get__DATA(time);

	if(time.GetLength() >= 14)
	{
		CString year, month, date, hour, minute, second;
		year   = time.Mid(0,4);
		month  = time.Mid(4,2);
		date   = time.Mid(6,2);
		hour   = time.Mid(8,2);
		minute = time.Mid(10,2);
		second = time.Mid(12,2);

		SYSTEMTIME	sys_time;
		GetLocalTime(&sys_time);
		sys_time.wYear   = atoi(year);
		sys_time.wMonth  = atoi(month); 
		sys_time.wDay	 = atoi(date);
		sys_time.wHour   = atoi(hour);
		sys_time.wMinute = atoi(minute); 
		sys_time.wSecond = atoi(second); 
		SetLocalTime(&sys_time);
	}			
	return 1;
}

int  CObj__TMC_SYSTEM_STD::
Call__SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return pTMC_SYS__OBJ_CTRL->Call__OBJECT("SYSTEM_INIT");
}

int  CObj__TMC_SYSTEM_STD::
Call__SYSTEM_MAINT(CII_OBJECT__VARIABLE* p_variable)
{
	return pTMC_SYS__OBJ_CTRL->Call__OBJECT("SYSTEM_MAINT");
}

int  CObj__TMC_SYSTEM_STD::
Call__AUTO_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	Call__TIME_INIT(p_variable);
	return Call__SYSTEM_INIT(p_variable);
}


// ...
int  CObj__TMC_SYSTEM_STD::
Call__CTC_TO_TMC(CII_OBJECT__VARIABLE* p_variable)
{
	return 1;
}

int  CObj__TMC_SYSTEM_STD::
Call__TMC_TO_CTC(CII_OBJECT__VARIABLE* p_variable)
{
	return 1;
}
