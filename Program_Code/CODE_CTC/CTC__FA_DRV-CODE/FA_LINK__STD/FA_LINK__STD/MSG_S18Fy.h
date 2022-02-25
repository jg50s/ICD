#pragma once

#include "Interface_Code.h"


class CMsg_S18Fy
{
private:
	//----------------------------------------------------------------
	// Read Data Request (RR)
	void Recv__F5(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Write Data Request (WDR)
	void Recv__F7(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Read ID Request (RIR)
	void Recv__F9(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Write ID Request (WIR)
	void Recv__F11(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//----------------------------------------------------------------
	int  iSx;

public:
	CMsg_S18Fy();

	//----------------------------------------------------------------
	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
