#include "StdAfx.h"
#include "CObj__LBx_OneManiFold.h"
#include "CObj__LBx_OneManiFold__DEF.h"


// ...
int  CObj__LBx_OneManiFold
::Check__OBJECT_BUSY(const CString& obj_sts)
{
	if(obj_sts.CompareNoCase(STR__AVAILABLE) == 0)		return -1;
	if(obj_sts.CompareNoCase(STR__ABORTED) == 0)		return -1;
	if(obj_sts.CompareNoCase(STR__IDLE) == 0)			return -1;

	return 1;
}

int  CObj__LBx_OneManiFold
::_Update__ACTION_AVG_MIN_MAX(const int db_i,
							  const double cur_sec,
							  const int n_count)
{
	CII__VAR_STRING_CTRL* p_ch_now = sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_CUR[db_i].Get__PTR();
	CII__VAR_STRING_CTRL* p_ch_avg = sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_AVG[db_i].Get__PTR();
	CII__VAR_STRING_CTRL* p_ch_min = sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_MIN[db_i].Get__PTR();
	CII__VAR_STRING_CTRL* p_ch_max = sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_MAX[db_i].Get__PTR();

	CString ch_data;
	CString str_cur;

	// Now ...
	{
		str_cur.Format("%.1f", cur_sec);
		p_ch_now->Set__DATA(str_cur);
	}
	// Avg ...
	{
		ch_data = p_ch_avg->Get__STRING();

		if(ch_data.GetLength() < 1)
		{
			p_ch_avg->Set__DATA(str_cur);
		}
		else
		{
			double pre_ratio = (n_count - 1.0) / (double) n_count;
			double now_ratio = 1.0 / (double) n_count;

			double pre_avg = atof(ch_data);
			double cur_avg = (pre_avg * pre_ratio) + (cur_sec * now_ratio);

			ch_data.Format("%.1f", cur_avg);
			p_ch_avg->Set__DATA(ch_data);
		}
	}
	// Min ...
	{
		ch_data = p_ch_min->Get__STRING();

		if(ch_data.GetLength() < 1)
		{
			p_ch_min->Set__DATA(str_cur);
		}
		else
		{
			double cur_min = atof(ch_data);

			if(cur_sec < cur_min)		p_ch_min->Set__DATA(str_cur);
		}
	}
	// Max ...
	{
		ch_data = p_ch_max->Get__STRING();

		if(ch_data.GetLength() < 1)
		{
			p_ch_max->Set__DATA(str_cur);
		}
		else
		{
			double cur_max = atof(ch_data);

			if(cur_sec > cur_max)		p_ch_max->Set__DATA(str_cur);
		}
	}

	return 1;
}
