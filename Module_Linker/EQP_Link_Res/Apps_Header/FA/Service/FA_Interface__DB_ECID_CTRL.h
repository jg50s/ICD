#pragma once


class CDS_ECID_INFO
{
public:
	int		iECID;
	CString sUnit;
	double	dDefault;
	double	dMin;
	double	dMax;
	CString	sName;
};

class CDS_ECID_INFO_EX : public CDS_ECID_INFO
{
public:
	CString	sEQPID;
	CString sToolID;
	CString sUnitID;

	CString sDefault;
	CString sMin;
	CString sMax;
};

class CDS_ECID_DATA
{
public:
	int		iECID;
	CString sFmt_Type;
	int		iFmt_Byte;
	CString sData;
};

class CI_FA_DB__ECID_CTRL
{
public:
	virtual ~CI_FA_DB__ECID_CTRL(){};

	//----------------------------------------------------
	virtual int Is_SIZE() = 0;
	virtual int Is_ECID(const int ecid) = 0;
	
	virtual int Set_DATA(const int ecid,const double data) = 0;
	virtual int Get_DATA_WITH_ECID(const int ecid,CDS_ECID_DATA& ecid_data) = 0;
	virtual int Get_DATA_WITH_INDEX(const int db_index,CDS_ECID_DATA& ecid_data) = 0;

	virtual int Save_FILE() = 0;

	virtual int Get_INFO_WITH_ECID(const int ecid,CDS_ECID_INFO& ecid_info) = 0;
	virtual int Get_INFO_WITH_INDEX(const int db_index,CDS_ECID_INFO& ecid_info) = 0;

	virtual int Is_ENABLE__S6F9_REPORT() = 0;
	virtual int Get__INITIAL_CONTROL_STATE(int& state) = 0;

	virtual int Get_ECID__TIME_FORMAT() = 0;
	virtual int Get_ECID__COMMUNICATION_TIMEOUT() = 0;

	virtual int Init__SET_ECID_LIST() = 0;

	virtual int Set__INITIAL_CONTROL_STATE__ENABLE()  = 0;
	virtual int Set__INITIAL_CONTROL_STATE__DISABLE() = 0;

	virtual int Set__DEVICE_ID(const int device_id) = 0;

	// ...
	virtual int Set__T1(const int sec) = 0;
	virtual int Set__T2(const int sec) = 0;
	virtual int Set__T3(const int sec) = 0;
	virtual int Set__T4(const int sec) = 0;

	virtual int Set__T5(const int sec) = 0;
	virtual int Set__T6(const int sec) = 0;
	virtual int Set__T7(const int sec) = 0;
	virtual int Set__T8(const int sec) = 0;

	virtual int Set__LINK_TEST(const int sec) = 0;

	// ...
	virtual int Set__S5Fy_Reply(const int sx_reply) = 0;
	virtual int Set__S6Fy_Reply(const int sx_reply) = 0;
	virtual int Set__S10Fy_Reply(const int sx_reply) = 0;

	// ...
	virtual int Get_INFO_EX_WITH_ECID(const int ecid,CDS_ECID_INFO_EX& ecid_info) = 0;
	virtual int Get_INFO_EX_WITH_INDEX(const int db_index,CDS_ECID_INFO_EX& ecid_info) = 0;

	virtual int Get_ECID_LIST_OF_TOOLID(const CString& str_toolid,CUIntArray& l_ecid) = 0;
};
