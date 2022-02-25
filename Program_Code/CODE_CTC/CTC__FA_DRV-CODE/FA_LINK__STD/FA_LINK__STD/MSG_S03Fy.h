#pragma once

#include "Interface_Code.h"


class CMsg_S03Fy
{
private:
	// ...
	void _Make__CMS_LOG(const CDS_CASSETTE_INFO& cst_info);

	//--------------------------------------------------------------------
	void Recv__F17_0(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F17_1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F17_2(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	void Recv__F25(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F27(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	void Recv__F29(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv__F31(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);

	//-----------------------------------------------------
	int  iSx;

public:
	CMsg_S03Fy();

	//--------------------------------------------------------------------
	void Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
	void Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl);
};
