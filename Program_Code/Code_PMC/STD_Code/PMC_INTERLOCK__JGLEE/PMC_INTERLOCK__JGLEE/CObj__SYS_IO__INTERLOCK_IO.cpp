#include "StdAfx.h"
#include "CObj__SYS_IO.h"
#include "CObj__SYS_IO__DEF.h"
#include "CObj__SYS_IO__ALID.h"

#include "Macro_Function.h"


//-------------------------------------------------------------------------
// VENT.Fast Valve <- Open
INTERLOCK_REGISTER(CObj__SYS_IO, Fnc_SetPoint__VENT_Fast_Vlv_Open);

// VENT.Soft Valve <- Open
INTERLOCK_REGISTER(CObj__SYS_IO, Fnc_SetPoint__VENT_Soft_Vlv_Open);

// Foreline Valve <- Open
INTERLOCK_REGISTER(CObj__SYS_IO, Fnc_SetPoint__VAC_Foreline_Vlv_Open);

// Foreline Valve <- Close
INTERLOCK_REGISTER(CObj__SYS_IO, Fnc_SetPoint__VAC_Foreline_Vlv_Close);

// VAC.Fast Valve <- Open
INTERLOCK_REGISTER(CObj__SYS_IO, Fnc_SetPoint__VAC_Fast_Vlv_Open);

// VAC.Slow Valve <- Open
INTERLOCK_REGISTER(CObj__SYS_IO, Fnc_SetPoint__VAC_Slow_Vlv_Open);


//-------------------------------------------------------------------------
int  CObj__SYS_IO
::__DEFINE__IO_INTERLOCK(p_interlock)
{
	CString ch_name;
	CString obj_name;
	CString var_name;
	CString var_data;

	// Vent.Fast Valve <- Open
	{
		ch_name = sCH_Name__DO_VENT_FAST_VLV;
		_Macro__Get_Channel_To_Obj_Variable(ch_name, obj_name,var_name);

		var_data = STR__Open;
		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__VENT_Fast_Vlv_Open);
	}
	// Vent.Soft Valve <- Open
	if(bActive__DO_VENT_SOFT_VLV)
	{
		ch_name = sCH_Name__DO_VENT_SOFT_VLV;
		_Macro__Get_Channel_To_Obj_Variable(ch_name, obj_name,var_name);

		var_data = STR__Open;
		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__VENT_Soft_Vlv_Open);
	}

	// Foreline Valve <- Open, Close
	if(bActive__DO_ROUGH_FORELINE_VLV)
	{
		ch_name = sCH_Name__DO_ROUGH_FORELINE_VLV;
		_Macro__Get_Channel_To_Obj_Variable(ch_name, obj_name,var_name);

		var_data = STR__Open;
		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__VAC_Foreline_Vlv_Open);

		var_data = STR__Close;
		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__VAC_Foreline_Vlv_Close);
	}

	// Fast Valve <- Open
	{
		ch_name = sCH_Name__DO_ROUGH_FAST_VLV;
		_Macro__Get_Channel_To_Obj_Variable(ch_name, obj_name,var_name);

		var_data = STR__Open;
		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__VAC_Fast_Vlv_Open);
	}

	// 3. Slow Valve <- Open
	if(bActive__DO_ROUGH_SOFT_VLV)
	{
		ch_name = sCH_Name__DO_ROUGH_SOFT_VLV;
		_Macro__Get_Channel_To_Obj_Variable(ch_name, obj_name,var_name);

		var_data = STR__Open;
		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__VAC_Slow_Vlv_Open);
	}

	return 1;
}


//--------------------------------------------------------
//	Interlock Function

// VENT.Fast Valve -> Open
int CObj__SYS_IO::
IFnc_SetPoint__VENT_Fast_Vlv_Open()
{
	CString err_msg;

	if(Check__Interlock_Use(ALID__VENT_Fast_Valve__OPEN) < 0)
	{
		return 1;
	}

	if(SetPoint__VENT_Fast_Vlv_Open(err_msg) > 0)
	{
		return 1;
	}

	// ...
	{
		int	alarm_id = ALID__VENT_Fast_Valve__OPEN;

		Post_Alarm(alarm_id, err_msg);
	}
	return -1;
}

int CObj__SYS_IO::
SetPoint__VENT_Fast_Vlv_Open(CString &err_msg)
{
	if(doEXT_CH__DO_ROUGH_FAST_VLV->Check__DATA(STR__Close) < 0)
	{
		err_msg = "Vacuum fast-valve is not closed. \n";
		return -11;
	}

	if(bActive__DO_ROUGH_SOFT_VLV)
	{
		if(doEXT_CH__DO_ROUGH_SOFT_VLV->Check__DATA(STR__Close) < 0)
		{
			err_msg = "Vacuum slow-valve is not closed. \n";
			return -12;
		}
	}

	// APC.VLV_POS ...
	{
		CString ch_data = sEXT_CH__APC_VLV_CUR_POS->Get__STRING();
		double cur__vlv_pos = atof(ch_data);

		if(cur__vlv_pos > 0.0)
		{
			err_msg = "APC's current valve position is not closed ! \n"; 
			return -13;
		}
	}

	return 1;
}

// VENT.Soft Valve -> Open
int CObj__SYS_IO::
IFnc_SetPoint__VENT_Soft_Vlv_Open()
{
	CString err_msg;

	if(Check__Interlock_Use(ALID__VENT_Soft_Valve__OPEN) < 0)
	{
		return 1;
	}

	if(SetPoint__VENT_Soft_Vlv_Open(err_msg) > 0)
	{
		return 1;
	}

	// ...
	{
		int	alarm_id = ALID__VENT_Soft_Valve__OPEN;

		Post_Alarm(alarm_id, err_msg);
	}
	return -1;
}

int CObj__SYS_IO::
SetPoint__VENT_Soft_Vlv_Open(CString &err_msg)
{
	if(doEXT_CH__DO_ROUGH_FAST_VLV->Check__DATA(STR__Close) < 0)
	{
		err_msg = "Vacuum fast-valve is not closed. \n";
		return -11;
	}

	if(bActive__DO_ROUGH_SOFT_VLV)
	{
		if(doEXT_CH__DO_ROUGH_SOFT_VLV->Check__DATA(STR__Close) < 0)
		{
			err_msg = "Vacuum slow-valve is not closed. \n";
			return -12;
		}
	}

	// APC.VLV_POS ...
	{
		CString ch_data = sEXT_CH__APC_VLV_CUR_POS->Get__STRING();
		double cur__vlv_pos = atof(ch_data);

		if(cur__vlv_pos > 0.0)
		{
			err_msg = "APC's current valve position is not closed ! \n"; 
			return -13;
		}
	}

	return 1;
}

// Foreline Valve <- Open
int CObj__SYS_IO::
IFnc_SetPoint__VAC_Foreline_Vlv_Open()
{
	CString err_msg;

	if(Check__Interlock_Use(ALID__VAC_Foreline_Valve__OPEN) < 0)
	{
		return 1;
	}

	if(SetPoint__VAC_Foreline_Vlv_Open(err_msg) > 0)
	{
		return 1;
	}

	// ...
	{
		int	alarm_id = ALID__VAC_Foreline_Valve__OPEN;

		Post_Alarm(alarm_id, err_msg);
	}
	return -1;
}

int CObj__SYS_IO::
SetPoint__VAC_Foreline_Vlv_Open(CString &err_msg)
{
	if(dEXT_CH__IO_VAC_SNS->Check__DATA(sVAC_SNS__ACTIVE_STATE) < 0)
	{
		CString var_data = sEXT_CH__APC_VLV_CUR_POS->Get__STRING();
		double cur_pos = atof(var_data);

		if(cur_pos > 0.0)
		{
			err_msg.Format("Vacuum sensor is not \"%s\". \n", sVAC_SNS__ACTIVE_STATE);
			err_msg += "And, APC's current valve position is not closed ! \n"; 
			return -11;
		}
	}

	if(doEXT_CH__DO_ROUGH_FAST_VLV->Check__DATA(STR__Close) < 0)
	{
		err_msg = "Vacuum fast-valve is not closed. \n";
		return -12;
	}

	if(bActive__DO_ROUGH_SOFT_VLV)
	{
		if(doEXT_CH__DO_ROUGH_SOFT_VLV->Check__DATA(STR__Close) < 0)
		{
			err_msg = "Vacuum slow-valve is not closed. \n";
			return -13;
		}
	}

	if(bActive__DRY_PUMP_POWER_SNS)
	{
		if(dEXT_CH__DRY_PUMP_POWER_SNS->Check__DATA(STR__ON) < 0)
		{
			err_msg = "Dry-Pump is not \"On\". \n";
			return -21;
		}
	}
	if(bActive__DRY_PUMP_VAC_SNS)
	{
		if(dEXT_CH__DRY_PUMP_VAC_SNS->Check__DATA(STR__ON) < 0)
		{
			err_msg = "Roughing-Line is not \"VAC\". \n";
			return -22;
		}
	}

	return 1;
}

// Foreline Valve <- Close
int CObj__SYS_IO::
IFnc_SetPoint__VAC_Foreline_Vlv_Close()
{
	CString err_msg;

	if(Check__Interlock_Use(ALID__VAC_Foreline_Valve__CLOSE) < 0)
	{
		return 1;
	}

	if(SetPoint__VAC_Foreline_Vlv_Close(err_msg) > 0)
	{
		return 1;
	}

	// ...
	{
		int	alarm_id = ALID__VAC_Foreline_Valve__CLOSE;

		Post_Alarm(alarm_id, err_msg);
	}
	return -1;
}

int CObj__SYS_IO::
SetPoint__VAC_Foreline_Vlv_Close(CString &err_msg)
{
	// APC.VLV_POS ...
	{
		CString ch_data = sEXT_CH__APC_VLV_CUR_POS->Get__STRING();
		double cur__vlv_pos = atof(ch_data);

		if(cur__vlv_pos > 0.0)
		{
			err_msg = "APC's current valve position is not closed ! \n"; 
			return -11;
		}
	}

	return 1;
}

// VAC.Fast Valve -> Open
int CObj__SYS_IO::
IFnc_SetPoint__VAC_Fast_Vlv_Open()
{
	CString err_msg;

	if(Check__Interlock_Use(ALID__VAC_Fast_Valve__OPEN) < 0)
	{
		return 1;
	}

	if(SetPoint__VAC_Fast_Vlv_Open(err_msg) > 0)
	{
		return 1;
	}

	// ...
	{
		int	alarm_id = ALID__VAC_Fast_Valve__OPEN;

		Post_Alarm(alarm_id, err_msg);
	}
	return -1;
}

int CObj__SYS_IO::
SetPoint__VAC_Fast_Vlv_Open(CString &err_msg)
{
	if(bActive__DO_ROUGH_SOFT_VLV)
	{
		if(dEXT_CH__IO_ATM_SNS->Check__DATA(sATM_SNS__ACTIVE_STATE) > 0)
		{
			err_msg = "ATM sensor is not \"Off\". \n";
			return -11;
		}
	}

	if(bActive__DO_ROUGH_FORELINE_VLV)
	{
		if(doEXT_CH__DO_ROUGH_FORELINE_VLV->Check__DATA(STR__Close) < 0)
		{
			err_msg = "TMP foreline valve is not closed. \n";
			return -12;
		}
	}

	return 1;
}

// VAC.Slow Valve -> Open
int CObj__SYS_IO::
IFnc_SetPoint__VAC_Slow_Vlv_Open()
{
	CString err_msg;

	if(Check__Interlock_Use(ALID__VAC_Slow_Valve__OPEN) < 0)
	{
		return 1;
	}

	if(SetPoint__VAC_Slow_Vlv_Open(err_msg) > 0)
	{
		return 1;
	}

	// ...
	{
		int	alarm_id = ALID__VAC_Slow_Valve__OPEN;

		Post_Alarm(alarm_id, err_msg);
	}
	return -1;
}

int CObj__SYS_IO::
SetPoint__VAC_Slow_Vlv_Open(CString &err_msg)
{
	if(bActive__DO_ROUGH_FORELINE_VLV)
	{
		if(doEXT_CH__DO_ROUGH_FORELINE_VLV->Check__DATA(STR__Close) < 0)
		{
			err_msg = "TMP foreline valve is not closed. \n";
			return -1;
		}
	}

	return 1;
}
