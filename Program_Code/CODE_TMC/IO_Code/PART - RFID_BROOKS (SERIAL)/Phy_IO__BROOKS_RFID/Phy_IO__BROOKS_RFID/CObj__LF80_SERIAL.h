#pragma once

#include "Interface_Code.h"

#include "CCommon_System.h"
#include "CCommon_Error.h"


#define CFG__PAGE_SIZE				17


class CObj__LF80_SERIAL : public __IOBJ__IO_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//-------------------------------------------------------------------------
	CString	sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;

	// ...
	SCX__SERIAL	mX_Serial;

	char m_Term_Str[3];
	int	 m_nCommState;
	int	 m_Rcv_Time;
	int  m_nTimeout;
	int  m_nRetryCount;

	// ...
	int  iFlag_Log;
	int  iSim_Flag;

	CString sSTR__ERROR_VALUE;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// VIRTUAL CHANNEL
	CX__VAR_DIGITAL_CTRL  dCH__OTR_IN_LP__FA_MODE;
	CX__VAR_DIGITAL_CTRL  dCH__OTR_IN_LP__FA_SERVICE_MODE;

	CX__VAR_STRING_CTRL  sCH__MSG;

	CX__VAR_ANALOG_CTRL  aCH__PAGE1_NUM;
	CX__VAR_ANALOG_CTRL  aCH__PAGE2_NUM;

	CX__VAR_STRING_CTRL  sCH__READ_PAGE_DATA;
	CX__VAR_STRING_CTRL  sCH__WRITE_PAGE_DATA;

	CX__VAR_STRING_CTRL  sCH__READ_MID_PAGE_DATA;
	CX__VAR_STRING_CTRL  sCH__WRITE_MID_PAGE_DATA;

	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_READ_PAGE1_AND_2_ONLY;
	CX__VAR_DIGITAL_CTRL dCH__CFG_TAG_READ_ID_INSTALLED_CHECK_SKIP;

	CX__VAR_ANALOG_CTRL aCH__CFG_TAG_PARAM_READ_MODE;
	CX__VAR_ANALOG_CTRL aCH__CFG_TAG_PARAM_READ_PAGE;
	CX__VAR_ANALOG_CTRL aCH__CFG_TAG_PARAM_RS232_MAX_REPEAT;
	CX__VAR_ANALOG_CTRL aCH__CFG_TAG_PARAM_RS232_REPEAT_TIME;
	CX__VAR_ANALOG_CTRL aCH__CFG_TAG_PARAM_RW_MAX_REPEAT;
	CX__VAR_ANALOG_CTRL aCH__CFG_TAG_PARAM_RW_REPEAT_TIME;
	CX__VAR_ANALOG_CTRL aCH__CFG_TAG_PARAM_WATCH_PORT;

	CX__VAR_DIGITAL_CTRL dCH__DEVICE_ADDRESS;

	// ...
	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_INFO;
	//


	// IO CHANNEL  -----------------------------------
	// DO  ----------
	CX__VAR_DIGITAL_CTRL doCH__HEART_BEAT;

	// DI  ----------
	CX__VAR_DIGITAL_CTRL diCH__FAILURE_CODE;

	// SO  ----------
	CX__VAR_STRING_CTRL  soCH__WRITE_PAGE_DATA[CFG__PAGE_SIZE];

	// SI  ----------
	CX__VAR_STRING_CTRL  siCH__READ_PAGE_DATA[CFG__PAGE_SIZE];


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__MULTI_PAGE_READ;
	int  Call__MULTI_PAGE_READ(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PAGE_READ;
	int  Call__PAGE_READ(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__MULTI_PAGE_WRITE;
	int  Call__MULTI_PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PAGE_WRITE;
	int  Call__PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__MID_WRITE;
	int  Call__MID_WRITE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__MID_READ;
	int  Call__MID_READ(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);


	//-------------------------------------------------------------------------
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	int Fnc__Check_Online(CII_OBJECT__ALARM* p_alarm, const CString szCtrl_Mode);

	int Fnc__MultPage_Read(CII_OBJECT__ALARM* p_alarm,
							const int min_page_index, 
							const int max_page_index,
							CString *page_data,
							const CString szCtrl_Mode);

	int Fnc__Page_Read(CII_OBJECT__ALARM* p_alarm,
						const int page_index,
						CString *page_data);

	int Fnc__MultPage_Write(CII_OBJECT__ALARM* p_alarm,
							const int min_page_index,
							const int max_page_index,
							const CString& page_data);

	int Fnc__Page_Write(CII_OBJECT__ALARM* p_alarm,
						const int page_index,
						const CString& page_data);

	int Is__LP_AUTO_MODE();

	// ...
	void Fnc__LOG(const char *fmt, ...);
	void Fnc__MSG(const CString& log_msg);

	CString Fnc__ASCII_Conver(CString data);
	CString Fnc__ASCII_Table(CString data);
	CString Fnc__HEX_Conver(CString data);
	CString Fnc__HEX_Table(CString data);

	// ...
	int Make_CheckSum(const int index,
					  char *data,
					  int *i_cs1_high,
					  int *i_cs1_low,
					  int *i_cs2_high,
					  int *i_cs2_low);

	int Error_Report(const CString& error_code);
	//

public:
	CObj__LF80_SERIAL();
	~CObj__LF80_SERIAL();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj, l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__VARIABLE_IO(p_rs232_variable);

	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm);
	int __CALL__MONITORING(id, p_variable, p_alarm);

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);
};
