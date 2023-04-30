#include "StdAfx.h"
#include "CObj__RF_STD.h"



//-------------------------------------------------------------------------
int CObj__RF_STD
::Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	// Interlock Channel Enable for Simulator ...
	if(iActive__SIM_MODE > 0)
	{
		dEXT_CH__DI_VAC_SNS->Set__DATA(STR__ON);
		dEXT_CH__DI_ATM_SNS->Set__DATA(STR__OFF);		
	}

	// 2. Default RF Set
	if(Fnc__DEFAULT_CONFIG_SET(p_variable, p_alarm) < 0)
	{
		return -11;
	}

	// 3. PHY IO Object Initialize
	if(bActive__RF_IO_OBJ)
	{
		CString obj_mode = sLINK__RF_MODE__INIT;

		if(pOBJ_CTRL__IO_RF->Call__OBJECT(obj_mode) < 0)
		{
			return -21;
		}
	}
	else
	{
		aEXT_CH__RF_AO_SET_POWER->Set__DATA("0");
	}

	if(bActive__RF_DO_POWER_CTRL)	
	{
		dEXT_CH__RF_DO_POWER_CTRL->Set__DATA(STR__OFF);
	}

	if(bActive__DO_RF_POWER_CONNECTOR)
	{
		dEXT_CH__DO_RF_POWER_CONNECTOR->Set__DATA(STR__ON);
	}
	return 1;
}

int CObj__RF_STD
::Call__REMOTE(CII_OBJECT__VARIABLE *p_variable,
			   CII_OBJECT__ALARM *p_alarm)
{
	if(bActive__RF_IO_OBJ)
	{
		CString obj_mode = sLINK__RF_MODE__REMOTE;

		if(pOBJ_CTRL__IO_RF->Call__OBJECT(obj_mode) < 0)
		{
			return -11;
		}
	}

	return 1;
}

int CObj__RF_STD
::Call__LOCAL(CII_OBJECT__VARIABLE *p_variable,
			  CII_OBJECT__ALARM *p_alarm)
{
	if(bActive__RF_IO_OBJ)
	{
		CString obj_mode = sLINK__RF_MODE__LOCAL;

		if(pOBJ_CTRL__IO_RF->Call__OBJECT(obj_mode) < 0)
		{
			return -11;
		}
	}

	return 1;
}

int CObj__RF_STD
::Call__OFF(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	/*
	// 1. RF Frequency Control ...
	if(dCH__CFG_FREQUENCY_USE->Check__DATA(STR__YES) > 0)
	{
		if(dCH__PARA_RCP_CTRL_ACTIVE->Check__DATA(STR__ON) > 0)
		{
			Fnc__RECIPE_CONTROL_SET(p_variable, p_alarm);
		}
		else
		{
			Fnc__DEFAULT_CONFIG_SET(p_variable, p_alarm);
		}
	}
	*/

	// 2. 
	if(bActive__RF_IO_OBJ)
	{
		CString obj_mode = sLINK__RF_MODE__OFF;
		if(pOBJ_CTRL__IO_RF->Call__OBJECT(obj_mode) < 0)
		{
			return -11;		
		}
	}
	else
	{
		aEXT_CH__RF_AO_SET_POWER->Set__DATA("0");
		if(iActive__SIM_MODE > 0) dEXT_CH__INFO_DI_RF_POWER->Set__DATA(STR__OFF); //KMS
		Sleep(250); // For Prevent Too Fast Control
	}

	if(bActive__RF_DO_POWER_CTRL)	
	{
		dEXT_CH__RF_DO_POWER_CTRL->Set__DATA(STR__OFF);
	}
	return 1;
}

int CObj__RF_STD
::Call__QUICK_OFF(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(bActive__RF_IO_OBJ)
	{
		CString obj_mode = sLINK__RF_MODE__OFF;
	
		if(pOBJ_CTRL__IO_RF->Call__OBJECT(obj_mode) < 0)
		{
			return -11;		
		}
	}
	else
	{
		aEXT_CH__RF_AO_SET_POWER->Set__DATA("0");
		if(iActive__SIM_MODE > 0) dEXT_CH__INFO_DI_RF_POWER->Set__DATA(STR__OFF); //KMS
		Sleep(250); // For Prevent Too Fast Control
	}

	if(bActive__RF_DO_POWER_CTRL)	
	{
		dEXT_CH__RF_DO_POWER_CTRL->Set__DATA(STR__OFF);
	}
	return 1;
}

int CObj__RF_STD
::Call__POWER_SET(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	CString str_data;

	if(dCH__RF_CONDUCTANCE_INTLK_SKIP->Check__DATA(STR__ON) < 0)
	{
		if(Fnc__INTLK_CHECK(p_variable, p_alarm) < 0)
		{
			dCH__RF_ABORT_FLAG->Set__DATA(STR__ON);
			return -11;
		}
	}

	if(bActive__RF_DO_POWER_CTRL)
	{
		if(bActive__DO_RF_POWER_CONNECTOR)
		{
			dEXT_CH__DO_RF_POWER_CONNECTOR->Set__DATA(STR__ON);
		}
	}

	// 1. RF Power On HOLD Delay TIME
	{
		double cfg_sec = aCH__PARA_HOLD_TIME->Get__VALUE();

		SCX__TIMER_CTRL x_timer_ctrl;
		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);

		if(x_timer_ctrl->WAIT(cfg_sec) < 0)
		{
			return -21;
		}
	}

	// 2. RF Power SET
	{
		double para__set_pwr = aCH__PARA_SET_POWER->Get__VALUE();
		Fnc__SET_OFFSET_POWER(para__set_pwr);

		str_data = sCH__PARA_RF_OFFSET_POWER->Get__STRING();
		double set_offset = atof(str_data);
		double set_power = 0.0;

		if(para__set_pwr <= 0 ) {set_power = para__set_pwr;} // KMS : 0 Watt Case Not apply offset Power
		else {set_power = para__set_pwr + set_offset;} 
		
		if(bActive__RF_IO_OBJ)
		{
			aEXT_CH__RF_PARA_SET_POWER->Set__VALUE(set_power);
		}
		else
		{
			// KMS 5W Split & 0W not adapt Offset
			if(para__set_pwr ==  0) set_power = 0;
			else set_power = (5*(int)(set_power/5)); //Just Using AD-TEC

			str_data.Format("%.1f", set_power);
			aEXT_CH__RF_AO_SET_POWER->Set__DATA(str_data);;
		}
	}

	if(bActive__RF_FREQ_MODE)
	{
		// 3. RF Ramp SET
		{
			aCH__PARA_RAMP_UP_TIME->Get__DATA(str_data);
			aEXT_CH__RF_PARA_RAMP_UP_TIME->Set__DATA(str_data);

			aCH__PARA_RAMP_DOWN_TIME->Get__DATA(str_data);
			aEXT_CH__RF_PARA_RAMP_DOWN_TIME->Set__DATA(str_data);
		}

		// 4. RF Frequency Use SET
		{
			dCH__PARA_FREQ_TUNE_USE->Get__DATA(str_data);
			dEXT_CH__RF_PARA_TUNE_USE->Set__DATA(str_data);
		}

		// 5. RF Frequency SET
		{
			aCH__PARA_FREQ_PRESET->Get__DATA(str_data);					// KHZ
			aEXT_CH__RF_PARA_START_FREQUENCY->Set__DATA(str_data);		// KHz
		}

		// 6. RF Frequency Output Power SET
		{
			aCH__PARA_FREQ_OUTPUT->Get__DATA(str_data);
			aEXT_CH__RF_PARA_OUTPUT_FREQUENCY->Set__DATA(str_data);
		}

		// 7. RF Tune Delay Time SET
		{
			aCH__PARA_FREQ_TUNE_DELAY->Get__DATA(str_data);				// msec
			aEXT_CH__RF_PARA_TUNE_DELAY->Set__DATA(str_data);			// msec
		}
	}

	// 8. RF POWER.SET ...
	if(bActive__RF_IO_OBJ)
	{
		CString obj_mode = sLINK__RF_MODE__POWER_SET;

		if(pOBJ_CTRL__IO_RF->Call__OBJECT(obj_mode) < 0)
		{
			return -31;
		}
	}

	return 1;
}

int CObj__RF_STD
::Call__POWER_ON(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	CString str_data;

	if(dCH__RF_CONDUCTANCE_INTLK_SKIP->Check__DATA(STR__ON) < 0)
	{
		if(Fnc__INTLK_CHECK(p_variable, p_alarm) < 0)
		{
			dCH__RF_ABORT_FLAG->Set__DATA(STR__ON);
			return -11;
		}
	}

	if(bActive__DO_RF_POWER_CONNECTOR)
	{
		dEXT_CH__DO_RF_POWER_CONNECTOR->Set__DATA(STR__ON);
	}

	// RF POWER.ON ...
	// RF POWER.ON ...
	if(bActive__RF_IO_OBJ)
	{
		CString obj_mode = sLINK__RF_MODE__POWER_ON;

		if(pOBJ_CTRL__IO_RF->Call__OBJECT(obj_mode) < 0)
		{
			return -21;
		}
	}
	else
	{
		unsigned char check_count = 0;
		if(bActive__RF_DO_POWER_CTRL)// KMS : IO TYPE
		{
			dEXT_CH__RF_DO_POWER_CTRL->Set__DATA(STR__ON);
			if(iActive__SIM_MODE > 0) dEXT_CH__INFO_DI_RF_POWER->Set__DATA(STR__ON);
			return 1;
			while(check_count<10) // 
			{
				if(dEXT_CH__INFO_DI_RF_POWER ->Check__DATA(STR__ON)>0) return 1;
				Sleep(100);
				check_count+=1;
			}
			dEXT_CH__RF_DO_POWER_CTRL->Set__DATA(STR__OFF);
			
		}
		return -21;
	}	
	return 1;
}

int CObj__RF_STD
::Fnc__SET_OFFSET_POWER(const double ref__set_pwr)
{
	sCH__PARA_RF_OFFSET_POWER->Set__DATA("");

	// ...
	int check_flag = 1;
	CString str__apply_mode;

	if(check_flag > 0)
	{
		dCH__RF_CAL__OFFSET_APPLY->Get__DATA(str__apply_mode);

		if((str__apply_mode.CompareNoCase(STR__AVERAGE) != 0)	
		&& (str__apply_mode.CompareNoCase(STR__LOOKUP)  != 0))
		{
			check_flag = -1;
		}
	}
	if(check_flag > 0)
	{
		if(sCH__RF_CAL__TEST_FLAG->Check__DATA(STR__YES) > 0)
		{
			check_flag = -2;
		}
	}
	if(check_flag > 0)
	{
		CString var_data;
		sCH__RF_CAL__OFFSET_SAVE_DATE->Get__DATA(var_data);

		if(var_data.GetLength() < 1)
		{
			check_flag = -3;
		}
	}

	if(check_flag > 0)
	{
		double  value__set_pwr = ref__set_pwr;

		if(value__set_pwr < 1)
		{
			return 1;
		}

		if(str__apply_mode.CompareNoCase(STR__LOOKUP) == 0)	
		{
			double  cur__x = value__set_pwr;
			double  cur__y = 0;

			double  pos__min_x;
			double  pos__max_x;
			double  pos__min_y;
			double  pos__max_y;

			CString var_data;
			int i;

			for(i=0;i<CFG__ITEM_CHECK-1;i++)
			{
				// Pos X ...
				sCH__RF_CAL__CFG_NOW_POWER[i]->Get__DATA(var_data);
				pos__min_x = atof(var_data);

				sCH__RF_CAL__CFG_NOW_POWER[i+1]->Get__DATA(var_data);
				pos__max_x = atof(var_data);

				// Pos Y ...
				sCH__RF_CAL__CFG_NOW_OFFSET[i]->Get__DATA(var_data);
				pos__min_y = atof(var_data);

				sCH__RF_CAL__CFG_NOW_OFFSET[i+1]->Get__DATA(var_data);
				pos__max_y = atof(var_data);

				if((cur__x >= pos__min_x)
					&& (cur__x <= pos__max_x))	
				{
					if(pos__max_x - pos__min_x >= 1.0)
					{
						cur__y = pos__min_y + ((pos__max_y - pos__min_y) / (pos__max_x - pos__min_x)) * (cur__x - pos__min_x);
					}
					else
					{
						cur__y = pos__min_y + (pos__max_y - pos__min_y) * (cur__x - pos__min_x);
					}

					// Offset Setting ...
					{
						double value__offset = value__set_pwr * (cur__y / 100.0);

						var_data.Format("%.1f", value__offset);
						sCH__PARA_RF_OFFSET_POWER->Set__DATA(var_data);
						return 1;
					}
				}
			}
		}
		else if(str__apply_mode.CompareNoCase(STR__AVERAGE) == 0)
		{
			CString var_data;

			sCH__RF_CAL__CFG_NOW_AVG_OFFSET->Get__DATA(var_data);
			double cur__avg_offset = atof(var_data);

			double value__offset = value__set_pwr * (cur__avg_offset / 100.0);

			var_data.Format("%.1f", value__offset);
			sCH__PARA_RF_OFFSET_POWER->Set__DATA(var_data);
			return 1;
		}
	}			

	return 1;
}

// ...
int CObj__RF_STD
::Call__PROC_SET(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm)
{
	int r_flag;

	r_flag = Call__POWER_SET(p_variable, p_alarm);
	if(r_flag < 0)			return r_flag;

	if(bActive__RF_IO_OBJ == false) Sleep(200); // Not Object IO Case Need Delay Time
	
	// Power ON Delay
	{
		double dWaitSec = aCH__PARA_WAIT_POWER_ON->Get__VALUE();
		if(dWaitSec > 0) Sleep(dWaitSec);
		aCH__PARA_WAIT_POWER_ON->Set__VALUE(0);
	}

	r_flag = Call__POWER_ON(p_variable, p_alarm);
	if(r_flag < 0)			return r_flag;

	return 1;
}
