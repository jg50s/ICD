#include "StdAFx.h"

#include "MSG_S16Fy.h"
CMsg_S16Fy mMSG_S16Fy;


//----------------------------------------------------------------------------
CMsg_S16Fy::CMsg_S16Fy()
{
	iSx = 16;
}

void CMsg_S16Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)				return;

	/*
	switch(p_bridge_ctrl->iFy)
	{
	}
	*/
}

void CMsg_S16Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)				return;

	switch(p_bridge_ctrl->iFy)
	{
		case 5:		Recv__F5(p_bridge_ctrl);	return;
		case 7:		Recv__F7(p_bridge_ctrl);	return;
		case 9:		Recv__F9(p_bridge_ctrl);	return;
		case 11:	Recv__F11(p_bridge_ctrl);	return;
		case 13:	Recv__F13(p_bridge_ctrl);	return;
		case 15:	Recv__F15(p_bridge_ctrl);	return;
		case 17:	Recv__F17(p_bridge_ctrl);	return;
		case 19:	Recv__F19(p_bridge_ctrl);	return;
		case 21:	Recv__F21(p_bridge_ctrl);	return;

		case 25:	Recv__F25(p_bridge_ctrl);	return;
		case 27:	Recv__F27(p_bridge_ctrl);	return;
		case 29:	Recv__F29(p_bridge_ctrl);	return;
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
	MessageBox(NULL,"CHECK","MSG_S16 : Recv__F7()",MB_OK|MB_TOPMOST);
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
	MessageBox(NULL,"CHECK","MSG_S16 : Recv__F9()",MB_OK|MB_TOPMOST);
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

	CString db_name;
	CString var_data;

	//-------------------------------
	CString pjobid;
	int cst_list;
	int slot_limit;
	int visit_limit;
	int i;
	int t;

	p_e40_ctrl->Clear_PRJob();

	//-------------------------------
	// PJOBID
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,pjobid);

	// CST LIST
	db_name = "-1-4";
	p_recv_ctrl->Get_Data(db_name,var_data);

	cst_list = atoi(var_data);

	for(t=0;t<cst_list;t++)
	{
		// CARRIERID
		db_name.Format("-1-4-%1d-1",t+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		p_e40_ctrl->Load_CARRIERID(var_data);

		// SLOT_LIMIT
		db_name.Format("-1-4-%1d-2",t+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		slot_limit = atoi(var_data);

		for(i=0;i<slot_limit;i++)
		{
			// SLOTID
			db_name.Format("-1-4-%1d-2-%1d",t+1,i+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			p_e40_ctrl->Load_SLOTID(atoi(var_data));
		}

		// VISION VISIT LIMIT
		db_name.Format("-1-4-%1d-3",t+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		visit_limit = atoi(var_data);

		for(i=0;i<visit_limit;i++)
		{
			// VISIT FLAG
			db_name.Format("-1-4-%1d-3-%1d",t+1,i+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			p_e40_ctrl->Load_VISION_VISIT(atoi(var_data));
		}
	}

	// RECIPE METHOD
	db_name = "-1-5-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	p_e40_ctrl->Load_RecipeMethod(atoi(var_data));

	// RCPSPEC
	db_name = "-1-5-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	p_e40_ctrl->Load_RecID(var_data);

	// PROCESS START
	db_name = "-1-6";
	p_recv_ctrl->Get_Data(db_name,var_data);

	var_data.MakeUpper();

	int start_method;
	if(var_data == "FF")	start_method = 1;
	else					start_method = atoi(var_data);

	p_e40_ctrl->Load_PRProcessStart(start_method);
	//-------------------------------

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

		// ERRCODE
		db_name = "-1-2-2-1-1";
		p_send_ctrl->Add_U1(db_name,err_code);

		// ERRTEXT
		db_name = "-1-2-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
		//---------------------------
	}
	else
	{
		int flag = p_e40_ctrl->Create_PRJob(pjobid);

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
void CMsg_S16Fy::Recv__F13(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
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
	int i;
	int j;

	int pjob_limit;
	int recipe_method;
	CString rcpspec;
	CString pjobid;
	int slot_limit;
	int vis_limit;
	int process_start;

	int err_count = 0;
	int err_code;
	CString err_text;

	//-------------------------------
	// PJOB_LIMIT
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	pjob_limit = atoi(var_data);

	// RECIPE_METHOD
	db_name = "-1-3-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	recipe_method = atoi(var_data);

	// RCPSPEC
	db_name = "-1-3-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	rcpspec = var_data;

	// PROCESS_START
	db_name = "-1-4";
	p_recv_ctrl->Get_Data(db_name,var_data);

	var_data.MakeUpper();

	if(var_data == "FF")	process_start = 1;
	else					process_start = atoi(var_data);

	for(i=0;i<pjob_limit;i++)
	{
		p_e40_ctrl->Clear_PRJob();

		//---------------------------------
		// PJOBID
		db_name.Format("-1-2-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,pjobid);

		// CST LIST
		int t;
		int cst_list;

		db_name.Format("-1-2-%1d-3",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		cst_list = atoi(var_data);

		for(t=0;t<cst_list;t++)
		{
			// CARRIERID
			db_name.Format("-1-2-%1d-3-%1d-1",i+1,t+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			p_e40_ctrl->Load_CARRIERID(var_data);

			// SLOT_LIMIT
			db_name.Format("-1-2-%1d-3-%1d-2",i+1,t+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			slot_limit = atoi(var_data);

			for(j=0;j<slot_limit;j++)
			{
				// SLOTID
				db_name.Format("-1-2-%1d-3-%1d-2-%1d",i+1,t+1,j+1);
				p_recv_ctrl->Get_Data(db_name,var_data);

				p_e40_ctrl->Load_SLOTID(atoi(var_data));
			}

			// VISION VISIT LIMIT
			db_name.Format("-1-2-%1d-3-%1d-3",i+1,t+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			vis_limit = atoi(var_data);

			for(j=0;j<vis_limit;j++)
			{
				// VISION FLAG
				db_name.Format("-1-2-%1d-3-%1d-3-%1d",i+1,t+1,j+1);
				p_recv_ctrl->Get_Data(db_name,var_data);
	
				p_e40_ctrl->Load_VISION_VISIT(atoi(var_data));
			}
		}
		//---------------------------------

		//---------------------------------
		p_e40_ctrl->Load_RecipeMethod(recipe_method);
		p_e40_ctrl->Load_RecID(rcpspec);
		p_e40_ctrl->Load_PRProcessStart(process_start);
		//---------------------------------

		//---------------------------------
		int flag = p_e40_ctrl->Create_PRJob(pjobid);		

		if(flag < 0)
		{
			err_count = 1;
		}
		//---------------------------------

		//---------------------------------
		// PJOBID
		db_name.Format("-1-1-%1d",i+1);
		p_send_ctrl->Add_Ascii(db_name,pjobid);
		//---------------------------------

		//---------------------------------
		p_e40_ctrl->Get_PRJob_Error(err_code,err_text);

		// ERRCODE
		db_name.Format("-1-2-2-%1d-1",i+1);
		p_send_ctrl->Add_U1(db_name,err_code);

		// ERRTEXT
		db_name.Format("-1-2-2-%1d-2",i+1);
		p_send_ctrl->Add_Ascii(db_name,err_text);
		//---------------------------------
	}
	//-------------------------------

	// PJOB_LIMIT
	db_name = "-1-1";
	p_send_ctrl->Add_List(db_name,pjob_limit);

	//-------------------------------
	if(err_count > 0)
	{
		//-------------------------------
		// ACKA
		db_name = "-1-2-1";
		p_send_ctrl->Add_Boolean(db_name,FALSE);

		// ERROR_LIMIT
		db_name = "-1-2-2";
		p_send_ctrl->Add_List(db_name,pjob_limit);
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
void CMsg_S16Fy::Recv__F15(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
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
	int list_limit;
	int i;
	CString pjobid;
	int slot_limit;
	int vis_limit;
	int j;

	int error_count = 0;
	int err_code;
	CString err_text;

	//-------------------------------
	// LIST_LIMIT
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	list_limit = atoi(var_data);

	for(i=0;i<list_limit;i++)
	{
		p_e40_ctrl->Clear_PRJob();

		//-------------------------------
		// PJOBID
		db_name.Format("-1-2-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,pjobid);

		// CST_LIST
		int t;
		int cst_list;

		db_name.Format("-1-2-%1d-3",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		cst_list = atoi(var_data);

		for(t=0;t<cst_list;t++)
		{
			// CARRIERID
			db_name.Format("-1-2-%1d-3-%1d-1",i+1,t+1);
			p_recv_ctrl->Get_Data(db_name,var_data);
	
			p_e40_ctrl->Load_CARRIERID(var_data);

			// SLOT_LIMIT
			db_name.Format("-1-2-%1d-3-%1d-2",i+1,t+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			slot_limit = atoi(var_data);
		
			for(j=0;j<slot_limit;j++)
			{
				// SLOTID
				db_name.Format("-1-2-%1d-3-%1d-2-%1d",i+1,t+1,j+1);
				p_recv_ctrl->Get_Data(db_name,var_data);
			
				p_e40_ctrl->Load_SLOTID(atoi(var_data));
			}

			// VISION VISIT LIMIT
			db_name.Format("-1-2-%1d-3-%1d-3",i+1,t+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			vis_limit = atoi(var_data);

			for(j=0;j<vis_limit;j++)
			{
				// VISIT FLAG
				db_name.Format("-1-2-%1d-3-%1d-3-%1d",i+1,t+1,j+1);
				p_recv_ctrl->Get_Data(db_name,var_data);

				p_e40_ctrl->Load_VISION_VISIT(atoi(var_data));
			}
		}

		// RECIPE_METHOD
		db_name.Format("-1-2-%1d-4-1",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		p_e40_ctrl->Load_RecipeMethod(atoi(var_data));

		// RCPSPEC
		db_name.Format("-1-2-%1d-4-2",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		p_e40_ctrl->Load_RecID(var_data);

		// RCPPARNM_LIMIT 
		db_name.Format("-1-2-%1d-4-3",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		int rcpparnm_limit = atoi(var_data);

		for(t=0;t<rcpparnm_limit;t++)
		{
			// RCPPARNM
			db_name.Format("-1-2-%1d-4-3-%1d-1",i+1,t+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			// CARRIERID_LIST
			db_name.Format("-1-2-%1d-4-3-%1d-2",i+1,t+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			CString      carrierid;
			CUIntArray   slotid_list;
			CStringArray slotrcp_list;

			int x;
			int carrierid_list = atoi(var_data);

			for(x=0;x<carrierid_list;x++)
			{
				// CARRIERID
				db_name.Format("-1-2-%1d-4-3-%1d-2-%1d-1",i+1,t+1,x+1);
				p_recv_ctrl->Get_Data(db_name,var_data);

				carrierid = var_data;
				slotid_list.RemoveAll();
				slotrcp_list.RemoveAll();


				// MAPREAD_LIST
				db_name.Format("-1-2-%1d-4-3-%1d-2-%1d-2",i+1,t+1,x+1);
				p_recv_ctrl->Get_Data(db_name,var_data);

				int y;
				int mapread_list = atoi(var_data);

				for(y=0;y<mapread_list;y++)
				{
					// SLOTID
					db_name.Format("-1-2-%1d-4-3-%1d-2-%1d-2-%1d-1",i+1,t+1,x+1,y+1);
					p_recv_ctrl->Get_Data(db_name,var_data);

					slotid_list.Add(atoi(var_data));

					// OCR_SCRIBE
					db_name.Format("-1-2-%1d-4-3-%1d-2-%1d-2-%1d-2-1",i+1,t+1,x+1,y+1);
					p_recv_ctrl->Get_Data(db_name,var_data);

					slotrcp_list.Add(var_data);
				}

				p_e40_ctrl->Load__RCPPARNM_INFO(carrierid,slotid_list,slotrcp_list);
			}
		}

		// PROCESS-START
		db_name.Format("-1-2-%1d-5",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		var_data.MakeUpper();

		int start_method;
		if(var_data == "FF")		start_method = 1;
		else						start_method = atoi(var_data);

		p_e40_ctrl->Load_PRProcessStart(start_method);
		//-------------------------------

		//----------------------------------------
		int flag = p_e40_ctrl->Create_PRJob(pjobid);

		if(flag < 0)
		{
			error_count = 1;
		}
		//----------------------------------------

		//----------------------------------------
		// PJOBID
		db_name.Format("-1-1-%1d",i+1);
		p_send_ctrl->Add_Ascii(db_name,pjobid);

		p_e40_ctrl->Get_PRJob_Error(err_code,err_text);

		// ERRCODE
		db_name.Format("-1-2-2-%1d-1",i+1);
		p_send_ctrl->Add_U1(db_name,err_code);

		// ERRTEXT
		db_name.Format("-1-2-2-%1d-2",i+1);
		p_send_ctrl->Add_Ascii(db_name,err_text);
		//----------------------------------------
	}
	//-------------------------------

	//-------------------------------
	// PJ_LIMIT
	db_name = "-1-1";
	p_send_ctrl->Add_List(db_name,list_limit);

	if(error_count > 0)
	{
		//-------------------------------
		// ACKA
		db_name = "-1-2-1";
		p_send_ctrl->Add_Boolean(db_name,FALSE);

		// ERROR_LIMIT
		db_name = "-1-2-2";
		p_send_ctrl->Add_List(db_name,list_limit);
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
