#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Def.h"

#include "CObj__AUTO_PM__ALID.h"
#include "CObj__AUTO_PM__DEF.h"


class CObj__AUTO_PM : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	// ...
	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;
	CCommon_Error__USER_FNC     mERROR__USER_FNC;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	CX__VAR_STRING_CTRL  sCH__AUTO_PM__START_TIME;
	CX__VAR_STRING_CTRL  sCH__AUTO_PM__END_TIME;
	CX__VAR_STRING_CTRL  sCH__AUTO_PM__RESULT;

	CX__VAR_DIGITAL_CTRL dCH__LeakCheck__CFG_CHECK_FLAG;
	CX__VAR_STRING_CTRL  sCH__LeakCheck__CUR_CHECK_FLAG;
	CX__VAR_STRING_CTRL  sCH__LeakCheck__START_TIME;
	CX__VAR_STRING_CTRL  sCH__LeakCheck__END_TIME;
	CX__VAR_STRING_CTRL  sCH__LeakCheck__RESULT;

	CX__VAR_DIGITAL_CTRL dCH__FRC_CHECK__CFG_CHECK_FLAG;
	CX__VAR_STRING_CTRL  sCH__FRC_CHECK__CUR_CHECK_FLAG;
	CX__VAR_STRING_CTRL  sCH__FRC_CHECK__START_TIME;
	CX__VAR_STRING_CTRL  sCH__FRC_CHECK__END_TIME;
	CX__VAR_STRING_CTRL  sCH__FRC_CHECK__RESULT;

	CX__VAR_DIGITAL_CTRL dCH__GaugeCheck__CFG_CHECK_FLAG;
	CX__VAR_STRING_CTRL  sCH__GaugeCheck__CUR_CHECK_FLAG;
	CX__VAR_STRING_CTRL  sCH__GaugeCheck__START_TIME;
	CX__VAR_STRING_CTRL  sCH__GaugeCheck__END_TIME;
	CX__VAR_STRING_CTRL  sCH__GaugeCheck__RESULT;

	CX__VAR_DIGITAL_CTRL dCH__MfcCheck__CFG_CHECK_FLAG;
	CX__VAR_STRING_CTRL  sCH__MfcCheck__CUR_CHECK_FLAG;
	CX__VAR_DIGITAL_CTRL dCH__MfcCheck__CFG_CHECK_MODE;
	CX__VAR_STRING_CTRL  sCH__MfcCheck__CUR_CHECK_MODE;
	CX__VAR_STRING_CTRL  sCH__MfcCheck__START_TIME;
	CX__VAR_STRING_CTRL  sCH__MfcCheck__END_TIME;
	CX__VAR_STRING_CTRL  sCH__MfcCheck__RESULT;

	CX__VAR_DIGITAL_CTRL dCH__VatCheck__CFG_CHECK_FLAG;
	CX__VAR_STRING_CTRL  sCH__VatCheck__CUR_CHECK_FLAG;
	CX__VAR_DIGITAL_CTRL dCH__VatCheck__CFG_CHECK_MODE;
	CX__VAR_STRING_CTRL  sCH__VatCheck__CUR_CHECK_MODE;
	CX__VAR_STRING_CTRL  sCH__VatCheck__START_TIME;
	CX__VAR_STRING_CTRL  sCH__VatCheck__END_TIME;
	CX__VAR_STRING_CTRL  sCH__VatCheck__RESULT;
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// SYSTEM CHANNEL ...
	CX__VAR_STRING_CTRL  sEXT_CH__SYS_FNC_NAME;

	// OBJ : CHM ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__CHM;

	// OBJ : Leak Check ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__LEAK_CHECK;

	// OBJ : FRC_CHECK.X ...
	int iFRC_CHECK__SIZE;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__FRC_CHECK_X[_MAX__FRC_CHECK];

	// OBJ : GAUGE Check ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__GAUGE_CHECK;

	// OBJ : Vat Check ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__VAT_CHECK;

	CX__VAR_DIGITAL_CTRL dEXT_CH__VAT_CHECK__CFG_CHECK_TYPE;

	// OBJ : Mfc Check ...
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__MFC_CHECK;
	//


	//-------------------------------------------------------------------------
	CString sMODE__AUTO_PM;
	int  Call__AUTO_PM(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int  Fnc__AUTO_PM(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	//


public:
	CObj__AUTO_PM();
	~CObj__AUTO_PM();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_def_fnc);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
