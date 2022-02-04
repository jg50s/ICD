#include "StdAfx.h"
#include "CObj__STEP_STD.h"
#include "CObj__STEP_STD__DEF.h"


// ...
int CObj__STEP_STD
::ESC_OBJ__Start_MODE(const CString& obj_mode)
{
	if(!bActive__OBJ_CTRL__ESC)						return 1;

	return pOBJ_CTRL__ESC->Run__OBJECT(obj_mode);
}
int CObj__STEP_STD
::ESC_OBJ__Start_HE_CLOSE()
{
	if(!bActive__OBJ_CTRL__ESC)						return 1;

	CString obj_mode = _ESC_CMD__HE_CLOSE;

	return pOBJ_CTRL__ESC->Run__OBJECT(obj_mode);
}

int CObj__STEP_STD
::ESC_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__ESC)						return -1;

	int obj_sts = pOBJ_CTRL__ESC->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}
