#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"
#include "CCommon_System.h"


#define ALID__OBJECT_MODE_UNKNOWN					11


class CObj_Phy__SYS_STD : public __IOBJ__STD_TYPE
{
private:
	//-----------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__MODULE_OBJ mERROR__MODULE_OBJ;

	SCX__CTC__MODULE_OBJ xI_Module_Obj;
	SCX__USER_LOG_CTRL xI_LOG_CTRL;


	//-----------------------------------------------------------
	// INTERNAL PROPERTY

	//  CONTROL  
	CX__VAR_DIGITAL_CTRL xCH__OBJ_CTRL;
	CString dVAR__MODE;

	//  STATUS   
	CX__VAR_DIGITAL_CTRL xCH__OBJ_STATUS;
	CX__VAR_STRING_CTRL  xCH__MODULE_TIME;

	// SIM CFG ...
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_INIT_SEC;
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_CTC_TO_TMC;
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_TMC_TO_CTC;
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_SYSTEM_MAINT;
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_JOB_START_READY;
	//

	//-----------------------------------------------------------
	// EXTERNAL PROPERTY

	CX__VAR_DIGITAL_CTRL  dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC;

	// OBJ_EFEM_ROBOT ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__EFEM_ROBOT;

	// OBJ_VAC_ROBOT ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__VAC_ROBOT;

	// OBJ_LPx ...
	int iLP_SIZE;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__LPx[CFG_LP_LIMIT];
	
	// OBJ_ALx ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__AL1;

	// OBJ_LLx ...
	int iLLx_SIZE;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__LLx[CFG_LLx_LIMIT];

	// OBJ_TMC_CHM ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__TMC_CHM;

	// OBJ_PMx ...
	int iPM_SIZE;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__PMx[CFG_PM_LIMIT];
	
	CX__VAR_DIGITAL_CTRL pEXT_CH__PMx_SLIT_VLV[CFG_PM_LIMIT];
	//


	//-----------------------------------------------------------
	SCI__THREAD_SYNC_CTRL xI_Sync_Ctrl;
	int iPRC_STS;

	// ...
	CString sMODE__TIME_INIT;
	int Call__TIME_INIT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__SYSTEM_INIT;
	int Call__SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__AUTO_INIT;
	int  Call__AUTO_INIT(CII_OBJECT__VARIABLE* p_variable);

	// ...
	CString sMODE__CTC_TO_TMC;
	int  Call__CTC_TO_TMC(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__TMC_TO_CTC;
	int  Call__TMC_TO_CTC(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__SYSTEM_MAINT;
	int  Call__SYSTEM_MAINT(CII_OBJECT__VARIABLE* p_variable);

	// ...
	CString sMODE__JOB_START_READY;
	int  Call__JOB_START_READY(CII_OBJECT__VARIABLE* p_variable);
	//

	// ...
	int  Fnc__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
						 const CString obj_mode);
	int  Sim__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
					     const CString obj_mode);

	int  Fnc__WAIT_SEC(CII_OBJECT__VARIABLE* p_variable,
					   CII__VAR_ANALOG_CTRL* pch_analog_cfg);
	//

	// ...
	void Mon__Obj_Status(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	void Set__Module_Time();
	//


public:
	CObj_Phy__SYS_STD();
	~CObj_Phy__SYS_STD();

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
