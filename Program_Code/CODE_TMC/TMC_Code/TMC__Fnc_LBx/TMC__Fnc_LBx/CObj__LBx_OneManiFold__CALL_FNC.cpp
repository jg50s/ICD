#include "StdAfx.h"
#include "CObj__LBx_OneManiFold.h"
#include "CObj__LBx_OneManiFold__DEF.h"


//----------------------------------------------------------------------------------------------------
int  CObj__LBx_OneManiFold
::Call__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return pLLx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__INIT);
}

int  CObj__LBx_OneManiFold
::Call__PUMP(CII_OBJECT__ALARM* p_alarm,CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__PUMP(p_alarm, p_variable, -1);
}
int  CObj__LBx_OneManiFold
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

int  CObj__LBx_OneManiFold
::Fnc__PUMP(CII_OBJECT__ALARM* p_alarm,CII_OBJECT__VARIABLE* p_variable,const int transfer_flag)
{
	dCH__PUMPING_STS_FLAG->Set__DATA("PUMPING");

	// LLx ...
	{
		if(pLLx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__PUMP) < 0)
		{
			return -101;
		}

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -102;
		}
	}

	return 1;
}

int  CObj__LBx_OneManiFold::Call__VENT(CII_OBJECT__VARIABLE* p_variable)
{
	return pLLx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__VENT);
}
int  CObj__LBx_OneManiFold::Call__LEAK_CHECK(CII_OBJECT__VARIABLE* p_variable)
{
	return pLLx_UTILITY__OBJ_CTRL->Call__OBJECT(CMMD__LLx_LEAK_CHECK);
}

int  CObj__LBx_OneManiFold::Call__PREPMATER(CII_OBJECT__VARIABLE* p_variable)
{
	return pLLx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__PREPMATER);
}
int  CObj__LBx_OneManiFold::Call__COMPMATER(CII_OBJECT__VARIABLE* p_variable)
{
	return pLLx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__COMPMATER);
}

int  CObj__LBx_OneManiFold::Call__IN_PROC(CII_OBJECT__VARIABLE* p_variable)
{
	return pLLx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__IN_PROC);
}
int  CObj__LBx_OneManiFold::Call__OUT_PROC(CII_OBJECT__VARIABLE* p_variable)
{
	return pLLx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__OUT_PROC);
}

int  CObj__LBx_OneManiFold::
Call__DV_OPEN(CII_OBJECT__VARIABLE* p_variable)
{
	return pLLx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__DV_TRANSFER_OPEN);
}
int  CObj__LBx_OneManiFold::
Call__DV_CLOSE(CII_OBJECT__VARIABLE* p_variable)
{
	return pLLx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__DV_TRANSFER_CLOSE);
}

int  CObj__LBx_OneManiFold::
Call__SV_OPEN(CII_OBJECT__VARIABLE* p_variable)
{
	return pLLx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__SV_TRANSFER_OPEN);
}
int  CObj__LBx_OneManiFold::
Call__SV_CLOSE(CII_OBJECT__VARIABLE* p_variable)
{
	return pLLx_CHM__OBJ_CTRL->Call__OBJECT(CMMD__SV_TRANSFER_CLOSE);
}

int  CObj__LBx_OneManiFold::
Call__LIFT_PIN_UP(CII_OBJECT__VARIABLE* p_variable)
{
	return pLLx_CHM__OBJ_CTRL->Call__OBJECT("LIFT_PIN.UP");
}
int  CObj__LBx_OneManiFold::
Call__LIFT_PIN_DOWN(CII_OBJECT__VARIABLE* p_variable)
{
	return pLLx_CHM__OBJ_CTRL->Call__OBJECT("LIFT_PIN.DOWN");
}

int  CObj__LBx_OneManiFold::
Call__CYCLE_LIFT_PIN(CII_OBJECT__VARIABLE* p_variable)
{
	sCH__ACTIVE_CYCLE_LIFT_PIN->Set__DATA(STR__YES);

	int r_flag = Fnc__CYCLE_LIFT_PIN(p_variable);

	sCH__ACTIVE_CYCLE_LIFT_PIN->Set__DATA("");
	return r_flag;
}
int  CObj__LBx_OneManiFold::
Fnc__CYCLE_LIFT_PIN(CII_OBJECT__VARIABLE* p_variable)
{
	SCX__TIMER_CTRL x_up_delay;
	SCX__TIMER_CTRL x_down_delay;

	x_up_delay->REGISTER__ABORT_OBJECT(sObject_Name);
	x_up_delay->REGISTER__COUNT_CHANNEL(sCH__CUR_CYCLE_LIFT_PIN__UP_DELAY_SEC->Get__CHANNEL_NAME());

	x_down_delay->REGISTER__ABORT_OBJECT(sObject_Name);
	x_down_delay->REGISTER__COUNT_CHANNEL(sCH__CUR_CYCLE_LIFT_PIN__DOWN_DELAY_SEC->Get__CHANNEL_NAME());

	if(pLLx_CHM__OBJ_CTRL->Call__OBJECT("LIFT_PIN.DOWN") < 0)
	{
		return -11;
	}

	// ...
	CString ch_data;

	int cfg_count = (int) aCH__CFG_CYCLE_LIFT_PIN__COUNT->Get__VALUE();
	int i;

	// Data Initial ...
	{
		sCH__CUR_CYCLE_LIFT_PIN__COUNT->Set__DATA("");
		sCH__CUR_CYCLE_LIFT_PIN__UP_DELAY_SEC->Set__DATA("");
		sCH__CUR_CYCLE_LIFT_PIN__DOWN_DELAY_SEC->Set__DATA("");

		for(i=0; i<CFG_ACTION__SIZE; i++)
		{
			sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_CUR[i]->Set__DATA("");
			sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_AVG[i]->Set__DATA("");
			sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_MIN[i]->Set__DATA("");
			sCH__RESULT_CYCLE_LIFT_PIN_ACTION_TIME_MAX[i]->Set__DATA("");
		}
	}

	for(i=0; i<cfg_count; i++)
	{
		int n_count = i + 1;

		ch_data.Format("%1d", n_count);
		sCH__CUR_CYCLE_LIFT_PIN__COUNT->Set__DATA(ch_data);

		// Up Action ...
		{
			SCX__ASYNC_TIMER_CTRL x_timer;
			x_timer->START__COUNT_UP(9999);

			if(pLLx_CHM__OBJ_CTRL->Call__OBJECT("LIFT_PIN.UP") < 0)
			{
				return -21;
			}

			// ...
			{
				double cur_sec = x_timer->Get__CURRENT_TIME();

				int db_i = _ACT_INDEX__UP;
				_Update__ACTION_AVG_MIN_MAX(db_i,cur_sec, n_count);
			}

			double cfg_sec = aCH__CFG_CYCLE_LIFT_PIN__UP_DELAY_SEC->Get__VALUE();
			if(x_up_delay->WAIT(cfg_sec) < 0)		return -22;
		}

		// Down Action ...
		{
			SCX__ASYNC_TIMER_CTRL x_timer;
			x_timer->START__COUNT_UP(9999);

			if(pLLx_CHM__OBJ_CTRL->Call__OBJECT("LIFT_PIN.DOWN") < 0)
			{
				return -31;
			}

			// ...
			{
				double cur_sec = x_timer->Get__CURRENT_TIME();

				int db_i = _ACT_INDEX__DOWN;
				_Update__ACTION_AVG_MIN_MAX(db_i,cur_sec, n_count);
			}

			if(n_count < cfg_count)
			{
				double cfg_sec = aCH__CFG_CYCLE_LIFT_PIN__DOWN_DELAY_SEC->Get__VALUE();
				if(x_down_delay->WAIT(cfg_sec) < 0)		return -32;
			}
		}
	}

	return 1;
}

int  CObj__LBx_OneManiFold::
Call__ISOLATE(CII_OBJECT__VARIABLE* p_variable)
{
	int r_flag;

	r_flag = Call__DV_CLOSE(p_variable);
	if(r_flag < 0)			return r_flag;

	r_flag = Call__SV_CLOSE(p_variable);
	if(r_flag < 0)			return r_flag;

	return pLLx_CHM__OBJ_CTRL->Call__OBJECT("ALL_GAS_VLV_CLOSE");
}

int  CObj__LBx_OneManiFold::
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
