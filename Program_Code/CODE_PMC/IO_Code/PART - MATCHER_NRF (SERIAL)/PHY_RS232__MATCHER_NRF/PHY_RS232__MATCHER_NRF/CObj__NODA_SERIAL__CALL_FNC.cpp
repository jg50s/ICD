#include "StdAfx.h"
#include "CObj__NODA_SERIAL.h"


// ...
int CObj__NODA_SERIAL
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		dCH__PARA_MODE_SET->Set__DATA(STR__AUTO);
		dCH__PARA_PRESET_SET->Set__DATA(STR__INTERNAL);

		doCH__STATUS_SET->Set__DATA(STR__ON);
	}

	return Fnc__PRESET_SET(p_variable, p_alarm);
}

int CObj__NODA_SERIAL
::Call__MODE_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool mode_set)
{
	int flag = Fnc__PRESET_SET(p_variable, p_alarm);
	if(flag < 0)		return flag;

	// AUTO MODE SET ...
	if(mode_set)
	{
		dCH__PARA_MODE_SET->Set__DATA(STR__AUTO);
		dCH__PARA_PRESET_SET->Set__DATA(STR__INTERNAL);
	}
	// MANUAL MODE SET ...
	else
	{
		dCH__PARA_MODE_SET->Set__DATA(STR__MANUAL);
		dCH__PARA_PRESET_SET->Set__DATA(STR__INTERNAL);
	}

	return doCH__STATUS_SET->Set__DATA(STR__ON);
}

// ...
int  CObj__NODA_SERIAL
::Call__TEST_DRV(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CDS_IO__CHANNEL_INFO io_info;

	/*
	// do.CH ...
	{
		CString var_name = doCH__STATUS_SET->Get__VARIABLE_NAME();
		CString set_data = doCH__STATUS_SET->Get__STRING();

		__Write__DIGITAL(var_name, io_info, set_data, 0);

		var_name = doCH__MOTOR_RESET->Get__VARIABLE_NAME();
		set_data = doCH__MOTOR_RESET->Get__STRING();

		__Write__DIGITAL(var_name, io_info, set_data, 0);
	}

	// ao.CH ...
	{
		CString var_name = aoCH__TUNE_PRESET->Get__VARIABLE_NAME();
		double set_data  = aoCH__TUNE_PRESET->Get__VALUE();

		__Write__ANALOG(var_name, io_info, set_data);

		var_name = aoCH__LOAD_MANUAL->Get__VARIABLE_NAME();
		set_data  = aoCH__LOAD_MANUAL->Get__VALUE();

		__Write__ANALOG(var_name, io_info, set_data);
	}
	*/

	return 1;
}
