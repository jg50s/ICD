#include "StdAfx.h"
#include "CObj__MFC_FLOW_CHECK.h"


extern void Macro__Get_Date(CString& date, CString& time);
extern int  Macro__Check_1Point(const CString& str_data, int& check_percent);


//-------------------------------------------------------------------------
int CObj__MFC_FLOW_CHECK::
Call__PARTIAL_PRESSURE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	Fnc__INIT_PARAMETER(CHECK_MODE__PARTIAL_PRESSURE);

	int flag = Fnc__PARTIAL_CHECK(p_variable,p_alarm);

	// ...
	{
		sEXT_CH__FNC_MSG->Set__DATA("Partial Pressure : All MFC Close ...");

		pOBJ_CTRL__GAS_VLV->Dislink__UPPER_OBJECT();
		pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__ALL_CLOSE);
		pOBJ_CTRL__GAS_VLV->Link__UPPER_OBJECT();
	}

	// ...
	{
		sEXT_CH__FNC_MSG->Set__DATA("Partial Pressure : High VAC Pumping ...");
		xCH__OBJ_MSG->Set__DATA("High Vac Pumping Started ...");

		pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();
		pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP);
		pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
	}

	xCH__OBJ_MSG->Set__DATA("");
	return flag;
}

int CObj__MFC_FLOW_CHECK::
Call__MFC_CAL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	Fnc__INIT_PARAMETER(CHECK_MODE__MFC_CAL);

	int flag = Fnc__MFC_CAL_CHECK(p_variable,p_alarm);

	// ...
	{
		sEXT_CH__FNC_MSG->Set__DATA("MFC CAL. : All MFC Close ...");

		//
		pOBJ_CTRL__GAS_VLV->Dislink__UPPER_OBJECT();
		pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__ALL_CLOSE);
		pOBJ_CTRL__GAS_VLV->Link__UPPER_OBJECT();
	}

	// ...
	{
		sEXT_CH__FNC_MSG->Set__DATA("MFC CAL. : High VAC Pumping ...");
		xCH__OBJ_MSG->Set__DATA("High Vac Pumping Started ...");

		//
		pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();
		pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP);
		pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
	}

	xCH__OBJ_MSG->Set__DATA("");
	return flag;
}

int CObj__MFC_FLOW_CHECK::
Call__ALL_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	Fnc__INIT_PARAMETER(CHECK_MODE__ALL_CHECK);

	int flag = Fnc__ALL_CHECK(p_variable,p_alarm);

	// ...
	{
		sEXT_CH__FNC_MSG->Set__DATA("MFC ALL_CHECK : MFC All Close ...");

		//
		pOBJ_CTRL__GAS_VLV->Dislink__UPPER_OBJECT();
		pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__ALL_CLOSE);
		pOBJ_CTRL__GAS_VLV->Link__UPPER_OBJECT();
	}

	// ...
	{
		sEXT_CH__FNC_MSG->Set__DATA("MFC ALL_CHECK : High VAC Pumping ...");
		xCH__OBJ_MSG->Set__DATA("High Vac Pumping Started ...");

		//
		pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();
		pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP);
		pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
	}

	xCH__OBJ_MSG->Set__DATA("");
	return flag;
}

int CObj__MFC_FLOW_CHECK::
Fnc__INIT_PARAMETER(const int check_mode)
{
	int i;

	// ...
	{
		sCH_INFO__CUR_GAS_ID->Set__DATA("");
		sCH_INFO__CUR_GAS_NAME->Set__DATA("");
	
		sCH_PARA__CHECK_DATE->Set__DATA("");
		sCH_PARA__CHECK_TIME->Set__DATA("");

		sCH_PARA__CHECK_START_PRESSURE->Set__DATA("");
		sCH_PARA__CHECK_END_PRESSURE->Set__DATA("");
		sCH_PARA__CHECK_CAL_TIME->Set__DATA("");

		for(i=0;i<iSIZE__OBJ_MFCx;i++)
		{
			sCH_APP__GAS_STATUS[i]->Set__DATA("");
		}

		if((check_mode == CHECK_MODE__PARTIAL_PRESSURE)
		|| (check_mode == CHECK_MODE__ALL_CHECK))
		{
			for(i=0;i<CFG__GAS_FLOW_LIST;i++)
			{	
				sCH_PARA__CURRENT_PRESSURE[i]->Set__DATA("");
			}
		}
		
		if((check_mode == CHECK_MODE__MFC_CAL)
		|| (check_mode == CHECK_MODE__ALL_CHECK))
		{
			for(i=0;i<CFG__GAS_FLOW_LIST;i++)
			{	
				sCH_PARA__GAS_CURRENT_FLOW[i]->Set__DATA("");
				sCH_PARA__CAL_ERROR_RESULT[i]->Set__DATA("");
			}
		}
	}

	return 1;
}

int CObj__MFC_FLOW_CHECK::
Fnc__ALL_CHECK(CII_OBJECT__VARIABLE *p_variable,
			   CII_OBJECT__ALARM *p_alarm)
{
	CII_EXT_OBJECT__CTRL *p_obj_ctrl = NULL;
	CII__VAR_ANALOG_CTRL *p_mfc_flow_set = NULL;

	CString fnc_msg;
	CString var_data;
	CString msg;
	int flag;
	int i;

	for(i=0;i<iSIZE__OBJ_MFCx;i++)
	{
		if(dCH_APP__GAS_USE_FLAG[i]->Check__DATA(STR__YES) < 0)
		{
			continue;
		}
		else
		{
			CString szRun_Mode;

			dCH_PARA__MFC_SETTING_MODE->Get__DATA(szRun_Mode);
			sCH_APP__GAS_RUN_MODE[i]->Set__DATA(szRun_Mode);
		}
		
		//
		{
			fnc_msg.Format("List%1d - Started ...", i+1);
			sCH_INFO__LIST_CTRL->Set__DATA(fnc_msg);
			
			sCH_APP__GAS_STATUS[i]->Set__DATA("Start");	

			msg.Format("MFC ALL_CHECK : %s", fnc_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		//
		{
			CString msg;

			msg.Format("GAS%002d",i+1);
			sCH_INFO__CUR_GAS_ID->Set__DATA(msg);

			sEXT_CH__PARA_MFCx_GAS_NAME[i]->Get__DATA(var_data);
			sCH_INFO__CUR_GAS_NAME->Set__DATA(var_data);

			//
			CString str_min;
			CString str_max;

			aEXT_CH__PARA_MFCx_SET_FLOW[i]->Get__MIN_MAX_INFO(str_min,str_max);

			sCH_INFO__CUR_GAS_MIN->Set__DATA(str_min);
			sCH_INFO__CUR_GAS_MAX->Set__DATA(str_max);
		}

		//
		flag = Fnc__UPPER_ALL_CHECK(p_variable,p_alarm,i);
		if(flag < 0)
		{
			fnc_msg.Format("List%1d - Aborted ...", i+1);
			sCH_INFO__LIST_CTRL->Set__DATA(fnc_msg);

			sCH_APP__GAS_STATUS[i]->Set__DATA("Abort");

			msg.Format("MFC ALL_CHECK : %s", fnc_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			return flag;
		}

		//
		{
			CString str_date;
			CString str_time;
			
			Macro__Get_Date(str_date,str_time);

			sCH_PARA__CHECK_DATE->Set__DATA(str_date);
			sCH_PARA__CHECK_TIME->Set__DATA(str_time);
		}

		//
		{
			for(int j=0; j<CFG__GAS_FLOW_LIST; j++)
			{
				sCH_PARA__GAS_CURRENT_FLOW[j]->Get__DATA(var_data);
				sCH_RESULT__CURRENT_FLOW[i][j]->Set__DATA(var_data);

				sCH_PARA__CURRENT_PRESSURE[j]->Get__DATA(var_data);
				sCH_RESULT__CURRENT_PRESSURE[i][j]->Set__DATA(var_data);

				sCH_PARA__CAL_ERROR_RESULT[j]->Get__DATA(var_data);
				sCH_RESULT__CAL_ERROR[i][j]->Set__DATA(var_data);
			}

			//
			sCH_PARA__CHECK_DATE->Get__DATA(var_data);
			sCH_RESULT__CHECK_DATE[i]->Set__DATA(var_data);

			sCH_PARA__CHECK_TIME->Get__DATA(var_data);
			sCH_RESULT__CHECK_TIME[i]->Set__DATA(var_data);
		}

		sCH_APP__GAS_STATUS[i]->Set__DATA("Complete");
	}

	//
	{
		fnc_msg = "Partial Pressure Check - Completed ...";
		sCH_INFO__LIST_CTRL->Set__DATA(fnc_msg);

		msg.Format("MFC ALL_CHECK : %s", fnc_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);
	}

	return 1;
}
int CObj__MFC_FLOW_CHECK::
Fnc__UPPER_ALL_CHECK(CII_OBJECT__VARIABLE *p_variable,
					 CII_OBJECT__ALARM *p_alarm,
					 const int gas_index)
{
	CII_EXT_OBJECT__CTRL *p_obj_ctrl = NULL;
	CII__VAR_ANALOG_CTRL *p_mfc_flow_set = NULL;
	CII__VAR_ANALOG_CTRL *p_mfc_flow_get = NULL;

	CString gas_name;
	gas_name.Format("GAS%002d", gas_index+1);

	// ...
	{
		p_obj_ctrl = pOBJ_CTRL__MFCx[gas_index];
		p_mfc_flow_set = aEXT_CH__PARA_MFCx_SET_FLOW[gas_index].Get__PTR();
		p_mfc_flow_get = aEXT_CH__PARA_MFCx_GET_FLOW[gas_index].Get__PTR();
	}

	// ...
	{
		int flag;
		int i;

		for(i=0; i<CFG__GAS_FLOW_LIST; i++)
		{
			sCH_PARA__CURRENT_PRESSURE[i]->Set__DATA("");
			sCH_PARA__GAS_CURRENT_FLOW[i]->Set__DATA("");
		}


		for(i=0;i<CFG__GAS_FLOW_LIST;i++)
		{
			// Partial Pressure Check
			{
				flag = Fnc__LOWER_PARTIAL_CHECK(p_variable,
										        p_alarm,
										        p_obj_ctrl,
										        p_mfc_flow_set,
										        p_mfc_flow_get,
											    gas_name,
										        i);

				if(flag < 0)
				{
					return flag;	
				}

				pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__ALL_CLOSE);
			}

			// MFC CAL. Check
			{
				flag = Fnc__LOWER_MFC_CAL_CHECK(p_variable,
										        p_alarm,
										        p_obj_ctrl,
										        p_mfc_flow_set,
										        p_mfc_flow_get,
											    gas_name,
												gas_index,
										        i);

				if(flag < 0)
				{
					return flag;	
				}

				pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__ALL_CLOSE);
			}
		}
	}

	return 1;
}

int CObj__MFC_FLOW_CHECK::
Fnc__PARTIAL_CHECK(CII_OBJECT__VARIABLE *p_variable,
				   CII_OBJECT__ALARM *p_alarm)
{
	CII_EXT_OBJECT__CTRL *p_obj_ctrl = NULL;
	CII__VAR_ANALOG_CTRL *p_mfc_flow_set = NULL;

	CString fnc_msg;
	CString var_data;
	CString msg;
	int flag;
	int i;

	for(i=0;i<iSIZE__OBJ_MFCx;i++)
	{
		if(dCH_APP__GAS_USE_FLAG[i]->Check__DATA(STR__YES) < 0)
		{
			continue;
		}
		else
		{
			CString szRun_Mode;

			dCH_PARA__MFC_SETTING_MODE->Get__DATA(szRun_Mode);
			sCH_APP__GAS_RUN_MODE[i]->Set__DATA(szRun_Mode);
		}

		//
		{
			fnc_msg.Format("List%1d - Started ...", i+1);
			sCH_INFO__LIST_CTRL->Set__DATA(fnc_msg);
			
			sCH_APP__GAS_STATUS[i]->Set__DATA("Start");	

			msg.Format("MFC PARTIAL_CHECK : %s", fnc_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		//
		{
			CString msg;

			msg.Format("GAS%002d",i+1);
			sCH_INFO__CUR_GAS_ID->Set__DATA(msg);

			sEXT_CH__PARA_MFCx_GAS_NAME[i]->Get__DATA(var_data);
			sCH_INFO__CUR_GAS_NAME->Set__DATA(var_data);

			//
			CString str_min;
			CString str_max;

			aEXT_CH__PARA_MFCx_SET_FLOW[i]->Get__MIN_MAX_INFO(str_min,str_max);

			sCH_INFO__CUR_GAS_MIN->Set__DATA(str_min);
			sCH_INFO__CUR_GAS_MAX->Set__DATA(str_max);
		}

		flag = Fnc__UPPER_PARTIAL_CHECK(p_variable,p_alarm,i);
		if(flag < 0)
		{
			fnc_msg.Format("List%1d - Aborted ...", i+1);
			sCH_INFO__LIST_CTRL->Set__DATA(fnc_msg);

			sCH_APP__GAS_STATUS[i]->Set__DATA("Abort");

			msg.Format("MFC PARTIAL_CHECK : %s", fnc_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			return flag;
		}

		//
		{
			CString str_date;
			CString str_time;
			
			Macro__Get_Date(str_date,str_time);

			sCH_PARA__CHECK_DATE->Set__DATA(str_date);
			sCH_PARA__CHECK_TIME->Set__DATA(str_time);
		}

		//
		{
			int j;
			int nFlow;
			CString szPara_Mode;

			dCH_PARA__MFC_SETTING_MODE->Get__DATA(szPara_Mode);
			if(szPara_Mode.CompareNoCase(STR__YSK_PERCENT) == 0)
			{
				nFlow = CFG__GAS_FLOW_EVEN_LIST;
			}
			else
			{
				CString str_data = szPara_Mode;
				int check_percent; 
				
				if(Macro__Check_1Point(str_data,check_percent) > 0)
				{
					nFlow = 1;
				}
				else
				{
					nFlow =	CFG__GAS_FLOW_LIST;
				}
			}

			for(j=0;j<nFlow;j++)
			{
				sCH_PARA__CURRENT_PRESSURE[j]->Get__DATA(var_data);
				sCH_RESULT__CURRENT_PRESSURE[i][j]->Set__DATA(var_data);
			}

			//
			sCH_PARA__CHECK_DATE->Get__DATA(var_data);
			sCH_RESULT__CHECK_DATE[i]->Set__DATA(var_data);

			sCH_PARA__CHECK_TIME->Get__DATA(var_data);
			sCH_RESULT__CHECK_TIME[i]->Set__DATA(var_data);
		}

		sCH_APP__GAS_STATUS[i]->Set__DATA("Complete");
	}

	//
	{
		fnc_msg = "Partial Pressure Check - Completed ...";
		sCH_INFO__LIST_CTRL->Set__DATA(fnc_msg);

		msg.Format("MFC PARTIAL_CHECK : %s", fnc_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);
	}
	return 1;
}

int CObj__MFC_FLOW_CHECK::
Fnc__UPPER_PARTIAL_CHECK(CII_OBJECT__VARIABLE *p_variable,
					     CII_OBJECT__ALARM *p_alarm,
					     const int gas_index)
{
	CII_EXT_OBJECT__CTRL *p_obj_ctrl = NULL;
	CII__VAR_ANALOG_CTRL *p_mfc_flow_set = NULL;
	CII__VAR_ANALOG_CTRL *p_mfc_flow_get = NULL;
	CString gas_name;

	gas_name.Format("GAS%002d",gas_index+1);

	// ...
	{
		p_obj_ctrl = pOBJ_CTRL__MFCx[gas_index];
		p_mfc_flow_set = aEXT_CH__PARA_MFCx_SET_FLOW[gas_index].Get__PTR();
		p_mfc_flow_get = aEXT_CH__PARA_MFCx_GET_FLOW[gas_index].Get__PTR();
	}

	// ...
	{
		int i;

		for(i=0;i<CFG__GAS_FLOW_LIST;i++)
		{
			sCH_PARA__CURRENT_PRESSURE[i]->Set__DATA("");
		}

		for(i=0;i<CFG__GAS_FLOW_LIST;i++)
		{
			int flag = Fnc__LOWER_PARTIAL_CHECK(p_variable,
										        p_alarm,
										        p_obj_ctrl,
										        p_mfc_flow_set,
										        p_mfc_flow_get,
											    gas_name,
										        i);

			p_mfc_flow_set->Set__DATA("0");

			if(flag < 0)
			{
				return flag;	
			}

			pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__ALL_CLOSE);
		}
	}
	return 1;
}
int CObj__MFC_FLOW_CHECK::
Fnc__LOWER_PARTIAL_CHECK(CII_OBJECT__VARIABLE *p_variable,
					     CII_OBJECT__ALARM *p_alarm,
					     CII_EXT_OBJECT__CTRL *p_obj_ctrl,
					     CII__VAR_ANALOG_CTRL *p_mfc_set_ctrl,
					     CII__VAR_ANALOG_CTRL *p_mfc_get_ctrl,
					     const CString& gas_name,
					     const int db_index)
{
	CString str__check_mode;
	CString str__mfc_set_mode;
	CString fnc_msg;
	CString var_data;
	CString msg;

	// ...
	{
		dCH_PARA__TEST_MODE->Get__DATA(str__check_mode);
		dCH_PARA__MFC_SETTING_MODE->Get__DATA(str__mfc_set_mode);
	}

	// 1. Base Pumping
	{
		fnc_msg = "High VAC - Pumping Started ...";
		sCH_INFO__ITEM_CTRL->Set__DATA(fnc_msg);

		msg.Format("MFC PARTIAL_CHECK : %s", fnc_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);

		if(pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP) < 0)
		{
			sCH_INFO__ITEM_CTRL->Set__DATA("High VAC - Pumping Aborted ...");
			return -1;
		}
	}
	
	// 2. MFC Flow
	{	
		if(str__mfc_set_mode.CompareNoCase(STR__USER_DEF) == 0)
		{
			aCH_PARA__GAS_SET_USER_FLOW[db_index]->Get__DATA(var_data);
		}
		else
		{
			double set_per;

			aCH_PARA__GAS_SET_AUTO_FLOW[db_index]->Get__DATA(var_data);
			set_per = atof(var_data);

			//
			double min_value;
			double max_value;
			int i_dec;

			p_mfc_set_ctrl->Get__MIN_MAX_DEC(min_value,max_value,i_dec);

			double cur_value = (set_per * max_value) / 100.0;
			var_data.Format("%.3f", cur_value);
		}

		if(atof(var_data) < 0.1)
		{
			return 1;
		}

		//
		{
			dEXT_CH__GAS_VLV__PARA_MFC_TYPE->Set__DATA(gas_name);
			aEXT_CH__GAS_VLV__PARA_MFC_FLOW->Set__DATA(var_data);
			sCH_INFO__CUR_GAS_FLOW_SET->Set__DATA(var_data);

			//
			CString str_msg;

			str_msg.Format("MFC Control - Started (%s)", var_data);
			sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

			msg.Format("MFC PARTIAL_CHECK : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__MFC_CONTROL) < 0)
		{
			CString str_msg;

			str_msg = "MFC Control - Aborted ...";
			sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

			msg.Format("MFC PARTIAL_CHECK : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -21;
		}
		
		//
		{
			CString str_msg;

			str_msg = "MFC Control - Completed ...";
			sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

			msg.Format("MFC PARTIAL_CHECK : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}
	}

	// 3. Pressure Stable Time
	{
		SCX__TIMER_CTRL x_timer_ctrl;

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH_PARA__CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		double cfg__delay_sec;
		aCH_CFG__MFC_FLOW_STABLE_DELAY_SEC->Get__DATA(var_data);
		cfg__delay_sec = atof(var_data);

		//
		{
			CString str_msg;

			str_msg.Format("Pressure Stable Time - (%s) sec", var_data);
			sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

			msg.Format("MFC PARTIAL_CHECK : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			CString str_msg;

			str_msg = "Pressure Stable Time - Aborted ...";
			sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

			msg.Format("MFC PARTIAL_CHECK : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			return -3;
		}
	}

	// 4. Result Error Check
	{
		sEXT_CH__CHM_PRESSURE_TORR->Get__DATA(var_data);

		double cur_mtorr = atof(var_data) * 1000.0;
		var_data.Format("%.1f",cur_mtorr);
		sCH_PARA__CURRENT_PRESSURE[db_index]->Set__DATA(var_data);
	}

	return 1;
}

int CObj__MFC_FLOW_CHECK::
Fnc__MFC_CAL_CHECK(CII_OBJECT__VARIABLE *p_variable,
				   CII_OBJECT__ALARM *p_alarm)
{
	printf(" * CObj__MFC_FLOW_CHECK::Fnc__MFC_CAL_CHECK() ... \n");

	// ...
	CII_EXT_OBJECT__CTRL *p_obj_ctrl = NULL;
	CII__VAR_ANALOG_CTRL *p_mfc_flow_set = NULL;

	CString fnc_msg;
	CString var_data;
	CString msg;
	int flag;
	int i;

	for(i=0;i<iSIZE__OBJ_MFCx;i++)
	{
		if(dCH_APP__GAS_USE_FLAG[i]->Check__DATA(STR__YES) < 0)
		{
			continue;
		}
		else
		{
			CString szRun_Mode;

			dCH_PARA__MFC_SETTING_MODE->Get__DATA(szRun_Mode);
			sCH_APP__GAS_RUN_MODE[i]->Set__DATA(szRun_Mode);
		}

		//
		{
			fnc_msg.Format("List%1d - Started ...", i+1);
			sCH_INFO__LIST_CTRL->Set__DATA(fnc_msg);
			
			sCH_APP__GAS_STATUS[i]->Set__DATA("Start");	

			msg.Format("MFC CAL_CHECK : %s", fnc_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		//
		{
			CString msg;

			msg.Format("GAS%002d",i+1);
			sCH_INFO__CUR_GAS_ID->Set__DATA(msg);

			sEXT_CH__PARA_MFCx_GAS_NAME[i]->Get__DATA(var_data);
			sCH_INFO__CUR_GAS_NAME->Set__DATA(var_data);

			//
			CString str_min;
			CString str_max;

			aEXT_CH__PARA_MFCx_SET_FLOW[i]->Get__MIN_MAX_INFO(str_min,str_max);

			sCH_INFO__CUR_GAS_MIN->Set__DATA(str_min);
			sCH_INFO__CUR_GAS_MAX->Set__DATA(str_max);
		}

		flag = Fnc__UPPER_MFC_CAL_CHECK(p_variable,p_alarm,i);
		if(flag < 0)
		{
			fnc_msg.Format("List%1d - Aborted ...", i+1);
			sCH_INFO__LIST_CTRL->Set__DATA(fnc_msg);

			sCH_APP__GAS_STATUS[i]->Set__DATA("Abort");

			msg.Format("MFC CAL_CHECK : %s", fnc_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			return flag;
		}

		//
		{
			CString str_date;
			CString str_time;
			
			Macro__Get_Date(str_date,str_time);

			sCH_PARA__CHECK_DATE->Set__DATA(str_date);
			sCH_PARA__CHECK_TIME->Set__DATA(str_time);
		}

		//
		{
			int nFlow;
			
			CString	str_data = dCH_PARA__MFC_SETTING_MODE->Get__STRING();
			if(str_data.CompareNoCase(STR__YSK_PERCENT) == 0)
			{
				nFlow = CFG__GAS_FLOW_EVEN_LIST;
			}
			else
			{
				int check_percent; 

				if(Macro__Check_1Point(str_data, check_percent) > 0)		nFlow = 1;
				else														nFlow =	CFG__GAS_FLOW_LIST;
			}

			for(int j=0; j<nFlow; j++)
			{
				sCH_PARA__GAS_CURRENT_FLOW[j]->Get__DATA(var_data);
				sCH_RESULT__CURRENT_FLOW[i][j]->Set__DATA(var_data);

				sCH_PARA__CAL_ERROR_RESULT[j]->Get__DATA(var_data);
				sCH_RESULT__CAL_ERROR[i][j]->Set__DATA(var_data);
			}

			//
			sCH_PARA__CHECK_DATE->Get__DATA(var_data);
			sCH_RESULT__CHECK_DATE[i]->Set__DATA(var_data);

			sCH_PARA__CHECK_TIME->Get__DATA(var_data);
			sCH_RESULT__CHECK_TIME[i]->Set__DATA(var_data);
		}

		sCH_APP__GAS_STATUS[i]->Set__DATA("Complete");
	}

	// ...
	{
		fnc_msg = "MFC Calibration Check - Completed ...";
		sCH_INFO__LIST_CTRL->Set__DATA(fnc_msg);

		msg.Format("MFC CAL_CHECK : %s", fnc_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);
	}
	return 1;
}

int CObj__MFC_FLOW_CHECK::
Fnc__UPPER_MFC_CAL_CHECK(CII_OBJECT__VARIABLE *p_variable,
					     CII_OBJECT__ALARM *p_alarm,
					     const int gas_index)
{
	CII_EXT_OBJECT__CTRL *p_obj_ctrl = NULL;
	CII__VAR_ANALOG_CTRL *p_mfc_flow_set = NULL;
	CII__VAR_ANALOG_CTRL *p_mfc_flow_get = NULL;
	CString gas_name;

	gas_name.Format("GAS%002d",gas_index+1);

	// ...
	{
		p_obj_ctrl = pOBJ_CTRL__MFCx[gas_index];
		p_mfc_flow_set = aEXT_CH__PARA_MFCx_SET_FLOW[gas_index].Get__PTR();
		p_mfc_flow_get = aEXT_CH__PARA_MFCx_GET_FLOW[gas_index].Get__PTR();
	}

	// ...
	{
		int i;

		for(i=0; i<CFG__GAS_FLOW_LIST; i++)
		{
			sCH_PARA__GAS_CURRENT_FLOW[i]->Set__DATA("");
			sCH_PARA__CAL_ERROR_RESULT[i]->Set__DATA("");
		}

		for(i=0; i<CFG__GAS_FLOW_LIST; i++)
		{
			int flag = Fnc__LOWER_MFC_CAL_CHECK(p_variable,
										        p_alarm,
										        p_obj_ctrl,
										        p_mfc_flow_set,
										        p_mfc_flow_get,
											    gas_name,
												gas_index,
										        i);

			p_mfc_flow_set->Set__DATA("0");
			
			if(flag < 0)
			{
				return flag;	
			}
	
			pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__ALL_CLOSE);
		}
	}
	return 1;
}
int CObj__MFC_FLOW_CHECK::
Fnc__LOWER_MFC_CAL_CHECK(CII_OBJECT__VARIABLE *p_variable,
					     CII_OBJECT__ALARM *p_alarm,
					     CII_EXT_OBJECT__CTRL *p_obj_ctrl,
					     CII__VAR_ANALOG_CTRL *p_mfc_set_ctrl,
					     CII__VAR_ANALOG_CTRL *p_mfc_get_ctrl,
					     const CString& gas_name,
						 const int gas_index,
					     const int db_index)
{
	CString str__check_mode;
	CString str__mfc_set_mode;
	CString var_data;
	CString str_msg;
	CString msg;

	// ...
	{
		dCH_PARA__TEST_MODE->Get__DATA(str__check_mode);
		dCH_PARA__MFC_SETTING_MODE->Get__DATA(str__mfc_set_mode);
	}

	// 1. Base Pumping
	{
		str_msg = "High VAC - Pumping Started ...";
		sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

		msg.Format("MFC CAL_CHECK : %s", str_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);

		printf(" * High_Vac Pumping : Start ... \n");

		if(pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP) < 0)
		{
			sCH_INFO__ITEM_CTRL->Set__DATA("High VAC - Pumping Aborted ...");

			printf(" * High_Vac Pumping : Aborted ... \n");
			return -1;
		}

		printf(" * High_Vac Pumping : End ... \n");
		printf(" * Over-Pumping : Start ... \n");

		// ...
		{
			SCX__ASYNC_TIMER_CTRL x_async_timer_ctrl;
			x_async_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH_PARA__CHECK_TIME_COUNT->Get__CHANNEL_NAME());
			x_async_timer_ctrl->START__COUNT_UP(99999);

			aCH_CFG__OVER_PUMPING_TIME->Get__DATA(var_data);
			double cfg_sec = atof(var_data);

			// ...
			CString str_msg;

			str_msg.Format("Over-Pumping Time - (%s) sec", var_data);
			sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

			msg.Format("MFC CAL_CHECK : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			while(1)
			{
				Sleep(10);

				if(x_async_timer_ctrl->Get__CURRENT_TIME() > cfg_sec)
				{
					break;
				}

				if(p_variable->Check__CTRL_ABORT() > 0)
				{
					sCH_INFO__ITEM_CTRL->Set__DATA("High VAC - Over-Pumping Aborted ...");

					printf(" * Over-Pumping : Aborted ... \n");			
					return -111;
				}
			}
		}
		dEXT_CH___ISO_VLV->Set__DATA("Open");

		printf(" * Over-Pumping : End ... \n");
	}
	
	// 2. VAT Close
	{
		printf(" ** VAT : Close ... \n");

		// ...
		{
			str_msg = "VAT Close - Started ...";
			sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

			msg.Format("MFC CAL_CHECK : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		// if(pOBJ_CTRL__VAT->Call__OBJECT(CMMD_MODE__VAT_CLOSE) < 0)
		if(pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_CLOSE_VAC_LINE) < 0)
		{
			str_msg = "VAT Close - Aborted ...";
			sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

			msg.Format("MFC CAL_CHECK : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			printf(" ** VAT : Aborted ... \n");
			return -3;
		}

		sCH_INFO__ITEM_CTRL->Set__DATA("VAT Close - Completed ...");

		printf(" ** VAT : End ... \n");
	}

	// 3. Pressure Stable Time
	{
		SCX__TIMER_CTRL x_timer_ctrl;

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH_PARA__CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		aCH_CFG__MFC_FLOW_STABLE_DELAY_SEC->Get__DATA(var_data);
		double cfg__delay_sec = atof(var_data);

		printf(" ** Pressure Stable (%.1f) sec : Start ... \n", cfg__delay_sec);

		// ...
		{
			str_msg.Format("Pressure Stable Time - (%s) sec", var_data);
			sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

			msg.Format("MFC CAL_CHECK : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			str_msg = "Pressure Stable Time - Aborted ...";
			sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

			msg.Format("MFC CAL_CHECK : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			printf(" ** Pressure Stable (%s) sec : Aborted ... \n", sCH_PARA__CHECK_TIME_COUNT->Get__STRING());
			return -4;
		}

		printf(" ** Pressure Stable (%s) sec : End ... \n", sCH_PARA__CHECK_TIME_COUNT->Get__STRING());
	}

	// 4. MFC Flow
	{	
		printf(" * MFC(%1d)-Flow Control : Start ... \n", gas_index);
		printf(" ** mfc_set_mode <- [%s] \n", str__mfc_set_mode);

		if(str__mfc_set_mode.CompareNoCase(STR__USER_DEF) == 0)
		{
			aCH_PARA__GAS_SET_USER_FLOW[db_index]->Get__DATA(var_data);

			printf(" ** %s <- %s \n", 
				aCH_PARA__GAS_SET_USER_FLOW[db_index]->Get__CHANNEL_NAME(),
				var_data);
		}
		else
		{
			aCH_PARA__GAS_SET_AUTO_FLOW[db_index]->Get__DATA(var_data);
			double set_per = atof(var_data);

			printf(" ** %s <- %s \n", 
				aCH_PARA__GAS_SET_AUTO_FLOW[db_index]->Get__CHANNEL_NAME(),
				var_data);

			// ...
			double min_value;
			double max_value;
			int i_dec;

			p_mfc_set_ctrl->Get__MIN_MAX_DEC(min_value,max_value, i_dec);

			double cur_value = (set_per * max_value) / 100.0;
			var_data.Format("%.3f", cur_value);

			printf(" ** min_value <- %.3f \n", min_value);
			printf(" ** max_value <- %.3f \n", max_value);
			printf(" ** cur_value <- %.3f \n", cur_value);
		}

		// ...
		double set_gas_flow = atof(var_data);

		if(set_gas_flow < 0.001)
		{
			printf(" ** set_gas_flow <- %.3f \n : Skip !!! \n", set_gas_flow);
			return 1;
		}

		// ...
		{
			CString str_data;

			aCH_CFG__MFC_MAX_GAS_CAL_FLOW->Get__DATA(str_data);
			double gas_max_cal = atof(str_data);

			if(gas_max_cal < set_gas_flow)
			{
				int alarm_id = ALID__MFC_MAX_GAS_CAL_FLOW;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("%s's set-flow (%s) must be less than \"%s\".\n", 
					gas_name,var_data,str_data);
				alm_msg += alm_bff;

				alm_bff.Format("In Utility.CFG page, MFC MAX GAS CAL's Value is \"%s\".\n",
					str_data);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__WARNING_With_MESSAGE(alarm_id,alm_msg);

				sCH_PARA__CAL_ERROR_RESULT[db_index]->Set__DATA("Error");
				return 1;
			}
		}

		// ...
		{
			dEXT_CH__GAS_VLV__PARA_MFC_TYPE->Set__DATA(gas_name);
			aEXT_CH__GAS_VLV__PARA_MFC_FLOW->Set__DATA(var_data);
			sCH_INFO__CUR_GAS_FLOW_SET->Set__DATA(var_data);

			str_msg.Format("MFC Control - Started (%s)", var_data);
			sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

			msg.Format("MFC CAL_CHECK : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		// ...
		{
			printf(" ** MFC(%1d)_Control : Start ... \n", gas_index);

			printf(" ** %s <- %s \n", 
				dEXT_CH__GAS_VLV__PARA_MFC_TYPE->Get__CHANNEL_NAME(),
				dEXT_CH__GAS_VLV__PARA_MFC_TYPE->Get__STRING());
			printf(" ** %s <- %.3f \n", 
				aEXT_CH__GAS_VLV__PARA_MFC_FLOW->Get__CHANNEL_NAME(),
				aEXT_CH__GAS_VLV__PARA_MFC_FLOW->Get__VALUE());
		}

		if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_MODE__FNC_MFC__MFC_CONTROL) < 0)
		{
			str_msg = "MFC Control - Aborted ...";
			sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

			msg.Format("MFC CAL_CHECK : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			printf(" ** MFC(%1d)_Control : Aborted ... \n", gas_index);
			return -21;
		}

		// ...
		{
			str_msg = "MFC Control - Completed ...";
			sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

			msg.Format("MFC CAL_CHECK : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		printf(" ** MFC(%1d)_Control : End ... \n", gas_index);
	}

	// 5. Ref Pressure Check
	{
		double cfg__timeout;
		double cfg__ref_pressure;
		double cur__chm_pressure;

		SCX__ASYNC_TIMER_CTRL x_async_timer_ctrl;
		x_async_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH_PARA__CHECK_TIME_COUNT->Get__CHANNEL_NAME());
		x_async_timer_ctrl->START__COUNT_UP(99999);

		// ...
		{
			sEXT_CH__CHM_PRESSURE_mTORR->Get__DATA(var_data);
			sCH_PARA__CHECK_START_PRESSURE->Set__DATA(var_data);

			sCH_PARA__CHECK_END_PRESSURE->Set__DATA("");
			sCH_PARA__CHECK_CAL_TIME->Set__DATA("");
		}

		// ...
		{
			CString str_msg;

			aCH_CFG__MFC_FLOW_CHECK_TIMEOUT->Get__DATA(var_data);

			str_msg.Format("Test Check Timeout - (%s) sec", var_data);
			sCH_INFO__ITEM_CTRL->Set__DATA(str_msg);

			msg.Format("MFC CAL_CHECK : %s", str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		cfg__ref_pressure = aCH_APP__GAS_CHECK_PRESSURE[gas_index]->Get__VALUE();
		if(cfg__ref_pressure < 0.001)
		{
			aCH_CFG__MFC_FLOW_REF_PRESSURE->Get__DATA(var_data);
			cfg__ref_pressure = atof(var_data);
		}

		printf(" ** Ref.Pressure Check : Start ... \n");
		printf(" ** Target Pressure <- %.3f torr \n", cfg__ref_pressure);
		printf(" ** Check Timeout <- (%.1f) sec \n", aCH_CFG__MFC_FLOW_CHECK_TIMEOUT->Get__VALUE());
		printf(" ** Set Gas-Flow  <- %s sccm \n", sCH_INFO__CUR_GAS_FLOW_SET->Get__STRING());

		// ...
		double sim__check_sec = cfg__timeout;

		// ...
		{
			sCH_INFO__CUR_GAS_FLOW_SET->Get__DATA(var_data);
			double set_flow = atof(var_data);

			double cfg__ref_mtorr = cfg__ref_pressure * 1000.0;

			if(iSIM_MODE > 0)
			{
				sim__check_sec = Get__GAS_CAL_TIME(set_flow, cfg__ref_mtorr);
				printf(" ** sim__check_sec <- (%.3f) sec \n", sim__check_sec);
			}
			else
			{
				double exp__check_sec = Get__GAS_CAL_TIME(set_flow, cfg__ref_mtorr);
				printf(" ** expected__check_sec <- (%.3f) sec \n", exp__check_sec);
			}
		}

		while(1)
		{
			Sleep(10);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				printf(" ** Ref.Pressure Check : Aborted ... \n");
				return -5;
			}

			cfg__timeout = aCH_CFG__MFC_FLOW_CHECK_TIMEOUT->Get__VALUE();
			if(cfg__timeout < x_async_timer_ctrl->Get__CURRENT_TIME())
			{
				int alarm_id = ALID__MFC_FLOW_CHECK_TIMEOUT;
				CString alarm_msg;
				CString alarm_bff;
				CString r_act;

				alarm_msg.Format("The current \"MFC FLOW CHECK TIMEOUT\" is %.1f sec.\n", cfg__timeout);
				alarm_bff.Format("Please, check MFC flow.\n");
				alarm_msg += alarm_bff;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alarm_msg);
				return -51;
			}

			cfg__ref_pressure = aCH_APP__GAS_CHECK_PRESSURE[gas_index]->Get__VALUE();
			if(cfg__ref_pressure < 0.001)
			{
				aCH_CFG__MFC_FLOW_REF_PRESSURE->Get__DATA(var_data);
				cfg__ref_pressure = atof(var_data);
			}

			if(iSIM_MODE > 0)
			{
				double cur_sec = x_async_timer_ctrl->Get__CURRENT_TIME();

				double time_per = 1.0;
				if(cfg__timeout > 0.9)			time_per = cur_sec / sim__check_sec;
				if(time_per > 1.0)				time_per = 1.0;

				cur__chm_pressure = cfg__ref_pressure * time_per;
				
				var_data.Format("%.3f", cur__chm_pressure * 1000.0);
				sEXT_CH__CHM_PRESSURE_mTORR->Set__DATA(var_data);

				/*
				printf(" * cur__chm_pressure  <- %.3f torr \n", cur__chm_pressure);
				printf(" ** cfg__ref_pressure <- %.3f torr \n", cfg__ref_pressure);
				printf(" ** time_per <- %.3f \n", time_per);
				printf(" ** cur_sec  <- %.3f \n", cur_sec);
				*/
			}
			else
			{
				sEXT_CH__CHM_PRESSURE_mTORR->Get__DATA(var_data);
				cur__chm_pressure = atof(var_data) / 1000.0;
			}

			if(cur__chm_pressure >= cfg__ref_pressure)
			{
				break;
			}
		}	

		if(iSIM_MODE > 0)
		{
			var_data.Format("%.1f", cfg__ref_pressure * 1000.0);
			sCH_PARA__CHECK_END_PRESSURE->Set__DATA(var_data);
		}
		else
		{
			sEXT_CH__CHM_PRESSURE_mTORR->Get__DATA(var_data);
			sCH_PARA__CHECK_END_PRESSURE->Set__DATA(var_data);
		}

		// ...
		{
			var_data.Format("%.3f", x_async_timer_ctrl->Get__CURRENT_TIME());
			sCH_PARA__CHECK_CAL_TIME->Set__DATA(var_data);

			x_async_timer_ctrl->STOP();
		}

		printf(" ** Ref.Pressure Check : End ... \n");
		printf(" ** End-Pressure <- %s mtorr \n",   sCH_PARA__CHECK_END_PRESSURE->Get__STRING());
		printf(" ** Cal-Time <- (%s) sec \n", sCH_PARA__CHECK_CAL_TIME->Get__STRING());
	}

	// 6. Result Display
	{
		double test_flow = Get__GAS_CAL_RATE();

			 if(test_flow >= 10000.0)			var_data.Format("%.0f", test_flow);
		else if(test_flow >=  1000.0)			var_data.Format("%.1f", test_flow);
		else if(test_flow >=   100.0)			var_data.Format("%.2f", test_flow);
		else									var_data.Format("%.3f", test_flow);
		
		sCH_PARA__GAS_CURRENT_FLOW[db_index]->Set__DATA(var_data);
		double get_value = atof(var_data);

		p_mfc_set_ctrl->Get__DATA(var_data);
		double set_value = atof(var_data);

		// ...
		double cal_err = 0;
		if(set_value > 0)	cal_err = ((get_value - set_value) / set_value) * 100;

		double abs_err = cal_err;
		if(abs_err < 0)		abs_err = -abs_err;

			 if(abs_err >= 10000.0)					var_data.Format("%.0f", cal_err);
		else if(abs_err >=  1000.0)					var_data.Format("%.1f", cal_err);
		else if(abs_err >=   100.0)					var_data.Format("%.2f", cal_err);
		else										var_data.Format("%.3f", cal_err);

		sCH_PARA__CAL_ERROR_RESULT[db_index]->Set__DATA(var_data);

		// ...
		{
			printf(" *  Result Display ... \n");
			printf(" ** get_value <- [%.3f] \n", get_value);
			printf(" ** set_value <- [%.3f] \n", set_value);
			printf(" ** abs_err   <- [%.3f) \n", abs_err);
		}

		// ...
		double warning_low;
		double warning_high;

		double err_low;
		double err_high;

		aCH_CFG__MFC_FLOW_LOW_ERROR[gas_index]->Get__DATA(var_data);
		err_low = atof(var_data);
		aCH_CFG__MFC_FLOW_HIGH_ERROR[gas_index]->Get__DATA(var_data);
		err_high = atof(var_data);

		aCH_CFG__MFC_FLOW_LOW_WARNING[gas_index]->Get__DATA(var_data);
		warning_low = atof(var_data);
		aCH_CFG__MFC_FLOW_HIGH_WARNING[gas_index]->Get__DATA(var_data);
		warning_high = atof(var_data);

		// ...
		int alarm_id;
		CString r_act;

		if(cal_err <= -err_low)
		{
			alarm_id = ALID__MFC_CAL__ERROR_LOW + gas_index;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
			return 1;
		}
		if(cal_err >= err_high)
		{
			alarm_id = ALID__MFC_CAL__ERROR_HIGH + gas_index;


			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
			return 1;
		}
		if(cal_err <= -warning_low)
		{
			alarm_id = ALID__MFC_CAL__WARNING_LOW + gas_index;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
			return 1;
		}
		if(cal_err >= warning_high)
		{
			alarm_id = ALID__MFC_CAL__WARNING_HIGH + gas_index;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
			return 1;
		}
	}

	return 1;
}

double CObj__MFC_FLOW_CHECK::Get__GAS_CAL_RATE()
{
	double chm_volume;
	double chm_temperature;
	double s_press;
	double e_press;
	double check_sec;
	CString var_data;

	aEXT_CH__DB_SYS_CHM_VOLUMN->Get__DATA(var_data);
	chm_volume = atof(var_data);

	aEXT_CH__DB_SYS_CHM_TEMPERATURE->Get__DATA(var_data);
	chm_temperature = atof(var_data);

	//
	sCH_PARA__CHECK_START_PRESSURE->Get__DATA(var_data);
	s_press = atof(var_data);

	sCH_PARA__CHECK_END_PRESSURE->Get__DATA(var_data);
	e_press = atof(var_data);

	//
	sCH_PARA__CHECK_CAL_TIME->Get__DATA(var_data);
	check_sec = atof(var_data);
	if(check_sec < 0.001)		check_sec = 0.001;

	double cfg_coefficent = aCH__CFG_PROPORTION_COEFFICENT->Get__VALUE();

	//
	double actual_flow_rate;

	// actual_flow_rate = ((21.572) / (273.15 + chm_temperature)) * (chm_volume) * (e_press - s_press) / check_sec;
	actual_flow_rate = ((21.572) * (chm_volume) * (e_press - s_press)) / ((273.15 + chm_temperature) * check_sec);
	actual_flow_rate = actual_flow_rate * cfg_coefficent;

	return actual_flow_rate;
}
double CObj__MFC_FLOW_CHECK::Get__GAS_CAL_TIME(const double set_flow, const double trg_press)
{
	double chm_volume = aEXT_CH__DB_SYS_CHM_VOLUMN->Get__VALUE();
	double chm_temperature = aEXT_CH__DB_SYS_CHM_TEMPERATURE->Get__VALUE();

	CString var_data = sCH_PARA__CHECK_START_PRESSURE->Get__STRING();
	double s_press = atof(var_data);
	double e_press = trg_press;

	double check_sec = ((21.572) * (chm_volume) * (e_press - s_press)) / ((273.15 + chm_temperature) * set_flow);
	return check_sec;
}
