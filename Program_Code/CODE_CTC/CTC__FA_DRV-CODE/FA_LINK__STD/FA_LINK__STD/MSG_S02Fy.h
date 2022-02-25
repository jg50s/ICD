#pragma once

#include "Interface_Code.h"


class CMsg_S02Fy
{
private:
	//-----------------------------------------------------
	int  F41__Check_RCMD(CI_FA_300mm__E30_CTRL* p_e30_ctrl,
						 const CString& rcmd,
						 const CStringArray& l_cpname,
						 const CStringArray& l_cpval,
						 int& hcack,
						 CStringArray& l_err_cpname,
						 CUIntArray&   l_err_cpack);

	//-----------------------------------------------------
	//  Date and Time Request
	void Send__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//  Loopback Diagnostic
	void Send__F25(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//-----------------------------------------------------
	// 	Equipment Constant Request
	void Recv__F13(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	// 	New Equipment Constant
	void Recv__F15(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	//  Date and Time Request
	void Recv__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// 	Trace Initialize Send
	void Recv__F23(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//  Loopback Diagnostic
	void Recv__F25(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	// 	Equipment Constant Namelist Request
	void Recv__F29(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	//	Date and Time Set Request (DTS) 
	void Recv__F31(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	//  Define Report
	void Recv__F33(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	//  Link Event Report
	void Recv__F35(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	// 	Enable/Disable Event Report 
	void Recv__F37(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	//  Multi-Block Inquire
	void Recv__F39(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	//  Host Command Send (HCS)
	void Recv__F41(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	// 	Reset Spooling Streams and Functions
	void Recv__F43(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	// 	Variable Limit Attribute Request 
	void Recv__F45(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	// 	Variable Limit Attribute Request 
	void Recv__F47(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);


	//-----------------------------------------------------
	int  iSx;

public:
	CMsg_S02Fy();

	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
