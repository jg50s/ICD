#include "StdAfx.h"
#include "CObj_NET__ALx_SR100.h"
#include "CObj_NET__ALx_SR100__DEF.h"

#include "math.h"
#include "CCommon_DEF.h"
#include "Macro_Function.h"


//------------------------------------------------------------------------------------
int  CObj_NET__ALx_SR100
::Drv__CMD_COM_INIT(const CString& var_name)
{

	return 1;
}

int CObj_NET__ALx_SR100
::_Send__CMMD(const CString& var_name, 
			  const CString& set_data)
{
	// ...
	{
		CString s_cmd;
		CString s_packet;
		CString s_sum;
		CString e_msg;

		s_cmd.Format(",%s,", set_data);
		s_sum = _Get__CHECK_SUM(s_cmd);
		s_packet.Format("$%s%s", s_cmd,s_sum);

		// Log ...
		{
			CString log_msg;
			CString log_bff;

			log_msg = "_Send__CMMD() ... \n";

			log_bff.Format(" * %s <- %s \n", var_name,set_data);
			log_msg += log_bff;

			log_bff.Format(" * Packet <- [%s] \n", s_packet);
			log_msg += log_bff;

			Fnc__DRV_LOG(log_msg);
		}

		mX_Net->DATA__SEND(s_cmd, 1, &e_msg);
	}
	return 1;
}
int CObj_NET__ALx_SR100
::_Recv__CMMD(const CString& var_name, 
			  const bool act_mode, 
			  const CString& set_data, 
			  CString& recv_data)
{
	CString log_msg;
	CString log_bff;

	// ...
	int ref_tick = GetTickCount();
	int act_timeout = 15 * 1000;

	int loop_count = 0;
	int r_count = 0;

	// ...
	{
		CString err_msg;
		mX_Net->CLEAR__BUFFER(&err_msg);

		mMng__RSP_MSG.Clear__ALL_RSP_MSG();

		//
		CString s_packet;
		CString s_cmmd;
		CString s_sum;

		s_cmmd.Format(",%s,", set_data);
		s_sum = _Get__CHECK_SUM(s_cmmd);

		s_packet.Format("$%s%s", s_cmmd,s_sum);

		// Log ...
		{
			log_msg = "_Recv__CMMD() ... \n";

			log_bff.Format(" * %s <- %s \n", var_name,set_data);
			log_msg += log_bff;

			log_bff.Format(" * Packet <- [%s] \n", s_packet);
			log_msg += log_bff;

			if(act_mode)
			{
				log_bff = "Action_Mode : Active \n";
				log_msg += log_bff;
			}

			Fnc__DRV_LOG(log_msg);
		}

		mX_Net->DATA__SEND(s_packet, 1, &err_msg);
	}

	// ...
	int rsp_active = -1;
	int cnt_vent = 0;

	while(1)
	{
		Sleep(1);

		// ...
		CString rsp_msg;

		if(mMng__RSP_MSG.Get__RSP_MSG(rsp_msg) > 0)
		{
			m_nCommState = ONLINE;

			if(rsp_msg.GetLength() > 0)
			{
				char ch_rsp = rsp_msg.GetAt(0);

				recv_data = rsp_msg;

				// ACK Response
				if(ch_rsp == '$')
				{
					if(!act_mode)		
						return _DRV_RSP__ACK;
				}
				// Error Response
				if(ch_rsp == '?')
				{
					return _DRV_RSP__ERROR;
				}
				// Action Complete
				if(ch_rsp == '!')
				{
					cnt_vent++;

					// Log ...
					{
						log_msg = " _Recv__CMMD() ... \n";

						log_bff.Format(" * Event_Count <- %1d \n", cnt_vent);
						log_msg += log_bff;

						Fnc__DRV_LOG(log_msg);
					}

					/*
					// ACKN
					if(cnt_vent == 1)
					{
						CString str_ackn;
						str_ackn.Format("%s,ACKN", sDRV_UnitID);

						_Send__CMMD(var_name, str_ackn);
					}
					*/

					if(cnt_vent >= 1)
						return _DRV_RSP__COMPLETE;		
				}
			}
		}

		// ...
		{
			int dif_tick = GetTickCount() - ref_tick;

			if(dif_tick >= act_timeout)
			{
				// Log ...
				{
					log_msg = "Timeout ! \n";

					log_bff.Format(" * ref_timeout <- %1d \n", dif_tick);
					log_msg += log_bff;

					Fnc__DRV_LOG(log_msg);
				}

				m_nCommState = OFFLINE;
				return -1;
			}
			else if(dif_tick < 0)
			{
				ref_tick = GetTickCount();
			}
		}
	} 

	return -1;
}

int  CObj_NET__ALx_SR100
::_Update__SYSTEM_STATUS(const CString& r_data)
{
	unsigned char i_sts1 = 0x0;
	unsigned char i_sts2 = 0x0;

	int i_len = r_data.GetLength();
	if(i_len > 0)		i_sts1 = _Get__HEXA_FROM_ASCII(r_data.GetAt(0));
	if(i_len > 1)		i_sts2 = _Get__HEXA_FROM_ASCII(r_data.GetAt(1));

	// Status1 ...
	{
		unsigned char x_sts = i_sts1;

		// 1H : Manipulator battery status
		if(x_sts & 0x01)		sCH__MON_SYS_STS__MANIPULATOR_BATTERY->Set__DATA(STR__LOW);
		else					sCH__MON_SYS_STS__MANIPULATOR_BATTERY->Set__DATA(STR__OK);

		// 2H : Unit status
		if(x_sts & 0x02)		sCH__MON_SYS_STS__UNIT_STATUS->Set__DATA(STR__READY);
		else					sCH__MON_SYS_STS__UNIT_STATUS->Set__DATA(STR__BUSY);

		// 4H : Servo status
		if(x_sts & 0x04)		sCH__MON_SYS_STS__SERVO_STATUS->Set__DATA(STR__OFF);
		else					sCH__MON_SYS_STS__SERVO_STATUS->Set__DATA(STR__ON);

		// 8H : Error status
		if(x_sts & 0x08)		sCH__MON_SYS_STS__ERROR_STATUS->Set__DATA(STR__ON);
		else					sCH__MON_SYS_STS__ERROR_STATUS->Set__DATA(STR__OFF);
	}
	// Status2 ...
	{
		unsigned char x_sts = i_sts2;

		// 1H : Controller battery status
		if(x_sts & 0x01)		sCH__MON_SYS_STS__CONTROLLER_BATTERY->Set__DATA(STR__LOW);
		else					sCH__MON_SYS_STS__CONTROLLER_BATTERY->Set__DATA(STR__OK);

		// 2H : Wafer presence status1
		if(x_sts & 0x02)		sCH__MON_SYS_STS__WAFER_PRESENCE_STS1->Set__DATA(STR__ON);
		else					sCH__MON_SYS_STS__WAFER_PRESENCE_STS1->Set__DATA(STR__OFF);

		// 4H : Wafer presence status2
		if(x_sts & 0x04)		sCH__MON_SYS_STS__WAFER_PRESENCE_STS2->Set__DATA(STR__ON);
		else					sCH__MON_SYS_STS__WAFER_PRESENCE_STS2->Set__DATA(STR__OFF);

		// 8H : Reserve
		if(x_sts & 0x08)		;
	}

	return 1;
}
int  CObj_NET__ALx_SR100
::_Update__ERROR_CODE(const CString& rsp_errcd)
{
	int i_len = rsp_errcd.GetLength();
	if(i_len != 4)		return -1;

	CString err_level = rsp_errcd;
	CString err_code  = rsp_errcd;

	err_level.Delete(1, 3);
	err_code.Delete(0, 1);

	     if(err_code.CompareNoCase("1") == 0)			sCH__MON_ERR_SYS__LEVEL->Set__DATA("W1");
	else if(err_code.CompareNoCase("2") == 0)			sCH__MON_ERR_SYS__LEVEL->Set__DATA("W2");
	else if(err_code.CompareNoCase("3") == 0)			sCH__MON_ERR_SYS__LEVEL->Set__DATA("A1");
	else if(err_code.CompareNoCase("4") == 0)			sCH__MON_ERR_SYS__LEVEL->Set__DATA("A2");
	else if(err_code.CompareNoCase("5") == 0)			sCH__MON_ERR_SYS__LEVEL->Set__DATA("F");
	else												sCH__MON_ERR_SYS__LEVEL->Set__DATA("??");

	sCH__MON_ERR_STS__CODE->Set__DATA(err_code);
	return 1;
}
int  CObj_NET__ALx_SR100
::_Check__ERROR_CODE(const CString& rsp_err)
{
	int i_err = _Get__HEXA_FROM_ASCII(rsp_err);
	if(i_err > 0)
	{
		CString err_msg = YASKAWA__Get_Error_Msg_Of_Error_Code(i_err, rsp_err);

		mMNG__ERR_CODE.Load__Error_Code(rsp_err, err_msg);
		return 1;
	}
	return -1;
}

int  CObj_NET__ALx_SR100
::_Update__ALIGNER_STATUS(const CString& r_data)
{
	unsigned char i_sts1 = 0x0;

	int i_len = r_data.GetLength();
	if(i_len > 0)		i_sts1 = _Get__HEXA_FROM_ASCII(r_data.GetAt(0));

	// Status1 ...
	{
		unsigned char x_sts = i_sts1;

		if(x_sts & 0x01)		sCH__MON_PA_STS__VACUUM_STS->Set__DATA(STR__ON);
		else					sCH__MON_PA_STS__VACUUM_STS->Set__DATA(STR__OFF);

		if(x_sts & 0x02)		sCH__MON_PA_STS__WAFER_SNS->Set__DATA(STR__ON);
		else					sCH__MON_PA_STS__WAFER_SNS->Set__DATA(STR__OFF);

		if(x_sts & 0x04)		sCH__MON_PA_STS__CHUCKING_CMMD->Set__DATA(STR__OFF);
		else					sCH__MON_PA_STS__CHUCKING_CMMD->Set__DATA(STR__ON);
	}

	return 1;
}

int  CObj_NET__ALx_SR100
::_Get__HEXA_FROM_ASCII(const CString& str_ascii)
{
	int i_hexa = 0;

	int i_limit = str_ascii.GetLength();
	int i;

	for(i=0; i<i_limit; i++)
	{
		char ch_ascii = (char) str_ascii.GetAt(i);

		i_hexa *= 0x10;
		i_hexa += _Get__HEXA_FROM_ASCII(ch_ascii);
	}
	return i_hexa;
}
int  CObj_NET__ALx_SR100
::_Get__HEXA_FROM_ASCII(const unsigned char ch_ascii)
{
	switch(ch_ascii)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return (ch_ascii - '0');

		case 'a':
		case 'A':
			return 10;

		case 'b':
		case 'B':
			return 11;

		case 'c':
		case 'C':
			return 12;

		case 'd':
		case 'D':
			return 13;

		case 'e':
		case 'E':
			return 14;

		case 'f':
		case 'F':
			return 15;
	}

	return 0;
}

int  CObj_NET__ALx_SR100
::Fnc__StrTo2Word(const CString& data,
				  const char section,
				  CString *p_str1,
				  CString *p_str2)
{
	CString word;
	char str_ch[2];
	char ch;

	int init_flag;
	int para;
	int limit;
	int i;

	// ...
	init_flag = 0;
	para = 0;
	str_ch[1] = 0;

	limit = data.GetLength();

	for(i=0; i<=limit; i++)
	{
		if(i<limit)		ch = data.GetAt(i);
		else			ch = section;

		if(ch == section)
		{
			if(word.GetLength() > 0)
			{
				if(para == 0)	*p_str1 = word;
				else if(para == 1)	*p_str2 = word;

				word = "";
			}

			para++;
		}
		else
		{
			str_ch[0] = ch;
			word += str_ch;
		}
	}

	return 1;
}
int  CObj_NET__ALx_SR100
::Fnc__StrTo7Word(const CString& data,
				  const char section,
				  CString *p_str1,
				  CString *p_str2,
				  CString *p_str3,
				  CString *p_str4,
				  CString *p_str5,
				  CString *p_str6,
				  CString *p_str7)
{
	CString word;
	char str_ch[2];
	char ch;

	int init_flag;
	int para;
	int limit;
	int i;

	// ...
	init_flag = 0;
	para = 0;
	str_ch[1] = '\0';

	limit = data.GetLength();

	for(i=0;i<=limit;i++)
	{
		if(i<limit)		ch = data.GetAt(i);
		else			ch = section;

		if(ch == section)
		{
			if(word.GetLength() > 0)
			{
				if(para == 0)	*p_str1 = word;
				else if(para == 1)	*p_str2 = word;
				else if(para == 2)  *p_str3 = word;
				else if(para == 3)  *p_str4 = word;
				else if(para == 4)  *p_str5 = word;
				else if(para == 5)  *p_str6 = word;
				else if(para == 6)  *p_str7 = word;

				word = "";
			}

			para++;
		}
		else
		{
			str_ch[0] = ch;
			word += str_ch;
		}
	}

	return 1;
}

//.....
int  CObj_NET__ALx_SR100::
Fnc__IndexStrTo1Word(const CString& data,
					 const char section,
					 int index,
					 CString *p_str1)
{
	//.....
	CString word;
	char str_ch[2];
	char ch;

	int init_flag;
	int para;
	int limit;
	int i;

	//.....
	init_flag = 0;
	para = 0;
	str_ch[1] = '\0';

	limit = data.GetLength();
	index--;

	for(i=index;i<=limit;i++)
	{
		if(i<limit)		ch = data.GetAt(i);
		else			ch = section;

		if(ch == section)
		{
			if(word.GetLength() > 0)
			{
				if(para == 0)		*p_str1 = word;

				word = "";
			}

			para++;
		}
		else
		{
			str_ch[0] = ch;
			word += str_ch;
		}
	}

	//
	return 1;
}
int  CObj_NET__ALx_SR100::
Fnc__IndexStrTo4Word(const CString& data,
					 const char section,
					 int index,
					 CString *p_str1,
					 CString *p_str2,
					 CString *p_str3,
					 CString *p_str4)
{
	//.....
	CString word;
	char str_ch[2];
	char ch;

	int  init_flag;
	int  para;
	int  limit;
	int  i;

	//.....
	init_flag = 0;
	para = 0;
	str_ch[1] = 0;

	limit = data.GetLength();
	index--;

	for(i=index;i<=limit;i++)
	{
		if(i<limit)			ch = data.GetAt(i);
		else				ch = section;

		if(ch == section)
		{
			if(word.GetLength() > 0)
			{
				if(para == 0)	*p_str1 = word;
				else if(para == 1)	*p_str2 = word;
				else if(para == 2)  *p_str3 = word;
				else if(para == 3)  *p_str4 = word;

				word = "";
			}

			para++;
		}
		else
		{
			str_ch[0] = ch;
			word += str_ch;
		}
	}

	//
	return 1;
}
int  CObj_NET__ALx_SR100::
Fnc__IndexStrTo5Word(const CString& data,
					 const char section,
					 int index,
					 CString *p_str1,
					 CString *p_str2,
					 CString *p_str3,
					 CString *p_str4,
					 CString *p_str5)
{
	//.....
	CString word;
	char str_ch[2];
	char ch;

	int  init_flag;
	int  para;
	int  limit;
	int  i;

	//.....
	init_flag = 0;
	para = 0;
	str_ch[1] = 0;

	limit = data.GetLength();
	index--;

	for(i=index;i<=limit;i++)
	{
		if(i<limit)			ch = data.GetAt(i);
		else				ch = section;

		if(ch == section)
		{
			if(word.GetLength() > 0)
			{
				if(para == 0)	*p_str1 = word;
				else if(para == 1)	*p_str2 = word;
				else if(para == 2)  *p_str3 = word;
				else if(para == 3)  *p_str4 = word;
				else if(para == 4)  *p_str5 = word;

				word = "";
			}

			para++;
		}
		else
		{
			str_ch[0] = ch;
			word += str_ch;
		}
	}

	//
	return 1;
}

//.....
int  CObj_NET__ALx_SR100::
Fnc__HexToDec(const CString& str_dec)
{
	CString string;
	char str_ch[2];
	char ch;

	int  value;
	int  limit;
	int  i;

	string = str_dec;
	string.MakeUpper();

	value = 0;
	str_ch[1] = 0;

	limit = string.GetLength();

	for(i=0; i<limit; i++)
	{
		if(i > 0)	value *= 16;

		ch = string.GetAt(i);
		str_ch[0] = ch;

			if(((ch >= '0')&&(ch <= '9')))		value += atoi(str_ch);
		else if(ch == 'A')						value += 10;
		else if(ch == 'B')						value += 11;
		else if(ch == 'C')						value += 12;
		else if(ch == 'D')						value += 13;
		else if(ch == 'E')						value += 14;
		else if(ch == 'F')						value += 15;		
	}

	return value;
}
int  CObj_NET__ALx_SR100::
Fnc__DecToBin(int dec,
			  CString *p_str)
{
	CString str_result;
	CString word;
	int value;
	int bit;

	int flag = 1;

	while(flag > 0)
	{
		value = dec / 2;
		bit   = dec % 2;
		dec   = value;

		if(value >= 0)
		{
			word.Format("%1d",bit);
			str_result += word;
		}

		if(value == 0)
		{
			flag = 0;
		}
	}

	char str_ch[2];
	int limit;
	int i;

	str_ch[1] = 0;
	word = "";

	limit = str_result.GetLength();

	for(i=limit-1; i>=0; i--)
	{
		str_ch[0] = str_result.GetAt(i); 
		word += str_ch;
	}

	*p_str = word;
	return 1;
}


