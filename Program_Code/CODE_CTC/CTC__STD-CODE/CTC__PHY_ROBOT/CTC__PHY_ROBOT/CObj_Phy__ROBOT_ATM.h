#pragma once

#include "Interface_Code.h"

#include "CCommon_System.h"
#include "CCommon_Error.h"


#define  ALID__OBJECT_MODE_UNKNOWN					11


class CObj_Phy__ROBOT_ATM : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------
	CString sObject_Name;

	int iACTIVE__SIM_MODE;

	// ...
	CCommon_Error__MODULE_OBJ   mERROR__MODULE_OBJ;
	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;

	// ...
	SCX__CTC__MODULE_OBJ xI_Module_Obj;
	SCX__CTC__MODULE_OBJ xI_Upper_Obj;

	SCX__USER_LOG_CTRL xI_LOG_CTRL;

	SCX__CTC__SCH_MATERIAL_CTRL xI_SCH_MATERIAL_CTRL;

	CString sDir_ROOT;
	CString sDir_WFR_DATA;

	// ...
	bool bActive__LLx_MULTI_SLOT_VALVE;
	//


	//-------------------------------------------------------------------
	// INTERNAL VARIABLE

	// REMOTE CONTROL ...
	int iUPPER_OBJ__FLAG;

	CX__VAR_DIGITAL_CTRL xCH__UPPER_OBJ__CTRL;
	CX__VAR_DIGITAL_CTRL xCH__UPPER_OBJ__MODE;
	CX__VAR_STRING_CTRL  xCH__UPPER_OBJ__STATUS;

	CX__VAR_STRING_CTRL  xCH__UPPER_OBJ__PARA_MODULE;
	CX__VAR_STRING_CTRL  xCH__UPPER_OBJ__PARA_PLACE_ARM;
	CX__VAR_STRING_CTRL  xCH__UPPER_OBJ__PARA_PLACE_SLOT;
	CX__VAR_STRING_CTRL  xCH__UPPER_OBJ__PARA_PICK_ARM;
	CX__VAR_STRING_CTRL  xCH__UPPER_OBJ__PARA_PICK_SLOT;

	// ...
	CX__VAR_DIGITAL_CTRL xCH__OBJ_CTRL;
	CX__VAR_DIGITAL_CTRL dCH__OBJ_MODE;

	CX__VAR_DIGITAL_CTRL dCH__PARA_ARM_TYPE;
	CX__VAR_DIGITAL_CTRL dCH__PARA_MODULE;
	CX__VAR_DIGITAL_CTRL dCH__PARA_SLOT;
	CX__VAR_DIGITAL_CTRL dCH__PARA_POS;

	//
	CX__VAR_ANALOG_CTRL  aCH__CFG_ALIGN_RETRY;
	CX__VAR_STRING_CTRL  sCH__CUR_ALIGN_RETRY;

	CX__VAR_DIGITAL_CTRL dCH__TARGET_PMx_MODE;

	CX__VAR_DIGITAL_CTRL dCH__TARGET_LLx_MODE;
	CX__VAR_DIGITAL_CTRL dCH__TARGET_LLx_SLOT_CHECK;

	CX__VAR_STRING_CTRL  sCH__TARGET_LLx_NAME_SET_OF_ARM_A;
	CX__VAR_STRING_CTRL  sCH__TARGET_LLx_SLOT_SET_OF_ARM_A;

	CX__VAR_STRING_CTRL  sCH__TARGET_LLx_NAME_SET_OF_ARM_B;
	CX__VAR_STRING_CTRL  sCH__TARGET_LLx_SLOT_SET_OF_ARM_B;

	CX__VAR_STRING_CTRL  sCH__TARGET_LLx_NAME_SET_AL;
	CX__VAR_STRING_CTRL  sCH__TARGET_LLx_SLOT_SET_AL;

	CX__VAR_STRING_CTRL  sCH__TARGET_LLx_NAME_GET;
	CX__VAR_STRING_CTRL  sCH__TARGET_LLx_SLOT_GET;

	CX__VAR_STRING_CTRL  sCH__TARGET_LLx_ANGLE_GET;

	// STATUS
	CX__VAR_STRING_CTRL xCH__OBJ_STATUS;

	CX__VAR_DIGITAL_CTRL xCH__SLOT_STATUS[CFG_ROBOT__ARM_SIZE];
	CX__VAR_STRING_CTRL  xCH__SLOT_TITLE[CFG_ROBOT__ARM_SIZE];

	CX__VAR_STRING_CTRL  xCH__MATERIAL_SIZE[CFG_ROBOT__ARM_SIZE];

	// MATERIAL INFO
	CX__VAR_STRING_CTRL  xCH__SLOT_LPx_PTN[CFG_ROBOT__ARM_SIZE];
	CX__VAR_STRING_CTRL  xCH__SLOT_LPx_STN[CFG_ROBOT__ARM_SIZE];
	CX__VAR_STRING_CTRL  xCH__SLOT_PPID[CFG_ROBOT__ARM_SIZE];
	CX__VAR_STRING_CTRL  xCH__SLOT_LOTID[CFG_ROBOT__ARM_SIZE];
	CX__VAR_STRING_CTRL  xCH__SLOT_MATERIALID[CFG_ROBOT__ARM_SIZE];

	CX__VAR_STRING_CTRL  xCH__DVID_SLOT_LPx_PTN[CFG_ROBOT__ARM_SIZE];
	CX__VAR_STRING_CTRL  xCH__DVID_SLOT_LPx_STN[CFG_ROBOT__ARM_SIZE];
	CX__VAR_STRING_CTRL  xCH__DVID_SLOT_PPID[CFG_ROBOT__ARM_SIZE];
	CX__VAR_STRING_CTRL  xCH__DVID_SLOT_LOTID[CFG_ROBOT__ARM_SIZE];
	CX__VAR_STRING_CTRL  xCH__DVID_SLOT_MATERIALID[CFG_ROBOT__ARM_SIZE];

	// ANIMATION
	CX__VAR_STRING_CTRL  sCH__ANI_VIRTUAL_TRG_MOVE;
	CX__VAR_DIGITAL_CTRL dCH__ANI_TRG_MOVE;
	CX__VAR_STRING_CTRL  sCH__ANI_VIRTUAL_TRG_ROTE;
	CX__VAR_DIGITAL_CTRL dCH__ANI_TRG_ROTE;
	CX__VAR_DIGITAL_CTRL dCH__ANI_ROTE_ARM;

	CX__VAR_DIGITAL_CTRL dCH__ANI_ARM_A_ACT;
	CX__VAR_DIGITAL_CTRL dCH__ANI_ARM_B_ACT;
	CX__VAR_DIGITAL_CTRL dCH__ANI_ARM_C_ACT;
	CX__VAR_DIGITAL_CTRL dCH__ANI_ARM_D_ACT;

	// LLx : Scheduler - Dual Only Input & Output ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_LLx_CTRL_ONLY_INPUT_OUTPUT_MODE;

	CX__VAR_DIGITAL_CTRL dCH__CFG_DUAL_ARM_MOVING_AT_THE_SAME_TIME;
	CX__VAR_DIGITAL_CTRL dCH__CFG_DUAL_ARM_MOVING_AT_LPx;
	CX__VAR_DIGITAL_CTRL dCH__CFG_DUAL_ARM_MOVING_AT_STx;
	CX__VAR_DIGITAL_CTRL dCH__CFG_DUAL_ARM_MOVING_AT_LLx;

	// LLx : CONTRAINT ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_LL_CONSTRAINT_1;
	CX__VAR_DIGITAL_CTRL dCH__CFG_LL_CONSTRAINT_2;

	// CFG : WAFER PICK PARAMETER ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_PICK_WAFER_CONDITION;

	// CONFIG ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_ARM_USE_FLAG_X[CFG_ROBOT__ARM_SIZE];

	// SIM CFG ...
	CX__VAR_ANALOG_CTRL aCH__SCH_TEST_CFG_PICK_LPx_SEC;
	CX__VAR_ANALOG_CTRL aCH__SCH_TEST_CFG_PICK_ALx_SEC;
	CX__VAR_ANALOG_CTRL aCH__SCH_TEST_CFG_PICK_LLx_SEC;
	CX__VAR_ANALOG_CTRL aCH__SCH_TEST_CFG_PICK_STx_SEC;

	CX__VAR_ANALOG_CTRL aCH__SCH_TEST_CFG_PLACE_LPx_SEC;
	CX__VAR_ANALOG_CTRL aCH__SCH_TEST_CFG_PLACE_ALx_SEC;
	CX__VAR_ANALOG_CTRL aCH__SCH_TEST_CFG_PLACE_LLx_SEC;
	CX__VAR_ANALOG_CTRL aCH__SCH_TEST_CFG_PLACE_STx_SEC;

	CX__VAR_ANALOG_CTRL aCH__SCH_TEST_CFG_INIT_SEC;
	CX__VAR_ANALOG_CTRL aCH__SCH_TEST_CFG_HOME_SEC;
	CX__VAR_ANALOG_CTRL aCH__SCH_TEST_CFG_LP_MAP_SEC;

	// INFO 
	CX__VAR_STRING_CTRL xCH__MODULE_TIME;

	CX__VAR_STRING_CTRL sCH__TIME_ACT_START;
	CX__VAR_STRING_CTRL sCH__TIME_ACT_END;
	CX__VAR_STRING_CTRL sCH__TIME_ACT_TACK;
	CX__VAR_STRING_CTRL sCH__TIME_ACT_RESULT;

	// INFO.LLx ...
	CX__VAR_DIGITAL_CTRL dCH__INFO_LL_RESERVE_X[CFG_LLx_LIMIT];

	// ...
	SCI__THREAD_SYNC_CTRL xI_Sync_Ctrl;
	int iPRC_STS;

	CString sPara0__Arm_Type;
	CString sPara1__Module;
	CString sPara2__Slot;
	CString sPara3__Pos;
	//

	//-----------------------------------------------------------
	// EXTERNAL PROPERTY

	// DB_CFG ...
	CString sSCH_NAME;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC;

	// OBJ_LPx ...
	int iLPx_SIZE;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__LPx[CFG_LP_LIMIT];

	CX__VAR_DIGITAL_CTRL dEXT_CH__LPx_DOOR_STATUS[CFG_LP_LIMIT];
	CX__VAR_DIGITAL_CTRL dEXT_CH__LPx_SLOTx_STATUS[CFG_LP_LIMIT][CFG_LP__SLOT_MAX];

	// OBJ_ALx ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__AL1;
	CX__VAR_DIGITAL_CTRL dEXT_CH__AL1_SLOTx_STATUS[CFG_AL__SLOT_MAX];
	CX__VAR_STRING_CTRL  sEXT_CH__AL1_SLOTx_TITLE[CFG_AL__SLOT_MAX];

	// OBJ_LLx ...
	int iLLx_SIZE;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__LLx[CFG_LLx_LIMIT];

	CX__VAR_DIGITAL_CTRL dEXT_CH__LLx_DOOR_STATUS[CFG_LLx_LIMIT];
	CX__VAR_DIGITAL_CTRL dEXT_CH__LLx_DOOR_STATUS_X[CFG_LLx_LIMIT][CFG_LLx__SLOT_MAX];

	CX__VAR_DIGITAL_CTRL dEXT_CH__LLx_SLOTx_STATUS[CFG_LLx_LIMIT][CFG_LLx__SLOT_MAX];
	CX__VAR_STRING_CTRL  sEXT_CH__LLx_SLOTx_TITLE[CFG_LLx_LIMIT][CFG_LLx__SLOT_MAX];

	// OBJ_STx ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__ST1;
	CX__VAR_DIGITAL_CTRL dEXT_CH__ST1_SLOTx_STATUS[CFG_LP__SLOT_MAX];
	CX__VAR_STRING_CTRL  sEXT_CH__ST1_SLOTx_TITLE[CFG_LP__SLOT_MAX];

	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__ST2;
	CX__VAR_DIGITAL_CTRL dEXT_CH__ST2_SLOTx_STATUS[CFG_LP__SLOT_MAX];
	CX__VAR_STRING_CTRL  sEXT_CH__ST2_SLOTx_TITLE[CFG_LP__SLOT_MAX];
	//


	//-------------------------------------------------------------------
	// ROBOT

	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__HOME;
	int  Call__HOME(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__MAINT;
	int  Call__MAINT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PICK;
	int  Call__PICK(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__XPICK;
	int  Call__XPICK(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PLACE;
	int  Call__PLACE(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__XPLACE;
	int  Call__XPLACE(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__ROTATE;
	int  Call__ROTATE(CII_OBJECT__VARIABLE* p_variable);

	// SWAP
	CString sMODE__SWAP_PMx;
	int  Call__SWAP_PMx(CII_OBJECT__VARIABLE* p_variable);

	// ROBOT & MODULE	
	CString sMODE__SWAP_ALx;
	int  Call__SWAP_ALx(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__SWAP_LBx;
	int  Call__SWAP_LBx(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__SWAP_VISx;
	int  Call__SWAP_VISx(CII_OBJECT__VARIABLE* p_variable);

	// 
	CString sMODE__LP_MAP;
	int  Call__LP_MAP(CII_OBJECT__VARIABLE* p_variable);

	// SCH_TEST : CONFIG ...
	CString sMODE__SCH_TEST_CFG;
	int  Call__SCH_TEST_CFG(CII_OBJECT__VARIABLE* p_variable);
	//

	// ...
	int  Fnc__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable, const CString obj_mode);
	int  Sim__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable, const CString obj_mode);

	int  Sim__PICK_MATERIAL(const bool act_start, const bool ex_mode);
	int  Sim__PLACE_MATERIAL(const bool act_start, const bool ex_mode);

	int  Get__ARMx_INDEX(const CString& str_arm);
	int  Get__ARMx_INDEX_LIST(const CString& str_arm, CUIntArray& l_arm_index);
	int  Get__ALx_INDEX(const CString& str_module);
	int  Get__LLx_INDEX(const CString& str_module);
	int  Get__STx_INDEX(const CString& str_module);
	int  Get__LPx_INDEX(const CString& str_module);
	//

	// ...
	void Mon__MODULE_STATUS(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	void Fnc__SET_TIME();
	void Fnc__SET_ANI_ARM(CII_OBJECT__VARIABLE* p_variable);

	int  Fnc__WAIT_SEC(CII_OBJECT__VARIABLE* p_variable,CII__VAR_ANALOG_CTRL* pch_analog_cfg);

	// ...
	void Update__MATERIAL_INFO();

	void Report__MATERIAL_INFO(const CString& mode);
	void _Report__MATERIAL_INFO(const CString& mode, const CString& arm_type);
	void _Report__LPx_MATERIAL_INFO(const CString& mode, const CString& arm_type,const int lp_id,const int lp_slot, const bool active_wfr);
	void _Report__ALx_MATERIAL_INFO(const CString& mode, const CString& arm_type,const int al_id,const int al_slot, const int lp_id,const int lp_slot);
	void _Report__MDx_MATERIAL_INFO(const CString& mode, const CString& arm_type,const CString& md_id,const CString& md_slot, const int lp_id,const int lp_slot);

	CString _Get__MDx_ACTION_INFO(const CString& act_mode, const CString& arm_type,const CString& md_name, const CString& act_log);
	void _Save__MATERIAL_INFO(const int lp_id,
							  const int lp_slot, 
							  const CString& wfr_info);

	// ...
	int _Query__GET_EMPTY_ARM(const CString& query_name,CStringArray& l_data);
	//


public:
	CObj_Phy__ROBOT_ATM();
	~CObj_Phy__ROBOT_ATM();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);

	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	int __START__OBJECT();

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);

	//-------------------------------------------------------------------------
	int __Define__QUERY(CStringArray& l_query);

	int __Call__QUERY_LIST(const CString& query_name,CStringArray& l_data);
	int __Call__QUERY_LIST(const CString& query_name,const CStringArray& l_sub_query, CStringArray& l_data);
};

