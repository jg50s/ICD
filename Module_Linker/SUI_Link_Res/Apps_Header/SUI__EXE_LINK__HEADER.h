#pragma once

#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__EXE_LINK_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__EXE_LINK_R.lib")
#endif


//----------------------------------------------------------------------------------
class UII__ExeNetLink_Ctrl
{
public:
	virtual ~UII__ExeNetLink_Ctrl(){};

	// ...
	virtual int  Connect__NET(const CString& sub_dir,const CString& exe_name,CString& err_msg) = 0;
	virtual int  Get__CHANNEL_LIST(CStringArray& l_ch_name) = 0;

	virtual int  Disconnect__NET() = 0;

	// WinCtrl
	virtual int  Show__OBJ(const int popup_flag,
						   const int win_x,const int win_y,
						   const int win_width,const int win_height) = 0;
	virtual int  Hide__OBJ() = 0;

	// ChannelCtrl
	virtual int  Set__CHANNEL_DATA(const CString& ch_name,const CString& ch_data) = 0;
	virtual int  Get__CHANNEL_DATA(const CString& ch_name,CString& ch_data) = 0;

	virtual int  Get__CHANNEL_CHANGE_DATA(CStringArray& l_ch_name,CStringArray& l_ch_data) = 0;
};
//----------------------------------------------------------------------------------
