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


int Macro__Get_StringArrray_From_String(const CString& str_org_data,const CString& str_sep,CStringArray& l_data)
{
	CString str_data = str_org_data;

	l_data.RemoveAll();

	while(1)
	{
		int db_index = str_data.Find(str_sep);
		if(db_index < 0)
		{
			if(str_data.GetLength() > 0)
			{
				l_data.Add(str_data);
			}
			break;
		}

		CString str_token = str_data;			
		str_token.Delete(db_index, str_token.GetLength()-db_index);

		str_data.Delete(0, 1+db_index);

		if(db_index > 0)
		{
			l_data.Add(str_token);
		}
	}

	return 1;
}
int Macro__Get_Hexa_From_String(const CString& xxx_data)
{
	CString str_data = xxx_data;

	str_data.MakeUpper();
	if(str_data.Find("OX") == 0)		str_data.Delete(0, 2);

	// ...
	int i_hexa = 0;

	int i_limit = str_data.GetLength();
	int i;

	for(i=0; i<i_limit; i++)
	{
		char ch = str_data[i];

		i_hexa *= 0x10;

		if((ch >= '0') && (ch <= '9'))
		{
			i_hexa += (ch - '0');
			continue;
		}
		if((ch >= 'A') && (ch <= 'F'))
		{
			i_hexa += ((ch - 'A') + 10);
			continue;
		}
		if((ch >= 'a') && (ch <= 'f'))
		{
			i_hexa += ((ch - 'a') + 10);
			continue;
		}		
	}

	return i_hexa;
}
