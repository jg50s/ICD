#pragma once


//----------------------------------------------------
class CI_STD_LIB_FA_300mm__CTRL
{
public:
	virtual ~CI_STD_LIB_FA_300mm__CTRL(){};

	//-------------------------------------------------------------------------
	virtual int Create(const CString& service_name) = 0;

	// Core : DB_CTRL에서 제어 ...
	virtual int Clear__All_Memory_Info() = 0;

	// ...
	virtual int Get__Thread_All_List_MSG(CString& list_msg) = 0;
};
//----------------------------------------------------

//----------------------------------------------------
class CI_STD_LIB_FA_300mm__LINK
{
public:
	virtual ~CI_STD_LIB_FA_300mm__LINK(){};

	//-------------------------------------------------------------------------
	virtual int Create_Ex(const int server_size,
						  const CString& service_name,
						  const CString& file_name) = 0;

	virtual int Stop_All_Service() = 0;
	virtual int Exit_All_Service() = 0;
};
//----------------------------------------------------

//----------------------------------------------------
class CI_STD_LIB_FA_300mm__DB_CTRL
{
public:
	virtual ~CI_STD_LIB_FA_300mm__DB_CTRL(){};

	//-------------------------------------------------------------------------
	virtual int Create(const CString& service_name) = 0;
};
//----------------------------------------------------

//----------------------------------------------------
class CI_STD_LIB_FA_300mm__VARIABLE_CTRL
{
public:
	virtual ~CI_STD_LIB_FA_300mm__VARIABLE_CTRL(){};

	//-------------------------------------------------------------------------
	virtual int Create(const CString& service_name) = 0;
};
//----------------------------------------------------

//----------------------------------------------------
class CI_STD_LIB_FA_300mm__SEQ_INFO
{
public:
	virtual ~CI_STD_LIB_FA_300mm__SEQ_INFO(){};

	//-------------------------------------------------------------------------
	virtual int Create(const CString& service_name) = 0;
};
//----------------------------------------------------
