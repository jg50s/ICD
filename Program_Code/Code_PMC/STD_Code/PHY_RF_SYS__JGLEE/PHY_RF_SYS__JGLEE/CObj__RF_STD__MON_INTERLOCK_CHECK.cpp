#include "StdAfx.h"
#include "CObj__RF_STD.h"

#include "CObj__RF_STD__ALID.h"
#include "CObj__RF_STD__DEF.h"


// ...
int CObj__RF_STD
::Mon__INTERLOCK_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;

	// ...
	SCX__TIMER_CTRL x_timer;
	CString str_data;

	// Program Loading Wait ...
	x_timer->WAIT(10.0);

	if(iActive__SIM_MODE > 0)
	{
		dEXT_CH__DI_VAC_SNS->Set__DATA(STR__ON);
		dEXT_CH__DI_ATM_SNS->Set__DATA(STR__OFF);

		dEXT_CH__CHM_SHUTTER_STATE->Set__DATA(STR__CLOSE);
	}

	// ...
	int count__di_vac_sns = 0;
	int count__di_atm_sns = 0;
	int count__di_lid_close = 0;
	int count__di_shutter = 0;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		
		if(sCH__RF_CONDUCTANCE_INTLK_SKIP->Check__DATA("SKIP") > 0)
		{
			continue;
		}

		// DI VAC.SNS ...
		if(dEXT_CH__DI_VAC_SNS->Check__DATA(STR__ON) < 0)
		{
			if(count__di_vac_sns < 5)
			{
				count__di_vac_sns++;
			}
			else
			{
				count__di_vac_sns = 0;

				// ...
				{
					int alarm_id = ALID__VACUUM_SWITCH_ALARM;
					CString r_act;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);
				}

				dCH__RF_ABORT_FLAG->Set__DATA("ON");
				Call__OFF(p_variable, p_alarm);
			}
		}
		else
		{
			count__di_vac_sns = 0;
		}

		// DI ATM.SNS ...
		if(dEXT_CH__DI_ATM_SNS->Check__DATA(STR__OFF) < 0)
		{
			if(count__di_atm_sns < 5)
			{
				count__di_atm_sns++;
			}
			else
			{
				count__di_atm_sns = 0;

				// ...
				{
					int alarm_id = ALID__ATM_SWITCH_ALARM;
					CString r_act;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);
				}

				dCH__RF_ABORT_FLAG->Set__DATA("ON");
				Call__OFF(p_variable, p_alarm);
			}
		}

		// DI LID_CLOSE.SNS ...
		bool active__chm_lid_open = false;

		if(bActive__DI_CHM_LID_CLOSE_SNS)
		{
			if(dEXT_CH__DI_CHM_LID_CLOSE_SNS->Check__DATA(STR__ON) < 0)			active__chm_lid_open = true;
		}
		if(bActive__DI_CHM_LID_OPEN_SNS)
		{
			if(dEXT_CH__DI_CHM_LID_OPEN_SNS->Check__DATA(STR__OFF) < 0)			active__chm_lid_open = true;
		}

		if(active__chm_lid_open)
		{
			if(count__di_lid_close < 5)
			{
				count__di_lid_close++;
			}
			else
			{
				count__di_lid_close = 0;

				// ...
				{
					int alarm_id = ALID__CHAMBER_LID_INTLK_ALARM; 
					CString r_act;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);
				}

				dCH__RF_ABORT_FLAG->Set__DATA("ON");
				Call__OFF(p_variable, p_alarm);
			}
		}	
		else
		{
			count__di_lid_close = 0;
		}

		// DI SHUTTER.SNS ...
		if(dEXT_CH__CHM_SHUTTER_STATE->Check__DATA(STR__CLOSE) < 0)
		{
			if(count__di_shutter < 5)
			{
				count__di_shutter++;
			}
			else
			{
				count__di_shutter = 0;

				if(dCH__MON_IO_POWER_STATE->Check__DATA(STR__ON) > 0)
				{
					// ...
					{
						int alarm_id = ALID__CHAMBER_SHUTTER_NOT_CLOSE;
						CString r_act;

						p_alarm->Check__ALARM(alarm_id,r_act);
						p_alarm->Post__ALARM(alarm_id);
					}

					dCH__RF_ABORT_FLAG->Set__DATA("ON");
					Call__OFF(p_variable, p_alarm);
				}
			}
		}
		else
		{
			count__di_shutter = 0;
		}

		if(dEXT_CH__INTERLOCK_ACTIVE->Check__DATA(STR__ON) > 0)
		{
			// ...
			{
				int alarm_id = ALID__INTERLOCK_SENSOR_ALARM;
				CString alm_msg;
				CString r_act;

				alm_msg = sEXT_CH__INTERLOCK_MSG->Get__STRING();

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
			}

			dCH__RF_ABORT_FLAG->Set__DATA(STR__ON);

			Call__OFF(p_variable, p_alarm);
		}
	}

	return 1;
}

