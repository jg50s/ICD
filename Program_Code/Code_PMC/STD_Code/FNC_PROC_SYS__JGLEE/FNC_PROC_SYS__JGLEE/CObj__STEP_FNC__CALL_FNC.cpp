#include "StdAfx.h"
#include "CObj__STEP_FNC.h"
#include "CObj__STEP_FNC__DEF.h"

#include "Macro_Function.h"


//-------------------------------------------------------------------------
// INIT ...
int CObj__STEP_FNC
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

// RCP DATA INIT ...
int CObj__STEP_FNC
::Call__RCP_DATA_INIT(CII_OBJECT__VARIABLE* p_variable,	CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		sCH__STEP_STABLE_REQ->Set__DATA("");
				
		aCH__RCP_MON_STEP_NO->Set__DATA("1");
		sCH__STEP_EDP_CHECK_SEC->Set__DATA("");
		sEXT_CH__LAST_STEP_FLAG->Set__DATA("");

		sCH__STEP_TIME_ABORT_FLAG->Set__DATA("");
	}
			
	// ...
	{
		Fnc__INIT_PART_ERROR(p_variable, p_alarm);

		Init__PRE_RCP_ITEM();
	}
			
	// ...
	{
		sCH__LEARNED_APPLY_STATUS->Set__DATA("Idle ...");

		mDB__LEARNED_ITEM_CTRL.Init__ALL_ITEM();
	}
	return 1;
}

// READY .....
int CObj__STEP_FNC
::Call__READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
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

// START .....
int CObj__STEP_FNC
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
		mDB__LEARNED_ITEM_CTRL.Init__ALL_ITEM();

		if(sCH__LEARNED_RESULT->Check__DATA("") > 0)
			sCH__LEARNED_RESULT->Set__DATA(STR__OK);
	}

	return OBJ_AVAILABLE;
}

int CObj__STEP_FNC
::Init__PRE_RCP_ITEM()
{
	int i;

	// ...
	{
		aCH__RCP_ESC_CENTER_OP_OFFSET->Set__VALUE(0.0);
		aCH__RCP_ESC_EDGE_OP_OFFSET->Set__VALUE(0.0);
	}

	// APC ...
	{
		sCH__PRE_RCP_APC_CTRL->Set__DATA("");
	}

	// MFC ...
	{
		for(i=0; i<CFG_SIZE__MFC_OBJ; i++)
		{
			sCH__PRE_RCP_MFC_SET_FLOW[i]->Set__DATA("");
		}
	}

	return 1;
}

// PROC .....
int CObj__STEP_FNC
::Call__PROC(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);
	
	int flag = 1;
	CString log_msg;


	// Header Proc ...
	if(iSTEP_COUNT == 1)
	{
		// ...
		{
			iHEADER_RCP_START    = -1;
			iTEMP_STEP_RCP_START = -1;
		}

		if(flag > 0)
		{	
			sCH__STEP_TIME_COUNT->Set__DATA("0");
		}
	}

	// Step Proc ...
	if(flag > 0)
	{
		// ...
		{
			iPRC_FLAG = 1;
			iSTEP_CHANGE_FLAG = 1;		

			iTOLERANCE_ABORT_FLAG = -1;
		}

		if(sCH__STEP_STABLE_REQ->Check__DATA(STR__YES) > 0)
		{
			sCH__STEP_STABLE_REQ->Set__DATA("");

			Init__PRE_RCP_ITEM();

			flag = Fnc__PROC__CONTINUE_STEP(p_variable,p_alarm);
		}

		if(flag > 0)
		{
			// ...
			{
				iHEADER_RCP_START    = 1;
				iTEMP_STEP_RCP_START = 1;

				iDCOP__START_FLAG = -1;
			}

			flag = Fnc__PROC(p_variable,p_alarm);

			if(flag < 0)
			{
				CString var_data;

				sCH__STEP_TIME_COUNT->Get__DATA(var_data);
				aCH__RCP_FDC_STEP_TIME->Set__DATA(var_data);

				//
				aCH__RCP_FDC_STEP_TIME->Get__DATA(var_data);

				CString log_msg;
				log_msg.Format("** FDC STEP TIME(2) : [%s] sec", var_data);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}

		// ...
		{
			iPRC_FLAG = -1;		
			iTOLERANCE_ABORT_FLAG = -1;
			iDCOP__START_FLAG = -1;
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


int CObj__STEP_FNC::
Fnc__PROC__CONTINUE_STEP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	// INIT .....
	{
		// sEXT_CH__APC_PID_CONTROL_STOP->Set__DATA("Yes");
	}

	/*
	//.....
	CString log_msg;
	CString log_bff;

	CString log_id = "Fnc__PROC__CONTINUE_STEP()";

	//.....
	CString str__step_msg;
	CString str__step_type;
	CString str__chm_press;
	
	CString str__dgf_we_setpoint;
	CString str__mfc_gas_flow[CFG_SIZE__MFC_OBJ];
	CString str__select_tuning_line;

	CString str__mfc_he_inner_flow;
	CString str__mfc_he_outer_flow;

	CString str__esc_threshold;
	CString str__esc_ext_bias_compensation_enable;
	CString str__esc_ext_bias_compensation_mode_select;

	CString str__lift_pin_pos;

	// CString str__valve_ctrl_mode;
	CString str__valve_hold_delay;
	CString str__valve_wap_control_mode;
	CString str__valve_pos_data;
	CString str__valve_preset_offset_pos;
	CString str__valve_ramp_target_pos;

	CString str__ring_hold_delay;
	CString str__ring_velocity;
	CString str__ring_ramp_time;
	CString str__ring_pos_data;

	CString str__rf_he_inner_max_threshold;
	CString str__rf_he_inner_min_threshold;
	CString str__rf_he_outer_max_threshold;	
	CString str__rf_he_outer_min_threshold;


	// ..........
	CString var_data;

	int	nProcessResult = -1;
	int i;
	
	
	//////////////////////////////////////////////////////////////////////////
	// 1. Process Data Read

	// Process Information
	sCH__RCP_STEP_MESSAGE->Get__DATA(str__step_msg);
	aCH__RCP_CHM_PRESSURE->Get__DATA(str__chm_press);
	dCH__RCP_STEP_TYPE->Get__DATA(str__step_type); 
	
	// ... DGF Set Point
	aCH__RCP_DGF_WT_SET_POINT->Get__DATA(str__dgf_we_setpoint);

	// ... MFC Set Point
	for(i=0;i<CFG_SIZE__MFC_OBJ;i++)
	{
		aCH__RCP_MFC_GASx_FLOW[i]->Get__DATA(str__mfc_gas_flow[i]);
		if(dCH__RCP_DATA_APP_LOG->Check__DATA("Enable") > 0)
		{
			log_msg.Format("MFC %d Flow value: %s", i+1, str__mfc_gas_flow[i]);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}
	dCH__RCP_SELECT_TUNING_LINE->Get__DATA(str__select_tuning_line);

	// ESC
	aCH__RCP_MFC_He_INNER_FLOW->Get__DATA(str__mfc_he_inner_flow);
	aCH__RCP_MFC_He_OUTER_FLOW->Get__DATA(str__mfc_he_outer_flow);

	aCH__RCP_ESC_Bias_VOLT_THRESHOLD->Get__DATA(str__esc_threshold);
	dCH__RCP_EXT_BIAS_COMPENSATION_ENABLE->Get__DATA(str__esc_ext_bias_compensation_enable);
	dCH__RCP_EXT_BIAS_COMPENSATION_MODE_SELECT->Get__DATA(str__esc_ext_bias_compensation_mode_select);	

	// LIFTER
	dCH__RCP_LIFT_PIN_POSITION->Get__DATA(str__lift_pin_pos);
		

	// APC VALVE ...
	{
		// dCH__RCP_VALVE_CTRL_MODE->Get__DATA(str__valve_ctrl_mode);
		aCH__RCP_VALVE_HOLD_DELAY->Get__DATA(str__valve_hold_delay);
		
		aCH__RCP_VALVE_PRESET_OFFSET_POS->Get__DATA(str__valve_preset_offset_pos);
		aCH__RCP_VALVE_RAMP_TARGET_POS->Get__DATA(str__valve_ramp_target_pos);
	}

	// WAP
	{
		dCH__RCP_WAP_CONTROL_MODE->Get__DATA(str__valve_wap_control_mode);
    
		aCH__RCP_CONFINEMENT_RING_HOLD_DELAY->Get__DATA(str__ring_hold_delay);
		aCH__RCP_CONFINEMENT_RING_VELOCITY->Get__DATA(str__ring_velocity);
		aCH__RCP_CONFINEMENT_RING_RAMP_TIME->Get__DATA(str__ring_ramp_time);

		// ...
		{
			aCH__RCP_CONFINEMENT_RING_PRESET_POSITION->Get__DATA(str__ring_pos_data);

			int cur_data = atoi(str__ring_pos_data);
			if(cur_data < 1)
			{
				aCH__RCP_CONFINEMENT_RING_LEARNED_POSITION->Get__DATA(str__ring_pos_data);
			}
		}
	}

	// APC PRESET POS ...
	{
		aCH__RCP_VALVE_PRESET_POSITION->Get__DATA(str__valve_pos_data);
		
		int cur_data = atoi(str__valve_pos_data);
		if(cur_data < 1)
		{
			if(str__valve_wap_control_mode.CompareNoCase("Throttle") == 0)
			{
				int apc_offset_pos = atoi(str__valve_preset_offset_pos);
				if(apc_offset_pos < -50)		apc_offset_pos = 0;
				
				//
				aCH__RCP_VALVE_LEARNED_POSITION->Get__DATA(var_data);
				int apc_preset_pos = apc_offset_pos + atoi(var_data);
				
				str__valve_pos_data.Format("%1d", apc_preset_pos);
			}
			else
			{
				aCH__RCP_VALVE_LEARNED_POSITION->Get__DATA(str__valve_pos_data);
			}
		}

		// ...
		{
			int ramp_pos = atoi(str__valve_ramp_target_pos);

			if(ramp_pos < -50)			str__valve_ramp_target_pos = "0";	
		}	
	}


	// ESC ...
	aCH__RCP_He_INNER_ZONE_FLOW_MAX_THRESHOLD->Get__DATA(str__rf_he_inner_max_threshold);
	aCH__RCP_He_INNER_ZONE_FLOW_MIN_THRESHOLD->Get__DATA(str__rf_he_inner_min_threshold);
	aCH__RCP_He_OUTER_ZONE_FLOW_MAX_THRESHOLD->Get__DATA(str__rf_he_outer_max_threshold);
	aCH__RCP_He_OUTER_ZONE_FLOW_MIN_THRESHOLD->Get__DATA(str__rf_he_outer_min_threshold);


	//////////////////////////////////////////////////////////////////////////
	// DEBUG RECIPE PARAMETER LIST
	
	// ...
	int	nProcess_Control		= 0;
	int nRet					=  -1;
	double dbProgress_Step_Time = 0.0;
	double db_step_time			= 0.0;
	CString obj_err_msg;

	// ...
	{
		if(ALL_OBJ__ABORT_WAIT(p_variable,p_alarm,obj_err_msg) < 0)
		{
		}
	}

	// 00. End Control ...
	if(str__step_type.CompareNoCase("End") == 0)
	{
		sEXT_CH__EXCEPTION_ACT->Set__DATA("END");

		//.....
		{
			CString str_data;

			aEXT_CH__STEP_CUR_NUM->Get__DATA(str_data);
			aCH__RCP_MON_STEP_NO->Set__DATA(str_data);

			// ...
			{
				log_msg = "\n";
				
				log_bff.Format("Monitoring Last Step Number : [%s] \n", str_data);
				log_msg += log_bff;

				log_bff.Format(">>> Step Name : %s / Type : %s / \n", str__step_msg, str__step_type);
				log_msg += log_bff;

				log_msg += ">>> Recipe Step Control End  >>>>>>>>>>>>>> \n";

				//
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
		return 1;
	}


	//.....
	{
		ALL_MFC__ABORTED_TO_AVAILABLE(p_variable);
		MFC_OBJ__WAIT(p_variable);

		// 2-1. MFC & Gas Flow Control
		{
			int flow_flag = -1;

			// ...
			{
				log_msg  = "\n";
				log_msg += "2-1. MFC Flow Control \n";
			}

			// ...
			{
				sCH__OBJ_SUB_MSG->Set__DATA("2-1. MFC & Gas Flow Control ...");
	
				for(i=0; i<iOBJ_MFC__SIZE; i++)
				{
					aEXT_CH__MFC__SET_FLOW[i]->Set__DATA(str__mfc_gas_flow[i]);

					if(atof(str__mfc_gas_flow[i]) > 0)
					{
						log_bff.Format("MFC CONTROL Index: %d. Run, Flow: %s \n", 
									   i+1, str__mfc_gas_flow[i]);
						log_msg += log_bff;

						// ... 
						pOBJ_CTRL__MFC[i]->Run__OBJECT(CMMD__MFC_CONTROL);

						flow_flag = 1;
					}
				}
			}

			// ...
			{
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}

		// ALL_OBJ__WAIT(p_variable,-1);
	}


	// 0. Part Initialize Set "Off" ...
	{
		Fnc__INIT_PART_ERROR(p_variable, p_alarm);
	}
	
	// 1. DGF Control ...
	{
		// ...
		{
			log_msg.Format("1. DGF Weight Set Point: %s", str__dgf_we_setpoint);

			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		// ...
		{
			sCH__OBJ_SUB_MSG->Set__DATA("1. DGF Control ...");
			aEXT_CH__DFG_WT_SETPOINT->Set__DATA(str__dgf_we_setpoint);

			if(DGF_OBJ__Start_MODE(CMMD__DGF_CONTROL) < 0)
			{
				// ...
				{
					log_msg = "[ERROR] DGF_OBJ__Start_MODE(CMMD__DGF_CONTROL) is Failed ...";
					xLOG_CTRL->WRITE__LOG(log_msg);
				}
				
				return OBJ_ABORT;
			}
		}
	}

	// 0. Lift Pin Control ...
	{
		// ...
		{
			log_msg.Format("0. Lift Pin Control : %s", str__lift_pin_pos);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(str__lift_pin_pos.CompareNoCase("Down") == 0)
		{
			sCH__OBJ_SUB_MSG->Set__DATA("Lift Pin Down Control ...");

			if(LIFT_PIN_OBJ__Start_MODE(CMMD__LIFT_PIN_DOWN) < 0)
			{
				// ...
				{
					log_msg.Format("[ERROR] LIFT_PIN_OBJ__Start_MODE(CMMD__LIFT_PIN_DOWN) is Failed ...");
					xLOG_CTRL->WRITE__LOG(log_msg);
				}
				return OBJ_ABORT;
			}
		}
		else if(str__lift_pin_pos.CompareNoCase("Up") == 0)
		{
			sCH__OBJ_SUB_MSG->Set__DATA("Lift Pin Up Control ...");

			if(LIFT_PIN_OBJ__Start_MODE(CMMD__LIFT_PIN_UP) < 0)
			{
				// ...
				{
					log_msg.Format("[ERROR] LIFT_PIN_OBJ__Start_MODE(CMMD__LIFT_PIN_UP) is Failed ...");
					xLOG_CTRL->WRITE__LOG(log_msg);
				}
				return OBJ_ABORT;
			}
		}
		else if(str__lift_pin_pos.CompareNoCase("Middle") == 0)
		{
			sCH__OBJ_SUB_MSG->Set__DATA("Lift Pin Middle(Up) Control ...");

			if(LIFT_PIN_OBJ__Start_MODE(CMMD__LIFT_PIN_MIDDLE_UP_PROC) < 0)
			{
				// ...
				{
					log_msg.Format("[ERROR] LIFT_PIN_OBJ__Start_MODE(CMMD__LIFT_PIN_MIDDLE_UP_PROC) is Failed ...");
					xLOG_CTRL->WRITE__LOG(log_msg);
				}
				return OBJ_ABORT;
			}
		}
	}

	// 3. WAP & APC Control ...
	// Pressure Control	- Position Transfer Pressure Throttle
	{

		if(str__valve_wap_control_mode.CompareNoCase("Position") == 0)
		{
			// WAP - Position Control
			{
				sCH__OBJ_SUB_MSG->Set__DATA("3. WAP - Position Control ...");

				//.....
				aEXT_CH__WAP__PRESET_POS->Set__DATA(str__ring_pos_data);
				aEXT_CH__WAP__HOLD_DELAY->Set__DATA(str__ring_hold_delay);
						
				// Learned Value is Not Ready (by wjkim)

				// aEXT_CH__WAP__POS_VALUE->Set__DATA(str__ring_learned_pos);
				aEXT_CH__WAP__POS_VALUE->Set__DATA(str__ring_pos_data);
				dEXT_CH__WAP__CONTROL_TYPE->Set__DATA(CMMD__POSITION_CONTROL);

				//
				if(atof(str__ring_ramp_time) >= 1.0)
				{
					aEXT_CH__WAP__RAMP_TIME->Set__DATA(str__ring_ramp_time);
					pOBJ_CTRL__WAP->Run__OBJECT(CMMD__WAP_RAMP_CONTROL);
				}
				else
				{
					pOBJ_CTRL__WAP->Run__OBJECT(CMMD__WAP_CONTROL);
				}
			}

			// APC - Position Control
			{
				sCH__OBJ_SUB_MSG->Set__DATA("3. APC - Position Control ...");

				//.....
				aEXT_CH__APC_PRESET_POS->Set__DATA(str__valve_pos_data);
				aEXT_CH__APC_HOLD_DELAY_TIME->Set__DATA(str__valve_hold_delay);
		
				// Learned Value is Not Ready (by wjkim)
			
				// aEXT_CH__APC_CONTROL_VALUE->Set__DATA(str__valve_learned_pos);
				aEXT_CH__APC_CONTROL_VALUE->Set__DATA(str__valve_pos_data);
				dEXT_CH__APC_CONTROL_TYPE->Set__DATA(CMMD__POSITION_CONTROL);

				//
				pOBJ_CTRL__APC->Run__OBJECT(CMMD__APC_CONTROL);
			}
		}
		else if(str__valve_wap_control_mode.CompareNoCase("Transfer") == 0)
		{
			// WAP - Position UP
			{
				sCH__OBJ_SUB_MSG->Set__DATA("3. WAP Position UP - Transfer Control ...");

				//.....
				aEXT_CH__WAP__PRESET_POS->Set__DATA(str__ring_pos_data);
				aEXT_CH__WAP__HOLD_DELAY->Set__DATA(str__ring_hold_delay);

				//
				pOBJ_CTRL__WAP->Run__OBJECT(CMMD__WAP_UP_POSITION);
			}

			// APC - Pressure Control
			{
				sCH__OBJ_SUB_MSG->Set__DATA("3. APC Pressure - Transfer Control ...");

				//.....
				aEXT_CH__APC_PRESET_POS->Set__DATA(str__valve_pos_data);
				aEXT_CH__APC_HOLD_DELAY_TIME->Set__DATA(str__valve_hold_delay);

				aEXT_CH__APC_CONTROL_VALUE->Set__DATA(str__chm_press);
				dEXT_CH__APC_CONTROL_TYPE->Set__DATA(CMMD__POSITION_CONTROL);

				// Transfer Mode에서 APC를 OPEN 시키도록 변경함.
				pOBJ_CTRL__APC->Run__OBJECT(CMMD__APC_OPEN);
			}
		}
		else if(str__valve_wap_control_mode.CompareNoCase("Pressure") == 0)
		{
			// WAP - Pressure
			{
				sCH__OBJ_SUB_MSG->Set__DATA("3. WAP Pressure - Pressure Control ...");

				//.....
				aEXT_CH__WAP__PRESET_POS->Set__DATA(str__ring_pos_data);
				
				aEXT_CH__WAP__HOLD_DELAY->Set__DATA(str__ring_hold_delay);
				aEXT_CH__WAP__PRESS_VALUE->Set__DATA(str__chm_press);
				dEXT_CH__WAP__CONTROL_TYPE->Set__DATA(CMMD__PRESSURE_CONTROL);

				//
				pOBJ_CTRL__WAP->Run__OBJECT(CMMD__WAP_PRC_CONTROL_START);
			}

			// APC - Position Control
			{
				sCH__OBJ_SUB_MSG->Set__DATA("3. APC Position - Pressure Control ...");

				//.....
				aEXT_CH__APC_PRESET_POS->Set__DATA(str__valve_pos_data);
				aEXT_CH__APC_HOLD_DELAY_TIME->Set__DATA(str__valve_hold_delay);
		
				// Learned Value is Not Ready (by wjkim)
			
				aEXT_CH__APC_CONTROL_VALUE->Set__DATA(str__valve_pos_data);
				dEXT_CH__APC_CONTROL_TYPE->Set__DATA(CMMD__POSITION_CONTROL);

				//
				pOBJ_CTRL__APC->Run__OBJECT(CMMD__APC_CONTROL);
			}
		}
		else if(str__valve_wap_control_mode.CompareNoCase("Throttle") == 0)
		{
			// WAP - Position
			{
				sCH__OBJ_SUB_MSG->Set__DATA("3. WAP Position - Throttle Control ...");

				//.....
				aEXT_CH__WAP__PRESET_POS->Set__DATA(str__ring_pos_data);
				aEXT_CH__WAP__HOLD_DELAY->Set__DATA(str__ring_hold_delay);
		
				// Learned Value is Not Ready (by wjkim)
			
				aEXT_CH__WAP__POS_VALUE->Set__DATA(str__ring_pos_data);
				dEXT_CH__WAP__CONTROL_TYPE->Set__DATA(CMMD__POSITION_CONTROL);

				//
				pOBJ_CTRL__WAP->Run__OBJECT(CMMD__WAP_CONTROL);
			}

			// APC - Pressure
			{
				sCH__OBJ_SUB_MSG->Set__DATA("3. APC Pressure - Throttle Control ...");

				// ...
				aEXT_CH__APC_PRESET_POS->Set__DATA(str__valve_pos_data);
				aEXT_CH__APC_HOLD_DELAY_TIME->Set__DATA(str__valve_hold_delay);
				aEXT_CH__APC_CONTROL_VALUE->Set__DATA(str__chm_press);

				// ...
				int hw_flag = 1;
				
				CString ctrl_device;
				dEXT_CH__APC_PRESSURE_CONTROL_DEVICE->Get__DATA(ctrl_device);
				
				if(ctrl_device.CompareNoCase(STR__SW) == 0)
				{
					hw_flag = -1;
				}

				if(hw_flag > 0)
				{
					dEXT_CH__APC_CONTROL_TYPE->Set__DATA(CMMD__PRESSURE_CONTROL);
					pOBJ_CTRL__APC->Run__OBJECT(CMMD__APC_CONTROL);
				}
				else
				{
					if(str__step_type.CompareNoCase("Stable") == 0)
					{
						sEXT_CH__APC_PROC_STEP_TYPE_STABLE_FLAG->Set__DATA(STR__YES);
					}
					else
					{
						sEXT_CH__APC_PROC_STEP_TYPE_STABLE_FLAG->Set__DATA("");
					}

					// ...
					{
						aEXT_CH__APC_PRESET_RAMP_TRG_POS->Set__DATA(str__valve_ramp_target_pos);
					}

					// ...
					{
						sEXT_CH__APC_PROC_STEP_SEC->Set__DATA("-1");
					}

					pOBJ_CTRL__APC->Run__OBJECT(CMMD__APC_PRESSURE_CTRL_PROC);
				}

				// ...
				{
					CString log_msg;
					CString log_bff;
					
					log_msg = "3. APC Pressure - Throttle Control ... \n";
					
					log_bff.Format("   1) Pressure Control Type : [%s] \n", ctrl_device);
					log_msg += log_bff;

					log_bff.Format("   3) Preset Position   : [%s] \n", str__valve_pos_data);
					log_msg += log_bff;
					
					log_bff.Format("   4) Hold Delay        : [%s] \n", str__valve_hold_delay);
					log_msg += log_bff;

					log_bff.Format("   5) Chamber Pressure  : [%s] \n", str__chm_press);
					log_msg += log_bff;

					log_bff.Format("   6.1) Preset Offset Pos  : [%s] \n", str__valve_preset_offset_pos);
					log_msg += log_bff;

					aCH__RCP_VALVE_LEARNED_POSITION->Get__DATA(var_data);
					log_bff.Format("   6.2) Preset Learned Pos : [%s] \n", var_data);
					log_msg += log_bff;

					log_bff.Format("   7) Ramp Target Pos   : [%s] \n", str__valve_ramp_target_pos);
					log_msg += log_bff;
					
					//
					xLOG_CTRL->WRITE__LOG(log_msg);
				}
			}
		}
		else
		{
			// ...
			{
				log_msg.Format("Invalid WAP Control Mode(%s)", str__valve_wap_control_mode);
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			return OBJ_ABORT;
		}
	}

	// 4. ESC Control ...
	//		1) Wafer Check
	//		2) He Set Flow Check
	{
		// ...
		{
			log_msg = "\n";

			log_bff.Format("4. ESC Control Mode (%s) Start \n", 
						   str__step_type);
			log_msg += log_bff;

			log_bff.Format("4-1. ESC Voltage Parameter - Threadhold : %s \n", 
						   str__esc_threshold);
			log_msg += log_bff;
			
			log_bff.Format("4-2. He Inner Parameter - Press : %s / Min Threshold : %s / Max Threadhold : %s \n", 
						   str__mfc_he_inner_flow, str__rf_he_inner_min_threshold, str__rf_he_inner_max_threshold);
			log_msg += log_bff;

			log_bff.Format("4-3. He Outer Parameter - Press : %s / Min Threshold : %s / Max Threadhold : %s \n", 
						   str__mfc_he_outer_flow, str__rf_he_outer_min_threshold, str__rf_he_outer_max_threshold);
			log_msg += log_bff;

			//
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		//.....
		{			
			// ESC Set Pressure / Voltage
			aEXT_CH__INNER_PRESSURE->Set__DATA(str__mfc_he_inner_flow);
			aEXT_CH__OUTER_PRESSURE->Set__DATA(str__mfc_he_outer_flow);
		
			aEXT_CH__BIAS_VOLT_THRESHOLD->Set__DATA(str__esc_threshold);

			aEXT_CH__INNER_MIN_THRESHOLD->Set__DATA(str__rf_he_inner_min_threshold);
			aEXT_CH__INNER_MAX_THRESHOLD->Set__DATA(str__rf_he_inner_max_threshold);
			aEXT_CH__OUTER_MIN_THRESHOLD->Set__DATA(str__rf_he_outer_min_threshold);
			aEXT_CH__OUTER_MAX_THRESHOLD->Set__DATA(str__rf_he_outer_max_threshold);

			dEXT_CH__EXT_BIAS_COMPENSATION_ENABLE->Set__DATA(str__esc_ext_bias_compensation_enable);
			dEXT_CH__EXT_BIAS_COMPENSATION_MODE_SELECT->Set__DATA(str__esc_ext_bias_compensation_mode_select);

			//////////////////////////////////////////////////////////////////////////
			// ESC Chuck, Dechuck, He Flow, Dump Check ... (by wjkim)
			// ESC Turn ON He Flow Config Check
		
			double dbRcp_He_Inner_Flow = 0.0;
			double dbRcp_He_Outer_Flow = 0.0;

			dbRcp_He_Inner_Flow = atof(str__mfc_he_inner_flow);
			dbRcp_He_Outer_Flow = atof(str__mfc_he_outer_flow);

			if((dbRcp_He_Inner_Flow < 0.1)&&(dbRcp_He_Outer_Flow < 0.1))
			{
				sCH__OBJ_SUB_MSG->Set__DATA("4. ESC Dechucking ...");

				pOBJ_CTRL__ESC->Run__OBJECT(CMMD__ESC_DECHUCK);
			}
			else
			{
				sCH__OBJ_SUB_MSG->Set__DATA("4. ESC Chucking ...");

				pOBJ_CTRL__ESC->Run__OBJECT(CMMD__ESC_CHUCK);
			}
		}
	}

	
	//----------------------------------------------------------------------------
	SCX__ASYNC_TIMER_CTRL async_timer;
	
	//.....
	{
		async_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__STEP_TIME_COUNT->Get__CHANNEL_NAME());
		async_timer->STOP();
		async_timer->START__COUNT_UP(99999);	
	}


	// ...
	{
		// ...
		{
			sCH__TOP_CHILLER_TEMP_SET_FLAG->Set__DATA("");
			sCH__BOTTOM_CHILLER_TEMP_SET_FLAG->Set__DATA("");
			sCH__TOP_PLATE_TEMP_SET_FLAG->Set__DATA("");
		}

		if(dCH__CFG_HEADER_APPLY_MODE->Check__DATA(STR__STEP_CTRL) > 0)
		{
			Fnc__TEMP_STEP__PWR_SET(p_variable,p_alarm);
		}
	}


	// Step Stable ...
	{	
		sCH__OBJ_SUB_MSG->Set__DATA("Step Stable Control ...");
		sCH__STEP_EDP_CHECK_SEC->Set__DATA("");

		//
		db_step_time = 30.0;

		while(db_step_time > async_timer->Get__CURRENT_TIME())
		{
			// ...
			if(Check__STEP_CONTROL() < 0)
			{ 
				nProcess_Control = 1;		
				break; 
			}
				
			// ...
			nRet = Fnc__CHECK_PART_ERROR(p_variable, p_alarm);
			if(nRet < 0)
			{ 
				nProcess_Control = nRet;	
				break; 
			}

			// ...
			if(p_variable->Check__CTRL_ABORT() > 0)
			{ 
				sCH__OBJ_MSG->Set__DATA("Process Aborted By User(2).");

				nProcess_Control = -2;	
				break; 
			}

			// ...
			nRet = Fnc__OBJ_Abort_Check(log_id);
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

			// Tolerance Abort Check ...
			if(iTOLERANCE_ABORT_FLAG > 0)
			{
				// ...
				{
					log_msg = ">>> Tolerance Abort ..."; 
					xLOG_CTRL->WRITE__LOG(log_msg);
				}

				return OBJ_ABORT;
			}


			//.....
			Sleep(1);
		}

		//.....
		{
			async_timer->STOP();

			// Stop CR Pressure Control
			dEXT_CH__WAP_PID_STOP->Set__DATA("Yes");
			sEXT_CH__APC_PID_CONTROL_STOP->Set__DATA("Yes");
		}
		

		//.....
		if(nProcess_Control == -101)			// Process OverEtch Time Over
		{
			dbProgress_Step_Time = async_timer->Get__CURRENT_TIME();

			// ...
			{
				log_msg.Format("Monitoring Timeout [%d] ... Recipe Progress Time(%.2f)", 
						       nProcess_Control, dbProgress_Step_Time);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			// ... Process OverEtch Step Overtime Alarm Post ...
			int alarm_id = ALID__PROCESS_OVERETCH_OVERTIME;
			Alarm__POST_CHECK(p_alarm, "", alarm_id);
		}
		else if(nProcess_Control < 0)			// Process Aborted
		{
			dbProgress_Step_Time = async_timer->Get__CURRENT_TIME();

			// ...
			{
				log_msg.Format("Abort [%d] ... Recipe Progress Time(%.2f)", 
							   nProcess_Control, dbProgress_Step_Time);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			
			// ... Process Abort Flag Add ...
		}
		else if(nProcess_Control == 0)			// Process Normal Complete
		{
			dbProgress_Step_Time = async_timer->Get__CURRENT_TIME();

			// ...
			{
				log_msg.Format("Monitoring Normal End [%d] ... Recipe Progress Time(%.2f)", 
							   nProcess_Control, dbProgress_Step_Time);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			if(str__step_type.CompareNoCase("Stable") == 0)
			{
				// ... Process Stable Step Overtime Alarm Post ...
				int alarm_id = ALID__PROCESS_STABLE_OVERTIME;
				CString err_msg;
				
				Fnc__Get_OBJ_Not_Available_List(err_msg);

				Alarm__POST_CHECK(p_alarm, err_msg, alarm_id);
				nProcess_Control = -10;			// Stable Step Overtime Alarm !!!
			}
		}
		else if(nProcess_Control == 1)			// Process Step Skip
		{
			dbProgress_Step_Time = async_timer->Get__CURRENT_TIME();

			// ...
			{
				log_msg.Format("Monitoring SKIP [%d] ... Recipe Progress Time(%.2f)", 
							   nProcess_Control, dbProgress_Step_Time);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
		else if(nProcess_Control == 50)			// Process EndPT OK
		{
			dbProgress_Step_Time = async_timer->Get__CURRENT_TIME();

			// ...
			{
				log_msg.Format("Monitoring EndPT End [%d] ... Recipe Progress Time(%.2f)", 
							   nProcess_Control, dbProgress_Step_Time);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
		else if(nProcess_Control == 100)		// Process Stable OK
		{
			dbProgress_Step_Time = async_timer->Get__CURRENT_TIME();

			// ...
			{
				log_msg.Format("Monitoring Stable End [%d] ... Recipe Progress Time(%.2f)", 
							   nProcess_Control, dbProgress_Step_Time);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//	Exception Continue or Jump : Process Step Complete Sequence
	//////////////////////////////////////////////////////////////////////////

	// OBJECT WAIT .....
	if((nProcess_Control < 0) 
	|| (sCH__RCP_PRE_STEP_TIME_FLAG->Check__DATA(STR__YES) < 0))
	{
		int delay_flag = 1;

		if(nProcess_Control < 0) 
		{
			delay_flag = -1;
		}

		if(ALL_OBJ__ABORT_WAIT(p_variable,p_alarm,obj_err_msg,delay_flag) < 0)
		{
		}
	}


	// Step Temperature Control ...
	if(nProcess_Control >= 0)
	{
		if(dCH__CFG_HEADER_APPLY_MODE->Check__DATA(STR__STEP_CTRL) > 0)
		{
			int temp_flag = Fnc_PROC__TEMP_STEP__WAIT(p_variable, p_alarm);
			
			if(temp_flag < 0)
			{
				// ...
				{
					log_msg.Format("Temperature Control Aborted ... : Flag (%1d)", temp_flag);
					xLOG_CTRL->WRITE__LOG(log_msg);
				}
				
				ALL_OBJ__ABORT_WAIT(p_variable,p_alarm,obj_err_msg,1);
				return -1;
			}
		}
	}

	if(nProcess_Control >= 0)
	{
		// ... Step End Information Log
		{
			dbProgress_Step_Time = async_timer->Get__CURRENT_TIME();
		
			// ...
			{
				log_msg.Format(">>> Recipe Exception Step Control End [%d] >>>>>>>>>>>>>>", 
							   nProcess_Control);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
		return OBJ_AVAILABLE;
	}
	else
	{
		// ... Step End Information Log
		{
			dbProgress_Step_Time = async_timer->Get__CURRENT_TIME();
		
			// ...
			{
				log_msg.Format(">>> Recipe Exception Step Control Aborted  [%d] >>>>>>>>>>>>>>", 
							   nProcess_Control);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
		return OBJ_ABORT;
	}
	*/

	return OBJ_ABORT;
}

int CObj__STEP_FNC
::Fnc__PROC(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	// ...
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

	CString str__plasma_power;
	CString str__plasma_pulse_freq;
	CString str__plasma_duty;
	CString str__bias_power;
	CString str__bias_pulse_freq;
	CString str__bias_duty;

	CString str__plasma_ctrl_mode;
	CString str__plasma_mat_c1_output;
	CString str__plasma_mat_c1_preset;
	CString str__plasma_mat_c1_learned;
	CString str__plasma_mat_c2_output;
	CString str__plasma_mat_c2_preset;
	CString str__plasma_mat_c2_learned;

	CString str__bias_ctrl_mode;
	CString str__bias_mat_c1_output;
	CString str__bias_mat_c1_preset;
	CString str__bias_mat_c1_learned;
	CString str__bias_mat_c2_output;
	CString str__bias_mat_c2_preset;
	CString str__bias_mat_c2_learned;

	CString str__top_frc_center;

	CString str__gas_xx_flow[CFG_SIZE__MFC_OBJ];

	CString str__ecs_center_temp;
	CString str__ecs_edge_temp;

	CString str__esc_ctrl_mode;
	CString str__dpc_center_pressure;
	CString str__dpc_edge_pressure;
	
	CString str__dpc_center_flow_min_threshold;
	CString str__dpc_center_flow_max_threshold;
	CString str__dpc_edge_flow_min_threshold;
	CString str__dpc_edge_flow_max_threshold;

	CString str__lift_pin_mode;

	CString str__loop_start;
	CString str__loop_repeat;

	int i_limit;
	int i;

	// ...
	{
		sCH__RCP_STEP_MESSAGE->Get__DATA(str__step_msg);
		dCH__RCP_STEP_MODE->Get__DATA(str__step_mode);
		aCH__RCP_STEP_TIME->Get__DATA(str__step_time);

		//
		dCH__RCP_APC_MODE->Get__DATA(str__apc_mode);
		aCH__RCP_APC_PRESSURE->Get__DATA(str__apc_pressure);
		aCH__RCP_APC_POSITION->Get__DATA(str__apc_position);
		aCH__RCP_APC_HOLD_DELAY->Get__DATA(str__apc_hold_delay);

		aCH__RCP_APC_PRESET_POS->Get__DATA(str__apc_preset_pos);
		double value__preset_pos = atof(str__apc_preset_pos);
		if(value__preset_pos < 1.0)		aCH__RCP_APC_LEARNED_POS->Get__DATA(str__apc_preset_pos);

		//
		aCH__RCP_RF_PLASMA_POWER->Get__DATA(str__plasma_power);
		aCH__RCP_RF_PLASMA_PULSE_FREQ->Get__DATA(str__plasma_pulse_freq);
		aCH__RCP_RF_PLASMA_DUTY->Get__DATA(str__plasma_duty);

		aCH__RCP_RF_BIAS_POWER->Get__DATA(str__bias_power);
		aCH__RCP_RF_BIAS_PULSE_FREQ->Get__DATA(str__bias_pulse_freq);
		aCH__RCP_RF_BIAS_DUTY->Get__DATA(str__bias_duty);

		dCH__RCP_PLASMA_CTRL_MODE->Get__DATA(str__plasma_ctrl_mode);
		aCH__RCP_PLASMA_MATCHER_C1_OUTPUT->Get__DATA(str__plasma_mat_c1_output);
		aCH__RCP_PLASMA_MATCHER_C1_PRESET->Get__DATA(str__plasma_mat_c1_preset);
		aCH__RCP_PLASMA_MATCHER_C1_LEARNED->Get__DATA(str__plasma_mat_c1_learned);
		aCH__RCP_PLASMA_MATCHER_C2_OUTPUT->Get__DATA(str__plasma_mat_c2_output);
		aCH__RCP_PLASMA_MATCHER_C2_PRESET->Get__DATA(str__plasma_mat_c2_preset);
		aCH__RCP_PLASMA_MATCHER_C2_LEARNED->Get__DATA(str__plasma_mat_c2_learned);
		
		dCH__RCP_BIAS_CTRL_MODE->Get__DATA(str__bias_ctrl_mode);
		aCH__RCP_BIAS_MATCHER_C1_OUTPUT->Get__DATA(str__bias_mat_c1_output);
		aCH__RCP_BIAS_MATCHER_C1_PRESET->Get__DATA(str__bias_mat_c1_preset);
		aCH__RCP_BIAS_MATCHER_C1_LEARNED->Get__DATA(str__bias_mat_c1_learned);
		aCH__RCP_BIAS_MATCHER_C2_OUTPUT->Get__DATA(str__bias_mat_c2_output);
		aCH__RCP_BIAS_MATCHER_C2_PRESET->Get__DATA(str__bias_mat_c2_preset);
		aCH__RCP_BIAS_MATCHER_C2_LEARNED->Get__DATA(str__bias_mat_c2_learned);

		aCH__RCP_TOP_FRC_CENTER->Get__DATA(str__top_frc_center);

		for(i=0; i<CFG_SIZE__MFC_OBJ; i++)
		{
			aCH__RCP_GAS_XX_FLOW[i]->Get__DATA(str__gas_xx_flow[i]);
		}

		dCH__RCP_ESC_CTRL_MODE->Get__DATA(str__esc_ctrl_mode);
		aCH__RCP_DPC_CENTER->Get__DATA(str__dpc_center_pressure);
		aCH__RCP_DPC_EDGE->Get__DATA(str__dpc_edge_pressure);
		
		aCH__RCP_DPC_CENTER_FLOW_MIN_THRESHOLD->Get__DATA(str__dpc_center_flow_min_threshold);
		aCH__RCP_DPC_CENTER_FLOW_MAX_THRESHOLD->Get__DATA(str__dpc_center_flow_max_threshold);
		aCH__RCP_DPC_EDGE_FLOW_MIN_THRESHOLD->Get__DATA(str__dpc_edge_flow_min_threshold);
		aCH__RCP_DPC_EDGE_FLOW_MAX_THRESHOLD->Get__DATA(str__dpc_edge_flow_max_threshold);

		aCH__RCP_ESC_CENTER_TEMP->Get__DATA(str__ecs_center_temp);
		aCH__RCP_ESC_EDGE_TEMP->Get__DATA(str__ecs_edge_temp);

		dCH__RCP_LIFT_PIN_MODE->Get__DATA(str__lift_pin_mode);

		aCH__RCP_LOOP_START->Get__DATA(str__loop_start);
		aCH__RCP_LOOP_REPEAT->Get__DATA(str__loop_repeat);
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
			str_msg.Format("Step(%1d) : Learned Mode Appling ...", step_id);

			sCH__LEARNED_APPLY_STATUS->Set__DATA(str_msg);
		}
		else
		{
			CString str_msg;
			str_msg.Format("Step(%1d) : Preset Mode Appling ...", step_id);

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
		log_msg = ">>> Recipe Step Control Start  >>>>>>>>>>>>>> \n";
			
		log_bff.Format(">>> Step Name : %s / Type : %s / Time : %s / ", 
					   str__step_msg, 
					   str__step_mode, 
					   str__step_time);
		log_msg += log_bff;
		log_msg += "\n";

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// Fnc__DCOP_STEP_INIT();

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

	// ...
	{
		// Fnc__DCOP_STEP_START();
		// Fnc__INIT_PART_ERROR(p_variable, p_alarm);

		// ALL_MFC__ABORTED_TO_AVAILABLE(p_variable);
		// MFC_OBJ__WAIT(p_variable);

		sCH__RCP_MATCHER_TOP__CTRL_REQ->Set__DATA(STR__YES);
		SetEvent(hEVENT__RCP_MATCHER_CTRL);
	}

	// Recipe Control : Turn_On ...
	{
		// 0. FRC Control
		{
			sCH__OBJ_SUB_MSG->Set__DATA("0. FRC1 Control ...");

			aEXT_CH__FRC1__CENTER_FLOW->Set__DATA(str__top_frc_center);
	
			// ...
			{
				log_msg  = "\n";
				log_msg += "0. FRC1 Control \n";

				log_bff.Format("  * top_frc_center  <- %s \n", str__top_frc_center);
				log_msg += log_bff;
				
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}

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

				pOBJ_CTRL__VAC_VLV->Call__OBJECT("FR_OPEN.IO");
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
			// MFC Interlock Check ...
			{
				sCH__OBJ_SUB_MSG->Set__DATA("2.2  MFC Interlock Gas Close ...");
			
				// ...
				{
					log_msg  = "\n";
					log_msg += "2.2 MFC Interlock List \n";
				}
				
				for(i=0; i<iOBJ_MFC__SIZE; i++)
				{
					if(atof(str__gas_xx_flow[i]) < 0.1)
					{
						continue;
					}

					// ...
					CUIntArray l_lock_index;

					if(Get__MFC_Interlock_Index(i,l_lock_index) > 0)
					{
						CUIntArray l_mfc_index;
						int check_count = 0;

						int kk_limit = l_lock_index.GetSize();
						int kk;

						for(kk=0;kk<kk_limit;kk++)
						{
							int db_i = l_lock_index[kk];

							if(atof(str__gas_xx_flow[db_i]) > 0)
							{
								// ...
								{
									check_count++;

									if(check_count == 1)
									{
										log_bff.Format("   Turn-On : MFC (%1d) <- %s \n", i+1,str__gas_xx_flow[i]);					
										log_msg += log_bff;
									}

									log_bff.Format("   ** Turn-Off : MFC (%1d) <- %s \n", db_i+1,str__gas_xx_flow[db_i]);
									log_msg += log_bff;
								}
							
								aEXT_CH__MFC__SET_FLOW[db_i]->Set__DATA(str__gas_xx_flow[db_i]);
								pOBJ_CTRL__MFC[db_i]->Run__OBJECT(CMMD__MFC_CLOSE);

								l_mfc_index.Add(db_i);
							}
						}

						// ...
						kk_limit = l_mfc_index.GetSize();
						
						for(kk=0;kk<kk_limit;kk++)
						{
							int db_i = l_mfc_index[kk];

							// ...
							{
								int alarm_id = ALID__MFC_INTERLOCK_CLOSE_ERROR;
								CString alm_msg;
								CString alm_bff;
								CString r_act;

								alm_bff.Format("In this step, MFC%1d's flow will be set to \"%s\". \n",
									           i+1,
											   str__gas_xx_flow[i]);
								alm_msg  = alm_bff;

								alm_bff.Format("But, Interlock MFC%1d's flow must be closed. \n",
									           db_i+1);
								alm_msg += alm_bff;

								alm_msg += "So, this step is aborted. \n";

								p_alarm->Check__ALARM(alarm_id,r_act);
								p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
							}

							xLOG_CTRL->WRITE__LOG(log_msg);
							return -1;
						}
					}
				}

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			// MFC Control ...
			{
				sCH__OBJ_SUB_MSG->Set__DATA("2. MFC & Gas Flow Control ...");

				// ...
				{
					log_msg  = "\n";
					log_msg += "2.2 MFC Flow Control \n";
				}
				
				for(i=0; i<iOBJ_MFC__SIZE; i++)
				{
					if(atof(str__gas_xx_flow[i]) > 0)
					{
						sCH__PRE_RCP_MFC_SET_FLOW[i]->Set__DATA(str__gas_xx_flow[i]);

						// ...
						{
							log_bff.Format("MFC CONTROL Index: %d. Run, Flow: %s \n", 
									       i+1, str__gas_xx_flow[i]);
							log_msg += log_bff;
						}

						aEXT_CH__MFC__SET_FLOW[i]->Set__DATA(str__gas_xx_flow[i]);
						pOBJ_CTRL__MFC[i]->Run__OBJECT(CMMD__MFC_CONTROL);
					}
				}

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}

		// 3. RF_Generator Control
		{
			// ...
			{
				log_msg  = "\n";

				log_msg += "* RF_Generator Control \n";

				log_bff.Format("   1)  BIAS_Power  <-  %s \n", str__bias_power);
				log_msg += log_bff;

				log_bff.Format("   2)  PLASMA_Power    <-  %s \n", str__plasma_power);
				log_msg += log_bff;

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			sCH__OBJ_SUB_MSG->Set__DATA("RF ON ...");

			// ...
			int active__rf_hf_set = -1;

			CII_EXT_OBJECT__CTRL *p_obj_ctrl;
			CII__VAR_ANALOG_CTRL *p_set_pwr;
			CString rf_name;

			int rf_limit = 2;
			int i;

			for(i=0; i<rf_limit; i++)
			{
				double set_pwr = 0.0;
				CString rf_cmmd;

				if(i == 0)			// BIAS
				{
					rf_name = "RF_BIAS";

					p_obj_ctrl = pOBJ_CTRL__RF_BIAS;
					p_set_pwr  = aEXT_CH__RF_BIAS__PARA_SET_POWER.Get__PTR();

					set_pwr = atoi(str__bias_power);
					rf_cmmd = "SET_POWER";
				}
				else if(i == 1)		// PLASMA
				{
					rf_name = "RF_PLASMA";

					p_obj_ctrl = pOBJ_CTRL__RF_PLASMA;
					p_set_pwr  = aEXT_CH__RF_PLASMA__PARA_SET_POWER.Get__PTR();

					set_pwr = atoi(str__plasma_power);
					rf_cmmd = "SET_POWER";

					if(set_pwr > 0)
					{
						active__rf_hf_set = 1;
					}
				}
				else
				{
					continue;
				}

				if(set_pwr < 0.0001)
				{
					continue;
				}

				// ...
				{
					p_set_pwr->Set__VALUE(set_pwr);
					p_obj_ctrl->Run__OBJECT(rf_cmmd);
				}

				// ...
				{
					CString log_bff;

					log_msg = "\n";

					log_bff.Format("%s <- ON \n", rf_name);
					log_msg += log_bff;

					log_bff.Format(" * %s <- %.1f \n",
									p_set_pwr->Get__CHANNEL_NAME(),
									p_set_pwr->Get__VALUE());
					log_msg += log_bff;

					log_bff.Format(" * RF_CMMD <- %s \n", rf_cmmd);
					log_msg += log_bff;

					xLOG_CTRL->WRITE__LOG(log_msg);
				}
			}

		}

		// 4. ESC Control 
		{
			// ...
			{
				log_msg = "\n";

				log_bff.Format("* ESC Control Mode (%s) Start \n", str__esc_ctrl_mode);
				log_msg += log_bff;

				log_bff.Format("   1) DPC_Center <-  %s \n", str__dpc_center_pressure);
				log_msg += log_bff;
				
				log_bff.Format("   2) DPC_Edge <-  %s \n", str__dpc_edge_pressure);
				log_msg += log_bff;

				log_bff.Format("   3) Center_Flow_Min_Threshold <-  %s \n", str__dpc_center_flow_min_threshold);
				log_msg += log_bff;
				
				log_bff.Format("   4) Center_Flow_Max_Threshold <-  %s \n", str__dpc_center_flow_max_threshold);
				log_msg += log_bff;
				
				log_bff.Format("   5) Edge_Flow_Min_Threshold <-  %s \n", str__dpc_edge_flow_min_threshold);
				log_msg += log_bff;
				
				log_bff.Format("   6) Edge_Flow_Max_Threshold <-  %s \n", str__dpc_edge_flow_max_threshold);
				log_msg += log_bff;

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			// ESC Set Pressure / Voltage
			if(str__esc_ctrl_mode.CompareNoCase("NoChange") != 0)
			{	
				// ...
				{
					sEXT_CH__ESC__RCP_He_CENTER_PRESSURE_SETPOINT_TORR->Set__DATA(str__dpc_center_pressure);
					sEXT_CH__ESC__RCP_He_EDGE_PRESSURE_SETPOINT_TORR->Set__DATA(str__dpc_edge_pressure);

					sEXT_CH__ESC__RCP_He_CENTER_FLOW_MAX_THRESHOLD->Set__DATA(str__dpc_center_flow_min_threshold);
					sEXT_CH__ESC__RCP_He_CENTER_FLOW_MIN_THRESHOLD->Set__DATA(str__dpc_center_flow_max_threshold);
					sEXT_CH__ESC__RCP_He_EDGE_FLOW_MAX_THRESHOLD->Set__DATA(str__dpc_edge_flow_min_threshold);
					sEXT_CH__ESC__RCP_He_EDGE_FLOW_MIN_THRESHOLD->Set__DATA(str__dpc_edge_flow_max_threshold);
				}

				if((str__esc_ctrl_mode.CompareNoCase("CHUCK")    == 0)
				|| (str__esc_ctrl_mode.CompareNoCase("CHUCK1")   == 0)
				|| (str__esc_ctrl_mode.CompareNoCase("CHUCK2")   == 0)
				|| (str__esc_ctrl_mode.CompareNoCase("DECHUCK")  == 0)
				|| (str__esc_ctrl_mode.CompareNoCase("DECHUCK1") == 0)
				|| (str__esc_ctrl_mode.CompareNoCase("DECHUCK2") == 0))
				{
					CString obj__esc_mode = str__esc_ctrl_mode;

					     if(str__esc_ctrl_mode.CompareNoCase("CHUCK")  == 0)		obj__esc_mode = "CHUCK.PROC";
					else if(str__esc_ctrl_mode.CompareNoCase("CHUCK1") == 0)		obj__esc_mode = "CHUCK1.PROC";
					else if(str__esc_ctrl_mode.CompareNoCase("CHUCK2") == 0)		obj__esc_mode = "CHUCK2.PROC";

					pOBJ_CTRL__ESC->Run__OBJECT(obj__esc_mode);
				}
				else if(str__esc_ctrl_mode.CompareNoCase("HE.SET") == 0)
				{
					pOBJ_CTRL__ESC->Run__OBJECT("HE_SET.PROC");
				}
				else
				{
					pOBJ_CTRL__ESC->Run__OBJECT("HE.CLOSE");
				}
			}
		}
	}
	
	// Recipe Control : Turn_Off ...
	{
		// RF OFF ...
		if(aCH__CFG_STEP_DELAY_RF_OFF->Get__VALUE() >= 0.1)
		{
			sCH__ACTIVE__RF_TURN_OFF_DELAY->Set__DATA(STR__YES);
		}
		else
		{
			sCH__ACTIVE__RF_TURN_OFF_DELAY->Set__DATA("");

			// ...
			sCH__OBJ_SUB_MSG->Set__DATA("RF OFF ...");

			CII_EXT_OBJECT__CTRL *p_obj_ctrl;
			CII__VAR_ANALOG_CTRL *p_set_pwr;
			CString rf_name;
			CString rf_cmmd;

			int rf_limit = 2;
			int i;

			for(i=0; i<rf_limit; i++)
			{
				double set_pwr = 0.0;

				if(i == 0)			// BIAS
				{
					rf_name = "RF_BIAS";

					p_obj_ctrl = pOBJ_CTRL__RF_BIAS;
					p_set_pwr  = aEXT_CH__RF_BIAS__PARA_SET_POWER.Get__PTR();

					set_pwr = atoi(str__bias_power);
				}
				else if(i == 1)		// PLASMA
				{
					rf_name = "RF_PLASMA";

					p_obj_ctrl = pOBJ_CTRL__RF_PLASMA;
					p_set_pwr  = aEXT_CH__RF_PLASMA__PARA_SET_POWER.Get__PTR();

					set_pwr = atoi(str__plasma_power);
				}
				else
				{
					continue;
				}

				if(set_pwr >= 0.1)
				{
					continue;
				}

				// ...
				{
					p_set_pwr->Set__DATA("0.0");
					p_obj_ctrl->Run__OBJECT("OFF");
				}

				// ...
				{
					log_msg.Format("%s <- OFF", rf_name);

					xLOG_CTRL->WRITE__LOG(log_msg);
				}
			}
		}

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

			for(i=0; i<iOBJ_MFC__SIZE; i++)
			{
				if(atof(str__gas_xx_flow[i]) > 0)
				{
					continue;
				}

				aEXT_CH__MFC__SET_FLOW[i]->Set__DATA("0");
				pOBJ_CTRL__MFC[i]->Run__OBJECT(CMMD__MFC_CLOSE);

				// ...
				{
					log_bff.Format("  * MFC%1d <- 0.0 \n", i+1);
					log_msg += log_bff;
				}
			}

			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}
	
	
	// Lift_Pin Control ...
	{
		// ...
		{
			log_msg.Format("* Lift_Pin Control : %s", str__lift_pin_mode);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(str__lift_pin_mode.CompareNoCase("Up") == 0)
		{
			sCH__OBJ_SUB_MSG->Set__DATA("Lift_Pin Proc.Up Control ...");

			x_step_timer->STOP();

			if(pOBJ_CTRL__LIFT_PIN->Call__OBJECT(CMMD__LIFT_PIN__PROC_UP) < 0)
			{
				return -101;
			}

			x_step_timer->START__COUNT_UP(99999);	
		}
		else if(str__lift_pin_mode.CompareNoCase("Middle") == 0)
		{
			sCH__OBJ_SUB_MSG->Set__DATA("Lift_Pin Proc.Middle Control ...");

			pOBJ_CTRL__LIFT_PIN->Run__OBJECT(CMMD__LIFT_PIN__PROC_MIDDLE);
		}
		else
		{
			sCH__OBJ_SUB_MSG->Set__DATA("Lift_Pin Proc.Down Control ...");

			pOBJ_CTRL__LIFT_PIN->Run__OBJECT(CMMD__LIFT_PIN__PROC_DOWN);
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
			SCX__STEP_TIMER_CTRL x_step_timer_ctrl;
			double result__step_sec;
			double cur__step_sec;

			double offset_sec = aCH__CFG_STEP_TIME_OFFSET_SEC->Get__VALUE();
			x_step_timer_ctrl->Enable__QUERY_COUNT(offset_sec);

			x_step_timer_ctrl->START__TIMER();

			// ...
			nProcess_Control = 0;		

			// Delay ....
			if(sEXT_CH__LAST_STEP_FLAG->Check__DATA("YES") < 0)
			{
				// ???
			}

			sCH__OBJ_SUB_MSG->Set__DATA("Step Time Control ...");
			sCH__STEP_EDP_CHECK_SEC->Set__DATA("");

			while(!x_step_timer_ctrl->Check__CURRENT_TIME(db_step_time, cur__step_sec))
			{
				Control__RECIPE_DELAY_PARAMETER(x_step_timer->Get__CURRENT_TIME());

				if(iActive__SIM_MODE > 0)
				{
					if(dEXT_CH__CFG_SCH_TEST_SIM_ALARM_STEP_ACTIVE->Check__DATA(STR__ENABLE) > 0)
					{
						nProcess_Control = -1;
						break; 
					}
				}

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
			}

			// ...
			{ 
				CString log_msg;

				log_msg.Format(" * result step_sec (%.3f) <- (%.3f) (%.3f)", 
							   db_step_time,
							   cur__step_sec,
							   x_step_timer->Get__CURRENT_TIME());

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
		// 2. Stable Control
		else if(str__step_mode.CompareNoCase("Stable") == 0)
		{
			nProcess_Control = 0;		

			// ...
			sCH__OBJ_SUB_MSG->Set__DATA("Step Stable Control ...");
			sCH__STEP_EDP_CHECK_SEC->Set__DATA("");

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
		}
		else if(nProcess_Control == 0)		// Process Normal Complete
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
	
	
	//------------------------------------------------------------------------
	if(dEXT_CH__SLOT01_STATUS->Check__DATA(STR__NONE) < 0)
	{
		CString ch_data;

		aEXT_CH__STEP_CUR_NUM->Get__DATA(ch_data);
		int step_id = atoi(ch_data);

		if(nProcess_Control >= 0)
		{	
			CString data__apc_pos;
			
			// APC VALVE 
			{
				data__apc_pos = sEXT_CH__APC_IO__CUR_VLV_POS->Get__STRING();
			}
			
			// ...
			CDS__LEARNED_ITEM_INFO ds_info;
		
			// ...
			{
				sEXT_CH__STEP_ID->Get__DATA(var_data);
				ds_info.iSTEP_ID = atoi(var_data);

				// 
				ds_info.sDATA__APC = data__apc_pos;

				//
				mDB__LEARNED_ITEM_CTRL.Load__ITEM(ds_info);
			}
		}
	}
	//------------------------------------------------------------------------

	
	if(nProcess_Control >= 0)
	{
		if(pOBJ_CTRL__ESC->When__OBJECT() < 0)
		{
			nProcess_Control = -1;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	//	Normal Process Step Complete Sequence
	//////////////////////////////////////////////////////////////////////////

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

void CObj__STEP_FNC
::Control__RECIPE_DELAY_PARAMETER(const double step_sec, const int set_req)
{
	if(sCH__ACTIVE__RF_TURN_OFF_DELAY->Check__DATA(STR__YES) > 0)
	{
		if((set_req  >  0)
		|| (step_sec >= aCH__CFG_STEP_DELAY_RF_OFF->Get__VALUE()))
		{
			sCH__ACTIVE__RF_TURN_OFF_DELAY->Set__DATA("");

			// ...
			CII_EXT_OBJECT__CTRL *p_obj_ctrl;
			CII__VAR_ANALOG_CTRL *p_set_pwr;
			CString rf_name;

			int rf_limit = 2;
			int i;

			for(i=0; i<rf_limit; i++)
			{
				double set_pwr = 0.0;

				if(i == 0)			// BIAS
				{
					rf_name = "RF_BIAS";

					p_obj_ctrl = pOBJ_CTRL__RF_BIAS;
					p_set_pwr  = aEXT_CH__RF_BIAS__PARA_SET_POWER.Get__PTR();

					set_pwr = aCH__RCP_RF_BIAS_POWER->Get__VALUE();
				}
				else if(i == 1)		// PLASMA
				{
					rf_name = "RF_PLASMA";

					p_obj_ctrl = pOBJ_CTRL__RF_PLASMA;
					p_set_pwr  = aEXT_CH__RF_PLASMA__PARA_SET_POWER.Get__PTR();

					set_pwr = aCH__RCP_RF_PLASMA_POWER->Get__VALUE();
				}
				else
				{
					continue;
				}

				if(set_pwr >= 0.1)
				{
					continue;
				}

				// ...
				{
					p_set_pwr->Set__DATA("0.0");
					p_obj_ctrl->Run__OBJECT("OFF");
				}

				// ...
				{
					CString log_msg;

					log_msg.Format("%s <- Delay_Turn_Off", rf_name);

					xLOG_CTRL->WRITE__LOG(log_msg);
				}
			}
		}
	}

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

			for(int i=0; i<iOBJ_MFC__SIZE; i++)
			{
				if(aCH__RCP_GAS_XX_FLOW[i]->Get__VALUE() > 0)
				{
					continue;
				}

				aEXT_CH__MFC__SET_FLOW[i]->Set__DATA("0");
				pOBJ_CTRL__MFC[i]->Run__OBJECT(CMMD__MFC_CLOSE);

				// ...
				{
					log_bff.Format("  * MFC%1d <- 0.0 \n", i+1);
					log_msg += log_bff;
				}
			}

			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// ...
}


void CObj__STEP_FNC::ALL_OBJ__WAIT(CII_OBJECT__VARIABLE* p_variable,const int mfc_check)
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

void CObj__STEP_FNC
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
		for(i=0; i<iOBJ_MFC__SIZE; i++)
		{
			if(pOBJ_CTRL__MFC[i]->Is__OBJ_BUSY() > 0)
			{
				check_flag = 1;

				// ...
				{
					log_bff.Format("MFC%1d : Busy \n", i+1);
					log_msg += log_bff; 
				}

				// ...
				if(busy_abort_flag > 0)
				{
					OBJ_ABORT_flag = 1;

					log_bff.Format("MFC%1d is not completed. \n", i+1);
					str_abort_msg += log_bff;
				}
			}
		}

		if(check_flag < 0)
		{
			if(x_async_timer->Get__CURRENT_TIME() > 1.0)
			{
				log_msg.Format("All_Obj__Wait_Sec() : Error-Check (%.3f) ...", x_async_timer->Get__CURRENT_TIME());
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
				// ...
				{
					sCH__STEP_TIME_ABORT_FLAG->Set__DATA(STR__YES);
				}

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

void CObj__STEP_FNC::ALL_OBJ__ABORTED_TO_AVAILABLE(CII_OBJECT__VARIABLE *p_variable)
{
	CString log_msg;


	// APC OBJ
	if(dEXT_CH__APC_OBJ__CTRL->Check__DATA(STR__ABORTED) > 0)
	{
		dEXT_CH__APC_OBJ__CTRL->Set__DATA(STR__AVAILABLE);

		//
		log_msg = "APC CTRL : ABORTED -> AVAILABLE";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	/*
	// DGF OBJ
	if(dEXT_CH__DGF_OBJ_CTRL->Check__DATA(STR__ABORTED) > 0)
	{
		dEXT_CH__DGF_OBJ_CTRL->Set__DATA(STR__AVAILABLE);

		//
		log_msg = "DGF CTRL : ABORTED -> AVAILABLE";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// 2 MHz
	if(dEXT_CH__RF_2MHz_OBJ_CTRL->Check__DATA(STR__ABORTED) > 0)
	{
		dEXT_CH__RF_2MHz_OBJ_CTRL->Set__DATA(STR__AVAILABLE);

		//
		log_msg = "RF 2MHz CTRL : ABORTED -> AVAILABLE";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	// 27 MHz
	if(dEXT_CH__RF_27MHz_OBJ_CTRL->Check__DATA(STR__ABORTED) > 0)
	{
		dEXT_CH__RF_27MHz_OBJ_CTRL->Set__DATA(STR__AVAILABLE);

		//
		log_msg = "RF 27MHz CTRL : ABORTED -> AVAILABLE";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	// 60 MHz
	if(dEXT_CH__RF_60MHz_OBJ_CTRL->Check__DATA(STR__ABORTED) > 0)
	{
		dEXT_CH__RF_60MHz_OBJ_CTRL->Set__DATA(STR__AVAILABLE);

		//
		log_msg = "RF 60MHz CTRL : ABORTED -> AVAILABLE";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// RFx MAT OBJ
	if(dEXT_CH__RF_MATCHER_OBJ_CTRL->Check__DATA(STR__ABORTED) > 0)
	{
		dEXT_CH__RF_MATCHER_OBJ_CTRL->Set__DATA(STR__AVAILABLE);

		//
		log_msg = "RFx MATCHER CTRL : ABORTED -> AVAILABLE";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// HEATER OBJ
	if(dEXT_CH__HEATER_WALL_OBJ_CTRL->Check__DATA(STR__ABORTED) > 0)
	{
		dEXT_CH__HEATER_WALL_OBJ_CTRL->Set__DATA(STR__AVAILABLE);

		//
		log_msg = "HEATER CTRL : ABORTED -> AVAILABLE";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ESC OBJ
	if(dEXT_CH__ESC__OBJ_CTRL->Check__DATA(STR__ABORTED) > 0)
	{
		dEXT_CH__ESC__OBJ_CTRL->Set__DATA(STR__AVAILABLE);

		//
		log_msg = "ESC CTRL : ABORTED -> AVAILABLE";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// CHILLER OBJ
	if(dEXT_CH__CHILLER__OBJ_CTRL->Check__DATA(STR__ABORTED) > 0)
	{
		dEXT_CH__CHILLER__OBJ_CTRL->Set__DATA(STR__AVAILABLE);

		//
		log_msg = "CHILLER CTRL : ABORTED -> AVAILABLE";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	*/
			
	/*
	// LIFT_PIN OBJ
	if(dEXT_CH__LIFT_PIN__OBJ_CTRL->Check__DATA(STR__ABORTED) > 0)
	{
		dEXT_CH__LIFT_PIN__OBJ_CTRL->Set__DATA(STR__AVAILABLE);

		//
		log_msg = "LIFT PIN CTRL : ABORTED -> AVAILABLE";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	*/

	// MFC OBJ - FNC .....
	{
		ALL_MFC__ABORTED_TO_AVAILABLE(p_variable);
	}
}
void CObj__STEP_FNC::ALL_MFC__ABORTED_TO_AVAILABLE(CII_OBJECT__VARIABLE *p_variable)
{
	CString log_msg;
	CString log_bff;


	// MFC OBJ - FNC .....
	{
		log_msg = "\n";

		for(int i=0; i<iOBJ_MFC__SIZE; i++)
		{
			if(dEXT_CH__MFC__OBJ_CTRL[i]->Check__DATA(STR__ABORTED) > 0)
			{
				dEXT_CH__MFC__OBJ_CTRL[i]->Set__DATA(STR__AVAILABLE);

				//
				log_bff.Format("MFC%1d CTRL : ABORTED -> AVAILABLE \n", i+1);
				log_msg += log_bff;
			}
		}

		//
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
}

void CObj__STEP_FNC::MFC_OBJ__WAIT(CII_OBJECT__VARIABLE* p_variable)
{
	CString log_msg;
	CString log_bff;

	CString var_data;


	// MFC OBJ - FNC .....
	{
		log_msg = "\n";

		// ...
		int i;

		for(i=0; i<iOBJ_MFC__SIZE; i++)
		{
			var_data.Format("MFC(%1d) Object Wait ... \n", i+1);
			log_msg += var_data;

			// ...
			sCH__OBJ_SUB_MSG->Set__DATA(var_data);

			pOBJ_CTRL__MFC[i]->When__OBJECT();
		}

		//
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
}

// ALL OBJECT - ABORT .....
int  CObj__STEP_FNC::
ALL_OBJ__ABORT_WAIT(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm,
				    CString& err_msg,
					const int delay_flag)
{
	CString log_msg;

	int err_flag = -1;
	int i;

	// ...
	{
		sCH__STEP_TIME_ABORT_FLAG->Set__DATA("");
	}

	if(delay_flag > 0)
	{
		ALL_OBJ__WAIT_SEC(p_variable,p_alarm);
	}

	// ...
	err_msg = "";
	
	// APC ...
	if(pOBJ_CTRL__APC->Is__OBJ_BUSY() > 0)
	{
		log_msg = "ABORT : APC OBJ ...";
		xLOG_CTRL->WRITE__LOG(log_msg);

		// sEXT_CH__APC_PID_CONTROL_STOP->Set__DATA("Yes");
		pOBJ_CTRL__APC->Abort__OBJECT();

		err_msg += "APC Object. \n";
	}

	/*
	// DGF ...
	if(pOBJ_CTRL__DGF->Is__OBJ_BUSY() > 0)
	{
		log_msg = "ABORT : DGF OBJ ...";
		xLOG_CTRL->WRITE__LOG(log_msg);

		pOBJ_CTRL__DGF->Abort__OBJECT();

		err_msg += "DGF Object. \n";
	}

	// RF : 2 MHz ...
	if(pOBJ_CTRL__RF_GEN_2MHz->Is__OBJ_BUSY() > 0)
	{
		log_msg = "ABORT : RF 2MHz OBJ ...";
		xLOG_CTRL->WRITE__LOG(log_msg);

		//
		pOBJ_CTRL__RF_GEN_2MHz->Abort__OBJECT();

		//
		err_msg += "RF GEN 2MHz Object. \n";
	}
	// RF : 27 MHz ...
	if(pOBJ_CTRL__RF_GEN_27MHz->Is__OBJ_BUSY() > 0)
	{
		log_msg = "ABORT : RF 27MHz OBJ ...";
		xLOG_CTRL->WRITE__LOG(log_msg);

		//
		pOBJ_CTRL__RF_GEN_27MHz->Abort__OBJECT();

		//
		err_msg += "RF GEN 27MHz Object. \n";
	}
	// RF : 60 MHz ...
	if(pOBJ_CTRL__RF_GEN_60MHz->Is__OBJ_BUSY() > 0)
	{
		log_msg = "ABORT : RF 60MHz OBJ ...";
		xLOG_CTRL->WRITE__LOG(log_msg);

		//
		pOBJ_CTRL__RF_GEN_60MHz->Abort__OBJECT();

		//
		err_msg += "RF GEN 60MHz Object. \n";
	}

	// RFx MAT OBJ ...
	if(pOBJ_CTRL__RF_MATCH->Is__OBJ_BUSY() > 0)
	{
		log_msg = "ABORT : RFx MAT OBJ ...";
		xLOG_CTRL->WRITE__LOG(log_msg);

		//
		pOBJ_CTRL__RF_MATCH->Abort__OBJECT();

		//
		err_msg += "RF Matcher Object. \n";
	}
	*/

	// HEATER OBJ ...
	/*
	if(pOBJ_CTRL__HEATER_WALL->Is__OBJ_BUSY() > 0)
	{
		log_msg = "ABORT : HEATER OBJ ...";
		xLOG_CTRL->WRITE__LOG(log_msg);

		//
		pOBJ_CTRL__HEATER_WALL->Abort__OBJECT();

		//
		err_msg += "Heater Wall Object. \n";
	}
	*/

	/*
	// ESC OBJ ...
	if(pOBJ_CTRL__ESC->Is__OBJ_BUSY() > 0)
	{
		log_msg = "ABORT : ESC OBJ ...";
		xLOG_CTRL->WRITE__LOG(log_msg);

		//
		pOBJ_CTRL__ESC->Abort__OBJECT();

		//
		err_msg += "ESC Object. \n";
	}
	*/

	// CHILLER OBJ ...
	/*
	if(pOBJ_CTRL__CHILLER->Is__OBJ_BUSY() > 0)
	{
		log_msg = "ABORT : CHILLER OBJ ...";
		xLOG_CTRL->WRITE__LOG(log_msg);

		//
		pOBJ_CTRL__CHILLER->Abort__OBJECT();

		//
		err_msg += "Chiller Object. \n";
	}
	*/

	/*			
	// LIFT_PIN OBJ ...
	if(pOBJ_CTRL__LIFT_PIN->Is__OBJ_BUSY() > 0)
	{
		log_msg = "ABORT : LIFT_PIN OBJ ...";
		xLOG_CTRL->WRITE__LOG(log_msg);

		//
		pOBJ_CTRL__LIFT_PIN->Abort__OBJECT();

		//
		err_msg += "Lift Pin Object. \n";
	}
	*/

	// MFC OBJ ...
	{
		CString err_bff;
		CString log_bff;

		// ...
		log_msg = "";

		for(i=0; i<iOBJ_MFC__SIZE; i++)
		{
			if(pOBJ_CTRL__MFC[i]->Is__OBJ_BUSY() > 0)
			{
				log_bff.Format("ABORT : MFC(%1d) Object ... \n", i+1);
				log_msg += log_bff;
			
				// ...
				pOBJ_CTRL__MFC[i]->Abort__OBJECT();

				//
				err_bff.Format("MFC%1d Object \n", i+1);
				err_msg += err_bff;
			}
		}

		if(log_msg.GetLength() > 0)
		{
			xLOG_CTRL->WRITE__LOG(log_msg);
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


//////////////////////////////////////////////////////////////////////////
// ABORT .....
int CObj__STEP_FNC::Call__ABORT(CII_OBJECT__VARIABLE* p_variable,
								CII_OBJECT__ALARM* p_alarm)
{
	sCH__OBJ_MSG->Set__DATA("Call__ABORT() : Start ...");

	Fnc__ABORT(p_variable,p_alarm);

	sCH__OBJ_MSG->Set__DATA("Call__ABORT() : End ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");

	return OBJ_AVAILABLE;
}

//////////////////////////////////////////////////////////////////////////
// Function ABORT .....
int CObj__STEP_FNC
::Fnc__ABORT(CII_OBJECT__VARIABLE* p_variable,
		     CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		// aEXT_CH__APC_PRESET_POS->Set__DATA("0");
		// aEXT_CH__APC_HOLD_DELAY_TIME->Set__DATA("0");

		Init__PRE_RCP_ITEM();
	}

	// ...
	{
		iHEADER_RCP_START    = -1;
		iTEMP_STEP_RCP_START = -1;
	}

	// ...
	{
		// dEXT_CH__ESC_MON_FLAG->Set__DATA("STOP");
		// dEXT_CH__UPC_MON_FLAG->Set__DATA("STOP");

		aCH__RCP_FDC_STEP_TIME->Set__DATA("0");
	}

	// ...
	{
		sCH__OBJ_MSG->Set__DATA("Fnc__ABORT() : Start ...");
		sCH__OBJ_SUB_MSG->Set__DATA("Fnc__ABORT() : Start ...");

		sCH__LEARNED_APPLY_STATUS->Set__DATA("Learned Mode Aborted ...");
	}

	// jglee ...
	{
		CString log_msg;
		CString log_id = "Fnc__ABORT()";

		// ...
		{
			log_msg.Format("%s : Start ...", log_id);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		// Lift_Pin <- Proc.Down ...
		{
			// ...
			{
				log_msg = "Lift_Pin <- Proc.Down ...";
				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			pOBJ_CTRL__LIFT_PIN->Run__OBJECT(CMMD__LIFT_PIN__PROC_DOWN);
		}

		// ALL RF <- OFF ...
		{
			// ...
			{
				log_msg = "All RF -> Off ...";
				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			// BIAS
			{
				aEXT_CH__RF_BIAS__PARA_SET_POWER->Set__VALUE(0.0);
				pOBJ_CTRL__RF_BIAS->Run__OBJECT("OFF");
			}
			// PLASMA
			{
				aEXT_CH__RF_PLASMA__PARA_SET_POWER->Set__VALUE(0.0);
				pOBJ_CTRL__RF_PLASMA->Run__OBJECT("OFF");
			}
		}

		// MFC & APC Control .....
		{
			// ...
			{
				log_msg.Format("%s : (APC -> Open) & (MFC -> Close) ...", log_id);
				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			// MFC start
			{
				sCH__OBJ_SUB_MSG->Set__DATA("All MFC Close ...");

				ALL_MFC_OBJ__Abort_Call_MODE(CMMD__MFC_CLOSE, log_id);
			}
			// APC Start 
			{
				sCH__OBJ_SUB_MSG->Set__DATA("APC Open ...");

				pOBJ_CTRL__VAC_VLV->Call__OBJECT("FR_OPEN");
			}
		}

		// He Close Start ...
		{
			log_msg.Format("%s : ESC He.Close Start ...", log_id);
			xLOG_CTRL->WRITE__LOG(log_msg);

			sCH__OBJ_SUB_MSG->Set__DATA("ESC He.Close Start ...");

			pOBJ_CTRL__ESC->Run__OBJECT("HE.CLOSE");
		}
	}

	// ...
	{
		sCH__OBJ_MSG->Set__DATA("Fnc__ABORT() : End ...");
		sCH__OBJ_SUB_MSG->Set__DATA("");
	}

	// ...
	{
		pOBJ_CTRL__VAC_VLV->When__OBJECT();

		pOBJ_CTRL__LIFT_PIN->When__OBJECT();
		pOBJ_CTRL__ESC->When__OBJECT();

		pOBJ_CTRL__RF_BIAS->When__OBJECT();
		pOBJ_CTRL__RF_PLASMA->When__OBJECT();
	}

	return OBJ_AVAILABLE;
}

int CObj__STEP_FNC::Call__END(CII_OBJECT__VARIABLE* p_variable,
							  CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		aCH__RCP_FDC_STEP_TIME->Set__DATA("0");
	}

	// ...
	{
		sCH__OBJ_MSG->Set__DATA("Call__END() : Start (ALL Object Wait) ...");

		// ...
		{
			CString obj_err_msg;

			sCH__STEP_TIME_ABORT_FLAG->Set__DATA("");

			ALL_OBJ__ABORT_WAIT(p_variable,p_alarm,obj_err_msg);
		}

		sCH__OBJ_MSG->Set__DATA("Call__END() : Start ...");
	}

	// ...
	CString log_msg;
	int nRet = -1;	
	int flag_wap = 1;
	
	int xfer_flag = -1;
	
	// All Part -> Start ...
	{
		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg.Format("Call__END() : All Part -> Started ...");
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		// APC OPEN : Start ...
		{
			APC_OBJ__Start_MODE(CMMD__APC_OPEN);
		}
				
		// MFC CLOSE : Start ...
		{
			ALL_MFC_OBJ__Start_MODE(CMMD__MFC_CLOSE);
		}

		// ESC Dechuck : Start ...
		if(dEXT_CH__CFG_DECHUCK_CTRL_MODE->Check__DATA("CONFIG") > 0)
		{
			pOBJ_CTRL__ESC->Call__OBJECT("DECHUCK.END");
		}
	}

	// Learned Data -> Save ...
	{
		if(dCH__CFG_LEARNED_APPLY_MODE->Check__DATA(STR__ENABLE) > 0)
		{
			CString var_data;

			sCH__CUR_LOTID->Get__DATA(var_data);
			sCH__PRE_LOTID->Set__DATA(var_data);

			if(sCH__LEARNED_RESULT->Check__DATA(STR__OK) > 0)
			{
				sCH__LEARNED_APPLY_STATUS->Set__DATA("Leaned Mode Applied ...");

				// ...
				int check_count = 0;
					
				while(sEXT_CH__RCP_FILE_UPLOAD_FLAG->Check__DATA(STR__YES) > 0)
				{
					Sleep(100);
				
					if(p_variable->Check__CTRL_ABORT() > 0)
					{
						return -1;
					}
				
					check_count++;
					if(check_count > 10)
					{
						int alarm_id = ALID__PROCESS_RECIPE_FILE_CHANGING_NOW;
						CString r_act;
					
						p_alarm->Check__ALARM(alarm_id,r_act);
						p_alarm->Post__ALARM(alarm_id);
					}
				}
			
				sEXT_CH__RCP_FILE_UPLOAD_FLAG->Set__DATA(STR__YES);

				// ...
				SCX__FILE_RCP_CTRL x_file_ctrl;
				int change_flag = -1;

				CString file_path;
				sCH__RCP_FILE_PATH->Get__DATA(file_path);

				// ...
				CUIntArray l__change_step;

				CDS__LEARNED_ITEM_INFO ds_info;
				int i = 0;

				while(mDB__LEARNED_ITEM_CTRL.Get__DB_ITEM(i,&ds_info) > 0)
				{
					i++;

					if(change_flag < 0)
					{
						change_flag = 1;

						x_file_ctrl->Partial__INIT_FILE(file_path);
					}
				
					// ...
					int step_id = ds_info.iSTEP_ID;
					l__change_step.Add(step_id);

					if(x_file_ctrl->Partial__STEP_JUMP(step_id) > 0)
					{
						CString ch_name;
						CString ch_type = "A";
						CString ch_data;

						// APC : VALVE POS
						{
							ch_name = aCH__RCP_APC_LEARNED_POS->Get__CHANNEL_NAME();
							ch_data = ds_info.sDATA__APC;
							x_file_ctrl->Partial__ADD_ITEM(ch_name,ch_type,ch_data);
						}

						// RFx : PLASMA
						{
							ch_name = aCH__RCP_RF_PLASMA_FREQ_LEARNED->Get__CHANNEL_NAME();
							ch_data = ds_info.sDATA__RF_PLASMA__FREQUENCY;
							x_file_ctrl->Partial__ADD_ITEM(ch_name,ch_type,ch_data);
						}
						// RFx : BIAS
						{
							ch_name = aCH__RCP_RF_BIAS_FREQ_LEARNED->Get__CHANNEL_NAME();
							ch_data = ds_info.sDATA__RF_BIAS__FREQUENCY;
							x_file_ctrl->Partial__ADD_ITEM(ch_name,ch_type,ch_data);
						}

						// MAT : PLASMA
						{
							ch_name = aCH__RCP_PLASMA_MATCHER_C1_LEARNED->Get__CHANNEL_NAME();
							ch_data = ds_info.sDATA__MAT_PLASMA__LOAD_POS;
							x_file_ctrl->Partial__ADD_ITEM(ch_name,ch_type,ch_data);

							ch_name = aCH__RCP_PLASMA_MATCHER_C2_LEARNED->Get__CHANNEL_NAME();
							ch_data = ds_info.sDATA__MAT_PLASMA__TUNE_POS;
							x_file_ctrl->Partial__ADD_ITEM(ch_name,ch_type,ch_data);
						}
						// MAT : BIAS
						{
							ch_name = aCH__RCP_BIAS_MATCHER_C1_LEARNED->Get__CHANNEL_NAME();
							ch_data = ds_info.sDATA__MAT_BIAS__LOAD_POS;
							x_file_ctrl->Partial__ADD_ITEM(ch_name,ch_type,ch_data);

							ch_name = aCH__RCP_BIAS_MATCHER_C2_LEARNED->Get__CHANNEL_NAME();
							ch_data = ds_info.sDATA__MAT_BIAS__TUNE_POS;
							x_file_ctrl->Partial__ADD_ITEM(ch_name,ch_type,ch_data);
						}
					}
				}

				if(change_flag > 0)
				{
					x_file_ctrl->Partial__SAVE_FILE(file_path);

					// ...
					CString log_msg;
					CString log_bff;

					int k_limit = l__change_step.GetSize();
					int k;

					log_msg  = "\n";
					log_msg += "Learned Value Applied ... \n"; 

					for(k=0;k<k_limit;k++)
					{
						log_bff.Format("   Step[%1d] \n", (int) l__change_step[k]);
						log_msg += log_bff;
					}

					xLOG_CTRL->WRITE__LOG(log_msg);
				}
			
				sEXT_CH__RCP_FILE_UPLOAD_FLAG->Set__DATA("");
			}
			else
			{
				sCH__LEARNED_APPLY_STATUS->Set__DATA("Learned Result is not OK ...");
			}
		}
		else
		{
			sCH__LEARNED_APPLY_STATUS->Set__DATA("");
		}

		mDB__LEARNED_ITEM_CTRL.Init__ALL_ITEM();
	}


	// All Part -> Complete ...
	{
		CString log_id = "Call__END()";
		CString str_data;

		// APC Start ...
		{
			sCH__OBJ_SUB_MSG->Set__DATA("APC Open ...");

			APC_OBJ__Wait_MODE(log_id);

			// ...
			{
				CString log_msg;
				
				log_msg.Format("Call__END() : APC <- Opened ...");
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
				
		// MFC Start 
		{
			sCH__OBJ_SUB_MSG->Set__DATA("All MFC Close ...");

			// ...
			{
				CString log_msg;
				
				log_msg.Format("Call__END() : All MFC <- Closed ...");
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
	}

	// ...
	{
		sCH__OBJ_MSG->Set__DATA("Call__END() : End ...");
		sCH__OBJ_SUB_MSG->Set__DATA("");
	}

	// ...
	{
		pOBJ_CTRL__VAC_VLV->When__OBJECT();

		pOBJ_CTRL__LIFT_PIN->When__OBJECT();
		pOBJ_CTRL__ESC->When__OBJECT();

		pOBJ_CTRL__RF_BIAS->When__OBJECT();
		pOBJ_CTRL__RF_PLASMA->When__OBJECT();
	}
	return 1;
}

int CObj__STEP_FNC::
Call__STEP_DB_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm)
{
	mDB__LEARNED_ITEM_CTRL.Init__ALL_ITEM();

	// ...
	CString str_log;
	CString str_bff;

	// ...
	{
		CDS__LEARNED_ITEM_INFO ds_info;

		int limit = 3;

		for(int i=0; i<limit; i++)
		{
			ds_info.iSTEP_ID = i+1;
			ds_info.sDATA__APC.Format("APC-%1d", i+1);

			mDB__LEARNED_ITEM_CTRL.Load__ITEM(ds_info);
		}
	}

	// ...
	{
		CDS__LEARNED_ITEM_INFO ds_info;

		int i = 0;

		while(mDB__LEARNED_ITEM_CTRL.Get__DB_ITEM(i,&ds_info) > 0)	
		{
			i++;

			str_bff.Format("iSTEP_ID : %1d \n", ds_info.iSTEP_ID);
			str_log += str_bff;

			str_bff.Format("   APC : %s \n", ds_info.sDATA__APC);
			str_log += str_bff;
		}
	}

	// ...
	{
		printf("\n");
		printf("%s - CObj__STEP_FNC::Call__STEP_DB_CHECK() \n", sObject_Name);
		printf("==================================================\n");
		printf("%s", str_log);
		printf("==================================================\n");
		printf("\n");
	}
	return 1;
}
