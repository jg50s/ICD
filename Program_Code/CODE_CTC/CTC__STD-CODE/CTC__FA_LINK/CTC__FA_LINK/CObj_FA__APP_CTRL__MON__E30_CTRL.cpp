#include "StdAfx.h"
#include "CObj_FA__APP_CTRL.h"


#include "CMacro_FA.h"
extern CMacro_FA mFA_Link;


// ...
void CObj_FA__APP_CTRL::Mon__E30_CTRL(CII_OBJECT__VARIABLE* p_variable)
{
	// Hearbeat ...
	int sec_count = 0;

	// Terminal Message ...
	CString pre_msg;
	int log_count = -1;

	xCH__TERMINAL_LOG_COUNT->Set__DATA("0");

	// ...
	CString pre_fa_flag;
	CString cur_fa_flag;

	CString pre_time;
	CString cur_time;

	CString var_str;
	int var_i;

	CI_FA_DB__ECID_CTRL* p_ecid_ctrl = mFA_Link.Get__FA_ECID_CTRL();
	CI_FA_VARIABLE_CTRL* p_var_ctrl  = mFA_Link.Get__FA_VAR_CTRL();

	CString main_name;
	CString sub_name;
	CString var_data;

	int  flag__fa_connected = -1;


	while(1)
	{
		Sleep(490);


		// Heatbeat Control ...
		{
			Fnc__HEARTBEAT_CTRL(p_variable, sec_count);
		}

		// Terminal Message ...
		{
			Fnc__TERMINAL_LOG_CTRL(p_variable, pre_msg, log_count);
		}

		// REQ : Time From HOst ...
		if(xCH__TIME_FROM_HOST_REQ->Check__DATA("YES") > 0)
		{
			xCH__TIME_FROM_HOST_REQ->Set__DATA("");

			mFA_Link.Send__S2F17();
		}

		// ...
		{
			if(mFA_Link.Is__CONNECTED() > 0)
			{
				xCH__FA_CONNECTION_STATUS->Set__DATA(STR__ONLINE);

				if(flag__fa_connected < 0)
				{
					flag__fa_connected = 1;

					if(dCH__CFG_AUTO_REMOTE_CONNECTION->Check__DATA(STR__ENABLE) > 0)
					{
						xCH__FA_REQ->Set__DATA(STR__REMOTE);
					}
				}
			}
			else
			{
				xCH__FA_CONNECTION_STATUS->Set__DATA(STR__OFFLINE);

				// ...
				{
					flag__fa_connected = -1;
				}
			}
		}

		// ...
		{
			var_i = p_ecid_ctrl->Get_ECID__TIME_FORMAT();
			var_data.Format("%1d",var_i);

			xCH__TIME_FORMAT_TYPE->Set__DATA(var_data);
		}

		if(iFLAG__DEVICE_ID_CONTROL > 0)
		{
			xCH_CFG__DEVICEID->Get__DATA(var_data);
			int device_id = atoi(var_data);

			p_ecid_ctrl->Set__DEVICE_ID(device_id);
		}

		// SxFy Reply Control ...
		{
			CString cur_data;

			// S5Fy Reply ...
			{
				xCH_CFG__S5Fy_REPLY_CTRL->Get__DATA(cur_data);

				if(cur_data.CompareNoCase(STR__ENABLE) == 0)
				{
					p_ecid_ctrl->Set__S5Fy_Reply(1);
				}
				else if(cur_data.CompareNoCase(STR__DISABLE) == 0)
				{
					p_ecid_ctrl->Set__S5Fy_Reply(0);					
				}
			}

			// S6Fy Reply ...
			{
				xCH_CFG__S6Fy_REPLY_CTRL->Get__DATA(cur_data);

				if(cur_data.CompareNoCase(STR__ENABLE) == 0)
				{
					p_ecid_ctrl->Set__S6Fy_Reply(1);
				}
				else if(cur_data.CompareNoCase(STR__DISABLE) == 0)
				{
					p_ecid_ctrl->Set__S6Fy_Reply(0);					
				}
			}

			// S10Fy Reply ...
			{
				xCH_CFG__S10Fy_REPLY_CTRL->Get__DATA(cur_data);

				if(cur_data.CompareNoCase(STR__ENABLE) == 0)
				{
					p_ecid_ctrl->Set__S10Fy_Reply(1);
				}
				else if(cur_data.CompareNoCase(STR__DISABLE) == 0)
				{
					p_ecid_ctrl->Set__S10Fy_Reply(0);					
				}
			}
		}

		if(iFLAG__INITIAL_CONTROL_STATE > 0)
		{
			if(xCH__INITIAL_CONTROL_STATE->Check__DATA(STR__LOCAL) > 0)
			{
				p_ecid_ctrl->Set__INITIAL_CONTROL_STATE__DISABLE();
			}
			else if(xCH__INITIAL_CONTROL_STATE->Check__DATA(STR__REMOTE) > 0)
			{
				p_ecid_ctrl->Set__INITIAL_CONTROL_STATE__ENABLE();				
			}
		}

		// ...
		{
			xCH__FA_COMMUNICATION_FLAG->Get__DATA(cur_fa_flag);

			if(cur_fa_flag.CompareNoCase(pre_fa_flag) != 0)
			{
				pre_fa_flag = cur_fa_flag;

				if(cur_fa_flag.CompareNoCase(STR__ENABLE) == 0)
				{
					mFA_Link.Event__COMMUNICATION_STATE__DISABLE_TO_ENABLE();
				}
				else if(cur_fa_flag.CompareNoCase(STR__DISABLE) == 0)		
				{
					mFA_Link.Event__COMMUNICATION_STATE__ENABLE_TO_DISABLE();
				}
			}
		}

		// ...
		{
			main_name = "E30.SYSTEM";

			// PMC.SIZE
			if(p_var_ctrl == NULL)
			{
				p_var_ctrl = mFA_Link.Get__FA_VAR_CTRL();
			}

			if(p_var_ctrl != NULL)
			{
				xCH_CFG__PMC_SIZE->Get__DATA(var_data);
				sub_name = "PMC.SIZE";

				p_var_ctrl->Set_Variable(main_name,sub_name,var_data);
			}
		}

		if(mFA_Link.Is__REMOTE() > 0)
		{
			xSCH_MATERIAL_CTRL->Set__FA_STATUS__REMOTE();
		}
		else if(mFA_Link.Is__LOCAL() > 0)
		{
			xSCH_MATERIAL_CTRL->Set__FA_STATUS__LOCAL();
		}
		else if(mFA_Link.Is__OFFLINE() > 0)
		{
			xSCH_MATERIAL_CTRL->Set__FA_STATUS__OFFLINE();
		}
		else 
		{
			xSCH_MATERIAL_CTRL->Set__FA_STATUS__NOT_ESTABLISHED();
		}

		if(xCH__ALL_ALARM_REPORT_FLAG->Check__DATA("ENABLE") > 0)
		{
			mFA_Link.Set__REPORT_ALL_ALARM();
		}
		else
		{
			mFA_Link.Clear__REPORT_ALL_ALARM();
		}

		if(xCH__LOG_CTRL__FLAG->Check__DATA(STR__ENABLE) > 0)
		{
			if(xCH__LOG_CTRL__CTRL_MSG_FLAG->Check__DATA(STR__ENABLE) > 0)
			{
				mFA_Link.LOG_CTRL__Enable_Ctrl_Msg();
			}
			else
			{
				mFA_Link.LOG_CTRL__Disable_Ctrl_Msg();
			}

			if(xCH__LOG_CTRL__SECSI_FLAG->Check__DATA(STR__ENABLE) > 0)
			{
				mFA_Link.LOG_CTRL__Enable_SECSI();
			}
			else
			{
				mFA_Link.LOG_CTRL__Disable_SECSI();
			}

			if(xCH__LOG_CTRL__SECSII_FLAG->Check__DATA(STR__ENABLE) > 0)
			{
				mFA_Link.LOG_CTRL__Enable_SECSII();
			}
			else
			{
				mFA_Link.LOG_CTRL__Disable_SECSII();
			}

			if(xCH__LOG_CTRL__S6F1_LOG_FLAG->Check__DATA(STR__ENABLE) > 0)
			{
				mFA_Link.LOG_CTRL__Enable_S6F1_LOG();
			}
			else
			{
				mFA_Link.LOG_CTRL__Disable_S6F1_LOG();
			}

			// ...
			{
				xCH__LOG_CTRL__INTERVAL_MIN_TIME->Get__DATA(cur_time);

				if(cur_time.CompareNoCase(pre_time) != 0)
				{
					pre_time = cur_time;

					mFA_Link.LOG_CTRL__Set_Interval_Time(atoi(cur_time));
				}
			}

			// ...
			{
				xCH__LOG_CTRL__DATE_SIZE->Get__DATA(var_str);
				var_i = atoi(var_str);

				mFA_Link.LOG_CTRL__Set_Date_Size(var_i);
			}

			mFA_Link.LOG_CTRL__Enable();
		}
		else
		{
			mFA_Link.LOG_CTRL__Disable();
		}

		if(xCH__ENG_CALL__EQP_CALL->Check__DATA("YES") > 0)
		{
			xCH__ENG_CALL__WIN_NAME->Set__DATA("");

			// ...
			{
				CString call_msg;
				xCH__ENG_CALL__TEXT_MSG->Get__DATA(call_msg);

				mFA_Link.ENG_CALL__Report_Equipment(call_msg);
			}

			xCH__ENG_CALL__EQP_CALL->Set__DATA("");
		}
		if(xCH__ENG_CALL__PRC_CALL->Check__DATA("YES") > 0)
		{
			xCH__ENG_CALL__WIN_NAME->Set__DATA("");

			// ...
			{
				CString call_msg;
				xCH__ENG_CALL__TEXT_MSG->Get__DATA(call_msg);

				mFA_Link.ENG_CALL__Report_Process(call_msg);
			}

			xCH__ENG_CALL__PRC_CALL->Set__DATA("");
		}
	}

	// ...
}

void CObj_FA__APP_CTRL::
Fnc__TERMINAL_LOG_CTRL(CII_OBJECT__VARIABLE* p_variable, 
					   CString& pre_msg,
					   int& log_count)
{
	CI_FA_VARIABLE_CTRL* p_var_ctrl = mFA_Link.Get__FA_VAR_CTRL();

	if(dCH_CFG__S10Fy_TID_CHECK_FLAG->Check__DATA("YES") > 0)
	{
		p_var_ctrl->Set_Variable("S10Fy.TID","CHECK.FLAG","YES");
	}
	else
	{
		p_var_ctrl->Set_Variable("S10Fy.TID","CHECK.FLAG","NO");
	}

	if(xCH__TERMINAL_WIN_NAME->Check__DATA(STR__OK) > 0)
	{
		xCH__TERMINAL_WIN_NAME->Set__DATA("");

		mFA_Link.Event__MESSAGE_CONFIRM();
	}

	// ...
	CString log_title;
	CString log_msg;
	CString bff_msg;
	int i;

	for(i=0; i<CFG__TERMINAL_MSG_SIZE; i++)
	{
		if(i == 0)
		{
			xCH__TERMINAL_MSG[i]->Get__DATA(log_title);
		}

		xCH__TERMINAL_MSG[i]->Get__DATA(bff_msg);
		bff_msg += "\n";
		log_msg += bff_msg;
	}

	// ...
	{
		if(log_msg == pre_msg)		return;
		pre_msg = log_msg;

		log_count++;
		if(log_count < 1)			return;
	}

	// ...
	{
		CString str_title;
		CString str_time;
		SYSTEMTIME st;

		GetLocalTime(&st);	
		str_time.Format("%002d:%002d:%002d:%0003d",
						st.wHour,
						st.wMinute,
						st.wSecond,
						st.wMilliseconds);

		str_title.Format("[%s] %s",str_time,log_title);

		for(i=CFG__TERMINAL_LOG_SIZE-1; i>0; i--)
		{
			xCH__TERMINAL_LOG_TITLE[i-1]->Get__DATA(bff_msg);
			xCH__TERMINAL_LOG_TITLE[i]->Set__DATA(bff_msg);

			xCH__TERMINAL_LOG_MSG[i-1]->Get__DATA(bff_msg);
			xCH__TERMINAL_LOG_MSG[i]->Set__DATA(bff_msg);
		}

		xCH__TERMINAL_LOG_TITLE[0]->Set__DATA(str_title);
		xCH__TERMINAL_LOG_MSG[0]->Set__DATA(log_msg);

		bff_msg.Format("%1d",log_count);
		xCH__TERMINAL_LOG_COUNT->Set__DATA(bff_msg);
	}
}

void CObj_FA__APP_CTRL::
Fnc__HEARTBEAT_CTRL(CII_OBJECT__VARIABLE* p_variable, int& sec_count)
{
	CString var_data;

	xCH__FA_HEARTBEAT_INTERVAL_SEC->Get__DATA(var_data);
	int ref_sec = atoi(var_data) * 2;

	if(ref_sec < 1)
	{
		sec_count = 0;
		return;
	}

	sec_count++;

	if(ref_sec <= sec_count)
	{
		sec_count = 0;

		if(mFA_Link.Is__CONNECTED()	> 0)
		{
			mFA_Link.Send__S1F1();
		}
	}
}

