#pragma once


class CI_FA_NET__CTRL
{
public:
	virtual ~CI_FA_NET__CTRL(){};

	//------------------------------------------------------------------------------
	virtual int Link__Service_Name(const CString& service_name) = 0;
	
	virtual int Send__E30_Event(const int msg_cmmd,const CString& msg_data) = 0;
	virtual int Send__E87_Event(const int msg_cmmd,const int ptn,const CString& cstid) = 0;
};	
