#include "StdAfx.h"
#include "Interface_Code.h"


#define  _MODULE__LBA					"LBA"
#define  _MODULE__LBB					"LBB"
#define  _MODULE__LBC					"LBC"
#define  _MODULE__LBD					"LBD"

#define  _MODULE__LLx					"LLx"


// ...
CString Macro__GET_LLx_NAME(const int ll_index)
{
	if(ll_index == 0)			return _MODULE__LBA;
	if(ll_index == 1)			return _MODULE__LBB;
	if(ll_index == 2)			return _MODULE__LBC;
	if(ll_index == 3)			return _MODULE__LBD;

	return _MODULE__LLx;
}
int  Macro__CHECK_LLx_INDEX(const CString& stn_name)
{
	CString ll_name;
	int i;

	for(i=0; i<CFG__LLx_SIZE;i++)
	{
		ll_name.Format("LL%1d",i+1);
		if(ll_name.CompareNoCase(stn_name) == 0)		return i;

		ll_name = Macro__GET_LLx_NAME(i);
		if(ll_name.CompareNoCase(stn_name) == 0)		return i;
	}

	return -1;
}
