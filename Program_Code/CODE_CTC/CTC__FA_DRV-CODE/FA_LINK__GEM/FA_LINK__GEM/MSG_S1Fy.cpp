#include "StdAFx.h"

#include "MSG_S1Fy.h"
CMsg_S1Fy mMSG_S1Fy;


//----------------------------------------------------------------------------
CMsg_S1Fy::CMsg_S1Fy()
{
	iSx = 1;
}

void CMsg_S1Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	/*
	switch(p_bridge_ctrl->iFy)
	{

	}
	*/
}

void CMsg_S1Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	switch(p_bridge_ctrl->iFy)
	{
		case 15:	Recv__F15(p_bridge_ctrl);		return;
		case 17:	Recv__F17(p_bridge_ctrl);		return;
	}
}


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void CMsg_S1Fy::Recv__F15(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
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

void CMsg_S1Fy::Recv__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
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
		if(p_e30_ctrl->Check__CONTROL_STATE__EQUIPMENT_OFFLINE() > 0)
		{
			onlack = 1;
		}
		else
		{
			// 0 = ON-LINE accepted
			onlack = 0;
		}
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
		int local_flag = 1;

		if(p_e30_ctrl->Check__CONTROL_STATE__ONLINE_LOCAL() > 0)
		{
			local_flag = 1;
		}
		else if(p_e30_ctrl->Check__CONTROL_STATE__ONLINE_REMOTE() > 0)
		{
			local_flag = -1;
		}
		else
		{
			CI_FA_DB__ECID_CTRL *p_ecid_ctrl 
				= p_bridge_ctrl->pRES_DB_CTRL->Get_ECID_CTRL();

			int state = 0;
			p_ecid_ctrl->Get__INITIAL_CONTROL_STATE(state);

			if(state == 1)		local_flag = -1;
			else				local_flag =  1;
		}

		if(local_flag > 0)		p_e30_ctrl->Set_LOCAL_BY_HOST();
		else					p_e30_ctrl->Set_REMOTE_BY_HOST();
	}
	//----------------------------------------------------------

	FA__OK
}
