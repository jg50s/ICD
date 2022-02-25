#include "StdAfx.h"
#include "CObj_Fnc__DUAL_ARM_STD.h"

#include "Macro_Function.h"


// ...
void CObj_Fnc__DUAL_ARM_STD::Mon__PMx_CTRL(CII_OBJECT__VARIABLE *p_variable)
{
	int idle_flag  =  1;
	int abort_flag = -1;

	while(1)
	{
		while(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)
		{
			if(idle_flag < 0)
			{
				if(xSCH_MATERIAL_CTRL->Check__SYSTEM_ABORT() > 0)
				{
					AUTO_CTRL__PMx_ABORT(p_variable);
				}
				else if(xSCH_MATERIAL_CTRL->Check__SYSTEM_STOP() > 0)
				{

				}
				else
				{
					try
					{
						AUTO_CTRL__LBo_PUMP(p_variable);
					}
					catch(int err_flag)
					{

					}
				}
			}

			Sleep(100);
			idle_flag = 1;
		}

		Sleep(1);

		if(idle_flag > 0)
		{
			idle_flag = -1;
		}

	}
}

void CObj_Fnc__DUAL_ARM_STD::AUTO_CTRL__PMx_ABORT(CII_OBJECT__VARIABLE *p_variable)
{

	for(int i=0; i<iPMx_SIZE; i++)
	{
		if(xEXT_CH__CFG__PMx_USE[i]->Check__DATA("ENABLE") < 0)
		{
			continue;
		}
		if(xCH__PMx__OBJ_CTRL[i]->Check__DATA("ABORTED") > 0)
		{
			continue;
		}

		xCH__PMx__OBJ_CTRL[i]->Set__DATA("ABORT");
	}
}
void CObj_Fnc__DUAL_ARM_STD::AUTO_CTRL__PMx_PUMP(CII_OBJECT__VARIABLE *p_variable)
{
	CString log_id = "AUTO_CTRL__PMx_PUMP()";

	for(int i=0; i<iPMx_SIZE; i++)
	{
		if(PMx__Is_Available(i) < 0)
		{
			continue;
		}

		if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
		{
			if(PMx__Is_VAC(i) < 0)
			{
				pPMx__OBJ_CTRL[i]->Run__OBJECT(CMMD__PUMP);
			}
		}
		else
		{
			if(PMx__Is_ATM(i) < 0)
			{
				pPMx__OBJ_CTRL[i]->Run__OBJECT(CMMD__VENT);
			}
		}
	}
}
void CObj_Fnc__DUAL_ARM_STD::AUTO_CTRL__TMC_PUMP(CII_OBJECT__VARIABLE *p_variable)
{

	if(TMC_CHM__Is_Available() > 0)
	{
		if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
		{
			if(TMC_CHM__Is_VAC() < 0)
			{
				pTMC_CHM__OBJ_CTRL->Run__OBJECT(CMMD__PUMP);
			}
		}
		else
		{
			if(TMC_CHM__Is_ATM() < 0)
			{
				pTMC_CHM__OBJ_CTRL->Run__OBJECT(CMMD__VENT);
			}
		}
	}
}
void CObj_Fnc__DUAL_ARM_STD::AUTO_CTRL__LBo_PUMP(CII_OBJECT__VARIABLE *p_variable)
{

	if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("ATM") > 0)
	{
		return;
	}

	// ...
	int ll_limit = iLLx_LIMIT;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
		{
			if((LLx__Is_Available(ll_i)    > 0)
			&& (LLx__Check_All_Empty(ll_i) > 0))
			{
				SCH__LLx_PUMP(ll_i, p_variable);
			}
		}
	}
}
