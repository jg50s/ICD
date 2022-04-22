#include "stdafx.h"

#include "CObj__DURAPORT_SERIAL.h"
#include "CObj__DURAPORT_SERIAL__DEF.h"
#include "CObj__DURAPORT_SERIAL__ALID.h"


// ...
void CObj__DURAPORT_SERIAL::
Mon__STATE_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;
	CString ch_data;

	m_nCommSts = ONLINE;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);


		// ...
		{
			doCH__UPDATE_SYSTEM->Set__DATA(STR__ON);
			doCH__UPDATE_INDICATOR->Set__DATA(STR__ON);
		}

		if(iActive__SIM_MODE > 0)
		{
			m_nCommSts = ONLINE;

			// ...
			{
				ch_data = doCH__OPR_MAINT_MODE_SET->Get__STRING();
				sCH__BIT_STS__MAINT_MODE->Set__DATA(ch_data);
			}

			_Update__SYSTEM_STATUS();
		}

		if(m_nCommSts == ONLINE)				sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__ONLINE);
		else									sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__OFFLINE);

		if(sCH__MON_COMMUNICATION_STATE->Check__DATA(STR__OFFLINE) > 0)
		{
			int alarm_id = ALID__OFFLINE;
			CString r_act;
 				
			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
 		}
	}	
}

void CObj__DURAPORT_SERIAL::
Mon__PROC_RSP_MSG(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	_Proc__RSP_MSG();
}
