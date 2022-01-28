#include "StdAfx.h"
#include "CObj__LBx_TwoManiFold.h"
#include "CObj__LBx_TwoManiFold__DEF.h"


//----------------------------------------------------------------------------------------------------
int  CObj__LBx_TwoManiFold
::Call__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__INIT);
}

int  CObj__LBx_TwoManiFold
::Call__PUMP(CII_OBJECT__ALARM* p_alarm,CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__PUMP(p_alarm, p_variable, -1);
}
int  CObj__LBx_TwoManiFold
::Call__TRANSFER_PUMP(CII_OBJECT__ALARM* p_alarm,CII_OBJECT__VARIABLE* p_variable)
{
	// ...
	{
		sEXT_CH__SLIT_VALVE_LOCK_FLAG->Link__UPPER_OBJECT_ABORT(sObject_Name);
		sEXT_CH__SLIT_VALVE_LOCK_FLAG->Enable__UPPER_OBJECT_ABORT_CHECK();

		int flag = sEXT_CH__SLIT_VALVE_LOCK_FLAG->When__NOT_DATA(STR__YES);
		if(flag <= 0)		return OBJ_ABORT;
	}

	if(dEXT_CH__VAC_VLV_STATUS->Check__DATA(STR__OPEN) > 0)
	{
		CString log_msg;

		log_msg = "Call__TRANSFER_PUMP() : VAC-Valve Open !";
		xLOG_CTRL->WRITE__LOG(log_msg);
		return 1;
	}

	return Fnc__PUMP(p_alarm, p_variable, 1);
}

int  CObj__LBx_TwoManiFold
::Fnc__PUMP(CII_OBJECT__ALARM* p_alarm,CII_OBJECT__VARIABLE* p_variable,const int transfer_flag)
{
Mode_Chk_Rty:

	// ...
	CString str_lbx_mode;
	CString str_tmx_mode;
	CString str_obj_sts;

	dEXT_CH__OTHER_LBX_PUMPING_STS_FLAG->Link__UPPER_OBJECT_ABORT(sObject_Name);
	dEXT_CH__OTHER_LBX_PUMPING_STS_FLAG->Enable__UPPER_OBJECT_ABORT_CHECK();

	// ...
	int nRet = dEXT_CH__OTHER_LBX_PUMPING_STS_FLAG->When__DATA("END", 0.0);
	if(nRet <= 0)
	{
		return OBJ_ABORT;
	}

	// ...
	{
		Sleep(100);
		dCH__PUMPING_STS_FLAG->Set__DATA("PUMPING");
	}

	if(dEXT_CH__OTHER_LBX_PUMPING_STS_FLAG->Check__DATA("PUMPING") > 0)
	{
		dCH__PUMPING_STS_FLAG->Set__DATA("");
		goto Mode_Chk_Rty;
	}

	// LLx -----
	{
		if(sLBx__MODULE_NAME.CompareNoCase(STR__LEFT) == 0)
		{
			pPress_VLV__OBJ_CTRL->Call__OBJECT(CMMD__LBA_PUMP_VLV_OPEN);
		}
		else if(sLBx__MODULE_NAME.CompareNoCase(STR__RIGHT) == 0)
		{
			pPress_VLV__OBJ_CTRL->Call__OBJECT(CMMD__LBB_PUMP_VLV_OPEN);
		}

		if(pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__PUMP) < 0)
		{
			return -101;
		}

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -102;
		}
	}

	// ...
	CString obj_sts;

	// PUMP VLV OPEN -----
	// The Other LBx ...
	{
		pOther_LBx_CHM__OBJ_CTRL->Get__OBJECT_STATUS(obj_sts);

		if(Check__OBJECT_BUSY(obj_sts) < 0)
		{
			if(sEXT_CH__Other_LBx__PRESSURE_CTRL_FLAG->Check__DATA("PUMP") > 0)
			{
				if(dEXT_CH__Other_LBx__PRESSURE_STATUS->Check__DATA(STR__VAC) > 0)
				{
					if(sLBx__MODULE_NAME.CompareNoCase(STR__LEFT) == 0)
					{
						pPress_VLV__OBJ_CTRL->Call__OBJECT(CMMD__LBB_VAC_VLV_OPEN);
					}
					else if(sLBx__MODULE_NAME.CompareNoCase(STR__RIGHT) == 0)
					{
						pPress_VLV__OBJ_CTRL->Call__OBJECT(CMMD__LBA_VAC_VLV_OPEN);
					}
				}
			}
		}
	}

	return 1;
}

int  CObj__LBx_TwoManiFold::Call__VENT(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__VENT);
}
int  CObj__LBx_TwoManiFold::Call__LEAK_CHECK(CII_OBJECT__VARIABLE* p_variable)
{
	if(sLBx__MODULE_NAME.CompareNoCase(STR__LEFT) == 0)
	{
		return pLBx_MANIFOLD__OBJ_CTRL->Call__OBJECT("LEFT_LEAK_CHECK");
	}	
	if(sLBx__MODULE_NAME.CompareNoCase(STR__RIGHT) == 0)
	{
		return pLBx_MANIFOLD__OBJ_CTRL->Call__OBJECT("RIGHT_LEAK_CHECK");
	}

	return -1;
}

int  CObj__LBx_TwoManiFold::Call__PREPMATER(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__PREPMATER);
}
int  CObj__LBx_TwoManiFold::Call__COMPMATER(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__COMPMATER);
}

int  CObj__LBx_TwoManiFold::Call__IN_PROC(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__IN_PROC);
}

int  CObj__LBx_TwoManiFold::Call__OUT_PROC(CII_OBJECT__VARIABLE* p_variable)
{
	if((dEXT_CH__CFG_HEATER_USE->Check__DATA(STR__YES) > 0)
	&& (dEXT_CH__CFG_HEATER_SOFT_VENT_USE->Check__DATA(STR__YES) > 0))
	{
		return Fnc__OUT_PROC_With_ManiFoldType(p_variable);
	}

	return Fnc__OUT_PROC_With_SingleType(p_variable);
}
int  CObj__LBx_TwoManiFold::Fnc__OUT_PROC_With_SingleType(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__OUT_PROC);
}
int  CObj__LBx_TwoManiFold::Fnc__OUT_PROC_With_ManiFoldType(CII_OBJECT__VARIABLE* p_variable)
{
Mode_Chk_Rty:

	// ...
	CString str_lbx_mode;
	CString str_tmx_mode;
	CString str_obj_sts;

	dEXT_CH__OTHER_LBX_PUMPING_STS_FLAG->Link__UPPER_OBJECT_ABORT(sObject_Name);
	dEXT_CH__OTHER_LBX_PUMPING_STS_FLAG->Enable__UPPER_OBJECT_ABORT_CHECK();

	// ...
	int nRet = dEXT_CH__OTHER_LBX_PUMPING_STS_FLAG->When__DATA("END", 0.0);
	if(nRet <= 0)
	{
		return OBJ_ABORT;
	}

	// ...
	{
		Sleep(100);
		dCH__PUMPING_STS_FLAG->Set__DATA("PUMPING");
	}

	if(dEXT_CH__OTHER_LBX_PUMPING_STS_FLAG->Check__DATA("PUMPING") > 0)
	{
		dCH__PUMPING_STS_FLAG->Set__DATA("");
		goto Mode_Chk_Rty;
	}

	// LLx ...
	{
		if(sLBx__MODULE_NAME.CompareNoCase(STR__LEFT) == 0)
		{
			pPress_VLV__OBJ_CTRL->Call__OBJECT(CMMD__LBA_PUMP_VLV_OPEN);
		}
		else if(sLBx__MODULE_NAME.CompareNoCase(STR__RIGHT) == 0)
		{
			pPress_VLV__OBJ_CTRL->Call__OBJECT(CMMD__LBB_PUMP_VLV_OPEN);
		}

		if(pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__OUT_PROC) < 0)
		{
			return -101;
		}
		if(pLBx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__PUMP) < 0)
		{
			return -102;
		}

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -103;
		}
	}

	//.....
	CString obj_sts;

	// PUMP VLV OPEN -----
	// The Other LBx
	{
		pOther_LBx_CHM__OBJ_CTRL->Get__OBJECT_STATUS(obj_sts);

		if(Check__OBJECT_BUSY(obj_sts) < 0)
		{
			if(sEXT_CH__Other_LBx__PRESSURE_CTRL_FLAG->Check__DATA("PUMP") > 0)
			{
				if(dEXT_CH__Other_LBx__PRESSURE_STATUS->Check__DATA(STR__VAC) > 0)
				{
					if(sLBx__MODULE_NAME.CompareNoCase(STR__LEFT) == 0)
					{
						pPress_VLV__OBJ_CTRL->Call__OBJECT(CMMD__LBB_VAC_VLV_OPEN);
					}
					else if(sLBx__MODULE_NAME.CompareNoCase(STR__RIGHT) == 0)
					{
						pPress_VLV__OBJ_CTRL->Call__OBJECT(CMMD__LBA_VAC_VLV_OPEN);
					}
				}
			}
		}
	}

	return 1;
}

int  CObj__LBx_TwoManiFold::
Call__DV_OPEN(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM *p_alarm)
{
LOOP_RETRY:

	if((dEXT_CH__CFG_SETUP_TEST_MODE->Check__DATA(STR__ENABLE) > 0)
	&& (dEXT_CH__CFG_SETUP_LLx_DOOR_SLOT_VLV_CONTROL->Check__DATA(STR__DISABLE) > 0))
	{
		if(dEXT_CH__DOOR_VLV_STATUS->Check__DATA(STR__OPEN) > 0)
		{
			return 1;
		}
	}

	// ...
	bool active__vlv_open = true;
	int loop_count = 0;

	while(active__vlv_open)
	{
		if(dEXT_CH__VAC_VLV_STATUS->Check__DATA(STR__OPEN) < 0)
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
int  CObj__LBx_TwoManiFold::
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

int  CObj__LBx_TwoManiFold::
Call__SV_OPEN(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM *p_alarm)
{
LOOP_RETRY:

	if((dEXT_CH__CFG_SETUP_TEST_MODE->Check__DATA(STR__ENABLE) > 0)
		&& (dEXT_CH__CFG_SETUP_LLx_DOOR_SLOT_VLV_CONTROL->Check__DATA(STR__DISABLE) > 0))
	{
		if(dEXT_CH__VAC_VLV_STATUS->Check__DATA(STR__OPEN) > 0)
		{
			return 1;
		}
	}

	// jglee : 2019.05.29
	if(dEXT_CH__DOOR_VLV_STATUS->Check__DATA(STR__OPEN) > 0)
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
int  CObj__LBx_TwoManiFold::
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

int  CObj__LBx_TwoManiFold::
Call__LIFT_PIN_UP(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT("LIFT_PIN.UP");
}
int  CObj__LBx_TwoManiFold::
Call__LIFT_PIN_DOWN(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx_CHM__OBJ_CTRL->Call__OBJECT("LIFT_PIN.DOWN");
}

// ...
int  CObj__LBx_TwoManiFold::
Call__ISOLATE(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM *p_alarm)
{
	int flag;

	// DV CLOSE ...
	{
		flag = Call__DV_CLOSE(p_variable, p_alarm);
		if(flag < 0)		return flag;
	}
	// SV CLOSE ...
	{
		flag = Call__SV_CLOSE(p_variable, p_alarm);
		if(flag < 0)		return flag;
	}

	if(sLBx__MODULE_NAME.CompareNoCase(STR__LEFT) == 0)
	{
		return pPress_VLV__OBJ_CTRL->Call__OBJECT(CMMD__LBA_ALL_VLV_CLOSE);
	}
	if(sLBx__MODULE_NAME.CompareNoCase(STR__RIGHT) == 0)
	{
		return pPress_VLV__OBJ_CTRL->Call__OBJECT(CMMD__LBB_ALL_VLV_CLOSE);
	}

	return -1;
}

int  CObj__LBx_TwoManiFold::
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
