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
	return _Fnc__END();
}
int CObj__STEP_STD
::Call__START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString rcp__sh_temp_x[_CFG__SH_SIZE];
	CString rcp__sh_offset_x[_CFG__SH_SIZE];
	CString rcp__sh_warning_x[_CFG__SH_SIZE];
	CString rcp__sh_alarm_x[_CFG__SH_SIZE];

	CString rcp__wall_main_temp;
	CString rcp__wall_offset;
	CString rcp__wall_warning;
	CString rcp__wall_alarm;

	int i;

	// Showerhead.Temperature ...
	for(i=0; i<_CFG__SH_SIZE; i++)
	{
		rcp__sh_temp_x[i]    = sCH__RCP_SH_TEMP_X[i]->Get__STRING();
		rcp__sh_offset_x[i]  = sCH__RCP_SH_OFFSET_X[i]->Get__STRING();
		rcp__sh_warning_x[i] = sCH__RCP_SH_WARNING_X[i]->Get__STRING();
		rcp__sh_alarm_x[i]   = sCH__RCP_SH_ALARM_X[i]->Get__STRING();
	}
	// Wall.Temperature ...
	{
		rcp__wall_main_temp = sCH__RCP_WALL_MAIN_TEMP->Get__STRING();
		rcp__wall_offset    = sCH__RCP_WALL_MAIN_OFFSET->Get__STRING();	
		rcp__wall_warning   = sCH__RCP_WALL_MAIN_WARNING->Get__STRING();	
		rcp__wall_alarm     = sCH__RCP_WALL_MAIN_ALARM->Get__STRING();
	}

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

	// RF.RPS ...
	{
		RF_RPS_OBJ__Start_OFF();
	}
	// RF.400KHZ ...
	{
		RF_400KHZ_OBJ__Start_OFF();
	}
	// RF.40MHZ ...
	{
		RF_40MHZ_OBJ__Start_OFF();
	}
	
	// ESC ...
	{
		ESC_OBJ__Start_HE_CLOSE();
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

