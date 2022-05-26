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

		aCH__MON_PUMP_RPM_VALUE->Set__DATA("0");
	}

	if(iActive__SIM_MODE > 0)
	{
		if(bActive__DI_PCW_ALARM)			dEXT_CH__DI_PCW_ALARM->Set__DATA(STR__OFF);
		if(bActive__DI_PCW_WATER_LEAK)		dEXT_CH__DI_PCW_WATER_LEAK->Set__DATA(STR__OFF);
	}

	// ...
	double loop_sec = 0.1;
	double cur__di_foreline__err_sec = 0;
	double cur__di_pcw__err_sec = 0;

	int loop_count = 0;

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
					else																active__normal_speed = false;
				}
				if(bActive__TMP_DI_ACCELERATION)
				{
					if(dEXT_CH__TMP_DI_ACCELERATION->Check__DATA(STR__ON) > 0)			active__acceleration = true;
					else																active__acceleration = false;
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
					else																active__alarm_sts = false;
				}
				if(bActive__TMP_DI_WARNING_STATE)
				{
					if(dEXT_CH__TMP_DI_WARNING_STATE->Check__DATA(STR__ON) > 0)			active__warning_sts = true;
					else																active__warning_sts = false;
				}

				if((active__alarm_sts)
				|| (active__warning_sts))
				{
						 if(active__alarm_sts)			sCH__MON_ERROR_STATE->Set__DATA(STR__ALARM);
					else if(active__warning_sts)		sCH__MON_ERROR_STATE->Set__DATA(STR__WARNING);

					dCH__MON_ERROR_ON_SNS->Set__DATA(STR__ON);
				}
				else
				{
					sCH__MON_ERROR_STATE->Set__DATA(STR__OK);

					dCH__MON_ERROR_ON_SNS->Set__DATA(STR__OFF);
				}
			}

			if(bActive__TMP_AI_ROT_RPM)
			{
				aEXT_CH__TMP_AI_ROT_RPM->Get__DATA(ch_data);
				aCH__MON_PUMP_RPM_VALUE->Set__DATA(ch_data);
			}				
		}


		// PUMP ERROR ...
		if(dCH__MON_ERROR_ON_SNS->Check__DATA(STR__ON) > 0)
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
		}

		// INTERLOCK.CHECK : FORELINE ...
		{
			bool active__err_sns = false;

			if(bActive__DI_FORELINE_VAC_SNS)
			{
				if(dEXT_CH__DI_FORELINE_VAC_SNS->Check__DATA(STR__ON) < 0)			active__err_sns = true;
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

					if(dCH__MON_PUMP_ON_SNS->Check__DATA(STR__ON) > 0)
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

						Call__OFF(p_variable, p_alarm, false);
					}
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

					if(dCH__MON_PUMP_ON_SNS->Check__DATA(STR__ON) > 0)
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

						Call__OFF(p_variable, p_alarm, false);
					}
				}
			}
			else
			{
				cur__di_pcw__err_sec = 0.0;
			}
		}

		// TMP Exhaust Valve Close ...
		if(bActive__FORELINE_VLV_CHECK)
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
				if(bActive__DO_TMP_PURGE_VALVE)
				{
					dEXT_CH__DO_TMP_PURGE_VALVE->Set__DATA(STR__OPEN);
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

					if(cur_pos > 0.1)		pOBJ_CTRL__VAT->Call__OBJECT("CLOSE");
				}
			}
		}

		// ...
	}
}

