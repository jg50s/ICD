#include "StdAfx.h"
#include "CObj__VAC_VLV_PHY.h"


// ...
int  CObj__VAC_VLV_PHY
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);

	
		// ...
		int active__pumping = -1;

		if(dEXT_CH__DI_DRY_PMP_PWR_SNS->Check__DATA(STR__ON) > 0)
		{
			bool active__fr_open = false;

			if(bActive__DO_FR_VALVE)
			{
				if(dEXT_CH__DO_FR_VALVE_CTRL->Check__DATA(STR__OPEN) > 0)		active__fr_open = true;
			}
			else if(bActive__DO_FR_VAT)
			{
				ch_data = sEXT_CH__VAT__MON_POSITION->Get__STRING();
				double cur_pos = atof(ch_data);

				if(cur_pos >= 10.0)			active__fr_open = true;
			}

			if(bActive__DO_SR_VALVE_CTRL)
			{
				if((dEXT_CH__DO_SR_VALVE_CTRL->Check__DATA(STR__OPEN) > 0) || (active__fr_open))
				{
					active__pumping = 1;
				}
			}
		}

		if(active__pumping > 0)
		{
			sCH__MON_PUMPING_STATE->Set__DATA("PUMPING");
		}
		else
		{
			sCH__MON_PUMPING_STATE->Set__DATA("IDLE");
		}
	}

	return 1;
}

