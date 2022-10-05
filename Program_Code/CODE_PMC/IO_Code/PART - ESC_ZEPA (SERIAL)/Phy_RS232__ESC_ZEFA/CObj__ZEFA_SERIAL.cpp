#include "StdAfx.h"
#include "CObj__ZEFA_SERIAL.h"
#include "CCommon_DEF.h"


//--------------------------------------------------------------------------------
CObj__ZEFA_SERIAL::CObj__ZEFA_SERIAL()
{

}
CObj__ZEFA_SERIAL::~CObj__ZEFA_SERIAL()
{

}

//--------------------------------------------------------------------------------
int CObj__ZEFA_SERIAL::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,   "INIT");

		ADD__CTRL_VAR(sMODE__LOCAL,	 "LOCAL");
		ADD__CTRL_VAR(sMODE__REMOTE, "REMOTE");

		ADD__CTRL_VAR(sMODE__RESET,       "RESET");
		ADD__CTRL_VAR(sMODE__ALARM_CLEAR, "ALARM.CLEAR");

		ADD__CTRL_VAR(sMODE__ON,  "ON");
		ADD__CTRL_VAR(sMODE__OFF, "OFF");

		ADD__CTRL_VAR(sMODE__TOGGLE_ON,  "TOGGLE.ON");
		ADD__CTRL_VAR(sMODE__TOGGLE_OFF, "TOGGLE.OFF");

		//
		ADD__CTRL_VAR(sMODE__CURRENT_LIMIT_SET, "CURRENT_LIMIT.SET");

		ADD__CTRL_VAR(sMODE__RAMP_UP_SET,	"RAMP_UP.SET");
		ADD__CTRL_VAR(sMODE__RAMP_DOWN_SET,	"RAMP_DOWN.SET");

		//
		ADD__CTRL_VAR(sMODE__PROC_READY,  "PROC.READY");
		ADD__CTRL_VAR(sMODE__PROC_START,  "PROC.START");
	}

	return 1;
}
int CObj__ZEFA_SERIAL::__DEFINE__VERSION_HISTORY(version)
{
	version = "By jglee ... \n";

	return 1;
}


// ...
#define  MON_ID__STATE_CHECK			1

// ...
#define  APP_DSP__COMM_STATUS           "OFFLINE  ONLINE"
#define  APP_DSP__LOCAL_REMOTE			"LOCAL	  REMOTE"
#define  APP_DSP__OFF_ON				"OFF	  ON"
#define  APP_DSP__NO_YES				"NO		  YES"


int CObj__ZEFA_SERIAL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		//
		str_name = "COMM.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__COMM_STS, str_name);
	}

	// CFG...
	{
		str_name = "CFG.DRV_LOG.ENABLE";
		STD__ADD_DIGITAL(str_name, APP_DSP__NO_YES);
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_DRV_LOG_ENABLE, str_name);

		//
		str_name = "CFG.CURRENT.LIMIT.CH1";
		STD__ADD_ANALOG(str_name, "mA", 1, 0.3, 1.0);
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CURRENR_LIMIT_CH1, str_name);

		str_name = "CFG.CURRENT.LIMIT.CH2";
		STD__ADD_ANALOG(str_name, "mA", 1, 0.3, 1.0);
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CURRENR_LIMIT_CH2, str_name);

		//
		str_name = "CFG.RAMP.UP.SEC";
		STD__ADD_ANALOG(str_name, "sec", 1, 0.3, 9.9);
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RAMP_UP_SEC, str_name);

		str_name = "CFG.RAMP.DOWN.SEC";
		STD__ADD_ANALOG(str_name, "sec", 1, 0.3, 9.9);
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RAMP_DOWN_SEC, str_name);

		//
		str_name = "CFG.AUTO.TOGGLE.COUNT";
		STD__ADD_ANALOG(str_name, "times", 0, 1, 10);
		LINK__VAR_ANALOG_CTRL(aCH__CFG_AUTO_TOGGLE_COUNT, str_name);

		str_name = "CFG.AUTO.TOGGLE.VOLT";
		STD__ADD_ANALOG(str_name, "V", 0, 0, 2500);
		LINK__VAR_ANALOG_CTRL(aCH__CFG_AUTO_TOGGLE_VOLTAGE, str_name);

		str_name = "CFG.AUTO.TOGGLE.USE";
		STD__ADD_DIGITAL(str_name, APP_DSP__NO_YES);				
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_AUTO_TOGGLE_USE, str_name);
	}

	// PARA ...
	{
		str_name = "PARA.CURRENT_LIMIT.CH1";
		STD__ADD_ANALOG(str_name,  "mA", 1, 0.3, 1.0);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_CURRENT_LIMIT_CH1, str_name);

		str_name = "PARA.CURRENT_LIMIT.CH2";
		STD__ADD_ANALOG(str_name,  "mA", 1, 0.3, 1.0);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_CURRENT_LIMIT_CH2, str_name);

		//
		str_name = "PARA.VOLT_SET.CH1";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "V", 0, -2500, 2500, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_VOLT_SET_CH1, str_name);

		str_name = "PARA.VOLT_SET.CH2";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "V", 0, -2500, 2500, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_VOLT_SET_CH2, str_name);

		//
		str_name = "PARA.RAMP_UP.SEC";
		STD__ADD_ANALOG(str_name, "sec", 1, 0.3, 9.9);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_RAMP_UP_SEC, str_name);

		str_name = "PARA.RAMP_DOWN.SEC";
		STD__ADD_ANALOG(str_name, "sec", 1, 0.3, 9.9);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_RAMP_DOWN_SEC, str_name);
	}

	// RCP ...
	{
		str_name = "RCP.VOLT_SET.CH1";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "V", 0, -2500, 2500, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__RCP_VOLT_SET_CH1, str_name);

		str_name = "RCP.VOLT_SET.CH2";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "V", 0, -2500, 2500, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__RCP_VOLT_SET_CH2, str_name);

		//
		str_name = "RCP.RAMP_UP.SEC";
		STD__ADD_ANALOG(str_name, "sec", 1, 0.3, 9.9);
		LINK__VAR_ANALOG_CTRL(aCH__RCP_RAMP_UP_SEC, str_name);

		str_name = "RCP.RAMP_DOWN.SEC";
		STD__ADD_ANALOG(str_name, "sec", 1, 0.3, 9.9);
		LINK__VAR_ANALOG_CTRL(aCH__RCP_RAMP_DOWN_SEC, str_name);
	}

	// CUR ...
	{
		str_name = "CUR.REMOTE.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CUR_REMOTE_STATE, str_name);

		//
		str_name = "CUR.VOLT_SET.CH1";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "V", 0, -2500, 2500, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__CUR_VOLT_SET_CH1, str_name);

		str_name = "CUR.VOLT_SET.CH2";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "V", 0, -2500, 2500, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__CUR_VOLT_SET_CH2, str_name);

		//
		str_name = "CUR.CURRENT_LIMIT.CH1";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__CUR_CURRENT_LIMIT_CH1, str_name);

		str_name = "CUR.CURRENT_LIMIT.CH2";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__CUR_CURRENT_LIMIT_CH2, str_name);
	}

	// INFO.STS ...
	{
		str_name = "INFO_STS.VOLT.CH1";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_VOLT_CH1, str_name);

		str_name = "INFO_STS.VOLT.CH2";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_VOLT_CH2, str_name);

		//
		str_name = "INFO_STS.CURRENT.CH1";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_CURRENT_CH1, str_name);

		str_name = "INFO_STS.CURRENT.CH2";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_CURRENT_CH2, str_name);

		//
		str_name = "INFO_STS.OUTPUT";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_OUTPUT, str_name);

		str_name = "INFO_STS.TOGGLE";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_TOGGLE, str_name);

		str_name = "INFO_STS.REMOTE";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_REMOTE, str_name);
	}

	// INFO.CFG ...
	{
		str_name = "INFO_CFG.VOLT.CH1";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CFG_VOLT_CH1, str_name);

		str_name = "INFO_CFG.VOLT.CH2";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CFG_VOLT_CH2, str_name);

		//
		str_name = "INFO_CFG.CURR_LIMIT.CH1";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CFG_CURR_LIMIT_CH1, str_name);

		str_name = "INFO_CFG.CURR_LIMIT.CH2";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CFG_CURR_LIMIT_CH2, str_name);

		//
		str_name = "INFO_CFG.RAMP_UP.SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CFG_RAMP_UP_SEC, str_name);
		
		str_name = "INFO_CFG.RAMP_DOWN.SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CFG_RAMP_DOWN_SEC, str_name);

		//
		str_name = "INFO.AUTO_TOGGLE.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_AUTO_TOGGLE_COUNT, str_name);
		
		str_name = "INFO.AUTO_TOGGLE.VOLTAGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_AUTO_TOGGLE_VOLTAGE, str_name);

		//
		str_name = "INFO.VERSION_FIRMWARE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_VERSION_FIRMWARE, str_name);

		str_name = "INFO.VERSION_SOFTWARE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_VERSION_SOFTWARE, str_name);
	}

	// INFO.ERROR ...
	{
		str_name = "INFO.ERROR_ID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_ERROR_ID, str_name);

		//
		for(int i=0; i<_CFG__ERR_LINE_MAX; i++)
		{
			str_name.Format("INFO.ERROR_LINE.%1d", i+1);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__INFO_ERROR_LINE_X[i], str_name);
		}
	}

	// INFO.DRV ...
	{
		str_name = "INFO.DRV.COM_PORT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_COM_PORT, str_name);

		//
		str_name = "INFO.DRV.BAUD_RATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BAUD_RATE, str_name);

		str_name = "INFO.DRV.DATA_BIT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_DATA_BIT, str_name);

		str_name = "INFO.DRV.STOP_BIT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_STOP_BIT, str_name);

		str_name = "INFO.DRV.PARITY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_PARITY, str_name);

		//
		str_name = "INFO.DRV.END_SEND";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_END_SEND, str_name);

		str_name = "INFO.DRV.END_RECV";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_END_RECV, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__STATE_CHECK);
	}
	return 1;
}
int CObj__ZEFA_SERIAL::__DEFINE__ALARM(p_alarm)
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
		alarm_title += "Controller Offline";

		alarm_msg = "Controller Offline.";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ERROR_ID;

		alarm_title  = title;
		alarm_title += "수신된 Error 정보가 있습니다 !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__NO_REMOTE_MODE;

		alarm_title  = title;
		alarm_title += "Control Mode가 Remote 상태가 아닙니다 !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

// ...
int CObj__ZEFA_SERIAL::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;

	// DO ...
	{
		str_name = "do.OUTPUT.SET";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);			
		LINK__IO_VAR_DIGITAL_CTRL(doCH__OUTPUT_SET, str_name);	

		str_name = "do.TOGGLE.SET";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);			
		LINK__IO_VAR_DIGITAL_CTRL(doCH__TOGGLE_SET, str_name);

		str_name = "do.REMOTE.SET";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);			
		LINK__IO_VAR_DIGITAL_CTRL(doCH__REMOTE_SET, str_name);

		//
		str_name = "do.ALL_VOLT.SET";
		IO__ADD_DIGITAL_WRITE(str_name, "OFF ON SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__ALL_VOLT_SET, str_name);

		//
		str_name = "do.ERROR_CLEAR";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);			
		LINK__IO_VAR_DIGITAL_CTRL(doCH__ERROR_CLEAR, str_name);

		str_name = "do.SYSTEM_RESET";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);			
		LINK__IO_VAR_DIGITAL_CTRL(doCH__SYSTEM_RESET, str_name);
	}

	// SO ...
	{
		str_name = "so.CURRENT_LIMIT.SET";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__CURRENT_LIMIT_SET, str_name);

		//
		str_name = "so.RAMP_UP.SET";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__RAMP_UP_SET, str_name);

		str_name = "so.RAMP_DOWN.SET";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__RAMP_DOWN_SET, str_name);

		//
		str_name = "so.AUTO_TOGGLE_CNT.SET";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__AUTO_TOGGLE_CNT_SET, str_name);

		str_name = "so.AUTO_TOGGLE_VOLT.SET";
		IO__ADD_STRING_WRITE(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__AUTO_TOGGLE_VOLT_SET, str_name);
	}

	// SI ...
	{
		str_name = "si.STATE.READ";
		IO__ADD_STRING_READ_WITH_OPTION(str_name, "","","", 0.1, "");
		LINK__IO_VAR_STRING_CTRL(siCH__STATE_READ, str_name);

		str_name = "si.ERROR.READ";
		IO__ADD_STRING_READ_WITH_OPTION(str_name, "","","", 1, "");
		LINK__IO_VAR_STRING_CTRL(siCH__ERROR_READ, str_name);

		//
		str_name = "si.CFG_VOLT.ALL";	
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__CFG_VOLT_ALL, str_name);
		
		str_name = "si.CFG_CURR_LIMIT.ALL";	
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__CFG_CURR_LIMIT_ALL, str_name);

		//
		str_name = "si.CFG_RAMP_UP";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__CFG_RAMP_UP, str_name);
		
		str_name = "si.CFG_RAMP_DOWN";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__CFG_RAMP_DOWN, str_name);

		//
		str_name = "si.AUTO_TOGGLE.INFO";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__AUTO_TOGGLE_INFO, str_name);

		str_name = "si.ALL_VERSION.INFO";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__ALL_VERSION_INFO, str_name);
	}

	return 1;
}

//--------------------------------------------------------------------------------
int CObj__ZEFA_SERIAL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

	// PAra.Init...
	{
		aCH__PARA_VOLT_SET_CH1->Set__VALUE(0.0);
		aCH__PARA_VOLT_SET_CH2->Set__VALUE(0.0);

		aCH__RCP_VOLT_SET_CH1->Set__VALUE(0.0);
		aCH__RCP_VOLT_SET_CH2->Set__VALUE(0.0);

		//
		aCH__CUR_VOLT_SET_CH1->Set__VALUE(0.0);
		aCH__CUR_VOLT_SET_CH2->Set__VALUE(0.0);
	}
	return 1;
}
int CObj__ZEFA_SERIAL::__INITIALIZE__IO(p_io_para)
{
	int com_port = -1;

	int nRate   = 19200;
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

		sEND_RECV = (char) LF;
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

		ch_data = "LF";
		sCH__INFO_DRV_END_RECV->Set__DATA(ch_data);
	}

	if(iActive__SIM_MODE > 0)
	{
		sCH__CUR_REMOTE_STATE->Set__DATA(STR__REMOTE);
	}
	else
	{
		mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity);
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__ZEFA_SERIAL::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	CString msg;
	int flag = 1;

	// ...
	{
		msg.Format("%s Started...",mode);
		sCH__OBJ_MSG->Set__DATA(msg);

		Write__APP_LOG(msg);
	}

	if(mode.CompareNoCase(sMODE__INIT) != 0)
	{
		if(sCH__CUR_REMOTE_STATE->Check__DATA(STR__REMOTE) < 0)
		{
			flag = -1;

			// ...
			int alm_id = ALID__NO_REMOTE_MODE;
			CString alm_msg;
			CString r_act;

			alm_msg.Format(" \"%s\" 명령을 실행 할 수 없습니다. \n", mode);

			p_alarm->Check__ALARM(alm_id, r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
		}
	}

	if(flag > 0)
	{
			 IF__CTRL_MODE(sMODE__INIT)						flag = Call__INIT(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__LOCAL)					flag = Call__LOCAL(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__REMOTE)					flag = Call__REMOTE(p_variable,p_alarm);
	    
		ELSE_IF__CTRL_MODE(sMODE__RESET)					flag = Call__RESET(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ALARM_CLEAR)				flag = Call__ALARM_CLEAR(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__ON)						flag = Call__ON(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__OFF)						flag = Call__OFF(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__TOGGLE_ON)				flag = Call__TOGGLE(p_variable,p_alarm, true);
		ELSE_IF__CTRL_MODE(sMODE__TOGGLE_OFF)				flag = Call__TOGGLE(p_variable,p_alarm, false);

		ELSE_IF__CTRL_MODE(sMODE__CURRENT_LIMIT_SET)		flag = Call__CURRENT_LIMIT_SET(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__RAMP_UP_SET)				flag = Call__RAMP_UP_SET(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__RAMP_DOWN_SET)			flag = Call__RAMP_DOWN_SET(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PROC_READY)				flag = Call__PROC_READY(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PROC_START)				flag = Call__PROC_START(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		msg.Format("%s Aborted (%1d)", mode, flag);
		Write__APP_LOG(msg);
	}
	else
	{
		msg.Format("%s Completed (%1d)", mode, flag);
		Write__APP_LOG(msg);
	}	

	sCH__OBJ_MSG->Set__DATA(msg);
	return flag;
}

int CObj__ZEFA_SERIAL::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__STATE_CHECK)		Mon__STATE_CHECK(p_variable,p_alarm);

	return 1;
}
