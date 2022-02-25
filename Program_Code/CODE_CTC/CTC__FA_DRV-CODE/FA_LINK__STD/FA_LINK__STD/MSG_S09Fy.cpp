#include "StdAFx.h"

#include "MSG_S09Fy.h"
CMsg_S09Fy mMSG_S09Fy;


//----------------------------------------------------------------------------
CMsg_S09Fy::CMsg_S09Fy()
{
	iSx = 9;
}

void CMsg_S09Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	switch(p_bridge_ctrl->iFy)
	{
		case 13:	Send__F13(p_bridge_ctrl);		return;
	}
}

void CMsg_S09Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	/*
	switch(p_bridge_ctrl->iFy)
	{
	}
	*/
}

//----------------------------------------------------------------------------
void CMsg_S09Fy::Send__F13(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl = p_bridge_ctrl->pMSG_SEND_CTRL;
	CI_FA_VARIABLE_CTRL  *p_variable_ctrl = p_bridge_ctrl->pRES_VARIABLE_CTRL;

	CString db_name;

	CString main_name;
	CString sub_name;

	CString mexp;
	CString edid;

	//-------------------------------
	main_name = "##S9F13";

	// MEXP
	sub_name = "MEXP";
	p_variable_ctrl->Get_Variable(main_name,sub_name,mexp);

	// EDID
	sub_name = "EDID";
	p_variable_ctrl->Get_Variable(main_name,sub_name,edid);
	//-------------------------------

	//-------------------------------
	// MEXP
	db_name = "-1-1";
	p_send_ctrl->Add_Ascii(db_name,mexp);
	
	// EDID
	db_name = "-1-2";
	p_send_ctrl->Add_Ascii(db_name,edid);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	//--------------------------------------------
	if(p_bridge_ctrl->iReply < 0)						FA__OK;
	if(p_bridge_ctrl->pFA_DRV_CTRL->Is_Recv() < 0)		FA__ERROR;
	//--------------------------------------------

	FA__OK;
}
