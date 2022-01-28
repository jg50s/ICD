#include "StdAfx.h"
#include "CObj__NXA_PULSE.h"


//------------------------------------------------------------------------------------
void CObj__NXA_PULSE
::Write__APP_LOG(const CString& log_msg)
{
	xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
}

void CObj__NXA_PULSE
::Write__DRV_LOG(const CString& log_msg)
{
	if(dCH__CFG_DRV_LOG_ENABLE->Check__DATA(STR__ON) < 0)			return;

	xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
}
