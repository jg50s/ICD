#include "StdAfx.h"
#include "CObj__RFG_SERIAL.h"


// ...
int CObj__RFG_SERIAL
::Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	dCH__MON_COMM_STS->Set__DATA(STR__ONLINE); 


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


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
