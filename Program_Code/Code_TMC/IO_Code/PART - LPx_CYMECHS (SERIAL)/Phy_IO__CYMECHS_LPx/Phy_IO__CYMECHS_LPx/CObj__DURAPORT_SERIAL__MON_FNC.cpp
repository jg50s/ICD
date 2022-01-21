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
	CString var_data;

	m_nCommSts = ONLINE;

	while(1)
	{
		cx_timer_ctrl->WAIT(0.5);

		// ...
		{
			doCH__UPDATE_SYSTEM->Set__DATA(STR__ON);
			doCH__UPDATE_INDICATOR->Set__DATA(STR__ON);
		}

		if(iSim_Mode > 0)
		{
			m_nCommSts = ONLINE;

			_Update__SYSTEM_STATUS();
		}

		if(m_nCommSts == ONLINE)				sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__ONLINE);
		else									sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__OFFLINE);

		if(sCH__MON_COMMUNICATION_STATE->Check__DATA(STR__OFFLINE) > 0)
		{
			CString r_act;
			int alarm_id = ALID__OFFLINE;
 				
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
