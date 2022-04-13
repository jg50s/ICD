#include "StdAfx.h"
#include "CObj__EPD_STD.h"



//--------------------------------------------------------------------------
double CObj__EPD_STD::
Get__IBx_SPEC_DATA()
{
	double  value_ibx_spec = 0.0;
	CString var_data;

	// IB1
	{
		aEXT_CH__IBx_SPEC_DATA[0]->Get__DATA(var_data);
		value_ibx_spec = atof(var_data);
	}

	return value_ibx_spec;
}

double CObj__EPD_STD:: 
Get__EPD_CUR_SEC()
{
	double cur_sec = 0.0;
	CString var_data;

	sCH_INFO__CUR_EPD_START_SEC->Get__DATA(var_data);
	cur_sec = atof(var_data);

	return cur_sec;
}


//--------------------------------------------------------------------------
int  CObj__EPD_STD
::Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm,CString msg, const int alarm_id)
{
	//.....
	CString r_act;

	p_alarm->Check__ALARM(alarm_id,r_act);
	p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, msg, r_act);
	if(r_act.CompareNoCase("RETRY") == 0)		return 1;
	return -1;
}

void CObj__EPD_STD
::Alarm__POST_CHECK(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id)
{
	CString r_act;
	p_alarm->Check__ALARM(alarm_id, r_act);
	p_alarm->Post__ALARM_With_MESSAGE(alarm_id, msg);
}


//--------------------------------------------------------------------------
void CObj__EPD_STD
::Fnc__WRITE_LOG(const CString& log_msg)
{
	xLOG_CTRL->WRITE__LOG(log_msg);
}

