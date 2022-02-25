#pragma once

#include "Interface_Code.h"


class CMsg_S01Fy
{
private:
	void Send__F1(CI_BRIDGE__INFO_CTRL  *p_bridge_ctrl);
	void Send__F13(CI_BRIDGE__INFO_CTRL  *p_bridge_ctrl);

	void Recv__F1(CI_BRIDGE__INFO_CTRL  *p_bridge_ctrl);
	void Recv__F3(CI_BRIDGE__INFO_CTRL  *p_bridge_ctrl);
	void Recv__F11(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F13(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F15(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	int  iSx;

public:
	CMsg_S01Fy();

	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
