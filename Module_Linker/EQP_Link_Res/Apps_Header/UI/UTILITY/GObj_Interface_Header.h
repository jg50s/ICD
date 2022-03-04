#ifndef _GOBJ_INTERFACE_HEADER_H_
#define _GOBJ_INTERFACE_HEADER_H_


//----------------------------------------------------------------------------------
#define VERSION_1_1				1.1

#define  MACRO_DECLARE__GOI_START											\
extern "C" __declspec(dllexport)											\
void Get__GOI__GET_VERSION(double& version,									\
						   int& debug_mode)									\
{																			\
	version = VERSION_1_1;													\
	debug_mode = 0;

#define  MACRO_DECLARE__GOI_END												\
}


//----------------------------------------------------------------------------------
class GObj__Parameter_Def
{
public:
	virtual ~GObj__Parameter_Def(){};

	//---------------------------------------------------------
	virtual int Register_Channel(const CString& key_word,
								 const CString& comment = "") = 0;
	virtual int Register_Command(const CString& key_word,
								 const CString& cmmd_type = "",
								 const CString& cmmd_list = "",
								 const CString& default_data = "",
								 const CString& comment = "") = 0;

	//------------------------------------------
	// Command List

	// @Comment
	// @User_Level
	// @Message
	
	// FontBox
	// FontBox.Ex
	// ListBox
	// Recipe
	// Color
	//------------------------------------------
};
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
#define  RES_TYPE__SWF				1
#define  RES_TYPE__PAGE_EXE			2
#define  RES_TYPE__GUI_ROOT			3


class GObj__Parameter_Ctrl
{
public:
	virtual ~GObj__Parameter_Ctrl(){};

	//---------------------------------------------------------
	virtual int Get_Obj_Dir(const int res_type,CString& res_dir) = 0;
	
	virtual int Get_Core_Info(const CString& key_word,CString& info_data) = 0;
	virtual COLORREF Get_RGB_Color(const CString& rgb_color,
								   int& r_color,
								   int& g_color,
								   int& b_color) = 0;

	//---------------------------------------------------------
	virtual int Get_Channel_Name(const CString& key_word,CString& ch_name)  = 0;
	virtual int Get_Channel_Data(const CString& key_word,CString& ch_data)  = 0;

	virtual int Get_Constant_Data(const CString& key_word,CString& const_data) = 0;

	//---------------------------------------------------------
	virtual int Set_Suffix_Feedback(const CString& key_word,const CString& ch_data) = 0;

	//---------------------------------------------------------
	virtual int Check__RealMode() = 0;

	//---------------------------------------------------------
	virtual int Make_Exe_Channel_List(const CStringArray& l_ch_name) = 0;

	//---------------------------------------------------------
	virtual int Change_Min__Suffix_Feedback(const CStringArray& l_key_word,
											const CString& min_data) = 0;
	virtual int Change_Max__Suffix_Feedback(const CStringArray& l_key_word,
											const CString& max_data) = 0;
	virtual int Change_Dec__Suffix_Feedback(const CStringArray& l_key_word,
											const CString& dec_data) = 0;

	//.....
	virtual int Set_Suffix_Feedback_With_ModuleID(const int module_id,
												  const CString& key_word,
												  const CString& ch_data) = 0;


	virtual int Get_Channel_Data_With_Check_Box(const CString& key_word,CString& ch_data)  = 0;

	//---------------------------------------------------------
	// 2008.11.18

	virtual int Check__Win_Level() = 0;

	//---------------------------------------------------------
	// 2009.06.19

	virtual int Get__Data_From_Ch_Name(const CString& ch_name,CString& ch_data) = 0;

	// ...
	virtual int Get__Ch_Index_From_Module_GUI_Ch_Name(const int seq_id,const CString& ch_name) = 0;

	virtual int Get__Data_From_Module_GUI_Ch_Name(const int seq_id,const CString& ch_name,CString& ch_data) = 0;
	virtual int Get__Data_From_Module_GUI_Ch_Index(const int seq_id,const int& ch_index,CString& ch_data) = 0;

	virtual int Set__Data_From_Module_GUI_Ch_Name(const int seq_id,const CString& ch_name,const CString& ch_data) = 0;

	
	//---------------------------------------------------------
	// ITEM_NAME   ITEM_DATA ...
	// CH_TYPE     ANALOG, DIGITAL, STRING
	// SET_DATA    Current Setting Data        
	// LIST        Data        (In only Digital)
	// MIN         Value       (In only Analog)
	// MAX         Value       (In only Analog)
	// UNIT        Unit Name   (In only Analog)

	virtual int Get__Channel_Info_From_Key_Word(const CString& key_word, CStringArray& l_item_name,CStringArray& l_item_data) = 0;
	virtual int Get__Channel_Info_From_Ch_Name(const CString& ch_name, CStringArray& l_item_name,CStringArray& l_item_data) = 0;
};
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
class GObj__Resource_Info
{
public:
	GObj__Resource_Info()
	{
		hDC = NULL;
		hDC_BACK = NULL;
		hDC_MEM  = NULL;
		pGOBJ_PARA_CTRL = NULL;

		iCLEAR_REQ = -1;
	}

	//.....
	HDC hDC;
	HDC hDC_BACK;
	HDC hDC_MEM;
	GObj__Parameter_Ctrl *pGOBJ_PARA_CTRL;

	int iCLEAR_REQ;
};

class GObj__Interface_Ctrl
{
public:
	virtual ~GObj__Interface_Ctrl(){};

	//---------------------------------------------------------
	virtual void Get_Parameter(GObj__Parameter_Def* p_obj_para_def) = 0;
	
	virtual void Set_Parameter(const int& module_id,
							   const POINT& st,
							   const POINT& et,
							   const HWND& hwnd,
							   GObj__Resource_Info *p_obj_res) = 0;

	virtual void Hide_Draw(const HWND& hwnd) { };
	virtual void Show_GObj(const HWND& hwnd) = 0;
	virtual void Hide_GObj() = 0;
	
	//---------------------------------------------------------
	virtual void WM_Paint(const HWND& hwnd) { };
	virtual void WM_Timer(const HWND& hwnd) { };
	
	virtual void WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd) { };
	virtual void WM_LButtonUp(const HWND& hwnd) { };

	virtual void WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd) { };
	virtual void WM_RButtonUp(const HWND& hwnd) { };

	virtual void WM_Notify(UINT message,const WPARAM wparam,LPARAM lparam) { };

	// 2014.08.11 Ãß°¡
	virtual void WM_LButtonUp_With_Point(const POINT& mouse_pt,const HWND& hwnd) { };
	virtual void WM_RButtonUp_With_Point(const POINT& mouse_pt,const HWND& hwnd) { };
};
//----------------------------------------------------------------------------------


#endif

