#include "StdAfx.h"
#include "CObj__MS_FC100.h"



//--------------------------------------------------------------------------------
void CObj__MS_FC100::
Mon__ALM_REPORT(CII_OBJECT__ALARM *p_alarm)
{
	int alm_id;
	CString r_act;

	iCOMM_STATE = ONLINE;

	while(1)
	{
		Sleep(500);

		if(iSim_Mode > 0)
		{
			iCOMM_STATE = ONLINE;
		}

		if(iCOMM_STATE == ONLINE)
		{
			sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__ONLINE);
		}
		else
		{
			sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__OFFLINE);

			// ...
			{	
				int alm_id = ALID__FFU_OFFLINE;

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM(alm_id);
			}
		}
	}
}
