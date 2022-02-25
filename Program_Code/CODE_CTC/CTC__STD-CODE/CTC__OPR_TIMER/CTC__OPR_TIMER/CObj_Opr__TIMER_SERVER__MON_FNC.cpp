#include "StdAfx.h"
#include "CObj_Opr__TIMER_SERVER.h"


// ...
void CObj_Opr__TIMER_SERVER
::Mon__Time_Sync_Server(CII_OBJECT__VARIABLE* p_variable)
{
	CString var_data;
	CString sync_time;
	int cur_sync_count = 0;
	int pre_sync_count = 0;  

	while(1)
	{
		Sleep(1);

		xCH__SYNC_COUNT->Get__DATA(var_data);
		cur_sync_count = atoi(var_data);

		if(pre_sync_count == cur_sync_count)		continue;
		pre_sync_count = cur_sync_count;

		if(cur_sync_count < 1)		continue;

		xCH__MODULE_TIME->Get__DATA(sync_time);
		Fnc__Time_Sync(sync_time);
	}
}

void CObj_Opr__TIMER_SERVER
::Fnc__Time_Sync(const CString& time)
{
	if(time.GetLength() >= 14)
	{
		CString year, month, date, hour, minute, second;

		year   = time.Mid(0,4);
		month  = time.Mid(4,2);
		date   = time.Mid(6,2);
		hour   = time.Mid(8,2);
		minute = time.Mid(10,2);
		second = time.Mid(12,2);

		//
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

	// MessageBox(NULL,time,sObject_Name,MB_OK|MB_TOPMOST);
}
