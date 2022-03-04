#pragma once


//------------------------------------------------------------------------------------------------
#define VERSION_1_1				1.1


#define  MACRO_DECLARE__FA_START											\
extern "C" __declspec(dllexport)											\
void Get__FA__GET_VERSION(double& version,									\
						  int& debug_mode)									\
{																			\
	version = VERSION_1_1;													\
	debug_mode = 0;

#define  MACRO_DECLARE__FA_END												\
}


//------------------------------------------------------------------------------------------------
#define  MACRO_DECLARE__OBJECT_FA__CLASS_LIST__START						\
extern "C" __declspec(dllexport)											\
void Get__OBJECT_FA__CLASS_LIST(CStringArray& l_class)						\
{

#define  MACRO_DECLARE__OBJECT_FA__CLASS_LIST__END							\
}


#define  MACRO_DECLARE__OBJECT_FA__CREATE__START							\
extern "C" __declspec(dllexport)											\
CI_OBJECT_FA_PROC* Create__OBJECT_FA(const CString& class_name)				\
{

#define  MACRO_DECLARE__OBJECT_FA__CREATE__END								\
	return NULL;															\
}


//------------------------------------------------------------------------------------------------
#define EMPTY__BODY   { return 0; }


#define FA__START_LOOP						\
try											\
{

#define FA__END_LOOP						\
}											\
catch (int r_flag)							\
{											\
	throw r_flag;							\
}											


#define FA__OK								throw  1;
#define FA__ERROR							throw -1;


//------------------------------------------------------------------------------------------------
class CDS__VID_INFO
{
public:
	CString sFmt_Type;
	int     iFmt_Byte;

	CString sUnit;
	CString sDisplay_Name;
};
class CDS__VID_DATA
{
public:
	void Init__DB()
	{
		sFmt_Type = "A";
		iFmt_Byte = 0;
		sData = "";

		sList__Sub_Fmt_Type1.RemoveAll();
		sList__Sub_Fmt_Type2.RemoveAll();
		sList__Sub_Fmt_Type3.RemoveAll();

		iList__Sub_Fmt_Byte1.RemoveAll();
		iList__Sub_Fmt_Byte2.RemoveAll();
		iList__Sub_Fmt_Byte3.RemoveAll();

		sList__Sub_Data1.RemoveAll();
		sList__Sub_Data2.RemoveAll();
		sList__Sub_Data3.RemoveAll();
	}

	CString sFmt_Type;
	int     iFmt_Byte;
	CString sData;

	CStringArray sList__Sub_Fmt_Type1;
	CStringArray sList__Sub_Fmt_Type2;
	CStringArray sList__Sub_Fmt_Type3;

	CUIntArray	 iList__Sub_Fmt_Byte1;
	CUIntArray	 iList__Sub_Fmt_Byte2;
	CUIntArray	 iList__Sub_Fmt_Byte3;

	CStringArray sList__Sub_Data1;
	CStringArray sList__Sub_Data2;
	CStringArray sList__Sub_Data3;	
};

class CI__VID_DB_Ctrl
{
public:
	~CI__VID_DB_Ctrl() {};

	//-------------------------------------------------------------------------
	virtual int Check__VID(const int vid) = 0;

	virtual int Get__VID_INFO(const int vid,    
						      CDS__VID_INFO& vid_info) = 0;
	virtual int Get__VID_INFO(const int db_index,
						      int& vid,
						      CDS__VID_INFO& vid_info) = 0;

	virtual int Get__VID_DATA(const int vid,
							  CDS__VID_DATA& vid_data) = 0;
	virtual int Get__VID_DATA(const int db_index,
						      int& vid,
							  CDS__VID_DATA& vid_data) = 0;
};

//------------------------------------------------------------------------------------------------
class CI__SEQ_Ctrl
{
public:
	~CI__SEQ_Ctrl() {};

	//-------------------------------------------------------------------------
};

//------------------------------------------------------------------------------------------------
class CI__VARIABLE_Ctrl
{
public:
	~CI__VARIABLE_Ctrl() {};

	//-------------------------------------------------------------------------
};

//------------------------------------------------------------------------------------------------
class CI_SxFy__Send_DB_Ctrl
{
public:
	~CI_SxFy__Send_DB_Ctrl() {};

	//-------------------------------------------------------------------------
	virtual int Get_Info_From_DB_Name(const CString& db_name,
									  int& fmt_type,
									  int& fmt_byte) = 0;
	virtual int Get_Info_From_Var_Name(const CString& var_name,
									   CString &db_name,
									   int& fmt_type,
									   int& fmt_byte) = 0;

	//-------------------------------------------------------------------------
	virtual int Add_List(const CString& db_name,const int list_size) = 0;
	
	virtual int Add_Binary(const CString& db_name,const int bin) = 0;
    virtual	int Add_Binary_Array(const CString& db_name,const int bin) = 0;

	virtual int Add_Boolean(const CString& db_name,const BOOL bool_value) = 0;
	virtual int Add_Boolean_Array(const CString& db_name,const BOOL bool_value) = 0;

	virtual int Add_Ascii(const CString& db_name,const CString& ascii) = 0; 

  	virtual int Add_I1(const CString& db_name,const int i_value) = 0;
  	virtual int Add_I1_Array(const CString& db_name,const int i_value) = 0;
  	virtual int Add_I2(const CString& db_name,const int i_value) = 0;
  	virtual int Add_I2_Array(const CString& db_name,const int i_value) = 0;
	virtual int Add_I4(const CString& db_name,const long l_value) = 0;
	virtual int Add_I4_Array(const CString& db_name,const long l_value) = 0;
	virtual int Add_I8(const CString& db_name,const long l_value) = 0;
	virtual int Add_I8_Array(const CString& db_name,const long l_value) = 0;
  
	virtual int Add_F4(const CString& db_name,const double d_value) = 0;
	virtual int Add_F4_Array(const CString& db_name,const double d_value) = 0;
	virtual int Add_F8(const CString& db_name,const double d_value) = 0;
	virtual int Add_F8_Array(const CString& db_name,const double d_value) = 0;

	virtual int Add_U1(const CString& db_name,const unsigned int u_value) = 0;
	virtual int Add_U1_Array(const CString& db_name,const unsigned int u_value) = 0;
	virtual int Add_U2(const CString& db_name,const unsigned int u_value) = 0;
	virtual int Add_U2_Array(const CString& db_name,const unsigned int u_value) = 0;
	virtual int Add_U4(const CString& db_name,const unsigned long u_value) = 0;
	virtual int Add_U4_Array(const CString& db_name,const unsigned long u_value) = 0;
	virtual int Add_U8(const CString& db_name,const unsigned long u_value) = 0;
	virtual int Add_U8_Array(const CString& db_name,const unsigned long u_value) = 0;


	virtual int Add_Virtual(const CString& db_name,const CString& unit_type,const int unit_size,const CString& data) = 0;
	//virtual int Add_Virtual(const CString& db_name,const CDS_SVID_DATA& svid_data) = 0;
	//virtual int Add_Virtual(const CString& db_name,const CDS_ECID_DATA& ecid_data) = 0;
	//virtual int Add_Virtual(const CString& db_name,const CDS_ATTR_DATA& attr_data) = 0;
};
class CI_SxFy__Recv_DB_Ctrl
{
public:
	~CI_SxFy__Recv_DB_Ctrl() {};

	//-------------------------------------------------------------------------
	virtual int Get_Data(const CString& db_name,
						 int& type,
						 CString& first_data,
						 CStringArray& data_list) = 0;

	virtual int Get_Data(const CString& db_name,
						 CString& data) = 0;
};

//------------------------------------------------------------------------------------------------
class CI_SxFy__Send_Ctrl
{
public:
	~CI_SxFy__Send_Ctrl() {};

	//-------------------------------------------------------------------------
	CI_SxFy__Send_DB_Ctrl *pSxFy__Send_DB_Ctrl;
	CI_SxFy__Recv_DB_Ctrl *pSxFy__Recv_DB_Ctrl;

	//-------------------------------------------------------------------------
	virtual int Send__SxFy() = 0;
	virtual int Wait__SxFy() = 0;

	//
	virtual CI__VARIABLE_Ctrl* Get__VARIABLE_Ctrl() = 0;
	virtual CI__VID_DB_Ctrl* Get__VID_DB_Ctrl() = 0;
	virtual CI__SEQ_Ctrl* Get__SEQ_Ctrl() = 0;
};
class CI_SxFy__Recv_Ctrl
{
public:
	~CI_SxFy__Recv_Ctrl() {};

	//-------------------------------------------------------------------------
	CI_SxFy__Send_DB_Ctrl *pSxFy__Send_DB_Ctrl;
	CI_SxFy__Recv_DB_Ctrl *pSxFy__Recv_DB_Ctrl;

	//-------------------------------------------------------------------------
	virtual int Send__SxFy() = 0;

	//
	virtual CI__VARIABLE_Ctrl* Get__VARIABLE_Ctrl() = 0;
	virtual CI__VID_DB_Ctrl* Get__VID_DB_Ctrl() = 0;
	virtual CI__SEQ_Ctrl* Get__SEQ_Ctrl() = 0;
};


//------------------------------------------------------------------------------------------------
class CI_OBJECT_FA_PROC
{
public:
	virtual ~CI_OBJECT_FA_PROC(){};

	//-------------------------------------------------------------------------
	virtual int Define__VERSION_HISTORY(CString& version) = 0;

	virtual int Define__VARIABLE() EMPTY__BODY;
	virtual int Define__CONSTANT() EMPTY__BODY;

	//-------------------------------------------------------------------------
	virtual int Initialize__OBJECT() = 0;

	//-------------------------------------------------------------------------
	virtual int Init__PROC() EMPTY__BODY;

	//-------------------------------------------------------------------------
	virtual void Send__MSG(const int sx,
						   const int fy,
						   const int type,
						   CI_SxFy__Send_Ctrl* p_ctrl) = 0;

	virtual void Recv__MSG(const int sx,
						   const int fy,
						   const int type,
						   CI_SxFy__Recv_Ctrl* p_ctrl) = 0;

	//-------------------------------------------------------------------------
	virtual int Close__PROC() EMPTY__BODY;
};
//------------------------------------------------------------------------------------------------
