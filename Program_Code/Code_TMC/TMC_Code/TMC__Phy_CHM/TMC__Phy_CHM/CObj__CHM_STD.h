#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"


class CObj__CHM_STD : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	//.....
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xLOG_CTRL;
	CII_EXT_OBJECT__CTRL *m_xI_DATALOG_OBJ_CTRL;

	int  iSim_Flag;
	int	 m_nDatalog_Flag;
	//

	
	//-------------------------------------------------------------------------
	// INTERNAL PROPERTY

	// ...
	CX__VAR_STRING_CTRL  sCH__MSG;
	CX__VAR_STRING_CTRL  sCH__OBJ_STATUS;

	CX__VAR_STRING_CTRL  sCH__PUMP_VLV_OPEN_FLAG;
	CX__VAR_STRING_CTRL  sCH__PRESSURE_CTRL_FLAG;

	// ...
	CX__VAR_ANALOG_CTRL  aCH__TMC_CHM_PRESSURE_TORR;
	CX__VAR_ANALOG_CTRL  aCH__TMC_CHM_PRESSURE_mTORR;
	CX__VAR_DIGITAL_CTRL dCH__TMC_CHM_PRESSURE_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__TMC_CMH_VAC_SNS;

	//
	CX__VAR_ANALOG_CTRL  aCH__CFG_EXHAUST_PUMP_PRESSURE_TORR;
	CX__VAR_ANALOG_CTRL  aCH__CFG_EXHAUST_PUMP_TIMEOUT;

	//
	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_PUMP_PRESSURE_TORR;
	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_PUMP_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_PUMP_COMPLETE_STABLE_TIME;

	CX__VAR_ANALOG_CTRL  aCH__CFG_FAST_PUMP_PRESSURE_TORR;
	CX__VAR_ANALOG_CTRL  aCH__CFG_FAST_PUMP_TIMEOUT;

	//
	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_VENT_PRESSURE_TORR;
	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_VENT_TIMEOUT;

	CX__VAR_ANALOG_CTRL  aCH__CFG_FAST_VENT_PRESSURE_TORR;
	CX__VAR_ANALOG_CTRL  aCH__CFG_FAST_VENT_TIMEOUT;

	//
	CX__VAR_ANALOG_CTRL  aCH__CFG_VAC_LOWER_TOLERANCE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_VAC_UPPER_TOLERANCE;

	//
	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_PUMP_DELAY_TIME;
	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_VENT_DELAY_TIME;

	CX__VAR_ANALOG_CTRL  aCH__CFG_VALVE_CLOSE_DELAY_TIME;

	//
	CX__VAR_ANALOG_CTRL  aCH__TIME_COUNT;

	CX__VAR_ANALOG_CTRL  CFG_aCH__UPC_SETPOINT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_OVER_VENT_TIME;

	CX__VAR_DIGITAL_CTRL dCFG_CH__TM_BALLAST_CONTROL;
	CX__VAR_DIGITAL_CTRL dCFG_CH__TM_BALLAST_MODE;

	CX__VAR_DIGITAL_CTRL dCFG_CH__TM_BALLAST_DATALOG_ENDIS;

	CX__VAR_ANALOG_CTRL  aCFG_CH__TM_BALLAST_N2_VALUE;
	CX__VAR_ANALOG_CTRL  aCFG_CH__TM_BALLAST_N2_P_GAIN;
	CX__VAR_ANALOG_CTRL  aCFG_CH__TM_BALLAST_N2_I_GAIN;
	CX__VAR_ANALOG_CTRL  aCFG_CH__TM_BALLAST_N2_D_GAIN;

	CX__VAR_STRING_CTRL  sTM_BALLAST_OUTPUT_RESULT;
	CX__VAR_DIGITAL_CTRL dTM_BALLAST_CTRL_INIT_FLAG;

	CX__VAR_ANALOG_CTRL  aCH__CFG_ATM_PRESS_STS_TOLERANCE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_EQUALIZE_VENT_TIME;
	CX__VAR_DIGITAL_CTRL dCH__CFG_EQUAL_VLV_OPEN_WHEN_ATM;
	
	CX__VAR_ANALOG_CTRL  aCH__CFG_ATM_HIGH_PRESSURE_TORR;
	//


	//-------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	// OBJ : DB ...
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_SIM_VENT_TIME;
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_SIM_PUMP_TIME;

	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_TRANSFER_MODE;
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_REF_ATM_PRESSURE;
	CX__VAR_ANALOG_CTRL  aEXT_CH__CFG_REF_VAC_PRESSURE;

	// OBJ : IO ...
	// VENT VLV
	CX__VAR_DIGITAL_CTRL doEXT_CH__FAST_VENT_VLV__SET;

	bool bActive__SOFT_VENT_VLV__SET;
	CX__VAR_DIGITAL_CTRL doEXT_CH__SOFT_VENT_VLV__SET;
	
	bool bActive__ATM_EQUAL_VLV;
	CX__VAR_DIGITAL_CTRL doEXT_CH__ATM_EQUAL_VLV__SET;

	// PUMP VLV
	CX__VAR_DIGITAL_CTRL doEXT_CH__FAST_PUMP_VLV__SET;

	bool bActive__SOFT_PUMP_VLV__SET;
	CX__VAR_DIGITAL_CTRL doEXT_CH__SOFT_PUMP_VLV__SET;

	// SNS
	bool bActive__ATM_SNS_Virtual_Type;

	CX__VAR_DIGITAL_CTRL diEXT_CH__ATM_SENSOR;
	CString sDATA__ATM_ON;
	CString sDATA__ATM_OFF;

	CX__VAR_DIGITAL_CTRL diEXT_CH__VAC_SENSOR;
	CString sDATA__VAC_ON;
	CString sDATA__VAC_OFF;

	// BALLAST 
	CX__VAR_DIGITAL_CTRL doEXT_CH__BALLAST_VALVE_SET;
	CX__VAR_ANALOG_CTRL  aoEXT_CH__BALLAST_N2_SET;

	// OBJ : PUMP ...
	CII_EXT_OBJECT__CTRL *pPUMP__OBJ_CTRL;
	CX__VAR_STRING_CTRL  sEXT_CH__MON_PUMP_COMM_STS;
	CX__VAR_STRING_CTRL  sEXT_CH__MON_PUMP_RUN_STS;

	// OBJ : GAUGE ...
	CII_EXT_OBJECT__CTRL *pGAUGE__OBJ_CTRL;

	CX__VAR_ANALOG_CTRL  aiEXT_CH__TMC_CHM__PRESSURE_TORR;

	bool bActive__TMC_CHM__EXHAUST_PRESSURE;
	CX__VAR_ANALOG_CTRL  aiEXT_CH__TMC_CHM__EXHAUST_PRESSURE;

	// CHM LID ...
	bool bActive__LID_CLOSE;
	CX__VAR_DIGITAL_CTRL diEXT_CH__CHM_LID_CLOSE_SMS;
	//


	//------------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__CL_ALL_VLV;
	int  Call__CL_ALL_VLV(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__CL_PUMP_VLV;
	int  Call__CL_PUMP_VLV(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__OP_PUMP_VLV;
	int  Call__OP_PUMP_VLV(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__PUMP;
	int  Call__PUMP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int  _Fnc__PUMP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int  _Wait__PUMPING_PRESSURE(CII_OBJECT__VARIABLE* p_variable,
								 CII_OBJECT__ALARM* p_alarm,
								 CII__VAR_ANALOG_CTRL  *pch__gauge_pressure,
								 CII__VAR_ANALOG_CTRL  *pch__cfg_pressyre,
								 CII__VAR_ANALOG_CTRL  *pch__cfg_timeout,
								 const bool active__atm_sns,
								 CII__VAR_DIGITAL_CTRL *pch__atm_sns,
								 const CString& trg__atm_sts,
								 const bool active__vac_sns,
								 CII__VAR_DIGITAL_CTRL *pch__vac_sns,
								 const CString& trg__vac_sts,
								 const int alm_id__pumping_timeout);

	CString sMODE__VENT;
	int  Call__VENT(CII_OBJECT__VARIABLE* p_variable,
		            CII_OBJECT__ALARM* p_alarm);

	int  _Fnc__VENT(CII_OBJECT__VARIABLE* p_variable,
		            CII_OBJECT__ALARM* p_alarm);
	int  _Sub__VENT(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm);

	int  _Wait__VENTING_PRESSURE(CII_OBJECT__VARIABLE* p_variable,
								 CII_OBJECT__ALARM* p_alarm,
								 CII__VAR_ANALOG_CTRL  *pch__gauge_pressure,
								 CII__VAR_ANALOG_CTRL  *pch__cfg_pressyre,
								 CII__VAR_ANALOG_CTRL  *pch__cfg_timeout,
								 const bool active__atm_sns,
								 CII__VAR_DIGITAL_CTRL *pch__atm_sns,
								 const CString& trg__atm_sts,
								 const bool active__vac_sns,
								 CII__VAR_DIGITAL_CTRL *pch__vac_sns,
								 const CString& trg__vac_sts,
								 const int alm_id__venting_timeout);

	CString sMODE__AUTO_PUMP_VLV_CLOSE;
	int  Call__AUTO_PUMP_VLV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
								  CII_OBJECT__ALARM* p_alarm);

	int  Fnc__SIM_AUTO_PUMP_VLV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
									  CII_OBJECT__ALARM* p_alarm);
	int  Fnc__AUTO_PUMP_VLV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
								  CII_OBJECT__ALARM* p_alarm);


	// ...
	int  Check__VENT_ALL_VLV__CLOSE(CII_OBJECT__ALARM* p_alarm);
	int  Check__PUMP_ALL_VLV__CLOSE(CII_OBJECT__ALARM* p_alarm);

	int  Check__PUMP_VLV__OPEN(CII_OBJECT__ALARM* p_alarm);
	void Update__PUMP_VLV_STS(CII_OBJECT__ALARM* p_alarm);

	int  Fnc__VENT_ALL_VLV__CLOSE(CII_OBJECT__ALARM* p_alarm);
	int  Fnc__VENT_ALL_VLV__CLOSE_WITHOUT_EQUAL_VLV(CII_OBJECT__ALARM* p_alarm);
	int  Fnc__PUMP_ALL_VLV__CLOSE(CII_OBJECT__ALARM* p_alarm);

	int  Fnc__PUMP_FAST_VLV__OPEN(CII_OBJECT__ALARM* p_alarm);
	int  Fnc__PUMP_SOFT_VLV__OPEN(CII_OBJECT__ALARM* p_alarm);
	int  Fnc__PUMP_BALLAST_VLV__OPEN(CII_OBJECT__ALARM* p_alarm);

	int  Fnc__VENT_FAST_VLV__OPEN(CII_OBJECT__ALARM* p_alarm);
	int  Fnc__VENT_SOFT_VLV__OPEN(CII_OBJECT__ALARM* p_alarm);

	int  Fnc__CNTS_PG_Disable(CII_OBJECT__VARIABLE* p_variable,CString sLogEnDis);
	int  Fnc__MON__TM_Purge_PID_Ctrl(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	void  Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	void  Fnc__INTERLOCK(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	void  Fnc__MSG(const CString &sMsg);		// sCH__MSG
	void  Fnc__LOG(const CString &sLog);

	// ...
	int Check__CHM_LID_CLOSE(CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj__CHM_STD();
	~CObj__CHM_STD();

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
