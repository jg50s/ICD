#include "StdAfx.h"
#include "CObj__STEP_FNC.h"


/*
//---------------------------------------------------------------------------------------------------------
int CObj__STEP_FNC::HEATER_WALL__Start_MODE(const CString& mode_name)
{
	CString log_msg;
	int	nIsBusy = -1;
	int	nRet = -1;

	// 1. Check Object Status
	nIsBusy = pOBJ_CTRL__HEATER_WALL->Is__OBJ_BUSY();		// Object Running Check
	if(nIsBusy > 0)											// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
	{
		log_msg.Format("( Start_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Is__OBJ_BUSY() is failed [%d] !", mode_name, nIsBusy);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// 2. Run Object Mode
	nRet = pOBJ_CTRL__HEATER_WALL->Run__OBJECT(mode_name);
	if(nRet < 0)
	{
		log_msg.Format("( Start_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Run__OBJECT(%s) is failed [%d] !", mode_name, mode_name, nRet);
		xLOG_CTRL->WRITE__LOG(log_msg);
		return nRet;
	}
	
	//.....
	return nRet;
}

int CObj__STEP_FNC::HEATER_WALL__Wait_MODE(const CString& log_id)
{
	CString log_msg;
	CString cur_mode;
	int	nRet = -1;

	//.....
	// 1. Running Object Mode Get
	nRet = pOBJ_CTRL__HEATER_WALL->Get__OBJ_MODE(cur_mode);
	if(nRet < 0)
	{
		log_msg.Format("%s ( Wait_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Get__OBJ_MODE(%s) is failed [%d] !", log_id, cur_mode, cur_mode, nRet);
		xLOG_CTRL->WRITE__LOG(log_msg);
		// return nRet;
	}

	//.....
	// 2. Waiting Object Complete
	nRet = pOBJ_CTRL__HEATER_WALL->When__OBJECT();
	if(nRet < 0)
	{
		log_msg.Format("%s ( Wait_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->When__OBJECT() is failed [%d] !", log_id, cur_mode, nRet);
		xLOG_CTRL->WRITE__LOG(log_msg);
		return nRet;
	}

	//.....
	return nRet;
}

int CObj__STEP_FNC::HEATER_WALL__Status_MODE(const CString& log_id)
{
	CString log_msg;
	CString cur_mode;
	int	nRet = -1;

	//.....
	// 1. Running Object Mode Get
	nRet = pOBJ_CTRL__HEATER_WALL->Get__OBJ_MODE(cur_mode);
	if(nRet < 0)
	{
		log_msg.Format("%s ( Status_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Get__OBJ_MODE(%s) is failed [%d] !", log_id, cur_mode, cur_mode, nRet);
		xLOG_CTRL->WRITE__LOG(log_msg);
		// return nRet;
	}

	//.....
	// 2. Check Object Status
	CString str_Status;
	nRet = pOBJ_CTRL__HEATER_WALL->Get__OBJECT_STATUS();
	switch(nRet)
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

	return nRet;		// Object Status Result
}

int CObj__STEP_FNC::HEATER_WALL__Call_MODE(const CString& mode_name, const CString& log_id)
{
	CString log_msg;
	int	nIsBusy = -1;
	int	nRet = -1;

	//.....
	// 1. Check Object Status
	nIsBusy = pOBJ_CTRL__HEATER_WALL->Is__OBJ_BUSY();		// Object Running Check
	if(nIsBusy > 0)											// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
	{
		log_msg.Format("%s ( Call_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Is__OBJ_BUSY() is failed [%d] !", log_id, mode_name, nIsBusy);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	//.....
	// 2. Call Object Mode
	nRet = pOBJ_CTRL__HEATER_WALL->Call__OBJECT(mode_name);
	if(nRet < 0)
	{
		log_msg.Format("%s ( Call_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Call__OBJECT(%s) is failed !", log_id, mode_name, mode_name, nRet);
		xLOG_CTRL->WRITE__LOG(log_msg);
		return nRet;
	}

	//.....
	return nRet;
}

int CObj__STEP_FNC::HEATER_WALL__Abort_Call_MODE(const CString& mode_name, const CString& log_id)
{
	CString log_msg;
	int	nIsBusy = -1;
	int	nRet = -1;

	//.....
	// 1. Check Object Status
	nIsBusy = pOBJ_CTRL__HEATER_WALL->Is__OBJ_BUSY();		// Object Running Check
	if(nIsBusy > 0)											// BUSY > 0,  AVAILABLE = -1, ABORTED = -2, IDLE = -3
	{
		log_msg.Format("%s ( Abort_Call_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Is__OBJ_BUSY() is failed [%d] !", log_id, mode_name, nIsBusy);
		xLOG_CTRL->WRITE__LOG(log_msg);

		//
		pOBJ_CTRL__HEATER_WALL->Abort__OBJECT();
		pOBJ_CTRL__HEATER_WALL->When__OBJECT();
	}

	//.....
	// 2. Dislink Upper Call Object Mode
	pOBJ_CTRL__HEATER_WALL->Dislink__UPPER_OBJECT();

	//.....
	// 3. Call Object Mode
	nRet = pOBJ_CTRL__HEATER_WALL->Call__OBJECT(mode_name);

	//.....
	// 4. Link Upper Call Object Mode
	pOBJ_CTRL__HEATER_WALL->Link__UPPER_OBJECT();
	
	if(nRet < 0)
	{
		log_msg.Format("%s ( Abort_Call_MODE(%s) ) - OBJ_CTRL__HEATER_WALL->Call__OBJECT(%s) is failed !", log_id, mode_name, mode_name, nRet);
		xLOG_CTRL->WRITE__LOG(log_msg);
		return nRet;
	}

	//.....
	return nRet;
}
*/
