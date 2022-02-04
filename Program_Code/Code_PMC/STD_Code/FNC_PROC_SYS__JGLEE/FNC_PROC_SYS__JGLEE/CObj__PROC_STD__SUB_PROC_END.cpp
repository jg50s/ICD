#include "StdAfx.h"
#include "CObj__PROC_STD.h"


// ...
int CObj__PROC_STD
::Sub__PROC_END(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;

	// ...
	{
		log_msg = "Process End - Start ...";
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	// Step.End ...
	{
		pOBJ_CTRL__STEP->Dislink__UPPER_OBJECT();

		pOBJ_CTRL__STEP->Call__OBJECT(_STEP_CMD__END);

		pOBJ_CTRL__STEP->Link__UPPER_OBJECT();
	}

	// Chamber.Pumping ...
	{
		pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();

		pOBJ_CTRL__CHM->Call__OBJECT(_CHM_CMD__HIGH_VAC_PUMP);

		pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
	}
	return 1;
}
