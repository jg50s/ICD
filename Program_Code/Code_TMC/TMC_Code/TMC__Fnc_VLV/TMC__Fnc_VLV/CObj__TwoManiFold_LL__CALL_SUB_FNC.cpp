#include "StdAfx.h"
#include "CObj__TwoManiFold_LL.h"
#include "CObj__TwoManiFold_LL__ALID.h"


//----------------------------------------------------------------------------------------------------
// LBA -----
int  CObj__TwoManiFold_LL::
Fnc__LBA__PUMP_VLV_CLOSE()
{
	int flag = 1;

	// 1.
	if(doEXT_CH__LBA__SOFT_PUMP_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		flag = -1;
	}
	doEXT_CH__LBA__SOFT_PUMP_VLV__SET->Set__DATA(STR__IO_Close);

	// 2.
	if(doEXT_CH__LBA__FAST_PUMP_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		flag = -1;
	}
	doEXT_CH__LBA__FAST_PUMP_VLV__SET->Set__DATA(STR__IO_Close);

	return flag;
}
int  CObj__TwoManiFold_LL::
Fnc__LBA__PUMP_VLV_OPEN(const int close_flag)
{
	if(close_flag > 0)
	{
		if(Fnc__LBA__VENT_VLV_CLOSE() < 0)
		{
			Fnc__VENT_VLV_CLOSE_DELAY();
		}
	}
	else
	{
		if(Check__LBA__VENT_VLV_CLOSE() < 0)
		{
			return -1;
		}
	}

	doEXT_CH__LBA__FAST_PUMP_VLV__SET->Set__DATA(STR__IO_Open);
	return 1;
}

int  CObj__TwoManiFold_LL::
Fnc__LBA__VENT_VLV_CLOSE()
{
	int flag = 1;

	// 1.
	if(doEXT_CH__LBA__SOFT_VENT_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		flag = -1;
	}
	doEXT_CH__LBA__SOFT_VENT_VLV__SET->Set__DATA(STR__IO_Close);

	// 2.
	if(doEXT_CH__LBA__FAST_VENT_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		flag = -1;
	}
	doEXT_CH__LBA__FAST_VENT_VLV__SET->Set__DATA(STR__IO_Close);

	return flag;
}
int  CObj__TwoManiFold_LL::
Check__LBA__VENT_VLV_CLOSE()
{
	// 1.
	if(doEXT_CH__LBA__SOFT_VENT_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		return -1;
	}
	doEXT_CH__LBA__SOFT_VENT_VLV__SET->Set__DATA(STR__IO_Close);

	// 2.
	if(doEXT_CH__LBA__FAST_VENT_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		return -1;
	}
	doEXT_CH__LBA__FAST_VENT_VLV__SET->Set__DATA(STR__IO_Close);

	return 1;
}


// LBB -----
int  CObj__TwoManiFold_LL::
Fnc__LBB__PUMP_VLV_CLOSE()
{
	int flag = 1;

	// 1.
	if(doEXT_CH__LBB__SOFT_PUMP_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		flag = -1;
	}
	doEXT_CH__LBB__SOFT_PUMP_VLV__SET->Set__DATA(STR__IO_Close);

	// 2.
	if(doEXT_CH__LBB__FAST_PUMP_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		flag = -1;
	}
	doEXT_CH__LBB__FAST_PUMP_VLV__SET->Set__DATA(STR__IO_Close);

	return flag;
}
int  CObj__TwoManiFold_LL::
Fnc__LBB__PUMP_VLV_OPEN(const int close_flag)
{
	if(close_flag > 0)
	{
		if(Fnc__LBB__VENT_VLV_CLOSE() < 0)
		{
			Fnc__VENT_VLV_CLOSE_DELAY();
		}
	}
	else
	{
		if(Check__LBB__VENT_VLV_CLOSE() < 0)
		{
			return -1;
		}
	}

	doEXT_CH__LBB__FAST_PUMP_VLV__SET->Set__DATA(STR__IO_Open);
	return 1;
}

int  CObj__TwoManiFold_LL::
Fnc__LBB__VENT_VLV_CLOSE()
{
	int flag = 1;

	// 1.
	if(doEXT_CH__LBB__SOFT_VENT_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		flag = -1;
	}
	doEXT_CH__LBB__SOFT_VENT_VLV__SET->Set__DATA(STR__IO_Close);

	// 2.
	if(doEXT_CH__LBB__FAST_VENT_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		flag = -1;
	}
	doEXT_CH__LBB__FAST_VENT_VLV__SET->Set__DATA(STR__IO_Close);

	return flag;
}
int  CObj__TwoManiFold_LL::
Check__LBB__VENT_VLV_CLOSE()
{
	// 1.
	if(doEXT_CH__LBB__SOFT_VENT_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		return -1;
	}
	doEXT_CH__LBB__SOFT_VENT_VLV__SET->Set__DATA(STR__IO_Close);

	// 2.
	if(doEXT_CH__LBB__FAST_VENT_VLV__SET->Check__DATA(STR__IO_Close) < 0)
	{
		return -1;
	}
	doEXT_CH__LBB__FAST_VENT_VLV__SET->Set__DATA(STR__IO_Close);

	return 1;
}


void CObj__TwoManiFold_LL::
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
void CObj__TwoManiFold_LL::
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
