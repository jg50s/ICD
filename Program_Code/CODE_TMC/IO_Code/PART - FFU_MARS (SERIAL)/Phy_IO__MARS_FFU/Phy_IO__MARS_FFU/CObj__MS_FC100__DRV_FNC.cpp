#include "StdAfx.h"
#include "CObj__MS_FC100.h"



//------------------------------------------------------------------------------------
int CObj__MS_FC100
::__Read__ANALOG(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 double& read_data)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg  = "__Read__ANALOG()";
		log_msg += "\n";

		log_bff.Format(" * %s", var_name); 
		log_msg += log_bff;

		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	return -1;
}

int CObj__MS_FC100
::__Read__DIGITAL(const CString& var_name,
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  CString& read_data,
				  int& item_index)
{
	CString log_msg;
	CString log_bff;

	CString ch_data;
	int i;

	// ...
	{
		log_msg  = "__Read__DIGITAL()";
		log_msg += "\n";

		log_bff.Format(" * %s", var_name); 
		log_msg += log_bff;

		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	// ...'
	unsigned char cmmd_byte = 0x00;

	if(diCH__FFU_Status_Get->Check__VARIABLE_NAME(var_name) > 0)
	{
		cmmd_byte = _CMMD_MODE__STATUS_GET;
	}
	else if(diCH__FFU_Group_Get->Check__VARIABLE_NAME(var_name) > 0)
	{
		cmmd_byte = _CMMD_MODE__GROUP_GET;
	}
	else if(diCH__FFU_Block_Get->Check__VARIABLE_NAME(var_name) > 0)
	{
		cmmd_byte = _CMMD_MODE__BLOCK_GET;
	}

	if(cmmd_byte == 0x00)
	{
		log_msg = " * Variable Error !";

		Fnc__DRV_LOG_OF_MSG(log_msg);		
		return -1;
	}

	// ...
	unsigned char r_data[CFG__MAX_DATA];
	memset(r_data, 0, sizeof(r_data));

	int r_ret = _Recv_Command(cmmd_byte, r_data);
	if(r_ret < 0)		return -1;

	// ...
	if(diCH__FFU_Status_Get->Check__VARIABLE_NAME(var_name) > 0)
	{
		int i_sts = r_data[0];

		ch_data.Format("%02X", i_sts);
		sCH__FFU_Status__HEXA->Set__DATA(ch_data);

		// 0x00 : No Connection
		if(i_sts & 0x01)		sCH__FFU_Status__NO_CONNECTION->Set__DATA(STR__OFF);
		else					sCH__FFU_Status__NO_CONNECTION->Set__DATA(STR__ON);
		
		// 0x01 : Fan 동작 Error
		if(i_sts & 0x01)		sCH__FFU_Status__FAN_ERROR->Set__DATA(STR__ON);
		else					sCH__FFU_Status__FAN_ERROR->Set__DATA(STR__OFF);
		
		// 0x02 : 차압센서 압력 Error
		if(i_sts & 0x02)		sCH__FFU_Status__DIF_PRESS_ERROR->Set__DATA(STR__ON);
		else					sCH__FFU_Status__DIF_PRESS_ERROR->Set__DATA(STR__OFF);

		// 0x04 : RPM High Setting Error
		if(i_sts & 0x04)		sCH__FFU_Status__RPM_HIGH_ERROR->Set__DATA(STR__ON);
		else					sCH__FFU_Status__RPM_HIGH_ERROR->Set__DATA(STR__OFF);

		// 0x08 : RPM Low Setting Error
		if(i_sts & 0x08)		sCH__FFU_Status__RPM_LOW_ERROR->Set__DATA(STR__ON);
		else					sCH__FFU_Status__RPM_LOW_ERROR->Set__DATA(STR__OFF);

		// 0x10 : 차압 High Setting Error
		if(i_sts & 0x10)		sCH__FFU_Status__DIF_PRESS_HIGH_ERROR->Set__DATA(STR__ON);
		else					sCH__FFU_Status__DIF_PRESS_HIGH_ERROR->Set__DATA(STR__OFF);

		// 0x20 : 차압 Low Setting Error
		if(i_sts & 0x20)		sCH__FFU_Status__DIF_PRESS_LOW_ERROR->Set__DATA(STR__ON);
		else					sCH__FFU_Status__DIF_PRESS_LOW_ERROR->Set__DATA(STR__OFF);

		// 0x40 : 안정화 시간 오버 Error
		if(i_sts & 0x40)		sCH__FFU_Status__STABLE_TIME_ERROR->Set__DATA(STR__ON);
		else					sCH__FFU_Status__STABLE_TIME_ERROR->Set__DATA(STR__OFF);

		return 1;
	}
	if(diCH__FFU_Group_Get->Check__VARIABLE_NAME(var_name) > 0)
	{
		for(i=0; i<CFG__FAN_SIZE; i++)
		{
			int i_offset = i * 6;

			CString str_hexa;
			int i_hex = 0;

			// HEXA ...
			{
				int k_limit = 6;
				int k;

				ch_data = "";

				for(k=0; k<k_limit; k++)
				{
					// 0 : FanID
					// 1 : RPM PV
					// 2 : AL&ST
					// 3 : RPM SV
					// 4 : PRES LOW
					// 5 : PRES HI
					
					i_hex = 0x0ff & r_data[i_offset + k];
					str_hexa.Format("%02X ", i_hex);
					ch_data += str_hexa;
				}

				sCH__FFU_FAN_X__STATE_HEXA[i]->Set__DATA(ch_data);
			}

			// 1 : RPM PV
			{
				i_hex = 0x0ff & r_data[1 + i_offset];
				double value_pv = i_hex * 10.0;

				ch_data.Format("%.0f", value_pv);
				sCH__FFU_FAN_X__RPM_PV[i]->Set__DATA(ch_data);
			}
			// 3 : RPM SV
			{
				i_hex = 0x0ff & r_data[3 + i_offset];
				double value_sv = i_hex * 10.0;

				ch_data.Format("%.0f", value_sv);
				sCH__FFU_FAN_X__RPM_SV[i]->Set__DATA(ch_data);
			}
			// 4 : PRES LOW
			// 5 : PRES HI
			{
				int low_hex  = 0x0ff & r_data[4 + i_offset];
				int high_hex = 0x0ff & r_data[5 + i_offset];

				double value_presx = (high_hex * 100.0) + (low_hex * 10.0);
				
				ch_data.Format("%.0f", value_presx);
				sCH__FFU_FAN_X__DIFF_PRESS[i]->Set__DATA(ch_data);
			}
		}

		return 1;
	}
	if(diCH__FFU_Block_Get->Check__VARIABLE_NAME(var_name) > 0)
	{
		/*
		int s_i = 0;
		int e_i = 0;

		if(e_i > CFG__FAN_SIZE)		e_i = CFG__FAN_SIZE;

		for(i=s_i; i<e_i; i++)
		{
			sCH__FFU_FAN_X__STATE_HEXA[i]->Set__DATA(ch_data);

			sCH__FFU_FAN_X__RPM_PV[i]->Set__DATA(ch_data);

			sCH__FFU_FAN_X__RPM_SV[i]->Set__DATA(ch_data);

			sCH__FFU_FAN_X__DIFF_PRESS[i]->Set__DATA(ch_data);
		}
		*/
		return 1;
	}

	return -1;
}

int CObj__MS_FC100
::__Read__STRING(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 CString& read_data)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg  = "__Read__STRING()";
		log_msg += "\n";

		log_bff.Format(" * %s", var_name); 
		log_msg += log_bff;

		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__MS_FC100
::__Write__ANALOG(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const double set_data)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg  = "__Write__ANALOG()";
		log_msg += "\n";

		log_bff.Format(" * %s <- [%.3f]", var_name,set_data); 
		log_msg += log_bff;

		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	return -1;
}

int CObj__MS_FC100
::__Write__DIGITAL(const CString& var_name,
				   const CDS_IO__CHANNEL_INFO& io_info, 
				   const CString& set_data,
				   const int item_index)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg  = "__Write__DIGITAL()";
		log_msg += "\n";

		log_bff.Format(" * %s <- [%s]", var_name,set_data); 
		log_msg += log_bff;

		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	// ...
	unsigned char cmmd_byte = 0x00;
	
	double set_sv = 0;
	double set_pressure = 0;
	int  block_id = 0;
	int  block_sz = 0;

	if(doCH__FFU_Group_Set->Check__VARIABLE_NAME(var_name) > 0)
	{
		cmmd_byte  = _CMMD_MODE__GROUP_SET;

		set_sv = aCH__FFU_Group_Para_Set_RPM->Get__VALUE();
		set_pressure = aCH__FFU_Group_Para_Set_PRESSURE->Get__VALUE();
	}
	else if(doCH__FFU_Block_Set->Check__VARIABLE_NAME(var_name) > 0)
	{
		cmmd_byte  = _CMMD_MODE__BLOCK_SET;

		block_id = (int) aCH__FFU_Block_Para_Set_StartID->Get__VALUE();
		block_sz = (int) aCH__FFU_Block_Para_Set_Size->Get__VALUE();

		set_sv = aCH__FFU_Block_Para_Set_RPM->Get__VALUE();
		set_pressure = aCH__FFU_Block_Para_Set_PRESSURE->Get__VALUE();
	}

	if(cmmd_byte == 0x00)
	{
		log_msg = " * Variable Error !";

		Fnc__DRV_LOG_OF_MSG(log_msg);		
		return -1;
	}

	// ...
	unsigned char r_data[CFG__MAX_DATA];

	int r_ret = _Recv_Command(cmmd_byte, r_data, set_sv,set_pressure, block_id,block_sz);
	if(r_ret < 0)		return -1;

	// ...
	if((doCH__FFU_Group_Set->Check__VARIABLE_NAME(var_name) > 0)
	|| (doCH__FFU_Block_Set->Check__VARIABLE_NAME(var_name) > 0))
	{
		return 1;
	}

	return -1;
}

int CObj__MS_FC100
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__MS_FC100::
_Recv_Command(const unsigned char cmmd_type, 
			  unsigned char* r_xxxx, 
			  const double set_sv,
			  const double set_pressure, 
			  const int block_id,
			  const int block_sz)
{
	unsigned char s_data[CFG__MAX_DATA];
	unsigned char r_data[CFG__MAX_DATA];

	ZeroMemory(s_data, sizeof(s_data));
	ZeroMemory(r_data, sizeof(r_data));
	ZeroMemory(r_xxxx, sizeof(r_xxxx));

	// ...
	int i_db;
	
	i_db = 0;
	s_data[i_db++] = STX;
	s_data[i_db++] = cmmd_type;

	if(cmmd_type == _CMMD_MODE__STATUS_GET)
	{
		s_data[i_db++] = 0x81;
	}
	else if((cmmd_type == _CMMD_MODE__GROUP_SET)
	     || (cmmd_type == _CMMD_MODE__GROUP_GET)
		 || (cmmd_type == _CMMD_MODE__BLOCK_SET)
		 || (cmmd_type == _CMMD_MODE__BLOCK_GET))
	{
		s_data[i_db++] = 0x9f;
		
		s_data[i_db++] = 0x81;
		s_data[i_db++] = 0x9f;
	}
	else
	{
		return -1;
	}

	if(cmmd_type == _CMMD_MODE__GROUP_SET)
	{
		s_data[i_db++] = 0x0ff & ((int) (set_sv * 0.1));
		s_data[i_db++] = 0x0ff & ((int) (set_pressure * 0.1));
		s_data[i_db++] = 0x0ff & ((int) (set_pressure * 0.01));
	}
	else if(cmmd_type == _CMMD_MODE__BLOCK_SET)
	{
		s_data[i_db++] = 0x0ff & (block_id + 0x80);
		s_data[i_db++] = 0x0ff & (block_sz + 0x80);

		s_data[i_db++] = 0x0ff & ((int) (set_sv * 0.1));
		s_data[i_db++] = 0x0ff & ((int) (set_pressure * 0.1));
		s_data[i_db++] = 0x0ff & ((int) (set_pressure * 0.01));
	}
	else if(cmmd_type == _CMMD_MODE__GROUP_GET)
	{

	}
	else if(cmmd_type == _CMMD_MODE__BLOCK_GET)
	{
		s_data[i_db++] = 0x0ff & (block_id + 0x80);
		s_data[i_db++] = 0x0ff & (block_sz + 0x80);
	}

	s_data[i_db++] = _Get_CheckSum(s_data,i_db);
	s_data[i_db++] = ETX;

	// ...
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg = "_Recv_Command() ... \n";
		log_msg += "  > ";

		for(int i=0; i<i_db; i++)
		{
			log_bff.Format("%02X ", 0x0ff&s_data[i]);
			log_msg += log_bff;
		}
		log_msg += "\n";
		
		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	// ...
	int check_flag = 1;
	int n_counter  = 0;

	int r_len = 0;

	if(cmmd_type == _CMMD_MODE__STATUS_GET)
	{
		r_len = 6;
	}
	else if(cmmd_type == _CMMD_MODE__GROUP_SET)
	{
		r_len = 8;
	}
	else if(cmmd_type == _CMMD_MODE__GROUP_GET)
	{
		r_len = 7 + (6*4);
	}
	else if(cmmd_type == _CMMD_MODE__BLOCK_SET)
	{
		r_len = 10;
	}
	else if(cmmd_type == _CMMD_MODE__BLOCK_GET)
	{
		r_len = 7 + (6*block_sz);
	}

	do
	{
		// ...
		{
			CString str_log;
			mX_Serial->CLEAR__BUFFER(&str_log);
		}

		int s_ret = mX_Serial->CHAR__SEND(s_data, i_db);
		
		int ref_len = r_len;
		int r_count = mX_Serial->OnlyRecv__CHAR(r_data, &r_len, m_Rcv_Time);

		// ...
		{
			log_msg = "OnlyRecv__CHAR() ...\n";

			log_bff.Format(" * ref_len <- %1d \n", ref_len);
			log_msg += log_bff;

			log_bff.Format(" * r_len <- %1d \n", r_len);
			log_msg += log_bff;

			log_bff.Format(" * r_count <- %1d \n", r_count);
			log_msg += log_bff;

			log_msg += "  < ";

			for(int i=0; i<r_len; i++)
			{
				log_bff.Format("%02X ", r_data[i]);
				log_msg += log_bff;
			}

			Fnc__DRV_LOG_OF_MSG(log_msg);
		}

		if(ref_len == r_len)
		{
			int i_count = 0;

			for(int i=5; i<ref_len; i++)
			{
				r_xxxx[i-5] = r_data[i];
				i_count++;;
			}

			iCOMM_STATE = ONLINE;
			return i_count;
		}
	}
	while(++n_counter < m_nRetryCnt);

	iCOMM_STATE = OFFLINE;
	return -1;
}
