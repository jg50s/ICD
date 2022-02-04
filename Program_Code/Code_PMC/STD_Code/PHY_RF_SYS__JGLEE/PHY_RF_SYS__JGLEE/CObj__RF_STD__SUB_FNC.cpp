#include "StdAfx.h"
#include "CObj__RF_STD.h"



//-------------------------------------------------------------------------
int  CObj__RF_STD
::Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm,CString msg, const int alarm_id)
{
	CString r_act;

	p_alarm->Check__ALARM(alarm_id,r_act);
	p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, msg, r_act);

	if(r_act.CompareNoCase("RETRY") == 0)
	{
		return 1;
	}
	return -1;
}

void CObj__RF_STD
::Alarm__POST_CHECK(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id)
{
	CString r_act;

	p_alarm->Check__ALARM(alarm_id, r_act);
	p_alarm->Post__ALARM_With_MESSAGE(alarm_id, msg);
}

int CObj__RF_STD
::Fnc__INTLK_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString str_data;
	CString log_msg;

	if(dEXT_CH__DI_VAC_SNS->Check__DATA(STR__ON) < 0)
	{
		// ...
		{
			int alarm_id = ALID__VACUUM_SWITCH_ALARM;
			CString r_act;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
		}
		return OBJ_ABORT;
	}
	if(dEXT_CH__DI_ATM_SNS->Check__DATA(STR__OFF) < 0)
	{
		// ...
		{
			int alarm_id = ALID__ATM_SWITCH_ALARM;
			CString r_act;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
		}
		return OBJ_ABORT;
	}

	if(dEXT_CH__CHM_SHUTTER_STATE->Check__DATA(STR__CLOSE) < 0)
	{
		// ...
		{
			int alarm_id = ALID__CHAMBER_SHUTTER_NOT_CLOSE;
			CString r_act;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
		}
		return OBJ_ABORT;
	}
	if(dEXT_CH__DI_CHM_LID_CLOSE_SNS->Check__DATA(STR__ON) < 0)
	{
		// ...
		{
			int alarm_id = ALID__CHAMBER_LID_INTLK_ALARM;
			CString r_act;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
		}
		return OBJ_ABORT;
	}	

	if(dEXT_CH__INTERLOCK_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		// ...
		{
			int alarm_id = ALID__INTERLOCK_SENSOR_ALARM;
			CString alm_msg;
			CString r_act;

			alm_msg = sEXT_CH__INTERLOCK_MSG->Get__STRING();

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
		}
		return OBJ_ABORT;
	}

	// User Config Interlock (Max RF Power without Wafer) ...
	if(dEXT_CH__SLOT01_STATUS->Check__DATA("NONE") > 0)
	{
		if(dCH__CFG_POWER_INTERLOCK_WITHOUT_WAFER->Check__DATA(STR__YES) > 0)
		{
			aCH__CFG_MAX_POWER_WITHOUT_WAFER->Get__DATA(str_data);
			double dbCfg_Max_Power_Without_Wafer = atof(str_data);

			aCH__PARA_SET_POWER->Get__DATA(str_data);
			double dbRf_Set_Power = atof(str_data);

			if(dbRf_Set_Power > dbCfg_Max_Power_Without_Wafer)
			{
				CString str_msg;

				// ...
				{
					dEXT_CH__SLOT01_STATUS->Get__DATA(str_data);
					str_msg.Format("Set Power: %.2f, Wafer Status: %s, Power Limit: %.2f", 
									dbRf_Set_Power, 
									str_data, 
									dbCfg_Max_Power_Without_Wafer);

					int alarm_id = ALID__RF_MAX_POWER_OVER_WHITOUT_WAFER;
					Alarm__POST_CHECK(p_alarm, str_msg, alarm_id);
				}

				xLOG_CTRL->WRITE__LOG(str_msg);
				return OBJ_ABORT;
			}
		}
	}

	// User Config Interlock (RF Allowed SET Power) ...
	{
		aCH__CFG_MAX_ALLOWED_POWER->Get__DATA(str_data);
		double dbCfg_Max_Allowed_Power = atof(str_data);

		aCH__PARA_SET_POWER->Get__DATA(str_data);
		double dbRf_Set_Power = atof(str_data);

		if(dbRf_Set_Power > dbCfg_Max_Allowed_Power)
		{
			CString str_msg;

			// ...
			{
				str_msg.Format("Set Power: %.2f, Allowed Power Limit: %.2f", 
							   dbRf_Set_Power, dbCfg_Max_Allowed_Power);

				int alarm_id = ALID__RF_MAX_ALLOWED_POWER_OVER;
				Alarm__POST_CHECK(p_alarm, str_msg, alarm_id);
			}

			xLOG_CTRL->WRITE__LOG(str_msg);
			return OBJ_ABORT;
		}
	}

	return OBJ_AVAILABLE;
}

int CObj__RF_STD
::Fnc__DEFAULT_CONFIG_SET(CII_OBJECT__VARIABLE *p_variable, 
						  CII_OBJECT__ALARM *p_alarm)
{
	CString str_data;

	if(bActive__RF_FREQ_MODE)
	{
		// 1. RF Ramp SET (msec)
		{
			aCH__CFG_DEFAULT_RAMP_TIME->Get__DATA(str_data);				

			aCH__PARA_RAMP_UP_TIME->Set__DATA(str_data);					
			aEXT_CH__RF_PARA_RAMP_UP_TIME->Set__DATA(str_data);				

			aCH__PARA_RAMP_DOWN_TIME->Set__DATA(str_data);					
			aEXT_CH__RF_PARA_RAMP_DOWN_TIME->Set__DATA(str_data);			
		}

		// 2. RF Frequency SET (kHz)
		{
			aCH__CFG_DEFAULT_FREQUENCY->Get__DATA(str_data);	

			aCH__PARA_FREQ_PRESET->Set__DATA(str_data);				
			aEXT_CH__RF_PARA_START_FREQUENCY->Set__DATA(str_data);
		}

		// 3. RF Tune Delay Time SET (msec)
		{
			aCH__CFG_DEFAULT_TUNE_DELAY->Get__DATA(str_data);	

			aCH__PARA_FREQ_TUNE_DELAY->Set__DATA(str_data);			
			aEXT_CH__RF_PARA_TUNE_DELAY->Set__DATA(str_data);	
		}
	}

	return 1;
}
int CObj__RF_STD
::Fnc__RECIPE_CONTROL_SET(CII_OBJECT__VARIABLE *p_variable, 
						  CII_OBJECT__ALARM *p_alarm)
{
	CString str_data;

	if(bActive__RF_FREQ_MODE)
	{
		// 1. RF Ramp SET (msec)
		{
			aCH__PARA_RAMP_UP_TIME->Get__DATA(str_data);		
			aEXT_CH__RF_PARA_RAMP_UP_TIME->Set__DATA(str_data);	

			aCH__PARA_RAMP_DOWN_TIME->Get__DATA(str_data);			
			aEXT_CH__RF_PARA_RAMP_DOWN_TIME->Set__DATA(str_data);	
		}

		// 2. RF Frequency SET (kHz)
		{
			aCH__PARA_FREQ_PRESET->Get__DATA(str_data);					
			aEXT_CH__RF_PARA_START_FREQUENCY->Set__DATA(str_data);	
		}

		// 3. RF Frequency Output Power SET (kHz)
		{
			aCH__PARA_FREQ_OUTPUT->Get__DATA(str_data);			
			aEXT_CH__RF_PARA_OUTPUT_FREQUENCY->Set__DATA(str_data);	
		}

		// 4. RF Tune Delay Time SET (msec)
		{
			aCH__PARA_FREQ_TUNE_DELAY->Get__DATA(str_data);	
			aEXT_CH__RF_PARA_TUNE_DELAY->Set__DATA(str_data);
		}
	}

	return 1;
}
