#include "StdAfx.h"
#include "CObj__ManiFold_TEST.h"
#include "CObj__ManiFold_TEST__DEF.h"



// ...
int  CObj__ManiFold_TEST::
Call__PUMPING_CYCLE_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;
	int i;

	// Initial ...
	{
		aCH__CYCLE_TEST_CFG_COUNT_ALL->Get__DATA(ch_data);
		sCH__CYCLE_TEST_CUR_COUNT_ALL->Set__DATA(ch_data);

		for(i=0; i<iMD_SIZE; i++)
		{
			dCH__CYCLE_TEST_CFG_ACTIVE_X[i]->Get__DATA(ch_data);
			sCH__CYCLE_TEST_CUR_ACTIVE_X[i]->Set__DATA(ch_data);

			sCH__CYCLE_TEST_CUR_COUNT_X[i]->Set__DATA("");

			dCH__CYCLE_TEST_CFG_VENT_X[i]->Get__DATA(ch_data);
			sCH__CYCLE_TEST_CUR_VENT_X[i]->Set__DATA(ch_data);
		}
	}

	// 
	ch_data = sCH__CYCLE_TEST_CUR_COUNT_ALL->Get__STRING();
	int ref_count = atoi(ch_data);

	// Test ...
	while(ref_count > 0)
	{
		ref_count--;
		
		if(p_variable->Check__CTRL_ABORT() > 0)			return -1;

		// Venting : Start ...
		for(i=0; i<iMD_SIZE; i++)
		{
			if(sCH__CYCLE_TEST_CUR_ACTIVE_X[i]->Check__DATA("YES") < 0)			continue;
			if(sCH__CYCLE_TEST_CUR_VENT_X[i]->Check__DATA("YES")   < 0)			continue;

			// ...
			CII_EXT_OBJECT__CTRL *p_obj_ctrl = pOBJ_CTRL__MD_FNC_X[i];

			if(dEXT_CH__MD_OBJ_STATUS_X[i]->Check__DATA(STR__MAINTMODE) < 0)
			{
				int alm_id = ALID__MD_X__STATUS_IS_NOT_MAINT + i;
				CString alm_msg;
				CString r_act;

				alm_msg.Format("The state of %s is not \"MAINTMODE\". ", sMD_NAME_X[i]);

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);	
				return -111;
			}

			if(p_obj_ctrl->Run__OBJECT("VENT") < 0)
			{
				return -121;
			}
		}
		// Venting : Wait ...
		for(i=0; i<iMD_SIZE; i++)
		{
			if(sCH__CYCLE_TEST_CUR_ACTIVE_X[i]->Check__DATA("YES") < 0)			continue;
			if(sCH__CYCLE_TEST_CUR_VENT_X[i]->Check__DATA("YES")   < 0)			continue;

			// ...
			CII_EXT_OBJECT__CTRL *p_obj_ctrl = pOBJ_CTRL__MD_FNC_X[i];

			if(p_obj_ctrl->When__OBJECT() < 0)
			{
				return -122;
			}
		}

		if(p_variable->Check__CTRL_ABORT() > 0)			return -1;

		// Pumping : Start ...
		for(i=0; i<iMD_SIZE; i++)
		{
			if(sCH__CYCLE_TEST_CUR_ACTIVE_X[i]->Check__DATA("YES") < 0)			continue;

			// ...
			CII_EXT_OBJECT__CTRL *p_obj_ctrl = pOBJ_CTRL__MD_FNC_X[i];

			if(dEXT_CH__MD_OBJ_STATUS_X[i]->Check__DATA(STR__MAINTMODE) < 0)
			{
				int alm_id = ALID__MD_X__STATUS_IS_NOT_MAINT + i;
				CString alm_msg;
				CString r_act;

				alm_msg.Format("The state of %s is not \"MAINTMODE\". ", sMD_NAME_X[i]);

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);	
				return -11;
			}

			if(p_obj_ctrl->Run__OBJECT("PUMP") < 0)
			{
				return -21;
			}
		}
		// Pumping : Wait ...
		for(i=0; i<iMD_SIZE; i++)
		{
			if(sCH__CYCLE_TEST_CUR_ACTIVE_X[i]->Check__DATA("YES") < 0)			continue;

			// ...
			CII_EXT_OBJECT__CTRL *p_obj_ctrl = pOBJ_CTRL__MD_FNC_X[i];

			if(p_obj_ctrl->When__OBJECT() < 0)
			{
				return -22;
			}

			// ...
			{
				ch_data = sCH__CYCLE_TEST_CUR_COUNT_X[i]->Get__STRING();
				int cur_count = atoi(ch_data) + 1;
				ch_data.Format("%1d", cur_count);
				sCH__CYCLE_TEST_CUR_COUNT_X[i]->Set__DATA(ch_data);
			}
		}
	}

	return 1;
}

CString CObj__ManiFold_TEST::
Get__AVG_DATA(const int n_count,
			  const double cur_data,
			  const double pre_avg)
{
	double cur_avg = (pre_avg * ((n_count-1) / ((double) n_count))) + (cur_data / n_count); 

	CString str_data;
	str_data.Format("%.3f", cur_avg);

	return str_data;	
}
void CObj__ManiFold_TEST::
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
