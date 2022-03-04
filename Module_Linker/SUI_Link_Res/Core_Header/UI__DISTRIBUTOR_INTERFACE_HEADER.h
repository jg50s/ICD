#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\GUI_DS.h"


#define  GUI_TYPE__FAB							100
#define  GUI_TYPE__RCS							103


class CI_DISTRIBUTOR_FACTORY_CTRL
{
public:
	virtual ~CI_DISTRIBUTOR_FACTORY_CTRL(){};

	//-----------------------------------------
	virtual int  System_Init() = 0;		

	virtual int  Proc__SYSTEM_INIT(const int module_id,const int page_count) = 0;
	virtual void Proc__SYSTEM_INIT() = 0;

	virtual int Is_System_Init() = 0;		
	virtual int Init_Screen(const int module_id,const int page_count) = 0;		
	virtual int Init_Screen_End() = 0;		
	virtual int Init_Screen() = 0;		

	virtual int Init_Module1() = 0;
	virtual int Init_Module2() = 0;

	//-----------------------------------------
	virtual int  Editor_Init() = 0;		

};

class CI_DISTRIBUTOR_INFO_CTRL
{
public:
	virtual ~CI_DISTRIBUTOR_INFO_CTRL(){};
	
	//-----------------------------------------
	virtual int Set_Channel_Data(const int seq_id,
								 const CStringArray& channel_list,
								 const CStringArray& data_list) = 0;

	virtual int Set_Alarm_Info(const int seq_id,
							   const int sys_id,
							   const int alarm_id,
							   const int alarm_type,
							   CString& time,
							   CString& title,
							   CString& message,
							   CStringArray& l_option_act,
							   CStringArray& l_option_exp) = 0;
							
	virtual int Delete_Alarm_Info(const int seq_id,
								  const int sys_id,
								  const int alarm_id,
								  const CString& act_result,
							      const CString& clear_time) = 0;


	virtual int Set_Module_Offline(const int seq_id) = 0;
	//-----------------------------------------

	//-----------------------------------------
	virtual int Set__USER_LEVEL(const CString& user_level) = 0;

	virtual int Set__USER_ID(const CString& userid) = 0;
	//-----------------------------------------

	//-----------------------------------------
	virtual int Get_Alarm__Post_Info_List(int& seq_id,
										  int& sys_id,
										  int& alarm_id,
										  int& alarm_type,
										  CString& time,
										  CString& title,
										  CString& message,
										  CStringArray& l_option_act,
										  CStringArray& l_option_exp) = 0;

	virtual int Get_Alarm__Size() = 0;

	virtual int Clear_Alarm__Info(const int seq_id,
								  const int sys_id,
								  const int alarm_id,
								  const int alarm_type,
								  const CString& act_result) = 0;
	//-----------------------------------------

	//-----------------------------------------
	virtual int Get__SYS_INFO(CStringArray& info_list) = 0;
	//-----------------------------------------

	//-----------------------------------------
	virtual int Get__SEQ_DIR_RECIPE(const int& seq_id,
									CString& dir_recipe) = 0;

	virtual int Get__GUI_DIR_EXE(CString& dir_exe) = 0;


	virtual int Get__SEQ_DIR_ROOT(const int& seq_id,
								  CString& dir) = 0;

	virtual int Get__SEQ_DIR_CONFIG(const int& seq_id,
									CString& dir) = 0;

	virtual int Get__SEQ_DIR_DATALOG(const int& seq_id,
									 CString& dir) = 0;

	virtual int Get__SEQ_DIR_ROUTE(const int& seq_id,
								   CString& dir) = 0;

	virtual int Get__SEQ_DIR_CASSETTE(const int& seq_id,
									  CString& dir) = 0;
    
	virtual int Get__SEQ_DIR_JOB(const int& seq_id,
								 CString& dir) = 0;
	//-----------------------------------------

	//-----------------------------------------
	virtual int Get__DEFINE_INFO(const int& seq_id,
							     const CString& define,
							     CString& data) = 0;
	//-----------------------------------------

	//-----------------------------------------
	virtual int Get__SEQ_IP_PORT(const int seq_id,
								 CString& net_ip,
								 int& net_port) = 0;

	//-----------------------------------------

	//-----------------------------------------
	virtual void Get__Win_Module_List(CUIntArray& l_module_id) = 0;

	virtual void Get__Win_List(const int module_id,
							   CStringArray& l_win_name,
							   CStringArray& l_win_title,
							   CStringArray& l_level) = 0;

	virtual void Set__Win_Level(const int module_id,
								const CString& win_name,
								const CString& win_level) = 0;
	//-----------------------------------------

	//-----------------------------------------
	virtual void Get__Seq_List(CUIntArray& l_module_id) = 0;

	virtual void Get__Version_List(const int module_id,
							       CStringArray& l_obj_name,
							       CStringArray& l_obj_type,
							       CStringArray& l_obj_version) = 0;

	virtual int  Set__Seq_Version_Info(const int seq_id,
									   const CStringArray& l_obj_name,
									   const CStringArray& l_obj_type,
									   const CStringArray& l_obj_version) = 0;
	//-----------------------------------------

	//-----------------------------------------
	virtual void Get__Win_Module_List_Ex(CUIntArray& l_module_id,
										 CStringArray& l_module_name) = 0;

	virtual void Get__Seq_List_Ex(CUIntArray& l_module_id,
								  CStringArray& l_module_name) = 0;
	//-----------------------------------------

	//-----------------------------------------
	virtual int  Save__ECID_Page(const CUIntArray&   l_seq_id,
								 const CUIntArray&   l_ecid,
								 const CStringArray& l_name,
								 const CStringArray& l_data) = 0;

	//-----------------------------------------
	virtual int Get__Clear_Alarm_Info(CUIntArray& l_seq_id,
									  CUIntArray& l_sys_id,
									  CUIntArray& l_alm_id) = 0;

	virtual int Delete_Alarm__Info(const int seq_id,
								   const int sys_id,
								   const int alarm_id) = 0;

	//-----------------------------------------
	virtual int Get__GUI_TYPE() = 0;
	virtual int Get__RCS_CTRL_CH_LIST(CStringArray& l_ch) = 0;

	//-----------------------------------------
	virtual int Get__Current_ModuleID() = 0;
	virtual int Get__Current_Screen_Name(const int module_id,
										 CStringArray& l_page_name) = 0;
	virtual int Get__Current_Page_Data(const int module_id,
									   const CString& page_name,
									   CStringArray&  l_ch_name,
									   CStringArray&  l_ch_data) = 0;

	//.....
	virtual void Clear__RCS_ALARM_ID() = 0;
	virtual int  Load__RCS_ALARM_ID(const int seq_id,
									const CUIntArray& l_alarm_id) = 0;

	//.....
	virtual CString Get__SYSTEM_FONT_NAME() = 0;

	virtual int Get__SYSTEM_FONT_SIZE__MAIN_WIDTH()  = 0;
	virtual int Get__SYSTEM_FONT_SIZE__MAIN_HEIGHT() = 0;

	virtual int Get__SYSTEM_FONT_SIZE__SUB_WIDTH()  = 0;
	virtual int Get__SYSTEM_FONT_SIZE__SUB_HEIGHT() = 0;

	//.....
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

	// Core & APPs
	virtual int  Set__Seq_Version_Info_Ex(const int seq_id,
									      const int ver_type,
									      const CString& seq_ver,
									      const CStringArray& l_file_name,
									      const CStringArray& l_file_ver,
									      const CStringArray& l_file_date) = 0;

	//
	virtual void Get__Seq_Core_Ver_Title_List(CUIntArray&   l_seq_id,
											  CStringArray&	l_seq_ver_title) = 0;
	virtual void Get__Seq_APPs_Ver_Title_List(CUIntArray&   l_seq_id,
											  CStringArray&	l_seq_ver_title) = 0;

	// 
	virtual double Get__Gui_Core_Version() = 0;

	//
	virtual int Check__GUI_KEYPAD_MODE() = 0;


	//-----------------------------------------
	virtual int Set_Log_Channel_Data(const int seq_id,
									 const CStringArray& l_ch_name,
									 const CStringArray& l_ch_data) = 0;

	//-----------------------------------------
	virtual int Set_Alarm_Ex_Info(const int seq_id,
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

	virtual int Get_Alarm__Post_Info_Ex_List(int& seq_id,
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

	// ...
	virtual int Set__SYSTEM_FONT_NAME(const CString& font_name) = 0;
	
	virtual int Set__SYSTEM_FONT_SIZE__MAIN_WIDTH(const int main_width)  = 0;
	virtual int Set__SYSTEM_FONT_SIZE__MAIN_HEIGHT(const int main_height) = 0;
	
	virtual int Set__SYSTEM_FONT_SIZE__SUB_WIDTH(const int sub_width)  = 0;
	virtual int Set__SYSTEM_FONT_SIZE__SUB_HEIGHT(const int sub_height) = 0;

	// ...
	virtual int Get__SEQx_NAME(const int seq_id,
		                       CString& seq_name) = 0;

	virtual int Get__SEQx_NAME_LIST(CUIntArray& l_seq_id,
		                            CStringArray& l_seq_name) = 0;

	// ...
	virtual int Get_Log_Channel_Index(const int seqp_id, 
									  const CString& ch_name) = 0;

	virtual int Set_Log_Channel_Index(const int seq_id,
									 const CUIntArray&   l_ch_index,
									 const CStringArray& l_ch_data) = 0;

	// ...
	virtual int Set__MDx_TITLE(const int eqp_id, 
		                       const CString& md_title) = 0;
};	
