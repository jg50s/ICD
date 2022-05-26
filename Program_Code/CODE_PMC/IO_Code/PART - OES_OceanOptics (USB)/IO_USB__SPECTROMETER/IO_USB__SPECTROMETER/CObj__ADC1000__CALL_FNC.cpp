#include "StdAfx.h"
#include "CObj__ADC1000.h"



//-------------------------------------------------------------------------	
int CObj__ADC1000
::Call__INIT(CII_OBJECT__VARIABLE *p_variable,
			 CII_OBJECT__ALARM *p_alarm)
{
	int nRet;
	CString str_log;

	xLOG_CTRL->WRITE__LOG("Call__INIT... Start..");

	if(diCH__COMM_STS->Check__DATA("Online") < 0)
	{
		xLOG_CTRL->WRITE__LOG("Not Online.. Alarm Occur");

		Alarm__CHECK__POST(p_alarm, ALID__OFFLINE_ALARM);		
		return OBJ_ABORT;
	}

	xLOG_CTRL->WRITE__LOG("Parameter Command Set...");

	// OES Spectrometer CCD Setting Parameter (Not Link) ...
	nRet = doCH__SET_COEFFICIENT->Set__DATA("Set");
	if(nRet < 0)	
	{
		str_log.Format("Fail...Ret %d", nRet);
		xLOG_CTRL->WRITE__LOG(str_log);

		// Alarm Occur !!;
		Alarm__CHECK__POST(p_alarm, ALID__INIT_CMD_ERROR_ALARM);		
		return OBJ_ABORT;
	}

	// Dark Check ...
	if(dCH__CFG_ZERO_CAL_USE->Check__DATA(STR__YES) > 0)
	{
		CString var_data;
		sCH__Gui_Cal_Value->Get__DATA(var_data);

		if(atof(var_data) < 0.1)
		{
			nRet = Call__DARK(p_variable, p_alarm);

			if(nRet < 0)
			{
				str_log.Format("Fail...Call Dark : Return %d", nRet);
				xLOG_CTRL->WRITE__LOG(str_log);
			}
		}
	}

	// ...
	{
		str_log.Format("Success...Ret %d", nRet);
		xLOG_CTRL->WRITE__LOG(str_log);

		xLOG_CTRL->WRITE__LOG("Call__INIT... Complete..");
	}
	return nRet;
}

int CObj__ADC1000
::Call__DARK(CII_OBJECT__VARIABLE *p_variable,
			 CII_OBJECT__ALARM *p_alarm)
{
	int nRet = 0;
	CString str_log;
	CString str_sData;

	// ...
	xLOG_CTRL->WRITE__LOG("Call__DARK... Start..");

	if(diCH__COMM_STS->Check__DATA("Online") < 0)
	{
		xLOG_CTRL->WRITE__LOG("Not Online.. Alarm Occur");

		Alarm__CHECK__POST(p_alarm, ALID__OFFLINE_ALARM);		
		return OBJ_ABORT;
	}

	// ...
	{
		doCH__SET_Dark->Set__DATA(STR__Disable);

		Sleep(2000);
	}

	// Spectrum Value ...
	{
		aiCH__Spectrum[1]->Get__DATA(str_sData);
		sCH__Gui_Cal_Value->Set__DATA(str_sData);
	}

	// ...
	{
		doCH__SET_Dark->Set__DATA(STR__Enable);

		if(iACTIVE_SIM > 0)
		{
			diCH__Get_Dark->Set__DATA(STR__Enable);
		}

		// ...
		diCH__Get_Dark->Link__UPPER_OBJECT_ABORT(sObject_Name);
		diCH__Get_Dark->Enable__UPPER_OBJECT_ABORT_CHECK();

		nRet = diCH__Get_Dark->When__DATA(STR__Enable, 3.0);

		if(nRet < 0)
		{
			str_log.Format("Failed... DRAK Ret %d", nRet);
			xLOG_CTRL->WRITE__LOG(str_log);
		}		
	}

	// ...
	{
		str_log.Format("Success...Ret %d", nRet);
		xLOG_CTRL->WRITE__LOG(str_log);

		xLOG_CTRL->WRITE__LOG("Call__DARK... Complete..");
	}
	return nRet;
}
