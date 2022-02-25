#include "StdAFx.h"
#include "Macro_FNC.h"

#include "MSG_S15Fy.h"
CMsg_S15Fy mMSG_S15Fy;


//----------------------------------------------------------------------------
CMsg_S15Fy::CMsg_S15Fy()
{
	iSx = 15;
}

void CMsg_S15Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	/*
	switch(p_bridge_ctrl->iFy)
	{
	}
	*/
}

void CMsg_S15Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	switch(p_bridge_ctrl->iFy)
	{
		case 3:		Recv__F3(p_bridge_ctrl);		return;
		case 5:		Recv__F5(p_bridge_ctrl);		return;

		case 19:	Recv__F19(p_bridge_ctrl);		return;
	}
}


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void CMsg_S15Fy::Recv__F3(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	SCX__FILE_ROUTE_CTRL xFile_Route_Ctrl;

	CString db_name;
	CString var_data;

	//-------------------------------
	CString rmnsspec;
	int rmnscmd;
	int rmack;
    int err_list;
	int errcode;
	CString errtext;

	//-------------------------------
	CString rte_path;
	CString dir_route;

	p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Route(dir_route);

	//-------------------------------
	// RMNSSPEC
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	rmnsspec = var_data;

	// RMNSCMD
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	rmnscmd = atoi(var_data);
	//-------------------------------

	//-------------------------------
	err_list = 0;
	errcode  = 0;

	rte_path  = dir_route;
	rte_path += rmnsspec;
	rte_path += ".rte";
	//-------------------------------

	switch(rmnscmd)
	{
		case 5:		// Delete
			if(xFile_Route_Ctrl->Delete__FILE(rte_path) < 0)
			{
				err_list = 1;
			}
			break;

		default:
			err_list = 1;
			break;
	}

	// ERR_LIST
	db_name = "-1-2";
	p_send_ctrl->Add_List(db_name,err_list);

	if(err_list > 0)
	{
		rmack = 1;
		if(errcode < 1)		errcode = 4;

		Macro__Get_ERRTEXT_From_ERRCODE(errcode,errtext);

		// ERRCODE
		db_name = "-1-2-1-1";
		p_send_ctrl->Add_U4(db_name,errcode);

		// ERRTEXT
		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,errtext);
	}
	else
	{
		rmack = 0;
	}

	// RMACK
	db_name = "-1-1";
	p_send_ctrl->Add_U1(db_name,rmack);
	//-------------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}

void CMsg_S15Fy::Recv__F5(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	SCX__FILE_ROUTE_CTRL xFile_Route_Ctrl;

	CString db_name;
	CString var_data;

	//-------------------------------
	CString rmnsspec;
	CString rmnewns;
	int rmack;
    int err_list;
	int errcode;
	CString errtext;

	//-------------------------------
	CString dir_route;
	CString src_path;
	CString trg_path;

	p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Route(dir_route);

	//-------------------------------
	// RMNSSPEC
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	rmnsspec = var_data;

	// RMNEWNS
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	rmnewns = var_data;
	//-------------------------------

	//-------------------------------
	err_list = 0;
	errcode  = 0;

	src_path  = dir_route;
	src_path += rmnsspec;
	src_path += ".rte";

	trg_path  = dir_route;
	trg_path += rmnewns;
	trg_path += ".rte";
	//-------------------------------

	if((xFile_Route_Ctrl->Check__FILE(src_path) < 0)
	|| (xFile_Route_Ctrl->Check__FILE(trg_path) > 0))
	{
		err_list = 1;
		errcode  = 3;
	}

	if(err_list < 1)
	{
		if(xFile_Route_Ctrl->Rename__FILE(src_path,trg_path) < 0)
		{
			err_list = 1;
		}
	}

	//-------------------------------
	// ERR_LIST
	db_name = "-1-2";
	p_send_ctrl->Add_List(db_name,err_list);

	if(err_list > 0)
	{
		rmack = 1;
		if(errcode < 1)		errcode = 4;

		Macro__Get_ERRTEXT_From_ERRCODE(errcode,errtext);

		// ERRCODE
		db_name = "-1-2-1-1";
		p_send_ctrl->Add_U4(db_name,errcode);

		// ERRTEXT
		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,errtext);
	}
	else
	{
		rmack = 0;
	}

	// RMACK
	db_name = "-1-1";
	p_send_ctrl->Add_U1(db_name,rmack);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}

void CMsg_S15Fy::Recv__F19(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	SCX__FILE_ROUTE_CTRL xFile_Route_Ctrl;

	CString db_name;
	CString var_data;

	//-------------------------------
	CString rcpspec;
	int rcprename_flag;
	CString rcpnewid;
	int rmack;
    int err_list;
	int errcode;
	CString errtext;

	//-------------------------------
	CString dir_route;
	CString src_path;
	CString trg_path;

	p_bridge_ctrl->pRES_SEQ_INFO->Get__Dir_Route(dir_route);

	//-------------------------------
	// RCPSPEC
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	rcpspec = var_data;

	// RCPRENAME
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	rcprename_flag = atoi(var_data); 

	// RCPNEWID
	db_name = "-1-3";
	p_recv_ctrl->Get_Data(db_name,var_data);

	rcpnewid = var_data;
	//-------------------------------

	//-------------------------------
	err_list = 0;
	errcode  = 0;

	src_path  = dir_route;
	src_path += rcpspec;
	src_path += ".rte";

	trg_path  = dir_route;
	trg_path += rcpnewid;
	trg_path += ".rte";
	//-------------------------------

	if(src_path != trg_path)
	{
		if((xFile_Route_Ctrl->Check__FILE(src_path) < 0)
		|| (xFile_Route_Ctrl->Check__FILE(trg_path) > 0))
		{
			err_list = 1;
			errcode  = 3;
		}
	}
	else
	{
		err_list = 1;
		errcode  = 7;
	}

	if(err_list < 1)
	{
		if(rcprename_flag > 0)
		{
			if(xFile_Route_Ctrl->Rename__FILE(src_path,trg_path) < 0)
			{
				err_list = 1;
			}
		}
		else
		{
			if(xFile_Route_Ctrl->Copy__FILE(src_path,trg_path) < 0)
			{
				err_list = 1;
			}
		}

		if(err_list > 0)
		{
			errcode = 4;
		}
	}

	//-------------------------------
	// ERR_LIST
	db_name = "-1-2";
	p_send_ctrl->Add_List(db_name,err_list);

	if(err_list > 0)
	{
		rmack = 1;
		if(errcode < 1)		errcode = 4;

		Macro__Get_ERRTEXT_From_ERRCODE(errcode,errtext);

		// ERRCODE
		db_name = "-1-2-1-1";
		p_send_ctrl->Add_U4(db_name,errcode);

		// ERRTEXT
		db_name = "-1-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,errtext);
	}
	else
	{
		rmack = 0;
	}

	// RMACK
	db_name = "-1-1";
	p_send_ctrl->Add_U1(db_name,rmack);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
