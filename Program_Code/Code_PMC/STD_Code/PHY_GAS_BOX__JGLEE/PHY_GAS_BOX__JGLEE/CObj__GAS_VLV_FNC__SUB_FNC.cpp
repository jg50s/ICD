#include "StdAfx.h"
#include "CObj__GAS_VLV_FNC.h"


// ...
int CObj__GAS_VLV_FNC::Get__MFC_INDEX(const CString& gas_name)
{
	int i_limit = sList__GAS_TYPE.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		if(sList__GAS_TYPE[i].CompareNoCase(gas_name) != 0)			
			continue;

		return i;
	}
	return -1;
}
