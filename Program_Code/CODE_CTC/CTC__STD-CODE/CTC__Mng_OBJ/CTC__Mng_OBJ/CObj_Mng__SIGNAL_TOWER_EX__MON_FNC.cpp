#include "StdAfx.h"
#include "CObj_Mng__SIGNAL_TOWER_EX.h"


// ...
#define  STR__RED_LIGHT				"RED_LIGHT"
#define  STR__RED_ON				"RED_ON"
#define  STR__RED_OFF				"RED_OFF"
#define  STR__RED_FLASH				"RED_FLASH"

#define  STR__YELLOW_LIGHT			"YELLOW_LIGHT"
#define  STR__YELLOW_ON				"YELLOW_ON"
#define  STR__YELLOW_OFF			"YELLOW_OFF"
#define  STR__YELLOW_FLASH			"YELLOW_FLASH"

#define  STR__GREEN_LIGHT			"GREEN_LIGHT"
#define  STR__GREEN_ON				"GREEN_ON"
#define  STR__GREEN_OFF				"GREEN_OFF"
#define  STR__GREEN_FLASH			"GREEN_FLASH"

#define  STR__BLUE_LIGHT			"BLUE_LIGHT"
#define  STR__BLUE_ON				"BLUE_ON"
#define  STR__BLUE_OFF				"BLUE_OFF"
#define  STR__BLUE_FLASH			"BLUE_FLASH"

// ...
#define  STR__ON					"ON"
#define  STR__OFF					"OFF"
#define  STR__BLINK					"BLINK"
#define  STR__NOT_USE				"NOT_USE"


//-------------------------------------------------------------------------
int  CObj_Mng__SIGNAL_TOWER_EX
::Mon__SIGNAL_TOWER_CTRL(CII_OBJECT__VARIABLE *p_variable)
{
	/*
	1. RED
	   1) Equipment is error status
	   2) Equipment is maint mode
	   3) Equipment is error status and maint mode
	   4) Default
	  
	2. AMBER
	   1) Acceptable new carrier
	   2) Not acceptable new carrier
	   3) There is a proceeded carrrier
	   
	3. GREEN
	   1) Equipment is processing status
	   2) Equipment is idle status
	   
	4. BLUE
	   1) Online Remote Status & OHT Use (AUTO)
	   2) Online Remote Status & OHT Disuse (MANUAL)
	   3) Online Local Status 
	   4) Default
	*/

	// ...
	xSCH_MATERIAL_CTRL->Link__SERVICE_DB("");
	iPROCESS_PRE_FLAG = -1;

	xTIMER_CTRL->REGISTER__COUNT_CHANNEL(sObject_Name,xCH__PROCESS_END_TIME->Get__VARIABLE_NAME());

	// ...
	CString status;
	int flag;
	int cst_pre_sts = -1;

	while(1)
	{
		Sleep(490);

		// RED ---------------
		{
			// Alarm & Maint -----
			{
				flag = Check__ALARM_Or_MAINT();
				
				status.Format("%1d",flag);
				xCH__RED_STS->Set__DATA(status);
			}

			switch(flag)
			{
				case 1:		// ALARM
					xCH_CFG__RED_STATUS1_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;

				case 2:		// MAINT
					xCH_CFG__RED_STATUS2_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;

				case 3:		// ALARM & MAINT
					xCH_CFG__RED_STATUS3_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;

				default:
					xCH_CFG__RED_DEFAULT_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;
			}
		}

		// YELLOW ---------------
		{
			// Cassette Status -----
			{
				flag = Check__LOAD_REQ_Or_UNLOAD_REQ();

				status.Format("%1d",flag);
				xCH__YELLOW_STS->Set__DATA(status);
			}

			switch(flag)
			{
				case 1:
					xCH_CFG__AMBER_STATUS1_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;

				case 2:
					xCH_CFG__AMBER_STATUS2_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;

				case 3:
					xCH_CFG__AMBER_STATUS3_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;

				case 4:		// Equipment is idle status
					xCH_CFG__AMBER_STATUS4_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;

				default:	// Default
					xCH_CFG__AMBER_DEFAULT_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;
			}
		}

		// GREEN ---------------
		{
			// Process & Idle -----
			{
				flag = Check__PROCESS_Or_IDLE();
				
				status.Format("%1d",flag);
				xCH__GREEN_STS->Set__DATA(status);
			}

			switch(flag)
			{
				case 1:		// PROCESS
					xCH_CFG__GREEN_STATUS1_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;

				case 2:		// IDLE
					xCH_CFG__GREEN_STATUS2_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;

				default:    // Default
					xCH_CFG__GREEN_DEFAULT_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;
			}
		}
		
		// BLUE ---------------
		{
			// Control State -----
			{
				flag = Check__FA_STATUS();

				status.Format("%1d",flag);
				xCH__BLUE_STS->Set__DATA(status);
			}

			switch(flag)
			{
				case 1:		// REMOTE  (AUTO)
					xCH_CFG__BLUE_STATUS1_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;

				case 2:		// REMOTE  (MANUAL)
					xCH_CFG__BLUE_STATUS2_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;

				case 3:		// LOCAL
					xCH_CFG__BLUE_STATUS3_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;

				default:
					xCH_CFG__BLUE_DEFAULT_LIGHT_COLOR->Get__DATA(status);

					Fnc__Control_Light_Color(status);
					break;
			}
		}
	}

	return 1;
}


//-------------------------------------------------------------------------
// Alarm & Maint
int  CObj_Mng__SIGNAL_TOWER_EX::Check__ALARM_Or_MAINT()
{
	int error_flag = -1;
	int maint_flag = -1;

	if(xSCH_MATERIAL_CTRL->Check__SYSTEM_STATUS__ALARM() > 0)
	{
		error_flag = 1;
	}
	if(xSCH_MATERIAL_CTRL->Check__SYSTEM_STATUS__MAINT() > 0)
	{
		maint_flag = 1;
	}

	if(xCH_CFG__RED_STATUS3_LIGHT_COLOR->Check__DATA(STR__NOT_USE) < 0)
	{
		if((error_flag > 0)&&(maint_flag > 0))
		{
			return 3;
		}
	}
	if(xCH_CFG__RED_STATUS1_LIGHT_COLOR->Check__DATA(STR__NOT_USE) < 0)
	{
		if(error_flag > 0)
		{
			return 1;
		}
	}
	if(xCH_CFG__RED_STATUS2_LIGHT_COLOR->Check__DATA(STR__NOT_USE) < 0)
	{
		if(maint_flag > 0)
		{
			return 2;
		}
	}

	return -1;
}

// Cassette Status
int  CObj_Mng__SIGNAL_TOWER_EX::Check__LOAD_REQ_Or_UNLOAD_REQ()
{
	if(xCH_CFG__AMBER_STATUS4_LIGHT_COLOR->Check__DATA(STR__NOT_USE) < 0)
	{
		if(xSCH_MATERIAL_CTRL->Check__SYSTEM_STATUS__PROCESS() < 0)
		{
			return 4;
		}
	}

	if(xCH_CFG__AMBER_STATUS3_LIGHT_COLOR->Check__DATA(STR__NOT_USE) < 0)
	{
		if(xSCH_MATERIAL_CTRL->Check__SYSTEM_STATUS__UNLOAD_REQ() > 0)
		{
			if(xTIMER_CTRL->Get__CURRENT_TIME() > 0)
			{
				xTIMER_CTRL->STOP();
				xCH__PROCESS_END_TIME->Set__DATA("0");
			}
			return 3;
		}
	}

	if(xCH_CFG__AMBER_STATUS1_LIGHT_COLOR->Check__DATA(STR__NOT_USE) < 0)
	{
		if(xSCH_MATERIAL_CTRL->Check__SYSTEM_STATUS__LOAD_REQ() > 0)
		{
			return 1;
		}
	}

	if(xCH_CFG__AMBER_STATUS2_LIGHT_COLOR->Check__DATA(STR__NOT_USE) < 0)
	{
		return 2;
	}

	return -1;
}
		
// Process & Idle 
int  CObj_Mng__SIGNAL_TOWER_EX::Check__PROCESS_Or_IDLE()
{
	if(xCH_CFG__GREEN_STATUS1_LIGHT_COLOR->Check__DATA(STR__NOT_USE) < 0)
	{
		if(xSCH_MATERIAL_CTRL->Check__SYSTEM_STATUS__PROCESS() > 0)
		{
			iPROCESS_PRE_FLAG = 1;
			return 1;
		}
	}

	if(xCH_CFG__GREEN_STATUS2_LIGHT_COLOR->Check__DATA(STR__NOT_USE) < 0)
	{
		if(iPROCESS_PRE_FLAG > 0)
		{
			iPROCESS_PRE_FLAG = -1;

			xTIMER_CTRL->START__COUNT_DOWN(7.0);
		}

		return 2;
	}

	return -1;
}

// Control State
int  CObj_Mng__SIGNAL_TOWER_EX::Check__FA_STATUS()
{
	int fa_sts = xSCH_MATERIAL_CTRL->Get__FA_STATUS();

	if(fa_sts == FA_STATUS__REMOTE)
	{
		if(xCH_CFG__BLUE_STATUS1_LIGHT_COLOR->Check__DATA(STR__NOT_USE) < 0)
		{
			CString main_name;
			CString sub_name;
			CStringArray l_sub_name;
			CStringArray l_data;

			main_name = "LP_INFO";
			xSCH_MATERIAL_CTRL->Get__USER_DEF__SUB_LIST(main_name,l_sub_name);

			// ...
			int limit = l_sub_name.GetSize();
			int i;

			for(i=0;i<limit;i++)
			{
				sub_name = l_sub_name[i];

				if(xSCH_MATERIAL_CTRL->Get__USER_DEF_INFO(main_name,sub_name,l_data) < 0)
				{
					continue;
				}

				// ...
				int k_limit = l_data.GetSize();
				int k;

				for(k=0;k<k_limit;k++)
				{
					if(l_data[k].CompareNoCase("AUTO") == 0)
					{
						return 1;
					}
				}
			}
		}

		if(xCH_CFG__BLUE_STATUS2_LIGHT_COLOR->Check__DATA(STR__NOT_USE) < 0)
		{
			return 2;
		}
	}
	else if(fa_sts == FA_STATUS__LOCAL)
	{
		if(xCH_CFG__BLUE_STATUS3_LIGHT_COLOR->Check__DATA(STR__NOT_USE) < 0)
		{
			return 3;
		}
	}

	return -1;
}


//-------------------------------------------------------------------------
int  CObj_Mng__SIGNAL_TOWER_EX
::Fnc__Control_Light_Color(const CString& status)
{
	//
	if(status.CompareNoCase(STR__RED_ON) == 0)
	{
		xCH__LIGHT_RED->Set__DATA(STR__ON);
		return 1;
	}
	if(status.CompareNoCase(STR__RED_OFF) == 0)
	{
		xCH__LIGHT_RED->Set__DATA(STR__OFF);
		return 1;
	}
	if(status.CompareNoCase(STR__RED_FLASH) == 0)
	{
		xCH__LIGHT_RED->Set__DATA(STR__BLINK);
		return 1;
	}

	// 
	if(status.CompareNoCase(STR__YELLOW_ON) == 0)
	{
		xCH__LIGHT_YELLOW->Set__DATA(STR__ON);
		return 1;
	}
	if(status.CompareNoCase(STR__YELLOW_OFF) == 0)
	{
		xCH__LIGHT_YELLOW->Set__DATA(STR__OFF);
		return 1;
	}
	if(status.CompareNoCase(STR__YELLOW_FLASH) == 0)
	{
		xCH__LIGHT_YELLOW->Set__DATA(STR__BLINK);	
		return 1;
	}

	//
	if(status.CompareNoCase(STR__GREEN_ON) == 0)
	{
		xCH__LIGHT_GREEN->Set__DATA(STR__ON);
		return 1;
	}
	if(status.CompareNoCase(STR__GREEN_OFF) == 0)
	{
		xCH__LIGHT_GREEN->Set__DATA(STR__OFF);
		return 1;
	}
	if(status.CompareNoCase(STR__GREEN_FLASH) == 0)
	{
		xCH__LIGHT_GREEN->Set__DATA(STR__BLINK);
		return 1;
	}

	// 
	if(status.CompareNoCase(STR__BLUE_ON) == 0)
	{
		xCH__LIGHT_BLUE->Set__DATA(STR__ON);
		return 1;
	}
	if(status.CompareNoCase(STR__BLUE_OFF) == 0)
	{
		xCH__LIGHT_BLUE->Set__DATA(STR__OFF);
		return 1;
	}
	if(status.CompareNoCase(STR__BLUE_FLASH) == 0)
	{
		xCH__LIGHT_BLUE->Set__DATA(STR__BLINK);
		return 1;
	}

	return -1;
}
int  CObj_Mng__SIGNAL_TOWER_EX
::Fnc__Set_Off_Light_Color(const CString& status)
{
	//
	if((status.CompareNoCase(STR__RED_LIGHT) == 0)
	|| (status.CompareNoCase(STR__RED_ON)    == 0)
	|| (status.CompareNoCase(STR__RED_OFF)   == 0)
	|| (status.CompareNoCase(STR__RED_FLASH) == 0))
	{
		xCH__LIGHT_RED->Set__DATA(STR__OFF);
		return 1;
	}

	// 
	if((status.CompareNoCase(STR__YELLOW_LIGHT) == 0)
	|| (status.CompareNoCase(STR__YELLOW_ON)    == 0)
	|| (status.CompareNoCase(STR__YELLOW_OFF)   == 0)
	|| (status.CompareNoCase(STR__YELLOW_FLASH) == 0))
	{
		xCH__LIGHT_YELLOW->Set__DATA(STR__OFF);
		return 1;
	}

	//
	if((status.CompareNoCase(STR__GREEN_LIGHT) == 0)
	|| (status.CompareNoCase(STR__GREEN_ON)    == 0)
	|| (status.CompareNoCase(STR__GREEN_OFF)   == 0)
	|| (status.CompareNoCase(STR__GREEN_FLASH) == 0))
	{
		xCH__LIGHT_GREEN->Set__DATA(STR__OFF);
		return 1;
	}

	// 
	if((status.CompareNoCase(STR__BLUE_LIGHT) == 0)
	|| (status.CompareNoCase(STR__BLUE_ON)    == 0)
	|| (status.CompareNoCase(STR__BLUE_OFF)   == 0)
	|| (status.CompareNoCase(STR__BLUE_FLASH) == 0))
	{
		xCH__LIGHT_BLUE->Set__DATA(STR__OFF);
		return 1;
	}

	return -1;
}
