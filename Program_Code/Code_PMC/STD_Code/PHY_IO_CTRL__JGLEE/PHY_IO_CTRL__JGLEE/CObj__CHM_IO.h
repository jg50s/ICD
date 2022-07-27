#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__CHM_IO__DEF.h"


class CObj__CHM_IO : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	SCX__USER_LOG_CTRL xI_LOG_CTRL;
	int iActive__SIM_MODE;
	//


	//-------------------------------------------------------------------------
	// OBJ ..
	CX__VAR_STRING_CTRL   sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL   sCH__OBJ_STATUS;

	// CFG ...
	CX__VAR_ANALOG_CTRL   aCH__CFG_INTERLOCK_HIGH_LIMIT_PRESSURE;
	CX__VAR_ANALOG_CTRL   aCH__CFG_PROCESS_MANOMETER_MAX_PRESSURE_mTORR_X[_CFG__PRC_GAUGE_SIZE];

	// MON ...
	CX__VAR_STRING_CTRL   sCH__MON_CHM_PRESSURE_DISPLAY;
	//

	//-------------------------------------------------------------------------
	// OBJ : DB_INF
	CX__VAR_DIGITAL_CTRL  dEXT_CH__CHM_SLOT_VLV_STATE;

	CX__VAR_STRING_CTRL   sEXT_CH__CHM_PRESSURE_VALUE;
	CX__VAR_STRING_CTRL   sEXT_CH__CHM_PRESSURE_mTORR;

	CX__VAR_STRING_CTRL   sEXT_CH__CHM_VAC_SNS;
	CX__VAR_STRING_CTRL   sEXT_CH__CHM_ATM_SNS;

	CX__VAR_STRING_CTRL   sEXT_CH__PMP_PRESSURE_VALUE;
	CX__VAR_STRING_CTRL   sEXT_CH__PMP_PRESSURE_STATE;
	CX__VAR_STRING_CTRL   sEXT_CH__PMP_VAC_SNS;

	// OBJ : DB_SYS
	CX__VAR_STRING_CTRL   sEXT_CH__SIM_PRESSURE_TORR;

	CX__VAR_DIGITAL_CTRL  dEXT_CH__CFG_INTERLOCK_USE_MODE;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__CFG_INTERLOCK_USE__CHM_MANOMETER_ISO;

	CX__VAR_STRING_CTRL   sEXT_CH__SYSTEM_SETUP_REQ;

	// LINK : IO Channel 
	CX__VAR_DIGITAL_CTRL  dEXT_CH__DI_VAC_SNS;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__DI_ATM_SNS;

	//
	bool bActive__DI_SLOT_VLV_OPEN;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__DI_SLOT_VLV_OPEN;

	bool bActive__DI_SLOT_VLV_CLOSE;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__DI_SLOT_VLV_CLOSE;

	//
	bool bActive__DO_CHM_CHECK_VLV;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__DO_CHM_CHECK_VLV;

	//
	int iSIZE__PRC_GUAGE;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__DO_PRC_GAUGE_ISO_VLV_X[_CFG__PRC_GAUGE_SIZE];
	CX__VAR_ANALOG_CTRL   aEXT_CH__AI_PRC_GAUGE_TORR_X[_CFG__PRC_GAUGE_SIZE];

	bool bActive__AI_CHM_GAUGE_TORR;
	CX__VAR_ANALOG_CTRL   aEXT_CH__AI_CHM_GAUGE_TORR;

	bool bActive__AI_FORELINE_GAUGE_TORR;
	CX__VAR_ANALOG_CTRL   aEXT_CH__AI_FORELINE_GAUGE_TORR;

	// RF INFO ...
	CX__VAR_STRING_CTRL   sEXT_CH__RF_TOTAL_ON_STATE;

	int iDATA__RF_SIZE;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__RF_ON_STATE_X[_CFG__RF_SIZE];

	/*
	CX__VAR_STRING_CTRL   sEXT_CH__PROC_STATE;
	*/


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);


	// ...
	int Mon__STATUS(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);


public:
	CObj__CHM_IO();
	~CObj__CHM_IO();

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
