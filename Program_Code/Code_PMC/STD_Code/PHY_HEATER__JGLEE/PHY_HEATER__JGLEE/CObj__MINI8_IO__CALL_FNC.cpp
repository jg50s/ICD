#include "StdAfx.h"
#include "CObj__MINI8_IO.h"
#include "CObj__MINI8_IO__ALID.h"

#include "CCommon_Utility.h"


// ...
#define HTR_TYPE__INIT				1
#define HTR_TYPE__IDLE				2
#define HTR_TYPE__PROC				3


// ...
int CObj__MINI8_IO
::Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	sCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);

	if(dCH__CFG_INITIAL_MODE->Check__DATA(STR__HEATING) > 0)
	{
		// H/W Alarm Check ...
		while(sCH__MON_IO_GET_ALARM_STATUS_ACTIVE->Check__DATA(STR__ON) > 0)
		{
			CString msg_title;
			CString msg_str;
			CStringArray l_act;
			CString r_act;

			msg_title = "Heater H/W Alarm이 발생된 상태입니다.";
			msg_str = "Alarm Reset 할까요?";

			l_act.RemoveAll();
			l_act.Add(STR__YES);
			l_act.Add(STR__NO);

			p_alarm->Popup__MESSAGE_BOX(msg_title,msg_str,l_act,r_act);

			if(r_act.CompareNoCase(STR__YES) == 0)
			{
				Fnc__ALARM_RESET(p_variable,p_alarm);
				continue;
			}
			return -1;
		}

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1;
		}

		if(Fnc__HEATING(p_variable,p_alarm, HTR_TYPE__INIT) < 0)
		{
			return -1;
		}
	}

	sCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	return 1;
}

int CObj__MINI8_IO
::Call__ALARM_RESET(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__ALARM_RESET(p_variable,p_alarm);
}
int CObj__MINI8_IO
::Fnc__ALARM_RESET(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(!bActive__SO_ALARM_RESET_HEXA)
	{
		return -1;
	}

	sEXT_CH__SO_ALARM_RESET_HEXA->Set__DATA("01 00");

	// ...
	{
		SCX__TIMER_CTRL x_timer_ctrl;
		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH__OBJ_TIMER->Get__CHANNEL_NAME());

		double cfg_sec = aCH__CFG_ALARM_RESET_ON_TIME->Get__VALUE();
		if(x_timer_ctrl->WAIT(cfg_sec) < 0)
		{
			sEXT_CH__SO_ALARM_RESET_HEXA->Set__DATA("00 00");
			return -1;
		}
	}

	sEXT_CH__SO_ALARM_RESET_HEXA->Set__DATA("00 00");
	return 1;
}

int CObj__MINI8_IO
::Call__HEATING_IDLE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(Fnc__HEATING(p_variable,p_alarm, HTR_TYPE__IDLE) < 0)
	{
		return -1;
	}
	return 1;
}
int CObj__MINI8_IO
::Call__HEATING_PROC(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(Fnc__HEATING(p_variable,p_alarm, HTR_TYPE__PROC) < 0)
	{
		return -1;
	}
	return 1;
}

int CObj__MINI8_IO
::Fnc__HEATING(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const int htr_type)
{
	sCH__MON_HEATING_ACTIVE->Set__DATA(STR__ON);

	int r_flag = _Fnc__HEATING(p_variable,p_alarm, htr_type);

	sCH__MON_HEATING_ACTIVE->Set__DATA(STR__OFF);
	return r_flag;
}
int CObj__MINI8_IO
::_Fnc__HEATING(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const int htr_type)
{
	double trg_sp[CFG__LOOP_SIZE];
	double start_pv[CFG__LOOP_SIZE];

	CString ch_data;
	int i;

	// CFG : SET ...
	{
		for(i=0; i<iLOOP_SIZE; i++)
		{
				 if(htr_type == HTR_TYPE__INIT)			trg_sp[i] = aCH__CFG_INITIAL_TARTGET_TEMP__LOOP_X[i]->Get__VALUE();
			else if(htr_type == HTR_TYPE__IDLE)			trg_sp[i] = aCH__CFG_TARGET_SP__LOOP_X[i]->Get__VALUE();
			else if(htr_type == HTR_TYPE__PROC)			trg_sp[i] = aCH__PARA_TARGET_SP__LOOP_X[i]->Get__VALUE();
			else										return -11;

			ch_data = sCH__MON_IO_GET_PV__LOOP_X[i]->Get__STRING();
			start_pv[i] = atof(ch_data);
		}
	}

	// ...
	double ramping_range = aCH__CFG_RAMPING_RANGE->Get__VALUE();
	double ramping_rate  = aCH__CFG_RAMPING_RATE->Get__VALUE();

	int stable_check_count = ramping_range / ramping_rate;
	int loop_count = 0;

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "\n";
		log_msg += "Ramping Info ... \n";

		log_bff.Format("ramping_range : %.3f \n", ramping_range);
		log_msg += log_bff;

		log_bff.Format("ramping_rate  : %.3f \n", ramping_rate);
		log_msg += log_bff;

		log_bff.Format("stable_check_count : %1d \n", stable_check_count);
		log_msg += log_bff;

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		aCH__CFG_RAMPING_RATE->Get__DATA(ch_data);
		sCH__CUR_RAMPING_RATE->Set__DATA(ch_data);
		
		aCH__CFG_RAMPING_RANGE->Get__DATA(ch_data);
		sCH__CUR_RAMPING_RANGE->Set__DATA(ch_data);
	}

	// ...
	SCX__TIMER_CTRL x_timer_ctrl;
	x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);

	// ...
	SCX__ASYNC_TIMER_CTRL x_elapse_timer;
	x_elapse_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__CUR_HEATING_TIMEOUT->Get__CHANNEL_NAME());
	x_elapse_timer->STOP_ZERO();
	x_elapse_timer->START__COUNT_UP(99999);

	int active_err__deviation = 0;

	while(1)
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1;
		}

		// MON.EOOR_ACTIVE ...
		{
			if(sCH__MON_IO_GET_ALARM_STATUS_ACTIVE->Check__DATA(STR__ON) > 0)				return -10001;

			if(sCH__MON_TEMP_HIGH_LIMIT_ACTIVE__LOOP_ALL->Check__DATA(STR__ON) > 0)			return -10011;
			if(sCH__MON_OP_HIGH_LIMIT_ACTIVE__LOOP_ALL->Check__DATA(STR__ON) > 0)			return -10012;
			if(sCH__MON_MAX_DEVIATION_ACTIVE__LOOP_ALL->Check__DATA(STR__ON) > 0)			return -10013;
			if(sCH__MON_DI_OVER_TEMP_STATE_LOOP_ALL->Check__DATA(STR__ON) > 0)				return -10014;
			if(sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_ALL->Check__DATA(STR__ON) > 0)				return -10015;
		}
		
		if(htr_type == HTR_TYPE__INIT)
		{
			double cfg_timeout = aCH__CFG_INITIAL_HEATING_TIMEOUT->Get__VALUE();

			if(cfg_timeout > 0)
			{
				if(x_elapse_timer->Get__CURRENT_TIME() > cfg_timeout)
				{
					// Alarm : Heating Timeout ...
					{
						int alm_id = ALID__INITIAL_HEATING_TIMEOUT;
						CString alm_msg;
						CString alm_bff;
						CString r_act;

						alm_bff.Format("Config에 설정된 heating timeout은 %.0f sec 입니다. \n", cfg_timeout);
						alm_msg += alm_bff;

						p_alarm->Check__ALARM(alm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
					}
					return -11;
				}
			}
		}
		else
		{
			double cfg_timeout = aCH__CFG_HEATING_TIMEOUT->Get__VALUE();

			if(cfg_timeout > 0)
			{
				if(x_elapse_timer->Get__CURRENT_TIME() > cfg_timeout)
				{
					// Alarm : Heating Timeout ...
					{
						int alm_id = ALID__HEATING_TIMEOUT;
						CString alm_msg;
						CString alm_bff;
						CString r_act;

						alm_bff.Format("Config에 설정된 heating timeout은 %.0f sec 입니다. \n", cfg_timeout);
						alm_msg += alm_bff;

						p_alarm->Check__ALARM(alm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
					}
					return -12;
				}
			}
		}

		// ...
		int comp_check = 1;
		loop_count++;

		// Temperature.Set ...
		{
			for(i=0; i<iLOOP_SIZE; i++)
			{
				double set_sp = start_pv[i] + (ramping_rate * loop_count);

				if(set_sp > trg_sp[i])		set_sp = trg_sp[i];
				else						comp_check = -1;

				if(bActive__CTRL_ACTIVE__LOOP_X[i])
					aEXT_CH__AO_TEMPERATURE_SET__LOOP_X[i]->Set__VALUE(set_sp);

				if(bActive__DO_HEATER_POWER__LOOP_X[i])
					dEXT_CH__DO_HEATER_POWER__LOOP_X[i]->Set__DATA(STR__ON);
			}
		}

		if(comp_check > 0)
		{
			break;
		}

		x_timer_ctrl->POLL(1.0);

		// Stable Check ...
		if(loop_count == stable_check_count)
		{
			int i_limit = iLOOP_SIZE;

			for(i=0; i<i_limit; i++)
			{
				start_pv[i] += (ramping_rate * loop_count);
			}
			loop_count = 0;

			// ...
			{
				SCX__TIMER_CTRL x_stable_timer;
				x_stable_timer->REGISTER__ABORT_OBJECT(sObject_Name);
				x_stable_timer->REGISTER__COUNT_CHANNEL(sCH__CUR_RAMPING_STABLE_TIME_COUNT->Get__CHANNEL_NAME());

				double cfg_stable = aCH__CFG_RAMPING_STABLE_TIME->Get__VALUE();

				if(x_stable_timer->WAIT(cfg_stable) < 0)
				{
					return -1;
				}
			}

			x_timer_ctrl->INIT__COUNT_UP();
		}
	}

	return 1;
}

int CObj__MINI8_IO
::Call__POWER_OFF(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	for(int i=0; i<iLOOP_SIZE; i++)
	{
		if(bActive__DO_HEATER_POWER__LOOP_X[i])
			dEXT_CH__DO_HEATER_POWER__LOOP_X[i]->Set__DATA(STR__OFF);
	}

	return 1;
}

int CObj__MINI8_IO
::Call__STABLE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	for(int i=0; i<iLOOP_SIZE; i++)
	{
		if(dCH__MON_IDLE_ERROR_CHECK_ACTIVE__LOOP_X[i]->Check__DATA(STR__ON) < 0)
			dCH__MON_IDLE_ERROR_CHECK_ACTIVE__LOOP_X[i]->Set__DATA(STR__READY);

		if(dCH__MON_PROC_ERROR_CHECK_ACTIVE__LOOP_X[i]->Check__DATA(STR__ON) < 0)
			dCH__MON_PROC_ERROR_CHECK_ACTIVE__LOOP_X[i]->Set__DATA(STR__READY);
	}

	return 1;
}
