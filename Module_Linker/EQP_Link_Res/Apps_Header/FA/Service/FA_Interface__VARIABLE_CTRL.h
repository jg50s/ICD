#pragma once


class CI_FA_VARIABLE_CTRL
{
public:
	virtual ~CI_FA_VARIABLE_CTRL(){};

	//----------------------------------------------------
	virtual int Set_Variable(const CString& main_name,
							 const CString& sub_name,
						     const CStringArray& data_list) = 0;
	virtual int Get_Variable(const CString& main_name,
							 const CString& sub_name,
							 CStringArray& data_list) = 0;

	virtual int Set_Variable(const CString& main_name,
							 const CString& sub_name,
						     const CString& data) = 0;
	virtual int Get_Variable(const CString& main_name,
							 const CString& sub_name,
							 CString& data) = 0;

	//----------------------------------------------------
	virtual int Add_Variable(const CString& main_name,
							 const CString& sub_name,
							 const CString& data) = 0;
	
	virtual int Clear_Variable(const CString& main_name) = 0;
	virtual int Clear_Variable(const CString& main_name,
							   const CString& sub_name) = 0;

	// ...
	virtual int Set__Head_Name(const int ptn,const int slot, const CString& head_name) = 0;


	//----------------------------------------------------
	// Data Info ...
	
	virtual int Set__Data_Info(const CString& main_name,
		                       const CString& sub_name,
							   const CString& key_name,
							   const CString& str_data) = 0;
	virtual int Set__Data_Info(const CString& main_name,
		                       const CString& sub_name,
							   const CString& key_name,
		                       const CStringArray& l_data) = 0;

	virtual int Add__Data_Info(const CString& main_name,
		                       const CString& sub_name,
							   const CString& key_name,
		                       const CString& str_data) = 0;

	virtual int Get__Data_Info(const CString& main_name,
		                       const CString& sub_name,
							   const CString& key_name,
		                       CString& str_data) = 0;
	virtual int Get__Data_Info(const CString& main_name,
		                       const CString& sub_name,
							   const CString& key_name,
		                       CStringArray& l_data) = 0;
	virtual int Get__Data_Info(const CString& main_name,
		                       const CString& sub_name,
		                       CStringArray& l_key_name,
		                       CStringArray& l_data) = 0;

	virtual int Get__Main_Name_Of_Data_Info(CStringArray& l_main_name) = 0;
	virtual int Get__Sub_Name_Of_Data_Info(const CString& main_name,
		                                   CStringArray& l_sub_name) = 0;
	virtual int Get__Key_Name_Of_Data_Info(const CString& main_name,
		                                   const CString& sub_name,
										   CStringArray& l_key_name) = 0;

	virtual int Clear__All_Of_Data_Info() = 0;
	virtual int Clear__Main_Name_Of_Data_Info(const CString& main_name) = 0;
	virtual int Clear__Sub_Name_Of_Data_Info(const CString& main_name,
		                                     const CString& sub_name) = 0;
	virtual int Clear__Key_Name_Of_Data_Info(const CString& main_name,
		                                     const CString& sub_name,
								             const CString& key_name) = 0;


	//----------------------------------------------------
	// Command Info ...

	virtual int Set__Command_Info(const CString& main_cmmd,
		                          const CString& sub_cmmd,
								  const CStringArray& l_para) = 0;

	virtual int Get__Command_Info(CString& main_cmmd,
							      CString& sub_cmmd,
								  CStringArray& l_para) = 0;
	virtual int Get__Command_Size() = 0;

	virtual int Clear__All_Command_Info() = 0;

	// ...
	// Return  :  OK ( > 0), Error ( < 0), Timeout ( == 0)
	virtual int Call__Command_Info(const CString& main_cmmd,
		                           const CString& sub_cmmd,
		                           const CStringArray& l_para,
								   const double timeout_sec,
								   CString& result_info) = 0;

	virtual int Report__Command_Result_OK(const int command_id,
		                                  const CString& result_info) = 0;
	virtual int Report__Command_Result_ERROR(const int command_id,
		                                     const CString& result_info) = 0;
	

	//----------------------------------------------------
	// CMP Info ...

	virtual int Get__Head_Name(const int ptn,const int slot, CString& head_name) = 0;
};
