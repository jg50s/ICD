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

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(iPUMP__CTRL_TYPE = _PMP_CTRL_TYPE__MANUAL)
		{
			sCH__MON_COMM_STATE->Set__DATA(STR__ONLINE);

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

		// DI.VAC_SNS ...
		{
			bool active__vac_sns = false;

			if(bActive__DI_PUMP_VAC_SNS)
			{
				if(dEXT_CH__DI_PUMP_VAC_SNS->Check__DATA(STR__ON) > 0)		active__vac_sns = true;
			}

			if(bActive__AI_PUMP_PRESSURE_TORR)
			{
				double cfg__high_limit = aCH__CFG_PUMP_PRESSURE_HIGH_LIMIT->Get__VALUE();
				double cur__pmp_pressure = aEXT_CH__AI_PUMP_PRESSURE_TORR->Get__VALUE();

				if(cur__pmp_pressure < cfg__high_limit)						active__vac_sns = true;
			}

			if(active__vac_sns)			dCH__MON_VAC_ON_SNS->Set__DATA(STR__ON);
			else						dCH__MON_VAC_ON_SNS->Set__DATA(STR__OFF);
		}
	}
}

