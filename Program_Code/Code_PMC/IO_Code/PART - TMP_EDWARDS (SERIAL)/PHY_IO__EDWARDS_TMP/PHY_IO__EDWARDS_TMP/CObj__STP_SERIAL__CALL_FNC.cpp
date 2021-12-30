#include "StdAfx.h"
#include "CObj__STP_SERIAL.h"

#include "Macro_Function.h"


//-------------------------------------------------------------------------	
int  CObj__STP_SERIAL::
Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(iACTIVE_SIM > 0)
	{
		diCH__COMM_STS->Set__DATA(STR__ONLINE);

		dCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	}

	return Fnc__INIT(p_variable,p_alarm);
}
int  CObj__STP_SERIAL::
Fnc__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(Is__OFFLINE(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	dCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	return OBJ_AVAILABLE;
}

int  CObj__STP_SERIAL::
Call__PUMP_ON(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;

ACT_RETRY:

	// Online Check ...
	if(Is__OFFLINE(p_variable, p_alarm)  < 0)
	{
		return OBJ_ABORT;
	}

	// TMP Start ...
	{
		double trg_rpm = aCH__CFG_TARGET_SPEED_RPM->Get__VALUE();
		double trg_hz = trg_rpm / 60.0;
		aoCH__SET_SPEED_HZ->Set__VALUE(trg_hz);

		doCH__OP_CMMD->Set__DATA(CMMD__START);

		if(p_variable->Check__CTRL_ABORT() > 0)			return OBJ_ABORT;
	}

	// Acceleration Check ...
	{
		double cfg_sec = aCH__CFG_ACCEL_TIMEOUT->Get__VALUE();

		log_msg.Format("Waiting TMP(Acceleration), config timeout.(%.1f) sec.", cfg_sec);			
		Fnc__APP_LOG(log_msg);

		if(iACTIVE_SIM > 0)
		{
			sCH__INFO_PUMP_OP_MODE->Set__DATA(STR__Acceleration);
		}

		sCH__INFO_PUMP_OP_MODE->Link__UPPER_OBJECT_ABORT(sObject_Name);
		sCH__INFO_PUMP_OP_MODE->Enable__UPPER_OBJECT_ABORT_CHECK();

		int state = sCH__INFO_PUMP_OP_MODE->When__DATA(STR__Acceleration, STR__Normal, cfg_sec);		
		if(state < 0) 
		{
			Fnc__APP_LOG("Acceleration Timeout !");

			//
			int alarm_id = ALID__PUMP_ACCELERATION__TIMEOUT;
			CString r_act;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);

			if(r_act.CompareNoCase("RETRY") == 0)
			{
				goto ACT_RETRY;
			}
			return OBJ_ABORT;
		}
		else if(state == 0)    // Abort
		{
			log_msg.Format("Aborted by user. (ret : %d)", state);			
			Fnc__APP_LOG(log_msg);

			return  OBJ_ABORT;
		}
	}

	// Normal Check ...
	{
		double cfg_sec = aCH__CFG_TARGET_SPEED_TIMEOUT->Get__VALUE();

		log_msg.Format("Waiting TMP(Normal), config timeout.(%.1f) sec.", cfg_sec);			
		Fnc__APP_LOG(log_msg);

		if(iACTIVE_SIM > 0)
		{
			sCH__INFO_PUMP_OP_MODE->Set__DATA(STR__Normal);
		}

		sCH__INFO_PUMP_OP_MODE->Link__UPPER_OBJECT_ABORT(sObject_Name);
		sCH__INFO_PUMP_OP_MODE->Enable__UPPER_OBJECT_ABORT_CHECK();

		int state = sCH__INFO_PUMP_OP_MODE->When__DATA(STR__Normal, cfg_sec);		
		if(state < 0) 			// Timeout 
		{
			Fnc__APP_LOG("Normal Timeout !");

			//
			int alarm_id = ALID__PUMP_POWER_ON__TIMEOUT;
			CString r_act;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);

			return OBJ_ABORT;
		}
		else if(state == 0)    // Abort
		{
			log_msg.Format("Aborted by user. (ret : %d)", state);			
			Fnc__APP_LOG(log_msg);

			return  OBJ_ABORT;
		}
	}

	return OBJ_AVAILABLE;
}

int  CObj__STP_SERIAL::
Call__AUTO_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;

	// TMP STOP Check ...
	{
		aoCH__SET_SPEED_HZ->Set__DATA("0");
		doCH__OP_CMMD->Set__DATA(CMMD__STOP);

		//
		int state = sCH__MON_PUMP_STS->When__DATA(STR__OFF, 2.0);
		if(state > 0)
		{
			Fnc__APP_LOG("Already, PUMP [OFF] Status ... \n");
			return OBJ_AVAILABLE;
		}
	}

	// Online Check ...
	if(Is__OFFLINE(p_variable, p_alarm)  < 0)
	{
		return OBJ_ABORT;
	}

	// TMP Start ...
	{
		doCH__OP_CMMD->Set__DATA(CMMD__STOP);

		if(p_variable->Check__CTRL_ABORT() > 0)			return OBJ_ABORT;
	}

	// STOP Check ...
	{
		double cfg_sec = aCH__CFG_STOP_TIMEOUT->Get__VALUE();

		log_msg.Format("Waiting TMP(STOP), config timeout.(%.1f) sec.", cfg_sec);			
		Fnc__APP_LOG(log_msg);

		sCH__MON_PUMP_STS->Link__UPPER_OBJECT_ABORT(sObject_Name);
		sCH__MON_PUMP_STS->Enable__UPPER_OBJECT_ABORT_CHECK();

		int state = sCH__MON_PUMP_STS->When__DATA(STR__OFF, cfg_sec);
		if(state < 0) 
		{
			Fnc__APP_LOG("STOP Timeout !");

			//
			int alarm_id = ALID__PUMP_POWER_OFF__TIMEOUT;
			CString r_act;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);

			return OBJ_ABORT;
		}
		else if( state == 0)    // Abort
		{
			log_msg.Format("Aborted by user. (ret : %d)", state);			
			Fnc__APP_LOG(log_msg);

			return  OBJ_ABORT;
		}
	}

	return OBJ_AVAILABLE;
}

int  CObj__STP_SERIAL::
Call__AUTO_STOP_NO_WAIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;

	// TMP STOP Check ...
	{
		aoCH__SET_SPEED_HZ->Set__DATA("0");
		doCH__OP_CMMD->Set__DATA(CMMD__STOP);

		//
		int state = sCH__MON_PUMP_STS->When__DATA(STR__OFF, 2.0);
		if(state > 0)
		{
			Fnc__APP_LOG("Already, PUMP [OFF] Status ... \n");
			return OBJ_AVAILABLE;
		}
	}

	// Online Check ...
	if(Is__OFFLINE(p_variable, p_alarm)  < 0)
	{
		return OBJ_ABORT;
	}

	// TMP Start ...
	{
		doCH__OP_CMMD->Set__DATA(CMMD__STOP);

		if(p_variable->Check__CTRL_ABORT() > 0)			return OBJ_ABORT;
	}

	return OBJ_AVAILABLE;
}

int  CObj__STP_SERIAL::
Call__CHECK_SUM(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	unsigned char s_cmmd[256];
	int s_len;

	memset(s_cmmd, 0, 256);

	s_len = 0;
	s_cmmd[s_len++]  = _STX;
	s_cmmd[s_len++] += '0';
	s_cmmd[s_len++] += '0';
	s_cmmd[s_len++] += '1';
	s_cmmd[s_len++] += '#';
	s_cmmd[s_len++] += _ETX;

	byte LRC = _Get__CheckSum(s_cmmd, s_len);
	
	printf(" * CMMD <- [%s] \n",   s_cmmd);
	printf(" * LRC  <- [%02X] \n", LRC);
	return 1;
}   