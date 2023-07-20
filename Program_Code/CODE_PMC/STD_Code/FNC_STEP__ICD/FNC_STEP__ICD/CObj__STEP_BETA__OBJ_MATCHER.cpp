#include "StdAfx.h"
#include "CObj__STEP_BETA.h"
#include "CObj__STEP_BETA__DEF.h"


// ...
int CObj__STEP_BETA
::MAT_LF_OBJ__Start_MODE(const CString& obj_mode)
{
	if(!bActive__OBJ_CTRL__MAT_LF)										return 1;
	if(dCH__CFG_RCP_PART_USE_MATx_LF->Check__DATA(STR__YES) < 0)		return 2;

	return pOBJ_CTRL__MAT_LF->Run__OBJECT(obj_mode);
}

int CObj__STEP_BETA
::MAT_LF_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__MAT_LF)										return -1;
	if(dCH__CFG_RCP_PART_USE_MATx_LF->Check__DATA(STR__YES) < 0)		return -2;

	int obj_sts = pOBJ_CTRL__MAT_LF->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}


// ...
int CObj__STEP_BETA
::MAT_HF_OBJ__Start_MODE(const CString& obj_mode)
{
	if(!bActive__OBJ_CTRL__MAT_HF)										return 1;
	if(dCH__CFG_RCP_PART_USE_MATx_HF->Check__DATA(STR__YES) < 0)		return 2;

	return pOBJ_CTRL__MAT_HF->Run__OBJECT(obj_mode);
}

int CObj__STEP_BETA
::MAT_HF_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__MAT_HF)										return -1;
	if(dCH__CFG_RCP_PART_USE_MATx_HF->Check__DATA(STR__YES) < 0)		return -2;

	int obj_sts = pOBJ_CTRL__MAT_HF->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}
