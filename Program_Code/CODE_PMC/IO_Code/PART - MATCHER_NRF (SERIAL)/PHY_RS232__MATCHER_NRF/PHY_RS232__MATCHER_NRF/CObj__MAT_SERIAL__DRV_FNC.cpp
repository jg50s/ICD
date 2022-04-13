#include "StdAfx.h"
#include "CObj__MAT_SERIAL.h"
#include "CObj__MAT_SERIAL__DEF.h"


//------------------------------------------------------------------------------------
int CObj__MAT_SERIAL
::__Read__ANALOG(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__MAT_SERIAL
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{

	return -1;
}

int CObj__MAT_SERIAL
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	unsigned char r_data[MAX_CHAR] = {0,};
	CString ch_data;

	byte addr_id = iUNIT__ADDR_ID;

	// ...
	bool active__mat_state			= false;
	bool active__load_preset		= false;
	bool active__tune_preset		= false;
	bool active__cur_load_position	= false;
	bool active__cur_tune_position	= false;
	bool active__vpp_value			= false;
	bool active__vrms_lrms			= false;
	bool active__impedance			= false;
	bool active__fwd_pwr			= false;
	bool active__ref_pwr			= false;
	bool active__start_stop_swr		= false;
	bool active__swr				= false;
	bool active__phase_shift		= false;
	
		 if(siCH__MAT_STATE->Check__VARIABLE_NAME(var_name) > 0)				active__mat_state			= true;
	else if(siCH__LOAD_PRESET->Check__VARIABLE_NAME(var_name) > 0)				active__load_preset			= true;
	else if(siCH__TUNE_PRESET->Check__VARIABLE_NAME(var_name)  > 0)				active__tune_preset			= true;	
	else if(siCH__CUR_LOAD_POSITION->Check__VARIABLE_NAME(var_name)  > 0)		active__cur_load_position	= true;
	else if(siCH__CUR_TUNE_POSITION->Check__VARIABLE_NAME(var_name)  > 0)		active__cur_tune_position	= true;
	else if(siCH__VPP_VALUE->Check__VARIABLE_NAME(var_name) > 0)				active__vpp_value			= true;
	else if(siCH__VRMS_AND_LRMS->Check__VARIABLE_NAME(var_name) > 0)			active__vrms_lrms			= true;
	else if(siCH__IMPEDANCE->Check__VARIABLE_NAME(var_name) > 0)				active__impedance			= true;
	else if(siCH__FWD_PWR->Check__VARIABLE_NAME(var_name) > 0)					active__fwd_pwr				= true;
	else if(siCH__REF_PWR->Check__VARIABLE_NAME(var_name) > 0)					active__ref_pwr				= true;
	else if(siCH__START_STOP_SWR->Check__VARIABLE_NAME(var_name) > 0)			active__start_stop_swr		= true;
	else if(siCH__SWR->Check__VARIABLE_NAME(var_name) > 0)						active__swr					= true;
	else if(siCH__PHASE_SHIFT->Check__VARIABLE_NAME(var_name) > 0)				active__phase_shift			= true;


	if((active__mat_state)
	|| (active__load_preset)
	|| (active__tune_preset)
	|| (active__cur_load_position)
	|| (active__cur_tune_position)
	|| (active__vpp_value)
	|| (active__vrms_lrms)
	|| (active__impedance)
	|| (active__fwd_pwr)
	|| (active__ref_pwr)
	|| (active__start_stop_swr)
	|| (active__swr)
	|| (active__phase_shift))
	{
		byte cmmd_id;

			 if	(active__mat_state)				cmmd_id = _MAT_CMD__SI_MAT_STATE;
		else if	(active__load_preset)			cmmd_id = _MAT_CMD__SI_LOAD_PRESET;
		else if	(active__tune_preset)			cmmd_id = _MAT_CMD__SI_TUNE_PRESET;
		else if	(active__cur_load_position)		cmmd_id = _MAT_CMD__SI_CUR_LOAD_POSITION;
		else if	(active__cur_tune_position)		cmmd_id = _MAT_CMD__SI_CUR_TUNE_POSITION;
		else if	(active__vpp_value)				cmmd_id = _MAT_CMD__SI_VPP_VALUE;
		else if	(active__vrms_lrms)				cmmd_id = _MAT_CMD__SI_VRMS_IRMS;
		else if	(active__impedance)				cmmd_id = _MAT_CMD__SI_IMPEDANCE;
		else if	(active__fwd_pwr)				cmmd_id = _MAT_CMD__SI_FORWARD_PWR;
		else if	(active__ref_pwr)				cmmd_id = _MAT_CMD__SI_REF_PWR;
		else if	(active__start_stop_swr)		cmmd_id = _MAT_CMD__SI_START_STOP_SWR;
		else if	(active__swr)					cmmd_id = _MAT_CMD__SI_SWR;
		else if	(active__phase_shift)			cmmd_id = _MAT_CMD__SI_PHASE_SHIFT;
		else									return -1;

		int r_len = _Recv__Command(addr_id, cmmd_id, r_data);	

		if(r_len > 0)
		{
			byte data_0;
			byte data_1;
			byte data_2;

			_DATA__2BYTE_INT data_pwr;
			data_pwr._hexa = 0;
			
			// MAT_STS Input ...
			if(active__mat_state)
			{
				_Update__MAT_State(r_data[4], r_data[5]);
				read_data.Format("%02X %02X", r_data[4],r_data[5]);
			}

			// 2 Byte Input ...
			else if((active__load_preset)
				 || (active__tune_preset)
				 || (active__cur_load_position)
				 || (active__cur_tune_position)
				 || (active__vpp_value))
			{
				data_0 = r_data[4];
				data_1 = r_data[5];
				
				data_pwr._byte[0] = data_0;
				data_pwr._byte[1] = data_1;

				if(active__load_preset)
				{
					double pwr_value = (data_pwr._hexa / (double) iHEXA__PWR_MAX_1000) * dVALUE__PWR_MAX_1000;
					ch_data.Format("%.1f", pwr_value);
					sCH__INFO_LOAD_PRESET->Set__DATA(ch_data);
				}
				else if(active__tune_preset)
				{
					double pwr_value = (data_pwr._hexa / (double) iHEXA__PWR_MAX_1000) * dVALUE__PWR_MAX_1000;
					ch_data.Format("%.1f", pwr_value);
					sCH__INFO_TUNE_PRESET->Set__DATA(ch_data);
				}
				else if(active__cur_load_position)
				{
					double pwr_value = (data_pwr._hexa / (double) iHEXA__PWR_MAX_1000) * dVALUE__PWR_MAX_1000;
					ch_data.Format("%.1f", pwr_value);
					sCH__INFO_CUR_LOAD_POSITION->Set__DATA(ch_data);
				}
				else if(active__cur_tune_position)
				{
					double pwr_value = (data_pwr._hexa / (double) iHEXA__PWR_MAX_1000) * dVALUE__PWR_MAX_1000;
					ch_data.Format("%.1f", pwr_value);
					sCH__INFO_CUR_TUNE_POSITION->Set__DATA(ch_data);
				}
				else if(active__vpp_value)
				{
					double pwr_value = (data_pwr._hexa / (double) iHEXA__PWR_MAX_1000) * dVALUE__PWR_MAX_1000;
					ch_data.Format("%d", pwr_value);
					sCH__INFO_VPP_VALUE->Set__DATA(ch_data);
				}
				read_data.Format("%02X %02X", r_data[4],r_data[5]);
			}
			// 3 Byte Input ...
			else if((active__fwd_pwr)
				 || (active__ref_pwr)
				 || (active__swr)
				 || (active__phase_shift))
			{
					 if(active__swr)			_Updata__MAT_SWR(r_data[4], r_data[5], r_data[6]);
				else if(active__phase_shift)	_Updata__MAT_PHASE_SHIFT(r_data[4], r_data[5], r_data[6]);
				else
				{
					double dVALUE__PWR_MAX = 10.0;
					_DATA__3BYTE_INT data_pwr_3byte;
					data_pwr_3byte._hexa = 0;

					data_0 = r_data[4];
					data_1 = r_data[5];
					data_2 = r_data[6];

					data_pwr_3byte._byte[0] = data_0;
					data_pwr_3byte._byte[1] = data_1;
					data_pwr_3byte._byte[2] = data_2;

					double pwr_value = (data_pwr_3byte._hexa * dVALUE__PWR_MAX);
					ch_data.Format("%d", pwr_value);

					if(active__fwd_pwr)		sCH__INFO_FORWARD_PWR->Set__DATA(ch_data);
					else					sCH__INFO_REF_PWR->Set__DATA(ch_data);
				}
				read_data.Format("%02X %02X %02X", r_data[4],r_data[5],r_data[6]);
			}
			// 4 Byte Input ...
			else if((active__vrms_lrms)
				|| (active__start_stop_swr))
			{
				if(active__vrms_lrms)			_Updata__MAT_VRMS_IRMS(r_data[4], r_data[5], r_data[6], r_data[7]);
				else if(active__start_stop_swr)	_Updata__MAT_START_STOP_SWR(r_data[4], r_data[5], r_data[6], r_data[7]);

				read_data.Format("%02X %02X %02X %02X", r_data[4],r_data[5],r_data[6],r_data[7]);
			}

			// 5 Byte Input ...
			else if(active__impedance)
			{
				_Updata__MAT_IMPEDANCE(r_data[4], r_data[5], r_data[6], r_data[7], r_data[8]);
				read_data.Format("%02X %02X %02X %02X %02X", r_data[4],r_data[5],r_data[6],r_data[7],r_data[8]);
			}
			else
			{
				read_data = STR__ERROR;
				return -1;
			}
			
			return 1;
		}
		
		read_data = STR__ERROR;
		return -1;
	}

	return -1;
}

//------------------------------------------------------------------------------------
int CObj__MAT_SERIAL
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	unsigned char r_data[MAX_CHAR] = {0,};
	CString ch_data;
	
	byte addr_id = iUNIT__ADDR_ID;

	if((aoCH__LOAD_PRESET->Check__VARIABLE_NAME(var_name) > 0)
	|| (aoCH__LOAD_MANUAL->Check__VARIABLE_NAME(var_name) > 0))
	{
		byte cmmd_id = 0x00;
		byte data_00 = 0x00;
		byte data_01 = 0x00;

		     if(aoCH__LOAD_PRESET->Check__VARIABLE_NAME(var_name) > 0)		cmmd_id = _MAT_CMD__AO_SET_LOAD_PRESET;
		else if(aoCH__LOAD_MANUAL->Check__VARIABLE_NAME(var_name) > 0)		cmmd_id = _MAT_CMD__AO_SET_LOAD_MANUAL;

		//
		int set_hexa = (int) ((set_data / dVALUE__PWR_MAX_1000) * iHEXA__PWR_MAX_1000);
		
		_DATA__2BYTE_INT data_pwr;
		data_pwr._hexa = 0;

		data_pwr._hexa = (int) set_hexa;
		data_00 = data_pwr._byte[0];
		data_01 = data_pwr._byte[1];

		int r_flag = _Send__Command(addr_id,cmmd_id,data_00,data_01);
		if(r_flag > 0)
		{
			ch_data.Format("%.0f", set_hexa);
			sCH__MON_LOAD_POS_SET->Set__DATA(ch_data);
		}
		return r_flag;
	}

	if((aoCH__TUNE_PRESET->Check__VARIABLE_NAME(var_name) > 0)
	|| (aoCH__TUNE_MANUAL->Check__VARIABLE_NAME(var_name) > 0))
	{
		byte cmmd_id = 0x00;
		byte data_00 = 0x00;
		byte data_01 = 0x00;

			 if(aoCH__TUNE_PRESET->Check__VARIABLE_NAME(var_name) > 0)		cmmd_id = _MAT_CMD__AO_SET_TUNE_PRESET;
		else if(aoCH__TUNE_MANUAL->Check__VARIABLE_NAME(var_name) > 0)		cmmd_id = _MAT_CMD__AO_SET_TUNE_MANUAL;

		//
		int set_hexa = (int) ((set_data / dVALUE__PWR_MAX_1000) * iHEXA__PWR_MAX_1000);

		_DATA__2BYTE_INT data_pwr;
		data_pwr._hexa = 0;

		data_pwr._hexa = (int) set_hexa;
		data_00 = data_pwr._byte[0];
		data_01 = data_pwr._byte[1];

		int r_flag = _Send__Command(addr_id,cmmd_id,data_00,data_01);		
		if(r_flag > 0)
		{
			ch_data.Format("%.0f", set_hexa);
			sCH__MON_TUNE_POS_SET->Set__DATA(ch_data);
		}
		return r_flag;
	}

	return -1;
}

int CObj__MAT_SERIAL
::__Write__DIGITAL(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	unsigned char r_data[MAX_CHAR] = {0,};
	CString ch_data;
	CString log_msg;
	CString log_buffer;

	byte addr_id = iUNIT__ADDR_ID;

	// ...
	/*======================================
	Auto-I:			0
	Manual:			1
	Auto-II:		2
	Auto Preset-I:	3 (default)
	Auto Preset-II: 4
	======================================*/
	if(doCH__STATUS_SET->Check__VARIABLE_NAME(var_name)  > 0)
	{
		byte cmmd_id = _MAT_CMD__DO_SET_STATUS;
		byte data_00 = 0x00;
		byte data_01 = 0x00;

		// jglee
		/*
		if(dCH__CFG_MODE_SET->Check__DATA(STR__AUTO) > 0)			data_00 += 0x08;
		else														data_00 += 0x01;
		*/
		if(dCH__CFG_MODE_SET->Check__DATA(STR__AUTO) > 0)			data_00 = 0x03;
		else														data_00 = 0x01;

		int r_flag = _Send__Command(addr_id,cmmd_id,data_00,data_01);

		if(r_flag > 0)
		{
			ch_data = dCH__CFG_MODE_SET->Get__STRING();
			sCH__MON_CONTROL_SET->Set__DATA(ch_data);
		}
		return r_flag;
	}

	if(doCH__MOTOR_RESET->Check__VARIABLE_NAME(var_name)  > 0)
	{
		byte cmmd_id = _MAT_CMD__DO_MOTOR_RESET;
		byte data_00 = 0x00;

		return _Send__Command(addr_id,cmmd_id,data_00);
	}

	return -1;
}

int CObj__MAT_SERIAL
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}

