#include "StdAfx.h"
#include "CObj__PIRANI_SERIAL.h"

#include "Macro_Function.h"


//--------------------------------------------------------------------------------
CObj__PIRANI_SERIAL::CObj__PIRANI_SERIAL()
{

}
CObj__PIRANI_SERIAL::~CObj__PIRANI_SERIAL()
{

}


//--------------------------------------------------------------------------------
int CObj__PIRANI_SERIAL::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");
		ADD__CTRL_VAR(sMODE__TEST, "TEST");
	}
	return 1;
}
int CObj__PIRANI_SERIAL::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee";

	return 1;
}


// ...
#define  MON_ID__ALM_REPORT					1

int CObj__PIRANI_SERIAL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString def_name;
	CString var_name;

	// ...
	CString log_type = "L";

	def_name = "DATA.LOG_TYPE";
	p_variable->Get__DEF_CONST_DATA(def_name, log_type);
	
	// CFG ...
	{
		var_name = "CFG.PRESSURE.TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "mbar torr", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PRESSURE_TYPE, var_name);
	}

	// MON ...
	{
		var_name = "s.DATA.PRESSURE.TORR";
		STD__ADD_STRING_WITH_OPTION(var_name, -1, log_type, "");
		LINK__VAR_STRING_CTRL(sCH__DATA_PRESSURE_TORR, var_name);

		var_name = "MON.PRESSURE.TYPE";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PRESSURE_TYPE, var_name);

		//
		var_name = "MON.COMMUNICATION.STATE";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMMUNICATION_STATE, var_name);

		var_name = "MON.COMMUNICATION.INFO";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMMUNICATION_INFO, var_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__ALM_REPORT);
	}
	return 1;
}
int CObj__PIRANI_SERIAL::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__GAUGEx_OFFLINE;

		alarm_title  = title;
		alarm_title += "Offline !";

		alarm_msg  = "Gauge Controller is Offline.\n";
		alarm_msg += "Please, Check Communication Status !\n";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__GAUGEx_CONTROL_TIMEOUT;

		alarm_title  = title;
		alarm_title += "Control Timeout !";

		alarm_msg  = "GAuge Controller is Timeout.\n";
		alarm_msg += "Please, Check Gauge Control Status !";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__PIRANI_SERIAL::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString var_name;

	// ...
	{
		var_name = "di.PRESSURE.GET";
		IO__ADD_DIGITAL_READ_WITH_OPTION(var_name, "GET", "","","", 0.1, "");
		LINK__IO_VAR_DIGITAL_CTRL(diCH__PRESSURE_GET, var_name);

		var_name = "do.PRESSURE.TYPE";
		IO__ADD_DIGITAL_WRITE(var_name, "mbar torr");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__PRESSURE_TYPE, var_name);

		var_name = "si.PRESSURE.TYPE";
		IO__ADD_STRING_READ__MANUAL(var_name);
		LINK__IO_VAR_STRING_CTRL(siCH__PRESSURE_TYPE, var_name);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__PIRANI_SERIAL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;

	// DATA.OFFLINE_VALUE ...
	{
		def_name = "DATA.OFFLINE_VALUE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		aSet__Offline_Value = atof(def_data);
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;
		
		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	iCOMM_STATE = _DEF__OFFLINE;
	return 1;
}
int CObj__PIRANI_SERIAL::__INITIALIZE__IO(p_io_para)
{
	//-------------------------------------------------------
	// Set Driver Parameter

	// ...
	int com_port = -1;

	int nRate   = 19200;
	int nByte   = 8;			
	int nStop   = 1;			
	int nParity = 0;		// 0, 1, 2, 3, 4  :  No, Odd, Even, Mark, Space

	iADDRESS_ID = 0;

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
		// 2.
		{
			para_cmmd = "BAUD_RATE";

			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				nRate = atoi(para_data);
			}
			else
			{

			}
		}
		// 3.
		{
			para_cmmd = "ADDRESS_ID";

			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				iADDRESS_ID = atoi(para_data);
			}
		}
	}

	// ...
	{
		m_nRetryCnt = 2;
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

	// ...
	{
		CString str_info;

		str_info.Format("Com_Port(%1d) Buad_Rate(%1d) Data_Bit(%1d) Stop_Bit(%1d) Parity(%s)",
						com_port,
						nRate,
						nByte,
						nStop,
						Macro__Get_Parity(nParity));

		sCH__MON_COMMUNICATION_INFO->Set__DATA(str_info);
	}

	if(iActive__SIM_MODE > 0)
	{
		CString msg;

		msg.Format("Simulation Mode !!! \n");

		xDRV_LOG_CTRL->WRITE__LOG(msg);
		return -1;
	}

	// ...
	{
		CString msg;

		mX_Serial->RTS__CHECK_SKIP();
		
		if(mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity) < 0)
		{
			iCOMM_STATE = _DEF__OFFLINE;

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
int CObj__PIRANI_SERIAL::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	int r_flag = -1;

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)			r_flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__TEST)			r_flag = Call__TEST(p_variable,p_alarm);
	}

	if((r_flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		r_flag = -1;
	}
	return r_flag;
}

int CObj__PIRANI_SERIAL::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__ALM_REPORT)		Mon__ALM_REPORT(p_variable, p_alarm);

	return 1;
}

int CObj__PIRANI_SERIAL::__CLOSE__OBJECT()
{

	return 1;
}
