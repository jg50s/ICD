#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Header.h"

#include "CObj__NXA_PULSE__ALID.h"


class CObj__NXA_PULSE : public __IOBJ__IO_TYPE
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

	double dUNIT__FREQ;
	double dUNIT__DUTY;
	double dUNIT__uSEQ;

	// ...
	void Write__APP_LOG(const CString& log_msg);
	void Write__DRV_LOG(const CString& log_msg);
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;		  

	// CFG : SYSTEM ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_PART_USE;

	CX__VAR_DIGITAL_CTRL dCH__CFG_UNIT__FREQ;
	CX__VAR_DIGITAL_CTRL dCH__CFG_UNIT__DUTY;
	CX__VAR_DIGITAL_CTRL dCH__CFG_UNIT__uSEQ;

	CX__VAR_ANALOG_CTRL  aCH__CFG_FREQUENCY_MIN;
	CX__VAR_ANALOG_CTRL  aCH__CFG_FREQUENCY_MAX;
	CX__VAR_DIGITAL_CTRL dCH__CFG_FREQUENCY_DEC;

	// PARA.USER ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_A_USER_FREQ;
	CX__VAR_ANALOG_CTRL  aCH__PARA_A_USER_DUTY;
	CX__VAR_ANALOG_CTRL  aCH__PARA_A_USER_ON_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_A_USER_OFF_TIME;

	CX__VAR_ANALOG_CTRL  aCH__PARA_B_USER_ON_SHIFT_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_B_USER_OFF_SHIFT_TIME;

	CX__VAR_ANALOG_CTRL  aCH__PARA_C_USER_ON_SHIFT_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_C_USER_OFF_SHIFT_TIME;

	CX__VAR_DIGITAL_CTRL dCH__PARA_A_USER_CLK_CTRL;
	CX__VAR_DIGITAL_CTRL dCH__PARA_B_USER_CLK_CTRL;
	CX__VAR_DIGITAL_CTRL dCH__PARA_C_USER_CLK_CTRL;

	// PARA.RCP ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_RCP_FREQUENCY;
	CX__VAR_ANALOG_CTRL  aCH__PARA_RCP_DUTY;
	CX__VAR_ANALOG_CTRL  aCH__PARA_RCP_ON_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_RCP_OFF_TIME;

	CX__VAR_ANALOG_CTRL  aCH__PARA_RCP_ON_SHIFT_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_RCP_OFF_SHIFT_TIME;

	CX__VAR_DIGITAL_CTRL dCH__PARA_RCP_EXEC;

	// PARA.DRV ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_A_DRV_FREQ;
	CX__VAR_ANALOG_CTRL  aCH__PARA_A_DRV_DUTY;
	CX__VAR_ANALOG_CTRL  aCH__PARA_A_DRV_ON_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_A_DRV_OFF_TIME;

	CX__VAR_ANALOG_CTRL  aCH__PARA_B_DRV_ON_SHIFT_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_B_DRV_OFF_SHIFT_TIME;

	CX__VAR_ANALOG_CTRL  aCH__PARA_C_DRV_ON_SHIFT_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_C_DRV_OFF_SHIFT_TIME;

	CX__VAR_DIGITAL_CTRL dCH__PARA_A_DRV_CLK_CTRL;
	CX__VAR_DIGITAL_CTRL dCH__PARA_B_DRV_CLK_CTRL;
	CX__VAR_DIGITAL_CTRL dCH__PARA_C_DRV_CLK_CTRL;

	// MON ...
	CX__VAR_DIGITAL_CTRL dCH__MON_COMM_STS;

	CX__VAR_DIGITAL_CTRL dCH__MON_POWER_ABORT_ACTIVE;

	// CFG ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_DRV_LOG_ENABLE;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_COM_PORT;	  
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_BAUD_RATE;	  

	CX__VAR_STRING_CTRL  sCH__INFO_LAST_ERROR_CODE;	  

	//
	CX__VAR_STRING_CTRL	 sCH__INFO_PARAM_A_FREQ;
	CX__VAR_STRING_CTRL  sCH__INFO_PARAM_A_DUTY;
	CX__VAR_STRING_CTRL  sCH__INFO_PARAM_A_ON_TIME;
	CX__VAR_STRING_CTRL  sCH__INFO_PARAM_A_OFF_TIME;

	CX__VAR_STRING_CTRL  sCH__INFO_PARAM_B_ON_SHIFT_TIME;
	CX__VAR_STRING_CTRL  sCH__INFO_PARAM_B_OFF_SHIFT_TIME;

	CX__VAR_STRING_CTRL  sCH__INFO_PARAM_C_ON_SHIFT_TIME;
	CX__VAR_STRING_CTRL  sCH__INFO_PARAM_C_OFF_SHIFT_TIME;

	CX__VAR_STRING_CTRL  sCH__INFO_CLK_A_CTRL;
	CX__VAR_STRING_CTRL  sCH__INFO_CLK_B_CTRL;
	CX__VAR_STRING_CTRL  sCH__INFO_CLK_C_CTRL;
	//

	// IO CHANNEL  -----------------------------------
	// DO ...
	CX__VAR_DIGITAL_CTRL doCH__PARAM_A1;
	CX__VAR_DIGITAL_CTRL doCH__PARAM_A2;
	CX__VAR_DIGITAL_CTRL doCH__PARAM_B;
	CX__VAR_DIGITAL_CTRL doCH__PARAM_C;

	CX__VAR_DIGITAL_CTRL doCH__SET_EXEC;
	CX__VAR_DIGITAL_CTRL doCH__FLASH_CTRL;

	// SI ...
	CX__VAR_STRING_CTRL  siCH__PARAM_A1;
	CX__VAR_STRING_CTRL  siCH__PARAM_A2;
	CX__VAR_STRING_CTRL  siCH__PARAM_B;
	CX__VAR_STRING_CTRL  siCH__PARAM_C;

	CX__VAR_STRING_CTRL  siCH__GET_EXEC;
	//


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__PARA_USER_ON;
	CString sMODE__PARA_USER_OFF;
	int  Call__PARA_USER_CTRL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_on);

	//
	CString sMODE__PARA_RCP_ON;
	CString sMODE__PARA_RCP_OFF;
	int  Call__PARA_RCP_CTRL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_on);

	//
	CString sMODE__TEST_DRV;
	int  Call__TEST_DRV(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	unsigned char _Set_CheckSum(unsigned char *s_cmmd, const int s_len);

	int  _Check_ErrorCode(unsigned char err_code);
	CString _Get_ErrorCode(unsigned char err_code);

	int  _Recv__Command(const unsigned char cmmd_id, const unsigned char* p_param_data,const int param_size);		
	int  _Recv__Command(const unsigned char cmmd_id, unsigned char* r_data);

	CString _Get__CLK_STATE(const unsigned clk_sts);

	// ...
	int  Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj__NXA_PULSE();
	~CObj__NXA_PULSE();

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

