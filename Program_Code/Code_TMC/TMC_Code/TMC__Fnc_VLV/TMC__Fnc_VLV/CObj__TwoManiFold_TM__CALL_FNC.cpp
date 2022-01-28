#include "StdAfx.h"
#include "CObj__TwoManiFold_TM.h"
#include "CObj__TwoManiFold_TM__ALID.h"


//----------------------------------------------------------------------------------------------------
// ALL : PUMP VLV CLOSE -----
int  CObj__TwoManiFold_TM
::Call__ALL_PUMP_VLV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
						   CII_OBJECT__ALARM* p_alarm)
{
	int flag = 1;

	// TMC_CHM -----
	if(Fnc__TMC_CHM__PUMP_VLV_CLOSE() < 0)
	{
		flag = -1;
	}

	if(flag < 0)
	{
		Fnc__PUMP_VLV_CLOSE_DELAY();
	}
	return 1;
}

// TMC_CHM : PUMP VLV OPEN -----
int  CObj__TwoManiFold_TM
::Call__TMC_CHM_PUMP_VLV_OPEN(CII_OBJECT__VARIABLE* p_variable,
							  CII_OBJECT__ALARM* p_alarm)
{
	int flag = 1;

	if(flag < 0)
	{
		Fnc__PUMP_VLV_CLOSE_DELAY();
	}
	return 1;
}

// TMC_CHM -----
// VAC_VLV_OPEN
int  CObj__TwoManiFold_TM::
Call__TMC_CHM_VLV_OPEN(CII_OBJECT__VARIABLE* p_variable,
					   CII_OBJECT__ALARM* p_alarm)
{
	Fnc__TMC_CHM__PUMP_VLV_OPEN(-1);
	return 1;
}
// VAC_VLV_CLOSE
int  CObj__TwoManiFold_TM::
Call__TMC_CHM_VLV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
						CII_OBJECT__ALARM* p_alarm)
{
	Fnc__TMC_CHM__PUMP_VLV_CLOSE();
	return 1;
}


int  CObj__TwoManiFold_TM::
Call__TMC_CHM_VLV_ALL_CLOSE(CII_OBJECT__VARIABLE* p_variable,
							CII_OBJECT__ALARM* p_alarm)
{
	Fnc__TMC_CHM__PUMP_VLV_CLOSE();
	Fnc__TMC_CHM__VENT_VLV_CLOSE();
	return 1;
}
