#include "StdAfx.h"
#include "CObj__VAT650_TYPE.h"


extern int  Macro__Get_Error_Msg_Of_1K_Type(const int err_id,CString& err_msg);
extern int  Macro__Get_Error_Msg_Of_1M_Type(const int err_id,CString& err_msg);



//--------------------------------------------------------------------------------
void CObj__VAT650_TYPE::
Mon__DRV_ALM(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm)
{
	int err_id;
	CString err_code;
	CString err_msg;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.01);


		while(mRes__ERR_DB.Get__ERR_ID(err_id,err_code) > 0)
		{
			if(dCH__CFG_POS_COUNT_TYPE->Check__DATA(STR__1M_TYPE) > 0)
			{
				Macro__Get_Error_Msg_Of_1M_Type(err_id,err_msg);

			}
			else
			{
				Macro__Get_Error_Msg_Of_1K_Type(err_id,err_msg);
			}

			// ...
			{
				int alarm_id = ALID__APC_COMM_ERROR_CODE;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_bff.Format("Error Code <- [%s]\n", err_code);
				alm_msg  = alm_bff;
				alm_msg += err_msg;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
			}
		}
	}	
}

void CObj__VAT650_TYPE::
Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm)
{

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(iACTIVE_SIM > 0)
		{
			continue;
		}

		if(xCH_diCOMM_STS->Check__DATA(STR__OFFLINE) > 0)
		{
			CString r_act;
			int alarm_id = ALID__APC_OFFLINE_ALARM;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
		}
	}	
}

void CObj__VAT650_TYPE::
Mon__VALUE_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm)
{
	CString var_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.01);


		// Position ...
		{
			xCH__aiVALVE_POS->Get__DATA(var_data);
			sCH__MON_CUR_POSITION_VALUE->Set__DATA(var_data);
		}

		// Pressure ...
		{
			xCH__aiVALVE_PRESS->Get__DATA(var_data);
			sCH__MON_PRESSURE_VALUE->Set__DATA(var_data);
		}
	}	
}
