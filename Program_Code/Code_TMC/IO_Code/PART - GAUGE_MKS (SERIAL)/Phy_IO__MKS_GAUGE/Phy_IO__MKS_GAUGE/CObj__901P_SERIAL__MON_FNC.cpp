#include "StdAfx.h"
#include "CObj__901P_SERIAL.h"



//--------------------------------------------------------------------------------
void CObj__901P_SERIAL::
Mon__ALM_REPORT(CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	iCOMM_STATE = _DEF__ONLINE;

	while(1)
	{
		Sleep(500);

		if(iSim_Mode > 0)
		{
			iCOMM_STATE = _DEF__ONLINE;
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
			sCH__DATA_PRESSURE_TORR->Set__DATA(ch_data);
		}
		else
		{
			sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__ONLINE);
		}
	}
}
