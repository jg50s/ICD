#include "StdAfx.h"
#include "CObj__LBx_STD.h"


//----------------------------------------------------------------------------------------------------
int  CObj__LBx_STD::Call__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx__OBJ_CTRL->Call__OBJECT("INIT");
}
int  CObj__LBx_STD::Call__MAINT(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx__OBJ_CTRL->Call__OBJECT("MAINT");
}

int  CObj__LBx_STD::Call__PUMP(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx__OBJ_CTRL->Call__OBJECT("PUMP");
}
int  CObj__LBx_STD::Call__VENT(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx__OBJ_CTRL->Call__OBJECT("VENT");
}

int  CObj__LBx_STD::Call__PREPMATER(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx__OBJ_CTRL->Call__OBJECT("PREPMATER");
}
int  CObj__LBx_STD::Call__COMPMATER(CII_OBJECT__VARIABLE* p_variable, const int ex_mode)
{
	int r_ret = pLBx__OBJ_CTRL->Call__OBJECT("COMPMATER");

	if(ex_mode > 0)
	{
		if(r_ret > 0)
		{
			r_ret = pLBx__OBJ_CTRL->Call__OBJECT("OUT_PROC");	
		}
	}
	return r_ret;
}

int  CObj__LBx_STD::Call__IN_PROC(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx__OBJ_CTRL->Call__OBJECT("IN_PROC");
}
int  CObj__LBx_STD::Call__OUT_PROC(CII_OBJECT__VARIABLE* p_variable)
{
	return pLBx__OBJ_CTRL->Call__OBJECT("OUT_PROC");
}
