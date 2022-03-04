#pragma once


class CDS_SVID_TRACE_INFO
{
public:
	void Clear()
	{
		iTRID   = 0;
		iDSPER  = 1;
		iTOTSMP = 0;
		iREPGSZ = 0;

		iSVID_LIST.RemoveAll();
	}

	// ...
	int iTRID;
	int iDSPER;
	int iTOTSMP;
	int iREPGSZ;

	CUIntArray iSVID_LIST;
};
class CDS_SVID_TRACE_INFO_EX
{
public:
	CDS_SVID_TRACE_INFO_EX()
	{
		Clear();
	}

	void Clear()
	{
		// ...
		iTRID   = 0;
		iDSPER  = 1;
		iTOTSMP = 0;
		iREPGSZ = 0;
		
		iSVID_LIST.RemoveAll();
		
		// ...
		iFLAG__CENTISECONDS_REPORT = -1;
		dDSPER_CC = 1.0;
	}
	
	// ...
	int iTRID;
	int iDSPER;
	int iTOTSMP;
	int iREPGSZ;
	
	CUIntArray iSVID_LIST;
	
	// ...
	int iFLAG__CENTISECONDS_REPORT;
	double dDSPER_CC;
};

class CI_FA_DB__SVID_TRACE_CTRL
{
public:
	virtual ~CI_FA_DB__SVID_TRACE_CTRL(){};

	//----------------------------------------------------
	virtual int Add_TRACE(const CDS_SVID_TRACE_INFO& trace_info) = 0;
	
	virtual int Start_TRACE(const int trid) = 0;
	virtual int Stop_TRACE(const int trid) = 0;

	virtual int Get_TRACE_INFO(const int trid,int& smpln,CUIntArray& svid_list) = 0;
	virtual int Get_TRACE_INFO_EX(const int trid,int& smpln,CPtrArray& l_data) = 0;
	virtual int Get_TRACE_TOTAL_INFO(const int trid,int& smpln,CUIntArray& l_svid,CStringArray& l_stime,CPtrArray& l_data) = 0;

	virtual int Stop_ALL_TRACE() = 0;

	// ...
	virtual int Delete_TRACE_INFO(CPtrArray& l_info) = 0;

	// ...
	virtual int Set__TOOLID_OF_TRID(const int trid,const CString& toolid) = 0;
	virtual int Set__UNITID_OF_TRID(const int trid,const CString& unitid) = 0;

	virtual int Get__TOOLID_OF_TRID(const int trid,CString& toolid) = 0;
	virtual int Get__UNITID_OF_TRID(const int trid,CString& unitid) = 0;

	// ...
	virtual int Add_TRACE_EX(const CDS_SVID_TRACE_INFO_EX& trace_info_ex) = 0;
};
