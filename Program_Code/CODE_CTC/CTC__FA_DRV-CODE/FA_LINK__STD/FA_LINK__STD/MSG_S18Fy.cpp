#include "StdAFx.h"

#include "MSG_S18Fy.h"
CMsg_S18Fy mMSG_S18Fy;


//----------------------------------------------------------------------------
CMsg_S18Fy::CMsg_S18Fy()
{
	iSx = 18;
}

void CMsg_S18Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)				return;

	/*
	switch(p_bridge_ctrl->iFy)
	{
	}
	*/
}

void CMsg_S18Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)				return;

	switch(p_bridge_ctrl->iFy)
	{
		case 5:		Recv__F5(p_bridge_ctrl);	return;
		case 7:		Recv__F7(p_bridge_ctrl);	return;
		case 9:		Recv__F9(p_bridge_ctrl);	return;
		case 11:	Recv__F11(p_bridge_ctrl);	return;
	}
}


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void CMsg_S18Fy::Recv__F5(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CString db_name;
	CString var_data;

	//-------------------------------
	int ptn_id   = 0;
	int data_seg = 0;
	int data_len = 0;

	//-------------------------------
	// TARGETID
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	ptn_id = atoi(var_data);

	// DATASEG
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	data_seg = atoi(var_data);

	// DATALENGTH
	db_name = "-1-3";
	p_recv_ctrl->Get_Data(db_name,var_data);

	data_len = atoi(var_data);
	//-------------------------------

	CI_FA_300mm__E30_CTRL *p_e30_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	CString data_page;
	int ssack = 0;
	CString status;

	int flag = p_e30_ctrl->Read_LP__PAGE(ptn_id,data_seg,data_len,5,data_page);

	if(flag < 0)
	{
		ssack = 1;
		data_page = "";

		if(flag != -1)  	status = "Execution Error";
	}
	else 
	{
		status = "Normal Operation";
	}

	//-------------------------------
	// TARGETID
	db_name = "-1-1";
	p_send_ctrl->Add_U1(db_name,ptn_id);

	// SSACK
	db_name = "-1-2";
	p_send_ctrl->Add_U1(db_name,ssack);

	// DATA
	db_name = "-1-3";
	p_send_ctrl->Add_Ascii(db_name,data_page);

	if(status.GetLength() > 0)
	{
		// LIST_LIMIT
		db_name = "-1-4";
		p_send_ctrl->Add_List(db_name,1);

		// STATUS
		db_name = "-1-4-1";
		p_send_ctrl->Add_Ascii(db_name,status);
	}
	else
	{
		// LIST_LIMIT
		db_name = "-1-4";
		p_send_ctrl->Add_List(db_name,0);
	}
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S18Fy::Recv__F7(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CString db_name;
	CString var_data;

	//-------------------------------
	int ptn_id   = 0;
	int data_seg = 0;
	int data_len = 0;
	CString data_page;

	//-------------------------------
	// TARGETID
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	ptn_id = atoi(var_data);

	// DATASEG
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	data_seg = atoi(var_data);

	// DATALENGTH
	db_name = "-1-3";
	p_recv_ctrl->Get_Data(db_name,var_data);

	data_len = atoi(var_data);

	// DATA
	db_name = "-1-4";
	p_recv_ctrl->Get_Data(db_name,data_page);
	//-------------------------------

	CI_FA_300mm__E30_CTRL *p_e30_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	int ssack = 0;
	CString status;

	int flag = p_e30_ctrl->Write_LP__PAGE(ptn_id,data_seg,data_len,5,data_page);

	if(flag < 0)
	{
		ssack = 1;
		
		if(flag != -1)  	status = "Execution Error";
	}
	else 
	{
		status = "Normal Operation";
	}

	//-------------------------------
	// TARGETID
	db_name = "-1-1";
	p_send_ctrl->Add_U1(db_name,ptn_id);

	// SSACK
	db_name = "-1-2";
	p_send_ctrl->Add_U1(db_name,ssack);

	if(status.GetLength() > 0)
	{
		// LIST_LIMIT
		db_name = "-1-3";
		p_send_ctrl->Add_List(db_name,1);

		// STATUS
		db_name = "-1-3-1";
		p_send_ctrl->Add_Ascii(db_name,status);
	}
	else
	{
		// LIST_LIMIT
		db_name = "-1-4";
		p_send_ctrl->Add_List(db_name,0);
	}
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S18Fy::Recv__F9(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CString db_name;
	CString var_data;

	//-------------------------------
	int ptn_id = 0;

	//-------------------------------
	// TARGETID
	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	ptn_id = atoi(var_data);
	//-------------------------------

	CI_FA_300mm__E30_CTRL *p_e30_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	CString data_page;
	int ssack = 0;
	CString status;

	int flag = p_e30_ctrl->Read_LP__CID(ptn_id,3,data_page);

	if(flag < 0)
	{
		ssack = 1;
		data_page = "";

		if(flag != -1)  	status = "Execution Error";
	}
	else 
	{
		status = "Normal Operation";
	}

	//-------------------------------
	// TARGETID
	db_name = "-1-1";
	p_send_ctrl->Add_U1(db_name,ptn_id);

	// SSACK
	db_name = "-1-2";
	p_send_ctrl->Add_U1(db_name,ssack);

	// MID
	db_name = "-1-3";
	p_send_ctrl->Add_Ascii(db_name,data_page);

	if(status.GetLength() > 0)
	{
		// LIST_LIMIT
		db_name = "-1-4";
		p_send_ctrl->Add_List(db_name,1);

		// STATUS
		db_name = "-1-4-1";
		p_send_ctrl->Add_Ascii(db_name,status);
	}
	else
	{
		// LIST_LIMIT
		db_name = "-1-4";
		p_send_ctrl->Add_List(db_name,0);
	}
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S18Fy::Recv__F11(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CString db_name;
	CString var_data;

	//-------------------------------
	int ptn_id   = 0;
	CString mid;

	//-------------------------------
	// TARGETID
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	ptn_id = atoi(var_data);

	// MID
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,mid);
	//-------------------------------

	CI_FA_300mm__E30_CTRL *p_e30_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	int ssack = 0;
	CString status;

	int flag = p_e30_ctrl->Write_LP__CID(ptn_id,3,mid);

	if(flag < 0)
	{
		ssack = 1;

		if(flag != -1)  	status = "Execution Error";
	}
	else 
	{
		status = "Normal Operation";
	}

	//-------------------------------
	// TARGETID
	db_name = "-1-1";
	p_send_ctrl->Add_U1(db_name,ptn_id);

	// SSACK
	db_name = "-1-2";
	p_send_ctrl->Add_U1(db_name,ssack);

	if(status.GetLength() > 0)
	{
		// LIST_LIMIT
		db_name = "-1-3";
		p_send_ctrl->Add_List(db_name,1);

		// STATUS
		db_name = "-1-3-1";
		p_send_ctrl->Add_Ascii(db_name,status);
	}
	else
	{
		// LIST_LIMIT
		db_name = "-1-4";
		p_send_ctrl->Add_List(db_name,0);
	}
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
