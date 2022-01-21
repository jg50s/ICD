#include "StdAfx.h"
#include "CObj__VIRTUAL_TYPE.h"


//------------------------------------------------------------------------------------
void CObj__VIRTUAL_TYPE
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;
	CString var_data;

	while(1)
	{
		cx_timer_ctrl->WAIT(2.0);

		if(iSim_Flag > 0)
		{
			if(diCH__COMM_STS->Check__DATA("OFFLINE") > 0)
			{
				diCH__COMM_STS->Set__DATA("ONLINE");			
			}
		}
		else
		{
			doCH__HEART_BEAT->Set__DATA("ON");
		}

		if(diCH__COMM_STS->Check__DATA("OFFLINE") > 0)
		{
			sCH__COMM_STS->Set__DATA("OFFLINE");
		}
		else
		{
			sCH__COMM_STS->Set__DATA("ONLINE");
		}
	}	
}
