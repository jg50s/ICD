#include "StdAfx.h"
#include "CObj__UNIT_TYPE.h"



//--------------------------------------------------------------------------------
CObj__UNIT_TYPE::CObj__UNIT_TYPE()
{
	for (int i=0; i<MAX_MFC; i++)
	{
		m_szFirm_Revision[i] = "0";
	}

	m_BoardID = 0;
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
#define  MON_ID__STATE_CHECK					1


int CObj__UNIT_TYPE::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString def_name;
	CString def_value;
	CString str_name;
	CString str_temp;
	int i;

	// ...
	sList__MAC_ID.RemoveAll();
	sList__VAR_ID.RemoveAll();

	// ...
	{
		def_name = "DATA.BOARD_ID";
		p_variable->Get__DEF_CONST_DATA(def_name, def_value);
		m_BoardID = atoi(def_value);

		def_name = "DATA.MFC_SIZE";
		p_variable->Get__DEF_CONST_DATA(def_name, def_value);

		int i_limit = atoi(def_value);
		if(i_limit > MAX_MFC)			i_limit = MAX_MFC;

		for(i=0; i<i_limit; i++)
		{
			int id = i + 1;

			def_name.Format("MFC.Mac_ID.%1d", id);
			p_variable->Get__DEF_CONST_DATA(def_name, def_value);
			sList__MAC_ID.Add(def_value);

			def_name.Format("MFC.Var_ID.%1d", id);
			p_variable->Get__DEF_CONST_DATA(def_name, def_value);
			sList__VAR_ID.Add(def_value);
		}
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

	// CFG ...
	{
		for(i=0; i<MAX_MFC; i++)
		{
			int id = i + 1;

			str_name.Format("CFG.MFC%1d.USE", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_MFC_USE_X[i], str_name);
		}

		str_name = "CFG.BAUD_RATE.NEXT_APPLY";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "38400 19200 9600", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_BAUD_RATE_NEXT_APPLY, str_name);		
	}

	// USER ...
	{
		str_name = "USER.INFO.UPDATE.REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__USER_INFO_UPDATE_REQ, str_name);
	}

	// INFO ...
	{
		str_name = "INFO.DRV.COM_PORT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_COM_PORT, str_name);

		str_name = "INFO.DRV.BAUD_RATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BAUD_RATE, str_name);

		str_name = "INFO.DRV.END_STRING";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_END_STRING, str_name);

		str_name = "INFO.DRV.RECV.TIMEOUT.mSEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_RECV_TIMEOUT_mSEC, str_name);

		str_name = "INFO.DRV.RETRY.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_RETRY_COUNT, str_name);

		str_name = "INFO.MFC.BOARD_ID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_MFC_BOARD_ID, str_name);

		int i_limit = sList__VAR_ID.GetSize();
		for(i=0; i<i_limit; i++)
		{
			CString str_id = sList__VAR_ID[i];
			
			str_name.Format("INFO.MFC.MACID.%s", str_id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__INFO_MFC_MACID_X[i], str_name);

			str_name.Format("INFO.MFC.SEND_ID.%s", str_id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__INFO_MFC_SEND_ID_X[i], str_name);
		}
	}
	// MON ...
	{
		int i_limit = sList__VAR_ID.GetSize();

		for(i=0; i<i_limit; i++)
		{
			CString str_id = sList__VAR_ID[i];

			str_name.Format("MON.MFC.VERSION.%s", str_id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_MFC_VERSION_X[i], str_name);

			str_name.Format("MON.MFC.VLV.STS.%s", str_id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_MFC_VLV_STS_X[i], str_name);
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__STATE_CHECK);
	}
	return 1;
}
int CObj__UNIT_TYPE::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	int alarm_id;
	CString alarm_title;
	CString alarm_msg;
	CString alarm_bff;
	CStringArray l_act;

	// ...
	int i_limit = sList__MAC_ID.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString var_id = sList__VAR_ID[i];

		// ...
		{
			alarm_id = ALID__GASx_OFFLINE + i;

			alarm_title = title;
			alarm_bff.Format("GAS[%s] Offline.", var_id);
			alarm_title += alarm_bff;

			alarm_msg.Format("MFC[%s] Controller is Offline.\n", var_id);
			alarm_msg += "Please, check communication status ! \n";
		
			l_act.RemoveAll();
			l_act.Add("CHECK");
	
			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
		// ...
		{
			alarm_id = ALID__GASx_CONTROL_TIMEOUT + i;

			alarm_title = title;
			alarm_bff.Format("GAS[%s] Control Timeout.", var_id);
			alarm_title += alarm_bff;

			alarm_msg.Format("MFC[%s] Controller is Timeout.\n", var_id);
			alarm_msg += "Please, check MFC control status !";

			l_act.RemoveAll();
			l_act.Add("CHECK");

			ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
		}
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
	CString str_index;

	int i_limit = sList__MAC_ID.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString var_id = sList__VAR_ID[i];
		CString mac_id = sList__MAC_ID[i];

		str_index.Format("%1d", i);

		// AI ...
		{
			str_name.Format("ai.MFC%s.FLOW", var_id);
			p_analog_io->Add__ANALOG_READ_EX(str_name, "101", "sccm", 1, -100, 100, mac_id, str_index, "", 0.1);

			//
			str_name.Format("ai.MFC%s.VOLT", var_id);
			p_analog_io->Add__ANALOG_READ_EX(str_name, "102", "volt", 1,-15.00, 15, mac_id, str_index, "", -1);

			str_name.Format("ai.MFC%s.SETPOINT", var_id);
			p_analog_io->Add__ANALOG_READ_EX(str_name, "103", "sccm", 1,-100, 100, mac_id, str_index, "", -1);

			str_name.Format("ai.MFC%s.MACID", var_id);
			p_analog_io->Add__ANALOG_READ_EX(str_name, "104", "num", 0, -100, 100, mac_id, str_index, "", -1);
		}
		// AO ...
		{
			str_name.Format("ao.MFC%s.SETPOINT", var_id);
			p_analog_io->Add__ANALOG_WRITE_EX(str_name, "150", "sccm", 1,-100, 100, mac_id, str_index, "");
		}

		// DO ...
		{
			str_name.Format("do.MFC%s.GET.FIRM.VER", var_id);
			p_digital_io->Add__DIGITAL_WRITE_EX(str_name, "251", "GET", mac_id, str_index, "");
			LINK__IO_VAR_DIGITAL_CTRL(dCH__DO_MFC_VERSION_X[i], str_name);

			//
			str_name.Format("do.MFC%s.INIT", var_id);
			p_digital_io->Add__DIGITAL_WRITE_EX(str_name, "252",APP_DSP__UNIT_INIT, mac_id, str_index, "");

			str_name.Format("do.MFC%s.FREEZE.FOLLOW", var_id);
			p_digital_io->Add__DIGITAL_WRITE_EX(str_name, "253",APP_DSP__FREEZE_FOLLOW, mac_id, str_index, "");

			str_name.Format("do.MFC%s.OVERRIDE.MODE", var_id);
			p_digital_io->Add__DIGITAL_WRITE_EX(str_name, "254",APP_DSP__OVERMODE, mac_id, str_index, "");

			str_name.Format("do.MFC%s.VALVE.SET", var_id);
			p_digital_io->Add__DIGITAL_WRITE_EX(str_name, "255",APP_DSP__VALVE_CTRL, mac_id, str_index, "");

			str_name.Format("do.MFC%s.CTRL.MODE", var_id);
			p_digital_io->Add__DIGITAL_WRITE_EX(str_name, "256",APP_DSP__UNIT_CTRL, mac_id, str_index, "");
		}	
		// DI ...
		{
			str_name.Format("di.MFC%s.COMM.STS", var_id);
			p_digital_io->Add__DIGITAL_READ_EX(str_name, "201",APP_DSP__COMM_STS, mac_id, str_index, "", 1);
			LINK__IO_VAR_DIGITAL_CTRL(dCH__DI_MFC_COMM_STATE_X[i], str_name);

			str_name.Format("di.MFC%s.VALVE.STS", var_id);
			p_digital_io->Add__DIGITAL_READ_EX(str_name, "202",APP_DSP__VALVE_CTRL, mac_id, str_index, "", -1);
			LINK__IO_VAR_DIGITAL_CTRL(dCH__DI_MFC_VLV_CTRL_X[i], str_name);
		}
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__UNIT_TYPE::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString obj_name;
	CString var_name;
	CString ch_data;
	
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
		def_name = "DATA.BOARD_ID";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		def_name = "DATA.MFC_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		int i_limit = atoi(def_data);

		for(int i=0; i<i_limit; i++)
		{
			int id = i + 1;

			def_name.Format("MFC.Mac_ID.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			def_name.Format("MFC.Var_ID.%1d", id);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		}
	}

	// ...
	{
		ch_data.Format("%1d", m_BoardID);
		sCH__INFO_MFC_BOARD_ID->Set__DATA(ch_data);

		int i_limit = sList__MAC_ID.GetSize();
		for(int i=0; i<i_limit; i++)
		{
			sCH__INFO_MFC_MACID_X[i]->Set__DATA(sList__MAC_ID[i]);

			int send_id = m_BoardID + atoi(sList__MAC_ID[i]);
			ch_data.Format("%1d", send_id);
			sCH__INFO_MFC_SEND_ID_X[i]->Set__DATA(ch_data);
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
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

		sCH__INFO_DRV_END_STRING->Set__DATA("<CR><LF>");
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
				sCH__INFO_DRV_COM_PORT->Set__DATA(para_data);
			}
		}
	}

	// ...
	{
		CString str_data = dCH__CFG_BAUD_RATE_NEXT_APPLY->Get__STRING();		
		sCH__INFO_DRV_BAUD_RATE->Set__DATA(str_data);

		nRate = atoi(str_data);
	}

	// ...
	{
		m_nRetryCnt = 1;
		m_Rcv_Time = 300;		// ms

		// ...
		CString ch_data;

		ch_data.Format("%1d", m_Rcv_Time);
		sCH__INFO_DRV_RECV_TIMEOUT_mSEC->Set__DATA(ch_data);

		ch_data.Format("%1d", m_nRetryCnt);
		sCH__INFO_DRV_RETRY_COUNT->Set__DATA(ch_data);
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

	if(iActive__SIM_MODE < 0)
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
	if(id == MON_ID__STATE_CHECK)			Mon__STATE_CHECK(p_variable, p_alarm);

	return 1;
}

int CObj__UNIT_TYPE::__CLOSE__OBJECT()
{

	return 1;
}
