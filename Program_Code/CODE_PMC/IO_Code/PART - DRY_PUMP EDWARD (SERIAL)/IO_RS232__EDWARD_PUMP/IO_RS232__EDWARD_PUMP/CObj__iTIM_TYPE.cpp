#include "StdAfx.h"
#include "CObj__iTIM_TYPE.h"



//--------------------------------------------------------------------------------
CObj__iTIM_TYPE::CObj__iTIM_TYPE()
{
	m_str_cmd_err = "";

}
CObj__iTIM_TYPE::~CObj__iTIM_TYPE()
{

}


//--------------------------------------------------------------------------------
int CObj__iTIM_TYPE::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	    "INIT");
		ADD__CTRL_VAR(sMODE__LOCAL,     "LOCAL");
		ADD__CTRL_VAR(sMODE__REMOTE,    "REMOTE");

		ADD__CTRL_VAR(sMODE__PUMP_ON,   "PUMP_ON");
		ADD__CTRL_VAR(sMODE__AUTO_STOP, "AUTO_STOP");
		ADD__CTRL_VAR(sMODE__FAST_STOP, "FAST_STOP");
	}
	return 1;
}
int CObj__iTIM_TYPE::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee";

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR							1

int CObj__iTIM_TYPE::__DEFINE__VARIABLE_STD(p_variable)
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

		str_name = "DRV.LOG.PARAM.LOG.START";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"STOP START","");
		LINK__VAR_DIGITAL_CTRL(dCH__DRV_LOG_PARAM_START_STOP,str_name);

		str_name = "OBJ.STATUS";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,dsc_item_list,"");
		LINK__VAR_DIGITAL_CTRL(dCH__OBJ_STATUS,str_name);

		//.....
		str_name = "INR.sMSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SEQUENCE_MSG,str_name);

		str_name = "sAPP.COMM.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__COMM_STS,str_name);

		str_name = "OTR.OUT.MON.sPUMP.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PUMP_STS,str_name);
	}

	// ...
	{
		str_name = "OTR.IN.CFG.PUMP.ON.SKIP.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"DISABLE ENABLE", "");
		LINK__VAR_STRING_CTRL(sCH__CFG_SKIP_MODE,str_name);

		str_name = "OTR.IN.CFG.AUTO.STOP.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec", 0, 1, 3600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_AUTO_STOP_TIMEOUT,str_name);

		str_name = "OTR.IN.CFG.FAST.STOP.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec", 0, 1, 3600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_FAST_STOP_TIMEOUT,str_name);
	}

	// ...
	{
		str_name = "CFG.PUMP.CTRL.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"AUTO MANUAL","");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PUMP_CTRL_MODE,str_name);
	}

	// INFO ...
	{
		str_name = "INFO.DRV.COM_PORT";	  
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_COM_PORT, str_name);

		str_name = "INFO.DRV.BAUD_RATE";	  
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BAUD_RATE, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(7.0, MON_ID__IO_MONITOR);
	}
	return 1;
}
int CObj__iTIM_TYPE::__DEFINE__ALARM(p_alarm)
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
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__CURRENT_STATUS__LOCAL_MODE;

		alarm_title  = title;
		alarm_title += "Local Status.";

		alarm_msg = "Please, Check Control Mode !";

		l_act.RemoveAll();
		l_act.Add("CHECK");

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
		//	l_act.Add("RETRY");
		//	l_act.Add("ABORT");
		l_act.Add("CHECK");

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
		//	l_act.Add("RETRY");
		//	l_act.Add("ABORT");
		l_act.Add("CHECK");

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
		//	l_act.Add("RETRY");
		//	l_act.Add("ABORT");
		l_act.Add("CHECK");

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
		//	l_act.Add("RETRY");
		//	l_act.Add("ABORT");
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_CMD_1_ERROR;

		alarm_title  = title;
		alarm_title += "Pump Command Error [ERR 1].";

		alarm_msg  = "After Send Command, Received following Error Response.\n";
		alarm_msg += "[From Manual..]\n";
		alarm_msg += "The message sent was not a valid query or\n";
		alarm_msg += "command message.\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_CMD_2_ERROR;

		alarm_title  = title;
		alarm_title += "Pump Command Error [ERR 2].";

		alarm_msg  = "After Send Command, Received following Error Response.\n";
		alarm_msg += "[From Manual..]\n";
		alarm_msg += "Part of a message (for example, {parameter}) was not found. \n";
		alarm_msg += "Resend the message in the correct format.\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_CMD_3_ERROR;

		alarm_title  = title;
		alarm_title += "Pump Command Error [ERR 3].";

		alarm_msg  = "After Send Command, Received following Error Response.\n";
		alarm_msg += "[From Manual..]\n";
		alarm_msg += "Part of a message was outside the valid range \n";
		alarm_msg += "for example the {0:1} digit in a command message was higher than 1.\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_CMD_4_ERROR;

		alarm_title  = title;
		alarm_title += "Pump Command Error [ERR 4:Parameter's value not received].";

		alarm_msg  = "After Send Command, Received following Error Response.\n";
		alarm_msg += "[From Manual..]\n";
		alarm_msg += "The corresponding sensor may be faulty or disconnected. \n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_CMD_5_ERROR;

		alarm_title  = title;
		alarm_title += "Pump Command Error [ERR 5:Command not possible].";

		alarm_msg  = "After Send Command, Received following Error Response.\n";
		alarm_msg += "[From Manual..]\n";
		alarm_msg += "You have tried to take or release control,\n";
		alarm_msg += "but another module has control of the dry pumping system. \n";
		alarm_msg += "Release control from the other module, then try again.\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_CONTROL_MODE__AUTO_TO_MANUAL;

		alarm_title  = title;
		alarm_title += "Control Mode : Converted \"AUTO\" To \"MANUAL\".";

		alarm_msg  = "Dry pump's control mode is converted \"AUTO\" to \"MANUAL\". \n";
		alarm_msg += "Please, check dry pump's control mode. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);		
	}

	// ...
	{
		alarm_id = ALID__PUMP_CONTROL_MODE__MANUAL_TO_AUTO;

		alarm_title  = title;
		alarm_title += "Control Mode : Converted \"MANUAL\" to \"AUTO\".";

		alarm_msg  = "Dry pump's control mode is converted \"MANUAL\" to \"AUTO\". \n";
		alarm_msg += "Please, check dry pump's control mode. \n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);		
	}

	return 1;
}


// ...
#define APP_DSP__COMM_STS				"OFFLINE  ONLINE"
#define APP_DSP__CTRL_MODE				"LOCAL  REMOTE"
#define APP_DSP__CTRL_STS				"LOCAL  REMOTE"
#define APP_DSP__PUMP_STS				"OFF  SwitchingOn  SwitchingOff  SwitchingOff  ON"
#define APP_DSP__RUN_STOP				"NONE  FAST_STOP  AUTO_STOP  ON"

int CObj__iTIM_TYPE::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;

	// Digital Channel ...
	// DO ...
	{
		str_name = "edo.CTRL.MODE";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__CTRL_MODE);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__CTRL_MODE, str_name);

		str_name = "edo.RUN.STOP";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__RUN_STOP);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__RUN_STOP, str_name);
	}
	// DI ...
	{
		str_name = "edi.COMM.STS";
		IO__ADD_DIGITAL_READ(str_name, APP_DSP__COMM_STS);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__COMM_STS, str_name);

		str_name = "edi.CTRL.STS";
		IO__ADD_DIGITAL_READ(str_name, APP_DSP__CTRL_STS);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__CTRL_STS, str_name);

		str_name = "edi.PUMP.STS";
		IO__ADD_DIGITAL_READ(str_name, APP_DSP__PUMP_STS);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__PUMP_STS, str_name);
	}

	// String Channel ...
	// SI ...
	{
		str_name = "esi.PUMP.CMD.ERR";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__CMD_ERR, str_name);

		str_name = "esi.PUMP.ELECT.SUPPLY.VOLT";			// V
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__ELEC_SUPPLY_VOLT, str_name);

		str_name = "esi.PUMP.PHASE.CURRENT";				// A
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__PHASE_CURRENT, str_name);

		str_name = "esi.PUMP.POWER";						// kW
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__PUMP_POWER, str_name);

		str_name = "esi.VOLT.READ.FROM.THERMISTOR";			// mV
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__VOLT_READ_THERMISTOR, str_name);

		str_name = "esi.TOTAL.RUN.TIME";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__TOTAL_RUN_TIME, str_name);

		str_name = "esi.TIME.TO.STOP";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__TIME_TO_STOP, str_name);

		str_name = "esi.N2.SUPPLY.STS";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__N2_SUPPLY_STS, str_name);

		str_name = "esi.MOTOR.TEMPERATURE";		// 'C
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__MOTOR_TEMP, str_name);

		str_name = "esi.BODY.TEMPERATURE";		// 'C
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__BODY_TEMP, str_name);

		str_name = "esi.WATER.FLOW.STATUS";		// 0, 1
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__WATER_FLOW_STS, str_name);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__iTIM_TYPE::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	iFlag__APP_LOG = 1;

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

		iACTIVE_SIM = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}
int CObj__iTIM_TYPE::__INITIALIZE__IO(p_io_para)
{
	//-------------------------------------------------------
	// Set Driver Parameter

	// ...
	int com_port = -1;

	int nRate   = 9600;
	int nByte   = 8;			
	int nStop   = 1;			
	int nParity = 0;		// 0, 1, 2, 3, 4  :  No, Odd, Even, Mark, Space

	// ...
	m_nCommState = OFFLINE;
	m_Rcv_Time	 = 1000;

	m_Term_Str[0] = CR;	
	m_Term_Str[1] = 0;

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

		msg.Format("m_nTimeout : %1d (msec) \n", m_Rcv_Time);
		log_msg += msg;

		xAPP_LOG_CTRL->WRITE__LOG(log_msg);
		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
	}

	if(iACTIVE_SIM < 0)
	{
		mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity);

		// ...
		{
			CString str_log;

			str_log.Format("PortNum:%d, Rate:%d, Byte:%d, Stop:%d, Parity:%d", com_port, nRate, nByte, nStop, nParity);
			Fnc__DRV_LOG(str_log);
		}
	}

	// ...
	{
		CString ch_data;

		ch_data.Format("%1d", com_port);
		sCH__INFO_DRV_COM_PORT->Set__DATA(ch_data);

		ch_data.Format("%1d", nRate);
		sCH__INFO_DRV_BAUD_RATE->Set__DATA(ch_data);
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__iTIM_TYPE::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		sCH__SEQUENCE_MSG->Set__DATA(log_msg);
		Fnc__APP_LOG(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__LOCAL)			flag = Call__LOCAL(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__REMOTE)			flag = Call__REMOTE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PUMP_ON)			flag = Call__PUMP_ON(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__AUTO_STOP)		flag = Call__AUTO_STOP(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__FAST_STOP)		flag = Call__FAST_STOP(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		sCH__SEQUENCE_MSG->Set__DATA(log_msg);
		Fnc__APP_LOG(log_msg);

		dCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__SEQUENCE_MSG->Set__DATA(log_msg);
		Fnc__APP_LOG(log_msg);
	}

	return flag;
}

int CObj__iTIM_TYPE::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable,p_alarm);
			break;
	}

	return 1;
}

int CObj__iTIM_TYPE::__CLOSE__OBJECT()
{

	return 1;
}
