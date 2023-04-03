#include "StdAfx.h"
#include "CObj__CHM_IO.h"
#include "CObj__CHM_IO__ALID.h"
#include "CObj__CHM_IO__DEF.h"


// ...
int CObj__CHM_IO
::Mon__STATUS(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString pre__sim_pressure = "~";

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
		if(bActive__AI_FORELINE_GAUGE_mTORR)	aEXT_CH__AI_FORELINE_GAUGE_mTORR->Set__DATA("0.0");
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
			if(pre__sim_pressure.CompareNoCase(ch_data) != 0)
			{
				pre__sim_pressure = ch_data;

				for(i=0; i<iSIZE__PROC_GAUGE; i++)
				{
					if(bActive__AI_PROC_GAUGE_TORR_X[i])
					{
						aEXT_CH__AI_PROC_GAUGE_TORR_X[i]->Set__DATA(ch_data);
					}
					if(bActive__AI_PROC_GAUGE_mTORR_X[i])
					{
						CString str_mtorr;
						
						str_mtorr.Format("%.1f", atof(ch_data) * 1000.0);
						aEXT_CH__AI_PROC_GAUGE_mTORR_X[i]->Set__DATA(str_mtorr);
					}
				}

				if(bActive__AI_CHM_GAUGE_TORR)
					aEXT_CH__AI_CHM_GAUGE_TORR->Set__DATA(ch_data);
			}
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

				for(i=0; i<iSIZE__PROC_GAUGE; i++)
				{
					if(active__interlock_pressure)
					{
						dEXT_CH__DO_PROC_GAUGE_ISO_VLV_X[i]->Set__DATA(STR__CLOSE);
					}
					else
					{
						bool active__vlv_open = false;

						if(vac_flag > 0)
						{
							double cfg__limit_mtorr = aCH__CFG_PROCESS_MANOMETER_LIMIT_PRESSURE_mTORR_X[i]->Get__VALUE();

							if(cfg__limit_mtorr > 0.1)
							{
								if(i > 0)
								{
									double cur__press_mtorr = 0;
	
									if(bActive__AI_PROC_GAUGE_mTORR_X[i-1])
									{
										cur__press_mtorr = aEXT_CH__AI_PROC_GAUGE_mTORR_X[i-1]->Get__VALUE();
									}
									else if(bActive__AI_PROC_GAUGE_TORR_X[i-1])
									{
										double cur__press_torr = aEXT_CH__AI_PROC_GAUGE_TORR_X[i-1]->Get__VALUE();
										cur__press_mtorr = cur__press_torr * 1000.0;
									}

									if(cur__press_mtorr < cfg__limit_mtorr)			active__vlv_open = true;
								}
								else
								{
									if(bActive__AI_CHM_GAUGE_TORR)
									{
										double cur__chm_torr  = aEXT_CH__AI_CHM_GAUGE_TORR->Get__VALUE();
										double cur__chm_mtorr = cur__chm_torr * 1000.0;

										if(cur__chm_mtorr < cfg__limit_mtorr)		active__vlv_open = true;
									}
									else
									{
										active__vlv_open = true;
									}
								}
							}
							else
							{
								active__vlv_open = true;
							}
						}

						if(active__vlv_open)		dEXT_CH__DO_PROC_GAUGE_ISO_VLV_X[i]->Set__DATA(STR__OPEN);
						else						dEXT_CH__DO_PROC_GAUGE_ISO_VLV_X[i]->Set__DATA(STR__CLOSE);
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

				// ...
				double cur__press_mtorr = 300.0 * 1000.0;

				if(bActive__AI_CHM_GAUGE_TORR)
				{
					double cur__chm_torr = aEXT_CH__AI_CHM_GAUGE_TORR->Get__VALUE();
					cur__press_mtorr = cur__chm_torr * 1000.0;
				}

				for(i=0; i<iSIZE__PROC_GAUGE; i++)
				{
					if(dEXT_CH__DO_PROC_GAUGE_ISO_VLV_X[i]->Check__DATA(STR__OPEN) < 0)
					{
						continue;
					}

					// ...
					double cfg__max_mtorr   = aCH__CFG_PROCESS_MANOMETER_MAX_PRESSURE_mTORR_X[i]->Get__VALUE();			
					double cur__gauge_mtorr = cfg__max_mtorr;

					if(bActive__AI_PROC_GAUGE_mTORR_X[i])
					{
						cur__gauge_mtorr = aEXT_CH__AI_PROC_GAUGE_mTORR_X[i]->Get__VALUE();
					}
					else if(bActive__AI_PROC_GAUGE_TORR_X[i])
					{
						double cur__gauge_torr = aEXT_CH__AI_PROC_GAUGE_TORR_X[i]->Get__VALUE();
						cur__gauge_mtorr = cur__gauge_torr * 1000.0;
					}

					if(cur__gauge_mtorr < cfg__max_mtorr)
					{
						cur__press_mtorr = cur__gauge_mtorr;
					}
				}

				// ...
				{
					double cur__press_torr = cur__press_mtorr * 0.001;

					ch_data.Format("%.3f", cur__press_torr);
					sEXT_CH__CHM_PRESSURE_VALUE->Set__DATA(ch_data);

					ch_data.Format("%.1f", cur__press_mtorr);
					sEXT_CH__CHM_PRESSURE_mTORR->Set__DATA(ch_data);
				}
			}
			else if(atm_flag > 0)			
			{
				sEXT_CH__CHM_VAC_SNS->Set__DATA(STR__OFF);
				sEXT_CH__CHM_ATM_SNS->Set__DATA(STR__ON);

				// ...
				double cur_press = 760;
					
				if(bActive__AI_CHM_GAUGE_TORR)
				{
					cur_press = aEXT_CH__AI_CHM_GAUGE_TORR->Get__VALUE();
				}

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
					cur_press = aEXT_CH__AI_CHM_GAUGE_TORR->Get__VALUE();
				}

				// ...
				{
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
			double cur__foreline_torr = 300.0;

			if(bActive__AI_FORELINE_GAUGE_TORR)
			{
				cur__foreline_torr = aEXT_CH__AI_FORELINE_GAUGE_TORR->Get__VALUE();
			}
			if(bActive__AI_FORELINE_GAUGE_mTORR)
			{
				double cur__foreline_mtorr = aEXT_CH__AI_FORELINE_GAUGE_mTORR->Get__VALUE();
				cur__foreline_torr = cur__foreline_mtorr * 0.001;
			}
	
			ch_data.Format("%.3f", cur__foreline_torr);
			sEXT_CH__PMP_PRESSURE_VALUE->Set__DATA(ch_data);

			     if(cur__foreline_torr < 10.0)		sEXT_CH__PMP_PRESSURE_STATE->Set__DATA(STR__VAC);
			else if(cur__foreline_torr < 730)		sEXT_CH__PMP_PRESSURE_STATE->Set__DATA(STR__BTW);
			else									sEXT_CH__PMP_PRESSURE_STATE->Set__DATA(STR__ATM);

			if(cur__foreline_torr < 10.0)			sEXT_CH__PMP_VAC_SNS->Set__DATA(STR__ON);
			else									sEXT_CH__PMP_VAC_SNS->Set__DATA(STR__OFF);
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

		// MFC INFO ...
		if(iDATA__MFC_SIZE > 0)
		{
			// MFC - TOTAL SET FLOW ...
			{
				double cur__total_flow = 0.0;

				for(i=0; i<iDATA__MFC_SIZE; i++)
				{
					cur__total_flow += aEXT_CH__MFC_FLOW_SET_X[i]->Get__VALUE();
				}

					 if(cur__total_flow >= 1000.0)		ch_data.Format("%.0f", cur__total_flow);
				else if(cur__total_flow >= 100.0)		ch_data.Format("%.1f", cur__total_flow);
				else if(cur__total_flow >= 10.0)		ch_data.Format("%.2f", cur__total_flow);
				else									ch_data.Format("%.3f", cur__total_flow);

				sEXT_CH__MFC_TOTAL_FLOW_SET->Set__DATA(ch_data);
			}

			// Chamber Interlock ...
			if((sEXT_CH__CHM_VAC_SNS->Check__DATA(STR__ON) < 0)
			&& (dCH__CFG_ALL_MFC_CLOSE_WHEN_VAC_SNS_OFF->Check__DATA(STR__YES) > 0))
			{
				bool active__err_check = false;
				CString err_msg;
				CString err_bff;

				for(i=0; i<iDATA__MFC_SIZE; i++)
				{
					double cur__mfc_flow = aEXT_CH__MFC_FLOW_SET_X[i]->Get__VALUE();
					if(cur__mfc_flow > 0.001)
					{
						active__err_check = true;
					
						err_bff.Format(" MFC%02d \n", i+1);
						err_msg += err_bff;

						pOBJ__NFC_CTRL_X[i]->Call__OBJECT("CLOSE");
					}
				}

				if(active__err_check)
				{
					int alarm_id = ALID__ALL_MFC_CLOSE_WHEN_VAC_SNS_OFF;
					CString alm_msg;
					CString r_act;
					
					alm_msg  = "All of the MFCs below are closed. \n";
					alm_msg += err_msg;

					p_alarm->Check__ALARM(alarm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
				}
			}
		}

		// REVERSE_VALVE ...
		{
			for(i=0; i<iDATA__REVERSE_VALVE_SIZE; i++)
			{
				ch_data = dEXT_CH__REVERSE_VALVE_REF_X[i]->Get__STRING();

				if(ch_data.CompareNoCase(STR__OPEN) == 0)		dEXT_CH__REVERSE_VALVE_SUB_X[i]->Set__DATA(STR__CLOSE);
				else											dEXT_CH__REVERSE_VALVE_SUB_X[i]->Set__DATA(STR__OPEN);
			}
		}
	}

	return 1;
}
