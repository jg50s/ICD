#include "StdAFx.h"
#include "Interface_Code.h"


#include "MSG_S01Fy.h"
extern CMsg_S01Fy mMSG_S01Fy;

#include "MSG_S02Fy.h"
extern CMsg_S02Fy mMSG_S02Fy;

#include "MSG_S03Fy.h"
extern CMsg_S03Fy mMSG_S03Fy;

#include "MSG_S05Fy.h"
extern CMsg_S05Fy mMSG_S05Fy;

#include "MSG_S06Fy.h"
extern CMsg_S06Fy mMSG_S06Fy;

#include "MSG_S07Fy.h"
extern CMsg_S07Fy mMSG_S07Fy;

#include "MSG_S09Fy.h"
extern CMsg_S09Fy mMSG_S09Fy;

#include "MSG_S10Fy.h"
extern CMsg_S10Fy mMSG_S10Fy;

#include "MSG_S14Fy.h"
extern CMsg_S14Fy mMSG_S14Fy;

#include "MSG_S15Fy.h"
extern CMsg_S15Fy mMSG_S15Fy;

#include "MSG_S16Fy.h"
extern CMsg_S16Fy mMSG_S16Fy;

#include "MSG_S18Fy.h"
extern CMsg_S18Fy mMSG_S18Fy;


#include "CRes__CHANNEL.h"
extern CRes__CHANNEL mRes__CHANNEL;


FA_LINK__INIT(STD,service_name)
{
	mRes__CHANNEL.Init__CHANNEL();
	return 1;
}

FA_LINK__SEND(STD,p_bridge_info)
{
	FA__START

	mMSG_S01Fy.Send_Msg(p_bridge_info);
	mMSG_S02Fy.Send_Msg(p_bridge_info);
	mMSG_S03Fy.Send_Msg(p_bridge_info);
	mMSG_S05Fy.Send_Msg(p_bridge_info);
	mMSG_S06Fy.Send_Msg(p_bridge_info);
	mMSG_S07Fy.Send_Msg(p_bridge_info);
	mMSG_S09Fy.Send_Msg(p_bridge_info);
	mMSG_S10Fy.Send_Msg(p_bridge_info);
	
	mMSG_S14Fy.Send_Msg(p_bridge_info);
	mMSG_S15Fy.Send_Msg(p_bridge_info);
	mMSG_S16Fy.Send_Msg(p_bridge_info);
	mMSG_S18Fy.Send_Msg(p_bridge_info);

	FA__END
}

FA_LINK__RECV(STD,p_bridge_info)
{
	FA__START

	mMSG_S01Fy.Recv_Msg(p_bridge_info);
	mMSG_S02Fy.Recv_Msg(p_bridge_info);
	mMSG_S03Fy.Recv_Msg(p_bridge_info);
	mMSG_S05Fy.Recv_Msg(p_bridge_info);
	mMSG_S06Fy.Recv_Msg(p_bridge_info);
	mMSG_S07Fy.Recv_Msg(p_bridge_info);
	mMSG_S09Fy.Recv_Msg(p_bridge_info);
	mMSG_S10Fy.Recv_Msg(p_bridge_info);

	mMSG_S14Fy.Recv_Msg(p_bridge_info);
	mMSG_S15Fy.Recv_Msg(p_bridge_info);
	mMSG_S16Fy.Recv_Msg(p_bridge_info);
	mMSG_S18Fy.Recv_Msg(p_bridge_info);

	FA__END
}
