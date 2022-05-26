#include "StdAfx.h"
#include "CObj__EPD_SINGLE.h"
#include "CObj__EPD_SINGLE__ALID.h"


// ...
int  CObj__EPD_SINGLE
::Mon__ERROR_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CClass__Error_Timer error__idle;

	CString ch_data;

	CString str_msg;
	CString str_bff;


	// Range.Error ...
	{
		CLink__Error_Common x_link_common;

		// ...
		{
			x_link_common.pCH__CFG_USE = dCH__CFG_USE.Get__PTR();
			x_link_common.pCH__ACTIVE_CHECK = dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE.Get__PTR();

			x_link_common.pCH__CFG_STABLE_DELAY_SEC = aCH__CFG_INTENSITY_STABLE_DELAY_TIME.Get__PTR();
			x_link_common.pCH__CUR_STABLE_DELAY_SEC = sCH__MON_IDLE_INTENSITY_STABLE_DELAY_TIME.Get__PTR();

			x_link_common.pCH__CFG_STABLE_CHECK_SEC = aCH__CFG_INTENSITY_STABLE_CHECK_TIME.Get__PTR();
			x_link_common.pCH__CUR_STABLE_CHECK_SEC = sCH__MON_IDLE_INTENSITY_STABLE_CHECK_TIME.Get__PTR();

			//
			x_link_common.pCH__CUR_STABLE_MIN = sCH__MON_IDLE_INTENSITY_STABLE_MIN.Get__PTR();
			x_link_common.pCH__CUR_STABLE_MAX = sCH__MON_IDLE_INTENSITY_STABLE_MAX.Get__PTR();

			x_link_common.pCH__CUR_ERROR_MIN = sCH__MON_IDLE_INTENSITY_STABLE_MIN.Get__PTR();
			x_link_common.pCH__CUR_ERROR_MAX = sCH__MON_IDLE_INTENSITY_STABLE_MAX.Get__PTR();
		}

		// Idle ...
		{
			error__idle.Disable__MAX_RANGE();
			error__idle.Enable__ERROR_THRESHOLD();

			error__idle.Link__REF_IN_CHANNEL(aEXT_CH__EPD_SIGNAL);

			error__idle.Link__ERROR_COMMON(&x_link_common);

			// ...
			CLink__Error_Para x_link_para;

			x_link_para.pCH__CFG_ERROR_CHECK_SEC = aCH__CFG_INTENSITY_ERROR_TIMEOUT.Get__PTR();
			x_link_para.pCH__CUR_ERROR_CHECK_SEC = sCH__MON_IDLE_INTENSITY_ERROR_CHECK_TIME.Get__PTR();

			error__idle.Link__ERROR_PARA(&x_link_para);
		}
	}

	// Timer.Init ...
	{
		error__idle.Init();
	}

	int loop_count = 0;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		loop_count++;
		if(loop_count > 10)		loop_count = 1;


		if(loop_count == 1)
		{
			double cfg_min = aCH__CFG_INTENSITY_MIN_VALUE->Get__VALUE();
			double cfg_max = aCH__CFG_INTENSITY_MAX_VALUE->Get__VALUE();
			int cfg_dec = (int) aCH__CFG_INTENSITY_DEC_VALUE->Get__VALUE();

			aEXT_CH__EPD_SIGNAL->Change__MIN_MAX_DEC(cfg_min, cfg_max, cfg_dec);

			ch_data.Format("-%.1f", cfg_max);
			sCH__INFO_INTENSITY_MAX_MINUS->Set__DATA(ch_data);

			//
			int err_check = p_alarm->Check__Posted_Internal_Alarm(iLIST_ALID__EPD);

			if(err_check > 0)			dCH__MON_PART_ERROR_ACTIVE->Set__DATA(STR__ON);
			else						dCH__MON_PART_ERROR_ACTIVE->Set__DATA(STR__OFF);
		}

		if(dCH__CFG_USE->Check__DATA(STR__YES) < 0)
		{
			dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE->Set__DATA(STR__OFF);
			dCH__MON_IDLE_INTENSITY_STABLE_ACTIVE->Set__DATA(STR__OFF);	
			dCH__MON_IDLE_INTENSITY_ERROR_ACTIVE->Set__DATA(STR__OFF);	
			continue;
		}

		if(dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE->Check__DATA(STR__READY) > 0)
		{
			dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE->Set__DATA(STR__ON);

			error__idle.Reset();
		}

		// ...
		int active__error_check = dCH__MON_IDLE_INTENSITY_CHECK_ACTIVE->Check__DATA(STR__ON);

		// Error Check ...
		{
			CClass__Error_Timer* p_error = &error__idle;

			if(p_error->Check__Error_State())
			{
				if(active__error_check > 0)
				{
					dCH__MON_IDLE_INTENSITY_ERROR_ACTIVE->Set__DATA(STR__ON);

					// ...
					int alarm_id = ALID__EPD_ERROR_RANGE;
					CString r_act;

					str_msg  = "Error range check ... \n\n";
					str_msg += Get__ERROR_MSG(p_error);

					p_alarm->Check__ALARM(alarm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id, str_msg);
				}
			}
		}

		// Stable Check ...
		if(active__error_check > 0)
		{
			if(error__idle.IsStable())
			{
				dCH__MON_IDLE_INTENSITY_STABLE_ACTIVE->Set__DATA(STR__ON);	
				dCH__MON_IDLE_INTENSITY_ERROR_ACTIVE->Set__DATA(STR__OFF);
			}
			else
			{
				dCH__MON_IDLE_INTENSITY_STABLE_ACTIVE->Set__DATA(STR__OFF);	
			}
		}
		else
		{
			dCH__MON_IDLE_INTENSITY_STABLE_ACTIVE->Set__DATA(STR__OFF);	
		}
	}

	return 1;
}

CString CObj__EPD_SINGLE
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

