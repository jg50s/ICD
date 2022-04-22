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
		str_action = "상위(Host) 명령 중에서 축지정을 확인.";

		return 1;
	}
	if(err_code == 3) 
	{
		str_alarm  = "ERR_InvalidData";
		str_reason = "입력 Data가 시스템의 지정된 범위를 초과하였거나, 숫자, 기호 등이 잘못 입력되었을 경우에 발생";
		str_action = "Data 확인 후 재입력";

		return 1;
	}	
	if(err_code == 4) 
	{
		str_alarm = "ERR_EventState";

		str_reason  = "Stop/EmStop Event가 발생.";
		str_reason += "\n";
		str_reason += "E-Stop Switch가 눌려져 있거나 Up/Down Limit Sensor가 Sensing되고 있음.";

		str_action  = "1. E-stop Switch가 눌려져 있는지 확인";
		str_action += "\n";
		str_action += "2. Z-axis Limit sensor가 감지되어 있는지 확인";
		str_action += "\n";
		str_action += "3. Servo Driver가 Alarm 상태인지 확인";

		return 1;
	}
	if(err_code == 5) 
	{
		str_alarm  = "ERR_DriverNotOn";

		str_reason = "Driver(Amp)가 OFF 상태임";

		str_action  = "1. Servo Motor Drive를 ON (AMP ON)";
		str_action += "\n";
		str_action += "2. E-stop Switch가 눌려져 있는지 확인";

		return 1;
	}
	if(err_code == 6) 
	{
		str_alarm  = "ERR_HomeNotDone";
		str_reason = "Homing이 완료되지 않은 상태에서 명령을 수행했을 경우 발생";
		str_action = "All Homing을 실시";

		return 1;
	}
	if(err_code == 7) 
	{
		str_alarm  = "ERR_DriverErrorState";
		str_reason = "Servo Motor Driver에서 Error가 발생됨";
		str_action = "Servo Drive을 Reset 또는 Power를 Shutdown한 후 (재부팅 후) 다시 Reset함";

		return 1;
	}
	if(err_code == 9)
	{
		str_alarm  = "ERR_ErrorNotCleared";
		str_reason = "Error가 Clear되지 않은 상태에서 다른 명령이 내려졌음";
		str_action = "RESET’Command로 Error를 Clear 시킨 후 동작 명령을 내림";

		return 1;
	}
	if(err_code == 10) 
	{
		str_alarm  = "ERR_PODNotOpened";
		str_reason = "Scan(Re-mapping) 명령이 FOUP Close 상태에서 내려졌음";
		str_action = "FOUP Open 상태에서 SCAN 명령을 재시도";

		return 1;
	}
	if(err_code == 11) 
	{
		str_alarm  = "ERR_PODTransIn";
		str_reason = "POD Docking 명령 후 정해진 시간(5초) 내에 POD Trans In Sensor가 Sensing 되지 않았음";

		str_action  = "Trans In Sensor가 Sensing 되지 못한 원인을 파악";
		str_action += "\n";
		str_action += "  1. POD Trans Motor의 이상여부 점검";
		str_action += "\n";
		str_action += "  2. Sensor 이상 여부 점검";
		str_action += "\n";
		str_action += "  3. POD Door와 Port Door 사이에 장애물이 있는지 점검";

		return 1;
	}
	if(err_code == 12) 
	{
		str_alarm  = "ERR_PODTransOut";
		str_reason = "POD Undocking 명령 후 정해진 시간(5초) 내에 POD Trans Out Sensor가 Sensing 되지 않았음";

		str_action  = "Trans Out Sensor가 Sensing 되지 못한 원인을 파악";
		str_action += "\n";
		str_action += "  1. POD Trans Motor의 이상여부 점검";
		str_action += "\n";
		str_action += "  2. Sensor 이상 여부 점검";

		return 1;
	}
	if(err_code == 13)
	{
		str_alarm  = "ERR_LatchOpen";
		str_reason = "Latch Open 위치에서 Latch Open Sensor가 Sensing되지 않았음";

		str_action  = "Latch Open Sensor가 Sensing되지 못한 원인을 파악";
		str_action += "\n";
		str_action += "  1. Latch SOL. 및 실린더의 이상여부 점검";
		str_action += "\n";
		str_action += "  2. Sensor 이상 여부 점검";

		return 1;
	}
	if(err_code == 14)
	{
		str_alarm  = "ERR_LatchClose";
		str_reason = "Latch Close 위치에서 Latch Close Sensor가 Sensing되지 않았음";

		str_action  = "Latch Close Sensor가 Sensing되지 못한 원인을 파악";
		str_action += "\n";
		str_action += "  1. Latch SOL. 및 실린더의 이상여부 점검";
		str_action += "\n";
		str_action += "  2. Sensor 이상 여부 점검";

		return 1;
	}
	if(err_code == 15) 
	{
		str_alarm  = "ERR_MappingArmOpen";
		str_reason = "Mapping Arm Open 동작 후 일정 시간안에( overtime 5초) Mapping Arm Open Sensor가 Sensing되지 않았음";

		str_action  = "Mapping Arm Open 동작 후 Mapping Arm Open Sensor가 Sensing되지 못한 원인 파악";
		str_action += "\n";
		str_action += "  1. Mapping Arm motor의 이상여부 점검";
		str_action += "\n";
		str_action += "  2. Sensor 이상 여부 점검";

		return 1;
	}
	if(err_code == 16) 
	{
		str_alarm  = "ERR_MappingArmClose";
		str_reason = "Mapping Arm Close 동작 후 일정 시간안에( overtime 5초) Mapping Arm Open Sensor가 Sensing되지 않았음";

		str_action  = "Mapping Arm Close 동작 후 Mapping Arm Close Sensor가 Sensing되지 못한 원인 파악";
		str_action += "\n";
		str_action += "  1. Mapping Arm motor의 이상여부 점검";
		str_action += "\n";
		str_action += "  2. Sensor 이상 여부 점검";

		return 1;
	}
	if(err_code == 17) 
	{
		str_alarm = "ERR_VacuumOn";

		str_reason  = "POD Trans In후 Vacuum solenoid가 On하였으나 이때 Vacuum Sensor가 On 되지 않았음.";
		str_reason += "\n";
		str_reason += "Vacuum Cup과 FOUP door사이에 Vacuum압이 형성되지 않았음";

		str_action  = "1.Vacuum이 Spec 대로 공급되고 있는지 점검(- 50kPa)";
		str_action += "\n";
		str_action += "2. FOUP Door가 PDO Door에 밀착되는 상태 점검";
		str_action += "\n";
		str_action += "3. FOUP의 Latch hole이 수직 상태를 점검";
		str_action += "\n";
		str_action += "4. Vacuum Sensor의 이상여부 점검";

		return 1;
	}
	if(err_code == 18) 
	{
		str_alarm  = "ERR_VacuumOff";
		str_reason = "Vacuum solenoid를 Off한 후 Vacuum sensor가 Off되지 않았음";

		str_action  = "1. Vacuum Sensor의 On/Off Threshold 값이 spec 대로 setting 되어 있는지 점검";
		str_action += "\n";
		str_action += "2. Vacuum Sensor의 이상여부 점검";

		return 1;
	}
	if(err_code == 19) 
	{
		str_alarm  = "ERR_PodPlacedImproperly";
		str_reason = "FOUP가 PDO의 Stage위에 올바르게 놓이지 않았음";

		str_action  = "1. FOUP 가 Stage위에 올바르게 놓였는지 확인";
		str_action += "\n";
		str_action += "2. Presence LED 및 Placement LED가 켜졌는지 확인";
		str_action += "\n";
		str_action += "3. FOUP이 올바르게 놓여진 상태에서 Placement sensor가 모두 Sensing되고 있는지 확인";
		str_action += "\n";
		str_action += "4. Placement Sensor의 이상여부 점검";

		return 1;
	}
	if(err_code == 20) 
	{
		str_alarm  = "ERR_PODDoorNotExist";
		str_reason = "POD Door가 감지되지 않았음";

		str_action  = "1. Vacuum이 Spec대로 공급되고 있는지 확인";
		str_action += "\n";
		str_action += "2. Vacuum Sensor의 이상여부 확인";

		return 1;
	}
	if(err_code == 21) 
	{
		str_alarm  = "ERR_PODNotExist";
		str_reason = "FOUP가 없는 상태에서 동작을 시도 하였음";

		str_action  = "1. FOUP가 Stage위에 올바르게 놓여 있는지 확인";
		str_action += "\n";
		str_action += "2. Placement Sensor 및 Presence Sensor의 이상여부 확인";

		return 1;
	}
	if(err_code == 22) 
	{
		str_alarm  = "ERR_WaferProtrude";

		str_reason  = "1. Close 동작 전에 Wafer Protrusion sensor가 Sensing 되었음";
		str_reason += "\n";
		str_reason += "2. Up/Down 동작 중에 Wafer Protrusion sensor가 sensing 되었음(Safety)";

		str_action  = "1. Wafer가 FOUP 밖으로 튀어 나와 있는지 확인.";
		str_action += "\n";
		str_action += "2. 수발광 사이에 이물질이 있는지 확인";
		str_action += "\n";
		str_action += "3. 수발광 사이의 Alignment를 확인";

		return 1;
	}
	if(err_code == 23) 
	{
		str_alarm  = "ERR_InvalidScanStartPosition";
		str_reason = "Mapping을 시작하는 Start Position Data 가 불합리하게 Setting 되었음";

		str_action  = "첫번째 Wafer의 위치가 올바르게 지정되었는지, ";
		str_action += "\n";
		str_action += "Slot 개수 및 한 Slot의 거리 Data가 올바르게 지정되었는지 확인";
	
		return 1;
	}
	if(err_code == 24) 
	{
		str_alarm  = "ERR_ScanTimeOver";
		str_reason = "Up 또는 Down 동작 시간이 10초를 초과함";

		str_action = "Mapping의 속도 및 Up/Down 동작 시간을 일정 시간 내로 Setting 되어 있는지 확인";

		return 1;
	}
	if(err_code == 25) 
	{
		str_alarm  = "ERR_StopScanMotion";
		str_reason = "Mapping이 끝나기 전에 Up/Down 동작이 멈춤";
		str_action = "Mapping의 속도 및 Up/Down 동작 시간을 일정 시간 내로 Setting 되어 있는지 확인";

		return 1;
	}
	if(err_code == 26) 
	{
		str_alarm  = "ERR_WaferThickness";
		str_reason = "두개 이상의 Wafer가 겹침";

		str_action  = "1. Wafer가 올바르게 놓여졌는지 확인";
		str_action += "\n";
		str_action += "2. Wafer의 두께가 올바르게 지정되었는지 확인";
		str_action += "\n";
		str_action += "	(W-T를 상향 조정해야 하는데 이는 Mapping Data의 Wafer 실측 두께에 근거함)";

		return 1;
	}
	if(err_code == 27) 
	{
		str_alarm  = "ERR_WaferPosition";
		str_reason = "Wafer가 두 Slot사이에 걸쳐 있음";

		str_action  = "1. Wafer가 올바르게 놓여졌는지 확인.";
		str_action += "\n";
		str_action += "2. Wafer의 첫번째 위치를 재 Teaching 함";

		return 1;
	}
	if(err_code == 28) 
	{
		str_alarm  = "ERR_InvalidScanInput";
		str_reason = "Wafer Detection Sensor의 값이 비정상적임";

		str_action  = "1. Wafer감지 Sensor에서의 입력 상태를 점검.";
		str_action += "\n";
		str_action += "2. Mapping Sensor의 이상여부 확인";

		return 1;
	}
	if(err_code == 29) 
	{
		str_alarm  = "ERR_InvalidScanData";
		
		str_reason  = "너무 많은 Wafer가 Sensing 됨.";
		str_reason += "\n";
		str_reason += "즉 Wafer Sensing시 Chattering으로 인해 Wafer 감지 On/Off point가 너무 많음.";

		str_action  = "1. Wafer감지 Sensor에서의 입력 상태를 점검.";
		str_action += "\n";
		str_action += "2. Z-axis의 진동으로 Wafer Sensing시 Chattering이 있는지 점검.";

		return 1;
	}
	if(err_code == 30) 
	{
		str_alarm  = "ERR_UnloadIdentifyTimeOver";
		str_reason = "FOUP를 PDO로부터 제거 한 10초 이내에 Unload button이 눌려지지 않았음.";
		str_action = "";

		return 1;
	}
	if(err_code == 31) 
	{
		str_alarm  = "ERR_StopTimeOver";
		str_reason = "Time interval이 정의되고 Motor가 이 이상을 회전함.";
		str_action = "";

		return 1;
	}
	if(err_code == 32) 
	{
		str_alarm  = "ERR_EscapeSensorTimeOver";
		str_reason = "Homing중 정해지 시간 안에 Homing Bracket이 Homing Sensor를 벗어나지 못함.";
		str_action = "1. Homing 속도가 너무 늦지 않은지를 점검.";

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
		str_reason = "Homing중 움직이는 반대 방향의 Limit sensor가 sensing됨.";
		str_action = "1. Homing 동안 아래의 +Limit sensor가 Sensing 되어 있는지 점검.";

		return 1;
	}
	if(err_code == 35) 
	{
		str_alarm  = "ERR_LimitSensorIncorrect";
		str_reason = "Homing 동안 두개의 Limit sensor가 모두 sensing됨.";
		str_action = "1. Homing 동안 두개의 Limit Sensor가 모두 Sensing되어 있는지 점검.";

		return 1;
	}
	if(err_code == 36) 
	{
		str_alarm  = "ERR_AxisPositionIncorrect";
		str_reason = "동작중 위치 Data가 200Pulse이상의 오차가 남.";
		str_action = "1. 제조사 문의";

		return 1;
	}
	if(err_code == 37)
	{
		str_alarm  = "ERR_HomeConditionNotCorrect";

		str_reason  = "Homing조건이 아님.";
		str_reason += "\n";
		str_reason += "  1. POD가 있을 경우 ";
		str_reason += "\n";
		str_reason += "    1.1 Vacuum이 On이고 Latch가 Unlock.";
		str_reason += "\n";
		str_reason += "    1.2 Vacuum이 Off고 Latch가 Lock.";
		str_reason += "\n";
		str_reason += "  2. POD가 없을 경우 Vacuum이 On이고 Latch가 Lock.";

		str_action = "1. PDO의 door 및 Stage로부터 모든 물체를 제거하고 정상적인 상태에서 Homing을 함.";

		return 1;
	}
	if(err_code == 38) 
	{
		str_action  = "ERR_LimitSensorNotIn";
		str_reason  = "Latch가 Open/Close후 Limit Sensor가 감지 되지 않았다.";
		
		str_action  = "1. Latch가 Open/Close동작 후 Limit sensor가 감지 되지 않은 원인을 파악";
		str_action += "\n";
		str_action += "2. All HOM을 실시";

		return 1;
	}
	if(err_code == 39) 
	{
		str_alarm  = "ERR_OutOfSwLimit";
		str_reason = "1. 위치 지정값이 Sw Limit 값 이상임.";

		str_action  = "1. Software Limit 값 적정한 위치로 조정한다.";
		str_action += "\n";
		str_action += "2. 위치 지정값 점검.";

		return 1;
	}
	if(err_code == 40) 
	{
		str_alarm  = "ERR_PinchPoint";
		str_reason = "Pinch point sensor가 감지됨.";

		str_action  = "1. Pinch sensor의 수발광 Sensor 사이에 이물질이 있는지 점검.";
		str_action += "2. 수발광 sensor사이의 alignment를 다시 조정.";

		return 1;
	}
	if(err_code == 47) 
	{
		str_alarm  = "ERR_DropValidSignal";
		str_reason = "Response is generated to exceed defined time interval.";
		str_action = "제조사 문의";

		return 1;
	}
	if(err_code == 48) 
	{
		str_alarm  = "ERR_UnexpectedPodAppear";
		str_reason = "Response is generated to exceed defined time interval.";
		str_action = "제조사 문의";

		return 1;
	}
	if(err_code == 49) 
	{
		str_alarm  = "ERR_UnexpectedPodDisappear";
		str_reason = "Response is generated to exceed defined time interval.";
		str_action = "제조사 문의";

		return 1;
	}
	if(err_code == 51) 
	{
		str_alarm  = "ERR_FlashErase";
		str_reason = "Backup Data is not erased normally.";
		str_action = "제조사 문의";
	
		return 1;
	}
	if(err_code == 52) 
	{
		str_alarm  = "ERR_FlashWrite";
		str_reason = "Backup Data is not correctly written.";
		str_action = "제조사 문의";

		return 1;
	}
	if(err_code == 53) 
	{
		str_alarm  = "ERR_FlashVerify";
		str_reason = "Backup Data is not correctly written.";
		str_action = "제조사 문의";

		return 1;
	}
	if(err_code == 54) 
	{
		str_alarm  = "ERR_CrashData";
		str_reason = "Backup Data가 정상적으로 입력되지 않음.";
		str_action = "1. Data를 모두 넣고 Save한다.";

		return 1;
	}
	if(err_code == 55) 
	{
		str_alarm  = "ERR_SwLimitOver";
		str_reason = "Motor가 운행 중 SW Limit 을 지나침.";
		str_action = "1. 가고자 하는 지정위치와 S/W 값을 비교해 본다.";

		return 1;
	}
	if(err_code == 56)
	{
		str_alarm  = "ERR_HwLimitOver";
		str_reason = "Motor가 운행 중 H/W Limit sensor가 감지됨.";

		str_action  = "1. Homing 후 다시 다시 동작시켜 본다.";
		str_action += "\n";
		str_action += "2. H/W Limit과 가고자 하는 지정위치를 비교해 본다.";

		return 1;
	}
	if(err_code == 57) 
	{
		str_alarm  = "ERR_TrackingError";
		str_reason = "운행 중 목표 위치와 현재 위치간에 오차가 있음.";
		str_action = "1. Servo drive의 gain을 조정한다.";

		return 1;
	}
	if(err_code == 58)
	{
		str_alarm  = "ERR_EmStopPressed";
		str_reason = "운행 중 E-Stop button이 눌려짐.";
		str_action = "1. E-Stop 상황을 해제한 후 재동작 시킨다.";

		return 1;
	}
	if(err_code == 59) 
	{
		str_alarm  = "ERR_DriverError";
		str_reason = "Servo Drive Error가 감지됨.";
		str_action = "1. Power를 OFF/ON 한 후에 Amp On 과 Homing을 수행한 후 다시 동작 시킨다.";

		return 1;
	}
	if(err_code == 60) 
	{
		str_alarm  = "ERR_IncorrectDockingPosition";
		str_reason = "Docking시 Stage가 뒤로 밀림";
		str_action = "1.Reset을 하거나 Homeing을 한다.";

		return 1;
	}
	if(err_code == 61) 
	{
		str_alarm  = "ERR_TpComTimeOut";
		str_reason = "TP로부터 일정주기 동안 입력이 없음.";

		str_action  = "1. TP Cable을 점검한다.";
		str_action += "\n";
		str_action += "2. Consult with the provider.";
	
		return 1;
	}
	if(err_code == 62) 
	{
		str_alarm  = "ERR_TpNotConnect";
		str_reason = "TP가 연결되지 않았음.";

		str_action  = "1. TP Cable을 점검한다.";
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
		str_reason = "POD Lock 동작 후 POD Lock sensor가 감지되지 않았음.";
		str_action = "1. FOUP Lock Position에서 Lock sensor가 sensing 안된 원인을 파악.";

		return 1;
	}
	if(err_code == 65)
	{
		str_alarm  = "ERR_PodUnlock";
		str_reason = "POD Unlock 동작 후 POD Unlock sensor가 감지되지 않았음.";
		str_action = "1. FOUP Unlock position에서 Unlock sensor가 sensing안된 원인을 파악.";

		return 1;
	}
	if(err_code == 66)
	{
		str_alarm  = "ERR_PortDoorOpen";
		str_reason = "Port door open 동작 후 Port door open sensor가 감지되지 않았음.";
		str_action = "1. PDO Door가 Open 상태에서 Port door open sensor가 sensing되지 않은 원인을 파악.";

		return 1;
	}
	if(err_code == 67) 
	{
		str_alarm  = "ERR_PortDoorClose";
		str_reason = "Port door close 동작 후 Port door close sensor가 감지되지 않았음.";
		str_action = "1. PDO Door가 Close 상태에서 Port door close sensor가 sensing되지 않은 원인을 파악.";

		return 1;
	}
	if(err_code == 68)
	{
		str_alarm  = "ERR_MaintMode";
		str_reason = "Maint_Mode 가 Enable임.";
		str_action = "1. Maint_Mode를 Disable 시킨다.";

		return 1;
	}
	if(err_code == 69)
	{
		str_alarm  = "ERR_NotMaintMode";
		str_reason = "Maint_Mode 가 Enable이 아님.";
		str_action = "1. Maint_Mode를 Enable 시킨다.";

		return 1;
	}
	if(err_code == 70)
	{
		str_alarm  = "ERR_InvalidArgument";
		str_reason = "정의되지 않은 명령어의 Parameter가 수신되었음.";
		str_action = "1. 명령을 올바른 형식에 맞추어 내린다.";

		return 1;
	}
	if(err_code == 71)
	{
		str_alarm  = "ERR_BarcodeComTimeOut";
		str_reason = "BCR로부터 Data가 수신되지 않음.";

		str_action  = "1. BCR Cable을 확인한다.";
		str_action += "\n";
		str_action += "2. BCR이 정상 동작하는지를 확인한다.";
		str_action += "\n";
		str_action += "3. COM3 Port에 이상이 있는지를 점검한다.";

		return 1;
	}
	if(err_code == 72)
	{
		str_alarm  = "ERR_BarcodeUnknownResponse";
		str_reason = "The setting OK of BCR and data other than ERR are received.";

		str_action  = "1. BCR Cable을 확인한다.";
		str_action += "\n";
		str_action += "2. BCR이 정상 동작하는지를 확인한다.";
		str_action += "\n";
		str_action += "3. COM3 Port에 이상이 있는지를 점검한다.";

		return 1;
	}
	if(err_code == 73)
	{
		str_alarm  = "ERR_BL_600NotDefinedError";
		str_reason = "BCR로부터 받은 Error code가 0-18임.";
		str_action = "";

		return 1;
	}
	if(err_code == 74)
	{
		str_alarm  = "ERR_BL_600MalFunction";
		str_reason = "BCR이 정상적으로 동작하지 않음.";
		str_action = "";

		return 1;
	}
	if(err_code == 75)
	{
		str_alarm  = "ERR_BarcodeDataReadError";
		str_reason = "BCR로부터 응답이 3초 동안 없음.";
	
		str_action  = "1. BCR이 정상 동작하는지를 확인한다.";
		str_action += "\n";
		str_action += "2. BCR type이 올바르게 지정되어 있는지 확인한다.";

		return 1;
	}
	if(err_code == 76)
	{
		str_alarm  = "ERR_BarcodeNotExist";
		str_reason = "BCR이 disable되어 있음.";

		str_action  = "BCR을 Enable 시킨다.";
		str_action += "\n";
		str_action += "\"MAIN=>SET=>FUNC\” of TP, and retry."; 

		return 1;
	}
	if(err_code == 77) 
	{
		str_alarm  = "ERR_TooLongCommand";
		str_reason = "명령 문자열이 200byte를 초과함.";
		str_action = "1.통신 Cable line상태를 점검한다.";

		return 1;
	}
	if(err_code == 78)
	{
		str_alarm  = "ERR_TpConnected";
		str_reason = "TP가 연결되어 있음.";
		str_action = "1. TP를 제거한 후 Host 명령을 내린다.";
		
		return 1;
	}
	if(err_code == 79) 
	{
		str_alarm  = "ERR_UnknownCommand";
		str_reason = "정의되지 않은 명령이 수신 되었음.";
		str_action = "1. 올바른 형식의 명령을 내린다.";

		return 1;
	}
	if(err_code == 80)
	{
		str_alarm  = "ERR_HostComTimeOut";
		str_reason = "Host로부터 문자열을 받는동안 10초이상동안 Data를 받지 못함.";
		str_action = "1. 통신 cable의 상태를 점검한다.";

		return 1;
	}
	if(err_code == 81)
	{
		str_alarm  = "ERR_BL_600ErrorStart";
		str_reason = "BCR setting으로부터 Error가 있음.";
		str_action = "";

		return 1;
	}
	if(err_code == 111)
	{
		str_alarm  = "ERR_LogDataNothing";
		str_reason = "Log Data가 존재하지 않음";
		str_action = "";

		return 1;
	}
	if(err_code == 112)
	{
		str_alarm  = "ERR_LogBufferToLarge";
		str_reason = "Log Write 할 공간이 부족함";
		str_action = "";

		return 1;
	}
	if(err_code == 150)
	{
		str_alarm  = "ERR_RobotRetract";
		str_reason = "Z축을 움직일 때 Robot Retract Signal이 Off 되어있음";
		str_action = "Robot Extend 상태에서 LPM의 동작 명령이 실행 되었는지 확인 IO 시그널이 올바르게 들어오는지 확인";

		return 1;
	}
	if(err_code == 152)
	{
		str_alarm  = "ERR_CanNot_T_Open";
		str_reason = "UNLOAD 완료 상태에서 TOPEN 명령 수신";
		str_action = "DURAPORT Status 확인";

		return 1;
	}
	if(err_code == 153)
	{
		str_alarm  = "ERR_SideDoorOpend";
		str_reason = "EFEM,SFEM door가 열려있음";

		str_action  = "EFEM,SFEM door 확인,";
		str_action += "\n";
		str_action += "Door Sensor 확인,";
		str_action += "\n";
		str_action += "Door Sensor와 PARALLEL간 배선 확인";

		return 1;
	}
	if(err_code == 155)
	{
		str_alarm  = "ERR_Door_Close_Time";
		str_reason = "Unload동작의 Door Close 시간이 Hom 동작 Door Close 시간 보다 작음";

		str_action  = "1.Door가 Close 되었는지 확인";
		str_action += "\n";
		str_action += "2.Door Close Sensor 및 Cable 점검";

		return 1;
	}
	if(err_code == 156)
	{
		str_alarm  = "ERR_Foup_Door_Open";
		str_reason = "Trans Out중 Obstacle_CHK_SEN 감지시 Foup_Door_Open 되어 있음";
		str_action = "FOUP Door 이상 유무 확인,";

		return 1;
	}
	if(err_code == 157)
	{
		str_alarm  = "ERR_MappingArmOpenMapData";
		str_reason = "Mapping Arm Extend 후 Mapping Arm Sensor로 빛이 감지되지 않음.";
		str_action = "Mapping Arm 상태 및 Sensor 확인";

		return 1;
	}
	if(err_code == 158)
	{
		str_alarm  = "ERR_MLIFT_DN_Exe";
		str_reason = "Door Close상태에서 MLIFT_DN 명령 함";
		str_action = "Door Open 후 MLIFT_DN 명령 실행";

		return 1;
	}

	return -1;
}

