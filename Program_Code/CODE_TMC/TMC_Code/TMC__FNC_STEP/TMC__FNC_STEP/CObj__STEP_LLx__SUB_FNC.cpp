#include "StdAfx.h"
#include "CObj__STEP_LLx.h"


//------------------------------------------------------------------------------
int CObj__STEP_LLx
::Check__STEP_CONTROL()
{
	CString log_msg;

	SCX__TIMER_CTRL time_ctrl;
	time_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);

	if(sCH__EXCEPTION_COMMAND->Check__DATA("PAUSE") > 0)
	{
		// ...
		{
			log_msg = "Received Process Paused. Wait Process Resume or Process Abort";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		while(1)
		{
			if(sCH__EXCEPTION_COMMAND->Check__DATA("RESUME") > 0)
			{
				// ...
				{
					log_msg = "Received Process Resume.";
					xLOG_CTRL->WRITE__LOG(log_msg);
				}
				return OBJ_AVAILABLE ;
			}
			if(sCH__EXCEPTION_COMMAND->Check__DATA("SKIP") > 0)
			{
				// ...
				{
					log_msg = "Receive Process Step Skip Command";
					xLOG_CTRL->WRITE__LOG(log_msg);
				}
				return OBJ_ABORT;
			}

			if(time_ctrl->WAIT(0.1) < 0)
			{
				return OBJ_ABORT;
			}
		}
	}
	else if(sCH__EXCEPTION_COMMAND->Check__DATA("SKIP") > 0)
	{
		// ...
		{
			log_msg = "Receive Process Step Skip Command";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
		return OBJ_ABORT;
	}
	else
	{
		return OBJ_AVAILABLE;
	}

	return OBJ_AVAILABLE;
}

int CObj__STEP_LLx
::Fnc__OBJ_Abort_Check(const CString& log_id, const int mfc_check)
{
	int obj_sts;

	if(mfc_check > 0)
	{
		if(ANY_MFC_OBJ__Check_ABORTED() > 0)
		{
			return -11;
		}
	}

	// APC ...
	{
		if(APC_OBJ__Status_MODE(log_id) == OBJECT_STATUS__ABORTED)
		{
			return -12;
		}
	}

	return OBJ_AVAILABLE;
}

int CObj__STEP_LLx
::Fnc__CHECK_PART_ERROR(CII_OBJECT__VARIABLE *p_variable,
						CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	CString log_bff;

	// MFC_N2 ...
	{
		if(dEXT_CH__MFC_N2__ABORT_FLAG->Check__DATA("OFF") < 0)
		{
			log_msg = "MFC_N2 Flow Abort Error. Abort Process Step";
			xLOG_CTRL->WRITE__LOG(log_msg);

			dEXT_CH__MFC_N2__ABORT_FLAG->Set__DATA("OFF");
			return -31;
		}
	}

	// APC ...
	if(dEXT_CH__APC_OBJ__ABORT_FLAG->Check__DATA("OFF") < 0)
	{
		log_msg = "APC Valve Abort Flag On.. Abort Process Step";
		xLOG_CTRL->WRITE__LOG(log_msg);
		
		dEXT_CH__APC_OBJ__ABORT_FLAG->Set__DATA("OFF");
		return -32;
	}

	return 1;
}

int CObj__STEP_LLx
::Fnc__INIT_PART_ERROR(CII_OBJECT__VARIABLE *p_variable,
					   CII_OBJECT__ALARM *p_alarm)
{
	// MFC Init ...
	dEXT_CH__MFC_N2__ABORT_FLAG->Set__DATA("OFF");

	// APC Init ...
	dEXT_CH__APC_OBJ__ABORT_FLAG->Set__DATA("OFF");

	return 1;
}

int CObj__STEP_LLx
::Fnc__CHECK_PART_STABLE(CII_OBJECT__VARIABLE *p_variable,
						 CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;

	// MFC_N2 ...
	if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
	{
		if(dEXT_CH__MFC_N2__STABLE_FLAG->Check__DATA("ON") < 0)
		{
			return -11;
		}
	}

	// APC
	if(dEXT_CH__APC_OBJ__STABLE_FLAG->Check__DATA("ON") < 0)
	{
		return -21;
	}
	return 1;
}
int CObj__STEP_LLx
::Get__PART_UNSTABLE_MSG(CString& err_msg)
{
	err_msg = "";

	// ...
	int err_flag = -1;

	CString log_msg;

	// MFC_N2 ...
	if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
	{
		if(dEXT_CH__MFC_N2__STABLE_FLAG->Check__DATA("ON") < 0)
		{
			log_msg = "MFC_N2' flow is not stable. \n";
			err_msg += log_msg;

			err_flag = 1;
		}
	}

	// APC
	if(dEXT_CH__APC_OBJ__STABLE_FLAG->Check__DATA("ON") < 0)
	{
		err_msg += "APC is not stable. \n";	

		err_flag = 1;
	}

	return err_flag;
}

int CObj__STEP_LLx
::Fnc__Get_OBJ_Not_Available_List(CString& part_list)
{
	part_list = "";

	// ...
	CString log_id = "Object Not Available Check : ";

	if(ALL_MFC_OBJ__Check_AVAILABLE() < 0)
	{
		part_list += "ALL MFC Object";
		part_list += " is not available ! \n";
	}
	
	if(APC_OBJ__Status_MODE(log_id)	!= OBJECT_STATUS__AVAILABLE)
	{
		part_list += "APC Object";
		part_list += " is not available ! \n";
	}
	
	//	Object Abort Check .....
	{
		CString bff;

		// MFC_N2 ...
		if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
		{
			if(dEXT_CH__MFC_N2__ABORT_FLAG->Check__DATA("OFF") < 0)
			{
				bff = "MFC_N2 - Abort Flag : Active \n";
				part_list += bff;
			}
		}

		// APC ...
		if(dEXT_CH__APC_OBJ__ABORT_FLAG->Check__DATA("OFF") < 0)
		{
			part_list += "APC - Abort Flag : Active \n";
		}
	}

	// Object Stable Check .....
	{
		CString bff;

		// MFC_N2 ...
		if(dEXT_CH__MFC_N2__CFG_USE_FLAG->Check__DATA(STR__USE) > 0)
		{
			if(dEXT_CH__MFC_N2__STABLE_FLAG->Check__DATA("ON") < 0)
			{
				bff = "MFC_N2 - Not Stable \n";
				part_list += bff;
			}
		}

		// APC
		if(dEXT_CH__APC_OBJ__STABLE_FLAG->Check__DATA("ON") < 0)
		{
			part_list += "APC - Not Stable \n";
		}
	}

	return 1;
}

int CObj__STEP_LLx
::Fnc__OBJ_Avaliable_Check(const CString& log_id)
{
	if((ALL_MFC_OBJ__Check_AVAILABLE() > 0)
	&& (pOBJ_CTRL__APC->Get__OBJECT_STATUS()  == OBJECT_STATUS__AVAILABLE))
	{
		// Fnc__WRITE_LOG("Chamber Stable Complete.");
		return 100;
	}
	return -100;
}

void CObj__STEP_LLx
::Alarm__POST_CHECK(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id)
{
	CString r_act;
	
	p_alarm->Check__ALARM(alarm_id, r_act);
	p_alarm->Post__ALARM_With_MESSAGE(alarm_id, msg);
}

