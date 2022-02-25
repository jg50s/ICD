#pragma once

#include "Interface_Code.h"


class CMsg_S7Fy
{
private:	
	//-----------------------------------------------------
	//	Process Program Verification Send (PVS)
	void Send__F27(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// ...
	void Recv__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);	
	void Recv__F19_0(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	void Recv__F23(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F25(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//-----------------------------------------------------
	int  iSx;

public:
	CMsg_S7Fy();

	//-----------------------------------------------------
	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
