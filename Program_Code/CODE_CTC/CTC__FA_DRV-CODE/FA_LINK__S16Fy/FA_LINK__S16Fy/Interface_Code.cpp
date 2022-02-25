#include "StdAFx.h"

#include "MSG_S16Fy.h"
extern CMsg_S16Fy mMSG_S16Fy;


FA_LINK__SEND(APC, p_bridge_info)
{
	FA__START

	mMSG_S16Fy.Send_Msg(p_bridge_info);

	FA__END
}

FA_LINK__RECV(APC, p_bridge_info)
{
	FA__START

	mMSG_S16Fy.Recv_Msg(p_bridge_info);

	FA__END
}
