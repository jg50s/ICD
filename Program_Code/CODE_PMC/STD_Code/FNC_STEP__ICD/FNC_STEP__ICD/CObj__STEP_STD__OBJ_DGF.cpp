#include "StdAfx.h"
#include "CObj__STEP_STD.h"
#include "CObj__STEP_STD__DEF.h"


// ...
int CObj__STEP_STD
::DGF_OBJ__Start_CONTROL(const CString& para_center)
{
	if(!bActive__OBJ_CTRL__APC)						return 1;

	aEXT_CH__DGF_OBJ__CENTER_Wt_SETPOINT->Set__DATA(para_center);

	return pOBJ_CTRL__DGF->Run__OBJECT("CONTROL");
}
