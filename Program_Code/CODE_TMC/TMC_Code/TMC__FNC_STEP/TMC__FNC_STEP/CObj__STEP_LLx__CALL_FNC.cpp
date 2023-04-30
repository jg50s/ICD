#include "StdAfx.h"
#include "CObj__STEP_LLx.h"
#include "CObj__STEP_LLx__DEF.h"

extern int  Macro__Get_Step_Data(const int step_id,const CString& in_data,CString& step_data);


//-------------------------------------------------------------------------
int CObj__STEP_LLx
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,
		     CII_OBJECT__ALARM* p_alarm)
{
	/*
	// ...
	{
		sCH__HE_DECHUCK__RESULT_FLAG->Set__DATA(STR__CHECKING);
		sCH__HE_DECHUCK__CTRL_REQ->Set__DATA(STR__START);

		while(1)
		{
			Sleep(10);

			if(sCH__HE_DECHUCK__RESULT_FLAG->Check__DATA(STR__CHECKING) < 0)
			{
				break;
			}
			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				sCH__HE_DECHUCK__CTRL_REQ->Set__DATA(STR__STOP);
				return -1;
			}
		}

		if(sCH__HE_DECHUCK__RESULT_FLAG->Check__DATA(STR__OK) > 0)
		{
			return 1;
		}
		else
		{
			int alarm_id = ALID__HE_DECHUCK__INIT_ERROR;
			CString r_act;

			p_alarm->Popup__ALARM(alarm_id,r_act);

			if(r_act.CompareNoCase(STR__IGNORE) == 0)
			{
				return 1;
			}
		}
		return -1;
	}
	*/

	return 1;
}

int CObj__STEP_LLx
::Call__RCP_DATA_INIT(CII_OBJECT__VARIABLE* p_variable,
					  CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		sCH__LEARNED_APPLY_STATUS->Set__DATA("Idle ...");
	}
		
	// ...
	{
		aCH__RCP_MON_STEP_NO->Set__DATA("1");
		sEXT_CH__LAST_STEP_FLAG->Set__DATA("");

		sCH__STEP_TIME_ABORT_FLAG->Set__DATA("");
	}
			
	// ...
	{
		Fnc__INIT_PART_ERROR(p_variable, p_alarm);
		Init__PRE_RCP_ITEM();
	}
			
	mDB__LEARNED_ITEM_CTRL.Init__ALL_ITEM();
	return 1;
}

int CObj__STEP_LLx
::Call__READY(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;
	CString ch_data;

	// ...
	{
		sCH__OBJ_MSG->Set__DATA("Ready : Start ...");
	}

	// ...
	{
		aCH__RCP_FDC_STEP_TIME->Set__DATA("0");
	}

	/*
	// ...
	{
		log_msg = "Ballast End : Call Start ...";
		xLOG_CTRL->WRITE__LOG(log_msg);
		
		// ...
		{
			sCH__OBJ_SUB_MSG->Set__DATA("Call__Ready() : Balast End ...");
			
			sCH__XFER_BALLAST_CTRL_FLAG->Set__DATA("");
			pOBJ_CTRL__CHM->Call__OBJECT(CMMD__BALLAST_END);
		}

		log_msg = "Ballast End : Call End ...";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	*/

	// ...
	{
		CString log_bff;
		
		log_msg = "Call__READY() : Info ... \n";
			
		log_bff.Format("  1. %s <- [%s] \n",
						sCH__CUR_PROC_TYPE->Get__CHANNEL_NAME(),
						sCH__CUR_PROC_TYPE->Get__STRING());
		log_msg += log_bff;
					
		log_bff.Format("  2. %s <- [%s] \n",
						dEXT_CH__SLOT01_STATUS->Get__CHANNEL_NAME(),
						dEXT_CH__SLOT01_STATUS->Get__STRING());
		log_msg += log_bff;
		
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	/*
	// ...
	int nRet = -1;	
	CString log_id = "Call__READY()";

	// 1. Process Manometer Check
	// 2. Pre Process Condition Check
	// 3. Lift Pin Down
	// 4. GasBox Bypass Pumping Stop (Sequence)

	// 1. Process Manometer Isolation Valve Open
	// IF Vac S/W On, 500mt S/W On, Isolation Valve Not Open...
	if((dEXT_CH__IO_VACUUM_SWITCH_STS->Check__DATA("True") > 0)
	&& (dEXT_CH__IO_THROTTLE_VALVE_INTLK_SWITCH_STS->Check__DATA("True") > 0)
	&& (dEXT_CH__IO_PROCESSMANOMETER_ISOLVALVE->Check__DATA("Open") < 0))
	{
		// ... Isolation Valve Open
		dEXT_CH__IO_PROCESSMANOMETER_ISOLVALVE->Set__DATA("Open");

		// ...
		{
			log_msg = ">>> Process Manometer Isolation Valve Open Control ...";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// 2. Pre Process Condition Check
	nRet = Fnc__IO_INTERLOCK_CHECK(p_variable, p_alarm);
	if(nRet < 0)
	{
		// ...
		{
			log_msg.Format("===>>> Fnc__IO_INTERLOCK_CHECK Failed [%d] ...", nRet);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		return nRet;
	}
	
	// 3. Before Process Pin Down
	if(dCH__CFG_ENFORECE_PINS_DOWN_BEFORE_PROCESS->Check__DATA("True") > 0)
	{
		//
		log_msg = "Lift Pin Down : Call Start ...";
		xLOG_CTRL->WRITE__LOG(log_msg);

		// ...
		{
			sCH__OBJ_SUB_MSG->Set__DATA("Call__Ready() : Lift Pin Down ...");

			nRet = LIFT_PIN_OBJ__Call_MODE(CMMD__LIFT_PIN_DOWN, log_id);
			if(nRet < 0)
			{
				log_msg.Format("%s : LIFT_PIN_OBJ__Call_MODE(CMMD__LIFT_PIN_DOWN) is Failed [%d] ...", 
					           log_id, nRet);
				xLOG_CTRL->WRITE__LOG(log_msg);

				return nRet;
			}
		}

		//
		log_msg = "Lift Pin Down : Call End ...";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	
	// 4. GasBox Bypass Pumping Stop (Sequence)
	{
		// *) N2 Purge Valve Close (Preventive Venting)
		dEXT_CH__IO_GASBOX_INLET_N2_PURGE_V1->Set__DATA("Close");	// Never Open, Only Close!!!
		dEXT_CH__IO_GASBOX_OUTLET_N2_PURGE_V3->Set__DATA("Close");	// Never Open, Only Close!!!

		// 1) Pumping Valve Close
		dEXT_CH__IO_GASBOX_INLET_PUMP_V2->Set__DATA("Close");
		dEXT_CH__IO_GASBOX_OUTLET_PUMP_V4->Set__DATA("Close");

		// 2) DGF Default Control
		aEXT_CH__CFG_DGF_DEFAULT_CENTER_WEIGHT->Get__DATA(str_data);
		aEXT_CH__DFG_WT_SETPOINT->Set__DATA(str_data);
	
		//
		log_msg = "DGF Control : Call Start ...";
		xLOG_CTRL->WRITE__LOG(log_msg);

		// ...
		{
			sCH__OBJ_SUB_MSG->Set__DATA("Call__Ready() : DGF Control ...");

			nRet = DGF_OBJ__Call_MODE(CMMD__DGF_CONTROL);
			if(nRet < 0)
			{
				log_msg.Format("%s : DGF_OBJ__Call_MODE(CMMD__DGF_CONTROL) is Failed [%d] ...", 
							   log_id, nRet);
				xLOG_CTRL->WRITE__LOG(log_msg);

				return nRet;
			}
		}

		//
		log_msg = "DGF Control : Call End ...";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return nRet;
	*/

	return 1;
}

int CObj__STEP_LLx
::Call__START(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	Init__PRE_RCP_ITEM();

	if(dEXT_CH__SLOT01_STATUS->Check__DATA(STR__NONE) < 0)
	{
		CString var_data;

		sEXT_CH__CUR_LOTID->Get__DATA(var_data);
		sCH__CUR_LOTID->Set__DATA(var_data);

		// Wafer Count ...
		aCH__WAFER_TOTAL_COUNT->Inc__VALUE(1);
		aCH__WAFER_CURRENT_COUNT->Inc__VALUE(1);
	}
	else
	{
		sCH__LEARNED_APPLY_STATUS->Set__DATA("Idle ...");
	}

	// ...
	{
		CString log_msg = " * Pumping ...";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	return pOBJ_CTRL__LLx_CHM->Call__OBJECT(_CMMD_LLx__PUMP);
}

int CObj__STEP_LLx
::Init__PRE_RCP_ITEM()
{
	// APC ...
	{
		sCH__PRE_RCP_APC_CTRL->Set__DATA("");
	}

	// MFC_N2 ...
	if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
	{
		sCH__PRE_RCP_MFC_SET_FLOW->Set__DATA("");
	}

	return 1;
}

int CObj__STEP_LLx
::Call__PROC(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm,
			 const bool cfg_mode)
{
	DECLARE__EXT_CTRL(p_variable);
	
	// ...
	int flag = 1;
	CString log_msg;

	if(iSTEP_COUNT == 1)
	{
		if(flag > 0)
		{	
			sCH__STEP_TIME_COUNT->Set__DATA("0");
		}
	}

	if(flag > 0)
	{
		// ...
		{
			iPRC_FLAG = 1;
			iSTEP_CHANGE_FLAG = 1;		

			iTOLERANCE_ABORT_FLAG = -1;
		}

		if(flag > 0)
		{
			flag = Fnc__PROC(p_variable,p_alarm, cfg_mode);

			if(flag < 0)
			{
				CString var_data;

				sCH__STEP_TIME_COUNT->Get__DATA(var_data);
				aCH__RCP_FDC_STEP_TIME->Set__DATA(var_data);

				// ...
				{
					aCH__RCP_FDC_STEP_TIME->Get__DATA(var_data);

					CString log_msg;
					log_msg.Format("** FDC STEP TIME(2) : [%s] sec", var_data);

					xLOG_CTRL->WRITE__LOG(log_msg);
				}
			}
		}

		// ...
		{
			iPRC_FLAG = -1;		
			iTOLERANCE_ABORT_FLAG = -1;
		}
	}

	// Abort Seq ...
	if(flag < 0)
	{
		// ...
		{
			log_msg.Format("  Call__PROC() : Abort Seq (%1d) ... \n", flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(Fnc__ABORT(p_variable,p_alarm) < 0)
		{
			log_msg.Format("===>>> Fnc__ABORT Failed ...");
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		// ...
		{
			sCH__LEARNED_RESULT->Set__DATA(STR__ERROR);
			mDB__LEARNED_ITEM_CTRL.Init__ALL_ITEM();
		}
	}

	return flag;
}

int CObj__STEP_LLx
::Fnc__PROC(CII_OBJECT__VARIABLE* p_variable,
			CII_OBJECT__ALARM* p_alarm,
			const bool cfg_mode)
{
	CString log_msg;
	CString log_bff;

	CString log_id = "Fnc__PROC()";

	// ...
	CString str__step_msg;
	CString str__step_mode;
	CString str__step_time;
	
	CString str__apc_mode;
	CString str__apc_pressure;
	CString str__apc_position;
	CString str__apc_preset_pos;
	CString str__apc_hold_delay;

	CString str__gas_n2_flow;

	CString str__lift_pin_mode;

	CString str__loop_start;
	CString str__loop_repeat;

	int i_limit;
	int i;

	if(cfg_mode)
	{
		str__step_msg  = "Config Mode";
		str__step_mode = "Time";		
		aCH__CFG_PARA_STEP_TIME->Get__DATA(str__step_time);

		dCH__CFG_PARA_APC_MODE->Get__DATA(str__apc_mode);
		aCH__CFG_PARA_APC_PRESSURE->Get__DATA(str__apc_pressure);
		aCH__CFG_PARA_APC_POSITION->Get__DATA(str__apc_position);
		str__apc_preset_pos = "0";
		str__apc_hold_delay = "0";

		aCH__CFG_PARA_GAS_N2_FLOW->Get__DATA(str__gas_n2_flow);
		
		dCH__CFG_PARA_LIFT_PIN_MODE->Get__DATA(str__lift_pin_mode);

		str__loop_start  = "0";
		str__loop_repeat = "0";

		// ...
		sCH__RCP_STEP_MESSAGE->Set__DATA(str__step_msg);
		dCH__RCP_STEP_MODE->Set__DATA(str__step_mode);
		aCH__RCP_STEP_TIME->Set__DATA(str__step_time);
	}
	else
	{
		sCH__RCP_STEP_MESSAGE->Get__DATA(str__step_msg);
		dCH__RCP_STEP_MODE->Get__DATA(str__step_mode);
		aCH__RCP_STEP_TIME->Get__DATA(str__step_time);

		dCH__RCP_APC_MODE->Get__DATA(str__apc_mode);
		aCH__RCP_APC_PRESSURE->Get__DATA(str__apc_pressure);
		aCH__RCP_APC_POSITION->Get__DATA(str__apc_position);
		aCH__RCP_APC_PRESET_POS->Get__DATA(str__apc_preset_pos);
		aCH__RCP_APC_HOLD_DELAY->Get__DATA(str__apc_hold_delay);

		aCH__RCP_GAS_N2_FLOW->Get__DATA(str__gas_n2_flow);

		dCH__RCP_LIFT_PIN_MODE->Get__DATA(str__lift_pin_mode);

		aCH__RCP_LOOP_START->Get__DATA(str__loop_start);
		aCH__RCP_LOOP_REPEAT->Get__DATA(str__loop_repeat);
	}

	// ...
	{
		log_msg = "Step Recipe Info ...\n";

		log_bff.Format(" * Step_Count <- %1d \n", iSTEP_COUNT);
		log_msg += log_bff;

		log_bff.Format(" * step_msg <- %s \n", str__step_msg);
		log_msg += log_bff;

		log_bff.Format(" * step_mode <- %s \n", str__step_mode);
		log_msg += log_bff;

		log_bff.Format(" * step_time <- %s \n", str__step_time);
		log_msg += log_bff;

		log_bff.Format(" * apc_mode <- %s \n", str__apc_mode);
		log_msg += log_bff;

		log_bff.Format(" * apc_pressure <- %s \n", str__apc_pressure);
		log_msg += log_bff;

		log_bff.Format(" * apc_position <- %s \n", str__apc_position);
		log_msg += log_bff;

		log_bff.Format(" * apc_preset_pos <- %s \n", str__apc_preset_pos);
		log_msg += log_bff;

		log_bff.Format(" * apc_hold_delay <- %s \n", str__apc_hold_delay);
		log_msg += log_bff;

		log_bff.Format(" * gas_n2_flow <- %s \n", str__gas_n2_flow);
		log_msg += log_bff;

		log_bff.Format(" * lift_pin_mode <- %s \n", str__lift_pin_mode);
		log_msg += log_bff;

		log_bff.Format(" * loop_start <- %s \n", str__loop_start);
		log_msg += log_bff;

		log_bff.Format(" * loop_repeat <- %s \n", str__loop_repeat);
		log_msg += log_bff;

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	CString var_data;
	int	nProcessResult = -1;
	
	int lotid_change_flag = -1;
	int step_learned_flag =  1;

	aEXT_CH__STEP_CUR_NUM->Get__DATA(var_data);
	int step_id = atoi(var_data);

	if(dEXT_CH__SLOT01_STATUS->Check__DATA(STR__NONE) < 0)
	{
		sCH__CUR_LOTID->Get__DATA(var_data);
		
		if((sCH__PRE_LOTID->Check__DATA(var_data) < 0)
		|| (atoi(str__step_time) < 5))
		{			
			lotid_change_flag =  1;

			if(atoi(str__step_time) < 5)
			{
				step_learned_flag = -1;
			}
		}

		if(lotid_change_flag < 0)
		{
			CString str_msg;
			str_msg.Format("Step(%1d) : Learned Mode Applied ...", step_id);

			sCH__LEARNED_APPLY_STATUS->Set__DATA(str_msg);
		}
		else
		{
			CString str_msg;
			str_msg.Format("Step(%1d) : Preset Mode Applied ...", step_id);

			sCH__LEARNED_APPLY_STATUS->Set__DATA(str_msg);
		}
	}

	// ...
	int     nRet = -1;
	double  dbProgress_Step_Time = 0.0;
	double  db_step_time = 0.0;
	CString obj_err_msg;

	// ...
	{
		log_msg = "All_Object__Abort_Wait() : Check 1";
		xLOG_CTRL->WRITE__LOG(log_msg);

		ALL_OBJ__ABORT_WAIT(p_variable,p_alarm,obj_err_msg);

		if(sCH__STEP_TIME_ABORT_FLAG->Check__DATA(STR__YES) > 0)
		{
			return -1;
		}
	}

	// Step Start Information Log ...
	{
		CString log_msg;
		CString log_bff;

		db_step_time = atof(str__step_time);

		// ...
		{
			log_msg = ">>> Recipe Step Control Start  >>>>>>>>>>>>>>";
			
			log_bff.Format(">>> Step Name : %s / Type : %s / Time : %s / ", 
						   str__step_msg, 
						   str__step_mode, 
						   str__step_time);
			log_msg += log_bff;
			log_msg += "\n";

			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// 0. End Control ...
	if(str__step_mode.CompareNoCase("End") == 0)
	{
		sEXT_CH__EXCEPTION_ACT->Set__DATA("END");

		// ...
		{
			CString str_data;

			aEXT_CH__STEP_CUR_NUM->Get__DATA(str_data);
			aCH__RCP_MON_STEP_NO->Set__DATA(str_data);

			// ...
			{
				log_msg = "\n";

				log_bff.Format("Monitoring Last Step Number : [%s] \n", 
							   str_data);
				log_msg += log_bff;

				log_bff.Format(">>> Step Name : %s / Type : %s / Time : %s / \n", 
							   str__step_msg, 
							   str__step_mode, 
							   str__step_time);
				log_msg += log_bff;

				log_bff.Format(">>> Recipe Step Control End  >>>>>>>>>>>>>> \n");
				log_msg += log_bff;

				//
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
		return 1;
	}

	// ...
	SCX__ASYNC_TIMER_CTRL x_step_timer;

	// Start Time Counting...	
	{
		x_step_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__STEP_TIME_COUNT->Get__CHANNEL_NAME());
		x_step_timer->STOP();
		x_step_timer->START__COUNT_UP(99999);	
	}

	// ...
	{
		CString str_data;

		aEXT_CH__STEP_CUR_NUM->Get__DATA(str_data);
		aCH__RCP_MON_STEP_NO->Set__DATA(str_data);

		// ...
		{
			log_msg.Format("Monitoring Step Number : [%s]", str_data);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// Recipe Control : Turn_On ...
	{
		// 1. APC Control
		{
			if(str__apc_mode.CompareNoCase("Position") == 0)
			{
				sCH__OBJ_SUB_MSG->Set__DATA("1. APC - Position Control ...");

				aEXT_CH__APC_OBJ__PARA_PRE_POS_VALUE->Set__DATA(str__apc_preset_pos);
				aEXT_CH__APC_OBJ__PARA_PRE_POS_SEC->Set__DATA(str__apc_hold_delay);
				
				aEXT_CH__APC_OBJ__PARA_POSITION->Set__DATA(str__apc_position);

				pOBJ_CTRL__APC->Run__OBJECT(CMMD__APC_PRE_POS_POSITION);
			}
			else if(str__apc_mode.CompareNoCase("Pressure") == 0)
			{	
				sCH__OBJ_SUB_MSG->Set__DATA("1. APC - Pressure Control ...");

				aEXT_CH__APC_OBJ__PARA_PRE_POS_VALUE->Set__DATA(str__apc_preset_pos);
				aEXT_CH__APC_OBJ__PARA_PRE_POS_SEC->Set__DATA(str__apc_hold_delay);
	
				aEXT_CH__APC_OBJ__PARA_PRESSURE->Set__DATA(str__apc_pressure);

				pOBJ_CTRL__APC->Run__OBJECT(CMMD__APC_PRE_POS_PRESSURE);
			}
			else
			{  
				// ...
				{
					log_msg.Format("Invalid APC Control Mode(%s)", str__apc_mode);
		 			xLOG_CTRL->WRITE__LOG(log_msg);
				}
				return OBJ_ABORT;
			}

			sCH__PRE_RCP_APC_CTRL->Set__DATA(str__apc_mode);
		}

		// 2.2  MFC & Gas Flow Control
		{
			// MFC Control ...
			{
				sCH__OBJ_SUB_MSG->Set__DATA("2. MFC & Gas Flow Control ...");

				// ...
				{
					log_msg  = "\n";
					log_msg += "2.2 MFC Flow Control \n";
				}

				int set_flow = atof(str__gas_n2_flow);
				if(set_flow > 0)
				{
					sCH__PRE_RCP_MFC_SET_FLOW->Set__DATA(str__gas_n2_flow);

					// ...
					{
						log_bff.Format("MFC CONTROL (N2) : Flow: (%s) \n", str__gas_n2_flow);
						log_msg += log_bff;
					}

					aEXT_CH__MFC_N2__SET_FLOW->Set__DATA(str__gas_n2_flow);
					pOBJ_CTRL__MFC_N2->Run__OBJECT(CMMD__MFC_CONTROL);
				}

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
	}
	
	// Recipe Control : Turn_Off ...
	{
		// MFC Close ...
		if(aCH__CFG_STEP_DELAY_MFC_CLOSE->Get__VALUE() >= 0.1)
		{
			sCH__ACTIVE__MFC_CLOSE_DELAY->Set__DATA(STR__YES);
		}
		else
		{			
			sCH__ACTIVE__MFC_CLOSE_DELAY->Set__DATA("");

			// ...
			sCH__OBJ_SUB_MSG->Set__DATA("MFC Close ...");

			// ...
			{
				log_msg  = "\n";
				log_msg += "* MFC Close List \n";
			}

			if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
			{
				int set_flow = atof(str__gas_n2_flow);

				if(set_flow < 0.1)
				{
					aEXT_CH__MFC_N2__SET_FLOW->Set__DATA("0");
					pOBJ_CTRL__MFC_N2->Run__OBJECT(CMMD__MFC_CLOSE);

					// ...
					{
						log_bff = "  * MFC_N2 <- 0.0 \n";
						log_msg += log_bff;
					}
				}
			}

			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		// ...
	}
	
	// Lift_Pin Control ...
	{
		log_msg.Format("* Lift_Pin Control : %s", str__lift_pin_mode);
		xLOG_CTRL->WRITE__LOG(log_msg);

		if(str__lift_pin_mode.CompareNoCase("Up") == 0)
		{
			sCH__OBJ_SUB_MSG->Set__DATA("Lift_Pin Proc.Up Control ...");

			x_step_timer->STOP();

			if(pOBJ_CTRL__LLx_CHM->Call__OBJECT(_CMMD_LLx__LIFT_PIN_UP) < 0)
			{
				return -101;
			}

			x_step_timer->START__COUNT_UP(99999);	
		}
		else
		{
			sCH__OBJ_SUB_MSG->Set__DATA("Lift_Pin Proc.Down Control ...");

			if(pOBJ_CTRL__LLx_CHM->Run__OBJECT(_CMMD_LLx__LIFT_PIN_DOWN) < 0)
			{
				return -102;
			}
		}
	}
	
	// Process Control Monitoring ...
	int nProcess_Control = 0;

	// Check Step_Mode - Time Stable End Chuck DeChuck
	{	
		// ...
		{
			log_msg.Format("Step Type (%s) Monitoring Start... Recipe Step Time(%s)", 
						   str__step_mode, str__step_time);

			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		db_step_time = atof(str__step_time);		

		// ...
		{
			sCH__OBJ_SUB_MSG->Set__DATA("Step Start ...");
		}

		// 1. Time Control
		if(str__step_mode.CompareNoCase("Time") == 0)
		{
			nProcess_Control = 0;		

			// Delay ....
			if(sEXT_CH__LAST_STEP_FLAG->Check__DATA("YES") < 0)
			{
				// ???
			}

			sCH__OBJ_SUB_MSG->Set__DATA("Step Time Control ...");

			while(db_step_time > x_step_timer->Get__CURRENT_TIME())
			{
				Control__RECIPE_DELAY_PARAMETER(x_step_timer->Get__CURRENT_TIME());

				if(Check__STEP_CONTROL() < 0)					
				{ 
					nProcess_Control = 1;		
					break; 
				}

				nRet = Fnc__CHECK_PART_ERROR(p_variable, p_alarm);
				if(nRet < 0)
				{ 
					nProcess_Control = nRet;	
					break; 
				}

				if(p_variable->Check__CTRL_ABORT() > 0)
				{ 
					sCH__OBJ_MSG->Set__DATA("Process Aborted By User(1).");

					nProcess_Control = -2;	
					break; 
				}

				if(iTOLERANCE_ABORT_FLAG > 0)
				{
					// ...
					{
						CString log_msg;

						log_msg.Format("Tolerance Abort : Flag(%1d)", iTOLERANCE_ABORT_FLAG);

						sCH__OBJ_MSG->Set__DATA(log_msg);
						xLOG_CTRL->WRITE__LOG(log_msg);
					}

					nProcess_Control = -11;	
					break;
				}

				nRet = Fnc__OBJ_Abort_Check(log_id,1);
				if(nRet < 0)
				{ 
					nProcess_Control = nRet;	
					break; 
				}

				Sleep(1);
			}
		}
		// 2. Stable Control
		else if(str__step_mode.CompareNoCase("Stable") == 0)
		{
			nProcess_Control = 0;		

			// ...
			sCH__OBJ_SUB_MSG->Set__DATA("Step Stable Control ...");

			if(db_step_time >= 1.0)
			{
				Sleep(100);
			}

			while(db_step_time > x_step_timer->Get__CURRENT_TIME())
			{
				Control__RECIPE_DELAY_PARAMETER(x_step_timer->Get__CURRENT_TIME());

				if(Check__STEP_CONTROL() < 0)
				{ 
					nProcess_Control = 1;		
					break; 
				}
				
				nRet = Fnc__CHECK_PART_ERROR(p_variable, p_alarm);
				if(nRet < 0)
				{ 
					nProcess_Control = nRet;	
					break; 
				}

				if(p_variable->Check__CTRL_ABORT() > 0)
				{ 
					sCH__OBJ_MSG->Set__DATA("Process Aborted By User(2).");

					nProcess_Control = -2;	
					break; 
				}
				
				if(iTOLERANCE_ABORT_FLAG > 0)
				{
					// ...
					{
						CString log_msg;
						
						log_msg.Format("Tolerance Abort : Flag(%1d)", iTOLERANCE_ABORT_FLAG);
						
						sCH__OBJ_MSG->Set__DATA(log_msg);
						xLOG_CTRL->WRITE__LOG(log_msg);
					}
					
					nProcess_Control = -11;	
					break;
				}

				nRet = Fnc__OBJ_Abort_Check(log_id,1);
				if(nRet < 0)
				{ 
					nProcess_Control = nRet;	
					break; 
				}

				// Stable Step Complete
				nRet = Fnc__OBJ_Avaliable_Check(log_id);
				if(nRet == 100)							// Object Available
				{
					if(Fnc__CHECK_PART_STABLE(p_variable, p_alarm) > 0)
					{
						nProcess_Control = nRet;
						break;							// Stable OK!
					}
				}

				Sleep(1);
			}	
		}
		// Invalid Step Type
		else
		{
			// ...
			{
				log_msg.Format("Unknown Step Type. Process Abort.");
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			return -1;
		}

		x_step_timer->STOP();

		// Step Complete ...
		if(nProcess_Control >= 0)
		{
			Control__RECIPE_DELAY_PARAMETER(0, 1);
		}
		
		if(nProcess_Control < 0)			// Process Aborted
		{
			dbProgress_Step_Time = x_step_timer->Get__CURRENT_TIME();

			// ...
			{
				log_msg.Format("Step Type (%s) Abort [%d] ... Recipe Progress Time(%.2f)", 
							   str__step_mode, 
							   nProcess_Control, 
							   dbProgress_Step_Time);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
				
			// Process Abort Flag Add ...
		}
		else if(nProcess_Control == 0)			// Process Normal Complete
		{
			dbProgress_Step_Time = x_step_timer->Get__CURRENT_TIME();

			// ...
			{
				log_msg.Format("Step Type (%s) Monitoring Normal End [%d] ... Recipe Progress Time(%.2f)", 
							   str__step_mode, 
							   nProcess_Control, 
							   dbProgress_Step_Time);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			if(str__step_mode.CompareNoCase("Stable") == 0)
			{
				// Process Stable Step Overtime Alarm Post ...
				{
					int alarm_id = ALID__PROCESS_STABLE_OVERTIME;

					CString err_msg;
					CString err_str1;
					CString err_str2;
				
					Fnc__Get_OBJ_Not_Available_List(err_str1);
					Get__PART_UNSTABLE_MSG(err_str2);

					err_msg  = err_str1;
					err_msg += "\n";
					err_msg += err_str2;

					Alarm__POST_CHECK(p_alarm, err_msg, alarm_id);
				}

				nProcess_Control = -10;			// Stable Step Overtime Alarm !!!
			}
		}
		else if(nProcess_Control == 1)			// Process Step Skip
		{
			dbProgress_Step_Time = x_step_timer->Get__CURRENT_TIME();

			// ...
			{
				log_msg.Format("Step Type (%s) Monitoring SKIP [%d] ... Recipe Progress Time(%.2f)", 
							   str__step_mode, 
							   nProcess_Control, 
							   dbProgress_Step_Time);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
		else if(nProcess_Control == 50)			// Process EndPT OK
		{
			dbProgress_Step_Time = x_step_timer->Get__CURRENT_TIME();

			// ...
			{
				log_msg.Format("Step Type (%s) Monitoring EndPT End [%d] ... Recipe Progress Time(%.2f)", 
							   str__step_mode, 
							   nProcess_Control, 
							   dbProgress_Step_Time);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
		else if(nProcess_Control == 100)		// Process Stable OK
		{
			dbProgress_Step_Time = x_step_timer->Get__CURRENT_TIME();

			// ...
			{
				log_msg.Format("Step Type (%s) Monitoring Stable End [%d] ... Recipe Progress Time(%.2f)", 
							   str__step_mode, 
							   nProcess_Control, 
							   dbProgress_Step_Time);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
	}
	
	// OBJECT WAIT ...
	if(nProcess_Control < 0) 
	{
		int delay_flag = 1;

		if(nProcess_Control < 0) 
		{
			delay_flag = -1;
		}

		// ...
		{
			log_msg = "All_Object__Abort_Wait() : Check 2";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		ALL_OBJ__ABORT_WAIT(p_variable,p_alarm,obj_err_msg,delay_flag);

		if(sCH__STEP_TIME_ABORT_FLAG->Check__DATA(STR__YES) > 0)
		{
			return -1;
		}
	}

	if(nProcess_Control >= 0)
	{
		// Step End Information Log ...
		dbProgress_Step_Time = x_step_timer->Get__CURRENT_TIME();
		
		// ...
		{
			log_msg = "\n";

			log_bff.Format(">>> Step Name : %s / Type : %s / Time : %s / Current Time : %.2f \n", 
						   str__step_msg, str__step_mode, str__step_time, dbProgress_Step_Time);
			log_msg += log_bff;
	
			log_bff.Format(">>> Recipe Step Control End [%d] >>>>>>>>>>>>>> \n", 
						   nProcess_Control);
			log_msg += log_bff;

			//
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		return OBJ_AVAILABLE;
	}
	else
	{
		// ... Step End Information Log
		dbProgress_Step_Time = x_step_timer->Get__CURRENT_TIME();
		
		// ...
		{
			log_msg = "\n";

			log_bff.Format(">>> Step Name : %s / Type : %s / Time : %s / Current Time : %.2f \n", 
						   str__step_msg, str__step_mode, str__step_time, dbProgress_Step_Time);
			log_msg += log_bff;
			
			log_bff.Format(">>> Recipe Step Control Aborted  [%d] >>>>>>>>>>>>>> \n", 
						   nProcess_Control);
			log_msg += log_bff;

			//
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		return OBJ_ABORT;
	}

	return OBJ_ABORT;
}

void CObj__STEP_LLx::Control__RECIPE_DELAY_PARAMETER(const double step_sec, const int set_req)
{
	if(sCH__ACTIVE__MFC_CLOSE_DELAY->Check__DATA(STR__YES) > 0)
	{
		if((set_req  >  0)
		|| (step_sec >= aCH__CFG_STEP_DELAY_MFC_CLOSE->Get__VALUE()))
		{
			sCH__ACTIVE__MFC_CLOSE_DELAY->Set__DATA("");

			// ...
			CString log_msg;
			CString log_bff;

			// ...
			{
				log_msg  = "\n";
				log_msg += "* MFC Delay_Close List ...\n";
			}

			if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
			{
				if(aCH__RCP_GAS_N2_FLOW->Get__VALUE() > 0)
				{

				}
				else
				{
					aEXT_CH__MFC_N2__SET_FLOW->Set__DATA("0");
					pOBJ_CTRL__MFC_N2->Run__OBJECT(CMMD__MFC_CLOSE);

					log_bff = "  * MFC_N2 <- 0.0 \n";
					log_msg += log_bff;
				}
			}

			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// ...
}

void CObj__STEP_LLx
::ALL_OBJ__WAIT(CII_OBJECT__VARIABLE* p_variable,
				const int mfc_check)
{
	CString var_data;

	// APC OBJ - FNC ...
	{
		// ...
		{
			var_data = "END : APC OBJ Wait ...";
			xLOG_CTRL->WRITE__LOG(var_data);
			
			sCH__OBJ_SUB_MSG->Set__DATA(var_data);
		}

		while(1)
		{
			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				break;
			}

			if(pOBJ_CTRL__APC->Is__OBJ_BUSY() > 0)
			{
				Sleep(1);
				continue;
			}
				
			break;
		}
	}
	
	// MFC OBJ - FNC ...
	if(mfc_check > 0)
	{
		MFC_OBJ__WAIT(p_variable);
	}
}

void CObj__STEP_LLx
::ALL_OBJ__WAIT_SEC(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm)
{
	SCX__ASYNC_TIMER_CTRL x_async_timer;

	CString log_msg;
	CString log_bff;
	
	CString str_abort_msg;
	int busy_abort_flag = -1;
	int OBJ_ABORT_flag = -1;
	int check_flag;
	int i;

	// ...
	{
		log_msg = "All_Obj__Wait_Sec() : Started ...";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	x_async_timer->START__COUNT_UP(9999);

	while(x_async_timer->Get__CURRENT_TIME() < 15.0)
	{
		// ...
		{
			check_flag = -1;

			// ...
			log_msg = "";
			str_abort_msg = "";
		}

		// APC ...
		if(pOBJ_CTRL__APC->Is__OBJ_BUSY() > 0)
		{
			check_flag = 1;

			// ...
			log_bff  = "APC : Busy \n";
			log_msg += log_bff; 
		}

		// MFC OBJ ...
		if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
		{
			if(pOBJ_CTRL__MFC_N2->Is__OBJ_BUSY() > 0)
			{
				check_flag = 1;

				// ...
				{
					log_bff = "MFC_N2 : Busy \n";
					log_msg += log_bff; 
				}

				if(busy_abort_flag > 0)
				{
					OBJ_ABORT_flag = 1;

					log_bff = "MFC_N2 is not completed. \n";
					str_abort_msg += log_bff;
				}
			}
		}

		if(check_flag < 0)
		{
			double cur_sec = x_async_timer->Get__CURRENT_TIME();

			if(cur_sec > 1.0)
			{
				log_msg.Format("All_Obj__Wait_Sec() : Error-Check (%.3f) ...", cur_sec);
				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			// ...
			{
				log_msg = "All_Obj__Wait_Sec() : Completed ...";
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			return;
		}

		xLOG_CTRL->WRITE__LOG(log_msg);

		if(x_async_timer->Get__CURRENT_TIME() < 1.5)
		{
			OBJ_ABORT_flag = -1;
		}
		else
		{
			if(OBJ_ABORT_flag > 0)
			{
				sCH__STEP_TIME_ABORT_FLAG->Set__DATA(STR__YES);

				// ...
				{
					int alarm_id = ALID__PROCESS_STEP_OVERTIME;
					CString r_act;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id,str_abort_msg);
				}

				Sleep(100);
			}
		}

		Sleep(3);
	}
}

void CObj__STEP_LLx::ALL_OBJ__ABORTED_TO_AVAILABLE(CII_OBJECT__VARIABLE *p_variable)
{
	CString log_msg;

	// APC OBJ
	if(dEXT_CH__APC_OBJ__CTRL->Check__DATA(STR__ABORTED) > 0)
	{
		dEXT_CH__APC_OBJ__CTRL->Set__DATA(STR__AVAILABLE);

		log_msg = "APC CTRL : ABORTED -> AVAILABLE";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// MFC OBJ ...
	{
		ALL_MFC__ABORTED_TO_AVAILABLE(p_variable);
	}
}
void CObj__STEP_LLx::ALL_MFC__ABORTED_TO_AVAILABLE(CII_OBJECT__VARIABLE *p_variable)
{
	CString log_msg;
	CString log_bff;

	// MFC_N2 ...
	if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
	{
		log_msg = "\n";

		if(dEXT_CH__MFC_N2__OBJ_CTRL->Check__DATA(STR__ABORTED) > 0)
		{
			dEXT_CH__MFC_N2__OBJ_CTRL->Set__DATA(STR__AVAILABLE);

			log_bff = "MFC_N2 CTRL : ABORTED -> AVAILABLE \n";
			log_msg += log_bff;
		}

		xLOG_CTRL->WRITE__LOG(log_msg);
	}
}

void CObj__STEP_LLx::MFC_OBJ__WAIT(CII_OBJECT__VARIABLE* p_variable)
{
	CString log_msg;
	CString log_bff;

	CString var_data;

	// MFC_N2 ...
	if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
	{
		log_msg = "\n";

		var_data = "MFC(N2) Object Wait ... \n";
		log_msg += var_data;

		sCH__OBJ_SUB_MSG->Set__DATA(var_data);

		pOBJ_CTRL__MFC_N2->When__OBJECT();

		xLOG_CTRL->WRITE__LOG(log_msg);
	}
}

int  CObj__STEP_LLx::
ALL_OBJ__ABORT_WAIT(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm,
				    CString& err_msg,
					const int delay_flag)
{
	err_msg = "";

	// ...
	CString log_msg;
	CString err_bff;

	sCH__STEP_TIME_ABORT_FLAG->Set__DATA("");

	if(delay_flag > 0)
	{
		ALL_OBJ__WAIT_SEC(p_variable,p_alarm);
	}
	
	// APC ...
	if(pOBJ_CTRL__APC->Is__OBJ_BUSY() > 0)
	{
		log_msg = "ABORT : APC OBJ ...";
		xLOG_CTRL->WRITE__LOG(log_msg);

		pOBJ_CTRL__APC->Abort__OBJECT();

		err_msg += "APC Object. \n";
	}

	// MFC OBJ ...
	if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
	{
		if(pOBJ_CTRL__MFC_N2->Is__OBJ_BUSY() > 0)
		{
			log_msg = "ABORT : MFC(N2) Object ... \n";	
			xLOG_CTRL->WRITE__LOG(log_msg);

			pOBJ_CTRL__MFC_N2->Abort__OBJECT();

			err_bff = "MFC_N2 Object \n";
			err_msg += err_bff;
		}
	}

	if(err_msg.GetLength() > 0)
	{
		ALL_OBJ__WAIT(p_variable);
		ALL_OBJ__ABORTED_TO_AVAILABLE(p_variable);
		return -1;
	}
	return 1;
}

int CObj__STEP_LLx::Call__ABORT(CII_OBJECT__VARIABLE* p_variable,
								CII_OBJECT__ALARM* p_alarm)
{
	sCH__OBJ_MSG->Set__DATA("Call__ABORT() : Start ...");

	Fnc__ABORT(p_variable,p_alarm);

	sCH__OBJ_MSG->Set__DATA("Call__ABORT() : End ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");

	return OBJ_AVAILABLE;
}
int CObj__STEP_LLx
::Fnc__ABORT(CII_OBJECT__VARIABLE* p_variable,
		     CII_OBJECT__ALARM* p_alarm)
{
	Init__PRE_RCP_ITEM();

	// ...
	{
		aCH__RCP_FDC_STEP_TIME->Set__DATA("0");
	}

	// ...
	{
		sCH__OBJ_MSG->Set__DATA("Fnc__ABORT() : Start ...");
		sCH__OBJ_SUB_MSG->Set__DATA("Fnc__ABORT() : Start ...");

		sCH__LEARNED_APPLY_STATUS->Set__DATA("Learned Mode Aborted ...");
	}

	// ...
	{
		CString log_msg;
		CString log_id = "Fnc__ABORT()";

		// ...
		{
			log_msg.Format("%s : Start ...", log_id);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		// MFC <- Close ...
		{
			// ...
			{
				log_msg = "Lift_Pin <- Down ...";
				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			sCH__OBJ_SUB_MSG->Set__DATA("Gas Close ...");

			ALL_MFC_OBJ__Abort_Call_MODE(CMMD__MFC_CLOSE, log_id);
		}
		// Lift_Pin <- Down ...
		{
			// ...
			{
				log_msg = "Lift_Pin <- Down ...";
				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			sCH__OBJ_SUB_MSG->Set__DATA("Lift_Pin <- Close ...");

			pOBJ_CTRL__LLx_CHM->Call__OBJECT(_CMMD_LLx__LIFT_PIN_DOWN);
		}

		// LLx_CHM <- Pumping .....
		{
			// ...
			{
				log_msg = "LLx_CHM <- Pumping ...";
				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			sCH__OBJ_SUB_MSG->Set__DATA("LLx_CHM <- Pumping ...");

			pOBJ_CTRL__LLx_CHM->Call__OBJECT(_CMMD_LLx__PUMP);
		}
	}

	// ...
	{
		sCH__OBJ_MSG->Set__DATA("Fnc__ABORT() : End ...");
		sCH__OBJ_SUB_MSG->Set__DATA("");
	}
	return 1;
}

int CObj__STEP_LLx::Call__END(CII_OBJECT__VARIABLE* p_variable,
							  CII_OBJECT__ALARM* p_alarm)
{
	sCH__OBJ_MSG->Set__DATA("Call__END() : Start ");
	sCH__OBJ_SUB_MSG->Set__DATA("");

	aCH__RCP_FDC_STEP_TIME->Set__DATA("0");
	sCH__STEP_TIME_ABORT_FLAG->Set__DATA("");

	// ...
	{
		CString obj_err_msg;
		ALL_OBJ__ABORT_WAIT(p_variable,p_alarm,obj_err_msg);
	}

	// ...
	CString log_msg;
	int r_flag = 1;
	
	// LLx_CHM ...
	if(r_flag > 0)
	{
		log_msg.Format(" LLx_CHM : Pumping !");
		xLOG_CTRL->WRITE__LOG(log_msg);

		r_flag = pOBJ_CTRL__LLx_CHM->Call__OBJECT(_CMMD_LLx__PUMP);
	}

	// LIFT_PIN ...
	if(r_flag > 0)
	{
		log_msg.Format(" Loft_Pin : Down !");
		xLOG_CTRL->WRITE__LOG(log_msg);

		r_flag = pOBJ_CTRL__LLx_CHM->Call__OBJECT(_CMMD_LLx__LIFT_PIN_DOWN);
	}

	sCH__OBJ_MSG->Set__DATA("Call__END() : End ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");

	return r_flag;
}

int CObj__STEP_LLx::
Call__STEP_DB_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CDS__LEARNED_ITEM_INFO ds_info;

	mDB__LEARNED_ITEM_CTRL.Init__ALL_ITEM();

	// ...
	int limit = 3;
	int i;

	for(i=0;i<limit;i++)
	{
		ds_info.iSTEP_ID = i+1;
		ds_info.sDATA__APC.Format("APC-%1d", i+1);

		mDB__LEARNED_ITEM_CTRL.Load__ITEM(ds_info);
	}

	// ...
	CString str_log;
	CString str_bff;

	i = 0;
	while(mDB__LEARNED_ITEM_CTRL.Get__DB_ITEM(i,&ds_info) > 0)
	{
		i++;

		str_bff.Format("iSTEP_ID : %1d \n", ds_info.iSTEP_ID);
		str_log += str_bff;

		str_bff.Format("   APC : %s \n", ds_info.sDATA__APC);
		str_log += str_bff;
	}

	MessageBox(NULL,str_log,sObject_Name,MB_OK|MB_TOPMOST);
	return 1;
}

