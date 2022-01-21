#include "StdAfx.h"
#include "CObj__901P_SERIAL.h"

/*
@<dev_addr><query>?:FF
@<dev_addr><command>!<para>:FF
*/

//------------------------------------------------------------------------------------
int CObj__901P_SERIAL
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

int CObj__901P_SERIAL
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
	CString cmmd_byte = "";

	if(diCH__PRESSURE_GET->Check__VARIABLE_NAME(var_name) > 0)
	{
		cmmd_byte = "PR3?";
	}

	if(cmmd_byte == "")
	{
		log_msg = " * Variable Error !";

		Fnc__DRV_LOG_OF_MSG(log_msg);		
		return -1;
	}

	// ...
	CString r_data = "";

	int r_ret = _Recv_Command(cmmd_byte, r_data);
	if(r_ret < 0)		return -1;

	// ...
	if(diCH__PRESSURE_GET->Check__VARIABLE_NAME(var_name) > 0)
	{
		sCH__DATA_PRESSURE_TORR->Set__DATA(r_data);
		return 1;
	}

	return -1;
}

int CObj__901P_SERIAL
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
int CObj__901P_SERIAL
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

int CObj__901P_SERIAL
::__Write__DIGITAL(const CString& fnc_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{

	return -1;
}

int CObj__901P_SERIAL
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__901P_SERIAL::
_Recv_Command(const CString& cmmd_byte,
			  CString& recv_data)
{
	CString dev_id = "253";

	CString s_data;
	s_data.Format("@%s%s", dev_id,cmmd_byte);
	s_data += sEnd_Str;

	// ...
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg = "_Recv_Command() ... \n";

		log_bff.Format(" * cmmd_byte <- [%s] \n", cmmd_byte);
		log_msg += log_bff;
		
		log_bff.Format(" * s_data <- [%s] \n", s_data);
		log_msg += log_bff;

		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	// ...
	int check_flag = 1;
	int n_counter  = 0;

	do
	{
		// ...
		{
			CString str_log;
			mX_Serial->CLEAR__BUFFER(&str_log);
		}

		CString r_data = "";

		int s_ret   = mX_Serial->DATA__SEND(s_data);
		int r_count = mX_Serial->OnlyRecv__DATA(sEnd_Str, &r_data,m_Rcv_Time);

		// ...
		{
			log_msg = "OnlyRecv__CHAR() ...\n";

			log_bff.Format(" * r_count <- %1d \n", r_count);
			log_msg += log_bff;

			if(r_count > 0)
			{
				log_bff.Format(" * r_data <- [%s] \n", r_data);
				log_msg += log_bff;
			}

			Fnc__DRV_LOG_OF_MSG(log_msg);
		}

		int s_index = r_data.Find("ACK");
		if(s_index == 4)
		{
			r_data.Delete(0,7);
			recv_data = r_data;

			iCOMM_STATE = _DEF__ONLINE;
			return 1;
		}

		Sleep(100);
	}
	while(++n_counter < m_nRetryCnt);

	iCOMM_STATE = _DEF__OFFLINE;
	return -1;
}
