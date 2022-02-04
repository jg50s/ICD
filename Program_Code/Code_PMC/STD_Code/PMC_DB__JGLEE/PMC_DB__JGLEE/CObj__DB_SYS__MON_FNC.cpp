#include "StdAfx.h"
#include "CObj__DB_SYS.h"
#include "CObj__DB_SYS__DEF.h"


// ...
void CObj__DB_SYS
::Mon__PARAMETER_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int alm_id;
	CString alm_msg;
	CString r_act;

	
	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(iSIM_MODE > 0)
		{
			if(dCH__CFG_SCH_TEST_SIM_ALARM_REPORT_MODE->Check__DATA(STR__ENABLE) > 0)
			{
				int alarm_id = ALID__SIMULATION_MODE_ACTIVE;
				CString alm_msg;
				CString r_act;

				p_alarm->Check__ALARM(alarm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
			}
		}

		if(dCH__CFG_INTERLOCK_USE_FLAG->Check__DATA(STR__DISABLE) > 0)
		{
			alm_id = ALID__SETPOINT_INTERLOCK__DISABLE;

			alm_msg.Format("&s <- %s\n", 
							dCH__CFG_INTERLOCK_USE_FLAG->Get__CHANNEL_NAME(),
							dCH__CFG_INTERLOCK_USE_FLAG->Get__STRING());

			p_alarm->Check__ALARM(alm_id, r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
		}
		if(dCH__CFG_INTERLOCK_USE_FLAG->Check__DATA(STR__ALL_DISABLE) > 0)
		{
			alm_id = ALID__SETPOINT_AND_MONITORING_INTERLOCK__DISABLE;

			alm_msg.Format("&s <- %s\n", 
							dCH__CFG_INTERLOCK_USE_FLAG->Get__CHANNEL_NAME(),
							dCH__CFG_INTERLOCK_USE_FLAG->Get__STRING());

			p_alarm->Check__ALARM(alm_id, r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
		}
	}
}
