#include "StdAfx.h"
#include "CObj__PM_SLOT_IO.h"
#include "CObj__PM_SLOT_IO__ALID.h"
#include "CObj__PM_SLOT_IO__DEF.h"


// ...
int CObj__PM_SLOT_IO
::Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int r_flag = Call__DOOR_CLOSE(p_variable, p_alarm);
	if(r_flag < 0)			return r_flag;

	sCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	return 1;
}

int CObj__PM_SLOT_IO
::Call__DOOR_OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

LOOP_RETRY:

	// Interlock Check ...
	{
		// TMC & PMx Pressure
		{
			bool active__press_err = true;

			CString ch__chm_sts = sEXT_CH__CHM_PRESSURE_STATE->Get__STRING();
			CString ch__tmc_sts = dEXT_CH__TMC_PRESSURE_STATE->Get__STRING();
			
			if((ch__chm_sts.CompareNoCase(STR__ATM) == 0)
			&& (ch__tmc_sts.CompareNoCase(STR__ATM) == 0))
			{
				active__press_err = false;
			}
			else if((ch__chm_sts.CompareNoCase(STR__VAC) == 0)
				 && (ch__tmc_sts.CompareNoCase(STR__VAC) == 0))
			{
				active__press_err = false;
			}

			if(active__press_err)
			{
				int alm_id = ALID__SLOT_VALVE_OPEN_INTERLOCK;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format("Interlock condition is as follows; \n");

				alm_bff.Format("  PMC pressure state is \"%s\". \n", ch__chm_sts);
				alm_msg += alm_bff;
				alm_bff.Format("  TMC pressure state is \"%s\". \n", ch__tmc_sts);
				alm_msg += alm_bff;

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);

				if(r_act.CompareNoCase(ACT__RETRY)  == 0)		goto LOOP_RETRY;	
				if(r_act.CompareNoCase(ACT__IGNORE) != 0)		return -101;
			}
		}

		// RF
		for(int i=0; i<iDATA__RF_SIZE; i++)
		{
			if(Check__RF_POWER(p_alarm, i) < 0)
			{
				return -102;
			}
		}
	}

	// Open ...
	{
		dEXT_CH__DO_DOOR_CLOSE->Set__DATA(STR__OFF);
		dEXT_CH__DO_DOOR_OPEN->Set__DATA(STR__ON);
	}

	// Sensor Check ...
	{
		SCX__ASYNC_TIMER_CTRL x_timer_ctrl;

		aCH__CFG_OPEN_TIMEOUT->Get__DATA(ch_data);
		double cfg_sec = atof(ch_data);

		x_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIME_COUNT->Get__CHANNEL_NAME());
		x_timer_ctrl->START__COUNT_DOWN(cfg_sec);

		if(iActive__SIM_MODE > 0)
		{
			Sleep(1000);

			dEXT_CH__DI_DOOR_OPEN->Set__DATA(STR__ON);
			dEXT_CH__DI_DOOR_CLOSE->Set__DATA(STR__OFF);
		}

		while(1)
		{
			Sleep(100);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -11;
			}

			if((dEXT_CH__DI_DOOR_OPEN->Check__DATA(STR__ON)   > 0)
			&& (dEXT_CH__DI_DOOR_CLOSE->Check__DATA(STR__OFF) > 0))
			{
				break;
			}

			if(x_timer_ctrl->Get__CURRENT_TIME() < 0.1)
			{
				int alm_id = ALID__DOOR_OPEN_TIMEOUT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format("Config Open-Timeout <- %.1f sec \n", cfg_sec);

				alm_bff.Format("%s <- %s \n", 
								dEXT_CH__DI_DOOR_OPEN->Get__VARIABLE_NAME(),
								dEXT_CH__DI_DOOR_OPEN->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format("%s <- %s \n", 
								dEXT_CH__DI_DOOR_CLOSE->Get__VARIABLE_NAME(),
								dEXT_CH__DI_DOOR_CLOSE->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);

				if(r_act.CompareNoCase(ACT__RETRY) == 0)
				{
					goto LOOP_RETRY;
				}

				return -21;
			}
		}
	}

	return 1;
}

int CObj__PM_SLOT_IO
::Call__DOOR_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

LOOP_RETRY:

	// Interlock Check ...
	{
		// Robot.Arm State ...
		{
			CString cur__arm_sts = dEXT_CH__TMC_ROBOT_ARM_STATE->Get__STRING();

			if(cur__arm_sts.CompareNoCase(STR__EXEND) == 0)
			{
				int alm_id = ALID__SLOT_VALVE_CLOSE_INTERLOCK;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format("Interlock condition is as follows; \n");

				alm_bff.Format("  Arm-state is \"%s\". \n", cur__arm_sts);
				alm_msg += alm_bff;
				
				alm_bff.Format("  * %s <- %s. \n",
							   dEXT_CH__TMC_ROBOT_ARM_STATE->Get__CHANNEL_NAME(),
							   cur__arm_sts);
				alm_msg += alm_bff;

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);

				if(r_act.CompareNoCase(ACT__RETRY)  == 0)		goto LOOP_RETRY;	
				if(r_act.CompareNoCase(ACT__IGNORE) != 0)		return -101;
			}
		}
	}

	// Close ...
	{
		dEXT_CH__DO_DOOR_CLOSE->Set__DATA(STR__ON);
		dEXT_CH__DO_DOOR_OPEN->Set__DATA(STR__OFF);
	}

	// Sensor Check ...
	{
		SCX__ASYNC_TIMER_CTRL x_timer_ctrl;

		aCH__CFG_CLOSE_TIMEOUT->Get__DATA(ch_data);
		double cfg_sec = atof(ch_data);

		x_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIME_COUNT->Get__CHANNEL_NAME());
		x_timer_ctrl->START__COUNT_DOWN(cfg_sec);

		if(iActive__SIM_MODE > 0)
		{
			Sleep(1000);

			dEXT_CH__DI_DOOR_OPEN->Set__DATA(STR__OFF);
			dEXT_CH__DI_DOOR_CLOSE->Set__DATA(STR__ON);
		}

		while(1)
		{
			Sleep(100);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -11;
			}

			if((dEXT_CH__DI_DOOR_OPEN->Check__DATA(STR__OFF) > 0)
				&& (dEXT_CH__DI_DOOR_CLOSE->Check__DATA(STR__ON) > 0))
			{
				break;
			}

			if(x_timer_ctrl->Get__CURRENT_TIME() < 0.1)
			{
				int alm_id = ALID__DOOR_CLOSE_TIMEOUT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format("Config Close-Timeout <- %.1f sec \n", cfg_sec);

				alm_bff.Format("%s <- %s \n", 
								dEXT_CH__DI_DOOR_OPEN->Get__VARIABLE_NAME(),
								dEXT_CH__DI_DOOR_OPEN->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format("%s <- %s \n", 
								dEXT_CH__DI_DOOR_CLOSE->Get__VARIABLE_NAME(),
								dEXT_CH__DI_DOOR_CLOSE->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);

				if(r_act.CompareNoCase(ACT__RETRY) == 0)
				{
					goto LOOP_RETRY;
				}

				return -21;
			}
		}
	}

	return 1;
}

int CObj__PM_SLOT_IO
::Check__RF_POWER(CII_OBJECT__ALARM *p_alarm, int rf_index)
{
	while(1)
	{
		if(dEXT_CH__RFx_ON_STS[rf_index]->Check__DATA(STR__OFF) < 0)
		{
			int alarm_id = ALID__RF_POWER_STS;

			CString alm_msg;
			CString r_act;

			CString rf_name = sList__RFx_NAME[rf_index];

			alm_msg.Format("Please, Check RF %s - Power On Status.", rf_name);	

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, alm_msg, r_act);

			if(r_act.CompareNoCase(ACT__RETRY) != 0)
			{
				CString log_msg;
				CString log_bff;

				log_msg.Format("RF(%s) Power Status Error ... \n", rf_name);

				log_bff.Format(" * %s <- %s \n",
								dEXT_CH__RFx_ON_STS[rf_index]->Get__CHANNEL_NAME(),
								dEXT_CH__RFx_ON_STS[rf_index]->Get__STRING());
				log_msg += log_bff;

				xI_LOG_CTRL->WRITE__LOG(log_msg);
				return -1;
			}	
		}
		else
		{
			return 1;
		}

		Sleep(500);
	}

	return -1;
}
