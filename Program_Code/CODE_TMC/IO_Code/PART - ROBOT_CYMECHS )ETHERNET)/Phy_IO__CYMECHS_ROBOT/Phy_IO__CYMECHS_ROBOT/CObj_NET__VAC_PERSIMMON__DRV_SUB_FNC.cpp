#include "StdAfx.h"
#include "CObj_NET__VAC_PERSIMMON.h"
#include "CObj_NET__VAC_PERSIMMON__DEF.h"

#include "math.h"
#include "Macro_Function.h"
#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
int  CObj_NET__VAC_PERSIMMON
::Proc__CMMD_RSP(const CString& var_name, 
				 const CString& str_xxx,
				 const double to_sec,
				 const BOOL active_prt,
				 CStringArray& l_rsp,
				 CStringArray& l_err)
{
	CString str_data;
	CString err_msg;
	CString key_word;
	CString log_msg;
	CString log_bff;

	// ...
	{
		l_rsp.RemoveAll();
		l_err.RemoveAll();
	}

	// ...
	{
		mX_Net->CLEAR__BUFFER(&err_msg);

		if(err_msg.GetLength() > 0)
		{
			log_msg.Format("Var_Name(%s) - Clear__Buffer() .. \n", var_name);
			log_msg += " * Clear_Msg : ";
			log_msg += err_msg;
			log_msg += "\n";

			Fnc__DRV_LOG(log_msg);			
		}

		//
		mX_Net->CLEAR__MEM_BUFFER(&err_msg);

		if(err_msg.GetLength() > 0)
		{
			log_msg.Format("Var_Name(%s) - Clear__Mem_Buffer() .. \n", var_name);
			log_msg += " * Clear_Mem_Buffer : ";
			log_msg += err_msg;
			log_msg += "\n";

			Fnc__DRV_LOG(log_msg);			
		}
	}

	CString str_cmmd;
	str_cmmd.Format("Custom2 %s", str_xxx);

	// ...
	{
		log_msg.Format(" %s -> %s%s \n", var_name,str_cmmd,sEnd_OutStr);

		Fnc__DRV_LOG(log_msg);
	}

	mX_Net->DATA__SEND(str_cmmd, 1, &err_msg);

	// ...
	SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
	x_timer_ctrl->START__COUNT_UP(99999.9);

	double ref_sec = to_sec;
	int r_cnt = 0;

	while(1)
	{
		int r_len = mX_Net->DATA__RECV_QUEUE(&str_data, 1, &err_msg);
		if(r_len < 0)
		{
			// Check : Timeout ...
			if(x_timer_ctrl->Get__CURRENT_TIME() > ref_sec)
			{
				// Error Msg ...
				{
					log_msg.Format("Error : %s <- Timeout(%.0f sec) \n", var_name,ref_sec);

					log_bff.Format("  * r_cnt [%1d] \n", r_cnt);
					log_msg += log_bff;

					Fnc__DRV_LOG(log_msg);
				}

				m_nCommState = OFFLINE;
				return -1;
			}
			continue;
		}

		r_cnt++;

		// ...
		{
			log_msg.Format(" %s <- %s%s\n", var_name,str_data,sEnd_InStr);

			log_bff.Format("  * r_cnt [%1d] \n", r_cnt);
			log_msg += log_bff;

			Fnc__DRV_LOG(log_msg);
		}

		// ...
		int check_done = -1;

		int k_limit = 2;
		int k;

		for(k=0; k<k_limit; k++)
		{
				 if(k == 0)		key_word = _RDY;
			else if(k == 1)		key_word = _ERR;
			else				break;

			// Check : Keyword ...
			CStringArray l_para;

			if(Check__MSG_KEY_WORD(str_data, key_word,l_para) > 0)
			{	
				// ...
				int active_err = -1;

				if(key_word.CompareNoCase(_ERR) == 0)
				{
					active_err = 1;
				}

				// ...
				CString str_para;

				int i_limit = l_para.GetSize();
				int i;

				for(i=0; i<i_limit; i++)
				{
					str_para = l_para[i];

					if(active_err > 0)
					{
						l_err.Add(str_para);
					}
				}

				if((key_word.CompareNoCase(_RDY) == 0)
				|| (key_word.CompareNoCase(_ERR) == 0))
				{
					check_done = 1;
					break;
				}
			}
		}

		if(check_done > 0)
		{
			break;
		}

		// Response ...
		{
			CStringArray l_data;
			Check__MSG_KEY_WORD(str_data, " ", l_data);

			int i_limit = l_data.GetSize();
			int i;

			l_rsp.RemoveAll();

			for(i=0; i<i_limit; i++)
			{
				CString str_para = l_data[i];

				l_rsp.Add(str_para);
			}
		}
	}

	if(l_err.GetSize() > 0)
	{
		CString err_xxx = l_err[0];

		_Check__ERROR_CODE(err_xxx);
	}

	// ...
	{
		int i_limit;
		int i;

		// _RSP Info ...
		{
			i_limit = l_rsp.GetSize();

			log_msg.Format("_RSP Info (%1d) ... \n", i_limit);

			for(i=0; i<i_limit; i++)
			{
				log_bff.Format(" * %1d) [%s] \n", i+1,l_rsp[i]);
				log_msg += log_bff;
			}

			Fnc__DRV_LOG(log_msg);
		}

		// _ERR Info ...
		{
			i_limit = l_err.GetSize();

			log_msg.Format("_ERR Info (%1d) ... \n", i_limit);

			for(i=0; i<i_limit; i++)
			{
				log_bff.Format(" * %1d) [%s] \n", i+1,l_err[i]);
				log_msg += log_bff;
			}

			Fnc__DRV_LOG(log_msg);
		}
	}

	m_nCommState = ONLINE;
	return 1;
}

int  CObj_NET__VAC_PERSIMMON
::Check__MSG_KEY_WORD(const CString& str_data, 
					  const CString& key_word, 
					  CStringArray& l_para)
{
	int s_index = str_data.Find(key_word);
	if(s_index < 0)			return -1;

	s_index += key_word.GetLength();
	l_para.RemoveAll();

	// ...
	CString word = "";
	char ch;

	int i_limit = str_data.GetLength();
	int i;

	for(i=s_index; i<i_limit; i++)
	{
		ch = str_data.GetAt(i);

		if(ch == ' ')
		{
			if(word.GetLength() > 0)
			{
				l_para.Add(word);
			}

			word = "";
		}
		else
		{
			word += ch;
		}
	}

	if(word.GetLength() > 0)
	{
		l_para.Add(word);
	}
	return 1;
}

CString CObj_NET__VAC_PERSIMMON
::Get__STRING_OF_LIST(const CStringArray& l_str)
{
	CString str_line = "";

	int i_limit = l_str.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(i > 0)		str_line += " ";

		str_line += l_str[i];
	}
	return str_line;
}
