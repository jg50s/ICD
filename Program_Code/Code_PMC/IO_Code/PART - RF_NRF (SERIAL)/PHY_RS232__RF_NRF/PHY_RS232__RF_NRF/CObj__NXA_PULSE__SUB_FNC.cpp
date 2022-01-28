#include "StdAfx.h"
#include "CObj__NXA_PULSE.h"
#include "CObj__NXA_PULSE__DEF.h"


// ...
unsigned char CObj__NXA_PULSE
::_Set_CheckSum(unsigned char* s_cmmd, const int s_len)
{
	unsigned char ch_cs = 0;

	for(int i=1; i<s_len ; i++)  
	{	
		ch_cs += s_cmmd[i];
	}
	return ch_cs;
}

int  CObj__NXA_PULSE
::_Check_ErrorCode(unsigned char err_code)
{
	if(err_code == 0x01)		return 1;

	CString str_err = _Get_ErrorCode(err_code);

	sCH__INFO_LAST_ERROR_CODE->Set__DATA(str_err);
	return -1;
}
CString CObj__NXA_PULSE
::_Get_ErrorCode(unsigned char err_code)
{
	if(err_code == 0xF0)		return "0xF0 : Communication Error";
	if(err_code == 0xF1)		return "0xF1 : CheckSum Error";
	if(err_code == 0xF2)		return "0xF2 : Parameter Error";
	if(err_code == 0xF3)		return "0xF3 : Execution Error ";
	if(err_code == 0xF4)		return "0xF3 : Etc. Error";

	CString str_err;
	str_err.Format("%02X : Unknown Error", err_code);

	return str_err;
}

int CObj__NXA_PULSE
::_Recv__Command(const unsigned char cmmd_id, const unsigned char* param_data,const int param_size)
{
	int	n_cnt = 1;

	do 
	{
		unsigned char s_cmmd[MAX_CHAR] = {0,};
		unsigned char r_data[MAX_CHAR] = {0,};

		int s_len = 0;
		int r_len = 0;
		int i;

		// Send Command ...
		{
			s_cmmd[s_len++] = _STX;
			s_cmmd[s_len++] = 0x0ff & (param_size + 1);
			s_cmmd[s_len++] = 0x0ff & cmmd_id;

			for(i=0; i<param_size; i++)
				s_cmmd[s_len++] = 0xff & param_data[i];

			s_cmmd[s_len++] = 0x0ff & _Set_CheckSum(s_cmmd, s_len);  
			s_cmmd[s_len++] = _ETX;
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
		int r_flag = mX_Serial->OnlyRecv__CHAR(r_data, _ETX, &r_len, m_Rcv_Time);

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

			if(r_len > 3)		err_code = r_data[3];

			return _Check_ErrorCode(err_code);
		}

		Sleep(100);
	}
	while(++n_cnt <= m_RetryCnt);

	dCH__MON_COMM_STS->Set__DATA(STR__OFFLINE); 
	return -1;
}

int CObj__NXA_PULSE
::_Recv__Command(const unsigned char cmmd_id, unsigned char* r_data)
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
			s_cmmd[s_len++] = _STX;
			s_cmmd[s_len++] = 1;
			s_cmmd[s_len++] = 0x0ff & cmmd_id;

			s_cmmd[s_len++] = 0x0ff & _Set_CheckSum(s_cmmd, s_len);  
			s_cmmd[s_len++] = _ETX;
		}

		// Send Data ...
		{
			CString cls_bff;
			mX_Serial->CLEAR__BUFFER(&cls_bff);

			mX_Serial->CHAR__SEND(s_cmmd, s_len);
		}

		// Recv Data ...
		int r_flag = mX_Serial->OnlyRecv__CHAR(r_data, _ETX, &r_len, m_Rcv_Time);

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

			if(r_len > 3)
			{
				int s_cmmd = 0x0ff & (cmmd_id + 0x80);
				int r_cmmd = 0x0ff & r_data[2];

				if(s_cmmd == r_cmmd)		return r_len;
			}
			return -1;
		}

		Sleep(100);
	}
	while(++n_cnt <= m_RetryCnt);

	dCH__MON_COMM_STS->Set__DATA(STR__OFFLINE); 
	return -1;
}


CString CObj__NXA_PULSE
::_Get__CLK_STATE(const unsigned clk_sts)
{
	if(clk_sts == 0)		return STR__ON;
	if(clk_sts == 1)		return "REVERSE";
	if(clk_sts == 2)		return "HIGH";
	if(clk_sts == 3)		return STR__OFF;

	return "UNKNOWN";
}

