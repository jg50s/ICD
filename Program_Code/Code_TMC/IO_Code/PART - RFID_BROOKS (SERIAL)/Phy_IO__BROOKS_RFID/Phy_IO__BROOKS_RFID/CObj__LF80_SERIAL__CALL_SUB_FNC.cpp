#include "StdAfx.h"
#include "CObj__LF80_SERIAL.h"
#include "CObj__LF80_SERIAL__DEF.h"

#include "math.h"


//------------------------------------------------------------------------------------
int  CObj__LF80_SERIAL::
Fnc__Check_Online(CII_OBJECT__ALARM* p_alarm, 
				  const CString szCtrl_Mode)
{
	int alarm_id;

	CString alm_title;
	CString alm_msg;
	CString r_act;
	CString err_code;

	if(iSim_Flag > 0)
	{
		m_nCommState = ONLINE;
		diCH__FAILURE_CODE->Set__DATA("NONE");
		return 1;
	}

	sCH__MON_COMMUNICATION_STATE->Get__DATA(err_code);
	alm_msg.Format("COMM_STS : %s", err_code);
	Fnc__LOG(alm_msg);

	if(err_code.CompareNoCase("ONLINE") != 0)
	{
		Fnc__LOG("From...Fnc__Check_Online()... Alarm Occured !!");

		if(szCtrl_Mode.CompareNoCase("CID_READ") == 0)
		{
			if(Is__LP_AUTO_MODE() > 0)
			{
				alarm_id = ALID__OFFLINE_ALARM_FULL_AUTO;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				return FA_FULL_AUTO_IGNORE;
			}
			else
			{
				alarm_id = ALID__OFFLINE_ALARM_NOT_FULL_AUTO;
				p_alarm->Popup__ALARM(alarm_id,r_act);		

				if(r_act.CompareNoCase("RETRY") == 0)	return 0;
				else if(r_act.CompareNoCase("ABORT") == 0)	return OBJ_ABORT;

				return FA_FULL_AUTO_IGNORE;
			}
		}
		else
		{
			alarm_id = ALID__OFFLINE_ALARM;
			p_alarm->Popup__ALARM(alarm_id,r_act);

			if(r_act.CompareNoCase("RETRY") == 0)		return 0;

			return OBJ_ABORT;
		}
	}

	// ...
	{
		diCH__FAILURE_CODE->Get__DATA(err_code);

		if(dCH__CFG_TAG_READ_ID_INSTALLED_CHECK_SKIP->Check__DATA("TRUE") > 0)
		{
			if(err_code.CompareNoCase("NOTAG") == 0)
			{
				Fnc__LOG("NO TAG Alarm Occur, but Skip !!");
				return 1;
			}
		}

		if(err_code.CompareNoCase("AUTOFAIL") == 0)
		{
			if(szCtrl_Mode.CompareNoCase("CID_READ") == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_AUTOFAIL_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!
					return FA_FULL_AUTO_IGNORE;
				}
				else
				{
					alarm_id = ALID__RF_AUTOFAIL_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!

					if(r_act.CompareNoCase("RETRY") == 0)		return 0;
					else if(r_act.CompareNoCase("ABORT") == 0)		return OBJ_ABORT;

					return FA_FULL_AUTO_IGNORE;
				}
			}
			else
			{
				alarm_id = ALID__RF_AUTOFAIL;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				diCH__FAILURE_CODE->Set__DATA("NONE");				// Error Clear !!
				return -1;
			}
		}
		else if(err_code.CompareNoCase("EXFAIL") == 0)
		{
			if(szCtrl_Mode.CompareNoCase("CID_READ") == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_EXFAIL_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!
					return FA_FULL_AUTO_IGNORE;
				}
				else
				{
					alarm_id = ALID__RF_EXFAIL_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!

					if(r_act.CompareNoCase("RETRY") == 0)		return 0;
					else if(r_act.CompareNoCase("ABORT") == 0)		return OBJ_ABORT;

					return FA_FULL_AUTO_IGNORE;
				}
			}
			else
			{
				alarm_id = ALID__RF_EXFAIL;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				diCH__FAILURE_CODE->Set__DATA("NONE");				// Error Clear !!
				return -1;
			}
		}
		else if(err_code.CompareNoCase("WRITEFAIL") == 0)
		{
			if(szCtrl_Mode.CompareNoCase("CID_READ") == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_WRITEFAIL_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!
					return FA_FULL_AUTO_IGNORE;
				}
				else
				{
					alarm_id = ALID__RF_WRITEFAIL_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!

					if(r_act.CompareNoCase("RETRY") == 0)		return 0;
					else if(r_act.CompareNoCase("ABORT") == 0)		return OBJ_ABORT;

					return FA_FULL_AUTO_IGNORE;
				}
			}
			else
			{
				alarm_id = ALID__RF_WRITEFAIL;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				diCH__FAILURE_CODE->Set__DATA("NONE");				// Error Clear !!
				return -1;
			}
		}
		else if(err_code.CompareNoCase("NOTAG") == 0)
		{
			if(szCtrl_Mode.CompareNoCase("CID_READ") == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_NOTAG_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!
					return FA_FULL_AUTO_IGNORE;
				}
				else
				{
					alarm_id = ALID__RF_NOTAG_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!

					if(r_act.CompareNoCase("RETRY") == 0)		return 0;
					else if(r_act.CompareNoCase("ABORT") == 0)		return OBJ_ABORT;

					return FA_FULL_AUTO_IGNORE;
				}
			}
			else
			{
				alarm_id = ALID__RF_NOTAG;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				diCH__FAILURE_CODE->Set__DATA("NONE");				// Error Clear !!
				return -1;
			}
		}
		else if(err_code.CompareNoCase("INVALID1") == 0)
		{
			if(szCtrl_Mode.CompareNoCase("CID_READ") == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_INVALID1_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!
					return FA_FULL_AUTO_IGNORE;
				}
				else
				{
					alarm_id = ALID__RF_INVALID1_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!

					if(r_act.CompareNoCase("RETRY") == 0)		return 0;
					else if(r_act.CompareNoCase("ABORT") == 0)		return OBJ_ABORT;

					return FA_FULL_AUTO_IGNORE;
				}
			}
			else
			{
				alarm_id = ALID__RF_INVALID1;
				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				diCH__FAILURE_CODE->Set__DATA("NONE");				// Error Clear !!
				return -1;
			}
		}
		else if(err_code.CompareNoCase("UNKNOWN") == 0)
		{
			if(szCtrl_Mode.CompareNoCase("CID_READ") == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_UNKNOWN_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!
					return FA_FULL_AUTO_IGNORE;
				}
				else
				{
					alarm_id = ALID__RF_UNKNOWN_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!

					if(r_act.CompareNoCase("RETRY") == 0)		return 0;
					else if(r_act.CompareNoCase("ABORT") == 0)		return OBJ_ABORT;

					return FA_FULL_AUTO_IGNORE;
				}
			}
			else
			{
				alarm_id = ALID__RF_UNKNOWN;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				diCH__FAILURE_CODE->Set__DATA("NONE");				// Error Clear !!
				return -1;
			}
		}
		else if(err_code.CompareNoCase("UNCONFIG") == 0)
		{
			if(szCtrl_Mode.CompareNoCase("CID_READ") == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_UNCONFIG_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!
					return FA_FULL_AUTO_IGNORE;
				}
				else
				{
					alarm_id = ALID__RF_UNCONFIG_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!

					if(r_act.CompareNoCase("RETRY") == 0)		return 0;
					else if(r_act.CompareNoCase("ABORT") == 0)		return OBJ_ABORT;

					return FA_FULL_AUTO_IGNORE;
				}
			}
			else
			{
				alarm_id = ALID__RF_UNCONFIG;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				diCH__FAILURE_CODE->Set__DATA("NONE");				// Error Clear !!
				return -1;
			}
		}
		else if(err_code.CompareNoCase("CHECK") == 0)
		{
			if(szCtrl_Mode.CompareNoCase("CID_READ") == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_CHECK_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!
					return FA_FULL_AUTO_IGNORE;
				}
				else
				{
					alarm_id = ALID__RF_CHECK_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!

					if(r_act.CompareNoCase("RETRY") == 0)		return 0;
					else if(r_act.CompareNoCase("ABORT") == 0)		return OBJ_ABORT;

					return FA_FULL_AUTO_IGNORE;
				}
			}
			else
			{
				alarm_id = ALID__RF_CHECK;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				diCH__FAILURE_CODE->Set__DATA("NONE");				// Error Clear !!
				return -1;
			}
		}
		else if(err_code.CompareNoCase("VOIDACKN") == 0)
		{
			if(szCtrl_Mode.CompareNoCase("CID_READ") == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_VOIDACKNE_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!
					return FA_FULL_AUTO_IGNORE;
				}
				else
				{
					alarm_id = ALID__RF_VOIDACKNE_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!

					if(r_act.CompareNoCase("RETRY") == 0)		return 0;
					else if(r_act.CompareNoCase("ABORT") == 0)		return OBJ_ABORT;

					return FA_FULL_AUTO_IGNORE;
				}
			}
			else
			{
				alarm_id = ALID__RF_VOIDACKNE;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				diCH__FAILURE_CODE->Set__DATA("NONE");				// Error Clear !!
				return -1;
			}
		}
		else if(err_code.CompareNoCase("LOCKED") == 0)
		{
			if(szCtrl_Mode.CompareNoCase("CID_READ") == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_LOCKED_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!
					return FA_FULL_AUTO_IGNORE;
				}
				else
				{
					alarm_id = ALID__RF_LOCKED_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!

					if(r_act.CompareNoCase("RETRY") == 0)		return 0;
					else if(r_act.CompareNoCase("ABORT") == 0)		return OBJ_ABORT;

					return FA_FULL_AUTO_IGNORE;
				}
			}
			else
			{
				alarm_id = ALID__RF_LOCKED;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				diCH__FAILURE_CODE->Set__DATA("NONE");				// Error Clear !!
				return -1;
			}
		}
		else if(err_code.CompareNoCase("MSGLEN") == 0)
		{
			if(szCtrl_Mode.CompareNoCase("CID_READ") == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_MSGLEN_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!
					return FA_FULL_AUTO_IGNORE;
				}
				else
				{
					alarm_id = ALID__RF_MSGLEN_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!

					if(r_act.CompareNoCase("RETRY") == 0)		return 0;
					else if(r_act.CompareNoCase("ABORT") == 0)		return OBJ_ABORT;

					return FA_FULL_AUTO_IGNORE;
				}
			}
			else
			{
				alarm_id = ALID__RF_MSGLEN;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				diCH__FAILURE_CODE->Set__DATA("NONE");				// Error Clear !!
				return -1;
			}
		}
		else if(err_code.CompareNoCase("INVALID2") == 0)
		{
			if(szCtrl_Mode.CompareNoCase("CID_READ") == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_INVALID2_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!
					return FA_FULL_AUTO_IGNORE;
				}
				else
				{
					alarm_id = ALID__RF_INVALID2_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!

					if(r_act.CompareNoCase("RETRY") == 0)		return 0;
					else if(r_act.CompareNoCase("ABORT") == 0)		return OBJ_ABORT;

					return FA_FULL_AUTO_IGNORE;
				}
			}
			else
			{
				alarm_id = ALID__RF_INVALID2;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				diCH__FAILURE_CODE->Set__DATA("NONE");				// Error Clear !!
				return -1;
			}
		}
		else if(err_code.CompareNoCase("NOACKN") == 0)
		{
			if(szCtrl_Mode.CompareNoCase("CID_READ") == 0)
			{
				if(Is__LP_AUTO_MODE() > 0)
				{
					alarm_id = ALID__RF_NOACKN_FULL_AUTO;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!
					return FA_FULL_AUTO_IGNORE;
				}
				else
				{
					alarm_id = ALID__RF_NOACKN_NOT_FULL_AUTO;

					p_alarm->Popup__ALARM(alarm_id,r_act);	

					diCH__FAILURE_CODE->Set__DATA("NONE");		// Error Clear !!

					if(r_act.CompareNoCase("RETRY") == 0)		return 0;
					else if(r_act.CompareNoCase("ABORT") == 0)		return OBJ_ABORT;

					return FA_FULL_AUTO_IGNORE;
				}
			}
			else
			{
				//
				alarm_id = ALID__RF_NOACKN;
				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);

				diCH__FAILURE_CODE->Set__DATA("NONE");				// Error Clear !!
				return -1;
			}
		}
		else
		{
			return 1;
		}

	}

	return 1;
}


int  CObj__LF80_SERIAL::
Fnc__MultPage_Read(CII_OBJECT__ALARM* p_alarm,
				   const int min_page_index, 
				   const int max_page_index,
				   CString *page_data,
				   const CString szCtrl_Mode)
{
	if(min_page_index <  0)						return -101;
	if(min_page_index >= CFG__PAGE_SIZE)		return -102;

	if(max_page_index <  0)						return -201;
	if(max_page_index >= CFG__PAGE_SIZE)		return -202;

	int flag;
	CString str__page;
	CString str__sum_value;
	CString str__conv_data;
	CString str__sim;
	int i;


MULTREAD_RTY:

	int nRet = -1;

	if(min_page_index >= max_page_index)
	{
		if(iSim_Flag > 0)
		{
			if(sObject_Name.Find("LP1") >=0)	str__sim.Format("%X5152535354%02X", rand()%60+30, min_page_index);
			if(sObject_Name.Find("LP2") >=0)	str__sim.Format("%X5552535354%02X", rand()%60+30, min_page_index);
			if(sObject_Name.Find("LP3") >=0)	str__sim.Format("%X5652535354%02X", rand()%60+30, min_page_index);
			siCH__READ_PAGE_DATA[min_page_index]->Set__DATA(str__sim);
		}

		nRet = siCH__READ_PAGE_DATA[min_page_index]->Get__DATA(str__page);
		str__conv_data = Fnc__ASCII_Conver(str__page);

		flag = Fnc__Check_Online(p_alarm, szCtrl_Mode);	
		if(flag == 0)
		{
			goto MULTREAD_RTY;
		}
		else if(flag == FA_FULL_AUTO_IGNORE)
		{
			*page_data = "";	// Null °ª...
			return 1;
		}
		else if(flag <  0)
		{
			return -1;
		}
	}
	else
	{
		str__sum_value = "";

		for(i=min_page_index;i<=max_page_index;i++)
		{
			if(iSim_Flag > 0)
			{
				if(sObject_Name.Find("LP1") >=0)	str__sim.Format("%X5152535354%02X", rand()%60+30, i);
				if(sObject_Name.Find("LP2") >=0)	str__sim.Format("%X5552535354%02X", rand()%60+30, i);
				if(sObject_Name.Find("LP3") >=0)	str__sim.Format("%X5652535354%02X", rand()%60+30, i);
				
				siCH__READ_PAGE_DATA[i]->Set__DATA(str__sim);
			}

			nRet = siCH__READ_PAGE_DATA[i]->Get__DATA(str__page);
			str__conv_data = Fnc__ASCII_Conver(str__page);

			str__sum_value += str__conv_data;

			flag = Fnc__Check_Online(p_alarm, szCtrl_Mode);	
			if(flag == 0)
			{
				goto MULTREAD_RTY;
			}
			else if(flag == FA_FULL_AUTO_IGNORE)
			{
				*page_data = "";	// Null °ª...
				return 1;
			}
			else if(flag <  0)
			{
				return -1;
			}
		}

		str__conv_data = str__sum_value;
	}

	*page_data = str__conv_data;
	return nRet;
}
int  CObj__LF80_SERIAL::
Fnc__Page_Read(CII_OBJECT__ALARM* p_alarm,
			   const int page_index,
			   CString *page_data)
{
	if(page_index <  0)							return -101;
	if(page_index >= CFG__PAGE_SIZE)			return -102;

	int flag;
	CString str__value;
	CString str__conv_data;


PAGEREAD_RTY:

	// ...
	int nRet = -1;

	if(iSim_Flag > 0)
	{
		str__value = "45444c3534322e31";
		siCH__READ_PAGE_DATA[page_index]->Set__DATA(str__value);

		nRet = 1;
	}
	else
	{
		nRet = siCH__READ_PAGE_DATA[page_index]->Get__DATA(str__value);
	}

	str__conv_data = Fnc__ASCII_Conver(str__value);

	// ...
	{
		flag = Fnc__Check_Online(p_alarm, "");	

		if(flag == 0)		goto PAGEREAD_RTY;
		if(flag <  0)		return -1;
	}

	*page_data = str__conv_data;
	return nRet;
}

int  CObj__LF80_SERIAL::
Fnc__MultPage_Write(CII_OBJECT__ALARM* p_alarm,
					const int min_page_index,
					const int max_page_index,
					const CString& page_data)
{
	if(min_page_index <  0)						return -101;
	if(min_page_index >= CFG__PAGE_SIZE)		return -102;

	if(max_page_index <  0)						return -201;
	if(max_page_index >= CFG__PAGE_SIZE)		return -202;

	//.....
	int flag;

	CString alm__title;
	CString alm__msg;
	CString alm__err_code;

	CString str__get_data;
	CString str__conv_data;
	CString str__sim;
	CString str__set_data;
	int i;
	int j;


MALTWRITE_RTY:

	// ...
	int nRet = -1;

	str__set_data = page_data;

	if(min_page_index >= max_page_index)
	{
		if(iSim_Flag > 0)
		{
			str__sim.Format("RF %dM-PageWrite", min_page_index+1);
			nRet = soCH__WRITE_PAGE_DATA[min_page_index]->Set__DATA(str__sim);

			nRet = 1;
		}

		for(i=str__set_data.GetLength();i<8;i++)
		{
			str__set_data += ' ';
		}

		if(str__set_data.GetLength() > 8)
		{
			str__set_data = str__set_data.Mid(0,8);
		}

		str__conv_data = Fnc__HEX_Conver(str__set_data);

		// ...
		nRet = soCH__WRITE_PAGE_DATA[min_page_index]->Set__DATA(str__conv_data);

		flag = Fnc__Check_Online(p_alarm, "");

		if(flag == 0)		goto MALTWRITE_RTY;
		if(flag <  0)		return -1;
	}
	else
	{
		int page_size = max_page_index - min_page_index;

		for(j=str__set_data.GetLength();j<((page_size*8)+8);j++)
		{
			str__set_data += ' ';
		}

		if(iSim_Flag > 0)
		{
			str__set_data.Format("FidesSC OK");
			nRet = 1;
		}

		// ...
		int l_data = 0;

		for(i=min_page_index;i<=max_page_index;i++)
		{			
			if(str__set_data.GetLength() >= 8)
			{
				str__get_data = str__set_data.Mid(0,8);
				str__set_data.Delete(0,8); 
			}
			else
			{
				str__get_data = str__set_data;
			}

			// ...
			str__conv_data = Fnc__HEX_Conver(str__get_data);
			nRet = soCH__WRITE_PAGE_DATA[i]->Set__DATA(str__conv_data);

			l_data = l_data + 8;  // 8 Byte

			// ...
			flag = Fnc__Check_Online(p_alarm, "");	

			if(flag == 0)		goto MALTWRITE_RTY;
			if(flag <  0)		return -1;
		}	
	}

	return nRet;
}
int  CObj__LF80_SERIAL::
Fnc__Page_Write(CII_OBJECT__ALARM* p_alarm,
				const int page_index,
				const CString& set_data)
{
	if(page_index <  0)							return -101;
	if(page_index >= CFG__PAGE_SIZE)			return -102;

	// ...
	int flag;
	CString str__sim;
	CString str__conv_data;
	int i;

	CString log_msg;

	// ...
	int nRet = -111;

	if(iSim_Flag > 0)
	{
		str__sim.Format("RF Page(%1d) Write OK", page_index+1);
		siCH__READ_PAGE_DATA[page_index]->Set__DATA(str__sim);

		nRet = 1;
	}

	// ...
	CString page_data = set_data;

	for(i=page_data.GetLength();i<8;i++)
	{
		page_data += ' ';
	}

	if(page_data.GetLength() > 8)
	{
		page_data = page_data.Mid(0,8);
	}

	str__conv_data = Fnc__HEX_Conver(page_data);


PAGEWRITE_RTY:

	// ...
	log_msg.Format("Write [%s] Data Start...", str__conv_data);
	Fnc__LOG(log_msg);

	nRet = soCH__WRITE_PAGE_DATA[page_index]->Set__DATA(str__conv_data);

	// ...
	CString err_code;
	diCH__FAILURE_CODE->Get__DATA(err_code);

	log_msg.Format("Ret : %d, err_code: %s", nRet, err_code);
	Fnc__LOG(log_msg);

	// ...
	flag = Fnc__Check_Online(p_alarm, "");	

	if(flag == 0)		goto PAGEWRITE_RTY;
	if(flag <  0)		return -1;

	return nRet;
}

int  CObj__LF80_SERIAL::
Is__LP_AUTO_MODE()
{
	if( (dCH__OTR_IN_LP__FA_MODE->Check__DATA("AUTO") > 0) 
		&&  (dCH__OTR_IN_LP__FA_SERVICE_MODE->Check__DATA("YES") > 0) )
	{
		return 1;
	}

	return -1;
}
