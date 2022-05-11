#include "StdAfx.h"
#include "CObj__UNIT_TYPE.h"

#include "math.h"



//--------------------------------------------------------------------------------
void CObj__UNIT_TYPE::
Fnc__DRV_LOG(const CString& log_msg)
{
	if(dCH__DRV_LOG_PARAM_START_STOP->Check__DATA("STOP") > 0)
	{
		return;
	}

	xDRV_LOG_CTRL->WRITE__LOG(log_msg);
}

unsigned char CObj__UNIT_TYPE::
CheckSum(unsigned char *str_data, const int nStart, const int nSize)
{
	int i;
	unsigned char uchReturn=0x00;
	unsigned char szData[MAX_DATA_LENGTH];
	ZeroMemory(szData, sizeof(szData));
	memcpy(szData, str_data, sizeof(szData));

	for(i = nStart; i < nSize; i++ )
	{
		uchReturn += szData[i];
	}

	return uchReturn;
}

bool CObj__UNIT_TYPE::Check__MFC_USE(const int mfc_index)
{
	if(mfc_index <  0)				return false;
	if(mfc_index >= MAX_MFC)		return false;

	if(dCH__CFG_MFC_USE_X[mfc_index]->Check__DATA(STR__YES) < 0)		return false;

	return true;
}
bool CObj__UNIT_TYPE::Check__MFC_NOT_USE(const int mfc_index)
{
	if(mfc_index <  0)				return false;
	if(mfc_index >= MAX_MFC)		return false;

	if(dCH__CFG_MFC_USE_X[mfc_index]->Check__DATA(STR__YES) > 0)		return false;

	return true;
}

