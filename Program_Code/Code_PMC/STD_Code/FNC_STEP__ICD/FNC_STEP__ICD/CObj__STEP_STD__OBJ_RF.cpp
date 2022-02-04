#include "StdAfx.h"
#include "CObj__STEP_STD.h"
#include "CObj__STEP_STD__DEF.h"


// RF.RPS ...
int CObj__STEP_STD
::RF_RPS_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data)
{
	if(!bActive__OBJ_CTRL__RF_RPS)					return 1;

	aEXT_CH__RF_RPS__PARA_SET_POWER->Set__DATA(para_data);
	aEXT_CH__RF_RPS__PARA_HOLD_TIME->Set__VALUE(0.0);

	return pOBJ_CTRL__RF_RPS->Run__OBJECT(obj_mode);
}
int CObj__STEP_STD
::RF_RPS_OBJ__Start_OFF()
{
	if(!bActive__OBJ_CTRL__RF_RPS)					return 1;
	
	CString obj_mode = _RF_CMD__OFF;

	return pOBJ_CTRL__RF_RPS->Run__OBJECT(obj_mode);
}

int CObj__STEP_STD
::RF_RPS_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__RF_RPS)					return -11;

	if(dEXT_CH__RF_RPS__MON_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 1;
	}
	if(dEXT_CH__RF_RPS__MON_REFLECT_HIGH_LIMIT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 2;
	}
	if(dEXT_CH__RF_RPS__MON_REFLECT_MAX_COEFFICIENT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 3;
	}

	return -1;
}
int CObj__STEP_STD
::RF_RPS_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__RF_RPS)					return -1;

	int obj_sts = pOBJ_CTRL__RF_RPS->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}


// RF.400KHZ ...
int CObj__STEP_STD
::RF_400KHZ_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data)
{
	if(!bActive__OBJ_CTRL__RF_400KHZ)				return 1;

	aEXT_CH__RF_400KHZ__PARA_SET_POWER->Set__DATA(para_data);
	aEXT_CH__RF_400KHZ__PARA_HOLD_TIME->Set__VALUE(0.0);

	return pOBJ_CTRL__RF_400KHZ->Run__OBJECT(obj_mode);
}
int CObj__STEP_STD
::RF_400KHZ_OBJ__Start_OFF()
{
	if(!bActive__OBJ_CTRL__RF_400KHZ)				return 1;

	CString obj_mode = _RF_CMD__OFF;

	return pOBJ_CTRL__RF_400KHZ->Run__OBJECT(obj_mode);
}

int CObj__STEP_STD
::RF_400KHZ_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__RF_400KHZ)				return -11;

	if(dEXT_CH__RF_400KHZ__MON_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 1;
	}
	if(dEXT_CH__RF_400KHZ__MON_REFLECT_HIGH_LIMIT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 2;
	}
	if(dEXT_CH__RF_400KHZ__MON_REFLECT_MAX_COEFFICIENT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 3;
	}

	return -1;
}
int CObj__STEP_STD
::RF_400KHZ_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__RF_400KHZ)				return -1;

	int obj_sts = pOBJ_CTRL__RF_400KHZ->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}


// RF.40MHZ ...
int CObj__STEP_STD
::RF_40MHZ_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data)
{
	if(!bActive__OBJ_CTRL__RF_40MHZ)					return 1;

	aEXT_CH__RF_40MHZ__PARA_SET_POWER->Set__DATA(para_data);
	aEXT_CH__RF_40MHZ__PARA_HOLD_TIME->Set__VALUE(0.0);

	return pOBJ_CTRL__RF_40MHZ->Run__OBJECT(obj_mode);
}
int CObj__STEP_STD
::RF_40MHZ_OBJ__Start_OFF()
{
	if(!bActive__OBJ_CTRL__RF_40MHZ)				return 1;

	CString obj_mode = _RF_CMD__OFF;

	return pOBJ_CTRL__RF_40MHZ->Run__OBJECT(obj_mode);
}

int CObj__STEP_STD
::RF_40MHZ_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__RF_40MHZ)				return -11;

	if(dEXT_CH__RF_40MHZ__MON_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 1;
	}
	if(dEXT_CH__RF_40MHZ__MON_REFLECT_HIGH_LIMIT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 2;
	}
	if(dEXT_CH__RF_40MHZ__MON_REFLECT_MAX_COEFFICIENT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 3;
	}

	return -1;
}
int CObj__STEP_STD
::RF_40MHZ_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__RF_40MHZ)				return -1;

	int obj_sts = pOBJ_CTRL__RF_40MHZ->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}
