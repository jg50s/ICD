#include "StdAfx.h"
#include "CObj__ACTIVE_HANDOFF_INF.h"


// ...
int CObj__ACTIVE_HANDOFF_INF
::Call__TRANSFER_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// OBJ.PM_SLOT ...
	if(bActive__OBJ_CTRL__PM_SLOT)
	{
		int r_flag = pOBJ_CTRL__PM_SLOT->Call__OBJECT(sLINK_MODE__PM_SLOT__OPEN);
		if(r_flag < 0)		return -11;
	}		
	// OBJ.SHUTTER ...
	if(bActive__OBJ_CTRL__SHUTTER)
	{
		int r_flag = pOBJ_CTRL__SHUTTER->Call__OBJECT(sLINK_MODE__SHUTTER__OPEN);
		if(r_flag < 0)		return -21;
	}

	// OBJ.LIFT_PIN ...
	if(bActive__OBJ_CTRL__LIFT_PIN)
	{
		int r_flag = pOBJ_CTRL__LIFT_PIN->Call__OBJECT(sLINK_MODE__LIFT_PIN_UP);
		if(r_flag < 0)		return -31;		
	}

	return 1;
}
int CObj__ACTIVE_HANDOFF_INF
::Call__TRANSFER_END(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// OBJ.LIFT_PIN ...
	if(bActive__OBJ_CTRL__LIFT_PIN)
	{
		int r_flag = pOBJ_CTRL__LIFT_PIN->Run__OBJECT(sLIST_MODE__LIFT_PIN_DOWN);
		if(r_flag < 0)		return -11;		
	}

	// OBJ.PM_SLOT ...
	if(bActive__OBJ_CTRL__PM_SLOT)
	{
		int r_flag = pOBJ_CTRL__PM_SLOT->Call__OBJECT(sLINK_MODE__PM_SLOT__CLOSE);
		if(r_flag < 0)		return -11;
	}		
	// OBJ.SHUTTER ...
	if(bActive__OBJ_CTRL__SHUTTER)
	{
		int r_flag = pOBJ_CTRL__SHUTTER->Call__OBJECT(sLINK_MODE__SHUTTER__CLOSE);
		if(r_flag < 0)		return -21;
	}

	return 1;
}
