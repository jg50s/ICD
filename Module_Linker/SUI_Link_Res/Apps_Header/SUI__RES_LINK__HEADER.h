#pragma once

#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__RES_LINK_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__RES_LINK_R.lib")
#endif


//----------------------------------------------------------------------------------
#define RCP_INTERLOCK__GET_PROC(FNC_NAME,CLS_TYPE)							\
int I##FNC_NAME(void *p_void,												\
			 const int i_row,											    \
			 const int i_col,											    \
			 CString& str_data)											    \
{																			\
	CLS_TYPE *p_class = (CLS_TYPE*) p_void;									\
																			\
	return p_class->FNC_NAME(i_row,i_col,str_data);							\
}
#define RCP_INTERLOCK__GET_FNC(FNC_NAME,CLS_TYPE)							\
int I##FNC_NAME(void *p_void,												\
			    const int main_fnc,											\
			    const int sub_fnc,											\
			    const CString& in_para,										\
			    const CStringArray& l_in_para,								\
			    CString& out_para,											\
			    CStringArray& l_out_para)									\
{																			\
	CLS_TYPE *p_class = (CLS_TYPE*) p_void;									\
																			\
	return p_class->FNC_NAME(main_fnc,										\
							 sub_fnc,										\
							 in_para,										\
							 l_in_para,										\
							 out_para,										\
							 l_out_para);									\
}


typedef int (*DLL_RCP_INTERLOCK__GET_PROC)(void* p_void,
										   const int i_row,
								      	   const int i_col,
									  	   CString& str_data);
typedef int (*DLL_RCP_INTERLOCK__GET_FNC)(void* p_void,
										  const int main_fnc,
										  const int sub_fnc,
										  const CString& in_para,
										  const CStringArray& l_in_para,
										  CString& out_para,
										  CStringArray& l_out_para);


class UII__RCP_INTERLOCK_CTRL
{
public:
	virtual ~UII__RCP_INTERLOCK_CTRL(){};

	// ...
	virtual int  Link__DLL_NAME(const CString& dll_name,
						        DLL_RCP_INTERLOCK__GET_PROC p_prc,
						        DLL_RCP_INTERLOCK__GET_FNC  p_fnc,
								void* p_void) = 0;

	// ...
	virtual int  Set__PROC(const int seq_id,
						   const int i_row,
					       const int i_col,
					       const CString& in_data,
						   CString& out_type,
						   CString& out_data) = 0;
	
	virtual int  Set__FNC(const int seq_id,
						  const int main_fnc,
						  const int sub_fnc,
						  const CString& in_para,
						  const CStringArray& l_in_para) = 0;

	// ...
	virtual void Set__DIR_ROOT(const CString& dir_root) = 0;

	// ...
	virtual int  Call__SUB_PAGE(const int seq_id,
								const int i_row,
								const int i_col,
								const CString& in_data,
								CString& out_type,
								CString& out_data) = 0;

	virtual int  Get__ALL_CHANNEL_OF_SUB_PAGE(const int seq_id,
											  const int i_col,	
											  CStringArray& l_ch_name,
											  CStringArray& l_ch_type,
											  CStringArray& l_ch_data) = 0;

	virtual int  Set__CHANNEL_OF_SUB_PAGE(const int seq_id,
										  const int i_col,
										  const CString& ch_name,
										  const CString& ch_data) = 0;

	virtual int  Get__ALL_TITLE_OF_SUB_PAGE(const int seq_id,
											CStringArray& l_title) = 0;

	// ...
	virtual int  Call__STEP_COPY(const int seq_id,
								 const int src_col,
								 const int trg_col) = 0;
	virtual int  Call__STEP_MOVE(const int seq_id, 
		                         const int src_col,
								 const int trg_col) = 0;
	virtual int  Call__STEP_DELETE(const int seq_id, 
		                           const int step_col) = 0;	
	virtual int  Call__STEP_SAVE(const int seq_id, 
		                         const int step_col,
								 CString& err_msg) = 0;

	// ...
	virtual int  Get__ALL_STEP_INFO_OF_ITEM(const int seq_id,
											const int db_index, 
											CString&  cur_item_name,
											CStringArray& l_item_data) = 0;

	virtual int  Get__CHANNEL_DATA_OF_SUB_PAGE(const int seq_id,
		                                       const int i_col,
											   const CString& ch_name,
											   CString& ch_data) = 0;

	// ...
	virtual int  Get__SUMMARY_INFO(const int seq_id,
								   const int step,
								   CStringArray& l_title,
								   CStringArray& l_data) = 0;
};

class UII__RCP_INTERLOCK_FEEDBACK
{
public:
	virtual ~UII__RCP_INTERLOCK_FEEDBACK(){};

	//.....
	virtual int  Link__RCP_PAGE(const int link_id) = 0;

	virtual int  Get__PROC(const int i_row,
						   const int i_col,
		  			       CString& str_data) = 0;

	virtual int  Get__FNC(const int main_fnc,
						  const int sub_fnc,
						  const CString& in_para,
						  const CStringArray& l_in_para,
						  CString& out_para,
						  CStringArray& l_out_para) = 0;
};

class UII__ALARM_DB_INFO
{
public:
	virtual ~UII__ALARM_DB_INFO(){};

	//.....
	virtual int  Upload__DB_FILE(const CString& dir_root) = 0;

	//
	virtual int  Get__USER_MSG(const int seq_id,const int alarm_id,CString& file_path) = 0;
	virtual int  Get__IMAGE(const int seq_id,const int alarm_id,CString& file_path) = 0;

	//
	virtual int  Check__RCS_ALARM_ID(const int seq_id,const int alarm_id) = 0;
};

class UII__FILE_CTRL
{
public:
	virtual ~UII__FILE_CTRL(){};

	//.....
	virtual int Set__Dir_Root(const CString& dir_root) = 0;
	virtual int Set__Key_Word(const CString& str_cmmd) = 0;
	virtual int Set__Para_Size(const int para_size) = 0;
	virtual int Disable__File_Log() = 0;

	virtual int Open(const CString& file_path) = 0;
	virtual int Read__File_Info() = 0;
	virtual int Close() = 0;

	virtual int Get__Item_List(CStringArray& l_item) = 0;
	virtual int Get__Item_List(CStringArray& l_para1,
							   CStringArray& l_para2) = 0;
	virtual int Get__Item_List(CStringArray& l_para1,
							   CStringArray& l_para2,
							   CStringArray& l_para3) = 0;
};

class UII__PAGE_INFO
{
public:
	virtual ~UII__PAGE_INFO(){};

	//.....
	virtual int Get__Current_ModuleID() = 0;
	virtual int Get__Current_Screen_Name(const int module_id,
										 CStringArray& l_page_name) = 0;
	virtual int Get__Current_Page_Data(const int module_id,
									   const CString& page_name,
									   CStringArray& l_ch_name,
									   CStringArray& l_ch_data) = 0;
};

class UII__FILE_ANALYSIS_CTRL
{
public:
	virtual ~UII__FILE_ANALYSIS_CTRL(){};

	//.....
	virtual int Set__Dir_Root(const CString& dir_root) = 0;

	virtual int Set__Main_Key_Word(const CString& str_cmmd) = 0;
	virtual int Set__Sub_Key_Word(const CString& str_cmmd) = 0;

	//
	virtual int Upload__File(const CString& file_path) = 0;

	//
	virtual int Get__Main_Item_List(CStringArray& l_item) = 0;
	virtual int Get__Sub_Item_List(const int db_index,
								   CStringArray& l_cmmd,
								   CStringArray& l_data) = 0;

	//
	virtual int Get__Dir_Date_List(const CString& dir_search,
								   CStringArray&  l_dir_name,
								   CStringArray&  l_dir_date) = 0;
	virtual int Get__File_List(const CString& dir_search,
							   const CString& file_ext,
							   CStringArray&  l_file_name) = 0;

	//
	virtual int Disable__File_Log() = 0;
	virtual int Set__Check_Mode(const int check_mode) = 0;

};

class UII__SYSTEM_INFO
{
public:
	virtual ~UII__SYSTEM_INFO(){};

	// Font .....
	virtual CString Get__System_Font_Name() = 0;

	virtual int Get__System_Font_Size__Main_Width()  = 0;
	virtual int Get__System_Font_Size__Main_Height() = 0;

	virtual int Get__System_Font_Size__Sub_Width()  = 0;
	virtual int Get__System_Font_Size__Sub_Height() = 0;

	// Version .....
	// Gui 
	virtual int Get__Gui_Core_Version_Info(CString& ver_title,
										   CStringArray& l_file_name,
										   CStringArray& l_ver_info,
										   CStringArray& l_file_date) = 0;

	virtual int Get__Gui_APPs_Version_Info(CString& ver_title,
										   CStringArray& l_file_name,
										   CStringArray& l_ver_info,
										   CStringArray& l_file_date) = 0;

	// Seq
	virtual int Get__Seq_List(CUIntArray& l_seq_id,
							  CStringArray& l_seq_name) = 0;

	virtual int Get__Seq_Core_Version_Info(const int seq_id,
										   CString& ver_title,
							  	  	       CStringArray& l_file_name,
									       CStringArray& l_ver_info,
									       CStringArray& l_file_date) = 0;
	virtual int Get__Seq_APPs_Version_Info(const int seq_id,
										   CString& ver_title,
							  	  	       CStringArray& l_file_name,
									       CStringArray& l_ver_info,
									       CStringArray& l_file_date) = 0;
	
	virtual int Get__Seq_Core_Ver_Title_List(CUIntArray& l_seq_id,
									         CStringArray& l_seq_ver_title) = 0;
	virtual int Get__Seq_APPs_Ver_Title_List(CUIntArray& l_seq_id,
									         CStringArray& l_seq_ver_title) = 0;

	// Version .....
	virtual double Get__Gui_Core_Version() = 0;

	// Font .....
	virtual int Set__System_Font_Name(const CString& font_name) = 0;
	
	virtual int Set__System_Font_Size__Main_Width(const int main_width)  = 0;
	virtual int Set__System_Font_Size__Main_Height(const int main_height) = 0;
	
	virtual int Set__System_Font_Size__Sub_Width(const int sub_width)  = 0;
	virtual int Set__System_Font_Size__Sub_Height(const int sub_height) = 0;
};

class UII__FILE_LOG_CTRL
{
public:
	virtual ~UII__FILE_LOG_CTRL(){};
	
	//-------------------------------------------------------------------------
	virtual int Init__FILE(const CString& dir_root) = 0;
	
	virtual int SET__LOG_FILE_TIME(const int time_hour)  = 0;
	virtual int SET__LOG_BACKUP_DATE_SIZE(const int day_count) = 0;

	virtual int Create__LOG_DIR(const CString& dir_root) = 0;

	//
	virtual int ENABLE__TIME_LOG()  = 0;
	virtual int DISABLE__TIME_LOG() = 0;

	//
	virtual int Write__LOG(const CString& string) = 0;	
};
//----------------------------------------------------------------------------------
