#include "StdAfx.h"


// ...
int Macro__LLx_ID(const CString& ll_name)
{
	if(ll_name.CompareNoCase("LBA") == 0)		return 1;
	if(ll_name.CompareNoCase("LBB") == 0)		return 2;
	if(ll_name.CompareNoCase("LBC") == 0)		return 3;
	if(ll_name.CompareNoCase("LBD") == 0)		return 4;

	if(ll_name.CompareNoCase("LL1") == 0)		return 1;
	if(ll_name.CompareNoCase("LL2") == 0)		return 2;
	if(ll_name.CompareNoCase("LL3") == 0)		return 3;
	if(ll_name.CompareNoCase("LL4") == 0)		return 4;
	return -1;
}

int Macro__Check_Material_Status(const CString& material_sts)
{
	if(material_sts.CompareNoCase("EXIST")      == 0)		return 1;
	if(material_sts.CompareNoCase("MAPPED")     == 0)		return 1;
	if(material_sts.CompareNoCase("ALIGNED")    == 0)		return 1;
	if(material_sts.CompareNoCase("PROCESSING") == 0)		return 1;
	if(material_sts.CompareNoCase("PROCESSED")  == 0)		return 1;
	if(material_sts.CompareNoCase("ABORTED")    == 0)		return 1;

	return -1;
}

int Macro__Analyze_Title_Info(const CString& title,int& wfr_ptn,int& wfr_slot)
{
	wfr_ptn  = -1;
	wfr_slot = -1;

	// ...
	CString bff = title;
	CString str_ptn  = title;
	CString str_slot = title;

	int db_index = bff.Find(":",0);
	if(db_index < 0)		return -1;

	str_ptn.Delete(db_index,bff.GetLength()-db_index);
	str_slot.Delete(0,db_index+1);

	if(str_ptn.GetLength() < 2)		return -1;
	if(str_ptn.GetAt(0) != 'P')		return -1;

	str_ptn.Delete(0,1);

	wfr_ptn  = atoi(str_ptn);
	wfr_slot = atoi(str_slot);

	return 1;
}

int  Macro__Get_Date_Time(CString &date_time)
{
	CTime t = CTime::GetCurrentTime();

	date_time.Format("%00004d%002d%002d%002d%002d%002d",
					 t.GetYear(),
					 t.GetMonth(),
					 t.GetDay(),
					 t.GetHour(),
					 t.GetMinute(),
					 t.GetSecond());
	return 1;
}
void Macro__Get_DateTime(CString& str_date, CString& str_time)
{
	CTime t = CTime::GetCurrentTime();

	str_date.Format("%00004d_%002d_%002d", t.GetYear(),t.GetMonth(),t.GetDay());
	str_time.Format("%002d%002d%002d",     t.GetHour(),t.GetMinute(),t.GetSecond());
}

CString Macro__Get_Current_Date()
{
	SYSTEMTIME file__sys_time;
	GetLocalTime(&file__sys_time);

	CString str_date;
	str_date.Format("%04d_%02d_%02d",		
					file__sys_time.wYear,
					file__sys_time.wMonth,
					file__sys_time.wDay);

	return str_date;
}
CString Macro__Get_Current_Time()
{
	SYSTEMTIME file__sys_time;
	GetLocalTime(&file__sys_time);

	CString str_time;
	str_time.Format("%02d:%02d:%02d.%03d",		
					file__sys_time.wHour,
					file__sys_time.wMinute,
					file__sys_time.wSecond,
					file__sys_time.wMilliseconds);

	return str_time;
}
