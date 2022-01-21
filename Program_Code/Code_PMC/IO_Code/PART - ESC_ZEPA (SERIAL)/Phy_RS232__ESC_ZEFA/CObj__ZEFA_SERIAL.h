#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_DEF.h"

#include "CObj__ZEFA_SERIAL__ALID.h"
#include "CObj__ZEFA_SERIAL__DEF.h"


class CObj__ZEFA_SERIAL : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	int iActive__SIM_MODE;

	// ...
	SCX__SERIAL	mX_Serial;

	CString sPROTOCOL_INFO;

	CString sEND_SEND;
	CString sEND_RECV;
	//

	//-------------------------------------------------------------------------
	SCX__USER_LOG_CTRL xI__APP_LOG_CTRL;
	SCX__USER_LOG_CTRL xI__DRV_LOG_CTRL;

	void Write__APP_LOG(const CString& log_msg);
	void Write__DRV_LOG(const CString& log_msg);
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// OBJ ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL  sCH__COMM_STS;

	// CFG ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_DRV_LOG_ENABLE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_CURRENR_LIMIT_CH1;
	CX__VAR_ANALOG_CTRL  aCH__CFG_CURRENR_LIMIT_CH2;

	CX__VAR_ANALOG_CTRL  aCH__CFG_RAMP_UP_SEC;
	CX__VAR_ANALOG_CTRL  aCH__CFG_RAMP_DOWN_SEC;

	CX__VAR_DIGITAL_CTRL dCH__CFG_AUTO_TOGGLE_USE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_AUTO_TOGGLE_COUNT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_AUTO_TOGGLE_VOLTAGE;

	// PARA ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_CURRENT_LIMIT_CH1;
	CX__VAR_ANALOG_CTRL  aCH__PARA_CURRENT_LIMIT_CH2;

	CX__VAR_ANALOG_CTRL  aCH__PARA_VOLT_SET_CH1;
	CX__VAR_ANALOG_CTRL  aCH__PARA_VOLT_SET_CH2;

	CX__VAR_ANALOG_CTRL  aCH__PARA_RAMP_UP_SEC;
	CX__VAR_ANALOG_CTRL  aCH__PARA_RAMP_DOWN_SEC;

	// RCP ...
	CX__VAR_ANALOG_CTRL  aCH__RCP_VOLT_SET_CH1;
	CX__VAR_ANALOG_CTRL  aCH__RCP_VOLT_SET_CH2;

	CX__VAR_ANALOG_CTRL  aCH__RCP_RAMP_UP_SEC;
	CX__VAR_ANALOG_CTRL  aCH__RCP_RAMP_DOWN_SEC;

	// CUR ...
	CX__VAR_STRING_CTRL  sCH__CUR_REMOTE_STATE;

	CX__VAR_STRING_CTRL  sCH__CUR_VOLT_SET_CH1;
	CX__VAR_STRING_CTRL  sCH__CUR_VOLT_SET_CH2;

	CX__VAR_STRING_CTRL  sCH__CUR_CURRENT_LIMIT_CH1;
	CX__VAR_STRING_CTRL  sCH__CUR_CURRENT_LIMIT_CH2;

	// INFO.STS ...
	CX__VAR_STRING_CTRL  sCH__INFO_STS_VOLT_CH1;
	CX__VAR_STRING_CTRL  sCH__INFO_STS_VOLT_CH2;
	CX__VAR_STRING_CTRL  sCH__INFO_STS_CURRENT_CH1;
	CX__VAR_STRING_CTRL  sCH__INFO_STS_CURRENT_CH2;
	CX__VAR_STRING_CTRL  sCH__INFO_STS_OUTPUT;
	CX__VAR_STRING_CTRL  sCH__INFO_STS_TOGGLE;
	CX__VAR_STRING_CTRL  sCH__INFO_STS_REMOTE;

	// INFO.CFG ...
	CX__VAR_STRING_CTRL  sCH__INFO_CFG_VOLT_CH1;
	CX__VAR_STRING_CTRL  sCH__INFO_CFG_VOLT_CH2;

	CX__VAR_STRING_CTRL  sCH__INFO_CFG_CURR_LIMIT_CH1;
	CX__VAR_STRING_CTRL  sCH__INFO_CFG_CURR_LIMIT_CH2;

	CX__VAR_STRING_CTRL  sCH__INFO_CFG_RAMP_UP_SEC;
	CX__VAR_STRING_CTRL  sCH__INFO_CFG_RAMP_DOWN_SEC;

	CX__VAR_STRING_CTRL  sCH__INFO_AUTO_TOGGLE_COUNT;
	CX__VAR_STRING_CTRL  sCH__INFO_AUTO_TOGGLE_VOLTAGE;

	CX__VAR_STRING_CTRL  sCH__INFO_VERSION_FIRMWARE;
	CX__VAR_STRING_CTRL  sCH__INFO_VERSION_SOFTWARE;

	// INFO.ERROR ...
	CX__VAR_STRING_CTRL  sCH__INFO_ERROR_ID;
	CX__VAR_STRING_CTRL  sCH__INFO_ERROR_LINE_X[_CFG__ERR_LINE_MAX];

	// INFO.DRV ...
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_COM_PORT;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_BAUD_RATE;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_DATA_BIT;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_STOP_BIT;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_PARITY;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_END_SEND;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_END_RECV;
	//

	//-------------------------------------------------------------------------
	// IO CHANNEL ...

	// DO
	CX__VAR_DIGITAL_CTRL doCH__OUTPUT_SET;	
	CX__VAR_DIGITAL_CTRL doCH__TOGGLE_SET;	
	CX__VAR_DIGITAL_CTRL doCH__REMOTE_SET;

	CX__VAR_DIGITAL_CTRL doCH__ALL_VOLT_SET;

	CX__VAR_DIGITAL_CTRL doCH__ERROR_CLEAR;
	CX__VAR_DIGITAL_CTRL doCH__SYSTEM_RESET;

	// SO
	CX__VAR_STRING_CTRL  soCH__CURRENT_LIMIT_SET;

	CX__VAR_STRING_CTRL  soCH__RAMP_UP_SET;
	CX__VAR_STRING_CTRL  soCH__RAMP_DOWN_SET;

	CX__VAR_STRING_CTRL  soCH__AUTO_TOGGLE_CNT_SET;
	CX__VAR_STRING_CTRL  soCH__AUTO_TOGGLE_VOLT_SET;

	// SI 
	CX__VAR_STRING_CTRL  siCH__STATE_READ;
	CX__VAR_STRING_CTRL  siCH__ERROR_READ;

	CX__VAR_STRING_CTRL  siCH__CFG_VOLT_ALL;	
	CX__VAR_STRING_CTRL  siCH__CFG_CURR_LIMIT_ALL;	
	CX__VAR_STRING_CTRL  siCH__CFG_RAMP_UP;
	CX__VAR_STRING_CTRL  siCH__CFG_RAMP_DOWN;

	CX__VAR_STRING_CTRL  siCH__AUTO_TOGGLE_INFO;
	CX__VAR_STRING_CTRL  siCH__ALL_VERSION_INFO;
	//


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__LOCAL;
	int  Call__LOCAL(CII_OBJECT__VARIABLE*	p_variable,	CII_OBJECT__ALARM* p_alarm);

	CString sMODE__REMOTE;
	int  Call__REMOTE(CII_OBJECT__VARIABLE*	p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__RESET;
	int  Call__RESET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__ALARM_CLEAR;
	int  Call__ALARM_CLEAR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__ON;
	int  Call__ON(CII_OBJECT__VARIABLE*	p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__OFF;
	int  Call__OFF(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM*	p_alarm);

	//
	CString sMODE__TOGGLE_ON;
	CString sMODE__TOGGLE_OFF;
	int  Call__TOGGLE(CII_OBJECT__VARIABLE*	p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_on);

	//
	CString sMODE__CURRENT_LIMIT_SET;
	int  Call__CURRENT_LIMIT_SET(CII_OBJECT__VARIABLE*	p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__RAMP_UP_SET;
	int  Call__RAMP_UP_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__RAMP_DOWN_SET;
	int  Call__RAMP_DOWN_SET(CII_OBJECT__VARIABLE*	p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__PROC_READY;
	int  Call__PROC_READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PROC_START;
	int  Call__PROC_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM*	p_alarm);

	int  FNC__ON_SEQ(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	
	// ...
	int _Send_Command(const CString& var_name, const CString& s_cmmd);
	int _Recv_Command(CString* p_data);

	int _Update__INFO_STS(const CString& r_data);
	int _Update__CFG_VOLT(const CString& r_data);
	int _Update__CFG_CURRENT_LIMIT(const CString& r_data);

	// ...
	void Mon__STATE_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	void Fnc__ERROR_CHECK(CII_OBJECT__ALARM* p_alarm);

	// ...
	void Fnc__Do_Abort(CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj__ZEFA_SERIAL();
	~CObj__ZEFA_SERIAL();

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

