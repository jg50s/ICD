#include "StdAfx.h"
#include "CObj__RFG_SERIAL.h"


// ...
int CObj__RFG_SERIAL
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	doCH__ALARM_RESET->Set__DATA(STR__ON);

	return Call__POWER_SET(p_variable, p_alarm, false);
}

int  CObj__RFG_SERIAL
::Call__POWER_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_set)
{
	CString ch_data;
	int	flag;

	if(active_set)
	{
		aCH__PARA_SET_POWER->Get__DATA(ch_data);
		aoCH__POWER_SET->Set__DATA(ch_data);

		flag = doCH__POWER_MODE->Set__DATA(STR__ON);
	}
	else
	{
		flag = doCH__POWER_MODE->Set__DATA(STR__OFF);

		aoCH__POWER_SET->Set__DATA("0.0");
	}
	return flag;
}

int  CObj__RFG_SERIAL
::Call__ALARM_RESET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	doCH__POWER_MODE->Set__DATA(STR__OFF);
	
	return doCH__ALARM_RESET->Set__DATA(STR__ON);
}


// ...
int  CObj__RFG_SERIAL
::Call__TEST_DRV(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CDS_IO__CHANNEL_INFO io_info;

	// do.CH ...
	{
		CString var_name = doCH__POWER_MODE->Get__VARIABLE_NAME();
		CString set_data = doCH__POWER_MODE->Get__STRING();

		__Write__DIGITAL(var_name, io_info, set_data, 0);
	}

	// ao.CH ...
	{
		CString var_name = aoCH__POWER_SET->Get__VARIABLE_NAME();
		double set_data  = aoCH__POWER_SET->Get__VALUE();

		__Write__ANALOG(var_name, io_info, set_data);
	}

	return 1;
}
