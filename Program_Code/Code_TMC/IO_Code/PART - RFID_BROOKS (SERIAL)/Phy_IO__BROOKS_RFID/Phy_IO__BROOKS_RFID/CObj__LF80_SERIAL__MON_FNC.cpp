#include "StdAfx.h"
#include "CObj__LF80_SERIAL.h"
#include "CObj__LF80_SERIAL__DEF.h"


//------------------------------------------------------------------------------------
void CObj__LF80_SERIAL::
Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm)
{
	CString var_data;

	m_nCommState = ONLINE;

	while(1)
	{
		Sleep(500);

		if(iSim_Flag > 0)
		{
			m_nCommState = ONLINE;
		}
		else
		{
			doCH__HEART_BEAT->Set__DATA("ON");
		}

		if(m_nCommState == OFFLINE)
		{
			sCH__MON_COMMUNICATION_STATE->Set__DATA("OFFLINE");

			// ...
			{
				int alarm_id = ALID__OFFLINE_ALARM;
				CString r_act;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}
		}
		else
		{
			sCH__MON_COMMUNICATION_STATE->Set__DATA("ONLINE");
		}
	}	
}
