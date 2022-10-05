#include "StdAfx.h"
#include "CObj__NODA_SERIAL.h"
#include "CObj__NODA_SERIAL__DEF.h"


int CObj__NODA_SERIAL
::Fnc__PRESET_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "\n";
		log_msg += "Preset Set Info ... \n";

		log_bff.Format(" * %s <- %s \n", 
						aCH__PARA_LOAD_POS->Get__CHANNEL_NAME(),
						aCH__PARA_LOAD_POS->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__PARA_TUNE_POS->Get__CHANNEL_NAME(),
						aCH__PARA_TUNE_POS->Get__STRING());
		log_msg += log_bff;

		Write__APP_LOG(log_msg);	
	}

	if(iActive__SIM_MODE > 0)
	{
		ch_data = aCH__PARA_LOAD_POS->Get__STRING();
		sCH__MON_LOAD_POS_SET->Set__DATA(ch_data);

		ch_data = aCH__PARA_TUNE_POS->Get__STRING();
		sCH__MON_TUNE_POS_SET->Set__DATA(ch_data);

		ch_data = STR__AUTO;
		sCH__MON_CONTROL_SET->Set__DATA(ch_data);
		sCH__INFO_STS_MAT_AUTO_MATCHING_STATE->Set__DATA(ch_data);
	}
	else
	{
		aCH__PARA_LOAD_POS->Get__DATA(ch_data);
		aoCH__LOAD_PRESET->Set__DATA(ch_data);

		aCH__PARA_TUNE_POS->Get__DATA(ch_data);
		aoCH__TUNE_PRESET->Set__DATA(ch_data);
	}

	return 1;
}

// ...
unsigned char CObj__NODA_SERIAL
::_Set_CheckSum(unsigned char* s_cmmd, const int s_len)
{
	unsigned char ch_cs = 0;

	for(int i=1; i<s_len ; i++)  
	{	
		ch_cs = ch_cs ^ s_cmmd[i];
	}
	return ch_cs;
}

int  CObj__NODA_SERIAL
::_Check_ErrorCode(unsigned char err_code)
{
	if(err_code == 0x01)		return 1;

	CString str_err = _Get_ErrorCode(err_code);

	sCH__INFO_LAST_ERROR_CODE->Set__DATA(str_err);
	return -1;
}
CString CObj__NODA_SERIAL
::_Get_ErrorCode(unsigned char err_code)
{
	if(err_code == 0xF0)		return "0xF0 : Communication Error";
	if(err_code == 0xF1)		return "0xF1 : CRC Error";
	if(err_code == 0xF2)		return "0xF2 : Data Error";
	if(err_code == 0xF3)		return "0xF3 : E2PROM Error ";

	CString str_err;
	str_err.Format("%02X : Unknown Error", err_code);

	return str_err;
}

int CObj__NODA_SERIAL
::_Send__Command(const byte addr_id,const byte cmmd_id, const byte data_0,const byte data_1)
{
	int	n_cnt = 1;

	// Clear.Data ...
	{
		CString cls_bff;
		mX_Serial->CLEAR__BUFFER(&cls_bff);

		CString r_msg;

		r_msg  = "Clear.Data ... \n";
		r_msg += cls_bff;

		Write__DRV_LOG(r_msg);
	}

	do 
	{
		unsigned char s_cmmd[MAX_CHAR] = {0,};
		unsigned char r_data[MAX_CHAR] = {0,};

		int s_len = 0;
		int r_len = 0;

		// Send Command ...
		{
			s_cmmd[s_len++] = _SM;
			s_cmmd[s_len++] = 0x04;

			s_cmmd[s_len++] = 0xff & addr_id;		// 0x40
			s_cmmd[s_len++] = 0xff & cmmd_id;
			s_cmmd[s_len++] = 0xff & data_0;
			s_cmmd[s_len++] = 0xff & data_1;

			s_cmmd[s_len++] = _Set_CheckSum(s_cmmd, s_len);  
			s_cmmd[s_len++] = _END;
		}

		if(iActive__SIM_MODE > 0)
		{
			CString log_msg;
			CString log_bff;

			log_msg = "Send Data ... \n";

			for(int i=0; i<s_len; i++)
			{
				log_bff.Format("%02X ", s_cmmd[i]);
				log_msg += log_bff;
			}
			log_msg += "\n";

			printf(log_msg);
			return 1;
		}

		// Send Log ...
		{
			CString s_msg;
			CString s_bff;

			s_msg = "Send_Data ... \n";

			for(int i=0; i<s_len; i++)
			{
				s_bff.Format("%02X ", s_cmmd[i]);
				s_msg += s_bff;
			}

			Write__DRV_LOG(s_msg);
		}

		// Send.Data ...
		{
			CString cls_bff;
			mX_Serial->CLEAR__BUFFER(&cls_bff);

			mX_Serial->CHAR__SEND(s_cmmd, s_len);
		}

		// Recv Data ...
		int r_flag = mX_Serial->OnlyRecv__CHAR(r_data, _END, &r_len, m_Rcv_Time);

		// Recv Log ...
		{
			CString r_msg;
			CString r_bff;

			r_msg.Format("Recv_Data (%1d) ... \n", r_flag);

			for(int i=0; i<r_len; i++)
			{
				r_bff.Format("%02X ", r_data[i]);
				r_msg += r_bff;
			}

			Write__DRV_LOG(r_msg);
		}

		if(r_flag > 0)
		{
			dCH__MON_COMM_STS->Set__DATA(STR__ONLINE); 

			if(r_len > 4)
			{
				if(r_data[4] == 0x01)
				{
					return r_len;
				}
			}
			return -1;
		}

		Sleep(100);
	}
	while(++n_cnt <= m_RetryCnt);

	dCH__MON_COMM_STS->Set__DATA(STR__OFFLINE); 
	return -1;
}

int CObj__NODA_SERIAL
::_Recv__Command(const byte addr_id,const byte cmmd_id, unsigned char* recv_data)
{
	int	n_cnt = 1;

	// Clear.Data ...
	{
		CString cls_bff;
		mX_Serial->CLEAR__BUFFER(&cls_bff);

		CString r_msg;

		r_msg  = "Clear.Data ... \n";
		r_msg += cls_bff;

		Write__DRV_LOG(r_msg);
	}

	do 
	{
		unsigned char s_cmmd[MAX_CHAR] = {0,};
		unsigned char r_data[MAX_CHAR] = {0,};

		int s_len = 0;
		int r_len = 0;

		// Send Command ...
		{
			s_cmmd[s_len++] = _SM;
			s_cmmd[s_len++] = 0x02;

			s_cmmd[s_len++] = 0xff & addr_id;
			s_cmmd[s_len++] = 0xff & cmmd_id;

			s_cmmd[s_len++] = _Set_CheckSum(s_cmmd, s_len);  
			s_cmmd[s_len++] = _END;
		}

		// Send Log ...
		{
			CString s_msg;
			CString s_bff;

			s_msg = "Send_Data ... \n";

			for(int i=0; i<s_len; i++)
			{
				s_bff.Format("%02X ", s_cmmd[i]);
				s_msg += s_bff;
			}

			Write__DRV_LOG(s_msg);
		}

		// Send Data ...
		{
			CString cls_bff;
			mX_Serial->CLEAR__BUFFER(&cls_bff);

			mX_Serial->CHAR__SEND(s_cmmd, s_len);
		}

		// Recv Data ...
		int r_flag = mX_Serial->OnlyRecv__CHAR(r_data, _END, &r_len, m_Rcv_Time);

		// Recv Log ...
		{
			CString r_msg;
			CString r_bff;

			r_msg.Format("Recv_Data (%1d) ... \n", r_flag);

			if(r_len > MAX_CHAR)		r_len = MAX_CHAR - 1;

			for(int i=0; i<r_len; i++)
			{
				r_bff.Format("%02X ", r_data[i]);
				r_msg += r_bff;

				recv_data[i] = r_data[i];
			}

			Write__DRV_LOG(r_msg);
		}

		if(r_flag > 0)
		{
			dCH__MON_COMM_STS->Set__DATA(STR__ONLINE); 

			if(r_len > 6)		return r_len;
			return -1;
		}

		Sleep(100);
	}
	while(++n_cnt <= m_RetryCnt);

	dCH__MON_COMM_STS->Set__DATA(STR__OFFLINE); 
	return -1;
}

// ...
void CObj__NODA_SERIAL
::_Update__MAT_State(unsigned char data_0, unsigned char data_1)
{
	CString ch_data;
	unsigned char bit_sts;

	// BYTE : 0
	{
		ch_data.Format("%02X", data_0);
		sCH__INFO_STS_HEXA_0->Set__DATA(ch_data);

		// BIT [0] : Auto Matching State
		{
			bit_sts = 0x01 & data_0;

			if(bit_sts == 0x00)		ch_data = "STAND-BY";
			else					ch_data = "AUTO-ON";

			sCH__INFO_STS_MAT_AUTO_MATCHING_STATE->Set__DATA(ch_data);
		}
		// BIT [1] : Matching Mode
		{
			bit_sts = 0x02 & data_0;

			if(bit_sts == 0x00)		ch_data = STR__MANUAL;
			else					ch_data = STR__AUTO;

			sCH__INFO_STS_MAT_MATCHING_MODE->Set__DATA(ch_data);
		}
		// BIT [2] : lms error
		{
			bit_sts = 0x04 & data_0;

			if(bit_sts == 0x00)		ch_data = STR__NORMAL;
			else					ch_data = STR__ABNORMAL;

			sCH__INFO_STS_MAT_IRMS_ERROR->Set__DATA(ch_data);
		}
		// BIT [3] : preset enable
		{
			bit_sts = 0x08 & data_0;

			if(bit_sts == 0x00)		ch_data = STR__DISABLE;
			else					ch_data = STR__ENABLE;

			sCH__INFO_STS_MAT_PRESET_ENABLE->Set__DATA(ch_data);
		}

		// BIT [4] : motor error 
		{
			bit_sts = 0x10 & data_0;

			if(bit_sts == 0x00)		ch_data = STR__NORMAL;
			else					ch_data = STR__ABNORMAL;

			sCH__INFO_STS_MAT_MOTOR_ERROR->Set__DATA(ch_data);
		}
		// BIT [5] : flow error 
		{
			bit_sts = 0x20 & data_0;

			if(bit_sts == 0x00)		ch_data = STR__NORMAL;
			else					ch_data = STR__ABNORMAL;

			sCH__INFO_STS_MAT_FLOW_ERROR->Set__DATA(ch_data);
		}
		// BIT [6] : coax error 
		{
			bit_sts = 0x40 & data_0;

			if(bit_sts == 0x00)		ch_data = STR__NORMAL;
			else					ch_data = STR__ABNORMAL;

			sCH__INFO_STS_MAT_COAX_ERROR->Set__DATA(ch_data);
		}
		// BIT [7] : temperature error 
		{
			bit_sts = 0x80 & data_0;

			if(bit_sts == 0x00)		ch_data = STR__NORMAL;
			else					ch_data = STR__ABNORMAL;

			sCH__INFO_STS_MAT_TEMPERATURE_ERROR->Set__DATA(ch_data);
		}
	}

	// BYTE : 1
	{
		ch_data.Format("%02X", data_1);
		sCH__INFO_STS_HEXA_1->Set__DATA(ch_data);

		// BIT [12 & 13] : preset mode
		{
			bit_sts = 0x30 & data_1;

				 if(bit_sts == 0x00)		ch_data = STR__INTERNAL;
			else if(bit_sts == 0x10)		ch_data = STR__EXTERNAL;
			else							ch_data = STR__NOT_USE;

			sCH__INFO_STS_MAT_PRESET_MODE->Set__DATA(ch_data);
		}
		// BIT [15] : hd con
		{
			bit_sts = 0x80 & data_1;
			
			if(bit_sts == 0x00)		ch_data = STR__DISABLE;
			else					ch_data = STR__ENABLE;
			
			sCH__INFO_STS_MAT_HD_CON->Set__DATA(ch_data);
		}
	}
}

