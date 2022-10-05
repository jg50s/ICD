#include "StdAfx.h"
#include "CObj__LFC_IO.h"

#include "CCommon_Utility.h"
#include "CCommon_Def.h"


// ...
int  CObj__LFC_IO
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int loop_count = 0;
	CString ch_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.01);

		loop_count++;
		if(loop_count > 100)		loop_count = 1;


		if(loop_count == 1)
		{
			int active__err_check = p_alarm->Check__Posted_Internal_Alarm(iLIST_ALID__PART);

			if(active__err_check > 0)		dCH__MON_PART_ERROR_ACTIVE->Set__DATA(STR__ON);
			else							dCH__MON_PART_ERROR_ACTIVE->Set__DATA(STR__OFF);
		}

		// Range : Flow ...
		if(loop_count == 0)
		{			
			aCH__CFG_LFC_MIN_VALUE->Get__DATA(ch_data);
			double min_value = atof(ch_data);

			aCH__CFG_LFC_MAX_VALUE->Get__DATA(ch_data);
			double max_value = atof(ch_data);

			aCH__CFG_LFC_DEC_VALUE->Get__DATA(ch_data);
			int i_dec = atoi(ch_data);

			aCH__MON_LFC_SET_FLOW->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
			aCH__MON_LFC_READ_FLOW->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
			aCH__PARA_SET_VALUE->Change__MIN_MAX_DEC(min_value,max_value,i_dec);
		}

		// Flow ...
		if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
		{
			UNION_2_BYTE__UINT m_value;
			double cur_percent;

			ch_data = sEXT_CH__IO_LFC_READ->Get__STRING();
			m_value.uiDATA = atoi(ch_data);

			int max_flow = iLINK_DATA__MAX_FLOW;

			if(m_value.uiDATA <= 0x7FFF)		cur_percent =  m_value.uiDATA / (double) max_flow;
			else								cur_percent = (m_value.uiDATA - 0xFFFF) / (double) max_flow;

			ch_data.Format("%.1f", cur_percent*100.0);
			sCH__MON_LFC_FLOW_PERCENT->Set__DATA(ch_data);

			double cfg__flow_max = aCH__CFG_LFC_MAX_VALUE->Get__VALUE();
			double cur_value = cfg__flow_max * cur_percent;

			if(cur_value < 0)		cur_value = 0;
			aCH__MON_LFC_READ_FLOW->Set__VALUE(cur_value);
		}
		else
		{
			ch_data = sEXT_CH__IO_LFC_READ->Get__STRING();
			double cur__io_flow = atof(ch_data);

			double cfg__flow_max = aCH__CFG_LFC_MAX_VALUE->Get__VALUE();
			double cur__flow_per = 0.0;

			if(cfg__flow_max > 0.01)			cur__flow_per = cur__io_flow / cfg__flow_max;
			else								cur__flow_per = 0.0;

			ch_data.Format("%.1f", cur__flow_per*100.0);
			sCH__MON_LFC_FLOW_PERCENT->Set__DATA(ch_data);

			aCH__MON_LFC_READ_FLOW->Set__VALUE(cur__io_flow);
		}

		// Status ...
		if(bActive__LFC_STATE)
		{
			if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
			{
				ch_data = sEXT_CH__IO_LFC_STATE->Get__STRING();
				int i_sts = atoi(ch_data);

				ch_data.Format("%02X", i_sts);
				sCH__MON_LFC_EXCEPTION_STATE->Set__DATA(ch_data);

				//
				if(i_sts == 0)			ch_data = "Normal";
				else					ch_data = "Alarm";

				sCH__MON_LFC_EXCEPTION_INFO->Set__DATA(ch_data);
			}
			else
			{
				sCH__MON_LFC_EXCEPTION_STATE->Set__DATA("???");
				sCH__MON_LFC_EXCEPTION_INFO->Set__DATA("???");
			}
		}
		else
		{
			sCH__MON_LFC_EXCEPTION_STATE->Set__DATA("__");
			sCH__MON_LFC_EXCEPTION_INFO->Set__DATA("__");
		}

		// Valve.Voltage ...
		if(bActive__LFC_VALVE_VOLTAGE)
		{
			if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
			{
				UNION_2_BYTE__UINT m_value;
				double cur_percent;

				ch_data = sEXT_CH__IO_LFC_VALVE_VOLTAGE->Get__STRING();
				m_value.uiDATA = atoi(ch_data);

				if(m_value.uiDATA <= 0x7FFF)		cur_percent =  m_value.uiDATA / (double) iLINK_DATA__MAX_DEFAULT;
				else								cur_percent = (m_value.uiDATA - 0xFFFF) / (double) iLINK_DATA__MAX_DEFAULT;

				double cfg_max = 100.0;
				int i_dec = 1;

				double cur_value = cfg_max * cur_percent;
				ch_data.Format("%.1f", cur_value);
				sCH__MON_LFC_READ_VALVE_VOLTAGE->Set__DATA(ch_data);

				ch_data.Format("%.1f", cur_percent);
				sCH__MON_LFC_VALVE_VOLTAGE_PERCENT->Set__DATA(ch_data);
			}
			else
			{
				sCH__MON_LFC_READ_VALVE_VOLTAGE->Set__DATA("???");
				sCH__MON_LFC_VALVE_VOLTAGE_PERCENT->Set__DATA("???");
			}
		}
		else
		{
			sCH__MON_LFC_READ_VALVE_VOLTAGE->Set__DATA("__");
			sCH__MON_LFC_VALVE_VOLTAGE_PERCENT->Set__DATA("__");
		}

		// Pressure ...
		if(iActive__SIM_MODE > 0)
		{
			ch_data = "50.0";
			sCH__MON_LFC_INLET_PRESSURE_PERCENT->Set__DATA(ch_data);
		}
		else
		{
			if(bActive__LFC_PRESSURE)
			{
				if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
				{
					UNION_2_BYTE__UINT m_value;
					double cur_percent;

					ch_data = sEXT_CH__IO_LFC_PRESSURE->Get__STRING();
					m_value.uiDATA = atoi(ch_data);

					if(m_value.uiDATA <= 0x7FFF)		cur_percent =  m_value.uiDATA / (double) iLINK_DATA__MAX_DEFAULT;
					else								cur_percent = (m_value.uiDATA - 0xFFFF) / (double) iLINK_DATA__MAX_DEFAULT;

					double cfg_max = aCH__CFG_RANGE_MAX_PRESSURE->Get__VALUE();
					int i_dec = (int) aCH__CFG_RANGE_DEC_PRESSURE->Get__VALUE();

					CString str_fmt;
					str_fmt.Format("%%.%1df", i_dec);

					double cur_value = cfg_max * cur_percent;
					ch_data.Format(str_fmt, cur_value);
					sCH__MON_LFC_READ_INLET_PRESSURE->Set__DATA(ch_data);			

					ch_data.Format("%.1f", cur_percent);
					sCH__MON_LFC_INLET_PRESSURE_PERCENT->Set__DATA(ch_data);			
				}
				else
				{
					sCH__MON_LFC_READ_INLET_PRESSURE->Set__DATA("???");
					sCH__MON_LFC_INLET_PRESSURE_PERCENT->Set__DATA("???");			
				}
			}
			else
			{
				sCH__MON_LFC_READ_INLET_PRESSURE->Set__DATA("__");
				sCH__MON_LFC_INLET_PRESSURE_PERCENT->Set__DATA("__");			
			}
		}

		// Temperature ...
		if(bActive__LFC_TEMPERATURE)
		{
			if(iLINK_DATA__TYPE == _DATA_TYPE__HEXA)
			{
				UNION_2_BYTE__UINT m_value;
				double cur_percent;

				ch_data = sEXT_CH__IO_LFC_TEMPERATURE->Get__STRING();
				m_value.uiDATA = atoi(ch_data);

				if(m_value.uiDATA <= 0x7FFF)		cur_percent =  m_value.uiDATA / (double) iLINK_DATA__MAX_DEFAULT;
				else								cur_percent = (m_value.uiDATA - 0xFFFF) / (double) iLINK_DATA__MAX_DEFAULT;

				double cfg_max = aCH__CFG_RANGE_MAX_TEMPERATURE->Get__VALUE();
				int i_dec = (int) aCH__CFG_RANGE_DEC_TEMPERATURE->Get__VALUE();

				CString str_fmt;
				str_fmt.Format("%%.%1df", i_dec);

				double cur_value = cfg_max * cur_percent;
				ch_data.Format(str_fmt, cur_value);
				sCH__MON_LFC_READ_TEMPERATURE->Set__DATA(ch_data);

				ch_data.Format("%.1f", cur_percent);
				sCH__MON_LFC_TEMPERATURE_PERCENT->Set__DATA(ch_data);
			}
			else
			{
				sCH__MON_LFC_READ_TEMPERATURE->Set__DATA("???");
				sCH__MON_LFC_TEMPERATURE_PERCENT->Set__DATA("???");
			}
		}
		else
		{
			sCH__MON_LFC_READ_TEMPERATURE->Set__DATA("__");
			sCH__MON_LFC_TEMPERATURE_PERCENT->Set__DATA("__");
		}

		//
		if(dCH__CFG_LFC_USE->Check__DATA(STR__YES) < 0)
		{
			aCH__MON_LFC_READ_FLOW->Set__VALUE(0);
		}

		// REQ : 3WAY.VLV ...
		if(bActive__3WAY_VLV)
		{
			// SET.VLV ...			
			if(sCH__REQ_3WAY_VLV->Check__DATA("") < 0)
			{
				ch_data = sCH__REQ_3WAY_VLV->Get__STRING();
				sCH__REQ_3WAY_VLV->Set__DATA("");

				if(ch_data.CompareNoCase("CLOSE") == 0)
				{
					doEXT_CH__3WAY_VLV_FINAL->Set__DATA(STR__CLOSE);
					doEXT_CH__3WAY_VLV_DUMP->Set__DATA(STR__CLOSE);
				}
				else if(ch_data.CompareNoCase("OPEN") == 0)
				{
					doEXT_CH__3WAY_VLV_FINAL->Set__DATA(STR__OPEN);
					doEXT_CH__3WAY_VLV_DUMP->Set__DATA(STR__CLOSE);
				}
				else if(ch_data.CompareNoCase("DUMP") == 0)
				{
					doEXT_CH__3WAY_VLV_FINAL->Set__DATA(STR__CLOSE);
					doEXT_CH__3WAY_VLV_DUMP->Set__DATA(STR__OPEN);
				}
				else if(ch_data.CompareNoCase("AL.OP") == 0)
				{
					doEXT_CH__3WAY_VLV_FINAL->Set__DATA(STR__OPEN);
					doEXT_CH__3WAY_VLV_DUMP->Set__DATA(STR__OPEN);
				}
			}

			// GET.VLV ...
			CString cur_sts;

			if(doEXT_CH__3WAY_VLV_FINAL->Check__DATA(STR__OPEN) > 0)
			{
				if(doEXT_CH__3WAY_VLV_DUMP->Check__DATA(STR__OPEN) > 0)			cur_sts = "AL.OP";
				else															cur_sts = "OPEN";
			}
			else
			{
				if(doEXT_CH__3WAY_VLV_DUMP->Check__DATA(STR__OPEN) > 0)			cur_sts = "DUMP";
				else															cur_sts = "CLOSE";
			}

			sCH__MON_3WAY_VLV->Set__DATA(cur_sts);
		}

		// ...
	}

	return 1;
}

