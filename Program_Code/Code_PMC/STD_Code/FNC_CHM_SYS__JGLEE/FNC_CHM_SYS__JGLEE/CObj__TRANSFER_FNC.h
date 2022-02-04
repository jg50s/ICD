#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Def.h"

#include "CObj__TRANSFER_FNC__ALID.h"
#include "CObj__TRANSFER_FNC__DEF.h"


class CObj__TRANSFER_FNC : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;	

	SCX__USER_LOG_CTRL xI_LOG_CTRL;
	//

	//-------------------------------------------------------------------------
	CX__VAR_STRING_CTRL sCH__OBJ_MSG;


	//-------------------------------------------------------------------------
	// OBJ : RFx ...
	int iDATA__RF_SIZE;

	CString sList__RFx_NAME[_CFG__RF_SIZE];
	CX__VAR_DIGITAL_CTRL dEXT_CH__RFx_ON_STS[_CFG__RF_SIZE];

	// OBJ : ESC ...
	bool bActive__ESC_ON_STS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__ESC_ON_STS;
	//

	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__PICK_READY;
	int Call__PICK_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__PICK_X_READY;
	int Call__PICK_X_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__PICK_COMPLETE;
	int Call__PICK_COMPLETE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__PICK_X_COMPLETE;
	int Call__PICK_X_COMPLETE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__PLACE_READY;
	int Call__PLACE_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__PLACE_X_READY;
	int Call__PLACE_X_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__PLACE_COMPLETE;
	int Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__PLACE_X_COMPLETE;
	int Call__PLACE_X_COMPLETE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	int Fnc__INTERLOCK_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	int Check__RF_POWER(CII_OBJECT__ALARM *p_alarm, int nIndex);
	int Check__ESC_POWER(CII_OBJECT__ALARM *p_alarm);

	// ...
	int	 Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm, const CString msg, const int alarm_id);
	void Alarm__POST_CHECK(CII_OBJECT__ALARM *p_alarm, const CString msg, const int alarm_id);

	void Fnc__WRITE_LOG(const char *fmt, ...);
	void Fnc__WRITE_COMMON_LOG(const char *fmt, ...);
	//


public:
	CObj__TRANSFER_FNC();
	~CObj__TRANSFER_FNC();

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
