#include "StdAfx.h"
#include "CObj__RF_IO.h"
#include "CObj__RF_IO__ALID.h"
#include "CObj__RF_IO__DEF.h"


// ...
int CObj__RF_IO
::Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	sCH__OBJ_STATUS->Set__DATA(STR__STANDBY);

	return OBJ_AVAILABLE;
}

int CObj__RF_IO
::Call__OFF(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	// Interlock Check ...
	{

	}

	// ...
	{
		dEXT_CH__DO_SOURCE_ON->Set__DATA(STR__OFF);
		aEXT_CH__AO_SOURCE_POWER->Set__DATA("0.0");
	}

	return OBJ_AVAILABLE;
}
int CObj__RF_IO
::Call__SET_POWER(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

LOOP_RETRY:

	// Interlock Check ...
	{

	}

	// ...
	{
		CString ch_data;
		aCH__PARA_POWER_SET->Get__DATA(ch_data);

		aEXT_CH__AO_SOURCE_POWER->Set__DATA(ch_data);
		dEXT_CH__DO_SOURCE_ON->Set__DATA(STR__ON);
	}

	return OBJ_AVAILABLE;
}
