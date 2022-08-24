#include "StdAfx.h"
#include "CObj__PT_IO.h"


// ...
int  CObj__PT_IO
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int loop_count = 0;

	CString ch_data;
	int i;

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		loop_count++;
		if(loop_count >= 10)		loop_count = 1;

		if(loop_count == 1)
		{			
			// RANGE ...
			for(i=0; i<iPT_SIZE; i++)
			{
				double min_value = aCH__CFG_MIN_VALUE__PT_X[i]->Get__VALUE();
				double max_value = aCH__CFG_MAX_VALUE__PT_X[i]->Get__VALUE();
				int i_dec = (int) aCH__CFG_DEC_VALUE__PT_X[i]->Get__VALUE();

				aCH__MON_PRESSURE__PT_X[i]->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
				aCH__CFG_SETPOINT__PT_X[i]->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
				aEXT_CH__AI_PT_PRESSURE_X[i]->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
			}
		}

		if((loop_count == 1)
		|| (loop_count == 6))
		{
			// ZERO-CAL ...
			for(i=0; i<iPT_SIZE; i++)
			{
				if(sCH__ZERO_CAL_REQ_PRESSURE__PT_X[i]->Check__DATA(STR__YES) > 0)
				{
					sCH__ZERO_CAL_REQ_PRESSURE__PT_X[i]->Set__DATA("");

					aEXT_CH__AI_PT_PRESSURE_X[i]->Get__DATA(ch_data);
					aCH__ZERO_CAL_OFFSET__PT_X[i]->Set__DATA(ch_data);
				}
				if(sCH__ZERO_CAL_RESET_PRESSURE__PT_X[i]->Check__DATA(STR__YES) > 0)
				{
					sCH__ZERO_CAL_RESET_PRESSURE__PT_X[i]->Set__DATA("");

					aCH__ZERO_CAL_OFFSET__PT_X[i]->Set__DATA("0");
				}

				// ...
				double off_value = aCH__ZERO_CAL_OFFSET__PT_X[i]->Get__VALUE();
				double cur_value = aEXT_CH__AI_PT_PRESSURE_X[i]->Get__VALUE();
				double cal_value = cur_value;

				if((off_value > 0.001) || (off_value < -0.001))
				{
					if(cur_value < off_value)
					{
						cal_value = 0.0;
					}
					else
					{
						double cfg_max = aCH__CFG_MAX_VALUE__PT_X[i]->Get__VALUE();

						double cfg_range = cfg_max;
						double off_range = cfg_max - off_value;
						double r_range = 1.0;

						if(off_range > 0.001)			r_range = cfg_range / off_range;

						cal_value = (cur_value - off_value) * r_range;
					}
				}

				aCH__MON_PRESSURE__PT_X[i]->Set__VALUE(cal_value);
			}
		}

		// ...
	}

	return 1;
}

