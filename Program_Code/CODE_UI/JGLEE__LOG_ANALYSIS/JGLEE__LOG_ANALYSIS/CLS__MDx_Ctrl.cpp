#include "stdafx.h"
#include "CLS__MDx_Ctrl.h"


// ...
CDB__MDx_Ctrl::CDB__MDx_Ctrl()
{
	InitializeCriticalSection(&mCS_LOCK);

	pCUR__GROUP_INFO = NULL;
}
CDB__MDx_Ctrl::~CDB__MDx_Ctrl()
{
	Clear__ALL_INFO();

	DeleteCriticalSection(&mCS_LOCK);
}

// ...
CDB__MDx_Info* CDB__MDx_Ctrl::
_Get_Addr__CDB_MDx_Info(const CString& md_name)
{
	int i_limit = pList__MDx_INFO.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CDB__MDx_Info *p_md = (CDB__MDx_Info *) pList__MDx_INFO[i];
		
		if(p_md->sMDx_NAME.CompareNoCase(md_name) != 0)			continue;

		return p_md;
	}
	return NULL;
}

void CDB__MDx_Ctrl::
Clear__ALL_INFO()
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		int i_limit = pList__MDx_INFO.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CDB__MDx_Info *p_info = (CDB__MDx_Info *) pList__MDx_INFO[i];
			delete p_info;
		}
		pList__MDx_INFO.RemoveAll();

		pCUR__GROUP_INFO = NULL;
	}

	LeaveCriticalSection(&mCS_LOCK);
}

void CDB__MDx_Ctrl::
Load__MDx_NAME(const CString& md_name)
{
	EnterCriticalSection(&mCS_LOCK);

	CDB__MDx_Info *p_info = _Get_Addr__CDB_MDx_Info(md_name);

	if(p_info == NULL)
	{
		p_info = new CDB__MDx_Info;
		pList__MDx_INFO.Add(p_info);

		p_info->sMDx_NAME = md_name;
	}

	LeaveCriticalSection(&mCS_LOCK);
}
void CDB__MDx_Ctrl::
Change__First_MDx_NAME(const CString& md_name)
{
	EnterCriticalSection(&mCS_LOCK);

	if(pList__MDx_INFO.GetSize() > 0)
	{
		CDB__MDx_Info *p_md = (CDB__MDx_Info *) pList__MDx_INFO[0];

		p_md->sMDx_NAME = md_name;
	}

	LeaveCriticalSection(&mCS_LOCK);
}

void CDB__MDx_Ctrl::
Load__GROUP_NAME_OF_MDx(const CString& md_name,
					    const CString& group_name)
{
	EnterCriticalSection(&mCS_LOCK);

	CDB__MDx_Info *p_info = _Get_Addr__CDB_MDx_Info(md_name);

	if(p_info != NULL)
	{
		p_info->Load__GROUP_NAME(group_name);
		
		pCUR__GROUP_INFO = p_info->_Get__GROUP_ADDR(group_name);
	}
	else
	{
		pCUR__GROUP_INFO = NULL;
	}

	LeaveCriticalSection(&mCS_LOCK);
}
void CDB__MDx_Ctrl::
Load__CHANNEL_ITEM(const CString& ch_name,
			       const CString& cfg_name,
			       const CString& cfg_unit,
			       const CString& cfg_comment)
{
	EnterCriticalSection(&mCS_LOCK);

	if(pCUR__GROUP_INFO != NULL)
	{
		pCUR__GROUP_INFO->Load__CHANNEL_ITEM(ch_name, cfg_name, cfg_unit, cfg_comment);
	}

	LeaveCriticalSection(&mCS_LOCK);
}

CString CDB__MDx_Ctrl::
Get__ALL_INFO()
{
	EnterCriticalSection(&mCS_LOCK);

	CString str_info = "";

	// ...
	{
		int i_limit = pList__MDx_INFO.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CDB__MDx_Info *p_info = (CDB__MDx_Info *) pList__MDx_INFO[i];

			str_info += p_info->Get__ALL_INFO();
			str_info += "\n";
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return str_info;
}

void CDB__MDx_Ctrl::
Get__ALL_CHANNEL_LIST(CStringArray& l_channel)
{
	EnterCriticalSection(&mCS_LOCK);

	l_channel.RemoveAll();

	int i_limit = pList__MDx_INFO.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CDB__MDx_Info *p_info = (CDB__MDx_Info *) pList__MDx_INFO[i];

		p_info->Get__CHANNEL_LIST(l_channel);
	}

	LeaveCriticalSection(&mCS_LOCK);
}

CString CDB__MDx_Ctrl::Get__First_MDx_NAME()
{
	EnterCriticalSection(&mCS_LOCK);

	CString md_name = "";

	if(pList__MDx_INFO.GetSize() > 0)
	{
		CDB__MDx_Info *p_md = (CDB__MDx_Info *) pList__MDx_INFO[0];

		md_name = p_md->sMDx_NAME;
	}

	LeaveCriticalSection(&mCS_LOCK);
	return md_name;
}
void CDB__MDx_Ctrl::
Get__MDx_LIST(CStringArray& l_md_name)
{
	EnterCriticalSection(&mCS_LOCK);

	l_md_name.RemoveAll();

	// ...
	int i_limit = pList__MDx_INFO.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CDB__MDx_Info *p_md = (CDB__MDx_Info *) pList__MDx_INFO[i];

		l_md_name.Add(p_md->sMDx_NAME);
	}

	LeaveCriticalSection(&mCS_LOCK);
}

void CDB__MDx_Ctrl::
Get__GROUP_LIST(const CString& md_name,
				CStringArray& l_group)
{
	EnterCriticalSection(&mCS_LOCK);

	l_group.RemoveAll();

	CDB__MDx_Info *p_md = _Get_Addr__CDB_MDx_Info(md_name);
	
	if(p_md != NULL)		
		p_md->Get__GROUP_LIST(l_group);

	LeaveCriticalSection(&mCS_LOCK);
}
int  CDB__MDx_Ctrl::
Get__CHANNEL_LIST_OF_GROUP(const CString& md_name,
						   const CString& group_name,
						   CStringArray& l_channel,
						   CStringArray& l_name,
						   CStringArray& l_unit,
						   CStringArray& l_comment)
{
	EnterCriticalSection(&mCS_LOCK);

	int check_flag = -1;

	// ...
	{
		l_channel.RemoveAll();
		l_name.RemoveAll();
		l_unit.RemoveAll();
		l_comment.RemoveAll();
	}

	CDB__MDx_Info *p_md = _Get_Addr__CDB_MDx_Info(md_name);
	if(p_md != NULL)
	{
		p_md->Get__CHANNEL_LIST(group_name, l_channel, l_name, l_unit, l_comment);

		check_flag = 1;
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}

int  CDB__MDx_Ctrl::
Get__INFO_OF_CH_NAME(const CString& ch_name,
					 CString& md_name,
					 CString& group_name,
					 CString& str_name,
					 CString& str_unit,
					 CString& str_comment)
{
	EnterCriticalSection(&mCS_LOCK);

	int check_flag = -1;

	int i_limit = pList__MDx_INFO.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CDB__MDx_Info *p_info = (CDB__MDx_Info *) pList__MDx_INFO[i];
	
		if(p_info->Get__INFO_OF_CH_NAME(ch_name, group_name,str_name,str_unit,str_comment) < 0)
			continue;

		md_name = p_info->sMDx_NAME;

		check_flag = 1;
		break;
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}

