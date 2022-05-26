#include "StdAfx.h"
#include "CObj__EPD_SINGLE.h"



//--------------------------------------------------------------------------
double CObj__EPD_SINGLE::
Get__EPD_CUR_DATA()
{
	return aEXT_CH__EPD_SIGNAL->Get__VALUE();
}

double CObj__EPD_SINGLE:: 
Get__EPD_CUR_SEC()
{
	CString ch_data = sCH_INFO__CUR_EPD_START_SEC->Get__STRING();
	double  cur_sec = atof(ch_data);

	return cur_sec;
}


//--------------------------------------------------------------------------
int  CObj__EPD_SINGLE
::Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm,CString msg, const int alarm_id)
{
	CString r_act;

	p_alarm->Check__ALARM(alarm_id,r_act);
	p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, msg, r_act);
	if(r_act.CompareNoCase("RETRY") == 0)		return 1;
	return -1;
}

void CObj__EPD_SINGLE
::Alarm__POST_CHECK(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id)
{
	CString r_act;
	p_alarm->Check__ALARM(alarm_id, r_act);
	p_alarm->Post__ALARM_With_MESSAGE(alarm_id, msg);
}


//--------------------------------------------------------------------------
void CObj__EPD_SINGLE
::Fnc__WRITE_LOG(const CString& log_msg)
{
	xLOG_CTRL->WRITE__LOG(log_msg);
}

