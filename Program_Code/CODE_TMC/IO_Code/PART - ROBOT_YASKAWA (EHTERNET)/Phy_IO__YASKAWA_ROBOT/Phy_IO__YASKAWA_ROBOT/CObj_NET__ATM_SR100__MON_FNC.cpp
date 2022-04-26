#include "StdAfx.h"
#include "CObj_NET__ATM_SR100.h"
#include "CObj_NET__ATM_SR100__DEF.h"
#include "CObj_NET__ATM_SR100__ALID.h"

#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
void CObj_NET__ATM_SR100
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	if(iSim_Flag > 0)
	{
		m_nCommState = ONLINE;

		//
		sCH__MON_SYS_STS__WAFER_PRESENCE_STS1->Set__DATA(STR__OFF);
		sCH__MON_SYS_STS__WAFER_PRESENCE_STS2->Set__DATA(STR__OFF);

		sCH__MON_SYS_STS__MANIPULATOR_BATTERY->Set__DATA(STR__OK);
		sCH__MON_SYS_STS__SERVO_STATUS->Set__DATA(STR__ON);
		sCH__MON_SYS_STS__CONTROLLER_BATTERY->Set__DATA(STR__OK);
	}

	// ...
	CString ch_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);

		
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
	}	
}

