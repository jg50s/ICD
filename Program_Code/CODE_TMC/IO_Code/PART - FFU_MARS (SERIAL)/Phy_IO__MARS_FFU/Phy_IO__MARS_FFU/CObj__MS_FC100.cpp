#include "StdAfx.h"
#include "CObj__MS_FC100.h"

#include "Macro_Function.h"


//--------------------------------------------------------------------------------
CObj__MS_FC100::CObj__MS_FC100()
{

}
CObj__MS_FC100::~CObj__MS_FC100()
{

}

//--------------------------------------------------------------------------------
int CObj__MS_FC100::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	return 1;
}
int CObj__MS_FC100::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee";

	return 1;
}


// ...
#define  MON_ID__ALM_REPORT					1

int CObj__MS_FC100::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);
	
	CString var_name;
	int i;

	// ...
	{
		var_name = "MON.COMMUNICATION.STATE";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMMUNICATION_STATE, var_name);

		var_name = "MON.COMMUNICATION.INFO";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMMUNICATION_INFO, var_name);
	}

	// State ...
	{
		var_name = "s.FFU.Status.HEXA";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__FFU_Status__HEXA, var_name);

		var_name = "s.FFU.Status.NO_CONNECTION";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__FFU_Status__NO_CONNECTION, var_name);

		var_name = "s.FFU.Status.FAN_ERROR";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__FFU_Status__FAN_ERROR, var_name);

		var_name = "s.FFU.Status.DIF_PRESS_ERROR";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__FFU_Status__DIF_PRESS_ERROR, var_name);

		var_name = "s.FFU.Status.RPM_HIGH_ERROR";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__FFU_Status__RPM_HIGH_ERROR, var_name);

		var_name = "s.FFU.Status_RPM_LOW_ERROR";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__FFU_Status__RPM_LOW_ERROR, var_name);

		var_name = "s.FFU.Status.DIF_PRESS_HIGH_ERROR";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__FFU_Status__DIF_PRESS_HIGH_ERROR, var_name);

		var_name = "s.FFU.Status.DIF_PRESS_LOW_ERROR";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__FFU_Status__DIF_PRESS_LOW_ERROR, var_name);

		var_name = "s.FFU.Status.STABLE_TIME_ERROR";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__FFU_Status__STABLE_TIME_ERROR, var_name);
	}
	// Group ...
	{
		var_name = "a.FFU.Group_Para.Set_RPM";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "rpm", 0, 0, 600, "");
		LINK__VAR_ANALOG_CTRL(aCH__FFU_Group_Para_Set_RPM, var_name);
		
		var_name = "a.FFU.Group_Para.Set_PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "pa", 0, 0, 2000, "");
		LINK__VAR_ANALOG_CTRL(aCH__FFU_Group_Para_Set_PRESSURE, var_name);
	}
	// Block ...
	{
		var_name = "a.FFU.Block_Para.Set_StartID";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "id", 0, 1, 4, "");
		LINK__VAR_ANALOG_CTRL(aCH__FFU_Block_Para_Set_StartID, var_name);

		var_name = "a.FFU.Block_Para.Set_Size";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "size", 0, 1, 4, "");
		LINK__VAR_ANALOG_CTRL(aCH__FFU_Block_Para_Set_Size, var_name);

		var_name = "a.FFU.Block_Para.Set_RPM";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "rpm", 0, 0, 600, "");
		LINK__VAR_ANALOG_CTRL(aCH__FFU_Block_Para_Set_RPM, var_name);

		var_name = "a.FFU.Block_Para.Set_PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "pa", 0, 0, 2000, "");
		LINK__VAR_ANALOG_CTRL(aCH__FFU_Block_Para_Set_PRESSURE, var_name);
	}
	
	// FAN ...
	{
		for(i=0; i<CFG__FAN_SIZE; i++)
		{
			int id = i + 1;

			var_name.Format("s.FFU.FAN.STATE_HEXA.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__FFU_FAN_X__STATE_HEXA[i], var_name);
	
			var_name.Format("s.FFU.FAN.RPM_PV.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__FFU_FAN_X__RPM_PV[i], var_name);
	
			var_name.Format("s.FFU.FAN.RPM_SV.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__FFU_FAN_X__RPM_SV[i], var_name);
			
			var_name.Format("s.FFU.FAN.DIFF_PRESS.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__FFU_FAN_X__DIFF_PRESS[i], var_name);
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__ALM_REPORT);
	}
	return 1;
}
int CObj__MS_FC100::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__FFU_OFFLINE;

		alarm_title  = title;
		alarm_title += "Offline !";

		alarm_msg  = "FFU Controller is Offline.\n";
		alarm_msg += "Please, Check Communication Status !\n";
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__FFU_CONTROL_TIMEOUT;

		alarm_title  = title;
		alarm_title += "Control Timeout !";

		alarm_msg  = "FFU Controller is Timeout.\n";
		alarm_msg += "Please, Check FFU Control Status !";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
#define APP_DSP__COMM_STS				"OFFLINE  ONLINE"
#define APP_DSP__CTRL_MODE				"LOCAL  REMOTE"
#define APP_DSP__CTRL_STS				"LOCAL  REMOTE"
#define APP_DSP__OFF_ON					"NONE OFF ON"

#define APP_DSP__UNIT_CTRL				"ANALOG DIGITAL"
#define APP_DSP__FREEZE_FOLLOW			"FREEZE FOLLOW"
#define APP_DSP__OVERMODE				"SEMI UNIT"
#define APP_DSP__VALVE_CTRL				"NONE CONTROL CLOSE OPEN OFF"
#define APP_DSP__UNIT_INIT				"AUTOZERO INIT RESET CALIBRATION"


int CObj__MS_FC100::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString var_name;

	// ...
	{
		var_name = "di.FFU.Status_Get";
		IO__ADD_DIGITAL_READ(var_name, "GET");
		LINK__IO_VAR_DIGITAL_CTRL(diCH__FFU_Status_Get, var_name);

		//
		var_name = "do.FFU.Group_Set";
		IO__ADD_DIGITAL_WRITE(var_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__FFU_Group_Set, var_name);

		var_name = "di.FFU.Group_Get";
		IO__ADD_DIGITAL_READ(var_name, "GET");
		LINK__IO_VAR_DIGITAL_CTRL(diCH__FFU_Group_Get, var_name);

		//
		var_name = "do.FFU.Block_Set";
		IO__ADD_DIGITAL_WRITE(var_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__FFU_Block_Set, var_name);

		var_name = "di.FFU.Block_Get";
		IO__ADD_DIGITAL_READ__MANUAL(var_name, "GET");
		LINK__IO_VAR_DIGITAL_CTRL(diCH__FFU_Block_Get, var_name);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__MS_FC100::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	SCX__SEQ_INFO x_seq_info;
	iSim_Mode = x_seq_info->Is__SIMULATION_MODE();

	return 1;
}
int CObj__MS_FC100::__INITIALIZE__IO(p_io_para)
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

			xLog_Ctrl__Drive->CREATE__SUB_DIRECTORY(dir_name);
			xLog_Ctrl__Drive->SET__PROPERTY(file_name,nfile_size,nfile_time);

			xLog_Ctrl__Drive->DISABLE__TIME_LOG();
			xLog_Ctrl__Drive->WRITE__LOG(log_msg);

			xLog_Ctrl__Drive->ENABLE__TIME_LOG();
			xLog_Ctrl__Drive->WRITE__LOG("   START   \n");
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

		xLog_Ctrl__Drive->WRITE__LOG(log_msg);
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

	m_nCommState = OFFLINE;

	if(iSim_Mode > 0)
	{
		CString msg;

		msg.Format("Simulation Mode !!!");
		
		xLog_Ctrl__Drive->WRITE__LOG(msg);
		return -1;
	}

	// ...
	{
		CString msg;

		mX_Serial->RTS__CHECK_SKIP();
		
		if(mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity) < 0)
		{
			msg.Format("Fail to do INIT__COMPORT: %d, ret:-1", com_port);
			xLog_Ctrl__Drive->WRITE__LOG(msg);
			return -1;
		}
		else
		{
			msg.Format("Initialize RS-232 Complete");
		}

		xLog_Ctrl__Drive->WRITE__LOG(msg);
	}
	
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__MS_FC100::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	
	return 1;
}

int CObj__MS_FC100::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__ALM_REPORT)		Mon__ALM_REPORT(p_alarm);

	return 1;
}

int CObj__MS_FC100::__CLOSE__OBJECT()
{

	return 1;
}
