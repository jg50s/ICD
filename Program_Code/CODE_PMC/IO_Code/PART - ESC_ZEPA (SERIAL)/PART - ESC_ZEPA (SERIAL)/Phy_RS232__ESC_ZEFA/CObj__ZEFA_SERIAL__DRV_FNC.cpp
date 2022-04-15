#include "StdAfx.h"
#include "CObj__ZEFA_SERIAL.h"

#include "CCommon_DEF.h"
#include "CCommon_Utility.h"


//------------------------------------------------------------------------------------
int CObj__ZEFA_SERIAL
::__Read__ANALOG(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{
	return 1;
}

int CObj__ZEFA_SERIAL
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{
	return 1;
}

int CObj__ZEFA_SERIAL
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString s_cmmd;
	CString	log_msg;
	CString	log_bff;

	// ...
	{
		log_msg.Format(" * _Read__STRING() : Start ... \n");
		log_bff.Format(" * var_name : %s ", var_name);
		log_msg += log_bff;

		Write__DRV_LOG(log_msg);
	}

	// STAT.READ
	if(siCH__STATE_READ->Check__VARIABLE_NAME(var_name) > 0)
	{
		// Send.Command ...
		{
			s_cmmd.Format("%s%c", CMD__STATE_READ, LF);	    // STAT?
			_Send_Command(var_name, s_cmmd);
		}

		// Receive.Command ...
		CString r_data;

		if(_Recv_Command(&r_data) < 0)
		{
			read_data = "ERROR";
			return 1;
		}

		_Update__INFO_STS(r_data);

		read_data = "OK";
		return 1;
	}

	// ERROR.READ
	if(siCH__ERROR_READ->Check__VARIABLE_NAME(var_name) > 0)
	{
		// Send.Command ...
		{
			s_cmmd.Format("%s%c", CMD__ERROR_READ, LF);	    // SYST:ERR?
			_Send_Command(var_name, s_cmmd);
		}

		// Receive.Command ...
		CString r_data;

		if(_Recv_Command(&r_data) < 0)
		{
			read_data = "ERROR";
			return 1;
		}

		sCH__INFO_ERROR_ID->Set__DATA(r_data);

		read_data = "OK";
		return 1;
	}

	// CFG.VOLT
	if(siCH__CFG_VOLT_ALL->Check__VARIABLE_NAME(var_name) > 0)
	{
		// Send.Command ...
		{
			s_cmmd.Format("%s%c", CMD__CFG_VOLT_READ, LF);	   
			_Send_Command(var_name, s_cmmd);
		}

		// Receive.Command ...
		CString r_data;

		if(_Recv_Command(&r_data) < 0)
		{
			read_data = "ERROR";
			return 1;
		}

		_Update__CFG_VOLT(r_data);

		read_data = "OK";
		return 1;
	}
	// CFG.CURRENT_LIMIT	
	if(siCH__CFG_CURR_LIMIT_ALL->Check__VARIABLE_NAME(var_name) > 0)
	{
		// Send.Command ...
		{
			s_cmmd.Format("%s%c", CMD__CFG_CURRLIMIT_READ, LF);	   
			_Send_Command(var_name, s_cmmd);
		}

		// Receive.Command ...
		CString r_data;

		if(_Recv_Command(&r_data) < 0)
		{
			read_data = "ERROR";
			return 1;
		}

		_Update__CFG_CURRENT_LIMIT(r_data);

		read_data = "OK";
		return 1;
	}
	
	// CFG.RAMP_UP
	if(siCH__CFG_RAMP_UP->Check__VARIABLE_NAME(var_name) > 0)
	{
		// Send.Command ...
		{
			s_cmmd.Format("%s%c", CMD__RAMPUP_READ, LF);	   
			_Send_Command(var_name, s_cmmd);
		}

		// Receive.Command ...
		CString r_data;

		if(_Recv_Command(&r_data) < 0)
		{
			read_data = "ERROR";
			return 1;
		}

		int i_sec = atoi(r_data);
		r_data.Format("%.3f", i_sec/1000.0);
		sCH__INFO_CFG_RAMP_UP_SEC->Set__DATA(r_data);

		read_data = "OK";
		return 1;
	}
	// CFG.RAMP_DOWN
	if(siCH__CFG_RAMP_DOWN->Check__VARIABLE_NAME(var_name) > 0)
	{
		// Send.Command ...
		{
			s_cmmd.Format("%s%c", CMD__RAMPDN_READ, LF);	   
			_Send_Command(var_name, s_cmmd);
		}

		// Receive.Command ...
		CString r_data;

		if(_Recv_Command(&r_data) < 0)
		{
			read_data = "ERROR";
			return 1;
		}

		int i_sec = atoi(r_data);
		r_data.Format("%.3f", i_sec/1000.0);
		sCH__INFO_CFG_RAMP_DOWN_SEC->Set__DATA(r_data);

		read_data = "OK";
		return 1;
	}

	if(siCH__AUTO_TOGGLE_INFO->Check__DATA(var_name) > 0)
	{
		sCH__INFO_AUTO_TOGGLE_COUNT->Set__DATA("__");
		sCH__INFO_AUTO_TOGGLE_VOLTAGE->Set__DATA("__");

		for(int k=0; k<2; k++)
		{
				 if(k == 0)			s_cmmd.Format("%s%c", CMD__AUTO_TOGG_CNT_READ, LF);	   
			else if(k == 1)			s_cmmd.Format("%s%c", CMD__AUTO_TOGG_VOLT_READ, LF);	  
			else					continue;

			// Send.Command ...
			_Send_Command(var_name, s_cmmd);

			// Receive.Command ...
			CString r_data;

			if(_Recv_Command(&r_data) < 0)
			{
				read_data = "ERROR";
				return 1;
			}

				 if(k == 0)			sCH__INFO_AUTO_TOGGLE_COUNT->Set__DATA(r_data);
			else if(k == 1)			sCH__INFO_AUTO_TOGGLE_VOLTAGE->Set__DATA(r_data);
		}

		read_data = "OK";
		return 1;		
	}

	if(siCH__ALL_VERSION_INFO->Check__VARIABLE_NAME(var_name) > 0)
	{
		sCH__INFO_VERSION_FIRMWARE->Set__DATA("__");
		sCH__INFO_VERSION_SOFTWARE->Set__DATA("__");

		for(int k=0; k<2; k++)
		{
				 if(k == 0)			s_cmmd.Format("%s%c", CMD__VERSION_READ, LF);	   
			else if(k == 1)			s_cmmd.Format("%s%c", CMD__IDENTITY, LF);	  
			else					continue;

			// Send.Command ...
			_Send_Command(var_name, s_cmmd);

			// Receive.Command ...
			CString r_data;

			if(_Recv_Command(&r_data) < 0)
			{
				read_data = "ERROR";
				return 1;
			}

				 if(k == 0)			sCH__INFO_VERSION_FIRMWARE->Set__DATA(r_data);
			else if(k == 1)			sCH__INFO_VERSION_SOFTWARE->Set__DATA(r_data);
		}

		read_data = "OK";
		return 1;		
	}

	// ...
	{
		log_msg.Format(" * Variable Error ! \n");
		Write__DRV_LOG(log_msg);
	}
	return -1;
}


//------------------------------------------------------------------------------------
int CObj__ZEFA_SERIAL
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{

	return -1; 
}

int CObj__ZEFA_SERIAL
::__Write__DIGITAL(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	CString	s_cmmd;
	CString	log_msg;
	CString	log_bff;

	// ...
	{
		log_msg.Format(" * %s : Start ... \n", var_name);
		log_bff.Format(" * %s <- %s ", var_name,set_data);
		log_msg += log_bff;

		Write__DRV_LOG(log_msg);
	}

	// ERROR.CLEAR ...
	if(doCH__ERROR_CLEAR->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase(STR__ON) != 0)			return 1;

		s_cmmd.Format("%s%s%c", CMD__ERR_RESET, set_data, LF);
		return _Send_Command(var_name, s_cmmd);
		
		// CMD__IDENTITY
	}
	// SYSTE.RESET ...
	if(doCH__SYSTEM_RESET->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase(STR__ON) != 0)			return 1;

		s_cmmd.Format("%s%s%c", CMD__POWER_RESET, set_data, LF);
		return _Send_Command(var_name, s_cmmd);
	}

	// VOLT.SET : ALL ...
	if(doCH__ALL_VOLT_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		CString ch_data;

		int ch1_volt = (int) aCH__CUR_VOLT_SET_CH1->Get__VALUE();
		int ch2_volt = (int) aCH__CUR_VOLT_SET_CH2->Get__VALUE();

		if(set_data.CompareNoCase(STR__ON) == 0)
		{	
			// OUTPUT.OFF ...
			{
				s_cmmd.Format("%s%s%c", CMD__OUTPUT, STR__OFF, LF);
				_Send_Command(var_name, s_cmmd);
			}

			// ...
			{
				log_msg.Format(" * Command <- [%s]", s_cmmd);
				log_bff.Format(" * ch1_volt <- %.1d \n", ch1_volt);
				log_msg += log_bff;
				log_bff.Format(" * ch2_volt <- %.1d \n", ch2_volt);
				log_msg += log_bff;

				Write__DRV_LOG(log_msg);
			}

			// Volt 극성이 바뀌게 될 경우, Controller 출력이 0V가 되는 Rampdown 0.3초를 기다리기 위해
			Sleep(350);	

			if((ch1_volt == 0) && (ch2_volt == 0))     
			{
				s_cmmd.Format("%s%d,%d%c", CMD__CFG_VOLT_SET, ch1_volt, ch2_volt, LF);    
				 _Send_Command(var_name, s_cmmd);

				log_msg.Format(" * %s : End ... \n", var_name);
				Write__DRV_LOG(log_msg);
				return 1;
			}

			// OUTPUT.ON ...
			s_cmmd.Format("%s%d,%d%s%s%s%c", CMD__CFG_VOLT_SET, ch1_volt, ch2_volt, CMD__LIAISE, CMD__OUTPUT, STR__ON, LF);     // VOLT 2500,-2500;:OUTP ON<LF>

			return _Send_Command(var_name, s_cmmd);
		}
		if(set_data.CompareNoCase(STR__OFF) == 0)
		{
			// OUTPUT.OFF ...
			{
				s_cmmd.Format("%s%s%c", CMD__OUTPUT, STR__OFF, LF);
				_Send_Command(var_name, s_cmmd);

 			}

			// SET.VOLT ...
			{
				s_cmmd.Format("%s%d,%d%c", CMD__CFG_VOLT_SET, 0, 0, LF);    
				_Send_Command(var_name, s_cmmd);
			}
			return 1;
		}
		if(set_data.CompareNoCase(STR__SET) == 0)
		{
			s_cmmd.Format("%s%d,%d%c", CMD__CFG_VOLT_SET, ch1_volt, ch2_volt, LF); 

			return _Send_Command(var_name, s_cmmd);
		}

		log_msg.Format(" * Error : [%s] !", set_data);
		Write__DRV_LOG(log_msg);
		return -11;
	}

	// OUTPUT : ON/OFF ...
	if(doCH__OUTPUT_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		if((set_data.CompareNoCase(STR__ON)  == 0)
		|| (set_data.CompareNoCase(STR__OFF) == 0))
		{
			s_cmmd.Format("%s%s%c", CMD__OUTPUT, set_data, LF);
		}
		else
		{
			log_msg = " * Error !";
			Write__DRV_LOG(log_msg);
			return -11;
		}

		return _Send_Command(var_name, s_cmmd);
	}

	// REMOTE : ON/OFF ...
	if(doCH__REMOTE_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
			 if(set_data.CompareNoCase(STR__ON)  == 0)			s_cmmd.Format("%s%c", CMD__REMOTE, LF);	
		else if(set_data.CompareNoCase(STR__OFF)  == 0)			s_cmmd.Format("%s%c", CMD__LOCAL,  LF);	
		else
		{
			log_msg = " * Error !";
			Write__DRV_LOG(log_msg);
			return -11;
		}

		return _Send_Command(var_name, s_cmmd);
	}

	// TOGGLE : ON/OFF
	if(doCH__TOGGLE_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		if((set_data.CompareNoCase(STR__ON)  == 0)
		|| (set_data.CompareNoCase(STR__OFF) == 0))
		{
			s_cmmd.Format("%s%s%c", CMD__TOGGLE, set_data, LF);
		}
		else
		{
			log_msg = " * Error !";
			Write__DRV_LOG(log_msg);
			return -11;
		}

		return _Send_Command(var_name, s_cmmd);
	}

	// ...
	{
		log_msg.Format(" * Variable Error ! \n");
		Write__DRV_LOG(log_msg);
	}
	return -1;
}

int CObj__ZEFA_SERIAL
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{
	CString s_cmmd;

	CString	log_msg;
	CString log_bff;

	// ...
	{
		log_msg.Format(" * %s : Start ... \n", var_name);
		log_bff.Format(" * %s <- %s ", var_name,set_data);
		log_msg += log_bff;

		Write__DRV_LOG(log_msg);
	}

	// CURR.LIMIT : SET ...
	if(soCH__CURRENT_LIMIT_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		CString cur_data;
		CString	ch1_data;
		CString	ch2_data;
		double	set_value;

		// set command
		{
			cur_data = sCH__CUR_CURRENT_LIMIT_CH1->Get__STRING();
			set_value = atof(cur_data);
			ch1_data.Format("%.4f", set_value / 1000.0);

			cur_data = sCH__CUR_CURRENT_LIMIT_CH2->Get__STRING();
			set_value = atof(cur_data);
			ch2_data.Format("%.4f", set_value / 1000.0);

			s_cmmd.Format("%s%s,%s%c", CMD__CFG_CURRLIMIT_SET, ch1_data, ch2_data, LF);	
		}

		return _Send_Command(var_name, s_cmmd);
	}

	// RAMP.UP : SET ...
	if(soCH__RAMP_UP_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		double  f_value;
		int	    i_value;
		CString	str_msec;

		// set command
		{
			f_value = atof(set_data);
			i_value = (int) (f_value * 1000);
			str_msec.Format("%d", i_value);

			s_cmmd.Format("%s%s%c", CMD__RAMPUP_SET, str_msec, LF);
		}

		return _Send_Command(var_name, s_cmmd);
	}

	// RAMP.DOWN : SET ...
	if(soCH__RAMP_DOWN_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		double	f_value;
		int		i_value;
		CString	str_msec;

		// set command
		{
			f_value = atof(set_data);
			i_value = (int) (f_value * 1000);
			str_msec.Format("%d", (i_value));

			s_cmmd.Format("%s%s%s%s%c", CMD__RAMPDN_SET, str_msec, LF);	
		}

		return _Send_Command(var_name, s_cmmd);
	}

	// AUTO.TOGGLE.COUNT : SET ...
	if(soCH__AUTO_TOGGLE_CNT_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		int	i_value;
		CString	str_count;

		// set command
		{
			i_value = atoi(set_data);
			str_count.Format("%d", i_value);

			s_cmmd.Format("%s%s%c", CMD__AUTO_TOGG_CNT, str_count, LF);	
		}

		return _Send_Command(var_name, s_cmmd);
	}

	// AUTO.TOGGLE.VOLT : SET ...
	if(soCH__AUTO_TOGGLE_VOLT_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		// set command
		{
			s_cmmd.Format("%s%s%c", CMD__AUTO_TOGG_VOLT, set_data, LF);
		}

		return _Send_Command(var_name, s_cmmd);
	}

	return -1;
}

int CObj__ZEFA_SERIAL
::_Send_Command(const CString& var_name, const CString& s_cmmd)
{
	CString cls_bff;
	mX_Serial->CLEAR__BUFFER(&cls_bff);

	int s_len = mX_Serial->DATA__SEND(s_cmmd);

	// ...
	{
		CString log_msg;

		log_msg.Format(" * Command <- [%s]", s_cmmd);
		Write__DRV_LOG(log_msg);

		log_msg.Format(" * %s : End ... \n", var_name);
		Write__DRV_LOG(log_msg);
	}
	return 1;
}
int CObj__ZEFA_SERIAL
::_Recv_Command(CString* p_data)
{
	int recv_msec = 500;

	int r_len = mX_Serial->DATA__RECV(LF, p_data, recv_msec);
	if(r_len < 1)
	{
		CString log_msg;
		log_msg.Format(" * Recv_Error (%1d) \n", r_len);

		Write__DRV_LOG(log_msg);

		sCH__COMM_STS->Set__DATA(STR__OFFLINE);
		return -11;
	}

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg.Format(" * Recv_Data (%1d) \n", p_data->GetLength());

		log_bff.Format(" * %s \n", *p_data);
		log_msg += log_bff;

		Write__DRV_LOG(log_msg);
	}

	sCH__COMM_STS->Set__DATA(STR__ONLINE);
	return 1;
}

int CObj__ZEFA_SERIAL
::_Update__INFO_STS(const CString& r_data)
{
	CCommon_Utility x_utility;
	CStringArray l_para;

	x_utility.Get__StringArrray_From_String(r_data, ";", l_para);

	int i_limit = l_para.GetSize();
	for(int i=0; i<i_limit; i++)
	{
		CString str_para = l_para[i];

		if(i == 0)		// CH1 측정 전압
		{
			if(str_para.GetLength() > 0)		str_para.Delete(0, 1);

			sCH__INFO_STS_VOLT_CH1->Set__DATA(str_para);
			continue;
		}
		if(i == 1)		// CH2 측정 전압
		{
			if(str_para.GetLength() > 0)		str_para.Delete(0, 1);

			sCH__INFO_STS_VOLT_CH2->Set__DATA(str_para);
			continue;
		}
		if(i == 2)		// CH1 측정 전류
		{
			if(str_para.GetLength() > 0)		str_para.Delete(0, 1);

			sCH__INFO_STS_CURRENT_CH1->Set__DATA(str_para);
			continue;
		}
		if(i == 3)		// CH2 측정 전류
		{
			if(str_para.GetLength() > 0)		str_para.Delete(0, 1);

			sCH__INFO_STS_CURRENT_CH2->Set__DATA(str_para);
			continue;
		}
		if(i == 4)		// OUTPUT 상태
		{
			sCH__INFO_STS_OUTPUT->Set__DATA(str_para);
			continue;
		}
		if(i == 5)		// TOGGLE 상태
		{
			sCH__INFO_STS_TOGGLE->Set__DATA(str_para);
			continue;
		}
		if(i == 6)		// REMOTE 상태
		{
			sCH__INFO_STS_REMOTE->Set__DATA(str_para);

			if(str_para.CompareNoCase("1") == 0)		sCH__CUR_REMOTE_STATE->Set__DATA(STR__REMOTE);
			else										sCH__CUR_REMOTE_STATE->Set__DATA(STR__LOCAL);

			continue;
		}
	}

	return 1;
}

int CObj__ZEFA_SERIAL
::_Update__CFG_VOLT(const CString& r_data)
{
	CCommon_Utility x_utility;
	CStringArray l_para;

	x_utility.Get__StringArrray_From_String(r_data, ";", l_para);

	int i_limit = l_para.GetSize();
	for(int i=0; i<i_limit; i++)
	{
		CString str_para = l_para[i];

		if(i == 0)		// CH1 CFG.VOLT
		{
			if(str_para.GetLength() > 0)		str_para.Delete(0, 1);

			sCH__INFO_CFG_VOLT_CH1->Set__DATA(str_para);
			continue;
		}
		if(i == 1)		// CH2 CFG.VOLT
		{
			if(str_para.GetLength() > 0)		str_para.Delete(0, 1);

			sCH__INFO_CFG_VOLT_CH2->Set__DATA(str_para);
			continue;
		}
	}

	return 1;
}

int CObj__ZEFA_SERIAL
::_Update__CFG_CURRENT_LIMIT(const CString& r_data)
{
	CCommon_Utility x_utility;
	CStringArray l_para;

	x_utility.Get__StringArrray_From_String(r_data, ";", l_para);

	int i_limit = l_para.GetSize();
	for(int i=0; i<i_limit; i++)
	{
		CString str_para = l_para[i];

		if(i == 0)		// CH1 CFG.CURRENT_LIMIT
		{
			if(str_para.GetLength() > 0)		str_para.Delete(0, 1);

			sCH__INFO_CFG_CURR_LIMIT_CH1->Set__DATA(str_para);
			continue;
		}
		if(i == 1)		// CH2 CFG.CURRENT_LIMIT
		{
			if(str_para.GetLength() > 0)		str_para.Delete(0, 1);

			sCH__INFO_CFG_CURR_LIMIT_CH2->Set__DATA(str_para);
			continue;
		}
	}

	return 1;
}
