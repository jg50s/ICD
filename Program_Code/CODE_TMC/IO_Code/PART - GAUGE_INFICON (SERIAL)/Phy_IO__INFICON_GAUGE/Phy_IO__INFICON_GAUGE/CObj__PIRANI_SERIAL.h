#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__PIRANI_SERIAL__ALID.h"
#include "CObj__PIRANI_SERIAL__DEF.h"


class CObj__PIRANI_SERIAL : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xDRV_LOG_CTRL;
	SCX__SERIAL_JG mX_Serial;

	int iActive__SIM_MODE;

	// ...
	unsigned char iADDRESS_ID;

	int	m_Rcv_Time;
	int m_nRetryCnt;
	//


	// ---------------------------------------------------------------------------------------------
	// INTERNAL PARAMETER ... 

	// CFG ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_PRESSURE_TYPE;

	// IO ...
	CX__VAR_DIGITAL_CTRL diCH__PRESSURE_GET;
	CX__VAR_STRING_CTRL  sCH__DATA_PRESSURE_TORR;

	CX__VAR_DIGITAL_CTRL doCH__PRESSURE_TYPE;

	CX__VAR_STRING_CTRL  siCH__PRESSURE_TYPE;
	CX__VAR_STRING_CTRL  sCH__MON_PRESSURE_TYPE;

	//
	int iCOMM_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_INFO;

	double aSet__Offline_Value;
	//

	// ---------------------------------------------------------------------------------------------
	// EXTERNAL PARAMETER ... 

	//

	//------------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__TEST;
	int  Call__TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	//

	// ---------------------------------------------------------------------------------------------
	void Mon__ALM_REPORT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	int _Recv_Command(unsigned char* s_packet, 
					  const unsigned char s_len,
					  unsigned char* r_packet,
					  const unsigned char r_size,
					  const unsigned char r_ref);

	// ...
	void Fnc__DRV_LOG_OF_MSG(const CString& log_msg);
	void Fnc__DRV_LOG_OF_DATA_ERROR();
	//


public:
	CObj__PIRANI_SERIAL();
	~CObj__PIRANI_SERIAL();

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
