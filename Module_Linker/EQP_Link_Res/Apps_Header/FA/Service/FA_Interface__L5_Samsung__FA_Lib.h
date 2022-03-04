#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__L5_Samsung__Msg_Type.h"


class SCI__L5_Samsung__FA_Lib
{
public:
	virtual ~SCI__L5_Samsung__FA_Lib(){};

	//===========================================================================================================================================
	// ...
	virtual int Open__Service_Name(const CString& service_name) = 0;
	
	virtual int Send__Event(const int sx,const int fy,const int sxfy_type = 0, const int event_id = -1) = 0;
	virtual int Send__Wait(const int event_id,const double timeout_sec = 0.0) = 0;

	// ...
	virtual int Define_Start__Event(const int sx,const int fy, const int sxfy_type = 0, const int event_type = 0,const int ceid = 0) = 0;
	virtual int Add__Msg_Info_To_Event(const int event_id, const int msg_id,void* p_msg_info) = 0;
	virtual int Define_End__Event(const int event_id) = 0;
	virtual int Define_Clear__Event(const int event_id) = 0;

	// ...
	virtual int Get__Event_Header_To_Report(CDS_Msg_Type__Event_Header& ds_event_header) = 0;
	virtual int Clear__Event_Resource(const int event_id) = 0;
	virtual int Clear__All_Event_Resource() = 0;

	virtual int Get__Event_Type_And_CEID_Of_Event_ID(const int event_id, int& event_type,int& ceid) = 0;
	virtual int Get__Msg_Header_Of_Event_ID(const int event_id, CDS_Msg_Type__Msg_Header& ds_event_header) = 0;
	virtual void* Get_Address__Msg_Info_With_Msg_Type_Of_Event_ID(const int event_id,const int msg_type) = 0;
	
	virtual void* Get_Address__First_Msg_Info(const int event_id, int& msg_id) = 0;
	virtual void* Get_Address__Next_Msg_Info(const int event_id, int& msg_id) = 0;
	
	virtual void* Get_Address__Msg_Info_Of_DB_Index(const int event_id,const int db_index, int& msg_id) = 0;
	//

	//===========================================================================================================================================
	// Utility ...
	virtual int Get__DataID() = 0;
	
	virtual CString Get__Date_And_Time__YYYYMMDDhhmmss() = 0;
	virtual CString Get__Date_And_Time__YYYYMMDDhhmmsscc() = 0;

	virtual int Convert__HEXA_TO_U2_1BYTE(const CString& str_hexa,int& i_data) = 0;
	virtual int Convert__HEXA_TO_U2_ARRAY(const CString& str_hexa,int& i_data1,int& i_data2) = 0;
	virtual int Convert__HEXA_TO_U1_ARRAY(const CString& str_src, const int data_size,unsigned int* p_data) = 0;
	virtual int Convert__HEXA_TO_BINARY_ARRAY(const CString& str_src, const int data_size,int* p_data) = 0;
	
	virtual int Check__ONLY_CHAR_NUMBER(const CString& str_data) = 0;

	virtual int Check__Same_String_Count(const CString& cmp_str,const CStringArray& l_str) = 0;

	//===========================================================================================================================================
	// System ...
	virtual int TOOLID__Link_Channel_Name(const int seq_id,const CString& ref_toolid,const CString& ch_name) = 0;
	virtual int EQST_OF_TOOLID__Link_Channel_Name(const int seq_id,const CString& ref_toolid,const CString& ch_name) = 0;
	virtual int TID_OF_TOOLID__Link_Channel_Name(const int seq_id,const CString& ref_toolid,const CString& ch_name) = 0;
	
	virtual int UNITID__Link_Channel_Name(const int seq_id,const CString& ref_toolid,const CString& ref_unitid,const CString& ch_name) = 0;
	virtual int EQST_OF_UNITID__Link_Channel_Name(const int seq_id,const CString& ref_toolid,const CString& ref_unitid,const CString& ch_name) = 0;
	
	virtual int GLASS_OF_TOOLID__Link_Channel_Name(const int seq_id,
												   const CString& ref_toolid,
												   const CString& ref_pos,
												   const CStringArray& l_key_name,
												   const CStringArray& l_ch_name) = 0;

	virtual int LOCAL_STATUS__Link_Channel_Name(const int seq_id,
											    const CString& ref_toolid,
												const CStringArray& l_key_name,
												const CStringArray& l_ch_name) = 0;
	
	//
	virtual int Update__INFO_OF_TOOL_LEVEL() = 0;
	virtual int Update__INFO_OF_UNIT_LEVEL() = 0;

	virtual int Update__GLASS_INFO_OF_SEQID() = 0;
	virtual int Update__GLASS_INFO_OF_SEQID(const int seq_id) = 0;

	virtual int Update__LOCAL_STATUS_OF_SEQID() = 0;
	virtual int Update__LOCAL_STATUS_OF_SEQID(const int seq_id) = 0;

	//
	virtual int Get__SEQID_LIST(CUIntArray& l_seq_id) = 0;
	
	//
	virtual int Get__CUR_TOOLID_LIST(CStringArray& l_cur_toolid) = 0;
	virtual int Get__CUR_TOOLID_LIST(const int seq_id,CStringArray& l_cur_toolid) = 0;

	//
	virtual int Get__UNITID_EQST_OF_UNIT_LEVEL(const CString& cur_toolid,CStringArray& l_cur_unitid,CStringArray& l_eqst) = 0;
	virtual int Get__UNITID_EQST_OF_UNIT_LEVEL(const int seq_id,const CString& cur_toolid,CStringArray& l_cur_unitid,CStringArray& l_eqst) = 0;

	virtual int Check__TID(const int i_tid) = 0;
	virtual int Get__ALL_TOOLID_OF_TID(const int i_tid,CString& ref_toolid,CString& cur_toolid) = 0;

	//
	virtual int Get__REF_TOOLID_OF_CUR_TOOLID(const CString& cur_toolid,CString& ref_toolid) = 0;
	virtual int Get__REF_TOOLID_OF_CUR_TOOLID(const int seq_id,const CString& cur_toolid,CString& ref_toolid) = 0;

	virtual int Get__CUR_TOOLID_OF_REF_TOOLID(const CString& ref_toolid,CString& cur_toolid) = 0;
	virtual int Get__CUR_TOOLID_OF_REF_TOOLID(const int seq_id,const CString& ref_toolid,CString& cur_toolid) = 0;

	//
	virtual int Get__REF_TOOLID_LIST(const int seq_id,CStringArray& l_ref_toolid) = 0;
	virtual int Get__REF_TOOLID_LIST(const int seq_id,CStringArray& l_ref_toolid,CStringArray& l_cur_toolid) = 0;

	//
	virtual int Get__CUR_UNITID_LIST(const int seq_id,const CString& cur_toolid,CStringArray& l_cur_unitid) = 0;

	virtual int Get__CUR_UNITID_OF_REF_UNITID(const CString& ref_toolid,const CString& ref_unitid,CString& cur_unitid) = 0;
	virtual int Get__CUR_UNITID_OF_REF_UNITID(const int seq_id,const CString& ref_toolid,const CString& ref_unitid,CString& cur_unitid) = 0;
	
	//
	virtual int Check__CUR_TOOLID(const CString& cur_toolid) = 0;
	virtual int Check__CUR_TOOLID(const CString& cur_toolid,int& seq_id) = 0;
	virtual int Check__CUR_TOOLID(const int seq_id,const CString& cur_toolid) = 0;

	virtual int Check__CUR_UNITID(const CString& cur_toolid,const CString& cur_unitid) = 0;
	virtual int Check__CUR_UNITID(const CString& curr_toolid,const CString& cur_unitid,int& seq_id) = 0;
	virtual int Check__CUR_UNITID(const int seq_id,const CString& cur_toolid,const CString& cur_unitid) = 0;

	// ...
	virtual int Load__Posted_Alarm_Item(const int seq_id,const CDS_Msg_Type__Alarm_Item& ds_item)  = 0;
	
	virtual int Clear__Posted_Alarm_Item(const int seq_id,const CDS_Msg_Type__Alarm_Item& ds_item) = 0;
	virtual int Clear__All_Posted_Alarm_Item(const int seq_id) = 0;
	virtual int Clear__All_Posted_Alarm_Item() = 0;

	virtual int Get__All_Posted_Alarm_List(CDS_Msg_Type__Alarm_Info& ds_info) = 0;
	virtual int Get__All_Posted_Alarm_List(const int seq_id,CDS_Msg_Type__Alarm_Info& ds_info) = 0;

	virtual int Check__Alarm_ID(const int seq_id,const int alarm_id) = 0;
	virtual int Check__Alarm_ID(const int alarm_id) = 0;

	// ...
	virtual int Set_Active__TID_Info(const CDS_L5__TID_INFO& ds_tid) = 0;
	virtual int Get_Active__TID_Info_Of_SxFy(const int sx,const int fy,CDS_L5__TID_INFO& ds_tid) = 0;
	virtual int Check_Active__TID_Of_SxFy(const int sx,const int fy) = 0;
	virtual int Check_Active__TID_Of_SxFy(const int sx,const int fy,int& i_tid) = 0;

	// ...
	virtual int EOID_Link__Channel_Name(const CString& ref_toolid,const int i_eoid,const CString& ch_name) = 0;

	virtual int Get__ALL_EOID_LIST(CUIntArray& l_eoid) = 0;
	virtual int Get__EOID_LIST(const CString& ref_toolid,CUIntArray& l_eoid) = 0;

	virtual int Get__ALL_EOID_EOV_LIST(CUIntArray& l_eoid,CUIntArray& l_eov) = 0;
	virtual int Get__EOID_EOV_LIST(const CString& ref_toolid,CUIntArray& l_eoid,CUIntArray& l_eov) = 0;

	virtual int Check__ALL_EOID(const int i_eoid) = 0;
	virtual int Check__EOID(const CString& ref_toolid,const int i_eoid) = 0;
	
	virtual int Check__ALL_EOV_OF_EOID(const int i_eoid,const int i_eov) = 0;
	virtual int Check__EOV_OF_EOID(const CString& ref_toolid,const int i_eoid,const int i_eov) = 0;
	
	virtual int Get__ALL_EOV_OF_EOID(const int i_eoid, int& i_eov) = 0;
	virtual int Get__EOV_OF_EOID(const CString& ref_toolid,const int i_eoid, int& i_eov) = 0;

	virtual int Check__RANGE_OF_EOV(const int i_eoid,const int i_eov) = 0;
	virtual int Check__RANGE_OF_EOV(const CString& ref_toolid,const int i_eoid,const int i_eov) = 0;

	//
	virtual int EOID_Change_Req__ALL_INIT() = 0;
	virtual int EOID_Change_Req__INIT(const CString& ref_toolid) = 0;

	virtual int EOID_Change_Req__ALL_EOID_EOV(const int i_eoid,const int i_eov) = 0;
	virtual int EOID_Change_Req__EOID_EOV(const CString& ref_toolid,const int i_eoid,const int i_eov) = 0;

	virtual int EOID_Change_Req__ALL_APPLY() = 0;	
	virtual int EOID_Change_Req__APPLY(const CString& ref_toolid) = 0;	

	// ...
	virtual int Get__ALL_GLASS_POS_IN_TOOLID(const int seq_id,
		                                     const CString& ref_toolid,
											 const int flag_glass_exist,
											 CStringArray& l_ref_pos) = 0;
	virtual int Get__GLASS_INFO_IN_TOOLID(const int seq_id,
								          const CString& ref_toolid,
							              const CString& ref_pos,
		                                  const CStringArray& l_key_name,
		                                  CStringArray& l_key_data) = 0;

	// ...
	virtual int Get__ALL_JOBID_IN_TOOLID(const CString& ref_toolid,
										 CStringArray& l_jobid) = 0;

	virtual int Get__ALL_GLASS_POS_OF_JOBID(const CString& ref_toolid,
											const CString jobid,
											CStringArray& l_ref_pos) = 0;

	virtual int Get__GLASS_INFO_OF_JOBID(const CString& ref_toolid,
										 const CString& jobid,
										 const CStringArray& l_key_name,
									     CStringArray& l_key_data) = 0;
	virtual int Get__GLASS_INFO_OF_JOBID(const CString& ref_toolid,
										 const CString& jobid,
										 const CString& ref_pos,
										 const CStringArray& l_key_name,
										 CStringArray& l_key_data) = 0;

	// ...
	virtual int Get__LOCAL_STATUS_OF_TOOLID(const CString& ref_toolid,
											const CStringArray& l_key_name,
											CStringArray& l_key_data) = 0;

	// ...
	virtual int Get__DB_INFO_OF_ID(const int db_id, CString& str_db) = 0;


	//===========================================================================================================================================
	// ...
	virtual int Add__Msg_Info_To_User_Event(const int event_id, const int user_msg_id,void* p_msg_info) = 0;
};
