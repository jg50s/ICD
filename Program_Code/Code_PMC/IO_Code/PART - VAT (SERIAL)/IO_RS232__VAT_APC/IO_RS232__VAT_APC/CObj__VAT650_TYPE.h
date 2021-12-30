#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__VAT650_TYPE__ALID.h"
#include "CObj__VAT650_TYPE__DEF.h"


class CRes__ERR_DB
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CUIntArray   iList__ERR_ID;
	CStringArray sList__ERR_CODE;

public:
	CRes__ERR_DB()
	{
		InitializeCriticalSection(&mCS_LOCK);
	}
	~CRes__ERR_DB()
	{
		DeleteCriticalSection(&mCS_LOCK);
	}

	void Load__ERR_ID(const int err_id,const CString& err_code)
	{
		EnterCriticalSection(&mCS_LOCK);

		// ...
		{
			iList__ERR_ID.Add(err_id);
			sList__ERR_CODE.Add(err_code);

			if(iList__ERR_ID.GetSize() > 30)
			{
				iList__ERR_ID.RemoveAt(0);
				sList__ERR_CODE.RemoveAt(0);
			}
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
	int  Get__ERR_ID(int& err_id,CString& err_code)
	{
		EnterCriticalSection(&mCS_LOCK);

		// ...
		int flag = -1;

		if(iList__ERR_ID.GetSize() > 0)
		{
			flag = 1;

			// ...
			{
				err_id   = (int) iList__ERR_ID[0];
				err_code = sList__ERR_CODE[0]; 

				iList__ERR_ID.RemoveAt(0);
				sList__ERR_CODE.RemoveAt(0);
			}
		}

		LeaveCriticalSection(&mCS_LOCK);
		return flag;
	}
};

class CObj__VAT650_TYPE: public __IOBJ__IO_TYPE
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
	CRes__ERR_DB mRes__ERR_DB;

	SCX__TIMER_CTRL	xI_TIMER;

	SCX__SERIAL mX_Serial;

	// ...
	int m_nCommSts;
	int m_nTimeout;
	char m_Term_Str[3];
	int m_nRetryCount;

	CString	m_sErrorCode;
	CString	m_szAlarm;

	int iFlag__APP_LOG;
	int iFlag__DRV_LOG;
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// DB_CFG
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_SIM_MODE;
	CX__VAR_DIGITAL_CTRL dCH__OBJ_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__DRV_LOG_PARAM_START_STOP;

	//-------------------------------------------------------------------------
	// Virtual Channel
	CX__VAR_STRING_CTRL  sCH__SEQUENCE_MSG;
	CX__VAR_ANALOG_CTRL  aCH__PRESSURE_SET;
	CX__VAR_ANALOG_CTRL  aCH__POSITION_SET;

	CX__VAR_STRING_CTRL  sCH__MON_PRESSURE_VALUE;
	CX__VAR_STRING_CTRL  sCH__MON_CUR_POSITION_VALUE;

	CX__VAR_DIGITAL_CTRL dCH__CFG_VALVE_INIT_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__CFG_POS_COUNT_TYPE;

	CX__VAR_ANALOG_CTRL  aCFG_CH__AUTO_LEARN_CMD_TIMEOUT;

	CX__VAR_STRING_CTRL  sCH__ERROR_CODE_1M_TYPE;

	CX__VAR_STRING_CTRL  sCH__CFG_RANGE_PRESSURE_1M_TYPE;
	CX__VAR_STRING_CTRL  sCH__CFG_RANGE_POSITION_1M_TYPE;

	// Driver Channel Controller ...
	// AO
	CX__VAR_ANALOG_CTRL	xCH__aoSET_PRESSURE;
	CX__VAR_ANALOG_CTRL	xCH__aoSET_POSITION;

	// AI
	CX__VAR_ANALOG_CTRL xCH__aiVALVE_POS;
	CX__VAR_ANALOG_CTRL xCH__aiVALVE_PRESS;

	// DO
	CX__VAR_DIGITAL_CTRL xCH__doCTRL_MODE;
	CX__VAR_DIGITAL_CTRL xCH_doOPER_MODE;
	CX__VAR_DIGITAL_CTRL xCH__doVALVE_OPR_CMD;
	CX__VAR_DIGITAL_CTRL xCH__doVALVE_MON_CMD;
	CX__VAR_DIGITAL_CTRL xCH__doRANGE_SET;
	CX__VAR_DIGITAL_CTRL xCH_doRESET_CMD;
	CX__VAR_DIGITAL_CTRL xCH_doZERO_CMD;
	CX__VAR_DIGITAL_CTRL xCH_doAUTO_LEARN_CMD;

	CX__VAR_DIGITAL_CTRL xCH_doGET_CONFIG_INFO__1M_TYPE;

	// DI
	CX__VAR_DIGITAL_CTRL xCH_diCOMM_STS;
	CX__VAR_DIGITAL_CTRL xCH_diOPER_MODE;
	CX__VAR_DIGITAL_CTRL xCH_diCTRL_STS;
	CX__VAR_DIGITAL_CTRL xCH_diPOSITION_ERROR;

	//
	CX__VAR_DIGITAL_CTRL xCH_diCOMM_ERROR__1K_TYPE;
	CX__VAR_DIGITAL_CTRL xCH_diCOMM_ERROR__1M_TYPE;


	//-------------------------------------------------------------------------
	// Driver Function ...
	int SendCommand__1K_TYPE(const CString& fnc_name, CString szMsg, const CString& set_data, const int cmd_timeout);
	int SendCommand__1M_TYPE(const CString& fnc_name, const CString& send_cmmd, const CString& key_word, const int cmd_timeout);

	int RecvDataProc__1K_TYPE(const CString& fnc_name, CString szMsg, CString& szRcvData);
	int RecvDataProc__1M_TYPE(const CString& fnc_name, const CString& send_cmmd, CString& recv_data);


	//-------------------------------------------------------------------------
	// INIT ---
	CString sMODE__INIT_COMM;
	CString sMODE__INIT;
	int	Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const int comm_flag);

	int Fnc__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const int comm_flag);

	// OPEN ---
	CString sMODE__OPEN;
	int	Call__OPEN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int Fnc__OPEN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// CLOSE ---
	CString sMODE__CLOSE;
	int	Call__CLOSE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int Fnc__CLOSE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// PRESSURE ---
	CString sMODE__PRESSURE;
	int	Call__PRESSURE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int Fnc__PRESSURE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// POSITION ---
	CString sMODE__POSITION;
	int	Call__POSITION(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int Fnc__POSITION(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// POSITION.WAIT ...
	CString sMODE__POSITION_WAIT;
	int	Call__POSITION_WAIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__POSITION_NO_WAIT;
	int	Call__POSITION_NO_WAIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int Fnc__POSITION_WAIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm,const int wait_flag);

	// HOLD ---
	CString sMODE__HOLD;
	int	Call__HOLD(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int Fnc__HOLD(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// AUTO LEARN ---
	CString sMODE__AUTO_LEARN;
	int	Call__AUTO_LEARN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int Fnc__AUTO_LEARN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);


	//-------------------------------------------------------------------------
	// ...
	void Mon__DRV_ALM(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	void Mon__VALUE_MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	int  Is__ONLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Is__REMOTE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int  ComErrorCheck__1K_TYPE(const CString& err_code);

	void Fnc__APP_LOG(const CString& log_msg);
	void Fnc__DRV_LOG(const CString& log_msg);
	//


public:
	CObj__VAT650_TYPE();
	~CObj__VAT650_TYPE();

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

	// ...
	int _Read__ANALOG_OF_1K_TYPE(const CString& var_name, double& read_data, 
								 const double min,const double max, 
								 const CString& cmmd1,const CString& cmmd2,const CString& cmmd3);
	int _Read__ANALOG_OF_1M_TYPE(const CString& var_name, double& read_data, 
								 const double min,const double max, 
								 const CString& cmmd1,const CString& cmmd2,const CString& cmmd3);

	int _Read__DIGITAL_OF_1K_TYPE(const CString& var_name, CString& read_data);
	int _Read__DIGITAL_OF_1M_TYPE(const CString& var_name, CString& read_data);

	int _Read__STRING_OF_1K_TYPE(const CString& var_name, CString& read_data);
	int _Read__STRING_OF_1M_TYPE(const CString& var_name, CString& read_data);

	int _Write__ANALOG_OF_1K_TYPE(const CString& var_name, const double set_data);
	int _Write__ANALOG_OF_1M_TYPE(const CString& var_name, const double set_data);

	int _Write__DIGITAL_OF_1K_TYPE(const CString& var_name, const CString& set_data);
	int _Write__DIGITAL_OF_1M_TYPE(const CString& var_name, const CString& set_data);

	int _Write__STRING_OF_1K_TYPE(const CString& var_name, const CString& set_data);	
	int _Write__STRING_OF_1M_TYPE(const CString& var_name, const CString& set_data);	

};
