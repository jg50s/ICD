#include "StdAfx.h"
#include "CObj__HERMOS_SERIAL.h"
#include "CObj__HERMOS_SERIAL__DEF.h"


//------------------------------------------------------------------------------------
void CObj__HERMOS_SERIAL::
Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;
	CString var_data;

	while(1)
	{
		cx_timer_ctrl->WAIT(2.0);

		if(iActive_SIM > 0)
		{
			if(diCH__COMM_STS->Check__DATA("OFFLINE") > 0)
				diCH__COMM_STS->Set__DATA("ONLINE");			
		}
		else
		{
			doCH__HEART_BEAT->Set__DATA("ON");
		}

		if(diCH__COMM_STS->Check__DATA("OFFLINE") > 0)
		{
			sCH__COMM_STS->Set__DATA("OFFLINE");

			// ...
			{
				CString r_act;
				int alarm_id = ALID__OFFLINE_ALARM;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}
		}
		else
		{
			sCH__COMM_STS->Set__DATA("ONLINE");
		}
	}	
}
