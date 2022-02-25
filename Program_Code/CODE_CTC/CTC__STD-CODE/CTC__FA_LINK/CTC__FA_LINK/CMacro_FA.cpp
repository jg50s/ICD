#include "StdAfx.h"
#include "CMacro_FA.h"


CMacro_FA mFA_Link;


// ...
CMacro_FA::CMacro_FA()
{
	InitializeCriticalSection(&mCS_LOCK);
	iInit_Flag = -1;
}
CMacro_FA::~CMacro_FA()
{
	DeleteCriticalSection(&mCS_LOCK);
}

// ...
int  CMacro_FA::Fnc_Init()
{
	EnterCriticalSection(&mCS_LOCK);

	if(iInit_Flag > 0)
	{
		LeaveCriticalSection(&mCS_LOCK);
		return 1;
	}

	while(1)
	{
		iInit_Flag = xFA_300mm_Link->Open("");

		if(iInit_Flag < 0)
		{
			Sleep(100);
			continue;
		}

		break;
	}

	LeaveCriticalSection(&mCS_LOCK);
	return iInit_Flag;
}
int  CMacro_FA::Check__Address(const void* p_addr,
							   const CString& msg)
{
	if(p_addr != NULL)		return 1;

	MessageBox(NULL,msg,"CMacro_FA : Address Null !!!",MB_OK|MB_TOPMOST);
	return -1;
}


//.....
#define  MACRO__CHECK_E30(MSG_STR)								\
	if(Fnc_Init() < 0)		return -1;								\
	\
	CI_FA_300mm__E30_CTRL *p_e30_ctrl								\
	= xFA_300mm_Link->Get_FA_300mm_CTRL()->Get_E30();				\
	\
	if(Check__Address(p_e30_ctrl,MSG_STR) < 0)						\
{																\
	return -1;													\
}

#define  MACRO__CHECK_E94(MSG_STR)								\
	if(Fnc_Init() < 0)		return -1;								\
	\
	CI_FA_300mm__E94_CTRL *p_e94_ctrl								\
	= xFA_300mm_Link->Get_FA_300mm_CTRL()->Get_E94();				\
	\
	if(Check__Address(p_e94_ctrl,MSG_STR) < 0)						\
{																\
	return -1;													\
}

#define  MACRO__CHECK_E40(MSG_STR)								\
	if(Fnc_Init() < 0)		return -1;								\
	\
	CI_FA_300mm__E40_CTRL *p_e40_ctrl								\
	= xFA_300mm_Link->Get_FA_300mm_CTRL()->Get_E40();				\
	\
	if(Check__Address(p_e40_ctrl,MSG_STR) < 0)						\
{																\
	return -1;													\
}


//.....
CI_FA_VARIABLE_CTRL* CMacro_FA::Get__FA_VAR_CTRL()
{
	if(Fnc_Init() < 0)		return NULL;

	//
	return xFA_300mm_Link->Get_FA_VARIABLE_CTRL();
}
CI_FA_DB__ECID_CTRL* CMacro_FA::Get__FA_ECID_CTRL()
{
	if(Fnc_Init() < 0)		return NULL;

	//
	CI_FA_DB_CTRL *p_db_ctrl = xFA_300mm_Link->Get_FA_DB_CTRL();

	return p_db_ctrl->Get_ECID_CTRL();
}
CI_FA_300mm__E30_CTRL* CMacro_FA::Get__FA_E30_CTRL()
{
	if(Fnc_Init() < 0)		return NULL;

	//
	return xFA_300mm_Link->Get_FA_300mm_CTRL()->Get_E30();
}

//.....
int  CMacro_FA::SEPARATE()
{
	if(Fnc_Init() < 0)		return -1;

	//xFA_300mm_Link->Send_SEPARATE();
	xFA_300mm_Link->Stop_DRIVER();
	return 1;
}

int  CMacro_FA::Is__CONNECTED()
{
	MACRO__CHECK_E30("Is__CONNECTED()");

	return p_e30_ctrl->Is_CONNECT();
}
int  CMacro_FA::Is__ONLINE()
{
	MACRO__CHECK_E30("Is__ONLINE()");

	return p_e30_ctrl->Is_ONLINE();
}
int  CMacro_FA::Is__LOCAL()
{
	MACRO__CHECK_E30("Is__LOCAL()");

	return p_e30_ctrl->Is_LOCAL();
}
int  CMacro_FA::Is__REMOTE()
{
	MACRO__CHECK_E30("Is__REMOTE()");

	return p_e30_ctrl->Is_REMOTE();
}
int  CMacro_FA::Is__OFFLINE()
{
	MACRO__CHECK_E30("Is__OFFLINE()");

	return p_e30_ctrl->Is_OFFLINE();
}

//
int  CMacro_FA::Send__S1F1()
{
	if(Fnc_Init() < 0)		return -1;

	return xFA_300mm_Link->Send_MSG(1,1);
}

int  CMacro_FA::Send__S2F17()
{
	if(Fnc_Init() < 0)		return -1;

	return xFA_300mm_Link->Send_MSG(2,17);
}

//
int  CMacro_FA::Report_CEID(const int ceid)
{
	if(Fnc_Init() < 0)		return -1;

	return xFA_300mm_Link->Send_EVENT(ceid); 
}
int  CMacro_FA::LP__START(const int ptn)
{
	MACRO__CHECK_E30("LP__START()");

	return p_e30_ctrl->Event__LP__START(ptn);
}

int  CMacro_FA::Set__REPORT_ALL_ALARM()
{
	MACRO__CHECK_E30("Set__REPORT_ALL_ALARM");

	return p_e30_ctrl->Set__REPORT_ALL_ALARM();
}
int  CMacro_FA::Clear__REPORT_ALL_ALARM()
{
	MACRO__CHECK_E30("Clear__REPORT_ALL_ALARM");

	return p_e30_ctrl->Clear__REPORT_ALL_ALARM();
}

int  CMacro_FA::Is_LP__BYPASS_ID(const int ptn)
{
	MACRO__CHECK_E30("Is_LP__BYPASS_ID()");

	return p_e30_ctrl->Is_LP__BYPASS_READ_ID(ptn);
}

//
int  CMacro_FA::CJOB__HOQ(const CString& cjobid)
{
	MACRO__CHECK_E94("CJOB__HOQ()");

	p_e94_ctrl->Deselect_CJob();
	return p_e94_ctrl->HOQ_CJob(cjobid);
}
int  CMacro_FA::CJOB__CANCEL(const CString& cjobid)
{
	MACRO__CHECK_E94("CJOB__CANCEL()");

	return p_e94_ctrl->Cancel_CJob(cjobid);
}
int  CMacro_FA::CJOB__ABORT_IN_QUEUED_Or_SELECTED(const CString& cjobid)
{
	MACRO__CHECK_E94("CJOB__ABORT_IN_QUEUED_Or_SELECTED()");

	return p_e94_ctrl->Delete__CJob_In_Queued_Or_Selected(cjobid);
}

//
int  CMacro_FA::PJOB__CANCEL(const CString& pjobid)
{
	MACRO__CHECK_E40("PJOB__CANCEL()");

	return p_e40_ctrl->Dequeue_PJOBID(pjobid);
}

//
int  CMacro_FA::Create__Local_PJOBID(const CString& job_name,
									 const CString& cstid,
									 const int ptn,
									 const CUIntArray& l_slotmap,
									 const CString& ppid)
{
	MACRO__CHECK_E40("Create__Local_PJOBID()");

	return p_e40_ctrl->Create__Local_PJOBID(job_name,cstid,ptn,l_slotmap,ppid);
}
int  CMacro_FA::Create__Local_CJOBID(const CString& job_name,
									 const CString& cstid)
{
	MACRO__CHECK_E94("Create__Local_CJOBID()");

	return p_e94_ctrl->Create__Local_CJOBID(job_name,cstid);
}

int  CMacro_FA::Write__VISION_RECIPE(const int ptn,
									 const int slot,
									 const CString& vision_recipe)
{
	//.....
	if(Fnc_Init() < 0)		return -1;

	CI_FA_VARIABLE_CTRL *p_variable_ctrl
		= xFA_300mm_Link->Get_FA_VARIABLE_CTRL();

	if(Check__Address(p_variable_ctrl,"Write__VISION_RECIPE()") < 0)
		return -1;

	//.....
	CString main_name;
	CString sub_name;
	CString var_data;

	main_name.Format("P%1d:%1d-INFO",ptn,slot);
	sub_name = "VIS_RCP";
	var_data.Format("%s",vision_recipe);

	return p_variable_ctrl->Set_Variable(main_name,sub_name,var_data);
}
int  CMacro_FA::Read__VISION_RECIPE(const int ptn,
									const int slot,
									CString& vision_recipe)
{
	//.....
	if(Fnc_Init() < 0)		return -1;

	CI_FA_VARIABLE_CTRL *p_variable_ctrl
		= xFA_300mm_Link->Get_FA_VARIABLE_CTRL();

	if(Check__Address(p_variable_ctrl,"Read__VISION_RECIPE()") < 0)
		return -1;

	//.....
	CString main_name;
	CString sub_name;
	CString var_data;

	main_name.Format("P%1d:%1d-INFO",ptn,slot);
	sub_name = "VIS_RCP";

	int flag = p_variable_ctrl->Get_Variable(main_name,sub_name,var_data);

	vision_recipe.Format("%s",var_data);
	return flag;
}


//.....
int  CMacro_FA::Event__CHM__DOWN(const int pmc_id)
{
	MACRO__CHECK_E30("Event__CHM__DOWN()");

	return p_e30_ctrl->Event__CHM__DOWN(pmc_id);
}

int  CMacro_FA::Event__CHM__DOOR_OPEN(const int pmc_id)
{
	MACRO__CHECK_E30("Event__CHM__DOOR_OPEN()");

	return p_e30_ctrl->Event__CHM__DOOR_OPEN(pmc_id);
}
int  CMacro_FA::Event__CHM__DOOR_CLOSE(const int pmc_id)
{
	MACRO__CHECK_E30("Event__CHM__DOOR_CLOSE()");

	return p_e30_ctrl->Event__CHM__DOOR_CLOSE(pmc_id);
}

int  CMacro_FA::Event__CHM__LIFT_PIN_UP(const int pmc_id)
{
	MACRO__CHECK_E30("Event__CHM__LIFT_PIN_UP()");

	return p_e30_ctrl->Event__CHM__LIFT_PIN_UP(pmc_id);
}
int  CMacro_FA::Event__CHM__LIFT_PIN_DOWN(const int pmc_id)
{
	MACRO__CHECK_E30("Event__CHM__LIFT_PIN_DOWN()");

	return p_e30_ctrl->Event__CHM__LIFT_PIN_DOWN(pmc_id);
}

int  CMacro_FA::Event__COMMUNICATION_STATE__DISABLE_TO_ENABLE()
{
	MACRO__CHECK_E30("Event__COMMUNICATION_STATE__DISABLE_TO_ENABLE()");

	return p_e30_ctrl->Event__COMMUNICATION_STATE__DISABLE_TO_ENABLE();
}
int  CMacro_FA::Event__COMMUNICATION_STATE__ENABLE_TO_DISABLE()
{
	MACRO__CHECK_E30("Event__COMMUNICATION_STATE__ENABLE_TO_DISABLE()");

	return p_e30_ctrl->Event__COMMUNICATION_STATE__ENABLE_TO_DISABLE();
}

int  CMacro_FA::Event__MESSAGE_CONFIRM()
{
	MACRO__CHECK_E30("Event__MESSAGE_CONFIRM()");

	return p_e30_ctrl->Event__MESSAGE_CONFIRM();
}


//.....
//#define 
int  CMacro_FA::LOG_CTRL__Enable()
{
	if(Fnc_Init() < 0)		return -1;

	xFA_300mm_Link->LOG_CTRL__Enable();
	return 1;
}
int  CMacro_FA::LOG_CTRL__Disable()
{
	if(Fnc_Init() < 0)		return -1;

	xFA_300mm_Link->LOG_CTRL__Disable();
	return 1;
}

int  CMacro_FA::LOG_CTRL__Enable_Ctrl_Msg()
{
	if(Fnc_Init() < 0)		return -1;

	xFA_300mm_Link->LOG_CTRL__Enable_Ctrl_Msg();
	return 1;
}
int  CMacro_FA::LOG_CTRL__Disable_Ctrl_Msg()
{
	if(Fnc_Init() < 0)		return -1;

	xFA_300mm_Link->LOG_CTRL__Disable_Ctrl_Msg();
	return 1;
}

int  CMacro_FA::LOG_CTRL__Enable_SECSI()
{
	if(Fnc_Init() < 0)		return -1;

	xFA_300mm_Link->LOG_CTRL__Enable_SECSI();
	return 1;
}
int  CMacro_FA::LOG_CTRL__Disable_SECSI()
{
	if(Fnc_Init() < 0)		return -1;

	xFA_300mm_Link->LOG_CTRL__Disable_SECSI();
	return 1;
}

int  CMacro_FA::LOG_CTRL__Enable_SECSII()
{
	if(Fnc_Init() < 0)		return -1;

	xFA_300mm_Link->LOG_CTRL__Enable_SECSII();
	return 1;
}
int  CMacro_FA::LOG_CTRL__Disable_SECSII()
{
	if(Fnc_Init() < 0)		return -1;

	xFA_300mm_Link->LOG_CTRL__Disable_SECSII();
	return 1;
}

int  CMacro_FA::LOG_CTRL__Enable_S6F1_LOG()
{
	if(Fnc_Init() < 0)		return -1;

	xFA_300mm_Link->LOG_CTRL__Enable_S6F1_LOG();
	return 1;
}
int  CMacro_FA::LOG_CTRL__Disable_S6F1_LOG()
{
	if(Fnc_Init() < 0)		return -1;

	xFA_300mm_Link->LOG_CTRL__Disable_S6F1_LOG();
	return 1;
}

int  CMacro_FA::LOG_CTRL__Set_Date_Size(const int date_size)
{
	if(Fnc_Init() < 0)		return -1;

	xFA_300mm_Link->LOG_CTRL__Set_Date_Size(date_size);
	return 1;
}
int  CMacro_FA::LOG_CTRL__Set_Interval_Time(const int log_min)
{
	if(Fnc_Init() < 0)		return -1;

	xFA_300mm_Link->LOG_CTRL__Set_Interval_Time(log_min);
	return 1;
}


//.....
int  CMacro_FA::ENG_CALL__Report_Equipment(const CString& call_msg)
{
	MACRO__CHECK_E30("ENG_CALL__Report_Equipment()");

	CI_FA_VARIABLE_CTRL *p_var_ctrl	= xFA_300mm_Link->Get_FA_VARIABLE_CTRL();

	if(p_var_ctrl != NULL)
	{
		CString main_name;
		CString sub_name;

		main_name = "ENG_CALL";
		sub_name  = "CALL_MSG";

		p_var_ctrl->Set_Variable(main_name,sub_name,call_msg);
	}

	return p_e30_ctrl->Event__EQUIPMENT_ENG_CALL();
}
int  CMacro_FA::ENG_CALL__Report_Process(const CString& call_msg)
{
	MACRO__CHECK_E30("ENG_CALL__Report_Process()");

	CI_FA_VARIABLE_CTRL *p_var_ctrl	= xFA_300mm_Link->Get_FA_VARIABLE_CTRL();

	if(p_var_ctrl != NULL)
	{
		CString main_name;
		CString sub_name;

		main_name = "ENG_CALL";
		sub_name  = "CALL_MSG";

		p_var_ctrl->Set_Variable(main_name,sub_name,call_msg);
	}
	//

	return p_e30_ctrl->Event__PROCESS_ENG_CALL();
}
