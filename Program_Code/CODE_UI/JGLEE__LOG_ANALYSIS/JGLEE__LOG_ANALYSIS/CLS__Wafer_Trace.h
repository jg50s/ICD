#pragma once


class CLS__MD_Info
{
public:
	CLS__MD_Info()	
	{
		Clear();
	}
	~CLS__MD_Info() 
	{

	}

	void Clear()	
	{
		bActive__PROCESS = false;
		bActive__PICK    = false;
		bActive__PLACE   = false;

		sPara__ACT    = "";
		sPara__ROBOT  = "";
		sPara__ARM    = "";
		sPara__MODULE = "";

		sPara__TIME_ACT   = "";
		sPara__TIME_START = "";
		sPara__TIME_END   = "";

		sPara__RT_OFFSET = "";
		sPara__RECIPE = "";
		sPara__LOG    = "";
		sPara__RESULT = "";
	}
	void Copy_From(const CLS__MD_Info& md_info)
	{
		bActive__PROCESS = md_info.bActive__PROCESS;
		bActive__PICK    = md_info.bActive__PICK;
		bActive__PLACE   = md_info.bActive__PLACE;

		sPara__ACT    = md_info.sPara__ACT;
		sPara__ROBOT  = md_info.sPara__ROBOT;
		sPara__ARM    = md_info.sPara__ARM;
		sPara__MODULE = md_info.sPara__MODULE;
		
		sPara__TIME_ACT   = md_info.sPara__TIME_ACT;
		sPara__TIME_START = md_info.sPara__TIME_START;
		sPara__TIME_END   = md_info.sPara__TIME_END;

		sPara__RT_OFFSET = md_info.sPara__RT_OFFSET;
		sPara__RECIPE = md_info.sPara__RECIPE;
		sPara__LOG    = md_info.sPara__LOG;
		sPara__RESULT = md_info.sPara__RESULT;
	}

	// ...
	bool bActive__PROCESS;
	bool bActive__PICK;
	bool bActive__PLACE;

	CString sPara__ACT;
	CString sPara__ROBOT;
	CString sPara__ARM;
	CString sPara__MODULE;
	
	CString sPara__TIME_ACT;
	CString sPara__TIME_START;
	CString sPara__TIME_END;

	CString sPara__RT_OFFSET;
	CString sPara__RECIPE;
	CString sPara__LOG;
	CString sPara__RESULT;
};

class DS__Wafer_Info
{
public:
	DS__Wafer_Info()
	{
		iPORTID = 0;
		iSLOTID = 0;
	}
	
	// ...
	int iPORTID;
	int iSLOTID;

	CString sLOTID;
	CString sPPID;
	CString sMATERIALID;

	CStringArray sList__STEP_RCP;

	CString sLOOP_ID;
	CString sLOOP_COUNT;
};


class CLS__Wafer_Info
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList__MD_INFO;

	// ...
	bool bActive__WAFER_INFO;

	int iPara__PORTID;
	int iPara__SLOTID;

	CString sPara__LOTID;
	CString sPara__PPID;
	CString sPara__MATERIALID;
	
	CStringArray sList__STEP_RCP;

	CString sPara__LOOP_ID;
	CString sPara__LOOP_COUNT;

	// ...
	int  _Get__MD_SIZE();
	int  _Get__MD_INFO(const int db_index, CLS__MD_Info& md_info);
	//

public:
	CLS__Wafer_Info();
	~CLS__Wafer_Info();

	// ...
	void Clear__ALL();

	// ...
	void Load__WFR_INFO(const DS__Wafer_Info& ds_info);
	void Load__MD_INFO(CLS__MD_Info md_info);

	// ...
	bool Is_Active__WFR_INFO();

	int  Get__WFR_INFO(DS__Wafer_Info& ds_info);

	int  Get__MD_SIZE();
	int  Get__MD_INFO(const int db_index, CLS__MD_Info& md_info);

	int  Get__CURRENT_PROCESS_SIZE();

	// ...
	int  Get__WAFER_DA_INFO(CStringArray& l_module, 
						    CStringArray& l_r_offset,
							CStringArray& l_t_offset);

	int  Get__WAFER_TACK_INFO(const bool active__search_move,
							  const bool active__search_proc,
							  CStringArray& l_module,
							  CStringArray& l_action,
							  CStringArray& l_result,
							  CStringArray& l_time,
							  CStringArray& l_comment);

	int  Get__PROCESS_LOG(CStringArray& l_md_info,
						  CStringArray& l_tack,
						  CStringArray& l_rcp,
						  CStringArray& l_log_info);

	int  Get__PROCESS_LOG(CStringArray& l_md_info,
						  CStringArray& l_log_info,
						  CStringArray& l_result);

	// ...
	void Display__WFR_INFO();
	void Display__MD_INFO();
};
