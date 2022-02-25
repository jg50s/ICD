#include "StdAFx.h"

#include "MSG_S7Fy.h"
CMsg_S7Fy mMSG_S7Fy;


//----------------------------------------------------------------------------
CMsg_S7Fy::CMsg_S7Fy()
{
	iSx = 7;

	iFlag__Log_Ctrl = -1;
}

void CMsg_S7Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	/*
	switch(p_bridge_ctrl->iFy)
	{
	}
	*/
}

void CMsg_S7Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	switch(p_bridge_ctrl->iFy)
	{
		/*
		case 19:
			if(p_bridge_ctrl->iType == 0)
			{
				Recv__F19_0(p_bridge_ctrl);		
			}
			return;
		*/
		
		case 25:    
			Recv__F25(p_bridge_ctrl);		
			return;
	}
}


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void CMsg_S7Fy::Recv__F19_0(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CI_SEQ_INFO *p_seq_info	= p_bridge_ctrl->pRES_SEQ_INFO;

	CString	db_name;
	int n_count = 0;

	// CTC
	{
		//.....
		CString	dir_route;
		CStringArray l_file;

		p_seq_info->Get__Dir_Route(dir_route);
		p_seq_info->Search_File(dir_route,"rte",l_file);

		//.....
		CString ascii;

		int list_limit = l_file.GetSize();
		int i;

		for(i=0;i<list_limit;i++)
		{
			// n.<A   $ASCII	
			n_count++;
			db_name.Format("-1-%1d",n_count);
			
			ascii.Format("ROUTE\\%s", l_file[i]);
			p_bridge_ctrl->pMSG_SEND_CTRL->Add_Ascii(db_name,ascii);
		}
	}

	// PMx
	{		
		int seq_id;
		int i;

		for(i=0;i<6;i++)
		{
			seq_id = i + 2;

			//.....
			SCX__FILE_RCP_INFO file_rcp_info;
			CStringArray l_file;

			file_rcp_info->Search__REMOTE_FILE_LIST(seq_id,"#DIR_FILE","rcp",l_file);

			//.....
			CString file_name;
			CString file_title;
			CString key_word = ".rcp";
			int db_index;

			int k_limit = l_file.GetSize();
			int k;

			for(k=0;k<k_limit;k++)
			{
				//	  n.<A   $ASCII	
				n_count++;
				db_name.Format("-1-%1d",n_count);
		
				//
				file_name.Format("PM%1d\\%s", i+1,l_file[k]);
				db_index = file_name.Find(key_word);
				if(db_index > 0)	file_name.Delete(db_index,key_word.GetLength());
				
				file_title = file_name;

				//
				p_bridge_ctrl->pMSG_SEND_CTRL->Add_Ascii(db_name,file_title);
			}
		}
	}

	// 1.<L,  n
	{
		db_name = "-1";
		p_bridge_ctrl->pMSG_SEND_CTRL->Add_List(db_name,n_count);
	}
	//----------------------------------------------------------

	//----------------------------------------------------------
		
	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//----------------------------------------------------------

	FA__OK
}
		
void CMsg_S7Fy::Recv__F25(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(iFlag__Log_Ctrl < 0)
	{
		iFlag__Log_Ctrl = 1;

		// ...
		{
			CString obj_name;
			CString file_name;
			CString log_msg;
			
			obj_name  = "FA_LOG";
			file_name = "S7F25.log";
			
			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";
			
			xLog_Ctrl->CREATE__SUB_DIRECTORY(obj_name);
			xLog_Ctrl->SET__PROPERTY(file_name, 24*5,60);
			
			xLog_Ctrl->DISABLE__TIME_LOG();
			xLog_Ctrl->WRITE__LOG(log_msg);
			
			xLog_Ctrl->ENABLE__TIME_LOG();
			xLog_Ctrl->WRITE__LOG("   START   \n");
			
			xLog_Ctrl->LINK__OBJECT(obj_name);
		}		
	}

	//------------------------------------------------------------------------
	SCX__FILE_ROUTE_INFO xFile_Route_Info;
	SCX__FILE_RCP_INFO   xFile_Rcp_Info;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl 
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__PPBODY_CTRL *p_ppbody_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_PPBODY_CTRL();

	CI_FA_VARIABLE_CTRL *p_var_ctrl
		= p_bridge_ctrl->pRES_VARIABLE_CTRL;
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
	int check_route = -1;
	int pmx_check   = -1;
	CString file_name;
	CString key_word;

	key_word = "ROUTE\\";
	if(ppid.Find(key_word) == 0)
	{
		check_route = 1;

		file_name = ppid;
		file_name.Delete(0,key_word.GetLength());
	}
	else 
	{
		int i;

		for(i=0;i<10;i++)
		{
			key_word.Format("PM%1d\\",i+1);
			if(ppid.Find(key_word) != 0)
			{
				continue;
			}

			//
			pmx_check = i+1;

			file_name = ppid;
			file_name.Delete(0,key_word.GetLength());
			break;
		}
	}

	// PPID
	db_name = "-1-1";
	p_send_ctrl->Add_Ascii(db_name,ppid);

	// MDLN
	//db_name = "-1-2";

	// SOFTREV
	//db_name = "-1-3";

	if(check_route > 0)
	{
		CString dir_route;
		CString ppid_path;

		p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Route(dir_route);

		ppid_path  = dir_route;
		ppid_path += file_name;
		ppid_path += ".rte";

		if(xFile_Route_Info->Check__FILE(ppid_path) > 0)
		{
			// PPID_INFO
			db_name = "-1";
			p_send_ctrl->Add_List(db_name,4);

			//
			xFile_Route_Info->Clear__MEM();
			xFile_Route_Info->Upload__FILE(ppid_path);

			int rte_step_size;
			int rte_path_size;
			int i;
		
			rte_step_size = xFile_Route_Info->Get__ROUTE_SERIAL_STEP_SIZE();
			if(rte_step_size < 0)	rte_step_size = 0;
	
			rte_path_size = xFile_Route_Info->Get__ROUTE_PARALLEL_PATH_SIZE(0);
			if(rte_path_size < 0)	rte_path_size = 0;
		
			//
			db_name = "-1-4";
			p_send_ctrl->Add_List(db_name,1);

			// ITEM_LIST
			db_name = "-1-4-1";
			p_send_ctrl->Add_List(db_name,2);

			//
			db_name = "-1-4-1-1";
			p_send_ctrl->Add_Ascii(db_name,"0");

			// ...
			{
				/*
				CString main_name;
				CString sub_name;
				CString var_data;
				int pmc_size;	 
			
				//
				main_name = "E30.SYSTEM";

				//
				sub_name  = "PMC.SIZE";
				p_var_ctrl->Get_Variable(main_name,sub_name,var_data);
				pmc_size = atoi(var_data);

				//
				db_name = "-1-4-1-2";
				p_send_ctrl->Add_List(db_name,pmc_size);
				*/

				db_name = "-1-4-1-2";
				p_send_ctrl->Add_List(db_name,4);
			}

			//
			CDS__ROUTE_PMC_INFO pmc_info;
			int		 pmc_id;
			CString	 pmc_recipe;
			CString  file_name;

			for(i=0;i<rte_path_size;i++)
			{
				//
				xFile_Route_Info->Get__PMC_INFO(0,i,pmc_info);

				pmc_id     = pmc_info.iMODULE_ID;
				pmc_recipe = pmc_info.sMODULE_RECIPE;

				// file_name.Format("PM%1d\\%s",pmc_id,pmc_recipe);
				file_name = pmc_recipe;

				//
				db_name.Format("-1-4-1-2-%1d",pmc_id);
				p_send_ctrl->Add_Ascii(db_name,file_name);
			}
		}
		else
		{
			// PPID_INFO
			db_name = "-1";
			p_send_ctrl->Add_List(db_name,3);
		}
	}
	else if(pmx_check > 0)
	{
		CString db_data;

		// PPID_INFO
		db_name = "-1";
		p_send_ctrl->Add_List(db_name,4);

		//
		db_name = "-1-4";
		p_send_ctrl->Add_List(db_name,1);

		// ITEM_LIST
		db_name = "-1-4-1";
		p_send_ctrl->Add_List(db_name,4);

		//
		CDS__ROUTE_PMC_INFO pmc_info;
		int      pmc_id = pmx_check;
		CString	 pmc_recipe = file_name;

		CString	 unit_type;
		int		 unit_size;
		CString	 pmc_data;

		if(pmc_id >= 0)
		{
			CString file_data;
			int ok_flag = 1;

			//---------------------
			p_ppbody_ctrl->Set_Current_PM_ID(pmc_id);
				
			xFile_Rcp_Info->Clear__MEM();
			// xFile_Rcp_Info->Upload__REMOTE_FILE(pmc_id+1,"",pmc_recipe,"rcp");
			ok_flag = xFile_Rcp_Info->Upload__REMOTE_FILE_AND_Get__FILE_DATA(pmc_id+1,"",pmc_recipe,"rcp",file_data);

			//---------------------
			// PM_ID
			p_ppbody_ctrl->Get_FORMAT_From_PM_ID(unit_type,unit_size);
			pmc_data.Format("%1d",pmc_id);

			db_name = "-1-4-1-1";
			p_send_ctrl->Add_Virtual(db_name,unit_type,unit_size,pmc_data);

			// PM_RECIPE
			p_ppbody_ctrl->Get_FORMAT_From_PM_RECIPE(unit_type,unit_size);
			pmc_data = pmc_recipe;

			db_name = "-1-4-1-2";
			p_send_ctrl->Add_Virtual(db_name,unit_type,unit_size,pmc_data);

			// STEP_LIMIT
			CUIntArray l__stepid_of_step_type_end;

			CString item_unit;
			CString item_range;
			CString ch_name;
			CString ch_type;
			CString fmt_unit;
			int     fmt_size;

			int rcp_step_size = xFile_Rcp_Info->Get__STEP_SIZE();
			int k;

			if(ok_flag < 0)
			{
				rcp_step_size = 0;
			}

			db_name = "-1-4-1-3";
			p_send_ctrl->Add_List(db_name,rcp_step_size);

			for(k=0;k<rcp_step_size;k++)
			{
				// ITEM_LIMIT
				int rcp_item_size;
				int t;

				// STEP PARAMETER
				rcp_item_size = p_ppbody_ctrl->Get_STEP_PARAMETER_SIZE();
	
				db_name.Format("-1-4-1-3-%1d",k+1);
				p_send_ctrl->Add_List(db_name,rcp_item_size);
	
				for(t=0;t<rcp_item_size;t++)
				{
					// STEP_PPARM
					{
						p_ppbody_ctrl->Get_STEP_PARAMETER_From_INDEX(t,
																     db_name,item_unit,item_range,
																     ch_name,ch_type,
																     fmt_unit,fmt_size);
				
						if(xFile_Rcp_Info->Get__ITEM_DATA(k,ch_name,pmc_data) < 0)
						{
							// pmc_data = "Unknown Data";
							pmc_data = "";
						}
									
						db_name.Format("-1-4-1-3-%1d-%1d",k+1,t+1);
						p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,pmc_data);
					}

					if(ch_name.CompareNoCase("FNC_STEP+RCP.STEP.TYPE") == 0)
					{
						if(pmc_data.CompareNoCase("End") == 0)
						{
							l__stepid_of_step_type_end.Add(1);
						}
						else
						{
							l__stepid_of_step_type_end.Add(0);
						}
					}
				}
			}

			// Step Type : "End" Check ...
			{
				int end_step_id = 0;
				int err_flag = -1;

				int i_limit = l__stepid_of_step_type_end.GetSize();
				int i;
				
				for(i=0; i<i_limit; i++)
				{
					if(l__stepid_of_step_type_end[i] > 0)
					{
						end_step_id = i + 1;
						break;
					}
				}

				if(end_step_id < rcp_step_size)
				{
					err_flag = 1;

					db_name = "-1-4-1-3";
					p_send_ctrl->Add_List(db_name, end_step_id);
				}					

				if((err_flag > 0) || (ok_flag < 0))
				{
					// Error Log ...
					{
						CString log_msg;
						CString bff;

						CString file_name;
						
						file_name.Format("PM%1d\\%s", pmc_id,pmc_recipe);

						log_msg  = "File Error \n";

						bff.Format("end_step_id <- %1d \n", end_step_id);
						log_msg += bff;
						
						bff.Format("rcp_step_size <- %1d \n", rcp_step_size);
						log_msg += bff;

						log_msg += "File Name : ";
						log_msg += file_name;
						log_msg += "\n";

						if(err_flag > 0)
						{
							log_msg += "File Data ...\n";
							log_msg += file_data;
							log_msg += "\nFile_End ...\n";
						}

						if(ok_flag < 0)
						{
							CString log_bff;
							CString err_msg;

							log_bff.Format("Ok_Flag(%1d) \n", ok_flag);
							log_msg += log_bff;

							//
							xFile_Rcp_Info->Get__FILE_DB__ERROR_MESSAGE(err_msg);

							log_msg += "Error Message ... \n";
							log_msg += err_msg;
						}

						xLog_Ctrl->WRITE__LOG(log_msg);
					}
				}
			}

			// CONFIG_LIMIT
			if(rcp_step_size > 0)
			{
				int cfg_item_size;
				int tt;
			
				cfg_item_size = p_ppbody_ctrl->Get_CFG_PARAMETER_SIZE();
	
				db_name = "-1-4-1-4";
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
						// pmc_data = "Unknown Data";
						pmc_data = "";
					}
					
					db_name.Format("-1-4-1-4-%1d",tt+1);
					p_send_ctrl->Add_Virtual(db_name,fmt_unit,fmt_size,pmc_data);
				}
			}
		}
		else
		{
			// PPID_INFO
			db_name = "-1";
			p_send_ctrl->Add_List(db_name,3);
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
