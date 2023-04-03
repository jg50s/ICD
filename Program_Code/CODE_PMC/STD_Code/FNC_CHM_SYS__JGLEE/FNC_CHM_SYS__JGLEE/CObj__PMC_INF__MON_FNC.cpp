#include "StdAfx.h"
#include "CObj__PMC_INF.h"
#include "CObj__PMC_INF__ALID.h"


#define  STR__ON			"ON"


// ...
void CObj__PMC_INF::Mon__STATUS(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	bool active__link_ready = false;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(sCH__LINK_TIME_ACTIVE->Check__DATA(STR__ON) > 0)
		{
			if(active__link_ready)
			{
				active__link_ready = false;

				Fnc__TIME_INIT(p_variable, p_alarm);
			}
		}
		else
		{
			active__link_ready = true;
		}
	}
}

int  CObj__PMC_INF
::Fnc__TIME_INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString str_time = sCH__MODULE_TIME->Get__STRING();
	if(str_time.GetLength() != 14)
	{
		int alm_id = ALID__SYSTEM_TIME_CHANGE_ERROR;
		CString alm_msg;
		CString alm_bff;
		CString r_act;

		alm_msg  = "TIME FORMAT ERROR (YYYYMMDDhhmmss)";
		alm_msg += "\n";

		alm_bff.Format(" * CHANGE REQUEST TIME <- %s \n", str_time);
		alm_msg += alm_bff;

		p_alarm->Check__ALARM(alm_id, r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);

		return -11;
	}

	// ...
	CString year, month, date, hour, minute, second;

	year   = str_time.Mid(0,4);
	month  = str_time.Mid(4,2);
	date   = str_time.Mid(6,2);
	hour   = str_time.Mid(8,2);
	minute = str_time.Mid(10,2);
	second = str_time.Mid(12,2);

	//
	SYSTEMTIME	sys_time;
	GetLocalTime(&sys_time);

	sys_time.wYear   = atoi(year);
	sys_time.wMonth  = atoi(month); 
	sys_time.wDay	 = atoi(date);
	sys_time.wHour   = atoi(hour);
	sys_time.wMinute = atoi(minute); 
	sys_time.wSecond = atoi(second); 

	int result__time_change = SetLocalTime(&sys_time);

	if(result__time_change < 1)
	{
		int alm_id = ALID__SYSTEM_TIME_CHANGE_ERROR;
		CString alm_msg;
		CString r_act;

		alm_msg.Format("CHANGE REQUEST TIME <- %s \n", str_time);

		p_alarm->Check__ALARM(alm_id, r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
	}

	return result__time_change;
}
