#include "StdAfx.h"
#include "CObj__STEP_FNC.h"


// ...
int CObj__STEP_FNC::ANY_MFC_OBJ__Check_ABORTED()
{
	int i;

	for(i=0; i<iOBJ_MFC__SIZE; i++)
	{
		if(dEXT_CH__MFC__CFG_USE_FLAG[i]->Check__DATA(STR__USE) < 0)
		{
			continue;
		}

		// ...
		int mfc_flag = pOBJ_CTRL__MFC[i]->Get__OBJECT_STATUS();

		if(mfc_flag == OBJECT_STATUS__ABORTED)
		{
			return 1;
		}
	}
	return -1;
}
int CObj__STEP_FNC::ALL_MFC_OBJ__Check_AVAILABLE()
{
	int i;

	for(i=0; i<iOBJ_MFC__SIZE; i++)
	{
		if(dEXT_CH__MFC__CFG_USE_FLAG[i]->Check__DATA(STR__USE) < 0)
		{
			continue;
		}

		// ...
		int mfc_flag = pOBJ_CTRL__MFC[i]->Get__OBJECT_STATUS();

		if(mfc_flag != OBJECT_STATUS__AVAILABLE)
		{
			return -1;
		}
	}
	
	return 1;
}

int CObj__STEP_FNC::ALL_MFC_OBJ__Start_MODE(const CString& mode_name)
{
	int i;
	
	for(i=0; i<iOBJ_MFC__SIZE; i++)
	{
		pOBJ_CTRL__MFC[i]->Run__OBJECT(mode_name);
	}	
	
	return 1;
}
int CObj__STEP_FNC::ALL_MFC_OBJ__Wait_MODE(const CString& log_id)
{
	int flag;
	int i;
	
	for(i=0; i<iOBJ_MFC__SIZE; i++)
	{
		flag = pOBJ_CTRL__MFC[i]->Is__OBJ_BUSY();			// Object Running Check

		if(flag > 0)										// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
		{
			continue;
		}
	}	
	
	return 1;
}
int CObj__STEP_FNC::ALL_MFC_OBJ__Call_MODE(const CString& mode_name,
										   const CString& log_id)
{
	CString log_msg;
	int	nIsBusy = -1;
	int	nRet = -1;
	int i;

	//.....
	// 1. Check Object Status, Call Object Mode
	for(i=0; i<iOBJ_MFC__SIZE; i++)
	{
		nIsBusy = pOBJ_CTRL__MFC[i]->Is__OBJ_BUSY();		// Object Running Check
		if(nIsBusy > 0)										// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
		{
			log_msg.Format("( ALL MFC Call_MODE(%s) ) - OBJ_CTRL__MFC[%d]->Is__OBJ_BUSY() is failed [%d] !", mode_name, i, nIsBusy);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		nRet = pOBJ_CTRL__MFC[i]->Call__OBJECT(mode_name);
		if(nRet < 0)
		{
			CString gas_name;
			sEXT_CH__MFC__CFG_GASx_NAME[i]->Get__DATA(gas_name);

			log_msg.Format("%s ( ALL MFC Call_MODE() ) - MFC(%s)'s %s mode action is failed !", log_id,gas_name,mode_name);
			xLOG_CTRL->WRITE__LOG(log_msg);

			log_msg.Format("%s ( ALL MFC Call_MODE(%s) ) - OBJ_CTRL__MFC[%d]->Call__OBJECT(%s) is failed !", log_id, mode_name, i, mode_name, nRet);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return nRet;
		}
	}	

	//.....
	return nRet;
}
int CObj__STEP_FNC::ALL_MFC_OBJ__Abort_Call_MODE(const CString& mode_name,
												 const CString& log_id)
{
	CString log_msg;
	int	nIsBusy = -1;
	int	nRet = -1;
	int i;

	//.....
	// 1. Check Object Status, Call Object Mode
	for(i=0; i<iOBJ_MFC__SIZE; i++)
	{
		nIsBusy = pOBJ_CTRL__MFC[i]->Is__OBJ_BUSY();		// Object Running Check
		if(nIsBusy > 0)										// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
		{
			log_msg.Format("( ALL MFC Abort_Call_MODE(%s) ) - OBJ_CTRL__MFC[%d]->Is__OBJ_BUSY() is failed [%d] !", mode_name, i, nIsBusy);
			xLOG_CTRL->WRITE__LOG(log_msg);

			//
			log_msg.Format("( ALL MFC Abort_Call_MODE(%s) ) - OBJ_CTRL__MFC[%d] : Abort Waited ... !", mode_name, i);
			xLOG_CTRL->WRITE__LOG(log_msg);

			pOBJ_CTRL__MFC[i]->Abort__OBJECT();
			pOBJ_CTRL__MFC[i]->When__OBJECT();

			log_msg.Format("( ALL MFC Abort_Call_MODE(%s) ) - OBJ_CTRL__MFC[%d] : Abort Completed ... !", mode_name, i);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		//.....
		// 2. Dislink Upper Call Object Mode
		pOBJ_CTRL__MFC[i]->Dislink__UPPER_OBJECT();

		//.....
		// 3. Call Object Mode
		nRet = pOBJ_CTRL__MFC[i]->Call__OBJECT(mode_name);

		//.....
		// 4. Link Upper Call Object Mode
		pOBJ_CTRL__MFC[i]->Link__UPPER_OBJECT();

		if(nRet < 0)
		{
			CString gas_name;
			sEXT_CH__MFC__CFG_GASx_NAME[i]->Get__DATA(gas_name);

			log_msg.Format("%s ( ALL MFC Abort_Call_MODE() ) - MFC(%s)'s %s mode action is failed !", log_id,gas_name,mode_name);
			xLOG_CTRL->WRITE__LOG(log_msg);

			log_msg.Format("%s ( ALL MFC Abort_Call_MODE(%s) ) - OBJ_CTRL__MFC[%d]->Call__OBJECT(%s) is failed !", log_id, mode_name, i, mode_name, nRet);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return nRet;
		}
	}	

	//.....
	return nRet;
}


