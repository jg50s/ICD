#include "StdAfx.h"
#include "CObj__MINI8_IO.h"
#include "CObj__MINI8_IO__ALID.h"

#include "CCommon_Utility.h"


// ...
int CObj__MINI8_IO
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	bool active__ai_max_devi;
	SCX__ASYNC_TIMER_CTRL x_timer__ai_max_devi;

	int  count__ai_max_x[CFG__LOOP_SIZE];
	bool active__ai_max_x[CFG__LOOP_SIZE];
	SCX__ASYNC_TIMER_CTRL x_timer__ai_max_x[CFG__LOOP_SIZE];

	int  count__ai_high_temp_x[CFG__LOOP_SIZE];
	bool active__ai_high_temp_x[CFG__LOOP_SIZE];
	SCX__ASYNC_TIMER_CTRL x_timer__ai_high_temp_x[CFG__LOOP_SIZE];

	int  count__ai_high_op_x[CFG__LOOP_SIZE];
	bool active__ai_high_op_x[CFG__LOOP_SIZE];
	SCX__ASYNC_TIMER_CTRL x_timer__ai_high_op_x[CFG__LOOP_SIZE];

	bool active__di_high_x[CFG__LOOP_SIZE];
	SCX__ASYNC_TIMER_CTRL x_timer__di_high_x[CFG__LOOP_SIZE];

	bool active__di_over_x[CFG__LOOP_SIZE];
	SCX__ASYNC_TIMER_CTRL x_timer__di_over_x[CFG__LOOP_SIZE];

	// ...
	int ref__count_max = 20;

	// ...
	CCommon_Utility m_fnc;
	CString ch_data;

	int loop_count = 0;
	int i;

	// Timer.Init ...
	{
		active__ai_max_devi = false;
		x_timer__ai_max_devi->STOP_ZERO();

		for(i=0; i<iLOOP_SIZE; i++)
		{
			count__ai_max_x[i] = 0;
			active__ai_max_x[i] = false;
			x_timer__ai_max_x[i]->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_MAX_DEVIATION_CHECK_TIME_LOOP_X[i]->Get__CHANNEL_NAME());
			x_timer__ai_max_x[i]->STOP_ZERO();

			count__ai_high_temp_x[i] = 0;
			active__ai_high_temp_x[i] = false;
			x_timer__ai_high_temp_x[i]->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_TEMP_HIGH_LIMIT_CHECK_TIME__LOOP_X[i]->Get__CHANNEL_NAME());
			x_timer__ai_high_temp_x[i]->STOP_ZERO();

			count__ai_high_op_x[i] = 0;
			active__ai_high_op_x[i] = false;
			x_timer__ai_high_op_x[i]->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_OP_HIGH_LIMIT_CHECK_TIME__LOOP_X[i]->Get__CHANNEL_NAME());
			x_timer__ai_high_op_x[i]->STOP_ZERO();

			//
			active__di_high_x[i] = false;
			x_timer__di_high_x[i]->STOP_ZERO();

			active__di_over_x[i] = false;
			x_timer__di_over_x[i]->STOP_ZERO();
		}
	}

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		loop_count++;
		if(loop_count > 10)			loop_count = 1;

		// Range Check ...
		if(loop_count == 1)
		{
			for(i=0; i<iLOOP_SIZE; i++)
			{
				double cfg_min = aCH__CFG_MIN_VALUE__LOOP_X[i]->Get__VALUE();
				double cfg_max = aCH__CFG_MAX_VALUE__LOOP_X[i]->Get__VALUE();
				int cfg_dec = (int) aCH__CFG_DEC_VALUE__LOOP_X[i]->Get__VALUE();

				aCH__MON_IO_SET_SP__LOOP_X[i]->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);

				aCH__CFG_TEMP_HIGH_LIMIT__LOOP_X[i]->Change__MIN_MAX_DEC(cfg_min,cfg_max+30,cfg_dec);
				aCH__CFG_INITIAL_TARTGET_TEMP__LOOP_X[i]->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);

				if(dCH__CFG_SP_RANGE_INTERLOCK_USE->Check__DATA(STR__YES) > 0)
				{
					double cfg_range = aCH__CFG_SP_RANGE_INTERLOCK_VALUE->Get__VALUE();
					
					ch_data = sCH__MON_IO_GET_PV__LOOP_X[i]->Get__STRING();
					double cur_pv = atof(ch_data);
					double max_range = cur_pv + cfg_range;
					double min_range = cur_pv - cfg_range;
					
					if(max_range > cfg_max)		max_range = cfg_max;
					if(min_range < cfg_min)		min_range = cfg_min;

					aCH__CFG_TARGET_SP__LOOP_X[i]->Change__MIN_MAX_DEC(min_range,max_range,cfg_dec);
				}
				else
				{
					aCH__CFG_TARGET_SP__LOOP_X[i]->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);
				}
			}

		}

		// 
		if(iActive__SIM_MODE > 0)
		{
			for(i=0; i<iLOOP_SIZE; i++)
			{
				aEXT_CH__AO_TEMPERATURE_SET__LOOP_X[i]->Get__DATA(ch_data);
				aCH__MON_IO_SET_SP__LOOP_X[i]->Set__DATA(ch_data);
				
				sCH__MON_IO_GET_PV__LOOP_X[i]->Set__DATA(ch_data);

				if(bActive__AI_TEMPERATURE_SET__LOOP_X[i])
					sCH__MON_IO_GET_WORKING_SP__LOOP_X[i]->Set__DATA(ch_data);
				else
					sCH__MON_IO_GET_WORKING_SP__LOOP_X[i]->Set__DATA("___");

				//
				if(bActive__AI_TEMPERATURE_POWER__LOOP_X[i])
				{
					double cfg_max = aCH__CFG_MAX_VALUE__LOOP_X[i]->Get__VALUE();
					double cur_sp  = aCH__MON_IO_SET_SP__LOOP_X[i]->Get__VALUE();

					if(cfg_max > 0.1)
					{
						double cur_per = (cur_sp / cfg_max) * 100.0;
						ch_data.Format("%.1f", cur_per);
					}
					else
					{
						ch_data = "!!!";
					}
	
					sCH__MON_IO_GET_WORKING_OP__LOOP_X[i]->Set__DATA(ch_data);
				}
				else
				{
					sCH__MON_IO_GET_WORKING_OP__LOOP_X[i]->Set__DATA("___");
				}
			}
		}
		else
		{
			for(i=0; i<iLOOP_SIZE; i++)
			{
				// SET ...
				{
					aEXT_CH__AO_TEMPERATURE_SET__LOOP_X[i]->Get__DATA(ch_data);
					aCH__MON_IO_SET_SP__LOOP_X[i]->Set__DATA(ch_data);
				}

				// PV ...
				{
					aEXT_CH__AI_TEMPERATURE_READ__LOOP_X[i]->Get__DATA(ch_data);
					sCH__MON_IO_GET_PV__LOOP_X[i]->Set__DATA(ch_data);
				}
				
				// SP ...
				if(bActive__AI_TEMPERATURE_SET__LOOP_X[i])
				{
					aEXT_CH__AI_TEMPERATURE_SET__LOOP_X[i]->Get__DATA(ch_data);
					sCH__MON_IO_GET_WORKING_SP__LOOP_X[i]->Set__DATA(ch_data);
				}
				else
				{
					sCH__MON_IO_GET_WORKING_SP__LOOP_X[i]->Set__DATA("___");
				}
				
				// OP ...
				if(bActive__AI_TEMPERATURE_POWER__LOOP_X[i])
				{
					aEXT_CH__AI_TEMPERATURE_POWER__LOOP_X[i]->Get__DATA(ch_data);
					sCH__MON_IO_GET_WORKING_OP__LOOP_X[i]->Set__DATA(ch_data);
				}
				else
				{
					sCH__MON_IO_GET_WORKING_OP__LOOP_X[i]->Set__DATA("___");
				}

				// PV Offset ...
				if(bActive__AI_PV_OFFSET__LOOP_X[i])
				{
					aEXT_CH__AI_PV_OFFSET__LOOP_X[i]->Get__DATA(ch_data);
					sCH__MON_IO_GET_PV_OFFSET__LOOP_X[i]->Set__DATA(ch_data);
				}
				else
				{
					sCH__MON_IO_GET_PV_OFFSET__LOOP_X[i]->Set__DATA("___");
				}

				// OP High.Limit ...
				if(bActive__AI_OP_HIGH_LIMIT__LOOP_X[i])
				{
					aEXT_CH__AI_OP_HIGH_LIMIT__LOOP_X[i]->Get__DATA(ch_data);
					sCH__MON_IO_GET_OP_HIGH_LIMIT__LOOP_X[i]->Set__DATA(ch_data);
				}
				else
				{
					sCH__MON_IO_GET_OP_HIGH_LIMIT__LOOP_X[i]->Set__DATA("___");
				}

				// OP.Forward ...
				if(bActive__AI_OP_FORWARD__LOOP_X[i])
				{
					aEXT_CH__AI_OP_FORWARD__LOOP_X[i]->Get__DATA(ch_data);
					sCH__MON_IO_GET_FORWARD_OP__LOOP_X[i]->Set__DATA(ch_data);
				}
				else
				{
					sCH__MON_IO_GET_FORWARD_OP__LOOP_X[i]->Set__DATA("___");
				}
			}
		}

		if(bActive__SI_ALARM_STATE_HEXA)
		{
			unsigned char uch_data[20];

			ch_data = sEXT_CH__SI_ALARM_STATE_HEXA->Get__STRING();

			// String_Hexa -> Int_Hexa
			{
				CStringArray l_data;
				m_fnc.Get__StringArrray_From_String(ch_data," ", l_data);

				int k_limit = l_data.GetSize();
				if(k_limit > 20)		k_limit = 20;

				for(int k=0; k<k_limit; k++)
				{
					uch_data[k] = 0x0ff & m_fnc.Get__Hexa_From_String(l_data[k]);
				}
			}

			// ...
			UNION_2_BYTE__UINT m_alarm;

			m_alarm.cBYTE[0] = 0x0ff & uch_data[0];
			m_alarm.cBYTE[1] = 0x0ff & uch_data[2];

			int hexa_data = m_alarm.uiDATA;
			
			if(hexa_data > 0)			sCH__MON_IO_GET_ALARM_STATUS_ACTIVE->Set__DATA(STR__ON);
			else						sCH__MON_IO_GET_ALARM_STATUS_ACTIVE->Set__DATA(STR__OFF);

			for(int i=0; i<8; i++)
			{
				int bit_check = 0x01 & (hexa_data >> i);

				if(bit_check > 0)		sCH__MON_IO_GET_ALARM_STATUS_BIT_X[i]->Set__DATA(STR__ON);
				else					sCH__MON_IO_GET_ALARM_STATUS_BIT_X[i]->Set__DATA(STR__OFF);
			}
		}

		// Alarm Check : H/W ...
		if(loop_count == 1)
		{
			for(int i=0; i<CFG__ALARM_BIT_SIZE; i++)
			{
				if(sCH__MON_IO_GET_ALARM_STATUS_BIT_X[i]->Check__DATA(STR__ON) < 0)
				{
					continue;
				}

				// Interlock : Power Off ...
				{
					Fnc__ALL_MC_OFF_BY_DI();
				}

				// ...
				{
					int alm_id = ALID__HW_ALARM__BIT_00 + i;
					CString alm_msg;
					CString r_act;

					alm_msg  = sCH__MON_IO_GET_ALARM_MESSAGE_BIT_X[i]->Get__STRING();
					alm_msg += "\n";

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				}
			}	
		}

		// Alarm Check : Max. Diff Temperature ...
		{
			double cur_min = 0.0;
			double cur_max = 0.0;

			for(i=0; i<iLOOP_SIZE; i++)
			{
				ch_data = sCH__MON_IO_GET_PV__LOOP_X[i]->Get__STRING();
				double cur_temp = atof(ch_data);

				if(i == 0)
				{
					cur_min = cur_temp;
					cur_max = cur_temp;
				}
				else
				{
					if(cur_temp > cur_max)		cur_max = cur_temp;
					if(cur_temp < cur_min)		cur_min = cur_temp;
				}
			}

			double cur_diff = cur_max - cur_min;
			double cfg_max  = aCH__CFG_TEMPERATURE_DIFF_MAX->Get__VALUE();
			
			if((cur_diff >= cfg_max)
			&& (cfg_max > 0.1))
			{
				if(!active__ai_max_devi)
				{
					active__ai_max_devi = true;
					x_timer__ai_max_devi->START__COUNT_UP(9999);
				}

				double cfg__err_check = 1.0;
				
				if(x_timer__ai_max_devi->Get__CURRENT_TIME() > cfg__err_check)
				{
					x_timer__ai_max_devi->STOP_ZERO();

					// Interlock : Power Off ...
					{
						Fnc__ALL_MC_OFF_BY_AI();
					}

					// Alarm Post ...
					{
						int alm_id = ALID__MAX_DIFF_TEMPERATURE;

						CString alm_msg;
						CString alm_bff;
						CString r_act;

						for(i=0; i<iLOOP_SIZE; i++)
						{
							CString cfg_name = sCH__CFG_NAME__LOOP_X[i]->Get__STRING();

							ch_data = sCH__MON_IO_GET_PV__LOOP_X[i]->Get__STRING();
							double cur_temp = atof(ch_data);

							alm_bff.Format("Zone%1d(%s)의 온도는 %.1f C 입니다. \n", i+1,cfg_name,cur_temp);
							alm_msg += alm_bff;
						}
						alm_msg += "\n";

						alm_bff.Format("현재, Zone의 최대 온도차는 %.0f C 입니다. \n", cur_diff);
						alm_msg += alm_bff;

						alm_bff.Format("Config에 설정된 최대 온도차는 %.0f C 입니다. \n", cfg_max);
						alm_msg += alm_bff;

						p_alarm->Check__ALARM(alm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					}
				}
			}
			else
			{
				active__ai_max_devi = false;
				x_timer__ai_max_devi->STOP_ZERO();
			}
		}

		// Alarm Check : Loop.x - MAx.Deviation ...
		{
			bool active__err_msg = false;
			CString err_msg = "";

			for(i=0; i<iLOOP_SIZE; i++)
			{
				ch_data = sCH__MON_IO_GET_PV__LOOP_X[i]->Get__STRING();
				double cur_pv = atof(ch_data);

				double cur_sp = aCH__MON_IO_SET_SP__LOOP_X[i]->Get__VALUE();
				double dif_tmp = cur_sp - cur_pv;

				double max_dev = aCH__CFG_MAX_DEVIATION__LOOP_X[i]->Get__VALUE();

				if((max_dev < 1)
				|| (dif_tmp < max_dev))
				{
					if(count__ai_max_x[i] > 0)
					{
						count__ai_max_x[i]--;
					}

					if(count__ai_max_x[i] <= 0)
					{
						sCH__MON_MAX_DEVIATION_ACTIVE__LOOP_X[i]->Set__DATA(STR__OFF);
					
						active__ai_max_x[i] = false;
						x_timer__ai_max_x[i]->STOP_ZERO();
					}
					continue;
				}

				// Alarm : Max Deviation ...
				{
					if(!active__ai_max_x[i])
					{
						active__ai_max_x[i] = true;
						x_timer__ai_max_x[i]->START__COUNT_UP(9999);
					}
					
					double cfg__err_check = aCH__CFG_ERROR_CHECK_TIMEOUT__LOOP_X[i]->Get__VALUE();
					if(x_timer__ai_max_x[i]->Get__CURRENT_TIME() < cfg__err_check)
					{
						continue;
					}
					else
					{
						count__ai_max_x[i] = ref__count_max;

						active__ai_max_x[i] = false;
						x_timer__ai_max_x[i]->STOP_ZERO();

						//
						sCH__MON_MAX_DEVIATION_ACTIVE__LOOP_X[i]->Set__DATA(STR__ON);
					}

					active__err_msg = true;

					// ...
					{
						CString cfg_name = 	sCH__CFG_NAME__LOOP_X[i]->Get__STRING();

						// ...
						CString alm_msg = "";
						CString alm_bff;

						alm_bff.Format("config에 등록된 Loop%1d(%s)의 Max. Deviation은 %.0f C 입니다. \n", i+1,cfg_name,max_dev);
						alm_msg += alm_bff;

						alm_bff.Format("설정된 온도와 감지된 온도의 차이는 %.1f C 입니다.\n", dif_tmp);
						alm_msg += alm_bff;
						alm_bff.Format("  * 설정 온도는 %.1f C 입니다.\n", cur_sp);
						alm_msg += alm_bff;
						alm_bff.Format("  * 감지된 온도는 %.1f C 입니다.\n", cur_pv);
						alm_msg += alm_bff;
						alm_msg += "\n";

						err_msg += alm_msg;
					}

					Fnc__MC_OFF_BY_AI(i);
				}
			}

			if(active__err_msg)
			{
				sCH__MON_MAX_DEVIATION_ACTIVE__LOOP_ALL->Set__DATA(STR__ON);

				// ...
				{
					int alm_id = ALID__MAX_DEVIATION_LOOP;
					CString r_act;

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id,err_msg);
				}

				Fnc__ALL_MC_OFF_BY_AI();
			}
			else
			{
				sCH__MON_MAX_DEVIATION_ACTIVE__LOOP_ALL->Set__DATA(STR__OFF);
			}
		}

		// Alarm Check : Loop.x - High Limit Temperature ...
		{
			bool active__high_limit = false;

			CString err_msg;
			CString err_bff;

			for(i=0; i<iLOOP_SIZE; i++)
			{
				ch_data = sCH__MON_IO_GET_PV__LOOP_X[i]->Get__STRING();
				double cur_value = atof(ch_data);
				double cfg_limit = aCH__CFG_TEMP_HIGH_LIMIT__LOOP_X[i]->Get__VALUE();

				if((cfg_limit < 0.1)
				|| (cur_value < cfg_limit))
				{
					if(count__ai_high_temp_x[i] > 0)
					{
						count__ai_high_temp_x[i]--;
					}

					if(count__ai_high_temp_x[i] <= 0)
					{
						active__ai_high_temp_x[i] = false;
						x_timer__ai_high_temp_x[i]->STOP_ZERO();

						sCH__MON_TEMP_HIGH_LIMIT_ACTIVE__LOOP_X[i]->Set__DATA(STR__OFF);
					}
					continue;
				}

				if(!active__ai_high_temp_x[i])
				{
					active__ai_high_temp_x[i] = true;
					x_timer__ai_high_temp_x[i]->START__COUNT_UP(9999);
				}

				double cfg__err_check = aCH__CFG_ERROR_CHECK_TIMEOUT__LOOP_X[i]->Get__VALUE();
				if(x_timer__ai_high_temp_x[i]->Get__CURRENT_TIME() < cfg__err_check)
				{
					continue;
				}
				else
				{
					count__ai_high_temp_x[i] = ref__count_max;

					active__ai_high_temp_x[i] = false;
					x_timer__ai_high_temp_x[i]->STOP_ZERO();

					//
					sCH__MON_TEMP_HIGH_LIMIT_ACTIVE__LOOP_X[i]->Set__DATA(STR__ON);
				}

				active__high_limit = true;

				// Alarm ...
				{
					CString cfg_name = sCH__CFG_NAME__LOOP_X[i]->Get__STRING();

					err_bff.Format("%s의 온도는 %.1f C 입니다. \n", cfg_name, cur_value);
					err_msg += err_bff;

					err_bff.Format("Config에 설정된 %s의 High Limit은 %.0f C 입니다. \n", cfg_name, cfg_limit);
					err_msg += err_bff;
					err_msg += "\n";
				}

				// Interlock : Power Off ...
				{
					Fnc__MC_OFF_BY_AI(i);
				}
			}

			if(active__high_limit)
			{
				Fnc__ALL_MC_OFF_BY_AI();

				// Alarm Post ...
				{
					int alm_id = ALID__TEMPERATURE_HIGH_LIMIT;
					CString r_act;

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, err_msg);
				}

				sCH__MON_TEMP_HIGH_LIMIT_ACTIVE__LOOP_ALL->Set__DATA(STR__ON);
			}
			else
			{
				bool active__all_clear = true;

				for(i=0; i<iLOOP_SIZE; i++)
				{
					if(sCH__MON_TEMP_HIGH_LIMIT_ACTIVE__LOOP_X[i]->Check__DATA(STR__ON) < 0)
						continue;

					active__all_clear = false;
					break;
				}

				if(active__all_clear)
					sCH__MON_TEMP_HIGH_LIMIT_ACTIVE__LOOP_ALL->Set__DATA(STR__OFF);
			}
		}

		// Alarm Check : Loop.x - High Limit Power ...
		{
			bool active__high_limit = false;

			CString err_msg;
			CString err_bff;

			for(i=0; i<iLOOP_SIZE; i++)
			{
				ch_data = sCH__MON_IO_GET_WORKING_OP__LOOP_X[i]->Get__STRING();
				double cur_value = atof(ch_data);
				double cfg_limit = aCH__CFG_OP_HIGH_LIMIT__LOOP_X[i]->Get__VALUE();

				if((cfg_limit < 0.1)
				|| (cur_value < cfg_limit))
				{
					if(count__ai_high_op_x[i] > 0)
					{
						count__ai_high_op_x[i]--;
					}

					if(count__ai_high_op_x[i] <= 0)
					{
						active__ai_high_op_x[i] = false;
						x_timer__ai_high_op_x[i]->STOP_ZERO();

						sCH__MON_OP_HIGH_LIMIT_ACTIVE__LOOP_X[i]->Set__DATA(STR__OFF);
					}
					continue;
				}

				if(!active__ai_high_op_x[i])
				{
					active__ai_high_op_x[i] = true;
					x_timer__ai_high_op_x[i]->START__COUNT_UP(9999);
				}

				double cfg__err_check = aCH__CFG_ERROR_CHECK_TIMEOUT__LOOP_X[i]->Get__VALUE();
				if(x_timer__ai_high_op_x[i]->Get__CURRENT_TIME() < cfg__err_check)
				{
					continue;
				}
				else
				{
					count__ai_high_op_x[i] = ref__count_max;

					active__ai_high_op_x[i] = false;
					x_timer__ai_high_op_x[i]->STOP_ZERO();

					//
					sCH__MON_OP_HIGH_LIMIT_ACTIVE__LOOP_X[i]->Set__DATA(STR__ON);
				}

				active__high_limit = true;

				// Alarm ...
				{
					CString cfg_name = sCH__CFG_NAME__LOOP_X[i]->Get__STRING();

					err_bff.Format("%s의 온도는 %.1f C 입니다. \n", cfg_name, cur_value);
					err_msg += err_bff;

					err_bff.Format("Config에 설정된 %s의 Output.Power - High.Limit은 %.0f C 입니다. \n", cfg_name, cfg_limit);
					err_msg += err_bff;
					err_msg += "\n";
				}

				// Interlock : Power Off ...
				{
					Fnc__MC_OFF_BY_AI(i);
				}
			}

			if(active__high_limit)
			{
				Fnc__ALL_MC_OFF_BY_AI();

				// Alarm Post ...
				{
					int alm_id = ALID__POWER_HIGH_LIMIT;
					CString r_act;

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, err_msg);
				}

				sCH__MON_OP_HIGH_LIMIT_ACTIVE__LOOP_ALL->Set__DATA(STR__ON);
			}
			else
			{
				bool active__all_clear = true;

				for(i=0; i<iLOOP_SIZE; i++)
				{
					if(sCH__MON_OP_HIGH_LIMIT_ACTIVE__LOOP_X[i]->Check__DATA(STR__ON) < 0)
						continue;

					active__all_clear = false;
					break;
				}

				if(active__all_clear)
					sCH__MON_OP_HIGH_LIMIT_ACTIVE__LOOP_ALL->Set__DATA(STR__OFF);
			}
		}

		// DI.CHECK ...
		{
			bool active__di_over_temp  = false;
			bool active__di_high_limit = false;

			for(i=0; i<iLOOP_SIZE; i++)
			{
				// OVER.TEMP ...
				if(bActive__DI_OVER_TEMP__LOOP_X[i])
				{
					if(dCH__CFG_DI_OVER_TEMP__LOOP_X[i]->Check__DATA(STR__YES) < 0)
					{
						sCH__MON_DI_OVER_TEMP_STATE_LOOP_X[i]->Set__DATA(STR__OFF);

						active__di_over_x[i] = false;
						x_timer__di_over_x[i]->STOP_ZERO();
						continue;
					}

					ch_data = dEXT_CH__DI_OVER_TEMP__LOOP_X[i]->Get__STRING();
					
					if((ch_data.CompareNoCase(STR__ON) == 0) || (ch_data.CompareNoCase("1") == 0))
					{
						if(!active__di_over_x[i])
						{
							active__di_over_x[i] = true;
							x_timer__di_over_x[i]->START__COUNT_UP(9999);
							continue;
						}

						double cfg__err_check = aCH__CFG_ERROR_CHECK_TIMEOUT__LOOP_X[i]->Get__VALUE();

						if(x_timer__di_over_x[i]->Get__CURRENT_TIME() >= cfg__err_check)
						{
							active__di_over_x[i] = false;
							x_timer__di_over_x[i]->STOP_ZERO();

							//
							sCH__MON_DI_OVER_TEMP_STATE_LOOP_X[i]->Set__DATA(STR__ON);

							// Alarm ...
							{
								int alm_id = ALID__DI_OVER_TEMP__LOOP_X + i;
								CString alm_msg;
								CString r_act;

								alm_msg.Format(" * %s <- %s \n",
												sCH__MON_DI_OVER_TEMP_STATE_LOOP_X[i]->Get__CHANNEL_NAME(),
												sCH__MON_DI_OVER_TEMP_STATE_LOOP_X[i]->Get__STRING());

								p_alarm->Check__ALARM(alm_id, r_act);
								p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);

							}

							active__di_over_temp = true;
							Fnc__MC_OFF_BY_DI(i);
						}
					}
					else
					{
						sCH__MON_DI_OVER_TEMP_STATE_LOOP_X[i]->Set__DATA(STR__OFF);

						active__di_over_x[i] = false;
						x_timer__di_over_x[i]->STOP_ZERO();
					}
				}

				// DI.HIGH.LIMIT ...
				if(bActive__DI_HIGH_LIMIT__LOOP_X[i])
				{
					if(dCH__CFG_DI_HIGH_LIMIT__LOOP_X[i]->Check__DATA(STR__YES) < 0)
					{
						sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_X[i]->Set__DATA(STR__OFF);

						active__di_high_x[i] = false;
						x_timer__di_high_x[i]->STOP_ZERO();
						continue;
					}

					ch_data = sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_X[i]->Get__STRING();

					if((ch_data.CompareNoCase(STR__ON) == 0) || (ch_data.CompareNoCase("1") == 0))
					{
						if(!active__di_high_x[i])
						{
							active__di_high_x[i] = true;
							x_timer__di_high_x[i]->START__COUNT_UP(9999);
						}

						double cfg__err_check = aCH__CFG_ERROR_CHECK_TIMEOUT__LOOP_X[i]->Get__VALUE();

						if(x_timer__di_high_x[i]->Get__CURRENT_TIME() >= cfg__err_check)
						{
							active__di_high_x[i] = false;
							x_timer__di_high_x[i]->STOP_ZERO();

							//
							sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_X[i]->Set__DATA(STR__ON);

							// Alarm ...
							{
								int alm_id = ALID__DI_HIGH_LIMIT__LOOP_X + i;
								CString alm_msg;
								CString r_act;

								alm_msg.Format(" * %s <- %s \n",
												sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_X[i]->Get__CHANNEL_NAME(),
												sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_X[i]->Get__STRING());

								p_alarm->Check__ALARM(alm_id, r_act);
								p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);

							}

							active__di_high_limit = true;
							Fnc__MC_OFF_BY_DI(i);
						}
					}
					else
					{
						sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_X[i]->Set__DATA(STR__OFF);

						active__di_high_x[i] = false;
						x_timer__di_high_x[i]->STOP_ZERO();
					}
				}

				// DO.POWER ...
				if(bActive__DO_HEATER_POWER__LOOP_X[i])
				{
					ch_data = dEXT_CH__DO_HEATER_POWER__LOOP_X[i]->Get__STRING();
					sCH__MON_DO_HEATER_POWER__LOOP_X[i]->Set__DATA(ch_data);
				}
			}

			// DI.OVER_TEMP ...
			if(active__di_over_temp)
			{
				sCH__MON_DI_OVER_TEMP_STATE_LOOP_ALL->Set__DATA(STR__ON);

				Fnc__ALL_MC_OFF_BY_DI();
			}
			else
			{
				bool active__all_clear = true;

				for(i=0; i<iLOOP_SIZE; i++)
				{
					if(sCH__MON_DI_OVER_TEMP_STATE_LOOP_X[i]->Check__DATA(STR__ON) < 0)
						continue;

					active__all_clear = false;
					break;
				}

				if(active__all_clear)
					sCH__MON_DI_OVER_TEMP_STATE_LOOP_ALL->Set__DATA(STR__OFF);
			}

			// DI.HIGH_LIMIT ...
			if(active__di_high_limit)
			{
				sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_ALL->Set__DATA(STR__ON);

				Fnc__ALL_MC_OFF_BY_DI();
			}
			else
			{
				bool active__all_clear = true;

				for(i=0; i<iLOOP_SIZE; i++)
				{
					if(sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_X[i]->Check__DATA(STR__ON) < 0)
						continue;

					active__all_clear = false;
					break;
				}

				if(active__all_clear)
					sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_ALL->Set__DATA(STR__OFF);
			}
		}

		// ...
	}

	return 1;
}


// ...
int CObj__MINI8_IO
::Fnc__ALL_MC_OFF_BY_AI()
{
	if(dCH__CFG_AI_ALARM_MC_OFF__LOOP_ALL->Check__DATA(STR__YES) < 0)			
	{
		return 1;
	}

	for(int i=0; i<iLOOP_SIZE; i++)
	{
		if(bActive__DO_HEATER_POWER__LOOP_X[i])
			dEXT_CH__DO_HEATER_POWER__LOOP_X[i]->Set__DATA(STR__OFF);

		Fnc__AO_TEMPERATURE_SET(i);
	}
	return 1;
}
int CObj__MINI8_IO
::Fnc__ALL_MC_OFF_BY_DI()
{
	if(dCH__CFG_DI_ALARM_MC_OFF__LOOP_ALL->Check__DATA(STR__YES) < 0)			
	{
		return 1;
	}

	for(int i=0; i<iLOOP_SIZE; i++)
	{
		if(bActive__DO_HEATER_POWER__LOOP_X[i])
			dEXT_CH__DO_HEATER_POWER__LOOP_X[i]->Set__DATA(STR__OFF);

		Fnc__AO_TEMPERATURE_SET(i);
	}
	return 1;
}

int CObj__MINI8_IO
::Fnc__MC_OFF_BY_AI(const int index)
{
	if(index < 0)
	{
		Fnc__ALL_MC_OFF_BY_AI();
	}
	else
	{
		if((index >= 0) && (index < iLOOP_SIZE))
		{
			bool active__mc_off = false;

			if(dCH__CFG_AI_ALARM_MC_OFF__LOOP_X[index]->Check__DATA(STR__YES) > 0)			
			{
				active__mc_off = true; 
			}

			if(active__mc_off)
			{
				if(bActive__DO_HEATER_POWER__LOOP_X[index])
					dEXT_CH__DO_HEATER_POWER__LOOP_X[index]->Set__DATA(STR__OFF);

				Fnc__AO_TEMPERATURE_SET(index);
			}
		}
	}
	return 1;
}
int CObj__MINI8_IO
::Fnc__MC_OFF_BY_DI(const int index)
{
	if(index < 0)
	{
		Fnc__ALL_MC_OFF_BY_DI();
	}
	else
	{
		if((index >= 0) && (index < iLOOP_SIZE))
		{
			bool active__mc_off = false;

			if(dCH__CFG_DI_ALARM_MC_OFF__LOOP_X[index]->Check__DATA(STR__YES) > 0)			
			{
				active__mc_off = true; 
			}

			if(active__mc_off)
			{
				if(bActive__DO_HEATER_POWER__LOOP_X[index])
					dEXT_CH__DO_HEATER_POWER__LOOP_X[index]->Set__DATA(STR__OFF);

				Fnc__AO_TEMPERATURE_SET(index);
			}
		}
	}
	return 1;
}

void CObj__MINI8_IO
::Fnc__AO_TEMPERATURE_SET(const int index)
{
	if(bActive__CTRL_ACTIVE__LOOP_X[index])
		aEXT_CH__AO_TEMPERATURE_SET__LOOP_X[index]->Set__VALUE(0.0);
}
