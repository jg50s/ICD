#include "StdAfx.h"
#include "CObj__HERMOS_SERIAL.h"
#include "CObj__HERMOS_SERIAL__DEF.h"


//------------------------------------------------------------------------------------
int CObj__HERMOS_SERIAL
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__HERMOS_SERIAL
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{

	if(diCH__COMM_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(m_nCommState == OFFLINE)		read_data = "OFFLINE";
		else							read_data = "ONLINE";

		return 1;
	}

	if(diCH__FAILURE_CODE->Check__VARIABLE_NAME(var_name) > 0)
	{
		read_data = sSTR__ERROR_VALUE;
		return 1;
	}

	return -1;
}

int CObj__HERMOS_SERIAL
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString str__log;

	int offline_count = 1;
	int i_checksum1_high;
	int i_checksum1_low;
	int i_checksum2_high;
	int i_checksum2_low;

	CString str__cnv_get_message;
	CString error;

	char ch__my_packet[128];
	int i;

	for(i=0;i<128;i++)
	{
		ch__my_packet[i] = 0;
	}

	//------------------------------------------------------------
	// Reading String

	for(i=0;i<CFG__PAGE_SIZE;i++)
	{
		if(siCH__READ_PAGE_DATA[i]->Check__VARIABLE_NAME(var_name) > 0)
		{
			int page_id = i + 1;
			int retryError = 0;

			do 
			{
				sprintf(ch__my_packet, "S04X%03d%c",
						page_id, CR);
				
				Make_CheckSum(7,
							  ch__my_packet,
							  &i_checksum1_high,
							  &i_checksum1_low,
							  &i_checksum2_high,
							  &i_checksum2_low);

				sprintf(ch__my_packet, "S04X%03d%c%X%X%X%X", 
					    page_id, CR, 
						i_checksum1_high,
						i_checksum1_low,
						i_checksum2_high,
						i_checksum2_low);

				// ...
				str__log.Format("[%s] : [%s] SEND => ", var_name,ch__my_packet);
				Fnc__LOG(str__log);

				if(mX_Serial->DATA__RECV(CR,ch__my_packet,m_Rcv_Time) > 0)
				{
					m_nCommState = ONLINE;
					diCH__COMM_STS->Set__DATA("ONLINE");

					str__log.Format("[%s] : RECV <= [%s]", var_name,ch__my_packet);
					Fnc__LOG(str__log);

					if(ch__my_packet[3] == 'x')
					{				
						Error_Report("0");

						str__cnv_get_message.Format("%s", ch__my_packet);
						int leng = str__cnv_get_message.GetLength();
						if(leng >= 7)  read_data = str__cnv_get_message.Mid(7,16);

						Error_Report("0");
					}
					else
					{
						CString error;
						error.Format("%c",ch__my_packet[5]);
						
						Error_Report(error);

						str__log.Format("Err:%s, ... CH:%s", error, var_name);
						Fnc__LOG(str__log);

						read_data = "PAGE READ ERROR";

						if(retryError > 3)		return 1;
						retryError++;
						continue;
					}

					return 1;         
				}
				else
				{
					str__log.Format("[%s] : RECV_TimeOut <= [%s]", var_name,ch__my_packet);
					Fnc__LOG(str__log);
				}				
			} 
			while(offline_count++ < 3);
			
			m_nCommState = OFFLINE;
			diCH__COMM_STS->Set__DATA("OFFLINE");
			
			read_data = "";
			return -1;
		}
	}

	return -1;
}

//------------------------------------------------------------------------------------
int CObj__HERMOS_SERIAL
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{

	return 1;
}

int CObj__HERMOS_SERIAL
::__Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	CString str__log;

	int offline_count = 1;	
	int i_checksum1_high;
	int i_checksum1_low;
	int i_checksum2_high;
	int i_checksum2_low;
	
	CString str__cnv_get_message;
	char ch__my_packet[128];
	int i;
	int nCount = 0;
	int retVal = 0;

	for(i=0;i<128;i++)
	{
		ch__my_packet[i] = 0;
	}

	CString sTemp;
	dCH__DEVICE_ADDRESS->Get__DATA(sTemp);


	//------------------------------------------------------------
	// DIGITAL : Setting

	if(doCH__HEART_BEAT->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase("OFF") == 0)
		{
			return 1;
		}

		do 
		{
			sprintf(ch__my_packet, "S02H%s%c",sTemp,CR);
		
			Make_CheckSum(5, 
						  ch__my_packet, 
						  &i_checksum1_high, 
						  &i_checksum1_low,
						  &i_checksum2_high,
						  &i_checksum2_low);

			sprintf(ch__my_packet, 
					"S02H%s%c%X%X%X%X", 
					sTemp,
					CR, 
					i_checksum1_high,
					i_checksum1_low,
					i_checksum2_high,
					i_checksum2_low);

			str__log.Format("[%s] : [%s] SEND => ", var_name,ch__my_packet);
			Fnc__LOG(str__log);

			retVal = mX_Serial->DATA__RECV(CR,ch__my_packet,m_Rcv_Time);
			if(retVal > 0)
			{
				m_nCommState = ONLINE;
				diCH__COMM_STS->Set__DATA("ONLINE");

				//.....
				str__log.Format("[%s] : RECV <= [%s]", var_name,ch__my_packet);
				Fnc__LOG(str__log);

				if(ch__my_packet[3] == 'h')
				{
					Error_Report("0");
				}
				else
				{
					CString error;
					error.Format("%c",ch__my_packet[5]);

					Error_Report(error);
					
					str__log.Format("Err:%s, ... CH:%s", error, var_name);
					Fnc__LOG(str__log);
				}
				return 1;
			}
			else
			{
				str__log.Format("retry count:%d/%d, [%s] : RECV_TimeOut <= [%s]", nCount, m_nRetryCount, var_name,ch__my_packet);
				Fnc__LOG(str__log);
			}
		} 
		while (nCount++ < m_nRetryCount);

		m_nCommState = OFFLINE;
		diCH__COMM_STS->Set__DATA("OFFLINE");
	}

	return -1;
}

int CObj__HERMOS_SERIAL
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{
	CString str__log;

	int offline_count=1;	
	int i_checksum1_high;
	int i_checksum1_low;
	int i_checksum2_high;
	int i_checksum2_low;
	
	CString str__cnv_get_message;
	char ch__my_packet[128];
	int i;

	for(i=0;i<128;i++)
	{
		ch__my_packet[i] = 0;
	}
    ZeroMemory(ch__my_packet, sizeof(ch__my_packet));

	CString sTemp;
	dCH__DEVICE_ADDRESS->Get__DATA(sTemp);


	//------------------------------------------------------------
	for(i=0;i<CFG__PAGE_SIZE;i++)
	{
		if(soCH__WRITE_PAGE_DATA[i]->Check__VARIABLE_NAME(var_name) > 0)
		{
			int page_id = i + 1;

			sprintf(ch__my_packet, "S14W%03d%16s%c", page_id,set_data,CR);

			// ...
			int len = strlen(ch__my_packet);
		
			Make_CheckSum(len,
						  ch__my_packet,
						  &i_checksum1_high,
						  &i_checksum1_low,
						  &i_checksum2_high,
						  &i_checksum2_low);
		
			sprintf(ch__my_packet, "S14W%03d%16s%c%X%X%X%X", 
					page_id, set_data, CR,
			        i_checksum1_high,
					i_checksum1_low,
					i_checksum2_high,
					i_checksum2_low);

			str__log.Format("[%s] : [%s] SEND => ",	var_name,ch__my_packet);
			Fnc__LOG(str__log);

			if(mX_Serial->DATA__RECV(CR,ch__my_packet,m_Rcv_Time) > 0)
			{
				m_nCommState = ONLINE;
				diCH__COMM_STS->Set__DATA("ONLINE");

				str__log.Format("[%s] : RECV <= [%s]", var_name,ch__my_packet);
				Fnc__LOG(str__log);

				if(ch__my_packet[3] == 'w')
				{				
					Error_Report("0");
				}
				else
				{
					CString error;
					error.Format("%c",ch__my_packet[5]);

					Error_Report(error);

					str__log.Format("Err:%s, ... CH:%s", error,var_name);
					Fnc__LOG(str__log);
				}

				return 1;
   			}
			else
			{
				str__log.Format("[%s] : RECV_TimeOut <= [%s]", var_name,ch__my_packet);
				Fnc__LOG(str__log);
			}				

			m_nCommState = OFFLINE;
			diCH__COMM_STS->Set__DATA("OFFLINE");
			return -1;
		}
	}

	return -1;
}
