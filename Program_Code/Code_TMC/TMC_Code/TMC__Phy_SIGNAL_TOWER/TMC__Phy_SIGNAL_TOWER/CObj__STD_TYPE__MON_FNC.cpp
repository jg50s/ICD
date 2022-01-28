#include "StdAfx.h"
#include "CObj__STD_TYPE.h"
#include "CObj__STD_TYPE__DEF.h"


//----------------------------------------------------------------------------------------------------
void CObj__STD_TYPE
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CII__VAR_DIGITAL_CTRL *pch__on_off;
	CII__VAR_DIGITAL_CTRL *pch__blink;
	CII__VAR_STRING_CTRL  *pch__set;
	CString var_data, var_num;
	int i;

	SCX__TIMER_CTRL x_timer_ctrl;


	while(1)
	{
		// ...
		{
			aCH__CFG_BLINK_PERIOD_SEC->Get__DATA(var_data);
			double cfg_sec = atof(var_data);

			x_timer_ctrl->POLL(cfg_sec);
		}

		int active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

		// ...
		{
			int i_limit = 5;

			for(i=0; i<i_limit; i++)
			{
				if(i == 0)				// RED
				{
					pch__on_off = doEXT_CH__LIGHT_RED__ON_OFF.Get__PTR();
					pch__blink  = doEXT_CH__LIGHT_RED__BLINK.Get__PTR();
					pch__set    = sCH__LINK_SET_LIGHT_RED.Get__PTR();

					if(active__remote_mode > 0)		dCH__LIGHT_RED->Get__DATA(var_data);	
					else							dCH__LINK_LOCAL_LIGHT_RED->Get__DATA(var_data);	
				}
				else if(i == 1)			// YELLOW
				{
					pch__on_off = doEXT_CH__LIGHT_YELLOW__ON_OFF.Get__PTR();
					pch__blink  = doEXT_CH__LIGHT_YELLOW__BLINK.Get__PTR();
					pch__set    = sCH__LINK_SET_LIGHT_YELLOW.Get__PTR();

					if(active__remote_mode > 0)		dCH__LIGHT_YELLOW->Get__DATA(var_data);
					else							dCH__LINK_LOCAL_LIGHT_YELLOW->Get__DATA(var_data);
				}
				else if(i == 2)			// GREEN
				{
					pch__on_off = doEXT_CH__LIGHT_GREEN__ON_OFF.Get__PTR();
					pch__blink  = doEXT_CH__LIGHT_GREEN__BLINK.Get__PTR();
					pch__set    = sCH__LINK_SET_LIGHT_GREEN.Get__PTR();

					if(active__remote_mode > 0)		dCH__LIGHT_GREEN->Get__DATA(var_data);
					else							dCH__LINK_LOCAL_LIGHT_GREEN->Get__DATA(var_data);
				}
				else if(i == 3)			// BLUE
				{
					pch__on_off = doEXT_CH__LIGHT_BLUE__ON_OFF.Get__PTR();
					pch__blink  = doEXT_CH__LIGHT_BLUE__BLINK.Get__PTR();
					pch__set    = sCH__LINK_SET_LIGHT_BLUE.Get__PTR();

					if(active__remote_mode > 0)		dCH__LIGHT_BLUE->Get__DATA(var_data);
					else							dCH__LINK_LOCAL_LIGHT_BLUE->Get__DATA(var_data);
				}
				else if(i == 4)			// WHITE
				{
					pch__on_off = doEXT_CH__LIGHT_WHITE__ON_OFF.Get__PTR();
					pch__blink  = doEXT_CH__LIGHT_WHITE__BLINK.Get__PTR();
					pch__set    = sCH__LINK_SET_LIGHT_WHITE.Get__PTR();

					if(active__remote_mode > 0)		dCH__LIGHT_WHITE->Get__DATA(var_data);
					else							dCH__LINK_LOCAL_LIGHT_WHITE->Get__DATA(var_data);
				}
				else
				{
					continue;
				}

				pch__set->Set__DATA(var_data);

				if(var_data.CompareNoCase(STR__OFF) == 0)
				{
					if((pch__on_off->Check__DATA(STR__OFF) < 0) 
					|| (pch__blink->Check__DATA(STR__OFF)  < 0))
					{
						pch__on_off->Set__DATA(STR__OFF);
						pch__blink->Set__DATA(STR__OFF);
					}
				}
				else if(var_data.CompareNoCase(STR__ON) == 0)
				{
					if(pch__on_off->Check__DATA(STR__ON) < 0)
					{
						pch__on_off->Set__DATA(STR__ON);
						pch__blink->Set__DATA(STR__OFF);
					}
				}
				else if(var_data.CompareNoCase(STR__BLINK) == 0)
				{
					if(dCH__CFG_BLINK_MODE_USE->Check__DATA(STR__ENABLE) > 0)
					{
						if(pch__blink->Check__DATA(STR__ON) < 0)
						{
							pch__on_off->Set__DATA(STR__OFF);
							pch__blink->Set__DATA(STR__ON);
						}
					}
					else 
					{
						if(pch__on_off->Check__DATA(STR__OFF) > 0)
							pch__on_off->Set__DATA(STR__ON);
						else
							pch__on_off->Set__DATA(STR__OFF);

						pch__blink->Set__DATA(STR__OFF);
					}
				}
			}
		}

		// Buzzer ...
		{
			dCH__CFG_BUZZER_USE->Get__DATA(var_data);

			if(var_data.CompareNoCase(STR__NO) == 0)
			{
				sCH__LINK_SET_ALARM_BUZZER->Set__DATA(STR__OFF);

				Seq__SET_BUZZER_OFF();
			}
			else if(var_data.CompareNoCase(STR__YES) == 0)
			{
				if(active__remote_mode > 0)			dCH__ALARM_BUZZER->Get__DATA(var_data);
				else								dCH__LINK_LOCAL_ALARM_BUZZER->Get__DATA(var_data);

				sCH__LINK_SET_ALARM_BUZZER->Set__DATA(var_data);

				if(var_data.CompareNoCase(STR__OFF) == 0)
				{
					Seq__SET_BUZZER_OFF();
				}
				else if(var_data.CompareNoCase(STR__ON) == 0)
				{
					Seq__SET_BUZZER_ON();
				}
			}
		}

		// Melody ...
		{
			dCH__CFG_MELODY_USE->Get__DATA(var_data);

			if(var_data.CompareNoCase(STR__NO) == 0)
			{
				sCH__LINK_SET_MELODY_BUZZER->Set__DATA(STR__OFF);

				for (i=0; i<CFG_MELODY_MAX; i++)
				{
					if(doEXT_CH__MELODY[i]->Check__DATA(STR__OFF) < 0)
					{
						doEXT_CH__MELODY[i]->Set__DATA(STR__OFF);
					}
				}
			}
			else if(var_data.CompareNoCase(STR__YES) == 0)
			{
				if(active__remote_mode > 0)			dCH__MELODY_BUZZER->Get__DATA(var_data);
				else								dCH__LINK_LOCAL_MELODY_BUZZER->Get__DATA(var_data);

				sCH__LINK_SET_MELODY_BUZZER->Set__DATA(var_data);

				if(var_data.CompareNoCase(STR__OFF) == 0)
				{
					for (i=0; i<CFG_MELODY_MAX; i++)
					{
						if(doEXT_CH__MELODY[i]->Check__DATA(STR__OFF) < 0)
						{
							doEXT_CH__MELODY[i]->Set__DATA(STR__OFF);
						}
					}
				}
				else if(var_data.CompareNoCase(STR__ON) == 0)
				{
					dCH__CFG_MELODY_NUM->Get__DATA(var_num);
					i = atoi(var_num)-1;

					for (int j=0; j<CFG_MELODY_MAX; j++)
					{
						if(i == j)
						{
							continue;
						}

						if(doEXT_CH__MELODY[j]->Check__DATA(STR__OFF) < 0)
						{
							doEXT_CH__MELODY[j]->Set__DATA(STR__OFF);
						}
					}

					if(doEXT_CH__MELODY[i]->Check__DATA(STR__ON) < 0)
					{
						doEXT_CH__MELODY[i]->Set__DATA(STR__ON);
					}
				}
			}
		}

		// ...
	}	
}

