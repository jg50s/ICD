#include "StdAfx.h"
#include "CObj__TMC_EX.h"
#include "CObj__TMC_EX__DEF.h"
#include "CObj__TMC_EX__ALID.h"


// LLx ---------------
int  CObj__TMC_EX::
Call__LLx_SV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm,
				   const int ll_id)
{
	int ll_index = ll_id - 1;	
	if(ll_index <  0)						return -11;
	if(ll_index >= iCFG__LLx_SIZE)			return -12;

	if(pLLx__OBJ_CTRL[ll_index]->Is__OBJ_BUSY() > 0)
	{
		if(bActive__LLx_MULTI_SLOT_VALVE)
		{
			bool active__all_close = true;

			for(int k=0; k<iLLx_SLOT_SIZE; k++)	
			{
				if(dEXT_CH__LLx__SLIT_VLV_STATUS_XX[ll_index][k]->Check__DATA(STR__CLOSE) > 0)
					continue;

				active__all_close = false;
				break;
			}

			if(active__all_close)			return 1;
		}
		else
		{
			if(dEXT_CH__LLx__SLIT_VLV_STATUS_A[ll_index]->Check__DATA(STR__CLOSE) > 0)
			{
				return 1;
			}
		}
	}

	return pLLx__OBJ_CTRL[ll_index]->Call__OBJECT("SV_TRANSFER.CLOSE");
}
int  CObj__TMC_EX::
Call__LLx_SV_OPEN(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm,
				  const int ll_id)
{
	int ll_index = ll_id - 1;	
	if(ll_index <  0)						return -11;
	if(ll_index >= iCFG__LLx_SIZE)			return -12;

	return pLLx__OBJ_CTRL[ll_index]->Call__OBJECT("SV_TRANSFER.OPEN");
}

int  CObj__TMC_EX::
Call__LLx_DV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm,
				   const int ll_id)
{
	int ll_index = ll_id - 1;	
	if(ll_index <  0)						return -11;
	if(ll_index >= iCFG__LLx_SIZE)			return -12;

	return pLLx__OBJ_CTRL[ll_index]->Call__OBJECT("DV_TRANSFER.CLOSE");
}
int  CObj__TMC_EX::
Call__LLx_DV_OPEN(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm,
				  const int ll_id)
{
	int ll_index = ll_id - 1;	
	if(ll_index <  0)						return -11;
	if(ll_index >= iCFG__LLx_SIZE)			return -12;

	// ...
	CString module_name;
	CII__VAR_ANALOG_CTRL *pch_module_pressure;

	module_name.Format("LL%1d", ll_id);
	pch_module_pressure = aEXT_CH__LLx__PRESSURE_TORR[ll_index].Get__PTR();

	if(Check__TRANSFER_ATM(p_variable,
						   p_alarm,
						   module_name,
						   pch_module_pressure) < 0)
	{
		return -1;
	}

	return pLLx__OBJ_CTRL[ll_index]->Call__OBJECT("DV_TRANSFER.OPEN");
}


// PMC ---------------
// CHECK PMC SV ALL CLOSE -----
int  CObj__TMC_EX::
Call__CHECK_PMC_SV_ALL_CLOSE(CII_OBJECT__VARIABLE* p_variable,
							 CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	int flag = pPMx__OBJ_CTRL->Call__OBJECT("CHECK_SV_ALL_CLOSE");

	// ...
	{
		CStringArray l_err_msg;
		pPMx__OBJ_CTRL->Get__RETURN_FNC_PARAMETER(l_err_msg);

		p_ext_mode_ctrl->Set__RETURN_FNC_PARAMETER(l_err_msg);
	}
	return flag;
}


// SV CLOSE -----
int  CObj__TMC_EX::
Call__PMC_SV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm)
{
	CString var_data;

	aCH__PARA_PMC_ID->Get__DATA(var_data);
	aEXT_CH__PMx__PARA_PMC_ID->Set__DATA(var_data);

	return pPMx__OBJ_CTRL->Call__OBJECT("SV_CLOSE");
}

int  CObj__TMC_EX::
Call__PMC_INIT_SV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
						CII_OBJECT__ALARM* p_alarm)
{
	CString var_data;

	aCH__PARA_PMC_ID->Get__DATA(var_data);
	aEXT_CH__PMx__PARA_PMC_ID->Set__DATA(var_data);

	return pPMx__OBJ_CTRL->Call__OBJECT("INIT_SV_CLOSE");
}

// ALL SV CLOSE -----
int  CObj__TMC_EX::
Call__PMC_ALL_SV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
					   CII_OBJECT__ALARM* p_alarm)
{
	CString var_data;

	aCH__PARA_PMC_ID->Get__DATA(var_data);
	aEXT_CH__PMx__PARA_PMC_ID->Set__DATA(var_data);

	return pPMx__OBJ_CTRL->Call__OBJECT("SV_ALL_CLOSE");
}


// SV OPEN -----
int  CObj__TMC_EX::
Call__PMC_SV_OPEN(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	CString var_data;
	int pm_index;

	aCH__PARA_PMC_ID->Get__DATA(var_data);
	pm_index = atoi(var_data) - 1;

	if(pm_index <  0)					return -1;
	if(pm_index >= CFG_PMx__SIZE)		return -2;

	return Fnc__PMC_SV_OPEN(p_variable,p_alarm,pm_index);
}
int  CObj__TMC_EX::
Fnc__PMC_SV_OPEN(CII_OBJECT__VARIABLE* p_variable,
				 CII_OBJECT__ALARM* p_alarm,
				 const int pm_index)
{
	// ...
	{
		CString pmc_name;
		CII__VAR_ANALOG_CTRL *pch_pmc_pressure;

		pmc_name.Format("PM%1d", pm_index+1);
		pch_pmc_pressure = aEXT_CH__PMx__PRESSURE_TORR[pm_index].Get__PTR();

		if(Check__TRANSFER_PRESSURE(p_variable,p_alarm, pmc_name,pch_pmc_pressure) < 0)
			return -11;
	}

	// ...
	CString var_data;
	
	aCH__PARA_PMC_ID->Get__DATA(var_data);
	aEXT_CH__PMx__PARA_PMC_ID->Set__DATA(var_data);

	return pPMx__OBJ_CTRL->Call__OBJECT("SV_OPEN");
}

int  CObj__TMC_EX::
Fnc__PMC_SV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm,
				  const int pm_index)
{
	CString var_data;

	aCH__PARA_PMC_ID->Get__DATA(var_data);
	aEXT_CH__PMx__PARA_PMC_ID->Set__DATA(var_data);

	return pPMx__OBJ_CTRL->Call__OBJECT("SV_CLOSE");
}
// SV TRANSFER OPEN -----
int  CObj__TMC_EX::
Call__PMC_SV_TRANSFER_OPEN(CII_OBJECT__VARIABLE* p_variable,
						   CII_OBJECT__ALARM* p_alarm)
{
	CString var_data;
	int pm_index;

	aCH__PARA_PMC_ID->Get__DATA(var_data);
	pm_index = atoi(var_data) - 1;

	if(pm_index <  0)					return -1;
	if(pm_index >= CFG_PMx__SIZE)		return -2;

	/*
	// ...
	double cfg_time_sec = 5.0;

	SCX__ASYNC_TIMER_CTRL x_async_timer;
	x_async_timer->START__COUNT_UP(9999);

LOOP_RETRY:

	// SHUTTER OPEN CHECK -----
	while(1)
	{
		CString str__shutter_sts;
		sEXT_CH__PMx__SHUTTER_STATUS[pm_index]->Get__DATA(str__shutter_sts);

		if(str__shutter_sts.Find("OPEN") != 0)
		{
			if(x_async_timer->Get__CURRENT_TIME() < cfg_time_sec)
			{
				Sleep(1);
				continue;
			}

			// ...
			int alarm_id = ALID__PMC_SHUTTER__NOT_OPEN;
			CString alarm_msg;
			CString alarm_bff;
			CString r_act;

			alarm_msg.Format("PM%1d's shutter status is \"%s\" !\n",pm_index+1,str__shutter_sts);
			alarm_bff.Format("Timeout <- (%.3f) sec \n", cfg_time_sec);
			alarm_msg += alarm_bff;

			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alarm_msg,r_act);

			if(r_act.CompareNoCase(ACT__RETRY) == 0)
			{
				goto LOOP_RETRY;
			}
			return -1;
		}

		break;
	}

	// ...
	{
		CString log_msg;
		log_msg.Format("Elapse Time <- (%.3f) sec", x_async_timer->Get__CURRENT_TIME());

		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	*/
	return Fnc__PMC_SV_OPEN(p_variable,p_alarm,pm_index);
}

// SV TRANSFER CLOSE -----
int  CObj__TMC_EX::
Call__PMC_SV_TRANSFER_CLOSE(CII_OBJECT__VARIABLE* p_variable,
							CII_OBJECT__ALARM* p_alarm)
{
	CString var_data;
	int pm_index;

	aCH__PARA_PMC_ID->Get__DATA(var_data);
	pm_index = atoi(var_data) - 1;

	if(pm_index <  0)					return -1;
	if(pm_index >= CFG_PMx__SIZE)		return -2;

	return Fnc__PMC_SV_CLOSE(p_variable,p_alarm,pm_index);
}
