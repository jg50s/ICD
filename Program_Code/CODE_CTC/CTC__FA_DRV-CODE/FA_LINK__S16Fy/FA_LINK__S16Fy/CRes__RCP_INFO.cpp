#include "StdAfx.h"
#include "CRes__Rcp_Info.h"


// ...
CRes__Rcp_Info::CRes__Rcp_Info()
{
	InitializeCriticalSection(&mCS_LOCK);
}
CRes__Rcp_Info::~CRes__Rcp_Info()
{
	Clear__Rcp_Info();

	DeleteCriticalSection(&mCS_LOCK);
}

// ...
int CRes__Rcp_Info::
Clear__Rcp_Info()
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		CRes__PM_Info *p_info;

		int limit = pList__PM_Info.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			p_info = (CRes__PM_Info *) pList__PM_Info[i];
			delete p_info;
		}
		pList__PM_Info.RemoveAll();
	}

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}

int CRes__Rcp_Info:: 
Load__Rcp_Info(const CString& pjobid,
			   const int pm_id,
			   const int step_id,
			   const CString& ch_type,
			   const CString& ch_name,
			   const CString& ch_data)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		CRes__PM_Info *p_pm;
		int check_pm = -1;

		int limit = pList__PM_Info.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			p_pm = (CRes__PM_Info*) pList__PM_Info[i];

			if(p_pm->sPJobID.CompareNoCase(pjobid) != 0)		continue;
			if(p_pm->iPM_ID != pm_id)							continue;

			// ...
			{
				CRes__Step_Info *p_step;
				int check_step = -1;

				int k_limit = p_pm->pList__Step_Info.GetSize();
				int k;

				for(k=0; k<k_limit; k++)
				{
					p_step = (CRes__Step_Info *) p_pm->pList__Step_Info[k];
					if(p_step->iStep_ID != step_id)		continue;

					// ...
					{
						check_step = 1;

						p_step->sList_CH_Type.Add(ch_type);
						p_step->sList_CH_Name.Add(ch_name);
						p_step->sList_CH_Data.Add(ch_data);
					}
				}

				if(check_step < 0)
				{
					p_step = new CRes__Step_Info;
					p_pm->pList__Step_Info.Add(p_step);

					// ...
					{
						p_step->iStep_ID = step_id;

						p_step->sList_CH_Type.Add(ch_type);
						p_step->sList_CH_Name.Add(ch_name);
						p_step->sList_CH_Data.Add(ch_data);
					}
				}
			}

			check_pm = 1;
			break;
		}

		if(check_pm < 0)
		{
			p_pm = new CRes__PM_Info;
			pList__PM_Info.Add(p_pm);

			p_pm->sPJobID = pjobid;
			p_pm->iPM_ID  = pm_id;

			// ...
			{
				CRes__Step_Info *p_step = new CRes__Step_Info;
				p_pm->pList__Step_Info.Add(p_step);

				// ...
				{
					p_step->iStep_ID = step_id;

					p_step->sList_CH_Type.Add(ch_type);
					p_step->sList_CH_Name.Add(ch_name);
					p_step->sList_CH_Data.Add(ch_data);
				}
			}
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}

int CRes__Rcp_Info:: 
Get__PJobID_List(CStringArray& l_pjobid)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		l_pjobid.RemoveAll();
	}

	// ...
	{
		CRes__PM_Info *p_pm;

		int limit = pList__PM_Info.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			p_pm = (CRes__PM_Info *) pList__PM_Info[i];

			l_pjobid.Add(p_pm->sPJobID);
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}

int CRes__Rcp_Info:: 
Get__PM_ID_List(const CString& pjobid,
				CUIntArray& l_pm_id)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	int flag = -1;

	l_pm_id.RemoveAll();

	// ...
	{
		CRes__PM_Info *p_pm;

		int limit = pList__PM_Info.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			p_pm = (CRes__PM_Info *) pList__PM_Info[i];

			if(p_pm->sPJobID.CompareNoCase(pjobid) != 0)		continue;

			l_pm_id.Add(p_pm->iPM_ID);
		}

		if(l_pm_id.GetSize() > 0)
		{
			flag = 1;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return flag;
}

int CRes__Rcp_Info:: 
Get__Rcp_Info(const CString& pjobid,
			  const int pm_id,
			  CString& rcp_info)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		rcp_info = "";
	}

	// ...
	int flag = -1;

	// ...
	{
		CRes__PM_Info *p_pm;
		CString rcp_bff;

		int limit = pList__PM_Info.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			p_pm = (CRes__PM_Info *) pList__PM_Info[i];

			if(p_pm->sPJobID.CompareNoCase(pjobid) != 0)		continue;
			if(p_pm->iPM_ID != pm_id)							continue;

			// ...
			{
				CRes__Step_Info *p_step;

				int k_limit = p_pm->pList__Step_Info.GetSize();
				int k;

				for(k=0; k<k_limit; k++)
				{
					p_step = (CRes__Step_Info *) p_pm->pList__Step_Info[k];

					// ...
					{
						rcp_bff.Format("@,%1d;\n", p_step->iStep_ID);
						rcp_info += rcp_bff;

						int t_limit = p_step->sList_CH_Type.GetSize();
						int t;

						for(t=0; t<t_limit; t++)
						{
							rcp_bff.Format("&,%s,%s,%s;\n", 
								p_step->sList_CH_Type[t],
								p_step->sList_CH_Name[t],
								p_step->sList_CH_Data[t]);
							rcp_info += rcp_bff;
						}
					}
				}
			}

			flag = 1;
			break;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return flag;
}
