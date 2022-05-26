#include "StdAfx.h"
#include "CObj__VAT_IO.h"
#include "CObj__VAT_IO__ALID.h"
#include "CObj__VAT_IO__DEF.h"


// ...
int CObj__VAT_IO
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	if(iActive__SIM_MODE > 0)
	{
		sCH__MON_SET_PRESSURE->Set__DATA("0");

		if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__OBJ)
		{

		}
		else
		{
			dEXT_CH__DI_APC_STATE->Set__DATA(STR__NORMAL);
		}
	}

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
			double max_value = atof(ch_data);

			ch_data.Format("%.0f", max_value * 1000.0);
			sCH__CFG_PRESSURE_MAX_mTORR->Set__DATA(ch_data);

			aCH__CFG_PRESSURE_DEC_VALUE->Get__DATA(ch_data);
			int i_dec = atoi(ch_data);

			aCH__PARA_PRESSURE->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
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

			// DI.APC_STATE ...
			{
				dEXT_CH__DI_APC_STATE->Get__DATA(ch_data);
				sCH__MON_DI_APC_STATE->Set__DATA(ch_data);
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

		// ...
	}

	return 1;
}

