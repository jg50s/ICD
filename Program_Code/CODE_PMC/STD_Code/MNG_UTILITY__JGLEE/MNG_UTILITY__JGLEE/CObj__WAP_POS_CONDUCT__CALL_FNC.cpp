#include "StdAfx.h"
#include "CObj__WAP_POS_CONDUCT.h"


extern void Macro__Get_Date(CString& date, CString& time);

extern int  Macro__Convert_String_To_Array(const CString& str_data,
										   CStringArray&  l_data);
extern int  Macro__Convert_String_To_String(const CString& str_data,
											CString& data1,
											CString& data2);


//-------------------------------------------------------------------------
int CObj__WAP_POS_CONDUCT::
Call__POSITION_PRESSURE_CHECK(CII_OBJECT__VARIABLE *p_variable,
							  CII_OBJECT__ALARM *p_alarm)
{
	sEXT_CH__DGF_CENTER_WT_SP->Set__DATA("50");

	// ...
	int flag = 1;
	
	if(flag > 0)
	{
		flag = Init__POSITION_PRESSURE_CHECK(p_variable,p_alarm);
	}

	if(flag > 0)
	{
		flag = Fnc__POSITION_PRESSURE_CHECK(p_variable,p_alarm);
	}

	End__POSITION_PRESSURE_CHECK(p_variable,p_alarm);
	return flag;
}

int CObj__WAP_POS_CONDUCT::
Init__POSITION_PRESSURE_CHECK(CII_OBJECT__VARIABLE *p_variable,
							  CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	CString log_bff;
	
	CString obj_msg;
	CString fnc_msg;
	
	
	// 1. WAP Init ...
	{
		// ...
		{
			obj_msg = "WAP Init - Started ...";
			xCH__OBJ_MSG->Set__DATA(obj_msg);
			
			fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}
		
		if(pOBJ_CTRL__WAP->Call__OBJECT("INIT") < 0)
		{
			// ...
			{
				obj_msg = "WAP Init - Aborted ...";
				xCH__OBJ_MSG->Set__DATA(obj_msg);
				
				fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
				sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
			}
			return -11;
		}
		
		// ...
		{
			obj_msg = "WAP Init - Completed ...";
			xCH__OBJ_MSG->Set__DATA(obj_msg);
			
			fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}
	}
	
	// 2. Base Pumping ...
	{
		// ...
		{
			obj_msg = "High VAC - Pumping Started ...";
			xCH__OBJ_MSG->Set__DATA(obj_msg);
			
			fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}
		
		//
		sEXT_CH__DGF_CENTER_WT_SP->Set__DATA("50");

		if(pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP) < 0)
		{
			// ...
			{
				obj_msg = "High VAC - Pumping Aborted ...";
				xCH__OBJ_MSG->Set__DATA(obj_msg);
				
				fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
				sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
			}
			return -12;
		}

		sEXT_CH__DGF_CENTER_WT_SP->Set__DATA("50");
		//
		
		// ...
		{
			obj_msg = "High VAC - Pumping Completed ...";
			xCH__OBJ_MSG->Set__DATA(obj_msg);
			
			fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}
	}
	
	return 1;
}
int CObj__WAP_POS_CONDUCT::
End__POSITION_PRESSURE_CHECK(CII_OBJECT__VARIABLE *p_variable,
						     CII_OBJECT__ALARM *p_alarm)
{
	CString obj_msg;
	CString fnc_msg;


	// WAP <- Up ...
	{
		// ...
		{
			obj_msg = "WAP Up Started ...";
			xCH__OBJ_MSG->Set__DATA(obj_msg);
		
			fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}
		
		// ...
		{
			pOBJ_CTRL__WAP->Dislink__UPPER_OBJECT();
		
			pOBJ_CTRL__WAP->Call__OBJECT("UP");
		
			pOBJ_CTRL__WAP->Link__UPPER_OBJECT();
		}
	}
	
	// CHM <- High_VAC Pump ...
	{
		// ...
		{
			obj_msg = "High Vac Pumping Started ...";
			xCH__OBJ_MSG->Set__DATA(obj_msg);
		
			fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}

		// ...
		{
			pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();
		
			pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP);
		
			pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
		}
	}
	
	xCH__OBJ_MSG->Set__DATA("");
	return 1;
}
int CObj__WAP_POS_CONDUCT::
Fnc__POSITION_PRESSURE_CHECK(CII_OBJECT__VARIABLE *p_variable,
							 CII_OBJECT__ALARM *p_alarm)
{
	CStringArray l_ref_pos;
	CStringArray l_ref_press;
	
	int check_flag = 1;

	int limit;
	int i;
	
	
	Fnc__REF_POS_PRESS_DATA(l_ref_pos,l_ref_press);
	
	// ...
	{
		CString log_msg;
		CString log_bff;
		CString var_data;
		
		CString str_pos;
		double  ref_pos;
		double  ref_press;
		double  cur_press;
		
		//
		{
			log_msg  = "\n";
			log_msg += "// -------------------------------------------------------------------------------------------";
			log_msg += "\n";
			log_msg += "Index,REF-Position,REF-Pressure(mtorr),Current-Pressure(mtorr)";
			log_msg += "\n";
		}
		
		//
		limit = l_ref_pos.GetSize();
		l_ref_press.SetSize(limit);
		
		for(i=0;i<limit;i++)
		{
			str_pos   = l_ref_pos[i];
			ref_pos   = atof(str_pos);
			ref_press = atof(l_ref_press[i]);
			
			// Position Moving ...
			if(Fnc_Move__POSITION_PRESSURE_CHECK(p_variable,p_alarm, str_pos) < 0)
			{
				// ...
				{
					log_msg += "\n";

					log_bff.Format("\"%s\" Position Check - Aborted !!!", str_pos);
					log_msg += log_bff;
					
					log_msg += "\n";
				}

				check_flag = -1;
				break;
			}
			
			sEXT_CH__CHM_PRESSURE->Get__DATA(var_data);
			cur_press = atof(var_data) * 1000.0;		// mtorr
			
			// ...
			{
				log_bff.Format("%0003d),   %.0f,   %.1f,   %.1f \n", i+1,ref_pos,ref_press,cur_press);
				log_msg += log_bff;
			}
		}
		
		//
		{
			log_msg += "// -------------------------------------------------------------------------------------------";
			log_msg += "\n";
		}
		
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return check_flag;
}
int CObj__WAP_POS_CONDUCT::
Fnc_Move__POSITION_PRESSURE_CHECK(CII_OBJECT__VARIABLE *p_variable,
								  CII_OBJECT__ALARM *p_alarm,
								  const CString& str_pos)
{
	CString obj_msg;
	CString fnc_msg;

	CString var_data;


	// 1. MFC Flow ...
	{	
		CString gas_name;
		CString gas_flow;

		dCH_CFG__POS_PRESS_CHECK__GAS_TYPE->Get__DATA(gas_name);
		aCH_CFG__POS_PRESS_CHECK__GAS_FLOW->Get__DATA(gas_flow);

		dEXT_CH__FNC_MFC__PARA_MFC_TYPE->Set__DATA(gas_name);
		aEXT_CH__FNC_MFC__PARA_MFC_FLOW->Set__DATA(gas_flow);

		// ...
		{
			obj_msg.Format("MFC Control - Started : (%s) <- (%s)", gas_name,gas_flow);
			xCH__OBJ_MSG->Set__DATA(obj_msg);

			fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}

		if(pOBJ_CTRL__FNC_MFC->Call__OBJECT(CMMD_MODE__FNC_MFC__MFC_CONTROL) < 0)
		{
			// ...
			{
				obj_msg = "MFC Control - Aborted ...";
				xCH__OBJ_MSG->Set__DATA(obj_msg);

				fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
				sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
			}
			return -11;
		}

		// ...
		{
			obj_msg = "MFC Control - Completed ...";
			xCH__OBJ_MSG->Set__DATA(obj_msg);

			fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}
	}

	// 2. Flow Delay Sec ...
	{
		SCX__TIMER_CTRL x_timer_ctrl;
		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH_PARA__POS_PRESS_CHECK__TIME_COUNT->Get__CHANNEL_NAME());

		double cfg__delay_sec;
		aCH_CFG__POS_PRESS_CHECK__FLOW_DELAY_SEC->Get__DATA(var_data);
		cfg__delay_sec = atof(var_data);

		// ...
		{
			obj_msg.Format("Flow Delay - Started ...  (%s) sec", var_data);
			xCH__OBJ_MSG->Set__DATA(obj_msg);

			fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}

		if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			// ...
			{
				obj_msg = "Flow Delay - Aborted ...";
				xCH__OBJ_MSG->Set__DATA(obj_msg);

				fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
				sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
			}
			return -12;
		}
	}

	// 3. WAP Ctrl ...
	{
		// ...
		{
			obj_msg = "WAP Control - Started ...";
			xCH__OBJ_MSG->Set__DATA(obj_msg);

			fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}

		// ...
		{
			aEXT_CH__PARA_PRESET_POS->Set__DATA("0");
			aEXT_CH__PARA_TRG_POS->Set__DATA(str_pos);
			dEXT_CH__PARA_CONTROL_TYPE->Set__DATA("Position");

			if(pOBJ_CTRL__WAP->Call__OBJECT(CMMD_MODE__VAT_CONTROL) < 0)
			{
				// ...
				{
					obj_msg = "WAP Control - Aborted ...";
					xCH__OBJ_MSG->Set__DATA(obj_msg);

					fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
					sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
				}
				return -13;
			}
		}

		// ...
		{
			obj_msg = "WAP Control - Completed ...";
			xCH__OBJ_MSG->Set__DATA(obj_msg);

			fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}
	}

	// 4. Pressure Stable Time ...
	{
		SCX__TIMER_CTRL x_timer_ctrl;
		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH_PARA__POS_PRESS_CHECK__TIME_COUNT->Get__CHANNEL_NAME());

		double cfg__delay_sec;
		aCH_CFG__POS_PRESS_CHECK__PRESSURE_STABLE_DELAY_SEC->Get__DATA(var_data);
		cfg__delay_sec = atof(var_data);

		// ...
		{
			obj_msg.Format("Pressure Stable Time - (%s) sec", var_data);
			xCH__OBJ_MSG->Set__DATA(obj_msg);

			fnc_msg.Format("WAP CONDUCT : %s", obj_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}

		if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			// ...
			{
				obj_msg = "Pressure Stable Time - Aborted ...";
				xCH__OBJ_MSG->Set__DATA(obj_msg);

				fnc_msg.Format("POS/PRESS CHECK : %s", obj_msg);
				sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
			}
			return -14;
		}
	}

	return 1;
}
int CObj__WAP_POS_CONDUCT::
Fnc__REF_POS_PRESS_DATA(CStringArray& l_ref_pos,
						CStringArray& l_ref_press)
{
	// ...
	{
		l_ref_pos.RemoveAll();
		l_ref_press.RemoveAll();

		_Fnc__REF_POS_PRESS_DATA(l_ref_pos,l_ref_press);
	}

	// ...
	{
		CString str_data;
		CString bff_data;

		double  ref_pos;
		double  ref_press;

		int limit = l_ref_pos.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			ref_pos   = atof(l_ref_pos[i]);
			ref_press = atof(l_ref_press[i]);
			
			bff_data.Format("%.3f/%.3f,", ref_pos,ref_press);
			str_data += bff_data;
		}

		sCH__RESULT_REF_POSITION_PRESSURE_STRING->Set__DATA(str_data);
	}
	
	return 1;
}


// ...
int CObj__WAP_POS_CONDUCT::
Call__POS_CONDUCT(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{	
	CString str_msg;
	CString msg;

	// ...
	{
		int i;

		for(i=0;i<CFG__TEST_LIST;i++)
		{
 			sCH_NEW__CONDUCT_RESULT[i]->Set__DATA("");
		}

		sCH_PARA__TEST_DATE->Set__DATA("");
		sCH_PARA__TEST_TIME->Set__DATA("");
		
		sCH__RESULT_NEW_STRING->Set__DATA("");
	}

	// ...
	xCH__AUTO_START_CTRL->Set__DATA("START");

	// ...
	{
		sEXT_CH__DGF_CENTER_WT_SP->Set__DATA("50");
	}
	
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
		str_msg = "MFC All Closed ...";
		xCH__OBJ_MSG->Set__DATA(str_msg);

		msg.Format("WAP CONDUCT : %s",str_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);

		//
		pOBJ_CTRL__FNC_MFC->Dislink__UPPER_OBJECT();

		aEXT_CH__FNC_MFC__PARA_MFC_FLOW->Set__DATA("0");
		pOBJ_CTRL__FNC_MFC->Call__OBJECT(CMMD_MODE__FNC_MFC__MFC_CONTROL);
		pOBJ_CTRL__FNC_MFC->Call__OBJECT(CMMD_MODE__FNC_MFC__ALL_CLOSE);

		pOBJ_CTRL__FNC_MFC->Link__UPPER_OBJECT();
	}

	// ...
	{
		str_msg = "WAP Up Started ...";
		xCH__OBJ_MSG->Set__DATA(str_msg);

		msg.Format("WAP CONDUCT : %s",str_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);

		//
		pOBJ_CTRL__WAP->Dislink__UPPER_OBJECT();

		pOBJ_CTRL__WAP->Call__OBJECT("UP");

		pOBJ_CTRL__WAP->Link__UPPER_OBJECT();
	}

	// ...
	{
		str_msg = "High Vac Pumping Started ...";
		xCH__OBJ_MSG->Set__DATA(str_msg);

		msg.Format("WAP CONDUCT : %s",str_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);

		//
		pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();

		pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP);

		pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
	}

	xCH__OBJ_MSG->Set__DATA("");

	return flag;
}

int CObj__WAP_POS_CONDUCT::
Fnc__POS_CONDUCT(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm)
{	
	// ...
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
			if(flag < 0)		return flag;
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
			if(flag < 0)		return flag;
		}
	}

	// SPEC TEST ...
	if(dCH_CFG__WAP_SPEC_TEST__APPLY_MODE->Check__DATA(STR__ENABLE) > 0)
	{	
		aCH_CFG__WAP_SPEC_TEST__GAS_FLOW;
		aCH_CFG__WAP_SPEC_TEST__POSITION;
		aCH_CFG__WAP_SPEC_TEST__PRESSURE_MIN;
		aCH_CFG__WAP_SPEC_TEST__PRESSURE_MAX;
		aCH_CFG__WAP_SPEC_TEST__STABLE_TIME;
		aCH_CFG__WAP_SPEC_TEST__CHECK_TIME;
	}

	if(flag > 0)
	{
		sEXT_CH__CHM_PM_ITEM__WAP_CONDUCTANCE_FLAG->Set__DATA("");

		// ...
		{
			int alarm_id = ALID__WAP_CONDUCTANCE_CHECK_COMPLETE;
			CString r_act;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
		}
	}

	return 1;
}
int CObj__WAP_POS_CONDUCT::
Fnc__LOWER_POS_CONDUCT(CII_OBJECT__VARIABLE *p_variable,
					   CII_OBJECT__ALARM *p_alarm,
					   const CString& vlv_pos,
					   const CString& gas_name,
					   const CString& gas_flow,
					   const int db_index)
{
	CString var_data;
	CString str_msg;
	CString msg;


	if(db_index == 0)
	{
		// 1. WAP Init
		{
			str_msg = "WAP Init - Started ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			//
			if(pOBJ_CTRL__WAP->Call__OBJECT("INIT") < 0)
			{
				str_msg = "WAP Init - Aborted ...";
				xCH__OBJ_MSG->Set__DATA(str_msg);

				msg.Format("WAP CONDUCT : %s",str_msg);
				sEXT_CH__FNC_MSG->Set__DATA(msg);
				return -11;
			}

			//
			str_msg = "WAP Init - Completed ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		// 2. Base Pumping
		{
			str_msg = "High VAC - Pumping Started ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);

			//
			sEXT_CH__DGF_CENTER_WT_SP->Set__DATA("50");

			if(pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP) < 0)
			{
				str_msg = "High VAC - Pumping Aborted ...";
				xCH__OBJ_MSG->Set__DATA(str_msg);

				msg.Format("WAP CONDUCT : %s",str_msg);
				sEXT_CH__FNC_MSG->Set__DATA(msg);
				return -12;
			}

			sEXT_CH__DGF_CENTER_WT_SP->Set__DATA("50");
		}
	}

	// 2. MFC Flow
	{	
		dEXT_CH__FNC_MFC__PARA_MFC_TYPE->Set__DATA(gas_name);
		aEXT_CH__FNC_MFC__PARA_MFC_FLOW->Set__DATA(gas_flow);

		//
		{
			str_msg.Format("MFC Control - Started : (%s) <- (%s)", gas_name,gas_flow);
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		if(pOBJ_CTRL__FNC_MFC->Call__OBJECT(CMMD_MODE__FNC_MFC__MFC_CONTROL) < 0)
		{
			str_msg = "MFC Control - Aborted ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -2;
		}

		//
		{
			str_msg = "MFC Control - Completed ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}
	}

	// 3. Flow Delay Sec
	{
		SCX__TIMER_CTRL x_timer_ctrl;

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH_PARA__CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		double cfg__delay_sec;
		aCH_CFG__FLOW_DELAY_SEC->Get__DATA(var_data);
		cfg__delay_sec = atof(var_data);

		//
		{
			str_msg.Format("Flow Delay - Started ...  (%s) sec", var_data);
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			str_msg = "Flow Delay - Aborted ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -3;
		}
	}

	// 4. WAP Ctrl
	{
		//
		{
			str_msg = "WAP Control - Started ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		//
		aEXT_CH__PARA_PRESET_POS->Set__DATA("0");
		aEXT_CH__PARA_TRG_POS->Set__DATA(vlv_pos);
		dEXT_CH__PARA_CONTROL_TYPE->Set__DATA("Position");

		if(pOBJ_CTRL__WAP->Call__OBJECT(CMMD_MODE__VAT_CONTROL) < 0)
		{
			str_msg = "WAP Control - Aborted ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -2;
		}

		//
		{
			str_msg = "WAP Control - Completed ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}
	}

	//.....
	double set__vlv_pos = atof(vlv_pos);

	// 5. Pressure Stable Time
	// if(set__vlv_pos > 0)
	{
		SCX__TIMER_CTRL x_timer_ctrl;

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH_PARA__CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		double cfg__delay_sec;
		aCH_CFG__PRESSURE_STABLE_DELAY_SEC->Get__DATA(var_data);
		cfg__delay_sec = atof(var_data);

		//
		{
			str_msg.Format("Pressure Stable Time - (%s) sec", var_data);
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			str_msg = "Pressure Stable Time - Aborted ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -3;
		}
	}

	// 6. Result Check
	// if(set__vlv_pos > 0)
	{
		double cur_result;
		double cur_press;
		double cur_flow = atof(gas_flow);

		//.....
		{
			int check_count = 0;

			// ...
RETRY_PRESSURE:

			// Pressure
			sEXT_CH__CHM_PRESSURE->Get__DATA(var_data);
			sCH_PARA__CUR_PRESS_LIST[db_index]->Set__DATA(var_data);
			cur_press = atof(var_data) * 1000.0;		// mtorr

			if(cur_press < 1.0)
			{
				check_count++;

				if(check_count < 5)
				{
					Sleep(90);

					goto RETRY_PRESSURE;
				}

				// ...
				{
					// ...
					{
						str_msg = "Pressure Reading - Error !";
						xCH__OBJ_MSG->Set__DATA(str_msg);
					}

					// ...
					{
						int alarm_id = ALID__PRESSURE_READ_ERROR;
						CString alm_msg;
						CString r_act;

						alm_msg.Format("Step[%1d] - Pressure Error !", db_index+1);

						p_alarm->Check__ALARM(alarm_id,r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
					}
				}
				return -1;
			}

			// Result
			if(cur_press >= 0.1)
			{
				cur_result = cur_flow / cur_press;
				var_data.Format("%.3f", cur_result);
				
				sCH_NEW__CONDUCT_RESULT[db_index]->Set__DATA(var_data);
			}
			else
			{
				cur_result = 100.0;
				
				sCH_NEW__CONDUCT_RESULT[db_index]->Set__DATA("***");
			}

			//
			CString cur_data;
			CString add_data;

			add_data.Format("%.3f/%.3f,", atof(vlv_pos), cur_result);

			sCH__RESULT_NEW_STRING->Get__DATA(cur_data);
			cur_data += add_data;
			sCH__RESULT_NEW_STRING->Set__DATA(cur_data);
		}
	}
	
	return 1;
}
int CObj__WAP_POS_CONDUCT::
Fnc__SPEC_TEST(CII_OBJECT__VARIABLE *p_variable,
			   CII_OBJECT__ALARM *p_alarm)
{
	//.....
	CString var_data;
	CString str_msg;


	// 1. Base Pumping
	{
		// 
		{
			str_msg = "SPEC TEST : High VAC - Pumping Started ...";
		
			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
		}

		//
		if(pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP) < 0)
		{
			str_msg = "High VAC - Pumping Aborted ...";
			
			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
			return -11;
		}
	}

	// 2. WAP -> '0' Position
	{
		//
		{
			str_msg = "SPEC TEST : WAP Control - Started ...";

			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
		}
		
		//
		aEXT_CH__PARA_PRESET_POS->Set__DATA("0");
		aEXT_CH__PARA_TRG_POS->Set__DATA("0");
		dEXT_CH__PARA_CONTROL_TYPE->Set__DATA("Position");
		
		if(pOBJ_CTRL__WAP->Call__OBJECT(CMMD_MODE__VAT_CONTROL) < 0)
		{
			str_msg = "SPEC TEST : WAP Control - Aborted ...";

			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
			return -12;
		}
		
		//
		{
			str_msg = "SPEC TEST : WAP Control - Completed ...";

			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
		}
	}
	
	// 3. MFC Flow
	{	
		CString gas_name;
		CString gas_flow;

		// 
		dCH_PARA__TEST_GAS_TYPE->Get__DATA(gas_name);
		aCH_CFG__WAP_SPEC_TEST__GAS_FLOW->Get__DATA(gas_flow);

		dEXT_CH__FNC_MFC__PARA_MFC_TYPE->Set__DATA(gas_name);
		aEXT_CH__FNC_MFC__PARA_MFC_FLOW->Set__DATA(gas_flow);

		//
		{
			str_msg.Format("SPEC TEST : MFC Control - Started  \"(%s) <- (%s)\" ", gas_name,gas_flow);

			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
		}

		if(pOBJ_CTRL__FNC_MFC->Call__OBJECT(CMMD_MODE__FNC_MFC__MFC_CONTROL) < 0)
		{
			str_msg = "SPEC TEST : MFC Control - Aborted ...";
			
			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
			return -13;
		}

		//
		{
			str_msg = "SPEC TEST : MFC Control - Completed ...";
			
			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
		}
	}

	// 4. Flow Delay Sec
	{
		SCX__TIMER_CTRL x_timer_ctrl;

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH_PARA__CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		double cfg__delay_sec;
		aCH_CFG__FLOW_DELAY_SEC->Get__DATA(var_data);
		cfg__delay_sec = atof(var_data);

		//
		{
			str_msg.Format("SPEC TEST : Flow Delay - Started ...  (%s) sec", var_data);

			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
		}

		if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			str_msg = "SPEC TEST : Flow Delay - Aborted ...";

			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
			return -14;
		}
	}

	// 5. WAP Ctrl
	{
		//
		{
			str_msg = "SPEC TEST : WAP Control - Started ...";

			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
		}

		//
		CString vlv_pos;
		aCH_CFG__WAP_SPEC_TEST__POSITION->Get__DATA(vlv_pos);

		aEXT_CH__PARA_PRESET_POS->Set__DATA("0");
		aEXT_CH__PARA_TRG_POS->Set__DATA(vlv_pos);
		dEXT_CH__PARA_CONTROL_TYPE->Set__DATA("Position");

		if(pOBJ_CTRL__WAP->Call__OBJECT(CMMD_MODE__VAT_CONTROL) < 0)
		{
			str_msg = "SPEC TEST : WAP Control - Aborted ...";

			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
			return -15;
		}

		//
		{
			str_msg = "SPEC TEST : WAP Control - Completed ...";

			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
		}
	}

	// 6. Pressure Stable Time
	{
		SCX__TIMER_CTRL x_timer_ctrl;

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH_PARA__CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		double cfg__delay_sec;
		aCH_CFG__WAP_SPEC_TEST__STABLE_TIME->Get__DATA(var_data);	
		cfg__delay_sec = atof(var_data);

		//
		{
			str_msg.Format("SPEC TEST : Pressure Stable Time - (%s) sec", var_data);

			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
		}

		if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			str_msg = "SPEC TEST : Pressure Stable Time - Aborted ...";
		
			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
			return -16;
		}
	}

	// 7. Pressure Check Time
	{
		SCX__ASYNC_TIMER_CTRL x_async_timer;		

		x_async_timer->START__COUNT_UP(9999);
		x_async_timer->REGISTER__COUNT_CHANNEL_NAME(sCH_PARA__CHECK_TIME_COUNT->Get__CHANNEL_NAME());
		
		// ...
		double cfg__delay_sec;
		aCH_CFG__WAP_SPEC_TEST__CHECK_TIME->Get__DATA(var_data);	
		cfg__delay_sec = atof(var_data);
		
		//
		{
			str_msg.Format("SPEC TEST : Pressure Check Time - (%s) sec", var_data);
			
			xCH__OBJ_MSG->Set__DATA(str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(str_msg);
		}
		
		//
		double cur__chm_press;

		aCH_CFG__WAP_SPEC_TEST__PRESSURE_MIN->Get__DATA(var_data);
		double cfg__press_min = atof(var_data);

		aCH_CFG__WAP_SPEC_TEST__PRESSURE_MAX->Get__DATA(var_data);
		double cfg__press_max = atof(var_data);


		while(1)
		{
			// ...
			sEXT_CH__CHM_PRESSURE->Get__DATA(var_data);
			cur__chm_press = atof(var_data) * 1000.0;			// mtorr

			if((cur__chm_press < cfg__press_min)
			|| (cur__chm_press > cfg__press_max))	
			{
				// ...
				{
					str_msg = "SPEC TEST : Pressure Check Time - Pressure Range Error ...";
					
					xCH__OBJ_MSG->Set__DATA(str_msg);
					sEXT_CH__FNC_MSG->Set__DATA(str_msg);
				}

				return -21;	
			}

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				// ...
				{
					str_msg = "SPEC TEST : Pressure Check Time - Aborted by upper-object ...";
					
					xCH__OBJ_MSG->Set__DATA(str_msg);
					sEXT_CH__FNC_MSG->Set__DATA(str_msg);
				}

				return -22;
			}

			if(x_async_timer->Get__CURRENT_TIME() > cfg__delay_sec)
			{
				// ...
				{
					str_msg = "SPEC TEST : Pressure Check Time - Completed ...";
					
					xCH__OBJ_MSG->Set__DATA(str_msg);
					sEXT_CH__FNC_MSG->Set__DATA(str_msg);
				}

				break;
			}


			// ...
			{
				Sleep(10);
			}
		}
	}
	
	return 1;
}

int CObj__WAP_POS_CONDUCT::
Call__DATA_SIM(CII_OBJECT__VARIABLE *p_variable,
			   CII_OBJECT__ALARM *p_alarm)
{
	// ...
	CStringArray l_data;
	CString str_data1;
	CString str_data2;
	CString var_data;
	
	int limit;
	int i;

	CStringArray l__cur_x;
	CStringArray l__cur_y;
	
	// ...
	{
		//
		sCH__RESULT_CUR_STRING->Get__DATA(var_data);
		Macro__Convert_String_To_Array(var_data, l_data);

		//
		limit = l_data.GetSize();

		for(i=0;i<limit;i++)
		{
			var_data = l_data[i];
			Macro__Convert_String_To_String(var_data, str_data1,str_data2);

			l__cur_x.Add(str_data1);
			l__cur_y.Add(str_data2);
		}
	}

	// ...
	{
		aEXT_CH__CFG_C_Ring_Offset_Move->Get__DATA(var_data);
		double  move_offset = atof(var_data);

		// 
		CString new_data;
		double  cur_x;
		double  new_x;
		double  new_y;

		limit = l__cur_x.GetSize();

		/*
		for(i=0;i<limit;i++)
		{
			new_x = atof(l__cur_x[i]) + move_offset;
			new_y = atof(l__cur_y[i]);

			if(new_x > 1000)		new_x = 1000;
			if(new_x < 0)			new_x = 0;

			var_data.Format("%.3f/%.3f,", new_x,new_y);
			new_data += var_data;
		}
		*/
		
		for(i=0;i<limit;i++)
		{
			cur_x = atof(l__cur_x[i]);
			new_x = cur_x - move_offset;
			
			if(new_x < 0)		new_x = 0;
			if(new_x > 1000)	new_x = 1000;

			new_y = Fnc__GET_DATA_FROM_LOOKUP_TABLE(new_x, l__cur_x,l__cur_y);

			var_data.Format("%.3f", new_y);
			sCH_NEW__CONDUCT_RESULT[i]->Set__DATA(var_data);

			var_data.Format("%.3f/%.3f,", cur_x,new_y);
			new_data += var_data;
		}

		for(i=limit;i<CFG__TEST_LIST;i++)
		{
			sCH_NEW__CONDUCT_RESULT[i]->Set__DATA("");
		}

		sCH__RESULT_NEW_STRING->Set__DATA(new_data);
	}
	
	return 1;
}

double CObj__WAP_POS_CONDUCT::
Fnc__GET_DATA_FROM_LOOKUP_TABLE(const double x_pos,
								const CStringArray& l_x,
								const CStringArray& l_y)
{
	// ...
	double y_pos = 0;

	// ...
	double cur_x1;
	double cur_x2;

	double cur_y1;
	double cur_y2;

	int limit = l_x.GetSize();
	int i;
	
	for(i=0;i<limit-1;i++)
	{
		cur_x1 = atof(l_x[i]);
		cur_x2 = atof(l_x[i+1]);

		cur_y1 = atof(l_y[i]);
		cur_y2 = atof(l_y[i+1]);

		if((x_pos >= cur_x1)
		&& (x_pos <= cur_x2))
		{
			if((cur_x2 - cur_x1) > 1)
			{
				y_pos = (cur_y2 - cur_y1) * ((x_pos - cur_x1) / (cur_x2 - cur_x1)) + cur_y1;
			}
			else
			{
				y_pos = (cur_y2 - cur_y1) * (x_pos - cur_x1) + cur_y1;
			}
		}
	}

	return (y_pos);
}

int  CObj__WAP_POS_CONDUCT::
Fnc__SIM_MOVE_CAL(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	int    r_result;
	double r_x_err;
	double r_y_err;

	//
	return Fnc__SIM_MOVE_CAL(p_variable,p_alarm, -1,r_result,r_x_err,r_y_err);
}
int  CObj__WAP_POS_CONDUCT::
Fnc__SIM_MOVE_CAL(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm,
				  const int scan_flag,
				  int& r_result,
				  double& r_x_err,
				  double& r_y_err)
{
	// ...
	{
		r_result = -1;

		r_x_err = 0;
		r_y_err = 0;
	}

	// ...
	if(scan_flag < 0)
	{
		CString err_msg = "Range Checking ...";
		sCH__RESULT_MSG->Set__DATA(err_msg);
	}

	// ...
	CStringArray l_data;
	CString str_data1;
	CString str_data2;
	CString var_data;
	
	int limit;
	int i;
	
	// ...
	CStringArray l__new_x;
	CStringArray l__new_y;
	CStringArray l__cur_x;
	CStringArray l__cur_y;
	CStringArray l__sim_x;
	CStringArray l__sim_y;

	double x__err_max = -1.0;
	double y__err_max =  0.0;


	// ...
	{
		//
		sCH__RESULT_NEW_STRING->Get__DATA(var_data);
		
		Macro__Convert_String_To_Array(var_data, l_data);
		
		//
		limit = l_data.GetSize();
		
		for(i=0;i<limit;i++)
		{
			var_data = l_data[i];
			Macro__Convert_String_To_String(var_data, str_data1,str_data2);
			
			l__new_x.Add(str_data1);
			l__new_y.Add(str_data2);
		}
	}
	
	// ...
	{
		//
		if(dCH__SIM_MOVE_DATA_TYPE->Check__DATA(STR__REF) > 0)
		{
			sCH__REF_STRING->Get__DATA(var_data);
		}
		else
		{
			sCH__RESULT_CUR_STRING->Get__DATA(var_data);
		}
		
		Macro__Convert_String_To_Array(var_data, l_data);
		
		//
		limit = l_data.GetSize();
		
		for(i=0;i<limit;i++)
		{
			var_data = l_data[i];
			Macro__Convert_String_To_String(var_data, str_data1,str_data2);
			
			l__cur_x.Add(str_data1);
			l__cur_y.Add(str_data2);
		}
	}
	
	// ...
	{
		aCH__SIM_MOVE_OFFSET->Get__DATA(var_data);
		double  move_offset = atof(var_data);
		
		// 
		CString str_x;
		CString str_y;
		CString new_data;

		double  cur_x;
		double  new_x;
		double  new_y;
		
		limit = l__cur_x.GetSize();
		
		if(dCH__SIM_MOVE_LOOKUP->Check__DATA(STR__YES) < 0)
		{
			for(i=0;i<limit;i++)
			{
				new_x = atof(l__cur_x[i]) + move_offset;
				new_y = atof(l__cur_y[i]);
			
				if(new_x < 0)			new_x = 0;
				if(new_x > 1000)		new_x = 1000;

				if(i < CFG__TEST_LIST)
				{
					var_data.Format("%.3f", new_y);
					sCH_SIM__CONDUCT_RESULT[i]->Set__DATA(var_data);
				}

				var_data.Format("%.3f/%.3f,", new_x,new_y);
				new_data += var_data;

				//
				str_x.Format("%.3f", new_x);
				str_y.Format("%.3f", new_y);

				l__sim_x.Add(str_x);
				l__sim_y.Add(str_y);
			}

			for(i=limit;i<CFG__TEST_LIST;i++)
			{
				sCH_SIM__CONDUCT_RESULT[i]->Set__DATA("");
			}
		}
		else
		{
			for(i=0;i<limit;i++)
			{
				cur_x = atof(l__cur_x[i]);
				new_x = cur_x - move_offset;

				if(new_x < 0)			new_x = 0;
				if(new_x > 1000)		new_x = 1000;
			
				new_y = Fnc__GET_DATA_FROM_LOOKUP_TABLE(new_x, l__cur_x,l__cur_y);

				if(i < CFG__TEST_LIST)
				{
					var_data.Format("%.3f", new_y);
					sCH_SIM__CONDUCT_RESULT[i]->Set__DATA(var_data);
				}

				var_data.Format("%.3f/%.3f,", cur_x,new_y);
				new_data += var_data;

				//
				str_x.Format("%.3f", cur_x);
				str_y.Format("%.3f", new_y);
				
				l__sim_x.Add(str_x);
				l__sim_y.Add(str_y);
			}

			for(i=limit;i<CFG__TEST_LIST;i++)
			{
				sCH_SIM__CONDUCT_RESULT[i]->Set__DATA("");
			}
		}

		// 
		sCH__RESULT_MOVE_STRING->Set__DATA(new_data);
	}

	// ...
	{
		aCH__SIM_MOVE_ERROR_RANGE->Get__DATA(var_data);
		double cfg__err_range = atof(var_data);

		aCH__SIM_MOVE_ERROR_X_MIN->Get__DATA(var_data);
		int cfg__err_x_min = atoi(var_data);

		aCH__SIM_MOVE_ERROR_X_MAX->Get__DATA(var_data);
		int cfg__err_x_max = atoi(var_data);

		// 
		int sim__pos_x;
		double sim__data;
		double sim__min;
		double sim__max;
		double cur__data;
		double err__data;

		//
		CStringArray l__err_pos;
		CStringArray l__err_dev;
		int err_flag = -1;

		//
		limit = l__cur_y.GetSize();
		l__cur_x.SetSize(limit);

		l__new_x.SetSize(limit);
		l__new_y.SetSize(limit);

		l__sim_x.SetSize(limit);
		l__sim_y.SetSize(limit);

		for(i=0;i<limit;i++)
		{
			//
			sim__pos_x = atoi(l__sim_x[i]);

			if(sim__pos_x < cfg__err_x_min)		continue;
			if(sim__pos_x > cfg__err_x_max)		continue;

			//
			sim__data = atof(l__sim_y[i]);
			sim__min  = sim__data - cfg__err_range;
			sim__max  = sim__data + cfg__err_range;

			cur__data = atof(l__new_y[i]);
			err__data = sim__data - cur__data;

			if((cur__data < sim__min)
			|| (cur__data > sim__max))
			{
				err_flag = 1;

				//
				var_data.Format("%.3f", (sim__data - cur__data));
				l__err_pos.Add(l__sim_x[i]);
				l__err_dev.Add(var_data);
			}
			else
			{
				double bff_err = err__data;
				
				if(bff_err < 0)
				{
					bff_err = - bff_err;
				}

				// 
				if(x__err_max < 0)
				{
					x__err_max = sim__pos_x;
					y__err_max = bff_err;
				}
				else
				{
					if(err__data > y__err_max)
					{
						x__err_max = sim__pos_x;
						y__err_max = bff_err;
					}
				}
			}
		}

		// Alarm - Range Error !
		if(err_flag > 0)
		{
			// ...
			if(scan_flag < 0)
			{
				CString err_msg = "Range Error !";
				sCH__RESULT_MSG->Set__DATA(err_msg);
			}

			// ...
			if(scan_flag < 0)
			{
				int alarm_id = ALID__SIM_RANGE_ERROR;
				CString alm_msg;
				CString alm_bff;
				CString r_act;
			
				int k_limit = l__err_pos.GetSize();
				int k;

				for(k=0;k<k_limit;k++)
				{
					alm_bff.Format("%1d)  [%s] : [%s] \n", k+1,l__err_pos[k],l__err_dev[k]);
					alm_msg += alm_bff;
				}

				p_alarm->Clear__ALARM(alarm_id);
				p_alarm->Check__ALARM(alarm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
			}
			return -1;
		}
	}

	// ...
	if(scan_flag < 0)
	{
		CString err_msg;
		
		if(x__err_max >= 0)
		{
			err_msg.Format("Range OK !  : Max Error Point (%.0f, %.3f)", 
						   x__err_max, 
						   y__err_max);
		}
		else
		{
			err_msg.Format("Range OK !");
		}

		sCH__RESULT_MSG->Set__DATA(err_msg);
	}

	// ...
	{
		r_result = 1;
		
		r_x_err = x__err_max;
		r_y_err = y__err_max;
	}

	return 1;
}

int  CObj__WAP_POS_CONDUCT::
Fnc__SIM_SCAN_CAL(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	// ...
	int scan_flag = -1;
	int scan__offset_min = 0;
	int scan__offset_max = 0;
	int scan__offset_pos = 0;
	double x__err_min = 0;
	double y__err_min = 0;

	int scan_pos;
	int r_result;
	double r_x_err;
	double r_y_err;
	CString var_data;

	int limit = 100;
	int s_i = -100;
	int i;


	for(i=s_i;i<limit;i++)
	{
		scan_pos = i+1;

		// ...
		{
			CString err_msg;
			
			err_msg.Format("Scan Pos (%1d) Checking ...", scan_pos);
			sCH__RESULT_MSG->Set__DATA(err_msg);
		}

		var_data.Format("%1d", scan_pos);
		aCH__SIM_MOVE_OFFSET->Set__DATA(var_data);
		
		Fnc__SIM_MOVE_CAL(p_variable,p_alarm, 1,r_result,r_x_err,r_y_err);

		if(r_result > 0)
		{
			if(scan_flag < 0)
			{
				scan_flag = 1;
				
				scan__offset_min = scan_pos;
				scan__offset_max = scan_pos;

				scan__offset_pos = scan_pos;
				x__err_min = r_x_err;
				y__err_min = r_y_err;
			}
			else
			{
				scan__offset_max = scan_pos;

				if(r_y_err < y__err_min)
				{
					scan__offset_pos = scan_pos;

					x__err_min = r_x_err;
					y__err_min = r_y_err;
				}
			}

			// ...
			{
				CString err_msg;
				
				err_msg.Format("Scan Pos (%1d) : Range OK ...", scan_pos);
				sCH__RESULT_MSG->Set__DATA(err_msg);
			}
		}
		else
		{
			// ...
			{
				CString err_msg;
				
				err_msg.Format("Scan Pos (%1d) : Range Error ...", scan_pos);
				sCH__RESULT_MSG->Set__DATA(err_msg);
			}
		}
		
		Sleep(10);
	}

	if(scan_flag > 0)
	{
		// ...
		{
			var_data.Format("%1d", scan__offset_pos);
			aCH__SIM_MOVE_OFFSET->Set__DATA(var_data);
		
			Fnc__SIM_MOVE_CAL(p_variable,p_alarm, 1,r_result,r_x_err,r_y_err);
		}

		// ...
		{
			CString err_msg;
			
			err_msg.Format("OK : Offset Range(%1d,%1d), Selected Offset(%1d) & Max Error(%.0f,%.3f)",
				           scan__offset_min,
						   scan__offset_max,
						   scan__offset_pos,
						   x__err_min,
						   y__err_min);
		
			sCH__RESULT_MSG->Set__DATA(err_msg);
		}

		// ...
		{
			int alarm_id = ALID__WAP_CONDUCTANCE__AUTO_OFFSET_CHECK__OK;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			alm_msg = "Auto Scan Result : \n";

			alm_bff.Format("   Selected Offset Position : %1d \n", scan__offset_pos);
			alm_msg += alm_bff;

			alm_bff.Format("   Max. Error Point (x, y) : (%.0f, %.3f) \n", x__err_min,y__err_min);
			alm_msg += alm_bff;

			alm_bff.Format("   Offset SPEC. In Range (min, max) : (%1d, %1d) \n", scan__offset_min,scan__offset_max);
			alm_msg += alm_bff;

			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alm_msg,r_act);

			if(r_act.CompareNoCase(STR__YES) == 0)
			{
				var_data.Format("%1d", scan__offset_pos);
				aEXT_CH__CFG_C_Ring_Offset_Move->Set__DATA(var_data);
			}

			return 1;
		}
	}
	else
	{
		// ...
		{
			CString err_msg;
			
			err_msg.Format("Scan Range Error");
			
			sCH__RESULT_MSG->Set__DATA(err_msg);
		}

		// ...
		{
			int alarm_id = ALID__WAP_CONDUCTANCE__AUTO_OFFSET_CHECK__ERROR;
			CString r_act;
		
			p_alarm->Popup__ALARM(alarm_id,r_act);
		}
	}

	return -1;
}

int CObj__WAP_POS_CONDUCT::
Call__PULSE_SCAN(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm)
{
	CString str_msg;
	CString fnc_msg;
	CString var_data;
	int flag = 1;

	// WAP Initialize ...
	{
		int req__wap_init = 1;

		// ...
		{
			CString str_title;
			CString str_message;
			CStringArray l_act;
			CString r_act;

			str_title = "WAP를 초기화 할까요?";
			
			str_message  = "초기화를 원하면, [YES]를 CLICK하시고, \n";
			str_message += "초기화를 원하지 않으면, [NO]를 CLICK하세요. \n";

			l_act.RemoveAll();
			l_act.Add(STR__YES);
			l_act.Add(STR__NO);

			p_alarm->Popup__MESSAGE_BOX(str_title,str_message,l_act,r_act);
	
			if(r_act.CompareNoCase(STR__YES) == 0)		req__wap_init =  1;
			else										req__wap_init = -1;
		}

		if(req__wap_init > 0)
		{
			// ...
			{
				str_msg = "WAP Init - Started ...";
				xCH__OBJ_MSG->Set__DATA(str_msg);
				
				fnc_msg.Format("WAP CONDUCT : %s", str_msg);
				sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
			}
			
			if(pOBJ_CTRL__WAP->Call__OBJECT(CMMD_MODE__WAP_INIT) < 0)
			{
				// ...
				{
					str_msg = "WAP Init - Aborted ...";
					xCH__OBJ_MSG->Set__DATA(str_msg);
					
					fnc_msg.Format("WAP CONDUCT : %s", str_msg);
					sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
				}
				return -11;
			}
				
			// ...
			{
				str_msg = "WAP Init - Completed ...";
				xCH__OBJ_MSG->Set__DATA(str_msg);
				
				fnc_msg.Format("WAP CONDUCT : %s", str_msg);
				sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
			}
		}
	}

	// Base Pumping Initialize ...
	{
		int req__base_pumping = 1;
		
		// ...
		{
			CString str_title;
			CString str_message;
			CStringArray l_act;
			CString r_act;
			
			str_title = "Base pumping을 수행 할까요?";
			
			str_message  = "Base Pupming을 원하면, [YES]를 CLICK하시고, \n";
			str_message += "Base Pumpingmf 원하지 않으면, [NO]를 CLICK하세요. \n";
			
			l_act.RemoveAll();
			l_act.Add(STR__YES);
			l_act.Add(STR__NO);
			
			p_alarm->Popup__MESSAGE_BOX(str_title,str_message,l_act,r_act);
			
			if(r_act.CompareNoCase(STR__YES) == 0)		req__base_pumping =  1;
			else										req__base_pumping = -1;
		}
		
		if(req__base_pumping > 0)
		{
			// ...
			{
				str_msg = "High VAC - Pumping Started ...";
				xCH__OBJ_MSG->Set__DATA(str_msg);
			
				fnc_msg.Format("WAP CONDUCT : %s",str_msg);
				sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
			}
			
			sEXT_CH__DGF_CENTER_WT_SP->Set__DATA("50");
			
			if(pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP) < 0)
			{
				// ...
				{
					str_msg = "High VAC - Pumping Aborted ...";
					xCH__OBJ_MSG->Set__DATA(str_msg);
				
					fnc_msg.Format("WAP CONDUCT : %s",str_msg);
					sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
				}
				return -21;
			}
		}

		sEXT_CH__DGF_CENTER_WT_SP->Set__DATA("50");
	}

	// MFC Flow Control ...
	{	
		CString gas_name;
		CString gas_flow;

		dCH_PARA__TEST_GAS_TYPE->Get__DATA(gas_name);
		aCH_PARA__TEST_GAS_FLOW->Get__DATA(gas_flow);

		dEXT_CH__FNC_MFC__PARA_MFC_TYPE->Set__DATA(gas_name);
		aEXT_CH__FNC_MFC__PARA_MFC_FLOW->Set__DATA(gas_flow);

		// ...
		{
			str_msg.Format("MFC Control - Started : (%s) <- (%s)", gas_name,gas_flow);
			xCH__OBJ_MSG->Set__DATA(str_msg);

			fnc_msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}

		if(pOBJ_CTRL__FNC_MFC->Call__OBJECT(CMMD_MODE__FNC_MFC__MFC_CONTROL) < 0)
		{
			// ...
			{
				str_msg = "MFC Control - Aborted ...";
				xCH__OBJ_MSG->Set__DATA(str_msg);

				fnc_msg.Format("WAP CONDUCT : %s",str_msg);
				sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
			}
			return -2;
		}

		// ...
		{
			str_msg = "MFC Control - Completed ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			fnc_msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}
	}

	// 3. Flow Delay Sec
	{
		SCX__TIMER_CTRL x_timer_ctrl;

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH_PARA__CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		double cfg__delay_sec;
		aCH_CFG__FLOW_DELAY_SEC->Get__DATA(var_data);
		cfg__delay_sec = atof(var_data);

		// ...
		{
			str_msg.Format("Flow Delay - Started ...  (%s) sec", var_data);
			xCH__OBJ_MSG->Set__DATA(str_msg);

			fnc_msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}

		if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			// ...
			{
				str_msg = "Flow Delay - Aborted ...";
				xCH__OBJ_MSG->Set__DATA(str_msg);

				fnc_msg.Format("WAP CONDUCT : %s",str_msg);
				sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
			}
			return -3;
		}
	}

	// 4. WAP Ctrl
	{
		flag = 	pOBJ_CTRL__WAP->Call__OBJECT(CMMD_MODE__WAP_PULSE_SCAN);	
	}

	// ...
	{
		// ...
		{
			str_msg = "MFC All Closed ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);
		
			fnc_msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}

		pOBJ_CTRL__FNC_MFC->Dislink__UPPER_OBJECT();
		
		aEXT_CH__FNC_MFC__PARA_MFC_FLOW->Set__DATA("0");
		pOBJ_CTRL__FNC_MFC->Call__OBJECT(CMMD_MODE__FNC_MFC__MFC_CONTROL);
		pOBJ_CTRL__FNC_MFC->Call__OBJECT(CMMD_MODE__FNC_MFC__ALL_CLOSE);
		
		pOBJ_CTRL__FNC_MFC->Link__UPPER_OBJECT();
	}
	
	// ...
	{
		// ...
		{
			str_msg = "WAP Up Started ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);
		
			fnc_msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}

		pOBJ_CTRL__WAP->Dislink__UPPER_OBJECT();
		
		pOBJ_CTRL__WAP->Call__OBJECT(CMMD_MODE__WAP_UP);
		
		pOBJ_CTRL__WAP->Link__UPPER_OBJECT();
	}
	
	// ...
	{
		// ...
		{
			str_msg = "High Vac Pumping Started ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);
		
			fnc_msg.Format("WAP CONDUCT : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(fnc_msg);
		}

		pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();
		
		pOBJ_CTRL__CHM->Call__OBJECT(CMMD_MODE__CHM_HIGH_VAC_PUMP);
		
		pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
	}
	
	xCH__OBJ_MSG->Set__DATA("");
	return flag;
}
