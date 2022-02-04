#include "StdAfx.h"
#include "CObj__STEP_FNC.h"
#include "CObj__STEP_FNC__DEF.h"


// ...
void CObj__STEP_FNC
::Mon__Wafer_Count_Ctrl(const int event_id, CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString	str_time;
	SYSTEMTIME st;

	// ...
	{
		GetLocalTime(&st);
		str_time.Format("%00004d.%002d.%002d", st.wYear,st.wMonth,st.wDay);

		// WAFER COUNT ...
		{
			if(sCH__TOTAL_COUNT_START_DATE->Check__DATA("") > 0)
			{
				sCH__TOTAL_COUNT_START_DATE->Set__DATA(str_time);

				aCH__WAFER_TOTAL_COUNT->Set__DATA("0");
			}
			if(sCH__CURRENT_COUNT_START_DATE->Check__DATA("") > 0)
			{
				sCH__CURRENT_COUNT_START_DATE->Set__DATA(str_time);
			
				aCH__WAFER_CURRENT_COUNT->Set__DATA("0");
			}
		}

		// RFx REF : RF ON_TIME ...
		{
			CString var_data;
			int i;

			for(i=0; i<CFG__RF_PART_SIZE; i++)
			{
				if(sCH__RF_PART__ON_TIME_START_DATE_X[i]->Check__DATA("") > 0)
				{
					sCH__RF_PART__ON_TIME_START_DATE_X[i]->Set__DATA(str_time);
				}
				
				// ...
				{
					aCH__RF_PART__ON_TIME_TOTAL_MIN_X[i]->Get__DATA(var_data);
					int cur_sec = atoi(var_data) * 60;
		
					var_data.Format("%1d", cur_sec);
					aCH__RF_PART__ON_TIME_TOTAL_SEC_X[i]->Set__DATA(var_data);
				}
			}
		}

		// ESC ON_TIME ...
		{
			CString var_data;

			if(sCH__ESC_ON_TIME_START_DATE->Check__DATA("") > 0)
			{
				sCH__ESC_ON_TIME_START_DATE->Set__DATA(str_time);
			}
			
			// ...
			{
				aCH__ESC_ON_TIME_TOTAL_MIN->Get__DATA(var_data);
				int cur_sec = atoi(var_data) * 60;
				
				var_data.Format("%1d", cur_sec);
				aCH__ESC_ON_TIME_TOTAL_SEC->Set__DATA(var_data);
			}
		}
	}

	// ...
	CString var_data;
	double  cur_value;
	double  cur_sec;

	int rf_hf_pwr   = -1;
	int rf_lf_pwr   = -1;
	int rf_bias_pwr = -1;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		// WAFER CURRENT COUNT INFO ...
		if(dCH__WAFER_CURRENT_COUNT_RESET->Check__DATA(STR__RESET) > 0)
		{
			dCH__WAFER_CURRENT_COUNT_RESET->Set__DATA(STR__RETURN);

			// ...
			{
				GetLocalTime(&st);	
				
				str_time.Format("%00004d.%002d.%002d", st.wYear,st.wMonth,st.wDay);
				sCH__CURRENT_COUNT_START_DATE->Set__DATA(str_time);

				aCH__WAFER_CURRENT_COUNT->Set__DATA("0");
			}
		}
		// WAFER TOTAL COUNT INFO ...
		if(dCH__WAFER_TOTAL_COUNT_RESET->Check__DATA(STR__RESET) > 0)
		{
			dCH__WAFER_TOTAL_COUNT_RESET->Set__DATA(STR__RETURN);
			
			// ...
			{
				GetLocalTime(&st);	
				
				str_time.Format("%00004d.%002d.%002d", st.wYear,st.wMonth,st.wDay);
				sCH__TOTAL_COUNT_START_DATE->Set__DATA(str_time);

				aCH__WAFER_CURRENT_COUNT->Get__DATA(var_data);
				aCH__WAFER_TOTAL_COUNT->Set__DATA(var_data);
			}
		}

		// RFx REF : RF ON_TIME INFO ...
		{
			int i;

			for(i=0; i<CFG__RF_PART_SIZE; i++)
			{
				if(dCH__RF_PART__ON_TIME_RESET_X[i]->Check__DATA(STR__RESET) > 0)
				{
					dCH__RF_PART__ON_TIME_RESET_X[i]->Set__DATA(STR__RETURN);

					GetLocalTime(&st);
						
					str_time.Format("%00004d.%002d.%002d", st.wYear,st.wMonth,st.wDay);
					sCH__RF_PART__ON_TIME_START_DATE_X[i]->Set__DATA(str_time);

					aCH__RF_PART__ON_TIME_TOTAL_HOUR_X[i]->Set__VALUE(0);
					aCH__RF_PART__ON_TIME_TOTAL_MIN_X[i]->Set__VALUE(0);
					aCH__RF_PART__ON_TIME_TOTAL_SEC_X[i]->Set__VALUE(0);
				}
			}
		}

		// ESC ON_TIME INFO ...
		{
			if(dCH__ESC_ON_TIME_RESET->Check__DATA(STR__RESET) > 0)
			{
				dCH__ESC_ON_TIME_RESET->Set__DATA(STR__RETURN);
				
				GetLocalTime(&st);

				str_time.Format("%00004d.%002d.%002d", st.wYear,st.wMonth,st.wDay);
				sCH__ESC_ON_TIME_START_DATE->Set__DATA(str_time);
					
				aCH__ESC_ON_TIME_TOTAL_HOUR->Set__VALUE(0);
				aCH__ESC_ON_TIME_TOTAL_MIN->Set__VALUE(0);
				aCH__ESC_ON_TIME_TOTAL_SEC->Set__VALUE(0);
			}
		}

		// RF ON Time ...
		// RF_PLASMA ...
		if(bActive__OBJ_CTRL__RF_PLASMA)
		{
			int p_index = RF_PART_INDEX__PLASMA;

			// ...
			{
				var_data = sEXT_CH__RF_PLASMA__MON_IO_POWER_SET->Get__STRING();
				cur_value = atof(var_data);

				if(cur_value >= 1.0)
				{
					rf_hf_pwr = 1;

					// ...
					{
						aCH__RF_PART__ON_TIME_TOTAL_SEC_X[p_index]->Inc__VALUE(1);
					
						aCH__RF_PART__ON_TIME_TOTAL_SEC_X[p_index]->Get__DATA(var_data);
						cur_sec = atof(var_data);
					}

					// ...
					{
						aCH__RF_PART__ON_TIME_TOTAL_MIN_X[p_index]->Get__DATA(var_data);
						int cfg_min = atoi(var_data);
						int cur_min = (int) (cur_sec / 60.0);

						if(cur_min > cfg_min)
						{
							aCH__RF_PART__ON_TIME_TOTAL_MIN_X[p_index]->Set__VALUE(cur_min);
						}
					}

					if(cur_sec >= 3600)
					{
						aCH__RF_PART__ON_TIME_TOTAL_SEC_X[p_index]->Set__VALUE(0);
						aCH__RF_PART__ON_TIME_TOTAL_MIN_X[p_index]->Set__VALUE(0);
						aCH__RF_PART__ON_TIME_TOTAL_HOUR_X[p_index]->Inc__VALUE(1);
					}
				}
				else
				{
					rf_hf_pwr = -1;
				}
			}
		}
		// RF_BIAS ...
		if(bActive__OBJ_CTRL__RF_BIAS)
		{
			int p_index = RF_PART_INDEX__BIAS;

			// ...
			{
				var_data = sEXT_CH__RF_BIAS__MON_IO_POWER_SET->Get__STRING();
				cur_value = atof(var_data);

				if(cur_value >= 1.0)
				{
					rf_bias_pwr = 1;

					// ...
					{
						aCH__RF_PART__ON_TIME_TOTAL_SEC_X[p_index]->Inc__VALUE(1);

						aCH__RF_PART__ON_TIME_TOTAL_SEC_X[p_index]->Get__DATA(var_data);
						cur_sec = atof(var_data);
					}

					// ...
					{
						aCH__RF_PART__ON_TIME_TOTAL_MIN_X[p_index]->Get__DATA(var_data);
						int cfg_min = atoi(var_data);
						int cur_min = (int) (cur_sec / 60.0);

						if(cur_min > cfg_min)
						{
							aCH__RF_PART__ON_TIME_TOTAL_MIN_X[p_index]->Set__VALUE(cur_min);
						}
					}

					if(cur_sec >= 3600)
					{
						aCH__RF_PART__ON_TIME_TOTAL_SEC_X[p_index]->Set__VALUE(0);
						aCH__RF_PART__ON_TIME_TOTAL_MIN_X[p_index]->Set__VALUE(0);
						aCH__RF_PART__ON_TIME_TOTAL_HOUR_X[p_index]->Inc__VALUE(1);
					}
				}
				else
				{
					rf_bias_pwr = -1;
				}
			}
		}

		if((rf_hf_pwr > 0) || (rf_lf_pwr > 0) || (rf_bias_pwr > 0))
		{
			// ...
			{
				aCH__ESC_ON_TIME_TOTAL_SEC->Inc__VALUE(1);
				
				aCH__ESC_ON_TIME_TOTAL_SEC->Get__DATA(var_data);
				cur_sec = atof(var_data);
			}
			
			// ...
			{
				aCH__ESC_ON_TIME_TOTAL_MIN->Get__DATA(var_data);
				int cfg_min = atoi(var_data);
				int cur_min = (int) (cur_sec / 60.0);
				
				if(cur_min > cfg_min)
				{
					aCH__ESC_ON_TIME_TOTAL_MIN->Set__VALUE(cur_min);
				}
			}
			
			if(cur_sec >= 3600)
			{
				aCH__ESC_ON_TIME_TOTAL_SEC->Set__VALUE(0);
				aCH__ESC_ON_TIME_TOTAL_MIN->Set__VALUE(0);
				aCH__ESC_ON_TIME_TOTAL_HOUR->Inc__VALUE(1);
			}			
		}

		// ...
	}

	// ...
}
