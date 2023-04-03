#include "StdAfx.h"
#include "CObj__RTU_SERIAL.h"


//-------------------------------------------------------------------------	
int  CObj__RTU_SERIAL
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	Call__CLEAR_ALARM(p_variable, p_alarm);

	if(Call__HOME(p_variable,p_alarm) < 0)
	{
		return -1;
	}

	return Call__DOWN(p_variable,p_alarm);
}

int  CObj__RTU_SERIAL
::Call__HOME(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int r_flag = _Fnc__HOME(p_variable, p_alarm);

	// ...
	{
		doCH__CTRL_SET->Set__DATA(_IO_Cmd__IDLE);

		while(1)
		{
			if(sCH__INFO_MOTOR_IDLE->Check__DATA(STR__ON) > 0)
			{
				break;
			}

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				break;
			}

			Sleep(50);
		}
	}
	return r_flag;
}
int  CObj__RTU_SERIAL
::_Fnc__HOME(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
	CString ch_data;

	x_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIME_COUNT->Get__CHANNEL_NAME());
	x_timer_ctrl->STOP_ZERO();
	x_timer_ctrl->START__COUNT_UP(9999);

	// HOME.PARA ...
	{		
		double cfg_unit = aCH__CFG_CONVERSION_UNIT_PULSE_TO_MM->Get__VALUE();

		// POSITION 
		{
			double cfg__offset_mm = aCH__CFG_HOME_OFFSET_POS->Get__VALUE();
			cfg__offset_mm = -cfg__offset_mm;

			ch_data.Format("%.1f", cfg__offset_mm);
			sCH__INFO_SET_POS_MM->Set__DATA(ch_data);

			double cfg__offset_step = cfg__offset_mm / cfg_unit;
			aCH__PARA_GOTO_POS_DATA_PULSE->Set__VALUE(cfg__offset_step);
		}
		// SPEED 
		{
			double cfg_value = aCH__CFG_HOME_SPEED->Get__VALUE();
			cfg_value /= cfg_unit;
			
			aCH__PARA_GOTO_POS_SPEED->Set__VALUE(cfg_value);
		}
		// ACCELERATION
		{
			double cfg_value = aCH__CFG_HOME_ACCEL->Get__VALUE();
			cfg_value /= cfg_unit;

			aCH__PARA_GOTO_POS_ACCEL->Set__VALUE(cfg_value);
		}
		// DECELERATION
		{
			double cfg_value = aCH__CFG_HOME_DECEL->Get__VALUE();
			cfg_value /= cfg_unit;

			aCH__PARA_GOTO_POS_DECEL->Set__VALUE(cfg_value);
		}
	}

	if(iActive__SIM_MODE > 0)
	{
		ch_data = aCH__PARA_GOTO_POS_DATA_PULSE->Get__STRING();
		sCH__INFO_SET_POS_STEP->Set__DATA(ch_data);

		sCH__INFO_MOTOR_IDLE->Set__DATA(STR__OFF);

		sCH__INFO_DRV_BIT05_READY->Set__DATA(STR__OFF);
		sCH__INFO_DRV_BIT13_MOVE->Set__DATA(STR__ON);
		sCH__INFO_DRV_BIT08_BUSY->Set__DATA(STR__ON);

		sCH__INFO_DRV_BIT04_HOME->Set__DATA(STR__OFF);
		sCH__INFO_DRV_BIT14_IN_POS->Set__DATA(STR__OFF);
	}

	// ...
	{
		doCH__PARA_GOTO_SET->Set__DATA(STR__ON);
		doCH__CTRL_SET->Set__DATA(_IO_Cmd__HOME);
		
		Sleep(10);

		siCH__DRIVER_STS__MANUAL->Get__STRING();
	}

	while(1)
	{
		Sleep(50);

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			Fnc__GOTO_POS_STOP(p_variable,p_alarm);

			// ...
			{
				CString log_msg = "Aborted By User ...";

				Write__APP_LOG(log_msg);
			}
			return -1;
		}

		if((sCH__INFO_DRV_BIT04_HOME->Check__DATA(STR__ON)   > 0)
		&& (sCH__INFO_DRV_BIT14_IN_POS->Check__DATA(STR__ON) > 0))
		{
			break;
		}

		double cfg_sec = aCH__CFG_HOME_TIMEOUT->Get__VALUE();
		if(x_timer_ctrl->Get__CURRENT_TIME() > cfg_sec)
		{
			Fnc__GOTO_POS_STOP(p_variable,p_alarm);

			// ...
			{
				CString log_msg = "Call__HOME() - Timeout ! \n";

				Write__APP_LOG(log_msg);
			}

			// ...
			{
				int alarm_id = ALID__HOME_TIMEOUT;

				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format(" * %s <- %.1f (sec) \n", 
								aCH__CFG_HOME_TIMEOUT->Get__CHANNEL_NAME(),
								cfg_sec);

				alm_bff.Format(" * %s <- %s \n", 
								sCH__INFO_MOTOR_IDLE->Get__CHANNEL_NAME(),
								sCH__INFO_MOTOR_IDLE->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format(" * %s <- %s \n", 
								sCH__INFO_DRV_BIT04_HOME->Get__CHANNEL_NAME(),
								sCH__INFO_DRV_BIT04_HOME->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alarm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
			}
			return -2;
		}

		if(iActive__SIM_MODE > 0)
		{
			double sim_sec = aCH__SIM_HOME_TIME->Get__VALUE();
			if(x_timer_ctrl->Get__CURRENT_TIME() >= sim_sec)
			{
				sCH__INFO_DRV_BIT04_HOME->Set__DATA(STR__ON);
				sCH__INFO_DRV_BIT14_IN_POS->Set__DATA(STR__ON);

				sCH__INFO_DRV_BIT05_READY->Set__DATA(STR__ON);
				sCH__INFO_DRV_BIT13_MOVE->Set__DATA(STR__OFF);
				sCH__INFO_DRV_BIT08_BUSY->Set__DATA(STR__OFF);
			}
		}
	}
	return 1;
}

int  CObj__RTU_SERIAL
::Call__DOWN(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int p_index;

	// UP -> MIDDLE.UP
	if(Check__TRANSFER_POS__MORE_THAN__MIDDLE_UP() > 0)
	{
		p_index = TRANSFER_POS__MIDDLE_UP;
		Update__GOTO_POS_OF_MOVE_POS(p_index);

		p_index = TRANSFER_POS__UP;
		Update__GOTO_POS_OF_MOVE_SPEED(p_index);

		if(Fnc__GOTO_POS_START(p_variable,p_alarm) < 0)
		{
			return -1;
		}
	}

	// MIDDLE.UP -> MIDDLE.DOWN
	if(Check__TRANSFER_POS__MORE_THAN__MIDDLE_DOWN() > 0)
	{
		p_index = TRANSFER_POS__MIDDLE_DOWN;
		Update__GOTO_POS_OF_MOVE_POS(p_index);
		Update__GOTO_POS_OF_MOVE_SPEED(p_index);

		if(Fnc__GOTO_POS_START(p_variable,p_alarm) < 0)
		{
			return -1;
		}
	}

	// MIDDLE.DOWN -> DOWN
	{
		p_index = TRANSFER_POS__DOWN;
		Update__GOTO_POS_OF_MOVE_POS(p_index);
		Update__GOTO_POS_OF_MOVE_SPEED(p_index);

		if(Fnc__GOTO_POS_START(p_variable,p_alarm) < 0)
		{
			return -3;
		}
	}
	return 1;
}

int  CObj__RTU_SERIAL
::Call__UP(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(Fnc__CHECK_CHUCKING(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	// ...
	int p_index;

	// DOWN -> MIDDLE.DOWN
	if(Check__TRANSFER_POS__LESS_THAN__MIDDLE_DOWN() > 0)
	{
		p_index = TRANSFER_POS__MIDDLE_DOWN;
		Update__GOTO_POS_OF_MOVE_POS(p_index);

		p_index = TRANSFER_POS__DOWN;
		Update__GOTO_POS_OF_MOVE_SPEED(p_index);

		if(Fnc__GOTO_POS_START(p_variable,p_alarm) < 0)
		{
			return -1;
		}
	}

	// MIDDLE.DOWN -> MIDDLE.UP
	if(Check__TRANSFER_POS__LESS_THAN__MIDDLE_UP() > 0)
	{
		p_index = TRANSFER_POS__MIDDLE_UP;
		Update__GOTO_POS_OF_MOVE_POS(p_index);
		Update__GOTO_POS_OF_MOVE_SPEED(p_index);

		if(Fnc__GOTO_POS_START(p_variable,p_alarm) < 0)
		{
			return -1;
		}
	}

	// MIDDLE.UP -> UP
	{
		p_index = TRANSFER_POS__UP;
		Update__GOTO_POS_OF_MOVE_POS(p_index);
		Update__GOTO_POS_OF_MOVE_SPEED(p_index);

		if(Fnc__GOTO_POS_START(p_variable,p_alarm) < 0)
		{
			return -3;
		}
	}
	return 1;
}


// ...
int  CObj__RTU_SERIAL
::Call__MOVE_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if((sCH__TEACH_ACTIVE_JOG_UP->Check__DATA(STR__YES)   > 0)
	|| (sCH__TEACH_ACTIVE_JOG_DOWN->Check__DATA(STR__YES) > 0))
	{
		sCH__TEACH_ACTIVE_JOG_UP->Set__DATA("");
		sCH__TEACH_ACTIVE_JOG_DOWN->Set__DATA("");

		return Fnc__TEACH_JOG_STOP(p_variable,p_alarm);
	}

	return Fnc__GOTO_POS_STOP(p_variable,p_alarm);
}

// ...
int  CObj__RTU_SERIAL
::Call__TEACH_ABS_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int up_mode)
{
	Update__ABS_OF_TEACHING_PROPERTY(up_mode);

	if(up_mode > 0)			sCH__TEACH_ACTIVE_ABS_UP->Set__DATA(STR__YES);
	else					sCH__TEACH_ACTIVE_ABS_DOWN->Set__DATA(STR__YES);

	int rc = Fnc__GOTO_POS_START(p_variable,p_alarm);

	sCH__TEACH_ACTIVE_ABS_UP->Set__DATA("");
	sCH__TEACH_ACTIVE_ABS_DOWN->Set__DATA("");

	return rc;
}

int  CObj__RTU_SERIAL
::Update__JOG_OF_TEACHING_PROPERTY()
{
	double cfg_value = 0.0;

	cfg_value = aCH__CFG_TEACH_JOG_SPEED->Get__VALUE();
	aCH__PARA_GOTO_POS_SPEED->Set__VALUE(cfg_value);

	cfg_value = aCH__CFG_TEACH_JOG_ACCEL->Get__VALUE();
	aCH__PARA_GOTO_POS_ACCEL->Set__VALUE(cfg_value);

	cfg_value = aCH__CFG_TEACH_JOG_DECEL->Get__VALUE();
	aCH__PARA_GOTO_POS_DECEL->Set__VALUE(cfg_value);

	return 1;
}
int  CObj__RTU_SERIAL
::Update__ABS_OF_TEACHING_PROPERTY(const int up_mode)
{
	double cfg_unit  = aCH__CFG_CONVERSION_UNIT_PULSE_TO_MM->Get__VALUE();
	if(cfg_unit < 0.001)		cfg_unit = 0.001;		

	double cfg_value = 0.0;

	cfg_value = aCH__CFG_TEACH_ABS_SPEED->Get__VALUE();
	cfg_value /= cfg_unit;
	aCH__PARA_GOTO_POS_SPEED->Set__VALUE(cfg_value);

	cfg_value = aCH__CFG_TEACH_ABS_ACCEL->Get__VALUE();
	cfg_value /= cfg_unit;
	aCH__PARA_GOTO_POS_ACCEL->Set__VALUE(cfg_value);

	cfg_value = aCH__CFG_TEACH_ABS_DECEL->Get__VALUE();
	cfg_value /= cfg_unit;
	aCH__PARA_GOTO_POS_DECEL->Set__VALUE(cfg_value);

	// ...
	double trg_pos    = 0.0;
	double goto_pulse = 0.0;

	CString ch_data = sCH__INFO_CUR_POS_MM->Get__STRING();
	double cur_pos = atof(ch_data);

	if(up_mode > 0)
	{
		double goto_pos = aCH__CFG_GOTO_POS_UP_ABS_POS->Get__VALUE();
		trg_pos = cur_pos + goto_pos;
	}
	else
	{
		double goto_pos = aCH__CFG_GOTO_POS_DOWN_ABS_POS->Get__VALUE();
		trg_pos = cur_pos - goto_pos;
	}

	goto_pulse = trg_pos / cfg_unit;
	aCH__PARA_GOTO_POS_DATA_PULSE->Set__VALUE(goto_pulse);
	return 1;
}

int  CObj__RTU_SERIAL
::Update__GOTO_POS_OF_PROC_POS(const int pos_index)
{
	double cfg_unit  = aCH__CFG_CONVERSION_UNIT_PULSE_TO_MM->Get__VALUE();
	if(cfg_unit < 0.001)		cfg_unit = 0.001;		

	double cfg_value = 0.0;

	cfg_value = aCH__CFG_PROC_POS_X_DATA_POS[pos_index]->Get__VALUE();
	cfg_value /= cfg_unit;
	aCH__PARA_GOTO_POS_DATA_PULSE->Set__VALUE(cfg_value);

	return 1;
}
int  CObj__RTU_SERIAL
::Update__GOTO_POS_OF_PROC_SPEED(const int pos_index)
{
	double cfg_unit  = aCH__CFG_CONVERSION_UNIT_PULSE_TO_MM->Get__VALUE();
	if(cfg_unit < 0.001)		cfg_unit = 0.001;		

	double cfg_value = 0.0;

	cfg_value = aCH__CFG_PROC_POS_X_SPEED[pos_index]->Get__VALUE();
	cfg_value /= cfg_unit;
	aCH__PARA_GOTO_POS_SPEED->Set__VALUE(cfg_value);

	cfg_value = aCH__CFG_PROC_POS_X_ACCEL[pos_index]->Get__VALUE();
	cfg_value /= cfg_unit;
	aCH__PARA_GOTO_POS_ACCEL->Set__VALUE(cfg_value);

	cfg_value = aCH__CFG_PROC_POS_X_DECEL[pos_index]->Get__VALUE();
	cfg_value /= cfg_unit;
	aCH__PARA_GOTO_POS_DECEL->Set__VALUE(cfg_value);

	return 1;
}

int  CObj__RTU_SERIAL
::Update__GOTO_POS_OF_MOVE_POS(const int pos_index)
{
	CString ch_data;

	double cfg_unit  = aCH__CFG_CONVERSION_UNIT_PULSE_TO_MM->Get__VALUE();
	if(cfg_unit < 0.001)		cfg_unit = 0.001;		

	double cfg_value = 0.0;

	cfg_value = aCH__CFG_TRANSFER_POS_X_DATA_POS[pos_index]->Get__VALUE();
	ch_data.Format("%.1f", cfg_value);
	sCH__INFO_SET_POS_MM->Set__DATA(ch_data);

	cfg_value /= cfg_unit;
	aCH__PARA_GOTO_POS_DATA_PULSE->Set__VALUE(cfg_value);

	
	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "\n";
		log_msg += "Update__GOTO_POS_OF_MOVE_POS() Started ...";
		log_msg += "\n";

		log_bff.Format("  * pos_index <- %1d \n", pos_index);
		log_msg += log_bff;

		CString ch_name = aCH__PARA_GOTO_POS_DATA_PULSE->Get__CHANNEL_NAME();
		CString ch_data;
		aCH__PARA_GOTO_POS_DATA_PULSE->Get__DATA(ch_data);

		log_bff.Format("  * %s <- %s \n", ch_name,ch_data), 
		log_msg += log_bff;

		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
}
int  CObj__RTU_SERIAL
::Update__GOTO_POS_OF_MOVE_SPEED(const int pos_index)
{
	double cfg_unit  = aCH__CFG_CONVERSION_UNIT_PULSE_TO_MM->Get__VALUE();
	if(cfg_unit < 0.001)		cfg_unit = 0.001;		

	double cfg_value = 0.0;

	cfg_value = aCH__CFG_TRANSFER_POS_X_SPEED[pos_index]->Get__VALUE();
	cfg_value /= cfg_unit;
	aCH__PARA_GOTO_POS_SPEED->Set__VALUE(cfg_value);

	cfg_value = aCH__CFG_TRANSFER_POS_X_ACCEL[pos_index]->Get__VALUE();
	cfg_value /= cfg_unit;
	aCH__PARA_GOTO_POS_ACCEL->Set__VALUE(cfg_value);

	cfg_value = aCH__CFG_TRANSFER_POS_X_DECEL[pos_index]->Get__VALUE();
	cfg_value /= cfg_unit;
	aCH__PARA_GOTO_POS_DECEL->Set__VALUE(cfg_value);

	return 1;
}

int  CObj__RTU_SERIAL
::Fnc__GOTO_POS_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int r_flag = Sub__GOTO_POS_START(p_variable, p_alarm);

	// ...
	{
		doCH__CTRL_SET->Set__DATA(_IO_Cmd__IDLE);

		while(1)
		{
			if(sCH__INFO_MOTOR_IDLE->Check__DATA(STR__ON) > 0)
			{
				break;
			}

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				break;
			}

			Sleep(50);
		}
	}

	return r_flag;
}
int  CObj__RTU_SERIAL
::Sub__GOTO_POS_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
	CString ch_data;

	x_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIME_COUNT->Get__CHANNEL_NAME());
	x_timer_ctrl->STOP_ZERO();
	x_timer_ctrl->START__COUNT_UP(9999);

	double cfg_unit  = aCH__CFG_CONVERSION_UNIT_PULSE_TO_MM->Get__VALUE();
	if(cfg_unit < 0.001)		cfg_unit = 0.001;		

	double cfg_offset = aCH__CFG_HOME_ZERO_BASE_OFFSET->Get__VALUE();
	double offset_pulse = cfg_offset / cfg_unit;
	
	double cur_pulse = aCH__PARA_GOTO_POS_DATA_PULSE->Get__VALUE();
	cur_pulse += offset_pulse;

	ch_data.Format("%.0f", cur_pulse);
	sCH__INFO_SET_POS_STEP->Set__DATA(ch_data);

	if(iActive__SIM_MODE > 0)
	{
		sCH__INFO_DRV_BIT04_HOME->Set__DATA(STR__OFF);
		sCH__INFO_DRV_BIT14_IN_POS->Set__DATA(STR__OFF);

		sCH__INFO_DRV_BIT05_READY->Set__DATA(STR__OFF);
		sCH__INFO_DRV_BIT13_MOVE->Set__DATA(STR__ON);
		sCH__INFO_DRV_BIT08_BUSY->Set__DATA(STR__ON);

		sCH__INFO_MOTOR_IDLE->Set__DATA(STR__OFF);
	}

	// ...
	{
		doCH__PARA_GOTO_SET->Set__DATA(STR__ON);
		doCH__CTRL_SET->Set__DATA(_IO_Cmd__GOTO);

		Sleep(10);

		siCH__DRIVER_STS__MANUAL->Get__STRING();
	}

	while(1)
	{
		Sleep(50);

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			Fnc__GOTO_POS_STOP(p_variable,p_alarm);

			// ...
			{
				CString log_msg = "Aborted By User ...";

				Write__APP_LOG(log_msg);
			}
			return -1;
		}

		if(sCH__INFO_DRV_BIT14_IN_POS->Check__DATA(STR__ON) > 0)
		{
			break;
		}

		// CHECK : TIMEOUT ...
		{
			double cfg_sec = aCH__CFG_MOVING_TIMEOUT->Get__VALUE();
		
			if(x_timer_ctrl->Get__CURRENT_TIME() > cfg_sec)
			{
				Fnc__GOTO_POS_STOP(p_variable,p_alarm);

				// ...
				{
					CString log_msg = "Fnc__GOTO_POS_START() - Timeout ! \n";

					Write__APP_LOG(log_msg);
				}
				
				// ...
				{
					int alarm_id = ALID__MOVING_TIMEOUT;

					CString alm_msg;
					CString alm_bff;
					CString r_act;

					alm_msg.Format(" * %s <- %.1f (sec) \n", 
									aCH__CFG_MOVING_TIMEOUT->Get__CHANNEL_NAME(),
									cfg_sec);

					alm_bff.Format(" * %s <- %s \n", 
									sCH__INFO_MOTOR_IDLE->Get__CHANNEL_NAME(),
									sCH__INFO_MOTOR_IDLE->Get__STRING());
					alm_msg += alm_bff;

					alm_bff.Format(" * %s <- %s \n", 
									sCH__INFO_DRV_BIT14_IN_POS->Get__CHANNEL_NAME(),
									sCH__INFO_DRV_BIT14_IN_POS->Get__STRING());
					alm_msg += alm_bff;

					p_alarm->Check__ALARM(alarm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
				}
				return -2;
			}
		}

		if(iActive__SIM_MODE > 0)
		{
			double sim_sec = aCH__SIM_MOVE_TIME->Get__VALUE();

			if(x_timer_ctrl->Get__CURRENT_TIME() >= sim_sec)
			{
				sCH__INFO_DRV_BIT05_READY->Set__DATA(STR__ON);
				sCH__INFO_DRV_BIT13_MOVE->Set__DATA(STR__OFF);
				sCH__INFO_DRV_BIT08_BUSY->Set__DATA(STR__OFF);

				sCH__INFO_DRV_BIT14_IN_POS->Set__DATA(STR__ON);
			}
		}
	}
	return 1;
}

int  CObj__RTU_SERIAL
::Fnc__GOTO_POS_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		doCH__CTRL_SET->Set__DATA(_IO_Cmd__STOP);

		Sleep(500);
	}

	if(iActive__SIM_MODE > 0)
	{
		sCH__INFO_DRV_BIT05_READY->Set__DATA(STR__ON);
		sCH__INFO_DRV_BIT13_MOVE->Set__DATA(STR__OFF);
		sCH__INFO_DRV_BIT08_BUSY->Set__DATA(STR__OFF);
	}	
	return 1;
}


// ...
int  CObj__RTU_SERIAL
::Call__TEACH_JOG_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int plus_mode)
{
	Update__JOG_OF_TEACHING_PROPERTY();

	return Fnc__TEACH_JOG_START(p_variable,p_alarm, plus_mode);
}

int  CObj__RTU_SERIAL
::Fnc__TEACH_JOG_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int plus_mode)
{
	if(plus_mode > 0)		sCH__TEACH_ACTIVE_JOG_UP->Set__DATA(STR__YES);
	else					sCH__TEACH_ACTIVE_JOG_DOWN->Set__DATA(STR__YES);

	// ...
	{
		doCH__PARA_GOTO_SET->Set__DATA(STR__ON);

		if(plus_mode > 0)		doCH__CTRL_SET->Set__DATA(_IO_Cmd__JOG_UP);
		else					doCH__CTRL_SET->Set__DATA(_IO_Cmd__JOG_DOWN);

		Sleep(10);

		siCH__DRIVER_STS__MANUAL->Get__STRING();
	}

	while(1)
	{
		Sleep(50);

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			Fnc__TEACH_JOG_STOP(p_variable,p_alarm);
			return -1;
		}
	}
	return 1;
}
int  CObj__RTU_SERIAL
::Fnc__TEACH_JOG_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		sCH__TEACH_ACTIVE_JOG_UP->Set__DATA("");
		sCH__TEACH_ACTIVE_JOG_DOWN->Set__DATA("");

		doCH__CTRL_SET->Set__DATA(_IO_Cmd__IDLE);
	}

	if(iActive__SIM_MODE > 0)
	{
		sCH__INFO_DRV_BIT05_READY->Set__DATA(STR__ON);
		sCH__INFO_DRV_BIT13_MOVE->Set__DATA(STR__OFF);
		sCH__INFO_DRV_BIT08_BUSY->Set__DATA(STR__OFF);
	}
	return 1;
}


// ...
int  CObj__RTU_SERIAL
::Call__MIDDLE_DOWN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(Fnc__CHECK_CHUCKING(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	// ...
	int p_index;

	// DOWN -> MIDDLE.DOWN
	if(Check__TRANSFER_POS__LESS_THAN__MIDDLE_DOWN() > 0)
	{
		p_index = TRANSFER_POS__MIDDLE_DOWN;
		Update__GOTO_POS_OF_MOVE_POS(p_index);

		p_index = TRANSFER_POS__DOWN;
		Update__GOTO_POS_OF_MOVE_SPEED(p_index);

		return Fnc__GOTO_POS_START(p_variable,p_alarm);
	}

	// UP -> MIDDLE.UP
	if(Check__TRANSFER_POS__MORE_THAN__MIDDLE_UP() > 0)
	{
		p_index = TRANSFER_POS__MIDDLE_UP;
		Update__GOTO_POS_OF_MOVE_POS(p_index);

		p_index = TRANSFER_POS__UP;
		Update__GOTO_POS_OF_MOVE_SPEED(p_index);

		if(Fnc__GOTO_POS_START(p_variable,p_alarm) < 0)
		{
			return -1;
		}
	}

	// MIDDLE.UP -> MIDDLE.DOWN
	p_index = TRANSFER_POS__MIDDLE_DOWN;
	Update__GOTO_POS_OF_MOVE_POS(p_index);
	Update__GOTO_POS_OF_MOVE_SPEED(p_index);

	return Fnc__GOTO_POS_START(p_variable,p_alarm);
}
int  CObj__RTU_SERIAL
::Call__MIDDLE_UP(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(Fnc__CHECK_CHUCKING(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	// ...
	int p_index;

	// UP -> MIDDLE.UP
	if(Check__TRANSFER_POS__MORE_THAN__MIDDLE_UP() > 0)
	{
		p_index = TRANSFER_POS__MIDDLE_UP;
		Update__GOTO_POS_OF_MOVE_POS(p_index);

		p_index = TRANSFER_POS__UP;
		Update__GOTO_POS_OF_MOVE_SPEED(p_index);

		return Fnc__GOTO_POS_START(p_variable,p_alarm);
	}

	// DOWN -> MIDDLE.DOWN
	if(Check__TRANSFER_POS__LESS_THAN__MIDDLE_DOWN() > 0)
	{
		p_index = TRANSFER_POS__MIDDLE_DOWN;
		Update__GOTO_POS_OF_MOVE_POS(p_index);

		p_index = TRANSFER_POS__DOWN;
		Update__GOTO_POS_OF_MOVE_SPEED(p_index);

		if(Fnc__GOTO_POS_START(p_variable,p_alarm) < 0)
		{
			return -1;
		}
	}

	// MIDDLE.DOWN -> MIDDLE.UP
	p_index = TRANSFER_POS__MIDDLE_UP;
	Update__GOTO_POS_OF_MOVE_POS(p_index);
	Update__GOTO_POS_OF_MOVE_SPEED(p_index);

	return Fnc__GOTO_POS_START(p_variable,p_alarm);
}

// ...
int  CObj__RTU_SERIAL
::Call__PROC_DOWN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int p_index;

	// XXX -> PROC.MIDDLE
	if(Check__PROCESS_POS__MORE_THAN__MIDDLE() > 0)
	{
		p_index = PROC_POS__MIDDLE;		
		Update__GOTO_POS_OF_PROC_POS(p_index);

		p_index = PROC_POS__UP;		
		Update__GOTO_POS_OF_PROC_SPEED(p_index);

		if(Fnc__GOTO_POS_START(p_variable,p_alarm) < 0)
		{
			return -1;
		}
	}

	// PROC.MIDDLE
	{
		p_index = PROC_POS__DOWN;
		
		Update__GOTO_POS_OF_PROC_POS(p_index);
		Update__GOTO_POS_OF_PROC_SPEED(p_index);
	}
	return Fnc__GOTO_POS_START(p_variable,p_alarm);
}
int  CObj__RTU_SERIAL
::Call__PROC_MIDDLE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(Fnc__CHECK_CHUCKING(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	// ...
	int p_index;

	// UP -> MIDDLE
	if(Check__PROCESS_POS__MORE_THAN__MIDDLE() > 0)
	{
		p_index = PROC_POS__MIDDLE;
		Update__GOTO_POS_OF_PROC_POS(p_index);

		p_index = PROC_POS__UP;
		Update__GOTO_POS_OF_PROC_SPEED(p_index);

		return Fnc__GOTO_POS_START(p_variable,p_alarm);
	}

	// DOWN -> MIDDLE
	p_index = PROC_POS__MIDDLE;
	Update__GOTO_POS_OF_PROC_POS(p_index);
	Update__GOTO_POS_OF_PROC_SPEED(p_index);

	return Fnc__GOTO_POS_START(p_variable,p_alarm);
}
int  CObj__RTU_SERIAL
::Call__PROC_UP(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(Fnc__CHECK_CHUCKING(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	// ...
	int p_index;

	// DOWN -> MIDDLE
	if(Check__PROCESS_POS__LESS_THAN__MIDDLE() > 0)
	{
		p_index = PROC_POS__MIDDLE;
		Update__GOTO_POS_OF_PROC_POS(p_index);
		Update__GOTO_POS_OF_PROC_SPEED(p_index);

		if(Fnc__GOTO_POS_START(p_variable,p_alarm) < 0)
		{
			return -1;
		}
	}

	// MIDDLE -> UP
	p_index = PROC_POS__UP;
	Update__GOTO_POS_OF_PROC_POS(p_index);
	Update__GOTO_POS_OF_PROC_SPEED(p_index);

	return Fnc__GOTO_POS_START(p_variable,p_alarm);
}


// ...
int  CObj__RTU_SERIAL
::Call__CHECK_ALARM(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{

	return 1;
}

int  CObj__RTU_SERIAL
::Call__CLEAR_ALARM(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	doCH__CTRL_SET->Set__DATA(_IO_Cmd__ALARM_RESET);

	return 1;
}
int  CObj__RTU_SERIAL
::Call__CLEAR_SERVO_ALARM(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	doCH__CTRL_SET->Set__DATA(_IO_Cmd__ALARM_RESET);

	return 1;
}


// ...
int  CObj__RTU_SERIAL
::Call__SERVO_ON(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	doCH__CTRL_SET->Set__DATA(_IO_Cmd__SERVO_ON);

	return 1;
}

int  CObj__RTU_SERIAL
::Call__SERVO_OFF(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	doCH__CTRL_SET->Set__DATA(_IO_Cmd__SERVO_OFF);

	return 1;
}


