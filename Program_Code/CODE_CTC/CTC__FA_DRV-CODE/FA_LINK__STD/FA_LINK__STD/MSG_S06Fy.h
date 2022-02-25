#pragma once

#include "Interface_Code.h"


class CMsg_S06Fy
{
private:
	//----------------------------------------------------------------
	void Send__F1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	void Send__F9(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Make__F9__LPx_MHP_REPORT(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl,
									const int ceid,
									const int lp_id);

	void Send__F11(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// ...
	void Recv__F15(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F19(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F21(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F23(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//----------------------------------------------------------------
	int  iSx;

public:
	CMsg_S06Fy();

	//----------------------------------------------------------------
	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
