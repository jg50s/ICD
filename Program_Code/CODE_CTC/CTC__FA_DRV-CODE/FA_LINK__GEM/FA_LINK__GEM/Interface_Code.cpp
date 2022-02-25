#include "StdAFx.h"
#include "Interface_Code.h"


#include "MSG_S1Fy.h"
extern CMsg_S1Fy  mMSG_S1Fy;

#include "MSG_S7Fy.h"
extern CMsg_S7Fy  mMSG_S7Fy;



// GEM_S1Fy --------------------------------------------------------------------
FA_LINK__SEND(GEM_S1Fy, p_bridge_info)
{
	FA__START

	mMSG_S1Fy.Send_Msg(p_bridge_info);

	FA__END
}

FA_LINK__RECV(GEM_S1Fy, p_bridge_info)
{
	FA__START

	mMSG_S1Fy.Recv_Msg(p_bridge_info);

	FA__END
}


// PMC_S7Fy --------------------------------------------------------------------
FA_LINK__SEND(PMC_S7Fy, p_bridge_info)
{
	FA__START

	mMSG_S7Fy.Send_Msg(p_bridge_info);

	FA__END
}

FA_LINK__RECV(PMC_S7Fy, p_bridge_info)
{
	FA__START

	mMSG_S7Fy.Recv_Msg(p_bridge_info);

	FA__END
}
