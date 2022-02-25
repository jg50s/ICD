#pragma once

#include "Interface_Code.h"


class CMsg_S1Fy
{
private:
	//----------------------------------------------------------------
	void Recv__F15(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//----------------------------------------------------------------
	int  iSx;

public:
	CMsg_S1Fy();

	//----------------------------------------------------------------
	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
