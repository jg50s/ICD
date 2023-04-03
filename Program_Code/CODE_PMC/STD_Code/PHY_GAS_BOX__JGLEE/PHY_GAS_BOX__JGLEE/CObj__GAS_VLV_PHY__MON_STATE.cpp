#include "StdAfx.h"
#include "CObj__GAS_VLV_PHY.h"

#include "CCommon_Utility.h"
#include "Macro__Function.h"

#include "CCommon_Def.h"


// ...
int  CObj__GAS_VLV_PHY
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		// CHECK : PROC_VALVE STATE ...
		{
			bool active__proc_state = true;

			for(int i=0; i<iSIZE__TOP_CHM__VLV_PROC; i++)
			{
				if(dEXT_CH__TOP_CHM__VLV_PROC[i]->Check__DATA(STR__OPEN) > 0)		continue;

				active__proc_state = false;
				break;
			}

			if(active__proc_state)		dEXT_CH__MON_ACTIVE_PROCESS_VALVE_READY_STATE->Set__DATA(STR__ON);
			else						dEXT_CH__MON_ACTIVE_PROCESS_VALVE_READY_STATE->Set__DATA(STR__OFF);
		}
	}

	return 1;
}

