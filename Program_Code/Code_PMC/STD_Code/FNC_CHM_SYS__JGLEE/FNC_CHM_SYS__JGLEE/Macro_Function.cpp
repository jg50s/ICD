#include "StdAfx.h"


// ...
CString Macro__Get_Date()
{
	CString	time;
	SYSTEMTIME st;

	GetLocalTime(&st);
	time.Format("%00004d/%002d/%002d %002d:%002d:%002d",
				st.wYear,st.wMonth, st.wDay,
				st.wHour,st.wMinute,st.wSecond);

	return time;
}

CString Macro__Get_Month()
{
	CString	time;
	SYSTEMTIME st;

	GetLocalTime(&st);
	time.Format("%1d", st.wMonth);

	return time;
}

void Macro__Get_Date(CString& date, CString& time)
{
	CTime t = CTime::GetCurrentTime();

	date.Format("%00004d_%002d_%002d", t.GetYear(),t.GetMonth(),t.GetDay());
	time.Format("%002d%002d%002d", t.GetHour(),t.GetMinute(),t.GetSecond());
}
