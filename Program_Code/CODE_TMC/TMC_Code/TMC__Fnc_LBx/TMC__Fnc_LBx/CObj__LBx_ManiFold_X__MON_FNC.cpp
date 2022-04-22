#include "StdAfx.h"
#include "CObj__LBx_ManiFold_X.h"


// ...
void CObj__LBx_ManiFold_X
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString var__data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.01);


		// OBJ STATUS -----
		sCH__OBJ_STATUS->Get__DATA(var__data);
		sEXT_CH__OBJ_STATUS->Set__DATA(var__data);

		// PRESSURE STATUS -----
		dEXT_CH__PRESSURE_STATUS->Get__DATA(var__data);
		sCH__PRESSURE_STATUS->Set__DATA(var__data);
	}	
}
