#pragma once

#include "Interface_Code.h"


class CMsg_S07Fy
{
private:
	//----------------------------------------------------------------
	void Recv__F1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	void Recv__F3(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F5(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	void Recv__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	void Recv__F19_0(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F19_1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	void Recv__F23(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F25(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	void Recv__F65(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	void Recv__F83(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F85(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	void Recv__F93(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F95(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	void Recv__F97(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F99(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//----------------------------------------------------------------
	int  iSx;

public:
	CMsg_S07Fy();

	//----------------------------------------------------------------
	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
