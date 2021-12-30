#include "StdAfx.h"

#include "CObj_Phy__ESC_ZEFA.h"


//-------------------------------------------------------------------------	
int  CObj_Phy__ESC_ZEFA::
Call__ON(CII_OBJECT__VARIABLE*		p_variable,
		 CII_OBJECT__ALARM*			p_alarm)
{
	int	flag = doCH__OUTPUT->Set__DATA(MODE__ON);
	dCH__OUTPUT->Set__DATA(MODE__ON);

	return flag;
}

//-------------------------------------------------------------------------	
int  CObj_Phy__ESC_ZEFA::
Call__OFF(CII_OBJECT__VARIABLE*		p_variable,
		  CII_OBJECT__ALARM*		p_alarm)
{
	int flag = 1;
		
	if (doCH__OUTPUT->Set__DATA(MODE__OFF) < 0) {flag = -1;}
	dCH__OUTPUT->Set__DATA(MODE__OFF);

	if (doCH__TOGGLE->Set__DATA(MODE__OFF) < 0) {flag = -2;}
	dCH__TOGGLE->Set__DATA(MODE__OFF);

	return flag;
}

//-------------------------------------------------------------------------	
int  CObj_Phy__ESC_ZEFA::
Call__TOGGLE(CII_OBJECT__VARIABLE*	p_variable,
			 CII_OBJECT__ALARM*		p_alarm,
			 CString				mode)
{
	int flag = -1;

	if		(mode.CompareNoCase(MODE__ON) == 0)
	{
		flag = doCH__TOGGLE->Set__DATA(MODE__ON);
		dCH__TOGGLE->Set__DATA(MODE__ON);
	}
	else if (mode.CompareNoCase(MODE__OFF) == 0)
	{
		flag = doCH__TOGGLE->Set__DATA(MODE__OFF);
		dCH__TOGGLE->Set__DATA(MODE__OFF);
	}

	return flag;
}

//-------------------------------------------------------------------------	
int  CObj_Phy__ESC_ZEFA::
Call__REMOTE(CII_OBJECT__VARIABLE*		p_variable,
			 CII_OBJECT__ALARM*			p_alarm)
{
	int	flag = doCH__LOCAL_REMOTE->Set__DATA(MODE__REMOTE);

	return flag;
}

//-------------------------------------------------------------------------	
int  CObj_Phy__ESC_ZEFA::
Call__LOCAL(CII_OBJECT__VARIABLE*		p_variable,
			CII_OBJECT__ALARM*			p_alarm)
{
	int	flag = doCH__LOCAL_REMOTE->Set__DATA(MODE__LOCAL);

	return flag;
}

//-------------------------------------------------------------------------	
int  CObj_Phy__ESC_ZEFA::
Call__VOLT_SET(CII_OBJECT__VARIABLE*		p_variable,
				  CII_OBJECT__ALARM*		p_alarm)
{
	int flag = sCH__VOLT_SET_ALL->Set__DATA("set");

	return flag;
}

//-------------------------------------------------------------------------	
int  CObj_Phy__ESC_ZEFA::
Call__CURRLIMIT_SET(CII_OBJECT__VARIABLE*		p_variable,
						CII_OBJECT__ALARM*			p_alarm)
{
	CString ch_data;
	int		flag;

	ch_data = "1";
	flag = soCH__CURRLIMIT_SET->Set__DATA(ch_data);

	return flag;
}

//-------------------------------------------------------------------------	
int  CObj_Phy__ESC_ZEFA::
Call__RAMPUP_SET(CII_OBJECT__VARIABLE*		p_variable,
				 CII_OBJECT__ALARM*			p_alarm)
{
	CString ch_data;

	aCH__RAMPUP_SET->Get__DATA(ch_data);
	int flag = soCH__RAMPUP_SET->Set__DATA(ch_data);

	return flag;
}

//-------------------------------------------------------------------------	
int  CObj_Phy__ESC_ZEFA::
Call__RAMPDN_SET(CII_OBJECT__VARIABLE*		p_variable,
				   CII_OBJECT__ALARM*			p_alarm)
{
	CString ch_data;

	aCH__RAMPDN_SET->Get__DATA(ch_data);
	int flag = soCH__RAMPDN_SET->Set__DATA(ch_data);

	return flag;
}

int  CObj_Phy__ESC_ZEFA::
Call__STATE_READ(CII_OBJECT__VARIABLE*		p_variable,
				 CII_OBJECT__ALARM*			p_alarm)
{
	CString ch_data = "1";

	int flag = soCH__STATE_READ->Set__DATA(ch_data);

	return flag;
}

//-------------------------------------------------------------------------	
//int  CObj_Phy__ESC_ZEFA::
//Call__VOLT_READ(CII_OBJECT__VARIABLE*		p_variable,
//				   CII_OBJECT__ALARM*			p_alarm)
//{
//	CString ch_data;
//
//	int flag = siCH__VOLT_READ->Get__DATA(ch_data);
//	sCH__VOLT_READ->Set__DATA(ch_data);
//	//Write__DRV_LOG("CALL__Voltage_Read");
//
//	return flag;
//}

//-------------------------------------------------------------------------	
//int  CObj_Phy__ESC_ZEFA::
//Call__CURRENT_READ(CII_OBJECT__VARIABLE*		p_variable,
//				   CII_OBJECT__ALARM*			p_alarm)
//{
//	CString log_msg;
//	CString log_bff;
//
//	CString ch_name;
//	CString ch_data;
//
//	int flag = aiCH__CURRENT_READ->Get__DATA(ch_data);
//	aCH__CURRENT_READ->Set__DATA(ch_data);
//	//Write__DRV_LOG("CALL__Current_Read");
//
//	return flag;
//}