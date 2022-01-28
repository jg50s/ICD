#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


class CObj__UPPER_VAC_ROBOT : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//-------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;


	//-------------------------------------------------------------------------
	// INTERNAL PROPERTY

	CX__VAR_DIGITAL_CTRL xCH__OBJ_STATUS;

	CX__VAR_DIGITAL_CTRL xCH__PARA_MODULE;
	CX__VAR_DIGITAL_CTRL xCH__PARA_PICK_ARM;
	CX__VAR_DIGITAL_CTRL xCH__PARA_PICK_SLOT;
	CX__VAR_DIGITAL_CTRL xCH__PARA_PLACE_ARM;
	CX__VAR_DIGITAL_CTRL xCH__PARA_PLACE_SLOT;


	//-------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	// VAC_ROBOT
	CII_EXT_OBJECT__CTRL *pVAC_ROBOT__OBJ_CTRL;

	CX__VAR_DIGITAL_CTRL dEXT_CH__VAC_ROBOT__OBJ_STATUS;

	CX__VAR_DIGITAL_CTRL dEXT_CH__VAC_ROBOT__PARA_ARM;
	CX__VAR_DIGITAL_CTRL dEXT_CH__VAC_ROBOT__PARA_MODULE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__VAC_ROBOT__PARA_SLOT;

	// LLx ...
	int iSIZE_LLx;

	CII_EXT_OBJECT__CTRL *pLLx__OBJ_CTRL[CFG__LLx_SIZE];

	CX__VAR_DIGITAL_CTRL xEXT_CH__LLx__OBJ_STATUS[CFG__LLx_SIZE];
	CX__VAR_DIGITAL_CTRL xEXT_CH__LLx__PREMATERIAL_SLOT[CFG__LLx_SIZE];


	//------------------------------------------------------------------------------
	CString sMODE__SWAP_LBx;
	int  Call__SWAP_LBx(CII_OBJECT__VARIABLE* p_variable);


public:
	CObj__UPPER_VAC_ROBOT();
	~CObj__UPPER_VAC_ROBOT();

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
