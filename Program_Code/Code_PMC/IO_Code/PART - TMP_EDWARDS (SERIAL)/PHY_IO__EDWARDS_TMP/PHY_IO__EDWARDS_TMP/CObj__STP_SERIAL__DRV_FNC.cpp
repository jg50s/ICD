#include "StdAfx.h"
#include "CObj__STP_SERIAL.h"

#include "Macro_Function.h"


//------------------------------------------------------------------------------------
int CObj__STP_SERIAL
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__STP_SERIAL
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{

	if(diCH__COMM_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(m_nCommState == DRV__OFFLINE)		read_data = STR__OFFLINE;
		else									read_data = STR__ONLINE;
			
		return 1;
	}
	
	return -1;
}

int CObj__STP_SERIAL
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString ch_data;

	CString str_cmmd;
	CString r_data;


	if(siCH__ReadMeas_HEXA->Check__VARIABLE_NAME(var_name) > 0)
	{
		str_cmmd = "?D";

		int r_val = Recv_Command(var_name, str_cmmd, r_data);
		if(r_val < 0)
		{
			read_data = "Error";
			return 1;
		}

		// ...
		CString para_01 = r_data.Mid(0, 14);
		CString para_02 = r_data.Mid(14, 4);

		// ...
		{
			int i_value = Macro__HexToDec(para_02);

			ch_data.Format("%1d", i_value);
			sCH__INFO_ROT_SPEED_HZ->Set__DATA(ch_data);

			ch_data.Format("%1d", i_value * 60);
			sCH__INFO_ROT_SPEED_RPM->Set__DATA(ch_data);
		}

		read_data = para_02;
		return 1;
	}

	if(siCH__ReadModFonct->Check__VARIABLE_NAME(var_name) > 0)
	{
		str_cmmd = "?M";

		int r_val = Recv_Command(var_name, str_cmmd, r_data);
		if(r_val < 0)
		{
			read_data = "Error";
			return 1;
		}

		// ...
		CString para_01 = r_data.Mid(0, 2);
		CString para_02 = r_data.Mid(2, 2);

		int cur__op_mode = Macro__HexToDec(para_01);
		int cur__err_cnt = Macro__HexToDec(para_02);
			
		// OP_MODE ...
		{
			CString str__op_mode;

			switch(cur__op_mode)
			{
				case 1:			str__op_mode = STR__Levitation;			break;
				case 2:			str__op_mode = STR__NoLevitation;		break;
				case 3:			str__op_mode = STR__Acceleration;		break;
				case 4:			str__op_mode = STR__Normal;				break;
				case 5:			str__op_mode = STR__Deceleration;		break;
				case 6:			str__op_mode = STR__AutoTest;			break;
				case 7:			str__op_mode = STR__Tuning;				break;
				case 8:			str__op_mode = STR__Tuning_Complete;	break;

				case 9:
				case 10:
				case 11:
					str__op_mode = "[System Reservation]";		
					break;

				default:
					str__op_mode = "Unknown";
					break;
			}

			sCH__INFO_PUMP_OP_MODE->Set__DATA(str__op_mode);
		}
		// ERR_COUNT ...
		{
			ch_data.Format("%1d", cur__err_cnt);
			sCH__INFO_ERROR_COUNT->Set__DATA(ch_data);
		}

		read_data = "OK";
		return 1;
	}

	if(siCH__All_Version->Check__VARIABLE_NAME(var_name) > 0)
	{
		str_cmmd = "?V";

		int r_val = Recv_Command(var_name, str_cmmd, r_data);
		if(r_val < 0)
		{
			read_data = "Error";
			return 1;
		}

		// ...
		CString para_01 = r_data.Mid(0, 32);
		CString para_02 = r_data.Mid(32, 4);
		CString para_03 = r_data.Mid(36, 4);

		// ...
		{
			ch_data = Macro__HEX_ASCII_TO_ASCII(para_01);
			sCH__INFO_VERSION__CTRL_UNIT->Set__DATA(ch_data);

			ch_data = para_02;
			sCH__INFO_VERSION__MTR_DRV->Set__DATA(ch_data);

			ch_data = para_03;
			sCH__INFO_VERSION__AMB_SW->Set__DATA(ch_data);
		}

		read_data = "OK";
		return 1;
	}

	if(siCH__ReadSetPoint->Check__VARIABLE_NAME(var_name) > 0)
	{
		str_cmmd = "?d";

		int r_val = Recv_Command(var_name, str_cmmd, r_data);
		if(r_val < 0)
		{
			read_data = "Error";
			return 1;
		}

		// ...
		CString para_01 = r_data.Mid(0, 4);
		CString para_02 = r_data.Mid(4, 4);

		// ...
		{
			int speed_hz = Macro__HexToDec(para_01);

			ch_data.Format("%1d", speed_hz);
			sCH__INFO_SPEED_SETPOINT_HZ->Set__DATA(ch_data);

			ch_data.Format("%1d", speed_hz * 60);
			sCH__INFO_SPEED_SETPOINT_RPM->Set__DATA(ch_data);

			//
			ch_data.Format("%1d", Macro__HexToDec(para_02));
			sCH__INFO_TMS_TEMPERATURE_SETTING->Set__DATA(ch_data);
		}

		read_data = "OK";
		return 1;
	}

	if(siCH__ReadMotorTemp->Check__VARIABLE_NAME(var_name) > 0)
	{
		str_cmmd = "?d";

		int r_val = Recv_Command(var_name, str_cmmd, r_data);
		if(r_val < 0)
		{
			read_data = "Error";
			return 1;
		}

		// ...
		CString para_01 = r_data.Mid(0, 4);

		read_data.Format("%1d", Macro__HexToDec(para_01));
		return 1;
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__STP_SERIAL
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	CString str_cmmd;
	CString s_data;
	CString r_data;

	if(aoCH__SET_SPEED_HZ->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_data.Format("%04X", (int) set_data);

		str_cmmd  = " h";
		str_cmmd += s_data;

		int r_val = Recv_Command(var_name, str_cmmd, r_data);
		if(r_val < 0)
		{
			return -1;
		}

		return 1;
	}

	return 1;
}

int CObj__STP_SERIAL
::__Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	printf(" * __Write__DIGITAL() ... \n");
	printf("  * var_name   <- %s  \n", var_name);
	printf("  * set_data   <- %s  \n", set_data);
	printf("  * item_index <- %1d \n", item_index);

	// ...
	CString str_cmmd;
	CString r_data;


	if(doCH__OP_CMMD->Check__VARIABLE_NAME(var_name) > 0)
	{
		str_cmmd = " E";

			 if(set_data.CompareNoCase(CMMD__START) == 0)			str_cmmd += "01";
		else if(set_data.CompareNoCase(CMMD__STOP)  == 0)			str_cmmd += "02";
		else if(set_data.CompareNoCase(CMMD__RESET) == 0)			str_cmmd += "04";
		else
		{
			return -1;
		}

		int r_val = Recv_Command(var_name, str_cmmd, r_data);
		if(r_val < 0)
		{
			return -1;
		}

		return 1;
	}

	return -1;
}

int CObj__STP_SERIAL
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__STP_SERIAL
::Recv_Command(const CString& var_name, const CString& s_cmmd, CString& r_data)
{
	r_data = "";

	// ...
	int cfg_msec = (int) aCH__CFG_MON_INTERVAL->Get__VALUE();
	int n_cnt = 0;
	
	unsigned char send_cmmd[256];
	unsigned char recv_cmmd[256];
	int  data_i;

	// Send_Command ...
	{
		data_i = 0;
		send_cmmd[data_i++] = _STX;
		send_cmmd[data_i++] = '0';
		send_cmmd[data_i++] = '0';
		send_cmmd[data_i++] = '1';
	
		int k_limit = s_cmmd.GetLength();
		for(int k=0; k<k_limit; k++)
		{
			send_cmmd[data_i++] = s_cmmd[k];
		}

		send_cmmd[data_i++] = _ETX;

		// LRC
		send_cmmd[data_i++] = _Get__CheckSum(send_cmmd, data_i);
	}
	// Recv_Command ...
	{
		memset(recv_cmmd, 0, sizeof(char)*255);
	}


	CString err_msg;
	mX_Serial->CLEAR__BUFFER(&err_msg);

	mX_Serial->CHAR__SEND(send_cmmd, data_i);

	do 
	{
		int r_len = 0;

		int r_val = mX_Serial->CHAR__RECV(recv_cmmd, _ETX, &r_len, 500);
		if(r_val >= 0)
		{
			char r_rsp = recv_cmmd[0];
			
			if(r_rsp == _ACK)
			{
				r_data = "";
				for(int i=7; i<r_len; i++)
				{
					r_data += recv_cmmd[i];
				}

				m_nCommState = DRV__ONLINE;

				// SEND > ACK 
				{
					data_i = 0;
					send_cmmd[data_i++] = _ACK;

					mX_Serial->CHAR__SEND(send_cmmd, data_i);
				}
				return 1;
			}
			return -1;
		}

		Sleep(cfg_msec);
	} 
	while(++n_cnt < 2);

	m_nCommState = DRV__ONLINE;

	Sleep(cfg_msec);
	return -1;
}

byte CObj__STP_SERIAL::_Get__CheckSum(const unsigned char* s_cmmd, const int s_len)
{
	byte LRC = 0x00;

	for(int i = 0; i < s_len; i++)
	{
		LRC ^= (byte) s_cmmd[i];
	}
	LRC ^= 0xFF;

	return LRC;
}
