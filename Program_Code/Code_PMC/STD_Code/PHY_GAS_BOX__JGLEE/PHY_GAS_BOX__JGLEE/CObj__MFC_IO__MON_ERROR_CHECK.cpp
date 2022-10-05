#include "StdAfx.h"
#include "CObj__MFC_IO.h"


// ...
int  CObj__MFC_IO
::Mon__ERROR_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	CString str_msg;
	CString str_bff;


	// MFC.Flow ...
	CClass__Error_Timer error__proc_warning;
	CClass__Error_Timer error__idle_warning;

	CClass__Error_Timer error__proc_abort;
	CClass__Error_Timer error__idle_abort;

	// Range.Warning ...
	{
		CLink__Error_Common x_link_common;

		// ...
		{
			x_link_common.pCH__CFG_USE = dCH__CFG_MFC_USE.Get__PTR();
			x_link_common.pCH__ACTIVE_CHECK = dCH__MON_ERROR_CHECK_ACTIVE.Get__PTR();

			x_link_common.pCH__CFG_STABLE_DELAY_SEC = aCH__CFG_STABLE_DELAY_TIME.Get__PTR();
			x_link_common.pCH__CUR_STABLE_DELAY_SEC = sCH__MON_MFC_STABLE_DELAY_TIME.Get__PTR();

			x_link_common.pCH__CFG_STABLE_CHECK_SEC = aCH__CFG_STABLE_CHECK_TIME.Get__PTR();
			x_link_common.pCH__CUR_STABLE_CHECK_SEC = sCH__MON_MFC_STABLE_CHECK_TIME.Get__PTR();

			x_link_common.pCH__CUR_STABLE_MIN = sCH__MON_MFC_STABLE_MIN.Get__PTR();
			x_link_common.pCH__CUR_STABLE_MAX = sCH__MON_MFC_STABLE_MAX.Get__PTR();

			x_link_common.pCH__CFG_TOLERANCE_ZERO_PERCENT = aCH__CFG_MFC_Zero_Setpoint_Tolerance_Compensation.Get__PTR();	
		}

		// Proc ...
		{
			error__proc_warning.Disable__MAX_RANGE();

			error__proc_warning.Link__REF_OUT_CHANNEL(aCH__MON_MFC_SET_FLOW);
			error__proc_warning.Link__REF_IN_CHANNEL(aCH__MON_MFC_READ_FLOW);
			error__proc_warning.Link__REF_RANGE_CHANNEL(aCH__MON_MFC_SET_FLOW);

			error__proc_warning.Link__ERROR_COMMON(&x_link_common);

			// ...
			CLink__Error_Para x_link_para;

			x_link_para.pCH__CFG_STABLE_DATA_PERCENT    = aCH__CFG_WARN_BAND.Get__PTR();
			x_link_para.pCH__CFG_TOLERANCE_DATA_PERCENT = aCH__CFG_WARN_BAND.Get__PTR();

			x_link_para.pCH__CFG_ERROR_CHECK_SEC  = aCH__CFG_TOL_WARN_TIMEOUT.Get__PTR();
			x_link_para.pCH__CUR_ERROR_CHECK_SEC  = sCH__MON_MFC_WARNING_CHECK_TIME.Get__PTR();

			error__proc_warning.Link__ERROR_PARA(&x_link_para);
		}
		// Idle ...
		{
			error__idle_warning.Disable__MAX_RANGE();

			error__idle_warning.Link__REF_OUT_CHANNEL(aCH__MON_MFC_SET_FLOW);
			error__idle_warning.Link__REF_IN_CHANNEL(aCH__MON_MFC_READ_FLOW);
			error__idle_warning.Link__REF_RANGE_CHANNEL(aCH__MON_MFC_SET_FLOW);

			error__idle_warning.Link__ERROR_COMMON(&x_link_common);

			// ...
			CLink__Error_Para x_link_para;

			x_link_para.pCH__CFG_STABLE_DATA_PERCENT    = aCH__CFG_IDLE_WARN_BAND.Get__PTR();
			x_link_para.pCH__CFG_TOLERANCE_DATA_PERCENT = aCH__CFG_IDLE_WARN_BAND.Get__PTR();

			x_link_para.pCH__CFG_ERROR_CHECK_SEC = aCH__CFG_TOL_WARN_TIMEOUT.Get__PTR();
			x_link_para.pCH__CUR_ERROR_CHECK_SEC = sCH__MON_MFC_WARNING_CHECK_TIME.Get__PTR();

			error__idle_warning.Link__ERROR_PARA(&x_link_para);
		}
	}
	// Range.Abort ...
	{
		CLink__Error_Common x_link_common;

		// ...
		{
			x_link_common.pCH__CFG_USE = dCH__CFG_MFC_USE.Get__PTR();
			x_link_common.pCH__ACTIVE_CHECK = dCH__MON_ERROR_CHECK_ACTIVE.Get__PTR();

			x_link_common.pCH__CFG_STABLE_DELAY_SEC = aCH__CFG_STABLE_DELAY_TIME.Get__PTR();

			x_link_common.pCH__CUR_STABLE_MIN = sCH__MON_MFC_ABORT_MIN.Get__PTR();
			x_link_common.pCH__CUR_STABLE_MAX = sCH__MON_MFC_ABORT_MAX.Get__PTR();

			x_link_common.pCH__CFG_TOLERANCE_ZERO_PERCENT = aCH__CFG_MFC_Zero_Setpoint_Tolerance_Compensation.Get__PTR();	
		}

		// Proc ...
		{
			error__proc_abort.Disable__MAX_RANGE();

			error__proc_abort.Link__REF_OUT_CHANNEL(aCH__MON_MFC_SET_FLOW);
			error__proc_abort.Link__REF_IN_CHANNEL(aCH__MON_MFC_READ_FLOW);
			error__proc_abort.Link__REF_RANGE_CHANNEL(aCH__MON_MFC_SET_FLOW);

			error__proc_abort.Link__ERROR_COMMON(&x_link_common);

			// ...
			CLink__Error_Para x_link_para;

			x_link_para.pCH__CFG_STABLE_DATA_PERCENT    = aCH__CFG_WARN_BAND.Get__PTR();
			x_link_para.pCH__CFG_TOLERANCE_DATA_PERCENT = aCH__CFG_ABORT_BAND.Get__PTR();

			x_link_para.pCH__CFG_ERROR_CHECK_SEC = aCH__CFG_TOL_ABORT_TIMEOUT.Get__PTR();
			x_link_para.pCH__CUR_ERROR_CHECK_SEC = sCH__MON_MFC_ABORT_CHECK_TIME.Get__PTR();

			error__proc_abort.Link__ERROR_PARA(&x_link_para);
		}
		// Idle ...
		{
			error__idle_abort.Disable__MAX_RANGE();

			error__idle_abort.Link__REF_OUT_CHANNEL(aCH__MON_MFC_SET_FLOW);
			error__idle_abort.Link__REF_IN_CHANNEL(aCH__MON_MFC_READ_FLOW);
			error__idle_abort.Link__REF_RANGE_CHANNEL(aCH__MON_MFC_SET_FLOW);

			error__idle_abort.Link__ERROR_COMMON(&x_link_common);

			// ...
			CLink__Error_Para x_link_para;

			x_link_para.pCH__CFG_STABLE_DATA_PERCENT    = aCH__CFG_IDLE_WARN_BAND.Get__PTR();
			x_link_para.pCH__CFG_TOLERANCE_DATA_PERCENT = aCH__CFG_IDLE_ABORT_BAND.Get__PTR();

			x_link_para.pCH__CFG_ERROR_CHECK_SEC = aCH__CFG_TOL_ABORT_TIMEOUT.Get__PTR();
			x_link_para.pCH__CUR_ERROR_CHECK_SEC = sCH__MON_MFC_ABORT_CHECK_TIME.Get__PTR();

			error__idle_abort.Link__ERROR_PARA(&x_link_para);
		}
	}
	// ...
	{
		error__proc_warning.Init();
		error__idle_warning.Init();

		error__proc_abort.Init();
		error__idle_abort.Init();
	}

	double inc_sec = 0.1;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(inc_sec);


		// ...
		bool active__check_skip = false;

		if(dEXT_CH__CFG_PMC_ATM_MAINT_ACTIVE->Check__DATA(STR__ON) > 0)	
		{
			active__check_skip = true;

			_Close__ALL_VALVE();
		}
		if(dCH__CFG_MFC_USE->Check__DATA(STR__YES) < 0)
		{
			active__check_skip = true;
		}

		if(active__check_skip)
		{
			dCH__MON_ERROR_CHECK_ACTIVE->Set__DATA(STR__OFF);
			dCH__MON_MFC_STABLE_ACTIVE->Set__DATA(STR__OFF);	
			dCH__MON_MFC_ABORT_ACTIVE->Set__DATA(STR__OFF);	

			continue;
		}

		if(dCH__MON_ERROR_CHECK_ACTIVE->Check__DATA(STR__READY) > 0)
		{
			dCH__MON_ERROR_CHECK_ACTIVE->Set__DATA(STR__ON);

			// Reset ...
			{
				error__proc_warning.Reset();
				error__idle_warning.Reset();

				error__proc_abort.Reset();
				error__idle_abort.Reset();
			}
		}

		// ...
		CString gas_name = sCH__CFG_GAS_NAME->Get__STRING();

		int active__error_check = dCH__MON_ERROR_CHECK_ACTIVE->Check__DATA(STR__ON);
		int active__proc_state  = dEXT_CH__MON_SYSTEM_PROCESS_ACTIVE->Check__DATA(STR__ON);

		// Warning Check ...
		{
			if(active__proc_state > 0)   // Process State ...
			{
				CClass__Error_Timer* p_error = &error__proc_warning;

				if(p_error->Check__Error_State())
				{
					if(active__error_check > 0)
					{
						int alarm_id = ALID__MFC_FLOW__CONTROL_WARNING_RANGE;
						CString r_act;

						// ...
						{
							str_msg  = "Process warning range check ... \n\n";

							str_bff.Format("When processing, gas_name [%s] \n", gas_name);
							str_msg += str_bff;

							str_msg += Get__ERROR_MSG(p_error);
						}

						p_alarm->Check__ALARM(alarm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alarm_id, str_msg);
					}
				}

				dCH__MON_MFC_PROC_ACTIVE->Set__DATA(STR__ON);
			}
			else   // Idle State ...
			{
				CClass__Error_Timer* p_error = &error__idle_warning;

				if(p_error->Check__Error_State())
				{
					if(active__error_check > 0)
					{
						int alarm_id = ALID__MFC_FLOW__CONTROL_IDLE_WARNING_RANGE;
						CString r_act;

						// ...
						{
							str_msg  = "Idle warning range check ... \n\n";

							str_bff.Format("When Idle, gas_name [%s] \n", gas_name);
							str_msg += str_bff;

							str_msg += Get__ERROR_MSG(p_error);
						}

						p_alarm->Check__ALARM(alarm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alarm_id, str_msg);
					}
				}

				dCH__MON_MFC_PROC_ACTIVE->Set__DATA(STR__OFF);
			}
		}

		// Abort Check ...
		{
			if(active__proc_state > 0)   // Process State ...
			{
				CClass__Error_Timer* p_error = &error__proc_abort;

				if(p_error->Check__Error_State())
				{
					if(active__error_check > 0)
					{
						dCH__MON_MFC_ABORT_ACTIVE->Set__DATA(STR__ON);

						// ...
						int alarm_id = ALID__MFC_FLOW__CONTROL_ABORT_RANGE;
						CString r_act;

						// ...
						{
							str_msg  = "Process Abort Range Check ... \n\n";

							str_bff.Format("When processing, gas_name [%s] \n", gas_name);
							str_msg += str_bff;

							str_msg += Get__ERROR_MSG(p_error);
						}

						p_alarm->Check__ALARM(alarm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alarm_id, str_msg);

						if(dCH__CFG_ABORT_TOLE_VALVE_CLOSE->Check__DATA(STR__YES) > 0)
						{
							Fnc__CONTROL(0, -1, 0);
						}
					}
				}
			}
			else   // Idle State ...
			{
				CClass__Error_Timer* p_error = &error__idle_abort;

				if(p_error->Check__Error_State())
				{
					if(active__error_check > 0)
					{
						dCH__MON_MFC_ABORT_ACTIVE->Set__DATA(STR__ON);

						// ...
						int alarm_id = ALID__MFC_FLOW__CONTROL_IDLE_ABORT_RANGE;
						CString r_act;

						// ...
						{
							str_msg  = "Idle Abort Range Check ... \n\n";

							str_bff.Format("When Idle, gas_name [%s] \n", gas_name);
							str_msg += str_bff;

							str_msg += Get__ERROR_MSG(p_error);
						}

						p_alarm->Check__ALARM(alarm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alarm_id, str_msg);

						if(dCH__CFG_ABORT_TOLE_VALVE_CLOSE->Check__DATA(STR__YES) > 0)
						{
							Fnc__CONTROL(0, -1, 0);
						}
					}
				}
			}
		}

		// Stable Check ...
		if(active__error_check > 0)
		{
			if(active__proc_state > 0)
			{
				if((error__proc_warning.IsStable())
				&& (error__proc_abort.IsStable()))
				{
					dCH__MON_MFC_STABLE_ACTIVE->Set__DATA(STR__ON);	
					dCH__MON_MFC_ABORT_ACTIVE->Set__DATA(STR__OFF);
				}
				else
				{
					dCH__MON_MFC_STABLE_ACTIVE->Set__DATA(STR__OFF);	
				}
			}
			else
			{
				if((error__idle_warning.IsStable())
				&& (error__idle_abort.IsStable()))
				{
					dCH__MON_MFC_STABLE_ACTIVE->Set__DATA(STR__ON);	
				}
				else
				{
					dCH__MON_MFC_STABLE_ACTIVE->Set__DATA(STR__OFF);	
				}
			}
		}
		else
		{
			dCH__MON_MFC_STABLE_ACTIVE->Set__DATA(STR__OFF);
		}

		// ...
	}

	return 1;
}

CString CObj__MFC_IO
::Get__ERROR_MSG(CClass__Error_Timer* p_error)
{
	CClass__Error_Report x_report;
	p_error->Get__ERROR_REPORT(&x_report);

	CString str_unit = dCH__CFG_RANGE_MFC_UNIT->Get__STRING();

	// ...
	CString str_msg;
	CString str_bff;

	str_bff.Format(" * MFC range <- (%.2f, %.2f) \n",
					x_report.dRange_MIN,
					x_report.dRange_MAX);
	str_msg += str_bff;

	str_bff.Format(" * Set.flow <- [%.2f] %s. \n", 
					x_report.dSet_VALUE,
					str_unit);
	str_msg += str_bff;

	str_bff.Format(" * Config abort.band <- [%.2f] %% \n", 
					x_report.dError_PERCENT);
	str_msg += str_bff;

	str_bff.Format(" * Checking time <- [%.f] sec \n\n", 
					x_report.dError_SEC);
	str_msg += str_bff;

	str_bff.Format(" * So, valid range is [%.2f] %s < current flow < [%.2f] %s. \n", 
					x_report.dError_MIN,
					str_unit,
					x_report.dError_MAX,
					str_unit);
	str_msg += str_bff;

	str_bff.Format(" * But, current flow is [%.2f] %s. \n", 
					x_report.dCUrrent_VALUE,
					str_unit);
	str_msg += str_bff;

	return str_msg;
}
