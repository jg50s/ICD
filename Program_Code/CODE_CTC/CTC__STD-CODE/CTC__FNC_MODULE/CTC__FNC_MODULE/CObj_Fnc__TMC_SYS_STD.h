#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"


class CObj_Fnc__TMC_SYS_STD : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__USER_FNC mERROR__USER_FNC;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_DIGITAL_CTRL  xCH_CFG__INIT_MODE;
	//

	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// EXT MODE
	CString sEXT_MODE__AUTO_INIT;
	CString sEXT_MODE__SYSTEM_INIT;
	CString sEXT_MODE__TIME_INIT;
	CString sEXT_MODE__SYSTEM_MAINT;

	CString sEXT_MODE__CTC_TO_TMC;
	CString sEXT_MODE__TMC_TO_CTC;

	// OBJ - ATM_ROBOT
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__ATM_ROBOT;
	
	// OBJ - VAC_ROBOT
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__VAC_ROBOT;
	//


	//-------------------------------------------------------------------------
	CString sMODE__ALL_INIT;
	int  Call__ALL_INIT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__TIME_INIT;
	int  Call__TIME_INIT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__SYSTEM_INIT;
	int  Call__SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__CTC_TO_TMC;
	int  Call__CTC_TO_TMC(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__TMC_TO_CTC;
	int  Call__TMC_TO_CTC(CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__WAFER_RESYNC_CLEAR_SYS;
	int  Call__WAFER_RESYNC_CLEAR_SYS(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__WAFER_RESYNC_CLEAR_PMx;
	int  Call__WAFER_RESYNC_CLEAR_PMx(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__WAFER_RESYNC_CLEAR_LLx;
	int  Call__WAFER_RESYNC_CLEAR_LLx(CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__SYSTEM_MAINT;
	int  Call__SYSTEM_MAINT(CII_OBJECT__VARIABLE* p_variable);

	int  Fnc__AUTO_INIT(CII_OBJECT__VARIABLE* p_variable);
	//

public:
	CObj_Fnc__TMC_SYS_STD();
	~CObj_Fnc__TMC_SYS_STD();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
