#include "StdAfx.h"
#include "CObj__TMP_IO.h"
#include "CObj__TMP_IO__ALID.h"


// ...
#define CMMD__INIT				"INIT"
#define CMMD__ON				"ON"
#define CMMD__OFF				"OFF"

// ...
#define CMMD_VAT__CLOSE			"CLOSE"
#define CMMD_VAT__OPEN			"OPEN"


// ...
int CObj__TMP_IO
::Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{

	return 1;
}

int CObj__TMP_IO
::Call__FULL_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(pOBJ_CTRL__VAT->Call__OBJECT(CMMD_VAT__CLOSE) < 0)
	{
		return -1;
	}

	Sleep(990);

	if(bActive__DO_TMP_PURGE_VALVE)			dEXT_CH__DO_TMP_PURGE_VALVE->Set__DATA(STR__CLOSE);
	if(bActive__DO_TMP_EXHAUST_VALVE)		dEXT_CH__DO_TMP_EXHAUST_VALVE->Set__DATA(STR__CLOSE);

	return 1;
}
int CObj__TMP_IO
::Call__FULL_OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int cfg_msec = 1500;
	int cur_msec = 0;
	int loop_msec = 100;

	while(1)
	{
		Sleep(loop_msec);

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -11;
		}

		// ...
		bool active__err_sns = false;

		if(bActive__DI_FORELINE_VAC_SNS)
		{
			if(dEXT_CH__DI_FORELINE_VAC_SNS->Check__DATA(STR__ON) < 0)			active__err_sns = true;
		}
		if(bActive__DI_BACKING_PUMP_ON)
		{
			if(dEXT_CH__DI_BACKING_PUMP_ON->Check__DATA(STR__ON) < 0)			active__err_sns = true;
		}

		if(dCH__MON_PUMP_ON_SNS->Check__DATA(STR__ON) < 0)
		{
			active__err_sns = true;
		}

		if(!active__err_sns)			break;

		// ...
		cur_msec += loop_msec;
		if(cur_msec < cfg_msec)			continue;

		if(active__err_sns)
		{
			int alarm_id = ALID__PUMP_STATE_ERROR;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			// ...
			{
				alm_bff.Format(" * %s <- %s \n", 
								sCH__MON_PUMP_STATE->Get__CHANNEL_NAME(),
								sCH__MON_PUMP_STATE->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format(" * %s <- %s \n", 
								dCH__MON_PUMP_ON_SNS->Get__CHANNEL_NAME(),
								dCH__MON_PUMP_ON_SNS->Get__STRING());
				alm_msg += alm_bff;
			}

			if(bActive__DI_FORELINE_VAC_SNS)
			{
				alm_bff.Format(" * %s <- %s \n", 
								dEXT_CH__DI_FORELINE_VAC_SNS->Get__CHANNEL_NAME(),
								dEXT_CH__DI_FORELINE_VAC_SNS->Get__STRING());
				alm_msg += alm_bff;
			}
			if(bActive__DI_BACKING_PUMP_ON)
			{
				alm_bff.Format(" * %s <- %s \n", 
								dEXT_CH__DI_BACKING_PUMP_ON->Get__CHANNEL_NAME(),
								dEXT_CH__DI_BACKING_PUMP_ON->Get__STRING());
				alm_msg += alm_bff;
			}

			p_alarm->Check__ALARM(alarm_id, r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
			return -12;
		}
	}

	// ...
	bool active__delay_check = false;

	if(dEXT_CH__DO_TMP_EXHAUST_VALVE->Check__DATA(STR__OPEN) < 0)
	{
		dEXT_CH__DO_TMP_EXHAUST_VALVE->Set__DATA(STR__OPEN);

		active__delay_check = true;
	}

	if(active__delay_check)
	{
		double cfg_sec = aCH__CFG_VAT_OPEN_DELAY_SEC->Get__VALUE();

		// ...
		SCX__TIMER_CTRL x_timer_ctrl;

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(aCH__CFG_VAT_OPEN_DELAY_SEC->Get__CHANNEL_NAME());

		if(x_timer_ctrl->WAIT(cfg_sec) < 0)			return -21;
	}

	if(pOBJ_CTRL__VAT->Call__OBJECT(CMMD_VAT__OPEN) < 0)
	{
		return -31;
	}
	return 1;
}

int CObj__TMP_IO
::Call__EXHAUST_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(bActive__DO_TMP_EXHAUST_VALVE)
		return dEXT_CH__DO_TMP_EXHAUST_VALVE->Set__DATA(STR__CLOSE);

	return 1;
}
int CObj__TMP_IO
::Call__EXHAUST_OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(bActive__DO_TMP_EXHAUST_VALVE)
	{
		return dEXT_CH__DO_TMP_EXHAUST_VALVE->Set__DATA(STR__OPEN);
	}
	return 1;
}

int CObj__TMP_IO
::Call__ON(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	// TMP Exhaust Valve Close ...
	if(bActive__DO_TMP_EXHAUST_VALVE)
	{
		dEXT_CH__DO_TMP_EXHAUST_VALVE->Set__DATA(STR__CLOSE);
	}

	// Backing.Pump Check ...
	if(bActive__DI_BACKING_PUMP_ON)
	{
		if(dEXT_CH__DI_BACKING_PUMP_ON->Check__DATA(STR__ON) < 0)
		{
			// Alarm ...
			{
				int alm_id = ALID__TMP_ON_ERROR;
				CString alm_msg;
				CString r_act;

				alm_msg.Format(" * %s <- %s \n",
								dEXT_CH__DI_BACKING_PUMP_ON->Get__CHANNEL_NAME(),
								dEXT_CH__DI_BACKING_PUMP_ON->Get__STRING());

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
			}
			return -11;
		}
	}

	// Foreline.Pressure Check ...
	if(bActive__DI_FORELINE_VAC_SNS)
	{
		if(dEXT_CH__DI_FORELINE_VAC_SNS->Check__DATA(STR__ON) < 0)
		{
			// Alarm ...
			{
				int alm_id = ALID__TMP_ON_ERROR;
				CString alm_msg;
				CString r_act;

				alm_msg.Format(" * %s <- %s \n",
								dEXT_CH__DI_FORELINE_VAC_SNS->Get__CHANNEL_NAME(),
								dEXT_CH__DI_FORELINE_VAC_SNS->Get__STRING());

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
			}
			return -21;
		}
	}

	if(iDATA__TMP_TYPE == _TMP_TYPE__OBJ)
	{
		if(pOBJ_CTRL__TMP->Call__OBJECT(sTMP_MODE__START) < 0)
			return -31;
	}
	else if(iDATA__TMP_TYPE == _TMP_TYPE__IO)
	{
		if(bActive__TMP_DO_RESET)		dEXT_CH__TMP_DO_RESET->Set__DATA(STR__OFF);
		if(bActive__TMP_DO_STOP)		dEXT_CH__TMP_DO_STOP->Set__DATA(STR__OFF);

		if(bActive__TMP_DO_START)		dEXT_CH__TMP_DO_START->Set__DATA(STR__ON);

		if(iActive__SIM_MODE > 0)
		{
			if(bActive__TMP_DI_NORMAL_SPEED)		dEXT_CH__TMP_DI_NORMAL_SPEED->Set__DATA(STR__ON);
			if(bActive__TMP_DI_ACCELERATION)		dEXT_CH__TMP_DI_ACCELERATION->Set__DATA(STR__OFF);

			if(bActive__TMP_DI_ALARM_STATE)			dEXT_CH__TMP_DI_ALARM_STATE->Set__DATA(STR__OFF);
			if(bActive__TMP_DI_WARNING_STATE)		dEXT_CH__TMP_DI_WARNING_STATE->Set__DATA(STR__OFF);
		}

		while(1)
		{
			Sleep(90);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -31;
			}

			if(sCH__MON_PUMP_STATE->Check__DATA(STR__NORMAL) > 0)
			{
				break;
			}
		}
	}

	return 1;
}
int CObj__TMP_IO
::Call__OFF(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm, const bool active__no_wait)
{
	bActive__FORELINE_VLV_CHECK = false;

	// ...
	SCX__TIMER_CTRL x_timer;
	x_timer->REGISTER__ABORT_OBJECT(sObject_Name);

	// Gate.Valve Close ...
	if(bActive__GV_USE)
	{
		dEXT_CH__GV_DO_OPEN->Set__DATA(STR__OFF);
		dEXT_CH__GV_DO_CLOSE->Set__DATA(STR__ON);
	}

	// VAT.Valve Close ...
	if(bActive__VAT_USE)
	{
		pOBJ_CTRL__VAT->Run__OBJECT(STR__CLOSE);
	}

	// TMP.OBJ Stop ...
	if(iDATA__TMP_TYPE == _TMP_TYPE__OBJ)
	{
		if(active__no_wait)
		{
			if(pOBJ_CTRL__TMP->Run__OBJECT(sTMP_MODE__STOP_NO_WAIT) < 0)		return -11;
		}
		else
		{
			if(pOBJ_CTRL__TMP->Call__OBJECT(sTMP_MODE__STOP) < 0)				return -12;
		}
	}
	else if(iDATA__TMP_TYPE == _TMP_TYPE__IO)
	{
		if(bActive__TMP_DO_RESET)		dEXT_CH__TMP_DO_RESET->Set__DATA(STR__OFF);
		if(bActive__TMP_DO_START)		dEXT_CH__TMP_DO_START->Set__DATA(STR__OFF);

		if(bActive__TMP_DO_STOP)		dEXT_CH__TMP_DO_STOP->Set__DATA(STR__ON);

		if(iActive__SIM_MODE > 0)
		{
			if(bActive__TMP_DI_NORMAL_SPEED)		dEXT_CH__TMP_DI_NORMAL_SPEED->Set__DATA(STR__OFF);
			if(bActive__TMP_DI_ACCELERATION)		dEXT_CH__TMP_DI_ACCELERATION->Set__DATA(STR__OFF);
		}

		if(active__no_wait)
		{
			
		}
		else
		{
			while(1)
			{
				Sleep(90);

				if(p_variable->Check__CTRL_ABORT() > 0)
				{
					return -11;
				}

				if(sCH__MON_PUMP_STATE->Check__DATA(STR__STOP) > 0)
				{
					break;
				}
			}
		}
	}

	// TMP Purge.Valve Close ...
	if(bActive__DO_TMP_PURGE_VALVE)
	{
		dEXT_CH__DO_TMP_PURGE_VALVE->Set__DATA(STR__CLOSE);

		double cfg_sec = aCH__CFG_TURBO_N2_PURGE_CLOSE_DELAY->Get__VALUE();
		if(x_timer->WAIT(cfg_sec) < 0)			return -21;
	}

	// TMP Exhaust Valve Close ...
	if(bActive__DO_TMP_EXHAUST_VALVE)
	{
		dEXT_CH__DO_TMP_EXHAUST_VALVE->Set__DATA(STR__CLOSE);

		double cfg_sec = aCH__CFG_TURBO_EXHAUST_VALVE_CLOSE_DELAY->Get__VALUE();
		if(x_timer->WAIT(cfg_sec) < 0)			return -31;
	}

	return 1;
}
