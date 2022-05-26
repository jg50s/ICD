#include "StdAfx.h"
#include "CObj__STEP_STD.h"
#include "CObj__STEP_STD__DEF.h"


// ...
int CObj__STEP_STD
::EPD_OBJ__Call_INIT()
{
	if(!bActive__OBJ_CTRL__EPD)					return 1;

	// ...
	CString obj_mode = _EPD_CMD__INIT;

	return pOBJ_CTRL__EPD->Call__OBJECT(obj_mode);
}

int CObj__STEP_STD
::EPD_OBJ__Start_IDLE()
{
	if(!bActive__OBJ_CTRL__EPD)					return 1;

	// ...
	CString obj_mode = _EPD_CMD__IDLE;

	return pOBJ_CTRL__EPD->Run__OBJECT(obj_mode);
}
int CObj__STEP_STD
::EPD_OBJ__Start_CHECK()
{
	if(!bActive__OBJ_CTRL__EPD)					return 1;

	// ...
	CString obj_mode = _EPD_CMD__ERROR_CHECK;

	return pOBJ_CTRL__EPD->Run__OBJECT(obj_mode);
}
int CObj__STEP_STD
::EPD_OBJ__Start_DETECT()
{
	if(!bActive__OBJ_CTRL__EPD)					return 1;

	// ...
	CString obj_mode = _EPD_CMD__DETECT;

	return pOBJ_CTRL__EPD->Run__OBJECT(obj_mode);
}

int CObj__STEP_STD
::EPD_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__EPD)					return -1;

	int obj_sts = pOBJ_CTRL__EPD->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)		return 1;		

	return -1;
}

int CObj__STEP_STD
::EPD_OBJ__Is_BUSY()
{
	if(!bActive__OBJ_CTRL__EPD)					return -1;

	return pOBJ_CTRL__EPD->Is__OBJ_BUSY();
}

int CObj__STEP_STD
::EPD_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__EPD)					return -1;

	if(dEXT_CH__EPD__MON_ERROR_ACTIVE->Check__DATA(STR__ON) > 0)			return 1;

	return -1;
}
