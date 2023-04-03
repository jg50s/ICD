#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Def.h"


// ...
#define CFG_SIZE__MFC__VLV_PURGE				10
#define CFG_SIZE__LINE__VLV_PURGE				10

#define CFG_SIZE__TOP_CHM__VLV_PROC				10
#define CFG_SIZE__TOP_CHM__VLV_PURGE			10

#define CFG_SIZE__VLV_SUPPLY					11

#define CFG_SIZE__SOFT_VENT__VLV_OPEN			10
#define CFG_SIZE__SOFT_VENT__VLV_CLOSE			10

#define CFG_SIZE__FAST_VENT__VLV_OPEN			10
#define CFG_SIZE__FAST_VENT__VLV_CLOSE			10


class CObj__GAS_VLV_PHY : public __IOBJ__STD_TYPE
{
private:
	//------------------------------------------------------------
	CString	sObject_Name;

	// ...
	SCX__USER_LOG_CTRL xI_LOG_CTRL;
	//

	//------------------------------------------------------------
	CX__VAR_STRING_CTRL sCH__OBJ_MSG;

	//------------------------------------------------------------
	// OBJ : DB_SYS ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_ACTIVE_PROCESS_VALVE_READY_STATE;

	// ...
	int iSIZE__GAS_LINE__VLV_PURGE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__GAS_LINE__VLV_PURGE[CFG_SIZE__MFC__VLV_PURGE];

	int iSIZE__CHM_LINE__VLV_PURGE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CHM_LINE__VLV_PURGE[CFG_SIZE__MFC__VLV_PURGE];

	int iSIZE__MFC__VLV_PURGE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__MFC__VLV_PURGE[CFG_SIZE__MFC__VLV_PURGE];

	// ...
	int iSIZE__TOP_CHM__VLV_PROC;
	CX__VAR_DIGITAL_CTRL dEXT_CH__TOP_CHM__VLV_PROC[CFG_SIZE__TOP_CHM__VLV_PROC];

	int iSIZE__TOP_CHM__VLV_PURGE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__TOP_CHM__VLV_PURGE[CFG_SIZE__TOP_CHM__VLV_PURGE];

	// ...
	int iSIZE__SOFT_VENT__VLV_OPEN;
	CX__VAR_DIGITAL_CTRL dEXT_CH__SOFT_VENT__VLV_OPEN[CFG_SIZE__SOFT_VENT__VLV_OPEN];

	int iSIZE__SOFT_VENT__VLV_CLOSE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__SOFT_VENT__VLV_CLOSE[CFG_SIZE__SOFT_VENT__VLV_CLOSE];

	// ...
	int iSIZE__FAST_VENT__VLV_OPEN;
	CX__VAR_DIGITAL_CTRL dEXT_CH__FAST_VENT__VLV_OPEN[CFG_SIZE__FAST_VENT__VLV_OPEN];

	int iSIZE__FAST_VENT__VLV_CLOSE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__FAST_VENT__VLV_CLOSE[CFG_SIZE__FAST_VENT__VLV_CLOSE];
	//


	//------------------------------------------------------------
	CString sMODE__ALL_CLOSE;
	int Call__ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__SV_OPEN;
	int Call__SV_OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__SV_CLOSE;
	int Call__SV_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__FV_OPEN;
	int Call__FV_OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__FV_CLOSE;
	int Call__FV_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	CString sMODE__GAS_LINE_PURGE;
	int Call__GAS_LINE_PURGE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__CHM_LINE_PURGE;
	int Call__CHM_LINE_PURGE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__LINE_PURGE_WITH_N2;
	int Call__LINE_PURGE_WITH_N2(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__CLOSE_N2_PURGE;
	int Call__CLOSE_N2_PURGE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	CString sMODE__PROC_OPEN;
	int Call__PROC_OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//

	// ...
	int  Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//


public:
	//------------------------------------------------------------
	CObj__GAS_VLV_PHY();
	~CObj__GAS_VLV_PHY();

	//------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	//------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
