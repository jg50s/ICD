#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__UNIT_TYPE__ALID.h"
#include "CObj__UNIT_TYPE__DEF.h"


class CDB__ALARM_INFO
{
public:
	int iALM_ID;
	int iGAS_ID;
	CString sALM_MSG;
};

class CDB__ALARM_CTRL
{
private:
	CRITICAL_SECTION mCS_LOCK;
	CPtrArray pList_INFO;

public:
	CDB__ALARM_CTRL();
	~CDB__ALARM_CTRL();

	// ...
	void Load__ALM_OFFLINE(const int gas_id,const int gas_index, const CString& alm_msg);
	void Load__ALM_CTRL_TIMEOUT(const int gas_id,const int gas_index, const CString& alm_msg);

	int  Get__ALM_INFO(int& alm_id, int& gas_id,CString& alm_msg);
};


class CObj__UNIT_TYPE : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	// ...
	SCX__USER_LOG_CTRL xDRV_LOG_CTRL;
	int iActive__SIM_MODE;

	// ...
	SCX__SERIAL	mX_Serial;

	// ...
	char m_Term_Str[4];
	int	 m_nCommState;
	int	 m_Rcv_Time;

	int m_nRetryCnt;

	int iFlag__DRV_LOG;

	int	m_BoardID;

	int	m_nSubOnline[MAX_MFC];
	CString m_szFirm_Revision[MAX_MFC];

	CDB__ALARM_CTRL mDB__ALM_CTRL;

	// ...
	CStringArray sList__MAC_ID;
	CStringArray sList__VAR_ID;
	//


	// ---------------------------------------------------------------------------------------------
	// INTERNAL PARAMETER ... 

	CX__VAR_DIGITAL_CTRL dCH__DRV_LOG_PARAM_START_STOP;
	CX__VAR_ANALOG_CTRL  aCH__DRV_READ_DELAY_TIME_MSEC;

	CX__VAR_STRING_CTRL  sCH__ALM_TEST__OFFLINE;
	CX__VAR_STRING_CTRL  sCH__ALM_TEST__TIMEOUT;

	CX__VAR_DIGITAL_CTRL dCH__CFG_BAUD_RATE_NEXT_APPLY;
	CX__VAR_STRING_CTRL  sCH__CUR_BAUD_RATE_APPLIED;


	// ---------------------------------------------------------------------------------------------
	// EXTERNAL PARAMETER ... 

	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_MFC_485_SETPOINT_READ_CONFIRM_USE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_MFC_485_COMM_OFFLINE_ALARM_USE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_MFC_485_CONTROL_TIMEOUT_ALARM_USE;
	// 


	// ---------------------------------------------------------------------------------------------
	void Mon__STATE_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	unsigned char CheckSum(unsigned char * str_data,const int nStart,const int nSize);

	int Is__OFFLINE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm,const int nGas_Num);

	// ...
	int SendCommand(const int flag_s_cmmd,
					const int retry_flag,
					unsigned char * szSendData, 
					const int nLength, 
					unsigned char *szRecvData, 
					int nRecvSize, 
					const int nPaddingSize,
					const int mac_id,
					const int mfc_index,
					const int cmd_id);

	int _SendCommand(const int flag_s_cmmd,
					const int retry_flag,
					unsigned char * szSendData, 
					const int nLength, 
					unsigned char *szRecvData, 
					int nRecvSize, 
					const int nPaddingSize,
					const int mac_id,
					const int mfc_index,
					const int cmd_id);

	void Fnc__DRV_LOG(const CString& log_msg);
	//


public:
	CObj__UNIT_TYPE();
	~CObj__UNIT_TYPE();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);	
	int __DEFINE__ALARM(p_alarm);

	int __DEFINE__VARIABLE_IO(p_io_variable);

	//-------------------------------------------------------------------------	
	int __INITIALIZE__OBJECT(p_variable, p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------	
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);

	int __CLOSE__OBJECT();

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);

	// ...
	int Fnc__FLOW_SETPOINT_SET(const int cmd_id,const int mac_id,const int mfc_index, const double set_data,const double min,const double max);
	int Fnc__FLOW_SETPOINT_GET(const int cmd_id,const int mac_id,const int mfc_index, const double max, double& read_data);

	int Fnc__VALVE_CONTROL_SET(const int ctrl_mode, const int cmd_id,const int mac_id,const int mfc_index);
};
