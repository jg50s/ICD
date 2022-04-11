#include "StdAfx.h"
#include "CObj__NXA_PULSE.h"


// ...
int CObj__NXA_PULSE
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int  CObj__NXA_PULSE
::Call__TEST_DRV(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CDS_IO__CHANNEL_INFO io_info;

	// do.CH ...
	{
		CString var_name = doCH__PARAM_A1->Get__VARIABLE_NAME();
		CString set_data = doCH__PARAM_A1->Get__STRING();

		__Write__DIGITAL(var_name, io_info, set_data, 0);
	}

	// do.CH ...
	{
		CString var_name = doCH__SET_EXEC->Get__VARIABLE_NAME();
		CString set_data = doCH__SET_EXEC->Get__STRING();

		__Write__DIGITAL(var_name, io_info, set_data, 0);
	}

	return 1;
}
