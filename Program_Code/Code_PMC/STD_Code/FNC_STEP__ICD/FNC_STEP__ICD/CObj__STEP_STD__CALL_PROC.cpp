#include "StdAfx.h"
#include "CObj__STEP_STD.h"
#include "CObj__STEP_STD__DEF.h"


// ...
int CObj__STEP_STD
::Call__PROC(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;
	CString log_bff;
	int i;

	CString rcp__step_msg;
	CString rcp__step_mode;
	CString rcp__step_time;

	CString rcp__apc_mode;
	CString rcp__apc_position;
	CString rcp__apc_learned_pos;
	CString rcp__apc_pressure;
	CString rcp__apc_hold_sec;

	CString rcp__mfc_x_flow[_CFG__MFC_SIZE];

	CString rcp__rf_rps_power;
	CString rcp__rf_lf_power;
	CString rcp__rf_hf_power;

	CString rcp__rf_pulse_frequency;
	CString rcp__rf_pulse_duty;
	CString rcp__rf_pulse_exec;
	CString rcp__rf_pulse_on_time;
	CString rcp__rf_pulse_off_time;
	CString rcp__rf_pulse_on_shift_time;
	CString rcp__rf_pulse_off_shift_time;

	CString rcp__mat_lf_shunt;
	CString rcp__mat_lf_series;

	CString rcp__mat_hf_shunt;
	CString rcp__mat_hf_series;

	CString rcp__esc_mode;
	CString rcp__dpc_center_pressure;
	CString rcp__dpc_edge_pressure;

	CString rcp__lift_pin_mode;

	// ...
	bool active__rcp_log = false;


	// RCP ...
	{
		sCH__RCP_STEP_MESSAGE->Get__DATA(rcp__step_msg);
		dCH__RCP_STEP_MODE->Get__DATA(rcp__step_mode);
		aCH__RCP_STEP_TIME->Get__DATA(rcp__step_time);

		// APC ...
		dCH__RCP_APC_MODE->Get__DATA(rcp__apc_mode);
		aCH__RCP_APC_POSITION->Get__DATA(rcp__apc_position);
		sCH__RCP_APC_LEARNED_POS->Get__DATA(rcp__apc_learned_pos);
		aCH__RCP_APC_PRESSURE->Get__DATA(rcp__apc_pressure);
		sCH__RCP_APC_HOLD_DELAY->Get__DATA(rcp__apc_hold_sec);

		// MFC ...
		for(i=0; i<iDATA__MFC_SIZE; i++)
		{
			rcp__mfc_x_flow[i]= sCH__RCP_GAS_FLOW_X[i]->Get__STRING();
		}

		// RF.RPS ...
		sCH__RCP_RF_RPS_POWER->Get__DATA(rcp__rf_rps_power);

		// RF.LF ...
		sCH__RCP_RF_LF_POWER->Get__DATA(rcp__rf_lf_power);

		// RF.HF ...
		sCH__RCP_RF_HF_POWER->Get__DATA(rcp__rf_hf_power);

		// RF.PULSE ...
		rcp__rf_pulse_frequency = aCH__RCP_RF_PULSE_FREQUENCY->Get__STRING();
		rcp__rf_pulse_duty = aCH__RCP_RF_PULSE_DUTY->Get__STRING();
		rcp__rf_pulse_exec = dCH__RCP_RF_PULSE_EXEC->Get__STRING();
		rcp__rf_pulse_on_time  = aCH__RCP_RF_PULSE_ON_TIME->Get__STRING();
		rcp__rf_pulse_off_time = aCH__RCP_RF_PULSE_OFF_TIME->Get__STRING();
		rcp__rf_pulse_on_shift_time  = aCH__RCP_RF_PULSE_ON_SHIFT_TIME->Get__STRING();
		rcp__rf_pulse_off_shift_time = aCH__RCP_RF_PULSE_OFF_SHIFT_TIME->Get__STRING();

		// MAT.LF ...
		sCH__RCP_MAT_LF_SHUNT->Get__DATA(rcp__mat_lf_shunt);
		sCH__RCP_MAT_LF_SERIES->Get__DATA(rcp__mat_lf_series);

		// MAT.HF ...
		sCH__RCP_MAT_HF_SHUNT->Get__DATA(rcp__mat_hf_shunt);
		sCH__RCP_MAT_HF_SERIES->Get__DATA(rcp__mat_hf_series);

		// ESC.MODE ...
		dCH__RCP_ESC_CTRL_MODE->Get__DATA(rcp__esc_mode);

		// DPC.CENTER ...
		sCH__RCP_DPC_CENTER_PRESSURE->Get__DATA(rcp__dpc_center_pressure);

		// DPC.EDGE ...
		sCH__RCP_DPC_EDGE_PRESSURE->Get__DATA(rcp__dpc_edge_pressure);

		//
		dCH__RCP_LIFT_PIN_MODE->Get__DATA(rcp__lift_pin_mode);
	}

	// LOG ...
	if(active__rcp_log)
	{
		_Fnc__PROC_LOG();
	}

	// APC.CTRL ...
	if(bActive__OBJ_CTRL__APC)
	{
		CString obj_mode;
		CString para_data;

		if(rcp__apc_mode.CompareNoCase(STR__Position) == 0)
		{
			obj_mode  = _APC_CMD__POSITION;
			para_data = rcp__apc_position;
		}
		else if(rcp__apc_mode.CompareNoCase(STR__Pressure) == 0)
		{
			obj_mode  = _APC_CMD__PRESSURE;
			para_data = rcp__apc_pressure;
		}

		double value__hold_sec = atof(rcp__apc_hold_sec);
		double value__hold_pos = atof(rcp__apc_position);
		if(value__hold_pos < 0.1)			value__hold_pos = atof(rcp__apc_learned_pos);

		APC_OBJ__Start_MODE(obj_mode,para_data, value__hold_sec,value__hold_pos);
	}

	// MFC_X.CTRL ...
	for(i=0; i<iDATA__MFC_SIZE; i++)
	{
		MFC_OBJ__Start_CONTROL(i, rcp__mfc_x_flow[i], "0");
	}

	// RF.RPS ...
	if(bActive__OBJ_CTRL__RF_RPS)
	{
		CString obj_mode;
		double set_power = atof(rcp__rf_rps_power);

		if(set_power > 0.1)				obj_mode = _RF_CMD__SET_POWER;
		else							obj_mode = _RF_CMD__OFF;

		RF_RPS_OBJ__Start_MODE(obj_mode, rcp__rf_rps_power);
	}
	// RF.PULSE ...
	if(bActive__OBJ_CTRL__RF_PULSE)
	{
		RF_PULSE_OBJ__Start_ON();
	}
	// RF.LF ...
	if(bActive__OBJ_CTRL__RF_LF)
	{
		CString obj_mode;
		double set_power = atof(rcp__rf_lf_power);

		if(set_power > 0.1)				obj_mode = _RF_CMD__SET_POWER;
		else							obj_mode = _RF_CMD__OFF;

		RF_LF_OBJ__Start_MODE(obj_mode, rcp__rf_lf_power);
	}
	// RF.HF ...
	if(bActive__OBJ_CTRL__RF_HF)
	{
		CString obj_mode;
		double set_power = atof(rcp__rf_hf_power);

		if(set_power > 0.1)				obj_mode = _RF_CMD__SET_POWER;
		else							obj_mode = _RF_CMD__OFF;

		RF_HF_OBJ__Start_MODE(obj_mode, rcp__rf_hf_power);
	}

	// MATCHER ...
	if(bActive__OBJ_CTRL__MAT_LF)
	{
		CString obj_mode = _MAT_CMD__PROC_CTRL;
		CString ch_data;

		// MAT.LF ...
		{
			sCH__RCP_MAT_LF_SHUNT->Get__DATA(ch_data);
			aEXT_CH__MAT_LF__PARA_LOAD_POS->Set__DATA(ch_data);

			sCH__RCP_MAT_LF_SERIES->Get__DATA(ch_data);
			aEXT_CH__MAT_LF__PARA_TUNE_POS->Set__DATA(ch_data);

			MAT_LF_OBJ__Start_MODE(obj_mode);
		}
		// MAT.HF ...
		{
			sCH__RCP_MAT_HF_SHUNT->Get__DATA(ch_data);
			aEXT_CH__MAT_HF__PARA_LOAD_POS->Set__DATA(ch_data);

			sCH__RCP_MAT_HF_SERIES->Get__DATA(ch_data);
			aEXT_CH__MAT_HF__PARA_TUNE_POS->Set__DATA(ch_data);

			MAT_HF_OBJ__Start_MODE(obj_mode);
		}
	}

	// ESC ...
	if(bActive__OBJ_CTRL__ESC)
	{
		CString obj_mode;
		CString ch_data;

			 if(rcp__esc_mode.CompareNoCase(STR__Chuck)    == 0)			obj_mode = _ESC_CMD__CHUCK_PROC;
		else if(rcp__esc_mode.CompareNoCase(STR__Chuck1)   == 0)			obj_mode = _ESC_CMD__CHUCK1_PROC;
		else if(rcp__esc_mode.CompareNoCase(STR__Chuck2)   == 0)			obj_mode = _ESC_CMD__CHUCK2_PROC;
		else if(rcp__esc_mode.CompareNoCase(STR__Dechuck)  == 0)			obj_mode = _ESC_CMD__DECHUCK;
		else if(rcp__esc_mode.CompareNoCase(STR__Dechuck1) == 0)			obj_mode = _ESC_CMD__DECHUCK1;
		else if(rcp__esc_mode.CompareNoCase(STR__Dechuck2) == 0)			obj_mode = _ESC_CMD__DECHUCK2;
		else if(rcp__esc_mode.CompareNoCase(STR__He_Set)   == 0)			obj_mode = _ESC_CMD__HE_SET_PROC;

		if(obj_mode.GetLength() > 0)			
		{
			// CENTER ...
			{
				sCH__RCP_DPC_CENTER_PRESSURE->Get__DATA(ch_data);
				sEXT_CH__ESC__RCP_He_CENTER_PRESSURE_SETPOINT_TORR->Set__DATA(ch_data);
			}
			// EDGE ...
			{
				sCH__RCP_DPC_EDGE_PRESSURE->Get__DATA(ch_data);
				sEXT_CH__ESC__RCP_He_EDGE_PRESSURE_SETPOINT_TORR->Set__DATA(ch_data);
			}

			ESC_OBJ__Start_MODE(obj_mode);
		}
	}

	// LIFT_PIN.CTRL ...
	if(bActive__OBJ_CTRL__LIFT_PIN)
	{
		CString obj_mode;

			 if(rcp__lift_pin_mode.CompareNoCase(STR__Down)   == 0)			obj_mode  = _PIN_CMD__DOWN;
		else if(rcp__lift_pin_mode.CompareNoCase(STR__Middle) == 0)			obj_mode  = _PIN_CMD__MIDDLE;
		else if(rcp__lift_pin_mode.CompareNoCase(STR__Up)     == 0)			obj_mode  = _PIN_CMD__UP;

		LIFT_PIN_OBJ__Start_MODE(obj_mode);
	}

	// ...
	bool active__stable_mode = false;
	bool active__fast_vac = false;

	if(rcp__step_mode.CompareNoCase(STR__Stable) == 0)
	{
		active__stable_mode = true;
	}
	else if(rcp__step_mode.CompareNoCase(STR__High_Vac) == 0)
	{
		active__fast_vac = true;
	}

	// ...
	double cfg__stable_min_sec = aCH__CFG_STEP_STABLE_MIN_SEC->Get__VALUE();

	// ...
	SCX__STEP_TIMER_CTRL x_step_timer;
	x_step_timer->START__TIMER();

	double para__step_sec = atof(rcp__step_time);
	double cur_sec  = 0.0;

	while(1)
	{
		// CHECK : STEP.ACT ...
		int cur_ctrl = Get__STEP_CTRL();

		if(cur_ctrl != _CMD_ID__START)
		{
			return cur_ctrl;
		}

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1;
		}

		if(iActive__SIM_MODE > 0)
		{
			if(dCH__CFG_STEP_ALARM_TEST_ACTIVE->Check__DATA(STR__ON) > 0)
			{
				return -2;
			}
		}

		// ERROR CHECK ...
		{
			if(MFC_OBJ__Check_ERROR() > 0)				return -111;
			if(APC_OBJ__Check_ERROR() > 0)				return -112;
			if(PT_OBJ__Check_ERROR()  > 0)				return -113;

			if(RF_RPS_OBJ__Check_ERROR()   > 0)			return -121;
			if(RF_LF_OBJ__Check_ERROR()    > 0)			return -122;
			if(RF_HF_OBJ__Check_ERROR()    > 0)			return -123;
			if(RF_PULSE_OBJ__Check_ERROR() > 0)			return -124;
		}
		// ABORTEDR CHECK ...
		{
			if(MFC_OBJ__Check_ABORTED() > 0)			return -211;
			if(APC_OBJ__Check_ABORTED() > 0)			return -212;

			if(RF_RPS_OBJ__Check_ABORTED()   > 0)		return -221;
			if(RF_LF_OBJ__Check_ABORTED()    > 0)		return -222;
			if(RF_HF_OBJ__Check_ABORTED()    > 0)		return -223;
			if(RF_PULSE_OBJ__Check_ABORTED() > 0)		return -224;
			
			if(MAT_LF_OBJ__Check_ABORTED() > 0)			return -231;
			if(MAT_HF_OBJ__Check_ABORTED() > 0)			return -232;

			if(ESC_OBJ__Check_ABORTED() > 0)			return -241;
		}

		if(active__stable_mode)
		{
			if(cur_sec >= cfg__stable_min_sec)
			{
				if(APC_OBJ__Check_STABLE() > 0)	
				{
					break;
				}
			}
		}
		else if(active__fast_vac)
		{
			if(cur_sec >= cfg__stable_min_sec)
			{
				double cur__pressure = aEXT_CH__APC_OBJ__PARA_PRESSURE->Get__VALUE();
				double ref__pressure = atof(rcp__apc_pressure);

				if(cur__pressure <= ref__pressure)
				{
					break;
				}
			}
		}

		if(cur_ctrl == _CMD_ID__START)
		{
			if(x_step_timer->Check__CURRENT_TIME(para__step_sec, cur_sec))
			{
				if((active__stable_mode)
					|| (active__fast_vac))
				{
					int alm_id = ALID__STABLE_OVERTIME;
					CString alm_msg;
					CString r_act;

					alm_msg.Format("Stable Timeout Error (%.1f sec) \n", para__step_sec);

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					return -1;
				}
				break;
			}
		}
	}

	return 1;
}

int CObj__STEP_STD
::Get__STEP_CTRL()
{
	CString cur_act = sCH__MON_STEP_EXCEPTION_ACT->Get__STRING();

	if(cur_act.CompareNoCase(_ACT_CMD__ABORT) == 0)
	{
		printf(" * Fnc__STEP() - ABORT ... \n");

		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg  = "\n";
			log_msg += "Step Exception Command ... \n";

			log_bff.Format(" * %s <- %s \n", 
				sCH__MON_STEP_EXCEPTION_ACT->Get__CHANNEL_NAME(),
				cur_act);
			log_msg += log_bff;

			xLOG_CTRL->WRITE__LOG(log_msg);		
		}
		return _CMD_ID__ABORT;
	}
	if(cur_act.CompareNoCase(_ACT_CMD__SKIP) == 0)
	{
		printf(" * Fnc__STEP() - SKIP ... \n");

		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg  = "\n";
			log_msg += "Step Exception Command ... \n";

			log_bff.Format(" * %s <- %s \n", 
				sCH__MON_STEP_EXCEPTION_ACT->Get__CHANNEL_NAME(),
				cur_act);
			log_msg += log_bff;

			xLOG_CTRL->WRITE__LOG(log_msg);		
		}
		return _CMD_ID__SKIP;
	}

	if(cur_act.CompareNoCase(_ACT_CMD__PAUSE) == 0)
	{
		printf(" * Fnc__STEP() - PAUSE ... \n");

		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg  = "\n";
			log_msg += "Step Exception Command ... \n";

			log_bff.Format(" * %s <- %s \n", 
				sCH__MON_STEP_EXCEPTION_ACT->Get__CHANNEL_NAME(),
				cur_act);
			log_msg += log_bff;

			xLOG_CTRL->WRITE__LOG(log_msg);		
		}
		return _CMD_ID__PAUSE;
	}

	return _CMD_ID__START;
}

int CObj__STEP_STD::_Fnc__PROC_LOG()
{
	CString log_msg;
	CString log_bff;

	CString ch_data;
	int i;

	log_msg  = "\n";
	log_msg += "Recipe Step-Info ... \n";

	// STEP ...
	{
		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_STEP_MESSAGE->Get__CHANNEL_NAME(),
						sCH__RCP_STEP_MESSAGE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						dCH__RCP_STEP_MODE->Get__CHANNEL_NAME(),
						dCH__RCP_STEP_MODE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_STEP_TIME->Get__CHANNEL_NAME(),
						aCH__RCP_STEP_TIME->Get__STRING());
		log_msg += log_bff;
	}

	// APC ...
	{
		log_bff.Format(" * %s <- %s \n", 
						dCH__RCP_APC_MODE->Get__CHANNEL_NAME(),
						dCH__RCP_APC_MODE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_APC_POSITION->Get__CHANNEL_NAME(),
						aCH__RCP_APC_POSITION->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_APC_LEARNED_POS->Get__CHANNEL_NAME(),
						sCH__RCP_APC_LEARNED_POS->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_APC_PRESSURE->Get__CHANNEL_NAME(),
						aCH__RCP_APC_PRESSURE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_APC_HOLD_DELAY->Get__CHANNEL_NAME(),
						sCH__RCP_APC_HOLD_DELAY->Get__STRING());
		log_msg += log_bff;
	}

	// MFC_X ...
	for(i=0; i<iDATA__MFC_SIZE; i++)
	{
		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_GAS_FLOW_X[i]->Get__CHANNEL_NAME(),
						sCH__RCP_GAS_FLOW_X[i]->Get__STRING());
		log_msg += log_bff;
	}

	// RF.RPS ...
	{
		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_RF_RPS_POWER->Get__CHANNEL_NAME(),
						sCH__RCP_RF_RPS_POWER->Get__STRING());
		log_msg += log_bff;
	}
	// RF.PULSE ...
	{
		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_RF_PULSE_FREQUENCY->Get__CHANNEL_NAME(),
						aCH__RCP_RF_PULSE_FREQUENCY->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_RF_PULSE_DUTY->Get__CHANNEL_NAME(),
						aCH__RCP_RF_PULSE_DUTY->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						dCH__RCP_RF_PULSE_EXEC->Get__CHANNEL_NAME(),
						dCH__RCP_RF_PULSE_EXEC->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_RF_PULSE_ON_TIME->Get__CHANNEL_NAME(),
						aCH__RCP_RF_PULSE_ON_TIME->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_RF_PULSE_OFF_TIME->Get__CHANNEL_NAME(),
						aCH__RCP_RF_PULSE_OFF_TIME->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_RF_PULSE_ON_SHIFT_TIME->Get__CHANNEL_NAME(),
						aCH__RCP_RF_PULSE_ON_SHIFT_TIME->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_RF_PULSE_OFF_SHIFT_TIME->Get__CHANNEL_NAME(),
						aCH__RCP_RF_PULSE_OFF_SHIFT_TIME->Get__STRING());
		log_msg += log_bff;
	}
	// RF.LF ...
	{
		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_RF_LF_POWER->Get__CHANNEL_NAME(),
						sCH__RCP_RF_LF_POWER->Get__STRING());
		log_msg += log_bff;
	}
	// RF.HF ...
	{
		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_RF_HF_POWER->Get__CHANNEL_NAME(),
						sCH__RCP_RF_HF_POWER->Get__STRING());
		log_msg += log_bff;
	}

	// MATCHER ...
	{
		// LF ...
		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_MAT_LF_SHUNT->Get__CHANNEL_NAME(),
						sCH__RCP_MAT_LF_SHUNT->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_MAT_LF_SERIES->Get__CHANNEL_NAME(),
						sCH__RCP_MAT_LF_SERIES->Get__STRING());
		log_msg += log_bff;

		// HF ...
		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_MAT_HF_SHUNT->Get__CHANNEL_NAME(),
						sCH__RCP_MAT_HF_SHUNT->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_MAT_HF_SERIES->Get__CHANNEL_NAME(),
						sCH__RCP_MAT_HF_SERIES->Get__STRING());
		log_msg += log_bff;
	}

	// ESC ...
	{
		log_bff.Format(" * %s <- %s \n", 
						dCH__RCP_ESC_CTRL_MODE->Get__CHANNEL_NAME(),
						dCH__RCP_ESC_CTRL_MODE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_DPC_CENTER_PRESSURE->Get__CHANNEL_NAME(),
						sCH__RCP_DPC_CENTER_PRESSURE->Get__STRING());
		log_msg += log_bff;
	}

	// LIFT_PIN ...
	{
		log_bff.Format(" * %s <- %s \n", 
						dCH__RCP_LIFT_PIN_MODE->Get__CHANNEL_NAME(),
						dCH__RCP_LIFT_PIN_MODE->Get__STRING());
		log_msg += log_bff;
	}

	xLOG_CTRL->WRITE__LOG(log_msg);		
	return 1;
}
