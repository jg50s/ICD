#include "StdAfx.h"
#include "CObj__ESC_SERIAL.h"


//--------------------------------------------------------------------------------
CObj__ESC_SERIAL::CObj__ESC_SERIAL()
{

}
CObj__ESC_SERIAL::~CObj__ESC_SERIAL()
{

}

//--------------------------------------------------------------------------------
int CObj__ESC_SERIAL::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__LOCAL,	 "LOCAL");
		ADD__CTRL_VAR(sMODE__REMOTE, "REMOTE");

		ADD__CTRL_VAR(sMODE__ON,  "ON");
		ADD__CTRL_VAR(sMODE__OFF, "OFF");

		ADD__CTRL_VAR(sMODE__RAMP_UP,   "RAMP.UP");
		ADD__CTRL_VAR(sMODE__RAMP_DOWN, "RAMP.DOWN");

		ADD__CTRL_VAR(sMODE__POSITIVE, "POSITIVE");
		ADD__CTRL_VAR(sMODE__NEGATIVE, "NEGATIVE");

		ADD__CTRL_VAR(sMODE__VOLTAGE_SET,       "VOLTAGE.SET");
		ADD__CTRL_VAR(sMODE__CURRENT_LIMIT_SET, "CURRENT_LIMIT.SET");

		ADD__CTRL_VAR(sMODE__PACKET_CHECK, "PACKET.CHECK");
	}
	return 1;
}
int CObj__ESC_SERIAL::__DEFINE__VERSION_HISTORY(version)
{
	version = "@pck 20180524 \n";

	return 1;
}


//.....
#define  MON_ID__MONITOR				1

#define  APP_DSP__MON_MODE				"IDLE	  RUN"
#define  APP_DSP__POSI_NEGA				"POSITIVE NEGATIVE"
#define  APP_DSP__OFF_ON				"OFF	  ON"
#define  APP_DSP__LOCAL_REMOTE			"LOCAL	  REMOTE"


int CObj__ESC_SERIAL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CString str_name;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// INFO ...
	{
		str_name = "INFO.DRV.COM_PORT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_COM_PORT, str_name);

		str_name = "INFO.DRV.PARAMETER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_PARAMETER, str_name);
	}

	// PARA ...
	{
		str_name = "PARA.VOLTAGE.SET";
		STD__ADD_ANALOG(str_name, "V", 1, 0, 3000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_VOLTAGE_SET, str_name);

		str_name = "PARA.CURRENT_LIMIT.SET";
		STD__ADD_ANALOG(str_name, "mA", 1, 0, 20);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_CURRENT_LIMIT_SET, str_name);

		//
		str_name = "PARA.RAMP_UP.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 9.9, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_RAMP_UP_TIME, str_name);

		str_name = "PARA.RAMP_DN.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 9.9, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_RAMP_DN_TIME, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.CURRENT_LIMIT.SET";
		STD__ADD_ANALOG(str_name, "mA", 1, 0, 20);
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CURRENT_LIMIT_SET, str_name);

		//
		str_name = "CFG.RAMP_UP.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 9.9, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RAMP_UP_TIME, str_name);

		str_name = "CFG.RAMP_DN.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 9.9, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RAMP_DN_TIME, str_name);
	}

	// MON ...
	{
		str_name = "MON.COMM.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMM_STS, str_name);

		//
		str_name = "MON.VOLTAGE.SETPOINT";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__MON_VOLTAGE_SETPOINT, str_name);

		str_name = "MON.CURRENT_LIMIT.SETPOINT";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__MON_CURRENT_LIMIT_SETPOINT, str_name);

		//
		str_name = "MON.VOLTAGE.READ";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__MON_VOLTAGE_READ, str_name);

		str_name = "MON.CURRENT.READ";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__MON_CURRENT_READ, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0,MON_ID__MONITOR);
	}
	return 1;
}
int CObj__ESC_SERIAL::__DEFINE__ALARM(p_alarm)
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
		alarm_title += "Offline !";

		alarm_msg = "Please, check the state of ESC controller. ";

		l_act.RemoveAll();
		l_act.Add("RETRY");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


// ...
#define APP_DSP__COMM_STATUS            "OFFLINE  ONLINE"


int CObj__ESC_SERIAL::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	//-------------------------------------------------------
	CString str_name;

	// AO ...
	{
		str_name = "ao.VOLTAGE.SETPOINT";
		IO__ADD_ANALOG_WRITE(str_name, "V", 1, 0, 3000);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__VOLTAGE_SET, str_name);

		str_name = "ao.CURRENT_LIMIT.SETPOINT";
		IO__ADD_ANALOG_WRITE(str_name, "V", 1, 0.0, 20.0);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__CURRENT_LIMIT_SET, str_name);

		//
		str_name = "ao.RAMP_UP.SETPOINT";
		IO__ADD_ANALOG_WRITE(str_name, "sec", 1, 0.0, 9.9);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__RAMP_UP_SET, str_name);

		str_name = "ao.RAMP_DN.SETPOINT";
		IO__ADD_ANALOG_WRITE(str_name, "sec", 1, 0.0, 9.9);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__RAMP_DN_SET, str_name);
	}
	// SI ...
	{
		str_name = "si.VOLTAGE.READ";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__VOLTAGE_READ, str_name);	

		str_name = "si.CURRENT.READ";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__CURRENT_READ, str_name);
	}

	// DO ...
	{
		str_name = "do.CONTROL.MODE";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__LOCAL_REMOTE);			
		LINK__IO_VAR_DIGITAL_CTRL(doCH__CONTROL_MODE, str_name);	

		str_name = "do.ECHO.MODE";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);		
		LINK__IO_VAR_DIGITAL_CTRL(doCH__ECHO_MODE, str_name);

		//
		str_name = "do.VOLTAGE.MODE";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__POSI_NEGA);		// +  -
		LINK__IO_VAR_DIGITAL_CTRL(doCH__VOLTAGE_MODE, str_name);

		str_name = "do.VOLTAGE.POWER";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);		
		LINK__IO_VAR_DIGITAL_CTRL(doCH__VOLTAGE_POWER, str_name);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__ESC_SERIAL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;

	// ...
	{
		CString file_name;
		CString log_msg;

		// APP Log ...
		{
			file_name.Format("%s__APP.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xI__APP_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xI__APP_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

			xI__APP_LOG_CTRL->DISABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG(log_msg);

			xI__APP_LOG_CTRL->ENABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG("   START   \n");
		}

		// DRV Log ...
		{
			file_name.Format("%s__DRV.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xI__DRV_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xI__DRV_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

			xI__DRV_LOG_CTRL->DISABLE__TIME_LOG();
			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);

			xI__DRV_LOG_CTRL->ENABLE__TIME_LOG();
			xI__DRV_LOG_CTRL->WRITE__LOG("   START   \n");
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}
int CObj__ESC_SERIAL::__INITIALIZE__IO(p_io_para)
{
	int com_port = -1;

	int nRate   = 9600;
	int nByte   = 8;			// 5, 6, 7, 8
	int nStop   = 1;			// 1, 2
	int nParity = 0;			// 0 ~ 4 : None, Odd, Even, Mark, Space

	// ...
	{
		CString str_cmmd;
		CString str_data;

		// 1.
		{
			str_cmmd = "COM_PORT";

			if(p_io_para->Get__PARAMETER_DATA(str_cmmd, str_data) > 0)
			{
				com_port = atoi(str_data);
			}
		}

		// ...
		CString str_info;

		str_info.Format("%1d", com_port);
		sCH__INFO_DRV_COM_PORT->Set__DATA(str_info);
	}

	// ...
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg = "Connect to Serial \n";

		log_bff.Format("Com Port: %1d \n", com_port);
		log_msg += log_bff;

		log_bff.Format("Baud Rate: %1d \n", nRate);
		log_msg += log_bff;

		log_bff.Format("Data Bit: %1d \n", nByte);
		log_msg += log_bff;

		log_bff.Format("Parity Bit: %1d \n", nParity);
		log_msg += log_bff;

		log_bff.Format("Stop Bit: %1d \n", nStop);
		log_msg += log_bff;

		//
		log_msg += "Terminal String : <CR> \n";							  
	}

	// ...
	{
		CString str_info;

		str_info.Format("Rate[%1d] DataBit[%1d] StopBit[%1d] Parity[%1d]",  
						nRate, nByte, nStop, nParity);

		sCH__INFO_DRV_PARAMETER->Set__DATA(str_info);

		//
		sPROTOCOL_INFO  = str_info;
		sPROTOCOL_INFO += "\n";
		sPROTOCOL_INFO += "Terminal String : [CR] \n";							  
	}

	if(iActive__SIM_MODE > 0)
	{	
		log_msg += "Initialize RS-232 Complete \n";
		log_msg += "Simulation Mode !!! \n";

		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
		xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
		return -1;
	}

	if(mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity) < 0)
	{
		log_bff.Format("Fail to do INIT__COMPORT: %d, ret:-1\n", com_port);
		log_msg += log_bff;

		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
		xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
		return -11;
	}
	else
	{
		log_msg += "Initialize RS-232 Complete \n";
	
		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
		xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__ESC_SERIAL::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	int flag = -1;

	// ...
	CString log_msg;

	// ...
	{
		log_msg.Format("%s Start ...", mode);
		sCH__OBJ_MSG->Set__DATA(log_msg);

		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)						flag = Call__INIT(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__LOCAL)					flag = Call__LOCAL(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__REMOTE)					flag = Call__REMOTE(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__ON)						flag = Call__ON(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__OFF)						flag = Call__OFF(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__RAMP_UP)					flag = Call__RAMP_UP(p_variable, p_alarm, false);
		ELSE_IF__CTRL_MODE(sMODE__RAMP_DOWN)				flag = Call__RAMP_DOWN(p_variable, p_alarm, false);

		ELSE_IF__CTRL_MODE(sMODE__POSITIVE)					flag = Call__POSITIVE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__NEGATIVE)					flag = Call__NEGATIVE(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__VOLTAGE_SET)				flag = Call__VOLTAGE_SET(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CURRENT_LIMIT_SET)		flag = Call__CURRENT_LIMIT_SET(p_variable, p_alarm, false);

		ELSE_IF__CTRL_MODE(sMODE__PACKET_CHECK)				flag = Call__PACKET_CHECK(p_variable, p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		log_msg.Format("%s Aborted (%1d)", mode, flag);
		sCH__OBJ_MSG->Set__DATA(log_msg);

		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		log_msg.Format("%s Completed (%1d)", mode, flag);
		sCH__OBJ_MSG->Set__DATA(log_msg);

		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
	}	

	return flag;
}

int CObj__ESC_SERIAL::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__MONITOR:
			Mon__MONITOR(p_variable,p_alarm);
			break;
	}

	return 1;
}
