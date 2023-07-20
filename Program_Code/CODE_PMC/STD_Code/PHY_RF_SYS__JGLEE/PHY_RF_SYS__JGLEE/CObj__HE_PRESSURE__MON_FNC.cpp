#include "StdAfx.h"
#include "CObj__HE_PRESSURE.h"
#include "CObj__HE_PRESSURE__ALID.h"

#include "CCommon_Utility.h"
#include "Macro__Function.h"


// ...
int CObj__HE_PRESSURE
::Mon__STATUS(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	xI_LOG_CTRL->WRITE__LOG("Mon__STATUS() : Start ...");

	// ...
	int loop_count = 0;
	int i;

	// Output.Init ...
	for(i=0; i<iZONE_SIZE; i++)
	{
		Fnc__PRESSURE_SET(i, 0.0);
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		loop_count++;
		if(loop_count > 10)		loop_count = 1;


		// Output ...
		{
			for(i=0; i<iZONE_SIZE; i++)
			{
				double user_set = aCH__USER_IO_PRESSURE_SET_X[i]->Get__VALUE();
				double mon_set  = aCH__MON_IO_PRESSURE_SET_X[i]->Get__VALUE();

				if(user_set != mon_set)			Fnc__PRESSURE_SET(i, user_set);
			}
		}

		// Input ...
		{
			CString ch_data;

			for(int i=0; i<iZONE_SIZE; i++)
			{
				// State ...
				{
					CString str_hexa = siEXT_CH__STATE_HEXA_X[i]->Get__STRING();
					unsigned char m_state = Macro__Get_1_BYTE_FROM_HEXA(str_hexa);

					ch_data.Format("%02X", m_state);
					sCH__MON_IO_STATUS_X[i]->Set__DATA(ch_data);
				}

				// Pressure ...
				{
					double cfg_max, cfg_min;
					int cfg_dec;

					aCH__MON_IO_PRESSURE_GET_X[i]->Get__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);

					//
					CString str_hexa = siEXT_CH__PRESSURE_HEXA_X[i]->Get__STRING();
					unsigned short int data_hexa = Macro__Get_2_UINT_FROM_HEXA(str_hexa);

					float data_ratio = 0.0;

					if(data_hexa >= 0x8000)			data_ratio = - (0xffff - data_hexa) / (double) 0x7FFF;
					else							data_ratio = data_hexa / (double) 0x7FFF;

					double cur_pressure = cfg_max * data_ratio;
					
					aCH__MON_IO_PRESSURE_GET_X[i]->Set__VALUE(cur_pressure);
				}
				// Flow ...
				{
					double cfg_max, cfg_min;
					int cfg_dec;

					aCH__MON_IO_FLOW_X[i]->Get__MIN_MAX_DEC(cfg_min,cfg_max,cfg_dec);

					//
					CString str_hexa = siEXT_CH__FLOW_HEXA_X[i]->Get__STRING();
					unsigned short int data_hexa = Macro__Get_2_UINT_FROM_HEXA(str_hexa);

					float data_ratio = 0.0;

					if(data_hexa >= 0x8000)			data_ratio = - (0xffff - data_hexa) / (double) 0x7FFF;
					else							data_ratio = data_hexa / (double) 0x7FFF;

					double cur_flow = cfg_max * data_ratio;

					aCH__MON_IO_FLOW_X[i]->Set__VALUE(cur_flow);
				}
			}
		}
	}

	return 1;
}
