#pragma once


class CStep_Info
{
public:
	CStep_Info()
	{
		sList__Channe_Type.RemoveAll();
		sList__Channe_Name.RemoveAll();
		sList__Channe_Data.RemoveAll();
		sList__Step_Name.RemoveAll();
	}
	~CStep_Info()
	{

	}

	int Add__Step_Info(const CString& ch_type,const CString& ch_name,const CString& ch_data)
	{
		sList__Channe_Type.Add(ch_type);
		sList__Channe_Name.Add(ch_name);
		sList__Channe_Data.Add(ch_data);
		sList__Step_Name.Add("");
		return 1;
	}

	// ...
	int iStep_ID;
	CStringArray sList__Channe_Type;
	CStringArray sList__Channe_Name;
	CStringArray sList__Channe_Data;
	CStringArray sList__Step_Name;
};
class CRcp_Info
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList__Step_Info;
	CStep_Info *pLast_Step;

public:
	CRcp_Info()
	{
		InitializeCriticalSection(&mCS_LOCK);

		pLast_Step = NULL;
	}
	~CRcp_Info()
	{
		Clear__All();

		DeleteCriticalSection(&mCS_LOCK);
	}

	// ...
	void Clear__All()
	{
		EnterCriticalSection(&mCS_LOCK);

		CStep_Info *p_step;

		int i_limit = pList__Step_Info.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			p_step = (CStep_Info *) pList__Step_Info[i];
			delete p_step;
		}
		pList__Step_Info.RemoveAll();

		LeaveCriticalSection(&mCS_LOCK);
	}

	int Add__Step_ID(const int step_id)
	{
		EnterCriticalSection(&mCS_LOCK);

		CStep_Info *p_step = new CStep_Info;
		pList__Step_Info.Add(p_step);
		pLast_Step = p_step;

		p_step->iStep_ID = step_id;

		LeaveCriticalSection(&mCS_LOCK);
		return 1;
	}
	int Add__Step_Info(const CString& ch_type,const CString& ch_name,const CString& ch_data)
	{
		EnterCriticalSection(&mCS_LOCK);

		int flag = pLast_Step->Add__Step_Info(ch_type,ch_name,ch_data);

		LeaveCriticalSection(&mCS_LOCK);
		return flag;
	}

	// ...
	int Get__Step_Size()
	{
		EnterCriticalSection(&mCS_LOCK);

		int step_size = pList__Step_Info.GetSize();

		LeaveCriticalSection(&mCS_LOCK);
		return step_size;
	}

	CStep_Info* Get__Step_Info(const int step_index)
	{
		EnterCriticalSection(&mCS_LOCK);

		CStep_Info *p_step = NULL;

		if((step_index >= 0) && (step_index < pList__Step_Info.GetSize()))
		{
			p_step = (CStep_Info*) pList__Step_Info[step_index];
		}

		LeaveCriticalSection(&mCS_LOCK);
		return p_step;
	}
};

class CPara_Info
{
private:
	CRITICAL_SECTION mCS_LOCK;

public:
	CStringArray sList__Para_Channel;
	CStringArray sList__Para_Title;
	CStringArray sList__Para_Ch_Title;
	CStringArray sList__Para_Category;

	// ...
	CPara_Info()
	{
		InitializeCriticalSection(&mCS_LOCK);
	}
	~CPara_Info()
	{
		DeleteCriticalSection(&mCS_LOCK);
	}

	void Clear__All()
	{
		EnterCriticalSection(&mCS_LOCK);

		sList__Para_Channel.RemoveAll();
		sList__Para_Title.RemoveAll();
		sList__Para_Ch_Title.RemoveAll();
		sList__Para_Category.RemoveAll();

		LeaveCriticalSection(&mCS_LOCK);
	}

	void Add__New_Parameter()
	{
		EnterCriticalSection(&mCS_LOCK);

		sList__Para_Channel.Add("");
		sList__Para_Title.Add("");
		sList__Para_Ch_Title.Add("");
		sList__Para_Category.Add("");

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Load__Para_Channel(const CString& ch_name)
	{
		EnterCriticalSection(&mCS_LOCK);

		int db_index = sList__Para_Channel.GetSize() - 1;

		if(db_index >= 0)		
			sList__Para_Channel[db_index] = ch_name;

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Load__Para_Titlel(const CString& title)
	{
		EnterCriticalSection(&mCS_LOCK);

		int db_index = sList__Para_Title.GetSize() - 1;

		if(db_index >= 0)		
			sList__Para_Title[db_index] = title;

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Load__Para_Ch_Titlel(const CString& title)
	{
		EnterCriticalSection(&mCS_LOCK);

		int db_index = sList__Para_Ch_Title.GetSize() - 1;

		if(db_index >= 0)		
			sList__Para_Ch_Title[db_index] = title;

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Load__Para_Category(const CString& category)
	{
		EnterCriticalSection(&mCS_LOCK);

		int db_index = sList__Para_Category.GetSize() - 1;

		if(db_index >= 0)		
			sList__Para_Category[db_index] = category;

		LeaveCriticalSection(&mCS_LOCK);
	}

	CString Get__Para_Title(const CString& ch_name, CString& str_category)
	{
		EnterCriticalSection(&mCS_LOCK);

		CString str_title = "";
		str_category = "";

		int i_limit = sList__Para_Channel.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(ch_name.CompareNoCase(sList__Para_Channel[i]) != 0)
			{
				continue;
			}

			str_title    = sList__Para_Title[i];
			str_category = sList__Para_Category[i];
			break;
		}

		LeaveCriticalSection(&mCS_LOCK);
		return str_title;
	}
};

