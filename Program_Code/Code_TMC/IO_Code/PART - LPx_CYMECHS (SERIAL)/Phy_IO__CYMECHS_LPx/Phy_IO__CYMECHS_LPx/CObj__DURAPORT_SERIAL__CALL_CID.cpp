#include "stdafx.h"

#include "CObj__DURAPORT_SERIAL.h"
#include "CObj__DURAPORT_SERIAL__DEF.h"


// ...
int	CObj__DURAPORT_SERIAL
::Call__CID_READ(CII_OBJECT__VARIABLE* p_variable,
				 CII_OBJECT__ALARM* p_alarm)
{
	/*
	m_bRunning = TRUE;

	int r_flag = Fnc__CID_READ(p_variable, p_alarm);

	m_bRunning = FALSE;
	return r_flag;
	*/
	return -1;
}
int	CObj__DURAPORT_SERIAL
::Fnc__CID_READ(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm)
{
	/*
	CString page_id;
	CString log_msg;

	// ...
	{
		aCH__CFG_PAGE_ID_OF_CID->Get__DATA(page_id);

		log_msg.Format("CID_READ Started ... : [%s] \n", page_id);
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	if(soCH__CID_PAGE_CMD->Set__DATA(page_id) < 0)
	{
		log_msg.Format("CID_READ Aborted ... \n");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);

		m_bRunning = FALSE;
		return -1;
	}

	// ...
	{
		int i_index = atoi(page_id) - 1;

		if((i_index >= 0) && (i_index < CFG__CID_PAGE))
		{
			CString ch_data = sCH__CID_PAGE_X[i_index]->Get__STRING();
			sCH__RSP_PAGE_CID->Set__DATA(ch_data);

			log_msg.Format("CID_READ End ... : [%s] \n", ch_data);
		}
		else
		{
			sCH__RSP_PAGE_CID->Set__DATA("UNKNOWN");

			log_msg.Format("CID_READ End ... : PageID(%s) Overflow !!! \n", page_id);
		}

		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
	*/
	return -1;
}

int	CObj__DURAPORT_SERIAL
::Call__PAGE_READ(CII_OBJECT__VARIABLE* p_variable, 
				  CII_OBJECT__ALARM* p_alarm)
{
	/*
	m_bRunning = TRUE;

	// ...
	CString log_msg;
	CString log_bff;

	// ...
	CString para__page_id;
	aCH__PARA_PAGE_ID->Get__DATA(para__page_id);

	// ...
	{
		log_msg.Format("PAGE_READ Started : [%s]... \n", para__page_id);

		log_bff.Format("  * %s <- \"%s\" \n", 
			aCH__PARA_PAGE_ID->Get__CHANNEL_NAME(),
			para__page_id);
		log_msg += log_bff;

		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	int state = 1;

	if(state > 0)
	{
		if(soCH__CID_PAGE_CMD->Set__DATA(para__page_id) < 0)
		{
			state = -1;
		}
	}

	if(state < 0)
	{
		log_msg.Format("PAGE_READ Aborted ... \n");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);

		m_bRunning = FALSE;
		return -1;
	}

	// ...
	{
		int i_index = atoi(para__page_id) - 1;

		if((i_index >= 0) && (i_index < CFG__CID_PAGE))
		{
			CString ch_data = sCH__CID_PAGE_X[i_index]->Get__STRING();
			sCH__RSP_PAGE_DATA->Set__DATA(ch_data);

			log_msg.Format("PAGE_READ End ... : [%s] \n", ch_data);
		}
		else
		{
			sCH__RSP_PAGE_DATA->Set__DATA("UNKNOWN");

			log_msg.Format("PAGE_READ End ... : PageID(%s) Overflow !!! \n", para__page_id);
		}

		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	m_bRunning = FALSE;
	return 1;
	*/
	return -1;
}

int	CObj__DURAPORT_SERIAL
::Call__CID_WRITE(CII_OBJECT__VARIABLE* p_variable, 
				  CII_OBJECT__ALARM* p_alarm)
{
	/*
	m_bRunning = TRUE;

	// ...
	CString ch_data;
	CString log_msg;
	CString log_bff;
	int i;

	// ...
	{
		log_msg.Format("CID_WRITE Started ... \n");

		log_bff.Format("  * %s <- %s \n", 
			sCH__PARA_PAGE_CID->Get__CHANNEL_NAME(),
			sCH__PARA_PAGE_CID->Get__STRING());
		log_msg += log_bff;

		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	int state = -1;

	// ...
	{

	}

	if(state < 0)
	{
		log_msg.Format("CID_WRITE Aborted ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);

		m_bRunning = FALSE;
		return -1;
	}

	// ...
	{
		log_msg.Format("CID_WRITE End ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	m_bRunning = FALSE;
	return 1;
	*/
	return -1;
}
int	CObj__DURAPORT_SERIAL
::Call__PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable, 
				   CII_OBJECT__ALARM* p_alarm)
{
	/*
	m_bRunning = TRUE;

	// ...
	CString log_msg;
	CString log_bff;

	// ...
	CString para__page_id;
	CString para__page_data;

	aCH__PARA_PAGE_ID->Get__DATA(para__page_id);
	sCH__PARA_PAGE_DATA->Get__DATA(para__page_data);

	// ...
	{
		log_msg.Format("PAGE_WRITE Started ...");

		log_bff.Format("  * %s <- \"%s\" \n", 
			aCH__PARA_PAGE_ID->Get__CHANNEL_NAME(),
			para__page_id);
		log_msg += log_bff;

		log_bff.Format("  * %s <- \"%s\" \n", 
			sCH__PARA_PAGE_DATA->Get__CHANNEL_NAME(),
			para__page_data);
		log_msg += log_bff;

		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	int state = -1;

	// ...
	{

	}

	if(state < 0)
	{
		log_msg.Format("PAGE_WRITE Aborted ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);

		m_bRunning = FALSE;
		return -1;
	}

	// ...
	{
		log_msg.Format("PAGE_WRITE End ...");
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	m_bRunning = FALSE;
	return 1;
	*/
	return -1;
}
