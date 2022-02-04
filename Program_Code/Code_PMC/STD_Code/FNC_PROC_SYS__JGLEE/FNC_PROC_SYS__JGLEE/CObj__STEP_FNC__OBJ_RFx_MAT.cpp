#include "StdAfx.h"
#include "CObj__STEP_FNC.h"


/*
int CObj__STEP_FNC
::RF_MAT__BIAS_OBJ__Status_MODE(const CString& log_id)
{
	CString log_msg;
	CString cur_mode;

	// 1. Running Object Mode Get
	{
		int flag = pOBJ_CTRL__RF_MATCH->Get__OBJ_MODE(cur_mode);

		if(flag < 0)
		{
			log_msg.Format("%s ( Status_MODE(%s) ) - OBJ_CTRL__RF_MATCH_2MHz->Get__OBJ_MODE(%s) is failed [%d] !", log_id, cur_mode, cur_mode, flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// 2. Check Object Status
	{
		CString str_Status;
		
		int flag = pOBJ_CTRL__RF_MATCH->Get__OBJECT_STATUS();

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
::RF_MAT__BIAS_OBJ__Call_MODE(const CString& mode_name, 
							  const CString& log_id)
{
	CString log_msg;

	dEXT_CH__RF_MATCH__SELECT->Set__DATA("2MHz");

	// ...
	{
		int flag = pOBJ_CTRL__RF_MATCH->Call__OBJECT(mode_name);

		if(flag < 0)
		{
			log_msg.Format("%s ( Call_MODE(%s) ) - OBJ_CTRL__RF_MATCH_2MHz->Call__OBJECT(%s) is failed !", log_id, mode_name, mode_name, flag);
			xLOG_CTRL->WRITE__LOG(log_msg);

			return flag;
		}
	}

	return 1;
}
*/
