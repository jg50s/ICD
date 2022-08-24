#pragma once

#include "Interface_Code.h"

#include "CObj__ESC_SERIAL__ALID.h"
#include "CObj__ESC_SERIAL__DEF.h"


class CObj__ESC_SERIAL : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	SCX__USER_LOG_CTRL xI__APP_LOG_CTRL;
	SCX__USER_LOG_CTRL xI__DRV_LOG_CTRL;

	int iActive__SIM_MODE;

	// ...
	SCX__SERIAL_JG mX_Serial;

	CString sPROTOCOL_INFO;

	bool bActive__COMM_ONLINE;
	//

	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// OBJ ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_COM_PORT;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_PARAMETER;

	// PARA ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_VOLTAGE_SET;
	CX__VAR_ANALOG_CTRL  aCH__PARA_CURRENT_LIMIT_SET;

	CX__VAR_ANALOG_CTRL  aCH__PARA_RAMP_UP_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_RAMP_DN_TIME;

	// CFG ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_CURRENT_LIMIT_SET;

	CX__VAR_ANALOG_CTRL  aCH__CFG_RAMP_UP_TIME;
	CX__VAR_ANALOG_CTRL  aCH__CFG_RAMP_DN_TIME;

	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_COMM_STS;

	CX__VAR_STRING_CTRL  sCH__MON_VOLTAGE_SETPOINT;
	CX__VAR_STRING_CTRL  sCH__MON_CURRENT_LIMIT_SETPOINT;

	CX__VAR_STRING_CTRL  sCH__MON_VOLTAGE_READ;
	CX__VAR_STRING_CTRL  sCH__MON_CURRENT_READ;
	//

	//-------------------------------------------------------------------------
	// IO CHANNEL ...

	// AO
	CX__VAR_ANALOG_CTRL  aoCH__VOLTAGE_SET;
	CX__VAR_ANALOG_CTRL  aoCH__CURRENT_LIMIT_SET;
	CX__VAR_ANALOG_CTRL  aoCH__RAMP_UP_SET;
	CX__VAR_ANALOG_CTRL  aoCH__RAMP_DN_SET;

	// SI
	CX__VAR_STRING_CTRL  siCH__VOLTAGE_READ;
	CX__VAR_STRING_CTRL  siCH__CURRENT_READ;

	// DO
	CX__VAR_DIGITAL_CTRL doCH__CONTROL_MODE;		// Local  Remote
	CX__VAR_DIGITAL_CTRL doCH__ECHO_MODE;			// Off  On

	CX__VAR_DIGITAL_CTRL doCH__VOLTAGE_MODE;		// Positive(+)  Negative(-)
	CX__VAR_DIGITAL_CTRL doCH__VOLTAGE_POWER;		// Off  On
	//


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__LOCAL;
	int  Call__LOCAL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__REMOTE;
	int  Call__REMOTE(CII_OBJECT__VARIABLE*	p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__ON;
	int  Call__ON(CII_OBJECT__VARIABLE*	p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__OFF;
	int  Call__OFF(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM*	p_alarm);

	//
	CString sMODE__RAMP_UP;
	int  Call__RAMP_UP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active__cfg_set);

	CString sMODE__RAMP_DOWN;
	int  Call__RAMP_DOWN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active__cfg_set);

	//
	CString sMODE__POSITIVE;
	int  Call__POSITIVE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__NEGATIVE;
	int  Call__NEGATIVE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__VOLTAGE_SET;
	int Call__VOLTAGE_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__CURRENT_LIMIT_SET;
	int Call__CURRENT_LIMIT_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active__cfg_set);

	//
	CString sMODE__PACKET_CHECK;
	int Call__PACKET_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	//

	// ...
	void Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//

	// ...
	int SEND_COMMAND(const CString& var_name, const CString& s_cmd, CString& r_data);

	CString _Get__NOT_NUMBER_LEFT_TRIM(const CString& str_data);
	//


public:
	CObj__ESC_SERIAL();
	~CObj__ESC_SERIAL();

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

