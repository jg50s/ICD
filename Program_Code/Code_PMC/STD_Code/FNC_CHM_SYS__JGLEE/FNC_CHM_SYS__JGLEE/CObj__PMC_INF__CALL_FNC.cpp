#include "StdAfx.h"
#include "CObj__PMC_INF.h"


// ...
int  CObj__PMC_INF
::Call__AUTO_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	Call__TIME_INIT(p_variable);

	return Call__SYSTEM_INIT(p_variable);
}

int  CObj__PMC_INF
::Call__TIME_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	CString time;

	xCH__MODULE_TIME->Get__DATA(time);
	if(time.GetLength() >= 14)
	{
		CString year, month, date, hour, minute, second;

		year   = time.Mid(0,4);
		month  = time.Mid(4,2);
		date   = time.Mid(6,2);
		hour   = time.Mid(8,2);
		minute = time.Mid(10,2);
		second = time.Mid(12,2);

		//
		SYSTEMTIME	sys_time;
		GetLocalTime(&sys_time);

		sys_time.wYear   = atoi(year);
		sys_time.wMonth  = atoi(month); 
		sys_time.wDay	 = atoi(date);
		sys_time.wHour   = atoi(hour);
		sys_time.wMinute = atoi(minute); 
		sys_time.wSecond = atoi(second); 

		SetLocalTime(&sys_time);
	}			
	return 1;
}


// ...
int  CObj__PMC_INF
::Call__SYSTEM_INIT(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__SYSTEM_INIT);
}
int  CObj__PMC_INF
::Call__SYSTEM_MAINT(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__SYSTEM_MAINT);
}

int  CObj__PMC_INF
::Call__PUMP(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PUMP);
}

int  CObj__PMC_INF
::Call__VENT(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__VENT);
}


// ...
int CObj__PMC_INF
::Call__LEAK_CHECK(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__LEAK_CHECK);
}

int CObj__PMC_INF
::Call__AUTO_PM(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__AUTO_PM);
}

int CObj__PMC_INF
::Call__PURGE(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PURGE);
}

// ...
int CObj__PMC_INF
::Call__PICK_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PICK_READY);
}
int CObj__PMC_INF
::Call__PICK_X_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PICK_X_READY);
}
int CObj__PMC_INF
::Call__PICK_COMPLETE(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	//
	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PICK_COMPLETE);
}
int CObj__PMC_INF
::Call__PICK_X_COMPLETE(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	//
	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PICK_X_COMPLETE);
}

int CObj__PMC_INF
::Call__PLACE_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PLACE_READY);
}
int CObj__PMC_INF
::Call__PLACE_X_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PLACE_X_READY);
}
int CObj__PMC_INF
::Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PLACE_COMPLETE);
}
int CObj__PMC_INF
::Call__PLACE_X_COMPLETE(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PLACE_X_COMPLETE);
}


// ...
int CObj__PMC_INF
::Call__PRO_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	xEXT_CH__STEP_START->Set__DATA("0");
	xEXT_CH__STEP_END->Set__DATA("0");

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PRO_READY);
}
int CObj__PMC_INF
::Call__PRO_START(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PRO_START);
}

int CObj__PMC_INF
::Call__CLN_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	xEXT_CH__STEP_START->Set__DATA("0");
	xEXT_CH__STEP_END->Set__DATA("0");

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__CLN_READY);
}
int CObj__PMC_INF
::Call__CLN_START(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__CLN_START);
}

int CObj__PMC_INF
::Call__PRE_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	xEXT_CH__STEP_START->Set__DATA("0");
	xEXT_CH__STEP_END->Set__DATA("0");

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PRE_READY);
}
int CObj__PMC_INF
::Call__PRE_START(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__PRE_START);
}

int CObj__PMC_INF
::Call__MNT_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	xEXT_CH__STEP_START->Set__DATA("0");
	xEXT_CH__STEP_END->Set__DATA("0");

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__MNT_READY);
}
int CObj__PMC_INF
::Call__MNT_START(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__MNT_START);
}

// ...
int CObj__PMC_INF
::Call__JOB_START_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__JOB_START_READY);
}
int CObj__PMC_INF
::Call__JOB_END_READY(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	p_ext_mode_ctrl->Abort__CTRL_STS();

	return p_ext_mode_ctrl->Call__FNC_MODE(sEXT_MODE__JOB_END_READY);
}
