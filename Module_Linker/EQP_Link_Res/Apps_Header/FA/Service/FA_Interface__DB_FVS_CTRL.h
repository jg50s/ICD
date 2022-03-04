#pragma once


class CI_FA_DB__FVS_CTRL
{
public:
	virtual ~CI_FA_DB__FVS_CTRL(){};

	//----------------------------------------------------
	virtual int Get_Index_From_CEID(const int ceid) = 0;

	virtual int Get_PFCD_From_Index(const int ceid_index,int& pfcd) = 0;
	virtual int Get_DATAID_From_Index(const int ceid_index,int& dataid) = 0;

	virtual int Get_DSID_SIZE(const int ceid_index) = 0;
	virtual int Get_DSID_From_Index(const int ceid_index,
								    const int dsid_index,
									int& dsid,CString& fmt_type) = 0;

	virtual int Get_VID_SIZE(const int ceid_index,const int dsid_index) = 0;
	virtual int Get_VID_INF_From_Index(const int ceid_index,
									   const int dsid_index,
									   const int vid_index,
									   int& vid,
									   CString& format,
									   int& size) = 0;
};
