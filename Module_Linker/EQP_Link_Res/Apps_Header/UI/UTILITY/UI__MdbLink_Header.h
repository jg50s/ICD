#ifndef _UI__MDBLINK_HEADER_H_
#define _UI__MDBLINK_HEADER_H_


#pragma comment(lib, "C:\\GES__Application_Interface\\Interface_Header\\UI\\UTILITY\\UI__MdbLink.lib")
	  

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


#endif

