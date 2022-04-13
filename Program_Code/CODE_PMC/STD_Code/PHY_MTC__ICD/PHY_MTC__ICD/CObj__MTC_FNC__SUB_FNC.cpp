#include "StdAfx.h"
#include "CObj__MTC_FNC.h"
#include "CObj__MTC_FNC__DEF.h"
#include "CObj__MTC_FNC__ALID.h"

#include "Macro_Function.h"


// ...
int CObj__MTC_FNC
::Fnc__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(iActive__SIM_MODE  > 0)
	{
		double cur__press_torr = aCH__MTC_PRESSURE_TORR->Get__VALUE();
		
		if(cur__press_torr >= 740)
		{
			dEXT_CH__DI_MTC_VAC_SNS->Set__DATA(STR__OFF);
			dEXT_CH__DI_MTC_ATM_SNS->Set__DATA(STR__ON);
			dEXT_CH__DO_MTC_CHECK_VV->Set__DATA(STR__OPEN);
		}
		else
		{
			dEXT_CH__DI_MTC_VAC_SNS->Set__DATA(STR__ON);
			dEXT_CH__DI_MTC_ATM_SNS->Set__DATA(STR__OFF);
			dEXT_CH__DO_MTC_CHECK_VV->Set__DATA(STR__CLOSE);
		}
 
 		dEXT_CH__DI_MTC_GATE_CLOSE_SNS->Set__DATA(STR__ON);
		dEXT_CH__DI_MTC_GATE_OPEN_SNS->Set__DATA(STR__OFF);
	}	

	return 1;
}

int CObj__MTC_FNC
::Fnc__GATE_CTL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm, const bool bOpen)
{
	CString log_msg;

	// Gate Open ...
	if(bOpen)
	{
		// Gate Open Interlock Checking ...
		{
			int Interlock_Check = 1;

			// CHM PRESSURE SNS
			if((dEXT_CH__DI_CHM_VAC_SNS->Check__DATA(STR__OFF) > 0) 
			|| (dEXT_CH__DI_CHM_ATM_SNS->Check__DATA(STR__ON) > 0))
			{
				Interlock_Check = -11;
			}

			// MTC PRESSURE SNS
			if((dEXT_CH__DI_MTC_VAC_SNS->Check__DATA(STR__OFF) > 0) 
			|| (dEXT_CH__DI_MTC_ATM_SNS->Check__DATA(STR__ON) > 0))
			{
				Interlock_Check = -12;
			}

			if(Interlock_Check < 0) 
			{
				return Interlock_Check;
			}
		}
		
		// Gate Open IO Set ...
		{
			log_msg = "MTC_Gate <- Open";
			xLOG_CTRL->WRITE__LOG(log_msg);

			dEXT_CH__DO_MTC_GATE_CLOSE->Set__DATA(STR__OFF);
			dEXT_CH__DO_MTC_GATE_OPEN->Set__DATA(STR__ON);
		}

		// Gate Sequence Check ...
		{
			SCX__ASYNC_TIMER_CTRL x_asyc_timer;

			x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
			x_asyc_timer->START__COUNT_UP(99999);

			do 
			{
				if(p_variable->Check__CTRL_ABORT() > 0)	
				{
					return -14;
				}

				// Gate Open SNS Check...
				{
					if((dEXT_CH__DI_MTC_GATE_OPEN_SNS->Check__DATA(STR__ON)   > 0) 
					&& (dEXT_CH__DI_MTC_GATE_CLOSE_SNS->Check__DATA(STR__OFF) > 0)) 
					{
						break;
					}
				}

				// Time-Out
				{
					double cfg_sec = aCH__CFG_GATE_VLV_OPEN_TIMEOUT->Get__VALUE();

					if(iActive__SIM_MODE  > 0)
					{
						if(x_asyc_timer->Get__CURRENT_TIME() >= 1.0)
						{
							dEXT_CH__DI_MTC_GATE_OPEN_SNS->Set__DATA(STR__ON);
							dEXT_CH__DI_MTC_GATE_CLOSE_SNS->Set__DATA(STR__OFF);
						}
					}

					if(x_asyc_timer->Get__CURRENT_TIME() >= cfg_sec)
					{
						return -15;
					}
				}

				Sleep(100);
			} 
			while (1);
		}
	}
	// Gate Close ...
	else
	{
		// Gate Close IO Set ...
		{
			log_msg = "MTC_Gate <- Close";
			xLOG_CTRL->WRITE__LOG(log_msg);

			dEXT_CH__DO_MTC_GATE_CLOSE->Set__DATA(STR__ON);
			dEXT_CH__DO_MTC_GATE_OPEN->Set__DATA(STR__OFF);
		}

		// Gate Sequence Check ...
		{
			SCX__ASYNC_TIMER_CTRL x_asyc_timer;

			x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
			x_asyc_timer->START__COUNT_UP(99999);

			do 
			{
				if(p_variable->Check__CTRL_ABORT() > 0)	
				{
					return -16;
				}

				// Gate Open SNS Check...
				{
					if((dEXT_CH__DI_MTC_GATE_OPEN_SNS->Check__DATA(STR__OFF) > 0) 
					&& (dEXT_CH__DI_MTC_GATE_CLOSE_SNS->Check__DATA(STR__ON) > 0)) 
					{
						break;
					}
				}

				// Time-Out
				{
					double cfg_sec = aCH__CFG_GATE_VLV_CLOSE_TIMEOUT->Get__VALUE();

					if(iActive__SIM_MODE  > 0)
					{
						if(x_asyc_timer->Get__CURRENT_TIME() >= 1.0)
						{
							dEXT_CH__DI_MTC_GATE_OPEN_SNS->Set__DATA(STR__OFF);
							dEXT_CH__DI_MTC_GATE_CLOSE_SNS->Set__DATA(STR__ON);
						}
					}

					if(x_asyc_timer->Get__CURRENT_TIME() >= cfg_sec)
					{
						return -15;
					}
				}

				Sleep(100);
			} 
			while (1);
		}
	}

	return 1;
}

int CObj__MTC_FNC
::Fnc__SOFT_PUMPING(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	// PRESSURE CHECK ...
	{
		double cfg_press = aCH__CFG_SOFT_PUMP_PRESSURE->Get__VALUE();
		double cur_press = aCH__MTC_PRESSURE_TORR->Get__VALUE();

		if((dEXT_CH__DI_MTC_ATM_SNS->Check__DATA(STR__OFF) > 0) 
		&& (dEXT_CH__DI_MTC_VAC_SNS->Check__DATA(STR__ON)  > 0) 
		&& (cur_press <= cfg_press))
		{
			return 1;
		}
	}

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -10;
	}

	// SOFT_PUMPING DO SET ...
	{
		CString log_msg = "Soft-Pumping ...";
		sCH__OBJ_MSG->Set__DATA(log_msg);

		//
		dEXT_CH__DO_MTC_2STAGE_SLOW->Set__DATA(STR__OPEN);
		dEXT_CH__DO_MTC_2STAGE_FAST->Set__DATA(STR__CLOSE);
	}

	// ...
	SCX__ASYNC_TIMER_CTRL x_asyc_timer;

	x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
	x_asyc_timer->START__COUNT_UP(99999);

	do 
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -11;
		}

		// Soft-Pump Press Check ...
		{
			double cfg_press = aCH__CFG_SOFT_PUMP_PRESSURE->Get__VALUE();
			double cur_press = aCH__MTC_PRESSURE_TORR->Get__VALUE();

			if((dEXT_CH__DI_MTC_ATM_SNS->Check__DATA(STR__OFF) > 0)
			&& (cur_press <= cfg_press))
			{
				break;
			}

			// Time-Out
			{
				double cfg_sec = aCH__CFG_SOFT_PUMP_TIMEOUT->Get__VALUE();

				if(iActive__SIM_MODE > 0)
				{
					if(x_asyc_timer->Get__CURRENT_TIME() >= 5.0)
					{
						aCH__MTC_PRESSURE_SIM_MODE->Set__VALUE(cfg_press);

						dEXT_CH__DI_MTC_ATM_SNS->Set__DATA(STR__OFF);
					}
				}

				if(x_asyc_timer->Get__CURRENT_TIME() > cfg_sec)
				{
					return -17;
				}
			}
		}

		Sleep(100);
	} 
	while (1);
	
	return 1;
}

int CObj__MTC_FNC
::Fnc__FAST_PUMPING(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	// FAST_PUMPING DO SET ...
	{
		CString log_msg = "Fast-Pumping ...";
		sCH__OBJ_MSG->Set__DATA(log_msg);

		//
		dEXT_CH__DO_MTC_2STAGE_SLOW->Set__DATA(STR__CLOSE);
		dEXT_CH__DO_MTC_2STAGE_FAST->Set__DATA(STR__OPEN);
	}

	// ...
	SCX__ASYNC_TIMER_CTRL x_asyc_timer;

	x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
	x_asyc_timer->START__COUNT_UP(99999);

	do 
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -11;
		}

		// Fast-Pump Press Check ...
		{
			double cfg_press = aCH__CFG_VAC_PUMP_PRESSURE->Get__VALUE();
			double cur_press = aCH__MTC_PRESSURE_TORR->Get__VALUE();

			if((dEXT_CH__DI_MTC_ATM_SNS->Check__DATA(STR__OFF) > 0) 
			&& (dEXT_CH__DI_MTC_VAC_SNS->Check__DATA(STR__ON)  > 0) 
			&& (cur_press <= cfg_press))
			{
				break;
			}

			// Time-Out
			{
				double cfg_sec = aCH__CFG_VAC_PUMP_TIMEOUT->Get__VALUE();

				if(iActive__SIM_MODE > 0)
				{
					if(x_asyc_timer->Get__CURRENT_TIME() >= 3.0)
					{
						aCH__MTC_PRESSURE_SIM_MODE->Set__VALUE(cfg_press);

						dEXT_CH__DI_MTC_ATM_SNS->Set__DATA(STR__OFF);
						dEXT_CH__DI_MTC_VAC_SNS->Set__DATA(STR__ON);
					}
				}

				if(x_asyc_timer->Get__CURRENT_TIME() > cfg_sec)
				{
					return -17;
				}
			}
		}

		Sleep(100);
	} 
	while (1);

	return 1;
}

int CObj__MTC_FNC
::Fnc__SOFT_VENT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	// ...
	{
		double cfg_press = aCH__CFG_SOFT_VENT_PRESSURE->Get__VALUE();
		double cur_press = aCH__MTC_PRESSURE_TORR->Get__VALUE();

		if((dEXT_CH__DI_MTC_ATM_SNS->Check__DATA(STR__ON)  > 0)
		&& (dEXT_CH__DI_MTC_VAC_SNS->Check__DATA(STR__OFF) > 0)
		&& (cur_press >= cfg_press))
		{
			return 1;
		}
	}

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -10;
	}

	// ...
	{
		dEXT_CH__DO_MTC_N2PURGE_SLOW->Set__DATA(STR__OPEN);
		dEXT_CH__DO_MTC_N2PURGE_FAST->Set__DATA(STR__CLOSE);
	}

	// ...
	SCX__ASYNC_TIMER_CTRL x_asyc_timer;

	x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
	x_asyc_timer->START__COUNT_UP(99999);

	do 
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			x_asyc_timer->STOP();
			return -11;
		}

		// Soft-Vent Press Check ...
		{
			double cfg_press = aCH__CFG_SOFT_VENT_PRESSURE->Get__VALUE();
			double cur_press = aCH__MTC_PRESSURE_TORR->Get__VALUE();

			if(cur_press >= cfg_press)
			{
				break;
			}

			// Time-Out
			{
				double cfg_sec = aCH__CFG_SOFT_VENT_TIMEOUT->Get__VALUE();

				if(iActive__SIM_MODE > 0)
				{
					if(x_asyc_timer->Get__CURRENT_TIME() >= 5.0)
					{
						aCH__MTC_PRESSURE_SIM_MODE->Set__VALUE(cfg_press);

						dEXT_CH__DI_MTC_VAC_SNS->Set__DATA(STR__OFF);
					}
				}

				if(x_asyc_timer->Get__CURRENT_TIME() > cfg_sec)
				{
					return -17;
				}
			}
		}

		Sleep(100);
	} 
	while (1);

	return 1;
}

int CObj__MTC_FNC
::Fnc__FAST_VENT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	// PRESSURE CHECK ...
	{
		double cfg_press = aCH__CFG_ATM_VENT_PRESSURE->Get__VALUE();
		double cur_press = aCH__MTC_PRESSURE_TORR->Get__VALUE();

		if((dEXT_CH__DI_MTC_ATM_SNS->Check__DATA(STR__ON)  > 0)
		&& (dEXT_CH__DI_MTC_VAC_SNS->Check__DATA(STR__OFF) > 0)
		&& (cur_press >= cfg_press))
		{
			return 1;
		}
	}

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -10;
	}

	// ...
	{
		dEXT_CH__DO_MTC_N2PURGE_FAST->Set__DATA(STR__OPEN);
		dEXT_CH__DO_MTC_N2PURGE_SLOW->Set__DATA(STR__CLOSE);
	}

	// ...
	SCX__ASYNC_TIMER_CTRL x_asyc_timer;

	x_asyc_timer->REGISTER__COUNT_CHANNEL_NAME(sCH__OBJ_TIMER->Get__CHANNEL_NAME());
	x_asyc_timer->START__COUNT_UP(99999);

	do 
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			x_asyc_timer->STOP();
			return -11;
		}

		// Soft-Vent Press Check ...
		{
			double cfg_press = aCH__CFG_ATM_VENT_PRESSURE->Get__VALUE();
			double cur_press = aCH__MTC_PRESSURE_TORR->Get__VALUE();

			if((dEXT_CH__DI_MTC_ATM_SNS->Check__DATA(STR__ON)  > 0)
			&& (dEXT_CH__DI_MTC_VAC_SNS->Check__DATA(STR__OFF) > 0)
			&& (cur_press >= cfg_press))
			{
				return 1;
			}

			// Time-Out
			{
				double cfg_sec = aCH__CFG_ATM_VENT_TIMEOUT->Get__VALUE();

				if(iActive__SIM_MODE > 0)
				{
					if(x_asyc_timer->Get__CURRENT_TIME() >= 3.0)
					{
						aCH__MTC_PRESSURE_SIM_MODE->Set__VALUE(cfg_press);

						dEXT_CH__DI_MTC_VAC_SNS->Set__DATA(STR__OFF);
						dEXT_CH__DI_MTC_ATM_SNS->Set__DATA(STR__ON);
					}
				}

				if(x_asyc_timer->Get__CURRENT_TIME() > cfg_sec)
				{
					x_asyc_timer->STOP();	
					return -17;
				}
			}
		}

		Sleep(100);
	} 
	while (1);

	return 1;
}

int CObj__MTC_FNC
::Fnc__ALL_VV_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	// ALL_VV_Close IO Set ...
	{
		// Pumping Line Close ...
		{
			dEXT_CH__DO_MTC_2STAGE_SLOW->Set__DATA(STR__CLOSE);
			dEXT_CH__DO_MTC_2STAGE_FAST->Set__DATA(STR__CLOSE);
		}

		// Venting Line Close ...
		{
			dEXT_CH__DO_MTC_N2PURGE_SLOW->Set__DATA(STR__CLOSE);
			dEXT_CH__DO_MTC_N2PURGE_FAST->Set__DATA(STR__CLOSE);
		}
	}

	return 1;
}