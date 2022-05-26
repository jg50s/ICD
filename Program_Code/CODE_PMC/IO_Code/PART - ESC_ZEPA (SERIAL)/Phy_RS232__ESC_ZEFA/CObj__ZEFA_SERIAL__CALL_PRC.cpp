#include "StdAfx.h"
#include "CObj__ZEFA_SERIAL.h"

#include "CCommon_DEF.h"


// ...
int CObj__ZEFA_SERIAL
::Call__PROC_READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(sCH__CUR_REMOTE_STATE->Check__DATA(STR__REMOTE) < 0)
	{
		if(doCH__REMOTE_SET->Set__DATA(STR__ON) < 0)		return -11;
	}

	doCH__TOGGLE_SET->Set__DATA(STR__OFF);
	return 1;
}

int CObj__ZEFA_SERIAL
::Call__PROC_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(iActive__SIM_MODE > 0)
	{
		CString ch_data;

		sCH__CUR_REMOTE_STATE->Set__DATA(STR__REMOTE);

		//
		aCH__PARA_RAMP_UP_SEC->Get__DATA(ch_data);
		sCH__INFO_CFG_RAMP_UP_SEC->Set__DATA(ch_data);

		aCH__PARA_RAMP_DOWN_SEC->Get__DATA(ch_data);
		sCH__INFO_CFG_RAMP_DOWN_SEC->Set__DATA(ch_data);

		//
		aCH__PARA_VOLT_SET_CH1->Get__DATA(ch_data);
		aCH__CUR_VOLT_SET_CH1->Set__DATA(ch_data);

		aCH__PARA_VOLT_SET_CH2->Get__DATA(ch_data);
		aCH__CUR_VOLT_SET_CH2->Set__DATA(ch_data);

		return 1;
	}

	// ...
	CString ch_data;

	// RAMP.SET ..
	{
		aCH__PARA_RAMP_UP_SEC->Get__DATA(ch_data);
		soCH__RAMP_UP_SET->Set__DATA(ch_data);

		aCH__PARA_RAMP_DOWN_SEC->Get__DATA(ch_data);
		soCH__RAMP_DOWN_SET->Set__DATA(ch_data);
	}

	// VOLT.SET ...
	{
		aCH__RCP_VOLT_SET_CH1->Get__DATA(ch_data);
		aCH__CUR_VOLT_SET_CH1->Set__DATA(ch_data);

		aCH__RCP_VOLT_SET_CH2->Get__DATA(ch_data);
		aCH__CUR_VOLT_SET_CH2->Set__DATA(ch_data);

		if(doCH__ALL_VOLT_SET->Set__DATA(STR__ON) < 0)			return -11;
	}

	return 1;
}

void  CObj__ZEFA_SERIAL
::Fnc__Do_Abort(CII_OBJECT__ALARM* p_alarm)
{
	doCH__ALL_VOLT_SET->Set__DATA(STR__OFF);
}

