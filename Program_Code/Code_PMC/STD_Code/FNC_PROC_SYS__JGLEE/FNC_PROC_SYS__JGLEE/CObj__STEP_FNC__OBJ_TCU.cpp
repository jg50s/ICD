#include "StdAfx.h"
#include "CObj__STEP_FNC.h"



/*
int CObj__STEP_FNC::
TCU__Start_MODE(const CString& mode_name)
{
	CString log_msg;
	int	n_ret = -1;

	// 1. Check Object Status ...
	{
		int	is_busy = -1;

		is_busy = pOBJ_CTRL__TCU->Is__OBJ_BUSY();		// Object Running Check
		if(is_busy > 0)									// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
		{
			log_msg.Format("( Start_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Is__OBJ_BUSY() is failed [%d] !", mode_name,is_busy);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// 2. Run Object Mode ...
	{
		n_ret = pOBJ_CTRL__TCU->Run__OBJECT(mode_name);
		if(n_ret < 0)
		{
			log_msg.Format("( Start_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Run__OBJECT(%s) is failed [%d] !", mode_name,mode_name,n_ret);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return n_ret;
		}
	}

	return n_ret;
}

int CObj__STEP_FNC::
TCU__Wait_MODE(const CString& log_id)
{
	CString log_msg;
	CString cur_mode;
	int	n_ret = -1;

	// 1. Running Object Mode Get ...
	{
		n_ret = pOBJ_CTRL__TCU->Get__OBJ_MODE(cur_mode);
		if(n_ret < 0)
		{
			log_msg.Format("%s ( Wait_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Get__OBJ_MODE(%s) is failed [%d] !", log_id,cur_mode,cur_mode,n_ret);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// 2. Waiting Object Complete ...
	{
		n_ret = pOBJ_CTRL__TCU->When__OBJECT();
		if(n_ret < 0)
		{
			log_msg.Format("%s ( Wait_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->When__OBJECT() is failed [%d] !", log_id,cur_mode,n_ret);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return n_ret;
		}
	}

	return n_ret;
}

int CObj__STEP_FNC::
TCU__Status_MODE(const CString& log_id)
{
	CString log_msg;
	CString cur_mode;
	int	n_ret = -1;

	// 1. Running Object Mode Get ...
	{
		n_ret = pOBJ_CTRL__TCU->Get__OBJ_MODE(cur_mode);
		if(n_ret < 0)
		{
			log_msg.Format("%s ( Status_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Get__OBJ_MODE(%s) is failed [%d] !", log_id,cur_mode,cur_mode,n_ret);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// 2. Check Object Status ...
	{
		CString str_Status;

		n_ret = pOBJ_CTRL__TCU->Get__OBJECT_STATUS();
		switch(n_ret)
		{
		case  OBJECT_STATUS__RUN:
			str_Status.Format("RUN");
			break;

		case OBJECT_STATUS__RESUME:
			str_Status.Format("RESUME");
			break;

		case OBJECT_STATUS__PAUSE:
			str_Status.Format("PAUSE");
			break;

		case OBJECT_STATUS__AVAILABLE:
			str_Status.Format("AVAILABLE");
			break;

		case OBJECT_STATUS__ABORTED:
			str_Status.Format("ABORTED");
			break;

		case OBJECT_STATUS__ABORT:
			str_Status.Format("ABORTING");
			break;

		default:
			str_Status.Format("UNKNOWN");
			break;		
		}
	}

	return n_ret;		// Object Status Result
}

int CObj__STEP_FNC::
TCU__Call_MODE(const CString& mode_name, const CString& log_id)
{
	CString log_msg;
	int	n_ret = -1;

	// 1. Check Object Status ...
	{
		int is_busy = pOBJ_CTRL__TCU->Is__OBJ_BUSY();	// Object Running Check
		if(is_busy > 0)											// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
		{
			log_msg.Format("%s ( Call_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Is__OBJ_BUSY() is failed [%d] !", log_id,mode_name,is_busy);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// 2. Call Object Mode ...
	{
		n_ret = pOBJ_CTRL__TCU->Call__OBJECT(mode_name);
		if(n_ret < 0)
		{
			log_msg.Format("%s ( Call_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Call__OBJECT(%s) is failed !", log_id,mode_name,mode_name,n_ret);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return n_ret;
		}
	}

	return n_ret;
}

int CObj__STEP_FNC::
TCU__Abort_Call_MODE(const CString& mode_name, const CString& log_id)
{
	CString log_msg;
	int	n_ret = -1;

	// 1. Check Object Status ...
	{
		int is_busy = pOBJ_CTRL__TCU->Is__OBJ_BUSY();		// Object Running Check
		if(is_busy > 0)												// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
		{
			log_msg.Format("%s ( Abort_Call_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Is__OBJ_BUSY() is failed [%d] !", log_id,mode_name,is_busy);
			xLOG_CTRL->WRITE__LOG(log_msg);

			//
			pOBJ_CTRL__TCU->Abort__OBJECT();
			pOBJ_CTRL__TCU->When__OBJECT();
		}
	}

	// ...
	{
		// 2. Dislink Upper Call Object Mode
		pOBJ_CTRL__TCU->Dislink__UPPER_OBJECT();

		// 3. Call Object Mode
		n_ret = pOBJ_CTRL__TCU->Call__OBJECT(mode_name);

		// 4. Link Upper Call Object Mode
		pOBJ_CTRL__TCU->Link__UPPER_OBJECT();

		if(n_ret < 0)
		{
			log_msg.Format("%s ( Abort_Call_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Call__OBJECT(%s) is failed !", log_id, mode_name,mode_name,n_ret);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return n_ret;
		}
	}

	return n_ret;
}
*/
