#include "StdAfx.h"
#include "CObj__SHUTTER_IO.h"
#include "CObj__SHUTTER_IO__ALID.h"
#include "CObj__SHUTTER_IO__DEF.h"


// ...
int CObj__SHUTTER_IO
::Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	sCH__OBJ_STATUS->Set__DATA(STR__STANDBY);

	return OBJ_AVAILABLE;
}

int CObj__SHUTTER_IO
::Call__SHUTTER_OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

LOOP_RETRY:

	// Interlock Check ...
	{

	}

	// Open ...
	{
		dEXT_CH__DO_SHUTTER_CLOSE->Set__DATA(STR__OFF);
		dEXT_CH__DO_SHUTTER_OPEN->Set__DATA(STR__ON);
	}

	// Sensor Check ...
	{
		SCX__ASYNC_TIMER_CTRL x_timer_ctrl;

		aCH__CFG_OPEN_TIMEOUT->Get__DATA(ch_data);
		double cfg_sec = atof(ch_data);

		x_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_ACT_TIME_COUNT->Get__CHANNEL_NAME());
		x_timer_ctrl->START__COUNT_DOWN(cfg_sec);

		if(iActive__SIM_MODE > 0)
		{
			Sleep(1000);

			dEXT_CH__DI_SHUTTER_OPEN->Set__DATA(STR__ON);
			dEXT_CH__DI_SHUTTER_CLOSE->Set__DATA(STR__OFF);
		}

		while(1)
		{
			Sleep(100);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return OBJ_ABORT;
			}

			if((dEXT_CH__DI_SHUTTER_OPEN->Check__DATA(STR__ON)   > 0)
				&& (dEXT_CH__DI_SHUTTER_CLOSE->Check__DATA(STR__OFF) > 0))
			{
				break;
			}

			if(x_timer_ctrl->Get__CURRENT_TIME() < 0.1)
			{
				int alm_id = ALID__SHUTTER_OPEN_TIMEOUT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format("Config Open-Timeout <- %.1f sec \n", cfg_sec);

				alm_bff.Format("%s <- %s \n", 
								dEXT_CH__DI_SHUTTER_OPEN->Get__VARIABLE_NAME(),
								dEXT_CH__DI_SHUTTER_OPEN->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format("%s <- %s \n", 
								dEXT_CH__DI_SHUTTER_CLOSE->Get__VARIABLE_NAME(),
								dEXT_CH__DI_SHUTTER_CLOSE->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);

				if(r_act.CompareNoCase(STR__RETRY) == 0)
				{
					goto LOOP_RETRY;
				}

				return OBJ_ABORT;
			}
		}
	}

	return OBJ_AVAILABLE;
}

int CObj__SHUTTER_IO
::Call__SHUTTER_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

LOOP_RETRY:

	// Interlock Check ...
	{

	}

	// Close ...
	{
		dEXT_CH__DO_SHUTTER_CLOSE->Set__DATA(STR__ON);
		dEXT_CH__DO_SHUTTER_OPEN->Set__DATA(STR__OFF);
	}

	// Sensor Check ...
	{
		SCX__ASYNC_TIMER_CTRL x_timer_ctrl;

		aCH__CFG_CLOSE_TIMEOUT->Get__DATA(ch_data);
		double cfg_sec = atof(ch_data);

		x_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_ACT_TIME_COUNT->Get__CHANNEL_NAME());
		x_timer_ctrl->START__COUNT_DOWN(cfg_sec);

		if(iActive__SIM_MODE > 0)
		{
			Sleep(1000);

			dEXT_CH__DI_SHUTTER_OPEN->Set__DATA(STR__OFF);
			dEXT_CH__DI_SHUTTER_CLOSE->Set__DATA(STR__ON);
		}

		while(1)
		{
			Sleep(100);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return OBJ_ABORT;
			}

			if((dEXT_CH__DI_SHUTTER_OPEN->Check__DATA(STR__OFF) > 0)
			&& (dEXT_CH__DI_SHUTTER_CLOSE->Check__DATA(STR__ON) > 0))
			{
				break;
			}

			if(x_timer_ctrl->Get__CURRENT_TIME() < 0.1)
			{
				int alm_id = ALID__SHUTTER_CLOSE_TIMEOUT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format("Config Close-Timeout <- %.1f sec \n", cfg_sec);

				alm_bff.Format("%s <- %s \n", 
					dEXT_CH__DI_SHUTTER_OPEN->Get__VARIABLE_NAME(),
					dEXT_CH__DI_SHUTTER_OPEN->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format("%s <- %s \n", 
					dEXT_CH__DI_SHUTTER_CLOSE->Get__VARIABLE_NAME(),
					dEXT_CH__DI_SHUTTER_CLOSE->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);

				if(r_act.CompareNoCase(STR__RETRY) == 0)
				{
					goto LOOP_RETRY;
				}

				return OBJ_ABORT;
			}
		}
	}

	return OBJ_AVAILABLE;
}
