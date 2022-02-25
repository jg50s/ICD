#include "StdAfx.h"
#include "CObj_Phy__ROBOT_ATM.h"
#include "CObj_Phy__ROBOT_ATM__DEF.h"


//--------------------------------------------------------------------------------
// ROBOT

int  CObj_Phy__ROBOT_ATM::Call__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	Fnc__SET_TIME();

	return Fnc__MODULE_OBJ(p_variable, _CMMD__INIT);
}
int  CObj_Phy__ROBOT_ATM::Call__HOME(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__HOME);
}

int  CObj_Phy__ROBOT_ATM::Call__MAINT(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__MAINT);
}

int  CObj_Phy__ROBOT_ATM::Call__PICK(CII_OBJECT__VARIABLE* p_variable)
{
	Fnc__SET_ANI_ARM(p_variable);

	return Fnc__MODULE_OBJ(p_variable, _CMMD__PICK);
}
int  CObj_Phy__ROBOT_ATM::Call__XPICK(CII_OBJECT__VARIABLE* p_variable)
{
	Fnc__SET_ANI_ARM(p_variable);

	return Fnc__MODULE_OBJ(p_variable, _CMMD__X_PICK);
}

int  CObj_Phy__ROBOT_ATM::Call__PLACE(CII_OBJECT__VARIABLE* p_variable)
{
	Fnc__SET_ANI_ARM(p_variable);

	return Fnc__MODULE_OBJ(p_variable, _CMMD__PLACE);
}
int  CObj_Phy__ROBOT_ATM::Call__XPLACE(CII_OBJECT__VARIABLE* p_variable)
{
	Fnc__SET_ANI_ARM(p_variable);

	return Fnc__MODULE_OBJ(p_variable, _CMMD__X_PLACE);
}

int  CObj_Phy__ROBOT_ATM::Call__ROTATE(CII_OBJECT__VARIABLE* p_variable)
{
	Fnc__SET_ANI_ARM(p_variable);

	return Fnc__MODULE_OBJ(p_variable, _CMMD__ROTATE);
}

int  CObj_Phy__ROBOT_ATM::Call__SWAP_PMx(CII_OBJECT__VARIABLE* p_variable)
{
	Fnc__SET_ANI_ARM(p_variable);

	return Fnc__MODULE_OBJ(p_variable, _CMMD__SWAP);
}


//--------------------------------------------------------------------------------
// ROBOT & MODULE

int  CObj_Phy__ROBOT_ATM::Call__SWAP_ALx(CII_OBJECT__VARIABLE* p_variable)
{
	if(iUPPER_OBJ__FLAG < 0)
	{
		return -1;
	}

	xI_Upper_Obj->Disable__ERROR_CHECK__NOT_STANDBY();

	return Fnc__MODULE_OBJ(p_variable, _CMMD__SWAP_ALx);
}
int  CObj_Phy__ROBOT_ATM::Call__SWAP_LBx(CII_OBJECT__VARIABLE* p_variable)
{
	if(iUPPER_OBJ__FLAG < 0)
	{
		return -1;
	}

	xI_Upper_Obj->Disable__ERROR_CHECK__NOT_STANDBY();

	return Fnc__MODULE_OBJ(p_variable, _CMMD__SWAP_LBx);
}
int  CObj_Phy__ROBOT_ATM::Call__SWAP_VISx(CII_OBJECT__VARIABLE* p_variable)
{
	if(iUPPER_OBJ__FLAG < 0)
	{
		return -1;
	}

	xI_Upper_Obj->Disable__ERROR_CHECK__NOT_STANDBY();

	return Fnc__MODULE_OBJ(p_variable, _CMMD__SWAP_VISx);
}


//--------------------------------------------------------------------------------
int  CObj_Phy__ROBOT_ATM::Call__LP_MAP(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__LP_MAP);
}


//--------------------------------------------------------------------------------
void CObj_Phy__ROBOT_ATM::Fnc__SET_TIME()
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

void CObj_Phy__ROBOT_ATM::Fnc__SET_ANI_ARM(CII_OBJECT__VARIABLE* p_variable)
{
	if(sPara0__Arm_Type.CompareNoCase("B") == 0)
	{
		dCH__ANI_ROTE_ARM->Set__DATA("B");
	}
	else
	{
		dCH__ANI_ROTE_ARM->Set__DATA("A");
	}
}
