#include "StdAfx.h"
#include "CObj__STEP_LLx.h"


/*		
->Get__OBJECT_STATUS()	
#define  OBJECT_STATUS__UNKNOWN					    -1
#define  OBJECT_STATUS__ABORTED						1		// Abort END
#define  OBJECT_STATUS__AVAILABLE					2		// Complete
#define  OBJECT_STATUS__RUN							3
#define  OBJECT_STATUS__ABORT						4
#define  OBJECT_STATUS__PAUSE						5
#define  OBJECT_STATUS__RESUME						6
*/

//////////////////////////////////////////////////////////////////////////
// MFC OBJ - FNC

int CObj__STEP_LLx::ANY_MFC_OBJ__Check_ABORTED()
{
	// MFC_N2 ...
	if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
	{
		int mfc_flag = pOBJ_CTRL__MFC_N2->Get__OBJECT_STATUS();
		
		if(mfc_flag == OBJECT_STATUS__ABORTED)
		{
			return 1;
		}
	}

	return -1;
}
int CObj__STEP_LLx::ALL_MFC_OBJ__Check_AVAILABLE()
{
	// MFC_N2 ...
	if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
	{
		int mfc_flag = pOBJ_CTRL__MFC_N2->Get__OBJECT_STATUS();

		if(mfc_flag != OBJECT_STATUS__AVAILABLE)
		{
			return -1;
		}
	}
	
	return 1;
}

int CObj__STEP_LLx::ALL_MFC_OBJ__Start_MODE(const CString& mode_name)
{
	// MFC_N2 ...
	if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
	{
		pOBJ_CTRL__MFC_N2->Run__OBJECT(mode_name);
	}	
	
	return 1;
}
int CObj__STEP_LLx::ALL_MFC_OBJ__Wait_MODE(const CString& log_id)
{
	// MFC_N2 ...
	if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
	{
		while(1)
		{
			int r_flag = pOBJ_CTRL__MFC_N2->Is__OBJ_BUSY();		
			
			if(r_flag > 0)			// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
			{
				Sleep(10);
				continue;
			}
			return 1;
		}
	}		
	return 1;
}
int CObj__STEP_LLx::ALL_MFC_OBJ__Call_MODE(const CString& mode_name,
										   const CString& log_id)
{
	CString log_msg;

	if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
	{
		int nIsBusy = pOBJ_CTRL__MFC_N2->Is__OBJ_BUSY();

		if(nIsBusy > 0)				// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
		{
			log_msg.Format("(ALL MFC Call_MODE(%s)) - OBJ_CTRL__MFC_N2->Is__OBJ_BUSY() is failed [%d] !", mode_name, nIsBusy);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		int nRet = pOBJ_CTRL__MFC_N2->Call__OBJECT(mode_name);
		if(nRet < 0)
		{
			log_msg.Format("%s ( ALL MFC Call_MODE() ) - MFC(N2)'s %s mode action is failed !", log_id,mode_name);
			xLOG_CTRL->WRITE__LOG(log_msg);

			log_msg.Format("%s ( ALL MFC Call_MODE() ) - OBJ_CTRL__MFC_N2->Call__OBJECT(%s) is failed !", log_id, mode_name);
			xLOG_CTRL->WRITE__LOG(log_msg);
			
			return nRet;
		}
	}	

	return -1;
}
int CObj__STEP_LLx::ALL_MFC_OBJ__Abort_Call_MODE(const CString& mode_name,
												 const CString& log_id)
{
	CString log_msg;

	if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
	{
		int nIsBusy = pOBJ_CTRL__MFC_N2->Is__OBJ_BUSY();	
		
		if(nIsBusy > 0)					// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
		{
			log_msg.Format("( ALL MFC Abort_Call_MODE(%s) ) - OBJ_CTRL__MFC_N2->Is__OBJ_BUSY() is failed [%d] !", mode_name, nIsBusy);
			xLOG_CTRL->WRITE__LOG(log_msg);

			log_msg.Format("( ALL MFC Abort_Call_MODE(%s) ) - OBJ_CTRL__MFC_N2 : Abort Waited ... !", mode_name);
			xLOG_CTRL->WRITE__LOG(log_msg);

			pOBJ_CTRL__MFC_N2->Abort__OBJECT();
			pOBJ_CTRL__MFC_N2->When__OBJECT();

			log_msg.Format("( ALL MFC Abort_Call_MODE(%s) ) - OBJ_CTRL__MFC_N2 : Abort Completed ... !", mode_name);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		pOBJ_CTRL__MFC_N2->Dislink__UPPER_OBJECT();

		int nRet = pOBJ_CTRL__MFC_N2->Call__OBJECT(mode_name);

		pOBJ_CTRL__MFC_N2->Link__UPPER_OBJECT();

		if(nRet < 0)
		{
			log_msg.Format("%s ( ALL MFC Abort_Call_MODE() ) - MFC(N2)'s %s mode action is failed !", log_id, mode_name);
			xLOG_CTRL->WRITE__LOG(log_msg);

			log_msg.Format("%s ( ALL MFC Abort_Call_MODEs) ) - OBJ_CTRL__MFC_N2->Call__OBJECT(%s) is failed !", log_id, mode_name);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return nRet;
		}
	}	

	return -1;
}


