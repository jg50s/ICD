#include "StdAfx.h"
#include "CObj__VAT650_TYPE.h"



//--------------------------------------------------------------------------------
int CObj__VAT650_TYPE
::_Read__ANALOG_OF_1K_TYPE(const CString& var_name, double& read_data, 
						   const double min, const double max, 
						   const CString& cmmd1,const CString& cmmd2,const CString& cmmd3)
{
	CString tmpStr;
	CString szRcvData;
	CString str__log;

	int	nReturn = DRV__CMD_FAIL;

	if(xCH__aiVALVE_POS->Check__VARIABLE_NAME(var_name) > 0)
	{
		tmpStr = "A:";		// ... Valve Position  !!
	}
	else if(xCH__aiVALVE_PRESS->Check__VARIABLE_NAME(var_name) > 0)
	{
		tmpStr = "P:";		// ... Actual Pressure !!
	}
	else
	{
		str__log.Format("[%s] AI - Unknown Channel Error\n", var_name);
		Fnc__DRV_LOG(str__log);

		nReturn = 1;
		return nReturn;
	}

	// ...
	{
		nReturn = RecvDataProc__1K_TYPE(var_name, tmpStr, szRcvData);
		if(nReturn > 0)		read_data = atof(szRcvData);
	}
	return nReturn;
}

int CObj__VAT650_TYPE
::_Read__DIGITAL_OF_1K_TYPE(const CString& var_name,
							CString& read_data)
{
	CString tmpStr;
	CString szRcvData;
	CString str__log;

	int nErrCase;

	if(xCH_diCOMM_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(m_nCommSts == OFFLINE)	read_data = "OFFLINE";
		else						read_data = "ONLINE";

		return 1;
	}
	else if(xCH_diOPER_MODE->Check__VARIABLE_NAME(var_name) > 0)
	{
		tmpStr.Format("I:");
	}
	else if(xCH_diCTRL_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		tmpStr.Format("M:");
	}
	else if((xCH_diCOMM_ERROR__1K_TYPE->Check__VARIABLE_NAME(var_name) > 0)
		 || (xCH_diCOMM_ERROR__1M_TYPE->Check__VARIABLE_NAME(var_name) > 0))
	{
		nErrCase = ComErrorCheck__1K_TYPE(m_sErrorCode);

		switch(nErrCase)
		{
			case 0:		read_data.Format("NOERR");				break;
			case 1:		read_data.Format("PARITYERR");			break;
			case 2:		read_data.Format("CRLFERR");			break;
			case 3:		read_data.Format("SYNERR");				break;
			case 4:		read_data.Format("WRONGLETTER");		break;
			case 5:		read_data.Format("VALNOT6DIGIT");		break;
			case 6:		read_data.Format("VALOVER1000");		break;
			case 7:		read_data.Format("SNSNOCONNECTED");		break;
			case 8:		read_data.Format("LOCALERR");			break;
			case 9:		read_data.Format("INPUTACTIVE");		break;
			case 10:	read_data.Format("ERRLEARN");			break;
			case 11:	read_data.Format("ERRZERO");			break;

			default:	read_data.Format("UNKNOWN");			break;
		}

		return 1;
	}
	else if(xCH_diPOSITION_ERROR->Check__VARIABLE_NAME(var_name) > 0)
	{
		tmpStr.Format("p:");
	}
	else
	{
		str__log.Format("[%s] Unknown Channel Error\n", var_name);
		Fnc__DRV_LOG(str__log);

		return 1;
	}

	// ...
	{
		int nReturn = RecvDataProc__1K_TYPE(var_name, tmpStr, szRcvData);

		if(nReturn > 0)		read_data = szRcvData;
		else				read_data = "UNKNOWN";
	}
	return 1;
}

int CObj__VAT650_TYPE
::_Read__STRING_OF_1K_TYPE(const CString& var_name,
						   CString& read_data)
{
	return 1;
}

int CObj__VAT650_TYPE
::_Write__ANALOG_OF_1K_TYPE(const CString& var_name, 
							const double set_data)
{
	CString tmpStr;
	CString str__log;
	CString str_set_data;

	int	nSetPressure = 0;
	int	nSetPosition = 0;

	// Pressure ...
	if(xCH__aoSET_PRESSURE->Check__VARIABLE_NAME(var_name) > 0)
	{
		nSetPressure = (int)(set_data);					// Sensor
		tmpStr.Format("S:00%04d", nSetPressure);
	}
	// Position ...
	else if(xCH__aoSET_POSITION->Check__VARIABLE_NAME(var_name) > 0)
	{
		nSetPosition = (int) (set_data);

		tmpStr.Format("R:%06d", nSetPosition);
	}
	else
	{
		str__log.Format("[%s] AO - Unknown Channel Error\n", var_name);
		Fnc__DRV_LOG(str__log);
		return 1;
	}

	// ...
	str_set_data.Format("%f", set_data);

	int	nReturn = SendCommand__1K_TYPE(var_name, tmpStr, str_set_data, m_nTimeout);
	if(nReturn < 0)
	{
		str__log.Format("[%s], Ret : %d\n", var_name, nReturn);
		Fnc__DRV_LOG(str__log);
	}
	return nReturn;
}

int CObj__VAT650_TYPE
::_Write__DIGITAL_OF_1K_TYPE(const CString& var_name, 
							 const CString& set_data)
{
	CString tmpStr;
	CString str__log;

	int nCmd_Timeout = m_nTimeout;

	if(xCH_doOPER_MODE->Check__VARIABLE_NAME(var_name) > 0)
	{
			 if(set_data.CompareNoCase("LOCAL")  == 0)			tmpStr.Format("U:02");
		else if(set_data.CompareNoCase("REMOTE") == 0)			tmpStr.Format("U:01");
		else													return 1;
	}
	else if(xCH__doVALVE_OPR_CMD->Check__VARIABLE_NAME(var_name) > 0)
	{
			 if(set_data.CompareNoCase("OPEN")		== 0)		tmpStr.Format("O:");
		else if(set_data.CompareNoCase("CLOSE")		== 0)		tmpStr.Format("C:");
		else if(set_data.CompareNoCase("HOLD")		== 0)		tmpStr.Format("H:");
		else													return 1;
	}
	else if(xCH_doRESET_CMD->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase("ERRFLAG_RESET")	== 0)		tmpStr.Format("f:");
		else													return 1;
	}
	else if(xCH_doZERO_CMD->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase("ZERO")	== 0)				tmpStr.Format("Z:");
		else													return 1;
	}
	else if(xCH_doAUTO_LEARN_CMD->Check__VARIABLE_NAME(var_name) > 0)
	{
		// Timeout을 따로 넣을것.. Auto Learning 하는데 시간이 많이 걸리므로...
		if(set_data.CompareNoCase("AUTO_LEARN")	== 0)			tmpStr.Format("L:001000");	// up to sensor full scale
		else													return 1;

		// ...
		CString str_cfg_data;
		aCFG_CH__AUTO_LEARN_CMD_TIMEOUT->Get__DATA(str_cfg_data);

		nCmd_Timeout = atoi(str_cfg_data)*1000;		// msec이므로..
	}
	else
	{
		str__log.Format("[%s] DO - Unknown Channel Error\n", var_name);

		Fnc__DRV_LOG(str__log);
		return 1;
	}

	// ...
	int nReturn = SendCommand__1K_TYPE(var_name, tmpStr, set_data, nCmd_Timeout);
	if(nReturn < 0)
	{
		str__log.Format("[%s], Ret : %d\n", var_name, nReturn);
		Fnc__DRV_LOG(str__log);
	}
	
	return nReturn;
}

int CObj__VAT650_TYPE
::_Write__STRING_OF_1K_TYPE(const CString& fnc_name, 
							const CString& set_data)
{

	return 1;
}



// ...
// Message Format : [Function][Value][CF][LF]  /  [Function][CR][LF]

int CObj__VAT650_TYPE
::SendCommand__1K_TYPE(const CString& var_name, 
					   CString szMsg, 
					   const CString& set_data, 
					   const int cmd_timeout)
{
	CString	send_data;
	CString str__log;
	
	int nCounter = 0;

	do
	{
		// ...
		{
			str__log.Format("[%s] SEND => [%s]", var_name, szMsg);
			Fnc__DRV_LOG(str__log);
		}

		send_data.Format("%s%c%c",szMsg, CR, LF);

		if(mX_Serial->DATA__RECV(m_Term_Str, &send_data, cmd_timeout) <= 0)
		{
			// ...
			{
				str__log.Format("[%s] RECV <= [%s] Timeout Retry = %d", var_name,send_data,nCounter);
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

				str__log.Format("[%s] RECV <= [%s]", var_name,send_data);
				Fnc__DRV_LOG(str__log);
			}
			break;
		}
	} 
	while(++nCounter <= m_nRetryCount);

	// 3. retry count check
	if(nCounter > m_nRetryCount)
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

	if(send_data.GetLength() <= 0)
	{
		str__log.Format("[%s] Short Data Received...[%s]", var_name, send_data);
		Fnc__DRV_LOG(str__log);

		return DRV__CMD_FAIL;
	}

	// DO ...
	if(xCH_doOPER_MODE->Check__VARIABLE_NAME(var_name) > 0)
	{
		if((set_data.CompareNoCase("REMOTE") == 0) 
		|| (set_data.CompareNoCase("LOCAL")  == 0))
		{
			if(send_data.Find("U:") >=0)		return 1;
			else								m_sErrorCode.Format("%s", send_data);
		}
	}
	else if(xCH__doVALVE_OPR_CMD->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase("OPEN") == 0)
		{
			if(send_data.Find("O:") >=0)		return 1;
			else								m_sErrorCode.Format("%s", send_data);
		}
		else if(set_data.CompareNoCase("CLOSE")	== 0)
		{
			if(send_data.Find("C:") >=0)		return 1;
			else								m_sErrorCode.Format("%s", send_data);
		}
		else if(set_data.CompareNoCase("HOLD") == 0)
		{
			if(send_data.Find("H:") >=0)		return 1;
			else								m_sErrorCode.Format("%s", send_data);
		}
		else
		{
			return 1;
		}
	}
	else if(xCH_doRESET_CMD->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase("ERRFLAG_RESET")	== 0)
		{
			if(send_data.Find("f:") >=0)		return 1;
			else								m_sErrorCode.Format("%s", send_data);
		}
		else
		{
			return 1;
		}
	}
	else if(xCH_doZERO_CMD->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase("ZERO")	== 0)
		{
			if(send_data.Find("f:") >=0)		return 1;
			else								m_sErrorCode.Format("%s", send_data);
		}
		else
		{
			return 1;
		}
	}

	// AO ...
	if(xCH__aoSET_PRESSURE->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(send_data.Find("S:") >=0)			return 1;
		else									m_sErrorCode.Format("%s", send_data);
	}
	else if(xCH__aoSET_POSITION->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(send_data.Find("R:") >=0)			return 1;
		else									m_sErrorCode.Format("%s", send_data);
	}

	return 1;
}


// Recv. Message:  [Function][CF][LF]  /  [Function][Value][CR][LF]

int CObj__VAT650_TYPE
::RecvDataProc__1K_TYPE(const CString& var_name, CString szMsg, CString& szRcvData)
{
	CString	send_data;
	CString str__log;
	int nCounter = 0;

	do
	{
		// ...
		{
			str__log.Format("[%s] SEND ==> [%s]", var_name, szMsg);
			Fnc__DRV_LOG(str__log);
		}

		send_data.Format("%s%c%c",szMsg, CR, LF);
		if(mX_Serial->DATA__RECV(m_Term_Str, &send_data, m_nTimeout) <= 0)
		{
			str__log.Format("[%s] RECV <= [%s] Timeout Retry = %d",
							var_name, 
							send_data, 
							nCounter);
			Fnc__DRV_LOG(str__log);

			Sleep(100);
		}
		else
		{
			m_sErrorCode.Format("%s", send_data);

			str__log.Format("[%s] RECV <= [%s]", var_name,send_data);
			Fnc__DRV_LOG(str__log);
			break;
		}
	} 
	while(++nCounter <= m_nRetryCount);


	// retry count check
	if(nCounter > m_nRetryCount)
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

	// Position, Pressure
	if(xCH__aiVALVE_POS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(send_data.GetAt(0) == 'E')
		{
			szRcvData = "999.999";			// Error

			// ...
			{
				str__log.Format("[%s] Error Received...[%s]", var_name, send_data);
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
			if(send_data.GetLength() >= 2)
			{
				send_data.Delete(0, 2);		// remove "A:"

				szRcvData = send_data;
			}
		}
	}
	else if(xCH__aiVALVE_PRESS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(send_data.GetAt(0) == 'E')
		{
			szRcvData = "999.999";			// Error

			// ...
			{
				str__log.Format("[%s] Error Received...[%s]", var_name, send_data);
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
			// P:-00001 이것은 -1 mTorr 이다.
			send_data.Delete(0, 2);		// remove "P:"
			szRcvData = send_data;
		}
	}

	// [Read Digital]
	// Valve Status, Ctrl Mode ...
	else if(xCH_diOPER_MODE->Check__VARIABLE_NAME(var_name) > 0)
	{
		     if(send_data.Find("LOCAL")  >=0)		szRcvData = "LOCAL";
		else if(send_data.Find("REMOTE") >=0)		szRcvData = "REMOTE";
		else if(send_data.Find("LOCKED") >=0)		szRcvData = "LOCKED";
		else										szRcvData = "UNKNOWN";		
	}
	else if(xCH_diCTRL_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
			 if(send_data.Find("POS")   >=0)		szRcvData = "POSITION";
		else if(send_data.Find("PRESS") >=0)		szRcvData = "PRESSURE";
		else										szRcvData = "UNKNOWN";
	}
	else if(xCH_diPOSITION_ERROR->Check__VARIABLE_NAME(var_name) > 0)
	{
			 if(send_data.Find("OK")      >=0)		szRcvData = "OK";
		else if(send_data.Find("POS_ERR") >=0)		szRcvData = "POS_ERR";
		else if(send_data.Find("AIR-ER")  >=0)		szRcvData = "AIR_ERR";
		else										szRcvData = "UNKNOWN";
	}

	return 1;
}

int CObj__VAT650_TYPE
::ComErrorCheck__1K_TYPE(const CString& err_code)
{
	int result = 0;

	if(err_code.CompareNoCase("UNKNOWN") == 0)
	{
		result = 999;	// UNKNOWN
		return result;
	}

	if(err_code.GetLength() < 7)
	{
		result = 0;
		return result;
	}
	if(err_code.GetAt(0) == 'E')
	{	
		     if(err_code.Find("001") != -1)		{ result =  1; }	// Parity Error		
		else if(err_code.Find("002") != -1)		{ result =  2; }	// <cr><lf> is missing)
		else if(err_code.Find("003") != -1)		{ result =  3; }	// : is missing
		else if(err_code.Find("004") != -1)		{ result =  4; }	// Wrong letter code
		else if(err_code.Find("005") != -1)		{ result =  5; }	// Numerical value not given in 6 digits
		else if(err_code.Find("006") != -1)		{ result =  6; }	// Numerical value larger 1000
		else if(err_code.Find("007") != -1)		{ result =  7; }	// PRESSURE MODE, ZERO or LEARN have been selected with no sensor connected (display format set for no sensor)
		else if(err_code.Find("008") != -1)		{ result =  8; }	// Instruction given in operating mode LOCAL
		else if(err_code.Find("009") != -1)		{ result =  9; }	// RS232 commands Z:, L:XXXXXX or J: given while a logic input is activated
		else if(err_code.Find("101") != -1)		{ result = 10; }	// (Error with LEARN) Pressure at closed valve is smaller than 5% of the sensor full scale
		else if(err_code.Find("200") != -1)		{ result = 11; }	// (Error with ZERO)
		else									{ result =  0; }
	}
	else
	{
		result = 0;
	}

	return result;
}
