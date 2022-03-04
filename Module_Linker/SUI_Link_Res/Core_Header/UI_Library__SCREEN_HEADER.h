#pragma once


//----------------------------------------------------------------------------------------------------------------------
class CInterface__CHANNEL_CTRL
{
public:
	virtual ~CInterface__CHANNEL_CTRL(){};

	//-------------------------------------------------------------
	virtual int  Load__CHANNEL(const int module_id,const CString& channel) = 0;
	virtual int  Get__CHANNEL_DATA(const int module_id,const int db_index,CString& channel) = 0;

	//-------------------------------------------------------------
	virtual int  Get__CHANNEL_INDEX(const int module_id,
								    const CString& channel_name) = 0;
};

class CInterface__LOG_CHANNEL_CTRL
{
public:
	virtual ~CInterface__LOG_CHANNEL_CTRL(){};
	
	//-------------------------------------------------------------
	virtual int  Load__CHANNEL(const int module_id,const CString& channel) = 0;
	virtual int  Get__CHANNEL_DATA(const int module_id,const int db_index,CString& channel) = 0;
	
	//-------------------------------------------------------------
	virtual int  Get__CHANNEL_INDEX(const int module_id,
								    const CString& channel_name) = 0;
};

class CInterface__SCREEN_CHANNEL_CTRL
{
public:
	virtual ~CInterface__SCREEN_CHANNEL_CTRL(){};

	//-------------------------------------------------------------
	virtual int  Load__GUI_CHANNEL(const int module_id,
								   const CString& channel) = 0;
	
	virtual int  Get__GUI_CHANNEL_DATA(const int module_id,
									   const int db_index,
									   CString& channel) = 0;
	virtual int  Get__GUI_CHANNEL_DATA(const int module_id,
									   const CString& ch_name,
									   CString& ch_data,
									   int& click_count,
									   int& ch_type,
									   CStringArray& l_item) = 0;

	virtual int  Set__GUI_CHANNEL_DATA(const int module_id,
									   const CString& channel_name,
									   const CString& data_result) = 0;
	virtual int  Set__GUI_CHANNEL_DATA(const int module_id,
									   const CStringArray& l_gui_channel,
									   const CStringArray& l_gui_data) = 0;

	//-------------------------------------------------------------
	virtual int  Get__GUI_CHANNEL_INDEX(const int module_id,
										const CString& channel_name) = 0;

	virtual int  Click__Gui_Page() = 0;
};	

class CInterface__SYS_INFO 
{
public:
	virtual ~CInterface__SYS_INFO(){};

	//-------------------------------------------------------------
	virtual int  Get__USER_LEVEL_ID(CString& user_level) = 0;
	virtual int  Get__DEFINE_DATA(const int module_id,const CString& key_word,CString& data) = 0;

	//-------------------------------------------------------------
	virtual int  Check__DEF_CHANNEL(const int module_id,CString& str_ch) = 0;

	virtual int  Get__KEYPAD_FLAG(CString& str_data) = 0;
	
	virtual int  Check__EVENT_ENABLE__LBUTTON_UP() = 0;

	virtual int  Get__PIXEL_BIT_COUNT() = 0;
};
//----------------------------------------------------------------------------------------------------------------------
