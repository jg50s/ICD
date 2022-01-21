#include "StdAfx.h"
#include "CObj__MS_FC100.h"

#include "math.h"


//--------------------------------------------------------------------------------
void CObj__MS_FC100::
Fnc__DRV_LOG_OF_MSG(const CString& log_msg)
{
	xLog_Ctrl__Drive->WRITE__LOG(log_msg);
}
void CObj__MS_FC100::
Fnc__DRV_LOG_OF_DATA_ERROR()
{
	CString log_msg = " * Data Size Error !";

	xLog_Ctrl__Drive->WRITE__LOG(log_msg);
}

unsigned char CObj__MS_FC100::
_Get_CheckSum(const unsigned char *s_data, const int s_len)
{
	unsigned char sum = 0; 
	
	for(int i=1; i < s_len; i++) 
	{ 
		sum += s_data[i]; 
	} 

	return (0x0ff & sum);
}
