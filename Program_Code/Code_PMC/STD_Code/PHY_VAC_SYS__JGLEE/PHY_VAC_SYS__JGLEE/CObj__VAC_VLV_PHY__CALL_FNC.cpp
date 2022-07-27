#include "StdAfx.h"
#include "CObj__VAC_VLV_PHY.h"
#include "CObj__VAC_VLV_PHY__ALID.h"


// ...
int CObj__VAC_VLV_PHY
::Call__ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	if(bActive__DO_SR_VALVE_CTRL)
	{
		dEXT_CH__DO_SR_VALVE_CTRL->Set__DATA(STR__CLOSE);
	}

	if(bActive__DO_FR_VALVE)
	{
		dEXT_CH__DO_FR_VALVE_CTRL->Set__DATA(STR__CLOSE);
	}
	else if(bActive__DO_FR_VAT)
	{
		int r_flag = pOBJ_CTRL__DO_FR_VAT->Call__OBJECT(STR__CLOSE);
		if(r_flag < 0)			return -101;
	}

	if(Check__SR_CLOSE_SENSOR_TIMEOUT(p_alarm) < 0)
	{
		return -11;
	}
	if(Check__FR_CLOSE_SENSOR_TIMEOUT(p_alarm) < 0)
	{
		return -12;
	}
	return 1;
}

int CObj__VAC_VLV_PHY
::Call__SR_OPEN(CII_OBJECT__VARIABLE *p_variable,
				CII_OBJECT__ALARM *p_alarm)
{
	if(bActive__DO_FR_VALVE)
	{
		dEXT_CH__DO_FR_VALVE_CTRL->Set__DATA(STR__CLOSE);
	}
	else if(bActive__DO_FR_VAT)
	{
		int r_flag = pOBJ_CTRL__DO_FR_VAT->Call__OBJECT(STR__CLOSE);
		if(r_flag < 0)			return -101;
	}

	if(bActive__DO_SR_VALVE_CTRL)
	{
		if(dEXT_CH__DO_SR_VALVE_CTRL->Set__DATA(STR__OPEN) < 0)
		{
			return -1;
		}
	}

	if(Check__SR_OPEN_SENSOR_TIMEOUT(p_alarm) < 0)
	{
		return -11;
	}
	return 1;
}
int CObj__VAC_VLV_PHY
::Call__SR_CLOSE(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm)
{
	if(bActive__DO_SR_VALVE_CTRL)
	{
		dEXT_CH__DO_SR_VALVE_CTRL->Set__DATA(STR__CLOSE);
	}

	if(Check__SR_CLOSE_SENSOR_TIMEOUT(p_alarm) < 0)
	{
		return -11;
	}
	return 1;
}

int CObj__VAC_VLV_PHY
::Call__FR_OPEN(CII_OBJECT__VARIABLE *p_variable,
				CII_OBJECT__ALARM *p_alarm)
{
	if(bActive__DO_SR_VALVE_CTRL)
	{
		dEXT_CH__DO_SR_VALVE_CTRL->Set__DATA(STR__CLOSE);
	}

	if(bActive__DO_FR_VALVE)
	{
		if(dEXT_CH__DO_FR_VALVE_CTRL->Set__DATA(STR__OPEN) < 0)
		{
			return -1;
		}
	}
	else if(bActive__DO_FR_VAT)
	{
		int r_flag = pOBJ_CTRL__DO_FR_VAT->Call__OBJECT(STR__OPEN);
		if(r_flag < 0)			return -101;
	}

	if(Check__FR_OPEN_SENSOR_TIMEOUT(p_alarm) < 0)
	{
		return -11;
	}
	return 1;
}
int CObj__VAC_VLV_PHY
::Call__FR_CLOSE(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm)
{
	if(bActive__DO_FR_VALVE)
	{
		dEXT_CH__DO_FR_VALVE_CTRL->Set__DATA(STR__CLOSE);
	}
	else if(bActive__DO_FR_VAT)
	{
		int r_flag = pOBJ_CTRL__DO_FR_VAT->Call__OBJECT(STR__CLOSE);
		if(r_flag < 0)			return -101;
	}

	if(Check__FR_CLOSE_SENSOR_TIMEOUT(p_alarm) < 0)
	{
		return -11;
	}
	return 1;
}

int CObj__VAC_VLV_PHY
::Call__EXHAUST_OPEN(CII_OBJECT__VARIABLE *p_variable,
					 CII_OBJECT__ALARM *p_alarm)
{
	if(bActive__DO_EXHAUST_VALVE_CTRL)
	{
		if(dEXT_CH__DO_EXHAUST_VALVE_CTRL->Set__DATA(STR__OPEN) < 0)
			return -1;
	}
	return 1;
}
int CObj__VAC_VLV_PHY
::Call__EXHAUST_CLOSE(CII_OBJECT__VARIABLE *p_variable,
					  CII_OBJECT__ALARM *p_alarm)
{
	if(bActive__DO_EXHAUST_VALVE_CTRL)
	{
		if(dEXT_CH__DO_EXHAUST_VALVE_CTRL->Set__DATA(STR__CLOSE) < 0)
			return -1;
	}
	return 1;
}

// ...
int CObj__VAC_VLV_PHY
::Check__SR_OPEN_SENSOR_TIMEOUT(CII_OBJECT__ALARM* p_alarm)
{
	if(dCH__CFG_USE_SR_OPEN_SNS->Check__DATA(STR__YES) > 0)
	{
		if(bActive__DI_SR_OPEN_SNS)
		{
			double cfg_sec = aCH__CFG_USE_SR_OPEN_TIMEOUT->Get__VALUE();

			int r_flag = dEXT_CH__DI_SR_OPEN_SNS->When__DATA(STR__ON, cfg_sec);
			if(r_flag < 0)
			{
				// Alarm Post ...
				int alm_id = ALID__SR_OPEN_SENSOR_TIMEOUT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format("Config SR Open Timeout <- %.0f sec \n", 
								cfg_sec);

				alm_bff.Format("%s <- %s \n", 
								dEXT_CH__DI_SR_OPEN_SNS->Get__CHANNEL_NAME(),
								dEXT_CH__DI_SR_OPEN_SNS->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				return -1;
			}
		}
		else
		{
			return -11;
		}
	}

	if(dCH__CFG_USE_SR_CLOSE_SNS->Check__DATA(STR__YES) > 0)
	{
		if(bActive__DI_SR_CLOSE_SNS)
		{
			double cfg_sec = aCH__CFG_USE_SR_OPEN_TIMEOUT->Get__VALUE();

			int r_flag = dEXT_CH__DI_SR_CLOSE_SNS->When__DATA(STR__OFF, cfg_sec);
			if(r_flag < 0)
			{
				// Alarm Post ...
				int alm_id = ALID__SR_OPEN_SENSOR_TIMEOUT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format("Config SR Open Timeout <- %.0f sec \n", 
								cfg_sec);

				alm_bff.Format("%s <- %s \n", 
								dEXT_CH__DI_SR_CLOSE_SNS->Get__CHANNEL_NAME(),
								dEXT_CH__DI_SR_CLOSE_SNS->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				return -1;
			}
		}
		else
		{
			return -11;
		}
	}

	return 1;
}
int CObj__VAC_VLV_PHY
::Check__FR_OPEN_SENSOR_TIMEOUT(CII_OBJECT__ALARM* p_alarm)
{
	if(dCH__CFG_USE_FR_OPEN_SNS->Check__DATA(STR__YES) > 0)
	{
		if(bActive__DI_FR_OPEN_SNS)
		{
			double cfg_sec = aCH__CFG_USE_FR_OPEN_TIMEOUT->Get__VALUE();

			int r_flag = dEXT_CH__DI_FR_OPEN_SNS->When__DATA(STR__ON, cfg_sec);
			if(r_flag < 0)
			{
				// Alarm Post ...
				int alm_id = ALID__FR_OPEN_SENSOR_TIMEOUT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format("Config FR Open Timeout <- %.0f sec \n", 
								cfg_sec);

				alm_bff.Format("%s <- %s \n", 
								dEXT_CH__DI_FR_OPEN_SNS->Get__CHANNEL_NAME(),
								dEXT_CH__DI_FR_OPEN_SNS->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				return -1;
			}	
		}
		else
		{
			return -11;
		}
	}

	if(dCH__CFG_USE_FR_CLOSE_SNS->Check__DATA(STR__YES) > 0)
	{
		if(bActive__DI_FR_CLOSE_SNS)
		{
			double cfg_sec = aCH__CFG_USE_FR_OPEN_TIMEOUT->Get__VALUE();

			int r_flag = dEXT_CH__DI_FR_CLOSE_SNS->When__DATA(STR__OFF, cfg_sec);
			if(r_flag < 0)
			{
				// Alarm Post ...
				int alm_id = ALID__FR_OPEN_SENSOR_TIMEOUT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format("Config FR Open Timeout <- %.0f sec \n", 
					cfg_sec);

				alm_bff.Format("%s <- %s \n", 
								dEXT_CH__DI_FR_CLOSE_SNS->Get__CHANNEL_NAME(),
								dEXT_CH__DI_FR_CLOSE_SNS->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				return -2;
			}	
		}
		else
		{
			return -21;
		}
	}

	return 1;
}

int CObj__VAC_VLV_PHY
::Check__SR_CLOSE_SENSOR_TIMEOUT(CII_OBJECT__ALARM* p_alarm)
{
	if(dCH__CFG_USE_SR_OPEN_SNS->Check__DATA(STR__YES) > 0)
	{
		if(bActive__DI_SR_OPEN_SNS)
		{
			double cfg_sec = aCH__CFG_USE_SR_CLOSE_TIMEOUT->Get__VALUE();

			int r_flag = dEXT_CH__DI_SR_OPEN_SNS->When__DATA(STR__OFF, cfg_sec);
			if(r_flag < 0)
			{
				// Alarm Post ...
				int alm_id = ALID__SR_CLOSE_SENSOR_TIMEOUT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format("Config SR Close Timeout <- %.0f sec \n", 
								cfg_sec);

				alm_bff.Format("%s <- %s \n", 
								dEXT_CH__DI_SR_OPEN_SNS->Get__CHANNEL_NAME(),
								dEXT_CH__DI_SR_OPEN_SNS->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				return -1;
			}
		}
		else
		{
			return -11;
		}
	}

	if(dCH__CFG_USE_SR_CLOSE_SNS->Check__DATA(STR__YES) > 0)
	{
		if(bActive__DI_SR_CLOSE_SNS)
		{
			double cfg_sec = aCH__CFG_USE_SR_CLOSE_TIMEOUT->Get__VALUE();

			int r_flag = dEXT_CH__DI_SR_CLOSE_SNS->When__DATA(STR__ON, cfg_sec);
			if(r_flag < 0)
			{
				// Alarm Post ...
				int alm_id = ALID__SR_CLOSE_SENSOR_TIMEOUT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format("Config SR Close Timeout <- %.0f sec \n", 
								cfg_sec);

				alm_bff.Format("%s <- %s \n", 
								dEXT_CH__DI_SR_CLOSE_SNS->Get__CHANNEL_NAME(),
								dEXT_CH__DI_SR_CLOSE_SNS->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				return -2;
			}
		}
		else
		{
			return -21;
		}
	}

	return 1;
}
int CObj__VAC_VLV_PHY
::Check__FR_CLOSE_SENSOR_TIMEOUT(CII_OBJECT__ALARM* p_alarm)
{
	if(dCH__CFG_USE_FR_OPEN_SNS->Check__DATA(STR__YES) > 0)
	{
		if(bActive__DI_FR_OPEN_SNS)
		{
			double cfg_sec = aCH__CFG_USE_FR_OPEN_TIMEOUT->Get__VALUE();

			int r_flag = dEXT_CH__DI_FR_OPEN_SNS->When__DATA(STR__OFF, cfg_sec);
			if(r_flag < 0)
			{
				// Alarm Post ...
				int alm_id = ALID__FR_CLOSE_SENSOR_TIMEOUT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format("Config FR Open Timeout <- %.0f sec \n", 
								cfg_sec);

				alm_bff.Format("%s <- %s \n", 
								dEXT_CH__DI_FR_OPEN_SNS->Get__CHANNEL_NAME(),
								dEXT_CH__DI_FR_OPEN_SNS->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				return -1;
			}
		}
		else
		{
			return -11;
		}
	}

	if(dCH__CFG_USE_FR_CLOSE_SNS->Check__DATA(STR__YES) > 0)
	{
		if(bActive__DI_FR_CLOSE_SNS)
		{
			double cfg_sec = aCH__CFG_USE_FR_CLOSE_TIMEOUT->Get__VALUE();

			int r_flag = dEXT_CH__DI_FR_CLOSE_SNS->When__DATA(STR__ON, cfg_sec);
			if(r_flag < 0)
			{
				// Alarm Post ...
				int alm_id = ALID__FR_CLOSE_SENSOR_TIMEOUT;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format("Config FR Close Timeout <- %.0f sec \n", 
								cfg_sec);

				alm_bff.Format("%s <- %s \n", 
								dEXT_CH__DI_FR_CLOSE_SNS->Get__CHANNEL_NAME(),
								dEXT_CH__DI_FR_CLOSE_SNS->Get__STRING());
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
				return -1;
			}
		}
		else
		{
			return -11;
		}
	}

	return 1;
}
