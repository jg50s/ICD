#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"


class CObj__ALx_STD : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//-------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;

	// ...
	bool bActive__LLx_MULTI_DOOR_VALVE;
	int  iLLx_SLOT_SIZE;
	//

	//-------------------------------------------------------------------------
	// INTERNAL PROPERTY

	CX__VAR_ANALOG_CTRL  aCH__PARA_SLOT;

	CX__VAR_DIGITAL_CTRL dCH__SLOT_STATUS[CFG_ALx__SLOT_MAX];
	CX__VAR_STRING_CTRL  sCH__SLOT_TITLE[CFG_ALx__SLOT_MAX];
	CX__VAR_STRING_CTRL	 sCH__MSG;
	//

	//-------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	// OBJ DB ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__MAINT_TARGT_LLx_NAME;	
	CX__VAR_DIGITAL_CTRL dEXT_CH__MAINT_TARGT_LLx_SLOT;	

	CX__VAR_STRING_CTRL  sEXT_CH__MODULE_LINK_TARGT_LLx_NAME;
	CX__VAR_STRING_CTRL  sEXT_CH__MODULE_LINK_TARGT_LLx_SLOT;

	CX__VAR_STRING_CTRL  sEXT_CH__CUR_AL1_TARGET_LLx_NAME;
	CX__VAR_STRING_CTRL  sEXT_CH__CUR_AL1_TARGET_LLx_SLOT;
	CX__VAR_STRING_CTRL  sEXT_CH__CUR_AL1_CCD_POS;

	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_LLx_ALIGN_ANGLE[CFG_LLx__SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT[CFG_LLx__SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_RANGE[CFG_LLx__SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_START_ANGLE[CFG_LLx__SIZE];
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_APPLY[CFG_LLx__SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__CUR_LLx_POST_POSITION_INCREMENT_ANGLE[CFG_LLx__SIZE];

	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_LLx_X_ALIGN_ANGLE[CFG_LLx__SIZE][CFG_LLx__SLOT_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT[CFG_LLx__SIZE][CFG_LLx__SLOT_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_RANGE[CFG_LLx__SIZE][CFG_LLx__SLOT_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_START_ANGLE[CFG_LLx__SIZE][CFG_LLx__SLOT_SIZE];
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_APPLY[CFG_LLx__SIZE][CFG_LLx__SLOT_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__CUR_LLx_X_POST_POSITION_INCREMENT_ANGLE[CFG_LLx__SIZE][CFG_LLx__SLOT_SIZE];

	// CH LINK ...
	CX__VAR_STRING_CTRL  sEXT_CH__OBJ_STATUS;
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_SLOT_MAX;

	// ALx OBJECT ...
	CII_EXT_OBJECT__CTRL *pALx__OBJ_CTRL;

	CX__VAR_DIGITAL_CTRL dEXT_CH__ALx_PARA_SLOT;
	CX__VAR_STRING_CTRL  sEXT_CH__ALx_PARA_CCD_POS;
	//

	//------------------------------------------------------------------------------
	// INIT ----- 
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ALIGN -----
	CString sMODE__ALIGN;
	int  Call__ALIGN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);


public:
	CObj__ALx_STD();
	~CObj__ALx_STD();

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
