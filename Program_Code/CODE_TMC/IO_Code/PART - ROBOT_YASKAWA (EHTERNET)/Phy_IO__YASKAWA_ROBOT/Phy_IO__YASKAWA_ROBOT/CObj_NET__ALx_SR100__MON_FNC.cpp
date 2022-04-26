#include "StdAfx.h"
#include "CObj_NET__ALx_SR100.h"
#include "CObj_NET__ALx_SR100__DEF.h"
#include "CObj_NET__ALx_SR100__ALID.h"

#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
void CObj_NET__ALx_SR100
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	m_nCommState = ONLINE;

	while(1)
	{
		Sleep(500);

		if(iSim_Flag > 0)
		{
			m_nCommState = ONLINE;
		}

		if(m_nCommState == ONLINE)
		{
			sCH__OTR_OUT_MON__COMM_STS->Set__DATA(STR__ONLINE);
			sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__ONLINE);
		}
		else
		{
			sCH__OTR_OUT_MON__COMM_STS->Set__DATA(STR__OFFLINE);
			sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__OFFLINE);

			// ...
			{
				int alarm_id = ALID__OFFLINE_ALARM;
				CString r_act;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}
		}

		// ...
		{
			ch_data = diCH__PA_STS->Get__STRING();
		}
	}	
}

