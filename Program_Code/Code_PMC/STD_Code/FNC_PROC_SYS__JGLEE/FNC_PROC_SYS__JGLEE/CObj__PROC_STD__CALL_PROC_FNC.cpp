#include "StdAfx.h"
#include "CObj__PROC_STD.h"


// PRE-PROCESS ...
int CObj__PROC_STD
::Call__PRE_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__PRE);

	return Fnc__PROC_READY(p_variable, p_alarm);
}
int CObj__PROC_STD
::Call__PRE_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__PRE);

	return Fnc__PROC_START(p_variable, p_alarm);
}

// MAIN-PROCESS ...
int CObj__PROC_STD
::Call__MAIN_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__MAIN);

	return Fnc__PROC_READY(p_variable, p_alarm);
}
int CObj__PROC_STD
::Call__MAIN_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__MAIN);

	return Fnc__PROC_START(p_variable, p_alarm);
}

// POST-PROCESS ...
int CObj__PROC_STD
::Call__POST_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__POST);

	return Fnc__PROC_READY(p_variable, p_alarm);
}
int CObj__PROC_STD
::Call__POST_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__POST);

	return Fnc__PROC_START(p_variable, p_alarm);
}

// MANUAL-PROCESS ...
int CObj__PROC_STD
::Call__MANUAL_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__MANUAL);

	return Fnc__PROC_READY(p_variable, p_alarm);
}
int CObj__PROC_STD
::Call__MANUAL_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	dCH__CUR_PROCESS_TYPE->Set__DATA(STR__MANUAL);

	return Fnc__PROC_START(p_variable, p_alarm);
}
