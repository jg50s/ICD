#include "StdAfx.h"
#include "CObj__STEP_STD.h"
#include "CObj__STEP_STD__DEF.h"


// ...
int CObj__STEP_STD
::APC_OBJ__Start_MODE(const CString& obj_mode, 
					  const CString& para_data, 
					  const double para_hold_sec,
					  const double para_hold_pos)
{
	if(!bActive__OBJ_CTRL__APC)						return 1;

		 if(obj_mode.CompareNoCase(_APC_CMD__POSITION) == 0)		aEXT_CH__APC_OBJ__PARA_POSITION->Set__DATA(para_data);
	else if(obj_mode.CompareNoCase(_APC_CMD__PRESSURE) == 0)		aEXT_CH__APC_OBJ__PARA_PRESSURE->Set__DATA(para_data);
	else															return -11;

	if(obj_mode.CompareNoCase(_APC_CMD__PRESSURE) == 0)	
	{
		aEXT_CH__APC_OBJ__PARA_HOLD_SEC->Set__VALUE(para_hold_sec);
		aEXT_CH__APC_OBJ__PARA_POSITION->Set__VALUE(para_hold_pos);
	}

	return pOBJ_CTRL__APC->Run__OBJECT(obj_mode);
}
int CObj__STEP_STD
::APC_OBJ__Start_OPEN()
{
	if(!bActive__OBJ_CTRL__APC)						return 1;

	CString obj_mode = _APC_CMD__OPEN;

	return pOBJ_CTRL__APC->Run__OBJECT(obj_mode);
}

int CObj__STEP_STD::APC_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__APC)						return -11;

	if((dEXT_CH__APC_OBJ__MON_IDLE_PRESSURE_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)			
	|| (dEXT_CH__APC_OBJ__MON_PROC_PRESSURE_ABORT_ACTIVE->Check__DATA(STR__ON) > 0))
	{
		return 1;
	}

	return -1;
}
int CObj__STEP_STD::APC_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__APC)						return -11;

	int obj_sts = pOBJ_CTRL__APC->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}

int CObj__STEP_STD::APC_OBJ__Check_STABLE()
{
	if(!bActive__OBJ_CTRL__APC)						return -11;

	if(dEXT_CH__APC_OBJ__MON_PROC_PRESSURE_STABLE_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 1;
	}

	return -1;
}
