#include "StdAfx.h"
#include "CObj__UNIT_TYPE.h"


extern CString Macro__Get_Date_Time();



//--------------------------------------------------------------------------------
CDB__ALARM_CTRL::CDB__ALARM_CTRL()
{
	InitializeCriticalSection(&mCS_LOCK);
}
CDB__ALARM_CTRL::~CDB__ALARM_CTRL()
{
	DeleteCriticalSection(&mCS_LOCK);
}

// ...
void CDB__ALARM_CTRL::Load__ALM_OFFLINE(const int gas_id,const int gas_index, const CString& alm_msg)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		CDB__ALARM_INFO *p_info = new CDB__ALARM_INFO;
		pList_INFO.Add(p_info);

		p_info->iALM_ID  = ALID__GASx_OFFLINE + (gas_id-1);
		p_info->iGAS_ID  = gas_id;
		p_info->sALM_MSG = alm_msg;

		CString alm_bff;
		alm_bff.Format("PMC Time <- [%s] \n", Macro__Get_Date_Time());
		p_info->sALM_MSG += alm_bff;
	}

	if(pList_INFO.GetSize() > 30)
	{
		CDB__ALARM_INFO *p_info = (CDB__ALARM_INFO*) pList_INFO[0];
		delete p_info;

		pList_INFO.RemoveAt(0);
	}
	// ...

	LeaveCriticalSection(&mCS_LOCK);
}
void CDB__ALARM_CTRL::Load__ALM_CTRL_TIMEOUT(const int gas_id,const int gas_index, const CString& alm_msg)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		CDB__ALARM_INFO *p_info = new CDB__ALARM_INFO;
		pList_INFO.Add(p_info);

		p_info->iALM_ID  = ALID__GASx_CONTROL_TIMEOUT + (gas_id-1);
		p_info->iGAS_ID  = gas_id;
		p_info->sALM_MSG = alm_msg;

		CString alm_bff;
		alm_bff.Format("PMC Time <- [%s] \n", Macro__Get_Date_Time());
		p_info->sALM_MSG += alm_bff;
	}

	if(pList_INFO.GetSize() > 30)
	{
		CDB__ALARM_INFO *p_info = (CDB__ALARM_INFO*) pList_INFO[0];
		delete p_info;

		pList_INFO.RemoveAt(0);
	}
	// ...

	LeaveCriticalSection(&mCS_LOCK);
}

int  CDB__ALARM_CTRL::Get__ALM_INFO(int& alm_id,int& gas_id,CString& alm_msg)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	int flag = -1;

	if(pList_INFO.GetSize() > 0)
	{
		flag = 1;

		// ...
		CDB__ALARM_INFO *p_info = (CDB__ALARM_INFO*) pList_INFO[0];

		// ...
		{
			alm_id  = p_info->iALM_ID;
			gas_id  = p_info->iGAS_ID;
			alm_msg = p_info->sALM_MSG; 
		}

		delete p_info;
		pList_INFO.RemoveAt(0);
	}

	LeaveCriticalSection(&mCS_LOCK);
	return flag;
}
