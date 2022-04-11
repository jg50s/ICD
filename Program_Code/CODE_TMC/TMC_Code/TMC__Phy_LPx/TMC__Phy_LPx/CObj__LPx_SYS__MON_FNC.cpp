#include "StdAfx.h"
#include "CObj__LPx_SYS.h"
#include "CObj__LPx_SYS__DEF.h"


// ...
void CObj__LPx_SYS
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.01);


		// LPx_INFO UPDATE ...
		{
			ch_data = sEXT_CH__LPx__CLAMP_STS->Get__STRING();
			dCH__MON_CLAMP_STS->Set__DATA(ch_data);

			ch_data = sEXT_CH__LPx__FOUP_STS->Get__STRING();
			dCH__MON_FOUP_STS->Set__DATA(ch_data);

			ch_data = sEXT_CH__LPx__FOUP_POS->Get__STRING();
			dCH__MON_FOUP_POS->Set__DATA(ch_data);

			ch_data = sEXT_CH__LPx__DOOR_STS->Get__STRING();
			dCH__MON_DOOR_STS->Set__DATA(ch_data);
		}

		// CHECK : ACTIVE FA AUTO ...
		{
			bool active__fa_auto = false;

			CString obj_state = dEXT_CH__OBJ_STATE->Get__STRING();

			if((obj_state.CompareNoCase(STR__STANDBY)  == 0)
			|| (obj_state.CompareNoCase(STR__CTCINUSE) == 0))
			{
				if((sCH__CFG_FA_MODE->Check__DATA(STR__AUTO) > 0)
				&& (sCH__CFG_FA_SERVICE_MODE->Check__DATA(STR__YES) > 0))
				{
					active__fa_auto = true;
				}
			}

			if(active__fa_auto)			dCH__LINK_PIO_ACTIVE_FA_AUTO->Set__DATA(STR__ON);	
			else						dCH__LINK_PIO_ACTIVE_FA_AUTO->Set__DATA(STR__OFF);
		}

		// ...
	}	
}
