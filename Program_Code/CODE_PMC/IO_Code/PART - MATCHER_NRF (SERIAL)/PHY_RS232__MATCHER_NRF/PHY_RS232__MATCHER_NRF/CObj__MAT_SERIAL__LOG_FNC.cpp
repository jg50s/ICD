#include "StdAfx.h"
#include "CObj__MAT_SERIAL.h"


//------------------------------------------------------------------------------------
void CObj__MAT_SERIAL
::Write__APP_LOG(const CString& log_msg)
{
	xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
}

void CObj__MAT_SERIAL
::Write__DRV_LOG(const CString& log_msg)
{
	if(dCH__CFG_DRV_LOG_ENABLE->Check__DATA(STR__ON) < 0)			return;

	xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
}
