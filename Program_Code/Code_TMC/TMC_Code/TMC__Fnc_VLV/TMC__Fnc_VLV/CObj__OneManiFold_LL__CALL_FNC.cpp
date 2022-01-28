#include "StdAfx.h"
#include "CObj__OneManiFold_LL.h"
#include "CObj__OneManiFold_LL__ALID.h"


int  CObj__OneManiFold_LL
::Call__ALL_PUMP_VLV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
						   CII_OBJECT__ALARM* p_alarm)
{
	int flag = 1;

	if(Fnc__LLx__PUMP_VLV_CLOSE() < 0)
	{
		flag = -1;
	}

	if(flag < 0)
	{
		Fnc__PUMP_VLV_CLOSE_DELAY();
	}
	return 1;
}

int  CObj__OneManiFold_LL
::Call__LLx_PUMP_VLV_OPEN(CII_OBJECT__VARIABLE* p_variable,
						  CII_OBJECT__ALARM* p_alarm)
{
	int flag = 1;

	if(Fnc__LLx__PUMP_VLV_CLOSE() < 0)
	{
		flag = -1;
	}

	if(flag < 0)
	{
		Fnc__PUMP_VLV_CLOSE_DELAY();
	}

	return 1;
}

int  CObj__OneManiFold_LL
::Call__LLx_VLV_OPEN(CII_OBJECT__VARIABLE* p_variable,
					 CII_OBJECT__ALARM* p_alarm)
{
	Fnc__LLx__PUMP_VLV_OPEN(-1);
	return 1;
}
int  CObj__OneManiFold_LL
::Call__LLx_VLV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
					  CII_OBJECT__ALARM* p_alarm)
{
	Fnc__LLx__PUMP_VLV_CLOSE();
	return 1;
}

int  CObj__OneManiFold_LL
::Call__LLx_VLV_ALL_CLOSE(CII_OBJECT__VARIABLE* p_variable,
						  CII_OBJECT__ALARM* p_alarm)
{
	Fnc__LLx__PUMP_VLV_CLOSE();
	Fnc__LLx__VENT_VLV_CLOSE();
	return 1;
}
