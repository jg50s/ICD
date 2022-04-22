#include "stdafx.h"

#include "CObj__DURAPORT_SERIAL.h"
#include "CObj__DURAPORT_SERIAL__ALID.h"
#include "CObj__DURAPORT_SERIAL__DEF.h"


//--------------------------------------------------------------------------------
void CObj__DURAPORT_SERIAL
::Fnc__DRV_LOG(const CString& log_msg)
{
	if(dCH__DRV_LOG_PARAM_START_STOP->Check__DATA("STOP") > 0)
	{
		return;
	}
	
	xDRV__LOG_CTRL->WRITE__LOG(log_msg);
}

void CObj__DURAPORT_SERIAL
::Fnc__APP_LOG(const CString& log_msg)
{
	if(iFlag__APP_LOG < 1)
	{
		return;
	}
	
	xAPP__LOG_CTRL->WRITE__LOG(log_msg);
}

int  CObj__DURAPORT_SERIAL
::Is__ONLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(sCH__MON_COMMUNICATION_STATE->Check__DATA(STR__ONLINE) < 0)
	{
		int alarm_id = ALID__OFFLINE;
	
		p_alarm->Post__ALARM(alarm_id);
		return -1;
	}
	return 1;
}

int  CObj__DURAPORT_SERIAL
::Is__REMOTE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{	
	return OBJ_AVAILABLE;
}

int CObj__DURAPORT_SERIAL
::Fnc__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	CString str_log;
	CString fnc_name = "Fnc__INIT()";
	
	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);
	
	str_log.Format("INIT Starting ...");
	Fnc__APP_LOG(str_log);
	
	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);

	if(state > 0)
	{
		Fnc__APP_LOG("INIT Seq Start... !");
		state = Seq__INIT(p_variable, p_alarm, fnc_name);
	}
	return state;
}
int CObj__DURAPORT_SERIAL
::Seq__INIT(CII_OBJECT__VARIABLE* p_variable, 
			CII_OBJECT__ALARM* p_alarm, 
			const CString str_caller)
{
	CString fnc_name = "Seq__INIT()";

	CString str_log;
	CString var_data;

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// ...
	{
		var_data = siCH__FIRMWARE_VER->Get__STRING();
		sCH__MON_FIRMWARE_VER->Set__DATA(var_data);
	}

	return 1;
}

// ...
int CObj__DURAPORT_SERIAL
::Fnc__HOME(CII_OBJECT__VARIABLE* p_variable, 
			CII_OBJECT__ALARM* p_alarm, 
			const CString str_caller)
{
	CString str_log;
	CString fnc_name = "Fnc__HOME()";
	
	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);
	
	str_log.Format("HOME Starting ...");
	Fnc__APP_LOG(str_log);

	// ...
	double cfg_sec = 2.0;

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return -1;

	// HOME ...
	{
		doCH__OPR_MAIN_SET->Set__DATA("HOME");
		
		if(iActive__SIM_MODE > 0)
		{
			Sleep(500);

			sCH__BIT_STS__DOOR_OPENED->Set__DATA(STR__OFF);
			sCH__BIT_STS__DOOR_CLOSED->Set__DATA(STR__ON);
		}

		if(sCH__BIT_STS__DOOR_OPENED->When__DATA(STR__OFF, cfg_sec) <= 0)		return -11;
		if(sCH__BIT_STS__DOOR_CLOSED->When__DATA(STR__ON,  cfg_sec) <= 0)		return -12;

		if(iActive__SIM_MODE > 0)
		{
			Sleep(500);

			sCH__BIT_STS__POD_DOCKED->Set__DATA(STR__OFF);
			sCH__BIT_STS__POD_UNDOCKED->Set__DATA(STR__ON);
		}

		if(sCH__BIT_STS__POD_DOCKED->When__DATA(STR__OFF,  cfg_sec) <= 0)		return -13;
		if(sCH__BIT_STS__POD_UNDOCKED->When__DATA(STR__ON, cfg_sec) <= 0)		return -14;

		dCH__LP_STATE->Set__DATA(STR_INITIALIZED);
	}	

	return 1;
}

// ...
int CObj__DURAPORT_SERIAL
::Fnc__DOOR_OPEN(CII_OBJECT__VARIABLE* p_variable, 
			     CII_OBJECT__ALARM* p_alarm, 
			     const CString str_caller)
{
	CString fnc_name = "Fnc__OPEN()";
	
	// ...
	{
		CString str_log;
		CString str_bff;

		str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);

		str_log.Format("OPEN Starting ...");
		str_log += str_bff;

		str_log.Format(" * %s <- %s \n", 
						dCH__CFG_CTRL_MODE->Get__CHANNEL_NAME(),
						dCH__CFG_CTRL_MODE->Get__STRING());
		str_log += str_bff;

		Fnc__APP_LOG(str_log);
	}

	if(dCH__CFG_CTRL_MODE->Check__DATA(STR__AUTO) > 0)	
	{
		return _Auto__DOOR_OPEN(p_variable, p_alarm);
	}
	return _Manual__DOOR_OPEN(p_variable, p_alarm);
}
int CObj__DURAPORT_SERIAL
::_Auto__DOOR_OPEN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	double cfg_sec = 2.0;

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return -1;

	// MAINT_MODE ...
	{
		doCH__OPR_MAINT_MODE_SET->Set__DATA(STR__OFF);

		if(sCH__BIT_STS__MAINT_MODE->When__DATA(STR__OFF, cfg_sec) <= 0)				return -10001;
	}

	// DOOR.OPEN ...
	{
		doCH__OPR_MAIN_SET->Set__DATA(STR__OPEN);

		if(iActive__SIM_MODE > 0)
		{
			if((sCH__BIT_STS__LATCH_CONDITION->Check__DATA(STR__ON) < 0)
			|| (sCH__BIT_STS__DOOR_OPENED->Check__DATA(STR__ON)  < 0)
			|| (sCH__BIT_STS__DOOR_CLOSED->Check__DATA(STR__OFF) < 0))
			{
				Sleep(500);

				sCH__BIT_STS__LATCH_CONDITION->Set__DATA(STR__ON);
				sCH__BIT_STS__DOOR_OPENED->Set__DATA(STR__ON);
				sCH__BIT_STS__DOOR_CLOSED->Set__DATA(STR__OFF);
			}
		}

		if(sCH__BIT_STS__LATCH_CONDITION->When__DATA(STR__ON, cfg_sec) <= 0)			return -31;

		if(sCH__BIT_STS__DOOR_OPENED->When__DATA(STR__ON,  cfg_sec) <= 0)				return -33;
		if(sCH__BIT_STS__DOOR_CLOSED->When__DATA(STR__OFF, cfg_sec) <= 0)				return -34;

		dCH__LP_STATE->Set__DATA(STR_OPENED);
	}	

	return 1;
}
int CObj__DURAPORT_SERIAL
::_Manual__DOOR_OPEN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return -10001;

	double cfg_sec = 2.0;

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return -1;

	// MAINT_MODE ...
	{
		doCH__OPR_MAINT_MODE_SET->Set__DATA(STR__ON);

		if(sCH__BIT_STS__MAINT_MODE->When__DATA(STR__ON, cfg_sec) <= 0)					return -10001;
	}

	// VAC.ON ...
	{
		doCH__OPR_VAC_SET->Set__DATA(STR__ON);

		if(iActive__SIM_MODE > 0)
		{
			if(sCH__BIT_STS__VACUUM_CONDITION->Check__DATA(STR__ON) < 0)
			{
				Sleep(500);
				sCH__BIT_STS__VACUUM_CONDITION->Set__DATA(STR__ON);
			}
		}

		if(sCH__BIT_STS__VACUUM_CONDITION->When__DATA(STR__ON, cfg_sec) <= 0)			return -11;
	}

	// LATCH.ON ...
	{
		doCH__OPR_LATCH_SET->Set__DATA(STR__ON);

		if(iActive__SIM_MODE > 0)
		{
			if(sCH__BIT_STS__UNLATCH_CONDITION->Check__DATA(STR__OFF) < 0)
			{
				Sleep(500);

				sCH__BIT_STS__LATCH_CONDITION->Set__DATA(STR__OFF);
				sCH__BIT_STS__UNLATCH_CONDITION->Set__DATA(STR__OFF);
			}
		}

		// if(sCH__BIT_STS__LATCH_CONDITION->When__DATA(STR__ON, cfg_sec)    <= 0)			return -21;
		if(sCH__BIT_STS__UNLATCH_CONDITION->When__DATA(STR__OFF, cfg_sec) <= 0)			return -22;
	}

	// DOOR.OPEN ...
	{
		doCH__OPR_PORT_DOOR_OPEN_SET->Set__DATA(STR__ON);

		if(iActive__SIM_MODE > 0)
		{
			if((sCH__BIT_STS__LATCH_CONDITION->Check__DATA(STR__ON) < 0)
			|| (sCH__BIT_STS__DOOR_OPENED->Check__DATA(STR__ON)  < 0)
			|| (sCH__BIT_STS__DOOR_CLOSED->Check__DATA(STR__OFF) < 0))
			{
				Sleep(500);

				sCH__BIT_STS__LATCH_CONDITION->Set__DATA(STR__ON);
				sCH__BIT_STS__DOOR_OPENED->Set__DATA(STR__ON);
				sCH__BIT_STS__DOOR_CLOSED->Set__DATA(STR__OFF);
			}
		}

		if(sCH__BIT_STS__LATCH_CONDITION->When__DATA(STR__ON, cfg_sec) <= 0)			return -31;

		//
		doCH__OPR_DOOR_LIFT_DOWN_SET->Set__DATA(STR__ON);

		if(sCH__BIT_STS__DOOR_OPENED->When__DATA(STR__ON,  cfg_sec) <= 0)				return -33;
		if(sCH__BIT_STS__DOOR_CLOSED->When__DATA(STR__OFF, cfg_sec) <= 0)				return -34;

		dCH__LP_STATE->Set__DATA(STR_OPENED);
	}	

	// MAINT_MODE ...
	{
		doCH__OPR_MAINT_MODE_SET->Set__DATA(STR__OFF);
	}

	return 1;
}

// ...
int CObj__DURAPORT_SERIAL
::Fnc__DOOR_CLOSE(CII_OBJECT__VARIABLE* p_variable, 
			      CII_OBJECT__ALARM* p_alarm, 
			      const CString str_caller)
{
	CString fnc_name = "Fnc__CLOSE()";

	// ...
	{
		CString str_log;
		CString str_bff;
	
		str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	
		str_log.Format("CLOSE Starting ...");
		str_log += str_bff;

		str_log.Format(" * %s <- %s \n", 
					   dCH__CFG_CTRL_MODE->Get__CHANNEL_NAME(),
					   dCH__CFG_CTRL_MODE->Get__STRING());
		str_log += str_bff;

		Fnc__APP_LOG(str_log);
	}

	if(dCH__CFG_CTRL_MODE->Check__DATA(STR__AUTO) > 0)	
	{
		return _Auto__DOOR_CLOSE(p_variable, p_alarm);
	}
	return _Manual__DOOR_CLOSE(p_variable, p_alarm);
}
int CObj__DURAPORT_SERIAL
::_Auto__DOOR_CLOSE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	double cfg_sec = 2.0;

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return -1;

	// MAINT_MODE ...
	{
		doCH__OPR_MAINT_MODE_SET->Set__DATA(STR__OFF);

		if(sCH__BIT_STS__MAINT_MODE->When__DATA(STR__OFF, cfg_sec) <= 0)			return -10001;
	}

	// DOOR.CLOSE ...
	{
		doCH__OPR_MAIN_SET->Set__DATA(STR__CLOSE);

		if(iActive__SIM_MODE > 0)
		{
			if((sCH__BIT_STS__LATCH_CONDITION->Check__DATA(STR__OFF) < 0)
			|| (sCH__BIT_STS__DOOR_OPENED->Check__DATA(STR__OFF) < 0)
			|| (sCH__BIT_STS__DOOR_CLOSED->Check__DATA(STR__ON)  < 0))
			{
				Sleep(500);

				sCH__BIT_STS__LATCH_CONDITION->Set__DATA(STR__OFF);
				sCH__BIT_STS__DOOR_OPENED->Set__DATA(STR__OFF);
				sCH__BIT_STS__DOOR_CLOSED->Set__DATA(STR__ON);
			}
		}

		if(sCH__BIT_STS__LATCH_CONDITION->When__DATA(STR__OFF, cfg_sec) <= 0)		return -11;
		if(sCH__BIT_STS__DOOR_OPENED->When__DATA(STR__OFF, cfg_sec) <= 0)			return -12;
		if(sCH__BIT_STS__DOOR_CLOSED->When__DATA(STR__ON,  cfg_sec) <= 0)			return -13;

		dCH__LP_STATE->Set__DATA(STR_CLOSED);
	}	

	// MAINT_MODE ...
	{
		doCH__OPR_MAINT_MODE_SET->Set__DATA(STR__OFF);
	}

	return 1;
}
int CObj__DURAPORT_SERIAL
::_Manual__DOOR_CLOSE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	return -10001;

	double cfg_sec = 2.0;

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return -1;

	// MAINT_MODE ...
	{
		doCH__OPR_MAINT_MODE_SET->Set__DATA(STR__ON);

		if(sCH__BIT_STS__MAINT_MODE->When__DATA(STR__ON, cfg_sec) <= 0)					return -10001;
	}

	// DOOR.CLOSE ...
	{
		doCH__OPR_PORT_DOOR_OPEN_SET->Set__DATA(STR__OFF);

		if(iActive__SIM_MODE > 0)
		{
			if((sCH__BIT_STS__LATCH_CONDITION->Check__DATA(STR__OFF)  < 0)
				|| (sCH__BIT_STS__DOOR_OPENED->Check__DATA(STR__OFF) < 0)
				|| (sCH__BIT_STS__DOOR_CLOSED->Check__DATA(STR__ON)  < 0))
			{
				Sleep(500);

				sCH__BIT_STS__LATCH_CONDITION->Set__DATA(STR__OFF);
				sCH__BIT_STS__DOOR_OPENED->Set__DATA(STR__OFF);
				sCH__BIT_STS__DOOR_CLOSED->Set__DATA(STR__ON);
			}
		}

		if(sCH__BIT_STS__LATCH_CONDITION->When__DATA(STR__OFF,  cfg_sec) <= 0)		return -11;
		if(sCH__BIT_STS__DOOR_OPENED->When__DATA(STR__OFF, cfg_sec) <= 0)			return -12;
		if(sCH__BIT_STS__DOOR_CLOSED->When__DATA(STR__ON,  cfg_sec) <= 0)			return -13;

		dCH__LP_STATE->Set__DATA(STR_CLOSED);
	}	

	// LATCH.OFF ...
	{
		doCH__OPR_LATCH_SET->Set__DATA(STR__OFF);

		if(iActive__SIM_MODE > 0)
		{
			if(sCH__BIT_STS__UNLATCH_CONDITION->Check__DATA(STR__ON) < 0)
			{
				Sleep(500);

				sCH__BIT_STS__UNLATCH_CONDITION->Set__DATA(STR__ON);
			}
		}

		if(sCH__BIT_STS__UNLATCH_CONDITION->When__DATA(STR__ON, cfg_sec) <= 0)		return -22;
	}

	// VAC.OFF ...
	{
		doCH__OPR_VAC_SET->Set__DATA(STR__OFF);

		if(iActive__SIM_MODE > 0)
		{
			if(sCH__BIT_STS__VACUUM_CONDITION->Check__DATA(STR__OFF) < 0)
			{
				Sleep(500);
				sCH__BIT_STS__VACUUM_CONDITION->Set__DATA(STR__OFF);
			}
		}

		if(sCH__BIT_STS__VACUUM_CONDITION->When__DATA(STR__OFF, cfg_sec) <= 0)		return -31;
	}

	// MAINT_MODE ...
	{
		doCH__OPR_MAINT_MODE_SET->Set__DATA(STR__OFF);
	}

	return 1;
}

// ...
int CObj__DURAPORT_SERIAL
::Fnc__LOAD(CII_OBJECT__VARIABLE* p_variable, 
			CII_OBJECT__ALARM* p_alarm, 
			const CString str_caller)
{
	CString str_log;
	CString fnc_name = "Fnc__LOAD()";
	
	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);
	
	str_log.Format("LOAD Starting ...");
	Fnc__APP_LOG(str_log);

	// ...
	double cfg_sec = 2.0;

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return -1;

	// LOAD ...
	{
		_Update__LPx_INIT();

		doCH__OPR_LOAD_SET->Set__DATA("LOAD");

		if(iActive__SIM_MODE > 0)
		{
			sCH__BIT_STS__POD_CLAMPED->Set__DATA(STR__ON);
			sCH__BIT_STS__POD_UNCLAMPED->Set__DATA(STR__OFF);

			Sleep(500);

			sCH__BIT_STS__DOOR_OPENED->Set__DATA(STR__ON);
			sCH__BIT_STS__DOOR_CLOSED->Set__DATA(STR__OFF);

			sCH__BIT_STS__POD_DOCKED->Set__DATA(STR__ON);
			sCH__BIT_STS__POD_UNDOCKED->Set__DATA(STR__OFF);
		}

		if(sCH__BIT_STS__POD_CLAMPED->When__DATA(STR__ON,    cfg_sec) <= 0)			return -11;
		if(sCH__BIT_STS__POD_UNCLAMPED->When__DATA(STR__OFF, cfg_sec) <= 0)			return -12;

		if(sCH__BIT_STS__DOOR_OPENED->When__DATA(STR__ON,    cfg_sec) <= 0)			return -21;
		if(sCH__BIT_STS__DOOR_CLOSED->When__DATA(STR__OFF,   cfg_sec) <= 0)			return -22;

		if(sCH__BIT_STS__POD_DOCKED->When__DATA(STR__ON,     cfg_sec) <= 0)			return -31;
		if(sCH__BIT_STS__POD_UNDOCKED->When__DATA(STR__OFF,  cfg_sec) <= 0)			return -32;

		dCH__LP_STATE->Set__DATA(STR_LOADED);
	}

	return 1;
}

int CObj__DURAPORT_SERIAL
::Fnc__UNLOAD(CII_OBJECT__VARIABLE* p_variable, 
		 	  CII_OBJECT__ALARM* p_alarm, 
			  const CString str_caller)
{
	CString str_log;
	CString fnc_name = "Fnc__UNLOAD()";
	
	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);
	
	str_log.Format("UNLOAD Starting ...");
	Fnc__APP_LOG(str_log);
	
	// ...
	double cfg_sec = 2.0;

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return -1;

	// UNLOAD ...
	{
		doCH__OPR_LOAD_SET->Set__DATA("UNLOAD");
		
		if(iActive__SIM_MODE > 0)
		{
			sCH__BIT_STS__DOOR_OPENED->Set__DATA(STR__OFF);
			sCH__BIT_STS__DOOR_CLOSED->Set__DATA(STR__ON);

			sCH__BIT_STS__POD_DOCKED->Set__DATA(STR__OFF);
			sCH__BIT_STS__POD_UNDOCKED->Set__DATA(STR__ON);

			Sleep(500);

			sCH__BIT_STS__POD_CLAMPED->Set__DATA(STR__ON);
			sCH__BIT_STS__POD_UNCLAMPED->Set__DATA(STR__OFF);
		}

		if(sCH__BIT_STS__POD_CLAMPED->When__DATA(STR__OFF,   cfg_sec) <= 0)			return -11;
		if(sCH__BIT_STS__POD_UNCLAMPED->When__DATA(STR__ON,  cfg_sec) <= 0)			return -12;

		if(sCH__BIT_STS__DOOR_OPENED->When__DATA(STR__OFF,   cfg_sec) <= 0)			return -21;
		if(sCH__BIT_STS__DOOR_CLOSED->When__DATA(STR__ON,    cfg_sec) <= 0)			return -22;

		if(sCH__BIT_STS__POD_DOCKED->When__DATA(STR__OFF,    cfg_sec) <= 0)			return -31;
		if(sCH__BIT_STS__POD_UNDOCKED->When__DATA(STR__ON,   cfg_sec) <= 0)			return -32;

		dCH__LP_STATE->Set__DATA(STR_UNLOADED);
	}

	return 1;
}

// ...
int CObj__DURAPORT_SERIAL
::Fnc__SHUTTLE_IN(CII_OBJECT__VARIABLE* p_variable, 
			      CII_OBJECT__ALARM* p_alarm, 
			      const CString str_caller)
{
	CString fnc_name = "Fnc__SHUTTLE_IN()";
	
	// ...
	{
		CString str_log;
		CString str_bff;

		str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);

		str_log.Format("SHUTTLE_IN Starting ...");
		str_log += str_bff;

		str_log.Format(" * %s <- %s \n", 
						dCH__CFG_CTRL_MODE->Get__CHANNEL_NAME(),
						dCH__CFG_CTRL_MODE->Get__STRING());
		str_log += str_bff;

		Fnc__APP_LOG(str_log);
	}

	if(dCH__CFG_CTRL_MODE->Check__DATA(STR__AUTO) > 0)	
		return _Auto__SHUTTLE_IN(p_variable, p_alarm);

	return _Manual__SHUTTLE_IN(p_variable, p_alarm);
}
int CObj__DURAPORT_SERIAL
::_Auto__SHUTTLE_IN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	double cfg_sec = 2.0;

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return -1;

	// LOAD ...
	{
		doCH__OPR_LOAD_SET->Set__DATA("LOAD");

		if(iActive__SIM_MODE > 0)
		{
			Sleep(500);

			sCH__BIT_STS__POD_DOCKED->Set__DATA(STR__ON);
			sCH__BIT_STS__POD_UNDOCKED->Set__DATA(STR__OFF);
		}

		if(sCH__BIT_STS__POD_DOCKED->When__DATA(STR__ON, cfg_sec)	 <= 0)			return -11;
		if(sCH__BIT_STS__POD_UNDOCKED->When__DATA(STR__OFF, cfg_sec) <= 0)			return -12;

		dCH__LP_STATE->Set__DATA(STR_DOCKED);
	}

	return 1;
}
int CObj__DURAPORT_SERIAL
::_Manual__SHUTTLE_IN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	double cfg_sec = 2.0;

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return -1;

	// DOCK ...
	{
		doCH__OPR_DOCK_SET->Set__DATA("DOCK");

		if(iActive__SIM_MODE > 0)
		{
			Sleep(500);

			sCH__BIT_STS__POD_DOCKED->Set__DATA(STR__ON);
			sCH__BIT_STS__POD_UNDOCKED->Set__DATA(STR__OFF);
		}

		if(sCH__BIT_STS__POD_DOCKED->When__DATA(STR__ON, cfg_sec)	 <= 0)			return -11;
		if(sCH__BIT_STS__POD_UNDOCKED->When__DATA(STR__OFF, cfg_sec) <= 0)			return -12;

		dCH__LP_STATE->Set__DATA(STR_DOCKED);
	}

	return 1;
}

int CObj__DURAPORT_SERIAL
::Fnc__SHUTTLE_OUT(CII_OBJECT__VARIABLE* p_variable, 
				   CII_OBJECT__ALARM* p_alarm,
				   const CString str_caller)
{
	CString fnc_name = "Fnc__SHUTTLE_OUT()";

	// ...
	{
		CString str_log;
		CString str_bff;

		str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);

		str_log.Format("SHUTTLE_OUT Starting ...");
		str_log += str_bff;

		str_log.Format(" * %s <- %s \n", 
						dCH__CFG_CTRL_MODE->Get__CHANNEL_NAME(),
						dCH__CFG_CTRL_MODE->Get__STRING());
		str_log += str_bff;

		Fnc__APP_LOG(str_log);
	}

	if(dCH__CFG_CTRL_MODE->Check__DATA(STR__AUTO) > 0)	
		return _Auto__SHUTTLE_OUT(p_variable, p_alarm);

	return _Manual__SHUTTLE_OUT(p_variable, p_alarm);
}
int CObj__DURAPORT_SERIAL
::_Auto__SHUTTLE_OUT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	double cfg_sec = 2.0;

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return -1;

	// UNDOCK ...
	{
		doCH__OPR_LOAD_SET->Set__DATA("UNLOAD");

		if(iActive__SIM_MODE > 0)
		{
			Sleep(500);

			sCH__BIT_STS__POD_DOCKED->Set__DATA(STR__OFF);
			sCH__BIT_STS__POD_UNDOCKED->Set__DATA(STR__ON);
		}

		if(sCH__BIT_STS__POD_DOCKED->When__DATA(STR__OFF,  cfg_sec) <= 0)			return -11;
		if(sCH__BIT_STS__POD_UNDOCKED->When__DATA(STR__ON, cfg_sec) <= 0)			return -12;

		dCH__LP_STATE->Set__DATA(STR_UNDOCKED);
	}
	return 1;
}
int CObj__DURAPORT_SERIAL
::_Manual__SHUTTLE_OUT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	double cfg_sec = 2.0;

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return -1;

	// UNDOCK ...
	{
		doCH__OPR_DOCK_SET->Set__DATA("UNDOCK");

		if(iActive__SIM_MODE > 0)
		{
			Sleep(500);

			sCH__BIT_STS__POD_DOCKED->Set__DATA(STR__OFF);
			sCH__BIT_STS__POD_UNDOCKED->Set__DATA(STR__ON);
		}

		if(sCH__BIT_STS__POD_DOCKED->When__DATA(STR__OFF,  cfg_sec) <= 0)			return -11;
		if(sCH__BIT_STS__POD_UNDOCKED->When__DATA(STR__ON, cfg_sec) <= 0)			return -12;

		dCH__LP_STATE->Set__DATA(STR_UNDOCKED);
	}
	return 1;
}

// ...
int CObj__DURAPORT_SERIAL
::Fnc__CLAMP(CII_OBJECT__VARIABLE* p_variable, 
			 CII_OBJECT__ALARM* p_alarm, 
			 const CString str_caller)
{
	CString str_log;
	CString fnc_name = "Fnc__CLAMP()";
	
	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);
	
	str_log.Format("CLAMP Starting ...");
	Fnc__APP_LOG(str_log);
	
	// ...
	double cfg_sec = 2.0;

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return -1;

	// CLAMP ...
	{
		doCH__OPR_CLAMP_SET->Set__DATA("CLAMP");
		
		if(iActive__SIM_MODE > 0)
		{
			Sleep(500);

			sCH__BIT_STS__POD_CLAMPED->Set__DATA(STR__ON);
			sCH__BIT_STS__POD_UNCLAMPED->Set__DATA(STR__OFF);
		}

		if(sCH__BIT_STS__POD_CLAMPED->When__DATA(STR__ON,    cfg_sec) <= 0)			return -11;
		if(sCH__BIT_STS__POD_UNCLAMPED->When__DATA(STR__OFF, cfg_sec) <= 0)			return -12;

		dCH__LP_STATE->Set__DATA(STR_CLAMPED);
	}

	return 1;
}

// ...
int CObj__DURAPORT_SERIAL
::Fnc__UNCLAMP(CII_OBJECT__VARIABLE* p_variable, 
			  CII_OBJECT__ALARM* p_alarm, 
			  const CString str_caller)
{
	CString str_log;
	CString fnc_name = "Fnc__UNCLAMP()";
	
	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);
	
	str_log.Format("UNCLAMP Starting ...");
	Fnc__APP_LOG(str_log);
	
	// ...
	double cfg_sec = 2.0;

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return -1;

	// UNCLAMP ...
	{
		doCH__OPR_CLAMP_SET->Set__DATA("UNCLAMP");
		
		if(iActive__SIM_MODE > 0)
		{
			Sleep(500);

			sCH__BIT_STS__POD_CLAMPED->Set__DATA(STR__OFF);
			sCH__BIT_STS__POD_UNCLAMPED->Set__DATA(STR__ON);
		}

		if(sCH__BIT_STS__POD_CLAMPED->When__DATA(STR__OFF,  cfg_sec) <= 0)			return -11;
		if(sCH__BIT_STS__POD_UNCLAMPED->When__DATA(STR__ON, cfg_sec) <= 0)			return -12;

		dCH__LP_STATE->Set__DATA(STR_UNCLAMPED);
	}

	return 1;
}

int CObj__DURAPORT_SERIAL
::_Check__ERROR_CODE(const CString& err_xxxx)
{
	if(err_xxxx.GetLength() < 1)			return -1;

	char ch_err = err_xxxx.GetAt(0);
	if(ch_err != 'E')						return -2;

	// ...
	CStringArray l_rsp;
	CString str_del = " ";
	
	CString str_data = err_xxxx;
	str_data.Delete(0, 1);
	
	_Get__STRING_ARRAY(str_data,str_del, l_rsp);
	
	if(l_rsp.GetSize() > 1)
	{
		CString err_code  = l_rsp[0];
		CString err_title = l_rsp[1];

		int i_errcode = atoi(err_code);
		CString err_msg = _Get__Error_Code(i_errcode);

		mMNG__ERR_CODE.Load__Error_Code(err_code,err_title,err_msg);
	}
	else
	{
		CString err_code  = err_xxxx;
		CString err_title = "????";
		CString err_msg   = "____";

		mMNG__ERR_CODE.Load__Error_Code(err_code,err_title,err_msg);
	}
	return 1;
}
CString CObj__DURAPORT_SERIAL
::_Get__Error_Code(const int err_code)
{
	CString str_alarm;
	CString str_reason;
	CString str_action;

	if(_Get__Error_Info(err_code, str_alarm,str_reason,str_action) > 0)
	{
		return _Get__Error_Msg(err_code, str_alarm,str_reason,str_action);
	}

	// ...
	CString err_msg;

	err_msg.Format("Unknown Code (%1d)", err_code);
	return err_msg;
}
CString CObj__DURAPORT_SERIAL
::_Get__Error_Msg(const int err_code,
				  const CString& str_alarm,
				  const CString& str_reason,
				  const CString& str_action)
{
	CString err_msg;

	err_msg.Format("Error Code : %1d (0x%02X)", err_code,err_code);
	err_msg += "\n";

	err_msg += "Alarms : ";
	err_msg += "\n";
	err_msg += str_alarm;
	err_msg += "\n";

	err_msg += "Reasons : ";
	err_msg += "\n";
	err_msg += str_reason;
	err_msg += "\n";

	err_msg += "Actions : ";
	err_msg += "\n";
	err_msg += str_action;

	return err_msg;
}
int CObj__DURAPORT_SERIAL
::_Get__Error_Info(const int err_code,
				   CString& str_alarm,
				   CString& str_reason,
				   CString& str_action)
{
	// ...
	{
		str_alarm  = "";
		str_reason = "";
		str_action = "";
	}

	if(err_code == 2) 
	{
		str_alarm  = "ERR_InvalidAxis";
		str_reason = "information is wrong.";
		str_action = "����(Host) ��� �߿��� �������� Ȯ��.";

		return 1;
	}
	if(err_code == 3) 
	{
		str_alarm  = "ERR_InvalidData";
		str_reason = "�Է� Data�� �ý����� ������ ������ �ʰ��Ͽ��ų�, ����, ��ȣ ���� �߸� �ԷµǾ��� ��쿡 �߻�";
		str_action = "Data Ȯ�� �� ���Է�";

		return 1;
	}	
	if(err_code == 4) 
	{
		str_alarm = "ERR_EventState";

		str_reason  = "Stop/EmStop Event�� �߻�.";
		str_reason += "\n";
		str_reason += "E-Stop Switch�� ������ �ְų� Up/Down Limit Sensor�� Sensing�ǰ� ����.";

		str_action  = "1. E-stop Switch�� ������ �ִ��� Ȯ��";
		str_action += "\n";
		str_action += "2. Z-axis Limit sensor�� �����Ǿ� �ִ��� Ȯ��";
		str_action += "\n";
		str_action += "3. Servo Driver�� Alarm �������� Ȯ��";

		return 1;
	}
	if(err_code == 5) 
	{
		str_alarm  = "ERR_DriverNotOn";

		str_reason = "Driver(Amp)�� OFF ������";

		str_action  = "1. Servo Motor Drive�� ON (AMP ON)";
		str_action += "\n";
		str_action += "2. E-stop Switch�� ������ �ִ��� Ȯ��";

		return 1;
	}
	if(err_code == 6) 
	{
		str_alarm  = "ERR_HomeNotDone";
		str_reason = "Homing�� �Ϸ���� ���� ���¿��� ����� �������� ��� �߻�";
		str_action = "All Homing�� �ǽ�";

		return 1;
	}
	if(err_code == 7) 
	{
		str_alarm  = "ERR_DriverErrorState";
		str_reason = "Servo Motor Driver���� Error�� �߻���";
		str_action = "Servo Drive�� Reset �Ǵ� Power�� Shutdown�� �� (����� ��) �ٽ� Reset��";

		return 1;
	}
	if(err_code == 9)
	{
		str_alarm  = "ERR_ErrorNotCleared";
		str_reason = "Error�� Clear���� ���� ���¿��� �ٸ� ����� ��������";
		str_action = "RESET��Command�� Error�� Clear ��Ų �� ���� ����� ����";

		return 1;
	}
	if(err_code == 10) 
	{
		str_alarm  = "ERR_PODNotOpened";
		str_reason = "Scan(Re-mapping) ����� FOUP Close ���¿��� ��������";
		str_action = "FOUP Open ���¿��� SCAN ����� ��õ�";

		return 1;
	}
	if(err_code == 11) 
	{
		str_alarm  = "ERR_PODTransIn";
		str_reason = "POD Docking ��� �� ������ �ð�(5��) ���� POD Trans In Sensor�� Sensing ���� �ʾ���";

		str_action  = "Trans In Sensor�� Sensing ���� ���� ������ �ľ�";
		str_action += "\n";
		str_action += "  1. POD Trans Motor�� �̻󿩺� ����";
		str_action += "\n";
		str_action += "  2. Sensor �̻� ���� ����";
		str_action += "\n";
		str_action += "  3. POD Door�� Port Door ���̿� ��ֹ��� �ִ��� ����";

		return 1;
	}
	if(err_code == 12) 
	{
		str_alarm  = "ERR_PODTransOut";
		str_reason = "POD Undocking ��� �� ������ �ð�(5��) ���� POD Trans Out Sensor�� Sensing ���� �ʾ���";

		str_action  = "Trans Out Sensor�� Sensing ���� ���� ������ �ľ�";
		str_action += "\n";
		str_action += "  1. POD Trans Motor�� �̻󿩺� ����";
		str_action += "\n";
		str_action += "  2. Sensor �̻� ���� ����";

		return 1;
	}
	if(err_code == 13)
	{
		str_alarm  = "ERR_LatchOpen";
		str_reason = "Latch Open ��ġ���� Latch Open Sensor�� Sensing���� �ʾ���";

		str_action  = "Latch Open Sensor�� Sensing���� ���� ������ �ľ�";
		str_action += "\n";
		str_action += "  1. Latch SOL. �� �Ǹ����� �̻󿩺� ����";
		str_action += "\n";
		str_action += "  2. Sensor �̻� ���� ����";

		return 1;
	}
	if(err_code == 14)
	{
		str_alarm  = "ERR_LatchClose";
		str_reason = "Latch Close ��ġ���� Latch Close Sensor�� Sensing���� �ʾ���";

		str_action  = "Latch Close Sensor�� Sensing���� ���� ������ �ľ�";
		str_action += "\n";
		str_action += "  1. Latch SOL. �� �Ǹ����� �̻󿩺� ����";
		str_action += "\n";
		str_action += "  2. Sensor �̻� ���� ����";

		return 1;
	}
	if(err_code == 15) 
	{
		str_alarm  = "ERR_MappingArmOpen";
		str_reason = "Mapping Arm Open ���� �� ���� �ð��ȿ�( overtime 5��) Mapping Arm Open Sensor�� Sensing���� �ʾ���";

		str_action  = "Mapping Arm Open ���� �� Mapping Arm Open Sensor�� Sensing���� ���� ���� �ľ�";
		str_action += "\n";
		str_action += "  1. Mapping Arm motor�� �̻󿩺� ����";
		str_action += "\n";
		str_action += "  2. Sensor �̻� ���� ����";

		return 1;
	}
	if(err_code == 16) 
	{
		str_alarm  = "ERR_MappingArmClose";
		str_reason = "Mapping Arm Close ���� �� ���� �ð��ȿ�( overtime 5��) Mapping Arm Open Sensor�� Sensing���� �ʾ���";

		str_action  = "Mapping Arm Close ���� �� Mapping Arm Close Sensor�� Sensing���� ���� ���� �ľ�";
		str_action += "\n";
		str_action += "  1. Mapping Arm motor�� �̻󿩺� ����";
		str_action += "\n";
		str_action += "  2. Sensor �̻� ���� ����";

		return 1;
	}
	if(err_code == 17) 
	{
		str_alarm = "ERR_VacuumOn";

		str_reason  = "POD Trans In�� Vacuum solenoid�� On�Ͽ����� �̶� Vacuum Sensor�� On ���� �ʾ���.";
		str_reason += "\n";
		str_reason += "Vacuum Cup�� FOUP door���̿� Vacuum���� �������� �ʾ���";

		str_action  = "1.Vacuum�� Spec ��� ���޵ǰ� �ִ��� ����(- 50kPa)";
		str_action += "\n";
		str_action += "2. FOUP Door�� PDO Door�� �����Ǵ� ���� ����";
		str_action += "\n";
		str_action += "3. FOUP�� Latch hole�� ���� ���¸� ����";
		str_action += "\n";
		str_action += "4. Vacuum Sensor�� �̻󿩺� ����";

		return 1;
	}
	if(err_code == 18) 
	{
		str_alarm  = "ERR_VacuumOff";
		str_reason = "Vacuum solenoid�� Off�� �� Vacuum sensor�� Off���� �ʾ���";

		str_action  = "1. Vacuum Sensor�� On/Off Threshold ���� spec ��� setting �Ǿ� �ִ��� ����";
		str_action += "\n";
		str_action += "2. Vacuum Sensor�� �̻󿩺� ����";

		return 1;
	}
	if(err_code == 19) 
	{
		str_alarm  = "ERR_PodPlacedImproperly";
		str_reason = "FOUP�� PDO�� Stage���� �ùٸ��� ������ �ʾ���";

		str_action  = "1. FOUP �� Stage���� �ùٸ��� �������� Ȯ��";
		str_action += "\n";
		str_action += "2. Presence LED �� Placement LED�� �������� Ȯ��";
		str_action += "\n";
		str_action += "3. FOUP�� �ùٸ��� ������ ���¿��� Placement sensor�� ��� Sensing�ǰ� �ִ��� Ȯ��";
		str_action += "\n";
		str_action += "4. Placement Sensor�� �̻󿩺� ����";

		return 1;
	}
	if(err_code == 20) 
	{
		str_alarm  = "ERR_PODDoorNotExist";
		str_reason = "POD Door�� �������� �ʾ���";

		str_action  = "1. Vacuum�� Spec��� ���޵ǰ� �ִ��� Ȯ��";
		str_action += "\n";
		str_action += "2. Vacuum Sensor�� �̻󿩺� Ȯ��";

		return 1;
	}
	if(err_code == 21) 
	{
		str_alarm  = "ERR_PODNotExist";
		str_reason = "FOUP�� ���� ���¿��� ������ �õ� �Ͽ���";

		str_action  = "1. FOUP�� Stage���� �ùٸ��� ���� �ִ��� Ȯ��";
		str_action += "\n";
		str_action += "2. Placement Sensor �� Presence Sensor�� �̻󿩺� Ȯ��";

		return 1;
	}
	if(err_code == 22) 
	{
		str_alarm  = "ERR_WaferProtrude";

		str_reason  = "1. Close ���� ���� Wafer Protrusion sensor�� Sensing �Ǿ���";
		str_reason += "\n";
		str_reason += "2. Up/Down ���� �߿� Wafer Protrusion sensor�� sensing �Ǿ���(Safety)";

		str_action  = "1. Wafer�� FOUP ������ Ƣ�� ���� �ִ��� Ȯ��.";
		str_action += "\n";
		str_action += "2. ���߱� ���̿� �̹����� �ִ��� Ȯ��";
		str_action += "\n";
		str_action += "3. ���߱� ������ Alignment�� Ȯ��";

		return 1;
	}
	if(err_code == 23) 
	{
		str_alarm  = "ERR_InvalidScanStartPosition";
		str_reason = "Mapping�� �����ϴ� Start Position Data �� ���ո��ϰ� Setting �Ǿ���";

		str_action  = "ù��° Wafer�� ��ġ�� �ùٸ��� �����Ǿ�����, ";
		str_action += "\n";
		str_action += "Slot ���� �� �� Slot�� �Ÿ� Data�� �ùٸ��� �����Ǿ����� Ȯ��";
	
		return 1;
	}
	if(err_code == 24) 
	{
		str_alarm  = "ERR_ScanTimeOver";
		str_reason = "Up �Ǵ� Down ���� �ð��� 10�ʸ� �ʰ���";

		str_action = "Mapping�� �ӵ� �� Up/Down ���� �ð��� ���� �ð� ���� Setting �Ǿ� �ִ��� Ȯ��";

		return 1;
	}
	if(err_code == 25) 
	{
		str_alarm  = "ERR_StopScanMotion";
		str_reason = "Mapping�� ������ ���� Up/Down ������ ����";
		str_action = "Mapping�� �ӵ� �� Up/Down ���� �ð��� ���� �ð� ���� Setting �Ǿ� �ִ��� Ȯ��";

		return 1;
	}
	if(err_code == 26) 
	{
		str_alarm  = "ERR_WaferThickness";
		str_reason = "�ΰ� �̻��� Wafer�� ��ħ";

		str_action  = "1. Wafer�� �ùٸ��� ���������� Ȯ��";
		str_action += "\n";
		str_action += "2. Wafer�� �β��� �ùٸ��� �����Ǿ����� Ȯ��";
		str_action += "\n";
		str_action += "	(W-T�� ���� �����ؾ� �ϴµ� �̴� Mapping Data�� Wafer ���� �β��� �ٰ���)";

		return 1;
	}
	if(err_code == 27) 
	{
		str_alarm  = "ERR_WaferPosition";
		str_reason = "Wafer�� �� Slot���̿� ���� ����";

		str_action  = "1. Wafer�� �ùٸ��� ���������� Ȯ��.";
		str_action += "\n";
		str_action += "2. Wafer�� ù��° ��ġ�� �� Teaching ��";

		return 1;
	}
	if(err_code == 28) 
	{
		str_alarm  = "ERR_InvalidScanInput";
		str_reason = "Wafer Detection Sensor�� ���� ����������";

		str_action  = "1. Wafer���� Sensor������ �Է� ���¸� ����.";
		str_action += "\n";
		str_action += "2. Mapping Sensor�� �̻󿩺� Ȯ��";

		return 1;
	}
	if(err_code == 29) 
	{
		str_alarm  = "ERR_InvalidScanData";
		
		str_reason  = "�ʹ� ���� Wafer�� Sensing ��.";
		str_reason += "\n";
		str_reason += "�� Wafer Sensing�� Chattering���� ���� Wafer ���� On/Off point�� �ʹ� ����.";

		str_action  = "1. Wafer���� Sensor������ �Է� ���¸� ����.";
		str_action += "\n";
		str_action += "2. Z-axis�� �������� Wafer Sensing�� Chattering�� �ִ��� ����.";

		return 1;
	}
	if(err_code == 30) 
	{
		str_alarm  = "ERR_UnloadIdentifyTimeOver";
		str_reason = "FOUP�� PDO�κ��� ���� �� 10�� �̳��� Unload button�� �������� �ʾ���.";
		str_action = "";

		return 1;
	}
	if(err_code == 31) 
	{
		str_alarm  = "ERR_StopTimeOver";
		str_reason = "Time interval�� ���ǵǰ� Motor�� �� �̻��� ȸ����.";
		str_action = "";

		return 1;
	}
	if(err_code == 32) 
	{
		str_alarm  = "ERR_EscapeSensorTimeOver";
		str_reason = "Homing�� ������ �ð� �ȿ� Homing Bracket�� Homing Sensor�� ����� ����.";
		str_action = "1. Homing �ӵ��� �ʹ� ���� �������� ����.";

		return 1;
	}
	if(err_code == 33) 
	{
		str_alarm  = "ERR_HomeStopWithAnotherCondition";
		str_reason = "The motor working has stopped due to a reason except for Limit Sensor Detection.";
		str_action = "";

		return 1;
	}
	if(err_code == 34) 
	{
		str_alarm  = "ERR_IllegalLimitSensor";
		str_reason = "Homing�� �����̴� �ݴ� ������ Limit sensor�� sensing��.";
		str_action = "1. Homing ���� �Ʒ��� +Limit sensor�� Sensing �Ǿ� �ִ��� ����.";

		return 1;
	}
	if(err_code == 35) 
	{
		str_alarm  = "ERR_LimitSensorIncorrect";
		str_reason = "Homing ���� �ΰ��� Limit sensor�� ��� sensing��.";
		str_action = "1. Homing ���� �ΰ��� Limit Sensor�� ��� Sensing�Ǿ� �ִ��� ����.";

		return 1;
	}
	if(err_code == 36) 
	{
		str_alarm  = "ERR_AxisPositionIncorrect";
		str_reason = "������ ��ġ Data�� 200Pulse�̻��� ������ ��.";
		str_action = "1. ������ ����";

		return 1;
	}
	if(err_code == 37)
	{
		str_alarm  = "ERR_HomeConditionNotCorrect";

		str_reason  = "Homing������ �ƴ�.";
		str_reason += "\n";
		str_reason += "  1. POD�� ���� ��� ";
		str_reason += "\n";
		str_reason += "    1.1 Vacuum�� On�̰� Latch�� Unlock.";
		str_reason += "\n";
		str_reason += "    1.2 Vacuum�� Off�� Latch�� Lock.";
		str_reason += "\n";
		str_reason += "  2. POD�� ���� ��� Vacuum�� On�̰� Latch�� Lock.";

		str_action = "1. PDO�� door �� Stage�κ��� ��� ��ü�� �����ϰ� �������� ���¿��� Homing�� ��.";

		return 1;
	}
	if(err_code == 38) 
	{
		str_action  = "ERR_LimitSensorNotIn";
		str_reason  = "Latch�� Open/Close�� Limit Sensor�� ���� ���� �ʾҴ�.";
		
		str_action  = "1. Latch�� Open/Close���� �� Limit sensor�� ���� ���� ���� ������ �ľ�";
		str_action += "\n";
		str_action += "2. All HOM�� �ǽ�";

		return 1;
	}
	if(err_code == 39) 
	{
		str_alarm  = "ERR_OutOfSwLimit";
		str_reason = "1. ��ġ �������� Sw Limit �� �̻���.";

		str_action  = "1. Software Limit �� ������ ��ġ�� �����Ѵ�.";
		str_action += "\n";
		str_action += "2. ��ġ ������ ����.";

		return 1;
	}
	if(err_code == 40) 
	{
		str_alarm  = "ERR_PinchPoint";
		str_reason = "Pinch point sensor�� ������.";

		str_action  = "1. Pinch sensor�� ���߱� Sensor ���̿� �̹����� �ִ��� ����.";
		str_action += "2. ���߱� sensor������ alignment�� �ٽ� ����.";

		return 1;
	}
	if(err_code == 47) 
	{
		str_alarm  = "ERR_DropValidSignal";
		str_reason = "Response is generated to exceed defined time interval.";
		str_action = "������ ����";

		return 1;
	}
	if(err_code == 48) 
	{
		str_alarm  = "ERR_UnexpectedPodAppear";
		str_reason = "Response is generated to exceed defined time interval.";
		str_action = "������ ����";

		return 1;
	}
	if(err_code == 49) 
	{
		str_alarm  = "ERR_UnexpectedPodDisappear";
		str_reason = "Response is generated to exceed defined time interval.";
		str_action = "������ ����";

		return 1;
	}
	if(err_code == 51) 
	{
		str_alarm  = "ERR_FlashErase";
		str_reason = "Backup Data is not erased normally.";
		str_action = "������ ����";
	
		return 1;
	}
	if(err_code == 52) 
	{
		str_alarm  = "ERR_FlashWrite";
		str_reason = "Backup Data is not correctly written.";
		str_action = "������ ����";

		return 1;
	}
	if(err_code == 53) 
	{
		str_alarm  = "ERR_FlashVerify";
		str_reason = "Backup Data is not correctly written.";
		str_action = "������ ����";

		return 1;
	}
	if(err_code == 54) 
	{
		str_alarm  = "ERR_CrashData";
		str_reason = "Backup Data�� ���������� �Էµ��� ����.";
		str_action = "1. Data�� ��� �ְ� Save�Ѵ�.";

		return 1;
	}
	if(err_code == 55) 
	{
		str_alarm  = "ERR_SwLimitOver";
		str_reason = "Motor�� ���� �� SW Limit �� ����ħ.";
		str_action = "1. ������ �ϴ� ������ġ�� S/W ���� ���� ����.";

		return 1;
	}
	if(err_code == 56)
	{
		str_alarm  = "ERR_HwLimitOver";
		str_reason = "Motor�� ���� �� H/W Limit sensor�� ������.";

		str_action  = "1. Homing �� �ٽ� �ٽ� ���۽��� ����.";
		str_action += "\n";
		str_action += "2. H/W Limit�� ������ �ϴ� ������ġ�� ���� ����.";

		return 1;
	}
	if(err_code == 57) 
	{
		str_alarm  = "ERR_TrackingError";
		str_reason = "���� �� ��ǥ ��ġ�� ���� ��ġ���� ������ ����.";
		str_action = "1. Servo drive�� gain�� �����Ѵ�.";

		return 1;
	}
	if(err_code == 58)
	{
		str_alarm  = "ERR_EmStopPressed";
		str_reason = "���� �� E-Stop button�� ������.";
		str_action = "1. E-Stop ��Ȳ�� ������ �� �絿�� ��Ų��.";

		return 1;
	}
	if(err_code == 59) 
	{
		str_alarm  = "ERR_DriverError";
		str_reason = "Servo Drive Error�� ������.";
		str_action = "1. Power�� OFF/ON �� �Ŀ� Amp On �� Homing�� ������ �� �ٽ� ���� ��Ų��.";

		return 1;
	}
	if(err_code == 60) 
	{
		str_alarm  = "ERR_IncorrectDockingPosition";
		str_reason = "Docking�� Stage�� �ڷ� �и�";
		str_action = "1.Reset�� �ϰų� Homeing�� �Ѵ�.";

		return 1;
	}
	if(err_code == 61) 
	{
		str_alarm  = "ERR_TpComTimeOut";
		str_reason = "TP�κ��� �����ֱ� ���� �Է��� ����.";

		str_action  = "1. TP Cable�� �����Ѵ�.";
		str_action += "\n";
		str_action += "2. Consult with the provider.";
	
		return 1;
	}
	if(err_code == 62) 
	{
		str_alarm  = "ERR_TpNotConnect";
		str_reason = "TP�� ������� �ʾ���.";

		str_action  = "1. TP Cable�� �����Ѵ�.";
		str_action += "\n";
		str_action += "2. Consult with the provider.";

		return 1;
	}
	if(err_code == 63)
	{
		str_alarm  = "ERR_QuitCommunication";
		str_reason = "-";
		str_action = "-";

		return 1;
	}
	if(err_code == 64) 
	{
		str_alarm  = "ERR_PodLock";
		str_reason = "POD Lock ���� �� POD Lock sensor�� �������� �ʾ���.";
		str_action = "1. FOUP Lock Position���� Lock sensor�� sensing �ȵ� ������ �ľ�.";

		return 1;
	}
	if(err_code == 65)
	{
		str_alarm  = "ERR_PodUnlock";
		str_reason = "POD Unlock ���� �� POD Unlock sensor�� �������� �ʾ���.";
		str_action = "1. FOUP Unlock position���� Unlock sensor�� sensing�ȵ� ������ �ľ�.";

		return 1;
	}
	if(err_code == 66)
	{
		str_alarm  = "ERR_PortDoorOpen";
		str_reason = "Port door open ���� �� Port door open sensor�� �������� �ʾ���.";
		str_action = "1. PDO Door�� Open ���¿��� Port door open sensor�� sensing���� ���� ������ �ľ�.";

		return 1;
	}
	if(err_code == 67) 
	{
		str_alarm  = "ERR_PortDoorClose";
		str_reason = "Port door close ���� �� Port door close sensor�� �������� �ʾ���.";
		str_action = "1. PDO Door�� Close ���¿��� Port door close sensor�� sensing���� ���� ������ �ľ�.";

		return 1;
	}
	if(err_code == 68)
	{
		str_alarm  = "ERR_MaintMode";
		str_reason = "Maint_Mode �� Enable��.";
		str_action = "1. Maint_Mode�� Disable ��Ų��.";

		return 1;
	}
	if(err_code == 69)
	{
		str_alarm  = "ERR_NotMaintMode";
		str_reason = "Maint_Mode �� Enable�� �ƴ�.";
		str_action = "1. Maint_Mode�� Enable ��Ų��.";

		return 1;
	}
	if(err_code == 70)
	{
		str_alarm  = "ERR_InvalidArgument";
		str_reason = "���ǵ��� ���� ��ɾ��� Parameter�� ���ŵǾ���.";
		str_action = "1. ����� �ùٸ� ���Ŀ� ���߾� ������.";

		return 1;
	}
	if(err_code == 71)
	{
		str_alarm  = "ERR_BarcodeComTimeOut";
		str_reason = "BCR�κ��� Data�� ���ŵ��� ����.";

		str_action  = "1. BCR Cable�� Ȯ���Ѵ�.";
		str_action += "\n";
		str_action += "2. BCR�� ���� �����ϴ����� Ȯ���Ѵ�.";
		str_action += "\n";
		str_action += "3. COM3 Port�� �̻��� �ִ����� �����Ѵ�.";

		return 1;
	}
	if(err_code == 72)
	{
		str_alarm  = "ERR_BarcodeUnknownResponse";
		str_reason = "The setting OK of BCR and data other than ERR are received.";

		str_action  = "1. BCR Cable�� Ȯ���Ѵ�.";
		str_action += "\n";
		str_action += "2. BCR�� ���� �����ϴ����� Ȯ���Ѵ�.";
		str_action += "\n";
		str_action += "3. COM3 Port�� �̻��� �ִ����� �����Ѵ�.";

		return 1;
	}
	if(err_code == 73)
	{
		str_alarm  = "ERR_BL_600NotDefinedError";
		str_reason = "BCR�κ��� ���� Error code�� 0-18��.";
		str_action = "";

		return 1;
	}
	if(err_code == 74)
	{
		str_alarm  = "ERR_BL_600MalFunction";
		str_reason = "BCR�� ���������� �������� ����.";
		str_action = "";

		return 1;
	}
	if(err_code == 75)
	{
		str_alarm  = "ERR_BarcodeDataReadError";
		str_reason = "BCR�κ��� ������ 3�� ���� ����.";
	
		str_action  = "1. BCR�� ���� �����ϴ����� Ȯ���Ѵ�.";
		str_action += "\n";
		str_action += "2. BCR type�� �ùٸ��� �����Ǿ� �ִ��� Ȯ���Ѵ�.";

		return 1;
	}
	if(err_code == 76)
	{
		str_alarm  = "ERR_BarcodeNotExist";
		str_reason = "BCR�� disable�Ǿ� ����.";

		str_action  = "BCR�� Enable ��Ų��.";
		str_action += "\n";
		str_action += "\"MAIN=>SET=>FUNC\�� of TP, and retry."; 

		return 1;
	}
	if(err_code == 77) 
	{
		str_alarm  = "ERR_TooLongCommand";
		str_reason = "��� ���ڿ��� 200byte�� �ʰ���.";
		str_action = "1.��� Cable line���¸� �����Ѵ�.";

		return 1;
	}
	if(err_code == 78)
	{
		str_alarm  = "ERR_TpConnected";
		str_reason = "TP�� ����Ǿ� ����.";
		str_action = "1. TP�� ������ �� Host ����� ������.";
		
		return 1;
	}
	if(err_code == 79) 
	{
		str_alarm  = "ERR_UnknownCommand";
		str_reason = "���ǵ��� ���� ����� ���� �Ǿ���.";
		str_action = "1. �ùٸ� ������ ����� ������.";

		return 1;
	}
	if(err_code == 80)
	{
		str_alarm  = "ERR_HostComTimeOut";
		str_reason = "Host�κ��� ���ڿ��� �޴µ��� 10���̻󵿾� Data�� ���� ����.";
		str_action = "1. ��� cable�� ���¸� �����Ѵ�.";

		return 1;
	}
	if(err_code == 81)
	{
		str_alarm  = "ERR_BL_600ErrorStart";
		str_reason = "BCR setting���κ��� Error�� ����.";
		str_action = "";

		return 1;
	}
	if(err_code == 111)
	{
		str_alarm  = "ERR_LogDataNothing";
		str_reason = "Log Data�� �������� ����";
		str_action = "";

		return 1;
	}
	if(err_code == 112)
	{
		str_alarm  = "ERR_LogBufferToLarge";
		str_reason = "Log Write �� ������ ������";
		str_action = "";

		return 1;
	}
	if(err_code == 150)
	{
		str_alarm  = "ERR_RobotRetract";
		str_reason = "Z���� ������ �� Robot Retract Signal�� Off �Ǿ�����";
		str_action = "Robot Extend ���¿��� LPM�� ���� ����� ���� �Ǿ����� Ȯ�� IO �ñ׳��� �ùٸ��� �������� Ȯ��";

		return 1;
	}
	if(err_code == 152)
	{
		str_alarm  = "ERR_CanNot_T_Open";
		str_reason = "UNLOAD �Ϸ� ���¿��� TOPEN ��� ����";
		str_action = "DURAPORT Status Ȯ��";

		return 1;
	}
	if(err_code == 153)
	{
		str_alarm  = "ERR_SideDoorOpend";
		str_reason = "EFEM,SFEM door�� ��������";

		str_action  = "EFEM,SFEM door Ȯ��,";
		str_action += "\n";
		str_action += "Door Sensor Ȯ��,";
		str_action += "\n";
		str_action += "Door Sensor�� PARALLEL�� �輱 Ȯ��";

		return 1;
	}
	if(err_code == 155)
	{
		str_alarm  = "ERR_Door_Close_Time";
		str_reason = "Unload������ Door Close �ð��� Hom ���� Door Close �ð� ���� ����";

		str_action  = "1.Door�� Close �Ǿ����� Ȯ��";
		str_action += "\n";
		str_action += "2.Door Close Sensor �� Cable ����";

		return 1;
	}
	if(err_code == 156)
	{
		str_alarm  = "ERR_Foup_Door_Open";
		str_reason = "Trans Out�� Obstacle_CHK_SEN ������ Foup_Door_Open �Ǿ� ����";
		str_action = "FOUP Door �̻� ���� Ȯ��,";

		return 1;
	}
	if(err_code == 157)
	{
		str_alarm  = "ERR_MappingArmOpenMapData";
		str_reason = "Mapping Arm Extend �� Mapping Arm Sensor�� ���� �������� ����.";
		str_action = "Mapping Arm ���� �� Sensor Ȯ��";

		return 1;
	}
	if(err_code == 158)
	{
		str_alarm  = "ERR_MLIFT_DN_Exe";
		str_reason = "Door Close���¿��� MLIFT_DN ��� ��";
		str_action = "Door Open �� MLIFT_DN ��� ����";

		return 1;
	}

	return -1;
}

