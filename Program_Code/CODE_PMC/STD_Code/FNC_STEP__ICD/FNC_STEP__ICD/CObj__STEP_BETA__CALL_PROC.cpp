#include "StdAfx.h"
#include "CObj__STEP_BETA.h"
#include "CObj__STEP_BETA__DEF.h"


// ...
int CObj__STEP_BETA
::Call__PROC(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;
	CString log_bff;

	CString ch_data;
	int i;

	CString rcp__step_msg;
	CString rcp__step_mode;
	CString rcp__step_time;
	CString rcp__step_overetch_per;

	CString rcp__apc_mode;
	CString rcp__apc_pressure_torr;
	CString rcp__apc_position;
	CString rcp__apc_learned_pos;
	CString rcp__apc_hold_sec;

	CString rcp__frc_center;
	
	CString rcp__mfc_x_flow[_CFG__MFC_SIZE];

	CString rcp__rf_rps_power;

	CString rcp__rf_lf_power;
	CString rcp__rf_lf_mode;

	CString rcp__rf_hf_power;
	CString rcp__rf_hf_p2;
	CString rcp__rf_hf_mode;

	CString rcp__rf_pulse_frequency;
	CString rcp__rf_pulse_duty;
	CString rcp__rf_pulse_exec;
	CString rcp__rf_pulse_on_shift_time;
	CString rcp__rf_pulse_off_shift_time;

	//
	CString rcp__mat_lf_shunt;
	CString rcp__mat_lf_series;

	CString rcp__mat_lf_learned_shunt;
	CString rcp__mat_lf_learned_series;

	//
	CString rcp__mat_hf_shunt;
	CString rcp__mat_hf_series;

	CString rcp__mat_hf_learned_shunt;
	CString rcp__mat_hf_learned_series;

	//
	CString rcp__esc_mode;
	CString rcp__dpc_center_pressure;
	CString rcp__dpc_edge_pressure;

	CString rcp__lift_pin_mode;

	//
	CString rcp__epd_mode;
	CString rcp__epd_value_to_change;
	CString rcp__epd_percent_to_change;

	CString rcp__epd_delay_time;
	CString rcp__epd_normalize_time;

	CString rcp__epd_min_time;
	CString rcp__epd_max_time;

	CString rcp__epd_min_threshold;
	CString rcp__epd_max_threshold;

	CString rcp__epd_slope_value;
	CString rcp__epd_slope_type;
	CString rcp__epd_valid_time;
	//


	// ...
	bool active__rcp_log = false;

	CString cur__step_ud = sCH__INFO_STEP_CUR_NUM->Get__STRING();

	// ...
	bool active__mfc_delay_off = false;
	bool active__rfx_delay_off = false;

	double cfg_delay__rf_off    = aCH__CFG_STEP_DELAY_RF_OFF->Get__VALUE();
	double cfg_delay__mfc_close = aCH__CFG_STEP_DELAY_MFC_CLOSE->Get__VALUE();
	double cfg_delay__ref_sec = 0.05;

	if(cfg_delay__mfc_close > cfg_delay__ref_sec)		active__mfc_delay_off = true;
	if(cfg_delay__rf_off    > cfg_delay__ref_sec)		active__rfx_delay_off = true;

	// RCP ...
	{
		sCH__RCP_STEP_MESSAGE->Get__DATA(rcp__step_msg);
		dCH__RCP_STEP_MODE->Get__DATA(rcp__step_mode);
		aCH__RCP_STEP_TIME->Get__DATA(rcp__step_time);
		aCH__RCP_STEP_OVERETCH_PERCENT->Get__DATA(rcp__step_overetch_per);

		// APC ...
		dCH__RCP_APC_MODE->Get__DATA(rcp__apc_mode);

		CString ch_data = aCH__RCP_APC_PRESSURE_mTORR->Get__STRING();
		rcp__apc_pressure_torr.Format("%.3f", atof(ch_data)*0.001);

		aCH__RCP_APC_POSITION->Get__DATA(rcp__apc_position);
		sCH__RCP_APC_LEARNED_POS->Get__DATA(rcp__apc_learned_pos);
		sCH__RCP_APC_HOLD_DELAY->Get__DATA(rcp__apc_hold_sec);

		// FRC ...
		rcp__frc_center = aCH__RCP_FRC_CENTER_PERCENT->Get__STRING();

		// MFC ...
		for(i=0; i<iDATA__MFC_SIZE; i++)
		{
			rcp__mfc_x_flow[i]= sCH__RCP_GAS_FLOW_X[i]->Get__STRING();
		}

		// RF.RPS ...
		sCH__RCP_RF_RPS_POWER->Get__DATA(rcp__rf_rps_power);

		// RF.LF ...
		sCH__RCP_RF_LF_POWER->Get__DATA(rcp__rf_lf_power);
		dCH__RCP_RF_LF_MODE->Get__DATA(rcp__rf_lf_mode);

		// RF.HF ...
		sCH__RCP_RF_HF_POWER->Get__DATA(rcp__rf_hf_power);
		sCH__RCP_RF_HF_P2->Get__DATA(rcp__rf_hf_p2);
		dCH__RCP_RF_HF_MODE->Get__DATA(rcp__rf_hf_mode);

		// RF.PULSE ...
		rcp__rf_pulse_frequency = aCH__RCP_RF_PULSE_FREQUENCY->Get__STRING();
		rcp__rf_pulse_duty = aCH__RCP_RF_PULSE_DUTY->Get__STRING();
		rcp__rf_pulse_exec = dCH__RCP_RF_PULSE_EXEC->Get__STRING();
		rcp__rf_pulse_on_shift_time  = aCH__RCP_RF_PULSE_ON_SHIFT_TIME->Get__STRING();
		rcp__rf_pulse_off_shift_time = aCH__RCP_RF_PULSE_OFF_SHIFT_TIME->Get__STRING();

		// MAT.LF ...
		sCH__RCP_MAT_LF_SHUNT->Get__DATA(rcp__mat_lf_shunt);
		sCH__RCP_MAT_LF_SERIES->Get__DATA(rcp__mat_lf_series);

		sCH__RCP_MAT_LF_LEARNED_SHUNT->Get__DATA(rcp__mat_lf_learned_shunt);
		sCH__RCP_MAT_LF_LEARNED_SERIES->Get__DATA(rcp__mat_lf_learned_series);

		// MAT.HF ...
		sCH__RCP_MAT_HF_SHUNT->Get__DATA(rcp__mat_hf_shunt);
		sCH__RCP_MAT_HF_SERIES->Get__DATA(rcp__mat_hf_series);

		sCH__RCP_MAT_HF_LEARNED_SHUNT->Get__DATA(rcp__mat_hf_learned_shunt);
		sCH__RCP_MAT_HF_LEARNED_SERIES->Get__DATA(rcp__mat_hf_learned_series);

		// ESC.MODE ...
		dCH__RCP_ESC_CTRL_MODE->Get__DATA(rcp__esc_mode);

		// DPC.CENTER ...
		sCH__RCP_DPC_CENTER_PRESSURE->Get__DATA(rcp__dpc_center_pressure);

		// DPC.EDGE ...
		sCH__RCP_DPC_EDGE_PRESSURE->Get__DATA(rcp__dpc_edge_pressure);

		//
		dCH__RCP_LIFT_PIN_MODE->Get__DATA(rcp__lift_pin_mode);

		//
		rcp__epd_mode = dCH__RCP_EPD_EPD_MODE->Get__STRING();

		rcp__epd_value_to_change   = aCH__RCP_EPD_VALUE_TO_CHANGE->Get__STRING();
		rcp__epd_percent_to_change = aCH__RCP_EPD_PERCENT_TO_CHANGE->Get__STRING();

		rcp__epd_delay_time = aCH__RCP_EPD_DELAY_TIME->Get__STRING();
		rcp__epd_normalize_time = aCH__RCP_EPD_NORMALIZE_TIME->Get__STRING();

		rcp__epd_min_time = aCH__RCP_EPD_MIN_TIME->Get__STRING();
		rcp__epd_max_time = aCH__RCP_EPD_MAX_TIME->Get__STRING();

		rcp__epd_min_threshold = aCH__RCP_EPD_MIN_THRESHOLD->Get__STRING();
		rcp__epd_max_threshold = aCH__RCP_EPD_MAX_THRESHOLD->Get__STRING();

		rcp__epd_slope_value = aCH__RCP_EPD_SLOPE_VALUE->Get__STRING();
		rcp__epd_slope_type  = dCH__RCP_EPD_SLOPE_TYPE->Get__STRING();
		rcp__epd_valid_time  = aCH__RCP_EPD_SLOPE_VALID_TIME->Get__STRING();
	}

	// LOG ...
	if(active__rcp_log)
	{
		_Fnc__PROC_LOG();
	}


	// ...
	bool active__stable_mode = false;
	bool active__fast_vac  = false;
	bool active__end_point = false;
	bool active__over_etch = false;

	if(rcp__step_mode.CompareNoCase(STR__Stable) == 0)
	{
		active__stable_mode = true;
	}
	else if(rcp__step_mode.CompareNoCase(STR__High_Vac) == 0)
	{
		active__fast_vac = true;
	}
	else if(rcp__step_mode.CompareNoCase(STR__EndPT) == 0)
	{
		active__end_point = true;
	}
	else if(rcp__step_mode.CompareNoCase(STR__OverEtch) == 0)
	{
		active__over_etch = true;

		ch_data = sCH__INFO_STEP_PRE_TIME->Get__STRING();
		double cur__step_sec = atof(ch_data);
		double cur__over_per = atof(rcp__step_overetch_per);

		rcp__step_time.Format("%.1f", (cur__step_sec * cur__over_per) * 0.01);
		aCH__RCP_STEP_TIME->Set__DATA(rcp__step_time);
	}
	else if(rcp__step_mode.CompareNoCase(STR__End) == 0)
	{
		return 1;
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
			para_data = rcp__apc_pressure_torr;
		}

		if(obj_mode.GetLength() > 0)
		{
			double value__hold_sec = atof(rcp__apc_hold_sec);
			double value__hold_pos = atof(rcp__apc_position);
			if(value__hold_pos < 0.1)			value__hold_pos = atof(rcp__apc_learned_pos);

			APC_OBJ__Start_MODE(obj_mode,para_data, value__hold_sec,value__hold_pos);
		}
	}

	// FRC.CTRL ...
	{
		FRC_OBJ__Start_CONTROL(rcp__frc_center);
	}

	// MFC_X.CTRL ...
	if(active__mfc_delay_off)
	{
		int mfc_ctrl_count = 0;

		for(i=0; i<iDATA__MFC_SIZE; i++)
		{
			double para__set_flow = atof(rcp__mfc_x_flow[i]);
			if(para__set_flow < 0.001)			continue;

			MFC_OBJ__Start_CONTROL(i, rcp__mfc_x_flow[i], "0");

			// ...
			{
				mfc_ctrl_count++;		
				if(mfc_ctrl_count == 1)		
					log_msg.Format("MFCx Control ... \n");

				log_bff.Format("  * MFC%1d Control(%s, %s) \n", i+1, rcp__mfc_x_flow[i], "0");
				log_msg += log_bff;
			}
		}

		if(mfc_ctrl_count > 0)
		{
			xLOG_CTRL->WRITE__LOG(log_msg);		
		}
	}
	else
	{
		for(i=0; i<iDATA__MFC_SIZE; i++)
		{
			MFC_OBJ__Start_CONTROL(i, rcp__mfc_x_flow[i], "0");
		}
	}

	// RF.RPS ...
	if(bActive__OBJ_CTRL__RF_RPS)
	{
		CString obj_mode;
		double set_power = atof(rcp__rf_rps_power);

		if(set_power > 0.1)				obj_mode = _RF_CMD__PROC_SET;
		else							obj_mode = _RF_CMD__OFF;

		if(active__rfx_delay_off)
		{
			if(obj_mode.CompareNoCase(_RF_CMD__OFF) != 0)
			{
				RF_RPS_OBJ__Start_MODE(obj_mode, rcp__rf_rps_power);

				// ...
				{
					log_msg = "RF.RPS Control ... \n";

					log_bff.Format("  * RF.RPS Control(%s, %s) \n", obj_mode, rcp__rf_rps_power);
					log_msg += log_bff;

					xLOG_CTRL->WRITE__LOG(log_msg);		
				}
			}
		}
		else
		{
			RF_RPS_OBJ__Start_MODE(obj_mode, rcp__rf_rps_power);
		}
	}
	// RF.LF ...
	if(bActive__OBJ_CTRL__RF_LF)
	{
		CString obj_mode;
		double set_power = atof(rcp__rf_lf_power);

		if(set_power > 0.1)				obj_mode = _RF_CMD__PROC_SET;
		else							obj_mode = _RF_CMD__OFF;

		if(active__rfx_delay_off)
		{
			if(obj_mode.CompareNoCase(_RF_CMD__OFF) != 0)
			{
				RF_LF_OBJ__Start_MODE(obj_mode, rcp__rf_lf_power, rcp__rf_lf_mode);

				// ...
				{
					log_msg = "RF.LF Control ... \n";

					log_bff.Format("  * RF.LF Control(%s, %s) \n", obj_mode, rcp__rf_lf_power);
					log_msg += log_bff;

					xLOG_CTRL->WRITE__LOG(log_msg);		
				}
			}
		}
		else
		{
			RF_LF_OBJ__Start_MODE(obj_mode, rcp__rf_lf_power, rcp__rf_lf_mode);
		}
	}
	// RF.HF ...
	if(bActive__OBJ_CTRL__RF_HF)
	{
		CString obj_mode;
		double set_power = atof(rcp__rf_hf_power);
		double set_p2 = atof(rcp__rf_hf_p2);

		if(set_power > 0.1)				obj_mode = _RF_CMD__PROC_SET;
		else							obj_mode = _RF_CMD__OFF;

		if(active__rfx_delay_off)
		{
			if(obj_mode.CompareNoCase(_RF_CMD__OFF) != 0)
			{
				RF_HF_OBJ__Start_MODE(obj_mode, rcp__rf_hf_power, rcp__rf_hf_p2, rcp__rf_hf_mode);

				// ...
				{
					log_msg = "RF.HF Control ... \n";

					log_bff.Format("  * RF.HF Control(%s, %s, %s) \n", obj_mode, rcp__rf_hf_power, rcp__rf_hf_p2);
					log_msg += log_bff;

					xLOG_CTRL->WRITE__LOG(log_msg);		
				}
			}
		}
		else
		{
			RF_HF_OBJ__Start_MODE(obj_mode, rcp__rf_hf_power, rcp__rf_hf_p2, rcp__rf_hf_mode);
		}
	}

	// RF.PULSE ...
	if(bActive__OBJ_CTRL__RF_PULSE)
	{
		double rcp__rf_pulse = aCH__RCP_RF_PULSE_FREQUENCY->Get__VALUE();

		if(rcp__rf_pulse < 1.0)				RF_PULSE_OBJ__Start_OFF();
		else								RF_PULSE_OBJ__Start_ON();

		if(dCH__CFG_RCP_PART_USE_RFx_PULSE->Check__DATA(STR__YES) > 0)
		{
			log_msg = "RF.PULSE Control ... \n";

			log_bff.Format("  * RF.PULSE Control(%.3f Hz) \n",  rcp__rf_pulse);
			log_msg += log_bff;

			xLOG_CTRL->WRITE__LOG(log_msg);		
		}
	}

	// MATCHER ...
	if(bActive__OBJ_CTRL__MAT_LF)
	{
		CString obj_mode = _MAT_CMD__PROC_CTRL;
		CString ch_data;

		double para__rcp_value = 0;

		// MAT.LF ...
		{
			para__rcp_value = atof(rcp__mat_lf_shunt);
			if(para__rcp_value < 0.01)			para__rcp_value = atof(rcp__mat_lf_learned_shunt);

			aEXT_CH__MAT_LF__PARA_LOAD_POS->Set__VALUE(para__rcp_value);

			//
			para__rcp_value = atof(rcp__mat_lf_series);
			if(para__rcp_value < 0.01)			para__rcp_value = atof(rcp__mat_lf_learned_series);

			aEXT_CH__MAT_LF__PARA_TUNE_POS->Set__VALUE(para__rcp_value);

			//
			MAT_LF_OBJ__Start_MODE(obj_mode);
		}
		// MAT.HF ...
		{

			para__rcp_value = atof(rcp__mat_hf_shunt);
			if(para__rcp_value < 0.01)			para__rcp_value = atof(rcp__mat_hf_learned_shunt);

			aEXT_CH__MAT_HF__PARA_LOAD_POS->Set__VALUE(para__rcp_value);

			//
			para__rcp_value = atof(rcp__mat_hf_series);
			if(para__rcp_value < 0.01)			para__rcp_value = atof(rcp__mat_hf_learned_series);

			aEXT_CH__MAT_HF__PARA_TUNE_POS->Set__VALUE(para__rcp_value);

			//
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
	bool active__pin_ctrl = false;

	if(bActive__OBJ_CTRL__LIFT_PIN)
	{
		CString obj_mode;

			 if(rcp__lift_pin_mode.CompareNoCase(STR__Down)   == 0)			obj_mode  = sDATA__LIFT_PIN__DOWN;
		else if(rcp__lift_pin_mode.CompareNoCase(STR__Middle) == 0)			obj_mode  = sDATA__LIFT_PIN__MIDDLE;
		else if(rcp__lift_pin_mode.CompareNoCase(STR__Up)     == 0)			obj_mode  = sDATA__LIFT_PIN__UP;

		if(obj_mode.GetLength() > 0)
		{
			LIFT_PIN_OBJ__Start_MODE(obj_mode);

			if(active__end_point)
			{
				if(obj_mode.CompareNoCase(_PIN_CMD__DOWN) != 0)
				{
					active__pin_ctrl  = true;
					active__end_point = false;
				}
			}
		}
	}

	// EPD ...
	{
		bool active__epd_idle   = false;
		bool active__epd_check  = false;
		bool active__epd_detect = false;
		bool active__err_check  = false;

		if(rcp__epd_mode.CompareNoCase("Idle") == 0)
		{
			if(active__end_point)			active__err_check = true;
			else							active__epd_idle  = true;
		}
		else if(rcp__epd_mode.CompareNoCase("Error.Check") == 0)
		{
			if(active__end_point)			active__err_check = true;
			else							active__epd_check = true;
		}
		else
		{
			if(active__end_point)
			{
				active__epd_detect = true;

				//
				dEXT_CH__EPD__PARA_EPD_MODE->Set__DATA(rcp__epd_mode);

				sEXT_CH__EPD__PARA_VALUE_TO_CHANGE->Set__DATA(rcp__epd_value_to_change);
				sEXT_CH__EPD__PARA_PERCENT_TO_CHANGE->Set__DATA(rcp__epd_percent_to_change);

				aEXT_CH__EPD__PARA_DELAY_TIME->Set__DATA(rcp__epd_delay_time);
				sEXT_CH__EPD__PARA_NORMALIZE_TIME->Set__DATA(rcp__epd_normalize_time);

				aEXT_CH__EPD__PARA_EPD_TIMEOUT_MINIMUM->Set__DATA(rcp__epd_min_time);
				aEXT_CH__EPD__PARA_EPD_TIMEOUT_MAXIMUM->Set__DATA(rcp__epd_max_time);

				sEXT_CH__EPD__PARA_EPD_THRESHOLD_MIN->Set__DATA(rcp__epd_min_threshold);
				sEXT_CH__EPD__PARA_EPD_THRESHOLD_MAX->Set__DATA(rcp__epd_max_threshold);

				sEXT_CH__EPD__PARA_SLOPE_COUNT->Set__DATA(rcp__epd_slope_value);
				sEXT_CH__EPD__PARA_SLOPE_DIRECTION->Set__DATA(rcp__epd_slope_type);
				sEXT_CH__EPD__PARA_VALID_TIME->Set__DATA(rcp__epd_valid_time);
			}
			else
			{
				active__epd_idle = true;
			}
		}

		if(active__err_check)
		{
			int alm_id = ALID__STEP_PARAMETER__SETTING_ERROR;

			CString alm_msg;
			CString alm_bff;
			CString r_act;

			alm_bff.Format("Current Step.No <- %s \n", sCH__INFO_STEP_CUR_NUM->Get__STRING());
			alm_msg += alm_bff;

			alm_bff.Format("  Step.Mode <- %s \n", rcp__step_mode);
			alm_msg += alm_bff;
			alm_bff.Format("  EPD.Mode  <- %s \n", rcp__epd_mode);
			alm_msg += alm_bff;

			p_alarm->Check__ALARM(alm_id, r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
			return -101;
		}

			 if(active__epd_idle)			EPD_OBJ__Start_IDLE();
		else if(active__epd_check)			EPD_OBJ__Start_CHECK();
		else if(active__epd_detect)			EPD_OBJ__Start_DETECT();
	}


	// ...
	double cfg__stable_min_sec = aCH__CFG_STEP_STABLE_MIN_SEC->Get__VALUE();

	// ...
	bool active__htr_error_check = false;

	if(dCH__CFG_STEP_CTRL_ERROR_CONTROL->Check__DATA(STR__ENABLE) > 0)
	{
		active__htr_error_check = true;
	}

	// ...
	SCX__STEP_TIMER_CTRL x_step_timer;
	x_step_timer->START__TIMER();

	double para__step_sec = atof(rcp__step_time);
	double cur_sec  = 0.0;

	// ...
	{
		log_msg.Format("Step(%s) Start - Mode(%s) Time(%s sec) \n", cur__step_ud, rcp__step_mode,rcp__step_time);

		log_bff.Format("  * cfg_delay__rf_off : %.1f sec \n", cfg_delay__rf_off);
		log_msg += log_bff;
		log_bff.Format("  * cfg_delay__mfc_close : %.1f sec \n", cfg_delay__mfc_close);
		log_msg += log_bff;
		log_bff.Format("  * cfg_delay__ref_sec : %.1f sec \n", cfg_delay__ref_sec);
		log_msg += log_bff;

		xLOG_CTRL->WRITE__LOG(log_msg);		
	}

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

		// Turn.Off De;ay ...
		{
			// MFC_X.CTRL ...
			if(active__mfc_delay_off)
			{
				if(cur_sec >= cfg_delay__mfc_close)
				{
					active__mfc_delay_off = false;

					//
					int mfc_ctrl_count = 0;

					for(i=0; i<iDATA__MFC_SIZE; i++)
					{
						double para__set_flow = atof(rcp__mfc_x_flow[i]);
						if(para__set_flow >= 0.001)		continue;

						MFC_OBJ__Start_CLOSE(i);

						// ...
						{
							mfc_ctrl_count++;		
							if(mfc_ctrl_count == 1)		
								log_msg.Format("MFCx Close ... \n");

							log_bff.Format("  * MFC%1d Close(%s) \n", i+1, rcp__mfc_x_flow[i]);
							log_msg += log_bff;
						}
					}

					if(mfc_ctrl_count > 0)
					{
						xLOG_CTRL->WRITE__LOG(log_msg);		
					}
				}
			}

			// RFx.CTRL ...
			if(active__rfx_delay_off)
			{
				if(cur_sec >= cfg_delay__rf_off)
				{
					active__rfx_delay_off = false;

					//
					int rfx_ctrl_count = 0;

					log_msg.Format("RFx Off ... \n");

					// RF_RPS ...
					{
						double set_power = atof(rcp__rf_rps_power);

						if(set_power < 0.001)
						{
							RF_RPS_OBJ__Start_OFF();

							// ...
							{
								rfx_ctrl_count++;

								log_bff.Format("  * RF.HF Off(%s) \n", rcp__rf_rps_power);
								log_msg += log_bff;
							}
						}
					}
					// RF_HF ...
					{
						double set_power = atof(rcp__rf_hf_power);

						if(set_power < 0.001)
						{
							RF_HF_OBJ__Start_OFF();

							// ...
							{
								rfx_ctrl_count++;

								log_bff.Format("  * RF.HF Off(%s) \n", rcp__rf_hf_power);
								log_msg += log_bff;
							}
						}
					}
					// RF_LF ...
					{
						double set_power = atof(rcp__rf_lf_power);

						if(set_power < 0.001)
						{
							RF_LF_OBJ__Start_OFF();

							// ...
							{
								rfx_ctrl_count++;

								log_bff.Format("  * RF.Bias Off(%s) \n", rcp__rf_lf_power);
								log_msg += log_bff;
							}
						}
					}

					if(rfx_ctrl_count > 0)
					{
						xLOG_CTRL->WRITE__LOG(log_msg);		
					}
				}
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

			if(ESC_OBJ__Check_ERROR() > 0)				return -131;

			if(active__htr_error_check)
			{
				if(HTR_SH_OBJ__Check_ERROR()   > 0)		return -141;
				if(HTR_WALL_OBJ__Check_ERROR() > 0)		return -142;
			}

			// if(active__over_etch)
			{
				if(EPD_OBJ__Check_ERROR() > 0)			return -151;
			}
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
			
			if(LIFT_PIN_OBJ__Check_ABORTED() > 0)		return -251;
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
				double ref__pressure = atof(rcp__apc_pressure_torr);

				if(cur__pressure <= ref__pressure)
				{
					break;
				}
			}
		}
		else if(active__end_point)
		{
			if(EPD_OBJ__Is_BUSY() < 0)
			{
				break;
			}
		}
		else if(active__pin_ctrl)
		{
			if(LIFT_PIN_OBJ__Is_BUSY() < 0)
			{
				break;
			}
		}

		if(cur_ctrl == _CMD_ID__START)
		{
			if(x_step_timer->Check__CURRENT_TIME(para__step_sec, cur_sec))
			{
				if((active__stable_mode)
				|| (active__fast_vac)
				|| (active__end_point)
				|| (active__pin_ctrl))
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

	// ...
	{
		ch_data.Format("%.1f", x_step_timer->Get__CURRENT_SEC());
		sCH__INFO_STEP_PRE_TIME->Set__DATA(ch_data);
	}

	// Object Over-Time Check ...
	double cur__obj_delay_sec = Fnc__OBJ_OVERTIME_CHECK(p_variable, p_alarm);

	// ...
	{
		log_msg.Format("Step(%s) End - Object Delay (%.2f sec)", cur__step_ud, cur__obj_delay_sec);

		xLOG_CTRL->WRITE__LOG(log_msg);		
	}

	// OBJ.Abort Check ...
	{
		if(ESC_OBJ__Check_ABORTED() > 0)						return -301;
		if(LIFT_PIN_OBJ__Check_ABORTED() > 0)					return -302;
		if(EPD_OBJ__Check_ABORTED() > 0)						return -303;
	}
	return 1;
}

double CObj__STEP_BETA
::Fnc__OBJ_OVERTIME_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm)
{
	SCX__ASYNC_TIMER_CTRL x_obj_timer_ctrl;
	x_obj_timer_ctrl->START__COUNT_UP(9999);

	bool active__esc_obj = false;
	bool active__pin_obj = false;
	bool active__epd_obj = false;

	while(1)
	{
		bool active__obj_budy = false;

		if(ESC_OBJ__Is_BUSY() > 0)
		{
			active__obj_budy = true;
			active__esc_obj = true;
		}
		if(LIFT_PIN_OBJ__Is_BUSY() > 0)
		{
			active__obj_budy = true;
			active__pin_obj = true;
		}
		if(EPD_OBJ__Is_BUSY() > 0)
		{
			active__obj_budy = true;
			active__epd_obj  = true;
		}

		if(active__obj_budy)
		{
			if(p_variable->Check__CTRL_ABORT() > 0)			break;

			Sleep(1);
			continue;
		}

		break;
	}

	//
	double cfg__err_ref = aCH__CFG_STEP_OBJECT_OVER_TIME_ERRPR_REF_SEC->Get__VALUE();

	if(x_obj_timer_ctrl->Get__CURRENT_TIME() > cfg__err_ref)
	{
		int alm_id = ALID__OBJECT_OVERTIME;

		CString alm_msg;
		CString alm_bff;
		CString r_act;

		CString cur__step_id = sCH__INFO_STEP_CUR_NUM->Get__STRING();

		//
		CString cur__step_time = aCH__RCP_STEP_TIME->Get__STRING();
		CString cur__step_mode = dCH__RCP_STEP_MODE->Get__STRING();
		CString cur__esc_mode  = dCH__RCP_ESC_CTRL_MODE->Get__STRING();
		CString cur__pin_mode  = dCH__RCP_LIFT_PIN_MODE->Get__STRING();
		CString cur__epd_mode  = dCH__RCP_EPD_EPD_MODE->Get__STRING();

		//
		alm_bff.Format(" Object over-time is %.1f (sec). \n", x_obj_timer_ctrl->Get__CURRENT_TIME());
		alm_msg += alm_bff;

		alm_bff.Format(" Object over-time error-ref is %.2f (sec). \n", cfg__err_ref);
		alm_msg += alm_bff;

		//
		alm_msg += "\n";
		alm_bff.Format(" The current step ID is %s. \n", cur__step_id);
		alm_msg += alm_bff;

		alm_bff.Format(" The step information is as follows : \n");
		alm_msg += alm_bff;

		alm_bff.Format("   * Step-time is %s (sec). \n", cur__step_time);
		alm_msg += alm_bff;

		alm_bff.Format("   * Step-mode is \"%s\". \n", cur__step_mode);
		alm_msg += alm_bff;

		if(active__esc_obj)
		{
			alm_bff.Format("   * ESC control-mode is \"%s\". \n", cur__esc_mode);
			alm_msg += alm_bff;
		}
		if(active__pin_obj)
		{
			alm_bff.Format("   * Lift-pin control is \"%s\". \n", cur__pin_mode);
			alm_msg += alm_bff;
		}
		if(active__epd_obj)
		{
			alm_bff.Format("   * EPD control is \"%s\". \n", cur__epd_mode);
			alm_msg += alm_bff;
		}

		alm_msg += "\n";

		if(active__esc_obj)
		{
			alm_bff.Format(" Please, check the time of ESC (%s) config page. \n", cur__esc_mode);
			alm_msg += alm_bff;
		}
		if(active__pin_obj)
		{
			alm_bff.Format(" Please, check the actual operation time of lift-pin (%s). \n", cur__pin_mode);
			alm_msg += alm_bff;
		}
		if(active__epd_obj)
		{
			alm_bff.Format(" Please, check the actual operation time of EPD (%s). \n", cur__epd_mode);
			alm_msg += alm_bff;
		}

		//
		p_alarm->Check__ALARM(alm_id, r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
	}

	return x_obj_timer_ctrl->Get__CURRENT_TIME();
}

int CObj__STEP_BETA
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

int CObj__STEP_BETA::_Fnc__PROC_LOG()
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
						aCH__RCP_APC_PRESSURE_mTORR->Get__CHANNEL_NAME(),
						aCH__RCP_APC_PRESSURE_mTORR->Get__STRING());
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

		log_bff.Format(" * %s <- %s \n", 
						dCH__RCP_RF_LF_MODE->Get__CHANNEL_NAME(),
						dCH__RCP_RF_LF_MODE->Get__STRING());
		log_msg += log_bff;
	}
	// RF.HF ...
	{
		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_RF_HF_POWER->Get__CHANNEL_NAME(),
						sCH__RCP_RF_HF_POWER->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_RF_HF_P2->Get__CHANNEL_NAME(),
						sCH__RCP_RF_HF_P2->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						dCH__RCP_RF_HF_MODE->Get__CHANNEL_NAME(),
						dCH__RCP_RF_HF_MODE->Get__STRING());
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
