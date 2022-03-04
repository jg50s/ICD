#ifndef _UI__ExeNetLink_HEADER_H_
#define _UI__ExeNetLink_HEADER_H_


#pragma comment(lib, "C:\\GES__Application_Interface\\Interface_Header\\UI\\UTILITY\\UI__ExeNetLink_Ctrl.lib")
	  

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


#endif

