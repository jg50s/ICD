#include "StdAfx.h"
#include "CObj__LIFT_PIN_IO.h"


// ...
int  CObj__LIFT_PIN_IO
::Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id)
{
	CString r_act;

	p_alarm->Check__ALARM(alarm_id,r_act);
	p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, msg, r_act);

	if(r_act.CompareNoCase("RETRY") == 0)		return 1;

	return OBJ_ABORT;
}


int  CObj__LIFT_PIN_IO
::Alarm__POST_CHECK(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id)
{
	CString r_act;

	p_alarm->Check__ALARM(alarm_id, r_act);
	p_alarm->Post__ALARM_With_MESSAGE(alarm_id, msg);

	return OBJ_ABORT;
}

void CObj__LIFT_PIN_IO
::Fnc__WRITE_LOG(const CString& log_msg)
{
	xLOG_CTRL->WRITE__LOG(log_msg);
}

int CObj__LIFT_PIN_IO
::Fnc__CHECK_CHUCKING(CII_OBJECT__VARIABLE *p_variable,
					  CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	// ESC.AI_Voltage : Check ...
	{
		double cfg__esc_pin_up_volt = aCH__CFG_ESC_VOLTAGE_PIN_UP_THRESHOLD->Get__VALUE();
		double cur__ai_esc_voltage = 0;

		bool active__esc_voltage = false;

		if(cfg__esc_pin_up_volt > 0.1)
		{
			for(int i=0; i<iDATA__ESC_CH_SIZE; i++)
			{
				cur__ai_esc_voltage = aEXT_CH__ESC_AI_VOLTAGE_X[i]->Get__VALUE();
				if(cur__ai_esc_voltage < cfg__esc_pin_up_volt)		continue;
	
				active__esc_voltage = true;
				break;
			}
		}

		if(active__esc_voltage)
		{
			int alm_id = ALID__CHUCKING_STATUS_ALARM;
			CString alm_msg;
			CString alm_bff;

			alm_bff.Format("ESC current voltage : %d \n", cur__ai_esc_voltage);
			alm_msg += alm_bff;

			alm_bff.Format("PIN-UP threshold voltage : %d \n", cfg__esc_pin_up_volt);
			alm_msg += alm_bff;

			Alarm__POST_CHECK(p_alarm, alm_msg, alm_id);
			return -11;
		}
	}

	// ESC.Chuck_State Check ...
	if(bActive__ESC_CHUCK_STATE)
	{
		if(sEXT_CH__ESC_CHUCK_STATE->Check__DATA("DECHUCKED") > 0)
		{
			return 1;
		}

		// ...
		{
			int alm_id = ALID__CHUCKING_STATUS_ALARM;
			CString alm_msg;

			sEXT_CH__ESC_CHUCK_STATE->Get__DATA(ch_data);
			alm_msg.Format("Chuck-State : %s ", ch_data);

			Alarm__POST_CHECK(p_alarm, alm_msg, alm_id);
		}
		return -1;
	}

	return 1;
}

void CObj__LIFT_PIN_IO
::_Fnc__SIM_PIN_POD(const bool active_up, const bool active_down, const bool active_middle)
{
	Sleep(1000);

	if(iDATA__PIN_SNS_TYPE == _PIN_TYPE__DI_SNS)
	{
		dEXT_CH__DI_PIN_UP->Set__DATA(STR__OFF);
		dEXT_CH__DI_PIN_DOWN->Set__DATA(STR__OFF);
		dEXT_CH__DI_PIN_MIDDLE->Set__DATA(STR__OFF);

		if(active_up)			dEXT_CH__DI_PIN_UP->Set__DATA(STR__ON);
		if(active_down)			dEXT_CH__DI_PIN_DOWN->Set__DATA(STR__ON);
		if(active_middle)		dEXT_CH__DI_PIN_MIDDLE->Set__DATA(STR__ON);
	}
	else
	{
		double cfg__up_min = 0.0;
		double cfg__up_max = 0.0;
		int i;

		for(i=0; i<iSIZE__AI_PIN__POS; i++)
		{
			if(active_up)
			{
				cfg__up_min = aCH__CFG_UP_POS_MIN__PIN_X[i]->Get__VALUE();
				cfg__up_max = aCH__CFG_UP_POS_MAX__PIN_X[i]->Get__VALUE();
			}
			else if(active_down)
			{
				cfg__up_min = aCH__CFG_DOWN_POS_MIN__PIN_X[i]->Get__VALUE();
				cfg__up_max = aCH__CFG_DOWN_POS_MAX__PIN_X[i]->Get__VALUE();
			}
			else if(active_middle)
			{
				cfg__up_min = aCH__CFG_MIDDLE_POS_MIN__PIN_X[i]->Get__VALUE();
				cfg__up_max = aCH__CFG_MIDDLE_POS_MAX__PIN_X[i]->Get__VALUE();
			}
			else
			{
				continue;
			}

			double ref__pin_pos = (cfg__up_min + cfg__up_max) * 0.5;
			aEXT_CH__AI_PIN_POS_X[i]->Set__VALUE(ref__pin_pos);
		}
	}
}
