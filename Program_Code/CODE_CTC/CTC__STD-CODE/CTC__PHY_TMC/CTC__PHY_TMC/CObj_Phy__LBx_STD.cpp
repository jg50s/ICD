#include "StdAfx.h"
#include "CObj_Phy__LBx_STD.h"
#include "CObj_Phy__LBx_STD__DEF.h"


//-------------------------------------------------------------------------
CObj_Phy__LBx_STD::CObj_Phy__LBx_STD()
{

}
CObj_Phy__LBx_STD::~CObj_Phy__LBx_STD()
{

}

//-------------------------------------------------------------------------
int CObj_Phy__LBx_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,  "INIT");
		ADD__CTRL_VAR(sMODE__MAINT, "MAINT");

		ADD__CTRL_VAR(sMODE__PUMP, "PUMP");
		ADD__CTRL_VAR(sMODE__VENT, "VENT");

		ADD__CTRL_VAR(sMODE__DOOR_OPEN,  "DOOR.OPEN");
		ADD__CTRL_VAR(sMODE__DOOR_CLOSE, "DOOR.CLOSE");

		ADD__CTRL_VAR(sMODE__SLOT_OPEN,  "SLOT.OPEN");
		ADD__CTRL_VAR(sMODE__SLOT_CLOSE, "SLOT.CLOSE");

		ADD__CTRL_VAR(sMODE__PIN_UP,   "PIN.UP");
		ADD__CTRL_VAR(sMODE__PIN_DOWN, "PIN.DOWN");

		ADD__CTRL_VAR(sMODE__PREPMATER, "PREPMATER");
		ADD__CTRL_VAR(sMODE__MAP,       "MAP");
		ADD__CTRL_VAR(sMODE__COMPMATER,    "COMPMATER"); 
		ADD__CTRL_VAR(sMODE__COMPMATER_EX, "COMPMATER.EX"); 
		ADD__CTRL_VAR(sMODE__ISOLATE,   "ISOLATE");

		//
		ADD__CTRL_VAR(sMODE__PROC_MAIN,  "PROC_MAIN");
		ADD__CTRL_VAR(sMODE__PROC_PRE,   "PROC_PRE");
		ADD__CTRL_VAR(sMODE__PROC_POST,  "PROC_POST");

		ADD__CTRL_VAR(sMODE__PROC_MAINT, "PROC_MAINT");

		//
		ADD__CTRL_VAR(sMODE__SCH_TEST_CFG, "SCH_TEST.CFG");
	}
	return 1;
}
int CObj_Phy__LBx_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__ALL_STATE                              1

// ...
#define  DSP__MODE										\
"INIT  MAINT											\
 PUMP  VENT												\
 DOOR.OPEN  DOOR.CLOSE									\
 SLOT.OPEN  SLOT.CLOSE									\
 PIN.UP  PIN.DOWN    									\
 PREPMATER  MAP											\
 COMPMATER  COMPMATER.EX  ISOLATE						\
 LOAD  UNLOAD											\
 PROC_READY  PROC_START									\
 PRE_READY   PRE_START									\
 CLN_READY   CLN_START									\
 MNT_READY   MNT_START"

#define  DSP__NO_YES			"NO  YES"
#define  DSP__ENABLE_DISABLE    "ENABLE  DISABLE"


int CObj_Phy__LBx_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	//--------------------------------------------------------------------------
	CString str_name;
	int i;

	// ...
	CString dsp__obj_sts;
	p_variable->Get__STD_DESCRIPTION("STD_OBJ_STATUS", dsp__obj_sts);

	// ...
	{
		CString dsp_item;
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_CTRL",dsp_item);

		// ACT REPORT ...
		{
			str_name = "TIME.ACT.START";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__TIME_ACT_START, str_name);

			str_name = "TIME.ACT.END";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__TIME_ACT_END, str_name);

			str_name = "TIME.ACT.TACK";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__TIME_ACT_TACK, str_name);

			str_name = "TIME.ACT.RESULT";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__TIME_ACT_RESULT, str_name);
		}

		// LOG ...
		{
			str_name = "LOG.SUB_DIRECTORY";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__LOG_SUB_DIRECTORY,str_name);

			str_name = "LOG.FILE_NAME";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__LOG_FILE_NAME,str_name);

			//
			str_name = "WFR.LOG.INFO";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__WFR_LOG_INFO, str_name);
		}

		// NEXT_CTRL_REQ
		{
			str_name = "NEXT.CTRL_REQ";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__NEXT_CTRL_REQ, str_name);
		}
		// ...
		{
			str_name = "LBx.CTRL";
			STD__ADD_DIGITAL(str_name,dsp_item);
			LINK__VAR_DIGITAL_CTRL(xCH__LBx_CTRL, str_name);

			str_name = "LBx.MODE";
			STD__ADD_DIGITAL(str_name, DSP__MODE);
			LINK__VAR_DIGITAL_CTRL(xCH__LBx_MODE, str_name);

			//
			str_name = "LBx.SLOT.ID";
			STD__ADD_DIGITAL(str_name, "1 2");
			LINK__VAR_DIGITAL_CTRL(xCH__LBx_SLOT_ID, str_name);
		}
		
		// ...
		{
			str_name = "OBJ.MSG";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__OBJ_MSG,str_name);

			str_name = "OBJ.FNC.MSG";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(xCH__OBJ_FNC_MSG,str_name);
		}

		// ...
		{
			str_name = "UPPER_OBJ.MSG";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__UPPER_OBJ_MSG, str_name);
		}
	}

	// ...
	{
		str_name = "CFG.USE.FLAG";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, DSP__ENABLE_DISABLE,"");
		LINK__VAR_DIGITAL_CTRL(xCH__CFG_USE_FLAG,str_name);

		//
		str_name = "MOVE.FLAG";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,DSP__NO_YES,"");
		LINK__VAR_DIGITAL_CTRL(xCH__MOVE_FLAG, str_name);

		str_name = "ACTIVE.VAC_AREA.CTRL";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(xCH__ACTIVE_VAC_AREA_CTRL, str_name);

		str_name = "ACTIVE.ATM_AREA.CTRL";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(xCH__ACTIVE_ATM_AREA_CTRL, str_name);

		//
		sVAR_SCH__IN_OUT_FLAG = "SCH.IN_OUT.FLAG";
		STD__ADD_STRING_WITH_COMMENT(sVAR_SCH__IN_OUT_FLAG, "LIST : IN OUT");

		sVAR_SCH__IN_COUNT = "SCH.IN_COUNT";
		STD__ADD_STRING_WITH_COMMENT(sVAR_SCH__IN_COUNT,"");

		sVAR_SCH__OUT_COUNT = "SCH.OUT_COUNT";
		STD__ADD_STRING_WITH_COMMENT(sVAR_SCH__OUT_COUNT,"");

		sVAR_SCH__CR_REQ = "SCH.CR.REQ";
		STD__ADD_STRING_WITH_COMMENT(sVAR_SCH__CR_REQ,"");

		str_name = "SCH.IDLE_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SCH_IDLE_COUNT, str_name);
	}

	// PARA ...
	{
		str_name = "PARA.SLOT_ID";
		STD__ADD_DIGITAL(str_name, "1 2");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_SLOT_ID, str_name);

		//
		str_name = "PARA.VENT_COOLING_SEC";
		STD__ADD_ANALOG(str_name, "sec", 0, 0, 9999);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_VENT_COOLING_SEC, str_name);

		str_name = "COUNT.VENT_COOLING_SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__COUNT_VENT_COOLING_SEC, str_name);
	}

	// ...
	{
		str_name = "OBJ.VIRTUAL.STATUS";
		STD__ADD_DIGITAL(str_name, dsp__obj_sts);
		LINK__VAR_DIGITAL_CTRL(xCH__OBJ_VIRTUAL_STATUS,str_name);

		str_name = "OBJ.STATUS";
		STD__ADD_DIGITAL(str_name, dsp__obj_sts);
		LINK__VAR_DIGITAL_CTRL(xCH__OBJ_STATUS,str_name);

		//
		str_name = "PRESSURE.VALUE";
		STD__ADD_ANALOG(str_name,"torr",3,0.0,1000.0);
		LINK__VAR_ANALOG_CTRL(xCH__PRESSURE_VALUE,str_name);

		str_name = "VAC.SNS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__VAC_SNS,str_name);

		//
		str_name = "CFG.HEATING.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__CFG_HEATING_TIME, str_name);
		
		str_name = "APP.HEATING.TIME_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__APP_HEATING_TIME_COUNT, str_name);

		//
		str_name = "PRESSURE.mTORR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__PRESSURE_mTORR,str_name);

		//
		str_name = "PRE_MAINT_FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__PRE_MAINT_FLAG,str_name);

		//
		str_name = "PUMPING.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__PUMPING_FLAG,str_name);

		str_name = "PUMPING.COMP.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__PUMPING_COMP_FLAG,str_name);

		//
		str_name = "VENTING.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__VENTING_FLAG,str_name);

		str_name = "VENTING.COMP.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__VENTING_COMP_FLAG,str_name);
	}

	// ...
	{
		CString dsp_item;
		p_variable->Get__STD_DESCRIPTION("STD_PRESSURE_STATUS",dsp_item);

		str_name = "PRESSURE.STATUS";
		STD__ADD_DIGITAL(str_name,dsp_item);
		LINK__VAR_DIGITAL_CTRL(xCH__PRESSURE_STATUS,str_name);
	}

	// ...
	{
		CString dsp_item;
		p_variable->Get__STD_DESCRIPTION("STD_VALVE_STATUS",dsp_item);

		str_name = "SLOT.NO";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SLOT_NO,str_name);

		// ...
		{
			str_name = "SLIT.VLV.STS";
			STD__ADD_DIGITAL(str_name,dsp_item);
			LINK__VAR_DIGITAL_CTRL(dCH__SLIT_VLV_STS_X, str_name);

			for(i=0; i<CFG_LBx__SLOT_MAX; i++)
			{
				str_name.Format("SLIT.VLV.STS.%1d", i+1);
				STD__ADD_DIGITAL(str_name,dsp_item);
				LINK__VAR_DIGITAL_CTRL(dCH__SLIT_VLV_STS_SLOT[i], str_name);
			}
		}

		// ...
		{
			str_name = "DOOR.STS";
			STD__ADD_DIGITAL(str_name, dsp_item);
			LINK__VAR_DIGITAL_CTRL(dCH__DOOR_STS_X, str_name);
	
			for(i=0; i<CFG_LBx__SLOT_MAX; i++)
			{
				str_name.Format("DOOR.STS.%1d", i+1);
				STD__ADD_DIGITAL(str_name, dsp_item);
				LINK__VAR_DIGITAL_CTRL(dCH__DOOR_STS_SLOT[i], str_name);
			}
		}

		//
		str_name = "SVID.SLOT_DATA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__SVID_SLOT_DATA,str_name);

		str_name = "SVID.SLIT_VLV_STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(xCH__SVID_SLIT_VLV_STS,str_name);
	}

	// ...
	{
		CString dsp__slot_sts;
		p_variable->Get__STD_DESCRIPTION("STD_SLOT_STATUS",dsp__slot_sts);

		CString str_slot_status;
		CString str_slot_title;
		int slot_id;

		int slot_limit = CFG_LBx__SLOT_MAX;
		int i;

		for(i=0; i<slot_limit; i++)
		{
			slot_id = i+1;

			//
			str_slot_status.Format("SLOT%002d.VIRTUAL_STATUS", slot_id);
			STD__ADD_DIGITAL(str_slot_status, dsp__obj_sts);
			LINK__VAR_DIGITAL_CTRL(xCH__SLOT_X_VIRTUAL_STATUS[i], str_slot_status);

			str_slot_status.Format("SLOT%002d.STATUS", slot_id);
			STD__ADD_DIGITAL(str_slot_status, dsp__slot_sts);
			LINK__VAR_DIGITAL_CTRL(xCH__SLOT_STATUS[i], str_slot_status);

			//
			str_slot_title.Format("SLOT%002d.TITLE", slot_id);
			STD__ADD_STRING(str_slot_title);
			LINK__VAR_STRING_CTRL(xCH__SLOT_TITLE[i], str_slot_title);
		}

		// ...
		{
			str_name = "LLx.LPx_PTN";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__LLx_LPx_PTN, str_name);

			str_name = "LLx.LPx_STN";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__LLx_LPx_STN, str_name);

			//
			str_name = "LLx.PPID";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__LLx_PPID, str_name);

			str_name = "LLx.LOTID";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__LLx_LOTID, str_name);

			str_name = "LLx.MATERIALID";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__LLx_MATERIALID, str_name);
		}

		//
		str_name = "SCH.AUTO_PUMPING.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SCH_AUTO_PUMPING_REQ,str_name);

		str_name = "SCH.AUTO_PUMPING.LOCK";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SCH_AUTO_PUMPING_LOCK,str_name);

		str_name = "SCH.LOCK";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__SCH_LOCK,str_name);

		//
		aVAR__PARA__PREPMATERIAL_SLOT = "PREPMATERIAL.SLOT";
		STD__ADD_ANALOG(aVAR__PARA__PREPMATERIAL_SLOT,"num",0,1,slot_limit);

		str_name = "PARA.PREHEAT.TIME";
		STD__ADD_ANALOG(str_name,"sec",1,0.0,9999.0);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PREHEAT_TIME,str_name);

		str_name = "PARA.COOLING.TIME";
		STD__ADD_ANALOG(str_name,"sec",1,0.0,9999.0);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_COOLING_TIME,str_name);
	}

	// SIM CFG ...
	{
		str_name = "SCH_TEST.CFG.INIT.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_INIT_SEC, str_name);

		//
		str_name = "SCH_TEST.CFG.PUMP.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PUMP_SEC, str_name);
		
		str_name = "SCH_TEST.CFG.VENT.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_VENT_SEC, str_name);
		
		//
		str_name = "SCH_TEST.CFG.DOOR.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 1.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_DOOR_SEC, str_name);

		str_name = "SCH_TEST.CFG.SLOT.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 1.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_SLOT_SEC, str_name);

		//
		str_name = "SCH_TEST.CFG.PREPMATER.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PREPMATER_SEC, str_name);
		
		str_name = "SCH_TEST.CFG.MAP.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_MAP_SEC, str_name);
		
		str_name = "SCH_TEST.CFG.COMPMATER.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_COMPMATER_SEC, str_name);
		
		str_name = "SCH_TEST.CFG.COMPMATER_EX.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_COMPMATER_EX_SEC, str_name);
		
		str_name = "SCH_TEST.CFG.ISOLATE.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_ISOLATE_SEC, str_name);
		
		str_name = "SCH_TEST.CFG.LOAD.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_LOAD_SEC, str_name);
		
		str_name = "SCH_TEST.CFG.UNLOAD.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_UNLOAD_SEC, str_name);

		//
		str_name = "SCH_TEST.CFG.PROC_READY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PROC_READY_SEC, str_name);

		str_name = "SCH_TEST.CFG.PROC_START.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SCH_TEST_CFG_PROC_START_SEC, str_name);
	}

	// PROCESS CHANNEL ...
	{
		str_name = "PARA.PROC.RECIPE.NAME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_PROC_RECIPE_NAME, str_name);

		str_name = "PARA.PROC.SCH.NAME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_PROC_SCH_NAME, str_name);

		//
		str_name = "PROC_INFO.STEP_MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PROC_INFO_STEP_MSG, str_name);

		str_name = "PROC_INFO.STEP_MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PROC_INFO_STEP_MODE, str_name);

		str_name = "PROC_INFO.STEP_TOTAL_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PROC_INFO_STEP_TOTAL_TIME, str_name);

		str_name = "PROC_INFO.STEP_CUR_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PROC_INFO_STEP_CUR_TIME, str_name);

		str_name = "PROC_INFO.TOTAL_PROC_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PROC_INFO_TOTAL_PROC_TIME, str_name);

		str_name = "PROC_INFO.CUR_PROC_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PROC_INFO_CUR_PROC_TIME, str_name);

		str_name = "PROC_INFO.TOTAL_STEP_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PROC_INFO_TOTAL_STEP_COUNT, str_name);

		str_name = "PROC_INFO.CUR_STEP_COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PROC_INFO_CUR_STEP_COUNT, str_name);

		str_name = "PROC_INFO.PROCESS_STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PROC_INFO_PROCESS_STATUS, str_name);

		//
		str_name = "PROC_INFO.TOTAL.PRC_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PROC_INFO_TOTAL_PRC_TIME, str_name);

		str_name = "PROC_INFO.CHANGE.PRC_TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PROC_INFO_CHANGE_PRC_TIME, str_name);

		str_name = "PROC_INFO.PROCESS.PERCENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PROC_INFO_PROCESS_PERCENT,str_name);

		str_name = "PROC_INFO.PROCESS_BAR.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PROC_INFO_PROCESS_BAR_STATUS, str_name);
	}

	// DA OFFSET ...
	{
		str_name = "FDC.DA.RT.OFFSET";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__FDC_DA_RT_OFFSET, str_name);

		str_name = "FDC.DA.R.OFFSET";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__FDC_DA_R_OFFSET, str_name);

		str_name = "FDC.DA.T.OFFSET";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__FDC_DA_T_OFFSET, str_name);
	}

	// ...
	{
		str_name = "PARA.TEMPLATE_FILE";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_TEMPLATE_FILE, str_name);
	}

	iMON_FLAG__PRESSURE_STATUS = -1;

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__ALL_STATE);
	}
	return 1;
}

int CObj_Phy__LBx_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	int alarm_id;
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// ...
	ALARM_DEFINE__MODULE_OBJECT;

	// ...
	{
		alarm_id = ALID__OBJECT_MODE_UNKNOWN;

		alarm_title  = title;
		alarm_title += "OBJECT MODE : UNKNOWN";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add(_ACT__ABORT);

		ADD__ALARM_EX(alarm_id, alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__VENT_ERROR;

		alarm_title  = title;
		alarm_title += "VENT ERROR";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add(_ACT__ABORT);
		l_act.Add(_ACT__RETRY);

		ADD__ALARM_EX(alarm_id, alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__PUMP_ERROR;

		alarm_title  = title;
		alarm_title += "PUMP ERROR";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add(_ACT__ABORT);
		l_act.Add(_ACT__RETRY);

		ADD__ALARM_EX(alarm_id, alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__DOOR_VALVE_OPEN_ERROR;

		alarm_title  = title;
		alarm_title += "DOOR VALVE OPEN ERROR";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add(_ACT__ABORT);
		l_act.Add(_ACT__RETRY);

		ADD__ALARM_EX(alarm_id, alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__SLOT_VALVE_OPEN_ERROR;

		alarm_title  = title;
		alarm_title += "SLOT VALVE OPEN ERROR";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add(_ACT__ABORT);
		l_act.Add(_ACT__RETRY);

		ADD__ALARM_EX(alarm_id, alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj_Phy__LBx_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	p_ext_obj_create->Link__DEF_VARIABLE__ERROR_FEEDBACK(&mERROR__DEF_VAR);

	// ...
	CString def_name;
	CString def_data;
	CString var_name;
	int i;

	// ...
	{
		sSCH_NAME = "";

		def_name = "OBJ__SCH_NAME";
		if(p_ext_obj_create->Get__DEF_CONST_DATA_EX(def_name,def_data,-1) > 0)
		{
			sSCH_NAME = def_data;
		}
	}

	// ...
	{
		CString cfg_db_name;
		p_ext_obj_create->Get__DEF_CONST_DATA("DB_CFG_NAME",cfg_db_name);

		//
		var_name = "SCH_TEST.CFG.TMC_DUMMY_BY_CTC";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC, cfg_db_name,var_name);

		//
		var_name = "TRANSFER.MODE";
		LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH_CFG__TRANSFER_MODE, cfg_db_name,var_name);

		var_name = "REF.ATM.PRESSURE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH_CFG__REF_ATM_PRESSURE, cfg_db_name,var_name);

		var_name = "REF.VAC.PRESSURE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH_CFG__REF_VAC_PRESSURE, cfg_db_name,var_name);

		//
		for(i=0; i<CFG_LLx__SLOT_MAX; i++)
		{
			int id = i + 1;

			var_name.Format("%s.SLOT%1d_STATUS", sSCH_NAME,id);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LL_SLOT_X_STATUS[i], cfg_db_name,var_name);
		}
	}

	// ...
	{
		xI_Module_Obj->Link__ERROR_FEEDBACK(&mERROR__MODULE_OBJ);

		//
		xI_Module_Obj->Link__Object_Name(sObject_Name);

		xI_Module_Obj->Register__Module_Status_Channel(xCH__OBJ_STATUS->Get__VARIABLE_NAME());
		xI_Module_Obj->Register__Module_Mode_Channel(xCH__LBx_MODE->Get__VARIABLE_NAME());
		xI_Module_Obj->Register__Module_Ctrl_Channel(xCH__LBx_CTRL->Get__VARIABLE_NAME());

		xI_Module_Obj->Disable__CTCINUSE_TO_STANDBY();

		// ...
		{
			CString data_const;
			p_ext_obj_create->Get__DEF_CONST_DATA_EX("FLAG.REPORT_ABORTED_ALARM",data_const,-1);

			if(data_const.CompareNoCase("DISABLE") == 0)
			{
				xI_Module_Obj->Disable__REPORT_ABORTED_ALARM();
			}
		}
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xI_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xI_LOG_CTRL->SET__PROPERTY(file_name,24*7,60);

		xI_LOG_CTRL->DISABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG(log_msg);

		xI_LOG_CTRL->ENABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	{
		iActive__CTRL_STS = -1;
		iActive__PROC_STS = -1;
	}
	// ...
	{
		double cfg_sec;

		cfg_sec = aCH__SCH_TEST_CFG_PROC_READY_SEC->Get__VALUE();
		if(cfg_sec < 1)		aCH__SCH_TEST_CFG_PROC_READY_SEC->Set__VALUE(1.0);

		cfg_sec = aCH__SCH_TEST_CFG_PROC_START_SEC->Get__VALUE();
		if(cfg_sec < 1)		aCH__SCH_TEST_CFG_PROC_START_SEC->Set__VALUE(10.0);
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;
		x_seq_info->Get__DIR_ROOT(sDir_ROOT);

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}

int CObj_Phy__LBx_STD::__START__OBJECT()
{
	xI_SCH_MATERIAL_CTRL->Link__SERVICE_DB("");
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Phy__LBx_STD::__CALL__CONTROL_MODE(xx_mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	CString mode = xx_mode;
	int retry_action = -1;

	xI_Sync_Ctrl.Thread__LOCK();

LOOP_RETRY:

	// ...
	iActive__CTRL_STS = 1;
	sCH__SCH_IDLE_COUNT->Set__DATA("");

	// ...
	xI_Module_Obj->Enable__ERROR_CHECK__NOT_STANDBY();

	// ...
	{
		CString log_msg;
		CString log_bff;

		CString str__ref_vac;
		CString str__ref_atm;
		CString str__cur_press;

		aEXT_CH_CFG__REF_VAC_PRESSURE->Get__DATA(str__ref_vac);
		aEXT_CH_CFG__REF_ATM_PRESSURE->Get__DATA(str__ref_atm);
		xCH__PRESSURE_VALUE->Get__DATA(str__cur_press);

		log_msg.Format("START : [%s], (%s, %s, %s) ... Called By %s (%s) ...",
					   mode,
					   str__ref_atm,
					   str__ref_vac,
					   str__cur_press,
					   p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME(),
					   sCH__UPPER_OBJ_MSG->Get__STRING());

		//
		CString str__slot_title;
		CString str__slot_status;
		int i;

		log_msg += "\n";

		for(i=0; i<CFG_LBx__SLOT_MAX; i++)
		{
			xCH__SLOT_STATUS[i]->Get__DATA(str__slot_status);
			xCH__SLOT_TITLE[i]->Get__DATA(str__slot_title);

			log_bff.Format("  %1d) [%s][%s]\n",
						   i+1,
						   str__slot_title,
						   str__slot_status);
			log_msg += log_bff;
		}

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	bool active__proc_mode = FALSE;
	CString proc__sch_name = sCH__PARA_PROC_SCH_NAME->Get__STRING();

	if((mode.CompareNoCase(sMODE__PROC_MAIN)  == 0)
	|| (mode.CompareNoCase(sMODE__PROC_PRE)   == 0)
	|| (mode.CompareNoCase(sMODE__PROC_POST)  == 0)
	|| (mode.CompareNoCase(sMODE__PROC_MAINT) == 0))
	{
		if(mode.CompareNoCase(sMODE__PROC_MAINT) != 0)
		{
			active__proc_mode = TRUE;
		}

		// ...
		CString log_msg;
		CString log_bff;

		// ...
		{
			log_msg = "PROC_INFO ... \n";

			log_bff.Format(" * %s <- %s \n", 
						   sCH__PARA_PROC_RECIPE_NAME->Get__CHANNEL_NAME(),
						   sCH__PARA_PROC_RECIPE_NAME->Get__STRING());
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n", 
						   sCH__PARA_PROC_SCH_NAME->Get__CHANNEL_NAME(),
						   sCH__PARA_PROC_SCH_NAME->Get__STRING());
			log_msg += log_bff;
		}

		// ...
		{
			IDS__SCH_MATERIAL_INFO db_info;			
			CString ch_data;

			if(xI_SCH_MATERIAL_CTRL->Get__MATERIAL_INFO(proc__sch_name, db_info) > 0)
			{
				log_bff.Format(" * OK - Material Info. Update ! \n");
				log_msg += log_bff;

				// PORT_ID
				ch_data.Format("%1d", db_info.iSRC__PTN);
				sCH__LLx_LPx_PTN->Set__DATA(ch_data);

				// SLOT_ID
				ch_data.Format("%1d", db_info.iSRC__STN);
				sCH__LLx_LPx_STN->Set__DATA(ch_data);

				// PPID
				ch_data = db_info.sPPID;
				sCH__LLx_PPID->Set__DATA(ch_data);

				// LOTID
				ch_data = db_info.sLOT_ID;
				sCH__LLx_LOTID->Set__DATA(ch_data);

				// MATERIALID
				ch_data = db_info.sMATERIAL_ID;
				sCH__LLx_MATERIALID->Set__DATA(ch_data);
			}
			else
			{
				log_bff.Format(" * ERROR - Material Info. Update ! \n");
				log_msg += log_bff;

				sCH__LLx_LPx_PTN->Set__DATA("");
				sCH__LLx_LPx_STN->Set__DATA("");

				sCH__LLx_PPID->Set__DATA("");
				sCH__LLx_LOTID->Set__DATA("");
				sCH__LLx_MATERIALID->Set__DATA("");
			}

			xI_SCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(proc__sch_name, STR__PROCESSING);
		}
		
		// ...
		{
			log_bff.Format(" * %s <- %s \n", 
						   sCH__LLx_LPx_PTN->Get__CHANNEL_NAME(),
						   sCH__LLx_LPx_PTN->Get__STRING());
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n", 
						   sCH__LLx_LPx_STN->Get__CHANNEL_NAME(),
						   sCH__LLx_LPx_STN->Get__STRING());
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n", 
						   sCH__LLx_PPID->Get__CHANNEL_NAME(),
						   sCH__LLx_PPID->Get__STRING());
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n", 
						   sCH__LLx_LOTID->Get__CHANNEL_NAME(),
						   sCH__LLx_LOTID->Get__STRING());
			log_msg += log_bff;

			log_bff.Format(" * %s <- %s \n", 
						   sCH__LLx_MATERIALID->Get__CHANNEL_NAME(),
						   sCH__LLx_MATERIALID->Get__STRING());
			log_msg += log_bff;
		}

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		CString para__slot_id = dCH__PARA_SLOT_ID->Get__STRING();
		xCH__LBx_SLOT_ID->Set__DATA(para__slot_id);

		// 
		CString log_msg;
		CString log_bff;

		log_msg.Format(" * %s <- %s \n",
						dCH__PARA_SLOT_ID->Get__CHANNEL_NAME(),
						dCH__PARA_SLOT_ID->Get__STRING());

		log_bff.Format(" * %s <- %s \n",
						aCH__PARA_VENT_COOLING_SEC->Get__CHANNEL_NAME(),
						aCH__PARA_VENT_COOLING_SEC->Get__STRING());
		log_msg += log_bff;

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		CString msg;

		msg.Format("%s ...",mode);
		xCH__OBJ_FNC_MSG->Set__DATA(msg);
	}

	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__MAINT)
		{
			flag = Call__MAINT(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__PUMP)
		{
			xCH__PUMPING_FLAG->Set__DATA("YES");
			xCH__PUMPING_COMP_FLAG->Set__DATA("CHECK");

			flag = Call__PUMP(p_variable, p_alarm);

			xCH__PUMPING_FLAG->Set__DATA("");
			xCH__PUMPING_COMP_FLAG->Set__DATA("");
		}
		ELSE_IF__CTRL_MODE(sMODE__VENT)
		{
			xCH__VENTING_FLAG->Set__DATA("YES");
			xCH__VENTING_COMP_FLAG->Set__DATA("CHECK");

			flag = Call__VENT(p_variable, p_alarm);

			xCH__VENTING_FLAG->Set__DATA("");
			xCH__VENTING_COMP_FLAG->Set__DATA("");
		}

		ELSE_IF__CTRL_MODE(sMODE__DOOR_OPEN)		flag = Call__DOOR_OPEN(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__DOOR_CLOSE)		flag = Call__DOOR_CLOSE(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__SLOT_OPEN)		flag = Call__SLOT_OPEN(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SLOT_CLOSE)		flag = Call__SLOT_CLOSE(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PIN_UP)			flag = Call__PIN_UP(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PIN_DOWN)			flag = Call__PIN_DOWN(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PREPMATER)		flag = Call__PREPMATER(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MAP)				flag = Call__MAP(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__COMPMATER)		flag = Call__COMPMATER(p_variable,p_alarm, -1);
		ELSE_IF__CTRL_MODE(sMODE__COMPMATER_EX)		flag = Call__COMPMATER(p_variable,p_alarm,  1);
		ELSE_IF__CTRL_MODE(sMODE__ISOLATE)			flag = Call__ISOLATE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SCH_TEST_CFG)		flag = Call__SCH_TEST_CFG(p_variable,p_alarm);
		
		ELSE_IF__CTRL_MODE(sMODE__PROC_MAIN)		flag = Call__PROC_MAIN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PROC_PRE)			flag = Call__PROC_PRE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PROC_POST)		flag = Call__PROC_POST(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PROC_MAINT)		flag = Call__PROC_MAINT(p_variable, p_alarm);
		
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

	// ...
	CString next_ctrl_req = sCH__NEXT_CTRL_REQ->Get__STRING();

	if(next_ctrl_req.GetLength() > 0)
	{
		sCH__NEXT_CTRL_REQ->Set__DATA("");

		CString log_msg;

		if((flag > 0) && (p_variable->Check__CTRL_ABORT() < 0))
		{
			log_msg.Format(" * Next_Ctrl_Req : [%s] ", next_ctrl_req);
			xI_LOG_CTRL->WRITE__LOG(log_msg);

			printf("[%s] - [%s] \n", sObject_Name,log_msg);
			printf("[%s] - Pre_Mode [%s] \n", sObject_Name,mode);

			if(next_ctrl_req.CompareNoCase("VENTING") == 0)
			{
				log_msg.Format(" ** Start__Next_Ctrl : [%s] ", next_ctrl_req);
				xI_LOG_CTRL->WRITE__LOG(log_msg);
				printf("[%s] - [%s] \n", sObject_Name,log_msg);

				// ...
				{
					xCH__VENTING_FLAG->Set__DATA("YES");
					xCH__VENTING_COMP_FLAG->Set__DATA("CHECK");

					flag = Call__VENT(p_variable,p_alarm);
		
					xCH__VENTING_FLAG->Set__DATA("");
					xCH__VENTING_COMP_FLAG->Set__DATA("");
				}

				if(flag > 0)
					log_msg.Format(" ** Completed__Next_Ctrl : [%s] ", next_ctrl_req);
				else
					log_msg.Format(" ** Aborted__Next_Ctrl : [%s] ", next_ctrl_req);

				xI_LOG_CTRL->WRITE__LOG(log_msg);
				printf("[%s] - [%s] \n", sObject_Name,log_msg);
			}
		}
		else
		{
			log_msg.Format(" * Cleared ... Next_Ctrl_Req : [%s] ", next_ctrl_req);
			xI_LOG_CTRL->WRITE__LOG(log_msg);
		
			printf("[%s] - [%s] \n", sObject_Name,log_msg);		
		}
	}
	else
	{
		CString log_msg;

		if((flag > 0) && (p_variable->Check__CTRL_ABORT() < 0))
		{
			log_msg = " ** Completed !";
		}
		else
		{
			log_msg = " ** Aborted !";
		}

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		CString log_string;

		if(flag > 0)		log_string.Format("COMPLETE : [%s]",mode);
		else				log_string.Format("ABORTED  : [%s]",mode);

		CString log_bff;
		CString str__slot_title;
		CString str__slot_status;
		int i;

		log_string += "\n";

		for(i=0; i<CFG_LBx__SLOT_MAX; i++)
		{
			xCH__SLOT_STATUS[i]->Get__DATA(str__slot_status);
			xCH__SLOT_TITLE[i]->Get__DATA(str__slot_title);

			log_bff.Format("     %1d) [%s][%s]\n",
							i+1,
							str__slot_title,
							str__slot_status);
			log_string += log_bff;
		}

		xI_LOG_CTRL->WRITE__LOG(log_string);
	}

	// ...
	{
		xCH__OBJ_FNC_MSG->Set__DATA("");
		xCH__PRE_MAINT_FLAG->Set__DATA("");

		sCH__UPPER_OBJ_MSG->Set__DATA("");
	}

	sCH__SCH_IDLE_COUNT->Set__DATA("");

	iActive__CTRL_STS = -1;
	iActive__PROC_STS = -1;

	if((active__proc_mode)
	&& (retry_action < 0))
	{
		if((flag > 0) && (p_variable->Check__CTRL_ABORT() < 0))
		{
			int next_proc = xI_SCH_MATERIAL_CTRL->Check__NEXT_PROCESS(proc__sch_name);

			for(int i=0; i< CFG_LBx__SLOT_MAX; i++)
			{
				if(xCH__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
				{
					continue;
				}

				// ...
				CString wfr_sts = STR__COMPLETED;
				if(next_proc > 0)			wfr_sts = STR__PROCESSED;

				xCH__SLOT_STATUS[i]->Set__DATA(wfr_sts);
			}

			xI_SCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(proc__sch_name, STR__PROCESSED);

			if(next_proc < 0)
			{
				if(xCH__PRESSURE_STATUS->Check__DATA("ATM") < 0)
				{
					mode = sMODE__VENT;
					retry_action = 1;

					// ....
					{
						CString log_msg = " * AUTO_VENTING !!!";
						xI_LOG_CTRL->WRITE__LOG(log_msg);
					}
					goto LOOP_RETRY;
				}
			}
		}
		else
		{
			xI_SCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(proc__sch_name, STR__ABORTED);

			for(int i=0; i< CFG_LBx__SLOT_MAX; i++)
			{
				if(xCH__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
				{
					continue;
				}

				// ...
				CString wfr_sts = STR__ABORTED;

				xCH__SLOT_STATUS[i]->Set__DATA(wfr_sts);
			}

			xI_SCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(proc__sch_name, STR__ABORTED);
		}
	}

	aCH__PARA_VENT_COOLING_SEC->Set__VALUE(0.0);
	
	xI_Sync_Ctrl.Thread__UNLOCK();
	return flag;
}
int CObj_Phy__LBx_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__ALL_STATE:
			Mon__All_State(p_variable, p_alarm);
			break;
	}

	return 1;
}
