#include "StdAfx.h"
#include "CObj__VIRTUAL_TYPE.h"


//-------------------------------------------------------------------------	
int  CObj__VIRTUAL_TYPE::
Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return 1;
}

int  CObj__VIRTUAL_TYPE::
Call__MULTI_PAGE_READ(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return 1;
}
int  CObj__VIRTUAL_TYPE::
Call__PAGE_READ(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return 1;
}

int  CObj__VIRTUAL_TYPE::
Call__MULTI_PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return 1;
}
int  CObj__VIRTUAL_TYPE::
Call__PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return 1;
}


int  CObj__VIRTUAL_TYPE::
Call__MID_WRITE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return 1;
}
int  CObj__VIRTUAL_TYPE::
Call__MID_READ(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return 1;
}


// ...
void CObj__VIRTUAL_TYPE
::Fnc__LOG(const char *fmt, ...)
{
	if(iFlag_Log < 1)		return;

	CString str_msg;
	va_list args;

	va_start(args, fmt);
	str_msg.FormatV(fmt, args);
	va_end(args);

	xLOG_CTRL->WRITE__LOG(str_msg);
}

void CObj__VIRTUAL_TYPE
::Fnc__MSG(const CString& log_msg)
{
	sCH__MSG->Set__DATA(log_msg);
}
