#pragma once

#include "Interface_Code.h"

#include "CObj__SYS_IO__ALID.h"
#include "CObj__SYS_IO__DEF.h"


class CObj__SYS_IO : public __IOBJ__INTERLOCK_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	SCX__USER_LOG_CTRL xI__APP_LOG_CTRL;
	//

	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// OBJ DB_SUS ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__ACTIVE_INTERLOCK_CHAMBER_VENT;

	// IO Channel ...
	CString sCH_Name__DO_VENT_FAST_VLV;
	CX__VAR_DIGITAL_CTRL doEXT_CH__DO_VENT_FAST_VLV;

	bool bActive__DO_VENT_SOFT_VLV;
	CString sCH_Name__DO_VENT_SOFT_VLV;
	CX__VAR_DIGITAL_CTRL doEXT_CH__DO_VENT_SOFT_VLV;

	//
	bool bActive__DO_ROUGH_FORELINE_VLV;
	CString sCH_Name__DO_ROUGH_FORELINE_VLV;
	CX__VAR_DIGITAL_CTRL doEXT_CH__DO_ROUGH_FORELINE_VLV;

	//
	CString sCH_Name__DO_ROUGH_FAST_VLV;
	CX__VAR_DIGITAL_CTRL doEXT_CH__DO_ROUGH_FAST_VLV;

	bool bActive__DO_ROUGH_SOFT_VLV;
	CString sCH_Name__DO_ROUGH_SOFT_VLV;
	CX__VAR_DIGITAL_CTRL doEXT_CH__DO_ROUGH_SOFT_VLV;

	//
	CString sCH_Name__APC_VLV_CUR_POS;
	CX__VAR_STRING_CTRL  sEXT_CH__APC_VLV_CUR_POS;

	// 
	CString sCH_Name__IO_VAC_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__IO_VAC_SNS;
	CString sVAC_SNS__ACTIVE_STATE;

	CString sCH_Name__IO_ATM_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__IO_ATM_SNS;
	CString sATM_SNS__ACTIVE_STATE;

	// DRY_PUMP ...
	bool bActive__DRY_PUMP_POWER_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DRY_PUMP_POWER_SNS;

	bool bActive__DRY_PUMP_VAC_SNS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DRY_PUMP_VAC_SNS;
	//

	// LINK_OBJ.TMP ...
	bool bActive__TMP_LINK;

	CX__VAR_DIGITAL_CTRL dEXT_CH__TMP_LINK__ACTIVE_INTERLOCK_SKIP_FORELINE_VAC;
	//


	//-------------------------------------------------------------------------
	// ...
	int	 Check__Interlock_Use(const int lock_id);

	void Post_Alarm(const int alarm_id, const CString err_msg);
	//


	//-------------------------------------------------------------------------
	CString sMODE__TEST_1;
	int  Call__TEST_1(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	void Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//


public:
	// SetPoint Interlock .....

	// VENT-Fast Valve <- Open
	int IFnc_SetPoint__VENT_Fast_Vlv_Open();
	int SetPoint__VENT_Fast_Vlv_Open(CString &err_msg);

	// VENT-Soft Valve <- Open
	int IFnc_SetPoint__VENT_Soft_Vlv_Open();
	int SetPoint__VENT_Soft_Vlv_Open(CString &err_msg);

	// VAC-Foreline Valve <- Open
	int IFnc_SetPoint__VAC_Foreline_Vlv_Open();
	int SetPoint__VAC_Foreline_Vlv_Open(CString &err_msg);

	// VAC-Foreline Valve <- Close
	int IFnc_SetPoint__VAC_Foreline_Vlv_Close();
	int SetPoint__VAC_Foreline_Vlv_Close(CString &err_msg);

	// VAC-Fast Valve <- Open
	int IFnc_SetPoint__VAC_Fast_Vlv_Open();
	int SetPoint__VAC_Fast_Vlv_Open(CString &err_msg);

	// VAC-Slow Valve <- Open
	int IFnc_SetPoint__VAC_Slow_Vlv_Open();
	int SetPoint__VAC_Slow_Vlv_Open(CString &err_msg);
	//


public:
	CObj__SYS_IO();
	~CObj__SYS_IO();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	int __DEFINE__UI_INTERLOCK(p_interlock);
	int __DEFINE__IO_INTERLOCK(p_interlock);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id, p_variable, p_alarm);
};
