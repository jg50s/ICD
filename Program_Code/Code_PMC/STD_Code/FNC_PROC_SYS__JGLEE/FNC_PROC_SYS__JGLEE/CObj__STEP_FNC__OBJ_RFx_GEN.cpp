#include "StdAfx.h"
#include "CObj__STEP_FNC.h"


// ...
int CObj__STEP_FNC::RF_GEN__BIAS_OBJ__Start_MODE(const CString& mode_name)
{
	CString log_msg;

	// 1. Check Object Status
	{
		int flag = pOBJ_CTRL__RF_BIAS->Is__OBJ_BUSY();			// Object Running Check
		if(flag > 0)											// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
		{
			log_msg.Format("( Start_MODE(%s) ) - OBJ_CTRL__RF_BIAS->Is__OBJ_BUSY() is failed [%d] !", mode_name, flag);
			xLOG_CTRL->WRITE__LOG(log_msg);

			pOBJ_CTRL__RF_BIAS->Abort__OBJECT();
			pOBJ_CTRL__RF_BIAS->When__OBJECT();
		}
	}

	// 2. Run Object Mode
	{
		int flag = pOBJ_CTRL__RF_BIAS->Run__OBJECT(mode_name);
		if(flag < 0)
		{
			log_msg.Format("( Start_MODE(%s) ) - OBJ_CTRL__RF_BIAS->Run__OBJECT(%s) is failed [%d] !", mode_name, mode_name, flag);
			xLOG_CTRL->WRITE__LOG(log_msg);

			return flag;
		}
	}	
	
	return 1;
}

int CObj__STEP_FNC::RF_GEN__BIAS_OBJ__Wait_MODE(const CString& log_id)
{
	CString log_msg;
	CString cur_mode;

	// 1. Running Object Mode Get
	{
		int flag = pOBJ_CTRL__RF_BIAS->Get__OBJ_MODE(cur_mode);
		if(flag < 0)
		{
			log_msg.Format("%s ( Wait_MODE(%s) ) - OBJ_CTRL__RF_BIAS->Get__OBJ_MODE(%s) is failed [%d] !", log_id, cur_mode, cur_mode, flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// 2. Waiting Object Complete
	{
		int flag = pOBJ_CTRL__RF_BIAS->When__OBJECT();
		if(flag < 0)
		{
			log_msg.Format("%s ( Wait_MODE(%s) ) - OBJ_CTRL__RF_BIAS->When__OBJECT() is failed [%d] !", log_id, cur_mode,flag);
			xLOG_CTRL->WRITE__LOG(log_msg);

			return flag;
		}
	}

	return 1;
}

int CObj__STEP_FNC::RF_GEN__BIAS_OBJ__Status_MODE(const CString& log_id)
{
	CString log_msg;
	CString cur_mode;

	// 1. Running Object Mode Get
	{
		int flag = pOBJ_CTRL__RF_BIAS->Get__OBJ_MODE(cur_mode);
		if(flag < 0)
		{
			log_msg.Format("%s ( Status_MODE(%s) ) - OBJ_CTRL__RF_BIAS->Get__OBJ_MODE(%s) is failed [%d] !", log_id, cur_mode, cur_mode, flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// 2. Check Object Status
	{
		CString str_Status;

		int flag = pOBJ_CTRL__RF_BIAS->Get__OBJECT_STATUS();

		switch(flag)
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

	return 1;		// Object Status Result
}

int CObj__STEP_FNC
::RF_GEN__BIAS_OBJ__Call_MODE(const CString& mode_name,
						      const CString& log_id)
{
	CString log_msg;

	// 1. Check Object Status
	{
		int flag = pOBJ_CTRL__RF_BIAS->Is__OBJ_BUSY();			// Object Running Check
		if(flag > 0)											// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
		{
			log_msg.Format("%s ( Call_MODE(%s) ) - OBJ_CTRL__RF_BIAS->Is__OBJ_BUSY() is failed [%d] !", log_id, mode_name, flag);
			xLOG_CTRL->WRITE__LOG(log_msg);

			pOBJ_CTRL__RF_BIAS->Abort__OBJECT();
			pOBJ_CTRL__RF_BIAS->When__OBJECT();
		}
	}

	// 2. Call Object Mode
	{
		int flag = pOBJ_CTRL__RF_BIAS->Call__OBJECT(mode_name);
		if(flag < 0)
		{
			log_msg.Format("%s ( Call_MODE(%s) ) - OBJ_CTRL__RF_BIAS->Call__OBJECT(%s) is failed !", log_id, mode_name, mode_name, flag);
			xLOG_CTRL->WRITE__LOG(log_msg);

			return flag;
		}
	}

	return 1;
}

int CObj__STEP_FNC
::RF_GEN__BIAS_OBJ__Abort_Call_MODE(const CString& mode_name,
								    const CString& log_id)
{
	CString log_msg;

	// 1. Check Object Status
	{
		int flag = pOBJ_CTRL__RF_BIAS->Is__OBJ_BUSY();			// Object Running Check
		if(flag > 0)											// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
		{
			log_msg.Format("%s ( Abort_Call_MODE(%s) ) - OBJ_CTRL__RF_BIAS->Is__OBJ_BUSY() is failed [%d] !", log_id, mode_name, flag);
			xLOG_CTRL->WRITE__LOG(log_msg);

			pOBJ_CTRL__RF_BIAS->Abort__OBJECT();
			pOBJ_CTRL__RF_BIAS->When__OBJECT();
		}
	}

	// ...
	{
		pOBJ_CTRL__RF_BIAS->Dislink__UPPER_OBJECT();

		int flag = pOBJ_CTRL__RF_BIAS->Call__OBJECT(mode_name);

		pOBJ_CTRL__RF_BIAS->Link__UPPER_OBJECT();

		if(flag < 0)
		{
			log_msg.Format("%s ( Abort_Call_MODE(%s) ) - OBJ_CTRL__RF_BIAS->Call__OBJECT(%s) is failed !", log_id, mode_name, mode_name, flag);
			xLOG_CTRL->WRITE__LOG(log_msg);

			return flag;
		}
	}

	return 1;
}
