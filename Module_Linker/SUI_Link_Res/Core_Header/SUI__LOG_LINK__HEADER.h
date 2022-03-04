#pragma once

#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__LOG_LINK_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__LOG_LINK_R.lib")
#endif


//-----------------------------------------------------------------------
class CCI__UTILITY_LOG_CTRL__LOG_CREATE
{
public:
	virtual ~CCI__UTILITY_LOG_CTRL__LOG_CREATE(){};

	// ...
	virtual int Create__LOG_SERVICE(const CString& service_name) = 0;
	
	virtual int Register__DIR_BOUNDARY(const CString& dir_boundary) = 0;
	virtual int Register__DIR_ROOT(const CString& dir_root) = 0;

	virtual int Register__BACKUP_SIZE(const int backup_size) = 0;
	
	virtual int Start__LOG_SERVICE() = 0;
};


// ...
#define QUERY__DIR_BOUNDARY			"QUERY.DIR_BOUNDARY"
#define QUERY__DIR_ROOT				  "QUERY.DIR_ROOT"
#define QUERY__BACKUP_SIZE			"QUERY.BACKUP_SIZE"


class CCI__UTILITY_LOG_CTRL__LOG_LINK
{
public:
	virtual ~CCI__UTILITY_LOG_CTRL__LOG_LINK(){};
	
	// ...
	virtual int Get__ALL_LOG_SERVICE(CStringArray& l_service_name) = 0;

	// ...
	virtual int Link__LOG_SERVICE(const CString& service_name) = 0;

	// ...
	virtual int Get__QUERY_AND_ANSWER(const CString& str_query,CString& str_answer) = 0;
	virtual int Get__LOG_MESSAGE_SIZE_IN_BUFFER() = 0;
	
	virtual int Write__LOG_MESSAGE(const CString& log_msg) = 0;

	// ...
	virtual int Set__REQ_DIRECTORY_BACKUP_CHECK() = 0;
};

class CCI__UI_PROPERTY_CTRL
{
public:
	virtual ~CCI__UI_PROPERTY_CTRL(){};

	// ...
	virtual int CustomColorBox__UPLOAD(const int i_size,COLORREF *p_color) = 0;
	virtual int CustomColorBox__SAVE(const int i_size,COLORREF *p_color)   = 0;
};
//-----------------------------------------------------------------------
