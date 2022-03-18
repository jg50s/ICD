#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"
#include "CCommon_LEARNED_ITEM.h"

#include "CObj__PROC_STD__ALID.h"
#include "CObj__PROC_STD__DEF.h"


class CObj__PROC_STD : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	// ...
	SCX__USER_LOG_CTRL xI_LOG_CTRL;

	CDS__LEARNED_ITEM_CTRL mCTRL__LEARNED_ITEM;

	// ...
	int iActive__PROC_START;

	SCX__RECIPE_FILE xRCP__FILE_CTRL;
	CString sDir_PROC;

	int iActive__SIM_MODE;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// OBJ ...
	CX__VAR_STRING_CTRL	 sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL	 sCH__OBJ_TIMER;

	// CTC REPORT ...
	CX__VAR_STRING_CTRL  sCH__PRC_TOTAL_TIME_TO_CTC;
	CX__VAR_STRING_CTRL  sCH__PRC_CHANGE_TIME_TO_CTC;

	// PARA ...
	CX__VAR_DIGITAL_CTRL dCH__PARA_MANUAL_PROCESS_DECHUCK_ACTIVE;

	CX__VAR_DIGITAL_CTRL dCH__PARA_MANUAL_STEP_CTRL_ACTIVE;
	CX__VAR_STRING_CTRL  sCH__PARA_MANUAL_STEP_CTRL_REQ;

	CX__VAR_STRING_CTRL  sCH__ACT_RECOVERY_RESTART_FLAG;

	// LEARNED INFO ... 
	CX__VAR_DIGITAL_CTRL dCH__CFG_LEARNED_APPLY_MODE;
	CX__VAR_STRING_CTRL  sCH__CUR_LEARNED_RESULT;

	CX__VAR_STRING_CTRL  sCH__PRE_LOTID;
	CX__VAR_STRING_CTRL  sCH__CUR_LEARNED_APPLY_STATUS;
	
	CX__VAR_STRING_CTRL  sCH__RCP_FILE_UPLOAD_FLAG;

	// WIN.JUMP_STEP ...
	CX__VAR_ANALOG_CTRL  aCH__JUMP_STEP_ID;
	CX__VAR_ANALOG_CTRL  aCH__CONTINUE_OVER_STEP_TIME;
	CX__VAR_STRING_CTRL  sCH__EXCEPTION_CONTINUE_REQ;

	CX__VAR_STRING_CTRL  sCH__WIN_CTRL_JUMP_PAGE;
	CX__VAR_STRING_CTRL  sCH__WIN_CTRL_MSG;

	CX__VAR_DIGITAL_CTRL dCH__WIN_CTRL_LOCK_ACTIVE_JUMP;
	CX__VAR_DIGITAL_CTRL dCH__WIN_CTRL_LOCK_ACTIVE_CONTINUE;
	CX__VAR_DIGITAL_CTRL dCH__WIN_CTRL_LOCK_ACTIVE_ABORT;

	// MON ...
	CX__VAR_DIGITAL_CTRL dCH__MON_LOCK_ACTIVE_ABORT;
	CX__VAR_DIGITAL_CTRL dCH__MON_LOCK_ACTIVE_END;
	CX__VAR_DIGITAL_CTRL dCH__MON_LOCK_ACTIVE_SKIP;
	CX__VAR_DIGITAL_CTRL dCH__MON_LOCK_ACTIVE_JUMP;
	CX__VAR_DIGITAL_CTRL dCH__MON_LOCK_ACTIVE_PAUSE;
	CX__VAR_DIGITAL_CTRL dCH__MON_LOCK_ACTIVE_RESUME;

	CX__VAR_DIGITAL_CTRL dCH__MON_EXCEPTION_ACT;
	CX__VAR_STRING_CTRL  sCH__MON_EXCEPTION_MSG;

	// CUR ...
	CX__VAR_STRING_CTRL  sCH__CUR_RCP_FILE_PATH;
	CX__VAR_DIGITAL_CTRL dCH__CUR_PROCESS_TYPE;

	// Loop Parameter ...
	bool bACTIVE__LOOP_STEP;

	int iLOOP__STEP_START;
	int iLOOP__STEP_END;
	int iLOOP__STEP_REPEAT;
	int iLOOP__STEP_COUNT;

	// Recipe Info ...
	CX__VAR_STRING_CTRL  sCH__PRC_TOTAL_TIME;
	CX__VAR_STRING_CTRL  sCH__PRC_CUR_TIME;
	CX__VAR_STRING_CTRL  sCH__STEP_CUR_TIME;
	CX__VAR_ANALOG_CTRL  aCH__STEP_TOTAL_NUM;
	CX__VAR_ANALOG_CTRL  aCH__STEP_CUR_NUM;
	CX__VAR_STRING_CTRL  sCH__STEP_LOOP_MSG;

	CX__VAR_ANALOG_CTRL  aCH__RCP_JUMP_STEP_ID;

	// Recipe Parameter ...
	CX__VAR_DIGITAL_CTRL dCH__RCP_STEP_MODE;

	CX__VAR_ANALOG_CTRL  aCH__RCP_LOOP_START;
	CX__VAR_ANALOG_CTRL  aCH__RCP_LOOP_REPEAT;
	//

	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// OBJ_THIS ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__OBJ_CTRL;

	// OBJ : DB_INF
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PROCESS_STATUS;

	CX__VAR_STRING_CTRL  sEXT_CH__RCP_NAME;

	CX__VAR_STRING_CTRL  sEXT_CH__PRC_TOTAL_TIME_TO_CTC;
	CX__VAR_STRING_CTRL  sEXT_CH__PRC_CHANGE_TIME_TO_CTC;

	CX__VAR_DIGITAL_CTRL dEXT_CH__SLOT01_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__SLOT01_TITLE;

	CX__VAR_STRING_CTRL  sEXT_CH__SLOT01_LOTID;
	CX__VAR_STRING_CTRL  sEXT_CH__SLOT01_MATERIALID;
	CX__VAR_STRING_CTRL  sEXT_CH__SLOT01_PORTID;
	CX__VAR_STRING_CTRL  sEXT_CH__SLOT01_SLOTID;	

	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_DECHUCK_CTRL_MODE;
	CX__VAR_STRING_CTRL  sEXT_CH__CFG_DECHUCK_RECIPE_ABORT;
	//

	// OBJ : CHM ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__CHM;

	// OBJ : STEP ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__STEP;

	CX__VAR_STRING_CTRL  sEXT_CH__MON_STEP_EXCEPTION_ACT;

	CX__VAR_DIGITAL_CTRL dEXT_CH__RCP_STEP_MODE;	
	CX__VAR_ANALOG_CTRL  aEXT_CH__RCP_STEP_TIME;

	// OBJ : PROC_LOG ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__PROC_LOG;

	CX__VAR_STRING_CTRL  sEXT_CH__PROC_LOG__LOTID;
	CX__VAR_STRING_CTRL  sEXT_CH__PROC_LOG__RECIPEID;
	CX__VAR_STRING_CTRL  sEXT_CH__PROC_LOG__PORTID;
	CX__VAR_STRING_CTRL  sEXT_CH__PROC_LOG__SLOTID;

	CX__VAR_STRING_CTRL  sEXT_CH__PROC_LOG__SUB_DIR;
	CX__VAR_STRING_CTRL  sEXT_CH__PROC_LOG__FILE_NAME;	
	//

	// LINK CHANNEL ...
	CX__VAR_STRING_CTRL  sEXT_CH__SYS_CTRL_LOCK;
	//

	//-------------------------------------------------------------------------
	// ...
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__PRE_READY;
	int  Call__PRE_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PRE_START;
	int  Call__PRE_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__MAIN_READY;
	int Call__MAIN_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__MAIN_START;
	int Call__MAIN_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__POST_READY;
	int Call__POST_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__POST_START;
	int Call__POST_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__MANUAL_READY;
	int Call__MANUAL_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__MANUAL_START;
	int Call__MANUAL_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__JOB_STRT_READY;
	int Call__JOB_START_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__JOB_END_READY;
	int Call__JOB_END_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ....
	int Fnc__PROC_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_dechuck);
	int _Fnc__PROC_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_dechuck);
	int Sub__PROC_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_dechuck);
	int _Fnc__RCP_UPLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_dechuck);

	int Fnc__PROC_START_EX(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_dechuck);
	int Fnc__PROC_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_dechuck);
	int _Fnc__PROC_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_dechuck);
	int Sub__PROC_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_dechuck);	
	int _Make__PROC_LOG(const int restart_count);	
	
	int Sub__PROC_CTRL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_dechuck);
	int Sub__STEP_CTRL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int cur__step_id,const int rcp__step_max);
	int Sub__PROC_END(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	int Save__LEARNED_MOCE();

	int Check__ALARM_RECOVERY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	int _Check__ALARM_RECOVERY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	int Check__STEP_JUMP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	int Check__STEP_LOOP(const int cur__step_id);

	int Fnc__PROC_DECHUCK(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//

	//-------------------------------------------------------------------------
	// ...
	void Mon__EXCEPTION_ACT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	bool bActive__PROC_LOG__STEP_START;

	int  Fnc__PRC_LOG__ENABLE(CII_OBJECT__VARIABLE *p_variable);
	int  Fnc__PRC_LOG__DISABLE(CII_OBJECT__VARIABLE *p_variable);
	int  Fnc__PRC_LOG__PAUSE(CII_OBJECT__VARIABLE *p_variable);
	int  Fnc__PRC_LOG__RESUME(CII_OBJECT__VARIABLE *p_variable);

	int  Fnc__PRC_LOG__STEP_START();
	int  Fnc__PRC_LOG__STEP_END();
	int  Fnc__PRC_LOG__STEP_END_START();
	int  Fnc__PRC_LOG__STEP_ABORT();
	//

public:
	CObj__PROC_STD();
	~CObj__PROC_STD();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
