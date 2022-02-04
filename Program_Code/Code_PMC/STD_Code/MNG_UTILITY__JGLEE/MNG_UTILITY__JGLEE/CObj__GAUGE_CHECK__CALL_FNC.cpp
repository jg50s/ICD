#include "StdAfx.h"
#include "CObj__GAUGE_CHECK.h"


extern void Macro__Get_Date(CString& date, CString& time);


//-------------------------------------------------------------------------
int CObj__GAUGE_CHECK::
Call__ALL_CHECK(CII_OBJECT__VARIABLE *p_variable, 
				CII_OBJECT__ALARM *p_alarm)
{
	int r_flag;

	r_flag = Call__LOW_PRESSURE_CHECK(p_variable, p_alarm);
	if(r_flag < 0)		return -1;

	r_flag = Call__LINEAR_CHECK(p_variable, p_alarm);
	if(r_flag < 0)		return -1;

	return 1;
}

int CObj__GAUGE_CHECK::
Call__LOW_PRESSURE_CHECK(CII_OBJECT__VARIABLE *p_variable, 
						 CII_OBJECT__ALARM *p_alarm)
{
	// Chamber Pumping ...
	{
		xCH__OBJ_MSG->Set__DATA("Chamber Pumping ...");

		if(pOBJ_CTRL__CHM->Call__OBJECT("PUMPING") < 0)
		{
			return -11;
		}
	}

	// Stable Time ...
	{
		SCX__TIMER_CTRL x_timer_ctrl;
		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH__CUR_CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		double sec_stable = aCH_CFG__PRESSURE_STABLE_SEC->Get__VALUE();
		if(x_timer_ctrl->WAIT(sec_stable) < 0)		
		{
			return -12;
		}
	}

	// Data Initial ...
	{
		sCH__TEST_LOW_PRESS_MIN_NEW->Set__DATA("__");
		sCH__TEST_LOW_PRESS_MAX_NEW->Set__DATA("__");
		sCH__TEST_LOW_PRESS_AVG_NEW->Set__DATA("__");
	}

	// Pressure Check ...
	{
		SCX__TIMER_CTRL x_timer_ctrl;

		double min_press;
		double max_press;
		double avg_press;
		CString ch_data;

		sCH__CUR_LOW_PRESSURE_COUNT->Set__DATA("");

		int cfg_count = 10;
		int chk_count = 0;

		while(chk_count < cfg_count)
		{
			x_timer_ctrl->POLL(1.0);

			ch_data = sEXT_CH__CHM_PRESSURE->Get__STRING();
			double cur_press = atof(ch_data) * 1000.0;

			if(iSIM_MODE > 0)
			{
				cur_press = 1.0 * (10.0 - chk_count);
			}

			if(chk_count == 0)
			{
				min_press = cur_press;
				max_press = cur_press;
				avg_press = cur_press;
			}
			else
			{
				if(cur_press < min_press)		min_press = cur_press;
				if(cur_press > max_press)		max_press = cur_press;

				double t_count = (double) chk_count + 1.0;
				avg_press = (avg_press * (chk_count / t_count)) + (cur_press / t_count); 
			}
			
			//
			ch_data.Format("%.0f", min_press);
			sCH__TEST_LOW_PRESS_MIN_NEW->Set__DATA(ch_data);

			ch_data.Format("%.0f", max_press);
			sCH__TEST_LOW_PRESS_MAX_NEW->Set__DATA(ch_data);

			ch_data.Format("%.0f", avg_press);
			sCH__TEST_LOW_PRESS_AVG_NEW->Set__DATA(ch_data);

			//
			ch_data.Format("%1d", ++chk_count);
			sCH__CUR_LOW_PRESSURE_COUNT->Set__DATA(ch_data);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -13;
			}
		}
	}

	return 1;
}

int CObj__GAUGE_CHECK::
 Call__LINEAR_CHECK(CII_OBJECT__VARIABLE *p_variable, 
				   CII_OBJECT__ALARM *p_alarm)
{
	// ...
	{
		CString str_date;
		CString str_time;

		Macro__Get_Date(str_date,str_time);

		sCH__LAST_TEST_DATE->Set__DATA(str_date);
		sCH__LAST_TEST_TIME->Set__DATA(str_time);
	}

	// ...
	sCH__CUR_CHECK_COUNT->Set__DATA("");

	int i_limit = aCH__CFG_CHECK_COUNT->Get__VALUE();
	int r_flag;

	for(int i=0; i<=i_limit; i++)
	{
		r_flag = _Fnc__LINEAR_CHECK(p_variable, i);
		if(r_flag < 0)		break;

		CString ch_data;
		ch_data.Format("%1d", i);
		sCH__CUR_CHECK_COUNT->Set__DATA(ch_data);
	}

	if(r_flag > 0)
	{
		CString ch_data;
		
		aCH_CFG__CHECK_ERROR_PERCENT->Get__DATA(ch_data);
		sCH__CUR_CHECK_ERROR_PERCENT->Set__DATA(ch_data);

		//
		ch_data = sCH__TEST_LINEAR_CHECK_RESULT_REF->Get__STRING();
		double ref_result = atof(ch_data);

		ch_data = sCH__TEST_LINEAR_CHECK_RESULT_NEW->Get__STRING();
		double new_result = atof(ch_data);
		
		double err_result = ref_result - new_result;
		if(err_result < 0)		err_result = -err_result;

		double cfg__err_per = aCH_CFG__CHECK_ERROR_PERCENT->Get__VALUE();

		if(ref_result > 0.001)
		{
			double cur__err_per = (err_result / ref_result) * 100.0;
			ch_data.Format("%.1f", cur__err_per);
		}
		else
		{
			ch_data = "--";
		}
		sCH__TEST_LINEAR_CHECK_ERROR_NEW->Set__DATA(ch_data);
	}

	// Chamber Pumping ...
	{
		pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();
		pOBJ_CTRL__CHM->Call__OBJECT("PUMPING");
		pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
	}
	return r_flag;
}
int CObj__GAUGE_CHECK::
_Fnc__LINEAR_CHECK(CII_OBJECT__VARIABLE *p_variable, const int loop_index)
{
	// Chamber Pumping ...
	{
		xCH__OBJ_MSG->Set__DATA("Chamber Pumping ...");

		if(pOBJ_CTRL__CHM->Call__OBJECT("PUMPING") < 0)
		{
			return -11;
		}
	}

	// Stable Time ...
	{
		xCH__OBJ_MSG->Set__DATA("Stable Time ...");

		SCX__TIMER_CTRL x_timer_ctrl;
		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH__CUR_CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		double sec_stable = aCH_CFG__PRESSURE_STABLE_SEC->Get__VALUE();
		if(x_timer_ctrl->WAIT(sec_stable) < 0)		
		{
			return -12;
		}
	}

	// VAT Close ...
	{
		xCH__OBJ_MSG->Set__DATA("VAT Close ...");

		if(pOBJ_CTRL__CHM->Call__OBJECT("CLOSE.VAC_LINE") < 0)
		{
			return -13;
		}
	}

	// Gas Flow ...
	{
		xCH__OBJ_MSG->Set__DATA("Gas Flow ...");

		CString ch_data = dCH_PARA__TEST_GAS_TYPE->Get__STRING();

		int db_index = Get__Gas_Type_Index(ch_data);
		if(db_index < 0)		return -21;

		double cfg_flow = aCH_PARA__TEST_GAS_FLOW->Get__VALUE();
		aEXT_CH__MFCx_PARA_SET_FLOW[db_index]->Set__VALUE(cfg_flow);

		if(pOBJ_CTRL__MFC_X[db_index]->Call__OBJECT("CONTROL") < 0)
		{
			return -22;
		}
	}

	// Pressure Check ...
	if(loop_index == 0)
	{
		xCH__OBJ_MSG->Set__DATA("Pressure Check ...");

		sCH__TEST_INTERVAL_TIME->Set__DATA("");
		sCH__TEST_INTERVAL_CUR->Set__DATA("");

		// ...
		{
			int i_limit = CFG_GAUGE__TEST_LIST;
			int i;

			for(i=0; i<i_limit; i++)
			{
				sCH__TEST_TIME_NEW_X[i]->Set__DATA("__");
				sCH__TEST_PRESS_NEW_X[i]->Set__DATA("__");
				sCH__TEST_RATE_NEW_X[i]->Set__DATA("__");
			}

			sCH__CUR_CHECK_ERROR_PERCENT->Set__DATA("__");

			sCH__TEST_LINEAR_CHECK_RESULT_NEW->Set__DATA("__");
			sCH__TEST_LINEAR_CHECK_ERROR_NEW->Set__DATA("__");

			sCH__RESULT_STRING->Set__DATA("");
		}

		// ...
		SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
		CString ch_data;

		x_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH__TEST_INTERVAL_CUR->Get__CHANNEL_NAME());
		x_timer_ctrl->START__COUNT_UP(99999);

		double sim_sec = 10.0;
		if(iSIM_MODE > 0)		sim_sec = 30.0;

		while(1)
		{
			Sleep(1);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -31;
			}

			// ...
			double cfg_pressure = aCH__CFG_UPPER_PRESSURE->Get__VALUE();
			double cur_pressure;

			if(iSIM_MODE > 0)
			{
				double cur_sec = x_timer_ctrl->Get__CURRENT_TIME();
				double cur_per = cur_sec / sim_sec;
			
				cur_pressure = cfg_pressure * cur_per;
				ch_data.Format("%.3f", cur_pressure);
				sEXT_CH__CHM_PRESSURE->Set__DATA(ch_data);
			}
			else
			{
				ch_data = sEXT_CH__CHM_PRESSURE->Get__STRING();
				cur_pressure = atof(ch_data);
			}

			if(cur_pressure >= cfg_pressure)
			{
				ch_data.Format("%.1f", x_timer_ctrl->Get__CURRENT_TIME());
				sCH__TEST_INTERVAL_TIME->Set__DATA(ch_data);

				ch_data.Format("%.3f", cur_pressure);
				sCH__CUR_UPPER_PRESSURE->Set__DATA(ch_data);
				break;
			}
		}
	}
	else if(loop_index > 0)
	{
		xCH__OBJ_MSG->Set__DATA("Pressure Check ...");

		// ...
		{
			int i_limit = CFG_GAUGE__TEST_LIST;
			int i;

			for(i=0; i<i_limit; i++)
			{
				sCH__TEST_TIME_NEW_X[i]->Set__DATA("__");
				sCH__TEST_PRESS_NEW_X[i]->Set__DATA("__");
			}
		}

		// ...
		SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
		CString ch_data;

		ch_data = sCH__TEST_INTERVAL_TIME->Get__STRING();
		double total_sec = atof(ch_data);
		double check_sec = total_sec / 10.0;
		int check_count = 1;

		x_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH__TEST_INTERVAL_CUR->Get__CHANNEL_NAME());
		x_timer_ctrl->START__COUNT_UP(99999);

		while(1)
		{
			Sleep(1);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -32;
			}

			// ...
			double ref_sec = check_sec * check_count;
			double cur_sec = x_timer_ctrl->Get__CURRENT_TIME();

			double cur_pressure;

			if(iSIM_MODE > 0)
			{
				ch_data = sCH__CUR_UPPER_PRESSURE->Get__STRING();
				double trg_pressure = atof(ch_data);
				double cur_per = cur_sec / total_sec;

				cur_pressure = trg_pressure * cur_per;
				ch_data.Format("%.3f", cur_pressure);
				sEXT_CH__CHM_PRESSURE->Set__DATA(ch_data);

				cur_pressure *= 1000.0;
			}
			else
			{
				ch_data = sEXT_CH__CHM_PRESSURE->Get__STRING();
				cur_pressure = atof(ch_data) * 1000.0;
			}

			if(cur_sec < ref_sec)		
			{
				continue;
			}

			if(check_count <= CFG_GAUGE__TEST_LIST)
			{
				int db_i = check_count - 1;
				check_count++;

				ch_data.Format("%.2f", cur_sec);
				sCH__TEST_TIME_NEW_X[db_i]->Set__DATA(ch_data);
				
				ch_data.Format("%.1f", cur_pressure);
				sCH__TEST_PRESS_NEW_X[db_i]->Set__DATA(ch_data);
			
				if(db_i > 0)
				{
					double x1, y1;
					double x2, y2;

					// 1.
					{
						ch_data = sCH__TEST_TIME_NEW_X[db_i-1]->Get__STRING();
						x1 = atof(ch_data);
					
						ch_data = sCH__TEST_PRESS_NEW_X[db_i-1]->Get__STRING();
						y1 = atof(ch_data);
					}
					// 2.
					{
						ch_data = sCH__TEST_TIME_NEW_X[db_i]->Get__STRING();
						x2 = atof(ch_data);

						ch_data = sCH__TEST_PRESS_NEW_X[db_i]->Get__STRING();
						y2 = atof(ch_data);
					}

					double x_data = x2 - x1;
					double y_data = y2 - y1;

					double m_data;
					if(x_data > 0)		m_data = y_data / x_data;
					else				m_data = y_data / 0.001;

					ch_data = sCH__TEST_RATE_NEW_X[db_i-1]->Get__STRING();
					double avg_data = atof(ch_data);
					
					double t_count = (double) loop_index;
					avg_data = (avg_data * (t_count - 1.0) / t_count) + (m_data / t_count);

					ch_data.Format("%.3f", avg_data);
					sCH__TEST_RATE_NEW_X[db_i-1]->Set__DATA(ch_data);
				}

				if(db_i > 0)
				{
					ch_data = sCH__TEST_RATE_NEW_X[db_i-1]->Get__STRING();

					CString str_data;
					str_data.Format("%1d/%s,", db_i,ch_data);
									
					ch_data = sCH__RESULT_STRING->Get__STRING();
					ch_data += str_data;

					sCH__RESULT_STRING->Set__DATA(ch_data);
				}
			}

			if(check_count > CFG_GAUGE__TEST_LIST)
			{
				double x1, y1;
				double x2, y2;

				// 1.
				{
					ch_data = sCH__TEST_TIME_NEW_X[0]->Get__STRING();
					x1 = atof(ch_data);

					ch_data = sCH__TEST_PRESS_NEW_X[0]->Get__STRING();
					y1 = atof(ch_data);
				}
				// 10.
				{
					ch_data = sCH__TEST_TIME_NEW_X[9]->Get__STRING();
					x2 = atof(ch_data);

					ch_data = sCH__TEST_PRESS_NEW_X[9]->Get__STRING();
					y2 = atof(ch_data);
				}

				double x_data = x2 - x1;
				double y_data = y2 - y1;

				double m_data;
				if(x_data > 0)		m_data = y_data / x_data;
				else				m_data = y_data / 0.001;

				ch_data = sCH__TEST_LINEAR_CHECK_RESULT_NEW->Get__STRING();
				double avg_data = atof(ch_data);
				
				double t_count = (double) loop_index;
				avg_data = (avg_data * (t_count - 1.0) / t_count) + (m_data / t_count);

				ch_data.Format("%.3f", avg_data);
				sCH__TEST_LINEAR_CHECK_RESULT_NEW->Set__DATA(ch_data);

				break;
			}
		}
	
		// ...
	}

	return 1;
}
