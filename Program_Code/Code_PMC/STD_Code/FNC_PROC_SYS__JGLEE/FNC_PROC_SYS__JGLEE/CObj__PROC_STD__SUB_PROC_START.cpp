#include "StdAfx.h"
#include "CObj__PROC_STD.h"


// ...
int CObj__PROC_STD::
Sub__PROC_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	// Chamber.Pumping ...
	{

	}

	return pOBJ_CTRL__STEP->Call__OBJECT(_STEP_CMD__START);
}
