#include "StdAfx.h"
#include "CObj_Phy__BUFFER_STD.h"


// ...
void CObj_Phy__BUFFER_STD
::Mon__STATUS_CTRL(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL x_timer_ctrl;

	double  cur_sec;
	CString var_data;
	int i;

	while(1)
	{
		x_timer_ctrl->POLL(1.0);

		if(xCH__CFG_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
		{
			sCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
		}
		else
		{
			sCH__OBJ_STATUS->Set__DATA(STR__DISABLE);
		}

		// ...
		int slot_max = (int) xCH__CFG_SLOT_MAX->Get__VALUE();
		if(slot_max > CFG_CLx__SLOT_MAX)
			slot_max = CFG_CLx__SLOT_MAX;

		for(i=0; i<slot_max; i++)
		{
			xCH__SLOT_WAIT_SEC[i]->Get__DATA(var_data);
			cur_sec = atof(var_data);

			if(cur_sec > 0)
			{
				cur_sec -= 1.0;						
				if(cur_sec < 0)			cur_sec = 0.0;

				var_data.Format("%.0f", cur_sec);
				xCH__SLOT_WAIT_SEC[i]->Set__DATA(var_data);
			}
			else if(cur_sec < 0)
			{
				xCH__SLOT_WAIT_SEC[i]->Set__DATA("0");
			}
		}
	}
}
