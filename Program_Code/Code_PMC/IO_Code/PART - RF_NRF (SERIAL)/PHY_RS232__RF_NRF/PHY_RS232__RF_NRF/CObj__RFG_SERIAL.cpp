#include "StdAfx.h"
#include "CObj__RFG_SERIAL.h"



//--------------------------------------------------------------------------------
CObj__RFG_SERIAL::CObj__RFG_SERIAL()
{
	m_Rcv_Time	 = 250;
	m_RetryCnt	 = 3;

	//
	iUNIT__ADDR_ID = 0x80;

	dVALUE__PWR_MAX = 2000;
	iHEXA__PWR_MAX = 0x07d0;
}
CObj__RFG_SERIAL::~CObj__RFG_SERIAL()
{

}

//--------------------------------------------------------------------------------
int CObj__RFG_SERIAL::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");
		ADD__CTRL_VAR(sMODE__ON,  "ON");
		ADD__CTRL_VAR(sMODE__OFF, "OFF");
		ADD__CTRL_VAR(sMODE__ALARM_RESET, "ALARM.RESET");

		ADD__CTRL_VAR(sMODE__TEST_DRV, "TEST.DRV");
	}
	return 1;
}
int CObj__RFG_SERIAL::__DEFINE__VERSION_HISTORY(version)
{
	version = "2022.01.21 \n";

	return 1;
}


// ...
#define  MON_ID__MONITOR				1

#define  APP_DSP__COMM_STATUS           "OFFLINE  ONLINE"
#define  APP_DSP__OFF_ON				"OFF	  ON"


int CObj__RFG_SERIAL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// PARA ...
	{
		str_name = "PARA.SET.POWER";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "Watt", 0, 0, dVALUE__PWR_MAX, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_SET_POWER, str_name);
	}

	// MON ...
	{
		str_name = "MON.COMM.STS";
		STD__ADD_DIGITAL(str_name, APP_DSP__COMM_STATUS);
		LINK__VAR_DIGITAL_CTRL(dCH__MON_COMM_STS, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.DRV.LOG.ENABLE";
		STD__ADD_DIGITAL(str_name,  APP_DSP__OFF_ON);
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_DRV_LOG_ENABLE, str_name);

		str_name = "CFG.RF.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "CW  PULSE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_RF_MODE, str_name);
	}

	// INFO ...
	{
		str_name = "INFO.LAST.ERROR.CODE";	  
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__INFO_LAST_ERROR_CODE, str_name);

		//
		str_name = "INFO.POWER_SETPOINT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_POWER_SETPOINT, str_name);

		str_name = "INFO.FORWARD_POWER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_FORWARD_POWER, str_name);

		str_name = "INFO.REFLECT_POWER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_REFLECT_POWER, str_name);
	}

	// INFO,STS ...
	{
		// BYTE : 0
		str_name = "INFO.STS.HEXA_0";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_HEXA_0, str_name);

		str_name = "INFO.STS.RF_OUTPUT_CONTROL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_RF_OUTPUT_CONTROL, str_name);

		str_name = "INFO.STS.RF_MODE_CONTROL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_RF_MODE_CONTROL, str_name);

		str_name = "INFO.STS.ALARM";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_ALARM, str_name);

		// BYTE : 1
		str_name = "INFO.STS.HEXA_1";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_HEXA_1, str_name);
		
		str_name = "INFO.STS.TEMPERATURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_TEMPERATURE, str_name);

		str_name = "INFO.STS.INTERLOCK";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_INTERLOCK, str_name);
		
		str_name = "INFO.STS.AMP";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_AMP, str_name);
		
		str_name = "INFO.STS.HD_CON";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_HD_CON, str_name);
	}
	
	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0,MON_ID__MONITOR);
	}
	return 1;
}
int CObj__RFG_SERIAL::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__GEN_OFFLINE_ALARM;

		alarm_title  = title;
		alarm_title += "Generator Offline";

		alarm_msg = "Generator Offline.";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__GEN_RETRY_OVER_ALARM;

		alarm_title  = title;
		alarm_title += "Generator Communication Retry Over";

		alarm_msg = "Generator Communication Retry Over";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__RFG_SERIAL::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;

	// SI ...
	{
		str_name = "si.RF.STATE";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__RF_STATE, str_name);

		//
		str_name = "si.POWER.SERPOINT";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__POWER_SERPOINT, str_name);
		
		str_name = "si.POWER.FORWARD";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__POWER_FORWARD, str_name);
		
		str_name = "si.POWER.REFLECT";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__POWER_REFLECT, str_name);
	}

	// AO ...
	{
		str_name = "ao.POWER.SET";
		IO__ADD_ANALOG_WRITE(str_name, "W", 0, 0.0, 2000.0);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__POWER_SET, str_name);
	}

	// DO ...
	{
		str_name = "do.POWER.MODE";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);	
		LINK__IO_VAR_DIGITAL_CTRL(doCH__POWER_MODE, str_name);

		str_name = "do.ALARM.RESET";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);	
		LINK__IO_VAR_DIGITAL_CTRL(doCH__ALARM_RESET, str_name);	
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__RFG_SERIAL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

int CObj__RFG_SERIAL::__INITIALIZE__IO(p_io_para)
{
	int com_port = -1;

	int nRate   = 57600;
	int nByte   = 8;			// 5, 6, 7, 8
	int nStop   = 1;			// 1, 2
	int nParity = 2;			// None(0), Odd(1), Even(2), Mark(3), Space(4)

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
	}

	// ...
	{
		sPROTOCOL_INFO.Format("Rate[%1d] DataBit[%1d] StopBit[%1d] Parity[%1d] \n",
			                  nRate, nByte, nStop, nParity);

		sPROTOCOL_INFO += "Terminal String : [CR] \n";							  
	}

	if(iActive__SIM_MODE < 0)
	{
		mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity);
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__RFG_SERIAL::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	CString log_msg;
	int flag = -1;

	// ...
	{
		log_msg.Format("%s Started...", mode);
		sCH__OBJ_MSG->Set__DATA(log_msg);

		Write__APP_LOG(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ON)				flag = Call__POWER_SET(p_variable, p_alarm, true);
		ELSE_IF__CTRL_MODE(sMODE__OFF)				flag = Call__POWER_SET(p_variable, p_alarm, false);
		ELSE_IF__CTRL_MODE(sMODE__ALARM_RESET)		flag = Call__ALARM_RESET(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__TEST_DRV)			flag =  Call__TEST_DRV(p_variable, p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		log_msg.Format("%s Aborted (%1d)", mode,flag);

	}
	else
	{
		log_msg.Format("%s Completed (%1d)", mode,flag);
	}	
	Write__APP_LOG(log_msg);

	sCH__OBJ_MSG->Set__DATA(log_msg);
	return flag;
}

int CObj__RFG_SERIAL::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__MONITOR)
	{
		return Mon__MONITOR(p_variable,p_alarm);
	}
	return 1;
}

