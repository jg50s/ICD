#include "StdAfx.h"

#include "CObj_Phy__ESC_ZEFA.h"
//#include "CObj_Phy__ESC_ZEFA__DEF.h"
#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA
::__Read__ANALOG(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{
	return 1;
}


//------------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{
	return 1;
}


//------------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	return 1;
}


//------------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	Write__DRV_LOG("Write__Analog_start");

	CString			cmd;
	CString			command;
	CString			ch1_data = "";
	CString			ch2_data = "";
	int				n_cnt = 1;
	int				r_len;
	int				s_len;
	CString			log_msg;
	CString			str;
	CString			r_data;
	CStringArray	r_value;

	// Volt Set
	if((var_name.CompareNoCase(aoCH__VOLT_SET_CH1->Get__VARIABLE_NAME()) == 0) ||
		(var_name.CompareNoCase(aoCH__VOLT_SET_CH2->Get__VARIABLE_NAME()) == 0))
	{
		Write__DRV_LOG("volt_set_start");

		int	ch1_value;
		int ch2_value;
		int	buf;
		int ch = 1;

		if (var_name.CompareNoCase(aoCH__VOLT_SET_CH1->Get__VARIABLE_NAME()) == 0)
		{
			ch = 1;
			ch1_value = (int) set_data;
			ch1_data.Format("%d", ch1_value);
			aCH__VOLT_SET_CH2->Get__DATA(ch2_data);
			ch2_value = atoi(ch2_data);
			ch2_data.Format("%d", ch2_value);
		}
		else
		{
			ch = 2;
			ch2_value = (int) set_data;
			aCH__VOLT_SET_CH1->Get__DATA(ch1_data);
			ch1_value = atoi(ch1_data);
		}

		{
			CString cls_bff;

			{
				// OUTPUT OFF
				// set command
				cmd.Format("%s%s%c", CMD__OUTPUT, MODE__OFF, end_str);	// OUTP OFF<LF>				
				command = cmd;

				// send command
				log_msg.Format("OUTPUT_%s_SEND", MODE__OFF);
				Write__DRV_LOG(log_msg);
				mX_Serial->CLEAR__BUFFER(&cls_bff);
				s_len = mX_Serial->DATA__SEND(command);
			}
			Sleep(300);
			{
				// VOLT SET
				// set command
				cmd.Format("%s%d,%d%c", CMD__VOLT_SET, ch1_value, ch2_value, end_str);	// VOLT 2500,-2500<LF>
				command = cmd;
				
				// send command
				Write__DRV_LOG("VOLT_SET_SEND");
				mX_Serial->CLEAR__BUFFER(&cls_bff);
				s_len = mX_Serial->DATA__SEND(command);

				log_msg.Format("command[%s]", command);
				Write__DRV_LOG(log_msg);
			}
			Sleep(300);
			{
				if ((ch1_value != 0) && (ch2_value != 0))
				{
					// OUTPUT ON
					// set command
					cmd.Format("%s%s%c", CMD__OUTPUT, MODE__ON, end_str);	// OUTP ON<LF>				
					command = cmd;

					// send command
					log_msg.Format("OUTPUT_%s_SEND", MODE__ON);
					Write__DRV_LOG(log_msg);
					mX_Serial->CLEAR__BUFFER(&cls_bff);
					s_len = mX_Serial->DATA__SEND(command);
				}
				else
				{
					log_msg.Format("OUTPUT_NOT_ON : SetVolt is '0'");
					Write__DRV_LOG(log_msg);
				}
			}

			aCH__VOLT_SET_CH1->Set__DATA(ch1_data);
			aCH__VOLT_SET_CH2->Set__DATA(ch2_data);

			Write__DRV_LOG("volt_set_end");
			return 1;
		}
	}

	Write__DRV_LOG("Write__Analog_end");
	return 1; 
}


//------------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA
::__Write__DIGITAL(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	Write__DRV_LOG("Write__Digital_start");

	CString			cmd;
	CString			command;
	CString			ch1_data = "";
	CString			ch2_data = "";
	int				n_cnt = 1;
	int				r_len;
	int				s_len;
	CString			log_msg;
	CString			str;
	CString			r_data;

	do
	{
		{
			r_data = "";
		}

		// OUTPUT ON/OFF	// doCH__OUTPUT에서 On/Off만 진행할 경우.
		if(var_name.CompareNoCase(doCH__OUTPUT->Get__VARIABLE_NAME()) == 0)
		{
			CString data;
			
			// doCH__OUTPUT에서 On/Off만 진행할 경우.
			// Output On
			{

				// set command
				{
					if (dCH__CFG_NEED_REPLY->Check__DATA(MODE__ON) > 0)
					{
						cmd.Format("%s%s%s%s%c", CMD__OUTPUT, set_data, CMD__LIAISE, CMD__OUTPUT_STATE_READ, end_str);	// OUTP ON;:OUTP?<LF> or OUTP OFF;:OUTP?<LF>
					}
					else
					{
						cmd.Format("%s%s%c", CMD__OUTPUT, set_data, end_str);	// OUTP ON<LF> orOUTP OFF<LF>
					}
					command = cmd;
				}

				// send command
				{
					CString cls_bff;
					log_msg.Format("Write_Digital_OUTPUT_%s_SEND", set_data);
					Write__DRV_LOG(log_msg);
					mX_Serial->CLEAR__BUFFER(&cls_bff);
					s_len = mX_Serial->DATA__SEND(command);
				}
			}

			log_msg.Format("SND : [%s], s_len[%d]", command, s_len);
			Write__DRV_LOG(log_msg);

			return 1;

		}

		// TOGGLE ON/OFF
		if(var_name.CompareNoCase(doCH__TOGGLE->Get__VARIABLE_NAME()) == 0)
		{
			CString data;

			// set command
			{
				if (dCH__CFG_NEED_REPLY->Check__DATA(MODE__ON) > 0)
				{
					cmd.Format("%s%s%s%s%c", CMD__TOGGLE, set_data, CMD__LIAISE, CMD__TOGGLE_STATE_READ, end_str);	// TOGG ON;:TOGG?<LF> or TOGG OFF;:TOGG?<LF>				
				}
				else
				{
					cmd.Format("%s%s%c", CMD__TOGGLE, set_data, end_str);	// TOGG ON<LF> or TOGG OFF<LF>				
				}
				command = cmd;
			}

			// send command
			{
				CString cls_bff;
				log_msg.Format("Write_Digital_TOGGLE_%s_SEND", set_data);
				Write__DRV_LOG(log_msg);
				mX_Serial->CLEAR__BUFFER(&cls_bff);
				s_len = mX_Serial->DATA__SEND(command);
			}

			//{
			//	if (Command_Recv(command, &r_data) < 0)
			//	{
			//		log_msg.Format("Write_Digital_TOGGLE_%s_Command_Send_NG", set_data);
			//		Write__DRV_LOG(log_msg);
			//		return -1;
			//	}

			//	r_len = r_data.GetLength();
			//}

			// recv data 처리
			{
				if (dCH__CFG_NEED_REPLY->Check__DATA(MODE__OFF) > 0)
				{
					return 1;
				}
				
				// receive data
				{
					r_len = mX_Serial->DATA__RECV(end_str, &r_data, m_Rcv_Time);
					log_msg.Format("Write_Digital_TOGGLE_%s_RECV", set_data);
					Write__DRV_LOG(log_msg);
				}

				if (r_len > -1)
				{
					Recv_Data_Single(r_data, &data);

					if		(data.CompareNoCase(STS__ON) == 0)
					{
						dCH__TOGGLE->Set__DATA(MODE__ON);
						sCH__TOGGLE_STATUS->Set__DATA(MODE__ON);
					}
					else if (data.CompareNoCase(STS__OFF) == 0)
					{
						dCH__TOGGLE->Set__DATA(MODE__OFF);
						sCH__TOGGLE_STATUS->Set__DATA(MODE__OFF);
					}

					log_msg.Format("SND : [%s], RCV : [%s], RCV_Len : [%d], s_flag[%d]", command, r_data, r_len, s_len);
					Write__DRV_LOG(log_msg);

					return 1;
				}
			}
		}

		// REMOTE/LOCAL
		if(var_name.CompareNoCase(doCH__LOCAL_REMOTE->Get__VARIABLE_NAME()) == 0)
		{
			// set command
			{
				if		(set_data.CompareNoCase(MODE__REMOTE) == 0)
				{
					cmd.Format("%s%c", CMD__REMOTE, end_str);	// SYST:REM<LF>			
				}
				else if (set_data.CompareNoCase(MODE__LOCAL) == 0)
				{
					cmd.Format("%s%c", CMD__LOCAL, end_str);	// SYST:LOC<LF>			
				}
				command = cmd;
			}

			// send command
			{
				CString cls_bff;
				log_msg.Format("Write_Digital_%s_SEND", set_data);
				Write__DRV_LOG(log_msg);
				mX_Serial->CLEAR__BUFFER(&cls_bff);
				s_len = mX_Serial->DATA__SEND(command);
			}

			//{
			//	if (Command_Send(command) < 0)
			//	{
			//		log_msg.Format("Write_Digital_TOGGLE_%s_Command_Send_NG", set_data);
			//		Write__DRV_LOG(log_msg);
			//		return -1;
			//	}
			//}

			if (s_len < 0)
			{
				Write__DRV_LOG("RS232 REMOTE NG");
				return -1;
			}

			log_msg.Format("SND : [%s], s_flag[%d]", command, s_len);
			Write__DRV_LOG(log_msg);

			return 1;
		}
	}
	while (++n_cnt <= m_RetryCnt);

	if (n_cnt > m_RetryCnt)
	{	
		log_msg.Format("Write_Analog Receive Data NG_Retry Over - SND : [%s], RCV : [%s], RCV_Len : [%d], s_flag[%d]", cmd, r_data, r_len, s_len);
		Write__DRV_LOG(log_msg);
		return -1;
	}

	Write__DRV_LOG("Write__Digital_end");
	return -1;
}


//------------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{
	Write__DRV_LOG("Write__String_start");

	CString			cmd;
	CString			command;
	CString			ch1_data = "";
	CString			ch2_data = "";
	int				n_cnt = 1;
	int				r_len;
	int				s_len;
	CString			log_msg;
	CString			str;
	CString			r_data;
	CStringArray	r_value;
	int				ch1_volt = 0;
	int				ch2_volt = 0;

	do
	{
		{
			r_data = "";
			r_value.RemoveAll();
		}
		
		// Volt Set
		if(var_name.CompareNoCase(sCH__VOLT_SET_ALL->Get__VARIABLE_NAME()) == 0)
		{
			log_msg.Format("volt_set_all_start : %s", set_data);
			Write__DRV_LOG(log_msg);

			aCH__VOLT_SET_CH1->Get__DATA(ch1_data);
			aCH__VOLT_SET_CH2->Get__DATA(ch2_data);
			ch1_volt = atoi(ch1_data);
			ch2_volt = atoi(ch2_data);

			CString cls_bff;
			if (set_data.CompareNoCase(MODE__ON) == 0)
			{		
				{
					// OUTPUT OFF
					// set command
					cmd.Format("%s%s%c", CMD__OUTPUT, MODE__OFF, end_str);	// OUTP OFF<LF>				
					command = cmd;

					// send command
					mX_Serial->CLEAR__BUFFER(&cls_bff);
					s_len = mX_Serial->DATA__SEND(command);

					log_msg.Format("command[%s]",command);
					Write__DRV_LOG(log_msg);

					log_msg.Format("OUTPUT_%s_SEND", MODE__OFF);
					Write__DRV_LOG(log_msg);

					Sleep(350);	// Volt 극성이 바뀌게 될 경우, Controller 출력이 0V가 되는 Rampdown 0.3초를 기다리기 위해

					// VOLT SET + OUTPUT ON
					if ((ch1_volt == 0) && (ch2_volt == 0))		// set값이 0일 경우, Output On하지 않는다.
					{
						log_msg.Format("OUTPUT_NOT_ON : SetVolt is '0'");
						Write__DRV_LOG(log_msg);
					}
					else
					{
						// set command
						cmd.Format("%s%d,%d%s%s%s%c", CMD__VOLT_SET, ch1_volt, ch2_volt, CMD__LIAISE, CMD__OUTPUT, MODE__ON, end_str);	// VOLT 2500,-2500;:OUTP ON<LF>
						command = cmd;

						// send command
						mX_Serial->CLEAR__BUFFER(&cls_bff);
						s_len = mX_Serial->DATA__SEND(command);

						log_msg.Format("SET + ON - command[%s]", command);
						Write__DRV_LOG(log_msg);
					}
				}	
			}
			else if (set_data.CompareNoCase(MODE__OFF) == 0)
			{
				// OUTPUT OFF
				// set command
				cmd.Format("%s%s%c", CMD__OUTPUT, MODE__OFF, end_str);	// OUTP OFF<LF>	
				command = cmd;

				// send command
				mX_Serial->CLEAR__BUFFER(&cls_bff);
				s_len = mX_Serial->DATA__SEND(command);
			}
			else if (set_data.CompareNoCase("set") == 0)
			{
				// set command
				cmd.Format("%s%d,%d%c", CMD__VOLT_SET, ch1_volt, ch2_volt, end_str);	// VOLT 2500,-2500<LF>
				command = cmd;

				// send command
				mX_Serial->CLEAR__BUFFER(&cls_bff);
				s_len = mX_Serial->DATA__SEND(command);
			}
		
			log_msg.Format("volt_set_all_end : %s", set_data);
			Write__DRV_LOG(log_msg);

			return 1;
		}

		// CurrLimit Set
		if(var_name.CompareNoCase(soCH__CURRLIMIT_SET->Get__VARIABLE_NAME()) == 0)
		{
			log_msg.Format("current_limit_set_start : %s", set_data);
			Write__DRV_LOG(log_msg);

			CString	ch_data;
			double	value;
			double	buf;
						
			//// set command
			//{
			//	value = atof(set_data);
			//	ch1_data.Format("%.4f", value / 1000);
			//	ch2_data.Format("%.4f", value / 1000);
			//	cmd.Format("%s%s,%s%s%s%c", CMD__CURRLIMIT_SET, ch1_data, ch2_data, CMD__LIAISE, CMD__CURRLIMIT_READ, end_str);	// CONF:CURR 0.001,0.001;:CONF:CURR? (@1,2)<LF>
			//	command = cmd;
			//}

			// set command
			{
				aCH__CURRLIMIT_SET_CH1->Get__DATA(ch_data);
				value = atof(ch_data);
				ch1_data.Format("%.4f", value / 1000);
				aCH__CURRLIMIT_SET_CH2->Get__DATA(ch_data);
				value = atof(ch_data);
				ch2_data.Format("%.4f", value / 1000);

				if (dCH__CFG_NEED_REPLY->Check__DATA(MODE__ON) > 0)
				{
					cmd.Format("%s%s,%s%s%s%c", CMD__CURRLIMIT_SET, ch1_data, ch2_data, CMD__LIAISE, CMD__CURRLIMIT_READ, end_str);	// CONF:CURR 0.001,0.001;:CONF:CURR? (@1,2)<LF>
				}
				else
				{
					cmd.Format("%s%s,%s%c", CMD__CURRLIMIT_SET, ch1_data, ch2_data, end_str);	// CONF:CURR 0.001,0.001<LF>  // 
				}
				command = cmd;
			}

			// send command
			{
				CString cls_bff;
				Write__DRV_LOG("Write_String_CURRLIMIT_SET_SEND");
				mX_Serial->CLEAR__BUFFER(&cls_bff);
				s_len = mX_Serial->DATA__SEND(command);
			}

			// receive data
			{
				r_len = mX_Serial->DATA__RECV(end_str, &r_data, m_Rcv_Time);
				Write__DRV_LOG("Write_String_CURRLIMIT_SET_RECV");
			}

			//{
			//	if (Command_Recv(command, &r_data) < 0)
			//	{
			//		log_msg.Format("Write_String_CURRLIMIT_SET_Command_Send_NG", set_data);
			//		Write__DRV_LOG(log_msg);
			//		return -1;
			//	}

			//	r_len = r_data.GetLength();
			//}

			// recv data 처리
			{
				if (dCH__CFG_NEED_REPLY->Check__DATA(MODE__OFF) > 0)
				{
					return 1;
				}

				if (r_len > -1)
				{
					Recv_Data_Multi(r_data, r_value, CHAR__SEPARATE_SEMICOLON, r_len);

					str.Format("%s", r_value[0].Mid(1, 1));
					ch1_data = str;
					str.Format("%s", r_value[0].Mid(2, 4));
					buf = atof(str);
					str.Format("%.1f", buf / 1000);
					ch1_data += str;

					str.Format("%s", r_value[1].Mid(1, 1));
					ch2_data = str;
					str.Format("%s", r_value[1].Mid(2, 4));
					buf = atof(str);
					str.Format("%.1f", buf / 1000);
					ch2_data += str;

					sCH__SETCURR_READ_CH1->Set__DATA(ch1_data);
					sCH__SETCURR_READ_CH2->Set__DATA(ch2_data);

					log_msg.Format("SND : [%s], RCV : [%s], RCV_Len : [%d], s_flag[%d]", command, r_data, r_len, s_len);
					Write__DRV_LOG(log_msg);

					log_msg.Format("current_limit_set_end : %s", set_data);
					Write__DRV_LOG(log_msg);
					return 1;
				}
			}
		}

		// Ramp Up Time Set
		if(var_name.CompareNoCase(soCH__RAMPUP_SET->Get__VARIABLE_NAME()) == 0)
		{
			double f_value;
			int	   i_value;
			CString	data;
			
			// set command
			{
			f_value = atof(set_data);
			i_value = (int) (f_value * 1000);
			ch1_data.Format("%d", (i_value));

			cmd.Format("%s%s%s%s%c", CMD__RAMPUP_SET, ch1_data, CMD__LIAISE, CMD__RAMPUP_READ, end_str);	// CONF:RAMP UP,9900;:CONF:RAMP? UP<LF>
			command = cmd;
			}
			
			// send command
			{
				CString cls_bff;
				Write__DRV_LOG("Write_String_RAMPUP_SET_SEND");
				mX_Serial->CLEAR__BUFFER(&cls_bff);
				s_len = mX_Serial->DATA__SEND(command);
			}

			// receive data
			{
				r_len = mX_Serial->DATA__RECV(end_str, &r_data, m_Rcv_Time);
				Write__DRV_LOG("Write_String_RAMPUP_SET_RECV");
			}

			//{
			//	if (Command_Recv(command, &r_data) < 0)
			//	{
			//		log_msg.Format("Write_String_CURRLIMIT_SET_Command_Send_NG", set_data);
			//		Write__DRV_LOG(log_msg);
			//		return -1;
			//	}

			//	r_len = r_data.GetLength();
			//}

			// recv data 처리
			{
				if (r_len > -1)
				{
					Recv_Data_Single(r_data, &data);

					f_value = atof(data);
					f_value = f_value / 1000.0;
					ch1_data.Format("%.1f", f_value);

					//log_msg.Format("[%.1f], [%s]", f_value, ch1_data);
					//Write__DRV_LOG(log_msg);

					sCH__SETRAMPUP_READ->Set__DATA(ch1_data);

					log_msg.Format("SND : [%s], RCV : [%s], RCV_Len : [%d], s_flag[%d]", command, r_data, r_len, s_len);
					Write__DRV_LOG(log_msg);

					return 1;
				}
			}
		}

		// Ramp Down Time Set
		if(var_name.CompareNoCase(soCH__RAMPDN_SET->Get__VARIABLE_NAME()) == 0)
		{
			double	f_value;
			int		i_value;
			CString	data;

			// set command
			{
				f_value = atof(set_data);
				i_value = (int) (f_value * 1000);
				ch1_data.Format("%d", (i_value));

				cmd.Format("%s%s%s%s%c", CMD__RAMPDN_SET, ch1_data, CMD__LIAISE, CMD__RAMPDN_READ, end_str);	// CONF:RAMP DOWN,9900;:CONF:RAMP? DOWN<LF>
				command = cmd;
			}

			// send command
			{
				CString cls_bff;
				Write__DRV_LOG("Write_String_RAMPDN_SET_SEND");
				mX_Serial->CLEAR__BUFFER(&cls_bff);
				s_len = mX_Serial->DATA__SEND(command);
			}

			// receive data
			{
				r_len = mX_Serial->DATA__RECV(end_str, &r_data, m_Rcv_Time);
				Write__DRV_LOG("Write_String_RAMPDN_SET_RECV");
			}

			//{
			//	if (Command_Recv(command, &r_data) < 0)
			//	{
			//		log_msg.Format("Write_String_CURRLIMIT_SET_Command_Send_NG", set_data);
			//		Write__DRV_LOG(log_msg);
			//		return -1;
			//	}

			//	r_len = r_data.GetLength();
			//}

			// recv data 처리
			{
				if (r_len > -1)
				{
					Recv_Data_Single(r_data, &data);

					f_value = atof(data);
					f_value = f_value / 1000.0;
					ch1_data.Format("%.1f", f_value);

					sCH__SETRAMPDN_READ->Set__DATA(ch1_data);

					log_msg.Format("SND : [%s], RCV : [%s], RCV_Len : [%d], s_flag[%d]", command, r_data, r_len, s_len);
					Write__DRV_LOG(log_msg);

					return 1;
				}
			}
		}

		// Auto Toggle Count Set
		if(var_name.CompareNoCase(soCH__AUTO_TOGGLE_CNT->Get__VARIABLE_NAME()) == 0)
		{
			int	value;
			CString	data;

			// set command
			{
			value = atoi(set_data);
			ch1_data.Format("%d", value);
			cmd.Format("%s%s%s%s%c", CMD__AUTO_TOGG_CNT, ch1_data, CMD__LIAISE, CMD__AUTO_TOGG_CNT_READ, end_str);	// AT:COUNT 1;:AT:COUNT?
			command = cmd;
			}

			// send command
			{
				CString cls_bff;
				Write__DRV_LOG("Write_String_AUTO_TOGG_CNT_SEND");
				mX_Serial->CLEAR__BUFFER(&cls_bff);
				s_len = mX_Serial->DATA__SEND(command);
			}

			// receive data
			{
				r_len = mX_Serial->DATA__RECV(end_str, &r_data, m_Rcv_Time);
				Write__DRV_LOG("Write_String_AUTO_TOGG_CNT_RECV");
			}

			//{
			//	if (Command_Recv(command, &r_data) < 0)
			//	{
			//		log_msg.Format("Write_String_CURRLIMIT_SET_Command_Send_NG", set_data);
			//		Write__DRV_LOG(log_msg);
			//		return -1;
			//	}

			//	r_len = r_data.GetLength();
			//}


			// recv data 처리
			{
				if (r_len > -1)
				{
					Recv_Data_Single(r_data, &data);

					value = atoi(data);
					ch1_data.Format("%d", value);

					aCH__AUTO_TOGGLE_CNT_READ->Set__DATA(ch1_data);

					log_msg.Format("SND : [%s], RCV : [%s], RCV_Len : [%d], s_flag[%d]", command, r_data, r_len, s_len);
					Write__DRV_LOG(log_msg);

					return 1;
				}
			}
		}

		// Auto Toggle VOLT Set
		if(var_name.CompareNoCase(soCH__AUTO_TOGGLE_VOLT->Get__VARIABLE_NAME()) == 0)
		{
			CString	value;
			CString	data;

			// set command
			{
			ch1_data = set_data;
			cmd.Format("%s%s%s%s%c", CMD__AUTO_TOGG_VOLT, ch1_data, CMD__LIAISE, CMD__AUTO_TOGG_VOLT_READ, end_str);	// AT:VOLT 400;:AT:VOLT?
			command = cmd;
			}

			// send command
			{
				CString cls_bff;
				Write__DRV_LOG("Write_String_AUTO_TOGG_VOLT_SEND");
				mX_Serial->CLEAR__BUFFER(&cls_bff);
				s_len = mX_Serial->DATA__SEND(command);
			}

			// receive data
			{
				r_len = mX_Serial->DATA__RECV(end_str, &r_data, m_Rcv_Time);
				Write__DRV_LOG("Write_String_AUTO_TOGG_VOLT_RECV");
			}

			//{
			//	if (Command_Recv(command, &r_data) < 0)
			//	{
			//		log_msg.Format("Write_String_CURRLIMIT_SET_Command_Send_NG", set_data);
			//		Write__DRV_LOG(log_msg);
			//		return -1;
			//	}

			//	r_len = r_data.GetLength();
			//}

			// recv data 처리
			{
				if (r_len > -1)
				{
					Recv_Data_Single(r_data, &data);

					value = data;
					ch1_data.Format("%s", value);

					aCH__AUTO_TOGGLE_VOLT_READ->Set__DATA(ch1_data);

					log_msg.Format("SND : [%s], RCV : [%s], RCV_Len : [%d], s_flag[%d]", command, r_data, r_len, s_len);
					Write__DRV_LOG(log_msg);

					return 1;
				}
			}
		}

		// STAT READ
		if(var_name.CompareNoCase(soCH__STATE_READ->Get__VARIABLE_NAME()) == 0)
		{
			CString	value;
			CString	data;
			CString ch1_volt;
			CString ch2_volt;
			CString ch1_curr;
			CString ch2_curr;
			CString output_sts;
			CString toggle_sts;
			CString remote_sts;

			// set command
			{
				ch1_data = set_data;
				cmd.Format("%s%c", CMD__STATE_READ, end_str);	// STAT?
				command = cmd;
			}

			// send command
			{
				CString cls_bff;
				Write__DRV_LOG("Write_String_STAT_READ_SEND");
				mX_Serial->CLEAR__BUFFER(&cls_bff);
				s_len = mX_Serial->DATA__SEND(command);
			}

			// receive data
			{
				r_len = mX_Serial->DATA__RECV(end_str, &r_data, m_Rcv_Time);
				Write__DRV_LOG("Write_String_STAT_READ_RECV");
			}

			//{
			//	if (Command_Recv(command, &r_data) < 0)
			//	{
			//		log_msg.Format("Write_String_CURRLIMIT_SET_Command_Send_NG", set_data);
			//		Write__DRV_LOG(log_msg);
			//		return -1;
			//	}

			//	r_len = r_data.GetLength();
			//}

			// recv data 처리
			{
				if (r_len > -1)
				{
					Recv_Data_Multi(r_data, r_value, CHAR__SEPARATE_SEMICOLON, r_len);
					
					sCH__STATE_READ->Set__DATA(r_value[0]);

					CString ch1_volt;
					CString ch2_volt;
					CString ch1_curr;
					CString ch2_curr;
					CString output_sts;
					CString toggle_sts;
					CString remote_sts;
					double	buf;
					
					{
						// volt
						ch1_volt.Format("%s", r_value[0].Mid(1, 5));
						ch2_volt.Format("%s", r_value[1].Mid(1, 5));

						// current
						str.Format("%s", r_value[2].Mid(1, 1));
						ch1_curr = str;
						str.Format("%s", r_value[2].Mid(2, 4));
						buf = atof(str);
						str.Format("%.2f", buf / 1000);
						ch1_curr += str;

						str.Format("%s", r_value[3].Mid(1, 1));
						ch2_curr = str;
						str.Format("%s", r_value[3].Mid(2, 4));
						buf = atof(str);
						str.Format("%.2f", buf / 1000);
						ch2_curr += str;

						// output
						output_sts = r_value[4];

						// toggle
						toggle_sts = r_value[5];

						// remote
						remote_sts = r_value[6];
					}
					
					aCH__VOLT_READ_CH1->Set__DATA(ch1_volt);
					aCH__VOLT_READ_CH2->Set__DATA(ch2_volt);
					aCH__CURR_READ_CH1->Set__DATA(ch1_curr);
					aCH__CURR_READ_CH2->Set__DATA(ch2_curr);

					if		(output_sts.CompareNoCase(STS__ON) == 0)
					{
						sCH__OUTPUT_STATUS->Set__DATA(MODE__ON);
					}
					else if (output_sts.CompareNoCase(STS__OFF) == 0)
					{
						sCH__OUTPUT_STATUS->Set__DATA(MODE__OFF);
					}

					if		(toggle_sts.CompareNoCase(STS__ON) == 0)
					{
						sCH__TOGGLE_STATUS->Set__DATA(MODE__ON);
					}
					else if (toggle_sts.CompareNoCase(STS__OFF) == 0)
					{
						sCH__TOGGLE_STATUS->Set__DATA(MODE__OFF);
					}

					if		(remote_sts.CompareNoCase(STS__ON) == 0)
					{
						sCH__REMOTE_STATUS->Set__DATA(MODE__REMOTE);
					}
					else if (remote_sts.CompareNoCase(STS__OFF) == 0)
					{
						sCH__REMOTE_STATUS->Set__DATA(MODE__LOCAL);
					}

					log_msg.Format("SND : [%s], RCV : [%s], RCV_Len : [%d], s_flag[%d]", command, r_data, r_len, s_len);
					Write__DRV_LOG(log_msg);

					return 1;
				}
				else
				{
					log_msg.Format("INFO_UPDATE_NG - SND : [%s], RCV : [%s], RCV_Len : [%d], s_flag[%d]", command, r_data, r_len, s_len);
					Write__DRV_LOG(log_msg);

					return -1;
				}
			}

		}

		// ERROR READ
		if(var_name.CompareNoCase(soCH__ERROR_READ->Get__VARIABLE_NAME()) == 0)
		{
			CString r_err;

			// set command
			{
				//ch1_data = set_data;
				cmd.Format("%s%c", CMD__ERROR_READ, end_str);	// SYST:ERR?<LF>
				command = cmd;
			}

			// send command
			{
				CString cls_bff;
				Write__DRV_LOG("Write_String_ERROR_READ_SEND");
				mX_Serial->CLEAR__BUFFER(&cls_bff);
				s_len = mX_Serial->DATA__SEND(command);
			}

			// receive data
			{
				r_len = mX_Serial->DATA__RECV(end_str, &r_data, m_Rcv_Time);
				Write__DRV_LOG("Write_String_ERROR_READ_RECV");
			}

			//{
			//	if (Command_Recv(command, &r_data) < 0)
			//	{
			//		log_msg.Format("Write_String_CURRLIMIT_SET_Command_Send_NG", set_data);
			//		Write__DRV_LOG(log_msg);
			//		return -1;
			//	}

			//	r_len = r_data.GetLength();
			//}

			// recv data 처리
			{
				if (r_len > -1)
				{
					Recv_Data_Multi(r_data, r_value, CHAR__SEPARATE_COMMA, r_len);

					sCH__ERROR_READ->Set__DATA(r_value[0]);

					log_msg.Format("SND : [%s], RCV : [%s], RCV_Len : [%d], s_flag[%d]", command, r_data, r_len, s_len);
					Write__DRV_LOG(log_msg);

					return 1;
				}
			}
		}
	}
	while (++n_cnt <= m_RetryCnt);

	if (n_cnt > m_RetryCnt)
	{	
		log_msg.Format("Write_String Receive Data NG_Retry Over - SND : [%s], RCV : [%s], RCV_Len : [%d], s_flag[%d]", cmd, r_data, r_len, s_len);
		Write__DRV_LOG(log_msg);
		return -1;
	}

	Write__DRV_LOG("Write__String_end");
	return -1;
}

//------------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA
::Command_Send(CString send_cmd)
{
	CString log_msg;
	int s_flag;	

	// send command
	CString cls_bff;
	mX_Serial->CLEAR__BUFFER(&cls_bff);
	s_flag = mX_Serial->DATA__SEND(send_cmd);

	if (s_flag < 0)
	{
		return -1;
	}

	return 1;

}

//------------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA
::Command_Recv(CString send_cmd, CString *recv_cmd)
{
	CString log_msg;
	int r_len;	

	// send command
	{
		CString cls_bff;
		mX_Serial->CLEAR__BUFFER(&cls_bff);
		r_len = mX_Serial->DATA__RECV(end_str, &send_cmd, m_Rcv_Time);

		if (r_len < 0)
		{
			return -1;
		}
		else
		{
			recv_cmd = &send_cmd;
		}
	}

	return 1;
}