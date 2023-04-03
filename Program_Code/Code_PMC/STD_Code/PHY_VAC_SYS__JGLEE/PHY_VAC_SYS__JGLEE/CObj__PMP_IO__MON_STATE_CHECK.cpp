#include "StdAfx.h"
#include "CObj__PMP_IO.h"


// ...
void CObj__PMP_IO
::Fnc__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	// Init ...
	{
		dCH__MON_PUMP_POWER_SNS->Set__DATA(STR__OFF);
		dCH__MON_VAC_ON_SNS->Set__DATA(STR__OFF);
	}

	// ...
	int loop_count = 0;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		loop_count++;
		if(loop_count > 10)			loop_count = 1;

		
		if(loop_count == 1)
		{
			int active__err_check = p_alarm->Check__Posted_Internal_Alarm(iLIST_ALID__PART);

			if(active__err_check > 0)		dCH__MON_PART_ERROR_ACTIVE->Set__DATA(STR__ON);
			else							dCH__MON_PART_ERROR_ACTIVE->Set__DATA(STR__OFF);
		}

		if(iPUMP__CTRL_TYPE == _PMP_CTRL_TYPE__MANUAL)
		{
			dCH__MON_PUMP_POWER_SNS->Set__DATA(STR__ON);
		}
		else
		{
			if(bActive__DI_PUMP_POWER_SNS)
			{
				if(dEXT_CH__DI_PUMP_POWER_SNS->Check__DATA(STR__ON) > 0)		dCH__MON_PUMP_POWER_SNS->Set__DATA(STR__ON);
				else															dCH__MON_PUMP_POWER_SNS->Set__DATA(STR__OFF);
			}
		}

		if(iPUMP__CTRL_TYPE == _PMP_CTRL_TYPE__OBJECT)
		{
			ch_data = dEXT_CH__PUMP_OBJ__MON_COMM_STATE->Get__STRING();
			sCH__MON_COMM_STATE->Set__DATA(ch_data);
		}
		else
		{
			sCH__MON_COMM_STATE->Set__DATA(STR__ONLINE);
		}

		// DI.VAC_SNS ...
		{
			bool active__vac_sns = true;

			if(bActive__DI_PUMP_VAC_SNS)
			{
				if(dEXT_CH__DI_PUMP_VAC_SNS->Check__DATA(STR__ON) < 0)			active__vac_sns = false;
			}

			if(active__vac_sns)
			{
				double cfg__limit_torr = aCH__CFG_PUMP_PRESSURE_HIGH_LIMIT->Get__VALUE();
				double cur__press_torr = cfg__limit_torr + 0.1;

				if(bActive__AI_PUMP_PRESSURE_TORR)
				{
					cur__press_torr = aEXT_CH__AI_PUMP_PRESSURE_TORR->Get__VALUE();
				}
				else if(bActive__AI_PUMP_PRESSURE_mTORR)
				{
					double cur__press_mtorr = aEXT_CH__AI_PUMP_PRESSURE_mTORR->Get__VALUE();
					cur__press_torr = cur__press_mtorr * 0.001;
				}
				else
				{
					if(dCH__MON_PUMP_POWER_SNS->Check__DATA(STR__ON) > 0)		cur__press_torr = 0.0;
					else														active__vac_sns = false;
				}

				if(cur__press_torr >= cfg__limit_torr)							active__vac_sns = false;

				// ...
				{
					ch_data.Format("%.3f", cur__press_torr);
					sCH__MON_PRESSURE_TORR->Set__DATA(ch_data);

					//
					double cur__press_mtorr = cur__press_torr * 1000.0;

					if(cur__press_torr > 1)			ch_data.Format("%.0f", cur__press_mtorr);
					else							ch_data.Format("%.1f", cur__press_mtorr);

					sCH__MON_PRESSURE_mTORR->Set__DATA(ch_data);
				}
			}

			if(active__vac_sns)			dCH__MON_VAC_ON_SNS->Set__DATA(STR__ON);
			else						dCH__MON_VAC_ON_SNS->Set__DATA(STR__OFF);
		}
	}
}

