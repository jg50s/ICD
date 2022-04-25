#include "StdAfx.h"
#include "CObj__PIRANI_SERIAL.h"

#include "CClass_Crc16.h"


union UNION_4_BYTE__FLOAT
{
	float fDATA;
	unsigned long uiDATA;
	char  cBYTE[4];
};


//------------------------------------------------------------------------------------
int CObj__PIRANI_SERIAL
::__Read__ANALOG(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 double& read_data)
{

	return -1;
}

int CObj__PIRANI_SERIAL
::__Read__DIGITAL(const CString& var_name,
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  CString& read_data,
				  int& item_index)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg  = "__Read__DIGITAL()";
		log_msg += "\n";

		log_bff.Format(" * %s", var_name); 
		log_msg += log_bff;

		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	// ...'
	unsigned char s_packet[100];
	unsigned char s_len = 0;

	unsigned char r_packet[100];
	unsigned char r_size = 100;
	unsigned char r_ref = 0;

	if(diCH__PRESSURE_GET->Check__VARIABLE_NAME(var_name) > 0)
	{
		r_ref = 15;
		s_len = 0;

		s_packet[s_len++] = 0x0ff & iADDRESS_ID;
		s_packet[s_len++] = 0x00;					// DEVICE ID
		s_packet[s_len++] = 0x00;					// ACK
		s_packet[s_len++] = 0x05;					// MSG Length
		s_packet[s_len++] = 0x01;					// CMD
		s_packet[s_len++] = 0x00;					// PID
		s_packet[s_len++] = 0xDE;					
		s_packet[s_len++] = 0x00;					// RESERVE
		s_packet[s_len++] = 0x00;					

		Crc16 x_crc;
		unsigned short crc_result = x_crc.Create(s_packet, s_len);

		s_packet[s_len++] = 0x0ff & (crc_result);
		s_packet[s_len++] = 0x0ff & (crc_result >> 8);
	}

	int r_ret = _Recv_Command(s_packet,s_len, r_packet,r_size, r_ref);
	if(r_ret < 0)		return -11;

	if(diCH__PRESSURE_GET->Check__VARIABLE_NAME(var_name) > 0)
	{
		unsigned char r_ack = r_packet[2];
		if(r_ack != 0x01)		return -1;

		UNION_4_BYTE__FLOAT packet_data;
		CString ch_data;

		packet_data.cBYTE[3] = 0x0ff & r_packet[9];
		packet_data.cBYTE[2] = 0x0ff & r_packet[10];
		packet_data.cBYTE[1] = 0x0ff & r_packet[11];
		packet_data.cBYTE[0] = 0x0ff & r_packet[12];

		float cur__press_value = packet_data.fDATA;
		float cur__press_torr = 0.0;

		if(iSTATE__PRESSURE_TYPE == _PRESSURE_TYPE__MBAR)
		{
			cur__press_torr = cur__press_value * (760.0 / 1013.25);
		}
		else if(iSTATE__PRESSURE_TYPE == _PRESSURE_TYPE__TORR)
		{
			cur__press_torr = cur__press_value;
		}
		else
		{
			Fnc__DRV_LOG_OF_MSG("PRESSURE.TYPE ERROR !");

			cur__press_torr = 300.0;
		}

		ch_data.Format("%.3f", cur__press_value);
		sCH__MON_PRESSURE_VALUE->Set__DATA(ch_data);

		ch_data.Format("%.3f", cur__press_torr);
		sCH__MON_PRESSURE_TORR->Set__DATA(ch_data);
		return 1;
	}

	return -1;
}

int CObj__PIRANI_SERIAL
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

	// ...'
	unsigned char s_packet[100];
	unsigned char s_len = 0;

	unsigned char r_packet[100];
	unsigned char r_size = 100;
	unsigned char r_ref = 0;

	if(siCH__PRESSURE_TYPE->Check__VARIABLE_NAME(var_name) > 0)
	{
		r_ref = 12;
		s_len = 0;

		s_packet[s_len++] = 0x0ff & iADDRESS_ID;
		s_packet[s_len++] = 0x00;					// DEVICE ID
		s_packet[s_len++] = 0x00;					// ACK
		s_packet[s_len++] = 0x05;					// MSG Length
		s_packet[s_len++] = 0x01;					// CMD

		s_packet[s_len++] = 0x00;					// PID
		s_packet[s_len++] = 0xE0;					

		s_packet[s_len++] = 0x00;					// RESERVE
		s_packet[s_len++] = 0x00;					

		Crc16 x_crc;
		unsigned short crc_result = x_crc.Create(s_packet, s_len);

		s_packet[s_len++] = 0x0ff & (crc_result);
		s_packet[s_len++] = 0x0ff & (crc_result >> 8);
	}

	int r_ret = _Recv_Command(s_packet,s_len, r_packet,r_size, r_ref);
	if(r_ret < 0)
	{
		read_data = "ERROR.2";
		return -11;
	}

	if(siCH__PRESSURE_TYPE->Check__VARIABLE_NAME(var_name) > 0)
	{
		unsigned char r_ack = r_packet[2];
		if(r_ack != 0x01)
		{
			read_data = "ERROR.1";
			return -1;
		}

		unsigned char cur_type = 0x0ff & r_packet[9];

		if(cur_type == 0x00)
		{
			sCH__MON_PRESSURE_TYPE->Set__DATA(STR__mbar);
		}
		else if(cur_type == 0x01)
		{
			sCH__MON_PRESSURE_TYPE->Set__DATA(STR__torr);
		}
		else 
		{
			sCH__MON_PRESSURE_TYPE->Set__DATA("??");
		}

		read_data.Format("%02X", cur_type);
		return 1;
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__PIRANI_SERIAL
::__Write__ANALOG(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const double set_data)
{

	return -1;
}

int CObj__PIRANI_SERIAL
::__Write__DIGITAL(const CString& var_name,
				   const CDS_IO__CHANNEL_INFO& io_info, 
				   const CString& set_data,
				   const int item_index)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg  = "__Read__DIGITAL()";
		log_msg += "\n";

		log_bff.Format(" * %s", var_name); 
		log_msg += log_bff;

		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	// ...'
	unsigned char s_packet[100];
	unsigned char s_len = 0;

	unsigned char r_packet[100];
	unsigned char r_size = 100;
	unsigned char r_ref = 0;

	if(doCH__PRESSURE_TYPE->Check__VARIABLE_NAME(var_name) > 0)
	{
		unsigned char set_type = 0x00;

			 if(set_data.CompareNoCase("mbar") == 0)			set_type = 0x00;
		else if(set_data.CompareNoCase("torr") == 0)			set_type = 0x01;

		r_ref = 11;
		s_len = 0;

		s_packet[s_len++] = 0x0ff & iADDRESS_ID;
		s_packet[s_len++] = 0x00;					// DEVICE ID
		s_packet[s_len++] = 0x00;					// ACK
		s_packet[s_len++] = 0x06;					// MSG Length

		s_packet[s_len++] = 0x03;					// CMD
		
		s_packet[s_len++] = 0x00;					// PID
		s_packet[s_len++] = 0xE0;					
		
		s_packet[s_len++] = 0x00;					// RESERVE
		s_packet[s_len++] = 0x00;					

		s_packet[s_len++] = 0x0ff & set_type;		// DATA

		Crc16 x_crc;
		unsigned short crc_result = x_crc.Create(s_packet, s_len);

		s_packet[s_len++] = 0x0ff & (crc_result);
		s_packet[s_len++] = 0x0ff & (crc_result >> 8);
	}

	int r_ret = _Recv_Command(s_packet,s_len, r_packet,r_size, r_ref);
	if(r_ret < 0)		return -11;

	if(doCH__PRESSURE_TYPE->Check__VARIABLE_NAME(var_name) > 0)
	{
		return 1;
	}

	return -1;
}

int CObj__PIRANI_SERIAL
::__Write__STRING(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const CString& set_data)
{

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__PIRANI_SERIAL::
_Recv_Command(unsigned char* s_packet, 
			  const unsigned char s_len, 
			  unsigned char* r_packet,
			  const unsigned char r_size,
			  const unsigned char r_ref)
{
	CString log_msg;
	CString log_bff;

	int n_counter = 0;
	int i;

	while(1)
	{
		// ...
		{
			log_msg = "Send >> \n";

			for(i=0; i<s_len; i++)
			{
				log_bff.Format(" %02X", s_packet[i]);
				log_msg += log_bff;
			}

			Fnc__DRV_LOG_OF_MSG(log_msg);
		}

		// ...
		int r_len = r_ref;

		memset(r_packet, 0, r_size);

		// ...
		{
			CString str_log;
			mX_Serial->CLEAR__BUFFER(&str_log);
		}

		mX_Serial->CHAR__SEND(s_packet, s_len);		
		int r_flag = mX_Serial->OnlyRecv__CHAR(r_packet, &r_len, m_Rcv_Time);

		if(iActive__SIM_MODE > 0)
		{
			int i_cnt = 0;

			r_packet[i_cnt] = s_packet[i_cnt];
			i_cnt++;
			r_packet[i_cnt] = 0x02;
			i_cnt++;
			r_packet[i_cnt] = 0x01;
			i_cnt++;
			r_packet[i_cnt] = 0x09;
			i_cnt++;
			r_packet[i_cnt] = s_packet[i_cnt] + 0x01;
			i_cnt++;
			r_packet[i_cnt] = s_packet[i_cnt];
			i_cnt++;
			r_packet[i_cnt] = s_packet[i_cnt];
			i_cnt++;
			r_packet[i_cnt] = s_packet[i_cnt];
			i_cnt++;
			r_packet[i_cnt] = s_packet[i_cnt];
			i_cnt++;

			r_packet[i_cnt] = 0x4E;
			i_cnt++;
			r_packet[i_cnt] = 0x7E;
			i_cnt++;
			r_packet[i_cnt] = 0x18;
			i_cnt++;
			r_packet[i_cnt] = 0xAC;
			i_cnt++;

			r_packet[i_cnt] = 0x00;
			i_cnt++;
			r_packet[i_cnt] = 0x00;
			i_cnt++;

			r_len = i_cnt;
		}

		if(r_flag > 0)
		{
			log_msg.Format("Recv (%1d) << \n", r_len);

			for(i=0; i<r_len; i++)
			{
				log_bff.Format(" %02X", r_packet[i]);
				log_msg += log_bff;
			}

			Fnc__DRV_LOG_OF_MSG(log_msg);
		}

		if(r_len == r_ref)
		{
			iCOMM_STATE = _DEF__ONLINE;
			return r_len;
		}

		++n_counter;
		if(n_counter > m_nRetryCnt)
		{
			break;
		}

		Sleep(100);

		// ...
		{
			log_msg.Format(" Send_Retry (%1d) \n", n_counter);
			log_bff.Format("  * Ref_Retry : %1d \n", m_nRetryCnt);
			log_msg += log_bff;

			Fnc__DRV_LOG_OF_MSG(log_msg);
		}
	}

	// ...
	{
		log_msg.Format("Recv Error ! \n");

		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	iCOMM_STATE = _DEF__OFFLINE;
	return -1;
}
