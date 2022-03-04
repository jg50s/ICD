#pragma once


class CDS_FA__APP_INFO
{
public:
	CDS_FA__APP_INFO()
	{
		Clear();
	}
	void Clear()
	{
		//------------------------------------------------
		sService_Name = "";

		sMain_Command = "";
		sSub_Command  = "";

		sPara1 = "";
		sPara2 = "";
		sPara3 = "";
		sPara4 = "";
		sPara5 = "";
		//------------------------------------------------
	}

	//------------------------------------------------
	CString sService_Name;

	CString sMain_Command;
	CString sSub_Command;

	CString sPara1;
	CString sPara2;
	CString sPara3;
	CString sPara4;
	CString sPara5;
	//------------------------------------------------
};

class CDS_ATTR_DATA
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


#define FA_APP_DLL(fnc_name,app_info)		\
extern "C" __declspec(dllexport) int FA_APP_DLL_##fnc_name(const CDS_FA__APP_INFO& app_info)
