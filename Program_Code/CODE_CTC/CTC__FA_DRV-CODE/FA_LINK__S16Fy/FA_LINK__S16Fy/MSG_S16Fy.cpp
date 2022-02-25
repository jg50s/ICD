#include "StdAFx.h"
#include "Macro_FNC.h"
#include "CRes__Rcp_Info.h"


#include "MSG_S16Fy.h"
CMsg_S16Fy mMSG_S16Fy;


//----------------------------------------------------------------------------
CMsg_S16Fy::CMsg_S16Fy()
{
	iSx = 16;
}

void CMsg_S16Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	/*
	switch(p_bridge_ctrl->iFy)
	{
	}
	*/
}

void CMsg_S16Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	switch(p_bridge_ctrl->iFy)
	{
		case 5:		Recv__F5(p_bridge_ctrl);		return;
		case 7:		Recv__F7(p_bridge_ctrl);		return;
		case 9:		Recv__F9(p_bridge_ctrl);		return;
		case 11:	Recv__F11(p_bridge_ctrl);		return;
		case 13:	Recv__F13(p_bridge_ctrl);		return;
		case 15:	Recv__F15(p_bridge_ctrl);		return;
		case 17:	Recv__F17(p_bridge_ctrl);		return;
		case 19:	Recv__F19(p_bridge_ctrl);		return;
		case 21:	Recv__F21(p_bridge_ctrl);		return;

		case 25:	Recv__F25(p_bridge_ctrl);		return;
		case 27:	Recv__F27(p_bridge_ctrl);		return;
		case 29:	Recv__F29(p_bridge_ctrl);		return;
	}
}


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void CMsg_S16Fy::Recv__F5(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CString db_name;
	CString var_data;

	//-------------------------------
	CString pjobid;
	CString prcmdname;

	//-------------------------------
	// PJOBID
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	pjobid = var_data;

	// PRCMDNAME
	db_name = "-1-3";
	p_recv_ctrl->Get_Data(db_name,var_data);

	prcmdname = var_data;
	prcmdname.MakeUpper();
	//-------------------------------

	//-------------------------------
	CI_FA_300mm__E40_CTRL *p_e40_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E40();

	//-------------------------------
	int acka_bool = TRUE;
	int err_limit = 0;

	//----------------------------------------------------------------
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	if(p_e30_ctrl->Is_REMOTE() < 0)
	{
		acka_bool = FALSE;
		err_limit = 1;

		//---------------------------
		int err_code;
		CString err_text;

		err_code = ERROR_CODE__COMMAND_NOT_VALID_FOR_CURRENT_STATE;
		err_text = "Command not valid for current state";
		//---------------------------
	}
	else
	{
		int flag = p_e40_ctrl->Run_COMMAND(pjobid,prcmdname);

		if(flag < 0)
		{
			acka_bool = FALSE;
			err_limit = 1;

			//---------------------------
			int err_code;
			CString err_text;

			p_e40_ctrl->Get_PRJob_Error(err_code,err_text);

			// ERRCODE
			db_name = "-1-2-2-1-1";
			p_send_ctrl->Add_U1(db_name,err_code);

			// ERRTEXT
			db_name = "-1-2-2-1-2";
			p_send_ctrl->Add_Ascii(db_name,err_text);
			//---------------------------
		}
	}
	//----------------------------------------------------------------

	// PJOBID
	db_name = "-1-1";
	p_send_ctrl->Add_Ascii(db_name,pjobid);

	// ACKA
	db_name = "-1-2-1";
	p_send_ctrl->Add_Boolean(db_name,acka_bool);

	// ERROR_LIMIT
	db_name = "-1-2-2";
	p_send_ctrl->Add_List(db_name,err_limit);
	//-------------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S16Fy::Recv__F7(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CString db_name;
	CString var_data;

	//-------------------------------

	//-------------------------------
	//-------------------------------

	//-------------------------------
	//-------------------------------

	//-------------------------------
	// MessageBox(NULL,"CHECK","MSG_S16 : Recv__F7()",MB_OK|MB_TOPMOST);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S16Fy::Recv__F9(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CString db_name;
	CString var_data;

	//-------------------------------

	//-------------------------------
	//-------------------------------

	//-------------------------------
	//-------------------------------

	//-------------------------------
	// MessageBox(NULL,"CHECK","MSG_S16 : Recv__F9()",MB_OK|MB_TOPMOST);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}

void CMsg_S16Fy::Recv__F11(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_FA_300mm__E40_CTRL *p_e40_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E40();

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();
	
	// ...
	CRes__Rcp_Info m_rcp_tuning;

	CString db_name;
	CString var_data;

	//-------------------------------
	CString pjobid;
	int err_flag = 0;
	int err_apc_flag = 0;
	int err_apc_id = 0;

	p_e40_ctrl->Clear_PRJob();

	//-------------------------------
	{
		// 1.2  PJOBID
		{
			db_name = "-1-2";
			p_recv_ctrl->Get_Data(db_name, pjobid);
		}

		// 1.4  CST LIST
		{
			db_name = "-1-4";
			p_recv_ctrl->Get_Data(db_name,var_data);

			int cst_list = atoi(var_data);
			int t;

			for(t=0; t<cst_list; t++)
			{
				// 1.4.n.1  CARRIERID
				{
					db_name.Format("-1-4-%1d-1",t+1);
					p_recv_ctrl->Get_Data(db_name,var_data);

					p_e40_ctrl->Load_CARRIERID(var_data);
				}
				// 1.4.n.2  SLOT_LIMIT
				{
					db_name.Format("-1-4-%1d-2",t+1);
					p_recv_ctrl->Get_Data(db_name,var_data);

					int slot_limit = atoi(var_data);
					int i;
	
					for(i=0; i<slot_limit; i++)
					{
						// 1.4.n.2.m  SLOTID
						{
							db_name.Format("-1-4-%1d-2-%1d",t+1,i+1);
							p_recv_ctrl->Get_Data(db_name,var_data);

							p_e40_ctrl->Load_SLOTID(atoi(var_data));
						}
					}
				}
			}
		}

		// 1.5.1  RECIPE METHOD
		{
			db_name = "-1-5-1";
			p_recv_ctrl->Get_Data(db_name,var_data);

			p_e40_ctrl->Load_RecipeMethod(atoi(var_data));
		}
		// 1.5.2  RCPSPEC
		{
			db_name = "-1-5-2";
			p_recv_ctrl->Get_Data(db_name,var_data);
			
			p_e40_ctrl->Load_RecID(var_data);
		}
		// 1.5.3  RCPPARNM_LIMIT
		{
			db_name = "-1-5-3";
			p_recv_ctrl->Get_Data(db_name,var_data);

			int rcpparnm_limit = atoi(var_data);
			int t;
				
			// ...
			CString rcp_name;
			CString rcp_data;
			int pm_id = -1;
			CUIntArray l_pm_id;			
			CStringArray l_rcp_name;
			CStringArray l_rcp_data;

			for(t=0; t<rcpparnm_limit; t++)
			{
				// 1.5.3.n.1  RCPPARNM
				{
					db_name.Format("-1-5-3-%1d-1", t+1);
					p_recv_ctrl->Get_Data(db_name,var_data);

					rcp_name = var_data;
				}
				// 1.5.3.n.2  RCPPARVAL
				{
					db_name.Format("-1-5-3-%1d-2", t+1);
					p_recv_ctrl->Get_Data(db_name,var_data);

					rcp_data = var_data;
				}
					
				// ...
				{
					int step_id;
					CString item_name;
						
					int flag = Macro__Get_PmID_And_StepID_And_ParaName(rcp_name, pm_id,step_id,item_name);
						
					if(flag > 0)
					{
						int check_flag = -1;
							
						CString item_unit;
						CString item_range;
						CString ch_name;
						CString ch_type;
						CString fmt_unit;
						int fmt_size;
							
						if(p_ppbody_ctrl->Set_Current_PM_ID(pm_id) > 0)
						{
							int step_max = p_ppbody_ctrl->Get_STEP_PARAMETER_SIZE();
								
							if((step_id > 0) && (step_id <= step_max))
							{
								if(p_ppbody_ctrl->Check_STEP_DATA(item_name,rcp_data) > 0)
								{
									if(p_ppbody_ctrl->Get_STEP_PARAMETER_From_ITEM_NAME(item_name,
										                                                item_unit,
									                                                 	item_range,
										                                                ch_name,
										                                                ch_type,
										                                                fmt_unit,
										                                                fmt_size) > 0) 
									{
										check_flag = 1;
											
										m_rcp_tuning.Load__Rcp_Info(pjobid,pm_id,step_id, ch_type,ch_name,rcp_data);
									}
									else
									{
										err_apc_id = 14;
									}
								}
								else
								{
									err_apc_id = 13;
								}
							}
							else
							{
								err_apc_id = 12;
							}
						}
						else
						{
							err_apc_id = 11;
						}
							
						if(check_flag < 0)
						{
							err_apc_flag = 2;
						}
						else
						{	
							l_rcp_name.Add(rcp_name);
							l_rcp_data.Add(rcp_data);
	
							if(Macro__Check_ID(pm_id,l_pm_id) < 0)
							{
								l_pm_id.Add(pm_id);
							}
						}
					}
					else
					{
						err_apc_flag = 1;
						err_apc_id = 21;
					}
				}
			}

			if(err_apc_flag < 0)
			{
				p_e40_ctrl->Load_RecipeTuning(l_rcp_name,l_rcp_data);	
				
				// ...
				{
					CString rcp_info;
					
					int k_limit = l_pm_id.GetSize();
					int k;
					
					for(k=0; k<k_limit; k++)
					{
						int i_pm = (int) l_pm_id[k];
						
						rcp_info = "";
						if(m_rcp_tuning.Get__Rcp_Info(pjobid,i_pm,rcp_info) > 0)
						{
							p_e40_ctrl->Load_RecipeInfo(i_pm, rcp_info);	
						}
					}
				}
			}
		}
	
		// 1.6  PROCESS START
		{
			db_name = "-1-6";
			p_recv_ctrl->Get_Data(db_name,var_data);

			// ...
			int start_method;

			if(var_data.CompareNoCase("FF") == 0)	start_method = 1;
			else									start_method = atoi(var_data);

			p_e40_ctrl->Load_PRProcessStart(start_method);
		}
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	int acka_bool = TRUE;
	int err_limit = 0;

	if(p_e30_ctrl->Is_REMOTE() < 0)
	{
		acka_bool = FALSE;
		err_limit = 1;

		// ...
		int err_code;
		CString err_text;

		err_code = ERROR_CODE__COMMAND_NOT_VALID_FOR_CURRENT_STATE;
		err_text = "Command not valid for current state";

		// 1.2.2.1.1  ERRCODE
		{
			db_name = "-1-2-2-1-1";
			p_send_ctrl->Add_U1(db_name,err_code);
		}
		// 1.2.2.1.2  ERRTEXT
		{
			db_name = "-1-2-2-1-2";
			p_send_ctrl->Add_Ascii(db_name,err_text);
		}
	}
	else
	{
		int err_code;
		CString err_text;
			
		if(err_apc_flag < 0)
		{
			if(p_e40_ctrl->Create_PRJob(pjobid) < 0)
			{
				err_flag = 1;
			}
			
			p_e40_ctrl->Get_PRJob_Error(err_code,err_text);
		}
		else
		{
			err_flag = 1;
				
			// ...
			{
				err_code = 101;
				err_text.Format("Recipe Tuning Parameter Error(%1d)", err_apc_id);
			}
		}
			
		// 1.2.2.1.1  ERRCODE
		{
			db_name = "-1-2-2-1-1";
			p_send_ctrl->Add_U1(db_name,err_code);
		}
		// 1.2.2.1.2  ERRTEXT
		{
			db_name = "-1-2-2-1-2";
			p_send_ctrl->Add_Ascii(db_name,err_text);
		}

		if(err_flag > 0)
		{
			acka_bool = FALSE;
			err_limit = 1;
		}
	}

	// ...
	{
		// 1.1  PJOBID
		{
			db_name = "-1-1";
			p_send_ctrl->Add_Ascii(db_name,pjobid);
		}
		// 1.2.1  ACKA
		{
			db_name = "-1-2-1";
			p_send_ctrl->Add_Boolean(db_name,acka_bool);
		}
		// 1.2.2  ERROR_LIMIT
		{
			db_name = "-1-2-2";
			p_send_ctrl->Add_List(db_name,err_limit);
		}
	}
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//----------------------------------------------------------------

	FA__OK;
}
void CMsg_S16Fy::Recv__F13(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_FA_300mm__E40_CTRL *p_e40_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E40();

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();

	// ...
	CRes__Rcp_Info m_rcp_tuning;

	CString db_name;
	CString var_data;

	//----------------------------------------------------------------
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	if(p_e30_ctrl->Is_REMOTE() < 0)
	{
		//-------------------------------
		int err_code;
		CString err_text;

		err_code = ERROR_CODE__COMMAND_NOT_VALID_FOR_CURRENT_STATE;
		err_text = "Command not valid for current state";
		//-------------------------------

		//-------------------------------
		{
			// ACKA
			db_name = "-1-2-1";
			p_send_ctrl->Add_Boolean(db_name,FALSE);

			// ERROR_LIMIT
			db_name = "-1-2-2";
			p_send_ctrl->Add_List(db_name,1);

			// ERRCODE
			db_name = "-1-2-2-1-1";
			p_send_ctrl->Add_U1(db_name,err_code);

			// ERRTEXT
			db_name = "-1-2-2-1-2";
			p_send_ctrl->Add_Ascii(db_name,err_text);
		}
		//-------------------------------

		p_bridge_ctrl->pFA_DRV_CTRL->Send();

		FA__OK;
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	int pjob_limit;
	CStringArray l_rcp_name;
	CStringArray l_rcp_data;

	int err_flag = 0;
	int err_apc_flag = 0;
	int err_apc_id = 0;

	//-------------------------------
	{
		int recipe_method;
		CString rcpspec;
		CString pjobid;
		int process_start;
		
		// 1.3.1  RECIPE_METHOD
		{
			db_name = "-1-3-1";
			p_recv_ctrl->Get_Data(db_name,var_data);
			
			recipe_method = atoi(var_data);
			p_e40_ctrl->Load_RecipeMethod(recipe_method);
		}
		// 1.3.2  RCPSPEC
		{
			db_name = "-1-3-2";
			p_recv_ctrl->Get_Data(db_name,var_data);
			
			rcpspec = var_data;
			p_e40_ctrl->Load_RecID(rcpspec);
		}
		// 1.3.3  RCPPARNM_LIMIT
		{
			db_name = "-1-3-3";
			p_recv_ctrl->Get_Data(db_name, var_data);

			int rcpparnm_limit = atoi(var_data);
			int t;

			for(t=0; t<rcpparnm_limit; t++)
			{
				// 1.3.3.n.1  RCPPARNM
				{
					db_name.Format("-1-3-3-%1d-1", t+1);
					p_recv_ctrl->Get_Data(db_name, var_data);

					l_rcp_name.Add(var_data);
				}
				// 1.3.3.n.2  RCPPARVAL
				{
					db_name.Format("-1-3-3-%1d-2", t+1);
					p_recv_ctrl->Get_Data(db_name, var_data);

					l_rcp_data.Add(var_data);
				}
			}
		}
		
		// 1.4  PROCESS_START
		{
			db_name = "-1-4";
			p_recv_ctrl->Get_Data(db_name,var_data);
			
			if(var_data.CompareNoCase("FF") == 0)		process_start = 1;
			else										process_start = atoi(var_data);
			
			p_e40_ctrl->Load_PRProcessStart(process_start);
		}

		// 1.2  PJOB_LIMIT
		{
			db_name = "-1-2";
			p_recv_ctrl->Get_Data(db_name,var_data);

			pjob_limit = atoi(var_data);

			// ...
			int i;

			for(i=0; i<pjob_limit; i++)
			{
				p_e40_ctrl->Clear_PRJob();

				// 1.2.n.1  PJOBID
				{
					db_name.Format("-1-2-%1d-1", i+1);
					p_recv_ctrl->Get_Data(db_name,pjobid);

					// 1.2.n.3  CST_LIST				
					{
						db_name.Format("-1-2-%1d-3", i+1);
						p_recv_ctrl->Get_Data(db_name,var_data);

						// ...
						int cst_list = atoi(var_data);
						int t;

						for(t=0; t<cst_list; t++)
						{
							// 1.2.n.3.m.1  CARRIERID
							{
								db_name.Format("-1-2-%1d-3-%1d-1", i+1,t+1);
								p_recv_ctrl->Get_Data(db_name,var_data);
	
								p_e40_ctrl->Load_CARRIERID(var_data);
							}
	
							// 1.2.n.3.m.2  SLOT_LIMIT
							{
								db_name.Format("-1-2-%1d-3-%1d-2", i+1,t+1);
								p_recv_ctrl->Get_Data(db_name,var_data);

								int slot_limit = atoi(var_data);
								int k;

				                for(k=0; k<slot_limit; k++)
								{
									// 1.2.n.3.m.2.1  SLOTID
									{
										db_name.Format("-1-2-%1d-3-%1d-2-%1d", i+1,t+1,k+1);
										p_recv_ctrl->Get_Data(db_name,var_data);
	
										p_e40_ctrl->Load_SLOTID(atoi(var_data));
									}
								}
							}
						}
					}
				}

				// 1.3.3  RCPPARNM_LIMIT
				{
					int rcpparnm_limit = l_rcp_name.GetSize();
					int t;

					// ...
					CString rcp_name;
					CString rcp_data;
					int pm_id = -1;
					CUIntArray l_pm_id;

					for(t=0; t<rcpparnm_limit; t++)
					{
						// 1.3.3.n.1  RCPPARNM
						{
							rcp_name = l_rcp_name[t];
						}
						// 1.3.3.n.2  RCPPARVAL
						{
							rcp_data = l_rcp_data[t];
						}

						// ...
						{
							int step_id;
							CString item_name;

							int flag = Macro__Get_PmID_And_StepID_And_ParaName(rcp_name, pm_id,step_id,item_name);

							if(flag > 0)
							{
								int check_flag = -1;

								CString item_unit;
								CString item_range;
								CString ch_name;
								CString ch_type;
								CString fmt_unit;
								int fmt_size;

								if(p_ppbody_ctrl->Set_Current_PM_ID(pm_id) > 0)
								{
									int step_max = p_ppbody_ctrl->Get_STEP_PARAMETER_SIZE();

									if((step_id > 0) && (step_id <= step_max))
									{
										if(p_ppbody_ctrl->Check_STEP_DATA(item_name,rcp_data) > 0)
										{
											if(p_ppbody_ctrl->Get_STEP_PARAMETER_From_ITEM_NAME(item_name,
												                                                item_unit,
																								item_range,
																								ch_name,
																								ch_type,
																								fmt_unit,
																								fmt_size) > 0)
											{
												check_flag = 1;
		
												m_rcp_tuning.Load__Rcp_Info(pjobid,pm_id,step_id, ch_type,ch_name,rcp_data);
											}
											else
											{
												err_apc_id = 14;
											}
										}
										else
										{
											err_apc_id = 13;
										}
									}
									else
									{
										err_apc_id = 12;
									}
								}
								else
								{
									err_apc_id = 11;
								}

								if(check_flag < 0)
								{
									err_apc_flag = 2;
								}
								else
								{									
									if(Macro__Check_ID(pm_id,l_pm_id) < 0)
									{
										l_pm_id.Add(pm_id);
									}
								}
							}
							else
							{
								err_apc_flag = 1;
								err_apc_id = 21;
							}
						}
					}

					if(err_apc_flag < 0)
					{
						p_e40_ctrl->Load_RecipeTuning(l_rcp_name,l_rcp_data);	

						// ...
						{
							CString rcp_info;
							
							int k_limit = l_pm_id.GetSize();
							int k;
							
							for(k=0; k<k_limit; k++)
							{
								int i_pm = (int) l_pm_id[k];
								
								rcp_info = "";
								if(m_rcp_tuning.Get__Rcp_Info(pjobid,i_pm,rcp_info) > 0)
								{
									p_e40_ctrl->Load_RecipeInfo(i_pm, rcp_info);	
								}
							}
						}
					}
				}

				// ...
				{
					// PJOBID
					{
						db_name.Format("-1-1-%1d",i+1);
						p_send_ctrl->Add_Ascii(db_name, pjobid);
					}
				
					// ...
					{
						int err_code;
						CString err_text;
					
						if(err_apc_flag < 0)
						{
							if(p_e40_ctrl->Create_PRJob(pjobid) < 0)
							{
								err_flag = 1;
							}
						
							p_e40_ctrl->Get_PRJob_Error(err_code,err_text);
						}
						else
						{
							err_flag = 1;
							
							// ...
							{
								err_code = 101;
								err_text.Format("Recipe Tuning Parameter Error(%1d)", err_apc_id);
							}
						}
					
						// 1.2.2.n.1  ERRCODE
						{
							db_name.Format("-1-2-2-%1d-1", i+1);
							p_send_ctrl->Add_U1(db_name,err_code);
						}
						// 1.2.2.n.2  ERRTEXT
						{
							db_name.Format("-1-2-2-%1d-2", i+1);
							p_send_ctrl->Add_Ascii(db_name,err_text);
						}
					}
				}
			}

			// ...
		}
	}
	//-------------------------------

	//-------------------------------
	{
		// 1.1  PJOB_LIMIT
		{
			db_name = "-1-1";
			p_send_ctrl->Add_List(db_name, pjob_limit);
		}

		if(err_flag > 0)
		{
			// 1.2.1  ACKA
			{
				db_name = "-1-2-1";
				p_send_ctrl->Add_Boolean(db_name,FALSE);
			}
			// 1.2.2  ERROR_LIMIT
			{
				db_name = "-1-2-2";
				p_send_ctrl->Add_List(db_name,pjob_limit);
			}
		}
		else
		{
			// 1.2.1  ACKA
			{
				db_name = "-1-2-1";
				p_send_ctrl->Add_Boolean(db_name,TRUE);
			}
			// 1.2.2  ERROR_LIMIT
			{
				db_name = "-1-2-2";
				p_send_ctrl->Add_List(db_name,0);
			}
		}
	}

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//----------------------------------------------------------------

	FA__OK;
}
void CMsg_S16Fy::Recv__F15(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_FA_300mm__E40_CTRL *p_e40_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E40();

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();

	// ...
	CRes__Rcp_Info m_rcp_tuning;

	CString db_name;
	CString var_data;

	//----------------------------------------------------------------
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	if(p_e30_ctrl->Is_REMOTE() < 0)
	{
		int err_code;
		CString err_text;

		err_code = ERROR_CODE__COMMAND_NOT_VALID_FOR_CURRENT_STATE;
		err_text = "Command not valid for current state";

		// 1.2.1  ACKA
		{
			db_name = "-1-2-1";
			p_send_ctrl->Add_Boolean(db_name,FALSE);
		}
		// 1.2.2  ERROR_LIMIT
		{
			db_name = "-1-2-2";
			p_send_ctrl->Add_List(db_name,1);
		}
		// 1.2.2.1.1  ERRCODE
		{
			db_name = "-1-2-2-1-1";
			p_send_ctrl->Add_U1(db_name,err_code);
		}
		// 1.2.2.1.2  ERRTEXT
		{
			db_name = "-1-2-2-1-2";
			p_send_ctrl->Add_Ascii(db_name,err_text);
		}

		p_bridge_ctrl->pFA_DRV_CTRL->Send();

		FA__OK;
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	int pjob_limit =  0;
	int err_flag   = -1;
	int err_apc_flag = -1;
	int err_apc_id = 0;

	// 1.2  LIST_LIMIT 
	{
		db_name = "-1-2";
		p_recv_ctrl->Get_Data(db_name, var_data);
		
		pjob_limit = atoi(var_data);

		// ...
		int i;

		for(i=0; i<pjob_limit; i++)
		{
			p_e40_ctrl->Clear_PRJob();

			// ...
			{
				err_apc_flag = -1;
				err_apc_id = 0;
			}

			// ...
			CString para_pjobid;
			int pm_id;
			CUIntArray l_pm_id;

			// 1.2.n.1  PJOBID
			{
				db_name.Format("-1-2-%1d-1", i+1);
				p_recv_ctrl->Get_Data(db_name, para_pjobid);
			}
		
			// 1.2.n.3  CST_LIST
			{
				db_name.Format("-1-2-%1d-3", i+1);
				p_recv_ctrl->Get_Data(db_name, var_data);

				// ...
				int cst_list = atoi(var_data);
				int t;

				for(t=0; t<cst_list; t++)
				{
					// 1.2.n.3.m.1  CARRIERID
					{
						db_name.Format("-1-2-%1d-3-%1d-1",i+1,t+1);
						p_recv_ctrl->Get_Data(db_name, var_data);
	
						p_e40_ctrl->Load_CARRIERID(var_data);
					}
		
					// 1.2.n.3.m.2  SLOT_LIMIT
					{
						db_name.Format("-1-2-%1d-3-%1d-2",i+1,t+1);
						p_recv_ctrl->Get_Data(db_name, var_data);

						// ...
						int slot_limit = atoi(var_data);
						int j;
			
						for(j=0; j<slot_limit; j++)
						{
							// 1.2.n.3.m.2.k  SLOTID
							{
								db_name.Format("-1-2-%1d-3-%1d-2-%1d", i+1,t+1,j+1);
								p_recv_ctrl->Get_Data(db_name, var_data);
			
								p_e40_ctrl->Load_SLOTID(atoi(var_data));
							}
						}
					}
				}	
			}
		
			// 1.2.n.4  RECIPE_INFO
			{
				// 1.2.n.4.1  RECIPE_METHOD
				{
					db_name.Format("-1-2-%1d-4-1",i+1);
					p_recv_ctrl->Get_Data(db_name, var_data);

					int i_rcp_method = atoi(var_data);
		
					p_e40_ctrl->Load_RecipeMethod(i_rcp_method);
				}
				// 1.2.n.4.2  RCPSPEC
				{
					db_name.Format("-1-2-%1d-4-2",i+1);
					p_recv_ctrl->Get_Data(db_name, var_data);

					p_e40_ctrl->Load_RecID(var_data);
				}
				// 1.2.n.4.3  RCPPARNM_LIMIT 
				{
					db_name.Format("-1-2-%1d-4-3",i+1);
					p_recv_ctrl->Get_Data(db_name, var_data);

					int rcpparnm_limit = atoi(var_data);
					int t;

					// ...
					CStringArray l_rcp_name;
					CStringArray l_rcp_data;

					CString rcp_name;
					CString rcp_data;
						
					for(t=0; t<rcpparnm_limit; t++)
					{
						// 1.2.n.4.3.m.1  RCPPARNM
						{
							db_name.Format("-1-2-%1d-4-3-%1d-1",i+1,t+1);
							p_recv_ctrl->Get_Data(db_name, var_data);
		
							rcp_name = var_data;
						}
						// 1.2.n.4.3.m.2  RCPPARVAL
						{
							db_name.Format("-1-2-%1d-4-3-%1d-2",i+1,t+1);
							p_recv_ctrl->Get_Data(db_name, var_data);

							rcp_data = var_data;
						}

						// ...
						{
							int step_id;
							CString item_name;

							int flag = Macro__Get_PmID_And_StepID_And_ParaName(rcp_name, pm_id,step_id,item_name);

							if(flag > 0)
							{
								int check_flag = -1;

								CString item_unit;
								CString item_range;
								CString ch_name;
								CString ch_type;
								CString fmt_unit;
								int fmt_size;

								if(p_ppbody_ctrl->Set_Current_PM_ID(pm_id) > 0)
								{
									int step_max = p_ppbody_ctrl->Get_STEP_PARAMETER_SIZE();

									if((step_id > 0) && (step_id <= step_max))
									{
										if(p_ppbody_ctrl->Check_STEP_DATA(item_name,rcp_data) > 0)
										{
											if(p_ppbody_ctrl->Get_STEP_PARAMETER_From_ITEM_NAME(item_name,
												                                                item_unit,
																								item_range,
																								ch_name,
																								ch_type,
																								fmt_unit,
																								fmt_size) > 0)
											{
												check_flag = 1;
		
												m_rcp_tuning.Load__Rcp_Info(para_pjobid,pm_id,step_id, ch_type,ch_name,rcp_data);
											}
											else
											{
												err_apc_id = 14;
											}
										}
										else
										{
											err_apc_id = 13;
										}
									}
									else
									{
										err_apc_id = 12;
									}
								}
								else
								{
									err_apc_id = 11;
								}

								if(check_flag < 0)
								{
									err_apc_flag = 2;
								}
								else
								{
									l_rcp_name.Add(rcp_name);
									l_rcp_data.Add(rcp_data);

									if(Macro__Check_ID(pm_id,l_pm_id) < 0)
									{
										l_pm_id.Add(pm_id);
									}
								}
							}
							else
							{
								err_apc_flag = 1;
								err_apc_id = 21;
							}
						}
					}

					if(err_apc_flag < 0)
					{
						p_e40_ctrl->Load_RecipeTuning(l_rcp_name,l_rcp_data);	

						// ...
						{
							CString rcp_info;

							int k_limit = l_pm_id.GetSize();
							int k;

							for(k=0; k<k_limit; k++)
							{
								int i_pm = (int) l_pm_id[k];
						
								rcp_info = "";
								if(m_rcp_tuning.Get__Rcp_Info(para_pjobid,i_pm,rcp_info) > 0)
								{
									p_e40_ctrl->Load_RecipeInfo(i_pm, rcp_info);	
								}
							}
						}
					}

					// ...
				}
			}

			// 1.2.n.5  PROCESS-START
			{
				db_name.Format("-1-2-%1d-5",i+1);
				p_recv_ctrl->Get_Data(db_name, var_data);

				// ...
				{
					int start_method;
	
					if(var_data.CompareNoCase("FF") == 0)		start_method = 1;
					else										start_method = atoi(var_data);
	
					p_e40_ctrl->Load_PRProcessStart(start_method);
				}
			}

			// ...
			{
				// PJOBID
				{
					db_name.Format("-1-1-%1d",i+1);
					p_send_ctrl->Add_Ascii(db_name, para_pjobid);
				}

				// ...
				{
					int err_code;
					CString err_text;

					if(err_apc_flag < 0)
					{
						if(p_e40_ctrl->Create_PRJob(para_pjobid) < 0)
						{
							err_flag = 1;
						}

						p_e40_ctrl->Get_PRJob_Error(err_code,err_text);
					}
					else
					{
						err_flag = 1;

						// ...
						{
							err_code = 101;
							err_text.Format("Recipe Tuning Parameter Error(%1d)", err_apc_id);
						}
					}

					// ERRCODE
					{
						db_name.Format("-1-2-2-%1d-1",i+1);
						p_send_ctrl->Add_U1(db_name, err_code);
					}
					// ERRTEXT
					{
						db_name.Format("-1-2-2-%1d-2",i+1);
						p_send_ctrl->Add_Ascii(db_name, err_text);
					}
				}
			}

			// ...
		}
	}

	// 1.1  PJ_LIMIT
	{
		db_name = "-1-1";
		p_send_ctrl->Add_List(db_name, pjob_limit);

		if(err_flag > 0)
		{
			// 1.2.1  ACKA
			{
				db_name = "-1-2-1";
				p_send_ctrl->Add_Boolean(db_name, FALSE);
			}
			// 1.2.2  ERROR_LIMIT
			{
				db_name = "-1-2-2";
				p_send_ctrl->Add_List(db_name, pjob_limit);
			}
		}
		else
		{
			// 1.2.1  ACKA
			{
				db_name = "-1-2-1";
				p_send_ctrl->Add_Boolean(db_name, TRUE);
			}
			// 1.2.2  ERROR_LIMIT
			{
				db_name = "-1-2-2";
				p_send_ctrl->Add_List(db_name, 0);
			}
		}
	}

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//----------------------------------------------------------------

	FA__OK;
}
void CMsg_S16Fy::Recv__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_FA_300mm__E40_CTRL *p_e40_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E40();

	CString db_name;
	CString var_data;

	//----------------------------------------------------------------
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	if(p_e30_ctrl->Is_REMOTE() < 0)
	{
		//-------------------------------
		int err_code;
		CString err_text;

		err_code = ERROR_CODE__COMMAND_NOT_VALID_FOR_CURRENT_STATE;
		err_text = "Command not valid for current state";
		//-------------------------------

		//-------------------------------
		// ACKA
		db_name = "-1-2-1";
		p_send_ctrl->Add_Boolean(db_name,FALSE);

		// ERROR_LIMIT
		db_name = "-1-2-2";
		p_send_ctrl->Add_List(db_name,1);

		// ERRCODE
		db_name = "-1-2-2-1-1";
		p_send_ctrl->Add_U1(db_name,err_code);

		// ERRTEXT
		db_name = "-1-2-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
		//-------------------------------

		p_bridge_ctrl->pFA_DRV_CTRL->Send();

		FA__OK;
	}
	//----------------------------------------------------------------

	//-------------------------------
	int pr_limit;
	int i;
	CString pjobid;

	int error_count = 0;
	int err_code;
	CString err_text;
	
	//-------------------------------
	// PR_LIMIT
	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	pr_limit = atoi(var_data);
	
	if(pr_limit > 0)
	{
		for(i=0;i<pr_limit;i++)
		{
			// PJOBID
			db_name.Format("-1-%1d",i+1);
			p_recv_ctrl->Get_Data(db_name,pjobid);

			//-----------------------------------------------------
			int flag = p_e40_ctrl->Dequeue_PJOBID(pjobid);

			if(flag < 0)
			{
				error_count = 1;
			}
			//-----------------------------------------------------

			//-----------------------------------------------------
			p_e40_ctrl->Get_PRJob_Error(err_code,err_text);

			// PRJOBID
			db_name.Format("-1-1-%1d",i+1);
			p_send_ctrl->Add_Ascii(db_name,pjobid);

			// ERRCODE
			db_name.Format("-1-2-2-%1d-1",i+1);
			p_send_ctrl->Add_U1(db_name,err_code);
			
			// ERRTEXT
			db_name.Format("-1-2-2-%1d-2",i+1);
			p_send_ctrl->Add_Ascii(db_name,err_text);
			//-----------------------------------------------------
		}
	}
	else
	{
		CStringArray l_pjobid;

		//-----------------------------------------------------
		int flag = p_e40_ctrl->Dequeue_ALL(l_pjobid);
	
		pr_limit = l_pjobid.GetSize();

		for(i=0;i<pr_limit;i++)
		{
			// PRJOBID
			db_name.Format("-1-1-%1d",i+1);
			p_send_ctrl->Add_Ascii(db_name,l_pjobid[i]);
		}
		//-----------------------------------------------------
	}
	//-------------------------------
	
	//-------------------------------
	// PR_LIMIT
	db_name = "-1-1";
	p_send_ctrl->Add_List(db_name,pr_limit);

	if(error_count > 0)
	{
		//-------------------------------
		// ACKA
		db_name = "-1-2-1";
		p_send_ctrl->Add_Boolean(db_name,FALSE);

		// ERROR_LIMIT
		db_name = "-1-2-2";
		p_send_ctrl->Add_List(db_name,pr_limit);
		//-------------------------------
	}
	else
	{
		//-------------------------------
		// ACKA
		db_name = "-1-2-1";
		p_send_ctrl->Add_Boolean(db_name,TRUE);

		// ERROR_LIMIT
		db_name = "-1-2-2";
		p_send_ctrl->Add_List(db_name,0);
		//-------------------------------
	}
	//-------------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S16Fy::Recv__F19(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E40_CTRL *p_e40_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E40();

	CString db_name;
	CString var_data;

	//-------------------------------
	CString pjobid;
	int pjob_sts;

	int index = 0;

	while(p_e40_ctrl->Get_PJOBID_And_STATUS(index,pjobid,pjob_sts) > 0)
	{
		index++;

		// PJOBID
		db_name.Format("-1-%1d-1",index);
		p_send_ctrl->Add_Ascii(db_name,pjobid);

		// PRSTATE
		db_name.Format("-1-%1d-2",index);
		p_send_ctrl->Add_U1(db_name,pjob_sts);
	}

	// LIST_LIMIT
	db_name = "-1";
	p_send_ctrl->Add_List(db_name,index);
	//-------------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S16Fy::Recv__F21(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E40_CTRL *p_e40_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E40();

	CString db_name;

	//-------------------------------
	int size = p_e40_ctrl->Get_PJOB_SPACE();

	// PRJOBSPACE
	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,size);
	//-------------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}

void CMsg_S16Fy::Recv__F25(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_FA_300mm__E40_CTRL *p_e40_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E40();

	CString db_name;
	CString var_data;

	//----------------------------------------------------------------
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	if(p_e30_ctrl->Is_REMOTE() < 0)
	{
		//-------------------------------
		int err_code;
		CString err_text;

		err_code = ERROR_CODE__COMMAND_NOT_VALID_FOR_CURRENT_STATE;
		err_text = "Command not valid for current state";
		//-------------------------------

		//-------------------------------
		// ACKA
		db_name = "-1-2-1";
		p_send_ctrl->Add_Boolean(db_name,FALSE);

		// ERROR_LIMIT
		db_name = "-1-2-2";
		p_send_ctrl->Add_List(db_name,1);

		// ERRCODE
		db_name = "-1-2-2-1-1";
		p_send_ctrl->Add_U1(db_name,err_code);

		// ERRTEXT
		db_name = "-1-2-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
		//-------------------------------

		p_bridge_ctrl->pFA_DRV_CTRL->Send();

		FA__OK;
	}
	//----------------------------------------------------------------

	//-------------------------------
	int pr_limit;
	int i;
	int process_start;
	CString pjobid;

	int error_count = 0;
	int err_code;
	CString err_text;

	//-------------------------------
	// PR_LIMIT
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);
	
	pr_limit = atoi(var_data);

	// PROCESS-START
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	var_data.MakeUpper();

	if(var_data == "FF")	process_start = 1;
	else					process_start = atoi(var_data);

	for(i=0;i<pr_limit;i++)
	{
		// PRJOBID
		db_name.Format("-1-1-%1d",i+1);
		p_recv_ctrl->Get_Data(db_name,pjobid);

		//-------------------------------
		int flag = p_e40_ctrl->Change_PROCESS_START(pjobid,process_start);

		if(flag < 0)
		{
			error_count = 1;
		}
		//-------------------------------

		//-------------------------------
		p_e40_ctrl->Get_PRJob_Error(err_code,err_text);

		// PRJOBID
		db_name.Format("-1-1-%1d",i+1);
		p_send_ctrl->Add_Ascii(db_name,pjobid);

		// ERRCODE
		db_name.Format("-1-2-2-%1d-1",i+1);
		p_send_ctrl->Add_U1(db_name,err_code);

		// ERRTEXT
		db_name.Format("-1-2-2-%1d-2",i+1);
		p_send_ctrl->Add_Ascii(db_name,err_text);
		//-------------------------------
	}

	// PR_LIMIT
	db_name = "-1-1";
	p_send_ctrl->Add_List(db_name,pr_limit);

	if(error_count > 0)
	{
		//-------------------------------
		// ACKA
		db_name = "-1-2-1";
		p_send_ctrl->Add_Boolean(db_name,FALSE);

		// ERROR_LIMIT
		db_name = "-1-2-2";
		p_send_ctrl->Add_List(db_name,pr_limit);
		//-------------------------------
	}
	else
	{
		//-------------------------------
		// ACKA
		db_name = "-1-2-1";
		p_send_ctrl->Add_Boolean(db_name,TRUE);

		// ERROR_LIMIT
		db_name = "-1-2-2";
		p_send_ctrl->Add_List(db_name,0);
		//-------------------------------
	}
	//-------------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S16Fy::Recv__F27(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_FA_300mm_CTRL *p_300mm_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL;

	CI_FA_300mm__E94_CTRL *p_e94_ctrl 
		= p_300mm_ctrl->Get_E94();

	CString db_name;
	CString var_data;

	//----------------------------------------------------------------
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	if(p_e30_ctrl->Is_REMOTE() < 0)
	{
		//-------------------------------
		int err_code;
		CString err_text;

		err_code = ERROR_CODE__COMMAND_NOT_VALID_FOR_CURRENT_STATE;
		err_text = "Command not valid for current state";
		//-------------------------------

		//-------------------------------
		// ACKA
		db_name = "-1-1";
		p_send_ctrl->Add_Boolean(db_name,FALSE);

		// LIST_LIMIT
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,2);

		// ERRCODE
		db_name = "-1-2-1";
		p_send_ctrl->Add_U2(db_name,err_code);

		// ERRTEXT
		db_name = "-1-2-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
		//-------------------------------

		p_bridge_ctrl->pFA_DRV_CTRL->Send();

		FA__OK;
	}
	//----------------------------------------------------------------

	//-------------------------------
	CString cjobid;
	int cjob_cmmd;
	int list_limit;
	int remove_flag = 0;

	int err_code = 0;
	CString err_text;

	//-------------------------------
	// CTLJOBID
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,cjobid);
	
	// CTLJOBCMD
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	cjob_cmmd = atoi(var_data);

	// LIST_LIMIT
	db_name = "-1-3";
	p_recv_ctrl->Get_Data(db_name,var_data);

	list_limit = atoi(var_data);
	if(list_limit == 2)
	{
		// CPVAL
		db_name = "-1-3-2";
		p_recv_ctrl->Get_Data(db_name,var_data);

		remove_flag = atoi(var_data);
	}
	else if(list_limit != 0)
	{
		err_code = ERROR_CODE__INSUFFICIENT_PARAMETERS_SPECIFIED;

		p_300mm_ctrl->Get_Error_Text(err_code,err_text);
	}
	//-------------------------------
	
	//-------------------------------
	if(err_code == 0)
	{
		switch(cjob_cmmd)
		{
			case 1:		// CJStart
				if(p_e94_ctrl->Start_CJob(cjobid) < 0)
				{
					p_e94_ctrl->Get_CJob_Error(err_code,err_text);
				}
				break;

			case 2:		// CJPause
				if(p_e94_ctrl->Pause_CJob(cjobid) < 0)
				{
					p_e94_ctrl->Get_CJob_Error(err_code,err_text);
				}
				break;

			case 3:		// CJResume
				if(p_e94_ctrl->Resume_CJob(cjobid) < 0)
				{
					p_e94_ctrl->Get_CJob_Error(err_code,err_text);
				}
				break;

			case 4:		// CJCancel
				if(p_e94_ctrl->Cancel_CJob(cjobid,remove_flag) < 0)
				{
					p_e94_ctrl->Get_CJob_Error(err_code,err_text);
				}
				break;

			case 5:		// CJDeselect
				if(p_e94_ctrl->Deselect_CJob(cjobid) < 0)
				{
					p_e94_ctrl->Get_CJob_Error(err_code,err_text);
				}
				break;

			case 6:		// CJStop
				if(p_e94_ctrl->Stop_CJob(cjobid,remove_flag) < 0)
				{
					p_e94_ctrl->Get_CJob_Error(err_code,err_text);
				}
				break;

			case 7:		// CJAbort
				if(p_e94_ctrl->Abort_CJob(cjobid,remove_flag) < 0)
				{
					p_e94_ctrl->Get_CJob_Error(err_code,err_text);
				}
				break;

			case 8:		// CJHOQ  
				if(p_e94_ctrl->HOQ_CJob(cjobid) < 0)
				{
					p_e94_ctrl->Get_CJob_Error(err_code,err_text);
				}
				break;

			default:	// Unknown Command
				{
					err_code = ERROR_CODE__PARAMETER_IMPROPERLY_SPECIFIED;

					p_300mm_ctrl->Get_Error_Text(err_code,err_text);
				}
				break;
		}
	}
	//-------------------------------

	//-------------------------------
	if(err_code == 0)
	{
		// ACKA
		db_name = "-1-1";
		p_send_ctrl->Add_Boolean(db_name,TRUE);

		// LIST_LIMIT
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,0);
	}
	else if(err_code > 0)
	{
		// ACKA
		db_name = "-1-1";
		p_send_ctrl->Add_Boolean(db_name,FALSE);

		// LIST_LIMIT
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,2);

		// ERRCODE
		db_name = "-1-2-1";
		p_send_ctrl->Add_U2(db_name,err_code);

		// ERRTEXT
		db_name = "-1-2-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
	}
	//-------------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S16Fy::Recv__F29(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CString db_name;
	CString var_data;

	//-------------------------------
	
	//-------------------------------
	db_name.Format("-1");
	p_send_ctrl->Add_Boolean(db_name,TRUE);

	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
