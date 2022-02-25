#include "StdAFx.h"
#include "Interface_Code.h"


#include "MSG_S7Fy.h"
extern CMsg_S7Fy mMSG_S7Fy;


FA_LINK__SEND(S7F25, p_bridge_info)
{
	FA__START

	mMSG_S7Fy.Send_Msg(p_bridge_info);

	FA__END
}

FA_LINK__RECV(S7F25, p_bridge_info)
{
	FA__START

	mMSG_S7Fy.Recv_Msg(p_bridge_info);

	FA__END
}
