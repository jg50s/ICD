#include "StdAFx.h"
#include "MSG_S03Fy.h"


CMsg_S03Fy mMSG_S03Fy;


//----------------------------------------------------------------------------
CMsg_S03Fy::CMsg_S03Fy()
{
	iSx = 3;
}

void CMsg_S03Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	/*
	switch(p_bridge_ctrl->iFy)
	{
		
	}
	*/
}

void CMsg_S03Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	int type = p_bridge_ctrl->iType;

	switch(p_bridge_ctrl->iFy)
	{
		case 17:
			{
					 if(type == 0)		Recv__F17_0(p_bridge_ctrl);
				else if(type == 1)		Recv__F17_1(p_bridge_ctrl);
				else if(type == 2)		Recv__F17_2(p_bridge_ctrl);
			}
			return;
		
		case 25:	Recv__F25(p_bridge_ctrl);		return;
		case 27:	Recv__F27(p_bridge_ctrl);		return;

			// Carrier Tag Read
		case 29:	Recv__F29(p_bridge_ctrl);		return;		
			// Carrier Tag Write
		case 31:	Recv__F31(p_bridge_ctrl);		return;
	}
}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void CMsg_S03Fy::Recv__F17_0(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	//-----------------------------
	// RECV-MSG

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E87_CTRL *p_e87_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E87();

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
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,1);
		
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,1);

		db_name = "-1-2-1-1";
		p_send_ctrl->Add_U1(db_name,err_code);

		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
		//-------------------------------

		p_bridge_ctrl->pFA_DRV_CTRL->Send();

		FA__OK;
	}
	//----------------------------------------------------------------

	//-----------------------------
	CDS_CASSETTE_INFO ds_cst_info;
	int i;
	int limit;

	// CARRIER_ACTION
	db_name.Format("-1-2");
	p_recv_ctrl->Get_Data(db_name,var_data);
	
	ds_cst_info.sCARRIER_ACTION = var_data;
	
	// CARRIERID
	db_name.Format("-1-3");
	p_recv_ctrl->Get_Data(db_name,var_data);
	
	ds_cst_info.sCARRIER_ID = var_data;

	// PTN
	db_name.Format("-1-4");
	p_recv_ctrl->Get_Data(db_name,var_data);
	
	ds_cst_info.iPTN = atoi(var_data);

	// CAPACITY 
	db_name = "-1-5-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	ds_cst_info.iCAPACITY = atoi(var_data);

	// SUBSTRATE_COUNT
	db_name = "-1-5-2-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	ds_cst_info.iSUBSTRATE_COUNT = atoi(var_data);

	// USAGE
	db_name = "-1-5-3-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	ds_cst_info.sUSAGE = var_data;

	// MAP_LIMIT
	db_name.Format("-1-5-4-2");
	p_recv_ctrl->Get_Data(db_name,var_data);
	limit = atoi(var_data);
	if(limit > 30)	limit = 30;
	if(limit < 0)	limit = 0;
	ds_cst_info.iSLOTMAP_LIMIT = limit;

	for(i=0;i<limit;i++)
	{
		// SLOTMAP
		db_name.Format("-1-5-4-2-%1d",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);
		ds_cst_info.sSLOTMAP_LIST.Add(var_data);
	}

	// CONTENT_LIMIT
	db_name.Format("-1-5-5-2");
	p_recv_ctrl->Get_Data(db_name,var_data);

	limit = atoi(var_data);
	if(limit > 30)	limit = 30;
	if(limit < 0)	limit = 0;
	ds_cst_info.iCONTENT_LIMIT = limit;
	
	for(i=0;i<limit;i++)
	{
		// LOTID
		db_name.Format("-1-5-5-2-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);
		ds_cst_info.sLOTID_LIST.Add(var_data);		

		// WAFERID
		db_name.Format("-1-5-5-2-%1d-2",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);
		ds_cst_info.sWAFERID_LIST.Add(var_data);
	}

	// WID_ANGLE_LIMIT
	db_name.Format("-1-5-6-2");
	p_recv_ctrl->Get_Data(db_name,var_data);

	limit = atoi(var_data);
	if(limit > 30)	limit = 30;
	if(limit < 0)	limit = 0;
	ds_cst_info.iWID_ANGLG_LIMIT = limit;
	
	for(i=0;i<limit;i++)
	{
		// WID_Angle
		db_name.Format("-1-5-6-2-%1d",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);
		ds_cst_info.sWID_ANGLE_LIST.Add(var_data);
	}
	//-----------------------------

	//----------------------------------------------------------
	//-----------------------------
	// SEND-MSG

	//-----------------------------
	int flag = p_e87_ctrl->Load(ds_cst_info);
	if(flag > 0)
	{
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,0);
		
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,0);


		//---------------------------------------------------------
		CString path;
		CString dir_process;
		CString carrier_action = ds_cst_info.sCARRIER_ACTION;
		int     ptn = ds_cst_info.iPTN;

		p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Process(dir_process);

		path.Format("%s\\LP%1d\\LP%1d_LocalJOB.css",
					dir_process,
					ptn,
					ptn);

		carrier_action.MakeUpper();

		if(carrier_action.CompareNoCase("PROCEEDWITHCARRIER") == 0)
		{
			printf(" ** path <- [%s] \n", path);

			p_e87_ctrl->Create__LocalJOB(path,ds_cst_info);
		}

		_Make__CMS_LOG(ds_cst_info);
		//---------------------------------------------------------
	}
	else
	{
		int     err_code;
		CString err_text;

		p_e87_ctrl->Get_E87_Error(err_code,err_text);
		
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,1);
		
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,1);

		db_name = "-1-2-1-1";
		p_send_ctrl->Add_U1(db_name,err_code);

		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
	}
	//-----------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}
void CMsg_S03Fy::Recv__F17_1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	//-----------------------------
	// RECV-MSG

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;
	
	CI_FA_300mm__E87_CTRL *p_e87_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E87();

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
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,1);
		
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,1);

		db_name = "-1-2-1-1";
		p_send_ctrl->Add_U1(db_name,err_code);

		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
		//-------------------------------

		p_bridge_ctrl->pFA_DRV_CTRL->Send();

		FA__OK;
	}
	//----------------------------------------------------------------

	//-----------------------------
	CDS_CASSETTE_INFO ds_cst_info;

	// CARRIER_ACTION
	db_name.Format("-1-2");
	p_recv_ctrl->Get_Data(db_name,var_data);
	
	ds_cst_info.sCARRIER_ACTION = var_data;

	// CARRIERID
	db_name.Format("-1-3");
	p_recv_ctrl->Get_Data(db_name,var_data);
	
	ds_cst_info.sCARRIER_ID = var_data;

	// PTN
	db_name.Format("-1-4");
	p_recv_ctrl->Get_Data(db_name,var_data);
	
	ds_cst_info.iPTN = atoi(var_data);
	//-----------------------------

	//----------------------------------------------------------
	//-----------------------------
	// SEND-MSG

	//-----------------------------
	int flag = p_e87_ctrl->Load(ds_cst_info);

	if(flag > 0)
	{
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,0);
		
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,0);
	}
	else
	{
		int     err_code;
		CString err_text;

		p_e87_ctrl->Get_E87_Error(err_code,err_text);
		
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,1);
		
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,1);

		db_name = "-1-2-1-1";
		p_send_ctrl->Add_U1(db_name,err_code);

		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
	}
	//-----------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}
void CMsg_S03Fy::Recv__F17_2(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	//-----------------------------
	// RECV-MSG

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E87_CTRL *p_e87_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E87();

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
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,1);
		
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,1);

		db_name = "-1-2-1-1";
		p_send_ctrl->Add_U1(db_name,err_code);

		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
		//-------------------------------

		p_bridge_ctrl->pFA_DRV_CTRL->Send();

		FA__OK;
	}
	//----------------------------------------------------------------

	//-----------------------------
	CDS_CASSETTE_INFO ds_cst_info;
	int i;
	int limit;

	// CARRIER_ACTION
	db_name.Format("-1-2");
	p_recv_ctrl->Get_Data(db_name,var_data);
	
	ds_cst_info.sCARRIER_ACTION = var_data;
	
	// CARRIERID
	db_name.Format("-1-3");
	p_recv_ctrl->Get_Data(db_name,var_data);
	
	ds_cst_info.sCARRIER_ID = var_data;

	// PTN
	db_name.Format("-1-4");
	p_recv_ctrl->Get_Data(db_name,var_data);
	
	ds_cst_info.iPTN = atoi(var_data);

	// CONTENT_LIMIT
	db_name.Format("-1-5-1-2");
	p_recv_ctrl->Get_Data(db_name,var_data);

	limit = atoi(var_data);
	if(limit > 30)	limit = 30;
	if(limit < 0)	limit = 0;
	ds_cst_info.iCONTENT_LIMIT = limit;
	
	for(i=0;i<limit;i++)
	{
		// LOTID
		db_name.Format("-1-5-1-2-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);
		ds_cst_info.sLOTID_LIST.Add(var_data);		

		// WAFERID
		db_name.Format("-1-5-1-2-%1d-2",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);
		ds_cst_info.sWAFERID_LIST.Add(var_data);
	}

	ds_cst_info.iWID_ANGLG_LIMIT = 0;
	//-----------------------------

	//----------------------------------------------------------
	//-----------------------------
	// SEND-MSG

	//-----------------------------
	int flag = p_e87_ctrl->Load(ds_cst_info);

	if(flag > 0)
	{
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,0);
		
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,0);

		//---------------------------------------------------------
		CString path;
		CString dir_process;
		CString carrier_action = ds_cst_info.sCARRIER_ACTION;
		int     ptn = ds_cst_info.iPTN;

		p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Process(dir_process);

		path.Format("%s\\LP%1d\\LP%1d_LocalJOB.css",
					dir_process,
					ptn,
					ptn);

		carrier_action.MakeUpper();

		if(carrier_action.CompareNoCase("PROCEEDWITHCARRIER") == 0)
		{
			printf(" ** path <- [%s] \n", path);

			p_e87_ctrl->Create__LocalJOB(path,ds_cst_info);
		}

		_Make__CMS_LOG(ds_cst_info);
		//---------------------------------------------------------
	}
	else
	{
		int     err_code;
		CString err_text;

		p_e87_ctrl->Get_E87_Error(err_code,err_text);
		
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,1);
		
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,1);

		db_name = "-1-2-1-1";
		p_send_ctrl->Add_U1(db_name,err_code);

		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
	}
	//-----------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}

void CMsg_S03Fy::Recv__F25(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	//-----------------------------
	// RECV-MSG

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E87_CTRL *p_e87_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E87();

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
		// CAACK
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,2);

		// LIST_LIMIT
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,1);

		// ERRCODE
		db_name = "-1-2-1-1";
		p_send_ctrl->Add_U1(db_name,err_code);

		// ERRTEXT
		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
		//-------------------------------

		p_bridge_ctrl->pFA_DRV_CTRL->Send();

		FA__OK;
	}
	//----------------------------------------------------------------

	//-----------------------------
	CString port_action;
	int ptn;

	//-----------------------------
	// PORT-ACTION
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,port_action);

	// PTN
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	ptn = atoi(var_data);
	//-------------------------------
	
	//-------------------------------
	port_action.MakeUpper();

	int flag = -1;
	int caack = 1;

	if(port_action == "IN SERVICE")
	{
		flag = p_e87_ctrl->Set_Transfer__IN_SERVICE(ptn);

		if(flag < 0)	caack = -flag;
	}
	else if(port_action == "OUT OF SERVICE")
	{
		flag = p_e87_ctrl->Set_Transfer__OUT_OF_SERVICE(ptn);

		if(flag < 0)	caack = -flag;
	}
	else if(port_action == "RESERVEATPORT")
	{
		flag = p_e87_ctrl->Set_PTN_CTRL__ReserveAtPort(ptn);
	}
	else if(port_action == "CANCELRESERVATIONATPORT")
	{
		flag = p_e87_ctrl->Set_PTN_CTRL__CancelReservationAtPort(ptn);
	}

	if(flag > 0)
	{
		// CAACK
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,0);

		// LIST_LIMIT
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,0);
	}
	else
	{
		int     err_code;
		CString err_text;

		p_e87_ctrl->Get_E87_Error(err_code,err_text);

		// CAACK
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,caack);

		// LIST_LIMIT
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,1);

		// ERRCODE
		db_name = "-1-2-1-1";
		p_send_ctrl->Add_U1(db_name,err_code);

		// ERRTEXT
		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);

	}
	//-----------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}
void CMsg_S03Fy::Recv__F27(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	//-----------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E87_CTRL *p_e87_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E87();

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
		// CAACK
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,2);

		// LIST_LIMIT
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,1);

		// ERRCODE
		db_name = "-1-2-1-1";
		p_send_ctrl->Add_U1(db_name,err_code);

		// ERRTEXT
		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
		//-------------------------------

		p_bridge_ctrl->pFA_DRV_CTRL->Send();

		FA__OK;
	}
	//----------------------------------------------------------------

	//-----------------------------
	int access_mode;
	CUIntArray ptn_list;
	int i;
	int limit;

	// ACCESS_MODE
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	access_mode = atoi(var_data);

	// PORT_LIMIT
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	limit = atoi(var_data);
	
	for(i=0;i<limit;i++)
	{
		// PTN
		db_name.Format("-1-2-%1d",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		ptn_list.Add(atoi(var_data));
	}
	//-------------------------------

	//-------------------------------
	int flag;
	int err_code = 0;
	int ptn;
	int err_count = 0;
	int e_code;
	CString e_text;

	if(limit == 0)
	{
		limit = 5;
		ptn_list.RemoveAll();
			
		for(i=0;i<5;i++)
		{
			ptn_list.Add(i+1);
		}
	}

	for(i=0;i<limit;i++)
	{
		ptn = ptn_list[i];

		flag = 1;

		if(access_mode == 0)			// MANUAL
		{
			flag = p_e87_ctrl->Set_AccessMode__MANUAL(ptn);
		}
		else if(access_mode == 1)		// AUTO
		{
			flag = p_e87_ctrl->Set_AccessMode__AUTO(ptn);
		}
		else
		{
			flag = -1;
		}

		if(flag >= 0)	continue;

		
		e_code = -flag;

		switch(e_code)
		{
			case 1:		e_text = "Invalid command";
				break;

			case 2:		e_text = "Can not perform now";
				break;

			case 3:		e_text = "Invalid data or argument";
				break;

			case 4:		e_text = "Acknowledge, request will be perfomed with completion signaled later by an event.";
				break;

			case 5:		e_text = "Rejected. Invalid state.";
				break;

			case 6:		e_text = "Command performed with errors.";
				break;

			default:	e_text = "Unknown Error";
				break;
		}

		err_count++;

		// ERROR_LIMIT
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,err_count);

		// PTN
		db_name.Format("-1-2-%1d-1",err_count);
		p_send_ctrl->Add_U1(db_name,ptn);

		// ERR_CODE
		db_name.Format("-1-2-%1d-2",err_count);
		p_send_ctrl->Add_U1(db_name,e_code);

		// ERR_TEXT
		db_name.Format("-1-2-%1d-3",err_count);
		p_send_ctrl->Add_Ascii(db_name,e_text);
	}

	// CAACK
	db_name = "-1-1";

	if(err_count > 0)		err_code = 1;
	else 					err_code = 0;
	
	p_send_ctrl->Add_U1(db_name,err_code);

	// ERROR_LIMIT
	db_name = "-1-2";
	p_send_ctrl->Add_List(db_name,err_count);
	//-----------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}

void CMsg_S03Fy::Recv__F29(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	//-----------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E87_CTRL *p_e87_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E87();

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
		// DATA
		db_name = "-1-1";
		p_send_ctrl->Add_Ascii(db_name,"");

		// CAACK
		db_name = "-1-2-1";
		p_send_ctrl->Add_U1(db_name,2);

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

	//-----------------------------
	CString locid;
	CString carrierspec;
	CString dataseg;
	int datalen;

	// LOCID
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	locid = var_data;

	// CARRIERSPEC
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	carrierspec = var_data;

	// DATASEG
	db_name = "-1-3";
	p_recv_ctrl->Get_Data(db_name,var_data);

	dataseg = var_data;

	// DATALENGTH
	db_name = "-1-4";
	p_recv_ctrl->Get_Data(db_name,var_data);

	datalen = atoi(var_data);
	//-------------------------------

	//-------------------------------
	int flag;
	int e_code;
	CString e_text;
	CString tag_data;

	flag = p_e87_ctrl->Read__CarrierTag(locid,carrierspec,dataseg,datalen,tag_data);
	e_code = -flag;

	if(flag > 0)
	{
		// DATA
		db_name = "-1-1";
		p_send_ctrl->Add_Ascii(db_name,tag_data);

		// CAACK
		db_name = "-1-2-1";
		p_send_ctrl->Add_U1(db_name,0);

		// ERROR_LIMIT
		db_name = "-1-2-2";
		p_send_ctrl->Add_List(db_name,0);
	}
	else
	{
		switch(e_code)
		{
			case 1:		e_text = "Invalid command";
				break;

			case 2:		e_text = "Can not perform now";
				break;

			case 3:		e_text = "Invalid data or argument";
				break;

			case 4:		e_text = "Acknowledge, request will be perfomed with completion signaled later by an event.";
				break;

			case 5:		e_text = "Rejected. Invalid state.";
				break;

			case 6:		e_text = "Command performed with errors.";
				break;

			default:	e_text = "Unknown Error";
				break;
		}

		// DATA
		db_name = "-1-1";
		p_send_ctrl->Add_Ascii(db_name,"");

		// CAACK
		db_name = "-1-2-1";
		p_send_ctrl->Add_U1(db_name,1);

		// ERROR_LIMIT
		db_name = "-1-2-2";
		p_send_ctrl->Add_List(db_name,1);

		// ERRCODE
		db_name = "-1-2-2-1-1";
		p_send_ctrl->Add_U1(db_name,e_code);

		// ERRTEXT
		db_name = "-1-2-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,e_text);
	}
	//-----------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}

void CMsg_S03Fy::Recv__F31(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	//-----------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E87_CTRL *p_e87_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E87();

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
		// CAACK
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,2);

		// ERROR_LIMIT
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,1);

		// ERRCODE
		db_name = "-1-2-1-1";
		p_send_ctrl->Add_U1(db_name,err_code);

		// ERRTEXT
		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
		//-------------------------------

		p_bridge_ctrl->pFA_DRV_CTRL->Send();

		FA__OK;
	}
	//----------------------------------------------------------------

	//-----------------------------
	CString locid;
	CString carrierspec;
	CString dataseg;
	int datalen;
	CString tag_data;

	// LOCID
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	locid = var_data;

	// CARRIERSPEC
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	carrierspec = var_data;

	// DATASEG
	db_name = "-1-3";
	p_recv_ctrl->Get_Data(db_name,var_data);

	dataseg = var_data;

	// DATALENGTH
	db_name = "-1-4";
	p_recv_ctrl->Get_Data(db_name,var_data);

	datalen = atoi(var_data);

	// DATA
	db_name = "-1-5";
	p_recv_ctrl->Get_Data(db_name,var_data);

	tag_data = var_data;
	//-------------------------------

	//-------------------------------
	int flag;
	int e_code;
	CString e_text;

	flag = p_e87_ctrl->Write__CarrierTag(locid,carrierspec,dataseg,datalen,tag_data);
	e_code = -flag;

	if(flag > 0)
	{
		// CAACK
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,0);

		// ERROR_LIMIT
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,0);
	}
	else
	{
		switch(e_code)
		{
			case 1:		e_text = "Invalid command";
				break;

			case 2:		e_text = "Can not perform now";
				break;

			case 3:		e_text = "Invalid data or argument";
				break;

			case 4:		e_text = "Acknowledge, request will be perfomed with completion signaled later by an event.";
				break;

			case 5:		e_text = "Rejected. Invalid state.";
				break;

			case 6:		e_text = "Command performed with errors.";
				break;

			default:	e_text = "Unknown Error";
				break;
		}

		// CAACK
		db_name = "-1-1";
		p_send_ctrl->Add_U1(db_name,1);

		// ERROR_LIMIT
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,1);

		// ERRCODE
		db_name = "-1-2-1-1";
		p_send_ctrl->Add_U1(db_name,e_code);

		// ERRTEXT
		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,e_text);
	}
	//-----------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}
