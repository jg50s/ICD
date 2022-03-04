#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\GUI_DS.h"
#include "C:\Module_Linker\SUI_Link_Res\Core_Header\COMMON_DEFINE__NETWORK.h"


//----------------------------------------------------
#define  NET_STATUS__OFFLINE			0
#define  NET_STATUS__ONLINE				1
#define  NET_STATUS__STARTUP			2
#define  NET_STATUS__INITING			3
#define  NET_STATUS__INITED				4


//----------------------------------------------------
class CI_GUI__NET_CTRL
{
public:
	virtual ~CI_GUI__NET_CTRL(){};

	//-----------------------------------------
 	virtual int System_Init_Ex(const int gui_id,
							   const CString& dir_root,
							   const CUIntArray& seq_id,
							   const CStringArray& device_list) = 0;		

	virtual int System_Start(const int gui_id) = 0;

	virtual int Is_Changed() = 0;

	virtual int Get_Info(CStringArray& device_list,
						 CUIntArray&   id_list,
						 CStringArray& ip_list,
						 CUIntArray&   port_list) = 0;

	virtual int  Set_System_Status(const int seq_id,const int status) = 0;
	virtual void Get_System_Status(const int seq_id,int& status) = 0;


	virtual int Is_Active(const int seq_id,
						  CString& error_msg) = 0;

	virtual int Get_Channel_Data(const int seq_id,
								 const CString& channel_name,
								 int& ack,
								 int& channel_type,
								 CString& data,
								 CString& unit,
								 CStringArray& info_list) = 0;

	virtual int Get_Channel_ID(const int seq_id,
							   const CStringArray& rcp_channel_name_list,
							   CUIntArray& rcp_channel_id_list) = 0;

	virtual int Set_Channel_Data(const int seq_id,
								 const CString& set_type,
								 const CStringArray& name_list,
								 const CStringArray& data_list) = 0;

	virtual int Report_Channel_Info(const int seq_id) = 0;
	
	virtual int Report_Alarm_List(const int seq_id) = 0;

	virtual int Set_Screen_Page_Info(const int seq_id,
									 const CString& screen_name,
									 const CStringArray& seq_channel_list) = 0;

	virtual int Set_Screen_Ctrl_Channel_List(const int seq_id,
											 const CStringArray& channel_list) = 0;

	virtual int Change_Screen_Status(const int seq_id,
									 const CString& screen_name,
									 const int status) = 0;

	virtual int Clear_Alarm_Info(const int seq_id,
								 const int sys_id,
								 const int alarm_id,
								 const CString& act_result) = 0;

	virtual int Get_ERROR__NEW_MSG(CString& error_msg) = 0;

	virtual int Read_Config_File(const int seq_id,
								 const CString& file_name,
								 int& file_status,
								 CString& file_msg) = 0;

	virtual int Write_Config_File(const int seq_id,
								  const CString& file_name,
								  const CString& file_msg,
								  int& file_status) = 0;

	virtual int Get__INFO_LIST(const int& seq_id,
							   CStringArray& level_list,
							   CStringArray& userid_list,
							   CStringArray& password_list) = 0;

	virtual int Add__INFO(const int& seq_id,
						  const CString& level,
						  const CString& userid,
						  const CString& password) = 0;

	virtual int Delete__INFO(const int& seq_id,
							 const CString& userid) = 0;

	virtual int Check__INFO(const int& seq_id,
							const CString& userid,
							const CString& password) = 0;

	virtual int PM__Get_FILE_LIST(const int& seq_id,
								  const CString& sub_dir,
								  const CString& file_ext,
								  CStringArray& file_list) = 0;

	virtual int PM__Get_FILE_LIST(const int& seq_id,
								  const CString& sub_dir,
								  const CString& file_ext,
								  CStringArray& file_list,
								  CStringArray& date_list) = 0;

	virtual int PM__Delete_FILE(const int& seq_id,
								const CString& sub_dir,
								const CString& file_ext,
								const CString& file_name) = 0;

	virtual int PM__Copy_FILE(const int& seq_id,
							  const CString& sub_dir,
							  const CString& file_ext,
							  const CString& src_file,
							  const CString& trg_file) = 0;

	virtual int PM__Rename_FILE(const int& seq_id,
							    const CString& sub_dir,
							    const CString& file_ext,
								const CString& src_file,
								const CString& trg_file) = 0;

	virtual int PM__Download_FILE(const int& seq_id,
								  const CString& sub_dir,
								  const CString& file_ext,
								  const CString& file_name,
								  const CString& file_data) = 0;

	virtual int PM__Upload_FILE(const int& seq_id,
								const CString& sub_dir,
								const CString& file_ext,
								const CString& file_name,
								CString& file_data) = 0;

	virtual int  DATALOG__Get_DIR_LIST(const int& seq_id,
									   const CString& sub_dir,
									   CStringArray& dir_list) = 0;

	virtual int  DATALOG__Get_FILE_LIST(const int& seq_id,
										const CString& sub_dir,
										const CString& file_ext,
										CStringArray& file_list) = 0;

	virtual int  DATALOG__Get_FILE_LIST(const int& seq_id,
										const CString& sub_dir,
										const CString& file_ext,
										CStringArray& file_list,
										CStringArray& date_list) = 0;

	virtual int  DATALOG__Delete_FILE(const int& seq_id,
									  const CString& sub_dir,
									  const CString& file_ext,
									  const CString& file_name) = 0;

	virtual int  DATALOG__Copy_FILE(const int& seq_id,
								    const CString& sub_dir,
								    const CString& file_ext,
								    const CString& src_file,
								    const CString& trg_file) = 0;

	virtual int  DATALOG__Rename_FILE(const int& seq_id,
								      const CString& sub_dir,
								      const CString& file_ext,
									  const CString& src_file,
									  const CString& trg_file) = 0;

	virtual int  DATALOG__Upload_FILE(const int& seq_id,
									  const CString& sub_dir,
									  const CString& file_ext,
									  const CString& file_name,
									  CString& file_data) = 0;

	virtual int  DATALOG__Download_FILE(const int& seq_id,
									    const CString& sub_dir,
									    const CString& file_ext,
									    const CString& file_name,
									    const CString& file_data) = 0;

	virtual int  ROOT__Get_DIR_LIST(const int& seq_id,
								    const CString& sub_dir,
								    CStringArray& dir_list) = 0;

	virtual int  ROOT__Get_FILE_LIST(const int& seq_id,
									 const CString& sub_dir,
									 const CString& file_ext,
									 CStringArray& file_list) = 0;

	virtual int  ROOT__Get_FILE_LIST(const int& seq_id,
									 const CString& sub_dir,
									 const CString& file_ext,
									 CStringArray& file_list,
									 CStringArray& date_list) = 0;

	virtual int  ROOT__Delete_FILE(const int& seq_id,
								   const CString& sub_dir,
								   const CString& file_ext,
								   const CString& file_name) = 0;

	virtual int  ROOT__Copy_FILE(const int& seq_id,
								 const CString& sub_dir,
								 const CString& file_ext,
								 const CString& src_file,
								 const CString& trg_file) = 0;

	virtual int  ROOT__Rename_FILE(const int& seq_id,
								   const CString& sub_dir,
								   const CString& file_ext,
								   const CString& src_file,
								   const CString& trg_file) = 0;

	virtual int  ROOT__Upload_FILE(const int& seq_id,
								   const CString& sub_dir,
								   const CString& file_ext,
								   const CString& file_name,
								   CString& file_data) = 0;

	virtual int  ROOT__Download_FILE(const int& seq_id,
									 const CString& sub_dir,
									 const CString& file_ext,
									 const CString& file_name,
									 const CString& file_data) = 0;

	virtual int  CONFIG__Get_LOG_INFO(const int& seq_id,
									  CStringArray& channel_list,
								      CStringArray& win_list) = 0;

	virtual int  CONFIG__Get_IO_INFO(const int& seq_id,
									 const CString& io_type,
									 const int& in_out_type,
									 const CStringArray& para_list,
									 CStringArray& bd_no_list,
									 CStringArray& ch_no_list,
									 CStringArray& ch_name_list) = 0;

	virtual int Get__SEQ_VERSION(const int seq_id) = 0;

	virtual int PM__Get_DIR_LIST(const int& seq_id,
								 CStringArray& l_dir) = 0;

	virtual int  DATALOG__Get_DIR_DATE_LIST(const int& seq_id,
									        const CString& sub_dir,
									        CStringArray& l_dir,
											CStringArray& l_date) = 0;

	virtual int  ROOT__Get_DIR_DATE_LIST(const int& seq_id,
									     const CString& sub_dir,
									     CStringArray& l_dir,
									     CStringArray& l_date) = 0;

	virtual int PM__Get_DIR_LIST_EX(const int& seq_id,
									const CString& sub_dir,
								    CStringArray& l_dir) = 0;

	virtual int Get__SEQ_CORE_VERSION(const int seq_id) = 0;
	virtual int Get__SEQ_APPs_VERSION(const int seq_id) = 0;

	virtual int Get_Rcp_History(const int seq_id,
							    const CString& channel_name,
							    int& ack,
							    CStringArray& l_time_data) = 0;

	// ...
	virtual int Set_Channel_Data_By_LB_Event(const CString& event_msg,
											 const int seq_id,
										     const CString& set_type,
										     const CStringArray& name_list,
										     const CStringArray& data_list) = 0;

	virtual int Set_Channel_Data_With_Comment(const CString& event_msg,
											  const CString& str_comment,
											  const int seq_id,
											  const CString& set_type,
											  const CStringArray& name_list,
											  const CStringArray& data_list) = 0;
};
