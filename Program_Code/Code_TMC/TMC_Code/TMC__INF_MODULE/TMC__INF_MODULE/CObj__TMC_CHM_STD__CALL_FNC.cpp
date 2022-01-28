#include "StdAfx.h"
#include "CObj__TMC_CHM_STD.h"


//----------------------------------------------------------------------------------------------------
int  CObj__TMC_CHM_STD::Call__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return pTMC_CHM__OBJ_CTRL->Call__OBJECT("INIT");
}
int  CObj__TMC_CHM_STD::Call__MAINT(CII_OBJECT__VARIABLE* p_variable)
{
	return pTMC_CHM__OBJ_CTRL->Call__OBJECT("MAINT");
}

//
int  CObj__TMC_CHM_STD::Call__PUMP(CII_OBJECT__VARIABLE* p_variable)
{
	return pTMC_CHM__OBJ_CTRL->Call__OBJECT("PUMP");
}
int  CObj__TMC_CHM_STD::Call__VENT(CII_OBJECT__VARIABLE* p_variable)
{
	return pTMC_CHM__OBJ_CTRL->Call__OBJECT("VENT");
}
