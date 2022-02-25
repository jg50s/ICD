#include "StdAfx.h"
#include "CObj__DB_CFG.h"
#include "CObj__DB_CFG__ALID.h"


//-------------------------------------------------------------------------
CObj__DB_CFG::CObj__DB_CFG()
{

}
CObj__DB_CFG::~CObj__DB_CFG()
{

}

//-------------------------------------------------------------------------
int CObj__DB_CFG::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	return 1;
}
int CObj__DB_CFG::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define DSP__TRANS_MODE				"ATM  VAC"
#define DSP__PMx_SLOT_MAX			"1  2  3"
#define DSP__PMx_PROC_SLOT_TYPE		"ANY_SLOT  FULL_SLOT"

#define DSP__LBx_MODE_TYPE	        "ALL  ONLY_INPUT  ONLY_OUTPUT"
#define DSP__LBx_SLOT_STATUS		"DISABLE  ENABLE" 
#define DSP__LBx_SLOT_MODE			"INPUT  OUTPUT  ALL"
#define DSP__FNC_MODE				"IDLE  COOLING  PREHEAT"
#define DSP__PRESSURE_CHECK_MODE	"DISABLE  ALARM  RECOVERY  ONLY_RECOVERY"

#define DSP__LLx_SLOT_MAX			"25  26"

#define DSP__LBx_SLOT_MAX			"2  1"
#define LIST__ENABLE_DISABLE		"ENABLE  DISABLE"
#define LIST__DISABLE_ENABLE		"DISABLE  ENABLE"

#define LIST__NO_YES				"NO  YES"

#define APP_DSP__TOOL_CLEAR_MODE			"ALL_MATERIAL  NOT_ERROR_WAFER"
#define APP_DSP__LEAK_CHECK_TIME_MODE		"DATE_TIME  INTERVAL"
#define APP_DSP__AUTO_PM_TIME_MODE		    "DATE_TIME  INTERVAL"

#define APP_DSP__AGVMODE			"MANUAL  AUTO"
#define APP_DSP__ENABLE_DISABLE     "ENABLE  DISABLE"

#define APP_DSP__LBx_IDLE_STATUS	"NONE  ATM  VAC"
#define APP_DSP__CID_FORMAT			"ONLY_TIME  Bypass&ReadFail"

#define APP_DSP__CONCURRENT_ALWAYS_APPLY     "DISABLE  ENABLE  PPID_CHECK"


// ...
#define LINK__VAR(VAR_NAME,CH_NAME)								\
str_name = CH_NAME;												\
VAR_NAME = CH_NAME;


// ...
#define MON_ID__CFG_PORT							1


int CObj__DB_CFG::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	//-----------------------------------------------------------------------------------
	CString dsc_item_list;
	CString str_name;
	CString str_data;
	int i;

	//-----------------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// SYSTEM
	str_name = "SYS.USER.LEVEL";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	LINK__VAR_STRING_CTRL(sCH_SYS__USER_LEVEL,str_name);

	str_name = "SYS.USER.ID";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	LINK__VAR_STRING_CTRL(sCH_SYS__USER_ID,str_name);

	//
	str_name = "SYS.MSG";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	sVAR__SYS_MSG = str_name;

	str_name = "FNC.MSG";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	sVAR__FNC_MSG = str_name;

	//
	LINK__VAR(sVAR_SYS__VAC_AREA__MATERIAL_COUNT,"VAC_AREA.MATERIAL.COUNT");
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");

	LINK__VAR(sVAR_SYS__VAC_ROBOT__OUT_MATERIAL_COUNT,"VAC_ROBOT.OUT_MATERIAL.COUNT");
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");

	LINK__VAR(sVAR_SYS__TOTAL_MATERIAL_COUNT_IN_SYSTEM, "TOTAL.MATERIAL.COUNT.IN.SYSTEM");
	STD__ADD_STRING_WITH_COMMENT(str_name,"");

	//
	LINK__VAR(sVAR_SYS__SYSTEM_LEAK_CHECK_REQ, "SYSTEM.LEAK_CHECK.REQ");
	STD__ADD_STRING_WITH_COMMENT(str_name,"");

	str_name = "SYSTEM.AUTO_PM.REQ";
	STD__ADD_STRING(str_name);

	//
	str_name = "SYS_INFO.TOOL_ID";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH_SYS_INFO__TOOL_ID, str_name);

	str_name = "SYS_INFO.TMC_ID";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH_SYS_INFO__TMC_ID, str_name);

	for(i=0;i<CFG_PM_LIMIT;i++)
	{
		str_name.Format("SYS_INFO.PM%1d_ID",i+1);
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH_SYS_INFO__PMC_ID[i], str_name);
	}

	//
	str_name = "TMC.SYS.MSG";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	sVAR__TMC_SYS_MSG = str_name;

	str_name = "TMC.FNC.MSG";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	sVAR__TMC_FNC_MSG = str_name;

	//
	for(i=0;i<CFG_PM_LIMIT;i++)
	{
		str_name.Format("PM%1d.SYS.MSG",i+1);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		sVAR__PMC_SYS_MSG[i] = str_name;

		str_name.Format("PM%1d.FNC.MSG",i+1);
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		sVAR__PMC_FNC_MSG[i] = str_name;
	}

	// CFG ...
	{
		str_name = "SCH_TEST.CFG.SIM_ALARM_REPORT";
		STD__ADD_DIGITAL(str_name, "YES NO");
		LINK__VAR_DIGITAL_CTRL(dCH__SCH_TEST_CFG_SIM_ALARM_REPORT, str_name);

		//
		str_name = "SCH_TEST.CFG.TMC_DUMMY_BY_CTC";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES","");
		LINK__VAR_DIGITAL_CTRL(dCH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC, str_name);

		//
		for(i=0;i<CFG_PM_LIMIT;i++)
		{
			str_name.Format("SCH_TEST.CFG.PM%1d_DUMMY_BY_CTC", i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES","");
			LINK__VAR_DIGITAL_CTRL(dCH__SCH_TEST_CFG_PMX_DUMMY_BY_CTC[i], str_name);
		}
	}

	// AL1_AL2_USE_MODE
	LINK__VAR(sVAR_CFG__AL1_AL2_CFG_USE_MODE,"AL1_AL2.CFG.USE.MODE");
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"DUAL AL1 AL2","");

	// EQUIPMENT ID	
	LINK__VAR(sVAR_CFG__EQP_ID,"EQUIPMENT.ID");
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");

	// AGVMODEs
	str_name = "AGV.MODE";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__AGVMODE,"");
	LINK__VAR_DIGITAL_CTRL(xCH_CFG__AGVMODE,str_name);

	// TOOL CLEAR
	dVAR_CFG__TOOL_CLEAR__PMC_MATERIAL = "TOOL_CLEAR.PMC_MATERIAL.MODE";
	STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__TOOL_CLEAR__PMC_MATERIAL,APP_DSP__TOOL_CLEAR_MODE,"");

	// ENABLE / DISABLE 
	int pm_id;

	aVAR_CFG__PMx_USE_CNT = "PMx.USE.CNT";
	STD__ADD_ANALOG_WITH_X_OPTION(aVAR_CFG__PMx_USE_CNT,"Num",0,0,CFG_PM_LIMIT,"");

	// PMC ...
	{
		p_variable->Get__STD_DESCRIPTION(DSP__ENABLE_DISABLE,dsc_item_list);

		for(i=0;i<CFG_PM_LIMIT;i++)
		{
			pm_id = i + 1;

			//
			sVAR_CFG__PMx_NAME[i].Format("PM%1d.NAME",pm_id);
			STD__ADD_STRING(sVAR_CFG__PMx_NAME[i]);

			//
			dVAR_CFG__PMx_USE[i].Format("PM%1d.USE",pm_id);
			STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__PMx_USE[i],dsc_item_list,"");

			dVAR_CFG__PMx_SYS_USE_FLAG[i].Format("PM%1d.SYS.USE.FLAG",pm_id);
			STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__PMx_SYS_USE_FLAG[i],"NO YES","");

			dVAR_CFG__PMx_STAGE1_USE[i].Format("PM%1d.STAGE1.USE",pm_id);
			STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__PMx_STAGE1_USE[i],APP_DSP__ENABLE_DISABLE,"");

			dVAR_CFG__PMx_STAGE2_USE[i].Format("PM%1d.STAGE2.USE",pm_id);
			STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__PMx_STAGE2_USE[i],APP_DSP__ENABLE_DISABLE,"");

			//
			dVAR_CFG__PMx_SLOT_MAX[i].Format("PM%1d.SLOT.MAX",pm_id);
			STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__PMx_SLOT_MAX[i],DSP__PMx_SLOT_MAX,"");

			dVAR_CFG__PMx_PROC_SLOT_TYPE[i].Format("PM%1d.PROC_SLOT_TYPE",pm_id);
			STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__PMx_PROC_SLOT_TYPE[i],DSP__PMx_PROC_SLOT_TYPE,"");

			//
			dVAR_CFG__PMx_PROC_TYPE[i].Format("PM%1d.PROCESS.TYPE", pm_id);
			STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__PMx_PROC_TYPE[i],"NORMAL TEST","");

			//
			str_name.Format("PM%1d.CUR.PRE_COUNT", pm_id);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");

			str_name.Format("PM%1d.CUR.POST_COUNT", pm_id);
			STD__ADD_STRING_WITH_COMMENT(str_name, "");
		}
	}

	// PRESSURE REFERENCE ...
	{
		dVAR_CFG__TRANSFER_MODE = "TRANSFER.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__TRANSFER_MODE,DSP__TRANS_MODE,"");

		//
		aVAR_CFG__REF_ATM_PRESSURE = "REF.ATM.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(aVAR_CFG__REF_ATM_PRESSURE,"torr",1,600.0,1000.0,"");

		aVAR_CFG__REF_VAC_PRESSURE = "REF.VAC.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(aVAR_CFG__REF_VAC_PRESSURE,"torr",3,0.0,100.0,"");
	}

	// SCH.STS.ATM_RB_TO_LLx ...
	{
		for(i=0; i<CFG_LLx_LIMIT; i++)
		{
			str_name.Format("SCH.STS.ATM_RB_TO_LL%1d", i+1);
			STD__ADD_STRING(str_name, "");
		}
	}

	// SCH.START_JOB.XXX ...
	{
		str_name = "SCH.START_JOB.LLx_IN.SIZE";
		STD__ADD_STRING(str_name, "");

		str_name = "SCH.START_JOB.LLx_OUT.SIZE";
		STD__ADD_STRING(str_name, "");
	}
	// SCH.MODE.XXX ...
	{
		str_name = "SCH.MODE.LLx_IN";
		STD__ADD_STRING(str_name, "");

		str_name = "SCH.MODE.LLx_OUT";
		STD__ADD_STRING(str_name, "");
	}

	// LLx : CFG & SCH ...
	{
		CString ll_name;

		int ll_limit = CFG_LLx_LIMIT;
		int ll_i;

		for(ll_i = 0; ll_i < ll_limit; ll_i++)
		{
				 if(ll_i == 0)			ll_name  = "LBA";
			else if(ll_i == 1)			ll_name  = "LBB";
			else if(ll_i == 2)			ll_name  = "LBC";
			else if(ll_i == 3)			ll_name  = "LBD";
			else						continue;

			// CFG : LLx ...
			{
				str_name.Format("%s.USE.FLAG", ll_name);
				STD__ADD_DIGITAL_WITH_X_OPTION(str_name, LIST__DISABLE_ENABLE, "");

				str_name.Format("%s.SLOT_MAX", ll_name);
				STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__LBx_SLOT_MAX, "");

				str_name.Format("%s.MODE_TYPE", ll_name);
				STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__LBx_MODE_TYPE, "");

				for(i=0; i<CFG_LLx__SLOT_MAX; i++)
				{
					str_name.Format("%s.SLOT%1d_STATUS", ll_name,i+1);
					STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__LBx_SLOT_STATUS, "");
				}
				for(i=0; i<CFG_LLx__SLOT_MAX; i++)
				{
					str_name.Format("%s.SLOT%1d_MODE", ll_name,i+1);
					STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__LBx_SLOT_MODE, "");
				}

				str_name.Format("%s.FNC_MODE", ll_name);
				STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__FNC_MODE, "");
		
				str_name.Format("%s.JOB_START.READY.RUN.FLAG", ll_name);
				STD__ADD_STRING_WITH_COMMENT(str_name, "");

				str_name.Format("%s.IDLE.STATUS", ll_name);
				STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__LBx_IDLE_STATUS, "");

				//
				str_name.Format("%s.CFG.PREPMATER.USE", ll_name);
				STD__ADD_DIGITAL(str_name, LIST__DISABLE_ENABLE);

				str_name.Format("%s.CFG.COMPMATER.USE", ll_name);
				STD__ADD_DIGITAL(str_name, LIST__DISABLE_ENABLE);

				// PRE_RCP ...
				str_name.Format("%s.PRE_RCP.CFG.USE", ll_name);
				STD__ADD_DIGITAL(str_name, LIST__NO_YES);

				str_name.Format("%s.PRE_RCP.CFG.WAFER_COUNT", ll_name);
				STD__ADD_ANALOG(str_name, "wafer", 0, 0, 100);

				// POST_RCP ...
				str_name.Format("%s.POST_RCP.CFG.USE", ll_name);
				STD__ADD_DIGITAL(str_name, LIST__NO_YES);

				str_name.Format("%s.POST_RCP.CFG.WAFER_COUNT", ll_name);
				STD__ADD_ANALOG(str_name, "wafer", 0, 1, 100);
			}
			// SCH : LLx ...
			{
				str_name.Format("SCH_DB.%s.USE.FLAG", ll_name);
				STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__ENABLE_DISABLE, "");

				str_name.Format("SCH_DB.%s.SLOT_MAX", ll_name);
				STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__LBx_SLOT_MAX, "");

				str_name.Format("SCH_DB.%s.MODE_TYPE", ll_name);
				STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__LBx_MODE_TYPE, "");

				for(i=0; i<CFG_LLx__SLOT_MAX; i++)
				{
					str_name.Format("SCH_DB.%s.SLOT%1d_STATUS", ll_name,i+1);
					STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__LBx_SLOT_STATUS, "");
				}
				for(i=0; i<CFG_LLx__SLOT_MAX; i++)
				{
					str_name.Format("SCH_DB.%s.SLOT%1d_MODE", ll_name,i+1);
					STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__LBx_SLOT_MODE, "");
				}

				str_name.Format("SCH_DB.%s.FNC_MODE", ll_name);
				STD__ADD_DIGITAL_WITH_X_OPTION(str_name, DSP__FNC_MODE, "");

				str_name.Format("SCH_DB.%s.JOB_START.READY.RUN.FLAG", ll_name);
				STD__ADD_STRING_WITH_COMMENT(str_name, "");

				str_name.Format("SCH_DB.%s.IDLE.STATUS", ll_name);
				STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__LBx_IDLE_STATUS, "");

				//
				str_name.Format("SCH.%s.PAUSE.REQ", ll_name);
				STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			}
		}
	}

	// LPx ...
	{
		for(i=0;i<CFG_LP_LIMIT;i++)
		{
			str_name.Format("CFG.LP%1d.GLASS.TYPE",i+1);
			LINK__VAR(dVAR_CFG__LPx_GLASS_TYPE[i],str_name);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"NO  YES","");

			str_name.Format("CFG.LP%1d.JOB_START.FLAG",i+1);
			LINK__VAR(dVAR_CFG__LPx_JOB_START_FLAG[i],str_name);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");

			str_name.Format("LP%1d.MAP.REQ",i+1);
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			sVAR__LPx_MAP_REQ[i] = str_name;
		}

		str_name = "CFG.LPx.MANUAL_TO_AUTO.ALWAYS.APPLY";
		LINK__VAR(dVAR_CFG__LPx_MANUAL_TO_AUTO_ALWAYS_APPLY,str_name);
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,LIST__ENABLE_DISABLE,"");

		str_name = "CFG.LPx.PIO.READY.CHECK.MODE";
		LINK__VAR(dVAR_CFG__LPx_PIO_READY_CHECK_MODE,str_name);
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,LIST__DISABLE_ENABLE,"");

		str_name = "CFG.LPx.JOB_MODE.WITH_UNKNOWN_SLOT";
		LINK__VAR(dVAR_CFG__LPx_JOB_MODE_WITH_UNKNOWN_SLOT,str_name);
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"USE  NOT_USE","");

		str_name = "CFG.LPx.CID.FORMAT";
		LINK__VAR(dVAR_CFG__LPx_CID_FORMAT,str_name);
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__CID_FORMAT,"");
	}

	// STx ...
	{
		str_name = "CFG.BUFFER.JOB.WAIT.MODULE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"LLx LPx" ,"");

		//
		str_name = "CUR.BUFFER.SIZE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
	}

	// CFG_DB : ALx ...
	{
		// AL1
		{
			LINK__VAR(dVAR_CFG__AL1_USE_FLAG,"CFG.AL1.USE.FLAG");
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name,LIST__DISABLE_ENABLE,"");

			LINK__VAR(dVAR_CFG__AL1_SLOT01_USE_FLAG,"CFG.AL1.SLOT01.USE.FLAG");
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name,LIST__DISABLE_ENABLE,"");

			LINK__VAR(dVAR_CFG__AL1_SLOT02_USE_FLAG,"CFG.AL1.SLOT02.USE.FLAG");
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name,LIST__DISABLE_ENABLE,"");
		}
		// AL2
		{
			LINK__VAR(dVAR_CFG__AL2_USE_FLAG,"CFG.AL2.USE.FLAG");
			STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__AL2_USE_FLAG,LIST__DISABLE_ENABLE,"");

			LINK__VAR(dVAR_CFG__AL2_SLOT01_USE_FLAG,"CFG.AL2.SLOT01.USE.FLAG");
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name,LIST__DISABLE_ENABLE,"");

			LINK__VAR(dVAR_CFG__AL2_SLOT02_USE_FLAG,"CFG.AL2.SLOT02.USE.FLAG");
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name,LIST__DISABLE_ENABLE,"");
		}
	}
	// SCH_DB : ALx ...
	{
		// AL1
		{
			str_name = "SCH_DB.CFG.AL1.USE.FLAG";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, LIST__DISABLE_ENABLE, "");

			str_name = "SCH_DB.CFG.AL1.SLOT01.USE.FLAG";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, LIST__DISABLE_ENABLE, "");

			str_name = "SCH_DB.CFG.AL1.SLOT02.USE.FLAG";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, LIST__DISABLE_ENABLE, "");
		}
		// AL2
		{
			str_name = "SCH_DB.CFG.AL2.USE.FLAG";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, LIST__DISABLE_ENABLE, "");

			str_name = "CFG.AL2.SLOT01.USE.FLAG";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, LIST__DISABLE_ENABLE, "");

			str_name = "SCH_DB.CFG.AL2.SLOT02.USE.FLAG";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, LIST__DISABLE_ENABLE, "");
		}
	}

	// JOB START READY - CONTROL ...
	{
		str_name = "CFG.JOB_START_READY.CTRL.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "SYSTEM.IDLE JOB.CHANGE", "");

		for(i=0; i<CFG_PM_LIMIT; i++)
		{
			str_name.Format("CFG.JOB_START_READY.PM%1d.USE", i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, LIST__NO_YES, "");
		}
	}
	// JOB END READY - CONTROL ...
	{
		for(i=0; i<CFG_PM_LIMIT; i++)
		{
			str_name.Format("CFG.JOB_END_READY.PM%1d.USE", i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, LIST__NO_YES, "");
		}
	}

	// SYSTEM IDLE ...
	{
		// ...
		{
			aVAR_CFG__SYSTEM_IDLE_CFG_TIME_SEC = "SYSTEM_IDLE.CFG.TIME.SEC";
			STD__ADD_ANALOG_WITH_X_OPTION(aVAR_CFG__SYSTEM_IDLE_CFG_TIME_SEC, "sec", 0, 0, 9999, "");

			aVAR__SYSTEM_IDLE_CUR_TIME_SEC = "SYSTEM_IDLE.CUR.TIME.SEC";
			STD__ADD_ANALOG(aVAR__SYSTEM_IDLE_CUR_TIME_SEC, "sec", 0, 0, 999999);
		}

		for(i=0; i<CFG_PM_LIMIT; i++)
		{
			dVAR_CFG__SYSTEM_IDLE_CFG_PMx_USE[i].Format("SYSTEM_IDLE.CFG.PM%1d.USE", i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__SYSTEM_IDLE_CFG_PMx_USE[i], LIST__NO_YES, "");

			aVAR_CFG__SYSTEM_IDLE_CFG_PMx_SEC[i].Format("SYSTEM_IDLE.CFG.PM%1d.SEC", i+1);
			STD__ADD_ANALOG_WITH_X_OPTION(aVAR_CFG__SYSTEM_IDLE_CFG_PMx_SEC[i], "sec", 0, 0, 9999, "");
		}
	}

	// PRE_RCP ...
	{
		for(i=0; i<CFG_PM_LIMIT; i++)
		{
			dVAR_CFG__PRE_RCP_CFG_PMx_USE[i].Format("PRE_RCP.CFG.PM%1d.USE", i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__PRE_RCP_CFG_PMx_USE[i], LIST__NO_YES, "");
			
			aVAR_CFG__PRE_RCP_CFG_PMx_WAFER_COUNT[i].Format("PRE_RCP.CFG.PM%1d.WAFER_COUNT", i+1);
			STD__ADD_ANALOG_WITH_X_OPTION(aVAR_CFG__PRE_RCP_CFG_PMx_WAFER_COUNT[i], "wafer", 0, 0, 100, "");
		}
	}
	// POST_RCP ...
	{
		for(i=0; i<CFG_PM_LIMIT; i++)
		{
			str_name.Format("POST_RCP.CFG.PM%1d.USE", i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, LIST__NO_YES, "");

			str_name.Format("POST_RCP.CFG.PM%1d.WAFER_COUNT", i+1);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "wafer", 0, 1, 100, "");
		}
	}

	// ...
	{
		dVAR_CFG__PRESSURE_CHECK_MODE = "PRESSURE_CHECK.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__PRESSURE_CHECK_MODE,DSP__PRESSURE_CHECK_MODE,"");

		//
		sVAR_CFG__PMC_MSG_WIN_CTRL = "PMC_MSG.WIN_CTRL";
		STD__ADD_STRING_WITH_X_OPTION(sVAR_CFG__PMC_MSG_WIN_CTRL,"");

		sVAR_CFG__PMC_MSG_WIN_NAME = "PMC_MSG.WIN_NAME";
		STD__ADD_STRING_WITH_X_OPTION(sVAR_CFG__PMC_MSG_WIN_NAME,"");
	}

	// CYCLE TEST
	{
		sVAR_CFG__CYCLE_MODE_FLAG = "CFG.CYCLE.MODE.FLAG";
		STD__ADD_STRING_WITH_COMMENT(sVAR_CFG__CYCLE_MODE_FLAG,"");

		sVAR_CFG__CYCLE_FOUP_CTRL_MODE = "CFG.CYCLE.FOUP.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(sVAR_CFG__CYCLE_FOUP_CTRL_MODE,"NO_MOVE UNLOAD_RELOAD","");
	}

	// CTC LEAK_CHECK ...
	{
		LINK__VAR(dVAR_CFG__CTC_LEAK_CHECK_USE_FLAG, "CTC.LEAK_CHECK.USE.FLAG");
		STD__ADD_DIGITAL(str_name, "DISABLE ENABLE");
	}
	// LEAK CHECK TIME ...
	{
		LINK__VAR(sVAR__LEAK_CHECK__SCH_SEQUENCE_MODE__REQ_FLAG,"LEAK_CHECK.SCH.SEQUENCE_MODE.REQ_FLAG");
		STD__ADD_STRING(str_name);

		LINK__VAR(dVAR_CFG__LEAK_CHECK_TIME_MODE,"LEAK_CHECK.TIME.MODE");
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__LEAK_CHECK_TIME_MODE,"");

		for(i=0; i<CFG_PM_LIMIT; i++)
		{
			str_name.Format("PM%1d.LEAK_CHECK.FLAG",i+1);
			sVAR_CFG__PMC_LEAK_CHECK_FLAG[i] = str_name;
			STD__ADD_STRING(str_name);
		}
	}
	// IDLE PARA ...
	{
		LINK__VAR(dVAR_CFG__LEAK_CHECK_IDLE_USE_FLAG, "LEAK_CHECK.IDLE.USE.FLAG");
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"DISABLE ENABLE","");

		LINK__VAR(aVAR_CFG__LEAK_CHECK_IDLE_REF_TIME, "LEAK_CHECK.IDLE.REF.TIME");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,36000,"");

		LINK__VAR(aVAR_CFG__LEAK_CHECK_IDLE_CUR_TIME, "LEAK_CHECK.IDLE.CUR.TIME");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,36000,"");

		LINK__VAR(aVAR_CFG__LEAK_CHECK_IDLE_REF_COUNT, "LEAK_CHECK.IDLE.REF.COUNT");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"num",0,0,100,"");

		LINK__VAR(aVAR_CFG__LEAK_CHECK_IDLE_CUR_COUNT, "LEAK_CHECK.IDLE.CUR.COUNT");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"num",0,0,100,"");
	}

	// CTC AUTO_PM ...
	{
		LINK__VAR(dVAR_CFG__CTC_AUTO_PM_USE_FLAG, "CTC.AUTO_PM.USE.FLAG");
		STD__ADD_DIGITAL(str_name, "DISABLE ENABLE");
	}
	// AUTO_PM TIME ...
	{
		LINK__VAR(sVAR__AUTO_PM__SCH_SEQUENCE_MODE__REQ_FLAG,"AUTO_PM.SCH.SEQUENCE_MODE.REQ_FLAG");
		STD__ADD_STRING(str_name);

		LINK__VAR(dVAR_CFG__AUTO_PM_TIME_MODE, "AUTO_PM.TIME.MODE");
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__AUTO_PM_TIME_MODE,"");

		for(i=0; i<CFG_PM_LIMIT; i++)
		{
			str_name.Format("PM%1d.AUTO_PM.FLAG",i+1);
			sVAR_CFG__PMC_AUTO_PM_FLAG[i] = str_name;
			STD__ADD_STRING(str_name);
		}
	}
	// IDLE PARA ...
	{
		LINK__VAR(dVAR_CFG__AUTO_PM_IDLE_USE_FLAG, "AUTO_PM.IDLE.USE.FLAG");
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"DISABLE ENABLE","");

		LINK__VAR(aVAR_CFG__AUTO_PM_IDLE_REF_TIME, "AUTO_PM.IDLE.REF.TIME");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,36000,"");

		LINK__VAR(aVAR_CFG__AUTO_PM_IDLE_CUR_TIME, "AUTO_PM.IDLE.CUR.TIME");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,36000,"");

		LINK__VAR(aVAR_CFG__AUTO_PM_IDLE_REF_COUNT, "AUTO_PM.IDLE.REF.COUNT");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"num",0,0,100,"");

		LINK__VAR(aVAR_CFG__AUTO_PM_IDLE_CUR_COUNT, "AUTO_PM.IDLE.CUR.COUNT");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"num",0,0,100,"");
	}

	// HANDSHAKE PROTOCOL - USE CONFIG
	{
		// LBx
		dVAR_CFG__LBx_PREPMATER_USE = "CFG.LBx.PREPMATER.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__LBx_PREPMATER_USE,LIST__ENABLE_DISABLE,"");

		dVAR_CFG__LBx_COMPMATER_USE = "CFG.LBx.COMPMATER.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__LBx_COMPMATER_USE,LIST__ENABLE_DISABLE,"");

		// PMx
		dVAR_CFG__PMx_PICK_READY_USE = "CFG.PMx.PICK_READY.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__PMx_PICK_READY_USE,LIST__ENABLE_DISABLE,"");

		dVAR_CFG__PMx_PICK_COMPLETE_USE = "CFG.PMx.PICK_COMPLETE.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__PMx_PICK_COMPLETE_USE,LIST__ENABLE_DISABLE,"");

		dVAR_CFG__PMx_PLACE_READY_USE = "CFG.PMx.PLACE_READY.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__PMx_PLACE_READY_USE,LIST__ENABLE_DISABLE,"");

		dVAR_CFG__PMx_PLACE_COMPLETE_USE = "CFG.PMx.PLACE_COMPLETE.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(dVAR_CFG__PMx_PLACE_COMPLETE_USE,LIST__ENABLE_DISABLE,"");
	}

	// DUMMY CLEAN RECIPE
	{
		str_name = "CFG.DUMMY.CLEAN.USE.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,LIST__DISABLE_ENABLE,"");
		aVAR_CFG__DUMMY_CLEAN_USE_FLAG = str_name;

		str_name = "CFG.DUMMY.CLEAN.SYSTEM.IDLE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,9999,"");
		aVAR_CFG__DUMMY_CLEAN_SYSTEM_IDLE_TIME = str_name;

		str_name = "DUMMY.CLEAN.SYSTEM.IDLE.TIME.COUNT";
		STD__ADD_ANALOG(str_name,"sec",0,0,9999);
		aVAR__DUMMY_CLEAN_SYSTEM_IDLE_TIME_COUNT = str_name;

		str_name = "CFG.DUMMY.CLEAN.WAFER.PER.PMC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,1,1,"");
		aVAR_CFG__DUMMY_CLEAN_WAFER_PER_PMC = str_name;

		for(i=0; i<CFG_LP__SLOT_MAX; i++)
		{
			str_name.Format("APP.DUMMY_PORT.CUR_COUNT.SLOT%1d", i+1);
			STD__ADD_STRING(str_name);
			sVAR__APP_DUMMY_PORT_CUR_COUNT_SLOTx[i] = str_name;
		}
	}

	// SCHEDULER PARAMETER
	{
		str_name = "SCH.CONCURRENT.ALWAYS.APPLY";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__CONCURRENT_ALWAYS_APPLY,"");
		sVAR__SCH_CONCURRENT_ALWAYS_APPLY == str_name;

		//
		str_name = "SCH.LBx.MATERIAL.OUT.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		sVAR__SCH_LBx_MATERIAL_OUT_REQ = str_name;

		str_name = "SCH.LBx.EMPTY.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		sVAR__SCH_LBx_EMPTY_REQ = str_name;

		str_name = "SCH.LBx.VERTICAL.PLACE.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"DISABLE ENABLE","");
		sVAR__SCH_LBx_VERTICAL_PLACE_MODE = str_name;

		// 
		str_name = "SCH.MAP.DEVICE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"LP ATM_RB ROBOT.MANUAL","");
		sVAR__SCH_MAP_DEVICE = str_name;

		str_name = "SCH.ALIGN.DEVICE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"AL ATM_RB","");
		sVAR__SCH_ALIGN_DEVICE = str_name;

		str_name = "SCH.POST.ALIGN.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"DISABLE ENABLE","");
		sVAR__SCH_POST_ALIGN_MODE = str_name;

		// 
		str_name = "SCH.WAC.WAFER.POSITION";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"PMx LLx CENTER","");
		sVAR__SCH_WAC_WAFER_POSITION = str_name;

		str_name = "SCH.WAC.WAFER.APPLY";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		sVAR__SCH_WAC_WAFER_APPLY = str_name;

		str_name = "SCH.WAC.WAFER.DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,3,"");
		aVAR__SCH_WAC_WAFER_DELAY_SEC = str_name;

		str_name = "SCH.WAC.WAFER.DELAY.COUNT";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		sVAR__SCH_WAC_WAFER_DELAY_COUNT = str_name;

		for(i=0; i<CFG_LP_LIMIT; i++)
		{
			str_name.Format("SCH.LP_JOB_LIST.%1d", i+1);
			STD__ADD_STRING(str_name);
			sVAR__SCH_LP_JOB_LIST[i] = str_name;
		}
	}

	// SYSTEM INFO
	{
		str_name = "ANI.PRESSURE_STATUS.ATM";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		sVAR__ANI_PRESSURE_STATUS__ATM = str_name;
	}

	// ...
	{
		str_name = "UI.MEMORY.USAGE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__UI_MEMORY_USAGE,str_name);

		str_name = "CFG.LPx.ACCESS_MODE.AUTO_CTRL.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE ENABLE","");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_LPx_ACCESS_MODE_AUTO_CTRL_FLAG, str_name);
	}

	// ...
	{
		str_name = "TEST.RANGE.MINUS";
		STD__ADD_ANALOG(str_name, "value", 3, -1000, 1000);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__CFG_PORT);
	}
	return 1;
}

int CObj__DB_CFG::__DEFINE__ALARM(p_alarm)
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
	int i;

	// ...
	{
		alarm_id = ALID__SIMULATION_MODE_ACTIVE;

		alarm_title  = title;
		alarm_title += "Simulation mode is active !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__SIMULATION_TMC_DUMMY_MODE_ACTIVE;

		alarm_title  = title;
		alarm_title += "TMC-Dummy mode is active !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	for(i=0; i<CFG_PM_LIMIT; i++)
	{
		alarm_id = ALID__SIMULATION_PMX_DUMMY_MODE_ACTIVE + i;

		alarm_title  = title;
		alarm_bff.Format("PM%1d-Dummy mode is active !", i+1);
		alarm_title += alarm_bff;

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


//-------------------------------------------------------------------------
int CObj__DB_CFG::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// ...
	{
		sCH_SYS__USER_LEVEL->Set__DATA("UNKNOWN");

		p_variable->Set__VARIABLE_DATA(sVAR__ANI_PRESSURE_STATUS__ATM,"ATM");
	}

	// ...
	{
		CString var_data;

		sCH__UI_MEMORY_USAGE->Get__DATA(var_data);
		if(var_data.GetLength() < 1)
		{
			sCH__UI_MEMORY_USAGE->Set__DATA("1200");
		}
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__DB_CFG::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{

	return 1;
}
int CObj__DB_CFG::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__CFG_PORT:
			Mon__INFO_REPORT(p_alarm);
			break;
	}

	return 1;
}
