#include "StdAfx.h"
#include "CObj__NODA_SERIAL.h"
#include "CObj__NODA_SERIAL__DEF.h"


//------------------------------------------------------------------------------------
int CObj__NODA_SERIAL
::__Read__ANALOG(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__NODA_SERIAL
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{

	return -1;
}

int CObj__NODA_SERIAL
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	unsigned char r_data[MAX_CHAR] = {0,};
	CString ch_data;

	byte addr_id = iUNIT__ADDR_ID;

	// ...
	bool active__mat_state		   = false;
	bool active__load_preset	   = false;
	bool active__tune_preset	   = false;
	bool active__cur_load_position = false;
	bool active__cur_tune_position = false;
	bool active__vpp_value		   = false;
	bool active__vdc_value		   = false;
	bool active__irms_value        = false;
	bool active__pos_value         = false;

		 if(siCH__MAT_STATE->Check__VARIABLE_NAME(var_name) > 0)				active__mat_state		  = true;
	else if(siCH__LOAD_PRESET->Check__VARIABLE_NAME(var_name) > 0)				active__load_preset		  = true;
	else if(siCH__TUNE_PRESET->Check__VARIABLE_NAME(var_name)  > 0)				active__tune_preset		  = true;	
	else if(siCH__CUR_LOAD_POSITION->Check__VARIABLE_NAME(var_name)  > 0)		active__cur_load_position = true;
	else if(siCH__CUR_TUNE_POSITION->Check__VARIABLE_NAME(var_name)  > 0)		active__cur_tune_position = true;
	else if(siCH__VPP_VALUE->Check__VARIABLE_NAME(var_name) > 0)				active__vpp_value		  = true;
	else if(siCH__VDD_VALUE->Check__VARIABLE_NAME(var_name) > 0)				active__vdc_value         = true;
	else if(siCH__IRMS_VALUE->Check__VARIABLE_NAME(var_name) > 0)				active__irms_value        = true;
	else if(siCH__POS_VALUE->Check__VARIABLE_NAME(var_name) > 0)				active__pos_value         = true;

	if((active__mat_state)
	|| (active__load_preset)
	|| (active__tune_preset)
	|| (active__cur_load_position)
	|| (active__cur_tune_position)
	|| (active__vpp_value)
	|| (active__vdc_value)
	|| (active__irms_value)
	|| (active__pos_value))
	{
		byte cmmd_id;

			 if	(active__mat_state)				cmmd_id = _MAT_CMD__SI_MAT_STATE;
		else if	(active__load_preset)			cmmd_id = _MAT_CMD__SI_LOAD_PRESET;
		else if	(active__tune_preset)			cmmd_id = _MAT_CMD__SI_TUNE_PRESET;
		else if	(active__cur_load_position)		cmmd_id = _MAT_CMD__SI_CUR_LOAD_POSITION;
		else if	(active__cur_tune_position)		cmmd_id = _MAT_CMD__SI_CUR_TUNE_POSITION;
		else if	(active__vpp_value)				cmmd_id = _MAT_CMD__SI_VPP_VALUE;
		else if	(active__vdc_value)				cmmd_id = _MAT_CMD__SI_VDC_VALUE;
		else if	(active__irms_value)			cmmd_id = _MAT_CMD__SI_IRMS_VALUE;
		else if	(active__pos_value)				cmmd_id = _MAT_CMD__SI_POS_VALUE;
		else									return -1;

		int r_len = _Recv__Command(addr_id, cmmd_id, r_data);	

		if(r_len > 0)
		{
			byte data_0;
			byte data_1;

			_DATA__2BYTE_INT data_pwr;
			data_pwr._hexa = 0;
			
			data_0 = r_data[4];
			data_1 = r_data[5];

			// MAT_STS Input ...
			if(active__mat_state)
			{
				_Update__MAT_State(data_0, data_1);
				read_data.Format("%02X %02X", data_0, data_1);
			}

			// 2 Byte Input ...
			else if((active__load_preset)
				 || (active__tune_preset)
				 || (active__cur_load_position)
				 || (active__cur_tune_position)
				 || (active__vpp_value)
				 || (active__vdc_value)
				 || (active__irms_value)
				 || (active__pos_value))
			{			
				data_pwr._byte[0] = data_0;
				data_pwr._byte[1] = data_1;

				if(active__load_preset)
				{
					double pwr_value = data_pwr._hexa * 0.1;
					ch_data.Format("%.1f", pwr_value);
					sCH__INFO_LOAD_PRESET->Set__DATA(ch_data);
				}
				else if(active__tune_preset)
				{
					double pwr_value = data_pwr._hexa * 0.1;
					ch_data.Format("%.1f", pwr_value);
					sCH__INFO_TUNE_PRESET->Set__DATA(ch_data);
				}
				else if(active__cur_load_position)
				{
					double pwr_value = data_pwr._hexa * 0.1;
					ch_data.Format("%.1f", pwr_value);
					sCH__INFO_CUR_LOAD_POSITION->Set__DATA(ch_data);
				}
				else if(active__cur_tune_position)
				{
					double pwr_value = data_pwr._hexa * 0.1;
					ch_data.Format("%.1f", pwr_value);
					sCH__INFO_CUR_TUNE_POSITION->Set__DATA(ch_data);
				}
				else if(active__vpp_value)
				{
					int vpp_value = data_pwr._hexa;
					ch_data.Format("%1d", vpp_value);
					sCH__INFO_VPP_VALUE->Set__DATA(ch_data);
				}
				else if(active__vdc_value)
				{
					int vdc_sign = data_1 & 0x80;
					int vdc_value = data_pwr._hexa;

					if(vdc_sign != 0x00)
					{
						if(vdc_value > 0)			vdc_value = -vdc_value;
					}

					ch_data.Format("%1d", vdc_value);
					sCH__INFO_VDC_VALUE->Set__DATA(ch_data);					
				}
				else if(active__irms_value)
				{
					ch_data.Format("%1d", data_0);
					sCH__INFO_IRMS_VALUE->Set__DATA(ch_data);					
				}
				else if(active__pos_value)
				{
					int pos_value = data_pwr._hexa;
					ch_data.Format("%1d", pos_value);
					sCH__INFO_POS_VALUE->Set__DATA(ch_data);					
				}

				read_data.Format("%02X %02X", data_0, data_1);
			}
			else
			{
				read_data = "ERROR";
			}
			return 1;
		}
		
		read_data = "ERROR.?";
		return 1;
	}

	return -1;
}

//------------------------------------------------------------------------------------
int CObj__NODA_SERIAL
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

	if(aoCH__LOAD_PRESET->Check__VARIABLE_NAME(var_name) > 0)
	{
		byte cmmd_id = 0x00;
		byte data_00 = 0x00;
		byte data_01 = 0x00;

	 	cmmd_id = _MAT_CMD__AO_SET_LOAD_PRESET;

		//
		int set_hexa = (int) (set_data * 10);
		
		_DATA__2BYTE_INT data_pwr;
		data_pwr._hexa = 0;

		data_pwr._hexa = (int) set_hexa;
		data_00 = data_pwr._byte[0];
		data_01 = data_pwr._byte[1];

		int r_flag = _Send__Command(addr_id,cmmd_id,data_00,data_01);
		if(r_flag > 0)
		{
			ch_data.Format("%.1f", set_data);
			sCH__MON_LOAD_POS_SET->Set__DATA(ch_data);
		}
		return r_flag;
	}

	if(aoCH__TUNE_PRESET->Check__VARIABLE_NAME(var_name) > 0)
	{
		byte cmmd_id = 0x00;
		byte data_00 = 0x00;
		byte data_01 = 0x00;

		cmmd_id = _MAT_CMD__AO_SET_TUNE_PRESET;

		//
		int set_hexa = (int) (set_data * 10);

		_DATA__2BYTE_INT data_pwr;
		data_pwr._hexa = 0;

		data_pwr._hexa = (int) set_hexa;
		data_00 = data_pwr._byte[0];
		data_01 = data_pwr._byte[1];

		int r_flag = _Send__Command(addr_id,cmmd_id,data_00,data_01);		
		if(r_flag > 0)
		{
			ch_data.Format("%.1f", set_data);
			sCH__MON_TUNE_POS_SET->Set__DATA(ch_data);
		}
		return r_flag;
	}

	return -1;
}

int CObj__NODA_SERIAL
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
	CString log_msg;
	CString log_buffer;

	byte addr_id = iUNIT__ADDR_ID;


	if(doCH__STATUS_SET->Check__VARIABLE_NAME(var_name)  > 0)
	{
		byte cmmd_id = _MAT_CMD__DO_SET_STATUS;
		byte data_00 = 0x00;
		byte data_01 = 0x00;

		// MATCHING MODE ...
		{
			if(dCH__PARA_MODE_SET->Check__DATA(STR__AUTO) > 0)			data_00 += 0x00;
			else														data_00 += 0x08;
		}
		// PRESET MODE ...
		{
			CString str_preset = dCH__PARA_PRESET_SET->Get__STRING();

				 if(str_preset.CompareNoCase(STR__INTERNAL) == 0)		data_00 += 0x00;
			else if(str_preset.CompareNoCase(STR__EXTERNAL) == 0)		data_00 += 0x10;
			else														data_00 += 0x20;
		}

		// ...
		// int r_flag = _Send__Command(addr_id,cmmd_id, data_00,data_01);
		int r_flag = _Send__Command(addr_id,cmmd_id, data_01,data_00);

		if(r_flag > 0)
		{
			ch_data = dCH__PARA_MODE_SET->Get__STRING();
			sCH__MON_CONTROL_SET->Set__DATA(ch_data);

			ch_data = dCH__PARA_PRESET_SET->Get__STRING();
			sCH__MON_PRESET_SET->Set__DATA(ch_data);
		}
		return r_flag;
	}

	return -1;
}

int CObj__NODA_SERIAL
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}

