#include "StdAfx.h"
#include "CObj__ZEFA_SERIAL.h"


// ...
int CObj__ZEFA_SERIAL
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(iActive__SIM_MODE > 0)
	{
		sCH__CUR_REMOTE_STATE->Set__DATA(STR__REMOTE);

		sCH__CUR_VOLT_SET_CH1->Set__DATA("0");
		sCH__CUR_VOLT_SET_CH2->Set__DATA("0");
		return 1;
	}

	// ...
	CString ch_data;

	// VERSION ...
	{
		siCH__ALL_VERSION_INFO->Get__STRING();
	}

	// CTRL.REMOTE ...
	{
		if(doCH__REMOTE_SET->Set__DATA(STR__ON)  < 0)				return -11;
		if(doCH__ERROR_CLEAR->Set__DATA(STR__ON) < 0)				return -12;
	}

	// VOLT.SET ...
	{
		if(doCH__ALL_VOLT_SET->Set__DATA(STR__OFF) < 0)				return -21;

		siCH__CFG_VOLT_ALL->Get__STRING();
	}

	// CURRENT.LIMIT ...
	{
		aCH__CFG_CURRENR_LIMIT_CH1->Get__DATA(ch_data);
		sCH__INFO_CFG_CURR_LIMIT_CH1->Set__DATA(ch_data);

		aCH__CFG_CURRENR_LIMIT_CH2->Get__DATA(ch_data);
		sCH__INFO_CFG_CURR_LIMIT_CH2->Set__DATA(ch_data);

		if(soCH__CURRENT_LIMIT_SET->Set__DATA(STR__SET) < 0)		return -31;

		siCH__CFG_CURR_LIMIT_ALL->Get__STRING();
	}

	// RAMP.SEC ...
	{
		aCH__CFG_RAMP_UP_SEC->Get__DATA(ch_data);
		if(soCH__RAMP_UP_SET->Set__DATA(ch_data) < 0)				return -41;

		siCH__CFG_RAMP_UP->Get__STRING();

		//
		aCH__CFG_RAMP_DOWN_SEC->Get__DATA(ch_data);
		if(soCH__RAMP_DOWN_SET->Set__DATA(ch_data) < 0)				return -42;

		siCH__CFG_RAMP_DOWN->Get__STRING();
	}

	// AUTO.TOGGLE ...
	{
		ch_data = dCH__CFG_AUTO_TOGGLE_USE->Get__STRING();
		if(ch_data.CompareNoCase(STR__YES) == 0)
		{
			if(doCH__TOGGLE_SET->Set__DATA(STR__ON) < 0)			return -51;
		}
		else
		{
			if(doCH__TOGGLE_SET->Set__DATA(STR__OFF) < 0)			return -52;
		}

		//
		aCH__CFG_AUTO_TOGGLE_COUNT->Get__DATA(ch_data);
		if(soCH__AUTO_TOGGLE_CNT_SET->Set__DATA(ch_data) < 0)		return -53;

		aCH__CFG_AUTO_TOGGLE_VOLTAGE->Get__DATA(ch_data);
		if(soCH__AUTO_TOGGLE_VOLT_SET->Set__DATA(ch_data) < 0)		return -54;

		//
		siCH__AUTO_TOGGLE_INFO->Get__STRING();
	}

	return 1;
}

int  CObj__ZEFA_SERIAL
::Call__REMOTE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return doCH__REMOTE_SET->Set__DATA(STR__ON);
}
int  CObj__ZEFA_SERIAL
::Call__LOCAL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return doCH__REMOTE_SET->Set__DATA(STR__OFF);
}

int CObj__ZEFA_SERIAL
::Call__RESET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return doCH__SYSTEM_RESET->Set__DATA(STR__ON);
}
int CObj__ZEFA_SERIAL
::Call__ALARM_CLEAR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return doCH__ERROR_CLEAR->Set__DATA(STR__ON);
}

int  CObj__ZEFA_SERIAL
::Call__ON(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	aCH__PARA_VOLT_SET_CH1->Get__DATA(ch_data);
	sCH__CUR_VOLT_SET_CH1->Set__DATA(ch_data);

	aCH__PARA_VOLT_SET_CH2->Get__DATA(ch_data);
	sCH__CUR_VOLT_SET_CH2->Set__DATA(ch_data);

	return doCH__ALL_VOLT_SET->Set__DATA(STR__ON);
}
int  CObj__ZEFA_SERIAL
::Call__OFF(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	sCH__CUR_VOLT_SET_CH1->Set__DATA("0");
	sCH__CUR_VOLT_SET_CH2->Set__DATA("0");

	return doCH__ALL_VOLT_SET->Set__DATA(STR__OFF);
}

int  CObj__ZEFA_SERIAL
::Call__TOGGLE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_on)
{
	if(active_on)
	{
		return doCH__TOGGLE_SET->Set__DATA(STR__ON);
	}

	return doCH__TOGGLE_SET->Set__DATA(STR__OFF);
}

// ...
int  CObj__ZEFA_SERIAL
::Call__CURRENT_LIMIT_SET(CII_OBJECT__VARIABLE*	p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	aCH__PARA_CURRENT_LIMIT_CH1->Get__DATA(ch_data);
	sCH__CUR_CURRENT_LIMIT_CH1->Set__DATA(ch_data);

	aCH__PARA_CURRENT_LIMIT_CH2->Get__DATA(ch_data);
	sCH__CUR_CURRENT_LIMIT_CH2->Set__DATA(ch_data);

	return soCH__CURRENT_LIMIT_SET->Set__DATA(STR__SET);
}

int  CObj__ZEFA_SERIAL
::Call__RAMP_UP_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	aCH__PARA_RAMP_UP_SEC->Get__DATA(ch_data);
	return soCH__RAMP_UP_SET->Set__DATA(ch_data);
}
int  CObj__ZEFA_SERIAL
::Call__RAMP_DOWN_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM*	p_alarm)
{
	CString ch_data;

	aCH__PARA_RAMP_DOWN_SEC->Get__DATA(ch_data);
	return soCH__RAMP_DOWN_SET->Set__DATA(ch_data);
}
