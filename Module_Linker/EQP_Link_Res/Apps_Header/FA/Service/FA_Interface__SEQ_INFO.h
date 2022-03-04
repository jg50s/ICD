#pragma once


class CI_SEQ_INFO
{
public:
	virtual ~CI_SEQ_INFO(){};

	//----------------------------------------------------
	virtual int  Get__Name_And_IP(CString& module_name,CString& module_ip) = 0;
	virtual int  Get__Dir_Root(CString& dir_root) = 0;
	virtual int  Get__Dir_Datalog(CString& dir_datalog) = 0;
	virtual int  Get__Dir_Process(CString& dir_process) = 0;
	virtual int  Get__Dir_Route(CString& dir_route) = 0;
	virtual int  Get__Dir_Cassette(CString& dir_cassette) = 0;
	virtual int  Get__Dir_Job(CString& dir_job) = 0;

	virtual int  Search_File(const CString& dir,const CString& file_ext,CStringArray& file_list) = 0;

	virtual int  Get__Date_And_Time(CString& time) = 0;											// yyyymmddhhmmsscc
	virtual int  Set__Date_And_Time(const CString& time) = 0;									// yyyymmddhhmmsscc

	//----------------------------------------------------
	virtual int  Search_Recipe_File_List_In_Module(const int seq_id,
						                           const CString& sub_dir,
						                           const CString& file_ext,
						                           CStringArray& rcp_file_list) = 0;

	virtual int  Get__Date_And_Time__With_2_Digit_Year(CString& time) = 0;						// yymmddhhmmss

	//----------------------------------------------------
	virtual int  Write__Bridge_Log(const CString& file_name,		
				                   const CString& log_msg) = 0;

	// ...
	virtual int  Get__Date_And_Time__YYYYMMDDhhmmss(CString& time) = 0;

	//----------------------------------------------------
	virtual int  Get__File_Name_And_File_Existence(const CString& dir,
												   const CString& file_ext,
												   const CStringArray& l_file_name,
												   CUIntArray& l_file_existence) = 0;			// existence : 1, absence : 0

	virtual int  Get__File_Name_And_File_ChangeTime(const CString& dir,
													const CString& file_ext,
												    CStringArray& l_file_name,
												    CStringArray& l_file_time) = 0;				// yyyymmddhhmmss

	virtual int  Get__ChangeTime_Of_File(const CString& dir,
										 const CString& file_ext,
								         const CStringArray& l_file_name,
										 CStringArray& l_file_time) = 0;						// yyyymmddhhmmss
};
