#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


#define  ALID__OBJECT_MODE_UNKNOWN					11
#define  ALID__TMC_OFFLINE						    12
#define  ALID__VENT_ERROR							13
#define  ALID__PUMP_ERROR							14


class CObj_Phy__CHM_STD : public __IOBJ__STD_TYPE
{
private:
	//-----------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;
	CCommon_Error__MODULE_OBJ   mERROR__MODULE_OBJ;

	SCX__CTC__MODULE_OBJ xI_Module_Obj;
	SCX__USER_LOG_CTRL xI_LOG_CTRL;

	int iActive__SIM_MODE;
	//


	//-----------------------------------------------------------
	// INTERNAL PROPERTY

	int iSEQ_ID;

	// PARA ...
	CX__VAR_DIGITAL_CTRL dCH__PARA_PMx_ID;

	//  CONTROL
	CX__VAR_DIGITAL_CTRL xCH__TMC_CHM_CTRL;
	CX__VAR_DIGITAL_CTRL xCH__TMC_CHM_MODE;

	CX__VAR_DIGITAL_CTRL xCH__TMC_CHM_PARA_PMx_ID;

	//  STATUS
	CX__VAR_DIGITAL_CTRL xCH__OBJ_STATUS;

	CX__VAR_DIGITAL_CTRL xCH__PRESSURE_STATUS;
	CX__VAR_STRING_CTRL  xCH__PRESSURE_VALUE;
	CX__VAR_STRING_CTRL  xCH__PRESSURE_mTORR;

	CX__VAR_STRING_CTRL  xCH__VAC_SNS;

	// SIM CFG ...
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_INIT_SEC;
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_PUMP_SEC;
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_VENT_SEC;
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_ISOLATE_SEC;
	CX__VAR_ANALOG_CTRL  aCH__SCH_TEST_CFG_PURGE_SEC;
	//

	//-----------------------------------------------------------
	// EXTERNAL PROPERTY

	SCX__MODULE_INFO xI__MODULE_INFO;

	CX__VAR_DIGITAL_CTRL dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC;

	CX__VAR_ANALOG_CTRL  aEXT_CH_CFG__REF_ATM_PRESSURE;
	CX__VAR_ANALOG_CTRL  aEXT_CH_CFG__REF_VAC_PRESSURE;
	CX__VAR_DIGITAL_CTRL dEXT_CH_CFG__TRANSFER_MODE;

	CX__VAR_DIGITAL_CTRL xEXT_CH__TMC_CONNECT_STATUS;
	//


	//-----------------------------------------------------------
	SCI__THREAD_SYNC_CTRL xI_Sync_Ctrl;
	int iPRC_STS;

	// ...
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__MAINT;
	int Call__MAINT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__PUMP;
	int Call__PUMP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__VENT;
	int Call__VENT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__ISOLATE;
	int Call__ISOLATE(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PURGE;
	int Call__PURGE(CII_OBJECT__VARIABLE* p_variable);

	// ...
	CString sMODE__PMx_SV_OPEN;
	int Call__PMx_SV_OPEN(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PMx_SV_CLOSE;
	int Call__PMx_SV_CLOSE(CII_OBJECT__VARIABLE* p_variable);
	//

	// ...
	int Fnc__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
						const CString obj_mode);
	int Sim__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
						const CString obj_mode);

	int Fnc__WAIT_SEC(CII_OBJECT__VARIABLE* p_variable,
					  CII__VAR_ANALOG_CTRL* pch_analog_cfg);
	//

	//-----------------------------------------------------------
	void Mon__All_State(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj_Phy__CHM_STD();
	~CObj_Phy__CHM_STD();

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
