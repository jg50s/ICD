#include "StdAfx.h"
#include "CObj__UNIT_TYPE.h"



//--------------------------------------------------------------------------------
CObj__UNIT_TYPE::CObj__UNIT_TYPE()
{
	for (int i=0; i<MAX_MFC; i++)
	{
		m_szFirm_Revision[i] = "0";
	}

	m_nBoardNumber = 0;
	m_nStartNumber = 0;
	m_nMaxNumber   = 0;
	m_nMFCMaxCount = 0;
}

CObj__UNIT_TYPE::~CObj__UNIT_TYPE()
{

}


//--------------------------------------------------------------------------------
int CObj__UNIT_TYPE::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	return 1;
}
int CObj__UNIT_TYPE::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee";

	return 1;
}


// ...
#define  MON_ID__ALM_REPORT					1

int CObj__UNIT_TYPE::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);
	
	CString def_name, def_value, str_name;
	CString str_temp;

	// ...
	def_name.Format("MFC_BOARD_NUMBER");
	p_variable->Get__DEF_CONST_DATA(def_name, def_value);
	m_nBoardNumber = atoi(def_value);

	def_name.Format("MFC_START_NUM");
	p_variable->Get__DEF_CONST_DATA(def_name, def_value);
	m_nStartNumber = atoi(def_value);

	// ...
	def_name.Format("MFC_MAX_NUM");
	p_variable->Get__DEF_CONST_DATA(def_name, def_value);
	m_nMaxNumber = atoi(def_value);

	for (int i=m_nStartNumber; i<= m_nMaxNumber; i++)
	{
		m_nMFCMaxCount++;
	}

	// ...
	{
		str_name = "DRV.LOG.PARAM.LOG.START";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"STOP START","");
		LINK__VAR_DIGITAL_CTRL(dCH__DRV_LOG_PARAM_START_STOP,str_name);

		str_name = "DRV.READ.DELAY.TIME.MSEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "msec", 0, 10, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__DRV_READ_DELAY_TIME_MSEC,str_name);
	}

	// ...
	{
		str_name = "ALM_TEST.OFFLINE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ALM_TEST__OFFLINE,str_name);

		str_name = "ALM_TEST.TIMEOUT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ALM_TEST__TIMEOUT,str_name);
	}

	// ...
	{
		str_name = "CFG.BAUD_RATE.NEXT_APPLY";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "38400 19200 9600", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_BAUD_RATE_NEXT_APPLY, str_name);
		
		str_name = "CUR.BAUD_RATE.APPLIED";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_BAUD_RATE_APPLIED, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__ALM_REPORT);
	}
	return 1;
}
int CObj__UNIT_TYPE::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	CString szGas_Num;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	int nGas_Num = m_nStartNumber;
	int i;

	for(i=0; i<=MAX_MFC; i++)
	{
		alarm_id = ALID__GASx_OFFLINE + i;

		alarm_title  = title;
		szGas_Num.Format("GAS[%02d] Offline.", nGas_Num);
		alarm_title += szGas_Num;

		alarm_msg.Format("MFC[%02d] Controller is Offline.\n", nGas_Num);
		alarm_msg += "Please, Check Communication Status !\n";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

		nGas_Num++;
	}

	// ...
	nGas_Num = m_nStartNumber;

	for(i=0; i<=MAX_MFC; i++)
	{
		alarm_id = ALID__GASx_CONTROL_TIMEOUT + i;

		alarm_title  = title;
		szGas_Num.Format("GAS[%02d] Control Timeout.", nGas_Num);
		alarm_title += szGas_Num;

		alarm_msg.Format("MFC[%02d] Controller is Timeout.\n", nGas_Num);
		alarm_msg += "Please, Check MFC Control Status !";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

		nGas_Num++;
	}

	return 1;
}

//-------------------------------------------------------------------------
#define APP_DSP__COMM_STS				"OFFLINE  ONLINE"
#define APP_DSP__CTRL_MODE				"LOCAL  REMOTE"
#define APP_DSP__CTRL_STS				"LOCAL  REMOTE"
#define APP_DSP__OFF_ON					"NONE OFF ON"

// ...
#define APP_DSP__UNIT_CTRL				"ANALOG DIGITAL"
#define APP_DSP__FREEZE_FOLLOW			"FREEZE FOLLOW"
#define APP_DSP__OVERMODE				"SEMI UNIT"
#define APP_DSP__VALVE_CTRL				"NONE CONTROL CLOSE OPEN OFF"
#define APP_DSP__UNIT_INIT				"AUTOZERO INIT RESET CALIBRATION"

int CObj__UNIT_TYPE::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;
	CString str_gas_num;

	int i = 0;
	int nGas_Num = 0;
	double dblMax = 0.0;
	
	// Analog Channel ...
	// AI ...
	{
		for(nGas_Num = 0,i=m_nStartNumber; i<=m_nMaxNumber; i++)
		{
			str_name.Format("ai.MFC%02d.FLOW", i);
			str_gas_num.Format("%d", ++nGas_Num);

			p_analog_io->Add__ANALOG_READ_EX(str_name, "101", "sccm", 1, -10000, 99999, str_gas_num, "", "", -1);
		}

		for(nGas_Num = 0,i=m_nStartNumber; i<=m_nMaxNumber; i++)
		{
			str_name.Format("ai.MFC%02d.VOLT", i);
			str_gas_num.Format("%d", ++nGas_Num);

			p_analog_io->Add__ANALOG_READ_EX(str_name, "102", "Volt", 1,-15.00, 15, str_gas_num, "", "", -1);
		}

		for(nGas_Num = 0,i=m_nStartNumber; i<=m_nMaxNumber; i++)
		{
			str_name.Format("ai.MFC%02d.SETPOINT", i);
			str_gas_num.Format("%d", ++nGas_Num);

			p_analog_io->Add__ANALOG_READ_EX(str_name, "103", "sccm", 1,-10000, 99999, str_gas_num, "", "", -1);
		}

		for(nGas_Num = 0,i=m_nStartNumber; i<=m_nMaxNumber; i++)
		{
			str_name.Format("ai.MFC%02d.MACID", i);
			str_gas_num.Format("%d", ++nGas_Num);

			p_analog_io->Add__ANALOG_READ_EX(str_name, "104", "num", 0, -100, 100, str_gas_num, "", "", -1);
		}
	}
	// AO ...
	{
		for(nGas_Num = 0,i=m_nStartNumber; i<=m_nMaxNumber; i++)
		{
			str_name.Format("ao.MFC%02d.SETPOINT", i);
			str_gas_num.Format("%d", ++nGas_Num);

			p_analog_io->Add__ANALOG_WRITE_EX(str_name, "150", "sccm", 1,-10000, 99999, str_gas_num, "", "");
		}
	}

	// Digital Channel ...
	// DO ...
	{
		for(nGas_Num = 0,i=m_nStartNumber; i<=m_nMaxNumber; i++)
		{
			str_name.Format("do.MFC%02d.GET.FIRM.VER", i);
			str_gas_num.Format("%d", ++nGas_Num);
			
			p_digital_io->Add__DIGITAL_WRITE_EX(str_name, "251", "GET", str_gas_num, "", "");
		}

		for(nGas_Num = 0,i=m_nStartNumber; i<=m_nMaxNumber; i++)
		{
			str_name.Format("do.MFC%02d.INIT", i);
			str_gas_num.Format("%d", ++nGas_Num);

			p_digital_io->Add__DIGITAL_WRITE_EX(str_name, "252",APP_DSP__UNIT_INIT, str_gas_num, "", "");
		}

		for(nGas_Num = 0,i=m_nStartNumber; i<=m_nMaxNumber; i++)
		{
			str_name.Format("do.MFC%02d.FREEZE.FOLLOW", i);
			str_gas_num.Format("%d", ++nGas_Num);
			
			p_digital_io->Add__DIGITAL_WRITE_EX(str_name, "253",APP_DSP__FREEZE_FOLLOW, str_gas_num, "", "");
		}

		for(nGas_Num = 0,i=m_nStartNumber; i<=m_nMaxNumber; i++)
		{
			str_name.Format("do.MFC%02d.OVERRIDE.MODE", i);
			str_gas_num.Format("%d", ++nGas_Num);

			p_digital_io->Add__DIGITAL_WRITE_EX(str_name, "254",APP_DSP__OVERMODE, str_gas_num, "", "");
		}

		for(nGas_Num = 0,i=m_nStartNumber; i<=m_nMaxNumber; i++)
		{
			str_name.Format("do.MFC%02d.VALVE.SET", i);
			str_gas_num.Format("%d", ++nGas_Num);

			p_digital_io->Add__DIGITAL_WRITE_EX(str_name, "255",APP_DSP__VALVE_CTRL, str_gas_num, "", "");
		}

		for(nGas_Num = 0,i=m_nStartNumber; i<=m_nMaxNumber; i++)
		{
			str_name.Format("do.MFC%02d.CTRL.MODE", i);
			str_gas_num.Format("%d", ++nGas_Num);

			p_digital_io->Add__DIGITAL_WRITE_EX(str_name, "256",APP_DSP__UNIT_CTRL, str_gas_num, "", "");
		}
	}	
	// DI ...
	{
		for(nGas_Num = 0,i=m_nStartNumber; i<=m_nMaxNumber; i++)
		{
			str_name.Format("di.MFC%02d.COMM.STS", i);
			str_gas_num.Format("%d", ++nGas_Num);

			p_digital_io->Add__DIGITAL_READ_EX(str_name, "201",APP_DSP__COMM_STS, str_gas_num, "", "");
		}

		for(nGas_Num = 0,i=m_nStartNumber; i<=m_nMaxNumber; i++)
		{
			str_name.Format("di.MFC%02d.VALVE.STS", i);
			str_gas_num.Format("%d", ++nGas_Num);

			p_digital_io->Add__DIGITAL_READ_EX(str_name, "202",APP_DSP__VALVE_CTRL, str_gas_num, "", "", -1);
		}
	}

	// String Cnannel ...
	// SI ...
	{
		for(nGas_Num = 0,i=m_nStartNumber; i<=m_nMaxNumber; i++)
		{
			str_name.Format("si.MFC%02d.Version", i);
			str_gas_num.Format("%d", ++nGas_Num);

			p_string_io->Add__STRING_READ_EX(str_name, "301", str_gas_num, "", "", -1);
		}
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__UNIT_TYPE::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString obj_name;
	CString var_name;
	
	// DB_SYS ...
	{
		obj_name = "DB_SYS";
		
		//
		var_name = "CFG.MFC_485.SETPOINT_READ.CONFIRM_USE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_MFC_485_SETPOINT_READ_CONFIRM_USE, obj_name,var_name);

		var_name = "CFG.MFC_485.COMM_OFFLINE_ALARM.USE";		
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_MFC_485_COMM_OFFLINE_ALARM_USE, obj_name,var_name);

		var_name = "CFG.MFC_485.CONTROL_TIMEOUT_ALARM.USE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_MFC_485_CONTROL_TIMEOUT_ALARM_USE, obj_name,var_name);
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iACTIVE_SIM = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}
int CObj__UNIT_TYPE::__INITIALIZE__IO(p_io_para)
{
	//-------------------------------------------------------
	// Set Driver Parameter

	// ...
	int com_port = -1;

	int nRate   = 38400;
	int nByte   = 8;			
	int nStop   = 1;			
	int nParity = 0;		// 0, 1, 2, 3, 4  :  No, Odd, Even, Mark, Space

	// ...
	{
		m_Term_Str[0] = CR;	
		m_Term_Str[1] = LF;
		m_Term_Str[2] = '\0';
		m_Term_Str[3] = '\0';
	}

	// ...
	{
		CString file_name;
		CString log_msg;
		CString dir_name;
		int nfile_size;
		int nfile_time;

		file_name.Format("%s_Drv.log", sObject_Name);
		dir_name = sObject_Name;
		nfile_size = 24;
		nfile_time = 60;	// minute

		// ...
		{
			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xDRV_LOG_CTRL->CREATE__SUB_DIRECTORY(dir_name);
			xDRV_LOG_CTRL->SET__PROPERTY(file_name,nfile_size,nfile_time);

			xDRV_LOG_CTRL->DISABLE__TIME_LOG();
			xDRV_LOG_CTRL->WRITE__LOG(log_msg);

			xDRV_LOG_CTRL->ENABLE__TIME_LOG();
			xDRV_LOG_CTRL->WRITE__LOG("   START   \n");
		}
	}

	// ...
	{
		CString para_cmmd;
		CString para_data;

		// 1.
		{
			para_cmmd = "COM_PORT";

			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				com_port = atoi(para_data);
			}
		}
	}

	// ...
	{
		CString str_data = dCH__CFG_BAUD_RATE_NEXT_APPLY->Get__STRING();

		nRate = atoi(str_data);
		sCH__CUR_BAUD_RATE_APPLIED->Set__DATA(str_data);
	}

	// ...
	{
		m_nRetryCnt = 1;
		m_Rcv_Time = 300;		// ms
	}

	// ...
	{
		CString log_msg;
		CString msg;

		log_msg.Format("Connect to Serial ... \n");

		msg.Format("Com_Port : %d \n", com_port);
		log_msg += msg;

		msg.Format("nBaudRate : %1d \n", nRate);
		log_msg += msg;

		msg.Format("nDataBit  : %1d \n", nByte);
		log_msg += msg;

		msg.Format("nParity   : %1d \n", nParity);
		log_msg += msg;

		msg.Format("nStopBit  : %1d \n", nStop);
		log_msg += msg;

		msg.Format("m_nRetryCnt : %1d \n", m_nRetryCnt);
		log_msg += msg;

		msg.Format("m_Rcv_Time : %1d (msec) \n", m_Rcv_Time);
		log_msg += msg;

		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
	}

	m_nCommState = OFFLINE;

	if(iACTIVE_SIM < 0)
	{
		CString msg;

		mX_Serial->RTS__CHECK_SKIP();
		
		if(mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity) < 0)
		{
			msg.Format("Fail to do INIT__COMPORT: %d, ret:-1", com_port);
			xDRV_LOG_CTRL->WRITE__LOG(msg);
			return -1;
		}
		else
		{
			msg.Format("Initialize RS-232 Complete");
		}

		xDRV_LOG_CTRL->WRITE__LOG(msg);
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__UNIT_TYPE::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	
	return 1;
}

int CObj__UNIT_TYPE::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__ALM_REPORT)		Mon__ALM_REPORT(p_alarm);

	return 1;
}

int CObj__UNIT_TYPE::__CLOSE__OBJECT()
{

	return 1;
}
