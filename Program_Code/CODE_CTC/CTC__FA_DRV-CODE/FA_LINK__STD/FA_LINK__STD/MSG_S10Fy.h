#pragma once

#include "Interface_Code.h"


class CMsg_S10Fy
{
private:
	//----------------------------------------------------------------
	// Terminal Request (TRN) 
	void Send__F1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	// Multi-Block Not Allowed(MMN) 
	void Send__F7(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Terminal Display, Single (VTN)
	void Recv__F3(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	// Terminal Display, Multi-Block (VTN) 
	void Recv__F5(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	// Broadcast(BCN)    
	void Recv__F9(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//----------------------------------------------------------------
	int  iSx;

public:
	CMsg_S10Fy();

	//----------------------------------------------------------------
	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
