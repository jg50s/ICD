#include "StdAfx.h"
#include "CObj__PT_IO.h"


// ...
int  CObj__PT_IO
::Mon__PT_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	// PT Check ...
	CClass__Error_Timer error__pt_warning_x[_CFG__PT_MAX];
	CClass__Error_Timer error__pt_abort_x[_CFG__PT_MAX];
	int i;

	// Warning ...
	for(i=0; i<iPT_SIZE; i++)
	{
		CLink__Error_Common x_link_common;

		// ...
		{
			x_link_common.pCH__CFG_USE = dCH__CFG_USE__PT_X[i].Get__PTR();
			x_link_common.pCH__ACTIVE_CHECK = dCH__MON_ERROR_CHECK_ACTIVE__PT_X[i].Get__PTR();

			x_link_common.pCH__CFG_STABLE_CHECK_SEC = aCH__CFG_STABLE_CHECK_TIMEOUT__PT_X[i].Get__PTR();
			x_link_common.pCH__CUR_STABLE_CHECK_SEC = sCH__MON_STABLE_CHECK_TIME__PT_X[i].Get__PTR();

			x_link_common.pCH__CUR_ERROR_MIN = sCH__MON_WARNING_MIN__PT_X[i].Get__PTR();
			x_link_common.pCH__CUR_ERROR_MAX = sCH__MON_WARNING_MAX__PT_X[i].Get__PTR();
		}

		// ...
		error__pt_warning_x[i].Disable__MAX_RANGE();
		error__pt_warning_x[i].Enable__ERROR_THRESHOLD();

		error__pt_warning_x[i].Link__REF_OUT_CHANNEL(aCH__CFG_SETPOINT__PT_X[i]);
		error__pt_warning_x[i].Link__REF_IN_CHANNEL(aEXT_CH__AI_PT_PRESSURE_X[i]);

		error__pt_warning_x[i].Link__ERROR_COMMON(&x_link_common);

		// ...
		CLink__Error_Para x_link_para;

		x_link_para.pCH__CFG_TOLERANCE_DATA_PERCENT = aCH__CFG_SOFT_TOLERANCE_THRESHOLD__PT_X[i].Get__PTR();

		x_link_para.pCH__CFG_ERROR_CHECK_SEC = aCH__CFG_SOFT_TOLERANCE_TIMEOUT__PT_X[i].Get__PTR();
		x_link_para.pCH__CUR_ERROR_CHECK_SEC = sCH__MON_WARNING_CHECK_TIME__PT_X[i].Get__PTR();

		error__pt_warning_x[i].Link__ERROR_PARA(&x_link_para);
	}

	// Abort ...
	for(i=0; i<iPT_SIZE; i++)
	{
		CLink__Error_Common x_link_common;

		// ...
		{
			x_link_common.pCH__CFG_USE = dCH__CFG_USE__PT_X[i].Get__PTR();
			x_link_common.pCH__ACTIVE_CHECK = dCH__MON_ERROR_CHECK_ACTIVE__PT_X[i].Get__PTR();

			x_link_common.pCH__CUR_ERROR_MIN = sCH__MON_ABORT_MIN__PT_X[i].Get__PTR();
			x_link_common.pCH__CUR_ERROR_MAX = sCH__MON_ABORT_MAX__PT_X[i].Get__PTR();
		}

		// ...
		error__pt_abort_x[i].Disable__MAX_RANGE();
		error__pt_abort_x[i].Enable__ERROR_THRESHOLD();

		error__pt_abort_x[i].Link__REF_OUT_CHANNEL(aCH__CFG_SETPOINT__PT_X[i]);
		error__pt_abort_x[i].Link__REF_IN_CHANNEL(aEXT_CH__AI_PT_PRESSURE_X[i]);

		error__pt_abort_x[i].Link__ERROR_COMMON(&x_link_common);

		// ...
		CLink__Error_Para x_link_para;

		x_link_para.pCH__CFG_TOLERANCE_DATA_PERCENT = aCH__CFG_HARD_TOLERANCE_THRESHOLD__PT_X[i].Get__PTR();

		x_link_para.pCH__CFG_ERROR_CHECK_SEC = aCH__CFG_HARD_TOLERANCE_TIMEOUT__PT_X[i].Get__PTR();
		x_link_para.pCH__CUR_ERROR_CHECK_SEC = sCH__MON_ABORT_CHECK_TIME__PT_X[i].Get__PTR();

		error__pt_abort_x[i].Link__ERROR_PARA(&x_link_para);
	}

	// Init ...
	for(i=0; i<iPT_SIZE; i++)
	{
		error__pt_warning_x[i].Init();
		error__pt_abort_x[i].Init();
	}

	// ...
	CString str_msg;
	CString str_bff;

	double inc_sec = 0.1;

	for(i=0; i<iPT_SIZE; i++)
	{
		dCH__MON_ERROR_CHECK_ACTIVE__PT_X[i]->Set__DATA(STR__READY);
	}

	// Stable Time ...
	{
		Sleep(500);
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(inc_sec);

		//
		for(i=0; i<iPT_SIZE; i++)
		{
			if(dCH__CFG_USE__PT_X[i]->Check__DATA(STR__YES) < 0)
			{
				if(iActive__SIM_MODE > 0)
				{
					aEXT_CH__AI_PT_PRESSURE_X[i]->Set__DATA("0");
				}

				dCH__MON_ERROR_CHECK_ACTIVE__PT_X[i]->Set__DATA(STR__OFF);
				dCH__MON_STABLE_ACTIVE__PT_X[i]->Set__DATA(STR__OFF);	
				dCH__MON_ABORT_ACTIVE__PT_X[i]->Set__DATA(STR__OFF);	
				continue;
			}
			else
			{
				if(dCH__MON_ERROR_CHECK_ACTIVE__PT_X[i]->Check__DATA(STR__OFF) > 0)
				{
					dCH__MON_ERROR_CHECK_ACTIVE__PT_X[i]->Set__DATA(STR__READY);
				}
			}

			if(dCH__MON_ERROR_CHECK_ACTIVE__PT_X[i]->Check__DATA(STR__READY) > 0)
			{
				dCH__MON_ERROR_CHECK_ACTIVE__PT_X[i]->Set__DATA(STR__ON);

				if(iActive__SIM_MODE > 0)
				{
					CString ch_data;

					aCH__CFG_SETPOINT__PT_X[i]->Get__DATA(ch_data);
					aEXT_CH__AI_PT_PRESSURE_X[i]->Set__DATA(ch_data);

					printf(" * PT%1d : ch_Data <- %s \n", i+1,ch_data);
				}

				// Reset ...
				{
					error__pt_warning_x[i].Reset();
					error__pt_abort_x[i].Reset();
				}
			}

			// ...
			int active__error_check = dCH__MON_ERROR_CHECK_ACTIVE__PT_X[i]->Check__DATA(STR__ON);

			// Warning Check ...
			{
				CClass__Error_Timer* p_error = &(error__pt_warning_x[i]);

				if(p_error->Check__Error_State())
				{
					if(active__error_check > 0)
					{
						CString pt_name = sCH__CFG_NAME__PT_X[i]->Get__STRING();

						int alm_id = ALID__PRESSURE_TRANSMITTER__THRESHOLD_WARNING + i;
						CString alm_msg;
						CString r_act;

						alm_msg = Get__PT_MSG(pt_name, p_error);

						p_alarm->Check__ALARM(alm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					}
				}
			}

			// Abort Check ...
			{
				CClass__Error_Timer* p_error = &(error__pt_abort_x[i]);

				if(p_error->Check__Error_State())
				{
					if(active__error_check > 0)
					{
						dCH__MON_ABORT_ACTIVE__PT_X[i]->Set__DATA(STR__ON);

						// ...
						CString pt_name = sCH__CFG_NAME__PT_X[i]->Get__STRING();

						int alm_id = ALID__PRESSURE_TRANSMITTER__THRESHOLD_ABORT + i;
						CString alm_msg;
						CString r_act;

						alm_msg = Get__PT_MSG(pt_name, p_error);

						p_alarm->Check__ALARM(alm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					}
				}
			}

			// Stable Check ...
			if(active__error_check > 0)
			{
				if((error__pt_warning_x[i].IsStable())
				&& (error__pt_abort_x[i].IsStable()))
				{
					dCH__MON_STABLE_ACTIVE__PT_X[i]->Set__DATA(STR__ON);	
					dCH__MON_ABORT_ACTIVE__PT_X[i]->Set__DATA(STR__OFF);
				}
				else
				{
					dCH__MON_STABLE_ACTIVE__PT_X[i]->Set__DATA(STR__OFF);	
				}
			}
			else
			{
				dCH__MON_STABLE_ACTIVE__PT_X[i]->Set__DATA(STR__OFF);
			}
		}

		// ...
	}

	return 1;
}

CString CObj__PT_IO
::Get__PT_MSG(const CString& pt_name, CClass__Error_Timer* p_error)
{
	CClass__Error_Report x_report;
	p_error->Get__ERROR_REPORT(&x_report);

	// ...
	CString str_msg;
	CString str_bff;

	str_bff.Format("PT Name : %s \n", pt_name);
	str_msg += str_bff;

	str_bff.Format("Current pressure : %.f \n", x_report.dCUrrent_VALUE);
	str_msg += str_bff;

	str_bff.Format("Setpoint pressure : %.f \n", x_report.dSet_VALUE);
	str_msg += str_bff;

	double dif_pressure = fabs(x_report.dCUrrent_VALUE - x_report.dSet_VALUE);

	str_bff.Format("Diff-pressure : %.f \n", dif_pressure);
	str_msg += str_bff;

	str_bff.Format("Config-Threshold : %.f \n", x_report.dError_THRESHOLD);
	str_msg += str_bff;

	str_bff.Format("Config-Timeout : %.0f \n", x_report.dError_SEC);
	str_msg += str_bff;


	return str_msg;
}
