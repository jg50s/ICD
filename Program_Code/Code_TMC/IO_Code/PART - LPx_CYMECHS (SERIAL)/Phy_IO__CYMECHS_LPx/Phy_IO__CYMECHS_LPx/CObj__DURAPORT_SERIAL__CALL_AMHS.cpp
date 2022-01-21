#include "stdafx.h"

#include "CObj__DURAPORT_SERIAL.h"
#include "CObj__DURAPORT_SERIAL__DEF.h"


// ...
int	CObj__DURAPORT_SERIAL
::Call__AMHS_AUTO(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	/*
	m_bRunning = TRUE;

	// ...
	CString log_msg;

	// ...
	{
		log_msg.Format("AMHS_AUTO : Started ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	if(doCH__AMHS_MODE_SET->Set__DATA("Enable") < 0)
	{
		log_msg.Format("AMHS_AUTO : Aborted ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);

		m_bRunning = FALSE;
		return -1;
	}

	// ...
	{
		log_msg.Format("AMHS_AUTO : End ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	m_bRunning = FALSE;
	*/
	return 1;
}
int	CObj__DURAPORT_SERIAL
::Call__AMHS_MANUAL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	/*
	m_bRunning = TRUE;

	// ...
	CString log_msg;

	// ...
	{
		log_msg.Format("AMHS_MANUAL : Started ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	if(doCH__AMHS_MODE_SET->Set__DATA("Disable") < 0)
	{
		log_msg.Format("AMHS_MANUAL : Aborted ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);

		m_bRunning = FALSE;
		return -1;
	}

	// ...
	{
		log_msg.Format("AMHS_MANUAL : End ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	m_bRunning = FALSE;
	*/
	return 1;
}

int	CObj__DURAPORT_SERIAL
::Call__AMHS_HO_ENABLE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	/*
	m_bRunning = TRUE;

	// ...
	CString log_msg;

	// ...
	{
		log_msg.Format("AMHS_HO_ENABLE : Started ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	if((doCH__AMHS_IO_HO_AVBL_SET->Set__DATA("On") < 0)
		|| (doCH__AMHS_IO_ES_SET->Set__DATA("On") < 0))
	{
		log_msg.Format("AMHS_HO_ENABLE : Aborted ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);

		m_bRunning = FALSE;
		return -1;
	}

	// ...
	{
		log_msg.Format("AMHS_HO_ENABLE : End ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	m_bRunning = FALSE;
	*/
	return 1;
}
int	CObj__DURAPORT_SERIAL
::Call__AMHS_HO_DISBLE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	/*
	m_bRunning = TRUE;

	// ...
	CString log_msg;

	// ...
	{
		log_msg.Format("AMHS_HO_DISABLE : Started ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	if((doCH__AMHS_IO_HO_AVBL_SET->Set__DATA("Off") < 0)
		|| (doCH__AMHS_IO_ES_SET->Set__DATA("Off") < 0))
	{
		log_msg.Format("AMHS_HO_DISABLE : Aborted ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);

		m_bRunning = FALSE;
		return -1;
	}

	// ...
	{
		log_msg.Format("AMHS_HO_DISABLE : End ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	m_bRunning = FALSE;
	*/
	return 1;
}
