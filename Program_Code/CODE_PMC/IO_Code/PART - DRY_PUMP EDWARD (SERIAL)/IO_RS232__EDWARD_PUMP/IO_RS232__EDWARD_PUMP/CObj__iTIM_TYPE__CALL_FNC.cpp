#include "StdAfx.h"
#include "CObj__iTIM_TYPE.h"
#include "CObj__iTIM_TYPE__DEF.h"



//-------------------------------------------------------------------------	
// Init -----
int  CObj__iTIM_TYPE::
Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__INIT(p_variable,p_alarm);
}

int  CObj__iTIM_TYPE::
Fnc__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(iACTIVE_SIM > 0)
	{
		diCH__COMM_STS->Set__DATA(STR__ONLINE);
		diCH__CTRL_STS->Set__DATA(STR__REMOTE);
	}

	if(Is__OFFLINE(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	dCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	return OBJ_AVAILABLE;
}

int  CObj__iTIM_TYPE::
Call__LOCAL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__LOCAL(p_variable,p_alarm);
}
int  CObj__iTIM_TYPE::
Fnc__LOCAL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int state;
	int timeout;
	CString msg;

CMD_RTY:

	if(iACTIVE_SIM > 0)
	{
		diCH__COMM_STS->Set__DATA(STR__ONLINE);
		diCH__CTRL_STS->Set__DATA(STR__LOCAL);
	}

	if(Is__OFFLINE(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	if(diCH__CTRL_STS->Check__DATA(STR__LOCAL) > 0)
	{
		Fnc__APP_LOG("   Already PUMP [LOCAL] Sts...   \n");
		return OBJ_AVAILABLE;
	}

	timeout=10;
	doCH__CTRL_MODE->Set__DATA(STR__LOCAL);

	// ...
	state = Fnc__CMD_ERR_Check(p_alarm);

		 if(state == OBJ_ABORT)				return OBJ_ABORT;
	else if(state == OBJ_RETRY)				goto CMD_RTY;

	sCH__SEQUENCE_MSG->Set__DATA("Waiting... LOCAL STS");

	state = p_variable->When__VARIABLE_DATA(diCH__CTRL_STS->Get__VARIABLE_NAME(), "LOCAL", timeout);
	if(state < 0) 			// TimeOut
	{
		int alarm_id = ALID__PUMP_LOCAL__TIMEOUT;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);

		return OBJ_ABORT;
	}
	else if( state == 0)    // Abort
	{
		msg.Format(" User Object Aborted...[ret:%d]", state);		
		Fnc__APP_LOG(msg);
		
		return  OBJ_ABORT;
	}

	return OBJ_AVAILABLE;
}

int  CObj__iTIM_TYPE::
Call__REMOTE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__REMOTE(p_variable,p_alarm);
}
int  CObj__iTIM_TYPE::
Fnc__REMOTE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int state;
	int timeout;
	CString msg;

CMD_RTY:

	if(iACTIVE_SIM > 0)
	{
		diCH__COMM_STS->Set__DATA(STR__ONLINE);	
		diCH__CTRL_STS->Set__DATA(STR__REMOTE);
	}

	if(Is__OFFLINE(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	if(diCH__CTRL_STS->Check__DATA(STR__REMOTE) > 0)
	{
		Fnc__APP_LOG("   Already PUMP [REMOTE] Sts...   \n");
		return OBJ_AVAILABLE;
	}

	timeout=10;
	doCH__CTRL_MODE->Set__DATA(STR__REMOTE);

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return OBJ_ABORT;
	}

	// ...
	state = Fnc__CMD_ERR_Check(p_alarm);
	if(state == OBJ_ABORT)
	{
		return OBJ_ABORT;
	}
	else if(state == OBJ_RETRY)
	{
		goto CMD_RTY;
	}

	sCH__SEQUENCE_MSG->Set__DATA("Waiting... REMOTE STS");

	state = p_variable->When__VARIABLE_DATA(diCH__CTRL_STS->Get__VARIABLE_NAME(), "REMOTE", 5.0);
	if(state < 0) 	// TimeOut
	{
		// ...
		{
			int alarm_id = ALID__PUMP_REMOTE__TIMEOUT;
			CString r_act;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
		}
		return OBJ_ABORT;
	}
	else if( state == 0)    // Abort
	{
		msg.Format(" User Object Aborted...[ret:%d]", state);		

		Fnc__APP_LOG(msg);
		return  OBJ_ABORT;
	}

	return OBJ_AVAILABLE;
}

int  CObj__iTIM_TYPE::
Call__PUMP_ON(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__PUMP_ON(p_variable,p_alarm);
}

int  CObj__iTIM_TYPE::
Fnc__PUMP_ON(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int state;
	int timeout;

	CString title;
	CString msg;

CMD_RTY:

	if(iACTIVE_SIM > 0)
	{
		diCH__COMM_STS->Set__DATA(STR__ONLINE);	
		diCH__CTRL_STS->Set__DATA(STR__REMOTE);
	}

	if(diCH__PUMP_STS->Check__DATA("ON") > 0)
	{
		Fnc__APP_LOG("   Already PUMP [ON] Sts...   \n");
		return OBJ_AVAILABLE;
	}

	timeout=10;
	doCH__CTRL_MODE->Set__DATA(STR__REMOTE);

	// ...
	state = Fnc__CMD_ERR_Check(p_alarm);
	if(state == OBJ_ABORT)
	{
		return OBJ_ABORT;
	}
	else if(state == OBJ_RETRY)
	{
		goto CMD_RTY;
	}

	if(Is__REMOTE(p_variable, p_alarm)  < 0)
	{
		return OBJ_ABORT;
	}
	if(Is__OFFLINE(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	// ...
	{
		doCH__RUN_STOP->Set__DATA("ON");

		state = Fnc__CMD_ERR_Check(p_alarm);

		if(state == OBJ_ABORT)
		{
			return OBJ_ABORT;
		}
		else if(state == OBJ_RETRY)
		{
			goto CMD_RTY;
		}
	}

	if(iACTIVE_SIM > 0)
	{
		diCH__PUMP_STS->Set__DATA("ON");
	}

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return OBJ_ABORT;
	}

	sCH__SEQUENCE_MSG->Set__DATA("Waiting... PUMP ON STS");

	// ...
	state = p_variable->When__VARIABLE_DATA(diCH__PUMP_STS->Get__VARIABLE_NAME(), "ON", timeout);
	if(state < 0) 			// TimeOut
	{
		int alarm_id = ALID__PUMP_POWER_ON__TIMEOUT;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);

		return OBJ_ABORT;
	}
	else if( state == 0)    // Abort
	{
		msg.Format(" User Object Aborted...[ret:%d]", state);		

		Fnc__APP_LOG(msg);
		return  OBJ_ABORT;
	}

	return OBJ_AVAILABLE;
}

int  CObj__iTIM_TYPE::
Call__AUTO_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__AUTO_STOP(p_variable,p_alarm);
}

int  CObj__iTIM_TYPE::
Fnc__AUTO_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int state;
	int timeout;

	CString title;
	CString msg;
	CString str_cfg_data;

CMD_RTY:

	if(iACTIVE_SIM > 0)
	{
		diCH__COMM_STS->Set__DATA(STR__ONLINE);	
		diCH__CTRL_STS->Set__DATA(STR__REMOTE);
	}

	timeout=10;
	doCH__CTRL_MODE->Set__DATA(STR__REMOTE);	

	if(Is__REMOTE(p_variable, p_alarm)  < 0)		return OBJ_ABORT;
	if(Is__OFFLINE(p_variable, p_alarm) < 0)		return OBJ_ABORT;

	doCH__RUN_STOP->Set__DATA("AUTO_STOP");

	// ...
	state = Fnc__CMD_ERR_Check(p_alarm);
	
		 if(state == OBJ_ABORT)				return OBJ_ABORT;
	else if(state == OBJ_RETRY)				goto CMD_RTY;

	if(iACTIVE_SIM > 0)
	{
		diCH__PUMP_STS->Set__DATA("OFF");
	}

	if(p_variable->Check__CTRL_ABORT() > 0)			return OBJ_ABORT;

	aCH__CFG_AUTO_STOP_TIMEOUT->Get__DATA(str_cfg_data);
	timeout = atoi(str_cfg_data);

	msg.Format("Waiting... AUTO STOP STS");
	sCH__SEQUENCE_MSG->Set__DATA(msg);
	Fnc__APP_LOG(msg);

	// ...
	state = p_variable->When__VARIABLE_DATA(diCH__PUMP_STS->Get__VARIABLE_NAME(), "OFF", timeout);

	msg.Format("   Call__AUTO_STOP...[ret:%d]", state);
	Fnc__APP_LOG(msg);

	if(state < 0) 			// TimeOut
	{
		int alarm_id = ALID__PUMP_POWER_OFF__TIMEOUT;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);

		return OBJ_ABORT;
	}
	else if( state == 0)    // Abort
	{
		msg.Format(" User Object Aborted...[ret:%d]", state);		
		Fnc__APP_LOG(msg);
		
		return  OBJ_ABORT;
	}

	return OBJ_AVAILABLE;
}

// Fast Stop -----
int  CObj__iTIM_TYPE::
Call__FAST_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__FAST_STOP(p_variable,p_alarm);
}

int  CObj__iTIM_TYPE::
Fnc__FAST_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int state;
	int timeout;

	CString title;
	CString msg;
	CString str_cfg_data;

CMD_RTY:

	if(iACTIVE_SIM > 0)
	{
		diCH__COMM_STS->Set__DATA(STR__ONLINE);	
		diCH__CTRL_STS->Set__DATA(STR__REMOTE);
	}

	timeout=10;
	doCH__CTRL_MODE->Set__DATA(STR__REMOTE);

	if(Is__REMOTE(p_variable, p_alarm)   < 0)		return OBJ_ABORT;
	if(Is__OFFLINE(p_variable, p_alarm)  < 0)		return OBJ_ABORT;

	doCH__RUN_STOP->Set__DATA("FAST_STOP");

	// ...
	state = Fnc__CMD_ERR_Check(p_alarm);

		 if(state == OBJ_ABORT)				return OBJ_ABORT;
	else if(state == OBJ_RETRY)				goto CMD_RTY;

	if(iACTIVE_SIM > 0)
	{
		diCH__PUMP_STS->Set__DATA("OFF");
	}

	if(p_variable->Check__CTRL_ABORT() > 0)			return OBJ_ABORT;

	aCH__CFG_FAST_STOP_TIMEOUT->Get__DATA(str_cfg_data);
	timeout = atoi(str_cfg_data);
	
	sCH__SEQUENCE_MSG->Set__DATA("Waiting... FAST OFF STS");
	
	// ...
	state = p_variable->When__VARIABLE_DATA(diCH__PUMP_STS->Get__VARIABLE_NAME(), "OFF", timeout);
	if(state < 0) 	// TimeOut
	{
		int alarm_id = ALID__PUMP_POWER_OFF__TIMEOUT;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);

		return OBJ_ABORT;
	}
	else if( state == 0)    // Abort
	{
		msg.Format(" User Object Aborted...[ret:%d]", state);		
		Fnc__APP_LOG(msg);

		return  OBJ_ABORT;
	}

	return OBJ_AVAILABLE;
}
