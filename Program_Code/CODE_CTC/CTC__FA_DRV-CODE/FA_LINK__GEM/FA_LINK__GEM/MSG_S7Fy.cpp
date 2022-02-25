#include "StdAFx.h"
#include "Macro_FNC.h"

#include "MSG_S7Fy.h"
CMsg_S7Fy mMSG_S7Fy;


//----------------------------------------------------------------------------
CMsg_S7Fy::CMsg_S7Fy()
{
	iSx = 7;
}

void CMsg_S7Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	switch(p_bridge_ctrl->iFy)
	{
		case 27:	Send__F27(p_bridge_ctrl);		return;
	}
}

void CMsg_S7Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	switch(p_bridge_ctrl->iFy)
	{
		case 17:    Recv__F17(p_bridge_ctrl);		return;
		case 19:
			switch(p_bridge_ctrl->iType)
			{
				case 0:
					Recv__F19_0(p_bridge_ctrl);		
					return;
			}
			return;
		
		case 23:	Recv__F23(p_bridge_ctrl);		return;
		case 25:    Recv__F25(p_bridge_ctrl);		return;
	}
}


//----------------------------------------------------------------------------
void CMsg_S7Fy::Send__F27(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_VARIABLE_CTRL *p_variable_ctrl
		= p_bridge_ctrl->pRES_VARIABLE_CTRL;

	//----------------------------------------------------------
	CString	db_name;

	CString main_name;
	CString sub_name;
	CString var_data;

	CString str__ppid;
	int     i_err_list = 0;
	CString str__ack7a;
	CString str__seqnum;
	CString str__errw7;

	// ...
	{
		// PPID
		db_name = "-1-1";
		p_send_ctrl->Add_Ascii(db_name,str__ppid);

		// ERROR_LIST
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,i_err_list);
			
		// ACKC7A
		db_name = "-1-2-1-1";
		p_send_ctrl->Add_Ascii(db_name,str__ack7a);

		// SEQNUM
		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,str__seqnum);

		// ERRW7
		db_name = "-1-2-1-3";
		p_send_ctrl->Add_Ascii(db_name,str__errw7);
	}

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//----------------------------------------------------------

	//----------------------------------------------------------
	if(p_bridge_ctrl->iReply < 0)						FA__OK;
	if(p_bridge_ctrl->pFA_DRV_CTRL->Is_Recv() < 0)		FA__ERROR;
	//----------------------------------------------------------

	FA__OK;
}


//----------------------------------------------------------------------------
void CMsg_S7Fy::Recv__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	SCX__FILE_RCP_CTRL file_rcp_ctrl;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl = p_bridge_ctrl->pMSG_RECV_CTRL;
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl = p_bridge_ctrl->pMSG_SEND_CTRL;

	//-------------------------------
	CString db_name;
	CString var_data;

	//-------------------------------
	int seq_id = 2;
	int ackc7 = 0;
	int limit;
	int	i;

	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,var_data);
	limit = atoi(var_data);

	if(limit < 1)
	{

	}
	else
	{
		for(i=0;i<limit;i++)
		{
			db_name.Format("-1-%1d",i+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			var_data = Macro__Change_1st_UnderBar(var_data);

			if(file_rcp_ctrl->Delete__REMOTE_FILE(seq_id,"",var_data,"rcp") < 0)
			{
				ackc7 = 4;
			}
		}
	}
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//------------------------------------------------------------------------

	FA__OK
}
void CMsg_S7Fy::Recv__F19_0(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl = p_bridge_ctrl->pMSG_RECV_CTRL;

	// PM_ID
	int seq_id = 2;

	CString	db_name;
	CStringArray l_file_name;
	CString file_name;

	//----------------------------------------------------------
	SCX__FILE_RCP_INFO file_rcp_info;
	file_rcp_info->Search__REMOTE_FILE_LIST(seq_id,"#DIR_FILE","rcp",l_file_name);

	//----------------------------------------------------------
	int list_limit = l_file_name.GetSize();
	int i;

	// 1.<L,  n
	db_name = "-1";
	p_bridge_ctrl->pMSG_SEND_CTRL->Add_List(db_name,list_limit);

	for(i=0;i<list_limit;i++)
	{
		//	  n.<A   $ASCII	
		db_name.Format("-1-%1d",i+1);
		file_name = l_file_name[i];

		file_name.Replace('\\','_');
		p_bridge_ctrl->pMSG_SEND_CTRL->Add_Ascii(db_name,file_name);
	}
		
	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}

void CMsg_S7Fy::Recv__F23(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	// SCX__FILE_ROUTE_CTRL xFile_Route_Ctrl;
	SCX__FILE_RCP_CTRL   xFile_Rcp_Ctrl;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl = p_bridge_ctrl->pMSG_RECV_CTRL;
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl = p_bridge_ctrl->pMSG_SEND_CTRL;
	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl  = p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	CString		 db_name;
	int			 type;
	CString		 first_data;
	CStringArray data_list;

	CString ppid;
	int pm_limit;
	int i;

	int err_flag = -1;

	//-----------------------------------------------
	// PPID
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

	ppid = first_data;
	//-----------------------------------------------

	//-----------------------------------------------
  	// MDLN
	// db_name = "-1-2";
  	
	// SOFTREV
	// db_name = "-1-3";
	//-----------------------------------------------
	
	//-----------------------------------------------
	CString		rte_path;
	CString		dir_route;
	CI_SEQ_INFO *p_seq_info	= p_bridge_ctrl->pRES_SEQ_INFO;

	p_seq_info->Get__Dir_Route(dir_route);

	rte_path  = dir_route;
	rte_path += ppid;
	rte_path += ".rte";
	//-----------------------------------------------

	/*
	if(xFile_Route_Ctrl->Create__FILE(rte_path) < 0)
	{
		err_flag = 1;
		goto fnc_end;
	}
	*/

	//-----------------------------------------------
	// PM_LIST
	db_name = "-1-4";
	p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
	
	pm_limit = atoi(first_data);

	for(i=0;i<pm_limit;i++)
	{
		int		pm_id;
		CString pm_recipe;

		//-----------------------------------------------
		// ROUTE RECIPE CREATE 

		// PM_ID
		db_name.Format("-1-4-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

		pm_id = atoi(first_data);

		// PM_RECIPE
		db_name.Format("-1-4-%1d-2",i+1);
		p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
			
		pm_recipe = first_data;
		pm_recipe = Macro__Change_1st_UnderBar(pm_recipe);
			
		// xFile_Route_Ctrl->Add__PATH(pm_id,pm_recipe);
		//-----------------------------------------------

		//-----------------------------------------------
		// PM RECIPE CREATE

		if(p_ppbody_ctrl->Set_Current_PM_ID(pm_id) > 0)
		{
			xFile_Rcp_Ctrl->Create__REMOTE_FILE();

			//-----------------------------------------------
			CString ppbody_name;
			CString ppbody_unit;
			CString ppbody_range;
			CString channel_name;
			CString channel_type;
			CString channel_data;
			CString fmt_unit;
			int		fmt_size;

			int cfg_para_limit;
			int step_limit;
			int k;

			//-----------------------------------------------
			// CONFIG PARAMETER

			// CONFIG_LIMIT
			db_name.Format("-1-4-%1d-4",i+1);
			p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

			cfg_para_limit = atoi(first_data);

			if(cfg_para_limit > 0)
			{
				xFile_Rcp_Ctrl->Go__NEXT_STEP();
			}

			if(cfg_para_limit != p_ppbody_ctrl->Get_CFG_PARAMETER_SIZE())
			{
				err_flag = 2;
				goto fnc_end;
			}

			for(k=0;k<cfg_para_limit;k++)
			{
				// CONFIG PROCESS PARAMETER
				db_name.Format("-1-4-%1d-4-%1d",i+1,k+1);
				p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

				if(p_ppbody_ctrl->Check_CFG_DATA(k,first_data) < 0)
				{
					err_flag = 3;
					goto fnc_end;
				}

				if(p_ppbody_ctrl->Get_CFG_PARAMETER_From_INDEX(k,
															   ppbody_name,
															   ppbody_unit,
															   ppbody_range,
															   channel_name,
															   channel_type,
															   fmt_unit,
															   fmt_size) < 0)
				{
					err_flag = 4;
					goto fnc_end;
				}

				channel_data = first_data;
				xFile_Rcp_Ctrl->Add__ITEM(channel_name,channel_type,channel_data);
			}

			//-----------------------------------------------
			// PROCESS PARAMETER

			// STEP_LIMIT
			db_name.Format("-1-4-%1d-3",i+1);
			p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

			step_limit = atoi(first_data);

			for(k=0;k<step_limit;k++)
			{
				if(k == 0)
				{
					if(cfg_para_limit < 1)
					{
						xFile_Rcp_Ctrl->Go__NEXT_STEP();
					}
				}
				else
				{
					xFile_Rcp_Ctrl->Go__NEXT_STEP();
				}

				int item_limit;
				int t;

				// ITEM-LIMIT
				db_name.Format("-1-4-%1d-3-%1d",i+1,k+1);
				p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

				item_limit = atoi(first_data);

				if(item_limit != p_ppbody_ctrl->Get_STEP_PARAMETER_SIZE())
				{
					err_flag = 5;
					goto fnc_end; 
				}

				for(t=0;t<item_limit;t++)
				{
					// ITEM PARAMETER
					db_name.Format("-1-4-%1d-3-%1d-%1d",i+1,k+1,t+1);
					p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

					if(p_ppbody_ctrl->Check_STEP_DATA(t,first_data) < 0)
					{
						err_flag = 6;
						goto fnc_end;
					}

					if(p_ppbody_ctrl->Get_STEP_PARAMETER_From_INDEX(t,
																    ppbody_name,
																    ppbody_unit,
																	ppbody_range,
																	channel_name,
																	channel_type,
																	fmt_unit,
																	fmt_size) < 0)
					{
						err_flag = 7;
						goto fnc_end;
					}
						
					channel_data = first_data;
					xFile_Rcp_Ctrl->Add__ITEM(channel_name,channel_type,channel_data);
				}
			}

			//-----------------------------------------------
			if(xFile_Rcp_Ctrl->Save__REMOTE_FILE(pm_id+1,
												 "",
												 pm_recipe,
												 "rcp") < 0)
			{
				err_flag = 8;
				goto fnc_end;
			}

			xFile_Rcp_Ctrl->Close__REMOTE_FILE();
			//-----------------------------------------------
		}
	}

	//-----------------------------------------------
	if(pm_limit > 0)
	{
		/*
		xFile_Route_Ctrl->End__STEP();
		if(xFile_Route_Ctrl->Save__FILE() < 0)
		{
			err_flag = 9;
			goto fnc_end;
		}
		*/
	}
	//-----------------------------------------------
	//------------------------------------------------------------------------

fnc_end:
	xFile_Rcp_Ctrl->Close__FILE();
	// xFile_Route_Ctrl->Close__FILE();

	//------------------------------------------------------------------------
	//-----------------------------------------------
	int ackc7 = 0;

	if(err_flag > 0)	ackc7 = err_flag;

	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,ackc7);
	//-----------------------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//------------------------------------------------------------------------

	FA__OK
}
void CMsg_S7Fy::Recv__F25(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	SCX__FILE_RCP_INFO xFile_Rcp_Info;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl   = p_bridge_ctrl->pMSG_RECV_CTRL;
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl   = p_bridge_ctrl->pMSG_SEND_CTRL;
	CI_FA_DB__PPBODY_CTRL    *p_ppbody_ctrl = p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	CString	db_name;
	int		type;
	CString first_data;
	CStringArray data_list;

	//.....
	int pmc_id = 1;
	CString pmc_recipe;
	CString pmc_data;

	// PM_RECIPE
	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

	pmc_recipe = first_data;
	//------------------------------------------------------------

	//------------------------------------------------------------
	// PM_ID
	db_name = "-1-1";
	p_send_ctrl->Add_U1(db_name,pmc_id);

	// PM_RECIPE
	db_name = "-1-2";
	p_send_ctrl->Add_Ascii(db_name,pmc_recipe);

	//.....
	{
		pmc_recipe = Macro__Change_1st_UnderBar(pmc_recipe);

		//.....
		p_ppbody_ctrl->Set_Current_PM_ID(pmc_id);
			
		xFile_Rcp_Info->Clear__MEM();
		xFile_Rcp_Info->Upload__REMOTE_FILE(pmc_id+1,
											"",
											pmc_recipe,
											"rcp");

		//.....
		// STEP_LIMIT
		CString item_unit;
		CString item_range;
		CString ch_name;
		CString ch_type;
		CString fmt_unit;
		int     fmt_size;

		int rcp_step_size = xFile_Rcp_Info->Get__STEP_SIZE();
		int k;

		db_name = "-1-3";
		p_send_ctrl->Add_List(db_name,rcp_step_size);

		for(k=0;k<rcp_step_size;k++)
		{
			// ITEM_LIMIT
			int rcp_item_size;
			int t;

			// STEP PARAMETER
			rcp_item_size = p_ppbody_ctrl->Get_STEP_PARAMETER_SIZE();

			db_name.Format("-1-3-%1d",k+1);
			p_send_ctrl->Add_List(db_name,rcp_item_size);

			for(t=0;t<rcp_item_size;t++)
			{
				// STEP_PPARM
				p_ppbody_ctrl->Get_STEP_PARAMETER_From_INDEX(t,
														     db_name,item_unit,item_range,
														     ch_name,ch_type,
														     fmt_unit,fmt_size);
					
				if(xFile_Rcp_Info->Get__ITEM_DATA(k,ch_name,pmc_data) < 0)
				{
					pmc_data = "Unknown Data";
				}
					
				db_name.Format("-1-3-%1d-%1d",k+1,t+1);
				p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,pmc_data);
			}
		}

		// CONFIG_LIMIT
		if(rcp_step_size > 0)
		{
			int cfg_item_size;
			int tt;
			
			cfg_item_size = p_ppbody_ctrl->Get_CFG_PARAMETER_SIZE();

			db_name = "-1-4";
			p_send_ctrl->Add_List(db_name,cfg_item_size);

			for(tt=0;tt<cfg_item_size;tt++)
			{
				// CFG_PPARM
				p_ppbody_ctrl->Get_CFG_PARAMETER_From_INDEX(tt,
														    db_name,item_unit,item_range,
														    ch_name,ch_type,
														    fmt_unit,fmt_size);

				if(xFile_Rcp_Info->Get__ITEM_DATA(0,ch_name,pmc_data) < 0)
				{
					pmc_data = "Unknown Data";
				}
					
				db_name.Format("-1-4-%1d",tt+1);
				p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,pmc_data);
			}
		}
	}

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//------------------------------------------------------------------------

	FA__OK
}
