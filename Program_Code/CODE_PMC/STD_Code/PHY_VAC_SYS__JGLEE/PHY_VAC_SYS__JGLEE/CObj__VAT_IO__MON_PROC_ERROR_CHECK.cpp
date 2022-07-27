#include "StdAfx.h"
#include "CObj__VAT_IO.h"
#include "CObj__VAT_IO__ALID.h"


// ...
int  CObj__VAT_IO
::Mon__PROC_ERROR_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CClass__Error_Timer error__proc_warning;
	CClass__Error_Timer error__proc_abort;

	CString ch_data;

	CString str_msg;
	CString str_bff;


	// Range.Warning ...
	{
		CLink__Error_Common x_link_common;

		// ...
		{
			x_link_common.pCH__CFG_USE = dCH__CFG_USE.Get__PTR();
			x_link_common.pCH__ACTIVE_CHECK = dCH__MON_PROC_PRESSURE_CHECK_ACTIVE.Get__PTR();

			x_link_common.pCH__CFG_STABLE_DELAY_SEC = aCH__CFG_PRESSURE_STABLE_DELAY_TIME.Get__PTR();
			x_link_common.pCH__CUR_STABLE_DELAY_SEC = sCH__MON_PROC_PRESSURE_STABLE_DELAY_TIME.Get__PTR();

			x_link_common.pCH__CFG_STABLE_CHECK_SEC = aCH__CFG_PRESSURE_STABLE_CHECK_TIME.Get__PTR();
			x_link_common.pCH__CUR_STABLE_CHECK_SEC = sCH__MON_PROC_PRESSURE_STABLE_CHECK_TIME.Get__PTR();

			x_link_common.pCH__CUR_ERROR_MIN = sCH__MON_PROC_PRESSURE_STABLE_MIN.Get__PTR();
			x_link_common.pCH__CUR_ERROR_MAX = sCH__MON_PROC_PRESSURE_STABLE_MAX.Get__PTR();

			x_link_common.pCH__CFG_TOLERANCE_ZERO_PERCENT = aCH__CFG_Zero_Setpoint_Tolerance_Compensation.Get__PTR();	
		}

		// Process ...
		{
			error__proc_warning.Disable__MAX_RANGE();

			error__proc_warning.Link__REF_OUT_CHANNEL(sCH__MON_SET_PRESSURE_TORR);
			error__proc_warning.Link__REF_IN_CHANNEL(sCH__MON_PRESSURE_TORR);
			error__proc_warning.Link__REF_RANGE_CHANNEL(aCH__PARA_PRESSURE);

			error__proc_warning.Link__ERROR_COMMON(&x_link_common);

			// ...
			CLink__Error_Para x_link_para;

			x_link_para.pCH__CFG_STABLE_DATA_PERCENT    = aCH__CFG_PRESSURE_WARNING_BAND.Get__PTR();
			x_link_para.pCH__CFG_TOLERANCE_DATA_PERCENT = aCH__CFG_PRESSURE_WARNING_BAND.Get__PTR();
			x_link_para.pCH__CFG_ERROR_CHECK_SEC        = aCH__CFG_PRESSURE_WARNING_TIMEOUT.Get__PTR();
			x_link_para.pCH__CUR_ERROR_CHECK_SEC        = sCH__MON_PROC_PRESSURE_WARNING_CHECK_TIME.Get__PTR();

			error__proc_warning.Link__ERROR_PARA(&x_link_para);
		}
	}
	// Range.Abort ...
	{
		CLink__Error_Common x_link_common;

		// ...
		{
			x_link_common.pCH__CFG_USE = dCH__CFG_USE.Get__PTR();
			x_link_common.pCH__ACTIVE_CHECK = dCH__MON_PROC_PRESSURE_CHECK_ACTIVE.Get__PTR();

			x_link_common.pCH__CFG_STABLE_DELAY_SEC = aCH__CFG_PRESSURE_STABLE_DELAY_TIME.Get__PTR();
			x_link_common.pCH__CFG_STABLE_CHECK_SEC = aCH__CFG_PRESSURE_STABLE_CHECK_TIME.Get__PTR();

			x_link_common.pCH__CUR_ERROR_MIN = sCH__MON_PROC_PRESSURE_ABORT_MIN.Get__PTR();
			x_link_common.pCH__CUR_ERROR_MAX = sCH__MON_PROC_PRESSURE_ABORT_MAX.Get__PTR();
		}

		// Process ...
		{
			error__proc_abort.Disable__MAX_RANGE();

			error__proc_abort.Link__REF_OUT_CHANNEL(sCH__MON_SET_PRESSURE_TORR);
			error__proc_abort.Link__REF_IN_CHANNEL(sCH__MON_PRESSURE_TORR);
			error__proc_abort.Link__REF_RANGE_CHANNEL(aCH__PARA_PRESSURE);

			error__proc_abort.Link__ERROR_COMMON(&x_link_common);

			// ...
			CLink__Error_Para x_link_para;

			x_link_para.pCH__CFG_STABLE_DATA_PERCENT    = aCH__CFG_PRESSURE_WARNING_BAND.Get__PTR();
			x_link_para.pCH__CFG_TOLERANCE_DATA_PERCENT = aCH__CFG_PRESSURE_ABORT_BAND.Get__PTR();
			x_link_para.pCH__CFG_ERROR_CHECK_SEC        = aCH__CFG_PRESSURE_ABORT_TIMEOUT.Get__PTR();
			x_link_para.pCH__CUR_ERROR_CHECK_SEC        = sCH__MON_PROC_PRESSURE_ABORT_CHECK_TIME.Get__PTR();

			error__proc_abort.Link__ERROR_PARA(&x_link_para);
		}
	}

	// Timer.Init ...
	{
		error__proc_warning.Init();
		error__proc_abort.Init();
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		
		// ...
		int active__proc_state = dEXT_CH__MON_SYSTEM_PROCESS_ACTIVE->Check__DATA(STR__ON);

		if((active__proc_state < 0) 
		|| (dCH__CFG_USE->Check__DATA(STR__YES) < 0))
		{
			dCH__MON_PROC_PRESSURE_CHECK_ACTIVE->Set__DATA(STR__OFF);
			dCH__MON_PROC_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__OFF);	
			dCH__MON_PROC_PRESSURE_ABORT_ACTIVE->Set__DATA(STR__OFF);	

			error__proc_warning.Reset();
			error__proc_abort.Reset();
			continue;
		}

		if(dCH__MON_PROC_PRESSURE_CHECK_ACTIVE->Check__DATA(STR__READY) > 0)
		{
			dCH__MON_PROC_PRESSURE_CHECK_ACTIVE->Set__DATA(STR__ON);

			//
			error__proc_warning.Reset();
			error__proc_abort.Reset();
		}

		// ...
		int active__error_check = dCH__MON_PROC_PRESSURE_CHECK_ACTIVE->Check__DATA(STR__ON);

		// Warning Check ...
		{
			CClass__Error_Timer* p_error = &error__proc_warning;

			if(p_error->Check__Error_State())
			{
				if(active__error_check > 0)
				{
					int alarm_id = ALID__VAT__CONTROL_WARNING_RANGE;
					CString r_act;

					str_msg  = "Process warning range check ... \n\n";
					str_msg += Get__ERROR_MSG(p_error);

					p_alarm->Check__ALARM(alarm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id, str_msg);
				}
			}
		}

		// Abort Check ...
		if(active__error_check > 0)
		{
			CClass__Error_Timer* p_error = &error__proc_abort;

			if(p_error->Check__Error_State())
			{
				if(active__error_check > 0)
				{
					dCH__MON_PROC_PRESSURE_ABORT_ACTIVE->Set__DATA(STR__ON);

					// ...
					int alarm_id = ALID__VAT__CONTROL_ABORT_RANGE;
					CString r_act;

					str_msg  = "Process abort range Check ... \n\n";
					str_msg += Get__ERROR_MSG(p_error);

					p_alarm->Check__ALARM(alarm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id, str_msg);
				}
			}
		}

		// Stable Check ...
		if(active__error_check > 0)
		{
			if((error__proc_warning.IsStable())
			&& (error__proc_abort.IsStable()))
			{
				dCH__MON_PROC_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__ON);	
				dCH__MON_PROC_PRESSURE_ABORT_ACTIVE->Set__DATA(STR__OFF);
			}
			else
			{
				dCH__MON_PROC_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__OFF);	
			}
		}
		else
		{
			dCH__MON_PROC_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__OFF);	
		}
	}

	return 1;
}

