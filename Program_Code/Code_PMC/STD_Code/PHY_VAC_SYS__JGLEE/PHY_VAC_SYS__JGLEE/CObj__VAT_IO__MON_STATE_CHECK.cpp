#include "StdAfx.h"
#include "CObj__VAT_IO.h"
#include "CObj__VAT_IO__ALID.h"


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


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		// Range : Pressure ...
		{			
			aCH__CFG_PRESSURE_MIN_VALUE->Get__DATA(ch_data);
			double min_value = atof(ch_data);

			aCH__CFG_PRESSURE_MAX_VALUE->Get__DATA(ch_data);
			double max_value = atof(ch_data);

			aCH__CFG_PRESSURE_DEC_VALUE->Get__DATA(ch_data);
			int i_dec = atoi(ch_data);

			aCH__PARA_PRESSURE->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
		}

		if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__OBJ)
		{
			// AI.PRESSURE ...
			{
				if(iActive__SIM_MODE > 0)
				{
					ch_data = sEXT_CH__SIM_PRESSURE_TORR->Get__STRING();
					aEXT_CH__VAT__CUR_PRESSURE_TORR->Set__DATA(ch_data);
				}

				double cur_pressure = aEXT_CH__VAT__CUR_PRESSURE_TORR->Get__VALUE();

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
					aEXT_CH__AI_APC_PRESSURE->Set__DATA(ch_data);
				}

				double cur_pressure = aEXT_CH__AI_APC_PRESSURE->Get__VALUE();

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

