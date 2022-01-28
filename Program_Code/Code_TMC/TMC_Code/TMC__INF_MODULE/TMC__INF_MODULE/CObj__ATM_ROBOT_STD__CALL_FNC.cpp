#include "StdAfx.h"
#include "CObj__ATM_ROBOT_STD.h"
#include "CObj__ATM_ROBOT_STD__DEF.h"


//----------------------------------------------------------------------------------------------------
int  CObj__ATM_ROBOT_STD::
Call__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return pATM_ROBOT__OBJ_CTRL->Call__OBJECT("INIT");
}
int  CObj__ATM_ROBOT_STD::
Call__HOME(CII_OBJECT__VARIABLE* p_variable)
{
	return pATM_ROBOT__OBJ_CTRL->Call__OBJECT("HOME");
}

int  CObj__ATM_ROBOT_STD::
Call__MAINT(CII_OBJECT__VARIABLE* p_variable)
{
	return pATM_ROBOT__OBJ_CTRL->Call__OBJECT("MAINT");
}

//
int  CObj__ATM_ROBOT_STD::
Call__PICK(CII_OBJECT__VARIABLE* p_variable)
{
	return pATM_ROBOT__OBJ_CTRL->Call__OBJECT("PICK");
}
int  CObj__ATM_ROBOT_STD::
Call__XPICK(CII_OBJECT__VARIABLE* p_variable)
{
	return pATM_ROBOT__OBJ_CTRL->Call__OBJECT("XPICK");
}

//
int  CObj__ATM_ROBOT_STD::
Call__PLACE(CII_OBJECT__VARIABLE* p_variable)
{
	return pATM_ROBOT__OBJ_CTRL->Call__OBJECT("PLACE");
}
int  CObj__ATM_ROBOT_STD::
Call__XPLACE(CII_OBJECT__VARIABLE* p_variable)
{
	return pATM_ROBOT__OBJ_CTRL->Call__OBJECT("XPLACE");
}

//
int  CObj__ATM_ROBOT_STD::
Call__ROTATE(CII_OBJECT__VARIABLE* p_variable)
{
	return pATM_ROBOT__OBJ_CTRL->Call__OBJECT("ROTATE");
}

//
int  CObj__ATM_ROBOT_STD::
Call__LP_MAP(CII_OBJECT__VARIABLE* p_variable)
{
	return pATM_ROBOT__OBJ_CTRL->Call__OBJECT("LP_MAP");
}

//
int  CObj__ATM_ROBOT_STD::
Call__PLACE_ALGN_PICK(CII_OBJECT__VARIABLE* p_variable)
{
	return pATM_ROBOT__OBJ_CTRL->Call__OBJECT("PLACE_PICK");
}



