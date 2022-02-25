#pragma once

#include "Interface_Code.h"


class CMsg_S14Fy
{
private:
	//----------------------------------------------------------------
	// Get Attribute Request
	void Recv__F1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Fnc__MSG_S14F1__Make_Process_History(const CString& node_name,
											   const CString& objtype,
											   const CString& objid,
											   CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl);
	void Fnc__MSG_S14F1__Make_Module_History(const CString& node_name,
											 const CString& objtype,
											 const CString& objid,
											 CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl);

	// Set Attribute Request
	void Recv__F3(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	// Get Type Request
	void Recv__F5(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	// Get Attribute Name Request
	void Recv__F7(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Create Object Request
	void Recv__F9_0(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F9_1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// Delete Object Request
	void Recv__F11(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//----------------------------------------------------------------
	int  iSx;

public:
	CMsg_S14Fy();

	//----------------------------------------------------------------
	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
