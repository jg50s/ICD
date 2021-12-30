#include "StdAfx.h"

#include "CObj_Phy__ESC_ZEFA.h"
//#include "CObj_Phy__ESC_ZEFA__DEF.h"


//------------------------------------------------------------------------------------
void CObj_Phy__ESC_ZEFA::Write__APP_LOG(const CString& log_msg)
{
	xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
}

void CObj_Phy__ESC_ZEFA::Write__DRV_LOG(const CString& log_msg)
{
	if(iFLAG__DRV_FLAG < 0)
	{
		return;
	}

	xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
}

