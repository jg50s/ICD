#include "StdAfx.h"
#include "CObj__MTC_FNC.h"

#include "Macro_Function.h"


union UNION_4_BYTE__FLOAT
{
	float fDATA;
	unsigned long uiDATA;
	char  cBYTE[4];
};


// ...
 void CObj__MTC_FNC::
 Mon__PRESSURE_STATUS(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
 {
	 CString ch_data;

	 if(iActive__SIM_MODE > 0)
	 {
		dEXT_CH__DI_MTC_GATE_OPEN_SNS->Set__DATA(STR__OFF);
		dEXT_CH__DI_MTC_GATE_CLOSE_SNS->Set__DATA(STR__ON);
	 }


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);
		
	
		// State Mon ...
		{
			// PUMPING_STATE Mon ...
			{
				if(dEXT_CH__DI_MTC_ATM_SNS->Check__DATA(STR__ON) > 0)
				{
					sCH__MON_PUMPING_STATE->Set__DATA(STR__ATM);
				}
				else if(dEXT_CH__DI_MTC_VAC_SNS->Check__DATA(STR__ON) > 0)
				{
					sCH__MON_PUMPING_STATE->Set__DATA(STR__VAC);
				}
			}

			// GATE_STATE Mon ...
			{
				bool active__slot_open  = false;
				bool active__slot_close = false;

				if(dEXT_CH__DI_MTC_GATE_OPEN_SNS->Check__DATA(STR__ON) > 0)
				{
					if(dEXT_CH__DI_MTC_GATE_CLOSE_SNS->Check__DATA(STR__OFF) > 0)
					{
						active__slot_open = true;
					}
				}
				else if(dEXT_CH__DI_MTC_GATE_CLOSE_SNS->Check__DATA(STR__ON) > 0)
				{
					active__slot_close = true;
				}

					 if(active__slot_open)		sCH__MON_GATE_STATE->Set__DATA(STR__OPEN);
				else if(active__slot_close)		sCH__MON_GATE_STATE->Set__DATA(STR__CLOSE);
				else							sCH__MON_GATE_STATE->Set__DATA(STR__UNKNOWN);
			}
		}

		// Check V/V Mon ...
		{
			if(dEXT_CH__DI_MTC_ATM_SNS->Check__DATA(STR__ON) > 0)
			{
				dEXT_CH__DO_MTC_CHECK_VV->Set__DATA(STR__OPEN);
			}
			else
			{
				dEXT_CH__DO_MTC_CHECK_VV->Set__DATA(STR__CLOSE);
			}
		}

		if(iActive__SIM_MODE > 0)
		{
			double cur__press_torr  = aCH__MTC_PRESSURE_SIM_MODE->Get__VALUE();
			double cur__press_mtorr = cur__press_torr * 1000.0;

			aCH__MTC_PRESSURE_TORR->Set__VALUE(cur__press_torr);
		}
		else
		{
			ch_data = sEXT_CH__SI_MTC_GAUGE_PRESSURE_HEXA->Get__STRING();
			
			CStringArray l_data;
			Macro__Get_StringArrray_From_String(ch_data, " ", l_data);

			// ...
			byte hexa_data[5];
			memset(hexa_data, 0, 5);

			int data_len = l_data.GetSize();
			for(int i=0; i<data_len; i++)
			{
				hexa_data[i] = 0xff & Macro__Get_Hexa_From_String(l_data[i]);
			}

			// ...
			UNION_4_BYTE__FLOAT m_pressure;

			m_pressure.cBYTE[0] = 0xff & hexa_data[0];
			m_pressure.cBYTE[1] = 0xff & hexa_data[1];
			m_pressure.cBYTE[2] = 0xff & hexa_data[2];
			m_pressure.cBYTE[3] = 0xff & hexa_data[3];
			/*
			m_pressure.cBYTE[0] = 0xff & hexa_data[3];
			m_pressure.cBYTE[1] = 0xff & hexa_data[2];
			m_pressure.cBYTE[2] = 0xff & hexa_data[1];
			m_pressure.cBYTE[3] = 0xff & hexa_data[0];
			*/

			aCH__MTC_PRESSURE_TORR->Set__VALUE(m_pressure.fDATA);
		}

		// ...
		{
			double cur__press_torr  = aCH__MTC_PRESSURE_TORR->Get__VALUE();
			double cur__press_mtorr = cur__press_torr * 1000.0;

				 if(cur__press_torr < 0.1)		ch_data.Format("%.1f mtorr", cur__press_mtorr);
			else if(cur__press_torr < 1.0)		ch_data.Format("%.0f mtorr", cur__press_mtorr);
			else								ch_data.Format("%.0f torr",  cur__press_torr);

			sCH__MTC_PRESSURE_DISPLAY->Set__DATA(ch_data);
		}

		// ...
	}
 }
 
