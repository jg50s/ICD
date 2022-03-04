#pragma once


class CI_FA_DB__RPTID_SVID_CTRL
{
public:
	virtual ~CI_FA_DB__RPTID_SVID_CTRL(){};

	//----------------------------------------------------
	virtual int Init_RPTID() = 0;
	virtual int Load_RPTID(const int rptid) = 0;
	virtual int Load_SVID(const int svid) = 0;
	virtual int Save() = 0;

	virtual int Is_RPTID(const int rptid) = 0;
	virtual int Get_SVID(const int rptid,CUIntArray& svid_list) = 0;

	virtual int Change_Save() = 0;
};
