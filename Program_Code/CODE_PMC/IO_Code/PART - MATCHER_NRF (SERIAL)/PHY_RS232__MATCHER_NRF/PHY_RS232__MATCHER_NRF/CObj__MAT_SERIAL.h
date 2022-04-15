#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Header.h"

#include "CObj__MAT_SERIAL__ALID.h"


class CObj__MAT_SERIAL : public __IOBJ__IO_TYPE
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

	double dVALUE__PWR_MAX_10;
	int  iHEXA__PWR_MAX_10;

	double dVALUE__PWR_MAX_100;
	int  iHEXA__PWR_MAX_100;

	double dVALUE__PWR_MAX_200;
	int  iHEXA__PWR_MAX_200;

	double dVALUE__PWR_MAX_1000;
	int  iHEXA__PWR_MAX_1000;

	double dVALUE__PWR_MAX_10000;
	int  iHEXA__PWR_MAX_10000;

	// ...
	void Write__APP_LOG(const CString& log_msg);
	void Write__DRV_LOG(const CString& log_msg);
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;		  

	// MON ...
	CX__VAR_DIGITAL_CTRL dCH__MON_COMM_STS;

	// PARA ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_LOAD_POS;
	CX__VAR_ANALOG_CTRL	 aCH__PARA_TUNE_POS;

	// CFG ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_DRV_LOG_ENABLE;
	CX__VAR_DIGITAL_CTRL dCH__CFG_MODE_SET;

	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_CONTROL_SET;	 
	CX__VAR_STRING_CTRL  sCH__MON_LOAD_POS_SET;	 
	CX__VAR_STRING_CTRL  sCH__MON_TUNE_POS_SET;	 

	// INFO...
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_COM_PORT;	  
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_BAUD_RATE;	  

	CX__VAR_STRING_CTRL  sCH__INFO_LAST_ERROR_CODE;	 
	CX__VAR_STRING_CTRL	 sCH__INFO_LOAD_PRESET;
	CX__VAR_STRING_CTRL	 sCH__INFO_TUNE_PRESET;
	CX__VAR_STRING_CTRL	 sCH__INFO_CUR_LOAD_POSITION;
	CX__VAR_STRING_CTRL	 sCH__INFO_CUR_TUNE_POSITION;
	CX__VAR_STRING_CTRL	 sCH__INFO_VPP_VALUE;

	CX__VAR_STRING_CTRL	 sCH__INFO_VRMS;
	CX__VAR_STRING_CTRL	 sCH__INFO_IRMS;
	CX__VAR_STRING_CTRL	 sCH__INFO_REAL_IMPEDANCE;
	CX__VAR_STRING_CTRL	 sCH__INFO_IMAGE_IMPEDANCE;
	CX__VAR_STRING_CTRL	 sCH__INFO_FORWARD_PWR;
	CX__VAR_STRING_CTRL	 sCH__INFO_REF_PWR;
	CX__VAR_STRING_CTRL	 sCH__INFO_START_SWR;
	CX__VAR_STRING_CTRL	 sCH__INFO_STOP_SWR;
	CX__VAR_STRING_CTRL	 sCH__INFO_CUR_SWR;
	CX__VAR_STRING_CTRL	 sCH__INFO_PHASE_SHIFT;

	// BYTE : 0
	CX__VAR_STRING_CTRL  sCH__INFO_STS_HEXA_0;

	CX__VAR_STRING_CTRL  sCH__INFO_STS_MAT_AUTO_MATCHING_STATE;		// 1
	CX__VAR_STRING_CTRL  sCH__INFO_STS_MAT_PANEL;					// 3
	CX__VAR_STRING_CTRL  sCH__INFO_STS_MAT_RF;						// 4

	// BYTE : 1
	CX__VAR_STRING_CTRL  sCH__INFO_STS_HEXA_1;

	CX__VAR_STRING_CTRL  sCH__INFO_STS_MAT_MOTOR_ERROR;				// 1
	CX__VAR_STRING_CTRL  sCH__INFO_STS_MAT_TEMP;					// 3
	CX__VAR_STRING_CTRL  sCH__INFO_STS_MAT_MATCHING;				// 4
	//

	// IO CHANNEL  -----------------------------------
	// AO ...
	CX__VAR_ANALOG_CTRL		aoCH__LOAD_PRESET;
	CX__VAR_ANALOG_CTRL		aoCH__TUNE_PRESET;
	CX__VAR_ANALOG_CTRL		aoCH__LOAD_MANUAL;
	CX__VAR_ANALOG_CTRL		aoCH__TUNE_MANUAL;

	// SI ...
	CX__VAR_STRING_CTRL		siCH__MAT_STATE;
	CX__VAR_STRING_CTRL		siCH__LOAD_PRESET;
	CX__VAR_STRING_CTRL		siCH__TUNE_PRESET;
	CX__VAR_STRING_CTRL		siCH__CUR_LOAD_POSITION;
	CX__VAR_STRING_CTRL		siCH__CUR_TUNE_POSITION;
	CX__VAR_STRING_CTRL		siCH__VPP_VALUE;
	CX__VAR_STRING_CTRL		siCH__VRMS_AND_LRMS;
	CX__VAR_STRING_CTRL		siCH__IMPEDANCE;
	CX__VAR_STRING_CTRL		siCH__FWD_PWR;
	CX__VAR_STRING_CTRL		siCH__REF_PWR;
	CX__VAR_STRING_CTRL		siCH__START_STOP_SWR;
	CX__VAR_STRING_CTRL		siCH__SWR;
	CX__VAR_STRING_CTRL		siCH__PHASE_SHIFT;

	// DO ...
	CX__VAR_DIGITAL_CTRL	doCH__STATUS_SET;		// OFF  ON
	CX__VAR_DIGITAL_CTRL	doCH__MOTOR_RESET;		// OFF  ON
	//

	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__AUTO;
	CString sMODE__MANUAL;
	CString sMODE__PROC_CTRL;
	int  Call__MODE_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool mode_set);
	int  Fnc__PRESET_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__MANUAL_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__TEST_DRV;
	int  Call__TEST_DRV(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	unsigned char _Set_CheckSum(unsigned char *s_cmmd, const int s_len);
	
	int  _Check_ErrorCode(unsigned char err_code);
	CString _Get_ErrorCode(unsigned char err_code);

	int  _Send__Command(const byte addr_id,const byte cmmd_id, const byte data_00);
	int  _Send__Command(const byte addr_id,const byte cmmd_id, const byte data_01,const byte data_02);

	int  _Recv__Command(const byte addr_id,const byte cmmd_id, unsigned char* r_data);
	
	// ...
	int  Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	void _Update__MAT_State(unsigned char data_0, unsigned char data_1);
	void _Updata__MAT_VRMS_IRMS(unsigned char data_0, unsigned char data_1, unsigned char data_2, unsigned char data_3);
	void _Updata__MAT_START_STOP_SWR(unsigned char data_0, unsigned char data_1, unsigned char data_2, unsigned char data_3);
	void _Updata__MAT_SWR(unsigned char data_0, unsigned char data_1, unsigned char data_2);
	void _Updata__MAT_PHASE_SHIFT(unsigned char data_0, unsigned char data_1, unsigned char data_2);
	void _Updata__MAT_IMPEDANCE(unsigned char data_0, unsigned char data_1, unsigned char data_2, unsigned char data_3, unsigned char data_4);
	//


public:
	CObj__MAT_SERIAL();
	~CObj__MAT_SERIAL();

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

