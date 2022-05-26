#include "StdAfx.h"
#include "CObj__EPD_SINGLE.h"

#include <math.h>



//--------------------------------------------------------------------------------
int CObj__EPD_SINGLE::
Fnc__EPD_DETECT__ValueSlope(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active__over_check)
{
	CString str__slope_count;
	CString str__slope_direction;
	CString str__valid_time;

	sCH__PARA_SLOPE_COUNT->Get__DATA(str__slope_count);
	sCH__PARA_SLOPE_DIRECTION->Get__DATA(str__slope_direction);
	sCH__PARA_VALID_TIME->Get__DATA(str__valid_time);

	double value__slope_count = atof(str__slope_count);
	double value__valid_time  = atof(str__valid_time);

	if(value__slope_count < 0)			value__slope_count = -value__slope_count;

	// ...
	int slope_dir_mode = -1;

	if(str__slope_direction.CompareNoCase(STR__UP) == 0)
	{
		slope_dir_mode = SLOPE_DIR__UP;
	}
	else if(str__slope_direction.CompareNoCase(STR__DOWN) == 0)
	{
		slope_dir_mode = SLOPE_DIR__DOWN;
		
		value__slope_count = -value__slope_count;
	}
	else if(str__slope_direction.CompareNoCase(STR__FLAT) == 0)
	{
		slope_dir_mode = SLOPE_DIR__FLAT;
	}
	else if(str__slope_direction.CompareNoCase(STR__UP_TO_FLAT) == 0)
	{
		slope_dir_mode = SLOPE_DIR__UP_TO_FLAT;
	}
	else if(str__slope_direction.CompareNoCase(STR__DOWN_TO_FLAT) == 0)
	{
		slope_dir_mode = SLOPE_DIR__DOWN_TO_FLAT;
	}
	else
	{
		int alarm_id = ALID__EPD_DETECT_UNKNOWN_SLOPE_DIRECTION;

		CString alarm_msg;
		CString alarm_bff;
		CString r_act;

		alarm_msg.Format("Unknown Slope Direction : Current Slope Direction [%s]\n", 
						str__slope_direction);

		alarm_bff.Format("Supported Slope Direction is as follows.\n");
		alarm_msg += alarm_bff;

		alarm_bff.Format("   1)  [%s]\n", STR__UP);
		alarm_msg += alarm_bff;

		alarm_bff.Format("   2)  [%s]\n", STR__DOWN);
		alarm_msg += alarm_bff;

		alarm_bff.Format("   3)  [%s]\n", STR__FLAT);
		alarm_msg += alarm_bff;

		alarm_bff.Format("   4)  [%s]\n", STR__UP_TO_FLAT);
		alarm_msg += alarm_bff;

		alarm_bff.Format("   5)  [%s]\n", STR__DOWN_TO_FLAT);
		alarm_msg += alarm_bff;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alarm_msg);
		return -1;
	}

	// ...
	bool active__epd_ok = false;

	double  epd_data = 0;
	CString str_data;

	double cur_data = 0;
	double pre_data = 0;
	int n_count = 0;

	int success_count = 1;
	int check_count = 0;

	if(value__valid_time < 0.1)
	{
		success_count = 1;
	}
	else
	{
		success_count = (int) (value__valid_time / DEF__SAMPLING_SEC);
	}

	if(success_count < 1)
	{
		success_count = 1;
	}

	double timeout = aCH__PARA_EPD_TIMEOUT_MAXIMUM->Get__VALUE();

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "\n";
		log_msg += "EPD Information ...\n";

		//
		log_msg += "   1. Setting Parameter ...\n";

		log_bff.Format("   Slope Count     : [%s]\n", str__slope_count);
		log_msg += log_bff;

		log_bff.Format("   Slope Direction : [%s]\n", str__slope_direction);
		log_msg += log_bff;

		log_bff.Format("   Valid Time : [%s]\n", str__valid_time);
		log_msg += log_bff;

		//
		log_msg += "   2. Control Parameter ...\n";

		log_bff.Format("   Value Slope    : [%.3f]\n", value__slope_count);
		log_msg += log_bff;

		log_bff.Format("   Slope Dir Mode : [%1d]\n", slope_dir_mode);
		log_msg += log_bff;

		log_bff.Format("   Success Count  : [%1d]\n", success_count);
		log_msg += log_bff;

		log_bff.Format("   Timeout : [%.1f]\n", timeout);
		log_msg += log_bff;

		Fnc__WRITE_LOG(log_msg);
	}

	// ...
	SCX__TIMER_CTRL x_timer_ctrl;
	x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);

	while(1)
	{
		double cur_sec = Get__EPD_CUR_SEC();
		if(cur_sec >= timeout)			break;

		//
		if(x_timer_ctrl->POLL(DEF__SAMPLING_SEC) < 0)
		{
			return -1;
		}

		// ...
		{
			epd_data = Get__EPD_CUR_DATA();

			str_data.Format("%.1f", epd_data);
			sCH_INFO__CUR_IBx_DATA->Set__DATA(str_data);

			// ...
			{
				CString log_msg;

				log_msg.Format("EPD Data (%f)", epd_data);
				Fnc__WRITE_LOG(log_msg);
			}
		}

		// ...
		n_count++;

		if(n_count == 1)
		{
			cur_data = epd_data;
			pre_data = cur_data;
		}
		else 
		{
			double change_data = cur_data - pre_data;
			double cur_slope = change_data / DEF__SAMPLING_SEC;

			str_data.Format("%.1f", cur_slope);
			sCH_INFO__CUR_CAL_SLOPE_COUNT->Set__DATA(str_data);

			if(slope_dir_mode == SLOPE_DIR__UP)
			{
				if(cur_slope > value__slope_count)
				{
					check_count++;

					if(check_count >= success_count)
					{
						active__epd_ok = true;
						break;
					}
				}
				else
				{
					check_count = 0;
				}
			}
			else if(slope_dir_mode == SLOPE_DIR__DOWN)
			{
				if(cur_slope < value__slope_count)
				{
					check_count++;

					if(check_count >= success_count)
					{
						active__epd_ok = true;
						break;
					}
				}
				else
				{
					check_count = 0;
				}
			}
			else if(slope_dir_mode == SLOPE_DIR__FLAT)
			{
				if(cur_slope <= value__slope_count)
				{
					check_count++;

					if(check_count >= success_count)
					{
						active__epd_ok = true;
						break;
					}
				}
				else
				{
					check_count = 0;
				}
			}
			else if(slope_dir_mode == SLOPE_DIR__UP_TO_FLAT)
			{
				if((cur_slope >= 0) && (cur_slope <= value__slope_count))	
				{
					check_count++;

					if(check_count >= success_count)
					{
						active__epd_ok = true;
						break;
					}
				}
				else
				{
					check_count = 0;
				}
			}
			else if(slope_dir_mode == SLOPE_DIR__DOWN_TO_FLAT)
			{
				if((cur_slope <= 0) && (cur_slope >= value__slope_count))
				{
					check_count++;

					if(check_count >= success_count)
					{
						active__epd_ok = true;
						break;
					}
				}
				else
				{
					check_count = 0;
				}
			}
		}
	}

	if(active__epd_ok)
	{
		double min_sec = aCH__PARA_EPD_TIMEOUT_MINIMUM->Get__VALUE();
		double cur_sec = Get__EPD_CUR_SEC();

		if(cur_sec < min_sec)
		{
			CString alm_msg;
			CString alm_bff;

			alm_msg  = "During checking EPD's CheckSlope Algorithm, \n";
			alm_msg += "Minimum Timeout occurred !\n";

			alm_bff.Format("Minimum timeout value is \"%.1f\".\n", min_sec);
			alm_msg += alm_bff;

			alm_bff.Format("Detecting time is \"%.1f\".\n", cur_sec);
			alm_msg += alm_bff;

			Alarm_Post__EPD_MIN_TIMEOUT(p_alarm,alm_msg);

			THROW__ABORT;
		}
		return 1;
	}

	// ...
	{
		CString alarm_msg;
		CString alarm_bff;

		alarm_msg  = "During checking EPD's CheckSlope Algorithm, \n";
		alarm_msg += "Timeout occurred !\n";

		alarm_bff.Format("Timeout value is \"%.1f\".\n",timeout);
		alarm_msg += alarm_bff;

		Alarm_Post__EPD_MAX_TIMEOUT(p_alarm,alarm_msg);
	}
	return -1;
}
