#include "StdAfx.h"
#include "CObj__TMC_ManiFold_X.h"
#include "CObj__TMC_ManiFold_X__DEF.h"
#include "CObj__TMC_ManiFold_X__ALID.h"


// ...
int  CObj__TMC_ManiFold_X::
Check__TRANSFER_ATM(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm,
					const CString& module_name,
					CII__VAR_ANALOG_CTRL* pch_module_pressure)
{
LOOP_RETRY:

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -1;
	}

	// ...
	CString var_data;

	double cur__module_press;
	double cfg__atm_press;

	pch_module_pressure->Get__DATA(var_data);
	cur__module_press = atof(var_data);

	aEXT_CH__CFG_REF_ATM_PRESSURE->Get__DATA(var_data);
	cfg__atm_press = atof(var_data);

	// ATM Check
	if(cur__module_press >= cfg__atm_press)
	{

	}
	else
	{
		int alarm_id = ALID__TMC__NOT_ATM_ERROR;
		CString alarm_msg;
		CString alarm_bff;
		CString r_act;

		alarm_bff.Format("Config ATM Pressure : %.3f\n",cfg__atm_press);
		alarm_msg += alarm_bff;
		alarm_bff.Format("Current %s Pressure : %.3f\n", module_name,cur__module_press);
		alarm_msg += alarm_bff;

		p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alarm_msg,r_act);

		if(r_act.CompareNoCase(ACT__RETRY) == 0)		goto LOOP_RETRY;
		return -1;
	}

	return 1;
}

int  CObj__TMC_ManiFold_X::
Check__TRANSFER_PRESSURE(CII_OBJECT__VARIABLE* p_variable,
						 CII_OBJECT__ALARM* p_alarm,
						 const CString& module_name,
						 CII__VAR_ANALOG_CTRL* pch_module_pressure)
{
LOOP_RETRY:

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -1;
	}

	// ...
	CString var_data;

	double cur__tmc_press;
	double cur__module_press;
	double cfg__atm_press;
	double cfg__vac_press;


	aEXT_CH__TMC_CHM__PRESSURE_TORR->Get__DATA(var_data);
	cur__tmc_press = atof(var_data);

	pch_module_pressure->Get__DATA(var_data);
	cur__module_press = atof(var_data);

	aEXT_CH__CFG_REF_ATM_PRESSURE->Get__DATA(var_data);
	cfg__atm_press = atof(var_data);

	aEXT_CH__CFG_REF_VAC_PRESSURE->Get__DATA(var_data);
	cfg__vac_press = atof(var_data);

	// VAC Check
	if((cur__tmc_press    <= cfg__vac_press)
		&& (cur__module_press <= cfg__vac_press))
	{

	}
	// ATM Check
	else if((cur__tmc_press    >= cfg__atm_press)
		&& (cur__module_press >= cfg__atm_press))
	{

	}
	else
	{
		int alarm_id = ALID__TMC__TRANSFER_PRESSURE_ERROR;
		CString alarm_msg;
		CString alarm_bff;
		CString r_act;

		alarm_bff.Format("Config ATM Pressure : %.3f\n",cfg__atm_press);
		alarm_msg += alarm_bff;
		alarm_bff.Format("Config VAC Pressure : %.3f\n",cfg__vac_press);
		alarm_msg += alarm_bff;
		alarm_bff.Format("Current TMC_CHM Pressure : %.3f\n", cur__tmc_press);
		alarm_msg += alarm_bff;
		alarm_bff.Format("Current %s Pressure : %.3f\n", module_name, cur__module_press);
		alarm_msg += alarm_bff;

		p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alarm_msg,r_act);

		if(r_act.CompareNoCase(ACT__RETRY) == 0)		goto LOOP_RETRY;
		return -1;
	}

	return 1;
}
