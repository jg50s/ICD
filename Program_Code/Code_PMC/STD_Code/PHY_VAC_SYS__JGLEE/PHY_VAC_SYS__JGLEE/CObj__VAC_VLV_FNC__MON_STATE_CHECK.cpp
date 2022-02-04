#include "StdAfx.h"
#include "CObj__VAC_VLV_FNC.h"

#include "CObj__VAC_VLV_FNC__DEF.h"


// ...
int  CObj__VAC_VLV_FNC
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);

		// ...
		{
			int active_pumping = -1;

			ch_data = sEXT_CH__APC_VLV__MON_POSITION->Get__STRING();
			double cur_pos = atof(ch_data);

			if(cur_pos > 90)
			{
				if(sEXT_CH__VAC_VLV__MON_PUMPING_STATE->Check__DATA(STR__PUMPING) > 0)
				{
					active_pumping = 1;
				}
			}

			if(active_pumping > 0)		sCH__MON_PUMPING_STATE->Set__DATA(STR__PUMPING);
			else						sCH__MON_PUMPING_STATE->Set__DATA(STR__IDLE);
		}
	}

	return 1;
}

