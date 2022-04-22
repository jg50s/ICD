#include "StdAfx.h"
#include "CObj__PIRANI_SERIAL.h"


// ...
int  CObj__PIRANI_SERIAL::
Call__INIT(CII_OBJECT__VARIABLE* p_variable,
		   CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	ch_data = dCH__CFG_PRESSURE_TYPE->Get__STRING();
	doCH__PRESSURE_TYPE->Set__DATA(ch_data);

	ch_data = siCH__PRESSURE_TYPE->Get__STRING();

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "Init Result ... \n";

		log_bff.Format(" * %s <- %s \n",
						doCH__PRESSURE_TYPE->Get__CHANNEL_NAME(),
						doCH__PRESSURE_TYPE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n",
						sCH__MON_PRESSURE_TYPE->Get__CHANNEL_NAME(),
						sCH__MON_PRESSURE_TYPE->Get__STRING());
		log_msg += log_bff;

		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
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

