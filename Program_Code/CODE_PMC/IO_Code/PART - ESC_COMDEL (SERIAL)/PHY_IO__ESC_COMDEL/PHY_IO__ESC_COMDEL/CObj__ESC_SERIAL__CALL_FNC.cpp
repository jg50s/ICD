#include "StdAfx.h"
#include "CObj__ESC_SERIAL.h"


//-------------------------------------------------------------------------	
int  CObj__ESC_SERIAL::
Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		doCH__CONTROL_MODE->Set__DATA(STR__REMOTE);
		doCH__ECHO_MODE->Set__DATA(STR__ON);

		doCH__VOLTAGE_POWER->Set__DATA(STR__OFF);
		aoCH__VOLTAGE_SET->Set__VALUE(0.0);
	}

	// ...
	{
		Call__RAMP_UP(p_variable, p_alarm, true);
		Call__RAMP_DOWN(p_variable, p_alarm, true);

		Call__CURRENT_LIMIT_SET(p_variable, p_alarm, true);
	}
	return 1;
}

// ...
int  CObj__ESC_SERIAL::
Call__REMOTE(CII_OBJECT__VARIABLE* 	p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data = STR__REMOTE;

	return doCH__CONTROL_MODE->Set__DATA(ch_data);
}
int  CObj__ESC_SERIAL::
Call__LOCAL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data = STR__LOCAL;

	return doCH__CONTROL_MODE->Set__DATA(ch_data);
}

// ...
int  CObj__ESC_SERIAL::
Call__ON(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data = STR__ON;

	return doCH__VOLTAGE_POWER->Set__DATA(ch_data);
}
int  CObj__ESC_SERIAL::
Call__OFF(CII_OBJECT__VARIABLE*	p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data = STR__OFF;

	return doCH__VOLTAGE_POWER->Set__DATA(ch_data);
}

// ...
int  CObj__ESC_SERIAL::
Call__POSITIVE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM*	p_alarm)
{
	CString ch_data = STR__POSITIVE;

	return doCH__VOLTAGE_MODE->Set__DATA(ch_data);
}
int  CObj__ESC_SERIAL::
Call__NEGATIVE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data = STR__NEGATIVE;

	return doCH__VOLTAGE_MODE->Set__DATA(ch_data);
}

// ...
int  CObj__ESC_SERIAL::
Call__RAMP_UP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active__cfg_set)
{
	CString ch_data;

	if(active__cfg_set)			aCH__CFG_RAMP_UP_TIME->Get__DATA(ch_data);
	else						aCH__PARA_RAMP_UP_TIME->Get__DATA(ch_data);

	return aoCH__RAMP_UP_SET->Set__DATA(ch_data);
}
int  CObj__ESC_SERIAL::
Call__RAMP_DOWN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active__cfg_set)
{
	CString ch_data;

	if(active__cfg_set)			aCH__CFG_RAMP_DN_TIME->Get__DATA(ch_data);
	else						aCH__PARA_RAMP_DN_TIME->Get__DATA(ch_data);

	return aoCH__RAMP_DN_SET->Set__DATA(ch_data);
}

// ...
int  CObj__ESC_SERIAL::
Call__VOLTAGE_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	aCH__PARA_VOLTAGE_SET->Get__DATA(ch_data);

	return aoCH__VOLTAGE_SET->Set__DATA(ch_data);
}

int  CObj__ESC_SERIAL::
Call__CURRENT_LIMIT_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active__cfg_set)
{
	CString ch_data;

	if(active__cfg_set)			aCH__CFG_CURRENT_LIMIT_SET->Get__DATA(ch_data);
	else						aCH__PARA_CURRENT_LIMIT_SET->Get__DATA(ch_data);

	return aoCH__CURRENT_LIMIT_SET->Set__DATA(ch_data);
}


// ...
int  CObj__ESC_SERIAL::
Call__PACKET_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CDS_IO__CHANNEL_INFO io_info;
	CString var_name;

	// AO ...
	{
		double set_data;

		//
		{
			var_name = aoCH__VOLTAGE_SET->Get__VARIABLE_NAME();
			set_data = 1000.0;
			
			__Write__ANALOG(var_name, io_info, set_data);
		}
       
		//
		{
			var_name = aoCH__CURRENT_LIMIT_SET->Get__VARIABLE_NAME();
			set_data = 0.1;

			__Write__ANALOG(var_name, io_info, set_data);
		}

		//
		{
			var_name = aoCH__RAMP_UP_SET->Get__VARIABLE_NAME();
			set_data = 0.5;
		
			__Write__ANALOG(var_name, io_info, set_data);
		}

		//
		{
			var_name = aoCH__RAMP_DN_SET->Get__VARIABLE_NAME();
			set_data = 1.0;

			__Write__ANALOG(var_name, io_info, set_data);
		}
	}

	// SI ...
	{
		CString r_data;

		// 
		{
			var_name = siCH__VOLTAGE_READ->Get__VARIABLE_NAME();

			__Read__STRING(var_name, io_info, r_data);
		}
		// 
		{
			var_name = siCH__CURRENT_READ->Get__VARIABLE_NAME();

			__Read__STRING(var_name, io_info, r_data);
		}
	}

	// DO ...
	{
		CString set_data;
		int item_index;

		//
		{
			var_name = doCH__CONTROL_MODE->Get__VARIABLE_NAME();
			set_data = STR__REMOTE;

			__Write__DIGITAL(var_name, io_info, set_data, item_index);
		}

		// 
		{
			var_name = doCH__ECHO_MODE->Get__VARIABLE_NAME();
			set_data = STR__ON;

			__Write__DIGITAL(var_name, io_info, set_data, item_index);
		}

		//
		{
			var_name = doCH__VOLTAGE_MODE->Get__VARIABLE_NAME();
			set_data = STR__POSITIVE;

			__Write__DIGITAL(var_name, io_info, set_data, item_index);
		}

		// 
		{
			var_name = doCH__VOLTAGE_POWER->Get__VARIABLE_NAME();
			set_data = STR__ON;

			__Write__DIGITAL(var_name, io_info, set_data, item_index);
		}
	}

	return 1;
}
