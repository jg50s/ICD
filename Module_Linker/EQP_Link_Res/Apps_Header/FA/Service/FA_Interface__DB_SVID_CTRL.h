#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__SEQ_INFO.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__300mm_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__VARIABLE_CTRL.h"


class CDS_SVID_INFO
{
public:
	CString sFmt_Type;
	int     iFmt_Byte;

	CString sUnit;
	CString sDisplay_Name;
};

class CDS_SVID_INFO_EX : public CDS_SVID_INFO
{
public:
	CString sEQPID;
	CString sToolID;
	CString sUnitID;
};

class CDS_SVID_DATA
{
public:
	void Init()
	{
		sFmt_Type = "A";
		iFmt_Byte = 0;
		sData = "";

		sSub_Fmt_Type1.RemoveAll();
		sSub_Fmt_Type2.RemoveAll();
		sSub_Fmt_Type3.RemoveAll();

		iSub_Fmt_Byte1.RemoveAll();
		iSub_Fmt_Byte2.RemoveAll();
		iSub_Fmt_Byte3.RemoveAll();

		sSub_Data1.RemoveAll();
		sSub_Data2.RemoveAll();
		sSub_Data3.RemoveAll();
	}

	CString sFmt_Type;
	int     iFmt_Byte;
	CString sData;

	CStringArray sSub_Fmt_Type1;
	CStringArray sSub_Fmt_Type2;
	CStringArray sSub_Fmt_Type3;

	CUIntArray	 iSub_Fmt_Byte1;
	CUIntArray	 iSub_Fmt_Byte2;
	CUIntArray	 iSub_Fmt_Byte3;

	CStringArray sSub_Data1;
	CStringArray sSub_Data2;
	CStringArray sSub_Data3;
};


class CI_FA_DB__SVID_CTRL
{
public:
	virtual ~CI_FA_DB__SVID_CTRL(){};

	//----------------------------------------------------
	virtual int Is_SVID(const int svid) = 0;

	// ...
	virtual int Get_INFO(const int svid,    
						 CDS_SVID_INFO& svid_info) = 0;
	virtual int Get_INFO(const int db_index,
						 int& svid,
						 CDS_SVID_INFO& svid_info) = 0;

	// ...
	virtual int Get_DATA(const int svid,
						 CDS_SVID_DATA& svid_data,
						 CI_FA_300mm_CTRL* p_30mm_ctrl,
						 CI_FA_VARIABLE_CTRL* p_variable_ctrl) = 0;
	virtual int Get_DATA(const int db_index,
						 int& svid,
						 CDS_SVID_DATA& svid_data,
						 CI_FA_300mm_CTRL* p_30mm_ctrl,
						 CI_FA_VARIABLE_CTRL* p_variable_ctrl) = 0;

	// ...
	virtual int Get__ALL_SVID_LIST(CUIntArray& l_svid) = 0;

	// ...
	virtual int Get__ALL_SVID_LIST_OF_TOOLID(const CString& str_toolid,
											 CUIntArray& l_svid) = 0;

	virtual int Get_INFO_EX(const int svid,    
		                    CDS_SVID_INFO_EX& svid_info) = 0;
	virtual int Get_INFO_EX(const int db_index,
		                    int& svid,
		                    CDS_SVID_INFO_EX& svid_info) = 0;

};
