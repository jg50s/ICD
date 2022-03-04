#ifndef _UI__INTERFACE_EX_HEADER_H_
#define _UI__INTERFACE_EX_HEADER_H_


//----------------------------------------------------------------------------------
class CGI_FILE__PASSWORD_CTRL
{
public:
	virtual ~CGI_FILE__PASSWORD_CTRL(){};

	//-------------------------------------------------------------------------
	virtual int  Get__INFO_LIST(const int& seq_id,
							    CStringArray& level_list,
							    CStringArray& userid_list,
								CStringArray& password_list) = 0;

	virtual int  Add__INFO(const int& seq_id,
						   const CString& level,
						   const CString& userid,
						   const CString& password) = 0;

	virtual int  Delete__INFO(const int& seq_id,
							  const CString& userid) = 0;

	virtual int  Check__INFO(const int& seq_id,
							 const CString& userid,
							 const CString& password) = 0;
};

class CGI_FILE__ALARM_CTRL
{
public:
	virtual ~CGI_FILE__ALARM_CTRL(){};

	//-------------------------------------------------------------------------
	virtual int  Get__POST_INFO_LIST(CString& module_name,
									 int& sys_id,
									 int& alarm_id,
									 CString& alarm_type,
									 CString& time,
									 CString& title,
									 CString& message,
									 CStringArray& l_option_act,
									 CStringArray& l_option_exp) = 0;

	virtual int  Get__ALARM_SIZE() = 0;

	virtual int  Clear__ALARM_INFO(const CString& module_name,
								   const int sys_id,
								   const int alarm_id,
								   const CString& alarm_type,
								   const CString& act_result) = 0;

	//-------------------------------------------------------------------------
	virtual int  Get__ALARM_HISTORY__LOG_LIST(const CStringArray& pm_list,
											  CStringArray& pm_status,
											  CStringArray& log_list) = 0;
	
	virtual int  Get__ALARM_HISTORY__LOG_MSG(const CString& log_name,
											 const CStringArray& pm_status,
											 CString& log_msg) = 0;

	//-------------------------------------------------------------------------
	virtual int  Get__CLEAR_ALARM_INFO(CUIntArray& l_seq_id,
									   CUIntArray& l_sys_id,
									   CUIntArray& l_alm_id) = 0;

	virtual int  Delete__ALARM_INFO(const int seq_id,
								    const int sys_id,
								    const int alarm_id) = 0;

	//-------------------------------------------------------------------------
	virtual int  Get__POST_INFO_EX_LIST(CString& module_name,
								        int& sys_id,
		                                int& alarm_id,
		                                CString& alarm_type,
		                                int& host_report,
										int& alarm_level,
										CString& ref_toolid,
										CString& ref_unitid,
										CString& time,
		                                CString& title,
		                                CString& message,
		                                CStringArray& l_option_act,
		                                CStringArray& l_option_exp) = 0;

	//-------------------------------------------------------------------------
	virtual int  Get__POST_INFO_OF_TYPE_I(int& seq_id,
		                                  CString& seq_name,
		                                  int& sys_id,
		                                  int& alarm_id,
		                                  CString& alarm_type,
		                                  int& host_report,
		                                  int& alarm_level,
		                                  CString& ref_toolid,
		                                  CString& ref_unitid,
		                                  CString& time,
		                                  CString& title,
		                                  CString& message,
		                                  CStringArray& l_option_act,
		                                  CStringArray& l_option_exp) = 0;

	virtual int  Clear__ALARM_INFO_OF_TYPE_I(const int seq_id,
											 const CString& seq_name,
		                                     const int sys_id,
		                                     const int alarm_id,
		                                     const CString& alarm_type,
		                                     const CString& act_result) = 0;

	virtual int  Get__SEQID_And_TITLE_LIST(CUIntArray& l_seq_id,
		                                   CStringArray& l_seq_title) = 0;
};

class CGI__UTILITY_CTRL
{
public:
	virtual ~CGI__UTILITY_CTRL(){};

	//-------------------------------------------------------------------------
	virtual COLORREF Get__COLORREF(const CString& string) = 0;

	virtual int Get__CHANNEL_NAME(const CString& string,
								 CString& channel) = 0;

	virtual int Get__LOGFONT(const CString& font_name,
							LOGFONT& logfont) = 0;

	//-------------------------------------------------------------------------
	virtual int Popup__ANALOG_PAD(const CString& title,
								  const CString& min,
								  const CString& max,
								  const CString& in_data,
								  CString& out_data) = 0;

	virtual int Popup__DIGITAL_PAD(const CString& title,
								   const CStringArray& data_list,
								   const CString& in_data,
								   CString& out_data) = 0;


	virtual int Popup_Keyboard(const CString& title,
							   const CString& in_data,
							   CString& out_data) = 0;

	virtual int Popup_Password(const CString& title,
							   CString& out_data) = 0;

	//-------------------------------------------------------------------------
	virtual int Popup__ANALOG_PAD__WITH_UNIT(const CString& title,
											 const CString& min,
											 const CString& max,
											 const CString& unit,
											 const CString& in_data,
											 CString& out_data) = 0;

	//-------------------------------------------------------------------------
	virtual int Popup__FILE_SELECT(const CString& title,
								   const CStringArray& file_list,
								   const CStringArray& date_list,
								   CString& out_file_name) = 0;

	//-------------------------------------------------------------------------
	virtual int Popup__ANALOG_DIGITAL_PAD(const CString& analog_title,
	                                      const CString& analog_min,
	                                      const CString& analog_max,
	                                      const CString& analog_in_data,
	                                      const CString& digital_title,
	                                      const CStringArray& digital_data_list,
	                                      const CString& digital_in_data,
	                                      CString& analog_out_data,
	                                      CString& digital_out_data) = 0;

	virtual int Popup__DIGITAL_ANALOG_PAD(const CString& digital_title,
	                                      const CStringArray& digital_data_list,
	                                      const CString& digital_in_data,
	                                      const CString& analog_title,
	                                      const CString& analog_min,	
	                                      const CString& analog_max,	
	                                      const CString& analog_in_data,
	                                      CString& digital_out_data,
	                                      CString& analog_out_data) = 0;


	//-------------------------------------------------------------------------
	virtual int Popup__DIGITAL_PAD_EX(const HWND p_hwnd,
									  const POINT& cur_pt,
									  const CString& title,
									  const CStringArray& data_list,
									  const CString& in_data,
									  CString& out_data) = 0;

	// ...
};

class CGI_FILE__PM_CTRL
{
public:
	virtual ~CGI_FILE__PM_CTRL(){};

	//-------------------------------------------------------------------------
	virtual int  Get__FILE_LIST(const int& seq_id,
								const CString& sub_dir,
								const CString& file_ext,
								CStringArray& file_list) = 0;

	virtual int  Get__FILE_LIST(const int& seq_id,
								const CString& sub_dir,
								const CString& file_ext,
								CStringArray& file_list,
								CStringArray& date_list) = 0;

	virtual int  Delete__FILE(const int& seq_id,
							  const CString& sub_dir,
							  const CString& file_ext,
							  const CString& file_name) = 0;

	virtual int  Copy__FILE(const int& seq_id,
							const CString& sub_dir,
							const CString& file_ext,
							const CString& src_file,
							const CString& trg_file) = 0;

	virtual int  Rename__FILE(const int& seq_id,
							  const CString& sub_dir,
							  const CString& file_ext,
							  const CString& src_file,
							  const CString& trg_file) = 0;

	virtual int  Download__FILE(const int& seq_id,
								const CString& sub_dir,
								const CString& file_ext,
								const CString& file_name,
								const CString& file_data) = 0;

	virtual int  Upload__FILE(const int& seq_id,
							  const CString& sub_dir,
							  const CString& file_ext,
							  const CString& file_name,
							  CString& file_data) = 0;

	//-------------------------------------------------------------------------
	virtual int Popup_File_Control(const int& module_id,
								   const CString& sub_dir,
								   const CString& file_ext,
								   const CString& in_file_name,
								   CString& out_file_name) = 0;
	
	virtual int Popup_File_Select(const int& module_id,
								  const CString& sub_dir,
								  const CString& file_ext,
								  const CString& in_file_name,
								  CString& out_file_name) = 0;

	//-------------------------------------------------------------------------
	virtual int Get__DIR_LIST(const int& module_id,
							  CStringArray& l_dir) = 0;

	virtual int Get__DIR_LIST_EX(const int& module_id,
								 const CString& sub_dir,
							     CStringArray& l_dir) = 0;
};

class CGI_FILE__DATALOG_CTRL
{
public:
	virtual ~CGI_FILE__DATALOG_CTRL(){};

	//-------------------------------------------------------------------------
	virtual int  Get__DIR_LIST(const int& seq_id,
							   const CString& sub_dir,
							   CStringArray& dir_list) = 0;

	virtual int  Get__FILE_LIST(const int& seq_id,
								const CString& sub_dir,
								const CString& file_ext,
								CStringArray& file_list) = 0;

	virtual int  Get__FILE_LIST(const int& seq_id,
								const CString& sub_dir,
								const CString& file_ext,
								CStringArray& file_list,
								CStringArray& date_list) = 0;

	virtual int  Delete__FILE(const int& seq_id,
							  const CString& sub_dir,
							  const CString& file_ext,
							  const CString& file_name) = 0;

	virtual int  Copy__FILE(const int& seq_id,
							const CString& sub_dir,
							const CString& file_ext,
							const CString& src_file,
							const CString& trg_file) = 0;

	virtual int  Rename__FILE(const int& seq_id,
							  const CString& sub_dir,
							  const CString& file_ext,
							  const CString& src_file,
							  const CString& trg_file) = 0;

	virtual int  Upload__FILE(const int& seq_id,
							  const CString& sub_dir,
							  const CString& file_ext,
							  const CString& file_name,
							  CString& file_data) = 0;

	virtual int  Download__FILE(const int& seq_id,
							    const CString& sub_dir,
							    const CString& file_ext,
							    const CString& file_name,
							    const CString& file_data) = 0;

	//-------------------------------------------------------------------------
	virtual int Popup_File_Control(const int& module_id,
								   const CString& sub_dir,
								   const CString& file_ext,
								   const CString& in_file_name,
								   CString& out_file_name) = 0;
	
	virtual int Popup_File_Select(const int& module_id,
								  const CString& sub_dir,
								  const CString& file_ext,
								  const CString& in_file_name,
								  CString& out_file_name) = 0;

	virtual int Popup_File_Explorer(const int& module_id,
									const CString& sub_dir,
									const CString& file_ext,
									const CString& in_file_name,
									CString& out_file_name) = 0;

	// ...
	virtual int Get__DIR_DATE_LIST(const int& module_id,
								   const CString& sub_dir,
							       CStringArray& l_dir,
								   CStringArray& l_date) = 0;

	// ...
	virtual int Popup_File_Explorer_Using_Remote_Disk(const CString& dir_root,
													  const CString& file_ext,
													  const CString& in_file_name,
													  CString& out_file_name) = 0;
};

class CGI_FILE__ROOT_CTRL
{
public:
	virtual ~CGI_FILE__ROOT_CTRL(){};

	//-------------------------------------------------------------------------
	virtual int  Get__DIR_LIST(const int& seq_id,
							   const CString& sub_dir,
							   CStringArray& dir_list) = 0;

	virtual int  Get__FILE_LIST(const int& seq_id,
								const CString& sub_dir,
								const CString& file_ext,
								CStringArray& file_list) = 0;

	virtual int  Get__FILE_LIST(const int& seq_id,
								const CString& sub_dir,
								const CString& file_ext,
								CStringArray& file_list,
								CStringArray& date_list) = 0;

	virtual int  Delete__FILE(const int& seq_id,
							  const CString& sub_dir,
							  const CString& file_ext,
							  const CString& file_name) = 0;

	virtual int  Copy__FILE(const int& seq_id,
							const CString& sub_dir,
							const CString& file_ext,
							const CString& src_file,
							const CString& trg_file) = 0;

	virtual int  Rename__FILE(const int& seq_id,
							  const CString& sub_dir,
							  const CString& file_ext,
							  const CString& src_file,
							  const CString& trg_file) = 0;

	virtual int  Upload__FILE(const int& seq_id,
							  const CString& sub_dir,
							  const CString& file_ext,
							  const CString& file_name,
							  CString& file_data) = 0;

	virtual int  Download__FILE(const int& seq_id,
							    const CString& sub_dir,
							    const CString& file_ext,
							    const CString& file_name,
							    const CString& file_data) = 0;

	//.....
	virtual int Get__DIR_DATE_LIST(const int& module_id,
								   const CString& sub_dir,
							       CStringArray& l_dir,
								   CStringArray& l_date) = 0;
};

class CGI__CONFIG_CTRL
{
public:
	virtual ~CGI__CONFIG_CTRL(){};

	//-------------------------------------------------------------------------
	virtual int  Get__LOG_INFO(const int& seq_id,
							   CStringArray& channel_list,
							   CStringArray& win_list) = 0;

	virtual int  Get__IO_INFO(const int& seq_id,
							  const CString& io_type,	// 1 = RS232, 2 = INTERFACE, 3 = BOARD, 4 = DEVICE_NET
							  const int& in_out_type,	// 1 = IN, 2 = OUT
							  const CStringArray& para_list,
							  CStringArray& bd_no_list,
							  CStringArray& ch_no_list,
							  CStringArray& ch_name_list) = 0;
};

class CGI__SYSTEM_CTRL
{
public:
	virtual ~CGI__SYSTEM_CTRL(){};

	//-------------------------------------------------------------------------
	virtual int  Get__GUI_DIR_EXE(CString& dir_exe) = 0;


	virtual int  Get__SEQ_DIR_ROOT(const int& module_id,
								   CString& dir) = 0;

	virtual int  Get__SEQ_DIR_CONFIG(const int module_id,
									 CString& dir) = 0;

	virtual int  Get__SEQ_DIR_DATALOG(const int module_id,
									  CString& dir) = 0;

	virtual int  Get__SEQ_DIR_PROCESS(const int& module_id,
									  CString& dir) = 0;

	virtual int  Get__SEQ_DIR_ROUTE(const int module_id,
									CString& dir) = 0;

	virtual int  Get__SEQ_DIR_CASSETTE(const int module_id,
									   CString& dir) = 0;

	virtual int  Get__SEQ_DIR_JOB(const int module_id,
								  CString& dir) = 0;

	//-------------------------------------------------------------------------
	virtual int  Get__DEFINE_INFO(const int& module_id,
							      const CString& define,
							      CString& data) = 0;


	//-------------------------------------------------------------------------
	virtual int  Set__LOG_CHANNEL(const int& module_id,
								  const CStringArray& l_ch_name,
								  const CStringArray& l_ch_data) = 0;

};
//----------------------------------------------------------------------------------


#endif

