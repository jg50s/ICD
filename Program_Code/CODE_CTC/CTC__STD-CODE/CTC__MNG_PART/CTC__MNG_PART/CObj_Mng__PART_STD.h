#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"

#include "CObj_Mng__PART_STD__DEF.h"


// ...
#define  ALID__OBJECT_MODE_UNKNOWN					11


class CObj_Mng__PART_STD : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;
	CCommon_Error__USER_FNC     mERROR__USER_FNC;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// PART ----
	CX__VAR_STRING_CTRL  xCH__PART_ITEM_X[CFG__PMx_SIZE][CFG__PART_SIZE];
	CX__VAR_STRING_CTRL  xCH__PART_CHANGE_DAY_X[CFG__PMx_SIZE][CFG__PART_SIZE];
	CX__VAR_ANALOG_CTRL  xCH__PART_REF_DAY_X[CFG__PMx_SIZE][CFG__PART_SIZE];
	CX__VAR_ANALOG_CTRL  xCH__PART_REF_COUNT_X[CFG__PMx_SIZE][CFG__PART_SIZE];
	CX__VAR_ANALOG_CTRL  xCH__PART_CUR_DAY_X[CFG__PMx_SIZE][CFG__PART_SIZE];
	CX__VAR_ANALOG_CTRL  xCH__PART_CUR_COUNT_X[CFG__PMx_SIZE][CFG__PART_SIZE];
	CX__VAR_ANALOG_CTRL  xCH__PART_PERCENT_X[CFG__PMx_SIZE][CFG__PART_SIZE];
	CX__VAR_DIGITAL_CTRL xCH__PART_RESET_X[CFG__PMx_SIZE][CFG__PART_SIZE];
	CX__VAR_STRING_CTRL  xCH__PART_COMMENT_X[CFG__PMx_SIZE][CFG__PART_SIZE];
	CX__VAR_DIGITAL_CTRL xCH__PART_ALL_RESET_X[CFG__PMx_SIZE];

	CX__VAR_ANALOG_CTRL  xCH__POPUP_PERIOD_X[CFG__PMx_SIZE];
	CX__VAR_STRING_CTRL  xCH__POPUP_CUR_DAY_X[CFG__PMx_SIZE];

	CX__VAR_STRING_CTRL  xCH__MSG_WIN_X[CFG__PMx_SIZE];
	CX__VAR_STRING_CTRL  xCH__PART_EXCHANGE_MSG_X[CFG__PMx_SIZE][CFG__EXCHANGE_SIZE];

	CX__VAR_STRING_CTRL  xCH__ALERT_UNIT_X[CFG__PMx_SIZE];
	CX__VAR_STRING_CTRL  xCH__ALERT_TIME_X[CFG__PMx_SIZE];
	CX__VAR_STRING_CTRL  xCH__ALERT_PART_NAME_X[CFG__PMx_SIZE];
	CX__VAR_STRING_CTRL  xCH__ALERT_PART_REF_DAY_X[CFG__PMx_SIZE];
	CX__VAR_STRING_CTRL  xCH__ALERT_PART_REF_COUNT_X[CFG__PMx_SIZE];
	CX__VAR_STRING_CTRL  xCH__ALERT_PART_CUR_COUNT_X[CFG__PMx_SIZE];

	CX__VAR_DIGITAL_CTRL dCH__SEL_PART_ITEM_X[CFG__PMx_SIZE];
	CX__VAR_STRING_CTRL  sCH__SEL_PART_REF_DAY_X[CFG__PMx_SIZE];
	CX__VAR_STRING_CTRL  sCH__SEL_PART_REF_COUNT_X[CFG__PMx_SIZE];
	//

	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	int iPMx_SIZE;

	CX__VAR_DIGITAL_CTRL xEXT_CH__CFG_MODULE_USE_X[CFG__PMx_SIZE];
	CX__VAR_STRING_CTRL  xEXT_CH__MODULE_MATERIAL_COUNT_X[CFG__PMx_SIZE];
	CString sSTR__POPUP_WIN_NAME_X[CFG__PMx_SIZE];

	int iCEID__PART_CHANGE_ALERT_X[CFG__PMx_SIZE];

	// ...
	void Mon__PART_CTRL(CII_OBJECT__VARIABLE *p_variable,
						CII_OBJECT__ALARM *p_alarm);

	void Fnc__PART_CTRL(CII_OBJECT__VARIABLE *p_variable,
						CII_OBJECT__ALARM *p_alarm,
						CString& pre_count,
						const int p);
	//


public:
	CObj_Mng__PART_STD();
	~CObj_Mng__PART_STD();

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
