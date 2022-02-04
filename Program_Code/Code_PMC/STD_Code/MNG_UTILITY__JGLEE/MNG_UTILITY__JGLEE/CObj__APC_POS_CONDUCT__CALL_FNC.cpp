#include "StdAfx.h"
#include "CObj__APC_POS_CONDUCT.h"


extern void Macro__Get_Date(CString& date, CString& time);


//-------------------------------------------------------------------------
int CObj__APC_POS_CONDUCT::
Call__POS_CONDUCT(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{	
	printf(" * CObj__APC_POS_CONDUCT::Call__POS_CONDUCT() - Start \n");

	// ...
	{
		int i;

		for(i=0;i<CFG__TEST_LIST;i++)
		{
			sCH_PARA__CONDUCT_RESULT[i]->Set__DATA("");
		}

		sCH_PARA__TEST_DATE->Set__DATA("");
		sCH_PARA__TEST_TIME->Set__DATA("");
		sCH__RESULT_STRING->Set__DATA("");
	}

	// ...
	xCH__AUTO_START_CTRL->Set__DATA("START");

	int flag = Fnc__POS_CONDUCT(p_variable,p_alarm);

	xCH__AUTO_START_CTRL->Set__DATA("STOP");

	// ...
	{
		CString str_date;
		CString str_time;

		Macro__Get_Date(str_date,str_time);

		sCH_PARA__TEST_DATE->Set__DATA(str_date);
		sCH_PARA__TEST_TIME->Set__DATA(str_time);
	}

	// ...
	{
		sEXT_CH__FNC_MSG->Set__DATA("APC Conduct : MFC All Close ...");

		//
		pOBJ_CTRL__GAS_VLV->Dislink__UPPER_OBJECT();

		aEXT_CH__GAS_VLV__PARA_MFC_FLOW->Set__DATA("0");
		pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__MFC_CONTROL);
		pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__ALL_CLOSE);

		pOBJ_CTRL__GAS_VLV->Link__UPPER_OBJECT();
	}

	// ...
	{
		sEXT_CH__FNC_MSG->Set__DATA("APC Conduct : High VAC Pumping ...");

		//
		pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();

		pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP);

		pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
	}

	return flag;
}

int CObj__APC_POS_CONDUCT::
Fnc__POS_CONDUCT(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm)
{	
	CString gas_name;
	CString gas_flow;
	CString vlv_pos;
	CString var_data;

	int flag;
	int i;

	if(dCH_CFG__TEST_ORDER->Check__DATA(STR__BOTTOM_TO_UP) > 0)
	{
		for(i=0;i<CFG__TEST_LIST;i++)
		{
			aCH_PARA__VLV_POS_LIST[i]->Get__DATA(vlv_pos);
			dCH_PARA__TEST_GAS_TYPE->Get__DATA(gas_name);
			aCH_PARA__TEST_GAS_FLOW->Get__DATA(gas_flow);

			flag = Fnc__LOWER_POS_CONDUCT(p_variable,p_alarm,vlv_pos,gas_name,gas_flow,i);
			if(flag < 0)	return flag;
		}
	}
	else
	{
		for(i=CFG__TEST_LIST-1;i>=0;i--)
		{
			aCH_PARA__VLV_POS_LIST[i]->Get__DATA(vlv_pos);
			dCH_PARA__TEST_GAS_TYPE->Get__DATA(gas_name);
			aCH_PARA__TEST_GAS_FLOW->Get__DATA(gas_flow);

			flag = Fnc__LOWER_POS_CONDUCT(p_variable,p_alarm,vlv_pos,gas_name,gas_flow,i);
			if(flag < 0)	return flag;
		}
	}
	return 1;
}
int CObj__APC_POS_CONDUCT::
Fnc__LOWER_POS_CONDUCT(CII_OBJECT__VARIABLE *p_variable,
					   CII_OBJECT__ALARM *p_alarm,
					   const CString& vlv_pos,
					   const CString& gas_name,
					   const CString& gas_flow,
					   const int db_index)
{
	printf(" * CObj__APC_POS_CONDUCT::Fnc__LOWER_POS_CONDUCT() - Start \n");

	CString var_data;
	CString str_msg;
	CString msg;

	// 1. Base Pumping
	if(db_index == 0)
	{
		xCH__OBJ_MSG->Set__DATA("High VAC - Pumping Started ...");
		sEXT_CH__FNC_MSG->Set__DATA("APC Conduct : High VAC Pumping Started ...");

		if(pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP) < 0)
		{
			xCH__OBJ_MSG->Set__DATA("High VAC - Pumping Aborted ...");
			sEXT_CH__FNC_MSG->Set__DATA("APC Conduct : High VAC Pumping Aborted ...");
			return -1;
		}
	}

	// 2. MFC Flow
	{	
		dEXT_CH__GAS_VLV__PARA_MFC_TYPE->Set__DATA(gas_name);
		aEXT_CH__GAS_VLV__PARA_MFC_FLOW->Set__DATA(gas_flow);

		//
		{
			str_msg.Format("MFC Control - Started : (%s) <- (%s)", gas_name,gas_flow);
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("APC Conduct : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__MFC_CONTROL) < 0)
		{
			str_msg = "MFC Control - Aborted ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("APC Conduct : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			return -2;
		}

		//
		str_msg = "MFC Control - Completed ...";
		xCH__OBJ_MSG->Set__DATA(str_msg);

		msg.Format("APC Conduct : %s", str_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);
	}

	// 3. Flow Delay Sec
	{
		SCX__TIMER_CTRL x_timer_ctrl;

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH__CUR_CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		double cfg__delay_sec;
		aCH_CFG__FLOW_DELAY_SEC->Get__DATA(var_data);
		cfg__delay_sec = atof(var_data);

		//
		{
			str_msg.Format("Flow Delay - Started ...  (%s) sec", var_data);
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("APC Conduct : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			str_msg = "Flow Delay - Aborted ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("APC Conduct : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -3;
		}
	}

	// 4. VAT Ctrl
	{
		xCH__OBJ_MSG->Set__DATA("APC Control - Started ...");

		double set_pos = atof(vlv_pos) / 10.0;
		aEXT_CH__PARA_VLV_POS_DATA->Set__VALUE(set_pos);

		if(pOBJ_CTRL__VAT->Call__OBJECT(CMMD_MODE__VAT_POSITION) < 0)
		{
			str_msg = "APC Control - Aborted ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("APC Conduct : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -4;
		}

		//
		str_msg = "APC Control - Completed ...";
		xCH__OBJ_MSG->Set__DATA(str_msg);

		msg.Format("APC Conduct : %s", str_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);
	}

	// ...
	double set__vlv_pos = atof(vlv_pos);

	// 5. Pressure Stable Time
	if(set__vlv_pos > 0)
	{
		SCX__TIMER_CTRL x_timer_ctrl;

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH__CUR_CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		double cfg__delay_sec;
		aCH_CFG__PRESSURE_STABLE_DELAY_SEC->Get__DATA(var_data);
		cfg__delay_sec = atof(var_data);

		//
		{
			str_msg.Format("Pressure Stable Time - (%s) sec", var_data);
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("APC Conduct : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			str_msg.Format("Pressure Stable Time - Aborted ...");
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("APC Conduct : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -5;
		}
	}

	// 6. Result Check
	if(set__vlv_pos > 0)
	{
		double cur_result = 0.0;
		double cur_press;
		double cur_flow = atof(gas_flow);

		// Pressure
		sEXT_CH__CHM_PRESSURE->Get__DATA(var_data);
		cur_press = atof(var_data) * 1000.0;   // torr -> mtorr

		// Result
		if(cur_press > 0)
		{
			cur_result = cur_flow / cur_press;
			var_data.Format("%.6f", cur_result);
			sCH_PARA__CONDUCT_RESULT[db_index]->Set__DATA(var_data);
		}
		else
		{
			sCH_PARA__CONDUCT_RESULT[db_index]->Set__DATA("***");
		}

		//
		CString cur_data;
		CString add_data;

		add_data.Format("%.1f/%.1f,", atof(vlv_pos), cur_result);

		sCH__RESULT_STRING->Get__DATA(cur_data);
		cur_data += add_data;
		sCH__RESULT_STRING->Set__DATA(cur_data);
	}
	else
	{
		// Result
		sCH_PARA__CONDUCT_RESULT[db_index]->Set__DATA("0.0");

		//
		CString cur_data;
		CString add_data;

		add_data = "0.0/0.0,";

		sCH__RESULT_STRING->Get__DATA(cur_data);
		cur_data += add_data;
		sCH__RESULT_STRING->Set__DATA(cur_data);
	}

	// ...
	{
		CString str__check_type = dCH__CFG_CHECK_TYPE->Get__STRING();
		int type_index = -1;

		if(str__check_type.CompareNoCase(STR__Ar_80)   == 0)			type_index = _TEST_TYPE__INDEX_AR;
		if(str__check_type.CompareNoCase(STR__N2_5PER) == 0)			type_index = _TEST_TYPE__INDEX_N2;
		if(str__check_type.CompareNoCase(STR__User_Define) == 0)		type_index = _TEST_TYPE__INDEX_USER;

		if(type_index >= 0)
		{
			sCH_PARA__CONDUCT_RESULT[db_index]->Get__DATA(var_data);
			sCH_PARA__CONDUCT_RESULT_OF_TYPE[type_index][db_index]->Set__DATA(var_data);
		}
	}

	printf(" * CObj__APC_POS_CONDUCT::Fnc__LOWER_POS_CONDUCT() - End \n");
	return 1;
}
