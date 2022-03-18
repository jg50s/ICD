#include "StdAfx.h"
#include "CObj__PROC_STD.h"


// ...
int CObj__PROC_STD
::Fnc__PROC_READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_dechuck)
{
	if(dCH__CUR_PROCESS_TYPE->Check__DATA(STR__MANUAL) > 0)
	{
		if(dCH__PARA_MANUAL_PROCESS_DECHUCK_ACTIVE->Check__DATA(STR__ON) > 0)
			sEXT_CH__SYS_CTRL_LOCK->Set__DATA(STR__DECHUCK_PROC);
		else
			sEXT_CH__SYS_CTRL_LOCK->Set__DATA(STR__MAINT_PROC);
	}
	else
	{
		sEXT_CH__SYS_CTRL_LOCK->Set__DATA(STR__AUTO_PROC);
	}

	int r_flag = _Fnc__PROC_READY(p_variable, p_alarm, active_dechuck);

	// ...
	{
		sEXT_CH__SYS_CTRL_LOCK->Set__DATA("");
	}
	return r_flag;
}
int CObj__PROC_STD
::_Fnc__PROC_READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_dechuck)
{
	CString log_msg;

	// PARA.INIT ...
	{
		sCH__PRC_TOTAL_TIME_TO_CTC->Set__DATA("");
		sEXT_CH__PRC_CHANGE_TIME_TO_CTC->Set__DATA("");

		sCH__PRC_CHANGE_TIME_TO_CTC->Set__DATA("");
		sEXT_CH__PRC_CHANGE_TIME_TO_CTC->Set__DATA("");

		sCH__PRC_TOTAL_TIME->Set__DATA("");
		sCH__PRC_CUR_TIME->Set__DATA("");

		//
		aCH__STEP_TOTAL_NUM->Set__DATA("0");
		aCH__STEP_CUR_NUM->Set__DATA("-1");
	}

	// CHM : HIGH_VAC ...
	{
		log_msg = "HIGH_VAC Started ...";
		xI_LOG_CTRL->WRITE__LOG(log_msg);

		if(pOBJ_CTRL__CHM->Call__OBJECT(_CHM_CMD__HIGH_VAC_PUMP) < 0)
		{
			return -11;
		}
	}

	return Sub__PROC_READY(p_variable, p_alarm, active_dechuck);
}

int CObj__PROC_STD
::Fnc__PROC_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_dechuck)
{
	dCH__MON_EXCEPTION_ACT->Set__DATA(_ACT_CMD__START);
	sEXT_CH__MON_STEP_EXCEPTION_ACT->Set__DATA("");

	if(dCH__CUR_PROCESS_TYPE->Check__DATA(STR__MANUAL) > 0)
	{
		if(dCH__PARA_MANUAL_PROCESS_DECHUCK_ACTIVE->Check__DATA(STR__ON) > 0)
			sEXT_CH__SYS_CTRL_LOCK->Set__DATA(STR__DECHUCK_PROC);
		else
			sEXT_CH__SYS_CTRL_LOCK->Set__DATA(STR__MAINT_PROC);
	}
	else
	{
		sEXT_CH__SYS_CTRL_LOCK->Set__DATA(STR__AUTO_PROC);
	}

	int r_flag = _Fnc__PROC_START(p_variable, p_alarm, active_dechuck);

	// ...
	{
		sEXT_CH__SYS_CTRL_LOCK->Set__DATA("");
	}

	// ...
	{
		Fnc__PRC_LOG__DISABLE(p_variable);

		sEXT_CH__PMC_PROCESS_STATUS->Set__DATA(STR__Idle);

		aCH__STEP_CUR_NUM->Set__DATA("-1");		
	}

	Sub__PROC_END(p_variable, p_alarm);

	if((dCH__MON_EXCEPTION_ACT->Check__DATA(ACT__RESTART) < 0)
	&& (dCH__MON_EXCEPTION_ACT->Check__DATA(ACT__END_WITH_PLASMA_DECHUCK) < 0))
	{
		dCH__MON_EXCEPTION_ACT->Set__DATA(_ACT_CMD__END);
	}
	return r_flag;
}
int CObj__PROC_STD
::_Fnc__PROC_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_dechuck)
{
	int r_flag = 1;

	if(r_flag > 0)	
	{
		r_flag = Sub__PROC_START(p_variable, p_alarm, active_dechuck);
		if(r_flag < 0)		return r_flag;
	}

	if(r_flag > 0)
	{
		iActive__PROC_START = 1;

		r_flag = Sub__PROC_CTRL(p_variable, p_alarm, active_dechuck);
		if(r_flag < 0)		return r_flag;
	}
	return 1;

}

int CObj__PROC_STD::
Check__STEP_LOOP(const int cur__step_id)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg = "Loop_Cycle Info ... \n";

		log_bff.Format("  * %s <- %.0f \n",
						aCH__RCP_LOOP_START->Get__CHANNEL_NAME(),
						aCH__RCP_LOOP_START->Get__VALUE());
		log_msg += log_bff;

		log_bff.Format("  * %s <- %.0f \n",
						aCH__RCP_LOOP_REPEAT->Get__CHANNEL_NAME(),
						aCH__RCP_LOOP_REPEAT->Get__VALUE());
		log_msg += log_bff;

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	CString ch_data;

	if(!bACTIVE__LOOP_STEP)
	{
		int rcp__step_start  = (int) aCH__RCP_LOOP_START->Get__VALUE();
		int rcp__loop_repeat = (int) aCH__RCP_LOOP_REPEAT->Get__VALUE();

		if(rcp__loop_repeat < 1)
		{
			return 1;
		}

		if((rcp__step_start > 0) && (rcp__step_start < cur__step_id))
		{
			bACTIVE__LOOP_STEP = true;

			iLOOP__STEP_START = rcp__step_start;
			iLOOP__STEP_END   = cur__step_id;

			iLOOP__STEP_REPEAT = rcp__loop_repeat;
			iLOOP__STEP_COUNT  = 0;

			printf(" * Loop Active .. \n");
			printf("  * steo_start  <- [%1d] \n", rcp__step_start );
			printf("  * loop_repeat <- [%1d] \n", rcp__loop_repeat);
			printf("\n");
		}
		else
		{
			// Alarm & Abort

			return -1;
		}
	}

	if(!bACTIVE__LOOP_STEP)
	{
		return 1;
	}

	if(cur__step_id >= iLOOP__STEP_END)
	{
		iLOOP__STEP_COUNT++;

		if(iLOOP__STEP_COUNT > iLOOP__STEP_REPEAT)
		{
			bACTIVE__LOOP_STEP = false;

			sCH__STEP_LOOP_MSG->Set__DATA("");
		}
		else
		{
			int jump__step_id = iLOOP__STEP_START;

			ch_data.Format("%1d", jump__step_id - 1);
			aCH__STEP_CUR_NUM->Set__DATA(ch_data);

			xRCP__FILE_CTRL->Jump__STEP_NO(jump__step_id);

			log_msg.Format("Step%1d -> Step%1d : %1d",
							iLOOP__STEP_END,
							iLOOP__STEP_START,
							iLOOP__STEP_COUNT);

			sCH__STEP_LOOP_MSG->Set__DATA(log_msg);
		}

		// Loop.Info ...
		if(bACTIVE__LOOP_STEP)
		{
			log_msg = "Loop_Cycle Info ... \n";

			log_bff.Format("  * step_count <- %1d \n", iLOOP__STEP_COUNT);
			log_msg += log_bff;

			log_bff.Format("  * loop_step_start <- %1d \n", iLOOP__STEP_START);
			log_msg += log_bff;

			log_bff.Format("  * loop_step_end <- %1d \n", iLOOP__STEP_END);
			log_msg += log_bff;

			log_bff.Format("  * loop_count <- %1d \n", iLOOP__STEP_REPEAT);
			log_msg += log_bff;

			xI_LOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	return 1;
}
