#include "StdAfx.h"
#include "CObj__RF_STD.h"

#include <math.h>


// ...
int CObj__RF_STD::
Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int loop_count = 0;
	CString ch_data;

	if(sCH__MON_RF_ON_TIME_START_DATE->Check__DATA("") > 0)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		ch_data.Format("%00004d.%002d.%002d", st.wYear,st.wMonth,st.wDay);
		sCH__MON_RF_ON_TIME_START_DATE->Set__DATA(ch_data);
	}

	
	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		loop_count++;
		if(loop_count > 10)			loop_count = 1;

		//
		if(loop_count == 1)
		{
			bool active__idle_check = false;
			bool active__proc_check = false;

			if(dCH__MON_IDLE_POWER_CHECK_ACTIVE->Check__DATA(STR__ON) > 0)			active__idle_check = true;
			if(dCH__MON_PROC_POWER_CHECK_ACTIVE->Check__DATA(STR__ON) > 0)			active__proc_check = true;

			if((active__idle_check)
			|| (active__proc_check))
			{
				bool active__idle_error = false;
				bool active__proc_error = false;

				if(active__idle_check)
				{
					if(dCH__MON_IDLE_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)			active__idle_error = true;
				}
				if(active__proc_check)
				{
					if(dCH__MON_PROC_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)			active__proc_error = true;
				}

				if((active__idle_error)
				|| (active__proc_error))
				{
					dCH__MON_RF_POWER_ABORT_ACTIVE->Set__DATA(STR__ON);
					dCH__MON_RF_POWER_STABLE_ACTIVE->Set__DATA(STR__OFF);
				}
				else
				{
					dCH__MON_RF_POWER_ABORT_ACTIVE->Set__DATA(STR__OFF);

					if(active__proc_check)
					{
						if(dCH__MON_PROC_POWER_STABLE_ACTIVE->Check__DATA(STR__ON) > 0)		
							dCH__MON_RF_POWER_STABLE_ACTIVE->Set__DATA(STR__ON);
						else
							dCH__MON_RF_POWER_STABLE_ACTIVE->Set__DATA(STR__OFF);
					}
					else if(active__idle_check)
					{
						if(dCH__MON_IDLE_POWER_STABLE_ACTIVE->Check__DATA(STR__ON) > 0)
							dCH__MON_RF_POWER_STABLE_ACTIVE->Set__DATA(STR__ON);
						else
							dCH__MON_RF_POWER_STABLE_ACTIVE->Set__DATA(STR__OFF);
					}
				}

				dCH__MON_RF_CTRL_ACTIVE->Set__DATA(STR__ON);
			}
			else
			{
				dCH__MON_RF_CTRL_ACTIVE->Set__DATA(STR__OFF);
				dCH__MON_RF_POWER_ABORT_ACTIVE->Set__DATA(STR__OFF);
				dCH__MON_RF_POWER_STABLE_ACTIVE->Set__DATA(STR__OFF);
			}

			//
			int active__err_check = p_alarm->Check__Posted_Internal_Alarm(iLIST_ALID__RF);

			if(active__err_check > 0)		dCH__MON_RF_ERROR_ACTIVE->Set__DATA(STR__ON);
			else							dCH__MON_RF_ERROR_ACTIVE->Set__DATA(STR__OFF);
		}

		// Range : Power ...
		{			
			double min_value = aCH__CFG_POWER_MIN_VALUE->Get__VALUE();
			double max_value = aCH__CFG_POWER_MAX_VALUE->Get__VALUE();
			int i_dec = (int) aCH__CFG_POWER_DEC_VALUE->Get__VALUE();

			aCH__PARA_SET_POWER->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
			aCH__CFG_MAX_ALLOWED_POWER->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
			aCH__CFG_MAX_POWER_WITHOUT_WAFER->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
		}

		// Range : Frequency ...
		{
			double min_value = aCH__CFG_MIN_FREQUENCY->Get__VALUE();
			double max_value = aCH__CFG_MAX_FREQUENCY->Get__VALUE();
			int i_dec = 0;

			aCH__CFG_DEFAULT_FREQUENCY->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
			aCH__CFG_REFLECT_HIGH_LIMIT->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
		}

		// MON.IO ...
		{
			if(iActive__SIM_MODE > 0)
			{
				ch_data = sEXT_CH__RF_AO_SET_POWER->Get__STRING();
				
				sEXT_CH__RF_AI_FORWARD_POWER->Set__DATA(ch_data);
				sEXT_CH__RF_AI_REFLECT_POWER->Set__DATA("0.0");
			}

			// ...
			ch_data = sCH__PARA_RF_OFFSET_POWER->Get__STRING();
			double set_offset = atof(ch_data);

			// SET.POWER ...
			{
				ch_data = sEXT_CH__RF_AO_SET_POWER->Get__STRING();
				double io_set   = atof(ch_data);
				double io_value = io_set + set_offset;

				ch_data.Format("%.1f", io_value);
				sCH__MON_IO_SET_POWER->Set__DATA(ch_data);

				if(io_set > 0.1)		dCH__MON_IO_POWER_STATE->Set__DATA(STR__ON);
				else					dCH__MON_IO_POWER_STATE->Set__DATA(STR__OFF);
			}

			// FORWARD.POWER ...
			{
				ch_data = sEXT_CH__RF_AI_FORWARD_POWER->Get__STRING();
				double io_value = atof(ch_data) - set_offset;

				ch_data.Format("%.1f", io_value);
				sCH__MON_IO_FORWARD_POWER->Set__DATA(ch_data);
			}
			// REFLECT.POWER ...
			{
				ch_data = sEXT_CH__RF_AI_REFLECT_POWER->Get__STRING();
				sCH__MON_IO_REFLECT_POWER->Set__DATA(ch_data);
			}
		}

		// RF.ON TIME ...
		if(loop_count == 1)
		{
			ch_data = sCH__MON_IO_FORWARD_POWER->Get__STRING();
			double cur__rf_power = atof(ch_data);

			if(cur__rf_power > 1.0)
			{		
				aCH__MON_RF_ON_TIME_TOTAL_SEC->Inc__VALUE(1);
				double cur__on_sec = aCH__MON_RF_ON_TIME_TOTAL_SEC->Get__VALUE();
	
				if(cur__on_sec >= 3600)
				{
					aCH__MON_RF_ON_TIME_TOTAL_SEC->Set__VALUE(0);
					aCH__MON_RF_ON_TIME_TOTAL_HOUR->Inc__VALUE(1);
				}
			}
		}
		else
		{
			if(dCH__MON_RF_ON_TIME_RESET->Check__DATA(STR__RESET) > 0)
			{
				dCH__MON_RF_ON_TIME_RESET->Set__DATA(STR__RETURN);

				// ...
				{
					SYSTEMTIME st;
					GetLocalTime(&st);

					ch_data.Format("%00004d.%002d.%002d", st.wYear,st.wMonth,st.wDay);
					sCH__MON_RF_ON_TIME_START_DATE->Set__DATA(ch_data);
				
					aCH__MON_RF_ON_TIME_TOTAL_HOUR->Set__VALUE(0);
					aCH__MON_RF_ON_TIME_TOTAL_SEC->Set__VALUE(0);
				}
			}
		}

		/*
		// Recipe Config Item ...
		{
			aCH__REFL_POWER_LIMIT->Get__DATA(str_data);
			dbRcp_refl_limit = atof(str_data);

			aCH__REFL_COEFFICIENT_LIMIT->Get__DATA(str_data);
			dbRcp_refl_coeff_limit = atof(str_data);
		}

		// Object Reading Set Power & Forward, Reflect Power ...
		{
			str_data = sCH__MON_IO_POWER_SET->Get__STRING();
			dbRf_Set_Power = atof(str_data);
		
			str_data = sCH__MON_IO_FORWARD_POWER->Get__STRING();
			dbRf_Fwd_power = atof(str_data);

			str_data = sCH__MON_IO_REFLECT_POWER->Get__STRING();
			dbRf_Refl_Power = atof(str_data);
		}
		*/

		/*
		// Recipe SET Reflect Power Limit Value "0" Disable Monitoring ...
		if(dbRcp_refl_limit > 0)	
		{
			if(dbRcp_refl_limit < dbRf_Refl_Power)
			{
				dCH__RF_STABLE_FLAG->Set__DATA("OFF");

				if(nRefl_Limit_Cnt > nCfg_Hard_Tol_Timeout)
				{
					CString str_msg;

					str_msg.Format("REFLECTED POWER :%.2f, CFG_REFLECT_LIMIT:%.2f, TIME:%d sec", 
									dbRf_Refl_Power, 
									dbRcp_refl_limit, 
									nCfg_Hard_Tol_Timeout);

					// ...
					{
						int alarm_id = ALID__REFLECTED_POWER_OVER;
						Alarm__POST_CHECK(p_alarm, str_msg, alarm_id);
					}

					// ...
					{
						dCH__RF_ABORT_FLAG->Set__DATA("ON");
						dCH__MON_FLAG->Set__DATA("IDLE");

						nRefl_Limit_Cnt = 0;
					}
					break;
				}

				nRefl_Limit_Cnt++;
			}
			else
			{
				dCH__RF_STABLE_FLAG->Set__DATA("ON");
				nRefl_Limit_Cnt = 0;
			}
		}
		*/

		/*
		// Recipe SET Reflect Coefficient Limit Value "0" Disable Monitoring ...	
		if(dbRf_Fwd_power <= 0)
		{
			dbRf_refl_coeff = 0;
		}
		else
		{
			double temp = dbRf_Refl_Power/dbRf_Fwd_power;
			dbRf_refl_coeff = sqrt(temp);
		}
		aCH__REFL_COEFFICIENT->Set__VALUE(dbRf_refl_coeff);

		if(dbRcp_refl_coeff_limit == 0)
		{
			dbRcp_refl_coeff_limit = dbCfg_Max_Refl_Coeff;		// IF Rcp Limit Is "0", Default Max Reflect Coeff SET.
		}
		if(dbRcp_refl_coeff_limit < dbRf_refl_coeff)
		{
			if(nRefl_Coeff_Limit_Cnt > nCfg_Hard_Tol_Timeout)
			{
				CString str_msg;

				str_msg.Format("REFLECTED COEFFICIENT :%.2f, REFLECT_COEFFICIENT_LIMIT:%.2f, TIME:%d sec", 
								dbRf_refl_coeff, 
								dbRcp_refl_coeff_limit, 
								nCfg_Hard_Tol_Timeout);

				// ...
				{
					int alarm_id = ALID__REFLECTED_COEFF_OVER;
					Alarm__POST_CHECK(p_alarm, str_msg, alarm_id);
				}

				// ...
				{
					dCH__RF_ABORT_FLAG->Set__DATA("ON");
					dCH__MON_FLAG->Set__DATA("IDLE");

					nRefl_Coeff_Limit_Cnt = 0;
				}
				break;
			}

			nRefl_Coeff_Limit_Cnt++;
		}
		else
		{
			nRefl_Coeff_Limit_Cnt = 0;
		}
		*/

		// ...
	}

	return 1;
}
