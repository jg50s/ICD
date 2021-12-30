#include "StdAfx.h"
#include "CObj__VAT650_TYPE.h"



//--------------------------------------------------------------------------------
void CObj__VAT650_TYPE::
Fnc__DRV_LOG(const CString& log_msg)
{
	if(dCH__DRV_LOG_PARAM_START_STOP->Check__DATA("STOP") > 0)
	{
		return;
	}

	xDRV_LOG_CTRL->WRITE__LOG(log_msg);
}

void CObj__VAT650_TYPE
::Fnc__APP_LOG(const CString& log_msg)
{
	if(iFlag__APP_LOG < 1)
	{
		return;
	}

	xAPP_LOG_CTRL->WRITE__LOG(log_msg);
}

int  CObj__VAT650_TYPE::
Is__ONLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString title;
	CString msg;

	if(iACTIVE_SIM > 0)
	{
		xCH_diCOMM_STS->Set__DATA("ONLINE");
	}

	if(xCH_diCOMM_STS->Check__DATA("ONLINE") < 0)
	{
		int alarm_id = ALID__APC_OFFLINE_ALARM;

		p_alarm->Post__ALARM(alarm_id);
		return OBJ_ABORT;
	}

	return OBJ_AVAILABLE;
}

int  CObj__VAT650_TYPE::
Is__REMOTE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString title;
	CString szLog;

	int nCmd_Ret = 0;

	if(xCH_diOPER_MODE->Check__DATA("REMOTE") > 0)				return OBJ_AVAILABLE;		
	if(xCH_doOPER_MODE->Set__DATA("REMOTE")  <= 0)				return OBJ_ABORT;

	if(iACTIVE_SIM > 0)
	{
		xCH_diOPER_MODE->Set__DATA("REMOTE");
	}

	nCmd_Ret = xCH_diOPER_MODE->When__DATA("REMOTE", 3.0);
	if(nCmd_Ret == 0)
	{
		Fnc__APP_LOG("Upper Object Aborted...");
		return OBJ_ABORT;
	}
	else if(nCmd_Ret <  0)	
	{
		int alarm_id = ALID__APC_NOT_REMOTE_STATUS;
		p_alarm->Post__ALARM(alarm_id);
		return OBJ_ABORT;
	}
	else if(nCmd_Ret > 0)
	{
		szLog.Format("CH_NAME : [%s], Cmd[%s] Success", xCH_doOPER_MODE->Get__VARIABLE_NAME(), "CMD - REMOTE");
		Fnc__APP_LOG(szLog);
	}

	return OBJ_AVAILABLE;
}
