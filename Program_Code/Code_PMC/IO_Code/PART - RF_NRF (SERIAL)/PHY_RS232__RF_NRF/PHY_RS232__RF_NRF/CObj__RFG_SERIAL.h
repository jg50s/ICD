#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Header.h"

#include "CObj__RFG_SERIAL__ALID.h"


class CObj__RFG_SERIAL : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	int iActive__SIM_MODE;

	SCX__SERIAL_JG mX_Serial;
	CString sPROTOCOL_INFO;

	char m_Term_Str[3];
	int	 m_nCommState;
	int	 m_Rcv_Time;
	int	 m_RetryCnt;
	CString  m_Command;
	//


	//-------------------------------------------------------------------------
	SCX__USER_LOG_CTRL xI__APP_LOG_CTRL;
	SCX__USER_LOG_CTRL xI__DRV_LOG_CTRL;

	byte iUNIT__ADDR_ID;

	double dVALUE__PWR_MAX;
	int  iHEXA__PWR_MAX;

	// ...
	void Write__APP_LOG(const CString& log_msg);
	void Write__DRV_LOG(const CString& log_msg);
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;		  

	// PARA ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_SET_POWER;

	// MON ...
	CX__VAR_DIGITAL_CTRL dCH__MON_COMM_STS;

	// CFG ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_DRV_LOG_ENABLE;
	CX__VAR_DIGITAL_CTRL dCH__CFG_RF_MODE;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_COM_PORT;	  
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_BAUD_RATE;	  

	CX__VAR_STRING_CTRL  sCH__INFO_LAST_ERROR_CODE;	  

	CX__VAR_STRING_CTRL	 sCH__INFO_POWER_SETPOINT;
	CX__VAR_STRING_CTRL  sCH__INFO_FORWARD_POWER;
	CX__VAR_STRING_CTRL  sCH__INFO_REFLECT_POWER;

	// BYTE : 0
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_HEXA_0;

	CX__VAR_STRING_CTRL	 sCH__INFO_STS_RF_OUTPUT_CONTROL;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_RF_MODE_CONTROL;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_ALARM;

	// BYTE : 1
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_HEXA_1;

	CX__VAR_STRING_CTRL	 sCH__INFO_STS_TEMPERATURE;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_INTERLOCK;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_AMP;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_HD_CON;
	//

	// IO CHANNEL  -----------------------------------
	// AO ...
	CX__VAR_ANALOG_CTRL  aoCH__POWER_SET;

	// SI ...
	CX__VAR_STRING_CTRL  siCH__RF_STATE;

	CX__VAR_STRING_CTRL	 siCH__POWER_SERPOINT;
	CX__VAR_STRING_CTRL	 siCH__POWER_FORWARD;
	CX__VAR_STRING_CTRL	 siCH__POWER_REFLECT;

	// DO ...
	CX__VAR_DIGITAL_CTRL doCH__POWER_MODE;			// OFF   ON
	CX__VAR_DIGITAL_CTRL doCH__ALARM_RESET;			// OFF   ON
	//


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__ON;
	CString sMODE__OFF;
	int  Call__POWER_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_power);

	CString sMODE__ALARM_RESET;
	int  Call__ALARM_RESET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__TEST_DRV;
	int  Call__TEST_DRV(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	unsigned char _Set_CheckSum(unsigned char *s_cmmd, const int s_len);
	
	int  _Check_ErrorCode(unsigned char err_code);
	CString _Get_ErrorCode(unsigned char err_code);

	int  _Recv__Command(const byte addr_id,const byte cmmd_id, const byte data_01,const byte data_02);
	int  _Recv__Command(const byte addr_id,const byte cmmd_id, unsigned char* r_data);
	
	// ...
	int  Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	void _Update__RF_State(unsigned char data_0, unsigned char data_1);
	//


public:
	CObj__RFG_SERIAL();
	~CObj__RFG_SERIAL();

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

