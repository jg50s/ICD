#include "StdAfx.h"
#include "CObj__GAS_VLV_FNC.h"


// ...
int CObj__GAS_VLV_FNC::Get__MFC_INDEX(const CString& gas_name)
{
	CString str_name;
	int i;

	for(i=0; i<iMFC_SIZE; i++)
	{
		str_name.Format("GAS%02d", i+1);
		if(str_name.CompareNoCase(gas_name) != 0)		continue;

		return i;
	}
	return -1;
}
