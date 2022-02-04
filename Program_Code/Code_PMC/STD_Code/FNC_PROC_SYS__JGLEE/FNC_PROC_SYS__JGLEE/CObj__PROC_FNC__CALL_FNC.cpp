#include "StdAfx.h"
#include "CObj__PROC_FNC.h"
#include "CObj__PROC_FNC__DEF.h"
#include "CObj__PROC_FNC__ALID.h"

#include "Macro_Function.h"


//-----------------------------------------------------------------------------------
int CObj__PROC_FNC
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int r_flag = 1;

	if(sEXT_CH__CHUCK_STATE->Check__DATA("DECHUCKED") < 0)
	{
		if(dEXT_CH__CFG_DECHUCK_CTRL_MODE->Check__DATA("RECIPE") > 0)
		{
			r_flag = Fnc__PLASMA_DECHUCK_START(p_variable,p_alarm);
		}
	}
	return r_flag;
}

int CObj__PROC_FNC
::Call__PROC_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{

	return Fnc__PROC_READY(p_variable,p_alarm);
}
int CObj__PROC_FNC
::Fnc__PROC_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// Para Init .....
	{
		xTIMER_ASYNC->START__COUNT_DOWN(0);

		//
		xCH__PRC_TOTAL_TIME_TO_CTC->Set__DATA("");
		sEXT_CH__PRC_TOTAL_TIME_TO_CTC->Set__DATA("");

		xCH__PRC_CHANGE_TIME_TO_CTC->Set__DATA("");
		sEXT_CH__PRC_CHANGE_TIME_TO_CTC->Set__DATA("");

		//
		xCH__PRC_TOTAL_TIME->Set__DATA("");
		xCH__PRC_CUR_TIME->Set__DATA("");
		xCH__STEP_TOTAL_NUM->Set__DATA("");
		xCH__STEP_CUR_NUM->Set__DATA("-1");

		xCH__PRC_STS->Set__DATA("IDLE");
	}

	// CHM : HIGH_VAC ...
	{
		// ...
		{
			CString log_msg = "HIGH_VAC Started ...";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		if(pOBJ_CTRL__CHM->Call__OBJECT("HIGH_VAC_PUMP") < 0)
		{
			return -11;
		}
	}

	// Step Ready Check .....
	{
		int flag = p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__STEP_READY);

		if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
		{
			return -12;
		}
	}
	return 1;
}

int  CObj__PROC_FNC
::Call__PROC_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return Fnc__PROC_START(p_variable,p_alarm);
}
int  CObj__PROC_FNC
::Fnc__PROC_START(CII_OBJECT__VARIABLE* p_variable,	CII_OBJECT__ALARM* p_alarm)
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
	int flag = _Fnc__PROC_START(p_variable,p_alarm);

	if(sCH__ACT_RECOVERY_RESTART_FLAG->Check__DATA(STR__YES) > 0)
	{		
		/*
		if(pOBJ__STEP_CTRL->Call__OBJECT(OBJ_MODE__PROC_SYSTEN_INIT) < 0)
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

	// ESC Dechuck ...
	if(flag >= 0)
	{
		if(sEXT_CH__CHUCK_STATE->Check__DATA("DECHUCKED") < 0)
		{
			if(dEXT_CH__CFG_DECHUCK_CTRL_MODE->Check__DATA("RECIPE") > 0)
			{
				Fnc__PLASMA_DECHUCK_START(p_variable,p_alarm);
			}
		}
	}

	// CHM : LOW_VAC ...
	{
		// ...
		{
			CString log_msg = "LOW_VAC Started : Fnc__PROC_START() ...";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();

		pOBJ_CTRL__CHM->Call__OBJECT("HIGH_VAC_PUMP");

		pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
	}
	return flag;
}
int  CObj__PROC_FNC
::_Fnc__PROC_START(CII_OBJECT__VARIABLE* p_variable,
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
		CString log_msg;

		//
		sEXT_CH__RCP_NAME->Get__DATA(rcp_name);
		str_prc_dir = sDIR_PROC;
		
		rcp_path.Format("%s%s.rcp", str_prc_dir, rcp_name);
		sEXT_CH__RCP_FILE_PATH->Set__DATA(rcp_path);

		log_msg.Format("RCP Name: %s\n", rcp_name);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}


	// Recipe Check ...
	{
		// ...
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
				// MessageBox(NULL,rcp_info,"Check : _Fnc__PROC_START() !",MB_OK|MB_TOPMOST);
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

		sEXT_CH__MON_SYSTEM_PROCESS_ACTIVE->Set__DATA(STR__ON);
		sEXT_CH__SYSTEM_PROCESS_STEP_ID->Set__DATA("");
	}

	// ...
	int flag = Fnc__PROC_STEP_START(p_variable,p_alarm);

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		sCH__PROCESS_STATUS_FLAG->Set__DATA("PROCESS.ABORT");

		// ...
		{
			CString log_msg;
			log_msg.Format("_Fnc__PROC_START() : Flag [%1d], Ctrl_Abort [%1d]", 
						   flag, p_variable->Check__CTRL_ABORT());
			
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__STEP_ABORT);
	}
	else
	{
		sCH__PROCESS_STATUS_FLAG->Set__DATA("PROCESS.END");

		// ...
		{
			flag = p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__STEP_END);
		}

		sCH__PROCESS_STATUS_FLAG->Set__DATA("PROCESS.COMP");
	}

	// End DCOP Process End
	{
		xRCP_FILE->Clear__APC_INFO();

		// xDCOP_CTRL->Report__PROCESS_END();
	}

	return flag;
}
int  CObj__PROC_FNC::Fnc__PROC_STEP_START(CII_OBJECT__VARIABLE* p_variable,
										     CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	int step_total_count = 0;

	CString var_data;
	int flag;
	CString rcp_name;

	// ...
	{
		sCH__REPORT_TOTAL_ERROR_SEC->Set__DATA("__");
		sCH__REPORT_AVG_ERROR_SEC->Set__DATA("__");
	}

	// Total Step Time Check .....
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
		sEXT_CH__PRC_TOTAL_TIME_TO_CTC->Set__DATA(var_data);
		xCH__PRC_TOTAL_TIME->Set__DATA(var_data);

		step_total_count = step_count;
		var_data.Format("%1d",step_count);
		xCH__STEP_TOTAL_NUM->Set__DATA(var_data);

		xRCP_FILE->Jump__STEP_NO(1);
	}

	flag = p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__STEP_START);

	// Step Control .....
	if(flag > 0)
	{	
		bool active__log_end_start = false;
		double _rcp__total_sec = atof(xCH__PRC_TOTAL_TIME->Get__STRING());

		// ...
		CString log_msg;
		CString log_bff;
		CString var_data;

		// ...
		{
			SCX__STEP_TIMER_CTRL  x_toal_step_timer;
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
				log_msg = "Step Loop : Start (1) ...";
				xLOG_CTRL->WRITE__LOG(log_msg);

				flag = xRCP_FILE->Read__MEM();

				log_msg = "Step Loop : Start (2) ...";
				xLOG_CTRL->WRITE__LOG(log_msg);

				if(flag > 0)
				{
					if(init_step < 0)
					{
						init_step = 1;

						//
						xCH__PRC_STS->Set__DATA("PROCESSING");	
						Fnc__PRC_LOG__ENABLE(p_variable);

						//
						log_msg = "INIT_STEP : Start ...";
						xLOG_CTRL->WRITE__LOG(log_msg);

						// Start DCOP Process Start;
						// xDCOP_CTRL->Report__PROCESS_START();
						xTIMER_ASYNC->START__COUNT_UP(9999);

						//
						x_toal_step_timer->START__TIMER();						

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
						sEXT_CH__STEP_EXCEPTION_COMMAND->Set__DATA("");
						sCH__EXCEPTION_ACT->Set__DATA("");

						if(!active__log_end_start)
						{
							log_msg = "LOG_STEP START : Start ...";
							xLOG_CTRL->WRITE__LOG(log_msg);

							int log_flag = p_ext_mode_ctrl->Run__FNC_MODE(sEXT_MODE__LOG_STEP_START);
	
							log_msg.Format("LOG_STEP START : End (%1d) ...", log_flag);
							xLOG_CTRL->WRITE__LOG(log_msg);
						}
					}

					// ...
					aEXT_CH__STEP_TIME->Get__DATA(var_data);
					int step_time = atoi(var_data);

					// Item List Log
					int cur_step_no = xRCP_FILE->Get__CUR_STEP_NO();

					// DCOP Step Start 
					int dcop_step_start = -1;

					if(dRCP_CH__PROCESS_DATA_SUMMARY->Check__DATA("Enable") > 0)
					{
						dcop_step_start = 1;
						// xDCOP_CTRL->Report__STEP_START(cur_step_no);
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

					/*
					// ...
					CString cur_mode;
					dEXT_CH__RCP_Use_Next_Learned_Value->Get__DATA(cur_mode);

					if((cur_mode.CompareNoCase(STR__ENABLE)  == 0)
					|| (cur_mode.CompareNoCase(STR__WAP_POS) == 0)
					|| (cur_mode.CompareNoCase(STR__VAT_POS) == 0))
					{
						CString log_msg;
						CString log_bff;

						int next_step_index = cur_step_no;

						//
						log_msg.Format("Use learned value of next step : Next StepID(%1d) \n", (cur_step_no + 1));

						//
						CStringArray l_ch_name;
						CStringArray l_ch_data;
	
						l_ch_name.Add(aEXT_CH__RCP_VALVE_LEARNED_POSITION->Get__CHANNEL_NAME());						
						l_ch_name.Add(aEXT_CH__RCP_CONFINEMENT_RING_LEARNED_POSITION->Get__CHANNEL_NAME());

						if(xRCP_FILE->Get__ITEM_INFO_OF_RECIPE_STEPx(next_step_index, l_ch_name,l_ch_data) > 0)
						{
							CString ch_name;
							CString ch_data;

							int k_limit = l_ch_name.GetSize();
							int k;

							l_ch_data.SetSize(k_limit);

							for(k=0; k<k_limit; k++)
							{
								ch_name = l_ch_name[k];
								ch_data = l_ch_data[k];

								// ...
								{
									log_bff.Format("  %1d)  %s <- \"%s\" \n", k+1,ch_name,ch_data);
									log_msg += log_bff;
								}

								if(ch_data.GetLength() < 1)
								{
									continue;
								}

								if((cur_mode.CompareNoCase(STR__ENABLE)  == 0)
								|| (cur_mode.CompareNoCase(STR__VAT_POS) == 0))
								{
									if(ch_name.CompareNoCase(aEXT_CH__RCP_VALVE_LEARNED_POSITION->Get__CHANNEL_NAME()) == 0)
									{
										aEXT_CH__RCP_VALVE_LEARNED_POSITION->Set__DATA(ch_data);
										continue;
									}
								}

								if((cur_mode.CompareNoCase(STR__ENABLE)  == 0)
								|| (cur_mode.CompareNoCase(STR__WAP_POS) == 0))
								{
									if(ch_name.CompareNoCase(aEXT_CH__RCP_CONFINEMENT_RING_LEARNED_POSITION->Get__CHANNEL_NAME()) == 0)
									{
										aEXT_CH__RCP_CONFINEMENT_RING_LEARNED_POSITION->Set__DATA(ch_data);
										continue;
									}
								}

								// ...
							}
						}

						xLOG_CTRL->WRITE__LOG(log_msg);
					}
					*/
					
					/*
					if(dRCP_CH__PROCESS_DATA_SUMMARY->Check__DATA("Enable") > 0)
					{
						sEXT_CH__DCOP_REPORT_FLAG->Set__DATA(STR__YES);
					}
					else
					{
						sEXT_CH__DCOP_REPORT_FLAG->Set__DATA("");
					}
					*/

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

							flag = p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__STEP_PROC);

							sEXT_CH__STEP_STABLE_REQ->Set__DATA("");
						}
					}

					// DCOP Step End
					int dcop_step_end = -1;
					
					if(dRCP_CH__PROCESS_DATA_SUMMARY->Check__DATA("Enable") > 0)
					{
						dcop_step_end = 1;
						// xDCOP_CTRL->Report__STEP_END(cur_step_no);
					}

					// Process Recovery Check .....
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
								sEXT_CH__STEP_STABLE_REQ->Set__DATA(STR__YES);

								//
								flag = 2;
								sCH__EXCEPTION_ACT->Set__DATA(ACT__JUMP);
							}
							else if(r_act.CompareNoCase(ACT__END) == 0)
							{
								flag = 0;
							}
							else if(r_act.CompareNoCase(ACT__END_WITH_PLASMA_DECHUCK) == 0)
							{
								// ...
								{
									log_msg.Format("%s Started...", r_act);
									xLOG_CTRL->WRITE__LOG(log_msg);
								}

								flag = Fnc__PLASMA_DECHUCK_START(p_variable, p_alarm);

								// ...
								{
									log_msg.Format("%s End... Return:%d \n", r_act,flag);
									xLOG_CTRL->WRITE__LOG(log_msg);
								}

								if(flag < 0)
								{
									// Alarm Occur !!
									int alarm_id = ALID__PLSAMA_DECHUCK_PROCESS_FAILED;
									p_alarm->Popup__ALARM(alarm_id, r_act);
								}
								else
								{
									flag = 0;
								}
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
							//.....
							{
								log_msg = "Exception Command : \"ABORT\" \n";
								xLOG_CTRL->WRITE__LOG(log_msg);
							}

							flag = -1;
						}
						else if(sCH__EXCEPTION_ACT->Check__DATA(ACT__END) > 0)
						{
							//.....
							{
								log_msg = "Exception Command : \"END\" \n";
								xLOG_CTRL->WRITE__LOG(log_msg);
							}

							flag = 0;
						}
						else if(sCH__EXCEPTION_ACT->Check__DATA(ACT__JUMP) > 0)
						{
							// ...
							{
								sEXT_CH__EXCEPTION_CONTINUE_REQ->Set__DATA("");
								aCH__CONTINUE_OVER_STEP_TIME->Set__DATA("0");
							}

							// ...
							{
								log_msg = "Exception Command : \"JUMP\" \n";
								xLOG_CTRL->WRITE__LOG(log_msg);
							}

							// ...
							Fnc__PRC_LOG__PAUSE(p_variable);
							xTIMER_ASYNC->PAUSE();

							//.....
							int min_step = 0;
							int max_step;

							xCH__STEP_TOTAL_NUM->Get__DATA(var_data);
							max_step = atoi(var_data);
							if(max_step > 0)		min_step = 1;
							else					max_step = 0;

							aCH__JUMP_STEP_ID->Change__MIN_MAX_DEC(min_step,max_step,-1);
							xCH__STEP_CUR_NUM->Get__DATA(var_data);
							aCH__JUMP_STEP_ID->Set__DATA(var_data);

							//.....
							sCH__WIN_CTRL_MSG->Set__DATA("Input Step Number or Time.");
							sCH__WIN_CTRL_LOCK->Set__DATA("");
							
							CString win_name = STR__WIN_NAME;
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

							// ...
							{
								Fnc__PRC_LOG__RESUME(p_variable);
								xTIMER_ASYNC->RESUME();
							}
						}

						sEXT_CH__STEP_EXCEPTION_COMMAND->Set__DATA("");
						sCH__EXCEPTION_ACT->Set__DATA("");

						sCH__WIN_CTRL_MSG->Set__DATA("");
						sCH__WIN_CTRL_LOCK->Set__DATA("");
						sCH__WIN_CTRL_JUMP_PAGE->Set__DATA("");
					}

					// Timer Count End
					double db_time;
					db_time = x_async_timer->Get__CURRENT_TIME();
					x_async_timer->STOP();					
			
					// Step Change time .....
					int i_change_time = (int) db_time - step_time;

					if(flag > 0)
					{					
						if(i_change_time != 0)
						{
							var_data.Format("%1d", i_change_time);

							xCH__PRC_CHANGE_TIME_TO_CTC->Set__DATA(var_data);
							sEXT_CH__PRC_CHANGE_TIME_TO_CTC->Set__DATA(var_data);
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

							log_bff.Format(" ->>  Step Time : (%.3f / %s) \n", db_time,rcp__step_time);
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

										// ...
										{
											flag = -1;
										}
									}
									else
									{
										xRCP_FILE->Jump__STEP_NO(cur_step);
									}
								}

								if(flag > 0)
								{
									pOBJ__STEP_CTRL->Call__OBJECT(OBJ_MODE__RCP_DATA_INIT);

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
							
								// ...
								sCH__NEXT_STEP_CTRL_REQ->Set__DATA(STR__LOCK);
							}

							// ...
							{
								log_msg = "NEXT_STEP_CTRL : End ...";
								xLOG_CTRL->WRITE__LOG(log_msg);
							}
						}
					}

					if(flag > 0)
					{
						int rcp__steo_max = (int) xCH__STEP_TOTAL_NUM->Get__VALUE();
						int cur__step_id  = (int) xCH__STEP_CUR_NUM->Get__VALUE();

						log_msg.Format(" * REPORT : cur_step (%1d) & max_step (%1d)", cur__step_id, rcp__steo_max);
						xLOG_CTRL->WRITE__LOG(log_msg);

						if(cur__step_id < rcp__steo_max)
						{
							active__log_end_start = true;

							log_msg = "LOG_STEP (END & START) : Start ...";
							xLOG_CTRL->WRITE__LOG(log_msg);

							int log_flag = p_ext_mode_ctrl->Run__FNC_MODE(sEXT_MODE__LOG_STEP_END_START);

							log_msg.Format("LOG_STEP (END & START) : End (%1d) ...", log_flag);
							xLOG_CTRL->WRITE__LOG(log_msg);
						}
						else
						{
							active__log_end_start = false;

							log_msg = "LOG_STEP END : Start ...";
							xLOG_CTRL->WRITE__LOG(log_msg);

							int log_flag = p_ext_mode_ctrl->Run__FNC_MODE(sEXT_MODE__LOG_STEP_END);
	
							log_msg.Format("LOG_STEP END : End (%1d) ...", log_flag);
							xLOG_CTRL->WRITE__LOG(log_msg);
						}
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
					// ...
					{
						log_msg.Format("Fnc__PROC_STEP_START() : Flag -> [0] !!! \n");
						xLOG_CTRL->WRITE__LOG(log_msg);
					}

					flag = 0;
				}

				log_msg = "Step Loop : End(1) ...";
				xLOG_CTRL->WRITE__LOG(log_msg);

				if(p_variable->Check__CTRL_ABORT() > 0)
				{
					// ...
					{
						log_msg.Format("Fnc__PROC_STEP_START() : Flag -> [-1] !!! \n");
						xLOG_CTRL->WRITE__LOG(log_msg);
					}

					flag = -1;
				}

				log_msg = "Step Loop : End(2) ...";
				xLOG_CTRL->WRITE__LOG(log_msg);

				//
				double cur__total_sec = x_toal_step_timer->Get__CURRENT_SEC();
				double dif__total_sec = cur__total_sec - _rcp__total_sec;
				double cur__step_id   = xCH__STEP_CUR_NUM->Get__VALUE();
				double cur__err_rate  = dif__total_sec / cur__step_id;

				log_msg.Format(" * Report : (%.3f) = (%.3f) - (%.3f) -> (%.4f) [%.1f] ", dif__total_sec,cur__total_sec,_rcp__total_sec, cur__err_rate, cur__step_id);
				xLOG_CTRL->WRITE__LOG(log_msg);

				var_data.Format("%.3f", dif__total_sec);
				sCH__REPORT_TOTAL_ERROR_SEC->Set__DATA(var_data);

				var_data.Format("%.5f", cur__err_rate);
				sCH__REPORT_AVG_ERROR_SEC->Set__DATA(var_data);
			}
			while(flag > 0);
		}
	}

	// ...
	{
		Fnc__PRC_LOG__DISABLE(p_variable);

		//
		xTIMER_ASYNC->STOP();		

		xCH__PRC_STS->Set__DATA("IDLE");
		xCH__CHM_STATE->Set__DATA(STR__Idle);

		xCH__STEP_CUR_NUM->Set__DATA("-1");			// 몰라 ! Lam꺼는 Process 끝나면 -1로 올라온데..
	}

	return flag;
}
//.....
int CObj__PROC_FNC
::Call__CLN_READY(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	//
	return Fnc__PROC_READY(p_variable,p_alarm);
}

int CObj__PROC_FNC
::Call__CLN_START(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	//
	return Fnc__PROC_START(p_variable,p_alarm);
}


//.....
int CObj__PROC_FNC
::Call__MNT_READY(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__PROC_READY(p_variable,p_alarm);
}
int CObj__PROC_FNC
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
	int flag = Fnc__PROC_START(p_variable,p_alarm);

	if(log_clear_flag > 0)
	{
		xEXT_CH__LOG_SUB_DIR->Set__DATA("");
		xEXT_CH__LOG_FILE_NAME->Set__DATA("");
	}

	return flag;
}

int CObj__PROC_FNC
::Call__JOB_START_READY(CII_OBJECT__VARIABLE *p_variable,
						CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__PROC_READY(p_variable,p_alarm);
}
int CObj__PROC_FNC
::Call__JOB_END_READY(CII_OBJECT__VARIABLE *p_variable,
					  CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__PROC_START(p_variable,p_alarm);
}


//-----------------------------------------------------------------------------
// Process Data Log
int  CObj__PROC_FNC::Fnc__PRC_LOG__ENABLE(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	//.....	
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

	//.....
	CStringArray l_para;
	l_para.Add(pm_rcp);

	dCH__DATALOG_GATHERING_ENABLE_DISABLE->Set__DATA("ENABLE");

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__LOG_ENABLE,l_para);
}
int  CObj__PROC_FNC::Fnc__PRC_LOG__DISABLE(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	//
	dCH__DATALOG_GATHERING_ENABLE_DISABLE->Set__DATA("DISABLE");

	return p_ext_mode_ctrl->Run__FNC_MODE(sEXT_MODE__LOG_DISABLE);
}

int  CObj__PROC_FNC::Fnc__PRC_LOG__PAUSE(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	//
	return p_ext_mode_ctrl->Run__FNC_MODE(sEXT_MODE__LOG_PAUSE);
}
int  CObj__PROC_FNC::Fnc__PRC_LOG__RESUME(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	//
	return p_ext_mode_ctrl->Run__FNC_MODE(sEXT_MODE__LOG_RESUME);
}

