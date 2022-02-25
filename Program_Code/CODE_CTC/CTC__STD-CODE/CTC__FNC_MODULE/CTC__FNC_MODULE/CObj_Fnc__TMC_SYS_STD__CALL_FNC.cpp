#include "StdAfx.h"
#include "CObj_Fnc__TMC_SYS_STD.h"


#define STR__ENABLE			"ENABLE"


// ...
int  CObj_Fnc__TMC_SYS_STD::Call__ALL_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	if(xCH_CFG__INIT_MODE->Check__DATA("AUTO") > 0)
	{
		if(Fnc__AUTO_INIT(p_variable) < 0)			return -1;
	}
	else if(xCH_CFG__INIT_MODE->Check__DATA("ONLY_SYSTEM") > 0)
	{
		if(Call__SYSTEM_INIT(p_variable) < 0)		return -1;
	}
	else
	{
		if(Call__TIME_INIT(p_variable)   < 0)		return -1;
		Sleep(300);
		if(Call__SYSTEM_INIT(p_variable) < 0)		return -1;
	}

	return 1;
}
int  CObj_Fnc__TMC_SYS_STD::Call__TIME_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__TIME_INIT);
}
int  CObj_Fnc__TMC_SYS_STD::Call__SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__SYSTEM_INIT);
}

int  CObj_Fnc__TMC_SYS_STD::Fnc__AUTO_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__AUTO_INIT);
}

//
int  CObj_Fnc__TMC_SYS_STD::Call__CTC_TO_TMC(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__CTC_TO_TMC);
}
int  CObj_Fnc__TMC_SYS_STD::Call__TMC_TO_CTC(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__TMC_TO_CTC);
}

//
int  CObj_Fnc__TMC_SYS_STD::Call__WAFER_RESYNC_CLEAR_SYS(CII_OBJECT__VARIABLE* p_variable)
{
	pOBJ_CTRL__ATM_ROBOT->Call__OBJECT("WAFER_RESYNC.CLEAR_SYS");
	pOBJ_CTRL__VAC_ROBOT->Call__OBJECT("WAFER_RESYNC.CLEAR_SYS");
	return 1;
}
int  CObj_Fnc__TMC_SYS_STD::Call__WAFER_RESYNC_CLEAR_PMx(CII_OBJECT__VARIABLE* p_variable)
{
	pOBJ_CTRL__VAC_ROBOT->Call__OBJECT("WAFER_RESYNC.CLEAR_PMx");
	return 1;
}
int  CObj_Fnc__TMC_SYS_STD::Call__WAFER_RESYNC_CLEAR_LLx(CII_OBJECT__VARIABLE* p_variable)
{
	pOBJ_CTRL__VAC_ROBOT->Call__OBJECT("WAFER_RESYNC.CLEAR_LLx");
	return 1;
}

//
int  CObj_Fnc__TMC_SYS_STD::Call__SYSTEM_MAINT(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__SYSTEM_MAINT);
}
