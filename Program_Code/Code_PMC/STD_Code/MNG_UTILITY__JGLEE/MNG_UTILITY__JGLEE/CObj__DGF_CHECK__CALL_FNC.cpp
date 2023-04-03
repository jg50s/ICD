#include "StdAfx.h"
#include "CObj__DGF_CHECK.h"

#include "CCommon_Def.h"


extern void Macro__Get_Date(CString& date, CString& time);


// ...
int CObj__DGF_CHECK::
Call__COPY_NEW_TO_BASELINE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;
	int i;

	for(i=0;i<CFG__TEST_LIST;i++)
	{
		ch_data = sCH_PARA__NEW_RESULT_mTORR_LIST[i]->Get__STRING();
		aCH_CFG__BASELINE_mTORR[i]->Set__DATA(ch_data);
	}

	return 1;
}

int CObj__DGF_CHECK::
Call__ORIFICE_CHECK(CII_OBJECT__VARIABLE *p_variable,
					CII_OBJECT__ALARM *p_alarm)
{	
	// ...
	{
		CString var_data;
		int i;

		for(i=0;i<CFG__TEST_LIST;i++)
		{
			// New List
			sCH_PARA__NEW_RESULT_mTORR_LIST[i]->Set__DATA("");

			sCH_PARA__NEW_RESULT_START_mTORR_LIST[i]->Set__DATA("");
			sCH_PARA__NEW_RESULT_END_mTORR_LIST[i]->Set__DATA("");

			// Delta List
			sCH_PARA__DELTA_RESULT_mTORR_LIST[i]->Set__DATA("");
			sCH_PARA__DELTA_RESULT_PER_LIST[i]->Set__DATA("");
		}

		sCH_PARA__TEST_DATE->Set__DATA("");
		sCH_PARA__TEST_TIME->Set__DATA("");
	}

	xCH__AUTO_START_CTRL->Set__DATA("START");

	int flag = Fnc__ORIFICE_CHECK(p_variable,p_alarm);

	xCH__AUTO_START_CTRL->Set__DATA("STOP");

	// ...
	{
		CString str_msg;
		CString msg;

		//
		{
			str_msg = "MFC All Closed ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("Orifice Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			//
			pOBJ_CTRL__GAS_VLV->Dislink__UPPER_OBJECT();
			pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__ALL_CLOSE);
			pOBJ_CTRL__GAS_VLV->Link__UPPER_OBJECT();
		}

		//
		{
			str_msg = "DGF All Closed ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("Orifice Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			//
			pOBJ_CTRL__DGF->Dislink__UPPER_OBJECT();
			pOBJ_CTRL__DGF->Call__OBJECT(CMMD_MODE__DGF_ALL_CLOSE);
			pOBJ_CTRL__DGF->Link__UPPER_OBJECT();
		}

		//
		{
			str_msg = "High VAC Pumping Started ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("Orifice Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			//
			pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();
			pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP);
			pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
		}
	}

	// ...
	{
		CString str_date;
		CString str_time;

		Macro__Get_Date(str_date,str_time);

		sCH_PARA__TEST_DATE->Set__DATA(str_date);
		sCH_PARA__TEST_TIME->Set__DATA(str_time);
	}

	return flag;
}

int CObj__DGF_CHECK::
Fnc__ORIFICE_CHECK(CII_OBJECT__VARIABLE *p_variable,
				   CII_OBJECT__ALARM *p_alarm)
{	
	sCH_RESULT__START_PRESSURE_mTORR->Set__DATA("");
	sCH_RESULT__END_PRESSURE_mTORR->Set__DATA("");

	// ...
	int flag;
	int i;

	if(dCH_CFG__TEST_ORDER->Check__DATA(STR__BOTTOM_TO_UP) > 0)
	{
		for(i=0;i<CFG__TEST_LIST;i++)
		{
			flag = Fnc__LOWER_ORIFICE_CHECK(p_variable,p_alarm,i);
			if(flag < 0)		return flag;
		
			// ...
			{
				if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__ALL_CLOSE) < 0)
				{
					return -1;
				}

				if(pOBJ_CTRL__DGF->Call__OBJECT(CMMD_MODE__DGF_ALL_CLOSE) < 0)
				{
					return -1;
				}
			}
		}
	}
	else
	{
		for(i=CFG__TEST_LIST-1;i>=0;i--)
		{
			flag = Fnc__LOWER_ORIFICE_CHECK(p_variable,p_alarm,i);
			if(flag < 0)		return flag;		

			// ...
			{
				if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__ALL_CLOSE) < 0)
				{
					return -1;
				}

				if(pOBJ_CTRL__DGF->Call__OBJECT(CMMD_MODE__DGF_ALL_CLOSE) < 0)
				{
					return -1;
				}
			}
		}
	}

	return 1;
}
int CObj__DGF_CHECK::
Fnc__LOWER_ORIFICE_CHECK(CII_OBJECT__VARIABLE *p_variable,
						 CII_OBJECT__ALARM *p_alarm,
						 const int db_index)
{
	CString var_data;
	CString str_msg;
	CString msg;


	// 1. Base Pumping
	{
		str_msg = "High VAC - Pumping Started ...";
		xCH__OBJ_MSG->Set__DATA(str_msg);

		msg.Format("Orifice Check : %s",str_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);

		//
		if(pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP) < 0)
		{
			str_msg = "High VAC - Pumping Aborted ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("Orifice Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -1;
		}

		// ...
		{
			SCX__TIMER_CTRL x_timer_ctrl;

			x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
			x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH_PARA__CHECK_TIME_COUNT->Get__CHANNEL_NAME());

			//
			str_msg = "Pumping Delay Started ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("Orifice Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			//
			aCH_CFG__PUMPING_DELAY_SEC->Get__DATA(var_data);
			double cfg__delay_sec = atof(var_data);

			if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
			{
				str_msg = "Pumping Delay Aborted ...";
				xCH__OBJ_MSG->Set__DATA(str_msg);

				msg.Format("Orifice Check : %s",str_msg);
				sEXT_CH__FNC_MSG->Set__DATA(msg);
				return -11;
			}
		}
	}

	// 2. MFC Flow
	{	
		CString gas_name;
		CString gas_flow;

		if((db_index >= 0)&&(db_index <= 2))
		{
			dCH_CFG__LOW_FLOW_GAS_NAME->Get__DATA(gas_name);
			aCH_CFG__LOW_FLOW_GAS_SET->Get__DATA(gas_flow);
		}
		else
		{
			dCH_CFG__HIGH_FLOW_GAS_NAME->Get__DATA(gas_name);
			aCH_CFG__HIGH_FLOW_GAS_SET->Get__DATA(gas_flow);
		}

		//
		dEXT_CH__GAS_VLV__PARA_MFC_TYPE->Set__DATA(gas_name);
		aEXT_CH__GAS_VLV__PARA_MFC_FLOW->Set__DATA(gas_flow);

		//
		{
			str_msg.Format("MFC Control - Started : (%s) <- (%s)", gas_name,gas_flow);
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("Orifice Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		dEXT_CH__GAS_VLV__PARA_INTERLOCK_SKIP->Set__DATA(STR__YES);
		if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__MFC_CONTROL) < 0)
		{
			str_msg = "MFC Control - Aborted ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("Orifice Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -2;
		}

		//
		str_msg = "MFC Control - Completed ...";
		xCH__OBJ_MSG->Set__DATA(str_msg);

		msg.Format("Orifice Check : %s",str_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);
	}

	// 3. Orifice Open
	{
		str_msg = "Orifice Valve Control - Started ...";
		xCH__OBJ_MSG->Set__DATA(str_msg);

		msg.Format("Orifice Check : %s",str_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);

		//
		CString vlv_name;

		vlv_name.Format("VLV%1d", db_index+1);
		dEXT_CH__PARA_ORIFICE_VLV->Set__DATA(vlv_name);

		if(pOBJ_CTRL__DGF->Call__OBJECT(CMMD_MODE__DGF_ORIFICE_CTRL) < 0)
		{
			str_msg = "Orifice Valve Control - Aborted ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("Orifice Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -3;
		}
	}

	// 4. Pressure Stable Time
	{
		SCX__TIMER_CTRL x_timer_ctrl;

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH_PARA__CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		double cfg__delay_sec;
		aCH_CFG__STABLE_DELAY_SEC->Get__DATA(var_data);
		cfg__delay_sec = atof(var_data);

		//
		{
			str_msg.Format("Pressure Stable Time - (%s) sec", var_data);
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("Orifice Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			str_msg = "Pressure Stable Time - Aborted ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("Orifice Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -4;
		}

		//
		{
			sEXT_CH__PRESSURE->Get__DATA(var_data);			
			double cur__press_torr  = atof(var_data);
			double cur__press_mtorr = cur__press_torr * 1000.0;

			var_data.Format("%.0f", cur__press_mtorr);
			sCH_RESULT__START_PRESSURE_mTORR->Set__DATA(var_data);

			sCH_RESULT__END_PRESSURE_mTORR->Set__DATA("");
		}
	}

	// 5. Check Delay Time
	{
		SCX__TIMER_CTRL x_timer_ctrl;

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH_PARA__CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		double cfg__delay_sec;
		aCH_CFG__CHECK_DELAY_SEC->Get__DATA(var_data);
		cfg__delay_sec = atof(var_data);

		//
		{
			str_msg.Format("Check Delay Time Started ... (%s) sec", var_data);
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("Orifice Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			str_msg = "Check Delay Time Aborted ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("Orifice Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -5;
		}

		if(iActive__SIM_MODE > 0)
		{
			aCH_CFG__BASELINE_mTORR[db_index]->Get__DATA(var_data);
			sCH_RESULT__END_PRESSURE_mTORR->Set__DATA(var_data);
		}
		else
		{
			sEXT_CH__PRESSURE->Get__DATA(var_data);
			double cur__press_torr  = atof(var_data);
			double cur__press_mtorr = cur__press_torr * 1000.0;
			
			var_data.Format("%.0f", cur__press_mtorr);
			sCH_RESULT__END_PRESSURE_mTORR->Set__DATA(var_data);
		}
	}

	// 6. Result Check
	{
		double new_value;
		double base_value;

		double s_press_mtorr = 0;
		double e_press_mtorr = 0;

		// Start.Pressure
		sCH_RESULT__START_PRESSURE_mTORR->Get__DATA(var_data);
		s_press_mtorr = atof(var_data);

		var_data.Format("%.0f", s_press_mtorr);
		sCH_PARA__NEW_RESULT_START_mTORR_LIST[db_index]->Set__DATA(var_data);

		// End.Pressure
		sCH_RESULT__END_PRESSURE_mTORR->Get__DATA(var_data);
		e_press_mtorr = atof(var_data);

		var_data.Format("%.0f", e_press_mtorr);
		sCH_PARA__NEW_RESULT_END_mTORR_LIST[db_index]->Set__DATA(var_data);

		// New
		new_value = e_press_mtorr - s_press_mtorr;
		var_data.Format("%.0f", new_value);
		sCH_PARA__NEW_RESULT_mTORR_LIST[db_index]->Set__DATA(var_data);

		// Delta  = (Baseline - New)
		aCH_CFG__BASELINE_mTORR[db_index]->Get__DATA(var_data);
		base_value = atof(var_data);

		//
		double delta_value = (base_value - new_value);
		if(delta_value < 0)		delta_value = -delta_value;

		var_data.Format("%.0f", delta_value);
		sCH_PARA__DELTA_RESULT_mTORR_LIST[db_index]->Set__DATA(var_data);

		//
		double err_per = 0.0;

		if(base_value > 0)
		{	
			err_per = (delta_value / base_value) * 100.0;
		}

		var_data.Format("%.1f", err_per);
		sCH_PARA__DELTA_RESULT_PER_LIST[db_index]->Set__DATA(var_data);

		//
		double cfg_err = aCH_CFG__BASELINE_TOLERANCE->Get__VALUE();

		if(err_per > cfg_err)
		{
			int alarm_id = ALID__BASELINE_TOLERANCE_ERROR;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
			return -1;
		}
	}

	return 1;
}
