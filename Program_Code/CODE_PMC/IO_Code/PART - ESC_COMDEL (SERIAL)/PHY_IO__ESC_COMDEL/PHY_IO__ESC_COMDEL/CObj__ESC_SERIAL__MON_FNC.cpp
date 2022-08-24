#include "StdAfx.h"
#include "CObj__ESC_SERIAL.h"


//------------------------------------------------------------------------------------
void CObj__ESC_SERIAL::
Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm)
{
	if(iActive__SIM_MODE > 0)
	{
		bActive__COMM_ONLINE = true;
	}
	else
	{
		bActive__COMM_ONLINE = false;
	}

	// ...
	CString ch_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.2);


		// ...
		{
			aoCH__VOLTAGE_SET->Get__DATA(ch_data);
			sCH__MON_VOLTAGE_SETPOINT->Set__DATA(ch_data);

			aoCH__CURRENT_LIMIT_SET->Get__DATA(ch_data);
			sCH__MON_CURRENT_LIMIT_SETPOINT->Set__DATA(ch_data);
		}

		if(bActive__COMM_ONLINE)
		{
			sCH__MON_COMM_STS->Set__DATA(STR__ONLINE);

		}
		else
		{
			sCH__MON_COMM_STS->Set__DATA(STR__OFFLINE);

			// ...
			{
				int alarm_id = ALID__OFFLINE_ALARM;
				CString alm_msg;
				CString	r_act;

				alm_msg = sPROTOCOL_INFO;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
			}
		}

		// ...
	}
}
