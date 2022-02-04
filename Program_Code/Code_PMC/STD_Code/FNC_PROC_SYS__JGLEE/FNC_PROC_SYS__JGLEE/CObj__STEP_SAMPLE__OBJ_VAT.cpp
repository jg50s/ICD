#include "StdAfx.h"
#include "CObj__STEP_SAMPLE.h"
#include "CObj__STEP_SAMPLE__DEF.h"


// ...
int CObj__STEP_SAMPLE
::APC_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data)
{
	if(!bActive__OBJ_CTRL__APC)			return 1;

		 if(obj_mode.CompareNoCase(_APC_CMD__POSITION) == 0)		aEXT_CH__APC_OBJ__PARA_POSITION->Set__DATA(para_data);
	else if(obj_mode.CompareNoCase(_APC_CMD__PRESSURE) == 0)		aEXT_CH__APC_OBJ__PARA_PRESSURE->Set__DATA(para_data);

	return pOBJ_CTRL__APC->Run__OBJECT(obj_mode);
}

