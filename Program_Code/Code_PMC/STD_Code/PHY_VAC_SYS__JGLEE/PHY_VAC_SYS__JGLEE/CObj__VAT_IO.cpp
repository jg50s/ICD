#include "StdAfx.h"
#include "CObj__VAT_IO.h"
#include "CObj__VAT_IO__ALID.h"
#include "CObj__VAT_IO__DEF.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__VAT_IO::CObj__VAT_IO()
{

}
CObj__VAT_IO::~CObj__VAT_IO()
{

}

//-------------------------------------------------------------------------
int CObj__VAT_IO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__OPEN,  "OPEN");
		ADD__CTRL_VAR(sMODE__CLOSE, "CLOSE");

		ADD__CTRL_VAR(sMODE__PRESSURE, "PRESSURE");
		ADD__CTRL_VAR(sMODE__POSITION, "POSITION");

		ADD__CTRL_VAR(sMODE__BALLAST_TRANSFER, "BALLAST.TRANSFER");
		ADD__CTRL_VAR(sMODE__BALLAST_CHAMBER,  "BALLAST.CHAMBER");
	}
	return 1;
}
int CObj__VAT_IO::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATE_CHECK						1

#define MON_ID__IDLE_ERROR_CHECK				2
#define MON_ID__PROC_ERROR_CHECK				3


int CObj__VAT_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString item_list;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);
	}

	// PARA ...
	{
		str_name = "PARA.PRESSURE";
		STD__ADD_ANALOG(str_name, "torr", 3, 0.0, 10.0);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PRESSURE, str_name);
		
		str_name = "PARA.POSITION";
		STD__ADD_ANALOG(str_name, "%", 1, 0.0, 100.0);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_POSITION, str_name);

		str_name = "PARA.HOLD.SEC";
		STD__ADD_ANALOG(str_name, "sec", 1, 0.0, 5.0);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_HOLD_SEC, str_name);
	}

	// MON.PART ...
	{
		str_name = "MON.VAT.CTRL.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_VAT_CTRL_ACTIVE, str_name);

		str_name = "MON.VAT.ERROR.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_VAT_ERROR_ACTIVE, str_name);

		//
		str_name = "MON.VAT.PRESSURE.STABLE.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_VAT_PRESSURE_STABLE_ACTIVE, str_name);

		str_name = "MON.VAT.PRESSURE.ABORT.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_VAT_PRESSURE_ABORT_ACTIVE, str_name);
	}

	// MON.PRESSURE ...
	{
		str_name = "MON.SET.PRESSURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SET_PRESSURE, str_name);

		str_name = "MON.PRESSURE.TORR";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__MON_PRESSURE_TORR, str_name);

		str_name = "MON.PRESSURE.mTORR";
		STD__ADD_STRING_WITH_OPTION(str_name, -1, "L", "");
		LINK__VAR_STRING_CTRL(sCH__MON_PRESSURE_mTORR, str_name);

		str_name = "MON.SET.HOLD.SEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SET_HOLD_SEC, str_name);
	}
	// MON.POSITION ...
	{
		str_name = "MON.SET.POSITION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SET_POSITION, str_name);

		str_name = "MON.POSITION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_POSITION, str_name);
	}

	// MON SET.DATA ...
	{
		str_name = "MON.DO.APC_CTRL_MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_DO_APC_CTRL_MODE, str_name);

		str_name = "MON.AO.APC_SETPOINT_DATA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_AO_APC_SETPOINT_DATA, str_name);

		str_name = "MON.DO.APC_SETPOINT_TYPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_DO_APC_SETPOINT_TYPE, str_name);
	}
	// MON.GET DATA ...
	{
		str_name = "MON.DI.APC_STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_DI_APC_STATE, str_name);

		str_name = "MON.DI.APC_VLV_CLOSE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_DI_APC_VLV_CLOSE, str_name);

		str_name = "MON.DI.APC_VLV_OPEN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_DI_APC_VLV_OPEN, str_name);

		str_name = "MON.DI.APC_VLV_STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_DI_APC_VLV_STATE, str_name);
	}

	// MON : STABLE_IDLE ...
	{
		str_name = "MON.IDLE.PRESSURE.CHECK.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON READY");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_IDLE_PRESSURE_CHECK_ACTIVE, str_name);

		str_name = "MON.IDLE.PRESSURE.ABORT.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_IDLE_PRESSURE_ABORT_ACTIVE, str_name);

		//
		str_name = "MON.IDLE.PRESSURE.STABLE.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_IDLE_PRESSURE_STABLE_ACTIVE, str_name);

		//
		str_name = "MON.IDLE.PRESSURE.STABLE.MIN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IDLE_PRESSURE_STABLE_MIN, str_name);

		str_name = "MON.IDLE.PRESSURE.STABLE.MAX";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IDLE_PRESSURE_STABLE_MAX, str_name);

		str_name = "MON.IDLE.PRESSURE.STABLE.DELAY.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IDLE_PRESSURE_STABLE_DELAY_TIME, str_name);

		str_name = "MON.IDLE.PRESSURE.STABLE.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IDLE_PRESSURE_STABLE_CHECK_TIME, str_name);

		str_name = "MON.IDLE.PRESSURE.WARNING.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IDLE_PRESSURE_WARNING_CHECK_TIME, str_name);

		str_name = "MON.IDLE.PRESSURE.ABORT.MIN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IDLE_PRESSURE_ABORT_MIN, str_name);

		str_name = "MON.IDLE.PRESSURE.ABORT.MAX";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IDLE_PRESSURE_ABORT_MAX, str_name);

		str_name = "MON.IDLE.PRESSURE.ABORT.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_IDLE_PRESSURE_ABORT_CHECK_TIME, str_name);
	}
	// MON : STABLE_PROC ...
	{
		str_name = "MON.PROC.PRESSURE.CHECK.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON READY");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PROC_PRESSURE_CHECK_ACTIVE, str_name);

		str_name = "MON.PROC.PRESSURE.ABORT.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PROC_PRESSURE_ABORT_ACTIVE, str_name);

		//
		str_name = "MON.PROC.PRESSURE.STABLE.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PROC_PRESSURE_STABLE_ACTIVE, str_name);

		//
		str_name = "MON.PROC.PRESSURE.STABLE.MIN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PROC_PRESSURE_STABLE_MIN, str_name);

		str_name = "MON.PROC.PRESSURE.STABLE.MAX";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PROC_PRESSURE_STABLE_MAX, str_name);

		str_name = "MON.PROC.PRESSURE.STABLE.DELAY.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PROC_PRESSURE_STABLE_DELAY_TIME, str_name);

		str_name = "MON.PROC.PRESSURE.STABLE.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PROC_PRESSURE_STABLE_CHECK_TIME, str_name);

		str_name = "MON.PROC.PRESSURE.WARNING.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PROC_PRESSURE_WARNING_CHECK_TIME, str_name);

		str_name = "MON.PROC.PRESSURE.ABORT.MIN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PROC_PRESSURE_ABORT_MIN, str_name);

		str_name = "MON.PROC.PRESSURE.ABORT.MAX";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PROC_PRESSURE_ABORT_MAX, str_name);

		str_name = "MON.PROC.PRESSURE.ABORT.CHECK.TIME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PROC_PRESSURE_ABORT_CHECK_TIME, str_name);
	}

	// CFG : SYSTEM ...
	{
		str_name = "CFG.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_USE, str_name);

		//
		str_name = "CFG.PRESSURE.MIN.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 3, 0, 1, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PRESSURE_MIN_VALUE, str_name);

		str_name = "CFG.PRESSURE.MAX.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 3, 0.1, 500, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PRESSURE_MAX_VALUE, str_name);

		str_name = "CFG.PRESSURE.MAX.mTORR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CFG_PRESSURE_MAX_mTORR, str_name);

		str_name = "CFG.PRESSURE.DEC.VALUE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "dec", 0, 0, 5, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PRESSURE_DEC_VALUE, str_name);

		//
		str_name = "CFG.PRESSURE.STABLE.DELAY.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 3600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PRESSURE_STABLE_DELAY_TIME, str_name);

		str_name = "CFG.PRESSURE.STABLE.CHECK.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PRESSURE_STABLE_CHECK_TIME, str_name);

		//
		str_name = "CFG.PRESSURE.WARNING.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 3600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PRESSURE_WARNING_TIMEOUT, str_name);

		str_name = "CFG.PRESSURE.ABORT.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 3600, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PRESSURE_ABORT_TIMEOUT, str_name);

		//
		str_name = "CFG.PRESSURE.WARNING.BAND";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PRESSURE_WARNING_BAND, str_name);

		str_name = "CFG.PRESSURE.ABORT.BAND";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PRESSURE_ABORT_BAND, str_name);

		str_name = "CFG.IDLE.PRESSURE.WARNING.BAND";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_IDLE_PRESSURE_WARNING_BAND, str_name);

		str_name = "CFG.IDLE.PRESSURE.ABORT.BAND";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_IDLE_PRESSURE_ABORT_BAND, str_name);

		str_name = "CFG.Zero.Setpoint.Tolerance.Compensation";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 1, 0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_Zero_Setpoint_Tolerance_Compensation, str_name);

		//
		str_name = "CFG.OPEN.INTERLOCK.OVER_PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "torr", 0, 1, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_OPEN_INTERLOCK_OVER_PRESSURE, str_name);
	}

	// Transfer.Ballast Config ...
	{
		str_name = "CFG.TRANSFER.BALLAST.CTRL_MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "POSITION  PRESSURE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_TRANSFER_BALLAST_CTRL_MODE, str_name);

		str_name = "CFG.TRANSFER.BALLAST.POSITION";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TRANSFER_BALLAST_POSITION, str_name);

		str_name = "CFG.TRANSFER.BALLAST.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr", 1, 0, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TRANSFER_BALLAST_PRESSURE, str_name);

		str_name = "CFG.TRANSFER.BALLAST.TOL.PRESSURE.MIN";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr", 1, 0, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TRANSFER_BALLAST_TOL_PRESSURE_MIN, str_name);

		str_name = "CFG.TRANSFER.BALLAST.TOL.PRESSURE.MAX";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr", 1, 1, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TRANSFER_BALLAST_TOL_PRESSURE_MAX, str_name);

		str_name = "CFG.TRANSFER.BALLAST.TOL.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.1, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TRANSFER_BALLAST_TOL_TIMEOUT, str_name);
	}
	// Chamber.Ballast Config ...
	{
		str_name = "CFG.CHAMBER.BALLAST.CTRL_MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "POSITION  PRESSURE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_CHAMBER_BALLAST_CTRL_MODE, str_name);

		str_name = "CFG.CHAMBER.BALLAST.POSITION";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CHAMBER_BALLAST_POSITION, str_name);

		str_name = "CFG.CHAMBER.BALLAST.PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr", 0, 0, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CHAMBER_BALLAST_PRESSURE, str_name);

		str_name = "CFG.CHAMBER.BALLAST.TOL.PRESSURE.MIN";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr", 1, 0, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CHAMBER_BALLAST_TOL_PRESSURE_MIN, str_name);

		str_name = "CFG.CHAMBER.BALLAST.TOL.PRESSURE.MAX";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr", 1, 1, 1000, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CHAMBER_BALLAST_TOL_PRESSURE_MAX, str_name);

		str_name = "CFG.CHAMBER.BALLAST.TOL.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.1, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CHAMBER_BALLAST_TOL_TIMEOUT, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATE_CHECK);

		p_variable->Add__MONITORING_PROC(1.0, MON_ID__IDLE_ERROR_CHECK);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__PROC_ERROR_CHECK);
	}
	return 1;
}

int CObj__VAT_IO::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ", sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	iLIST_ALID__VAT.RemoveAll();

	// ...
	{
		alarm_id = ALID__VAT__CONTROL_WARNING_RANGE;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "VAT Control Warning Range Alarm.";

		alarm_msg = "VAT control was over the warning range. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__VAT__CONTROL_ABORT_RANGE;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "VAT Control Abort Range Alarm.";

		alarm_msg = "VAT Control was over the abort range. \n";
		alarm_msg += "For safety, MFC flow will be stopped !!\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__VAT__CONTROL_IDLE_WARNING_RANGE;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "During Idle, VAT Control Warning Range Alarm.";

		alarm_msg = "VAT control was over the warning range. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__VAT__CONTROL_IDLE_ABORT_RANGE;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "During Idle, VAT Control Abort Range Alarm.";

		alarm_msg = "VAT control was over the abort range. \n";
		alarm_msg += "For Safety, VAT will be stopped !!\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__TRANSFER_BALLAST_PRESSURE_WAIT;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "\"Transfer ballast pressure wait\" occurred !";

		alarm_msg = "Please, check Ballast valve or N2 valve.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__TRANSFER_BALLAST_OVER_PRESSURE;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "\"Transfer ballast over pressure\" occurred !";

		alarm_msg = "Please, check Ballast valve or N2 valve.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__CHAMBER_BALLAST_PRESSURE_WAIT;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "\"Chamber ballast pressure wait\" occurred !";

		alarm_msg = "Please, check Ballast valve or N2 valve.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__CHAMBER_BALLAST_OVER_PRESSURE;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "\"Chamber ballast over pressure\" occurred !";

		alarm_msg = "Please, check Ballast valve or N2 valve.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__VAT_CONTROL_ABORTED;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "VAT Control Aborted !.";

		alarm_msg  = "VAT Control Error !.\n";
		alarm_msg += "Please, check VAT controller.";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__VAT_NOT_USE;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "In VAT config page, VAT's use is selected to \"NOT USE\".";

		alarm_msg = "Please, check VAT's use option in the config page. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__TV_INTERLOCK_STATE;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "TV Interlock 관련 Digital Output이 \"ON\" 되어 있습니다.";

		alarm_msg = "TV Interlock 관련 Digital Output 상태를 확인 바랍니다. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__VAT_OPEN_TIMEOUT;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "\"VAT open timeout\" occurred !";

		alarm_msg = "Please, check VAT's board or cable. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__VAT_CLOSE_TIMEOUT;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "\"VAT close timeout\" occurred !";

		alarm_msg = "Please, check VAT's board or cable. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__VAT_ENABLE_SENSOR_ERROR;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "\"VAT,Enable Sensor Error\" occurred !";

		alarm_msg = "Please, check VAT's Enable Sensor State. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__VAT_READY_ERROR;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "\"VAT,Ready Error\" occurred !";

		alarm_msg = "Please, check VAT's All Sensor State. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__OPEN_INTERLOCK_OVER_PRESSURE;
		iLIST_ALID__VAT.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Open Interlock !";

		alarm_msg = "Open 명령을 수행 할 수 없습니다. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__VAT_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xI_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xI_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

		xI_LOG_CTRL->DISABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG(log_msg);

		xI_LOG_CTRL->ENABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;

	// ...
	CCommon_Utility x_utility;

	// OBJ : DB_SYS 
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "SIM.PRESSURE.TORR";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SIM_PRESSURE_TORR, obj_name,var_name);

		//
		var_name = "MON.SYSTEM.PROCESS.ACTIVE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_SYSTEM_PROCESS_ACTIVE, obj_name,var_name);

		//
		var_name = "MON.INTERLOCK.HEAVY.ACTIVE.SYSTEM";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_SYSTEM, obj_name,var_name);

		var_name = "MON.INTERLOCK.LIGHT.ACTIVE.SYSTEM";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_INTERLOCK_LIGHT_ACTIVE_SYSTEM, obj_name,var_name);

		//
		var_name = "MON.INTERLOCK.HEAVY.ACTIVE.CHAMBER";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_CHAMBER, obj_name,var_name);

		var_name = "MON.INTERLOCK.LIGHT.ACTIVE.CHAMBER";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MON_INTERLOCK_LIGHT_ACTIVE_CHAMBER, obj_name,var_name);
	}

	// PARA.PRESSURE_UNIT ...
	{
		def_name = "DATA.PRESSURE_UNIT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		if(def_data.CompareNoCase("mTORR") == 0)			iPARA__PRESSURE_UNIT = _PRESSURE_UNIT__mTORR;
		else  												iPARA__PRESSURE_UNIT = _PRESSURE_UNIT__TORR;
	}

	// VAT_CTRL.TYPE ...
	def_name = "DATA.CONTROL_TYPE";
	p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

	if(def_data.CompareNoCase("OBJ") == 0)		iDATA__VAT_CTRL_TYPE = _VAT_CTRL_TYPE__OBJ;
	else										iDATA__VAT_CTRL_TYPE = _VAT_CTRL_TYPE__IO;

	if(iDATA__VAT_CTRL_TYPE == _VAT_CTRL_TYPE__OBJ)
	{
		def_name = "OBJ__VAT_NAME";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
		
		pOBJ_CTRL__VAT = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		// COMMD.INFO ...
		{
			def_name = "VAT_CMMD.INIT";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sVAT_CMMD__INIT = def_data;

			def_name = "VAT_CMMD.CLOSE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sVAT_CMMD__CLOSE = def_data;

			def_name = "VAT_CMMD.OPEN";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sVAT_CMMD__OPEN = def_data;

			def_name = "VAT_CMMD.POSITION";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sVAT_CMMD__POSITION = def_data;

			def_name = "VAT_CMMD.PRESSURE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
			sVAT_CMMD__PRESSURE = def_data;
		}

		// PARA.INFO ...
		{
			def_name = "VAR__PARA_PRESSURE_VALUE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, var_name);
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__VAT__PARA_PRESSURE_VALUE, obj_name,var_name);
			
			def_name = "VAR__PARA_POSITION_PERCENT";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, var_name);
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__VAT__PARA_POSITION_PER, obj_name,var_name);
		}
		// CUR.INFO ...
		{
			def_name = "VAR__CUR_PRESSURE_VALUE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, var_name);
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__VAT__CUR_PRESSURE_VALUE, obj_name,var_name);

			def_name = "VAR__CUR_POSITION_PERCENT";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, var_name);
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__VAT__CUR_POSITION_PER, obj_name,var_name);
		}
	}
	else     // LINK.IO ...
	{
		// LINK : OUTPUT ...
		{
			// DO.APC_CTRL_MODE ...
			{
				def_name = "CH__DO_APC_CTRL_MODE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,    obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_APC_CTRL_MODE, obj_name,var_name);
			}
			// AO.APC_SETPOINT_DATA ...
			{
				def_name = "CH__AO_APC_SETPOINT_DATA";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,       obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AO_APC_SETPOINT_DATA, obj_name,var_name);
			}
			// DO.APC_SETPOINT_TYPE ...
			{
				def_name = "CH__DO_APC_SETPOINT_TYPE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,        obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_APC_SETPOINT_TYPE, obj_name,var_name);
			}
		}

		// LINK : INPUT ...
		{
			// DI.APC_STATE ...
			{
				def_name = "CH__DI_APC_STATE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_APC_STATE,  obj_name,var_name);
			}

			// AI.APC_PRESSURE ...
			{
				def_name = "CH__AI_APC_PRESSURE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,  obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_APC_PRESSURE, obj_name,var_name);
			}
			// AI.APC_POSITION ...
			{
				def_name = "CH__AI_APC_POSITION";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name,  obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_APC_POSITION, obj_name,var_name);
			}

			// DI.APC_VLV_CLOSE ...
			{
				def_name = "CH__DI_APC_VLV_CLOSE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				bool def_check = x_utility.Check__Link(ch_name);
				bActive__DI_APC_VLV_CLOSE = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_APC_VLV_CLOSE, obj_name,var_name);
				}
			}

			// DI.APC_VLV_OPEN ...
			{
				def_name = "CH__DI_APC_VLV_OPEN";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				bool def_check = x_utility.Check__Link(ch_name);
				bActive__DI_APC_VLV_OPEN = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_APC_VLV_OPEN, obj_name,var_name);
				}
			}

			// DI.APC_VLV_STATE ...
			{
				def_name = "CH__DI_APC_VLV_STATE";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

				bool def_check = x_utility.Check__Link(ch_name);
				bActive__DI_APC_VLV_STATE = def_check;

				if(def_check)
				{
					p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_APC_VLV_STATE, obj_name,var_name);
				}
			}
		}

		// ...
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__VAT_IO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	int flag = -1;

	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg.Format("Start [%s] ... By %s \n", mode, p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());

		sCH__OBJ_MSG->Set__DATA(log_msg);

		log_bff.Format(" * %s <- %.3f \n", 
						aCH__PARA_PRESSURE->Get__VARIABLE_NAME(),
						aCH__PARA_PRESSURE->Get__VALUE());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %.3f \n", 
						aCH__PARA_POSITION->Get__VARIABLE_NAME(),
						aCH__PARA_POSITION->Get__VALUE());
		log_msg += log_bff;

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		dCH__MON_IDLE_PRESSURE_CHECK_ACTIVE->Set__DATA(STR__OFF);
		dCH__MON_IDLE_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__OFF);	
		dCH__MON_IDLE_PRESSURE_ABORT_ACTIVE->Set__DATA(STR__OFF);	

		dCH__MON_PROC_PRESSURE_CHECK_ACTIVE->Set__DATA(STR__OFF);
		dCH__MON_PROC_PRESSURE_STABLE_ACTIVE->Set__DATA(STR__OFF);	
		dCH__MON_PROC_PRESSURE_ABORT_ACTIVE->Set__DATA(STR__OFF);	
	}

	if(dCH__CFG_USE->Check__DATA(STR__YES) < 0)
	{
		int alm_id = ALID__VAT_NOT_USE;
		CString alm_msg;
		CString r_act;

		alm_msg.Format("VAT [%s] command is aborted !.\n", mode);

		p_alarm->Check__ALARM(alm_id,r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
	}
	else
	{
		flag = 1;
	}

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__OPEN)
		{
			flag = Call__OPEN(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__CLOSE)
		{
			flag = Call__CLOSE(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__POSITION)
		{
			flag = Call__POSITION(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__PRESSURE)
		{
			flag = Call__PRESSURE(p_variable, p_alarm);

			dCH__MON_IDLE_PRESSURE_CHECK_ACTIVE->Set__DATA(STR__READY);
			dCH__MON_PROC_PRESSURE_CHECK_ACTIVE->Set__DATA(STR__READY);
		}
		ELSE_IF__CTRL_MODE(sMODE__BALLAST_TRANSFER)
		{
			flag = Call__BALLAST_TRANSFER(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__BALLAST_CHAMBER)
		{
			flag = Call__BALLAST_CHAMBER(p_variable, p_alarm);
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);		
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__VAT_IO::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATE_CHECK)			Mon__STATE_CHECK(p_variable, p_alarm);

	if(id == MON_ID__IDLE_ERROR_CHECK)		Mon__IDLE_ERROR_CHECK(p_variable, p_alarm);
	if(id == MON_ID__PROC_ERROR_CHECK)		Mon__PROC_ERROR_CHECK(p_variable, p_alarm);

	return 1;
}
