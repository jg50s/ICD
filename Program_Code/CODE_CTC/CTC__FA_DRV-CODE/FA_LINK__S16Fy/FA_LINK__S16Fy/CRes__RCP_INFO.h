#pragma once


class CRes__Step_Info
{
public:
	CRes__Step_Info()
	{

	}
	~CRes__Step_Info()
	{
		sList_CH_Type.RemoveAll();
		sList_CH_Name.RemoveAll();
		sList_CH_Data.RemoveAll();
	}

	// ...
	int iStep_ID;

	CStringArray sList_CH_Type;
	CStringArray sList_CH_Name;
	CStringArray sList_CH_Data;
};
class CRes__PM_Info
{
public:
	CRes__PM_Info()
	{

	}
	~CRes__PM_Info()
	{
		CRes__Step_Info *p_info;

		int limit = pList__Step_Info.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			p_info = (CRes__Step_Info*) pList__Step_Info[i];
			delete p_info;
		}
		pList__Step_Info.RemoveAll();
	}

	// ...
	CString sPJobID;
	int iPM_ID;

	// CRes__Step_Info
	CPtrArray pList__Step_Info;
};

class CRes__Rcp_Info
{
private:
	CRITICAL_SECTION mCS_LOCK;

	// CRes__PM_Info
	CPtrArray pList__PM_Info;

public:
	CRes__Rcp_Info();
	~CRes__Rcp_Info();

	// ...
	int Clear__Rcp_Info();

	int Load__Rcp_Info(const CString& pjobid,
						const int pm_id,
						const int step_id,
						const CString& ch_type,
						const CString& ch_name,
						const CString& ch_data);

	int Get__PJobID_List(CStringArray& l_pjobid);

	int Get__PM_ID_List(const CString& pjobid,
						CUIntArray& l_pm_id);

	int Get__Rcp_Info(const CString& pjobid,
						const int pm_id,
						CString& rcp_info);
};
