#pragma once

#include "Interface_Code.h"


class CMsg_S05Fy
{
private:
	//--------------------------------------------------------------------
	void Send__F1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	void Recv__F3(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F5(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F7(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//--------------------------------------------------------------------
	int  iSx;

public:
	CMsg_S05Fy();

	//--------------------------------------------------------------------
	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
