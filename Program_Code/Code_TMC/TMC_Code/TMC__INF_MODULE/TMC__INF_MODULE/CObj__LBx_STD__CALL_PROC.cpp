#include "StdAfx.h"
#include "CObj__LBx_STD.h"


#define _CMMD__PROC_READY				"PROC_READY"
#define _CMMD__PROC_START				"PROC_START"

#define _CMMD__PRE_READY				"PRE_READY"
#define _CMMD__PRE_START				"PRE_START"

#define _CMMD__CLN_READY				"CLN_READY"
#define _CMMD__CLN_START				"CLN_START"

#define _CMMD__MNT_READY				"MNT_READY"
#define _CMMD__MNT_START				"MNT_START"


// ...
int  CObj__LBx_STD
::Call__PROC_READY(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm)
{
	return pLBx__OBJ_CTRL->Call__OBJECT(_CMMD__PROC_READY);
}
int  CObj__LBx_STD
::Call__PROC_START(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm)
{
	return pLBx__OBJ_CTRL->Call__OBJECT(_CMMD__PROC_START);
}

int  CObj__LBx_STD
::Call__PRE_READY(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	return pLBx__OBJ_CTRL->Call__OBJECT(_CMMD__PRE_READY);
}
int  CObj__LBx_STD
::Call__PRE_START(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	return pLBx__OBJ_CTRL->Call__OBJECT(_CMMD__PRE_START);
}

int  CObj__LBx_STD
::Call__CLN_READY(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	return pLBx__OBJ_CTRL->Call__OBJECT(_CMMD__CLN_READY);
}
int  CObj__LBx_STD
::Call__CLN_START(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	return pLBx__OBJ_CTRL->Call__OBJECT(_CMMD__CLN_START);
}

int  CObj__LBx_STD
::Call__MNT_READY(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	return pLBx__OBJ_CTRL->Call__OBJECT(_CMMD__MNT_READY);
}
int  CObj__LBx_STD
::Call__MNT_START(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	return pLBx__OBJ_CTRL->Call__OBJECT(_CMMD__MNT_START);
}
