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

		ch_data = sCH__PARA_SET_P2->Get__STRING();
		sCH__MON_SET_P2->Set__DATA(ch_data);
	}
	else
	{
		flag = doCH__POWER_MODE->Set__DATA(STR__OFF);

		aCH__PARA_SET_POWER->Set__DATA("0.0");
		aoCH__POWER_SET->Set__DATA("0.0");

		sCH__PARA_SET_P2->Set__DATA("0.0");
		sCH__MON_SET_P2->Set__DATA("0.0");
	}
	return flag;
}
int  CObj__RFG_SERIAL
::Call__POWER_ON(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return doCH__POWER_MODE->Set__DATA(STR__ON);
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

int  CObj__RFG_SERIAL
::Call__TEST_READ_STRING(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;
	CString log_bff;
	CString str_hexa;

	unsigned int k_limit = 2000;
	unsigned int k;

	for(k=0; k <= k_limit; k++)
	{
		byte data_0 = 0x0ff & k;
		byte data_1 = 0x0ff & (k >> 8);

		_DATA__2BYTE_UINT data_pwr;

		data_pwr._hexa = 0;
		data_pwr._byte[0] = 0x0ff & data_0;
		data_pwr._byte[1] = 0x0ff & data_1;

		str_hexa.Format("%02X %02X", data_0,data_1);

		log_bff.Format(" %04d)  %04d (%02X %02X) (%s) \n",
						k, 
						data_pwr._hexa,
						data_pwr._byte[0],
						data_pwr._byte[1],
						str_hexa);
		log_msg += log_bff;
	}

	printf("===========================================\n");
	printf(" Test.Read_String() ... \n");
	printf(log_msg);
	printf("===========================================\n");

	return 1;
}

