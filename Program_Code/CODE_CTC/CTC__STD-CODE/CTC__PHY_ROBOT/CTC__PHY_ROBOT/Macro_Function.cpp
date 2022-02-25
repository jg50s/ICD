#include "StdAfx.h"
#include "CCommon_System.h"

#include "Macro_Function.h"


// ...
int  Macro__Get_PMx_INDEX(const CString& str_name)
{
	CString cmp_name;

	int i_limit = CFG_PM_LIMIT;

	for(int i=0; i<i_limit; i++)
	{
		cmp_name.Format("PM%1d", i+1);

		if(str_name.CompareNoCase(cmp_name) == 0)		
			return i;
	}
	return -1;
}
int  Macro__Get_LLx_INDEX(const CString& str_name)
{
	int ll_id = Macro__LLx_ID(str_name);
	if(ll_id < 1)			return -1;

	return (ll_id - 1);
}

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

int Macro__LPx_ID(const CString& lp_name)
{
	CString cmp_name;

	int i_limit = CFG_LP_LIMIT;
	int i;

	for(i=0; i<i_limit; i++)
	{
		cmp_name.Format("LP%1d", i+1);

		if(lp_name.CompareNoCase(cmp_name) != 0)
			continue;

		return (i+1);
	}
	return -1;
}

int Macro__STx_ID(const CString& st_name)
{
	if(st_name.CompareNoCase("BUFF1") == 0)			return 1;
	if(st_name.CompareNoCase("BUFF2") == 0)			return 2;

	if(st_name.CompareNoCase("ST1") == 0)			return 1;
	if(st_name.CompareNoCase("ST2") == 0)			return 2;

	return -1;
}

int Macro__ALx_ID(const CString& al_name)
{
	if(al_name.CompareNoCase("AL1") == 0)			return 1;
	if(al_name.CompareNoCase("AL2") == 0)			return 2;

	return -1;
}

int Macro__Get_Wafer_Info(const CString& wfr_title, int& lp_id,int& lp_slot)
{
	CString wfr_bff = wfr_title;	

	// ...
	{
		int s_index = wfr_bff.Find("P");
		if(s_index < 0)		return -1;

		wfr_bff.Delete(0, s_index+1);
	}
	lp_id = atoi(wfr_bff);

	// ...
	{
		int s_index = wfr_bff.Find(":");
		if(s_index < 0)		return -2;

		wfr_bff.Delete(0, s_index+1);
	}
	lp_slot = atoi(wfr_bff);

	return 1;
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
