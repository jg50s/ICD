#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\EQP\Interface\OBJECT_INTERFACE.h"


#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\EQP_Link_Res\\EQP_Lib\\EQP__CTC_Link_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\EQP_Link_Res\\EQP_Lib\\EQP__CTC_Link_R.lib")
#endif


// ...
#define DEF__ENABLE							"ENABLE"

#define DEF__STANDBY						"STANDBY"
#define DEF__CTCINUSE						"CTCINUSE"
#define DEF__MAINTMODE						"MAINTMODE"

#define DEF__AVAILABLE						"AVAILABLE"
#define DEF__ABORTED						"ABORTED"


#define MODULE__IS_AVAILABLE(CLS,MODULE_NAME,CH_OBJ_STS,CH_OBJ_CTRL)					\
int  CLS::MODULE_NAME##__Is_Available()													\
{																						\
	CString obj_sts;																	\
	CString obj_ctrl;																	\
																						\
	CH_OBJ_STS->Get__DATA(obj_sts);														\
	CH_OBJ_CTRL->Get__DATA(obj_ctrl);													\
																						\
	if((obj_sts.CompareNoCase(DEF__STANDBY)  != 0)										\
	&& (obj_sts.CompareNoCase(DEF__CTCINUSE) != 0))										\
	{																					\
		return -1;																		\
	}																					\
																						\
	if((obj_ctrl.CompareNoCase(DEF__AVAILABLE) != 0)									\
	&& (obj_ctrl.CompareNoCase(DEF__ABORTED)   != 0))									\
	{																					\
		return -1;																		\
	}																					\
																						\
	return 1;																			\
}

#define MODULE__IS_AVAILABLE_WITH_USE(CLS,MODULE_NAME,CH_OBJ_STS,CH_OBJ_CTRL,CH_CFG_USE)	\
int  CLS::MODULE_NAME##__Is_Available()														\
{																							\
	CString cfg_use;																	\
	CString obj_sts;																	\
	CString obj_ctrl;																	\
																						\
	CH_CFG_USE->Get__DATA(cfg_use);														\
	CH_OBJ_STS->Get__DATA(obj_sts);														\
	CH_OBJ_CTRL->Get__DATA(obj_ctrl);													\
																						\
	if(cfg_use.CompareNoCase(DEF__ENABLE) != 0)											\
	{																					\
		return -1;																		\
	}																					\
																						\
	if((obj_sts.CompareNoCase(DEF__STANDBY)  != 0)										\
	&& (obj_sts.CompareNoCase(DEF__CTCINUSE) != 0))										\
	{																					\
		return -1;																		\
	}																					\
																						\
	if((obj_ctrl.CompareNoCase(DEF__AVAILABLE) != 0)									\
	&& (obj_ctrl.CompareNoCase(DEF__ABORTED)   != 0))									\
	{																					\
		return -1;																		\
	}																					\
																						\
	return 1;																			\
}

#define MODULE__IS_AVAILABLE_WITH_USE_INDEX(CLS,MODULE_NAME,INDEX,CH_OBJ_STS,CH_OBJ_CTRL,CH_CFG_USE)	\
int  CLS::MODULE_NAME##__Is_Available()													\
{																						\
	CString cfg_use;																	\
	CString obj_sts;																	\
	CString obj_ctrl;																	\
																						\
	CH_CFG_USE[INDEX]->Get__DATA(cfg_use);												\
	CH_OBJ_STS[INDEX]->Get__DATA(obj_sts);												\
	CH_OBJ_CTRL[INDEX]->Get__DATA(obj_ctrl);											\
																						\
	if(cfg_use.CompareNoCase(DEF__ENABLE) != 0)											\
	{																					\
		return -1;																		\
	}																					\
																						\
	if((obj_sts.CompareNoCase(DEF__STANDBY)  != 0)										\
	&& (obj_sts.CompareNoCase(DEF__CTCINUSE) != 0))										\
	{																					\
		return -1;																		\
	}																					\
																						\
	if((obj_ctrl.CompareNoCase(DEF__AVAILABLE) != 0)									\
	&& (obj_ctrl.CompareNoCase(DEF__ABORTED)   != 0))									\
	{																					\
		return -1;																		\
	}																					\
																						\
	return 1;																			\
}
#define MODULEx__IS_AVAILABLE_WITH_USE_INDEX(CLS,MODULE_NAME,CH_OBJ_STS,CH_OBJ_CTRL,CH_CFG_USE)		\
int  CLS::MODULE_NAME##__Is_Available(const int ll_i)									\
{																						\
	CString cfg_use;																	\
	CString obj_sts;																	\
	CString obj_ctrl;																	\
																						\
	CH_CFG_USE[ll_i]->Get__DATA(cfg_use);												\
	CH_OBJ_STS[ll_i]->Get__DATA(obj_sts);												\
	CH_OBJ_CTRL[ll_i]->Get__DATA(obj_ctrl);												\
																						\
	if(cfg_use.CompareNoCase(DEF__ENABLE) != 0)											\
	{																					\
		return -1;																		\
	}																					\
																						\
	if((obj_sts.CompareNoCase(DEF__STANDBY)  != 0)										\
	&& (obj_sts.CompareNoCase(DEF__CTCINUSE) != 0))										\
	{																					\
		return -1;																		\
	}																					\
																						\
	if((obj_ctrl.CompareNoCase(DEF__AVAILABLE) != 0)									\
	&& (obj_ctrl.CompareNoCase(DEF__ABORTED)   != 0))									\
	{																					\
		return -1;																		\
	}																					\
																						\
	return 1;																			\
}

#define MODULE__IS_IDLE(CLS,MODULE_NAME,CH_OBJ_STS,CH_OBJ_CTRL)							\
int  CLS::MODULE_NAME##__Is_Idle()														\
{																						\
	CString obj_sts;																	\
	CString obj_ctrl;																	\
																						\
	CH_OBJ_STS->Get__DATA(obj_sts);														\
	CH_OBJ_CTRL->Get__DATA(obj_ctrl);													\
																						\
	if((obj_sts.CompareNoCase(DEF__STANDBY)  != 0)										\
	&& (obj_sts.CompareNoCase(DEF__CTCINUSE) != 0))										\
	{																					\
		return -1;																		\
	}																					\
																						\
	if((obj_ctrl.CompareNoCase(DEF__AVAILABLE) != 0)									\
	&& (obj_ctrl.CompareNoCase(DEF__ABORTED)   != 0))									\
	{																					\
		return -1;																		\
	}																					\
																						\
	return 1;																			\
}

// ...
#define MODULEx__IS_AVAILABLE(CLS,MODULEx,CH_OBJ_STS,CH_OBJ_CTRL)						\
int  CLS::MODULEx##__Is_Available(const int db_i)										\
{																						\
	CString obj_sts;																	\
	CString obj_ctrl;																	\
																						\
	CH_OBJ_STS[db_i]->Get__DATA(obj_sts);												\
	CH_OBJ_CTRL[db_i]->Get__DATA(obj_ctrl);												\
																						\
	if((obj_sts.CompareNoCase(DEF__STANDBY)  != 0)										\
	&& (obj_sts.CompareNoCase(DEF__CTCINUSE) != 0))										\
	{																					\
		return -1;																		\
	}																					\
																						\
	if((obj_ctrl.CompareNoCase(DEF__AVAILABLE) != 0)									\
	&& (obj_ctrl.CompareNoCase(DEF__ABORTED)   != 0))									\
	{																					\
		return -1;																		\
	}																					\
																						\
	return 1;																			\
}

#define MODULEx__IS_AVAILABLE_EX(CLS,MODULEx,CH_OBJ_STS,CH_OBJ_CTRL,CH_CFG_USE)			\
int  CLS::MODULEx##__Is_Available(const int db_i)										\
{																						\
	CString cfg_use;																	\
	CString obj_sts;																	\
	CString obj_ctrl;																	\
																						\
	CH_CFG_USE[db_i]->Get__DATA(cfg_use);												\
	CH_OBJ_STS[db_i]->Get__DATA(obj_sts);												\
	CH_OBJ_CTRL[db_i]->Get__DATA(obj_ctrl);												\
																						\
	if(cfg_use.CompareNoCase(DEF__ENABLE) != 0)											\
	{																					\
		return -1;																		\
	}																					\
																						\
	if((obj_sts.CompareNoCase(DEF__STANDBY)  != 0)										\
	&& (obj_sts.CompareNoCase(DEF__CTCINUSE) != 0))										\
	{																					\
		return -1;																		\
	}																					\
																						\
	if((obj_ctrl.CompareNoCase(DEF__AVAILABLE) != 0)									\
	&& (obj_ctrl.CompareNoCase(DEF__ABORTED)   != 0))									\
	{																					\
		return -1;																		\
	}																					\
																						\
	return 1;																			\
}

#define MODULEx__IS_IDLE(CLS,MODULEx,CH_OBJ_STS,CH_OBJ_CTRL)							\
int  CLS::MODULEx##__Is_Idle(const int db_i)											\
{																						\
	CString obj_sts;																	\
	CString obj_ctrl;																	\
																						\
	CH_OBJ_STS[db_i]->Get__DATA(obj_sts);												\
	CH_OBJ_CTRL[db_i]->Get__DATA(obj_ctrl);												\
																						\
	if((obj_sts.CompareNoCase(DEF__STANDBY)  != 0)										\
	&& (obj_sts.CompareNoCase(DEF__CTCINUSE) != 0))										\
	{																					\
		return -1;																		\
	}																					\
																						\
	if((obj_ctrl.CompareNoCase(DEF__AVAILABLE) != 0)									\
	&& (obj_ctrl.CompareNoCase(DEF__ABORTED)   != 0))									\
	{																					\
		return -1;																		\
	}																					\
																						\
	return 1;																			\
}

#define MODULEx__IS_READY(CLS,MODULEx,CH_OBJ_STS,CH_CFG_USE,CH_PRC_STS)				    \
int  CLS::MODULEx##__Is_Ready(const int db_i)											\
{																						\
	CString cfg_use;																	\
	CString obj_sts;																	\
	CString prc_sts;																	\
																						\
	cfg_use = CH_CFG_USE[db_i]->Get__STRING();											\
	obj_sts = CH_OBJ_STS[db_i]->Get__STRING();											\
	prc_sts = CH_PRC_STS[db_i]->Get__STRING();											\
																						\
	if(cfg_use.CompareNoCase(DEF__ENABLE) != 0)											\
	{																					\
		return -1;																		\
	}																					\
																						\
	if((obj_sts.CompareNoCase(DEF__STANDBY)  != 0)										\
	&& (obj_sts.CompareNoCase(DEF__CTCINUSE) != 0))										\
	{																					\
		return -2;																		\
	}																					\
																						\
	if(obj_sts.CompareNoCase(DEF__CTCINUSE) == 0)										\
	{																					\
	    if(prc_sts.CompareNoCase(STR__ALARM) == 0)		return -3;						\
	}																					\
																						\
	return 1;																			\
}

// ...
#define MODULE__SET_OBJ_STATUS(CLS,MODULE_NAME,CH_OBJ_STS)								\
int  CLS::MODULE_NAME##__Set_Standby_To_CtcInUse()										\
{																						\
	if(CH_OBJ_STS->Check__DATA(DEF__STANDBY) < 0)		return -1;						\
																						\
	CH_OBJ_STS->Set__DATA(DEF__CTCINUSE);												\
	return 1;																			\
}																						\
int  CLS::MODULE_NAME##__Set_CtcInUse_To_Standby()										\
{																						\
	if(CH_OBJ_STS->Check__DATA(DEF__CTCINUSE) < 0)		return -1;						\
																						\
	CH_OBJ_STS->Set__DATA(DEF__STANDBY);												\
	return 1;																			\
}																						\
int  CLS::MODULE_NAME##__Check_CtcInUse_Or_Standby()									\
{																						\
	CString obj_sts;																	\
	CH_OBJ_STS->Get__DATA(obj_sts);														\
																						\
	if((obj_sts.CompareNoCase(DEF__STANDBY)  != 0)										\
	&& (obj_sts.CompareNoCase(DEF__CTCINUSE) != 0))										\
	{																					\
		return -1;																		\
	}																					\
	return 1;																			\
}																						\
int  CLS::MODULE_NAME##__Set_To_MaintMode()												\
{																						\
	CH_OBJ_STS->Set__DATA(DEF__MAINTMODE);												\
	return 1;																			\
}

#define MODULE__SET_OBJ_STATUS_WITH_INDEX(CLS,MODULE_NAME,INDEX,CH_OBJ_STS)				\
int  CLS::MODULE_NAME##__Set_Standby_To_CtcInUse()										\
{																						\
	if(CH_OBJ_STS[INDEX]->Check__DATA(DEF__STANDBY) < 0)		return -1;				\
																						\
	CH_OBJ_STS[INDEX]->Set__DATA(DEF__CTCINUSE);										\
	return 1;																			\
}																						\
int  CLS::MODULE_NAME##__Set_CtcInUse_To_Standby()										\
{																						\
	if(CH_OBJ_STS[INDEX]->Check__DATA(DEF__CTCINUSE) < 0)		return -1;				\
																						\
	CH_OBJ_STS[INDEX]->Set__DATA(DEF__STANDBY);											\
	return 1;																			\
}																						\
int  CLS::MODULE_NAME##__Check_CtcInUse_Or_Standby()									\
{																						\
	CString obj_sts;																	\
	CH_OBJ_STS[INDEX]->Get__DATA(obj_sts);												\
																						\
	if((obj_sts.CompareNoCase(DEF__STANDBY)  != 0)										\
	&& (obj_sts.CompareNoCase(DEF__CTCINUSE) != 0))										\
	{																					\
		return -1;																		\
	}																					\
	return 1;																			\
}																						\
int  CLS::MODULE_NAME##__Set_To_MaintMode()												\
{																						\
	CH_OBJ_STS[INDEX]->Set__DATA(DEF__MAINTMODE);										\
	return 1;																			\
}

#define MODULEx__SET_OBJ_STATUS_WITH_INDEX(CLS,MODULE_NAME,CH_OBJ_STS)					\
int  CLS::MODULE_NAME##__Set_Standby_To_CtcInUse(const int ll_i)						\
{																						\
	if(CH_OBJ_STS[ll_i]->Check__DATA(DEF__STANDBY) < 0)			return -1;				\
																						\
	CH_OBJ_STS[ll_i]->Set__DATA(DEF__CTCINUSE);											\
	return 1;																			\
}																						\
int  CLS::MODULE_NAME##__Set_CtcInUse_To_Standby(const int ll_i)						\
{																						\
	if(CH_OBJ_STS[ll_i]->Check__DATA(DEF__CTCINUSE) < 0)		return -1;				\
																						\
	CH_OBJ_STS[ll_i]->Set__DATA(DEF__STANDBY);											\
	return 1;																			\
}																						\
int  CLS::MODULE_NAME##__Check_CtcInUse_Or_Standby(const int ll_i)						\
{																						\
	CString obj_sts;																	\
	CH_OBJ_STS[ll_i]->Get__DATA(obj_sts);												\
																						\
	if((obj_sts.CompareNoCase(DEF__STANDBY)  != 0)										\
	&& (obj_sts.CompareNoCase(DEF__CTCINUSE) != 0))										\
	{																					\
		return -1;																		\
	}																					\
	return 1;																			\
}																						\
int  CLS::MODULE_NAME##__Set_To_MaintMode(const int ll_i)								\
{																						\
	CH_OBJ_STS[ll_i]->Set__DATA(DEF__MAINTMODE);										\
	return 1;																			\
}


// ...
#define MODULEx__SET_OBJ_STATUS(CLS,MODULEx,CH_OBJ_STS)									\
int  CLS::MODULEx##__Set_Standby_To_CtcInUse(const int db_i)							\
{																						\
	if(CH_OBJ_STS[db_i]->Check__DATA(DEF__STANDBY) < 0)		return -1;					\
																						\
	CH_OBJ_STS[db_i]->Set__DATA(DEF__CTCINUSE);											\
	return 1;																			\
}																						\
int  CLS::MODULEx##__Set_CtcInUse_To_Standby(const int db_i)							\
{																						\
	if(CH_OBJ_STS[db_i]->Check__DATA(DEF__CTCINUSE) < 0)	return -1;					\
																						\
	CH_OBJ_STS[db_i]->Set__DATA(DEF__STANDBY);											\
	return 1;																			\
}																						\
int  CLS::MODULEx##__Check_CtcInUse_Or_Standby(const int db_i)							\
{																						\
	CString obj_sts;																	\
	CH_OBJ_STS[db_i]->Get__DATA(obj_sts);												\
																						\
	if((obj_sts.CompareNoCase(DEF__STANDBY)  != 0)										\
	&& (obj_sts.CompareNoCase(DEF__CTCINUSE) != 0))										\
	{																					\
		return -1;																		\
	}																					\
																						\
	return 1;																			\
}

// ...
#define MODULE__IS_ATM(CLS,MODULE_NAME,CH_PRSS_STS)										\
int  CLS::MODULE_NAME##__Is_ATM()														\
{																						\
	if(CH_PRSS_STS->Check__DATA("ATM") < 0)			return -1;							\
																						\
	return 1;																			\
}
#define MODULE__IS_VAC(CLS,MODULE_NAME,CH_PRSS_STS)										\
int  CLS::MODULE_NAME##__Is_VAC()														\
{																						\
	if(CH_PRSS_STS->Check__DATA("VAC") < 0)			return -1;							\
																						\
	return 1;																			\
}

#define MODULE__IS_ATM_WITH_INDEX(CLS,MODULE_NAME,INDEX,CH_PRSS_STS)					\
int  CLS::MODULE_NAME##__Is_ATM()														\
{																						\
	if(CH_PRSS_STS[INDEX]->Check__DATA("ATM") < 0)			return -1;					\
																						\
	return 1;																			\
}
#define MODULE__IS_VAC_WITH_INDEX(CLS,MODULE_NAME,INDEX,CH_PRSS_STS)					\
int  CLS::MODULE_NAME##__Is_VAC()														\
{																						\
	if(CH_PRSS_STS[INDEX]->Check__DATA("VAC") < 0)			return -1;					\
																						\
	return 1;																			\
}

#define MODULEx__IS_ATM_WITH_INDEX(CLS,MODULE_NAME,CH_PRSS_STS)			        		\
int  CLS::MODULE_NAME##__Is_ATM(const int ll_i)									    	\
{																						\
	if(CH_PRSS_STS[ll_i]->Check__DATA("ATM") < 0)			return -1;					\
																						\
	return 1;																			\
}
#define MODULEx__IS_VAC_WITH_INDEX(CLS,MODULE_NAME,CH_PRSS_STS)				        	\
int  CLS::MODULE_NAME##__Is_VAC(const int ll_i)											\
{																						\
	if(CH_PRSS_STS[ll_i]->Check__DATA("VAC") < 0)			return -1;					\
																						\
	return 1;																			\
}

// ...
#define MODULEx__IS_ATM(CLS,MODULEx,CH_PRSS_STS)										\
int  CLS::MODULEx##__Is_ATM(const int db_i)												\
{																						\
	if(CH_PRSS_STS[db_i]->Check__DATA("ATM") < 0)			return -1;					\
																						\
	return 1;																			\
}
#define MODULEx__IS_VAC(CLS,MODULEx,CH_PRSS_STS)										\
int  CLS::MODULEx##__Is_VAC(const int db_i)												\
{																						\
	if(CH_PRSS_STS[db_i]->Check__DATA("VAC") < 0)			return -1;					\
																						\
	return 1;																			\
}


/*
// ...
#define MAKE__XCLS(XCLS,ICLS)										\
class XCLS															\
{																	\
private:															\
	ICLS *m_pT;														\
																	\
public:																\
	XCLS()															\
	{																\
		m_pT = NULL;												\
	}																\
	~XCLS()															\
	{																\
		if(m_pT != NULL)											\
		{															\
			delete m_pT;											\
		}															\
	}																\
																	\
	ICLS* operator->() const										\
	{																\
		return m_pT;												\
	}																\
	void Set__PTR(ICLS* p_ptr)										\
	{																\
		m_pT = p_ptr;												\
	}																\
	ICLS* Get__PTR()												\
	{																\
		return m_pT;												\
	}																\
};
*/


// ...
class SCI__Memory_Check__SC_Library__CTC_CTRL
{
public:
	virtual ~SCI__Memory_Check__SC_Library__CTC_CTRL(){};
	
	// ...
	virtual int Dump_To_File(const CString& path, const CString& log_title) = 0;

	// Core : DB_CTRL에서 제어 ...
	virtual int Clear__All_Memory_Info() = 0;
};

class SCI__Memory_Check__SC__NET_CTRL
{
public:
	virtual ~SCI__Memory_Check__SC__NET_CTRL(){};
	
	// ...
	virtual int Dump_To_File(const CString& path, const CString& log_title) = 0;
};

class SCI__Memory_Check__SC__DB_CTRL
{
public:
	virtual ~SCI__Memory_Check__SC__DB_CTRL(){};
	
	// ...
	virtual int Dump_To_File(const CString& path, const CString& log_title) = 0;
};


// ...
class SCI__CTC__CJOB_CTRL
{
public:
	virtual ~SCI__CTC__CJOB_CTRL(){};

	// ...
	virtual int Create__SERVICE_NAME(const CString& service_name) = 0;
	virtual int Link__SERVICE_NAME(const CString& service_name) = 0;
};


// ...
#define  MODULE_OBJ__AVAILABLE						 				 1
#define  MODULE_OBJ__ABORTED										-1
#define  MODULE_OBJ__OFFLINE										-2
#define  MODULE_OBJ__NOT_STANDBY									-3

#define  MODULE_OBJ__ERROR_TYPE__LINK_UPPER_OBJ						1
#define  MODULE_OBJ__ERROR_TYPE__LINK_OBJ_NAME						2
#define  MODULE_OBJ__ERROR_TYPE__MODULE_STATUS_CHANNEL				3
#define  MODULE_OBJ__ERROR_TYPE__MODULE_MODE_CHANNEL				4
#define  MODULE_OBJ__ERROR_TYPE__MODULE_CTRL_CHANNEL				5
#define  MODULE_OBJ__ERROR_TYPE__CONNECT_MODULE_OBJ				    6
#define  MODULE_OBJ__ERROR_TYPE__NOT_DEFINED_IN_MODULE_OBJ			7


class CII__ERROR_FEEDBACK__MODULE_OBJ
{
public:
	virtual ~CII__ERROR_FEEDBACK__MODULE_OBJ() { };

	// ...
	virtual int Call__ERROR__MODULE_OBJ(const CString& upper_obj,
										const CString& ch_ctrl,
										const CString& ch_mode,
										const CString& ch_status,
										const int err_type,
										const CString& err_msg,
										CII_OBJECT__ALARM *p_alarm) = 0;

	// ...
	virtual int Call__ERROR__ABORTED(const CString& upper_obj,
									 const CString& obj_mode,
									 CII_OBJECT__ALARM *p_alarm) = 0;

	virtual int Call__ERROR__OFFLINE(const CString& upper_obj,
									 const CString& obj_mode,
									 CII_OBJECT__ALARM *p_alarm) = 0;

	virtual int Call__ERROR__NOT_STANDBY(const CString& upper_obj,
										 const CString& obj_mode,
										 CII_OBJECT__ALARM *p_alarm) = 0;
};

class CII__COMMON_CODE__ERROR_FEEDBACK__MODULE_OBJ : public CII__ERROR_FEEDBACK__MODULE_OBJ
{
public:
	virtual ~CII__COMMON_CODE__ERROR_FEEDBACK__MODULE_OBJ() { };
	
	// ...
	virtual int Set__Object_Name(const CString& obj_name) = 0;
	virtual int Define__AlarmID(CII_DEFINE__ALARM* p_alarm, const CString& alarm_title) = 0;
};

class SCI__CTC__MODULE_OBJ
{
public:
	virtual ~SCI__CTC__MODULE_OBJ(){};

	// ...
	virtual int Link__Object_Name(const CString& obj_name) = 0;

	virtual int Register__Module_Status_Channel(const CString& var_name) = 0;
	virtual int Register__Module_Mode_Channel(const CString& var_name)   = 0;
	virtual int Register__Module_Ctrl_Channel(const CString& var_name)   = 0;

	virtual int Connect__Module_Obj(const CString& mode) = 0;	
	virtual int Abort__Module_Obj() = 0;


	// ...
	virtual int Link__ERROR_FEEDBACK(CII__ERROR_FEEDBACK__MODULE_OBJ* p_error) = 0;

	virtual int Disable__ERROR_CHECK__NOT_STANDBY() = 0;
	virtual int Enable__ERROR_CHECK__NOT_STANDBY() = 0;

	virtual int Disable__CTCINUSE_TO_STANDBY() = 0;

	virtual int Disable__REPORT_ABORTED_ALARM() = 0;
	virtual int Enable__REPORT_ABORTED_ALARM() = 0;		// Default

	virtual int Disable__STANDBY_TO_CTCINUSE() = 0;
};


// ...
#define  CSS_FILE__SLOT_ERROR__PPID_EMPTY			1
#define  CSS_FILE__SLOT_ERROR__ROUTE_NoEXIST		2


class SCI__CTC__JOB_FILE_CTRL
{
public:
	virtual ~SCI__CTC__JOB_FILE_CTRL(){};

	// ...
	virtual int  Link__Material_DB(const CString& service_name) = 0;

	//
	virtual int  Upload__JOB_FILE(const CString& dir,
							      const CString& port,
							      const CString& file) = 0;

	virtual void Check__DB() = 0;
	virtual void Get__PRC_MODULE(CStringArray& l_module) = 0;

	//
	virtual void Copy__TO_MATERIAL(const CString& job_name) = 0;

	virtual void Get__SLOT_ERROR_INFO(CUIntArray&   l_slot_err_id,
									  CStringArray& l_slot_err_msg) = 0;

	virtual void Get__PRC_RECIPE(CStringArray& l_module,
								 CStringArray& l_recipe) = 0;

	virtual void Get__SLOT_NUM_LIST(CStringArray& l_slot_num) = 0;

	virtual void Copy__TO_MATERIAL_EX(const int src_ptn,
									  const int trg_ptn,
									  const CString& job_name) = 0;

	virtual void Change__OCR_INFO(const CStringArray& l_ocr_info) = 0;
	virtual void Set__TOP_DOWN() = 0;

	virtual void Copy__TO_MATERIAL_WITH_SLOT_LIST(const int src_ptn,
												  const int trg_ptn,
												  const CUIntArray& l_slot_id,
												  const CString& job_name) = 0;

	virtual void Register__PROCESS_MODULE(const CString& module_name) = 0;
	virtual void Register__ALL_MODULE() = 0;

	virtual int  Get__ALL_PPID_LIST(CStringArray& l_ppid) = 0;

	virtual int  Enable__LOTID_AUTO_DEFINE()  = 0;
	virtual int  Disable__LOTID_AUTO_DEFINE() = 0;

	virtual void Copy__TO_MATERIAL_WITH_CSTID(const CString& job_name,
											  const CString& cstid) = 0;

	virtual void Copy__TO_MATERIAL_WITH_SRC_MODULE(const CString& job_name,
												   const CString& src_module) = 0;

	virtual void Set__JOB_TYPE__SINGLE_MATERIAL() = 0;
	virtual void Set__JOB_TYPE__MULTI_MATERIAL()  = 0;

	virtual int  Get__LOTID_PPID_OF_FIRST_DB(CString& str_lotid,
											 CString& str_ppid) = 0;

	virtual void Get__ALL_BUFFERx_INFO(CStringArray& l_slot,
									   CStringArray& l_bff1,
									   CStringArray& l_bff2) = 0;

	// For New Route Recipe ...
	virtual int  Upload__JOB_FILE_FOR_NEW_ROUTE_RECIPE(const CString& dir,
										               const CString& port,
										               const CString& file) = 0;


	// Recipe Info Of Route Edit Type ...
	virtual int  Get__SLOTID_OF_EDIT_TYPE(CUIntArray& l_slotid) = 0;

	virtual int  Check__ROUTE_EDIT_TYPE() = 0;
	virtual int  Check__ROUTE_EDIT_TYPE(const int slot_id) = 0;
	virtual int  Get__ALx_OF_EDIT_TYPE(const int slot_id,
									   CStringArray& l_id,
								       CStringArray& l_mode,
									   CStringArray& l_slot) = 0;	
	virtual int  Get__LLx_IN_OF_EDIT_TYPE(const int slot_id,
										  CStringArray& l_id,
										  CStringArray& l_mode,
										  CStringArray& l_slot) = 0;
	virtual int  Get__LLx_OUT_OF_EDIT_TYPE(const int slot_id,
										   CStringArray& l_id,
										   CStringArray& l_mode,
										   CStringArray& l_slot) = 0;
	virtual int  Get__STx_OF_EDIT_TYPE(const int slot_id,
									   CStringArray& l_id,
									   CStringArray& l_mode,
									   CStringArray& l_slot,
									   CStringArray& l_sec) = 0;

	//
	virtual void Get__PRC_MODULE_OF_FIRST_PATH(CStringArray& l_pmx) = 0;
	virtual int  Get__PRC_PATH_SIZE() = 0;

	//
	virtual int  Get__STx_N2_PURGE_OF_EDIT_TYPE(const int slot_id,
											    CStringArray& l_id,
											    CStringArray& l_mode,
											    CStringArray& l_slot,
											    CStringArray& l_sec,
											    CStringArray& l_n2_purge) = 0;
};


// ...
class IDS__SCH_MATERIAL_STATUS
{
public:
	int iPORT_ID;
	int iSLOT_ID;
	CString sMATERIAL_POS;
	CString sMATERIAL_STS;
};
class IDS__SCH_MATERIAL_INFO
{
public:
	int iSRC__PTN;
	int iSRC__STN;
	int iTRG__PTN;
	int iTRG__STN;

	//
	CString sCUR_RECIPE;
	CString sLOT_ID;
	CString sMATERIAL_ID;
	CString sPPID;
	CString sMATERIAL_TYPE;

	int     iVISION_VISIT;
	CString sVISION_RCP;

	CString sOCR_SCRIBE;		
};
class IDS__SCH_DB_INFO
{
public:
	IDS__SCH_DB_INFO()
	{
		iSRC__PTN = -1;
		iSRC__STN = -1;
		iTRG__PTN = -1;
		iTRG__STN = -1;
	
		sJOB_NAME = "";
		sLOT_ID = "";
		sMATERIAL_ID = "";
		sPPID = "";
		sMATERIAL_TYPE = "";

		iVISION_VISIT = -1;
		sVISION_RCP = "";

		sOCR_SCRIBE = "";
		sLIST_PRC_MODULE.RemoveAll();
		sLIST_PRC_RECIPE.RemoveAll();
	}

	// ...
	int iSRC__PTN;
	int iSRC__STN;
	int iTRG__PTN;
	int iTRG__STN;
	
	//
	CString sJOB_NAME;
	CString sLOT_ID;
	CString sMATERIAL_ID;
	CString sPPID;
	CString sMATERIAL_TYPE;

	int iVISION_VISIT;
	CString sVISION_RCP;

	CString sOCR_SCRIBE;
	CStringArray sLIST_PRC_MODULE;
	CStringArray sLIST_PRC_RECIPE;
};
class IDS__SCH_DB_ROUTE_INFO
{
public:
	IDS__SCH_DB_ROUTE_INFO()
	{
		sLIST_PRC_MODULE.RemoveAll();
		sLIST_PRC_RECIPE.RemoveAll();
		
		sLIST_PRC_SUB_RCP1.RemoveAll();
		sLIST_PRC_SUB_RCP2.RemoveAll();
		sLIST_PRC_SUB_RCP3.RemoveAll();
		sLIST_PRC_SUB_RCP4.RemoveAll();
		sLIST_PRC_SUB_RCP5.RemoveAll();
	}

	// ...
	CStringArray sLIST_PRC_MODULE;
	CStringArray sLIST_PRC_RECIPE;

	CStringArray sLIST_PRC_SUB_RCP1;
	CStringArray sLIST_PRC_SUB_RCP2;
	CStringArray sLIST_PRC_SUB_RCP3;
	CStringArray sLIST_PRC_SUB_RCP4;
	CStringArray sLIST_PRC_SUB_RCP5;
};
class IDS__JOB_INFO
{
public:
	IDS__JOB_INFO()
	{
		sJOB_ID = "";
		sLOT_ID = "";
		sGLS_ID = "";

		iPORT_ID = -1;
		iSLOT_ID = -1;
	}

	// ...
	CString sJOB_ID;
	CString sLOT_ID;
	CString sGLS_ID;

	int iPORT_ID;
	int iSLOT_ID;
};

class IDS_SAMSUNG_STD_LOG__LEH
{
public:
	IDS_SAMSUNG_STD_LOG__LEH(){};

	// ...
	int iPortID;
	CString sEventID;
	CString sLotID;
	CString sFlow_RecipeID;
	CString sFlow_Info;
	CString sCarrierID;

	CStringArray sList_Key;
	CStringArray sList_Value;
};
class IDS_SAMSUNG_STD_LOG__XFR
{
public:
	IDS_SAMSUNG_STD_LOG__XFR(){};

	// ...
	CString sDeviceID;
	CString sEventID;
	CString sMaterialID;
	CString sMaterialType;	
	CString sFromDevice;
	CString sFromSlot;
	CString sToDevice;
	CString sToSlot;

	CStringArray sList_Key;
	CStringArray sList_Value;
};
class IDS_SAMSUNG_STD_LOG__PRC
{
public:
	IDS_SAMSUNG_STD_LOG__PRC(){};

	// ...
	CString sDeviceID;
	CString sEventID;
	CString sMaterialID;
	CString sSlotID;
	CString sLotID;
	CString sRecipeID;
	CString sStepNum;

	CStringArray sList_Key;
	CStringArray sList_Value;
};
class IDS_SAMSUNG_STD_LOG__FNC
{
public:
	IDS_SAMSUNG_STD_LOG__FNC(){};

	// ...
	CString sDeviceID;
	CString sEventID;
	CString sMaterialID;
	CString sMaterialType;
	
	CStringArray sList_Key;
	CStringArray sList_Value;
};


class SCI__CTC__SCH_MATERIAL_CTRL
{
public:
	virtual ~SCI__CTC__SCH_MATERIAL_CTRL(){};

	// ...
	virtual int  Create__SERVICE_DB(const CString& service_name) = 0;
	virtual int  Link__SERVICE_DB(const CString& service_name)   = 0;

	virtual int  Define__ROBOT_NAME(const CString& robot_name) = 0;
	virtual int  Define__ROBOT_ARM(const CString& arm_type) = 0;

	//
	virtual int  Lock__MATERIAL_DB() = 0;
	virtual int  Unlock__MATERIAL_DB() = 0;

	virtual int  Get__MATERIAL_DB_SIZE() = 0;

	virtual int  Get__LPx_SLOT_LIST(const int port_id,CStringArray& l_slot) = 0;
	virtual int  Check__LPx_COMPLETE(const int port_id) = 0;
	virtual int  Check__MATERIAL_TO_PROCESS() = 0;
	virtual int  Check__MATERIAL_LESS_THAN_MOVE_COUNT(const int move_count) = 0;

	virtual int  Get__MATERIAL_FROM_LPx(int& port_id,int& slot_id) = 0;					// *

	virtual int  Get__MATERIAL_STATUS(const int port_id,const int slot_id,				// *
									  IDS__SCH_MATERIAL_STATUS& ds_status) = 0;
	virtual int  Get__MATERIAL_STATUS(const CString& material_pos,
									  IDS__SCH_MATERIAL_STATUS& ds_status) = 0;			// *

	virtual int  Get__MATERIAL_INFO(const int port_id,const int slot_id,				// *
									IDS__SCH_MATERIAL_INFO& ds_info) = 0;
	virtual int  Get__MATERIAL_INFO(const CString& material_pos,						// *
									IDS__SCH_MATERIAL_INFO& db_info) = 0;

	virtual int  Get__CUR_PROCESS_INFO(const int port_id,const int slot_id,				// *
									   CStringArray& l_prc_module,
									   CStringArray& l_prc_recipe) = 0;
	virtual int  Get__CUR_PROCESS_INFO(const CString& material_pos,						// *
									   CStringArray& l_prc_module,
									   CStringArray& l_prc_recipe) = 0;

	virtual int  Goto__NEXT_PROCESS(const int port_id,const int slot_id) = 0;			// *
	virtual int  Goto__NEXT_PROCESS(const CString& material_pos) = 0;					// *

	virtual int  Get__TARGET_LPx_INFO(const int port_id,const int slot_id,
									  int& trg_port_id,int& trg_slot_id) = 0;
	virtual int  Get__TARGET_LPx_INFO(const CString& material_pos,
									  int& trg_port_id,int& trg_slot_id) = 0;


	// 
	virtual int  Pick__From_LPx(const int port_id,const int slot_id,
								const CString& robot_pos) = 0;
	virtual int  Place__To_LPx(const CString& robot_pos,
							   const CString& module_pos) = 0;
	
	virtual int  Pick__From_MODULE(const int& port_id,const int& slot_id,
								   const CString& robot_pos) = 0;
	virtual int  Pick__From_MODULE(const CString& module_pos,
								   const CString& robot_pos) = 0;

	virtual int  Place__To_MODULE(const int port_id,const int slot_id,
								  const CString& module_pos) = 0;
	virtual int  Place__To_MODULE(const CString& robot_pos,
								  const CString& module_pos) = 0;

	virtual int  Set__MATERIAL_STATUS(const int port_id,const int slot_id,
									  const CString& status) = 0;
	virtual int  Set__MATERIAL_STATUS(const CString& material_pos,
									  const CString& status) = 0;

	virtual int  Set__CURRENT_RECIPE(const int port_id,const int slot_id,
									 const CString& recipe) = 0;
	virtual int  Set__CURRENT_RECIPE(const CString& material_pos,
									 const CString& recipe) = 0;

	//
	virtual int  Clear__MATERIAL_INFO(const int port_id,const int slot_id) = 0;
	virtual int  Clear__MATERIAL_INFO(const CString& material_pos) = 0;

	virtual int  Clear__ALL_MATERIAL_INFO() = 0;

	//
	virtual int  End__PORT_ID(const int port_id) = 0;
	virtual int  Pause__PORT_ID(const int port_id) = 0;
	virtual int  Resume__PORT_ID(const int port_id) = 0;

	virtual int  End__JOB_NAME(const CString& job_name) = 0;
	virtual int  End__LOT_NAME(const CString& lot_name) = 0;

	virtual int  End__ALL_PORT() = 0;
	virtual int  Pause__ALL_PORT() = 0;
	virtual int  Abort__ALL_PORT() = 0;

	//
	virtual int  Set__SYSTEM_START() = 0;

	virtual int  Set__SYSTEM_PAUSE() = 0;
	virtual int  Set__SYSTEM_STOP()  = 0;
	virtual int  Set__SYSTEM_ABORT() = 0;

	virtual int  Check__SYSTEM_PAUSE() = 0;
	virtual int  Check__SYSTEM_STOP()  = 0;
	virtual int  Check__SYSTEM_ABORT() = 0;

	//
	virtual int  Set__ROBOT_BUSY(const CString& robot_name) = 0;
	virtual int  Set__ROBOT_IDLE(const CString& robot_name) = 0;

	virtual int  Check__ROBOT_IDLE() = 0;

	// ...
	virtual int  Init__PROCESS_MODULE() = 0;
	virtual int  Define__PROCESS_MODULE(const CString& prc_module) = 0;

	virtual int  Init__IN_MODULE() = 0;
	virtual int  Define__IN_MODULE(const CString& in_module) = 0;
	
	virtual int  Init__OUT_MODULE() = 0;
	virtual int  Define__OUT_MODULE(const CString& out_module) = 0;

	//
	virtual int  Get__VISIT_MODULE(const int port_id,const int slot_id,
								   CStringArray& l_visit_module) = 0;
	virtual int  Get__VISIT_MODULE(const CString& material_pos,
								   CStringArray& l_visit_module) = 0;

	virtual int  Get__VISIT_MODULE_And_PRC_RECIPE(const int port_id,const int slot_id,
												  CStringArray& l_visit_module,
												  CStringArray& l_prc_recipe) = 0;
	virtual int  Get__VISIT_MODULE_And_PRC_RECIPE(const CString& material_pos,
												  CStringArray& l_visit_module,
												  CStringArray& l_prc_recipe) = 0;

	// ...
	virtual int  Init__MATERIAL_PICK_COUNT()  = 0;
	virtual int  Init__MATERIAL_PLACE_COUNT() = 0;

	virtual int  Add__MATERIAL_PICK_COUNT( const int count = 1) = 0;
	virtual int  Add__MATERIAL_PLACE_COUNT(const int count = 1) = 0;

	virtual int  Get__MATERIAL_PICK_COUNT()  = 0;
	virtual int  Get__MATERIAL_PLACE_COUNT() = 0;

	virtual void Check__RCP_DB() = 0;
	virtual void Check__STS_DB() = 0;

	virtual int  Set__PMx_FRONT_TIME(const double sec) = 0;
	virtual double Get__PMx_FRONT_TIME() = 0;

	//
	virtual int  Set__SCH_MODE__SEQUENTIAL() = 0;
	virtual int  Set__SCH_MODE__PIPELINE()   = 0;
	virtual int  Set__SCH_MODE__CONCURRENT() = 0;

	virtual int  Check__SCH_MODE__SEQUENTIAL() = 0;
	virtual int  Check__SCH_MODE__PIPELINE()   = 0;
	virtual int  Check__SCH_MODE__CONCURRENT() = 0;

	//
	virtual int  Can_Upload__NEXT_PORT() = 0;
	virtual int  Check__MATERIAL_MORE_THAN_MOVE_COUNT(const int move_count) = 0;

	virtual int  Set__JOB_PORT(const int ptn) = 0;
	virtual int  Get__JOB_PORT_LIST(CUIntArray& l_ptn) = 0;

	//
	virtual int  Clear__PORT_RESERVE() = 0;
	virtual int  Set__PORT_RESERVE(const int ptn) = 0;
	virtual int  Set__PORT_RESERVE_LIST(const CUIntArray& l_ptn) = 0;
	virtual int  Get__PORT_RESERVE_LIST(CUIntArray& l_ptn) = 0;

	//
	virtual int  Get__ALL_PRC_MODULE(CStringArray& l_module) = 0;
	virtual int  Get__PORT_FIRST_SLOT_INFO(const int ptn,
										   IDS__SCH_MATERIAL_INFO& ds_info) = 0;

	//
	virtual int  Register__SYSTEM_NAME(const CString& sys_name) = 0;
	virtual int  Get__SYSTEM_LIST(CStringArray& l_sys_name) = 0;

	virtual int  Check__SYSTEM_STATUS__ALARM() = 0;
	virtual int  Set__SYSTEM_STATUS__ALARM(const CString& sys_name)   = 0;
	virtual int  Clear__SYSTEM_STATUS__ALARM(const CString& sys_name) = 0;

	virtual int  Check__SYSTEM_STATUS__MAINT() = 0;
	virtual int  Set__SYSTEM_STATUS__MAINT(const CString& sys_name)   = 0;
	virtual int  Clear__SYSTEM_STATUS__MAINT(const CString& sys_name) = 0;

	virtual int  Check__SYSTEM_STATUS__LOAD_REQ() = 0;
	virtual int  Set__SYSTEM_STATUS__LOAD_REQ(const CString& sys_name)   = 0;
	virtual int  Clear__SYSTEM_STATUS__LOAD_REQ(const CString& sys_name) = 0;

	virtual int  Check__SYSTEM_STATUS__UNLOAD_REQ() = 0;
	virtual int  Set__SYSTEM_STATUS__UNLOAD_REQ(const CString& sys_name)   = 0;
	virtual int  Clear__SYSTEM_STATUS__UNLOAD_REQ(const CString& sys_name) = 0;

	virtual int  Check__SYSTEM_STATUS__PROCESS() = 0;
	virtual int  Set__SYSTEM_STATUS__PROCESS(const CString& sys_name)   = 0;
	virtual int  Clear__SYSTEM_STATUS__PROCESS(const CString& sys_name) = 0;

	virtual int  Get__FA_STATUS() = 0;
	virtual int  Set__FA_STATUS__NOT_ESTABLISHED() = 0;
	virtual int  Set__FA_STATUS__OFFLINE() = 0;
	virtual int  Set__FA_STATUS__LOCAL()   = 0;
	virtual int  Set__FA_STATUS__REMOTE()  = 0;

	virtual int  Check__SYSTEM_STATUS__MATERIAL_STS(const CString& sys_name,
											        CStringArray& l_pos,
										            CUIntArray&   l_sts) = 0;
	virtual int  Set__SYSTEM_STATUS__MATERIAL_STS(const CString& sys_name,
												  const CString& material_pos) = 0;
	virtual int  Clear__SYSTEM_STATUS__MATERIAL_STS(const CString& sys_name,
												    const CString& material_pos) = 0;

	virtual int  Check__SYSTEM_STATUS__PMC_STS(const CString& sys_name,
											   CStringArray& l_pmc_name,
											   CUIntArray&   l_pmc_sts) = 0;
	virtual int  Set__SYSTEM_STATUS__PMC_STS(const CString& sys_name,
											 const CString& pmc_name) = 0;
	virtual int  Clear__SYSTEM_STATUS__PMC_STS(const CString& sys_name,
											   const CString& pmc_name) = 0;

	//
	virtual int  Change__VISION_RECIPE(const int ptn,const CString& vis_rcp) = 0;
	virtual int  Change__VISION_VISIT_SLOT(const int ptn,
										   const CUIntArray& l_slot_id,
										   const CUIntArray& l_slot_sts) = 0;

	//
	virtual int  Check__VIS_INFO__CFG_MODE() = 0;
	virtual int  Set__VIS_INFO__CFG_MODE() = 0;
	virtual int  Clear__VIS_INFO__CFG_MODE() = 0;

	virtual int  Check__VIS_INFO__CFG_VISIT() = 0;
	virtual int  Set__VIS_INFO__CFG_VISIT() = 0;
	virtual int  Clear__VIS_INFO__CFG_VISIT() = 0;

	virtual int  Set__VIS_INFO__CFG_RECIPE_NAME(const CString& rcp_name) = 0;
	virtual int  Get__VIS_INFO__CFG_RECIPE_NAME(CString& rcp_name) = 0;

	virtual int  Set__VIS_INFO__CFG_VISIT_SLOT(const CUIntArray& l_slot_id,
											   const CUIntArray& l_slot_sts) = 0;
	virtual int  Get__VIS_INFO__CFG_VISIT_SLOT(CUIntArray& l_slot_id,
											   CUIntArray& l_slot_sts) = 0;

	//
	virtual int  Check__DISABLE_PORT(const int ptn) = 0;
	virtual int  Check__DUMMY_PORT(const int ptn)   = 0;
	virtual int  Check__PROCESS_PORT(const int ptn) = 0;

	virtual int  Set__DISABLE_PORT(const int ptn) = 0;
	virtual int  Set__DUMMY_PORT(const int ptn)   = 0;
	virtual int  Set__PROCESS_PORT(const int ptn) = 0;

	virtual int  Get__DUMMY_PORT(int& ptn) = 0;
	virtual int  Get__DUMMY_PORT_LIST(CUIntArray& l_ptn) = 0;

	virtual int  Get__PORT_SLOT_MAX(const int ptn,int& slot_max) = 0;
	virtual int  Set__PORT_SLOT_MAX(const int ptn,const int slot_max) = 0;

	virtual int  Get__PORT_SLOT_STS(const int ptn,CUIntArray& l_slot_sts) = 0;
	virtual int  Set__PORT_SLOT_STS(const int ptn,const CUIntArray& l_slot_sts) = 0;

	//
	virtual int  Check__SYSTEM_STATUS__MODULE_STS(const CString& sys_name,
											      CStringArray& l_module_name,
										          CUIntArray&   l_module_sts) = 0;

	virtual int  Set__SYSTEM_STATUS__MODULE_AVAILABLE(const CString& sys_name,
												      const CString& module_name) = 0;
	virtual int  Set__SYSTEM_STATUS__MODULE_NOT_AVAILABLE(const CString& sys_name,
												          const CString& module_name) = 0;
	virtual int  Set__SYSTEM_STATUS__MODULE_DISABLE(const CString& sys_name,
												    const CString& module_name) = 0;

	// ...
	virtual int  Load__SCH_INFO_At_First_SCH_DB(const IDS__SCH_DB_INFO& db_info) = 0;
	virtual int  Change__LOTID(const int ptn,const CString& lotid) = 0;

	virtual int  Set__FA_REMOTE_VERSION() = 0;

	virtual int  Transfer_Start__To_MODULE(const CString& cur_pos,const CString& to_module) = 0;

	virtual int  Process_Start__PMC(const CString& cur_pos,const int pmc_id,const CString& recipe) = 0;
	virtual int  Process_End__PMC(const CString& cur_pos,const int pmc_id) = 0;

	virtual int  Set__LBx_SCH_MODE__STATUS_ERROR(const CString& err_msg) = 0;
	virtual int  Clear__LBx_SCH_MODE__STATUS_ERROR() = 0;
	
	virtual int  Check__LBx_SCH_MODE__STATUS_ERROR(CString& err_msg) = 0;
	
	virtual int  Clear__PROCESS_INFO(const int port_id,const int slot_id) = 0;
	virtual int  Clear__PROCESS_INFO(const CString& material_pos) = 0;

	virtual int  Check__NEXT_PROCESS(const int portid,const int slot_id) = 0;
	virtual int  Check__NEXT_PROCESS(const CString& material_pos) = 0;

	virtual int  Set__ALL_PMx_GoTo_MAINT() = 0;
	virtual int  Set__PMx_GoTo_MAINT(const int pm_id) = 0;
	virtual int  Clear__PMx_GoTo_MAINT(const int& pm_id) = 0;

	virtual int  Check__PMx_GoTo_MAINT(const int& pm_id) = 0;

	virtual int  Step_Start__PMC(const CString& cur_pos,const int pmc_id) = 0;
	virtual int  Step_End__PMC(const CString& cur_pos,const int pmc_id) = 0;
	virtual int  Step_Data_Report__PMC(const CString& cur_pos,const int pmc_id) = 0;

	virtual int  RMS__Report_PP_CREATE(const CString& pp_name) = 0;
	virtual int  RMS__Report_PP_UPDATE(const CString& pp_name) = 0;
	virtual int  RMS__Report_PP_DELETE(const CString& pp_name) = 0;

	virtual int  RMS__Report_SUCCESSFUL_UPLOAD() = 0;
	virtual int  RMS__Report_BAD_UPLOAD() = 0;

	virtual int  Clear__LPx_MATERIAL_INFO(const int port_id) = 0;

	virtual int  Set__LPx_CID(const int port_id,const CString& cid) = 0;
	virtual int  Get__LPx_CID(const int port_id,CString& cid) = 0;
	virtual int  Check__LPx_CID(const int port_id,const CString& cid) = 0;

	virtual int  Report__VIS_PROC_START(const int vis_id) = 0;
	virtual int  Report__VIS_PROC_END(const int vis_id) = 0;

	virtual int  Clean_Start__PMC(const int pmc_id) = 0;
	virtual int  Clean_End__PMC(const int pmc_id) = 0;

	virtual int  LeakCheck_Start__PMC(const int pmc_id) = 0;
	virtual int  LeakCheck_End__PMC(const int pmc_id) = 0;

	virtual int  End__ALL_PORT__WITH_EVENT_SLOT() = 0;
	virtual int  Mix__MATERIAL_DB_WITH_LPx(const int first_ptn,const int second_ptn) = 0;

	virtual int  Get__FIRST_MATERIAL_INFO(int& port_id,int& slot_id) = 0;

	virtual int  Set__ECS_MODE(const CString& ecs_mode) = 0;
	virtual int  Get__ECS_MODE(CString& ecs_mode) = 0;

	virtual int  Load__SCH_INFO_At_Last_SCH_DB(const IDS__SCH_DB_INFO& db_info) = 0;
	virtual int  Set__MATERIAL_POSITION(const int port_id,const int slot_id,
									    const CString& pos_name) = 0;

	virtual int  Get__MATERIAL_FROM_LPx_WITH_MULTI_SLOT(int& port_id,
														CUIntArray& l_slot_id,
														const int list_size) = 0;

	virtual int  Get__MATERIAL_FROM_LPx_WITH_MULTI_SLOT_EX(CUIntArray& l_port_id,
														   CUIntArray& l_slot_id,
														   const int list_size) = 0;

	virtual int  Get__CUR_PROCESS_INFO_EX(const int port_id,const int slot_id,
									      CStringArray& l_prc_module,
									      CStringArray& l_prc_recipe,
										  CStringArray& l_stage_info) = 0;
	virtual int  Get__CUR_PROCESS_INFO_EX(const CString& material_pos,
									      CStringArray& l_prc_module,
									      CStringArray& l_prc_recipe,
										  CStringArray& l_stage_info) = 0;

	virtual int  Set__MATERIAL_USER_INFO(const int port_id,const int slot_id,
										 const CString& def_name,
										 const CString& def_data) = 0;
	virtual int  Set__MATERIAL_USER_INFO(const CString& material_pos,
										 const CString& def_name,
										 const CString& def_data) = 0;

	virtual int  Get__MATERIAL_USER_INFO(const int port_id,const int slot_id,
										 const CString& def_name,
										 CString& def_data) = 0;
	virtual int  Get__MATERIAL_USER_INFO(const CString& material_pos,
										 const CString& def_name,
										 CString& def_data) = 0;

	virtual int  End__PTN_And_SLOTID(const int port_id,const int slot_id) = 0;

	virtual int  Register__SYSTEM_NAME_EX(const CString& sys_name,
										  const int atm_area_flag) = 0;

	virtual int  Get__ATM_AREA__SYSTEM_LIST(CStringArray& l_sys_name) = 0;
	virtual int  Get__VAC_AREA__SYSTEM_LIST(CStringArray& l_sys_name) = 0;

	virtual int  Get__PMC_INFO_IN_SYSTEM(const CStringArray& l_module_name,CStringArray& l_pmc_info) = 0;
	virtual int  Get__ALL_PPID_LIST(CStringArray& l_ppid) = 0;

	
	virtual int  Start__JOB(const int port_id,
		                    const CStringArray& l_slot_id,
							const CString& cst_id) = 0;
	
	virtual int  Complete__JOB(const int port_id) = 0;
	virtual int  Complete__JOB(const int port_id,const int slot_id) = 0;

	virtual int  Abort__JOB(const int port_id) = 0;
	virtual int  Abort__JOB(const int port_id,const int slot_id) = 0;

	virtual int  Clear__JOB(const int port_id) = 0;
	virtual int  Clear__JOB(const int port_id,const int slot_id) = 0;

	//
	virtual int  Get__CARRIERID_LIST(CStringArray& l_carrierid) = 0;
	virtual int  Get__LOTID_LIST(CStringArray& l_lotid) = 0;
	virtual int  Get__JOBID_LIST(CStringArray& l_jobid) = 0;

	virtual int  Check__CARRIERID(const CString& carrierid) = 0;
	virtual int  Check__LOTID(const CString& lotid) = 0;
	virtual int  Check__JOBID(const CString& jobid) = 0;

	//
	virtual int  CARRIERID__Get_ALL_MATERIAL(const CString& cstid,
											 CStringArray& l_portid,
											 CStringArray& l_slotid) = 0;
	virtual int  LOTID__Get_ALL_MATERIAL(const CString& lotid,
										 CStringArray& l_portid,
										 CStringArray& l_slotid) = 0;
	virtual int  JOBID__Get_ALL_MATERIAL(const CString& jobid,
										 CStringArray& l_portid,
										 CStringArray& l_slotid) = 0;

	virtual int  MATERIAL_INFO__Get_PROC_INFO(const int port_id,
											  const int slot_id,
											  CStringArray& l_proc_module_name,
											  CStringArray& l_proc_recipe_name,
											  CStringArray& l_proc_start_time,
											  CStringArray& l_proc_end_time) = 0;
	virtual int  MATERIAL_INFO__Get_MOVE_INFO(const int port_id,
											  const int slot_id,
											  CStringArray& l_move_module_name,
											  CStringArray& l_move_start_time,
											  CStringArray& l_move_end_time) = 0;

	virtual int  Get__PORT_FIRST_SLOT_ID(const int ptn,int& slot_id) = 0;

	virtual int  JOB_CTRL__Disable_AUTO_PORT_COUNT() = 0;
	virtual int  JOB_CTRL__GoTo_NEXT_PORT() = 0;

	virtual int  Check__SYSTEM_END() = 0;


	virtual int  Check__MATERIAL_TO_PROCESS__WITH_NOT_PAUSED() = 0;

	virtual int  Get__ALL_PRC_MODULE_EX(const int slot_size,CStringArray& l_module) = 0;

	// ...	
	virtual int  Process_Start__PMC_WITH_SLOT(const int material_port_id,
											  const int material_slot_id,
											  const int pmc_id,
											  const int pmc_slot_id,
											  const CString& recipe) = 0;
	virtual int  Process_End__PMC_WITH_SLOT(const int material_port_id,
											const int material_slot_id,
											const int pmc_id,
											const int pmc_slot_id) = 0;

	// ...
	virtual int  Clear__MATERIAL_INFO__INTO_PMC(const int pmc_id) = 0;

	virtual int  Set__MATERIAL_INFO__INTO_PMC(const int pmc_id,
											  const int pmc_slot_id,
											  const int material_port_id,
											  const int material_slot_id) = 0;
	virtual int  Get__MATERIAL_INFO__INTO_PMC(const int pmc_id,
											  const int pmc_slot_id,
											  int& material_port_id,
											  int& material_slot_id) = 0;

	// ...
	virtual int  Transfer_End__To_MODULE(const CString& cur_pos,const CString& to_module) = 0;

	virtual int  MATERIAL_INFO__Get_ACT_INFO(const int port_id,
											 const int slot_id,
											 const int module_index,
											 CStringArray& l_act_name,
											 CStringArray& l_act_start_time,
											 CStringArray& l_act_end_time) = 0;

	// ...
	virtual int  MATERIAL_INFO__Get_MOVE_INFO_EX(const int port_id,
												 const int slot_id,
												 CStringArray& l_move_module_name,
												 CStringArray& l_move_start_time,
												 CStringArray& l_move_end_time,
												 CStringArray& l_delay_time) = 0;

	// ...
	virtual int  Start__ACT_COMMAND(const CString& cur_pos,
									const CString& cmmd_name) = 0;
	virtual int  End__ACT_COMMAND(const CString& cur_pos,
								  const CString& cmmd_name) = 0;

	// ...
	virtual int  MATERIAL_INFO__Register_SYSTEM_NAME(const CString& sys_name) = 0;
	virtual int  MATERIAL_INFO__Set_COUNT_IN_SYSTEM(const CString& sys_name,const int material_count) = 0;

	virtual int  MATERIAL_INFO__Get_TOTAL_COUNT_IN_SYSTEM(int& material_count) = 0;
	virtual int  MATERIAL_INFO__Get_SYSTEM_LIST(CStringArray& l_sys_name) = 0;
	virtual int  MATERIAL_INFO__Get_COUNT_IN_SYSTEM(const CString& sys_name,int& material_count) = 0;

	// ...
	virtual int  ROUTE_INFO__Get_ALIGN_INFO(const int port_id,const int slot_id,
											CString& align_info) = 0;
	virtual int  ROUTE_INFO__Get_ALIGN_INFO(const CString& material_pos,
											CString& align_info) = 0;

	// ...
	virtual int  Process_Start__PMC_WITH_SLOT_EX(const int material_port_id,
												 const int material_slot_id,
												 const int pmc_id,
												 const int pmc_slot_id,
												 const CString& recipe,
												 const CString& pm_log_path) = 0;

	// ...
	virtual int  LPx__MOVE_IN(const int port_id) = 0;
	virtual int  LPx__MOVE_OUT(const int port_id) = 0;

	virtual int  Post__ALARM_INFO(const int port_id,const int lp_slot_id) = 0;
	virtual int  Clear__ALARM_INFO(const int port_id,const int lp_slot_id) = 0;

	// ...
	virtual int  Make_JOB_HISTORY__START(const int src_ptn,
										 const int trg_ptn,
										 const CString& job_name,
										 const CString& cstid) = 0;

	// ...
	virtual int  Get__JOB_PORT_SIZE() = 0;

	virtual void* Get_Ptr__JOB_DB() = 0;
	virtual int   Copy__TO_JOB_DB(void *p_void) = 0;

	// ...
	virtual int  Get__Last_Processing_Info(const int port_id,const int slot_id,
										   CString& pmc_name,
										   CString& pmc_rcp) = 0;

	virtual int  Get__Last_Processing_Info(const CString& cur_pos,
										   CString& pmc_name,
										   CString& pmc_rcp) = 0;

	// ...
	virtual int  Get__Current_Process_Name_Of_PMC(const int port_id,const int slot_id,
												  const CString& pmc_name,
												  CString& rcp_name) = 0;

	virtual int  Get__Current_Process_Name_Of_PMC(const CString& cur_pos,
												  const CString& pmc_name,
												  CString& rcp_name) = 0;

	// ...
	virtual int  Make_JOB_HISTORY__START_SINGLE_MATERIAL(const int src_ptn,
														 const int trg_ptn,
														 const CString& job_name,
														 const CString& cstid) = 0;

	virtual int  Log_Ctrl__WRITE_LOT_FLOW(const int port_id,
								          const CString& log_flow) = 0;

	virtual int  Sch_Info__SET_TARGET_MODULE(const CString& target_module) = 0;

	virtual int  Load__SCH_INFO_At_First_SCH_DB_EX(const IDS__SCH_DB_INFO& db_info,
												  const double preheat_time,
												  const double cooling_time) = 0;

	virtual int  Load__SCH_INFO_At_Last_SCH_DB_EX(const IDS__SCH_DB_INFO& db_info,
												  const double preheat_time,
												  const double cooling_time) = 0;

	virtual int  Get__SCH_LBx_INFO(const int port_id,const int slot_id,
								   double& preheat_time,
								   double& cooling_time) = 0;
	virtual int  Get__SCH_LBx_INFO(const CString& sch_name,
								   double& preheat_time,
								   double& cooling_time) = 0;

	virtual int  Get__JOB_INFO(const int port_id,
							   const int slot_id,
							   IDS__JOB_INFO& job_info) = 0;
	virtual int  Get__JOB_INFO(const CString& cur_pos,
							   IDS__JOB_INFO& job_info) = 0;

	// ...
	virtual int  Set__SCH_DB_DIR(const CString& dir_sch_db) = 0;
	virtual int  Save__SCH_DB()   = 0;
	virtual int  Update__SCH_DB() = 0;

	virtual int  Clear__PROCESS_MODULE(const int port_id,
									   const int slot_id,
									   const CString& module_name) = 0;
	virtual int  Clear__PROCESS_MODULE(const CString& cur_pos,
									   const CString& module_name) = 0;

	virtual int  Check__LAST_PORT_SLOT_ID(const int ptn,const int slot_id) = 0;

	// ...
	virtual int  TAS__Upload_DB_FILE(const CString& sub_dir,
								     const CString& file_name) = 0;
	virtual int  TAS__Set_SUB_MACHINE_ID(const CString& str_id) = 0;
	virtual int  TAS__Set_MAX_LOG_DAY(const int max_day) = 0;

	virtual int  Disable__ALL_MATERIAL_LOG() = 0;

	virtual int  TAS__Get_REPORT_FILE_LIST(CStringArray& l_path,
										   CStringArray& l_file) = 0;

	// ...
	virtual int  APC__Upload_DB_FILE(const CString& sub_dir,
								     const CString& file_name) = 0;

	virtual int  APC__Start_UNIT_TYPE(const CString& unit_type) = 0;
	virtual int  APC__Stop_UNIT_TYPE(const CString& unit_type) = 0;

	virtual int  APC__Change_SAMPLING_TIME(const CString& unit_type,
										   const double sec) = 0;

	virtual int  APC__Get_UNIT_TYPE_LIST(CStringArray& l_unit_type) = 0;
	virtual int  APC__Set_EQPID(const CString& unit_type,const CString& eqp_id) = 0;
	virtual int  APC__Get_REPORT_FILE_LIST(CStringArray& l_file_path,
										   CStringArray& l_file_name) = 0;

	virtual int  APC__Set_BACKUP_SIZE(const int day_size) = 0;
	virtual int  TAS__Set_BACKUP_SIZE(const int day_size) = 0;

	// ...
	virtual int  JOB_CTRL__GoTo_NEXT_PORT_WITHOUT_PORT(const int port_id) = 0;

	virtual int  Set__USER_DEF_INFO(const CString& main_name,
								    const CString& sub_name,
									const CStringArray& l_data) = 0;
	virtual int  Get__USER_DEF_INFO(const CString& main_name,
									const CString& sub_name,
									CStringArray& l_data) = 0;

	virtual int  Get__USER_DEF__MAIN_LIST(CStringArray& l_main_name) = 0;
	virtual int  Get__USER_DEF__SUB_LIST(const CString& main_name,
										 CStringArray& l_sub_name) = 0;

	// ...
	virtual int  PMC__Process_Fail(const int material_port_id,
								   const int material_slot_id,
								   const int pmc_id,
								   const CString& pm_log_path) = 0;
								   
	// ...
	virtual int  LOG_CTRL__Check_Job_End(const CString& cur_pos) = 0; 

	virtual int  Check__EVENT__PICK_From_LPx(int& port_id,int& slot_id,CString& lot_id) = 0;
	virtual int  Check__EVENT__PLACE_To_LPx(int& port_id,int& slot_id,CString& lot_id)  = 0;

	virtual int  Get__ALL_LPx_INFO_FROM_DB(CUIntArray& l_portid,CUIntArray& l_slotid) = 0;

	// ...
	virtual int  ALARM_EXP__Upload_INFO_FILE(const CString& sub_dir,const CString& file_name) = 0;
	virtual int  ALARM_EXP__Check_ID(const int seq_id,const int alarm_id,CString& alm_exp) = 0;

	// ...
	virtual int  RMS__Upload_ECID_FILE(const CString& sub_dir,
								       const CString& file_name) = 0;

	virtual int  RMS__Set_Current_UNITID(const CString& str_unitid) = 0;
	virtual int  RMS__Get_Current_UNITID(CString& str_unitid) = 0;

	virtual int  RMS__Get_ECID_PARAMETER_SIZE() = 0;
	virtual int  RMS__Get_ECID_PARAMETER_From_INDEX(int index,
												    CString& item_name,CString& item_unit,CString& item_range,
												    CString& ch_name,CString& ch_type,
												    CString& fmt_unit,int& size) = 0;
	virtual int  RMS__Get_ECID_PARAMETER_From_ITEM_NAME(const CString& item_name,
													    CString& item_unit,CString& item_range,
													    CString& ch_name,CString& ch_type,
													    CString& fmt_unit,int& size) = 0;

	virtual int  RMS__Check_ECID_DATA(int index,const CString& data) = 0;
	virtual int  RMS__Check_ECID_DATA(const CString& item_name,const CString& data) = 0;

	virtual CString RMS__Get_ECID_DATA(int index) = 0;
	virtual CString RMS__Get_ECID_DATA(const CString& item_name) = 0;

	virtual int  RMS__Check_ECID_CHANGE() = 0;
	virtual int  RMS__Get_ECID_CHANGE_INFO(int& index,
									       CString& item_name,
										   CString& ch_data,
									       CString& fmt_unit,
										   int& fmt_size) = 0;
	virtual int  RMS__Resynch_ECID_CHANGE() = 0;
	virtual int  RMS__Set_ECID_DATA(const CString& item_name,const CString& item_data) = 0;

	// ...
	virtual int  Get__POST_CLN_INFO(const int port_id,const int slot_id,
									CStringArray& l_cln_module,
									CStringArray& l_cln_recipe) = 0;
	virtual int  Get__POST_CLN_INFO(const CString& material_pos,
									CStringArray& l_cln_module,
									CStringArray& l_cln_recipe) = 0;
	
	virtual int  Get__POST_CLN_In_PMC(const CString& material_pos,
									  const int pmc_id,
									  CString& cln_module,
									  CString& cln_recipe) = 0;
	virtual int  Check__POST_CLN_In_PMC(const CString& material_pos,
									    const int pmc_id) = 0;

	// ...
	virtual int  Change__SCH_DB_INFO(const int port_id,const int slot_id,
									 const IDS__SCH_MATERIAL_INFO& db_info) = 0;

	virtual int  Check__MATERIAL_TO_PROCESS_IN_LPx(const int port_id) = 0;

	virtual int  Get__BUFFERx_INFO(const int port_id,const int slot_id,
								   CString& buffer1_info,
								   CString& buffer2_info) = 0;
	virtual int  Get__BUFFERx_INFO(const CString& material_pos,
								   CString& buffer1_info,
								   CString& buffer2_info) = 0;

	virtual int  Check__MATERIAL_TO_USE_BUFFERx() = 0;

	virtual int  Load__POST_CLN_INFO(const int port_id,
									 const int slot_id,
									 const CStringArray& l_cln_module,
									 const CStringArray& l_cln_recipe) = 0;

	virtual int  Insert__SCH_INFO_At_First_SCH_DB(const int db_index,
												  const IDS__SCH_DB_INFO& db_info) = 0;

	virtual int  Get__ALL_PRC_MODULE_In_LPx(const int port_id, 
										    CStringArray& l_module) = 0;

	virtual int  JOB_CTRL__GoTo_JOB_PORT(const int port_id) = 0;
	virtual int  Check__MATERIAL_TO_PROCESS_WITH_PMC_IN_LPx(const int port_id) = 0;

	virtual int  Return__PORT_ID(const int port_id) = 0;
	
	virtual int  SCH_DB_INFO__Change_Current_Route_Step(const int port_id,
														const int slot_id,
														const CStringArray& l_pmc_name,
														const CStringArray& l_pmc_rcp,
														const CStringArray& l_pmc_stage) = 0;
	virtual int  SCH_DB_INFO__Change_Current_Route_Step(const CString& sch_name,
														const CStringArray& l_pmc_name,
														const CStringArray& l_pmc_rcp,
														const CStringArray& l_pmc_stage) = 0;

	// ...
	virtual int  Get__COOLER_INFO(const int port_id,const int slot_id,
								  CStringArray& l_cool_module,
								  CStringArray& l_cool_recipe) = 0;
	virtual int  Get__COOLER_INFO(const CString& material_pos,
								  CStringArray& l_cool_module,
								  CStringArray& l_cool_recipe) = 0;
	
	virtual int  Get__COOLER_In_PMC(const CString& material_pos,
									const int pmc_id,
									CString& cool_module,
									CString& cool_recipe) = 0;
	virtual int  Check__COOLER_In_PMC(const CString& material_pos,
									  const int pmc_id) = 0;

	// ...
	virtual int  SCH_DB_INFO__Get_Cuurent_Step_Count(const int port_id,const int slot_id) = 0;
	virtual int  SCH_DB_INFO__Get_Current_Step_Count(const CString& material_pos) = 0;

	// ...
	virtual int  Step_Start__PMC_EX(const CString& cur_pos,const int pmc_id, const int step_id) = 0;
	virtual int  Step_End__PMC_EX(const CString& cur_pos,const int pmc_id, const int step_id) = 0;

	// ...
	virtual int  Set__LPx_Foup_Exist(const int port_id) = 0;
	virtual int  Clear__LPx_Foup_Exist(const int port_id) = 0;
	virtual int  Check__LPx_Foup_Exist(const int port_id) = 0;

	virtual int  Set__LPx_PIO_Handshake(const int port_id) = 0;
	virtual int  Clear__LPx_PIO_Handshake(const int port_id) = 0;
	virtual int  Check__LPx_PIO_Handshake(const int port_id) = 0;

	// ...
	virtual int  Add__Route_Info_At_SCH_DB(const int port_id,
		                                   const int slot_id,
		                                   const IDS__SCH_DB_ROUTE_INFO& db_info) = 0;

	virtual int  Set__MATERIAL_POSITION_EX(const CString& material_pos,
		                                   const CString& pos_name) = 0;

	// ...
	virtual int  Get__CUR_PROCESS_ALL_INFO(const int port_id,const int slot_id,
		                                   CStringArray& l_prc_module,
		                                   CStringArray& l_prc_recipe,
		                                   CStringArray& l_stage_info,
										   CStringArray& l_sub_recipe1,
										   CStringArray& l_sub_recipe2,
										   CStringArray& l_sub_recipe3,
										   CStringArray& l_sub_recipe4,
										   CStringArray& l_sub_recipe5) = 0;
	virtual int  Get__CUR_PROCESS_ALL_INFO(const CString& material_pos,
		                                   CStringArray& l_prc_module,
		                                   CStringArray& l_prc_recipe,
		                                   CStringArray& l_stage_info,
										   CStringArray& l_sub_recipe1,
										   CStringArray& l_sub_recipe2,
										   CStringArray& l_sub_recipe3,
										   CStringArray& l_sub_recipe4,
										   CStringArray& l_sub_recipe5) = 0;

	//
	virtual int  Get__PRE_MEASUREMENT_INFO(const int port_id,const int slot_id,
		                                   CString& rcp_name) = 0;
	virtual int  Get__PRE_MEASUREMENT_INFO(const CString& material_pos,
		                                   CString& rcp_name) = 0;

	virtual int  Get__POST_MEASUREMENT_INFO(const int port_id,const int slot_id,
		                                    CString& rcp_name) = 0;
	virtual int  Get__POST_MEASUREMENT_INFO(const CString& material_pos,
		                                    CString& rcp_name) = 0;

	//
	virtual int  Load__PRE_MEASUREMENT_INFO(const int port_id,
		                                    const int slot_id,
		                                    const CString& rcp_name) = 0;

	virtual int  Load__POST_MEASUREMENT_INFO(const int port_id,
		                                     const int slot_id,
		                                     const CString& rcp_name) = 0;

	//
	virtual int  Get__HEAD_ARM_USE_INFO(const int port_id,const int slot_id,
		                                int& arm1_use,
										int& arm2_use,
										int& arm3_use,
										int& arm4_use) = 0;
	virtual int  Get__HEAD_ARM_USE_INFO(const CString& material_pos,
		                                int& arm1_use,
										int& arm2_use,
										int& arm3_use,
										int& arm4_use) = 0;
	
	virtual int  Load__HEAD_ARM_USE_INFO(const int port_id,
		                                 const int slot_id,
		                                 const int arm1_use,
										 const int arm2_use,
										 const int arm3_use,
										 const int arm4_use) = 0;

	//
	virtual int  Get__LLx_CLEAN_RECIPE(const int port_id,const int slot_id,
		                               CString& ll1_recipe,
		                               CString& ll2_recipe) = 0;
	virtual int  Get__LLx_CLEAN_RECIPE(const CString& material_pos,
		                               CString& ll1_recipe,
		                               CString& ll2_recipe) = 0;

	virtual int  Load__LLx_CLEAN_RECIPE(const int port_id,
		                                const int slot_id,
		                                const CString& ll1_cln_rcp,
		                                const CString& ll2_cln_rcp) = 0;

	// ...
	virtual int  Step_Start__CHMx_STAGEy(const CString& cur_pos,
		                                 const int chm_id,
										 const int stage_id, 
										 const int step_id) = 0;
	virtual int  Step_End__CHMx_STAGEy(const CString& cur_pos,
		                               const int chm_id,
									   const int stage_id, 
									   const int step_id) = 0;

	virtual int  Place__To_MODULE_STAGEx(const CString& robot_pos,
		                                 const CString& module_pos,
										 const int chm_id,
										 const int stage_id) = 0;
	virtual int  Pick__From_MODULE_STAGEx(const CString& module_pos,
		                                  const CString& robot_pos,
										  const int chm_id,
										  const int stage_id) = 0;

	// ...
	virtual int  Check__MATERIAL_IN_LPx_TO_USE_BUFFERx() = 0;


	// ...
	virtual int  MARS_PRIME__Set_BACKUP_SIZE(const int day_size) = 0;
	virtual int  MARS_PRIME__Set_BACKUP_DIRECTORY(const CString& log_dir) = 0;

	virtual int  MARS_PRIME__Start() = 0;
	virtual int  MARS_PRIME__Stop() = 0;

	virtual int  MARS_PRIME__Get_REPORT_FILE_LIST(CStringArray& l_path,CStringArray& l_file) = 0;

	// ...
	virtual int  Rotate_Start__To_MODULE(const CString& cur_pos,const CString& to_module) = 0;
	virtual int  Rotate_End__To_MODULE(const CString& cur_pos,const CString& to_module) = 0;

	// Lot Event Log ...
	virtual int  SAMSUNG_STD_LOG__LEH(const IDS_SAMSUNG_STD_LOG__LEH& ds_info) = 0;
		
	// Transfer Log ...
	virtual int  SAMSUNG_STD_LOG__XFR_Start(const IDS_SAMSUNG_STD_LOG__XFR& ds_info) = 0;
	virtual int  SAMSUNG_STD_LOG__XFR_End(const IDS_SAMSUNG_STD_LOG__XFR& ds_info) = 0;
	
	// Process Log ...
	virtual int  SAMSUNG_STD_LOG__PRC_Start(const IDS_SAMSUNG_STD_LOG__PRC& ds_info) = 0;
	virtual int  SAMSUNG_STD_LOG__PRC_End(const IDS_SAMSUNG_STD_LOG__PRC& ds_info) = 0;
	
	// Function Log ...
	virtual int  SAMSUNG_STD_LOG__FNC_Start(const IDS_SAMSUNG_STD_LOG__FNC& ds_info) = 0;
	virtual int  SAMSUNG_STD_LOG__FNC_End(const IDS_SAMSUNG_STD_LOG__FNC& ds_info) = 0;

	// hour_size : 1 ~ 24 ...	
	//   Default : 1 
	virtual int  MARS_PRIME__Set_BACKUP_HOUR_SIZE(const double hour_size) = 0;
	virtual double  MARS_PRIME__Get_BACKUP_HOUR_SIZE() = 0;

	// ...
	virtual int  Get__ALL_MATERIAL_INFO_TO_PROCESS(CStringArray& l_all_sch_db) = 0;


	// EDIT TYPE ...
	virtual int  Check__EDIT_TYPE__STATE() = 0;
	virtual int  Check__SCH_CFG() = 0;

	virtual int  Get__ALx_OF_EDIT_TYPE(CStringArray& l_id, 
										CStringArray& l_mode, 
										CStringArray& l_slot) = 0;
	virtual int  Get__LLx_IN_OF_EDIT_TYPE(CStringArray& l_id, 
										  CStringArray& l_mode, 
										  CStringArray& l_slot) = 0;
	virtual int  Get__LLx_OUT_OF_EDIT_TYPE(CStringArray& l_id, 
											CStringArray& l_mode, 
											CStringArray& l_slot) = 0;
	virtual int  Get__STx_OF_EDIT_TYPE(CStringArray& l_id, 
										CStringArray& l_mode, 
										CStringArray& l_slot, 
										CStringArray& l_sec) = 0;

	// PRE-RECIPE ...
	virtual int  Get__PRE_RCP_INFO(const int port_id,const int slot_id,
								   CStringArray& l_pre_module,
								   CStringArray& l_pre_recipe) = 0;
	virtual int  Get__PRE_RCP_INFO(const CString& material_pos,
								   CStringArray& l_pre_module,
								   CStringArray& l_pre_recipe) = 0;

	virtual int  Get__PRE_RCP_In_PMC(const CString& material_pos,
									 const int pmc_id,
									 CString& pre_module,
									 CString& pre_recipe) = 0;
	virtual int  Check__PRE_RCP_In_PMC(const CString& material_pos,
									   const int pmc_id) = 0;

	// 
	virtual int  Clear__CURRENT_PROCESS(const int portid,const int slot_id) = 0;
	virtual int  Clear__CURRENT_PROCESS(const CString& material_pos) = 0;


	// EDIT TYPE : MATERIAL INFO ...
	virtual int  Get__ALx_OF_EDIT_TYPE(const int port_id,const int slot_id,
									   CStringArray& l_id, 
									   CStringArray& l_mode, 
									   CStringArray& l_slot) = 0;
	virtual int  Get__ALx_OF_EDIT_TYPE(const CString& material_pos,
										CStringArray& l_id, 
										CStringArray& l_mode, 
										CStringArray& l_slot) = 0;

	virtual int  Get__LLx_IN_OF_EDIT_TYPE(const int port_id,const int slot_id,
										  CStringArray& l_id, 
										  CStringArray& l_mode, 
										  CStringArray& l_slot) = 0;
	virtual int  Get__LLx_IN_OF_EDIT_TYPE(const CString& material_pos,
										  CStringArray& l_id, 
										  CStringArray& l_mode, 
										  CStringArray& l_slot) = 0;

	virtual int  Get__LLx_OUT_OF_EDIT_TYPE(const int port_id,const int slot_id,
										   CStringArray& l_id, 
										   CStringArray& l_mode, 
										   CStringArray& l_slot) = 0;
	virtual int  Get__LLx_OUT_OF_EDIT_TYPE(const CString& material_pos,
										   CStringArray& l_id, 
										   CStringArray& l_mode, 
										   CStringArray& l_slot) = 0;

	virtual int  Get__STx_OF_EDIT_TYPE(const int port_id,const int slot_id,
									   CStringArray& l_id, 
									   CStringArray& l_mode, 
									   CStringArray& l_slot, 
									   CStringArray& l_sec) = 0;
	virtual int  Get__STx_OF_EDIT_TYPE(const CString& material_pos,
									   CStringArray& l_id, 
									   CStringArray& l_mode, 
									   CStringArray& l_slot, 
									   CStringArray& l_sec) = 0;

	// ...
	virtual int  Check__MATERIAL_OF_LLx_IN(const int port_id,
		                                   const int ll_id, 
										   const bool single_mode) = 0;

	virtual int  Check__MATERIAL_OF_LLx_OUT(const int port_id,
										    const int ll_id, 
											const bool single_mode) = 0;

	// ...
	virtual int  Check__PMC_TO_PROCESS_OF_PRE_DB(const int port_id,
												 const int slot_id,
												 const CString& pmc_name) = 0; 

	virtual int  Check__PMC_TO_PROCESS_OF_PRE_DB(const CString& material_pos,
												 const CString& pmc_name) = 0; 

	// ...
	virtual int  Get__PROC_LOOPx_OF_EDIT_TYPE(const int port_id,const int slot_id,
											  CString& loop_id,
											  int& loop_count) = 0;
	virtual int  Get__PROC_LOOPx_OF_EDIT_TYPE(const CString& material_pos,
											  CString& loop_id,
											  int& loop_count) = 0;

	// ...
	virtual int  Get__STEP_SIZE_OF_MATERIAL(const int port_id,const int slot_id) = 0;
	virtual int  Get__STEP_SIZE_OF_MATERIAL(const CString& material_pos) = 0;

	virtual int  Get__STEPx_PROCESS_INFO_OF_MATERIAL(const int port_id,const int slot_id,	
													 const int step_index,
													 CStringArray& l_pre_module,
													 CStringArray& l_pre_recipe,
													 CStringArray& l_main_module,
													 CStringArray& l_main_recipe,
													 CStringArray& l_post_module,
													 CStringArray& l_post_recipe) = 0;
	virtual int  Get__STEPx_PROCESS_INFO_OF_MATERIAL(const CString& material_pos,
													 const int step_index,
													 CStringArray& l_pre_module,
													 CStringArray& l_pre_recipe,
													 CStringArray& l_main_module,
													 CStringArray& l_main_recipe,
													 CStringArray& l_post_module,
													 CStringArray& l_post_recipe) = 0;

	// ...
	virtual int  Set__DIR_JOB_LOG(const int port_id, const CString& dir_job_log) = 0;
	virtual int  Get__DIR_JOB_LOG(const int port_id, CString& dir_job_log) = 0;

	// ...
	virtual int  Set__PROC_LOOPx_OF_EDIT_TYPE(const int port_id,const int slot_id,
											  const CString& loop_id,
											  const int loop_count) = 0;

	// ...
	virtual int  Get__NEXT_PROCESS_INFO(const int port_id,const int slot_id,				// *
										CStringArray& l_prc_module,
										CStringArray& l_prc_recipe) = 0;
	virtual int  Get__NEXT_PROCESS_INFO(const CString& material_pos,						// *
										CStringArray& l_prc_module,
										CStringArray& l_prc_recipe) = 0;

	// ...
	virtual int  Copy__SCH_INFO_At_SCH_DB(const int db_index, 
		                                  const int src_ptn,
										  const int src_slot,
										  const int trg_ptn,
										  const int trg_slot,
										  const bool active__al_clear,
										  const bool active__st_clear,
										  const bool active__loop_clear) = 0;

	virtual int  Change__PROC_INFO_OF_SCH_DB(const int port_id,
											 const int slot_id,
											 const CString& job_name,
											 const CString& lotid,
											 const CString& material_id,
											 const CString& ppid,
											 const CString& material_type,
											 const CStringArray& l_pre_module,
											 const CStringArray& l_pre_recipe,
											 const CStringArray& l_main_module,
											 const CStringArray& l_main_recipe,
											 const CStringArray& l_post_module,
											 const CStringArray& l_post_recipe) = 0;

	// ...
	virtual int  Check__Pause_PORT_ID(const int port_id) = 0;

	//.LLx_OUT : INFO ...
	virtual int  Get__COOLING_SEC_OF_LLx_OUT(const int port_id,const int slot_id,
											 const int ll_id,
										     CString& ll_cooling_sec) = 0;

	virtual int  Get__COOLING_SEC_OF_LLx_OUT(const CString& material_pos,
											 const int ll_id,
											 CString& ll_cooling_sec) = 0;

	// ...
	virtual int  Set__USER_DEF_DATA(const CString& main_name,
									const CString& sub_name,
									const CString& set_data) = 0;
	virtual int  Get__USER_DEF_DATA(const CString& main_name,
									const CString& sub_name,
									CString& rcv_data) = 0;

	virtual int  Clear__USER_DEF_INFO(const CString& main_name) = 0;
	virtual int  Clear__USER_DEF_INFO(const CString& main_name,
									  const CString& sub_name) = 0;

	// STx ...
	virtual int  Get__STx_N2_PURGE_OF_EDIT_TYPE(CStringArray& l_id, 
												CStringArray& l_n2_purge) = 0;

	virtual int  Get__STx_N2_PURGE_OF_EDIT_TYPE(const int port_id,const int slot_id,
												CStringArray& l_id, 
												CStringArray& l_n2_purge) = 0;
	virtual int  Get__STx_N2_PURGE_OF_EDIT_TYPE(const CString& material_pos,
												CStringArray& l_id, 
												CStringArray& l_n2_purge) = 0;

	virtual int  Check__STx_N2_PURGE_OF_EDIT_TYPE(const int port_id) = 0;
};


// ...
#define  MODULE_STATUS__NOT_AVAILABLE				0
#define  MODULE_STATUS__DISABLE						1
#define  MODULE_STATUS__AVAILABLE					2

#define  FA_STATUS__NOT_ESTABLISHED					0
#define  FA_STATUS__OFFLINE							1
#define  FA_STATUS__LOCAL							2
#define  FA_STATUS__REMOTE							3


class SCI__CTC__LOT_SUMMARY_CTRL
{
public:
	virtual ~SCI__CTC__LOT_SUMMARY_CTRL(){};

	// ...
	virtual int Create__SERVICE_DB(const CString& service_name) = 0;
	virtual int Link__SERVICE_DB(const CString& service_name)   = 0;
	
	virtual int Set__DIR_ROOT(const CString& dir_root) = 0;
	virtual int Set__DATE_LIMIT(const int limit) = 0;

	virtual int Write__LOT_LOG(const CString& lotid,
						   const CString& portid) = 0;
	virtual int End__LOT_LOG(const CString& lotid,
						     const CString& portid) = 0;

	virtual int Write__SLOT_LOG(const CString& lotid,
								const CString& portid,
								const int slot,
							    const CString& module,
								const CString& recipeid,
								const CString& log) = 0;
	virtual int End__SLOT_LOG(const CString& lotid,
							  const CString& portid,
							  const int slot) = 0;

	virtual int Set__MULTI_SLOT() = 0;
	virtual int Clear__LOT_LOG(const CString& lotid,
							   const CString& portid) = 0;

	virtual int Alarm_Post__LOT_SLOT(const CString& lotid,
									 const CString& portid,
									 const int slot,
								     const int alarmid,
									 const CString& prcid) = 0;
	virtual int Alarm_Clear__LOT_SLOT(const CString& lotid,
									  const CString& portid,
									  const int slot,
									  const int alarmid) = 0;

	virtual int Write__LOT_LOG_EX(const CString& lotid,
								  const CString& portid,
								  const CString& user_id,
								  const CString& user_level) = 0;
};

class SCI__CTC__MATERIAL_LOG_CTRL
{
public:
	virtual ~SCI__CTC__MATERIAL_LOG_CTRL(){};

	// ...
	virtual int Create__SERVICE_DB(const CString& service_name) = 0;
	virtual int Link__SERVICE_DB(const CString& service_name)   = 0;
	
	virtual int Set__DIR_ROOT(const CString& dir_root) = 0;
	virtual int Set__DATE_LIMIT(const int limit)  = 0;


	virtual int Start__LOG(const CString& lotid,
						   const CString& portid) = 0;

	virtual int End__LOG(const CString& lotid,
						 const CString& portid)   = 0;

	// arm_type 
	//		0 : lower-arm
	//		1 : upper-arm
	// action
	//		0 : picking
	//      1 : pick
	//		2 : placing
	//      3 : place
	// module
	//		1 ~ 6 : PM1 ~ PM6
	//	   11 : AL
	//     21 : CL
	//     31 ~ 40 : PORT1 ~ PORT10
	virtual int Write__LOG(const int arm_type,
						   const int action,
						   const int module,
						   const CString& material,
						   const CString& lotid,
						   const CString& recipe) = 0;
};


// ...
class IDS__LCD_DB_INFO
{
public:
	CString sLOTID;				
	CString sCSTID;				
	CString sSLOTID;			
	CString sRECIPEID;			
	CString sPRCID;				
	CString sGLSODR;			
	CString sGLSID;				
	CString sGLSJUDGE;			
	CString sPNLIF;				
	CString sPORTID;			
	CString sGLSCODE;			
	CString sREINPUT;			
	CString sGLSTHICK;			
	CString sMODELNAME;			
	CString sLOTTYPE;			
	CString sGLSTYPE;			
	CString sKEYID;				

	CString sSUBMDLIF;
	CString sPARTNUM;
	CString sPRODTYPE;
	CString sATTRIBUTE;

	CStringArray sLIST__LSDITEM;
	CStringArray sLIST__LSDVALUE;

	CStringArray sLIST__GSDITEM;
	CStringArray sLIST__GSDVALUE;

	CString sPPID;
	CString sGLSMODE;
	CString sGLSPTN;	
};

class IDS__LOT_END_DATA
{
public:
	CString sLOTID;
	CString sCSTID;
	CString sRECIPEID;
	CString sPRCID;
	CString sUNITID;
	CString sKEYID;
	CString sLOTJUDGE;

	CString sINNO;
	CString sOUTNO;
	CString sCEID;

	CString sLOTNUMBER;
};

class IDS__PORT_INFO
{
public:
	CString sLOTID;
	CString sCSTID;
	CString sPORTID;
	CString sSLOTMAP;
    	CString sCSTREADY;
};

class IDS__S6F11_INFO
{
public:
	IDS__S6F11_INFO()
	{
		sCEID  = "";
		sRPTID = "";

		sLOTID   = "";
		sCSTID   = "";
		sSLOTNO  = "";
		sGLSID   = "";
		sGLSPROC = "";
		sPNLF    = "";
		sDICODE  = "";
		sPORTID  = "";
		sPPID    = "";

		sJUDGECODE = "";
		sGLSTHICK  = "";
		sGLSPTN    = "";
	}

	void Set_INFO(const IDS__S6F11_INFO& ds_info)
	{
		sCEID  = ds_info.sCEID;
		sRPTID = ds_info.sRPTID;

		sLOTID   = ds_info.sLOTID;
		sCSTID   = ds_info.sCSTID;
		sSLOTNO  = ds_info.sSLOTNO;
		sGLSID   = ds_info.sGLSID;
		sGLSPROC = ds_info.sGLSPROC;
		sPNLF    = ds_info.sPNLF;
		sDICODE  = ds_info.sDICODE;
		sPORTID  = ds_info.sPORTID;
		sPPID    = ds_info.sPPID;

		sJUDGECODE = ds_info.sJUDGECODE;
		sGLSTHICK  = ds_info.sGLSTHICK;
		sGLSPTN    = ds_info.sGLSPTN;
	}
	void Get_INFO(IDS__S6F11_INFO& ds_info)
	{
		ds_info.sCEID  = sCEID;
		ds_info.sRPTID = sRPTID;

		ds_info.sLOTID   = sLOTID;
		ds_info.sCSTID   = sCSTID;
		ds_info.sSLOTNO  = sSLOTNO;
		ds_info.sGLSID   = sGLSID;
		ds_info.sGLSPROC = sGLSPROC;
		ds_info.sPNLF    = sPNLF;
		ds_info.sDICODE  = sDICODE;
		ds_info.sPORTID  = sPORTID;
		ds_info.sPPID    = sPPID;

		ds_info.sJUDGECODE = sJUDGECODE;
		ds_info.sGLSTHICK  = sGLSTHICK;
		ds_info.sGLSPTN    = sGLSPTN;
	}

	// ...
	CString sCEID;
	CString sRPTID;

	CString sLOTID;
	CString sCSTID;
	CString sSLOTNO;
	CString sGLSID;
	CString sGLSPROC;
	CString sPNLF;
	CString sDICODE;
	CString sPORTID;
	CString sPPID;
	CString sJUDGECODE;
	CString sGLSTHICK;
	CString sGLSPTN;
};

class IDS__S6F91_INFO
{
public:
	IDS__S6F91_INFO()
	{
		sMODULE_NAME = "";
		iUNITID = 0;
		sEQPSTATUS = "";
		sALARMID = "";
		sALARM_TEXT = "";

		//
		sLIST__UNITID.RemoveAll();
		sLIST__EQPSTATUS.RemoveAll();
	}

	void Set_INFO(const IDS__S6F91_INFO& ds_info)
	{
		sMODULE_NAME = ds_info.sMODULE_NAME;
		iUNITID      = ds_info.iUNITID;
		sEQPSTATUS   = ds_info.sEQPSTATUS;
		sALARMID     = ds_info.sALARMID;
		sALARM_TEXT  = ds_info.sALARM_TEXT;

		//
		int limit = ds_info.sLIST__UNITID.GetSize();
		int i;

		sLIST__UNITID.RemoveAll();
		sLIST__EQPSTATUS.RemoveAll();

		for(i=0;i<limit;i++)
		{
			sLIST__UNITID.Add(ds_info.sLIST__UNITID[i]);
			sLIST__EQPSTATUS.Add(ds_info.sLIST__EQPSTATUS[i]);
		}
	}
	void Get_INFO(IDS__S6F91_INFO& ds_info)
	{
		ds_info.sMODULE_NAME = sMODULE_NAME;
		ds_info.iUNITID      = iUNITID;
		ds_info.sEQPSTATUS   = sEQPSTATUS;
		ds_info.sALARMID     = sALARMID;
		ds_info.sALARM_TEXT  = sALARM_TEXT;

		//
		int limit = sLIST__UNITID.GetSize();
		int i;

		ds_info.sLIST__UNITID.RemoveAll();
		ds_info.sLIST__EQPSTATUS.RemoveAll();

		for(i=0;i<limit;i++)
		{
			ds_info.sLIST__UNITID.Add(sLIST__UNITID[i]);
			ds_info.sLIST__EQPSTATUS.Add(sLIST__EQPSTATUS[i]);
		}
	}

	// ...
	CString sMODULE_NAME;
	
	int     iUNITID;
	CString sEQPSTATUS;
	CString sALARMID;

	CStringArray sLIST__UNITID;
	CStringArray sLIST__EQPSTATUS;

	CString sALARM_TEXT;
};

class IDS__GLS_LOT_END_REQ
{
public:
	CString sLOTID;
	CString sCSTID;
	CString sSLOTNO;
	CString sPPID;
	CString sPRCID;
	CString sGLSMODE;
	CString sGLSID;
	CString sJUDGECODE;
	CString sPNLIF;
	CString sPORTID;
};

class IDS__GLS_LOT_INFO
{
public:
	CString sLOTID;
	CString sCSTID;
	CString sSLOTNO;
	CString sPPID;
	CString sPRCID;
	CString sGLSMODE;
	CString sGLSID;
	CString sJUDGECODE;
	CString sPNLIF;
	CString sPORTID;
};


class SCI__LCD_DB_CTRL
{
public:
	virtual ~SCI__LCD_DB_CTRL(){};

	// ...
	virtual int  Check__GLSCODE(const CString& glscode) = 0;

	virtual int  Load__DB_INFO(const CString& cur_pos,
							   const IDS__LCD_DB_INFO& db_info) = 0;

	virtual int  Clear__DB_INFO_WITH_GLS_CODE(const CString& gls_code) = 0;
	virtual int  Clear__DB_INFO_WITH_GLS_POS(const CString& cur_pos) = 0;
	virtual int  Clear__ALL_INFO() = 0;

	virtual int  Get__DB_INFO(const CString& cur_pos,
							  IDS__LCD_DB_INFO& db_info) = 0;

	virtual int  Get__DB_SIZE() = 0;
	virtual int  Get__CUR_POS_And_GLSCODE(const int db_index,
										  CString& cur_pos,
										  CString& glscode) = 0;

	virtual int  Check__DB(const CString& cur_pos) = 0;
	virtual int  Get__ALL_DB_INFO(CString& all_db_info) = 0;

	// ...
	virtual int  Set__ECS_MODE(const CString& ecs_mode) = 0;
	virtual int  Get__ECS_MODE(CString& ecs_mode) = 0;

	virtual int  Set__TOOL_UNITID(const int id) = 0;
	virtual int  Set__LBA_UNITID(const int id) = 0;
	virtual int  Set__LBB_UNITID(const int id) = 0;
	virtual int  Set__TMC_UNITID(const int id) = 0;
	virtual int  Set__PMC_UNITID(const int pm_id,const int id) = 0;

	virtual int  Get__SUNITID(const CString& module_name,int& id) = 0;
	virtual int  Get__TOOL_UNITID(int &id) = 0;
	virtual int  Get__LBA_UNITID(int &id) = 0;
	virtual int  Get__LBB_UNITID(int &id) = 0;
	virtual int  Get__TMC_UNITID(int &id) = 0;
	virtual int  Get__PMC_UNITID(const int pm_id,int &id) = 0;

	virtual int  Check__TOOL_UNITID(const int id) = 0;
	virtual int  Check__LBA_UNITID(const int id) = 0;
	virtual int  Check__LBB_UNITID(const int id) = 0;
	virtual int  Check__TMC_UNITID(const int id) = 0;
	virtual int  Check__PMC_UNITID(const int pm_id,const int id) = 0;

	virtual int  Set__TOOL_STATUS(const CString& eqp_sts) = 0;
	virtual int  Set__LBA_STATUS(const CString& eqp_sts) = 0;
	virtual int  Set__LBB_STATUS(const CString& eqp_sts) = 0;
	virtual int  Set__TMC_STATUS(const CString& eqp_sts) = 0;
	virtual int  Set__PMC_STATUS(const int pm_id,const CString& eqp_sts) = 0;

	virtual int  Get__TOOL_STATUS(CString& eqp_sts) = 0;
	virtual int  Get__LBA_STATUS(CString& eqp_sts) = 0;
	virtual int  Get__LBB_STATUS(CString& eqp_sts) = 0;
	virtual int  Get__TMC_STATUS(CString& eqp_sts) = 0;
	virtual int  Get__PMC_STATUS(const int pm_id,CString& eqp_sts) = 0;

	// ...
	virtual int  Pick_From_MODULE(const CString& module_name,const CString& arm_type) = 0;
	virtual int  Place_To_MODULE(const CString& arm_type,const CString& module_name)  = 0;

	virtual int  Set__MATERIAL_ARRIVED(const CString& cur_pos) = 0;
	virtual int  Clear__DB_INFO_OF_NEXT_MATERIAL(const CString& cur_pos) = 0;

	virtual int  Set__LBA_UNLOAD_MATERIAL(const int exist_flag) = 0;
	virtual int  Set__LBB_UNLOAD_MATERIAL(const int exist_flag) = 0;

	virtual int  Check__LBA_UNLOAD_MATERIAL() = 0;
	virtual int  Check__LBB_UNLOAD_MATERIAL() = 0;

	virtual int  Load__LOT_END_DATA(const IDS__LOT_END_DATA& lot_end_data) = 0;
	virtual int  Get__LOT_END_DATA(IDS__LOT_END_DATA& lot_end_data) = 0;

	virtual int  Clear__PORT_INFO() = 0;
	virtual int  Load__PORT_INFO(const IDS__PORT_INFO& ds_port_info) = 0;
	virtual int  Get__PORT_INFO(const int db_index,IDS__PORT_INFO& ds_port_info) = 0;

	// ...		
	virtual int  Set__DIR_DB_INFO(const CString& dir_db_info) = 0;
	virtual int  Init__DB_INFO() = 0;

	// ...
	virtual int  Enable__PMx_STATUS(const int pm_id)  = 0;
	virtual int  Disable__PMx_STATUS(const int pm_id) = 0;
	virtual int  Check_Enable__PMx_STATUS(const int pm_id) = 0;

	virtual int  Set__PMx_CMSTATUS(const int pm_id,const CString& pm_sts) = 0;
	virtual int  Get__PMx_CMSTATUS(const int pm_id,CString& pm_sts) = 0;

	virtual int  Enable__LBA_STATUS()  = 0;
	virtual int  Disable__LBA_STATUS() = 0;
	virtual int  Check_Enable__LBA_STATUS() = 0;

	virtual int  Enable__LBB_STATUS()  = 0;
	virtual int  Disable__LBB_STATUS() = 0;
	virtual int  Check_Enable__LBB_STATUS() = 0;

	// ...
	virtual int  Set__S6F91_QUEUE(const IDS__S6F91_INFO& ds_info) = 0;
	virtual int  Get__S6F91_QUEUE(IDS__S6F91_INFO& ds_info) = 0;
	virtual int  Clear__S6F91_QUEUE() = 0;

	virtual int  Check__LCD_INFO(const CString& lotid,
								 const CString& glsid,
								 const CString& portid,
								 const CString& slotid) = 0;

	virtual int  Set__PMx_USE_CNT(const int pm_size) = 0;
	virtual int  Get__PMx_USE_CNT() = 0;

	virtual int  Get__NEXT_DB_INFO(const CString& cur_pos,
							       IDS__LCD_DB_INFO& db_info) = 0;

	virtual int  Get__GSD_INFO(const CString& cur_pos,
		                       const CString& gsd_item,
							   CString& gsd_value) = 0;

	virtual int  Get__KEYID_OF_LOT_DB(const CString& lotid,
									  CString& keyid) = 0;

	virtual int  Get__LSD_INFO(const CString& lotid,
							   const CString& glsid,
							   const CString& portid,
							   const CString& slotid,
							   CStringArray&  l_lsditem,
							   CStringArray&  l_lsdvalue) = 0;

	virtual int  Get__GSD_INFO(const CString& lotid,
							   const CString& glsid,
							   const CString& portid,
							   const CString& slotid,
							   CStringArray&  l_gsditem,
							   CStringArray&  l_gsdvalue) = 0;

	virtual int  Set__TOOL_EQPID(const CString& id) = 0;
	virtual int  Set__LBA_EQPID(const CString& id) = 0;
	virtual int  Set__LBB_EQPID(const CString& id) = 0;
	virtual int  Set__TMC_EQPID(const CString& id) = 0;
	virtual int  Set__PMC_EQPID(const int pm_id,const CString& id) = 0;

	virtual int  Get__TOOL_EQPID(CString& id) = 0;
	virtual int  Get__LBA_EQPID(CString& id) = 0;
	virtual int  Get__LBB_EQPID(CString& id) = 0;
	virtual int  Get__TMC_EQPID(CString& id) = 0;
	virtual int  Get__PMC_EQPID(const int pm_id,CString& id) = 0;

	virtual int  Set__LBA_MATERIAL(const int sts) = 0;
	virtual int  Set__LBB_MATERIAL(const int sts) = 0;
	virtual int  Set__TMC_A_MATERIAL(const int sts) = 0;
	virtual int  Set__TMC_B_MATERIAL(const int sts) = 0;
	virtual int  Set__PMC_MATERIAL(const int pm_id,const int sts) = 0;

	virtual int  Check__LBA_MATERIAL() = 0;
	virtual int  Check__LBB_MATERIAL() = 0;
	virtual int  Check__TMC_A_MATERIAL() = 0;
	virtual int  Check__TMC_B_MATERIAL() = 0;
	virtual int  Check__PMC_MATERIAL(const int pm_id) = 0;

	virtual int  Change__DB_INFO(const CString& cur_pos,
								 const IDS__LCD_DB_INFO& db_info) = 0;

	virtual int  Set__S6F11_QUEUE(const IDS__S6F11_INFO& ds_info) = 0;
	virtual int  Get__S6F11_QUEUE(IDS__S6F11_INFO& ds_info) = 0;
	virtual int  Clear__S6F11_QUEUE() = 0;

	virtual int  Change__CUR_POS(const CString& cur_pos,
								 const CString& new_pos) = 0;

	virtual int  Clear__ALL_GLS_LOT_END_REQ() = 0;
	virtual int  Clear__GLS_LOT_END_REQ(const CString& lotid) = 0;
	virtual int  Load__GLS_LOT_END_REQ(const IDS__GLS_LOT_END_REQ& gls_lot_end_req) = 0;
	virtual int  Get__GLS_LOT_END_REQ(IDS__GLS_LOT_END_REQ& gls_lot_end_req) = 0;
	virtual int  Check__GLS_LOT_END_REQ(const CString& lotid) = 0;

	virtual int  Check__LOTID_In_DB_INFO(const CString& lotid) = 0;

	virtual int  Load__DB_INFO_EX(const CString& cur_pos,
								  const IDS__LCD_DB_INFO& db_info,
								  const int check_flag = 1) = 0;

	virtual int  Clear__ALL_LOT_INFO() = 0;
	virtual int  Clear__LOT_INFO(const CString& lotid) = 0;

	virtual int  Inc__INNO_Of_LOT_INFO(const CString& lotid)  = 0;
	virtual int  Inc__OUTNO_Of_LOT_INFO(const CString& lotid) = 0;

	virtual int  Get__INNO_Of_LOT_INFO(const CString& lotid)  = 0;
	virtual int  Get__OUTNO_Of_LOT_INFO(const CString& lotid) = 0;

	virtual int  Get__LOT_INFO_LIST(CStringArray& l_lotid,
									CStringArray& l_inno,
									CStringArray& l_outno) = 0;

	virtual int  Set__PMx_USE_FLAG(const int pm_id,const int use_flag) = 0;
	virtual int  Check__PMx_USE_FLAG(const int pm_id) = 0;

	virtual int  Set__LBA_S2F87_REQ()   = 0;
	virtual int  Clear__LBA_S2F87_REQ() = 0;
	virtual int  Check__LBA_S2F87_REQ() = 0;

	virtual int  Set__LBB_S2F87_REQ()   = 0;
	virtual int  Clear__LBB_S2F87_REQ() = 0;
	virtual int  Check__LBB_S2F87_REQ() = 0;

	virtual int  Set__PMx__PROC_DUMMY_TYPE(const int pm_id) = 0;
	virtual int  Set__PMx__PROC_NORMAL_TYPE(const int pm_id) = 0;
	virtual int  Check__PMx__PROC_DUMMY_TYPE(const int pm_id) = 0;

	virtual int  Update__PRC_DATA_DB(const CString& str_dir,
									 const CString& str_file) = 0;

	virtual int  Save__PMC_DATA(const CString& jobid,
								const CString& lotid,
								const CString& glsid,
								const int port_id,
								const int slot_id,
								const int pmc_id) = 0;
	virtual int  Get__PMC_DATA(const CString& jobid,
							   const CString& lotid,
							   const CString& glsid,
							   const int port_id,
							   const int slot_id,
							   const int pmc_id,
							   CStringArray& l_exp_name,
							   CStringArray& l_ch_data) = 0;

	virtual int  Set__LBA_PIO_TRANSFER(const int pio_sts) = 0;
	virtual int  Check__LBA_PIO_TRANSFER() = 0;
	
	virtual int  Set__LBB_PIO_TRANSFER(const int pio_sts) = 0;
	virtual int  Check__LBB_PIO_TRANSFER() = 0;

	virtual int  Set__GLS__START_INFO(const CString& cur_pos,
							          const CString& start_module,
									  const CString& start_time) = 0;
	virtual int  Get__GLS__START_INFO(const CString& cur_pos,
							          CString& start_module,
									  CString& start_time) = 0;

	virtual int  Save__LOT_DATA(const CString& lotid,
								const int port_id,
								const int slot_id,
								const int pmc_id) = 0;
	virtual int  Get__LOT_DATA(const CString& lotid,
							   CUIntArray&    l_portid,
							   CUIntArray&    l_slotid,
							   CUIntArray&    l_pmcid,
							   CStringArray&  l_exp_name,
							   CStringArray&  l_ch_data) = 0;

	virtual int  Get__GLS__LOT_INFO(const CString& gls_lotid,
									CString& start_time,
									CString& tack_time,
									int& gls_count) = 0;

	virtual int  Set__LBA_SUB_UNITID(const int id) = 0;
	virtual int  Set__LBB_SUB_UNITID(const int id) = 0;
	virtual int  Set__TMC_SUB_UNITID(const int id) = 0;
	virtual int  Set__PMC_SUB_UNITID(const int pm_id,const int id) = 0;

	virtual int  Get__LBA_SUB_UNITID(int &id) = 0;
	virtual int  Get__LBB_SUB_UNITID(int &id) = 0;
	virtual int  Get__TMC_SUB_UNITID(int &id) = 0;
	virtual int  Get__PMC_SUB_UNITID(const int pm_id,int &id) = 0;

	virtual int  Check__LBA_SUB_UNITID(const int id) = 0;
	virtual int  Check__LBB_SUB_UNITID(const int id) = 0;
	virtual int  Check__TMC_SUB_UNITID(const int id) = 0;
	virtual int  Check__PMC_SUB_UNITID(const int pm_id,const int id) = 0;

	virtual int  Set__PMx_UNLOAD_MATERIAL(const int pm_id,const int exist_flag) = 0;
	virtual int  Check__PMx_UNLOAD_MATERIAL(const int pm_id) = 0;

	virtual int  Set__PMx_S2F87_REQ(const int pm_id)   = 0;
	virtual int  Clear__PMx_S2F87_REQ(const int pm_id) = 0;
	virtual int  Check__PMx_S2F87_REQ(const int pm_id) = 0;

	virtual int  Set__PMx_PIO_TRANSFER(const int pm_id,const int pio_sts) = 0;
	virtual int  Check__PMx_PIO_TRANSFER(const int pm_id) = 0;

	virtual int  Set__LBA_AVAILABLE(const int sts = 1) = 0;
	virtual int  Check__LBA_AVAILABLE() = 0;

	virtual int  Set__LBB_AVAILABLE(const int sts = 1) = 0;
	virtual int  Check__LBB_AVAILABLE() = 0;

	virtual int  Set__TMC_AVAILABLE(const int sts = 1) = 0;
	virtual int  Check__TMC_AVAILABLE() = 0;

	virtual int  Set__PMx_AVAILABLE(const int pm_id,const int sts = 1) = 0;
	virtual int  Check__PMx_AVAILABLE(const int pm_id) = 0;

	virtual int  Get__GLS_LOT_END_REQ_FROM_LOTID(const CString& gls_lotid,IDS__GLS_LOT_END_REQ& gls_lot_end_req) = 0;

	virtual int  Load__GLS_LOT_INFO(const IDS__GLS_LOT_INFO& gls_lot_info) = 0;
	virtual int  Get__GLS_LOT_INFO(const CString& lotid,IDS__GLS_LOT_INFO& gls_lot_info) = 0;

	virtual int  Set__GLS__END_INFO(const CString& cur_pos,
							        const CString& end_module,
									const CString& end_time) = 0;
	virtual int  Get__GLS__END_INFO(const CString& cur_pos,
							        CString& end_module,
									CString& end_time) = 0;
};


// ...
class SCI__FTP_CTRL
{
public:
	virtual ~SCI__FTP_CTRL(){};

	// ...
	virtual bool FTP_CTRL__Connect(LPCSTR ip,
								   int port, 
								   LPCSTR id, 
								   LPCSTR pass,
								   bool passive_mode) = 0;
	virtual bool FTP_CTRL__Disconnect() = 0;
	virtual bool FTP_CTRL__IsConnected() = 0;

	virtual bool FTP_CTRL__Compress(LPCSTR dst_file, 
								    LPCSTR src_file) = 0;
	virtual bool FTP_CTRL__Send(const CString& dst_folder,
								LPCSTR dst_file, 
								LPCSTR src_file,
								bool overwrite) = 0;
	virtual void FTP_CTRL__GetProgress(int& cur_progress) = 0;

	virtual void FTP_CTRL__GetErrorMessage(int err_code,
										   CString& err_msg) = 0;
	virtual void FTP_CTRL__GetErrorMessage(CString& err_msg) = 0;

	virtual int  FTP_CTRL__Disable_CREATE_DIRECTORY() = 0;
	virtual int  FTP_CTRL__Enable_CREATE_DIRECTORY() = 0;

	virtual int  FTP_CTRL__Set_UNIX_TYPE() = 0;
	virtual int  FTP_CTRL__Set_WIN_TYPE() = 0;

};


// ...
class CDS__LOT_HEADER_INFO
{
public:
	CString sLOTID;
	CString sLPxID;
	CString sCSTID;
	
	CString sMapSlotList;
	CString sJobSlotList;
	CString sRunSlotList;
	
	CString sJob_StartTime;
	CString sJob_EndTime;
	CString sJob_Result;
};

class CDS__LOT_SLOT_INFO
{
public:
	CString sLOTID;
	CString sWAFERID;
	CString sROUTE_RCP;
				
	CString sPMC_ID;
	CString sRCP_NAME;
	CString sRCP_TIME;
	CString sPROC_RESULT;
};

class SCI__LOT_LOG_CTRL
{
public:
	virtual ~SCI__LOT_LOG_CTRL(){};
	
	// ...
	virtual int  Enable__LOG_CTRL()  = 0;	   // Default
	virtual int  Disable__LOG_CTRL() = 0;

	// ...
	virtual int  Set__DIR_LOG(const CString& dir_log) = 0;
	virtual int  Set__DATE_LIMIT(const int limit) = 0;

	virtual int  Init__LOG_CTRL() = 0;

	// ...
	virtual int  Create__LOG_NAME(const CDS__LOT_HEADER_INFO& ds_info) = 0;
    
	virtual int  Register__SLOT_INFO(const int i_portid,const int i_slotid, const CDS__LOT_SLOT_INFO& ds_info) = 0;
	
	virtual int  Register__LOT_COMPLETED(const CString& str_lotid) = 0;
	virtual int  Register__LOT_ABORTED(const CString& str_lotid) = 0;
	
	virtual int  Clear__LOG_NAME(const CString& str_lotid) = 0;
};

