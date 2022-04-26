#include "StdAfx.h"
#include "CObj_NET__ALx_SR100.h"
#include "CObj_NET__ALx_SR100__DEF.h"
#include "CObj_NET__ALx_SR100__ALID.h"

#include "Macro_Function.h"


//-------------------------------------------------------------------------	
int  CObj_NET__ALx_SR100
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	doCH__AL_CMMD->Set__DATA(_CMMD__ALErrClr);

	return 1;
}

int  CObj_NET__ALx_SR100
::Call__ALIGN(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM* p_alarm)
{
LOOP_RETRY:

	CString str__ccd_pos;
	aCH__PARA_CCD_POS->Get__DATA(str__ccd_pos);

	int drv_check = 1;

	if(iSim_Flag > 0)
	{
		Sleep(1000);
	}
	else
	{
		dPARA__TRG_ANGLE = atof(str__ccd_pos);	
		drv_check = doCH__AL_CMMD->Set__DATA(_CMMD__Align);
		
		if(drv_check > 0)		
		{
			drv_check = doCH__AL_CMMD->Set__DATA(_CMMD__VacOff);
		}
	}

	// ...
	{
		int r_flag = Fnc__ONLINE_CHECK(p_alarm,1);

			 if(r_flag == 0)			goto LOOP_RETRY;
		else if(r_flag  < 0)			return -11;	
	}

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -12;
	}
	if(drv_check < 0)				
	{
		return -13;
	}
	return 1;
}

int  CObj_NET__ALx_SR100
::Call__VAC_ON(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM* p_alarm)
{
	doCH__AL_CMMD->Set__DATA(_CMMD__VacOn);
	return 1;
}
int  CObj_NET__ALx_SR100
::Call__VAC_OFF(CII_OBJECT__VARIABLE* p_variable,
			    CII_OBJECT__ALARM* p_alarm)
{
	doCH__AL_CMMD->Set__DATA(_CMMD__VacOff);
	return 1;
}


// ...
int  CObj_NET__ALx_SR100
::Call__CHECK_ERROR_CODE(CII_OBJECT__VARIABLE* p_variable,
						 CII_OBJECT__ALARM* p_alarm)
{
LOOP_RETRY:

	mMNG__ERR_CODE.Clear__Error_Code();

	CString err_code = sCH__ERROR_TEST__ERROR_CODE->Get__STRING();
	_Check__ERROR_CODE(err_code);

	// ...
	CString err_msg;

	while(mMNG__ERR_CODE.Get__Error_Code(err_code,err_msg) > 0)
	{
		int i_error = atoi(err_code);
		if(i_error == 0)		continue;

		// ...
		int alm_id = ALID__ERROR_CODE;
		CString alm_msg;
		CString alm_bff;
		CString r_act;

		alm_msg.Format("Control_Mode : %s \n", "Call__CHECK_ERROR_CODE()");

		alm_bff.Format("Error_Code : %s \n", err_code);
		alm_msg += alm_bff;
		alm_bff.Format("Error_Message \n");
		alm_msg += alm_bff;
		alm_msg += "  * ";
		alm_msg += err_msg;

		// ...
		{
			CString log_msg;

			log_msg.Format("Alarm Post : %1d \n", alm_id);
			log_msg += alm_msg;

			Fnc__APP_LOG(log_msg);
		}

		p_alarm->Popup__ALARM_With_MESSAGE(alm_id,alm_msg,r_act);			

		if(r_act.CompareNoCase(ACT__RETRY) == 0)
		{
			CString log_msg = "Alarm Selection <- Retry";
			Fnc__APP_LOG(log_msg);

			goto LOOP_RETRY;
		}
		if(r_act.CompareNoCase(ACT__ABORT) == 0)
		{
			return -1;
		}

		if(r_act.CompareNoCase(ACT__IGNORE) == 0)
		{
			// ...
		}
	}

	return 1;
}

