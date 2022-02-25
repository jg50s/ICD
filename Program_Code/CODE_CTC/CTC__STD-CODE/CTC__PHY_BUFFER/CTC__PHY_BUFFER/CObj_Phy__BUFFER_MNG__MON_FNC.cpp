#include "StdAfx.h"
#include "CObj_Phy__BUFFER_MNG.h"


// ...
void CObj_Phy__BUFFER_MNG
::Mon__STATUS_CTRL(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL x_timer_ctrl;

	CString var_data;
	int obj_ihdex = -1;


	while(1)
	{
		x_timer_ctrl->POLL(1.0);

		// ...
		{
			CString cur_sel = sCH__SEL_BUFFER->Get__STRING();

			obj_ihdex = -1;

			int i_limit = iSIZE__BUFFERx;
			int i;

			for(i=0; i<i_limit; i++)
			{
				var_data.Format("BUFFER%1d", i+1);
				if(cur_sel.CompareNoCase(var_data) != 0)
					continue;

				obj_ihdex = i;
				break;
			}

			// ...
			CString ch_state;
			CString ch_title;
			CString ch_sec;

			int k_limit = CFG_CLx__SLOT_MAX;
			int k;

			if(obj_ihdex < 0)
			{
				// PARAMETER ...
				{
					sCH__CFG_SLOT_MAX->Set__DATA("?");
					sCH__CFG_CST_FLAG->Set__DATA("UNKNOWN");

					sCH__APP_CUR_LOTID->Set__DATA("?");
					sCH__APP_NEXT_SLOT_TO_PLACE->Set__DATA("?");
					sCH__APP_NEXT_SLOT_TO_PICK->Set__DATA("?");
				}

				// ...
				ch_state = "UNKNOWN";
				ch_title = "";
				ch_sec   = "?";

				for(k=0; k<k_limit; k++)
				{
					sCH__SLOT_STATUS[k]->Set__DATA(ch_state);
					sCH__SLOT_TITLE[k]->Set__DATA(ch_title);
					sCH__SLOT_WAIT_SEC[k]->Set__DATA(ch_sec);
				}
			}
			else
			{
				// PARAMETER ...
				{
					var_data = sEXT_CH__CFG_SLOT_MAX[obj_ihdex]->Get__STRING();
					sCH__CFG_SLOT_MAX->Set__DATA(var_data);
					
					var_data = sEXT_CH__CFG_CST_FLAG[obj_ihdex]->Get__STRING();
					sCH__CFG_CST_FLAG->Set__DATA(var_data);

					//
					var_data = sEXT_CH__APP_CUR_LOTID[obj_ihdex]->Get__STRING();
					sCH__APP_CUR_LOTID->Set__DATA(var_data);
					
					var_data = sEXT_CH__APP_NEXT_SLOT_TO_PLACE[obj_ihdex]->Get__STRING();
					sCH__APP_NEXT_SLOT_TO_PLACE->Set__DATA(var_data);
					
					var_data = sEXT_CH__APP_NEXT_SLOT_TO_PICK[obj_ihdex]->Get__STRING();
					sCH__APP_NEXT_SLOT_TO_PICK->Set__DATA(var_data);
				}

				for(k=0; k<k_limit; k++)
				{
					ch_state = sEXT_CH__SLOT_STATUS_X[obj_ihdex][k]->Get__STRING();
					ch_title = sEXT_CH__SLOT_TITLE_X[obj_ihdex][k]->Get__STRING();
					ch_sec   = sEXT_CH__SLOT_WAIT_SEC_X[obj_ihdex][k]->Get__STRING();

					sCH__SLOT_STATUS[k]->Set__DATA(ch_state);
					sCH__SLOT_TITLE[k]->Set__DATA(ch_title);
					sCH__SLOT_WAIT_SEC[k]->Set__DATA(ch_sec);
				}
			}
		}

		// ...
	}
}
