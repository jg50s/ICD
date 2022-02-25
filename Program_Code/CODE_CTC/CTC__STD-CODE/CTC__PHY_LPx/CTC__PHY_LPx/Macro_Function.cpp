#include "StdAfx.h"


void Macro__GET_DATE_TIME(CString& str_date,CString& str_time)
{
	CTime t = CTime::GetCurrentTime();

	str_date.Format("%00004d%002d%002d",
					t.GetYear(),
					t.GetMonth(),
					t.GetDay());

	str_time.Format("%002d%002d%002d",
					t.GetHour(),
					t.GetMinute(),
					t.GetSecond());
}
