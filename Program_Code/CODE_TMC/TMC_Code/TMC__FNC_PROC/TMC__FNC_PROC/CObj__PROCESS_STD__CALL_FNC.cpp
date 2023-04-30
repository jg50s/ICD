#include "StdAfx.h"
#include "CObj__PROCESS_STD.h"
#include "CObj__PROCESS_STD__DEF.h"
#include "CObj__PROCESS_STD__ALID.h"

extern int Macro__Get_DateTime(CString &date,CString &time);


//-----------------------------------------------------------------------------------
int CObj__PROCESS_STD::Call__INIT(CII_OBJECT__VARIABLE* p_variable,
							   CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int CObj__PROCESS_STD::Call__PROC_READY(CII_OBJECT__VARIABLE *p_variable,
										CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__PROC_READY(p_variable,p_alarm);
}
int CObj__PROCESS_STD::Fnc__PROC_READY(CII_OBJECT__VARIABLE *p_variable,
									   CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// Para Init .....
	{
		xTIMER_ASYNC->START__COUNT_DOWN(0);

		//
		xCH__PRC_TOTAL_TIME_TO_CTC->Set__DATA("");
		xCH__PRC_CHANGE_TIME_TO_CTC->Set__DATA("");

		xCH__PRC_TOTAL_TIME->Set__DATA("");
		xCH__PRC_CUR_TIME->Set__DATA("");
		xCH__STEP_TOTAL_NUM->Set__DATA("");
		xCH__STEP_CUR_NUM->Set__DATA("-1");			

		xCH__PRC_STS->Set__DATA("IDLE");
	}

	// LLx_CHM : Pumping ...
	{
		CString log_msg = "PUMP Started ...";
		xLOG_CTRL->WRITE__LOG(log_msg);

		if(pOBJ_CTRL__CHM->Call__OBJECT(_CMMD_LLx__PUMP) < 0)
		{
			return -11;
		}
	}

	// Step Ready Check .....
	if(dCH__CFG_RECIPE_CTRL_MODE->Check__DATA(STR__CONFIG) < 0)
	{
		int flag = pOBJ_CTRL__STEP->Call__OBJECT(_CMMD_STEP__READY);

		if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
		{
			return -12;
		}
	}
	return 1;
}

int  CObj__PROCESS_STD
::Call__PROC_START(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm)
{
	return _Fnc__PROC_START(p_variable,p_alarm);
}
int  CObj__PROCESS_STD
::_Fnc__PROC_START(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm)
{
	int restart_count = 0;

LOOP_RESTART:

	// ...
	if(restart_count > 0)
	{
		CString str_lotid;
		CString str_lp_slotid;
		
		sEXT_CH__SLOT01_LOTID->Get__DATA(str_lotid);
		sEXT_CH__SLOT01_SLOTID->Get__DATA(str_lp_slotid);
		
		if(str_lotid.GetLength() > 0)
		{
			// ...
			CString sub_dir;
			CString file;
			CString date;
			CString time;
			
			Macro__Get_DateTime(date,time);
			
			// ...
			{
				sub_dir  = date;
				sub_dir += "\\";
				sub_dir += str_lotid;
				sub_dir += "\\";
				
				xEXT_CH__LOG_SUB_DIR->Set__DATA(sub_dir);
			}
			
			// ...
			{
				file.Format("RESTART%1d-", restart_count);
				file += str_lotid;
				file += "_";	
				file += str_lp_slotid;
				file += "-";
				file += time;
				
				xEXT_CH__LOG_FILE_NAME->Set__DATA(file);
			}
		}
	}

	// ...
	{
		sCH__ACT_RECOVERY_RESTART_FLAG->Set__DATA("");
	}

	// ...
	int flag = _Main__PROC_START(p_variable,p_alarm);

	if(sCH__ACT_RECOVERY_RESTART_FLAG->Check__DATA(STR__YES) > 0)
	{		
		/*
		if(pOBJ__STEP_CTRL->Call__OBJECT(_CMMD_STEP__PROC_SYSTEN_INIT) < 0)
		{
			sCH__ACT_RECOVERY_RESTART_FLAG->Set__DATA("");
			return -1;
		}
		*/
	
		// ...
		CString log_msg;

		xLOG_CTRL->WRITE__LOG("Recovery Restart - PROC_READY() Starting !!!");

		if(Fnc__PROC_READY(p_variable,p_alarm) < 0)
		{
			xLOG_CTRL->WRITE__LOG("Recovery Restart - PROC_READY() Aborted !!!");

			sCH__ACT_RECOVERY_RESTART_FLAG->Set__DATA("");
			return -1;
		}

		xLOG_CTRL->WRITE__LOG("Recovery Restart - PROC_READY() Completed !!!");

		restart_count++;
		goto LOOP_RESTART;
	}

	// LLx_CHM : Pumping ...
	{
		// ...
		{
			CString log_msg = "PUMP Started : _Fnc__PROC_START() ...";

			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();
		
		pOBJ_CTRL__CHM->Call__OBJECT(_CMMD_LLx__PUMP);
		
		pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
	}
	return flag;
}
int  CObj__PROCESS_STD
::_Main__PROC_START(CII_OBJECT__VARIABLE* p_variable,
				    CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CString str_prc_dir;
	CString rcp_path;
	CString rcp_name;

LOOP_START:

	if(dCH__CFG_RECIPE_CTRL_MODE->Check__DATA(STR__CONFIG) < 0)
	{
		CString log_msg;

		sEXT_CH__RCP_NAME->Get__DATA(rcp_name);
		xSEQ_INFO->Get__DIR_PROCESS(str_prc_dir);
		
		rcp_path.Format("%s%s.rcp", str_prc_dir,rcp_name);
		sEXT_CH__RCP_FILE_PATH->Set__DATA(rcp_path);

		log_msg.Format("RCP Name: %s\n", rcp_name);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		rcp_name = "Config Recipe";
		sEXT_CH__RCP_NAME->Set__DATA(rcp_name);
	}

	// Recipe Check ...
	if(dCH__CFG_RECIPE_CTRL_MODE->Check__DATA(STR__CONFIG) < 0)
	{
		int check_count = 0;
		
		while(sCH__RCP_FILE_UPLOAD_FLAG->Check__DATA(STR__YES) > 0)
		{
			Sleep(100);

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -1;
			}

			check_count++;
			if(check_count > 10)
			{
				int alarm_id = ALID__PROCESS_RECIPE_FILE_CHANGING_NOW;
				CString r_act;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}
		}

		sCH__RCP_FILE_UPLOAD_FLAG->Set__DATA(STR__YES);

		// ...
		{
			xRCP_FILE->Clear__APC_INFO();

			if(sCH__PMC_RECV_APC_APPLY->Check__DATA(STR__YES) > 0)
			{
				CString rcp_info;
				sCH__PMC_RECV_APC_DATA->Get__DATA(rcp_info);

				xRCP_FILE->Link__APC_INFO(rcp_info);
			}
		}

		// ...
		{
			xRCP_FILE->Free__MEM();

			if(xRCP_FILE->Upload__FILE(rcp_path) < 0)
			{
				// ...
				{
					sCH__RCP_FILE_UPLOAD_FLAG->Set__DATA("");
				}

				// ...
				{
					int alarm_id = ALID__PROCESS_RECIPE_NOT_EXIST;
					CString log_msg;
					CString r_act;

					log_msg.Format("The \"%s\" recipe file does not exist.\n", rcp_path);
					xLOG_CTRL->WRITE__LOG(log_msg);

					p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,log_msg,r_act);

					log_msg.Format("Alarm Recovery : [%s]",r_act);
					xLOG_CTRL->WRITE__LOG(log_msg);

					if(r_act.CompareNoCase(STR__RETRY) == 0)
					{
						goto LOOP_START;
					}
				}
				return -1;
			}

			// ...
			{
				int ref_item_num;
				int err_step;
				int err_item_num;
				CUIntArray l_step_item;

				if(xRCP_FILE->Check__STEP_ITEM_CHECK(ref_item_num, err_step,err_item_num,l_step_item) < 0)
				{
					// ...
					{
						sCH__RCP_FILE_UPLOAD_FLAG->Set__DATA("");
					}

					// ...
					int alarm_id = ALID__RECIPE_STEP_SIZE_ERROR;
					CString log_msg;
					CString log_bff;
					CString r_act;
					
					// ...
					{
						log_bff.Format("Reference item number is %1d. \n", ref_item_num);
						log_msg += log_bff;

						log_bff.Format("Error step ID : %1d. \n", err_step);
						log_msg += log_bff;

						log_bff.Format("Error item number : %1d \n", err_item_num);
						log_msg += log_bff;

						// ...
						int i_limit = l_step_item.GetSize();
						int i;

						for(i=0; i<i_limit; i++)
						{
							log_bff.Format("Step%1d [%1d], ", i+1,l_step_item[i]);
							log_msg += log_bff;

							if((i % 10) == 9)
							{
								log_msg += "\n";
							}
						}
					}
										
					p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,log_msg,r_act);
					
					if(r_act.CompareNoCase(STR__RETRY) == 0)
					{
						goto LOOP_START;
					}
					return -11;
				}
			}
		}
	
		sCH__RCP_FILE_UPLOAD_FLAG->Set__DATA("");
	}
	
	// ...
	{
		sCH__PROCESS_STATUS_FLAG->Set__DATA("PROCESS.START");

		sEXT_CH__SYSTEM_PROCESS_FLAG->Set__DATA(STR__YES);
		sEXT_CH__SYSTEM_PROCESS_STEP_ID->Set__DATA("");
	}

	// ...
	int flag;

	if(dCH__CFG_RECIPE_CTRL_MODE->Check__DATA(STR__CONFIG) < 0)
	{
		flag = _Sub__PROC_STEP_START(p_variable,p_alarm);
	}
	else
	{
		flag = _Sub__PROC_CFG_START(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		sCH__PROCESS_STATUS_FLAG->Set__DATA("PROCESS.ABORT");

		// ...
		{
			CString log_msg;

			log_msg.Format("_Main__PROC_START() : Flag [%1d], Ctrl_Abort [%1d]", 
						   flag, 
						   p_variable->Check__CTRL_ABORT());
			
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		pOBJ_CTRL__STEP->Call__OBJECT(_CMMD_STEP__ABORT);
	}
	else
	{
		sCH__PROCESS_STATUS_FLAG->Set__DATA("PROCESS.END");

		flag = pOBJ_CTRL__STEP->Call__OBJECT(_CMMD_STEP__END);

		sCH__PROCESS_STATUS_FLAG->Set__DATA("PROCESS.COMP");
	}

	xRCP_FILE->Clear__APC_INFO();
	return flag;
}
int  CObj__PROCESS_STD
::_Sub__PROC_STEP_START(CII_OBJECT__VARIABLE* p_variable,
					    CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	int step_total_count = 0;

	CString var_data;
	int flag;
	CString rcp_name;

	// Total Step Time Check ...
	{
		double total_time = 0.0;
		int step_count = 0;
			
		do
		{
			flag = xRCP_FILE->Read__MEM();

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

		var_data.Format("%.0f",total_time);
		xCH__PRC_TOTAL_TIME_TO_CTC->Set__DATA(var_data);
		xCH__PRC_TOTAL_TIME->Set__DATA(var_data);

		step_total_count = step_count;
		var_data.Format("%1d",step_count);
		xCH__STEP_TOTAL_NUM->Set__DATA(var_data);

		xRCP_FILE->Jump__STEP_NO(1);
	}

	flag = pOBJ_CTRL__STEP->Call__OBJECT(_CMMD_STEP__START);

	// Step Control .....
	if(flag > 0)
	{	
		CString log_msg;
		CString log_bff;
		CString var_data;

		// ...
		{
			SCX__ASYNC_TIMER_CTRL x_async_timer;
			int step_time  = 0;
			int step_count = 0;
			int init_step = -1;

			int loop_check =  1;
			int loop_flag  = -1;
			int loop_count =  0;
			int loop_step_end   = 0;
			int loop_step_start = 0;

			do
			{
				flag = xRCP_FILE->Read__MEM();

				if(flag > 0)
				{
					if(init_step < 0)
					{
						init_step = 1;

						xCH__PRC_STS->Set__DATA("PROCESSING");	
						Fnc__PRC_LOG__ENABLE(p_variable);

						xTIMER_ASYNC->START__COUNT_UP(9999);

						xCH__CHM_STATE->Set__DATA(STR__Processing);

						xCH__STEP_CUR_NUM->Set__DATA("1");
						sEXT_CH__SYSTEM_PROCESS_STEP_ID->Set__DATA("1");
					}
					else
					{
						xCH__STEP_CUR_NUM->Get__DATA(var_data);
					
						step_count = atoi(var_data) + 1;
						var_data.Format("%1d",step_count);

						xCH__STEP_CUR_NUM->Set__DATA(var_data);
						sEXT_CH__SYSTEM_PROCESS_STEP_ID->Set__DATA(var_data);
					}

					// ...
					{
						sEXT_CH__STEP_EXCEPTION_COMMAND->Set__DATA("");
						sCH__EXCEPTION_ACT->Set__DATA("");

						pOBJ_CTRL__LOG->Run__OBJECT(_CMMD_LOG__STEP_START);
					}

					aEXT_CH__STEP_TIME->Get__DATA(var_data);
					int step_time = atoi(var_data);

					int cur_step_no = xRCP_FILE->Get__CUR_STEP_NO();

					// ...
					int dcop_step_start = -1;

					if(dRCP_CH__PROCESS_DATA_SUMMARY->Check__DATA("Enable") > 0)
					{
						dcop_step_start = 1;
					}

					sEXT_CH__RCP_NAME->Get__DATA(rcp_name);

					// ...
					{
						log_msg.Format("Step Start :: Step Cur-NO./Total-NO. [Step_Count] : %d/%d [%1d] (dcop_step_start : %1d)", 
									   cur_step_no, 
									   step_total_count, 
									   step_count,
									   dcop_step_start);
					
						xLOG_CTRL->WRITE__LOG(log_msg);
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

						// ...
						{
							x_async_timer->START__COUNT_UP(9999);	
							sCH__EXCEPTION_LAST_ACT->Set__DATA("");

							flag = pOBJ_CTRL__STEP->Call__OBJECT(_CMMD_STEP__PROC);
						}
					}

					// ...
					int dcop_step_end = -1;
					
					if(dRCP_CH__PROCESS_DATA_SUMMARY->Check__DATA("Enable") > 0)
					{
						dcop_step_end = 1;
					}

					// Process Recovery Check ...
					if(flag < 0)
					{
						sCH__EXCEPTION_ACT->Set__DATA("");

						if(p_variable->Check__CTRL_ABORT() < 0)
						{
							Fnc__PRC_LOG__PAUSE(p_variable);
							xTIMER_ASYNC->PAUSE();

							// ...
							int alarm_id = ALID__PROCESS_RECOVERY_CHECK;
							CString r_act;

							// ...
							{
								sCH__PROCESS_STATUS_FLAG->Set__DATA("RECOVERY.WAIT");

								p_alarm->Post__ALARM_WITH_BLOCKING(alarm_id,r_act);

								sCH__PROCESS_STATUS_FLAG->Set__DATA("PROCESS.CONTINUE");
							}

							log_msg.Format("Alarm %s Button Pushed..", r_act);
							xLOG_CTRL->WRITE__LOG(log_msg);

							if(r_act.CompareNoCase(ACT__RESTART) == 0)
							{
								sCH__ACT_RECOVERY_RESTART_FLAG->Set__DATA(STR__YES);	

								flag = -1;
							}
							else if(r_act.CompareNoCase(ACT__ABORT) == 0)
							{
								flag = -1;
							}
							else if(r_act.CompareNoCase(ACT__JUMP) == 0)
							{
								flag = 2;
								sCH__EXCEPTION_ACT->Set__DATA(ACT__JUMP);
							}
							else if(r_act.CompareNoCase(ACT__END) == 0)
							{
								flag = 0;
							}

							if((flag > 0) && (flag != 2))
							{
								Fnc__PRC_LOG__RESUME(p_variable);
								xTIMER_ASYNC->RESUME();
							}
						}
					}
					else
					{
						CString var_data;						
						sCH__EXCEPTION_LAST_ACT->Get__DATA(var_data);

						if(var_data.GetLength() > 0)
						{
							sCH__EXCEPTION_ACT->Set__DATA(var_data);

							//.....
							{
								log_msg.Format("Exception Last Action : [%s] \n", var_data);
								xLOG_CTRL->WRITE__LOG(log_msg);
							}
						}
					}

					// Exception Command
					if(flag > 0)
					{
						if(sCH__EXCEPTION_ACT->Check__DATA(ACT__ABORT) > 0)
						{
							log_msg = "Exception Command : \"ABORT\" \n";
							xLOG_CTRL->WRITE__LOG(log_msg);

							flag = -1;
						}
						else if(sCH__EXCEPTION_ACT->Check__DATA(ACT__END) > 0)
						{
							log_msg = "Exception Command : \"END\" \n";
							xLOG_CTRL->WRITE__LOG(log_msg);

							flag = 0;
						}
						else if(sCH__EXCEPTION_ACT->Check__DATA(ACT__JUMP) > 0)
						{
							sEXT_CH__EXCEPTION_CONTINUE_REQ->Set__DATA("");
							aCH__CONTINUE_OVER_STEP_TIME->Set__DATA("0");

							log_msg = "Exception Command : \"JUMP\" \n";
							xLOG_CTRL->WRITE__LOG(log_msg);

							Fnc__PRC_LOG__PAUSE(p_variable);
							xTIMER_ASYNC->PAUSE();

							// ...
							int min_step = 0;
							int max_step;

							xCH__STEP_TOTAL_NUM->Get__DATA(var_data);
							max_step = atoi(var_data);

							if(max_step > 0)		min_step = 1;
							else					max_step = 0;

							aCH__JUMP_STEP_ID->Change__MIN_MAX_DEC(min_step,max_step,-1);
							xCH__STEP_CUR_NUM->Get__DATA(var_data);
							aCH__JUMP_STEP_ID->Set__DATA(var_data);

							sCH__WIN_CTRL_MSG->Set__DATA("Input Step Number or Time.");
							sCH__WIN_CTRL_LOCK->Set__DATA("");
							
							//
							CString win_name;
							win_name.Format("%s-%s", STR__WIN_NAME,sPara__LLx_NAME);

							sCH__WIN_CTRL_JUMP_PAGE->Set__DATA(win_name);
							
							while(1)
							{
								Sleep(100);

								sCH__WIN_CTRL_LOCK->Set__DATA("");

								if(sCH__WIN_CTRL_JUMP_PAGE->Check__DATA(win_name) < 0)
								{
									if(sCH__WIN_CTRL_JUMP_PAGE->Check__DATA("JUMP") > 0)
									{
										// ...
										{
											aCH__JUMP_STEP_ID->Get__DATA(var_data);
											int step_id = atoi(var_data);
											xRCP_FILE->Jump__STEP_NO(step_id);

											step_id--;
											var_data.Format("%1d",step_id);
											xCH__STEP_CUR_NUM->Set__DATA(var_data);
										}
									}
									else if(sCH__WIN_CTRL_JUMP_PAGE->Check__DATA("CONTINUE") > 0)
									{
										// ...
										sEXT_CH__EXCEPTION_CONTINUE_STEP_OVER_TIME->Get__DATA(var_data);
										int cur_step_sec = atoi(var_data);

										if(cur_step_sec > 0)
										{
											// ...
											{
												xCH__STEP_CUR_NUM->Get__DATA(var_data);
												int step_id = atoi(var_data);
												xRCP_FILE->Jump__STEP_NO(step_id);
										
												step_id--;
												if(step_id < 0)		step_id = 0;
												var_data.Format("%1d",step_id);
												xCH__STEP_CUR_NUM->Set__DATA(var_data);										
											}

											// ...
											{
												sEXT_CH__EXCEPTION_CONTINUE_REQ->Set__DATA(STR__YES);
											
												aCH__CONTINUE_OVER_STEP_TIME->Get__DATA(var_data);
												sEXT_CH__EXCEPTION_CONTINUE_STEP_OVER_TIME->Set__DATA(var_data);
											}
										}
										else
										{
											// ...
											{
												sEXT_CH__EXCEPTION_CONTINUE_REQ->Set__DATA("");
												sEXT_CH__EXCEPTION_CONTINUE_STEP_OVER_TIME->Set__DATA("0");
											}
										}
									}
									else if(sCH__WIN_CTRL_JUMP_PAGE->Check__DATA("ABORT") > 0)
									{
										flag = -1;
									}
									break;
								}
							}

							Fnc__PRC_LOG__RESUME(p_variable);
							xTIMER_ASYNC->RESUME();
						}

						sEXT_CH__STEP_EXCEPTION_COMMAND->Set__DATA("");
						sCH__EXCEPTION_ACT->Set__DATA("");

						sCH__WIN_CTRL_MSG->Set__DATA("");
						sCH__WIN_CTRL_LOCK->Set__DATA("");
						sCH__WIN_CTRL_JUMP_PAGE->Set__DATA("");
					}

					// Timer Count End ...
					double db_time = x_async_timer->Get__CURRENT_TIME();
					x_async_timer->STOP();					
			
					// Step Change time ...
					int i_change_time = (int) db_time - step_time;

					if(flag > 0)
					{					
						if(i_change_time != 0)
						{
							var_data.Format("%1d", i_change_time);
							xCH__PRC_CHANGE_TIME_TO_CTC->Set__DATA(var_data);
						}
					}

					// ...
					{
						log_msg.Format("Ret:%d, Step End :: (dcop_step_end : %1d) (Step Change Time : %1d) \n", 
									    flag, dcop_step_end,i_change_time);

						// PROC ...
						{
							CString rcp__proc_time;
							CString cur__proc_time;
						
							xCH__PRC_TOTAL_TIME->Get__DATA(rcp__proc_time);
							xCH__PRC_CUR_TIME->Get__DATA(cur__proc_time);
							
							log_bff.Format(" ->>  Proc Time : (%s / %s) \n", cur__proc_time,rcp__proc_time);
							log_msg += log_bff;
						}

						// STEP ...
						{
							CString rcp__step_time;
							CString cur__step_time;

							aEXT_CH__STEP_TIME->Get__DATA(rcp__step_time);
							xCH__PRC_CUR_TIME->Get__DATA(cur__step_time);

							log_bff.Format(" ->>  Step Time : (%.1f / %s) \n", db_time,rcp__step_time);
							log_msg += log_bff;
						}

						xLOG_CTRL->WRITE__LOG(log_msg);
					}

					if(flag > 0)
					{
						if(sCH__NEXT_STEP_CTRL_FLAG->Check__DATA(STR__YES) > 0)
						{
							// ...
							{
								log_msg = "NEXT_STEP_CTRL : Start ...";
								xLOG_CTRL->WRITE__LOG(log_msg);
							}

							// ...
							{
								sCH__NEXT_STEP_CTRL_REQ->Set__DATA(STR__READY);

								while(sCH__NEXT_STEP_CTRL_REQ->Check__DATA(STR__READY) > 0)
								{
									Sleep(50);
								
									if(sCH__EXCEPTION_ACT->Check__DATA(ACT__ABORT) > 0)
									{
										flag = -1;
										break;
									}
									if(p_variable->Check__CTRL_ABORT() > 0)
									{
										flag = -1;
										break;
									}
								}

								// ...
								int cur_step = xRCP_FILE->Get__CUR_STEP_NO();

								if(flag > 0)
								{
									CString rcp_path;
									sEXT_CH__RCP_FILE_PATH->Get__DATA(rcp_path);

									xRCP_FILE->Free__MEM();
									if(xRCP_FILE->Upload__FILE(rcp_path) < 0)
									{
										// ...
										{
											int alarm_id = ALID__PROCESS_RECIPE_NOT_EXIST;
											CString log_msg;
											CString r_act;
												
											log_msg.Format("The \"%s\" recipe file does not exist.\n", rcp_path);
											xLOG_CTRL->WRITE__LOG(log_msg);
												
											p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,log_msg,r_act);
												
											log_msg.Format("Alarm Recovery : [%s]",r_act);
											xLOG_CTRL->WRITE__LOG(log_msg);
										}

										flag = -1;
									}
									else
									{
										xRCP_FILE->Jump__STEP_NO(cur_step);
									}
								}

								if(flag > 0)
								{
									pOBJ_CTRL__STEP->Call__OBJECT(_CMMD_STEP__RCP_DATA_INIT);

									// ...
									CString str_req;
									sCH__NEXT_STEP_CTRL_REQ->Get__DATA(str_req);

									if(str_req.CompareNoCase(STR__NEXT_STEP) == 0)
									{
										xRCP_FILE->Jump__STEP_NO(cur_step+1);
									}	
									else if(str_req.CompareNoCase(STR__CUR_STEP) == 0)
									{
										cur_step--;
										var_data.Format("%1d",cur_step);
										xCH__STEP_CUR_NUM->Set__DATA(var_data);
									}
									else if(str_req.CompareNoCase(STR__PRE_STEP) == 0)
									{
										if(cur_step > 1)
										{
											cur_step--;
											xRCP_FILE->Jump__STEP_NO(cur_step);

											cur_step--;
											var_data.Format("%1d",cur_step);
											xCH__STEP_CUR_NUM->Set__DATA(var_data);
										}
										else
										{
											xRCP_FILE->Jump__STEP_NO(1);
											xCH__STEP_CUR_NUM->Set__DATA("");
										}
									}
								}
							
								sCH__NEXT_STEP_CTRL_REQ->Set__DATA(STR__LOCK);
							}

							log_msg = "NEXT_STEP_CTRL : End ...";
							xLOG_CTRL->WRITE__LOG(log_msg);
						}
					}

					if(flag > 0)
					{
						log_msg = "LOG_STEP END : Start ...";
						xLOG_CTRL->WRITE__LOG(log_msg);

						int log_flag = pOBJ_CTRL__LOG->Run__OBJECT(_CMMD_LOG__STEP_END);

						log_msg.Format("LOG_STEP END : End (%1d) ...", log_flag);
						xLOG_CTRL->WRITE__LOG(log_msg);
					}

					// Loop_Cycle ...
					if(flag > 0)
					{
						// ...
						{
							log_msg = "Loop_Cycle Info ... \n";

							log_bff.Format("  * %s <- %.0f \n",
								           aEXT_CH__RCP__LOOP_START->Get__CHANNEL_NAME(),
										   aEXT_CH__RCP__LOOP_START->Get__VALUE());
							log_msg += log_bff;

							log_bff.Format("  * %s <- %.0f \n",
								           aEXT_CH__RCP__LOOP_REPEAT->Get__CHANNEL_NAME(),
										   aEXT_CH__RCP__LOOP_REPEAT->Get__VALUE());
							log_msg += log_bff;

							xLOG_CTRL->WRITE__LOG(log_msg);
						}

						if((loop_flag < 0)&&(loop_check > 0))
						{
							aEXT_CH__RCP__LOOP_START->Get__DATA(var_data);	
							loop_step_start = atoi(var_data);

							aEXT_CH__RCP__LOOP_REPEAT->Get__DATA(var_data);
							loop_count = atoi(var_data);						

							if(loop_count > 0)
							{
								if((loop_step_start > 0)&&(loop_step_start < step_count))
								{
									loop_check = -1;
									loop_flag  =  1;

									loop_step_end = step_count;
								}
								else
								{
									// Alarm & Abort

								}
							}
						}

						if(loop_flag > 0)
						{
							if(step_count >= loop_step_end)
							{
								loop_count--;

								if(loop_count < 0)
								{
									loop_flag  = -1;
									loop_check =  1;

									xCH__LOOP_MSG->Set__DATA("");
								}
								else
								{
									step_count = loop_step_start - 1;

									var_data.Format("%1d", step_count);
									xCH__STEP_CUR_NUM->Set__DATA(var_data);

									xRCP_FILE->Jump__STEP_NO(loop_step_start);

									log_msg.Format("Step%1d -> Step%1d : %1d",
													loop_step_end,
													loop_step_start,
													loop_count+1);

									xCH__LOOP_MSG->Set__DATA(log_msg);
								}
							}
						}

						// ...
						{
							log_msg = "Loop_Cycle Info ... \n";

							log_bff.Format("  * loop_flag <- %1d \n", loop_flag);
							log_msg += log_bff;

							log_bff.Format("  * loop_check <- %1d \n", loop_check);
							log_msg += log_bff;

							log_bff.Format("  * step_count <- %1d \n", step_count);
							log_msg += log_bff;

							log_bff.Format("  * loop_step_start <- %1d \n", loop_step_start);
							log_msg += log_bff;

							log_bff.Format("  * loop_step_end <- %1d \n", loop_step_end);
							log_msg += log_bff;

							log_bff.Format("  * loop_count <- %1d \n", loop_count);
							log_msg += log_bff;

							xLOG_CTRL->WRITE__LOG(log_msg);
						}
					}

					// ...
				}
				else
				{
					log_msg.Format("_Sub__PROC_STEP_START() : Flag -> [0] !!! \n");
					xLOG_CTRL->WRITE__LOG(log_msg);

					flag = 0;
				}

				if(p_variable->Check__CTRL_ABORT() > 0)
				{
					log_msg.Format("_Sub__PROC_STEP_START() : Flag -> [-1] !!! \n");
					xLOG_CTRL->WRITE__LOG(log_msg);

					flag = -1;
				}
			}
			while(flag > 0);
		}
	}

	// ...
	{
		Fnc__PRC_LOG__DISABLE(p_variable);

		xTIMER_ASYNC->STOP();		

		xCH__PRC_STS->Set__DATA("IDLE");
		xCH__CHM_STATE->Set__DATA(STR__Idle);

		xCH__STEP_CUR_NUM->Set__DATA("-1");		
	}
	return flag;
}
int  CObj__PROCESS_STD
::_Sub__PROC_CFG_START(CII_OBJECT__VARIABLE* p_variable,
					   CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CString rcp_name = "Config Recipe !";

	// ...
	int step_total_count = 0;

	CString var_data;
	int flag;

	// Total Step Time Check ...
	{
		double total_time = aEXT_CH__CFG_PARA_STEP_TIME->Get__VALUE();
		int step_count = 1;

		var_data.Format("%.0f", total_time);
		xCH__PRC_TOTAL_TIME_TO_CTC->Set__DATA(var_data);
		xCH__PRC_TOTAL_TIME->Set__DATA(var_data);

		step_total_count = step_count;
		var_data.Format("%1d",step_count);
		xCH__STEP_TOTAL_NUM->Set__DATA(var_data);
	}

	flag = pOBJ_CTRL__STEP->Call__OBJECT(_CMMD_STEP__START);

	// Step Control .....
	if(flag > 0)
	{	
		CString log_msg;
		CString log_bff;
		CString var_data;

		//-------------------------------------------------------------------------
		SCX__ASYNC_TIMER_CTRL x_async_timer;

		int step_count = 0;
		int init_step = -1;

		int loop_check =  1;
		int loop_flag  = -1;
		int loop_count =  0;

		if(init_step < 0)
		{
			init_step = 1;

			xCH__PRC_STS->Set__DATA("PROCESSING");	
			Fnc__PRC_LOG__ENABLE(p_variable);

			xTIMER_ASYNC->START__COUNT_UP(9999);

			xCH__CHM_STATE->Set__DATA(STR__Processing);

			xCH__STEP_CUR_NUM->Set__DATA("1");
			sEXT_CH__SYSTEM_PROCESS_STEP_ID->Set__DATA("1");
		}

		// ...
		{
			sEXT_CH__STEP_EXCEPTION_COMMAND->Set__DATA("");
			sCH__EXCEPTION_ACT->Set__DATA("");

			pOBJ_CTRL__LOG->Run__OBJECT(_CMMD_LOG__STEP_START);
		}

		int step_time = (int) aEXT_CH__CFG_PARA_STEP_TIME->Get__VALUE();
		int cur_step_no = 1;

		// ...
		int dcop_step_start = -1;

		if(dRCP_CH__PROCESS_DATA_SUMMARY->Check__DATA("Enable") > 0)
		{
			dcop_step_start = 1;
		}

		// ...
		{
			log_msg.Format("Step Start :: Step Cur-NO./Total-NO. [Step_Count] : %d/%d [%1d] (dcop_step_start : %1d)", 
							cur_step_no, 
							step_total_count, 
							step_count,
							dcop_step_start);

			xLOG_CTRL->WRITE__LOG(log_msg);
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

			// ...
			{
				x_async_timer->START__COUNT_UP(9999);	
				sCH__EXCEPTION_LAST_ACT->Set__DATA("");

				flag = pOBJ_CTRL__STEP->Call__OBJECT(_CMMD_STEP__CFG_PROC);
			}
		}

		// ...
		int dcop_step_end = -1;

		if(dRCP_CH__PROCESS_DATA_SUMMARY->Check__DATA("Enable") > 0)
		{
			dcop_step_end = 1;
		}

		// Process Recovery Check ...
		if(flag < 0)
		{
			sCH__EXCEPTION_ACT->Set__DATA("");

			if(p_variable->Check__CTRL_ABORT() < 0)
			{
				Fnc__PRC_LOG__PAUSE(p_variable);
				xTIMER_ASYNC->PAUSE();

				// ...
				int alarm_id = ALID__PROCESS_RECOVERY_CHECK;
				CString r_act;

				// ...
				{
					sCH__PROCESS_STATUS_FLAG->Set__DATA("RECOVERY.WAIT");

					p_alarm->Post__ALARM_WITH_BLOCKING(alarm_id,r_act);

					sCH__PROCESS_STATUS_FLAG->Set__DATA("PROCESS.CONTINUE");
				}

				log_msg.Format("Alarm %s Button Pushed..", r_act);
				xLOG_CTRL->WRITE__LOG(log_msg);

				if(r_act.CompareNoCase(ACT__RESTART) == 0)
				{
					sCH__ACT_RECOVERY_RESTART_FLAG->Set__DATA(STR__YES);	

					flag = -1;
				}
				else if(r_act.CompareNoCase(ACT__ABORT) == 0)
				{
					flag = -1;
				}
				else if(r_act.CompareNoCase(ACT__JUMP) == 0)
				{
					flag = 2;
					sCH__EXCEPTION_ACT->Set__DATA(ACT__JUMP);
				}
				else if(r_act.CompareNoCase(ACT__END) == 0)
				{
					flag = 0;
				}

				if((flag > 0) && (flag != 2))
				{
					Fnc__PRC_LOG__RESUME(p_variable);
					xTIMER_ASYNC->RESUME();
				}
			}
		}
		else
		{
			CString var_data;						
			sCH__EXCEPTION_LAST_ACT->Get__DATA(var_data);

			if(var_data.GetLength() > 0)
			{
				sCH__EXCEPTION_ACT->Set__DATA(var_data);

				//.....
				{
					log_msg.Format("Exception Last Action : [%s] \n", var_data);
					xLOG_CTRL->WRITE__LOG(log_msg);
				}
			}
		}

		// Exception Command
		if(flag > 0)
		{
			if(sCH__EXCEPTION_ACT->Check__DATA(ACT__ABORT) > 0)
			{
				log_msg = "Exception Command : \"ABORT\" \n";
				xLOG_CTRL->WRITE__LOG(log_msg);

				flag = -1;
			}
			else if(sCH__EXCEPTION_ACT->Check__DATA(ACT__END) > 0)
			{
				log_msg = "Exception Command : \"END\" \n";
				xLOG_CTRL->WRITE__LOG(log_msg);

				flag = 0;
			}
			else if(sCH__EXCEPTION_ACT->Check__DATA(ACT__JUMP) > 0)
			{
				sEXT_CH__EXCEPTION_CONTINUE_REQ->Set__DATA("");
				aCH__CONTINUE_OVER_STEP_TIME->Set__DATA("0");

				log_msg = "Exception Command : \"JUMP\" \n";
				xLOG_CTRL->WRITE__LOG(log_msg);

				Fnc__PRC_LOG__PAUSE(p_variable);
				xTIMER_ASYNC->PAUSE();

				// ...
				int min_step = 0;
				int max_step;

				xCH__STEP_TOTAL_NUM->Get__DATA(var_data);
				max_step = atoi(var_data);

				if(max_step > 0)		min_step = 1;
				else					max_step = 0;

				aCH__JUMP_STEP_ID->Change__MIN_MAX_DEC(min_step,max_step,-1);
				xCH__STEP_CUR_NUM->Get__DATA(var_data);
				aCH__JUMP_STEP_ID->Set__DATA(var_data);

				sCH__WIN_CTRL_MSG->Set__DATA("Input Step Number or Time.");
				sCH__WIN_CTRL_LOCK->Set__DATA("");

				//
				CString win_name;
				win_name.Format("%s-%s", STR__WIN_NAME,sPara__LLx_NAME);

				sCH__WIN_CTRL_JUMP_PAGE->Set__DATA(win_name);

				while(1)
				{
					Sleep(100);

					sCH__WIN_CTRL_LOCK->Set__DATA("");

					if(sCH__WIN_CTRL_JUMP_PAGE->Check__DATA(win_name) < 0)
					{
						if(sCH__WIN_CTRL_JUMP_PAGE->Check__DATA("JUMP") > 0)
						{
							// ...
							{
								aCH__JUMP_STEP_ID->Get__DATA(var_data);
								int step_id = atoi(var_data);
								xRCP_FILE->Jump__STEP_NO(step_id);

								step_id--;
								var_data.Format("%1d",step_id);
								xCH__STEP_CUR_NUM->Set__DATA(var_data);
							}
						}
						else if(sCH__WIN_CTRL_JUMP_PAGE->Check__DATA("CONTINUE") > 0)
						{
							// ...
							sEXT_CH__EXCEPTION_CONTINUE_STEP_OVER_TIME->Get__DATA(var_data);
							int cur_step_sec = atoi(var_data);

							if(cur_step_sec > 0)
							{
								// ...
								{
									xCH__STEP_CUR_NUM->Get__DATA(var_data);
									int step_id = atoi(var_data);
									xRCP_FILE->Jump__STEP_NO(step_id);

									step_id--;
									if(step_id < 0)		step_id = 0;
									var_data.Format("%1d",step_id);
									xCH__STEP_CUR_NUM->Set__DATA(var_data);										
								}

								// ...
								{
									sEXT_CH__EXCEPTION_CONTINUE_REQ->Set__DATA(STR__YES);

									aCH__CONTINUE_OVER_STEP_TIME->Get__DATA(var_data);
									sEXT_CH__EXCEPTION_CONTINUE_STEP_OVER_TIME->Set__DATA(var_data);
								}
							}
							else
							{
								// ...
								{
									sEXT_CH__EXCEPTION_CONTINUE_REQ->Set__DATA("");
									sEXT_CH__EXCEPTION_CONTINUE_STEP_OVER_TIME->Set__DATA("0");
								}
							}
						}
						else if(sCH__WIN_CTRL_JUMP_PAGE->Check__DATA("ABORT") > 0)
						{
							flag = -1;
						}
						break;
					}
				}

				Fnc__PRC_LOG__RESUME(p_variable);
				xTIMER_ASYNC->RESUME();
			}

			sEXT_CH__STEP_EXCEPTION_COMMAND->Set__DATA("");
			sCH__EXCEPTION_ACT->Set__DATA("");

			sCH__WIN_CTRL_MSG->Set__DATA("");
			sCH__WIN_CTRL_LOCK->Set__DATA("");
			sCH__WIN_CTRL_JUMP_PAGE->Set__DATA("");
		}

		// Timer Count End ...
		double db_time = x_async_timer->Get__CURRENT_TIME();
		x_async_timer->STOP();					

		// Step Change time ...
		int i_change_time = (int) db_time - step_time;

		if(flag > 0)
		{					
			if(i_change_time != 0)
			{
				var_data.Format("%1d", i_change_time);
				xCH__PRC_CHANGE_TIME_TO_CTC->Set__DATA(var_data);
			}
		}

		// ...
		{
			log_msg.Format("Ret:%d, Step End :: (dcop_step_end : %1d) (Step Change Time : %1d) \n", 
				flag, dcop_step_end,i_change_time);

			// PROC ...
			{
				CString rcp__proc_time;
				CString cur__proc_time;

				xCH__PRC_TOTAL_TIME->Get__DATA(rcp__proc_time);
				xCH__PRC_CUR_TIME->Get__DATA(cur__proc_time);

				log_bff.Format(" ->>  Proc Time : (%s / %s) \n", cur__proc_time,rcp__proc_time);
				log_msg += log_bff;
			}

			// STEP ...
			{
				CString rcp__step_time;
				CString cur__step_time;

				aEXT_CH__STEP_TIME->Get__DATA(rcp__step_time);
				xCH__PRC_CUR_TIME->Get__DATA(cur__step_time);

				log_bff.Format(" ->>  Step Time : (%.1f / %s) \n", db_time,rcp__step_time);
				log_msg += log_bff;
			}

			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(flag > 0)
		{
			if(sCH__NEXT_STEP_CTRL_FLAG->Check__DATA(STR__YES) > 0)
			{
				// ...
				{
					log_msg = "NEXT_STEP_CTRL : Start ...";
					xLOG_CTRL->WRITE__LOG(log_msg);
				}

				// ...
				{
					sCH__NEXT_STEP_CTRL_REQ->Set__DATA(STR__READY);

					while(sCH__NEXT_STEP_CTRL_REQ->Check__DATA(STR__READY) > 0)
					{
						Sleep(50);

						if(sCH__EXCEPTION_ACT->Check__DATA(ACT__ABORT) > 0)
						{
							flag = -1;
							break;
						}
						if(p_variable->Check__CTRL_ABORT() > 0)
						{
							flag = -1;
							break;
						}
					}

					// ...
					int cur_step = xRCP_FILE->Get__CUR_STEP_NO();

					if(flag > 0)
					{
						CString rcp_path;
						sEXT_CH__RCP_FILE_PATH->Get__DATA(rcp_path);

						xRCP_FILE->Free__MEM();
						if(xRCP_FILE->Upload__FILE(rcp_path) < 0)
						{
							// ...
							{
								int alarm_id = ALID__PROCESS_RECIPE_NOT_EXIST;
								CString log_msg;
								CString r_act;

								log_msg.Format("The \"%s\" recipe file does not exist.\n", rcp_path);
								xLOG_CTRL->WRITE__LOG(log_msg);

								p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,log_msg,r_act);

								log_msg.Format("Alarm Recovery : [%s]",r_act);
								xLOG_CTRL->WRITE__LOG(log_msg);
							}

							flag = -1;
						}
						else
						{
							xRCP_FILE->Jump__STEP_NO(cur_step);
						}
					}

					if(flag > 0)
					{
						pOBJ_CTRL__STEP->Call__OBJECT(_CMMD_STEP__RCP_DATA_INIT);

						// ...
						CString str_req;
						sCH__NEXT_STEP_CTRL_REQ->Get__DATA(str_req);

						if(str_req.CompareNoCase(STR__NEXT_STEP) == 0)
						{
							xRCP_FILE->Jump__STEP_NO(cur_step+1);
						}	
						else if(str_req.CompareNoCase(STR__CUR_STEP) == 0)
						{
							cur_step--;
							var_data.Format("%1d",cur_step);
							xCH__STEP_CUR_NUM->Set__DATA(var_data);
						}
						else if(str_req.CompareNoCase(STR__PRE_STEP) == 0)
						{
							if(cur_step > 1)
							{
								cur_step--;
								xRCP_FILE->Jump__STEP_NO(cur_step);

								cur_step--;
								var_data.Format("%1d",cur_step);
								xCH__STEP_CUR_NUM->Set__DATA(var_data);
							}
							else
							{
								xRCP_FILE->Jump__STEP_NO(1);
								xCH__STEP_CUR_NUM->Set__DATA("");
							}
						}
					}

					sCH__NEXT_STEP_CTRL_REQ->Set__DATA(STR__LOCK);
				}

				log_msg = "NEXT_STEP_CTRL : End ...";
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}

		if(flag > 0)
		{
			log_msg = "LOG_STEP END : Start ...";
			xLOG_CTRL->WRITE__LOG(log_msg);

			int log_flag = pOBJ_CTRL__LOG->Run__OBJECT(_CMMD_LOG__STEP_END);

			log_msg.Format("LOG_STEP END : End (%1d) ...", log_flag);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			log_msg.Format("_Sub__PROC_STEP_START() : Flag -> [-1] !!! \n");
			xLOG_CTRL->WRITE__LOG(log_msg);

			flag = -1;
		}
		//-------------------------------------------------------------------------
	}

	// ...
	{
		Fnc__PRC_LOG__DISABLE(p_variable);

		xTIMER_ASYNC->STOP();		

		xCH__PRC_STS->Set__DATA("IDLE");
		xCH__CHM_STATE->Set__DATA(STR__Idle);

		xCH__STEP_CUR_NUM->Set__DATA("-1");		
	}
	return flag;
}

int CObj__PROCESS_STD
::Call__PRE_READY(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__PROC_READY(p_variable,p_alarm);
}
int CObj__PROCESS_STD
::Call__PRE_START(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	return _Fnc__PROC_START(p_variable,p_alarm);
}

int CObj__PROCESS_STD
::Call__CLN_READY(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__PROC_READY(p_variable,p_alarm);
}
int CObj__PROCESS_STD
::Call__CLN_START(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	return _Fnc__PROC_START(p_variable,p_alarm);
}

int CObj__PROCESS_STD
::Call__MNT_READY(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__PROC_READY(p_variable,p_alarm);
}
int CObj__PROCESS_STD
::Call__MNT_START(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	int log_clear_flag = -1;
	
	// ...
	{
		CString obj_sts;
		dEXT_CH__SYSTEM_OBJ_STATUS->Get__DATA(obj_sts);
		
		if((obj_sts.CompareNoCase(STR__STANDBY)  != 0)
		&& (obj_sts.CompareNoCase(STR__CTCINUSE) != 0))
		{
			CString str_lotid;
			CString str_lp_slotid;
			
			sEXT_CH__SLOT01_LOTID->Get__DATA(str_lotid);
			sEXT_CH__SLOT01_SLOTID->Get__DATA(str_lp_slotid);
			
			if(str_lotid.GetLength() > 0)
			{
				log_clear_flag = 1;
				
				// ...
				CString sub_dir;
				CString file;
				CString date;
				CString time;
				
				Macro__Get_DateTime(date,time);
				
				// ...
				{
					sub_dir  = date;
					sub_dir += "\\";
					sub_dir += str_lotid;
					sub_dir += "\\";
					
					xEXT_CH__LOG_SUB_DIR->Set__DATA(sub_dir);
				}
				
				// ...
				{
					file  = "RETRY-";
					file += str_lotid;
					file += "_";	
					file += str_lp_slotid;
					file += "-";
					file += time;
					
					xEXT_CH__LOG_FILE_NAME->Set__DATA(file);
				}
			}
			else
			{
				log_clear_flag = 1;

				// ...
				CString sub_dir;
				CString file;
				CString date;
				CString time;

				Macro__Get_DateTime(date,time);

				// ...
				{
					sub_dir  = date;
					sub_dir += "\\";
					sub_dir += "MNT";
					sub_dir += "\\";

					xEXT_CH__LOG_SUB_DIR->Set__DATA(sub_dir);
				}

				// ...
				{
					file  = "MANUAL-";
					file += str_lp_slotid;
					file += "-";
					file += time;

					xEXT_CH__LOG_FILE_NAME->Set__DATA(file);
				}
			}
		}
		
		/*
		// ...
		{
			CString var_data;
			CString log_msg;
			CString log_bff;
			
			log_bff.Format("log_clear_flag <- [%1d] \n", log_clear_flag);
			log_msg += log_bff;
			
			dEXT_CH__SYSTEM_OBJ_STATUS->Get__DATA(var_data);
			log_bff.Format("System Obj Status <- [%s] \n", var_data);
			log_msg += log_bff;
			
			xEXT_CH__LOG_SUB_DIR->Get__DATA(var_data);
			log_bff.Format("Log Sub_Dir <- [%s] \n", var_data);
			log_msg += log_bff;
			
			xEXT_CH__LOG_FILE_NAME->Get__DATA(var_data);
			log_bff.Format("Log File_Name <- [%s] \n", var_data);
			log_msg += log_bff;
			
			MessageBox(NULL,log_msg,"CHECK - Call__PROC_START()",MB_OK|MB_TOPMOST);
		}
		*/
	}

	// ...
	int flag = _Fnc__PROC_START(p_variable,p_alarm);

	if(log_clear_flag > 0)
	{
		xEXT_CH__LOG_SUB_DIR->Set__DATA("");
		xEXT_CH__LOG_FILE_NAME->Set__DATA("");
	}

	return flag;
}

int CObj__PROCESS_STD
::Call__JOB_START_READY(CII_OBJECT__VARIABLE *p_variable,
						CII_OBJECT__ALARM* p_alarm)
{
	return 1;
}
int CObj__PROCESS_STD
::Call__JOB_END_READY(CII_OBJECT__VARIABLE *p_variable,
					  CII_OBJECT__ALARM* p_alarm)
{
	return 1;
}

int CObj__PROCESS_STD
::Call__IDLE_START(CII_OBJECT__VARIABLE *p_variable,
				   CII_OBJECT__ALARM* p_alarm)
{
	return 1;
}


//-----------------------------------------------------------------------------
// Process Data Log
int  CObj__PROCESS_STD::Fnc__PRC_LOG__ENABLE(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CString pm_rcp;
	CString str_lotid;
	CString str_portid;
	CString str_slotid;

	sEXT_CH__RCP_NAME->Get__DATA(pm_rcp);
	sEXT_CH__SLOT01_LOTID->Get__DATA(str_lotid);
	sEXT_CH__SLOT01_PORTID->Get__DATA(str_portid);
	sEXT_CH__SLOT01_SLOTID->Get__DATA(str_slotid);

	xEXT_CH__LOG_RECIPEID->Set__DATA(pm_rcp);
	xEXT_CH__LOG_LOTID->Set__DATA(str_lotid);
	xEXT_CH__LOG_PORTID->Set__DATA(str_portid);
	xEXT_CH__LOG_SLOTID->Set__DATA(str_slotid);

	// ...
	CStringArray l_para;
	l_para.Add(pm_rcp);

	dCH__DATALOG_GATHERING_ENABLE_DISABLE->Set__DATA(STR__ENABLE);

	if(iLOG_ID > 0)
	{
		CString cmmd__log_enable;
		cmmd__log_enable.Format("ENABLE_D%1d", iLOG_ID);

		return pOBJ_CTRL__LOG->Run__OBJ_MODE(cmmd__log_enable, l_para);
	}
	return pOBJ_CTRL__LOG->Run__OBJ_MODE(_CMMD_LOG__ENABLE, l_para);
}
int  CObj__PROCESS_STD::Fnc__PRC_LOG__DISABLE(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	dCH__DATALOG_GATHERING_ENABLE_DISABLE->Set__DATA(STR__DISABLE);

	return pOBJ_CTRL__LOG->Run__OBJECT(_CMMD_LOG__DISABLE);
}

int  CObj__PROCESS_STD::Fnc__PRC_LOG__PAUSE(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return pOBJ_CTRL__LOG->Run__OBJECT(_CMMD_LOG__PAUSE);
}
int  CObj__PROCESS_STD::Fnc__PRC_LOG__RESUME(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return pOBJ_CTRL__LOG->Run__OBJECT(_CMMD_LOG__RESUME);
}
