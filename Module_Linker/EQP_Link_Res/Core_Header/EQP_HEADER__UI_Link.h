#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Core_Header\EQP_UI_HEADER.h"


class CI_SEQ_UI__ALARM_CTRL
{
public:
	virtual ~CI_SEQ_UI__ALARM_CTRL(){};

	virtual int ALARM_POST(const CDS_Alarm__MSG_INFO& msg_info) = 0;
	virtual int ALARM_DELETE(const int sys_id,const int alarm_id) = 0;
};
