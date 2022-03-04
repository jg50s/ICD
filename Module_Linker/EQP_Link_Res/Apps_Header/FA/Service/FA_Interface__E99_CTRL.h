#pragma once


class CI_FA_300mm__E99_CTRL
{
public:
	virtual ~CI_FA_300mm__E99_CTRL(){};

	//----------------------------------------------------
	virtual int  Read_LP__PAGE(const int ptn,
							   const int data_seg,
							   const int data_len,
							   const int sec,
							   CString& data_page) = 0;
	virtual int  Read_LP__CID(const int ptn,
							  const int sec,
							  CString& data_cid) = 0;

	virtual int  Write_LP__PAGE(const int ptn,
							    const int data_seg,
							    const int data_len,
								const int sec,
								const CString& data_page) = 0;
	virtual int  Write_LP__CID(const int ptn,
							   const int sec,
							   const CString& data_cid) = 0;
};
