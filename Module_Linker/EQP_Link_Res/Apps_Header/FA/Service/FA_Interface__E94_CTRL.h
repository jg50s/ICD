#pragma once

typedef int (*E94_Callback__CJOB_Upload)(const int req_id, const CString& job_id,const int ptn_id);

#define E94_CALLBACK__CJOB_UPLOAD__REQID__CJOB_CREATE                         1
#define E94_CALLBACK__CJOB_UPLOAD__REQID__SETUP_PJOBID_AUTO_START            11
#define E94_CALLBACK__CJOB_UPLOAD__REQID__SETUP_PJOBID_MANUAL_START          12
#define E94_CALLBACK__CJOB_UPLOAD__REQID__PJOBID_MANUAL_USER_START           21
#define E94_CALLBACK__CJOB_UPLOAD__REQID__PJOBID_MANUAL_USER_CANCEL          22


class CI_FA_300mm__E94_CTRL
{
public:
	virtual ~CI_FA_300mm__E94_CTRL(){};

	//----------------------------------------------------
	virtual int  Is_Active() = 0;

	//------------------------------------
	// CJobCreate
	virtual int  Create_CJob(const CString& cjobid) = 0;

	virtual int  Clear_CJob() = 0;
	virtual int  Get_CJob_Error(int& err_code,CString& err_text) = 0;

	virtual int  Load_ProcessOrderMgmt(const int mode) = 0;
	virtual int  Load_StartMethod(const int mode) = 0;
	virtual int  Load_CarrierID(const CString& carrierid) = 0;
	virtual int  Load_PJobID(const CString& pjobid) = 0;
	virtual int  Load_PauseEvent(const int ceid) = 0;

	//------------------------------------
 	virtual int  Get_VID__CJOB_STATUS(const CString& cjobid,
									  int& status) = 0;

	virtual	int  Get_VID__CJOB_SPACE() = 0;

	virtual int  Get_VID__LIST_Of_CJOB_QUEUED(CStringArray& cjobid_list) = 0;

	//------------------------------------
	virtual int  Start_CJob(const CString& cjobid)    = 0;
	virtual int  Pause_CJob(const CString& cjobid)    = 0;
	virtual int  Resume_CJob(const CString& cjobid)   = 0;
	virtual int  Cancel_CJob(const CString& cjobid)   = 0;
	virtual int  Deselect_CJob(const CString& cjobid) = 0;
	virtual int  Stop_CJob(const CString& cjobid)	  = 0;
	virtual int  Abort_CJob(const CString& cjobid)    = 0;
	virtual int  HOQ_CJob(const CString& cjobid)      = 0;
	
	virtual int  Deselect_CJob() = 0;

	virtual int  Create__Local_CJOBID(const CString& job_name,
									  const CString& cstid) = 0;

	virtual int  Cancel_CJob(const CString& cjobid,const int remove_flag) = 0;
	virtual int  Stop_CJob(const CString& cjobid,  const int remove_flag) = 0;
	virtual int  Abort_CJob(const CString& cjobid, const int remove_flag) = 0;


	//------------------------------------
	// CJobCreate
	
	virtual int  Load_MtrlOutSpec(const CString& lotid,const CUIntArray& slot_list) = 0;


	//------------------------------------
	virtual int  Get_VID__SOURCE_LP_LOTID(const CString& src_cstid,
										  CString& lotid) = 0;
	virtual int  Get_VID__SOURCE_SLOT_INFO(const CString& src_cstid,
										   CUIntArray& l_slot) = 0;

	virtual int  Get_VID__TARGET_LP_CSTID(const CString& src_cstid,
										  CString& cstid) = 0;
	virtual int  Get_VID__TARGET_LP_LOTID(const CString& src_cstid,
										  CString& lotid) = 0;
	virtual int  Get_VID__TARGET_SLOT_INFO(const CString& src_cstid,
										   CUIntArray& l_slot) = 0;


	//------------------------------------
	// CJob Control

	virtual int  Delete__All_CJob() = 0;
	virtual int  Delete__CJob_In_Queued_Or_Selected(const CString& cjob) = 0;

	virtual int  Abort__All_CJob() = 0;

	//
	virtual int  Complete_CJob(const CString& cjobid) = 0;

	//
	virtual int  Get__CJob_From_PJob(const CString& pjob,CString& cjob) = 0;


	//------------------------------------
	virtual int Select__CJOBID()  = 0;
	virtual int Execute__CJOBID() = 0;
	virtual int WaitingForStart_To_Execute_Or_Complete__CJOBID() = 0;
	virtual int SetUp__PJOBID() = 0;
	virtual int WaitingForStart_To_Processing_Or_Complete__PJOBID(const int flag__auto_start) = 0;
	virtual int Extinct__CJOBID() = 0;


	//------------------------------------
	virtual int Set__Scheduler_Pipeline_Mode(const int set_flag) = 0;
	virtual int Set__Scheduler_Pipeline_Next_Start(const int set_flag) = 0;

	//------------------------------------
	// jglee : 2016.04.06
	virtual int Register__CJOB_Callback(E94_Callback__CJOB_Upload fnc_addr)  = 0;
};
