#include "StdAfx.h"
#include "CObj__NXA_PULSE.h"



//--------------------------------------------------------------------------------
CObj__NXA_PULSE::CObj__NXA_PULSE()
{
	m_Rcv_Time	 = 250;
	m_RetryCnt	 = 3;

	//
	dUNIT__FREQ = 0.01;		// Hz
	dUNIT__DUTY = 0.01;		// %
	dUNIT__uSEQ = 0.01;		// usec
}
CObj__NXA_PULSE::~CObj__NXA_PULSE()
{

}

//--------------------------------------------------------------------------------
int CObj__NXA_PULSE::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__CLK_A_SET, "CLK_A.SET");
		ADD__CTRL_VAR(sMODE__CLK_B_SET, "CLK_B.SET");
		ADD__CTRL_VAR(sMODE__CLK_C_SET, "CLK_C.SET");

		ADD__CTRL_VAR(sMODE__CLK_EXEC_ON,  "CLK_EXEC.ON");
		ADD__CTRL_VAR(sMODE__CLK_EXEC_OFF, "CLK_EXEC.OFF");

		ADD__CTRL_VAR(sMODE__TEST_DRV, "TEST.DRV");
	}
	return 1;
}
int CObj__NXA_PULSE::__DEFINE__VERSION_HISTORY(version)
{
	version = "2022.01.21 \n";

	return 1;
}


// ...
#define  MON_ID__MONITOR				1

#define  APP_DSP__COMM_STATUS           "OFFLINE  ONLINE"
#define  APP_DSP__OFF_ON				"OFF	  ON"


int CObj__NXA_PULSE::__DEFINE__VARIABLE_STD(p_variable)
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
		str_name = "PARA.PARAM_A.FREQ";
		STD__ADD_ANALOG(str_name, "Hz", 2, 0, 10000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PARAM_A_FREQ, str_name);

		str_name = "PARA.PARAM_A.DUTY";
		STD__ADD_ANALOG(str_name, "%", 2, 0, 100);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PARAM_A_DUTY, str_name);

		str_name = "PARA.PARAM_A.ON_TIME";
		STD__ADD_ANALOG(str_name, "usec", 2, 0, 1000000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PARAM_A_ON_TIME, str_name);

		str_name = "PARA.PARAM_A.OFF_TIME";
		STD__ADD_ANALOG(str_name, "usec", 2, 0, 1000000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PARAM_A_OFF_TIME, str_name);

		//
		str_name = "PARA.PARAM_B.ON_SHIFT_TIME";
		STD__ADD_ANALOG(str_name, "usec", 2, 0, 1000000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PARAM_B_ON_SHIFT_TIME, str_name);

		str_name = "PARA.PARAM_B.OFF_SHIFT_TIME";
		STD__ADD_ANALOG(str_name, "usec", 2, 0, 1000000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PARAM_B_OFF_SHIFT_TIME, str_name);

		//
		str_name = "PARA.PARAM_C.ON_SHIFT_TIME";
		STD__ADD_ANALOG(str_name, "usec", 2, 0, 1000000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PARAM_C_ON_SHIFT_TIME, str_name);
		
		str_name = "PARA.PARAM_C.OFF_SHIFT_TIME";
		STD__ADD_ANALOG(str_name, "usec", 2, 0, 1000000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PARAM_C_OFF_SHIFT_TIME, str_name);

		//
		str_name = "PARA.CLK_A.CTRL";
		STD__ADD_DIGITAL(str_name, "OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_CLK_A_CTRL, str_name);
		
		str_name = "PARA.CLK_B.CTRL";
		STD__ADD_DIGITAL(str_name, "OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_CLK_B_CTRL, str_name);
		
		str_name = "PARA.CLK_C.CTRL";
		STD__ADD_DIGITAL(str_name, "OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_CLK_C_CTRL, str_name);
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
	}

	// INFO ...
	{
		str_name = "INFO.LAST.ERROR.CODE";	  
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__INFO_LAST_ERROR_CODE, str_name);

		//
		str_name = "INFO.PARAM_A.FREQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PARAM_A_FREQ, str_name);

		str_name = "INFO.PARAM_A.DUTY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PARAM_A_DUTY, str_name);

		str_name = "INFO.PARAM_A.ON_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PARAM_A_ON_TIME, str_name);

		str_name = "INFO.PARAM_A.OFF_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PARAM_A_OFF_TIME, str_name);

		//
		str_name = "INFO.PARAM_B.ON_SHIFT_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PARAM_B_ON_SHIFT_TIME, str_name);

		str_name = "INFO.PARAM_B.OFF_SHIFT_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PARAM_B_OFF_SHIFT_TIME, str_name);

		//
		str_name = "INFO.PARAM_C.ON_SHIFT_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PARAM_C_ON_SHIFT_TIME, str_name);

		str_name = "INFO.PARAM_C.OFF_SHIFT_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PARAM_C_OFF_SHIFT_TIME, str_name);

		//
		str_name = "INFO.CLK_A.CTRL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CLK_A_CTRL, str_name);

		str_name = "INFO.CLK_B.CTRL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CLK_B_CTRL, str_name);

		str_name = "INFO.CLK_C.CTRL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CLK_C_CTRL, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0,MON_ID__MONITOR);
	}
	return 1;
}
int CObj__NXA_PULSE::__DEFINE__ALARM(p_alarm)
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

int CObj__NXA_PULSE::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;

	// DO ...
	{
		str_name = "do.PARAM.A1";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);	
		LINK__IO_VAR_DIGITAL_CTRL(doCH__PARAM_A1, str_name);

		str_name = "do.PARAM.A2";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);	
		LINK__IO_VAR_DIGITAL_CTRL(doCH__PARAM_A2, str_name);

		str_name = "do.PARAM.B";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);	
		LINK__IO_VAR_DIGITAL_CTRL(doCH__PARAM_B, str_name);

		str_name = "do.PARAM.C";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);	
		LINK__IO_VAR_DIGITAL_CTRL(doCH__PARAM_C, str_name);

		//
		str_name = "do.SET.EXEC";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);	
		LINK__IO_VAR_DIGITAL_CTRL(doCH__SET_EXEC, str_name);

		//
		str_name = "do.FLASH.CTRL";
		IO__ADD_DIGITAL_WRITE(str_name, "WRITE  ERASE");	
		LINK__IO_VAR_DIGITAL_CTRL(doCH__FLASH_CTRL, str_name);
	}

	// SI ...
	{
		str_name = "si.PARAM.A1";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__PARAM_A1, str_name);

		str_name = "si.PARAM.A2";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__PARAM_A2, str_name);

		str_name = "si.PARAM.B";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__PARAM_B, str_name);

		str_name = "si.PARAM.C";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__PARAM_C, str_name);

		//
		str_name = "si.GET.EXEC";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__GET_EXEC, str_name);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__NXA_PULSE::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

int CObj__NXA_PULSE::__INITIALIZE__IO(p_io_para)
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
int CObj__NXA_PULSE::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
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

		ELSE_IF__CTRL_MODE(sMODE__CLK_A_SET)		flag = Call__CLK_A_SET(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CLK_B_SET)		flag = Call__CLK_B_SET(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CLK_C_SET)		flag = Call__CLK_C_SET(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__CLK_EXEC_ON)		flag = Call__CLK_EXEC_SET(p_variable, p_alarm, true);
		ELSE_IF__CTRL_MODE(sMODE__CLK_EXEC_OFF)		flag = Call__CLK_EXEC_SET(p_variable, p_alarm, false);

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

int CObj__NXA_PULSE::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__MONITOR)
	{
		return Mon__MONITOR(p_variable,p_alarm);
	}
	return 1;
}

