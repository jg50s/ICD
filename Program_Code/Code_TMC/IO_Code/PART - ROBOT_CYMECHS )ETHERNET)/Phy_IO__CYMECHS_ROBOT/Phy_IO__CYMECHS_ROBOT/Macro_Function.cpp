#include "StdAfx.h"
#include "CCommon_SYSTEM.h"


// ...
int  Macro__CHECK_LPx_INDEX(const CString& stn_name)
{
	CString lp_name;
	int i;

	for(i=0;i<CFG_LPx__SIZE;i++)
	{
		lp_name.Format("LP%1d",i+1);
		if(stn_name.CompareNoCase(lp_name) != 0)		continue;

		return i;
	}
	return -1;
}

int  Macro__CHECK_PMx_INDEX(const CString& stn_name)
{
	CString pm_name;
	int i;

	for(i=0;i<CFG_PMx__SIZE;i++)
	{
		pm_name.Format("PM%1d",i+1);
		if(stn_name.CompareNoCase(pm_name) != 0)		continue;

		return i;
	}
	return -1;
}

int  Macro__CHECK_LLx_INDEX(const CString& stn_name)
{
	if(stn_name.CompareNoCase(STR__LBA) == 0)			return 0;
	if(stn_name.CompareNoCase(STR__LBB) == 0)			return 1;
	if(stn_name.CompareNoCase(STR__LBC) == 0)			return 2;
	if(stn_name.CompareNoCase(STR__LBD) == 0)			return 3;

	return -1;
}
CString Macro__Get_LLx_NAME(const int ll_i)
{
	if(ll_i == 0)			return STR__LBA;
	if(ll_i == 1)			return STR__LBB;
	if(ll_i == 2)			return STR__LBC;
	if(ll_i == 3)			return STR__LBD;

	return STR__LLx;	
}
