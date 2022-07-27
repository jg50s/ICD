#include "StdAfx.h"
#include "CObj__VAT_IO.h"
#include "CObj__VAT_IO__ALID.h"


// ...
int  CObj__VAT_IO
::Mon__IDLE_ERROR_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CClass__Error_Timer error__idle_warning;
	CClass__Error_Timer error__idle_abort;

	CString ch_data;

	CString str_msg;
	CString str_bff;


	// Range.Warning ...
	{
		CLink__Error_Common x_link_common;

		// ...
		{
			x_link_common.pCH__CFG_USE = dCH__CFG_USE.Get__PTR();
			x_link_common.pCH__ACTIVE_CHECK = dCH__MON_IDLE_PRESSURE_CHECK_ACTIVE.Get__PTR();

			x_link_common.pCH__CFG_STABLE_DELAY_SEC = aCH__CFG_PRESSURE_STABLE_DELAY_TIME.Get__PTR();
			x_link_common.pCH__CUR_STABLE_DELAY_SEC = sCH__MON_IDLE_PRESSURE_STABLE_DELAY_TIME.Get__PTR();

			x_link_common.pCH__CFG_STABLE_CHECK_SEC = aCH__CFG_PRESSURE_STABLE_CHECK_TIME.Get__PTR();
			x_link_common.pCH__CUR_STABLE_CHECK_SEC = sCH__MON_IDLE_PRESSURE_STABLE_CHECK_TIME.Get__PTR();

			x_link_common.pCH__CUR_ERROR_MIN = sCH__MON_IDLE_PRESSURE_STABLE_MIN.Get__PTR();
			x_link_common.pCH__CUR_ERROR_MAX = sCH__MON_IDLE_PRESSURE_STABLE_MAX.Get__PTR();

			x_link_common.pCH__CFG_TOLERANCE_ZERO_PERCENT = aCH__CFG_Zero_Setpoint_Tolerance_Compensation.Get__PTR();	
		}

		// Idle ...
		{
			error__idle_warning.Disable__MAX_RANGE();

			error__idle_warning.Link__REF_OUT_CHANNEL(sCH__MON_SET_PRESSURE_TORR);
			error__idle_warning.Link__REF_IN_CHANNEL(sCH__MON_PRESSURE_TORR);
			error__idle_warning.Link__REF_RANGE_CHANNEL(aCH__PARA_PRESSURE);

			error__idle_warning.Link__ERROR_COMMON(&x_link_common);

			// ...
			CLink__Error_Para x_link_para;

			x_link_para.pCH__CFG_STABLE_DATA_PERCENT    = aCH__CFG_IDLE_PRESSURE_WARNING_BAND.Get__PTR();
			x_link_para.pCH__CFG_TOLERANCE_DATA_PERCENT = aCH__CFG_IDLE_PRESSURE_WARNING_BAND.Get__PTR();
			x_link_para.pCH__CFG_ERROR_CHECK_SEC        = aCH__CFG_PRESSURE_WARNING_TIMEOUT.Get__PTR();
			x_link_para.pCH__CUR_ERROR_CHECK_SEC        = sCH__MON_IDLE_PRESSURE_WARNING_CHECK_TIME.Get__PTR();

			error__idle_warning.Link__ERROR_PARA(&x_link_para);
		}
	}
	// Range.Abort ...
	{
		CLink__Error_Common x_link_common;

		// ...
		{
			x_link_common.pCH__CFG_USE = dCH__CFG_USE.Get__PTR();
			x_link_common.pCH__ACTIVE_CHECK = dCH__MON_IDLE_PRESSURE_CHECK_ACTIVE.Get__PTR();

			x_link_common.pCH__CFG_STABLE_DELAY_SEC = aCH__CFG_PRESSURE_STABLE_DELAY_TIME.Get__PTR();
			x_link_common.pCH__CFG_STABLE_CHECK_SEC = aCH__CFG_PRESSURE_STABLE_CHECK_TIME.Get__PTR();

			x_link_common.pCH__CUR_ERROR_MIN = sCH__MON_IDLE_PRESSURE_ABORT_MIN.Get__PTR();
			x_link_common.pCH__CUR_ERROR_MAX = sCH__MON_IDLE_PRESSURE_ABORT_MAX.Get__PTR();
		}

		// Idle ...
		{
			error__idle_abort.Disable__MAX_RANGE();

			error__idle_abort.Link__REF_OUT_CHANNEL(sCH__MON_SET_PRESSURE_TORR);
			error__idle_abort.Link__REF_IN_CHANNEL(sCH__MON_PRESSURE_TORR);
			error__idle_abort.Link__REF_RANGE_CHANNEL(aCH__PARA_PRESSURE);

			error__idle_abort.Link__ERROR_COMMON(&x_link_common);

			// ...
			CLink__Error_Para x_link_para;

			x_link_para.pCH__CFG_STABLE_DATA_PERCENT    = aCH__CFG_IDLE_PRESSURE_WARNING_BAND.Get__PTR();
			x_link_para.pCH__CFG_TOLERANCE_DATA_PERCENT = aCH__CFG_IDLE_PRESSURE_ABORT_BAND.Get__PTR();
			x_link_para.pCH__CFG_ERROR_CHECK_SEC        = aCH__CFG_PRESSURE_ABORT_TIMEOUT.Get__PTR();
			x_link_para.pCH__CUR_ERROR_CHECK_SEC        = sCH__MON_IDLE_PRESSURE_ABORT_CHECK_TIME.Get__PTR();

			error__idle_abort.Link__ERROR_PARA(&x_link_para);
		}
	}

	// Timer.Init ...
	{
		error__idle_warning.Init();
		error__idle_abort.Init();
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(dCH__CFG_USE->Check__DATA(STR__YES) < 0)
		{
			dCH__MON_IDLE_PRESSURE_CHECK_ACTIVE->Set__DATA(STR__OFF);
			dCH__MON_IDLE_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__OFF);	
			dCH__MON_IDLE_PRESSURE_ABORT_ACTIVE->Set__DATA(STR__OFF);	
			continue;
		}

		if(dCH__MON_IDLE_PRESSURE_CHECK_ACTIVE->Check__DATA(STR__READY) > 0)
		{
			dCH__MON_IDLE_PRESSURE_CHECK_ACTIVE->Set__DATA(STR__ON);

			//
			error__idle_warning.Reset();
			error__idle_abort.Reset();
		}

		// ...
		int active__error_check = dCH__MON_IDLE_PRESSURE_CHECK_ACTIVE->Check__DATA(STR__ON);

		// Warning Check ...
		{
			CClass__Error_Timer* p_error = &error__idle_warning;

			if(p_error->Check__Error_State())
			{
				if(active__error_check > 0)
				{
					int alarm_id = ALID__VAT__CONTROL_IDLE_WARNING_RANGE;
					CString r_act;

					str_msg  = "Idle warning range check ... \n\n";
					str_msg += Get__ERROR_MSG(p_error);

					p_alarm->Check__ALARM(alarm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id, str_msg);
				}
			}
		}

		// Abort Check ...
		if(active__error_check > 0)
		{
			CClass__Error_Timer* p_error = &error__idle_abort;

			if(p_error->Check__Error_State())
			{
				if(active__error_check > 0)
				{
					dCH__MON_IDLE_PRESSURE_ABORT_ACTIVE->Set__DATA(STR__ON);

					// ...
					int alarm_id = ALID__VAT__CONTROL_IDLE_ABORT_RANGE;
					CString r_act;

					str_msg  = "Idle abort range check ... \n\n";
					str_msg += Get__ERROR_MSG(p_error);

					p_alarm->Check__ALARM(alarm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id, str_msg);
				}
			}
		}

		// Stable Check ...
		if(active__error_check > 0)
		{
			if((error__idle_warning.IsStable())
			&& (error__idle_abort.IsStable()))
			{
				dCH__MON_IDLE_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__ON);	
				dCH__MON_IDLE_PRESSURE_ABORT_ACTIVE->Set__DATA(STR__OFF);
			}
			else
			{
				dCH__MON_IDLE_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__OFF);	
			}
		}
		else
		{
			dCH__MON_IDLE_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__OFF);	
		}
	}

	return 1;
}

CString CObj__VAT_IO
::Get__ERROR_MSG(CClass__Error_Timer* p_error)
{
	CClass__Error_Report x_report;
	p_error->Get__ERROR_REPORT(&x_report);

	// ...
	CString str_msg;
	CString str_bff;

	str_bff.Format(" * Pressure range <- (%.3f, %.3f) \n",
					x_report.dRange_MIN,
					x_report.dRange_MAX);
	str_msg += str_bff;

	str_bff.Format(" * Set.pressure <- [%.3f] torr \n", 
					x_report.dSet_VALUE);
	str_msg += str_bff;

	str_bff.Format(" * Config abort.band <- [%.2f] %% \n", 
					x_report.dError_PERCENT);
	str_msg += str_bff;

	str_bff.Format(" * Checking time <- [%.0f] sec \n\n", 
					x_report.dError_SEC);
	str_msg += str_bff;

	str_bff.Format(" * So, valid range is [%.3f] torr < current pressure < [%.3f] torr. \n", 
					x_report.dError_MIN,
					x_report.dError_MAX);
	str_msg += str_bff;

	str_bff.Format(" * But, current pressure is [%.3f] torr. \n", 
					x_report.dCUrrent_VALUE);
	str_msg += str_bff;

	return str_msg;
}

