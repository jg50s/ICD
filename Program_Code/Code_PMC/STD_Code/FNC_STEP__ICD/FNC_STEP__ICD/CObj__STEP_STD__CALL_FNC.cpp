#include "StdAfx.h"
#include "CObj__STEP_STD.h"
#include "CObj__STEP_STD__DEF.h"


// ...
int CObj__STEP_STD
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int CObj__STEP_STD
::Call__READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		sCH__INFO_STEP_CUR_NUM->Set__DATA("");
		sCH__INFO_STEP_PRE_TIME->Set__DATA("");
	}

	// EPD.INIT ...
	{
		EPD_OBJ__Call_INIT();
	}

	return _Fnc__END();
}
int CObj__STEP_STD
::Call__START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	// Temperature.Check ...
	{

	}
	return 1;
}

int CObj__STEP_STD
::Call__ABORT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	sCH__OBJ_MSG->Set__DATA("Call__ABORT() : Start ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");

	_Fnc__END();

	sCH__OBJ_MSG->Set__DATA("Call__ABORT() : End ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");
	return 1;
}
int CObj__STEP_STD
::Call__END(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	sCH__OBJ_MSG->Set__DATA("Call__END() : Start ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");

	_Fnc__END();

	sCH__OBJ_MSG->Set__DATA("Call__END() : End ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");
	return 1;
}

int CObj__STEP_STD::_Fnc__END()
{
	int i;

	// EPD.IDLE ...
	{
		EPD_OBJ__Start_IDLE();
	}

	// RF.RPS ...
	{
		RF_RPS_OBJ__Start_OFF();
	}
	// RF.PULSE ...
	{
		RF_PULSE_OBJ__Start_OFF();
	}
	// RF.LF ...
	{
		RF_LF_OBJ__Start_OFF();
	}
	// RF.HF ...
	{
		RF_HF_OBJ__Start_OFF();
	}
	
	// ESC ...
	{
		ESC_OBJ__Start_HE_CLOSE();
		ESC_OBJ__Init_DATA();
	}

	// MFC_X.CTRL ...
	for(i=0; i<iDATA__MFC_SIZE; i++)
	{
		MFC_OBJ__Start_CLOSE(i);
	}

	// APC.CTRL ...
	{
		APC_OBJ__Start_OPEN();
	}

	return 1;
}

