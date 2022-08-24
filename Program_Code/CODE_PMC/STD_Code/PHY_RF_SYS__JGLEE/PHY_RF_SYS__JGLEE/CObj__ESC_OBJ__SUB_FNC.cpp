#include "StdAfx.h"
#include "math.h"

#include "CObj__ESC_OBJ.h"



//-----------------------------------------------------------------------------------
int  CObj__ESC_OBJ
::Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm, const CString msg, const int alarm_id)
{
	CString r_act;

	p_alarm->Check__ALARM(alarm_id,r_act);
	p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, msg, r_act);

	if(r_act.CompareNoCase(STR__RETRY) == 0)
	{
		return 1;
	}
	return -1;
}
void CObj__ESC_OBJ
::Alarm__CHECK_POST(CII_OBJECT__ALARM *p_alarm, const CString msg, const int alarm_id)
{
	CString r_act;

	p_alarm->Check__ALARM(alarm_id, r_act);
	p_alarm->Post__ALARM_With_MESSAGE(alarm_id, msg);
}

int CObj__ESC_OBJ
::Check__CHUCK_STATUS(CII_OBJECT__ALARM *p_alarm, const CString cmp_status)
{

	while(1)
	{
		if(dCH__MON_CHUCK_STATUS->Check__DATA(cmp_status) > 0)
		{
			return 1;
		}

		// ...
		{
			int alarm_id = ALID__ESC_CHUCK_STATUS__UNKNOWN;

			CString cur_status;
			dCH__MON_CHUCK_STATUS->Get__DATA(cur_status);

			CString msg;
			msg.Format("Chuck Status is not %s. Current Chuck Status (%s)", cmp_status,cur_status);

			if(Alarm__CHECK_RETRY_ABORT(p_alarm, msg, alarm_id) < 0)
			{
				return -1;
			}
		}

		Sleep(10);
	}

	return 1;
}
