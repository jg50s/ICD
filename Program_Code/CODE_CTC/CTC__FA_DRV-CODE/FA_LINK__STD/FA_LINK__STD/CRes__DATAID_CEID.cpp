#include "StdAfx.h"
#include "CRes__DATAID_CEID.h"


CRes__DATAID_CEID mRes__DATAID_CEID;


// ...
CRes__DATAID_CEID::CRes__DATAID_CEID()
{
	InitializeCriticalSection(&mCS_LOCK);
}
CRes__DATAID_CEID::~CRes__DATAID_CEID()
{
	DeleteCriticalSection(&mCS_LOCK);
}

void CRes__DATAID_CEID::Load__INFO(const int ceid,const int dataid)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	int flag = -1;

	int limit = iList__CEID.GetSize();
	int i;

	for(i=0;i<limit;i++)
	{
		if(ceid != (int) iList__CEID[i])
		{
			continue;
		}

		iList__DATAID[i] = dataid;

		flag = 1;
		break;
	}

	if(flag < 0)
	{
		iList__CEID.Add(ceid);
		iList__DATAID.Add(dataid);
	}

	LeaveCriticalSection(&mCS_LOCK);
}
int  CRes__DATAID_CEID::Get__DATAID(const int ceid,int& dataid)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	int flag = -1;

	int limit = iList__CEID.GetSize();
	int i;

	for(i=0;i<limit;i++)
	{
		if(ceid != (int) iList__CEID[i])
		{
			continue;
		}

		dataid = (int) iList__DATAID[i];

		flag = 1;
		break;
	}

	LeaveCriticalSection(&mCS_LOCK);
	return flag;
}
