#include "StdAFx.h"

#include "MSG_S07Fy.h"
CMsg_S07Fy mMSG_S07Fy;


//----------------------------------------------------------------------------
CMsg_S07Fy::CMsg_S07Fy()
{
	iSx = 7;
}

void CMsg_S07Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)		return;

	/*
	switch(p_bridge_ctrl->iFy)
	{
	}
	*/
}

void CMsg_S07Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)		return;

	switch(p_bridge_ctrl->iFy)
	{
		case 1:		Recv__F1(p_bridge_ctrl);		return;
		
		case 3:     Recv__F3(p_bridge_ctrl);		return;
		case 5:     Recv__F5(p_bridge_ctrl);		return;
		
		case 17:    Recv__F17(p_bridge_ctrl);		return;

		case 19:
			switch(p_bridge_ctrl->iType)
			{
				case 0:
					Recv__F19_0(p_bridge_ctrl);		
					return;

				case 1:
					Recv__F19_1(p_bridge_ctrl);
					return;
			}
			return;
		
		case 23:	Recv__F23(p_bridge_ctrl);		return;
		case 25:    Recv__F25(p_bridge_ctrl);		return;

		case 65:    Recv__F65(p_bridge_ctrl);		return;

		case 83:	Recv__F83(p_bridge_ctrl);		return;
		case 85:    Recv__F85(p_bridge_ctrl);		return;

		case 93:	Recv__F93(p_bridge_ctrl);		return;
		case 95:    Recv__F95(p_bridge_ctrl);		return;

		case 97:    Recv__F97(p_bridge_ctrl);		return;
		case 99:    Recv__F99(p_bridge_ctrl);		return;
	}
}


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void CMsg_S07Fy::Recv__F1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//-----------------------------
	CString db_name;

	db_name = "-1";
	p_bridge_ctrl->pMSG_SEND_CTRL->Add_Binary(db_name,0);

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}
void CMsg_S07Fy::Recv__F3(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	SCX__FILE_ROUTE_CTRL xFile_Route_Ctrl;
	SCX__FILE_RCP_CTRL   xFile_Rcp_Ctrl;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl 
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();
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
	CString		rte_path;
	CString		dir_route;
	CI_SEQ_INFO *p_seq_info	= p_bridge_ctrl->pRES_SEQ_INFO;

	p_seq_info->Get__Dir_Route(dir_route);

	rte_path  = dir_route;
	rte_path += ppid;
	rte_path += ".rte";
	//-----------------------------------------------

	if(xFile_Route_Ctrl->Create__FILE(rte_path) < 0)
	{
		err_flag = 1;
		goto fnc_end;
	}

	//-----------------------------------------------
	// PM_LIST
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
	
	pm_limit = atoi(first_data);

	for(i=0;i<pm_limit;i++)
	{
		int		pm_id;
		CString pm_recipe;

		//-----------------------------------------------
		// ROUTE RECIPE CREATE 

		// PM_ID
		db_name.Format("-1-2-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

		pm_id = atoi(first_data);

		// PM_RECIPE
		db_name.Format("-1-2-%1d-2",i+1);
		p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
			
		pm_recipe = first_data;
			

		xFile_Route_Ctrl->Add__PATH(pm_id,pm_recipe);
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
			db_name.Format("-1-2-%1d-4",i+1);
			p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

			cfg_para_limit = atoi(first_data);

			if(cfg_para_limit > 0)
			{
				xFile_Rcp_Ctrl->Go__NEXT_STEP();
			}

			if(cfg_para_limit != p_ppbody_ctrl->Get_CFG_PARAMETER_SIZE())
			{
				err_flag = 1;
				goto fnc_end;
			}

			for(k=0;k<cfg_para_limit;k++)
			{
				// CONFIG PROCESS PARAMETER
				db_name.Format("-1-2-%1d-4-%1d",i+1,k+1);
				p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

				if(p_ppbody_ctrl->Check_CFG_DATA(k,first_data) < 0)
				{
					err_flag = 1;
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
					err_flag = 1;
					goto fnc_end;
				}

				channel_data = first_data;
				xFile_Rcp_Ctrl->Add__ITEM(channel_name,channel_type,channel_data);
			}

			//-----------------------------------------------
			// PROCESS PARAMETER

			// STEP_LIMIT
			db_name.Format("-1-2-%1d-3",i+1);
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
				db_name.Format("-1-2-%1d-3-%1d",i+1,k+1);
				p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

				item_limit = atoi(first_data);

				if(item_limit != p_ppbody_ctrl->Get_STEP_PARAMETER_SIZE())
				{
					err_flag = 1;
					goto fnc_end; 
				}

				for(t=0;t<item_limit;t++)
				{
					// ITEM PARAMETER
					db_name.Format("-1-2-%1d-3-%1d-%1d",i+1,k+1,t+1);
					p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

					if(p_ppbody_ctrl->Check_STEP_DATA(t,first_data) < 0)
					{
						err_flag = 1;
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
						err_flag = 1;
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
				err_flag = 1;
				goto fnc_end;
			}

			xFile_Rcp_Ctrl->Close__REMOTE_FILE();
			//-----------------------------------------------
		}
	}

	//-----------------------------------------------
	if(pm_limit > 0)
	{
		xFile_Route_Ctrl->End__STEP();
		if(xFile_Route_Ctrl->Save__FILE() < 0)
		{
			err_flag = 1;
			goto fnc_end;
		}
	}
	//-----------------------------------------------
	//------------------------------------------------------------------------

fnc_end:
	xFile_Rcp_Ctrl->Close__FILE();
	xFile_Route_Ctrl->Close__FILE();

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
void CMsg_S07Fy::Recv__F5(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	SCX__FILE_ROUTE_INFO xFile_Route_Info;
	SCX__FILE_RCP_INFO   xFile_Rcp_Info;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl 
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	CString		 db_name;
	int			 type;
	CString		 first_data;
	CStringArray data_list;

	//------------------------------------------------------------
	CString ppid;

	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
	ppid = first_data;
	//------------------------------------------------------------

	//------------------------------------------------------------
	// PPID
	db_name = "-1-1";
	p_send_ctrl->Add_Ascii(db_name,ppid);

	CString dir_route;
	CString ppid_path;

	p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Route(dir_route);

	ppid_path  = dir_route;
	ppid_path += ppid;
	ppid_path += ".rte";

	if(xFile_Route_Info->Check__FILE(ppid_path) > 0)
	{
		// PPID_INFO
		db_name = "-1";
		p_send_ctrl->Add_List(db_name,2);

		xFile_Route_Info->Clear__MEM();
		xFile_Route_Info->Upload__FILE(ppid_path);


		int rte_step_size;
		int rte_path_size;
		int i;
		
		rte_step_size = xFile_Route_Info->Get__ROUTE_SERIAL_STEP_SIZE();
		if(rte_step_size < 0)	rte_step_size = 0;

		rte_path_size = xFile_Route_Info->Get__ROUTE_PARALLEL_PATH_SIZE(0);
		if(rte_path_size < 0)	rte_path_size = 0;
		

		// PM_LIST
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,rte_path_size);


		CDS__ROUTE_PMC_INFO pmc_info;
		int	     pmc_id;
		CString  unit_type;
		int	     unit_size;
		CString	 pmc_data;

		for(i=0;i<rte_path_size;i++)
		{
			xFile_Route_Info->Get__PMC_INFO(0,i,pmc_info);

			pmc_id = pmc_info.iMODULE_ID;

			//---------------------
			p_ppbody_ctrl->Set_Current_PM_ID(pmc_id);

			xFile_Rcp_Info->Clear__MEM();
			xFile_Rcp_Info->Upload__REMOTE_FILE(pmc_id + 1,
												"",
												pmc_info.sMODULE_RECIPE,
												"rcp");
			//---------------------

			// PM_ID
			p_ppbody_ctrl->Get_FORMAT_From_PM_ID(unit_type,unit_size);
			pmc_data.Format("%1d",pmc_info.iMODULE_ID);

			db_name.Format("-1-2-%1d-1",i+1);
			p_send_ctrl->Add_Virtual(db_name,unit_type,unit_size,pmc_data);

			// PM_RECIPE
			p_ppbody_ctrl->Get_FORMAT_From_PM_RECIPE(unit_type,unit_size);
			pmc_data = pmc_info.sMODULE_RECIPE;

			db_name.Format("-1-2-%1d-2",i+1);
			p_send_ctrl->Add_Virtual(db_name,unit_type,unit_size,pmc_data);

			// STEP_LIMIT
			CString item_unit;
			CString item_range;
			CString ch_name;
			CString ch_type;
			CString fmt_unit;
			int     fmt_size;
			int     rcp_step_size = xFile_Rcp_Info->Get__STEP_SIZE();
			int     k;

			db_name.Format("-1-2-%1d-3",i+1);
			p_send_ctrl->Add_List(db_name,rcp_step_size);

			for(k=0;k<rcp_step_size;k++)
			{
				// ITEM_LIMIT
				int rcp_item_size;
				int t;

				// STEP PARAMETER
				rcp_item_size = p_ppbody_ctrl->Get_STEP_PARAMETER_SIZE();

				db_name.Format("-1-2-%1d-3-%1d",i+1,k+1);
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
					
					db_name.Format("-1-2-%1d-3-%1d-%1d",i+1,k+1,t+1);
					p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,pmc_data);
				}
			}

			// CONFIG_LIMIT
			if(rcp_step_size > 0)
			{
				int cfg_item_size;
				int tt;
			
				cfg_item_size = p_ppbody_ctrl->Get_CFG_PARAMETER_SIZE();

				db_name.Format("-1-2-%1d-4",i+1);
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
					
					db_name.Format("-1-2-%1d-4-%1d",i+1,tt+1);
					p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,pmc_data);
				}
			}
		}
	}
	else
	{
		// PPID_INFO
		db_name = "-1";
		p_send_ctrl->Add_List(db_name,0);
	}


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//------------------------------------------------------------------------

	FA__OK
}
void CMsg_S07Fy::Recv__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	SCX__FILE_ROUTE_CTRL xFile_Route_Ctrl;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl 
		= p_bridge_ctrl->pMSG_SEND_CTRL;
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	CString db_name;
	CString var_data;

	CString rte_path;
	CString dir_route;

	p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Route(dir_route);

	//-------------------------------
	int	i;
	int limit;
	int ackc7 = 0;

	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,var_data);
	limit = atoi(var_data);

	if(limit < 1)
	{
		xFile_Route_Ctrl->Delete__ALL_FILE(dir_route);
	}
	else
	{
		for(i=0;i<limit;i++)
		{
			db_name.Format("-1-%1d",i+1);
			p_recv_ctrl->Get_Data(db_name,var_data);


			rte_path  = dir_route;
			rte_path += var_data;
			rte_path += ".rte";

			if(xFile_Route_Ctrl->Delete__FILE(rte_path) < 0)
			{
				ackc7 = 4;
			}
		}
	}
	//-------------------------------

	// ACKC7
	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,ackc7);
	//-------------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//------------------------------------------------------------------------

	FA__OK
}

void CMsg_S07Fy::Recv__F19_0(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CStringArray file_list;
	CString		 dir_route;

	CI_SEQ_INFO *p_seq_info	= p_bridge_ctrl->pRES_SEQ_INFO;

	p_seq_info->Get__Dir_Route(dir_route);
	p_seq_info->Search_File(dir_route,"rte",file_list);
	//----------------------------------------------------------

	//----------------------------------------------------------
	//-----------------------------
	CString	db_name;
	CString ascii;
	int i;
	int list_limit = file_list.GetSize();

	// 1.<L,  n
	db_name = "-1";
	p_bridge_ctrl->pMSG_SEND_CTRL->Add_List(db_name,list_limit);

	for(i=0;i<list_limit;i++)
	{
		//	  n.<A   $ASCII	
		db_name.Format("-1-%1d",i+1);
		ascii = file_list[i];
		p_bridge_ctrl->pMSG_SEND_CTRL->Add_Ascii(db_name,ascii);
	}
		
	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}
void CMsg_S07Fy::Recv__F19_1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	int seq_id;
	CStringArray l_file_name;

	//.....
	CString	db_name;
	int		type;
	CString first_data;
	CStringArray data_list;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	// PM_ID
	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
	seq_id = atoi(first_data) + 1;

	//.....
	{
		SCX__FILE_RCP_INFO file_rcp_info;

		file_rcp_info->Search__REMOTE_FILE_LIST(seq_id,"#DIR_FILE","rcp",l_file_name);
	}

	//----------------------------------------------------------
	//-----------------------------
	CString file_name;

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

		p_bridge_ctrl->pMSG_SEND_CTRL->Add_Ascii(db_name,file_name);
	}
		
	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}

void CMsg_S07Fy::Recv__F23(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	SCX__FILE_ROUTE_CTRL xFile_Route_Ctrl;
	SCX__FILE_RCP_CTRL   xFile_Rcp_Ctrl;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl 
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();
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

	if(xFile_Route_Ctrl->Create__FILE(rte_path) < 0)
	{
		err_flag = 1;
		goto fnc_end;
	}

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
			

		xFile_Route_Ctrl->Add__PATH(pm_id,pm_recipe);
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
		xFile_Route_Ctrl->End__STEP();
		if(xFile_Route_Ctrl->Save__FILE() < 0)
		{
			err_flag = 9;
			goto fnc_end;
		}
	}
	//-----------------------------------------------
	//------------------------------------------------------------------------

fnc_end:
	xFile_Rcp_Ctrl->Close__FILE();
	xFile_Route_Ctrl->Close__FILE();

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
void CMsg_S07Fy::Recv__F25(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	SCX__FILE_ROUTE_INFO xFile_Route_Info;
	SCX__FILE_RCP_INFO   xFile_Rcp_Info;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl 
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	CString		 db_name;
	int			 type;
	CString		 first_data;
	CStringArray data_list;

	//------------------------------------------------------------
	CString ppid;

	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
	ppid = first_data;
	//------------------------------------------------------------

	//------------------------------------------------------------
	// PPID
	db_name = "-1-1";
	p_send_ctrl->Add_Ascii(db_name,ppid);

	// MDLN
	//db_name = "-1-2";

	// SOFTREV
	//db_name = "-1-3";


	CString dir_route;
	CString ppid_path;

	p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Route(dir_route);

	ppid_path  = dir_route;
	ppid_path += ppid;
	ppid_path += ".rte";

	if(xFile_Route_Info->Check__FILE(ppid_path) > 0)
	{
		// PPID_INFO
		db_name = "-1";
		p_send_ctrl->Add_List(db_name,4);


		xFile_Route_Info->Clear__MEM();
		xFile_Route_Info->Upload__FILE(ppid_path);

		int i;
		int rte_step_size;
		int rte_path_size;
		
		rte_step_size = xFile_Route_Info->Get__ROUTE_SERIAL_STEP_SIZE();
		if(rte_step_size < 0)	rte_step_size = 0;

		rte_path_size = xFile_Route_Info->Get__ROUTE_PARALLEL_PATH_SIZE(0);
		if(rte_path_size < 0)	rte_path_size = 0;
		
		// PM_LIST
		db_name = "-1-4";
		p_send_ctrl->Add_List(db_name,rte_path_size);

		CDS__ROUTE_PMC_INFO pmc_info;
		int		 pmc_id;
		CString	 pmc_recipe;
		CString	 unit_type;
		int		 unit_size;
		CString	 pmc_data;

		for(i=0;i<rte_path_size;i++)
		{
			xFile_Route_Info->Get__PMC_INFO(0,i,pmc_info);

			pmc_id     = pmc_info.iMODULE_ID;
			pmc_recipe = pmc_info.sMODULE_RECIPE;

			//---------------------
			p_ppbody_ctrl->Set_Current_PM_ID(pmc_id);
			
			xFile_Rcp_Info->Clear__MEM();
			xFile_Rcp_Info->Upload__REMOTE_FILE(pmc_id+1,
												"",
												pmc_recipe,
												"rcp");
			//---------------------

			// PM_ID
			p_ppbody_ctrl->Get_FORMAT_From_PM_ID(unit_type,unit_size);
			pmc_data.Format("%1d",pmc_id);

			db_name.Format("-1-4-%1d-1",i+1);
			p_send_ctrl->Add_Virtual(db_name,unit_type,unit_size,pmc_data);

			// PM_RECIPE
			p_ppbody_ctrl->Get_FORMAT_From_PM_RECIPE(unit_type,unit_size);
			pmc_data = pmc_recipe;

			db_name.Format("-1-4-%1d-2",i+1);
			p_send_ctrl->Add_Virtual(db_name,unit_type,unit_size,pmc_data);

			// STEP_LIMIT
			CString item_unit;
			CString item_range;
			CString ch_name;
			CString ch_type;
			CString fmt_unit;
			int     fmt_size;
			int     rcp_step_size = xFile_Rcp_Info->Get__STEP_SIZE();
			int     k;

			db_name.Format("-1-4-%1d-3",i+1);
			p_send_ctrl->Add_List(db_name,rcp_step_size);

			for(k=0;k<rcp_step_size;k++)
			{
				// ITEM_LIMIT
				int rcp_item_size;
				int t;

				// STEP PARAMETER
				rcp_item_size = p_ppbody_ctrl->Get_STEP_PARAMETER_SIZE();

				db_name.Format("-1-4-%1d-3-%1d",i+1,k+1);
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
					
					db_name.Format("-1-4-%1d-3-%1d-%1d",i+1,k+1,t+1);
					p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,pmc_data);
				}
			}

			// CONFIG_LIMIT
			if(rcp_step_size > 0)
			{
				int cfg_item_size;
				int tt;
			
				cfg_item_size = p_ppbody_ctrl->Get_CFG_PARAMETER_SIZE();

				db_name.Format("-1-4-%1d-4",i+1);
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
					
					db_name.Format("-1-4-%1d-4-%1d",i+1,tt+1);
					p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,pmc_data);
				}
			}
		}
	}
	else
	{
		// PPID_INFO
		db_name = "-1";
		p_send_ctrl->Add_List(db_name,3);
	}

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//------------------------------------------------------------------------

	FA__OK
}

void CMsg_S07Fy::Recv__F65(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	SCX__FILE_ROUTE_INFO xFile_Route_Info;
	SCX__FILE_RCP_INFO   xFile_Rcp_Info;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl 
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	CString		 db_name;
	CString      db_data;
	int			 type;
	CString		 first_data;
	CStringArray data_list;

	//------------------------------------------------------------
	CString ppid_name;
	int ppid_mode;

	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
	ppid_name = first_data;
	//------------------------------------------------------------

	//------------------------------------------------------------
	// 1. MDLN

	// 2. SOFTREV

	// 3. PPID_TYPE
	{
		db_name = "-1-3";
		p_recv_ctrl->Get_Data(db_name,db_data);

		ppid_mode = atoi(db_data);
	}

	// 4. PPID
	{
		db_name = "-1-4";
		p_recv_ctrl->Get_Data(db_name,db_data);
		
		ppid_name = db_data;
	}

	//.....
	// EMPTY BODY
	{
		// 3. PPID_TYPE
		{
			db_name = "-1-3";
			p_send_ctrl->Add_U4(db_name,ppid_mode);
		}

		// 4. PPID_NAME
		{
			db_name = "-1-4";
			p_send_ctrl->Add_Ascii(db_name,ppid_name);
		}

		// 5. PPID_INFO
		{
			db_name = "-1-5";
			p_send_ctrl->Add_List(db_name,0);
		}
	}

	// ROUTE RECIPE
	if(ppid_mode == 0)
	{
		CString dir_route;
		CString ppid_path;

		p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Route(dir_route);
	
		ppid_path  = dir_route;
		ppid_path += ppid_name;
		ppid_path += ".rte";

		if(xFile_Route_Info->Check__FILE(ppid_path) > 0)
		{
			xFile_Route_Info->Clear__MEM();
			xFile_Route_Info->Upload__FILE(ppid_path);

			int rte_step_size;
			int rte_path_size;
			int i;
		
			rte_step_size = xFile_Route_Info->Get__ROUTE_SERIAL_STEP_SIZE();
			if(rte_step_size < 0)	rte_step_size = 0;
	
			rte_path_size = xFile_Route_Info->Get__ROUTE_PARALLEL_PATH_SIZE(0);
			if(rte_path_size < 0)	rte_path_size = 0;
		
			// 5. PPID_LIST
			{
				db_name = "-1-5";
				p_send_ctrl->Add_List(db_name,rte_path_size);
			}

			//
			CDS__ROUTE_PMC_INFO pmc_info;
			int		 pmc_id;
			CString	 pmc_recipe;
			CString	 unit_type;
			int		 unit_size;
			CString	 pmc_data;

			for(i=0;i<rte_path_size;i++)
			{
				xFile_Route_Info->Get__PMC_INFO(0,i,pmc_info);

				pmc_id     = pmc_info.iMODULE_ID;
				pmc_recipe = pmc_info.sMODULE_RECIPE;

				// L, 2
				{
					db_name.Format("-1-5-%1d",i+1);
					p_send_ctrl->Add_List(db_name,2);
				}

				// 1. PM_ID
				{
					db_name.Format("-1-5-%1d-1",i+1);
					db_data.Format("%1d",pmc_id);
					
					p_send_ctrl->Add_Ascii(db_name,db_data);
				}

				// 2. PM_RECIPE
				{
					db_name.Format("-1-5-%1d-2",i+1);
					db_data = pmc_recipe;
					
					p_send_ctrl->Add_Ascii(db_name,db_data);
				}
			}

			//.....
		}
	}
	else if(ppid_mode > 0)
	{
		//
		{		
			int		 pmc_id;
			CString	 pmc_recipe;
			CString	 unit_type;
			int		 unit_size;
			CString	 pmc_data;

			//.....
			pmc_id = ppid_mode;
			pmc_recipe = ppid_name;

			//.....
			p_ppbody_ctrl->Set_Current_PM_ID(pmc_id);
				
			xFile_Rcp_Info->Clear__MEM();
			xFile_Rcp_Info->Upload__REMOTE_FILE(pmc_id+1,
												"",
												pmc_recipe,
												"rcp");

			// STEP_LIMIT
			CString item_unit;
			CString item_range;
			CString ch_name;
			CString ch_type;
			CString fmt_unit;
			int     fmt_size;
				
			int rcp_step_size = xFile_Rcp_Info->Get__STEP_SIZE();
			int k;

			// 5. PPID_LIST
			if(rcp_step_size > 0)
			{
				db_name = "-1-5";
				p_send_ctrl->Add_List(db_name,rcp_step_size+1);
			}
			else
			{
				db_name = "-1-5";
				p_send_ctrl->Add_List(db_name,0);
			}

			for(k=0;k<rcp_step_size;k++)
			{
				// 5.1  <L,2
				{
					db_name.Format("-1-5-%1d",k+1);
					p_send_ctrl->Add_List(db_name,2);
				}

				// 5.1.1  <STEP_ID
				{
					db_name.Format("-1-5-%1d-1",k+1);
					db_data.Format("%1d",k+1);
					p_send_ctrl->Add_Ascii(db_name,db_data);
				}

				//.....
				int rcp_item_size;
				int t;

				// STEP PARAMETER
				rcp_item_size = p_ppbody_ctrl->Get_STEP_PARAMETER_SIZE();

				// 5.1.2  <ITEM_LIST
				{
					db_name.Format("-1-5-%1d-2",k+1);
					p_send_ctrl->Add_List(db_name,rcp_item_size);
				}
	
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
						
					db_name.Format("-1-5-%1d-2-%1d",k+1,t+1);
					p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,pmc_data);
				}
			}

			// CONFIG_LIMIT
			if(rcp_step_size > 0)
			{
				int list_id = rcp_step_size + 1;
				int cfg_item_size;
				int tt;
			
				cfg_item_size = p_ppbody_ctrl->Get_CFG_PARAMETER_SIZE();

				// 5.n  <L,2
				{
					db_name.Format("-1-5-%1d",list_id);
					p_send_ctrl->Add_List(db_name,2);
				}

				// 5.n.1  <STEP_ID
				{
					db_name.Format("-1-5-%1d-1",list_id);
					db_data = "0";
					p_send_ctrl->Add_Ascii(db_name,db_data);
				}

				db_name.Format("-1-5-%1d-2",list_id);
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
					
					db_name.Format("-1-5-%1d-2-%1d",list_id,tt+1);
					p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,pmc_data);
				}
			}
		}
	}

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//------------------------------------------------------------------------

	FA__OK
}

void CMsg_S07Fy::Recv__F83(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	SCX__FILE_ROUTE_CTRL xFile_Route_Ctrl;
	SCX__FILE_RCP_CTRL   xFile_Rcp_Ctrl;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl 
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	CString		 db_name;
	int			 type;
	CString		 first_data;
	CStringArray data_list;

	int	err_recipe;
	int err_pmc_list;
	int err_cfg_item_list;
	int err_step_list;
	int err_step_item_list;

	CString ppid;
	CString rte_path;
	int     i;
	int     pm_list_limit;
	CString dir_route;

	p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Route(dir_route);

	//-------------------------------
	// ACKC7
	int ackc7 = 0;

	db_name = "-1-1";
	p_send_ctrl->Add_Binary(db_name,ackc7);
	//-------------------------------

	//-------------------------------
	// PPID
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
	ppid = first_data;
	
	rte_path  = dir_route;
	rte_path += ppid;
	rte_path += ".rte";

	if(xFile_Route_Ctrl->Create__FILE(rte_path) > 0)
	{
		// PM_LIST
		db_name = "-1-4";
		p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
		pm_list_limit = atoi(first_data);

		int		pm_id;
		CString pm_recipe;

		err_pmc_list = 0;

		for(i=0;i<pm_list_limit;i++)
		{
			err_recipe = -1;

			//-----------------------------------------------
			// PM_ID
			db_name.Format("-1-4-%1d-1",i+1);
			p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

			pm_id = atoi(first_data);

			// PM_RECIPE
			db_name.Format("-1-4-%1d-2",i+1);
			p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

			pm_recipe = first_data;

			// ROUTE RECIPE 累己
			xFile_Route_Ctrl->Add__PATH(pm_id,pm_recipe);
			//-----------------------------------------------

			//-----------------------------------------------
			// PM RECIPE 累己

			if(p_ppbody_ctrl->Set_Current_PM_ID(pm_id) > 0)
			{
				xFile_Rcp_Ctrl->Create__REMOTE_FILE();

				//-----------------------------------------------
				CString ppbody_name;
				CString ppbody_unit;
				CString ppbody_range;

				CString cfg_pparm_name;
				CString cfg_pparm_data;

				CString pmc_data;
				CString step_pparm_name;
				CString step_pparm_data;

				CString channel_name;
				CString channel_type;
				CString channel_data;
				CString fmt_unit;
				int     fmt_size;
				int		ppbody_check;

				//---------------------------
				// CONFIG_LIMIT
				
				int c;
				int cfg_limit;
				int cfg_flag = -1;

				db_name.Format("-1-4-%1d-4",i+1);
				p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

				cfg_limit = atoi(first_data);
				if(cfg_limit > 0)	cfg_flag = 1;
	
				if(cfg_flag > 0)
				{
					xFile_Rcp_Ctrl->Go__NEXT_STEP();
				}

				if(cfg_limit != p_ppbody_ctrl->Get_CFG_PARAMETER_SIZE())
				{
					err_recipe = 1;
				}

				err_cfg_item_list = 0;

				for(c=0;c<cfg_limit;c++)
				{
					// CFG_PPARM_NAME
					db_name.Format("-1-4-%1d-4-%1d-1",i+1,c+1);
					p_recv_ctrl->Get_Data(db_name,cfg_pparm_name);

					// CFG_PPARM_DATA
					db_name.Format("-1-4-%1d-4-%1d-2",i+1,c+1);
					p_recv_ctrl->Get_Data(db_name,cfg_pparm_data);

					//------------------------------------
					ppbody_check = p_ppbody_ctrl->Check_CFG_DATA(cfg_pparm_name,cfg_pparm_data);

					if(ppbody_check > 0)
					{
						if(p_ppbody_ctrl->Get_CFG_PARAMETER_From_ITEM_NAME(cfg_pparm_name,
																		   ppbody_unit,
																		   ppbody_range,
																		   channel_name,
																		   channel_type,
																		   fmt_unit,
																		   fmt_size) > 0)
						{
							channel_data = cfg_pparm_data;

							xFile_Rcp_Ctrl->Add__ITEM(channel_name,channel_type,channel_data);
						}
					}
					else 
					{
						err_cfg_item_list++;

						// CFG_ITEM_ERROR_LIST
						db_name.Format("-1-2-%1d-5",(err_pmc_list+1));
						p_send_ctrl->Add_List(db_name,err_cfg_item_list);
					
						// CFG_ITEM_NAME
						db_name.Format("-1-2-%1d-5-%1d-1",(err_pmc_list+1),err_cfg_item_list);
						p_send_ctrl->Add_Ascii(db_name,cfg_pparm_name);

                       	// CFG_ERROR_CODE
						db_name.Format("-1-2-%1d-5-%1d-2",(err_pmc_list+1),err_cfg_item_list);
						p_send_ctrl->Add_U1(db_name,-ppbody_check);
					}
					//------------------------------------
				}
				
				//---------------------------
				// STEP_LIMIT
				int k;
				int step_limit;
				
				db_name.Format("-1-4-%1d-3",i+1);
				p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
				
				step_limit = atoi(first_data);

				err_step_list = 0;

				for(k=0;k<step_limit;k++)
				{
					// ITEM_LIMIT
					int t;
					int item_limit;
					
					db_name.Format("-1-4-%1d-3-%1d",i+1,k+1);
					p_recv_ctrl->Get_Data(db_name,pmc_data);
					
					item_limit = atoi(pmc_data);

					if(k == 0)
					{
						if(cfg_flag < 1)
						{
							xFile_Rcp_Ctrl->Go__NEXT_STEP();
						}
					}
					else
					{
						xFile_Rcp_Ctrl->Go__NEXT_STEP();
					}

					if(item_limit != p_ppbody_ctrl->Get_STEP_PARAMETER_SIZE())
					{
						err_recipe = 1;
					}

					//--------------------------------------------------------------
					err_step_item_list = 0;

					for(t=0;t<item_limit;t++)
					{
						// STEP_PPARM_NAME
						db_name.Format("-1-4-%1d-3-%1d-%1d-1",i+1,k+1,t+1);
						p_recv_ctrl->Get_Data(db_name,step_pparm_name);

						// STEP_PPARM_DATA
						db_name.Format("-1-4-%1d-3-%1d-%1d-2",i+1,k+1,t+1);
						p_recv_ctrl->Get_Data(db_name,step_pparm_data);

						//------------------------------------
						ppbody_check = p_ppbody_ctrl->Check_STEP_DATA(step_pparm_name,step_pparm_data);

						if(ppbody_check > 0)
						{
							if(p_ppbody_ctrl->Get_STEP_PARAMETER_From_ITEM_NAME(step_pparm_name,
																				ppbody_unit,
																				ppbody_range,
																				channel_name,
																				channel_type,
																				fmt_unit,
																				fmt_size) > 0)
							{
								channel_data = step_pparm_data;

								xFile_Rcp_Ctrl->Add__ITEM(channel_name,channel_type,channel_data);
							}
						}
						else 
						{
							if(err_step_item_list == 0)
							{
								err_step_list++;
								
								// STEP_ERROR_LIST
								db_name.Format("-1-2-%1d-4",(err_pmc_list+1));
								p_send_ctrl->Add_List(db_name,err_step_list);
							}
							err_step_item_list++;

							// STEP_NO
							db_name.Format("-1-2-%1d-4-%1d-1",(err_pmc_list+1),err_step_list);
							p_send_ctrl->Add_U1(db_name,k+1);

							// ITEM_ERROR_LIST
							db_name.Format("-1-2-%1d-4-%1d-2",(err_pmc_list+1),err_step_list);
							p_send_ctrl->Add_List(db_name,err_step_item_list);

							// STEP_ITEM_NAME
							db_name.Format("-1-2-%1d-4-%1d-2-%1d-1",(err_pmc_list+1),err_step_list,err_step_item_list);
							p_send_ctrl->Add_Ascii(db_name,step_pparm_name);

							// STEP_ERROR_CODE
							db_name.Format("-1-2-%1d-4-%1d-2-%1d-2",(err_pmc_list+1),err_step_list,err_step_item_list);
							p_send_ctrl->Add_U1(db_name,-ppbody_check);
						}
						//------------------------------------
					}
					//-----------------------------------------------
				}
			}
			else
			{
				err_recipe = 1;
			}

			//-----------------------------------------------
			if((err_recipe > 0)||(err_step_list > 0)||(err_cfg_item_list > 0))
			{
				err_pmc_list++;

				// ACKC7
				int ackc7 = 1;

				db_name.Format("-1-1");
				p_send_ctrl->Add_Binary(db_name,ackc7);

				// PM_ERROR_LIST
				db_name.Format("-1-2");
				p_send_ctrl->Add_List(db_name,err_pmc_list);

				// PM_ACK
				db_name.Format("-1-2-%1d-1",err_pmc_list);
				if(err_recipe > 0)		p_send_ctrl->Add_U1(db_name,1);
				else					p_send_ctrl->Add_U1(db_name,6);

				// PM_ID
				db_name.Format("-1-2-%1d-2",err_pmc_list);
				p_send_ctrl->Add_U1(db_name,pm_id);
				
				// PM_RECIPE
				db_name.Format("-1-2-%1d-3",err_pmc_list);
				p_send_ctrl->Add_Ascii(db_name,pm_recipe);
			}
			else
			{
				xFile_Rcp_Ctrl->Save__REMOTE_FILE(pm_id+1,
												  "",
												  pm_recipe,
												  "rcp");

				xFile_Rcp_Ctrl->Close__REMOTE_FILE();
			}
			//-----------------------------------------------
		}

		if(pm_list_limit > 0)
		{
			if(err_pmc_list < 1)
			{
				xFile_Route_Ctrl->End__STEP();
				xFile_Route_Ctrl->Save__FILE();
			}

			xFile_Route_Ctrl->Close__FILE();
		}
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//------------------------------------------------------------------------

	FA__OK
}
// Full Formatted Process Program Data Request/Reply
void CMsg_S07Fy::Recv__F85(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	SCX__FILE_ROUTE_INFO xFile_Route_Info;
	SCX__FILE_RCP_INFO   xFile_Rcp_Info;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl 
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	CString		 db_name;
	int			 type;
	CString		 first_data;
	CStringArray data_list;

	//-------------------------------	
	CString param_name;
	CString ppid;

	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
	ppid = first_data;

	//------------------------------------------------------------
	CString ppid_path;
	CString dir_route;

	p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Route(dir_route);

	// PPID
	db_name.Format("-1-1");
	p_send_ctrl->Add_Ascii(db_name,ppid);

	ppid_path  = dir_route;
	ppid_path += ppid;
	ppid_path += ".rte";

	if(xFile_Route_Info->Check__FILE(ppid_path) > 0)
	{
		// PPID_INFO
		db_name = "-1";
		p_send_ctrl->Add_List(db_name,4);


		xFile_Route_Info->Clear__MEM();
		xFile_Route_Info->Upload__FILE(ppid_path);

		int i, rte_step_size, rte_path_size;
		
		rte_step_size = xFile_Route_Info->Get__ROUTE_SERIAL_STEP_SIZE();
		if(rte_step_size < 0)	rte_step_size = 0;

		rte_path_size = xFile_Route_Info->Get__ROUTE_PARALLEL_PATH_SIZE(0);
		if(rte_path_size < 0)	rte_path_size = 0;
		
		// PM_LIST
		db_name.Format("-1-4");
		p_send_ctrl->Add_List(db_name,rte_path_size);

		//------------------------------------------------
		CDS__ROUTE_PMC_INFO pmc_info;
		int		pmc_id;
		CString	pmc_recipe;	
		CString	unit_type;
		int		unit_size;
		CString	pmc_data;

		for(i=0;i<rte_path_size;i++)
		{
			xFile_Route_Info->Get__PMC_INFO(0,i,pmc_info);

			pmc_id     = pmc_info.iMODULE_ID;
			pmc_recipe = pmc_info.sMODULE_RECIPE;

			//---------------------
			p_ppbody_ctrl->Set_Current_PM_ID(pmc_id);

			xFile_Rcp_Info->Clear__MEM();
			xFile_Rcp_Info->Upload__REMOTE_FILE(pmc_id+1,
												"",
												pmc_recipe,
												"rcp");
			//---------------------

			// PM_ID
			p_ppbody_ctrl->Get_FORMAT_From_PM_ID(unit_type,unit_size);

			pmc_data.Format("%1d",pmc_info.iMODULE_ID);

			db_name.Format("-1-4-%1d-1",(i+1));			
			p_send_ctrl->Add_Virtual(db_name,unit_type,unit_size,pmc_data);
			
			// PM_RECIPE
			p_ppbody_ctrl->Get_FORMAT_From_PM_RECIPE(unit_type,unit_size);

			pmc_data = pmc_info.sMODULE_RECIPE;
			
			db_name.Format("-1-4-%1d-2",(i+1));			
			p_send_ctrl->Add_Virtual(db_name,unit_type,unit_size,pmc_data);

			// STEP_LIMIT
			CString item_name;
			CString item_unit;
			CString item_range;
			CString ch_name;
			CString ch_type;
			CString fmt_unit;
			int fmt_size;
			int k;
			int rcp_step_size = xFile_Rcp_Info->Get__STEP_SIZE();
			
			db_name.Format("-1-4-%1d-3",(i+1));			
			p_send_ctrl->Add_List(db_name,rcp_step_size);

			for(k=0;k<rcp_step_size;k++)
			{
				// STEP_NO
				db_name.Format("-1-4-%1d-3-%1d-1",(i+1),(k+1));
				p_send_ctrl->Add_U1(db_name,k+1);

				// ITEM_LIMIT
				int rcp_item_size = p_ppbody_ctrl->Get_STEP_PARAMETER_SIZE();

				db_name.Format("-1-4-%1d-3-%1d-2",(i+1),(k+1));
				p_send_ctrl->Add_List(db_name,rcp_item_size);


				int t;
				for(t=0;t<rcp_item_size;t++)
				{
					p_ppbody_ctrl->Get_STEP_PARAMETER_From_INDEX(t,
																 item_name,item_unit,item_range,
																 ch_name,ch_type,
																 fmt_unit,fmt_size);
					
					if(xFile_Rcp_Info->Get__ITEM_DATA(k,ch_name,pmc_data) < 0)
					{
						pmc_data = "Unknown Data";
					}
					
					
					// PPARM_NAME
					db_name.Format("-1-4-%1d-3-%1d-2-%1d-1",(i+1),(k+1),(t+1));
					p_send_ctrl->Add_Ascii(db_name,item_name);
					
					// UNIT
					db_name.Format("-1-4-%1d-3-%1d-2-%1d-2",(i+1),(k+1),(t+1));
					p_send_ctrl->Add_Ascii(db_name,item_unit);

	              	// RANGE
					db_name.Format("-1-4-%1d-3-%1d-2-%1d-3",(i+1),(k+1),(t+1));
					p_send_ctrl->Add_Ascii(db_name,item_range);

	              	// DATA
					db_name.Format("-1-4-%1d-3-%1d-2-%1d-4",(i+1),(k+1),(t+1));
					p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,pmc_data);
				}
			}

			// CONFIG_ITEM_LIMIT
			if(rcp_step_size > 0)
			{
				int cfg_item_size;
				int tt;
			
				cfg_item_size = p_ppbody_ctrl->Get_CFG_PARAMETER_SIZE();

				db_name.Format("-1-4-%1d-4",(i+1));			
				p_send_ctrl->Add_List(db_name,cfg_item_size);

				for(tt=0;tt<cfg_item_size;tt++)
				{
					// CFG_PPARM
					p_ppbody_ctrl->Get_CFG_PARAMETER_From_INDEX(tt,
																item_name,item_unit,item_range,
																ch_name,ch_type,
																fmt_unit,fmt_size);

					if(xFile_Rcp_Info->Get__ITEM_DATA(0,ch_name,pmc_data) < 0)
					{
						pmc_data = "Unknown Data";
					}
					
					// CFG_PPARM_NAME
					db_name.Format("-1-4-%1d-4-%1d-1",(i+1),(tt+1)); 
					p_send_ctrl->Add_Ascii(db_name,item_name);

					// UNIT
					db_name.Format("-1-4-%1d-4-%1d-2",(i+1),(tt+1)); 
					p_send_ctrl->Add_Ascii(db_name,item_unit);

					// RANGE
					db_name.Format("-1-4-%1d-4-%1d-3",(i+1),(tt+1)); 
					p_send_ctrl->Add_Ascii(db_name,item_range);

					// DATA
					db_name.Format("-1-4-%1d-4-%1d-4",(i+1),(tt+1)); 
					p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,pmc_data);
				}
			}
		}
	}
	else
	{
		// PPID_INFO
		db_name = "-1";
		p_send_ctrl->Add_List(db_name,3);
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//------------------------------------------------------------------------

	FA__OK
}
// Partial Formatted Process Program Send/Ack
void CMsg_S07Fy::Recv__F93(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	SCX__FILE_ROUTE_CTRL xFile_Route_Ctrl;
	SCX__FILE_RCP_CTRL   xFile_Rcp_Ctrl;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl 
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	CString		 db_name;
	CString      pp_name;
	CString		 bff_name;
	int			 type;
	CString		 first_data;
	CStringArray data_list;

	int err_recipe;
	int err_pm_recipe;
	int err_pmc_list;
	int err_cfg_item_list;
	int err_step_list;
	int err_step_item_list;

	CString ppid;
	CString rte_path;
	int i;
	int pm_list_limit;

	// ACKC7
	int ackc7 = 0;

	db_name.Format("-1-1");
	p_send_ctrl->Add_Binary(db_name,ackc7);
	//-------------------------------

	//-------------------------------
	// PPID
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
	ppid = first_data;
	
	
	CString dir_route;
	p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Route(dir_route);
	
	rte_path  = dir_route;
	rte_path += ppid;
	rte_path += ".rte";


	int flag = xFile_Route_Ctrl->Check__FILE(rte_path);
	
	if(flag < 0)
	{
		//-------------------------------
		// ACKC7
		int ackc7 = 7;

		db_name.Format("-1-1");
		p_send_ctrl->Add_Binary(db_name,ackc7);
		//-------------------------------
	}
	else
	{
		// PM_LIST
		db_name = "-1-4";
		p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
		pm_list_limit = atoi(first_data);

		int     seq_id;
		int		pm_id;
		CString pm_recipe;
		CString pmc_path_process;

		err_pmc_list = 0;

		for(i=0;i<pm_list_limit;i++)
		{
			err_recipe = -1;

			pp_name.Format("-1-4-%1d",i+1);
			
			//-----------------------------------------------
			// PM_ID
			db_name  = pp_name;
			db_name += "-1";
			p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

			pm_id = atoi(first_data);
			seq_id = pm_id + 1;

			// PM_RECIPE
			db_name  = pp_name;
			db_name += "-2";
			p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);

			pm_recipe = first_data;

			
			// ROUTE RECIPE 累己
			xFile_Route_Ctrl->Add__PATH(pm_id,pm_recipe);
			//-----------------------------------------------

			//-----------------------------------------------
			// PM RECIPE 累己
			
			if(p_ppbody_ctrl->Set_Current_PM_ID(pm_id) > 0)
			{
				CString cfg_pparm_name;
				CString cfg_pparm_data;
				CString step_pparm_name;
				CString step_pparm_data;
				CString ppbody_unit;
				CString ppbody_range;

				if(xFile_Rcp_Ctrl->Check__REMOTE_FILE(seq_id,"",pm_recipe,"rcp") > 0)
				{
					err_pm_recipe = -1;

					xFile_Rcp_Ctrl->Partial__INIT_REMOTE_FILE(seq_id,"",pm_recipe,"rcp");
	
					//-----------------------------------------------
					CString channel_name;
					CString channel_type;
					CString channel_data;
					CString fmt_unit;
					int fmt_size;
					int step_no;
					int ppbody_check;

					//---------------------------
					// CONFIG_LIMIT
					int c;
					int cfg_limit;
					int cfg_flag = -1;

					db_name  = pp_name;
					db_name += "-4";
					p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
					cfg_limit = atoi(first_data);
					if(cfg_limit > 0)	cfg_flag = 1;
	
					if(cfg_flag > 0)
					{
						xFile_Rcp_Ctrl->Go__NEXT_STEP();
					}

					err_cfg_item_list = 0;
				
					if(xFile_Rcp_Ctrl->Partial__STEP_REMOTE_FILE(1) < 0)
					{
						err_pm_recipe =  1;
					}
					else
					{
						err_pm_recipe = -1;
					}
					
					for(c=0;c<cfg_limit;c++)
					{
						pp_name.Format("-1-4-%1d-4-%1d",i+1,c+1);

						// CFG_PPARM_NAME
						db_name  = pp_name;
						db_name += "-1";
						p_recv_ctrl->Get_Data(db_name,cfg_pparm_name);
	
						// CFG_PPARM_DATA
						db_name  = pp_name;
						db_name += "-2";
						p_recv_ctrl->Get_Data(db_name,cfg_pparm_data);

						//------------------------------------
						ppbody_check = p_ppbody_ctrl->Check_CFG_DATA(cfg_pparm_name,cfg_pparm_data);

						if((err_pm_recipe < 0)&&(ppbody_check > 0))
						{
							if(p_ppbody_ctrl->Get_CFG_PARAMETER_From_ITEM_NAME(cfg_pparm_name,
																			   ppbody_unit,
																			   ppbody_range,
																			   channel_name,
																			   channel_type,
																			   fmt_unit,
																			   fmt_size) > 0)
							{
								channel_data = cfg_pparm_data;
	
								xFile_Rcp_Ctrl->Partial__ITEM_REMOTE_FILE(channel_name,
																		  channel_type,
																		  channel_data);
							}
						}
						else 
						{
							err_cfg_item_list++;

							// CFG_ITEM_ERROR_LIST
							db_name.Format("-1-2-%1d-5",(err_pmc_list+1));
							p_send_ctrl->Add_List(db_name,err_cfg_item_list);

							pp_name.Format("-1-2-%1d-6-%1d",(err_pmc_list+1),err_cfg_item_list);
							
							// CFG_ITEM_NAME
							db_name  = pp_name;
							db_name += "-1";
							p_send_ctrl->Add_Ascii(db_name,cfg_pparm_name);

				           	// CFG_ERROR_CODE
							db_name  = pp_name;
							db_name += "-2";

							if(err_pm_recipe > 0)	p_send_ctrl->Add_U1(db_name,4);
							else					p_send_ctrl->Add_U1(db_name,-ppbody_check);
						}
						//------------------------------------
					}
				
					//---------------------------
					int k;
					int step_limit;

					// STEP_LIMIT
					db_name.Format("-1-4-%1d-3",i+1);
					p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
					step_limit = atoi(first_data);

					err_step_list = 0;

					for(k=0;k<step_limit;k++)
					{
						pp_name.Format("-1-4-%1d-3-%1d",i+1,k+1);

						// STEP_NO
						db_name  = pp_name;
						db_name += "-1";
						p_recv_ctrl->Get_Data(db_name,first_data);
						step_no = atoi(first_data);

						if(xFile_Rcp_Ctrl->Partial__STEP_REMOTE_FILE(step_no) < 0)
						{
							err_pm_recipe =  1;
						}
						else
						{
							err_pm_recipe = -1;
						}

						// ITEM_LIMIT
						int t;
						int item_limit;
						
						db_name  = pp_name;
						db_name += "-2";
						p_recv_ctrl->Get_Data(db_name,first_data);
						item_limit = atoi(first_data);

						//--------------------------------------------------------------
						err_step_item_list = 0;

						for(t=0;t<item_limit;t++)
						{
							pp_name.Format("-1-4-%1d-3-%1d-2-%1d",i+1,k+1,t+1);

							// STEP_PPARM_NAME
							db_name  = pp_name;
							db_name += "-1";
							p_recv_ctrl->Get_Data(db_name,step_pparm_name);

							// STEP_PPARM_DATA
							db_name  = pp_name;
							db_name += "-2";
							p_recv_ctrl->Get_Data(db_name,step_pparm_data);

							//------------------------------------
							ppbody_check = p_ppbody_ctrl->Check_STEP_DATA(step_pparm_name,step_pparm_data);

							if((err_pm_recipe < 0)&&(ppbody_check > 0))
							{
								if(p_ppbody_ctrl->Get_STEP_PARAMETER_From_ITEM_NAME(step_pparm_name,
																					ppbody_unit,
																					ppbody_range,
																					channel_name,
																					channel_type,
																					fmt_unit,
																					fmt_size) > 0)
								{
									channel_data = step_pparm_data;
	
									xFile_Rcp_Ctrl->Partial__ITEM_REMOTE_FILE(channel_name,
																			  channel_type,
																			  channel_data);
								}
							}
							else 
							{
								pp_name.Format("-1-2-%1d",(err_pmc_list+1));
						
								if(err_step_item_list == 0)
								{
									err_step_list++;
								
									// STEP_ERROR_LIST
									db_name  = pp_name;
									db_name += "-4";
									p_send_ctrl->Add_List(db_name,err_step_list);
								}
								err_step_item_list++;

								bff_name.Format("-4-%1d",err_step_list);
								pp_name += bff_name;
								
								// STEP_NO
								db_name  = pp_name;
								db_name += "-1";
								p_send_ctrl->Add_U1(db_name,step_no);

								// ITEM_ERROR_LIST
								db_name  = pp_name;
								db_name += "-2";
								p_send_ctrl->Add_List(db_name,err_step_item_list);

	
								pp_name  = db_name;
								bff_name.Format("-%1d",err_step_item_list);
								pp_name += bff_name;
		
	
								// STEP_ITEM_NAME
								db_name  = pp_name;
								db_name += "-1";
								p_send_ctrl->Add_Ascii(db_name,step_pparm_name);

								// STEP_ERROR_CODE
								db_name  = pp_name;
								db_name += "-2";
								
								if(err_pm_recipe > 0)	p_send_ctrl->Add_U1(db_name,4);
								else					p_send_ctrl->Add_U1(db_name,-ppbody_check);
							}
							//------------------------------------
						}
						//-----------------------------------------------
					}
				}
				else
				{
					err_recipe = 1;
				}
			}
			else
			{
				err_recipe = 1;
			}

			//-----------------------------------------------
			if((err_recipe    > 0)||(err_pm_recipe     > 0)
			|| (err_step_list > 0)||(err_cfg_item_list > 0))
			{
				err_pmc_list++;

				// ACKC7
				int ackc7 = 1;

				db_name = "-1-1";
				p_send_ctrl->Add_Binary(db_name,ackc7);

				// PM_ERROR_LIST
				db_name = "-1-2";
				p_send_ctrl->Add_List(db_name,err_pmc_list);


				bff_name.Format("-%1d",err_pmc_list);
				pp_name  = db_name;
				pp_name += bff_name;
				
				
				// PM_ACK
				db_name  = pp_name;
				db_name += "-1";
				if(err_recipe > 0)		p_send_ctrl->Add_U1(db_name,7);
				else					p_send_ctrl->Add_U1(db_name,1);

				// PM_ID
				db_name  = pp_name;
				db_name += "-2";
				p_send_ctrl->Add_U1(db_name,pm_id);
				
				// PM_RECIPE
				db_name  = pp_name;
				db_name += "-3";
				p_send_ctrl->Add_Ascii(db_name,pm_recipe);
			}
			else
			{
				xFile_Rcp_Ctrl->Partial__SAVE_REMOTE_FILE(seq_id,
														  "",
														  pm_recipe,
														  "rcp");
			}
			//-----------------------------------------------
		}

		if(pm_list_limit > 0)
		{
			if(err_pmc_list < 1)
			{
				xFile_Route_Ctrl->End__STEP();
				xFile_Route_Ctrl->Save__FILE();
			}

			xFile_Route_Ctrl->Close__FILE();
		}
	}
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//------------------------------------------------------------------------

	FA__OK
}
// Partial Formatted Process Program Data Request/Reply
void CMsg_S07Fy::Recv__F95(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	SCX__FILE_ROUTE_INFO xFile_Route_Info;
	SCX__FILE_RCP_INFO   xFile_Rcp_Info;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl 
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	CString      bff_name;
	CString		 pp_name;
	CString		 db_name;
	CString		 first_data;
	CStringArray data_list;

	CString ppid;
	CString ppid_path;
	int i;
	int	k;
	int t;
	int	pm_list;
	int	pm_id;
	CString pm_recipe;
	int step_list;
	int step_no;
	int step_index;
	int item_list;
	CString pparm_name;
	CString pparm_unit;
	CString pparm_range;
	CString ch_name;
	CString ch_type;
	CString ch_data;
	CString fmt_unit;
	int fmt_size;
	int err_pm_recipe;
	CString pmc_data;

	// PPID
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,first_data);
	ppid = first_data;

	db_name = "-1-1";
	p_send_ctrl->Add_Ascii(db_name,ppid);


	CString dir_route;
	p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Route(dir_route);

	ppid_path  = dir_route;
	ppid_path += ppid;
	ppid_path += ".rte";
		
	if(xFile_Route_Info->Check__FILE(ppid_path) > 0)
	{
		// PPID_INFO
		db_name = "-1";
		p_send_ctrl->Add_List(db_name,4);
	
	
		// PM_LIST
		db_name = "-1-2";
		p_recv_ctrl->Get_Data(db_name,first_data);
		pm_list = atoi(first_data);

		db_name = "-1-4";
		p_send_ctrl->Add_List(db_name,pm_list);

		for(i=0;i<pm_list;i++)
		{
			pp_name.Format("-1-4-%1d",(i+1));


			// PM_ID
			db_name.Format("-1-2-%1d-1",i+1);
			p_recv_ctrl->Get_Data(db_name,pmc_data);
			pm_id = atoi(pmc_data);

		
			p_ppbody_ctrl->Set_Current_PM_ID(pm_id);
			p_ppbody_ctrl->Get_FORMAT_From_PM_ID(fmt_unit,fmt_size);


			db_name  = pp_name;
			db_name += "-1";
			p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,pmc_data);

			// PM_RECIPE
			db_name.Format("-1-2-%1d-2",i+1);
			p_recv_ctrl->Get_Data(db_name,pmc_data);
			pm_recipe = pmc_data;


			p_ppbody_ctrl->Get_FORMAT_From_PM_RECIPE(fmt_unit,fmt_size);

		
			db_name  = pp_name;
			db_name += "-2";
			p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,pmc_data);


			//---------------------
			xFile_Rcp_Info->Clear__MEM();
			xFile_Rcp_Info->Upload__REMOTE_FILE(pm_id+1,
												"",
												pm_recipe,
												"rcp");
			//---------------------

			// STEP_LIMIT
			db_name.Format("-1-2-%1d-3",i+1);
			p_recv_ctrl->Get_Data(db_name,pmc_data);
			step_list = atoi(pmc_data);


			db_name  = pp_name;
			db_name += "-3";
			p_send_ctrl->Add_List(db_name,step_list);

			for(k=0;k<step_list;k++)
			{
				pp_name.Format("-1-4-%1d-3-%1d",(i+1),(k+1));
	
				// STEP_NO
				db_name.Format("-1-2-%1d-3-%1d-1",i+1,k+1);
				p_recv_ctrl->Get_Data(db_name,pmc_data);
				step_no    = atoi(pmc_data);
				step_index = step_no - 1; 

			
				db_name  = pp_name;
				db_name += "-1";
				p_send_ctrl->Add_U1(db_name,step_no);

				if((step_no > xFile_Rcp_Info->Get__STEP_SIZE())
				|| (step_no < 1))
				{
					err_pm_recipe =  1;
				}
				else
				{
					err_pm_recipe = -1;
				}

	
				// ITEM_LIMIT
				db_name.Format("-1-2-%1d-3-%1d-2",i+1,k+1);
				p_recv_ctrl->Get_Data(db_name,pmc_data);
				item_list = atoi(pmc_data);


				db_name  = pp_name;
				db_name += "-2";
				p_send_ctrl->Add_List(db_name,item_list);

				for(t=0;t<item_list;t++)
				{
					pp_name.Format("-1-4-%1d-3-%1d-2-%1d",(i+1),(k+1),(t+1));

					// PPARM_NAME
					db_name.Format("-1-2-%1d-3-%1d-2-%1d",i+1,k+1,t+1);
					p_recv_ctrl->Get_Data(db_name,pparm_name);

					int item_flag = p_ppbody_ctrl->Get_STEP_PARAMETER_From_ITEM_NAME(pparm_name,
																					 pparm_unit,
																					 pparm_range,
																					 ch_name,
																					 ch_type,
																					 fmt_unit,
																					 fmt_size);
					if((err_pm_recipe < 0)&&(item_flag > 0))
					{
						xFile_Rcp_Info->Get__ITEM_DATA(step_index,ch_name,ch_data);
					}
					else
					{
						pparm_unit  = "???";
						pparm_range = "???";
						ch_data     = "???";	
					}

					// NAME
					db_name  = pp_name;
					db_name += "-1";
					p_send_ctrl->Add_Ascii(db_name,pparm_name);

					// UNIT
					db_name  = pp_name;
					db_name += "-2";
					p_send_ctrl->Add_Ascii(db_name,pparm_unit);

					// RANGE
					db_name  = pp_name;
					db_name += "-3";
					p_send_ctrl->Add_Ascii(db_name,pparm_range);

					// DATA
					db_name  = pp_name;
					db_name += "-4";
					p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,ch_data);
				}
			}

			// CFG ITEM LIMIT
			db_name.Format("-1-2-%1d-4",i+1);
			p_recv_ctrl->Get_Data(db_name,pmc_data);
			item_list = atoi(pmc_data);


			pp_name.Format("-1-4-%1d-4",(i+1));
			db_name = pp_name;
			p_send_ctrl->Add_List(db_name,item_list);

			for(k=0;k<item_list;k++)
			{
				bff_name.Format("-%1d",(k+1));
				pp_name += bff_name;

				// PPARM_NAME
				db_name.Format("-1-2-%1d-4-%1d",i+1,k+1);
				p_recv_ctrl->Get_Data(db_name,pparm_name);

				int item_flag = p_ppbody_ctrl->Get_CFG_PARAMETER_From_ITEM_NAME(pparm_name,
																				pparm_unit,
																				pparm_range,
																				ch_name,
																				ch_type,
																				fmt_unit,
																				fmt_size);
				if((err_pm_recipe < 0)&&(item_flag > 0))
				{
					xFile_Rcp_Info->Get__ITEM_DATA(0,ch_name,ch_data);
				}
				else
				{
					pparm_unit  = "???";
					pparm_range = "???";
					ch_data     = "???";	
				}

				// NAME
				db_name  = pp_name;
				db_name += "-1";
				p_send_ctrl->Add_Ascii(db_name,pparm_name);

				// UNIT
				db_name  = pp_name;
				db_name += "-2";
				p_send_ctrl->Add_Ascii(db_name,pparm_unit);

				// RANGE
				db_name  = pp_name;
				db_name += "-3";
				p_send_ctrl->Add_Ascii(db_name,pparm_range);

				// DATA
				db_name  = pp_name;
				db_name += "-4";
				p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,ch_data);
			}
		}
	}
	else
	{
		// PPID_INFO
		db_name = "-1";
		p_send_ctrl->Add_List(db_name,3);
	}
	//------------------------------------------------------------------------
	
	//------------------------------------------------------------------------
	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//------------------------------------------------------------------------

	FA__OK
}

void CMsg_S07Fy::Recv__F97(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	SCX__FILE_ROUTE_INFO xFile_Route_Info;
	SCX__FILE_RCP_INFO   xFile_Rcp_Info;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl 
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	CString		 db_name;
	int			 type;
	CString		 first_data;
	CStringArray data_list;

	//------------------------------------------------------------
	CString ppid;

	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
	ppid = first_data;
	//------------------------------------------------------------

	//------------------------------------------------------------
	// PPID
	db_name = "-1-1";
	p_send_ctrl->Add_Ascii(db_name,ppid);

	// MDLN
	//db_name = "-1-2";

	// SOFTREV
	//db_name = "-1-3";


	CString dir_route;
	CString ppid_path;

	p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Route(dir_route);

	ppid_path  = dir_route;
	ppid_path += ppid;
	ppid_path += ".rte";

	if(xFile_Route_Info->Check__FILE(ppid_path) > 0)
	{
		// PPID_INFO
		db_name = "-1";
		p_send_ctrl->Add_List(db_name,4);


		xFile_Route_Info->Clear__MEM();
		xFile_Route_Info->Upload__FILE(ppid_path);

		int i;
		int rte_step_size;
		int rte_path_size;
		
		rte_step_size = xFile_Route_Info->Get__ROUTE_SERIAL_STEP_SIZE();
		if(rte_step_size < 0)	rte_step_size = 0;

		rte_path_size = xFile_Route_Info->Get__ROUTE_PARALLEL_PATH_SIZE(0);
		if(rte_path_size < 0)	rte_path_size = 0;
		
		// PM_LIST
		db_name = "-1-4";
		p_send_ctrl->Add_List(db_name,rte_path_size);

		CDS__ROUTE_PMC_INFO pmc_info;
		int		 pmc_id;
		CString	 pmc_recipe;
		CString	 unit_type;
		int		 unit_size;
		CString	 pmc_data;

		for(i=0;i<rte_path_size;i++)
		{
			xFile_Route_Info->Get__PMC_INFO(0,i,pmc_info);

			pmc_id     = pmc_info.iMODULE_ID;
			pmc_recipe = pmc_info.sMODULE_RECIPE;

			//---------------------
			p_ppbody_ctrl->Set_Current_PM_ID(pmc_id);
			
			xFile_Rcp_Info->Clear__MEM();
			xFile_Rcp_Info->Upload__REMOTE_FILE(pmc_id+1,
												"",
												pmc_recipe,
												"rcp");
			//---------------------

			// PM_ID
			p_ppbody_ctrl->Get_FORMAT_From_PM_ID(unit_type,unit_size);
			pmc_data.Format("%1d",pmc_id);

			db_name.Format("-1-4-%1d-1",i+1);
			p_send_ctrl->Add_Virtual(db_name,unit_type,unit_size,pmc_data);

			// PM_RECIPE
			p_ppbody_ctrl->Get_FORMAT_From_PM_RECIPE(unit_type,unit_size);
			pmc_data = pmc_recipe;

			db_name.Format("-1-4-%1d-2",i+1);
			p_send_ctrl->Add_Virtual(db_name,unit_type,unit_size,pmc_data);

		}
	}
	else
	{
		// PPID_INFO
		db_name = "-1";
		p_send_ctrl->Add_List(db_name,3);
	}

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//------------------------------------------------------------------------

	FA__OK
}
void CMsg_S07Fy::Recv__F99(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//------------------------------------------------------------------------
	SCX__FILE_ROUTE_INFO xFile_Route_Info;
	SCX__FILE_RCP_INFO   xFile_Rcp_Info;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl 
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	CString	db_name;
	int		type;
	CString first_data;
	CStringArray data_list;

	//.....
	int pmc_id;
	CString pmc_recipe;
	CString pmc_data;

	// PM_ID
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,type,first_data,data_list);
	pmc_id = atoi(first_data);

	// PM_RECIPE
	db_name = "-1-2";
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
