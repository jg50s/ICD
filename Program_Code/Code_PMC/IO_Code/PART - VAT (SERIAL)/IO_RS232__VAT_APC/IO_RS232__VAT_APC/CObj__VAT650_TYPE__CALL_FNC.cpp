#include "StdAfx.h"
#include "CObj__VAT650_TYPE.h"



//-------------------------------------------------------------------------	
int  CObj__VAT650_TYPE::
Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int comm_flag)
{
	return Fnc__INIT(p_variable,p_alarm,comm_flag);
}

int  CObj__VAT650_TYPE::
Call__OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__OPEN(p_variable,p_alarm);
}
int  CObj__VAT650_TYPE::
Call__CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__CLOSE(p_variable,p_alarm);
}

int  CObj__VAT650_TYPE::
Call__PRESSURE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__PRESSURE(p_variable,p_alarm);
}
int  CObj__VAT650_TYPE::
Call__POSITION(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__POSITION(p_variable,p_alarm);
}

int  CObj__VAT650_TYPE::
Call__POSITION_WAIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__POSITION_WAIT(p_variable,p_alarm,1);
}
int  CObj__VAT650_TYPE::
Call__POSITION_NO_WAIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__POSITION_WAIT(p_variable,p_alarm,-1);
}

int  CObj__VAT650_TYPE::
Call__HOLD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__HOLD(p_variable,p_alarm);
}
int  CObj__VAT650_TYPE::
Call__AUTO_LEARN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__AUTO_LEARN(p_variable,p_alarm);
}
