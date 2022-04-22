#include "StdAfx.h"
#include "CObj__LBx_TEST.h"
#include "CObj__LBx_TEST__DEF.h"



// ...
int  CObj__LBx_TEST::
Call__LBA_SV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__LBx_CYCLE_TEST(p_variable,p_alarm, VLV_TYPE__SV, _LLx_INDEX__LBA);
}
int  CObj__LBx_TEST::
Call__LBB_SV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__LBx_CYCLE_TEST(p_variable,p_alarm, VLV_TYPE__SV, _LLx_INDEX__LBB);
}
int  CObj__LBx_TEST::
Call__LBC_SV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__LBx_CYCLE_TEST(p_variable,p_alarm, VLV_TYPE__SV, _LLx_INDEX__LBC);
}
int  CObj__LBx_TEST::
Call__LBD_SV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__LBx_CYCLE_TEST(p_variable,p_alarm, VLV_TYPE__SV, _LLx_INDEX__LBD);
}

int  CObj__LBx_TEST::
Call__LBA_DV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__LBx_CYCLE_TEST(p_variable,p_alarm, VLV_TYPE__DV, _LLx_INDEX__LBA);
}
int  CObj__LBx_TEST::
Call__LBB_DV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__LBx_CYCLE_TEST(p_variable,p_alarm, VLV_TYPE__DV, _LLx_INDEX__LBB);
}
int  CObj__LBx_TEST::
Call__LBC_DV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__LBx_CYCLE_TEST(p_variable,p_alarm, VLV_TYPE__DV, _LLx_INDEX__LBC);
}
int  CObj__LBx_TEST::
Call__LBD_DV_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__LBx_CYCLE_TEST(p_variable,p_alarm, VLV_TYPE__DV, _LLx_INDEX__LBD);
}

// ...
int  CObj__LBx_TEST::
Fnc__LBx_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, 
					CII_OBJECT__ALARM* p_alarm, 
					const int vlv_type,
					const int llx_index)
{
	CII_EXT_OBJECT__CTRL *p_obj_ctrl = pOBJ_CTRL__LLx_FNC[llx_index];

	// ...
	{	
		CString var_data;	

		int i_limit;
		int i;

		aCH__CYCLE_TEST_CFG_CYCLE_COUNT->Get__DATA(var_data);
		i_limit = atoi(var_data);

		for(i=0; i<i_limit; i++)
		{
			int n_count = i + 1;

			// ...
			{
				var_data.Format("%1d", n_count);
				sCH__CYCLE_TEST_CUR_CYCLE_COUNT->Set__DATA(var_data);
			}

			// ...
			{
				int err_flag = -1;
				int alarm_id = -1;

				if(dEXT_CH__LLx_OBJ_STATUS[llx_index]->Check__DATA(STR__MAINTMODE) < 0)
				{
					err_flag = 1;

					alarm_id = ALID__LBA_STATUS_IS_NOT_MAINT + llx_index;
				}

				if(err_flag > 0)
				{
					CString r_act;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);	
					return -12;
				}
			}

			// Open ...
			{
				SCX__ASYNC_TIMER_CTRL x_async_timer;

				x_async_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__CYCLE_TEST_OP_TIME_CUR->Get__CHANNEL_NAME());
				x_async_timer->START__COUNT_UP(9999);

				if(vlv_type == VLV_TYPE__SV)
				{
					if(p_obj_ctrl->Call__OBJECT(CMMD__SV_OPEN) < 0)
					{
						return -21;
					}
				}
				else if(vlv_type == VLV_TYPE__DV)
				{
					if(p_obj_ctrl->Call__OBJECT(CMMD__DV_OPEN) < 0)
					{
						return -22;
					}
				}
				else
				{
					return -23;
				}

				// ...
				{
					double cur_sec = x_async_timer->Get__CURRENT_TIME();
					x_async_timer->STOP();

					sCH__CYCLE_TEST_OP_TIME_AVG->Get__DATA(var_data);
					double pre_avg = atof(var_data);

					CII__VAR_STRING_CTRL* p_ch_min = sCH__CYCLE_TEST_OP_TIME_MIN.Get__PTR();
					CII__VAR_STRING_CTRL* p_ch_max = sCH__CYCLE_TEST_OP_TIME_MAX.Get__PTR();

					CString cur_avg = Get__AVG_DATA(n_count, cur_sec,pre_avg);
					sCH__CYCLE_TEST_OP_TIME_AVG->Set__DATA(cur_avg);
					Fnc__Check_MIN_MAX_DATA(n_count, p_ch_min,p_ch_max, cur_sec);
				}
			}

			// ...
			{
				SCX__TIMER_CTRL x_timer_ctrl;
				x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
				x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH__CYCLE_TEST_CUR_DELAY_SEC->Get__CHANNEL_NAME());

				aCH__CYCLE_TEST_CFG_DELAY_SEC->Get__DATA(var_data);
				double cfg_sec = atof(var_data);

				if(x_timer_ctrl->WAIT(cfg_sec) < 0)
				{
					return -101;
				}
			}

			// Close ...
			{
				SCX__ASYNC_TIMER_CTRL x_async_timer;

				x_async_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__CYCLE_TEST_CL_TIME_CUR->Get__CHANNEL_NAME());
				x_async_timer->START__COUNT_UP(9999);

				if(vlv_type == VLV_TYPE__SV)
				{
					if(p_obj_ctrl->Call__OBJECT(CMMD__SV_CLOSE) < 0)
					{
						return -31;
					}
				}
				else if(vlv_type == VLV_TYPE__DV)
				{
					if(p_obj_ctrl->Call__OBJECT(CMMD__DV_CLOSE) < 0)
					{
						return -32;
					}
				}
				else
				{
					return -33;
				}

				// ...
				{
					double cur_sec = x_async_timer->Get__CURRENT_TIME();
					x_async_timer->STOP();

					sCH__CYCLE_TEST_CL_TIME_AVG->Get__DATA(var_data);
					double pre_avg = atof(var_data);

					CII__VAR_STRING_CTRL* p_ch_min = sCH__CYCLE_TEST_CL_TIME_MIN.Get__PTR();
					CII__VAR_STRING_CTRL* p_ch_max = sCH__CYCLE_TEST_CL_TIME_MAX.Get__PTR();

					CString cur_avg = Get__AVG_DATA(n_count, cur_sec,pre_avg);
					sCH__CYCLE_TEST_CL_TIME_AVG->Set__DATA(cur_avg);
					Fnc__Check_MIN_MAX_DATA(n_count, p_ch_min,p_ch_max, cur_sec);
				}
			}

			// ...
			{
				SCX__TIMER_CTRL x_timer_ctrl;
				x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
				x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH__CYCLE_TEST_CUR_DELAY_SEC->Get__CHANNEL_NAME());

				aCH__CYCLE_TEST_CFG_DELAY_SEC->Get__DATA(var_data);
				double cfg_sec = atof(var_data);

				if(x_timer_ctrl->WAIT(cfg_sec) < 0)
				{
					return -201;
				}
			}

			// ...
		}
	}

	return 1;
}

CString CObj__LBx_TEST::
Get__AVG_DATA(const int n_count,
			  const double cur_data,
			  const double pre_avg)
{
	double cur_avg = (pre_avg * ((n_count-1) / ((double) n_count))) + (cur_data / n_count); 

	CString str_data;
	str_data.Format("%.3f", cur_avg);

	return str_data;	
}
void CObj__LBx_TEST::
Fnc__Check_MIN_MAX_DATA(const int n_count,
						CII__VAR_STRING_CTRL* p_ch_min,
						CII__VAR_STRING_CTRL* p_ch_max,
						const double cur_data)
{
	CString var_data;

	if(n_count == 1)
	{
		var_data.Format("%.2f", cur_data);

		p_ch_min->Set__DATA(var_data);
		p_ch_max->Set__DATA(var_data);
	}
	else
	{
		double min_data;
		double max_data;

		p_ch_min->Get__DATA(var_data);
		min_data = atof(var_data);

		p_ch_max->Get__DATA(var_data);
		max_data = atof(var_data);

		if(cur_data < min_data)
		{
			var_data.Format("%.2f", cur_data);
			p_ch_min->Set__DATA(var_data);
		}
		if(cur_data > max_data)
		{
			var_data.Format("%.2f", cur_data);
			p_ch_max->Set__DATA(var_data);
		}
	}	
}
