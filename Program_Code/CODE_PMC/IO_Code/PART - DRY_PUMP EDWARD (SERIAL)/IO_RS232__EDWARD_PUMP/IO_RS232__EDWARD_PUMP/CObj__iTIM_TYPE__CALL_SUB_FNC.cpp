#include "StdAfx.h"
#include "CObj__iTIM_TYPE.h"

#include "math.h"



//------------------------------------------------------------------------------------
int  CObj__iTIM_TYPE::
Is__REMOTE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString title;
	CString msg;

	int nRet = p_variable->When__VARIABLE_DATA(diCH__CTRL_STS->Get__VARIABLE_NAME(), "REMOTE", 5.0);
	if(nRet < 0)
	{
		int alarm_id = ALID__CURRENT_STATUS__LOCAL_MODE;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);

		return OBJ_ABORT;
	}
	else if(nRet == 0)
	{
		msg.Format(" User Object Aborted...[ret:%d]", nRet);		Fnc__APP_LOG(msg);
		return OBJ_ABORT;
	}

	return OBJ_AVAILABLE;
}

int  CObj__iTIM_TYPE::
Is__OFFLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString title;
	CString msg;

	if(diCH__COMM_STS->Check__DATA("OFFLINE") > 0)
	{
		int alarm_id = ALID__OFFLINE_ALARM;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);

		return OBJ_ABORT;
	}

	return OBJ_AVAILABLE;
}
