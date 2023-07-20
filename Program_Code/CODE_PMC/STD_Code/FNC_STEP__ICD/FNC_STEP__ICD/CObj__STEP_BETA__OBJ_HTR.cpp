#include "StdAfx.h"
#include "CObj__STEP_BETA.h"
#include "CObj__STEP_BETA__DEF.h"


// ...
int CObj__STEP_BETA
::HTR_SH_OBJ__Check_ERROR()
{
	if(bActive__OBJ_CTRL__HTR_SH)				return -1;

	for(int i=0; i<_CFG__SH_SIZE; i++)
	{
		if(dEXT_CH__HTR_SH__MON_IDLE_ABORT_ACTIVE_X[i]->Check__DATA(STR__ON) > 0)		return 1;
	}
	return -11;
}


int CObj__STEP_BETA
::HTR_WALL_OBJ__Check_ERROR()
{
	if(bActive__OBJ_CTRL__HTR_WALL)				return -1;

	for(int i=0; i<_CFG__WALL_SIZE; i++)
	{
		if(dEXT_CH__HTR_WALL__MON_IDLE_ABORT_ACTIVE_X[i]->Check__DATA(STR__ON) > 0)		return 1;
	}
	return -11;
}

