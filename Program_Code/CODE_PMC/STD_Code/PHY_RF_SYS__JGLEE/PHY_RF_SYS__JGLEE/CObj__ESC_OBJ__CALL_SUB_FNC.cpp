#include "StdAfx.h"
#include "CObj__ESC_OBJ.h"


// ...
int  CObj__ESC_OBJ
::Fnc__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	if(dEXT_CH__WAFER_STATUS->Check__DATA(STR__NONE) > 0)
	{
		dCH__MON_CHUCK_STATUS->Set__DATA(STR__DECHUCKED);
	}

	if(pOBJ_CTRL__ESC_POWER->Call__OBJECT("INIT") < 0)
	{
		return -1;
	}

	if(dCH__CFG_HW_CHECK_USE_DURING_INITIAL->Check__DATA(STR__ENABLE) > 0)
	{
		if(Fnc__HW_CHECK(p_variable, p_alarm) < 0)
		{
			return -1;
		}
	}

	if(dCH__MON_CHUCK_STATUS->Check__DATA(STR__DECHUCKED) < 0)
	{
		if(dEXT_CH__CFG_DECHUCK_CTRL_MODE->Check__DATA("CONFIG") > 0)
		{
			return Fnc__DECHUCK(p_variable,p_alarm, 0);
		}
	}
	return 1;
}

int  CObj__ESC_OBJ
::Fnc__HE_CLOSE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(dEXT_CH__WAFER_STATUS->Check__DATA(STR__NONE) < 0)
	{
		if(dCH__MON_CHUCK_STATUS->Check__DATA(STR__DECHUCKED) < 0)
		{
			dCH__MON_CHUCK_STATUS->Set__DATA(STR__UNKNOWN);
		}
	}
	else
	{
		dCH__MON_CHUCK_STATUS->Set__DATA(STR__DECHUCKED);
	}

	// ...
	{
		if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(0.0);
		if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(0.0);

		// ...
		{
			int center__delay_check__final_vlv = -1;
			int edge__delay_check__final_vlv   = -1;

			doEXT_CH__HE_VALVE_SUPPLY->Set__DATA(STR__Close);

			if(bActive__HE_CONTROL_CENTER_USE)
			{
				center__delay_check__final_vlv = doEXT_CH__HE_VALVE_FINAL_OUT_CENTER->Check__DATA(STR__Open);
			}
			if(bActive__HE_CONTROL_EDGE_USE)
			{
				edge__delay_check__final_vlv = doEXT_CH__HE_VALVE_FINAL_OUT_EDGE->Check__DATA(STR__Open);
			}

			pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__CLOSE);

			if((center__delay_check__final_vlv > 0)
			|| (edge__delay_check__final_vlv   > 0))
			{
				Sleep(2000);
			}
		}

		if(bActive__ESC_POWER_CENTER_USE)			aoEXT_CH__ESC_VOLTAGE_CENTER->Set__VALUE(0.0);
		if(bActive__ESC_POWER_EDGE_USE)				aoEXT_CH__ESC_VOLTAGE_EDGE->Set__VALUE(0.0);
		
		doEXT_CH__ESC_VOLTAGE_ON->Set__DATA(STR__Off); // KMS
		doEXT_CH__ESC_All_Voltage->Set__DATA(STR__Off);
	}	

	return 1;
}

int  CObj__ESC_OBJ
::Fnc__HW_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	dCH__MON_HE_FLOW_CTRL_ACTIVE->Set__DATA(STR__ON);

	// Pressure Setting ...
	{
		sCH__APP_LOG_SUB_MSG->Set__DATA("Pressure Setting ...");

		pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__BYPASS_FLOW);

		Sleep(900);

		// ...
		double cfg__center_pressure = aCH__CFG_HE_CENTER_PRESSURE_FOR_HW_CHECK->Get__VALUE();
		double cfg__edge_pressure   = aCH__CFG_HE_EDGE_PRESSURE_FOR_HW_CHECK->Get__VALUE();

		if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(cfg__center_pressure);
		if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(cfg__edge_pressure);

		doEXT_CH__HE_VALVE_SUPPLY->Set__DATA(STR__Open);

		if(iActive__SIM_MODE > 0)
		{
			if(bActive__HE_CONTROL_CENTER_USE)			aiEXT_CH__He_Flow_CENTER_IO->Set__VALUE(cfg__center_pressure / 2.0);
			if(bActive__HE_CONTROL_EDGE_USE)			aiEXT_CH__He_Flow_EDGE_IO->Set__VALUE(cfg__edge_pressure / 2.0);
		}
	}

	// Stable Time ...
	{
		sCH__APP_LOG_SUB_MSG->Set__DATA("Bypass Stable Time Delay ...");

		SCX__TIMER_CTRL x_app_timer;
		x_app_timer->REGISTER__ABORT_OBJECT(sObject_Name);
		x_app_timer->REGISTER__COUNT_CHANNEL(sCH__APP_TIMER_COUNT->Get__CHANNEL_NAME());

		double cfg__stable_sec = aCH__CFG_HE_STABLE_TIME_FOR_HW_CHECK->Get__VALUE();

		if(x_app_timer->WAIT(cfg__stable_sec) < 0)
		{
			return -1;
		}
	}

	// Error Check ...
	{
		CString var_data;

		var_data = sCH__MON_He_Flow_CENTER->Get__STRING();
		double cur__center_flow = atof(var_data);

		double cfg__center_flow = aCH__CFG_HE_CENTER_BYPASS_FLOW_FOR_HW_CHECK->Get__VALUE();
		double cfg__error_range = aCH__CFG_HE_FLOW_ERROR_RANGE_FOR_HW_CHECK->Get__VALUE();

		double ref__center_min_flow = cfg__center_flow - cfg__error_range;
		double ref__center_max_flow = cfg__center_flow + cfg__error_range;

		double ok_check = 1;

		if(iActive__SIM_MODE > 0)
		{
			aiEXT_CH__He_Flow_CENTER_IO->Set__VALUE((ref__center_min_flow + ref__center_max_flow) / 2.0);
		}

		if((cur__center_flow > ref__center_max_flow) 
		|| (cur__center_flow < ref__center_min_flow))
		{
			ok_check = -1;

			// ...
			{
				int alm_id = ALID__HE_CENTER_CONFIG_RANGE_ERROR;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg = "HW He_Center Checking Error ! \n";

				alm_bff.Format("Current helium flow is %.1f sccm. \n", cur__center_flow);
				alm_msg += alm_bff;
				alm_bff.Format("Config helium bypass Min. flow is %.1f sccm. \n", ref__center_min_flow);
				alm_msg += alm_bff;
				alm_bff.Format("Config helium bypass Max. flow is %.1f sccm. \n", ref__center_max_flow);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
			}
		}

		if(ok_check < 0)
		{
			sCH__APP_LOG_SUB_MSG->Set__DATA("Error Check Aborted ...");
			return -1;
		}
	}

	// Test End ...
	{
		sCH__APP_LOG_SUB_MSG->Set__DATA("Test End ...");

		pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__DUMP_FLOW);

		if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(0.0);
		if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(0.0);
	}
	return 1;
}

int  CObj__ESC_OBJ::
Fnc__CHUCK(CII_OBJECT__VARIABLE* p_variable,
		   CII_OBJECT__ALARM* p_alarm,
		   const int chuck_mode)
{
	if(chuck_mode <  0)							return -1;
	if(chuck_mode >= DEF__CHUCK_MODE_SIZE)		return -2;

	// ...
	{
		dCH__MON_ESC_CTRL_ACTIVE->Set__DATA(STR__ON);
		dCH__MON_HE_FLOW_CTRL_ACTIVE->Set__DATA(STR__ON);
	}

	// ...
	SCX__ASYNC_TIMER_CTRL x_app_timer;
	x_app_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__APP_TIMER_COUNT->Get__CHANNEL_NAME());
	x_app_timer->STOP_ZERO();

	// ...
	double  para__set_volt_center  = 0.0;
	double  para__set_volt_edge    = 0.0;
	double  para__set_press_center = 0.0;
	double  para__set_press_edge   = 0.0;

	double  cfg_sec__hv_off     = 0.0;
	double  cfg_sec__hv_on      = 0.0;
	double  cfg_sec__hv_stable  = 0.0;
	double  cfg_sec__hv_holding = 0.0;
	double  cfg_sec__rf_on      = 0.0;
	double  cfg_sec_final_flow_stable = 0.0;

	double  cfg__max_volt__center = 0.0;
	double  cfg__max_volt__edge   = 0.0;
	double  cfg__min_volt__center = 0.0;
	double  cfg__min_volt__edge   = 0.0;

	CString log_msg;
	CString log_bff;

	CString var_data;

	// ...
	{
		log_msg.Format("Fnc__CHUCK() ... Started");
		xLOG_CTRL->WRITE__LOG(log_msg);	

		sCH__RESULT_CHUCK_CHART_MAIN_MSG->Set__DATA("Chucking Started ...");
		sCH__RESULT_CHUCK_CHART_SUB_MSG->Set__DATA("");
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		var_data = x_seq_info->Get__DATE_TIME_STRING();
		sCH__RESULT_CHUCK_CHART_TEST_DATE->Set__DATA(var_data);

			 if(chuck_mode == 0)		sCH__RESULT_CHUCK_CHART_TEST_MODE->Set__DATA("CHUCK");
		else if(chuck_mode == 1)		sCH__RESULT_CHUCK_CHART_TEST_MODE->Set__DATA("CHUCK1");
		else if(chuck_mode == 2)		sCH__RESULT_CHUCK_CHART_TEST_MODE->Set__DATA("CHUCK2");
		else							sCH__RESULT_CHUCK_CHART_TEST_MODE->Set__DATA("Unknown !!!");

		sCH__RESULT_CHUCK_CHART_TEST_RESULT->Set__DATA("???");
	}

	// Chuck Step - Parameter ...
	{
		// Control Setting ...
		{
			if(bActive__ESC_POWER_CENTER_USE)
			{
				sCH__PARA_ESC_CENTER_SET_VOLTAGE->Get__DATA(var_data);
				para__set_volt_center = atof(var_data);
			}
			if(bActive__HE_CONTROL_CENTER_USE)
			{	
				sCH__PARA_He_SET_PRESSURE_CENTER->Get__DATA(var_data);
				para__set_press_center = atof(var_data);
			}

			if(bActive__ESC_POWER_EDGE_USE)
			{
				sCH__PARA_ESC_EDGE_SET_VOLTAGE->Get__DATA(var_data);
				para__set_volt_edge = atof(var_data);
			}
			if(bActive__HE_CONTROL_EDGE_USE)
			{
				sCH__PARA_He_SET_PRESSURE_EDGE->Get__DATA(var_data);
				para__set_press_edge = atof(var_data);
			}
		}

		// time (sec) ...
		{
			cfg_sec__hv_off     = aCH__CFG_HV_OFF_TIME_CHUCK_X[chuck_mode]->Get__VALUE();
			cfg_sec__hv_on      = aCH__CFG_HV_ON_TIME_CHUCK_X[chuck_mode]->Get__VALUE();
			cfg_sec__hv_stable  = aCH__CFG_HV_STABLE_TIME_CHUCK_X[chuck_mode]->Get__VALUE();
			cfg_sec__hv_holding = aCH__CFG_HV_HOLDING_TIME_CHUCK_X[chuck_mode]->Get__VALUE();
			cfg_sec__rf_on      = aCH__CFG_RF_ON_TIME_CHUCK_X[chuck_mode]->Get__VALUE();

			cfg_sec_final_flow_stable = aCH__CFG_FINAL_FLOW_STABLE_TIME_CHUCK_X[chuck_mode]->Get__VALUE();
		}

		// chucking interlock ...
		{
			if(bActive__ESC_POWER_CENTER_USE)
			{
				cfg__max_volt__center = aCH__CFG_ESC_CENTER_VOLTAGE_MAX_SETPOINT_FOR_CHUCKING->Get__VALUE();
				cfg__min_volt__center = aCH__CFG_ESC_CENTER_VOLTAGE_MIN_SETPOINT_FOR_CHUCKING->Get__VALUE();
			}
			if(bActive__ESC_POWER_EDGE_USE)
			{
				cfg__max_volt__edge = aCH__CFG_ESC_EDGE_VOLTAGE_MAX_SETPOINT_FOR_CHUCKING->Get__VALUE();
				cfg__min_volt__edge = aCH__CFG_ESC_EDGE_VOLTAGE_MIN_SETPOINT_FOR_CHUCKING->Get__VALUE();
			}
		}

		// ...
		{
			log_msg  = "\n";
			log_msg += "Parameter ... \n";

			if(bActive__ESC_POWER_CENTER_USE)
			{
				log_bff.Format("   para__set_volt_center  <- [%.1f] \n", para__set_volt_center);
				log_msg += log_bff;

				log_bff.Format("   para__set_press_center <- [%.1f] \n", para__set_press_center);
				log_msg += log_bff;
			}
			if(bActive__ESC_POWER_EDGE_USE)
			{
				log_bff.Format("   para__set_volt_edge  <- [%.1f] \n", para__set_volt_edge);
				log_msg += log_bff;

				log_bff.Format("   para__set_press_edge <- [%.1f] \n", para__set_press_edge);
				log_msg += log_bff;
			}

			log_bff.Format("   cfg_sec__hv_off     <- [%.1f] \n", cfg_sec__hv_off);
			log_msg += log_bff;
			log_bff.Format("   cfg_sec__hv_on      <- [%.1f] \n", cfg_sec__hv_on);
			log_msg += log_bff;
			log_bff.Format("   cfg_sec__hv_stable  <- [%.1f] \n", cfg_sec__hv_stable);
			log_msg += log_bff;
			log_bff.Format("   cfg_sec__hv_holding <- [%.1f] \n", cfg_sec__hv_holding);
			log_msg += log_bff;
			log_bff.Format("   cfg_sec__rf_on      <- [%.1f] \n", cfg_sec__rf_on);
			log_msg += log_bff;
			log_bff.Format("   cfg_sec_final_flow_stable <- [%.1f] \n", cfg_sec_final_flow_stable);
			log_msg += log_bff;

			if(bActive__ESC_POWER_CENTER_USE)
			{
				log_bff.Format("   cfg__max_volt_center <- [%.1f] \n", cfg__max_volt__center);
				log_msg += log_bff;

				log_bff.Format("   cfg__min_volt_center <- [%.1f] \n", cfg__min_volt__center);
				log_msg += log_bff;
			}
			if(bActive__ESC_POWER_EDGE_USE)
			{
				log_bff.Format("   cfg__max_volt_edge <- [%.1f] \n", cfg__max_volt__edge);
				log_msg += log_bff;

				log_bff.Format("   cfg__min_volt_edge <- [%.1f] \n", cfg__min_volt__edge);
				log_msg += log_bff;
			}

			log_msg += "\n";

			xLOG_CTRL->WRITE__LOG(log_msg);	
		}
	}

	// Test Data Init ...
	{
		// RESULT POINT1 ...
		if((chuck_mode == 0)
			|| (chuck_mode == 1))
		{
			sCH__RESULT_CH1_ESC_CHUCKING_VOLTAGE_READING_POINT1->Set__DATA("");
			sCH__RESULT_CH1_ESC_CHUCKING_CURRENT_READING_POINT1->Set__DATA("");

			sCH__RESULT_CH2_ESC_CHUCKING_VOLTAGE_READING_POINT1->Set__DATA("");
			sCH__RESULT_CH2_ESC_CHUCKING_CURRENT_READING_POINT1->Set__DATA("");

			sCH__RESULT_HE_CENTER_PRESSURE_READING_POINT1->Set__DATA("");
			sCH__RESULT_HE_CENTER_FLOW_READING_POINT1->Set__DATA("");

			sCH__RESULT_HE_EDGE_PRESSURE_READING_POINT1->Set__DATA("");
			sCH__RESULT_HE_EDGE_FLOW_READING_POINT1->Set__DATA("");
		}
		// RESULT POINT2 ...
		{
			sCH__RESULT_CH1_ESC_CHUCKING_VOLTAGE_READING_POINT2->Set__DATA("");
			sCH__RESULT_CH1_ESC_CHUCKING_CURRENT_READING_POINT2->Set__DATA("");

			sCH__RESULT_CH2_ESC_CHUCKING_VOLTAGE_READING_POINT2->Set__DATA("");
			sCH__RESULT_CH2_ESC_CHUCKING_CURRENT_READING_POINT2->Set__DATA("");

			sCH__RESULT_HE_CENTER_PRESSURE_READING_POINT2->Set__DATA("");
			sCH__RESULT_HE_CENTER_FLOW_READING_POINT2->Set__DATA("");

			sCH__RESULT_HE_EDGE_PRESSURE_READING_POINT2->Set__DATA("");
			sCH__RESULT_HE_EDGE_FLOW_READING_POINT2->Set__DATA("");
		}
	}

	// Interlock Check ...
	{
		sCH__APP_LOG_SUB_MSG->Set__DATA("Interlock Checking");
		sCH__RESULT_CHUCK_CHART_MAIN_MSG->Set__DATA("Interlock Checking ...");

		if(dCH__CFG_INTERLOCK_MODE_ALL->Check__DATA(STR__DISABLE) > 0)
		{
			int alarm_id = ALID__INTERLOCK_ALL_DISABLE;
			CString r_act;

			p_alarm->Popup__ALARM(alarm_id, r_act);

			if(r_act.CompareNoCase(STR__YES) != 0)		return -101;
		}
		else
		{
			if(Fnc__HV_SENSOR_INTERLOCK_CHECK(p_alarm) < 0)
			{
				return -201;
			}

			if(Fnc__HV_SETPOINT_INTERLOCK_CHECK(p_alarm, para__set_volt_center,para__set_volt_edge) < 0)
			{
				return -202;
			}

			if(Fnc__HE_SETPOINT_INTERLOCK_CHECK(p_alarm, para__set_press_center,para__set_press_edge) < 0)
			{
				return -203;
			}
		}
	}

	// ...
	SCX__ASYNC_TIMER_CTRL x_chart_timer;

	if(chuck_mode == 0)		x_chart_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__RESULT_CHUCK_CHART_TIME_CHUCK->Get__CHANNEL_NAME());
	else if(chuck_mode == 1)		x_chart_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__RESULT_CHUCK_CHART_TIME_CHUCK1->Get__CHANNEL_NAME());
	else if(chuck_mode == 2)		x_chart_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__RESULT_CHUCK_CHART_TIME_CHUCK2->Get__CHANNEL_NAME());

	x_chart_timer->START__COUNT_UP(9999);

	// TEST Parameter : Save ...
	{
		// control setting ...
		{
			// Center ...
			if(bActive__ESC_POWER_CENTER_USE)
			{
				var_data.Format("%.1f", para__set_volt_center);
				sCH__TEST_CH1_ESC_CHUCKING_VOLTAGE_SETPOINT_START->Set__DATA(var_data);
			}
			if(bActive__HE_CONTROL_CENTER_USE)
			{
				var_data.Format("%.1f", para__set_press_center);
				sCH__TEST_HE_CENTER_PRESSURE_SETPOINT_START->Set__DATA(var_data);
			}

			// Edge ...
			if(bActive__ESC_POWER_EDGE_USE)
			{
				var_data.Format("%.1f", para__set_volt_edge);
				sCH__TEST_CH2_ESC_CHUCKING_VOLTAGE_SETPOINT_START->Set__DATA(var_data);
			}
			if(bActive__HE_CONTROL_EDGE_USE)
			{
				var_data.Format("%.1f", para__set_press_edge);
				sCH__TEST_HE_EDGE_PRESSURE_SETPOINT_START->Set__DATA(var_data);
			}
		}

		// time (sec) ...
		{
			double test_total_sec  = 0.0;
			double test_chuck1_sec = 0.0;
			double test_chuck2_sec = 0.0;
			int i;

			for(i=0; i<DEF__CHUCK_CHART_SIZE; i++)
			{
					 if(i == 0)		var_data.Format("%.1f", cfg_sec__hv_off);
				else if(i == 1)		var_data.Format("%.1f", cfg_sec__hv_on);
				else if(i == 2)		var_data.Format("%.1f", cfg_sec__hv_stable);
				else if(i == 3)		var_data.Format("%.1f", cfg_sec__hv_holding);
				else if(i == 4)		var_data.Format("%.1f", cfg_sec__rf_on);
				else if(i == 5)		var_data.Format("%.1f", cfg_sec_final_flow_stable);
				else				continue;	

				if((chuck_mode == 0)
					|| (chuck_mode == 1))
				{
					sCH__RESULT_CHUCK_CHART_TIME[i]->Set__DATA("");
				}
				else if(chuck_mode == 2)
				{
					if(i > 3)		sCH__RESULT_CHUCK_CHART_TIME[i]->Set__DATA("--");
				}

				if(i > 0)
				{
					sCH__TEST_CHUCK_CHART_TIME[i]->Set__DATA(var_data);
					double cur_sec = atof(var_data);

					test_total_sec += cur_sec;

					if(i < 3)		test_chuck1_sec += cur_sec;
					else			test_chuck2_sec += cur_sec;
				}
			}				

			var_data.Format("%.1f", test_total_sec);
			sCH__TEST_CHUCK_CHART_TIME_TOTAL->Set__DATA(var_data);
			sCH__RESULT_CHUCK_CHART_TIME_TOTAL->Set__DATA("");

			if(chuck_mode == 2)
			{
				sCH__TEST_CHUCK_CHART_TIME_CHUCK->Set__DATA("--");
				sCH__TEST_CHUCK_CHART_TIME_CHUCK2->Set__DATA("--");

				sCH__RESULT_CHUCK_CHART_TIME_CHUCK->Set__DATA("--");
				sCH__RESULT_CHUCK_CHART_TIME_CHUCK2->Set__DATA("--");
			}
			else
			{
				sCH__TEST_CHUCK_CHART_TIME_CHUCK->Set__DATA("--");
				sCH__TEST_CHUCK_CHART_TIME_CHUCK1->Set__DATA("--");
				sCH__TEST_CHUCK_CHART_TIME_CHUCK2->Set__DATA("--");

				sCH__RESULT_CHUCK_CHART_TIME_CHUCK->Set__DATA("--");
				sCH__RESULT_CHUCK_CHART_TIME_CHUCK1->Set__DATA("--");
				sCH__RESULT_CHUCK_CHART_TIME_CHUCK2->Set__DATA("--");
			}

			if(chuck_mode == 0)
			{
				var_data = sCH__TEST_CHUCK_CHART_TIME_TOTAL->Get__STRING();
				sCH__TEST_CHUCK_CHART_TIME_CHUCK->Set__DATA(var_data);
			}
			else if(chuck_mode == 1)
			{
				var_data.Format("%.1f", test_chuck1_sec);
				sCH__TEST_CHUCK_CHART_TIME_CHUCK1->Set__DATA(var_data);
			}	
			else if(chuck_mode == 2)
			{
				var_data.Format("%.1f", test_chuck2_sec);
				sCH__TEST_CHUCK_CHART_TIME_CHUCK2->Set__DATA(var_data);
			}
		}
	}

	dCH__MON_CHUCK_STATUS->Set__DATA(STR__CHUCKING);


	//====================================================================================================================================
	// CHUCK1 

	// 1. HV On Delay ...
	if((chuck_mode == 0)
	|| (chuck_mode == 1))
	{
		SCX__ASYNC_TIMER_CTRL x_timer__hv_on_delay;

		x_timer__hv_on_delay->REGISTER__COUNT_CHANNEL_NAME(sCH__RESULT_CHUCK_CHART_TIME[DEF_CHUCK_CHART__HV_ON]->Get__CHANNEL_NAME());
		x_timer__hv_on_delay->START__COUNT_UP(9999);

		x_app_timer->START__COUNT_UP(9999);

		// He Bypass Flow ...  
		{
			int delay_check = -1;

			if(bActive__HE_CONTROL_CENTER_USE)
			{
				if(doEXT_CH__HE_VALVE_FINAL_OUT_CENTER->Check__DATA(STR__Close) < 0)		delay_check = 1;
			}
			if(bActive__HE_CONTROL_EDGE_USE)
			{
				if(doEXT_CH__HE_VALVE_FINAL_OUT_EDGE->Check__DATA(STR__Close) < 0)			delay_check = 1;
			}

			pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__BYPASS_FLOW);

			if(doEXT_CH__HE_VALVE_SUPPLY->Check__DATA(STR__Open) < 0)
			{
				doEXT_CH__HE_VALVE_SUPPLY->Set__DATA(STR__Open);

				delay_check = 1;
			}

			// ---------------------------------------------------------------------------
			SCX__ASYNC_TIMER_CTRL x_timer__hv_off;

			x_timer__hv_off->REGISTER__COUNT_CHANNEL_NAME(sCH__RESULT_CHUCK_CHART_TIME[DEF_CHUCK_CHART__HV_OFF]->Get__CHANNEL_NAME());
			x_timer__hv_off->START__COUNT_UP(9999);

			// HV Off ...
			if(cfg_sec__hv_off > 0.0)
			{
				if(bActive__ESC_POWER_CENTER_USE)			aoEXT_CH__ESC_VOLTAGE_CENTER->Set__VALUE(0.0);
				if(bActive__ESC_POWER_EDGE_USE)				aoEXT_CH__ESC_VOLTAGE_EDGE->Set__VALUE(0.0);
				doEXT_CH__ESC_VOLTAGE_ON->Set__DATA(STR__Off); // KMS
				doEXT_CH__ESC_All_Voltage->Set__DATA(STR__Off);
			}

			if(delay_check > 0)
			{
				// ...
				{
					log_msg  = "Fnc__CHUCK() : Valve Delay (0.9 sec) ... \n";
					log_msg += " * He_Final_Out_Vlv_Center (Open -> Close) \n";
					log_msg += " * He_Final_Out_Vlv_Edge   (Open -> Close) \n";
					log_msg += " * He_Side_Supply_Vlv      (Close -> Open) \n";

					xLOG_CTRL->WRITE__LOG(log_msg);	
				}

				Sleep(900);
			}

			if(cfg_sec__hv_off > 0.0)
			{
				// ...
				{
					log_msg.Format("Fnc__CHUCK() : HV Off Delay Started ...");	
					xLOG_CTRL->WRITE__LOG(log_msg);	

					log_msg.Format("HV Off Delay (%.1f sec)", cfg_sec__hv_off);
					sCH__APP_LOG_SUB_MSG->Set__DATA(log_msg);
					sCH__RESULT_CHUCK_CHART_MAIN_MSG->Set__DATA(log_msg);
				}

				while(x_timer__hv_off->Get__CURRENT_TIME() < cfg_sec__hv_off)
				{
					Sleep(1);

					if(p_variable->Check__CTRL_ABORT() > 0)
					{
						sCH__RESULT_CHUCK_CHART_SUB_MSG->Set__DATA("HV Off Delay Aborted ...");
						return -11;
					}
				}
			}

			x_timer__hv_off->STOP();
			// ---------------------------------------------------------------------------

			if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(para__set_press_center);				
			if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(para__set_press_edge);				

			if(iActive__SIM_MODE > 0)
			{
				if(bActive__HE_CONTROL_CENTER_USE)			aiEXT_CH__He_Flow_CENTER_IO->Set__VALUE(para__set_press_center / 2.0);
				if(bActive__HE_CONTROL_EDGE_USE)			aiEXT_CH__He_Flow_EDGE_IO->Set__VALUE(para__set_press_edge / 2.0);
			}
		}

		// HV On ...
		{
			if(bActive__ESC_POWER_CENTER_USE)			aoEXT_CH__ESC_VOLTAGE_CENTER->Set__VALUE(para__set_volt_center);
			if(bActive__ESC_POWER_EDGE_USE)				aoEXT_CH__ESC_VOLTAGE_EDGE->Set__VALUE(para__set_volt_edge);

			doEXT_CH__ESC_All_Voltage->Set__DATA(STR__On);
			doEXT_CH__ESC_VOLTAGE_ON->Set__DATA(STR__On); //KMS Voltage ON
		}

		// HV On Delay ...
		if((chuck_mode == 0)
		|| (chuck_mode == 1))
		{
			// ...
			{
				log_msg.Format("Fnc__CHUCK() : HV On Started ...");	
				xLOG_CTRL->WRITE__LOG(log_msg);	

				log_msg.Format("HV On Delay (%.1f sec)", cfg_sec__hv_on);
				sCH__APP_LOG_SUB_MSG->Set__DATA(log_msg);
				sCH__RESULT_CHUCK_CHART_MAIN_MSG->Set__DATA(log_msg);
			}

			while(x_timer__hv_on_delay->Get__CURRENT_TIME() < cfg_sec__hv_on)
			{
				Sleep(1);

				if(p_variable->Check__CTRL_ABORT() > 0)
				{
					sCH__RESULT_CHUCK_CHART_SUB_MSG->Set__DATA("HV On Aborted ...");
					return -11;
				}
			}
		}

		x_timer__hv_on_delay->STOP();
		x_app_timer->STOP();
	}

	// 2. HV Stable Delay ...
	if((chuck_mode == 0)
	|| (chuck_mode == 1))
	{
		SCX__TIMER_CTRL x_timer;

		x_timer->REGISTER__COUNT_CHANNEL(sCH__RESULT_CHUCK_CHART_TIME[DEF_CHUCK_CHART__HV_STABLE]->Get__CHANNEL_NAME());
		x_timer->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer->SET__DECIMAL_POINT(2);
		x_timer->INIT__COUNT_UP();
		x_app_timer->START__COUNT_UP(9999);

		// HV Stable ...
		{
			if((bActive__HE_CONTROL_CENTER_USE)
			&& (bActive__HE_CONTROL_EDGE_USE))
			{
				log_msg.Format("Center_Volt(%.0f V) & Edge_Volt(%.0f V) & HV Stable (%.0f sec)", 
								para__set_volt_center,
								para__set_volt_edge,
								cfg_sec__hv_stable);
			}
			else if(bActive__HE_CONTROL_CENTER_USE)
			{
				log_msg.Format("Center_Volt(%.0f V) & HV Stable (%.0f sec)", 
								para__set_volt_center,
								cfg_sec__hv_stable);
			}

			sCH__APP_LOG_SUB_MSG->Set__DATA(log_msg);
			sCH__RESULT_CHUCK_CHART_MAIN_MSG->Set__DATA(log_msg);

			if(x_timer->WAIT(cfg_sec__hv_stable) < 0)
			{
				return -21;
			}
		}

		x_app_timer->STOP();
	}

	// 3. HV Holding Delay ...
	if((chuck_mode == 0)
	|| (chuck_mode == 1))
	{
		SCX__TIMER_CTRL x_timer;

		x_timer->REGISTER__COUNT_CHANNEL(sCH__RESULT_CHUCK_CHART_TIME[DEF_CHUCK_CHART__HV_HOLDING]->Get__CHANNEL_NAME());
		x_timer->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer->SET__DECIMAL_POINT(2);
		x_timer->INIT__COUNT_UP();
		x_app_timer->START__COUNT_UP(9999);

		// HV Holding ...
		{
			log_msg.Format("HV Holding Delay (%.0f sec)", cfg_sec__hv_holding);
			sCH__APP_LOG_SUB_MSG->Set__DATA(log_msg);
			sCH__RESULT_CHUCK_CHART_MAIN_MSG->Set__DATA(log_msg);

			if(x_timer->WAIT(cfg_sec__hv_holding) < 0)
			{
				return -31;
			}
		}

		x_app_timer->STOP();
	}

	// ...
	{
		double cur_sec = 0.0;
		int i;

		for(i=1; i<=DEF_CHUCK_CHART__HV_HOLDING; i++)
		{
			var_data = sCH__RESULT_CHUCK_CHART_TIME[i]->Get__STRING();
			cur_sec += atof(var_data);
		}

		var_data.Format("%.1f", cur_sec);
		sCH__RESULT_CHUCK_CHART_TIME_TOTAL->Set__DATA(var_data);

		if(chuck_mode == 1)
		{
			x_chart_timer->STOP();
		}
	}

	// HV Error Check & He Pressure Error Check ...
	if((chuck_mode == 0)
	|| (chuck_mode == 1))
	{
		// Data Save ...
		{
			// ESC Center ...
			if(bActive__ESC_POWER_CENTER_USE)
			{
				aiEXT_CH__ESC_VOLTAGE_CENTER->Get__DATA(var_data);
				sCH__RESULT_CH1_ESC_CHUCKING_VOLTAGE_READING_POINT1->Set__DATA(var_data);

				aiEXT_CH__ESC_CURRENT_CENTER->Get__DATA(var_data);
				sCH__RESULT_CH1_ESC_CHUCKING_CURRENT_READING_POINT1->Set__DATA(var_data);
			}
			// ESC Center ...
			if(bActive__ESC_POWER_EDGE_USE)
			{
				aiEXT_CH__ESC_VOLTAGE_EDGE->Get__DATA(var_data);
				sCH__RESULT_CH2_ESC_CHUCKING_VOLTAGE_READING_POINT1->Set__DATA(var_data);

				aiEXT_CH__ESC_CURRENT_EDGE->Get__DATA(var_data);
				sCH__RESULT_CH2_ESC_CHUCKING_CURRENT_READING_POINT1->Set__DATA(var_data);
			}

			// He Center ...
			if(bActive__HE_CONTROL_CENTER_USE)
			{
				sCH__MON_He_Pressure_CENTER->Get__DATA(var_data);
				sCH__RESULT_HE_CENTER_PRESSURE_READING_POINT1->Set__DATA(var_data);

				sCH__MON_He_Flow_CENTER->Get__DATA(var_data);
				sCH__RESULT_HE_CENTER_FLOW_READING_POINT1->Set__DATA(var_data);
			}
			// He Edge ...
			if(bActive__HE_CONTROL_EDGE_USE)
			{
				sCH__MON_He_Pressure_EDGE->Get__DATA(var_data);
				sCH__RESULT_HE_EDGE_PRESSURE_READING_POINT1->Set__DATA(var_data);

				sCH__MON_He_Flow_EDGE->Get__DATA(var_data);
				sCH__RESULT_HE_EDGE_FLOW_READING_POINT1->Set__DATA(var_data);
			}
		}

		// ...
		{
			int err_check = -1;

			// HV Error Check ...
			{
				if(Fnc__HV_ERROR_CHECK(p_alarm, CHECK_POINT__1) < 0)			err_check = 1;
			}

			// He Error Check ...
			{
				if(bActive__HE_CONTROL_CENTER_USE)
				{
					if(Fnc__HE_ERROR_CHECK(p_alarm, HE_TYPE__CENTER, CHECK_POINT__1) < 0)			err_check = 1;
				}
				if(bActive__HE_CONTROL_EDGE_USE)
				{
					if(Fnc__HE_ERROR_CHECK(p_alarm, HE_TYPE__EDGE, CHECK_POINT__1) < 0)				err_check = 1;
				}
			}

			if(err_check > 0)
			{
				return -1;
			}
		}
	}


	//====================================================================================================================================
	// CHUCK2 

	// 4. RF On Delay ...
	if((chuck_mode == 0)
	|| (chuck_mode == 2))
	{
		SCX__TIMER_CTRL x_timer;

		x_timer->REGISTER__COUNT_CHANNEL(sCH__RESULT_CHUCK_CHART_TIME[DEF_CHUCK_CHART__RF_ON]->Get__CHANNEL_NAME());
		x_timer->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer->SET__DECIMAL_POINT(2);
		x_timer->INIT__COUNT_UP();
		x_app_timer->START__COUNT_UP(9999);

		// RF On ...
		{
			log_msg.Format("RF On Delay (%.1f sec)", cfg_sec__rf_on);
			sCH__APP_LOG_SUB_MSG->Set__DATA(log_msg);
			sCH__RESULT_CHUCK_CHART_MAIN_MSG->Set__DATA(log_msg);

			if(x_timer->POLL(cfg_sec__rf_on) < 0)
			{
				return -41;
			}

			x_app_timer->STOP();
		}
	}

	// 5. Final Flow Stable Delay ...
	if((chuck_mode == 0)
	|| (chuck_mode == 2))
	{
		// Data Save ...
		{
			sCH__MON_He_Flow_CENTER->Get__DATA(var_data);
			sCH__RESULT_HE_CENTER_FLOW_READING_POINT1->Set__DATA(var_data);
		}

		// ...
		SCX__TIMER_CTRL x_timer;

		x_timer->REGISTER__COUNT_CHANNEL(sCH__RESULT_CHUCK_CHART_TIME[DEF_CHUCK_CHART__FINAL_FLOW_STABLE]->Get__CHANNEL_NAME());
		x_timer->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer->SET__DECIMAL_POINT(2);
		x_timer->INIT__COUNT_UP();
		x_app_timer->START__COUNT_UP(9999);

		// ...
		{
			pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__FINAL_FLOW);

			doEXT_CH__HE_VALVE_SUPPLY->Set__DATA(STR__Open);			

			if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(para__set_press_center);
			if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(para__set_press_edge);
		}

		iACTIVE__WAFER_LEAK_CHECK = 1;

		// Final Flow Stable ...
		{
			log_msg.Format("Final Flow Stable Delay (%.1f sec) ...", cfg_sec_final_flow_stable);
			sCH__APP_LOG_SUB_MSG->Set__DATA(log_msg);
			sCH__RESULT_CHUCK_CHART_MAIN_MSG->Set__DATA(log_msg);

			if(x_timer->WAIT(cfg_sec_final_flow_stable) <= 0)
			{
				return -51;
			}
		}

		x_app_timer->STOP();
	}

	if((chuck_mode == 0)
	|| (chuck_mode == 2))
	{
		var_data = sCH__RESULT_CHUCK_CHART_TIME_TOTAL->Get__STRING();
		double pre_sec = atof(var_data);

		double cur_sec = 0.0;
		int i;

		for(i=DEF_CHUCK_CHART__RF_ON; i<DEF__CHUCK_CHART_SIZE; i++)
		{
			var_data = sCH__RESULT_CHUCK_CHART_TIME[i]->Get__STRING();
			cur_sec += atof(var_data);
		}

		var_data.Format("%.1f", pre_sec + cur_sec);
		sCH__RESULT_CHUCK_CHART_TIME_TOTAL->Set__DATA(var_data);

		if(chuck_mode == 0)
		{
			x_chart_timer->STOP();
		}
		else if(chuck_mode == 2)
		{
			x_chart_timer->STOP();
		}
	}

	// Wafer Leak Check Error ...
	if((chuck_mode == 0)
	|| (chuck_mode == 2))
	{
		// Data Save ...
		{
			// ESC Center ...
			if(bActive__ESC_POWER_CENTER_USE)
			{
				aiEXT_CH__ESC_VOLTAGE_CENTER->Get__DATA(var_data);
				sCH__RESULT_CH1_ESC_CHUCKING_VOLTAGE_READING_POINT2->Set__DATA(var_data);

				aiEXT_CH__ESC_CURRENT_CENTER->Get__DATA(var_data);
				sCH__RESULT_CH1_ESC_CHUCKING_CURRENT_READING_POINT2->Set__DATA(var_data);
			}
			// ESC Edge ...
			if(bActive__ESC_POWER_EDGE_USE)
			{
				aiEXT_CH__ESC_VOLTAGE_EDGE->Get__DATA(var_data);
				sCH__RESULT_CH2_ESC_CHUCKING_VOLTAGE_READING_POINT2->Set__DATA(var_data);

				aiEXT_CH__ESC_CURRENT_EDGE->Get__DATA(var_data);
				sCH__RESULT_CH2_ESC_CHUCKING_CURRENT_READING_POINT2->Set__DATA(var_data);
			}

			// He Center ...
			if(bActive__HE_CONTROL_CENTER_USE)
			{
				sCH__MON_He_Pressure_CENTER->Get__DATA(var_data);
				sCH__RESULT_HE_CENTER_PRESSURE_READING_POINT2->Set__DATA(var_data);

				sCH__MON_He_Flow_CENTER->Get__DATA(var_data);
				sCH__RESULT_HE_CENTER_FLOW_READING_POINT2->Set__DATA(var_data);
			}
			// He Edge ...
			if(bActive__HE_CONTROL_EDGE_USE)
			{
				sCH__MON_He_Pressure_EDGE->Get__DATA(var_data);
				sCH__RESULT_HE_EDGE_PRESSURE_READING_POINT2->Set__DATA(var_data);

				sCH__MON_He_Flow_EDGE->Get__DATA(var_data);
				sCH__RESULT_HE_EDGE_FLOW_READING_POINT2->Set__DATA(var_data);
			}
		}

		// ...
		{
			int err_check = -1;

			// HV Error Check ...
			{
				if(Fnc__HV_ERROR_CHECK(p_alarm, CHECK_POINT__2) < 0)						err_check = 1;
			}

			// He Error Check ...
			{
				if(bActive__HE_CONTROL_CENTER_USE)
				{
					if(Fnc__HE_ERROR_CHECK(p_alarm, HE_TYPE__CENTER, CHECK_POINT__2) < 0)		err_check = 1;
				}
				if(bActive__HE_CONTROL_EDGE_USE)
				{
					if(Fnc__HE_ERROR_CHECK(p_alarm, HE_TYPE__EDGE, CHECK_POINT__2) < 0)		err_check = 1;
				}
			}

			if(err_check > 0)
			{
				return -1;
			}
		}

		if(bActive__HE_CONTROL_CENTER_USE)
		{
			aCH__CFG_HE_CENTER_WAFER_MAX_LEAK->Get__DATA(var_data);
			sCH__TEST_HE_CENTER_WAFER_LEAK_CHECK_REF->Set__DATA(var_data);
		}
		if(bActive__HE_CONTROL_EDGE_USE)
		{
			aCH__CFG_HE_EDGE_WAFER_MAX_LEAK->Get__DATA(var_data);
			sCH__TEST_HE_EDGE_WAFER_LEAK_CHECK_REF->Set__DATA(var_data);
		}

		// Flow Leak Check ...
		{
			// Center ...
			if(bActive__HE_CONTROL_CENTER_USE)
			{
				sCH__RESULT_HE_CENTER_FLOW_READING_POINT2->Get__DATA(var_data);
				double pt2_flow = atof(var_data);

				sCH__RESULT_HE_CENTER_FLOW_READING_POINT1->Get__DATA(var_data);
				double pt1_flow = atof(var_data);

				var_data.Format("%.1f", pt2_flow - pt1_flow);
				sCH__RESULT_HE_CENTER_WAFER_LEAK_CHECK_RESULT->Set__DATA(var_data);
			}

			// Edge ...
			if(bActive__HE_CONTROL_EDGE_USE)
			{
				sCH__RESULT_HE_EDGE_FLOW_READING_POINT2->Get__DATA(var_data);
				double pt2_flow = atof(var_data);

				sCH__RESULT_HE_EDGE_FLOW_READING_POINT1->Get__DATA(var_data);
				double pt1_flow = atof(var_data);

				var_data.Format("%.1f", pt2_flow - pt1_flow);
				sCH__RESULT_HE_EDGE_WAFER_LEAK_CHECK_RESULT->Set__DATA(var_data);
			}
		}
	}

	// He Pressure Control ...
	if((chuck_mode == 0)
	|| (chuck_mode == 2))
	{
		// He Leak Check ...
		{
			log_msg = "He Leak Checking";
			sCH__APP_LOG_SUB_MSG->Set__DATA(log_msg);

			// ...
			bool active__err_leak = false;

			CString alm_msg;
			CString alm_bff;

			// Center ...
			if(bActive__HE_CONTROL_CENTER_USE)
			{
				sCH__TEST_HE_CENTER_WAFER_LEAK_CHECK_REF->Get__DATA(var_data);
				double cfg_center__max_leak = atof(var_data);

				sCH__RESULT_HE_CENTER_WAFER_LEAK_CHECK_RESULT->Get__DATA(var_data);
				double cur_center__leak_flow = atof(var_data);

				if(cur_center__leak_flow > cfg_center__max_leak)
				{
					active__err_leak = true;

					alm_bff.Format("Current center wafer leak flow is %.1f sccm. \n", cur_center__leak_flow);
					alm_msg += alm_bff;

					alm_bff.Format("Config center wafer Max. leak is %.1f sccm. \n", cfg_center__max_leak);
					alm_msg += alm_bff;
					alm_msg += "\n";
				}
			}			

			// Edge ...
			if(bActive__HE_CONTROL_EDGE_USE)
			{
				sCH__TEST_HE_EDGE_WAFER_LEAK_CHECK_REF->Get__DATA(var_data);
				double cfg_edge__max_leak = atof(var_data);

				sCH__RESULT_HE_EDGE_WAFER_LEAK_CHECK_RESULT->Get__DATA(var_data);
				double cur_edge__leak_flow = atof(var_data);

				if(cur_edge__leak_flow > cfg_edge__max_leak)
				{
					active__err_leak = true;

					alm_bff.Format("Current edge wafer leak flow is %.1f sccm. \n", cur_edge__leak_flow);
					alm_msg += alm_bff;

					alm_bff.Format("Config edge wafer Max. leak is %.1f sccm. \n", cfg_edge__max_leak);
					alm_msg += alm_bff;
					alm_msg += "\n";
				}
			}

			if(active__err_leak)
			{
				int alm_id = ALID__HE_WAFER_MAXIMUM_LEAK_SCCM;
				CString r_act;

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				return -101;
			}

			// ...
		}
	}

	// Stable check ...
	if(sCH__PARA_STABLE_CHECK_REQ->Check__DATA(STR__YES) > 0)
	{
		log_msg = "ESC Chucking - Stable Checking";
		sCH__APP_LOG_SUB_MSG->Set__DATA(log_msg);

		// ...
		{
			sCH__MON_CENTER_STABLE_ESC_STATE->Set__DATA("");
			sCH__MON_STABLE_HE_CENTER_STATE->Set__DATA("");

			sCH__MON_EDGE_STABLE_ESC_STATE->Set__DATA("");
			sCH__MON_STABLE_HE_EDGE_STATE->Set__DATA("");
		}

		while(1)
		{
			Sleep(10);

			// ...
			bool active__stable_check = true;

			// Center,Check
			if(bActive__ESC_POWER_CENTER_USE)
			{
				if(sCH__MON_CENTER_STABLE_ESC_STATE->Check__DATA(STR__YES) < 0)			active__stable_check = false;
			}
			if(bActive__HE_CONTROL_CENTER_USE)
			{
				if(sCH__MON_STABLE_HE_CENTER_STATE->Check__DATA(STR__YES) < 0)			active__stable_check = false;
			}

			// Edge.Check
			if(bActive__ESC_POWER_EDGE_USE)
			{
				if(sCH__MON_EDGE_STABLE_ESC_STATE->Check__DATA(STR__YES) < 0)			active__stable_check = false;
			}
			if(bActive__HE_CONTROL_EDGE_USE)
			{
				if(sCH__MON_STABLE_HE_EDGE_STATE->Check__DATA(STR__YES) < 0)			active__stable_check = false;
			}

			if(active__stable_check)
			{
				break;
			}

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				CString log_bff;

				log_msg = "Fnc__CHUCK : Aborted By Upper Object ... \n";

				// Center
				if(bActive__ESC_POWER_CENTER_USE)
				{
					log_bff.Format(" * %s <- %s \n", 
									sCH__MON_CENTER_STABLE_ESC_STATE->Get__CHANNEL_NAME(),
									sCH__MON_CENTER_STABLE_ESC_STATE->Get__STRING());
					log_msg += log_bff;
				}
				if(bActive__HE_CONTROL_CENTER_USE)
				{
					log_bff.Format(" * %s <- %s \n", 
									sCH__MON_STABLE_HE_CENTER_STATE->Get__CHANNEL_NAME(),
									sCH__MON_STABLE_HE_CENTER_STATE->Get__STRING());
					log_msg += log_bff;
				}

				// Edge
				if(bActive__ESC_POWER_EDGE_USE)
				{
					log_bff.Format(" * %s <- %s \n", 
									sCH__MON_EDGE_STABLE_ESC_STATE->Get__CHANNEL_NAME(),
									sCH__MON_EDGE_STABLE_ESC_STATE->Get__STRING());
					log_msg += log_bff;
				}
				if(bActive__HE_CONTROL_EDGE_USE)
				{
					log_bff.Format(" * %s <- %s \n", 
									sCH__MON_STABLE_HE_EDGE_STATE->Get__CHANNEL_NAME(),
									sCH__MON_STABLE_HE_EDGE_STATE->Get__STRING());
					log_msg += log_bff;
				}

				xLOG_CTRL->WRITE__LOG(log_msg);	
				return -111;
			}
		}
	}

	if((chuck_mode == 0)
		|| (chuck_mode == (DEF__CHUCK_MODE_SIZE - 1)))
	{
		sCH__RESULT_CHUCK_CHART_TEST_RESULT->Set__DATA("OK");
	}
	else
	{
		sCH__RESULT_CHUCK_CHART_TEST_RESULT->Set__DATA("ING");
	}

	dCH__MON_CHUCK_STATUS->Set__DATA(STR__CHUCKED);
	return 1;
}

int  CObj__ESC_OBJ::
Fnc__HE_SET_OF_PROC(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	double  para__set_press_center = 0.0;
	double  para__set_press_edge   = 0.0;

	CString log_msg;
	CString log_bff;

	CString var_data;

	// ...
	{
		log_msg.Format("Fnc__HE_SET_OF_PROC() ... Started");
		xLOG_CTRL->WRITE__LOG(log_msg);	
	}

	// pressure parameter ...
	{
		sCH__PARA_He_SET_PRESSURE_CENTER->Get__DATA(var_data);
		para__set_press_center = atof(var_data);

		sCH__PARA_He_SET_PRESSURE_EDGE->Get__DATA(var_data);
		para__set_press_edge = atof(var_data);

		// ...
		{
			log_msg  = "\n";
			log_msg += "Parameter ... \n";

			if(bActive__HE_CONTROL_CENTER_USE)
			{
				log_bff.Format("   para__set_press_center <- [%.1f] \n", para__set_press_center);
				log_msg += log_bff;
			}
			if(bActive__HE_CONTROL_EDGE_USE)
			{
				log_bff.Format("   para__set_press_edge <- [%.1f] \n", para__set_press_edge);
				log_msg += log_bff;
			}

			log_msg += "\n";

			xLOG_CTRL->WRITE__LOG(log_msg);	
		}
	}

	if((dCH__MON_CHUCK_STATUS->Check__DATA(STR__CHUCKED)  > 0)
	|| (dCH__MON_CHUCK_STATUS->Check__DATA(STR__CHUCKING) > 0))
	{
		if(Fnc__HE_SETPOINT_INTERLOCK_CHECK(p_alarm, para__set_press_center,para__set_press_edge) < 0)
		{
			return -1;
		}

		// He Final Flow ...
		{
			log_msg.Format("He Final Flow ...");
			xLOG_CTRL->WRITE__LOG(log_msg);	
		}

		// He Setting - Parameter ...
		{
			if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(para__set_press_center);				
			if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(para__set_press_edge);				

			pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__FINAL_FLOW);
			
			doEXT_CH__HE_VALVE_SUPPLY->Set__DATA(STR__Open);
		}
	}
	else
	{
		// He Bypass Flow ...
		{
			log_msg.Format("He Bypass Flow ...");
			xLOG_CTRL->WRITE__LOG(log_msg);	
		}

		// ...
		bool active__close_delay = false;

		if(bActive__HE_CONTROL_CENTER_USE)
		{
			if(doEXT_CH__HE_VALVE_FINAL_OUT_CENTER->Check__DATA(STR__Close) < 0)			active__close_delay = true;
		}
		if(bActive__HE_CONTROL_EDGE_USE)
		{
			if(doEXT_CH__HE_VALVE_FINAL_OUT_EDGE->Check__DATA(STR__Close) < 0)				active__close_delay = true;
		}

		pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__BYPASS_FLOW);

		if(active__close_delay)
		{
			Sleep(1000);
		}

		if(para__set_press_center > 0.001)
		{
			doEXT_CH__HE_VALVE_SUPPLY->Set__DATA(STR__Open);			
		}
		else
		{
			doEXT_CH__HE_VALVE_SUPPLY->Set__DATA(STR__Close);		
		}

		// He Setting - Parameter ...
		{
			if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(para__set_press_center);				
			if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(para__set_press_edge);				
		}
	}

	return 1;
}

int  CObj__ESC_OBJ::
Fnc__HV_SENSOR_INTERLOCK_CHECK(CII_OBJECT__ALARM* p_alarm)
{
	int err_check = -1;

	if(dCH__CFG_INTERLOCK_MODE_VACUUM->Check__DATA(STR__ENABLE) > 0)
	{
		if(sEXT_CH__CHM_PRESSURE_STATUS->Check__DATA(STR__VAC) < 0)
		{
			err_check = 1;

			// ...
			{
				CString log_msg = "Chamber pressure is not Vacuum !!!";						
				xLOG_CTRL->WRITE__LOG(log_msg);	
			}

			// Alarm ...
			{
				int alm_id = ALID__ESC_CHUCK_ERROR__PRESSURE_NOT_VAC;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM(alm_id);
			}
		}
	}
	else
	{
		int alarm_id = ALID__INTERLOCK_VACUUM_DISABLE;
		CString r_act;

		p_alarm->Popup__ALARM(alarm_id, r_act);

		if(r_act.CompareNoCase(STR__YES) == 0)		return 1;
		return -11;
	}

	if(dCH__CFG_INTERLOCK_MODE_WAFER->Check__DATA(STR__ENABLE) > 0)
	{
		if(dEXT_CH__WAFER_STATUS->Check__DATA(STR__NONE) > 0)
		{
			err_check = 1;

			// ...
			{
				CString log_msg = "Wafer does not exist !!!";						
				xLOG_CTRL->WRITE__LOG(log_msg);	
			}

			// Alarm ...
			{
				int alm_id = ALID__ESC_CHUCK_ERROR__WAFER_NOT_EXIST;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM(alm_id);
			}
		}
	}
	else
	{
		int alarm_id = ALID__INTERLOCK_WAFER_DISABLE;
		CString r_act;

		p_alarm->Popup__ALARM(alarm_id, r_act);

		if(r_act.CompareNoCase(STR__YES) == 0)		return 1;
		return -21;
	}

	if(err_check > 0)
	{
		return -1;
	}
	return 1;
}
int  CObj__ESC_OBJ::
Fnc__HV_SETPOINT_INTERLOCK_CHECK(CII_OBJECT__ALARM* p_alarm, const double set_volt_center,const double set_volt_edge)
{
	int err_check = -1;

	// ESC Center ...
	if(bActive__ESC_POWER_CENTER_USE)
	{
		double cfg__max_volt = aCH__CFG_ESC_CENTER_VOLTAGE_MAX_SETPOINT_FOR_CHUCKING->Get__VALUE();
		double cfg__min_volt = aCH__CFG_ESC_CENTER_VOLTAGE_MIN_SETPOINT_FOR_CHUCKING->Get__VALUE();

		if(set_volt_center > cfg__max_volt)
		{
			err_check = 1;

			// Alarm ...
			{
				int alm_id = ALID__ESC_CENTER_CHUCK_VOLTAGE__MAX_ERROR;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("ESC Center Voltage Set <- %.1f V \n", set_volt_center);
				alm_msg += alm_bff;
				alm_bff.Format("Config Max. Voltage    <- %.1f V \n", cfg__max_volt);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			}
		}
		if(set_volt_center < cfg__min_volt)
		{
			err_check = 1;

			// Alarm ...
			{
				int alm_id = ALID__ESC_CENTER_CHUCK_VOLTAGE__MIN_ERROR;;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("ESC Center Voltage Set <- %.1f V \n", set_volt_center);
				alm_msg += alm_bff;
				alm_bff.Format("Config Min. Voltage    <- %.1f V \n", cfg__min_volt);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			}
		}
	}
	// ESC Edge ...
	if(bActive__ESC_POWER_EDGE_USE)
	{
		double cfg__max_volt = aCH__CFG_ESC_EDGE_VOLTAGE_MAX_SETPOINT_FOR_CHUCKING->Get__VALUE();
		double cfg__min_volt = aCH__CFG_ESC_EDGE_VOLTAGE_MIN_SETPOINT_FOR_CHUCKING->Get__VALUE();

		if(set_volt_edge > cfg__max_volt)
		{
			err_check = 1;

			// Alarm ...
			{
				int alm_id = ALID__ESC_EDGE_CHUCK_VOLTAGE__MAX_ERROR;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("ESC Edge Voltage Set <- %.1f V \n", set_volt_edge);
				alm_msg += alm_bff;
				alm_bff.Format("Config Max. Voltage    <- %.1f V \n", cfg__max_volt);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			}
		}
		if(set_volt_edge < cfg__min_volt)
		{
			err_check = 1;

			// Alarm ...
			{
				int alm_id = ALID__ESC_EDGE_CHUCK_VOLTAGE__MIN_ERROR;;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("ESC Edge Voltage Set <- %.1f V \n", set_volt_edge);
				alm_msg += alm_bff;
				alm_bff.Format("Config Min. Voltage    <- %.1f V \n", cfg__min_volt);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			}
		}
	}

	// Shutter Close Check ...
	if(dCH__CFG_INTERLOCK_MODE_CHM_ISO->Check__DATA(STR__DISABLE) > 0)
	{
		int alarm_id = ALID__INTERLOCK_CHM_ISO_DISABLE;
		CString r_act;

		p_alarm->Popup__ALARM(alarm_id, r_act);

		if(r_act.CompareNoCase(STR__YES) != 0)			return -21;
	}
	else
	{
		bool active__shutter_error  = false;
		bool active__slot_vlv_error = false;

		if(bActive__SHUTTER_STATUS)
		{
			if(sEXT_CH__SHUTTER_STATUS->Check__DATA(STR__Close) < 0)			active__shutter_error = true;
		}
		if(bActive__SLOT_VALVE_STATE)
		{
			if(sEXT_CH__SLOT_VALVE_STATE->Check__DATA(STR__Close) < 0)			active__slot_vlv_error = true;
		}

		if(active__slot_vlv_error)
		{
			err_check = 1;

			// ...
			{
				int alm_id = ALID__SHUTTER_NOT_CLOSE;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				if(bActive__ESC_POWER_CENTER_USE)
				{
					alm_bff.Format("ESC Center에 Voltage(%.1f V)를 인가 할 수 없습니다.\n", set_volt_center);
					alm_msg += alm_bff;
				}
				if(bActive__ESC_POWER_EDGE_USE)
				{
					alm_bff.Format("ESC Edge에 Voltage(%.1f V)를 인가 할 수 없습니다.\n", set_volt_edge);
					alm_msg += alm_bff;
				}

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			}
		}
		if(active__slot_vlv_error)
		{
			err_check = 1;

			// ...
			{
				int alm_id = ALID__SLOT_VALVE_NOT_CLOSE;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				if(bActive__ESC_POWER_CENTER_USE)
				{
					alm_bff.Format("ESC Center에 Voltage(%.1f V)를 인가 할 수 없습니다.\n", set_volt_center);
					alm_msg += alm_bff;
				}
				if(bActive__ESC_POWER_EDGE_USE)
				{
					alm_bff.Format("ESC Edge에 Voltage(%.1f V)를 인가 할 수 없습니다.\n", set_volt_edge);
					alm_msg += alm_bff;
				}

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			}
		}
	}

	if(err_check > 0)
	{
		return -1;
	}
	return 1;
}

int  CObj__ESC_OBJ::
Fnc__HE_SETPOINT_INTERLOCK_CHECK(CII_OBJECT__ALARM* p_alarm, const double center_pressure,const double edge_pressure)
{
	bool active__pressure_error = false;

	double cfg__pressure_max = aCH__CFG_He_PRESSURE_MAX_SETPOINT->Get__VALUE();

	if(bActive__HE_CONTROL_CENTER_USE)
	{
		if(center_pressure > cfg__pressure_max)		active__pressure_error = true;
	}
	if(bActive__HE_CONTROL_EDGE_USE)
	{
		if(edge_pressure > cfg__pressure_max)		active__pressure_error = true;
	}

	if(active__pressure_error)
	{
		int alm_id = ALID__HE_PRESSURE__MAX_ERROR;
		CString alm_msg;
		CString alm_bff;
		CString r_act;

		if(bActive__HE_CONTROL_CENTER_USE)
		{
			if(center_pressure > cfg__pressure_max)
			{
				alm_bff.Format("current he center pressure <- %.1f (tprr) \n", center_pressure);
				alm_msg += alm_bff;
			}
		}
		if(bActive__HE_CONTROL_EDGE_USE)
		{
			if(edge_pressure > cfg__pressure_max)
			{
				alm_bff.Format("current he edge pressure <- %.1f (tprr) \n", edge_pressure);
				alm_msg += alm_bff;
			}
		}

		alm_bff.Format("config he max. pressure <- %.1f (torr) \n", cfg__pressure_max);
		alm_msg += alm_bff;

		p_alarm->Check__ALARM(alm_id,r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
		return -1;
	}

	return 1;
}

int  CObj__ESC_OBJ::
Fnc__HV_ERROR_CHECK(CII_OBJECT__ALARM* p_alarm, 
					const int check_point,
					const int alm_report)
{
	double check_vol__center     = 0.0;
	double check_vol__edge       = 0.0;
	double check_current__center = 0.0;
	double check_current__edge   = 0.0;
	double hv_set__center = 0.0;
	double hv_set__edge   = 0.0;

	double cfg_warning__vol_per = 0.0;
	double cfg_fault__vol_per   = 0.0;
	double ref_warning__vol_min = 0.0;
	double ref_warning__vol_max = 0.0;

	double ref_fault__vol_min = 0.0;
	double ref_fault__vol_max = 0.0;			

	double cfg__vol_high_limit     = 0.0;
	double cfg__current_high_limit = 0.0;

	int err_check = -1;
	CString var_data;

	
	if(check_point == CHECK_POINT__1)
	{
		// ESC.Center ...
		if(bActive__ESC_POWER_CENTER_USE)
		{
			sCH__RESULT_CH1_ESC_CHUCKING_VOLTAGE_READING_POINT1->Get__DATA(var_data);
			check_vol__center = atof(var_data);

			sCH__RESULT_CH1_ESC_CHUCKING_CURRENT_READING_POINT1->Get__DATA(var_data);
			check_current__center = atof(var_data);
		}
		// ESC.Edge ...
		if(bActive__ESC_POWER_EDGE_USE)
		{
			sCH__RESULT_CH2_ESC_CHUCKING_VOLTAGE_READING_POINT1->Get__DATA(var_data);
			check_vol__edge = atof(var_data);

			sCH__RESULT_CH2_ESC_CHUCKING_CURRENT_READING_POINT1->Get__DATA(var_data);
			check_current__edge = atof(var_data);
		}
	}
	else if(check_point == CHECK_POINT__2)
	{
		// ESC.Center ...
		if(bActive__ESC_POWER_CENTER_USE)
		{
			sCH__RESULT_CH1_ESC_CHUCKING_VOLTAGE_READING_POINT2->Get__DATA(var_data);
			check_vol__center = atof(var_data);

			sCH__RESULT_CH1_ESC_CHUCKING_CURRENT_READING_POINT2->Get__DATA(var_data);
			check_current__center = atof(var_data);
		}
		// ESC.Edge ...
		if(bActive__ESC_POWER_EDGE_USE)
		{
			sCH__RESULT_CH2_ESC_CHUCKING_VOLTAGE_READING_POINT2->Get__DATA(var_data);
			check_vol__edge = atof(var_data);

			sCH__RESULT_CH2_ESC_CHUCKING_CURRENT_READING_POINT2->Get__DATA(var_data);
			check_current__edge = atof(var_data);
		}
	}
	else if(check_point == CHECK_POINT__IO)
	{
		// ESC.Center ...
		if(bActive__ESC_POWER_CENTER_USE)
		{
			aiEXT_CH__ESC_VOLTAGE_CENTER->Get__DATA(var_data);
			check_vol__center = atof(var_data);

			aiEXT_CH__ESC_CURRENT_CENTER->Get__DATA(var_data);
			check_current__center = atof(var_data);
		}
		// ESC.Edge ...
		if(bActive__ESC_POWER_EDGE_USE)
		{
			aiEXT_CH__ESC_VOLTAGE_EDGE->Get__DATA(var_data);
			check_vol__edge = atof(var_data);

			aiEXT_CH__ESC_CURRENT_EDGE->Get__DATA(var_data);
			check_current__edge = atof(var_data);
		}
	}
	else
	{
		return 1;
	}

	// ESC.Center ...
	if(bActive__ESC_POWER_CENTER_USE)
	{
		aoEXT_CH__ESC_VOLTAGE_CENTER->Get__DATA(var_data);
		hv_set__center = atof(var_data);

		//
		aCH__CFG_ESC_CENTER_CHUCKING_VOLTAGE_WARNING->Get__DATA(var_data);
		cfg_warning__vol_per = atof(var_data);
		ref_warning__vol_min = hv_set__center * (1.0 - cfg_warning__vol_per / 100.0);
		ref_warning__vol_max = hv_set__center * (1.0 + cfg_warning__vol_per / 100.0);

		aCH__CFG_ESC_CENTER_CHUCKING_VOLTAGE_FAULT->Get__DATA(var_data);
		cfg_fault__vol_per = atof(var_data);
		ref_fault__vol_min = hv_set__center * (1.0 - cfg_fault__vol_per / 100.0);
		ref_fault__vol_max = hv_set__center * (1.0 + cfg_fault__vol_per / 100.0);			

		aCH__CFG_ESC_CENTER_VOLTAGE_THRESHOLD->Get__DATA(var_data);
		cfg__vol_high_limit = atof(var_data);

		aCH__CFG_ESC_CENTER_CURRENT_LIMIT->Get__DATA(var_data);
		cfg__current_high_limit = atof(var_data);

		// ...
		double abs__cur_vol = check_vol__center;
		double abs__min_vol = ref_warning__vol_min;
		double abs__max_vol = ref_warning__vol_max;

		if(abs__cur_vol < 0)		abs__cur_vol = -abs__cur_vol;
		if(abs__min_vol < 0)		abs__min_vol = -abs__min_vol;
		if(abs__max_vol < 0)		abs__max_vol = -abs__max_vol;

		if((abs__cur_vol > abs__max_vol)
		|| (abs__cur_vol < abs__min_vol))
		{
			err_check = 1;

			if(alm_report > 0)
			{
				int alm_id = ALID__ESC_CENTER_VOLTAGE__WARNING_RANGE;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("current center voltage <- %.1f (V) \n", check_vol__center);
				alm_msg += alm_bff;
				alm_bff.Format("config warning min. center voltage <- %.1f (V) \n", ref_warning__vol_min);
				alm_msg += alm_bff;
				alm_bff.Format("config warning max. center voltage <- %.1f (V) \n", ref_warning__vol_max);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			}
		}

		// ...
		abs__min_vol = ref_fault__vol_min;
		abs__max_vol = ref_fault__vol_max;

		if(abs__min_vol < 0)		abs__min_vol = -abs__min_vol;
		if(abs__max_vol < 0)		abs__max_vol = -abs__max_vol;

		if((abs__cur_vol > abs__max_vol)
			|| (abs__cur_vol < abs__min_vol))
		{
			err_check = 1;

			if(alm_report > 0)
			{
				int alm_id = ALID__ESC_CENTER_VOLTAGE__FAULT_RANGE;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("current center voltage <- %.1f (V) \n", check_vol__center);
				alm_msg += alm_bff;
				alm_bff.Format("config fault min. center voltage <- %.1f (V) \n", ref_fault__vol_min);
				alm_msg += alm_bff;
				alm_bff.Format("config fault max. center voltage <- %.1f (V) \n", ref_fault__vol_max);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			}
		}

		// ...
		double abs__high_limit = cfg__vol_high_limit;

		if(abs__high_limit < 0)		abs__high_limit = -abs__high_limit;

		if(abs__cur_vol > abs__high_limit)
		{
			err_check = 1;

			if(alm_report > 0)
			{
				int alm_id = ALID__ESC_CENTER_VOLTAGE__HIGH_LIMIT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("current center voltage <- %.1f (V) \n", check_vol__center);
				alm_msg += alm_bff;
				alm_bff.Format("config high limit center voltage <- %.1f (V) \n", cfg__vol_high_limit);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			}
		}

		if(check_current__center > cfg__current_high_limit)
		{
			err_check = 1;

			if(alm_report > 0)
			{
				int alm_id = ALID__ESC_CENTER_CURRENT__HIGH_LIMIT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("ESC_Center current <- %.1f (mA) \n", check_current__center);
				alm_msg += alm_bff;
				alm_bff.Format("config high limit center current <- %.1f (mA) \n", cfg__current_high_limit);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			}
		}
	}
	// ESC.Edge ...
	if(bActive__ESC_POWER_EDGE_USE)
	{
		aoEXT_CH__ESC_VOLTAGE_EDGE->Get__DATA(var_data);
		hv_set__edge = atof(var_data);

		//
		aCH__CFG_ESC_EDGE_CHUCKING_VOLTAGE_WARNING->Get__DATA(var_data);
		cfg_warning__vol_per = atof(var_data);
		ref_warning__vol_min = hv_set__edge * (1.0 - cfg_warning__vol_per / 100.0);
		ref_warning__vol_max = hv_set__edge * (1.0 + cfg_warning__vol_per / 100.0);

		aCH__CFG_ESC_EDGE_CHUCKING_VOLTAGE_FAULT->Get__DATA(var_data);
		cfg_fault__vol_per = atof(var_data);
		ref_fault__vol_min = hv_set__edge * (1.0 - cfg_fault__vol_per / 100.0);
		ref_fault__vol_max = hv_set__edge * (1.0 + cfg_fault__vol_per / 100.0);			

		aCH__CFG_ESC_EDGE_VOLTAGE_THRESHOLD->Get__DATA(var_data);
		cfg__vol_high_limit = atof(var_data);

		aCH__CFG_ESC_EDGE_CURRENT_LIMIT->Get__DATA(var_data);
		cfg__current_high_limit = atof(var_data);

		// ...
		double abs__cur_vol = check_vol__edge;
		double abs__min_vol = ref_warning__vol_min;
		double abs__max_vol = ref_warning__vol_max;

		if(abs__cur_vol < 0)		abs__cur_vol = -abs__cur_vol;
		if(abs__min_vol < 0)		abs__min_vol = -abs__min_vol;
		if(abs__max_vol < 0)		abs__max_vol = -abs__max_vol;

		if((abs__cur_vol > abs__max_vol)
		|| (abs__cur_vol < abs__min_vol))
		{
			err_check = 1;

			if(alm_report > 0)
			{
				int alm_id = ALID__ESC_EDGE_VOLTAGE__WARNING_RANGE;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("current edge voltage <- %.1f (V) \n", check_vol__edge);
				alm_msg += alm_bff;
				alm_bff.Format("config warning min. edge voltage <- %.1f (V) \n", ref_warning__vol_min);
				alm_msg += alm_bff;
				alm_bff.Format("config warning max. edge voltage <- %.1f (V) \n", ref_warning__vol_max);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			}
		}

		// ...
		abs__min_vol = ref_fault__vol_min;
		abs__max_vol = ref_fault__vol_max;

		if(abs__min_vol < 0)		abs__min_vol = -abs__min_vol;
		if(abs__max_vol < 0)		abs__max_vol = -abs__max_vol;

		if((abs__cur_vol > abs__max_vol)
			|| (abs__cur_vol < abs__min_vol))
		{
			err_check = 1;

			if(alm_report > 0)
			{
				int alm_id = ALID__ESC_EDGE_VOLTAGE__FAULT_RANGE;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("current edge voltage <- %.1f (V) \n", check_vol__edge);
				alm_msg += alm_bff;
				alm_bff.Format("config fault min. edge voltage <- %.1f (V) \n", ref_fault__vol_min);
				alm_msg += alm_bff;
				alm_bff.Format("config fault max. edge voltage <- %.1f (V) \n", ref_fault__vol_max);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			}
		}

		// ...
		double abs__high_limit = cfg__vol_high_limit;

		if(abs__high_limit < 0)		abs__high_limit = -abs__high_limit;

		if(abs__cur_vol > abs__high_limit)
		{
			err_check = 1;

			if(alm_report > 0)
			{
				int alm_id = ALID__ESC_EDGE_VOLTAGE__HIGH_LIMIT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("current edge voltage <- %.1f (V) \n", check_vol__edge);
				alm_msg += alm_bff;
				alm_bff.Format("config high limit edge voltage <- %.1f (V) \n", cfg__vol_high_limit);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			}
		}

		if(check_current__edge > cfg__current_high_limit)
		{
			err_check = 1;

			if(alm_report > 0)
			{
				int alm_id = ALID__ESC_EDGE_CURRENT__HIGH_LIMIT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("ESC_Edge current <- %.1f (mA) \n", check_current__edge);
				alm_msg += alm_bff;
				alm_bff.Format("config high limit edge current <- %.1f (mA) \n", cfg__current_high_limit);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			}
		}
	}

	if(err_check > 0)
	{
		return -1;
	}
	return 1;
}
int  CObj__ESC_OBJ::
Fnc__HE_ERROR_CHECK(CII_OBJECT__ALARM* p_alarm, 
					const int he_type, 
					const int check_point,
					const int alm_report)
{
	double check_pressure = 0.0;
	double check_flow = 0.0;

	double set_pressure = 0.0;

	double cfg__pressure_warning = 0.0;
	double cfg__pressure_fault = 0.0;

	double ref_warning__pressure_min = 0.0;
	double ref_warning__pressure_max = 0.0;

	double ref_fault__pressure_min = 0.0;
	double ref_fault__pressure_max = 0.0;

	double cfg__flow_min = 0.0;
	double cfg__flow_max = 0.0;

	int err_check = -1;
	CString var_data;

	// ...
	int alm_id__pressure_warning;
	int alm_id__pressure_fault;

	int alm_id__flow_min_threshold;
	int alm_id__flow_max_threshold;

	if(he_type == HE_TYPE__CENTER)
	{
		alm_id__pressure_warning = ALID__HE_CENTER_PRESSURE_WARNING;
		alm_id__pressure_fault   = ALID__HE_CENTER_PRESSURE_FAULT;

		alm_id__flow_min_threshold = ALID__HE_CENTER_FLOW_MIN_THRESHOLD;
		alm_id__flow_max_threshold = ALID__HE_CENTER_FLOW_MAX_THREASHOLD;

		if(check_point == CHECK_POINT__1)
		{
			sCH__RESULT_HE_CENTER_PRESSURE_READING_POINT1->Get__DATA(var_data);
			check_pressure = atof(var_data);

			sCH__RESULT_HE_CENTER_FLOW_READING_POINT1->Get__DATA(var_data);
			check_flow = atof(var_data);
		}
		else if(check_point == CHECK_POINT__2)
		{
			sCH__RESULT_HE_CENTER_PRESSURE_READING_POINT2->Get__DATA(var_data);
			check_pressure = atof(var_data);

			sCH__RESULT_HE_CENTER_FLOW_READING_POINT2->Get__DATA(var_data);
			check_flow = atof(var_data);
		}
		else if(check_point == CHECK_POINT__IO)
		{
			sCH__MON_He_Pressure_CENTER->Get__DATA(var_data);
			check_pressure = atof(var_data);

			sCH__MON_He_Flow_CENTER->Get__DATA(var_data);
			check_flow = atof(var_data);
		}
		else
		{
			return 1;
		}

		// ...
		{
			aoEXT_CH__He_Pressure_CENTER->Get__DATA(var_data);
			set_pressure = atof(var_data);

			aCH__CFG_HE_CENTER_PRESSURE_WARNING->Get__DATA(var_data);
			cfg__pressure_warning = atof(var_data);
			ref_warning__pressure_min = set_pressure * (1.0 - (cfg__pressure_warning / 100.0));
			ref_warning__pressure_max = set_pressure * (1.0 + (cfg__pressure_warning / 100.0));

			aCH__CFG_HE_CENTER_PRESSURE_FAULT->Get__DATA(var_data);
			cfg__pressure_fault = atof(var_data);
			ref_fault__pressure_min = set_pressure * (1.0 - (cfg__pressure_fault / 100.0));
			ref_fault__pressure_max = set_pressure * (1.0 + (cfg__pressure_fault / 100.0));

			aCH__MON_HE_CENTER_FLOW_MIN_THRESHOLD->Get__DATA(var_data);
			cfg__flow_min = atof(var_data);

			aCH__MON_HE_CENTER_FLOW_MAX_THRESHOLD->Get__DATA(var_data);
			cfg__flow_max = atof(var_data);
		}
	}
	else if(he_type == HE_TYPE__EDGE)
	{
		alm_id__pressure_warning = ALID__HE_EDGE_PRESSURE_WARNING;
		alm_id__pressure_fault   = ALID__HE_EDGE_PRESSURE_FAULT;

		alm_id__flow_min_threshold = ALID__HE_EDGE_FLOW_MIN_THRESHOLD;
		alm_id__flow_max_threshold = ALID__HE_EDGE_FLOW_MAX_THRESHOLD;

		if(check_point == CHECK_POINT__1)
		{
			sCH__RESULT_HE_EDGE_PRESSURE_READING_POINT1->Get__DATA(var_data);
			check_pressure = atof(var_data);

			sCH__RESULT_HE_EDGE_FLOW_READING_POINT1->Get__DATA(var_data);
			check_flow = atof(var_data);
		}
		else if(check_point == CHECK_POINT__2)
		{
			sCH__RESULT_HE_EDGE_PRESSURE_READING_POINT2->Get__DATA(var_data);
			check_pressure = atof(var_data);

			sCH__RESULT_HE_EDGE_FLOW_READING_POINT2->Get__DATA(var_data);
			check_flow = atof(var_data);
		}
		else if(check_point == CHECK_POINT__IO)
		{
			sCH__MON_He_Pressure_EDGE->Get__DATA(var_data);
			check_pressure = atof(var_data);

			sCH__MON_He_Flow_EDGE->Get__DATA(var_data);
			check_flow = atof(var_data);
		}
		else
		{
			return 1;
		}

		// ...
		{
			aoEXT_CH__He_Pressure_EDGE->Get__DATA(var_data);
			set_pressure = atof(var_data);

			aCH__CFG_HE_EDGE_PRESSURE_WARNING->Get__DATA(var_data);
			cfg__pressure_warning = atof(var_data);
			ref_warning__pressure_min = set_pressure * (1.0 - (cfg__pressure_warning / 100.0));
			ref_warning__pressure_max = set_pressure * (1.0 + (cfg__pressure_warning / 100.0));

			aCH__CFG_HE_EDGE_PRESSURE_FAULT->Get__DATA(var_data);
			cfg__pressure_fault = atof(var_data);
			ref_fault__pressure_min = set_pressure * (1.0 - (cfg__pressure_fault / 100.0));
			ref_fault__pressure_max = set_pressure * (1.0 + (cfg__pressure_fault / 100.0));

			aCH__MON_HE_EDGE_FLOW_MIN_THRESHOLD->Get__DATA(var_data);
			cfg__flow_min = atof(var_data);

			aCH__MON_HE_EDGE_FLOW_MAX_THRESHOLD->Get__DATA(var_data);
			cfg__flow_max = atof(var_data);
		}
	}
	else
	{
		return 1;
	}

	if(set_pressure < 0.001)
	{
		ref_warning__pressure_min = 0.0;
		ref_warning__pressure_max = 1.0;

		ref_fault__pressure_min = 0.0;
		ref_fault__pressure_max = 1.0;
	}

	if(cfg__pressure_warning > 0.001)
	{
		if((check_pressure > ref_warning__pressure_max)
		|| (check_pressure < ref_warning__pressure_min))
		{
			err_check = 0;

			if(alm_report > 0)
			{
				int alm_id = alm_id__pressure_warning;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("current he pressure  <- %.1f (torr) \n", check_pressure);
				alm_msg += alm_bff;
				alm_bff.Format("config ref min warning <- %.1f (torr) \n", ref_warning__pressure_min);
				alm_msg += alm_bff;
				alm_bff.Format("config ref max warning <- %.1f (torr) \n", ref_warning__pressure_max);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
			}
		}
	}
	if(cfg__pressure_fault > 0.001)
	{
		if((check_pressure > ref_fault__pressure_max)
			|| (check_pressure < ref_fault__pressure_min))
		{
			err_check = 1;

			if(alm_report > 0)
			{
				int alm_id = alm_id__pressure_fault;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("current he pressure  <- %.1f (torr) \n", check_pressure);
				alm_msg += alm_bff;
				alm_bff.Format("config ref min fault <- %.1f (torr) \n", ref_fault__pressure_min);
				alm_msg += alm_bff;
				alm_bff.Format("config ref max fault <- %.1f (torr) \n", ref_fault__pressure_max);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
			}
		}
	}

	if(check_flow < cfg__flow_min)
	{
		err_check = 1;

		if(alm_report > 0)
		{
			int alm_id = alm_id__flow_min_threshold;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			alm_bff.Format("current he flow <- %.1f (sccm) \n", check_flow);
			alm_msg += alm_bff;
			alm_bff.Format("config min. threshold <- %.1f (sccm) \n", cfg__flow_min);
			alm_msg += alm_bff;

			p_alarm->Check__ALARM(alm_id, r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
		}
	}
	if(check_flow > cfg__flow_max)
	{
		err_check = 1;

		if(alm_report > 0)
		{
			int alm_id = alm_id__flow_max_threshold;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			alm_bff.Format("current he flow <- %.1f (sccm) \n", check_flow);
			alm_msg += alm_bff;
			alm_bff.Format("config max. threshold <- %.1f (sccm) \n", cfg__flow_max);
			alm_msg += alm_bff;

			p_alarm->Check__ALARM(alm_id, r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
		}
	}

	if(err_check >  0)		return -1;
	if(err_check == 0)		return 0;

	return 1;
}

int  CObj__ESC_OBJ::
Fnc__DECHUCK(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm,
			 const int dechuck_mode)
{
	if(dechuck_mode  < 0)							return -101;
	if(dechuck_mode >= DEF__DECHUCK_MODE_SIZE)		return -102;

	// ...
	{
		dCH__MON_ESC_CTRL_ACTIVE->Set__DATA(STR__ON);
	}

	// ...
	SCX__ASYNC_TIMER_CTRL x_app_timer;
	x_app_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__APP_TIMER_COUNT->Get__CHANNEL_NAME());
	x_app_timer->STOP_ZERO();

	// ...
	CString log_msg;
	CString log_bff;
	CString var_data;

	int skip__proc_dechuck = -1;
	int skip__he_dechuck = -1;

	if(bActive__HE_CONTROL_CENTER_USE)
	{
		if(doEXT_CH__HE_VALVE_FINAL_OUT_CENTER->Check__DATA(STR__Close) > 0)		skip__he_dechuck = 1;
	}
	if(bActive__HE_CONTROL_EDGE_USE)
	{
		if(doEXT_CH__HE_VALVE_FINAL_OUT_EDGE->Check__DATA(STR__Close) > 0)			skip__he_dechuck = 1;
	}

	// He Dump ...
	{
		// DPC.Zero ...
		{
			doEXT_CH__HE_VALVE_SUPPLY->Set__DATA(STR__Close);

			if(bActive__HE_CONTROL_CENTER_USE)				aoEXT_CH__He_Pressure_CENTER->Set__VALUE(0.0);
			if(bActive__HE_CONTROL_EDGE_USE)				aoEXT_CH__He_Pressure_EDGE->Set__VALUE(0.0);
		}

		pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__DUMP_FLOW);
	}

	if((dEXT_CH__WAFER_STATUS->Check__DATA(STR__NONE) > 0)
	|| (skip__proc_dechuck > 0))
	{
		// ...
		{
			doEXT_CH__HE_VALVE_SUPPLY->Set__DATA(STR__Close);
			pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__DUMP_FLOW);

			// Center
			if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(0.0);
			if(bActive__ESC_POWER_CENTER_USE)			aoEXT_CH__ESC_VOLTAGE_CENTER->Set__VALUE(0.0);

			// Edge
			if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(0.0);
			if(bActive__ESC_POWER_EDGE_USE)				aoEXT_CH__ESC_VOLTAGE_EDGE->Set__VALUE(0.0);
			doEXT_CH__ESC_VOLTAGE_ON->Set__DATA(STR__Off); // KMS
			doEXT_CH__ESC_All_Voltage->Set__DATA(STR__Off);
		}

		dCH__MON_CHUCK_STATUS->Set__DATA(STR__DECHUCKED);

		// ...
		{
			CString log_bff;

			CString ch_name;
			CString ch_data;

			log_msg = "Fnc__CHUCK() : Already ESC Dechucked ...";	

			ch_name = dCH__MON_CHUCK_STATUS->Get__CHANNEL_NAME();
			dCH__MON_CHUCK_STATUS->Get__DATA(ch_data);
			log_bff.Format("%s <- %s \n", ch_name,ch_data);
			log_msg += log_bff;

			ch_name = dEXT_CH__WAFER_STATUS->Get__CHANNEL_NAME();
			dEXT_CH__WAFER_STATUS->Get__DATA(ch_data);
			log_bff.Format("%s <- %s \n", ch_name,ch_data);
			log_msg += log_bff;

			xLOG_CTRL->WRITE__LOG(log_msg);	

			log_msg = "Already ESC Dechucked ...";	
			sCH__APP_LOG_SUB_MSG->Set__DATA(log_msg);
		}
		return 1;
	}

	if(dCH__CFG_INTERLOCK_MODE_ALL->Check__DATA(STR__DISABLE) > 0)
	{
		int alarm_id = ALID__INTERLOCK_ALL_DISABLE;
		CString r_act;

		p_alarm->Popup__ALARM(alarm_id, r_act);

		if(r_act.CompareNoCase(STR__YES) != 0)		return -101;
	}
	else
	{
		if(Fnc__HV_SENSOR_INTERLOCK_CHECK(p_alarm) < 0)
		{
			return -1;
		}
	}

	dCH__MON_CHUCK_STATUS->Set__DATA(STR__DECHUCKING);

	// ...
	double cfg__he_dump_sec;

	SCX__TIMER_CTRL timer_ctrl;
	timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);

	// He Initial ...
	if(skip__he_dechuck < 0)
	{
		aCH__CFG_He_DUMP_TIME_BEFORE_DECHUCK->Get__DATA(var_data);
		cfg__he_dump_sec = atof(var_data);

		// Time Delay ...
		{
			x_app_timer->START__COUNT_UP(9999);

			log_msg.Format("He Dump Waiting (%.f sec)", cfg__he_dump_sec);	
			sCH__APP_LOG_SUB_MSG->Set__DATA(log_msg);

			if(timer_ctrl->WAIT(cfg__he_dump_sec) < 0)
			{
				return -11;
			}

			x_app_timer->STOP();
		}
	}

	// ...
	bool active__dump_valve_close = false;
	if(dCH__CFG_He_DUMP_VALVE_CLOSE_DURING_DECHUCK->Check__DATA(STR__YES) > 0)			active__dump_valve_close = true;

	// HV : STEPx Control ...
	{
		log_msg.Format("ESC Voltage Control (Step)");	
		sCH__APP_LOG_SUB_MSG->Set__DATA(log_msg);

		xLOG_CTRL->WRITE__LOG(log_msg);	

		// ...
		SCX__TIMER_CTRL x_timer_ctrl;
		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->INIT__COUNT_UP();

		int i_limit = DEF_DECHUCK__STEP_SIZE;
		int i;

		for(i=0; i<i_limit; i++)
		{
			double cfg_volt__center = aCH__CFG_CENTER_DECHUCK_X__STEPx_VOLT[dechuck_mode][i]->Get__VALUE();
			double cfg_volt__edge   = aCH__CFG_EDGE_DECHUCK_X__STEPx_VOLT[dechuck_mode][i]->Get__VALUE();
			double cfg_he_set = aCH__CFG_DECHUCK_X__STEPx_HE[dechuck_mode][i]->Get__VALUE();
			double cfg_sec = aCH__CFG_DECHUCK_X__STEPx_TIME[dechuck_mode][i]->Get__VALUE();

			if(cfg_sec < 0.1)
			{
				break;
			}

			// ...
			{
				// ...
				{
					log_msg.Format("Delay Time <- %.1f sec \n", cfg_sec);
					sCH__APP_LOG_SUB_MSG->Set__DATA(log_msg);
				}

				// ...
				{
					log_msg = "\n";

					log_bff.Format("Step (%1d) ... \n", i+1);
					log_msg += log_bff;

					if(bActive__ESC_POWER_CENTER_USE)
					{
						log_bff.Format(" * ESC Center Voltage Set <- %.1f V \n", cfg_volt__center);
						log_msg += log_bff;
					}
					if(bActive__ESC_POWER_EDGE_USE)
					{
						log_bff.Format(" * ESC Edge Voltage Set <- %.1f V \n", cfg_volt__edge);
						log_msg += log_bff;
					}

					// ...
					{
						log_bff.Format(" * He_Flow <- %.1f sccm \n", cfg_he_set);
						log_msg += log_bff;

						log_bff.Format(" * Delay Time <- %.1f sec \n", cfg_sec);
						log_msg += log_bff;
					}

					xLOG_CTRL->WRITE__LOG(log_msg);	
				}

				// ...
				{
					if(bActive__ESC_POWER_CENTER_USE)			aoEXT_CH__ESC_VOLTAGE_CENTER->Set__VALUE(cfg_volt__center);
					if(bActive__ESC_POWER_EDGE_USE)				aoEXT_CH__ESC_VOLTAGE_EDGE->Set__VALUE(cfg_volt__edge);

					doEXT_CH__ESC_All_Voltage->Set__DATA(STR__On);
					doEXT_CH__ESC_VOLTAGE_ON->Set__DATA(STR__On); //KMS Voltage ON
				}
				

				// He 사용기능 수정
				if(cfg_he_set > 0)
				{
					if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(cfg_he_set);
					if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(cfg_he_set);

					pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__FINAL_FLOW);
				}
				else
				{
					if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(0.0);
					if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(0.0);

					if(active__dump_valve_close)				pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__CLOSE);
					else										pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__DUMP_FLOW);
				}

				// ...
				{
					x_app_timer->START__COUNT_UP(9999);

					if(x_timer_ctrl->POLL(cfg_sec) <= 0)
					{
						return -1005;
					}

					x_app_timer->STOP();
				}
			}
		}
	}

	// Last Voltage Control ...
	{
		SCX__TIMER_CTRL x_timer_ctrl;
		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->INIT__COUNT_UP();

		aCH__CFG_CENTER_DECHUCK_X__LAST_VOLT[dechuck_mode]->Get__DATA(var_data);
		double cfg_volt_center = atof(var_data);

		aCH__CFG_EDGE_DECHUCK_X__LAST_VOLT[dechuck_mode]->Get__DATA(var_data);
		double cfg_volt_edge = atof(var_data);

		aCH__CFG_DECHUCK_X__LAST_HE[dechuck_mode]->Get__DATA(var_data);
		double cfg_he_set = atof(var_data);

		aCH__CFG_DECHUCK_X__LAST_TIME[dechuck_mode]->Get__DATA(var_data);
		double cfg_sec = atof(var_data);

		if(cfg_sec > 0.1)
		{
			log_msg.Format(" Last Delay Time(%.1f sec)", cfg_sec);	
			sCH__APP_LOG_SUB_MSG->Set__DATA(log_msg);

			// ...
			{
				log_msg += "\n";
				
				if(bActive__ESC_POWER_CENTER_USE)
				{
					log_bff.Format("Last Center_Volt(%.1f V) \n", cfg_volt_center);
					log_msg += log_bff;
				}
				if(bActive__ESC_POWER_EDGE_USE)
				{
					log_msg.Format(" Last Edge_Volt(%.1f V) \n", cfg_volt_edge);
					log_msg += log_bff;
				}

				// ...
				{
					log_msg += "\n";

					log_bff.Format("Last He_Flow <- %.1f sccm \n", cfg_he_set);
					log_msg += log_bff;

					log_bff.Format(" Last Delay Time(%.1f sec)", cfg_sec);	
					log_msg += log_bff;
				}

				xLOG_CTRL->WRITE__LOG(log_msg);	
			}

			// ...
			{
				if(bActive__ESC_POWER_CENTER_USE)			aoEXT_CH__ESC_VOLTAGE_CENTER->Set__VALUE(cfg_volt_center);
				if(bActive__ESC_POWER_EDGE_USE)				aoEXT_CH__ESC_VOLTAGE_EDGE->Set__VALUE(cfg_volt_edge);

				doEXT_CH__ESC_All_Voltage->Set__DATA(STR__On);
				doEXT_CH__ESC_VOLTAGE_ON->Set__DATA(STR__On); //KMS Voltage ON
			}

			if(cfg_he_set > 0)
			{
				if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(cfg_he_set);
				if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(cfg_he_set);

				pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__FINAL_FLOW);
			}
			else
			{
				if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(0.0);
				if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(0.0);

				if(active__dump_valve_close)				pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__CLOSE);
				else										pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__DUMP_FLOW);
			}

			// ...
			{
				x_app_timer->START__COUNT_UP(9999);
			
				if(x_timer_ctrl->POLL(cfg_sec) <= 0)
				{
					return -12;
				}

				x_app_timer->STOP();
			}
		}
	}

	// ...
	{
		if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(0.0);
		if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(0.0);

		if(bActive__ESC_POWER_CENTER_USE)			aoEXT_CH__ESC_VOLTAGE_CENTER->Set__VALUE(0.0);
		if(bActive__ESC_POWER_EDGE_USE)				aoEXT_CH__ESC_VOLTAGE_EDGE->Set__VALUE(0.0);
		doEXT_CH__ESC_VOLTAGE_ON->Set__DATA(STR__Off); // KMS
		doEXT_CH__ESC_All_Voltage->Set__DATA(STR__Off);
	}

	if(dechuck_mode == 0)
	{
		if(dCH__CFG_He_DECHUCK_CHECK_APPLY->Check__DATA(STR__DISABLE) > 0)
		{
			// Bypass Flow : Not Check ...
			{
				sCH__CUR_HE_CENTER_BYPASS_FLOW_FOR_DECHUCK_VERIFY->Set__DATA(STR__Pass);
			}
		}
		else 
		{	
			if(Fnc__DECHUCK_VERIFY(p_variable, p_alarm) < 0)
			{
				return -1;
			}
		}

		// He Dump ...
		{
			// DPC.Zero ...
			{
				doEXT_CH__HE_VALVE_SUPPLY->Set__DATA(STR__Close);

				if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(0.0);
				if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(0.0);
			}

			pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__DUMP_FLOW);
		}
	}

	dCH__MON_CHUCK_STATUS->Set__DATA(STR__DECHUCKED);
	return 1;
}

int  CObj__ESC_OBJ
::Fnc__DECHUCK_VERIFY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	dCH__MON_HE_FLOW_CTRL_ACTIVE->Set__DATA(STR__ON);

	// Pressure Setting ...
	{
		sCH__APP_LOG_SUB_MSG->Set__DATA("Pressure Setting ...");

		pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__BYPASS_FLOW);

		Sleep(900);

		// ...
		double cfg__center_pressure = aCH__CFG_HE_CENTER_PRESSURE_DURING_DECHUCK_VERIFY->Get__VALUE();
		double cfg__edge_pressure   = aCH__CFG_HE_EDGE_PRESSURE_DURING_DECHUCK_VERIFY->Get__VALUE();

		if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(cfg__center_pressure);
		if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(cfg__edge_pressure);

		doEXT_CH__HE_VALVE_SUPPLY->Set__DATA(STR__Open);

		if(iActive__SIM_MODE > 0)
		{
			if(bActive__HE_CONTROL_CENTER_USE)			aiEXT_CH__He_Flow_CENTER_IO->Set__VALUE(cfg__center_pressure / 2.0);
			if(bActive__HE_CONTROL_EDGE_USE)			aiEXT_CH__He_Flow_EDGE_IO->Set__VALUE(cfg__edge_pressure / 2.0);
		}
	}

	// Bypass Flow Stable ...
	{
		sCH__APP_LOG_SUB_MSG->Set__DATA("Bypass Flow Stable Delay ...");

		SCX__TIMER_CTRL x_app_timer;
		x_app_timer->REGISTER__ABORT_OBJECT(sObject_Name);
		x_app_timer->REGISTER__COUNT_CHANNEL(sCH__APP_TIMER_COUNT->Get__CHANNEL_NAME());

		double cfg__stable_sec = aCH__CFG_HE_BYPASS_FLOW_STABLE_TIME_FOR_DECHUCK_VERIFY->Get__VALUE();

		if(x_app_timer->WAIT(cfg__stable_sec) < 0)
		{
			return -1;
		}
	}

	// Bypass Flow Check ...
	{
		sCH__APP_LOG_SUB_MSG->Set__DATA("Bypass Flow Check ...");

		double cur__center_flow = aiEXT_CH__He_Flow_CENTER_IO->Get__VALUE();
		CString var_data;

		var_data.Format("%.1f", cur__center_flow);
		sCH__CUR_HE_CENTER_BYPASS_FLOW_FOR_DECHUCK_VERIFY->Set__DATA(var_data);
	}

	// Final Flow Stable ...
	{
		sCH__APP_LOG_SUB_MSG->Set__DATA("Final Flow Stable Delay ...");

		pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__FINAL_FLOW);

		doEXT_CH__HE_VALVE_SUPPLY->Set__DATA(STR__Open);

		if(iActive__SIM_MODE > 0)
		{
			double cfg__min_leak = aCH__CFG_HE_MINIMUM_LEAK_FOR_DECHUCK_VERIFY->Get__VALUE();
			cfg__min_leak += 1.0;

			if(bActive__HE_CONTROL_CENTER_USE)			aiEXT_CH__He_Flow_CENTER_IO->Set__VALUE(cfg__min_leak);
			if(bActive__HE_CONTROL_EDGE_USE)			aiEXT_CH__He_Flow_EDGE_IO->Set__VALUE(cfg__min_leak);
		}

		SCX__TIMER_CTRL x_app_timer;
		x_app_timer->REGISTER__ABORT_OBJECT(sObject_Name);
		x_app_timer->REGISTER__COUNT_CHANNEL(sCH__APP_TIMER_COUNT->Get__CHANNEL_NAME());

		double cfg__stable_sec = aCH__CFG_HE_FINAL_FLOW_STABLE_TIME_FOR_DECHUCK_VERIFY->Get__VALUE();

		if(x_app_timer->WAIT(cfg__stable_sec) < 0)
		{
			return -1;
		}
	}

	// Dechuck Verify ...
	{
		sCH__APP_LOG_SUB_MSG->Set__DATA("Dechuck Verify ...");

		CString var_data;

		double cur__center_flow = 0;
		double cur__edge_flow = 0;

		if(bActive__HE_CONTROL_CENTER_USE)
		{
			cur__center_flow = aiEXT_CH__He_Flow_CENTER_IO->Get__VALUE();
		}
		if(bActive__HE_CONTROL_EDGE_USE)
		{
			cur__edge_flow = aiEXT_CH__He_Flow_EDGE_IO->Get__VALUE();
		}

		sCH__CUR_HE_CENTER_BYPASS_FLOW_FOR_DECHUCK_VERIFY->Get__DATA(var_data);
		double ref__center_bypass = atof(var_data);

		sCH__CUR_HE_EDGE_BYPASS_FLOW_FOR_DECHUCK_VERIFY->Get__DATA(var_data);
		double ref__edge_bypass = atof(var_data);

		double cur__center_leak = cur__center_flow - ref__center_bypass;
		double cur__edge_leak   = cur__edge_flow   - ref__edge_bypass;

		double cfg__min_leak = aCH__CFG_HE_MINIMUM_LEAK_FOR_DECHUCK_VERIFY->Get__VALUE();

		bool active__leak_err = false;

		if(bActive__HE_CONTROL_CENTER_USE)
		{
			if(cur__center_leak < cfg__min_leak)		active__leak_err = true;
		}
		if(bActive__HE_CONTROL_EDGE_USE)
		{
			if(cur__edge_leak < cfg__min_leak)			active__leak_err = true;
		}

		if(active__leak_err)
		{
			int alm_id = ALID__HE_WAFER_MINIMUM_LEAK_SCCM;

			CString alm_msg;
			CString alm_bff;
			CString r_act;

			if(bActive__HE_CONTROL_CENTER_USE)
			{
				if(cur__center_leak < cfg__min_leak)
				{
					alm_bff.Format("current he center flow <- %.1f sccm \n", cur__center_flow);
					alm_msg += alm_bff;
					alm_bff.Format("current he center leak <- %.1f sccm \n", cur__center_leak);
					alm_msg += alm_bff;				
					alm_bff.Format("he center bypass flow  <- %.1f sccm \n", ref__center_bypass);
					alm_msg += alm_bff;			
					alm_msg += "\n";
				}
			}
			if(bActive__HE_CONTROL_EDGE_USE)
			{
				if(cur__edge_leak < cfg__min_leak)
				{
					alm_bff.Format("current he edge flow <- %.1f sccm \n", cur__edge_flow);
					alm_msg += alm_bff;
					alm_bff.Format("current he edge leak <- %.1f sccm \n", cur__edge_leak);
					alm_msg += alm_bff;				
					alm_bff.Format("he edge bypass flow  <- %.1f sccm \n", ref__edge_bypass);
					alm_msg += alm_bff;			
					alm_msg += "\n";
				}
			}

			alm_bff.Format("config Min. leak <- %.1f sccm \n", cfg__min_leak);

			p_alarm->Check__ALARM(alm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alm_id,alm_msg);
			return -1;
		}
	}

	// Test End ...
	{
		sCH__APP_LOG_SUB_MSG->Set__DATA("Test End ...");

		// DPC.Close ...
		{
			doEXT_CH__HE_VALVE_SUPPLY->Set__DATA(STR__Close);

			if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(0.0);
			if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(0.0);
		}

		pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__DUMP_FLOW);
	}
	return 1;
}

int  CObj__ESC_OBJ
::Fnc__VENT_READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if((dEXT_CH__WAFER_STATUS->Check__DATA(STR__NONE) > 0)
	|| (dCH__MON_CHUCK_STATUS->Check__DATA(STR__DECHUCKED) > 0))
	{
		dCH__MON_CHUCK_STATUS->Set__DATA(STR__DECHUCKED);

		return Fnc__HE_CLOSE(p_variable,p_alarm);
	}

	int r_flag = Fnc__DECHUCK(p_variable,p_alarm, 0);
	if(r_flag < 0)		return r_flag;

	return Fnc__HE_CLOSE(p_variable,p_alarm);
}
int  CObj__ESC_OBJ
::Fnc__PUMP_READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(dEXT_CH__WAFER_STATUS->Check__DATA(STR__NONE) > 0)
	{
		dCH__MON_CHUCK_STATUS->Set__DATA(STR__DECHUCKED);

		return Fnc__HE_CLOSE(p_variable,p_alarm);
	}

	if(dCH__MON_CHUCK_STATUS->Check__DATA(STR__DECHUCKED) > 0)
	{
		return Fnc__HE_CLOSE(p_variable,p_alarm);
	}
	return 1;
}

int CObj__ESC_OBJ::
Fnc__ESC_ABORT(CII_OBJECT__VARIABLE *p_variable,
			   CII_OBJECT__ALARM *p_alarm, 
			   const CString err_msg)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg  = "\n";
		log_bff.Format("Fnc__ESC_ABORT() : Error_Msg(%s)", err_msg);			
		log_msg += log_bff;
		log_msg += "\n";

		xLOG_CTRL->WRITE__LOG(log_msg);	
	}

	// ...
	{
		int delay_flag = -1;

		if(bActive__HE_CONTROL_CENTER_USE)
		{
			if(doEXT_CH__HE_VALVE_FINAL_OUT_CENTER->Check__DATA(STR__Close) < 0)			delay_flag = 1;
		}
		if(bActive__HE_CONTROL_EDGE_USE)
		{
			if(doEXT_CH__HE_VALVE_FINAL_OUT_EDGE->Check__DATA(STR__Close) < 0)				delay_flag = 1;
		}

		// ...
		{
			doEXT_CH__HE_VALVE_SUPPLY->Set__DATA(STR__Close);

			if(bActive__HE_CONTROL_CENTER_USE)			aoEXT_CH__He_Pressure_CENTER->Set__VALUE(0.0);
			if(bActive__HE_CONTROL_EDGE_USE)			aoEXT_CH__He_Pressure_EDGE->Set__VALUE(0.0);

			if(dCH__CFG_HE_VALVE_CLOSE_WHEN_ERROR->Check__DATA(STR__YES) > 0)
				pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__CLOSE);
			else
				pOBJ_CTRL__HE_VALVE->Call__OBJECT(_HE_VLV__DUMP_FLOW);
		}

		if(delay_flag > 0)
		{
			CString var_data;

			aCH__CFG_He_DUMP_TIME_BEFORE_DECHUCK->Get__DATA(var_data);
			double cfg_sec = atof(var_data);

			SCX__TIMER_CTRL x_timer;
			x_timer->WAIT(cfg_sec);
		}

		// ...
		{
			if(bActive__ESC_POWER_CENTER_USE)			aoEXT_CH__ESC_VOLTAGE_CENTER->Set__VALUE(0.0);
			if(bActive__ESC_POWER_EDGE_USE)				aoEXT_CH__ESC_VOLTAGE_EDGE->Set__VALUE(0.0);
			doEXT_CH__ESC_VOLTAGE_ON->Set__DATA(STR__Off); // KMS
			doEXT_CH__ESC_All_Voltage->Set__DATA(STR__Off);
		}

		if(dEXT_CH__WAFER_STATUS->Check__DATA(STR__NONE) < 0)
		{
			if((dCH__MON_CHUCK_STATUS->Check__DATA(STR__CHUCKED)   < 0)
			&& (dCH__MON_CHUCK_STATUS->Check__DATA(STR__DECHUCKED) < 0))
			{
				dCH__MON_CHUCK_STATUS->Set__DATA(STR__UNKNOWN);
			}
		}
		else
		{
			dCH__MON_CHUCK_STATUS->Set__DATA(STR__DECHUCKED);
		}
	}

	// ...
	{
		log_msg  = "\n";
		log_msg += "Fnc__ESC_ABORT() : Abort Complete ...";	
		log_msg += "\n";

		xLOG_CTRL->WRITE__LOG(log_msg);	
	}
	return 1;
}

