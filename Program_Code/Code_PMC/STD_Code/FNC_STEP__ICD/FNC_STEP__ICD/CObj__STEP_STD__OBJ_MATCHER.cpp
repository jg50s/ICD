#include "StdAfx.h"
#include "CObj__STEP_STD.h"
#include "CObj__STEP_STD__DEF.h"


// ...
int CObj__STEP_STD
::MAT_LF_OBJ__Start_MODE(const CString& obj_mode)
{
	if(!bActive__OBJ_CTRL__MAT_LF)					return 1;

	return pOBJ_CTRL__MAT_LF->Run__OBJECT(obj_mode);
}

int CObj__STEP_STD
::MAT_LF_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__MAT_LF)					return -1;

	int obj_sts = pOBJ_CTRL__MAT_LF->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}


// ...
int CObj__STEP_STD
::MAT_HF_OBJ__Start_MODE(const CString& obj_mode)
{
	if(!bActive__OBJ_CTRL__MAT_HF)					return 1;

	return pOBJ_CTRL__MAT_HF->Run__OBJECT(obj_mode);
}

int CObj__STEP_STD
::MAT_HF_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__MAT_HF)					return -1;

	int obj_sts = pOBJ_CTRL__MAT_HF->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}
