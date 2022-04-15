#include "StdAfx.h"
#include "CObj__MTC_FNC.h"
#include "CObj__MTC_FNC__DEF.h"
#include "CObj__MTC_FNC__ALID.h"

#include "Macro_Function.h"


// ...
int CObj__MTC_FNC
::Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(Fnc__INIT(p_variable,p_alarm) < 0)
	{
		sCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
		return -1;
	}
	sCH__MON_MTC_STATUS->Set__DATA(STR__IDLE);
	sCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	return 1;
}

int CObj__MTC_FNC
::Call__MAINTMODE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	sCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
	return OBJ_AVAILABLE;
}

int CObj__MTC_FNC
::Call__GATE_CTL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const bool bOpen)
{
	int flag = Fnc__GATE_CTL(p_variable,p_alarm,bOpen);

	if(flag < 0)
	{
		// ...
		{
			CString log_msg;
			log_msg.Format("Fnc__GATE_CTL_%d() : Failed [%d]...",bOpen, flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
		return flag;
	}

	return 1;
}

int CObj__MTC_FNC
::Call__PUMPING(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;

	// GATE.VLV CHECK ...
	if(dEXT_CH__MON_GATE_STATE->Check__DATA(STR__CLOSE) < 0)
	{
		return -101;
	}

	// ALL_VV_CLOSE ...
	{
		int flag = Fnc__ALL_VV_CLOSE(p_variable,p_alarm);

		if(flag < 0)
		{
			log_msg.Format("Fnc__ALL_VV_CLOSE() : Failed [%d]...",flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return flag;
		}
	}

	// SOFT-PUMPING ...
	{
		int flag = Fnc__SOFT_PUMPING(p_variable,p_alarm);

		if(flag < 0)
		{
			log_msg.Format("Fnc__SOFT_PUMPING() : Failed [%d]...",flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return flag;
		}
	}

	// FAST-PUMPING ...
	{
		int flag = Fnc__FAST_PUMPING(p_variable,p_alarm);

		if(flag < 0)
		{
			log_msg.Format("Fnc__FAST_PUMPING() : Failed [%d]...",flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return flag;
		}
	}

	return 1;
}

int CObj__MTC_FNC
::Call__VENT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;

	// GATE.VLV CHECK ...
	if(dEXT_CH__MON_GATE_STATE->Check__DATA(STR__CLOSE) < 0)
	{
		return -101;
	}

	// ALL_VV_CLOSE ...
	{
		int flag = Fnc__ALL_VV_CLOSE(p_variable,p_alarm);

		if(flag < 0)
		{
			log_msg.Format("Fnc__ALL_VV_CLOSE() : Failed [%d]...",flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return flag;
		}
	}

	// SOFT-VENT ...
	{
		int flag = Fnc__SOFT_VENT(p_variable,p_alarm);

		if(flag < 0)
		{
			log_msg.Format("Fnc__VENT() : Failed [%d]...",flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return flag;
		}
	}

	// FAST-VENT ...
	{
		int flag = Fnc__FAST_VENT(p_variable,p_alarm);

		if(flag < 0)
		{
			log_msg.Format("Fnc__VENT() : Failed [%d]...",flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return flag;
		}
	}
	// ALL_VV_CLOSE ...
	{
		int flag = Fnc__ALL_VV_CLOSE(p_variable,p_alarm);

		if(flag < 0)
		{
			log_msg.Format("Fnc__ALL_VV_CLOSE() : Failed [%d]...",flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return flag;
		}
	}

	return 1;
}