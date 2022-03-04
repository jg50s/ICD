#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\EQP\INTERFACE\OBJECT_INTERFACE.h"


#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\EQP_Link_Res\\EQP_Lib\\EQP__FA_Link_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\EQP_Link_Res\\EQP_Lib\\EQP__FA_Link_R.lib")
#endif


// ...
#define EVENT_LPx__LOAD_REQ									1
#define EVENT_LPx__LOAD										2

#define EVENT_LPx__UNLOAD_REQ								3
#define EVENT_LPx__UNLOAD									4

#define EVENT_LPx__CST_EXIST								11
#define EVENT_LPx__CST_NONE									12

#define EVENT_LPx__FOUP_DOCK								13
#define EVENT_LPx__FOUP_UNDOCK								14

#define EVENT_LPx__CID_READ_START							21
#define EVENT_LPx__CID_READ_END								22

#define EVENT_LPx__MAP_START								23
#define EVENT_LPx__MAP_END									24

#define EVENT_LPx__JOB_START								31
#define EVENT_LPx__PORT_COMPLETE							32

#define EVENT_LPx__PORT_CANCEL								41
#define EVENT_LPx__PORT_CANCELED							42
#define EVENT_LPx__PORT_PAUSE								43
#define EVENT_LPx__PORT_PAUSED								44
#define EVENT_LPx__PORT_RESUME								45
#define EVENT_LPx__PORT_RESUMED								46
#define EVENT_LPx__PORT_ABORT								47
#define EVENT_LPx__PORT_ABORTED								48
#define EVENT_LPx__PORT_RELOAD								49
#define EVENT_LPx__PORT_RELOADED							50


// ...
class SCI_FA__E87_CTRL
{
public:
	virtual ~SCI_FA__E87_CTRL(){};

	// ...
	virtual int  Register__CST_STS(const CString& ch_name) = 0;
	virtual int  Register__CST_ID(const CString& ch_name)  = 0;
	virtual int  Register__SLOT_STS(const int slot_id,const CString& ch_name) = 0;
  
	virtual int  Event__LPx__ACCESS_MODE__AUTO() = 0;
	virtual int  Event__LPx__ACCESS_MODE__MANUAL() = 0;

	virtual int  Event__LPx__IN_SERVICE() = 0;
	virtual int  Event__LPx__OUT_OF_SERVICE() = 0;

	virtual int  Event__LPx__TRANSFER_READY() = 0;
	virtual int  Event__LPx__READY_TO_UNLOAD() = 0;
	virtual int  Event__LPx__READY_TO_LOAD() = 0;
	virtual int  Event__LPx__TRANSFER_BLOCKED() = 0;

	virtual int  Event__LPx__ID_NOT_READ() = 0;
	virtual int  Event__LPx__ID_WAITING_FOR_HOST() = 0;
	virtual int  Event__LPx__ID_VERIFICATION_OK() = 0;
	virtual int  Event__LPx__ID_VERIFICATION_FAIL() = 0;
	virtual	int  Event__LPx__ID_WAITING_FOR_HOST__BypassReadID_False() = 0;
	virtual int  Event__LPx__ID_VERIFICATION_OK__BypassReadID_True() = 0;
			
	virtual int  Event__LPx__NOT_ACCESSED() = 0;
	virtual int  Event__LPx__IN_ACCESS() = 0;
	virtual int  Event__LPx__CARRIER_COMPLETE() = 0;
	virtual int  Event__LPx__CARRIER_STOPPED() = 0;

	virtual int  Event__LPx__SLOT_MAP_NOT_READ() = 0;
	virtual int  Event__LPx__SLOT_MAP_WAITING_FOR_HOST() = 0;
	virtual int  Event__LPx__SLOT_MAP_VERIFICATION_OK() = 0;
	virtual int  Event__LPx__SLOT_MAP_VERIFICATION_FAIL() = 0;

	virtual int  Event__LPx__NOT_RESERVED() = 0;
	virtual int  Event__LPx__TO_RESERVED() = 0;

	virtual int  Event__LPx__NOT_ASSOCIATED() = 0;
	virtual int  Event__LPx__ASSOCIATED() = 0;
};


class SCI__FA_CTRL
{
public:
	virtual ~SCI__FA_CTRL(){};

	// ...
	virtual int Link__Service_Name(const CString& fa_service_name) = 0;
	virtual int Send__E30_Event(const int msg_cmmd,const CString& msg_data) = 0;
	virtual int LPx__EVENT(const int ptn,const int event_id) = 0;
	
	virtual SCI_FA__E87_CTRL* Get__E87_CTRL(const int ptn) = 0;
};
