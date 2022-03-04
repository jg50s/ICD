#pragma once


class CISeq__IPC_Ctrl
{
public:
	virtual ~CISeq__IPC_Ctrl(){};

	//--------------------------------------------------------------
	virtual int  Callback__SET_DATA(const int ch_index,
					const CString& ch_name,
					const CString& ch_data) = 0;
};

class SCI__IPC_INTERFACE_CTRL
{
public:
	virtual ~SCI__IPC_INTERFACE_CTRL(){};

	//--------------------------------------------------------------
	virtual int  Start__IPC(const HWND hwnd,
				const CStringArray& l_ch_name,
			     	CISeq__IPC_Ctrl* p_proc = NULL) = 0;

	virtual int  Set__DATA(const int ch_index,
			       const CString& ch_name,
			       const CString& ch_data) = 0;
	virtual int  Get__DATA(const int ch_index,
			       const CString& ch_name,
			       CString& ch_data) = 0;
};
