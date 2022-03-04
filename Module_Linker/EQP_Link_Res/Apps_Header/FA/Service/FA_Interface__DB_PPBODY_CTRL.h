#pragma once


class CI_FA_DB__PPBODY_CTRL
{
public:
	virtual ~CI_FA_DB__PPBODY_CTRL(){};

	//----------------------------------------------------
	// FORMAT
	virtual int Get_FORMAT_From_PM_ID(CString& unit,int& size) = 0;
	virtual int Get_FORMAT_From_PM_RECIPE(CString& unit,int& size) = 0;

	// PM ID
	virtual int Set_Current_PM_ID(const int pm_id) = 0;
	virtual int Get_Current_PM_ID(CString& pm_id) = 0;

	// STEP PARAMETER
	virtual int Get_STEP_PARAMETER_SIZE() = 0;
	virtual int Get_STEP_PARAMETER_From_INDEX(int index,
											  CString& item_name,CString& item_unit,CString& item_range,
											  CString& ch_name,CString& ch_type,
											  CString& fmt_unit,int& size) = 0;
	virtual int Get_STEP_PARAMETER_From_ITEM_NAME(const CString& item_name,
												  CString& item_unit,CString& item_range,
												  CString& ch_name,CString& ch_type,
												  CString& fmt_unit,int& size) = 0;

	virtual int Check_STEP_DATA(int index,const CString& data) = 0;
	virtual int Check_STEP_DATA(const CString& item_name,const CString& data) = 0;
	
	// CFG PARAMTER
	virtual int Get_CFG_PARAMETER_SIZE() = 0;
	virtual int Get_CFG_PARAMETER_From_INDEX(int index,
											 CString& item_name,CString& item_unit,CString& item_range,
											 CString& ch_name,CString& ch_type,
											 CString& fmt_unit,int& size) = 0;
	virtual int Get_CFG_PARAMETER_From_ITEM_NAME(const CString& item_name,
												 CString& item_unit,CString& item_range,
												 CString& ch_name,CString& ch_type,
												 CString& fmt_unit,int& size) = 0;

	virtual int Check_CFG_DATA(int index,const CString& data) = 0;
	virtual int Check_CFG_DATA(const CString& item_name,const CString& data) = 0;


	//----------------------------------------------------
	virtual int Set_Current_CHM_Stage(const int chm_id,const int stage_id) = 0;

	
	//----------------------------------------------------
	virtual int Set__CFG_ITEM_RANGE_OF_PMx(const int pm_id,
										   const int stage_id,
		                                   const CString& str_ppbody,
		                                   const double min_value,
		                                   const double max_value) = 0;

	virtual int Set__STEP_ITEM_RANGE_OF_PMx(const int pm_id,
		                                    const int stage_id,
		                                    const CString& str_ppbody,
											const double min_value,
											const double max_value) = 0;

	virtual int Get__CFG_ITEM_RANGE_OF_PMx(const int pm_id,
		                                   const int stage_id,
										   const CString& str_ppbody,
										   CString& min_data,
										   CString& max_data) = 0;

	virtual int Get__STEP_ITEM_RANGE_OF_PMx(const int pm_id,
		                                    const int stage_id,
		                                    const CString& str_ppbody,
		                                    CString& min_data,
		                                    CString& max_data) = 0;
};
