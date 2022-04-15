#include "StdAfx.h"
#include "CObj__STP_SERIAL.h"



//--------------------------------------------------------------------------------
CObj__STP_SERIAL::CObj__STP_SERIAL()
{

}
CObj__STP_SERIAL::~CObj__STP_SERIAL()
{

}

//--------------------------------------------------------------------------------
int CObj__STP_SERIAL::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,     "INIT");
		ADD__CTRL_VAR(sMODE__PUMP_ON,  "PUMP_ON");

		ADD__CTRL_VAR(sMODE__AUTO_STOP,			"AUTO_STOP");
		ADD__CTRL_VAR(sMODE__AUTO_STOP_NO_WAIT, "AUTO_STOP_NO_WAIT");

		ADD__CTRL_VAR(sMODE__CHECK_SUM, "CHECK_SUM");
	}
	return 1;
}
int CObj__STP_SERIAL::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee";

	return 1;
}


// ...
#define  MON_ID__STATE_CHECK				1


int CObj__STP_SERIAL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString dsc_item_list;

	// ...
	{
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_STATUS",dsc_item_list);

		str_name = "OBJ.STATUS";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, dsc_item_list, "");
		LINK__VAR_DIGITAL_CTRL(dCH__OBJ_STATUS, str_name);

		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// MON ...
	{
		str_name = "MON.COMM.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMM_STS, str_name);

		str_name = "MON.PUMP.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PUMP_STS, str_name);

		str_name = "MON.ERROR.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ERROR_STS, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.TARGET_SPEED.RPM";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "rpm", 0, 13500, 27000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TARGET_SPEED_RPM, str_name);

		//
		str_name = "CFG.STOP.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 60*120, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STOP_TIMEOUT, str_name);

		str_name = "CFG.ACCEL.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 60*10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_ACCEL_TIMEOUT, str_name);

		str_name = "CFG.TARGET_SPEED.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 60*20, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TARGET_SPEED_TIMEOUT, str_name);

		str_name = "CFG.MON.INTERVAL";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "msec", 0, 0, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_MON_INTERVAL, str_name);
	}

	// INFO ...
	{
		str_name = "INFO.DRV.COM_PORT";	  
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_COM_PORT, str_name);

		str_name = "INFO.DRV.BAUD_RATE";	  
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BAUD_RATE, str_name);

		//
		str_name = "INFO.ROT_SPEED.HZ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_ROT_SPEED_HZ, str_name);

		str_name = "INFO.ROT_SPEED.RPM";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_ROT_SPEED_RPM, str_name);

		//
		str_name = "INFO.PUMP_OP_MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PUMP_OP_MODE, str_name);

		str_name = "INFO.ERROR_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_ERROR_COUNT, str_name);

		//
		str_name = "INFO_VERSION.CTRL_UNIT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_VERSION__CTRL_UNIT, str_name);

		str_name = "INFO_VERSION.MTR_DRV";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_VERSION__MTR_DRV, str_name);

		str_name = "INFO_VERSION.AMB_SW";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_VERSION__AMB_SW, str_name);

		//
		str_name = "INFO.SPEED_SETPOINT.HZ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_SPEED_SETPOINT_HZ, str_name);

		str_name = "INFO.SPEED_SETPOINT.RPM";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_SPEED_SETPOINT_RPM, str_name);

		//
		str_name = "INFO.TMS_TEMPERATURE_SETTING";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_TMS_TEMPERATURE_SETTING, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(7.0, MON_ID__STATE_CHECK);
	}
	return 1;
}

int CObj__STP_SERIAL::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__OFFLINE_ALARM;

		alarm_title  = title;
		alarm_title += "Offline.";

		alarm_msg  = "Controller is Offline.\n";
		alarm_msg += "Please, Check Communication Status !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__CURRENT_STATUS__LOCAL_MODE;

		alarm_title  = title;
		alarm_title += "Controller is Local Mode.\n";

		alarm_msg = "Please, Check Mode.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_POWER_OFF__TIMEOUT;

		alarm_title  = title;
		alarm_title += "Pump Power Off TimeOut.";

		alarm_msg  = "Power Sensor -> Off : Timeout.\n";
		alarm_msg += "Please, Check Pump Status !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_POWER_ON__TIMEOUT;

		alarm_title  = title;
		alarm_title += "Pump Power On TimeOut.";

		alarm_msg  = "Power Sensor -> On : Timeout.\n";
		alarm_msg += "Please, Check Pump Status !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_REMOTE__TIMEOUT;

		alarm_title  = title;
		alarm_title += "Pump Remote Command TimeOut.";

		alarm_msg  = "Power Sensor -> Remote : Timeout.\n";
		alarm_msg += "Please, Check Pump Status !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_LOCAL__TIMEOUT;

		alarm_title  = title;
		alarm_title += "Pump Local Command TimeOut.";

		alarm_msg  = "Power Sensor -> Local : Timeout.\n";
		alarm_msg += "Please, Check Pump Status !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_ACCELERATION__TIMEOUT;

		alarm_title  = title;
		alarm_title += "Pump Acceleration TimeOut.";

		alarm_msg  = "Power Sensor -> Acceleration : Timeout.\n";
		alarm_msg += "Please, Check Pump Status !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


// ...
#define APP_DSP__CTRL_MODE				"LOCAL  REMOTE"
#define APP_DSP__RUN_STOP				"OFF  ON"

#define APP_DSP__COMM_STS				"OFFLINE  ONLINE"
#define APP_DSP__CTRL_STS				"UNKNOWN LOCAL  REMOTE"
#define APP_DSP__PUMP_STS				"UNKNOWN OFF ON"
#define APP_DSP__RUN_STS				"UNKNOWN STOP START"
#define APP_DSP__SPEED_STS				"UNKNOWN STOP START ACCELERATING NORMAL BRAKING"
#define APP_DSP__TEMP_STS				"UNKNOWN NORMAL WARNING"
#define APP_DSP__FAULT_STS				"UNKNOWN OK FAULT"


int CObj__STP_SERIAL::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;
	CString str_list;

	// AO ...
	{
		str_name = "ao.SET_SPEED_HZ";
		IO__ADD_ANALOG_WRITE(str_name, "Hz", 0, 0.0, 450.0);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__SET_SPEED_HZ, str_name);
	}

	// DO ...
	{
		str_list  = CMMD__START;
		str_list += " ";
		str_list += CMMD__STOP;
		str_list += " ";
		str_list += CMMD__RESET;

		str_name = "do.OP.CMMD";
		IO__ADD_DIGITAL_WRITE(str_name, str_list);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__OP_CMMD, str_name);
	}

	// DI ...
	{
		str_name = "di.COMM.STS";
		IO__ADD_DIGITAL_READ__MANUAL(str_name, APP_DSP__COMM_STS);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__COMM_STS, str_name);
	}

	// SI ...
	{
		str_name = "si.ReadMeas.HEXA";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__ReadMeas_HEXA, str_name);

		str_name = "si.ReadModFonct";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__ReadModFonct, str_name);

		str_name = "si.All_Version";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__All_Version, str_name);

		str_name = "si.ReadSetPoint";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__ReadSetPoint, str_name);

		str_name = "si.ReadMotorTemp";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__ReadMotorTemp, str_name);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__STP_SERIAL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xAPP_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xAPP_LOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xAPP_LOG_CTRL->DISABLE__TIME_LOG();
		xAPP_LOG_CTRL->WRITE__LOG(log_msg);

		xAPP_LOG_CTRL->ENABLE__TIME_LOG();
		xAPP_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}

int CObj__STP_SERIAL::__INITIALIZE__IO(p_io_para)
{
	int com_port = -1;

	int nRate   = 9600;
	int nByte   = 8;			
	int nStop   = 1;			
	int nParity = 0;		// 0, 1, 2, 3, 4  :  No, Odd, Even, Mark, Space

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

		xAPP_LOG_CTRL->WRITE__LOG(log_msg);
		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		CString ch_data;

		ch_data.Format("%1d", com_port);
		sCH__INFO_DRV_COM_PORT->Set__DATA(ch_data);

		ch_data.Format("%1d", nRate);
		sCH__INFO_DRV_BAUD_RATE->Set__DATA(ch_data);
	}

	if(iActive__SIM_MODE < 0)
	{
		CString msg;

		mX_Serial->RTS__CHECK_SKIP();

		if(mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity) < 0)
		{
			msg.Format("Fail to do INIT__COMPORT: %d, ret:-1", com_port);
			Fnc__DRV_LOG(msg);
			// return -1;
		}

		msg.Format("Initialize RS-232 Complete");
		Fnc__DRV_LOG(msg);
	}

	m_nCommState = DRV__OFFLINE;
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__STP_SERIAL::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		Fnc__APP_LOG(log_msg);
	}

	// ...
	{
		     IF__CTRL_MODE(sMODE__INIT)						flag = Call__INIT(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PUMP_ON)					flag = Call__PUMP_ON(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__AUTO_STOP)				flag = Call__AUTO_STOP(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__AUTO_STOP_NO_WAIT)		flag = Call__AUTO_STOP_NO_WAIT(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__CHECK_SUM)				flag = Call__CHECK_SUM(p_variable, p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		Fnc__APP_LOG(log_msg);

		dCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		Fnc__APP_LOG(log_msg);
	}

	return flag;
}

int CObj__STP_SERIAL::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__STATE_CHECK)		Mon__STATE_CHECK(p_variable, p_alarm);

	return 1;
}

int CObj__STP_SERIAL::__CLOSE__OBJECT()
{

	return 1;
}
