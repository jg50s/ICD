#include "StdAfx.h"
#include "CObj__ACTIVE_HANDOFF_INF.h"


// ...
int CObj__ACTIVE_HANDOFF_INF
::Call__INIT( CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm )
{
	return 1;
}


// Pick
int CObj__ACTIVE_HANDOFF_INF
::Call__S1(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
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

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__S1);
}
int CObj__ACTIVE_HANDOFF_INF
::Call__S2(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__S2);
}
int CObj__ACTIVE_HANDOFF_INF
::Call__S3(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// S3 ...
	{
		int r_flag = p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__S3);
		if(r_flag < 0)		return -1;
	}

	// OBJ.SHUTTER ...
	if(bActive__OBJ_CTRL__SHUTTER)
	{
		int r_flag = pOBJ_CTRL__SHUTTER->Call__OBJECT(sLINK_MODE__SHUTTER__CLOSE);
		if(r_flag < 0)		return -11;
	}
	// OBJ.PM_SLOT ...
	if(bActive__OBJ_CTRL__PM_SLOT)
	{
		int r_flag = pOBJ_CTRL__PM_SLOT->Call__OBJECT(sLINK_MODE__PM_SLOT__CLOSE);
		if(r_flag < 0)		return -21;
	}		

	return 1;
}


// Place
int CObj__ACTIVE_HANDOFF_INF
::Call__R1(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
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

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__R1);
}
int CObj__ACTIVE_HANDOFF_INF
::Call__R2(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__R2);
}
int CObj__ACTIVE_HANDOFF_INF
::Call__R3(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// R3 ...
	{
		int r_flag = p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__R3);
		if(r_flag < 0)		return -1;
	}

	// OBJ.SHUTTER ...
	if(bActive__OBJ_CTRL__SHUTTER)
	{
		int r_flag = pOBJ_CTRL__SHUTTER->Call__OBJECT(sLINK_MODE__SHUTTER__CLOSE);
		if(r_flag < 0)		return -11;
	}
	// OBJ.PM_SLOT ...
	if(bActive__OBJ_CTRL__PM_SLOT)
	{
		int r_flag = pOBJ_CTRL__PM_SLOT->Call__OBJECT(sLINK_MODE__PM_SLOT__CLOSE);
		if(r_flag < 0)		return -21;
	}		

	return 1;
}


// Pick -> Place
int CObj__ACTIVE_HANDOFF_INF
::Call__SX1(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
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

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__S1);
}
int CObj__ACTIVE_HANDOFF_INF
::Call__SX2(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__S2);
}
int CObj__ACTIVE_HANDOFF_INF
::Call__SX3(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__S3);
}

int CObj__ACTIVE_HANDOFF_INF
::Call__SX4(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__R1);
}
int CObj__ACTIVE_HANDOFF_INF
::Call__SX5(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__R2);
}
int CObj__ACTIVE_HANDOFF_INF
::Call__SX6(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__R3);
}


// Place -> Pick
int CObj__ACTIVE_HANDOFF_INF
::Call__RX1(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	return -1;
}
int CObj__ACTIVE_HANDOFF_INF
::Call__RX2(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	return -1;
}
int CObj__ACTIVE_HANDOFF_INF
::Call__RX3(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	return -1;
}
int CObj__ACTIVE_HANDOFF_INF
::Call__RX4(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	return -1;
}
int CObj__ACTIVE_HANDOFF_INF
::Call__RX5(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	return -1;
}
int CObj__ACTIVE_HANDOFF_INF
::Call__RX6(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	return -1;
}