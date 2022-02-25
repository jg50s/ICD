#include "StdAFx.h"
#include "MSG_S10Fy.h"


CMsg_S10Fy mMSG_S10Fy;


//----------------------------------------------------------------------------
CMsg_S10Fy::CMsg_S10Fy()
{
	iSx = 10;
}

void CMsg_S10Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)		return;

	switch(p_bridge_ctrl->iFy)
	{
		case 1:		Send__F1(p_bridge_ctrl);		return;
		case 7:		Send__F7(p_bridge_ctrl);		return;
	}
}

void CMsg_S10Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)		return;

	switch(p_bridge_ctrl->iFy)
	{
		case 3:		Recv__F3(p_bridge_ctrl);		return;
		case 5:		Recv__F5(p_bridge_ctrl);		return;
		case 9:		Recv__F9(p_bridge_ctrl);		return;
	}
}


//----------------------------------------------------------------------------
void CMsg_S10Fy::Send__F1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl = p_bridge_ctrl->pMSG_SEND_CTRL;
	CI_FA_VARIABLE_CTRL  *p_variable_ctrl = p_bridge_ctrl->pRES_VARIABLE_CTRL;

	//-------------------------------
	CString db_name;

	CString main_name;
	CString sub_name;

	int tid;
	CString text;


	main_name = "##S10F1";
	sub_name  = "TEXT";
	p_variable_ctrl->Get_Variable(main_name,sub_name,text);
	//-------------------------------

	//-------------------------------
	// TID;
	tid = 0;
	db_name = "-1-1";
	p_send_ctrl->Add_Binary(db_name,tid);

	// TEXT
	db_name = "-1-2";
	p_send_ctrl->Add_Ascii(db_name,text);
	//-------------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	//--------------------------------------------
	if(p_bridge_ctrl->iReply < 0)						FA__OK;
	if(p_bridge_ctrl->pFA_DRV_CTRL->Is_Recv() < 0)		FA__ERROR;

	//--------------------------------------------

	FA__OK;
}
void CMsg_S10Fy::Send__F7(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl = p_bridge_ctrl->pMSG_SEND_CTRL;

	//-------------------------------
	CString db_name;

	int tid;


	//-------------------------------
	// TID;

	tid = 0;
	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,tid);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	//--------------------------------------------
	if(p_bridge_ctrl->iReply < 0)						FA__OK;
	if(p_bridge_ctrl->pFA_DRV_CTRL->Is_Recv() < 0)		FA__ERROR;

	//--------------------------------------------

	FA__OK;
}

//----------------------------------------------------------------------------
void CMsg_S10Fy::Recv__F3(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl = p_bridge_ctrl->pMSG_SEND_CTRL;
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl = p_bridge_ctrl->pMSG_RECV_CTRL;
	CI_FA_VARIABLE_CTRL  *p_variable_ctrl = p_bridge_ctrl->pRES_VARIABLE_CTRL;

	CString	db_name;

	CString tid;
	CString text;

	//-------------------------------
	// TID
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,tid);

	// TEXT
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,text);
	//-------------------------------

	//.....
	int tid_check_flag = 1;

	//...
	{
		CString main_name = "S10Fy.TID";
		CString sub_name  = "CHECK.FLAG";
		CString var_data;

		p_variable_ctrl->Get_Variable(main_name,sub_name,var_data);

		if(var_data.CompareNoCase("NO") == 0)
		{
			tid_check_flag = -1;
		}
	}

	//.....
	int acka10 = 0;

	if((atoi(tid) == 0) || (tid_check_flag < 0))	
	{
		//-------------------------------
		CString main_name;
		CString sub_name;
		CString var_data;

		main_name = "##S10F3";

		// TID
		sub_name = "TID";
		var_data = tid;
		p_variable_ctrl->Set_Variable(main_name,sub_name,var_data);

		// TEXT
		sub_name = "TEXT";
		var_data = text;
		p_variable_ctrl->Set_Variable(main_name,sub_name,var_data);
		//-------------------------------
	}
	else
	{
		acka10 = 2;
	}

	//-------------------------------
	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,acka10);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	if(acka10 != 0)		FA__ERROR;
	FA__OK;
}
void CMsg_S10Fy::Recv__F5(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl = p_bridge_ctrl->pMSG_SEND_CTRL;
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl = p_bridge_ctrl->pMSG_RECV_CTRL;
	CI_FA_VARIABLE_CTRL  *p_variable_ctrl = p_bridge_ctrl->pRES_VARIABLE_CTRL;

	CString	db_name;
	CString db_data;

	CString tid;
	CString text;

	int i;
	int limit;

	//-------------------------------
	// TID
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,tid);

	// LIST_LIMIT
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,db_data);

	limit = atoi(db_data);	
	if(limit > 10)		limit = 10;
	//-------------------------------

	//-------------------------------
	//.....
	int tid_check_flag = 1;

	//...
	{
		CString main_name = "S10Fy.TID";
		CString sub_name  = "CHECK.FLAG";
		CString var_data;

		p_variable_ctrl->Get_Variable(main_name,sub_name,var_data);

		if(var_data.CompareNoCase("NO") == 0)
		{
			tid_check_flag = -1;
		}
	}

	//.....
	int acka10 = 0;

	if((atoi(tid) == 0) || (tid_check_flag < 0))
	{
		CString main_name;
		CString sub_name;
		CString var_data;
		CStringArray var_list;

		main_name = "##S10F5";

		// TID
		sub_name = "TID";

		var_data = tid;
		p_variable_ctrl->Set_Variable(main_name,sub_name,var_data);

		// TEXT
		sub_name = "TEXT";

		CString first_data;
		CStringArray data_list;
		int data_type;

		for(i=0;i<limit;i++)
		{
			db_name.Format("-1-2-%1d",i+1);
			p_recv_ctrl->Get_Data(db_name,text);

			p_recv_ctrl->Get_Data(db_name,data_type,first_data,data_list);
			if(data_type != 114)   // ASCII
			{
				acka10 = 1;
				break;
			}

			var_list.Add(text);
		}

		p_variable_ctrl->Set_Variable(main_name,sub_name,var_list);
	}
	else
	{
		acka10 = 2;
	}
	//-------------------------------

	//-------------------------------
	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,acka10);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	if(acka10 != 0)		FA__ERROR;
	FA__OK;
}
void CMsg_S10Fy::Recv__F9(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl = p_bridge_ctrl->pMSG_SEND_CTRL;
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl = p_bridge_ctrl->pMSG_RECV_CTRL;
	CI_FA_VARIABLE_CTRL  *p_variable_ctrl = p_bridge_ctrl->pRES_VARIABLE_CTRL;

	CString	db_name;
	CString text;

	//-------------------------------
	// TEXT
	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,text);
	//-------------------------------

	//-------------------------------
	CString main_name;
	CString sub_name;

	main_name = "##S10F9";

	// TEXT
	sub_name = "TEXT";
	p_variable_ctrl->Set_Variable(main_name,sub_name,text);
	//-------------------------------

	//-------------------------------
	int acka10 = 0;

	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,acka10);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
