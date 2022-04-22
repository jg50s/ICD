#include "StdAfx.h"
#include "CObj__CHM_STD.h"
#include "CObj__CHM_STD__DEF.h"
#include "CObj__CHM_STD__ALID.h"


//----------------------------------------------------------------------------------------------------
int  CObj__CHM_STD
::Check__VENT_ALL_VLV__CLOSE(CII_OBJECT__ALARM* p_alarm)
{
	if(doEXT_CH__FAST_VENT_VLV__SET->Check__DATA(STR__CLOSE) < 0)			return -1;

	if(bActive__SOFT_VENT_VLV__SET)
	{
		if(doEXT_CH__SOFT_VENT_VLV__SET->Check__DATA(STR__CLOSE) < 0)		return -1;
	}

	return 1;
}
int  CObj__CHM_STD
::Check__PUMP_ALL_VLV__CLOSE(CII_OBJECT__ALARM* p_alarm)
{
	if(doEXT_CH__FAST_PUMP_VLV__SET->Check__DATA(STR__CLOSE) < 0)			return -1;

	if(bActive__SOFT_PUMP_VLV__SET)
	{
		if(doEXT_CH__SOFT_PUMP_VLV__SET->Check__DATA(STR__CLOSE) < 0)		return -1;
	}

	return 1;
}

int  CObj__CHM_STD
::Check__PUMP_VLV__OPEN(CII_OBJECT__ALARM* p_alarm)
{
	if(doEXT_CH__FAST_PUMP_VLV__SET->Check__DATA(STR__OPEN) > 0)			return 1;

	if(bActive__SOFT_PUMP_VLV__SET)
	{
		if(doEXT_CH__SOFT_PUMP_VLV__SET->Check__DATA(STR__OPEN) > 0)		return 1;
	}

	return -1;
}
void CObj__CHM_STD
::Update__PUMP_VLV_STS(CII_OBJECT__ALARM* p_alarm)
{
	if(Check__PUMP_VLV__OPEN(p_alarm) > 0)
	{
		sCH__PUMP_VLV_OPEN_FLAG->Set__DATA(STR__YES);
	}
	else
	{
		sCH__PUMP_VLV_OPEN_FLAG->Set__DATA("");
	}	
}

int  CObj__CHM_STD
::Fnc__VENT_ALL_VLV__CLOSE(CII_OBJECT__ALARM* p_alarm)
{
	int flag_close = 1;

	if(doEXT_CH__FAST_VENT_VLV__SET->Check__DATA(STR__CLOSE) < 0)
	{
		flag_close = -1;
	}
	if(bActive__SOFT_VENT_VLV__SET)
	{
		if(doEXT_CH__SOFT_VENT_VLV__SET->Check__DATA(STR__CLOSE) < 0)
			flag_close = -1;
	}
	if(bActive__ATM_EQUAL_VLV)
	{
		if(doEXT_CH__ATM_EQUAL_VLV__SET->Check__DATA(STR__CLOSE) < 0)
			flag_close = -1;
	}

	//
	doEXT_CH__FAST_VENT_VLV__SET->Set__DATA(STR__CLOSE);
	
	if(bActive__SOFT_VENT_VLV__SET)
	{
		doEXT_CH__SOFT_VENT_VLV__SET->Set__DATA(STR__CLOSE);
	}
	if(bActive__ATM_EQUAL_VLV)
	{
		doEXT_CH__ATM_EQUAL_VLV__SET->Set__DATA(STR__CLOSE);
	}

	//
	if(flag_close < 0)
	{
		SCX__TIMER_CTRL x_timer_ctrl;
		double delay_time;
		CString var_data;

		aCH__CFG_VALVE_CLOSE_DELAY_TIME->Get__DATA(var_data);
		delay_time = atof(var_data);

		if(delay_time < 0.3)	delay_time = 0.3;

		if(x_timer_ctrl->WAIT(delay_time) < 0)
		{
			return -1;
		}
	}
	return 1;
}
int  CObj__CHM_STD
::Fnc__VENT_ALL_VLV__CLOSE_WITHOUT_EQUAL_VLV(CII_OBJECT__ALARM* p_alarm)
{
	int flag_close = 1;

	if(doEXT_CH__FAST_VENT_VLV__SET->Check__DATA(STR__CLOSE) < 0)
	{
		flag_close = -1;
	}
	if(bActive__SOFT_VENT_VLV__SET)
	{
		if(doEXT_CH__SOFT_VENT_VLV__SET->Check__DATA(STR__CLOSE) < 0)
			flag_close = -1;
	}

	//
	doEXT_CH__FAST_VENT_VLV__SET->Set__DATA(STR__CLOSE);

	if(bActive__SOFT_VENT_VLV__SET)
	{
		doEXT_CH__SOFT_VENT_VLV__SET->Set__DATA(STR__CLOSE);
	}

	//
	if(flag_close < 0)
	{
		SCX__TIMER_CTRL x_timer_ctrl;
		double delay_time;
		CString var_data;

		aCH__CFG_VALVE_CLOSE_DELAY_TIME->Get__DATA(var_data);
		delay_time = atof(var_data);

		if(delay_time < 0.3)	delay_time = 0.3;

		if(x_timer_ctrl->WAIT(delay_time) < 0)
		{
			return -1;
		}
	}
	return 1;
}
int  CObj__CHM_STD
::Fnc__PUMP_ALL_VLV__CLOSE(CII_OBJECT__ALARM* p_alarm)
{
	int flag_close = 1;

	if(doEXT_CH__FAST_PUMP_VLV__SET->Check__DATA(STR__CLOSE) < 0)
	{
		flag_close = -1;
	}
	if(bActive__SOFT_PUMP_VLV__SET)
	{
		if(doEXT_CH__SOFT_PUMP_VLV__SET->Check__DATA(STR__CLOSE) < 0)
			flag_close = -1;
	}

	doEXT_CH__FAST_PUMP_VLV__SET->Set__DATA(STR__CLOSE);
	if(bActive__SOFT_PUMP_VLV__SET)
	{
		doEXT_CH__SOFT_PUMP_VLV__SET->Set__DATA(STR__CLOSE);
	}

	if(dCFG_CH__TM_BALLAST_MODE->Check__DATA(STR__VALVE) > 0)
	{
		doEXT_CH__BALLAST_VALVE_SET->Set__DATA(STR__CLOSE);
	}

	if(flag_close < 0)
	{
		SCX__TIMER_CTRL x_timer_ctrl;
		double delay_time;
		CString var_data;

		aCH__CFG_VALVE_CLOSE_DELAY_TIME->Get__DATA(var_data);
		delay_time = atof(var_data);

		if(delay_time < 0.3)	delay_time = 0.3;

		if(x_timer_ctrl->WAIT(delay_time) < 0)
		{
			return -1;
		}
	}
	return 1;
}

int  CObj__CHM_STD
::Fnc__PUMP_FAST_VLV__OPEN(CII_OBJECT__ALARM* p_alarm)
{
	if(bActive__SOFT_PUMP_VLV__SET)
		doEXT_CH__SOFT_PUMP_VLV__SET->Set__DATA(STR__CLOSE);

	doEXT_CH__FAST_PUMP_VLV__SET->Set__DATA(STR__OPEN);
	return 1;
}
int  CObj__CHM_STD
::Fnc__PUMP_SOFT_VLV__OPEN(CII_OBJECT__ALARM* p_alarm)
{
	doEXT_CH__FAST_PUMP_VLV__SET->Set__DATA(STR__CLOSE);

	if(bActive__SOFT_PUMP_VLV__SET)
		doEXT_CH__SOFT_PUMP_VLV__SET->Set__DATA(STR__OPEN);
	return 1;
}
int  CObj__CHM_STD
::Fnc__PUMP_BALLAST_VLV__OPEN(CII_OBJECT__ALARM* p_alarm)
{
	if(dCFG_CH__TM_BALLAST_MODE->Check__DATA(STR__VALVE) > 0)
	{
		doEXT_CH__BALLAST_VALVE_SET->Set__DATA(STR__OPEN);
	}
	return 1;
}

int  CObj__CHM_STD
::Fnc__VENT_FAST_VLV__OPEN(CII_OBJECT__ALARM* p_alarm)
{
	if(bActive__SOFT_VENT_VLV__SET)
		doEXT_CH__SOFT_VENT_VLV__SET->Set__DATA(STR__CLOSE);

	doEXT_CH__FAST_VENT_VLV__SET->Set__DATA(STR__OPEN);
	
	return 1;
}
int  CObj__CHM_STD
::Fnc__VENT_SOFT_VLV__OPEN(CII_OBJECT__ALARM* p_alarm)
{
	doEXT_CH__FAST_VENT_VLV__SET->Set__DATA(STR__CLOSE);

	if(bActive__SOFT_VENT_VLV__SET)
		doEXT_CH__SOFT_VENT_VLV__SET->Set__DATA(STR__OPEN);
	
	return 1;
}

void CObj__CHM_STD
::Fnc__MSG(const CString &sMsg)		
{
	sCH__MSG->Set__DATA(sMsg);
}
void CObj__CHM_STD
::Fnc__LOG(const CString &sLog)
{
	xLOG_CTRL->WRITE__LOG(sLog);
}

int CObj__CHM_STD
::Check__CHM_LID_CLOSE(CII_OBJECT__ALARM* p_alarm)
{
LOOP_RETRY:

	if(!bActive__LID_CLOSE)
	{
		return 1;
	}

	if(diEXT_CH__CHM_LID_CLOSE_SMS->Check__DATA(STR__ON) > 0)
	{
		return 1;
	}
	
	// ...
	{
		int alm_id = ALID__CHM_LID_NOT_CLOSED;
		CString alm_msg;
		CString r_act;

		alm_msg = "You can't execute the \"PUMP\" command !";

		p_alarm->Popup__ALARM_With_MESSAGE(alm_id,alm_msg,r_act);

		if(r_act.CompareNoCase(ACT__RETRY) == 0)
		{
			goto LOOP_RETRY;
		}
	}
	return -1;
}
