#include "StdAfx.h"
#include "CObj__RTU_SERIAL.h"
#include "CObj__RTU_SERIAL__DEF.h"


//------------------------------------------------------------------------------------
int  CObj__RTU_SERIAL
::Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(iActive__SIM_MODE > 0)
	{
		bActive__COMM_ONLINE = true;
	}
	else
	{
		bActive__COMM_ONLINE = false;
	}

	// ...
	CString ch_data;

	int loop_count = 0;
	int link_count = 0;
	int i;

	double pre__cfg_min = -1;
	double pre__cfg_max = -1;
	int    pre__cfg_dec = -1;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		loop_count++;
		if(loop_count > 10)			loop_count = 1;

		if(loop_count == 1)
		{
			int active__err_check = p_alarm->Check__Posted_Internal_Alarm(iLIST_ALID__PIN);

			if(active__err_check > 0)		dCH__MON_PIN_ERROR_ACTIVE->Set__DATA(STR__ON);
			else							dCH__MON_PIN_ERROR_ACTIVE->Set__DATA(STR__OFF);

			link_count++;
			if(link_count > 10)			link_count = 1;
		}

		if(iActive__SIM_MODE > 0)
		{
			// ...
			{
				ch_data = sCH__INFO_SET_POS_STEP->Get__STRING();

				sCH__INFO_MON_POS_STEP_CUR->Set__DATA(ch_data);
				sCH__INFO_CUR_POS_STEP->Set__DATA(ch_data);
			}

			// ...
			{
				double cfg_unit = aCH__CFG_CONVERSION_UNIT_PULSE_TO_MM->Get__VALUE();
				double cfg_offset = aCH__CFG_HOME_ZERO_BASE_OFFSET->Get__VALUE();

				//
				ch_data = sCH__INFO_SET_POS_STEP->Get__STRING();
				double trg_pulse = atof(ch_data);
				double trg_pos = (trg_pulse * cfg_unit) - cfg_offset;
				ch_data.Format("%.1f", trg_pos);
				sCH__INFO_SET_POS_MM->Set__DATA(ch_data);

				ch_data = sCH__INFO_CUR_POS_STEP->Get__STRING();
				double cur_pulse = atof(ch_data);
				double cur_pos = (cur_pulse * cfg_unit) - cfg_offset;
				ch_data.Format("%.1f", cur_pos);
				sCH__INFO_CUR_POS_MM->Set__DATA(ch_data);

				//
				double set_speed = aCH__PARA_GOTO_POS_SPEED->Get__VALUE();
				ch_data.Format("%.1f", set_speed);
				sCH__INFO_SET_VEL->Set__DATA(ch_data);
				sCH__INFO_CUR_VEL->Set__DATA(ch_data);
			}
		}

		Update__PIN_STATE();

		// CHECK : PIN_STATE ...
		{
			CString cur__pin_sts = sCH__MON_LIFT_PIN_INFO->Get__STRING();
			CString str__pin_sts = STR__MOVING;
			
			int s_index = - 1;

			// CHECK : MIDDLE ...
			if(s_index < 0)
			{
				s_index = cur__pin_sts.Find(STR__MIDDLE);
				if(s_index >= 0)		str__pin_sts = STR__MIDDLE;
			}

			// CHECK : DOWN ...
			if(s_index < 0)
			{
				s_index = cur__pin_sts.Find(STR__DOWN);
				if(s_index >= 0)		str__pin_sts = STR__DOWN;
			}

			// CHECK : UP ...
			if(s_index < 0)
			{
				s_index = cur__pin_sts.Find(STR__UP);
				if(s_index >= 0)		str__pin_sts = STR__UP;
			}

			// CHECK : HOME ...
			if(s_index < 0)
			{
				s_index = cur__pin_sts.Find(STR__HOME);
				if(s_index >= 0)		str__pin_sts = STR__DOWN;
			}

			sCH__MON_LIFT_PIN_STATE->Set__DATA(str__pin_sts);

			ch_data.Format("%s.%1d", str__pin_sts,link_count);
			sEXT_CH__LIFT_PIN_STATE->Set__DATA(ch_data);
		}

		// ...
		{
			double cfg_min = aCH__CFG_RANGE_POSITION_MIN->Get__VALUE();
			double cfg_max = aCH__CFG_RANGE_POSITION_MAX->Get__VALUE();
			int    cfg_dec = (int) aCH__CFG_RANGE_POSITION_DEC->Get__VALUE();

			if((pre__cfg_min != cfg_min)
			|| (pre__cfg_max != cfg_max)
			|| (pre__cfg_dec != cfg_dec))
			{
				pre__cfg_min = cfg_min;
				pre__cfg_max = cfg_max;
				pre__cfg_dec = cfg_dec;

				cfg_min = -10.0;

				aCH__CFG_GOTO_POS_UP_ABS_POS->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);
				aCH__CFG_GOTO_POS_DOWN_ABS_POS->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);

				for(i=0; i<CFG_SIZE__TRANSFER_POS; i++)		
				{
					aCH__CFG_TRANSFER_POS_X_DATA_POS[i]->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);
				}

				for(i=0; i<CFG_SIZE__PROC_POS; i++)		
				{
					aCH__CFG_PROC_POS_X_DATA_POS[i]->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);
				}
			}
		}

		//
		if(bActive__COMM_ONLINE)
		{
			sCH__MON_COMM_STS->Set__DATA(STR__ONLINE);
		}
		else
		{
			sCH__MON_COMM_STS->Set__DATA(STR__OFFLINE);
		}

		if(sCH__MON_COMM_STS->Check__DATA(STR__OFFLINE) > 0)
		{
			int alarm_id = ALID__OFFLINE_ALARM;
			CString alm_msg;
			CString	r_act;

			alm_msg  = "Please, check the communication state of ESC unit ! \n\n";
			alm_msg += sCH__INFO_DRV_PARAMETER->Get__STRING(); 

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
		}

		// Motor Idle ...
		{
			if((sCH__INFO_DRV_BIT05_READY->Check__DATA(STR__ON) > 0)
			&& (sCH__INFO_DRV_BIT13_MOVE->Check__DATA(STR__OFF) > 0)
			&& (sCH__INFO_DRV_BIT08_BUSY->Check__DATA(STR__OFF) > 0))
			{
				sCH__INFO_MOTOR_IDLE->Set__DATA(STR__ON);
			}
			else
			{
				sCH__INFO_MOTOR_IDLE->Set__DATA(STR__OFF);
			}
		}

		// State Error ...
		{
			bool active__state_err = false;

			if(sCH__INFO_DRV_BIT07_ALARM->Check__DATA(STR__ON) > 0)			active__state_err = true;
			if(sCH__INFO_DRV_BIT15_TLC->Check__DATA(STR__ON)   > 0)			active__state_err = true;

			if(active__state_err)
			{
				int alarm_id = ALID__STATE_ERROR;
				CString alm_msg;
				CString alm_bff;
				CString	r_act;

				alm_bff.Format("  * %s <- %s \n", 
								sCH__INFO_DRV_BIT07_ALARM->Get__VARIABLE_NAME(),
								sCH__INFO_DRV_BIT07_ALARM->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format("  * %s <- %s \n", 
								sCH__INFO_DRV_BIT15_TLC->Get__VARIABLE_NAME(),
								sCH__INFO_DRV_BIT15_TLC->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
			}
		}

		// ...
	}

	return 1;
}

void CObj__RTU_SERIAL
::Update__PIN_STATE()
{
	CString ch_data = sCH__INFO_CUR_POS_MM->Get__STRING();
	int cur_pos = atoi(ch_data);

	// ...
	CString str_state = STR__MOVING;

	// HOME.POS ...
	bool active__home_pos = false;

	if((sCH__INFO_DRV_BIT04_HOME->Check__DATA(STR__ON)  > 0)
	&& (sCH__INFO_DRV_BIT05_READY->Check__DATA(STR__ON) > 0))
	{
		active__home_pos = true;
	}

	if(active__home_pos)
	{
		str_state = STR__HOME;
	}
	else
	{
		// PROCESS.POS ...
		{
			int pos_index = -1;
			int i;

			for(i=0; i<CFG_SIZE__PROC_POS; i++)
			{
				int cfg_pos = (int) aCH__CFG_PROC_POS_X_DATA_POS[i]->Get__VALUE();
				if(cur_pos != cfg_pos)			continue;

					 if(i == PROC_POS__DOWN)				str_state = STR__PROC_DOWN;
				else if(i == PROC_POS__MIDDLE)				str_state = STR__PROC_MIDDLE;
				else if(i == PROC_POS__UP)					str_state = STR__PROC_UP;
				else										continue;

				pos_index = i;
				break;
			}

			for(i=0; i<CFG_SIZE__PROC_POS; i++)
			{
				if(i == pos_index)		sCH__APP_PROC_POS_X_SNS[i]->Set__DATA(STR__ON);
				else					sCH__APP_PROC_POS_X_SNS[i]->Set__DATA(STR__OFF);
			}
		}

		// TRNASFER.POS ...
		{
			int pos_index = -1;
			int i;

			for(i=0; i<CFG_SIZE__TRANSFER_POS; i++)
			{
				int cfg_pos = (int) aCH__CFG_TRANSFER_POS_X_DATA_POS[i]->Get__VALUE();

				if(cur_pos != cfg_pos)			continue;

					 if(i == TRANSFER_POS__DOWN)			str_state = STR__DOWN;
				else if(i == TRANSFER_POS__MIDDLE_DOWN)		str_state = STR__MIDDLE_DOWN;
				else if(i == TRANSFER_POS__MIDDLE_UP)		str_state = STR__MIDDLE_UP;
				else if(i == TRANSFER_POS__UP)				str_state = STR__UP;
				else										continue;

				pos_index = i;
				break;
			}

			for(i=0; i<CFG_SIZE__TRANSFER_POS; i++)
			{
				if(i == pos_index)		sCH__APP_TRANSFER_POS_X_SNS[i]->Set__DATA(STR__ON);
				else					sCH__APP_TRANSFER_POS_X_SNS[i]->Set__DATA(STR__OFF);
			}
		}
	}

	sCH__MON_LIFT_PIN_INFO->Set__DATA(str_state);
}

// TRANSFER : XXX_POS -> DOWN
int CObj__RTU_SERIAL
::Check__TRANSFER_POS__MORE_THAN__MIDDLE_UP()
{
	int db_index = TRANSFER_POS__MIDDLE_UP;
	int cfg_pos  = (int) aCH__CFG_TRANSFER_POS_X_DATA_POS[db_index]->Get__VALUE();

	if(cfg_pos < 1)				return -1;

	CString ch_data = sCH__INFO_CUR_POS_MM->Get__STRING();
	int cur_pos = atoi(ch_data);

	if(cur_pos > cfg_pos)		return 1;

	return -1;
}
int  CObj__RTU_SERIAL
::Check__TRANSFER_POS__MORE_THAN__MIDDLE_DOWN()
{
	int db_index = TRANSFER_POS__MIDDLE_DOWN;
	int cfg_pos  = (int) aCH__CFG_TRANSFER_POS_X_DATA_POS[db_index]->Get__VALUE();

	if(cfg_pos < 1)				return -1;

	CString ch_data = sCH__INFO_CUR_POS_MM->Get__STRING();
	int cur_pos = atoi(ch_data);

	if(cur_pos > cfg_pos)		return 1;

	return -1;
}

// TRANSFER : XXX_POS -> UP
int  CObj__RTU_SERIAL
::Check__TRANSFER_POS__LESS_THAN__MIDDLE_DOWN()
{
	int db_index = TRANSFER_POS__MIDDLE_DOWN;
	int cfg_pos  = (int) aCH__CFG_TRANSFER_POS_X_DATA_POS[db_index]->Get__VALUE();

	if(cfg_pos < 1)				return -1;

	CString ch_data = sCH__INFO_CUR_POS_MM->Get__STRING();
	int cur_pos = atoi(ch_data);

	if(cur_pos < cfg_pos)		return 1;

	return -1;
}
int  CObj__RTU_SERIAL
::Check__TRANSFER_POS__LESS_THAN__MIDDLE_UP()
{
	int db_index = TRANSFER_POS__MIDDLE_UP;
	int cfg_pos  = (int) aCH__CFG_TRANSFER_POS_X_DATA_POS[db_index]->Get__VALUE();

	if(cfg_pos < 1)				return -1;

	CString ch_data = sCH__INFO_CUR_POS_MM->Get__STRING();
	int cur_pos = atoi(ch_data);

	if(cur_pos < cfg_pos)		return 1;

	return -1;
}

// PROCESS : XXX_POS -> DOWN
int CObj__RTU_SERIAL
::Check__PROCESS_POS__MORE_THAN__MIDDLE()
{
	int db_index = PROC_POS__MIDDLE;
	int cfg_pos  = (int) aCH__CFG_PROC_POS_X_DATA_POS[db_index]->Get__VALUE();

	if(cfg_pos < 1)				return -1;

	CString ch_data = sCH__INFO_CUR_POS_MM->Get__STRING();
	int cur_pos = atoi(ch_data);

	if(cur_pos > cfg_pos)		return 1;

	return -1;
}

// PROCESS : XXX_POS -> UP
int CObj__RTU_SERIAL
::Check__PROCESS_POS__LESS_THAN__MIDDLE()
{
	int db_index = PROC_POS__MIDDLE;
	int cfg_pos  = (int) aCH__CFG_PROC_POS_X_DATA_POS[db_index]->Get__VALUE();

	if(cfg_pos < 1)				return -1;

	CString ch_data = sCH__INFO_CUR_POS_MM->Get__STRING();
	int cur_pos = atoi(ch_data);

	if(cur_pos < cfg_pos)		return 1;

	return -1;
}
