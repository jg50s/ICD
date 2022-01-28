#include "StdAfx.h"
#include "CObj__TwoManiFold_LL.h"
#include "CObj__TwoManiFold_LL__ALID.h"


//----------------------------------------------------------------------------------------------------
// ALL : PUMP VLV CLOSE -----
int  CObj__TwoManiFold_LL
::Call__ALL_PUMP_VLV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
						   CII_OBJECT__ALARM* p_alarm)
{
	int flag = 1;

	// LBA -----
	if(Fnc__LBA__PUMP_VLV_CLOSE() < 0)
	{
		flag = -1;
	}

	// LBB -----
	if(Fnc__LBB__PUMP_VLV_CLOSE() < 0)
	{
		flag = -1;
	}

	if(flag < 0)
	{
		Fnc__PUMP_VLV_CLOSE_DELAY();
	}
	return 1;
}

// LBA : PUMP VLV OPEN -----
int  CObj__TwoManiFold_LL
::Call__LBA_PUMP_VLV_OPEN(CII_OBJECT__VARIABLE* p_variable,
						  CII_OBJECT__ALARM* p_alarm)
{
	int flag = 1;

	// LBB -----
	if(Fnc__LBB__PUMP_VLV_CLOSE() < 0)
	{
		flag = -1;
	}

	if(flag < 0)
	{
		Fnc__PUMP_VLV_CLOSE_DELAY();
	}

	return 1;
}

// LBB : PUMP VLV OPEN -----
int  CObj__TwoManiFold_LL
::Call__LBB_PUMP_VLV_OPEN(CII_OBJECT__VARIABLE* p_variable,
						  CII_OBJECT__ALARM* p_alarm)
{
	int flag = 1;

	// LBA -----
	if(Fnc__LBA__PUMP_VLV_CLOSE() < 0)
	{
		flag = -1;
	}

	if(flag < 0)
	{
		Fnc__PUMP_VLV_CLOSE_DELAY();
	}

	return 1;
}

// LBA -----
// VAC_VLV_OPEN
int  CObj__TwoManiFold_LL
::Call__LBA_VLV_OPEN(CII_OBJECT__VARIABLE* p_variable,
				     CII_OBJECT__ALARM* p_alarm)
{
	Fnc__LBA__PUMP_VLV_OPEN(-1);
	return 1;
}
// VAC_VLV_CLOSE
int  CObj__TwoManiFold_LL
::Call__LBA_VLV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
					  CII_OBJECT__ALARM* p_alarm)
{
	Fnc__LBA__PUMP_VLV_CLOSE();
	return 1;
}

// LBB -----
// VAC_VLV_OPEN
int  CObj__TwoManiFold_LL
::Call__LBB_VLV_OPEN(CII_OBJECT__VARIABLE* p_variable,
				     CII_OBJECT__ALARM* p_alarm)
{
	Fnc__LBB__PUMP_VLV_OPEN(-1);
	return 1;
}
// VAC_VLV_CLOSE
int  CObj__TwoManiFold_LL
::Call__LBB_VLV_CLOSE(CII_OBJECT__VARIABLE* p_variable,
					  CII_OBJECT__ALARM* p_alarm)
{
	Fnc__LBB__PUMP_VLV_CLOSE();
	return 1;
}

// ...
int  CObj__TwoManiFold_LL
::Call__LBA_VLV_ALL_CLOSE(CII_OBJECT__VARIABLE* p_variable,
						  CII_OBJECT__ALARM* p_alarm)
{
	Fnc__LBA__PUMP_VLV_CLOSE();
	Fnc__LBA__VENT_VLV_CLOSE();
	return 1;
}

int  CObj__TwoManiFold_LL
::Call__LBB_VLV_ALL_CLOSE(CII_OBJECT__VARIABLE* p_variable,
						  CII_OBJECT__ALARM* p_alarm)
{
	Fnc__LBB__PUMP_VLV_CLOSE();
	Fnc__LBB__VENT_VLV_CLOSE();
	return 1;
}
