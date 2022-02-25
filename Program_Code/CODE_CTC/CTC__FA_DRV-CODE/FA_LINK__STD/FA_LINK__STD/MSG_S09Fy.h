#pragma once

#include "Interface_Code.h"


class CMsg_S09Fy
{
private:
	//----------------------------------------------------------------
	// Conversation Timeout
	void Send__F13(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//----------------------------------------------------------------
	int  iSx;

public:
	CMsg_S09Fy();

	//----------------------------------------------------------------
	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
