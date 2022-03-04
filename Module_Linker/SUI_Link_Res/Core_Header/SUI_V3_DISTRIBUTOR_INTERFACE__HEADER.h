#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\GUI_DS.h"


//----------------------------------------------------
class CI_V3_DISTRIBUTOR_FACTORY_CTRL
{
public:
	virtual ~CI_V3_DISTRIBUTOR_FACTORY_CTRL(){};

	//-----------------------------------------
	virtual int System_Init() = 0;		

	virtual int Is_System_Init() = 0;		
	virtual int Init_Screen() = 0;		
	//-----------------------------------------
};

class CI_V3_DISTRIBUTOR_INFO_CTRL
{
public:
	virtual ~CI_V3_DISTRIBUTOR_INFO_CTRL(){};

	//-----------------------------------------
	virtual int Set_Channel_Data(const int seq_id,
								 const CUIntArray&   prefix_list,
								 const CStringArray& channel_list,
								 const CStringArray& data_list) = 0;

	virtual int Set_Alarm_Info(const int seq_id,
							   const int alarm_type,
							   const int alarm_id,
							   const CString& time,
							   const CString& title,
							   const CString& message,
							   const CUIntArray& optoin_list) = 0;

	virtual int Delete_Alarm_Info(const int seq_id,
							      const int alarm_type,
							      const int alarm_id,
							      const CString& time) = 0;

	virtual int Set_Module_Offline(const int seq_id) = 0;
	//-----------------------------------------

	//-----------------------------------------
	virtual int Set__USER_LEVEL(const CString& user_level) = 0;

	virtual int Set__USER_ID(const CString& userid) = 0;
	//-----------------------------------------

	//-----------------------------------------
	virtual int Get_Alarm__Post_Info_List(int& seq_id,
										  int& alarm_type,
										  int& alarm_id,
										  CString& time,
										  CString& title,
										  CString& message,
										  CUIntArray& option_list) = 0;

	virtual int Get_Alarm__Size() = 0;

	virtual int Clear_Alarm__Info(const int& module_name,
								  const int& alarm_type,
								  const int& alarm_id,
								  const CString& time,
								  const int& result) = 0;
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
};
//----------------------------------------------------
