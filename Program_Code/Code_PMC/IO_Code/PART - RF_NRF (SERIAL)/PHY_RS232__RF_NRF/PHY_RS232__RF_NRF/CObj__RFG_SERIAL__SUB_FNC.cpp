#include "StdAfx.h"
#include "CObj__RFG_SERIAL.h"
#include "CObj__RFG_SERIAL__DEF.h"


// ...
unsigned char CObj__RFG_SERIAL
::_Set_CheckSum(unsigned char* s_cmmd, const int s_len)
{
	unsigned char ch_cs = 0;

	for(int i=1; i<s_len ; i++)  
	{	
		ch_cs = ch_cs ^ s_cmmd[i];
	}
	return ch_cs;
}

int  CObj__RFG_SERIAL
::_Check_ErrorCode(unsigned char err_code)
{
	if(err_code == 0x01)		return 1;

	CString str_err = _Get_ErrorCode(err_code);

	sCH__INFO_LAST_ERROR_CODE->Set__DATA(str_err);
	return -1;
}
CString CObj__RFG_SERIAL
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

int CObj__RFG_SERIAL
::_Recv__Command(const byte addr_id,const byte cmmd_id, const byte data_0,const byte data_1)
{
	int	n_cnt = 1;

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
			
			s_cmmd[s_len++] = 0xff & addr_id;
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

		// Send.Data ...
		{
			CString cls_bff;
			mX_Serial->CLEAR__BUFFER(&cls_bff);

			mX_Serial->CHAR__SEND(s_cmmd, s_len);
		}

		// Recv.Data ...
		int r_flag = mX_Serial->OnlyRecv__CHAR(r_data, _END, &r_len, m_Rcv_Time);
		
		// Send.Log ...
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
		// Recv.Log ...
		{
			CString r_msg;
			CString r_bff;

			r_msg.Format("Recv_Data (%1d) \n", r_flag);

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

			// ...
			unsigned char err_code = 0xFF;

			if(r_len > 5)		err_code = r_data[4];

			return _Check_ErrorCode(err_code);
		}

		Sleep(100);
	}
	while(++n_cnt <= m_RetryCnt);

	dCH__MON_COMM_STS->Set__DATA(STR__OFFLINE); 
	return -1;
}

int CObj__RFG_SERIAL
::_Recv__Command(const byte addr_id,const byte cmmd_id, unsigned char* r_data)
{
	int	n_cnt = 1;

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

		// Send Data ...
		{
			CString cls_bff;
			mX_Serial->CLEAR__BUFFER(&cls_bff);

			mX_Serial->CHAR__SEND(s_cmmd, s_len);
		}

		// Recv Data ...
		int r_flag = mX_Serial->OnlyRecv__CHAR(r_data, _END, &r_len, m_Rcv_Time);

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
void CObj__RFG_SERIAL
::_Update__RF_State(unsigned char data_0, unsigned char data_1)
{
	CString ch_data;
	unsigned char bit_sts;

	// BYTE : 0
	{
		ch_data.Format("%02X", data_0);
		sCH__INFO_STS_HEXA_0->Set__DATA(ch_data);
		
		// BIT [1]
		{
			bit_sts = 0x02 & data_0;		

			if(bit_sts == 0)		ch_data = STR__OFF;
			else					ch_data = STR__ON;

			sCH__INFO_STS_RF_OUTPUT_CONTROL->Set__DATA(ch_data);
		}
		// BIT [2]
		{
			bit_sts = 0x04 & data_0;		

			if(bit_sts == 0)		ch_data = STR__CW;
			else					ch_data = STR__PULSE;
			
			sCH__INFO_STS_RF_MODE_CONTROL->Set__DATA(ch_data);
		}
		// BIT [6]
		{
			bit_sts = 0x40 & data_0;		

			if(bit_sts == 0)		ch_data = STR__Normal;
			else					ch_data = STR__Abnormal;

			sCH__INFO_STS_ALARM->Set__DATA(ch_data);
		}
	}

	// BYTE : 1
	{
		ch_data.Format("%02X", data_0);
		sCH__INFO_STS_HEXA_1->Set__DATA(ch_data);
	
		// BIT [0]
		{
			bit_sts = 0x01 & data_1;		

			if(bit_sts == 0)		ch_data = STR__Normal;
			else					ch_data = STR__Abnormal;

			sCH__INFO_STS_TEMPERATURE->Set__DATA(ch_data);
		}
		// BIT [1]
		{
			bit_sts = 0x02 & data_1;		

			if(bit_sts == 0)		ch_data = STR__Normal;
			else					ch_data = STR__Abnormal;

			sCH__INFO_STS_INTERLOCK->Set__DATA(ch_data);
		}
		// BIT [3]
		{
			bit_sts = 0x08 & data_1;		

			if(bit_sts == 0)		ch_data = STR__Normal;
			else					ch_data = STR__Abnormal;

			sCH__INFO_STS_AMP->Set__DATA(ch_data);
		}
		// BIT [7]
		{
			bit_sts = 0x80 & data_1;		

			if(bit_sts == 0)		ch_data = STR__Disable;
			else					ch_data = STR__Enable;

			sCH__INFO_STS_HD_CON->Set__DATA(ch_data);
		}
	}
}

