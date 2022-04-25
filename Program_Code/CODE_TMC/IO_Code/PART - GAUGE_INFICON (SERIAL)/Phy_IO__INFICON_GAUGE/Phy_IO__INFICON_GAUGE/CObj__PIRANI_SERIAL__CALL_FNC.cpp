#include "StdAfx.h"
#include "CObj__PIRANI_SERIAL.h"


// ...
int  CObj__PIRANI_SERIAL::
Call__INIT(CII_OBJECT__VARIABLE* p_variable,
		   CII_OBJECT__ALARM* p_alarm)
{
	int cur__retry_count = 0;

	while(1)
	{
		CString ch_data = dCH__CFG_PRESSURE_TYPE->Get__STRING();
		doCH__PRESSURE_TYPE->Set__DATA(ch_data);

		siCH__PRESSURE_TYPE->Get__STRING();

		ch_data = sCH__MON_PRESSURE_TYPE->Get__STRING();
		if(dCH__CFG_PRESSURE_TYPE->Check__DATA(ch_data) > 0)
		{
				 if(ch_data.CompareNoCase(STR__mbar) == 0)			iSTATE__PRESSURE_TYPE = _PRESSURE_TYPE__MBAR;
			else if(ch_data.CompareNoCase(STR__torr) == 0)			iSTATE__PRESSURE_TYPE = _PRESSURE_TYPE__TORR;
			else													iSTATE__PRESSURE_TYPE = _PRESSURE_TYPE__ERROR;

			return 1;
		}
		
		cur__retry_count++;
		if(cur__retry_count > 3)
		{
			return -1;
		}

		Sleep(500);
	}
	return 1;
}

int  CObj__PIRANI_SERIAL::
Call__TEST(CII_OBJECT__VARIABLE* p_variable,
		   CII_OBJECT__ALARM* p_alarm)
{
	CDS_IO__CHANNEL_INFO io_info;
	CString read_data;
	int item_index;

	CString var_name = diCH__PRESSURE_GET->Get__VARIABLE_NAME();
	
	__Read__DIGITAL(var_name,io_info, read_data,item_index);


	/*
	CString r_data = "@253ACK8.31E+2";

	int s_index = r_data.Find("ACK");
	if(s_index == 4)
	{
		r_data.Delete(0,7);

		sCH__DATA_PRESSURE_TORR->Set__DATA(r_data);
	}
	else
	{
		sCH__DATA_PRESSURE_TORR->Set__DATA("???");
	}
	*/

	return 1;
}

