#include "StdAfx.h"
#include "CObj__iTIM_TYPE.h"



//------------------------------------------------------------------------------------
int CObj__iTIM_TYPE
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__iTIM_TYPE
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{
	CString str__read_req_data;
	CString str__for_error;
	CString str__log;
	CString str__analog_data;
	int     index = 0;

	if(diCH__CTRL_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__read_req_data.Format("?C%c",CR);
		str__for_error.Format("?C<CR>");

		str__log.Format("[%s] SEND => [%s]\n", var_name,str__for_error);
		Fnc__DRV_LOG(str__log);

		if((mX_Serial->DATA__RECV(m_Term_Str,&str__read_req_data,m_Rcv_Time)) > 0)
		{
			m_nCommState = ONLINE;

			index = str__read_req_data.GetLength();
			if(index >= 1)
			{
				if(str__read_req_data.GetAt(0) == '0')		read_data = "LOCAL";
				else										read_data = "REMOTE";

				// ...
				{
					str__log.Format("[%s] RECV <= [%s]\n", var_name,str__read_req_data);

					Fnc__DRV_LOG(str__log);
				}
			}
			else
			{
				read_data = "LOCAL";
			}
		}
		else
		{
			m_nCommState = OFFLINE;

			// ...
			{
				str__log.Format("[%s] [Error] => No response Send:(%s) Receive:(%s)\n",
								var_name,
								str__for_error,
								str__read_req_data);

				Fnc__DRV_LOG(str__log);
			}

			read_data = "LOCAL";
		}

		return 1;
	}

	if(diCH__PUMP_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__read_req_data.Format("?P%c",CR);
		str__for_error.Format("?P<CR>");

		str__log.Format("[%s] SEND => [%s]\n", var_name,str__for_error);
		Fnc__DRV_LOG(str__log);

		if((mX_Serial->DATA__RECV(m_Term_Str,&str__read_req_data,m_Rcv_Time)) > 0)
		{
			m_nCommState = ONLINE;

			index = str__read_req_data.GetLength();
			if(index >= 1)
			{
				str__read_req_data.Remove(0x0D);
				str__read_req_data.Remove(0x0A);

				char ch = str__read_req_data.GetAt(0);

					 if(ch == '0')		read_data = "OFF";
				else if(ch == '1')		read_data = "SwitchingOn";
				else if(ch == '2')		read_data = "SwitchingOff";
				else if(ch == '3')		read_data = "SwitchingOff";
				else					read_data = "ON";

				// ...
				{
					str__log.Format("[%s] RECV <= [%s]\n", var_name,str__read_req_data);
					Fnc__DRV_LOG(str__log);
				}
			}
			else
			{
				read_data = "OFF";
			}
		}
		else
		{
			m_nCommState = OFFLINE;

			// ...
			{
				str__log.Format("[%s] [Error] => No response Send:(%s) Receive:(%s)\n",
								var_name,
								str__for_error,
								str__read_req_data);

				Fnc__DRV_LOG(str__log);
			}

			read_data = "OFF";
		}

		return 1;
	}

	if(diCH__COMM_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(iACTIVE_SIM > 0)
		{
			read_data = STR__ONLINE;
		}
		else
		{
			if(m_nCommState == OFFLINE)		read_data = STR__OFFLINE;
			else							read_data = STR__ONLINE;
		}

		return 1;
	}

	return -1;
}

int CObj__iTIM_TYPE
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString str__read_req_data;
	CString str__for_error;
	CString str__log;
	CString str__analog_data;
	int index = 0;

	if((siCH__CMD_ERR->Check__VARIABLE_NAME(var_name) > 0)
	|| (siCH__ELEC_SUPPLY_VOLT->Check__VARIABLE_NAME(var_name) > 0))
	{
		str__read_req_data.Format("?V2%c",CR);
		str__for_error.Format("?V2<CR>");
	}
	else if(siCH__PHASE_CURRENT->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__read_req_data.Format("?V3%c",CR);
		str__for_error.Format("?V3<CR>");
	}
	else if(siCH__PUMP_POWER->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__read_req_data.Format("?V4%c",CR);
		str__for_error.Format("?V4<CR>");
	}
	else if(siCH__VOLT_READ_THERMISTOR->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__read_req_data.Format("?V5%c",CR);
		str__for_error.Format("?V5<CR>");
	}
	else if(siCH__TOTAL_RUN_TIME->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__read_req_data.Format("?V14%c",CR);
		str__for_error.Format("?V14<CR>");
	}
	else if(siCH__TIME_TO_STOP->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__read_req_data.Format("?V21%c",CR);
		str__for_error.Format("?V21<CR>");
	}
	else if(siCH__N2_SUPPLY_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__read_req_data.Format("?V45%c",CR);
		str__for_error.Format("?V45<CR>");
	}
	else if(siCH__MOTOR_TEMP->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__read_req_data.Format("?V55%c",CR);
		str__for_error.Format("?V55<CR>");
	}
	else if(siCH__BODY_TEMP->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__read_req_data.Format("?V57%c",CR);
		str__for_error.Format("?V57<CR>");
	}
	else if(siCH__WATER_FLOW_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__read_req_data.Format("?V60%c",CR);
		str__for_error.Format("?V60<CR>");
	}
	else
	{
		str__log.Format("[%s] SEND => UNKNOWN CHANNEL NAME..\n", var_name);
		Fnc__DRV_LOG(str__log);
		return -1;
	}

	// ...
	{
		str__log.Format("[%s] SEND => [%s]\n", var_name,str__for_error);
		Fnc__DRV_LOG(str__log);

		if((mX_Serial->DATA__RECV(m_Term_Str,&str__read_req_data,m_Rcv_Time)) > 0)
		{
			m_nCommState = ONLINE;
			str__read_req_data.Remove(0x0D);
			str__read_req_data.Remove(0x0A);

			Fnc__DATA_PARSING(var_name, str__read_req_data, read_data);

			str__log.Format("[%s] => Response Send:(%s) Receive:(%s)\n",
							var_name,
							str__for_error,
							str__read_req_data);

			Fnc__DRV_LOG(str__log);
		}
		else
		{
			m_nCommState = OFFLINE;

			// ...
			{
				str__log.Format("[%s] [Error] => No response Send:(%s) Receive:(%s)\n",
								var_name,
								str__for_error,
								str__read_req_data);

				Fnc__DRV_LOG(str__log);
			}

			read_data = "UNKNOWN";
		}

		return 1;
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__iTIM_TYPE
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{

	return 1;
}

int CObj__iTIM_TYPE
::__Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	CString str__send_data;
	CString str__log;
	CString str__for_error;
	int     i__list_data;
	int     index = 0;

	if(var_name.CompareNoCase(doCH__CTRL_MODE->Get__VARIABLE_NAME()) == 0)
	{
		if(set_data.CompareNoCase("LOCAL") == 0)		i__list_data = 0;
		else											i__list_data = 1;

		str__send_data.Format("!C%d%c", i__list_data,CR);
		str__for_error.Format("!C%d<CR>", i__list_data);

		str__log.Format("[%s] SEND => [%s]\n", var_name,str__for_error);
		Fnc__DRV_LOG(str__log);

		if((mX_Serial->DATA__RECV(m_Term_Str,&str__send_data,m_Rcv_Time)) > 0)
		{
			m_nCommState = ONLINE;

			Fnc__DRV_CMD_ERR(var_name, str__send_data);

			index = str__send_data.GetLength();
			if(index >= 5)
			{
				m_str_cmd_err = str__send_data;

				if(str__send_data.GetAt(4) == '0')	// ERR 0
				{
					str__log.Format("[%s] RECV <= [%s]\n", var_name,str__send_data);

					Fnc__DRV_LOG(str__log);
				}
				else
				{
					str__log.Format("[%s][%s] [ERROR] => Problem of Command[%s]\n",
									var_name,
									str__for_error,
									str__send_data);

					Fnc__DRV_LOG(str__log);
				}
			}

			return 1;
		}

		m_nCommState = OFFLINE;

		// ...
		{
			str__log.Format("[%s] [Error] => No response Send:(%s) Receive:(%s)\n",
							var_name, 
							str__for_error,
							str__send_data);

			Fnc__DRV_LOG(str__log);
		}

		return -1;
	}

	if(doCH__RUN_STOP->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase("NONE") == 0) 
		{
			m_nCommState = ONLINE;
			return 1;
		}
		else if(set_data.CompareNoCase("FAST_STOP") == 0)
		{
			i__list_data = 2;
		}
		else if(set_data.CompareNoCase("AUTO_STOP") == 0)
		{
			i__list_data = 0;
		}
		else
		{
			i__list_data = 1;
		}

		str__send_data.Format("!P%d%c", i__list_data,CR);
		str__for_error.Format("!P%d<CR>", i__list_data);

		str__log.Format("[%s] SEND => [%s]\n", var_name,str__for_error);
		Fnc__DRV_LOG(str__log);

		// Rcv:[ERR 0]
		if((mX_Serial->DATA__RECV(m_Term_Str,&str__send_data,m_Rcv_Time)) > 0)
		{
			m_nCommState = ONLINE;
			Fnc__DRV_CMD_ERR(var_name, str__send_data);

			index = str__send_data.GetLength();
			if(index >= 5)
			{
				m_str_cmd_err = str__send_data;

				if(str__send_data.GetAt(4) == '0')
				{
					str__log.Format("[%s] RECV <= [%s]\n", 
									var_name,
									str__send_data);

					Fnc__DRV_LOG(str__log);
				}
				else
				{
					str__log.Format("[%s][%s] [ERROR] => Problem of Command[%s]\n",
									var_name,
									str__for_error,
									str__send_data);

					Fnc__DRV_LOG(str__log);
				}
			}

			return 1;
		}

		m_nCommState = OFFLINE;

		// ...
		{
			str__log.Format("[%s] [Error] => No response Send:(%s) Receive:(%s)\n",
							var_name,
							str__for_error,
							str__send_data);

			Fnc__DRV_LOG(str__log);
		}

		return -1;
	}

	return -1;
}

int CObj__iTIM_TYPE
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}
