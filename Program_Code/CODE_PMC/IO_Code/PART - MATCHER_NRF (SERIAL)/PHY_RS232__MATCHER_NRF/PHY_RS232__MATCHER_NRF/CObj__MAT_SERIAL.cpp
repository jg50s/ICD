#include "StdAfx.h"
#include "CObj__MAT_SERIAL.h"



//--------------------------------------------------------------------------------
CObj__MAT_SERIAL::CObj__MAT_SERIAL()
{
	m_Rcv_Time	 = 250;
	m_RetryCnt	 = 3;

	//
	iUNIT__ADDR_ID = 0x40;

	dVALUE__PWR_MAX_10		= 10;
	iHEXA__PWR_MAX_10		= 0x000A;

	dVALUE__PWR_MAX_100		= 100;
	iHEXA__PWR_MAX_100		= 0x0064;

	dVALUE__PWR_MAX_200		= 200;
	iHEXA__PWR_MAX_200		= 0x00C8;

	dVALUE__PWR_MAX_1000	= 1000;
	iHEXA__PWR_MAX_1000		= 0x03E8;

	dVALUE__PWR_MAX_10000	= 10000;
	iHEXA__PWR_MAX_10000	= 0x2710;
}
CObj__MAT_SERIAL::~CObj__MAT_SERIAL()
{

}

//--------------------------------------------------------------------------------
int CObj__MAT_SERIAL::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__AUTO,	 "AUTO");
		ADD__CTRL_VAR(sMODE__MANUAL, "MANUAL");
		ADD__CTRL_VAR(sMODE__PROC_CTRL, "PROC.CTRL");

		ADD__CTRL_VAR(sMODE__TEST_DRV, "TEST.DRV");
	}
	return 1;
}
int CObj__MAT_SERIAL::__DEFINE__VERSION_HISTORY(version)
{
	version = "2022.01.21 \n";

	return 1;
}


// ...
#define  MON_ID__MONITOR				1

#define  APP_DSP__COMM_STATUS           "OFFLINE  ONLINE"
#define  APP_DSP__OFF_ON				"OFF	  ON"
#define  APP_DSP__MODE_SET				"MANUAL	  AUTO"


int CObj__MAT_SERIAL::__DEFINE__VARIABLE_STD(p_variable)
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

	// CFG : SYSTEM ...
	{
		str_name = "CFG.PART.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PART_USE, str_name);
	}

	// PARA ...
	{
 		str_name = "PARA.LOAD_POS";
 		STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 0, 0, dVALUE__PWR_MAX_1000, -1, "L", "");
 		LINK__VAR_ANALOG_CTRL(aCH__PARA_LOAD_POS, str_name);
 
 		str_name = "PARA.TUNE_POS";
 		STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 0, 0, dVALUE__PWR_MAX_1000, -1, "L", "");
 		LINK__VAR_ANALOG_CTRL(aCH__PARA_TUNE_POS, str_name);
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

		str_name = "CFG.MODE.SET";
		STD__ADD_DIGITAL(str_name,  APP_DSP__MODE_SET);
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_MODE_SET, str_name);
	}

	// MON ...
	{
		str_name = "MON.CONTROL.SET";	 
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__MON_CONTROL_SET, str_name);

		str_name = "MON.LOAD_POS.SET";	 
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__MON_LOAD_POS_SET, str_name);

		str_name = "MON.TUNE_POS.SET";	 
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__MON_TUNE_POS_SET, str_name);
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
		str_name = "INFO.LAST.ERROR.CODE";	  
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__INFO_LAST_ERROR_CODE, str_name);

		//
		str_name = "INFO.LOAD_PRESET";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_LOAD_PRESET, str_name);

		str_name = "INFO.TUNE_PRESET";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_TUNE_PRESET, str_name);

		str_name = "INFO.CUR_LOAD_POSITION";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_CUR_LOAD_POSITION, str_name);

		str_name = "INFO.CUR_TUNE_POSITION";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_CUR_TUNE_POSITION, str_name);

		str_name = "INFO.VPP_VALUE";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_VPP_VALUE, str_name);

		str_name = "INFO.VRMS";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_VRMS, str_name);

		str_name = "INFO.IRMS";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_IRMS, str_name);

		str_name = "INFO.REAL_IMPEDANCE";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_REAL_IMPEDANCE, str_name);

		str_name = "INFO.IMAGE_IMPEDANCE";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_IMAGE_IMPEDANCE, str_name);

		str_name = "INFO.FORWARD_PWR";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_FORWARD_PWR, str_name);

		str_name = "INFO.REF_PWR";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_REF_PWR, str_name);

		str_name = "INFO.START_SWR";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_START_SWR, str_name);

		str_name = "INFO.STOP_SWR";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_STOP_SWR, str_name);

		str_name = "INFO.CUR_SWR";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_CUR_SWR, str_name);

		str_name = "INFO.PHASE_SHIFT";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__INFO_PHASE_SHIFT, str_name);
	}

	// INFO,STS ...
	{
		// BYTE : 0
		str_name = "INFO.STS.HEXA_0";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_HEXA_0, str_name);

		str_name = "INFO.STS.MAT_AUTO_MATCHING_STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_MAT_AUTO_MATCHING_STATE, str_name);

		str_name = "INFO.STS.MAT_PANEL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_MAT_PANEL, str_name);

		str_name = "INFO.STS.MAT_RF";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_MAT_RF, str_name);

		// BYTE : 1
		str_name = "INFO.STS.HEXA_1";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_HEXA_1, str_name);

		str_name = "INFO.STS.MAT_MOTOR_ERROR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_MAT_MOTOR_ERROR, str_name);

		str_name = "INFO.STS.MAT_TEMP";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_MAT_TEMP, str_name);

		str_name = "INFO.STS.MAT_MATCHING";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_MAT_MATCHING, str_name);
	}
	
	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0,MON_ID__MONITOR);
	}
	return 1;
}
int CObj__MAT_SERIAL::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__MAT_OFFLINE_ALARM;

		alarm_title  = title;
		alarm_title += "Matcher Offline";

		alarm_msg = "Matcher Offline.";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__MAT_RETRY_OVER_ALARM;

		alarm_title  = title;
		alarm_title += "Matcher Communication Retry Over";

		alarm_msg = "Matcher Communication Retry Over";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__MAT_SERIAL::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;

	// SI ...
	{
		str_name = "si.MAT.STATE";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__MAT_STATE, str_name);

		str_name = "si.LOAD.PRESET";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__LOAD_PRESET, str_name);

		str_name = "si.TUNE.PRESET";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__TUNE_PRESET, str_name);

		str_name = "si.CURLOAD.POSITION";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__CUR_LOAD_POSITION, str_name);

		str_name = "si.CURTUNE.POSITION";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__CUR_TUNE_POSITION, str_name);

		str_name = "si.VPP.VALUE";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__VPP_VALUE, str_name);

		str_name = "si.VRMS.LRMS";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__VRMS_AND_LRMS, str_name);

		str_name = "si.IMPEDANCE";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__IMPEDANCE, str_name);

		str_name = "si.FWD_PWR";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__FWD_PWR, str_name);

		str_name = "si.REF_PWR";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__REF_PWR, str_name);

		str_name = "si.START_STOP_SWR";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__START_STOP_SWR, str_name);

		str_name = "si.SWR";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__SWR, str_name);

		str_name = "si.PHASE_SHIFT";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__PHASE_SHIFT, str_name);
	}

	// AO ...
	{
		str_name = "ao.LOAD.PRESET";
		IO__ADD_ANALOG_WRITE(str_name, "%", 0, 0.0, 1000.0);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__LOAD_PRESET, str_name);

		str_name = "ao.TUNE.PRESET";
		IO__ADD_ANALOG_WRITE(str_name, "%", 0, 0.0, 1000.0);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__TUNE_PRESET, str_name);

		str_name = "ao.LOAD.MANUAL";
		IO__ADD_ANALOG_WRITE(str_name, "%", 0, 0.0, 1000.0);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__LOAD_MANUAL, str_name);

		str_name = "ao.TUNE.MANUAL";
		IO__ADD_ANALOG_WRITE(str_name, "%", 0, 0.0, 1000.0);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__TUNE_MANUAL, str_name);
	}

	// DO ...
	{
		str_name = "do.STAUTS.SET";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__STATUS_SET, str_name);

		str_name = "do.MOTOR.RESET";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__MOTOR_RESET, str_name);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__MAT_SERIAL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

int CObj__MAT_SERIAL::__INITIALIZE__IO(p_io_para)
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
int CObj__MAT_SERIAL::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
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

		ELSE_IF__CTRL_MODE(sMODE__MANUAL)			flag = Call__MODE_SET(p_variable, p_alarm, false);
		ELSE_IF__CTRL_MODE(sMODE__AUTO)				flag = Call__MODE_SET(p_variable, p_alarm, true);
		ELSE_IF__CTRL_MODE(sMODE__PROC_CTRL)		flag = Call__MODE_SET(p_variable, p_alarm, true);

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

int CObj__MAT_SERIAL::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__MONITOR)
	{
		return Mon__MONITOR(p_variable,p_alarm);
	}
	return 1;
}

