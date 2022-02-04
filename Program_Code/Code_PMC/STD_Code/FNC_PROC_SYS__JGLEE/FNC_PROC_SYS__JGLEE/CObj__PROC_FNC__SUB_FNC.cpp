#include "StdAfx.h"
#include "CObj__PROC_FNC.h"
#include "CObj__PROC_FNC__DEF.h"
#include "CObj__PROC_FNC__ALID.h"


// ...
int  CObj__PROC_FNC::
Fnc__PLASMA_DECHUCK_START(CII_OBJECT__VARIABLE* p_variable,
						  CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CString str_prc_dir;
	CString rcp_path;
	CString rcp_name;

LOOP_START:

	// ...
	{
		// ...
		{
			sEXT_CH__CFG_DECHUCK_RECIPE_ABORT->Get__DATA(rcp_name);

			str_prc_dir = sDIR_PROC;
			sEXT_CH__RCP_NAME->Set__DATA(rcp_name);

			rcp_path.Format("%s%s.rcp", str_prc_dir, rcp_name);
		}

		// ...
		{
			CString log_msg;

			log_msg.Format("RCP Name: %s\n", rcp_name);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}

	// Recipe Check ...
	{
		xRCP_FILE_PLASMA_DECHUCK->Free__MEM();

		if(xRCP_FILE_PLASMA_DECHUCK->Upload__FILE(rcp_path) < 0)
		{
			int alarm_id = ALID__PLSAMA_DECHUCK_RECIPE_NOT_EXIST;
			CString log_msg;
			CString r_act;

			// ...
			{
				log_msg.Format("The \"%s\" plasma dechuck recipe " "\n" "does not exist.\n", 
					rcp_path);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,log_msg,r_act);

			// ...
			{
				log_msg.Format("Alarm Recovery : [%s]", r_act);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			if(r_act.CompareNoCase("RETRY") == 0)
			{
				goto LOOP_START;
			}
			return -1;
		}
	}

	if(Fnc__PROC_READY(p_variable,p_alarm) < 0)
	{
		return -1;
	}

	//.....
	int flag = Fnc__PROC_PLASMA_DECHUCK_START(p_variable,p_alarm);

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		// ...
		{
			CString log_msg;

			log_msg.Format("Fnc__PLASMA_DECHUCK_START() : Flag [%1d], Ctrl_Abort [%1d]", 
				flag, 
				p_variable->Check__CTRL_ABORT());

			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__STEP_ABORT);
	}
	else
	{
		flag = p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__STEP_END);
	}

	return flag;
}

int  CObj__PROC_FNC::
Fnc__PROC_PLASMA_DECHUCK_START(CII_OBJECT__VARIABLE* p_variable,
							   CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	//.....
	int step_total_count = 0;

	CString var_data;
	int flag;

	// Total Step Time Check .....
	{
		double total_time = 0.0;
		int step_count = 0;

		do
		{
			flag = xRCP_FILE_PLASMA_DECHUCK->Read__MEM();

			if(flag > 0)
			{
				step_count++;
				aEXT_CH__STEP_TIME->Get__DATA(var_data);

				total_time += atof(var_data);
			}
			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				flag = -1;
			}
		}
		while(flag > 0);

		//.....
		var_data.Format("%.0f",total_time);
		xCH__PRC_TOTAL_TIME->Set__DATA(var_data);

		step_total_count = step_count;
		var_data.Format("%1d",step_count);
		xCH__STEP_TOTAL_NUM->Set__DATA(var_data);

		xRCP_FILE_PLASMA_DECHUCK->Jump__STEP_NO(1);
	}

	// ...
	{
		sEXT_CH__STEP_EXCEPTION_COMMAND->Set__DATA("");
		sCH__EXCEPTION_ACT->Set__DATA("");

		sCH__EXCEPTION_LAST_ACT->Set__DATA("");
		sEXT_CH__STEP_STABLE_REQ->Set__DATA("");
	}

	// ...
	flag = p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__STEP_START);

	// Step Control ...
	if(flag > 0)
	{	
		// ...
		CString log_msg;
		CString log_bff;
		CString var_data;

		// ...
		{
			SCX__ASYNC_TIMER_CTRL x_async_timer;
			int step_time  = 0;
			int step_count = 0;
			int init_step = -1;

			do
			{
				flag = xRCP_FILE_PLASMA_DECHUCK->Read__MEM();

				if(flag > 0)
				{
					// ...
					if(init_step < 0)
					{
						init_step = 1;

						//
						xCH__PRC_STS->Set__DATA("PROCESSING");	
						xTIMER_ASYNC->START__COUNT_UP(9999);

						//
						xCH__CHM_STATE->Set__DATA(STR__Processing);

						xCH__STEP_CUR_NUM->Set__DATA("1");
						sEXT_CH__SYSTEM_PROCESS_STEP_ID->Set__DATA("1");
					}
					else
					{
						//
						xCH__STEP_CUR_NUM->Get__DATA(var_data);

						step_count = atoi(var_data) + 1;
						var_data.Format("%1d",step_count);

						xCH__STEP_CUR_NUM->Set__DATA(var_data);
						sEXT_CH__SYSTEM_PROCESS_STEP_ID->Set__DATA(var_data);
					}

					// ...
					{
						CString rcp_name;
						sCH__CFG_PLASMA_DECHUCK_RCP_NAME->Get__DATA(rcp_name);

						aEXT_CH__STEP_TIME->Get__DATA(var_data);
						int step_time = atoi(var_data);

						int cur_step_no = xRCP_FILE_PLASMA_DECHUCK->Get__CUR_STEP_NO();

						// ...
						{
							log_msg.Format("Step Start :: Step Cur-NO./Total-NO. [Step_Count] : %d/%d [%1d]", 
								cur_step_no, 
								step_total_count, 
								step_count);

							xLOG_CTRL->WRITE__LOG(log_msg);
						}
					}

					// Timer Count Start .....
					{	
						int total_step;
						int cur_step;

						xCH__STEP_TOTAL_NUM->Get__DATA(var_data);
						total_step = atoi(var_data);
						xCH__STEP_CUR_NUM->Get__DATA(var_data);
						cur_step = atoi(var_data);

						if(total_step <= cur_step)
						{
							sEXT_CH__SYSTEM_PROCESS_LAST_STEP_FLAG->Set__DATA("YES");
							xCH__LAST_STEP_FLAG->Set__DATA("YES");
						}

						x_async_timer->START__COUNT_UP(9999);	
					}


					// ...
					{
						sEXT_CH__STEP_EXCEPTION_COMMAND->Set__DATA("");
						sCH__EXCEPTION_ACT->Set__DATA("");

						sCH__EXCEPTION_LAST_ACT->Set__DATA("");
						sEXT_CH__STEP_STABLE_REQ->Set__DATA("");
					}

					// ...
					{
						flag = p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__STEP_PROC);
					}


					// Timer Count End ...
					double db_time = x_async_timer->Get__CURRENT_TIME();
					x_async_timer->STOP();					

					// Step Change time ...
					int i_change_time = (int) db_time - step_time;


					// ...
					{
						log_msg.Format("Ret:%d, Step End :: (Step Change Time : %1d) \n", 
							flag, 
							i_change_time);

						xLOG_CTRL->WRITE__LOG(log_msg);
					}
				}
				else
				{
					flag = 0;
				}

				if(p_variable->Check__CTRL_ABORT() > 0)
				{
					flag = -1;
				}
			}
			while(flag > 0);
		}
	}

	// ...
	{
		xTIMER_ASYNC->STOP();		

		xCH__PRC_STS->Set__DATA("IDLE");
		xCH__CHM_STATE->Set__DATA(STR__Idle);
	}
	return flag;
}
