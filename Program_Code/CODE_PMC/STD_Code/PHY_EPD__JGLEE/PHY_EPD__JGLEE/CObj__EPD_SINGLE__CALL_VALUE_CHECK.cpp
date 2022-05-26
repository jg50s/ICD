#include "StdAfx.h"
#include "CObj__EPD_SINGLE.h"

#include <math.h>



//--------------------------------------------------------------------------------
int CObj__EPD_SINGLE::
Fnc__EPD_DETECT__ValueCheck(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const bool active__over_check)
{
	CString log_msg;

	// ...
	{
		if(active__over_check)		log_msg = "OverValue.Check : Detecting Start ...";
		else						log_msg = "UnderValue.Check : Detecting Start ...";

		Fnc__WRITE_LOG(log_msg);
	}

	// 1. Wait Delay Time
	if(Fnc__EPD_DETECT__CheckDelayTime(p_variable) < 0)
	{
		return -1;
	}

	// 2. Wait Normalize time
	if(Fnc__EPD_DETECT__CheckNormalizeTime(p_variable) < 0)
	{
		return -1;
	}

	// 3. EPD Detect
	if(_Fnc__EPD_DETECT__ValueCheck(p_variable,p_alarm, active__over_check) < 0)
	{
		return -1;
	}

	// ...
	{
		log_msg = "Detecting End ...";

		Fnc__WRITE_LOG(log_msg);
	}
	return 1;
}
int CObj__EPD_SINGLE::
_Fnc__EPD_DETECT__ValueCheck(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active__over_check)
{
	if(active__over_check)			sCH__OBJ_MSG->Set__DATA("OverValue.Check : Start ...");
	else							sCH__OBJ_MSG->Set__DATA("UnderValue.Check : Start ...");

	// ...
	CString ch_data= sCH__PARA_VALID_TIME->Get__STRING();
	double ref__valid_sec = atof(ch_data);
	if(ref__valid_sec < 1.0)		ref__valid_sec = 1.0;

	double timeout = aCH__PARA_EPD_TIMEOUT_MAXIMUM->Get__VALUE();	
	int check_count = 0;

	// ...
	{
		CString log_msg;

		log_msg.Format("EPD Timeout (%.1f), Valid_Time (%.1f) sec",
						timeout, ref__valid_sec);
		Fnc__WRITE_LOG(log_msg);
	}

	// ...
	ch_data = sCH_INFO__CUR_NORMALIZE_VALUE->Get__STRING();
	double normal_value = atof(ch_data);

	ch_data = sCH__PARA_VALUE_TO_CHANGE->Get__STRING();
	double para__target_value = atof(ch_data);
	double threshold_value = normal_value + para__target_value;

	// ...
	{
		CString log_msg;

		log_msg.Format("Threshold_Value(%.1f) = Normalize_Value(%.1f) + target_value(%.1f)",
						threshold_value, 
						normal_value,
						para__target_value);
		Fnc__WRITE_LOG(log_msg);
	}

	ch_data.Format("%.1f", threshold_value);
	sCH_INFO__CUR_THRESHOLD_VALUE->Set__DATA(ch_data);

	// ...
	bool active__epd_ok = false;
	double epd_data = 0;

	// ...
	SCX__ASYNC_TIMER_CTRL x_timer_check_sec;
	x_timer_check_sec->REGISTER__COUNT_CHANNEL_NAME(sCH_INFO__CUR_EPD_TIME_COUNT->Get__CHANNEL_NAME());
	x_timer_check_sec->STOP_ZERO();

	SCX__TIMER_CTRL x_timer_ctrl;
	x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);


	while(1)
	{
		double cur_sec = Get__EPD_CUR_SEC();
		if(cur_sec >= timeout)			break;

		//
		if(x_timer_ctrl->POLL(DEF__SAMPLING_SEC) < 0)
		{
			Fnc__WRITE_LOG("Check ValueChange : Abort ...");

			THROW__ABORT;
		}

		if(sCH__EPD_EXCEPTION_REQ->Check__DATA(STR__ABORT) > 0)
		{
			Fnc__WRITE_LOG("Check ValueChange (By Exception) : Abort ...");

			THROW__ABORT;
		}
		if(sCH__EPD_EXCEPTION_REQ->Check__DATA(STR__END) > 0)
		{
			Fnc__WRITE_LOG("Check ValueChange (By Exception) : End ...");

			THROW__END;
		}

		if(iActive__SIM_MODE > 0)
		{
			double cfg_sec = aCH__PARA_EPD_TIMEOUT_MINIMUM->Get__VALUE();
			double cur_sec = Get__EPD_CUR_SEC();

			double sim_sec = 0.0;

			if(cur_sec < cfg_sec)
			{
				if(active__over_check)			sim_sec = threshold_value * 0.5;
				else							sim_sec = threshold_value * 1.5;
			}
			else
			{
				if(active__over_check)			sim_sec = threshold_value + 0.01;
				else							sim_sec = threshold_value - 0.01;
			}

			aEXT_CH__EPD_SIGNAL->Set__VALUE(sim_sec);
		}

		// ...
		{
			epd_data = Get__EPD_CUR_DATA();

			ch_data.Format("%.1f", epd_data);
			sCH_INFO__CUR_IBx_DATA->Set__DATA(ch_data);

			// ...
			{
				CString log_msg;

				log_msg.Format("EPD Data (%f)", epd_data);
				Fnc__WRITE_LOG(log_msg);
			}
		}

		if(active__over_check)
		{
			if(epd_data >= threshold_value)
			{
				if(check_count == 0)		x_timer_check_sec->START__COUNT_UP(9999);
				check_count++;
			}
			else
			{
				if(check_count > 0)			x_timer_check_sec->STOP_ZERO();
				check_count = 0;
			}
		}
		else
		{
			if(epd_data <= threshold_value)
			{
				if(check_count == 0)		x_timer_check_sec->START__COUNT_UP(9999);
				check_count++;
			}
			else
			{
				if(check_count > 0)			x_timer_check_sec->STOP_ZERO();
				check_count = 0;
			}
		}

		// ...
		double cur__check_sec = x_timer_check_sec->Get__CURRENT_TIME();

		if(cur__check_sec >= ref__valid_sec)
		{
			// ...
			{
				CString log_msg;

				log_msg.Format("EPD Success : Current-Check_Time (%.1f), Ref.Valid_Time (%.1f)", 
					cur__check_sec, ref__valid_sec);
				Fnc__WRITE_LOG(log_msg);
			}

			active__epd_ok = true;
			break;
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

			alm_msg  = "During checking EPD's ValueChange Algorithm, \n";
			alm_msg += "Minimum Timeout occurred !\n";

			alm_bff.Format("Minimum timeout value is \"%.1f\".\n", min_sec);
			alm_msg += alm_bff;

			alm_bff.Format("Detecting Time is \"%.1f\".\n", cur_sec);
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

		alarm_msg  = "During checking EPD's ValueChange Algorithm, \n";
		alarm_msg += "Timeout occurred !\n";

		alarm_bff.Format("Timeout value is \"%.1f\".\n",timeout);
		alarm_msg += alarm_bff;

		Alarm_Post__EPD_MAX_TIMEOUT(p_alarm,alarm_msg);
	}

	THROW__ABORT;
}

