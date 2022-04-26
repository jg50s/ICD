#include "StdAfx.h"
#include "CObj_NET__ALx_SR100.h"
#include "CObj_NET__ALx_SR100__DEF.h"
#include "CObj_NET__ALx_SR100__ALID.h"

#include "math.h"
#include "CCommon_DEF.h"
#include "Macro_Function.h"


//------------------------------------------------------------------------------------
int  CObj_NET__ALx_SR100
::Is__LOCAL(CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}
int  CObj_NET__ALx_SR100
::Is__OFFLINE(CII_OBJECT__ALARM* p_alarm)
{
LOOP_RETRY:

	if(m_nCommState == OFFLINE)
	{
		int alarm_id = ALID__OFFLINE_ALARM;
		CString r_act;

		p_alarm->Popup__ALARM(alarm_id,r_act);

		if(r_act.CompareNoCase("RETRY") == 0)
		{
			goto LOOP_RETRY;
		}
		return -1;
	}

	return 1;
}

//------------------------------------------------------------------------------------
int  CObj_NET__ALx_SR100
::Fnc__IS_COMM_ONLINE()
{
	if(m_nCommState == ONLINE)
	{
		return 1;
	}
	return -1;
}
int  CObj_NET__ALx_SR100
::Fnc__ONLINE_CHECK(CII_OBJECT__ALARM* p_alarm,
				    const int alarm_check)
{
	SCX__TIMER_CTRL x_timer_ctrl;
	x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);

	if(iSim_Flag > 0)     
	{	
		sCH__INR__ERROR_ID->Set__DATA("0");
		sCH__INR__ALGINER_ERROR_ID->Set__DATA("0");
	}

	if(Fnc__IS_COMM_ONLINE() > 0)
	{
		CString str__err_id;
		int i__err_id;

		sCH__INR__ERROR_ID->Get__DATA(str__err_id);
		i__err_id = atoi(str__err_id);

		if((i__err_id != 0)&&(alarm_check == 1))
		{
			// Error Check ...

		}
		return 1;
	} 

	// ...
	{
		int alarm_id = ALID__OFFLINE_ALARM;

		CString err_msg;
		CString r_act;

		err_msg  = "1. Check the ethernet-cable.\n";
		err_msg += "2. Check the aligner power";

		p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,err_msg,r_act);

		if(r_act.CompareNoCase(ACT__ABORT) == 0)		return -1;
		if(r_act.CompareNoCase(ACT__RETRY) == 0)		return  0;
	}

    return -1;
}
