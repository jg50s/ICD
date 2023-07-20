#include "StdAfx.h"
#include "CObj__STEP_BETA.h"
#include "CObj__STEP_BETA__DEF.h"


// ...
int CObj__STEP_BETA
::FRC_OBJ__Start_CONTROL(const CString& para_center)
{
	if(!bActive__OBJ_CTRL__FRC)						return 1;

	aEXT_CH__FRC_OBJ__CENTER_Wt_SETPOINT->Set__DATA(para_center);

	return pOBJ_CTRL__FRC->Run__OBJECT("CONTROL");
}
