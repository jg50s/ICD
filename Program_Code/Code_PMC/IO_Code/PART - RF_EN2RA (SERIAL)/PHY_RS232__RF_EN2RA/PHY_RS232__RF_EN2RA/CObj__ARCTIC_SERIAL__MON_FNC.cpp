#include "StdAfx.h"
#include "CObj__ARCTIC_SERIAL.h"


// ...
int CObj__ARCTIC_SERIAL
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString pre__digital_power_set;
	CString ch_data;

	if(iActive__SIM_MODE > 0)
	{
		dCH__MON_COMM_STS->Set__DATA(STR__ONLINE); 
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(iActive__SIM_MODE > 0)
		{
			aoCH__DIGITAL_POWER_SET->Get__DATA(ch_data);
			if(pre__digital_power_set != ch_data)
			{
				pre__digital_power_set = ch_data;

				sCH__INFO_DELIVERED_POWER->Set__DATA(ch_data);
				sCH__INFO_POWER_SETPOINT->Set__DATA(ch_data);
			}
		}

		// ...
		{
			ch_data = sCH__INFO_DELIVERED_POWER->Get__STRING();
			double cur__dev_pwr = atof(ch_data);

			ch_data = sCH__INFO_POWER_SETPOINT->Get__STRING();
			double cur__set_pwr = atof(ch_data);

			double cur__ref_pwr = cur__set_pwr - cur__dev_pwr;
			ch_data.Format("%.1f", cur__ref_pwr);
			sCH__INFO_REFLECTED_POWER->Set__DATA(ch_data);
		}

		if(dCH__MON_COMM_STS->Check__DATA(STR__OFFLINE) > 0)
		{
			// ...
			int alarm_id = ALID__GEN_OFFLINE_ALARM;
			CString alm_msg;
			CString	r_act;

			alm_msg = sPROTOCOL_INFO;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
		}

		// ...
	}

	return 1;
}
