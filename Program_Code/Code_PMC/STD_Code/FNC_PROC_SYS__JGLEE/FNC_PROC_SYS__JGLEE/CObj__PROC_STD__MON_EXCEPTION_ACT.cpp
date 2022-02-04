#include "StdAfx.h"
#include "CObj__PROC_STD.h"
#include "CObj__PROC_STD__DEF.h"


// ...
void CObj__PROC_STD
::Mon__EXCEPTION_ACT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString pre__act_cmd;

	CString act_msg;
	CString act_name;
	CString var_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(iActive__PROC_START < 0)
		{
			sCH__MON_EXCEPTION_MSG->Set__DATA("__");

			// sCH__WIN_CTRL_JUMP_PAGE->Set__DATA("");

			//
			dCH__MON_LOCK_ACTIVE_ABORT->Set__DATA(STR__ON);
			dCH__MON_LOCK_ACTIVE_END->Set__DATA(STR__ON);

			dCH__MON_LOCK_ACTIVE_SKIP->Set__DATA(STR__ON);
			dCH__MON_LOCK_ACTIVE_JUMP->Set__DATA(STR__ON);

			dCH__MON_LOCK_ACTIVE_PAUSE->Set__DATA(STR__ON);
			dCH__MON_LOCK_ACTIVE_RESUME->Set__DATA(STR__ON);
		}
		else if(dCH__CUR_PROCESS_TYPE->Check__DATA(STR__MANUAL) > 0)
		{
			if(dCH__MON_EXCEPTION_ACT->Check__DATA(_ACT_CMD__START) > 0)
			{
				dCH__MON_LOCK_ACTIVE_ABORT->Set__DATA(STR__OFF);
				dCH__MON_LOCK_ACTIVE_END->Set__DATA(STR__OFF);

				dCH__MON_LOCK_ACTIVE_SKIP->Set__DATA(STR__OFF);
				dCH__MON_LOCK_ACTIVE_JUMP->Set__DATA(STR__OFF);

				dCH__MON_LOCK_ACTIVE_PAUSE->Set__DATA(STR__OFF);
				dCH__MON_LOCK_ACTIVE_RESUME->Set__DATA(STR__ON);
			}
			else if(dCH__MON_EXCEPTION_ACT->Check__DATA(_ACT_CMD__ABORT) > 0)
			{
				act_msg = "\"ABORT\" Command Requested";
				sCH__MON_EXCEPTION_MSG->Set__DATA(act_msg);

				//
				dCH__MON_LOCK_ACTIVE_ABORT->Set__DATA(STR__ON);
				dCH__MON_LOCK_ACTIVE_END->Set__DATA(STR__ON);

				dCH__MON_LOCK_ACTIVE_SKIP->Set__DATA(STR__ON);
				dCH__MON_LOCK_ACTIVE_JUMP->Set__DATA(STR__ON);

				dCH__MON_LOCK_ACTIVE_PAUSE->Set__DATA(STR__ON);
				dCH__MON_LOCK_ACTIVE_RESUME->Set__DATA(STR__ON);
			}
			else if(dCH__MON_EXCEPTION_ACT->Check__DATA(_ACT_CMD__END) > 0)
			{
				act_msg = "\"END\" Command Requested";
				sCH__MON_EXCEPTION_MSG->Set__DATA(act_msg);

				//
				dCH__MON_LOCK_ACTIVE_ABORT->Set__DATA(STR__OFF);
				dCH__MON_LOCK_ACTIVE_END->Set__DATA(STR__OFF);

				dCH__MON_LOCK_ACTIVE_SKIP->Set__DATA(STR__ON);
				dCH__MON_LOCK_ACTIVE_JUMP->Set__DATA(STR__ON);

				dCH__MON_LOCK_ACTIVE_PAUSE->Set__DATA(STR__ON);
				dCH__MON_LOCK_ACTIVE_RESUME->Set__DATA(STR__ON);
			}
			else if(dCH__MON_EXCEPTION_ACT->Check__DATA(_ACT_CMD__ALARM) > 0)
			{
				dCH__MON_LOCK_ACTIVE_ABORT->Set__DATA(STR__ON);
				dCH__MON_LOCK_ACTIVE_END->Set__DATA(STR__ON);

				dCH__MON_LOCK_ACTIVE_SKIP->Set__DATA(STR__ON);
				dCH__MON_LOCK_ACTIVE_JUMP->Set__DATA(STR__ON);

				dCH__MON_LOCK_ACTIVE_PAUSE->Set__DATA(STR__ON);
				dCH__MON_LOCK_ACTIVE_RESUME->Set__DATA(STR__ON);
			}
			else 
			{
				act_name = dCH__MON_EXCEPTION_ACT->Get__STRING();

				act_msg.Format("\"%s\" Command Requested", act_name);
				sCH__MON_EXCEPTION_MSG->Set__DATA(act_msg);

				if(dCH__MON_EXCEPTION_ACT->Check__DATA(_ACT_CMD__PAUSE) > 0)
				{
					dCH__MON_LOCK_ACTIVE_RESUME->Set__DATA(STR__OFF);
					dCH__MON_LOCK_ACTIVE_PAUSE->Set__DATA(STR__ON);
				}
				else if(dCH__MON_EXCEPTION_ACT->Check__DATA(_ACT_CMD__RESUME) > 0)
				{
					dCH__MON_EXCEPTION_ACT->Set__DATA(_ACT_CMD__START);
				}
			}
		}

		// ...
		CString cur__act_cmd = dCH__MON_EXCEPTION_ACT->Get__STRING();

		if(cur__act_cmd.CompareNoCase(_ACT_CMD__IDLE) == 0)
		{
			pre__act_cmd = "";
		}
		else
		{
			dCH__MON_EXCEPTION_ACT->Set__DATA("");

			if((cur__act_cmd.CompareNoCase(_ACT_CMD__ABORT) == 0)
			|| (cur__act_cmd.CompareNoCase(_ACT_CMD__END)   == 0)
			|| (cur__act_cmd.CompareNoCase(_ACT_CMD__SKIP)  == 0)
			|| (cur__act_cmd.CompareNoCase(_ACT_CMD__JUMP)  == 0))
			{
				sEXT_CH__MON_STEP_EXCEPTION_ACT->Set__DATA(_ACT_CMD__SKIP);
			}
			else if(cur__act_cmd.CompareNoCase(_ACT_CMD__PAUSE) == 0)
			{
				sEXT_CH__MON_STEP_EXCEPTION_ACT->Set__DATA(_ACT_CMD__PAUSE);
			}
			else if(cur__act_cmd.CompareNoCase(_ACT_CMD__RESUME) == 0)
			{
				sEXT_CH__MON_STEP_EXCEPTION_ACT->Set__DATA(_ACT_CMD__RESUME);
			}
			else
			{
				sEXT_CH__MON_STEP_EXCEPTION_ACT->Set__DATA("");
			}

			if(pre__act_cmd != cur__act_cmd)
			{
				pre__act_cmd = cur__act_cmd;

				// ...
				{
					CString log_msg;
					log_msg.Format("Exception Command Changed  :  [%s]", cur__act_cmd);

					xI_LOG_CTRL->WRITE__LOG(log_msg);
				}

				if(cur__act_cmd.CompareNoCase(_ACT_CMD__JUMP) == 0)
				{
					sCH__WIN_CTRL_MSG->Set__DATA("Input Step Number.");
					
					dCH__WIN_CTRL_LOCK_ACTIVE_JUMP->Set__DATA(STR__OFF);
					dCH__WIN_CTRL_LOCK_ACTIVE_CONTINUE->Set__DATA(STR__ON);
					dCH__WIN_CTRL_LOCK_ACTIVE_ABORT->Set__DATA(STR__OFF);

					Check__STEP_JUMP(p_variable, p_alarm);

					dCH__WIN_CTRL_LOCK_ACTIVE_JUMP->Set__DATA(STR__ON);
					dCH__WIN_CTRL_LOCK_ACTIVE_CONTINUE->Set__DATA(STR__ON);
					dCH__WIN_CTRL_LOCK_ACTIVE_ABORT->Set__DATA(STR__ON);
				}
			}

			// ...
		}

		// ...
	}
}

int CObj__PROC_STD
::Check__STEP_JUMP(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString win_name = STR__WIN_NAME__JUMP_STEP;
	sCH__WIN_CTRL_JUMP_PAGE->Set__DATA(win_name);

	while(1)
	{
		Sleep(100);

		if(sCH__WIN_CTRL_JUMP_PAGE->Check__DATA(win_name) > 0)
		{
			continue;
		}

		// ...
		CString cur__win_ctrl = sCH__WIN_CTRL_JUMP_PAGE->Get__STRING();

		if(cur__win_ctrl.CompareNoCase("JUMP") == 0)
		{
			// ...
			{
				int step_id = (int) aCH__JUMP_STEP_ID->Get__VALUE();
				xRCP__FILE_CTRL->Jump__STEP_NO(step_id);

				step_id--;
				aCH__STEP_CUR_NUM->Set__VALUE(step_id);
			}

			dCH__MON_EXCEPTION_ACT->Set__DATA(_ACT_CMD__START);
			return 1;
		}
		
		if(cur__win_ctrl.CompareNoCase("CONTINUE") == 0)
		{
			CString var_data;

			// ...
			{
				aCH__CONTINUE_OVER_STEP_TIME->Get__DATA(var_data);
				int cur_step_sec = atoi(var_data);

				if(cur_step_sec > 0)
				{
					aCH__STEP_CUR_NUM->Get__DATA(var_data);
					int step_id = atoi(var_data);
					xRCP__FILE_CTRL->Jump__STEP_NO(step_id);

					step_id--;
					if(step_id < 0)		step_id = 0;
					var_data.Format("%1d",step_id);
					aCH__STEP_CUR_NUM->Set__DATA(var_data);										

					/*
					sEXT_CH__EXCEPTION_CONTINUE_REQ->Set__DATA(STR__YES);

					aCH__CONTINUE_OVER_STEP_TIME->Get__DATA(var_data);
					sEXT_CH__EXCEPTION_CONTINUE_STEP_OVER_TIME->Set__DATA(var_data);
					*/
				}
				else
				{
					/*
					sEXT_CH__EXCEPTION_CONTINUE_REQ->Set__DATA("");
					sEXT_CH__EXCEPTION_CONTINUE_STEP_OVER_TIME->Set__DATA("0");
					*/
				}
			}

			dCH__MON_EXCEPTION_ACT->Set__DATA(_ACT_CMD__START);
			return 1;
		}
		
		if(cur__win_ctrl.CompareNoCase("ABORT") == 0)
		{
			dCH__MON_EXCEPTION_ACT->Set__DATA(_ACT_CMD__ABORT);
			return -1;
		}
	}

	return 1;
}

