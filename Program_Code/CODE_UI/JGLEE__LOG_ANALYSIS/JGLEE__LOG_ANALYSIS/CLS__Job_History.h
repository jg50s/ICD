#pragma once


class CLS__Job_Log_Info
{
public:
	CString sLog_Date;

	CStringArray sList_JobID;
	CStringArray sList_LotID;
	CStringArray sList_PortID;
	CStringArray sList_SlotID;
	CStringArray sList_CstID;
	CStringArray sList_Dir;
	CStringArray sList_Time;

public:
	CLS__Job_Log_Info()
	{

	}
	~CLS__Job_Log_Info()
	{

	}
};

class CLS__Job_Log_Ctrl
{
private:
	CPtrArray pList__Log_Info;
	CLS__Job_Log_Info* pCUR__Log_Info;

	CLS__Job_Log_Info* _Get_Addr__Log_Info(const CString& log_date)
	{
		int i_limit = pList__Log_Info.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CLS__Job_Log_Info* p_info 
				= (CLS__Job_Log_Info*) pList__Log_Info[i];

			if(p_info->sLog_Date.CompareNoCase(log_date) != 0)
				continue;

			return p_info;
		}
		return NULL;
	}

public:
	CLS__Job_Log_Ctrl()
	{
		pCUR__Log_Info = NULL;
	}
	~CLS__Job_Log_Ctrl()
	{

	}

	// ...
	void Clear_ALL()
	{
		int i_limit = pList__Log_Info.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CLS__Job_Log_Info* p_info 
				= (CLS__Job_Log_Info*) pList__Log_Info[i];

			delete p_info;
		}

		pList__Log_Info.RemoveAll();
		pCUR__Log_Info = NULL;
	}

	// ...
	void Load__Log_Date(const CString& log_date)
	{
		CLS__Job_Log_Info* p_info = _Get_Addr__Log_Info(log_date);
		
		if(p_info == NULL)
		{
			p_info = new CLS__Job_Log_Info;
			pList__Log_Info.Add(p_info);

			p_info->sLog_Date = log_date;
		}

		pCUR__Log_Info = p_info;
	}
	void Load__Log_Info_With_No_Slot(const CString& log_portid,
									 const CString& log_cstid,
									 const CString& log_jobid,
									 const CString& log_lotid,
									 const CString& log_dir,
									 const CString& log_time)
	{
		Load__Log_Info(log_portid, "*.*", log_cstid, log_jobid, log_lotid, log_dir, log_time);
	}
	void Load__Log_Info(const CString& log_portid,
						const CString& log_slotid,
						const CString& log_cstid,
						const CString& log_jobid,
						const CString& log_lotid,
						const CString& log_dir,
						const CString& log_time)
	{
		if(pCUR__Log_Info != NULL)
		{
			pCUR__Log_Info->sList_PortID.Add(log_portid);
			pCUR__Log_Info->sList_SlotID.Add(log_slotid);
			pCUR__Log_Info->sList_CstID.Add(log_cstid);
			pCUR__Log_Info->sList_JobID.Add(log_jobid);
			pCUR__Log_Info->sList_LotID.Add(log_lotid);
			pCUR__Log_Info->sList_Dir.Add(log_dir);
			pCUR__Log_Info->sList_Time.Add(log_time);
		}
	}

	// ...
	int  Get__Log_Size()
	{
		return pList__Log_Info.GetSize();
	}
	CLS__Job_Log_Info* Get__Log_Info(const int log_i)
	{
		if(log_i < pList__Log_Info.GetSize())
		{
			return (CLS__Job_Log_Info*) pList__Log_Info[log_i];
		}
		return NULL;
	}
};
