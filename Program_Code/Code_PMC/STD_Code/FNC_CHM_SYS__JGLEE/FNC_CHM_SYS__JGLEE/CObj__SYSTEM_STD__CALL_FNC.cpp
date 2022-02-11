#include "StdAfx.h"
#include "CObj__SYSTEM_STD.h"


// ...
int CObj__SYSTEM_STD
::Call__SYSTEM_INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int r_flag = Fnc__SYSTEM_INIT(p_variable, p_alarm);

	// ...
	{
		int i;

		// RF_SYS ...
		{
			// RF_GEN ...
			for(i=0; i<iRF_SYS__GEN_SIZE; i++)
			{
				sCH__LINK_OBJ_ACTIVE__RF_GEN_X[i]->Set__DATA("");
			}

			// RF_MAT ...
			for(i=0; i<iRF_SYS__MAT_SIZE; i++)
			{
				sCH__LINK_OBJ_ACTIVE__RF_MAT_X[i]->Set__DATA("");
			}

			// ESC_DC_SUPPLY ...
			{
				sCH__LINK_OBJ_ACTIVE__ESC_DC_SUPPLY->Set__DATA("");
			}

			// ESC_BACK_HE ...
			{
				sCH__LINK_OBJ_ACTIVE__ESC_BACK_HE->Set__DATA("");
			}
		}

		// HTR_SYS ...
		{
			for(i=0; i<iHTR_SYS__PART_SIZE; i++)
			{
				sCH__LINK_OBJ_ACTIVE__HEATER_X[i]->Set__DATA("");
			}
		}

		// CHAMBER ...
		{
			sCH__LINK_OBJ_ACTIVE_CHM_LIFT_PIN_DOWN->Set__DATA("");
			sCH__LINK_OBJ_ACTIVE_CHM_DECHUCK->Set__DATA("");
		}
	}

	return r_flag;
}
int CObj__SYSTEM_STD
::Fnc__SYSTEM_INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	SCX__TIMER_CTRL x_timer_ctrl;

	x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
	x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH__OBJ_TIMER->Get__CHANNEL_NAME());

	// ...
	CString log_msg;
	CString log_bff;
	int i;

	// LINK_OBJ ...
	for(i=0; i<iOBJ_SIZE; i++)
	{
		CString obj_name = sList__OBJ_NAME[i];

		// ...
		{
			log_msg.Format("%s Init : Started ...", obj_name);
			sEXT_CH__FNC_MSG->Set__DATA(log_msg);

			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		int retVal = pOBJ_CTRL__LIST[i]->Call__OBJECT(CMMD_INIT);
		if(retVal < 0)
		{
			// ...
			{
				log_msg.Format("%s Init : Aborted ...", obj_name);
				sEXT_CH__FNC_MSG->Set__DATA(log_msg);
			}

			CString str_msg;
			str_msg.Format("OBJECT [%s] INIT Failed [%d] Object : Result [%d] ", obj_name[i], i, retVal);

			int alarm_id = ALID__SYSTEM_INIT_ALARM;
			Alarm__POST_CHECK(p_alarm, str_msg, alarm_id);

			xLOG_CTRL->WRITE__LOG(str_msg);
			return retVal;
		}

		// INIT Complete Check ...
		{
			log_msg.Format("OBJECT [%s] INIT Complete [%d] Object : Result [%d] ", obj_name, i, retVal);

			xLOG_CTRL->WRITE__LOG(log_msg);
		}

		// ...
		{
			log_msg.Format("%s Init : Completed ...", obj_name);
			sEXT_CH__FNC_MSG->Set__DATA(log_msg);
		}
	}

	// RF_SYS ...
	{
		CString obj_msg;

		// RF_GEN ...
		for(i=0; i<iRF_SYS__GEN_SIZE; i++)
		{
			if(dCH__CFG_SYS_INIT__RF_GEN_X[i]->Check__DATA(STR__ENABLE) < 0)
			{
				continue;
			}

			CString obj_name = sCH__LINK_OBJ_NAME__RF_GEN_X[i]->Get__STRING();

			// ...
			{
				log_msg  = "\n";
				log_bff.Format("%s started ...", obj_name);
				log_msg += log_bff;
				log_msg += "\n";

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			// ...
			{
				sCH__LINK_OBJ_ACTIVE__RF_GEN_X[i]->Set__DATA(STR__YES);

				obj_msg.Format("%s started ...", obj_name);
				sEXT_CH__FNC_MSG->Set__DATA(obj_msg);

				if(pOBJ_CTRL__RF_SYS__GEN_X[i]->Call__OBJECT(CMMD_INIT) < 0)
				{
					obj_msg.Format("%s aborted ...", obj_name);
					sEXT_CH__FNC_MSG->Set__DATA(obj_msg);
					return -101;
				}

				double cfg_sec = aCH__CFG_PART_STABLE_SEC->Get__VALUE();
				if(x_timer_ctrl->WAIT(cfg_sec) < 0)		return -(11 + i);

				obj_msg.Format("%s completed ...", obj_name);
				sEXT_CH__FNC_MSG->Set__DATA(obj_msg);

				sCH__LINK_OBJ_ACTIVE__RF_GEN_X[i]->Set__DATA("");
			}
		}

		// RF_MAT ...
		for(i=0; i<iRF_SYS__MAT_SIZE; i++)
		{
			if(dCH__CFG_SYS_INIT__RF_MAT_X[i]->Check__DATA(STR__ENABLE) < 0)
			{
				continue;
			}

			CString obj_name = sCH__LINK_OBJ_NAME__RF_MAT_X[i]->Get__STRING();

			// ...
			{
				log_msg  = "\n";
				log_bff.Format("%s started ...", obj_name);
				log_msg += log_bff;
				log_msg += "\n";

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			// ...
			{
				sCH__LINK_OBJ_ACTIVE__RF_MAT_X[i]->Set__DATA(STR__YES);

				obj_msg.Format("%s started ...", obj_name);
				sEXT_CH__FNC_MSG->Set__DATA(obj_msg);

				if(pOBJ_CTRL__RF_SYS__MAT_X[i]->Call__OBJECT(CMMD_INIT) < 0)
				{
					obj_msg.Format("%s aborted ...", obj_name);
					sEXT_CH__FNC_MSG->Set__DATA(obj_msg);
					return -111;
				}

				double cfg_sec = aCH__CFG_PART_STABLE_SEC->Get__VALUE();
				if(x_timer_ctrl->WAIT(cfg_sec) < 0)		return -(21 + i);

				obj_msg.Format("%s completed ...", obj_name);
				sEXT_CH__FNC_MSG->Set__DATA(obj_msg);

				sCH__LINK_OBJ_ACTIVE__RF_MAT_X[i]->Set__DATA("");
			}
		}

		// ESC_DC_SUPPLY ...
		if((dCH__CFG_SYS_INIT__ESC_DC_SUPPLY->Check__DATA(STR__ENABLE) > 0)
		&& (bACTIVE_RF_SYS__ESC_DC_SUPPLY))
		{
			CString obj_name = "ESC_DC_SUPPLY";

			// Started ...
			{
				sCH__LINK_OBJ_ACTIVE__ESC_DC_SUPPLY->Set__DATA(STR__YES);

				obj_msg.Format("%s started ...", obj_name);
				sEXT_CH__FNC_MSG->Set__DATA(obj_msg);
			}

			if(pOBJ_CTRL__RF_SYS_ESC_DC_SUPPLY->Call__OBJECT(CMMD_INIT) < 0)
			{
				obj_msg.Format("%s aborted ...", obj_name);
				sEXT_CH__FNC_MSG->Set__DATA(obj_msg);
				return -121;
			}

			double cfg_sec = aCH__CFG_PART_STABLE_SEC->Get__VALUE();
			if(x_timer_ctrl->WAIT(cfg_sec) < 0)		return -(31);

			// Completed ...
			{
				sCH__LINK_OBJ_ACTIVE__ESC_DC_SUPPLY->Set__DATA("");

				obj_msg.Format("%s completed ...", obj_name);
				sEXT_CH__FNC_MSG->Set__DATA(obj_msg);
			}
		}

		// ESC_BACK_HE ...
		if(dCH__CFG_SYS_INIT__ESC_BACK_HE->Check__DATA(STR__ENABLE) > 0)
		{
			if(bACTIVE_RF_SYS__ESC_BACK_HE)
			{
				CString obj_name = "ESC_BACK_HE";

				// Started ...
				{
					sCH__LINK_OBJ_ACTIVE__ESC_BACK_HE->Set__DATA(STR__YES);

					obj_msg.Format("%s started ...", obj_name);
					sEXT_CH__FNC_MSG->Set__DATA(obj_msg);
				}

				if(pOBJ_CTRL__RF_SYS_ESC_BACK_HE->Call__OBJECT(CMMD_INIT) < 0)
				{
					obj_msg.Format("%s aborted ...", obj_name);
					sEXT_CH__FNC_MSG->Set__DATA(obj_msg);
					return -121;
				}

				double cfg_sec = aCH__CFG_PART_STABLE_SEC->Get__VALUE();
				if(x_timer_ctrl->WAIT(cfg_sec) < 0)		return -(41);

				// Completed ...
				{
					sCH__LINK_OBJ_ACTIVE__ESC_BACK_HE->Set__DATA("");

					obj_msg.Format("%s completed ...", obj_name);
					sEXT_CH__FNC_MSG->Set__DATA(obj_msg);
				}
			}
		}
	}

	// HEATER_SYS ...
	{
		int active__htr_count = 0;

		// HEATER.START ...
		{
			for(i=0; i<iHTR_SYS__PART_SIZE; i++)
			{
				if(dCH__CFG_SYS_INIT__HEATER_X[i]->Check__DATA(STR__ENABLE) < 0)
				{
					continue;
				}

				CString obj_name = sCH__LINK_OBJ_NAME__HEATER_X[i]->Get__STRING();
				CString obj_msg;

				// ...
				{
					log_msg  = "\n";

					log_bff.Format("%s started ...", obj_name);
					log_msg += log_bff;
					log_msg += "\n";

					xLOG_CTRL->WRITE__LOG(log_msg);
				}

				// ...
				{
					sCH__LINK_OBJ_ACTIVE__HEATER_X[i]->Set__DATA(STR__YES);

					obj_msg.Format("%s started ...", obj_name);
					sEXT_CH__FNC_MSG->Set__DATA(obj_msg);

					if(pOBJ_CTRL__HTR_SYS__PART_X[i]->Run__OBJECT(CMMD_INIT) < 0)
					{
						obj_msg.Format("%s aborted ...", obj_name);
						sEXT_CH__FNC_MSG->Set__DATA(obj_msg);
						return -111;
					}
				}

				active__htr_count++;
			}
		}

		// HEATER.END ...
		while(1)
		{
			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -121;
			}

			bool active__htr_obj = false;

			for(i=0; i<iHTR_SYS__PART_SIZE; i++)
			{
				if(dCH__CFG_SYS_INIT__HEATER_X[i]->Check__DATA(STR__ENABLE) < 0)
				{
					continue;
				}

				if(pOBJ_CTRL__HTR_SYS__PART_X[i]->Is__OBJ_BUSY() > 0)
				{
					active__htr_obj = true;
					continue;
				}

				// ...
				{
					CString obj_name = sCH__LINK_OBJ_NAME__HEATER_X[i]->Get__STRING();
					CString obj_msg;

					obj_msg.Format("%s completed ...", obj_name);
					sEXT_CH__FNC_MSG->Set__DATA(obj_msg);

					sCH__LINK_OBJ_ACTIVE__HEATER_X[i]->Set__DATA("");
				}
			}

			if(!active__htr_obj)
			{
				if(active__htr_count > 0)
				{
					double cfg_sec = aCH__CFG_PART_STABLE_SEC->Get__VALUE();
					if(x_timer_ctrl->WAIT(cfg_sec) < 0)		return -(131 + i);
				}
				break;
			}
		}
	}

	// CHAMBER ...
	{
		CString obj_msg;

		if(dCH__CFG_SYS_INIT_CHM_LIFT_PIN_DOWN->Check__DATA(STR__ENABLE) > 0)
		{
			// ...
			{
				log_msg  = "\n";
				log_msg += "CHMABER.LIFT_PIN-DOWN Started ...";
				log_msg += "\n";
				log_bff.Format("  * %s \n", sCH__LINK_OBJ_NAME_CHM_LIFT_PIN_DOWN->Get__STRING());
				log_msg += log_bff;

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			if(bACTIVE_CHM__LIFT_PIN)
			{
				sCH__LINK_OBJ_ACTIVE_CHM_LIFT_PIN_DOWN->Set__DATA(STR__YES);

				sEXT_CH__FNC_MSG->Set__DATA("CHAMBER.LIFT_PIN-DOWN Started ...");

				if(pOBJ_CTRL__CHM_LIFT_PIN->Call__OBJECT(CMMD_INIT) < 0)
				{
					sEXT_CH__FNC_MSG->Set__DATA("CHAMBER.LIFT_PIN-DOWN Aborted ...");
					return -51;
				}

				double cfg_sec = aCH__CFG_PART_STABLE_SEC->Get__VALUE();
				if(x_timer_ctrl->WAIT(cfg_sec) < 0)		return -(201 + i);

				sEXT_CH__FNC_MSG->Set__DATA("CHAMBER.LIFT_PIN-DOWN Completed ...");

				sCH__LINK_OBJ_ACTIVE_CHM_LIFT_PIN_DOWN->Set__DATA("");
			}
			else
			{
				log_msg  = "\n";
				log_msg += "Error : Not Active ...";
				log_msg += "\n";

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}

		if(dCH__CFG_SYS_INIT_CHM_DECHUCK->Check__DATA(STR__ENABLE) > 0)
		{
			// ...
			{
				log_msg  = "\n";
				log_msg += "CHMABER.DECHUCK Started ...";
				log_msg += "\n";
				log_bff.Format("  * %s \n", sCH__LINK_OBJ_NAME_CHM_DECHUCK->Get__STRING());
				log_msg += log_bff;

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			if(bACTIVE_CHM__DECHUCK)
			{
				sCH__LINK_OBJ_ACTIVE_CHM_DECHUCK->Set__DATA(STR__YES);

				sEXT_CH__FNC_MSG->Set__DATA("CHAMBER.DECHUCK Started ...");

				if(pOBJ_CTRL__CHM_DECHUCK->Call__OBJECT(CMMD_INIT) < 0)
				{
					sEXT_CH__FNC_MSG->Set__DATA("CHAMBER.DECHUCK Aborted ...");
					return -52;
				}

				double cfg_sec = aCH__CFG_PART_STABLE_SEC->Get__VALUE();
				if(x_timer_ctrl->WAIT(cfg_sec) < 0)		return -(211 + i);

				sEXT_CH__FNC_MSG->Set__DATA("CHAMBER.DECHUCK Completed ...");

				sCH__LINK_OBJ_ACTIVE_CHM_DECHUCK->Set__DATA("");
			}
			else
			{
				log_msg  = "\n";
				log_msg += "Error : Not Active ...";
				log_msg += "\n";

				xLOG_CTRL->WRITE__LOG(log_msg);
			}
		}
	}

	// ...
	int retVal = 1;

	if(dCH__CFG_CHAMBER_MODE->Check__DATA(STR__NORMAL) < 0)
	{
		retVal = -1;

		// ...
		{
			CString str_title;
			CString str_msg;
			CString str_bff;
			CStringArray l_act;
			CString r_act;
			CString var_data;

			//
			str_title = "The current chamber' status is not \"Normal\".";

			//
			str_msg = "Please, change chamber's status to \"Normal\". \n";

			dCH__CFG_CHAMBER_MODE->Get__DATA(var_data);
			str_bff.Format("Current status : \"%s\". \n", var_data);
			str_msg += str_bff;

			//
			l_act.RemoveAll();
			l_act.Add(STR__CHECK);

			//
			p_alarm->Popup__MESSAGE_BOX(str_title,str_msg,l_act,r_act);
		}
	}
	else
	{
		if(dCH__CFG_WAFER_STATUS->Check__DATA(STR__YES) > 0)
		{
			CString str_title;
			CString str_msg;
			CStringArray l_act;
			CString r_act;
			CString var_data;

			//
			str_title = "The current chamber' wafer status is not \"No\".";

			//
			str_msg  = "Really, is there wafer in PMC ? \n";
			str_msg += "If there is no wafer in PMC, change chamber's wafer status to \"NO\". \n";

			//
			l_act.Add(STR__YES);
			l_act.Add(STR__NO);

			//
			p_alarm->Popup__MESSAGE_BOX(str_title,str_msg,l_act,r_act);

			if(r_act.CompareNoCase(STR__YES) == 0)
			{
				dEXT_CH__WAFER_STATUS->Set__DATA(STR__EXIST);
			}
			else
			{
				retVal = -1;
			}
		}
	}

	return retVal;
}

int CObj__SYSTEM_STD
::Call__SYSTEM_MAINT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	//.....
	{
		CString log_msg;

		log_msg = "Maint : Completed ...";
		sEXT_CH__FNC_MSG->Set__DATA(log_msg);
	}
	return 1;
}

int CObj__SYSTEM_STD
::Call__TRANSFER_INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	int retVal = 1;
	CString log_msg;

	/*
	// ...
	{
		log_msg.Format("Transfer Init : Lift Pin Init Started ...");
		sEXT_CH__FNC_MSG->Set__DATA(log_msg);

		retVal = pEXT_LIFT_PIN_CTRL->Call__OBJECT(CMMD_INIT);
		if(retVal < 0)
		{
			log_msg.Format("Transfer Init : Lift Pin Init Aborted ...");
			sEXT_CH__FNC_MSG->Set__DATA(log_msg);

			//.....
			CString str_msg;
			str_msg.Format("TRANSFER_INIT : Lift Pin INIT Failed : Result [%d] ", retVal);

			int alarm_id = ALID__SYSTEM_INIT_ALARM;
			Alarm__POST_CHECK(p_alarm, str_msg, alarm_id);

			xLOG_CTRL->WRITE__LOG(str_msg);
			return retVal;
		}

		log_msg.Format("Transfer Init : Lift Pin Init Completed ...");
		sEXT_CH__FNC_MSG->Set__DATA(log_msg);
	}

	// ...
	{
		log_msg.Format("Transfer Init : Active Hand-Off Started ...");
		sEXT_CH__FNC_MSG->Set__DATA(log_msg);

		retVal = pEXT_ACT_HANDOFF_CTRL->Call__OBJECT(CMMD_INIT);
		if(retVal < 0)
		{
			log_msg.Format("Transfer Init : Active Hand-Off Aborted ...");
			sEXT_CH__FNC_MSG->Set__DATA(log_msg);

			//.....
			CString str_msg;
			str_msg.Format("TRANSFER_INIT : Active Hand-Off INIT Failed : Result [%d] ", retVal);

			int alarm_id = ALID__SYSTEM_INIT_ALARM;
			Alarm__POST_CHECK(p_alarm, str_msg, alarm_id);

			xLOG_CTRL->WRITE__LOG(str_msg);
			return retVal;
		}

		log_msg.Format("Transfer Init : Active Hand-Off Completed ...");
		sEXT_CH__FNC_MSG->Set__DATA(log_msg);
	}

	// ...
	{
		log_msg.Format("Transfer Init : ESC Init Started ...");
		sEXT_CH__FNC_MSG->Set__DATA(log_msg);

		//.....
		retVal = pEXT_ESC_CTRL->Call__OBJECT(CMMD_INIT);
		if(retVal < 0)
		{
			log_msg.Format("Transfer Init : ESC Init Aborted ...");
			sEXT_CH__FNC_MSG->Set__DATA(log_msg);

			//.....
			CString str_msg;
			str_msg.Format("TRANSFER_INIT : ESC Init Failed : Result [%d] ", retVal);

			int alarm_id = ALID__SYSTEM_INIT_ALARM;
			Alarm__POST_CHECK(p_alarm, str_msg, alarm_id);

			xLOG_CTRL->WRITE__LOG(str_msg);
			return retVal;
		}

		log_msg.Format("Transfer Init : ESC Init Completed ...");
		sEXT_CH__FNC_MSG->Set__DATA(log_msg);
	}

	// INIT Complete Check ...
	{
		log_msg.Format("TRANSFER_INIT Complete : Result [%d] ", retVal);
		xLOG_CTRL->WRITE__LOG(log_msg);

		sEXT_CH__FNC_MSG->Set__DATA("Init Completed ...");
	}
	*/

	return retVal;
}