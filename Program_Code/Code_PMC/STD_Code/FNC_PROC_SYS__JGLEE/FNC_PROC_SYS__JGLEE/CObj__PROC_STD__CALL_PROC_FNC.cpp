#include "StdAfx.h"
#include "CObj__PROC_STD.h"


// PRE-PROCESS ...
int CObj__PROC_STD
::Call__PRE_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__PRE);

	return Fnc__PROC_READY(p_variable, p_alarm, false);
}
int CObj__PROC_STD
::Call__PRE_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__PRE);

	return Fnc__PROC_START_EX(p_variable, p_alarm, false);
}

// MAIN-PROCESS ...
int CObj__PROC_STD
::Call__MAIN_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__MAIN);

	return Fnc__PROC_READY(p_variable, p_alarm, false);
}
int CObj__PROC_STD
::Call__MAIN_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
LOOP_RETRY:

	if(dCH__CFG_DA_OFFSET_CHECK_BEFORE_PROCESSING->Check__DATA(STR__YES) > 0)
	{
		if(dEXT_CH__TMC_LINK_DA_REPORT_RESULT_WAFER->Check__DATA(STR__OK) < 0)
		{
			if(dEXT_CH__SLOT01_STATUS->Check__DATA(STR__NONE) < 0)
			{
				int alm_id = ALID__PROCESS_INTERLOCK__DA_OFFSET_ERROR;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("  * R_Offset <- %s (deg) \n", 
							   sEXT_CH__TMC_LINK_DA_REPORT_R_OFFSET_WAFER->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format("  * T_Offset <- %s (mm) \n", 
							   sEXT_CH__TMC_LINK_DA_REPORT_T_OFFSET_WAFER->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format("  * %s <- %s \n", 
							   dEXT_CH__TMC_LINK_DA_REPORT_RESULT_WAFER->Get__CHANNEL_NAME(),
							   dEXT_CH__TMC_LINK_DA_REPORT_RESULT_WAFER->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format("  * %s <- %s \n", 
							   dEXT_CH__SLOT01_STATUS->Get__CHANNEL_NAME(),
							   dEXT_CH__SLOT01_STATUS->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format("  * %s <- %s \n", 
							   sEXT_CH__SLOT01_TITLE->Get__CHANNEL_NAME(),
							   sEXT_CH__SLOT01_TITLE->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);

				if(r_act.CompareNoCase(ACT__RETRY)  == 0)		goto LOOP_RETRY;
				if(r_act.CompareNoCase(ACT__IGNORE) != 0)		return -11;
			}
		}
	}

	// ...
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__MAIN);

	return Fnc__PROC_START_EX(p_variable, p_alarm, false);
}

// POST-PROCESS ...
int CObj__PROC_STD
::Call__POST_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__POST);

	return Fnc__PROC_READY(p_variable, p_alarm, false);
}
int CObj__PROC_STD
::Call__POST_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__POST);

	int r_flag = Fnc__PROC_START_EX(p_variable, p_alarm, false);

	if(r_flag > 0)
	{
		aCH__MON_WAFER_INFO_CURRENT_COUNT_VALUE->Set__VALUE(0);
	}
	return r_flag;
}

// MANUAL-PROCESS ...
int CObj__PROC_STD
::Call__MANUAL_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__MANUAL);

	return Fnc__PROC_READY(p_variable, p_alarm, false);
}
int CObj__PROC_STD
::Call__MANUAL_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__MANUAL);

	return Fnc__PROC_START_EX(p_variable, p_alarm, false);
}

// ...
int CObj__PROC_STD
::Fnc__PROC_START_EX(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_dechuck)
{
LOOP_RETRY:

	int r_flag;

	if(dEXT_CH__CFG_BEFORE_PROCESS_DI_SENSOR_INTERLOCK_CHECK->Check__DATA(STR__YES) > 0)
	{
		r_flag = _Check__DI_INTERLOCK(p_variable, p_alarm);
		if(r_flag < 0)			return r_flag;
	}

	r_flag = Fnc__PROC_START(p_variable, p_alarm, active_dechuck);
	if(r_flag < 0)
	{
		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg = "\n";
			log_bff.Format(" * Fnc__PROC_START() : r_flag (%1d) \n", r_flag);
			log_msg += log_bff;
			log_bff.Format(" * %s <- %s \n",
							dCH__MON_EXCEPTION_ACT->Get__CHANNEL_NAME(),
							dCH__MON_EXCEPTION_ACT->Get__STRING());
			log_msg += log_bff;

			xI_LOG_CTRL->WRITE__LOG(log_msg);
		}

		if(dCH__MON_EXCEPTION_ACT->Check__DATA(ACT__RESTART) > 0)
		{
			if(Fnc__PROC_READY(p_variable, p_alarm, active_dechuck) > 0)
				goto LOOP_RETRY;
		}

		while(dCH__MON_EXCEPTION_ACT->Check__DATA(ACT__END_WITH_PLASMA_DECHUCK) > 0)
		{
			r_flag = Fnc__PROC_DECHUCK(p_variable, p_alarm);

			// ...
			{
				CString log_msg;
				CString log_bff;

				log_msg = "\n";
				log_bff.Format(" * Fnc__PROC_DECHUCK() : r_flag (%1d) \n", r_flag);
				log_msg += log_bff;
				log_bff.Format(" * %s <- %s \n",
								dCH__MON_EXCEPTION_ACT->Get__CHANNEL_NAME(),
								dCH__MON_EXCEPTION_ACT->Get__STRING());
				log_msg += log_bff;

				xI_LOG_CTRL->WRITE__LOG(log_msg);
			}
		}
	}

	dCH__MON_EXCEPTION_ACT->Set__DATA(_ACT_CMD__END);
	return r_flag;
}

