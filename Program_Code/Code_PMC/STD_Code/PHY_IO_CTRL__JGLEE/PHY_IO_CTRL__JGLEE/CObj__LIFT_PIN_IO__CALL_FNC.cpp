#include "StdAfx.h"
#include "CObj__LIFT_PIN_IO.h"



//---------------------------------------------------------------------------
int CObj__LIFT_PIN_IO
::Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(iActive__CONTROL_TYPE == _CTRL_TYPE__OBJ)
	{
		int r_flag = pLINK_OBJ__CTRL->Call__OBJECT(sLINK_MODE__INIT);
		if(r_flag < 0)			return r_flag;
	}

	if(Call__TRANSFER_DOWN(p_variable, p_alarm) < 0)
	{
		return -1;
	}

	return OBJ_AVAILABLE;
}

int CObj__LIFT_PIN_IO
::Call__UP(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
RETRY_ACTION:

	// WAP Position Check Interlock ...
	if(Fnc__CHECK_CHUCKING(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	sCH__MON_ACT_NAME->Set__DATA(" -> UP");

	if(iActive__CONTROL_TYPE == _CTRL_TYPE__OBJ)
	{
		int r_flag = pLINK_OBJ__CTRL->Call__OBJECT(sLINK_MODE__PIN_UP);
		if(r_flag < 0)			return r_flag;
	}
	else
	{
		dEXT_CH__DO_TRANSFER_PIN_UP->Set__DATA(STR__ON);		
		dEXT_CH__DO_TRANSFER_PIN_DOWN->Set__DATA(STR__OFF);		

		if(bActive__DO_MIDDLE_PIN_UP)			dEXT_CH__DO_MIDDLE_PIN_UP->Set__DATA(STR__OFF);
		if(bActive__DO_MIDDLE_PIN_DOWN)			dEXT_CH__DO_MIDDLE_PIN_DOWN->Set__DATA(STR__OFF);
	}

	if(dCH__CFG_LIFT_PIN_SENSOR_CHECK->Check__DATA(STR__NO) > 0)
	{
		return 1;
	}

	if(iActive__SIM_MODE > 0)
	{
		_Fnc__SIM_PIN_POD(true, false, false);
	}

	// ...
	double cfg__timeout_sec = aCH__CFG_LIFT_PIN_ACTION_TIMEOUT->Get__VALUE();
	
	if(cfg__timeout_sec < 1.0)		cfg__timeout_sec = 1.0;

	// ...
	{
		CString log_msg;
		log_msg.Format("Pin.Up Timeout <- %.1f (sec) ", cfg__timeout_sec);

		Fnc__WRITE_LOG(log_msg);
	}

	if(sCH__MON_LIFT_STATE->When__DATA(STR__UP, cfg__timeout_sec) <= 0)
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			// ...
			{
				CString log_msg;

				log_msg = "Aborted By User ...";

				Fnc__WRITE_LOG(log_msg);
			}
			return -1;
		}

		// ...
		{
			CString log_msg;
			log_msg.Format("During Pin Up.. Check the Lift-Up Sensor");

			Fnc__WRITE_LOG(log_msg);

			// ...
			{
				int alarm_id = ALID__PIN_LIFTER_ALARM;
				CString r_act;
		
				p_alarm->Check__ALARM(alarm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,log_msg);
			}
			return OBJ_ABORT;
		}
	}

	return OBJ_AVAILABLE;
}

int CObj__LIFT_PIN_IO
::Call__MIDDLE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm, const bool active__middle_up)
{
RETRY_ACTION:

	// WAP Position Check Interlock 
	if(Fnc__CHECK_CHUCKING(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	sCH__MON_ACT_NAME->Set__DATA(" -> MIDDLE");

	if(iActive__CONTROL_TYPE == _CTRL_TYPE__OBJ)
	{
		int r_flag = pLINK_OBJ__CTRL->Call__OBJECT(sLINK_MODE__PIN_MIDDLE);
		if(r_flag < 0)			return r_flag;
	}
	else
	{
		dEXT_CH__DO_TRANSFER_PIN_UP->Set__DATA(STR__OFF);		
		dEXT_CH__DO_TRANSFER_PIN_DOWN->Set__DATA(STR__OFF);		

		if(active__middle_up)
		{
			if(bActive__DO_MIDDLE_PIN_UP)		dEXT_CH__DO_MIDDLE_PIN_UP->Set__DATA(STR__ON);
			if(bActive__DO_MIDDLE_PIN_DOWN)		dEXT_CH__DO_MIDDLE_PIN_DOWN->Set__DATA(STR__OFF);
		}
		else
		{
			if(bActive__DO_MIDDLE_PIN_UP)		dEXT_CH__DO_MIDDLE_PIN_UP->Set__DATA(STR__OFF);
			if(bActive__DO_MIDDLE_PIN_DOWN)		dEXT_CH__DO_MIDDLE_PIN_DOWN->Set__DATA(STR__ON);
		}
	}

	if(dCH__CFG_LIFT_PIN_SENSOR_CHECK->Check__DATA(STR__NO) > 0)
	{
		return 1;
	}

	if(iActive__SIM_MODE > 0)
	{
		if(active__middle_up)		_Fnc__SIM_PIN_POD(false, false, true);
		else						_Fnc__SIM_PIN_POD(false, true,  false);	
	}

	// ...
	double cfg__timeout_sec = aCH__CFG_LIFT_PIN_ACTION_TIMEOUT->Get__VALUE();

	if(cfg__timeout_sec < 1.0)		cfg__timeout_sec = 1.0;

	// ...
	{
		CString log_msg;

		log_msg.Format("Pin.Middle Timeout <- %.1f (sec) ", cfg__timeout_sec);

		Fnc__WRITE_LOG(log_msg); 
	}

	if(sCH__MON_LIFT_STATE->When__DATA(STR__MIDDLE, cfg__timeout_sec) <= 0)
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			// ...
			{
				CString log_msg;

				log_msg = "Aborted By User ...";

				Fnc__WRITE_LOG(log_msg);
			}
			return -1;
		}

		// ...
		{
			CString log_msg;
			log_msg.Format("During Pin Middle .. Check the Lift-Middle Sensor");
		
			Fnc__WRITE_LOG(log_msg);

			// ...
			{
				int alarm_id = ALID__PIN_LIFTER_ALARM;
				CString r_act;
		
				p_alarm->Check__ALARM(alarm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,log_msg);
			}
			return OBJ_ABORT;
		}
	}

	return OBJ_AVAILABLE;
}

int CObj__LIFT_PIN_IO
::Call__TRANSFER_UP(CII_OBJECT__VARIABLE *p_variable,
					CII_OBJECT__ALARM *p_alarm)
{
RETRY_ACTION:

	if(Fnc__CHECK_CHUCKING(p_variable, p_alarm) < 0)
	{
		return -11;
	}

	sCH__MON_ACT_NAME->Set__DATA(" -> TRANSFER.UP");

	if(iActive__CONTROL_TYPE == _CTRL_TYPE__OBJ)
	{
		int r_flag = pLINK_OBJ__CTRL->Call__OBJECT(sLINK_MODE__PIN_UP);
		if(r_flag < 0)			return r_flag;
	}
	else
	{
		dEXT_CH__DO_TRANSFER_PIN_UP->Set__DATA(STR__ON);		
		dEXT_CH__DO_TRANSFER_PIN_DOWN->Set__DATA(STR__OFF);		

		if(bActive__DO_MIDDLE_PIN_UP)			dEXT_CH__DO_MIDDLE_PIN_UP->Set__DATA(STR__OFF);
		if(bActive__DO_MIDDLE_PIN_DOWN)			dEXT_CH__DO_MIDDLE_PIN_DOWN->Set__DATA(STR__OFF);
	}

	if(dCH__CFG_LIFT_PIN_SENSOR_CHECK->Check__DATA(STR__NO) > 0)
	{
		return 1;
	}

	if(iActive__SIM_MODE > 0)
	{
		_Fnc__SIM_PIN_POD(true, false, false);
	}

	// ...
	double cfg__timeout_sec = aCH__CFG_LIFT_PIN_ACTION_TIMEOUT->Get__VALUE();

	if(cfg__timeout_sec < 1.0)		cfg__timeout_sec = 1.0;

	// ...
	{
		CString log_msg;
		log_msg.Format("Pin Transfer.Up Timeout <- %.1f (sec) ", cfg__timeout_sec);

		Fnc__WRITE_LOG(log_msg);
	}

	if(sCH__MON_LIFT_STATE->When__DATA(STR__UP, cfg__timeout_sec) <= 0)
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			// ...
			{
				CString log_msg;
				log_msg = "Aborted By User ...";

				Fnc__WRITE_LOG(log_msg);
			}
			return -1;
		}

		// ...
		{
			CString log_msg;
			log_msg.Format("During Transfer_Up .. Check the Lift-Up Sensor");
			
			Fnc__WRITE_LOG(log_msg);

			// ...
			{
				int alarm_id = ALID__PIN_LIFTER_ALARM__TRANSFER;
				CString r_act;
				
				p_alarm->Check__ALARM(alarm_id, r_act);
				p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, log_msg, r_act);
				
				if(r_act.CompareNoCase("RETRY") == 0)
				{
					goto RETRY_ACTION;
				}
			}
		}
		return -21;
	}

	return 1;
}

int CObj__LIFT_PIN_IO
::Call__DOWN(CII_OBJECT__VARIABLE *p_variable,
			 CII_OBJECT__ALARM *p_alarm)
{
RETRY_ACTION:

	sCH__MON_ACT_NAME->Set__DATA(" -> DOWN");

	if(iActive__CONTROL_TYPE == _CTRL_TYPE__OBJ)
	{
		int r_flag = pLINK_OBJ__CTRL->Call__OBJECT(sLINK_MODE__PIN_DOWN);
		if(r_flag < 0)			return r_flag;
	}
	else
	{
		dEXT_CH__DO_TRANSFER_PIN_UP->Set__DATA(STR__OFF);		
		dEXT_CH__DO_TRANSFER_PIN_DOWN->Set__DATA(STR__ON);

		if(bActive__DO_MIDDLE_PIN_UP)			dEXT_CH__DO_MIDDLE_PIN_UP->Set__DATA(STR__OFF);
		if(bActive__DO_MIDDLE_PIN_DOWN)			dEXT_CH__DO_MIDDLE_PIN_DOWN->Set__DATA(STR__OFF);
	}	
	
	if(dCH__CFG_LIFT_PIN_SENSOR_CHECK->Check__DATA(STR__NO) > 0)
	{
		return 1;
	}

	if(iActive__SIM_MODE > 0)
	{
		_Fnc__SIM_PIN_POD(false, true, false);
	}

	// ...
	double cfg__timeput_sec = aCH__CFG_LIFT_PIN_ACTION_TIMEOUT->Get__VALUE();

	// ...
	{
		CString log_msg;
		log_msg.Format("Pin.Down Timeout <- %.1f (sec) ", cfg__timeput_sec);

		Fnc__WRITE_LOG(log_msg);
	}

	if(sCH__MON_LIFT_STATE->When__DATA(STR__DOWN, cfg__timeput_sec) <= 0)
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1;
		}

		// ...
		CString log_msg;
		log_msg.Format("During Down, Check the Lift-Down Sensor");
				
		Fnc__WRITE_LOG(log_msg);

		// ...
		{
			int alarm_id = ALID__PIN_LIFTER_ALARM;
			CString r_act;

			p_alarm->Check__ALARM(alarm_id, r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id, log_msg);
		}
		return OBJ_ABORT;
	}

	return OBJ_AVAILABLE;
}

int CObj__LIFT_PIN_IO
::Call__TRANSFER_DOWN(CII_OBJECT__VARIABLE *p_variable,
					  CII_OBJECT__ALARM *p_alarm)
{
RETRY_ACTION:

	sCH__MON_ACT_NAME->Set__DATA(" -> TRANSFER.DOWN");

	if(iActive__CONTROL_TYPE == _CTRL_TYPE__OBJ)
	{
		int r_flag = pLINK_OBJ__CTRL->Call__OBJECT(sLINK_MODE__PIN_DOWN);
		if(r_flag < 0)			return r_flag;
	}
	else
	{
		dEXT_CH__DO_TRANSFER_PIN_UP->Set__DATA(STR__OFF);		
		dEXT_CH__DO_TRANSFER_PIN_DOWN->Set__DATA(STR__ON);		

		if(bActive__DO_MIDDLE_PIN_UP)			dEXT_CH__DO_MIDDLE_PIN_UP->Set__DATA(STR__OFF);
		if(bActive__DO_MIDDLE_PIN_DOWN)			dEXT_CH__DO_MIDDLE_PIN_DOWN->Set__DATA(STR__OFF);
	}

	if(dCH__CFG_LIFT_PIN_SENSOR_CHECK->Check__DATA(STR__NO) > 0)
	{
		return 1;
	}

	if(iActive__SIM_MODE > 0)
	{
		_Fnc__SIM_PIN_POD(false, true, false);
	}

	// ...
	double cfg__timeout_sec = aCH__CFG_LIFT_PIN_ACTION_TIMEOUT->Get__VALUE();

	// ...
	{
		CString log_msg;
		log_msg.Format("Pin.Down Timeout <- %.1f (sec) ", cfg__timeout_sec);

		Fnc__WRITE_LOG(log_msg);
	}

	if(sCH__MON_LIFT_STATE->When__DATA(STR__DOWN, cfg__timeout_sec) <= 0)
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			// ...
			{
				CString log_msg;
				log_msg = "Aborted By User ... ";
				
				Fnc__WRITE_LOG(log_msg);
			}
			return -1;
		}

		// ...
		CString log_msg;
		log_msg.Format("During Transfer_Down, Check the sensor of Lift-Down.");
	
		Fnc__WRITE_LOG(log_msg);

		// ...
		{
			int alarm_id = ALID__PIN_LIFTER_ALARM__TRANSFER;
			CString r_act;
		
			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, log_msg, r_act);
		
			if(r_act.CompareNoCase("RETRY") == 0)
			{
				goto RETRY_ACTION;
			}
		}
		return -11;
	}

	return 1;
}

int CObj__LIFT_PIN_IO::Call__MIDDLE_UP(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	return Call__MIDDLE(p_variable,p_alarm, true);
}
int CObj__LIFT_PIN_IO::Call__MIDDLE_DOWN(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	return Call__MIDDLE(p_variable,p_alarm, false);
}

// ...
CString CObj__LIFT_PIN_IO
::Get__AVG_DATA(const int n_count,
				const double cur_data,
				const double pre_avg)
{
	double cur_avg = (pre_avg * ((n_count-1) / ((double) n_count))) + (cur_data / n_count); 

	CString str_data;
	str_data.Format("%.3f", cur_avg);

	return str_data;
}
void CObj__LIFT_PIN_IO
::Fnc__Check_MIN_MAX_DATA(const int n_count,
						  CII__VAR_STRING_CTRL* p_ch_min,
						  CII__VAR_STRING_CTRL* p_ch_max,
						  const double cur_data)
{
	CString var_data;

	if(n_count == 1)
	{
		var_data.Format("%.2f", cur_data);
		
		p_ch_min->Set__DATA(var_data);
		p_ch_max->Set__DATA(var_data);
	}
	else
	{
		double min_data;
		double max_data;

		p_ch_min->Get__DATA(var_data);
		min_data = atof(var_data);

		p_ch_max->Get__DATA(var_data);
		max_data = atof(var_data);

		if(cur_data < min_data)
		{
			var_data.Format("%.2f", cur_data);
			p_ch_min->Set__DATA(var_data);
		}
		if(cur_data > max_data)
		{
			var_data.Format("%.2f", cur_data);
			p_ch_max->Set__DATA(var_data);
		}
	}
}

int CObj__LIFT_PIN_IO
::Fnc__CYCLE_TEST(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm, 
				  const int i_cycle_mode)
{
	{
		CString file_name;
		CString log_msg;
		file_name.Format("%s_Cycle_Test.csv", sObject_Name);
		xCYCLE_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xCYCLE_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);
		xCYCLE_LOG_CTRL->DISABLE__TIME_LOG();
		log_msg ="TIME,COUNT,ACTION,ACTION_TIME";
		xCYCLE_LOG_CTRL->WRITE__LOG(log_msg);
		xCYCLE_LOG_CTRL->ENABLE__TIME_LOG();
	}

	SCX__TIMER_CTRL x_timer_ctrl;
	CString var_data;
	
	x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
	
	if(i_cycle_mode == CYCLE_MODE__UpToDown)
	{
		sCH__RESULT_MOVE_DOWN_UP_NOW_UP->Set__DATA("");
		sCH__RESULT_MOVE_DOWN_UP_AVG_UP->Set__DATA("");
		sCH__RESULT_MOVE_DOWN_UP_MIN_UP->Set__DATA("");
		sCH__RESULT_MOVE_DOWN_UP_MAX_UP->Set__DATA("");

		sCH__RESULT_MOVE_DOWN_UP_NOW_DOWN->Set__DATA("");
		sCH__RESULT_MOVE_DOWN_UP_AVG_DOWN->Set__DATA("");
		sCH__RESULT_MOVE_DOWN_UP_MIN_DOWN->Set__DATA("");
		sCH__RESULT_MOVE_DOWN_UP_MAX_DOWN->Set__DATA("");
	}
	else if(i_cycle_mode == CYCLE_MODE__MiddleToDown)
	{
		sCH__RESULT_MOVE_DOWN_MIDDLE_NOW_MIDDLE->Set__DATA("");
		sCH__RESULT_MOVE_DOWN_MIDDLE_AVG_MIDDLE->Set__DATA("");
		sCH__RESULT_MOVE_DOWN_MIDDLE_MIN_MIDDLE->Set__DATA("");
		sCH__RESULT_MOVE_DOWN_MIDDLE_MAX_MIDDLE->Set__DATA("");

		sCH__RESULT_MOVE_DOWN_MIDDLE_NOW_DOWN->Set__DATA("");
		sCH__RESULT_MOVE_DOWN_MIDDLE_AVG_DOWN->Set__DATA("");
		sCH__RESULT_MOVE_DOWN_MIDDLE_MIN_DOWN->Set__DATA("");
		sCH__RESULT_MOVE_DOWN_MIDDLE_MAX_DOWN->Set__DATA("");
	}

	if(Call__DOWN(p_variable,p_alarm) < 0)
	{
		return -101;
	}

	// ...
	aCH__UPDOWN_TEST_CFG_CYCLE_COUNT->Get__DATA(var_data);
	sCH__UPDOWN_TEST_CUR_CYCLE_COUNT->Set__DATA(var_data);
	
	int cycle_count = atoi(var_data);
	int i;
	
	for(i=0;i<cycle_count;i++)
	{
		// ...
		{
			var_data.Format("Cycle Test (%1d) - Started", i+1);
			sCH__UPDOWN_TEST_MSG->Set__DATA(var_data);
		}

		// ...
		{
			var_data.Format("%1d", (cycle_count - i - 1));
			sCH__UPDOWN_TEST_CUR_CYCLE_COUNT->Set__DATA(var_data);
		}

		// Up ...
		{
			SCX__ASYNC_TIMER_CTRL x_async_timer;

			if(i_cycle_mode == CYCLE_MODE__UpToDown)
			{
				x_async_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__RESULT_MOVE_DOWN_UP_NOW_UP->Get__CHANNEL_NAME());
			}
			else if(i_cycle_mode == CYCLE_MODE__MiddleToDown)
			{
				x_async_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__RESULT_MOVE_DOWN_MIDDLE_NOW_MIDDLE->Get__CHANNEL_NAME());
			}

			x_async_timer->START__COUNT_UP(9999);

			if(i_cycle_mode == CYCLE_MODE__UpToDown)
			{
				if(Call__UP(p_variable,p_alarm) < 0)
				{
					return -11;
				}
			}
			else if(i_cycle_mode == CYCLE_MODE__MiddleToDown)
			{
				if(Call__MIDDLE(p_variable,p_alarm) < 0)
				{
					return -12;
				}
			}

			// ...
			{
				double cur_sec = x_async_timer->Get__CURRENT_TIME();
				x_async_timer->STOP();

				double pre_avg = 0;
				int n_count = i + 1;

				if(i_cycle_mode == CYCLE_MODE__UpToDown)
				{
					sCH__RESULT_MOVE_DOWN_UP_AVG_UP->Get__DATA(var_data);
					pre_avg = atof(var_data);

					var_data = Get__AVG_DATA(n_count, cur_sec,pre_avg);
					sCH__RESULT_MOVE_DOWN_UP_AVG_UP->Set__DATA(var_data);

					// ...
					{
 						CII__VAR_STRING_CTRL* p_ch_min = sCH__RESULT_MOVE_DOWN_UP_MIN_UP.Get__PTR();
						CII__VAR_STRING_CTRL* p_ch_max = sCH__RESULT_MOVE_DOWN_UP_MAX_UP.Get__PTR();

						Fnc__Check_MIN_MAX_DATA(n_count,p_ch_min,p_ch_max,cur_sec);
					}
					// ...
					{
						CString log_msg;

						log_msg.Format(",%1d,UP,%.2f",n_count,cur_sec);
						xCYCLE_LOG_CTRL->WRITE__LOG(log_msg);
					}
				}
				else if(i_cycle_mode == CYCLE_MODE__MiddleToDown)
				{
					sCH__RESULT_MOVE_DOWN_MIDDLE_AVG_MIDDLE->Get__DATA(var_data);
					pre_avg = atof(var_data);
					
					var_data = Get__AVG_DATA(n_count, cur_sec,pre_avg);					
					sCH__RESULT_MOVE_DOWN_MIDDLE_AVG_MIDDLE->Set__DATA(var_data);

					// ...
					{
						CII__VAR_STRING_CTRL* p_ch_min = sCH__RESULT_MOVE_DOWN_MIDDLE_MIN_MIDDLE.Get__PTR();
						CII__VAR_STRING_CTRL* p_ch_max = sCH__RESULT_MOVE_DOWN_MIDDLE_MAX_MIDDLE.Get__PTR();
						
						Fnc__Check_MIN_MAX_DATA(n_count,p_ch_min,p_ch_max,cur_sec);
					}
				}
			}

			// ...
			{
				x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH__UPDOWN_TEST_CUR_UP_STAY_SEC->Get__CHANNEL_NAME());
				
				aCH__UPDOWN_TEST_CFG_UP_STAY_SEC->Get__DATA(var_data);
				double cfg_sec = atof(var_data);
				
				if(x_timer_ctrl->WAIT(cfg_sec) < 0)
				{
					return -111;
				}
			}
		}
		
		// Down ...
		{
			SCX__ASYNC_TIMER_CTRL x_async_timer;
			
			if(i_cycle_mode == CYCLE_MODE__UpToDown)
			{
				x_async_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__RESULT_MOVE_DOWN_UP_NOW_DOWN->Get__CHANNEL_NAME());
			}
			else if(i_cycle_mode == CYCLE_MODE__MiddleToDown)
			{
				x_async_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__RESULT_MOVE_DOWN_MIDDLE_NOW_DOWN->Get__CHANNEL_NAME());
			}

			x_async_timer->START__COUNT_UP(9999);

			if((i_cycle_mode == CYCLE_MODE__UpToDown)
			|| (i_cycle_mode == CYCLE_MODE__MiddleToDown))
			{
				if(Call__DOWN(p_variable,p_alarm) < 0)
				{
					return -21;
				}
			}

			// ...
			{
				double cur_sec = x_async_timer->Get__CURRENT_TIME();
				x_async_timer->STOP();

				double pre_avg = 0;
				int n_count = i + 1;

				x_async_timer->STOP();

				if(i_cycle_mode == CYCLE_MODE__UpToDown)
				{
					sCH__RESULT_MOVE_DOWN_UP_AVG_DOWN->Get__DATA(var_data);
					pre_avg = atof(var_data);
					
					var_data = Get__AVG_DATA(n_count, cur_sec,pre_avg);					
					sCH__RESULT_MOVE_DOWN_UP_AVG_DOWN->Set__DATA(var_data);

					// ...
					{
						CII__VAR_STRING_CTRL* p_ch_min = sCH__RESULT_MOVE_DOWN_UP_MIN_DOWN.Get__PTR();
						CII__VAR_STRING_CTRL* p_ch_max = sCH__RESULT_MOVE_DOWN_UP_MAX_DOWN.Get__PTR();
						
						Fnc__Check_MIN_MAX_DATA(n_count,p_ch_min,p_ch_max,cur_sec);
					}
					// ...
					{
						CString log_msg;

						log_msg.Format(",%1d,DOWN,%.2f",n_count,cur_sec);
						xCYCLE_LOG_CTRL->WRITE__LOG(log_msg);
					}
				}
				else if(i_cycle_mode == CYCLE_MODE__MiddleToDown)
				{
					sCH__RESULT_MOVE_DOWN_MIDDLE_AVG_DOWN->Get__DATA(var_data);
					pre_avg = atof(var_data);
					
					var_data = Get__AVG_DATA(n_count, cur_sec,pre_avg);					
					sCH__RESULT_MOVE_DOWN_MIDDLE_AVG_DOWN->Set__DATA(var_data);

					// ...
					{
						CII__VAR_STRING_CTRL* p_ch_min = sCH__RESULT_MOVE_DOWN_MIDDLE_MIN_DOWN.Get__PTR();
						CII__VAR_STRING_CTRL* p_ch_max = sCH__RESULT_MOVE_DOWN_MIDDLE_MAX_DOWN.Get__PTR();
						
						Fnc__Check_MIN_MAX_DATA(n_count,p_ch_min,p_ch_max,cur_sec);
					}
				}
			}

			// ...
			{
				x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH__UPDOWN_TEST_CUR_DOWN_STAY_SEC->Get__CHANNEL_NAME());
				
				aCH__UPDOWN_TEST_CFG_DOWN_STAY_SEC->Get__DATA(var_data);
				double cfg_sec = atof(var_data);
				
				if(x_timer_ctrl->WAIT(cfg_sec) < 0)
				{
					return -121;
				}
			}
		}
	}
	
	// ...
	{
		var_data.Format("Cycle Test (%1d) - Completed", cycle_count);
		sCH__UPDOWN_TEST_MSG->Set__DATA(var_data);
	}
	return 1;
}

int CObj__LIFT_PIN_IO
::Call__CYCLE_UpToDown(CII_OBJECT__VARIABLE *p_variable,
					   CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__CYCLE_TEST(p_variable,p_alarm, CYCLE_MODE__UpToDown);
}
int CObj__LIFT_PIN_IO
::Call__CYCLE_MiddleToDown(CII_OBJECT__VARIABLE *p_variable,
							   CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__CYCLE_TEST(p_variable,p_alarm, CYCLE_MODE__MiddleToDown);
}
