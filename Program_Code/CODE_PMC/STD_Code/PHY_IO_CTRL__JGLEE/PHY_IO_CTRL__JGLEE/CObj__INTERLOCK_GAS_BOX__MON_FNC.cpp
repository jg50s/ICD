#include "StdAfx.h"
#include "CObj__INTERLOCK_GAS_BOX.h"


// ...
int CObj__INTERLOCK_GAS_BOX
::Mon__INTERLOCK_SENSOR(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	SCX__ASYNC_TIMER_CTRL x_time_check_x[DEF_SIZE__INTERLOCK_SENSOR];
	int error_active_x[DEF_SIZE__INTERLOCK_SENSOR];

	// ...
	{
		int i_limit = iSIZE__INTERLOCK_SENSOR;
		int i;

		for(i=0; i<i_limit; i++)
		{
			error_active_x[i] = -1;
		}
	}

	// ...
	CString ch_data;

	if(iActive__SIM_MODE > 0)
	{
		if(bActive__Gas_Box_Diff_Pressure)
		{
			double cfg__diff_press = aEXT_CH__CFG_GAS_BOX_DIFF_PRESSURE_LOW_PRESSURE->Get__VALUE();
			double cur__diff_press = cfg__diff_press * 1.1;
			
			aEXT_CH__GAS_BOX_DIFF_PRESSURE->Set__VALUE(cur__diff_press);
		}

		//
		int i_limit = iSIZE__INTERLOCK_SENSOR;
		int i;

		for(i=0; i<i_limit; i++)
		{
			dEXT_CH__DI_SENSOR_X[i]->Set__DATA(sDATA__NORMAL_STATE_X[i]);
		}
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		// ...
		{
			int check_mode = 1;

			ch_data = dEXT_CH__CFG_INTERLOCK_USE_MODE->Get__STRING();

			if((ch_data.CompareNoCase(STR__DISABLE)     == 0)
				|| (ch_data.CompareNoCase(STR__ALL_DISABLE) == 0))
			{
				check_mode = -1;
			}
			else if(ch_data.CompareNoCase(STR__CONTROL) == 0)
			{
				ch_data = dEXT_CH__CFG_INTERLOCK_USE__INTERLOCK_SNS_ALL->Get__STRING();

				if(ch_data.CompareNoCase(STR__ENABLE) != 0)
				{
					check_mode = -1;
				}
			}

			if(check_mode < 0)
			{
				dEXT_CH__INTERLOCK_HEAVY_ACTIVE->Set__DATA(STR__OFF);
				dEXT_CH__INTERLOCK_LIGHT_ACTIVE->Set__DATA(STR__OFF);

				sEXT_CH__INTERLOCK_HEAVY_MESSAGE->Set__DATA("");
				sEXT_CH__INTERLOCK_LIGHT_MESSAGE->Set__DATA("");

				// ...
				{
					int i_limit = iSIZE__INTERLOCK_SENSOR;
					int i;

					for(i=0; i<i_limit; i++)
					{
						x_time_check_x[i]->STOP_ZERO();
						error_active_x[i] = -1;
					}
				}
				continue;
			}
		}

		// ...
		double cfg_sec = aEXT_CH__CFG_INTERLOCK_CHECK_SEC->Get__VALUE();

		// ...
		{
			int control_mode = -1;

			if((dEXT_CH__CFG_INTERLOCK_USE_MODE->Check__DATA(STR__CONTROL) > 0)
				|| (dEXT_CH__CFG_INTERLOCK_USE_MODE->Check__DATA(STR__ENABLE)  > 0))
			{
				control_mode = 1;
			}

			int count__err_heavy = 0;
			int count__err_light = 0;

			CString msg__err_heavy = "";
			CString msg__err_light = "";

			int i_limit = iSIZE__INTERLOCK_SENSOR;
			int i;

			for(i=0; i<i_limit; i++)
			{
				ch_data = dEXT_CH__DI_SENSOR_X[i]->Get__STRING();

				if(control_mode > 0)
				{
					if(dEXT_CH__CFG_USE_X[i]->Check__DATA(STR__YES) < 0)
					{
						continue;
					}
				}

				if(ch_data.CompareNoCase(sDATA__NORMAL_STATE_X[i]) == 0)
				{
					x_time_check_x[i]->STOP_ZERO();
					error_active_x[i] = -1;
					continue;
				}
				else
				{
					if(error_active_x[i] < 0)
					{
						error_active_x[i] = 1;

						x_time_check_x[i]->START__COUNT_UP(9999);
					}
				}

				if(x_time_check_x[i]->Get__CURRENT_TIME() < cfg_sec)
				{
					continue;
				}

				x_time_check_x[i]->STOP_ZERO();
				error_active_x[i] = -1;

				// ...
				bool active__err_heavy = false;
				bool active__err_light = false;

				if(iDATA__ERROR_LEVEL_X[i] == _ERR_LEVEL__HEAVY)			active__err_heavy = true;
				else														active__err_light = true;

				if(active__err_heavy)
				{
					int alm_id = ALID__INTERLOCK_HEAVY_ACTIVE + i;
					CString alm_msg;
					CString alm_bff;
					CString r_act;

					alm_msg  = sDATA__ERROR_MSG_X[i];
					alm_msg += "\n";

					alm_bff.Format(" * %s <- %s \n",
						dEXT_CH__DI_SENSOR_X[i]->Get__CHANNEL_NAME(),
						ch_data);
					alm_msg += alm_bff;

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				}
				if(active__err_light)
				{
					int alm_id = ALID__INTERLOCK_LIGHT_ACTIVE + i;
					CString alm_msg;
					CString alm_bff;
					CString r_act;

					alm_msg  = sDATA__ERROR_MSG_X[i];
					alm_msg += "\n";

					alm_bff.Format(" * %s <- %s \n",
						dEXT_CH__DI_SENSOR_X[i]->Get__CHANNEL_NAME(),
						ch_data);
					alm_msg += alm_bff;

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				}

				if(active__err_heavy)
				{
					count__err_heavy++;

					msg__err_heavy += sDATA__ERROR_MSG_X[i];
					msg__err_heavy += "\n";
				}
				if(active__err_light)
				{
					count__err_light++;

					msg__err_light += sDATA__ERROR_MSG_X[i];
					msg__err_light += "\n";
				}
			}

			if(bActive__Gas_Box_Diff_Pressure)
			{
				bool active__gas_box_err = false;

				double cur__diff_press = aEXT_CH__GAS_BOX_DIFF_PRESSURE->Get__VALUE();
				double cfg__diff_press = aEXT_CH__CFG_GAS_BOX_DIFF_PRESSURE_LOW_PRESSURE->Get__VALUE();

				if(cfg__diff_press > 0.1)
				{
					if(cur__diff_press < cfg__diff_press)
					{
						count__err_heavy++;
						msg__err_heavy = "Gas-Box Diff-Pressure Error";

						active__gas_box_err = true;

						// ...
						int alm_id = ALID__GAS_BOX_DIFF_PRESSURE_ERROR;

						CString alm_msg;
						CString alm_bff;
						CString r_act;

						alm_bff.Format(" The current diff-pressure must be more than config diff-pressure \n");
						alm_msg += alm_bff;
						alm_bff.Format(" The current diff-pressure of gas-box is %.1f (pa) \n", cur__diff_press);
						alm_msg += alm_bff;
						alm_bff.Format(" The config diff-pressure of gas-box is %.1f (pa) \n", cfg__diff_press);
						alm_msg += alm_bff;

						p_alarm->Check__ALARM(alm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					}
				}

				if(active__gas_box_err)			dCH__ACTIVE_GAS_BOX_DIFF_PRESSURE_ERROR->Set__DATA(STR__ON);
				else							dCH__ACTIVE_GAS_BOX_DIFF_PRESSURE_ERROR->Set__DATA(STR__OFF);
			}

			if(bActive__DGF_All_Close_Active)
			{
				if(dEXT_CH__DGF_ALL_CLOSE_ACTIVE->Check__DATA(STR__ON) > 0)
				{
					count__err_heavy++;
					msg__err_heavy = "All valve of DGF are closed !";

					// ...
					int alm_id = ALID__DGF_ALL_VALVE_CLOSE;

					CString alm_msg;
					CString alm_bff;
					CString r_act;

					alm_bff.Format(" * %s <- %s \n", 
									dEXT_CH__DGF_ALL_CLOSE_ACTIVE->Get__CHANNEL_NAME(),
									dEXT_CH__DGF_ALL_CLOSE_ACTIVE->Get__STRING());
					alm_msg += alm_bff;

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);					
				}
			}

			if(count__err_heavy > 0)
			{
				dEXT_CH__INTERLOCK_HEAVY_ACTIVE->Set__DATA(STR__ON);
				sEXT_CH__INTERLOCK_HEAVY_MESSAGE->Set__DATA(msg__err_heavy);
			}
			if(count__err_light > 0)
			{
				dEXT_CH__INTERLOCK_LIGHT_ACTIVE->Set__DATA(STR__ON);
				sEXT_CH__INTERLOCK_LIGHT_MESSAGE->Set__DATA(msg__err_light);
			}

			if((count__err_heavy < 1)
			&& (count__err_light < 1))
			{
				dEXT_CH__INTERLOCK_HEAVY_ACTIVE->Set__DATA(STR__OFF);
				dEXT_CH__INTERLOCK_LIGHT_ACTIVE->Set__DATA(STR__OFF);

				sEXT_CH__INTERLOCK_HEAVY_MESSAGE->Set__DATA("");
				sEXT_CH__INTERLOCK_LIGHT_MESSAGE->Set__DATA("");
			}
		}
	}

	return 1;
}
