#include "StdAfx.h"
#include "CObj__VAT_IO.h"
#include "CObj__VAT_IO__ALID.h"
#include "CObj__VAT_IO__DEF.h"

#include "CCommon_Utility.h"


// ...
int CObj__VAT_IO
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(iActive__SIM_MODE > 0)
	{
		if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__OBJ)
		{

		}
		else if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__HEXA)
		{
			sEXT_CH__SI_APC_STATE_HEXA->Set__DATA("80");
		}
		else
		{
			if(bActive__DI_APC_STATE_IO)		dEXT_CH__DI_APC_STATE_IO->Set__DATA(STR__NORMAL);
			if(bActive__SI_APC_STATE_IO)		sEXT_CH__SI_APC_STATE_IO->Set__DATA("80");
		}

		Fnc__PRESSURE(p_variable,p_alarm, 0.0);
	}

	// ...
	CCommon_Utility x_utility;
	CString ch_data;

	int loop_count = 0;

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		loop_count++;
		if(loop_count > 10)		loop_count = 1;


		// Range : Pressure ...
		if(loop_count == 1)
		{			
			aCH__CFG_PRESSURE_MIN_VALUE->Get__DATA(ch_data);
			double min_value = atof(ch_data);

			aCH__CFG_PRESSURE_MAX_VALUE->Get__DATA(ch_data);
			double max_value_torr = atof(ch_data);
			double max_value_mtorr = max_value_torr * 1000.0;

			ch_data.Format("%.1f", max_value_mtorr);
			sCH__CFG_PRESSURE_MAX_mTORR->Set__DATA(ch_data);

			aCH__CFG_PRESSURE_DEC_VALUE->Get__DATA(ch_data);
			int i_dec = atoi(ch_data);

			aCH__PARA_PRESSURE->Change__MIN_MAX_DEC(min_value,max_value_torr,i_dec);
			aCH__PARA_PRESSURE_mTORR->Change__MIN_MAX_DEC(min_value,max_value_mtorr,1);

			//
			if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__OBJ)
			{
				if(iPARA__PRESSURE_UNIT == _PRESSURE_UNIT__mTORR)
				{
					aEXT_CH__VAT__PARA_PRESSURE_VALUE->Change__MIN_MAX_DEC(min_value,max_value_mtorr, 1);
					aEXT_CH__VAT__CUR_PRESSURE_VALUE->Change__MIN_MAX_DEC(min_value,max_value_mtorr, 1);
				}
				else
				{
					aEXT_CH__VAT__PARA_PRESSURE_VALUE->Change__MIN_MAX_DEC(min_value,max_value_torr, i_dec);
					aEXT_CH__VAT__CUR_PRESSURE_VALUE->Change__MIN_MAX_DEC(min_value,max_value_torr, i_dec);
				}
			}
			else if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__IO)
			{
				aEXT_CH__AO_APC_SETPOINT_DATA->Change__MIN_MAX_DEC(0, 100, 1);

				if(iPARA__PRESSURE_UNIT == _PRESSURE_UNIT__mTORR)
				{
					aEXT_CH__AI_APC_PRESSURE->Change__MIN_MAX_DEC(min_value,max_value_mtorr, 1);
				}
				else
				{
					aEXT_CH__AI_APC_PRESSURE->Change__MIN_MAX_DEC(min_value,max_value_torr, i_dec);
				}
			}
		}

		if(loop_count == 1)
		{
			bool active__idle_check = false;
			bool active__proc_check = false;

			if(dCH__MON_IDLE_PRESSURE_CHECK_ACTIVE->Check__DATA(STR__ON) > 0)			active__idle_check = true;
			if(dCH__MON_PROC_PRESSURE_CHECK_ACTIVE->Check__DATA(STR__ON) > 0)			active__proc_check = true;

			if((active__idle_check)
			|| (active__proc_check))
			{
				bool active__idle_error = false;
				bool active__proc_error = false;

				if(active__idle_check)
				{
					if(dCH__MON_IDLE_PRESSURE_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)			active__idle_error = true;
				}
				if(active__proc_check)
				{
					if(dCH__MON_PROC_PRESSURE_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)			active__proc_error = true;
				}

				if((active__idle_error)
				|| (active__proc_error))
				{
					dCH__MON_VAT_PRESSURE_ABORT_ACTIVE->Set__DATA(STR__ON);
					dCH__MON_VAT_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__OFF);
				}
				else
				{
					dCH__MON_VAT_PRESSURE_ABORT_ACTIVE->Set__DATA(STR__OFF);

					if(active__proc_check)
					{
						if(dCH__MON_PROC_PRESSURE_STABLE_ACTIVE->Check__DATA(STR__ON) > 0)		
							dCH__MON_VAT_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__ON);
						else
							dCH__MON_VAT_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__OFF);
					}
					else if(active__idle_check)
					{
						if(dCH__MON_IDLE_PRESSURE_STABLE_ACTIVE->Check__DATA(STR__ON) > 0)
							dCH__MON_VAT_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__ON);
						else
							dCH__MON_VAT_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__OFF);
					}
				}

				dCH__MON_VAT_CTRL_ACTIVE->Set__DATA(STR__ON);
			}
			else
			{
				dCH__MON_VAT_CTRL_ACTIVE->Set__DATA(STR__OFF);
				dCH__MON_VAT_PRESSURE_ABORT_ACTIVE->Set__DATA(STR__OFF);
				dCH__MON_VAT_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__OFF);
			}

			//
			int active__err_check = p_alarm->Check__Posted_Internal_Alarm(iLIST_ALID__VAT);

			if(active__err_check > 0)		dCH__MON_VAT_ERROR_ACTIVE->Set__DATA(STR__ON);
			else							dCH__MON_VAT_ERROR_ACTIVE->Set__DATA(STR__OFF);
		}

		if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__OBJ)
		{
			// AI.PRESSURE ...
			{
				if(iActive__SIM_MODE > 0)
				{
					ch_data = sEXT_CH__SIM_PRESSURE_TORR->Get__STRING();

					if(iPARA__PRESSURE_UNIT == _PRESSURE_UNIT__mTORR)
					{
						double pressure_mtorr = atof(ch_data) * 1000.0;

						aEXT_CH__VAT__CUR_PRESSURE_VALUE->Set__VALUE(pressure_mtorr);
					}
					else
					{
						aEXT_CH__VAT__CUR_PRESSURE_VALUE->Set__DATA(ch_data);
					}
				}

				double cur_pressure = aEXT_CH__VAT__CUR_PRESSURE_VALUE->Get__VALUE();

				if(iPARA__PRESSURE_UNIT == _PRESSURE_UNIT__mTORR)
				{
					cur_pressure = cur_pressure / 1000.0;
				}

				ch_data.Format("%.3f", cur_pressure);
				sCH__MON_PRESSURE_TORR->Set__DATA(ch_data);

				ch_data.Format("%.1f", cur_pressure * 1000.0);
				sCH__MON_PRESSURE_mTORR->Set__DATA(ch_data);
			}
			// AI.POSITION ...
			{
				aEXT_CH__VAT__CUR_POSITION_PER->Get__DATA(ch_data);
				sCH__MON_POSITION->Set__DATA(ch_data);
			}
		}
		else if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__HEXA)
		{
			CString str_hexa;
			int i_hexa;

			// MON SET.DATA ...
			{
				str_hexa = sEXT_CH__SO_APC_CTRL_MODE->Get__STRING();
				i_hexa = x_utility.Get__Hexa_From_String(str_hexa);

					 if(i_hexa == 0)			sCH__MON_DO_APC_CTRL_MODE->Set__DATA(STR__CONTROL);
				else if(i_hexa == 1)			sCH__MON_DO_APC_CTRL_MODE->Set__DATA(STR__CLOSE);
				else if(i_hexa == 2)			sCH__MON_DO_APC_CTRL_MODE->Set__DATA(STR__OPEN);
				else							sCH__MON_DO_APC_CTRL_MODE->Set__DATA(STR__UNKNOWN);

				//
				str_hexa = sEXT_CH__SO_APC_SETPOINT_DATA->Get__STRING();
				i_hexa = x_utility.Get__Hexa_From_String(str_hexa);
				
				ch_data.Format("%.2f", i_hexa * (100.0 / iLINK_HEXA__MAX_VALUE));
				sCH__MON_AO_APC_SETPOINT_DATA->Set__DATA(ch_data);

				//
				str_hexa = sEXT_CH__SO_APC_SETPOINT_TYPE->Get__STRING();
				i_hexa = x_utility.Get__Hexa_From_String(str_hexa);

					 if(i_hexa == 0)			sCH__MON_DO_APC_SETPOINT_TYPE->Set__DATA(STR__PRESSURE);
				else if(i_hexa == 1)			sCH__MON_DO_APC_SETPOINT_TYPE->Set__DATA(STR__POSITION);
				else							sCH__MON_DO_APC_SETPOINT_TYPE->Set__DATA(STR__UNKNOWN);
			}

			// SI.STATE ...
			{
				str_hexa = sEXT_CH__SI_APC_STATE_HEXA->Get__STRING();
				i_hexa = x_utility.Get__Hexa_From_String(str_hexa);

					 if(i_hexa == 0x80)			sCH__MON_DI_APC_STATE->Set__DATA(STR__NORMAL);
				else if(i_hexa == 0xC0)			sCH__MON_DI_APC_STATE->Set__DATA(STR__WARNING);
				else if(i_hexa == 0x84)			sCH__MON_DI_APC_STATE->Set__DATA(STR__ALARM);
				else							sCH__MON_DI_APC_STATE->Set__DATA(STR__UNKNOWN);
			}
			// SI.PRESSURE ...
			{
				double cfg_max = aCH__CFG_PRESSURE_MAX_VALUE->Get__VALUE();

				if(iActive__SIM_MODE > 0)
				{
					UNION_2_BYTE__UINT x_data;

					unsigned char uch_data[101];
					memset(uch_data, 0, 101);

					ch_data = sEXT_CH__SIM_PRESSURE_TORR->Get__STRING();
					double cur_value = atof(ch_data);

					i_hexa = (cur_value / cfg_max) * iLINK_HEXA__MAX_VALUE;
					x_data.uiDATA = 0x0ffff & i_hexa;;
					
					ch_data.Format("%02X %02X", (0x0ff & x_data.cBYTE[0]), (0x0ff & x_data.cBYTE[1]));
					sEXT_CH__SI_APC_PRESSURE->Set__DATA(ch_data);
				}

				// ...
				UNION_2_BYTE__UINT m_pressure;

				// ...
				{
					byte uch_data[21];
					memset(uch_data, 0, 21);

					str_hexa = sEXT_CH__SI_APC_PRESSURE->Get__STRING();

					// ...
					{
						CStringArray l_data;
						x_utility.Get__StringArrray_From_String(str_hexa, " ", l_data);

						int i_limit = l_data.GetSize();
						if(i_limit > 20)		i_limit = 20;

						for(int i=0; i<i_limit; i++)
						{
							uch_data[i] = 0x0ff & x_utility.Get__Hexa_From_String(l_data[i]);
						}
					}

					m_pressure.cBYTE[0] = 0x0ff & uch_data[0];
					m_pressure.cBYTE[1] = 0x0ff & uch_data[1];
				}

				double cur_pressure = (cfg_max * m_pressure.uiDATA) / iLINK_HEXA__MAX_VALUE;

				ch_data.Format("%.3f", cur_pressure);
				sCH__MON_PRESSURE_TORR->Set__DATA(ch_data);

				ch_data.Format("%.1f", cur_pressure * 1000.0);
				sCH__MON_PRESSURE_mTORR->Set__DATA(ch_data);
			}
			// SI.POSITION ...
			{
				UNION_2_BYTE__UINT m_pos;

				// ...
				{
					byte uch_data[21];
					memset(uch_data, 0, 21);

					str_hexa = sEXT_CH__SI_APC_POSITION->Get__STRING();

					// ...
					{
						CStringArray l_data;
						x_utility.Get__StringArrray_From_String(str_hexa, " ", l_data);

						int i_limit = l_data.GetSize();
						if(i_limit > 20)		i_limit = 20;

						for(int i=0; i<i_limit; i++)
						{
							uch_data[i] = 0x0ff & x_utility.Get__Hexa_From_String(l_data[i]);
						}
					}

					m_pos.cBYTE[0] = 0x0ff & uch_data[0];
					m_pos.cBYTE[1] = 0x0ff & uch_data[1];
				}

				double cur_pos = (100.0 * m_pos.uiDATA) / iLINK_HEXA__MAX_VALUE;

				ch_data.Format("%.1f", cur_pos);
				sCH__MON_POSITION->Set__DATA(ch_data);
			}
		}
		else
		{
			// MON SET.DATA ...
			{
				dEXT_CH__DO_APC_CTRL_MODE->Get__DATA(ch_data);
				sCH__MON_DO_APC_CTRL_MODE->Set__DATA(ch_data);

				aEXT_CH__AO_APC_SETPOINT_DATA->Get__DATA(ch_data);
				sCH__MON_AO_APC_SETPOINT_DATA->Set__DATA(ch_data);

				dEXT_CH__DO_APC_SETPOINT_TYPE->Get__DATA(ch_data);
				sCH__MON_DO_APC_SETPOINT_TYPE->Set__DATA(ch_data);
			}

			// AI.PRESSURE ...
			{
				if(iActive__SIM_MODE > 0)
				{
					ch_data = sEXT_CH__SIM_PRESSURE_TORR->Get__STRING();
					
					if(iPARA__PRESSURE_UNIT == _PRESSURE_UNIT__mTORR)
					{
						double pressure_mtorr = atof(ch_data) * 1000.0;

						aEXT_CH__AI_APC_PRESSURE->Set__VALUE(pressure_mtorr);
					}
					else
					{
						aEXT_CH__AI_APC_PRESSURE->Set__DATA(ch_data);
					}
				}

				double cur_pressure = aEXT_CH__AI_APC_PRESSURE->Get__VALUE();

				if(iPARA__PRESSURE_UNIT == _PRESSURE_UNIT__mTORR)
				{
					cur_pressure = cur_pressure / 1000.0;
				}

				ch_data.Format("%.3f", cur_pressure);
				sCH__MON_PRESSURE_TORR->Set__DATA(ch_data);

				ch_data.Format("%.1f", cur_pressure * 1000.0);
				sCH__MON_PRESSURE_mTORR->Set__DATA(ch_data);
			}
			// AI.POSITION ...
			{
				aEXT_CH__AI_APC_POSITION->Get__DATA(ch_data);
				sCH__MON_POSITION->Set__DATA(ch_data);
			}

			if(bActive__DI_APC_STATE_IO)
			{
				dEXT_CH__DI_APC_STATE_IO->Get__DATA(ch_data);
				sCH__MON_DI_APC_STATE->Set__DATA(ch_data);
			}
			else if(bActive__SI_APC_STATE_IO)
			{
				sEXT_CH__SI_APC_STATE_IO->Get__DATA(ch_data);
				int i_data = x_utility.Get__Hexa_From_String(ch_data);

					 if(i_data == 0x80)			sCH__MON_DI_APC_STATE->Set__DATA(STR__NORMAL);
				else if(i_data == 0xC0)			sCH__MON_DI_APC_STATE->Set__DATA(STR__WARNING);
				else if(i_data == 0x84)			sCH__MON_DI_APC_STATE->Set__DATA(STR__ALARM);
				else							sCH__MON_DI_APC_STATE->Set__DATA(STR__UNKNOWN);
			}

			if(bActive__DI_APC_VLV_CLOSE)
			{
				dEXT_CH__DI_APC_VLV_CLOSE->Get__DATA(ch_data);
				sCH__MON_DI_APC_VLV_CLOSE->Set__DATA(ch_data);
			}
			if(bActive__DI_APC_VLV_OPEN)
			{
				dEXT_CH__DI_APC_VLV_OPEN->Get__DATA(ch_data);
				sCH__MON_DI_APC_VLV_OPEN->Set__DATA(ch_data);
			}
			if(bActive__DI_APC_VLV_STATE)
			{
				dEXT_CH__DI_APC_VLV_STATE->Get__DATA(ch_data);
				sCH__MON_DI_APC_VLV_STATE->Set__DATA(ch_data);
			}
		}

		// High Limit Interlock ...
		{
			bool active__high_limit = false;
			CString err_msg;
			CString err_bff;

			if(dCH__CFG_HIGH_LIMIT_ATM_SENSOR_APPLY->Check__DATA(STR__YES) > 0)
			{
				if(bActive__DI_ATM_SENSOR)
				{
					if(dEXT_CH__DI_ATM_SENSOR->Check__DATA(STR__ON) > 0)
					{
						active__high_limit = true;

						err_bff.Format("ATM Sensor가 감지된 상태입니다. \n");
						err_msg += err_bff;

						err_bff.Format(" * %s <- %s \n", 
										dEXT_CH__DI_ATM_SENSOR->Get__CHANNEL_NAME(),
										dEXT_CH__DI_ATM_SENSOR->Get__STRING());
						err_msg += err_bff;
						err_msg += "\n";
					}
				}			
			}

			if(dCH__CFG_HIGH_LIMIT_VAC_SENSOR_APPLY->Check__DATA(STR__YES) > 0)
			{
				if(bActive__DI_VAC_SENSOR)
				{
					if(dEXT_CH__DI_VAC_SENSOR->Check__DATA(STR__ON) < 0)
					{
						active__high_limit = true;

						err_bff.Format("VAC Sensor가 감지되지 않고 있습니다. \n");
						err_msg += err_bff;

						err_bff.Format(" * %s <- %s \n", 
										dEXT_CH__DI_VAC_SENSOR->Get__CHANNEL_NAME(),
										dEXT_CH__DI_VAC_SENSOR->Get__STRING());
						err_msg += err_bff;
						err_msg += "\n";
					}
				}
			}

			if(dCH__CFG_HIGH_LIMIT_CHM_PRESSURE_APPLY->Check__DATA(STR__YES) > 0)
			{
				if(bActive__AI_CHM_PRESSURE_TORR)
				{
					double cfg__high_limit   = aCH__CFG_HIGH_LIMIT_CHM_PRESSURE_TORR->Get__VALUE();
					double cur__chm_pressure = aEXT_CH__AI_CHM_PRESSURE_TORR->Get__VALUE();

					if(cur__chm_pressure >= cfg__high_limit)
					{
						active__high_limit = true;

						err_bff.Format("현재 Chamber 압력이 %.3f torr 입니다.\n", cur__chm_pressure);
						err_msg += err_bff;

						err_bff.Format("Config에 설정된 high-limit pressure 는 %.3f torr 입니다.\n", cfg__high_limit);
						err_msg += err_bff;
						err_msg += "\n";
					}
				}
			}

			if(active__high_limit)
			{
				ch_data = sCH__MON_POSITION->Get__STRING();
				double cur_pos = atof(ch_data);

				if(cur_pos > 0.1)
				{
					// ...
					{
						int alarm_id = ALID__HIGH_LIMIT_CHM_PRESSURE_INTERLOCK;
						CString r_act;

						p_alarm->Check__ALARM(alarm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alarm_id, err_msg);
					}

					Call__CLOSE(p_variable, p_alarm);
				}
			}
		}

		// ...
	}

	return 1;
}

