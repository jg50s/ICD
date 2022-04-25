#include "StdAfx.h"
#include "CObj__PIRANI_SERIAL.h"


// ...
void CObj__PIRANI_SERIAL::
Mon__ALM_REPORT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(iActive__SIM_MODE > 0)
	{
		iCOMM_STATE = _DEF__ONLINE;
	}

	// ...
	CString ch_data;

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);

		if(iSTATE__PRESSURE_TYPE == _PRESSURE_TYPE__ERROR)
		{
			Call__INIT(p_variable, p_alarm);
		}

		if(iActive__SIM_MODE > 0)
		{
			ch_data = dCH__CFG_PRESSURE_TYPE->Get__STRING();
			sCH__MON_PRESSURE_TYPE->Set__DATA(ch_data);

			ch_data = sCH__MON_PRESSURE_TORR->Get__STRING();
			sCH__MON_PRESSURE_VALUE->Set__DATA(ch_data);
		}

		if(iCOMM_STATE == _DEF__OFFLINE)
		{
			sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__OFFLINE);

			// ...
			{
				int alm_id = ALID__GAUGEx_OFFLINE;
				CString alm_msg;
				CString r_act;
			
				alm_msg.Format("Offline-Value : %.3f", aSet__Offline_Value);

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
			}

			ch_data.Format("%.3f", aSet__Offline_Value);
			sCH__MON_PRESSURE_TORR->Set__DATA(ch_data);
		}
		else
		{
			sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__ONLINE);
		}
	}
}
