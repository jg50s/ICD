#include "StdAfx.h"
#include "CObj__MINI8_IO.h"
#include "CObj__MINI8_IO__ALID.h"


// ...
int  CObj__MINI8_IO
::Mon__PROC_ERROR_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	// PT Check ...
	CClass__Error_Timer error__pt_warning_x[CFG__LOOP_SIZE];
	CClass__Error_Timer error__pt_abort_x[CFG__LOOP_SIZE];
	int i;

	// Soft.Tolerance ...
	for(i=0; i<iLOOP_SIZE; i++)
	{
		CLink__Error_Common x_link_common;

		// ...
		{
			x_link_common.pCH__CFG_USE = dCH__CFG_USE__LOOP_X[i].Get__PTR();
			x_link_common.pCH__ACTIVE_CHECK = dCH__MON_PROC_ERROR_CHECK_ACTIVE__LOOP_X[i].Get__PTR();

			x_link_common.pCH__CFG_STABLE_CHECK_SEC = aCH__CFG_STABLE_CHECK_TIMEOUT__LOOP_X[i].Get__PTR();
			x_link_common.pCH__CUR_STABLE_CHECK_SEC = sCH__MON_PROC_STABLE_CHECK_TIME__LOOP_X[i].Get__PTR();

			x_link_common.pCH__CFG_STABLE_DELAY_SEC = aCH__CFG_DELAY_CHECK_TIMEOUT__LOOP_X[i].Get__PTR();
			x_link_common.pCH__CUR_STABLE_DELAY_SEC = sCH__MON_PROC_DELAY_CHECK_TIME__LOOP_X[i].Get__PTR();

			x_link_common.pCH__CUR_ERROR_MIN = sCH__MON_PROC_WARNING_MIN__LOOP_X[i].Get__PTR();
			x_link_common.pCH__CUR_ERROR_MAX = sCH__MON_PROC_WARNING_MAX__LOOP_X[i].Get__PTR();
		}

		// ...
		error__pt_warning_x[i].Disable__MAX_RANGE();
		error__pt_warning_x[i].Enable__ERROR_THRESHOLD();

		error__pt_warning_x[i].Link__REF_OUT_CHANNEL(sCH__MON_REF_SET__LOOP_X[i]);
		error__pt_warning_x[i].Link__REF_IN_CHANNEL(sCH__MON_IO_GET_PV__LOOP_X[i]);

		error__pt_warning_x[i].Link__ERROR_COMMON(&x_link_common);

		// ...
		CLink__Error_Para x_link_para;

		x_link_para.pCH__CFG_TOLERANCE_DATA_PERCENT = aCH__CFG_PROC_SOFT_TOLERANCE_THRESHOLD__LOOP_X[i].Get__PTR();

		x_link_para.pCH__CFG_ERROR_CHECK_SEC = aCH__CFG_SOFT_TOLERANCE_TIMEOUT__LOOP_X[i].Get__PTR();
		x_link_para.pCH__CUR_ERROR_CHECK_SEC = sCH__MON_PROC_WARNING_CHECK_TIME__LOOP_X[i].Get__PTR();

		error__pt_warning_x[i].Link__ERROR_PARA(&x_link_para);
	}

	// Hard.Tolerance ...
	for(i=0; i<iLOOP_SIZE; i++)
	{
		CLink__Error_Common x_link_common;

		// ...
		{
			x_link_common.pCH__CFG_USE = dCH__CFG_USE__LOOP_X[i].Get__PTR();
			x_link_common.pCH__ACTIVE_CHECK = dCH__MON_PROC_ERROR_CHECK_ACTIVE__LOOP_X[i].Get__PTR();

			x_link_common.pCH__CFG_STABLE_DELAY_SEC = aCH__CFG_DELAY_CHECK_TIMEOUT__LOOP_X[i].Get__PTR();

			x_link_common.pCH__CUR_ERROR_MIN = sCH__MON_PROC_ABORT_MIN__LOOP_X[i].Get__PTR();
			x_link_common.pCH__CUR_ERROR_MAX = sCH__MON_PROC_ABORT_MAX__LOOP_X[i].Get__PTR();
		}

		// ...
		error__pt_abort_x[i].Disable__MAX_RANGE();
		error__pt_abort_x[i].Enable__ERROR_THRESHOLD();

		error__pt_abort_x[i].Link__REF_OUT_CHANNEL(sCH__MON_REF_SET__LOOP_X[i]);
		error__pt_abort_x[i].Link__REF_IN_CHANNEL(sCH__MON_IO_GET_PV__LOOP_X[i]);

		error__pt_abort_x[i].Link__ERROR_COMMON(&x_link_common);

		// ...
		CLink__Error_Para x_link_para;

		x_link_para.pCH__CFG_TOLERANCE_DATA_PERCENT = aCH__CFG_PROC_HARD_TOLERANCE_THRESHOLD__LOOP_X[i].Get__PTR();

		x_link_para.pCH__CFG_ERROR_CHECK_SEC = aCH__CFG_HARD_TOLERANCE_TIMEOUT__LOOP_X[i].Get__PTR();
		x_link_para.pCH__CUR_ERROR_CHECK_SEC = sCH__MON_PROC_ABORT_CHECK_TIME__LOOP_X[i].Get__PTR();

		error__pt_abort_x[i].Link__ERROR_PARA(&x_link_para);
	}

	// Init ...
	for(i=0; i<iLOOP_SIZE; i++)
	{
		error__pt_warning_x[i].Init();
		error__pt_abort_x[i].Init();
	}

	// ...
	CString str_msg;
	CString str_bff;

	CString ch_data;

	double inc_sec = 0.1;

	for(i=0; i<iLOOP_SIZE; i++)
	{
		dCH__MON_PROC_ERROR_CHECK_ACTIVE__LOOP_X[i]->Set__DATA(STR__READY);
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(inc_sec);


		// ...
		int active__proc_state = dEXT_CH__MON_SYSTEM_PROCESS_ACTIVE->Check__DATA(STR__ON);

		// Stable.Check ...
		for(i=0; i<iLOOP_SIZE; i++)
		{
			if((active__proc_state < 0)
			|| (dCH__CFG_USE__LOOP_X[i]->Check__DATA(STR__YES) < 0))
			{
				dCH__MON_PROC_ERROR_CHECK_ACTIVE__LOOP_X[i]->Set__DATA(STR__OFF);
				dCH__MON_PROC_STABLE_ACTIVE__LOOP_X[i]->Set__DATA(STR__OFF);	
				dCH__MON_PROC_ABORT_ACTIVE__LOOP_X[i]->Set__DATA(STR__OFF);	

				error__pt_warning_x[i].Reset();
				error__pt_abort_x[i].Reset();
				continue;
			}
			else
			{
				if(dCH__MON_PROC_ERROR_CHECK_ACTIVE__LOOP_X[i]->Check__DATA(STR__OFF) > 0)
				{
					dCH__MON_PROC_ERROR_CHECK_ACTIVE__LOOP_X[i]->Set__DATA(STR__READY);
				}
			}

			if(dCH__MON_PROC_ERROR_CHECK_ACTIVE__LOOP_X[i]->Check__DATA(STR__READY) > 0)
			{
				dCH__MON_PROC_ERROR_CHECK_ACTIVE__LOOP_X[i]->Set__DATA(STR__ON);

				if(iActive__SIM_MODE > 0)
				{
					CString ch_data;

					aCH__MON_IO_SET_SP__LOOP_X[i]->Get__DATA(ch_data);
					sCH__MON_IO_GET_PV__LOOP_X[i]->Set__DATA(ch_data);
				}

				// Reset ...
				{
					error__pt_warning_x[i].Reset();
					error__pt_abort_x[i].Reset();
				}
			}

			// ...
			int active__error_check = dCH__MON_PROC_ERROR_CHECK_ACTIVE__LOOP_X[i]->Check__DATA(STR__ON);

			// Warning Check ...
			{
				CClass__Error_Timer* p_error = &(error__pt_warning_x[i]);

				if(p_error->Check__Error_State())
				{
					if(active__error_check > 0)
					{
						CString loop_name = sCH__CFG_NAME__LOOP_X[i]->Get__STRING();

						int alm_id = ALID__WARNING__LOOP_X + i;
						CString alm_msg;
						CString r_act;

						alm_msg = Get__ERROR_MSG(loop_name, p_error);

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
						dCH__MON_PROC_ABORT_ACTIVE__LOOP_X[i]->Set__DATA(STR__ON);

						// ...
						CString loop_name = sCH__CFG_NAME__LOOP_X[i]->Get__STRING();

						int alm_id = ALID__FAULT__LOOP_X + i;
						CString alm_msg;
						CString r_act;

						alm_msg = Get__ERROR_MSG(loop_name, p_error);

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
					dCH__MON_PROC_STABLE_ACTIVE__LOOP_X[i]->Set__DATA(STR__ON);	
					dCH__MON_PROC_ABORT_ACTIVE__LOOP_X[i]->Set__DATA(STR__OFF);
				}
				else
				{
					dCH__MON_PROC_STABLE_ACTIVE__LOOP_X[i]->Set__DATA(STR__OFF);	
				}
			}
			else
			{
				dCH__MON_PROC_STABLE_ACTIVE__LOOP_X[i]->Set__DATA(STR__OFF);
			}
		}

		// ...
	}

	return 1;
}

