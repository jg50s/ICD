#pragma once


class CI_FA_DB__CEID_CTRL
{
public:
	virtual ~CI_FA_DB__CEID_CTRL(){};

	virtual int SetDIR(const CString& dir,const CString& file) = 0;
	virtual int Save() = 0;
	virtual int Upload() = 0;

	virtual int Check(const int ceid) = 0;
	virtual int IsENABLE(const int ceid) = 0;
	virtual int SetALLBUFFER(const int status) = 0;
	virtual int SetBUFFER(const int ceid,const int status) = 0;
	virtual int ClearBUFFER() = 0;
	virtual int ApplyBUFFER() = 0;

	virtual int SetENABLE(const int ceid) = 0;
};
