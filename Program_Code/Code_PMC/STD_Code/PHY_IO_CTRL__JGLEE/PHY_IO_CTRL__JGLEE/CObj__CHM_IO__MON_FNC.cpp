#include "StdAfx.h"
#include "CObj__CHM_IO.h"
#include "CObj__CHM_IO__ALID.h"
#include "CObj__CHM_IO__DEF.h"


// ...
int CObj__CHM_IO
::Mon__STATUS(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	bool active__btw_check = false;

	CString ch_data;
	int i;

	if(iActive__SIM_MODE > 0)
	{
		dEXT_CH__DI_VAC_SNS->Set__DATA(STR__ON);
		dEXT_CH__DI_ATM_SNS->Set__DATA(STR__OFF);

		//
		if(bActive__DI_SLOT_VLV_OPEN)			dEXT_CH__DI_SLOT_VLV_OPEN->Set__DATA(STR__OFF);
		if(bActive__DI_SLOT_VLV_CLOSE)			dEXT_CH__DI_SLOT_VLV_CLOSE->Set__DATA(STR__ON);

		//
		if(bActive__AI_FORELINE_GAUGE_TORR)		aEXT_CH__AI_FORELINE_GAUGE_TORR->Set__DATA("0.0");
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		// ...
		int interlock__do_iso_vlv = 1;

		if((dEXT_CH__CFG_INTERLOCK_USE_MODE->Check__DATA(STR__DISABLE)     > 0)
		|| (dEXT_CH__CFG_INTERLOCK_USE_MODE->Check__DATA(STR__ALL_DISABLE) > 0))
		{
			interlock__do_iso_vlv = -1;

			if(dEXT_CH__CFG_INTERLOCK_USE_MODE->Check__DATA(STR__ALL_DISABLE) > 0)
			{
				int alm_id = ALID__MONITORING_INTERLOCK__DISABLE;
				CString r_act;

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM(alm_id);
			}
		}
		else if(dEXT_CH__CFG_INTERLOCK_USE_MODE->Check__DATA(STR__CONTROL) > 0)
		{
			if(dEXT_CH__CFG_INTERLOCK_USE__CHM_MANOMETER_ISO->Check__DATA(STR__DISABLE) > 0)
			{
				interlock__do_iso_vlv = -1;
			}
		}

		if(iActive__SIM_MODE > 0)
		{
			ch_data = sEXT_CH__SIM_PRESSURE_TORR->Get__STRING();

			for(i=0; i<iSIZE__PRC_GUAGE; i++)
			{
				aEXT_CH__AI_PRC_GAUGE_TORR_X[i]->Set__DATA(ch_data);
			}

			if(bActive__AI_CHM_GAUGE_TORR)
				aEXT_CH__AI_CHM_GAUGE_TORR->Set__DATA(ch_data);
		}

		// SLOT.VLV SNS ...
		if((bActive__DI_SLOT_VLV_OPEN)
		|| (bActive__DI_SLOT_VLV_CLOSE))
		{
			int check_open  = 0;
			int check_close = 0;

			if(bActive__DI_SLOT_VLV_OPEN)
			{
				if(dEXT_CH__DI_SLOT_VLV_OPEN->Check__DATA(STR__ON) > 0)			check_open =  1;
				else															check_open = -1;
			}
			if(bActive__DI_SLOT_VLV_CLOSE)
			{
				if(dEXT_CH__DI_SLOT_VLV_CLOSE->Check__DATA(STR__ON) > 0)		check_close  = 1;
				else															check_close = -1;
			}

			if((check_close >= 0) && (check_open <= 0))
			{
				dEXT_CH__CHM_SLOT_VLV_STATE->Set__DATA(STR__CLOSE);
			}
			else if((check_close <= 0) && (check_open >= 0))
			{
				dEXT_CH__CHM_SLOT_VLV_STATE->Set__DATA(STR__OPEN);
			}
			else
			{
				dEXT_CH__CHM_SLOT_VLV_STATE->Set__DATA(STR__UNKNOWN);
			}
		}

		// ...
		{
			int vac_flag = -1;
			int atm_flag = -1;

			if((dEXT_CH__DI_VAC_SNS->Check__DATA(STR__ON)  > 0)
			&& (dEXT_CH__DI_ATM_SNS->Check__DATA(STR__OFF) > 0))
			{
				vac_flag = 1;
			}
			else if((dEXT_CH__DI_VAC_SNS->Check__DATA(STR__OFF)  > 0)
				 && (dEXT_CH__DI_ATM_SNS->Check__DATA(STR__ON)   > 0))
			{
				atm_flag = 1;
			}

			if(interlock__do_iso_vlv > 0)
			{
				bool active__interlock_pressure = false;

				if(bActive__AI_CHM_GAUGE_TORR)
				{
					double cur__chm_press = aEXT_CH__AI_CHM_GAUGE_TORR->Get__VALUE();
					double cfg__interlock_press = aCH__CFG_INTERLOCK_HIGH_LIMIT_PRESSURE->Get__VALUE();

					if(cur__chm_press >= cfg__interlock_press)		active__interlock_pressure = true;
				}

				for(i=0; i<iSIZE__PRC_GUAGE; i++)
				{
					if(active__interlock_pressure)
					{
						dEXT_CH__DO_PRC_GAUGE_ISO_VLV_X[i]->Set__DATA(STR__CLOSE);
					}
					else
					{
						if(vac_flag > 0)		dEXT_CH__DO_PRC_GAUGE_ISO_VLV_X[i]->Set__DATA(STR__OPEN);
						else					dEXT_CH__DO_PRC_GAUGE_ISO_VLV_X[i]->Set__DATA(STR__CLOSE);
					}
				}
			}

			if(bActive__DO_CHM_CHECK_VLV)
			{
				if(vac_flag > 0)			dEXT_CH__DO_CHM_CHECK_VLV->Set__DATA(STR__CLOSE);
				else						dEXT_CH__DO_CHM_CHECK_VLV->Set__DATA(STR__OPEN);
			}

			if(vac_flag > 0)			
			{
				sEXT_CH__CHM_VAC_SNS->Set__DATA(STR__ON);
				sEXT_CH__CHM_ATM_SNS->Set__DATA(STR__OFF);

				active__btw_check = false;

				// ...
				double cur_press = 300.0;

				for(i=0; i<iSIZE__PRC_GUAGE; i++)
				{
					if(dEXT_CH__DO_PRC_GAUGE_ISO_VLV_X[i]->Check__DATA(STR__OPEN) < 0)
					{
						if(bActive__AI_CHM_GAUGE_TORR)		cur_press = aEXT_CH__AI_CHM_GAUGE_TORR->Get__VALUE();

						continue;
					}

					// ...
					double cfg_max_torr = aCH__CFG_PROCESS_MANOMETER_MAX_PRESSURE_mTORR_X[i]->Get__VALUE();
					cfg_max_torr = cfg_max_torr * 0.001;

					double cur__prc_press = aEXT_CH__AI_PRC_GAUGE_TORR_X[i]->Get__VALUE();
					double cur__chm_press = 500.0;

					if(bActive__AI_CHM_GAUGE_TORR)			cur__chm_press = aEXT_CH__AI_CHM_GAUGE_TORR->Get__VALUE();
						
					if(cur__prc_press < cfg_max_torr)		cur_press = cur__prc_press;
					else									cur_press = cur__chm_press;

					break;
				}

				// ...
				{
					ch_data.Format("%.3f", cur_press);
					sEXT_CH__CHM_PRESSURE_VALUE->Set__DATA(ch_data);

					ch_data.Format("%.1f", cur_press*1000.0);
					sEXT_CH__CHM_PRESSURE_mTORR->Set__DATA(ch_data);
				}
			}
			else if(atm_flag > 0)			
			{
				sEXT_CH__CHM_VAC_SNS->Set__DATA(STR__OFF);
				sEXT_CH__CHM_ATM_SNS->Set__DATA(STR__ON);

				active__btw_check = false;

				// ...
				double cur_press = 7600;
					
				if(bActive__AI_CHM_GAUGE_TORR)
					cur_press = aEXT_CH__AI_CHM_GAUGE_TORR->Get__VALUE();

				// ...
				{
					ch_data.Format("%.1f", cur_press);
					sEXT_CH__CHM_PRESSURE_VALUE->Set__DATA(ch_data);

					ch_data.Format("%.1f", cur_press*1000.0);
					sEXT_CH__CHM_PRESSURE_mTORR->Set__DATA(ch_data);
				}
			}
			else
			{
				sEXT_CH__CHM_VAC_SNS->Set__DATA(STR__OFF);
				sEXT_CH__CHM_ATM_SNS->Set__DATA(STR__OFF);

				// ...
				double cur_press = 550.0;

				if(bActive__AI_CHM_GAUGE_TORR)
				{
					active__btw_check = false;
					
					cur_press = aEXT_CH__AI_CHM_GAUGE_TORR->Get__VALUE();
				}

				if(!active__btw_check)
				{
					active__btw_check = true;

					ch_data.Format("%.1f", cur_press);
					sEXT_CH__CHM_PRESSURE_VALUE->Set__DATA(ch_data);

					ch_data.Format("%.1f", cur_press*1000.0);
					sEXT_CH__CHM_PRESSURE_mTORR->Set__DATA(ch_data);
				}
			}

			// ...
			{
				ch_data = sEXT_CH__CHM_PRESSURE_VALUE->Get__STRING();
				double cur__press_torr = atof(ch_data);

				ch_data = sEXT_CH__CHM_PRESSURE_mTORR->Get__STRING();
				double cur__press_mtorr = atof(ch_data);

					 if(cur__press_torr <  0.01)		ch_data.Format("%1.2f mtorr", cur__press_mtorr);
				else if(cur__press_torr <   0.1)		ch_data.Format("%2.1f mtorr", cur__press_mtorr);
				else if(cur__press_torr <   1.0)		ch_data.Format("%3.0f mtorr", cur__press_mtorr);
				else if(cur__press_torr <  10.0)		ch_data.Format("%.3f torr", cur__press_torr);
				else if(cur__press_torr < 100.0)		ch_data.Format("%.2f torr", cur__press_torr);
				else									ch_data.Format("%.1f torr", cur__press_torr);

				sCH__MON_CHM_PRESSURE_DISPLAY->Set__DATA(ch_data);
			}
		}

		// ...
		{
			if(bActive__AI_FORELINE_GAUGE_TORR)			aEXT_CH__AI_FORELINE_GAUGE_TORR->Get__DATA(ch_data);
			else										ch_data = "0.000";
			
			sEXT_CH__PMP_PRESSURE_VALUE->Set__DATA(ch_data);
			double cur_pmp_press = atof(ch_data);

			     if(cur_pmp_press < 10.0)		sEXT_CH__PMP_PRESSURE_STATE->Set__DATA("VAC");
			else if(cur_pmp_press < 730)		sEXT_CH__PMP_PRESSURE_STATE->Set__DATA("BTW");
			else								sEXT_CH__PMP_PRESSURE_STATE->Set__DATA("ATM");

			if(cur_pmp_press < 10.0)			sEXT_CH__PMP_VAC_SNS->Set__DATA(STR__ON);
			else								sEXT_CH__PMP_VAC_SNS->Set__DATA(STR__OFF);
		}

		// RF INFO ...
		if(iDATA__RF_SIZE > 0)
		{
			bool active__rf_on = false;

			for(i=0; i<iDATA__RF_SIZE; i++)
			{
				if(dEXT_CH__RF_ON_STATE_X[i]->Check__DATA(STR__ON) < 0)			continue;
					
				active__rf_on = true;
				break;
			}

			if(active__rf_on)			sEXT_CH__RF_TOTAL_ON_STATE->Set__DATA(STR__ON);
			else						sEXT_CH__RF_TOTAL_ON_STATE->Set__DATA(STR__OFF);
		}
		else
		{
			sEXT_CH__RF_TOTAL_ON_STATE->Set__DATA(STR__OFF);
		}

		// ...
	}

	return 1;
}
