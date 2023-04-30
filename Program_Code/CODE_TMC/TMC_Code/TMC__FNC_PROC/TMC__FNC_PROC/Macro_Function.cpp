#include "StdAfx.h"


// ...
int Macro__Get_DateTime(CString &date,CString &time)
{
	CTime t = CTime::GetCurrentTime();

	date.Format("%00004d_%002d_%002d", t.GetYear(),t.GetMonth(),t.GetDay());
	time.Format("%002d%002d%002d", t.GetHour(),t.GetMinute(),t.GetSecond());
	return 1;
}
