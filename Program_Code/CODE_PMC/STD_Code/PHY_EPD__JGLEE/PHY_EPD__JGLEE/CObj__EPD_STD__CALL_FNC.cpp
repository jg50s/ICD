#include "StdAfx.h"
#include "CObj__EPD_STD.h"

#include <math.h>



//--------------------------------------------------------------------------------
int CObj__EPD_STD
::Call__INIT(CII_OBJECT__VARIABLE *p_variable,
			 CII_OBJECT__ALARM *p_alarm)
{
	Fnc__WRITE_LOG("Call__INIT.. Start ...");

	// ...
	CString log_msg;

	int nRet = pOBJ__OES_CTRL->Call__OBJECT(MODE__INIT);
	if(nRet < 0)
	{
		// ...
		{
			log_msg.Format("Ret:%d, Fail ...", nRet);
			Fnc__WRITE_LOG(log_msg);
		}
	}

	// ...
	{
		log_msg.Format("Call__INIT.. Ret:%d, Complete ...", nRet);
		Fnc__WRITE_LOG(log_msg);
	}
	return nRet;
}

int CObj__EPD_STD
::Call__EPD_DETECT(CII_OBJECT__VARIABLE *p_variable,
				   CII_OBJECT__ALARM *p_alarm)
{
	CString var_data;

	// ...
	{
		sCH_INFO__CUR_SEQ_MSG->Set__DATA("");
		sCH_INFO__CUR_DELAY_TIME_COUNT->Set__DATA("");
		sCH_INFO__CUR_NORMALIZE_TIME_COUNT->Set__DATA("");
		sCH_INFO__CUR_EPD_TIME_COUNT->Set__DATA("");
		sCH_INFO__CUR_NORMALIZE_VALUE->Set__DATA("");
		sCH_INFO__CUR_THRESHOLD_VALUE->Set__DATA("");
		sCH_INFO__CUR_CAL_SLOPE_COUNT->Set__DATA("");
		sCH_INFO__CUR_IBx_LIST->Set__DATA("");
		sCH_INFO__CUR_IBx_DATA->Set__DATA("");

		sCH_INFO__CUR_EPD_START_SEC->Set__DATA("");
	}

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "\n";

		// ...
		{
			aCH__CFG_DELAY_TIME->Get__DATA(var_data);
			log_bff.Format("Delay Time <- [%s] \n", var_data);
			log_msg += log_bff;
		
			//
			sCH__CFG_PARAMETER_NORMALIZE_TIME->Get__DATA(var_data);	
			log_bff.Format("Normalize Time <- [%s] \n", var_data);
			log_msg += log_bff;
		}

		// ...
		{
			dCH__CFG_EPD_MODE->Get__DATA(var_data);		
			log_bff.Format("EPD Mode <- [%s] \n", var_data);
			log_msg += log_bff;

			//
			sCH__CFG_PARAMETER_VALUE_TO_CHANGE->Get__DATA(var_data);
			log_bff.Format("Parameter Valve_To_Change <- [%s] \n", var_data);
			log_msg += log_bff;

			sCH__CFG_PARAMETER_PERCENT_TO_CHANGE->Get__DATA(var_data);
			log_bff.Format("Parameter Percent_To_Change <- [%s] \n", var_data);
			log_msg += log_bff;

			//
			sCH__CFG_PARAMETER_SLOPE_COUNT->Get__DATA(var_data);
			log_bff.Format("Parameter Slop_Count <- [%s] \n", var_data);
			log_msg += log_bff;

			sCH__CFG_PARAMETER_SLOPE_DIRECTION->Get__DATA(var_data);
			log_bff.Format("Parameter Slop_Direction <- [%s] \n", var_data);
			log_msg += log_bff;

			sCH__CFG_PARAMETER_VALIDATION_TIME->Get__DATA(var_data);
			log_bff.Format("Parameter Validation_Time <- [%s] \n", var_data);
			log_msg += log_bff;

			//
			aCH__CFG_EPD_TIMEOUT_MINIMUM->Get__DATA(var_data);
			log_bff.Format("Min. Timeout <- [%s] \n", var_data);
			log_msg += log_bff;

			//
			aCH__CFG_EPD_TIMEOUT_MAXIMUM->Get__DATA(var_data);
			log_bff.Format("Max. Timeout <- [%s] \n", var_data);
			log_msg += log_bff;
		}

		Fnc__WRITE_LOG(log_msg);
	}

	dCH__CFG_EPD_MODE->Get__DATA(var_data);

	if(var_data.CompareNoCase(STR__VALUE_CHANGE) == 0)
	{
		return Fnc__EPD_DETECT__ValueChange(p_variable,p_alarm);
	}
	else if(var_data.CompareNoCase(STR__PERCENT_CHANGE) == 0)
	{
		return Fnc__EPD_DETECT__PercentChange(p_variable,p_alarm);
	}
	else if(var_data.CompareNoCase(STR__VALUE_SLOPE) == 0)
	{
		int flag = Fnc__EPD_DETECT__ValueChange(p_variable,p_alarm);
		if(flag < 0)		return -1;

		return Fnc__EPD_DETECT__CheckSlope(p_variable,p_alarm);
	}
	else if(var_data.CompareNoCase(STR__PERCENT_SLOPE) == 0)
	{
		int flag = Fnc__EPD_DETECT__PercentChange(p_variable,p_alarm);
		if(flag < 0)		return -1;

		return Fnc__EPD_DETECT__CheckSlope(p_variable,p_alarm);
	}

	return -1;
}

int CObj__EPD_STD::
Fnc__EPD_DETECT__ValueChange(CII_OBJECT__VARIABLE *p_variable,
							 CII_OBJECT__ALARM *p_alarm)
{
	Fnc__WRITE_LOG("ValueChange : Detecting Start ...");

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
	if(Fnc__EPD_DETECT__CheckValueChange(p_variable,p_alarm) < 0)
	{
		return -1;
	}

	Fnc__WRITE_LOG("ValueChange : Detecting End ...");
	return 1;
}
int CObj__EPD_STD::
Fnc__EPD_DETECT__PercentChange(CII_OBJECT__VARIABLE *p_variable,
							   CII_OBJECT__ALARM *p_alarm)
{
	Fnc__WRITE_LOG("PercentChange : Detecting Start ...");

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
	if(Fnc__EPD_DETECT__CheckPercentChange(p_variable,p_alarm) < 0)
	{
		return -1;
	}

	Fnc__WRITE_LOG("PercentChange : Detecting End ...");
	return 1;
}

int CObj__EPD_STD::
Fnc__EPD_DETECT__CheckDelayTime(CII_OBJECT__VARIABLE* p_variable)
{
	sCH__OBJ_MSG->Set__DATA("Delay Time Check : Start ...");

	// ...
	SCX__ASYNC_TIMER_CTRL x_async_timer;
	
	CString str_data;
	double delay_sec;

	aCH__CFG_DELAY_TIME->Get__DATA(str_data);
	delay_sec = atof(str_data);

	x_async_timer->REGISTER__COUNT_CHANNEL_NAME(sCH_INFO__CUR_DELAY_TIME_COUNT->Get__CHANNEL_NAME());
	x_async_timer->Set__START_TIME(0);
	x_async_timer->START__COUNT_UP(99999);

	while(1)
	{
		Sleep(3);

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			Fnc__WRITE_LOG("Wait Delay Time : Abort ...");

			THROW__ABORT;
		}
		if(sCH__EPD_EXCEPTION_REQ->Check__DATA(STR__ABORT) > 0)
		{
			Fnc__WRITE_LOG("Wait Delay Time (By Exception) : Abort ...");

			THROW__ABORT;
		}
		if(sCH__EPD_EXCEPTION_REQ->Check__DATA(STR__END) > 0)
		{
			Fnc__WRITE_LOG("Wait Delay Time (By Exception) : End ...");

			THROW__END;
		}

		if(delay_sec <= x_async_timer->Get__CURRENT_TIME())
		{
			break;
		}
	}

	Fnc__WRITE_LOG("Wait Delay Time : OK ...");
	return 1;
}
int CObj__EPD_STD::
Fnc__EPD_DETECT__CheckNormalizeTime(CII_OBJECT__VARIABLE* p_variable)
{
	sCH__OBJ_MSG->Set__DATA("Normalize Time Check : Start ...");

	// ...
	CString str_data;
	
	sCH__CFG_PARAMETER_NORMALIZE_TIME->Get__DATA(str_data);
	double normal_time = atof(str_data);
	
	double normal_value  = 0.0;
	double sampling_data = 0.0;

	SCX__ASYNC_TIMER_CTRL async_time_ctrl;
	SCX__TIMER_CTRL       x_timer_ctrl;
	int count = 0;
	
	x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);

	async_time_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH_INFO__CUR_NORMALIZE_TIME_COUNT->Get__CHANNEL_NAME());
	async_time_ctrl->Set__START_TIME(0);
	async_time_ctrl->START__COUNT_UP(99999);

	while(1)
	{
		count++;

		if(x_timer_ctrl->WAIT(DEF__SAMPLING_SEC) < 0)
		{
			async_time_ctrl->STOP();
			Fnc__WRITE_LOG("Check Normalize Time : Abort ...");

			THROW__ABORT;
		}

		if(sCH__EPD_EXCEPTION_REQ->Check__DATA(STR__ABORT) > 0)
		{
			Fnc__WRITE_LOG("Check Normalize Time (By Exception) : Abort ...");

			THROW__ABORT;
		}
		if(sCH__EPD_EXCEPTION_REQ->Check__DATA(STR__END) > 0)
		{
			Fnc__WRITE_LOG("Check Normalize Time (By Exception) : End ...");

			THROW__END;
		}

		// Sampling Data : All Sum ...
		{
			sampling_data = Get__IBx_SPEC_DATA();

			// ...
			{
				str_data.Format("%.1f", sampling_data);
				sCH_INFO__CUR_IBx_DATA->Set__DATA(str_data);

				// ...
				{
					CString log_msg;

					log_msg.Format("EPD Data (%f)", sampling_data);
					Fnc__WRITE_LOG(log_msg);
				}
			}

			if(count == 1)
			{
				normal_value = sampling_data;
			}
			else
			{
				double pre_n = (double) (count - 1.0);
				double cur_n = (double) (count);

				double pre_y = normal_value;
				double pre_x = sampling_data / pre_n;

				normal_value = (pre_n / cur_n) * (pre_y + pre_x);
			}

			// ...
			{
				CString log_msg;

				log_msg.Format("Normalize Value (%.1f)", normal_value);
				Fnc__WRITE_LOG(log_msg);
			}
		}

		if(normal_time <= async_time_ctrl->Get__CURRENT_TIME())
		{
			async_time_ctrl->STOP();

			// ...
			{
				CString log_msg;

				log_msg.Format("Normalize Time (%.1f), Sampling Count (%1d)", 
							   normal_time, count);
				Fnc__WRITE_LOG(log_msg);
			}
			break;
		}
	}

	// ...
	{
		str_data.Format("%.3f", normal_value);
		sCH_INFO__CUR_NORMALIZE_VALUE->Set__DATA(str_data);

		// ...
		{
			CString log_msg;

			log_msg.Format("Result - Normalize Value (%.2f)", normal_value);
			Fnc__WRITE_LOG(log_msg);
		}
	}
	return 1;
}

int CObj__EPD_STD::
Fnc__EPD_DETECT__CheckValueChange(CII_OBJECT__VARIABLE* p_variable,
								  CII_OBJECT__ALARM* p_alarm)
{
	sCH__OBJ_MSG->Set__DATA("ValueChange Check : Start ...");

	// ...
	CString str_data;

	aCH__CFG_EPD_TIMEOUT_MAXIMUM->Get__DATA(str_data);
	double timeout = atof(str_data);	
	
	int success_count = 2;
	int check_count = 0;

	// ...
	{
		CString log_msg;

		log_msg.Format("EPD Timeout (%.1f), Success Count (%1d)",
					   timeout, success_count);
		Fnc__WRITE_LOG(log_msg);
	}

	// ...
	sCH_INFO__CUR_NORMALIZE_VALUE->Get__DATA(str_data);
	double normal_value = atof(str_data);

	sCH__CFG_PARAMETER_VALUE_TO_CHANGE->Get__DATA(str_data);	
	double value_change = atof(str_data);
	double threshold_value = normal_value + value_change;

	// ...
	{
		CString log_msg;

		log_msg.Format("Threshold_Value(%f) = Normalize_Value(%f) + Value_Change(%f)",
					   threshold_value,normal_value,value_change);
		Fnc__WRITE_LOG(log_msg);
	}

	str_data.Format("%.1f", threshold_value);
	sCH_INFO__CUR_THRESHOLD_VALUE->Set__DATA(str_data);

	SCX__TIMER_CTRL x_timer_ctrl;
	double epd_data = 0;

	x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);


	while(1)
	{
		// ...
		{
			double cur_sec = Get__EPD_CUR_SEC();
			
			if(cur_sec >= timeout)
			{
				break;
			}
		}

		if(x_timer_ctrl->WAIT(DEF__SAMPLING_SEC) < 0)
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
			double cur_sec = Get__EPD_CUR_SEC();
			double sim_data = 0.0;

			aCH__CFG_EPD_TIMEOUT_MINIMUM->Get__DATA(str_data);
			double min_sec = atof(str_data);

			if(cur_sec < min_sec)
			{
				if(value_change >= 0)			sim_data = threshold_value * 0.5;
				else							sim_data = threshold_value * 1.5;
			}
			else
			{
				if(value_change >= 0)			sim_data = threshold_value + 0.01;
				else							sim_data = threshold_value - 0.01;
			}

			aEXT_CH__IBx_SPEC_DATA[0]->Set__VALUE(sim_data);				
		}

		// ...
		{
			epd_data = Get__IBx_SPEC_DATA();

			str_data.Format("%.1f", epd_data);
			sCH_INFO__CUR_IBx_DATA->Set__DATA(str_data);

			// ...
			{
				CString log_msg;

				log_msg.Format("EPD Data (%f)", epd_data);
				Fnc__WRITE_LOG(log_msg);
			}
		}

		if(value_change >= 0)
		{
			if(epd_data >= threshold_value)
			{
				check_count ++;
			}
			else
			{
				check_count = 0;
			}
		}
		else
		{
			if(epd_data <= threshold_value)
			{
				check_count ++;
			}
			else
			{
				check_count = 0;
			}
		}

		if(check_count >= success_count)
		{
			// ...
			{
				CString log_msg;

				log_msg.Format("EPD Success : Count (%1d), Config Success Count (%1d)", 
							   check_count, success_count);
				Fnc__WRITE_LOG(log_msg);
			}

			// ...
			{
				aCH__CFG_EPD_TIMEOUT_MINIMUM->Get__DATA(str_data);
				double min_sec = atof(str_data);
				double cur_sec = Get__EPD_CUR_SEC();

				if(min_sec > cur_sec)
				{
					CString alm_msg;
					CString alm_bff;

					alm_msg  = "During checking EPD's ValueChange Algorithm, \n";
					alm_msg += "Minimum Timeout occurred !\n";
					
					alm_bff.Format("Minimum Timeout's value is \"%.1f\".\n", min_sec);
					alm_msg += alm_bff;

					alm_bff.Format("Detecting Time is \"%.1f\".\n", cur_sec);
					alm_msg += alm_bff;

					Alarm_Post__EPD_MIN_TIMEOUT(p_alarm,alm_msg);
					
					THROW__ABORT;
				}
			}
			return 1;
		}
	}

	// ...
	{
		CString log_msg;

		log_msg.Format("EPD Fail : Count (%1d), Config Success Count (%1d)", 
					   check_count, success_count);
		Fnc__WRITE_LOG(log_msg);
	}

	// ...
	{
		CString alarm_msg;
		CString alarm_bff;

		alarm_msg  = "During checking EPD's ValueChange Algorithm, \n";
		alarm_msg += "Timeout occurred !\n";

		alarm_bff.Format("Timeout's value is \"%.1f\".\n",timeout);
		alarm_msg += alarm_bff;

		Alarm_Post__EPD_MAX_TIMEOUT(p_alarm,alarm_msg);
	}

	THROW__ABORT;
}
int CObj__EPD_STD::
Fnc__EPD_DETECT__CheckPercentChange(CII_OBJECT__VARIABLE* p_variable,
									CII_OBJECT__ALARM* p_alarm)
{
	sCH__OBJ_MSG->Set__DATA("PercentChange Check : Start ...");

	// ...
	CString str_data;

	aCH__CFG_EPD_TIMEOUT_MAXIMUM->Get__DATA(str_data);
	double timeout = atof(str_data);	
	
	int success_count = 2;
	int check_count = 0;

	// ...
	{
		CString log_msg;

		log_msg.Format("EPD Timeout (%.1f), Success Count (%1d)",
					   timeout, success_count);
		Fnc__WRITE_LOG(log_msg);
	}

	// ...
	sCH_INFO__CUR_NORMALIZE_VALUE->Get__DATA(str_data);
	double normal_value = atof(str_data);

	sCH__CFG_PARAMETER_PERCENT_TO_CHANGE->Get__DATA(str_data);	
	double percent_change  = atof(str_data);
	double threshold_value = normal_value * (1.0 + percent_change / 100.0);

	// ...
	{
		CString log_msg;
		
		log_msg.Format("Threshold_Value(%f) = Normalize_Value(%f) * ( 1.0 + Percent_Change(%f) / 100.0)",
					   threshold_value,normal_value,percent_change);
		Fnc__WRITE_LOG(log_msg);
	}

	str_data.Format("%.1f", threshold_value);
	sCH_INFO__CUR_THRESHOLD_VALUE->Set__DATA(str_data);

	// ...
	SCX__TIMER_CTRL x_timer_ctrl;
	double epd_data = 0;

	x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);

	while(1)
	{
		// ...
		{
			double cur_sec = Get__EPD_CUR_SEC();
			
			if(cur_sec >= timeout)
			{
				break;
			}
		}

		if(x_timer_ctrl->WAIT(DEF__SAMPLING_SEC) < 0)
		{
			Fnc__WRITE_LOG("Check Percent Change : Abort ...");

			THROW__ABORT;
		}
		
		if(sCH__EPD_EXCEPTION_REQ->Check__DATA(STR__ABORT) > 0)
		{
			Fnc__WRITE_LOG("Check Percent Change (By Exception) : Abort ...");

			THROW__ABORT;
		}
		if(sCH__EPD_EXCEPTION_REQ->Check__DATA(STR__END) > 0)
		{
			Fnc__WRITE_LOG("Check Percent Change (By Exception) : End ...");

			THROW__END;
		}

		if(iActive__SIM_MODE > 0)
		{
			double cur_sec = Get__EPD_CUR_SEC();
			double sim_data = 0.0;

			aCH__CFG_EPD_TIMEOUT_MINIMUM->Get__DATA(str_data);
			double min_sec = atof(str_data);

			if(cur_sec < min_sec)
			{
				if(percent_change >= 0)			sim_data = threshold_value * 0.5;
				else							sim_data = threshold_value * 1.5;
			}
			else
			{
				if(percent_change >= 0)			sim_data = threshold_value + 0.01;
				else							sim_data = threshold_value - 0.01;
			}

			aEXT_CH__IBx_SPEC_DATA[0]->Set__VALUE(sim_data);				
		}

		// ...
		{
			epd_data = Get__IBx_SPEC_DATA();

			str_data.Format("%.1f", epd_data);
			sCH_INFO__CUR_IBx_DATA->Set__DATA(str_data);

			// ...
			{
				CString log_msg;

				log_msg.Format("EPD Data (%f)", epd_data);
				Fnc__WRITE_LOG(log_msg);
			}
		}

		if(percent_change >= 0)
		{
			if(epd_data >= threshold_value)
			{
				check_count ++;
			}
			else
			{
				check_count = 0;
			}
		}
		else
		{
			if(epd_data <= threshold_value)
			{
				check_count ++;
			}
			else
			{
				check_count = 0;
			}
		}

		if(check_count >= success_count)
		{
			// ...
			{
				CString log_msg;

				log_msg.Format("EPD Success : Count (%1d), Config Success Count (%1d)", 
							   check_count, success_count);
				Fnc__WRITE_LOG(log_msg);
			}

			// ...
			{
				aCH__CFG_EPD_TIMEOUT_MINIMUM->Get__DATA(str_data);
				double min_sec = atof(str_data);
				double cur_sec = Get__EPD_CUR_SEC();
				
				if(min_sec > cur_sec)
				{
					CString alm_msg;
					CString alm_bff;
					
					alm_msg  = "During checking EPD's PercentChange Algorithm, \n";
					alm_msg += "Minimum Timeout occurred !\n";
					
					alm_bff.Format("Minimum Timeout's value is \"%.1f\".\n", min_sec);
					alm_msg += alm_bff;
					
					alm_bff.Format("Detecting Time is \"%.1f\".\n", cur_sec);
					alm_msg += alm_bff;

					Alarm_Post__EPD_MIN_TIMEOUT(p_alarm,alm_msg);
					
					THROW__ABORT;
				}
			}
			return 1;
		}
	}

	// ...
	{
		CString log_msg;

		log_msg.Format("EPD Fail : Count (%1d), Config Success Count (%1d)", 
					   check_count, success_count);
		Fnc__WRITE_LOG(log_msg);
	}

	//.....
	{
		CString alarm_msg;
		CString alarm_bff;

		alarm_msg  = "During checking EPD's PercentChange Algorithm, \n";
		alarm_msg += "Timeout occurred !\n";

		alarm_bff.Format("Timeout's value is \"%.1f\".\n",timeout);
		alarm_msg += alarm_bff;

		Alarm_Post__EPD_MAX_TIMEOUT(p_alarm,alarm_msg);
	}
	
	THROW__ABORT;
}


// ...
#define SLOPE_DIR__UP				1
#define SLOPE_DIR__DOWN				2
#define SLOPE_DIR__FLAT				3
#define SLOPE_DIR__UP_TO_FLAT		4
#define SLOPE_DIR__DOWN_TO_FLAT		5

int CObj__EPD_STD::
Fnc__EPD_DETECT__CheckSlope(CII_OBJECT__VARIABLE* p_variable,
							CII_OBJECT__ALARM* p_alarm)
{
	CString str__slope_count;
	CString str__slope_direction;
	CString str__validation_time;

	sCH__CFG_PARAMETER_SLOPE_COUNT->Get__DATA(str__slope_count);
	sCH__CFG_PARAMETER_SLOPE_DIRECTION->Get__DATA(str__slope_direction);
	sCH__CFG_PARAMETER_VALIDATION_TIME->Get__DATA(str__validation_time);

	double value__slope_count = atof(str__slope_count);
	double value__validation_time = atof(str__validation_time);

	if(value__slope_count < 0)		
	{
		value__slope_count = - value__slope_count;
	}

	// ...
	int slope_dir_mode = -1;

	if(str__slope_direction.CompareNoCase(STR__UP) == 0)
	{
		slope_dir_mode = SLOPE_DIR__UP;
	}
	else if(str__slope_direction.CompareNoCase(STR__DOWN) == 0)
	{
		slope_dir_mode = SLOPE_DIR__DOWN;
		value__slope_count = - value__slope_count;
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
	double  epd_data = 0;
	CString str_data;

	double cur_data = 0;
	double pre_data = 0;
	int n_count = 0;
	
	int success_count = 1;
	int check_count = 0;

	if(value__validation_time < 0.1)
	{
		success_count = 1;
	}
	else
	{
		success_count = (int) (value__validation_time / DEF__SAMPLING_SEC);
	}

	if(success_count < 1)
	{
		success_count = 1;
	}

	aCH__CFG_EPD_TIMEOUT_MAXIMUM->Get__DATA(str_data);
	double timeout = atof(str_data);	

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

		log_bff.Format("   Validation Time : [%s]\n", str__validation_time);
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

	SCX__TIMER_CTRL x_timer_ctrl;
	x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
	
	while(1)
	{
		// ...
		{
			double cur_sec = Get__EPD_CUR_SEC();
			
			if(cur_sec >= timeout)
			{
				break;
			}
		}

		if(x_timer_ctrl->WAIT(DEF__SAMPLING_SEC) < 0)
		{
			return -1;
		}

		// ...
		{
			epd_data = Get__IBx_SPEC_DATA();

			str_data.Format("%.1f", epd_data);
			sCH_INFO__CUR_IBx_DATA->Set__DATA(str_data);

			// ...
			{
				CString log_msg;

				log_msg.Format("EPD Data (%f)", epd_data);
				Fnc__WRITE_LOG(log_msg);
			}
		}

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

			if(slope_dir_mode == SLOPE_DIR__UP)
			{
				if(cur_slope > value__slope_count)
				{
					check_count++;

					if(check_count >= success_count)
					{
						Fnc__WRITE_LOG("OK : Fnc__EPD_DETECT__CheckSlope [Slope_Dir (UP)]");
						return 1;
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
						Fnc__WRITE_LOG("OK : Fnc__EPD_DETECT__CheckSlope [Slope_Dir (DOWN)]");
						return 1;
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
						Fnc__WRITE_LOG("OK : Fnc__EPD_DETECT__CheckSlope [Slope_Dir (FLAT)]");
						return 1;
					}
				}
				else
				{
					check_count = 0;
				}
			}
			else if(slope_dir_mode == SLOPE_DIR__UP_TO_FLAT)
			{
				if((cur_slope > 0) && (cur_slope <= value__slope_count))	
				{
					check_count++;

					if(check_count >= success_count)
					{
						Fnc__WRITE_LOG("OK : Fnc__EPD_DETECT__CheckSlope [Slope_Dir (UP_TO_FLAT)]");
						return 1;
					}
				}
				else
				{
					check_count = 0;
				}
			}
			else if(slope_dir_mode == SLOPE_DIR__DOWN_TO_FLAT)
			{
				if((cur_slope < 0) && (cur_slope <= value__slope_count))
				{
					check_count++;

					if(check_count >= success_count)
					{
						Fnc__WRITE_LOG("OK : Fnc__EPD_DETECT__CheckSlope [Slope_Dir (DOWN_TO_FLAT)]");

						// ...
						{
							aCH__CFG_EPD_TIMEOUT_MINIMUM->Get__DATA(str_data);
							double min_sec = atof(str_data);
							double cur_sec = Get__EPD_CUR_SEC();

							if(min_sec > cur_sec)
							{
								CString alm_msg;
								CString alm_bff;
								
								alm_msg  = "During checking EPD's CheckSlope Algorithm, \n";
								alm_msg += "Minimum Timeout occurred !\n";
								
								alm_bff.Format("Minimum Timeout's value is \"%.1f\".\n", min_sec);
								alm_msg += alm_bff;

								alm_bff.Format("Detecting Time is \"%.1f\".\n", cur_sec);
								alm_msg += alm_bff;
								
								Alarm_Post__EPD_MIN_TIMEOUT(p_alarm,alm_msg);
								
								THROW__ABORT;
							}
						}
						return 1;
					}
				}
				else
				{
					check_count = 0;
				}
			}
		}
	}

	// ...
	{
		CString alarm_msg;
		CString alarm_bff;

		alarm_msg  = "During chicking EPD's CheckSlope Algorithm, \n";
		alarm_msg += "Timeout occurred !\n";

		alarm_bff.Format("Timeout's value is \"%.1f\".\n",timeout);
		alarm_msg += alarm_bff;

		Alarm_Post__EPD_MAX_TIMEOUT(p_alarm,alarm_msg);
	}
	return -1;
}
