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

CString Macro__Get_Parity(const int parity_mode)
{
	if(parity_mode == 0)		return "None";
	if(parity_mode == 1)		return "Odd";
	if(parity_mode == 2)		return "Even";
	if(parity_mode == 3)		return "Mark";
	if(parity_mode == 4)		return "Space";

	return "Unknown";
}
