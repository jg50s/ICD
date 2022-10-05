#include "StdAfx.h"
#include "CObj__CHM_FNC.h"
#include "CObj__CHM_FNC__DEF.h"
#include "CObj__CHM_FNC__ALID.h"

#include "Macro_Function.h"


// ...
int CObj__CHM_FNC
::Fnc__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(iActive__SIM_MODE  > 0)
	{
		dEXT_CH__CHM_ATM_SNS->Set__DATA(STR__OFF);
		dEXT_CH__CHM_VAC_SNS->Set__DATA(STR__ON);
	}	

	// ...
	bool active__wafer_dechuck = false;

	if(dEXT_CH__WAFER_SLOT01_STATE->Check__DATA(STR__NONE) < 0)
	{
		if(bActive__ESC_OBJ)
		{
			if(dEXT_CH__ESC_MON_CHUCK_STATUS->Check__DATA(STR__DECHUCKED) < 0)			active__wafer_dechuck = true;
		}
	}

	if(active__wafer_dechuck)
	{
		if(dEXT_CH__CFG_DECHUCK_CTRL_MODE->Check__DATA(STR__CONFIG) > 0)
		{
			if(bActive__ESC_OBJ)
			{
				if(pOBJ_CTRL__ESC->Call__OBJECT(_ESC_CMMD__DECHUCK) < 0)
				{
					return -21;
				}
			}
		}
	}

	return 1;
}

int CObj__CHM_FNC
::Fnc__ALL_GAS_LINE_CLOSE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	pOBJ_CTRL__GAS_VLV->Dislink__UPPER_OBJECT();

	int flag = pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__ALL_CLOSE);

	pOBJ_CTRL__GAS_VLV->Link__UPPER_OBJECT();

	if(flag < 0)
	{
		CString log_msg;

		log_msg.Format("Fnc__ALL_GAS_LINE_CLOSE - Failed (%d) ...", flag);	
		xLOG_CTRL->WRITE__LOG(log_msg);
		return -1;
	}
	return 1;
}
int CObj__CHM_FNC
::Fnc__ALL_VAC_LINE_CLOSE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{	
	int flag = Call__VAC_VLV__ALL_CLOSE(p_variable, p_alarm);
	
	if(flag < 0)
	{
		CString log_msg;

		log_msg.Format("Fnc__ALL_VAC_LINE_CLOSE - Failed (%d) ...", flag);	
		xLOG_CTRL->WRITE__LOG(log_msg);
		return -1;
	}
	return 1;
}

int CObj__CHM_FNC::Check__LOW_VAC_PUMP()
{
	// SLOT.VALVE ...
	{
		bool active__slot_vlv_open = true;

		if(bActive__CHM_SHUTTER_STATE)
		{
			if(dEXT_CH__CHM_SHUTTER_STATE->Check__DATA(STR__CLOSE) > 0)			active__slot_vlv_open = false;
		}
		else if(bActive__CHM_SLOT_VLV_STATE)
		{
			if(dEXT_CH__CHM_SLOT_VLV_STATE->Check__DATA(STR__CLOSE) > 0)		active__slot_vlv_open = false;
		}
		else
		{
			if(dEXT_CH__PMC_SLIT_VLV_STS->Check__DATA(STR__CLOSE) > 0)			active__slot_vlv_open = false;
		}

		if(active__slot_vlv_open)
		{
			return -11;
		}
	}

	if(bActive__CHM_LID_STATE)
	{
		if(dEXT_CH__CHM_LID_STATE->Check__DATA(sCHM_LID__CLOSE_STATE) < 0)
		{
			return -12;
		}
	}

	// Dry_Pump On Check 
	if(bActive__DRY_PUMP)
	{
		if(dEXT_CH__DRY_PUMP__POWER_SNS->Check__DATA(STR__ON) < 0)
		{
			return -13;
		}
	}

	// PRESSURE CHECK ...
	{
		double cfg_press = aCH__CFG_FAST_PUMP_PRESSURE->Get__VALUE();
		double cur_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();

		if(cur_press > cfg_press)
		{
			return -21;
		}
	}

	// ATM & VAC.Sensor Check ...
	if((dEXT_CH__CHM_ATM_SNS->Check__DATA(STR__OFF) < 0)
	|| (dEXT_CH__CHM_VAC_SNS->Check__DATA(STR__ON)  < 0))
	{
		return -31;
	}

	return 1;
}
int CObj__CHM_FNC
::Fnc__LOW_VAC_PUMP(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const int high_vac_flag,const int purge_flag)
{
LOOP_RETRY:

	CString ch_data;
	CString log_msg;
	int flag;

	// SLOT.VALVE ...
	{
		bool active__slot_vlv_open = true;

		if(bActive__CHM_SHUTTER_STATE)
		{
			if(dEXT_CH__CHM_SHUTTER_STATE->Check__DATA(STR__CLOSE) > 0)			active__slot_vlv_open = false;
		}
		else if(bActive__CHM_SLOT_VLV_STATE)
		{
			if(dEXT_CH__CHM_SLOT_VLV_STATE->Check__DATA(STR__CLOSE) > 0)		active__slot_vlv_open = false;
		}
		else
		{
			if(dEXT_CH__PMC_SLIT_VLV_STS->Check__DATA(STR__CLOSE) > 0)			active__slot_vlv_open = false;
		}

		if(active__slot_vlv_open)
		{
			// Alarm ...
			{
				int alm_id = ALID__CHM_SLOT_VLV_NOT_CLOSE;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				if(bActive__CHM_SHUTTER_STATE)
				{
					alm_bff.Format(" * %s <- %s",
									dEXT_CH__CHM_SHUTTER_STATE->Get__CHANNEL_NAME(),
									dEXT_CH__CHM_SHUTTER_STATE->Get__STRING());
					alm_msg += alm_bff;
				}
				else
				{
					alm_bff.Format(" * %s <- %s",
									dEXT_CH__PMC_SLIT_VLV_STS->Get__CHANNEL_NAME(),
									dEXT_CH__PMC_SLIT_VLV_STS->Get__STRING());
					alm_msg += alm_bff;
				}

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);

				if(r_act.CompareNoCase(ACT__RETRY) == 0)
				{
					goto LOOP_RETRY;
				}
			}
			return -101;
		}
	}

	if(bActive__CHM_LID_STATE)
	{
		if(dEXT_CH__CHM_LID_STATE->Check__DATA(sCHM_LID__CLOSE_STATE) < 0)
		{
			// Alarm ...
			{
				int alm_id = ALID__CHM_LID_NOT_CLOSE;
				CString alm_msg;
				CString r_act;

				alm_msg.Format(" * %s <- %s",
							   dEXT_CH__CHM_LID_STATE->Get__CHANNEL_NAME(),
							   dEXT_CH__CHM_LID_STATE->Get__STRING());

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);

				if(r_act.CompareNoCase(ACT__RETRY) == 0)
				{
					goto LOOP_RETRY;
				}
			}
			return -102;
		}
	}

	// ESC Pump_Ready ...
	if(bActive__ESC_OBJ)
	{
		// ...
		{
			log_msg = "ESC <- Pump_Ready";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(pOBJ_CTRL__ESC->Call__OBJECT(_ESC_CMMD__PUMP_READY) < 0)
		{
			return -10;
		}
	}

	// Gas-Valve <- Proc_Ready
	{
		// ...
		{
			log_msg = "GAS-Valve <- Proc_Ready";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__ALL_CLOSE) < 0)
		{
			return -11;
		}
	}

	// VAC-Valve <- All_Close
	{
		// ...
		{
			log_msg = "VAC-Valve <- All_Close";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
		
		if(Call__VAC_VLV__ALL_CLOSE(p_variable, p_alarm) < 0)
		{
			return -31;
		}
	}

	// Dry_Pump On Check 
	if(bActive__DRY_PUMP)
	{
		// ...
		{
			log_msg = "Dry_Pump On Check";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(dEXT_CH__DRY_PUMP__POWER_SNS->Check__DATA(STR__ON) < 0)
		{
			// Alarm ...
			{
				int alm_id = ALID__DRY_PUMP_STATE_NOT_ON;
				CString alm_msg;
				CString r_act;

				alm_msg = "The sequence of Low-VAC can not be executed !";

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);
			}
			return -41;
		}
	}

	// Soft Pumping ...
	{
		// ...
		{
			log_msg = "Soft_Pumping : Started ...";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		flag = _Fnc__SOFT_LOW_VAC(p_variable, p_alarm, purge_flag);

		if(flag < 0)
		{
			// ...
			{
				log_msg.Format("Soft_Pumping : Failed (%d) ...", flag);	
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			return flag;
		}

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -51;
		}
	}

	// ATM.Sensor Off Checking ...
	{
		if(iActive__SIM_MODE > 0)
		{
			dEXT_CH__CHM_ATM_SNS->Set__DATA(STR__OFF);
		}

		// ...
		{
			log_msg = "ATM_Sensor.Off Checking ...";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		sCH__OBJ_MSG->Set__DATA("ATM_Sensor.Off Checking ...");

		// ...
		SCX__ASYNC_TIMER_CTRL x_asyc_timer;

		x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
		x_asyc_timer->START__COUNT_UP(99999);

		while(1)
		{
			// ATM.SNS Check ...
			{
				double cur__chm_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();
				double cfg__ref_press = aCH__CFG_ATM_SNS_REF_PRESSURE->Get__VALUE();

				if(cur__chm_press > cfg__ref_press)
				{
					break;
				}

				if(dEXT_CH__CHM_ATM_SNS->Check__DATA(STR__OFF) > 0)
				{
					break;
				}
			}

			Sleep(100);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -61;
			}

			// ...
			double cfg__atm_off_sec = aCH__CFG_SOFT_PUMP_ATM_SNS_OFF_TIMEOUT->Get__VALUE();

			if(x_asyc_timer->Get__CURRENT_TIME() >= cfg__atm_off_sec)
			{
				int alarm_id = ALID__VAC_SENSOR_CHECKING_TIMEOUT;
				
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format(" * %s <- %s \n", 
							   dEXT_CH__CHM_ATM_SNS->Get__CHANNEL_NAME(),
							   dEXT_CH__CHM_ATM_SNS->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format(" * %s <- %s \n",
							   dEXT_CH__CHM_VAC_SNS->Get__CHANNEL_NAME(),
							   dEXT_CH__CHM_VAC_SNS->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format(" * Config timeout of ATM_OFF Sensor is %.1f (sec) \n",
								cfg__atm_off_sec);
				alm_msg += alm_bff;

				p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, r_act, alm_msg);
			}
		}
	}

	// Soft-OverPumping.Timeout ...
	{
		SCX__ASYNC_TIMER_CTRL x_asyc_timer;

		x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
		x_asyc_timer->START__COUNT_UP(99999);

		do
		{
			if(p_variable->Check__CTRL_ABORT() > 0)					return -71;

			double cfg_sec = aCH__CFG_SOFT_PUMP_OVER_TIME->Get__VALUE();
			if(x_asyc_timer->Get__CURRENT_TIME() >= cfg_sec)		break;

			Sleep(10);
		} 
		while(1);
	}

RETRY_LOOP:

	// SR CLOSE & FR OPEN ...
	{
		SCX__ASYNC_TIMER_CTRL x_asyc_timer;

		x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
		x_asyc_timer->START__COUNT_UP(9999);

		if(Call__VAC_VLV__FR_OPEN(p_variable, p_alarm) < 0)
		{
			return -101;
		}

		// ...
		{
			log_msg = "Fast.Vacuum Checking ...";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		sCH__OBJ_MSG->Set__DATA("Fast.Vacuum Checking ...");

		while(1)
		{
			// PRESSURE CHECK ...
			double cfg_press = aCH__CFG_FAST_PUMP_PRESSURE->Get__VALUE();
			double cur_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();

			if(cur_press < cfg_press)
			{
				break;
			}

			Sleep(100);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -102;
			}

			// TIMEOUT CHECK ...
			{
				double cfg__timeout_sec = aCH__CFG_FAST_PUMP_TIMEOUT->Get__VALUE();

				if(iActive__SIM_MODE > 0)
				{
					double sim_sec = cfg__timeout_sec / 2.0;
					if(sim_sec > 5.0)		sim_sec = 5.0;

					if(sim_sec <= x_asyc_timer->Get__CURRENT_TIME())
					{
						ch_data.Format("%.3f", cfg_press - 0.1);

						sEXT_CH__SIM_PRESSURE_TORR->Set__DATA(ch_data);
						aEXT_CH__CHM_PRESSURE_TORR->Set__DATA(ch_data);
					}
				}

				if(cfg__timeout_sec <= x_asyc_timer->Get__CURRENT_TIME())
				{
					int alarm_id = ALID__LOW_VAC_CHECK_COMPLETE_TIMEOUT;

					CString alarm_msg;
					CString msg_bff;
					CString r_act;

					msg_bff.Format("Current chamber pressure is %.3f (torr).\n", cur_press);
					alarm_msg += msg_bff;
					
					msg_bff.Format("Config fast-vacuum pressure is %.3f (torr).\n", cfg_press);
					alarm_msg += msg_bff;
					
					msg_bff.Format("Config time-out is %.0f (sec).\n", cfg__timeout_sec);
					alarm_msg += msg_bff;

					p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alarm_msg,r_act);

					if(r_act.CompareNoCase(ACT__RETRY) == 0)
					{
						goto RETRY_LOOP;
					}
					return -103;
				}
			}
		}
	}

	// VAC.Sensor On Checking ...
	{
		if(iActive__SIM_MODE > 0)
		{
			dEXT_CH__CHM_ATM_SNS->Set__DATA(STR__OFF);
			dEXT_CH__CHM_VAC_SNS->Set__DATA(STR__ON);
		}

		// ...
		{
			log_msg = "VAC_Sensor.On Checking ...";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		sCH__OBJ_MSG->Set__DATA("VAC_Sensor.On Checking ...");

		// ...
		SCX__ASYNC_TIMER_CTRL x_asyc_timer;

		x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
		x_asyc_timer->START__COUNT_UP(99999);

		while(1)
		{
			if((dEXT_CH__CHM_ATM_SNS->Check__DATA(STR__OFF) > 0)
			&& (dEXT_CH__CHM_VAC_SNS->Check__DATA(STR__ON)  > 0))
			{
				break;
			}

			Sleep(100);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -61;
			}

			// ...
			double cfg__vac_on_sec = aCH__CFG_FAST_PUMP_VAC_SNS_ON_TIMEOUT->Get__VALUE();

			if(x_asyc_timer->Get__CURRENT_TIME() >= cfg__vac_on_sec)
			{
				int alarm_id = ALID__VAC_SENSOR_CHECKING_TIMEOUT;

				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format(" * %s <- %s \n", 
								dEXT_CH__CHM_ATM_SNS->Get__CHANNEL_NAME(),
								dEXT_CH__CHM_ATM_SNS->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format(" * %s <- %s \n",
								dEXT_CH__CHM_VAC_SNS->Get__CHANNEL_NAME(),
								dEXT_CH__CHM_VAC_SNS->Get__STRING());
				alm_msg += alm_bff;

				alm_bff.Format(" * Config timeout of VAC_ON Sensor is %.1f (sec) \n",
								cfg__vac_on_sec);
				alm_msg += alm_bff;

				p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, r_act, alm_msg);
			}
		}
	}

	return 1;
}

int CObj__CHM_FNC
::Fnc__HIGH_VAC_PUMP(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	int flag;

	// ...
	bool active__tmp_on = false;

	if(bActive__OBJ_CTRL__TURBO_PUMP)
	{
		if(dEXT_CH__TURBO_PUMP__POWER_SNS->Check__DATA(STR__ON) > 0)
			active__tmp_on = true;
	}

	// VAC-Valve : All_Close ...
	if(active__tmp_on)
	{
		// ...
		{
			log_msg = "VAC-Valve <- All_Close, In TMP-ON State.";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(Call__VAC_VLV__ALL_CLOSE(p_variable, p_alarm, false, false) < 0)
		{
			return -11;
		}
	}
	else
	{
		// ...
		{
			log_msg = "VAC-Valve <- All_Close";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(Call__VAC_VLV__ALL_CLOSE(p_variable, p_alarm, false) < 0)
		{
			return -12;
		}
	}

	// Turbo_Pump On : Check 
	if(bActive__OBJ_CTRL__TURBO_PUMP)
	{
		// ...
		{
			log_msg = "Turbo_Pump On Check";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(dEXT_CH__TURBO_PUMP__POWER_SNS->Check__DATA(STR__ON) < 0)
		{
			if(Fnc__TURBO_PUMP_ON(p_variable, p_alarm) < 0)
			{
				return -21;
			}
		}
	}

RETRY_LOOP:

	// High-Vacuum Pumping ...
	{
		CString ch_data;

		SCX__ASYNC_TIMER_CTRL x_asyc_timer;

		x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
		x_asyc_timer->START__COUNT_UP(9999);

		if(bActive__OBJ_CTRL__TURBO_PUMP)
		{
			if(pOBJ_CTRL__TURBO_PUMP->Call__OBJECT(CMMD_TMP__FULL_OPEN) < 0)
				return -101;
		}

		while(1)
		{
			Sleep(100);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -71;
			}

			// Fast_Pumping.Pressure Check ...
			double cfg_press = aCH__CFG_HIGH_VAC_PRESSURE->Get__VALUE();
			double cur_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();

			if(cur_press < cfg_press)
			{
				break;
			}

			// Timeout Check ...
			{
				double ref_timeout = aCH__CFG_HIGH_VAC_TIMEOUT->Get__VALUE();

				if(iActive__SIM_MODE > 0)
				{
					double sim_sec = 5.0;

					if(sim_sec <= x_asyc_timer->Get__CURRENT_TIME())
					{
						double cfg_press = aCH__CFG_HIGH_VAC_PRESSURE->Get__VALUE();
						cfg_press -= 0.001;

						ch_data.Format("%.3f", cfg_press);
						sEXT_CH__SIM_PRESSURE_TORR->Set__DATA(ch_data);
					}
				}

				if(ref_timeout <= x_asyc_timer->Get__CURRENT_TIME())
				{
					// ...	
					int alarm_id = ALID__LOW_VAC_CHECK_COMPLETE_TIMEOUT;
					CString alarm_msg;
					CString msg_bff;
					CString r_act;

					double ref_press;
					double cur_press;

					ref_press = aCH__CFG_HIGH_VAC_PRESSURE->Get__VALUE();
					cur_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();

					msg_bff.Format("Current chamber's pressure is %.3f (torr).\n", cur_press);
					alarm_msg += msg_bff;
					msg_bff.Format("Config low-vacuum pressure is %.3f (torr).\n", ref_press);
					alarm_msg += msg_bff;
					msg_bff.Format("Config time-out is %.0f (sec).\n",   ref_timeout);
					alarm_msg += msg_bff;

					p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alarm_msg,r_act);

					if(r_act.CompareNoCase(ACT__RETRY) == 0)
					{
						goto RETRY_LOOP;
					}
					return -205;
				}
			}
		}
	}

	// Gas-Valve : Proc_Ready ...
	if(dCH__CFG_PROCESS_READY_CTRL_AFTER_CHM_PUMPING->Check__DATA(STR__YES) > 0)
	{
		// ...
		{
			log_msg = "GAS-Valve <- Proc_Ready";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__PROC_READY) < 0)
		{
			return -11;
		}
	}

	return 1;
}

int CObj__CHM_FNC
::Fnc__DRY_PUMP_ON(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -101;
	}

	if(Fnc__ALL_GAS_LINE_CLOSE(p_variable,p_alarm) < 0)
	{
		return -102;
	}

	if(bActive__DRY_PUMP)
	{
		if(dEXT_CH__DRY_PUMP__POWER_SNS->Check__DATA(STR__ON) > 0)
		{
			return 11;
		}
	}

	if(Fnc__PUMP_CTRL(p_variable, p_alarm, MODE__DRY_PUMP_ON) < 0)
	{
		return -104;
	}

	return 1;
}

int CObj__CHM_FNC
::Fnc__TURBO_PUMP_ON(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	int	flag = -1;

RETRY_LOOP:

	// ...
	{
		log_msg = "Fnc__TURBO_PUMP_ON() : Started ...";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -201;
	}

	// 1.1 Gas Line Close
	if(Fnc__ALL_GAS_LINE_CLOSE(p_variable,p_alarm) < 0)
	{
		return -202;
	}

	// 1.2 Soft/Fast Rough Valve Close
	if(Fnc__ALL_VAC_LINE_CLOSE(p_variable,p_alarm) < 0)
	{
		return -203;
	}

	// 2. Dry Pump Check
	flag = Fnc__DRY_PUMP_ON(p_variable,p_alarm);					// Dry Pump On Check
	if(flag < 0)
	{
		log_msg.Format("Fnc__TURBO_PUMP_ON : Fnc__DRY_PUMP_ON - Failed (%d) ...", flag);	
		xLOG_CTRL->WRITE__LOG(log_msg);

		return flag;
	}

	// 3.2 Turbo Pump Status Check
	if(dEXT_CH__TURBO_PUMP__POWER_SNS->Check__DATA(STR__ON)  > 0)
	{
		flag = Call__VAC_VLV__EXHAUST_OPEN(p_variable, p_alarm);
		if(flag < 0)
		{
			log_msg.Format("Fnc__TURBO_PUMP_ON : EXHAUST.VAC VALVE OPEN - Failed (%1d) ...", flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return flag;
		}

		// ...
		{
			log_msg.Format("Fnc__TURBO_PUMP_ON : TURBO_PUMP Status is ON - Skipped ...");
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
		return 1;
	}

	// ...
	{
		log_msg = "Fnc__TURBO_PUMP_ON() : Check (1) ...";
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// Turbo Pump - On
	{
		bool active__foreline_vac_on = false;

		double  ref_timeout;
		CString var_data;
		
		int	n_count = 0;
		int n_turbo_stable_time = 0;

		SCX__ASYNC_TIMER_CTRL x_asyc_timer;
		x_asyc_timer->START__COUNT_UP(9999);

		do
		{
			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -1001;
			}

			aCH__CFG_PUMP_TURBO_STABLE_TIME->Get__DATA(var_data);
			n_turbo_stable_time = atoi(var_data) * 10;				// sec

			if(sEXT_CH__PMP_VAC_SNS->Check__DATA(STR__ON) > 0)
			{
				n_count++;
				active__foreline_vac_on = true;
			}
			else
			{
				n_count = 0;
				active__foreline_vac_on = false;
			}

			if((active__foreline_vac_on)
			&& (n_count >= n_turbo_stable_time))
			{
				// Turbo Pump out Pressure OK !!!
				break;
			}

			// Alarm Check ...
			ref_timeout = aCH__CFG_FORELINE_PUMPING_TIMEOUT->Get__VALUE();

			if(ref_timeout <= x_asyc_timer->Get__CURRENT_TIME())
			{
				int alarm_id = ALID__FORELINE_PUMP_TIMEOUT;
				CString alarm_msg;
				CString msg_bff;
				CString r_act;

				msg_bff.Format("Config foreline time-out is %.0f (sec).\n",   ref_timeout);
				alarm_msg += msg_bff;

				p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alarm_msg,r_act);

				if(r_act.CompareNoCase(ACT__RETRY) == 0)
				{
					goto RETRY_LOOP;
				}

				return -205;
			}

			Sleep(100);
		} 
		while(1);

		// ...
		{
			log_msg = "Fnc__TURBO_PUMP_ON() : Check (2) ...";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		flag = Call__VAC_VLV__EXHAUST_OPEN(p_variable, p_alarm);
		if(flag < 0)
		{
			log_msg.Format("Fnc__TURBO_PUMP_ON : EXHAUST.VAC VALVE OPEN - Failed (%1d) ...", flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
			return flag;
		}

		// ...
		{
			log_msg = "Fnc__TURBO_PUMP_ON() : Check (3) ...";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(Fnc__PUMP_CTRL(p_variable, p_alarm, MODE__TMP_ON) < 0)
		{
			return -207;
		}

		// ...
		{
			log_msg = "Fnc__TURBO_PUMP_ON() : Check (4) ...";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	return 1;
}

int CObj__CHM_FNC
::Fnc__PUMP_CTRL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm, const int mode)
{
	CString log_msg;

	switch(mode)
	{
		// Dry-Pump ...
		case MODE__DRY_PUMP_ON:
			if(bActive__DRY_PUMP)
			{
				if(dEXT_CH__DRY_PUMP__POWER_SNS->Check__DATA(STR__ON) < 0)
				{
					if(pOBJ_CTRL__DRY_PUMP->Call__OBJECT(CMMD_TMP__PUMP_ON) < 0)
					{
						log_msg.Format("Fnc__PUMP_CTRL - Dry Pump On Failed");
						xLOG_CTRL->WRITE__LOG(log_msg);

						return -111;
					}
				}
			}
			break;

		case MODE__DRY_PUMP_OFF:
			if(bActive__DRY_PUMP)
			{
				if(dEXT_CH__DRY_PUMP__POWER_SNS->Check__DATA(STR__OFF) < 0)
				{
					if(pOBJ_CTRL__DRY_PUMP->Call__OBJECT(CMMD_TMP__PUMP_OFF) < 0)
					{
						log_msg.Format("Fnc__PUMP_CTRL - Dry Pump Off Failed");
						xLOG_CTRL->WRITE__LOG(log_msg);

						return -112;
					}
				}
			}
			break;

		// Turbo-Pump ...
		case MODE__TMP_ON:
			if(iActive__SIM_MODE > 0)
			{
				if(bActive__OBJ_CTRL__TURBO_PUMP)
				{
					if(pOBJ_CTRL__TURBO_PUMP->Call__OBJECT(CMMD_TMP__PUMP_ON) < 0)
					{
						log_msg.Format("Fnc__PUMP_CTRL - Turbo Pump On Failed");
						xLOG_CTRL->WRITE__LOG(log_msg);
						
						return -113;
					}
				}
			}
			else
			{
				if(bActive__OBJ_CTRL__TURBO_PUMP)
				{
					if(pOBJ_CTRL__TURBO_PUMP->Call__OBJECT(CMMD_TMP__PUMP_ON) < 0)
					{
						log_msg.Format("Fnc__PUMP_CTRL - Turbo Pump On Failed");
						xLOG_CTRL->WRITE__LOG(log_msg);

						return -113;
					}
				}
			}
			break;

		case MODE__TMP_OFF:
			if(bActive__OBJ_CTRL__TURBO_PUMP)
			{
				if(pOBJ_CTRL__TURBO_PUMP->Call__OBJECT(CMMD_TMP__PUMP_OFF) < 0)
				{
					log_msg.Format("Fnc__PUMP_CTRL - Turbo Pump Off Failed");
					xLOG_CTRL->WRITE__LOG(log_msg);

					return -114;
				}
			}
			break;

		default:
			{
				log_msg.Format("Fnc__PUMP_CTRL - Invalid Mode (%d)", mode);
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			return -115;
	}

	return 1;
}


int CObj__CHM_FNC
::_Fnc__SOFT_LOW_VAC(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const int purge_flag)
{
RETRY_LOOP:

	// ...
	CString ch_data;

	// PRESSURE CHECK ...
	{
		double ref_press;

		if(purge_flag < 0)		ref_press = aCH__CFG_SOFT_PUMP_PRESSURE->Get__VALUE();
		else					ref_press = aCH__CFG_PURGE_DOWN_PRESSURE->Get__VALUE();

		double cur_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();

		if(cur_press <= ref_press)	
		{
			return 1;
		}
	}

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -101;
	}

	// Soft-Pumping ... 
	{
		if(purge_flag < 0)		sCH__OBJ_MSG->Set__DATA("Low_Vacuum - Soft Pumping ...");
		else					sCH__OBJ_MSG->Set__DATA("Purge Low_Vacuum - Soft Pumping ...");

		if(Call__VAC_VLV__SR_OPEN(p_variable, p_alarm) < 0)
		{
			return -111;
		}
	}

	// Pressure Check ...
	{
		SCX__ASYNC_TIMER_CTRL x_asyc_timer;

		x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
		x_asyc_timer->START__COUNT_UP(99999);

		do
		{
			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -124;
			}

			// ...
			double cfg__ref_press;
			double cur__chm_press;

			// Soft_Pump.Pressure Check ...
			{
				if(purge_flag < 0)		cfg__ref_press = aCH__CFG_SOFT_PUMP_PRESSURE->Get__VALUE();
				else					cfg__ref_press = aCH__CFG_PURGE_DOWN_PRESSURE->Get__VALUE();

				cur__chm_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();

				if(cur__chm_press <= cfg__ref_press)
				{
					break;
				}
			}

			// Alarm Check ...
			double cfg__timeout_sec = aCH__CFG_SOFT_PUMP_TIMEOUT->Get__VALUE();

			if(iActive__SIM_MODE > 0)
			{
				double sim_sec = cfg__timeout_sec / 2.0;
				if(sim_sec > 5.0)		sim_sec = 5.0;

				if(sim_sec <= x_asyc_timer->Get__CURRENT_TIME())
				{
					ch_data.Format("%.3f", cfg__ref_press - 0.001);
					
					sEXT_CH__SIM_PRESSURE_TORR->Set__DATA(ch_data);
					aEXT_CH__CHM_PRESSURE_TORR->Set__DATA(ch_data);

					dEXT_CH__CHM_ATM_SNS->Set__DATA(STR__OFF);
				}
			}

			if(cfg__timeout_sec <= x_asyc_timer->Get__CURRENT_TIME())
			{
				int alarm_id = ALID__SOFT_PUMP_TIMEOUT;

				CString alarm_msg;
				CString msg_bff;
				CString r_act;
				
				// ...
				{
					msg_bff.Format("Current chamber pressure is %.3f (torr).\n", cur__chm_press);
					alarm_msg += msg_bff;
				
					msg_bff.Format("Config soft-pumping pressure is %.3f (torr).\n", cfg__ref_press);
					alarm_msg += msg_bff;
				
					msg_bff.Format("Config soft-pumping time-out is %.0f (sec).\n", cfg__timeout_sec);
					alarm_msg += msg_bff;
				}

				p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alarm_msg,r_act);

				if(r_act.CompareNoCase(ACT__RETRY) == 0)
				{
					goto RETRY_LOOP;
				}
				return -125;
			}

			Sleep(100);
		} 
		while(1);
	}

	return 1;
}

int CObj__CHM_FNC
::Fnc__VENT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm, const int purge_flag)
{
	CString log_msg;
	int flag = -1;

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -151;
	}

	// 1. Purge Line CLOSE
	{
		// ...
		{
			log_msg = "Purge_Line <- Close ...";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(Fnc__ALL_GAS_LINE_CLOSE(p_variable,p_alarm) < 0)
		{
			return -152;
		}
	}

	// 2.1 APC CLOSE
	{
		// ...
		{
			log_msg = "VAC_Valve <- All_Close ...";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(Call__VAC_VLV__ALL_CLOSE(p_variable, p_alarm, false) < 0)
		{
			return -162;
		}
	}

	// ...
	{
		flag = _Fnc__SOFT_VENT(p_variable, p_alarm, purge_flag);

		if(flag < 0)
		{
			pOBJ_CTRL__GAS_VLV->Dislink__UPPER_OBJECT();
			pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__SV_CLOSE);

			// ...
			{
				log_msg.Format("_Fnc__SOFT_VENT - Failed (%d) ... Purge_Flag (%d)", flag, purge_flag);	
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			return -171;
		}
	}

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		pOBJ_CTRL__GAS_VLV->Dislink__UPPER_OBJECT();
		pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__SV_CLOSE);
		return -181;
	}

	// ...
	{
		flag = _Fnc__FAST_VENT(p_variable, p_alarm, purge_flag);

		if(flag < 0)
		{
			pOBJ_CTRL__GAS_VLV->Dislink__UPPER_OBJECT();
			pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__FV_CLOSE);

			// ...
			{
				log_msg.Format("_Fnc__FASE_VENT Failed (%d) ... Purge_Flag (%d)", flag,purge_flag);		
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			return -156;
		}

		if(purge_flag > 0)
		{
			return 1;
		}
	}

	// Check Vent Complete ...
	{
		flag = Fnc__VENT_COMPLETE(p_variable, p_alarm);
		
		if(flag < 0)
		{
			// ...
			{
				log_msg.Format("Fnc__VENT_COMPLETE - Failed (%d) ...", flag);	
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			return flag;
		}
	}

	// Fast.Vent Over.Time ...
	{
		SCX__TIMER_CTRL x_timer_ctrl;
		
		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH__OBJ_TIMER->Get__CHANNEL_NAME());

		double cfg_sec = aCH__CFG_FAST_VENT_OVER_TIME->Get__VALUE();

		if(x_timer_ctrl->WAIT(cfg_sec) < 0)
		{
			return -1;
		}
	}

	return pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__FV_CLOSE);
}

int CObj__CHM_FNC
::_Fnc__SOFT_VENT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const int purge_flag)
{
RETRY_LOOP:

	// ...
	CString ch_data;

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -161;
	}

	// ...
	SCX__ASYNC_TIMER_CTRL x_asyc_timer;

	x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
	x_asyc_timer->START__COUNT_UP(99999);
	
	// Soft Vent ....
	{
		if(purge_flag < 0)		sCH__OBJ_MSG->Set__DATA("Soft Venting ...");
		else					sCH__OBJ_MSG->Set__DATA("Purge Soft Venting ...");

		if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__SV_OPEN) < 0)
		{
			CString log_msg;

			log_msg.Format("_Fnc__SOFT_VENT - S/V Valve Open Failed");			
			xLOG_CTRL->WRITE__LOG(log_msg);

			x_asyc_timer->STOP();
			return -162;
		}

		// Pressure.Check ...
		do
		{
			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				x_asyc_timer->STOP();
				return -163;
			}

			// Pressure Check ...
			double cfg__ref_press;

			if(purge_flag < 0)		cfg__ref_press = aCH__CFG_SOFT_VENT_PRESSURE->Get__VALUE();
			else					cfg__ref_press = aCH__CFG_PURGE_UP_PRESSURE->Get__VALUE();

			double cur__chm_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();

			if(cur__chm_press >= cfg__ref_press)
			{
				break;
			}

			// Alarm Check ...
			double cfg__timeout_sec = aCH__CFG_SOFT_VENT_TIMEOUT->Get__VALUE();

			if(iActive__SIM_MODE > 0)
			{
				double sim_sec = cfg__timeout_sec / 2.0;
				if(sim_sec > 5.0)		sim_sec = 5.0;

				if(sim_sec <= x_asyc_timer->Get__CURRENT_TIME())
				{
					ch_data.Format("%.3f", cfg__ref_press + 1);
					sEXT_CH__SIM_PRESSURE_TORR->Set__DATA(ch_data);

					dEXT_CH__CHM_VAC_SNS->Set__DATA(STR__OFF);
					dEXT_CH__CHM_ATM_SNS->Set__DATA(STR__OFF);
				}
			}

			if(cfg__timeout_sec <= x_asyc_timer->Get__CURRENT_TIME())
			{
				x_asyc_timer->STOP();

				pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__SV_CLOSE);

				// ...
				{
					int alarm_id = ALID__SOFT_VENT_TIMEOUT;
					CString alm_msg;
					CString alm_bff;
					CString r_act;
				
					// ...
					{
						alm_bff.Format("Current chamber pressure is %.3f (torr).\n",  cur__chm_press);
						alm_msg += alm_bff;
					
						alm_bff.Format("Config soft-vent pressure is %.3f (torr).\n", cfg__ref_press);
						alm_msg += alm_bff;
					
						alm_bff.Format("Config soft-vent time-out is %.0f (sec).\n",  cfg__timeout_sec);
						alm_msg += alm_bff;
					}

					p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alm_msg,r_act);
	
					if(r_act.CompareNoCase(ACT__RETRY) == 0)
					{
						goto RETRY_LOOP;
					}
				}
				return -164;
			}

			Sleep(100);
		}
		while(1);

		x_asyc_timer->STOP();
		x_asyc_timer->START__COUNT_UP(99999);

		do
		{
			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				x_asyc_timer->STOP();
				return -163;
			}

			// VAC.SNS Check ...
			{
				double cur__chm_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();
				double cfg__ref_press = aCH__CFG_VAC_SNS_REF_PRESSURE->Get__VALUE();

				if(cur__chm_press < cfg__ref_press)
				{
					break;
				}

				if(dEXT_CH__CHM_VAC_SNS->Check__DATA(STR__OFF) > 0)
				{
					break;
				}
			}

			// Alarm Check ...
			double cfg__timeout_sec = aCH__CFG_SOFT_VENT_VAC_SNS_OFF_TIMEOUT->Get__VALUE();

			if(iActive__SIM_MODE > 0)
			{
				double sim_sec = cfg__timeout_sec / 2.0;
				if(sim_sec > 5.0)		sim_sec = 5.0;

				if(sim_sec <= x_asyc_timer->Get__CURRENT_TIME())
				{
					dEXT_CH__CHM_VAC_SNS->Set__DATA(STR__OFF);
					dEXT_CH__CHM_ATM_SNS->Set__DATA(STR__OFF);
				}
			}

			if(cfg__timeout_sec <= x_asyc_timer->Get__CURRENT_TIME())
			{	
				x_asyc_timer->STOP();

				pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__SV_CLOSE);

				// ...
				{
					int alarm_id = ALID__VACUUM_SNS_OFF_TIMEOUT;
					CString alm_msg;
					CString alm_bff;
					CString r_act;

					alm_bff.Format("Current Vacuum Sensor is %s.\n", dEXT_CH__CHM_VAC_SNS->Get__STRING());
					alm_msg += alm_bff;

					alm_bff.Format("Config Vacuum Sensor Off time-out is %.1f (sec).\n", cfg__timeout_sec);
					alm_msg += alm_bff;

					p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alm_msg, r_act);

					if(r_act.CompareNoCase(ACT__RETRY) == 0)
					{
						goto RETRY_LOOP;
					}
					return -164;
				}
			}

			Sleep(100);
		}
		while(1);
	}

	x_asyc_timer->STOP();

	// SOFT_VENT.OVER.TIME ...
	if(purge_flag < 0)
	{
		x_asyc_timer->START__COUNT_UP(9999);

		while(1)
		{
			Sleep(100);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -201;
			}

			double cfg__over_sec = aCH__CFG_SOFT_VENT_OVER_TIME->Get__VALUE();
			if(cfg__over_sec <= x_asyc_timer->Get__CURRENT_TIME())
			{
				break;
			}
		}
	}

	return pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__SV_CLOSE);
}

int CObj__CHM_FNC
::_Fnc__FAST_VENT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const int purge_flag)
{
	SCX__ASYNC_TIMER_CTRL x_asyc_timer;
	SCX__TIMER_CTRL timer_ctrl;

	timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);	

RETRY_LOOP:

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -171;
	}

	// ...
	CString ch_data;

	// Fast Vent ....
	{
		if(purge_flag < 0)		sCH__OBJ_MSG->Set__DATA("Fast Venting ...");
		else					sCH__OBJ_MSG->Set__DATA("Purge Fast Venting ...");

		x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
		x_asyc_timer->START__COUNT_UP(99999);
	
		if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__FV_OPEN) < 0)
		{
			CString log_msg;

			log_msg.Format("Seq__FAST_VENT - F/V Valve Open Failed");			
			xLOG_CTRL->WRITE__LOG(log_msg);

			x_asyc_timer->STOP();
			return -172;
		}

		do
		{
			if(p_variable->Check__CTRL_ABORT() > 0)	
			{
				x_asyc_timer->STOP();
				return -173;
			}

			if(dCH__CFG_FAST_VENT_GAUGE_CHECK->Check__DATA(STR__NO) > 0)
			{
				if((dEXT_CH__CHM_VAC_SNS->Check__DATA(STR__OFF) > 0)
				&& (dEXT_CH__CHM_ATM_SNS->Check__DATA(STR__ON)  > 0))
				{
					break;
				}
			}
			else
			{
				// Pressure Check ...
				double cfg__ref_press = 0;

				if(purge_flag < 0)		cfg__ref_press = aCH__CFG_FAST_VENT_PRESSURE->Get__VALUE();
				else					cfg__ref_press = aCH__CFG_PURGE_UP_PRESSURE->Get__VALUE();

				double cur__chm_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();

				if(cur__chm_press >= cfg__ref_press)
				{
					break;
				}
			}

			// Alarm Check ...
			double cfg__timeout_sec = aCH__CFG_FAST_VENT_TIMEOUT->Get__VALUE();

			if(iActive__SIM_MODE > 0)
			{
				double sim_sec = cfg__timeout_sec / 2.0;
				if(sim_sec > 10.0)		sim_sec = 10;

				if(sim_sec <= x_asyc_timer->Get__CURRENT_TIME())
				{
					double cfg__ref_press = 0;
					
					if(purge_flag < 0)		cfg__ref_press = aCH__CFG_FAST_VENT_PRESSURE->Get__VALUE();
					else					cfg__ref_press = aCH__CFG_PURGE_UP_PRESSURE->Get__VALUE();

					double cur__chm_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();

					ch_data.Format("%.1f", cfg__ref_press + 1.0);
					sEXT_CH__SIM_PRESSURE_TORR->Set__DATA(ch_data);

					dEXT_CH__CHM_VAC_SNS->Set__DATA(STR__OFF);
					dEXT_CH__CHM_ATM_SNS->Set__DATA(STR__ON);
				}
			}

			if(cfg__timeout_sec <= x_asyc_timer->Get__CURRENT_TIME())
			{
				x_asyc_timer->STOP();	

				pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__FV_CLOSE);

				// ...
				{
					int alarm_id = ALID__ATM_TIMEOUT;
					
					CString alm_msg;
					CString alm_bff;
					CString r_act;
				
					if(dCH__CFG_FAST_VENT_GAUGE_CHECK->Check__DATA(STR__NO) > 0)
					{
						alm_bff.Format("  * %s <- %s \n",
										dEXT_CH__CHM_VAC_SNS->Get__CHANNEL_NAME(),
										dEXT_CH__CHM_VAC_SNS->Get__STRING());
						alm_msg += alm_bff;

						alm_bff.Format("  * %s <- %s \n",
										dEXT_CH__CHM_ATM_SNS->Get__CHANNEL_NAME(),
										dEXT_CH__CHM_ATM_SNS->Get__STRING());
						alm_msg += alm_bff;
					}
					else
					{
						double cfg__ref_press = 0;

						if(purge_flag < 0)		cfg__ref_press = aCH__CFG_FAST_VENT_PRESSURE->Get__VALUE();
						else					cfg__ref_press = aCH__CFG_PURGE_UP_PRESSURE->Get__VALUE();

						double cur__chm_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();

						//
						alm_bff.Format("Current chamber pressure is %.3f (torr).\n", cur__chm_press);
						alm_msg += alm_bff;
				
						alm_bff.Format("Config ATM pressure is %.3f (torr).\n", cfg__ref_press);
						alm_msg += alm_bff;

						alm_bff.Format("Config ATM time-out is %.0f (sec).\n", cfg__timeout_sec);
						alm_msg += alm_bff;
					}

					p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alm_msg,r_act);

					if(r_act.CompareNoCase(ACT__RETRY) == 0)
					{
						goto RETRY_LOOP;
					}
				}
				return -174;
			}

			Sleep(100);
		}
		while(1);
	}

	x_asyc_timer->STOP();
	
	return 1;
}

int CObj__CHM_FNC
::Fnc__LEAK_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const bool active__ctc_call)
{
	CString log_msg;
	CString log_bff;

	CString alarm_msg;
	CString alarm_bff;
	
	double base_press_mtorr = 0.0;
	double pre_press_mtorr  = 0.0;
	double cur_press_mtorr  = 0.0;

	double total_leak_rate;
	double cur_leak_rate;

	double cfg_max_press_mtorr;
	double cfg_leak_rate;
	
	int i;

	// ...
	{
		sCH__LEAK_CHECK__START_PRESSURE_mTORR->Set__DATA("");

		sCH__LEAK_CHECK__APP_START_TIME->Set__DATA("");
		sCH__LEAK_CHECK__APP_END_TIME->Set__DATA("");

		sCH__LEAK_CHECK__CUR_TIME_COUNT->Set__DATA("");

		for(i=0;i<LEAK_CHECK__ITEM_SIZE;i++)
		{
			sCH__LEAK_CHECK__PRESSUREx_mTORR[i]->Set__DATA("");
			sCH__LEAK_CHECK__RATEx_mTORR_Per_MIN[i]->Set__DATA("");
		}

		sCH__LEAK_CHECK__RESULT_mTORR_Per_MIN->Set__DATA("");
	}

	// ...
	SCX__ASYNC_TIMER_CTRL async_timer;
	SCX__TIMER_CTRL timer_ctrl;
	double wait_sec;

	CString var_data;
	int flag;

	// ...
	{
		timer_ctrl->REGISTER__COUNT_CHANNEL(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
		timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
	}

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -1001;
	}

	// ...
	{
		if(bActive__OBJ_CTRL__TURBO_PUMP)
		{
			sCH__OBJ_MSG->Set__DATA("1.1 HIGH VAC PUMPING ...");

			flag = Call__HIGH_VAC_PUMP(p_variable,p_alarm);
		}
		else
		{
			sCH__OBJ_MSG->Set__DATA("1.1 LOW VAC PUMPING ...");

			flag = Call__LOW_VAC_PUMP(p_variable,p_alarm);
		}

		if(flag < 0)
		{
			return -1002;
		}
	}

	// ...
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1011;
		}

		// ...
		{
			sCH__OBJ_MSG->Set__DATA("1.2 OVER PUMPING ...");
			
			if(active__ctc_call)
			{
				wait_sec = aEXT_CH__CTC_LEAK_CHECK_OVER_PUMPING_TIME->Get__VALUE();
			}
			else
			{
				wait_sec = aCH__LEAK_CHECK__CFG_OVER_PUMPING_TIME->Get__VALUE();
			}
	
			if(timer_ctrl->WAIT(wait_sec) < 0)
			{
				return -1012;
			}
		}

		// ...
		{
			aEXT_CH__CHM_PRESSURE_mTORR->Get__DATA(var_data);
			sCH__LEAK_CHECK__BASE_PRESSURE_mTORR->Set__DATA(var_data);
		}
	}

	// ...
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1021;
		}

		sCH__OBJ_MSG->Set__DATA("2. VAC_Line All Close ...");

		if(Call__VAC_VLV__ALL_CLOSE(p_variable, p_alarm, false) < 0)
		{
			return -1022;
		}

		if(bActive__OBJ_CTRL__TURBO_PUMP)
		{
			if(Call__VAC_VLV__EXHAUST_OPEN(p_variable, p_alarm) < 0)
			{
				return -1023;
			}
		}

		timer_ctrl->WAIT(1.0);
	}

	// ...
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1031;
		}

		// ...
		sCH__OBJ_MSG->Set__DATA("3. STABLE TIME WAIT ...");

		if(active__ctc_call)
		{
			wait_sec = aEXT_CH__CTC_LEAK_CHECK_STABLE_TIME->Get__VALUE();
		}
		else
		{
			wait_sec = aCH__LEAK_CHECK__CFG_STABLE_TIME->Get__VALUE();
		}

		if(timer_ctrl->WAIT(wait_sec) < 0)
		{
			return -1032;
		}
	}

	// ...
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1041;
		}

		// ...
		{
			sCH__OBJ_MSG->Set__DATA("4. LEAK CHECK ...");

			// ...
			{
				CString str_date;
				CString str_time;
				
				Macro__Get_Date(str_date,str_time);

				log_msg.Format("%s_%s_-_Leak_Check_started_...", str_date,str_time);
				sCH__LEAK_CHECK__LOG_MESSAGE->Set__DATA(log_msg);
			}

			// ...
			double cur_press = aEXT_CH__CHM_PRESSURE_mTORR->Get__VALUE();
			
			var_data.Format("%.0f", cur_press);
			sCH__LEAK_CHECK__START_PRESSURE_mTORR->Set__DATA(var_data);
			sCH__LEAK_CHECK__LOG_START_PRESSURE_mTORR->Set__DATA(var_data);

			CString cur_month = Macro__Get_Month();
			sCH__LEAK_CHECK__APP_DATE_FDC_MONTH->Set__DATA(cur_month);

			CString cur_date = Macro__Get_Date();
			sCH__LEAK_CHECK__APP_START_TIME->Set__DATA(cur_date);
			sCH__LEAK_CHECK__APP_END_TIME->Set__DATA("Checking ...");

			sCH__LEAK_CHECK__CUR_TIME_COUNT->Set__DATA("0");
		}

		if(bActive__PMC_LOG)
		{
			xEXT_CH__PMC_LOG__SAMPLING_PERIOD->Set__DATA("10.0");
			
			int log_flag = pOBJ_CTRL__PMC_LOG->Call__OBJECT(CMMD__LOG_ENABLE_TIME);
			
			// ...
			{
				CString sub_dir;
				xEXT_CH__PMC_LOG__SUB_DIR->Get__DATA(sub_dir);

				// ...
				log_msg = "\n";

				log_bff  = "Logging Start ... \n";
				log_msg += log_bff;

				log_bff.Format("   1. Sub_Dir : [%s] \n", sub_dir);
				log_msg += log_bff;

				log_bff.Format("   2. Log Flag : [%1d] \n", log_flag);
				log_msg += log_bff;
	
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}

		// ...
		{
			double cfg__min_sec;

			if(active__ctc_call)		cfg__min_sec = aEXT_CH__CTC_LEAK_CHECK_TIME_MIN->Get__VALUE();
			else						cfg__min_sec = aCH__LEAK_CHECK__CFG_TIME_MIN->Get__VALUE();

			wait_sec = cfg__min_sec * 60.0;

			async_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__LEAK_CHECK__CUR_TIME_COUNT->Get__CHANNEL_NAME());
			async_timer->START__COUNT_UP(wait_sec+1.0);

			// ...
			base_press_mtorr = aEXT_CH__CHM_PRESSURE_mTORR->Get__VALUE();

			total_leak_rate = 0.0;
			cur_leak_rate   = 0.0;
	
			pre_press_mtorr = base_press_mtorr;

			// ...
			int i_limit = (int) cfg__min_sec;

			for(i=0; i<i_limit; i++)
			{
				if(bActive__PMC_LOG)
				{
					int log_flag = pOBJ_CTRL__PMC_LOG->Call__OBJECT(CMMD__LOG_STEP_START);

					log_msg = "\n";

					log_bff.Format("Step(%1d) Start ... \n", i+1);
					log_msg += log_bff;

					log_bff.Format("   1. Log_Flag : [%1d] \n", log_flag);
					log_msg += log_bff;
	
					xLOG_CTRL->WRITE__LOG(log_msg);
				}

				if(timer_ctrl->WAIT(60.0) < 0)
				{
					sCH__LEAK_CHECK__APP_END_TIME->Set__DATA("Aborted ...");
					async_timer->STOP();

					return -1042;
				}

				cfg_max_press_mtorr = aCH__LEAK_CHECK__MAX_PRESSURE_mTORR->Get__VALUE();
				cur_press_mtorr = aEXT_CH__CHM_PRESSURE_mTORR->Get__VALUE();

				if(cur_press_mtorr > cfg_max_press_mtorr)
				{
					// ...
					{
						int alarm_id = ALID__LEAK_CHECK_MAX_PRESSURE_ALARM;
						CString r_act;

						alarm_bff  = "During Leak Checking, Current Chamber Pressure is higher than config value. \n";
						alarm_msg += alarm_bff;

						alarm_bff.Format("  * Current Pressure : %.0f (mtorr) \n", cur_press_mtorr);
						alarm_msg += alarm_bff;

						alarm_bff.Format("  * Config Max. Pressure : %.0f (mtorr) \n", cfg_max_press_mtorr);
						alarm_msg += alarm_bff;

						alarm_bff.Format("Please, Check Chamber Pressure Status !!\n");
						alarm_msg += alarm_bff;

						p_alarm->Check__ALARM(alarm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alarm_msg);
					}
					return -1043;
				}

				// ...
				{
					total_leak_rate = (cur_press_mtorr - base_press_mtorr) / (i + 1);
				
					cur_leak_rate = (cur_press_mtorr - pre_press_mtorr);
					pre_press_mtorr = cur_press_mtorr;
				}
				
				if(i < LEAK_CHECK__ITEM_SIZE)
				{
					var_data.Format("%.0f", cur_press_mtorr);
					sCH__LEAK_CHECK__PRESSUREx_mTORR[i]->Set__DATA(var_data);
					sCH__LEAK_CHECK__LOG_PRESSURE_mTORR->Set__DATA(var_data);	

					var_data.Format("%.1f", cur_leak_rate);
					sCH__LEAK_CHECK__RATEx_mTORR_Per_MIN[i]->Set__DATA(var_data);
					sCH__LEAK_CHECK__LOG_RATE_mTORR_Per_MIN->Set__DATA(var_data);

					// ...
					{
						log_msg = "\n";

						log_bff.Format("Step(%1d) Result ... \n", i+1);
						log_msg += log_bff;

						log_bff.Format("   1. cur_press_mtorr    : [%.0f] mtorr \n", cur_press_mtorr); 
						log_msg += log_bff;

						log_bff.Format("   2. base_press_mtorr   : [%.0f] mtorr \n", base_press_mtorr); 
						log_msg += log_bff;

						log_bff.Format("   3. result_press_mtorr : [%.0f] mtorr \n", (cur_press_mtorr - base_press_mtorr)); 
						log_msg += log_bff;

						log_bff.Format("   4. leak_rate          : [%.0f] mtorr / min \n", cur_leak_rate); 
						log_msg += log_bff;
						
						xLOG_CTRL->WRITE__LOG(log_msg);
					}
				}

				// ...
				{
					log_msg.Format("Result(%1d)_:_(%.1f)(mtorr/min)_<-_(%.0f-%.0f)/(%1d)", 
						           (i+1),
								   cur_leak_rate,
								   cur_press_mtorr,
								   base_press_mtorr,
								   (i+1));

					sCH__LEAK_CHECK__LOG_MESSAGE->Set__DATA(log_msg);
				}

				if(bActive__PMC_LOG)
				{
					int log_flag = pOBJ_CTRL__PMC_LOG->Call__OBJECT(CMMD__LOG_STEP_END);

					log_msg = "\n";

					log_bff.Format("Step(%1d) End ... \n", i+1);
					log_msg += log_bff;

					log_bff.Format("   1. Log_Flag : [%1d] \n", log_flag);
					log_msg += log_bff;

					xLOG_CTRL->WRITE__LOG(log_msg);
				}
			}

			sCH__LEAK_CHECK__APP_END_TIME->Set__DATA(Macro__Get_Date());

			// ...
			{
				var_data.Format("%.1f", total_leak_rate);
				sCH__LEAK_CHECK__RESULT_mTORR_Per_MIN->Set__DATA(var_data);
				sCH__LEAK_CHECK__LOG_RESULT_mTORR_Per_MIN->Set__DATA(var_data);
			}

			// ...
			{
				log_msg.Format("Total_Result_:_(%.1f)_(mtorr/min)", 
						       total_leak_rate);

				sCH__LEAK_CHECK__LOG_MESSAGE->Set__DATA(log_msg);
			}
		}

		if(bActive__PMC_LOG)
		{
			int log_flag = pOBJ_CTRL__PMC_LOG->Call__OBJECT(CMMD__LOG_DISABLE);

			// ...
			{
				log_msg = "\n";

				log_bff  = "Logging End ... \n";
				log_msg += log_bff;

				log_bff.Format("   1. Log Flag : [%1d] \n", log_flag);
				log_msg += log_bff;

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}

		// ...
		{
			aCH__LEAK_CHECK__CFG_RESULT_POSTING->Get__DATA(var_data);
			cfg_leak_rate = atof(var_data);

			if(total_leak_rate > cfg_leak_rate)
			{
				int alarm_id = ALID__LEAK_CHECK_RESULT_ALARM;
				CString r_act;

				alarm_bff  = "After Leak Checking, Leak Rate is higher than config value.\n";
				alarm_msg += alarm_bff;
				
				alarm_bff.Format("  * Leak Rate Result : %.1f \n",   total_leak_rate);
				alarm_msg += alarm_bff;

				alarm_bff.Format("  * Config Leak Rate : %.1f \n\n", cfg_leak_rate);
				alarm_msg += alarm_bff;

				alarm_bff.Format("Please, Check Chamber Pressure Status !!\n");
				alarm_msg += alarm_bff;

				p_alarm->Check__ALARM(alarm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alarm_msg);
			}
		}
	
		async_timer->STOP();
	}

	// Leak Check Datalog ...
	{
		CString log_msg;
		CString log_bff;

		CString var_data;
		int i;

		// ...
		{
			log_msg  = "#LOG_INFO	START";
			log_msg += "\n"; 

			// ...
			{
				if(active__ctc_call)		aEXT_CH__CTC_LEAK_CHECK_OVER_PUMPING_TIME->Get__DATA(var_data);		
				else						aCH__LEAK_CHECK__CFG_OVER_PUMPING_TIME->Get__DATA(var_data);

				log_bff.Format("#OVER_PUMPING_TIME	%s", var_data);
				log_msg += log_bff;
				log_msg += "\n";
			}

			// ...
			{
				if(active__ctc_call)		aEXT_CH__CTC_LEAK_CHECK_STABLE_TIME->Get__DATA(var_data);			
				else						aCH__LEAK_CHECK__CFG_STABLE_TIME->Get__DATA(var_data);

				log_bff.Format("#STABLE_TIME	%s", var_data);
				log_msg += log_bff;
				log_msg += "\n";
			}

			// ...
			sCH__LEAK_CHECK__BASE_PRESSURE_mTORR->Get__DATA(var_data);
			log_bff.Format("#BASE_PRESSURE	%s", var_data);
			log_msg += log_bff;
			log_msg += "\n";

			sCH__LEAK_CHECK__START_PRESSURE_mTORR->Get__DATA(var_data);
			log_bff.Format("#START_PRESSURE	%s", var_data);
			log_msg += log_bff;
			log_msg += "\n";

			sCH__LEAK_CHECK__APP_START_TIME->Get__DATA(var_data);
			log_bff.Format("#START_TIME	%s", var_data);
			log_msg += log_bff;
			log_msg += "\n";

			sCH__LEAK_CHECK__APP_END_TIME->Get__DATA(var_data);
			log_bff.Format("#END_TIME	%s", var_data);
			log_msg += log_bff;
			log_msg += "\n";
			
			for(i=0;i<LEAK_CHECK__ITEM_SIZE;i++)
			{
				sCH__LEAK_CHECK__PRESSUREx_mTORR[i]->Get__DATA(var_data);
				log_bff.Format("#%1d.RESULT_PRESSURE	%s", i+1,var_data);
				log_msg += log_bff;
				log_msg += "\n";

				sCH__LEAK_CHECK__RATEx_mTORR_Per_MIN[i]->Get__DATA(var_data);
				log_bff.Format("#%1d.RESULT_RATE	%s", i+1,var_data);
				log_msg += log_bff;
				log_msg += "\n";
			}
			
			sCH__LEAK_CHECK__RESULT_mTORR_Per_MIN->Get__DATA(var_data);
			log_bff.Format("#TOTAL_RESULT	%s", var_data);
			log_msg += log_bff;
			log_msg += "\n";
		}

		// ...
		{
			SCX__SEQ_INFO x_seq_info;

			CString dir_root;
			CString sub_dir;
			CString dir_log;
			CString path_log;

			// LEAK_CHECK_LOG ...
			{
				x_seq_info->Get__DIR_ROOT(dir_root);
				sub_dir = "LEAK_CHECK_LOG";
				sub_dir += "\\";

				dir_log  = dir_root;
				dir_log += "\\";
				dir_log += sub_dir;

				x_seq_info->Create__DIR(dir_log);
			}

			// LEAK_CHECK_LOG/DATE ...
			{
				int i_year,i_mon,i_day;
				x_seq_info->Get__DAY(i_year,i_mon,i_day);
	
				sub_dir.Format("%00004d_%002d_%002d", i_year,i_mon,i_day);
				sub_dir += "\\";
				
				dir_log += sub_dir;
				
				x_seq_info->Create__DIR(dir_log);
			}

			// LEAK_CHECK_LOG/DATE/TIME-Result.log ...
			{
				int i_hour,i_min,i_sec,i_msec;
				x_seq_info->Get__TIME(i_hour,i_min,i_sec,i_msec);
				
				sub_dir.Format("Result-%002d%002d%002d.log", i_hour,i_min,i_sec);
				
				path_log.Format("%s\\%s", dir_log,sub_dir);				
			}

			// ...
			{
				FILE *p_log = fopen(path_log,"w");

				if(p_log != NULL)
				{
					fputs(log_msg, p_log);
					fclose(p_log);
				}
			}

			// ...
			{
				SCX__FILE_CTRL x_file_ctrl;
				CString check_dir;

				check_dir.Format("%s\\%s\\", dir_root,"LEAK_CHECK_LOG");

				x_file_ctrl->Delete__LOG_DIR(check_dir,30);
			}
		}
	}

	return 1;
}

int CObj__CHM_FNC::
Fnc__LEAK_CHECK__VAT_VLV_POS_MOVE(CII_OBJECT__VARIABLE *p_variable,
								  CII_OBJECT__ALARM *p_alarm,
								  const bool active__ctc_call)
{
	CString log_msg;
	CString log_bff;

	CString alarm_msg;
	CString alarm_bff;
	
	double start_press_mtorr = 0.0;
	double cur_press_mtorr   = 0.0;
	
	int i;
	
	// ...
	{
		sCH__LEAK_CHECK__VAT_MOVE__START_PRESSURE_mTORR->Set__DATA("");
		sCH__LEAK_CHECK__VAT_MOVE__RESULT_PRESSURE_mTORR->Set__DATA("");
	}

	// ...
	SCX__ASYNC_TIMER_CTRL async_timer;
	SCX__TIMER_CTRL timer_ctrl;
	double wait_sec;

	CString var_data;
	int flag;

	// ...
	{
		timer_ctrl->REGISTER__COUNT_CHANNEL(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
		timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
	}

	// Pumping ...
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -2001;
		}

		if(bActive__OBJ_CTRL__TURBO_PUMP)
		{
			sCH__OBJ_MSG->Set__DATA("1.1 HIGH.VAC PUMPING ...");
	
			flag = Call__HIGH_VAC_PUMP(p_variable, p_alarm);

			if(flag < 0)		return -2002;
		}
		else
		{
			sCH__OBJ_MSG->Set__DATA("1.1 LOW.VAC PUMPING ...");

			flag = Call__LOW_VAC_PUMP(p_variable, p_alarm);

			if(flag < 0)		return -2002;
		}
	}

	// OVER.PUMPING ...
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -2011;
		}

		// ...
		{
			sCH__OBJ_MSG->Set__DATA("1.2 OVER PUMPING ...");

			if(active__ctc_call)		wait_sec = aEXT_CH__CTC_LEAK_CHECK_OVER_PUMPING_TIME->Get__VALUE();
			else						wait_sec = aCH__LEAK_CHECK__CFG_OVER_PUMPING_TIME->Get__VALUE();
	
			if(timer_ctrl->WAIT(wait_sec) < 0)
			{
				return -2012;
			}
		}
	}

	// VAT.OPEN ...
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -2021;
		}
	
		sCH__OBJ_MSG->Set__DATA("2. TH/V OPEN ...");
	
		if(Call__VAC_VLV__APC_OPEN() < 0)
		{
			return -2022;
		}

		timer_ctrl->WAIT(1.0);
	}

	// STABLE.TIME ...
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -2031;
		}

		// ...
		sCH__OBJ_MSG->Set__DATA("3. STABLE TIME WAIT ...");

		if(active__ctc_call)		wait_sec = aEXT_CH__CTC_LEAK_CHECK_STABLE_TIME->Get__VALUE();
		else						wait_sec = aCH__LEAK_CHECK__CFG_STABLE_TIME->Get__VALUE();
			
		if(timer_ctrl->WAIT(wait_sec) < 0)
		{
			return -2032;
		}
	}

	// LEAK.CHECK START ...
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -2041;
		}

		sCH__OBJ_MSG->Set__DATA("4. LEAK CHECK - VAT Position Moving ...");

		// ...
		{
			start_press_mtorr = aEXT_CH__CHM_PRESSURE_mTORR->Get__VALUE();
			
			var_data.Format("%.3f", start_press_mtorr);
			sCH__LEAK_CHECK__VAT_MOVE__START_PRESSURE_mTORR->Set__DATA(var_data);
	
			// ...
			int i_limit = 9;

			for(i=0; i<i_limit; i++)
			{
				double apc__trg_pos = 90.0 - (i * 10.0);				

				// VAT-POS Move ...
				if(Call__VAC_VLV__APC_POSITION(apc__trg_pos) < 0)
				{
					return -2051;
				}

				// ...
				double wait_sec = 60.0;

				async_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__LEAK_CHECK__CUR_TIME_COUNT->Get__CHANNEL_NAME());
				async_timer->START__COUNT_UP(wait_sec + 1.0);

				timer_ctrl->INIT__COUNT_DOWN();
				if(timer_ctrl->WAIT(wait_sec) < 0)
				{
					async_timer->STOP();
					return -2052;
				}

				// ...
				cur_press_mtorr = aEXT_CH__CHM_PRESSURE_mTORR->Get__VALUE();

				var_data.Format("%.3f", cur_press_mtorr);
				sCH__LEAK_CHECK__VAT_MOVE__RESULT_PRESSURE_mTORR->Set__DATA(var_data);

				if(cur_press_mtorr > start_press_mtorr)	
				{
					// ...
					{
						int alarm_id = ALID__LEAK_CHECK__VAT_MOVE__START_PRESSURE_OVER;
						CString r_act;

						// ...
						{
							alarm_msg = "";

							alarm_bff.Format("시작 압력은 \"%.3f mtorr\" 였습니다. \n", start_press_mtorr);
							alarm_msg += alarm_bff;

							alarm_bff.Format("현재 압력은 \"%.3f mtorr\" 입니다. \n", cur_press_mtorr);
							alarm_msg += alarm_bff;

							alarm_bff.Format("현재 Checking Time은 \"%1d min\" 입니다. \n", i+1);
							alarm_msg += alarm_bff;
							
							alarm_bff.Format("현재 VAT-Position은 \"%.1f %%\" 입니다. \n", apc__trg_pos);
							alarm_msg += alarm_bff;
						}

						p_alarm->Check__ALARM(alarm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alarm_msg);
					}
					return -2053;
				}
			}
		}
	
		async_timer->STOP();
	}

	if(bActive__OBJ_CTRL__TURBO_PUMP)
	{
		return Call__HIGH_VAC_PUMP(p_variable,p_alarm);
	}
	return Call__LOW_VAC_PUMP(p_variable,p_alarm);
}


// ...
int CObj__CHM_FNC
::Fnc__PURGE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	int ref_cycle_count = (int) aCH__CFG_PURGE_CYCLE_COUNT->Get__VALUE();
	int i;

	for(i=0; i<ref_cycle_count; i++)
	{
		ch_data.Format("%1d", i+1);
		sCH__CUR_PURGE_CYCLE_COUNT->Set__DATA(ch_data);

		// PUMPING 
		if(i == 0)
		{
			if(p_variable->Check__CTRL_ABORT() > 0)			return -11;

			if(Seq__PURGE_PUMP(p_variable,p_alarm,i) < 0)	return -12;
		}

		// VENTING
		{
			if(p_variable->Check__CTRL_ABORT() > 0)			return -21;

			if(Seq__PURGE_VENT(p_variable,p_alarm) < 0)		return -22;
		}

		// PUMPING
		{
			if(p_variable->Check__CTRL_ABORT() > 0)			return -31;

			if(Seq__PURGE_PUMP(p_variable,p_alarm,i) < 0)	return -32;
		}
	}

	return 1;
}

/*
int CObj__CHM_FNC
::Fnc__PURGE_PUMP(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	CString var_data;
	int ref_cycle_count;
	int i;

	aCH__CFG_NUM_PPCYCLE_WITH_PUMP->Get__DATA(var_data);
	ref_cycle_count = atoi(var_data);

	for(i=0;i<ref_cycle_count;i++)
	{
		var_data.Format("%1d",i+1);
		aCH__PURGE_CURRENT_COUNT->Set__DATA(var_data);

		// VENTING
		{
			if(p_variable->Check__CTRL_ABORT() > 0)			return -1;

			if(Seq__PURGE_VENT(p_variable,p_alarm) < 0)		return -1;
		}

		// PUMPING
		{
			if(p_variable->Check__CTRL_ABORT() > 0)			return -1;

			if(Seq__PURGE_PUMP(p_variable,p_alarm,i) < 0)	return -1;
		}
	}

	return 1;
}
int CObj__CHM_FNC
::Fnc__PURGE_VENT(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	CString var_data;
	int ref_cycle_count;
	int i;

	aCH__CFG_NUM_PPCYCLE_WITH_VENT->Get__DATA(var_data);
	ref_cycle_count = atoi(var_data);

	for(i=0;i<ref_cycle_count;i++)
	{
		var_data.Format("%1d",i+1);
		aCH__PURGE_CURRENT_COUNT->Set__DATA(var_data);

		// VENTING
		{
			if(p_variable->Check__CTRL_ABORT() > 0)			return -1;

			if(Seq__PURGE_VENT(p_variable,p_alarm) < 0)		return -1;
		}

		// PUMPING
		{
			if(p_variable->Check__CTRL_ABORT() > 0)			return -1;

			if(Seq__PURGE_PUMP(p_variable,p_alarm,i) < 0)	return -1;
		}
	}

	return 1;
}
*/

int CObj__CHM_FNC
::Seq__PURGE_VENT(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;
	int flag;

	CString str_data;
	SCX__TIMER_CTRL timer_ctrl;

	timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);

	// ...
	double dbl_Add_Purgetime_for_PP = 0;

	// ...
	{
		flag = Fnc__VENT(p_variable,p_alarm,1);		// Purge Venting
	
		Fnc__ALL_GAS_LINE_CLOSE(p_variable, p_alarm);

		if(flag < 0)
		{
			// ...
			{
				log_msg.Format("Seq__PURGE_VENT : Fnc__VENT - Failed (%d) ...", flag);	
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			return flag;
		}
	}

	// ...
	{
		flag = Fnc__ALL_GAS_LINE_CLOSE(p_variable, p_alarm);
	
		if(flag < 0)
		{
			// ...
			{
				log_msg.Format("Seq__PURGE_VENT : Fnc__ALL_GAS_LINE_CLOSE - Failed (%d) ...", flag);	
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			return flag;
		}
	}

	// ... 
	{
		aCH__CFG_ADD_PURGE_TIME_SECONDS_FOR_PP->Get__DATA(str_data);
		dbl_Add_Purgetime_for_PP = atof(str_data);

		if(timer_ctrl->WAIT(dbl_Add_Purgetime_for_PP) < 0)
		{
			return -1;
		}
	}

	return 1;
}

int CObj__CHM_FNC
::Seq__PURGE_PUMP(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm,
				  const int cycle_count)
{
	CString log_msg;
	int flag;

	// ...
	SCX__TIMER_CTRL timer_ctrl;
	timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);

	// ...
	CString str_data;
	double dbl_Add_Pumptime_for_PP = 0;

	// ...
	{
		flag = Fnc__LOW_VAC_PUMP(p_variable,p_alarm,1,1);

		if(flag < 0)
		{
			log_msg.Format("Seq__PURGE_PUMP : Fnc__HIGH_VAC_PUMP - Failed (%d) ...", flag);	
			xLOG_CTRL->WRITE__LOG(log_msg);

			return flag;
		}
	}

	// ... 
	{
		aCH__CFG_ADD_PUMP_TIME_SECONDS_FOR_PP->Get__DATA(str_data);
		dbl_Add_Pumptime_for_PP = atof(str_data);

		if(timer_ctrl->WAIT(dbl_Add_Pumptime_for_PP) < 0)
		{
			return -1;
		}
	}

	return 1;
}

int CObj__CHM_FNC
::Fnc__VENT_COMPLETE(CII_OBJECT__VARIABLE *p_variable,
					 CII_OBJECT__ALARM *p_alarm)
{
	SCX__ASYNC_TIMER_CTRL x_asyc_timer;

RETRY_LOOP:

	// ...
	{
		double  ref_timeout;
		CString var_data;
		
		x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
		x_asyc_timer->START__COUNT_UP(9999);

		if(iActive__SIM_MODE > 0)
		{
			dEXT_CH__CHM_VAC_SNS->Set__DATA(STR__OFF);
			dEXT_CH__CHM_ATM_SNS->Set__DATA(STR__ON);
		}

		int count__atm_sns = 0;

		do
		{
			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -1;
			}

			if((dEXT_CH__CHM_VAC_SNS->Check__DATA(STR__OFF) > 0)
			&& (dEXT_CH__CHM_ATM_SNS->Check__DATA(STR__ON)  > 0))
			{
				if(count__atm_sns < 5)
				{
					count__atm_sns++;
				}
				else
				{
					count__atm_sns = 0;
					break;
				}
			}
			else
			{
				count__atm_sns = 0;
			}
			
			// ...
			aCH__CFG_FAST_VENT_ATM_SNS_ON_TIMEOUT->Get__DATA(var_data);
			ref_timeout = atof(var_data);
			
			if(ref_timeout <= x_asyc_timer->Get__CURRENT_TIME())
			{
				int alarm_id = ALID__VENT_CHECK_COMPLETE_TIMEOUT;
				CString alarm_msg;
				CString msg_bff;
				CString r_act;
				
				double ref_press;
				double cur_press;
				
				ref_press = aCH__CFG_SOFT_VENT_PRESSURE->Get__VALUE();
				cur_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();
				
				CString var_sns_data = dEXT_CH__CHM_ATM_SNS->Get__STRING();

				msg_bff.Format("Current chamber's ATM Sensor is %s.\n", var_sns_data);
				alarm_msg += msg_bff;
				msg_bff.Format("Config time-out is %.0f (sec).\n", ref_timeout);
				alarm_msg += msg_bff;
				
				// Vent Gas Valve Close ... Interlock Add
				x_asyc_timer->STOP();

				if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD_GAS__FV_CLOSE) < 0)
				{
					pOBJ_CTRL__GAS_VLV->Dislink__UPPER_OBJECT();
					return -201;
				}
				
				p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alarm_msg,r_act);
				
				if(r_act.CompareNoCase(ACT__RETRY) == 0)
				{
					goto RETRY_LOOP;
				}
				return -202;
			}

			Sleep(100);
		} 
		while(1);
	}
	
	x_asyc_timer->STOP();
	return 1;
}

int CObj__CHM_FNC
::Fnc__TRANS_BALLAST_START(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	CString log_bff;

	if(dCH__CFG_TRANSFER_BALLAST_ENABLED->Check__DATA(STR__YES) < 0)
	{
		// ...
		{
			log_msg = "Fnc__TRANS_BALLAST_START() : ENABLED.NO ... \n";
			log_bff.Format(" * %s <- %s \n", 
							dCH__CFG_TRANSFER_BALLAST_ENABLED->Get__CHANNEL_NAME(),
							dCH__CFG_TRANSFER_BALLAST_ENABLED->Get__STRING());
			log_msg += log_bff;
		
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		Fnc__BALLAST_END(p_variable, p_alarm);
		return 1;
	}
	else
	{
		log_msg.Format("Fnc__TRANS_BALLAST_START() ...");

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	//=================================================================
	bool active_xfer = true;

	//	1. Chamber Ballast User Config Check
	//	2. APC Valve OPEN
	//  3. Ballast MFC Flow
	//  4. APC Ballast Pressure Control

	// APC.OPEN ...
	if(Call__VAC_VLV__APC_OPEN() < 0)
	{
		log_msg = " * APC-OPEN is Aborted ...";

		xLOG_CTRL->WRITE__LOG(log_msg);
		return -11;
	}

	// GAS.FLOW - START ...
	if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD__TRANS_BALLAST_FLOW) < 0)
	{
		log_msg = " * Gas Ballast-Flow is Aborted ... ";

		xLOG_CTRL->WRITE__LOG(log_msg);
		return -21;
	}

	// APC.BALLAST_POS - START ...
	if(Call__VAC_VLV__APC_BALLAST_CTRL(active_xfer) < 0)
	{
		log_msg = " * APC Ballast-Control is Aborted ... ";

		xLOG_CTRL->WRITE__LOG(log_msg);
		return -31;
	}

	return 1;
}
int CObj__CHM_FNC
::Fnc__CHM_BALLAST_START(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	CString log_bff;

	if(dCH__CFG_CHAMBER_BALLAST_ENABLED->Check__DATA(STR__YES) < 0)
	{
		// ...
		{
			log_msg = "Fnc__CHM_BALLAST_START() : ENABLED.NO ... \n";
			log_bff.Format(" * %s <- %s \n", 
							dCH__CFG_CHAMBER_BALLAST_ENABLED->Get__CHANNEL_NAME(),
							dCH__CFG_CHAMBER_BALLAST_ENABLED->Get__STRING());
			log_msg += log_bff;

			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		Fnc__BALLAST_END(p_variable, p_alarm);
		return 1;
	}
	else
	{
		log_msg = "Fnc__CHM_BALLAST_START() ...";
		
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	//=================================================================
	bool active_xfer = false;

	//	1. Chamber Ballast User Config Check
	//	2. APC Valve OPEN
	//  3. Ballast MFC Flow
	//  4. APC Ballast Pressure Control
	
	// APC.OPEN ...
	if(Call__VAC_VLV__APC_OPEN() < 0)
	{
		log_msg = " * APC-OPEN is Failed ... ";
			
		xLOG_CTRL->WRITE__LOG(log_msg);
		return -11;
	}

	// CHAMBER.BALLAST FLOW ...
	if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD__CHM_BALLAST_FLOW) < 0)
	{
		log_msg = " * Gas Ballast-Flow is Aborted ... ";

		xLOG_CTRL->WRITE__LOG(log_msg);
		return -21;
	}

	// APC.BALLAST POST ...
	if(Call__VAC_VLV__APC_BALLAST_CTRL(active_xfer) < 0)
	{
		log_msg = " * APC Ballast-Control is Aborted ... ";

		xLOG_CTRL->WRITE__LOG(log_msg);
		return -31;
	}

	return 1;
}

int CObj__CHM_FNC
::Fnc__BALLAST_END(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(dEXT_CH__SYSTEM_TRANSFER_MODE->Check__DATA(STR__ATM) > 0)
	{
		return 11;
	}

	// ...
	CString log_msg;

	// ...
	{
		log_msg = " * Fnc__BALLAST_END() ... ";
		
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	//=================================================================
	//	1. Chamber Ballast User Config Check
	//	2. APC Valve OPEN
	//  3. Ballast MFC Close

	sCH__TRANSFER_BALLAST_FLAG->Set__DATA("");

	if(Call__VAC_VLV__APC_OPEN() < 0)
	{
		return -11;
	}

	if(pOBJ_CTRL__GAS_VLV->Call__OBJECT(CMMD__BALLAST_CLOSE) < 0)
	{
		return -21;
	}

	return 1;
}

