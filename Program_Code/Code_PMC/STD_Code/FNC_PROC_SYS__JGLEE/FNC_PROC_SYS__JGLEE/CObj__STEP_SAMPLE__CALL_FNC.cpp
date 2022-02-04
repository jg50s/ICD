#include "StdAfx.h"
#include "CObj__STEP_SAMPLE.h"
#include "CObj__STEP_SAMPLE__DEF.h"

#include "Macro_Function.h"


// ...
int CObj__STEP_SAMPLE
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int CObj__STEP_SAMPLE
::Call__READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int CObj__STEP_SAMPLE
::Call__START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int CObj__STEP_SAMPLE
::Call__PROC(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;
	CString log_bff;

	CString rcp__step_msg;
	CString rcp__step_mode;
	CString rcp__step_time;

	CString rcp__apc_mode;
	CString rcp__apc_position;
	CString rcp__apc_pressure;

	// RCP ...
	{
		sCH__RCP_STEP_MESSAGE->Get__DATA(rcp__step_msg);
		dCH__RCP_STEP_MODE->Get__DATA(rcp__step_mode);
		aCH__RCP_STEP_TIME->Get__DATA(rcp__step_time);

		dCH__RCP_APC_MODE->Get__DATA(rcp__apc_mode);
		aCH__RCP_APC_POSITION->Get__DATA(rcp__apc_position);
		aCH__RCP_APC_PRESSURE->Get__DATA(rcp__apc_pressure);
	}

	// LOG ...
	{
		log_msg  = "\n";
		log_msg += "Recipe Step-Info ... \n";

		// STEP ...
		{
			log_bff.Format(" * %s <- %s \n", 
							sCH__RCP_STEP_MESSAGE->Get__CHANNEL_NAME(),
							rcp__step_msg);
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n", 
							dCH__RCP_STEP_MODE->Get__CHANNEL_NAME(),
							rcp__step_mode);
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n", 
							aCH__RCP_STEP_TIME->Get__CHANNEL_NAME(),
							rcp__step_time);
			log_msg += log_bff;
		}

		// APC ...
		{
			log_bff.Format(" * %s <- %s \n", 
							dCH__RCP_APC_MODE->Get__CHANNEL_NAME(),
							rcp__apc_mode);
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n", 
							aCH__RCP_APC_POSITION->Get__CHANNEL_NAME(),
							rcp__apc_position);
			log_msg += log_bff;
	
			log_bff.Format(" * %s <- %s \n", 
							aCH__RCP_APC_PRESSURE->Get__CHANNEL_NAME(),
							rcp__apc_pressure);
			log_msg += log_bff;
		}

		//
		xLOG_CTRL->WRITE__LOG(log_msg);		
	}

	// APC.CTRL ...
	{
		CString obj_mode;
		CString para_data;

		if(rcp__apc_mode.CompareNoCase(STR__POSITION) == 0)
		{
			obj_mode  = _APC_CMD__POSITION;
			para_data = rcp__apc_position;
		}
		else if(rcp__apc_mode.CompareNoCase(STR__PRESSURE) == 0)
		{
			obj_mode  = _APC_CMD__PRESSURE;
			para_data = rcp__apc_pressure;
		}

		APC_OBJ__Start_MODE(obj_mode, para_data);
	}

	// ...
	bool active__stable_mode = false;
	bool active__fast_vac = false;

	if(rcp__step_mode.CompareNoCase(STR__Stable) == 0)
	{
		active__stable_mode = true;
	}
	else if(rcp__step_mode.CompareNoCase(STR__Fast_Vac) == 0)
	{
		active__fast_vac = true;
	}

	// ...
	double cfg__stable_min_sec = aCH__CFG_STEP_STABLE_MIN_SEC->Get__VALUE();

	// ...
	SCX__STEP_TIMER_CTRL x_step_timer;
	x_step_timer->START__TIMER();

	double para__step_sec = atof(rcp__step_time);
	double cur_sec  = 0.0;

	while(1)
	{
		// CHECK : STEP.ACT ...
		int cur_ctrl = Get__STEP_CTRL();

		if(cur_ctrl != _CMD_ID__START)
		{
			return cur_ctrl;
		}

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1;
		}

		if(dCH__CFG_STEP_ALARM_TEST_ACTIVE->Check__DATA(STR__ON) > 0)
		{
			return -2;
		}

		if(active__stable_mode)
		{
			if(cur_sec >= cfg__stable_min_sec)
			{
				/*
				bool active__pressure_stable = true;

				if(active_stable__apc_ctrl)
				{
					if(apc_index >= 0)
					{
						if(dEXT_CH__APC_MON_PRESSURE_STABLE_ACTIVE_X[apc_index]->Check__DATA(STR__OFF) > 0)	
							active__pressure_stable = false;
					}
				}
				if(active_stable__vac_ctrl)
				{
					if(dEXT_CH__VAT_MON_PRESSURE_STABLE_ACTIVE->Check__DATA(STR__OFF) > 0)	
						active__pressure_stable = false;
				}

				if(active__pressure_stable)
				{
					break;
				}
				*/
			}
		}
		else if(active__fast_vac)
		{
			if(cur_sec >= cfg__stable_min_sec)
			{
				/*
				bool active__pressure_vac = false;

				if(active_vac__apc_ctrl)
				{
					double cur__pressure = aEXT_CH__APC_MON_PRESSURE->Get__VALUE();
					double ref__pressure = atof(rcp__apc_pressure);

					if(cur__pressure <= ref__pressure)			active__pressure_vac = true;
				}
				if(active_vac__vac_ctrl)
				{
					double cur__pressure = aEXT_CH__VAT_MON_PRESSURE->Get__VALUE();
					double ref__pressure = atof(rcp__vat_pressure);

					if(cur__pressure <= ref__pressure)			active__pressure_vac = true;
				}

				if(active__pressure_vac)
				{
					break;
				}
				*/
			}
		}

		if(cur_ctrl == _CMD_ID__START)
		{
			if(x_step_timer->Check__CURRENT_TIME(para__step_sec, cur_sec))
			{
				if((active__stable_mode)
				|| (active__fast_vac))
				{
					int alm_id = ALID__STABLE_OVERTIME;
					CString alm_msg;
					CString r_act;

					alm_msg.Format("Stable Timeout Error (%.1f sec) \n", para__step_sec);

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					return -1;
				}
				break;
			}
		}
	}

	return 1;
}

int CObj__STEP_SAMPLE
::Call__ABORT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	sCH__OBJ_MSG->Set__DATA("Call__ABORT() : Start ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");

	// ...
	{

	}

	sCH__OBJ_MSG->Set__DATA("Call__ABORT() : End ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");
	return 1;
}

int CObj__STEP_SAMPLE
::Call__END(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	sCH__OBJ_MSG->Set__DATA("Call__END() : Start ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");

	// ...
	{

	}

	sCH__OBJ_MSG->Set__DATA("Call__END() : End ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");
	return 1;
}


// ...
int CObj__STEP_SAMPLE
::Get__STEP_CTRL()
{
	CString cur_act = sCH__MON_STEP_EXCEPTION_ACT->Get__STRING();

	if(cur_act.CompareNoCase(_ACT_CMD__ABORT) == 0)
	{
		printf(" * Fnc__STEP() - ABORT ... \n");

		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg  = "\n";
			log_msg += "Step Exception Command ... \n";
		
			log_bff.Format(" * %s <- %s \n", 
							sCH__MON_STEP_EXCEPTION_ACT->Get__CHANNEL_NAME(),
							cur_act);
			log_msg += log_bff;

			xLOG_CTRL->WRITE__LOG(log_msg);		
		}
		return _CMD_ID__ABORT;
	}
	if(cur_act.CompareNoCase(_ACT_CMD__SKIP) == 0)
	{
		printf(" * Fnc__STEP() - SKIP ... \n");

		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg  = "\n";
			log_msg += "Step Exception Command ... \n";

			log_bff.Format(" * %s <- %s \n", 
							sCH__MON_STEP_EXCEPTION_ACT->Get__CHANNEL_NAME(),
							cur_act);
			log_msg += log_bff;

			xLOG_CTRL->WRITE__LOG(log_msg);		
		}
		return _CMD_ID__SKIP;
	}

	if(cur_act.CompareNoCase(_ACT_CMD__PAUSE) == 0)
	{
		printf(" * Fnc__STEP() - PAUSE ... \n");

		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg  = "\n";
			log_msg += "Step Exception Command ... \n";

			log_bff.Format(" * %s <- %s \n", 
							sCH__MON_STEP_EXCEPTION_ACT->Get__CHANNEL_NAME(),
							cur_act);
			log_msg += log_bff;

			xLOG_CTRL->WRITE__LOG(log_msg);		
		}
		return _CMD_ID__PAUSE;
	}

	return _CMD_ID__START;
}
