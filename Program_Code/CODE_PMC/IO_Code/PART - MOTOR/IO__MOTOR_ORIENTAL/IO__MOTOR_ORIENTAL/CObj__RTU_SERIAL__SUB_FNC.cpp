#include "StdAfx.h"
#include "CObj__RTU_SERIAL.h"


// ...
int CObj__RTU_SERIAL
::Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm, 
						   CString msg, 
						   const int alarm_id)
{
	CString r_act;

	p_alarm->Check__ALARM(alarm_id,r_act);
	p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, msg, r_act);

	if(r_act.CompareNoCase("RETRY") == 0)		return 1;

	return OBJ_ABORT;
}
int CObj__RTU_SERIAL
::Alarm__POST_CHECK(CII_OBJECT__ALARM* p_alarm, 
					CString msg, 
					const int alarm_id)
{
	CString r_act;

	p_alarm->Check__ALARM(alarm_id, r_act);
	p_alarm->Post__ALARM_With_MESSAGE(alarm_id, msg);

	return OBJ_ABORT;
}


// ...
int CObj__RTU_SERIAL
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
			int alm_id = ALID__CHUCKING_STATUS_ALARM__MON;
			CString alm_msg;
			CString alm_bff;

			alm_bff.Format("ESC current voltage : %.0f \n", cur__ai_esc_voltage);
			alm_msg += alm_bff;

			alm_bff.Format("PIN-UP threshold voltage : %.0f \n", cfg__esc_pin_up_volt);
			alm_msg += alm_bff;

			Alarm__POST_CHECK(p_alarm, alm_msg, alm_id);
			return -11;
		}
	}

	// ESC.Chuck_State Check ...
	if(bActive__ESC_CHUCK_STATE)
	{
		if(sEXT_CH__ESC_CHUCK_STATE->Check__DATA(STR__DECHUCKED) < 0)
		{
			int alm_id = ALID__CHUCKING_STATUS_ALARM__MON;
			CString alm_msg;

			sEXT_CH__ESC_CHUCK_STATE->Get__DATA(ch_data);
			alm_msg.Format("Chuck-State : %s ", ch_data);

			Alarm__POST_CHECK(p_alarm, alm_msg, alm_id);
			return -12;
		}
	}

	return 1;
}
