#include "StdAfx.h"
#include "CObj_Phy__SYS_STD.h"
#include "CObj_Phy__SYS_STD__DEF.h"


// ...
int CObj_Phy__SYS_STD::Call__TIME_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	xI_Module_Obj->Disable__ERROR_CHECK__NOT_STANDBY();

	Set__Module_Time();

	return Fnc__MODULE_OBJ(p_variable, _CMMD__TIME_INIT);
}
int CObj_Phy__SYS_STD::Call__SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	xI_Module_Obj->Disable__ERROR_CHECK__NOT_STANDBY();

	return Fnc__MODULE_OBJ(p_variable, _CMMD__SYSTEM_INIT);
}
int CObj_Phy__SYS_STD::Call__AUTO_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	xI_Module_Obj->Disable__ERROR_CHECK__NOT_STANDBY();

	Set__Module_Time();

	return Fnc__MODULE_OBJ(p_variable, _CMMD__AUTO_INIT);
}


// ...
int CObj_Phy__SYS_STD::Call__CTC_TO_TMC(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__CTC_TO_TMC);
}
int CObj_Phy__SYS_STD::Call__TMC_TO_CTC(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__TMC_TO_CTC);
}


//
int CObj_Phy__SYS_STD::Call__SYSTEM_MAINT(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__SYSTEM_MAINT);
}

//
int CObj_Phy__SYS_STD::Call__JOB_START_READY(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__JOB_START_READY);
}


// ...
void CObj_Phy__SYS_STD::Set__Module_Time()
{
	SYSTEMTIME cur_time;
	CString	   str_time;

	GetLocalTime(&cur_time);

	str_time.Format("%00004d%002d%002d%002d%002d%002d",
					cur_time.wYear,
					cur_time.wMonth, 
					cur_time.wDay,
					cur_time.wHour,
					cur_time.wMinute,
					cur_time.wSecond);

	xCH__MODULE_TIME->Set__DATA(str_time);
}
