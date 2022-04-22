#include "StdAfx.h"
#include "CObj__LBx_ManiFold_X.h"
#include "CObj__LBx_ManiFold_X__DEF.h"

#include "Macro_Function.h"


//----------------------------------------------------------------------------------------------------
int  CObj__LBx_ManiFold_X
::Call__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__INIT);
}

int  CObj__LBx_ManiFold_X
::Call__PUMP(CII_OBJECT__ALARM* p_alarm,CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__PUMP(p_alarm, p_variable, -1);
}
int  CObj__LBx_ManiFold_X
::Call__TRANSFER_PUMP(CII_OBJECT__ALARM* p_alarm,CII_OBJECT__VARIABLE* p_variable)
{
	for(int i=0; i<iLBx_SLOT_SIZE; i++)
	{
		sEXT_CH__SLIT_VALVE_LOCK_FLAG_X[i]->Link__UPPER_OBJECT_ABORT(sObject_Name);
		sEXT_CH__SLIT_VALVE_LOCK_FLAG_X[i]->Enable__UPPER_OBJECT_ABORT_CHECK();

		int flag = sEXT_CH__SLIT_VALVE_LOCK_FLAG_X[i]->When__NOT_DATA(STR__YES);
		if(flag <= 0)		return OBJ_ABORT;
	}

	if(Is__ALL_SV_OPEN())
	{
		CString log_msg;

		log_msg = "Call__TRANSFER_PUMP() : VAC-Valve Open !";
		xLOG_CTRL->WRITE__LOG(log_msg);
		return 1;
	}

	return Fnc__PUMP(p_alarm, p_variable, 1);
}

int  CObj__LBx_ManiFold_X
::Fnc__PUMP(CII_OBJECT__ALARM* p_alarm,CII_OBJECT__VARIABLE* p_variable,const int transfer_flag)
{
	CString log_msg;

	log_msg.Format("Fnc__PUMP() - Check(1) \n");
	xLOG_CTRL->WRITE__LOG(log_msg);

Mode_Chk_Rty:

	// ...
	CString str_lbx_mode;
	CString str_tmx_mode;
	CString str_obj_sts;
	int i;

	//
	for(i=0; i<iOTHER_CHM__SIZE; i++)
	{
		dEXT_CH__OTHER_CHM__PUMPING_STS_FLAG_X[i]->Link__UPPER_OBJECT_ABORT(sObject_Name);
		dEXT_CH__OTHER_CHM__PUMPING_STS_FLAG_X[i]->Enable__UPPER_OBJECT_ABORT_CHECK();
	}

	log_msg.Format("Fnc__PUMP() - Check(2) \n");
	xLOG_CTRL->WRITE__LOG(log_msg);

	for(i=0; i<iOTHER_CHM__SIZE; i++)
	{
		int r_flag = dEXT_CH__OTHER_CHM__PUMPING_STS_FLAG_X[i]->When__DATA("END");
		if(r_flag <= 0)		return OBJ_ABORT;
	}

	log_msg.Format("Fnc__PUMP() - Check(3) \n");
	xLOG_CTRL->WRITE__LOG(log_msg);

	dCH__PUMPING_STS_FLAG->Set__DATA("PUMPING");

	for(i=0; i<iOTHER_CHM__SIZE; i++)
	{
		if(dEXT_CH__OTHER_CHM__PUMPING_STS_FLAG_X[i]->Check__DATA("PUMPING") < 0)
			continue;

		dCH__PUMPING_STS_FLAG->Set__DATA("END");

		Sleep(100);
		goto Mode_Chk_Rty;
	}

	log_msg.Format("Fnc__PUMP() - Check(4) \n");
	xLOG_CTRL->WRITE__LOG(log_msg);

	// Other : CL.PUMP_VLV
	for(i=0; i<iOTHER_CHM__SIZE; i++)
	{
		if(pOther_CHM__OBJ_PHY_X[i]->Is__OBJ_BUSY() > 0)		continue;

		pOther_CHM__OBJ_PHY_X[i]->Call__OBJECT("CL.PUMP_VLV");
	}

	// CHM -----
	{
		if(pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__PUMP) < 0)
		{
			return -101;
		}

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -102;
		}
	}

	log_msg.Format("Fnc__PUMP() - Check(5) \n");
	xLOG_CTRL->WRITE__LOG(log_msg);

	// PUMP VLV OPEN -----
	// Other CHM ...
	for(i=0; i<iOTHER_CHM__SIZE; i++)
	{
		if(pOther_CHM__OBJ_PHY_X[i]->Is__OBJ_BUSY() > 0)		continue;

		if(sEXT_CH__Other_CHM__PRESSURE_CTRL_FLAG_X[i]->Check__DATA("PUMP") < 0)
			continue;

		if(dEXT_CH__Other_CHM__PRESSURE_STATUS_X[i]->Check__DATA(STR__VAC) < 0)
			continue;

		pOther_CHM__OBJ_PHY_X[i]->Call__OBJECT("OP.PUMP_VLV");
	}
	
	log_msg.Format("Fnc__PUMP() - Check(6) \n");
	xLOG_CTRL->WRITE__LOG(log_msg);

	return 1;
}

int  CObj__LBx_ManiFold_X::Call__VENT(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__VENT);
}

int  CObj__LBx_ManiFold_X::Call__LEAK_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		sCH__MON_LEAK_CHECK__START_TIME->Set__DATA("");
		sCH__MON_LEAK_CHECK__END_TIME->Set__DATA("");
		sCH__MON_LEAK_CHECK__START_PRESSURE_TORR->Set__DATA("");
		sCH__MON_LEAK_CHECK__END_PRESSURE_TORR->Set__DATA("");
		sCH__MON_LEAK_CHECK__TOTAL_LEAK_RATE->Set__DATA("");

		for(int i=0; i<CFG_LEAK_RATE__STEP_SIZE; i++)
		{
			sCH__MON_LEAK_CHECK__STEP_PRESSURE_TORR[i]->Set__DATA("");
			sCH__MON_LEAK_CHECK__STEP_LEAK_RATE[i]->Set__DATA("");
		}
	}

	sCH__OBJ_MSG->Set__DATA("Pumping ...");

	// ...
	int r_flag;

	r_flag = Call__PUMP(p_alarm, p_variable);
	if(r_flag < 0)			return -11;

	r_flag = Fnc__LEAK_CHECK(p_variable, p_alarm);
	if(r_flag < 0)			return -12;

	r_flag = Call__PUMP(p_alarm, p_variable);
	if(r_flag < 0)			return -13;

	return 1;
}
int  CObj__LBx_ManiFold_X::Fnc__LEAK_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;

	SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
	double  delay_time;
	CString var_data;

	x_timer_ctrl->REGISTER__COUNT_CHANNEL(sObject_Name, aCH__MON_LEAK_CHECK__TIME_COUNT->Get__VARIABLE_NAME());

	// ...
	CString str__unit = "mTorr";
	CString str__over_pump_time;
	CString str__stable_time;
	CString str__check_time;

	// Over-Pumping -----
	{
		log_msg = "Leak_Check : Over-Pumping ...";

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		aCH__CFG_LEAK_CHECK__OVER_PUMPING_TIME->Get__DATA(var_data);
		str__over_pump_time = var_data;
		delay_time = atof(var_data);

		x_timer_ctrl->START__COUNT_DOWN(delay_time);

		while(1)
		{
			Sleep(3);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -1;
			}
			if(x_timer_ctrl->Get__CURRENT_TIME() < 0.1)
			{
				break;
			}
		}

		pLBx_CHM__OBJ_CTRL->Call__OBJECT("CL.PUMP_VLV");
	}

	// Stable Time -----
	{
		log_msg = "Leak_Check : Stable Time ...";

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		aCH__CFG_LEAK_CHECK__STABLE_TIME->Get__DATA(var_data);
		str__stable_time = var_data;
		delay_time = atof(var_data);

		x_timer_ctrl->START__COUNT_DOWN(delay_time);

		while(1)
		{
			Sleep(3);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -1;
			}
			if(x_timer_ctrl->Get__CURRENT_TIME() < 0.1)
			{
				break;
			}
		}
	}

	// Leak Check -----
	{
		log_msg = "Leak_Checking ...";

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		CString date_time;
		Macro__Get_Date_Time(date_time);

		sCH__MON_LEAK_CHECK__START_TIME->Set__DATA(date_time);

		aEXT_CH__PRESSURE_TORR->Get__DATA(var_data);
		sCH__MON_LEAK_CHECK__START_PRESSURE_TORR->Set__DATA(var_data);

		// LeakCheck Log ...
		{
			sCH__MON_LEAK_CHECK__START_PRESSURE_TORR->Get__DATA(var_data);
			double start_press = atof(var_data);

			CString log_msg;
			log_msg.Format("0,Start Pressure,%.3f,%s", start_press,str__unit);

			LeakCheck__LOG_MakeFile(sLLx_NAME);
			LeakCheck__LOG_WriteMsg(sLLx_NAME, log_msg);
		}

		// ...
		aCH__CFG_LEAK_CHECK__CHECK_TIME_MIN->Get__DATA(var_data);
		str__check_time = var_data;
		int check_min = atoi(var_data);

		for(int i=0;i<check_min;i++)
		{
			delay_time = 60.0;
			x_timer_ctrl->START__COUNT_DOWN(delay_time);

			while(1)
			{
				Sleep(3);

				if(p_variable->Check__CTRL_ABORT() > 0)
				{
					return -1;
				}
				if(x_timer_ctrl->Get__CURRENT_TIME() < 0.1)
				{
					break;
				}
			}

			if(i < CFG_LEAK_RATE__STEP_SIZE)
			{
				double pre_press;
				double cur_press;

				if(i < 1)
				{
					sCH__MON_LEAK_CHECK__START_PRESSURE_TORR->Get__DATA(var_data);
					pre_press = atof(var_data);
				}
				else
				{
					sCH__MON_LEAK_CHECK__STEP_PRESSURE_TORR[i-1]->Get__DATA(var_data);
					pre_press = atof(var_data);
				}

				aEXT_CH__PRESSURE_TORR->Get__DATA(var_data);
				sCH__MON_LEAK_CHECK__STEP_PRESSURE_TORR[i]->Set__DATA(var_data);
				cur_press = atof(var_data);

				var_data.Format("%.3f", (cur_press-pre_press)/(i+1.0));
				sCH__MON_LEAK_CHECK__STEP_LEAK_RATE[i]->Set__DATA(var_data);

				// LeakCheck Log ...
				{
					CString str_rate;
					CString str_press;

					sCH__MON_LEAK_CHECK__STEP_LEAK_RATE[i]->Get__DATA(str_rate);
					sCH__MON_LEAK_CHECK__STEP_PRESSURE_TORR[i]->Get__DATA(str_press);

					//
					CString log_msg;
					log_msg.Format("%d,%d min,%.3f,%.3f", 
									i+1, 
									i+1,
									atof(str_press), 
									atof(str_rate));

					LeakCheck__LOG_WriteMsg(sLLx_NAME, log_msg);
				}
			}
		}

		// ...
		{
			aEXT_CH__PRESSURE_TORR->Get__DATA(var_data);
			sCH__MON_LEAK_CHECK__END_PRESSURE_TORR->Set__DATA(var_data);

			sCH__MON_LEAK_CHECK__START_PRESSURE_TORR->Get__DATA(var_data);
			double pre_press = atof(var_data);

			aEXT_CH__PRESSURE_TORR->Get__DATA(var_data);
			double cur_press = atof(var_data);

			if(check_min < 1)		check_min = 1;
			var_data.Format("%.3f", (cur_press-pre_press)/check_min);
			sCH__MON_LEAK_CHECK__TOTAL_LEAK_RATE->Set__DATA(var_data);
		}

		Macro__Get_Date_Time(date_time);
		sCH__MON_LEAK_CHECK__END_TIME->Set__DATA(date_time);
	}

	// LeackCheck Log ...
	{
		CString log_msg;
		CString log_bff;

		log_msg += "#COMMENT";
		log_msg += "\n";

		log_msg += "*** LLx LEAK CHECK INFORMATION ***";
		log_msg += "\n";

		log_bff.Format("(1) Over Pumping Time: %.1f sec                (2) Stable Time: %.1f sec             (3) Leak Check Time: %.0f min", 
						atof(str__over_pump_time),
						atof(str__stable_time),
						atof(str__check_time));
		log_msg += log_bff;
		log_msg += "\n";

		CString str__start_time;
		CString str__end_time;

		sCH__MON_LEAK_CHECK__START_TIME->Get__DATA(str__start_time);
		sCH__MON_LEAK_CHECK__END_TIME->Get__DATA(str__end_time);

		log_bff.Format("(4) Leak Check Start Time: %s        (5) Leak Check End Time: %s", 
						str__start_time,
						str__end_time);
		log_msg += log_bff;
		log_msg += "\n";

		sCH__MON_LEAK_CHECK__START_PRESSURE_TORR->Get__DATA(var_data);

		log_bff.Format("(6) Start Pressure: %.3f %s", 
						atof(var_data),
						str__unit);
		log_msg += log_bff;
		log_msg += "\n";

		sCH__MON_LEAK_CHECK__TOTAL_LEAK_RATE->Get__DATA(var_data);

		log_bff.Format("(7) Leak Rate: %.3f %s", 
						atof(var_data),
						str__unit);
		log_msg += log_bff;
		log_msg += "\n";

		//
		LeakCheck__LOG_WriteMsg(sLLx_NAME, log_msg);
	}

	// ...
	{
		sCH__MON_LEAK_CHECK__TOTAL_LEAK_RATE->Get__DATA(var_data);
		double total_leak_rate = atof(var_data) * 1000.0;

		aCH__CFG_LEAK_CHECK__ALARM_RATE->Get__DATA(var_data);
		double cfg_leak_alarm = atof(var_data);

		if(total_leak_rate >= cfg_leak_alarm)
		{
			int alarm_id = ALID__LEAK_CHECK_BAD_RESULT_ALARM;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			alm_msg.Format(" * Total Leak_Rate  : %.0f (mtorr/min) \n", total_leak_rate);
			alm_bff.Format(" * Config Leak_Rate : %.0f (mtorr/min) \n", cfg_leak_alarm);
			alm_msg += alm_bff;

			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, alm_msg, r_act);
		}
	}
	return 1;
}

int  CObj__LBx_ManiFold_X::Call__PREPMATER(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__PREPMATER);
}
int  CObj__LBx_ManiFold_X::Call__COMPMATER(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__COMPMATER);
}

int  CObj__LBx_ManiFold_X::Call__IN_PROC(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__IN_PROC);
}

int  CObj__LBx_ManiFold_X::Call__OUT_PROC(CII_OBJECT__VARIABLE* p_variable)
{
	if((dEXT_CH__CFG_HEATER_USE->Check__DATA(STR__YES) > 0)
		&& (dEXT_CH__CFG_HEATER_SOFT_VENT_USE->Check__DATA(STR__YES) > 0))
	{
		return Fnc__OUT_PROC_With_ManiFoldType(p_variable);
	}

	return Fnc__OUT_PROC_With_SingleType(p_variable);
}
int  CObj__LBx_ManiFold_X::Fnc__OUT_PROC_With_SingleType(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__OUT_PROC);
}
int  CObj__LBx_ManiFold_X::Fnc__OUT_PROC_With_ManiFoldType(CII_OBJECT__VARIABLE* p_variable)
{
Mode_Chk_Rty:

	// ...
	CString str_lbx_mode;
	CString str_tmx_mode;
	CString str_obj_sts;
	int i;

	for(i=0; i<iOTHER_CHM__SIZE; i++)
	{
		dEXT_CH__OTHER_CHM__PUMPING_STS_FLAG_X[i]->Link__UPPER_OBJECT_ABORT(sObject_Name);
		dEXT_CH__OTHER_CHM__PUMPING_STS_FLAG_X[i]->Enable__UPPER_OBJECT_ABORT_CHECK();
	}

	for(i=0; i<iOTHER_CHM__SIZE; i++)
	{
		int r_flag = dEXT_CH__OTHER_CHM__PUMPING_STS_FLAG_X[i]->When__DATA("END");
		if(r_flag <= 0)		return OBJ_ABORT;
	}

	dCH__PUMPING_STS_FLAG->Set__DATA("PUMPING");

	for(i=0; i<iOTHER_CHM__SIZE; i++)
	{
		if(dEXT_CH__OTHER_CHM__PUMPING_STS_FLAG_X[i]->Check__DATA("PUMPING") < 0)
			continue;

		dCH__PUMPING_STS_FLAG->Set__DATA("END");

		Sleep(100);
		goto Mode_Chk_Rty;
	}

	// Other : CL.PUMP_VLV
	for(i=0; i<iOTHER_CHM__SIZE; i++)
	{
		if(pOther_CHM__OBJ_PHY_X[i]->Is__OBJ_BUSY() > 0)		continue;

		pOther_CHM__OBJ_PHY_X[i]->Call__OBJECT("CL.PUMP_VLV");
	}

	// CHM ...
	{
		if(pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__OUT_PROC) < 0)
		{
			return -101;
		}
		if(pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__PUMP) < 0)
		{
			return -102;
		}
	}

	// PUMP VLV OPEN -----
	// Other CHM ...
	for(i=0; i<iOTHER_CHM__SIZE; i++)
	{
		if(pOther_CHM__OBJ_PHY_X[i]->Is__OBJ_BUSY() > 0)		continue;

		if(sEXT_CH__Other_CHM__PRESSURE_CTRL_FLAG_X[i]->Check__DATA("PUMP") < 0)
			continue;

		if(dEXT_CH__Other_CHM__PRESSURE_STATUS_X[i]->Check__DATA(STR__VAC) < 0)
			continue;

		pOther_CHM__OBJ_PHY_X[i]->Call__OBJECT("OP.PUMP_VLV");
	}

	return 1;
}

int  CObj__LBx_ManiFold_X::
Call__DV_OPEN(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM *p_alarm)
{
LOOP_RETRY:

	if((dEXT_CH__CFG_SETUP_TEST_MODE->Check__DATA(STR__ENABLE) > 0)
	&& (dEXT_CH__CFG_SETUP_LLx_DOOR_SLOT_VLV_CONTROL->Check__DATA(STR__DISABLE) > 0))
	{
		if(Is__ALL_DV_OPEN())
		{
			return 1;
		}
	}

	// ...
	bool active__vlv_open = true;
	int loop_count = 0;

	while(active__vlv_open)
	{
		if(Is__ALL_SV_CLOSE())
		{
			active__vlv_open = false;
			break;
		}

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1;
		}

		loop_count++;
		if(loop_count > 20)
		{
			break;
		}

		Sleep(90);
	}

	if(active__vlv_open)
	{
		int alm_id = ALID__SV_DOOR_OPEN_ERROR;
		CString alm_msg;
		CString r_act;

		alm_msg = "You can't open DV. \n";

		p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);

		if(r_act.CompareNoCase("RETRY")  == 0)		goto LOOP_RETRY;
		if(r_act.CompareNoCase("IGNORE") != 0)		return -11;
	}

	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__DV_TRANSFER_OPEN);
}
int  CObj__LBx_ManiFold_X::
Call__DV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM *p_alarm)
{
	if((dEXT_CH__CFG_SETUP_TEST_MODE->Check__DATA(STR__ENABLE) > 0)
	&& (dEXT_CH__CFG_SETUP_LLx_DOOR_SLOT_VLV_CONTROL->Check__DATA(STR__DISABLE) > 0))
	{
		return 1;
	}

	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__DV_TRANSFER_CLOSE);
}

int  CObj__LBx_ManiFold_X::
Call__SV_OPEN(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM *p_alarm)
{
LOOP_RETRY:

	if((dEXT_CH__CFG_SETUP_TEST_MODE->Check__DATA(STR__ENABLE) > 0)
	&& (dEXT_CH__CFG_SETUP_LLx_DOOR_SLOT_VLV_CONTROL->Check__DATA(STR__DISABLE) > 0))
	{
		if(Is__ALL_SV_OPEN())
		{
			return 1;
		}
	}

	if(Is__SLOT_DV_OPEN())
	{
		int alm_id = ALID__SV_DOOR_OPEN_ERROR;
		CString alm_msg;
		CString r_act;

		alm_msg = "You can't open DV. \n";

		p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);

		if(r_act.CompareNoCase("RETRY")  == 0)		goto LOOP_RETRY;
		if(r_act.CompareNoCase("IGNORE") != 0)		return -11;
	}

	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__SV_TRANSFER_OPEN);
}
int  CObj__LBx_ManiFold_X::
Call__SV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM *p_alarm)
{
	if((dEXT_CH__CFG_SETUP_TEST_MODE->Check__DATA(STR__ENABLE) > 0)
	&& (dEXT_CH__CFG_SETUP_LLx_DOOR_SLOT_VLV_CONTROL->Check__DATA(STR__DISABLE) > 0))
	{
		return 1;
	}

	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__SV_TRANSFER_CLOSE);
}

int  CObj__LBx_ManiFold_X::
Call__LIFT_PIN_UP(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT("LIFT_PIN.UP");
}
int  CObj__LBx_ManiFold_X::
Call__LIFT_PIN_DOWN(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT("LIFT_PIN.DOWN");
}

// ...
int  CObj__LBx_ManiFold_X::
Call__ISOLATE(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	for(int i=0; i<iLBx_SLOT_SIZE; i++)
	{
		ch_data.Format("%1d", i+1);
		aEXT_CH__PARA_SLOT_ID->Set__DATA(ch_data);

		// DV CLOSE ...
		{
			int r_flag = Call__DV_CLOSE(p_variable, p_alarm);
			if(r_flag < 0)		return r_flag;
		}

		// SV CLOSE ...
		{
			int r_flag = Call__SV_CLOSE(p_variable, p_alarm);
			if(r_flag < 0)		return r_flag;
		}
	}

	return pLBx_CHM__OBJ_CTRL->Call__OBJECT("ALL_GAS_VLV_CLOSE");
}

int  CObj__LBx_ManiFold_X::
Call__CYCLE_PURGE(CII_OBJECT__ALARM* p_alarm, CII_OBJECT__VARIABLE* p_variable)
{
	int flag;
	CString str_get_cfg;
	CString str_temp;
	CString str_msg;

	int cfg_count;
	int current_count = 0;

	SCX__TIMER_CTRL xTimer;
	xTimer->REGISTER__ABORT_OBJECT(sObject_Name);

	aCFG_CH__CYCLE_PURGE_COUNT->Get__DATA(str_get_cfg);
	cfg_count = atoi(str_get_cfg);

	do 
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return OBJ_ABORT;
		}

		// ...
		{
			current_count++;
			str_temp.Format("%d", current_count);

			sCFG_CH__CYCLE_PURGE_CURRENT_COUNT->Set__DATA(str_temp);
			sCFG_CH__CYCLE_PURGE_SEQ_MSG->Set__DATA("Pumping Started...");
		}

		// ...
		{
			flag = Call__PUMP(p_alarm, p_variable);
			if(flag < 0)
			{
				sCFG_CH__CYCLE_PURGE_SEQ_MSG->Set__DATA("Pumping Aborted...");
				return flag;
			}
		}

		// ...
		{
			aCFG_CH__CYCLE_PURGE_PUMPDOWN_TIME_LIMIT->Get__DATA(str_temp);
			str_msg.Format("Pumping %.d sec Delay...", atoi(str_temp));
			sCFG_CH__CYCLE_PURGE_SEQ_MSG->Set__DATA(str_msg);

			if(xTimer->WAIT(atoi(str_temp)) < 0)
			{
				return OBJ_ABORT;
			}
		}

		// ...
		{
			sCFG_CH__CYCLE_PURGE_SEQ_MSG->Set__DATA("Venting Started...");

			flag = Call__VENT(p_variable);
			if(flag < 0)
			{
				sCFG_CH__CYCLE_PURGE_SEQ_MSG->Set__DATA("Venting Aborted...");
				return flag;
			}
		}
	} 
	while(cfg_count > current_count);

	// ...
	{
		sCFG_CH__CYCLE_PURGE_SEQ_MSG->Set__DATA("Pumping Started...");

		flag = Call__PUMP(p_alarm, p_variable);
		if(flag < 0)
		{
			sCFG_CH__CYCLE_PURGE_SEQ_MSG->Set__DATA("Pumping Aborted...");
			return flag;
		}

		sCFG_CH__CYCLE_PURGE_SEQ_MSG->Set__DATA("Completed...");
	}

	return 1;
}
