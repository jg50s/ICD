#pragma once

#include "Interface_Code.h"


class CMsg_S16Fy
{
private:
	//----------------------------------------------------------------
	// Process Job Command 
	void Recv__F5(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Process Job Alert
	void Recv__F7(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Process Job Event Notify  
	void Recv__F9(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Process Job Create Enhance 
	void Recv__F11(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Process Job Duplicate Create 
	void Recv__F13(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Process Job Multi Create 
	void Recv__F15(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Process Job Dequeue 
	void Recv__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Process Job Get All Jobs 
	void Recv__F19(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Process Job Get Space 
	void Recv__F21(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// PRJobSetStartMethod  
	void Recv__F25(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Control Job Command 
	void Recv__F27(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// PRSetMtrlOrder
	void Recv__F29(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//----------------------------------------------------------------
	int  iSx;

public:
	CMsg_S16Fy();

	//----------------------------------------------------------------
	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
