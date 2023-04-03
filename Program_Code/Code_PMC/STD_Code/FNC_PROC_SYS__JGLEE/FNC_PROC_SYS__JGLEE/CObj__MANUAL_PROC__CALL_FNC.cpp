#include "StdAfx.h"
#include "CObj__MANUAL_PROC.h"

#include "CCommon_System.h"


// ...
int CObj__MANUAL_PROC::Call__MANUAL_PROCESS(CII_OBJECT__VARIABLE* p_variable)
{
	CString ch_data;

	aCH__CFG_AGING_COUNT->Get__DATA(ch_data);
	sCH__CUR_AGING_COUNT->Set__DATA("");

	int trg_count = atoi(ch_data);
	int cur_count = 0;

	while(1)
	{
		// ...
		{
			cur_count++;
			ch_data.Format("%1d", cur_count);
			sCH__CUR_AGING_COUNT->Set__DATA(ch_data);
		}

		sEXT_CH__SYSTEM_MSG->Set__DATA("Manual Process Start ...");
		sEXT_CH__FNC_MSG->Set__DATA("");

		int r_flag = Fnc__MANUAL_PROCESS(p_variable);

		dEXT_CH__PARA_MANUAL_STEP_CTRL_ACTIVE->Set__DATA(STR__OFF);
		sEXT_CH__PARA_MANUAL_STEP_CTRL_REQ->Set__DATA("");

		if(r_flag < 0)
		{
			return -11;
		}
		if(cur_count >= trg_count)
		{
			return 1;
		}
	}

	return 1;
}
int CObj__MANUAL_PROC::Fnc__MANUAL_PROCESS(CII_OBJECT__VARIABLE* p_variable)
{
	// Manual Step.Ctrl ...
	{
		dEXT_CH__PARA_MANUAL_STEP_CTRL_ACTIVE->Set__DATA(STR__OFF);
		sEXT_CH__PARA_MANUAL_STEP_CTRL_REQ->Set__DATA("");

		if(dCH__CFG_MANUAL_STEP_CTRL->Check__DATA(STR__ENABLE) > 0)
		{
			dEXT_CH__PARA_MANUAL_STEP_CTRL_ACTIVE->Set__DATA(STR__ON);
		}
	}

	// ...
	{
		CString var_data = sCH__PARA_RECIPE_NAME->Get__STRING();
		sEXT_CH__RCP_NAME->Set__DATA(var_data);
	}

	int flag = pOBJ_CTRL__PROC->Call__OBJECT(_PROC_CMMD__MANUAL_READY);
	if(flag < 0)		return -11;

	flag = pOBJ_CTRL__PROC->Call__OBJECT(_PROC_CMMD__MANUAL_START);
	if(flag < 0)		return -12;

	return 1;
}

int CObj__MANUAL_PROC::Call__ABORTL_DECHUCK(CII_OBJECT__VARIABLE* p_variable)
{
	// ...
	{
		CString var_data = sEXT_CH__RCP_ABORT_DECHUCK->Get__STRING();
		sEXT_CH__RCP_NAME->Set__DATA(var_data);
	}

	int flag = pOBJ_CTRL__PROC->Call__OBJECT(_PROC_CMMD__MANUAL_READY);
	if(flag < 0)		return -11;

	flag = pOBJ_CTRL__PROC->Call__OBJECT(_PROC_CMMD__MANUAL_START);
	if(flag < 0)		return -12;

	return flag;
}

int CObj__MANUAL_PROC::Call__DECHUCK_LIST(CII_OBJECT__VARIABLE* p_variable)
{
	// ...
	{
		CString var_data = sCH__PARA_DECHUCK_LIST->Get__STRING();
		sEXT_CH__RCP_NAME->Set__DATA(var_data);
	}

	int flag = pOBJ_CTRL__PROC->Call__OBJECT(_PROC_CMMD__MANUAL_READY);
	if(flag < 0)		return -11;

	flag = pOBJ_CTRL__PROC->Call__OBJECT(_PROC_CMMD__MANUAL_START);
	if(flag < 0)		return -12;

	return flag;
}
