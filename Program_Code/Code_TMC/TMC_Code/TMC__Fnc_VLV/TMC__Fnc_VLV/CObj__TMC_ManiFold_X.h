#pragma once

#include "Interface_Code.h"

#include "Ccommon_Error.h"
#include "CCommon_System.h"


class CObj__TMC_ManiFold_X : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//-------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;
	int m_nPM_LIMIT;


	//-------------------------------------------------------------------------
	// INTERNAL PROPERTY

	CX__VAR_STRING_CTRL  sCH__OBJ_STATUS;

	CX__VAR_ANALOG_CTRL  aCH__PARA_PMC_ID;
	//

	//-------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	// DB OBJECT -----
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_TRANSFER_MODE;
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_REF_ATM_PRESSURE;
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_REF_VAC_PRESSURE;

	// TMC CHM -----
	CII_EXT_OBJECT__CTRL *pTMC_CHM__OBJ_CTRL;

	CX__VAR_STRING_CTRL  sEXT_CH__TMC_CHM__OBJ_STATUS;
	CX__VAR_ANALOG_CTRL  aEXT_CH__TMC_CHM__PRESSURE_TORR;

	// PMC OBJECT -----
	CII_EXT_OBJECT__CTRL *pPMx__OBJ_CTRL;

	CX__VAR_ANALOG_CTRL  aEXT_CH__PMx__PARA_PMC_ID;
	CX__VAR_ANALOG_CTRL  aEXT_CH__PMx__PRESSURE_TORR[CFG_PMx__SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMx__SHUTTER_STATUS[CFG_PMx__SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMx__LIFT_PIN_STATUS[CFG_PMx__SIZE];
	//


	//------------------------------------------------------------------------------
	// PMC ---------------
	// CHECK PMC SV ALL CLOSE -----
	CString sMODE__CHECK_PMC_SV_ALL_CLOSE;
	int  Call__CHECK_PMC_SV_ALL_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// SV CLOSE -----
	CString sMODE__PMC_SV_CLOSE;
	int  Call__PMC_SV_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PMC_INIT_SV_CLOSE;
	int  Call__PMC_INIT_SV_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ALL SV CLOSE -----
	CString sMODE__PMC_ALL_SV_CLOSE;
	int  Call__PMC_ALL_SV_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// SV OPEN -----
	CString sMODE__PMC_SV_OPEN;
	int  Call__PMC_SV_OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Fnc__PMC_SV_OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm,const int pm_index);
	int  Fnc__PMC_SV_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm,const int pm_index);

	// SV TRANSFER OPEN -----
	CString sMODE__PMC_SV_TRANSFER_OPEN;
	int  Call__PMC_SV_TRANSFER_OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// SV TRANSFER CLOSE -----
	CString sMODE__PMC_SV_TRANSFER_CLOSE;
	int  Call__PMC_SV_TRANSFER_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//

	//------------------------------------------------------------------------------
	int  Check__TRANSFER_ATM(CII_OBJECT__VARIABLE* p_variable,
								CII_OBJECT__ALARM* p_alarm,
								const CString& module_name,
								CII__VAR_ANALOG_CTRL* pch_module_pressure);

	int  Check__TRANSFER_PRESSURE(CII_OBJECT__VARIABLE* p_variable,
									CII_OBJECT__ALARM* p_alarm,
									const CString& module_name,
									CII__VAR_ANALOG_CTRL* pch_module_pressure);
	//
	

public:
	CObj__TMC_ManiFold_X();
	~CObj__TMC_ManiFold_X();

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
