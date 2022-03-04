#pragma once


class UII__SCREEN_USER_LEVEL_CTRL
{
public:
	virtual ~UII__SCREEN_USER_LEVEL_CTRL(){};

	//-------------------------------------------------------------------------
	virtual void Get__Win_Module_List(CUIntArray& l_module_id) = 0;

	virtual void Get__Win_List(const int module_id,
							   CStringArray& l_win_name,
							   CStringArray& l_win_title,
							   CStringArray& l_level) = 0;

	virtual void Set__Win_Level(const int module_id,
								const CString& win_name,
								const CString& win_level) = 0;

	virtual void Get__Win_Module_List_Ex(CUIntArray& l_module_id,
										 CStringArray& l_module_name) = 0;
};

class UII__SEQ_VERSION_INFO_CTRL
{
public:
	~UII__SEQ_VERSION_INFO_CTRL(){};

	//-------------------------------------------------------------------------	
	virtual void Get__Seq_List(CUIntArray& l_module_id) = 0;
	virtual void Get__Version_List(const int module_id,
							       CStringArray& l_obj_name,
							       CStringArray& l_obj_type,
							       CStringArray& l_obj_version) = 0;

	virtual void Get__Seq_List_Ex(CUIntArray& l_module_id,
								  CStringArray& l_module_name) = 0;
};

class UII__ANALOG_PAD_CTRL
{
public:
	virtual ~UII__ANALOG_PAD_CTRL(){};

	virtual int Popup(const CString& name, 
					  const CString& min_value,
					  const CString& max_value, 
					  const CString& init_data, 
					  const CString& unit,
					  CString& result) =0;
};

class UII__DIGITAL_PAD_CTRL
{
public:
	virtual ~UII__DIGITAL_PAD_CTRL(){};
	
	virtual int Popup(const CString& name, 
					  const CString& init_data, 
					  const CStringArray& l_data, 
					  CString& result) =0;
}; 

class UII__STRING_PAD_CTRL
{
public:
	virtual ~UII__STRING_PAD_CTRL(){};

	virtual int Popup(const CString& name,
					  const CString& init_data, 
					  CString& result) = 0;
};

class UII__FLASH_CTRL
{
public:
	virtual ~UII__FLASH_CTRL(){};

	//-------------------------------------------------------------------------	
	virtual int	 Init__FLASH(HWND hwnd,const CString& swf_path,POINT st, POINT et) = 0;

	virtual void Hide__FLASH() = 0;
	virtual void Show__FLASH() = 0;
	virtual void Move__FLASH(HWND hwnd) = 0;

	virtual int  Check__WM_LBUTTON() = 0;

	virtual int  Set__DATA(const CString& key_word,const CString& data) = 0;

	virtual int  Convert__RGB_To_BGR(const CString& rgb_data) = 0;
};

class UII__LAYERED_WIN_INTERFACE
{
public:
	virtual int Call__Create(POINT win_size) = 0;
	virtual int Call__Move(HDC hdc,POINT win_size) = 0;

	virtual int Call__Paint(HDC hdc,POINT win_size) = 0;
	virtual int Call__Timer(HWND hwnd,POINT win_size) = 0;

	virtual int Call__LButtonDown(HWND hwnd,POINT win_size) = 0;
	virtual int Call__LButtonUp(HWND hwnd,POINT win_size)   = 0;

	virtual int Call__RButtonDown(HWND hwnd,POINT win_size) = 0;
	virtual int Call__RButtonUp(HWND hwnd,POINT win_size)   = 0;
};

class UII__LAYERED_WIN_CTRL
{
public:
	virtual ~UII__LAYERED_WIN_CTRL(){};

	//-------------------------------------------------------------------------	
	virtual int Set__WIN_MASK_COLOR(COLORREF color) = 0;
	virtual COLORREF Get__WIN_MASK_COLOR() = 0;

	virtual int Set__WIN_SIZE(double x_rate,double y_rate) = 0;
	virtual int Set__WIN_TIMER(int msec) = 0;		// msec >= 10

	virtual int Init__WIN(HWND parent_hwnd,
						  POINT st,
						  POINT et,
						  UII__LAYERED_WIN_INTERFACE* p_win_interface) = 0;	
	virtual int Get__WIN_CENTER(POINT& cpt) = 0;

	virtual int Show__WIN() = 0;
	virtual int Hide__WIN() = 0;

	virtual int Is__CLICKED() = 0;

	virtual void Delete__WIN() = 0;
};
