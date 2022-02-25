#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"

#include "CObj_Opr__MAINT_MODE__DEF.h"


// ...
#define  ALID__OBJECT_MODE_UNKNOWN					11

// ...
#define  _CMMD__MACRO_MOVE__MANUAL_MOVE				1
#define  _CMMD__MACRO_MOVE__TOOL_CLEAR				2
#define  _CMMD__MACRO_MOVE__PROCESS					3
#define  _CMMD__MACRO_MOVE__LOOP					4
#define  _CMMD__MACRO_MOVE__ERROR					101


class CDB__MACRO_LOG
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CUIntArray   iList__CMMD_TYPE;
	CStringArray sList__PARA_1;
	CStringArray sList__PARA_2;
	CStringArray sList__PARA_3;
	CStringArray sList__PARA_4;

public:
	CDB__MACRO_LOG()
	{
		InitializeCriticalSection(&mCS_LOCK);
	}
	~CDB__MACRO_LOG()
	{
		DeleteCriticalSection(&mCS_LOCK);
	}

	void Clear__ALL_HISTORY()
	{
		EnterCriticalSection(&mCS_LOCK);

		// ...
		{
			iList__CMMD_TYPE.RemoveAll();
			
			sList__PARA_1.RemoveAll();
			sList__PARA_2.RemoveAll();
			sList__PARA_3.RemoveAll();
			sList__PARA_4.RemoveAll();
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
	int  Get__HISTORY_COUNT()
	{
		int count = 0;

		EnterCriticalSection(&mCS_LOCK);

		// ...
		{
			count = iList__CMMD_TYPE.GetSize();
		}

		LeaveCriticalSection(&mCS_LOCK);
		return count;
	}
	void Load__MOVE_INFO(const int cmmd_type,
						 const CString& str__para_1,
						 const CString& str__para_2,
						 const CString& str__para_3,
						 const CString& str__para_4)   
	{
		EnterCriticalSection(&mCS_LOCK);

		// ...
		{
			iList__CMMD_TYPE.Add(cmmd_type);

			sList__PARA_1.Add(str__para_1);
			sList__PARA_2.Add(str__para_2);
			sList__PARA_3.Add(str__para_3);
			sList__PARA_4.Add(str__para_4);
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Get__ALL_MOVE_HISTORY(CUIntArray&   l_cmmd_type,
							   CStringArray& l_para_1,
							   CStringArray& l_para_2,
							   CStringArray& l_para_3,
							   CStringArray& l_para_4)
	{
		EnterCriticalSection(&mCS_LOCK);

		// ...
		{
			l_cmmd_type.Copy(iList__CMMD_TYPE);

			l_para_1.Copy(sList__PARA_1);
			l_para_2.Copy(sList__PARA_2);
			l_para_3.Copy(sList__PARA_3);
			l_para_4.Copy(sList__PARA_4);
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
};


// ...
#define CFG_SIZE__MOVE_HISTORY				20


class CObj_Opr__MAINT_MODE : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__USER_FNC mERROR__USER_FNC;
	SCX__USER_LOG_CTRL xAPP_LOG_CTRL;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_STRING_CTRL xCH__OBJ_MSG;
	CX__VAR_STRING_CTRL xCH__ACTIVE_MODE;

	CStringArray sList__ATM_AREA;
	CStringArray sList__ATM_RB_AREA;
	CStringArray sList__LPx_AREA;
	CStringArray sList__ALx_AREA;
	CStringArray sList__BUFFx_AREA;
	CStringArray sList__VISx_AREA;
	CStringArray sList__LBx_AREA;

	CStringArray sList__VAC_AREA;
	CStringArray sList__VAC_RB_AREA;
	CStringArray sList__PMx_AREA;

	// ...
	CX__VAR_STRING_CTRL  sCH__PARTICLE_PARA_SELECT_MODE;

	CX__VAR_STRING_CTRL  sCH__PARTICLE_PARA_SRC_MODULE;
	CX__VAR_STRING_CTRL  sCH__PARTICLE_PARA_SRC_SLOT;
	CX__VAR_DIGITAL_CTRL dCH__PARTICLE_PARA_TRG_MODULE;

	CX__VAR_ANALOG_CTRL  aCH__PARTICLE_PARA_DELAY_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARTICLE_PARA_DELAY_COUNT;

	//
	CX__VAR_DIGITAL_CTRL dCH__PARTICLE_PARA_PRC_APPLY;
	CX__VAR_STRING_CTRL  sCH__PARTICLE_DATA_PRC_APPLY;

	CX__VAR_DIGITAL_CTRL dCH__PARTICLE__PROCESS_PMx;
	CX__VAR_STRING_CTRL  sCH__PARTICLE_PARA_PMx_RECIPE[CFG_PM_LIMIT];
	CX__VAR_STRING_CTRL  sCH__PARTICLE_PARA_PMx_RCP_CLN[CFG_PM_LIMIT];
	CX__VAR_STRING_CTRL  sCH__PARTICLE_PARA_PMx_RCP_PRE[CFG_PM_LIMIT];
	CX__VAR_STRING_CTRL  sCH__PARTICLE_PARA_LLx_RECIPE[CFG_LLx_LIMIT];
	CX__VAR_STRING_CTRL  sCH__PARTICLE_PARA_LLx_RCP_CLN[CFG_LLx_LIMIT];
	CX__VAR_STRING_CTRL  sCH__PARTICLE_PARA_LLx_RCP_PRE[CFG_LLx_LIMIT];

	// CX__VAR_DIGITAL_CTRL dCH__PARTICLE_PARA_CYCLE_MODULE;
	CX__VAR_STRING_CTRL  sCH__PARTICLE_DATA_CYCLE_MODULE;

	CX__VAR_ANALOG_CTRL  aCH__PARTICLE_PARA_CYCLE_COUNT;
	CX__VAR_STRING_CTRL  sCH__PARTICLE_DATA_CYCLE_COUNT;

	CX__VAR_ANALOG_CTRL  aCH__PARTICLE_PARA_VAC_ROBOT_CFG_TIME_SEC;
	CX__VAR_STRING_CTRL  sCH__PARTICLE_PARA_VAC_ROBOT_CUR_TIME_COUNT;

	// ...
	CDB__MACRO_LOG mMacro_Log;

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__LOG_STATUS;		// START STOP	
	CX__VAR_ANALOG_CTRL  aCH__MACRO_MOVE__CYCLE_COUNT;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__CUR_CYCLE_COUNT;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__LOG_VIEW_REQ;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__LOG_SAVE_REQ;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__LOG_FILE_NAME;

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__HISTORY[CFG_SIZE__MOVE_HISTORY];
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__LOG_COUNT;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__SCR_NAME;

	CX__VAR_ANALOG_CTRL  aCH__MACRO_MOVE__CFG_FOUP_WAIT_SEC;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__FOUP_WAIT_CUR_SEC;
	CX__VAR_ANALOG_CTRL  aCH__MACRO_MOVE__CFG_PMC_WAIT_SEC;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__PMC_WAIT_CUR_SEC;
	CX__VAR_ANALOG_CTRL  aCH__MACRO_MOVE__CFG_BUFFER_WAIT_SEC;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__BUFFER_WAIT_CUR_SEC;

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__ATM_RB_MOVE_POS__CENTER;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__ATM_RB_ARM_ACT__RETRACT;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__VAC_RB_ARM_TYPE__A;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__VAC_RB_ROT_POS__CENTER;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__VAC_RB_ARM_ACT__RETRACT;

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__EDITOR_ACTION_NAME[CFG_SIZE__MOVE_HISTORY];
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__EDITOR_CUR_INDEX;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__EDITOR_CHANGE_FLAG;

	//
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__MOVE_SELECT;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__SRC_SLOT;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__SRC_MODULE;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__TRG_SLOT;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__TRG_MODULE;

	CX__VAR_ANALOG_CTRL  aCH__MACRO_MOVE__LOOP_START;
	CX__VAR_ANALOG_CTRL  aCH__MACRO_MOVE__LOOP_END;
	CX__VAR_ANALOG_CTRL  aCH__MACRO_MOVE__LOOP_REPEAT;

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__STEP_REPEAT_START;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__STEP_REPEAT_END;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__STEP_REPEAT_COUNT;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__STEP_REPEAT_INDEX;

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__PROCESS_ROUTE;
	CX__VAR_DIGITAL_CTRL dCH__MACRO_MOVE__PROCESS_PMx;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__PROCESS_PRE_RECIPE_PMx[CFG_PM_LIMIT];
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__PROCESS_MAIN_RECIPE_PMx[CFG_PM_LIMIT];
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__PROCESS_POST_RECIPE_PMx[CFG_PM_LIMIT];
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__PROCESS_PRE_RECIPE_LLx[CFG_LLx_LIMIT];
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__PROCESS_MAIN_RECIPE_LLx[CFG_LLx_LIMIT];
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__PROCESS_POST_RECIPE_LLx[CFG_LLx_LIMIT];

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__OBJ_STATUS__STANDBY;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__PRESSURE_STATUS__VAC;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__DOOR_STATUS__CLOSE;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__DOOR_STATUS__OPEN;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__CST_STATUS__EXIST;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__CST_POS__LOAD;

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__EDITOR_ACT_CMMD;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__FILE_ACT_CMMD;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__FILE_NAME;

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__ACTION_SELECT;

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__PMC_SLOT_STATUS[CFG_PM_LIMIT];
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__PMC_SLOT_TITLE[CFG_PM_LIMIT];

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__VAC_RB__A_ARM_SLOT_STATUS;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__VAC_RB__A_ARM_SLOT_TITLE;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__VAC_RB__B_ARM_SLOT_STATUS;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__VAC_RB__B_ARM_SLOT_TITLE;

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__ATM_RB__A_ARM_SLOT_STATUS;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__ATM_RB__A_ARM_SLOT_TITLE;

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__ATM_RB__B_ARM_SLOT_STATUS;
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__ATM_RB__B_ARM_SLOT_TITLE;

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__LLx_SLOT_STATUS[CFG_LLx_LIMIT][CFG_LLx__SLOT_MAX];
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__LLx_SLOT_TITLE[CFG_LLx_LIMIT][CFG_LLx__SLOT_MAX];

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__AL_SLOT_STATUS[CFG_AL__SLOT_MAX];
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__AL_SLOT_TITLE[CFG_AL__SLOT_MAX];

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__BUFFER1_SLOT_STATUS[CFG_BUFFER__SLOT_MAX];
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__BUFFER1_SLOT_TITLE[CFG_BUFFER__SLOT_MAX];

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__BUFFER2_SLOT_STATUS[CFG_BUFFER__SLOT_MAX];
	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__BUFFER2_SLOT_TITLE[CFG_BUFFER__SLOT_MAX];

	CX__VAR_STRING_CTRL  sCH__MACRO_MOVE__LPx_SLOT_STATUS[CFG_LP_LIMIT][CFG_LP__SLOT_MAX];

	// ...
	CString sVAR_PARA__MOVE_SELECT;

	CX__VAR_STRING_CTRL  sCH__PARA_SRC_MODULE;
	CX__VAR_STRING_CTRL  sCH__PARA_SRC_SLOT;

	CX__VAR_STRING_CTRL  sCH__PARA_TRG_MODULE;
	CX__VAR_STRING_CTRL  sCH__PARA_TRG_SLOT;
	//

	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// LPx - OBJ ...
	int iLPx_SIZE;
	CX__VAR_STRING_CTRL sEXT_CH__LPx_LOCK_FLAG[CFG_LP_LIMIT];

	// ATM RB - OBJ ...
	CII_EXT_OBJECT__CTRL *pATM_RB__OBJ_CTRL;

	CX__VAR_STRING_CTRL  sEXT_CH__TARGET_LLx_NAME;
	CX__VAR_STRING_CTRL  sEXT_CH__TARGET_LLx_SLOT;

	CX__VAR_STRING_CTRL  sEXT_CH__ATM_RB__CHECK_MODULE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__ATM_RB__CFG_BUFFER_USE_DURING_MAINT_MODE;

	// VAC_RB - OBJ ...
	CII_EXT_OBJECT__CTRL *pVAC_RB__OBJ_CTRL;

	CX__VAR_STRING_CTRL  sEXT_CH__VAC_RB__CHECK_MODULE;	

	// PMx - OBJ ...
	int iPMx_SIZE;
	CII_EXT_OBJECT__CTRL *pPMx__OBJ_CTRL[CFG_PM_LIMIT];

	// LLx - OBJ ...
	int iLLx_SIZE;
	CII_EXT_OBJECT__CTRL *pLLx__OBJ_CTRL[CFG_LLx_LIMIT];

	CX__VAR_STRING_CTRL  sEXT_CH__LLx_PARA_PROC_RECIPE_NAME[CFG_LLx_LIMIT];
	CX__VAR_STRING_CTRL  sEXT_CH__LLx_PARA_PROC_SCH_NAME[CFG_LLx_LIMIT];
	//


	//-------------------------------------------------------------------------
	CString sMODE__MANUAL_MOVE;
	int  Call__MANUAL_MOVE(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__TOOL_CLEAR;
	int  Call__TOOL_CLEAR(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__PARTICLE_CHECK;
	int  Call__PARTICLE_CHECK(CII_OBJECT__VARIABLE *p_variable);

	CString sMODE__MACRO_MOVE;
	int  Call__MACRO_MOVE(CII_OBJECT__VARIABLE *p_variable);

	// ...
	void Mon__MACRO_MOVE_CTRL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	void Fnc__MACRO_MOVE_EDITOR(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	void Fnc__MOVE_HISTORY_TO_SCR();

	void Fnc__MACRO_MOVE_CHANGE_INFO();
	void Fnc__MACRO_MOVE_INIT_INFO();
	void Fnc__MACRO_MOVE_EDITOR_CLEAR();
	void Fnc__MACRO_MOVE_WAFER_RESET();

	// ...
	int  Fnc__ATM_RB__Manual_Move_To(CII_OBJECT__VARIABLE *p_variable,
									 const CString& s_module,
									 const CString& s_slot,
									 CString& t_module,CString& t_slot);

	int  ATM_RB__Pick_Module_With_Arm(CII_OBJECT__VARIABLE *p_variable,
									  CString& arm_type,
									  const CString& s_module,
									  const CString& s_slot);

	int  ATM_RB__Pick_Module(CII_OBJECT__VARIABLE *p_variable,
		                     const CString& str_module,
							 const CString& str_slot,
							 CString& arm_type);

	int  ATM_RB__Place_Module(CII_OBJECT__VARIABLE *p_variable,
		                      const CString& arm_type,
							  CString& str_module,
							  CString& str_slot,
							  const bool active__al_retry = true);

	// ...
	int  Fnc__VAC_RB__Manual_Move_To(CII_OBJECT__VARIABLE *p_variable,
									 const CString& s_module,const CString& s_slot,
									 CString& t_module,CString& t_slot);

	int  VAC_RB__Pick_Module_With_Arm(CII_OBJECT__VARIABLE *p_variable,
									  CString& arm_type,const CString& s_module,const CString& s_slot);

	int  VAC_RB__Pick_Module(CII_OBJECT__VARIABLE *p_variable,
							 const CString& str_module,const CString& str_slot,CString& arm_type);

	int  VAC_RB__Place_Module(CII_OBJECT__VARIABLE *p_variable,
							  const CString& arm_type,CString& str_module,CString& str_slot);

	// ...
	int  Seq__ATM_RB__Place(CII_OBJECT__VARIABLE* p_variable,
							const CString& arm_type,
							const CString& str_module,
							const CString& str_slot);
	int  Seq__ATM_RB__Pick(CII_OBJECT__VARIABLE* p_variable,
							const CString& arm_type,
							const CString& str_module,
							const CString& str_slot);

	// ...
	CString Get__ATM_RB1__ARM_TYPE(const CString& str_arm);
	CString Get__VAC_RB1__ARM_TYPE(const CString& str_arm);

	int  Get__LLx_INDEX(const CString str_module);
	CString Get__LLx_NAME(const int ll_i);
	CString Get__LLx_NAME(const CString& ll_name);

	bool Check__LLx_ISLOT(const CString str_module, CString& ll_name,CString& ll_slot);
	//

public:
	CObj_Opr__MAINT_MODE();
	~CObj_Opr__MAINT_MODE();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);
	
	int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_def_fnc);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
