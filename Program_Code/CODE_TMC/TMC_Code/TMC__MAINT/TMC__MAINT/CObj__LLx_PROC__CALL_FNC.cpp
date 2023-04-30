#include "StdAfx.h"
#include "CObj__LLx_PROC.h"
#include "CObj__LLx_PROC__DEF.h"


// ...
#define _CMMD_PROC__MNT_READY				"MNT_READY"
#define _CMMD_PROC__MNT_START				"MNT_START"


int CObj__LLx_PROC::Call__MANUAL_PROCESS(CII_OBJECT__VARIABLE* p_variable)
{
	int flag;

	// ...
	{
		CString var_data = sCH__SEL_RECIPE_NAME->Get__STRING();
		sEXT_CH__RCP_NAME->Set__DATA(var_data);
	}

	flag = pOBJ_CTRL__PROC->Call__OBJECT(_CMMD_PROC__MNT_READY);
	if(flag < 0)		return -1;

	flag = pOBJ_CTRL__PROC->Call__OBJECT(_CMMD_PROC__MNT_START);
	if(flag < 0)		return -2;

	return flag;
}

