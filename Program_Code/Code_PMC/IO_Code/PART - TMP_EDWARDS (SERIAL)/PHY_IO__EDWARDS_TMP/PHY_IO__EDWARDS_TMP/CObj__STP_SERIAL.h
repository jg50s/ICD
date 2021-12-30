#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__STP_SERIAL__ALID.h"
#include "CObj__STP_SERIAL__DEF.h"


class CObj__STP_SERIAL : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xAPP_LOG_CTRL;
	SCX__USER_LOG_CTRL xDRV_LOG_CTRL;

	int iACTIVE_SIM;

	// ...
	SCX__SERIAL_JG	mX_Serial;

	int	 m_nCommState;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// ...
	CX__VAR_DIGITAL_CTRL dCH__OBJ_STATUS;
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	CX__VAR_STRING_CTRL  sCH__MON_COMM_STS;
	CX__VAR_STRING_CTRL  sCH__MON_PUMP_STS;
	CX__VAR_STRING_CTRL  sCH__MON_ERROR_STS;

	CX__VAR_ANALOG_CTRL  aCH__CFG_TARGET_SPEED_RPM;

	CX__VAR_ANALOG_CTRL  aCH__CFG_STOP_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_ACCEL_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_TARGET_SPEED_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_MON_INTERVAL;

	// ...
	CX__VAR_STRING_CTRL  sCH__INFO_ROT_SPEED_HZ;
	CX__VAR_STRING_CTRL  sCH__INFO_ROT_SPEED_RPM;

	CX__VAR_STRING_CTRL  sCH__INFO_PUMP_OP_MODE;
	CX__VAR_STRING_CTRL  sCH__INFO_ERROR_COUNT;

	CX__VAR_STRING_CTRL  sCH__INFO_VERSION__CTRL_UNIT;
	CX__VAR_STRING_CTRL  sCH__INFO_VERSION__MTR_DRV;
	CX__VAR_STRING_CTRL  sCH__INFO_VERSION__AMB_SW;

	CX__VAR_STRING_CTRL  sCH__INFO_SPEED_SETPOINT_HZ;
	CX__VAR_STRING_CTRL  sCH__INFO_SPEED_SETPOINT_RPM;
	CX__VAR_STRING_CTRL  sCH__INFO_TMS_TEMPERATURE_SETTING;
	//

	//-------------------------------------------------------------------------
	// IO CHANNEL 

	// AO ...
	CX__VAR_ANALOG_CTRL aoCH__SET_SPEED_HZ;

	// DO ...
	CX__VAR_DIGITAL_CTRL doCH__OP_CMMD;

	// DI  ...
	CX__VAR_DIGITAL_CTRL diCH__COMM_STS;

	// SI ...
	CX__VAR_STRING_CTRL  siCH__ReadMeas_HEXA;
	CX__VAR_STRING_CTRL  siCH__ReadModFonct;
	CX__VAR_STRING_CTRL  siCH__All_Version;
	CX__VAR_STRING_CTRL  siCH__ReadSetPoint;
	CX__VAR_STRING_CTRL  siCH__ReadMotorTemp;
	//


	//-------------------------------------------------------------------------
	// Init ----
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Fnc__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// Pump On -----
	CString sMODE__PUMP_ON;
	int  Call__PUMP_ON(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// Auto Stop -----
	CString sMODE__AUTO_STOP;
	int  Call__AUTO_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Fnc__AUTO_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__AUTO_STOP_NO_WAIT;
	int  Call__AUTO_STOP_NO_WAIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Fnc__AUTO_STOP_NO_WAIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// CHECK_SUM -----
	CString sMODE__CHECK_SUM;
	int  Call__CHECK_SUM(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//

	//-------------------------------------------------------------------------
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	int  Is__OFFLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	void Fnc__APP_LOG(const CString& log_msg);
	void Fnc__DRV_LOG(const CString& log_msg);

	// ...
	int  Recv_Command(const CString& var_name, const CString& s_cmmd, CString& r_data);
	byte _Get__CheckSum(const unsigned char* s_cmmd, const int s_len);

	CString _Get__Error_Message(const int err_value);
	//


public:
	CObj__STP_SERIAL();
	~CObj__STP_SERIAL();

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
};
