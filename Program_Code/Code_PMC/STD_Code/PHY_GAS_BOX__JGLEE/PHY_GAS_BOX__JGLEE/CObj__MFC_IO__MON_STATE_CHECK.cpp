#include "StdAfx.h"
#include "CObj__MFC_IO.h"

#include "CCommon_Utility.h"
#include "Macro__Function.h"


// ...
int  CObj__MFC_IO
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CCommon_Utility m_fnc;

	int loop_count = 0;
	CString ch_data;


	if(iActive__SIM_MODE > 0)
	{
		UNION_4_BYTE__FLOAT m_float;
		UNION_2_BYTE__UINT  m_uint;
		CString ch_hexa;

		// State ...
		if(bActive__MFC_STATE)
		{
			if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
			{
				ch_data.Format("%02X", 0x00);
				sEXT_CH__IO_MFC_STATE->Set__DATA(ch_data);
			}
		}
		// Voltage ...
		if(bActive__MFC_VALVE_VOLTAGE)
		{
			ch_data = "";

			if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
			{
				CString cfg__hexa_type = dCH__CFG_HEXA_TYPE_VOLTAGE->Get__STRING();

				if(cfg__hexa_type.CompareNoCase(STR__REAL) == 0)
				{
					double cfg_max = aCH__CFG_RANGE_MAX_VOLTAGE->Get__VALUE();
					m_float.fDATA = cfg_max * 0.5;

					int i_limit = 4;
					for(int i=0; i<i_limit; i++)
					{
						ch_hexa.Format("%02X ", 0x0ff & m_float.cBYTE[i]);
						ch_data += ch_hexa;
					}

					sEXT_CH__IO_MFC_VALVE_VOLTAGE->Set__DATA(ch_data);
				}
				else
				{
					int set_hexa = iLINK_DATA__MAX_DEFAULT * 0.4;
					m_uint.uiDATA = 0xffff & set_hexa;

					int i_limit = 2;
					for(int i=0; i<i_limit; i++)
					{
						ch_hexa.Format("%02X ", 0x0ff & m_uint.cBYTE[i]);
						ch_data += ch_hexa;
					}

					sEXT_CH__IO_MFC_VALVE_VOLTAGE->Set__DATA(ch_data);
				}
			}
		}
		// Temperature ...
		if(bActive__MFC_TEMPERATURE)
		{
			ch_data = "";

			if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
			{
				CString cfg__hexa_type = dCH__CFG_HEXA_TYPE_TEMPERATURE->Get__STRING();

				if(cfg__hexa_type.CompareNoCase(STR__REAL) == 0)
				{
					double cfg_max = aCH__CFG_RANGE_MAX_TEMPERATURE->Get__VALUE();
					m_float.fDATA = cfg_max * 0.5;
					
					int i_limit = 4;
					for(int i=0; i<i_limit; i++)
					{
						ch_hexa.Format("%02X ", 0x0ff & m_float.cBYTE[i]);
						ch_data += ch_hexa;
					}

					sEXT_CH__IO_MFC_TEMPERATURE->Set__DATA(ch_data);
				}
				else
				{
					int set_hexa = iLINK_DATA__MAX_DEFAULT * 0.6;
					m_uint.uiDATA = 0xffff & set_hexa;

					int i_limit = 2;
					for(int i=0; i<i_limit; i++)
					{
						ch_hexa.Format("%02X ", 0x0ff & m_uint.cBYTE[i]);
						ch_data += ch_hexa;
					}

					sEXT_CH__IO_MFC_TEMPERATURE->Set__DATA(ch_data);
				}
			}
		}
		// Pressure ...
		if(bActive__MFC_PRESSURE)
		{
			ch_data = "";

			if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
			{
				CString cfg__hexa_type = dCH__CFG_HEXA_TYPE_PRESSURE->Get__STRING();

				if(cfg__hexa_type.CompareNoCase(STR__REAL) == 0)
				{
					double cfg_max = aCH__CFG_RANGE_MAX_PRESSURE->Get__VALUE();
					m_float.fDATA = cfg_max * 0.5;

					int i_limit = 4;
					for(int i=0; i<i_limit; i++)
					{
						ch_hexa.Format("%02X ", 0x0ff & m_float.cBYTE[i]);
						ch_data += ch_hexa;
					}

					sEXT_CH__IO_MFC_PRESSURE->Set__DATA(ch_data);
				}
				else
				{
					int set_hexa = iLINK_DATA__MAX_DEFAULT * 0.5;
					m_uint.uiDATA = 0xffff & set_hexa;

					int i_limit = 2;
					for(int i=0; i<i_limit; i++)
					{
						ch_hexa.Format("%02X ", 0x0ff & m_uint.cBYTE[i]);
						ch_data += ch_hexa;
					}

					sEXT_CH__IO_MFC_PRESSURE->Set__DATA(ch_data);
				}
			}
			else
			{
				ch_data = "50.0";
				sCH__MON_MFC_INLET_PRESSURE_PERCENT->Set__DATA(ch_data);
			}
		}
	}

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.01);

		loop_count++;
		if(loop_count > 100)		loop_count = 1;

		//
		if(loop_count == 1)
		{
			int active__err_check = p_alarm->Check__Posted_Internal_Alarm(iLIST_ALID__PART);

			if(active__err_check > 0)		dCH__MON_PART_ERROR_ACTIVE->Set__DATA(STR__ON);
			else							dCH__MON_PART_ERROR_ACTIVE->Set__DATA(STR__OFF);
		}

		// Range : Flow ...
		if(loop_count == 1)
		{			
			aCH__CFG_MFC_MIN_VALUE->Get__DATA(ch_data);
			double min_value = atof(ch_data);
		
			aCH__CFG_MFC_MAX_VALUE->Get__DATA(ch_data);
			double max_value = atof(ch_data);
			
			aCH__CFG_MFC_DEC_VALUE->Get__DATA(ch_data);
			int i_dec = atoi(ch_data);

			aCH__MON_MFC_SET_FLOW->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
			aCH__MON_MFC_READ_FLOW->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
			aCH__PARA_SET_VALUE->Change__MIN_MAX_DEC(min_value,max_value,i_dec);

			if(iLINK_DATA__TYPE != _DATA_TYPE__HEXA)
			{
				aEXT_CH__IO_MFC_SET_DEC->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
				aEXT_CH__IO_MFC_READ_DEC->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
			}
		}

		// Flow ...
		if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
		{
			CString cfg__hexa_type = dCH__CFG_HEXA_TYPE_FLOW->Get__STRING();
			CString str__hexa_data = sEXT_CH__IO_MFC_READ_HEXA->Get__STRING();
		
			if(cfg__hexa_type.CompareNoCase(STR__REAL) == 0)
			{
				double cur_flow = Macro__Get_FLOAT_FROM_HEXA(str__hexa_data);
				double cfg__flow_max = aCH__CFG_MFC_MAX_VALUE->Get__VALUE();
				double flow_percent = cur_flow / cfg__flow_max;

				ch_data.Format("%.1f", flow_percent*100.0);
				sCH__MON_MFC_FLOW_PERCENT->Set__DATA(ch_data);

				aCH__MON_MFC_READ_FLOW->Set__VALUE(cur_flow);
			}
			else
			{
				unsigned short int cur_flow_hexa = Macro__Get_2_UINT_FROM_HEXA(str__hexa_data);
				
				double flow_percent = 0.0;
				double hexa_max = (double) iLINK_DATA__MAX_FLOW;

				if(cur_flow_hexa <= 0x7FFF)		flow_percent =  cur_flow_hexa / hexa_max;
				else							flow_percent = (cur_flow_hexa - 0xFFFF) / hexa_max;

				ch_data.Format("%.1f", flow_percent*100.0);
				sCH__MON_MFC_FLOW_PERCENT->Set__DATA(ch_data);

				double cfg__flow_max = aCH__CFG_MFC_MAX_VALUE->Get__VALUE();
				double cur_value = cfg__flow_max * flow_percent;

				if(cur_value < 0)		cur_value = 0;
				aCH__MON_MFC_READ_FLOW->Set__VALUE(cur_value);
			}
		}
		else
		{
			double cur__io_flow = aEXT_CH__IO_MFC_READ_DEC->Get__VALUE();

			double cfg__flow_max = aCH__CFG_MFC_MAX_VALUE->Get__VALUE();
			double cur__flow_per = 0.0;

			if(cfg__flow_max > 0.01)			cur__flow_per = cur__io_flow / cfg__flow_max;
			else								cur__flow_per = 0.0;

			ch_data.Format("%.1f", cur__flow_per*100.0);
			sCH__MON_MFC_FLOW_PERCENT->Set__DATA(ch_data);

			aCH__MON_MFC_READ_FLOW->Set__VALUE(cur__io_flow);
		}

		// Status ...
		if(bActive__MFC_STATE)
		{
			if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
			{
				ch_data = sEXT_CH__IO_MFC_STATE->Get__STRING();
				int i_sts = atoi(ch_data);

				ch_data.Format("%02X", i_sts);
				sCH__MON_MFC_EXCEPTION_STATE->Set__DATA(ch_data);

				//
				if(i_sts == 0)			ch_data = "Normal";
				else					ch_data = "Alarm";

				sCH__MON_MFC_EXCEPTION_INFO->Set__DATA(ch_data);
			}
			else
			{
				sCH__MON_MFC_EXCEPTION_STATE->Set__DATA("???");
				sCH__MON_MFC_EXCEPTION_INFO->Set__DATA("???");
			}
		}
		else
		{
			sCH__MON_MFC_EXCEPTION_STATE->Set__DATA("__");
			sCH__MON_MFC_EXCEPTION_INFO->Set__DATA("__");
		}

		// Valve.Voltage ...
		if(bActive__MFC_VALVE_VOLTAGE)
		{
			if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
			{
				CString cfg__hexa_type = dCH__CFG_HEXA_TYPE_VOLTAGE->Get__STRING();
				CString str__hexa_data = sEXT_CH__IO_MFC_VALVE_VOLTAGE->Get__STRING();

				if(cfg__hexa_type.CompareNoCase(STR__REAL) == 0)
				{
					double cur_voltage = Macro__Get_FLOAT_FROM_HEXA(str__hexa_data);
					double cfg_max = aCH__CFG_RANGE_MAX_VOLTAGE->Get__VALUE();
					double cur_percent = cur_voltage / cfg_max;

					CString str_fmt;
					int i_dec = (int) aCH__CFG_RANGE_DEC_VOLTAGE->Get__VALUE();
					str_fmt.Format("%%.%1df", i_dec);

					ch_data.Format(str_fmt, cur_voltage);
					sCH__MON_MFC_READ_VALVE_VOLTAGE->Set__DATA(ch_data);

					ch_data.Format("%.1f", cur_percent * 100.0);
					sCH__MON_MFC_VALVE_VOLTAGE_PERCENT->Set__DATA(ch_data);
				}
				else
				{
					unsigned short int cur__hexa_data = Macro__Get_2_UINT_FROM_HEXA(str__hexa_data);
					double cur_percent;

					if(cur__hexa_data <= 0x7FFF)		cur_percent =  cur__hexa_data / (double) iLINK_DATA__MAX_DEFAULT;
					else								cur_percent = (cur__hexa_data - 0xFFFF) / (double) iLINK_DATA__MAX_DEFAULT;

					CString str_fmt;
					int i_dec = (int) aCH__CFG_RANGE_DEC_VOLTAGE->Get__VALUE();
					str_fmt.Format("%%.%1df", i_dec);

					double cfg_max = aCH__CFG_RANGE_MAX_VOLTAGE->Get__VALUE();
					double cur_value = cfg_max * cur_percent;
					
					ch_data.Format(str_fmt, cur_value);
					sCH__MON_MFC_READ_VALVE_VOLTAGE->Set__DATA(ch_data);

					ch_data.Format("%.1f", cur_percent * 100.0);
					sCH__MON_MFC_VALVE_VOLTAGE_PERCENT->Set__DATA(ch_data);
				}
			}
			else
			{
				sCH__MON_MFC_READ_VALVE_VOLTAGE->Set__DATA("???");
				sCH__MON_MFC_VALVE_VOLTAGE_PERCENT->Set__DATA("???");
			}
		}
		else
		{
			sCH__MON_MFC_READ_VALVE_VOLTAGE->Set__DATA("__");
			sCH__MON_MFC_VALVE_VOLTAGE_PERCENT->Set__DATA("__");
		}

		// Pressure ...
		if(bActive__MFC_PRESSURE)
		{
			if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
			{
				CString cfg__hexa_type = dCH__CFG_HEXA_TYPE_PRESSURE->Get__STRING();
				CString str__hexa_data = sEXT_CH__IO_MFC_PRESSURE->Get__STRING();

				if(cfg__hexa_type.CompareNoCase(STR__REAL) == 0)
				{
					double cur_pressure = Macro__Get_FLOAT_FROM_HEXA(str__hexa_data);

					double cfg_max = aCH__CFG_RANGE_MAX_PRESSURE->Get__VALUE();
					double cur_percent = cur_pressure / cfg_max;
				
					CString str_fmt;
					int i_dec = (int) aCH__CFG_RANGE_DEC_PRESSURE->Get__VALUE();
					str_fmt.Format("%%.%1df", i_dec);

					ch_data.Format(str_fmt, cur_pressure);
					sCH__MON_MFC_READ_INLET_PRESSURE->Set__DATA(ch_data);			

					ch_data.Format("%.1f", cur_percent * 100.0);
					sCH__MON_MFC_INLET_PRESSURE_PERCENT->Set__DATA(ch_data);			
				}
				else
				{
					unsigned short int cur__hexa_data = Macro__Get_2_UINT_FROM_HEXA(str__hexa_data);
					double cur_percent;

					if(cur__hexa_data <= 0x7FFF)		cur_percent =  cur__hexa_data / (double) iLINK_DATA__MAX_DEFAULT;
					else								cur_percent = (cur__hexa_data - 0xFFFF) / (double) iLINK_DATA__MAX_DEFAULT;

					CString str_fmt;
					int i_dec = (int) aCH__CFG_RANGE_DEC_PRESSURE->Get__VALUE();
					str_fmt.Format("%%.%1df", i_dec);

					double cfg_max = aCH__CFG_RANGE_MAX_PRESSURE->Get__VALUE();
					double cur_value = cfg_max * cur_percent;

					ch_data.Format(str_fmt, cur_value);
					sCH__MON_MFC_READ_INLET_PRESSURE->Set__DATA(ch_data);			

					ch_data.Format("%.1f", cur_percent * 100.0);
					sCH__MON_MFC_INLET_PRESSURE_PERCENT->Set__DATA(ch_data);			
				}
			}
			else
			{
				sCH__MON_MFC_READ_INLET_PRESSURE->Set__DATA("???");
				sCH__MON_MFC_INLET_PRESSURE_PERCENT->Set__DATA("???");			
			}
		}
		else
		{
			sCH__MON_MFC_READ_INLET_PRESSURE->Set__DATA("__");
			sCH__MON_MFC_INLET_PRESSURE_PERCENT->Set__DATA("__");			
		}

		// Temperature ...
		if(bActive__MFC_TEMPERATURE)
		{
			if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
			{
				CString cfg__hexa_type = dCH__CFG_HEXA_TYPE_TEMPERATURE->Get__STRING();
				CString str__hexa_data = sEXT_CH__IO_MFC_TEMPERATURE->Get__STRING();

				if(cfg__hexa_type.CompareNoCase(STR__REAL) == 0)
				{
					double cur_temperature = Macro__Get_FLOAT_FROM_HEXA(str__hexa_data);

					double cfg_max = aCH__CFG_RANGE_MAX_TEMPERATURE->Get__VALUE();
					double cur_percent = cur_temperature / cfg_max;

					CString str_fmt;
					int i_dec = (int) aCH__CFG_RANGE_DEC_TEMPERATURE->Get__VALUE();
					str_fmt.Format("%%.%1df", i_dec);

					// ch_data.Format(str_fmt, cur_value - 273.15);		// K (Àý´ë ¿Âµµ) -> C (¼·¾¾)
					ch_data.Format(str_fmt, cur_temperature);
					sCH__MON_MFC_READ_TEMPERATURE->Set__DATA(ch_data);

					ch_data.Format("%.1f", cur_percent * 100.0);
					sCH__MON_MFC_TEMPERATURE_PERCENT->Set__DATA(ch_data);
				}
				else
				{
					unsigned short int  cur__hexa_data = Macro__Get_2_UINT_FROM_HEXA(str__hexa_data);						
					double cur_percent;

					if(cur__hexa_data <= 0x7FFF)			cur_percent =  cur__hexa_data / (double) iLINK_DATA__MAX_DEFAULT;
					else									cur_percent = (cur__hexa_data - 0xFFFF) / (double) iLINK_DATA__MAX_DEFAULT;

					CString str_fmt;
					int i_dec = (int) aCH__CFG_RANGE_DEC_TEMPERATURE->Get__VALUE();
					str_fmt.Format("%%.%1df", i_dec);

					double cfg_max = aCH__CFG_RANGE_MAX_TEMPERATURE->Get__VALUE();
					double cur_value = cfg_max * cur_percent;

					ch_data.Format(str_fmt, cur_value - 273.15);		// K (Àý´ë ¿Âµµ) -> C (¼·¾¾)
					sCH__MON_MFC_READ_TEMPERATURE->Set__DATA(ch_data);

					ch_data.Format("%.1f", cur_percent * 100.0);
					sCH__MON_MFC_TEMPERATURE_PERCENT->Set__DATA(ch_data);
				}
			}
			else
			{
				sCH__MON_MFC_READ_TEMPERATURE->Set__DATA("???");
				sCH__MON_MFC_TEMPERATURE_PERCENT->Set__DATA("???");
			}
		}
		else
		{
			sCH__MON_MFC_READ_TEMPERATURE->Set__DATA("__");
			sCH__MON_MFC_TEMPERATURE_PERCENT->Set__DATA("__");
		}

		//
		if(dCH__CFG_MFC_USE->Check__DATA(STR__YES) < 0)
		{
			aCH__MON_MFC_READ_FLOW->Set__VALUE(0);
		}
		else  // Interlock Check ...
		{
			bool active__interlock_atm_maint = false;
			bool active__interlock_system    = false;
			bool active__interlock_chamber   = false;
			bool active__interlock_gas_box   = false;
			bool active__proc_vlv_not_ready  = false;

			if(dEXT_CH__CFG_PMC_ATM_MAINT_ACTIVE->Check__DATA(STR__ON) > 0)
			{
				active__interlock_atm_maint = true;
			}

			if(dEXT_CH__CFG_DI_INTERLOCK_HEAVY_CHECK_SYSTEM->Check__DATA(STR__YES) > 0)
			{
				if(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_SYSTEM->Check__DATA(STR__ON)  > 0)		active__interlock_system = true;
			}
			if(dEXT_CH__CFG_DI_INTERLOCK_HEAVY_CHECK_CHAMBER->Check__DATA(STR__YES) > 0)
			{
				if(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_CHAMBER->Check__DATA(STR__ON) > 0)		active__interlock_chamber = true;
			}
			if(dEXT_CH__CFG_DI_INTERLOCK_HEAVY_CHECK_GAS_BOX->Check__DATA(STR__YES) > 0)
			{
				if(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_GAS_BOX->Check__DATA(STR__ON) > 0)		active__interlock_gas_box = true;
			}

			// ...
			CString cur__act_mode = sCH__ACT_MODE->Get__STRING();

			if(dEXT_CH__MON_ACTIVE_PROCESS_VALVE_READY_STATE->Check__DATA(STR__ON) < 0)
			{
				if((cur__act_mode.CompareNoCase(sMODE__CLOSE) == 0)
				|| (cur__act_mode.CompareNoCase(sMODE__OPEN)  == 0)
				|| (cur__act_mode.CompareNoCase(sMODE__PURGE) == 0)
				|| (cur__act_mode.CompareNoCase(sMODE__CHM_LINE_PURGE) == 0)
				|| (cur__act_mode.CompareNoCase(sMODE__GAS_LINE_PURGE) == 0))
				{
					active__proc_vlv_not_ready = false;
				}
				else
				{
					active__proc_vlv_not_ready = true;
				}
			}

			if((active__interlock_atm_maint)
			|| (active__interlock_system)
			|| (active__interlock_chamber)
			|| (active__interlock_gas_box)
			|| (active__proc_vlv_not_ready))
			{
				if(sCH__MON_MFC_STATE->Check__DATA(STR__CLOSE) < 0)
				{
					sCH__MON_MFC_STATE->Set__DATA(STR__CLOSE);

					// ...
					{
						int alarm_id = ALID__INTERLOCK_MFC_CLOSE;
						CString alm_msg;
						CString alm_bff;
						CString r_act;

						alm_msg = "Interlock condition \n";

						if(active__interlock_atm_maint)		
						{
							alm_bff.Format(" * %s <- %s \n", 
											dEXT_CH__CFG_PMC_ATM_MAINT_ACTIVE->Get__CHANNEL_NAME(),
											dEXT_CH__CFG_PMC_ATM_MAINT_ACTIVE->Get__STRING());
							alm_msg += alm_bff;
						}
						if(active__interlock_system)
						{
							alm_bff.Format(" * %s <- %s \n", 
											dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_SYSTEM->Get__CHANNEL_NAME(),
											dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_SYSTEM->Get__STRING());
							alm_msg += alm_bff;
						}
						if(active__interlock_chamber)
						{
							alm_bff.Format(" * %s <- %s \n", 
											dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_CHAMBER->Get__CHANNEL_NAME(),
											dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_CHAMBER->Get__STRING());
							alm_msg += alm_bff;
						}
						if(active__interlock_gas_box)
						{
							alm_bff.Format(" * %s <- %s \n", 
											dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_GAS_BOX->Get__CHANNEL_NAME(),
											dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_GAS_BOX->Get__STRING());
							alm_msg += alm_bff;
						}
						if(active__proc_vlv_not_ready)
						{
							alm_bff.Format(" * %s <- %s \n", 
											dEXT_CH__MON_ACTIVE_PROCESS_VALVE_READY_STATE->Get__CHANNEL_NAME(),
											dEXT_CH__MON_ACTIVE_PROCESS_VALVE_READY_STATE->Get__STRING());
							alm_msg += alm_bff;

							alm_bff.Format(" * %s <- %s \n", 
											sCH__ACT_MODE->Get__CHANNEL_NAME(),
											cur__act_mode);
							alm_msg += alm_bff;
						}

						p_alarm->Check__ALARM(alarm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
					}

					Call__CLOSE(p_variable,p_alarm);
				}
			}
		}

		// ...
	}

	return 1;
}

