#pragma once


class CI_FA_DB__CEID_RPTID_CTRL
{
public:
	virtual ~CI_FA_DB__CEID_RPTID_CTRL(){};

	//----------------------------------------------------
	virtual int Init_CEID() = 0;
	virtual int Load_CEID(const int ceid) = 0;
	virtual int Load_RPTID(const int rptid) = 0;
	virtual int Save() = 0;

	virtual int Get_RPTID(const int ceid,CUIntArray& rptid_list) = 0;

	virtual int Change_Save() = 0;
};
