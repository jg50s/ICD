#include "StdAfx.h"
#include "CObj__OneManiFold_LL.h"
#include "CObj__OneManiFold_LL__ALID.h"


int  CObj__OneManiFold_LL::
Fnc__LLx__PUMP_VLV_CLOSE()
{
	int flag = 1;

	// 1.
	if(doEXT_CH__LLx__SOFT_PUMP_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		flag = -1;
	}
	doEXT_CH__LLx__SOFT_PUMP_VLV__SET->Set__DATA(STR__IO_Close);

	// 2.
	if(doEXT_CH__LLx__FAST_PUMP_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		flag = -1;
	}
	doEXT_CH__LLx__FAST_PUMP_VLV__SET->Set__DATA(STR__IO_Close);

	return flag;
}
int  CObj__OneManiFold_LL::
Fnc__LLx__PUMP_VLV_OPEN(const int close_flag)
{
	if(close_flag > 0)
	{
		if(Fnc__LLx__VENT_VLV_CLOSE() < 0)
		{
			Fnc__VENT_VLV_CLOSE_DELAY();
		}
	}
	else
	{
		if(Check__LLx__VENT_VLV_CLOSE() < 0)
		{
			return -1;
		}
	}

	doEXT_CH__LLx__FAST_PUMP_VLV__SET->Set__DATA(STR__IO_Open);
	return 1;
}

int  CObj__OneManiFold_LL::
Fnc__LLx__VENT_VLV_CLOSE()
{
	int flag = 1;

	// 1.
	if(doEXT_CH__LLx__SOFT_VENT_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		flag = -1;
	}
	doEXT_CH__LLx__SOFT_VENT_VLV__SET->Set__DATA(STR__IO_Close);

	// 2.
	if(doEXT_CH__LLx__FAST_VENT_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		flag = -1;
	}
	doEXT_CH__LLx__FAST_VENT_VLV__SET->Set__DATA(STR__IO_Close);

	return flag;
}
int  CObj__OneManiFold_LL::
Check__LLx__VENT_VLV_CLOSE()
{
	// 1.
	if(doEXT_CH__LLx__SOFT_VENT_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		return -1;
	}
	doEXT_CH__LLx__SOFT_VENT_VLV__SET->Set__DATA(STR__IO_Close);

	// 2.
	if(doEXT_CH__LLx__FAST_VENT_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		return -1;
	}
	doEXT_CH__LLx__FAST_VENT_VLV__SET->Set__DATA(STR__IO_Close);

	return 1;
}

void CObj__OneManiFold_LL::
Fnc__PUMP_VLV_CLOSE_DELAY()
{
	SCX__TIMER_CTRL x_timer_ctrl;
	double delay_sec;
	CString var_data;

	aCH__CFG_PUMP_VALVE_CLOSE_TIMEOUT->Get__DATA(var_data);
	delay_sec = atof(var_data);
	if(delay_sec < 0.3)		delay_sec = 0.3;

	x_timer_ctrl->WAIT(delay_sec);
}
void CObj__OneManiFold_LL::
Fnc__VENT_VLV_CLOSE_DELAY()
{
	SCX__TIMER_CTRL x_timer_ctrl;
	double delay_sec;
	CString var_data;

	aCH__CFG_VENT_VALVE_CLOSE_TIMEOUT->Get__DATA(var_data);
	delay_sec = atof(var_data);
	if(delay_sec < 0.3)		delay_sec = 0.3;

	x_timer_ctrl->WAIT(delay_sec);
}
