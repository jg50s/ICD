#include "StdAfx.h"
#include "CObj__STEP_BETA.h"
#include "CObj__STEP_BETA__DEF.h"


// RF.RPS ...
int CObj__STEP_BETA
::RF_RPS_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data)
{
	if(!bActive__OBJ_CTRL__RF_RPS)										return 1;
	if(dCH__CFG_RCP_PART_USE_RFx_RPS->Check__DATA(STR__YES) < 0)		return 2;

	aEXT_CH__RF_RPS__PARA_SET_POWER->Set__DATA(para_data);
	aEXT_CH__RF_RPS__PARA_HOLD_TIME->Set__VALUE(0.0);

	return pOBJ_CTRL__RF_RPS->Run__OBJECT(obj_mode);
}
int CObj__STEP_BETA
::RF_RPS_OBJ__Start_OFF()
{
	if(!bActive__OBJ_CTRL__RF_RPS)										return 1;
	if(dCH__CFG_RCP_PART_USE_RFx_RPS->Check__DATA(STR__YES) < 0)		return 2;

	// ...
	CString obj_mode = _RF_CMD__OFF;

	return pOBJ_CTRL__RF_RPS->Run__OBJECT(obj_mode);
}

int CObj__STEP_BETA
::RF_RPS_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__RF_RPS)										return -11;
	if(dCH__CFG_RCP_PART_USE_RFx_RPS->Check__DATA(STR__YES) < 0)		return -12;

	if((dEXT_CH__RF_RPS__MON_IDLE_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)
	|| (dEXT_CH__RF_RPS__MON_PROC_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0))
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
int CObj__STEP_BETA
::RF_RPS_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__RF_RPS)										return -11;
	if(dCH__CFG_RCP_PART_USE_RFx_RPS->Check__DATA(STR__YES) < 0)		return -12;

	int obj_sts = pOBJ_CTRL__RF_RPS->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}


// RF.PULSE ...
int CObj__STEP_BETA
::RF_PULSE_OBJ__Start_ON()
{
	if(!bActive__OBJ_CTRL__RF_PULSE)									return 1;
	if(dCH__CFG_RCP_PART_USE_RFx_PULSE->Check__DATA(STR__YES) < 0)		return 2;

	// ...
	{
		CString ch_data;

		ch_data = aCH__RCP_RF_PULSE_FREQUENCY->Get__STRING();
		aEXT_CH__RF_PULSE__PARA_RCP_FREQUENCY->Set__DATA(ch_data);

		ch_data = aCH__RCP_RF_PULSE_DUTY->Get__STRING();
		aEXT_CH__RF_PULSE__PARA_RCP_DUTY->Set__DATA(ch_data);

		ch_data = dCH__RCP_RF_PULSE_EXEC->Get__STRING();
		dEXT_CH__RF_PULSE__PARA_RCP_EXEC->Set__DATA(ch_data);

		//
		ch_data = aCH__RCP_RF_PULSE_ON_SHIFT_TIME->Get__STRING();
		aEXT_CH__RF_PULSE__PARA_RCP_ON_SHIFT_TIME->Set__DATA(ch_data);

		ch_data = aCH__RCP_RF_PULSE_OFF_SHIFT_TIME->Get__STRING();
		aEXT_CH__RF_PULSE__PARA_RCP_OFF_SHIFT_TIME->Set__DATA(ch_data);
	}

	// ...
	CString obj_mode = _PULSE_CMD__PARA_RCP_ON;
	
	return pOBJ_CTRL__RF_PULSE->Run__OBJECT(obj_mode);
}
int CObj__STEP_BETA
::RF_PULSE_OBJ__Start_OFF()
{
	if(!bActive__OBJ_CTRL__RF_PULSE)									return 1;
	if(dCH__CFG_RCP_PART_USE_RFx_PULSE->Check__DATA(STR__YES) < 0)		return 2;

	// ...
	CString obj_mode = _PULSE_CMD__PARA_RCP_OFF;

	return pOBJ_CTRL__RF_PULSE->Run__OBJECT(obj_mode);
}

int CObj__STEP_BETA
::RF_PULSE_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__RF_PULSE)									return -11;
	if(dCH__CFG_RCP_PART_USE_RFx_PULSE->Check__DATA(STR__YES) < 0)		return -12;

	if(dEXT_CH__RF_PULSE__MON_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 1;
	}

	return -1;
}
int CObj__STEP_BETA
::RF_PULSE_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__RF_PULSE)									return -11;
	if(dCH__CFG_RCP_PART_USE_RFx_PULSE->Check__DATA(STR__YES) < 0)		return -12;

	int obj_sts = pOBJ_CTRL__RF_PULSE->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}


// RF.LF ...
int CObj__STEP_BETA
::RF_LF_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data, const CString& para_pulse_mode)
{
	// ...
	{
		if(para_pulse_mode.CompareNoCase(STR__Pulse) == 0)				dEXT_CH__DO_RF_LF_PULSE_SET->Set__DATA(STR__ON);
		else															dEXT_CH__DO_RF_LF_PULSE_SET->Set__DATA(STR__OFF);
	}

	if(!bActive__OBJ_CTRL__RF_LF)										return 1;
	if(dCH__CFG_RCP_PART_USE_RFx_LF->Check__DATA(STR__YES) < 0)			return 2;

	aEXT_CH__RF_LF__PARA_SET_POWER->Set__DATA(para_data);
	aEXT_CH__RF_LF__PARA_HOLD_TIME->Set__VALUE(0.0);

	return pOBJ_CTRL__RF_LF->Run__OBJECT(obj_mode);
}
int CObj__STEP_BETA
::RF_LF_OBJ__Start_OFF()
{
	if(!bActive__OBJ_CTRL__RF_LF)										return 1;
	if(dCH__CFG_RCP_PART_USE_RFx_LF->Check__DATA(STR__YES) < 0)			return 2;

	// ...
	CString obj_mode = _RF_CMD__OFF;

	return pOBJ_CTRL__RF_LF->Run__OBJECT(obj_mode);
}

int CObj__STEP_BETA
::RF_LF_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__RF_LF)										return -11;
	if(dCH__CFG_RCP_PART_USE_RFx_LF->Check__DATA(STR__YES) < 0)			return -12;

	if((dEXT_CH__RF_LF__MON_IDLE_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)
	|| (dEXT_CH__RF_LF__MON_PROC_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0))
	{
		return 1;
	}

	if(dEXT_CH__RF_LF__MON_REFLECT_HIGH_LIMIT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 2;
	}
	if(dEXT_CH__RF_LF__MON_REFLECT_MAX_COEFFICIENT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 3;
	}

	return -1;
}
int CObj__STEP_BETA
::RF_LF_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__RF_LF)										return -11;
	if(dCH__CFG_RCP_PART_USE_RFx_LF->Check__DATA(STR__YES) < 0)			return -12;

	int obj_sts = pOBJ_CTRL__RF_LF->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}


// RF.HF ...
int CObj__STEP_BETA
::RF_HF_OBJ__Start_MODE(const CString& obj_mode, const CString& para_power, const CString& para_p2, const CString& para_pulse_mode)
{
	// ...
	{
		if(para_pulse_mode.CompareNoCase(STR__Pulse) == 0)				dEXT_CH__DO_RF_HF_PULSE_SET->Set__DATA(STR__ON);
		else															dEXT_CH__DO_RF_HF_PULSE_SET->Set__DATA(STR__OFF);
	}

	if(!bActive__OBJ_CTRL__RF_HF)										return 1;
	if(dCH__CFG_RCP_PART_USE_RFx_HF->Check__DATA(STR__YES) < 0)			return 2;

	aEXT_CH__RF_HF__PARA_SET_POWER->Set__DATA(para_power);
	aEXT_CH__RF_HF__PARA_SET_P2->Set__DATA(para_p2);

	aEXT_CH__RF_HF__PARA_HOLD_TIME->Set__VALUE(0.0);

	return pOBJ_CTRL__RF_HF->Run__OBJECT(obj_mode);
}
int CObj__STEP_BETA
::RF_HF_OBJ__Start_OFF()
{
	if(!bActive__OBJ_CTRL__RF_HF)										return 1;
	if(dCH__CFG_RCP_PART_USE_RFx_HF->Check__DATA(STR__YES) < 0)			return 2;

	// ...
	CString obj_mode = _RF_CMD__OFF;

	return pOBJ_CTRL__RF_HF->Run__OBJECT(obj_mode);
}

int CObj__STEP_BETA
::RF_HF_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__RF_HF)										return -11;
	if(dCH__CFG_RCP_PART_USE_RFx_HF->Check__DATA(STR__YES) < 0)			return -12;

	if((dEXT_CH__RF_HF__MON_IDLE_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)
	|| (dEXT_CH__RF_HF__MON_PROC_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0))
	{
		return 1;
	}

		if(dEXT_CH__RF_HF__MON_REFLECT_HIGH_LIMIT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 2;
	}
	if(dEXT_CH__RF_HF__MON_REFLECT_MAX_COEFFICIENT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 3;
	}

	return -1;
}
int CObj__STEP_BETA
::RF_HF_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__RF_HF)										return -11;
	if(dCH__CFG_RCP_PART_USE_RFx_HF->Check__DATA(STR__YES) < 0)			return -12;

	int obj_sts = pOBJ_CTRL__RF_HF->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}

