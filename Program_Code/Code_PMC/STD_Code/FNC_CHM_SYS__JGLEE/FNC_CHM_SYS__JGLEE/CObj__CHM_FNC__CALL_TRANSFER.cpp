#include "StdAfx.h"
#include "CObj__CHM_FNC.h"

#include "CObj__CHM_FNC__ALID.h"
#include "CObj__CHM_FNC__DEF.h"


#define CMMD__PICK_READY			"PICK_READY"
#define CMMD__PICK_X_READY			"PICK_X_READY"
#define CMMD__PICK_COMPLETE			"PICK_COMPLETE"
#define CMMD__PICK_X_COMPLETE		"PICK_X_COMPLETE"

#define CMMD__PLACE_READY			"PLACE_READY"
#define CMMD__PLACE_X_READY			"PLACE_X_READY"
#define CMMD__PLACE_COMPLETE		"PLACE_COMPLETE"
#define CMMD__PLACE_X_COMPLETE		"PLACE_X_COMPLETE"


// ...
int CObj__CHM_FNC::
Call__PICK_READY(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(!bActive__TRANSFER_OBJ)			return -11;

	int r_flag = pOBJ_CTRL__TRANSFER->Call__OBJECT(CMMD__PICK_READY);
	if(r_flag < 0)			return r_flag;

	Fnc__TRANSFER_START(p_variable,p_alarm);
	return 1;
}
int CObj__CHM_FNC::
Call__PICK_X_READY(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(!bActive__TRANSFER_OBJ)			return -11;

	int r_flag = pOBJ_CTRL__TRANSFER->Call__OBJECT(CMMD__PICK_X_READY);
	if(r_flag < 0)			return r_flag;

	Fnc__TRANSFER_START(p_variable,p_alarm);
	return 1;
}

int CObj__CHM_FNC::
Call__PICK_COMPLETE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(!bActive__TRANSFER_OBJ)			return -11;

	int r_flag = pOBJ_CTRL__TRANSFER->Call__OBJECT(CMMD__PICK_COMPLETE);
	if(r_flag < 0)			return r_flag;

	Fnc__TRANSFER_END(p_variable,p_alarm);
	return 1;
}
int CObj__CHM_FNC::
Call__PICK_X_COMPLETE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(!bActive__TRANSFER_OBJ)			return -11;

	int r_flag = pOBJ_CTRL__TRANSFER->Call__OBJECT(CMMD__PICK_X_COMPLETE);
	if(r_flag < 0)			return r_flag;

	Fnc__TRANSFER_END(p_variable,p_alarm);
	return 1;
}

//	
int CObj__CHM_FNC::
Call__PLACE_READY(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(!bActive__TRANSFER_OBJ)			return -11;

	int r_flag = pOBJ_CTRL__TRANSFER->Call__OBJECT(CMMD__PLACE_READY);
	if(r_flag < 0)			return r_flag;

	Fnc__TRANSFER_START(p_variable,p_alarm);
	return 1;
}
int CObj__CHM_FNC::
Call__PLACE_X_READY(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(!bActive__TRANSFER_OBJ)			return -11;

	int r_flag = pOBJ_CTRL__TRANSFER->Call__OBJECT(CMMD__PLACE_X_READY);
	if(r_flag < 0)			return r_flag;

	Fnc__TRANSFER_START(p_variable,p_alarm);
	return 1;
}

int CObj__CHM_FNC::
Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(!bActive__TRANSFER_OBJ)			return -11;

	Fnc__BALLAST_END(p_variable,p_alarm);

	return pOBJ_CTRL__TRANSFER->Call__OBJECT(CMMD__PLACE_COMPLETE);
}
int CObj__CHM_FNC::
Call__PLACE_X_COMPLETE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(!bActive__TRANSFER_OBJ)			return -11;

	return pOBJ_CTRL__TRANSFER->Call__OBJECT(CMMD__PLACE_X_COMPLETE);
}

//
int CObj__CHM_FNC::
Fnc__TRANSFER_START(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(dEXT_CH__SYSTEM_TRANSFER_MODE->Check__DATA(STR__ATM) > 0)
	{
		return 11;
	}

	sCH__TRANSFER_BALLAST_FLAG->Set__DATA(STR__YES);

	if(Fnc__TRANS_BALLAST_START(p_variable,p_alarm) > 0)
	{
		return 1;
	}

	Fnc__BALLAST_END(p_variable,p_alarm);
	return 1;
}
int CObj__CHM_FNC::
Fnc__TRANSFER_END(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(dEXT_CH__SYSTEM_TRANSFER_MODE->Check__DATA(STR__ATM) > 0)
	{
		return 11;
	}

	sCH__TRANSFER_BALLAST_FLAG->Set__DATA("");

	if(Fnc__CHM_BALLAST_START(p_variable,p_alarm) > 0)
	{
		return 1;
	}
	
	Fnc__BALLAST_END(p_variable,p_alarm);
	return 1;
}


// ...
int CObj__CHM_FNC::
Call__SLOT_OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(iActive__SIM_MODE > 0)
	{
		dEXT_CH__PMC_SLIT_VLV_STS->Set__DATA(STR__OPEN);
	}

	return 1;
}

int CObj__CHM_FNC::
Call__SLOT_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(iActive__SIM_MODE > 0)
	{
		dEXT_CH__PMC_SLIT_VLV_STS->Set__DATA(STR__CLOSE);
	}

	return 1;
}
