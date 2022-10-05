#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__RPS_SERIAL__ALID.h"
#include "CObj__RPS_SERIAL__DEF.h"


//...
#define MAX_CHAR						256

//...
#define HOST							0x02
#define ANALOG							0x04

// Header...
#define Header_NoData					0x08
#define Header_1ByteData				0x09
#define Header_2ByteData				0x0A
#define Header_3ByteData				0x0B

// Command...
#define CMD__ON							0x02	//  2 // RF Power ON
#define CMD__OFF						0x01	//  1 // RF Power OFF
#define CMD__REGULATION_SELECT			0x03	//	3 // Regulation select //6:Forward power, 7:Load(Delevery, 8:ext
#define CMD__SETPOINT					0x08	//  8 // RF Power Setpoint
#define CMD__MODE_SELECT				0x0E	// 14 // Mode Set  //Value 2:Host, 4:Analog
#define CMD__MODE_READ					0x9B    //155 // Mode Read //Value 2:Host, 4:Analog
#define CMD__STATUS_READ				0xA2	//162 // Status Read
#define CMD__SETPOINT_READ				0xA4	//164 // Setpoint Read
#define CMD__FORWARD_PWR_READ			0xA5	//165 // Forward Read
#define CMD__REFLECET_PWR_READ			0xA6	//166 // Reflect Read
#define CMD__DELIVERED_PWR_READ			0xA7	//167 // Delivered Read
//


class CObj__RPS_SERIAL : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	int iActive__SIM_MODE;

	// ...
	SCX__SERIAL_JG mX_Serial;

	CString sPROTOCOL_INFO;

	CString sEND_SEND;
	CString sEND_RECV;

	bool bActive__DRV_FNC_START;
	SCX__ASYNC_TIMER_CTRL xTIMER__DRV_LINE;
	//

	//-------------------------------------------------------------------------
	SCX__USER_LOG_CTRL xI__APP_LOG_CTRL;
	SCX__USER_LOG_CTRL xI__DRV_LOG_CTRL;

	void Write__APP_LOG(const CString& log_msg);
	void Write__DRV_LOG(const CString& log_title, const CString& log_msg);
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;		  

	// PARA ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_SET_POWER;

	// CFG ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_DRV_CHAR_SEDN_DELAY_SEC;
	CX__VAR_ANALOG_CTRL  aCH__CFG_DRV_LINE_SEDN_DELAY_SEC;

	CX__VAR_DIGITAL_CTRL dCH__CFG_DRV_LOG_ENABLE;

	// MON ...
	CX__VAR_DIGITAL_CTRL dCH__MON_COMM_STS;

	// INFO.PART ...
	CX__VAR_STRING_CTRL  sCH__INFO_DELIVERED_POWER;
	CX__VAR_STRING_CTRL	 sCH__INFO_POWER_SETPOINT;
	CX__VAR_STRING_CTRL	 sCH__INFO_REFLECTED_POWER;

	CX__VAR_STRING_CTRL	 sCH__INFO_RF_VOLTAGE;
	CX__VAR_STRING_CTRL	 sCH__INFO_RF_CURRENT;
	
	CX__VAR_STRING_CTRL	 sCH__INFO_DC_VOLTAGE;
	CX__VAR_STRING_CTRL	 sCH__INFO_DC_CURRENT;

	CX__VAR_STRING_CTRL	 sCH__INFO_RF_PHASE;
	CX__VAR_STRING_CTRL	 sCH__INFO_FREQUENCY;
	CX__VAR_STRING_CTRL	 sCH__INFO_QFR;
	
	CX__VAR_STRING_CTRL	 sCH__INFO_PLASMA_IMPEDANCE_R;
	CX__VAR_STRING_CTRL	 sCH__INFO_PLASMA_IMPEDANCE_X;

	CX__VAR_STRING_CTRL	 sCH__INFO_RUN_MODE_STATE;
	CX__VAR_STRING_CTRL	 sCH__INFO_RUN_MODE_DATA;

	CX__VAR_STRING_CTRL	 sCH__INFO_INTERLOCK_STATE;
	CX__VAR_STRING_CTRL	 sCH__INFO_INTERLOCK_DATA;

	CX__VAR_STRING_CTRL	 sCH__INFO_PLASMA_ON_ENABLE_TURN_ON_STATE;
	CX__VAR_STRING_CTRL	 sCH__INFO_PLASMA_ON_ENABLE_OUTPUT_HIGH_STATE;

	CX__VAR_STRING_CTRL	 sCH__INFO_DIGITAL_SET_POWER_STATE;
	CX__VAR_STRING_CTRL	 sCH__INFO_DIGITAL_SET_POWER_VALUE;

	// INFO.DRV ...
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_COM_PORT;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_BAUD_RATE;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_DATA_BIT;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_STOP_BIT;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_PARITY;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_END_SEND;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_END_RECV;
	//

	// IO CHANNEL  -----------------------------------
	// IO ...
	CX__VAR_DIGITAL_CTRL doCH__DIGITAL_POWER_CTRL;
	CX__VAR_ANALOG_CTRL  aoCH__DIGITAL_POWER_SET;

	CX__VAR_DIGITAL_CTRL doCH__PLASMA_ON_ENABLE_TURN_ON;
	CX__VAR_DIGITAL_CTRL doCH__PLASMA_ON_ENABLE_OUTPUT_HIGH;

	CX__VAR_STRING_CTRL  siCH__ALL_STATE_GET;
	//


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__REMOTE;
	CString sMODE__LOCAL;
	int  Call__CTRL_MODE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_remote);

	CString sMODE__POWER_SET;
	CString sMODE__OFF;
	int  Call__POWER_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_power);

	CString sMODE__POWER_ON;
	int  Call__POWER_ON(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__DRV_TEST;
	int  Call__DRV_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	int  _Send__Command(const CString& s_cmmd,const CString& s_op,const CString& s_data, CString* r_data);
	int  _Update__CMD_INFO(const CString& r_data);

	// ...
	int  Mon__STATE_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj__RPS_SERIAL();
	~CObj__RPS_SERIAL();

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

