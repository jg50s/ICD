#include "StdAfx.h"
#include "CObj__VAT650_TYPE.h"



//--------------------------------------------------------------------------------
CObj__VAT650_TYPE::CObj__VAT650_TYPE()
{
	sObject_Name = "";
	m_nCommSts   = OFFLINE;

	m_sErrorCode = "UNKNOWN";  // <-- Unknown	//"E:000000";
	m_szAlarm    = "UNKNOWN";  // <-- Unknown	//"NONE";
}
CObj__VAT650_TYPE::~CObj__VAT650_TYPE()
{

}


//--------------------------------------------------------------------------------
int CObj__VAT650_TYPE::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,				"INIT");
		ADD__CTRL_VAR(sMODE__INIT_COMM,			"INIT.COMM");

		ADD__CTRL_VAR(sMODE__OPEN,				"OPEN");
		ADD__CTRL_VAR(sMODE__CLOSE,				"CLOSE");
		ADD__CTRL_VAR(sMODE__PRESSURE,			"PRESSURE_CONTROL");

		ADD__CTRL_VAR(sMODE__POSITION,			"POSITION_CONTROL");

		ADD__CTRL_VAR(sMODE__POSITION_WAIT,     "POSITION.WAIT");
		ADD__CTRL_VAR(sMODE__POSITION_NO_WAIT,  "POSITION.NO_WAIT");

		ADD__CTRL_VAR(sMODE__HOLD,				"HOLD");
		ADD__CTRL_VAR(sMODE__AUTO_LEARN,		"AUTO_LEARN");
	}
	return 1;
}
int CObj__VAT650_TYPE::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee";

	return 1;
}


// ...
#define  MON_ID__STATE_CHECK					1


int CObj__VAT650_TYPE::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

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
	}

	// ...
	{
		str_name = "APP.OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SEQUENCE_MSG,str_name);
	}
	
	// ...
	{
		str_name = "PARA.PRESSURE.SET";
		STD__ADD_ANALOG(str_name, "mTorr", 3, 0, MAX_GUI_RANGE_PRESSURE);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PRESSURE_SET, str_name);

		str_name = "PARA.POSITION.SET";
		STD__ADD_ANALOG(str_name, "--", 3, 0, MAX_GUI_RANGE_POSITION);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_POSITION_SET, str_name);

		//
		str_name = "INR.OUT.sPRESSURE.VALUE";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__MON_PRESSURE_VALUE,str_name);

		str_name = "INR.OUT.sPOSITION.VALUE";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__MON_CUR_POSITION_VALUE,str_name);

		str_name = "INR.aAUTO.LEARNING.CMD.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 600, 3600, "");	// 최소 10분
		LINK__VAR_ANALOG_CTRL(aCFG_CH__AUTO_LEARN_CMD_TIMEOUT,str_name);
	}

	// ...
	{
		str_name = "ERROR_CODE.1M_TYPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ERROR_CODE_1M_TYPE, str_name);

		//
		str_name = "CFG_RANGE.PRESSURE.1M_TYPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CFG_RANGE_PRESSURE_1M_TYPE, str_name);

		str_name = "CFG_RANGE.POSITION.1M_TYPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CFG_RANGE_POSITION_1M_TYPE, str_name);
	}

	// ...
	{
		str_name = "CFG.VALVE.INIT.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "OPEN CLOSE HOLD", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_VALVE_INIT_STATUS, str_name);

		str_name = "CFG.POS.COUNT.TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "_1000  10000", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_POS_COUNT_TYPE, str_name);
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
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATE_CHECK);
	}
	return 1;
}
int CObj__VAT650_TYPE::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s : ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__APC_OFFLINE_ALARM;

		alarm_title  = title;
		alarm_title += " - APC SYSTEM : Controller is Offline.";

		alarm_msg = "Check, Communication Status !";
	
		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__APC_REMOTE_CMD_TIMEOUT;

		alarm_title  = title;
		alarm_title += " - APC SYSTEM : CMD [REMOTE] is out of time.";

		alarm_msg = "Check, Controller Status !";
	
		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__APC_CONTROL_CMD_TIMEOUT;

		alarm_title  = title;
		alarm_title += " - APC SYSTEM : CMD [CONTROL] is out of time.";

		alarm_msg = "Check, CMD [OPEN, CLOSE, PRESSURE, POSITION, HOLD] Status !";
	
		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__APC_ALARM_EXIST;

		alarm_title  = title;
		alarm_title += " - APC SYSTEM : POSITION or AIR Error is exist.";

		alarm_msg = "Check, Device [POSITION or AIR Error] Status !";
	
		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__APC_COMM_ERROR_EXIST;

		alarm_title  = title;
		alarm_title += " - APC SYSTEM : Communication Error is exist.";

		alarm_msg = "Check, Device Communication Status.. Reference the manual !";
	
		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__APC_DEVICE_ERROR_EXIST;

		alarm_title  = title;
		alarm_title += " - APC SYSTEM : Device Error is exist.";

		alarm_msg = "Check, Device Error Status !";
	
		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__APC_NOT_REMOTE_STATUS;

		alarm_title  = title;
		alarm_title += " - APC SYSTEM : Not Remote Status.";

		alarm_msg = "Check, Device Remote Status !";
	
		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__APC_AUTO_LEARN_CMD_TIMEOUT;

		alarm_title  = title;
		alarm_title += " - APC SYSTEM : Auto Learning Command Timeout Error";

		alarm_msg = "Check, Device Status !";
	
		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__APC_POSITION_CTRL_TIMEOUT;

		alarm_title  = title;
		alarm_title += " - APC Position Control Timeout Error !";
		
		alarm_msg = "Please, check APC's status ! \n";
		
		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	
	// ...
	{
		alarm_id = ALID__APC_COMM_ERROR_CODE;

		alarm_title  = title;
		alarm_title += " - APC로부터 통신 Error Code가 수신 되었습니다. \n";

		alarm_msg = " - APC로부터 통신 Error Code가 수신 되었습니다. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	return 1;
}

int CObj__VAT650_TYPE
::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;
	CString item_list;

	// Analog Channel ...
	// AO ...
	{
		// Set Pressure
		str_name.Format("ao.Set.Pressure");
		IO__ADD_ANALOG_WRITE(str_name, "value", 3, 0, MAX_CFG_RANGE_PRESSURE);			// PRESSURE and SENSOR READING: 1000 ... 1000000
		LINK__IO_VAR_ANALOG_CTRL(xCH__aoSET_PRESSURE, str_name);

		// Set Position
		str_name.Format("ao.Set.Position");
		// POSITION: 0 = 0~1000, 1 = 0~10000, 2 = 0~100000
		IO__ADD_ANALOG_WRITE(str_name, "value", 3, 0, MAX_CFG_RANGE_POSITION);			// 0 ~ 100000 
		LINK__IO_VAR_ANALOG_CTRL(xCH__aoSET_POSITION, str_name);
	}
	// AI ...
	{
		// ...
		{
			str_name.Format("ai.Valve.Pos");

			p_analog_io->Add__ANALOG_READ_EX2(str_name, str_name, "cnt", 3, 0.0, 999999, "1","1","1", 0.1, "");
			LINK__IO_VAR_ANALOG_CTRL(xCH__aiVALVE_POS, str_name);
		}
		// ...
		{
			str_name.Format("ai.Valve.Press");

			p_analog_io->Add__ANALOG_READ_EX2(str_name, str_name, "mtorr", 3, -999999, 999999, "1","1","1", 0.1, "");
			LINK__IO_VAR_ANALOG_CTRL(xCH__aiVALVE_PRESS, str_name);
		}
	}
	
	// Digital Channel ...
	// DO ...
	{
		str_name.Format("do.Opr.Command");
		item_list.Format("UNKNOWN LOCAL REMOTE");
		IO__ADD_DIGITAL_WRITE(str_name, item_list);
		LINK__IO_VAR_DIGITAL_CTRL(xCH_doOPER_MODE, str_name);

		str_name.Format("do.Valve.Opr.Command");
		item_list.Format("UNKNOWN OPEN CLOSE HOLD");
		IO__ADD_DIGITAL_WRITE(str_name, item_list);
		LINK__IO_VAR_DIGITAL_CTRL(xCH__doVALVE_OPR_CMD, str_name);
	
		str_name.Format("do.Reset.Command");
		item_list.Format("UNKNOWN ERRFLAG_RESET FATAL_ERR_RESET");
		IO__ADD_DIGITAL_WRITE(str_name, item_list);
		LINK__IO_VAR_DIGITAL_CTRL(xCH_doRESET_CMD, str_name);

		str_name.Format("do.Zero.Command");
		item_list.Format("UNKNOWN ZERO");
		IO__ADD_DIGITAL_WRITE(str_name, item_list);
		LINK__IO_VAR_DIGITAL_CTRL(xCH_doZERO_CMD, str_name);

		str_name.Format("do.AutoLearn.Command");
		item_list.Format("UNKNOWN AUTO_LEARN");
		IO__ADD_DIGITAL_WRITE(str_name, item_list);
		LINK__IO_VAR_DIGITAL_CTRL(xCH_doAUTO_LEARN_CMD, str_name);

		str_name.Format("do.GET.CONFIG_INFO.1M_TYPE");
		item_list.Format("RANGE_CFG");
		IO__ADD_DIGITAL_WRITE(str_name, item_list);
		LINK__IO_VAR_DIGITAL_CTRL(xCH_doGET_CONFIG_INFO__1M_TYPE, str_name);
	}
	// DI ...
	{
		str_name.Format("di.Comm.Sts");
		item_list.Format("OFFLINE ONLINE");
		IO__ADD_DIGITAL_READ__MANUAL(str_name, item_list);
		LINK__IO_VAR_DIGITAL_CTRL(xCH_diCOMM_STS, str_name);

		str_name.Format("di.Opr.Command");
		item_list.Format("UNKNOWN LOCAL REMOTE LOCKED");
		IO__ADD_DIGITAL_READ__MANUAL(str_name, item_list);
		LINK__IO_VAR_DIGITAL_CTRL(xCH_diOPER_MODE, str_name);

		str_name.Format("di.Ctrl.Mode");
		item_list.Format("UNKNOWN POSITION PRESSURE");
		IO__ADD_DIGITAL_READ__MANUAL(str_name, item_list);
		LINK__IO_VAR_DIGITAL_CTRL(xCH_diCTRL_STS, str_name);

		str_name.Format("di.Position.Error");
		item_list.Format("UNKNOWN OK POS_ERR AIR_ERR POWER_ERR LEARN_DATA_NOT_EXIST");
		IO__ADD_DIGITAL_READ__MANUAL(str_name, item_list);
		LINK__IO_VAR_DIGITAL_CTRL(xCH_diPOSITION_ERROR, str_name);

		//
		str_name.Format("di.Comm.Error.1K_TYPE");
		item_list.Format("UNKNOWN NOERR PARITYERR CRLFERR SYNERR WRONGLETTER VALNOT6DIGIT VALOVER1000 SNSNOCONNECTED LOCALERR INPUTACTIVE ERRLEARN ERRZERO");
		IO__ADD_DIGITAL_READ__MANUAL(str_name, item_list);
		LINK__IO_VAR_DIGITAL_CTRL(xCH_diCOMM_ERROR__1K_TYPE, str_name);

		str_name.Format("di.Comm.Error.1M_TYPE");
		item_list.Format("UNKNOWN NOERR ERROR");
		IO__ADD_DIGITAL_READ__MANUAL(str_name, item_list);
		LINK__IO_VAR_DIGITAL_CTRL(xCH_diCOMM_ERROR__1M_TYPE, str_name);
	}
	
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__VAT650_TYPE
::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	xI_TIMER->REGISTER__ABORT_OBJECT(sObject_Name);	

	// ...
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
		xCH_diCOMM_STS->Link__UPPER_OBJECT_ABORT(sObject_Name);
		xCH_diOPER_MODE->Link__UPPER_OBJECT_ABORT(sObject_Name);
		xCH_diCTRL_STS->Link__UPPER_OBJECT_ABORT(sObject_Name);
		xCH_diPOSITION_ERROR->Link__UPPER_OBJECT_ABORT(sObject_Name);
		xCH__aiVALVE_POS->Link__UPPER_OBJECT_ABORT(sObject_Name);

		xCH_diCOMM_ERROR__1K_TYPE->Link__UPPER_OBJECT_ABORT(sObject_Name);
		xCH_diCOMM_ERROR__1M_TYPE->Link__UPPER_OBJECT_ABORT(sObject_Name);
		
		//
		xCH_diCOMM_STS->Enable__UPPER_OBJECT_ABORT_CHECK();
		xCH_diOPER_MODE->Enable__UPPER_OBJECT_ABORT_CHECK();
		xCH_diCTRL_STS->Enable__UPPER_OBJECT_ABORT_CHECK();
		xCH_diPOSITION_ERROR->Enable__UPPER_OBJECT_ABORT_CHECK();
		xCH__aiVALVE_POS->Enable__UPPER_OBJECT_ABORT_CHECK();
		
		xCH_diCOMM_ERROR__1K_TYPE->Enable__UPPER_OBJECT_ABORT_CHECK();
		xCH_diCOMM_ERROR__1M_TYPE->Enable__UPPER_OBJECT_ABORT_CHECK();
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iACTIVE_SIM = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}

int CObj__VAT650_TYPE
::__INITIALIZE__IO(p_io_para)
{
	//-------------------------------------------------------
	// Set Driver Parameter

	// ...
	int com_port  = -1;

	int nBaudRate = 9600;
	int nDataBit  =    8;
	int nParity   =    0;
	int nStopBit  =    1;

	CString log_msg;
	CString msg;
	CString str_data;

	m_Term_Str[0] = CR;
	m_Term_Str[1] = LF;
	m_Term_Str[2] = '\0';

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
		m_nRetryCount = 3;
		m_nTimeout = 1000;		// msec
	}

	// ...
	{
		log_msg.Format("Connect to Serial ... \n");

		msg.Format("Com_Port : %d \n", com_port);
		log_msg += msg;

		msg.Format("nBaudRate : %1d \n", nBaudRate);
		log_msg += msg;

		msg.Format("nDataBit  : %1d \n", nDataBit);
		log_msg += msg;

		msg.Format("nParity   : %1d \n", nParity);
		log_msg += msg;

		msg.Format("nStopBit  : %1d \n", nStopBit);
		log_msg += msg;

		msg.Format("m_nRetryCount : %1d \n", m_nRetryCount);
		log_msg += msg;

		msg.Format("m_nTimeout : %1d (msec) \n", m_nTimeout);
		log_msg += msg;

		xAPP_LOG_CTRL->WRITE__LOG(log_msg);
		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		CString ch_data;

		ch_data.Format("%1d", com_port);
		sCH__INFO_DRV_COM_PORT->Set__DATA(ch_data);

		ch_data.Format("%1d", nBaudRate);
		sCH__INFO_DRV_BAUD_RATE->Set__DATA(ch_data);
	}

	if(iACTIVE_SIM < 0)
	{
		if(mX_Serial->INIT__COMPORT(com_port, nBaudRate, nDataBit, nStopBit, nParity) < 0)
		{
			msg.Format("Fail to do INIT__COMPORT: %d, ret:-1", com_port);
			Fnc__DRV_LOG(msg);
			return -1;
		}
		else
		{
			msg.Format("Initialize RS-232 Complete");
		}

		Fnc__DRV_LOG(msg);
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__VAT650_TYPE
::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
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
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable, p_alarm, -1);
		ELSE_IF__CTRL_MODE(sMODE__INIT_COMM)			flag = Call__INIT(p_variable, p_alarm,  1);
	
		ELSE_IF__CTRL_MODE(sMODE__OPEN)					flag = Call__OPEN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CLOSE)				flag = Call__CLOSE(p_variable, p_alarm);
		
		ELSE_IF__CTRL_MODE(sMODE__PRESSURE)
		{
			double para_pressure = aCH__PARA_PRESSURE_SET->Get__VALUE();

			flag = Call__PRESSURE(p_variable,p_alarm, para_pressure);
		}

		ELSE_IF__CTRL_MODE(sMODE__POSITION)
		{
			double para_position = aCH__PARA_POSITION_SET->Get__VALUE();
			int para_pos_cnt = (int) (para_position * (MAX_GUI_RANGE_POSITION / 100.0));

			flag = Call__POSITION(p_variable,p_alarm, para_position,para_pos_cnt);
		}
		ELSE_IF__CTRL_MODE(sMODE__POSITION_WAIT)
		{
			double para_position = aCH__PARA_POSITION_SET->Get__VALUE();
			int para_pos_cnt = (int) (para_position * (MAX_GUI_RANGE_POSITION / 100.0));

			flag = Call__POSITION_WAIT(p_variable,p_alarm, para_position,para_pos_cnt);
		}
		ELSE_IF__CTRL_MODE(sMODE__POSITION_NO_WAIT)
		{
			double para_position = aCH__PARA_POSITION_SET->Get__VALUE();
			int para_pos_cnt = (int) (para_position * (MAX_GUI_RANGE_POSITION / 100.0));

			flag = Call__POSITION_NO_WAIT(p_variable,p_alarm, para_position,para_pos_cnt);
		}

		ELSE_IF__CTRL_MODE(sMODE__HOLD)					flag = Call__HOLD(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__AUTO_LEARN)			flag = Call__AUTO_LEARN(p_variable, p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted (%1d)... :  [%s]", flag,mode);
		
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

int CObj__VAT650_TYPE
::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__STATE_CHECK)			Mon__STATE_CHECK(p_variable, p_alarm);

	return 1;
}
