#include "StdAfx.h"
#include "CObj__TRANSFER_FNC.h"


// ...
int CObj__TRANSFER_FNC
::Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{

	return 1;
}

int CObj__TRANSFER_FNC
::Call__PICK_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(Fnc__INTERLOCK_CHECK(p_variable, p_alarm) < 0)
	{
		return -1;
	}

	return 1;
}
int CObj__TRANSFER_FNC
::Call__PICK_X_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(Fnc__INTERLOCK_CHECK(p_variable, p_alarm) < 0)
	{
		return -1;
	}

	return 1;
}

int CObj__TRANSFER_FNC
::Call__PICK_COMPLETE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{

	return 1;
}
int CObj__TRANSFER_FNC
::Call__PICK_X_COMPLETE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{

	return 1;
}

int CObj__TRANSFER_FNC
::Call__PLACE_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(Fnc__INTERLOCK_CHECK(p_variable, p_alarm) < 0)
	{
		return -1;
	}

	return 1;
}
int CObj__TRANSFER_FNC
::Call__PLACE_X_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(Fnc__INTERLOCK_CHECK(p_variable, p_alarm) < 0)
	{
		return -1;
	}

	return 1;
}

int CObj__TRANSFER_FNC
::Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{

	return 1;
}
int CObj__TRANSFER_FNC
::Call__PLACE_X_COMPLETE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{

	return 1;
}

int CObj__TRANSFER_FNC
::Fnc__INTERLOCK_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	for(int i=0; i<iDATA__RF_SIZE; i++)
	{
		if(Check__RF_POWER(p_alarm, i) < 0)
		{
			return -1;
		}
	}

	if(Check__ESC_POWER(p_alarm) < 0)
	{
		return -1;
	}

	return 1;
}

int CObj__TRANSFER_FNC
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

int CObj__TRANSFER_FNC
::Check__ESC_POWER(CII_OBJECT__ALARM *p_alarm)
{
	while (1)
	{
		if(bActive__ESC_ON_STS)
		{
			if(dEXT_CH__ESC_ON_STS->Check__DATA(STR__OFF) < 0)
			{
				int alarm_id = ALID__ESC_POWER_STS;

				CString r_act;
	
				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, "", r_act);

				if(r_act.CompareNoCase(ACT__RETRY) != 0)
				{
					CString log_msg;
					CString log_bff;

					log_msg = "ESC Power Status Error !";

					log_bff.Format(" * %s <- %s \n",
									dEXT_CH__ESC_ON_STS->Get__CHANNEL_NAME(),
									dEXT_CH__ESC_ON_STS->Get__STRING());
					log_msg += log_bff;
	
					xI_LOG_CTRL->WRITE__LOG(log_msg);
					return -1;
				}	
			}
			else
			{
				return 1;
			}
		}
		else
		{
			return 11;
		}

		Sleep(500);
	}

	return -1;
}
