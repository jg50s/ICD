#include "StdAfx.h"
#include "CObj__STP_SERIAL.h"

#include "math.h"



//------------------------------------------------------------------------------------
int  CObj__STP_SERIAL::Is__OFFLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(iActive__SIM_MODE > 0)
	{
		diCH__COMM_STS->Set__DATA(STR__ONLINE);
	}

	if(diCH__COMM_STS->Check__DATA(STR__OFFLINE) > 0)
	{
		int alarm_id = ALID__OFFLINE_ALARM;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);

		return -1;
	}
	return 1;
}
