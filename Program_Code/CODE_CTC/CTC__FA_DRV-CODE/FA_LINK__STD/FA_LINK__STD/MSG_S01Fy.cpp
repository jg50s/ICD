#include "StdAFx.h"
#include "MSG_S01Fy.h"


CMsg_S01Fy mMSG_S01Fy;


//----------------------------------------------------------------------------
CMsg_S01Fy::CMsg_S01Fy()
{
	iSx = 1;
}

void CMsg_S01Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	switch(p_bridge_ctrl->iFy)
	{
		case 1:		Send__F1(p_bridge_ctrl);		return;
		case 13:	Send__F13(p_bridge_ctrl);		return;
	}
}

void CMsg_S01Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	switch(p_bridge_ctrl->iFy)
	{
		case 1:		Recv__F1(p_bridge_ctrl);		return;
		case 3:		Recv__F3(p_bridge_ctrl);		return;
		case 11:	Recv__F11(p_bridge_ctrl);		return;
		case 13:	Recv__F13(p_bridge_ctrl);		return;
		case 15:	Recv__F15(p_bridge_ctrl);		return;
		case 17:	Recv__F17(p_bridge_ctrl);		return;
	}
}

//----------------------------------------------------------------------------
void CMsg_S01Fy::Send__F1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	// SEND-MSG

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	//----------------------------------------------------------
	// RECV-MSG

	if(p_bridge_ctrl->iReply < 0)						FA__OK;

	if(p_bridge_ctrl->pFA_DRV_CTRL->Is_Recv() < 0)
	{
		CString main_name = "#RCV_MSG-S1F1";
		CString sub_name  = "ACK";
		CString var_data  = "S1F0";

		p_bridge_ctrl->pRES_VARIABLE_CTRL->Set_Variable(main_name,sub_name,var_data);

		FA__ERROR;
	}
	//-----------------------------

	FA__OK;
}

void CMsg_S01Fy::Send__F13(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	// SEND-MSG

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	//----------------------------------------------------------
	// RECV-MSG

	if(p_bridge_ctrl->iReply < 0)						FA__OK;
	if(p_bridge_ctrl->pFA_DRV_CTRL->Is_Recv() < 0)		FA__ERROR;
	//-----------------------------

	//-----------------------------
	CString db_name;
	CString var_data;

	// COMMACK
	db_name = "-1-1";
	p_bridge_ctrl->pMSG_RECV_CTRL->Get_Data(db_name,var_data);

	if(atoi(var_data) != 0)		FA__ERROR;
	//-----------------------------

	FA__OK;
}


//----------------------------------------------------------------------------
void CMsg_S01Fy::Recv__F1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	// RECV-MSG

	//-----------------------------

	//----------------------------------------------------------
	// SEND-MSG

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}

void CMsg_S01Fy::Recv__F3(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	CString	db_name;
	CString	db_data;

	//----------------------------------------------------------
	// RECV-MSG

	int list_limit;
	int i;
	int svid;
	CDS_SVID_DATA svid_data;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm_CTRL *p_300mm_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL;

	CI_FA_DB__SVID_CTRL *p_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_SVID_CTRL();

	// ...
	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,db_data);

	list_limit = atoi(db_data);

	if(list_limit > 0)
	{
		db_name = "-1";
		p_send_ctrl->Add_List(db_name,list_limit);

		for(i=0;i<list_limit;i++)
		{
			db_name.Format("-1-%1d",i+1);
			p_recv_ctrl->Get_Data(db_name,db_data);

			svid = atoi(db_data);
			p_svid_ctrl->Get_DATA(svid,
				svid_data,
				p_300mm_ctrl,
				p_bridge_ctrl->pRES_VARIABLE_CTRL);

			//--------------------------------------------
			db_name.Format("-1-%1d",i+1);
			p_send_ctrl->Add_Virtual(db_name,svid_data);
			//--------------------------------------------
		}
	}
	else
	{
		int db_index = 0;

		while(p_svid_ctrl->Get_DATA(db_index,
			svid,
			svid_data,
			p_300mm_ctrl,
			p_bridge_ctrl->pRES_VARIABLE_CTRL) > 0)
		{
			db_index++;

			//--------------------------------------------
			db_name.Format("-1-%1d",db_index);
			p_send_ctrl->Add_Virtual(db_name,svid_data);
			//--------------------------------------------
		}

		db_name = "-1";
		p_send_ctrl->Add_List(db_name,db_index);
	}
	//-----------------------------

	//----------------------------------------------------------
	// SEND-MSG

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	// p_bridge_ctrl->pFA_DRV_CTRL->Send_Without_DB_Check();
	//-----------------------------

	FA__OK
}

void CMsg_S01Fy::Recv__F11(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	CString		 db_name;
	int			 data_type;
	CString		 first_data;
	CStringArray data_list;

	//----------------------------------------------------------
	// RECV-MSG

	int list_limit;
	int i;
	int svid;
	CDS_SVID_INFO svid_info;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__SVID_CTRL *p_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_SVID_CTRL();

	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,data_type,first_data,data_list);

	list_limit = atoi(first_data);

	if(list_limit > 0)
	{
		db_name = "-1";
		p_send_ctrl->Add_List_Ex(db_name,list_limit, -1);

		for(i=0;i<list_limit;i++)
		{
			db_name.Format("-1-%1d",i+1);
			p_recv_ctrl->Get_Data(db_name,data_type,first_data,data_list);

			svid = atoi(first_data);
			p_svid_ctrl->Get_INFO(svid,svid_info);

			//--------------------------------------------
			// LIST
			db_name.Format("-1-%1d", i+1);
			p_send_ctrl->Add_List_Ex(db_name,3, -1);

			// SVID
			db_name.Format("-1-%1d-1",i+1);
			p_send_ctrl->Add_U4_Ex(db_name,svid, -1);
			// SVNAME
			db_name.Format("-1-%1d-2",i+1);
			p_send_ctrl->Add_Ascii_Ex(db_name,svid_info.sDisplay_Name, -1);
			// UNITS
			db_name.Format("-1-%1d-3",i+1);
			p_send_ctrl->Add_Ascii_Ex(db_name,svid_info.sUnit, -1);
			//--------------------------------------------
		}
	}
	else
	{
		int db_index = 0;

		while(p_svid_ctrl->Get_INFO(db_index,svid,svid_info) > 0)
		{
			db_index++;

			//--------------------------------------------
			// LIST
			db_name.Format("-1-%1d", db_index);
			p_send_ctrl->Add_List_Ex(db_name,3, -1);

			// SVID
			db_name.Format("-1-%1d-1",db_index);
			p_send_ctrl->Add_U4_Ex(db_name,svid, -1);
			// SVNAME
			db_name.Format("-1-%1d-2",db_index);
			p_send_ctrl->Add_Ascii_Ex(db_name,svid_info.sDisplay_Name, -1);
			// UNITS
			db_name.Format("-1-%1d-3",db_index);
			p_send_ctrl->Add_Ascii_Ex(db_name,svid_info.sUnit, -1);
			//--------------------------------------------
		}

		db_name = "-1";
		p_send_ctrl->Add_List_Ex(db_name,db_index, -1);
	}
	//-----------------------------

	//----------------------------------------------------------
	// SEND-MSG

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	// p_bridge_ctrl->pFA_DRV_CTRL->Send_Without_DB_Check(); 
	//-----------------------------

	FA__OK
}

void CMsg_S01Fy::Recv__F13(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CString db_name;

	db_name = "-1-1";
	p_bridge_ctrl->pMSG_SEND_CTRL->Add_Binary(db_name,0);

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//----------------------------------------------------------

	FA__OK
}

void CMsg_S01Fy::Recv__F15(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CString	db_name;

	//---------------------------------------

	//---------------------------------------
	//----------------------------------------------------------

	//----------------------------------------------------------
	//---------------------------------------
	// OFLACK
	int oflack = 0;

	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,oflack);
	//---------------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//----------------------------------------------------------

	//----------------------------------------------------------
	CI_FA_300mm__E30_CTRL *p_e30_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	p_e30_ctrl->Set_OFFLINE();
	//----------------------------------------------------------

	FA__OK
}

void CMsg_S01Fy::Recv__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E30_CTRL *p_e30_ctrl 
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	CString	db_name;
	int onlack = 0;

	//---------------------------------------
	if(p_e30_ctrl->Is_ONLINE() > 0)
	{
		// 2 = Equipment Already ON-LINE
		onlack = 2;
	}
	else
	{
		// 0 = ON-LINE accepted
		onlack = 0;
	}

	// ONLACK 
	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,onlack);
	//---------------------------------------
	//----------------------------------------------------------

	//----------------------------------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//----------------------------------------------------------

	//----------------------------------------------------------
	if(onlack == 0)
	{
		CI_FA_DB__ECID_CTRL *p_ecid_ctrl 
			= p_bridge_ctrl->pRES_DB_CTRL->Get_ECID_CTRL();

		int state = 0;
		p_ecid_ctrl->Get__INITIAL_CONTROL_STATE(state);

		if(state == 1)		p_e30_ctrl->Set_REMOTE_BY_HOST();
		else				p_e30_ctrl->Set_LOCAL_BY_HOST();
	}
	//----------------------------------------------------------

	FA__OK
}
