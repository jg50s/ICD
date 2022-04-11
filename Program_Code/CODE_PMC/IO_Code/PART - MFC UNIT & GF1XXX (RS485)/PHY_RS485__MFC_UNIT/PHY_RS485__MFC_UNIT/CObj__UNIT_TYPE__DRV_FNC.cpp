#include "StdAfx.h"
#include "CObj__UNIT_TYPE.h"



//------------------------------------------------------------------------------------
int CObj__UNIT_TYPE
::__Read__ANALOG(const CString& fnc_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{
	UCHAR szSendData[MAX_DATA_LENGTH];
	UCHAR szReadData[MAX_DATA_LENGTH];
	
	int nCmdLength = 0;
	int	nSizeOfRecv;
	
	UCHAR uchCheckSum = 0;
	CString str_cmd_name;

	// ...
	int cmd_id = atoi(fnc_name);
	int mac_id = atoi(io_info.sCOMMAND1);
	int mfc_index = atoi(io_info.sCOMMAND2);

	// ...
	{
		CString log_msg;

		log_msg.Format("Read__ANALOG_EX [%s] GAS_NUM [%d] --> IN", 
					   fnc_name, mac_id);

		Fnc__DRV_LOG(log_msg);
	}

	// ...
	double dbleMaxValue = io_info.dMAX_VALUE;

	if(dbleMaxValue <= 0)
	{
		CString log_msg;

		log_msg.Format("Invalid. Max Value[%f]", 
					   dbleMaxValue);

		Fnc__DRV_LOG(log_msg);
		return -1;
	}

	// ...
	int nPaddingSize = 0;

	ZeroMemory(szSendData, sizeof(szSendData));

	switch(cmd_id)
	{
		// 1. [FLOW] Make The Packet !!
		case 101:
		{
			str_cmd_name = "FLOW READ";

			// ...
			nSizeOfRecv = 12;

			szSendData[0] = m_BoardID + mac_id;
			szSendData[1] = STX;
			szSendData[2] = 0x80;	// CMD
			szSendData[3] = 0x03;	// Packet Length
			szSendData[4] = 0x68;	// class ID
			szSendData[5] = 0x01;	// Instance ID
			szSendData[6] = 0xB9;	// Attribute ID

			nCmdLength = 7;
			nPaddingSize = 1;
		}
		break;

		// 2. [VOLT] Make The Packet !!
		case 102:
		{
			str_cmd_name = "VOLT READ";

			// ...
			nSizeOfRecv = 12;

			szSendData[0] = m_BoardID + mac_id;
			szSendData[1] = STX;
			szSendData[2] = 0x80;
			szSendData[3] = 0x03;
			szSendData[4] = 0x6A;
			szSendData[5] = 0x01;
			szSendData[6] = 0xB6;
			
			nCmdLength = 7;
			nPaddingSize = 1;
		}
		break;
	
		// 3. [SETPOINT] Make The Packet !!
		case 103:
		{
			str_cmd_name = "SETPOINT READ";

			// ...
			nSizeOfRecv = 12;

			szSendData[0] = m_BoardID + mac_id;
			szSendData[1] = STX;
			szSendData[2] = 0x80;
			szSendData[3] = 0x03;
			szSendData[4] = 0x69;
			szSendData[5] = 0x01;
			szSendData[6] = 0xA5;
			
			nCmdLength = 7;
			nPaddingSize = 1;
		}
		break;

		// 4. [MACID] Make The Packet !!
		case 104:
		{
			str_cmd_name = "MACID READ";

			if(atof(m_szFirm_Revision[mfc_index]) >= 4.0)
			{
				nSizeOfRecv = 11;
			}
			else
			{
				nSizeOfRecv = 12;
			}

			// ...
			szSendData[0] = m_BoardID + mac_id;

			szSendData[1] = STX;
			szSendData[2] = 0x80;
			szSendData[3] = 0x04;
			szSendData[4] = 0x03;
			szSendData[5] = 0x01;
			szSendData[6] = 0x01;
			szSendData[7] = 0x01;

			nCmdLength = 8;
			nPaddingSize = 1;
		}
		break;

		default:
		{
			CString log_msg;
			log_msg.Format("[%s] Unknown Channel Error", fnc_name);

			Fnc__DRV_LOG(log_msg);
		}
		return -1;
	}

	// ...
	{
		CString log_msg;

		log_msg.Format("--> Start Read Analog:Gas_Num[%d] Action[%s] ...", 
					   mac_id,
					   str_cmd_name);

		Fnc__DRV_LOG(log_msg);
	}

	// ...
	ZeroMemory(szReadData, sizeof(szReadData));

	int nCmd_Ret = SendCommand(-1, 1,
							   szSendData, 
							   nCmdLength, 
							   szReadData, 
							   nSizeOfRecv, 
							   nPaddingSize,
							   mac_id,
							   mfc_index,
							   cmd_id);
	
	if(nCmd_Ret < 0)
	{
		CString log_msg;
		CString log_bff;

		log_msg += "\n";
		log_msg.Format("<-- Fail Read Analog:Fnc_Name:[%s], GAS_NUM:[%d], [%s] Value:%.2f ...",
					   fnc_name, mac_id, str_cmd_name, read_data);
		log_msg += "\n";

		log_bff.Format("Read__ANALOG_EX [%s] GAS_NUM [%d] <-- OUT, ret:%d", 
					   fnc_name, mac_id, nCmd_Ret);
		log_msg += log_bff;
		log_msg += "\n";

		Fnc__DRV_LOG(log_msg);
		return -1;
	}

	// ...
	CString szRcvData;

	unsigned int nHighByte;
	unsigned int nLowByte;
	double dblCurrSetPoint;
	double dblConvSetPoint;

	UCHAR recv_macid   = 0;
	UCHAR recv_chk_sum = 0;

	switch(cmd_id)
	{
		case 101:
		{
			nHighByte = ((unsigned int) szReadData[9]) * 256;
			nLowByte  = ((unsigned int) szReadData[8]);
		
			dblCurrSetPoint = nHighByte + nLowByte;
			dblConvSetPoint = (dblCurrSetPoint - 16384.0) / 327.68;
			dblConvSetPoint = (dblConvSetPoint / 100.0) * dbleMaxValue;
		
			szRcvData.Format("%f",dblConvSetPoint);
		}
		break;

		case 102:
		{
			nHighByte = ((unsigned int) szReadData[9]) * 256;
			nLowByte  = ((unsigned int) szReadData[8]);
		
			dblCurrSetPoint = ((float)nHighByte+(float)nLowByte);
			dblConvSetPoint = (dblCurrSetPoint / (float) 65535) * dbleMaxValue;
			szRcvData.Format("%f",dblConvSetPoint);
		}
		break;
		
		case 103:
		{
			nHighByte = ((unsigned int) szReadData[9]) * 256;
			nLowByte  = ((unsigned int) szReadData[8]);
		
			dblCurrSetPoint = nHighByte+nLowByte;
			dblConvSetPoint = (dblCurrSetPoint - 16384.0) / 327.68;
			dblConvSetPoint = (dblConvSetPoint / 100.0) * dbleMaxValue;
			szRcvData.Format("%f", dblConvSetPoint);
		}
		break;

		case 104:		
		{
			if(atof(m_szFirm_Revision[mfc_index]) >= 4.0)
			{
				recv_macid = szReadData[8];
				recv_chk_sum = szReadData[10];
			}
			else
			{
				recv_macid = szReadData[9];
				recv_chk_sum = szReadData[11];
			}
		
			if(recv_macid == (m_BoardID + mac_id))
			{
				szRcvData.Format("%d", (m_BoardID + mac_id));
			}
			else
			{
				szRcvData = "99";		
			}
		}
		break;
	
		default:
		{
			CString log_msg;

			log_msg.Format("[%s] UNKNOWN MESSAGE RECEIVED -> %d\n", 
						    fnc_name, 
							szReadData[9]);

			Fnc__DRV_LOG(log_msg);
		}
		return -1;
	}

	read_data = atof(szRcvData);

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "\n";

		log_bff.Format("<-- Success Read Analog:Fnc_Name:[%s], GAS_NUM:[%d], [%s] Value:%.2f ...",
					   fnc_name, mac_id, str_cmd_name, read_data);
		log_msg += log_bff;
		log_msg += "\n";

		log_bff.Format("Read__ANALOG_EX [%s] GAS_NUM [%d] <-- OUT", 
					   fnc_name, mac_id);
		log_msg += log_bff;
		log_msg += "\n";

		Fnc__DRV_LOG(log_msg);
	}
	return	1;
}

int CObj__UNIT_TYPE
::__Read__DIGITAL(const CString& fnc_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{
	UCHAR szSendData[MAX_DATA_LENGTH];
	UCHAR szReadData[MAX_DATA_LENGTH];
	int   nCmdLength = 0;
	int	  nSizeOfRecv;
	int nPaddingSize = 0;
	UCHAR uchCheckSum = 0;
	
	CString str__log;
	CString str_cmd_name;

	// ...
	int cmd_id = atoi(fnc_name);
	int mac_id = atoi(io_info.sCOMMAND1);
	int mfc_index = atoi(io_info.sCOMMAND2);

	// ...
	{
		CString log_msg;

		log_msg.Format("Read__DIGITAL_EX [%s] GAS_NUM [%d] --> IN", 
					   fnc_name, mac_id);

		Fnc__DRV_LOG(log_msg);
	}

	// ...
	ZeroMemory(szSendData, sizeof(szSendData));

	switch(cmd_id)
	{
		case 201:
		{
			if(m_nSubOnline[mfc_index] == OFFLINE)
			{	
				read_data = "OFFLINE";
			}
			else
			{
				read_data = "ONLINE";
			}

			// ...
			{
				str__log.Format("Read__DIGITAL_EX [%s] GAS_NUM [%d], [%s] <-- OUT \n", 
								fnc_name, 
								mac_id, 
								read_data);

				Fnc__DRV_LOG(str__log);
			}
		}
		return 1;

		// 1. [VALVE Sts] Make The Packet !!
		case 202:
		{
			str_cmd_name = "VALVE STATUS READ";

			if(atof(m_szFirm_Revision[mfc_index]) >= 4.0)
			{
				nSizeOfRecv = 11;
			}
			else
			{
				nSizeOfRecv = 12;
			}
		
			szSendData[0] = m_BoardID + mac_id;
			szSendData[1] = STX;
			szSendData[2] = 0x80;
			szSendData[3] = 0x04;		// nSizeOfSend-6 이다..
			szSendData[4] = 0x6A;
			szSendData[5] = 0x01;
			szSendData[6] = 0x01;
			szSendData[7] = 0x01;

			nCmdLength = 8;
			nPaddingSize = 1;
		}
		break;
	
		default:
		{
			str__log.Format("[%s] Unknown Channel Error\n",
				            fnc_name);
			Fnc__DRV_LOG(str__log);
		}
		return -1;
	}

	// ...
	{
		str__log.Format("--> Start Read Digital:Gas_Num[%d] Action[%s] ...",
			            mac_id, 
						str_cmd_name);

		Fnc__DRV_LOG(str__log);
	}

	// ...
	CString str_cmd;
	str_cmd.Format("%s", szSendData);
	ZeroMemory(szReadData, sizeof(szReadData));

	int nCmd_Ret = SendCommand(-1, 1,
							   szSendData, 
							   nCmdLength, 
							   szReadData, 
							   nSizeOfRecv, 
							   nPaddingSize,
							   mac_id,
							   mfc_index,
							   cmd_id);
	
	if(nCmd_Ret < 0)
	{
		CString log_bff;

		str__log.Format("<-- Fail Read Digital:Fnc_Name:[%s], GAS_NUM:[%d], [%s] Value:%s \n",
			            fnc_name, 
						mac_id, 
						str_cmd_name, 
						read_data);

		log_bff.Format("Read__DIGITAL_EX [%s] GAS_NUM [%d] <-- OUT, ret:%d \n", 
			            fnc_name, 
						mac_id, 
						nCmd_Ret);
		str__log += log_bff;

		Fnc__DRV_LOG(str__log);
		return -1;
	}

	// ...
	CString szRcvData;	
	UCHAR recv_vlv_sts = 0;

	switch(cmd_id)
	{
		case 202:
		{
			if(atof(m_szFirm_Revision[mfc_index]) >= 4.0)
			{
				recv_vlv_sts = szReadData[8];
			}
			else
			{
				recv_vlv_sts = szReadData[9];
			}
		
				 if(recv_vlv_sts == 0x00)		szRcvData = "CONTROL";
			else if(recv_vlv_sts == 0x01)		szRcvData = "CLOSE";
			else if(recv_vlv_sts == 0x02)		szRcvData = "OPEN";
			else if(recv_vlv_sts == 0x03)		szRcvData = "OFF";
			else								szRcvData = "NONE";
		}
		break;

		default:
		{
			str__log.Format("[%s] UNKNOWN CHANNEL NAME -> %s\n", fnc_name);
			Fnc__DRV_LOG(str__log);
		}
		break;
	}

	read_data = szRcvData;
	
	// ...
	{
		CString log_bff;

		str__log.Format("<-- Success Read Digital :: Fnc_Name:[%s], GAS_NUM:[%d], [%s] Value:%s \n",
						fnc_name, 
						mac_id, 
						str_cmd_name, 
						read_data);

		log_bff.Format("Read__DIGITAL_EX [%s] GAS_NUM [%d] <-- OUT \n", 
					    fnc_name, 
						mac_id);
		str__log += log_bff;

		Fnc__DRV_LOG(str__log);
	}

	return	1;
}

int CObj__UNIT_TYPE
::__Read__STRING(const CString& fnc_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	int cmd_id = atoi(fnc_name);
	int mac_id = atoi(io_info.sCOMMAND1);
	int mfc_index = atoi(io_info.sCOMMAND2);

	// ...
	{
		CString log_msg;

		log_msg.Format("Read__STRING_EX [%s] GAS_NUM [%d] --> IN", 
			           fnc_name, mac_id); 

		Fnc__DRV_LOG(log_msg);
	}

	switch(cmd_id)
	{
		case 301:
		{
			read_data.Format("%s", m_szFirm_Revision[mfc_index]);
		}
		break;
	}

	// ...
	{
		CString log_msg;

		log_msg.Format("Read__STRING_EX [%s] GAS_NUM [%d] <-- OUT \n", 
					   fnc_name, mac_id);

		Fnc__DRV_LOG(log_msg);
	}
	return 1;
}


//------------------------------------------------------------------------------------
int CObj__UNIT_TYPE
::__Write__ANALOG(const CString& fnc_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	int cmd_id = atoi(fnc_name);
	int mac_id = atoi(io_info.sCOMMAND1);
	int mfc_index = atoi(io_info.sCOMMAND2);

	double min_value = io_info.dMIN_VALUE;
	double max_value = io_info.dMAX_VALUE;

	// ...
	int retry_count = 0;

	switch(cmd_id)
	{
		case 150:	// 1. [Setpoint] Make The Packet !!
		{
			while(1)
			{
				double min_set = set_data - set_data / 100.0;
				double max_set = set_data + set_data / 100.0;

				double read_data = 0.0;
	
				if(dEXT_CH__CFG_MFC_485_SETPOINT_READ_CONFIRM_USE->Check__DATA(STR__ENABLE) > 0)
				{
					int fnc_flag = 1;

					if(fnc_flag > 0)
					{
						fnc_flag = Fnc__FLOW_SETPOINT_SET(cmd_id,mac_id,mfc_index, set_data,min_value,max_value);
					}
					
					if(fnc_flag > 0)
					{
						fnc_flag = Fnc__FLOW_SETPOINT_GET(cmd_id,mac_id,mfc_index, max_value, read_data);
					}
						
					if(fnc_flag > 0)
					{
						if((read_data >= min_set) && (read_data <= max_set))
						{
							if(set_data < 0.001)		Fnc__VALVE_CONTROL_SET(VLV_CTRL_MODE__CLOSE,   cmd_id,mac_id,mfc_index);
							else						Fnc__VALVE_CONTROL_SET(VLV_CTRL_MODE__CONTROL, cmd_id,mac_id,mfc_index);

							return 1;
						}
					}
				}
				else
				{
					int fnc_flag = 1;

					if(fnc_flag > 0)
					{
						fnc_flag = Fnc__FLOW_SETPOINT_SET(cmd_id,mac_id,mfc_index, set_data,min_value,max_value);
					}

					if(fnc_flag > 0)
					{
						if(set_data < 0.001)			Fnc__VALVE_CONTROL_SET(VLV_CTRL_MODE__CLOSE,   cmd_id,mac_id,mfc_index);
						else							Fnc__VALVE_CONTROL_SET(VLV_CTRL_MODE__CONTROL, cmd_id,mac_id,mfc_index);

						return 1;
					}
				}

				retry_count++;
				if(retry_count <= 5)
				{
					// ...
					{
						CString str__log;

						str__log.Format("ERROR ! : Retry Count [%1d] \n", retry_count);
						Fnc__DRV_LOG(str__log);				
					}
	
					// ...
					{
						SCX__TIMER_CTRL x_timer_ctrl;
						x_timer_ctrl->WAIT(0.01);   // 10 msec  delay
					}
				}
				else
				{
					if(dEXT_CH__CFG_MFC_485_CONTROL_TIMEOUT_ALARM_USE->Check__DATA(STR__ENABLE) > 0)
					{
						CString alm_msg;
						CString alm_bff;

						alm_bff.Format("Gas%1d's (%.3f) sccm Setpoint Timeout ! \n",
									   mac_id,set_data);
						alm_msg += alm_bff;

						alm_bff.Format("   Min(%.3f), Max(%.3f) \n", min_value,max_value);
						alm_msg += alm_bff;

						alm_bff.Format("   Retry Count <- [%1d] \n", retry_count);
						alm_msg += alm_bff;

						mDB__ALM_CTRL.Load__ALM_CTRL_TIMEOUT(mac_id,mfc_index, alm_msg);
					}
					return -1;
				}
			}
		}
		break;

		default:
		{
			CString str__log;

			str__log.Format("[%s] Unknown Channel Error \n",fnc_name);
			Fnc__DRV_LOG(str__log);
		}
		return -1;
	}

	return	1;
}

int CObj__UNIT_TYPE
::Fnc__FLOW_SETPOINT_SET(const int cmd_id,
						 const int mac_id,
						 const int mfc_index,
						 const double set_data,
						 const double min,
						 const double max)
{
	UCHAR szSendData[MAX_DATA_LENGTH];
	UCHAR szReadData[MAX_DATA_LENGTH];
	int   nCmdLength =  0;
	int	  nSizeOfRecv;

	double dblSetPoint;
	int nSetPoint;
	unsigned char ucHighByte;
	unsigned char ucLowByte;

	CString str_cmd_name;
	int nPaddingSize = 0;

	// ...
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg = "\n";

		log_bff.Format("Write__ANALOG_EX [%1d] GAS_NUM [%d] --> IN", cmd_id,mac_id);
		log_msg += log_bff;
		log_msg += "\n";

		log_bff.Format("** Set => [%f] sccm, Fnc_ID:[%d], GAS_NUM[%d] Start ...", set_data, cmd_id,mac_id);
		log_msg += log_bff;
		log_msg += "\n";
	}

	// ...
	double dbleMaxValue = max;

	if(dbleMaxValue <= 0)
	{	
		log_bff.Format("Invalid. Max Value[%f]", dbleMaxValue);
		log_msg += log_bff;

		Fnc__DRV_LOG(log_msg);
		return -1;
	}

	// ...
	ZeroMemory(szSendData, sizeof(szSendData));

	// ...
	{
		str_cmd_name = "SETPOINT-SET";

		dblSetPoint	= (set_data / dbleMaxValue) * 100;
		nSetPoint	= (int)((327.68 * dblSetPoint) + 16384);
		ucHighByte	= (unsigned char)(nSetPoint / 256);
		ucLowByte	= (unsigned char)(nSetPoint % 256); 
		
		// ...
		nSizeOfRecv	  = 2;

		szSendData[0] = m_BoardID + mac_id;
		szSendData[1] = STX;
		szSendData[2] = 0x81;
		szSendData[3] = 0x05;
		szSendData[4] = 0x69;
		szSendData[5] = 0x01;
		szSendData[6] = 0xA4;
		szSendData[7] = ucLowByte;
		szSendData[8] = ucHighByte;
		
		nCmdLength = 9;
		nPaddingSize = 1;
	}

	// ...
	{
		log_bff.Format("--> Start Write Analog:Gas_Num[%d] Action[%s] ...", mac_id, str_cmd_name);
		log_msg += log_bff;
		log_msg += "\n";

		Fnc__DRV_LOG(log_msg);
	}

	// ...
	CString str_cmd;
	str_cmd.Format("%s", szSendData);
	ZeroMemory(szReadData, sizeof(szReadData));

	// ...
	int nCmd_Ret = SendCommand(1, 1,
							   szSendData, 
							   nCmdLength, 
							   szReadData, 
							   nSizeOfRecv, 
							   nPaddingSize,
							   mac_id,
							   mfc_index,
							   cmd_id);
	
	// ...
	{
		log_msg = "\n";

		log_bff.Format("--> SendCommand Ret:%d", nCmd_Ret);
		log_msg += log_bff;
		log_msg += "\n";

		if(nCmd_Ret < 0)
		{
			log_bff.Format("Set => [%f] sccm, Fnc_ID:[%d], GAS_NUM[%d] Failed..ret:-1", 
				           set_data, cmd_id, mac_id);
			log_msg += log_bff;
			log_msg += "\n";

			log_bff.Format("Error :: Write__ANALOG_EX [%1d] GAS_NUM [%d] <-- OUT, ret:%d", 
				           cmd_id, mac_id, nCmd_Ret);
			log_msg += log_bff;
			log_msg += "\n";

			Fnc__DRV_LOG(log_msg);
			return -1;
		}

		log_bff.Format("Set Complete => [%f], Fnc_ID:[%d], GAS_NUM[%d]", 
			           set_data, cmd_id, mac_id);
		log_msg += log_bff;
		log_msg += "\n";

		log_bff.Format("Write__ANALOG_EX [%1d] GAS_NUM [%d] <-- OUT", 
					   cmd_id, mac_id);
		log_msg += log_bff;
		log_msg += "\n";

		Fnc__DRV_LOG(log_msg);
	}
	return	1;
}
int CObj__UNIT_TYPE
::Fnc__FLOW_SETPOINT_GET(const int cmd_id,const int mac_id,const int mfc_index, const double max, double& read_data)
{
	UCHAR szSendData[MAX_DATA_LENGTH];
	UCHAR szReadData[MAX_DATA_LENGTH];
	int nCmdLength = 0;
	int	nSizeOfRecv;
	UCHAR uchCheckSum = 0;
	CString str_cmd_name;

	// ...
	CString log_msg;
	CString log_bff;

	// ...
	int nPaddingSize = 0;

	ZeroMemory(szSendData, sizeof(szSendData));

	// ...
	{
		str_cmd_name = "SETPOINT-READ";

		nSizeOfRecv = 12;
		szSendData[0] = m_BoardID + mac_id;
		szSendData[1] = STX;
		szSendData[2] = 0x80;
		szSendData[3] = 0x03;
		szSendData[4] = 0x69;
		szSendData[5] = 0x01;
		szSendData[6] = 0xA5;

		nCmdLength = 7;
		nPaddingSize = 1;
	}

	// ...
	{
		log_msg = "\n";

		log_bff.Format("Read__ANALOG_EX : GAS_NUM [%1d] --> IN", mac_id);
		log_msg += log_bff;
		log_msg += "\n";

		log_bff.Format("--> Start Read Analog:Gas_Num[%d] Action[%s] ...", 
			           mac_id, str_cmd_name);
		log_msg += log_bff;
		log_msg += "\n";

		Fnc__DRV_LOG(log_msg);
	}

	// ...
	ZeroMemory(szReadData, sizeof(szReadData));
	
	int nCmd_Ret = SendCommand(-1, 1,
							   szSendData, 
							   nCmdLength, 
							   szReadData, 
							   nSizeOfRecv, 
							   nPaddingSize, 
							   mac_id,
							   mfc_index,
							   cmd_id);
	
	// ...
	log_msg = "\n";

	if(nCmd_Ret < 0)
	{
		log_bff.Format("<-- Fail Read Analog : GAS_NUM:[%d], [%s] Value:%.2f ...", 
			           mac_id, str_cmd_name, read_data);
		log_msg += log_bff;
		log_msg += "\n";

		log_bff.Format("Error :: Read__ANALOG_EX : GAS_NUM [%d] <-- OUT, ret:%d\n", 
			           mac_id, nCmd_Ret);
		log_msg += log_bff;
		log_msg += "\n";

		Fnc__DRV_LOG(log_msg);
		return -1;
	}

	// ...
	CString szRcvData;

	unsigned int nHighByte;
	unsigned int nLowByte;
	double dblCurrSetPoint;
	double dblConvSetPoint;
	UCHAR recv_macid   = 0;
	UCHAR recv_chk_sum = 0;

	// ...
	{
		nHighByte = ((unsigned int) szReadData[9]) * 256;
		nLowByte  = ((unsigned int) szReadData[8]);
		
		dblCurrSetPoint = nHighByte+nLowByte;
		dblConvSetPoint = (dblCurrSetPoint - 16384.0) / 327.68;
		dblConvSetPoint = (dblConvSetPoint / 100.0) * max;
		szRcvData.Format("%f", dblConvSetPoint);
	}

	// ...
	{
		read_data = atof(szRcvData);

		// ...
		{
			log_bff.Format("<-- Success Read Analog : GAS_NUM(%d), [%s] Value:%.2f ...", 
				           mac_id, str_cmd_name, read_data);
			log_msg += log_bff;
			log_msg += "\n";
		}

		if(read_data < 0)
		{
			read_data = 0.0;

			log_bff.Format(":: Read Value (0.0) <- (%.2f) ...", 
			               read_data);
			log_msg += log_bff;
			log_msg += "\n";
		}

		Fnc__DRV_LOG(log_msg);
	}

	return	1;
}

int CObj__UNIT_TYPE
::Fnc__VALVE_CONTROL_SET(const int ctrl_mode,
						 const int cmd_id,
						 const int mac_id,
						 const int mfc_index)
{
	CString fnc_name;

		 if(ctrl_mode == VLV_CTRL_MODE__CLOSE)			fnc_name = "Fnc__VLV_CLOSE_SET()";
	else if(ctrl_mode == VLV_CTRL_MODE__CONTROL)		fnc_name = "Fnc__VLV_CONTROL_SET()";
	else												return -1;

	// ...
	UCHAR szSendData[MAX_DATA_LENGTH];
	UCHAR szReadData[MAX_DATA_LENGTH];
	int   nCmdLength = 0;
	int	  nSizeOfRecv;
	
	CString str__log;
	CString str_cmd_name;

	int nPaddingSize = 0;

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "\n";
		log_bff.Format("%s <-- GAS_NUM [%d] : Started", fnc_name,mac_id);
		log_msg += log_bff;
		log_msg += "\n";

		Fnc__DRV_LOG(log_msg);
	}

	// ...
	ZeroMemory(szSendData, sizeof(szSendData));

	if(ctrl_mode == VLV_CTRL_MODE__CONTROL)
	{
		str_cmd_name = "CONTROL";

		// ...
		nSizeOfRecv = 2;

		szSendData[0] = m_BoardID + mac_id;
		szSendData[1] = STX;
		szSendData[2] = 0x81;
		szSendData[3] = 0x04;
		szSendData[4] = 0x6a;
		szSendData[5] = 0x01;
		szSendData[6] = 0x01;
		szSendData[7] = 0x00;

		nCmdLength = 8;
		nPaddingSize = 1;
	}
	else if(ctrl_mode == VLV_CTRL_MODE__CLOSE)	
	{
		str_cmd_name = "CLOSE";

		// ...
		nSizeOfRecv = 2;

		szSendData[0] = m_BoardID + mac_id;
		szSendData[1] = STX;
		szSendData[2] = 0x81;
		szSendData[3] = 0x04;
		szSendData[4] = 0x6a;
		szSendData[5] = 0x01;
		szSendData[6] = 0x01;
		szSendData[7] = 0x01;

		nCmdLength = 8;
		nPaddingSize = 1;
	}

	// ...
	ZeroMemory(szReadData, sizeof(szReadData));

	// ...
	{
		str__log.Format("--> Start Write Digital: Gas_Num[%d] ...", mac_id);

		Fnc__DRV_LOG(str__log);
	}

	int nCmd_Ret = SendCommand(1, 1,
							   szSendData, 
							   nCmdLength, 
							   szReadData, 
							   nSizeOfRecv, 
							   nPaddingSize,
							   mac_id,
							   mfc_index,
							   cmd_id);

	// ...
	{
		str__log.Format("--> SendCommand : Ret(%d) ...", mac_id); 

		Fnc__DRV_LOG(str__log);
	}

	if(nCmd_Ret < 0)
	{
		CString log_msg;
		CString log_bff;

		log_msg = "\n";
		log_bff.Format("Error :: Set Error => GAS_NUM[%d] ... (ret : %1d)", mac_id,nCmd_Ret);	
		log_msg += log_bff;
		log_msg += "\n";

		Fnc__DRV_LOG(log_msg);		
		return -1;
	}

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "\n";
		log_bff.Format("Set Complete => GAS_NUM[%d] ... (ret : %1d)", mac_id,nCmd_Ret);
		log_msg += log_bff;
		log_msg += "\n";

		Fnc__DRV_LOG(log_msg);
	}
	return	1;
}


int CObj__UNIT_TYPE
::__Write__DIGITAL(const CString& fnc_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	int flag_s_cmmd = -1;

	UCHAR szSendData[MAX_DATA_LENGTH];
	UCHAR szReadData[MAX_DATA_LENGTH];
	int   nCmdLength = 0;
	int	  nSizeOfRecv;
	
	CString str__log;
	CString str_cmd_name;

	int nPaddingSize = 0;

	// ...
	int cmd_id = atoi(fnc_name);
	int mac_id = atoi(io_info.sCOMMAND1);
	int mfc_index = atoi(io_info.sCOMMAND2);

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "\n";

		log_bff.Format("Write__DIGITAL_EX [%s] GAS_NUM [%d] --> IN", fnc_name,mac_id);
		log_msg += log_bff;
		log_msg += "\n";

		log_bff.Format("** Set => [%s], Fnc_ID:[%d], GAS_NUM[%d] Start..", set_data,cmd_id,mac_id);
		log_msg += log_bff;
		log_msg += "\n";

		Fnc__DRV_LOG(log_msg);
	}

	// ...
	ZeroMemory(szSendData, sizeof(szSendData));

	switch(cmd_id)
	{
		case 251:
			str_cmd_name = "GET Firm Ver.";

			if(set_data.CompareNoCase("GET") == 0)
			{
				nSizeOfRecv = 14;
				
				// ...
				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x80;
				szSendData[3] = 0x03;
				szSendData[4] = 0x64;
				szSendData[5] = 0x01;
				szSendData[6] = 0x05;
				
				nCmdLength = 7;
				nPaddingSize = 1;
			}
			else
			{
				str__log.Format("[%s] Unknown SetData[%s] Error", fnc_name,set_data);

				Fnc__DRV_LOG(str__log);
				return -1;
			}
			break;

		case 252:
			flag_s_cmmd = 1;
			
			if(set_data.CompareNoCase("AUTOZERO") == 0)
			{
				str_cmd_name = "AUTOZERO";
				
				// ...
				nSizeOfRecv = 2;
				
				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x81;
				szSendData[3] = 0x04;
				szSendData[4] = 0x68;
				szSendData[5] = 0x01;
				szSendData[6] = 0xa5;

				nCmdLength = 7;
				nPaddingSize = 2;
			}
			else if(set_data.CompareNoCase("INIT") == 0)
			{
				str_cmd_name = "INIT";
			
				// ...
				nSizeOfRecv = 2;

				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x81;
				szSendData[3] = 0x07;
				szSendData[4] = 0x00;
				szSendData[5] = 0x01;
				szSendData[6] = 0x13;

				nCmdLength = 7;
				nPaddingSize = 5;
			}
			else if(set_data.CompareNoCase("RESET") == 0)
			{
				str_cmd_name = "RESET";

				// ...
				nSizeOfRecv = 2;			

				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x81;
				szSendData[3] = 0x04;
				szSendData[4] = 0x69;
				szSendData[5] = 0x01;
				szSendData[6] = 0x04;
				szSendData[7] = 0x01;

				nCmdLength = 8;
				nPaddingSize = 1;
			}
			else if(set_data.CompareNoCase("CALIBRATION") == 0)
			{
				str_cmd_name = "CALIBRATION";

				// ...
				nSizeOfRecv = 2;
				
				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x81;
				szSendData[3] = 0x05;
				szSendData[4] = 0x66;
				szSendData[5] = 0x00;
				szSendData[6] = 0x65;
				szSendData[7] = 0x02;

				nCmdLength = 8;
				nPaddingSize = 2;
			}
			else
			{
				str__log.Format("[%s] Unknown SetData[%s] Error\n",	fnc_name,set_data);

				Fnc__DRV_LOG(str__log);
				return -1;
			}
			break;

		case 253:
			// ...
			{
				flag_s_cmmd = 1;
			}

			if(set_data.CompareNoCase("FREEZE") == 0)
			{
				str_cmd_name = "FREEZE";

				// ...
				nSizeOfRecv = 2;

				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x81;
				szSendData[3] = 0x04;
				szSendData[4] = 0x69;
				szSendData[5] = 0x01;
				szSendData[6] = 0x05;
				
				nCmdLength = 7;
				nPaddingSize = 2;
			}
			else if(set_data.CompareNoCase("FOLLOW") == 0)
			{
				str_cmd_name = "FOLLOW";

				// ...
				nSizeOfRecv = 2;

				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x81;
				szSendData[3] = 0x04;
				szSendData[4] = 0x69;
				szSendData[5] = 0x01;
				szSendData[6] = 0x05;
				szSendData[7] = 0x01;
				
				nCmdLength = 8;
				nPaddingSize  = 1;
			}
			else
			{
				str__log.Format("[%s] Unknown SetData[%s] Error\n", fnc_name,set_data);

				Fnc__DRV_LOG(str__log);
				return -1;
			}
			break;

		case 254:
			flag_s_cmmd = 1;

			if(set_data.CompareNoCase("SEMI") == 0)
			{
				str_cmd_name = "SEMI";

				// ...
				nSizeOfRecv = 2;

				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x81;
				szSendData[3] = 0x04;
				szSendData[4] = 0x6a;
				szSendData[5] = 0x01;
				szSendData[6] = 0x05;
				szSendData[7] = 0x01;
				
				nCmdLength = 8;
				nPaddingSize = 1;
			}
			else if(set_data.CompareNoCase("UNIT") == 0)
			{
				str_cmd_name = "UNIT";

				// ...
				nSizeOfRecv = 2;

				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x81;
				szSendData[3] = 0x04;
				szSendData[4] = 0x6a;
				szSendData[5] = 0x01;
				szSendData[6] = 0x05;
				szSendData[7] = 0x02;

				nCmdLength = 8;
				nPaddingSize = 1;
			}
			else
			{
				str__log.Format("[%s] Unknown SetData[%s] Error\n", fnc_name,set_data);

				Fnc__DRV_LOG(str__log);
				return -1;
			}
			break;

		case 255:
			flag_s_cmmd = 1;

			if(set_data.CompareNoCase("CONTROL") == 0)
			{
				str_cmd_name = "CONTROL";

				// ...
				nSizeOfRecv = 2;

				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x81;
				szSendData[3] = 0x04;
				szSendData[4] = 0x6a;
				szSendData[5] = 0x01;
				szSendData[6] = 0x01;
				szSendData[7] = 0x00;
				
				nCmdLength = 8;
				nPaddingSize = 1;
			}
			else if(set_data.CompareNoCase("CLOSE") == 0)
			{
				str_cmd_name = "CLOSE";

				// ...
				nSizeOfRecv = 2;

				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x81;
				szSendData[3] = 0x04;
				szSendData[4] = 0x6a;
				szSendData[5] = 0x01;
				szSendData[6] = 0x01;
				szSendData[7] = 0x01;

				nCmdLength = 8;
				nPaddingSize = 1;
			}
			else if(set_data.CompareNoCase("OPEN") == 0)
			{
				str_cmd_name = "OPEN";

				// ...
				nSizeOfRecv = 2;

				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x81;
				szSendData[3] = 0x04;
				szSendData[4] = 0x6a;
				szSendData[5] = 0x01;
				szSendData[6] = 0x01;
				szSendData[7] = 0x02;

				nCmdLength = 8;
				nPaddingSize = 1;
			}
			else if(set_data.CompareNoCase("OFF") == 0)
			{
				str_cmd_name = "OFF";

				// ...
				nSizeOfRecv = 2;

				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x81;
				szSendData[3] = 0x04;
				szSendData[4] = 0x6a;
				szSendData[5] = 0x01;
				szSendData[6] = 0x01;
				szSendData[7] = 0x03;

				nCmdLength = 8;
				nPaddingSize = 1;
			}
			else
			{
				str__log.Format("[%s] Unknown SetData[%s] Error\n", fnc_name,set_data);

				Fnc__DRV_LOG(str__log);
				return -1;
			}
			break;

		case 256:
			flag_s_cmmd = 1;

			if(set_data.CompareNoCase("DIGITAL") == 0)
			{
				str_cmd_name = "DIGITAL";

				// ...
				nSizeOfRecv = 2;

				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x81;	
				szSendData[3] = 0x04;
				szSendData[4] = 0x69;	
				szSendData[5] = 0x01;
				szSendData[6] = 0x03;
				szSendData[7] = 0x01;
				
				nCmdLength = 8;
				nPaddingSize = 1;
			}
			else if(set_data.CompareNoCase("ANALOG")  == 0)
			{
				str_cmd_name = "ANALOG";

				// ...
				nSizeOfRecv = 2;

				szSendData[0] = m_BoardID + mac_id;
				szSendData[1] = STX;
				szSendData[2] = 0x81;	
				szSendData[3] = 0x04;
				szSendData[4] = 0x69;	
				szSendData[5] = 0x01;
				szSendData[6] = 0x03;	
				szSendData[7] = 0x02;

				nCmdLength = 8;
				nPaddingSize = 1;
			}
			else
			{
				str__log.Format("[%s] Unknown SetData[%s] Error\n", fnc_name,set_data);

				Fnc__DRV_LOG(str__log);
				return -1;
			}
			break;
	}

	ZeroMemory(szReadData, sizeof(szReadData));

	// ...
	{
		str__log.Format("--> Start Write Digital : Gas_Num[%d] Action[%s] ...", mac_id,str_cmd_name);

		Fnc__DRV_LOG(str__log);
	}

	int nCmd_Ret = SendCommand(flag_s_cmmd,
							   1,
							   szSendData, 
							   nCmdLength, 
							   szReadData, 
							   nSizeOfRecv, 
							   nPaddingSize,
							   mac_id,
							   mfc_index,
							   cmd_id);

	// ...
	{
		str__log.Format("--> SendCommand Ret:%d", nCmd_Ret);

		Fnc__DRV_LOG(str__log);
	}

	if(nCmd_Ret < 0)
	{
		CString log_msg;
		CString log_bff;

		log_msg = "\n";

		log_bff.Format("Set => [%s], Fnc_ID:[%d], GAS_NUM[%d] Failed..ret:-1", set_data, cmd_id, mac_id);
		log_msg += log_bff;
		log_msg += "\n";

		log_bff.Format("Write__DIGITAL_EX [%s] GAS_NUM [%d] <-- OUT, ret:%d ", fnc_name, mac_id, nCmd_Ret);
		log_msg += log_bff;
		log_msg += "\n";

		Fnc__DRV_LOG(log_msg);		
		return -1;
	}

	switch(cmd_id)
	{
		case 251:
		{
			m_szFirm_Revision[mfc_index].Format("%c%c%c%c",
				                                szReadData[8], 
												szReadData[9], 
												szReadData[10], 
												szReadData[11]);
		}
		break;
	}

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "\n";

		log_bff.Format("Set Complete => [%s], Fnc_ID:[%d], GAS_NUM[%d]", 
					   set_data, cmd_id, mac_id);
		log_msg += log_bff;
		log_msg += "\n";
	
		log_bff.Format("Write__DIGITAL_EX [%s] GAS_NUM [%d] <-- OUT", 
						fnc_name, mac_id);
		log_msg += log_bff;
		log_msg += "\n";

		Fnc__DRV_LOG(log_msg);
	}
	return	1;
}

int CObj__UNIT_TYPE
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{
	
	return -1;
}


//------------------------------------------------------------------------------------
int CObj__UNIT_TYPE
::SendCommand(const int flag_s_cmmd,
			  const int retry_flag,
			  unsigned char *szSendData, 
			  const int nLength, 
			  unsigned char *szRecvData, 
			  int nRecvSize,
			  const int nPaddingSize,
			  const int mac_id,
			  const int mfc_index,
			  const int cmd_id)
{
	int flag = _SendCommand(flag_s_cmmd,
							retry_flag,
						    szSendData, 
							nLength, 
							szRecvData, 
							nRecvSize,
							nPaddingSize,
							mac_id,
							mfc_index,
							cmd_id);

	// ...
	{
		SCX__TIMER_CTRL x_timer_ctrl;
		x_timer_ctrl->WAIT(0.01);			// 10 msec
	}
	return flag;
}
int CObj__UNIT_TYPE
::_SendCommand(const int flag_s_cmmd,
			   const int retry_flag,
			   unsigned char *szSendData, 
			   const int nLength, 
			   unsigned char *szRecvData, 
			   int nRecvSize,
			   const int nPaddingSize,
			   const int mac_id,
			   const int mfc_index,
			   const int cmd_id)
{
	CString str_data;
	unsigned char szCommand[MAX_DATA_LENGTH];
	int nCounter = 0;
	CString str__log;
	unsigned char ucACK = ACK;

	// ...
	unsigned char uchCheckSum = CheckSum(szSendData, 1, nLength);
	ZeroMemory(szCommand, sizeof(szCommand));
	memcpy(szCommand, szSendData, sizeof(szCommand));

	for(int i = nLength; i <= (nPaddingSize + nLength); i++)
	{
		if(i == (nPaddingSize + nLength))		szCommand[i] = uchCheckSum;
		else									szCommand[i] = PADDING;
	}

	// ...
	int check_flag = 1;

	int nSizeofSend = nLength + nPaddingSize + 1;
	int nSizeofRecv = nRecvSize;

	aCH__DRV_READ_DELAY_TIME_MSEC->Get__DATA(str_data);
	m_Rcv_Time = atoi(str_data);
	
	if(m_Rcv_Time < 300)		m_Rcv_Time = 300;

	do
	{
		if(nCounter > 0)
		{
			SCX__TIMER_CTRL x_timer_ctrl;
			x_timer_ctrl->WAIT(0.01);
		}

		mX_Serial->CLEAR__BUFFER(&str__log);
		nRecvSize = nSizeofRecv;

		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg = "\n";
			log_bff.Format("Send ... Fnc_ID:[%d], GAS_NUM[%d], SendSize: [%d]",  
			               cmd_id, mac_id, nSizeofSend);
			log_msg += log_bff;
			log_msg += "\n";

			for(int i=0; i<nSizeofSend; i++)
			{
				log_bff.Format("SEND => [%#X]", szCommand[i]);
				log_msg += log_bff;
				log_msg += "\n";
			}
			
			Fnc__DRV_LOG(log_msg);
		}

		SCX__ASYNC_TIMER_CTRL x_async_timer;
		x_async_timer->START__COUNT_UP(9999);

		// ...
		{
			CString log_msg;
			CString log_bff;
			
			log_bff.Format("Start -- OnlyRecv__CHAR() : nRecvSize <- (%1d), m_Rcv_Time <- (%1d) \n",
				           nRecvSize, m_Rcv_Time);
			log_msg = log_bff;
			
			Fnc__DRV_LOG(log_msg);
		}
		
		int nSendRet   = mX_Serial->CHAR__SEND(szCommand, nSizeofSend);
		int Recv_count = mX_Serial->OnlyRecv__CHAR(ucACK, szRecvData, &nRecvSize, m_Rcv_Time);

		// ...
		{
			CString log_msg;
			CString log_bff;
			
			log_bff.Format("End -- OnlyRecv__CHAR() : Recv_count <- (%1d), m_Rcv_Time <- (%1d) \n",
						   Recv_count, m_Rcv_Time);
			log_msg = log_bff;
			
			Fnc__DRV_LOG(log_msg);
		}

		if(Recv_count > 0)
		{
			double cur_sec = x_async_timer->Get__CURRENT_TIME();

			if(cur_sec >= 0.100)			// 100 msec
			{
				CString log_msg;				
				log_msg.Format("TimeCheck : %.3f sec \n", cur_sec);
					
				Fnc__DRV_LOG(log_msg);
			}
		}
		x_async_timer->STOP();

		if(nRecvSize == nSizeofRecv)				
		{
			// ...
			{
				CString log_msg;
				CString log_bff;

				log_msg = "\n";

				if(nRecvSize != nSizeofRecv)
				{
					log_bff.Format("RECV <= [%s], Recv Ret (%d), RecvSize (%d), Expect RecvSize (%d)", 
						           szRecvData, Recv_count, nRecvSize, nSizeofRecv);
					log_msg += log_bff;
					log_msg += "\n";
				}
				else
				{
					log_bff.Format("RECV <= [%s], Recv Ret (%d), RecvSize (%d)", 
						           szRecvData, Recv_count, nRecvSize);
					log_msg += log_bff;
					log_msg += "\n";
				}

				log_msg += "RECV Data : "; 

				for(int i=0; i<nRecvSize; i++)
				{
					log_bff.Format("%#X ", szRecvData[i]);
					log_msg += log_bff;
				}
				log_msg += "\n";

				Fnc__DRV_LOG(log_msg);
			}

			if(szRecvData[0] == ACK)
			{
				if(flag_s_cmmd < 0)
				{
					// ...
					{
						CString log_msg;
						log_msg.Format("Send ACK : %X", ucACK);

						Fnc__DRV_LOG(log_msg);
					}

					mX_Serial->CHAR__SEND(&ucACK, 1);

					// Check-Sum Verify ...
					if((nRecvSize == nSizeofRecv)				
					&& (nRecvSize > 2))	
					{
						int check_err = -1;
						
						unsigned char uc_checksum   = CheckSum(szRecvData, 1, nRecvSize-2);
						unsigned char recv_checksum = szRecvData[nRecvSize-1];
						
						if(uc_checksum != recv_checksum)
						{
							check_err = 1;	
						}
						
						if(check_err > 0)
						{
							CString log_msg;
							log_msg.Format("Error CheckSum : [%X] != [%X]", uc_checksum, recv_checksum);
								
							Fnc__DRV_LOG(log_msg);							

							if(retry_flag > 0)
							{
								continue;
							}
						}
					}
				}
				else
				{
					int err_flag = 1;

					if(nRecvSize > 1)
					{
						if(szRecvData[1] == ACK)
						{
							err_flag = -1;
						}
					}

					if(err_flag > 0)
					{
						CString log_msg;
						log_msg = "Error : 두개의 ACK가 수신되어야 합니다. Retry 합니다.\n";
							
						Fnc__DRV_LOG(log_msg);

						if(retry_flag > 0)
						{
							continue;
						}
					}
				}
			}
			else
			{
				if(retry_flag < 0)
				{
					check_flag = -1;
				}
				else
				{
					CString log_msg;
					CString log_bff;

					log_msg = "\n";
					log_bff.Format("1. -- Retry Count:%d, And Send Again... --- ", 
						           nCounter);
					log_msg += log_bff;
					log_msg += "\n";

					Fnc__DRV_LOG(log_msg);
					continue;
				}
			}

			if(flag_s_cmmd < 0)
			{
				if(szRecvData[0] == ACK)
				{
					int ack_count = 0;
					int t;

					for(t=1; t<nRecvSize; t++)
					{
						if(szRecvData[t] == ACK)
						{
							ack_count++;
							continue;
						}
						break;
					}

					if(ack_count > 0)
					{
						nRecvSize -= ack_count;
					
						for(t=1;t<nRecvSize;t++)
						{
							szRecvData[t] = szRecvData[t+ack_count];
						}

						// ...
						CString log_msg;
						CString log_bff;

						log_msg = "\n";
						log_bff.Format("Change Recv-Data : (%1d) bytes", ack_count); 
						log_msg += log_bff;
						log_msg += "\n";

						log_msg += "RECV Data : "; 
						for(t=0;t<nRecvSize;t++)
						{
							log_bff.Format("%#X ", szRecvData[t]);
							log_msg += log_bff;
						}
						log_msg += "\n";

						Fnc__DRV_LOG(log_msg);
					}
				}
			}	
			break;
		}
		else
		{
			if(nRecvSize > 0)
			{
				CString log_msg;
				CString log_bff;

				log_msg = "\n";
				log_bff.Format("RECV <= [%s], RecvSize (%d), Timeout Retry (%d), Ret (%d), Expect RecvSize (%d)", 
					           szRecvData, nRecvSize, nCounter, Recv_count, nSizeofRecv);
				log_msg += log_bff;
	
				log_msg += "-- Not Matched RecvSize But Confirm --- ";
				log_msg += "RECV Data : "; 

				for (int i=0; i<nRecvSize; i++)
				{
					log_bff.Format("%#X ", szRecvData[i]);
					log_msg += log_bff;
				}
				log_msg += "\n";

				log_bff.Format("2. -- Retry Count:%d, And Send Again... --- ", 
					           nCounter);
				log_msg += log_bff;

				Fnc__DRV_LOG(log_msg);
			}

			if(retry_flag > 0)
			{
				continue;
			}			
			if(nRecvSize <= 0)
			{
				check_flag = -1;
			}			
			break;
		}
	}
	while(++nCounter < 2);
	
	if((nCounter >= 2) || (check_flag < 0))
	{
		if(dEXT_CH__CFG_MFC_485_COMM_OFFLINE_ALARM_USE->Check__DATA(STR__ENABLE) > 0)
		{
			CString alm_msg;
			CString alm_bff;

			alm_bff.Format("GasID[%1d] Offline ! \n", mac_id);
			alm_msg += alm_bff;
			alm_bff.Format("   Receive Timeout <- %1d msec \n", m_Rcv_Time);
			alm_msg += alm_bff;
			alm_bff.Format("   Retry Count <- %1d \n", nCounter);
			alm_msg += alm_bff;

			mDB__ALM_CTRL.Load__ALM_OFFLINE(mac_id,mfc_index, alm_msg);
		}
		m_nSubOnline[mfc_index] = OFFLINE;

		// ...
		{
			CString log_msg;
			log_msg.Format("Error :: [%d] OFFLINE", mac_id);	

			Fnc__DRV_LOG(log_msg);
		}
		return -1;
	}
	else
	{
		m_nSubOnline[mfc_index] = ONLINE;
	}
	
	return 1;
}

