#include "StdAfx.h"
#include "CObj__FRC_CHECK.h"


extern void Macro__Get_Date(CString& date, CString& time);


//-------------------------------------------------------------------------
int CObj__FRC_CHECK
::Call__FLOW_TEST(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{	
	xCH__OBJ_MSG->Set__DATA("Chamber Pumping ...");

	// CHM : PUMPING ...
	if(pOBJ_CTRL__CHM->Call__OBJECT("PUMPING") < 0)
	{
		return -11;
	}

	xCH__OBJ_MSG->Set__DATA("Gas Line Ready ...");

	// GAS_VLV : PROC_READY ...
	if(pOBJ_CTRL__GAS_VLV->Call__OBJECT("PROC_READY") < 0)
	{
		return -12;		
	}

	xCH__OBJ_MSG->Set__DATA("MFC Control ...");

	// MFC : CONTROL ...
	{
		CString ch_data = dCH_PARA__TEST_GAS_TYPE->Get__STRING();

		int db_index = Get__Gas_Type_Index(ch_data);
		if(db_index < 0)		return -13;

		double cfg_flow = aCH_PARA__TEST_GAS_FLOW->Get__VALUE();

		aEXT_CH__MFCx_PARA_SET_FLOW[db_index]->Set__VALUE(cfg_flow);
		pOBJ_CTRL__MFC_X[db_index]->Call__OBJECT("CONTROL");
	}

	int flag = Fnc__FLOW_TEST(p_variable,p_alarm);

	// CHM : PUMPING ...
	{
		pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();

		pOBJ_CTRL__CHM->Call__OBJECT("PUMPING");

		pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
	}
	return flag;
}

int CObj__FRC_CHECK
::Fnc__FLOW_TEST(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm)
{	
	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -1;
	}

	// ...
	{
		CString str_date;
		CString str_time;

		Macro__Get_Date(str_date,str_time);

		sCH__LAST_TEST_DATE->Set__DATA(str_date);
		sCH__LAST_TEST_TIME->Set__DATA(str_time);
	}

	// Test Initial ...
	{
		CString var_data;
		int i;

		for(i=0; i<CFG_FRC__TEST_LIST; i++)
		{
			sCH__TEST_CH1_NEW_X[i]->Set__DATA("?");
			sCH__TEST_CH2_NEW_X[i]->Set__DATA("?");
			sCH__TEST_RATE_NEW_X[i]->Set__DATA("?");

			sCH__TEST_RESULT_ERROR_X[i]->Set__DATA("?");
			sCH__TEST_RESULT_PASS_X[i]->Set__DATA("?");
		}

		aCH_CFG__CHECK_ERROR_PERCENT->Get__DATA(var_data);
		sCH__CUR_CHECK_ERROR_PERCENT->Set__DATA(var_data);

		sCH__RESULT_STRING->Set__DATA("");
	}

	// ...
	{
		SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
		x_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH__CUR_CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		CString var_data;
		int i;

		for(i=0; i<CFG_FRC__TEST_LIST; i++)
		{
			var_data.Format("%1d Line Testing ...", i+1);
			xCH__OBJ_MSG->Set__DATA(var_data);

			sCH__CFG_CH1_RATE_X[i]->Get__DATA(var_data);
			double ch1_rate = atof(var_data);

			sCH__CFG_CH2_RATE_X[i]->Get__DATA(var_data);
			double ch2_rate = atof(var_data);

			aEXT_CH__CH1_RATIO_SET->Set__VALUE(ch1_rate);
			aEXT_CH__CH2_RATIO_SET->Set__VALUE(ch2_rate);

			double sec_stable = aCH_CFG__FLOW_STABLE_SEC->Get__VALUE();
			x_timer_ctrl->STOP_ZERO();
			x_timer_ctrl->START__COUNT_UP(9999);

			while(1)
			{
				if(p_variable->Check__CTRL_ABORT() > 0)
				{
					return -2;
				}

				if(x_timer_ctrl->Get__CURRENT_TIME() >= sec_stable)
				{
					break;
				}
			}

			// ...
			aEXT_CH__CH1_RATIO_SET->Get__DATA(var_data);
			sCH__TEST_CH1_NEW_X[i]->Set__DATA(var_data);
			ch1_rate = atof(var_data);

			aEXT_CH__CH2_RATIO_SET->Get__DATA(var_data);
			sCH__TEST_CH2_NEW_X[i]->Set__DATA(var_data);
			ch2_rate = atof(var_data);

			if(ch2_rate < 0.001)		ch2_rate = 0.001;
			var_data.Format("%.3f", ch1_rate/ch2_rate);
			sCH__TEST_RATE_NEW_X[i]->Set__DATA(var_data);

			// ...
			sCH__TEST_RATE_NEW_X[i]->Get__DATA(var_data);
			double new_ratio = atof(var_data);

			sCH__TEST_RATE_REF_X[i]->Get__DATA(var_data);
			double ref_ratio = atof(var_data);

			double err_ratio = new_ratio - ref_ratio;
			var_data.Format("%.3f", err_ratio);
			sCH__TEST_RESULT_ERROR_X[i]->Set__DATA(var_data);

			sCH__CUR_CHECK_ERROR_PERCENT->Get__DATA(var_data);
			double err_per = atof(var_data) / 100.0;
			double err_max = err_per * ref_ratio;
			double err_min = -err_max;

			if((err_ratio > err_max) || (err_ratio < err_min))
				sCH__TEST_RESULT_PASS_X[i]->Set__DATA("ERROR");
			else
				sCH__TEST_RESULT_PASS_X[i]->Set__DATA("OK");

			// ...
			CString str_result = sCH__RESULT_STRING->Get__STRING();
			var_data.Format("%1d/%s,", i+1,sCH__TEST_RATE_NEW_X[i]->Get__STRING());
			str_result += var_data;
			sCH__RESULT_STRING->Set__DATA(str_result);
		}
	}

	return 1;
}
