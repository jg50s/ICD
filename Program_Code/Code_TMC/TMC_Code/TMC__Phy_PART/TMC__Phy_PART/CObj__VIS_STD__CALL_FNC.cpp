#include "StdAfx.h"
#include "CObj__VIS_STD.h"
#include "CObj__VIS_STD__DEF.h"


//----------------------------------------------------------------------------------------------------
// INIT ----- 
int  CObj__VIS_STD
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return pVISx__OBJ_CTRL->Call__OBJECT(CMMD__INIT);
}

// RUN_START -----
int  CObj__VIS_STD
::Call__RUN_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return pVISx__OBJ_CTRL->Call__OBJECT(CMMD__RUN_START);
}

// PRO_START -----
int  CObj__VIS_STD
::Call__PRO_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int nRet = pVISx__OBJ_CTRL->Call__OBJECT(CMMD__PRO_START);

	CString szData;
	sEXT_CH_VIS1__JUDGMENT->Get__DATA(szData);
	sCH__JUDGMENT->Set__DATA(szData);

	return nRet; 
}

// PRO_STOP -----
int  CObj__VIS_STD
::Call__PRO_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return pVISx__OBJ_CTRL->Call__OBJECT(CMMD__PRO_STOP);
}

// DOWNLOAD -----
int  CObj__VIS_STD
::Call__DOWNLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return pVISx__OBJ_CTRL->Call__OBJECT(CMMD__DOWNLOAD);
}


// PRO_READY -----
int  CObj__VIS_STD
::Call__PRO_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return pVISx__OBJ_CTRL->Call__OBJECT(CMMD__PRO_READY);
}

// PLACE_READY -----
int  CObj__VIS_STD
::Call__PLACE_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return pVISx__OBJ_CTRL->Call__OBJECT(CMMD__PLACE_READY);
}

// PLACE_COMPLETE -----
int  CObj__VIS_STD
::Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return pVISx__OBJ_CTRL->Call__OBJECT(CMMD__PLACE_COMPLETE);
}

// PICK_READY -----
int  CObj__VIS_STD
::Call__PICK_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return pVISx__OBJ_CTRL->Call__OBJECT(CMMD__PICK_READY);
}

// PICK_COMPLETE -----
int  CObj__VIS_STD
::Call__PICK_COMPLETE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return pVISx__OBJ_CTRL->Call__OBJECT(CMMD__PICK_COMPLETE);
}

// GET_RESULT -----
int  CObj__VIS_STD
::Call__GET_RESULT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return pVISx__OBJ_CTRL->Call__OBJECT(CMMD__GET_RESULT);
}

// GET_FILE -----
int  CObj__VIS_STD
::Call__GET_FILE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString szData;

	int nRet = pVISx__OBJ_CTRL->Call__OBJECT(CMMD__GET_FILE);

	if(nRet > 0)
	{
		sEXT_CH_VIS1__RECIPE_LIST->Get__DATA(szData);
		sCH__RECIPE_LIST->Set__DATA(szData);
	}
	else
	{
		sCH__RECIPE_LIST->Set__DATA("");
	}

	return nRet; 
}

// EXCHANGE_READY -----
int  CObj__VIS_STD
::Call__EXCHANGE_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return pVISx__OBJ_CTRL->Call__OBJECT(CMMD__EXCHANGE_READY);
}
