#pragma once


//----------------------------------------------------------------------------------------------------------------------
class CI_SEQ_NET_CTRL__Memory_Check
{
public:
	virtual ~CI_SEQ_NET_CTRL__Memory_Check(){};

	// ...
	virtual int Dump_To_File(const CString& path, const CString& log_title) = 0;

	// Core : DB_CTRL에서 제어 ...
	virtual int Clear__All_Memory_Info() = 0;

	// ...
	virtual int Get__Thread_All_List_MSG(CString& list_msg) = 0;
};	

class CI_SEQ_NET__CTRL
{
public:
	virtual ~CI_SEQ_NET__CTRL(){};

	//------------------------------------------------------------------------------
	virtual int  Load__MODULE_INFO(const CUIntArray& l_read_flag,
								   const CUIntArray& l_rw_all_flag,
								   const CUIntArray& l_init_reset,
								   const CStringArray& l_local_obj,
								   const CStringArray& l_local_var,
								   const CUIntArray& l_seq_id,
								   const CStringArray& l_remote_obj,
								   const CStringArray& l_remote_var) = 0;

	virtual	int  Make__MODULE_INFO() = 0;

	virtual int  Start__NET() = 0;
	virtual int  Stop__NET() = 0;
	//

	//------------------------------------------------------------------------------
	virtual int  Report__AlarmPost_To_CTC_GUI(const int sys_id,
											  const int alarm_id,
											  const int alarm_type, 
											  const CString& time,
											  const CString& title,
											  const CString& message,
											  const CStringArray& l_option_act,
											  const CStringArray& l_option_exp) = 0;

	virtual int  Report__AlarmDelete_To_CTC_GUI(const int sys_id,
											    const int alarm_id,
												const CString& title,
											    const CString& act_result,
												const CString& clear_time,
												const int gui_id) = 0;

	//------------------------------------------------------------------------------
	virtual int  Save__ECID_PARAMETER(const CUIntArray&   l_seq_id,
									  const CUIntArray&   l_ecid,
									  const CStringArray& l_name,
									  const CStringArray& l_data) = 0;

	//------------------------------------------------------------------------------
	virtual int  Stop__Server_NET() = 0;

	//------------------------------------------------------------------------------
	virtual int  Report__AlarmPost_To_CTC_GUI_EX(const int sys_id,
												 const int alarm_id,
												 const int alarm_type, 
												 const int host_report,
												 const int alarm_level,
												 const CString& ref_toolid,
												 const CString& ref_unitid,
												 const CString& time,
												 const CString& title,
												 const CString& message,
												 const CStringArray& l_option_act,
												 const CStringArray& l_option_exp) = 0;

	virtual int  Report__AlarmDelete_To_CTC_GUI_EX(const int sys_id,
												   const int alarm_id,
												   const int host_report,
												   const int alarm_level,
												   const CString& ref_toolid,
												   const CString& ref_unitid,
												   const CString& title,
												   const CString& act_result,
												   const CString& clear_time,
												   const int gui_id) = 0;

	//------------------------------------------------------------------------------
	virtual int  RMS__Create_File(const CString& bywho,const CString& file_name) = 0;
	virtual int  RMS__Modify_File(const CString& bywho,const CString& file_name) = 0;
	virtual int  RMS__Delete_File(const CString& bywho,const CString& file_name) = 0;
};	


//----------------------------------------------------------------------------------------------------------------------
class CI_SEQ_NET__MODULE_CTRL
{
public:
	virtual ~CI_SEQ_NET__MODULE_CTRL(){};

	//------------------------------------------------------------------------------
	virtual int Get__DATA(const CString& remote_channel,
						  CString& channel_data) = 0;

	virtual int Search__RECIPE_FILE_LIST_In_MODULE(const int seq_id,
												   const CString& sub_dir,
												   const CString& file_ext,
												   CStringArray& l_rcp_file) = 0;

	virtual int Check__RECIPE_FILE_In_MODULE(const int seq_id,
											 const CString& sub_dir,
											 const CString& file_name,
											 const CString& file_ext) = 0;

	virtual int Upload__RECIPE_FILE_In_MODULE(const int seq_id,
											  const CString& sub_dir,
											  const CString& file_name,
											  const CString& file_ext,
											  CString& file_data) = 0;

	virtual int Save__RECIPE_FILE_In_MODULE(const int seq_id,
											const CString& sub_dir,
											const CString& file_name,
											const CString& file_ext,
											const CString& file_data) = 0;


	//------------------------------------------------------------------------------
	virtual int Is__ONLINE(const int seq_id) = 0;


	//------------------------------------------------------------------------------
	virtual int Delete__RECIPE_FILE_In_MODULE(const int seq_id,
											  const CString& sub_dir,
											  const CString& file_name,
											  const CString& file_ext) = 0;

	virtual int Rename__RECIPE_FILE_In_MODULE(const int seq_id,
											  const CString& sub_dir,
											  const CString& file_ext,
											  const CString& src_file,
											  const CString& trg_file) = 0;
};
//----------------------------------------------------------------------------------------------------------------------

