#include "StdAfx.h"
#include "CRes__ALARM_INFO.h"


CRes__ALARM_REPORT mRes__ALARM_IREPORT;


// ...
CRes__ALARM_REPORT::CRes__ALARM_REPORT()
{
	InitializeCriticalSection(&mCS_LOCK);

}
CRes__ALARM_REPORT::~CRes__ALARM_REPORT()
{
	_Clear__ALL_Of_REPORT_NO();

	DeleteCriticalSection(&mCS_LOCK);
}	

// ...
void CRes__ALARM_REPORT::
_Clear__ALL_Of_REPORT_NO()
{
	int i_limit = pList__REPORT_NO.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CDB__ALARM_REPORT* p_db = (CDB__ALARM_REPORT*) pList__REPORT_NO[i];
		delete p_db;
	}
	pList__REPORT_NO.RemoveAll();
}

void CRes__ALARM_REPORT::
_Load__EQP_ID_Of_REPORT_NO(const int eqp_id, 
						   const int ext_id)
{
	bool active__eqp_id = false;

	int i_limit = pList__REPORT_NO.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CDB__ALARM_REPORT* p_db = (CDB__ALARM_REPORT*) pList__REPORT_NO[i];
		if(p_db->iEQP_ID != eqp_id)			continue;

		active__eqp_id = true;

		// ...
		bool active__ext_id = false;

		int k_limit = p_db->iList__EXT_ID.GetSize();
		int k;

		for(k=0; k<k_limit; k++)
		{
			if(p_db->iList__EXT_ID[k] != ext_id)
				continue;

			active__ext_id = true;
			break;
		}

		if(!active__ext_id)
		{
			p_db->iList__EXT_ID.Add(ext_id);
		}
		break;
	}

	if(!active__eqp_id)
	{
		CDB__ALARM_REPORT* p_db = new CDB__ALARM_REPORT;
		pList__REPORT_NO.Add(p_db);

		p_db->iEQP_ID = eqp_id;
		p_db->iList__EXT_ID.Add(ext_id);
	}
}

// ...
bool CRes__ALARM_REPORT::
Check__EXT_ID_Of_REPORT_NO(const int eqp_id, const int ext_id)
{
	EnterCriticalSection(&mCS_LOCK);

	bool active__ext_id = false;

	int i_limit = pList__REPORT_NO.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CDB__ALARM_REPORT* p_db = (CDB__ALARM_REPORT*) pList__REPORT_NO[i];
		if(p_db->iEQP_ID != eqp_id)			continue;

		int k_limit = p_db->iList__EXT_ID.GetSize();
		int k;

		for(k=0; k<k_limit; k++)
		{
			if(p_db->iList__EXT_ID[k] != ext_id)
				continue;

			active__ext_id = true;
			break;
		}
		break;
	}

	LeaveCriticalSection(&mCS_LOCK);
	return active__ext_id;
}

void CRes__ALARM_REPORT::
Report__ALL_Of_REPORT_NO()
{
	EnterCriticalSection(&mCS_LOCK);

	CString db_msg;
	CString db_bff;

	int r_count = 0;

	int i_limit = pList__REPORT_NO.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CDB__ALARM_REPORT* p_db = (CDB__ALARM_REPORT*) pList__REPORT_NO[i];

		db_bff.Format(" * Eqp_ID : %1d \n", p_db->iEQP_ID);
		db_msg += db_bff;

		int k_limit = p_db->iList__EXT_ID.GetSize();
		int k;

		for(k=0; k<k_limit; k++)
		{
			db_bff.Format(" ** %02d)  %1d \n", k+1,p_db->iList__EXT_ID[k]);
			db_msg += db_bff;

			r_count++;
		}
	}

	printf(" * CRes__ALARM_REPORT::Report__ALL_Of_REPORT_NO() ... \n");
	printf(" ** r_count <- [%1d] \n", r_count);
	printf(db_msg);
	printf("\n");

	LeaveCriticalSection(&mCS_LOCK);
}
