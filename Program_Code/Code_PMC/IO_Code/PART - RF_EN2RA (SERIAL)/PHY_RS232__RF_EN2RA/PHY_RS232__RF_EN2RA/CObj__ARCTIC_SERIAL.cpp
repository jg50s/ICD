#include "StdAfx.h"
#include "CObj__ARCTIC_SERIAL.h"


//--------------------------------------------------------------------------------
CObj__ARCTIC_SERIAL::CObj__ARCTIC_SERIAL()
{

}
CObj__ARCTIC_SERIAL::~CObj__ARCTIC_SERIAL()
{

}

//--------------------------------------------------------------------------------
int CObj__ARCTIC_SERIAL::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	   "INIT");

		ADD__CTRL_VAR(sMODE__LOCAL,	   "LOCAL");
		ADD__CTRL_VAR(sMODE__REMOTE,   "REMOTE");

		ADD__CTRL_VAR(sMODE__ON,	   "ON");
		ADD__CTRL_VAR(sMODE__OFF,	   "OFF");
	}
	return 1;
}
int CObj__ARCTIC_SERIAL::__DEFINE__VERSION_HISTORY(version)
{
	version = "2022.01.01 \n";

	return 1;
}


// ...
#define  MON_ID__STATE_CHECK			1

#define  APP_DSP__COMM_STATUS           "OFFLINE  ONLINE"
#define  APP_DSP__OFF_ON				"OFF  ON"
#define  APP_DSP__NO_YES				"NO  YES"


int CObj__ARCTIC_SERIAL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// PARA ...
	{
		str_name = "PARA.SET.POWER";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "Watt", 0, 0, 7000, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_SET_POWER, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.DRV_CHAR_SEDN_DELAY.mSEC";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "msec", 0, 0, 100, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DRV_CHAR_SEDN_DELAY_mSEC, str_name);

		str_name = "CFG.DRV_LINE_SEDN_DELAY.mSEC";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "msec", 0, 0, 100, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DRV_LINE_SEDN_DELAY_mSEC, str_name);

		//
		str_name = "CFG.DRV_LOG.ENABLE";
		STD__ADD_DIGITAL(str_name, APP_DSP__NO_YES);
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_DRV_LOG_ENABLE, str_name);
	}

	// MON ...
	{
		str_name = "MON.COMM.STS";
		STD__ADD_DIGITAL(str_name, APP_DSP__COMM_STATUS);
		LINK__VAR_DIGITAL_CTRL(dCH__MON_COMM_STS, str_name);
	}

	// INFO.PART ...
	{
		str_name = "INFO.DELIVERED_POWER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DELIVERED_POWER, str_name);

		str_name = "INFO.POWER_SETPOINT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_POWER_SETPOINT, str_name);

		//
		str_name = "INFO.RF_VOLTAGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_RF_VOLTAGE, str_name);

		str_name = "INFO.RF_CURRENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_RF_CURRENT, str_name);

		//
		str_name = "INFO.DC_VOLTAGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DC_VOLTAGE, str_name);

		str_name = "INFO.DC_CURRENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DC_CURRENT, str_name);

		//
		str_name = "INFO.RF_PHASE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_RF_PHASE, str_name);

		str_name = "INFO.FREQUENCY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_FREQUENCY, str_name);

		str_name = "INFO.QFR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_QFR, str_name);

		//
		str_name = "INFO.PLASMA_IMPEDANCE_R";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PLASMA_IMPEDANCE_R, str_name);

		str_name = "INFO.PLASMA_IMPEDANCE_X";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PLASMA_IMPEDANCE_X, str_name);

		//
		str_name = "INFO.RUN_MODE_STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_RUN_MODE_STATE, str_name);

		str_name = "INFO.RUN_MODE_DATA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_RUN_MODE_DATA, str_name);

		//
		str_name = "INFO.INTERLOCK_STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_INTERLOCK_STATE, str_name);

		str_name = "INFO.INTERLOCK_DATA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_INTERLOCK_DATA, str_name);

		//
		str_name = "INFO.PLASMA_ON_ENABLE.TURN_ON.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PLASMA_ON_ENABLE_TURN_ON_STATE, str_name);

		str_name = "INFO.PLASMA_ON_ENABLE.OUTPUT_HIGH.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PLASMA_ON_ENABLE_OUTPUT_HIGH_STATE, str_name);

		//
		str_name = "INFO.DIGITAL_SET_POWER.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DIGITAL_SET_POWER_STATE, str_name);

		str_name = "INFO.DIGITAL_SET_POWER.VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DIGITAL_SET_POWER_VALUE, str_name);
	}

	// INFO.DRV ...
	{
		str_name = "INFO_DRV.COM_PORT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_COM_PORT, str_name);

		//
		str_name = "INFO_DRV.BAUD_RATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BAUD_RATE, str_name);

		str_name = "INFO_DRV.DATA_BIT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_DATA_BIT, str_name);

		str_name = "INFO_DRV.STOP_BIT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_STOP_BIT, str_name);

		str_name = "INFO_DRV.PARITY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_PARITY, str_name);

		//
		str_name = "INFO_DRV.END_SEND";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_END_SEND, str_name);

		str_name = "INFO_DRV.END_RECV";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_END_RECV, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0,MON_ID__STATE_CHECK);
	}
	return 1;
}
int CObj__ARCTIC_SERIAL::__DEFINE__ALARM(p_alarm)
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

int CObj__ARCTIC_SERIAL::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;

	// IO ...
	{
		str_name = "do.DIGITAL_INITIAL.CTRL";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);	
		LINK__IO_VAR_DIGITAL_CTRL(doCH__DIGITAL_INITIAL_CTRL, str_name);

		str_name = "ao.DIGITAL_POWER.SET";
		IO__ADD_ANALOG_WRITE(str_name, "watt", 0, 0.0, 7000.0);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__DIGITAL_POWER_SET, str_name);

		//
		str_name = "do.PLASMA_ON_ENABLE.TURN_ON";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);	
		LINK__IO_VAR_DIGITAL_CTRL(doCH__PLASMA_ON_ENABLE_TURN_ON, str_name);

		str_name = "do.PLASMA_ON_ENABLE.OUTPUT_HIGH";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);	
		LINK__IO_VAR_DIGITAL_CTRL(doCH__PLASMA_ON_ENABLE_OUTPUT_HIGH, str_name);

		//
		str_name = "si.ALL_STATE.GET";
		IO__ADD_STRING_READ_WITH_OPTION(str_name, "","","", 0.1, "");
		LINK__IO_VAR_STRING_CTRL(siCH__ALL_STATE_GET, str_name);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__ARCTIC_SERIAL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

int CObj__ARCTIC_SERIAL::__INITIALIZE__IO(p_io_para)
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
	}

	// ...
	{
		sEND_SEND = (char) LF;

		sEND_RECV  = (char) CR;
		sEND_RECV += (char) LF;
	}

	// ...
	{
		CString log_msg;
		CString log_bff;

		int i_limit;
		int i;

		log_msg  = "\n";
		log_msg += "Driver Info ... \n";

		// ...
		{
			sPROTOCOL_INFO = "";

			log_bff.Format(" * COM_PORT <- [%1d] \n", com_port);
			log_msg += log_bff;
			sPROTOCOL_INFO += log_bff;

			log_bff.Format(" * Rate <- [%1d] \n", nRate);
			log_msg += log_bff;
			sPROTOCOL_INFO += log_bff;

			log_bff.Format(" * Byte <- [%1d] \n", nByte);
			log_msg += log_bff;
			sPROTOCOL_INFO += log_bff;

			log_bff.Format(" * Stop <- [%1d] \n", nStop);
			log_msg += log_bff;
			sPROTOCOL_INFO += log_bff;

			log_bff.Format(" * Parity <- [%1d] \n", nParity);
			log_msg += log_bff;
			sPROTOCOL_INFO += log_bff;
		}

		// END.SEND ...
		{
			log_bff.Format(" * END_SEND <- ");
			log_msg += log_bff;

			i_limit = sEND_SEND.GetLength();
			for(i=0; i<i_limit; i++)
			{	
				log_bff.Format("[%02X] ", sEND_SEND[i]);
				log_msg += log_bff;
			}
			log_msg += "\n";
		}
		// END.RECV ...
		{
			log_bff.Format(" * END_RECV <- ");
			log_msg += log_bff;

			i_limit = sEND_RECV.GetLength();
			for(i=0; i<i_limit; i++)
			{	
				log_bff.Format("[%02X] ", sEND_RECV[i]);
				log_msg += log_bff;
			}
			log_msg += "\n";
		}

		Write__APP_LOG(log_msg);
	}

	// INFO.DRV ...
	{
		CString ch_data;

		ch_data.Format("%1d", com_port);
		sCH__INFO_DRV_COM_PORT->Set__DATA(ch_data);

		//
		ch_data.Format("%1d", nRate);
		sCH__INFO_DRV_BAUD_RATE->Set__DATA(ch_data);

		ch_data.Format("%1d", nByte);
		sCH__INFO_DRV_DATA_BIT->Set__DATA(ch_data);

		ch_data.Format("%1d", nStop);
		sCH__INFO_DRV_STOP_BIT->Set__DATA(ch_data);

		ch_data = "None";
		sCH__INFO_DRV_PARITY->Set__DATA(ch_data);

		//
		ch_data = "LF";
		sCH__INFO_DRV_END_SEND->Set__DATA(ch_data);

		ch_data = "CR LF";
		sCH__INFO_DRV_END_RECV->Set__DATA(ch_data);
	}

	bActive__DRV_FNC_START = false;

	if(iActive__SIM_MODE > 0)
	{
		return -1;
	}
	else
	{
		mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity);
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__ARCTIC_SERIAL::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
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

		ELSE_IF__CTRL_MODE(sMODE__LOCAL)			flag = Call__CTRL_MODE(p_variable, p_alarm, false);
		ELSE_IF__CTRL_MODE(sMODE__REMOTE)			flag = Call__CTRL_MODE(p_variable, p_alarm, true);

		ELSE_IF__CTRL_MODE(sMODE__ON)				flag = Call__POWER_SET(p_variable, p_alarm, true);
		ELSE_IF__CTRL_MODE(sMODE__OFF)				flag = Call__POWER_SET(p_variable, p_alarm, false);
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

int CObj__ARCTIC_SERIAL::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__STATE_CHECK)		return Mon__STATE_CHECK(p_variable, p_alarm);

	return 1;
}

