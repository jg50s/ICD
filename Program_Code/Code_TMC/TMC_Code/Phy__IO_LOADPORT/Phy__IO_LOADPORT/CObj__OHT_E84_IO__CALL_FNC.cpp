#include "StdAfx.h"
#include "CObj__OHT_E84_IO.h"
#include "CObj__OHT_E84_IO__DEF.h"


//-------------------------------------------------------------------------	
int  CObj__OHT_E84_IO::
Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__INIT(p_variable, p_alarm);
}


int  CObj__OHT_E84_IO::
Fnc__LOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int state = OBJ_ABORT;

CHK_RTY:

	if(iSIM_FLAG > 0)
	{
		diEXT_CH__PHY_LPx__CST_PLACE->Set__DATA(_OFF);
		diEXT_CH__PHY_LPx__CST_PRESENT->Set__DATA(_OFF);

		Sleep(1000);
	}

	if(dCH__CFG_E84LOAD_CLAMP_CHECK->Check__DATA("TRUE") > 0)
	{
		if(diEXT_CH__LPx__CLAMP->Check__DATA("ON") > 0)
		{
			// Alarm..
			int alarm_id = ALID__LP_E84A_LOAD_CLAMP_CHECK;
			CString r_act;

			p_alarm->Popup__ALARM(alarm_id, r_act);

			if(r_act.CompareNoCase("RETRY") == 0)
			{
				Sleep(1000);
				goto CHK_RTY;
			}
			else
			{
				return OBJ_ABORT;
			}
		}
	}

	// ...
	{
		dCH__E84_RUN_SNS->Set__DATA("RUN");   // "UNKNOWN RUN DONE STOP"
		dCH__OTR_OUT_dLP_PIO_TRANSFER->Set__DATA(_YES);

		xPIO_LOG_CTRL->WRITE__LOG("<< LOAD START !!>>");
		xPIO_LOG_CTRL->WRITE__LOG("      IN[ VALID  CS_0  COMPT  CS_1  TR_REQ  BUSY  CONT ] OUT[ L_REQ  U_REQ  READY  HO_AVBL  ES     ]");

		state = Fnc__LOAD_PIO(p_variable, p_alarm);
		if(state == SEQ_COMPLETE)
		{
			// ... CLAMP 명령 넣을것...
			// if(Fnc__CLAMP(p_variable, p_alarm, "E84_LOAD") != SEQ_AVAILABLE)	return state; // Load시 clamp 할 것임..
			// 

			dCH__E84_RUN_SNS->Set__DATA("DONE");   // "UNKNOWN RUN DONE STOP"
			xPIO_LOG_CTRL->WRITE__LOG("<< LOAD COMPLETE !!>> \n");
			_sleep(1000);
		}
		else
		{
			xPIO_LOG_CTRL->WRITE__LOG("<< LOAD FAIL !!>> \n");
		}

		Is_CS_VALID_OFF(p_variable, p_alarm);
	}

	return state;	
}

int  CObj__OHT_E84_IO::
Fnc__UNLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(iSIM_FLAG > 0)
	{
		diEXT_CH__PHY_LPx__CST_PLACE->Set__DATA(_ON);
		diEXT_CH__PHY_LPx__CST_PRESENT->Set__DATA(_ON);

		Sleep(1000);
	}

	if(Fnc__UNCLAMP(p_variable, p_alarm, "E84_UNLOAD") != OBJ_AVAILABLE)
	{
		return OBJ_ABORT;
	}

	// ...
	dCH__E84_RUN_SNS->Set__DATA("RUN");   // "UNKNOWN RUN DONE STOP"
	dCH__OTR_OUT_dLP_PIO_TRANSFER->Set__DATA(_YES);

	xPIO_LOG_CTRL->WRITE__LOG("<< UNLOAD START !!>>");
	xPIO_LOG_CTRL->WRITE__LOG("      IN[ VALID  CS_0  COMPT  CS_1  TR_REQ  BUSY  CONT ] OUT[ L_REQ  U_REQ  READY  HO_AVBL  ES     ]");

	int state = Fnc__UNLOAD_PIO(p_variable, p_alarm);
	if(state == SEQ_COMPLETE)
	{
		dCH__E84_RUN_SNS->Set__DATA("DONE");   // "UNKNOWN RUN DONE STOP"
		xPIO_LOG_CTRL->WRITE__LOG("<< UNLOAD COMPLETE !!>> \n");
		_sleep(1000);
	}
	else
	{
		xPIO_LOG_CTRL->WRITE__LOG("<< UNLOAD FAIL !!>> \n");
	}

	Is_CS_VALID_OFF(p_variable, p_alarm);
	return state;
}
