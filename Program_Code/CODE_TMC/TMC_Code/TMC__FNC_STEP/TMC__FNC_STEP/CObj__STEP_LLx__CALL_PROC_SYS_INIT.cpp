#include "StdAfx.h"
#include "CObj__STEP_LLx.h"
#include "CObj__STEP_LLx__DEF.h"


// PROC.SYSTEM_INIT ...
int CObj__STEP_LLx::
Call__PROC_SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable, 
					   CII_OBJECT__ALARM* p_alarm) 
{
	CString err_msg;

	int flag = Fnc__PROC_SYSTEM_INIT(p_variable,p_alarm,err_msg); 

	if(flag < 0)
	{
		//
		CString log_msg; 	

		log_msg.Format("Call__PROC_SYSTEM_INIT() : Flag[%1d] \n", flag); 
		log_msg += err_msg;

		xLOG_CTRL->WRITE__LOG(log_msg); 

		//
		int alarm_id = ALID__PROC_RESTART_SYSTEM_INIT_ERROR;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alarm_id,log_msg);
	}

	return flag; 
}
int CObj__STEP_LLx::
Fnc__PROC_SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable,
					  CII_OBJECT__ALARM* p_alarm,
					  CString& err_msg)
{
	// APC ...
	if(pOBJ_CTRL__APC->Call__OBJECT(STR__INIT) < 0)
	{
		err_msg = "APC : Initial Error !";
		return -11;
	}

	/*
	// TEMP : INIT & TUNE
	{
		pOBJ_CTRL__HEATER_WALL->Call__OBJECT(STR__INIT);
		pOBJ_CTRL__CHILLER->Call__OBJECT(STR__INIT);
		pOBJ_CTRL__TCU->Call__OBJECT(STR__INIT);

		// pOBJ_CTRL__HEATER_WALL->Call__OBJECT(STR__TEMP_AUTO_TUNE);
	}

	// ESC ...
	if(pOBJ_CTRL__ESC->Call__OBJECT(STR__INIT) < 0)
	{
		err_msg = "ESC : Initial Error !";
		return -31;
	}

	// ...
	{
		// RF 2MHz ...
		if(pOBJ_CTRL__RF_GEN_2MHz->Call__OBJECT(STR__INIT) < 0)
		{
			err_msg = "RF 2MHz : Initial Error !";
			return -41;
		}
		// RF 27MHz ...
		if(pOBJ_CTRL__RF_GEN_27MHz->Call__OBJECT(STR__INIT) < 0)
		{
			err_msg = "RF 27MHz : Initial Error !";
			return -42;
		}
		// RF 60MHz ...
		if(pOBJ_CTRL__RF_GEN_60MHz->Call__OBJECT(STR__INIT) < 0)
		{
			err_msg = "RF 60MHz : Initial Error !";
			return -43;
		}
	}

	// MATCHER ...
	if(pOBJ_CTRL__RF_MATCH->Call__OBJECT(STR__INIT) < 0)
	{
		err_msg = "Matcher : Initial Error !";
		return -51;
	}
	*/

	return 1;
}
