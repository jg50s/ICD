#include "StdAfx.h"
#include "CObj__STEP_FNC.h"


// ...
int CObj__STEP_FNC
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


//.....
int CObj__STEP_FNC
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

	// ESC ...
	{
		obj_sts = pOBJ_CTRL__ESC->Get__OBJECT_STATUS();
		if(obj_sts == OBJECT_STATUS__ABORTED)			return -13;
	}

	// FRC1 ...
	{
		obj_sts = pOBJ_CTRL__FRC1->Get__OBJECT_STATUS();
		if(obj_sts == OBJECT_STATUS__ABORTED)			return -14;
	}

	return OBJ_AVAILABLE;
}

// ...
int CObj__STEP_FNC
::Fnc__CHECK_PART_ERROR(CII_OBJECT__VARIABLE *p_variable,
						CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	CString log_bff;
	int i;

	if(sEXT_CH__SYSTEM_INTERLOCK_FLAG->Check__DATA(STR__YES) > 0)
	{
		return -10001;
	}

	// MFCx ...
	{
		for(i=0; i<iOBJ_MFC__SIZE; i++)
		{
			if(dEXT_CH__MFC__ABORT_FLAG[i]->Check__DATA("OFF") < 0)
			{
				// ...
				{
					log_msg.Format("MFC %d Flow Abort Error. Abort Process Step", i+1);
					xLOG_CTRL->WRITE__LOG(log_msg);
				}

				dEXT_CH__MFC__ABORT_FLAG[i]->Set__DATA("OFF");
				return -31;
			}
		}
	}

	// APC ...
	{
		if(dEXT_CH__APC_OBJ__ABORT_FLAG->Check__DATA("OFF") < 0)
		{
			// ...
			{
				log_msg = "APC Valve Abort Flag On.. Abort Process Step";
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			
			dEXT_CH__APC_OBJ__ABORT_FLAG->Set__DATA("OFF");
			return -32;
		}
	}

	// ESC ...
	{
		if(sEXT_CH__ESC__MON_FAULT_FLAG->Check__DATA("ON") > 0)
		{
			// ...
			{
				log_msg = "ESC Abort Flag On. Abort Process Step";
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			return -33;
		}
	}

	// FRC1 ...
	{
		if(sEXT_CH__FRC1__MON_FAULT_FLAG->Check__DATA("ON") > 0)
		{
			// ...
			{
				log_msg = "FRC1 Abort Flag On. Abort Process Step";
				xLOG_CTRL->WRITE__LOG(log_msg);
			}
			return -34;
		}
	}

	// RF Check ...
	{
		// BIAS
		if(dEXT_CH__RF_BIAS__ABORT_FLAG->Check__DATA("OFF") < 0)
		{
			// ...
			{
				log_msg = "RF_BIAS Abort Flag On. Abort Process Step";
				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			dEXT_CH__RF_BIAS__ABORT_FLAG->Set__DATA("OFF");
			return -41;
		}
		// PLASMA
		if(dEXT_CH__RF_PLASMA__ABORT_FLAG->Check__DATA("OFF") < 0)
		{
			// ...
			{
				log_msg = "RF_PLASMA Abort Flag On. Abort Process Step";
				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			dEXT_CH__RF_PLASMA__ABORT_FLAG->Set__DATA("OFF");
			return -42;
		}
	}

	// ESC HEATER ...
	{
		if(dCH__CFG_STEP_ESC_HEATER_FAULT_CHECK->Check__DATA(STR__ENABLE) > 0)
		{
			if((sEXT_CH__ESC_HTR__MON_HEATING_FLAG->Check__DATA(STR__ON) < 0)
			|| (sEXT_CH__ESC_HTR__MON_FAULT_FLAG->Check__DATA(STR__ON)   > 0))
			{
				// ...
				{
					log_msg = "ESC_HEATER : ERROR !\n";

					log_bff.Format("  * %s <- %s \n",
									sEXT_CH__ESC_HTR__MON_HEATING_FLAG->Get__CHANNEL_NAME(),
									sEXT_CH__ESC_HTR__MON_HEATING_FLAG->Get__STRING());
					log_msg += log_bff;

					log_bff.Format("  * %s <- %s \n",
									sEXT_CH__ESC_HTR__MON_FAULT_FLAG->Get__CHANNEL_NAME(),
									sEXT_CH__ESC_HTR__MON_FAULT_FLAG->Get__STRING());
					log_msg += log_bff;

					xLOG_CTRL->WRITE__LOG(log_msg);
				}
				return -51;
			}
		}
	}

	return 1;
}

int CObj__STEP_FNC
::Fnc__INIT_PART_ERROR(CII_OBJECT__VARIABLE *p_variable,
					   CII_OBJECT__ALARM *p_alarm)
{
	int i;

	// MFCx Init ...
	for(i=0; i<iOBJ_MFC__SIZE; i++)
	{
		dEXT_CH__MFC__ABORT_FLAG[i]->Set__DATA("OFF");
	}

	// APC Init ...
	{
		dEXT_CH__APC_OBJ__ABORT_FLAG->Set__DATA("OFF");
	}
	return 1;
}

int CObj__STEP_FNC
::Fnc__CHECK_PART_STABLE(CII_OBJECT__VARIABLE *p_variable,
						 CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	int i;

	// MFC
	for(i=0; i<iOBJ_MFC__SIZE; i++)
	{
		if(dEXT_CH__MFC__CFG_USE_FLAG[i]->Check__DATA(STR__USE) < 0)
		{
			continue;
		}

		if(dEXT_CH__MFC__STABLE_FLAG[i]->Check__DATA("ON") < 0)
		{
			return -11;
		}
	}

	// APC
	if(dEXT_CH__APC_OBJ__STABLE_FLAG->Check__DATA("ON") < 0)
	{
		return -21;
	}

	// ESC
	if(sEXT_CH__ESC__MON_STABLE_FLAG->Check__DATA("ON") < 0)
	{
		return -31;
	}

	// RFx PLASMA
	{
		if(dEXT_CH__RF_PLASMA__STABLE_FLAG->Check__DATA("ON") < 0)
		{
			return -41;
		}
		if(dEXT_CH__RF_BIAS__STABLE_FLAG->Check__DATA("ON") < 0)
		{
			return -42;
		}
	}

	// ESC HEATER ...
	{
		if(dCH__CFG_STEP_ESC_HEATER_STABLE_CHECK->Check__DATA(STR__ENABLE) > 0)
		{
			if((sEXT_CH__ESC_HTR__MON_HEATING_FLAG->Check__DATA(STR__ON) < 0)
			|| (sEXT_CH__ESC_HTR__MON_FAULT_FLAG->Check__DATA(STR__ON)   < 0))
			{
				return -51;
			}
		}
	}
	return 1;
}
int CObj__STEP_FNC
::Get__PART_UNSTABLE_MSG(CString& err_msg)
{
	err_msg = "";

	// ...
	int err_flag = -1;

	CString log_msg;
	int i;

	// MFC
	for(i=0; i<iOBJ_MFC__SIZE; i++)
	{
		if(dEXT_CH__MFC__CFG_USE_FLAG[i]->Check__DATA(STR__USE) < 0)
		{
			continue;
		}

		if(dEXT_CH__MFC__STABLE_FLAG[i]->Check__DATA("ON") < 0)
		{
			log_msg.Format("MFC%1d' flow is not stable. \n", i+1);
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

	// ESC
	if(sEXT_CH__ESC__MON_STABLE_FLAG->Check__DATA("ON") < 0)
	{
		err_msg += "ESC is not stable. \n";

		err_flag = 1;
	}

	// RFx ...
	{
		if(dEXT_CH__RF_PLASMA__STABLE_FLAG->Check__DATA("ON") < 0)
		{
			err_msg += "RF_PLASMA is not stable. \n";

			err_flag = 1;
		}
		if(dEXT_CH__RF_BIAS__STABLE_FLAG->Check__DATA("ON") < 0)
		{
			err_msg += "RF_BIAS is not stable. \n";

			err_flag = 1;
		}
	}

	// ESC HEATER ...
	{
		if(dCH__CFG_STEP_ESC_HEATER_STABLE_CHECK->Check__DATA(STR__ENABLE) > 0)
		{
			if((sEXT_CH__ESC_HTR__MON_HEATING_FLAG->Check__DATA(STR__ON) < 0)
			|| (sEXT_CH__ESC_HTR__MON_FAULT_FLAG->Check__DATA(STR__ON)   < 0))
			{
				err_msg += "ESC Heater is not stable. \n";

				err_flag = 1;
			}
		}
	}

	return err_flag;
}

int CObj__STEP_FNC
::Fnc__IO_INTERLOCK_CHECK(CII_OBJECT__VARIABLE *p_variable,
						  CII_OBJECT__ALARM *p_alarm)
{
	return 1;
}

int CObj__STEP_FNC
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

	if(pOBJ_CTRL__FRC1->Get__OBJECT_STATUS() != OBJECT_STATUS__AVAILABLE)
	{
		part_list += "FRC1 Object";
		part_list += " is not available ! \n";
	}

	if(pOBJ_CTRL__ESC->Get__OBJECT_STATUS() != OBJECT_STATUS__AVAILABLE)
	{
		part_list += "ESC Object";
		part_list += " is not available ! \n";
	}

	//	Object Abort Check .....
	{
		CString bff;
		int i;

		// MFC
		for(i=0; i<iOBJ_MFC__SIZE; i++)
		{
			if(dEXT_CH__MFC__ABORT_FLAG[i]->Check__DATA("OFF") < 0)
			{
				bff.Format("MFC%1d - Abort Flag : Active \n", i+1);
				part_list += bff;
			}
		}

		// APC
		if(dEXT_CH__APC_OBJ__ABORT_FLAG->Check__DATA("OFF") < 0)
		{
			part_list += "APC - Abort Flag : Active \n";
		}

		// FRC1
		if(sEXT_CH__FRC1__MON_FAULT_FLAG->Check__DATA("ON") > 0)
		{
			part_list += "FRC1 - Abort Flag : Active \n";
		}

		// ESC
		if(sEXT_CH__ESC__MON_FAULT_FLAG->Check__DATA("ON") > 0)
		{
			part_list += "ESC - Abort Flag : Active \n";
		}
	}

	// Object Stable Check .....
	{
		CString bff;
		int i;

		// MFC
		for(i=0; i<iOBJ_MFC__SIZE; i++)
		{
			if(dEXT_CH__MFC__STABLE_FLAG[i]->Check__DATA("ON") < 0)
			{
				bff.Format("MFC%1d - Not Stable \n", i+1);
				part_list += bff;
			}
		}

		// APC
		if(dEXT_CH__APC_OBJ__STABLE_FLAG->Check__DATA("ON") < 0)
		{
			part_list += "APC - Not Stable \n";
		}

		// FRC1
		if(sEXT_CH__FRC1__MON_STABLE_FLAG->Check__DATA("ON") < 0)
		{
			part_list += "FRC1 - Not Stable \n";
		}

		// ESC
		if(sEXT_CH__ESC__MON_STABLE_FLAG->Check__DATA("ON") < 0)
		{
			part_list += "ESC - Not Stable \n";
		}
	}

	return 1;
}

int CObj__STEP_FNC
::Fnc__OBJ_Avaliable_Check(const CString& log_id)
{
	if((ALL_MFC_OBJ__Check_AVAILABLE() > 0)
	&& (pOBJ_CTRL__APC->Get__OBJECT_STATUS()  == OBJECT_STATUS__AVAILABLE)
	&& (pOBJ_CTRL__FRC1->Get__OBJECT_STATUS() == OBJECT_STATUS__AVAILABLE)
	&& (pOBJ_CTRL__ESC->Get__OBJECT_STATUS()  == OBJECT_STATUS__AVAILABLE))
	{
		return 100;
	}
	return -100;
}

void CObj__STEP_FNC
::Alarm__POST_CHECK(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id)
{
	CString r_act;
	
	p_alarm->Check__ALARM(alarm_id, r_act);
	p_alarm->Post__ALARM_With_MESSAGE(alarm_id, msg);
}

int CObj__STEP_FNC
::Get__MFC_Interlock_Index(const int cur_index,CUIntArray& l_lock_index)
{
	// ...
	{
		l_lock_index.RemoveAll();

		if(cur_index < 0)					return -1;
		if(cur_index >= iOBJ_MFC__SIZE)		return -1;
	}

	// ...
	CString var_data;
	int i;

	for(i=0;i<CFG_INTERLOCK__MFC_SIZE;i++)
	{
		dCH__CFG_INTERLOCK_MFC_TYPE[cur_index][i]->Get__DATA(var_data);

		int db_index = Get__GAS_Index(var_data);
		if(db_index < 0)		continue;

		l_lock_index.Add(db_index);
	}

	if(l_lock_index.GetSize() < 1)
	{
		return -1;
	}
	return 1;
}
int CObj__STEP_FNC
::Get__GAS_Index(const CString& gas_type)
{
	CString str_name;
	int i;
	
	for(i=0; i<iOBJ_MFC__SIZE; i++)
	{
		str_name.Format("GAS%1d", i+1);
		if(gas_type.CompareNoCase(str_name) != 0)
		{
			continue;
		}
		
		return (i);
	}	
	return -1;
}
