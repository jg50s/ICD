#include "StdAfx.h"
#include "CObj__VAC_ROBOT_STD.h"


//----------------------------------------------------------------------------------------------------
int  CObj__VAC_ROBOT_STD::Call__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return pVAC_ROBOT__OBJ_CTRL->Call__OBJECT("INIT");
}
int  CObj__VAC_ROBOT_STD::Call__MAINT(CII_OBJECT__VARIABLE* p_variable)
{
	return pVAC_ROBOT__OBJ_CTRL->Call__OBJECT("MAINT");
}

//
int  CObj__VAC_ROBOT_STD::Call__PICK(CII_OBJECT__VARIABLE* p_variable)
{
	return pVAC_ROBOT__OBJ_CTRL->Call__OBJECT("PICK");
}
int  CObj__VAC_ROBOT_STD::Call__XPICK(CII_OBJECT__VARIABLE* p_variable)
{
	return pVAC_ROBOT__OBJ_CTRL->Call__OBJECT("XPICK");
}

int  CObj__VAC_ROBOT_STD::Call__PLACE(CII_OBJECT__VARIABLE* p_variable)
{
	return pVAC_ROBOT__OBJ_CTRL->Call__OBJECT("PLACE");
}
int  CObj__VAC_ROBOT_STD::Call__XPLACE(CII_OBJECT__VARIABLE* p_variable)
{
	return pVAC_ROBOT__OBJ_CTRL->Call__OBJECT("XPLACE");
}

int  CObj__VAC_ROBOT_STD::Call__ROTATE(CII_OBJECT__VARIABLE* p_variable)
{
	return pVAC_ROBOT__OBJ_CTRL->Call__OBJECT("ROTATE");
}
