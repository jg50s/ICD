#include "StdAfx.h"
#include "CObj__EPD_SINGLE.h"
#include "CObj__EPD_SINGLE__ALID.h"


// ...
int  CObj__EPD_SINGLE
::Mon__EPD_CHART(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	SCX__SEQ_INFO x_seq_info;
	CString ch_data;
	
	SCX__TIMER_CTRL x_timer_loop;
	SCX__ASYNC_TIMER_CTRL x_timer_ctrl;

	bool active__epd_start = false;

	// ...
	{
		x_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH__CHART_TIME_COUNT->Get__CHANNEL_NAME());
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		
		if(sCH_INFO__EPD_START_FLAG->Check__DATA(STR__START) > 0)
		{
			if(!active__epd_start)
			{
				active__epd_start = true;

				// ...
				{
					ch_data = x_seq_info->Get__DATE_TIME_STRING();
					sCH__CHART_DATE_TIME->Set__DATA(ch_data);
				}

				x_timer_ctrl->START__COUNT_UP(9999);
				mEPD_CHART.Clear__ALL_CHART();
			}

			if(active__epd_start)
			{
				double cur_sec = x_timer_ctrl->Get__CURRENT_TIME();
				mEPD_CHART.Update__CHART_DATA(cur_sec);
			}
		}
		else
		{
			if(dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE->Check__DATA(STR__OFF) > 0)
			{
				if(active__epd_start)
				{
					active__epd_start = false;

					double cur_sec = x_timer_ctrl->Get__CURRENT_TIME();
					mEPD_CHART.Update__CHART_DATA(cur_sec);
	
					x_timer_ctrl->STOP();
				}
			}
			else
			{
				if(active__epd_start)
				{
					double cur_sec = x_timer_ctrl->Get__CURRENT_TIME();
					mEPD_CHART.Update__CHART_DATA(cur_sec);
				}
			}
		}
	}

	return 1;
}

