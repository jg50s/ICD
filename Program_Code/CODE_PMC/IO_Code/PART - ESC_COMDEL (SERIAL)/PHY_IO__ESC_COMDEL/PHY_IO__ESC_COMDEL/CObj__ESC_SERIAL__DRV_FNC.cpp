#include "StdAfx.h"
#include "CObj__ESC_SERIAL.h"


//------------------------------------------------------------------------------------
int CObj__ESC_SERIAL
::__Read__ANALOG(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__ESC_SERIAL
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{

	return 1;
}

int CObj__ESC_SERIAL
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString s_cmmd;
	CString r_data;

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "__Read__STRING() ... \n";

		log_bff.Format(" * Var_Name <- [%s] \n", var_name);
		log_msg += log_bff;

		xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
	}

	if((siCH__VOLTAGE_READ->Check__VARIABLE_NAME(var_name) > 0)
	|| (siCH__CURRENT_READ->Check__VARIABLE_NAME(var_name) > 0))
	{
		read_data = "Error";

			 if(siCH__VOLTAGE_READ->Check__VARIABLE_NAME(var_name) > 0)				s_cmmd.Format("%s", CMD__VOLTAGE_READ);
		else if(siCH__CURRENT_READ->Check__VARIABLE_NAME(var_name) > 0)				s_cmmd.Format("%s", CMD__CURRENT_READ);

		int r_len = SEND_COMMAND(var_name, s_cmmd, r_data);
		if(r_len > 0)
		{
			read_data = "OK";

			CString ch_data = _Get__NOT_NUMBER_LEFT_TRIM(r_data);
			
			if(siCH__VOLTAGE_READ->Check__VARIABLE_NAME(var_name) > 0)
			{
				int cur_value = atoi(ch_data);

				ch_data.Format("%1d", cur_value);
				sCH__MON_VOLTAGE_READ->Set__DATA(ch_data);
			}
			else if(siCH__CURRENT_READ->Check__VARIABLE_NAME(var_name) > 0)
			{
				double cur_value = atof(ch_data) * 0.1;

				ch_data.Format("%.1f", cur_value);
				sCH__MON_CURRENT_READ->Set__DATA(ch_data);
			}
		}
		return 1;
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__ESC_SERIAL
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	CString	s_cmmd;
	CString r_data;

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "__Write__ANALOG() ... \n";

		log_bff.Format(" * Var_Name <- [%s] \n", var_name);
		log_msg += log_bff;

		log_bff.Format(" * set_data <- [%.3f] \n", set_data);
		log_msg += log_bff;

		xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
	}

	if((aoCH__VOLTAGE_SET->Check__VARIABLE_NAME(var_name) > 0)
	|| (aoCH__CURRENT_LIMIT_SET->Check__VARIABLE_NAME(var_name) > 0)
	|| (aoCH__RAMP_UP_SET->Check__VARIABLE_NAME(var_name) > 0)
	|| (aoCH__RAMP_DN_SET->Check__VARIABLE_NAME(var_name) > 0))
	{
		if(aoCH__VOLTAGE_SET->Check__VARIABLE_NAME(var_name) > 0)
		{
			int set_value = (int) set_data;

			// ...
			{
				if(set_value > 0)		s_cmmd.Format("%s", CMD__POSITIVE);
				else					s_cmmd.Format("%s", CMD__NEGATIVE);

				SEND_COMMAND(var_name, s_cmmd, r_data);
			}

			int abs_value = set_value;
			if(abs_value < 0)			abs_value = -abs_value;

			s_cmmd.Format("%s%.4d", CMD__VOLTAGE_SET, abs_value);
		}
		else if(aoCH__CURRENT_LIMIT_SET->Check__VARIABLE_NAME(var_name) > 0)
		{
			int set_value = (int) (set_data * 10.0);

			s_cmmd.Format("%s%.3d", CMD__CURRENT_LIMIT_SET, set_value);
		}
		else if(aoCH__RAMP_UP_SET->Check__VARIABLE_NAME(var_name) > 0)
		{
			s_cmmd.Format("%s%3.1f", CMD__RAMP_UP, set_data);
		}
		else if(aoCH__RAMP_DN_SET->Check__VARIABLE_NAME(var_name) > 0)
		{
			s_cmmd.Format("%s%3.1f", CMD__RAMP_DN, set_data);
		}

		return SEND_COMMAND(var_name, s_cmmd, r_data);
	}

	return -1;
}

int CObj__ESC_SERIAL
::__Write__DIGITAL(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	CString s_cmmd;
	CString r_data;

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "__Write__DIGITAL() ... \n";

		log_bff.Format(" * Var_Name <- [%s] \n", var_name);
		log_msg += log_bff;

		log_bff.Format(" * set_data <- [%s] \n", set_data);
		log_msg += log_bff;

		log_bff.Format(" * item_index <- [%1d] \n", item_index);
		log_msg += log_bff;

		xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
	}

	if(doCH__CONTROL_MODE->Check__VARIABLE_NAME(var_name) > 0)
	{
			 if(set_data.CompareNoCase(STR__LOCAL)  == 0)			s_cmmd.Format("%s", CMD__LOCAL);
		else if(set_data.CompareNoCase(STR__REMOTE) == 0)			s_cmmd.Format("%s", CMD__REMOTE);

		return SEND_COMMAND(var_name, s_cmmd, r_data);
	}

	if(doCH__ECHO_MODE->Check__VARIABLE_NAME(var_name) > 0)
	{
			 if(set_data.CompareNoCase(STR__ON)  == 0)				s_cmmd.Format("%s", CMD__ENABLE_ECHO);
		else if(set_data.CompareNoCase(STR__OFF) == 0)				s_cmmd.Format("%s", CMD__DISABLE_ECHO);

		return SEND_COMMAND(var_name, s_cmmd, r_data);
	}

	if(doCH__VOLTAGE_MODE->Check__VARIABLE_NAME(var_name) > 0)
	{
			 if(set_data.CompareNoCase(STR__POSITIVE) == 0)			s_cmmd.Format("%s", CMD__POSITIVE);
		else if(set_data.CompareNoCase(STR__NEGATIVE) == 0)			s_cmmd.Format("%s", CMD__NEGATIVE);

		return SEND_COMMAND(var_name, s_cmmd, r_data);
	}

	if(doCH__VOLTAGE_POWER->Check__VARIABLE_NAME(var_name) > 0)
	{
			 if(set_data.CompareNoCase(STR__ON) == 0)				s_cmmd.Format("%s", CMD__ON);
		else if(set_data.CompareNoCase(STR__OFF) == 0)				s_cmmd.Format("%s", CMD__OFF);

		return SEND_COMMAND(var_name, s_cmmd, r_data);
	}

	return -1;
}

int CObj__ESC_SERIAL
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__ESC_SERIAL::SEND_COMMAND(const CString& var_name, const CString& s_cmd, CString& r_data)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		CString r_bff;
		mX_Serial->CLEAR__BUFFER(&r_bff);
	}

	// ...
	{
		CString s_packet;
		s_packet.Format("%s%c", s_cmd, CR);		

		int s_flag = mX_Serial->DATA__SEND(s_packet);

		// ...
		{
			log_msg.Format("SEND >> \n");

			log_bff.Format("%s<CR>\n", s_cmd);
			log_msg += log_bff;

			//
			log_bff.Format("HEXA (%1d) \n", s_flag);
			log_msg += log_bff;

			int s_len = s_packet.GetLength();
			for(int i=0; i<s_len; i++)
			{
				log_bff.Format("%02X ", 0x0ff & s_packet.GetAt(i));
				log_msg += log_bff;
			}
			log_msg += "\n";

			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// ...
	{
		CString end_str;
		end_str += (char) ECH;		//  ECH : '>'
		// end_str += (char) LF;

		int r_flag = mX_Serial->DATA__RECV(end_str, &r_data, 200);

		if(r_flag < 0)
		{
			log_msg.Format("RECV << (%1d) - ERROR ! \n", r_flag);

			log_bff.Format(" * END_CHAR : 0x%02X \n", end_str.GetAt(0));
			log_msg += log_bff;

			//
			log_bff.Format("ASCII DATA ... \n");
			log_msg += log_bff;

			log_bff.Format(" * [%s] \n", r_data);
			log_msg += log_bff;

			//
			int r_len = r_data.GetLength();

			log_bff.Format("HEXA (%1d) \n", r_len);
			log_msg += log_bff;

			for(int i=0; i<r_len; i++)
			{
				log_bff.Format("%02X ", 0x0ff & r_data.GetAt(i));
				log_msg += log_bff;
			}
			log_msg += "\n";

			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);

			bActive__COMM_ONLINE = false;
			return -1;
		}

		// ...
		{
			log_msg.Format("RECV << (%1d) \n", r_flag);

			log_bff.Format("%s<0x%02X>\n", s_cmd, end_str.GetAt(0));
			log_msg += log_bff;

			//
			log_bff.Format("HEXA (%1d) \n", r_flag);
			log_msg += log_bff;

			for(int i=0; i<r_flag; i++)
			{
				log_bff.Format("%02X ", 0x0ff & r_data.GetAt(i));
				log_msg += log_bff;
			}
			log_msg += "\n";

			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	bActive__COMM_ONLINE = true;
	return 1;
}

CString CObj__ESC_SERIAL::_Get__NOT_NUMBER_LEFT_TRIM(const CString& str_data)
{
	int index__left_trim = -1;

	int i_len = str_data.GetLength();
	int i;

	for(i=0; i<i_len; i++)
	{
		char ch = str_data.GetAt(i);

		if(ch < '0')		continue;
		if(ch > '9')		continue;

		index__left_trim = i;
		break;
	}

	if(index__left_trim <  0)		return "";
	if(index__left_trim == 0)		return str_data;

	CString str_number = str_data;
	str_number.Delete(0, index__left_trim);

	return str_number;
}
