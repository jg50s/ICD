#pragma once


class CDS_LIMIT_VID_INFO
{
public:
	int     iDEFINE_VID;
	int     iVID;
	CString sUNIT;
	double  dLIMIT_MIN;
	double  dLIMIT_MAX;

	int     iDEFINE_LIMITID;
	int     iLIMIT_ID;
	double  dUPPER_DB;
	double  dLOWER_DB;
};


class CI_FA_DB__LIMIT_VID_CTRL
{
public:
	virtual ~CI_FA_DB__LIMIT_VID_CTRL(){};

	//----------------------------------------------------
	virtual int Is_VID(const int vid) = 0;

	virtual int Get_INFO(const int vid,    
			             CDS_LIMIT_VID_INFO& vid_info) = 0;
	virtual int Get_INFO(const int db_index,
			             int& vid,
			             CDS_LIMIT_VID_INFO& vid_info) = 0;

	//----------------------------------------------------
	virtual int Undefine_BFF__ALL_VID() = 0;

	virtual int Undefine_BFF__VID(const int vid) = 0;
	virtual int Load_BFF__VID(const int vid) = 0;

	virtual int Undefine_BFF__ALL_LIMITID(const int vid) = 0;
	virtual int Undefine_BFF__LIMITID(const int vid,
									  const int limit_id) = 0;
	virtual int Load_BFF__LIMITID(const int vid,
								  const int limit_id) = 0;

	virtual int Load_BFF__LOWERDB_UPPERDB(const int vid,
										  const int limit_id,
										  const double lower_db,
									      const double upper_db) = 0;

	virtual int Init_BFF()  = 0;
	virtual int Clear_BFF() = 0;

	virtual int Save_BFF()  = 0;

	//----------------------------------------------------
	virtual int Get_CEID_INFO(const int db_index,
			                  int& ceid,
				              CDS_LIMIT_VID_INFO& vid_info) = 0;

	virtual int Set_CEID__UpperDB(const int ceid) = 0;
	virtual int Set_CEID__LowerDB(const int ceid) = 0;
};
