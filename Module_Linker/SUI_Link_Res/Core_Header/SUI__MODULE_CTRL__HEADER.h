#pragma once

#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__MODULE_CTRL_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__MODULE_CTRL_R.lib")
#endif


//----------------------------------------------------
class CGui__DB_Ctrl
{
public:
	virtual ~CGui__DB_Ctrl(){};

	//--------------------------------------------------------------------
	virtual int  Get__GUI_CHANNEL_INDEX(const int module_id,
										const CString& ch_name) = 0;

	virtual int  Get__GUI_CHANNEL_DATA(const int module_id,
									   const int db_index,
									   CString& ch_data) = 0;

	virtual int  Set__GUI_CHANNEL_DATA(const int module_id,
									   const CString& ch_name,
									   const CString& ch_data) = 0;
};
//----------------------------------------------------
