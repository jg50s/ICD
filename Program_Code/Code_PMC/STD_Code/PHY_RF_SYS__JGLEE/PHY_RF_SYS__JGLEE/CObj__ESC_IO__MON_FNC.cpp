#include "StdAfx.h"
#include <math.h>

#include "CObj__ESC_IO.h"
#include "CObj__ESC_IO__DEF.h"


//-----------------------------------------------------------------------------------
void CObj__ESC_IO::
Mon__REQ_CTRL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString cur_req;
	CString var_data;

	int loop_count = 0;

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.05);

		loop_count++;
		if(loop_count > 20)		loop_count = 1;

		if(loop_count == 1)
		{
			int check__err_esc     = p_alarm->Check__Posted_Internal_Alarm(iLIST_ALID__ESC);
			int check__err_he_flow = p_alarm->Check__Posted_Internal_Alarm(iLIST_ALID__HE_FLOW);

			if(check__err_esc > 0)			dCH__MON_ESC_ERROR_ACTIVE->Set__DATA(STR__ON);
			else							dCH__MON_ESC_ERROR_ACTIVE->Set__DATA(STR__OFF);

			if(check__err_he_flow > 0)		dCH__MON_HE_FLOW_ERROR_ACTIVE->Set__DATA(STR__ON);
			else							dCH__MON_HE_FLOW_ERROR_ACTIVE->Set__DATA(STR__OFF);
		}
		
		// REQ : 3WAY.VLV - CENTER ...
		if(bActive__CENTER_3WAY_VLV)
		{
			// SET.VLV ...
			cur_req = sCH__REQ_HE_FINAL_CENTER__3WAY_VLV->Get__STRING();
			
			if(cur_req.CompareNoCase("") != 0)
			{
				sCH__REQ_HE_FINAL_CENTER__3WAY_VLV->Set__DATA("");

				if(cur_req.CompareNoCase("CLOSE") == 0)
				{
					doEXT_CH__He_Final_Out_Vlv_CENTER->Set__DATA(STR__Close);
					if(bActive__He_Final_Dump_Vlv_CENTER)			doEXT_CH__He_Final_Dump_Vlv_CENTER->Set__DATA(STR__Close);
				}
				else if(cur_req.CompareNoCase("OPEN") == 0)
				{
					doEXT_CH__He_Final_Out_Vlv_CENTER->Set__DATA(STR__Open);
					if(bActive__He_Final_Dump_Vlv_CENTER)			doEXT_CH__He_Final_Dump_Vlv_CENTER->Set__DATA(STR__Close);
				}
				else if(cur_req.CompareNoCase("DUMP") == 0)
				{
					doEXT_CH__He_Final_Out_Vlv_CENTER->Set__DATA(STR__Close);
					if(bActive__He_Final_Dump_Vlv_CENTER)			doEXT_CH__He_Final_Dump_Vlv_CENTER->Set__DATA(STR__Open);
				}
				else if(cur_req.CompareNoCase("AL.OP") == 0)
				{
					doEXT_CH__He_Final_Out_Vlv_CENTER->Set__DATA(STR__Open);
					if(bActive__He_Final_Dump_Vlv_CENTER)			doEXT_CH__He_Final_Dump_Vlv_CENTER->Set__DATA(STR__Open);
				}
			}

			// GET.VLV ...
			CString cur_sts = "CLOSE";

			if(doEXT_CH__He_Final_Out_Vlv_CENTER->Check__DATA(STR__Open) > 0)
			{
				if(bActive__He_Final_Dump_Vlv_CENTER)			
				{
					if(doEXT_CH__He_Final_Dump_Vlv_CENTER->Check__DATA(STR__Open) > 0)		cur_sts = "AL.OP";
					else																	cur_sts = "OPEN";
				}
			}
			else
			{
				if(bActive__He_Final_Dump_Vlv_CENTER)			
				{
					if(doEXT_CH__He_Final_Dump_Vlv_CENTER->Check__DATA(STR__Open) > 0)		cur_sts = "DUMP";
				}
			}

			sCH__MON_HE_FINAL_CENTER__3WAY_VLV->Set__DATA(cur_sts);
		}
		// REQ : 3WAY.VLV - EDGE ...
		if(bActive__EDGE_3WAY_VLV)
		{
			// SET.VLV ...
			cur_req = sCH__REQ_HE_FINAL_EDGE__3WAY_VLV->Get__STRING();

			if(cur_req.CompareNoCase("") != 0)
			{
				sCH__REQ_HE_FINAL_EDGE__3WAY_VLV->Set__DATA("");

				if(cur_req.CompareNoCase("CLOSE") == 0)
				{
					doEXT_CH__He_Final_Out_Vlv_EDGE->Set__DATA(STR__Close);
					if(bActive__He_Final_Dump_Vlv_EDGE)				doEXT_CH__He_Final_Dump_Vlv_EDGE->Set__DATA(STR__Close);
				}
				else if(cur_req.CompareNoCase("OPEN") == 0)
				{
					doEXT_CH__He_Final_Out_Vlv_EDGE->Set__DATA(STR__Open);
					if(bActive__He_Final_Dump_Vlv_EDGE)				doEXT_CH__He_Final_Dump_Vlv_EDGE->Set__DATA(STR__Close);
				}
				else if(cur_req.CompareNoCase("DUMP") == 0)
				{
					doEXT_CH__He_Final_Out_Vlv_EDGE->Set__DATA(STR__Close);
					if(bActive__He_Final_Dump_Vlv_EDGE)				doEXT_CH__He_Final_Dump_Vlv_EDGE->Set__DATA(STR__Open);
				}
				else if(cur_req.CompareNoCase("AL.OP") == 0)
				{
					doEXT_CH__He_Final_Out_Vlv_EDGE->Set__DATA(STR__Open);
					if(bActive__He_Final_Dump_Vlv_EDGE)				doEXT_CH__He_Final_Dump_Vlv_EDGE->Set__DATA(STR__Open);
				}
			}

			// GET.VLV ...
			CString cur_sts = "CLOSE";

			if(doEXT_CH__He_Final_Out_Vlv_EDGE->Check__DATA(STR__Open) > 0)
			{
				if(bActive__He_Final_Dump_Vlv_EDGE)				
				{
					if(doEXT_CH__He_Final_Dump_Vlv_EDGE->Check__DATA(STR__Open) > 0)		cur_sts = "AL.OP";
					else																	cur_sts = "OPEN";
				}
			}
			else
			{
				if(bActive__He_Final_Dump_Vlv_EDGE)				
				{
					if(doEXT_CH__He_Final_Dump_Vlv_EDGE->Check__DATA(STR__Open) > 0)		cur_sts = "DUMP";
				}
			}

			sCH__MON_HE_FINAL_EDGE__3WAY_VLV->Set__DATA(cur_sts);
		}

		// ZERO-CAL - HE_PRESSURE.CENTER ...
		if(bActive__CENTER_USE)
		{
			if(sCH__ZERO_CAL_REQ_HE_PRESSURE_CENTER->Check__DATA(STR__YES) > 0)
			{
				sCH__ZERO_CAL_REQ_HE_PRESSURE_CENTER->Set__DATA("");

				aiEXT_CH__He_Pressure_CENTER_IO->Get__DATA(var_data);
				sCH__ZERO_CAL_He_Pressure_CENTER->Set__DATA(var_data);
			}
			if(sCH__ZERO_CAL_RESET_HE_PRESSURE_CENTER->Check__DATA(STR__YES) > 0)
			{
				sCH__ZERO_CAL_RESET_HE_PRESSURE_CENTER->Set__DATA("");

				sCH__ZERO_CAL_He_Pressure_CENTER->Set__DATA("0");
			}
		}
		// ZERO-CAL - HE_PRESSURE.EDGE ...
		if(bActive__EDGE_USE)
		{
			if(sCH__ZERO_CAL_REQ_HE_PRESSURE_EDGE->Check__DATA(STR__YES) > 0)
			{
				sCH__ZERO_CAL_REQ_HE_PRESSURE_EDGE->Set__DATA("");

				aiEXT_CH__He_Pressure_EDGE_IO->Get__DATA(var_data);
				sCH__ZERO_CAL_He_Pressure_EDGE->Set__DATA(var_data);
			}
			if(sCH__ZERO_CAL_RESET_HE_PRESSURE_EDGE->Check__DATA(STR__YES) > 0)
			{
				sCH__ZERO_CAL_RESET_HE_PRESSURE_EDGE->Set__DATA("");

				sCH__ZERO_CAL_He_Pressure_EDGE->Set__DATA("0");
			}
		}

		// ZERO-CAL - HE_FLOW.CENTER ...
		if(bActive__CENTER_USE)
		{
			if(sCH__ZERO_CAL_REQ_HE_FLOW_CENTER->Check__DATA(STR__YES) > 0)
			{
				sCH__ZERO_CAL_REQ_HE_FLOW_CENTER->Set__DATA("");

				aiEXT_CH__He_Flow_CENTER_IO->Get__DATA(var_data);
				sCH__ZERO_CAL_He_Flow_CENTER->Set__DATA(var_data);
			}
			if(sCH__ZERO_CAL_RESET_HE_FLOW_CENTER->Check__DATA(STR__YES) > 0)
			{
				sCH__ZERO_CAL_RESET_HE_FLOW_CENTER->Set__DATA("");

				sCH__ZERO_CAL_He_Flow_CENTER->Set__DATA("0");
			}
		}
		// ZERO-CAL - HE_FLOW.EDGE ...
		if(bActive__EDGE_USE)
		{
			if(sCH__ZERO_CAL_REQ_HE_FLOW_EDGE->Check__DATA(STR__YES) > 0)
			{
				sCH__ZERO_CAL_REQ_HE_FLOW_EDGE->Set__DATA("");

				aiEXT_CH__He_Flow_EDGE_IO->Get__DATA(var_data);
				sCH__ZERO_CAL_He_Flow_EDGE->Set__DATA(var_data);
			}
			if(sCH__ZERO_CAL_RESET_HE_FLOW_EDGE->Check__DATA(STR__YES) > 0)
			{
				sCH__ZERO_CAL_RESET_HE_FLOW_EDGE->Set__DATA("");

				sCH__ZERO_CAL_He_Flow_EDGE->Set__DATA("0");
			}
		}

		// DATA Update ...
		{
			double cal_offet = 0.0;
			double data_value = 0.0;

			// Center ...
			if(bActive__CENTER_USE)
			{
				sCH__ZERO_CAL_He_Pressure_CENTER->Get__DATA(var_data);
				cal_offet = atof(var_data);

				data_value = aiEXT_CH__He_Pressure_CENTER_IO->Get__VALUE() - cal_offet;
				if(data_value < 0)		data_value = 0;

				var_data.Format("%.1f", data_value);
				sCH__MON_He_Pressure_CENTER->Set__DATA(var_data);

				//
				sCH__ZERO_CAL_He_Flow_CENTER->Get__DATA(var_data);
				cal_offet = atof(var_data);

				data_value = aiEXT_CH__He_Flow_CENTER_IO->Get__VALUE() - cal_offet;
				if(data_value < 0)		data_value = 0;

				var_data.Format("%.1f", data_value);
				sCH__MON_He_Flow_CENTER->Set__DATA(var_data);
			}
			// Edge ...
			if(bActive__EDGE_USE)
			{
				sCH__ZERO_CAL_He_Pressure_EDGE->Get__DATA(var_data);
				cal_offet = atof(var_data);

				data_value = aiEXT_CH__He_Pressure_EDGE_IO->Get__VALUE() - cal_offet;
				if(data_value < 0)		data_value = 0;

				var_data.Format("%.1f", data_value);
				sCH__MON_He_Pressure_EDGE->Set__DATA(var_data);

				//
				sCH__ZERO_CAL_He_Flow_EDGE->Get__DATA(var_data);
				cal_offet = atof(var_data);

				data_value = aiEXT_CH__He_Flow_EDGE_IO->Get__VALUE() - cal_offet;
				if(data_value < 0)		data_value = 0;

				var_data.Format("%.1f", data_value);
				sCH__MON_He_Flow_EDGE->Set__DATA(var_data);
			}
		}

		if(iACTIVE_FLAG > 0)
		{
			sCH__MON_ESC_OBJ_STATUS->Set__DATA("Busy");
			sCH__MON_He_OBJ_STATUS->Set__DATA("Busy");
		}
		else
		{
			sCH__MON_ESC_OBJ_STATUS->Set__DATA("Ready");
			sCH__MON_He_OBJ_STATUS->Set__DATA("Ready");
		}
	}

	// ...
}

void CObj__ESC_IO::
Mon__SYS_INFO(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	double pre_range__cfg_esc_volt_max = 0.0;
	double pre_range__cfg_dechuck_volt_max__center = 0.0;

	double pre_range__cfg_he_pressure_max  = 0.0;
	double pre_range__cfg_he_flow_max      = 0.0;

	CString pre__chuck_sel = "";
	CString pre__cfg_save  = "";

	CString var_data;
	int i;

	// ...
	{
		doEXT_CH__He_Exhaust_Vlv->Set__DATA(STR__Open);
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(iActive__SIM_MODE > 0)
		{
			// ESC Center ...
			if(bActive__CENTER_USE)
			{
				aoEXT_CH__ESC_Voltage_CENTER->Get__DATA(var_data);
				aiEXT_CH__ESC_Voltage_CENTER->Set__DATA(var_data);
			}
			// ESC Edge ...
			if(bActive__EDGE_USE)
			{
				aoEXT_CH__ESC_Voltage_EDGE->Get__DATA(var_data);
				aiEXT_CH__ESC_Voltage_EDGE->Set__DATA(var_data);
			}

			doEXT_CH__ESC_All_Voltage->Set__DATA(STR__On);

			// DPC Center ...
			if(bActive__CENTER_USE)
			{
				double cur_set_center = aoEXT_CH__He_Pressure_CENTER->Get__VALUE();				
				aiEXT_CH__He_Pressure_CENTER_IO->Set__VALUE(cur_set_center);

				if(cur_set_center < 0.01)		aiEXT_CH__He_Flow_CENTER_IO->Set__VALUE(0.0);
			}
			// DPC Edge ...
			if(bActive__EDGE_USE)
			{
				double cur_set_edge = aoEXT_CH__He_Pressure_EDGE->Get__VALUE();				
				aiEXT_CH__He_Pressure_EDGE_IO->Set__VALUE(cur_set_edge);

				if(cur_set_edge < 0.01)			aiEXT_CH__He_Flow_EDGE_IO->Set__VALUE(0.0);
			}
		}

		// Config Update ...
		if(dEXT_CH__CONFIG_SAVE->Check__DATA(pre__cfg_save) < 0)
		{
			dEXT_CH__CONFIG_SAVE->Get__DATA(pre__cfg_save);

			if(pre__cfg_save.CompareNoCase("Unchange") == 0)
			{
				var_data = sCH__CUR_CHUCK_SEL->Get__STRING();
				if(var_data.GetLength() > 0)
				{
					sCH__CFG_CHUCK_SEL->Set__DATA(var_data);
				}

				// Center ...
				if(bActive__CENTER_USE)
				{
					aCH__CFG_ESC_CENTER_CURRENT_LIMIT->Get__DATA(var_data);
					eaoEXT_CH__ESC_IO__CUR_LIMIT_SETPOINT_CENTER->Set__DATA(var_data);
				}
				// Edge ...
				if(bActive__EDGE_USE)
				{
					aCH__CFG_ESC_EDGE_CURRENT_LIMIT->Get__DATA(var_data);
					eaoEXT_CH__ESC_IO__CUR_LIMIT_SETPOINT_EDGE->Set__DATA(var_data);
				}

				Sleep(500);
			}
		}

		if(sCH__CFG_CHUCK_SEL->Check__DATA("") < 0)
		{
			sCH__CFG_CHUCK_SEL->Get__DATA(pre__chuck_sel);
			sCH__CFG_CHUCK_SEL->Set__DATA("");
			sCH__CUR_CHUCK_SEL->Set__DATA(pre__chuck_sel);

			// ...
			double cfg_sec = 0.0;
			int chuck_mode = -1;

				 if(pre__chuck_sel.CompareNoCase("CHUCK")  == 0)		chuck_mode = 0;
			else if(pre__chuck_sel.CompareNoCase("CHUCK1") == 0)		chuck_mode = 1;
			else if(pre__chuck_sel.CompareNoCase("CHUCK2") == 0)		chuck_mode = 2;

			if(chuck_mode >= 0)
			{
				for(i=0; i<DEF__CHUCK_CHART_SIZE; i++)
				{
						 if(i == 0)		aCH__CFG_HV_OFF_TIME_CHUCK_X[chuck_mode]->Get__DATA(var_data);
					else if(i == 1)		aCH__CFG_HV_ON_TIME_CHUCK_X[chuck_mode]->Get__DATA(var_data);
					else if(i == 2)		aCH__CFG_HV_STABLE_TIME_CHUCK_X[chuck_mode]->Get__DATA(var_data);
					else if(i == 3)		aCH__CFG_HV_HOLDING_TIME_CHUCK_X[chuck_mode]->Get__DATA(var_data);
					else if(i == 4)		aCH__CFG_RF_ON_TIME_CHUCK_X[chuck_mode]->Get__DATA(var_data);
					else if(i == 5)		aCH__CFG_FINAL_FLOW_STABLE_TIME_CHUCK_X[chuck_mode]->Get__DATA(var_data);
					else                continue;

					sCH__CFG_CHUCK_CHART_TIME[i]->Set__DATA(var_data);
				}
			}
			else
			{
				for(i=0; i<DEF__CHUCK_CHART_SIZE; i++)
				{
					sCH__CFG_CHUCK_CHART_TIME[i]->Set__DATA("?");
				}
			}

			for(i=1; i<DEF__CHUCK_CHART_SIZE; i++)
			{
				var_data = sCH__CFG_CHUCK_CHART_TIME[i]->Get__STRING();
				cfg_sec += atof(var_data);
			}

			var_data.Format("%.1f", cfg_sec);
			sCH__CFG_CHUCK_CHART_TIME_TOTAL->Set__DATA(var_data);

			sCH__CFG_CHUCK_CHART_TIME_CHUCK->Set__DATA("__");
			sCH__CFG_CHUCK_CHART_TIME_CHUCK1->Set__DATA("__");
			sCH__CFG_CHUCK_CHART_TIME_CHUCK2->Set__DATA("__");

				 if(pre__chuck_sel.CompareNoCase("CHUCK")  == 0)		sCH__CFG_CHUCK_CHART_TIME_CHUCK->Set__DATA(var_data);
			else if(pre__chuck_sel.CompareNoCase("CHUCK1") == 0)		sCH__CFG_CHUCK_CHART_TIME_CHUCK1->Set__DATA(var_data);
			else if(pre__chuck_sel.CompareNoCase("CHUCK2") == 0)		sCH__CFG_CHUCK_CHART_TIME_CHUCK2->Set__DATA(var_data);
		}

		// He Flow.Center ...
		if(bActive__CENTER_USE)
		{
			int he_flow_check = doEXT_CH__He_Final_Out_Vlv_CENTER->Check__DATA(STR__Open);

			if(he_flow_check < 0)
			{
				sCH__MON_He_LEAK_SCCM_CENTER->Set__DATA("");
			}
			else 
			{
				if((iACTIVE__WAFER_LEAK_CHECK > 0)
				|| (dCH__MON_CHUCK_STATUS->Check__DATA(STR__CHUCKED) > 0))
				{
					sCH__RESULT_HE_CENTER_FLOW_READING_POINT1->Get__DATA(var_data);
					double cfg_center__bypass_flow = atof(var_data);

					sCH__MON_He_Flow_CENTER->Get__DATA(var_data);
					double cur_center__flow = atof(var_data);	

					var_data.Format("%.1f", (cur_center__flow - cfg_center__bypass_flow));
					sCH__MON_He_LEAK_SCCM_CENTER->Set__DATA(var_data);
				}
				else
				{
					sCH__MON_He_LEAK_SCCM_CENTER->Set__DATA("__");
				}
			}
		}
		// He Flow.Edge ...
		if(bActive__EDGE_USE)
		{
			int he_flow_check = doEXT_CH__He_Final_Out_Vlv_EDGE->Check__DATA(STR__Open);

			if(he_flow_check < 0)
			{
				sCH__MON_He_LEAK_SCCM_EDGE->Set__DATA("");
			}
			else 
			{
				if((iACTIVE__WAFER_LEAK_CHECK > 0)
				|| (dCH__MON_CHUCK_STATUS->Check__DATA(STR__CHUCKED) > 0))
				{
					sCH__RESULT_HE_EDGE_FLOW_READING_POINT1->Get__DATA(var_data);
					double cfg_edge__bypass_flow = atof(var_data);

					sCH__MON_He_Flow_EDGE->Get__DATA(var_data);
					double cur_edge__flow = atof(var_data);	

					var_data.Format("%.1f", (cur_edge__flow - cfg_edge__bypass_flow));
					sCH__MON_He_LEAK_SCCM_EDGE->Set__DATA(var_data);
				}
				else
				{
					sCH__MON_He_LEAK_SCCM_EDGE->Set__DATA("__");
				}
			}
		}

		// Range Change ...
		{
			double cfg_range_max;
			double cfg_range_min;

			// ESC Parameter ...
			{
				cfg_range_max = aCH__CFG_ESC_VOLTAGE_FULL_SCALE->Get__VALUE();

				if(pre_range__cfg_esc_volt_max != cfg_range_max)
				{
					pre_range__cfg_esc_volt_max = cfg_range_max;

					double cfg_max = cfg_range_max;
					double cfg_min = 0.0;
					int    cfg_dec = 1;

					if(dCH__CFG_ELECTROSTATIC_CHUCK_TYPE->Check__DATA("BIPOLAR") > 0)
					{
						cfg_min = -cfg_max;	
					}

					// Center ...
					if(bActive__CENTER_USE)
					{
						aCH__CFG_ESC_CENTER_VOLTAGE_MAX_SETPOINT_FOR_CHUCKING->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);
						aCH__CFG_ESC_CENTER_VOLTAGE_MIN_SETPOINT_FOR_CHUCKING->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);
						aCH__CFG_ESC_CENTER_VOLTAGE_THRESHOLD->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);

						aCH__CFG_ESC_CENTER_VOLTAGE_MAX_SETPOINT_FOR_DECHUCKING->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);
						
						aoEXT_CH__ESC_Voltage_CENTER->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);
						aiEXT_CH__ESC_Voltage_CENTER->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);
					}
					// Edge ...
					if(bActive__EDGE_USE)
					{
						aCH__CFG_ESC_EDGE_VOLTAGE_MAX_SETPOINT_FOR_CHUCKING->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);
						aCH__CFG_ESC_EDGE_VOLTAGE_MIN_SETPOINT_FOR_CHUCKING->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);
						aCH__CFG_ESC_EDGE_VOLTAGE_THRESHOLD->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);

						aCH__CFG_ESC_EDGE_VOLTAGE_MAX_SETPOINT_FOR_DECHUCKING->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);

						aoEXT_CH__ESC_Voltage_EDGE->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);
						aiEXT_CH__ESC_Voltage_EDGE->Change__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);
					}
				}
			}

			// Chucking Range ...
			{
				// Center ...
				{
					cfg_range_max = aCH__CFG_ESC_CENTER_VOLTAGE_MAX_SETPOINT_FOR_CHUCKING->Get__VALUE();
					cfg_range_min = aCH__CFG_ESC_CENTER_VOLTAGE_MIN_SETPOINT_FOR_CHUCKING->Get__VALUE();

					aCH__CFG_ESC_CENTER_CHUCKING_VOLTAGE_SETPOINT->Change__MIN_MAX_DEC(cfg_range_min,cfg_range_max,0);
				}
			}

			// Dechucking Range ...
			{
				// Center ...
				{
					cfg_range_max = aCH__CFG_ESC_CENTER_VOLTAGE_MAX_SETPOINT_FOR_DECHUCKING->Get__VALUE();

					if(pre_range__cfg_dechuck_volt_max__center != cfg_range_max)
					{
						pre_range__cfg_dechuck_volt_max__center = cfg_range_max;

						// ...
						int i_limit = DEF__DECHUCK_MODE_SIZE;
						int i;

						for(i=0; i<i_limit; i++)
						{
							int k_limit = DEF_DECHUCK__STEP_SIZE;
							int k;

							for(k=0; k<k_limit; k++)
							{
								aCH__CFG_CENTER_DECHUCK_X__STEPx_VOLT[i][k]->Change__MIN_MAX_DEC(-cfg_range_max,cfg_range_max,1);
							}
						}

						aCH__CFG_CENTER_DECHUCK_X__LAST_VOLT[i]->Change__MIN_MAX_DEC(-cfg_range_max,cfg_range_max,1);
					}
				}
			}

			// Helium Parameter ...
			{
				// Pressure Range ...
				{
					cfg_range_max = aCH__CFG_He_PRESSURE_FULL_SCALE->Get__VALUE();

					if(pre_range__cfg_he_pressure_max != cfg_range_max);
					{
						pre_range__cfg_he_pressure_max = cfg_range_max;

						aCH__CFG_He_PRESSURE_MAX_SETPOINT->Change__MIN_MAX_DEC(0,cfg_range_max,0);

						if(bActive__CENTER_USE)
						{
							aoEXT_CH__He_Pressure_CENTER->Change__MIN_MAX_DEC(0,cfg_range_max,1);
							aiEXT_CH__He_Pressure_CENTER_IO->Change__MIN_MAX_DEC(0,cfg_range_max,1);
						}
						if(bActive__EDGE_USE)
						{
							aoEXT_CH__He_Pressure_EDGE->Change__MIN_MAX_DEC(0,cfg_range_max,1);
							aiEXT_CH__He_Pressure_EDGE_IO->Change__MIN_MAX_DEC(0,cfg_range_max,1);
						}
					}

					//
					cfg_range_max = aCH__CFG_He_PRESSURE_MAX_SETPOINT->Get__VALUE();

					if(bActive__CENTER_USE)
					{
						aCH__CFG_HE_CENTER_PRESSURE_SETPOINT->Change__MIN_MAX_DEC(0,cfg_range_max,1);
						aCH__CFG_HE_CENTER_PRESSURE_DURING_DECHUCK_VERIFY->Change__MIN_MAX_DEC(0,cfg_range_max,1);
						aCH__CFG_HE_CENTER_PRESSURE_FOR_HW_CHECK->Change__MIN_MAX_DEC(0,cfg_range_max,1);
					}
					if(bActive__EDGE_USE)
					{
						aCH__CFG_HE_EDGE_PRESSURE_SETPOINT->Change__MIN_MAX_DEC(0,cfg_range_max,1);
						aCH__CFG_HE_EDGE_PRESSURE_DURING_DECHUCK_VERIFY->Change__MIN_MAX_DEC(0,cfg_range_max,1);
						aCH__CFG_HE_EDGE_PRESSURE_FOR_HW_CHECK->Change__MIN_MAX_DEC(0,cfg_range_max,1);
					}
				}

				// Flow Range ...
				{
					cfg_range_max = aCH__CFG_He_FLOW_FULL_SCALE->Get__VALUE();

					if(pre_range__cfg_he_flow_max != cfg_range_max)
					{
						pre_range__cfg_he_flow_max = cfg_range_max;

						if(bActive__CENTER_USE)
						{
							aiEXT_CH__He_Flow_CENTER_IO->Change__MIN_MAX_DEC(0,cfg_range_max,1);
							aCH__CFG_HE_CENTER_BYPASS_FLOW_FOR_HW_CHECK->Change__MIN_MAX_DEC(0,cfg_range_max,1);
						}
						if(bActive__EDGE_USE)
						{
							aiEXT_CH__He_Flow_EDGE_IO->Change__MIN_MAX_DEC(0,cfg_range_max,1);
							aCH__CFG_HE_EDGE_BYPASS_FLOW_FOR_HW_CHECK->Change__MIN_MAX_DEC(0,cfg_range_max,1);
						}
					}
				}

				// ...
			}
		}

		// ...
	}
}

void CObj__ESC_IO::
Mon__ESC_STABLE_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	SCX__ASYNC_TIMER_CTRL x_timer__esc_change_delay__center;
	SCX__ASYNC_TIMER_CTRL x_timer__esc_check_delay__center;
	SCX__ASYNC_TIMER_CTRL x_timer__esc_stable_delay__center;

	SCX__ASYNC_TIMER_CTRL x_timer__esc_change_delay__edge;
	SCX__ASYNC_TIMER_CTRL x_timer__esc_check_delay__edge;
	SCX__ASYNC_TIMER_CTRL x_timer__esc_stable_delay__edge;

	double pre__esc_setpoint__center = -1.0;
	double pre__esc_setpoint__edge   = -1.0;

	CString var_data;

	// Center ...
	{
		x_timer__esc_change_delay__center->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_CENTER_CHANGE_ESC_TIME->Get__CHANNEL_NAME());
		x_timer__esc_change_delay__center->STOP_ZERO();

		x_timer__esc_check_delay__center->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_CENTER_FAULT_ESC_TIME->Get__CHANNEL_NAME());
		x_timer__esc_check_delay__center->STOP_ZERO();

		x_timer__esc_stable_delay__center->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_CENTER_STABLE_ESC_TIME->Get__CHANNEL_NAME());
		x_timer__esc_stable_delay__center->STOP_ZERO();
	}
	// Edge ...
	{
		x_timer__esc_change_delay__edge->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_EDGE_CHANGE_ESC_TIME->Get__CHANNEL_NAME());
		x_timer__esc_change_delay__edge->STOP_ZERO();

		x_timer__esc_check_delay__edge->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_EDGE_FAULT_ESC_TIME->Get__CHANNEL_NAME());
		x_timer__esc_check_delay__edge->STOP_ZERO();

		x_timer__esc_stable_delay__edge->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_EDGE_STABLE_ESC_TIME->Get__CHANNEL_NAME());
		x_timer__esc_stable_delay__edge->STOP_ZERO();
	}

	// ...
	int loop_count = 0;

	if(sCH__MON_ESC_ON_TIME_START_DATE->Check__DATA("") > 0)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		var_data.Format("%00004d.%002d.%002d", st.wYear,st.wMonth,st.wDay);
		sCH__MON_ESC_ON_TIME_START_DATE->Set__DATA(var_data);
	}

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		loop_count++;
		if(loop_count > 10)		loop_count = 1;

		if(loop_count == 1)
		{
			if((dCH__MON_CENTER_ESC_VOLTAGE_STATE->Check__DATA(STR__ON) > 0)
			|| (dCH__MON_EDGE_ESC_VOLTAGE_STATE->Check__DATA(STR__ON)   > 0))
			{
				aCH__MON_ESC_ON_TIME_TOTAL_SEC->Inc__VALUE(1);
				double cur__on_sec = aCH__MON_ESC_ON_TIME_TOTAL_SEC->Get__VALUE();

				if(cur__on_sec >= 3600)
				{
					aCH__MON_ESC_ON_TIME_TOTAL_SEC->Set__VALUE(0);
					aCH__MON_ESC_ON_TIME_TOTAL_HOUR->Inc__VALUE(1);
				}
			}
		}
		else
		{
			if(dCH__MON_ESC_ON_TIME_RESET->Check__DATA(STR__RESET) > 0)
			{
				dCH__MON_ESC_ON_TIME_RESET->Set__DATA(STR__RETURN);

				// ...
				{
					SYSTEMTIME st;
					GetLocalTime(&st);

					var_data.Format("%00004d.%002d.%002d", st.wYear,st.wMonth,st.wDay);
					sCH__MON_ESC_ON_TIME_START_DATE->Set__DATA(var_data);

					aCH__MON_ESC_ON_TIME_TOTAL_HOUR->Set__VALUE(0);
					aCH__MON_ESC_ON_TIME_TOTAL_SEC->Set__VALUE(0);
				}
			}
		}

		// ...
		CII__VAR_STRING_CTRL *pch_esc_ctrl_check;
		CII__VAR_STRING_CTRL *pch_change_esc_state;
		CII__VAR_STRING_CTRL *pch_fault_esc_state;
		CII__VAR_STRING_CTRL *pch_stable_esc_state;

		SCI__ASYNC_TIMER_CTRL *p_timer__esc_change_delay;
		SCI__ASYNC_TIMER_CTRL *p_timer__esc_check_delay;
		SCI__ASYNC_TIMER_CTRL *p_timer__esc_stable_delay;

		double cur__esc_setpoint;
		double *p_pre__esc_setpoint;

		bool active__esc_voltage = false;

		int i_limit = DEF__ESC_SIZE;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == 0)			// ESC Center ...
			{
				if(bActive__CENTER_USE)
				{
					cur__esc_setpoint = aoEXT_CH__ESC_Voltage_CENTER->Get__VALUE();
					p_pre__esc_setpoint = &pre__esc_setpoint__center;

					pch_esc_ctrl_check = sCH__MON_ESC_CENTER_CTRL_CHECK.Get__PTR();
					pch_change_esc_state = sCH__MON_CENTER_CHANGE_ESC_STATE.Get__PTR();
					pch_fault_esc_state  = sCH__MON_CENTER_FAULT_ESC_STATE.Get__PTR();
					pch_stable_esc_state = sCH__MON_CENTER_STABLE_ESC_STATE.Get__PTR();

					p_timer__esc_change_delay = x_timer__esc_change_delay__center.Get__PTR();
					p_timer__esc_check_delay  = x_timer__esc_check_delay__center.Get__PTR();
					p_timer__esc_stable_delay = x_timer__esc_stable_delay__center.Get__PTR();

					//
					if((cur__esc_setpoint > 0.1) || (cur__esc_setpoint < -0.1))
					{
						active__esc_voltage = true;
						dCH__MON_CENTER_ESC_VOLTAGE_STATE->Set__DATA(STR__ON);
					}
					else
					{
						dCH__MON_CENTER_ESC_VOLTAGE_STATE->Set__DATA(STR__OFF);
					}
				}
				else
				{
					continue;
				}
			}
			else if(i == 1)		// ESC Edge ...
			{
				if(bActive__EDGE_USE)
				{
					cur__esc_setpoint = aoEXT_CH__ESC_Voltage_EDGE->Get__VALUE();
					p_pre__esc_setpoint = &pre__esc_setpoint__edge;

					pch_esc_ctrl_check = sCH__MON_ESC_EDGE_CTRL_CHECK.Get__PTR();
					pch_change_esc_state = sCH__MON_EDGE_CHANGE_ESC_STATE.Get__PTR();
					pch_fault_esc_state  = sCH__MON_EDGE_FAULT_ESC_STATE.Get__PTR();
					pch_stable_esc_state = sCH__MON_EDGE_STABLE_ESC_STATE.Get__PTR();

					p_timer__esc_change_delay = x_timer__esc_change_delay__edge.Get__PTR();
					p_timer__esc_check_delay  = x_timer__esc_check_delay__edge.Get__PTR();
					p_timer__esc_stable_delay = x_timer__esc_stable_delay__edge.Get__PTR();

					//
					if((cur__esc_setpoint > 0.1) || (cur__esc_setpoint < -0.1))
					{
						active__esc_voltage = true;
						dCH__MON_EDGE_ESC_VOLTAGE_STATE->Set__DATA(STR__ON);
					}
					else
					{
						dCH__MON_EDGE_ESC_VOLTAGE_STATE->Set__DATA(STR__OFF);
					}
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}

			//
			if((cur__esc_setpoint > 0.1) || (cur__esc_setpoint < -0.1))
			{
				pch_esc_ctrl_check->Set__DATA(STR__YES);
			}
			else
			{
				pch_esc_ctrl_check->Set__DATA(STR__NO);
			}

			if(*p_pre__esc_setpoint != cur__esc_setpoint)
			{
				*p_pre__esc_setpoint = cur__esc_setpoint;

				// ...
				{
					pch_change_esc_state->Set__DATA("");
					p_timer__esc_change_delay->STOP_ZERO();

					p_timer__esc_check_delay->STOP_ZERO();
					pch_fault_esc_state->Set__DATA(STR__NO);

					p_timer__esc_stable_delay->STOP_ZERO();
					pch_stable_esc_state->Set__DATA(STR__NO);
				}
			}

			if(pch_change_esc_state->Check__DATA(STR__YES) < 0)
			{
				double cur__sec = p_timer__esc_change_delay->Get__CURRENT_TIME();
				double cfg__change_stable = aCH__CFG_STABLE_TIME_FOR_ESC_HELIUM_SETPOINT_CHANGE->Get__VALUE();

				if(cur__sec < 0.001)
				{
					p_timer__esc_change_delay->START__COUNT_UP(9999);
				}
				else if(cur__sec >= cfg__change_stable)
				{
					pch_change_esc_state->Set__DATA(STR__YES);
					p_timer__esc_change_delay->STOP_ZERO();
				}
			}

			if(pch_change_esc_state->Check__DATA(STR__YES) < 0)
			{
				continue;
			}

			// ...
			{
				double cfg__stable_delay = aCH__CFG_CHECKING_TIME_FOR_ESC_HELIUM_STABLE->Get__VALUE();
				double cfg__check_delay  = aCH__CFG_ERROR_TIMEOUT_FOR_ESC_HELIUM_STATE->Get__VALUE();

				var_data.Format("cfg__check_delay (%.1f), cfg__stable_delay (%.1f)", cfg__check_delay,cfg__stable_delay);
				sCH__MON_MSG_STABLE_CHECK->Set__DATA(var_data);

				if(dCH__MON_CHUCK_STATUS->Check__DATA(STR__CHUCKED) > 0)
				{
					// ESC Voltage Error Check ...
					{
						if(Fnc__HV_ERROR_CHECK(p_alarm, CHECK_POINT__IO, -1) < 0)
						{
							double cur_sec = p_timer__esc_check_delay->Get__CURRENT_TIME();

							if(cur_sec < 0.001)
							{
								p_timer__esc_check_delay->START__COUNT_UP(9999);
							}
							else if(cur_sec >= cfg__check_delay)
							{
								if(Fnc__HV_ERROR_CHECK(p_alarm, CHECK_POINT__IO) < 0)
								{
									pch_fault_esc_state->Set__DATA(STR__YES);
								}
							}

							// ...
							{
								p_timer__esc_stable_delay->STOP_ZERO();
								pch_stable_esc_state->Set__DATA(STR__NO);
							}
						}
						else
						{
							double cur_sec = p_timer__esc_stable_delay->Get__CURRENT_TIME();

							if(cur_sec < 0.001)
							{
								p_timer__esc_stable_delay->START__COUNT_UP(9999);
							}
							else if(cur_sec >= cfg__stable_delay)
							{
								pch_stable_esc_state->Set__DATA(STR__YES);
							}

							// ...
							{
								p_timer__esc_check_delay->STOP_ZERO();
								pch_fault_esc_state->Set__DATA(STR__NO);
							}
						}
					}
				}
				else if(dCH__MON_CHUCK_STATUS->Check__DATA(STR__DECHUCKED) > 0)
				{
					p_timer__esc_check_delay->STOP_ZERO();
					pch_fault_esc_state->Set__DATA(STR__NO);

					p_timer__esc_stable_delay->STOP_ZERO();
					pch_stable_esc_state->Set__DATA(STR__YES);
				}
				else
				{
					p_timer__esc_check_delay->STOP_ZERO();
					pch_fault_esc_state->Set__DATA(STR__NO);

					p_timer__esc_stable_delay->STOP_ZERO();
					pch_stable_esc_state->Set__DATA(STR__NO);
				}
			}

			// ...
		}

		if(active__esc_voltage)			dCH__MON_ESC_VOLTAGE_ACTIVE->Set__DATA(STR__ON);
		else							dCH__MON_ESC_VOLTAGE_ACTIVE->Set__DATA(STR__OFF);

		//  STABLE.CHECK ...
		{
			bool active__stable_check = true;

			if(bActive__CENTER_USE)
			{
				if((sCH__MON_CENTER_STABLE_ESC_STATE->Check__DATA(STR__YES) < 0)
				|| (sCH__MON_STABLE_HE_CENTER_STATE->Check__DATA(STR__YES)  < 0))
				{
					active__stable_check = false;
				}
			}
			if(bActive__EDGE_USE)
			{
				if((sCH__MON_EDGE_STABLE_ESC_STATE->Check__DATA(STR__YES) < 0)
				|| (sCH__MON_STABLE_HE_EDGE_STATE->Check__DATA(STR__YES)  < 0))
				{
					active__stable_check = false;
				}
			}

			if(active__stable_check)
			{
				dCH__MON_STABLE_ACTIVE->Set__DATA(STR__ON);
			}
			else
			{
				dCH__MON_STABLE_ACTIVE->Set__DATA(STR__OFF);
			}
		}
		// FAULT.CHECK ...
		{
			bool active__fault_check = false;

			if(bActive__CENTER_USE)
			{
				if((sCH__MON_CENTER_FAULT_ESC_STATE->Check__DATA(STR__YES) > 0)
				|| (sCH__MON_FAULT_HE_CENTER_STATE->Check__DATA(STR__YES)  > 0))
				{
					active__fault_check = true;
				}
			}
			if(bActive__EDGE_USE)
			{
				if((sCH__MON_EDGE_FAULT_ESC_STATE->Check__DATA(STR__YES) > 0)
				|| (sCH__MON_FAULT_HE_EDGE_STATE->Check__DATA(STR__YES)  > 0))
				{
					active__fault_check = true;
				}
			}
			
			if(active__fault_check)
			{
				dCH__MON_FAULT_ACTIVE->Set__DATA(STR__ON);
			}
			else
			{
				dCH__MON_FAULT_ACTIVE->Set__DATA(STR__OFF);
			}
		}

		// ...
	}
}

void CObj__ESC_IO::
Mon__HELIUM_STABLE_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	SCX__ASYNC_TIMER_CTRL x_timer__he_center_change_delay;
	SCX__ASYNC_TIMER_CTRL x_timer__he_center_check_delay;
	SCX__ASYNC_TIMER_CTRL x_timer__he_center_stable_delay;

	SCX__ASYNC_TIMER_CTRL x_timer__he_edge_change_delay;
	SCX__ASYNC_TIMER_CTRL x_timer__he_edge_check_delay;
	SCX__ASYNC_TIMER_CTRL x_timer__he_edge_stable_delay;

	double pre__center_set = -1.0;
	double pre__edge_set = -1.0;

	CString var_data;

	// Center ...
	{
		x_timer__he_center_change_delay->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_CHANGE_HE_CENTER_TIME->Get__CHANNEL_NAME());
		x_timer__he_center_change_delay->STOP_ZERO();

		x_timer__he_center_check_delay->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_FAULT_HE_CENTER_TIME->Get__CHANNEL_NAME());
		x_timer__he_center_check_delay->STOP_ZERO();

		x_timer__he_center_stable_delay->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_STABLE_HE_CENTER_TIME->Get__CHANNEL_NAME());
		x_timer__he_center_stable_delay->STOP_ZERO();
	}
	// Edge ...
	{
		x_timer__he_edge_change_delay->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_CHANGE_HE_EDGE_TIME->Get__CHANNEL_NAME());
		x_timer__he_edge_change_delay->STOP_ZERO();

		x_timer__he_edge_check_delay->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_FAULT_HE_EDGE_TIME->Get__CHANNEL_NAME());
		x_timer__he_edge_check_delay->STOP_ZERO();

		x_timer__he_edge_stable_delay->REGISTER__COUNT_CHANNEL_NAME(sCH__MON_STABLE_HE_EDGE_TIME->Get__CHANNEL_NAME());
		x_timer__he_edge_stable_delay->STOP_ZERO();
	}

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		// ...
		double cfg__stable_delay = aCH__CFG_CHECKING_TIME_FOR_ESC_HELIUM_STABLE->Get__VALUE();
		double cfg__check_delay  = aCH__CFG_ERROR_TIMEOUT_FOR_ESC_HELIUM_STATE->Get__VALUE();

		// He Error Check ...
		{
			int he_type = -1;

			SCI__ASYNC_TIMER_CTRL *p_timer__change_delay;
			SCI__ASYNC_TIMER_CTRL *p_timer__stable_delay;
			SCI__ASYNC_TIMER_CTRL *p_timer__check_delay;

			CII__VAR_STRING_CTRL *p_ch_ctrl_check;
			CII__VAR_STRING_CTRL *p_ch__change;
			CII__VAR_STRING_CTRL *p_ch__stable;
			CII__VAR_STRING_CTRL *p_ch__fault;

			double cur__he_set;
			double *p_pre__he_set;

			int i_limit = 2;
			int i;

			for(i=0; i<i_limit; i++)
			{
				if(i == 0)
				{
					if(bActive__CENTER_USE)
					{
						he_type = HE_TYPE__CENTER;

						cur__he_set = aoEXT_CH__He_Pressure_CENTER->Get__VALUE();
						p_pre__he_set = &pre__center_set;

						p_timer__change_delay = x_timer__he_center_change_delay.Get__PTR();
						p_timer__stable_delay = x_timer__he_center_stable_delay.Get__PTR();
						p_timer__check_delay  = x_timer__he_center_check_delay.Get__PTR();

						p_ch_ctrl_check = sCH__MON_HE_CENTER_CTRL_CHECK.Get__PTR();
						p_ch__change = sCH__MON_CHANGE_HE_CENTER_STATE.Get__PTR();
						p_ch__stable = sCH__MON_STABLE_HE_CENTER_STATE.Get__PTR();
						p_ch__fault  = sCH__MON_FAULT_HE_CENTER_STATE.Get__PTR();
					}
					else
					{
						continue;
					}
				}
				else if(i == 1)
				{
					if(bActive__EDGE_USE)
					{
						he_type = HE_TYPE__EDGE;

						cur__he_set = aoEXT_CH__He_Pressure_EDGE->Get__VALUE();
						p_pre__he_set = &pre__edge_set;

						p_timer__change_delay = x_timer__he_edge_change_delay.Get__PTR();
						p_timer__stable_delay = x_timer__he_edge_stable_delay.Get__PTR();
						p_timer__check_delay  = x_timer__he_edge_check_delay.Get__PTR();

						p_ch_ctrl_check = sCH__MON_HE_EDGE_CTRL_CHECK.Get__PTR();
						p_ch__change = sCH__MON_CHANGE_HE_EDGE_STATE.Get__PTR();
						p_ch__stable = sCH__MON_STABLE_HE_EDGE_STATE.Get__PTR();
						p_ch__fault  = sCH__MON_FAULT_HE_EDGE_STATE.Get__PTR();
					}
					else
					{
						continue;
					}
				}
				else
				{
					continue;
				}

				// ...
				{
					if(cur__he_set > 0.1)		p_ch_ctrl_check->Set__DATA(STR__YES);
					else						p_ch_ctrl_check->Set__DATA(STR__NO);
				}

				if(*p_pre__he_set != cur__he_set)
				{
					*p_pre__he_set = cur__he_set;

					// ...
					{
						p_timer__change_delay->STOP_ZERO();
						p_ch__change->Set__DATA("");

						p_timer__check_delay->STOP_ZERO();
						p_ch__fault->Set__DATA("");

						p_timer__stable_delay->STOP_ZERO();
						p_ch__stable->Set__DATA("");
					}
				}

				if(p_ch__change->Check__DATA(STR__YES) < 0)
				{
					double cur__sec = p_timer__change_delay->Get__CURRENT_TIME();
					double cfg__change_stable = aCH__CFG_STABLE_TIME_FOR_ESC_HELIUM_SETPOINT_CHANGE->Get__VALUE();

					if(cur__sec < 0.001)
					{
						p_timer__change_delay->START__COUNT_UP(9999);
					}
					else if(cur__sec >= cfg__change_stable)
					{
						p_ch__change->Set__DATA(STR__YES);
						p_timer__change_delay->STOP_ZERO();
					}
				}

				if(p_ch__change->Check__DATA(STR__YES) < 0)
				{
					continue;
				}

				if(dCH__MON_CHUCK_STATUS->Check__DATA(STR__DECHUCKED) > 0)
				{
					p_timer__check_delay->STOP_ZERO();
					p_ch__fault->Set__DATA("");

					p_timer__stable_delay->STOP_ZERO();
					p_ch__stable->Set__DATA(STR__YES);

					continue;
				}
				if(dCH__MON_CHUCK_STATUS->Check__DATA(STR__CHUCKED) < 0)
				{
					p_timer__check_delay->STOP_ZERO();
					p_ch__fault->Set__DATA("");

					p_timer__stable_delay->STOP_ZERO();
					p_ch__stable->Set__DATA("");

					continue;
				}

				if(Fnc__HE_ERROR_CHECK(p_alarm, he_type,CHECK_POINT__IO, -1) < 0)
				{
					double cur_sec = p_timer__check_delay->Get__CURRENT_TIME();

					if(cur_sec < 0.001)
					{
						p_timer__check_delay->START__COUNT_UP(9999);
					}
					else if(cur_sec >= cfg__check_delay)
					{
						if(Fnc__HE_ERROR_CHECK(p_alarm, he_type,CHECK_POINT__IO) < 0)
						{
							p_ch__fault->Set__DATA(STR__YES);
						}
					}

					// ...
					{
						p_timer__stable_delay->STOP_ZERO();
						p_ch__stable->Set__DATA("");
					}
				}
				else
				{
					double cur_sec = p_timer__stable_delay->Get__CURRENT_TIME();

					if(cur_sec < 0.001)
					{
						p_timer__stable_delay->START__COUNT_UP(9999);
					}
					else if(cur_sec >= cfg__stable_delay)
					{
						p_ch__stable->Set__DATA(STR__YES);
					}

					// ...
					{
						p_timer__check_delay->STOP_ZERO();
						p_ch__fault->Set__DATA("");
					}
				}
			}

			// ...
		}
	}
}
