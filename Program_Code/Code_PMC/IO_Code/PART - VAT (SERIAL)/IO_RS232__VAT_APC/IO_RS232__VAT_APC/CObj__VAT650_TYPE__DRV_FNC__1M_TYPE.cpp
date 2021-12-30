#include "StdAfx.h"
#include "CObj__VAT650_TYPE.h"



//--------------------------------------------------------------------------------
int CObj__VAT650_TYPE
::_Read__ANALOG_OF_1M_TYPE(const CString& var_name, double& read_data, 
						   const double min, const double max, 
						   const CString& cmmd1,const CString& cmmd2,const CString& cmmd3)
{
	CString send_cmmd;
	CString recv_data;
	CString str__log;

	// ...
	{
	    if(xCH__aiVALVE_POS->Check__VARIABLE_NAME(var_name) > 0)
		{
			send_cmmd.Format("A:");		// Valve Position
		}
		else if(xCH__aiVALVE_PRESS->Check__VARIABLE_NAME(var_name) > 0)
		{
			send_cmmd.Format("P:");		// Actual Cur-Pressure
		}
		else
		{
			str__log.Format("[%s] AI - Unknown Channel Error\n", var_name);
			Fnc__DRV_LOG(str__log);
			return 1;
		}
	}

	// ...
	int fnc_flag = RecvDataProc__1M_TYPE(var_name, send_cmmd, recv_data);

	if(fnc_flag > 0)
	{
		read_data = atof(recv_data);
	}
	return fnc_flag;
}

int CObj__VAT650_TYPE
::_Read__DIGITAL_OF_1M_TYPE(const CString& fnc_name,
							CString& read_data)
{
	// ...
	CString send_cmmd;
	CString recv_data;
	CString str__log;

	int	fnc_flag = DRV__CMD_FAIL;


	// ...
	int n_fnc = atoi(fnc_name);

	if(n_fnc == 400)
	{
		if(m_nCommSts == OFFLINE)	read_data = "OFFLINE";
		else						read_data = "ONLINE";

		return 1;
	}
	else if(n_fnc == 401)
	{
		send_cmmd.Format("i:30");
	}
	else if(n_fnc == 402)
	{
		send_cmmd.Format("i:36");
	}
	else if(n_fnc == 403)
	{
		send_cmmd.Format("i:50");
	}
	else if(n_fnc == 404)
	{
		send_cmmd.Format("i:51");
	}
	else
	{
		// ...
		{
			str__log.Format("[%s] Unknown Channel Error\n", fnc_name);
			Fnc__DRV_LOG(str__log);
		}
		return -1;
	}


	// ...
	{
		fnc_flag = RecvDataProc__1M_TYPE(fnc_name, send_cmmd, recv_data);

		if(fnc_flag > 0)		read_data = recv_data;
		else					read_data = "UNKNOWN";
	}

	return 1;
}

int CObj__VAT650_TYPE
::_Read__STRING_OF_1M_TYPE(const CString& fnc_name,
						   CString& read_data)
{
	return 1;
}



// ...
int CObj__VAT650_TYPE
::_Write__ANALOG_OF_1M_TYPE(const CString& fnc_name, const double set_data)
{
	// ...
	CString str__log;
	CString send_cmmd;
	int fnc_flag;	

	int fnc_id = atoi(fnc_name);


	if(fnc_id == 100)				// Pressure ...
	{
		int trg_pressure = (int) set_data;

		send_cmmd.Format("S:0%07d", trg_pressure);
	}
	else if(fnc_id == 101)			// Position ...
	{
		int trg_position = (int) (set_data * 10.0);

		send_cmmd.Format("R:%06d", trg_position);
	}
	else
	{
		// ...
		{
			str__log.Format("[%s] AO - Unknown Channel Error\n",fnc_name);
			Fnc__DRV_LOG(str__log);
		}
		return 1;
	}


	// ...
	{
		fnc_flag = SendCommand__1M_TYPE(fnc_name, send_cmmd,send_cmmd, m_nTimeout);

		if(fnc_flag < 0)
		{
			str__log.Format("[%s] - Ret : %d\n", fnc_name,fnc_flag);
			Fnc__DRV_LOG(str__log);
		}
	}

	return fnc_flag;
}

int CObj__VAT650_TYPE
::_Write__DIGITAL_OF_1M_TYPE(const CString& fnc_name, 
							 const CString& set_data)
{
	// ...
	CString str__log;
	CString str_cfg_data;
	CString cmmd_keyword;
	CString send_cmmd;

	int fnc_id = atoi(fnc_name);	
	int nCmd_Timeout = m_nTimeout;


	if(fnc_id == 300)
	{
		cmmd_keyword = "c:01";

		if(set_data.CompareNoCase("LOCAL")  == 0)				send_cmmd.Format("%s%s", cmmd_keyword,"00");
		else if(set_data.CompareNoCase("REMOTE") == 0)				send_cmmd.Format("%s%s", cmmd_keyword,"01");
		else														return 1;
	}
	else if(fnc_id == 301)
	{
		if(set_data.CompareNoCase("OPEN")	== 0)				send_cmmd.Format("O:");
		else if(set_data.CompareNoCase("CLOSE")	== 0)				send_cmmd.Format("C:");
		else if(set_data.CompareNoCase("HOLD")	== 0)				send_cmmd.Format("H:");
		else														return 1;

		cmmd_keyword = send_cmmd;
	}
	else if(fnc_id == 302)
	{
		cmmd_keyword = "c:82";

		if(set_data.CompareNoCase("ERRFLAG_RESET")	  == 0)		send_cmmd.Format("%s%s", cmmd_keyword,"00");
		else if(set_data.CompareNoCase("FATAL_ERR_RESET") == 0)		send_cmmd.Format("%s%s", cmmd_keyword,"01");
		else														return 1;
	}
	else if(fnc_id == 303)
	{
		if(set_data.CompareNoCase("ZERO") == 0)						send_cmmd.Format("Z:");
		else														return 1;

		cmmd_keyword = send_cmmd;
	}
	else if(fnc_id == 304)
	{
		cmmd_keyword = "L:";

		if(set_data.CompareNoCase("AUTO_LEARN")	== 0)				send_cmmd.Format("%s%s", cmmd_keyword,"00010000");		// up to sensor full scale
		else														return 1;

		// ...
		{
			aCFG_CH__AUTO_LEARN_CMD_TIMEOUT->Get__DATA(str_cfg_data);
			nCmd_Timeout = atoi(str_cfg_data) * 1000;					// msec이므로..
		}
	}
	else if(fnc_id == 305)
	{
		cmmd_keyword = "i:21";

		if(set_data.CompareNoCase("RANGE_CFG") == 0)				send_cmmd.Format("%s", cmmd_keyword);
		else														return 1;	
	}
	else
	{
		// ...
		{
			str__log.Format("[%s] DO - Unknown Channel Error\n", fnc_name);
			Fnc__DRV_LOG(str__log);
		}
		return 1;
	}


	// ...
	{
		int fnc_flag = SendCommand__1M_TYPE(fnc_name, send_cmmd,cmmd_keyword, nCmd_Timeout);

		if(fnc_flag < 0)
		{
			str__log.Format("[%s], Ret(%d) \n", fnc_name,fnc_flag);
			Fnc__DRV_LOG(str__log);
		}
	}
	return 1;
}

int CObj__VAT650_TYPE
::_Write__STRING_OF_1M_TYPE(const CString& fnc_name, 
							const CString& set_data)
{

	return 1;
}



// ...
// Message Format : [Function][Value][CF][LF]  /  [Function][CR][LF]

int CObj__VAT650_TYPE
::SendCommand__1M_TYPE(const CString& fnc_name, 
					   const CString& send_cmmd,
					   const CString& key_word,
					   const int cmd_timeout)
{
	// ...
	CString	send_data;
	CString str__log;

	int n_counter = 0;
	int fnc_id = atoi(fnc_name);


	do
	{
		// ...
		{
			str__log.Format("[%s] SEND => [%s]", fnc_name,send_cmmd);
			Fnc__DRV_LOG(str__log);
		}

		// ...
		send_data.Format("%s%c%c", send_cmmd, CR,LF);

		if(mX_Serial->DATA__RECV(m_Term_Str, &send_data, cmd_timeout) <= 0)
		{
			// ...
			{
				str__log.Format("[%s] RECV <= [%s] Timeout Retry = %d",
					fnc_name, 
					send_data, 
					n_counter);

				Fnc__DRV_LOG(str__log);
			}

			Sleep(100);
		}
		else
		{
			// ...
			{
				m_sErrorCode.Format("%s", send_data);
				Fnc__DRV_LOG(send_data);

				str__log.Format("[%s] RECV <= [%s]",
					fnc_name, 
					send_data);
				Fnc__DRV_LOG(str__log);
			}
			break;
		}
	} 
	while(++n_counter <= m_nRetryCount);


	if(n_counter > m_nRetryCount)
	{
		m_nCommSts = OFFLINE;

		// ...
		{
			str__log.Format("[%s] OFFLINE", fnc_name);
			Fnc__DRV_LOG(str__log);
		}

		m_sErrorCode.Format("%s", "UNKNOWN");		// Offline 이므로.. UNKNOWN으로 변경.. 
		return DRV__CMD_FAIL;
	}
	else
	{
		m_nCommSts = ONLINE;
	}

	if(send_data.GetLength() <= 0)
	{
		str__log.Format("[%s] Short Data Received...[%s]", fnc_name, send_data);
		Fnc__DRV_LOG(str__log);

		return DRV__CMD_FAIL;
	}


	// DO ...
	if((fnc_id == 300)
		|| (fnc_id == 301)
		|| (fnc_id == 302)
		|| (fnc_id == 303)
		|| (fnc_id == 304))
	{
		// ...
		{
			if(send_data.Find(key_word) >= 0)		return 1;
			else									m_sErrorCode.Format("%s", send_data);
		}
		return 1;
	}
	if(fnc_id == 305)
	{
		if(send_data.Find(key_word) >= 0)
		{
			int cmmd_len = send_cmmd.GetLength();				

			if(send_data.GetLength() >= cmmd_len)
			{
				send_data.Delete(0, cmmd_len);			

				if(send_data.GetLength() >= 8)
				{
					CString str_a;
					CString str_bcdefgh;
					int i;

					//
					str_a = send_data.GetAt(0);

					for(i=0;i<7;i++)
					{
						str_bcdefgh += send_data.GetAt(i+1);
					}

					//
					int pos_range   = atoi(str_a);
					int press_range = atoi(str_bcdefgh);

					if(pos_range == 0)		sCH__CFG_RANGE_POSITION_1M_TYPE->Set__DATA("1000");
					else if(pos_range == 1)		sCH__CFG_RANGE_POSITION_1M_TYPE->Set__DATA("10000");
					else if(pos_range == 2)		sCH__CFG_RANGE_POSITION_1M_TYPE->Set__DATA("100000");

					CString var_data;
					var_data.Format("%1d", press_range);
					sCH__CFG_RANGE_PRESSURE_1M_TYPE->Set__DATA(var_data);
				}				
			}
		}
		return 1;
	}

	// AO ...
	if((fnc_id == 100)
		|| (fnc_id == 101))
	{
		// ...
		{
			if(send_data.Find(key_word) >= 0)		return 1;
			else									m_sErrorCode.Format("%s", send_data);
		}
		return 1;
	}

	return 1;
}


// Recv. Message:  [Function][CF][LF]  /  [Function][Value][CR][LF]

int CObj__VAT650_TYPE
::RecvDataProc__1M_TYPE(const CString& var_name, 
						const CString& send_cmmd, 
						CString& recv_data)
{
	CString	send_data;
	CString str__log;

	int s_counter = 0;

	do
	{
		// ...
		{
			str__log.Format("[%s] SEND ==> [%s]", var_name,send_cmmd);
			Fnc__DRV_LOG(str__log);
		}

		send_data.Format("%s%c%c", send_cmmd,CR,LF);

		if(mX_Serial->DATA__RECV(m_Term_Str, &send_data, m_nTimeout) <= 0)
		{
			// ...
			{
				str__log.Format("[%s] RECV <= [%s] : Timeout [%1d], Cur-Retry/Max-Retry [%1d/%1d],",
								var_name, 
								send_data, 
								m_nTimeout,
								s_counter,
								m_nRetryCount);

				Fnc__DRV_LOG(str__log);
			}

			Sleep(100);
		}
		else
		{
			// ...
			{
				m_sErrorCode.Format("%s", send_data);

				str__log.Format("[%s] RECV <= [%s]", var_name,send_data);
				Fnc__DRV_LOG(str__log);
			}
			break;
		}
	} 
	while(++s_counter <= m_nRetryCount);

	// retry count check
	if(s_counter > m_nRetryCount)
	{
		m_nCommSts = OFFLINE;

		// ...
		{
			str__log.Format("[%s] OFFLINE", var_name);
			Fnc__DRV_LOG(str__log);
		}

		m_sErrorCode.Format("%s", "UNKNOWN");		// Offline 이므로.. UNKNOWN으로 변경..
		return DRV__CMD_FAIL;
	}
	else
	{
		m_nCommSts = ONLINE;
	}

	// [Read Analog]
	if(xCH__aiVALVE_POS->Check__VARIABLE_NAME(var_name) > 0)		// Position ...
	{
		if(send_data.Find(send_cmmd) == 0)
		{
			int cmmd_len = send_cmmd.GetLength();

			if(send_data.GetLength() >= cmmd_len)
			{
				send_data.Delete(0, cmmd_len);			

				double cur_pos = atof(send_data) / 10.0;
				recv_data.Format("%.3f", cur_pos);
			}
		}
		else
		{
			if(send_data.GetAt(0) == 'E')
			{
				// ...
				{
					str__log.Format("[%s] Error Received...[%s]", var_name,send_data);
					Fnc__DRV_LOG(str__log);
				}

				// ...
				{
					CString str_data = send_data;
					CString err_code = send_data;

					if(str_data.Find("E:") == 0)
					{
						str_data.Delete(0,2);

						int err_id = atoi(str_data);
						mRes__ERR_DB.Load__ERR_ID(err_id,err_code);
					}
				}
			}
			else
			{
				// Recv Data Error !

			}
		}
	}
	else if(xCH__aiVALVE_PRESS->Check__VARIABLE_NAME(var_name) > 0)		// Pressure ...
	{
		if(send_data.Find(send_cmmd) == 0)
		{
			int cmmd_len = send_cmmd.GetLength();

			if(send_data.GetLength() >= cmmd_len)
			{
				send_data.Delete(0, cmmd_len);			

				double cur_press = atof(send_data) / 10.0;
				recv_data.Format("%.3f", cur_press);
			}
		}
		else
		{
			if(send_data.GetAt(0) == 'E')
			{
				// ...
				{
					str__log.Format("[%s] Error Received... [%s]", var_name,send_data);
					Fnc__DRV_LOG(str__log);
				}

				// ...
				{
					CString str_data = send_data;
					CString err_code = send_data;

					if(str_data.Find("E:") == 0)
					{
						str_data.Delete(0,2);

						int err_id = atoi(str_data);
						mRes__ERR_DB.Load__ERR_ID(err_id,err_code);
					}
				}
			}
			else
			{
				// Recv Data Error !

			}
		}
	}

	// [Read Digital]
	// Valve Status, Ctrl Mode ...
	else if(xCH_diOPER_MODE->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(send_data.Find(send_cmmd) == 0)
		{
			int cmmd_len = send_cmmd.GetLength();

			if(send_data.GetLength() >= cmmd_len)
			{
				send_data.Delete(0, cmmd_len);			

				if(send_data.GetLength() >= 8)
				{
					char str_a[2];
					str_a[0] = send_data.GetAt(0);
					str_a[1] = 0;

					int a_data = atoi(str_a);

						 if(a_data == 0)		recv_data = "LOCAL";
					else if(a_data == 1)		recv_data = "REMOTE";
					else if(a_data == 2)		recv_data = "LOCKED";
					else						recv_data = "UNKNOWN";		
				}
				else
				{
					recv_data = "UNKNOWN";		
				}
			}
			else
			{
				// Recv Data Error !

			}
		}
		else
		{
			// Recv Data Error !

		}
	}
	else if(xCH_diCTRL_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(send_data.Find(send_cmmd) == 0)
		{
			int cmmd_len = send_cmmd.GetLength();

			if(send_data.GetLength() >= cmmd_len)
			{
				send_data.Delete(0, cmmd_len);			

				if(send_data.GetLength() >= 8)
				{
					char str_a[2];
					str_a[0] = send_data.GetAt(0);
					str_a[1] = 0;
					
					int a_data = atoi(str_a);

						 if(a_data == 0)							recv_data = "POSITION";
					else if((a_data == 1) || (a_data == 2))			recv_data = "PRESSURE";
					else											recv_data = "UNKNOWN";
				}
				else
				{
					recv_data = "UNKNOWN";
				}
			}
			else
			{
				// Recv Data Error !

			}
		}
		else
		{
			// Recv Data Error !

		}
	}
	else if((xCH_diCOMM_ERROR__1K_TYPE->Check__VARIABLE_NAME(var_name) > 0)
		 || (xCH_diCOMM_ERROR__1M_TYPE->Check__VARIABLE_NAME(var_name) > 0))
	{
		int check_flag = -1;

		if(send_data.Find(send_cmmd) == 0)
		{
			int cmmd_len = send_cmmd.GetLength();

			if(send_data.GetLength() >= cmmd_len)
			{
				send_data.Delete(0, cmmd_len);			

				check_flag = 1;
				sCH__ERROR_CODE_1M_TYPE->Set__DATA(send_data);

				if(send_data.GetLength() >= 3)
				{					
					int abc_data = atoi(send_data);

					if(abc_data == 0)		recv_data = "NOERR";
					else					recv_data = "ERROR";
				}
				else
				{
					recv_data = "UNKNOWN";
				}
			}
			else
			{
				recv_data = "UNKNOWN";
			}
		}
		else
		{
			recv_data = "UNKNOWN";
		}

		if(check_flag < 0)
		{
			sCH__ERROR_CODE_1M_TYPE->Set__DATA(send_data);
		}
	}
	else if(xCH_diPOSITION_ERROR->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(send_data.Find(send_cmmd) == 0)
		{
			int cmmd_len = send_cmmd.GetLength();

			if(send_data.GetLength() >= cmmd_len)
			{
				send_data.Delete(0, cmmd_len);			

				if(send_data.GetLength() >= 8)
				{
					char str_a[2];
					char str_b[2];
					char str_c[2];
					char str_d[2];

					str_a[0] = send_data.GetAt(0);
					str_a[1] = 0;
					
					str_b[0] = send_data.GetAt(1);
					str_b[1] = 0;
					
					str_c[0] = send_data.GetAt(2);
					str_c[1] = 0;
					
					str_d[0] = send_data.GetAt(3);
					str_d[1] = 0;

					int a_data = atoi(str_a);
					int b_data = atoi(str_b);
					int c_data = atoi(str_c);
					int d_data = atoi(str_d);

					if((a_data == 0)					
					&& (b_data == 0)					
					&& (c_data == 0)					
					&& (d_data == 0))
					{
						recv_data = "OK";
					}
					else if(a_data == 1)			recv_data = "POS_ERR";						
					else if(b_data == 1)			recv_data = "LEARN_DATA_NOT_EXIST";
					else if(c_data == 1)			recv_data = "POWER_ERR";
					else if(d_data == 1)			recv_data = "AIR_ERR";
					else							recv_data = "UNKNOWN";
				}
				else
				{
					recv_data = "UNKNOWN";
				}
			}
			else
			{
				// Recv Data Error !

			}
		}
		else
		{
			// Recv Data Error !

		}
	}

	return 1;
}
