#include "STdAfx.h"
#include "CMacro_FA.h"

#include "CObj_Phy__LPx_STD.h"
#include "CObj_Phy__LPx_STD__DEF.h"
#include "CObj_Phy__LPx_STD__ALID.h"


extern CMacro_FA mFA_Link;


// ...
void CObj_Phy__LPx_STD
::Mon__FA_REPORT(CII_OBJECT__VARIABLE* p_variable)
{
	// FA ONLINE_REPORT ...
	int online_sts = -1;

	// FA IO_REPORT ...
	CString p_clamp_sts   = "~";
	CString p_cst_sts     = "~";
	CString p_shuttle_sts = "~";
	CString p_door_sts    = "~";

	CString cur_pio_sts;
	CString pre_pio_sts = "~";

	// ...
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();
	CI_FA_300mm__E87_CTRL *p_e87_ctrl = mFA_Link.Get__E87_CTRL();
	
	CString var_data;	


	while(1)
	{
		Sleep(90);


		// FA ONLINE_REPORT ...
		while(1)				// break 처리를 위한 while 문 ...
		{
			if(p_e30_ctrl->Is_ONLINE() > 0)
			{
				if(online_sts < 0)
				{
					online_sts = 1;

					if(dCH_CFG__LPx_USE->Check__DATA("PROCESS")   < 0)		break;
					if(xCH__FA_LP_SERVICE_REQ->Check__DATA("YES") < 0)		break;
					if(sCH__PORT_STATUS->Check__DATA("LOAD.REQ")  < 0)		break;
					if(dCH__CST_STATUS->Check__DATA("EXIST") > 0)			break;

					p_e87_ctrl->Report__LP__READY_TO_LOAD(iPTN);
				}
			}
			else
			{
				if(online_sts > 0)
				{
					online_sts = -1;
				}
			}

			break;
		}

		// FA IO_REPORT ...
		{
			// CST STATUS 
			if((iSEQ__LOCK_FLAG < 0)
			&& (dCH__CST_STATUS->Get__DATA(var_data) > 0))
			{
				if((xEXT_CH__CFG_LPx_PIO_READY_CHECK_MODE->Check__DATA("ENABLE") > 0)
				&& (xCH__FA_LP_ACCESS_STATUS->Check__DATA("AUTO") > 0))
				{
					sCH__PIO_TRANSFER->Get__DATA(cur_pio_sts);

					if((p_cst_sts   != var_data)
					|| (pre_pio_sts != cur_pio_sts))
					{
						if((var_data.CompareNoCase("NONE")   != 0)
						|| (cur_pio_sts.CompareNoCase("YES") == 0))
						{
							if(Check__PORT_STATUS__JOB_READY() < 0)
							{
								FA_Seq__TRANSFER_BLOCKED();

								if((var_data.CompareNoCase("NONE")  != 0)
									&& (p_cst_sts.CompareNoCase("NONE") == 0))
								{
									p_e30_ctrl->Event__LP__LOAD_COMPLETE(iPTN);
								}
							}
						}
						else if(var_data.CompareNoCase("NONE") == 0)
						{
							if(Check__PORT_STATUS__JOB_READY() < 0)
							{
								p_e30_ctrl->Event__MATERIAL_REMOVED(iPTN);
								FA_Seq__TRANSFER_BLOCKED();
								p_e30_ctrl->Event__LP__UNLOAD_COMPLETE(iPTN);

								if(sCH__PORT_STATUS->Check__DATA("LOAD.REQ") > 0)
								{
									FA_Seq__LOAD_REQ();
								}
							}
						}

						p_cst_sts   = var_data;
						pre_pio_sts = cur_pio_sts;
					}
				}
				else
				{
					if(p_cst_sts != var_data)
					{
						p_cst_sts = var_data;

						if(var_data.CompareNoCase("NONE") != 0)
						{
							if(Check__PORT_STATUS__JOB_READY() < 0)
							{
								FA_Seq__TRANSFER_BLOCKED();
								p_e30_ctrl->Event__LP__LOAD_COMPLETE(iPTN);
							}
						}
						else if(var_data.CompareNoCase("NONE") == 0)
						{
							if(Check__PORT_STATUS__JOB_READY() < 0)
							{
								p_e30_ctrl->Event__MATERIAL_REMOVED(iPTN);
								FA_Seq__TRANSFER_BLOCKED();
								p_e30_ctrl->Event__LP__UNLOAD_COMPLETE(iPTN);

								if(sCH__PORT_STATUS->Check__DATA("LOAD.REQ") > 0)
								{
									FA_Seq__LOAD_REQ();
								}
							}
						}
					}
				}
			}

			// CLAMP STATUS
			if(dCH__CLAMP_STS->Get__DATA(var_data) > 0)
			{
				if(p_clamp_sts != var_data)
				{
					p_clamp_sts = var_data;

					if(var_data.CompareNoCase("CLAMP") == 0)		
					{
						p_e30_ctrl->Event__LP__FOUP_CLAMPED(iPTN);
					}
					else if(var_data.CompareNoCase("UNCLAMP") == 0)
					{
						p_e30_ctrl->Event__LP__FOUP_UNCLAMPED(iPTN);

						if((sCH__PORT_STATUS->Check__DATA("RESERVE") > 0)
							|| (sCH__PORT_STATUS->Check__DATA("BUSY")    > 0))
						{
							xI_SCH_MATERIAL_CTRL->Clear__JOB(iPTN);
							Cancel__PORT();
						}
					}
				}
			}

			// SHUTTLE
			if(dCH__SHUTL_STS->Get__DATA(var_data) > 0)
			{
				if(p_shuttle_sts != var_data)
				{
					p_shuttle_sts = var_data;

					if(var_data.CompareNoCase("LOAD") == 0)
					{
						p_e30_ctrl->Event__LP__FOUP_DOCKED(iPTN);
					}
					else if(var_data.CompareNoCase("UNLOAD") == 0)
					{
						p_e30_ctrl->Event__LP__FOUP_UNDOCKED(iPTN);

						if((sCH__PORT_STATUS->Check__DATA("RESERVE") > 0)
						|| (sCH__PORT_STATUS->Check__DATA("BUSY")    > 0))
						{
							xI_SCH_MATERIAL_CTRL->Clear__JOB(iPTN);
							Cancel__PORT();
						}
					}
				}
			}

			// DOOR
			if(dCH__DOOR_STS->Get__DATA(var_data) > 0)
			{
				if(p_door_sts != var_data)
				{
					p_door_sts = var_data;

					if(var_data.CompareNoCase("OPEN") == 0)
					{
						p_e30_ctrl->Event__LP__FOUP_DOOR_OPEN(iPTN);
					}
					else if(var_data.CompareNoCase("CLOSE")	== 0)
					{
						p_e30_ctrl->Event__LP__FOUP_DOOR_CLOSE(iPTN);
					}
				}
			}

			// ...
		}
	}	

	// ...
}

void CObj_Phy__LPx_STD
::Mon__FA_ACCESS_And_TRANSFER(CII_OBJECT__VARIABLE* p_variable,
							  CII_OBJECT__ALARM* p_alarm)
{
	while(mFA_Link.Fnc_Init() < 0)
	{
		Sleep(500);
	}

	// ...
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();
	CI_FA_300mm__E87_CTRL *p_e87_ctrl = mFA_Link.Get__E87_CTRL();

	// ...
	CString lp_name;
	lp_name.Format("LP%1d",iPTN);

	// ...
	int service_change_flag;
	int access_change_flag;
	CString	n_service_req;
	CString p_service_req;
	CString	n_access_req;
	CString p_access_req;
	CString	current_status;
	CString cur_sts;
	CString var_data;

	p_service_req = "~";
	p_access_req  = "~";

	xCH__FA_LP_ACCESS_REQ->Get__DATA(var_data);
	xCH__FA_LP_ACCESS_STATUS->Set__DATA(var_data);

	while(1)
	{
		Sleep(490);

		if(dEXT_CH__CFG_LPx_ACCESS_MODE_AUTO_CTRL_FLAG->Check__DATA(STR__ENABLE) > 0)
		{
			if(dCH__CFG_PROCESS_TYPE->Check__DATA(STR__TEST) > 0)
			{
				xCH__FA_LP_ACCESS_REQ->Set__DATA(STR__MANUAL);
			}
		}

		// SERVICE-REQ & ACCESS-REQ ...
		xCH__FA_LP_SERVICE_REQ->Get__DATA(n_service_req);
		xCH__FA_LP_ACCESS_REQ->Get__DATA(n_access_req);

		service_change_flag = -1;
		access_change_flag  = -1;

		if(n_service_req.CompareNoCase(p_service_req) != 0)
		{
			cur_sts = n_service_req;

			int ok_flag = -1;

			     if(cur_sts.CompareNoCase("YES") == 0)		ok_flag = 1;
			else if(cur_sts.CompareNoCase("NO")  == 0)		ok_flag = 1;

			if(ok_flag > 0)
			{
				p_service_req = n_service_req;	
				service_change_flag = 1;
			}
			else
			{
				if(p_service_req.CompareNoCase("~") == 0)
				{
					p_service_req = n_service_req;
				}
			}
		}

		if(n_access_req.CompareNoCase(p_access_req) != 0)
		{
			cur_sts = n_access_req;

			int ok_flag = -1;

			if(cur_sts.CompareNoCase("AUTO") == 0)
			{
				if(xEXT_CH__CFG_LPx_MANUAL_TO_AUTO_ALWAYS_APPLY->Check__DATA("ENABLE") < 0)
				{
					if((dCH__CST_STATUS->Check__DATA("NONE")  > 0)
					&& (sCH__PIO_TRANSFER->Check__DATA("YES") < 0))
					{
						ok_flag = 1;
					}
				}
				else
				{
					if(sCH__PIO_TRANSFER->Check__DATA("YES") < 0)
					{
						ok_flag = 1;
					}
				}

				if((p_access_req.CompareNoCase("~") != 0)
				&& (ok_flag < 0))
				{
					// Alarm Post
					int alarm_id = ALID__PORT_ACCESS__MANUAL_TO_AUTO;
					CString alarm_msg;
					CString r_act;

					if(dCH__CST_STATUS->Check__DATA("NONE") < 0)
					{
						alarm_msg.Format("There is foup on LP%1d.\n",iPTN);
						alarm_msg += "Please, convert access mode after foup is unloaded.\n";
					}
					else if(sCH__PIO_TRANSFER->Check__DATA("YES") > 0)
					{
						alarm_msg.Format("PIO transfer is running on LP%1d.\n",iPTN);
						alarm_msg += "Please, convert access mode after PIO transfer is completed.\n";
					}

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alarm_msg);
				}
			}
			else if(cur_sts.CompareNoCase("MANUAL") == 0)
			{
				if(sCH__PIO_TRANSFER->Check__DATA("YES") < 0)
				{
					ok_flag = 1;
				}

				if((p_access_req.CompareNoCase("~") != 0)
				&& (ok_flag < 0))
				{
					// Alarm Post
					int alarm_id = ALID__PORT_ACCESS__AUTO_TO_MANUAL;
					CString alarm_msg;
					CString r_act;

					if(sCH__PIO_TRANSFER->Check__DATA("YES") > 0)
					{
						alarm_msg.Format("PIO transfer is running on LP%1d.\n",iPTN);
						alarm_msg += "Please, convert access mode after PIO transfer is completed.\n";
					}

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alarm_msg);
				}
			}

			if(ok_flag > 0)
			{
				p_access_req = n_access_req;
				access_change_flag = 1;
			}
			else
			{
				if(p_access_req.CompareNoCase("~") == 0)
				{
					p_access_req = n_access_req;
				}
				else
				{
					xCH__FA_LP_ACCESS_REQ->Set__DATA(p_access_req);
				}
			}
		}

		// CURRENT-STATUS ...
		if(access_change_flag > 0)
		{
			if(p_access_req.CompareNoCase("AUTO") == 0)
			{
				xCH__FA_LP_ACCESS_STATUS->Set__DATA("AUTO");

				p_e87_ctrl->Event__LP__ACCESS_MODE__AUTO(iPTN);
			}
			else
			{
				xCH__FA_LP_ACCESS_STATUS->Set__DATA("MANUAL");

				p_e87_ctrl->Event__LP__ACCESS_MODE__MANUAL(iPTN);
			}
		}

		if(service_change_flag > 0)
		{
			if(p_service_req.CompareNoCase("YES") == 0)
			{
				p_e87_ctrl->Event__LP__IN_SERVICE(iPTN);

				sCH__PORT_STATUS->Get__DATA(var_data);

				if((var_data.CompareNoCase("LOAD.REQ")   == 0)
				|| (var_data.CompareNoCase("UNLOAD.REQ") == 0))
				{
					int lp_ready_flag = 1;

					if(var_data.CompareNoCase("LOAD.REQ") == 0)
					{
						if(dCH__CST_STATUS->Check__DATA("EXIST") > 0)
						{
							lp_ready_flag = -1;
						}
					}
					else if(var_data.CompareNoCase("UNLOAD.REQ") == 0)
					{
						if(dCH__CST_STATUS->Check__DATA("EXIST") < 0)
						{
							lp_ready_flag = -1;
						}
					}

					if(lp_ready_flag > 0)
					{
						p_e87_ctrl->Event__LP__TRANSFER_READY(iPTN);

						if(var_data.CompareNoCase("UNLOAD.REQ") == 0)
						{
							p_e87_ctrl->Event__LP__READY_TO_UNLOAD(iPTN);
						}
						else if(var_data.CompareNoCase("LOAD.REQ") == 0)
						{
							p_e87_ctrl->Event__LP__READY_TO_LOAD(iPTN);
						}
					}
					else
					{
						FA_Seq__TRANSFER_BLOCKED();
					}
				}
				else
				{
					FA_Seq__TRANSFER_BLOCKED();
				}
			}
			else
			{
				p_e87_ctrl->Event__LP__OUT_OF_SERVICE(iPTN);
			}
		}

		if((access_change_flag  > 0)
		|| (service_change_flag > 0))
		{
			if(p_service_req.CompareNoCase("YES") == 0)
			{
				if(p_access_req.CompareNoCase("AUTO") == 0)
				{
					current_status = STR__FULL_AUTO;
				}
				else
				{
					current_status = STR__MANUAL;
				}
			}
			else
			{
				current_status = STR__OUT_OF_SERVICE;
			}

			xCH__FA_LP_CURRENT_STATUS->Set__DATA(current_status);

			// ...
			{
				CStringArray l_data;

				if(current_status.CompareNoCase(STR__FULL_AUTO) == 0)
				{
					l_data.Add("AUTO");
				}
				else
				{
					l_data.Add("MANUAL");
				}

				xI_SCH_MATERIAL_CTRL->Set__USER_DEF_INFO("LP_INFO",lp_name,l_data);
			}
		}
	}	

	// ...
}


int  CObj_Phy__LPx_STD::FA_Seq__STATUS_CHANGE()
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();

	p_e30_ctrl->Event__LP__STATUS_CHANGE(iPTN);
	return 1;
}
int  CObj_Phy__LPx_STD::FA_Seq__TRANSFER_BLOCKED()
{
	if(xCH__FA_LP_TRANSFER_STATUS->Check__DATA("TRANSFER BLOCKED") > 0)
	{
		return 1;
	}

	CI_FA_300mm__E87_CTRL *p_e87_ctrl = mFA_Link.Get__E87_CTRL();

	p_e87_ctrl->Event__LP__TRANSFER_BLOCKED(iPTN);
	return 1;
}
int  CObj_Phy__LPx_STD::FA_Seq__LOAD_REQ()
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();

	p_e30_ctrl->Event__LP__LOAD_REQUEST(iPTN);
	return 1;
}
int  CObj_Phy__LPx_STD::FA_Seq__UNLOAD_REQ()
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();
	CI_FA_300mm__E87_CTRL *p_e87_ctrl = mFA_Link.Get__E87_CTRL();
	CI_FA_300mm__E40_CTRL *p_e40_ctrl = mFA_Link.Get__E40_CTRL();

	// ...
	{
		p_e87_ctrl->Event__LP__CARRIER_COMPLETE(iPTN);
		p_e30_ctrl->Event__LP__UNLOAD_REQUEST(iPTN);

		p_e40_ctrl->Delete__PJOB_FROM_PTN(iPTN);
	}
	return 1;
}

int  CObj_Phy__LPx_STD::FA_Seq__CID_READ_START()
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();

	p_e30_ctrl->Event__LP__CSTID_READ_START(iPTN);
	return 1;
}
int  CObj_Phy__LPx_STD::FA_Seq__CID_READ_END()
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();

	p_e30_ctrl->Event__LP__CSTID_READ_END(iPTN);
	return 1;
}

int  CObj_Phy__LPx_STD::FA_Seq__MAP_START()
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();

	p_e30_ctrl->Event__LP__SLOT_MAP_START(iPTN);
	return 1;
}
int  CObj_Phy__LPx_STD::FA_Seq__MAP_END()
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();

	p_e30_ctrl->Event__LP__SLOT_MAP_END(iPTN);
	return 1;
}

int  CObj_Phy__LPx_STD::FA_Seq__CAMCEL()
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();

	p_e30_ctrl->Event__LP__CANCEL(iPTN);
	return 1;
}
int  CObj_Phy__LPx_STD::FA_Seq__PAUSE()
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();

	p_e30_ctrl->Event__LP__PAUSE(iPTN);
	return 1;
}
int  CObj_Phy__LPx_STD::FA_Seq__RESUME()
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();

	p_e30_ctrl->Event__LP__RESUME(iPTN);
	return 1;
}
int  CObj_Phy__LPx_STD::FA_Seq__ABORT()
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();

	p_e30_ctrl->Event__LP__ABORT(iPTN);
	return 1;
}
int  CObj_Phy__LPx_STD::FA_Seq__COMPLETE()
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();

	p_e30_ctrl->Event__LP__LOT_DATA_REPORT(iPTN);
	p_e30_ctrl->Event__LP__COMPLETE(iPTN);
	return 1;
}
