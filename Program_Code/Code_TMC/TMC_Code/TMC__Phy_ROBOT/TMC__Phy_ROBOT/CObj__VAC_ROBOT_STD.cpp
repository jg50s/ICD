#include "StdAfx.h"
#include "CObj__VAC_ROBOT_STD.h"
#include "CObj__VAC_ROBOT_STD__DEF.h"
#include "CObj__VAC_ROBOT_STD__ALID.h"

#include "Macro_Function.h"


//--------------------------------------------------------------------------------
CObj__VAC_ROBOT_STD::CObj__VAC_ROBOT_STD()
{

}
CObj__VAC_ROBOT_STD::~CObj__VAC_ROBOT_STD()
{

}

//--------------------------------------------------------------------------------
int CObj__VAC_ROBOT_STD::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	"INIT");

		ADD__CTRL_VAR(sMODE__HOME,  "HOME");

		ADD__CTRL_VAR(sMODE__PICK,	"PICK");
		ADD__CTRL_VAR(sMODE__PLACE,	"PLACE");
		ADD__CTRL_VAR(sMODE__SWAP,	"SWAP");

		ADD__CTRL_VAR(sMODE__ROTATE,"ROTATE");
		ADD__CTRL_VAR(sMODE__MAP,	"MAP");

		ADD__CTRL_VAR(sMODE__RETRACT, "RETRACT");
		ADD__CTRL_VAR(sMODE__EXTEND,  "EXTEND");
		ADD__CTRL_VAR(sMODE__GOUP,    "GOUP");
		ADD__CTRL_VAR(sMODE__GODOWN,  "GODOWN");

		ADD__CTRL_VAR(sMODE__RQ_STN,  "RQ_STN");
		ADD__CTRL_VAR(sMODE__SET_STN, "SET_STN");

		ADD__CTRL_VAR(sMODE__TEACHED_CPTR_SAVE, "TEACHED_CPTR_SAVE");

		ADD__CTRL_VAR(sMODE__TIME_TEST, "TIME_TEST");
	}
	return 1;
}
int CObj__VAC_ROBOT_STD::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee ";

	return 1;
}


// ...
#define APP_DSP__RB_TARGET_MOVE						\
"UNKNOWN  HOME  READY								\
 PM1  PM2  PM3  PM4  PM5  PM6						\
 PM12 PM34 PM56 									\
 LBA  LBB  LBC  LBD									\
 LBA-1   LBA-2										\
 LBB-1   LBB-2										\
 LBC-1   LBC-2										\
 LBD-1   LBC-2										\
 LBA-12  LBB-12  LBC-12  LBD-12"

#define APP_DSP__STN_NAME							\
"PM1 PM2 PM3 PM4 PM5 PM6							\
 LBA LBB LBC LBD"

#define APP_DSP__SLOT_NUM							\
"1 2 3 4"

#define APP_DSP__RB_ARM								\
"A  B  AB"

#define APP_DSP__ARM_STS_ANI						\
"UNKNOWN RETRACT EXTEND"


// ...
#define MON_ID__STATE_MONITOR						1


int CObj__VAC_ROBOT_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name, def_data;
	int i;
	int k;

	// LLx ...
	{
		CString def_name;
		CString def_data;

		def_name = "LLx.MULTI_SLOT_VALVE";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		if(def_data.CompareNoCase("YES") == 0)			bActive__LLx_MULTI_SLOT_VALVE = true;
		else											bActive__LLx_MULTI_SLOT_VALVE = false;
	}

	// ...
	{
		str_name = "sOBJ.MESSAGE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MESSAGE,str_name);
	}

	// PARA CHANNEL -----
	{
		str_name = "OTR.IN.PARA.dSTN.NAME";
		STD__ADD_DIGITAL(str_name, APP_DSP__STN_NAME);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__STN_NAME,str_name);

		str_name = "OTR.IN.PARA.dSTN.SLOT";
		STD__ADD_DIGITAL(str_name, APP_DSP__SLOT_NUM);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__STN_SLOT,str_name);

		str_name = "OTR.IN.PARA.dARM.TYPE";
		STD__ADD_DIGITAL(str_name, APP_DSP__RB_ARM);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__ARM_TYPE,str_name);
	}

	// MATERIAL CHANNEL -----
	{
		CString dsp_slot_sts;
		p_variable->Get__STD_DESCRIPTION("STD_SLOT_STATUS", dsp_slot_sts);

		// Material Status
		str_name = "OTR.OUT.MON.dARM_A.MATERIAL.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, dsp_slot_sts, "");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS,str_name);

		str_name = "OTR.OUT.MON.dARM_B.MATERIAL.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, dsp_slot_sts, "");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS,str_name);

		// Material Title
		str_name = "OTR.OUT.MON.sARM_A.MATERIAL.TITLE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__OTR_OUT_MON__ARM_A_MATERIAL_TITLE,str_name);

		str_name = "OTR.OUT.MON.sARM_B.MATERIAL.TITLE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__OTR_OUT_MON__ARM_B_MATERIAL_TITLE,str_name);
	}

	// WAFER INFO ...
	{
		// ARM_A ...
		str_name = "WFR_INFO.PORTID.ARM_A";
		STD__ADD_STRING(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__WFR_INFO_PORTID__ARM_A, str_name);
		
		str_name = "WFR_INFO.SLOTID.ARM_A";
		STD__ADD_STRING(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__WFR_INFO_SLOTID__ARM_A, str_name);
		
		str_name = "WFR_INFO.PPID_.ARM_A";
		STD__ADD_STRING(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__WFR_INFO_PPID__ARM_A, str_name);
		
		str_name = "WFR_INFO.LOTID.ARM_A";
		STD__ADD_STRING(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__WFR_INFO_LOTID__ARM_A, str_name);
		
		str_name = "WFR_INFO.MATERIALID.ARM_A";
		STD__ADD_STRING(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__WFR_INFO_MATERIALID__ARM_A, str_name);

		// ARM_B ...
		str_name = "WFR_INFO.PORTID.ARM_B";
		STD__ADD_STRING(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__WFR_INFO_PORTID__ARM_B, str_name);
		
		str_name = "WFR_INFO.SLOTID.ARM_B";
		STD__ADD_STRING(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__WFR_INFO_SLOTID__ARM_B, str_name);
		
		str_name = "WFR_INFO.PPID.ARM_B";
		STD__ADD_STRING(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__WFR_INFO_PPID__ARM_B, str_name);
		
		str_name = "WFR_INFO.LOTID.ARM_B";
		STD__ADD_STRING(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__WFR_INFO_LOTID__ARM_B, str_name);

		str_name = "WFR_INFO.MATERIALID.ARM_B";
		STD__ADD_STRING(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__WFR_INFO_MATERIALID__ARM_B, str_name);
	}

	// ANIMATION CHANNEL -----
	{	
		// Robot
		str_name = "OTR.OUT.MON.dACT.ARM";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__RB_ARM,"");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__ACT_ARM,str_name);

		str_name = "OTR.OUT.MON.dARM_A.ACT";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__ARM_STS_ANI,"");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__ARM_A_ACT,str_name);

		str_name = "OTR.OUT.MON.dARM_B.ACT";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__ARM_STS_ANI,"");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__ARM_B_ACT,str_name);

		str_name = "OTR.OUT.MON.dTRG.MOVE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__RB_TARGET_MOVE,"");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__TRG_MOVE,str_name);

		str_name = "OTR.OUT.MON.dTRG.ROTATE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__RB_TARGET_MOVE,"");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__TRG_ROTATE,str_name);

		p_variable->Get__DEF_CONST_DATA("PM_SIZE", def_data);
		m_nPM_LIMIT = atoi(def_data);

		for(i=0;i<m_nPM_LIMIT;i++)
		{
			// PMx - ARM_STATE
			str_name.Format("OTR.OUT.MON.dPM%1d.ARM.STATE", i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__ARM_STS_ANI,"");
			LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__PMx_ARM_STATE[i],str_name);

			// PMx - Arm_A
			str_name.Format("OTR.OUT.MON.dPM%1d.ARM_A.ACT", i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__ARM_STS_ANI,"");
			LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__PMx_ARM_A_ACT[i],str_name);

			// PMx - Arm_B
			str_name.Format("OTR.OUT.MON.dPM%1d.ARM_B.ACT", i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__ARM_STS_ANI,"");
			LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__PMx_ARM_B_ACT[i],str_name);
		}

		// LLx ...
		for(int ll_i=0; ll_i<CFG_LLx__SIZE; ll_i++)
		{
			CString ll_name = Macro__GET_LLx_NAME(ll_i);

			str_name.Format("OTR.OUT.MON.d%s.ARM_A.ACT", ll_name);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__ARM_STS_ANI,"");
			LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__LBx_ARM_A_ACT[ll_i],str_name);

			str_name.Format("OTR.OUT.MON.d%s.ARM_B.ACT", ll_name);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__ARM_STS_ANI,"");
			LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__LBx_ARM_B_ACT[ll_i],str_name);
		}
	}

	// TAS Channel ...
	{
		str_name = "TAS.RESET.REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TAS_RESET_REQ, str_name);

		//
		for(i=0; i<CFG_ACT__SIZE; i++)
		{
			CString act_name;

				 if(i == _ACT_INDEX__PICK)			act_name = "PICK";			
			else if(i == _ACT_INDEX__PLACE)			act_name = "PLACE";			
			else if(i == _ACT_INDEX__ROTATE)		act_name = "ROTATE";			
			else									continue;

			// ROBOT ...
			{
				str_name.Format("TAS.%s.TIME.NOW.RB", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_NOW__RB[i], str_name);

				//
				str_name.Format("TAS.%s.TIME.MIN.RB", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MIN__RB[i], str_name);
		
				str_name.Format("TAS.%s.TIME.MAX.RB", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MAX__RB[i], str_name);

				//
				str_name.Format("TAS.%s.TIME.AVG.RB", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG__RB[i], str_name);

				str_name.Format("TAS.%s.TIME.AVG_F.RB", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG_F__RB[i], str_name);

				str_name.Format("TAS.%s.TIME.CNT.RB", act_name);
				STD__ADD_ANALOG(str_name, "count", 0, 1, 100000);
				LINK__VAR_ANALOG_CTRL(aCH__TAS_ACTION_TIME_CNT__RB[i], str_name);
			}

			// LLx ...
			for(k=0; k<CFG_LLx__SIZE; k++)
			{
				int id = k + 1;

				if(bActive__LLx_MULTI_SLOT_VALVE)
				{
					for(int t=0; t<CFG_LLx__SLOT_SIZE; t++)
					{
						int slot = t + 1;

						str_name.Format("TAS.%s.TIME.NOW.LL%1d.%1d", act_name,id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_NOW__LLx_SLOT[i][k][t], str_name);

						//
						str_name.Format("TAS.%s.TIME.MIN.LL%1d.%1d", act_name,id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MIN__LLx_SLOT[i][k][t], str_name);

						str_name.Format("TAS.%s.TIME.MAX.LL%1d.%1d", act_name,id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MAX__LLx_SLOT[i][k][t], str_name);

						//
						str_name.Format("TAS.%s.TIME.AVG.LL%1d.%1d", act_name,id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG__LLx_SLOT[i][k][t], str_name);

						str_name.Format("TAS.%s.TIME.AVG_F.LL%1d.%1d", act_name,id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG_F__LLx_SLOT[i][k][t], str_name);

						str_name.Format("TAS.%s.TIME.CNT.LL%1d.%1d", act_name,id,slot);
						STD__ADD_ANALOG(str_name, "count", 0, 1, 100000);
						LINK__VAR_ANALOG_CTRL(aCH__TAS_ACTION_TIME_CNT__LLx_SLOT[i][k][t], str_name);
					}
				}
				else
				{
					str_name.Format("TAS.%s.TIME.NOW.LL%1d", act_name,id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_NOW__LLx_X[i][k], str_name);

					//
					str_name.Format("TAS.%s.TIME.MIN.LL%1d", act_name,id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MIN__LLx_X[i][k], str_name);

					str_name.Format("TAS.%s.TIME.MAX.LL%1d", act_name,id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MAX__LLx_X[i][k], str_name);

					//
					str_name.Format("TAS.%s.TIME.AVG.LL%1d", act_name,id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG__LLx_X[i][k], str_name);

					str_name.Format("TAS.%s.TIME.AVG_F.LL%1d", act_name,id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG_F__LLx_X[i][k], str_name);

					str_name.Format("TAS.%s.TIME.CNT.LL%1d", act_name,id);
					STD__ADD_ANALOG(str_name, "count", 0, 1, 100000);
					LINK__VAR_ANALOG_CTRL(aCH__TAS_ACTION_TIME_CNT__LLx_X[i][k], str_name);
				}
			}

			// PMx ...
			for(k=0; k<CFG_PMx__SIZE; k++)
			{
				int id = k + 1;

				str_name.Format("TAS.%s.TIME.NOW.PM%1d", act_name,id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_NOW__PMx[i][k], str_name);

				//
				str_name.Format("TAS.%s.TIME.MIN.PM%1d", act_name,id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MIN__PMx[i][k], str_name);

				str_name.Format("TAS.%s.TIME.MAX.PM%1d", act_name,id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MAX__PMx[i][k], str_name);

				//
				str_name.Format("TAS.%s.TIME.AVG.PM%1d", act_name,id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG__PMx[i][k], str_name);

				str_name.Format("TAS.%s.TIME.AVG_F.PM%1d", act_name,id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG_F__PMx[i][k], str_name);

				str_name.Format("TAS.%s.TIME.CNT.PM%1d", act_name,id);
				STD__ADD_ANALOG(str_name, "count", 0, 1, 100000);
				LINK__VAR_ANALOG_CTRL(aCH__TAS_ACTION_TIME_CNT__PMx[i][k], str_name);
			}
		}
	}

	// DA Config ...
	{
		// LLx ...
		{
			CString ll_name;

			if(bActive__LLx_MULTI_SLOT_VALVE)
			{
				for(i=0; i<CFG_LLx__SIZE; i++)
				{	
					ll_name.Format("LL%1d", i+1);

					for(int k=0; k<CFG_LLx__SLOT_SIZE; k++)
					{
						int slot = k + 1;

						// A_ARM ...
						{
							// Hard
							str_name.Format("CFG.%s.%1d.R.OFFSET.HARD.ERR.A_ARM", ll_name,slot);
							STD__ADD_ANALOG_WITH_X_OPTION(str_name, "deg", 1, 0, 10, "");
							LINK__VAR_ANALOG_CTRL(aCH__CFG__R_OFFSET_HARD_ERR_A_ARM__LLx_SLOT[i][k], str_name);

							str_name.Format("CFG.%s.%1d.T.OFFSET.HARD.ERR.A_ARM", ll_name,slot);
							STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 1, 0, 10, "");
							LINK__VAR_ANALOG_CTRL(aCH__CFG__T_OFFSET_HARD_ERR_A_ARM__LLx_SLOT[i][k], str_name);

							// Soft
							str_name.Format("CFG.%s.%1d.R.OFFSET.SOFT.ERR.A_ARM", ll_name,slot);
							STD__ADD_ANALOG_WITH_X_OPTION(str_name, "deg", 1, 0, 10, "");
							LINK__VAR_ANALOG_CTRL(aCH__CFG__R_OFFSET_SOFT_ERR_A_ARM__LLx_SLOT[i][k], str_name);

							str_name.Format("CFG.%s.%1d.T.OFFSET.SOFT.ERR.A_ARM", ll_name,slot);
							STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 1, 0, 10, "");
							LINK__VAR_ANALOG_CTRL(aCH__CFG__T_OFFSET_SOFT_ERR_A_ARM__LLx_SLOT[i][k], str_name);
						}
						// B_ARM ...
						{
							// Hard
							str_name.Format("CFG.%s.%1d.R.OFFSET.HARD.ERR.B_ARM", ll_name,slot);
							STD__ADD_ANALOG_WITH_X_OPTION(str_name, "deg", 1, 0, 10, "");
							LINK__VAR_ANALOG_CTRL(aCH__CFG__R_OFFSET_HARD_ERR_B_ARM__LLx_SLOT[i][k], str_name);

							str_name.Format("CFG.%s.%1d.T.OFFSET.HARD.ERR.B_ARM", ll_name,slot);
							STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 1, 0, 10, "");
							LINK__VAR_ANALOG_CTRL(aCH__CFG__T_OFFSET_HARD_ERR_B_ARM__LLx_SLOT[i][k], str_name);

							// Soft
							str_name.Format("CFG.%s.%1d.R.OFFSET.SOFT.ERR.B_ARM", ll_name,slot);
							STD__ADD_ANALOG_WITH_X_OPTION(str_name, "deg", 1, 0, 10, "");
							LINK__VAR_ANALOG_CTRL(aCH__CFG__R_OFFSET_SOFT_ERR_B_ARM__LLx_SLOT[i][k], str_name);

							str_name.Format("CFG.%s.%1d.T.OFFSET.SOFT.ERR.B_ARM", ll_name,slot);
							STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 1, 0, 10, "");
							LINK__VAR_ANALOG_CTRL(aCH__CFG__T_OFFSET_SOFT_ERR_B_ARM__LLx_SLOT[i][k], str_name);
						}
					}
				}
			}
			else
			{
				for(i=0; i<CFG_LLx__SIZE; i++)
				{	
					ll_name.Format("LL%1d", i+1);

					// A_ARM ...
					{
						// Hard
						str_name.Format("CFG.%s.R.OFFSET.HARD.ERR.A_ARM", ll_name);
						STD__ADD_ANALOG_WITH_X_OPTION(str_name, "deg", 1, 0, 10, "");
						LINK__VAR_ANALOG_CTRL(aCH__CFG__R_OFFSET_HARD_ERR_A_ARM__LLx_X[i], str_name);

						str_name.Format("CFG.%s.T.OFFSET.HARD.ERR.A_ARM", ll_name);
						STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 1, 0, 10, "");
						LINK__VAR_ANALOG_CTRL(aCH__CFG__T_OFFSET_HARD_ERR_A_ARM__LLx_X[i], str_name);

						// Soft
						str_name.Format("CFG.%s.R.OFFSET.SOFT.ERR.A_ARM", ll_name);
						STD__ADD_ANALOG_WITH_X_OPTION(str_name, "deg", 1, 0, 10, "");
						LINK__VAR_ANALOG_CTRL(aCH__CFG__R_OFFSET_SOFT_ERR_A_ARM__LLx_X[i], str_name);

						str_name.Format("CFG.%s.T.OFFSET.SOFT.ERR.A_ARM", ll_name);
						STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 1, 0, 10, "");
						LINK__VAR_ANALOG_CTRL(aCH__CFG__T_OFFSET_SOFT_ERR_A_ARM__LLx_X[i], str_name);
					}
					// B_ARM ...
					{
						// Hard
						str_name.Format("CFG.%s.R.OFFSET.HARD.ERR.B_ARM", ll_name);
						STD__ADD_ANALOG_WITH_X_OPTION(str_name, "deg", 1, 0, 10, "");
						LINK__VAR_ANALOG_CTRL(aCH__CFG__R_OFFSET_HARD_ERR_B_ARM__LLx_X[i], str_name);

						str_name.Format("CFG.%s.T.OFFSET.HARD.ERR.B_ARM", ll_name);
						STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 1, 0, 10, "");
						LINK__VAR_ANALOG_CTRL(aCH__CFG__T_OFFSET_HARD_ERR_B_ARM__LLx_X[i], str_name);

						// Soft
						str_name.Format("CFG.%s.R.OFFSET.SOFT.ERR.B_ARM", ll_name);
						STD__ADD_ANALOG_WITH_X_OPTION(str_name, "deg", 1, 0, 10, "");
						LINK__VAR_ANALOG_CTRL(aCH__CFG__R_OFFSET_SOFT_ERR_B_ARM__LLx_X[i], str_name);

						str_name.Format("CFG.%s.T.OFFSET.SOFT.ERR.B_ARM", ll_name);
						STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 1, 0, 10, "");
						LINK__VAR_ANALOG_CTRL(aCH__CFG__T_OFFSET_SOFT_ERR_B_ARM__LLx_X[i], str_name);
					}
				}
			}
		}
		// PMx ...
		{
			CString pm_name;

			for(i=0; i<CFG_PMx__SIZE; i++)
			{	
				pm_name.Format("PM%1d", i+1);

				// A_ARM ...
				{
					// Hard
					str_name.Format("CFG.%s.R.OFFSET.HARD.ERR.A_ARM", pm_name);
					STD__ADD_ANALOG_WITH_X_OPTION(str_name, "deg", 1, 0, 10, "");
					LINK__VAR_ANALOG_CTRL(aCH__CFG__R_OFFSET_HARD_ERR_A_ARM__PMx[i], str_name);

					str_name.Format("CFG.%s.T.OFFSET.HARD.ERR.A_ARM", pm_name);
					STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 1, 0, 10, "");
					LINK__VAR_ANALOG_CTRL(aCH__CFG__T_OFFSET_HARD_ERR_A_ARM__PMx[i], str_name);

					// Soft
					str_name.Format("CFG.%s.R.OFFSET.SOFT.ERR.A_ARM", pm_name);
					STD__ADD_ANALOG_WITH_X_OPTION(str_name, "deg", 1, 0, 10, "");
					LINK__VAR_ANALOG_CTRL(aCH__CFG__R_OFFSET_SOFT_ERR_A_ARM__PMx[i], str_name);

					str_name.Format("CFG.%s.T.OFFSET.SOFT.ERR.A_ARM", pm_name);
					STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 1, 0, 10, "");
					LINK__VAR_ANALOG_CTRL(aCH__CFG__T_OFFSET_SOFT_ERR_A_ARM__PMx[i], str_name);
				}
				// B_ARM ...
				{
					// Hard
					str_name.Format("CFG.%s.R.OFFSET.HARD.ERR.B_ARM", pm_name);
					STD__ADD_ANALOG_WITH_X_OPTION(str_name, "deg", 1, 0, 10, "");
					LINK__VAR_ANALOG_CTRL(aCH__CFG__R_OFFSET_HARD_ERR_B_ARM__PMx[i], str_name);

					str_name.Format("CFG.%s.T.OFFSET.HARD.ERR.B_ARM", pm_name);
					STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 1, 0, 10, "");
					LINK__VAR_ANALOG_CTRL(aCH__CFG__T_OFFSET_HARD_ERR_B_ARM__PMx[i], str_name);

					// Soft
					str_name.Format("CFG.%s.R.OFFSET.SOFT.ERR.B_ARM", pm_name);
					STD__ADD_ANALOG_WITH_X_OPTION(str_name, "deg", 1, 0, 10, "");
					LINK__VAR_ANALOG_CTRL(aCH__CFG__R_OFFSET_SOFT_ERR_B_ARM__PMx[i], str_name);

					str_name.Format("CFG.%s.T.OFFSET.SOFT.ERR.B_ARM", pm_name);
					STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 1, 0, 10, "");
					LINK__VAR_ANALOG_CTRL(aCH__CFG__T_OFFSET_SOFT_ERR_B_ARM__PMx[i], str_name);
				}
			}
		}

		// D Chart ...
		{
			str_name = "CFG.DA.CHART.AXIS_MAX";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 0, 1, 10, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG__DA_CHART_AXIS_MAX, str_name);

			str_name = "CFG.DA.CHART.ERR_RANGE";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 1, 0.1, 5, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG__DA_CHART_ERR_RANGE, str_name);
		}
	}

	// DA Result ...
	{
		// Robot ...
		{
			// R Offset ...
			str_name = "MON.ROBOT.R.OFFSET.A_ARM";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_R_OFFSET_A_ARM__ROBOT, str_name);

			str_name = "MON.ROBOT.R.OFFSET.B_ARM";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_R_OFFSET_B_ARM__ROBOT, str_name);

			// T Offset ...
			str_name = "MON.ROBOT.T.OFFSET.A_ARM";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_T_OFFSET_A_ARM__ROBOT, str_name);

			str_name = "MON.ROBOT.T.OFFSET.B_ARM";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_T_OFFSET_B_ARM__ROBOT, str_name);
		}

		// LLx ...
		for(i=0; i<CFG_LLx__SIZE; i++)
		{
			CString ll_name = Macro__GET_LLx_NAME(i);
			int id = i + 1;

			if(bActive__LLx_MULTI_SLOT_VALVE)
			{
				for(int k=0; k<CFG_LLx__SLOT_SIZE; k++)
				{
					int slot = k + 1;

					// Sts ...
					{
						str_name.Format("MON.LL%1d.%1d.STS.OFFSET.A_ARM", id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__MON_STS_OFFSET_A_ARM__LLx_SLOT[i][k], str_name);

						str_name.Format("MON.LL%1d.%1d.STS.OFFSET.B_ARM", id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__MON_STS_OFFSET_B_ARM__LLx_SLOT[i][k], str_name);
					}
					// Result ...
					{
						str_name.Format("MON.LL%1d.%1d.RESULT.OFFSET.A_ARM", id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__MON_RESULT_OFFSET_A_ARM__LLx_SLOT[i][k], str_name);

						str_name.Format("MON.LL%1d.%1d.RESULT.OFFSET.B_ARM", id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__MON_RESULT_OFFSET_B_ARM__LLx_SLOT[i][k], str_name);
					}
					// R Offset ...
					{
						str_name.Format("MON.LL%1d.%1d.R.OFFSET.A_ARM", id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__MON_R_OFFSET_A_ARM__LLx_SLOT[i][k], str_name);

						str_name.Format("MON.LL%1d.%1d.R.OFFSET.B_ARM", id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__MON_R_OFFSET_B_ARM__LLx_SLOT[i][k], str_name);
					}
					// T Offset ...
					{
						str_name.Format("MON.LL%1d.%1d.T.OFFSET.A_ARM", id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__MON_T_OFFSET_A_ARM__LLx_SLOT[i][k], str_name);

						str_name.Format("MON.LL%1d.%1d.T.OFFSET.B_ARM", id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__MON_T_OFFSET_B_ARM__LLx_SLOT[i][k], str_name);
					}
					// RT Offset ...
					{
						str_name.Format("MON.LL%1d.%1d.RT.OFFSET", id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__MON_DA_RT_OFFSET__LLx_SLOT[i][k], str_name);
					}

					// DA Chart Offset ...
					{
						str_name.Format("sDA.%s.%1d.CHART.ROFFSET.DISPLAY", ll_name,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__DA_CHART_R_OFFSET_DISPLAY__LLx_SLOT[i][k], str_name);

						str_name.Format("sDA.%s.%1d.CHART.TOFFSET.DISPLAY", ll_name,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__DA_CHART_T_OFFSET_DISPLAY__LLx_SLOT[i][k], str_name);
					}
				}
			}
			else
			{
				// Sts ...
				{
					str_name.Format("MON.LL%1d.STS.OFFSET.A_ARM", id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__MON_STS_OFFSET_A_ARM__LLx_X[i], str_name);

					str_name.Format("MON.LL%1d.STS.OFFSET.B_ARM", id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__MON_STS_OFFSET_B_ARM__LLx_X[i], str_name);
				}
				// Result ...
				{
					str_name.Format("MON.LL%1d.RESULT.OFFSET.A_ARM", id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__MON_RESULT_OFFSET_A_ARM__LLx_X[i], str_name);

					str_name.Format("MON.LL%1d.RESULT.OFFSET.B_ARM", id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__MON_RESULT_OFFSET_B_ARM__LLx_X[i], str_name);
				}
				// R Offset ...
				{
					str_name.Format("MON.LL%1d.R.OFFSET.A_ARM", id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__MON_R_OFFSET_A_ARM__LLx_X[i], str_name);

					str_name.Format("MON.LL%1d.R.OFFSET.B_ARM", id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__MON_R_OFFSET_B_ARM__LLx_X[i], str_name);
				}
				// T Offset ...
				{
					str_name.Format("MON.LL%1d.T.OFFSET.A_ARM", id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__MON_T_OFFSET_A_ARM__LLx_X[i], str_name);

					str_name.Format("MON.LL%1d.T.OFFSET.B_ARM", id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__MON_T_OFFSET_B_ARM__LLx_X[i], str_name);
				}
				// RT Offset ...
				{
					str_name.Format("MON.LL%1d.RT.OFFSET", id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__MON_DA_RT_OFFSET__LLx_X[i], str_name);
				}

				// DA Chart Offset ...
				{
					str_name.Format("sDA.%s.CHART.ROFFSET.DISPLAY", ll_name);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__DA_CHART_R_OFFSET_DISPLAY__LLx_X[i], str_name);

					str_name.Format("sDA.%s.CHART.TOFFSET.DISPLAY", ll_name);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__DA_CHART_T_OFFSET_DISPLAY__LLx_X[i], str_name);
				}
			}
		}

		// PMX ...
		for(i=0; i<CFG_PMx__SIZE; i++)
		{
			int id = i + 1;

			// Sts ...
			{
				str_name.Format("MON.PM%1d.STS.OFFSET.A_ARM", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__MON_STS_OFFSET_A_ARM__PMx[i], str_name);

				str_name.Format("MON.PM%1d.STS.OFFSET.B_ARM", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__MON_STS_OFFSET_B_ARM__PMx[i], str_name);
			}
			// Result ...
			{
				str_name.Format("MON.PM%1d.RESULT.OFFSET.A_ARM", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__MON_RESULT_OFFSET_A_ARM__PMx[i], str_name);

				str_name.Format("MON.PM%1d.RESULT.OFFSET.B_ARM", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__MON_RESULT_OFFSET_B_ARM__PMx[i], str_name);
			}
			// R Offset ...
			{
				str_name.Format("MON.PM%1d.R.OFFSET.A_ARM", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__MON_R_OFFSET_A_ARM__PMx[i], str_name);

				str_name.Format("MON.PM%1d.R.OFFSET.B_ARM", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__MON_R_OFFSET_B_ARM__PMx[i], str_name);
			}
			// T Offset ...
			{
				str_name.Format("MON.PM%1d.T.OFFSET.A_ARM", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__MON_T_OFFSET_A_ARM__PMx[i], str_name);

				str_name.Format("MON.PM%1d.T.OFFSET.B_ARM", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__MON_T_OFFSET_B_ARM__PMx[i], str_name);
			}
			// RT Offset ...
			{
				str_name.Format("MON.PM%1d.RT.OFFSET", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__MON_DA_RT_OFFSET__PMx[i], str_name);
			}

			// DA Chart Offset ...
			{
				str_name.Format("sDA.PM%1d.CHART.ROFFSET.DISPLAY", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DA_CHART_R_OFFSET_DISPLAY__PMx[i], str_name);

				str_name.Format("sDA.PM%1d.CHART.TOFFSET.DISPLAY", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DA_CHART_T_OFFSET_DISPLAY__PMx[i], str_name);
			}
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__STATE_MONITOR);
	}
	return 1;
}


// ...
#define  _LALM__RETRY_ABORT						\
l_act.RemoveAll();								\
l_act.Add("RETRY");								\
l_act.Add("ABORT");

#define  _LALM__CHECK							\
l_act.RemoveAll();								\
l_act.Add("CHECK");								\

#define  _LALM__ABORT_IGNORE					\
l_act.RemoveAll();								\
l_act.Add("ABORT");								\
l_act.Add("IGNORE");

#define  _LALM__ABORT_RETRY_IGNORE				\
l_act.RemoveAll();								\
l_act.Add("ABORT");								\
l_act.Add("RETRY");								\
l_act.Add("IGNORE");


int CObj__VAC_ROBOT_STD::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__ARM_A__MATERIAL_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "There is material on Robot's A-Arm.";

		alarm_msg = "Please, check material on Robot's A-Arm.\n";

		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__ARM_B__MATERIAL_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "There is material on Robot's B-Arm.";

		alarm_msg = "Please, check material on Robot's B-Arm.\n";

		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__LLx__MATERIAL_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "There is material in LLx.";

		alarm_msg = "Please, check material in LLx.\n";

		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__PMx__MATERIAL_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "There is material in PMx.";

		alarm_msg = "Please, check material in PMx.\n";

		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ARM_A__MATERIAL_NONE_ERROR;

		alarm_title  = title;
		alarm_title += "There is no material on Robot's A-Arm.";

		alarm_msg = "Please, check material on Robot's A-Arm.\n";

		_LALM__ABORT_RETRY_IGNORE;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__ARM_B__MATERIAL_NONE_ERROR;

		alarm_title  = title;
		alarm_title += "There is no material on Robot's B-Arm.";

		alarm_msg = "Please, check material on Robot's B-Arm.\n";

		_LALM__ABORT_RETRY_IGNORE;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__LLx__MATERIAL_NONE_ERROR;

		alarm_title  = title;
		alarm_title += "There is no material in LLx.";

		alarm_msg = "Please, check material in LLx.\n";

		_LALM__ABORT_RETRY_IGNORE;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__PMx__MATERIAL_NONE_ERROR;

		alarm_title  = title;
		alarm_title += "There is no material in PMx.";

		alarm_msg = "Please, check material in PMx.\n";

		_LALM__ABORT_RETRY_IGNORE;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__STN__NOT_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "STN does not exist.";

		alarm_msg = "Please, check config page.\n";

		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__LLx__SLOT_ID_ERROR;

		alarm_title  = title;
		alarm_title += "LLx Slot_ID Error !";

		alarm_msg = "Please, check the LLx slot parameter of command. \n";

		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__LLx__NOT_VALVE_OPEN;

		alarm_title  = title;
		alarm_title += "LLx's valve status is not open.";

		alarm_msg = "Please, check LLx's valve status !\n";

		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__PMx__NOT_VALVE_OPEN;

		alarm_title  = title;
		alarm_title += "PMx's valve status is not open.";

		alarm_msg = "";
	
		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_title,l_act);
	}

	// ...
	{
		alarm_id = ALID__TM_CHM__NOT_ATM_PRESSURE;

		alarm_title  = title;
		alarm_title += "TMC_CHM's Pressure is not ATM.";

		alarm_msg  = "Please, Check TMC_CHM's Pressure !\n";
		alarm_msg += "TMC_CHM's Pressure must be ATM.\n";

		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__LLx__NOT_ATM_PRESSURE;

		alarm_title  = title;
		alarm_title += "LLx's Pressure is not ATM.";

		alarm_msg  = "Please, Check LLx's Pressure !\n";
		alarm_msg += "LLx's Pressure must be ATM.\n";

		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__PMx__NOT_ATM_PRESSURE;

		alarm_title  = title;
		alarm_title += "PMx's pressure is not ATM.";

		alarm_msg  = "Please, check PMx's pressure !\n";
		alarm_msg += "PMx's pressure must be ATM.\n";

		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__TM_CHM__NOT_VAC_PRESSURE;

		alarm_title  = title;
		alarm_title += "TMC_CHM's Pressure is not VAC.";

		alarm_msg  = "Please, Check TMC_CHM's Pressure !\n";
		alarm_msg += "TMC_CHM's Pressure must be VAC.\n";

		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__LLx__NOT_VAC_PRESSURE;

		alarm_title  = title;
		alarm_title += "LLx's Pressure is not VAC.";

		alarm_msg  = "Please, Check LLx's Pressure !\n";
		alarm_msg += "LLx's Pressure must be VAC.\n";

		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__PMx__NOT_VAC_PRESSURE;

		alarm_title  = title;
		alarm_title += "PMx's pressure is not VAC.";

		alarm_msg  = "Please, check PMx's pressure !\n";
		alarm_msg += "PMx's pressure must be VAC.\n";

		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PMx__CAN_NOT_USE_PICK_PLACE_PASSIVE_CMD;

		alarm_title  = title;
		alarm_title += "Cannot use PICK or PLACE Command in PM CHAMBER.";

		alarm_msg  = "Please, check Command !\n";
		alarm_msg += "Only Use EXTEND or RETRACT Command in PM CHAMBER.\n";

		_LALM__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__DA_ERROR__SOFT_OFFSET;

		alarm_title  = title;
		alarm_title += "DA Soft-Offset Error !";

		alarm_msg = "Please, check DA result !\n";

		_LALM__CHECK;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);	
	}
	// ...
	{
		alarm_id = ALID__DA_ERROR__HARD_OFFSET;

		alarm_title  = title;
		alarm_title += "DA Hard-Offset Error !";

		alarm_msg = "Please, check DA result !\n";

		_LALM__ABORT_IGNORE;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);	
	}
	return 1;
}

//--------------------------------------------------------------------------------
int CObj__VAC_ROBOT_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString obj_name;
	CString str_name;
	int i;

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
		SCX__SEQ_INFO x_seq_info;
		
		iActive_SIM = x_seq_info->Is__SIMULATION_MODE();

		//
		CString dir_root;

		x_seq_info->Get__DIR_ROOT(sDir_Root);
		dir_root = sDir_Root + "\\EQP_LOG\\DA_Data\\";	

		CreateDirectory(dir_root, NULL);
	}

	// LLx ...
	{
		def_name = "LLx.MULTI_DOOR_VALVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		if(def_data.CompareNoCase("YES") == 0)			bActive__LLx_MULTI_DOOR_VALVE = true;
		else											bActive__LLx_MULTI_DOOR_VALVE = false;

		def_name = "LLx.MULTI_SLOT_VALVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		if(def_data.CompareNoCase("YES") == 0)			bActive__LLx_MULTI_SLOT_VALVE = true;
		else											bActive__LLx_MULTI_SLOT_VALVE = false;

		def_name = "LLx.SLOT_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		iLLx_SLOT_SIZE = atoi(def_data);
		if(iLLx_SLOT_SIZE > CFG_LLx__SLOT_SIZE)		iLLx_SLOT_SIZE = CFG_LLx__SLOT_SIZE;

		//
		def_name = "DATA.LLx_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		iSIZE__LLx = atoi(def_data);
		if(iSIZE__LLx > CFG_LLx__SIZE)		iSIZE__LLx = CFG_LLx__SIZE;

		for(int ll_i=0; ll_i<iSIZE__LLx; ll_i++)
		{
			def_name.Format("OBJ__LL%1d", ll_i+1);			
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			//
			str_name = "OTR.OUT.MON.aPRESSURE.TORR";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__LLx_PRESSURE_TORR[ll_i], obj_name,str_name);

			if(bActive__LLx_MULTI_SLOT_VALVE)
			{
				for(i=0; i<CFG_LLx__SLOT_SIZE; i++)
				{
					str_name.Format("OTR.OUT.MON.dSLIT.VALVE.STATUS.%1d", i+1);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LLx_SLIT_VALVE_STATUS_XX[ll_i][i], obj_name,str_name);
				}
			}
			else
			{
				str_name = "OTR.OUT.MON.dSLIT.VALVE.STATUS";
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LLx_SLIT_VALVE_STATUS_A[ll_i], obj_name,str_name);
			}

			for(i=0; i<CFG_LLx__SLOT_SIZE; i++)
			{
				str_name.Format("OTR.OUT.MON.dSLOT%002d.STATUS",i+1);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LLx_SLOT_STATUS[ll_i][i], obj_name,str_name);

				str_name.Format("OTR.OUT.MON.sSLOT%002d.TITLE",i+1);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LLx_SLOT_TITLE[ll_i][i], obj_name,str_name);
			}
		}
	}

	// DB_CFG ...
	{
		def_name = "PM_SIZE";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);

		m_nPM_LIMIT = atoi(def_data);
		if(m_nPM_LIMIT <= 0)
		{
			m_nPM_LIMIT = CFG_PMx__SIZE;
		}

		// ...
		def_name = "OBJ__DB";
		p_variable->Get__DEF_CONST_DATA(def_name, obj_name);

		// ...
		{
			str_name = "CFG.SETUP.TEST.MODE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_SETUP_TEST_MODE, obj_name,str_name);
		}

		// ...
		{
			str_name = "CFG.TRANSFER.MODE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_TRANSFER_MODE, obj_name,str_name);

			str_name = "CFG.REF.ATM.PRESSURE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_REF_ATM_PRESSURE, obj_name,str_name);

			str_name = "CFG.REF.VAC.PRESSURE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_REF_VAC_PRESSURE, obj_name,str_name);
		}

		// LLx ...
		for(i=0; i<CFG_LLx__SIZE; i++)
		{
			CString ll_name = Macro__GET_LLx_NAME(i);
			int ll_id = i + 1;

			// .CFG.SLOT.USE ..
			{
				str_name.Format("CFG.%s.SLOT.MAX", ll_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LLx_SLOT_MAX[i], obj_name,str_name);

				for(int  k=0; k<CFG_LLx__SLOT_SIZE; k++)
				{
					int slot = k + 1;

					str_name.Format("CFG.LL%1d.SLOT%02d.USE", ll_id, slot);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LLx_SLOT_USE_X[i][k], obj_name,str_name);
				}
			}

			// DA Use ...
			str_name.Format("CFG.DA.USE.LL%1d", ll_id);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_DA_USE__LLx[i], obj_name,str_name);

			if(bActive__LLx_MULTI_SLOT_VALVE)
			{
				str_name.Format("CFG.LL%1d.1.EXIST.FLAG", ll_id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LLx_1_EXIST_FLAG[i], obj_name,str_name);

				str_name.Format("CFG.LL%1d.2.EXIST.FLAG", ll_id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LLx_2_EXIST_FLAG[i], obj_name,str_name);
			}
			else
			{
				str_name.Format("CFG.%s.EXIST.FLAG", ll_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LLx_EXIST_FLAG[i], obj_name,str_name);
			}
		}

		// PMx ...
		for(i=0; i<CFG_PMx__SIZE; i++)
		{
			//
			str_name.Format("CFG.PM%1d.EXIST.FLAG", i+1);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_PMx_EXIST_FLAG[i], obj_name,str_name);

			str_name.Format("CFG.PM%1d.SV.USE", i+1);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_PMx_SV_USE[i], obj_name,str_name);

			// DA Use ...
			str_name.Format("CFG.DA.USE.PM%1d", i+1);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_DA_USE__PMx[i], obj_name,str_name);
		}
	}

	// ROBOT -----
	{
		def_name = "OBJ__ROBOT";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		pROBOT__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

		// Material Status ...
		{
			str_name = "OTR.OUT.MON.dARM_A.MATERIAL.STATUS";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ROBOT_ARM_A_MATERIAL_STATUS, def_data,str_name);

			str_name = "OTR.OUT.MON.dARM_B.MATERIAL.STATUS";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ROBOT_ARM_B_MATERIAL_STATUS, def_data,str_name);
		}
		// DA Offset ...
		{
			str_name = "DA.RESULT.R_OFFSET.DEG";		// deg
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ROBOT_DA_RESULT_R_OFFSET_DEG, def_data,str_name);

			str_name = "DA.RESULT.T_OFFSET.MM";			// mm
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ROBOT_DA_RESULT_T_OFFSET_MM, def_data,str_name); 
		}

		// ARM_RNE.SENSOR ... 
		{
			def_name = "ROBOT.RNE_SNS.ARM_A";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			if((def_data.CompareNoCase(STR__NO)   == 0)
			|| (def_data.CompareNoCase(STR__NULL) == 0))
			{
				bActive__ROBOT_RNE_SNS__ARM_A = false;
			}
			else
			{
				bActive__ROBOT_RNE_SNS__ARM_A = true;

				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name,str_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ROBOT_RNE_SNS__ARM_A, obj_name,str_name);
			}

			//
			def_name = "ROBOT.RNE_SNS.ARM_B";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			if((def_data.CompareNoCase(STR__NO)   == 0)
			|| (def_data.CompareNoCase(STR__NULL) == 0))
			{
				bActive__ROBOT_RNE_SNS__ARM_B = false;
			}
			else
			{
				bActive__ROBOT_RNE_SNS__ARM_B = true;

				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name,str_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ROBOT_RNE_SNS__ARM_B, obj_name,str_name);
			}
		}
		// ARM_RNE.STATE ...
		{
			def_name = "DATA.RNE_ON";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sDATA__RNE_ON = def_data;

			def_name = "DATA.RNE_OFF";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sDATA__RNE_OFF = def_data;
		}
	}

	// TMC CHM -----
	{
		def_name = "OBJ__TMC_CHM";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		//.....
		str_name = "OTR.OUT.MON.aPRESSURE.TORR";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__TMC_CHM_PRESSURE_TORR, def_data,str_name);
	}

	// PMx -----
	{
		def_name = "OBJ__PMC";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		for(i=0;i<m_nPM_LIMIT;i++)
		{
			str_name.Format("OTR.OUT.MON.aPM%1d.PRESSURE.TORR",i+1);
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PMx_PRESSURE_TORR[i], def_data,str_name);

			str_name.Format("OTR.OUT.MON.dPM%1d.SLIT.VALVE.STATUS",i+1);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PMx_SLIT_VALVE_STATUS[i], def_data,str_name);

			//
			str_name.Format("OTR.OUT.MON.dPM%1d.SLOT01.STATUS",i+1);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PMx_SLOT01_STATUS[i], def_data,str_name);

			str_name.Format("OTR.OUT.MON.sPM%1d.SLOT01.TITLE",i+1);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMx_SLOT01_TITLE[i], def_data,str_name);
		}
	}

	if(iActive_SIM > 0)
	{
		CString ch__lotid = "LOTID";
		CString ch__ppid = "PPID";

		// ARM_A ...
		{
			sCH__WFR_INFO_LOTID__ARM_A->Set__DATA(ch__lotid);
			sCH__WFR_INFO_PPID__ARM_A->Set__DATA(ch__ppid);
			sCH__WFR_INFO_MATERIALID__ARM_A->Set__DATA("");
		}
		// ARM_B ...
		{
			sCH__WFR_INFO_LOTID__ARM_B->Set__DATA(ch__lotid);
			sCH__WFR_INFO_PPID__ARM_B->Set__DATA(ch__ppid);
			sCH__WFR_INFO_MATERIALID__ARM_B->Set__DATA("");
		}

		// WAFER ...
		{
			dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Set__DATA(STR__NONE);
			dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Set__DATA(STR__NONE);

			sCH__OTR_OUT_MON__ARM_A_MATERIAL_TITLE->Set__DATA("");
			sCH__OTR_OUT_MON__ARM_B_MATERIAL_TITLE->Set__DATA("");
		}

		if(bActive__ROBOT_RNE_SNS__ARM_A)			dEXT_CH__ROBOT_RNE_SNS__ARM_A->Set__DATA(sDATA__RNE_ON);
		if(bActive__ROBOT_RNE_SNS__ARM_B)			dEXT_CH__ROBOT_RNE_SNS__ARM_B->Set__DATA(sDATA__RNE_ON);
	}

	iFlag__APP_LOG = 1;
	return 1;
}

//--------------------------------------------------------------------------------
int CObj__VAC_ROBOT_STD::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	int flag = 1;

	CString para__arm_type;
	CString para__stn_name;
	CString para__stn_slot;
	CString var_data;

	CStringArray l_para;
	p_variable->Get__FNC_PARAMETER(l_para);

	if(l_para.GetSize() > 0)
	{
		CString para_data;
		int limit = l_para.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			para_data = l_para[i];

			switch(i)
			{
				case 0:		
					dCH__OTR_IN_PARA__ARM_TYPE->Set__DATA(para_data);
					break;

				case 1:
					dCH__OTR_IN_PARA__STN_NAME->Set__DATA(para_data);
					break;

				case 2:
					dCH__OTR_IN_PARA__STN_SLOT->Set__DATA(para_data);
					break;
			}	
		}
	}

	dCH__OTR_IN_PARA__ARM_TYPE->Get__DATA(para__arm_type);
	dCH__OTR_IN_PARA__STN_NAME->Get__DATA(para__stn_name);
	dCH__OTR_IN_PARA__STN_SLOT->Get__DATA(para__stn_slot);

	// ...
	{
		CString log_msg;

		log_msg.Format("Start ... :  [%s] (%s,%s,%s)",
						mode,
						para__arm_type,
						para__stn_name,
						para__stn_slot);

		Fnc__APP_LOG(log_msg);
	}

	// ...
	{
		dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Get__DATA(var_data);
		dEXT_CH__ROBOT_ARM_A_MATERIAL_STATUS->Set__DATA(var_data);

		dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Get__DATA(var_data);
		dEXT_CH__ROBOT_ARM_B_MATERIAL_STATUS->Set__DATA(var_data);
	}

	// Pressure Check -----
	if((mode.CompareNoCase(sMODE__PICK)  == 0)
	|| (mode.CompareNoCase(sMODE__PLACE) == 0))
	{
		CString act_name;
		act_name.Format("%s ing from Arm-%s to %s-%s", 
			            mode, para__arm_type,para__stn_name,para__stn_slot);

		// ...
		int atm_mode = -1;
		
		if((dEXT_CH__CFG_SETUP_TEST_MODE->Check__DATA(STR__ENABLE) > 0)
		|| (dEXT_CH__CFG_TRANSFER_MODE->Check__DATA("ATM") > 0))
		{
			atm_mode = 1;
		}

		if(atm_mode > 0)
		{
			if(Interlock__CHECK_PRESSURE_ATM(p_alarm,para__stn_name,act_name) < 0)
			{
				flag = -1;
			}
		}
		else
		{
			if(Interlock__CHECK_PRESSURE_VAC(p_alarm,para__stn_name,act_name) < 0)
			{
				flag = -1;
			}
		}
	}

	if(flag > 0)
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable,p_alarm);

			if(flag > 0)
			{
				dEXT_CH__ROBOT_ARM_A_MATERIAL_STATUS->Get__DATA(var_data);
				dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Set__DATA(var_data);

				dEXT_CH__ROBOT_ARM_B_MATERIAL_STATUS->Get__DATA(var_data);
				dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Set__DATA(var_data);
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__PICK)
		{
			flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

			if(flag > 0)
			{
				flag = Call__PICK(p_variable,p_alarm, para__arm_type,para__stn_name,para__stn_slot,NORMAL);
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__PLACE)
		{
			flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

			if(flag > 0)
			{
				flag = Call__PLACE(p_variable,p_alarm, para__arm_type,para__stn_name,para__stn_slot,NORMAL);
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__SWAP)
		{
			flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

			if(flag > 0)
			{
				flag = Call__SWAP(p_variable,p_alarm, para__arm_type,para__stn_name,para__stn_slot,NORMAL);
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__ROTATE)
		{	
			flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

			if(flag > 0)
			{
				flag = Call__ROTATE(p_variable,	p_alarm, para__arm_type,para__stn_name,para__stn_slot);
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__HOME)
		{
			flag = Call__HOME(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__MAP)
		{
			flag = Call__MAP(p_variable,p_alarm);

			if(flag > 0)
			{
				dEXT_CH__ROBOT_ARM_A_MATERIAL_STATUS->Get__DATA(var_data);
				dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Set__DATA(var_data);

				dEXT_CH__ROBOT_ARM_B_MATERIAL_STATUS->Get__DATA(var_data);
				dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Set__DATA(var_data);			
			}
		}

		ELSE_IF__CTRL_MODE(sMODE__RETRACT)
		{
			flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

			if(flag > 0)
			{
				flag = Call__RETRACT(p_variable,p_alarm, para__arm_type,para__stn_name,para__stn_slot);
			}

		}
		ELSE_IF__CTRL_MODE(sMODE__EXTEND)
		{
			flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

			if(flag > 0)
			{
				flag = Call__EXTEND(p_variable,	p_alarm, para__arm_type,para__stn_name,para__stn_slot);
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__GOUP)
		{
			flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

			if(flag > 0)
			{
				flag = Call__GOUP(p_variable,p_alarm, para__arm_type,para__stn_name,para__stn_slot);
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__GODOWN)
		{
			flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

			if(flag > 0)
			{
				flag = Call__GODOWN(p_variable,	p_alarm, para__arm_type,para__stn_name,para__stn_slot);
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__RQ_STN)
		{
			flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

			if(flag > 0)
			{
				flag = Call__RQ_STN(p_variable,p_alarm, para__arm_type,para__stn_name);
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__SET_STN)
		{
			flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

			if(flag > 0)
			{
				flag = Call__SET_STN(p_variable,p_alarm, para__arm_type,para__stn_name);
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__TEACHED_CPTR_SAVE)
		{
			flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

			if(flag > 0)
			{
				flag = Call__TEACHED_CPTR_SAVE(p_variable,p_alarm, para__arm_type,para__stn_name);
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__TIME_TEST)
		{
			flag = Call__TIME_TEST(p_variable,p_alarm);
		}
	}


	// Pressure Check -----
	if(flag > 0)
	{
		if((mode.CompareNoCase(sMODE__PICK)  == 0)
		|| (mode.CompareNoCase(sMODE__PLACE) == 0))
		{
			CString act_name;

			if(mode.CompareNoCase(sMODE__PLACE) == 0)
			{
				act_name.Format("place from Arm-%s to %s-%s",
								para__arm_type,para__stn_name,para__stn_slot);
			}
			else
			{
				act_name.Format("pick from %s-%s to Arm-%s",
								para__stn_name,para__stn_slot,para__arm_type);
			}

			// ...
			int atm_mode = -1;

			if((dEXT_CH__CFG_SETUP_TEST_MODE->Check__DATA(STR__ENABLE) > 0)
			|| (dEXT_CH__CFG_TRANSFER_MODE->Check__DATA("ATM") > 0))
			{
				atm_mode = 1;
			}

			if(atm_mode > 0)
			{
				if(Interlock__CHECK_PRESSURE_ATM(p_alarm,para__stn_name,act_name) < 0)
				{
					flag = -1;
				}
			}
			else
			{
				if(Interlock__CHECK_PRESSURE_VAC(p_alarm,para__stn_name,act_name) < 0)
				{
					flag = -1;
				}
			}
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;

		log_msg.Format("Aborted ... :  [%s]",mode);
		Fnc__APP_LOG(log_msg);
	}
	else
	{
		CString log_msg;

		log_msg.Format("Completed ... :  [%s]",mode);
		Fnc__APP_LOG(log_msg);
	}

	return flag;
}

int CObj__VAC_ROBOT_STD::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__STATE_MONITOR:
			Mon__STATE_MONITOR(p_variable,p_alarm);
			break;
	}	
	return 1;
}
