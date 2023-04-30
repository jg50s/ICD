#include "StdAfx.h"
#include "CObj_FA__APP_CTRL.h"


#include "CMacro_FA.h"
extern CMacro_FA mFA_Link;


// ...
#define  STR__OFFLINE						"OFFLINE"
#define  STR__LOCAL							"LOCAL"
#define  STR__REMOTE						"REMOTE"
#define  STR__DISABLED						"DISABLED"

#define  STR__EQP_OFFLINE					"EQUIPMENT_OFFLINE"
#define  STR__ATTEMPT_ONLINE				"ATTEMPT_ONLINE"
#define  STR__HOST_OFFLINE					"HOST_OFFLINE"
#define  STR__ONLINE_LOCAL					"ONLINE_LOCAL"
#define  STR__ONLINE_REMOTE					"ONLINE_REMOTE"

#define  STR__COMMUNICATING					"COMMUNICATING"
#define  STR__ENABLE						"ENABLE"

#define  SPOOL_STATE__INACTIVE			    "Spool Inactive"
#define  SPOOL_STATE__ACTIVE				"Spool Active"
#define  SPOOL_STATE__FULL				    "Spool Full"
#define  SPOOL_STATE__PURGE					"Spool Purge"
#define  SPOOL_STATE__TRANSMIT				"Spool Transmit"
#define  SPOOL_STATE__NO_OUTPUT				"Spool No Output"


void CObj_FA__APP_CTRL::Mon__CONTROL_STATE_CTRL(CII_OBJECT__VARIABLE* p_variable)
{
	// SPOOLING CTRL ...
	int spool_count = 0;

	// ...
	CI_FA_300mm__E30_CTRL* p_e30_ctrl = mFA_Link.Get__FA_E30_CTRL();
	CI_FA_VARIABLE_CTRL*   p_var_ctrl = mFA_Link.Get__FA_VAR_CTRL();

	int init_flag = -1;
	int disconnect_flag = -1;
	int comm_ctrl_flag = -1;

	CString main_name;
	CString sub_name;
	CString var_data;

	// ...
	xCH__FA_CONTROL_STATE->Set__DATA(STR__DISABLED);

	if(xCH__FA_COMMUNICATION_CTRL->Check__DATA(STR__ENABLE) > 0)
	{
		comm_ctrl_flag = 1;
	}
	else
	{
		comm_ctrl_flag = -1;
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		// SPOOLING CTRL ...
		{
			Fnc__SPOOLING_CTRL(p_variable, spool_count);
		}

		// CONTROL STATE ...
		if(init_flag < 0)
		{
			if(xCH__FA_COMM_STATUS->Check__DATA(STR__COMMUNICATING) > 0)
			{
				init_flag = 1;

				// ...
				xCH__DEFAULT_INITIAL_STATE->Get__DATA(var_data);

				if(var_data.CompareNoCase(STR__ATTEMPT_ONLINE) != 0)
				{
					if(var_data.CompareNoCase(STR__ONLINE_LOCAL) == 0)
					{
						xCH__FA_REQ->Set__DATA(STR__LOCAL);
						xCH__FA_CONTROL_STATE->Set__DATA(STR__LOCAL);
					}
					else if(var_data.CompareNoCase(STR__ONLINE_REMOTE) == 0)
					{
						xCH__FA_REQ->Set__DATA(STR__REMOTE);
						xCH__FA_CONTROL_STATE->Set__DATA(STR__REMOTE);
					}
				}
				else
				{
					mFA_Link.Send__S1F1();

					// ...
					main_name = "#RCV_MSG-S1F1";
					sub_name  = "ACK";

					p_var_ctrl->Get_Variable(main_name,sub_name,var_data);
					if(var_data.CompareNoCase("S1F0") == 0)
					{
						if(xCH__DEFAULT_CONTROL_OFFLINE_STATE->Check__DATA(STR__EQP_OFFLINE) > 0)
						{
							xCH__FA_CONTROL_STATE->Set__DATA(STR__EQP_OFFLINE);
						}
						else if(xCH__DEFAULT_CONTROL_OFFLINE_STATE->Check__DATA(STR__HOST_OFFLINE) > 0)
						{
							xCH__FA_CONTROL_STATE->Set__DATA(STR__HOST_OFFLINE);
						}
					}
				}
			}
		}
		else
		{
			if(xCH__FA_USER_REQ->Check__DATA(STR__OFFLINE) > 0)
			{
				xCH__FA_USER_REQ->Set__DATA("");
				xCH__FA_REQ->Set__DATA(STR__OFFLINE);

				xCH__FA_CONTROL_STATE->Set__DATA(STR__EQP_OFFLINE);

				// Spooling Cleared ...
				{
					// MessageBox(NULL,"OK","Spooling Clear !!!",MB_OK|MB_TOPMOST);
				}
			}
			else if(mFA_Link.Is__LOCAL() > 0)
			{
				xCH__FA_CONTROL_STATE->Set__DATA(STR__LOCAL);
			}
			else if(mFA_Link.Is__REMOTE() > 0)
			{
				xCH__FA_CONTROL_STATE->Set__DATA(STR__REMOTE);
			}

			if(mFA_Link.Is__CONNECTED() < 0)
			{
				if(disconnect_flag < 0)
				{
					CString cur_state;
					xCH__FA_CONTROL_STATE->Get__DATA(cur_state);

					if((cur_state.CompareNoCase(STR__LOCAL)  == 0)
					|| (cur_state.CompareNoCase(STR__REMOTE) == 0))	
					{
						if(dCH_ECID__SPOOL_CONTROL->Check__DATA(STR__ENABLE) > 0)
						{
							sCH__SPOOLING_STATE->Set__DATA(SPOOL_STATE__ACTIVE);

							// ...
							{
								sCH_SVID__SPOOL_START_TIME->Set__DATA("");
								sCH_SVID__SPOOL_FULL_TIME->Set__DATA("");

								aCH_SVID__SPOOL_COUNT_TOTAL->Set__DATA("0");
								aCH_SVID__SPOOL_COUNT_ACTUAL->Set__DATA("0");
							}

							p_e30_ctrl->Request__SPOOLING_ACTIVE();
							p_e30_ctrl->Event__SPOOLING_ACTIVATED();
						}
					}
				}

				disconnect_flag = 1;
			}
			else if(disconnect_flag > 0)
			{
				disconnect_flag = -1;

				if(dCH_ECID__SPOOL_CONTROL->Check__DATA(STR__ENABLE) > 0)
				{
					CString cur_state;
					xCH__FA_CONTROL_STATE->Get__DATA(cur_state);

					if((cur_state.CompareNoCase(STR__LOCAL)  == 0)
						|| (cur_state.CompareNoCase(STR__REMOTE) == 0))	
					{	
						xCH__FA_REQ->Set__DATA("");

						if(cur_state.CompareNoCase(STR__LOCAL) == 0)
						{
							p_e30_ctrl->Set__FA_LINE_STATUS__LOCAL();
						}
						else if(cur_state.CompareNoCase(STR__REMOTE) == 0)
						{
							p_e30_ctrl->Set__FA_LINE_STATUS__REMOTE();
						}
					}

					// ...
				}
			}
		}

		// ...
		{
			if(xCH__EVENT_OFFLINE_ACTIVE_REQ->Check__DATA("YES") > 0)
			{
				xCH__EVENT_OFFLINE_ACTIVE_REQ->Set__DATA("");

				p_e30_ctrl->Set__EVENT_OFFLINE__ACTIVE();
			}
			if(xCH__EVENT_LOCAL_ACTIVE_REQ->Check__DATA("YES") > 0)
			{
				xCH__EVENT_LOCAL_ACTIVE_REQ->Set__DATA("");

				p_e30_ctrl->Set__EVENT_LOCAL__ACTIVE();
			}
			if(xCH__EVENT_REMOTE_ACTIVE_REQ->Check__DATA("YES") > 0)
			{
				xCH__EVENT_REMOTE_ACTIVE_REQ->Set__DATA("");

				p_e30_ctrl->Set__EVENT_REMOTE__ACTIVE();
			}

			// OFFLINE STATUS
			if(p_e30_ctrl->Check__EVENT_OFFLINE__ACTIVE() > 0)
			{
				xCH__EVENT_OFFLINE_ACTIVE_STATUS->Set__DATA("ENABLE");
			}
			else
			{
				xCH__EVENT_OFFLINE_ACTIVE_STATUS->Set__DATA("DISABLE");
			}	

			// LOCAL STATUS
			if(p_e30_ctrl->Check__EVENT_LOCAL__ACTIVE() > 0)
			{
				xCH__EVENT_LOCAL_ACTIVE_STATUS->Set__DATA("ENABLE");
			}
			else
			{
				xCH__EVENT_LOCAL_ACTIVE_STATUS->Set__DATA("DISABLE");
			}

			// REMOTE STATUS
			if(p_e30_ctrl->Check__EVENT_REMOTE__ACTIVE() > 0)
			{
				xCH__EVENT_REMOTE_ACTIVE_STATUS->Set__DATA("ENABLE");
			}
			else
			{
				xCH__EVENT_REMOTE_ACTIVE_STATUS->Set__DATA("DISABLE");
			}
		}

		// ...
		{
			if(xCH__FA_COMMUNICATION_CTRL->Check__DATA(STR__ENABLE) > 0)
			{
				if(comm_ctrl_flag < 0)
				{
					if(mFA_Link.Is__CONNECTED() > 0)
					{
						comm_ctrl_flag = 1;

						p_e30_ctrl->Event__COMMUNICATION_STATE__DISABLE_TO_ENABLE();
					}
				}
			}
			else
			{
				if(comm_ctrl_flag > 0)
				{
					comm_ctrl_flag = -1;

					p_e30_ctrl->Event__COMMUNICATION_STATE__ENABLE_TO_DISABLE();
				}
			}
		}
	}
}

void CObj_FA__APP_CTRL::
Fnc__SPOOLING_CTRL(CII_OBJECT__VARIABLE* p_variable, int& spool_count)
{
	CI_FA_300mm__E30_CTRL* p_e30_ctrl = mFA_Link.Get__FA_E30_CTRL();
	CI_FA_VARIABLE_CTRL*   p_var_ctrl = mFA_Link.Get__FA_VAR_CTRL();

	CString main_name = "#RCV_MSG-S6F23";
	CString sub_name  = "RSDC";

	CString var_data;
	int i_data;

	if(dCH_ECID__SPOOL_CONTROL->Check__DATA(STR__ENABLE) > 0)
	{
		if(p_var_ctrl->Get_Variable(main_name,sub_name,var_data) > 0)
		{
			if(var_data.CompareNoCase("OK") == 0)
			{
				p_e30_ctrl->Request__SPOOLING_TRANSMIT();

				p_var_ctrl->Clear_Variable(main_name);
			}
		}

		if(spool_count > 0)
		{
			aCH_SVID__SPOOL_COUNT_ACTUAL->Get__DATA(var_data);
			i_data = atoi(var_data);

			if(i_data < 1)
			{
				spool_count = -1;

				p_e30_ctrl->Request__SPOOLING_INACTIVE();
				p_e30_ctrl->Event__SPOOLING_DEACTIVATED();

				sCH__SPOOLING_STATE->Set__DATA(SPOOL_STATE__INACTIVE);				
			}
		}
		else
		{
			aCH_SVID__SPOOL_COUNT_ACTUAL->Get__DATA(var_data);
			i_data = atoi(var_data);

			if(i_data > 0)
			{
				spool_count = 1;
			}
		}
	}
	else
	{
		if(p_e30_ctrl->Check__SPOOLING_ACTIVE() > 0)
		{
			p_e30_ctrl->Request__SPOOLING_PURGE();
			p_e30_ctrl->Request__SPOOLING_INACTIVE();

			sCH__SPOOLING_STATE->Set__DATA(SPOOL_STATE__INACTIVE);				
		}
	}

	//.....
}

