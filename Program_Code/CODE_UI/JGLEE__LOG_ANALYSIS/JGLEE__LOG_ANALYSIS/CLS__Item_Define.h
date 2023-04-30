#pragma once


class CLS__Item_Define
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CStringArray sList__NAME;
	CStringArray sList__DATA;

public:
	CLS__Item_Define()	
	{
		InitializeCriticalSection(&mCS_LOCK);

		Clear();
	}
	~CLS__Item_Define() 
	{

		DeleteCriticalSection(&mCS_LOCK);
	}

	void Clear()	
	{
		EnterCriticalSection(&mCS_LOCK);

		sList__NAME.RemoveAll();
		sList__DATA.RemoveAll();

		LeaveCriticalSection(&mCS_LOCK);
	}

	void Load__INFO(const CString& para_name,const CString& para_data)
	{
		EnterCriticalSection(&mCS_LOCK);

		int check_flag = -1;

		int i_limit = sList__NAME.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(para_name.CompareNoCase(sList__NAME[i]) != 0)
				continue;

			sList__DATA[i] = para_data;

			check_flag = 1;
			break;
		}

		if(check_flag < 0)
		{
			sList__NAME.Add(para_name);
			sList__DATA.Add(para_data);
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
	int Get__DATA(const CString& para_name, CString& para_data)
	{
		EnterCriticalSection(&mCS_LOCK);

		int check_flag = -1;

		int i_limit = sList__NAME.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(para_name.CompareNoCase(sList__NAME[i]) != 0)
				continue;

			para_data = sList__DATA[i];

			check_flag = 1;
			break;
		}

		LeaveCriticalSection(&mCS_LOCK);
		return check_flag;
	}

	CString Check(const CString& check_data)
	{
		EnterCriticalSection(&mCS_LOCK);

		CString str_data = check_data;

		int i_limit = sList__NAME.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CString def_name = sList__NAME[i];
			CString def_data = sList__DATA[i];

			str_data.Replace(def_name,def_data);
		}

		LeaveCriticalSection(&mCS_LOCK);
		return str_data;
	}

	void Display__ALL_DATA()
	{
		EnterCriticalSection(&mCS_LOCK);

		CString log_msg;
		CString log_bff;

		log_msg = "CLS__Item_Define ... \n";

		int i_limit = sList__NAME.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			log_bff.Format(" * %1d) [%s] [%s] \n", i+1,sList__NAME[i],sList__DATA[i]);
			log_msg += log_bff;
		}

		log_msg += "\n";
		printf(log_msg);

		LeaveCriticalSection(&mCS_LOCK);
	}
};

class CLS__PMx_Info
{
public:
	CLS__PMx_Info()	
	{

	}
	~CLS__PMx_Info() 
	{

	}

	// ...
	int iPMx_ID;

	CStringArray sList__CHANNEL;
	CStringArray sList__TITLE;
};
class CLS__PMx_Ctrl
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList__INFO;
	CLS__PMx_Info *pCur_PMx;

public:
	CLS__PMx_Ctrl()	
	{
		InitializeCriticalSection(&mCS_LOCK);

		Clear();
	}
	~CLS__PMx_Ctrl() 
	{

		DeleteCriticalSection(&mCS_LOCK);
	}

	void Clear()	
	{
		EnterCriticalSection(&mCS_LOCK);

		pCur_PMx = NULL;

		int i_limit = pList__INFO.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CLS__PMx_Info *p_info = (CLS__PMx_Info *) pList__INFO[i];
			delete p_info;
		}
		pList__INFO.RemoveAll();

		LeaveCriticalSection(&mCS_LOCK);
	}

	void Set__PMx_ID(const int pm_id)
	{
		EnterCriticalSection(&mCS_LOCK);

		int check_flag = -1;

		int i_limit = pList__INFO.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CLS__PMx_Info *p_info = (CLS__PMx_Info *) pList__INFO[i];
			if(p_info->iPMx_ID != pm_id)		continue;

			pCur_PMx= p_info;

			check_flag = 1;
			break;
		}

		if(check_flag < 0)
		{
			CLS__PMx_Info *p_info = new CLS__PMx_Info;
			pList__INFO.Add(p_info);

			p_info->iPMx_ID = pm_id;
			pCur_PMx = p_info;
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Load__INFO(const CString& str_channel,const CString& str_title)
	{
		EnterCriticalSection(&mCS_LOCK);

		if(pCur_PMx != NULL)
		{
			int check_flag = -1;

			int i_limit = pCur_PMx->sList__CHANNEL.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				if(str_channel.CompareNoCase(pCur_PMx->sList__CHANNEL[i]) != 0)
					continue;

				pCur_PMx->sList__TITLE[i] = str_title;

				check_flag = 1;
				break;
			}

			if(check_flag < 0)
			{
				pCur_PMx->sList__CHANNEL.Add(str_channel);
				pCur_PMx->sList__TITLE.Add(str_title);
			}
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Load__EMPTY_LINE()
	{
		EnterCriticalSection(&mCS_LOCK);

		if(pCur_PMx != NULL)
		{
			pCur_PMx->sList__CHANNEL.Add("&LINE");
			pCur_PMx->sList__TITLE.Add("");
		}

		LeaveCriticalSection(&mCS_LOCK);
	}

	int Get__ALL_CHANNEL_INFO(CStringArray& l_channel)
	{
		EnterCriticalSection(&mCS_LOCK);

		// ...
		{
			l_channel.RemoveAll();

			int i_limit = pList__INFO.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				CLS__PMx_Info *p_info = (CLS__PMx_Info*) pList__INFO[i];

				int k_limit = p_info->sList__CHANNEL.GetSize();
				int k;

				for(k=0; k<k_limit; k++)
				{
					l_channel.Add(p_info->sList__CHANNEL[k]);
				}
			}
		}

		LeaveCriticalSection(&mCS_LOCK);
		return 1;
	}
	int Get__CHANNEL_INFO(const int pm_id,
						  CStringArray& l_channel)
	{
		EnterCriticalSection(&mCS_LOCK);

		// ...
		{
			l_channel.RemoveAll();

			int i_limit = pList__INFO.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				CLS__PMx_Info *p_info = (CLS__PMx_Info*) pList__INFO[i];
				if(p_info->iPMx_ID != pm_id)		continue;

				l_channel.Copy(p_info->sList__CHANNEL);
				break;
			}
		}

		LeaveCriticalSection(&mCS_LOCK);
		return 1;
	}

	int Get__PMx_LIST(CUIntArray& l_pm)
	{
		EnterCriticalSection(&mCS_LOCK);

		// ...
		{
			l_pm.RemoveAll();

			int i_limit = pList__INFO.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				CLS__PMx_Info *p_info = (CLS__PMx_Info*) pList__INFO[i];

				l_pm.Add(p_info->iPMx_ID);
			}
		}

		LeaveCriticalSection(&mCS_LOCK);
		return 1;
	}
	int Get__PMx_INFO(const int pm_id,
					  CStringArray& l_channel, 
					  CStringArray& l_title)
	{
		EnterCriticalSection(&mCS_LOCK);

		// ...
		{
			l_channel.RemoveAll();
			l_title.RemoveAll();
		}

		// ...
		{
			int i_limit = pList__INFO.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				CLS__PMx_Info *p_info = (CLS__PMx_Info*) pList__INFO[i];
				if(p_info->iPMx_ID != pm_id)		continue;

				l_channel.Copy(p_info->sList__CHANNEL);
				l_title.Copy(p_info->sList__TITLE);
				break;
			}
		}

		LeaveCriticalSection(&mCS_LOCK);
		return 1;
	}
};
