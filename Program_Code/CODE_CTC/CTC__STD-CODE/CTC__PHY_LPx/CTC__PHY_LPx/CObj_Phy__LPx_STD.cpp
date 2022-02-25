#include "StdAfx.h"
#include "CMacro_LOG.h"

#include "CObj_Phy__LPx_STD.h"
#include "CObj_Phy__LPx_STD__DEF.h"
#include "CObj_Phy__LPx_STD__ALID.h"


extern CMacro_LOG  mMacro_LOG;


//-------------------------------------------------------------------------
CObj_Phy__LPx_STD::CObj_Phy__LPx_STD()
{

}
CObj_Phy__LPx_STD::~CObj_Phy__LPx_STD()
{

}

//-------------------------------------------------------------------------
int CObj_Phy__LPx_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	// ...
	{
		sObject_Name = obj;
	}

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,       "INIT");
		ADD__CTRL_VAR(sMODE__MAP,        "MAP");
		ADD__CTRL_VAR(sMODE__PREPLOAD,   "PREPLOAD");
		ADD__CTRL_VAR(sMODE__CID_READ,   "CID_READ");
		ADD__CTRL_VAR(sMODE__LOAD,       "LOAD");
		ADD__CTRL_VAR(sMODE__RLSUNLOAD,  "RLSUNLOAD");
		ADD__CTRL_VAR(sMODE__UNLOAD,     "UNLOAD");
		ADD__CTRL_VAR(sMODE__RELOAD,     "RELOAD");

		ADD__CTRL_VAR(sMODE__RF_CID_READ,  "RF_CID_READ");
		ADD__CTRL_VAR(sMODE__RF_PAGE_READ, "RF_PAGE_READ");
		ADD__CTRL_VAR(sMODE__RF_CID_WRITE, "RF_CID_WRITE");
		ADD__CTRL_VAR(sMODE__RF_PAGE_WRITE,"RF_PAGE_WRITE");

		ADD__CTRL_VAR(sMODE__SCH_MAP,    "SCH_MAP");
		ADD__CTRL_VAR(sMODE__CHECK_SLOT, "CHECK_SLOT");
	}
	return 1;
}
int CObj_Phy__LPx_STD::__DEFINE__VERSION_HISTORY(version)
{
	version += "JG.Lee \n";

	return 1;
}


// ...
#define  MON_ID__ALL_STATE							1
#define  MON_ID__PORT_CTRL							2

#define  MON_ID__FA_REPORT							11
#define  MON_ID__FA_ACCESS_And_TRANSFER				13

//
#define  DSP__MODE					"INIT  MAP  PREPLOAD  CID_READ  LOAD  RLSUNLOAD  UNLOAD  RF_CID_READ  RF_CID_WRITE  RF_PAGE_READ  RF_PAGE_WRITE"

#define  DSP__LPx_MODE				"DISABLE  PROCESS  DUMMY"
#define  DSP__LPx_SLOT_MAX			"25  26"
#define  DSP__LPx_TYPE				"PROCESS  DONNER  HANDLE  DONNER_HANDLE"
#define  DSP__LPx_MATERIAL_SIZE		"6  8"

#define  DSP__CST_STATUS			"UNKNOWN  NONE  EXIST"
#define  DSP__DOOR_STS				"UNKNOWN  CLOSE  OPEN"
#define  DSP__SHUTL_STS				"UNKNOWN  UNLOAD  LOAD"
#define  DSP__CLAMP_STS				"UNKNOWN  UNCLAMP  CLAMP"

#define  DSP__DISABLE_ENABLE		"DISABLE   ENABLE"
#define  DSP__ENABLE_DISABLE		"ENABLE   DISABLE"
#define  DSP__NO_YES				"NO  YES"
#define  DSP__ACCESS_MODE			"MANUAL  AUTO"


int CObj_Phy__LPx_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	//-------------------------------------------------------------------------------
	CString str_name;
	CString dsp_item;

	// ...
	{
		CString str_lp_id;
		p_variable->Get__DEF_CONST_DATA("LP_ID",str_lp_id);

		iPTN = atoi(str_lp_id);
		sPORT_NAME.Format("PORT%s",str_lp_id);
	}

	// ...
	{
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_CTRL",dsp_item);

		str_name = "LPx.CTRL";
		STD__ADD_DIGITAL(str_name,dsp_item);
		LINK__VAR_DIGITAL_CTRL(xCH__OBJ_CTRL,str_name);

		dVAR__MODE = "LPx.MODE";
		STD__ADD_DIGITAL(dVAR__MODE,DSP__MODE);
	}

	// ...
	{
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_STATUS",dsp_item);

		str_name = "VIRTUAL.OBJ.STATUS";
		STD__ADD_DIGITAL(str_name,dsp_item);
		LINK__VAR_DIGITAL_CTRL(xCH__VIRTUAL_OBJ_STATUS,str_name);

		str_name = "OBJ.STATUS";
		STD__ADD_DIGITAL(str_name,dsp_item);
		LINK__VAR_DIGITAL_CTRL(xCH__OBJ_STATUS,str_name);

		str_name = "SEQ_INFO.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__SEQ_INFO_MSG,"SEQ_INFO.MSG");

		//
		str_name = "CFG.USE";
		STD__ADD_DIGITAL(str_name,DSP__LPx_MODE);
		dCH_CFG__LPx_USE = p_variable->Get__VAR_DIGITAL_CTRL(str_name);	

		str_name = "CFG.PROCESS.TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"NORMAL TEST","");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PROCESS_TYPE,str_name);

		dVAR_CFG__SLOT_MAX = "CFG.SLOT.MAX";
		STD__ADD_DIGITAL(dVAR_CFG__SLOT_MAX,DSP__LPx_SLOT_MAX);

		str_name = "CFG.TYPE";
		STD__ADD_DIGITAL(str_name,DSP__LPx_TYPE);
		dCH_CFG__LPx_TYPE = p_variable->Get__VAR_DIGITAL_CTRL(str_name);	

		str_name = "CFG.MATERIAL_SIZE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__LPx_MATERIAL_SIZE,"");
		dCH_CFG__LPx_MATERIAL_SIZE = p_variable->Get__VAR_DIGITAL_CTRL(str_name);

		str_name = "PICK_COUNT";
		STD__ADD_STRING(str_name);
		sCH__LPx_PICK_COUNT = p_variable->Get__VAR_STRING_CTRL(str_name);

		str_name = "LAMP.STATUS";
		STD__ADD_STRING(str_name);
		sCH__LPx_LAMP_STATUS = p_variable->Get__VAR_STRING_CTRL(str_name);

		str_name = "JOB.STATUS.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__LPx_JOB_STATUS_FLAG, str_name);

		//
		str_name = "LPx.END.REQ.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__LPx_END_REQ_FLAG, str_name);

		str_name = "LPx.RETURN.REQ.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__LPx_RETURN_REQ_FLAG, str_name);

		//
		str_name = "CST.STATUS";
		STD__ADD_DIGITAL(str_name,DSP__CST_STATUS);
		dCH__CST_STATUS = p_variable->Get__VAR_DIGITAL_CTRL(str_name);

		str_name = "SHUTL.STS";
		STD__ADD_DIGITAL(str_name,DSP__SHUTL_STS);
		dCH__SHUTL_STS = p_variable->Get__VAR_DIGITAL_CTRL(str_name);

		str_name = "CLAMP.STS";
		STD__ADD_DIGITAL(str_name,DSP__CLAMP_STS);
		dCH__CLAMP_STS = p_variable->Get__VAR_DIGITAL_CTRL(str_name);

		str_name = "CID.STRING";
		STD__ADD_STRING(str_name);
		sCH__CID_STRING = p_variable->Get__VAR_STRING_CTRL(str_name);

		str_name = "DOOR.STS";
		STD__ADD_DIGITAL(str_name,DSP__DOOR_STS);
		dCH__DOOR_STS = p_variable->Get__VAR_DIGITAL_CTRL(str_name);

		str_name = "PIO.TRANSFER";
		STD__ADD_STRING_WITH_COMMENT(str_name,"LIST  :  YES NO");
		sCH__PIO_TRANSFER = p_variable->Get__VAR_STRING_CTRL(str_name);

		str_name = "PIO.COMM.READY.STS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		sCH__PIO_COMM_READY_STS = p_variable->Get__VAR_STRING_CTRL(str_name);
	}

	// ...
	{
		CString dsp_slot_sts;
		p_variable->Get__STD_DESCRIPTION("STD_SLOT_STATUS", dsp_slot_sts);

		CString str_slot_sts;
		int slot_id;

		int limit = CFG_LP__SLOT_MAX;
		int i;
	
		for(i=0;i<limit;i++)
		{
			slot_id = i+1;
			str_slot_sts.Format("SLOT%002d.STATUS",slot_id);

			STD__ADD_DIGITAL(str_slot_sts,dsp_slot_sts);
			LINK__VAR_DIGITAL_CTRL(xCH__SLOT_STATUS[i],str_slot_sts);
		}
	}

	// START & END BUTTON ...
	{
		str_name = "CFG.START_BUTTON.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_START_BUTTON_MODE,str_name);

		str_name = "CFG.END_BUTTON.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_END_BUTTON_MODE,str_name);

		//
		str_name = "START_BUTTON.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__START_BUTTON_FLAG,str_name);

		str_name = "END_BUTTON.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__END_BUTTON_FLAG,str_name);
	}

	// REQ ...
	{
		str_name = "LPx.HOQ.REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__LPx_HOQ_REQ,str_name);

		str_name = "LPx.HOQ.LOCK";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__LPx_HOQ_LOCK,str_name);

		str_name = "LPx.LOAD.REQ.BY.USER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__LPx_LOAD_REQ_BY_USER,str_name);
	}

	// APP VARIABLE ...
	{
		p_variable->Get__STD_DESCRIPTION(DSP__OBJ_CTRL, dsp_item);

		str_name = "APP.PORT.CTRL";
		STD__ADD_DIGITAL(str_name,dsp_item);
		dCH__PORT_CTRL = p_variable->Get__VAR_DIGITAL_CTRL(str_name);

		str_name = "APP.PORT.STATUS";
		STD__ADD_STRING(str_name);
		sCH__PORT_STATUS = p_variable->Get__VAR_STRING_CTRL(str_name);

		str_name = "APP.PORT.EXCEPTION";
		STD__ADD_STRING(str_name);
		sCH__PORT_EXCEPTION = p_variable->Get__VAR_STRING_CTRL(str_name);

		str_name = "APP.PORT.UNLOAD.REQ.FROM.TMC";
		STD__ADD_STRING(str_name);
		sCH__PORT_UNLOAD_REQ_FROM_TMC = p_variable->Get__VAR_STRING_CTRL(str_name);

		//
		str_name = "APP.LOCK.FLAG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__APP_LOCK_FLAG, str_name);

		str_name = "APP.VIRTUAL.PORT.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__VIRTUAL_PORT_STATUS, str_name);

		//
		str_name = "APP.PORT.LOTID";
		STD__ADD_STRING(str_name);
		sCH__PORT_LOTID = p_variable->Get__VAR_STRING_CTRL(str_name);

		str_name = "APP.PORT.PPID";
		STD__ADD_STRING(str_name);
		sCH__PORT_PPID = p_variable->Get__VAR_STRING_CTRL(str_name);

		//
		str_name = "APP.JOB.POPUP.TYPE";
		STD__ADD_STRING(str_name);
		sCH__PORT_JOB_POPUP_TYPE = p_variable->Get__VAR_STRING_CTRL(str_name);

		str_name = "APP.JOB.POPUP.FILE";
		STD__ADD_STRING(str_name);
		sCH__PORT_JOB_POPUP_FILE = p_variable->Get__VAR_STRING_CTRL(str_name);

		str_name = "APP.JOB.NAME";
		STD__ADD_STRING(str_name);
		sCH__PORT_JOB_NAME = p_variable->Get__VAR_STRING_CTRL(str_name);

		str_name = "APP.CJOBID";
		STD__ADD_STRING(str_name);
		sCH__PORT_CJOBID = p_variable->Get__VAR_STRING_CTRL(str_name);

		str_name = "CFG.JOB.END_SLOT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"slot",0,0,25,"");
		aCH__PORT_CFG_JOB_END_SLOT = p_variable->Get__VAR_ANALOG_CTRL(str_name);

		//
		str_name = "APP.LAST.PICK.SLOT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"slot",0,1,30,"");
		LINK__VAR_ANALOG_CTRL(aCH__LAST_PICK_SLOT,str_name);

		str_name = "APP.LAST.RESERVE.SLOT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"slot",0,1,30,"");
		LINK__VAR_ANALOG_CTRL(aCH__LAST_RESERVE_SLOT,str_name);

		//
		str_name = "FA.LP.SERVICE_REQ";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__NO_YES,"");
		LINK__VAR_DIGITAL_CTRL(xCH__FA_LP_SERVICE_REQ,str_name);

		str_name = "FA.LP.ACCESS_REQ";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__ACCESS_MODE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__FA_LP_ACCESS_REQ,str_name);

		str_name = "FA.LP.CURRENT_STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_LP_CURRENT_STATUS,str_name);

		str_name = "FA.LP.ACCESS_STATUS";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,DSP__ACCESS_MODE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__FA_LP_ACCESS_STATUS,str_name);

		str_name = "FA.LP.BYPASS_ID.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__FA_LP_BYPASS_READ_ID_FLAG,str_name);

		str_name = "FA.LP.MANUAL_LOADING.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__DISABLE_ENABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__FA_LP_MANUAL_LOADING_FLAG,str_name);

		str_name = "FA.LP.RESERVATION_STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_LP_RESERVATION_STATUS,str_name);
		
		str_name = "FA.LP.ASSOCIATION_STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_LP_ASSOCIATION_STATUS,str_name);
		
		str_name = "FA.LP.TRANSFER_STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_LP_TRANSFER_STATUS,str_name);
		
		str_name = "FA.CARRIERID_STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_CARRIERID_STATUS,str_name);
	
		str_name = "FA.MAP_STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_MAP_STATUS,str_name);

		str_name = "FA.CARRIER.ACCESS_STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__FA_CARRIER_ACCESS_STATUS,str_name);

		str_name = "FA.LP.HOST_VERIFY.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,DSP__ENABLE_DISABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__FA_LP_HOST_VERIFY_FLAG,str_name);

		//
		str_name = "RF.PAGE_NUM";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__RF_PAGE_NUM,str_name);

		str_name = "RF.DATA_LEN";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__RF_DATA_LEN,str_name);

		str_name = "RF.PAGE_DATA";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__RF_PAGE_DATA,str_name);

		//
		str_name = "SCR.WIN_CSTID";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SCR__WIN_CSTID,str_name);

		str_name = "RELOAD.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__RELOAD_FLAG,str_name);

		str_name = "RF.YES_NO.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__RF_YES_NO_FLAG,str_name);
		
		str_name = "SIDE_BUFFER.USE.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SIDE_BUFFER_USE_FLAG,str_name);

		//
		str_name = "DB.LOTID";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__DB_LOTID,str_name);

		str_name = "DB.ROUTEID";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__DB_ROUTEID,str_name);

		str_name = "DB.CYCLE.START.SLOT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"slot",0,1,25,"");
		LINK__VAR_ANALOG_CTRL(xCH__DB_CYCLE_START_SLOT,str_name);

		str_name = "DB.CYCLE.END.SLOT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"slot",0,1,25,"");
		LINK__VAR_ANALOG_CTRL(xCH__DB_CYCLE_END_SLOT,str_name);

		str_name = "DB.CYCLE.COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"count",0,1,99999,"");
		LINK__VAR_ANALOG_CTRL(xCH__DB_CYCLE_COUNT,str_name);

		str_name = "CUR.CYCLE.COUNT";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__CUR_CYCLE_COUNT,str_name);

		str_name = "DB.CYCLE.MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__DB_CYCLE_MSG,str_name);

		//
		str_name = "MANUAL.CTRL.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__MANUAL_CTRL_FLAG,str_name);

		str_name = "MANUAL.CTRL.RUNNING.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__MANUAL_CTRL_RUNNING_FLAG,str_name);

		//
		str_name = "CYCLE.CTRL.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__CYCLE_CTRL_FLAG,str_name);

		str_name = "CYCLE.CTRL.RUNNING.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__CYCLE_CTRL_RUNNING_FLAG,str_name);
	}

	// TMC LINK ...
	{
		str_name = "LINK.AMHS.IO.IN.VALID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_AMHS_IO_IN_VALID, str_name);

		str_name = "LINK.AMHS.IO.IN.CS_0";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_AMHS_IO_IN_CS_0, str_name);

		str_name = "LINK.AMHS.IO.IN.CS_1";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_AMHS_IO_IN_CS_1, str_name);

		str_name = "LINK.AMHS.IO.IN.TR_REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_AMHS_IO_IN_TR_REQ, str_name);

		str_name = "LINK.AMHS.IO.IN.BUSY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_AMHS_IO_IN_BUSY, str_name);

		str_name = "LINK.AMHS.IO.IN.COMPT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_AMHS_IO_IN_COMPT, str_name);

		str_name = "LINK.AMHS.IO.IN.CONT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_AMHS_IO_IN_CONT, str_name);

		//
		str_name = "LINK.AMHS.IO.OUT.L_REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_AMHS_IO_OUT_L_REQ, str_name);

		str_name = "LINK.AMHS.IO.OUT.U_REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_AMHS_IO_OUT_U_REQ, str_name);

		str_name = "LINK.AMHS.IO.OUT.READY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_AMHS_IO_OUT_READY, str_name);

		str_name = "LINK.AMHS.IO.OUT.HO_AVBL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_AMHS_IO_OUT_HO_AVBL, str_name);

		str_name = "LINK.AMHS.IO.OUT.ES";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LINK_AMHS_IO_OUT_ES, str_name);
	}

	// SIM CFG ...
	{
		str_name = "SCH_TEST.CFG.INIT.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_INIT_SEC, str_name);

		str_name = "SCH_TEST.CFG.MAP.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_MAP_SEC, str_name);

		str_name = "SCH_TEST.CFG.PREPLOAD.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PREPLOAD_SEC, str_name);

		str_name = "SCH_TEST.CFG.CID_READ.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_CID_READ_SEC, str_name);

		str_name = "SCH_TEST.CFG.LOAD.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_LOAD_SEC, str_name);

		str_name = "SCH_TEST.CFG.RLSUNLOAD.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_RLSUNLOAD_SEC, str_name);

		str_name = "SCH_TEST.CFG.UNLOAD.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_UNLOAD_SEC, str_name);

		str_name = "SCH_TEST.CFG.RELOAD.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_RELOAD_SEC, str_name);

		//
		str_name = "SCH_TEST.CFG.RF_CID_READ.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_RF_CID_READ_SEC, str_name);

		str_name = "SCH_TEST.CFG.RF_PAGE_READ.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_RF_PAGE_READ_SEC, str_name);

		str_name = "SCH_TEST.CFG.RF_CID_WRITE.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_RF_CID_WRITE_SEC, str_name);

		str_name = "SCH_TEST.CFG.RF_PAGE_WRITE.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_RF_PAGE_WRITE_SEC, str_name);
	}

	//-------------------------------------------------------------------------------
	{
		p_variable->Add__MONITORING_PROC(0.5,MON_ID__ALL_STATE);
		p_variable->Add__MONITORING_PROC(0.5,MON_ID__PORT_CTRL);

		p_variable->Add__MONITORING_PROC(3,MON_ID__FA_REPORT);
		p_variable->Add__MONITORING_PROC(3,MON_ID__FA_ACCESS_And_TRANSFER);
	}
	return 1;
}

int CObj_Phy__LPx_STD::__DEFINE__ALARM(p_alarm)
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
	ALARM_DEFINE__MODULE_OBJECT;

	// ...
	{
		alarm_title  = title;
		alarm_title += "OBJECT MODE : UNKNOWN";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("ABORT");
	
		ADD__ALARM_EX(ALID__OBJECT_MODE_UNKNOWN,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_title  = title;
		alarm_title += "Access Mode Violation !";

		alarm_msg.Format("LP%1d : Access Mode Violation !",iPTN);

		l_act.RemoveAll();
		l_act.Add("IGNORE");

		ADD__ALARM_EX(ALID__ACCESS_MODE_VIOLATION,alarm_title,alarm_msg,l_act);
	}

	// ... 
	{
		alarm_title  = title;
		alarm_title += "Carrier Verification Failure !";

		alarm_msg.Format("LP%1d : Carrier Verification Failure !",iPTN);

		l_act.RemoveAll();
		l_act.Add("IGNORE");

		ADD__ALARM_EX(ALID__CARRIER_VERIFY_FAIL,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_title  = title;
		alarm_title += "Slot Map Verification Failed !";

		alarm_msg.Format("LP%1d : Slot Map Verification Failed !",iPTN);

		l_act.RemoveAll();
		l_act.Add("IGNORE");

		ADD__ALARM_EX(ALID__MAP_VERIFY_FAIL,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_title  = title;
		alarm_title += "Port Access Manual To Auto : Error";

		alarm_msg.Format("LP%1d's port access mode can not be converted from manual to auto !",iPTN);

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(ALID__PORT_ACCESS__MANUAL_TO_AUTO,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_title  = title;
		alarm_title += "Port Access Auto To Manual : Error";

		alarm_msg.Format("LP%1d's port access mode can not be converted from auto to manual !",iPTN);

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(ALID__PORT_ACCESS__AUTO_TO_MANUAL,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_title  = title;
		alarm_bff.Format("The status of LP%1d's job-end button is not \"ON\"",iPTN);
		alarm_title += alarm_bff;

		alarm_msg  = "Can not execute the \"JOB END\" command.\n";
		alarm_bff.Format("To run the command, the status of LP%1d job-end button must be \"ON\".\n",iPTN);
		alarm_msg += alarm_bff;
		alarm_bff.Format("Please, check the status of LP%1d job-end button !",iPTN);
		alarm_msg += alarm_bff;

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(ALID__JOB_END_BUTTON__NOT_ON,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_title  = title;
		alarm_title += "Unexpectedly, cassette disappeared.";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("RETRY_CHECK");
		l_act.Add("ABORT");

		ADD__ALARM_EX(ALID__CST_DISAPPEAR__UNEXPECTEDLY,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_title  = title;
		alarm_bff.Format("LP%1d's status is out_of_service.",iPTN);
		alarm_title += alarm_bff;

		alarm_msg  = "Can not execute any command.\n";
		alarm_bff.Format("Currently, the status of LP%1d is \"OUT_OF_SERVICE\".\n",iPTN);
		alarm_msg += alarm_bff;
		alarm_msg += "Please, convert LP's status to \"FULL-AUTO\" or \"MANUAL\".\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(ALID__LPx_STATUS_OUT_OF_SERVICE__NOT_RUN,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_title  = title;
		alarm_bff.Format("Currently, LP%1d is in use. So, can't unload.",iPTN);
		alarm_title += alarm_bff;

		alarm_bff.Format("LP%1d is in use. \n", iPTN);
		alarm_msg  = alarm_bff;
		alarm_msg += "Can not execute \"unload\" command.\n";
		alarm_msg += "Please, wait until LP's status is not in use.\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(ALID__LPx_IN_USE__NOT_UNLOAD,alarm_title,alarm_msg,l_act);
	}

	
	// ...
	{
		alarm_id = ALID__LPx__JOB_END;

		alarm_title  = title;
		alarm_bff.Format("LP%1d's job is ended by user.",iPTN);
		alarm_title += alarm_bff;

		alarm_bff.Format("LP%1d's job is ended by user. \n", iPTN);
		alarm_msg  = alarm_bff;

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__LPx__JOB_ABORT;
		
		alarm_title  = title;
		alarm_bff.Format("LP%1d's job is aborted by user.",iPTN);
		alarm_title += alarm_bff;
		
		alarm_bff.Format("LP%1d's job is aborted by user. \n", iPTN);
		alarm_msg  = alarm_bff;
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__LPx__JOB_PAUSED;

		alarm_title  = title;
		alarm_bff.Format("LP%1d's job is paused by user.",iPTN);
		alarm_title += alarm_bff;

		alarm_bff.Format("LP%1d's job is paused by user. \n", iPTN);
		alarm_msg  = alarm_bff;

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__LPx__JOB_RESUMED;

		alarm_title  = title;
		alarm_bff.Format("LP%1d's job is resumed by user.",iPTN);
		alarm_title += alarm_bff;

		alarm_bff.Format("LP%1d's job is resumed by user. \n", iPTN);
		alarm_msg  = alarm_bff;

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__LPx__PROCESS_TYPE_TO_NORMAL;

		alarm_title  = title;
		alarm_bff.Format("LP%1d's process type is converted to \"Normal\".",iPTN);
		alarm_title += alarm_bff;
		
		alarm_bff.Format("LP%1d's process type is converted to \"Normal\".",iPTN);
		alarm_msg  = alarm_bff;
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__LPx__PROCESS_TYPE_TO_TEST;

		alarm_title  = title;
		alarm_bff.Format("LP%1d's process type is converted to \"Test\".",iPTN);
		alarm_title += alarm_bff;
		
		alarm_bff.Format("LP%1d's process type is converted to \"Test\".",iPTN);
		alarm_msg  = alarm_bff;
		
		l_act.RemoveAll();
		l_act.Add("CHECK");
		
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj_Phy__LPx_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	mMacro_LOG.Init_LOG();

	// ...
	p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App",sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}
		
	
	// INTERNAL PROPERTY ...
	{
		iSEQ__LOCK_FLAG = -1;
	
		xCH__LPx_HOQ_LOCK->Set__DATA("YES");
	}

	// EXTERNAL PROPERTY ...
	{
		CString obj_name;
		CString str_name;

		// ...
		{
			CString str_lp_id;
			p_ext_obj_create->Get__DEF_CONST_DATA("LP_ID",str_lp_id);

			iPTN = atoi(str_lp_id);
			sPORT_NAME.Format("PORT%s",str_lp_id);
		}

		// ...
		{
			p_ext_obj_create->Get__DEF_CONST_DATA("DB_CFG_NAME",obj_name);

			//
			str_name = "SCH_TEST.CFG.TMC_DUMMY_BY_CTC";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC, obj_name,str_name);

			//
			str_name.Format("CFG.LP%1d.JOB_START.FLAG",iPTN);
			LINK__EXT_VAR_STRING_CTRL(xEXT_CH__CFG_LPx_JOB_START_FLAG, obj_name,str_name);

			str_name = "CFG.LPx.MANUAL_TO_AUTO.ALWAYS.APPLY";
			LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__CFG_LPx_MANUAL_TO_AUTO_ALWAYS_APPLY, obj_name,str_name);

			str_name = "CFG.LPx.PIO.READY.CHECK.MODE";
			LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__CFG_LPx_PIO_READY_CHECK_MODE, obj_name,str_name);
		
			str_name = "CFG.LPx.CID.FORMAT";
			LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__CFG_LPx_CID_FORMAT, obj_name,str_name);

			//
			str_name = "SCH.MAP.DEVICE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SCH_MAP_DEVICE, obj_name,str_name);

			str_name.Format("LP%1d.MAP.REQ",iPTN);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LPx_MAP_REQ, obj_name,str_name);

			//
			str_name = "CFG.LPx.ACCESS_MODE.AUTO_CTRL.FLAG";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LPx_ACCESS_MODE_AUTO_CTRL_FLAG, obj_name,str_name);
		}

		// ...
		{
			CString def_name;
			CString def_data;

			def_name = "FLAG.LPx_MANUAL_LOAD";
			p_ext_obj_create->Get__DEF_CONST_DATA_EX(def_name,def_data,-1);

			if(def_data.CompareNoCase("YES") == 0)
			{
				iFLAG__LPx_AUTO_LOAD = -1;
			}
			else
			{
				iFLAG__LPx_AUTO_LOAD = 1;
			}
		}

		// ...
		{
			p_ext_obj_create->Get__DEF_CONST_DATA("WIN_CSTID_NAME", sWIN_CSTID__NAME);
		}

		// ...
		{
			p_ext_obj_create->Get__DEF_CONST_DATA("OBJ__SIGNAL_TOWER",obj_name);

			LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__MELODY_BUZZER,obj_name,"MELODY.BUZZER");
			LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__MELODY_CTRL,  obj_name,"MELODY.CTRL");
		}
	}


	// ...
	{
		xI_Module_Obj->Link__ERROR_FEEDBACK(&mERROR__MODULE_OBJ);
	
		xI_Module_Obj->Link__Object_Name(sObject_Name);
		xI_Module_Obj->Register__Module_Status_Channel(xCH__OBJ_STATUS->Get__VARIABLE_NAME());
		xI_Module_Obj->Register__Module_Mode_Channel(dVAR__MODE);
		xI_Module_Obj->Register__Module_Ctrl_Channel(xCH__OBJ_CTRL->Get__VARIABLE_NAME());

		xI_Module_Obj->Disable__CTCINUSE_TO_STANDBY();
	}

	// ...
	{
		iFLAG__MODULE_OBJ = -1;
		iCALL_FLAG__FNC_UNLOAD = -1;

		sCH__LPx_LAMP_STATUS->Set__DATA("FINISH");
	}
	return 1;
}

int CObj_Phy__LPx_STD::__START__OBJECT()
{
	xI_SCH_MATERIAL_CTRL->Link__SERVICE_DB("");

	xI_SCH_MATERIAL_CTRL->Register__SYSTEM_NAME(sObject_Name);
	return 1;
}


//-------------------------------------------------------------------------
int CObj_Phy__LPx_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	xI_Module_Obj->Enable__ERROR_CHECK__NOT_STANDBY();

	// ...
	int flag = -1;

	if(xCH__FA_LP_CURRENT_STATUS->Check__DATA(STR__OUT_OF_SERVICE) > 0)
	{
		int alarm_id = ALID__LPx_STATUS_OUT_OF_SERVICE__NOT_RUN;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);
	}
	else
	{
		     IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__MAP)				flag = Call__MAP(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PREPLOAD)			flag = Call__PREPLOAD(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__CID_READ)			flag = Call__CID_READ(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__LOAD)				flag = Call__LOAD(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__RLSUNLOAD)		flag = Call__RLSUNLOAD(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__UNLOAD)			flag = Call__UNLOAD(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__RELOAD)			flag = Call__RELOAD(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__RF_CID_READ)		flag = Call__RF_CID_READ(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__RF_PAGE_READ)		flag = Call__RF_PAGE_READ(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__RF_CID_WRITE)		flag = Call__RF_CID_WRITE(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__RF_PAGE_WRITE)	flag = Call__RF_PAGE_WRITE(p_variable);

		ELSE_IF__CTRL_MODE(sMODE__SCH_MAP)			flag = Call__SCH_MAP(p_variable);
		ELSE_IF__CTRL_MODE(sMODE__CHECK_SLOT)		flag = Call__CHECK_SLOT(p_variable);
	
		else 
		{
			CString bff;
			CString alarm_msg;
			CString r_act;

			bff.Format("Object Name : %s\n",sObject_Name);
			alarm_msg  = bff;
			bff.Format("Unknown Object Mode : \"%s\"\n",mode);
			alarm_msg += bff;

			p_alarm->Popup__ALARM_With_MESSAGE(ALID__OBJECT_MODE_UNKNOWN,alarm_msg,r_act);		
		}
	}

	return flag;
}
int CObj_Phy__LPx_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__ALL_STATE:
			Mon__ALL_STATE(p_variable,p_alarm);
			break;

		case MON_ID__PORT_CTRL:
			Mon__PORT_CTRL(p_variable,p_alarm);
			break;

		//
		case MON_ID__FA_REPORT:
			Mon__FA_REPORT(p_variable);
			break;

		case MON_ID__FA_ACCESS_And_TRANSFER:
			Mon__FA_ACCESS_And_TRANSFER(p_variable,p_alarm);
			break;
	}

	return 1;
}
