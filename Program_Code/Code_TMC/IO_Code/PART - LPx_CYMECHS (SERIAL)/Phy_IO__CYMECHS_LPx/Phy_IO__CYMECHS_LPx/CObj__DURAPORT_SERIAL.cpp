#include "stdafx.h"
#include "CObj__DURAPORT_SERIAL.h"

#include "CObj__DURAPORT_SERIAL__ALID.h"
#include "CObj__DURAPORT_SERIAL__DEF.h"

#include "Macro_Function.h"


//--------------------------------------------------------------------------------
CObj__DURAPORT_SERIAL::CObj__DURAPORT_SERIAL()
{
	bSts_Running = FALSE;
}
CObj__DURAPORT_SERIAL::~CObj__DURAPORT_SERIAL()
{

}

//--------------------------------------------------------------------------------
int CObj__DURAPORT_SERIAL::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");
		ADD__CTRL_VAR(sMODE__HOME, "HOME");

		ADD__CTRL_VAR(sMODE__DOOR_OPEN,	 "DOOR_OPEN");
		ADD__CTRL_VAR(sMODE__DOOR_CLOSE, "DOOR_CLOSE");

		ADD__CTRL_VAR(sMODE__CLAMP,	  "CLAMP");
		ADD__CTRL_VAR(sMODE__UNCLAMP, "UNCLAMP");

		ADD__CTRL_VAR(sMODE__SHUTTLE_IN,  "SHUTTLE_IN");
		ADD__CTRL_VAR(sMODE__SHUTTLE_OUT, "SHUTTLE_OUT");

		ADD__CTRL_VAR(sMODE__LOAD,	 "LOAD");
		ADD__CTRL_VAR(sMODE__UNLOAD, "UNLOAD");

		ADD__CTRL_VAR(sMODE__MAP, "MAP");

		ADD__CTRL_VAR(sMODE__SIM_FOUP_EXIST, "SIM.FOUP_EXIST");
		ADD__CTRL_VAR(sMODE__SIM_FOUP_NONE,  "SIM.FOUP_NONE");
	}

	return 1;
}
int CObj__DURAPORT_SERIAL::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define  MON_ID__STATE_MONITOR				1
#define  MON_ID__PROC_RSP_MSG				2


#define APP_DSP__LP_OFF_ON					"OFF ON"
#define APP_DSP__LP_UNLOCK_LOCK				"NONE UNLOCK LOCK"
#define APP_DSP__LP_WFR_SLOT_STS			"UNKNOWN ABSENT PRESENT DOUBLE CROSSED INVALID"
#define APP_DSP__RB_TARGET_MOVE				"UNKNOWN HOME READY LP1 LP2 LP3 LP4 LBA LBB VIS1 AL1"


int CObj__DURAPORT_SERIAL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString dsc_item_list;

	// ...
	{
		str_name = "LP.STATE";
		STD__ADD_DIGITAL(str_name, "UNKNOWN INITIALIZED HOMED CLAMPED UNCLAMPED DOCKED UNDOCKED OPENED CLOSED LOADED UNLOADED EXIST");
		LINK__VAR_DIGITAL_CTRL(dCH__LP_STATE, str_name);

		str_name = "CMD.STATE";
		STD__ADD_DIGITAL(str_name, "UNKNOWN INPROGRESS SUCCEEDED FAILED");
		LINK__VAR_DIGITAL_CTRL(dCH__CMD_STATE, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.CTRL.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "AUTO  MAINT", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_CTRL_MODE, str_name);
	}

	// ...
	{
		str_name = "MON.COMMUNICATION.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMMUNICATION_STATE, str_name);

		str_name = "MON.COMMUNICATION.INFO";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMMUNICATION_INFO, str_name);
	}

	// ERROR TEST ...
	{
		str_name = "ERROR_TEST.ACTIVE";
		STD__ADD_DIGITAL(str_name, "NO YES");
		LINK__VAR_DIGITAL_CTRL(dCH__ERROR_TEST__ACTIVE, str_name);

		str_name = "ERROR_TEST.ERROR_CODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ERROR_TEST__ERROR_CODE, str_name);
	}

	// ...
	{
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_STATUS",dsc_item_list);

		str_name = "DRV.LOG.PARAM.LOG.START";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"START STOP","");
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
		str_name = "MON.DOOR.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_DOOR_STATUS, str_name);

		str_name = "MON.FOUP.POS.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_FOUP_POS_STATUS, str_name);

		str_name = "MON.FOUP.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_FOUP_STATUS, str_name);

		str_name = "MON.CLAMP.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_CLAMP_STATUS, str_name);
	}

	// ...
	{
		str_name = "MON.WFR.SLIDE_OUT.SNS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WFR_SLID_OUT_SNS, str_name);

		str_name = "MON.LOAD_BUTTON.SNS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_LOAD_BTN_SNS, str_name);

		str_name = "MON.UNLOAD_BUTTON.SNS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_UNLOAD_BTN_SNS, str_name);

		// ...
		int i;

		for(i=0; i<LAMP_MAX; i++)
		{
			str_name.Format("LINK.LAMP%1d.SET", i+1);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__LINK_LAMP_SET[i], str_name);
		}

		for(i=0; i<LPx_SLOT_MAX; i++)
		{
			int id = i + 1;

			str_name.Format("RES.MAP.SLOT%02d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RES_MAP_SLOT[i], str_name);

			str_name.Format("RES.MAP.CROSS_SLOT.%1d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RES_MAP_CROSS_SLOT[i], str_name);
			
			str_name.Format("RES.MAP.DOUBLE_SLOT.%1d", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__RES_MAP_DOUBLE_SLOT[i], str_name);
		}
	}
	
	// ...
	{
		str_name = "MON.FIRMWARE.VER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_FIRMWARE_VER, str_name);
	}

	// ...
	{
		str_name = "DOUBLE.CHECK.LP.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "Double check loadport status");
		LINK__VAR_DIGITAL_CTRL(dCH__DOUBLE_CHECK, str_name);
	}

	// È£È¯¿ë ...
	{	
		str_name = "RSP.PAGE.CID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RSP_PAGE_CID, str_name);

		str_name = "RSP.PAGE.DATA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RSP_PAGE_DATA, str_name);

		//
		str_name = "PARA.PAGE.CID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_PAGE_CID, str_name);

		str_name = "PARA.PAGE.ID";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "page", 0, 1, 17, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PAGE_ID, str_name);

		str_name = "PARA.PAGE.DATA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_PAGE_DATA, str_name);
	}

	// BIT STS ...
	{
		str_name = "s.BIT_STS.HOMING_COMPLETE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__HOMING_COMPLETE, str_name);

		str_name = "s.BIT_STS.MOTOR_DRIVER_ON";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__MOTOR_DRIVER_ON, str_name);

		str_name = "s.BIT_STS.DOOR_OPENED";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__DOOR_OPENED, str_name);

		str_name = "s.BIT_STS.DOOR_CLOSED";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__DOOR_CLOSED, str_name);

		//
		str_name = "s.BIT_STS.ACTING_CONDITION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__ACTING_CONDITION, str_name);

		str_name = "s.BIT_STS.BACKUP_DATA_CRASH";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__BACKUP_DATA_CRASH, str_name);

		str_name = "s.BIT_STS.MAINT_MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__MAINT_MODE, str_name);

		//
		str_name = "s.BIT_STS.POD_CLAMPED";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__POD_CLAMPED, str_name);

		str_name = "s.BIT_STS.POD_UNCLAMPED";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__POD_UNCLAMPED, str_name);

		str_name = "s.BIT_STS.POD_DOCKED";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__POD_DOCKED, str_name);

		//
		str_name = "s.BIT_STS.POD_UNDOCKED";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__POD_UNDOCKED, str_name);

		str_name = "s.BIT_STS.VACUUM_CONDITION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__VACUUM_CONDITION, str_name);

		str_name = "s.BIT_STS.LATCH_CONDITION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__LATCH_CONDITION, str_name);

		str_name = "s.BIT_STS.UNLATCH_CONDITION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__UNLATCH_CONDITION, str_name);

		//
		str_name = "s.BIT_STS.ERROR_OCCURRENCE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__ERROR_OCCURRENCE, str_name);

		//
		str_name = "s.BIT_STS.AMHS_MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__AMHS_MODE, str_name);

		str_name = "s.BIT_STS.BCR_USAGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__BCR_USAGE, str_name);

		str_name = "s.BIT_STS.MAPPING_USAGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__MAPPING_USAGE, str_name);

		str_name = "s.BIT_STS.AUTO_MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__AUTO_MODE, str_name);

		//
		str_name = "s.BIT_STS.Load_Unload_SW_USAGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__Load_Unload_SW_USAGE, str_name);
		
		str_name = "s.BIT_STS.OPEN_CASSETTE_USAGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__OPEN_CASSETTE_USAGE, str_name);

		str_name = "s.BIT_STS.LOADPORT_RESERVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__LOADPORT_RESERVE, str_name);

		//
		str_name = "s.BIT_STS.PLACEMENT_SENSOR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__PLACEMENT_SENSOR, str_name);

		str_name = "s.BIT_STS.PRESENCE_SENSOR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__PRESENCE_SENSOR, str_name);

		str_name = "s.BIT_STS.WAFER_SLIDE_SENSOR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__WAFER_SLIDE_SENSOR, str_name);

		str_name = "s.BIT_STS.FAN_IO_CONDITION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__BIT_STS__FAN_IO_CONDITION, str_name);
	}

	// BIT INDICATOR ...
	{
		str_name = "s.INDICATOR_STS.LOAD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INDICATOR_STS__LOAD, str_name);

		str_name = "s.INDICATOR_STS.UNLOAD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INDICATOR_STS__UNLOAD, str_name);

		str_name = "s.INDICATOR_STS.AUTO";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INDICATOR_STS__AUTO, str_name);

		str_name = "s.INDICATOR_STS.MANUAL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INDICATOR_STS__MANUAL, str_name);

		str_name = "s.INDICATOR_STS.RESERVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INDICATOR_STS__RESERVE, str_name);

		str_name = "s.INDICATOR_STS.BUTTON";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INDICATOR_STS__BUTTON, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATE_MONITOR);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__PROC_RSP_MSG);
	}
	return 1;
}
int CObj__DURAPORT_SERIAL::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;
	CString item_list;

	// Digital ...
	{
		// DO 
		{
			// INIT 
			str_name = "do.ERROR.RESET";
			item_list = "OFF ON";
			IO__ADD_DIGITAL_WRITE(str_name, item_list);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__ERROR_RESET, str_name);

			str_name = "do.AMP.SET";
			item_list = "OFF ON";
			IO__ADD_DIGITAL_WRITE(str_name, item_list);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__AMP_SET, str_name);

			str_name = "do.LAMP.AUTO_MODE";
			item_list = "OFF ON";
			IO__ADD_DIGITAL_WRITE(str_name, item_list);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__LAMP_AUTO_MODE, str_name);

			//
			str_name = "do.UPDATE.SYSTEM";
			item_list = "ON";
			IO__ADD_DIGITAL_WRITE(str_name, item_list);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__UPDATE_SYSTEM, str_name);

			str_name = "do.UPDATE.INDICATOR";
			item_list = "ON";
			IO__ADD_DIGITAL_WRITE(str_name, item_list);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__UPDATE_INDICATOR, str_name);

			// OPR Command 
			str_name = "do.Opr.Maint_Mode.Set";
			IO__ADD_DIGITAL_WRITE(str_name, "OFF ON");
			LINK__IO_VAR_DIGITAL_CTRL(doCH__OPR_MAINT_MODE_SET, str_name);

			str_name  = "do.Opr.Load.Set";
			item_list = "UNKNOWN UNLOAD LOAD";
			IO__ADD_DIGITAL_WRITE(str_name, item_list);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__OPR_LOAD_SET, str_name);

			//
			str_name  = "do.Opr.Dock.Set";
			item_list = "UNKNOWN UNDOCK DOCK";
			IO__ADD_DIGITAL_WRITE(str_name, item_list);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__OPR_DOCK_SET, str_name);

			str_name = "do.Opr.VAC.Set";
			IO__ADD_DIGITAL_WRITE(str_name, "OFF ON");
			LINK__IO_VAR_DIGITAL_CTRL(doCH__OPR_VAC_SET, str_name);

			str_name = "do.Opr.Latch.Set";
			IO__ADD_DIGITAL_WRITE(str_name, "OFF ON");
			LINK__IO_VAR_DIGITAL_CTRL(doCH__OPR_LATCH_SET, str_name);

			str_name = "do.Opr.Port_Door.Open.Set";
			IO__ADD_DIGITAL_WRITE(str_name, "OFF ON");
			LINK__IO_VAR_DIGITAL_CTRL(doCH__OPR_PORT_DOOR_OPEN_SET, str_name);

			str_name = "do.Opr.Door_Lift.Down.Set";
			IO__ADD_DIGITAL_WRITE(str_name, "OFF ON");
			LINK__IO_VAR_DIGITAL_CTRL(doCH__OPR_DOOR_LIFT_DOWN_SET, str_name);

			//
			str_name  = "do.Opr.Clamp.Set";
			item_list = "UNKNOWN UNCLAMP CLAMP";
			IO__ADD_DIGITAL_WRITE(str_name, item_list);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__OPR_CLAMP_SET, str_name);

			str_name  = "do.Opr.Main.Set";
			item_list = "UNKNOWN CLOSE OPEN HOME SCAN";
			IO__ADD_DIGITAL_WRITE(str_name, item_list);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__OPR_MAIN_SET, str_name);
		}

		// DI
		{
			str_name  = "di.Comm.Sts";
			item_list = "UNKNOWN OFFLINE ONLINE";
			IO__ADD_DIGITAL_READ__MANUAL(str_name, item_list);
			LINK__IO_VAR_DIGITAL_CTRL(diCH__COMM_STS, str_name);
		}
	}

	// String ...
	{
		// SI
		{
			str_name ="si.FIRMWARE_VER";
			IO__ADD_STRING_READ__MANUAL(str_name);
			LINK__IO_VAR_STRING_CTRL(siCH__FIRMWARE_VER, str_name);

			str_name ="si.ERROR_CODE";
			IO__ADD_STRING_READ__MANUAL(str_name);
			LINK__IO_VAR_STRING_CTRL(siCH__ERROR_CODE, str_name);
		}
	}

	return 1;
}

int CObj__DURAPORT_SERIAL::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s : ",sObject_Name);

	int alarm_id;
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// ...
	{
		alarm_id = ALID__OFFLINE;

		alarm_title  = title;
		alarm_title += "Offline !";

		alarm_msg = "Please, check communication line !\n";

		l_act.RemoveAll();
		l_act.Add(ALM_ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);	
	}

	// ...
	{
		alarm_id = ALID__ERROR_CODE;

		alarm_title  = title;
		alarm_title += "Error Code !";

		alarm_msg = "Please, check HW status !\n";

		l_act.RemoveAll();
		l_act.Add(ALM_ACT__ABORT);
		l_act.Add(ALM_ACT__RETRY);
		l_act.Add(ALM_ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);	
	}

	return 1;
}

//--------------------------------------------------------------------------------
int CObj__DURAPORT_SERIAL
::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s-APP.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		// ...
		{
			xAPP__LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xAPP__LOG_CTRL->SET__PROPERTY(file_name,24*5,60);

			xAPP__LOG_CTRL->DISABLE__TIME_LOG();
			xAPP__LOG_CTRL->WRITE__LOG(log_msg);

			xAPP__LOG_CTRL->ENABLE__TIME_LOG();
			xAPP__LOG_CTRL->WRITE__LOG("   START   \n");
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq;

		iActive__SIM_MODE = x_seq->Is__SIMULATION_MODE();
	}

	iFlag__APP_LOG = 1;
	return 1;
}
int CObj__DURAPORT_SERIAL
::__INITIALIZE__IO(p_io_para)
{
	//-------------------------------------------------------
	// Set Driver Parameter
	//------------------------------------------------------
	// ...
	int com_port  = -1;

	int nBaudRate = 9600;
	int nDataBit  =    8;
	int nParity   =    0;
	int nStopBit  =    2;

	sStr_End = (char) LF;

	m_nRetryCount = 1;
	m_nTimeout  = 3000;

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
		CString str_info;

		str_info.Format("Com_Port(%1d) Buad_Rate(%1d) Data_Bit(%1d) Stop_Bit(%1d) Parity(%s)",
						com_port,
						nBaudRate,
						nDataBit,
						nStopBit,
						Macro__Get_Parity(nParity));

		sCH__MON_COMMUNICATION_INFO->Set__DATA(str_info);
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		// ...
		{
			file_name.Format("%s-DRV.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			// ...
			{
				xDRV__LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
				xDRV__LOG_CTRL->SET__PROPERTY(file_name, 2*3, 30);

				xDRV__LOG_CTRL->DISABLE__TIME_LOG();
				xDRV__LOG_CTRL->WRITE__LOG(log_msg);

				xDRV__LOG_CTRL->ENABLE__TIME_LOG();
				xDRV__LOG_CTRL->WRITE__LOG("   START   \n");
			}
		}
	}

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "Connect to Serial \n";

		log_bff.Format("Com Port: %1d \n", com_port);
		log_msg += log_bff;

		log_bff.Format("Baud Rate: %1d \n", nBaudRate);
		log_msg += log_bff;

		log_bff.Format("Data Bit: %1d \n", nDataBit);
		log_msg += log_bff;

		log_bff.Format("Parity Bit: %1d \n", nParity);
		log_msg += log_bff;

		log_bff.Format("Stop Bit: %1d \n", nStopBit);
		log_msg += log_bff;

		log_bff.Format("Retry Count: %1d \n", m_nRetryCount);
		log_msg += log_bff;

		log_bff.Format("Timeout: %1d msec \n", m_nTimeout);
		log_msg += log_bff;

		if(iActive__SIM_MODE > 0)
		{
			log_bff.Format("Simulation Mode !!! \n");
			log_msg += log_bff;

			Fnc__DRV_LOG(log_msg);
			return -1;
		}

		if(mX_Serial->INIT__COMPORT(com_port, nBaudRate, nDataBit, nStopBit, nParity) < 0)
		{
			log_bff.Format("Fail to do INIT__COMPORT: %d, ret:-1\n", com_port);
			log_msg += log_bff;
			
			Fnc__DRV_LOG(log_msg);
			return -1;
		}

		log_msg += "Initialize RS-232 Complete \n";
		Fnc__DRV_LOG(log_msg);
	}

	m_nCommSts = ONLINE;
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__DURAPORT_SERIAL
::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
LOOP_RETRY:

	// ...
	bSts_Running = TRUE;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		sCH__SEQUENCE_MSG->Set__DATA(log_msg);
		Fnc__APP_LOG(log_msg);
	}

	mMNG__ERR_CODE.Clear__Error_Code();

	// ...
	int flag = -1;

	// ...
	{
		     IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__HOME)				flag = Call__HOME(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__DOOR_OPEN)		flag = Call__DOOR_OPEN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__DOOR_CLOSE)		flag = Call__DOOR_CLOSE(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__CLAMP)			flag = Call__CLAMP(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__UNCLAMP)			flag = Call__UNCLAMP(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__SHUTTLE_IN)		flag = Call__SHUTTLE_IN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SHUTTLE_OUT)		flag = Call__SHUTTLE_OUT(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__LOAD)				flag = Call__LOAD(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__UNLOAD)			flag = Call__UNLOAD(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__MAP)				flag = Call__MAP(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__SIM_FOUP_EXIST)
		{
			flag = 1;

			sCH__BIT_STS__PLACEMENT_SENSOR->Set__DATA(STR__ON);
			sCH__BIT_STS__PRESENCE_SENSOR->Set__DATA(STR__ON);

			sCH__MON_FOUP_STATUS->Set__DATA(STR__EXIST);
		}
		ELSE_IF__CTRL_MODE(sMODE__SIM_FOUP_NONE)
		{
			flag = 1;

			sCH__BIT_STS__PLACEMENT_SENSOR->Set__DATA(STR__OFF);
			sCH__BIT_STS__PRESENCE_SENSOR->Set__DATA(STR__OFF);

			sCH__MON_FOUP_STATUS->Set__DATA(STR__NONE);
		}
	}

	// ...
	{
		CString err_code;
		CString err_title;
		CString err_msg;

		if(dCH__ERROR_TEST__ACTIVE->Check__DATA(STR__YES) > 0)
		{
			CString err_code = sCH__ERROR_TEST__ERROR_CODE->Get__STRING();
			_Check__ERROR_CODE(err_code);
		}

		while(mMNG__ERR_CODE.Get__Error_Code(err_code,err_title,err_msg) > 0)
		{
			// ...
			{
				CString log_msg;
				CString log_bff;

				log_msg = "Error_Code Occurred !!!";

				log_bff.Format("Error_Code  : [%s] \n", err_code);
				log_msg += log_bff;
				log_bff.Format("Error_Title : [%s] \n", err_title);
				log_msg += log_bff;
				log_bff.Format("Error_Msg   : [%s] \n", err_msg);
				log_msg += log_bff;

				Fnc__APP_LOG(log_msg);
			}

			// ...
			int alm_id = ALID__ERROR_CODE;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			alm_msg.Format("Control_Mode : %s \n", mode);

			alm_bff.Format("Error_Code  : %s \n", err_code);
			alm_msg += alm_bff;
			alm_bff.Format("Error_Title : %s \n", err_title);
			alm_msg += alm_bff;
			alm_bff.Format("Error_Message \n");
			alm_msg += alm_bff;
			alm_msg += "  * ";
			alm_msg += err_msg;

			// ...
			{
				CString log_msg;

				log_msg.Format("Alarm Post : %1d \n", alm_id);
				log_msg += alm_msg;

				Fnc__APP_LOG(log_msg);
			}

			p_alarm->Popup__ALARM_With_MESSAGE(alm_id,alm_msg,r_act);			

			if(r_act.CompareNoCase(ALM_ACT__RETRY) == 0)
			{
				// ...
				{
					CString log_msg = "Alarm Selection <- Retry";
					Fnc__APP_LOG(log_msg);
				}

				goto LOOP_RETRY;
			}
			if(r_act.CompareNoCase(ALM_ACT__ABORT) == 0)
			{
				// ...
				{
					CString log_msg = "Alarm Selection <- Abort";
					Fnc__APP_LOG(log_msg);
				}

				flag = -1;
			}
			if(r_act.CompareNoCase(ALM_ACT__IGNORE) == 0)
			{
				// ...
			}

			break;
		}
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

	bSts_Running = FALSE;
	return flag;
}

int CObj__DURAPORT_SERIAL
::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__STATE_MONITOR:
 			Mon__STATE_MONITOR(p_variable, p_alarm);
 			break;

		case MON_ID__PROC_RSP_MSG:
			Mon__PROC_RSP_MSG(p_variable, p_alarm);
			break;
	}

	return 1;
}
