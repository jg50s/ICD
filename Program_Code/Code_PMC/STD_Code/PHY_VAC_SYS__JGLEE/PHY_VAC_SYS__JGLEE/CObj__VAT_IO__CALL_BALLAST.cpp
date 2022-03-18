#include "StdAfx.h"
#include "CObj__VAT_IO.h"

#include "CObj__VAT_IO__ALID.h"


// ...
int CObj__VAT_IO
::Call__BALLAST_TRANSFER(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{	
	// APC.Control ...
	if(dCH__CFG_TRANSFER_BALLAST_CTRL_MODE->Check__DATA(STR__PRESSURE) > 0)
	{
		double set_pressure = aCH__CFG_TRANSFER_BALLAST_PRESSURE->Get__VALUE();

		Fnc__PRESSURE(p_variable, p_alarm, set_pressure);
	}
	else
	{
		double set_position = aCH__CFG_TRANSFER_BALLAST_POSITION->Get__VALUE();

		Fnc__POSITION(p_alarm, set_position);
	}

	// Tolerance.Check ...
	{
		SCX__ASYNC_TIMER_CTRL x_async_timer;
		x_async_timer->START__COUNT_UP(9999);

		double cfg__tol_min = aCH__CFG_TRANSFER_BALLAST_TOL_PRESSURE_MIN->Get__VALUE();
		double cfg__tol_max = aCH__CFG_TRANSFER_BALLAST_TOL_PRESSURE_MAX->Get__VALUE();
		double cfg__timeout_sec = aCH__CFG_TRANSFER_BALLAST_TOL_TIMEOUT->Get__VALUE();

		CString log_msg;	
		CString log_bff;
		CString ch_data;

		while(1)
		{
			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -11;
			}

			if(iActive__SIM_MODE > 0)
			{
				double sim_sec = cfg__timeout_sec * 0.5;

				if(x_async_timer->Get__CURRENT_TIME() >= sim_sec)
				{
					double cfg__tol_avg = (cfg__tol_min + cfg__tol_max) * 0.5;
					double trg__press_torr = cfg__tol_avg / 1000.0;

					ch_data.Format("%.3f", trg__press_torr);
					sEXT_CH__SIM_PRESSURE_TORR->Set__DATA(ch_data);
				}
			}

			// ...
			ch_data = sCH__MON_PRESSURE_mTORR->Get__STRING();
			double cur_press = atof(ch_data);

			if((cur_press >= cfg__tol_min)
			&& (cur_press <= cfg__tol_max))	
			{
				log_msg.Format("OK : Elapse Time <- (%.3f) sec \n", x_async_timer->Get__CURRENT_TIME());

				log_bff.Format(" * cur_pressure <- %.1f mtorr \n", cur_press);
				log_msg += log_bff;
				log_bff.Format(" * cfg__tol_min <- %.1f mtorr \n", cfg__tol_min);
				log_msg += log_bff;
				log_bff.Format(" * cfg__tol_max <- %.1f mtorr \n", cfg__tol_max);
				log_msg += log_bff;

				xI_LOG_CTRL->WRITE__LOG(log_msg);
				break;
			}

			if((cur_press < cfg__tol_max)
			&& (x_async_timer->Get__CURRENT_TIME() > cfg__timeout_sec))
			{
				// ...
				{
					int alarm_id = ALID__TRANSFER_BALLAST_PRESSURE_WAIT;
					CString alm_msg;
					CString alm_bff;
					CString r_act;

					alm_msg.Format("Error-Type(1) : Elapse Time <- (%.3f) sec \n", x_async_timer->Get__CURRENT_TIME());
					
					alm_bff.Format(" * Config Max.Pressure <- (%.3f) mtorr \n", cfg__tol_max);
					alm_msg += alm_bff;
					alm_bff.Format(" * Config Min.Pressure <- (%.3f) mtorr \n", cfg__tol_min);
					alm_msg += alm_bff;
					alm_bff.Format(" * Current Pressure <- (%.3f) mtorr \n", cur_press);
					alm_msg += alm_bff;
					alm_bff.Format(" * Config Timeout   <- (%.3f) sec \n", cfg__timeout_sec);
					alm_msg += alm_bff;

					xI_LOG_CTRL->WRITE__LOG(alm_msg);

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
				}
				break;
			}

			if(cur_press >= cfg__tol_max)
			{
				// ...
				{
					int alarm_id = ALID__TRANSFER_BALLAST_OVER_PRESSURE;
					CString alm_msg;
					CString alm_bff;
					CString r_act;

					alm_msg.Format("Error-Type(2) : Elapse Time <- (%.3f) sec \n", x_async_timer->Get__CURRENT_TIME());

					alm_bff.Format(" * Config Max.Pressure <- (%.3f) mtorr \n", cfg__tol_max);
					alm_msg += alm_bff;
					alm_bff.Format(" * Config Min.Pressure <- (%.3f) mtorr \n", cfg__tol_min);
					alm_msg += alm_bff;
					alm_bff.Format(" * Current Pressure <- (%.3f) mtorr \n", cur_press);
					alm_msg += alm_bff;
					alm_bff.Format(" * Config Timeout   <- (%.3f) sec \n", cfg__timeout_sec);
					alm_msg += alm_bff;

					xI_LOG_CTRL->WRITE__LOG(alm_msg);

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
				}					
			}

			Sleep(5);
		}
	}

	return 1;
}

int CObj__VAT_IO
::Call__BALLAST_CHAMBER(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	// APC.Control ...
	if(dCH__CFG_CHAMBER_BALLAST_CTRL_MODE->Check__DATA(STR__PRESSURE) > 0)
	{
		double set_pressure = aCH__CFG_CHAMBER_BALLAST_PRESSURE->Get__VALUE();

		Fnc__PRESSURE(p_variable, p_alarm, set_pressure);
	}
	else
	{
		double set_position = aCH__CFG_CHAMBER_BALLAST_POSITION->Get__VALUE();

		Fnc__POSITION(p_alarm, set_position);
	}

	// Tolerance.Check ...
	{
		SCX__ASYNC_TIMER_CTRL x_async_timer;
		x_async_timer->START__COUNT_UP(9999);

		double cfg__tol_min = aCH__CFG_CHAMBER_BALLAST_TOL_PRESSURE_MIN->Get__VALUE();
		double cfg__tol_max = aCH__CFG_CHAMBER_BALLAST_TOL_PRESSURE_MAX->Get__VALUE();
		double cfg__timeout_sec =  aCH__CFG_CHAMBER_BALLAST_TOL_TIMEOUT->Get__VALUE();

		CString log_msg;	
		CString log_bff;
		CString ch_data;

		while(1)
		{
			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -11;
			}

			if(iActive__SIM_MODE > 0)
			{
				double sim_sec = cfg__timeout_sec * 0.5;

				if(x_async_timer->Get__CURRENT_TIME() >= sim_sec)
				{
					double cfg__tol_avg = (cfg__tol_min + cfg__tol_max) * 0.5;
					double trg__press_torr = cfg__tol_avg / 1000.0;

					ch_data.Format("%.3f", trg__press_torr);
					sEXT_CH__SIM_PRESSURE_TORR->Set__DATA(ch_data);
				}
			}

			// ...
			ch_data = sCH__MON_PRESSURE_mTORR->Get__STRING();
			double cur_press = atof(ch_data);

			if((cur_press >= cfg__tol_min)
			&& (cur_press <= cfg__tol_max))	
			{
				log_msg.Format("OK : Elapse Time <- (%.3f) sec \n", x_async_timer->Get__CURRENT_TIME());

				log_bff.Format(" * cur_pressure <- %.1f mtorr \n", cur_press);
				log_msg += log_bff;
				log_bff.Format(" * cfg__tol_min <- %.1f mtorr \n", cfg__tol_min);
				log_msg += log_bff;
				log_bff.Format(" * cfg__tol_max <- %.1f mtorr \n", cfg__tol_max);
				log_msg += log_bff;

				xI_LOG_CTRL->WRITE__LOG(log_msg);
				break;
			}

			if((cur_press < cfg__tol_max)
			&& (x_async_timer->Get__CURRENT_TIME() > cfg__timeout_sec))
			{
				// ...
				{
					int alarm_id = ALID__CHAMBER_BALLAST_PRESSURE_WAIT;
					CString alm_msg;
					CString alm_bff;
					CString r_act;

					alm_msg.Format("Error-Type(1) : Elapse Time <- (%.3f) sec \n", x_async_timer->Get__CURRENT_TIME());

					alm_bff.Format(" * Config Max.Pressure <- (%.3f) mtorr \n", cfg__tol_max);
					alm_msg += alm_bff;
					alm_bff.Format(" * Config Min.Pressure <- (%.3f) mtorr \n", cfg__tol_min);
					alm_msg += alm_bff;
					alm_bff.Format(" * Current Pressure <- (%.3f) mtorr \n", cur_press);
					alm_msg += alm_bff;
					alm_bff.Format(" * Config Timeout   <- (%.3f) sec \n", cfg__timeout_sec);
					alm_msg += alm_bff;

					xI_LOG_CTRL->WRITE__LOG(alm_msg);

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
				}
				break;
			}

			if(cur_press >= cfg__tol_max)
			{
				// ...
				{
					int alarm_id = ALID__CHAMBER_BALLAST_OVER_PRESSURE;
					CString alm_msg;
					CString alm_bff;
					CString r_act;

					alm_msg.Format("Error-Type(2) : Elapse Time <- (%.3f) sec \n", x_async_timer->Get__CURRENT_TIME());

					alm_bff.Format(" * Config Max.Pressure <- (%.3f) mtorr \n", cfg__tol_max);
					alm_msg += alm_bff;
					alm_bff.Format(" * Config Min.Pressure <- (%.3f) mtorr \n", cfg__tol_min);
					alm_msg += alm_bff;
					alm_bff.Format(" * Current Pressure <- (%.3f) mtorr \n", cur_press);
					alm_msg += alm_bff;
					alm_bff.Format(" * Config Timeout   <- (%.3f) sec \n", cfg__timeout_sec);
					alm_msg += alm_bff;

					xI_LOG_CTRL->WRITE__LOG(alm_msg);

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
				}					
			}

			Sleep(5);
		}
	}

	return 1;
}
