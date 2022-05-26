#include "StdAfx.h"
#include "CObj__iTIM_TYPE.h"



//------------------------------------------------------------------------------------
void CObj__iTIM_TYPE::
Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm)
{
	CString pre__ctrl_mode = dCH__CFG_PUMP_CTRL_MODE->Get__STRING();


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		//
		bool active__err_check = true;
		if(dCH__CFG_PART_USE->Check__DATA("YES") < 0)		active__err_check = false;

		if(iACTIVE_SIM > 0)
		{
			if(diCH__COMM_STS->Check__DATA(STR__ONLINE) < 0)
			{
				diCH__COMM_STS->Set__DATA(STR__ONLINE);
				sCH__COMM_STS->Set__DATA(STR__ONLINE);
			}
		}
		else
		{
			if(diCH__COMM_STS->Check__DATA(STR__OFFLINE) > 0)
			{
				sCH__COMM_STS->Set__DATA(STR__OFFLINE);

				if(active__err_check)
				{
					CString r_act;
					int alarm_id = ALID__OFFLINE_ALARM;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);
				}
			}
			else
			{
				sCH__COMM_STS->Set__DATA(STR__ONLINE);
			}
		}

		if(dCH__CFG_PUMP_CTRL_MODE->Check__DATA(STR__MANUAL) > 0)
		{
			sCH__PUMP_STS->Set__DATA(STR__ON);
		}
		else
		{
			if(diCH__PUMP_STS->Check__DATA(STR__ON) > 0)
			{
				sCH__PUMP_STS->Set__DATA(STR__ON);
			}
			else
			{
				sCH__PUMP_STS->Set__DATA(STR__OFF);
			}
		}

		if(dCH__CFG_PUMP_CTRL_MODE->Check__DATA(pre__ctrl_mode) < 0)
		{
			dCH__CFG_PUMP_CTRL_MODE->Get__DATA(pre__ctrl_mode);

			if(pre__ctrl_mode.CompareNoCase(STR__AUTO) == 0)
			{
				int alarm_id = ALID__PUMP_CONTROL_MODE__MANUAL_TO_AUTO;
				CString r_act;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}
			else if(pre__ctrl_mode.CompareNoCase(STR__MANUAL) == 0)
			{
				int alarm_id = ALID__PUMP_CONTROL_MODE__AUTO_TO_MANUAL;
				CString r_act;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}	
		}
	}	

	// ...
}
