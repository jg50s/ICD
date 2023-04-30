#include "StdAfx.h"
#include "CMacro_FA.h"

#include "CObj_Phy__LPx_STD.h"
#include "CObj_Phy__LPx_STD__DEF.h"
#include "CObj_Phy__LPx_STD__ALID.h"

#include "Macro_Function.h"


extern CMacro_FA mFA_Link;


// ...
#define STR__AVAILABLE			"AVAILABLE"
#define STR__ABORTED			"ABORTED"


// ...
void CObj_Phy__LPx_STD
::Mon__PORT_EXCEPTION(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;


	while(1)
	{
		while(dCH_CFG__LPx_USE->Check__DATA("DISABLE") > 0)
		{
			p_variable->Wait__SINGLE_OBJECT(0.9);

			sCH__RESERVE_ID->Set__DATA("__");
		}
		p_variable->Wait__SINGLE_OBJECT(0.1);

		
		// RESERVE ID ...
		{
			CUIntArray l__ptn_rsv;
			xI_SCH_MATERIAL_CTRL->Get__PORT_RESERVE_LIST(l__ptn_rsv);

			int check_id = -1;

			int k_limit = l__ptn_rsv.GetSize();
			for(int k=0; k<k_limit; k++)
			{
				int ptn_id = l__ptn_rsv[k];
				if(ptn_id != iPTN)			continue;

				check_id = k + 1;
				break;
			}

			if(check_id > 0)
			{
				ch_data.Format("%1d", check_id);
			}
			else				
			{
				if(sCH__PORT_STATUS->Check__DATA("RESERVE") > 0)			ch_data = "?";
				else														ch_data = ".";
			}

			sCH__RESERVE_ID->Set__DATA(ch_data);
		}

		// ...
		{
			if((sCH__PORT_STATUS->Check__DATA(STR__UNLOAD_REQ) > 0)
			&& (sCH__PIO_TRANSFER->Check__DATA(STR__YES) < 0))
			{
				ch_data = STR__ON;
			}
			else
			{
				ch_data = STR__OFF;
			}

			dCH__ACTIVE_FOUP_RELOAD->Set__DATA(ch_data);
		}

		_Fnc__PORT_EXCEPTION(p_variable, p_alarm);
	}
}

void CObj_Phy__LPx_STD
::Mon__PORT_CTRL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	// PORT CTRL ...
	int retry_cnt__cst_none = 0;

	CString status;
	CString pre_status;
	CString report_pre_status;

	sCH__PORT_STATUS->Get__DATA(status);

	if(status.CompareNoCase("EMPTY") != 0)
	{
		sCH__PORT_STATUS->Set__DATA(STR__ABORTED);
	}

	sCH__PORT_STATUS->Get__DATA(status);

	pre_status = status;
	report_pre_status = status;

	Sleep(3000);

	if((dCH__CST_STATUS->Check__DATA("NONE")   < 0)
	&& (dCH__SHUTL_STS->Check__DATA("UNLOAD")  > 0)
	&& (dCH__CLAMP_STS->Check__DATA("UNCLAMP") > 0))
	{
		if(sCH__PORT_STATUS->Check__DATA("ABORTED") > 0)
		{
			if(xCH__OBJ_CTRL->Check__DATA("RUN") > 0)
			{
				Fnc__PREPLOAD(p_variable);
			}
		}
	}


	while(1)
	{
		while(dCH_CFG__LPx_USE->Check__DATA("DISABLE") > 0)
		{
			p_variable->Wait__SINGLE_OBJECT(0.9);
		}
		p_variable->Wait__SINGLE_OBJECT(0.1);


		// PORT CTRL ...
		if(dCH__CST_STATUS->Check__DATA("NONE") > 0)
		{
			if(sCH__PORT_STATUS->Check__DATA("EMPTY") < 0)
			{
				if((Check__PORT_STATUS__JOB_READY() < 0)
				|| (retry_cnt__cst_none >= 10))
				{
					retry_cnt__cst_none = 0;

					// ...
					{
						xI_SCH_MATERIAL_CTRL->Clear__JOB(iPTN);

						sCH__PORT_STATUS->Set__DATA("EMPTY");
						sCH__CID_STRING->Set__DATA("");
					}

					Sleep(490);
				}
				else
				{
					retry_cnt__cst_none++;
				}
			}
		}
		else
		{
			if((dCH__SHUTL_STS->Check__DATA("UNLOAD")  > 0)
			&& (dCH__CLAMP_STS->Check__DATA("UNCLAMP") > 0))
			{
				if(sCH__PORT_STATUS->Check__DATA("WAITING") > 0)
				{
					sCH__PORT_STATUS->Set__DATA("ABORTED");
					//sCH__PORT_STATUS->Set__DATA("CANCELED");
				}
			}
			else
			{
				sCH__PORT_STATUS->Get__DATA(status);

				if((status.CompareNoCase("EMPTY") == 0)
				|| (status == ""))
				{
					if(xCH__FA_LP_CURRENT_STATUS->Check__DATA(STR__OUT_OF_SERVICE) > 0)
					{
						sCH__PORT_STATUS->Set__DATA("ABORTED");

						// ...
						{
							int alarm_id = ALID__LPx_STATUS_OUT_OF_SERVICE__NOT_RUN;
							CString alarm_msg;
							CString r_act;

							alarm_msg.Format("Please, clear foup on LP%1d.\n",iPTN);
							alarm_msg += "In out_of_service mode, cann't run any function.\n";

							p_alarm->Check__ALARM(alarm_id,r_act);
							p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alarm_msg);
						}
					}
					else
					{
						if(status.CompareNoCase("EMPTY") == 0)
						{
							sCH__PORT_STATUS->Set__DATA("WAITING");
						}
						else 
						{
							sCH__PORT_STATUS->Set__DATA("UNKNOWN");
						}
					}
				}			
			}
		}

		// ...
		sCH__PORT_STATUS->Get__DATA(status);

		if(report_pre_status.CompareNoCase(status) != 0)
		{
			report_pre_status = status;

			FA_Seq__STATUS_CHANGE();
		}

		if(status.CompareNoCase("CANCELED") == 0)
		{
			dCH__PORT_CTRL->Set__DATA(STR__AVAILABLE);

			//
			if(dCH_CFG__LPx_USE->Check__DATA("DUMMY") > 0)
			{
				Set__DUMMY_PORT();
			}
			else
			{
				Fnc__UNLOAD(p_variable,p_alarm);
			}
		}
		else if(status.CompareNoCase("ABORTED") ==0)
		{
			dCH__PORT_CTRL->Set__DATA(STR__ABORTED);

			if(pre_status != status)
			{
				pre_status = status;
			}

			if(Is__DUMMY_PORT() > 0)		Set__DUMMY_PORT();
		}
		else if(status.CompareNoCase("COMPLETED") == 0)
		{
			xCH__CYCLE_CTRL_FLAG->Set__DATA("");

			dCH__PORT_CTRL->Set__DATA(STR__AVAILABLE);

			if(pre_status != status)
			{
				pre_status = status;

				xEXT_CH__MELODY_BUZZER->Set__DATA("ON");
			}

			if(Is__DUMMY_PORT() > 0)
			{
				Set__DUMMY_PORT();
			}
			else
			{
				FA_Seq__COMPLETE();
				Fnc__UNLOAD(p_variable, p_alarm, 1);
			}
		}	
		else if(status.CompareNoCase("RELOAD") == 0)
		{
			dCH__PORT_CTRL->Set__DATA(STR__AVAILABLE);

			if(Is__DUMMY_PORT() > 0)
			{
				Clear__PORT_DATA();
			}
			else
			{
				if(dCH__PORT_CTRL->Check__DATA(STR__AVAILABLE) > 0)
				{
					Clear__PORT_DATA();
					Fnc__RELOAD(p_variable, p_alarm);
				}
			}
		}
		else if(status.CompareNoCase("UNLOAD_RELOAD") == 0)
		{
			dCH__PORT_CTRL->Set__DATA(STR__AVAILABLE);

			if(Fnc__RLSUNLOAD(p_variable) > 0)
			{
				if(Check__PORT_STS__Standby_Or_CtcInUse() > 0)
				{
					Fnc__RELOAD(p_variable, p_alarm, -1);
				}
			}
		}
		else if(status.CompareNoCase("EMPTY") == 0)
		{
			dCH__PORT_CTRL->Set__DATA(STR__AVAILABLE);

			if(Is__DUMMY_PORT() > 0)
			{
				Clear__PORT_DATA();
			}
			else
			{
				if(dCH__PORT_CTRL->Check__DATA(STR__AVAILABLE) > 0)
				{
					Clear__PORT_DATA();

					if(iFLAG__LPx_AUTO_LOAD > 0)
					{
						if(Check__PORT_STS__Standby_Or_CtcInUse() > 0)
						{
							Fnc__PREPLOAD(p_variable);
						}
					}
				}
			}
		}
		else if((status.CompareNoCase("LOAD") == 0)
		     || (status.CompareNoCase("LOAD_OK") == 0))
		{
			xCH__CYCLE_CTRL_FLAG->Set__DATA("");

			if(status.CompareNoCase("LOAD") == 0)
			{
				if(Is__MANUAL_MODE() > 0)
				{
					if(xCH__LPx_LOAD_REQ_BY_USER->Check__DATA("YES") < 0)
					{
						continue;
					}

					xCH__LPx_LOAD_REQ_BY_USER->Set__DATA("");
				}
			}

			// CID READ
			if(Is__DUMMY_PORT() > 0)
			{
				Set__DUMMY_PORT();
			}
			else
			{
				if(mFA_Link.Is_LP__BYPASS_ID(iPTN) > 0)
				{
					Sleep(990);

					sCH__PORT_STATUS->Set__DATA("CID_READING");
					FA_Seq__CID_READ_START();

					if(mFA_Link.Is__REMOTE() > 0)
					{
						Fnc__CID_READ(p_variable, p_alarm);
					}
					else
					{
						if(xEXT_CH__CFG_LPx_CID_FORMAT->Check__DATA(STR__CID_FORMAT__USER) > 0)
						{
							sCH__CID_STRING->Set__DATA("");

							if(Popup__WIN_CSTID() < 0)
							{
								Cancel__PORT();
							}
							else
							{
								Fnc__CID_READ(p_variable, p_alarm);
							}
						}
						else
						{
							CString str_cid;
							CString str_date;
							CString str_time;
	
							Macro__GET_DATE_TIME(str_date,str_time);

							if(xEXT_CH__CFG_LPx_CID_FORMAT->Check__DATA(STR__CID_FORMAT__ONLY_TIME) > 0)
							{
								str_cid.Format("LP%1d-%s_%s",iPTN,str_date,str_time);
							}
							else
							{
								str_cid.Format("LP%1d_Bypass-%s_%s",iPTN,str_date,str_time);
							}

							sCH__CID_STRING->Set__DATA(str_cid);

							Fnc__CID_READ(p_variable, p_alarm);
						}
					}
				}
				else
				{
					Sleep(990);

					if(Fnc__CID_READ(p_variable, p_alarm, 1) < 0)
					{
						sCH__PORT_STATUS->Set__DATA("ABORTED");
					}
				}
			}
		}
		else if(status.CompareNoCase("CID_CONFIRM")	== 0)
		{
			// MAP START
			if(Is__DUMMY_PORT() < 0)
			{
				if(Fnc__MAP(p_variable, p_alarm) < 0)
				{
					sCH__PORT_STATUS->Set__DATA("ABORTED");
				}
			}
		}
		else if(status.CompareNoCase("MAP_CONFIRM")	== 0)
		{
			sCH__PORT_STATUS->Set__DATA("WAITING");
		}
		else if(status.CompareNoCase("WAITING") == 0)
		{

		}

		pre_status = status;
	}
}

void CObj_Phy__LPx_STD
::_Fnc__PORT_EXCEPTION(CII_OBJECT__VARIABLE* p_variable, 
					   CII_OBJECT__ALARM* p_alarm)
{
	CString mode = sCH__PORT_EXCEPTION->Get__STRING();
	if(mode == "")		return;

	// ...
	CString status;

	if(xCH__FA_LP_CURRENT_STATUS->Check__DATA(STR__OUT_OF_SERVICE) > 0)
	{
		int alarm_id = ALID__LPx_STATUS_OUT_OF_SERVICE__NOT_RUN;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);
	}
	else
	{
		if((mode.CompareNoCase("CANCEL") == 0)
		|| (mode.CompareNoCase("ABORT")  == 0)
		|| (mode.CompareNoCase("RETURN") == 0))
		{
			if(xCH__APP_LOCK_FLAG->Check__DATA(STR__YES) > 0)
			{
				mode = "";

				// ...
				{
					int alarm_id = ALID__LPx_IN_USE__NOT_UNLOAD;
					CString r_act;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);
				}
			}
		}

		if(mode.CompareNoCase("CANCEL") == 0)
		{
			sCH__PORT_STATUS->Get__DATA(status);

			if((status.CompareNoCase("LOAD")        == 0)
			|| (status.CompareNoCase("CID_READ")    == 0)
			|| (status.CompareNoCase("CID_VERIFY")  == 0)
			|| (status.CompareNoCase("CID_CONFIRM") == 0)
			|| (status.CompareNoCase("MAP_START")   == 0)
			|| (status.CompareNoCase("MAP_END")     == 0)
			|| (status.CompareNoCase("MAP_VERIFY")  == 0)
			|| (status.CompareNoCase("MAP_CONFIRM") == 0)
			|| (status.CompareNoCase("WAITING")     == 0)
			|| (status.CompareNoCase("RESERVE")     == 0)
			|| (status.CompareNoCase("ABORTED")     == 0))
			{
				Cancel__PORT();
			}
		}
		else if(mode.CompareNoCase("ABORT") == 0)
		{
			sCH__PORT_STATUS->Get__DATA(status);

			if((status.CompareNoCase(STR__BUSY) == 0)
			|| (status.CompareNoCase("RESERVE") == 0)
			|| (status.CompareNoCase("PAUSED")  == 0))
			{
				Abort__PORT(p_alarm);

				xCH__LPx_END_REQ_FLAG->Set__DATA(STR__YES);
			}

			if(status.CompareNoCase("RESERVE") == 0)
			{
				// sCH__PORT_STATUS->Set__DATA("CANCELED");
				sCH__PORT_STATUS->Set__DATA("ABORTED");
			}
		}
		else if(mode.CompareNoCase("RETURN") == 0)
		{
			sCH__PORT_STATUS->Get__DATA(status);

			if((status.CompareNoCase(STR__BUSY) == 0)
			|| (status.CompareNoCase("RESERVE") == 0)
			|| (status.CompareNoCase("PAUSED")  == 0))
			{
				Return__PORT(p_alarm);

				xCH__LPx_RETURN_REQ_FLAG->Set__DATA(STR__YES);
			}

			if(status.CompareNoCase("RESERVE") == 0)
			{
				// sCH__PORT_STATUS->Set__DATA("CANCELED");
				sCH__PORT_STATUS->Set__DATA("ABORTED");
			}
		}
		else if(mode.CompareNoCase("PAUSE") == 0)
		{
			if(sCH__PORT_STATUS->Check__DATA(STR__BUSY) > 0)
			{
				Pause__PORT(p_alarm);
			}
			else if(sCH__PORT_STATUS->Check__DATA("PAUSED") > 0)
			{
				Resume__PORT(p_alarm);
			}
		}
		else if(mode.CompareNoCase("RELOAD") == 0)
		{
			sCH__PORT_STATUS->Get__DATA(status);

			if(status.CompareNoCase(STR__UNLOAD_REQ) == 0)
			{
				Reload__PORT(p_alarm);
			}
		}
	}

	sCH__PORT_EXCEPTION->Set__DATA("");
}

