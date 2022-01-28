#include "StdAfx.h"
#include "CObj__LBx_OneManiFold.h"


// ...
void CObj__LBx_OneManiFold
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;
	CString var__data;

	while(1)
	{
		Sleep(9);

		// OBJ STATUS -----
		sCH__OBJ_STATUS->Get__DATA(var__data);
		sEXT_CH__OBJ_STATUS->Set__DATA(var__data);

		// PRESSURE STATUS -----
		dEXT_CH__PRESSURE_STATUS->Get__DATA(var__data);
		sCH__PRESSURE_STATUS->Set__DATA(var__data);
	}	
}
