#pragma once


//--------------------------------------------------------------------
class CI__SYSTEM_INFO
{
public:
	//-------------------------------------------------------
	virtual ~CI__SYSTEM_INFO(){};

	//-------------------------------------------------------
	virtual int  Upload__PAGE_CHECK(const CString& file_path) = 0;
	virtual void Set__Popup_Page_Redraw(const bool popup_redraw) = 0;

	virtual int  Call__WM_Timer() = 0;
};


//--------------------------------------------------------------------
class CI__WIN_CTRL
{
public:
	//-------------------------------------------------------
	virtual ~CI__WIN_CTRL(){};

	//-------------------------------------------------------
	virtual int  Check__WIN_LEVEL(const CString& page_name) = 0;
};

class CInterface__DS_MODEL_CTRL
{
public:
	int iMODULE_ID;

	//-------------------------------------------------------
	virtual ~CInterface__DS_MODEL_CTRL(){};

	//-------------------------------------------------------
	virtual int  Get_All_Channel_List(CStringArray& l_gui_channel,
									  CStringArray& l_seq_channel,
									  CStringArray& l_log_sim_channel) = 0;

	virtual int  Get_Rcp_Channel_Name_List(CStringArray& rcp_channel_name_list) = 0;
};

class CInterface_Lib__WINDOW
{
public:
	//-----------------------------------------------------------
	//------------------------------------------
	int iModule_ID;
	CInterface__DS_MODEL_CTRL *pI_dsMODEL;

	
	//------------------------------------------
	int iFlash_Window_Flag;
	int iExe_Window_Flag;
	int iExe_Status;
	int iLayered_Window_Flag;

	CString sScreen_Name;
	CString sScreen_Title;

	int iPopup_Type;
	POINT pSt;
	POINT pSize;
	int iShow_Flag;

	int iGui_Ctrl;
	CString sCtrl_Channel_Name;

	CString sUser_Level;
	int iUser_Level;

	int iPage_Type;
	CString sStatus_Channel;

	int iPage_Password_Channel;
	CString sPage_Password_Channel;
	CString sPage_Password_Data;

public:
	//-----------------------------------------------------------
	virtual ~CInterface_Lib__WINDOW(){};

	//-----------------------------------------------------------
	virtual void Create(const HWND p_hwnd,
						const CString& scr_title,
						const CString& path,
						const CString& dir_root,
						const POINT& st,
						const POINT& size,
						const int popup_type) = 0;

	virtual int  Screen_Close() = 0;

	virtual int  Check__File(const CString& path) = 0;
	virtual int  Get__Scr_File_Name(const CString& path,
									CString& scr_file) = 0;

	// ...
	virtual	void Upload__Flash_File(const CString& flash_file_path,
									const CString& scr_file_path,
									const CString& back_dir,
									const int module_id) = 0;

	virtual void Upload__Scr_File(const CString& scr_file_path,
								  const CString& back_dir,
								  const int module_id,
								  const int goi__test_flag,
								  const CStringArray& l_goi_name) = 0;

	// ...
	virtual void Init__Screen() = 0;

	virtual int  Set_Rcp_Channel_ID_List(const CStringArray& rcp_channel_name_list,
								  	     const CUIntArray& rcp_channel_id_list) = 0;

	virtual void Show__Window() = 0;
	virtual void Hide__Window(const int clear_req) = 0;	

	//-----------------------------------------------------------
	virtual int  Start__Exe_Page(const int module_id,const CString& page_name) = 0;
	virtual int  Stop__Exe_Page( const int module_id,const CString& page_name) = 0;

	//.....
	virtual int  Get_All_Channel_List(CStringArray& l_gui_channel,
									  CStringArray& l_seq_channel,
									  CStringArray& l_log_sim_channel) = 0;

	//-----------------------------------------------------------
	virtual int  Save__Config_Page(const CStringArray& l_ch_name,
								   const CStringArray& l_ch_data) = 0;

	// ...
	virtual void Redraw__Window() = 0;

	//-----------------------------------------------------------
	virtual int  Part__Callback(const CString& cmmd_name,
		                        const CStringArray& l_para,
								CStringArray& l_rsp1,
								CStringArray& l_rsp2,
								CStringArray& l_rsp3) = 0;
};
//--------------------------------------------------------------------
