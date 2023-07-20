#include "StdAfx.h"
#include "CObj__EPD_SINGLE.h"

#include <math.h>


// ...
int CObj__EPD_SINGLE
::Call__EPD_TEST(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString str_msg;

	str_msg = "EPD.TEST Start ...";
	sCH__CHART_TEST_INFO->Set__DATA(str_msg);

	int r_flag = Fnc__EPD_TEST(p_variable, p_alarm);

	if(r_flag > 0)
	{
		str_msg = "EPD.TEST Complete ...";
		sCH__CHART_TEST_INFO->Set__DATA(str_msg);
	}
	else
	{
		str_msg = "EPD.TEST Aborted ...";
		sCH__CHART_TEST_INFO->Set__DATA(str_msg);
	}
	return r_flag;
}
int CObj__EPD_SINGLE
::Fnc__EPD_TEST(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString chart_info;
	CString ch_data;

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		ch_data = x_seq_info->Get__DATE_TIME_STRING();
		sCH__CHART_DATE_TIME->Set__DATA(ch_data);
	}

	// ...
	SCX__TIMER_CTRL x_timer_loop;
	SCX__ASYNC_TIMER_CTRL x_timer_ctrl;

	x_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH__CHART_TIME_COUNT->Get__CHANNEL_NAME());
	x_timer_ctrl->START__COUNT_UP(9999);

	// DATA.INIT ...
	{	
		mEPD_CHART.Clear__ALL_CHART();
	}

	// EPD.DETECT ...
	double ref_sec = 0.1;
	double cur_sec = 0.0;

	double cfg__check_sec = 55.0;

	double cfg__delay_sec = 10.0;
	cfg__delay_sec += cfg__check_sec;

	bool active__epd_check = false;

	while(1)
	{
		x_timer_loop->POLL(ref_sec);

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -11;
		}

		cur_sec = x_timer_ctrl->Get__CURRENT_TIME();

		if(cur_sec >= cfg__check_sec)
		{
			if(!active__epd_check)
			{
				active__epd_check = true;

				dCH_INFO__EPD_CHECK_ACTIVE->Set__DATA(STR__ON);
			}
		}

		// DATA.LOAD ...
		{
			if(iActive__SIM_MODE > 0)
			{
				for(int i=0; i<iSIZE__EPD_SIGNAL; i++)
				{
					double cur_value = (rand() % 100) + 1000.0;

					aEXT_CH__EPD_SIGNAL_X[i]->Set__VALUE(cur_value);
				}
			}

			mEPD_CHART.Update__CHART_DATA(cur_sec);
		}

		if(active__epd_check)
		{
			if(cur_sec >= cfg__delay_sec)
			{
				return 11;
			}
		}
	}

	return 1;
}
