#include "StdAfx.h"



CString Macro__Get_Date_Time()
{
	CTime t = CTime::GetCurrentTime();

	CString str_date_time;

	str_date_time.Format("%00004d_%002d_%002d %002d:%002d:%002d",
						 t.GetYear(),
						 t.GetMonth(),
						 t.GetDay(),
						 t.GetHour(),
						 t.GetMinute(),
						 t.GetSecond());

	return str_date_time;
}
