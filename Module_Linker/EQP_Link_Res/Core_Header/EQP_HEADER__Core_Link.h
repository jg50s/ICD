#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Core_Header\EQP_UI_HEADER.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\EQP\Interface\Object_Interface.h"


//----------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------
class CI_SEQ_DB_CTRL__Memory_Check
{
public:
	virtual ~CI_SEQ_DB_CTRL__Memory_Check(){};

	// ...
	virtual int Dump_To_File(const CString& path, const CString& log_title) = 0;

	// ...
	virtual int Get__Thread_All_List_MSG(CString& list_msg) = 0;
};


//----------------------------------------------------------------------------------------------------------------------
class CII_AWI__OBJECT_UTILITY_CTRL
{
public:
	virtual ~CII_AWI__OBJECT_UTILITY_CTRL(){};

	//-------------------------------------------------------------------------
	virtual int Search__OBJECT_INDEX_AND_VARIABLE_INDEX(const CString& obj_name,
														const CString& var_name,
														int& obj_index,
														int& var_type,
														int& var_index) = 0;

	virtual int Get__OBJECT_CTRL_STATUS(const int obj_index,
										CString& ctrl_sts) = 0;

	virtual int Get__VARIABLE_DATA(const int obj_index,
								   const int var_type,
								   const int var_index,
								   CString& var_data) = 0;
	virtual int Set__VARIABLE_DATA(const int obj_index,
								   const int var_type,
								   const int var_index,
								   const CString& var_data) = 0;

	virtual int Get__OBJECT_INDEX(const CString& obj_name) = 0;


	//-------------------------------------------------------------------------
	virtual int EXTERNAL__Popup_MESSAGE_BOX(const int alarm_id,
											const CString& title,
										    const CString& message,
										    const CStringArray& l_option,
										    CString& act_result) = 0;

	virtual int EXTERNAL__Popup_ALARM_BOX(const int alarm_id,
										  const CString& title,
										  const CString& message,
										  const CStringArray& l_option,
										  CString& act_result) = 0;

	//
	virtual int EXTERNAL__Post_ALARM(const int alarm_id,
									 const CString& title,
					 				 const CString& message,
									 const CStringArray& l_option) = 0;

	virtual int EXTERNAL__Post_WARNING(const int alarm_id,
									   const CString& title,
									   const CString& message,
									   const CStringArray& l_option) = 0;

	virtual int EXTERNAL__Check_ALARM(const int sys_id,
									  const int alarm_id,
									  CString& act_result) = 0;

	//
	virtual int EXTERNAL__Clear_MODULE_ALARM(const int seq_id) = 0;

	//
	virtual	int EXTERNAL__Is_SIZE() = 0;

	virtual int EXTERNAL__Get_POST_ALARM(const int db_index,
										 CString *module,
										 CString *alarm_type,
										 CString *time,  
										 CString *alarm_id,
										 CString *title, 
										 CString *message,
										 CStringArray *l_option) = 0;
	
	virtual int EXTERNAL__Get_CLEAR_ALARM(CString *module,
										  CString *alarm_type,
									      CString *time,  
										  CString *alarm_id,
									      CString *title, 
										  CString *act_result) = 0;

	//-------------------------------------------------------------------------
	virtual int Set__CYCLE_LIMIT(const int cycle_limit) = 0;

	virtual int Start__PM_DATALOG(const CString& path) = 0;
	virtual int Start__PM_DATALOG(const CString& path,const int module_id, const CString& log_msg = "") = 0;

	virtual int Stop__PM_DATALOG() = 0;
	virtual int Stop__PM_DATALOG(const int module_id) = 0;

	//-------------------------------------------------------------------------
	virtual int Get__ANALOG_INFO(const int obj_index,
								 const int var_index,
								 const int var_type,
								 double& min_vaule,
								 double& max_vaule,
								 int& dec) = 0;

	//
	virtual int Get__DIGITAL_INFO(const int obj_index,
								  const int var_index,
								  const int var_type,
								  CStringArray& l_item) = 0;

	virtual int Get__DESCRIPTOR_INFO(const CString& obj_name,
							    	 const CString& descriptor_name,
									 CStringArray& l_item) = 0;

	//-------------------------------------------------------------------------
	virtual int Set__OBJECT_CTRL_STATUS(const int obj_index,
										const CString& ctrl_sts) = 0;

	virtual CII_OBJECT__ALARM* Create__OBJ_ALARM_CTRL(const CString& obj_name) = 0;

	virtual int Get__REMOTE_SEQ_ID(const CString& obj_name,const CString& var_name) = 0;

	virtual int EXTERNAL__Get_Alarm_Module_List(CUIntArray& l_seqid) = 0;

	//-------------------------------------------------------------------------
	virtual int PM_DATALOG__Start_STEP(const int module_id,const int step_id) = 0;
	virtual int PM_DATALOG__End_STEP(const int module_id,const int step_id)   = 0;
	virtual int PM_DATALOG__Abort_STEP(const int module_id,const int step_id) = 0;

	virtual int Pause__PM_DATALOG(const int module_id) = 0;
	virtual int Resume__PM_DATALOG(const int module_id) = 0;

	//-------------------------------------------------------------------------
	virtual int	EXTERNAL__Get_POSTED_ALARM_INFO(const int db_index,
							  		            int& seq_id,
												int& alarm_type,
												int& alarm_id,
												CString& time,
												CString& title,
												CString& message,
												CStringArray& l_option) = 0;

	//-------------------------------------------------------------------------
	virtual int Get__SYS_LOG_INFO(const CString& obj_name,
								  int& file_size,
								  int& file_time) = 0;
	virtual int Get__COMMON_LOG_INFO(int& file_size,
								     int& file_time) = 0;


	//-------------------------------------------------------------------------
	virtual int PM_DATALOG__Write_ALL_ITEM(const CString& path) = 0;


	//-------------------------------------------------------------------------

	virtual int PM_CSV_LOG__Set_Cycle_Limit(const int cycle_limit) = 0;

	virtual int PM_CSV_LOG__Start_Datalog(const CString& path) = 0;
	virtual int PM_CSV_LOG__Start_Datalog(const CString& path,const int module_id) = 0;

	virtual int PM_CSV_LOG__Stop_Datalog() = 0;
	virtual int PM_CSV_LOG__Stop_Datalog(const int module_id) = 0;

	virtual int PM_CSV_LOG__Write_All_Item(const CString& path) = 0;

	virtual int PM_CSV_LOG__Start_Step(const int module_id,const int step_id) = 0;
	virtual int PM_CSV_LOG__End_Step(const int module_id,const int step_id)   = 0;
	virtual int PM_CSV_LOG__Abort_Step(const int module_id,const int step_id) = 0;

	virtual int PM_CSV_LOG__Pause_Datalog(const int module_id) = 0;
	virtual int PM_CSV_LOG__Resume_Datalog(const int module_id) = 0;


	//-------------------------------------------------------------------------
	virtual int Search__OBJECT_INDEX_AND_VARIABLE_INFO(const CString& obj_name,
													   const CString& var_name,
													   int& obj_index,
													   int& var_type,
													   int& var_index,
													   int& read_flag) = 0;

	virtual int Search__OBJECT_INDEX_AND_VARIABLE_INDEX_OF_CHANNEL(const CString& ch_name,
																   int& obj_index,
																   int& var_type,
																   int& var_index) = 0;


	//-------------------------------------------------------------------------
	virtual int	EXTERNAL__Get_LAST_POSTED_ALARM_INFO(int& seq_id,
													 int& alarm_type,
													 int& alarm_id,
													 CString& time,
													 CString& title,
													 CString& message,
													 CStringArray& l_option) = 0;

	// ...
	virtual int Start__PM_DATALOG_SEC(const CString& path,const double log_sec) = 0;

	// ...
	virtual int Get__ANALOG_INFO_EX(const int obj_index,
									const int var_index,
									const int var_type,
									double& min_vaule,
									double& max_vaule,
									int& dec,
									CString& str_unit) = 0;

	//-------------------------------------------------------------------------
	virtual int  Get__Dll_Name_List_Of_SC(const int obj_type,
		                                  CStringArray& l_dll) = 0;

	virtual int  Get__Object_List_Of_DLL_Name(const CString& dll_name, 
										      CStringArray& l_obj_name) = 0;

	//
	virtual int  Set__Object_Pause_Req(const CStringArray& l_obj) = 0;
	virtual int  Set__Object_Resume_Req(const CStringArray& l_obj) = 0;
	virtual int  Set__Object_Stop_Req(const CStringArray& l_obj) = 0;

	virtual int  Get__Object_Size_Of_Dll(const CString& dll_name) = 0;

	virtual int  Get__Object_Status_List(const CStringArray& l_obj,
							             CStringArray& l_sts) = 0;

	//
	virtual int  Set__FA_Stop_Req() = 0;
	virtual int  Set__FA_Exit_Req() = 0;
	
	//
	virtual int  FreeLibrary__Dll_List(const CStringArray& l_dll) = 0;
	virtual int  LoadLibrary__Dll_List(const CStringArray& l_dll) = 0;

	//
	virtual int  Set__All_Object_Pause_Req() = 0;
	virtual int  Set__All_Object_Resume_Req() = 0;

	//
	virtual int  Set__All_Thread_Stop() = 0;

	virtual int  Set__All_Interlock_Stop() = 0;
	virtual int  Set__All_Interlock_Exit() = 0;

	//-------------------------------------------------------------------------
	virtual int  Enable__System_Log() = 0;
	virtual int  Disable__System_Log() = 0;
	
	virtual int  Set__System_Log_Backup_Day(const int backup_day) = 0;

	//-------------------------------------------------------------------------
	virtual int  Check__Idle_Of_All_Seq_Obj_Proc_State(CStringArray& l_obj_name_of_run_state,
													   CUIntArray&   l_obj_type_of_run_state) = 0;

	//
	virtual int  Set__Server_Stop_Req() = 0;


	//-------------------------------------------------------------------------
	virtual int  EXTERNAL__Get_POST_ALARM_INFO_EX(const int db_index,
										          CString& ref_toolid,
											      CString& ref_unitid,
											      int& host_report,
											      int& alarm_level) = 0;

	virtual int  Reload__ALARM_DB() = 0;

	virtual int  EXTERNAL__Get_CLEAR_ALARM_EX(CString *module,
											  CString *alarm_type,
											  CString *time,  
											  CString *alarm_id,
											  CString& ref_toolid,
											  CString& ref_unitid,
											  int& host_report,
											  int& alarm_level,
											  CString *title, 
											  CString *act_result) = 0;

	//-------------------------------------------------------------------------
	virtual int  PM_DATALOG__Backup_FILE(const CString& src_path,const CString& trg_path) = 0;
	virtual int  PM_DATALOG__Make_FILE(const CString& log_path,const CString& log_msg) = 0;

	virtual int  PM_CSV_LOG__Backup_FILE(const CString& src_path,const CString& trg_path) = 0;
	virtual int  PM_CSV_LOG__Make_FILE(const CString& log_path,const CString& log_msg) = 0;

	//-------------------------------------------------------------------------
	virtual	int  EXTERNAL__Is_SIZE_EXCEPT_MSG_BOX() = 0;

	virtual	int  EXTERNAL__Is_HEAVY_ALARM_SIZE() = 0;
	virtual	int  EXTERNAL__Is_LIGHT_ALARM_SIZE() = 0;
	virtual	int  EXTERNAL__Is_WARNING_ALARM_SIZE() = 0;

	//-------------------------------------------------------------------------
	virtual int Start__PM_MULTI_DATALOG(const CString& path,const int module_id,const CString& log_msg = "") = 0;

	//-------------------------------------------------------------------------
	virtual int Get__IO_DATA(const int obj_index,
							 const int var_type,
							 const int var_index,
							 CString& md_id,
							 CString& ch_id,
							 CString& cmmd1,
							 CString& cmmd2,
							 CString& cmmd3) = 0;

	//-------------------------------------------------------------------------
	virtual int  Reload__ALARM_LEVEL() = 0;

	//-------------------------------------------------------------------------
	virtual int Get__Posted_All_Alarm(CUIntArray& l_ext_id) = 0;
	virtual int Get__Posted_Heavy_Alarm(CUIntArray& l_ext_id) = 0;

	virtual int Get__Posted_Alarm_Level(const int ext_id, 
		                                int& eqp_id,
		                                CString& alm_level) = 0;
	virtual int Get__Posted_Alarm_Level(const int ext_id, 
									   int& eqp_id,
									   CString& obj_name,
									   int& internal_id,
									   CString& alm_level,
									   CString& alm_title) = 0;
};

class CII_AWI__OBJECT_VARIABLE_CTRL
{
public:
	virtual ~CII_AWI__OBJECT_VARIABLE_CTRL(){};

	virtual int Link__OBJECT(const CString& obj_name) = 0;

	virtual int Set__VARIABLE_DATA(const CString& var_name,const CString& var_data) = 0;
	virtual int Get__VARIABLE_DATA(const CString& var_name,CString& var_data) = 0;
	virtual int Check__VARIABLE_DATA(const CString& var_name,const CString& var_data) = 0;
	
	virtual int When__VARIABLE_DATA(const CString& var_name,const CString& var_data,const double sec = 0.0) = 0;
	virtual int When__VARIABLE_DATA(const CString& var_name,const CStringArray& l_var_data,const double sec = 0.0) = 0;

	virtual int When__LESS_THAN(const CString& var_name,const double var_data,const double sec = 0.0) = 0;
	virtual int When__MORE_THAN(const CString& var_name,const double var_data,const double sec = 0.0) = 0;

	virtual int Get__SYNC_VARIABLE_DATA(const CString& var_name,CString& var_data) = 0;
	virtual int Check__SYNC_VARIABLE_DATA(const CString& var_name,const CString& var_data) = 0;

	virtual int Get__VARIABLE_INFO(const CString& var_name,int& var_type,CString& var_data,CStringArray& l_item_info) = 0;
};

class CII_AWI__OBJECT_ALARM_CTRL
{
public:
	virtual ~CII_AWI__OBJECT_ALARM_CTRL(){};

	virtual int Link__OBJECT(const CString& obj_name) = 0;

	virtual int Popup__ALARM(const int id,CString& recovery_action) = 0;
	virtual int Post__ALARM(const int id) = 0;

	virtual int Check__ALARM(const int id,CString& recovery_action) = 0;
	virtual int Clear__ALARM(const int id) = 0;

	virtual int Is__ALARM(const int id) = 0;
	virtual int Post__ALARM_WITH_BLOCKING(const int id,CString& recovery_action) = 0;
};

//-----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------
class CI_SEQ_DB__OBJECT_INFO_CTRL
{
public:
	virtual ~CI_SEQ_DB__OBJECT_INFO_CTRL(){};

	//------------------------------------------------------
	virtual int Get__OBJECT_NAME_LIST(const int object_type,CStringArray& object_name_list) = 0;

	//------------------------------------------------------
	virtual int Link__OBJECT_NAME(const CString& object_name) = 0;

	virtual int Get__VERSION(CString& version) = 0;

	virtual int Get__VARIABLE_ALL__INFO_LIST(CStringArray& l_name,
											 CUIntArray&   l_type,
											 CStringArray& l_information) = 0;

	// VARIALBE
	virtual int Get__VARIABLE_VIRTUAL__INFO_LIST(CStringArray& l_name,
												 CUIntArray&   l_type,
												 CStringArray& l_information) = 0;

	virtual int Get__VARIABLE_VIRTUAL__INFO_LIST(CStringArray& l_name,
												 CUIntArray&   l_type,
												 CStringArray& l_information,
												 CStringArray& l_commnet) = 0;

	virtual int Get__VARIABLE_VIRTUAL__INFO_LIST(CStringArray& l_name,
												 CUIntArray&   l_type,
												 CStringArray& l_information,
												 CUIntArray&   l_x_option,
											     CStringArray& l_log) = 0;

	virtual int Get__CHANNEL__ANALOG_INFO(const CString& vriable_name,
										  CString& unit,
										  CString& min_data,
										  CString& max_data,
										  CString& dec) = 0;

	virtual int Get__CHANNEL__DIGITAL_INFO(const CString& variable_name,CStringArray& l_data) = 0;

	virtual int Change__ANALOG_INFO(const CString& var_name,
									const CString& unit,
									const CString& min_data,
									const CString& max_data,
									const CString& dec) = 0;

	// ALARM
	virtual int Get__ALARM_ID_LIST(CUIntArray& l_id) = 0;

	virtual int Get__ALARM_ID_INFO(const int id,
							       CString& title,
								   int& ext_id) = 0;

	virtual int Get__ALARM_ID_INFO(const int id,
							       CString& title,
								   CString& message,
								   CStringArray& l_option_act,
								   CStringArray& l_option_exp,
								   int& ext_id) = 0;

	// OPTION
	virtual int Get__OPTION_INFO_LIST(CStringArray& l_variable,
									  CUIntArray&   l_save_option,
									  CStringArray& l_log) = 0;
	
	virtual int Set__OPTION_INFO(const CString& variable_name,
								 const CString& save_option,
								 const CString& log_type) = 0;

	// DESCRIPTOR
	virtual int Get__DESCRIPTOR_INFO_LIST(CStringArray& l_name) = 0;

	virtual int Get__DESCRIPTOR_DATA_INFO(const CString& name,CStringArray& l_data) = 0;
	virtual int Set__DESCRIPTOR_DATA_INFO(const CString& name,const CStringArray& l_data) = 0;

	// MODULE
	virtual int Get__MODULE_INFO_LIST(CStringArray& l_read_write,
									  CStringArray& l_local_obj,
									  CStringArray& l_local_var,
									  CUIntArray&   l_seq_id,
									  CStringArray& l_remote_obj,
									  CStringArray& l_remote_var) = 0;

	// IO VARIABLE
	virtual int Get__IO_VARIABLE_INFO_LIST(CUIntArray&   l_dll,
										   CStringArray& l_rw,
										   CStringArray& l_name,
										   CStringArray& l_fnc,
										   CUIntArray&   l_type,
										   CStringArray& l_info,
										   CStringArray& l_comment) = 0;

	virtual int Get__IO_ANALOG_INFO(const CString& vriable_name,
									CString& fnc_name,
									CString& unit,
									CString& min_data,
									CString& max_data,
									CString& dec,
									double& auto_polling) = 0;

	virtual int Get__IO_DIGITAL_INFO(const CString& variable_name,
									 CString& fnc_name,
									 CStringArray& l_data,
									 double& auto_polling) = 0;

	virtual int Get__IO_STRING_INFO(const CString& variable_name,
									CString& fnc_name,
									double& auto_polling) = 0;

	// IO VARIABLE
	virtual int Get__IO_VARIABLE_INFO_LIST(CStringArray& l_rw,
										   CStringArray& l_name,
										   CUIntArray& l_type,
										   CUIntArray& l_bd_no,
										   CUIntArray& l_ch_no,
										   CStringArray& l_cmmd1,
										   CStringArray& l_cmmd2,
										   CStringArray& l_cmmd3,
										   CStringArray& l_info,
										   CStringArray& l_io_type,
										   CStringArray& l_io_info) = 0;


	virtual int Get__IO_VARIABLE__ANALOG_INFO(const CString& ch_name,
											  int& ch_read_flag,
											  int& md_no,
											  int& ch_no,
											  CString& ch_command1,
											  CString& ch_command2,
											  CString& ch_command3,
											  CString& ch_unit,
											  int& ch_dec,
											  double& ch_min,
											  double& ch_max,
											  double& auto_polling,
											  CString& comment,
											  CString& io_type,
											  CString& io_min_volt,
											  CString& io_max_volt,
											  CString& ch_lookup_table) = 0;

	virtual int Get__IO_VARIABLE__DIGITAL_INFO(const CString& ch_name,
											   int& ch_read_flag,
											   int& md_no,
											   int& ch_no,
											   CString& ch_command1,
											   CString& ch_command2,
											   CString& ch_command3,
											   CStringArray& l_data,
											   double& auto_polling) = 0;

	virtual int Get__IO_VARIABLE__STRING_INFO(const CString& ch_name,
											  int& ch_read_flag,
											  int& md_no,
											  int& ch_no,
											  CString& ch_command1,
											  CString& ch_command2,
											  CString& ch_command3,
											  double& auto_polling) = 0;

	virtual int Search__IO_VARIABLE(const CString& ch_name) = 0;


	//------------------------------------------------------------------------------
	virtual int Get__IO_OPTION_INFO_LIST(CUIntArray&   l_dll,
										 CStringArray& l_variable,
										 CUIntArray&   l_x_option,
										 CStringArray& l_log) = 0;

	virtual int Set__IO_OPTION_INFO(const CString& variable_name,
								    const int x_option,
								    const CString& log_type) = 0;

	//------------------------------------------------------------------------------
	virtual int Save__OBJECT_INFO(const int obj_type,const CString& object_name) = 0;


	//------------------------------------------------------------------------------
	virtual int Get__INCLUDE_FILE(CString& file_name) = 0;
	virtual int Set__INCLUDE_FILE(const CString& file_name) = 0;


	//------------------------------------------------------------------------------
	virtual int Get__ALL_OBJECT__VERSION_INFO(CStringArray& l_obj_name,
									          CStringArray& l_obj_type,
									          CStringArray& l_version) = 0;
};	

//------------------------------------------------------
class CI_SEQ_DB__OBJECT_CTRL
{
public:
	virtual ~CI_SEQ_DB__OBJECT_CTRL(){};

	//------------------------------------------------------
	virtual int Link__OBJECT(const CString& object_name) = 0;

	//
	virtual int Get__CTRL_STATUS(CString& status) = 0;
	virtual int Get__MODE_STATUS(CString& mode) = 0;

	virtual int Get__MODE_LIST(CStringArray& l_mode) = 0;

	virtual int Set__MODE_STATUS(const CString& mode) = 0;

	virtual int Run__CTRL() = 0;
	virtual int Abort__CTRL() = 0;

	//
	virtual int Get__QUERY_LIST(CStringArray& l_query) = 0;
	virtual int Call__QUERY_NAME(const CString& q_name, CString& q_data) = 0;
	virtual int Call__QUERY_LIST(const CString& q_name, CStringArray& l_data) = 0;
	virtual int Call__QUERY_NAME(const CString& q_name,const CStringArray& l_sub_query, CString& q_data) = 0;
	virtual int Call__QUERY_LIST(const CString& q_name,const CStringArray& l_sub_query, CStringArray& l_data) = 0;
};

//------------------------------------------------------
class CI_SEQ_DB__CHANNEL_CTRL
{
public:
	virtual ~CI_SEQ_DB__CHANNEL_CTRL(){};

	//------------------------------------------------------
	virtual int Link__CHANNEL(const CString& object_name,
							  const CString& variable_name) = 0;

	virtual int Get__ANALOG_INFO(CString& min,
								 CString& max) = 0;
	virtual int Get__DIGITAL_INFO(CStringArray& l_data) = 0;

	virtual int Get__DATA(CString& data) = 0;
	virtual int Set__DATA(const CString& data) = 0;

	//------------------------------------------------------
	virtual int ASYNC__Set_DATA(const CString& data) = 0;
};

//------------------------------------------------------
class CI_SEQ_DB__OBJECT_EDITOR_CTRL
{
public:
	virtual ~CI_SEQ_DB__OBJECT_EDITOR_CTRL(){};

	//------------------------------------------------------
	virtual int Upload__DLL_LIST(const int object_type,
								 CStringArray& l_dll_name) = 0;

	virtual int Upload__CLASS_LIST(const int object_type,
								   const CString& dll_name,
								   CStringArray& l_class_name) = 0;

	virtual int Upload__OBJECT_LIST(const int object_type,
									CStringArray& l_object_name,
									CStringArray& l_dll_name,
									CStringArray& l_class_name) = 0;


	//------------------------------------------------------
	virtual int Get__INTERLOCK_OBJ_LIST(CStringArray& l_dll,
									    CStringArray& l_obj) = 0;

	virtual int Get__INTERLOCK_DLL_LIST(CStringArray& l_dll,
									    CStringArray& l_obj) = 0;

	virtual int Save__INTERLOCK_LIST(const CStringArray& l_dll,
									 const CStringArray& l_obj) = 0;


	//------------------------------------------------------
	virtual int Get__DLL_INFO(const int object_type, 
							  const CString& dll_name,
							  CString& dll_info) = 0;


	virtual int Create__OBJECT(const int object_type,
							   const CString& object_name,
							   const CString& dll_name,
							   const CString& class_name) = 0;

	virtual int Delete__OBJECT(const CString& object_name) = 0;

	virtual int Copy__OBJECT(const CString& src_obj,
							 const CString& trg_obj) = 0;

	virtual int Rename__OBJECT(const CString& old_obj,
							   const CString& new_obj) = 0;

	virtual int Save__OBJECT() = 0;

	virtual int Undo__OBJECT() = 0;

	//------------------------------------------------------
	virtual int Upload__SEQ_INFO() = 0;

	virtual int Get__SEQ_INFO(CUIntArray& l_seq_id,
							  CStringArray& l_seq_ip,
							  CUIntArray& l_seq_port) = 0;


	//------------------------------------------------------
	virtual int Upload__FA_INFO() = 0;

	virtual int Get__FA_INFO(CStringArray& l_service_name,
							 CStringArray& l_include_file) = 0;

};
//-----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------
#define  SYSTEM_CONFIG__SEQ_MODE__RUN				1
#define  SYSTEM_CONFIG__SEQ_MODE__EDITOR			2
#define  SYSTEM_CONFIG__SEQ_MODE__SIMULATION		3

#define  SYSTEM_CONFIG__LANGUAGE__KOREAN			1
#define  SYSTEM_CONFIG__LANGUAGE__ENGLISH			2


class CI_SEQ_DB__SYSTEM_CONFIG_CTRL
{
public:
	virtual ~CI_SEQ_DB__SYSTEM_CONFIG_CTRL(){};

	//------------------------------------------------------
	virtual int Get__SYSTEM_INFO(CString& sys_info) = 0;

	virtual int Set__SEQ_MODE(const int seq_mode) = 0;
	virtual int Get__SEQ_MODE() = 0;

	virtual int Set__LANGUAGE_TYPE(const int language_type) = 0;
	virtual int Get__LANGUAGE_TYPE() = 0;

	virtual int Set__SEQ_ID(const int seq_id) = 0;
	virtual int Get__SEQ_ID() = 0;

	virtual int Save_CONFIG() = 0;

	//------------------------------------------------------
	virtual int Get__SEQ_MODE_To_EDITOR() = 0;

	//------------------------------------------------------
	virtual int Set__WINDOW_SHOW() = 0;
	virtual int Set__WINDOW_HIDE() = 0;
	virtual int Is__WINDOW_SHOW()  = 0;
	virtual int Is__WINDOW_HIDE()  = 0;
	
	virtual int Is__RTC_HIGH() = 0;
	virtual int Is__RTC_LOW()  = 0;

	//------------------------------------------------------
	virtual void Get__CFG_PAGE_LIST(CStringArray& l_page) = 0;
	virtual int  Check__CFG_PAGE_LIST(const CString& cfg_page) = 0;
};
//------------------------------------------------------

//------------------------------------------------------

class CI_SEQ_DB__SYSTEM_DIR_INFO
{
public:
	virtual ~CI_SEQ_DB__SYSTEM_DIR_INFO(){};

	//------------------------------------------------------
	virtual int Get__DIR_ROOT(CString& dir_root)         = 0;
	virtual int Get__DIR_USER_LOG(CString& dir)          = 0;
	virtual int Get__DIR_USER_LOG__OBJECT(CString& dir)  = 0;
	virtual int Get__DIR_USER_LOG__DATALOG(CString& dir) = 0;
	virtual int Get__DIR_INCLUDE_FILE(CString& dir_include_file) = 0;
	virtual int Get__DIR_SCR_UI(CString& dir_scr_ui)     = 0;

	virtual int Get__DIR_CONFIG(CString& dir)  = 0;
	virtual int Get__DIR_PROCESS(CString& dir) = 0;

	//------------------------------------------------------
	virtual int Get__SEQ_INFO(CString& device_name,int& seq_id) = 0;

	//------------------------------------------------------
	virtual int Is__SIMULATION_MODE() = 0;
	virtual int Is__RUN_MODE() = 0;

	//------------------------------------------------------
	virtual int Get__DIR_EXT_DATALOG(CString& dir_log) = 0;

};
//------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------


class CI_SEQ_DB__DATALOG_VIEW_CTRL
{
public:
	virtual ~CI_SEQ_DB__DATALOG_VIEW_CTRL(){};

	//------------------------------------------------------
	virtual int Get__OBJECT_LOG_LIST(CStringArray& l_log_object,
									 CStringArray& l_log_name) = 0;

	virtual int Get__LOG_INFO(const CString& log_object,
							  const CString& log_name,
							  CString& log_info) = 0;
};
//------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------


class CI_SEQ_DB__MATERIAL_VIEW_CTRL
{
public:
	virtual ~CI_SEQ_DB__MATERIAL_VIEW_CTRL(){};

	//------------------------------------------------------
	virtual int Get__OBJECT_LOG_LIST(CStringArray& l_log_object,
									 CStringArray& l_log_name) = 0;

	virtual int Get__LOG_INFO(const CString& log_object,
							  const CString& log_name,
							  CString& log_info) = 0;
};
//------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------
#define  RECIPE_ITEM__TYPE__UNKNOWN			0
#define  RECIPE_ITEM__TYPE__ANALOG			1
#define  RECIPE_ITEM__TYPE__DIGITAL			2
#define  RECIPE_ITEM__TYPE__STRING			3
#define  RECIPE_ITEM__TYPE__FILE			4


class CI_SEQ_DB__RECIPE_ITEM_CTRL
{
public:
	virtual ~CI_SEQ_DB__RECIPE_ITEM_CTRL(){};

	//------------------------------------------------------
	virtual int Link__OBJECT_NAME(const CString& object_name) = 0;
	virtual int Get__FILE_LIST(CStringArray& l_rcp_file) = 0;

	virtual int Get__CONFIG_ITEM(CStringArray& l_item_name,
							     CUIntArray&   l_item_type) = 0;
	virtual int Get__STEP_ITEM(CStringArray& l_item_name,
							   CUIntArray&   l_item_type) = 0;

	virtual int Get__ITEM_TYPE(const CString& item_name,
							   int& item_type) = 0;

	virtual int Get__ITEM_ANALOG_INFO(const CString& item_name,
									  CString& str_min,
									  CString& str_max) = 0;
	virtual int Get__ITEM_DIGITAL_INFO(const CString& item_name,
									   CStringArray& l_data) = 0;
	virtual int Get__ITEM_FILE_INFO(const CString& item_name,
									CStringArray& l_rcp_file) = 0;

	virtual int Get__ITEM_OPTION_INFO(const CString& item_name,
									  int& x_option,
									  CString& log_type,
									  int& internal_svid,
									  int& external_svid) = 0;
};

class CI_SEQ_DB__CONFIG_ITEM_CTRL
{
public:
	virtual ~CI_SEQ_DB__CONFIG_ITEM_CTRL(){};

	//------------------------------------------------------
	virtual int Open__OBJECT(const CString& object_name) = 0;

	virtual int Get__ITEM_LIST(CStringArray& l_item) = 0;
	virtual int Get__ITEM_TYPE(const int& item_index,int& item_type) = 0;

	virtual int Get__ITEM_ANALOG_INFO(CString& str_min,CString& str_max) = 0;
	virtual int Get__ITEM_DIGITAL_INFO(CStringArray& l_data) = 0;
};
//------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------
#define  IO_TYPE__IO					1

//------------------------------------------------------
#define  DRIVER_PARA__ANALOG			1
#define  DRIVER_PARA__DIGITAL			2
#define  DRIVER_PARA__STRING			3


class CDS__DRIVER_PARA_ANALOG
{
public:
	CString sNAME;
	double  dDATA;
	CString sCOMMENT;

	double dMIN;
	double dMAX;
};
class CDS__DRIVER_PARA_DIGITAL
{
public:
	CString sNAME;
	CString sDATA;
	CString sCOMMENT;

	CStringArray sLIST_ITEM;
};
class CDS__DRIVER_PARA_STRING
{
public:
	CString sNAME;
	CString sDATA;
	CString sCOMMENT;
};


//-----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------
class CDS_Object__Variable_Info
{
public:
	CString sVARIABLE_NAME;

	int iVARIABLE_TYPE;
	int iVARIABLE_INDEX;
};
class CDS_Object__Alarm_Info
{
public:
	CString sALARM_NAME;

	int iALARM_INDEX;
};
class CDS_Object__Def_Constant_Info
{
public:
	CString sDEF_CONST_NAME;
	CString sDEF_CONST_DATA;
};
class CDS_Object__IO_Parameter_Info
{
public:
	CString sPARA_NAME;
	CString sPARA_DATA;
};
class CDS_Object__Link_Parameter_Info
{
public:
	CString sPARA_NAME;
	CString sPARA_DATA;
};
class CDS_Object__Interlock_Info
{
public:
	CStringArray sList__CH_NAME;
	CStringArray sList__CH_DATA;
	CStringArray sList__CMP_PARA;
};
class CDS_Object__FA_Parameter_Info
{
public:
	CString sPARA_NAME;
	CString sPARA_DATA;
};


class CDS_Object_Label
{
public:
	CDS_Object_Label()
	{
	}
	~CDS_Object_Label()
	{
		int limit;
		int i;

		// VARIABLE
		{
			CDS_Object__Variable_Info *p_variable;

			limit = pLIST__VARIABLE_INFO.GetSize();

			for(i=0;i<limit;i++)
			{
				p_variable = (CDS_Object__Variable_Info*) pLIST__VARIABLE_INFO[i];
				delete p_variable;
			}
			pLIST__VARIABLE_INFO.RemoveAll();
		}
		// ALARM
		{
			CDS_Object__Alarm_Info *p_alarm;

			limit = pLIST__ALARM_INFO.GetSize();

			for(i=0;i<limit;i++)
			{
				p_alarm = (CDS_Object__Alarm_Info*) pLIST__ALARM_INFO[i];
				delete p_alarm;
			}
			pLIST__ALARM_INFO.RemoveAll();
		}
		
		// DEF_CONSTANT
		{
			CDS_Object__Def_Constant_Info *p_para;

			limit = pLIST__DEF_CONSTANT_INFO.GetSize();

			for(i=0;i<limit;i++)
			{
				p_para = (CDS_Object__Def_Constant_Info*) pLIST__DEF_CONSTANT_INFO[i];
				delete p_para;
			}
			pLIST__DEF_CONSTANT_INFO.RemoveAll();
		}
		// IO_PARAMETER
		{
			CDS_Object__IO_Parameter_Info *p_para;

			limit = pLIST__IO_PARAMETER_INFO.GetSize();

			for(i=0;i<limit;i++)
			{
				p_para = (CDS_Object__IO_Parameter_Info*) pLIST__IO_PARAMETER_INFO[i];
				delete p_para;
			}
			pLIST__IO_PARAMETER_INFO.RemoveAll();
		}
		// LINK_PARAMETER
		{
			CDS_Object__Link_Parameter_Info *p_para;

			limit = pLIST__LINK_PARAMETER_INFO.GetSize();

			for(i=0;i<limit;i++)
			{
				p_para = (CDS_Object__Link_Parameter_Info*) pLIST__LINK_PARAMETER_INFO[i];
				delete p_para;
			}
			pLIST__LINK_PARAMETER_INFO.RemoveAll();
		}
		// FA_PARAMETER
		{
			CDS_Object__FA_Parameter_Info *p_para;

			limit = pLIST__FA_PARAMETER_INFO.GetSize();

			for(i=0;i<limit;i++)
			{
				p_para = (CDS_Object__FA_Parameter_Info*) pLIST__FA_PARAMETER_INFO[i];
				delete p_para;
			}
			pLIST__FA_PARAMETER_INFO.RemoveAll();
		}
	}

	// ...
	CString sOBJECT_NAME;

	CPtrArray pLIST__VARIABLE_INFO;
	CPtrArray pLIST__ALARM_INFO;
	CPtrArray pLIST__DEF_CONSTANT_INFO;
	CPtrArray pLIST__IO_PARAMETER_INFO;
	CPtrArray pLIST__LINK_PARAMETER_INFO;
	CPtrArray pLIST__FA_PARAMETER_INFO;

	CDS_Object__Interlock_Info mIO_INTERLOCK_INFO;
	CDS_Object__Interlock_Info mUI_INTERLOCK_INFO;

	CString sIO_FILE_NAME;
	CString sLINK_FILE_NAME;
	CString sFA_FILE_NAME;
	CString sFA_SERVICE_NAME;

	int iOBJECT_TYPE;
	int iOBJECT_INDEX;
};


class CDS_Channel_Label
{
public:
	void Copy_From(const CDS_Channel_Label* p_info)
	{
		sOBJECT_NAME   = p_info->sOBJECT_NAME;
		sVARIABLE_NAME = p_info->sVARIABLE_NAME;

		iOBJECT_INDEX   = p_info->iOBJECT_INDEX;
		iVARIABLE_TYPE  = p_info->iVARIABLE_TYPE;
		iVARIABLE_INDEX = p_info->iVARIABLE_INDEX;
	}

	//---------------------------------------------------------------------------
	CString sOBJECT_NAME;
	CString sVARIABLE_NAME;

	int	iVARIABLE_TYPE;		
	int	iOBJECT_INDEX;
	int iVARIABLE_INDEX;
};

class CDS_Polling_Channel
{
public:
	void *	pADDR;
	int		iTYPE;
	int		iINDEX;
	
	CDS_Channel_Label cCHANNEL;
};

class CDS_Channel_Property
{
public:
	CString sOBJECT_NAME;
	CString sVARIABLE_NAME;	

	CString sWIN;			// 윈도우 옵션
	CString sIn_TYPE;		// ANALOG...
	int     iIn_BD;
	int     iIn_CH;
	CString sOut_TYPE;		// DIGITAL...
	int     iOut_BD;
	int     iOut_CH;
	double  dMIN;			// ANALOG RANGE
	double  dMAX;			//
	double  dAtoD_MIN;		// ANALOG VALUE
	double  dAtoD_MAX;
	double  dDtoA_MIN;
	double  dDtoA_MAX;
	CString sDATA;			// Current Channel Value
};
//------------------------------------------------------

//------------------------------------------------------
#define  DEVICE_TYPE__IO				1
#define  DEVICE_TYPE__INTERFACE			2
#define  DEVICE_TYPE__DEVICE_NET		3

class CDS_DEVICE_PORT_INFO
{
public:
	int     iType;
	int		iIndex;
	CString sData;
};
//------------------------------------------------------

//------------------------------------------------------
#define  MAIN_TYPE__IO_LIST					1
#define  MAIN_TYPE__IO_INPUT				2
#define  MAIN_TYPE__IO_OUTPUT				3

#define  MAIN_TYPE__INTERFACE_LIST			21
#define  MAIN_TYPE__INTERFACE_INPUT			22
#define  MAIN_TYPE__INTERFACE_OUTPUT		23

#define  MAIN_TYPE__INFORMATION				31
#define  MAIN_TYPE__SYSTEM_INFORMATION		32			// 추가  :  2005.06.30

class CDS_SYSTEM_INFORMATION							// 추가  :  2005.06.30
{
public:
	CString sSEQ_NAME;
	CString sKEY_TYPE;
	CString sIP;
	int		iPORT;
	CString sSEQ_MODE;
};
//------------------------------------------------------

//------------------------------------------------------
class CI_SEQ_DB__CTRL
{
public:
	virtual ~CI_SEQ_DB__CTRL(){};

	//---------------------------------------------
	virtual int Start(HWND hwnd,const CString& root_dir,const int editor_mode,const int mutex_check) = 0;
	//---------------------------------------------

	//---------------------------------------------
	virtual int Get_Object_List__Label(const int object_type,
									   CPtrArray& p_array) = 0;

	virtual int Get__Variable_Info(const int obj_index,
								   const int var_index,
								   const int var_type,
								   CString&  var_data) = 0;

	virtual int Get_Analog_Channel_Label(CPtrArray& p_array)  = 0;
	virtual int Get_Digital_Channel_Label(CPtrArray& p_array) = 0;
	virtual int Get_String_Channel_Label(CPtrArray& p_array)  = 0;

	virtual int Get_Channel_Label(const int main_type,
								  const int sub_type,
								  const CDS_DEVICE_PORT_INFO& device_info,
								  CPtrArray& p_array) = 0;
	
	virtual int Get_Descript_List(const CDS_Channel_Label& ch_label,
								  CStringArray& list) = 0;

	virtual int Get_Channel_OutData(const CDS_Channel_Label& ch_label,
									CString& data) = 0;

	virtual int Set_Channel_OutData(const CDS_Channel_Label& ch_label,
									const CString& data) = 0;

	virtual int Get_Channel_Property(const CDS_Channel_Label& ch_label,
									 CDS_Channel_Property& ch_property) = 0;
	//---------------------------------------------

	//---------------------------------------------
	virtual int Get_Object_Debug_All_Info(const int object_index,
										  CStringArray& l_log_info) = 0;
	virtual int Get_Object_Debug_New_Info(const int object_index,
										  CStringArray& l_log_info) = 0;
	//---------------------------------------------

	//---------------------------------------------
	virtual int Alarm_Clear(const CDS_Alarm__MSG_INFO& msg_info) = 0;
	//---------------------------------------------

	//---------------------------------------------
	virtual int Close()	= 0;
	//---------------------------------------------

	//------------------------------------------------------
	virtual int Get__OBJECT_LIST(CStringArray& l_obj_name,
								 CUIntArray&   l_obj_type,
								 CStringArray& l_dll_name,
								 CStringArray& l_cls_name) = 0;

 	virtual int Get__OBJECT_VERSION(CStringArray& l_obj_name,
									CStringArray& l_obj_type,
									CStringArray& l_version) = 0;

	// ...
	virtual int Get__CORE_VERSION(CString& core_ver) = 0;

	// ...
	virtual int Change__Worker_File(const CString& file_name) = 0;
	virtual int Change__MetaData_File(const CString& file_name) = 0;
	virtual int Change__System_File(const CString& file_name) = 0;

	//
	virtual int Set__Debug_Property(const bool active_debug, const CStringArray& l_para) = 0;
};
//------------------------------------------------------

//------------------------------------------------------
#define SEQ_QUERY__HW_KEY_TYPE_CHECK		"HW.KEY.TYPE.CHECK"
#define SEQ_QUERY__SYS_ERROR				"SYS.ERROR"
#define SEQ_QUERY__ALARM_POST_SIZE			"ALARM.POST.SIZE"
#define SEQ_QUERY__FA_SERVER_UNIT_SIZE      "FA_SERVER.UNIT.SIZE"


class CI_SEQ_CORE__QUERY_CTRL
{
public:
	virtual ~CI_SEQ_CORE__QUERY_CTRL(){};

	//---------------------------------------------
	virtual double Get__VERSION() = 0;

	//.....
	virtual int Get__QUERY(const CString& in_query,
						   CString& out_answer) = 0;

	virtual int Get__QUERY_LIST(const CString& in_query,
							    CStringArray& l_out_answer) = 0;

	//.....
	virtual int Get__MULTI_QUERY(const CString& main_query,
								 const CString& sub_query,
								 CString& out_answer) = 0;

	virtual int Get__MULTI_QUERY_LIST(const CString& main_query,
									  const CString& sub_query,
								      CStringArray& l_out_answer) = 0;

	// ...
	virtual int Load__ERROR_INFO(const CString& err_title,
								 const CString& err_msg) = 0;
};
//------------------------------------------------------

//------------------------------------------------------
class CII_EQP_CORE__SYSTEM_CTRL
{
public:
	virtual ~CII_EQP_CORE__SYSTEM_CTRL(){};

	//------------------------------------------------------
	virtual int Get__OBJECT_LIST(CStringArray& l__obj_name) = 0;
	virtual int Get__OBJECT_LIST(CStringArray& l__obj_name, CStringArray& l__obj_sts) = 0;

	virtual int Get__OBJECT_COUNT_IN_RUN_STATE()  = 0;
	virtual int Get__OBJECT_LIST_IN_RUN_STATE(CStringArray& l__obj_name)  = 0;

	virtual int Abort__OBJECT_IN_RUN_STATE(const bool active_all, const CString& obj_name, CStringArray& l__abort_obj)  = 0;
};
//------------------------------------------------------
