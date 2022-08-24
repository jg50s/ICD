#include "StdAfx.h"
#include "CObj__HE_VLV.h"


// ...
int  CObj__HE_VLV
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int  CObj__HE_VLV
::Call__CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	Call__SUPPLY_VLV_CTRL(p_variable, p_alarm, STR__CLOSE);
	Call__FINAL_VLV_CTRL(p_variable, p_alarm,  STR__CLOSE);
	Call__BYPASS_VLV_CTRL(p_variable, p_alarm, STR__CLOSE);
	Call__DUMP_VLV_CTRL(p_variable, p_alarm,   STR__CLOSE);

	return 1;
}

// SUPPLY_VLV.CTRL ...
int  CObj__HE_VLV
::Call__SUPPLY_VLV_CTRL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString& vlv_ctrl)
{
	int i;

	for(i=0; i<iSIZE__SUPPLY_VLV; i++)
	{
		doEXT_CH__SUPPLY_VLV_X[i]->Set__DATA(vlv_ctrl);
	}
	return 1;
}

// BYPASS_VLV.CTRL ...
int  CObj__HE_VLV
::Call__BYPASS_VLV_CTRL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString& vlv_ctrl)
{
	int i;

	for(i=0; i<iSIZE__BYPASS_VLV; i++)
	{
		doEXT_CH__BYPASS_VLV_X[i]->Set__DATA(vlv_ctrl);
	}
	return 1;
}

// DUMP_VLV.CTRL ...
int  CObj__HE_VLV
::Call__DUMP_VLV_CTRL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString& vlv_ctrl)
{
	int i;

	for(i=0; i<iSIZE__DUMP_VLV; i++)
	{
		doEXT_CH__DUMP_VLV_X[i]->Set__DATA(vlv_ctrl);
	}
	return 1;
}

// FINAL_VLV.CTRL ...
int  CObj__HE_VLV
::Call__FINAL_VLV_CTRL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const CString& vlv_ctrl)
{
	int i;

	for(i=0; i<iSIZE__FINAL_VLV; i++)
	{
		doEXT_CH__FINAL_VLV_X[i]->Set__DATA(vlv_ctrl);
	}
	return 1;
}


// ...
int  CObj__HE_VLV
::Call__BYPASS_FLOW(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	Call__DUMP_VLV_CTRL(p_variable, p_alarm,   STR__CLOSE);
	Call__FINAL_VLV_CTRL(p_variable, p_alarm,  STR__CLOSE);
	
	Call__BYPASS_VLV_CTRL(p_variable, p_alarm, STR__OPEN);
	Call__SUPPLY_VLV_CTRL(p_variable, p_alarm, STR__OPEN);

	return 1;
}

int  CObj__HE_VLV
::Call__DUMP_FLOW(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	Call__SUPPLY_VLV_CTRL(p_variable, p_alarm, STR__CLOSE);
	Call__FINAL_VLV_CTRL(p_variable, p_alarm,  STR__CLOSE);

	Call__BYPASS_VLV_CTRL(p_variable, p_alarm, STR__OPEN);
	Call__DUMP_VLV_CTRL(p_variable, p_alarm,   STR__OPEN);

	return 1;
}

int  CObj__HE_VLV
::Call__FINAL_FLOW(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	Call__DUMP_VLV_CTRL(p_variable, p_alarm,   STR__CLOSE);

	Call__SUPPLY_VLV_CTRL(p_variable, p_alarm, STR__OPEN);
	Call__FINAL_VLV_CTRL(p_variable, p_alarm,  STR__OPEN);
	Call__BYPASS_VLV_CTRL(p_variable, p_alarm, STR__OPEN);

	return 1;
}

