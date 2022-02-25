#pragma once

#include "Interface_Code.h"


class CMsg_S7Fy
{
private:
	//----------------------------------------------------------------
	int iFlag__Log_Ctrl;
	SCX__USER_LOG_CTRL xLog_Ctrl;

	// ...
	void Recv__F19_0(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F25(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//----------------------------------------------------------------
	int  iSx;

public:
	CMsg_S7Fy();

	//----------------------------------------------------------------
	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
