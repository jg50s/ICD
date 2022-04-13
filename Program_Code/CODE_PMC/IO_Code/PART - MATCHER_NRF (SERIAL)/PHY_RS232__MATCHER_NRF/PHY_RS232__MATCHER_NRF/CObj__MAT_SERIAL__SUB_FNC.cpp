#include "StdAfx.h"
#include "CObj__MAT_SERIAL.h"
#include "CObj__MAT_SERIAL__DEF.h"


int CObj__MAT_SERIAL
::Fnc__PRESET_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "\n";
		log_msg += "Preset Set Info ... \n";

		log_bff.Format(" * %s <- %s \n", 
						aCH__PARA_LOAD_POS->Get__CHANNEL_NAME(),
						aCH__PARA_LOAD_POS->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__PARA_TUNE_POS->Get__CHANNEL_NAME(),
						aCH__PARA_TUNE_POS->Get__STRING());
		log_msg += log_bff;

		Write__APP_LOG(log_msg);	
	}

	if(iActive__SIM_MODE > 0)
	{
		ch_data = aCH__PARA_LOAD_POS->Get__STRING();
		sCH__MON_LOAD_POS_SET->Set__DATA(ch_data);

		ch_data = aCH__PARA_TUNE_POS->Get__STRING();
		sCH__MON_TUNE_POS_SET->Set__DATA(ch_data);

		ch_data = STR__AUTO;
		sCH__MON_CONTROL_SET->Set__DATA(ch_data);
		sCH__INFO_STS_MAT_AUTO_MATCHING_STATE->Set__DATA(ch_data);
	}
	else
	{
		aCH__PARA_LOAD_POS->Get__DATA(ch_data);
		aoCH__LOAD_PRESET->Set__DATA(ch_data);

		aCH__PARA_TUNE_POS->Get__DATA(ch_data);
		aoCH__TUNE_PRESET->Set__DATA(ch_data);
	}

	return 1;
}

int CObj__MAT_SERIAL
::Fnc__MANUAL_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "\n";
		log_msg += "Preset Set Info ... \n";

		log_bff.Format(" * %s <- %s \n", 
						aCH__PARA_LOAD_POS->Get__CHANNEL_NAME(),
						aCH__PARA_LOAD_POS->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__PARA_TUNE_POS->Get__CHANNEL_NAME(),
						aCH__PARA_TUNE_POS->Get__STRING());
		log_msg += log_bff;

		Write__APP_LOG(log_msg);	
	}

	if(iActive__SIM_MODE > 0)
	{
		ch_data = aCH__PARA_LOAD_POS->Get__STRING();
		sCH__MON_LOAD_POS_SET->Set__DATA(ch_data);

		ch_data = aCH__PARA_TUNE_POS->Get__STRING();
		sCH__MON_TUNE_POS_SET->Set__DATA(ch_data);

		ch_data = STR__MANUAL;
		sCH__MON_CONTROL_SET->Set__DATA(ch_data);
		sCH__INFO_STS_MAT_AUTO_MATCHING_STATE->Set__DATA(ch_data);
	}
	else
	{
		aCH__PARA_LOAD_POS->Get__DATA(ch_data);
		aoCH__LOAD_MANUAL->Set__DATA(ch_data);

		aCH__PARA_TUNE_POS->Get__DATA(ch_data);
		aoCH__TUNE_MANUAL->Set__DATA(ch_data);
	}

	return 1;
}


// ...
unsigned char CObj__MAT_SERIAL
::_Set_CheckSum(unsigned char* s_cmmd, const int s_len)
{
	unsigned char ch_cs = 0;

	for(int i=1; i<s_len ; i++)  
	{	
		ch_cs = ch_cs ^ s_cmmd[i];
	}
	return ch_cs;
}

int  CObj__MAT_SERIAL
::_Check_ErrorCode(unsigned char err_code)
{
	if(err_code == 0x01)		return 1;

	CString str_err = _Get_ErrorCode(err_code);

	sCH__INFO_LAST_ERROR_CODE->Set__DATA(str_err);
	return -1;
}
CString CObj__MAT_SERIAL
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

int CObj__MAT_SERIAL
::_Send__Command(const byte addr_id,const byte cmmd_id, const byte data_0,const byte data_1)
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
			s_cmmd[s_len++] = 0x06;

			s_cmmd[s_len++] = 0xff & addr_id; //0x40
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
			CString s_msg;
			CString s_bff;

			mX_Serial->CLEAR__BUFFER(&cls_bff);

			int nflag = mX_Serial->CHAR__SEND(s_cmmd, s_len);

			s_msg = "Send_Data ... %d \n,",nflag;

			for(int i=0; i<s_len; i++)
			{
				s_bff.Format("%02X ", s_cmmd[i]);
				s_msg += s_bff;
			}

			Write__DRV_LOG(s_msg);

			return nflag;
		}

		Sleep(100);
	}
	while(++n_cnt <= m_RetryCnt);

	dCH__MON_COMM_STS->Set__DATA(STR__OFFLINE); 
	return -1;
}

int CObj__MAT_SERIAL
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
			s_cmmd[s_len++] = 0x06;

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

int CObj__MAT_SERIAL
::_Send__Command(const byte addr_id,const byte cmmd_id, const byte data_00)
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
			s_cmmd[s_len++] = 0x06;

			s_cmmd[s_len++] = 0xff & addr_id;
			s_cmmd[s_len++] = 0xff & cmmd_id;

			s_cmmd[s_len++] = 0xff & data_00;

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

		// Send Data ...
		{
			CString s_msg;
			CString s_bff;
			CString cls_bff;

			mX_Serial->CLEAR__BUFFER(&cls_bff);

			int nflag = mX_Serial->CHAR__SEND(s_cmmd, s_len);

			s_msg = "Send_Data ... %d \n,",nflag;

			for(int i=0; i<s_len; i++)
			{
				s_bff.Format("%02X ", s_cmmd[i]);
				s_msg += s_bff;
			}

			Write__DRV_LOG(s_msg);

			return nflag;
		}

		Sleep(100);
	}
	while(++n_cnt <= m_RetryCnt);

	dCH__MON_COMM_STS->Set__DATA(STR__OFFLINE); 
	return -1;
}

// ...
void CObj__MAT_SERIAL
::_Update__MAT_State(unsigned char data_0, unsigned char data_1)
{
	CString ch_data;
	unsigned char bit_sts;

	// BYTE : 0
	{
		ch_data.Format("%02X", data_0);
		sCH__INFO_STS_HEXA_0->Set__DATA(ch_data);

		// BIT [0] : Auto Matching State
		{
			bit_sts = 0x01 & data_0;

			/*
			if(0 == bit_sts)	ch_data = STR__STAND_BY;
			else				ch_data = STR__AUTO_ON;
			*/
			if(0 == bit_sts)	ch_data = "AUTO";
			else				ch_data = "MANUAL";

			sCH__INFO_STS_MAT_AUTO_MATCHING_STATE->Set__DATA(ch_data);
		}

		// BIT [2] : Panel
		{
			bit_sts = 0x04 & data_0;

			if(0 == bit_sts)	ch_data = STR__NORMAL;
			else				ch_data = STR__ABNORMAL;

			sCH__INFO_STS_MAT_PANEL->Set__DATA(ch_data);
		}

		// BIT [3] : RF ON
		{
			bit_sts = 0x08 & data_0;

			if(0 == bit_sts)	ch_data = STR__OFF;
			else				ch_data = STR__ON;

			sCH__INFO_STS_MAT_RF->Set__DATA(ch_data);
		}
	}

	// BYTE : 1
	{
		ch_data.Format("%02X", data_1);
		sCH__INFO_STS_HEXA_1->Set__DATA(ch_data);

		// BIT [0] : Motor Error
		{
			bit_sts = 0x01 & data_1;

			if(0 == bit_sts)	ch_data = STR__NORMAL;
			else				ch_data = STR__ABNORMAL;

			sCH__INFO_STS_MAT_MOTOR_ERROR->Set__DATA(ch_data);
		}

		// BIT [2] : Temp
		{
			bit_sts = 0x04 & data_1;

			if(0 == bit_sts)	ch_data = STR__NORMAL;
			else				ch_data = STR__ABNORMAL;

			sCH__INFO_STS_MAT_TEMP->Set__DATA(ch_data);
		}

		// BIT [3] : Matching
		{
			bit_sts = 0x8 & data_1;
			if(0 == bit_sts)	ch_data = STR__NOT_MATCHED;
			else				ch_data = STR__MATCHED;
			
			sCH__INFO_STS_MAT_MATCHING->Set__DATA(ch_data);
		}
	}
}

void CObj__MAT_SERIAL
::_Updata__MAT_VRMS_IRMS(unsigned char data_0, unsigned char data_1, unsigned char data_2, unsigned char data_3)
{
	CString		ch_data;
	byte data0,data1,data2,data3;
	double pwr_value, pwr_value_1 = 0.0;

	_DATA__2BYTE_INT data_pwr;
	data_pwr._hexa = 0;

	data0 = data_0;
	data1 = data_1;
	data2 = data_2;
	data3 = data_3;

	// IRMS 0~15 Bit... 
	{
		data_pwr._byte[0] = data0;
		data_pwr._byte[1] = data1;

		pwr_value = (data_pwr._hexa / (double) iHEXA__PWR_MAX_10) * dVALUE__PWR_MAX_10;
		pwr_value_1 = pwr_value * dVALUE__PWR_MAX_10;
		ch_data.Format("%.1f", pwr_value_1);
		sCH__INFO_IRMS->Set__DATA(ch_data);
	}

	// VRMS 16~31 Bit...
	{
		data_pwr._hexa = 0;

		data_pwr._byte[0] = data2;
		data_pwr._byte[1] = data3;

		pwr_value = (data_pwr._hexa / (double) iHEXA__PWR_MAX_10) * dVALUE__PWR_MAX_10;
		pwr_value_1 = pwr_value * dVALUE__PWR_MAX_10;
		ch_data.Format("%.1f", pwr_value_1);
		sCH__INFO_VRMS->Set__DATA(ch_data);
	}
}

void CObj__MAT_SERIAL
::_Updata__MAT_START_STOP_SWR(unsigned char data_0, unsigned char data_1, unsigned char data_2, unsigned char data_3)
{
	CString		ch_data;
	byte data0,data1,data2,data3;
	double pwr_value, pwr_value_1 = 0.0;

	_DATA__2BYTE_INT data_pwr;
	data_pwr._hexa = 0;

	data0 = data_0;
	data1 = data_1;
	data2 = data_2;
	data3 = data_3;

	// Start SWR 0~15 Bit...
	{
		data_pwr._byte[0] = data0;
		data_pwr._byte[1] = data1;

		pwr_value = (data_pwr._hexa / (double) iHEXA__PWR_MAX_100) * dVALUE__PWR_MAX_100;
		pwr_value_1 = pwr_value * dVALUE__PWR_MAX_100;
		ch_data.Format("%d", pwr_value_1);
		sCH__INFO_START_SWR->Set__DATA(ch_data);
	}

	// Stop SWR 16~31 Bit...
	{
		data_pwr._hexa = 0;

		data_pwr._byte[0] = data2;
		data_pwr._byte[1] = data3;

		pwr_value = (data_pwr._hexa / (double) iHEXA__PWR_MAX_100) * dVALUE__PWR_MAX_100;
		pwr_value_1 = pwr_value * dVALUE__PWR_MAX_100;
		ch_data.Format("%d", pwr_value_1);
		sCH__INFO_STOP_SWR->Set__DATA(ch_data);
	}
}

void CObj__MAT_SERIAL
::_Updata__MAT_SWR(unsigned char data_0, unsigned char data_1, unsigned char data_2)
{
	CString		ch_data;
	byte data0,data1,data2;
	double pwr_value, pwr_value_1 = 0.0;

	_DATA__2BYTE_INT data_pwr;
	data_pwr._hexa = 0;

	data0 = data_0;
	data1 = data_1;
	data2 = data_2;
	
	// Sign 0~7 Bit...
	boolean bSB = (data0 & 0x01);

	// Cur SWR 8~23 Bit...
	data_pwr._byte[0] = data1;
	data_pwr._byte[1] = data2;


	pwr_value = (data_pwr._hexa / (double) iHEXA__PWR_MAX_100) * dVALUE__PWR_MAX_100;
	pwr_value_1 = pwr_value * dVALUE__PWR_MAX_100;

	if(bSB)	ch_data.Format("-%d", pwr_value_1);
	else	ch_data.Format("%d", pwr_value_1);

	sCH__INFO_CUR_SWR->Set__DATA(ch_data);
}

void CObj__MAT_SERIAL
::_Updata__MAT_PHASE_SHIFT(unsigned char data_0, unsigned char data_1, unsigned char data_2)
{
	CString		ch_data;
	byte data0,data1,data2;
	double pwr_value, pwr_value_1 = 0.0;

	_DATA__2BYTE_INT data_pwr;
	data_pwr._hexa = 0;

	data0 = data_0;
	data1 = data_1;
	data2 = data_2;

	// Sign 0~7 Bit...
	boolean bSB = (data0 & 0x01);

	// Phase Shift 8~23 Bit...
	data_pwr._byte[0] = data1;
	data_pwr._byte[1] = data2;

	pwr_value = (data_pwr._hexa / (double) iHEXA__PWR_MAX_10) * dVALUE__PWR_MAX_10;
	pwr_value_1 = pwr_value * dVALUE__PWR_MAX_10;

	if(bSB)	ch_data.Format("-%d", pwr_value_1);
	else	ch_data.Format("%d", pwr_value_1);

	sCH__INFO_PHASE_SHIFT->Set__DATA(ch_data);

}

void CObj__MAT_SERIAL
::_Updata__MAT_IMPEDANCE(unsigned char data_0, unsigned char data_1, unsigned char data_2, unsigned char data_3, unsigned char data_4)
{
	CString		ch_data;
	byte data0,data1,data2,data3,data4;
	double pwr_value, pwr_value_1 = 0.0;

	_DATA__2BYTE_INT data_pwr;
	data_pwr._hexa = 0;

	data0 = data_0;
	data1 = data_1;
	data2 = data_2;
	data3 = data_3;
	data4 = data_4;

	// Sign 0~7 Bit...
	boolean bSB = (data0 & 0x01);

	// Real Impedance 8~23 Bit...
	{
		data_pwr._byte[0] = data1;
		data_pwr._byte[1] = data2;

		pwr_value = (data_pwr._hexa / (double) iHEXA__PWR_MAX_10) * dVALUE__PWR_MAX_10;
		pwr_value_1 = pwr_value * dVALUE__PWR_MAX_10;

		if(bSB)	ch_data.Format("-%d", pwr_value_1);
		else	ch_data.Format("%d", pwr_value_1);

		sCH__INFO_REAL_IMPEDANCE->Set__DATA(ch_data);
	}

	// Imaginary Impedance 24~39 Bit...
	{
		data_pwr._hexa = 0;

		data_pwr._byte[0] = data1;
		data_pwr._byte[1] = data2;

		pwr_value = (data_pwr._hexa / (double) iHEXA__PWR_MAX_10) * dVALUE__PWR_MAX_10;
		pwr_value_1 = pwr_value * dVALUE__PWR_MAX_10;

		if(bSB)	ch_data.Format("-%d", pwr_value_1);
		else	ch_data.Format("%d", pwr_value_1);

		sCH__INFO_IMAGE_IMPEDANCE->Set__DATA(ch_data);
	}
}