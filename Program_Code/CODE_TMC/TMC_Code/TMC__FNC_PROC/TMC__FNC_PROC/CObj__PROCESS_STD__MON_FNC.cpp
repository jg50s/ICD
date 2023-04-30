#include "StdAfx.h"

#include "CObj__PROCESS_STD.h"
#include "CObj__PROCESS_STD__DEF.h"


void CObj__PROCESS_STD::
Mon__PROC_EXCEPTION_CTRL(CII_OBJECT__VARIABLE *p_variable,
						 CII_OBJECT__ALARM *p_alarm)
{
	CString pre_act_name;
	CString act_msg;
	CString act_name;
	CString var_data;
	

	while(1)
	{
		Sleep(100);


		if(iPROC_START_FLAG < 0)
		{
			sCH__EXCEPTION_ACT->Set__DATA("");
			sCH__EXCEPTION_MSG->Set__DATA("");

			//
			sCH__WIN_CTRL_JUMP_PAGE->Set__DATA("");

			//
			sCH__LOCK_FLAG__ABORT->Set__DATA(STR__YES);
			sCH__LOCK_FLAG__END->Set__DATA(STR__YES);
			sCH__LOCK_FLAG__SKIP->Set__DATA(STR__YES);
			sCH__LOCK_FLAG__JUMP->Set__DATA(STR__YES);

			//
			sCH__LOCK_FLAG__PAUSE->Set__DATA(STR__YES);
			sCH__LOCK_FLAG__RESUME->Set__DATA(STR__YES);
		}
		else
		{
			if(sCH__EXCEPTION_ACT->Check__DATA(ACT__ABORT) > 0)
			{
				//
				act_msg = "Process \"ABORT\" Command Requested ...";
				sCH__EXCEPTION_MSG->Set__DATA(act_msg);

				//
				sCH__LOCK_FLAG__ABORT->Set__DATA(STR__YES);
				sCH__LOCK_FLAG__END->Set__DATA(STR__YES);
				sCH__LOCK_FLAG__SKIP->Set__DATA(STR__YES);
				sCH__LOCK_FLAG__JUMP->Set__DATA(STR__YES);

				sCH__LOCK_FLAG__PAUSE->Set__DATA(STR__YES);
				sCH__LOCK_FLAG__RESUME->Set__DATA(STR__YES);
			}
			else if(sCH__EXCEPTION_ACT->Check__DATA(ACT__END) > 0)
			{
				//
				act_msg = "Process \"END\" Command Requested ...";
				sCH__EXCEPTION_MSG->Set__DATA(act_msg);

				//
				sCH__LOCK_FLAG__ABORT->Set__DATA("");

				sCH__LOCK_FLAG__END->Set__DATA(STR__YES);
				sCH__LOCK_FLAG__SKIP->Set__DATA(STR__YES);
				sCH__LOCK_FLAG__JUMP->Set__DATA(STR__YES);

				sCH__LOCK_FLAG__PAUSE->Set__DATA(STR__YES);
				sCH__LOCK_FLAG__RESUME->Set__DATA(STR__YES);
			}
			else if(sCH__EXCEPTION_ACT->Check__DATA("") < 0)
			{
				sCH__EXCEPTION_ACT->Get__DATA(act_name);
				act_msg.Format("Process \"%s\" Command Requested ...", act_name);

				sCH__EXCEPTION_MSG->Set__DATA(act_msg);

				//.....
				if(sCH__EXCEPTION_ACT->Check__DATA(ACT__PAUSE) > 0)
				{
					sCH__LOCK_FLAG__RESUME->Set__DATA("");
					sCH__LOCK_FLAG__PAUSE->Set__DATA(STR__YES);
				}
				else if(sCH__EXCEPTION_ACT->Check__DATA(ACT__RESUME) > 0)
				{
					sCH__LOCK_FLAG__RESUME->Set__DATA(STR__YES);
					sCH__LOCK_FLAG__PAUSE->Set__DATA("");
				}
			}
			else
			{
				sCH__LOCK_FLAG__ABORT->Set__DATA("");
				sCH__LOCK_FLAG__END->Set__DATA("");
				sCH__LOCK_FLAG__SKIP->Set__DATA("");
				sCH__LOCK_FLAG__JUMP->Set__DATA("");

				if(sEXT_CH__STEP_EXCEPTION_COMMAND->Check__DATA("") > 0)
				{
					sCH__EXCEPTION_MSG->Set__DATA("");

					sCH__LOCK_FLAG__PAUSE->Set__DATA("");
					sCH__LOCK_FLAG__RESUME->Set__DATA(STR__YES);
				}
			}
		}

		//.....
		sCH__EXCEPTION_ACT->Get__DATA(var_data);

		if(var_data.GetLength() > 0)
		{
			sCH__EXCEPTION_LAST_ACT->Set__DATA(var_data);
			sCH__EXCEPTION_ACT->Set__DATA("");

			if((var_data.CompareNoCase(ACT__ABORT) == 0)
			|| (var_data.CompareNoCase(ACT__END)   == 0)
			|| (var_data.CompareNoCase(ACT__SKIP)  == 0)
			|| (var_data.CompareNoCase(ACT__JUMP)  == 0))
			{
				sEXT_CH__STEP_EXCEPTION_COMMAND->Set__DATA(ACT_STEP__SKIP);
			}
			else if(var_data.CompareNoCase(ACT__PAUSE) == 0)
			{
				sEXT_CH__STEP_EXCEPTION_COMMAND->Set__DATA(ACT_STEP__PAUSE);
			}
			else if(var_data.CompareNoCase(ACT__RESUME) == 0)
			{
				sEXT_CH__STEP_EXCEPTION_COMMAND->Set__DATA(ACT_STEP__RESUME);
			}
			else
			{
				sEXT_CH__STEP_EXCEPTION_COMMAND->Set__DATA("");
			}

			if(pre_act_name != var_data)
			{
				if(var_data.CompareNoCase(ACT__JUMP) == 0)
				{
					sCH__WIN_CTRL_MSG->Set__DATA("Wait ...");
					sCH__WIN_CTRL_LOCK->Set__DATA(STR__YES);

					//
					CString win_name;
					win_name.Format("%s-%s", STR__WIN_NAME,sPara__LLx_NAME);

					sCH__WIN_CTRL_JUMP_PAGE->Set__DATA(win_name);
				}

				//
				CString log_msg;
				log_msg.Format("Exception Command Changed  :  [%s] -> [%s]", pre_act_name,var_data);

				xLOG_CTRL->WRITE__LOG(log_msg);

				pre_act_name = var_data;
			}
		}
		else
		{
			pre_act_name = "";
		}

		Fnc__SYSTEM_LOCK_CTRL(p_variable);
	}
}

void CObj__PROCESS_STD
::Fnc__SYSTEM_LOCK_CTRL(CII_OBJECT__VARIABLE *p_variable)
{
	CString cur__sys_status = dEXT_CH__SYSTEM_OBJ_STATUS->Get__STRING();

	if((cur__sys_status.CompareNoCase(STR__STANDBY)  == 0)
	|| (cur__sys_status.CompareNoCase(STR__CTCINUSE) == 0))
	{
		if(iPROC_START_FLAG < 0)
		{
			sEXT_CH__SYS_CTRL_LOCK->Set__DATA("ALL");
		}
		else
		{
			sEXT_CH__SYS_CTRL_LOCK->Set__DATA("AUTO.PROC");
		}
	}
	else
	{
		if(iPROC_START_FLAG < 0)
		{
			if((sEXT_CH__SYS_CTRL_LOCK->Check__DATA("ALL") > 0)
				|| (sEXT_CH__SYS_CTRL_LOCK->Check__DATA("AUTO.PROC") > 0))
			{
				sEXT_CH__SYS_CTRL_LOCK->Set__DATA("");
			}
		}
	}

	// ...
	CString var_data = sEXT_CH__SYS_CTRL_LOCK->Get__STRING();

	if((var_data.CompareNoCase("") != 0)
	&& (var_data.CompareNoCase("SUB.FNC") != 0))
	{	
		sEXT_CH__SYS_FNC_LOCK->Set__DATA("ALL");
	}
	else
	{
		sEXT_CH__SYS_FNC_LOCK->Get__DATA(var_data);

		if(var_data.CompareNoCase("ALL") == 0)
		{
			sEXT_CH__SYS_FNC_LOCK->Set__DATA("");	
		}
		else if(var_data.CompareNoCase("") != 0)
		{
			sEXT_CH__SYS_CTRL_LOCK->Set__DATA("SUB.FNC");					
		}
		else
		{
			if(sEXT_CH__SYS_CTRL_LOCK->Check__DATA("SUB.FNC") > 0)
			{
				sEXT_CH__SYS_CTRL_LOCK->Set__DATA("");
			}
		}
	}

	// ...
}
