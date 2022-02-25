#include "StdAfx.h"
#include "CObj_Opr__MAINT_MODE.h"


//-------------------------------------------------------------------------
CObj_Opr__MAINT_MODE::CObj_Opr__MAINT_MODE()
{

}
CObj_Opr__MAINT_MODE::~CObj_Opr__MAINT_MODE()
{

}

//-------------------------------------------------------------------------
int CObj_Opr__MAINT_MODE::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	// ...
	{
		sObject_Name = obj;
	}

	// ...
	{
		ADD__CTRL_VAR(sMODE__MANUAL_MOVE,    "MANUAL_MOVE");
		ADD__CTRL_VAR(sMODE__TOOL_CLEAR,     "TOOL_CLEAR" );
		ADD__CTRL_VAR(sMODE__PARTICLE_CHECK, "PARTICLE_CHECK");
		ADD__CTRL_VAR(sMODE__MACRO_MOVE,	 "MACRO_MOVE");
	}
	return 1;
}

int CObj_Opr__MAINT_MODE::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__MACRO_MOVE_CTRL				1

// ...
#define APP_DSP__TRG_MODULE					\
"ATM_RB-A									\
AL1											\
BUFFER1-1									\
BUFFER1-11									\
BUFFER1-25									\
BUFFER2-1									\
BUFFER2-11									\
BUFFER2-25									\
VAC_RB-A  VAC_RB-B							\
PM1-1										\
PM2-1										\
PM3-1										\
PM4-1										\
PM5-1										\
PM6-1"


int CObj_Opr__MAINT_MODE::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CString str_name;
	CString str_list;
	int i;

	// LLx_SIZE ...
	{
		CString def_name;
		CString def_data;

		def_name = "LLx_SIZE";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);

		iLLx_SIZE = atoi(def_data);
		if(iLLx_SIZE > CFG_LLx_LIMIT)			iLLx_SIZE = CFG_LLx_LIMIT;
	}

	// ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__OBJ_MSG,str_name);

		str_name = "ACTIVE.MODE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(xCH__ACTIVE_MODE,str_name);
	}

	// PARTICLE PARAMETER .....
	{
		str_name = "PARTICLE.PARA.SELECT_MODE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__PARTICLE_PARA_SELECT_MODE,str_name);

		//
		str_name = "PARTICLE.PARA.SRC_MODULE";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__PARTICLE_PARA_SRC_MODULE,str_name);

		str_name = "PARTICLE.PARA.SRC_SLOT";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__PARTICLE_PARA_SRC_SLOT,str_name);

		//
		str_list = APP_DSP__TRG_MODULE;

		for(i=0; i<iLLx_SIZE; i++)
		{
			CString ll_name;

			ll_name.Format(" LL%1d-1", i+1);
			str_list += ll_name;

			ll_name.Format(" LL%1d-2", i+1);
			str_list += ll_name;
		}

		str_name = "PARTICLE.PARA.TRG_MODULE";	
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, str_list,"");
		LINK__VAR_DIGITAL_CTRL(dCH__PARTICLE_PARA_TRG_MODULE,str_name);

		//
		str_name = "PARTICLE.PARA.DELAY_TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARTICLE_PARA_DELAY_TIME,str_name);

		str_name = "PARTICLE.PARA.DELAY_COUNT";
		STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",0,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARTICLE_PARA_DELAY_COUNT,str_name);
	}

	// PARTICLE TEST ...
	{
		str_name = "PARTICLE.PARA.PRC.APPLY";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE ENABLE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__PARTICLE_PARA_PRC_APPLY, str_name);

		str_name = "PARTICLE.DATA.PRC.APPLY";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARTICLE_DATA_PRC_APPLY, str_name);

		//
		str_name = "PARTICLE.PROCESS.PMx";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "PM1 PM2 PM3 PM4 PM5 PM6  LL1 LL2 LL3 LL4", "");
		LINK__VAR_DIGITAL_CTRL(dCH__PARTICLE__PROCESS_PMx, str_name);

		for(i=0; i<CFG_PM_LIMIT; i++)
		{
			str_name.Format("PARTICLE.PARA.PM%1d.RECIPE", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__PARTICLE_PARA_PMx_RECIPE[i], str_name);

			str_name.Format("PARTICLE.PARA.PM%1d.RCP_CLN", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__PARTICLE_PARA_PMx_RCP_CLN[i], str_name);

			str_name.Format("PARTICLE.PARA.PM%1d.RCP_PRE", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__PARTICLE_PARA_PMx_RCP_PRE[i], str_name);
		}
		for(i=0; i<CFG_LLx_LIMIT; i++)
		{
			str_name.Format("PARTICLE.PARA.LL%1d.RECIPE", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__PARTICLE_PARA_LLx_RECIPE[i], str_name);

			str_name.Format("PARTICLE.PARA.LL%1d.RCP_CLN", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__PARTICLE_PARA_LLx_RCP_CLN[i], str_name);

			str_name.Format("PARTICLE.PARA.LL%1d.RCP_PRE", i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__PARTICLE_PARA_LLx_RCP_PRE[i], str_name);
		}

		//
		/*
		str_name = "PARTICLE.PARA.CYCLE.MODULE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "PM1-1 PM2-1 PM3-1 PM4-1 PM5-1 PM6-1  LL1-1 LL2-1 LL3-1 LL4-1", "");
		LINK__VAR_DIGITAL_CTRL(dCH__PARTICLE_PARA_CYCLE_MODULE, str_name);
		*/

		str_name = "PARTICLE.DATA.CYCLE.MODULE";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARTICLE_DATA_CYCLE_MODULE, str_name);

		//
		str_name = "PARTICLE.PARA.CYCLE.COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "count", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARTICLE_PARA_CYCLE_COUNT, str_name);

		str_name = "PARTICLE.DATA.CYCLE.COUNT";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARTICLE_DATA_CYCLE_COUNT, str_name);

		//
		str_name = "PARTICLE.PARA.VAC_ROBOT.CFG.TIME.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARTICLE_PARA_VAC_ROBOT_CFG_TIME_SEC, str_name);
		
		str_name = "PARTICLE.PARA.VAC_ROBOT.CUR.TIME.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARTICLE_PARA_VAC_ROBOT_CUR_TIME_COUNT, str_name);
	}

	// MACRO MOVE ...
	{
		str_name = "MACRO_MOVE.LOG_STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__LOG_STATUS,str_name);

		str_name = "MACRO_MOVE.CYCLE_COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"count",0,1,1000,"");
		LINK__VAR_ANALOG_CTRL(aCH__MACRO_MOVE__CYCLE_COUNT,str_name)

			str_name = "MACRO_MOVE.CUR_CYCLE_COUNT";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__CUR_CYCLE_COUNT,str_name);

		str_name = "MACRO_MOVE.LOG_VIEW.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__LOG_VIEW_REQ,str_name);

		str_name = "MACRO_MOVE.LOG_SAVE.REQ";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__LOG_SAVE_REQ,str_name);

		str_name = "MACRO_MOVE.LOG.FILE_NAME";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__LOG_FILE_NAME,str_name);

		// ...
		int i;

		// ...
		{
			for(i=0;i<CFG_SIZE__MOVE_HISTORY;i++)
			{
				str_name.Format("MACRO_MOVE.HISTORY.%1d", i+1);
				STD__ADD_STRING_WITH_COMMENT(str_name,"");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__HISTORY[i],str_name);
			}

			//
			str_name = "MACRO_MOVE.LOG_COUNT";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__LOG_COUNT,str_name);

			//
			str_name = "MACRO_MOVE.SCR_NAME";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__SCR_NAME,str_name);

			//
			str_name = "MACRO_MOVE.CFG.FOUP_WAIT_SEC";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,1000,"");
			LINK__VAR_ANALOG_CTRL(aCH__MACRO_MOVE__CFG_FOUP_WAIT_SEC,str_name);

			str_name = "MACRO_MOVE.FOUP_WAIT_CUR_SEC";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__FOUP_WAIT_CUR_SEC,str_name);

			//
			str_name = "MACRO_MOVE.CFG.PMC_WAIT_SEC";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,1000,"");
			LINK__VAR_ANALOG_CTRL(aCH__MACRO_MOVE__CFG_PMC_WAIT_SEC,str_name);

			str_name = "MACRO_MOVE.PMC_WAIT_CUR_SEC";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__PMC_WAIT_CUR_SEC,str_name);

			//
			str_name = "MACRO_MOVE.CFG.BUFFER_WAIT_SEC";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,1000,"");
			LINK__VAR_ANALOG_CTRL(aCH__MACRO_MOVE__CFG_BUFFER_WAIT_SEC,str_name);

			str_name = "MACRO_MOVE.BUFFER_WAIT_CUR_SEC";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__BUFFER_WAIT_CUR_SEC,str_name);

			//
			str_name = "MACRO_MOVE.ATM_RB.MOVE_POS.CENTER";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__ATM_RB_MOVE_POS__CENTER,str_name);

			str_name = "MACRO_MOVE.ATM_RB.ARM_ACT.RETRACT";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__ATM_RB_ARM_ACT__RETRACT,str_name);	

			//
			str_name = "MACRO_MOVE.VAC_RB.ARM_TYPE.A";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__VAC_RB_ARM_TYPE__A,str_name);

			str_name = "MACRO_MOVE.VAC_RB.ROT_POS.CENTER";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__VAC_RB_ROT_POS__CENTER,str_name);

			str_name = "MACRO_MOVE.VAC_RB.ARM_ACT.RETRACT";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__VAC_RB_ARM_ACT__RETRACT,str_name);
		}

		// Editor ...
		{
			for(i=0;i<CFG_SIZE__MOVE_HISTORY;i++)
			{
				str_name.Format("MACRO_MOVE.EDITOR.ACTION_NAME.%1d", i+1);
				STD__ADD_STRING_WITH_COMMENT(str_name,"");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__EDITOR_ACTION_NAME[i],str_name);
			}

			//
			str_name = "MACRO_MOVE.EDITOR.CUR_INDEX";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__EDITOR_CUR_INDEX,str_name);

			//
			str_name = "MACRO_MOVE.EDITOR.CHANGE_FLAG";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__EDITOR_CHANGE_FLAG,str_name);
		}

		// ...
		{
			//
			str_name = "MACRO_MOVE.MOVE.SELECT";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__MOVE_SELECT,str_name);

			str_name = "MACRO_MOVE.SRC.SLOT";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__SRC_SLOT,str_name);

			str_name = "MACRO_MOVE.SRC.MODULE";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__SRC_MODULE,str_name);

			str_name = "MACRO_MOVE.TRG.SLOT";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__TRG_SLOT,str_name);

			str_name = "MACRO_MOVE.TRG.MODULE";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__TRG_MODULE,str_name);

			//
			str_name = "MACRO_MOVE.LOOP.START";
			STD__ADD_ANALOG(str_name, "No.", 0, 0, 20);
			LINK__VAR_ANALOG_CTRL(aCH__MACRO_MOVE__LOOP_START, str_name);

			str_name = "MACRO_MOVE.LOOP.END";
			STD__ADD_ANALOG(str_name, "No.", 0, 0, 20);
			LINK__VAR_ANALOG_CTRL(aCH__MACRO_MOVE__LOOP_END, str_name);

			str_name = "MACRO_MOVE.LOOP.REPEAT";
			STD__ADD_ANALOG(str_name, "Count", 0, 0, 100);
			LINK__VAR_ANALOG_CTRL(aCH__MACRO_MOVE__LOOP_REPEAT, str_name);

			//
			str_name = "MACRO_MOVE.STEP.REPEAT.START";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__STEP_REPEAT_START, str_name);

			str_name = "MACRO_MOVE.STEP.REPEAT.END";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__STEP_REPEAT_END, str_name);

			str_name = "MACRO_MOVE.STEP.REPEAT.COUNT";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__STEP_REPEAT_COUNT, str_name);

			str_name = "MACRO_MOVE.STEP.REPEAT.INDEX";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__STEP_REPEAT_INDEX, str_name);

			//
			str_name = "MACRO_MOVE.PROCESS.ROUTE";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__PROCESS_ROUTE, str_name);

			str_name = "MACRO_MOVE.PROCESS.PMx";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "PM1 PM2 PM3 PM4 PM5 PM6  LL1 LL2 LL3 LL4", "");
			LINK__VAR_DIGITAL_CTRL(dCH__MACRO_MOVE__PROCESS_PMx, str_name);

			for(i=0; i<CFG_PM_LIMIT; i++)
			{
				int id = i + 1;

				str_name.Format("MACRO_MOVE.PROCESS.PRE_RECIPE.PM%1d", id);
				STD__ADD_STRING_WITH_X_OPTION(str_name, "");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__PROCESS_PRE_RECIPE_PMx[i], str_name);

				str_name.Format("MACRO_MOVE.PROCESS.MAIN_RECIPE.PM%1d", id);
				STD__ADD_STRING_WITH_X_OPTION(str_name, "");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__PROCESS_MAIN_RECIPE_PMx[i], str_name);

				str_name.Format("MACRO_MOVE.PROCESS.POST_RECIPE.PM%1d", id);
				STD__ADD_STRING_WITH_X_OPTION(str_name, "");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__PROCESS_POST_RECIPE_PMx[i], str_name);
			}
			for(i=0; i<CFG_LLx_LIMIT; i++)
			{
				int id = i + 1;

				str_name.Format("MACRO_MOVE.PROCESS.PRE_RECIPE.LL%1d", id);
				STD__ADD_STRING_WITH_X_OPTION(str_name, "");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__PROCESS_PRE_RECIPE_LLx[i], str_name);

				str_name.Format("MACRO_MOVE.PROCESS.MAIN_RECIPE.LL%1d", id);
				STD__ADD_STRING_WITH_X_OPTION(str_name, "");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__PROCESS_MAIN_RECIPE_LLx[i], str_name);

				str_name.Format("MACRO_MOVE.PROCESS.POST_RECIPE.LL%1d", id);
				STD__ADD_STRING_WITH_X_OPTION(str_name, "");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__PROCESS_POST_RECIPE_LLx[i], str_name);
			}

			//
			str_name = "MACRO_MOVE.OBJ_STATUS.STANDBY";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__OBJ_STATUS__STANDBY,str_name);

			str_name = "MACRO_MOVE.PRESSURE_STATUS.VAC";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__PRESSURE_STATUS__VAC,str_name);

			str_name = "MACRO_MOVE.DOOR_STATUS.CLOSE";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__DOOR_STATUS__CLOSE,str_name);

			str_name = "MACRO_MOVE.DOOR_STATUS.OPEN";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__DOOR_STATUS__OPEN,str_name);

			str_name = "MACRO_MOVE.CST_STATUS.EXIST";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__CST_STATUS__EXIST,str_name);

			str_name = "MACRO_MOVE.CST_POS.LOAD";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__CST_POS__LOAD,str_name);

			//
			str_name = "MACRO_MOVE.EDITOR.ACT_CMMD";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__EDITOR_ACT_CMMD,str_name);

			str_name = "MACRO_MOVE.FILE.ACT_CMMD";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__FILE_ACT_CMMD,str_name);

			str_name = "MACRO_MOVE.FILE_NAME";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__FILE_NAME,str_name);

			//
			str_name = "MACRO_MOVE.ACTION_SELECT";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__ACTION_SELECT,str_name);

			//
			for(i=0; i<CFG_PM_LIMIT; i++)
			{
				str_name.Format("PM%1d.SLOT_STATUS", i+1);
				STD__ADD_STRING_WITH_COMMENT(str_name,"");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__PMC_SLOT_STATUS[i],str_name);

				str_name.Format("PM%1d.SLOT_TITLE", i+1);
				STD__ADD_STRING_WITH_COMMENT(str_name,"");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__PMC_SLOT_TITLE[i],str_name);
			}

			//
			str_name = "VAC_RB.A_ARM.SLOT_STATUS";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__VAC_RB__A_ARM_SLOT_STATUS,str_name);

			str_name = "VAC_RB.A_ARM.SLOT_TITLE";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__VAC_RB__A_ARM_SLOT_TITLE,str_name);

			str_name = "VAC_RB.B_ARM.SLOT_STATUS";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__VAC_RB__B_ARM_SLOT_STATUS,str_name);

			str_name = "VAC_RB.B_ARM.SLOT_TITLE";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__VAC_RB__B_ARM_SLOT_TITLE,str_name);

			//
			str_name = "ATM_RB.A_ARM.SLOT_STATUS";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__ATM_RB__A_ARM_SLOT_STATUS,str_name);

			str_name = "ATM_RB.A_ARM.SLOT_TITLE";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__ATM_RB__A_ARM_SLOT_TITLE,str_name);

			//
			str_name = "ATM_RB.B_ARM.SLOT_STATUS";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__ATM_RB__B_ARM_SLOT_STATUS,str_name);

			str_name = "ATM_RB.B_ARM.SLOT_TITLE";
			STD__ADD_STRING_WITH_COMMENT(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__ATM_RB__B_ARM_SLOT_TITLE,str_name);

			// LLx ...
			{
				for(int ll_i=0; ll_i<CFG_LLx_LIMIT; ll_i++)
				{
					CString ll_name = STR__LLx;

						 if(ll_i == 0)			ll_name = STR__LBA;
					else if(ll_i == 1)			ll_name = STR__LBB;
					else if(ll_i == 2)			ll_name = STR__LBC;
					else if(ll_i == 3)			ll_name = STR__LBD;
					else						continue;

					for(i=0; i<CFG_LLx__SLOT_MAX; i++)
					{
						str_name.Format("%s.SLOT%1d_STATUS", ll_name,i+1);
						STD__ADD_STRING_WITH_COMMENT(str_name,"");
						LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__LLx_SLOT_STATUS[ll_i][i],str_name);

						str_name.Format("%s.SLOT%1d_TITLE", ll_name,i+1);
						STD__ADD_STRING_WITH_COMMENT(str_name,"");
						LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__LLx_SLOT_TITLE[ll_i][i],str_name);
					}
				}
			}

			//
			for(i=0; i<CFG_AL__SLOT_MAX; i++)
			{
				str_name.Format("AL.SLOT_STATUS.%1d", i+1);
				STD__ADD_STRING_WITH_COMMENT(str_name, "");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__AL_SLOT_STATUS[i], str_name);

				str_name.Format("AL.SLOT_TITLE.%1d", i+1);
				STD__ADD_STRING_WITH_COMMENT(str_name, "");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__AL_SLOT_TITLE[i], str_name);
			}

			//
			for(i=0; i<CFG_BUFFER__SLOT_MAX; i++)
			{
				//
				str_name.Format("BUFFER1.SLOT%1d_STATUS", i+1);
				STD__ADD_STRING_WITH_COMMENT(str_name,"");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__BUFFER1_SLOT_STATUS[i],str_name);

				str_name.Format("BUFFER1.SLOT%1d_TITLE", i+1);
				STD__ADD_STRING_WITH_COMMENT(str_name,"");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__BUFFER1_SLOT_TITLE[i],str_name);

				//
				str_name.Format("BUFFER2.SLOT%1d_STATUS", i+1);
				STD__ADD_STRING_WITH_COMMENT(str_name,"");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__BUFFER2_SLOT_STATUS[i],str_name);

				str_name.Format("BUFFER2.SLOT%1d_TITLE", i+1);
				STD__ADD_STRING_WITH_COMMENT(str_name,"");
				LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__BUFFER2_SLOT_TITLE[i],str_name);
			}

			//
			for(i=0; i<CFG_LP_LIMIT; i++)
			{
				for(int j=0; j<CFG_LP__SLOT_MAX; j++)
				{
					str_name.Format("LP%1d.SLOT%1d_STATUS", i+1,j+1);
					STD__ADD_STRING_WITH_COMMENT(str_name,"");
					LINK__VAR_STRING_CTRL(sCH__MACRO_MOVE__LPx_SLOT_STATUS[i][j],str_name);
				}
			}
		}
	}

	// MOVE PARAMETER .....
	{
		sVAR_PARA__MOVE_SELECT = "PARA.MOVE.SELECT";
		STD__ADD_STRING_WITH_COMMENT(sVAR_PARA__MOVE_SELECT, "");

		//
		str_name = "PARA.SRC.MODULE";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_SRC_MODULE,str_name);

		str_name = "PARA.SRC.SLOT";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_SRC_SLOT,str_name);

		//
		str_name = "PARA.TRG.MODULE";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_TRG_MODULE,str_name);

		str_name = "PARA.TRG.SLOT";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_TRG_SLOT,str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__MACRO_MOVE_CTRL);
	}
	return 1;
}

int CObj_Opr__MAINT_MODE::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s [CObj_Opr__MAINT_MODE] : ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// ...
	{
		alarm_title  = title;
		alarm_title += "OBJECT MODE : UNKNOWN";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add("ABORT");

		ADD__ALARM_EX(ALID__OBJECT_MODE_UNKNOWN,alarm_title,alarm_msg,l_act);
	}
	return 1;
}

int CObj_Opr__MAINT_MODE::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	// ...
	{

	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj_Opr__MAINT_MODE::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// ...
	{
		sCH__PARTICLE_PARA_SELECT_MODE->Set__DATA("SOURCE");
		p_variable->Set__VARIABLE_DATA(sVAR_PARA__MOVE_SELECT,"SOURCE");
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.Log", sObject_Name);

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
		CString def_name;
		CString def_data;
		CString ch_name;
		CString obj_name;
		CString var_name;

		// ...
		{
			def_name = "CH__TARGET_LLx_NAME";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__TARGET_LLx_NAME, obj_name,var_name);

			def_name = "CH__TARGET_LLx_SLOT";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__TARGET_LLx_SLOT, obj_name,var_name);
		}

		// LPx INFO ...
		{
			// LPx SIZE ...
			{
				def_name = "LP_SIZE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

				iLPx_SIZE = atoi(def_data);
				if(iLPx_SIZE > CFG_LP_LIMIT)		iLPx_SIZE = CFG_LP_LIMIT;
			}

			// LPx_OBJ ...
			{
				int i;

				for(i=0; i<iLPx_SIZE; i++)
				{
					def_name.Format("OBJ__LP%1d", i+1);
					p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

					//
					var_name = "APP.LOCK.FLAG";
					LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LPx_LOCK_FLAG[i], obj_name,var_name);
				}
			}
		}

		// ATM RB - OBJ ...
		{
			def_name = "OBJ__ATM_RB";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pATM_RB__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "CHECK.MODULE";	
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ATM_RB__CHECK_MODULE, obj_name,var_name);

			var_name = "CFG.BUFFER.USE_DURING_MAINT_MODE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ATM_RB__CFG_BUFFER_USE_DURING_MAINT_MODE, obj_name,var_name);
		}

		// VAC_RB - OBJ ...
		{
			def_name = "OBJ__VAC_RB";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pVAC_RB__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "CHECK.MODULE";	
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__VAC_RB__CHECK_MODULE, obj_name,var_name);
		}

		// PMx INFO ...
		{
			// PMx_UNIT_SIZE ...
			{
				def_name = "PMx_UNIT_SIZE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

				iPMx_SIZE = atoi(def_data);
				if(iPMx_SIZE > CFG_PM_LIMIT)		iPMx_SIZE = CFG_PM_LIMIT;
			}

			// PMx_OBJ ...
			{
				int i;

				for(i=0; i<CFG_PM_LIMIT; i++)
				{
					pPMx__OBJ_CTRL[i] = NULL;
				}
				for(i=0; i<iPMx_SIZE; i++)
				{
					def_name.Format("OBJ__PM%1d", i+1);
					p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

					pPMx__OBJ_CTRL[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
				}
			}
		}

		// LLx INFO ...
		{
			// LLx_SIZE ...
			{
				def_name = "LLx_SIZE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

				iLLx_SIZE = atoi(def_data);
				if(iLLx_SIZE > CFG_LLx_LIMIT)			iLLx_SIZE = CFG_LLx_LIMIT;
			}

			// LLx_OBJ ...
			{
				int i;

				for(i=0; i<CFG_LLx_LIMIT; i++)
				{
					pLLx__OBJ_CTRL[i] = NULL;
				}
				for(i=0; i<iLLx_SIZE; i++)
				{
					def_name.Format("OBJ__LL%1d", i+1);
					p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

					pLLx__OBJ_CTRL[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

					//
					var_name = "PARA.PROC.RECIPE.NAME";
					LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LLx_PARA_PROC_RECIPE_NAME[i], obj_name,var_name);

					var_name = "PARA.PROC.SCH.NAME";
					LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LLx_PARA_PROC_SCH_NAME[i], obj_name,var_name);
				}
			}
		}
	}

	// ...
	{
		CString str_module;

		// ...
		{
			sList__ATM_AREA.RemoveAll();
			sList__ATM_RB_AREA.RemoveAll();
			sList__LPx_AREA.RemoveAll();
			sList__ALx_AREA.RemoveAll();
			sList__BUFFx_AREA.RemoveAll();
			sList__VISx_AREA.RemoveAll();
			sList__LBx_AREA.RemoveAll();

			//
			str_module = "ATM_RB1_A";
			sList__ATM_AREA.Add(str_module);
			sList__ATM_RB_AREA.Add(str_module);

			str_module = "ATM_RB1_B";
			sList__ATM_AREA.Add(str_module);
			sList__ATM_RB_AREA.Add(str_module);

			//
			str_module = "LP1";
			sList__ATM_AREA.Add(str_module);
			sList__LPx_AREA.Add(str_module);

			str_module = "LP2";
			sList__ATM_AREA.Add(str_module);
			sList__LPx_AREA.Add(str_module);

			str_module = "LP3";
			sList__ATM_AREA.Add(str_module);
			sList__LPx_AREA.Add(str_module);

			//
			str_module = "AL1";
			sList__ATM_AREA.Add(str_module);
			sList__ALx_AREA.Add(str_module);

			//
			str_module = "BUFF1";
			sList__ATM_AREA.Add(str_module);
			sList__BUFFx_AREA.Add(str_module);

			str_module = "BUFF2";
			sList__ATM_AREA.Add(str_module);
			sList__BUFFx_AREA.Add(str_module);

			//
			for(int i=0; i<iLLx_SIZE; i++)
			{
				str_module = Get__LLx_NAME(i);
				sList__ATM_AREA.Add(str_module);
				sList__LBx_AREA.Add(str_module);

				// ...
				int id = i + 1;

				str_module.Format("LL%1d", id);
				sList__ATM_AREA.Add(str_module);
				sList__LBx_AREA.Add(str_module);

				str_module.Format("LL%1d-1", id);
				sList__ATM_AREA.Add(str_module);
				sList__LBx_AREA.Add(str_module);

				str_module.Format("LL%1d-2", id);
				sList__ATM_AREA.Add(str_module);
				sList__LBx_AREA.Add(str_module);
			}

			/*
			str_module = "VIS1";
			sList__ATM_AREA.Add(str_module);
			sList__VISx_AREA.Add(str_module);
			*/
		}

		// ...
		{
			sList__VAC_RB_AREA.RemoveAll();
			sList__VAC_RB_AREA.RemoveAll();
			sList__PMx_AREA.RemoveAll();

			//
			str_module = "VAC_RB1_A";
			sList__VAC_AREA.Add(str_module);
			sList__VAC_RB_AREA.Add(str_module);

			str_module = "VAC_RB1_B";
			sList__VAC_AREA.Add(str_module);
			sList__VAC_RB_AREA.Add(str_module);

			//
			str_module = "PM1";
			sList__VAC_AREA.Add(str_module);
			sList__PMx_AREA.Add(str_module);

			str_module = "PM2";
			sList__VAC_AREA.Add(str_module);
			sList__PMx_AREA.Add(str_module);

			str_module = "PM3";
			sList__VAC_AREA.Add(str_module);
			sList__PMx_AREA.Add(str_module);

			str_module = "PM4";
			sList__VAC_AREA.Add(str_module);
			sList__PMx_AREA.Add(str_module);

			str_module = "PM5";
			sList__VAC_AREA.Add(str_module);
			sList__PMx_AREA.Add(str_module);

			str_module = "PM6";
			sList__VAC_AREA.Add(str_module);
			sList__PMx_AREA.Add(str_module);
		}
	}

	// ...
	{
		sCH__MACRO_MOVE__MOVE_SELECT->Set__DATA("SOURCE");

		//
		{
			sCH__MACRO_MOVE__OBJ_STATUS__STANDBY->Set__DATA("STANDBY");
			sCH__MACRO_MOVE__PRESSURE_STATUS__VAC->Set__DATA("VAC");
			sCH__MACRO_MOVE__DOOR_STATUS__CLOSE->Set__DATA("CLOSE");
			sCH__MACRO_MOVE__DOOR_STATUS__OPEN->Set__DATA("OPEN");
			sCH__MACRO_MOVE__CST_STATUS__EXIST->Set__DATA("EXIST");
			sCH__MACRO_MOVE__CST_POS__LOAD->Set__DATA("LOAD");
		}

		//
		{
			sCH__MACRO_MOVE__ATM_RB_MOVE_POS__CENTER->Set__DATA("LP1");
			sCH__MACRO_MOVE__ATM_RB_ARM_ACT__RETRACT->Set__DATA("RETRACT");

			sCH__MACRO_MOVE__VAC_RB_ARM_TYPE__A->Set__DATA("A");
			sCH__MACRO_MOVE__VAC_RB_ROT_POS__CENTER->Set__DATA("HOME");
			sCH__MACRO_MOVE__VAC_RB_ARM_ACT__RETRACT->Set__DATA("RETRACT");
		}

		//
		sCH__MACRO_MOVE__EDITOR_ACT_CMMD->Set__DATA("");

		//
		sCH__MACRO_MOVE__ACTION_SELECT->Set__DATA("MOVE");

		//
		int i;

		for(i=0;i<CFG_PM_LIMIT;i++)
		{
			sCH__MACRO_MOVE__PMC_SLOT_STATUS[i]->Set__DATA(STR__NONE);
			sCH__MACRO_MOVE__PMC_SLOT_TITLE[i]->Set__DATA("");
		}

		//
		sCH__MACRO_MOVE__VAC_RB__A_ARM_SLOT_STATUS->Set__DATA(STR__NONE);
		sCH__MACRO_MOVE__VAC_RB__A_ARM_SLOT_TITLE->Set__DATA("");
		sCH__MACRO_MOVE__VAC_RB__B_ARM_SLOT_STATUS->Set__DATA(STR__NONE);
		sCH__MACRO_MOVE__VAC_RB__B_ARM_SLOT_TITLE->Set__DATA("");

		//
		sCH__MACRO_MOVE__ATM_RB__A_ARM_SLOT_STATUS->Set__DATA(STR__NONE);
		sCH__MACRO_MOVE__ATM_RB__A_ARM_SLOT_TITLE->Set__DATA("");

		sCH__MACRO_MOVE__ATM_RB__B_ARM_SLOT_STATUS->Set__DATA(STR__NONE);
		sCH__MACRO_MOVE__ATM_RB__B_ARM_SLOT_TITLE->Set__DATA("");

		// LLx ...
		{
			for(int ll_i=0; ll_i<iLLx_SIZE; ll_i++)
			{
				for(i=0; i<CFG_LLx__SLOT_MAX; i++)
				{
					sCH__MACRO_MOVE__LLx_SLOT_STATUS[ll_i][i]->Set__DATA(STR__NONE);
					sCH__MACRO_MOVE__LLx_SLOT_TITLE[ll_i][i]->Set__DATA("");
				}
			}
		}

		//
		for(i=0;i<CFG_AL__SLOT_MAX;i++)
		{
			sCH__MACRO_MOVE__AL_SLOT_STATUS[i]->Set__DATA(STR__NONE);
			sCH__MACRO_MOVE__AL_SLOT_TITLE[i]->Set__DATA("");
		}

		//
		for(i=0;i<CFG_BUFFER__SLOT_MAX;i++)
		{
			sCH__MACRO_MOVE__BUFFER1_SLOT_STATUS[i]->Set__DATA(STR__NONE);
			sCH__MACRO_MOVE__BUFFER1_SLOT_TITLE[i]->Set__DATA("");

			sCH__MACRO_MOVE__BUFFER2_SLOT_STATUS[i]->Set__DATA(STR__NONE);
			sCH__MACRO_MOVE__BUFFER2_SLOT_TITLE[i]->Set__DATA("");
		}

		//
		for(i=0;i<CFG_LP_LIMIT;i++)
		{
			int j;

			for(j=0;j<CFG_LP__SLOT_MAX;j++)
			{
				sCH__MACRO_MOVE__LPx_SLOT_STATUS[i][j]->Set__DATA(STR__EXIST);
			}
		}
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj_Opr__MAINT_MODE::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		CString obj_msg;

		obj_msg.Format("%s started ...",mode);
		printf("[%s] : %s Started ... \n", sObject_Name,mode);

		xAPP_LOG_CTRL->WRITE__LOG(obj_msg);

		xCH__OBJ_MSG->Set__DATA(obj_msg);
		xCH__ACTIVE_MODE->Set__DATA(mode);
	}

	// ...
	{
		IF__CTRL_MODE(sMODE__MANUAL_MOVE)
		{
			flag = Call__MANUAL_MOVE(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__TOOL_CLEAR)
		{
			for(int i=0; i<iLPx_SIZE; i++)
			{
				sEXT_CH__LPx_LOCK_FLAG[i]->Set__DATA(STR__YES);
			}

			flag = Call__TOOL_CLEAR(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__PARTICLE_CHECK)
		{
			flag = Call__PARTICLE_CHECK(p_variable);
		}
		ELSE_IF__CTRL_MODE(sMODE__MACRO_MOVE)
		{
			flag = Call__MACRO_MOVE(p_variable);
		}

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
	{
		int i;

		for(i=0;i<iLPx_SIZE;i++)
		{
			sEXT_CH__LPx_LOCK_FLAG[i]->Set__DATA("");
		}
	}

	// ...
	{
		CString obj_msg;

		obj_msg.Format("%s completed : [%1d]", mode,flag);
		printf("[%s] : %s completed [%1d] ... \n", sObject_Name,mode,flag);

		xAPP_LOG_CTRL->WRITE__LOG(obj_msg);

		xCH__OBJ_MSG->Set__DATA(obj_msg);
		xCH__ACTIVE_MODE->Set__DATA("");
	}

	return flag;
}
int CObj_Opr__MAINT_MODE::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__MACRO_MOVE_CTRL)
	{
		Mon__MACRO_MOVE_CTRL(p_variable,p_alarm);	
	}

	return 1;
}
