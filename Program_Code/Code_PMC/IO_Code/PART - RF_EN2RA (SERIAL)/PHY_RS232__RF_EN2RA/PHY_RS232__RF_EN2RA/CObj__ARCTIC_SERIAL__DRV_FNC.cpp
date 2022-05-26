#include "StdAfx.h"
#include "CObj__ARCTIC_SERIAL.h"

#include "CCommon_Utility.h"


//------------------------------------------------------------------------------------
int CObj__ARCTIC_SERIAL
::__Read__ANALOG(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__ARCTIC_SERIAL
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{

	return -1;
}

int CObj__ARCTIC_SERIAL
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString s_cmmd;
	CString s_op;
	CString s_data;
	CString r_data;

	if(siCH__ALL_STATE_GET->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "CMD";
		s_op   = "";
		s_data = "";

		int r_flag = _Send__Command(s_cmmd,s_op,s_data, &r_data);
		if(r_flag > 0)
		{
			_Update__CMD_INFO(r_data);
		}

		if(r_flag > 0)			read_data = "OK";
		else					read_data = "ERROR";

		return 1;
	}

	return -1;
}

//------------------------------------------------------------------------------------
int CObj__ARCTIC_SERIAL
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	CString s_packet;
	CString s_cmmd;
	CString s_op;
	CString s_data;
	CString r_data;

	if(aoCH__DIGITAL_POWER_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "VSP";
		s_op   = "=";
		s_data.Format("%.0f", set_data);

		return _Send__Command(s_cmmd,s_op,s_data, &r_data);
	}

	return -1;
}

int CObj__ARCTIC_SERIAL
::__Write__DIGITAL(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	CString s_packet;
	CString s_cmmd;
	CString s_data;
	CString r_data;
	CString s_op;

	if(doCH__DIGITAL_POWER_CTRL->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "VSP";
		s_op   = "";

		if(set_data.CompareNoCase(STR__ON) == 0)		s_data = "1";
		else											s_data = "0";

		_Send__Command(s_cmmd,s_op,s_data, &r_data);		
		return 1;
	}

	if(doCH__PLASMA_ON_ENABLE_TURN_ON->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "VPO";
		s_op   = "";

		if(set_data.CompareNoCase(STR__ON) == 0)		s_data = "1";
		else											s_data = "0";

		_Send__Command(s_cmmd,s_op,s_data, &r_data);		
		return 1;
	}
	if(doCH__PLASMA_ON_ENABLE_OUTPUT_HIGH->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "VPO";
		s_op   = "=";

		if(set_data.CompareNoCase(STR__ON) == 0)		s_data = "1";
		else											s_data = "0";

		_Send__Command(s_cmmd,s_op,s_data, &r_data);		
		return 1;
	}

	return -1;
}

int CObj__ARCTIC_SERIAL
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}


// ...
int CObj__ARCTIC_SERIAL
::_Update__CMD_INFO(const CString& r_data)
{
	CCommon_Utility x_utility;
	CStringArray l_para;

	x_utility.Get__StringArrray_From_String(r_data, ",", l_para);

	int i_limit = l_para.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_para = l_para[i];

			 if(i == 0)			sCH__INFO_DELIVERED_POWER->Set__DATA(str_para);
		else if(i == 1)			sCH__INFO_POWER_SETPOINT->Set__DATA(str_para);
		else if(i == 2)			sCH__INFO_RF_VOLTAGE->Set__DATA(str_para);
		else if(i == 3)			sCH__INFO_RF_CURRENT->Set__DATA(str_para);
		else if(i == 4)			sCH__INFO_DC_VOLTAGE->Set__DATA(str_para);
		else if(i == 5)			sCH__INFO_DC_CURRENT->Set__DATA(str_para);
		else if(i == 6)			sCH__INFO_RF_PHASE->Set__DATA(str_para);
		else if(i == 7)			sCH__INFO_FREQUENCY->Set__DATA(str_para);
		else if(i == 8)			sCH__INFO_QFR->Set__DATA(str_para);
		else if(i == 9)			sCH__INFO_PLASMA_IMPEDANCE_R->Set__DATA(str_para);
		else if(i == 10)		sCH__INFO_PLASMA_IMPEDANCE_X->Set__DATA(str_para);
		else if(i == 11)
		{
			CString str_data;

			int i_sts = atoi(str_para);

			if(i_sts == 1)		str_data = "Ignition ready";
			else if(i_sts == 2)		str_data = "Ignition start";
			else if(i_sts == 3)		str_data = "Ignition failed";
			else if(i_sts == 4)		str_data = "Normal operation";
			else if(i_sts == 5)		str_data = "User off";
			else if(i_sts == 6)		str_data = "Interlock";
			else if(i_sts == 7)		str_data = "DC discharging";
			else					str_data = "Unknown";

			sCH__INFO_RUN_MODE_DATA->Set__DATA(str_para);
			sCH__INFO_RUN_MODE_STATE->Set__DATA(str_data);
		}
		else if(i == 12)
		{
			CString str_data;

			int i_sts = atoi(str_para);

				 if(i_sts == 0)		str_data = "None";
			else if(i_sts == 1)		str_data = "Over power";
			else if(i_sts == 2)		str_data = "Over operation time";
			else if(i_sts == 3)		str_data = "Current fault";
			else if(i_sts == 4)		str_data = "Fan fault";
			else if(i_sts == 5)		str_data = "User off";
			else if(i_sts == 6)		str_data = "Hardware fault";
			else					str_data = "Unknown";

			sCH__INFO_INTERLOCK_DATA->Set__DATA(str_para);
			sCH__INFO_INTERLOCK_STATE->Set__DATA(str_data);
		}
		else if(i == 13)		sCH__INFO_PLASMA_ON_ENABLE_TURN_ON_STATE->Set__DATA(str_para);
		else if(i == 14)		sCH__INFO_PLASMA_ON_ENABLE_OUTPUT_HIGH_STATE->Set__DATA(str_para);
		else if(i == 15)		sCH__INFO_DIGITAL_SET_POWER_STATE->Set__DATA(str_para);
		else if(i == 16)		sCH__INFO_DIGITAL_SET_POWER_VALUE->Set__DATA(str_para);
	}

	return 1;
}

int CObj__ARCTIC_SERIAL
::_Send__Command(const CString& s_packet, CString* p_data)
{
	if(bActive__DRV_FNC_START)
	{
		double cfg__line_sec = aCH__CFG_DRV_LINE_SEDN_DELAY_SEC->Get__VALUE();

		while(xTIMER__DRV_LINE->Get__CURRENT_TIME() < cfg__line_sec)
		{
			Sleep(1);
		}

		/*
		int cfg__line_msec = (int) (cfg__line_sec * 1000);
		Sleep(cfg__line_msec);
		*/
	}

	// Send ...
	{
		double cfg__char_sec = aCH__CFG_DRV_CHAR_SEDN_DELAY_SEC->Get__VALUE();
		int cfg__char_msec = (int) (cfg__char_sec * 1000);

		CString s_string;
		s_string  = s_packet;
		s_string += sEND_SEND;

		if(iActive__SIM_MODE > 0)
		{

		}
		else
		{
			CString cls_bff;
			mX_Serial->CLEAR__BUFFER(&cls_bff);

			int s_len = s_string.GetLength();
			for(int i=0; i<s_len; i++)
			{
				unsigned char s_ch = s_string.GetAt(i);;
				mX_Serial->CHAR__SEND(&s_ch, 1);

				if(cfg__char_msec > 0)		Sleep(cfg__char_msec);
			}
		}

		Write__DRV_LOG("SEND", s_packet);
	}

	if(bActive__DRV_FNC_START)
	{
		xTIMER__DRV_LINE->START__COUNT_UP(9999);
	}
	else
	{
		bActive__DRV_FNC_START = true;

		xTIMER__DRV_LINE->START__COUNT_UP(9999);
	}

	// Recv ...
	{
		CString r_data;
		int r_len = 0;

		if(iActive__SIM_MODE > 0)
		{
			r_data  = s_packet;
			r_data += ",";

			// ...
			CString s_xxx;

			int k_limit = 17;
			for(int k=0; k<k_limit; k++)
			{
				if(k > 0)		r_data += ",";

					 if(k == 11)		s_xxx = "1";
				else if(k == 12)		s_xxx = "2";
				else					s_xxx.Format("%1d", (1000 + k));
				r_data += s_xxx;
			}

			r_len = r_data.GetLength();
		}
		else
		{
			int r_msec = 500;

			r_len = mX_Serial->DATA__RECV(sEND_RECV, &r_data, r_msec);		
		}

		Write__DRV_LOG("RECV", r_data);

		if(r_len <= 0)		
		{
			Write__DRV_LOG("RECV", "ERROR (OFFLINE)");

			dCH__MON_COMM_STS->Set__DATA(STR__OFFLINE);
			return -1;
		}
		else
		{
			dCH__MON_COMM_STS->Set__DATA(STR__ONLINE);
		}

		int s_index = r_data.Find(s_packet);
		if(s_index < 0)
		{
			Write__DRV_LOG("RECV", "ERROR (CMMD NO CHECK)");
			return -11;
		}

		r_data.Delete(s_index, (s_packet.GetLength() + s_index));
		p_data->Format("%s", r_data);
	}

	return p_data->GetLength();
}

int CObj__ARCTIC_SERIAL
::_Send__Command(const CString& s_cmmd,const CString& s_op,const CString& s_data, CString* p_data)
{
	if(bActive__DRV_FNC_START)
	{
		double cfg__line_sec = aCH__CFG_DRV_LINE_SEDN_DELAY_SEC->Get__VALUE();

		while(xTIMER__DRV_LINE->Get__CURRENT_TIME() < cfg__line_sec)
		{
			Sleep(1);
		}

		/*
		int cfg__line_msec = (int) (cfg__line_sec * 1000);
		Sleep(cfg__line_msec);
		*/
	}

	// Send ...
	{
		double cfg__char_sec = aCH__CFG_DRV_CHAR_SEDN_DELAY_SEC->Get__VALUE();
		int cfg__char_msec = (int) (cfg__char_sec * 1000);
		// ...
		CString s_body;
		s_body.Format("%s%s%s", s_cmmd,s_op,s_data);

		CString s_string;
		s_string  = s_body;
		s_string += sEND_SEND;

		if(iActive__SIM_MODE > 0)
		{

		}
		else
		{
			CString cls_bff;
			mX_Serial->CLEAR__BUFFER(&cls_bff);

			int s_len = s_string.GetLength();
			for(int i=0; i<s_len; i++)
			{
				unsigned char s_ch = s_string.GetAt(i);;
				mX_Serial->CHAR__SEND(&s_ch, 1);

				if(cfg__char_msec > 0)		Sleep(cfg__char_msec);
			}
		}

		Write__DRV_LOG("SEND", s_body);
	}

	if(bActive__DRV_FNC_START)
	{
		xTIMER__DRV_LINE->START__COUNT_UP(9999);
	}
	else
	{
		bActive__DRV_FNC_START = true;
		
		xTIMER__DRV_LINE->START__COUNT_UP(9999);
	}

	// Recv ...
	{
		CString r_data;
		int r_len = 0;

		if(iActive__SIM_MODE > 0)
		{
			r_data  = s_cmmd;
			r_data += ",";

			// ...
			CString s_xxx;

			int k_limit = 17;
			for(int k=0; k<k_limit; k++)
			{
				if(k > 0)		r_data += ",";

					 if(k == 11)		s_xxx = "1";
				else if(k == 12)		s_xxx = "2";
				else					s_xxx.Format("%1d", (1000 + k));
				r_data += s_xxx;
			}

			r_len = r_data.GetLength();
		}
		else
		{
			int r_msec = 500;

			r_len = mX_Serial->DATA__RECV(sEND_RECV, &r_data, r_msec);		
		}

		Write__DRV_LOG("RECV", r_data);

		if(r_len <= 0)		
		{
			Write__DRV_LOG("RECV", "ERROR (OFFLINE)");

			dCH__MON_COMM_STS->Set__DATA(STR__OFFLINE);
			return -1;
		}
		else
		{
			dCH__MON_COMM_STS->Set__DATA(STR__ONLINE);
		}

		int s_index = r_data.Find(s_cmmd);
		if(s_index < 0)
		{
			Write__DRV_LOG("RECV", "ERROR (CMMD NO CHECK)");
			return -11;
		}

		r_data.Delete(s_index, (s_cmmd.GetLength() + s_index));
		p_data->Format("%s", r_data);
	}

	return p_data->GetLength();
}
