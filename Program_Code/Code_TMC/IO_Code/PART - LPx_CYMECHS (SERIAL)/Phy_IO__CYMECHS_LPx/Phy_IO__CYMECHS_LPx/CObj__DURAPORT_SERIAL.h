#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"

#include "CObj__DURAPORT_SERIAL__DEF.h"
#include "CMng__Error_Code.h"


class CMng__RSP_MSG
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CStringArray sList_MSG;

public:
	CMng__RSP_MSG()
	{
		InitializeCriticalSection(&mCS_LOCK);
	}
	~CMng__RSP_MSG()
	{
		DeleteCriticalSection(&mCS_LOCK);
	}

	void Clear__ALL_RSP_MSG()
	{
		EnterCriticalSection(&mCS_LOCK);

		sList_MSG.RemoveAll();

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Load__RSP_MSG(const CString& rsp_msg)
	{
		EnterCriticalSection(&mCS_LOCK);

		sList_MSG.Add(rsp_msg);

		int db_size = sList_MSG.GetSize();
		if(db_size > 10)
		{
			sList_MSG.RemoveAt(10);
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
	int Get__RSP_MSG(CString& rsp_msg)
	{
		EnterCriticalSection(&mCS_LOCK);

		int db_size = sList_MSG.GetSize();
		if(db_size > 0)
		{
			rsp_msg = sList_MSG.GetAt(0);
			sList_MSG.RemoveAt(0);
		}

		LeaveCriticalSection(&mCS_LOCK);
		return db_size;
	}
};

class CObj__DURAPORT_SERIAL : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;	
	SCX__USER_LOG_CTRL xAPP__LOG_CTRL;
	SCX__USER_LOG_CTRL xDRV__LOG_CTRL;

	// ...
	SCX__TIMER_CTRL	xI_TIMER;
	SCX__SEQ_INFO	xSEQ_INFO;

	SCX__SERIAL mX_Serial;
	CMng__RSP_MSG mMng__RSP_MSG;

	int nCh_Fist_Count;

	// ...
	CString sStr_End;

	int m_nCommSts;
	int m_nTimeout;
	int m_nRetryCount;

	CString	m_sErrorCode;
	CString	m_szAlarm;

	int iFlag__APP_LOG;
	int iFlag__DRV_LOG;

	CMng__Error_Code mMNG__ERR_CODE;


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// DB_CFG
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_SIM_MODE;
	CX__VAR_DIGITAL_CTRL dCH__OBJ_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__DRV_LOG_PARAM_START_STOP;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_STRING_CTRL  sCH__SEQUENCE_MSG;

	CX__VAR_DIGITAL_CTRL dCH__LP_STATE;
	CX__VAR_DIGITAL_CTRL dCH__CMD_STATE;

	// ...
	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_INFO;
	//


	//------------------------------------------
	//ANALOG

	//DIGITAL
	//INIT--------------------------------------
	CX__VAR_DIGITAL_CTRL  doCH__ERROR_RESET;
	CX__VAR_DIGITAL_CTRL  doCH__AMP_SET;

	CX__VAR_DIGITAL_CTRL  doCH__LAMP_AUTO_MODE;

	CX__VAR_DIGITAL_CTRL  doCH__UPDATE_SYSTEM;
	CX__VAR_DIGITAL_CTRL  doCH__UPDATE_INDICATOR;
	//------------------------------------------

	// OPR CMD---------------------------------
	CX__VAR_DIGITAL_CTRL  doCH__OPR_LOAD_SET;
	CX__VAR_DIGITAL_CTRL  doCH__OPR_DOCK_SET;
	CX__VAR_DIGITAL_CTRL  doCH__OPR_CLAMP_SET;
	CX__VAR_DIGITAL_CTRL  doCH__OPR_MAIN_SET;
	//-------------------------------------------

	CX__VAR_DIGITAL_CTRL  diCH__COMM_STS;

	CX__VAR_STRING_CTRL   sCH__MON_DOOR_STATUS;
	CX__VAR_STRING_CTRL   sCH__MON_FOUP_POS_STATUS;
	CX__VAR_STRING_CTRL   sCH__MON_FOUP_STATUS;
	CX__VAR_STRING_CTRL   sCH__MON_CLAMP_STATUS;

	CX__VAR_STRING_CTRL   sCH__MON_WFR_SLID_OUT_SNS;
	CX__VAR_STRING_CTRL   sCH__MON_LOAD_BTN_SNS;
	CX__VAR_STRING_CTRL   sCH__MON_UNLOAD_BTN_SNS;

	CX__VAR_STRING_CTRL   sCH__LINK_LAMP_SET[LAMP_MAX];

	CX__VAR_STRING_CTRL   sCH__RES_MAP_SLOT[LPx_SLOT_MAX];
	CX__VAR_STRING_CTRL   sCH__RES_MAP_CROSS_SLOT[LPx_SLOT_MAX];
	CX__VAR_STRING_CTRL   sCH__RES_MAP_DOUBLE_SLOT[LPx_SLOT_MAX];

	CX__VAR_DIGITAL_CTRL  dCH__DOUBLE_CHECK;

	// È£È¯¿ë ...
	CX__VAR_STRING_CTRL   sCH__RSP_PAGE_CID;
	CX__VAR_STRING_CTRL   sCH__RSP_PAGE_DATA;

	CX__VAR_STRING_CTRL   sCH__PARA_PAGE_CID;
	CX__VAR_ANALOG_CTRL   aCH__PARA_PAGE_ID;
	CX__VAR_STRING_CTRL   sCH__PARA_PAGE_DATA;

	// BIT STS ...
	CX__VAR_STRING_CTRL   sCH__BIT_STS__HOMING_COMPLETE;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__MOTOR_DRIVER_ON;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__DOOR_OPENED;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__DOOR_CLOSED;
	
	CX__VAR_STRING_CTRL   sCH__BIT_STS__ACTING_CONDITION;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__BACKUP_DATA_CRASH;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__MAINT_MODE;

	CX__VAR_STRING_CTRL   sCH__BIT_STS__POD_CLAMPED;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__POD_UNCLAMPED;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__POD_DOCKED;

	CX__VAR_STRING_CTRL   sCH__BIT_STS__PAD_UNDOCKED;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__VACUUM_CONDITION;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__LATCH_CONDITION;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__UNLATCH_CONDITION;

	CX__VAR_STRING_CTRL   sCH__BIT_STS__ERROR_OCCURRENCE;

	CX__VAR_STRING_CTRL   sCH__BIT_STS__AMHS_MODE;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__BCR_USAGE;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__MAPPING_USAGE;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__AUTO_MODE;

	CX__VAR_STRING_CTRL   sCH__BIT_STS__Load_Unload_SW_USAGE;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__OPEN_CASSETTE_USAGE;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__LOADPORT_RESERVE;

	CX__VAR_STRING_CTRL   sCH__BIT_STS__PLACEMENT_SENSOR;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__PRESENCE_SENSOR;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__WAFER_SLIDE_SENSOR;
	CX__VAR_STRING_CTRL   sCH__BIT_STS__FAN_IO_CONDITION;

	// BIT INDICATOR ...
	CX__VAR_STRING_CTRL   sCH__INDICATOR_STS__LOAD;
	CX__VAR_STRING_CTRL   sCH__INDICATOR_STS__UNLOAD;
	CX__VAR_STRING_CTRL   sCH__INDICATOR_STS__AUTO;
	CX__VAR_STRING_CTRL   sCH__INDICATOR_STS__MANUAL;
	CX__VAR_STRING_CTRL   sCH__INDICATOR_STS__RESERVE;
	CX__VAR_STRING_CTRL   sCH__INDICATOR_STS__BUTTON;
	//

	// STRING...
	CX__VAR_STRING_CTRL   sCH__MON_FIRMWARE_VER;

	CX__VAR_STRING_CTRL   siCH__FIRMWARE_VER;
	CX__VAR_STRING_CTRL   siCH__ERROR_CODE;

	// ERROR TEST ...
	CX__VAR_DIGITAL_CTRL  dCH__ERROR_TEST__ACTIVE;
	CX__VAR_STRING_CTRL   sCH__ERROR_TEST__ERROR_CODE;
	//

	
	//-------------------------------------------------------------------------
	// INIT --
	CString sMODE__INIT;
	int	 Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString str_caller);
	int  Seq__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString str_caller);

	CString sMODE__HOME;
	int	 Call__HOME(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__HOME(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString str_caller);

	CString sMODE__OPEN;
	int	 Call__OPEN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__OPEN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString str_caller);

	CString sMODE__CLOSE;
	int  Call__CLOSE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__CLOSE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString str_caller);

	CString sMODE__LOAD;
	int	 Call__LOAD(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__LOAD(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString str_caller);

	CString sMODE__UNLOAD;
	int  Call__UNLOAD(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__UNLOAD(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString str_caller);

	CString sMODE__DOCK;
	int	 Call__DOCK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__DOCK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString str_caller);

	CString sMODE__UNDOCK;
	int	 Call__UNDOCK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__UNDOCK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString str_caller);

	CString sMODE__CLAMP;
	int	 Call__CLAMP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__CLAMP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString str_caller);

	CString sMODE__UNCLAMP;
	int	 Call__UNCLAMP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__UNCLAMP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString str_caller);

	// ...
	CString sMODE__MAP;
	int	 Call__MAP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int	 Fnc__MAP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	CString sMODE__CID_READ;
	int	 Call__CID_READ(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int	 Fnc__CID_READ(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PAGE_READ;
	int	 Call__PAGE_READ(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__CID_WRITE;
	int	 Call__CID_WRITE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PAGE_WRITE;
	int	 Call__PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	CString sMODE__AMHS_AUTO;
	int	 Call__AMHS_AUTO(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__AMHS_MANUAL;
	int	 Call__AMHS_MANUAL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__AMHS_HO_ENABLE;
	int	 Call__AMHS_HO_ENABLE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__AMHS_HO_DISABLE;
	int	 Call__AMHS_HO_DISBLE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	CString sMODE__SIM_FOUP_EXIST;
	CString sMODE__SIM_FOUP_NONE;

	// ...
	CString sLastCommand;
	
	// ...
	int Fnc__Display_STS();

	
	//-------------------------------------------------------------------------
	void Mon__STATE_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	void Mon__PROC_RSP_MSG(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);


	//-------------------------------------------------------------------------
	int iSim_Mode;

	// ...
	int Is__ONLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int Is__REMOTE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	void Fnc__APP_LOG(const CString& log_msg);
	void Fnc__DRV_LOG(const CString& log_msg);

	// ...
	bool bSts_Running;
	
	int _Check__ERROR_CODE(const CString& err_code);
	CString _Get__Error_Code(const int err_code);
	int _Get__Error_Info(const int err_code, CString& str_alarm,CString& str_reason,CString& str_action);
	CString _Get__Error_Msg(const int err_code, const CString& str_alarm,const CString& str_reason,const CString& str_action);

	// ...
	int _Proc__RSP_MSG();
	int _Get__STRING_ARRAY(const CString& str_data,const CString& str_delimiter,CStringArray& l_data);

	int _Recv__CMMD(const CString& var_name, const CString& s_data, CString& r_data);

	// ...
	int _Update__SYSTEM_STATUS(const CString& r_data);
	int _Update__SYSTEM_STATUS();

	int _Update__INDICATOR_STATUS(const CString& r_data);
	int _Update__LPx_MAP(const CString& r_data);
	int _Update__LPx_INIT();
	
	int _Get__HEXA_FROM_ASCII(const unsigned char ch_ascii);
	//


public:
	CObj__DURAPORT_SERIAL();
	~CObj__DURAPORT_SERIAL();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__VARIABLE_IO(p_io_variable);

	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);
};
