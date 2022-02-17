#include "StdAfx.h"
#include "CObj__SYS_IO.h"
#include "CObj__SYS_IO__DEF.h"
#include "CObj__SYS_IO__ALID.h"

#include "Macro_Function.h"


//-------------------------------------------------------------------------
// 1. Foreline Valve <- Open
INTERLOCK_REGISTER(CObj__SYS_IO, Fnc_SetPoint__VAC_Foreline_Vlv_Open);

// 2. Fast Valve <- Open
INTERLOCK_REGISTER(CObj__SYS_IO, Fnc_SetPoint__VAC_Fast_Vlv_Open);

// 3. Slow Valve <- Open
INTERLOCK_REGISTER(CObj__SYS_IO, Fnc_SetPoint__VAC_Slow_Vlv_Open);


//-------------------------------------------------------------------------
int  CObj__SYS_IO
::__DEFINE__IO_INTERLOCK(p_interlock)
{
	CString ch_name;
	CString obj_name;
	CString var_name;
	CString var_data;

	// 1. Foreline Valve <- Open
	if(bActive__DO_ROUGH_FORELINE_VLV)
	{
		ch_name = sCH_Name__DO_ROUGH_FORELINE_VLV;
		_Macro__Get_Channel_To_Obj_Variable(ch_name, obj_name,var_name);

		var_data = STR__Open;

		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__VAC_Foreline_Vlv_Open);
	}

	// 2. Fast Valve <- Open
	{
		ch_name = sCH_Name__DO_ROUGH_FAST_VLV;
		_Macro__Get_Channel_To_Obj_Variable(ch_name, obj_name,var_name);

		var_data = STR__Open;

		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__VAC_Fast_Vlv_Open);
	}

	// 3. Slow Valve <- Open
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

// 1. Foreline Valve -> Open
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
	if(doEXT_CH__DO_ROUGH_SOFT_VLV->Check__DATA(STR__Close) < 0)
	{
		err_msg = "Vacuum slow-valve is not closed. \n";
		return -13;
	}

	return 1;
}

// 2. Fast Valve -> Open
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
	if(dEXT_CH__IO_ATM_SNS->Check__DATA(sATM_SNS__ACTIVE_STATE) > 0)
	{
		err_msg = "ATM sensor is not \"Off\". \n";
		return -1;
	}

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

// 3. Slow Valve -> Open
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
