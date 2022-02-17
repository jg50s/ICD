#include "StdAfx.h"
#include "CObj__ARCTIC_SERIAL.h"


//------------------------------------------------------------------------------------
void CObj__ARCTIC_SERIAL
::Write__APP_LOG(const CString& log_msg)
{
	xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
}

void CObj__ARCTIC_SERIAL
::Write__DRV_LOG(const CString& log_title, const CString& log_body)
{
	if(dCH__CFG_DRV_LOG_ENABLE->Check__DATA(STR__YES) < 0)			return;

	// ...
	CString log_msg;

	log_msg.Format("%s : %s", log_title,log_body);

	xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
}
