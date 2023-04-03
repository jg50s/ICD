#include "StdAfx.h"
#include "CObj__LIFT_PIN_IO.h"


// ...
int CObj__LIFT_PIN_IO
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString var_data;
	CString cur_data;

	int loop_count = 0;
	int link_count = 0;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		loop_count++;
		if(loop_count > 10)			loop_count = 1;

		if(loop_count == 1)
		{
			int active__err_check = p_alarm->Check__Posted_Internal_Alarm(iLIST_ALID__PIN);

			if(active__err_check > 0)		dCH__MON_PIN_ERROR_ACTIVE->Set__DATA(STR__ON);
			else							dCH__MON_PIN_ERROR_ACTIVE->Set__DATA(STR__OFF);
		}

		// PIN.STATE  ...
		{
			bool active__up_pos      = false;
			bool active__down_pos    = false;
			bool active__middle_pos  = false;
			bool active__unknown_pos = false;

			// DI.SNS ...
			if(iDATA__PIN_SNS_TYPE == _PIN_TYPE__DI_SNS)
			{
				if(dEXT_CH__DI_PIN_UP->Check__DATA(STR__ON)     > 0)		active__up_pos     = true;		
				if(dEXT_CH__DI_PIN_DOWN->Check__DATA(STR__ON)   > 0)		active__down_pos   = true;		
				if(dEXT_CH__DI_PIN_MIDDLE->Check__DATA(STR__ON) > 0)		active__middle_pos = true;		
			}
			else   // CHECK.POS ...
			{
				for(int i=0; i<iSIZE__AI_PIN__POS; i++)
				{
					double ref__down_min = aCH__CFG_DOWN_POS_MIN__PIN_X[i]->Get__VALUE();
					double ref__down_max = aCH__CFG_DOWN_POS_MAX__PIN_X[i]->Get__VALUE();

					double ref__up_min = aCH__CFG_UP_POS_MIN__PIN_X[i]->Get__VALUE();
					double ref__up_max = aCH__CFG_UP_POS_MAX__PIN_X[i]->Get__VALUE();

					double ref__middle_min = aCH__CFG_MIDDLE_POS_MIN__PIN_X[i]->Get__VALUE();
					double ref__middle_max = aCH__CFG_MIDDLE_POS_MAX__PIN_X[i]->Get__VALUE();

					double cur__pos = aEXT_CH__AI_PIN_POS_X[i]->Get__VALUE();

					if((cur__pos >= ref__down_min)
					&& (cur__pos <= ref__down_max))
					{
						active__down_pos = true;
					}
					else if((cur__pos >= ref__up_min)
						 && (cur__pos <= ref__up_max))
					{
						active__up_pos = true;
					}
					else if((cur__pos >= ref__middle_min)
						 && (cur__pos <= ref__middle_max))
					{
						active__middle_pos = true;
					}
					else
					{
						active__unknown_pos = true;
					}

					if(active__down_pos)		sCH__MON_POS_DOWN_ACTIVE_PIN_X[i]->Set__DATA(STR__ON);
					else						sCH__MON_POS_DOWN_ACTIVE_PIN_X[i]->Set__DATA(STR__OFF);

					if(active__up_pos)			sCH__MON_POS_UP_ACTIVE_PIN_X[i]->Set__DATA(STR__ON);
					else						sCH__MON_POS_UP_ACTIVE_PIN_X[i]->Set__DATA(STR__OFF);

					if(active__middle_pos)		sCH__MON_POS_MIDDLE_ACTIVE_PIN_X[i]->Set__DATA(STR__ON);
					else						sCH__MON_POS_MIDDLE_ACTIVE_PIN_X[i]->Set__DATA(STR__OFF);
				}
			}

			if(iDATA__PIN_SNS_CHECK_MODE == _PIN_CHECK_MODE__TOP)
			{
				if((active__up_pos) && (active__middle_pos) && (active__down_pos))
				{
					sCH__MON_LIFT_STATE->Set__DATA(STR__UP);
				}
				else if((!active__up_pos) && (active__middle_pos) && (active__down_pos))
				{
					sCH__MON_LIFT_STATE->Set__DATA(STR__MIDDLE);
				}
				else if((!active__up_pos) && (!active__middle_pos)&& (active__down_pos))
				{
					sCH__MON_LIFT_STATE->Set__DATA(STR__DOWN);
				}
				else
				{
					sCH__MON_LIFT_STATE->Set__DATA(STR__UNKNOWN);
				}
			}
			else
			{
				if((active__up_pos) && (!active__down_pos) && (!active__middle_pos))
				{
					sCH__MON_LIFT_STATE->Set__DATA(STR__UP);
				}
				else if((!active__up_pos) && (active__down_pos) && (!active__middle_pos))
				{
					sCH__MON_LIFT_STATE->Set__DATA(STR__DOWN);
				}
				else if((!active__up_pos) && (!active__down_pos) && (active__middle_pos))
				{
					sCH__MON_LIFT_STATE->Set__DATA(STR__MIDDLE);
				}
				else
				{
					sCH__MON_LIFT_STATE->Set__DATA(STR__UNKNOWN);
				}
			}
		}

		if(loop_count == 1)
		{
			link_count++;
			if(link_count > 10)			link_count = 1;
		}

		// ...
		{
			sCH__MON_LIFT_STATE->Get__DATA(cur_data);
			var_data.Format("%s.%1d", cur_data,link_count);

			sCH__LIFT_STS_LINK->Set__DATA(var_data);
			sEXT_CH__LIFT_PIN_STATE->Set__DATA(var_data);
		}
	}
}
