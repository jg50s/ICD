#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"


class CObj_Fnc__PMC_SYS_STD : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__USER_FNC mERROR__USER_FNC;
	
	int iPMx_SIZE;

	
	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_STRING_CTRL   sCH__ACTIVE_STATE;
	CX__VAR_DIGITAL_CTRL  xCH_CFG__INIT_MODE;


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	CII_EXT_OBJECT__CTRL* pOBJ_CTRL__PMx[CFG_PM_LIMIT];
	CX__VAR_DIGITAL_CTRL xEXT_CH__PMx__OBJ_STATUS[CFG_PM_LIMIT];
	//

	//-------------------------------------------------------------------------
	CString sMODE__ALL_INIT;
	int  Call__ALL_INIT(CII_OBJECT__VARIABLE* p_variable);
	int  Fnc__AUTO_INIT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__TIME_INIT;
	int  Call__TIME_INIT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__SYSTEM_INIT;
	int  Call__SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__SYSTEM_MAINT;
	int  Call__SYSTEM_MAINT(CII_OBJECT__VARIABLE* p_variable);

	int  Fnc__CMMD_ACT(CII_OBJECT__VARIABLE* p_variable, const CString& cmmd_act, const bool active_init = true);
	//

public:
	CObj_Fnc__PMC_SYS_STD();
	~CObj_Fnc__PMC_SYS_STD();

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
