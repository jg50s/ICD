#include "StdAfx.h"
#include "CObj__DB_INF.h"


// ...
int CObj__DB_INF::Call__POST_ALARM_LIST(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;
	CString log_bff;

	CUIntArray l_eqp_id;
	CUIntArray l_sys_id;
	CStringArray l_obj_name;
	CUIntArray l_internal_id;

	p_alarm->Get__Posted_All_Alarm(l_eqp_id,l_sys_id,l_obj_name,l_internal_id);
	int i_limit = l_eqp_id.GetSize();

	log_msg.Format(" Posted Alarm List (%1d) ... \n", i_limit);

	log_bff.Format("  * No.)  EqpID  SysID  Obj_Name  InternalID \n", i_limit);
	log_msg += log_bff;

	for(int i=0 ;i<i_limit; i++)
	{
		log_bff.Format("  * %1d)  [%1d]  [%1d]  [%s]  [%1d] \n", i+1,l_eqp_id[i],l_sys_id[i],l_obj_name[i],l_internal_id[i]);
		log_msg += log_bff;
	}

	printf(log_msg);
	return 1;
}

int CObj__DB_INF::Call__POST_ALARM_CLEAR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	p_alarm->Delete__Cleared_All_Alarm();
	return 1;
}

int CObj__DB_INF::Call__POST_ALARM_DB_SIZE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int db_size = p_alarm->Get__Posted_Alarm_DB_Size();

	printf(" Posted Alarm DB Size ... \n");
	printf("  * DB_Size <- [%1d] \n", db_size);
	printf("\n");

	return 1;
}

