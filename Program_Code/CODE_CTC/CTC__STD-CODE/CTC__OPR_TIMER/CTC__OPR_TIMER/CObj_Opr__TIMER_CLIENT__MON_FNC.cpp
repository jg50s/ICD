#include "StdAfx.h"
#include "CObj_Opr__TIMER_CLIENT.h"


// ...
void CObj_Opr__TIMER_CLIENT
::Mon__TIme_Sync_Client(CII_OBJECT__VARIABLE* p_variable)
{
	SCX__TIMER_CTRL timer_ctrl;
	CString var_data;
	int ref_time;

	int time_count = 0;
	timer_ctrl->INIT__COUNT_DOWN();

	while(1)
	{
		timer_ctrl->POLL(1.0);
		time_count++;

		if(xCH__CFG__SYNC_USE->Check__DATA("ENABLE") < 0)
		{
			continue;
		}

		if(xCH__SYNC_REQ_FLAG->Check__DATA("YES") > 0)
		{
			xCH__SYNC_REQ_FLAG->Set__DATA("");
		}
		else
		{
			xCH__CFG__REF_TIME->Get__DATA(var_data);

			if(xCH__CFG__REF_TYPE->Check__DATA("HOUR") > 0)
			{
				ref_time = atoi(var_data) * 3600;
			}
			else
			{
				ref_time = atoi(var_data) * 60;
			}

			if(time_count < ref_time)		continue;
		}

		Fnc__Set_Module_Time();
		time_count = 0;
	}
}

void CObj_Opr__TIMER_CLIENT
::Fnc__Set_Module_Time()		
{
	SYSTEMTIME cur_time;
	CString	   str_time;

	GetLocalTime(&cur_time);
	str_time.Format("%00004d%002d%002d%002d%002d%002d",
					cur_time.wYear,
					cur_time.wMonth, 
					cur_time.wDay,
					cur_time.wHour,
					cur_time.wMinute,
					cur_time.wSecond);

	xCH__MODULE_TIME->Set__DATA(str_time);

	// ...
	SCX__TIMER_CTRL timer_ctrl;

	xCH__SYNC_COUNT->Set__DATA("1");
	timer_ctrl->WAIT(1.0);
	xCH__SYNC_COUNT->Set__DATA("0");
}
