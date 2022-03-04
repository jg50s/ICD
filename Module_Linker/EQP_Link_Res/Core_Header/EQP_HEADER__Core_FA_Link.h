#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Core_Header\EQP_UI_HEADER.h"


//-----------------------------------------------------------------------
class CDS__CHANNEL_INFO
{
public:
	CDS__CHANNEL_INFO()
	{
		iOBJ_INDEX = -1;
		iVAR_INDEX = -1;
		iVAR_TYPE  = -1;

		sVAR_DATA  = "";
	}

	int iOBJ_INDEX;
	int	iVAR_INDEX;
	int iVAR_TYPE;
	
	CString sVAR_DATA;
};
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
class CDS__SEQ_INFO
{
public:
	CString	sModule_NAME;
	CString sModule_IP;
	
	CString sDir_ROOT;
	CString sDir_DATALOG;
	CString sDir_PROCESS;
	CString sDir_ROUTE;
	CString sDir_CASSETTE;
	CString sDir_JOB;
};
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
class CI_SEQ_DB__FA_CTRL
{
public:
	virtual ~CI_SEQ_DB__FA_CTRL(){};

	//-----------------------------------------------------------------------
	virtual int Get__SEQ_INFO(CDS__SEQ_INFO& ds_seq_info) = 0;
};
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
class CI_SEQ_DB__FA__CHANNEL_CTRL
{
public:
	virtual ~CI_SEQ_DB__FA__CHANNEL_CTRL(){};
	
	//-----------------------------------------------------------------------
	virtual int Get__CHANNEL_INFO(const CString& channel,CDS__CHANNEL_INFO *p_info) = 0;

	virtual int Get__DATA(CDS__CHANNEL_INFO *p_info) = 0;
	virtual int Set__DATA(const CDS__CHANNEL_INFO *p_info) = 0;

	//-----------------------------------------------------------------------
	virtual int Get__FA_VARIABLE__DATA(const CString& fa_var,CString& data) = 0;
};
//-----------------------------------------------------------------------

//----------------------------------------------------
class CI_SEQ_DB__FA__ALARM_CTRL
{
public:
	virtual ~CI_SEQ_DB__FA__ALARM_CTRL(){};

	//------------------------------------------------------------------
	virtual int Get__POST_INFO(const int& db_index,
							   int& seq_id,
							   int& alarm_type,
							   int& alarm_id,
							   CString& time,
							   CString& title,
							   CString& message,
							   CStringArray& l_option) = 0;

	virtual int Get__CLEAR_INFO(int& seq_id,
								int& alarm_type,
								int& alarm_id,
								CString& time,
								CString& title,
								CString& act_result) = 0;

	virtual int Is__POST_SIZE() = 0;
	virtual int Is__POST_SIZE(int& new_alarm_flag) = 0;

};
//----------------------------------------------------
