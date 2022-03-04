#pragma once


class CI_FA_300mm__E40_CTRL
{
public:
	virtual ~CI_FA_300mm__E40_CTRL(){};

	//----------------------------------------------------
	virtual int  Is_Active() = 0;

	//------------------------------------------------------------
	// PRJobCreate & PRJobCreateEnh & PRJobMultiCreate
	virtual int  Create_New_PRJob(CString& new_prjobid) = 0;
	virtual int  Create_PRJob(const CString& prjobid) = 0;
	
	virtual int  Clear_PRJob() = 0;
	virtual int  Get_PRJob_Error(int& err_code,CString& err_text) = 0;

	virtual int  Load_PRMtlType(const int mtl_type) = 0;			// 0D == Carrier, 0E == Substrate
	// Carrier Type
	virtual int  Load_CARRIERID(const CString& carrierid) = 0;
	virtual int  Load_SLOTID(const int id) = 0;
	// Substrate Type
	virtual int  Load_MID(const CString& mid) = 0;
	// Vision Visit
	virtual int  Load_VISION_VISIT(const int visit_flag) = 0;

	// PRRecipe Parameter
	virtual int  Load_RecipeMethod(const int recipe_method) = 0;	// 1 == Recipe only, 2 == Recipe with Variable Tuning
	virtual int  Load_RecID(const CString& recid) = 0;				// Route Recipe

	virtual int	 Load_PRProcessStart(const int start_method) = 0;	// 1 == Automatic start, 2 != Manual start
	virtual int	 Load_PRMtlOrder(const int prjob_order) = 0;			
		// 1 == ARRIVAL  : process whichever material first arrives.
		// 2 == LIST     : process in an order that maximizes throughput.
		// 3 == OPTIMIZE : process in an order that maximizes throughput.
	virtual int  Load_PauseEvent(const int ceid) = 0;				// list of : CEID 

	//------------------------------------------------------------
	/*
	virtual int  Get_VID__PRJOBID(CString& prjobid) = 0;
	virtual int  Get_VID__RECID(CString& recid) = 0;
	virtual int  Get_VID__PRSTATE(int& prstate) = 0;
	*/

	virtual int  Get_PJOBID_And_STATUS(const int db_index,CString& pjobid,int& pjob_sts) = 0;
	virtual int  Get_PJOB_SPACE() = 0;

	//------------------------------------------------------------
	virtual int  Dequeue_PJOBID(const CString& pjobid) = 0;
	virtual int  Dequeue_ALL(CStringArray& pjobid_list) = 0;

	virtual int  Change_PROCESS_START(const CString& pjobid,const int pr_start_bool) = 0;

	virtual int  Run_COMMAND(const CString& pjobid,
							 const CString& command) = 0;

	virtual int  Create__Local_PJOBID(const CString& job_name,
								      const CString& cstid,
								  	  const int ptn,
									  const CUIntArray& l_slotmap,
								      const CString& ppid) = 0;

	//------------------------------------------------------------
	virtual int  Get_PJOB_LIST__ABORT(CStringArray& pjob_list) = 0;
	virtual int  Get_PJOB_INFO(const CString& pjob,
							   CUIntArray& ptn_list,
							   CUIntArray& slot_list) = 0;

	
	//------------------------------------------------------------
	// Create PJob

	virtual int  Load__RCPPARNM_INFO(const CString& carrierid,
									 const CUIntArray& slotid_list,
									 const CStringArray& slotrcp_list) = 0;

	//
	virtual int  Complete_PJOBID(const CString& pjobid) = 0;

	//
	virtual int  Get__PJOB_FROM_PTN(const int ptn,CString& pjobid) = 0;
	virtual int  Delete__PJOB_FROM_PTN(const int ptn) = 0;
	
	//
	virtual int  Get__PJOB_FROM_PTN_And_SLOT(const int ptn,const int slotid,CString& pjobid) = 0;

	
	//------------------------------------------------------------
	// PRRecipe Parameter
	
	virtual int  Load_RecipeTuning(const CStringArray& l_rcp_name,
								   const CStringArray& l_rcp_data) = 0;	
	virtual int  Load_RecipeInfo(const int pm_id,
								 const CString& rcp_info) = 0;	

	// ...
	virtual int  Get_RecipeInfo_Of_PJobID(const CString& pjobid,
								          const int pm_id,
								          CString& rcp_info) = 0;	
};
