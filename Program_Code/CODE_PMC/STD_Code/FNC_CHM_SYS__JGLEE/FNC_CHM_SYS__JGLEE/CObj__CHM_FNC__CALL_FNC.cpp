#include "StdAfx.h"
#include "CObj__CHM_FNC.h"
#include "CObj__CHM_FNC__DEF.h"
#include "CObj__CHM_FNC__ALID.h"

#include "Macro_Function.h"


// ...
int CObj__CHM_FNC
::Call__INIT(CII_OBJECT__VARIABLE *p_variable,
			 CII_OBJECT__ALARM *p_alarm)
{
	if(dEXT_CH__CFG_PMC_ATM_MAINT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 1;
	}

	if(Fnc__INIT(p_variable,p_alarm) < 0)
	{
		sCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
		return -1;
	}

	sCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	return 1;
}
int CObj__CHM_FNC
::Call__MAINTMODE(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	sCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
	return OBJ_AVAILABLE;
}


// ...
int CObj__CHM_FNC
::Call__LOW_VAC_PUMP(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int flag = Fnc__LOW_VAC_PUMP(p_variable,p_alarm, -1, -1);

	if(flag < 0)
	{
		CString log_msg;

		log_msg.Format("Fnc__LOW_VAC_PUMP() : Failed [%d] ...", flag);	
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		if(bActive__GAS_CLOSE_SKIP)
		{

		}
		else
		{
			if(dCH__CFG_PROCESS_READY_CTRL_AFTER_CHM_PUMPING->Check__DATA(STR__YES) > 0)
			{
				pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__PROC_READY);
			}
		}
	}

	return flag;
}

int CObj__CHM_FNC
::Call__HIGH_VAC_PUMP(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;

	// ...
	bool active__high_vac_skip = false;
	
	if(dCH__CFG_USE_HIGH_VAC_PUMPING->Check__DATA(STR__NO) > 0)
	{
		active__high_vac_skip = true;
	}

	// ...
	bool active__low_vac = true;

	if(active__high_vac_skip)
	{
		active__low_vac = true;
	}
	else
	{
		if(bActive__OBJ_CTRL__TURBO_PUMP)
		{
			if(Check__LOW_VAC_PUMP() > 0)		active__low_vac = false;
		}
	}

	// LOW_VAC.PUMPING ...
	if(active__low_vac)
	{
		int flag = Fnc__LOW_VAC_PUMP(p_variable,p_alarm, 1, -1);

		if(flag < 0)
		{
			log_msg.Format("Fnc__LOW_VAC_PUMP() : Failed [%d] ...", flag);	
			xLOG_CTRL->WRITE__LOG(log_msg);
			return flag;
		}

		if(active__high_vac_skip)
		{
			if(!bActive__GAS_CLOSE_SKIP)
			{
				if(dCH__CFG_PROCESS_READY_CTRL_AFTER_CHM_PUMPING->Check__DATA(STR__YES) > 0)
				{
					pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__PROC_READY);
				}
			}
			return 1;
		}
	}
	else
	{
		// Gas-Valve <- Close
		if(bActive__GAS_CLOSE_SKIP)
		{

		}
		else
		{
			if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__ALL_CLOSE) < 0)		return -101;
		}

		// ESC Pump_Ready ...
		if(bActive__ESC_OBJ)
		{
			if(pOBJ_CTRL__ESC->Call__OBJECT(_ESC_CMMD__PUMP_READY) < 0)			return -102;
		}
	}

	// HIGH_VAC.PUMPING ...
	if(bActive__OBJ_CTRL__TURBO_PUMP)
	{
		int flag = Fnc__HIGH_VAC_PUMP(p_variable,p_alarm);

		// Gas-Valve <- Proc_Ready
		if(bActive__GAS_CLOSE_SKIP)
		{

		}
		else
		{
			if(dCH__CFG_PROCESS_READY_CTRL_AFTER_CHM_PUMPING->Check__DATA(STR__YES) > 0)
			{
				pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__PROC_READY);
			}
		}

		if(flag < 0)
		{
			log_msg.Format("Fnc__HIGH_VAC_PUMP() : Failed [%d] ...", flag);	
			xLOG_CTRL->WRITE__LOG(log_msg);
			return flag;
		}
	}

	return 1;
}

int CObj__CHM_FNC
::Call__PROC_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{

	return pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__PROC_READY);
}

// ...
int CObj__CHM_FNC
::Call__CLOSE_VAC_LINE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	sCH__OBJ_MSG->Set__DATA("VAC_Line All Close ...");

	Call__VAC_VLV__ALL_CLOSE(p_variable, p_alarm);

	sCH__OBJ_MSG->Set__DATA("");
	return 1;
}

int CObj__CHM_FNC
::Call__VENT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	CString log_bff;

	CString ch_data;
	int flag = -1;

	/*
	// ...
	{
		CString var_data;

		aEXT_CH__TOP_PLATE_CURRENT_TEMP->Get__DATA(var_data);
		double cur_temp = atof(var_data);

		if(cur_temp >= 50)
		{
			int alarm_id = ALID__PLATE_TEMP_INTERLOCK_FOR_VENTING;
			CString r_act;

			p_alarm->Popup__ALARM(alarm_id,r_act);
			return -1;
		}
	}
	*/

	// 1. ESC Vent_Ready ...
	if(bActive__ESC_OBJ)
	{
		// ...
		{
			log_msg = "ESC <- Vent_Ready";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(pOBJ_CTRL__ESC->Call__OBJECT(_ESC_CMMD__VENT_READY) < 0)
		{
			return -11;
		}
	}

	// 2. Config Turbo Mode 
	if(bActive__OBJ_CTRL__TURBO_PUMP)
	{
		if(dCH__CFG_BEFORE_VENT_TURBO_PUMP_OFF->Check__DATA(STR__TRUE) > 0)
		{
			// ...
			{
				log_msg = "\n";
			
				log_bff.Format(" * %s <- %s \n", 
								dCH__CFG_BEFORE_VENT_TURBO_PUMP_OFF->Get__CHANNEL_NAME(),
								dCH__CFG_BEFORE_VENT_TURBO_PUMP_OFF->Get__STRING());
				log_msg += log_bff;

				log_msg += " * Turbo Pump Off ... \n";
	
				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			if(pOBJ_CTRL__TURBO_PUMP->Run__OBJECT("OFF_NO_WAIT") < 0)
			{
				return -21;
			}
		}
	}

	// 3. Vent Sequence ...
	{
		flag = Fnc__VENT(p_variable, p_alarm, -1);

		Fnc__ALL_GAS_LINE_CLOSE(p_variable, p_alarm);

		if(flag < 0)
		{
			log_msg.Format("Call__VENT : Fnc__VENT is Failed [%d] ...", flag);	

			xLOG_CTRL->WRITE__LOG(log_msg);
			return -31;
		}
	}

	return 1;
}

// ...
int CObj__CHM_FNC
::Call__LEAK_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const bool active__gas_leak)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		CString sub_dir;

		CString str_date;
		CString str_time;

		Macro__Get_Date(str_date, str_time);

		sub_dir.Format("%s\\%s\\", str_date,"LEAK_CHECK");
		xEXT_CH__PMC_LOG__SUB_DIR->Set__DATA(sub_dir);

		//
		xEXT_CH__PMC_LOG__FILE_NAME->Set__DATA("");

		sCH__LEAK_CHECK__LOG_START_PRESSURE_mTORR->Set__DATA("");
		sCH__LEAK_CHECK__LOG_START_PRESSURE_mTORR->Set__DATA("");	

		sCH__LEAK_CHECK__LOG_RATE_mTORR_Per_MIN->Set__DATA("");
		sCH__LEAK_CHECK__LOG_RESULT_mTORR_Per_MIN->Set__DATA("");
	}

	// ...
	bool active__ctc_call = false;

	if((dEXT_CH__ACTIVE_CALL_BY_CTC->Check__DATA(STR__ON) > 0)
	&& (dEXT_CH__CTC_LEAK_CHECK_USE_FLAG->Check__DATA(STR__ENABLE) > 0))
	{
		active__ctc_call = true;

		sCH__LEAK_CHECK__ACTIVE_CALL_BY_CTC->Set__DATA("Controlled by CTC");
	}
	else
	{
		sCH__LEAK_CHECK__ACTIVE_CALL_BY_CTC->Set__DATA("Controlled by PMC");
	}

	// ...
	int flag = -1;

	if(active__gas_leak)
	{
		for(int k=0; k<iDATA__MFC_SIZE; k++)
		{
			dEXT_CH__REPORT_LEAK_CHECK_STATE_X[k]->Set__DATA(STR__UNKNOWN);
		}

		for(int k=0; k<iDATA__MFC_SIZE; k++)
		{
			if(dEXT_CH__CFG_MFC_USE_X[k]->Check__DATA(STR__YES) < 0)			continue;
			if(dEXT_CH__CFG_LEAK_CHECK_USE_X[k]->Check__DATA(STR__YES) < 0)		continue;
			
			dEXT_CH__REPORT_LEAK_CHECK_STATE_X[k]->Set__DATA(STR__CHECK);

			CString gas_name = sEXT_CH__CFG_GAS_NAME_X[k]->Get__STRING();

			flag = Fnc__LEAK_CHECK(p_variable,p_alarm, active__ctc_call, true, k);

			if(flag < 0)
			{
				dEXT_CH__REPORT_LEAK_CHECK_STATE_X[k]->Set__DATA(STR__NG);

				log_msg.Format("Call__LEAK_CHECK : Fnc__LEAK_CHECK is Failed [%d] ...", flag);	
				xLOG_CTRL->WRITE__LOG(log_msg);
				break;
			}
			else
			{
				dEXT_CH__REPORT_LEAK_CHECK_STATE_X[k]->Set__DATA(STR__OK);
			}
		}
	}
	else
	{
		flag = Fnc__LEAK_CHECK(p_variable,p_alarm, active__ctc_call, false);

		if(flag < 0)
		{
			log_msg.Format("Call__LEAK_CHECK : Fnc__LEAK_CHECK is Failed [%d] ...", flag);	
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(flag > 0)
		{
			if(dCH__LEAK_CHECK__CFG_VAT_VLV_POS_MOVING->Check__DATA(STR__ENABLE) > 0)
			{
				dCH__LEAK_CHECK__ACTIVE_VAT_VLV_POS_MOVING->Set__DATA(STR__ON);

				flag = Fnc__LEAK_CHECK__VAT_VLV_POS_MOVE(p_variable,p_alarm, active__ctc_call);

				dCH__LEAK_CHECK__ACTIVE_VAT_VLV_POS_MOVING->Set__DATA(STR__OFF);

				if(flag < 0)
				{
					log_msg.Format("Call__LEAK_CHECK : Fnc__LEAK_CHECK__VAT_VLV_POS_MOVE() <- Failed [%1d] ...", flag);
					xLOG_CTRL->WRITE__LOG(log_msg);
				}
			}
		}
	}

	if(flag < 0)
	{
		// ...
		{
			log_msg.Format("Leak_Check_Aborted_:_Error(%1d)", flag);
			sCH__LEAK_CHECK__LOG_MESSAGE->Set__DATA(log_msg);
		}

		if(bActive__PMC_LOG)
		{
			int log_flag = pOBJ_CTRL__PMC_LOG->Call__OBJECT(CMMD__LOG_DISABLE);

			// ...
			{
				log_msg = "\n";

				log_bff  = "** Logging End ... \n";
				log_msg += log_bff;

				log_bff.Format("   1. Log Flag : [%1d] \n", log_flag);
				log_msg += log_bff;

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}

		// ...
		{
			xEXT_CH__PMC_LOG__SUB_DIR->Set__DATA("");
			xEXT_CH__PMC_LOG__FILE_NAME->Set__DATA("");
		}
	}

	// ...
	{
		if(p_variable->Check__CTRL_ABORT() > 0)			dCH__OBJ_CTRL->Set__DATA("ABORTED");

		if(bActive__OBJ_CTRL__TURBO_PUMP)		Call__HIGH_VAC_PUMP(p_variable,p_alarm);
		else									Call__LOW_VAC_PUMP(p_variable,p_alarm);
	}

	return flag;
}

int CObj__CHM_FNC
::Call__PURGE(CII_OBJECT__VARIABLE *p_variable,
			  CII_OBJECT__ALARM *p_alarm)
{
	int flag = Fnc__PURGE(p_variable,p_alarm);

	if(flag < 0)
	{
		CString log_msg;

		log_msg.Format("Call__PURGE : Fnc__PURGE is Failed [%d] ...", flag);	
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	return flag;
}

/*
int CObj__CHM_FNC
::Call__PURGE_PUMP(CII_OBJECT__VARIABLE *p_variable,
				   CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;

	// Cycle Pumping (Pump -> Purge -> Pump)

	int flag = Fnc__LOW_VAC_PUMP(p_variable,p_alarm, 1, 1);
	if(flag < 0)
	{
		log_msg.Format("Call__PURGE_PUMP : Fnc__HIGH_VAC_PUMP is Failed [%d] ...", flag);	

		xLOG_CTRL->WRITE__LOG(log_msg);
		return flag;
	}

	flag = Fnc__PURGE_PUMP(p_variable,p_alarm);
	if(flag < 0)
	{
		log_msg.Format("Call__PURGE_PUMP : Fnc__PURGE is Failed [%d] ...", flag);	

		xLOG_CTRL->WRITE__LOG(log_msg);
		return flag;
	}

	flag = Fnc__LOW_VAC_PUMP(p_variable,p_alarm, 1, 1);
	if(flag < 0)
	{
		log_msg.Format("Call__PURGE_PUMP : Fnc__LOW_VAC_PUMP is Failed [%d] ...", flag);	

		xLOG_CTRL->WRITE__LOG(log_msg);
		return flag;
	}

	return flag;
}
int CObj__CHM_FNC
::Call__PURGE_VENT(CII_OBJECT__VARIABLE *p_variable,
				   CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;

	// Cycle Pumping (Pump -> Purge -> Pump)

	int flag = Fnc__LOW_VAC_PUMP(p_variable,p_alarm, 1, 1);
	if(flag < 0)
	{
		log_msg.Format("Call__PURGE_VENT : Fnc__HIGH_VAC_PUMP is Failed [%d] ...", flag);	

		xLOG_CTRL->WRITE__LOG(log_msg);
		return flag;
	}

	flag = Fnc__PURGE_VENT(p_variable,p_alarm);
	if(flag < 0)
	{
		log_msg.Format("Call__PURGE_VENT : Fnc__PURGE is Failed [%d] ...", flag);	

		xLOG_CTRL->WRITE__LOG(log_msg);
		return flag;
	}

	flag = Fnc__LOW_VAC_PUMP(p_variable,p_alarm, 1, 1);
	if(flag < 0)
	{
		log_msg.Format("Call__PURGE_VENT : Fnc__HIGH_VAC_PUMP is Failed [%d] ...", flag);	

		xLOG_CTRL->WRITE__LOG(log_msg);
		return flag;
	}

	return flag;
}
*/

//
int CObj__CHM_FNC
::Call__CHM_BALLAST_START(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int flag = Fnc__CHM_BALLAST_START(p_variable, p_alarm);

	if(flag < 0)
	{
		CString log_msg;

		log_msg.Format("Call__CHM_BALLAST_START : Fnc__CHM_BALLAST_START is Failed [%d] ...", flag);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	return flag;
}
int CObj__CHM_FNC
::Call__TRANS_BALLAST_START(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int flag = Fnc__TRANS_BALLAST_START(p_variable, p_alarm);

	if(flag < 0)
	{
		CString log_msg;

		log_msg.Format("Call__TRANS_BALLAST_START : Fnc__TRANS_BALLAST_START is Failed [%d] ...", flag);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	return flag;
}

int CObj__CHM_FNC
::Call__BALLAST_END(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;

	int flag = Fnc__BALLAST_END(p_variable, p_alarm);
	if(flag < 0)
	{
		log_msg.Format("Call__BALLAST_END : Fnc__BALLAST_END is Failed [%d] ...", flag);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__CHM_FNC
::Call__APC_AUTO_LEARN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;

	SCX__TIMER_CTRL xtimer_ctrl;
	xtimer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);


	// 1. Base Pumping ...
	{
		// ...
		{
			log_msg = "Low Pumping Start..";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(Call__LOW_VAC_PUMP(p_variable, p_alarm) < 0)
		{
			return -11;
		}
	}

	// 2. Chamber Ballast Flow ...
	{
		// ...
		{
			log_msg = "Chamber Ballast Flow Start..";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD__CHM_BALLAST_FLOW) < 0)
		{
			log_msg.Format("Fnc__CHM_BALLAST_START : MFC Ballast Flow is Failed...");
			xLOG_CTRL->WRITE__LOG(log_msg);

			return -21;
		}
	}

	// 3. Delay Time ...
	{
		// ...
		{
			log_msg = "Time Delay ...";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		double cfg__delay_sec = aCH__CFG_BEFORE_AUTO_LEARNING_DELAY_TIME->Get__VALUE();
		
		if(xtimer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			return -31;
		}
	}

	/*
	// 4. AUTO Learning ¸í·É ...
	{
		// ...
		{
			log_msg = "Auto Learn Command Call ...";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		// ...
		int flag = pOBJ_CTRL__APC_VLV->Call__OBJECT(CMMD__APC_AUTO_LEARN);
		if(flag < 0)
		{
			// ...
			{
				log_msg.Format("Call__APC_AUTO_LEARN : Failed [%d] ...", flag);
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			return OBJ_ABORT;
		}
	}
	*/

	// 5. Ballast Close ...
	{
		// ...
		{
			log_msg = "Chamber Ballast Flow End..";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD__BALLAST_CLOSE) < 0)
		{
			log_msg.Format("Fnc__CHM_BALLAST_END : MFC Ballast End is Failed ...");
			xLOG_CTRL->WRITE__LOG(log_msg);

			return -51;
		}
	}

	// ...
	{
		log_msg = "APC Auto Learn Fnc Complete ...";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
}
