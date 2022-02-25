#pragma once

#include "Interface_Code.h"


class CMacro_FA
{
private:
	CRITICAL_SECTION mCS_LOCK;

	//.....
	CX_FA_300mm_LINK xFA_300mm_Link;

	int iInit_Flag;
	int Fnc_Init();
	int Check__Address(const void* p_addr,const CString& msg);
	//

public:
	CMacro_FA();
	~CMacro_FA();

	//.....
	CI_FA_VARIABLE_CTRL*   Get__FA_VAR_CTRL();
	CI_FA_DB__ECID_CTRL*   Get__FA_ECID_CTRL();
	CI_FA_300mm__E30_CTRL* Get__FA_E30_CTRL();

	//.....
	int  Is__CONNECTED();
	int  Is__ONLINE();
	int  Is__LOCAL();
	int  Is__REMOTE();
	int  Is__OFFLINE();
	int  SEPARATE();

	//
	int  Send__S1F1();
	int  Send__S2F17();

	//
	int  Is_LP__BYPASS_ID(const int ptn);

	int  CJOB__HOQ(const CString& cjobid);
	int  CJOB__CANCEL(const CString& cjobid);
	int  CJOB__ABORT_IN_QUEUED_Or_SELECTED(const CString& cjobid);

	int  PJOB__CANCEL(const CString& pjobid);

	//
	int  Create__Local_PJOBID(const CString& job_name,
								const CString& cstid,
								const int ptn,
								const CUIntArray& l_slotmap,
								const CString& ppid);

	int  Create__Local_CJOBID(const CString& job_name,const CString& cstid);

	//
	int  Write__VISION_RECIPE(const int ptn,const int slot,const CString& vision_recipe);
	int  Read__VISION_RECIPE(const int ptn,const int slot,CString& vision_recipe);

	int  Report_CEID(const int ceid);
	int  LP__START(const int ptn);

	int  Set__REPORT_ALL_ALARM();
	int  Clear__REPORT_ALL_ALARM();

	//.....
	int  Event__CHM__DOWN(const int pmc_id);

	int  Event__CHM__DOOR_OPEN(const int pmc_id);
	int  Event__CHM__DOOR_CLOSE(const int pmc_id);

	int  Event__CHM__LIFT_PIN_UP(const int pmc_id);
	int  Event__CHM__LIFT_PIN_DOWN(const int pmc_id);

	//.....
	int  LOG_CTRL__Enable();
	int  LOG_CTRL__Disable();

	int  LOG_CTRL__Enable_Ctrl_Msg();
	int  LOG_CTRL__Disable_Ctrl_Msg();
	int  LOG_CTRL__Enable_SECSI();
	int  LOG_CTRL__Disable_SECSI();
	int  LOG_CTRL__Enable_SECSII();
	int  LOG_CTRL__Disable_SECSII();
	int  LOG_CTRL__Enable_S6F1_LOG();
	int  LOG_CTRL__Disable_S6F1_LOG();

	int  LOG_CTRL__Set_Date_Size(const int date_size);
	int  LOG_CTRL__Set_Interval_Time(const int log_min);

	//.....
	int  ENG_CALL__Report_Equipment(const CString& call_msg);
	int  ENG_CALL__Report_Process(const CString& call_msg);

	//.....
	int  Event__COMMUNICATION_STATE__DISABLE_TO_ENABLE();
	int  Event__COMMUNICATION_STATE__ENABLE_TO_DISABLE();

	//.....
	int  Event__MESSAGE_CONFIRM();
};
