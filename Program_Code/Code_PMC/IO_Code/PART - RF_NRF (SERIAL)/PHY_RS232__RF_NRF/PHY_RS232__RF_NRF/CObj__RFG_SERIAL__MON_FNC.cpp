#include "StdAfx.h"
#include "CObj__RFG_SERIAL.h"


// ...
int CObj__RFG_SERIAL
::Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(iActive__SIM_MODE > 0)
	{
		sCH__INFO_STS_ALARM->Set__DATA(STR__Normal);
		sCH__INFO_STS_TEMPERATURE->Set__DATA(STR__Normal);
		sCH__INFO_STS_INTERLOCK->Set__DATA(STR__Normal);
		sCH__INFO_STS_AMP->Set__DATA(STR__Normal);

		sCH__INFO_STS_HD_CON->Set__DATA(STR__Enable);
	}

	dCH__MON_COMM_STS->Set__DATA(STR__ONLINE); 


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		// ...
		bool active__err_check = true;

		if(dCH__CFG_PART_USE->Check__DATA("YES") < 0)
		{
			active__err_check = false;
		}

		//
		if(iActive__SIM_MODE > 0)
		{
			CString ch_data;

			aoCH__POWER_SET->Get__DATA(ch_data);
			sCH__INFO_POWER_SETPOINT->Set__DATA(ch_data);
			sCH__INFO_FORWARD_POWER->Set__DATA(ch_data);
		}

		// IO.Update ...
		{
			siCH__RF_STATE->Get__STRING();
			siCH__POWER_SERPOINT->Get__STRING();
			siCH__POWER_FORWARD->Get__STRING();
			siCH__POWER_REFLECT->Get__STRING();
		}

		if(dCH__MON_COMM_STS->Check__DATA(STR__OFFLINE) > 0)
		{
			if(active__err_check)
			{
				int alarm_id = ALID__GEN_OFFLINE_ALARM;
				CString alm_msg;
				CString	r_act;

				alm_msg = sPROTOCOL_INFO;
	
				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
			}
		}
		else
		{
			if(active__err_check)
			{
				int err_count = 0;
				CString err_msg;
				CString err_bff;

				if(sCH__INFO_STS_ALARM->Check__DATA(STR__Normal) < 0)
				{
					err_count++;

					err_bff.Format(" * %s <- %s \n", 
									sCH__INFO_STS_ALARM->Get__CHANNEL_NAME(),
									sCH__INFO_STS_ALARM->Get__STRING());
					err_msg += err_bff;
				}
				if(sCH__INFO_STS_TEMPERATURE->Check__DATA(STR__Normal) < 0)
				{
					err_count++;

					err_bff.Format(" * %s <- %s \n", 
									sCH__INFO_STS_TEMPERATURE->Get__CHANNEL_NAME(),
									sCH__INFO_STS_TEMPERATURE->Get__STRING());
					err_msg += err_bff;
				}
				if(sCH__INFO_STS_INTERLOCK->Check__DATA(STR__Normal) < 0)
				{
					err_count++;

					err_bff.Format(" * %s <- %s \n", 
									sCH__INFO_STS_INTERLOCK->Get__CHANNEL_NAME(),
									sCH__INFO_STS_INTERLOCK->Get__STRING());
					err_msg += err_bff;
				}
				if(sCH__INFO_STS_AMP->Check__DATA(STR__Normal) < 0)
				{
					err_count++;

					err_bff.Format(" * %s <- %s \n", 
									sCH__INFO_STS_AMP->Get__CHANNEL_NAME(),
									sCH__INFO_STS_AMP->Get__STRING());
					err_msg += err_bff;
				}
				
				if(sCH__INFO_STS_HD_CON->Check__DATA(STR__Enable) < 0)
				{
					err_count++;

					err_bff.Format(" * %s <- %s \n", 
									sCH__INFO_STS_HD_CON->Get__CHANNEL_NAME(),
									sCH__INFO_STS_HD_CON->Get__STRING());
					err_msg += err_bff;
				}

				if(err_count > 0)
				{
					err_msg += "\n";

					err_bff.Format(" Error State Code is \"%s %s\" \n", 
									sCH__INFO_STS_HEXA_0->Get__STRING(),
									sCH__INFO_STS_HEXA_1->Get__STRING());
					err_msg += err_bff;
				}

				if(err_count > 0)
				{
					int alarm_id = ALID__STATE_ERROR;
					CString r_act;

					p_alarm->Check__ALARM(alarm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id, err_msg);
				}
			}
		}

		// ...
	}

	return 1;
}

int CObj__RFG_SERIAL
::Mon__IO_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.05);

		// ...
		{
			double p1_value = aoCH__POWER_SET->Get__VALUE();
			
			ch_data = sCH__MON_SET_P2->Get__STRING();
			double p2_value = atof(ch_data);

			// ...
			bool active__do_pulse_mode = false;

			if(bActive__DO_PULSE_MODE)
			{
				if(dEXT_CH__DO_PULSE_MODE->Check__DATA(STR__ON) > 0)			active__do_pulse_mode = true;
			}

			if(active__do_pulse_mode)
			{
				double set_per;

				if(p1_value < 1.0)		set_per = 100.0;
				else					set_per = (p2_value / p1_value) * 100.0;

				if(set_per > 100.0)     set_per = 100.0;

				ch_data.Format("%.1f", set_per);
				sCH__MON_POWER_LEVEL_PERCENT->Set__DATA(ch_data);
			}
			else
			{
				sCH__MON_POWER_LEVEL_PERCENT->Set__DATA("100.0");
			}

			if(bActive__AO_LEVEL_VOLT)
			{
				ch_data = sCH__MON_POWER_LEVEL_PERCENT->Get__STRING();
				//double set_volt = 10.0 - (atof(ch_data) / 10.0);
				double set_volt = atof(ch_data) / 10.0;
				
					 if(set_volt <  0.0)		set_volt = 0.0;
				else if(set_volt > 10.0)		set_volt = 10.0;

				aEXT_CH__AO_LEVEL_VOLT->Set__VALUE(set_volt);
			}
		}
	}

	return 1;
}
