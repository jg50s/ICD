#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__Error.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__Macro.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__SEQ_INFO.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__VARIABLE_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__300mm_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__DB_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__BRIDGE_CTRL.h"


//----------------------------------------------------
class CDS_FA__MATERIAL_INFO
{
public:
	//------------------------------------------------
	CDS_FA__MATERIAL_INFO()
	{
		iPTN  = 0;
		iSLOT = 0;

		sLOTID  = "";
		sPPID   = "";
		sMATERIAL_ID   = "";
		sMATERIAL_TYPE = "";
		sPRC_ID = "";

		sLP_SOURCE = "";
		sLP_TARGET = "";

		iTRG_PTN  = iPTN;
		iTRG_SLOT = iSLOT;
	}
	//------------------------------------------------

	//------------------------------------------------
	int iPTN;
	int iSLOT;

	CString	sLOTID;
	CString	sPPID;
	CString	sMATERIAL_ID;
	CString	sMATERIAL_TYPE;
	CString	sPRC_ID;

	CString sLP_SOURCE;
	CString sLP_TARGET;

	int iTRG_PTN;
	int iTRG_SLOT;
	//------------------------------------------------
};
//----------------------------------------------------

//----------------------------------------------------
class CI_FA_300mm_LINK
{
public:
	virtual ~CI_FA_300mm_LINK(){};

	//-------------------------------------------------------------------------
	virtual int Open(const CString& service_name) = 0;

	//-------------------------------------------------------------------------
	virtual CI_FA_300mm_CTRL*    Get_FA_300mm_CTRL()    = 0;
	virtual CI_FA_DB_CTRL*	     Get_FA_DB_CTRL()       = 0;
	virtual CI_FA_VARIABLE_CTRL* Get_FA_VARIABLE_CTRL() = 0;
	virtual CI_SEQ_INFO*		 Get_SEQ_INFO() = 0;
	
	//-------------------------------------------------------------------------
	virtual int Send_EVENT(const int user_ceid,const int sxfy_type = 0) = 0;
	virtual int Send_MSG(const int sx,const int fy,const int sxfy_type = 0) = 0;
	virtual int Send_S9F13(const int sx,const int fy,const CString& edid) = 0;

	//-------------------------------------------------------------------------
	virtual int Report__MATERIAL_INFO(const CDS_FA__MATERIAL_INFO& material_info) = 0;

	//.....
	virtual int Send__ALARM_POST(const int& seq_id,const int& alid)  = 0;
	virtual int Send__ALARM_CLEAR(const int& seq_id,const int& alid) = 0;

	virtual int Send__ALARM_POST_EX(const int& seq_id,const int& alid,const CString& alarm_title)  = 0;
	virtual int Send__ALARM_CLEAR_EX(const int& seq_id,const int& alid,const CString& alarm_title) = 0;

	//-------------------------------------------------------------------------
	virtual void LOG_CTRL__Enable()  = 0;
	virtual void LOG_CTRL__Disable() = 0;

	virtual void LOG_CTRL__Enable_Ctrl_Msg()  = 0;
	virtual void LOG_CTRL__Disable_Ctrl_Msg() = 0;
	virtual void LOG_CTRL__Enable_SECSI()   = 0;
	virtual void LOG_CTRL__Disable_SECSI()  = 0;
	virtual void LOG_CTRL__Enable_SECSII()  = 0;
	virtual void LOG_CTRL__Disable_SECSII() = 0;

    // Unit : Day,  Range : 1 ~ 30   
	virtual void LOG_CTRL__Set_Date_Size(const int date_size) = 0;

	virtual void LOG_CTRL__Enable_S6F1_LOG()  = 0;
	virtual void LOG_CTRL__Disable_S6F1_LOG() = 0;	

	// Unit : Min,  Range : 10, 20, 30, 40, 50, 60
	virtual void LOG_CTRL__Set_Interval_Time(const int min_time) = 0;

	//.....
	virtual int Send_SEPARATE() = 0;

	virtual int Stop_DRIVER() = 0;
	virtual int Start_DRIVER() = 0;


	// ...
	virtual int Send__CDS_MSG_BIN(void *p_ds_msg_bin) = 0;
	virtual int Send__BIN_DATA(const int bin_len,const CString& bin_data) = 0;
};
//----------------------------------------------------

//----------------------------------------------------
class SCI__Memory_Check__FA_Interface__300mm
{
public:
	virtual ~SCI__Memory_Check__FA_Interface__300mm(){};

	// ...
	virtual int Dump_To_File(const CString& path, const CString& log_title) = 0;
};
//----------------------------------------------------

