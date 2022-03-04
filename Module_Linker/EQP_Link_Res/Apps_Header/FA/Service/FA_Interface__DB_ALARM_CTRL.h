#pragma once


class CI_FA_DB__ALARM_CTRL
{
public:
	virtual ~CI_FA_DB__ALARM_CTRL(){};

	//----------------------------------------------------
	virtual int SetDIR(const CString& dir,const CString& file) = 0;

	virtual int Get(const int alid,CString& altx) = 0;
	virtual int Get_INFO(const int alid,int& alcd,CString& altx,int& status) = 0;
	
	virtual int Set(const int alid,const int status) = 0;
	virtual int SetALL(const int status) = 0;
	
	virtual int IsENABLE(const int alid) = 0;

	virtual int Save() = 0;
	virtual int Upload() = 0;

	virtual int Init_BFF() = 0;
	virtual int Load_BFF(const int alid) = 0;
	virtual int Upload_BFF(int& alid,int& alcd,CString& altx) = 0;
	
	virtual int Init_LIST() = 0;
	virtual int Upload_LIST(int& alid,int& alcd,CString& altx) = 0;

	virtual int Is_ID_OFFSET(const CString& module,int& module_index) = 0;
};
