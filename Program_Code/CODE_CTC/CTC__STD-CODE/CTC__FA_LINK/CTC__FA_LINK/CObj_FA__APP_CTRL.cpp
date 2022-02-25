#include "StdAfx.h"
#include "CObj_FA__APP_CTRL.h"


//-------------------------------------------------------------------------
CObj_FA__APP_CTRL::CObj_FA__APP_CTRL()
{

}
CObj_FA__APP_CTRL::~CObj_FA__APP_CTRL()
{

}

//-------------------------------------------------------------------------
int CObj_FA__APP_CTRL::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	return 1;
}

int CObj_FA__APP_CTRL::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__E30_CTRL					1
#define  MON_ID__CONTROL_STATE_CTRL			2
#define  MON_ID__USER_JOB					3
#define  MON_ID__PMx_CEID					4

// ...
#define  DSP__COMM_MODE			"DISABLE  ENABLE  NOT_USE"
#define  DSP__DISABLE_ENABLE	"DISABLE  ENABLE"
#define  DSP__RCMD_PMC			"DISABLE  1  2  3  4  5  6"

#define  DEF__ENABLE_DISABLE	"ENABLE  DISABLE"
#define  DEF__FALSE_TRUE		"FALSE   TRUE"

#define  DEF__DEFAULT_INITIAL_STATE				\
"EQUIPMENT_OFFLINE								\
ATTEMPT_ONLINE									\
HOST_OFFLINE									\
ONLINE_LOCAL									\
ONLINE_REMOTE"

#define  DEF__DEFAULT_CONTROL_OFFLINE_STATE		\
"EQUIPMENT_OFFLINE								\
HOST_OFFLINE"

#define  DEF__INITIAL_CONTROL_STATE				\
"LOCAL  REMOTE"


int CObj_FA__APP_CTRL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	// ...
	CString str_name;
	int i;

	// ...
	{
		str_name = "CFG.AUTO.REMOTE.CONNECTION";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_AUTO_REMOTE_CONNECTION, str_name);
	}

	// ...
	{
		str_name = "FA.USER.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_USER_REQ,str_name);

		str_name = "FA.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_REQ,str_name);

		//
		str_name = "FA.CONNECTION.STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_CONNECTION_STATUS,str_name);

		str_name = "FA.STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_STATUS,str_name);

		str_name = "FA.PRE.STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_PRE_STATUS,str_name);

		//
		str_name = "FA.STATUS.ID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_STATUS_ID,str_name);

		str_name = "FA.PRE.STATUS.ID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_PRE_STATUS_ID,str_name);

		//
		str_name = "FA.COMM.STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_COMM_STATUS,str_name);

		str_name = "FA.CONTROL.STATE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_CONTROL_STATE,str_name);

		//
		str_name = "TIME_FROM_HOST.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__TIME_FROM_HOST_REQ,str_name);

		//
		str_name = "FA.COMMUNICATION.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__COMM_MODE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__FA_COMMUNICATION_FLAG,str_name);

		str_name = "FA.COMMUNICATION.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,10.0,100.0,"");
		LINK__VAR_ANALOG_CTRL(xCH__FA_COMMUNICATION_TIME,str_name);

		//
		str_name = "FA.COMMUNICATION.CTRL";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DEF__ENABLE_DISABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__FA_COMMUNICATION_CTRL,str_name);

		//
		str_name = "DEFAULT.INITIAL.STATE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DEF__DEFAULT_INITIAL_STATE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__DEFAULT_INITIAL_STATE,str_name);

		str_name = "DEFAULT.CONTROL.OFFLINE.STATE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DEF__DEFAULT_CONTROL_OFFLINE_STATE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__DEFAULT_CONTROL_OFFLINE_STATE,str_name);

		//
		str_name = "INITIAL.CONTROL.STATE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DEF__INITIAL_CONTROL_STATE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__INITIAL_CONTROL_STATE,str_name);

		//
		str_name = "TIME.FORMAT.TYPE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__TIME_FORMAT_TYPE,str_name);
	}
	
	// ...
	{
		str_name = "EVENT.OFFLINE.ACTIVE.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__EVENT_OFFLINE_ACTIVE_REQ,str_name);

		str_name = "EVENT.LOCAL.ACTIVE.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__EVENT_LOCAL_ACTIVE_REQ,str_name);

		str_name = "EVENT.REMOTE.ACTIVE.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__EVENT_REMOTE_ACTIVE_REQ,str_name);

		//
		str_name = "EVENT.OFFLINE.ACTIVE.STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__EVENT_OFFLINE_ACTIVE_STATUS,str_name);

		str_name = "EVENT.LOCAL.ACTIVE.STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__EVENT_LOCAL_ACTIVE_STATUS,str_name);

		str_name = "EVENT.REMOTE.ACTIVE.STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__EVENT_REMOTE_ACTIVE_STATUS,str_name);

		//
		str_name = "DVID.ECID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__DVID_ECID,str_name);

		str_name = "DVID.ECVAL";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__DVID_ECVAL,str_name);

		//
		str_name = "FA.HEARTBEAT.INTERVAL.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,60,"");
		LINK__VAR_ANALOG_CTRL(xCH__FA_HEARTBEAT_INTERVAL_SEC,str_name);

		//
		str_name = "TERMINAL.WIN_NAME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__TERMINAL_WIN_NAME,str_name);

		for(i=0;i<CFG__TERMINAL_MSG_SIZE;i++)
		{
			str_name.Format("TERMINAL.MSG%1d",i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__TERMINAL_MSG[i],str_name);
		}
	}

	// ...
	{
		str_name = "TERMINAL.LOG.COUNT";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__TERMINAL_LOG_COUNT,str_name);

		for(i=0; i<CFG__TERMINAL_LOG_SIZE; i++)
		{
			str_name.Format("TERMINAL.LOG.TITLE%1d",i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__TERMINAL_LOG_TITLE[i],str_name);

			str_name.Format("TERMINAL.LOG.MSG%1d",i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__TERMINAL_LOG_MSG[i],str_name);
		}

		//
		str_name = "TERMINAL.SEND.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__TERMINAL_SEND_REQ,str_name);

		str_name = "TERMINAL.SEND.MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__TERMINAL_SEND_MSG,str_name);

		//
		str_name = "LOOPBACK.TEST.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__LOOPBACK_TEST_REQ,str_name);

		str_name = "LOOPBACK.TEST.MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__LOOPBACK_TEST_MSG,str_name);

		//
		str_name = "RECV.SxFy";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__RECV_SxFy,str_name);

		str_name = "SEND.SxFy";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SEND_SxFy,str_name);
	}

	// ...
	{
		str_name = "ALL_ALARM.REPORT.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__ALL_ALARM_REPORT_FLAG,str_name);
	}

	// ...
	{
		str_name = "LOG_CTRL.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DEF__ENABLE_DISABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__LOG_CTRL__FLAG,str_name);

		str_name = "LOG_CTRL.MSG_FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DEF__ENABLE_DISABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__LOG_CTRL__CTRL_MSG_FLAG,str_name);

		str_name = "LOG_CTRL.SECSI_FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DEF__ENABLE_DISABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__LOG_CTRL__SECSI_FLAG,str_name);

		str_name = "LOG_CTRL.SECSII_FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DEF__ENABLE_DISABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__LOG_CTRL__SECSII_FLAG,str_name);

		str_name = "LOG_CTRL.S6F1_LOG_FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DEF__ENABLE_DISABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__LOG_CTRL__S6F1_LOG_FLAG,str_name);

		str_name = "LOG_CTRL.DATE_SIZE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"num",0,1,30,"");
		LINK__VAR_ANALOG_CTRL(xCH__LOG_CTRL__DATE_SIZE,str_name);

		str_name = "LOG_CTRL.INTERVAL.MIN_TIME";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"60 10 20 30","");
		LINK__VAR_DIGITAL_CTRL(xCH__LOG_CTRL__INTERVAL_MIN_TIME,str_name);

		str_name = "LOG_CTRL.PROPERTY_INFO";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__LOG_CTRL__PROPERTY_INFO,str_name);
	}

	// ...
	{
		str_name = "ENGS_CALL.WIN_NAME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__ENG_CALL__WIN_NAME,str_name);

		str_name = "ENGS_CALL.TEXT_MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__ENG_CALL__TEXT_MSG,str_name);

		str_name = "ENGS_CALL.EQP_CALL";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__ENG_CALL__EQP_CALL,str_name);

		str_name = "ENGS_CALL.PRC_CALL";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__ENG_CALL__PRC_CALL,str_name);
	}

	// ...
	{
		str_name = "CFG.DEVICEID";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"No.",0,0,32767,"");
		LINK__VAR_ANALOG_CTRL(xCH_CFG__DEVICEID,str_name);

		str_name = "CFG.T1";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,1.0,60.0,"");
		LINK__VAR_ANALOG_CTRL(xCH_CFG__T1,str_name);

		str_name = "CFG.T2";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,1.0,60.0,"");
		LINK__VAR_ANALOG_CTRL(xCH_CFG__T2,str_name);

		str_name = "CFG.T3";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,1.0,60.0,"");
		LINK__VAR_ANALOG_CTRL(xCH_CFG__T3,str_name);

		str_name = "CFG.T4";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,1.0,60.0,"");
		LINK__VAR_ANALOG_CTRL(xCH_CFG__T4,str_name);

		str_name = "CFG.T5";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,1.0,60.0,"");
		LINK__VAR_ANALOG_CTRL(xCH_CFG__T5,str_name);

		str_name = "CFG.T6";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,1.0,60.0,"");
		LINK__VAR_ANALOG_CTRL(xCH_CFG__T6,str_name);

		str_name = "CFG.T7";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,1.0,60.0,"");
		LINK__VAR_ANALOG_CTRL(xCH_CFG__T7,str_name);

		str_name = "CFG.T8";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,1.0,60.0,"");
		LINK__VAR_ANALOG_CTRL(xCH_CFG__T8,str_name);

		str_name = "CFG.RETRY_LIMIT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"num",0,1.0,10,"");
		LINK__VAR_ANALOG_CTRL(xCH_CFG__RETRY_LIMIT,str_name);

		str_name = "CFG.LINK_TEST";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,1.0,60,"");
		LINK__VAR_ANALOG_CTRL(xCH_CFG__LINK_TEST,str_name);
	}

	// ...
	{
		CString item_list;

		item_list  = STR__NOT_CTRL;
		item_list += " ";
		item_list += STR__ENABLE;
		item_list += " ";
		item_list += STR__DISABLE;

		//
		str_name = "CFG.S5Fy.REPLY.CTRL";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, item_list, "");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__S5Fy_REPLY_CTRL, str_name);

		str_name = "CFG.S6Fy.REPLY.CTRL";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, item_list, "");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__S6Fy_REPLY_CTRL, str_name);

		str_name = "CFG.S10Fy.REPLY.CTRL";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, item_list, "");
		LINK__VAR_DIGITAL_CTRL(xCH_CFG__S10Fy_REPLY_CTRL, str_name);
	}

	// ...
	{
		str_name = "CFG.PMC.SIZE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"num",0,1,10,"");
		LINK__VAR_ANALOG_CTRL(xCH_CFG__PMC_SIZE,str_name);
	}

	// ...
	{
		str_name = "FA.CONNECTION.INFO";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_CONNECTION_INFO,str_name);

		str_name = "FA.PROPERTY.INFO";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_PROPERTY_INFO,str_name);

		str_name = "FA.CONNECTION.CHANGE.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_CONNECTION_CHANGE_REQ,str_name);
	}

	// ...
	{
		str_name = "RCMD.SYSTEM_PAUSE.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_SYSTEM_PAUSE_FLAG,str_name);

		str_name = "RCMD.SYSTEM_RESUME.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_SYSTEM_RESUME_FLAG,str_name);

		str_name = "RCMD.SYSTEM_END.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_SYSTEM_END_FLAG,str_name);

		str_name = "RCMD.SYSTEM_STOP.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_SYSTEM_STOP_FLAG,str_name);

		str_name = "RCMD.SYSTEM_ABORT.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_SYSTEM_ABORT_FLAG,str_name);

		//
		str_name = "RCMD.SYSTEM_REMOTE.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_SYSTEM_REMOTE_FLAG,str_name);

		str_name = "RCMD.SYSTEM_LOCAL.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_SYSTEM_LOCAL_FLAG,str_name);

		str_name = "RCMD.SYSTEM_OFFLINE.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_SYSTEM_OFFLINE_FLAG,str_name);

		//
		str_name = "RCMD.PTN_CANCEL.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_PTN_CANCEL_FLAG,str_name);

		str_name = "RCMD.PTN_PAUSE.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_PTN_PAUSE_FLAG,str_name);

		str_name = "RCMD.PTN_RESUME.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_PTN_RESUME_FLAG,str_name);

		str_name = "RCMD.PTN_ABORT.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_PTN_ABORT_FLAG,str_name);

		//
		str_name = "RCMD.PM_ENABLE.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_PM_ENABLE_FLAG,str_name);

		str_name = "RCMD.PM_DISABLE.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_PM_DISABLE_FLAG,str_name);

		str_name = "RCMD.PM_CONTROL.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_PM_CONTROL_FLAG,str_name);

		for(i=0;i<CFG_PM_LIMIT;i++)
		{
			str_name.Format("RCMD.PMx.LIST%1d",i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__RCMD_PMC,"");
			LINK__VAR_DIGITAL_CTRL(xCH__RCMD_PMx_LIST[i],str_name);
		}

		//
		str_name = "RCMD.ALARM_BUZZER.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_ALARM_BUZZER_FLAG,str_name);

		str_name = "RCMD.SIGNAL_TOWER.RED.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_SIGNAL_TOWER_RED_FLAG,str_name);

		str_name = "RCMD.SIGNAL_TOWER.YELLOW.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_SIGNAL_TOWER_YELLOW_FLAG,str_name);

		str_name = "RCMD.SIGNAL_TOWER.GREEN.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_SIGNAL_TOWER_GREEN_FLAG,str_name);

		str_name = "RCMD.SIGNAL_TOWER.BLUE.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__RCMD_SIGNAL_TOWER_BLUE_FLAG,str_name);
	}

	// ...
	{
		str_name = "SPOOLING.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SPOOLING_STATE,str_name);

		str_name = "ECID.SPOOL.CONTROL";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(dCH_ECID__SPOOL_CONTROL,str_name);

		str_name = "ECID.MAX.SPOOL.TRANSMIT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"num",0,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH_ECID__MAX_SPOOL_TRANSMIT,str_name);

		str_name = "ECID.OVERWRITE.SPOOL";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(dCH_ECID__OVERWRITE_SPOOL,str_name);

		str_name = "ECID.MAX.SPOOL.SAVE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"num",0,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH_ECID__MAX_SPOOL_SAVE,str_name);

		// Spool Start Time  :  yyyymmddhhmmss
		str_name = "SVID.SPOOL.START.TIME";		
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH_SVID__SPOOL_START_TIME,str_name);		

		// Spool Count Total
		str_name = "SVID.SPOOL.COUNT.TOTAL";
		STD__ADD_ANALOG(str_name,"num",0,0,9999);
		LINK__VAR_ANALOG_CTRL(aCH_SVID__SPOOL_COUNT_TOTAL,str_name);

		// Spool Full Time   :  yyyymmddhhmmss
		str_name = "SVID.SPOOL.FULL.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH_SVID__SPOOL_FULL_TIME,str_name);

		// Spool Count Actual
		str_name = "SVID.SPOOL.COUNT.ACTUAL";
		STD__ADD_ANALOG(str_name,"num",0,0,9999);	
		LINK__VAR_ANALOG_CTRL(aCH_SVID__SPOOL_COUNT_ACTUAL,str_name);
	}

	// ...
	{
		str_name = "CFG.S10Fy.TID.CHECK.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"NO YES","");
		LINK__VAR_DIGITAL_CTRL(dCH_CFG__S10Fy_TID_CHECK_FLAG,str_name);
	}

	// E40 ...
	{
		str_name = "PJOB.ACTION";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__PJOB_ACTION,str_name);

		str_name = "PJOB.NAME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__PJOB_NAME,str_name);

		str_name = "PJOB.UPDATE.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__PJOB_UPDATE_FLAG,str_name);

		str_name = "AFTER_CST_LOAD.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__AFTER_CST_LOAD_FLAG,str_name);
	}

	// E94 ...
	{
		str_name = "CJOB.ACTION";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__CJOB_ACTION,str_name);

		str_name = "CJOB.NAME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__CJOB_NAME,str_name);

		str_name = "CJOB.UPDATE.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__CJOB_UPDATE_FLAG,str_name);

		for(int i=0;i<CFG_LP_LIMIT;i++)
		{
			str_name.Format("SCR.CJOB_START.WIN_NAME.%1d",i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(xCH_SCR__CJOB_START__WIN_NAME[i],str_name);

			str_name.Format("SCR.CJOB_START.CJOB_NAME.%1d",i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(xCH_SCR__CJOB_START__CJOB_NAME[i],str_name);
		}
	}

	// E87 ...
	{
		for(int i=0;i<CFG_LP_LIMIT;i++)
		{
			str_name.Format("CMS.UPDATE.FLAG.LP%1d", i+1);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__CMS_UPDATE_FLAG__LPx[i], str_name);		}
	}

	// PMx CEID ...
	{
		CString def_name;
		CString def_data;

		def_name = "PM_SIZE";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);

		iPMx_SIZE = atoi(def_data);
		if(iPMx_SIZE > CFG_PM_LIMIT)		iPMx_SIZE = CFG_PM_LIMIT;
		if(iPMx_SIZE < 0)					iPMx_SIZE = 0;

		for(i=0; i<iPMx_SIZE; i++)
		{
			def_name.Format("OBJ__PM%1d",i+1);
			p_variable->Get__DEF_CONST_DATA(def_name, def_data);

			sPMx_OBJ_NAME[i] = def_data;
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3,MON_ID__E30_CTRL);
		p_variable->Add__MONITORING_PROC(3,MON_ID__CONTROL_STATE_CTRL);
		p_variable->Add__MONITORING_PROC(3,MON_ID__USER_JOB);
		p_variable->Add__MONITORING_PROC(3,MON_ID__PMx_CEID);
	}
	return 1;
}

int CObj_FA__APP_CTRL::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

int CObj_FA__APP_CTRL::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	//

	return 1;
}


//-------------------------------------------------------------------------
#define  COMM_STS__CONFIG					0
#define  COMM_STS__DISABLE					1
#define  COMM_STS__ENABLE					2
#define  COMM_STS__NOT_USE					2


int CObj_FA__APP_CTRL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	//-------------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	CString def_var;
	CString def_data;

	//.....
	{
		iFLAG__DEVICE_ID_CONTROL = -1;

		def_var = "ENABLE__DEVICE_ID";
		def_data = "";

		p_ext_obj_create->Get__DEF_CONST_DATA_EX(def_var,def_data,-1);

		if(def_data.CompareNoCase("YES") == 0)
		{
			iFLAG__DEVICE_ID_CONTROL = 1;
		}
	}

	//.....
	{
		iFLAG__INITIAL_CONTROL_STATE = -1;

		def_var = "ENABLE__INITIAL_CONTROL_STATE";
		def_data = "";

		p_ext_obj_create->Get__DEF_CONST_DATA_EX(def_var,def_data,-1);

		if(def_data.CompareNoCase("YES") == 0)
		{
			iFLAG__INITIAL_CONTROL_STATE = 1;
		}
	}

	//.....
	{
		def_var = "COMMUNICATION_LIST__DISABLE_ENABLE";
		def_data = "";

		p_ext_obj_create->Get__DEF_CONST_DATA_EX(def_var,def_data,-1);

		if(def_data.CompareNoCase("YES") == 0)
		{
			CString var_name;
			CString var_data;

			xCH__FA_COMMUNICATION_FLAG->Get__DATA(var_data);

			var_name = xCH__FA_COMMUNICATION_FLAG->Get__VARIABLE_NAME();
			p_ext_obj_create->Change__LOCAL_DIGITAL_DESCRIPTOR_INFO(var_name,DSP__DISABLE_ENABLE);

			xCH__FA_COMMUNICATION_FLAG->Set__DATA(var_data);

			//
			iINIT__COMM_STS_TYPE = COMM_STS__CONFIG;
		}
		else
		{
			def_var = "INIT__COMM_STS";
			def_data = "";

			p_ext_obj_create->Get__DEF_CONST_DATA_EX(def_var,def_data,-1);

			if(def_data.CompareNoCase("NOT_USE") == 0)		iINIT__COMM_STS_TYPE = COMM_STS__NOT_USE;
			else											iINIT__COMM_STS_TYPE = COMM_STS__CONFIG;
		}
	}

	/*
	// ...
	{
		CString var_data;

		xCH__FA_COMMUNICATION_FLAG->Get__DATA(var_data);

		if(var_data.CompareNoCase(STR__DISABLE) == 0)
		{
			xCH__FA_COMMUNICATION_CTRL->Set__DATA(STR__DISABLE);
		}
		else
		{
			xCH__FA_COMMUNICATION_CTRL->Set__DATA(STR__ENABLE);
		}
	}
	*/

	// ...
	{
		CString obj_name;
		CString var_name;
		int i;

		for(i=0;i<iPMx_SIZE;i++)
		{
			obj_name = sPMx_OBJ_NAME[i];

			var_name = "CFG.PMC.USE";
			LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__PMx_CFG_USE[i], obj_name,var_name);

			var_name = "OBJ.STATUS";
			LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__PMx_OBJ_STATUS[i], obj_name,var_name);

			var_name = "SLIT.VLV.STS";
			LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__PMx_DOOR_STS[i], obj_name,var_name);

			var_name = "LIFT.PIN.STS";
			LINK__EXT_VAR_STRING_CTRL( xEXT_CH__PMx_LIFT_PIN_STS[i], obj_name,var_name);
		}
	}

	return 1;
}
int CObj_FA__APP_CTRL::__START__OBJECT()
{
	xSCH_MATERIAL_CTRL->Link__SERVICE_DB("");

	return 1;
}

//-------------------------------------------------------------------------
int CObj_FA__APP_CTRL::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	return flag;
}
int CObj_FA__APP_CTRL::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__E30_CTRL:
			if(iINIT__COMM_STS_TYPE == COMM_STS__NOT_USE)
				xCH__FA_COMMUNICATION_FLAG->Set__DATA("NOT_USE");

			Mon__E30_CTRL(p_variable);
			break;

		case MON_ID__CONTROL_STATE_CTRL:
			Mon__CONTROL_STATE_CTRL(p_variable);
			break;

		case MON_ID__USER_JOB:
			Mon__USER_JOB(p_variable);
			break;

		case MON_ID__PMx_CEID:
			Mon__PMx_CEID(p_variable);
			break;
	}

	return 1;
}
