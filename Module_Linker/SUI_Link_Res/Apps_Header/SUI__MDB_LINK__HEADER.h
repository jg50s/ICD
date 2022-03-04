#pragma once

#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__MDB_LINK_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__MDB_LINK_R.lib")
#endif
	  

//----------------------------------------------------------------------------------
class UII__GOI_EXE_MDB_LINK_CTRL
{
public:
	virtual ~UII__GOI_EXE_MDB_LINK_CTRL(){};

	//.....
	virtual int  Connect__DB(HWND hwnd,const CString& db_dir,CString& err_msg) = 0;
	virtual int  Disconnect__DB() = 0;

	// 
	virtual int  Clear__ChannelCtrl_Table() = 0;
	virtual int  Make__Channel_List(const CStringArray& l_item) = 0;

	// WinCtrl Table
	virtual int  Set__WinCtrl_DATA(const CString& ch_name,const CString& ch_data) = 0;
	virtual int  Get__WinCtrl_DATA(const CString& ch_name,CString& ch_data) = 0;

	// ChannelCtrl Table
	virtual int  Set__CHANNEL_DATA(const CString& ch_name,const CString& ch_data) = 0;
	virtual int  Get__CHANNEL_DATA(const CString& ch_name,CString& ch_data) = 0;

	//
	virtual int  Show__OBJ() = 0;
	virtual int  Hide__OBJ() = 0;
};
//----------------------------------------------------------------------------------
