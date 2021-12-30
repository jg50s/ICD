#include "StdAfx.h"
#include "CObj__VAT650_TYPE.h"



//-------------------------------------------------------------------------	
int  CObj__VAT650_TYPE::
Fnc__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm,const int comm_flag)
{
	CString szLog;
	CString str_data;
	int nCmd_Ret = -1;

	// 1. Online Check ...
	if(Is__ONLINE(p_variable, p_alarm) < 0)
	{
		return -11;
	}

	// 2. [REMOTE] Command Set ...
	{
		nCmd_Ret = xCH_doOPER_MODE->Set__DATA("REMOTE");

		if(nCmd_Ret <= 0)
		{
			// ...
			{
				szLog.Format("CH_NAME : [%s], CMD [REMOTE] Failed(ret:%d)... !!\n", 
					xCH_doOPER_MODE->Get__VARIABLE_NAME(), 
					nCmd_Ret);

				Fnc__APP_LOG(szLog);
			}
			return -12;
		}
	}

	if(iACTIVE_SIM > 0)
	{
		xCH_diOPER_MODE->Set__DATA("REMOTE");	
		Sleep(1000);
	}

	// [REMOTE] Command Check ... 
	{
		nCmd_Ret = xCH_diOPER_MODE->When__DATA("REMOTE", 5.0);

		if(nCmd_Ret == 0)
		{
			Fnc__APP_LOG("Upper Object Aborted...");
			return -13;
		}
		else if(nCmd_Ret < 0)	
		{
			int alarm_id = ALID__APC_REMOTE_CMD_TIMEOUT;
			p_alarm->Post__ALARM(alarm_id);

			return -14;
		}
		else if(nCmd_Ret > 0)
		{
			szLog.Format("CH_NAME : [%s], Cmd[%s] Success", xCH_doOPER_MODE->Get__VARIABLE_NAME(), "REMOTE");
			Fnc__APP_LOG(szLog);
		}
	}

	// 3. [RESET - WARNING, ERROR] Command Set ...
	{
		nCmd_Ret = xCH_doRESET_CMD->Set__DATA("ERRFLAG_RESET");

		if(nCmd_Ret <= 0)
		{
			szLog.Format("CH_NAME : [%s], CMD [RESET - ERROR Flag Reset] Failed(ret:%d)... !!\n", 
						 xCH_doRESET_CMD->Get__VARIABLE_NAME(), nCmd_Ret);
			Fnc__APP_LOG(szLog);
			return -15;
		}
	}

	if(iACTIVE_SIM > 0)
	{
		xCH_diPOSITION_ERROR->Set__DATA("OK");	
		Sleep(1000);
	}

	// 4. [RESET - ERROR] Command Check ... 
	{
		nCmd_Ret = xCH_diPOSITION_ERROR->When__DATA("OK", 5.0);

		if(nCmd_Ret == 0)
		{
			Fnc__APP_LOG("Upper Object Aborted...");		
			return -16;
		}
		else if(nCmd_Ret <  0)	
		{
			int alarm_id = ALID__APC_ALARM_EXIST;
			p_alarm->Post__ALARM(alarm_id);

			return -17;
		}
		else if(nCmd_Ret > 0)
		{
			szLog.Format("CH_NAME : [%s], Cmd[%s] Success", 
						 xCH_doOPER_MODE->Get__VARIABLE_NAME(), 
						 "RESET - WARNING, ERROR");
			Fnc__APP_LOG(szLog);
		}
	}

	if(dCH__CFG_POS_COUNT_TYPE->Check__DATA(STR__1M_TYPE) > 0)
	{
		if(iACTIVE_SIM > 0)
		{
			xCH_diCOMM_ERROR__1M_TYPE->Set__DATA("NOERR");	
			Sleep(1000);
		}

		// 5. [DISCONNECT] Status Check ... 
		{
			nCmd_Ret = xCH_diCOMM_ERROR__1M_TYPE->When__DATA("NOERR", 5.0);

			if(nCmd_Ret == 0)
			{
				Fnc__APP_LOG("Upper Object Aborted...");		
				return -18;
			}
			else if(nCmd_Ret <  0)	
			{
				int alarm_id = ALID__APC_COMM_ERROR_EXIST;
				p_alarm->Post__ALARM(alarm_id);

				return -19;
			}
			else if(nCmd_Ret > 0)
			{	
				szLog.Format("CH_NAME : [%s], Cmd[%s] Success", 
							 xCH_doOPER_MODE->Get__VARIABLE_NAME(), 
							 "RESET - COMM ERROR");

				Fnc__APP_LOG(szLog);
			}
		}
	}
	else
	{
		if(iACTIVE_SIM > 0)
		{
			xCH_diCOMM_ERROR__1K_TYPE->Set__DATA("NOERR");	
			Sleep(1000);
		}

		// 5. [DISCONNECT] Status Check ... 
		{
			nCmd_Ret = xCH_diCOMM_ERROR__1K_TYPE->When__DATA("NOERR", 5.0);

			if(nCmd_Ret == 0)
			{
				Fnc__APP_LOG("Upper Object Aborted...");		
				return -18;
			}
			else if(nCmd_Ret <  0)	
			{
				int alarm_id = ALID__APC_COMM_ERROR_EXIST;
				p_alarm->Post__ALARM(alarm_id);

				return -19;
			}
			else if(nCmd_Ret > 0)
			{	
				szLog.Format("CH_NAME : [%s], Cmd[%s] Success", 
							 xCH_doOPER_MODE->Get__VARIABLE_NAME(), 
							 "RESET - COMM ERROR");

				Fnc__APP_LOG(szLog);
			}
		}
	}

	if(comm_flag < 0)
	{
		// APC Init Valve Mode Select Config Add ...
		//     1) OPEN 2) CLOSE 3) HOLD (Skip)

		if((dCH__CFG_VALVE_INIT_STATUS->Check__DATA("OPEN")  > 0)
		|| (dCH__CFG_VALVE_INIT_STATUS->Check__DATA("CLOSE") > 0))
		{
			// 6. [OPEN/CLOSE] Command Set ...
			dCH__CFG_VALVE_INIT_STATUS->Get__DATA(str_data);
			nCmd_Ret = xCH__doVALVE_OPR_CMD->Set__DATA(str_data);

			if(nCmd_Ret == DRV__CMD_FAIL)
			{
				szLog.Format("CH_NAME : [%s], CMD [%s] Failed(ret:%d)... !!\n", 
							 xCH__doVALVE_OPR_CMD->Get__VARIABLE_NAME(), 
							 str_data, 
							 nCmd_Ret);

				Fnc__APP_LOG(szLog);
				return -20;
			}
			else if(nCmd_Ret <= 0)
			{
				szLog.Format("Interlock Occur... CH_NAME : [%s], CMD [%s] Failed(ret:%d)... !!\n", 
							 xCH__doVALVE_OPR_CMD->Get__VARIABLE_NAME(), 
							 str_data, 
							 nCmd_Ret);

				Fnc__APP_LOG(szLog);
				return -21;
			}

			if(iACTIVE_SIM > 0)
			{
				if(dCH__CFG_VALVE_INIT_STATUS->Check__DATA("CLOSE") > 0)
				{
					xCH__aiVALVE_POS->Set__VALUE(0.0);
				}
				else
				{
					xCH__aiVALVE_POS->Set__VALUE(1000.0);
				}
			}

			// 7. [OPEN/CLOSE] Command Check ...
			if(dCH__CFG_VALVE_INIT_STATUS->Check__DATA("OPEN") > 0)
			{
				nCmd_Ret = p_variable->When__MORE_THAN(xCH__aiVALVE_POS->Get__VARIABLE_NAME(), 999.0, VALVE_OPEN_TIMEOUT);
			}
			else
			{
				nCmd_Ret = p_variable->When__LESS_THAN(xCH__aiVALVE_POS->Get__VARIABLE_NAME(), 0.9, VALVE_CLOSE_TIMEOUT);
			}

			if(nCmd_Ret == 0)
			{
				Fnc__APP_LOG("Upper Object Aborted...");
				return -22;
			}
			else if(nCmd_Ret < 0)	
			{
				int alarm_id = ALID__APC_CONTROL_CMD_TIMEOUT;

				p_alarm->Post__ALARM(alarm_id);
				return -23;
			}
			else if(nCmd_Ret > 0)
			{
				szLog.Format("CH_NAME : [%s], Cmd[%s] Success", 
							 xCH__doVALVE_OPR_CMD->Get__VARIABLE_NAME(), 
							 str_data);

				Fnc__APP_LOG(szLog);
			}
		}
	}

	if(nCmd_Ret > 0)
	{
		dCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	}
	return nCmd_Ret;
}

int  CObj__VAT650_TYPE::
Fnc__OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString szLog;
	int nCmd_Ret = -1;

	Fnc__APP_LOG("Fnc__OPEN() ----> START !!\n");

	// ...
	{
		if(Is__REMOTE(p_variable, p_alarm)  < 0)		return OBJ_ABORT;
		if(Is__ONLINE(p_variable, p_alarm)  < 0)		return OBJ_ABORT;
	}

	//  1. APC Current Position Check ... 
	{
		nCmd_Ret = p_variable->When__MORE_THAN(xCH__aiVALVE_POS->Get__VARIABLE_NAME(), 999.0, 1.0);

		if(nCmd_Ret > 0)
		{
			szLog.Format("CH_NAME : [%s], Alaready [OPEN] Status...", xCH_diCTRL_STS->Get__VARIABLE_NAME());
			Fnc__APP_LOG(szLog);
			return OBJ_AVAILABLE;
		}
		else if(nCmd_Ret == 0)
		{
			Fnc__APP_LOG("Upper Object Aborted...");
			return OBJ_ABORT;
		}
	}

	// 2. [OPEN] Command Set ...
	{
		nCmd_Ret = xCH__doVALVE_OPR_CMD->Set__DATA("OPEN");

		if(nCmd_Ret <= 0)
		{
			szLog.Format("CH_NAME : [%s], CMD [OPEN - ERROR OPEN Opr] Failed(ret:%d)... !!\n", 
						 xCH__doVALVE_OPR_CMD->Get__VARIABLE_NAME(), nCmd_Ret);
			Fnc__APP_LOG(szLog);
			return OBJ_ABORT;
		}
	}

	if(iACTIVE_SIM > 0)
	{
		Sleep(1000);

		xCH__aiVALVE_PRESS->Set__DATA("0.0");
		xCH__aiVALVE_POS->Set__VALUE(MAX_GUI_RANGE_POSITION);
	}

	// 3. [OPEN] Command Check ...
	{
		nCmd_Ret = p_variable->When__MORE_THAN(xCH__aiVALVE_POS->Get__VARIABLE_NAME(), 999.0, VALVE_OPEN_TIMEOUT);

		if(nCmd_Ret == 0)
		{
			Fnc__APP_LOG("Upper Object Aborted...");
			return OBJ_ABORT;
		}
		else if(nCmd_Ret <  0)	
		{
			int alarm_id = ALID__APC_CONTROL_CMD_TIMEOUT;

			p_alarm->Post__ALARM(alarm_id);
			return OBJ_ABORT;
		}

		if(nCmd_Ret > 0)
		{
			szLog.Format("CH_NAME : [%s], Cmd[%s] Success", 
						 xCH__doVALVE_OPR_CMD->Get__VARIABLE_NAME(), 
						 "OPEN");

			Fnc__APP_LOG(szLog);
		}
	}

	Fnc__APP_LOG("Fnc__OPEN() <---- COMPLETE !!\n");	

	return OBJ_AVAILABLE;
}

int  CObj__VAT650_TYPE::
Fnc__CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString szLog;
	int nCmd_Ret = -1;

	Fnc__APP_LOG("Fnc__CLOSE() ----> START !! \n");

	// ...
	{
		if(Is__REMOTE(p_variable, p_alarm)  < 0)		return OBJ_ABORT;
		if(Is__ONLINE(p_variable, p_alarm)  < 0)		return OBJ_ABORT;
	}

	//  1. APC Current Position Check ... 
	{
		nCmd_Ret = p_variable->When__LESS_THAN(xCH__aiVALVE_POS->Get__VARIABLE_NAME(), 0.9, 1.0);

		if(nCmd_Ret > 0)
		{
			szLog.Format("CH_NAME : [%s], Alaready [CLOSE] Status...", 
						 xCH_diCTRL_STS->Get__VARIABLE_NAME());

			Fnc__APP_LOG(szLog);
			return OBJ_AVAILABLE;
		}
		else if(nCmd_Ret == 0)
		{
			Fnc__APP_LOG("Upper Object Aborted...");
			return OBJ_ABORT;
		}
	}

	// 2. [CLOSE] Command Set ...
	{
		nCmd_Ret = xCH__doVALVE_OPR_CMD->Set__DATA("CLOSE");

		if(nCmd_Ret <= 0)
		{
			szLog.Format("CH_NAME : [%s], CMD [CLOSE - ERROR CLOSE Opr] Failed(ret:%d)... !! \n", 
						 xCH__doVALVE_OPR_CMD->Get__VARIABLE_NAME(), 
						 nCmd_Ret);

			Fnc__APP_LOG(szLog);
			return OBJ_ABORT;
		}
	}

	if(iACTIVE_SIM > 0)
	{
		Sleep(1000);

		xCH__aiVALVE_PRESS->Set__DATA("0.0");
		xCH__aiVALVE_POS->Set__DATA("0.0");
	}

	// 3. [CLOSE] Command Check ...
	{
		nCmd_Ret = p_variable->When__LESS_THAN(xCH__aiVALVE_POS->Get__VARIABLE_NAME(), 0.9, VALVE_CLOSE_TIMEOUT);

		if(nCmd_Ret == 0)
		{
			Fnc__APP_LOG("Upper Object Aborted...");
			return OBJ_ABORT;
		}
		else if(nCmd_Ret <  0)	
		{
			int alarm_id = ALID__APC_CONTROL_CMD_TIMEOUT;

			p_alarm->Post__ALARM(alarm_id);
			return OBJ_ABORT;
		}

		if(nCmd_Ret > 0)
		{
			szLog.Format("CH_NAME : [%s], Cmd[%s] Success", xCH__doVALVE_OPR_CMD->Get__VARIABLE_NAME(), "CLOSE");
			Fnc__APP_LOG(szLog);
		}
	}

	Fnc__APP_LOG("Fnc__CLOSE() <---- COMPLETE !!\n");

	return OBJ_AVAILABLE;
}

int  CObj__VAT650_TYPE::
Fnc__PRESSURE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString szLog;
	int nCmd_Ret = -1;
	int nGet_Set_Val = 0;
	int nDrv_Set_Val = 0;

	CString szGet_Set_Val;
	CString szDrv_Set_Val;

	Fnc__APP_LOG("Fnc__PRESSURE() ----> START !!\n");

	// ...
	{
		if(Is__REMOTE(p_variable, p_alarm)  < 0)		return OBJ_ABORT;
		if(Is__ONLINE(p_variable, p_alarm)  < 0)		return OBJ_ABORT;
	}

	//  1. Set Pressure Reading ... 
	aCH__PRESSURE_SET->Get__DATA(szGet_Set_Val);
	nGet_Set_Val = atoi(szGet_Set_Val);

	// Sensor Range Convert...
	nDrv_Set_Val = (nGet_Set_Val*MAX_CFG_RANGE_PRESSURE)/MAX_GUI_RANGE_PRESSURE;
	szDrv_Set_Val.Format("%d", nDrv_Set_Val);

	szLog.Format("CH_NAME : [%s], Get_GUI_Val : [%s], Converted : [%s]", aCH__PRESSURE_SET->Get__VARIABLE_NAME(),szGet_Set_Val, szDrv_Set_Val);
	Fnc__APP_LOG(szLog);

	//  2. Set Pressure Writing ... 
	xCH__aoSET_PRESSURE->Set__DATA(szDrv_Set_Val);

	if(iACTIVE_SIM > 0)
	{
		xCH_diCTRL_STS->Set__DATA("PRESSURE");
		Sleep(1000);
		xCH__aiVALVE_PRESS->Set__DATA(szGet_Set_Val);
	}

	//  3. [PRESSURE] Control Mode Check 
	nCmd_Ret = p_variable->When__VARIABLE_DATA(xCH_diCTRL_STS->Get__VARIABLE_NAME(), "PRESSURE", VALVE_PRESS_STS_TIMEOUT);
	if(nCmd_Ret == 0)	
	{
		Fnc__APP_LOG("Upper Object Aborted...");
		return OBJ_ABORT;
	}
	else if(nCmd_Ret <  0)	
	{
		int alarm_id = ALID__APC_CONTROL_CMD_TIMEOUT;
		p_alarm->Post__ALARM(alarm_id);
		return OBJ_ABORT;
	}
	else if(nCmd_Ret > 0)
	{
		szLog.Format("CH_NAME : [%s], Cmd[%s] Success", xCH__aoSET_PRESSURE->Get__VARIABLE_NAME(), "PRESSURE CONTROL");
		Fnc__APP_LOG(szLog);
	}

	Fnc__APP_LOG("Fnc__PRESSURE() <---- COMPLETE !!\n");

	return OBJ_AVAILABLE;
}

int  CObj__VAT650_TYPE::
Fnc__POSITION(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int fnc_flag = -1;

	CString str_trg_pos;
	CString log_msg;

	// ...
	{
		log_msg = "Fnc__POSITION() ----> START !! \n";

		Fnc__APP_LOG(log_msg);
	}

	// ...
	{
		if(Is__REMOTE(p_variable, p_alarm)  < 0)		return OBJ_ABORT;
		if(Is__ONLINE(p_variable, p_alarm)  < 0)		return OBJ_ABORT;
	}

	// ... 
	{
		aCH__POSITION_SET->Get__DATA(str_trg_pos);
		xCH__aoSET_POSITION->Set__DATA(str_trg_pos);

		// ...
		{
			log_msg.Format("CH_NAME [%s] <- [%s]", 
						   aCH__POSITION_SET->Get__VARIABLE_NAME(),
						   str_trg_pos);

			Fnc__APP_LOG(log_msg);
		}

		if(iACTIVE_SIM > 0)
		{
			xCH_diCTRL_STS->Set__DATA("POSITION");
			xCH__aiVALVE_POS->Set__DATA(str_trg_pos);

			Sleep(1000);
		}
	}

	// [POSITION] Control Mode Check ...
	{
		fnc_flag = p_variable->When__VARIABLE_DATA(xCH_diCTRL_STS->Get__VARIABLE_NAME(), 
												   "POSITION", 
												   VALVE_POSITION_STS_TIMEOUT);

		if(fnc_flag == 0)	
		{
			log_msg = "Upper Object Aborted...";

			Fnc__APP_LOG(log_msg);
			return OBJ_ABORT;
		}
		else if(fnc_flag < 0)	
		{
			int alarm_id = ALID__APC_CONTROL_CMD_TIMEOUT;

			p_alarm->Post__ALARM(alarm_id);
			return OBJ_ABORT;
		}
		else if(fnc_flag > 0)
		{
			log_msg.Format("CH_NAME [%s] : Cmd[%s] Success", 
						   aCH__POSITION_SET->Get__VARIABLE_NAME(), 
						   "POSITION CONTROL");

			Fnc__APP_LOG(log_msg);
		}
	}

	// ...
	{
		log_msg = "Fnc__POSITION() <---- COMPLETE !! \n";

		Fnc__APP_LOG(log_msg);
	}
	return OBJ_AVAILABLE;
}

int  CObj__VAT650_TYPE::
Fnc__POSITION_WAIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm,const int wait_flag)
{
	CString log_msg;
	CString var_data;

	CString data__set_pos;

	// Set Position Reading ... 
	{
		aCH__POSITION_SET->Get__DATA(data__set_pos);
		xCH__aoSET_POSITION->Set__DATA(data__set_pos);

		// ...
		{
			log_msg.Format("Data - Set Position : [%s]", data__set_pos); 
			Fnc__APP_LOG(log_msg);
		}

		if(iACTIVE_SIM > 0)
		{
			xCH__aiVALVE_POS->Set__DATA(data__set_pos);
			xCH_diCTRL_STS->Set__DATA("POSITION");

			Sleep(100);
		}
	}

	// [POSITION] Control Mode Check ...
	if(wait_flag > 0)
	{
		int flag = p_variable->When__VARIABLE_DATA(xCH_diCTRL_STS->Get__VARIABLE_NAME(), 
												   "POSITION", 
												   VALVE_POSITION_STS_TIMEOUT);

		if(flag == 0)	
		{
			log_msg = "Upper Object Aborted ... (1)";

			Fnc__APP_LOG(log_msg);
			return -3;
		}
		else if(flag <  0)	
		{
			int alarm_id = ALID__APC_CONTROL_CMD_TIMEOUT;

			p_alarm->Post__ALARM(alarm_id);
			return -4;
		}

		// ...
		{
			log_msg = "[POSITION] - Control Mode Check ..."; 
			Fnc__APP_LOG(log_msg);
		}
	}

	// ...
	{
		SCX__ASYNC_TIMER_CTRL x_async_timer;
		x_async_timer->START__COUNT_UP(9999);

		double trg_pos = atof(data__set_pos);
		double min_pos = trg_pos - 1.0;
		double max_pos = trg_pos + 1.0;
		double cur_pos = 0.0;

		while(1)
		{
			xCH__aiVALVE_POS->Get__DATA(var_data);
			cur_pos = atof(var_data);

			if(trg_pos <= 1)
			{
				if(cur_pos <= 1)
				{
					break;
				}
			}
			else if(trg_pos >= 999)
			{
				if(cur_pos >= 999)
				{
					break;
				}
			}
			else
			{
				if((cur_pos >= min_pos)
				&& (cur_pos <= max_pos))	
				{
					int i__cur_pos = (int) cur_pos;
					int i__trg_pos = (int) trg_pos;

					if(i__cur_pos != i__trg_pos)
					{
						double diff_pos = cur_pos - trg_pos;

						if((diff_pos > 0.1) || (diff_pos < -0.1))
						{
							SCX__TIMER_CTRL x_timer;
							x_timer->WAIT(0.1);
						}
					}
					break;
				}
			}

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				log_msg = "Upper Object Aborted ... (2)";

				Fnc__APP_LOG(log_msg);
				return -11;
			}
			if(x_async_timer->Get__CURRENT_TIME() > 30.0)
			{
				// ...
				{
					int alarm_id = ALID__APC_POSITION_CTRL_TIMEOUT;
					CString alm_msg;
					CString alm_bff;
					CString r_act;

					alm_msg.Format("Current Position <- (%.3f) \n", cur_pos);
					alm_bff.Format("  Target Min Pos <- (%.3f) \n", min_pos);
					alm_msg += alm_bff;
					alm_bff.Format("  Target Max Pos <- (%.3f) \n", max_pos);
					alm_msg += alm_bff;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
				}
				return -12;
			}

			Sleep(1);
		}
	}

	return 1;
}

int  CObj__VAT650_TYPE::
Fnc__HOLD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString szLog;
	int nCmd_Ret = -1;

	Fnc__APP_LOG("Fnc__HOLD() ----> START !!\n");

	// ...
	{
		if(Is__REMOTE(p_variable, p_alarm)  < 0)		return OBJ_ABORT;
		if(Is__ONLINE(p_variable, p_alarm)  < 0)		return OBJ_ABORT;
	}

	// 1. [HOLD] Command Set ...
	nCmd_Ret = xCH__doVALVE_OPR_CMD->Set__DATA("HOLD");
	if(nCmd_Ret <= 0)
	{
		szLog.Format("CH_NAME : [%s], CMD [HOLD - ERROR HOLD Opr] Failed(ret:%d)... !!\n", 
					 xCH__doVALVE_OPR_CMD->Get__VARIABLE_NAME(), nCmd_Ret);
		
		Fnc__APP_LOG(szLog);
		return OBJ_ABORT;
	}
	if(nCmd_Ret > 0)
	{
		szLog.Format("CH_NAME : [%s], Cmd[%s] Success", xCH__doVALVE_OPR_CMD->Get__VARIABLE_NAME(), "HOLD");
		Fnc__APP_LOG(szLog);
	}

	Fnc__APP_LOG("Fnc__HOLD() <---- COMPLETE !!\n");

	return OBJ_AVAILABLE;
}

int  CObj__VAT650_TYPE::
Fnc__AUTO_LEARN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString szLog;
	CString strCH_Name;
	CString str_cfg_data;
	int nCmd_Ret = -1;

	Fnc__APP_LOG("Fnc__AUTO_LEARN() ----> START !!\n");

	strCH_Name = xCH_doAUTO_LEARN_CMD->Get__VARIABLE_NAME();

	// ...
	{
		if(Is__REMOTE(p_variable, p_alarm)  < 0)		return OBJ_ABORT;
		if(Is__ONLINE(p_variable, p_alarm)  < 0)		return OBJ_ABORT;
	}

	aCFG_CH__AUTO_LEARN_CMD_TIMEOUT->Get__DATA(str_cfg_data);	// Driver에서 직접 받음..
	szLog.Format("Auto Learn Command Set and Wait timeout:%s", str_cfg_data);
	Fnc__APP_LOG(szLog);

	// 1. [AUTO_LEARN] Command Set ...
	nCmd_Ret = xCH_doAUTO_LEARN_CMD->Set__DATA("AUTO_LEARN");
	if(nCmd_Ret == DRV__CMD_FAIL)
	{
		// ...
		{
			szLog.Format("CH_NAME : [%s], CMD [%s] Failed(ret:%d)... !!\n", 
						 strCH_Name, "AUTO_LEARN", nCmd_Ret);

			Fnc__APP_LOG(szLog);
		}

		// ...
		{
			int alarm_id = ALID__APC_AUTO_LEARN_CMD_TIMEOUT;
		
			p_alarm->Post__ALARM(alarm_id);
		}
		return OBJ_ABORT;
	}
	if(nCmd_Ret > 0)
	{
		szLog.Format("CH_NAME : [%s], Cmd[%s] Success", strCH_Name, "AUTO_LEARN");
		Fnc__APP_LOG(szLog);
	}

	Fnc__APP_LOG("Fnc__AUTO_LEARN() <---- COMPLETE !!\n");

	return OBJ_AVAILABLE;
}
