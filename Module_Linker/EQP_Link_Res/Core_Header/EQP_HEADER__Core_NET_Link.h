#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Core_Header\EQP_UI_HEADER.h"


#define  ALARM_TYPE__UNKNOWN							  0
#define  ALARM_TYPE__ALARM_BOX							1
#define  ALARM_TYPE__ALARM_POST							2
#define  ALARM_TYPE__MESSAGE_BOX						3
#define  ALARM_TYPE__WARNING_POST						4


//-----------------------------------------------------------------------
class CI_SEQ_DB__INet_CTRL
{
public:
	virtual ~CI_SEQ_DB__INet_CTRL(){};

	//-----------------------------------------------------------------------
	virtual int Get__SEQ_VERSION(CStringArray& l_obj_name,
								 CStringArray& l_obj_type,
								 CStringArray& l_obj_version) = 0;
									   
	virtual int Get__SEQ_LIST(CUIntArray& l_seq) = 0;

	virtual int Get__INTERNAL_IP_And_PORT(int& seq_id,
										  CString& ip,
										  int& port) = 0;

	virtual int Get__SEQ_IP_And_PORT(const int seq_id,
									 CString& ip,
									 int& port) = 0;

	//-----------------------------------------------------------------------
	virtual int Get__CHANNEL_INDEX(const CString& obj_name,
								   const CString& var_name,
								   int& obj_index,
								   int& var_index,
								   int& var_type) = 0;

	virtual int Get__DATA(const int obj_index,
						  const int var_index,
						  const int var_type,
						  const CString& var_data,
						  CString& cur_data) = 0;


	virtual int Set__DATA_LOCK() = 0;
	virtual int Set__DATA_UNLOCK() = 0;

	virtual int Get__DATA_CLICK(const int mem_flag,
								const int obj_index,
								const int var_index,
								const int var_type,
								const CString& var_data,
								const int click_count,
								CString& cur_data,
								int& cur_click_count) = 0;


	virtual int Set__INIT_DATA(const int obj_index,
							   const int var_index,
							   const int var_type) = 0;

	virtual int Set__DATA(const CString& obj_name,
						  const CString& var_name,
						  const int obj_index,
						  const int var_index,
						  const int var_type,
						  const CString& data) = 0;

	virtual int Set__DATA_WITHOUT_INTERLOCK(const int obj_index,
											const int var_index,
											const int var_type,
											const CString& data) = 0;

	virtual int Get__INFO(const int obj_index,
						  const int var_index,
						  const int var_type,
						  CString& var_data,
						  CStringArray& l_item_info) = 0;

	
	//-----------------------------------------------------------------------
	// 
	virtual int Get__DIR_ROOT(CString& dir_root)		= 0;
	virtual int Get__DIR_CONFIG(CString& dir_config)    = 0;
	virtual int Get__DIR_PROCESS(CString& dir_process)  = 0;
	virtual int Get__DIR_USER_LOG__DATALOG(CString& dir_datalog) = 0;


	//-----------------------------------------------------------------------
	// USER ID
	virtual int Get__USERID_INFO(CStringArray& l_id,
								 CStringArray& l_level,
								 CStringArray& l_password) = 0;

	virtual int Add__USERID_INFO(const CString& user_id,
								 const CString& user_level,
								 const CString& password) = 0;

	virtual int Delete__USERID_INFO(const CString& user_id) = 0;


	// ALARM
	virtual int Alarm__Get_INFO_LIST(int& db_index,
									 int& sys_id,
									 int& alarm_id,
									 int& alarm_type, 
									 CString& time,   
									 CString& title,
									 CString& message,
									 CStringArray& l_option_act,
									 CStringArray& l_option_exp) = 0;

	virtual int Alarm__Clear_ALL_ALARM_In_SEQ_ID(const int seq_id) = 0;

	virtual int Alarm__Clear_INFO(const int sys_id,
								  const int alarm_id,
								  const CString& act_result,
								  const CString& clear_time,
								  const int gui_id) = 0;

	virtual int AlarmPost__Report_To_CTC(const int seq_id,
										 const int sys_id,
										 const int alarm_id,
										 const int alarm_type, 
										 const CString& time,
										 const CString& title,
										 const CString& message,
										 const CStringArray& l_option_act,
										 const CStringArray& l_option_exp) = 0;
	
	virtual int AlarmClear__Report_To_CTC(const int seq_id,
										  const int sys_id,
										  const int alarm_id,
										  const CString& act_result,
										  const CString& clear_time) = 0;


	// CONFIG
	virtual int Get__EVENT_LIST(CStringArray& channel_list,
							    CStringArray& win_list) = 0;

	virtual int Get__INTERVAL_LIST(CStringArray& channel_list,
								   CStringArray& win_list) = 0;
	
	virtual int Is__CHANNEL_REAL_TYPE(const int& ch_prefix,
									  const int& ch_type,
									  const int& ch_index,
									  int& io_flag) = 0;

	/*
	io_type     :: RS232, INTERFACE, BOARD, DEVICE_NET
	in_out_type :: 1 = INPUT, 2 = OUTPUT
	para_list   :: BOARD or DEVICE_NET : bd_no
				   INTERFACE or RS232  : min_id, max_id
	*/
	virtual int Get__IO_INFO(const CString& io_type,
							 const int& in_out_type,
							 const CStringArray& para_list,
							 CStringArray& bd_no_list,
							 CStringArray& ch_no_list,
							 CStringArray& ch_name_list) = 0;


	//-----------------------------------------------------------------------
	virtual int Set__MIN(const int obj_index,
						 const int var_index,
						 const int var_type,
						 const CString& data) = 0;

	virtual int Set__MAX(const int obj_index,
						 const int var_index,
						 const int var_type,
						 const CString& data) = 0;

	virtual int Set__DEC(const int obj_index,
						 const int var_index,
						 const int var_type,
						 const CString& data) = 0;

	//-----------------------------------------------------------------------
	virtual int Get__SEQ_SVID_MAP__INFO(const int svid,
										CString& obj_name,
										CString& var_name,
										int& obj_index,
										int& var_index,
										int& var_type) = 0;

	//-----------------------------------------------------------------------
	virtual int Get__CHANNEL_INDEX_EX(const CString& obj_name,
									  const CString& var_name,
									  int& obj_index,
									  int& var_index,
									  int& var_type,
									  int& ch_read_flag) = 0;

	//-----------------------------------------------------------------------
	virtual int Get__CUR_DATA(const int mem_flag,
							  const int obj_index,
							  const int var_index,
							  const int var_type,
							  CString& cur_data,
							  int& cur_click_count) = 0;

	//-----------------------------------------------------------------------
	virtual int Get__SEQ_VER_INFO(const int ver_type,
								  CString& ver_info,
								  CStringArray& l_file_name,
						 		  CStringArray& l_file_ver,
								  CStringArray& l_file_date) = 0;	

	//-----------------------------------------------------------------------
	virtual int Get__Channel_X_Option_History(const CString& ch_name,
		                                      CStringArray& l_time_data) = 0;

	//-----------------------------------------------------------------------
	virtual int Alarm__Get_INFO_LIST_EX(int& db_index,
										int& sys_id,
										int& alarm_id,
										int& alarm_type, 
										int& host_report,
										int& alarm_level,
										CString& ref_toolid,
										CString& ref_unitid,
										CString& time,   
										CString& title,
										CString& message,
										CStringArray& l_option_act,
										CStringArray& l_option_exp) = 0;

	virtual int Alarm__Clear_INFO_EX(const int sys_id,
									 const int alarm_id,
									 const int host_report,
									 const int alarm_level,
									 const CString& ref_toolid,
									 const CString& ref_unitid,
									 const CString& act_result,
									 const CString& clear_time,
									 const int gui_id) = 0;

	virtual int AlarmPost__Report_To_CTC_EX(const int seq_id,
										    const int sys_id,
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
	
	virtual int AlarmClear__Report_To_CTC_EX(const int seq_id,
										     const int sys_id,
										     const int alarm_id,
											 const int host_report,
											 const int alarm_level,
											 const CString& ref_toolid,
											 const CString& ref_unitid,
										     const CString& act_result,
										     const CString& clear_time) = 0;

	// ...
	virtual int Is__RTC_HIGH() = 0;
	virtual int Is__RTC_LOW() = 0;

	// ...
	virtual CString Get__MODULE_LINK_SERVER_REPORT_SPEED() = 0;

};
//-----------------------------------------------------------------------
