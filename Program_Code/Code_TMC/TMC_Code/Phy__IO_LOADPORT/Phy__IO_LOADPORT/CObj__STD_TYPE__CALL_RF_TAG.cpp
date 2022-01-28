#include "StdAfx.h"
#include "CObj__STD_TYPE.h"
#include "CObj__STD_TYPE__DEF.h"


// ...
int  CObj__STD_TYPE
::Call__CID_READ(CII_OBJECT__VARIABLE* p_variable,
				 CII_OBJECT__ALARM* p_alarm)
{
	if(Check__CFG_CID_TAG_SENSOR(p_variable, p_alarm) < 0)
	{
		return -11;
	}
	if(pLPx__OBJ_CTRL->Call__OBJECT("CID_READ") < 0)
	{
		return -1;
	}

	// ...
	{
		CString str_cid = sEXT_CH__LPx__RSP_PAGE_CID->Get__STRING();
	
		str_cid.TrimRight();
		sCH__CID_STRING->Set__DATA(str_cid);
	}
	return 1;
}
int  CObj__STD_TYPE
::Call__PAGE_READ(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	if(Check__CFG_CID_TAG_SENSOR(p_variable, p_alarm) < 0)
	{
		return -11;
	}
	if(pLPx__OBJ_CTRL->Call__OBJECT("PAGE_READ") < 0)
	{
		return -1;
	}

	return 1;
}

int  CObj__STD_TYPE
::Call__CID_WRITE(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	if(Check__CFG_CID_TAG_SENSOR(p_variable, p_alarm) < 0)
	{
		return -11;
	}
	if(pLPx__OBJ_CTRL->Call__OBJECT("CID_WRITE") < 0)
	{
		return -1;
	}

	return 1;
}
int  CObj__STD_TYPE
::Call__PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm)
{
	if(Check__CFG_CID_TAG_SENSOR(p_variable, p_alarm) < 0)
	{
		return -11;
	}
	if(pLPx__OBJ_CTRL->Call__OBJECT("PAGE_WRITE") < 0)
	{
		return -1;
	}

	return 1;
}

// ...
int  CObj__STD_TYPE
::Check__CFG_CID_TAG_SENSOR(CII_OBJECT__VARIABLE* p_variable, 
							CII_OBJECT__ALARM* p_alarm)
{
LOOP_RETRY:

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -1;
	}

	if(dCH__CFG_CID_TAG_SENSOR_USE->Check__DATA(STR__YES) < 0)
	{
		int alm_id = ALID__LP_WITH_NO_RF_TAG_SENSOR;
		CString alm_msg;
		CString r_act;

		alm_msg.Format(" * %s <- %s \n",
			dCH__CFG_CID_TAG_SENSOR_USE->Get__CHANNEL_NAME(),
			dCH__CFG_CID_TAG_SENSOR_USE->Get__STRING());

		p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);
		if(r_act.CompareNoCase(ACT__RETRY) == 0)		
		{
			goto LOOP_RETRY;
		}
		return -11;
	}

	return 1;
}
