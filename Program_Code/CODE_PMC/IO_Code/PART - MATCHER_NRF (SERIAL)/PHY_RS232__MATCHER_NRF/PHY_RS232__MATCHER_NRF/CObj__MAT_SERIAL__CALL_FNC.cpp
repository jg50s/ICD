#include "StdAfx.h"
#include "CObj__MAT_SERIAL.h"


// ...
int CObj__MAT_SERIAL
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	doCH__MOTOR_RESET->Set__DATA(STR__ON);
	dCH__CFG_MODE_SET->Set__DATA(STR__AUTO);

	doCH__STATUS_SET->Set__DATA(STR__ON);
	return Fnc__PRESET_SET(p_variable, p_alarm);
}

int CObj__MAT_SERIAL
::Call__MODE_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool mode_set)
{
	CString log_msg;
	CString log_bff;	

	int flag;

	// AUTO MODE SET ...
	if(mode_set)
	{
		flag = Fnc__PRESET_SET(p_variable, p_alarm);
		if(flag < 0)
		{
			return flag;
		}

		dCH__CFG_MODE_SET->Set__DATA(STR__AUTO);
	}
	// MANUAL MODE SET ...
	else
	{
		flag = Fnc__MANUAL_SET(p_variable, p_alarm);
		if(flag < 0)
		{
			return flag;
		}
		dCH__CFG_MODE_SET->Set__DATA(STR__MANUAL);
	}

	return doCH__STATUS_SET->Set__DATA(STR__ON);
}

// ...
int  CObj__MAT_SERIAL
::Call__TEST_DRV(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CDS_IO__CHANNEL_INFO io_info;

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

	return 1;
}
