#include "StdAfx.h"
#include "CObj__SYSTEM.h"
#include "CObj__SYSTEM__DEF.h"
#include "CObj__SYSTEM__ALID.h"


//----------------------------------------------------------------------------------------------------
void CObj__SYSTEM
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;	

	int alarm_id;
	CString r_act;
	CString var_data;

	int r_cnt__air_press = 0;

	Sleep(5000);

	while(1)
	{
		cx_timer_ctrl->WAIT(1.0);

		if(mSeq_Info->Is__SIMULATION_MODE() > 0)
		{
			dEXT_CH__IO_AIR_SNS->Set__DATA(STR__ON);
		}

		// Waiting ... DeviceNet Comm status..
		if(diEXT_CH__IO_DNET_COMM_STS->Check__DATA("UNKNOWN") > 0)
		{
			continue;
		}

		if(dCFG_CDA_CHECK->Check__DATA("FALSE") > 0)
		{
			continue;
		}

		if(dEXT_CH__IO_AIR_SNS->Check__DATA(STR__ON) < 0)
		{
			r_cnt__air_press++;

			if(r_cnt__air_press > 4)
			{
				r_cnt__air_press = 0;

				// ...
				{
					alarm_id = ALID__AIR_PRESSURE__ERROR;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Popup__ALARM(alarm_id, r_act);
				}
			}
		}
		else
		{
			r_cnt__air_press = 0;
		}

		// ...
	}	
}

//----------------------------------------------------------------------------------------------------
void CObj__SYSTEM
::Mon__N2_SENSOR_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;	

	int alarm_id;
	CString r_act;
	CString var_data;

	int r_cnt__vac_press = 0;

	Sleep(5000);

	while(1)
	{
		cx_timer_ctrl->WAIT(1.0);

		if(mSeq_Info->Is__SIMULATION_MODE() > 0)
		{
			dEXT_CH__IO_N2_SNS->Set__DATA(STR__ON);
		}

		if(dCFG_N2_CHECK->Check__DATA("FALSE") > 0)
		{
			continue;
		}

		// Waiting ... DeviceNet Comm status..
		if(diEXT_CH__IO_DNET_COMM_STS->Check__DATA("UNKNOWN") > 0)
		{
			continue;
		}

		if(dEXT_CH__IO_N2_SNS->Check__DATA(STR__ON) < 0)
		{
			r_cnt__vac_press++;

			if(r_cnt__vac_press > 4)
			{
				r_cnt__vac_press = 0;

				// ...
				{
					alarm_id = ALID__N2_SENSOR__ERROR;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Popup__ALARM(alarm_id, r_act);
				}
			}
		}
		else
		{
			r_cnt__vac_press = 0;
		}

		// ...
	}	
}

//----------------------------------------------------------------------------------------------------
void CObj__SYSTEM
::Mon__EFEM_DOORS_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;	

	int alarm_id;
	CString r_act;
	CString var_data;

	int r_cnt = 0;

	while(1)
	{
		cx_timer_ctrl->WAIT(0.1);

		if(mSeq_Info->Is__SIMULATION_MODE() > 0)
		{
			dEXT_CH__IO_EFEM_DOOR_SNS->Set__DATA(STR__None);
		}			

		// Waiting ... DeviceNet Comm status..
		if(diEXT_CH__IO_DNET_COMM_STS->Check__DATA("UNKNOWN") > 0)
		{
			continue;
		}

		if(dEXT_CH__IO_EFEM_DOOR_SNS->Check__DATA(STR__None) < 0)
		{
			r_cnt++;

			if(r_cnt > 4)
			{
				r_cnt = 0;

				// ...
				{
					alarm_id = ALID__EFEM_SIDE_DOOR_NOT_CLOSE__ERROR;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Popup__ALARM(alarm_id, r_act);
				}
			}
		}
		else
		{
			r_cnt = 0;
		}

		// ...
	}	
}
