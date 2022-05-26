#include "StdAfx.h"
#include "CObj__ADC1000.h"
#include <math.h>



//------------------------------------------------------------------------------------
int  CObj__ADC1000
::Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm,CString msg, const int alarm_id)
{
	CString r_act;

	p_alarm->Check__ALARM(alarm_id,r_act);
	p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, msg, r_act);
	if(r_act.CompareNoCase("RETRY") == 0)		return 1;
	return -1;
}

int CObj__ADC1000
::Alarm__CHECK__POST(CII_OBJECT__ALARM *p_alarm,
					 const int alarm_id)
{
	CString r_act;
	p_alarm->Check__ALARM(alarm_id, r_act);
	p_alarm->Post__ALARM(alarm_id);

	return 1;
}

int CObj__ADC1000
::CheckOnline(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	while(1)
	{
		if(iACTIVE_SIM > 0)		diCH__COMM_STS->Set__DATA("Online");

		if(diCH__COMM_STS->Check__DATA("Online") > 0)				return 1;

		int alarm_id = ALID__OFFLINE_ALARM;
		if(Alarm__CHECK_RETRY_ABORT(p_alarm, "", alarm_id) < 0)		return -1;

		Sleep(9);
	}

	return 1;	
}

int CObj__ADC1000
::Check_OES_Open()
{
	if(m_nOpenSts == TRUE)		return 1;

	return -1;
}
