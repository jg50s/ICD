#ifndef _UI__IPC_INTERFACE_HEADER_H_
#define _UI__IPC_INTERFACE_HEADER_H_


#pragma comment(lib, "C:\\GES__Application_Interface\\Interface_Header\\UI\\UTILITY\\UI__IPC_Interface.lib")
	  

//----------------------------------------------------------------------------------
class CInterface__IPC_Ctrl
{
public:
	virtual ~CInterface__IPC_Ctrl(){};

	//--------------------------------------------------------------
	virtual int  Callback__SET_DATA(const int ch_index,
									const CString& ch_name,
									const CString& ch_data) = 0;
};

class UII__IPC_INTERFACE_CTRL
{
public:
	virtual ~UII__IPC_INTERFACE_CTRL(){};

	//--------------------------------------------------------------
	virtual int  Start__IPC(const HWND hwnd,
							const CStringArray& l_ch_name,
					     	CInterface__IPC_Ctrl* p_proc = NULL) = 0;

	virtual int  Set__DATA(const int ch_index,
					       const CString& ch_name,
					       const CString& ch_data) = 0;
	virtual int  Get__DATA(const int ch_index,
						   const CString& ch_name,
						   CString& ch_data) = 0;
};
//----------------------------------------------------------------------------------


#endif

