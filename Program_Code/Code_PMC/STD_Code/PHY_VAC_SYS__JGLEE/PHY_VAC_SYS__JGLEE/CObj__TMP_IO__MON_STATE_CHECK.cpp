#include "StdAfx.h"
#include "CObj__TMP_IO.h"
#include "CObj__TMP_IO__ALID.h"


// ...
int CObj__TMP_IO
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	// Init ...
	{
		sCH__MON_COMM_STATE->Set__DATA(STR__ONLINE);

		dCH__MON_PUMP_ON_SNS->Set__DATA(STR__OFF);
		dCH__MON_ERROR_ON_SNS->Set__DATA(STR__OFF);

		sCH__MON_ROT_SPEED_RPM_READ->Set__DATA("?");
		sCH__MON_PUMP_TEMPERATURE_READ->Set__DATA("?");
	}

	if(iActive__SIM_MODE > 0)
	{
		if(bActive__TMP_DI_NORMAL_SPEED)		dEXT_CH__TMP_DI_NORMAL_SPEED->Set__DATA(STR__OFF);
		if(bActive__TMP_DI_ACCELERATION)		dEXT_CH__TMP_DI_ACCELERATION->Set__DATA(STR__OFF);

		if(bActive__TMP_DI_ALARM_STATE)			dEXT_CH__TMP_DI_ALARM_STATE->Set__DATA(STR__OFF);
		if(bActive__TMP_DI_WARNING_STATE)		dEXT_CH__TMP_DI_WARNING_STATE->Set__DATA(STR__OFF);

		if(bActive__DI_PCW_ALARM)				dEXT_CH__DI_PCW_ALARM->Set__DATA(STR__OFF);
		if(bActive__DI_PCW_WATER_LEAK)			dEXT_CH__DI_PCW_WATER_LEAK->Set__DATA(STR__OFF);
	}

	// ...
	double loop_sec = 0.1;

	double cur__high_speed__err_sec = 0;
	double cur__low_speed__err_sec  = 0;

	double cur__high_temperature__err_sec = 0;

	double cur__di_foreline__err_sec = 0;
	double cur__di_pcw__err_sec = 0;

	int count_error__foreline_vlv_open = 0;

	bool active__tmp_init_check = true;

	int loop_count = 0;

	// ...
	{
		Sleep(5000);
	}
	
	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(loop_sec);

		loop_count++;
		if(loop_count > 10)			loop_count = 1;

		if(loop_count == 1)
		{
			int active__err_check = p_alarm->Check__Posted_Internal_Alarm(iLIST_ALID__PART);

			if(active__err_check > 0)		dCH__MON_PART_ERROR_ACTIVE->Set__DATA(STR__ON);
			else							dCH__MON_PART_ERROR_ACTIVE->Set__DATA(STR__OFF);
		}

		// UPDATE.IO ...
		{
			if(bActive__TMP_DI_COMM_STATE)
			{
				dEXT_CH__TMP_DI_COMM_STATE->Get__DATA(ch_data);
				sCH__MON_COMM_STATE->Set__DATA(ch_data);
			}

			// ...
			{
				bool active__normal_speed = false;
				bool active__acceleration = false;

				if(bActive__TMP_DI_NORMAL_SPEED)
				{
					if(dEXT_CH__TMP_DI_NORMAL_SPEED->Check__DATA(STR__ON) > 0)			active__normal_speed = true;
				}
				if(bActive__TMP_DI_ACCELERATION)
				{
					if(dEXT_CH__TMP_DI_ACCELERATION->Check__DATA(STR__ON) > 0)			active__acceleration = true;
				}

				if((active__normal_speed)
				|| (active__acceleration))
				{
						 if(active__normal_speed)		sCH__MON_PUMP_STATE->Set__DATA(STR__NORMAL);
					else if(active__acceleration)		sCH__MON_PUMP_STATE->Set__DATA(STR__ACCEL);

					dCH__MON_PUMP_ON_SNS->Set__DATA(STR__ON);
				}
				else
				{
					sCH__MON_PUMP_STATE->Set__DATA(STR__STOP);

					dCH__MON_PUMP_ON_SNS->Set__DATA(STR__OFF);
				}
			}

			// ...
			{
				bool active__alarm_sts   = false;
				bool active__warning_sts = false;

				if(bActive__TMP_DI_ALARM_STATE)
				{
					if(dEXT_CH__TMP_DI_ALARM_STATE->Check__DATA(STR__ON) > 0)			active__alarm_sts = true;
				}
				if(bActive__TMP_DI_WARNING_STATE)
				{
					if(dEXT_CH__TMP_DI_WARNING_STATE->Check__DATA(STR__ON) > 0)			active__warning_sts = true;
				}

				if((active__alarm_sts)
				|| (active__warning_sts))
				{
						 if(active__alarm_sts)			sCH__MON_ERROR_STATE->Set__DATA(STR__ALARM);
					else if(active__warning_sts)		sCH__MON_ERROR_STATE->Set__DATA(STR__WARNING);
				}
				else
				{
					sCH__MON_ERROR_STATE->Set__DATA(STR__OK);
				}
			}

			if(bActive__TMP_AI_ROT_SPEED_RPM)
			{
				aEXT_CH__TMP_AI_ROT_SPEED_RPM->Get__DATA(ch_data);
				sCH__MON_ROT_SPEED_RPM_READ->Set__DATA(ch_data);
			}				

			if(bActive__TMP_AI_TEMPERATURE)
			{
				aEXT_CH__TMP_AI_TEMPERATURE->Get__DATA(ch_data);
				sCH__MON_PUMP_TEMPERATURE_READ->Set__DATA(ch_data);
			}
		}

		// SPEED CHECK ...
		if(bActive__TMP_AI_ROT_SPEED_RPM)
		{
			if(sCH__MON_PUMP_STATE->Check__DATA(STR__NORMAL) > 0)
			{
				dCH___MON_SPEED_CHECK_ACTIVE->Set__DATA(STR__ON);
			}
			else
			{
				dCH___MON_SPEED_CHECK_ACTIVE->Set__DATA(STR__OFF);
				
				dCH___MON_SPEED_STABLE_ACTIVE->Set__DATA(STR__OFF);
				dCH___MON_SPEED_ABORT_ACTIVE->Set__DATA(STR__OFF);
			}

			if(dCH___MON_SPEED_CHECK_ACTIVE->Check__DATA(STR__ON) > 0)
			{
				bool active__speed_error = false;

				ch_data = sCH__MON_ROT_SPEED_RPM_READ->Get__STRING();
				double cur__rot_speed = atof(ch_data);

				double cfg__high_speed = aCH__CFG_HIGH_LIMIT_SPEED_RPM->Get__VALUE();
				double cfg__low_speed  = aCH__CFG_LOW_LIMIT_SPEED_RPM->Get__VALUE();

				double cfg__err_sec = aCH__CFG_SPEED_ERR_CHECK_SEC->Get__VALUE();

				if(cur__rot_speed > cfg__high_speed)
				{
					cur__high_speed__err_sec += loop_sec;

					if(cur__high_speed__err_sec >= cfg__err_sec)
					{
						active__speed_error = true;

						// ...
						{
							int alm_id = ALID__HIGH_LIMIT_SPEED_RPM;
							CString alm_msg;
							CString alm_bff;
							CString r_act;
				
							alm_msg.Format(" The current speed is %.0f (rpm). \n", cur__rot_speed);
							alm_bff.Format(" The config high-limit speed is %.0f (rpm). \n", cfg__high_speed);
							alm_msg += alm_bff;
							alm_msg += "\n";
		
							alm_bff.Format(" The config error check time is %.1f (sec). \n", cfg__err_sec);
							alm_msg += alm_bff;
			
							p_alarm->Check__ALARM(alm_id, r_act);
							p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
						}
					}
				}
				else
				{
					cur__high_speed__err_sec = 0;	
				}

				if(cur__rot_speed < cfg__low_speed)
				{
					cur__low_speed__err_sec += loop_sec;

					if(cur__low_speed__err_sec >= cfg__err_sec)
					{
						active__speed_error = true;

						// ...
						{
							int alm_id = ALID__LOW_LIMIT_SPEED_RPM;
							CString alm_msg;
							CString alm_bff;
							CString r_act;

							alm_msg.Format(" The current speed is %.0f (rpm). \n", cur__rot_speed);
							alm_bff.Format(" The config low-limit speed is %.0f (rpm). \n", cfg__low_speed);
							alm_msg += alm_bff;
							alm_msg += "\n";
		
							alm_bff.Format(" The config error check time is %.1f (sec). \n", cfg__err_sec);
							alm_msg += alm_bff;

							p_alarm->Check__ALARM(alm_id, r_act);
							p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
						}
					}
				}
				else
				{
					cur__low_speed__err_sec = 0;	
				}

				if((cur__rot_speed < cfg__high_speed) && (cur__rot_speed > cfg__low_speed))
				{
					dCH__MON_ROT_SPEED_ERROR_ACTIVE->Set__DATA(STR__OFF);

					dCH___MON_SPEED_STABLE_ACTIVE->Set__DATA(STR__ON);
					dCH___MON_SPEED_ABORT_ACTIVE->Set__DATA(STR__OFF);
				}
				else if(active__speed_error)
				{
					dCH__MON_ROT_SPEED_ERROR_ACTIVE->Set__DATA(STR__ON);

					dCH___MON_SPEED_STABLE_ACTIVE->Set__DATA(STR__OFF);
					dCH___MON_SPEED_ABORT_ACTIVE->Set__DATA(STR__ON);
				}
				else
				{
					dCH__MON_ROT_SPEED_ERROR_ACTIVE->Set__DATA(STR__IDLE);	

					dCH___MON_SPEED_STABLE_ACTIVE->Set__DATA(STR__OFF);
					dCH___MON_SPEED_ABORT_ACTIVE->Set__DATA(STR__OFF);
				}
			}
			else
			{
				dCH__MON_ROT_SPEED_ERROR_ACTIVE->Set__DATA(STR__IDLE);
			}
		}
		else
		{
			dCH__MON_ROT_SPEED_ERROR_ACTIVE->Set__DATA(STR__IDLE);
		}

		// TEMPERATURE CHECK ...
		if(bActive__TMP_AI_TEMPERATURE)
		{
			ch_data = sCH__MON_PUMP_TEMPERATURE_READ->Get__STRING();
			double cur__pmp_temp = atof(ch_data);

			double cfg__high_temp = aCH__CFG_HIGH_LIMIT_TEMPERATURE->Get__VALUE();
			double cfg__err_sec = aCH__CFG_TEMPERATURE_ERR_CHECK_SEC->Get__VALUE();

			if(cur__pmp_temp > cfg__high_temp)
			{
				cur__high_temperature__err_sec += loop_sec;

				if(cur__high_temperature__err_sec >= cfg__err_sec)
				{
					cur__high_temperature__err_sec>= cfg__err_sec;
					dCH__MON_MOTOR_TEMPERATURE_ERROR_ACTIVE->Set__DATA(STR__ON);

					// ...
					{
						int alm_id = ALID__HIGH_LIMIT_TEMPERATURE;
						CString alm_msg;
						CString alm_bff;
						CString r_act;

						alm_msg.Format(" The current temperature is %.0f (C). \n", cur__pmp_temp);
						alm_bff.Format(" The config high-limit temperature is %.0f (C). \n", cfg__high_temp);
						alm_msg += alm_bff;
						alm_msg += "\n";

						alm_bff.Format(" The config error check time is %.1f (sec). \n", cfg__err_sec);
						alm_msg += alm_bff;

						p_alarm->Check__ALARM(alm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					}
				}
			}
			else
			{
				cur__high_temperature__err_sec = 0;
				dCH__MON_MOTOR_TEMPERATURE_ERROR_ACTIVE->Set__DATA(STR__OFF);
			}
		}
		else
		{
			dCH__MON_MOTOR_TEMPERATURE_ERROR_ACTIVE->Set__DATA(STR__IDLE);
		}

		// Error.Check ...
		if((dCH__MON_MOTOR_TEMPERATURE_ERROR_ACTIVE->Check__DATA(STR__ON) > 0)
		|| (sCH__MON_ERROR_STATE->Check__DATA(STR__OK) < 0))
		{
			dCH__MON_ERROR_ON_SNS->Set__DATA(STR__ON);
		}
		else
		{
			dCH__MON_ERROR_ON_SNS->Set__DATA(STR__OFF);
		}

		// PUMP ERROR ...
		if(dCH__MON_ERROR_ON_SNS->Check__DATA(STR__ON) > 0)
		{
			Fnc_Interlock__TMP_ISO(p_variable,p_alarm);

			// ...
			{
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				// ...
				{
					alm_bff.Format(" * %s <- %s \n", 
									sCH__MON_ERROR_STATE->Get__CHANNEL_NAME(),
									sCH__MON_ERROR_STATE->Get__STRING());
					alm_msg += alm_bff;
				}

				if(sCH__MON_ERROR_STATE->Check__DATA(STR__ALARM) > 0)
				{
					int alm_id = ALID__PUMP_ALARM_STATE;

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				}
				else if(sCH__MON_ERROR_STATE->Check__DATA(STR__WARNING) > 0)
				{
					int alm_id = ALID__PUMP_WARNING_STATE;

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				}
				
				if(sCH__MON_COMM_STATE->Check__DATA(STR__ONLINE) < 0)
				{
					int alm_id = ALID__TMP_OFFLINE;

					if(bActive__TMP_DI_COMM_STATE)
					{
						alm_bff.Format(" * %s <- %s \n",
										dEXT_CH__TMP_DI_COMM_STATE->Get__CHANNEL_NAME(),
										dEXT_CH__TMP_DI_COMM_STATE->Get__STRING());
						alm_msg += alm_bff;
					}

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				}

				// Alarm ...
				{
					int alm_id = ALID__TMP_ERROR_DETECTED;
					CString alm_msg;
					CString alm_bff;
					CString r_act;

					if(bActive__TMP_DI_ALARM_STATE)
					{
						alm_bff.Format(" * %s <- %s \n",
									    dEXT_CH__TMP_DI_ALARM_STATE->Get__CHANNEL_NAME(),
										dEXT_CH__TMP_DI_ALARM_STATE->Get__STRING());
						alm_msg += alm_bff;
					}
					if(bActive__TMP_DI_WARNING_STATE)
					{
						alm_bff.Format(" * %s <- %s \n",
										dEXT_CH__TMP_DI_WARNING_STATE->Get__CHANNEL_NAME(),
										dEXT_CH__TMP_DI_WARNING_STATE->Get__STRING());
						alm_msg += alm_bff;
					}

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				}
			}
		}

		// INTERLOCK.CHECK : FORELINE ...
		{
			bool active__err_sns = false;

			if(dCH___ACTIVE_INTERLOCK_SKIP_FORELINE_VAC->Check__DATA(STR__ON) < 0)
			{
				if(bActive__DI_FORELINE_VAC_SNS)
				{
					if(dEXT_CH__DI_FORELINE_VAC_SNS->Check__DATA(STR__ON) < 0)			active__err_sns = true;
				}
			}
			if(bActive__DI_BACKING_PUMP_ON)
			{
				if(dEXT_CH__DI_BACKING_PUMP_ON->Check__DATA(STR__ON) < 0)			active__err_sns = true;
			}

			if(active__err_sns)
			{
				double cfg_sec = aCH__CFG_DI_FORELINE_ERR_CHECK_SEC->Get__VALUE();

				cur__di_foreline__err_sec += loop_sec;
				if(cur__di_foreline__err_sec >= cfg_sec)
				{
					cur__di_foreline__err_sec = 0.0;

					// ...
					{
						int alm_id = ALID__FORLINE_PRESSURE_UNSTABLE_ALARM;
						CString alm_msg;
						CString alm_bff;
						CString r_act;

						if(bActive__DI_FORELINE_VAC_SNS)
						{
							alm_bff.Format(" * %s <- %s \n", 
											dEXT_CH__DI_FORELINE_VAC_SNS->Get__CHANNEL_NAME(),
											dEXT_CH__DI_FORELINE_VAC_SNS->Get__STRING());
							alm_msg += alm_bff;
						}
						if(bActive__DI_BACKING_PUMP_ON)
						{
							alm_bff.Format(" * %s <- %s \n", 
											dEXT_CH__DI_BACKING_PUMP_ON->Get__CHANNEL_NAME(),
											dEXT_CH__DI_BACKING_PUMP_ON->Get__STRING());
							alm_msg += alm_bff;
						}

						p_alarm->Check__ALARM(alm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					}

					Fnc_Interlock__TMP_ISO(p_variable,p_alarm);
				}
			}
			else
			{
				cur__di_foreline__err_sec = 0.0;
			}
		}

		// INTERLOCK.CHECK : PCW ...
		{
			bool active__err_sns = false;

			if(bActive__DI_PCW_ALARM)
			{
				if(dEXT_CH__DI_PCW_ALARM->Check__DATA(STR__ON) > 0)					active__err_sns = true;
			}
			if(bActive__DI_PCW_WATER_LEAK)
			{
				if(dEXT_CH__DI_PCW_WATER_LEAK->Check__DATA(STR__ON) > 0)			active__err_sns = true;
			}

			if(active__err_sns)
			{
				double cfg_sec = aCH__CFG_DI_PCW_ERR_CHECK_SEC->Get__VALUE();

				cur__di_pcw__err_sec += loop_sec;
				if(cur__di_pcw__err_sec >= cfg_sec)
				{
					cur__di_pcw__err_sec = 0.0;

					// ...
					{
						int alm_id = ALID__PCW_UNSTABLE_ALARM;
						CString alm_msg;
						CString alm_bff;
						CString r_act;

						if(bActive__DI_PCW_ALARM)
						{
							alm_bff.Format(" * %s <- %s \n", 
											dEXT_CH__DI_PCW_ALARM->Get__CHANNEL_NAME(),
											dEXT_CH__DI_PCW_ALARM->Get__STRING());
							alm_msg += alm_bff;
						}
						if(bActive__DI_PCW_WATER_LEAK)
						{
							alm_bff.Format(" * %s <- %s \n", 
											dEXT_CH__DI_PCW_WATER_LEAK->Get__CHANNEL_NAME(),
											dEXT_CH__DI_PCW_WATER_LEAK->Get__STRING());
							alm_msg += alm_bff;
						}

						p_alarm->Check__ALARM(alm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					}

					// Fnc_Interlock__TMP_OFF(p_variable,p_alarm);
				}
			}
			else
			{
				cur__di_pcw__err_sec = 0.0;
			}
		}

		// TMP Exhaust Valve Close ...
		{
			bool active__foreline_vlv_open = false;

			if(bActive__DO_TMP_EXHAUST_VALVE)
			{
				if(dEXT_CH__DO_TMP_EXHAUST_VALVE->Check__DATA(STR__OPEN) > 0)
				{
					active__foreline_vlv_open = true;
				}
			}

			if(active__foreline_vlv_open)
			{
				count_error__foreline_vlv_open = 0;

				// ...
				bool active__n2_purge_vlv_open = true;

				/*
				if(bActive__REF_MFC_TOTAL_FLOW)
				{
					double ref__mfc_total_flow = aEXT_CH__REF_MFC_TOTAL_FLOW->Get__VALUE();

					if(ref__mfc_total_flow > 0.0)			active__n2_purge_vlv_open = true;
					else									active__n2_purge_vlv_open = false;
				}
				*/

				if(bActive__DO_TMP_PURGE_VALVE)
				{
					if(active__n2_purge_vlv_open)			dEXT_CH__DO_TMP_PURGE_VALVE->Set__DATA(STR__OPEN);
					else									dEXT_CH__DO_TMP_PURGE_VALVE->Set__DATA(STR__CLOSE);
				}
			}
			else
			{
				if(bActive__DO_TMP_PURGE_VALVE)
				{
					dEXT_CH__DO_TMP_PURGE_VALVE->Set__DATA(STR__CLOSE);
				}

				if(bActive__VAT_USE)
				{
					ch_data = sEXT_CH__VAT_MON_POSITION->Get__STRING();
					double cur_pos = atof(ch_data);

					if(cur_pos > 0.0)
					{
						count_error__foreline_vlv_open++;

						if(count_error__foreline_vlv_open >= 10)
						{
							// ...
							{
								int alarm_id = ALID__FORELINE_NOT_OPEN__VAT_CLOSE;
								CString alm_msg;
								CString r_act;

								alm_msg.Format("Current VAT-Position is %.1f %%.", cur_pos);

								p_alarm->Check__ALARM(alarm_id, r_act);
								p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
							}

							pOBJ_CTRL__VAT->Abort__OBJECT();
							pOBJ_CTRL__VAT->Run__OBJECT("CLOSE");
						}
					}
				}

				// ...
			}
		}

		Update__TMP_LINE_READY(p_variable,p_alarm);
	}
}

int CObj__TMP_IO
::Update__TMP_LINE_READY(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int r_flag = Check__TMP_LINE_READY(p_variable, p_alarm);

	if(r_flag > 0)			dCH___MON_TMP_LINE_NOT_READY_ACTIVE->Set__DATA(STR__ON);
	else					dCH___MON_TMP_LINE_NOT_READY_ACTIVE->Set__DATA(STR__OFF);

	return 1;
}

