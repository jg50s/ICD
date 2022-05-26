#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__iTIM_TYPE__ALID.h"
#include "CObj__iTIM_TYPE__DEF.h"



class CObj__iTIM_TYPE : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xAPP_LOG_CTRL;
	SCX__USER_LOG_CTRL xDRV_LOG_CTRL;

	// ...
	SCX__SERIAL	mX_Serial;

	int iACTIVE_SIM;

	// ...
	char m_Term_Str[3];
	int	 m_nCommState;
	int	 m_Rcv_Time;

	int  iFlag__APP_LOG;
	int  iFlag__DRV_LOG;

	CString m_str_cmd_err;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// CFG : SYSTEM ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_PART_USE;

	//
	CX__VAR_DIGITAL_CTRL dCH__OBJ_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__DRV_LOG_PARAM_START_STOP;

	CX__VAR_STRING_CTRL  sCH__SEQUENCE_MSG;

	CX__VAR_STRING_CTRL  sCH__COMM_STS;
	CX__VAR_STRING_CTRL  sCH__PUMP_STS;

	CX__VAR_STRING_CTRL  sCH__CFG_SKIP_MODE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_AUTO_STOP_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_FAST_STOP_TIMEOUT;

	CX__VAR_DIGITAL_CTRL dCH__CFG_PUMP_CTRL_MODE;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_COM_PORT;	  
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_BAUD_RATE;	  
	//

	//-------------------------------------------------------------------------
	// DO  ----------
	CX__VAR_DIGITAL_CTRL doCH__CTRL_MODE;
	CX__VAR_DIGITAL_CTRL doCH__RUN_STOP;

	// DI  ----------
	CX__VAR_DIGITAL_CTRL diCH__COMM_STS;
	CX__VAR_DIGITAL_CTRL diCH__CTRL_STS;
	CX__VAR_DIGITAL_CTRL diCH__PUMP_STS;

	// SI ---------
	CX__VAR_STRING_CTRL siCH__CMD_ERR;
	CX__VAR_STRING_CTRL siCH__ELEC_SUPPLY_VOLT;
	CX__VAR_STRING_CTRL siCH__PHASE_CURRENT;
	CX__VAR_STRING_CTRL siCH__PUMP_POWER;
	CX__VAR_STRING_CTRL siCH__VOLT_READ_THERMISTOR;

	CX__VAR_STRING_CTRL siCH__TOTAL_RUN_TIME;
	CX__VAR_STRING_CTRL siCH__TIME_TO_STOP;
	CX__VAR_STRING_CTRL siCH__TOTAL_N2;
	CX__VAR_STRING_CTRL siCH__EXHAUST_PRESS;
	CX__VAR_STRING_CTRL siCH__N2_SUPPLY_STS;
	CX__VAR_STRING_CTRL siCH__INLET_PURGE_STS;
	CX__VAR_STRING_CTRL siCH__MOTOR_TEMP;
	CX__VAR_STRING_CTRL siCH__BODY_TEMP;
	CX__VAR_STRING_CTRL siCH__WATER_FLOW_STS;
	//


	//-------------------------------------------------------------------------
	// Init ----
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Fnc__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// Local -----
	CString sMODE__LOCAL;
	int  Call__LOCAL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Fnc__LOCAL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// Remote -----
	CString sMODE__REMOTE;
	int  Call__REMOTE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Fnc__REMOTE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// Pump On -----
	CString sMODE__PUMP_ON;
	int  Call__PUMP_ON(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Fnc__PUMP_ON(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// Auto Stop -----
	CString sMODE__AUTO_STOP;
	int  Call__AUTO_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Fnc__AUTO_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// Fast Stop ------
	CString sMODE__FAST_STOP;
	int  Call__FAST_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Fnc__FAST_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//


	//-------------------------------------------------------------------------
	// ...
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	
	// ...
	int  Is__REMOTE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Is__OFFLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	void Fnc__APP_LOG(const CString& log_msg);
	void Fnc__DRV_LOG(const CString& log_msg);

	void Fnc__DATA_PARSING(const CString var_name, const CString str__read_req_data, CString& str_final_data);
	void Fnc__DRV_CMD_ERR(const CString var_name, const CString str_get_err);

	int  Fnc__CMD_ERR_Check(CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj__iTIM_TYPE();
	~CObj__iTIM_TYPE();

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
