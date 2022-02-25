#pragma once

#include "Interface_Code.h"


class CMsg_S15Fy
{
private:
	//----------------------------------------------------------------
	// Recipe Namespace Action Request
	void Recv__F3(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	// Recipe Namespace Action Acknowledge
	void Recv__F4(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	// Recipe Namespace Rename Request
	void Recv__F5(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	// Recipe Namespace Rename Acknowledge
	void Recv__F6(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);  

	// Recipe Rename Request
	void Recv__F19(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	// Recipe Rename Acknowledge
	void Recv__F20(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);  

	//----------------------------------------------------------------
	int  iSx;

public:
	CMsg_S15Fy();

	//----------------------------------------------------------------
	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
