#include "StdAfx.h"
#include "CObj__RFG_SERIAL.h"
#include "CObj__RFG_SERIAL__DEF.h"


//------------------------------------------------------------------------------------
int CObj__RFG_SERIAL
::__Read__ANALOG(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__RFG_SERIAL
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{

	return -1;
}

int CObj__RFG_SERIAL
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	unsigned char r_data[MAX_CHAR] = {0,};
	CString ch_data;

	byte addr_id = iUNIT__ADDR_ID;

	// ...
	bool active__rf_state = false;
	bool active__pwr_setpoint = false;
	bool active__pwr_forward  = false;
	bool active__pwr_reflect   = false;
	
		 if(siCH__RF_STATE->Check__VARIABLE_NAME(var_name) > 0)				active__rf_state     = true;
	else if(siCH__POWER_SERPOINT->Check__VARIABLE_NAME(var_name) > 0)		active__pwr_setpoint = true;
	else if(siCH__POWER_FORWARD->Check__VARIABLE_NAME(var_name)  > 0)		active__pwr_forward  = true;	
	else if(siCH__POWER_REFLECT->Check__VARIABLE_NAME(var_name)  > 0)		active__pwr_reflect  = true;

	if((active__rf_state)
	|| (active__pwr_setpoint)
	|| (active__pwr_forward)
	|| (active__pwr_reflect))
	{
		byte cmmd_id;

			 if(active__rf_state)			cmmd_id = _RFG_CMD__SI_RF_STATE;
		else if(active__pwr_setpoint)		cmmd_id = _RFG_CMD__SI_PWR_SETPOINT;
		else if(active__pwr_forward)		cmmd_id = _RFG_CMD__SI_PWR_FORWARD;
		else if(active__pwr_reflect)		cmmd_id = _RFG_CMD__SI_PWR_REFLECT;
		else								return -1;

		int r_len = _Recv__Command(addr_id,cmmd_id, r_data);		
		if(r_len > 0)
		{
			byte data_0 = r_data[4];
			byte data_1 = r_data[5];

			if(active__rf_state)
			{
				_Update__RF_State(data_0, data_1);
			}
			else
			{
				_DATA__2BYTE_UINT data_pwr;
				data_pwr._byte[0] = data_0;
				data_pwr._byte[1] = data_1;

				double pwr_value = (data_pwr._hexa / (double) iHEXA__PWR_MAX) * dVALUE__PWR_MAX;

				if(active__pwr_setpoint)		
				{				
					ch_data.Format("%.0f", pwr_value);
					sCH__INFO_POWER_SETPOINT->Set__DATA(ch_data);
				}
				else if(active__pwr_forward)		
				{
					ch_data.Format("%.0f", pwr_value);
					sCH__INFO_FORWARD_POWER->Set__DATA(ch_data);
				}
				else if(active__pwr_reflect)		
				{
					ch_data.Format("%.0f", pwr_value);
					sCH__INFO_REFLECT_POWER->Set__DATA(ch_data);
				}
			}

			read_data.Format("%02X %02X", data_0,data_1);
			return 1;
		}
		
		read_data = STR__ERROR;
		return -1;
	}

	return -1;
}

//------------------------------------------------------------------------------------
int CObj__RFG_SERIAL
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	// Log ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "_Write__ANALOG() \n";

		log_bff.Format(" * var_name <- %s \n", var_name);
		log_msg += log_bff;

		log_bff.Format(" * set_data <- %.3f \n", set_data);
		log_msg += log_bff;

		Write__DRV_LOG(log_msg);
	}

	// ...
	unsigned char r_data[MAX_CHAR] = {0,};
	CString ch_data;
	
	byte addr_id = iUNIT__ADDR_ID;

	if(aoCH__POWER_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		byte cmmd_id = _RFG_CMD__AO_POWER_SET;
		byte data_00 = 0x00;
		byte data_01 = 0x00;
	
		int set_hexa = (int) ((set_data / dVALUE__PWR_MAX) * iHEXA__PWR_MAX);
		
		_DATA__2BYTE_UINT data_pwr;
		data_pwr._hexa = (int) set_hexa;
		data_00 = data_pwr._byte[0];
		data_01 = data_pwr._byte[1];

		return _Recv__Command(addr_id,cmmd_id,data_00,data_01);		
	}

	return -1;
}

int CObj__RFG_SERIAL
::__Write__DIGITAL(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	// Log ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "_Write__DIGITAL() \n";

		log_bff.Format(" * var_name <- %s \n", var_name);
		log_msg += log_bff;

		log_bff.Format(" * set_data (%1d) <- %s \n", item_index, set_data);
		log_msg += log_bff;

		Write__DRV_LOG(log_msg);
	}

	// ...
	unsigned char r_data[MAX_CHAR] = {0,};
	CString ch_data;

	byte addr_id = iUNIT__ADDR_ID;


	if((doCH__POWER_MODE->Check__VARIABLE_NAME(var_name)  > 0)
	|| (doCH__ALARM_RESET->Check__VARIABLE_NAME(var_name) > 0))
	{
		byte cmmd_id = _RFG_CMD__DO_OUTPUT_MODE;
		byte data_00 = 0x00;
		byte data_01 = 0x00;

		if(dCH__CFG_RF_MODE->Check__DATA(STR__PULSE) > 0)				data_00 = 0x04;
		else															data_00 = 0x00;

		if(doCH__POWER_MODE->Check__VARIABLE_NAME(var_name) > 0)
		{
				 if(set_data.CompareNoCase(STR__ON)  == 0)				data_00 += 0x02;
			else if(set_data.CompareNoCase(STR__OFF) == 0)				data_00 += 0x00;
			else														return -1;
		}
		else if(doCH__ALARM_RESET->Check__VARIABLE_NAME(var_name) > 0)
		{
			if(set_data.CompareNoCase(STR__ON) == 0)					data_00 += 0x08;
			else														return 1;
		}
		else
		{
			return -11;
		}

		return _Recv__Command(addr_id,cmmd_id,data_00,data_01);		
	}

	return -1;
}

int CObj__RFG_SERIAL
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}

