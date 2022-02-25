#include "StdAfx.h"
#include "CObj_Fnc__SINGLE_ARM_STD.h"

#include "Macro_Function.h"


// ...
#define STR__ROBOT_NAME			"ATM_RB1"

void CObj_Fnc__SINGLE_ARM_STD
::Mon__AUTO_CTRL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	// ...
	{
		xSCH_MATERIAL_CTRL->Link__SERVICE_DB("");
	
		xSCH_MATERIAL_CTRL->Define__ROBOT_NAME(STR__ROBOT_NAME);
		xSCH_MATERIAL_CTRL->Define__ROBOT_ARM(ARM_A);
		xSCH_MATERIAL_CTRL->Define__ROBOT_ARM(ARM_B);

		xSCH_MATERIAL_CTRL->Register__SYSTEM_NAME(sObject_Name);

		xSCH_MATERIAL_CTRL->JOB_CTRL__Disable_AUTO_PORT_COUNT();
	}

	iJOB_FLAG = -1;

	// ...
	CString ch_data;

	int loop_count = 0;
	int idle_flag = 0;
	int idle_count = -1;

	while(1)
	{
		while(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)
		{
			if(idle_flag <= 0)
			{
				if(xSCH_MATERIAL_CTRL->Check__SYSTEM_ABORT() > 0)
				{
					//
				}
				else if(xSCH_MATERIAL_CTRL->Check__SYSTEM_STOP() > 0)
				{
					//
				}
				else
				{
					if(idle_flag < 0)
					{
						printf(" * Idle : ATM_Robot <- Home ! \n");
					
						SEQ__ATM_RB__HOME(1);
					}

					try
					{
						Start__ALL_LBx_To_IDLE_STATE(p_variable);
					}
					catch(int err_flag)
					{

					}
				}

				xSCH_MATERIAL_CTRL->Set__ROBOT_IDLE(STR__ROBOT_NAME);

				Fnc__LPx_SideBuffer_Use_Flag_Clear();
				Set__TMC_CtcInUse_To_Standby();
			}

			// ...
			{
				sCH__SCH_LOOP_ID->Set__DATA("__");

				xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PLACE->Set__DATA("1");
				xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PICK->Set__DATA("1");
				xEXT_CH__BUFFER1__APP_CUR_LOTID->Set__DATA("");

				xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PLACE->Set__DATA("1");
				xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PICK->Set__DATA("1");
				xEXT_CH__BUFFER2__APP_CUR_LOTID->Set__DATA("");
			}

			// LLx ..
			{
				int ll_limit = iLLx_SIZE;
				int ll_i;

				for(ll_i=0; ll_i<ll_limit; ll_i++)
				{
					xCH__ATM_RB__SCH_STS_TO_LLx[ll_i]->Set__DATA("");
				}
			}

			iJOB_FLAG = -1;
			SCH__MATERIAL_CHECK();
			SCH__MODULE_CHECK();
			CHECK__ROBOT_MAP(p_variable,p_alarm);

			Sleep(100);
			idle_flag = 1;
			idle_count--;
		}
		iJOB_FLAG = 1;
			
		Sleep(1);

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("1");

			if(CHECK__ROBOT_MAP(p_variable,p_alarm) < 0)			continue;
			if(ATM_RB__Is_Available() < 0)							continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		if(idle_flag > 0)
		{
			loop_count = 0;
			idle_flag = -1;

			xSCH_MATERIAL_CTRL->Set__ROBOT_BUSY(STR__ROBOT_NAME);
			SCH__SYSTEM_INIT(p_variable);

			for(int i=0; i<iLPx_SIZE; i++)
			{
				xCH__LPx__PICK_COUNT[i]->Set__DATA("");
			}
		}

		// ...
		{
			loop_count++;
			if(loop_count > 10)
			{
				loop_count = 0;
			}
		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("10");

			if(ATM_RB__Is_Available() < 0)							continue;
			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		try
		{
			if(loop_count == 1)
			{
				sCH__SCH_LOOP_ID->Set__DATA("11.1");

				SCH__CHECK_LBi_ATM_PRESSURE(p_variable,p_alarm);
			}
		}
		catch(int err_flag)
		{

		}

		try
		{
			sCH__SCH_LOOP_ID->Set__DATA("11.2");

			SCH__CHECK_DUMMY_PORT(p_variable,p_alarm);
		}
		catch(int err_flag)
		{

		}

		// ...
		int before_buffer_mode = -1;

		if(xCH__SCH_DB_STx_TRANSFER_MODE->Check__DATA(STR__BEFORE_PROCESS) > 0)
		{
			if(xCH__SCH_DB_STx_APPLY_MODE->Check__DATA(STR__ENABLE) > 0)
			{
				before_buffer_mode = 1;

				if((sCH__SCH_DB_ST1_USE_FLAG->Check__DATA(STR__DISABLE) > 0)
				&& (sCH__SCH_DB_ST2_USE_FLAG->Check__DATA(STR__DISABLE) > 0))
				{
					int alarm_id = ALID__BUFFERx_CONFIG_ERROR;
					CString alm_msg;
					CString r_act;

					alm_msg = "At least, buffer1 or buffer2's use flag must be \"ENABLE\".\n";

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
				}
			}
			else if(xCH__SCH_DB_STx_APPLY_MODE->Check__DATA(STR__ROUTE) > 0)
			{
				if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_USE_BUFFERx() > 0)
				{
					CString var_data;
					xEXT_CH__VAC_AREA_MATERIAL_COUNT->Get__DATA(var_data);

					int material_count = atoi(var_data);
					if(material_count >= 2)
					{
						before_buffer_mode = 1;
					}
				}
			}
		}

		if(before_buffer_mode < 0)
		{
			sCH__SCH_LOOP_ID->Set__DATA("20");

			if(ATM_RB__Is_Available() < 0)							continue;
			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;

			//  LPi -> ALx
			try
			{
				if(xCH__AL1__ALIGN_RETRY_FLAG->Check__DATA("YES") < 0)
				{
					xSCH_MATERIAL_CTRL->Lock__MATERIAL_DB();
				
					sCH__SCH_LOOP_ID->Set__DATA("21");

					AUTO_CTRL__LPi_AL(p_variable,p_alarm);

					xSCH_MATERIAL_CTRL->Unlock__MATERIAL_DB();
				}
			}
			catch(int err_flag)
			{
				xSCH_MATERIAL_CTRL->Unlock__MATERIAL_DB();
			}
		}
		else
		{
			sCH__SCH_LOOP_ID->Set__DATA("30");

			if(ATM_RB__Is_Available() < 0)							continue;
			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;

			// LPi -> BUFFERx
			try
			{
				if(xCH__AL1__ALIGN_RETRY_FLAG->Check__DATA("YES") < 0)
				{
					xSCH_MATERIAL_CTRL->Lock__MATERIAL_DB();
				
					sCH__SCH_LOOP_ID->Set__DATA("31");

					AUTO_CTRL__LPi_BUFFERx(p_variable,p_alarm);

					xSCH_MATERIAL_CTRL->Unlock__MATERIAL_DB();
				}
			}
			catch(int err_flag)
			{
				xSCH_MATERIAL_CTRL->Unlock__MATERIAL_DB();
			}

			// ...
			sCH__SCH_LOOP_ID->Set__DATA("32");

			if(ATM_RB__Is_Available() < 0)							continue;
			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;

			// BUFFERx -> ALx
			try
			{
				sCH__SCH_LOOP_ID->Set__DATA("33");

				AUTO_CTRL__BUFFERx_AL(p_variable,p_alarm);
			}
			catch(int err_flag)
			{

			}	
		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("40");

			if(ATM_RB__Is_Available() < 0)							continue;
			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		//  ATM_RB -> ALx
		try
		{
			if(xCH__AL1__ALIGN_RETRY_FLAG->Check__DATA("YES") < 0)
			{
				sCH__SCH_LOOP_ID->Set__DATA("41");

				AUTO_CTRL__RB_AL(p_variable,p_alarm);
			}
		}
		catch(int err_flag)
		{
	
		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("50");

			if(ATM_RB__Is_Available() < 0)							continue;
			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		//  ALx -> LBi
		try
		{
			if(xEXT_CH__SCH_DB_AL1_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
			{
				if(xCH__AL1__ALIGN_RETRY_FLAG->Check__DATA("YES") > 0)
				{
					sCH__SCH_LOOP_ID->Set__DATA("51");

					AUTO_CTRL__Retry_ALIGN(p_variable,p_alarm);
				}
				else
				{
					if(SCH__LBx__CHECK_ONLY_INPUNT() > 0)
					{
						sCH__SCH_LOOP_ID->Set__DATA("52");

						AUTO_CTRL__AL_LBi__ONLY_MODE(p_variable,p_alarm);
					}
					else
					{
						sCH__SCH_LOOP_ID->Set__DATA("53");

						AUTO_CTRL__AL_LBi__ALL_MODE(p_variable,p_alarm);
					}
				}
			}
			else
			{
				if(SCH__LBx__CHECK_ONLY_INPUNT() > 0)
				{
					sCH__SCH_LOOP_ID->Set__DATA("54");

					AUTO_CTRL__RB_LBi__ONLY_MODE(p_variable,p_alarm);
				}
				else
				{
					sCH__SCH_LOOP_ID->Set__DATA("55");

					AUTO_CTRL__RB_LBi__ALL_MODE(p_variable,p_alarm);
				}
			}
		}
		catch(int err_flag)
		{
			
		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("60");

			if(ATM_RB__Is_Available() < 0)							continue;
			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		int after_buffer_mode = -1;

		if(xCH__SCH_DB_STx_TRANSFER_MODE->Check__DATA(STR__AFTER_PROCESS) > 0)
		{
			if(xCH__SCH_DB_STx_APPLY_MODE->Check__DATA(STR__ENABLE) > 0)
			{
				after_buffer_mode = 1;
			}
			else if(xCH__SCH_DB_STx_APPLY_MODE->Check__DATA(STR__ROUTE) > 0)
			{
				if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_USE_BUFFERx() > 0)
				{
					after_buffer_mode = 1;
				}
			}
		}

		if(after_buffer_mode < 0)
		{
			// ...
			{
				sCH__SCH_LOOP_ID->Set__DATA("70");

				if(ATM_RB__Is_Available() < 0)							continue;
				if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
				if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
				if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
			}

			//  LBo -> LPo
			try
			{
				sCH__SCH_LOOP_ID->Set__DATA("71");

				AUTO_CTRL__LBo_LPo(p_variable,p_alarm);
			}
			catch(int err_flag)
			{

			}
	
			// ...
			{
				sCH__SCH_LOOP_ID->Set__DATA("80");

				if(ATM_RB__Is_Available() < 0)							continue;
				if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
				if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
				if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
			}

			//  ATM_RB -> LPo
			try
			{
				sCH__SCH_LOOP_ID->Set__DATA("81");

				AUTO_CTRL__RB_LPo(p_variable,p_alarm);
			}
			catch(int err_flag)
			{

			}
		}
		else
		{
			// ...
			{
				sCH__SCH_LOOP_ID->Set__DATA("90");

				if(ATM_RB__Is_Available() < 0)							continue;
				if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
				if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
				if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
			}

			//  RB -> BUFFERx
			try
			{
				sCH__SCH_LOOP_ID->Set__DATA("91");

				AUTO_CTRL__RB_BUFFERx(p_variable,p_alarm);
			}
			catch(int err_flag)
			{

			}

			// ...
			{
				sCH__SCH_LOOP_ID->Set__DATA("100");

				if(ATM_RB__Is_Available() < 0)							continue;
				if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
				if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
				if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
			}

			//  LBo -> BUFFERx
			try
			{
				sCH__SCH_LOOP_ID->Set__DATA("101");

				AUTO_CTRL__LBo_BUFFERx(p_variable,p_alarm);
			}
			catch(int err_flag)
			{

			}
	
			// ...
			{
				sCH__SCH_LOOP_ID->Set__DATA("110");

				if(ATM_RB__Is_Available() < 0)							continue;
				if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
				if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
				if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
			}

			//  BUFFERx -> RB
			try
			{
				sCH__SCH_LOOP_ID->Set__DATA("111");

				AUTO_CTRL__BUFFERx_RB(p_variable,p_alarm);
			}
			catch(int err_flag)
			{

			}			

			// ...
			{
				sCH__SCH_LOOP_ID->Set__DATA("120");

				if(ATM_RB__Is_Available() < 0)							continue;
				if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
				if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
				if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
			}

			//  ATM_RB -> LPo
			try
			{
				sCH__SCH_LOOP_ID->Set__DATA("121");

				AUTO_CTRL__RB_LPo_IN_BUFFER_MODE(p_variable,p_alarm);
			}
			catch(int err_flag)
			{

			}
		}
	
		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("130");

			if(ATM_RB__Is_Available() < 0)							continue;
			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		//  AUTO PUMP
		try
		{
			if(SCH__LBx__CHECK_ONLY_OUTPUT() > 0)
			{
				sCH__SCH_LOOP_ID->Set__DATA("131");

				AUTO_CTRL__LBi_PUMP__ONLY_MODE(p_variable);
			}
			else
			{
				sCH__SCH_LOOP_ID->Set__DATA("132");

				AUTO_CTRL__LBx_PUMP__ALL_MODE(p_variable);
			}
		}
		catch(int err_flag)
		{

		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("140");

			if(ATM_RB__Is_Available() < 0)							continue;
			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		//  FRONT LBi
		try
		{
			sCH__SCH_LOOP_ID->Set__DATA("141");

			AUTO_CTRL__FRONT_LBi(p_variable);
		}
		catch(int err_flag)
		{

		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("150");

			if(ATM_RB__Is_Available() < 0)							continue;
			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		//  FRONT LBo
		try
		{
			sCH__SCH_LOOP_ID->Set__DATA("151");

			AUTO_CTRL__FRONT_LBo(p_variable);
		}
		catch(int err_flag)
		{

		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("160");

			if(ATM_RB__Is_Available() < 0)							continue;
			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		try
		{
			if(loop_count == 3)
			{
				sCH__SCH_LOOP_ID->Set__DATA("161");

				AUTO_CTRL__Venting_Exception_Proc(p_variable,p_alarm);
			}
		}
		catch(int err_flag)
		{

		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("170");

			if(ATM_RB__Is_Available() < 0)							continue;
			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}
		
		try
		{
			if(loop_count == 3)
			{
				sCH__SCH_LOOP_ID->Set__DATA("171");

				AUTO_CTRL__Robot_Abort_Exception(p_variable,p_alarm);
			}
		}
		catch(int err_flag)
		{
			
		}
	
		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("180");

			if(ATM_RB__Is_Available() < 0)							continue;
			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}
		
		try
		{
			if(loop_count == 3)
			{
				sCH__SCH_LOOP_ID->Set__DATA("181");

				AUTO_CTRL__Robot_Exception_Proc(p_variable,p_alarm);
			}
		}
		catch(int err_flag)
		{
			
		}

		if(loop_count == 5)
		{
			int ll_limit = iLLx_SIZE;
			int ll_i;

			for(ll_i=0; ll_i<ll_limit; ll_i++)
			{
				if(xCH__ATM_RB__SCH_STS_TO_LLx[ll_i]->Check__DATA("") < 0)
				{
					if(xSCH_MATERIAL_CTRL->Check__MATERIAL_OF_LLx_IN(-1, 1, true) < 0)
					{
						xCH__ATM_RB__SCH_STS_TO_LLx[ll_i]->Set__DATA("");
					}
				}
			}
		}

		// ...
	}
}


//------------------------------------------------------------------------------------------------
void CObj_Fnc__SINGLE_ARM_STD
::SCH__SYSTEM_INIT(CII_OBJECT__VARIABLE *p_variable)
{
	// ...
	{
		xCH__ATM_RB__EXCHANGE_LOCK_FLAG->Set__DATA("");
		xCH__ATM_RB__EXCHANGE_LOCK_LBx->Set__DATA("");
		xCH__ATM_RB__EXCHANGE_LOCK_SLOT->Set__DATA("");

		xCH__AL1__ALIGN_RETRY_FLAG->Set__DATA("");
	}

	// LLx ...
	{
		iLBx_FRONT_FLAG = -1;
		iLLx_IN_COUNT = 0;

		int i_limit = iLLx_SIZE;
		int i;

		for(i=0; i<i_limit; i++)
		{
			xEXT_CH__LLx__MOVE_FLAG[i]->Set__DATA("NO");
			xEXT_CH__LLx__IN_OUT_FLAG[i]->Set__DATA("IN");
			xEXT_CH__LLx__IN_COUNT[i]->Set__DATA("0");
			xEXT_CH__LLx__OUT_COUNT[i]->Set__DATA("0");

			xEXT_CH__LLx__PRE_MAINT_FLAG[i]->Set__DATA("");
		}
	}

	try
	{
		AUTO_CTRL__LBi_VENT(p_variable);
	}
	catch(int err_flag)
	{
		
	}

	try
	{
		AUTO_CTRL__LBo_PUMP(p_variable);
	}
	catch(int err_flag)
	{
		
	}
}
void CObj_Fnc__SINGLE_ARM_STD
::SCH__SYSTEM_CHECK(CII_OBJECT__VARIABLE *p_variable,
					  CII_OBJECT__ALARM *p_alarm,
					  const int job_flag)
{	
	CString r_act;
	int maint_flag = -1;
	int i;

	for(i=0;i<iLPx_SIZE;i++)
	{
		if(xCH__LPx__CFG_USE_TYPE[i]->Check__DATA(STR__DISABLE) > 0)
		{
			continue;
		}

		if(LPx__Check_CtcInUse_Or_Standby(i) > 0)
		{
			continue;
		}

		maint_flag = 1;
		break;
	}

	if(ATM_RB__Check_CtcInUse_Or_Standby() < 0)
	{
		if(job_flag > 0)
		{
			p_alarm->Check__ALARM(ALID__JOB_ERROR__ATM_RB__NOT_STANDBY,r_act);
			p_alarm->Post__ALARM(ALID__JOB_ERROR__ATM_RB__NOT_STANDBY);
		}

		maint_flag = 1;
	}

	if(AL1__Check_CtcInUse_Or_Standby() < 0)
	{
		if(job_flag > 0)
		{
			p_alarm->Check__ALARM(ALID__JOB_ERROR__AL1__NOT_STANDBY,r_act);
			p_alarm->Post__ALARM(ALID__JOB_ERROR__AL1__NOT_STANDBY);
		}

		maint_flag = 1;
	}

	// LLx ...
	{
		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(LLx__Check_CtcInUse_Or_Standby(ll_i) < 0)
			{
				if(job_flag > 0)
				{
					p_alarm->Check__ALARM(ALID__JOB_ERROR__LBA__NOT_STANDBY,r_act);
					p_alarm->Post__ALARM(ALID__JOB_ERROR__LBA__NOT_STANDBY);
				}
	
				maint_flag = 1;
			}
		}
	}

	if(maint_flag > 0)
	{
		xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MAINT(sObject_Name);
	}
	else
	{
		xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__MAINT(sObject_Name);
	}
}
void CObj_Fnc__SINGLE_ARM_STD
::SCH__MATERIAL_CHECK()
{	
	// EFEM-RB ...
	{
		if(ATM_RB__Check_Empty__Arm_Type() > 0)
		{
			xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__MATERIAL_STS(sObject_Name, "ATM_RB-A");		
			xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__MATERIAL_STS(sObject_Name, "ATM_RB-B");		
		}
		else
		{
			CString arm_type;
			CString wfr_pos;

			if(ATM_RB__Get_Occupied__Arm_Type(arm_type) > 0)
			{
				wfr_pos.Format("ATM_RB-%s", arm_type);
				xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MATERIAL_STS(sObject_Name, wfr_pos);		
			}
		}
	}

	if(AL1__Check_Empty__All_Slot() < 0)
	{
		xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MATERIAL_STS(sObject_Name,"AL1");		
	}
	else
	{
		xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__MATERIAL_STS(sObject_Name,"AL1");		
	}

	// ...
	{
		xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__MATERIAL_STS(sObject_Name,"VIS1");		
	}

	// LLx ...
	{
		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			CString ll_name = Get__LLx_NAME(ll_i);

			if(LLx__Check_All_Empty(ll_i) < 0)
			{
				xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MATERIAL_STS(sObject_Name, ll_name);		
			}
			else
			{
				xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__MATERIAL_STS(sObject_Name, ll_name);		
			}
		}
	}

	// SIDE_STORAGE1 ...
	{
		CString str_stx = "ST1";

		if(sCH__SCH_DB_ST1_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
		{
			if(Buffer1__Check_Empty__All_Slot() < 0)
				xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MATERIAL_STS(sObject_Name, str_stx);
			else
				xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__MATERIAL_STS(sObject_Name, str_stx);		
		}
		else
		{
			xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__MATERIAL_STS(sObject_Name, str_stx);		
		}
	}
	// SIDE_STORAGE2 ...
	{
		CString str_stx = "ST2";

		if(sCH__SCH_DB_ST2_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
		{
			if(Buffer2__Check_Empty__All_Slot() < 0)
				xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MATERIAL_STS(sObject_Name, str_stx);					
			else
				xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__MATERIAL_STS(sObject_Name, str_stx);		
		}
		else
		{
			xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__MATERIAL_STS(sObject_Name, str_stx);		
		}
	}
}
void CObj_Fnc__SINGLE_ARM_STD
::SCH__MODULE_CHECK()
{	
	if(ATM_RB__Is_Available() > 0)
	{
		xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MODULE_AVAILABLE(sObject_Name,"ATM_RB");		
	}
	else
	{
		xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MODULE_NOT_AVAILABLE(sObject_Name,"ATM_RB");		
	}

	if(AL1__Is_Available() > 0)
	{
		xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MODULE_AVAILABLE(sObject_Name,"AL1");		
	}
	else
	{
		xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MODULE_NOT_AVAILABLE(sObject_Name,"AL1");		
	}

	// ...
	{
		xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MODULE_DISABLE(sObject_Name,"VIS1");		
	}

	// LLX ...
	{
		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			CString ll_name = Get__LLx_NAME(ll_i);

			if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ALL) > 0)
			{
				if(LLx__Is_Available(ll_i) < 0)
				{
					xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MODULE_NOT_AVAILABLE(sObject_Name, ll_name);		
				}
				else
				{
					xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MODULE_AVAILABLE(sObject_Name, ll_name);		
				}
			}
			else
			{
				if(LLx__Is_Available(ll_i) > 0)
				{
					xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MODULE_AVAILABLE(sObject_Name, ll_name);		
				}
				else
				{
					xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MODULE_NOT_AVAILABLE(sObject_Name, ll_name);		
				}
			}
		}
	}

	// ...
}

//------------------------------------------------------------------------------------------------
int  CObj_Fnc__SINGLE_ARM_STD
::CHECK__ROBOT_MAP(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int i;

	if(xEXT_CH__SCH_MAP_DEVICE->Check__DATA(STR__ATM_RB) < 0)
	{
		for(i=0;i<iLPx_SIZE;i++)
		{
			if(xEXT_CH__LPx_MAP_REQ[i]->Check__DATA(STR__YES) > 0)
			{
				xEXT_CH__LPx_MAP_REQ[i]->Set__DATA("");
			}
		}
		return 1;
	}
	else
	{
		for(i=0;i<iLPx_SIZE;i++)
		{
			if((ATM_RB__Check_CtcInUse_Or_Standby() < 0)
			|| (LPx__Check_CtcInUse_Or_Standby(i)   < 0))
			{
				if(xEXT_CH__LPx_MAP_REQ[i]->Check__DATA(STR__YES) > 0)
				{
					xEXT_CH__LPx_MAP_REQ[i]->Set__DATA(STR__ERROR);
					
					// ...
					int alarm_id = ALID__LPx__MAP_ABORTED;
					CString alm_msg;
					CString alm_bff;
					CString r_act;
					CString var_data;

					alm_bff.Format("LP%1d's mapping request is rejected. \n", i+1);
					alm_msg += alm_bff;

					//
					alm_msg += "1. ATM Robot's status must be \"CtcInUse\" or \"Standby\". \n";

					xCH__ATM_RB__OBJ_STATUS->Get__DATA(var_data);
					alm_bff.Format("   Robot's current status is \"%s\". \n", var_data);
					alm_msg += alm_bff;

					//
					alm_bff.Format("2. LP%1d's status must be \"CtcInUse\" or \"Standby\". \n", i+1);
					alm_msg += alm_bff;

					xCH__LPx__OBJ_STATUS[i]->Get__DATA(var_data);
					alm_bff.Format("   LP%1d's current status is \"%s\". \n", i+1,var_data);
					alm_msg += alm_bff;

					//
					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
				}
			}
		}
	}

	if(ATM_RB__Check_Empty__Arm_Type() < 0)
	{
		return 1;
	}
	if(ATM_RB__Is_Available() < 0)
	{
		return -1;
	}

	// ...
	CString lp_name;
	int flag;

	for(i=0; i<iLPx_SIZE; i++)
	{
		if(xEXT_CH__LPx_MAP_REQ[i]->Check__DATA(STR__YES) > 0)
		{
			if(LPx__Check_CtcInUse_Or_Standby(i) < 0)
			{
				xEXT_CH__LPx_MAP_REQ[i]->Set__DATA(STR__ERROR);
				continue;
			}

			if(ATM_RB__Check_Empty__Arm_Type() < 0)
			{
				return 1;
			}
			if(ATM_RB__Is_Available() < 0)
			{
				return -1;
			}

			int wait_flag = -1;

			if(xCH__LPx__PORT_STATUS[i]->Check__DATA("WAITING") > 0)
			{
				wait_flag = 1;
				
				xCH__LPx__PORT_STATUS[i]->Set__DATA("MAPPING ...");
			}

			lp_name.Format("LP%1d",i+1);
			flag = SEQ__MAP_BY_ATM_RB(p_variable,lp_name);

			if(flag > 0)		xEXT_CH__LPx_MAP_REQ[i]->Set__DATA("");
			else				xEXT_CH__LPx_MAP_REQ[i]->Set__DATA(STR__ERROR);

			if(wait_flag > 0)
			{
				xCH__LPx__PORT_STATUS[i]->Set__DATA("WAITING");
			}

			if(flag > 0)
			{
				if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)
				{
					SEQ__ATM_RB__HOME(-1);
				}
			}
		}
	}
	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__LPi_AL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int port_id;
	int slot_id;

	if(xSCH_MATERIAL_CTRL->Get__MATERIAL_FROM_LPx(port_id,slot_id) > 0)
	{
		if(SCH__LPx_TO_LLx_OF_ROUTE_TYPE(p_variable, port_id,slot_id) < 0)
		{
			xSCH_MATERIAL_CTRL->JOB_CTRL__GoTo_NEXT_PORT_WITHOUT_PORT(port_id);

			/*
			// ...
			{
				printf(" * CObj_Fnc__SINGLE_ARM_STD::AUTO_CTRL__LPi_AL() ... \n");
				printf(" ** SCH__LPx_TO_LLx_OF_ROUTE_TYPE() < 0 \n");
				printf(" ** port_id <- %1d \n", port_id);
				printf(" ** slot_id <- %1d \n", slot_id);
				printf("\n");
			}
			*/
			NEXT__LOOP;
		}

		// ...
		CUIntArray l_ptn;
		xSCH_MATERIAL_CTRL->Get__JOB_PORT_LIST(l_ptn);

		if(l_ptn.GetSize() > 1)
		{
			int active__pick_lp = 1;

			// ...
			{
				int i_limit = l_ptn.GetSize();
				int i;

				for(i=0; i<i_limit; i++)
				{
					int lp_ptn = l_ptn[i];
					
					if(port_id == lp_ptn)
					{
						continue;
					}

					if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS_IN_LPx(lp_ptn) < 0)
					{
						continue;
					}

					active__pick_lp = -1;
					break;
				}
			}

			if(active__pick_lp > 0)
			{
				if((AL1__Is_Available() < 0)
				|| (AL1__Check_Empty__All_Slot() < 0))
				{
					active__pick_lp = -1;
				}
			}

			if(active__pick_lp < 0)
			{
				if(SCH__CAN_PLACE_LBi(1) < 0)
				{
					NEXT__LOOP;
				}
			}
		}
		else
		{
			int active__pick_lp = -1;

			if(AL1__Is_Available() > 0)
			{
				if(AL1__Check_Empty__All_Slot() > 0)
				{
					active__pick_lp = 1;
				}
			}

			if(active__pick_lp < 0)
			{
				if(SCH__CAN_PLACE_LBi(1) < 0)
				{
					NEXT__LOOP;
				}
			}
		}
	}
	else
	{
		NEXT__LOOP;
	}

	// ...
	{
		int check_count = 0;

		while(1)
		{
			if(ATM_RB__Is_Available() < 0)
			{
				check_count++;
				if(check_count > 10)
				{
					NEXT__LOOP;
				}

				Sleep(90);
				continue;
			}
			break;
		}
	}
	if(ATM_RB__Check_Empty__Arm_Type() < 0)
	{
		NEXT__LOOP;
	}

	// ...
	{
		int dummy_lp = Fnc__GET_DUMMY_PORT();
		
		if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS_IN_LPx(dummy_lp) < 0)
		{
			int lba_portid = -1;
			int lbb_portid = -1;
			int lbc_portid = -1;
			int lbd_portid = -1;
			
			// ...
			{
				int ll_limit = iLLx_SIZE;
				int ll_i;

				for(ll_i=0; ll_i>ll_limit; ll_i++)
				{
					IDS__SCH_MATERIAL_STATUS ds_info;
					CString sch_name;
					int lb_slotid;		
				
					CString ll_name = Get__LLx_NAME(ll_i);

					if((LLx__Check_CtcInUse_Or_Standby(ll_i) > 0)
					&& (LLx__Get_Occupied__InSlot(ll_i, lb_slotid) > 0))
					{
						sch_name.Format("%s-%1d", ll_name,lb_slotid);
						xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(sch_name,ds_info);

							 if(ll_i == 0)		lba_portid = ds_info.iPORT_ID;
						else if(ll_i == 1)		lbb_portid = ds_info.iPORT_ID;
						else if(ll_i == 2)		lbc_portid = ds_info.iPORT_ID;
						else if(ll_i == 3)		lbd_portid = ds_info.iPORT_ID;
					}
				}
			}
			
			// ...
			int except_portid = -1;
			
			if((lba_portid > 0) && (lbb_portid > 0))
			{
				if(lba_portid != lbb_portid)
				{
					NEXT__LOOP;
				}
			}
			else if((lbc_portid > 0) && (lbd_portid > 0))
			{
				if(lbc_portid != lbd_portid)
				{
					NEXT__LOOP;
				}
			}
			else
			{
				if(lba_portid > 0)
				{
					except_portid = lba_portid;
				}
				else if(lbb_portid > 0)
				{
					except_portid = lbb_portid;
				}
				else if(lbc_portid > 0)
				{
					except_portid = lbc_portid;
				}
				else if(lbd_portid > 0)
				{
					except_portid = lbd_portid;
				}
			}
			
			if(except_portid > 0)
			{
				xSCH_MATERIAL_CTRL->JOB_CTRL__GoTo_NEXT_PORT_WITHOUT_PORT(except_portid);
			}
		}
	}

	if(xSCH_MATERIAL_CTRL->Get__MATERIAL_FROM_LPx(port_id,slot_id) > 0)
	{
		int ll_id = SCH__LPx_TO_LLx_OF_ROUTE_TYPE(p_variable, port_id,slot_id);
		if(ll_id < 0)			NEXT__LOOP;

		if(xEXT_CH__SYSTEM_LEAK_CHECK_REQ->Check__DATA(STR__YES) > 0)
		{
			int db_index = port_id - 1;
			
			if((db_index >= 0) && (db_index < iLPx_SIZE))
			{
				CString var_data;
				int i_count;
				
				xCH__LPx__PICK_COUNT[db_index]->Get__DATA(var_data);
				i_count = atoi(var_data);
				
				if(i_count < 1)
				{
					NEXT__LOOP;
				}
			}
		}

		Get__LPx_SideBuffer_Info_To_Use(port_id,slot_id);

		if(LPx__Check_Occupied__Slot_Status(port_id,slot_id) < 0)
		{
			int lp_index   = port_id - 1;
			int slot_index = slot_id - 1;
			CString var_data;

			int alarm_id = ALID__LPx_MATERIAL_PICK__JOB_ERROR;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			alm_bff.Format("Please, check LP(%1d) and slot(%1d)'s status.\n",
				           port_id, slot_id);
			alm_msg += alm_bff;

			if((lp_index >= 0) && (lp_index < CFG_LP_LIMIT))
			{
				//
				xCH__LPx__PORT_STATUS[lp_index]->Get__DATA(var_data);
				
				alm_bff.Format("   1. Port Status     : \"%s\" \n", var_data);
				alm_msg += alm_bff;
				alm_msg += "       status must be \"BUSY\". \n";

				// 
				xCH__LPx__CST_STATUS[lp_index]->Get__DATA(var_data);
				
				alm_bff.Format("   2. Cassette Status : \"%s\" \n", var_data);
				alm_msg += alm_bff;
				alm_msg += "       status must be \"EXIST\". \n";
			}
			if((slot_index >= 0) && (slot_index < CFG_LP__SLOT_MAX))
			{
				//
				xCH__LPx__SLOT_STATUS[lp_index][slot_index]->Get__DATA(var_data);
				
				alm_bff.Format("   3. Slot Status     : \"%s\" \n", var_data);
				alm_msg += alm_bff;
				alm_msg += "       status must be \"MAPPED\". \n";
			}

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);

			NEXT__LOOP;
		}

		if(xEXT_CH__SCH_DB_AL1_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
		{
			if(AL1__Check_Empty__All_Slot() < 0)
			{
				if(SCH__CHECK_LBo_OCCUPIED() > 0)
				{
					NEXT__LOOP;	
				}
			}
		}

		// ...
		CString arm_type;

		// LPx -> ATM_RB
		if(Fnc__PICK_LPi(p_variable,p_alarm, port_id,slot_id,ll_id, arm_type) < 0)
		{
			NEXT__LOOP;
		}

		// ...
		{
			int dummy_lp = Fnc__GET_DUMMY_PORT();

			if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS_IN_LPx(dummy_lp) < 0)
			{
				int ll_portid = -1;

				int ll_limit = iLLx_SIZE;
				int ll_i;

				for(ll_i=0; ll_i<ll_limit; ll_i++)
				{
					CString ll_name = Get__LLx_NAME(ll_i);
					int lb_slotid;

					if((LLx__Check_CtcInUse_Or_Standby(ll_i) > 0)
					&& (LLx__Get_Occupied__InSlot(ll_i, lb_slotid) > 0))
					{
						IDS__SCH_MATERIAL_STATUS ds_info;
						CString sch_name;

						sch_name.Format("%s-%1d", ll_name,lb_slotid);
						xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(sch_name,ds_info);

						ll_portid = ds_info.iPORT_ID;
					}
				}

				if(ll_portid < 0)
				{
					xSCH_MATERIAL_CTRL->JOB_CTRL__GoTo_NEXT_PORT();
				}
			}
		}

		xSCH_MATERIAL_CTRL->Unlock__MATERIAL_DB();
		
		if(xSCH_MATERIAL_CTRL->Check__SYSTEM_ABORT() > 0)		NEXT__LOOP;
		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		NEXT__LOOP;

		if(xSCH_MATERIAL_CTRL->Check__MATERIAL_MORE_THAN_MOVE_COUNT(1) < 0)
		{
			SCH__SYSTEM_INIT(p_variable);
		}
		else
		{
			Seq__LBx_VENT__ALL_MODE(p_variable);
		}

		/*
		if(xEXT_CH__SCH_DB_AL1_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
		{
			if(xCH__AL1__ALIGN_RETRY_FLAG->Check__DATA("YES") < 0)
			{
				// ATM_RB -> AL 
				if(Fnc__PLACE_AL(p_variable,p_alarm,arm_type) < 0)
				{
					NEXT__LOOP;
				}
			}
		}
		*/
	}
	
	return 1;
}
int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__LPi_BUFFERx(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString var_data;

	// LPi -> BUFFERx
	while(1)
	{
		if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		NEXT__LOOP;
		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		NEXT__LOOP;

		// ...
		{
			xSCH_MATERIAL_CTRL->Lock__MATERIAL_DB();

			Fnc__LPi_BUFFERx(p_variable,p_alarm);

			xSCH_MATERIAL_CTRL->Unlock__MATERIAL_DB();
		}

		// LPi & BUFFERx : Check ...
		{
			int buffer_flag = -1;
			int slot_id;

			if(buffer_flag < 0)
			{
				if(sCH__SCH_DB_ST1_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
				{
					if(Buffer1__Check_Empty_Slot(slot_id) > 0)
					{
						buffer_flag = 1;
					}
				}
			}
			if(buffer_flag < 0)
			{
				if(sCH__SCH_DB_ST2_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
				{
					if(Buffer2__Check_Empty_Slot(slot_id) > 0)
					{
						buffer_flag = 1;
					}
				}
			}

			if(buffer_flag < 0)
			{
				NEXT__LOOP;
			}
			if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS() < 0)
			{
				NEXT__LOOP;
			}
		}
	}
	return 1;
}
int  CObj_Fnc__SINGLE_ARM_STD
::Fnc__LPi_BUFFERx(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString log_id = "Fnc__LPi_BUFFERx()";

	// ...
	{
		int check_count = 0;
		
		while(1)
		{
			if(ATM_RB__Is_Available() < 0)
			{
				check_count++;
				if(check_count > 10)
				{
					NEXT__LOOP;
				}
				
				Sleep(90);
				continue;
			}
			break;
		}
	}
	if(ATM_RB__Check_Empty__Arm_Type() < 0)
	{
		NEXT__LOOP;
	}

	// ...
	int port_id;
	int slot_id;

	if(xSCH_MATERIAL_CTRL->Get__MATERIAL_FROM_LPx(port_id,slot_id) > 0)
	{
		int ll_id = SCH__LPx_TO_LLx_OF_ROUTE_TYPE(p_variable, port_id,slot_id);
		if(ll_id < 0)			NEXT__LOOP;

		if(xEXT_CH__SYSTEM_LEAK_CHECK_REQ->Check__DATA(STR__YES) > 0)
		{
			int db_index = port_id - 1;
			
			if((db_index >= 0) && (db_index < iLPx_SIZE))
			{
				CString var_data;
				int i_count;
				
				xCH__LPx__PICK_COUNT[db_index]->Get__DATA(var_data);
				i_count = atoi(var_data);
				
				if(i_count < 1)
				{
					NEXT__LOOP;
				}
			}
		}

		// ...
		int buffer_check_flag = -1;
		CString buffer_name;
		int buffer_slot;

		// ...
		{
			int r_flag = Get__LPx_SideBuffer_Info_To_Use(port_id,slot_id, buffer_name,buffer_slot);

				 if(r_flag >  0)		buffer_check_flag =  1;
			else if(r_flag == 0)		buffer_check_flag = -1;
			else						NEXT__LOOP;
		}

		// ...
		CString arm_type;

		// LPx -> ATM_RB
		if(Fnc__PICK_LPi_In_BUFFER_MODE(p_variable,p_alarm, port_id,slot_id,ll_id, arm_type) < 0)
		{
			NEXT__LOOP;
		}

		// ...
		int dummy_lp = Fnc__GET_DUMMY_PORT();

		if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS_IN_LPx(dummy_lp) < 0)
		{
			xSCH_MATERIAL_CTRL->JOB_CTRL__GoTo_NEXT_PORT();
		}
		
		xSCH_MATERIAL_CTRL->Unlock__MATERIAL_DB();

		// ...
		if(xSCH_MATERIAL_CTRL->Check__SYSTEM_ABORT() > 0)		NEXT__LOOP;
		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		NEXT__LOOP;

		if(xSCH_MATERIAL_CTRL->Check__MATERIAL_MORE_THAN_MOVE_COUNT(1) < 0)
		{
			SCH__SYSTEM_INIT(p_variable);
		}
		else
		{
			Seq__LBx_VENT__ALL_MODE(p_variable);
		}

		if(xSCH_MATERIAL_CTRL->Check__SYSTEM_ABORT() > 0)		NEXT__LOOP;
		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		NEXT__LOOP;

		if(xCH__CFG_BUFFER_PRE_ALIGN_MODE->Check__DATA(STR__ENABLE) > 0)
		{
			// ATM_RB -> ALx
			if(Fnc__PLACE_AL(p_variable,p_alarm, log_id, arm_type) < 0)
			{
				NEXT__LOOP;
			}
		}

		if(xSCH_MATERIAL_CTRL->Check__SYSTEM_ABORT() > 0)		NEXT__LOOP;
		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		NEXT__LOOP;

		// ...
		if(buffer_check_flag > 0)
		{
			if(buffer_name.CompareNoCase(MODULE__BUFFER1) == 0)
			{
				xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PLACE->Inc__VALUE(1);
			}
			else if(buffer_name.CompareNoCase(MODULE__BUFFER2) == 0)
			{
				xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PLACE->Inc__VALUE(1);
			}

			// ATM_RB -> BUFFERx 
			if(Fnc__PLACE_BUFFERx(p_variable,p_alarm, arm_type, buffer_name,buffer_slot, "") < 0)
			{
				NEXT__LOOP;
			}
		}
	}
	
	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__RB_AL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_id = "AUTO_CTRL__RB_AL()";

	// ...
	CString arm_type;
	int i;

	for(i=0;i<1;i++)
	{
		if(i == 0)
		{
			if(ATM_RB__Get_Occupied__Arm_Type(arm_type) < 0)
			{
				continue;
			}
		}
		else
		{
			continue;
		}

		// ...
		IDS__SCH_MATERIAL_STATUS ds_info;
		
		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info) < 0)
		{
			continue;
		}

		if(ds_info.sMATERIAL_STS.CompareNoCase("MAPPED") != 0)
		{
			continue;
		}

		Fnc__PLACE_AL(p_variable,p_alarm, log_id, arm_type);
		break;
	}

	NEXT__LOOP;
}

int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__BUFFERx_AL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_id = "AUTO_CTRL__BUFFERx_AL()";

	// ...
	CString arm_type;

	if(ATM_RB__Get_Empty__Arm_Type(arm_type) < 0)
	{
		NEXT__LOOP;
	}

	if(xEXT_CH__SCH_DB_AL1_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
	{
		if(AL1__Check_Empty__All_Slot() < 0)
		{
			if(SCH__CHECK_LBo_OCCUPIED() > 0)
			{
				NEXT__LOOP;	
			}
		}
	}

	if(SCH__CAN_PLACE_LBi() < 0)
	{
		NEXT__LOOP;
	}

	// ...
	int buffer_flag = -1;
	CString bff_name;
	CString bff_slot;
	int slot_id;

	if(buffer_flag < 0)
	{
		if(sCH__SCH_DB_ST1_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
		{
			if(Buffer1__Get_Occupied__Slot_To_Process(slot_id) > 0)
			{
				buffer_flag = 1;
				bff_name = MODULE__BUFFER1;
			}
		}
	}
	if(buffer_flag < 0)
	{
		if(sCH__SCH_DB_ST2_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
		{
			if(Buffer2__Get_Occupied__Slot_To_Process(slot_id) > 0)
			{
				buffer_flag = 1;
				bff_name = MODULE__BUFFER2;
			}
		}
	}

	if(buffer_flag < 0)
	{
		NEXT__LOOP;
	}
	
	bff_slot.Format("%1d", slot_id);

	// ...
	{
		CString sch_module;
		sch_module.Format("%s-%s", bff_name,bff_slot);

		if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,arm_type,bff_name,bff_slot,sch_module) < 0)
		{
			NEXT__LOOP;
		}

		xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,arm_type);
	}

	Fnc__PLACE_AL(p_variable,p_alarm, log_id, arm_type);
	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__RB_LBi__ONLY_MODE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(ATM_RB__Check_Empty__Arm_Type() > 0)		NEXT__LOOP;

	if(SCH__CAN_PLACE_LBi() < 0)				NEXT__LOOP;
	if(SCH__CHECK_LBi_EMPTY() < 0)				NEXT__LOOP;

	// ...
	CString arm_type = ARM_A;
	bool    ex_flag  = false;

	// ...
	{
		IDS__SCH_MATERIAL_STATUS ds_sts;
		xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_sts);

		if(ds_sts.sMATERIAL_STS.CompareNoCase("ALIGNED") != 0)
		{
			NEXT__LOOP;
		}
	}

	if(Fnc__PLACE_LBi(p_variable,p_alarm,ex_flag,arm_type) < 0)
	{
		NEXT__LOOP;
	}

	NEXT__LOOP;
}
int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__RB_LBi__ALL_MODE(CII_OBJECT__VARIABLE *p_variable,
							  CII_OBJECT__ALARM *p_alarm)
{
	if(ATM_RB__Check_Empty__Arm_Type() > 0)
	{
		NEXT__LOOP;
	}
	if(SCH__CAN_PLACE_LBi() < 0)
	{
		NEXT__LOOP;
	}

	// ...
	CString arm_type = ARM_A;
	bool    ex_flag  = false;

	// ...
	{
		IDS__SCH_MATERIAL_STATUS ds_sts;
		xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_sts);

		if(ds_sts.sMATERIAL_STS.CompareNoCase("ALIGNED") != 0)
		{
			NEXT__LOOP;
		}

		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) < 0)
		{
			NEXT__LOOP;
		}
	}

	if(Seq__LBx_VENT__INTO_LBi(p_variable) > 0)
	{
		NEXT__LOOP;
	}
	
	// ...
	int material_flag = -1;

	CString para_module;
	CString para_in_slot;
	CString para_out_slot;
	int slot_id;
	int pick_flag = -1;

	int active__sch_mode = -1;
	int active__sch_ll = -1;

	if(sEXT_CH__SCH_MODE_LLx_IN->Check__DATA(_SCH_MODE__ROUTE) > 0)
	{
		CStringArray l_ll_id;
		CStringArray l_ll_mode;
		CStringArray l_ll_slot;

		xSCH_MATERIAL_CTRL->Get__LLx_IN_OF_EDIT_TYPE(arm_type, l_ll_id,l_ll_mode,l_ll_slot);

		if(l_ll_id.GetSize() == 1)
		{
			int index_ll = 0;
			int ll_id = atoi(l_ll_id[index_ll]);

			CString str_mode = l_ll_mode[index_ll];
			CString str_slot = l_ll_slot[index_ll];

			if(str_mode.CompareNoCase("ALL") == 0)
			{
				if((str_slot.CompareNoCase("11") == 0)
				|| (str_slot.CompareNoCase("10") == 0)
				|| (str_slot.CompareNoCase("01") == 0))
				{
					active__sch_mode = 1;
					active__sch_ll = ll_id;
				}
			}
		}
	}

	// ...
	int llx_out_flag = -1;

	if(active__sch_mode > 0)
	{
		int i_limit = iLLx_SIZE;
		
		for(int i=0; i<i_limit; i++)
		{
			int id = i + 1;
			if(active__sch_ll != id)		continue;
			
			llx_out_flag = id;
			break;
		}
	}
	else
	{
		int llx__count_max = -1;

		int i_limit = iLLx_SIZE;
		int i;
		
		for(i=0; i<i_limit; i++)
		{
			if(LLx__Is_ATM(i) < 0)							continue;
			if(LLx__Is_Available(i) < 0)					continue;
			if(LLx__Get_Empty__InSlot(i, slot_id) < 0)		continue;

			CString ch_data = xEXT_CH__LLx__OUT_COUNT[i]->Get__STRING();
			int llx_count = atoi(ch_data);
			if(llx_count <= llx__count_max)					continue;

			llx_out_flag = i + 1;
			llx__count_max = llx_count;
		}
	}

	if(llx_out_flag > 0)
	{
		int ll_i = llx_out_flag - 1;

		if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
		{
			if((LLx__Is_ATM(ll_i) > 0)
			&& (LLx__Is_Available(ll_i) > 0))
			{
				if(LLx__Get_Empty__InSlot(ll_i, slot_id) > 0)
				{
					para_module = Get__LLx_NAME(ll_i);
					para_in_slot.Format("%1d", slot_id);

					if(LLx__Get_Occupied__OutSlot(ll_i, slot_id) > 0)
					{
						para_out_slot.Format("%1d", slot_id);

						pick_flag = 1;
						ex_flag = true;
					}

					material_flag = 1;
				}
			}
		}
	}

	if(material_flag < 0)
	{
		NEXT__LOOP;
	}

	if(ex_flag == true)
	{
		CString sch_name;
		sch_name.Format("%s-%s", para_module,para_out_slot);

		if(Get__LPx_SideBuffer_Info_To_Use(sch_name) < 1)
		{
			ex_flag = false;
		}
	}

	if(ex_flag == true)
	{
		if((xCH_CFG__LBx_SWAP_FLAG->Check__DATA(STR__ENABLE) > 0)
		&& (pick_flag > 0))
		{
			CString sch_place_module;
			CString sch_pick_module;

			sch_place_module.Format("%s-%s",para_module,para_in_slot );
			sch_pick_module.Format( "%s-%s",para_module,para_out_slot);

			if(Fnc__SWAP_LBx(p_variable,
							 p_alarm,
							 para_module,
							 arm_type,
							 para_in_slot,
							 arm_type,
							 para_out_slot,
							 sch_place_module,
							 sch_pick_module) < 0)
			{
				xEXT_CH__JOB_CTRL->Set__DATA("Abort");

				// ...
				{
					int alarm_id = ALID__SWAP_ERROR;
					CString alarm_msg;
					CString r_act;

					alarm_msg.Format("Swap Error occurred when ATM-Robot is swapping with %s.\n",para_module);

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alarm_msg);
				}

				// ...
				{
					Sleep(990);

					xSCH_MATERIAL_CTRL->Clear__ALL_MATERIAL_INFO();
				}

				NEXT__LOOP;
			}
		}
		else
		{
			if(Fnc__PLACE_LBx(p_variable,
							  p_alarm,
							  ex_flag,
							  arm_type,
							  para_module,
							  para_in_slot) < 0)
			{
				NEXT__LOOP;
			}
				
			if(pick_flag > 0)
			{
				if(Fnc__PICK_LBx(p_variable,p_alarm, false,arm_type,para_module,para_out_slot) < 0)
				{
					NEXT__LOOP;
				}
			}
			else
			{
				xCH__ATM_RB__EXCHANGE_LOCK_FLAG->Set__DATA("YES");
				xCH__ATM_RB__EXCHANGE_LOCK_LBx->Set__DATA(para_module);
				xCH__ATM_RB__EXCHANGE_LOCK_SLOT->Set__DATA(para_out_slot);
			}
		}
	}
	else
	{
		if(Fnc__PLACE_LBx(p_variable,
						  p_alarm,
						  false,
						  arm_type,
						  para_module,
						  para_in_slot) < 0)
		{
			NEXT__LOOP;
		}
	}

	NEXT__LOOP;
}

int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__AL_LBi__ONLY_MODE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(ATM_RB__Check_Empty__Arm_Type() > 0)
	{
		if(SCH__CAN_PICK_LBo() > 0)
		{
			NEXT__LOOP;
		}
	}
	if(SCH__CAN_PLACE_LBi() < 0)
	{
		NEXT__LOOP;
	}

	if(ATM_RB__Check_Empty__Arm_Type() > 0)
	{
		CString arm_type;
		
		if(ATM_RB__Get_Empty__Arm_Type(arm_type) < 0)
		{
			NEXT__LOOP;
		}

		// ...
		bool ex_flag = false;

		if((SCH__CHECK_LBi_EMPTY() > 1)
		&& (AL1__Get_Occupied__Total_Count() > 1))
		{
			ex_flag = true;
		}

		// AL -> ATM_RB
		if(Fnc__PICK_AL(p_variable,p_alarm, arm_type) < 0)
		{
			NEXT__LOOP;
		}

		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) < 0)
		{
			NEXT__LOOP;
		}

		// ATM_RB -> LBi
		if(Fnc__PLACE_LBi(p_variable,p_alarm,ex_flag,arm_type) < 0)
		{
			NEXT__LOOP;
		}
	
		if(ex_flag == true)
		{
			// AL -> ATM_RB
			if(Fnc__PICK_AL(p_variable,p_alarm, arm_type) < 0)
			{
				NEXT__LOOP;
			}

			// ATM_RB -> LBi
			if((SCH__CHECK_LBi_EMPTY() < 2)
			|| (xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS() < 0))
			{
				if(Fnc__PLACE_LBi(p_variable,p_alarm,false,arm_type) < 0)
				{
					NEXT__LOOP;
				}
			}
			else
			{
				if(Fnc__PLACE_LBi(p_variable,p_alarm,true,arm_type) < 0)
				{
					NEXT__LOOP;
				}
			}
		}
	}
	else
	{
		CString arm_type;

		if(ATM_RB__Get_Occupied__Arm_Type(arm_type) < 0)
		{
			NEXT__LOOP;
		}

		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) < 0)
		{
			NEXT__LOOP;
		}

		// ...
		IDS__SCH_MATERIAL_STATUS ds_info;
		xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info);

		if(ds_info.sMATERIAL_STS != "ALIGNED")
		{
			NEXT__LOOP;
		}

		// ...
		bool ex_flag = false;

		if((SCH__CHECK_LBi_EMPTY() > 1)
		&& (AL1__Get_Occupied__Total_Count() > 0))
		{
			ex_flag = true;
		}

		// ATM_RB -> LBi
		if(Fnc__PLACE_LBi(p_variable,p_alarm,ex_flag,arm_type) < 0)
		{
			NEXT__LOOP;
		}

		if(ATM_RB__Get_Empty__Arm_Type(arm_type) < 0)
		{
			NEXT__LOOP;
		}

		// AL -> ATM_RB
		if(Fnc__PICK_AL(p_variable,p_alarm, arm_type) < 0)
		{
			NEXT__LOOP;
		}

		// ATM_RB -> LBi
		if((SCH__CHECK_LBi_EMPTY() < 2)
		|| (xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS() < 0))
		{
			if(Fnc__PLACE_LBi(p_variable,p_alarm,false,arm_type) < 0)
			{
				NEXT__LOOP;
			}
		}
		else
		{
			if(Fnc__PLACE_LBi(p_variable,p_alarm,true,arm_type) < 0)
			{
				NEXT__LOOP;
			}
		}
	}

	NEXT__LOOP;
}
int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__AL_LBi__ALL_MODE(CII_OBJECT__VARIABLE *p_variable,
							  CII_OBJECT__ALARM *p_alarm)
{
	if((xEXT_CH__SCH_DB_LLx_MODE_TYPE[0]->Check__DATA(LBx_MODE__ALL) < 0)
	|| (xEXT_CH__SCH_DB_LLx_MODE_TYPE[1]->Check__DATA(LBx_MODE__ALL) < 0))
	{
		return -1;
	}

	// ...
	int material_flag = -1;

	bool ex_flag = false;
	CString para_module;
	CString para_in_slot;
	CString para_out_slot;
	int slot_id;
	int pick_flag = -1;

	// ...
	int lba_out_flag = -1;
	int lbb_out_flag = -1;

	// ...
	int active__sch_mode = -1;
	int active__sch_ll = -1;

	if(sEXT_CH__SCH_MODE_LLx_IN->Check__DATA(_SCH_MODE__ROUTE) > 0)
	{
		CString sch__ll_name;

		if(ATM_RB__Check_Empty__Arm_Type() > 0)
		{
			CString para_module = MODULE__AL1;
			int al_slot_id;

			if(AL1__Get_Occupied__SlotID(al_slot_id) > 0)
			{
				sch__ll_name.Format("%s-%1d", para_module,al_slot_id);
			}
		}
		else 
		{
			if(ATM_RB__Get_Occupied__Arm_Type(sch__ll_name) < 0)
			{
				NEXT__LOOP;
			}
		}

		// ...
		CStringArray l_ll_id;
		CStringArray l_ll_mode;
		CStringArray l_ll_slot;

		xSCH_MATERIAL_CTRL->Get__LLx_IN_OF_EDIT_TYPE(sch__ll_name, l_ll_id,l_ll_mode,l_ll_slot);

		if(l_ll_id.GetSize() == 1)
		{
			int index_ll = 0;
			int ll_id = atoi(l_ll_id[index_ll]);

			CString str_mode = l_ll_mode[index_ll];
			CString str_slot = l_ll_slot[index_ll];

			if(str_mode.CompareNoCase("ALL") == 0)
			{
				if((str_slot.CompareNoCase("11") == 0)
				|| (str_slot.CompareNoCase("10") == 0)
				|| (str_slot.CompareNoCase("01") == 0))
				{
					active__sch_mode = 1;
					active__sch_ll = ll_id;
				}
			}
		}
	}

	// ...
	int ll_a = _LLx_INDEX__LBA;
	int ll_b = _LLx_INDEX__LBB;

	if(active__sch_mode > 0)
	{
		if(active__sch_ll == 1)
		{
			lba_out_flag = 1;
		}
		else if(active__sch_ll == 2)
		{
			lbb_out_flag = 1;
		}
	}
	else
	{
		int lba_out_count;
		int lbb_out_count;
		CString var_data;

		// LBA ...
		{
			xEXT_CH__LLx__OUT_COUNT[ll_a]->Get__DATA(var_data);
			lba_out_count = atoi(var_data);
		}
		// LBB ...
		{
			xEXT_CH__LLx__OUT_COUNT[ll_b]->Get__DATA(var_data);
			lbb_out_count = atoi(var_data);
		}

		if(lba_out_count <= lbb_out_count)
		{
			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_a]->Check__DATA("IN") > 0)
			{
				if((LLx__Is_ATM(ll_a) > 0)
				&& (LLx__Is_Available(ll_a) > 0)
				&& (LLx__Get_Empty__InSlot(ll_a, slot_id) > 0))
				{
					lba_out_flag = 1;
				}
			}

			if((lba_out_flag < 0)
			&& (xEXT_CH__LLx__IN_OUT_FLAG[ll_b]->Check__DATA("IN") > 0))
			{
				if((LLx__Is_ATM(ll_b) > 0)
			    && (LLx__Is_Available(ll_b) > 0)
				&& (LLx__Get_Empty__InSlot(ll_b, slot_id) > 0))
				{
					lbb_out_flag = 1;
				}
			}
		}
		else
		{
			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_b]->Check__DATA("IN") > 0)
			{
				if((LLx__Is_ATM(ll_b) > 0)
				&& (LLx__Is_Available(ll_b) > 0)
				&& (LLx__Get_Empty__InSlot(ll_b, slot_id) > 0))
				{
					lbb_out_flag = 1;
				}
			}

			if((lbb_out_flag < 0)
			&& (xEXT_CH__LLx__IN_OUT_FLAG[ll_a]->Check__DATA("IN") > 0))
			{
				if((LLx__Is_ATM(ll_a) > 0)
			    && (LLx__Is_Available(ll_a) > 0)
				&& (LLx__Get_Empty__InSlot(ll_a, slot_id) > 0))
				{
					lba_out_flag = 1;
				}
			}
		}
	}

	if(lba_out_flag > 0)
	{
		if((LLx__Is_ATM(ll_a) > 0)
		&& (LLx__Is_Available(ll_a) > 0))
		{
			if(LLx__Get_Empty__InSlot(ll_a, slot_id) > 0)
			{
				para_module = MODULE__LBA;
				para_in_slot.Format("%1d", slot_id);

				if(LLx__Get_Occupied__OutSlot(ll_a, slot_id) > 0)
				{
					para_out_slot.Format("%1d", slot_id);

					pick_flag = 1;
					ex_flag = true;
				}

				material_flag = 1;
			}
		}
	}
	if(lbb_out_flag > 0)
	{
		if((LLx__Is_ATM(ll_b) > 0)
		&& (LLx__Is_Available(ll_b) > 0))
		{
			if(LLx__Get_Empty__InSlot(ll_b, slot_id) > 0)
			{
				para_module = MODULE__LBB;
				para_in_slot.Format("%1d", slot_id);

				if(LLx__Get_Occupied__OutSlot(ll_b, slot_id) > 0)
				{
					para_out_slot.Format("%1d",slot_id);

					pick_flag = 1;
					ex_flag = true;
				}

				material_flag = 1;
			}
		}
	}

	if(material_flag < 0)
	{
		NEXT__LOOP;
	}

	if(ex_flag == true)
	{
		CString sch_name;
		sch_name.Format("%s-%s", para_module,para_out_slot);

		if(Get__LPx_SideBuffer_Info_To_Use(sch_name) < 0)
		{
			ex_flag = false;
		}
	}

	CString pick_arm;
	
	// ...
	{
		if(ATM_RB__Check_Empty__Arm_Type() > 0)
		{
			// ...
			{
				CString ll_slot;
				CString ll_name = SCH__Get_LBx_To_PLACE(ll_slot);
			
				if(ll_name.GetLength() < 1)		NEXT__LOOP;
						
				xCH__ATM_RB__TARGET_LLx_NAME_SET->Set__DATA(ll_name);
				xCH__ATM_RB__TARGET_LLx_SLOT_SET->Set__DATA(ll_slot);
			}

			try
			{
				Fnc__PICK_AL(p_variable,p_alarm, pick_arm);
			}
			catch(int err_flag)
			{
				NEXT__LOOP;
			}
		}
		else 
		{
			CString arm_type = ARM_A;

			if(ATM_RB__Get_Occupied__Arm_Type(arm_type) < 0)
			{
				NEXT__LOOP;
			}

			// ...
			IDS__SCH_MATERIAL_STATUS ds_info;
			
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info) < 0)
			{
				NEXT__LOOP;
			}
			if(ds_info.sMATERIAL_STS.CompareNoCase("ALIGNED") != 0)
			{
				NEXT__LOOP;
			}
		
			pick_arm = arm_type;
		}
	
		if(pick_arm.GetLength() < 1)
		{
			NEXT__LOOP;
		}
		
		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(pick_arm) < 0)
		{
			NEXT__LOOP;
		}
	}
	
	if(Seq__LBx_VENT__INTO_LBi(p_variable) > 0)
	{
		NEXT__LOOP;
	}

	if(ex_flag == true)
	{
		if((xCH_CFG__LBx_SWAP_FLAG->Check__DATA(STR__ENABLE) > 0)
		&& (pick_flag > 0))
		{
			CString sch_place_module;
			CString sch_pick_module;

			sch_place_module.Format("%s-%s",para_module,para_in_slot );
			sch_pick_module.Format( "%s-%s",para_module,para_out_slot);

			if(Fnc__SWAP_LBx(p_variable,
							 p_alarm,
							 para_module,
							 pick_arm,
							 para_in_slot,
							 pick_arm,
							 para_out_slot,
							 sch_place_module,
							 sch_pick_module) < 0)
			{
				xEXT_CH__JOB_CTRL->Set__DATA("Abort");

				// ...	
				int alarm_id = ALID__SWAP_ERROR;
				CString alarm_msg;
				CString r_act;

				alarm_msg.Format("Swap Error occured when ATM-Robot is swaping with %s.\n",para_module);

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alarm_msg);

				Sleep(990);
				xSCH_MATERIAL_CTRL->Clear__ALL_MATERIAL_INFO();

				NEXT__LOOP;
			}
		}
		else
		{
			if(Fnc__PLACE_LBx(p_variable,
							  p_alarm,
							  ex_flag,
							  pick_arm,
							  para_module,
							  para_in_slot) < 0)
			{
				NEXT__LOOP;
			}
				
			if(pick_flag > 0)
			{
				if(Fnc__PICK_LBx(p_variable,p_alarm, false,pick_arm,para_module,para_out_slot) < 0)
				{
					NEXT__LOOP;
				}
			}
			else
			{
				xCH__ATM_RB__EXCHANGE_LOCK_FLAG->Set__DATA("YES");
				xCH__ATM_RB__EXCHANGE_LOCK_LBx->Set__DATA(para_module);
				xCH__ATM_RB__EXCHANGE_LOCK_SLOT->Set__DATA(para_out_slot);
			}
		}
	}
	else
	{
		if(Fnc__PLACE_LBx(p_variable,
						  p_alarm,
						  false,
						  pick_arm,
						  para_module,
						  para_in_slot) < 0)
		{
			NEXT__LOOP;
		}
	}

	NEXT__LOOP;
}
int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__Retry_ALIGN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_id = "AUTO_CTRL__Retry_ALIGN()";

	// ...
	if(AL1__Is_Available()    < 0)			NEXT__LOOP;
	if(ATM_RB__Is_Available() < 0)			NEXT__LOOP;

	if(ATM_RB__Check_Empty__Arm_Type() > 0)
	{
		CString arm_type;
		if(ATM_RB__Get_Empty__Arm_Type(arm_type) < 0)			NEXT__LOOP;

		// ALr -> ATM_RB
		Fnc__PICK_AL(p_variable,p_alarm, arm_type);

		// ATM_RB -> ALr
		Fnc__PLACE_AL(p_variable,p_alarm, log_id, arm_type);
	}
	else
	{

	}

	xCH__AL1__ALIGN_RETRY_FLAG->Set__DATA("");
	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__LBo_LPo(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(SCH__LBx__CHECK_ONLY_OUTPUT() > 0)
	{
		Fnc__LBo_To_LPx__ONLY_MODE(p_variable,p_alarm);
	}
	else
	{
		Fnc__LBo_To_LPx__ALL_MODE(p_variable,p_alarm);
	}
		
	NEXT__LOOP;
}
int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__RB_LPo(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString arm_type;

	if(ATM_RB__Get_Occupied__Arm_Type(arm_type) < 0)	
	{
		NEXT__LOOP;
	}

	// ...
	IDS__SCH_MATERIAL_STATUS ds_info;

	if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info) < 0)
	{
		NEXT__LOOP;
	}

	// ...
	CString cur_sts = ds_info.sMATERIAL_STS;
	
	if((cur_sts.CompareNoCase("PROCESSED") == 0)
	|| (cur_sts.CompareNoCase(STR__TO_LP)  == 0))
	{
		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
		{
			NEXT__LOOP;
		}

		// ATM_RB -> LPo
		if(Fnc__PLACE_LPx(p_variable,p_alarm,arm_type) < 0)
		{
			return -1;
		}
	}

	return 1;
}
int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__RB_LPo_IN_BUFFER_MODE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString arm_type;

	if(ATM_RB__Get_Occupied__Arm_Type(arm_type) < 0)	
	{
		NEXT__LOOP;
	}

	if(xCH__SCH_DB_STx_APPLY_MODE->Check__DATA(STR__ROUTE) > 0)
	{
		int check_flag = -1;

		if(xSCH_MATERIAL_CTRL->Check__EDIT_TYPE__STATE() > 0)
		{
			CStringArray l_id;
			CStringArray l_mode;
			CStringArray l_slot; 
			CStringArray l_sec;

			if(xSCH_MATERIAL_CTRL->Get__STx_OF_EDIT_TYPE(arm_type, l_id,l_mode,l_slot,l_sec) > 0)
			{
				if(l_id.GetSize() > 0)
				{
					check_flag = 1;
				}
			}
		}
		else
		{
			CString bff1_info;
			CString bff2_info;

			xSCH_MATERIAL_CTRL->Get__BUFFERx_INFO(arm_type, bff1_info,bff2_info);

			if((bff1_info.CompareNoCase(STR__YES) == 0)
			|| (bff2_info.CompareNoCase(STR__YES) == 0))
			{
				check_flag = 1;
			}
		}

		if(check_flag > 0)
		{
			IDS__SCH_MATERIAL_STATUS ds_info;

			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info) < 0)
			{
				NEXT__LOOP;
			}
			if(ds_info.sMATERIAL_STS.CompareNoCase(STR__TO_LP) != 0)
			{
				NEXT__LOOP;
			}
		}
	}
	else
	{
		IDS__SCH_MATERIAL_STATUS ds_info;

		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info) < 0)
		{
			NEXT__LOOP;
		}
		if(ds_info.sMATERIAL_STS.CompareNoCase(STR__TO_LP) != 0)
		{
			NEXT__LOOP;
		}
	}

	if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
	{
		NEXT__LOOP;
	}

	// ATM_RB -> LPo
	if(Fnc__PLACE_LPx(p_variable,p_alarm,arm_type) < 0)
	{
		NEXT__LOOP;
	}
	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__BUFFERx_RB(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_id = "AUTO_CTRL__BUFFERx_RB()";

	// ...
	CString arm_type;

	if(ATM_RB__Get_Empty__Arm_Type(arm_type) < 0)
	{
		NEXT__LOOP;
	}

	// ...
	int i;

	for(i=0; i<2; i++)
	{
		int buffer_flag = -1;
		CString bff_name;
		CString bff_slot;
		int slot_id;

		if(buffer_flag < 0)
		{
			if(i == 0)
			{
				if(sCH__SCH_DB_ST1_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
				{
					if((Buffer1__Get_Occupied__Slot_To_Process(slot_id) > 0)
					&& (Buffer1__Check_Wait_Sec(slot_id) < 0))
					{
						buffer_flag = 1;
				
						bff_name = MODULE__BUFFER1;
						bff_slot.Format("%1d", slot_id);
					}
				}
			}
			else if(i == 1)
			{
				if(sCH__SCH_DB_ST2_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
				{
					if((Buffer2__Get_Occupied__Slot_To_Process(slot_id) > 0)
					&& (Buffer2__Check_Wait_Sec(slot_id) < 0))
					{
						buffer_flag = 1;
			
						bff_name = MODULE__BUFFER2;
						bff_slot.Format("%1d", slot_id);
					}
				}
			}
		}

		if(buffer_flag < 0)
		{
			continue;
		}

		// ...
		CString sch_module;
		sch_module.Format("%s-%s", bff_name,bff_slot);

		CString para__out_mode = "";
		int active__lpx_empty = -1;
		int active__lpx_opt   = -1;
		int active__lpx_time  = -1;

		if(bff_name.CompareNoCase(MODULE__BUFFER1) == 0)
		{
			para__out_mode = dCH__SCH_DB_ST1_OUT_MODE_BUFFER_TO_LPo->Get__STRING();
		}
		else if(bff_name.CompareNoCase(MODULE__BUFFER2) == 0)
		{
			para__out_mode = dCH__SCH_DB_ST2_OUT_MODE_BUFFER_TO_LPo->Get__STRING();
		}

		if(para__out_mode.CompareNoCase(STR__LPx_EMPTY) == 0)					active__lpx_empty = 1;
		if(para__out_mode.CompareNoCase(STR__LPx_OPTIMIZATION) == 0)			active__lpx_opt   = 1;
		if(para__out_mode.CompareNoCase(STR__LPx_TIME)  == 0)					active__lpx_time  = 1;

		if((active__lpx_empty > 0)
		|| (active__lpx_opt   > 0))
		{
			IDS__SCH_MATERIAL_INFO ds_info;
			xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(sch_module,ds_info);
	
			if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS_IN_LPx(ds_info.iSRC__PTN) > 0)
			{
				continue;
			}
		}
		else if(active__lpx_time > 0)
		{
			IDS__SCH_MATERIAL_INFO ds_info;
			xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(sch_module,ds_info);

			if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS_IN_LPx(ds_info.iSRC__PTN) > 0)
			{
				int check_skip = -1;

				if(bff_name.CompareNoCase(MODULE__BUFFER1) == 0)
				{
					if(Buffer1__Check_Empty__Any_Slot() < 0)		check_skip = 1;
				}
				else if(bff_name.CompareNoCase(MODULE__BUFFER2) == 0)
				{
					if(Buffer2__Check_Empty__Any_Slot() < 0)		check_skip = 1;
				}

				if(check_skip < 0)
				{
					continue;
				}
			}
		}
	
		if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,arm_type,bff_name,bff_slot,sch_module) < 0)
		{
			NEXT__LOOP;
		}

		xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,arm_type);

		NEXT__LOOP;
	}

	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__RB_BUFFERx(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString arm_type;
	CString arm_lotid;
	
	// ...
	{
		if(ATM_RB__Get_Occupied__Arm_Type(arm_type) < 0)
		{
			NEXT__LOOP;
		}

		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
		{
			NEXT__LOOP;
		}

		// ...
		{
			IDS__SCH_MATERIAL_STATUS ds_sts;
			xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_sts);

			if(ds_sts.sMATERIAL_STS.CompareNoCase(STR__TO_LP) == 0)
			{
				NEXT__LOOP;
			}
		}

		// ...
		IDS__SCH_MATERIAL_INFO ds_info;
		xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(arm_type,ds_info);

		arm_lotid = ds_info.sLOT_ID;

		if(xCH__SCH_DB_STx_APPLY_MODE->Check__DATA(STR__ROUTE) > 0)
		{
			if(xSCH_MATERIAL_CTRL->Check__EDIT_TYPE__STATE() > 0)
			{
				CStringArray l_id;
				CStringArray l_mode;
				CStringArray l_slot; 
				CStringArray l_sec;

				xSCH_MATERIAL_CTRL->Get__STx_OF_EDIT_TYPE(arm_type, l_id,l_mode,l_slot,l_sec);

				if(l_id.GetSize() < 1)
				{
					NEXT__LOOP;
				}
			}
			else
			{
				CString bff1_info;
				CString bff2_info;

				xSCH_MATERIAL_CTRL->Get__BUFFERx_INFO(arm_type, bff1_info,bff2_info);

				if((bff1_info.CompareNoCase(STR__YES) != 0)
				&& (bff2_info.CompareNoCase(STR__YES) != 0))
				{
					NEXT__LOOP;
				}
			}
		}
	}

	// ...
	{
		int buffer_flag = -1;
		CString bff_module;
		int bff_slot_id;

		if(arm_lotid.GetLength() > 0)
		{
			CString bff1_lotid = Buffer1__Get_LotID();
			CString bff2_lotid = Buffer2__Get_LotID();

			if(buffer_flag < 0)
			{
				if(arm_lotid.CompareNoCase(bff1_lotid) == 0)
				{
					if(sCH__SCH_DB_ST1_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
					{
						if(Buffer1__Check_Empty__Slot_To_Process(bff_slot_id) > 0)
						{
							buffer_flag = 1;
							bff_module = MODULE__BUFFER1;
						}
					}
				}
			}
			if(buffer_flag < 0)
			{
				if(arm_lotid.CompareNoCase(bff2_lotid) == 0)
				{
					if(sCH__SCH_DB_ST2_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
					{
						if(Buffer2__Check_Empty__Slot_To_Process(bff_slot_id) > 0)
						{
							buffer_flag = 1;
							bff_module = MODULE__BUFFER2;
						}
					}
				}
			}

			if(buffer_flag < 0)
			{
				if(bff1_lotid.GetLength() < 1)
				{
					if(sCH__SCH_DB_ST1_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
					{
						if(Buffer1__Check_Empty__Slot_To_Process(bff_slot_id) > 0)
						{
							buffer_flag = 1;
							bff_module = MODULE__BUFFER1;
						}
					}
				}
			}
			if(buffer_flag < 0)
			{
				if(bff2_lotid.GetLength() < 1)
				{
					if(sCH__SCH_DB_ST2_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
					{
						if(Buffer2__Check_Empty__Slot_To_Process(bff_slot_id) > 0)
						{
							buffer_flag = 1;
							bff_module = MODULE__BUFFER2;
						}
					}
				}
			}
		}

		if(buffer_flag < 0)
		{
			if(sCH__SCH_DB_ST1_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
			{
				if(Buffer1__Check_Empty__Slot_To_Process(bff_slot_id) > 0)
				{
					buffer_flag = 1;
					bff_module = MODULE__BUFFER1;
				}
			}
		}
		if(buffer_flag < 0)
		{
			if(sCH__SCH_DB_ST2_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
			{
				if(Buffer2__Check_Empty__Slot_To_Process(bff_slot_id) > 0)
				{
					buffer_flag = 1;
					bff_module = MODULE__BUFFER2;
				}
			}
		}

		if(buffer_flag < 0)
		{
			NEXT__LOOP;
		}

		Fnc__PLACE_BUFFERx(p_variable,p_alarm, arm_type, bff_module,bff_slot_id, arm_lotid);
	}
	return 1;
}
int  CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__LBo_BUFFERx(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(SCH__LBx__CHECK_ONLY_OUTPUT() > 0)
	{
		Fnc__LBo_To_BUFFERx__ONLY_MODE(p_variable,p_alarm);
	}
	else
	{
		Fnc__LBo_To_BUFFERx__ALL_MODE(p_variable,p_alarm);
	}
		
	NEXT__LOOP;
}

void CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__FRONT_LBi(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	{
		CString cfg_mode;
		dCH__CFG_PLACE_FRONT_OF_ROBOT_AND_LLx_DOOR->Get__DATA(cfg_mode);

		if(cfg_mode.CompareNoCase(STR__DISABLE) == 0)
		{
			return;
		}

		// ...
		CString cur__ani_trg_rote = xCH__ATM_RB__ANI_TRG_ROTE->Get__STRING();
		CString cur__ani_trg_move = xCH__ATM_RB__ANI_TRG_MOVE->Get__STRING();

		if(cfg_mode.CompareNoCase(STR__ENABLE) == 0)
		{
			if(Get__LLx_INDEX(cur__ani_trg_rote) >= 0)
			{
				return;
			}
			if(Get__LLx_INDEX(cur__ani_trg_move) >= 0)
			{
				return;
			}
		}
		if(cfg_mode.CompareNoCase(STR__ENABLE_LPx) == 0)
		{
			if(SCH__Get_LPx_INDEX(cur__ani_trg_rote) >= 0)
			{
				return;
			}
			if(SCH__Get_LPx_INDEX(cur__ani_trg_move) >= 0)
			{
				return;
			}
		}
		if(cfg_mode.CompareNoCase(STR__ENABLE_ALx) == 0)
		{
			if((cur__ani_trg_rote.CompareNoCase(MODULE__AL1) == 0)
			|| (cur__ani_trg_move.CompareNoCase(MODULE__AL1) == 0))
			{
				return;
			}			
		}
	}
	
	// ...
	{
		if(iLBx_FRONT_FLAG > 0)							return;
		if(ATM_RB__Check_Occupied__Arm_Type() < 0)		return;
	}

	// ...
	{
		IDS__SCH_MATERIAL_STATUS ds_info;

		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(ARM_A,ds_info) < 0)		return;
		if(ds_info.sMATERIAL_STS.CompareNoCase("ALIGNED") != 0)				return;
	}

	// ...
	{
		CString cfg_mode;
		dCH__CFG_PLACE_FRONT_OF_ROBOT_AND_LLx_DOOR->Get__DATA(cfg_mode);

		if(cfg_mode.CompareNoCase(STR__ENABLE_ALx) == 0)
		{
			CStringArray l_para;
				
			l_para.Add(ARM_A);
			l_para.Add(MODULE__AL1);
			l_para.Add("1");
				
			pATM_RB__OBJ_CTRL->Call__OBJ_MODE(ATM_CMMD__ROTATE,l_para);

			iLBx_FRONT_FLAG = 1;
			return;
		}
		else if(cfg_mode.CompareNoCase(STR__ENABLE_LPx) == 0)
		{
			CStringArray l_para;

			CString next_module;
			CString next_slot;
			
			dCH__CFG_FRONT_LPx_MODULE->Get__DATA(next_module);
			aCH__CFG_FRONT_LPx_SLOT->Get__DATA(next_slot);

			l_para.Add(ARM_A);
			l_para.Add(next_module);
			l_para.Add(next_slot);
			
			pATM_RB__OBJ_CTRL->Call__OBJ_MODE(ATM_CMMD__ROTATE,l_para);
			
			iLBx_FRONT_FLAG = 1;
			return;
		}
		else if(cfg_mode.CompareNoCase(STR__ENABLE) == 0)
		{
			int ll_limit = iLLx_SIZE;
			int ll_i;

			for(ll_i=0; ll_i<ll_limit; ll_i++)
			{
				if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
				{
					continue;
				}

				if((LLx__Is_Available(ll_i) < 0)
				&& (LLx__Is_ATM(ll_i) < 0))
				{
					if((xCH__ATM_RB__ANI_TRG_ROTE->Check__DATA(MODULE__LBA) < 0)
					&& (xCH__ATM_RB__ANI_TRG_MOVE->Check__DATA(MODULE__LBA) < 0))
					{
						int slot_id;

						if(LLx__Get_Empty__InSlot(ll_i, slot_id) > 0)
						{
							CStringArray l_para;
							CString str_data;

							CString ll_name = Get__LLx_NAME(ll_i);
							str_data.Format("%1d",slot_id);

							l_para.Add(ARM_A);
							l_para.Add(ll_name);
							l_para.Add(str_data);

							pATM_RB__OBJ_CTRL->Call__OBJ_MODE(ATM_CMMD__ROTATE,l_para);

							iLBx_FRONT_FLAG = 1;
							return;
						}
					}
					else
					{
						return;
					}
				}
			}

			// ...
		}
	}

	// ...
}
void CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__FRONT_LBo(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	if(iLBx_FRONT_FLAG > 0)
	{
		return;
	}

	// ...
	if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS() > 0)	return;
	if(ATM_RB__Check_Empty__Arm_Type() < 0)						return;
	if(AL1__Check_Empty__All_Slot() < 0)						return;

	// ...
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) < 0)
		{
			if((LLx__Is_Available(ll_i) < 0)
			&& (LLx__Is_ATM(ll_i) < 0))
			{
				if((xCH__ATM_RB__ANI_TRG_ROTE->Check__DATA(MODULE__LBA) < 0)
				&& (xCH__ATM_RB__ANI_TRG_MOVE->Check__DATA(MODULE__LBA) < 0))
				{
					int slot_id;

					if(LLx__Get_Occupied__OutSlot(ll_i, slot_id) > 0)
					{
						CStringArray l_para;
						CString str_data;

						CString ll_name = Get__LLx_NAME(ll_i);
						str_data.Format("%1d", slot_id);

						l_para.Add(ARM_A);
						l_para.Add(ll_name);
						l_para.Add(str_data);

						pATM_RB__OBJ_CTRL->Call__OBJ_MODE(ATM_CMMD__ROTATE, l_para);
					}
				}
				else
				{
					return;
				}
			}
		}
	}

	// ...
}

void CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__Venting_Exception_Proc(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_id = "AUTO_CTRL__Venting_Exception_Proc()";
	int i;

	if(ATM_RB__Is_Available() > 0)
	{
		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(LLx__Is_Available(ll_i) > 0)
			{
				if(LLx__Is_ATM(ll_i)  > 0)
				{
					if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)	
					{
						if(LLx__Check_All_Empty(ll_i) > 0)
						{
							if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") < 0)
							{
								if(SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "1") > 0)
								{
									xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
								}
							}
						}
						else
						{
							xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
						}					
					}
					else if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)	
					{
						if(LLx__Check_All_Empty(ll_i) > 0)
						{
							CString ch_data;
							
							xEXT_CH__LLx__IDLE_COUNT[ll_i]->Get__DATA(ch_data);
							int i_count = atoi(ch_data);

							if(i_count > 10)
							{
								xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
							}
						}
					}
					else
					{
						if(xEXT_CH__LLx__PRE_MAINT_FLAG[ll_i]->Check__DATA(STR__YES) > 0)
						{
							if(LLx__Check_All_Empty(ll_i) > 0)
							{
								xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
							}
							else
							{
								int out_count = LLx__Get_Occupied__Total_OutSlot(ll_i);
								int in_count  = LLx__Get_Occupied__Total_InSlot(ll_i, 1);

								if((out_count > 0) && (in_count == 0))
								{
									xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");	
								}
								else if((out_count == 0) && (in_count > 0))
								{
									xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");	
								}
							}
						}
						else
						{
							int slot_max = iLLx_SLOT_MAX[ll_i];

							if(slot_max > 1)
							{
								int xx_port;
								int xx_slot;
								
								if(xSCH_MATERIAL_CTRL->Get__MATERIAL_FROM_LPx(xx_port, xx_slot) < 1)
								{
									if(LLx__Check_Occupied__InSlot(ll_i) > 0)
									{
										if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") < 0)
										{
											if(SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "2") > 0)
											{
												xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
											}
										}
									}
								}
							}
						}

						xEXT_CH__LLx__PRE_MAINT_FLAG[ll_i]->Set__DATA("");
					}
				}
				else
				{
					if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)	
					{

					}
					else if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)	
					{
						if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
						{
							if(LLx__Check_All_Empty(ll_i) > 0)
							{
								SCH_RUN__LLx_VENT(ll_i, p_variable, log_id, "3.1");
							}
						}
					}
					else
					{
						if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
						{
							int req_vent = 1;

							if(LLx__Check_Occupied__InSlot(ll_i) > 0)
							{
								req_vent = -1;
							}

							if(req_vent > 0)
							{
								SCH_RUN__LLx_VENT(ll_i, p_variable, log_id, "3");
							}
						}
						else if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
						{
							int req_pump = -1;

							if((LLx__Check_Occupied__InSlot(ll_i) > 0)			
							&& (LLx__Get_Occupied__Total_OutSlot(ll_i) < 1))
							{
								req_pump = 1;
							}

							if(req_pump > 0)
							{
								SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "4");
							}
						}
					}
				}
			}
		}

		// ....
	}

	// LPx RETURN - CHECK ...
	for(i=0;i<iLPx_SIZE;i++)
	{
		if(xCH__LPx__RETURN_REQ_FLAG[i]->Check__DATA(STR__YES) < 0)
		{
			continue;
		}

		// ...
		{
			int lp_id = i + 1;

			int ll_limit = iLLx_SIZE;
			int ll_i;

			for(ll_i=0; ll_i<ll_limit; ll_i++)
			{
				if((LLx__Is_ATM(ll_i) < 0)
				&& (LLx__Is_Available(ll_i) > 0)
				&& (xEXT_CH__LLx__MOVE_FLAG[ll_i]->Check__DATA("YES") < 0))
				{
					int lb_in_slotid;

					if(LLx__Get_Occupied__InSlot(ll_i, lb_in_slotid) > 0)
					{
						IDS__SCH_MATERIAL_STATUS ds_info;
						CString lb_sch_name;
						
						CString ll_name = Get__LLx_NAME(ll_i);
						lb_sch_name.Format("%s-%1d", ll_name,lb_in_slotid);

						if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(lb_sch_name,ds_info) > 0)
						{
							if(ds_info.iPORT_ID == lp_id)
							{
								if(SCH_RUN__LLx_VENT(ll_i, p_variable, log_id, "1") > 0)
								{
									xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
								}
							}
						}
					}
				}
			}

			// ...
		}
	}	
}
void CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__Robot_Abort_Exception(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(ATM_RB__Is_Available() < 0)
	{
		NEXT__LOOP;
	}

	// ...
	int i;

	// ROBOT ARMx ...
	for(i=0; i<iLPx_SIZE; i++)
	{
		if(xCH__LPx__RETURN_REQ_FLAG[i]->Check__DATA(STR__YES) < 0)
		{
			continue;
		}
		
		int lp_id = i + 1;

		// ...
		CString arm_type;

		if(ATM_RB__Get_Occupied__Arm_Type(arm_type) > 0)
		{	
			IDS__SCH_MATERIAL_STATUS ds_sts;
			
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_sts) > 0)
			{
				if(ds_sts.iPORT_ID == lp_id)
				{
					xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(arm_type,STR__PROCESSED);

					NEXT__LOOP;
				}
			}
		}
	}
	
	// LBx ...
	for(i=0; i<iLPx_SIZE; i++)
	{
		if(xCH__LPx__RETURN_REQ_FLAG[i]->Check__DATA(STR__YES) < 0)
		{
			continue;
		}
		
		// ...
		int lp_id = i + 1;
			
		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if((LLx__Is_ATM(ll_i) > 0)
			&& (LLx__Is_Available(ll_i) > 0)
			&& (xEXT_CH__LLx__MOVE_FLAG[ll_i]->Check__DATA("YES") < 0))
			{
				int lb_in_slotid;
					
				if(LLx__Get_Occupied__InSlot(ll_i, lb_in_slotid) > 0)
				{
					IDS__SCH_MATERIAL_STATUS ds_info;
					CString para_module;
					CString para_slot;
					CString lb_sch_name;
						
					para_module = Get__LLx_NAME(ll_i);
					para_slot.Format("%1d",lb_in_slotid);
					lb_sch_name.Format("%s-%s", para_module,para_slot);
						
					if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(lb_sch_name,ds_info) > 0)
					{
						if(ds_info.iPORT_ID == lp_id)
						{
							if(ATM_RB__Check_Empty__Arm_Type() < 0)
							{
								Fnc__RB_TO_AL(p_variable,p_alarm);
							}

							Fnc__PICK_LBx_EXCEPTION(p_variable,p_alarm, para_module,para_slot);
							NEXT__LOOP;
						}
					}
				}

				// ...
				int lb_out_slotid;
						
				if(LLx__Get_Occupied__OutSlot(ll_i, lb_out_slotid) > 0)
				{
					IDS__SCH_MATERIAL_STATUS ds_info;
					CString para_module;
					CString para_slot;
					CString lb_sch_name;
							
					para_module = Get__LLx_NAME(ll_i);
					para_slot.Format("%1d",lb_out_slotid);
					lb_sch_name.Format("%s-%s", para_module,para_slot);
							
					if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(lb_sch_name,ds_info) > 0)
					{
						if(ds_info.iPORT_ID == lp_id)
						{
							if(ATM_RB__Check_Empty__Arm_Type() < 0)
							{
								Fnc__RB_TO_AL(p_variable,p_alarm);
							}
									
							Fnc__PICK_LBx_EXCEPTION(p_variable,p_alarm, para_module,para_slot);
							NEXT__LOOP;
						}
					}
				}
			}
		}
			
		// ...
	}	
}

void CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__Robot_Exception_Proc(CII_OBJECT__VARIABLE *p_variable,	CII_OBJECT__ALARM *p_alarm)
{
	if(ATM_RB__Is_Available() < 0)
	{
		NEXT__LOOP;
	}
	
	if((ATM_RB__Check_Empty__Arm_Type() > 0)
	&& (AL1__Check_Empty__All_Slot() > 0))
	{
		NEXT__LOOP;
	}

	// ...
	CString arm_type = ARM_A;

	if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) < 0)
	{
		NEXT__LOOP;
	}

	// ...
	{
		int out_flag = -1;

		CString para_module;
		CString para_slot;
		int slot_id;

		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(out_flag < 0)
			{
				if((xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
				&& (LLx__Check_Empty__InSlot(ll_i) < 0))
				{
					if((LLx__Is_ATM(ll_i) > 0)
					&& (LLx__Is_Available(ll_i) > 0))
					{
						if(LLx__Get_Occupied__OutSlot(ll_i, slot_id) > 0)
						{
							out_flag = 1;
						}
					}
				}
			}
		}
	
		if(out_flag < 0)
		{
			NEXT__LOOP;
		}
	}

	// RB -> AL ...
	Fnc__RB_TO_AL(p_variable,p_alarm);

	// LBo -> RB
	Fnc__LBo_To_RB(p_variable,p_alarm);
}

int  CObj_Fnc__SINGLE_ARM_STD
::Fnc__RB_TO_AL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString log_id = "Fnc__RB_TO_AL()";

	// ...
	CString para_module = MODULE__AL1;
	CString para_slot;
	int al_slot_id;
	
	// ...
	{
		if(AL1__Is_Available() < 0)
		{
			NEXT__LOOP;
		}
		
		if(AL1__Get_Empty__SlotID(al_slot_id) < 0)
		{
			NEXT__LOOP;
		}
		para_slot.Format("%1d",al_slot_id);
	}
	
	// ...
	CString arm_type = ARM_A;

	if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) < 0)
	{
		NEXT__LOOP;
	}
	
	// ...
	bool ex_flag = false;
	
	CString sch_module;
	sch_module.Format("%s-%s",para_module,para_slot);
	
	if(SCH__PLACE_MODULE(p_variable,
						 p_alarm,
						 log_id,
						 ex_flag,
						 arm_type,
						 para_module,
						 para_slot,
						 sch_module) < 0)
	{
		NEXT__LOOP;
	}

	// ...
	xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);
		
	if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_module) > 0)
	{
		xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_module,"MAPPED");
	}
	else
	{
		xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_module,STR__TO_LP);
	}
	return 1;
}

void CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__LBi_VENT(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "AUTO_CTRL__LBi_VENT()";

	// ...
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i>ll_limit; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) < 0)
		{
			if((LLx__Is_Available(ll_i) > 0)
			&& (LLx__Check_All_Empty(ll_i) > 0)
			&& (LLx__Is_ATM(ll_i) < 0))
			{
				if(xEXT_CH__LLx__MOVE_FLAG[ll_i]->Check__DATA("YES") < 0)
				{
					SCH_RUN__LLx_VENT(ll_i, p_variable, log_id, "1");
				}
			}
		}
	}
}
void CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__LBo_PUMP(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "AUTO_CTRL__LBo_PUMP()";
	
	// ...
	int atm_mode = -1;

	if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("ATM") > 0)
	{
		atm_mode = 1;
	}

	// ...
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
		{
			if((LLx__Is_Available(ll_i)    > 0)
			&& (LLx__Check_All_Empty(ll_i) > 0))
			{
				if(atm_mode > 0)			SCH_RUN__LLx_VENT(ll_i, p_variable, log_id, "1");
				else						SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "1");
			}
		}
	}
}

void CObj_Fnc__SINGLE_ARM_STD
::Start__LBi_VENT(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "Start__LBi_VENT()";

	// ...
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) < 0)
		{
			if((LLx__Is_ATM(ll_i)       < 0)
			&& (LLx__Is_Available(ll_i) > 0))
			{
				SCH_RUN__LLx_VENT(ll_i, p_variable, log_id, "1");
			}
		}
	}
}
void CObj_Fnc__SINGLE_ARM_STD
::Start__ALL_LBx_VENT(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "Start__ALL_LBx_VENT()";

	// ...
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if((LLx__Is_ATM(ll_i)       < 0)
		&& (LLx__Is_Available(ll_i) > 0))
		{
			Sleep(500);

			if(LLx__Is_Available(ll_i) > 0)
			{
				SCH_RUN__LLx_VENT(ll_i, p_variable, log_id, "1");
			}
		}
	}
}
void CObj_Fnc__SINGLE_ARM_STD
::Start__ALL_LBx_PUMP(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "Start__ALL_LBx_PUMP()";

	// ...
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if((LLx__Is_VAC(ll_i)       < 0)
		&& (LLx__Is_Available(ll_i) > 0))
		{
			Sleep(500);

			if(LLx__Is_Available(ll_i) > 0)
			{
				SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "1");
			}
		}
	}
}
void CObj_Fnc__SINGLE_ARM_STD
::Start__ALL_LBx_To_IDLE_STATE(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "Start__ALL_LBx_To_IDLE_STATE()";

	// ...
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if((LLx__Is_Available(ll_i) > 0)
		&& (xEXT_CH__LLx__MOVE_FLAG[ll_i]->Check__DATA("YES") < 0))
		{
			Sleep(500);
	
			if(xEXT_CH__SCH_DB_LLx_IDLE_STATUS[ll_i]->Check__DATA("VAC") > 0)
			{
				SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "1");
			}
			else if(xEXT_CH__SCH_DB_LLx_IDLE_STATUS[ll_i]->Check__DATA("ATM") > 0)
			{
				SCH_RUN__LLx_VENT(ll_i, p_variable, log_id, "1");
			}
		}
	}
}

void CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__LBi_PUMP__ONLY_MODE(CII_OBJECT__VARIABLE *p_variable)
{
	CString log_id = "AUTO_CTRL__LBi_PUMP__ONLY_MODE()";

	// ...
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
		{
			if((ATM_RB__Check_Empty__Arm_Type() > 0)
			&& (AL1__Check_Empty__All_Slot() > 0)
			&& (xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS() < 0))
			{
				if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
				{
					if((LLx__Is_Available(ll_i) > 0)
					&& (LLx__Check_All_Empty(ll_i) < 0)
					&& (LLx__Is_ATM(ll_i) > 0))
					{
						if(SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "1") > 0)
						{
							xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
						}
					}
				}
			}
		}
	}

	// ...
}
void CObj_Fnc__SINGLE_ARM_STD
::AUTO_CTRL__LBx_PUMP__ALL_MODE(CII_OBJECT__VARIABLE *p_variable)
{
	CString log_id = "AUTO_CTRL__LBx_PUMP__ALL_MODE()";

	if((xEXT_CH__SCH_DB_LLx_MODE_TYPE[0]->Check__DATA(LBx_MODE__ALL) < 0)
	|| (xEXT_CH__SCH_DB_LLx_MODE_TYPE[1]->Check__DATA(LBx_MODE__ALL) < 0))
	{
		NEXT__LOOP;
	}

	if(ATM_RB__Is_Available() < 0)
	{
		NEXT__LOOP;
	}

	if(sEXT_CH__SCH_MODE_LLx_OUT->Check__DATA(_SCH_MODE__ROUTE) > 0)
	{
		if(xSCH_MATERIAL_CTRL->Check__MATERIAL_OF_LLx_OUT(-1,1,true) > 0)
		{
			NEXT__LOOP;
		}
		if(xSCH_MATERIAL_CTRL->Check__MATERIAL_OF_LLx_OUT(-1,2,true) > 0)
		{
			NEXT__LOOP;
		}
	}

	// LBA & LBB : InSlot Check ...
	{
		int k_limit = 2;
		int k;

		for(k=0; k<k_limit; k++)
		{
			int ll_i = -1;

			if(xCH__ATM_RB__SCH_STS_TO_LLx[k]->Check__DATA("") > 0)
			{
				ll_i = _LLx_INDEX__LBA + k;
			}
			else
			{
				continue;
			}

			if(LLx__Is_Available(ll_i) > 0)
			{
				if((LLx__Get_Occupied__Total_OutSlot(ll_i) < 1)
				&& (LLx__Get_Occupied__Total_InSlot(ll_i)  > 0))
				{
					int lb_slotid;

					if(LLx__Get_Occupied__InSlot(ll_i, lb_slotid) > 0)
					{
						CString lb_sch_name;
						CString ll_name = Get__LLx_NAME(ll_i);

						lb_sch_name.Format("%s-%1d", ll_name,lb_slotid);

						if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(lb_sch_name) > 0)
						{
							if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") < 0)
							{
								if(SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "1") > 0)
								{
									xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");	
								}
							}
						}
					}
				}
			}
		}

		// ...
	}

	// ATM Robot ...
	if(ATM_RB__Check_Occupied__Arm_Type() > 0)
	{
		NEXT__LOOP;
	}

	// AL1 ...
	if(AL1__Is_Available() > 0)
	{
		if(AL1__Check_Empty__All_Slot() < 0)
		{
			NEXT__LOOP;
		}
	}

	// VAC Robot : Out Material Count ...
	{
		CString var_data;

		xEXT_CH__VAC_ROBOT_OUT_MATERIAL_COUNT->Get__DATA(var_data);
		int count = atoi(var_data);

		if(count < 1)
		{
			NEXT__LOOP;
		}
	}

	// ...
	DECLARE__EXT_CTRL(p_variable);

	if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS() < 0)
	{
		if(xSCH_MATERIAL_CTRL->Check__MATERIAL_MORE_THAN_MOVE_COUNT(1) == 1)
		{
			int lbx_count = 0;

			int ll_limit = iLLx_SIZE;
			int ll_i;

			for(ll_i=0; ll_i<ll_limit; ll_i++)
			{
				if(xEXT_CH__SCH_DB_LLx_USE_FLAG[ll_i]->Check__DATA(STR__ENABLE) > 0)
				{
					if((pLLx__OBJ_CTRL[ll_i]->Is__OBJ_BUSY() > 0)
					|| (LLx__Is_VAC(ll_i) > 0))
					{
						lbx_count++;
					}
				}
			}

			if(lbx_count > 0)
			{
				NEXT__LOOP;
			}
		}
	}

	// LLx ...
	{
		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
			{
				if((LLx__Is_Available(ll_i) > 0)
				&& (LLx__Check_All_Empty(ll_i) > 0)
				&& (LLx__Is_ATM(ll_i) < 0))
				{
					NEXT__LOOP;
				}		
			}
		}
	}

	// ATM_RB ...
	{
		int k_limit = 2;
		int k;

		for(k=0; k<k_limit; k++)
		{
			int ll_i = -1;

			if(xCH__ATM_RB__SCH_STS_TO_LLx[k]->Check__DATA("") > 0)
			{
				ll_i = _LLx_INDEX__LBA + k;
			}
			else
			{
				continue;
			}

			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
			{
				if((LLx__Is_Available(ll_i) > 0)
				&& (LLx__Check_All_Empty(ll_i) > 0)
				&& (LLx__Is_ATM(ll_i) > 0))
				{
					if(SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "11") > 0)
					{
						xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
					}
				}
			}
		}
	}

	// ...
}
int  CObj_Fnc__SINGLE_ARM_STD
::Seq__LBx_VENT__ALL_MODE(CII_OBJECT__VARIABLE *p_variable)
{
	if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[0]->Check__DATA(LBx_MODE__ALL) < 0)		return -1;
	if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[1]->Check__DATA(LBx_MODE__ALL) < 0)		return -1;

	CString log_id = "Seq__LBx_VENT__ALL_MODE()";

	// ...
	DECLARE__EXT_CTRL(p_variable);

	// ...
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if((LLx__Is_Available(ll_i)    > 0)
		&& (LLx__Check_All_Empty(ll_i) > 0))
		{
			if(LLx__Is_ATM(ll_i) < 0)
			{
				if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
				{
					return -1;
				}

				if(SCH_RUN__LLx_VENT(ll_i, p_variable, log_id, "1") > 0)
				{
					xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
				}
				return 1;
			}
			else
			{
				return -1;
			}
		}
	}

	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD
::Seq__LBx_VENT__INTO_LBi(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "Seq__LBx_VENT__INTO_LBi()";

	// ...
	int ll_limit = iLLx_SIZE;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ALL) < 0)
		{
			return -1;
		}

		if((xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
		&& (LLx__Is_Available(ll_i)    < 0)
		&& (LLx__Check_All_Empty(ll_i) > 0))
		{
			return -1;
		}

		if((xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
		&& (LLx__Is_Available(ll_i)    > 0)
		&& (LLx__Check_All_Empty(ll_i) > 0)
		&& (LLx__Is_ATM(ll_i) > 0))
		{
			return -1;
		}

		if((xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
		&& (LLx__Is_Available(ll_i)    > 0)
		&& (LLx__Check_All_Empty(ll_i) > 0)
		&& (LLx__Is_VAC(ll_i) > 0))
		{
			if(SCH_RUN__LLx_VENT(ll_i, p_variable, log_id, "1") > 0)
			{
				xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
			}
			return 1;
		}
	}

	return -1;
}


//------------------------------------------------------------------------------------------------
int  CObj_Fnc__SINGLE_ARM_STD::Fnc__AUTO_CTRL__ERROR()
{

	return -1;
}


//------------------------------------------------------------------------------------------------
// LPx -> ATM_RB
int  CObj_Fnc__SINGLE_ARM_STD
::Fnc__PICK_LPi(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm,
				  const int port_id,
				  const int slot_id,
				  const int ll_id,
				  CString& arm_type)
{
	CString log_id = "Fnc__PICK_LPi()";

	// ...
	int lp_i = port_id - 1;
	
	if(LPx__Is_Available(lp_i) < 0)
	{
		NEXT__LOOP;
	}

	if(AL1__Check_Empty__All_Slot() > 0)
	{
		if(ATM_RB__Get_Empty__Arm_Type(arm_type) < 0)
		{
			NEXT__LOOP;
		}
	}
	else
	{
		int al_slot_id;

		if(AL1__Get_Empty__SlotID(al_slot_id) < 0)
		{
			NEXT__LOOP;
		}
		if(ATM_RB__Get_Empty__Arm_Type(arm_type) < 0)
		{
			NEXT__LOOP;
		}
	}

	if(xEXT_CH__SCH_ALIGN_DEVICE->Check__DATA(STR__ATM_RB) > 0)
	{
		if(SCH__CAN_PLACE_LBi() < 0)
		{
			NEXT__LOOP;
		}
	}

	// ...
	CString para_module;
	CString para_slot;

	para_module.Format("LP%1d",port_id);
	para_slot.Format("%1d",slot_id);

	CString sch_module;
	sch_module.Format("LP%1d-%1d",port_id,slot_id);

	// LLx ...
	{
		int ll_i = ll_id - 1;

		if((ll_i >= 0) && (ll_i < iLLx_SIZE))
		{
			xCH__ATM_RB__SCH_STS_TO_LLx[ll_i]->Set__DATA("YES");
		}
	}

	if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,arm_type,para_module,para_slot,sch_module) < 0)
	{
		// LLx ...
		{
			int ll_i = ll_id - 1;

			if((ll_i >= 0) && (ll_i < iLLx_SIZE))
			{
				xCH__ATM_RB__SCH_STS_TO_LLx[ll_i]->Set__DATA("");
			}
		}
		return -1;
	}

	// ...
	{
		int db_index = port_id - 1;
		
		if((db_index >= 0) && (db_index < iLPx_SIZE))
		{
			CString var_data;
			int i_count;
			
			xCH__LPx__PICK_COUNT[db_index]->Get__DATA(var_data);
			i_count = atoi(var_data) + 1;
			var_data.Format("%1d", i_count);
			xCH__LPx__PICK_COUNT[db_index]->Set__DATA(var_data);
		}
	}

	// ...
	{
		xSCH_MATERIAL_CTRL->Pick__From_LPx(port_id,slot_id,arm_type);
	
		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(port_id,slot_id) > 0)
		{
			if(xEXT_CH__SCH_DB_AL1_USE_FLAG->Check__DATA(STR__ENABLE) < 0)
			{
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(port_id,slot_id,"ALIGNED");
			}
		}
		else
		{
			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(port_id,slot_id,STR__TO_LP);
		}
	}

	if(Fnc__Check_ARM_WAFER_INFO_MISMATCH(p_variable,p_alarm, arm_type) < 0)
	{
		NEXT__LOOP;
	}
	return 1;
}
int  CObj_Fnc__SINGLE_ARM_STD
::Fnc__Check_ARM_WAFER_INFO_MISMATCH(CII_OBJECT__VARIABLE *p_variable,
									   CII_OBJECT__ALARM *p_alarm,
									   const CString& arm_type)
{
	CString wfr_title; 

	if(ATM_RB__Get_Occupied__Wfr_Title_Of_Arm_Type(arm_type, wfr_title) < 0)
	{
		return -1;
	}
	
	// ...
	{
		int wfr_ptn;
		int wfr_slot;		
		Macro__Analyze_Title_Info(wfr_title, wfr_ptn,wfr_slot);
		
		IDS__SCH_MATERIAL_INFO ds_info;
		xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(arm_type,ds_info);
		
		if((wfr_ptn  != ds_info.iSRC__PTN)
		|| (wfr_slot != ds_info.iSRC__STN))
		{
			xCH__ATM_RB_PAUSE_FLAG->Set__DATA(STR__YES);
			
			// ...
			{
				CString alarm_msg;
				CString r_act;
				
				alarm_msg.Format("Wafer Info (%1d:%1d) is different from SCH DB(%1d:%1d)\n",
								 wfr_ptn,wfr_slot,
								 ds_info.iSRC__PTN,ds_info.iSRC__STN);
				
				p_alarm->Popup__ALARM_With_MESSAGE(ALID__JOB_ERROR__WAFER_INFO_MISMATCH,alarm_msg,r_act);
			}
			
			return -1;
		}
	}

	return 1;
}

// LPx -> ATM_RB
int  CObj_Fnc__SINGLE_ARM_STD
::Fnc__PICK_LPi_In_BUFFER_MODE(CII_OBJECT__VARIABLE *p_variable,
								 CII_OBJECT__ALARM *p_alarm,
								 const int port_id,
								 const int slot_id,
								 const int ll_id,
								 CString& arm_type)
{
	CString log_id = "Fnc__PICK_LPi_In_BUFFER_MODE()";

	// ...
	int lp_i = port_id - 1;
	
	if(LPx__Is_Available(lp_i) < 0)
	{
		NEXT__LOOP;
	}

	if(ATM_RB__Get_Empty__Arm_Type(arm_type) < 0)
	{
		NEXT__LOOP;
	}

	// ...
	CString para_module;
	CString para_slot;

	para_module.Format("LP%1d",port_id);
	para_slot.Format("%1d",slot_id);

	// ...
	CString sch_module;
	sch_module.Format("LP%1d-%1d",port_id,slot_id);

	if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,arm_type,para_module,para_slot,sch_module) < 0)
	{
		return -1;
	}

	// ...
	{
		int db_index = port_id - 1;

		if((db_index >= 0) && (db_index < iLPx_SIZE))
		{
			CString var_data;
			int i_count;

			xCH__LPx__PICK_COUNT[db_index]->Get__DATA(var_data);
			i_count = atoi(var_data) + 1;
			var_data.Format("%1d", i_count);
			xCH__LPx__PICK_COUNT[db_index]->Set__DATA(var_data);
		}
	}

	// LLx ...
	{
		int ll_i = ll_id - 1;

		if((ll_i >= 0) && (ll_i < iLLx_SIZE))
		{
			xCH__ATM_RB__SCH_STS_TO_LLx[ll_i]->Set__DATA("YES");
		}
	}

	// ...
	{
		xSCH_MATERIAL_CTRL->Pick__From_LPx(port_id,slot_id,arm_type);

		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(port_id,slot_id) > 0)
		{
			if(xEXT_CH__SCH_DB_AL1_USE_FLAG->Check__DATA(STR__ENABLE) < 0)
			{
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(port_id,slot_id,"ALIGNED");
			}
		}
		else
		{
			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(port_id,slot_id,STR__TO_LP);
		}
	}

	if(Fnc__Check_ARM_WAFER_INFO_MISMATCH(p_variable,p_alarm, arm_type) < 0)
	{
		NEXT__LOOP;
	}
	return 1;
}

// ATM_RB -> ALx
int  CObj_Fnc__SINGLE_ARM_STD
::Fnc__PLACE_AL(CII_OBJECT__VARIABLE *p_variable,
				CII_OBJECT__ALARM *p_alarm,
				const CString& log_xx,
				const CString& arm_type,
				const int al_start_flag)
{
	CString log_id = log_xx;
	log_id += " -> ";
	log_id += "Fnc__PLACE_AL()";

	// ...
	CString para_module = MODULE__AL1;
	CString para_in_slot;
	CString para_out_slot;
	int al_slot_id;

	if(AL1__Is_Available() < 0)
	{
		NEXT__LOOP;
	}

	if(AL1__Get_Occupied__SlotID(al_slot_id) > 0)
	{
		para_out_slot.Format("%1d",al_slot_id);
	}

	if(AL1__Get_Empty__SlotID(al_slot_id) < 0)
	{
		NEXT__LOOP;
	}
	
	para_in_slot.Format("%1d",al_slot_id);

	// ...
	bool ex_flag = false;
	
	if(para_out_slot.GetLength() > 0)
	{
		ex_flag = true;
	}
	
	if(xEXT_CH__SCH_ALIGN_DEVICE->Check__DATA(STR__ATM_RB) > 0)
	{
		CString sch_module;
		sch_module.Format("%s-%s",para_module,para_in_slot);

		if(SCH__PLACE_MODULE(p_variable,
							 p_alarm,
							 log_id,
							 ex_flag,
							 arm_type,
							 para_module,
							 para_in_slot,
							 sch_module) < 0)
		{
			return -1;
		}

		// ...
		{
			xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);
		
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_module) > 0)
			{
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_module,"ALIGNED");
			}
			else
			{
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_module,STR__TO_LP);
			}
		}

		// ...
		{
			if(xCH__ATM_RB__TARGET_LLx_MODE->Check__DATA(STR__ENABLE) > 0)
			{
				CString ll_slot;
				CString ll_name = SCH__Get_LBx_To_PLACE(ll_slot);
				
				if(ll_name.GetLength() < 1)		NEXT__LOOP;
				
				xCH__ATM_RB__TARGET_LLx_NAME_SET->Set__DATA(ll_name);
				xCH__ATM_RB__TARGET_LLx_SLOT_SET->Set__DATA(ll_slot);
			}
			else
			{
				xCH__ATM_RB__TARGET_LLx_NAME_SET->Set__DATA("");
				xCH__ATM_RB__TARGET_LLx_SLOT_SET->Set__DATA("");
			}
		}

		if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,arm_type,para_module,para_in_slot,sch_module) < 0)
		{
			return -1;
		}

		xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,arm_type);
	}
	else
	{
		// ...
		{
			if(xCH__ATM_RB__TARGET_LLx_MODE->Check__DATA(STR__ENABLE) > 0)
			{
				CString ll_slot;
				CString ll_name = SCH__Get_LBx_To_PLACE(ll_slot);
				
				if(ll_name.GetLength() < 1)			NEXT__LOOP;
				
				xCH__ATM_RB__TARGET_LLx_NAME_SET->Set__DATA(ll_name);
				xCH__ATM_RB__TARGET_LLx_SLOT_SET->Set__DATA(ll_slot);
			}
			else
			{
				xCH__ATM_RB__TARGET_LLx_NAME_SET->Set__DATA("");
				xCH__ATM_RB__TARGET_LLx_SLOT_SET->Set__DATA("");
			}
		}

		if((ex_flag == true)
		&& (xCH_CFG__ALx_SWAP_FLAG->Check__DATA(STR__ENABLE) > 0)
		&& (al_start_flag > 0))
		{
			CString sch_place_module;
			CString sch_pick_module;

			sch_place_module.Format("%s-%s",para_module,para_in_slot );
			sch_pick_module.Format( "%s-%s",para_module,para_out_slot);

			if(Fnc__SWAP_ALx(p_variable,
							 para_module,
							 arm_type,
							 para_in_slot,
							 arm_type,
							 para_out_slot,
							 sch_place_module,
							 sch_pick_module) < 0)
			{
				xEXT_CH__JOB_CTRL->Set__DATA("Abort");

				// ...
				int alarm_id = ALID__SWAP_ERROR;
				CString alarm_msg;
				CString r_act;

				alarm_msg.Format("Swap Error occured when ATM-Robot is swaping with %s.\n",para_module);

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alarm_msg);

				Sleep(990);
				xSCH_MATERIAL_CTRL->Clear__ALL_MATERIAL_INFO();

				NEXT__LOOP;			
			}
		}
		else
		{
			CString sch_module;
			sch_module.Format("%s-%s",para_module,para_in_slot);

			if(SCH__PLACE_MODULE(p_variable,
								 p_alarm,
								 log_id,
								 ex_flag,
								 arm_type,
								 para_module,
								 para_in_slot,
								 sch_module) < 0)
			{
				return -1;
			}

			// ...
			{
				xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);

				if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_module) > 0)
				{
					if(al_start_flag > 0)
					{
						xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_module,"ALIGNED");
					}
				}
				else
				{
					xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_module,STR__TO_LP);
				}
			}
			
			// ...
			if(ex_flag == false)			NEXT__LOOP;
			if(AL1__Is_Available() < 0)		NEXT__LOOP;

			CString empty_arm;

			if(ATM_RB__Get_Empty__Arm_Type(empty_arm) < 0)
			{
				NEXT__LOOP;
			}

			sch_module.Format("%s-%s",para_module,para_out_slot);

			if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,empty_arm,para_module,para_out_slot,sch_module) < 0)
			{
				return -1;
			}

			xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,empty_arm);
		}
	
		if(ex_flag == true)
		{
			if(al_start_flag > 0)
			{
				SCH__ALIGN(p_variable,para_in_slot);
			}
		}
	}

	return 1;
}

// ATM_RB -> BUFFERx
int  CObj_Fnc__SINGLE_ARM_STD
::Fnc__PLACE_BUFFERx(CII_OBJECT__VARIABLE *p_variable,
					   CII_OBJECT__ALARM *p_alarm,
					   const CString& arm_type,
					   const CString& bff_name,
					   const int bff_slot,
					   const CString& bff_lotid)
{
	CString log_id;
	log_id.Format("Fnc__PLACE_BUFFERx() - LotID(%s)", bff_lotid);

	// ...
	{
		CStringArray l_id;
		CStringArray l_mode;
		CStringArray l_slot; 
		CStringArray l_sec;

		if(xSCH_MATERIAL_CTRL->Get__STx_OF_EDIT_TYPE(arm_type, l_id,l_mode,l_slot,l_sec) > 0)
		{
			int i_limit = l_id.GetSize();

			for(int i=0; i<i_limit; i++)
			{
				int stx_id = atoi(l_id[i]);
				CString str_sec = l_sec[i];

					 if(stx_id == 1)		xCH__SCH_DB_ST1_WAFER_CLEAN_TIME->Set__DATA(str_sec);
				else if(stx_id == 2)		xCH__SCH_DB_ST2_WAFER_CLEAN_TIME->Get__DATA(str_sec);
			}
		}
	}

	// ...
	{
		CString var_data;
		
		xCH__SCH_DB_ST1_WAFER_CLEAN_TIME->Get__DATA(var_data);
		xEXT_CH__BUFFER1__CFG_SLOT_WAIT_SEC->Set__DATA(var_data);

		xCH__SCH_DB_ST2_WAFER_CLEAN_TIME->Get__DATA(var_data);
		xEXT_CH__BUFFER2__CFG_SLOT_WAIT_SEC->Set__DATA(var_data);
	}

	CString sch_module;
	CString para_module;
	CString para_slot;

	// ...
	{
		para_module = bff_name;
		para_slot.Format("%1d", bff_slot);

		sch_module.Format("%s-%s", para_module,para_slot);
	}

	if(SCH__PLACE_MODULE(p_variable,
						 p_alarm,
						 log_id,
						 false,
						 arm_type,
						 para_module,
						 para_slot,
						 sch_module) < 0)
	{
		return -1;
	}

	// ...
	{
		xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);
		xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_module,STR__TO_LP);
	}

	// ...
	{
		int slot_index = bff_slot - 1;

		if((slot_index >= 0) && (slot_index < CFG_LP__SLOT_MAX))
		{
			CString var_data;
			
			if(bff_name.CompareNoCase(MODULE__BUFFER1) == 0)
			{
				xCH__SCH_DB_ST1_WAFER_CLEAN_TIME->Get__DATA(var_data);
				xEXT_CH__BUFFER1__SLOT_WAIT_SEC[slot_index]->Set__DATA(var_data);
			}
			else if(bff_name.CompareNoCase(MODULE__BUFFER2) == 0)
			{
				xCH__SCH_DB_ST2_WAFER_CLEAN_TIME->Get__DATA(var_data);
				xEXT_CH__BUFFER2__SLOT_WAIT_SEC[slot_index]->Set__DATA(var_data);
			}
		}
	}
	return 1;
}

// EXCEPTION : LBin -> ATM_RB
int  CObj_Fnc__SINGLE_ARM_STD
::Fnc__PICK_LBx_EXCEPTION(CII_OBJECT__VARIABLE *p_variable,
							CII_OBJECT__ALARM *p_alarm,
							const CString& para_module,
							const CString& para_slot)
{
	CString log_id = "Fnc__PICK_LBx_EXCEPTION()";

	// ...
	{
		if(ATM_RB__Is_Available() < 0)					NEXT__LOOP;
		if(ATM_RB__Check_Empty__Arm_Type() < 0)			NEXT__LOOP;
	}

	// ...
	{
		CString arm_type = ARM_A;
		CString sch_module;

		// ...
		{
			sch_module.Format("%s-%s", para_module,para_slot);

			if(Get__LPx_SideBuffer_Info_To_Use(sch_module) < 0)
			{
				NEXT__LOOP;
			}

			if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,arm_type,para_module,para_slot,sch_module) < 0)
			{
				NEXT__LOOP;
			}
		}
		
		xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,arm_type);
			
		// ...
		{
			CString pmc_name;
			CString pmc_rcp;

			if(xSCH_MATERIAL_CTRL->Get__Last_Processing_Info(arm_type,pmc_name,pmc_rcp) > 0)
			{
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(arm_type,STR__PROCESSED);
			}	
			else
			{
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(arm_type,STR__TO_LP);
			}
		}
	}

	return 1;
}
	
// ALx -> ATM_RB
int  CObj_Fnc__SINGLE_ARM_STD
::Fnc__PICK_AL(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm,
				 CString& arm_type)
{
	CString log_id = "Fnc__PICK_AL()";

	// ...
	if(AL1__Is_Available() < 0)
	{
		NEXT__LOOP;
	}
	if(AL1__Check_Empty__All_Slot() > 0)
	{
		NEXT__LOOP;
	}

	if(ATM_RB__Get_Empty__Arm_Type(arm_type) < 0)
	{
		NEXT__LOOP;
	}

	// ...
	CString para_module = MODULE__AL1;
	CString para_slot;
	int al_slot_id;

	if(AL1__Get_Occupied__SlotID(al_slot_id) < 0)
	{
		NEXT__LOOP;
	}
	para_slot.Format("%1d",al_slot_id);

	// ...
	{
		CString sch_module;
		sch_module.Format("%s-%s",para_module,para_slot);

		if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,arm_type,para_module,para_slot,sch_module) < 0)
		{
			NEXT__LOOP;
		}

		xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,arm_type);

		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
		{
			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(arm_type,"ALIGNED");
		}
		else
		{
			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(arm_type,STR__TO_LP);
		}
	}
	return 1;
}
int  CObj_Fnc__SINGLE_ARM_STD
::Fnc__PICK_AL_TO_RB(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_id = "Fnc__PICK_AL_TO_RB()";

	// ...
	if(xCH__ATM_RB__TARGET_LLx_MODE->Check__DATA(STR__ENABLE) > 0)
	{
		CString ll_slot;
		CString ll_name = SCH__Get_LBx_To_PLACE(ll_slot);
		
		if(ll_name.GetLength() < 1)			NEXT__LOOP;
		
		xCH__ATM_RB__TARGET_LLx_NAME_SET->Set__DATA(ll_name);
		xCH__ATM_RB__TARGET_LLx_SLOT_SET->Set__DATA(ll_slot);
	}
	else
	{
		xCH__ATM_RB__TARGET_LLx_NAME_SET->Set__DATA("");
		xCH__ATM_RB__TARGET_LLx_SLOT_SET->Set__DATA("");
	}

	if(AL1__Is_Available() < 0)
	{
		NEXT__LOOP;
	}
	if(AL1__Check_Empty__All_Slot() > 0)
	{
		NEXT__LOOP;
	}

	// ...
	CString arm_type;

	if(ATM_RB__Get_Empty__Arm_Type(arm_type) < 0)
	{
		NEXT__LOOP;
	}

	// ...
	CString para_module = MODULE__AL1;
	CString para_slot;
	int al_slot_id;
	
	if(AL1__Get_Occupied__SlotID(al_slot_id) < 0)
	{
		NEXT__LOOP;
	}
	para_slot.Format("%1d",al_slot_id);
	
	// ...
	{
		CString sch_module;
		sch_module.Format("%s-%s",para_module,para_slot);
		
		if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,arm_type,para_module,para_slot,sch_module) < 0)
		{
			NEXT__LOOP;
		}
		
		xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,arm_type);
		
		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
		{
			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(arm_type,"ALIGNED");
		}
		else
		{
			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(arm_type,STR__TO_LP);
		}
	}
	return 1;
}

// ATM_RB -> LBi
int  CObj_Fnc__SINGLE_ARM_STD::
Fnc__PLACE_LBi(CII_OBJECT__VARIABLE *p_variable,
			   CII_OBJECT__ALARM *p_alarm,
			   const bool ex_flag,
			   const CString& arm_type)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "Fnc__PLACE_LBi()";

	// ...
	CString para_module;
	CString para_slot;
	int slot_id;

	// LLx ...
	if(sEXT_CH__SCH_MODE_LLx_IN->Check__DATA(_SCH_MODE__ROUTE) > 0)
	{
		CStringArray l_ll_id;
		CStringArray l_ll_mode;
		CStringArray l_ll_slot;

		xSCH_MATERIAL_CTRL->Get__LLx_IN_OF_EDIT_TYPE(arm_type, l_ll_id,l_ll_mode,l_ll_slot);

		// ...
		int active__ll_only_input = -1;

		int i_limit = l_ll_id.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			int ll_i = atoi(l_ll_id[i]) - 1;

			if(ll_i <  0)				continue;
			if(ll_i >= iLLx_SIZE)		continue;

			if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) < 0)
			{
				continue;
			}

			if(LLx__Is_Available(ll_i) < 0)						continue;
			if(LLx__Get_Empty__InSlot(ll_i, slot_id) < 0)		continue;

			if(LLx__Is_ATM(ll_i) < 0)
			{
				if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") < 0)
				{
					SCH_RUN__LLx_VENT(ll_i, p_variable, log_id, "1");
				}
				continue;
			}

			// ...
			para_module = Get__LLx_NAME(ll_i);
			para_slot.Format("%1d", slot_id);

			active__ll_only_input = 1;
			break;
		}

		if(active__ll_only_input < 0)
		{
			NEXT__LOOP;
		}
	}
	else
	{
		int active__ll_only_input = -1;

		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
			{
				if(LLx__Is_Available(ll_i) < 0)						continue;
				if(LLx__Get_Empty__InSlot(ll_i, slot_id) < 0)		continue;

				if(LLx__Is_ATM(ll_i) < 0)
				{
					if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") < 0)
					{
						SCH_RUN__LLx_VENT(ll_i, p_variable, log_id, "1");
					}
					continue;
				}

				// ...
				active__ll_only_input = 1;

				para_module = Get__LLx_NAME(ll_i);
				para_slot.Format("%1d", slot_id);
			}

			if(active__ll_only_input > 0)
			{
				break;
			}
		}

		if(active__ll_only_input < 0)
		{
			NEXT__LOOP;
		}
	}

	// ...
	{
		CString sch_module;
		sch_module.Format("%s-%s", para_module,para_slot);

		if(SCH__PLACE_MODULE(p_variable,
							 p_alarm,
							 log_id,
							 ex_flag,
							 arm_type,
							 para_module,
							 para_slot,
							 sch_module) < 0)
		{
			return -1;
		}

		xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);
	}
	
	// ...
	{
		int ll_i = Get__LLx_INDEX(para_module);

		if(ll_i >= 0)
		{			
			CString str_data;

			str_data.Format("%1d", ++iLLx_IN_COUNT);
			xEXT_CH__LLx__IN_COUNT[ll_i]->Set__DATA(str_data);
		}
	}

	if(ex_flag == true)
	{
		return 1;
	}

	Fnc__PUMP_LBi(p_variable,para_module);
	return 1;
}
int CObj_Fnc__SINGLE_ARM_STD::
Fnc__PUMP_LBi(CII_OBJECT__VARIABLE *p_variable,
			  const CString& para_module)
{
	CString log_id = "Fnc__PUMP_LBi()";

	// ...
	int ll_i = Get__LLx_INDEX(para_module);

	if(ll_i >= 0)
	{
		if(LLx__Check_Empty__InSlot(ll_i) < 0)
		{
			if(SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "1") > 0)
			{
				xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
			}
		}
		else
		{
			if((ATM_RB__Check_Empty__Arm_Type() > 0)
			&& (AL1__Check_Empty__All_Slot()    > 0))
			{
				if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS() < 0)
				{
					if(SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "2") > 0)
					{
						xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
					}
				}
			}
		}

		NEXT__LOOP;
	}
	
	return 1;
}


int CObj_Fnc__SINGLE_ARM_STD::
Fnc__SWAP_ALx(CII_OBJECT__VARIABLE *p_variable,
			  const CString& para_module,
			  const CString& place_arm,
			  const CString& place_slot,
			  const CString& pick_arm,
			  const CString& pick_slot,
			  const CString& sch_place_module,
			  const CString& sch_pick_module)
{
	// ...
	{
		Datalog__Placing_Material(place_arm,para_module,place_slot,1);
		Datalog__Picking_Material(pick_arm,para_module,pick_slot,1);

		xSCH_MATERIAL_CTRL->Transfer_Start__To_MODULE(place_arm,sch_place_module);
		xSCH_MATERIAL_CTRL->Transfer_Start__To_MODULE(sch_pick_module,pick_arm);
	}

	if(Fnc__Seq_SWAP_ALx(p_variable,
						 place_arm,
						 pick_arm,
						 para_module,
						 place_slot,
						 pick_slot) < 0)
	{
		return -1;
	}

	// ...
	{
		Datalog__Placed_Material(place_arm,para_module,place_slot,-1);
		Datalog__Picked_Material(pick_arm,para_module,pick_slot,-1);

		xSCH_MATERIAL_CTRL->Transfer_End__To_MODULE(place_arm,sch_place_module);
		xSCH_MATERIAL_CTRL->Transfer_End__To_MODULE(sch_pick_module,pick_arm);
	}

	// ...
	{
		xSCH_MATERIAL_CTRL->Place__To_MODULE(place_arm,sch_place_module);

		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_place_module) > 0)
		{
			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_place_module,"ALIGNED");
		}
		else
		{
			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_place_module,STR__TO_LP);
		}
	}

	// ...
	{
		xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_pick_module,pick_arm);
	}
	return 1;
}
int CObj_Fnc__SINGLE_ARM_STD::
Fnc__Seq_SWAP_ALx(CII_OBJECT__VARIABLE *p_variable,
				  const CString& place_arm,
			      const CString& pick_arm,
				  const CString& para_module,
				  const CString& place_slot,
				  const CString& pick_slot)
{
	DECLARE__EXT_CTRL(p_variable);
	

	//.....
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(para_module);
	
	l_para.Add(place_arm);
	l_para.Add(place_slot);

	l_para.Add(pick_arm);
	l_para.Add(pick_slot);
	//

	return pATM_RB__OBJ_CTRL->Call__OBJ_MODE("SWAP_ALx",l_para);
}

int CObj_Fnc__SINGLE_ARM_STD::
Fnc__SWAP_LBx(CII_OBJECT__VARIABLE *p_variable,
			  CII_OBJECT__ALARM    *p_alarm,
			  const CString& para_module,
			  const CString& place_arm,
			  const CString& place_slot,
			  const CString& pick_arm,
			  const CString& pick_slot,
			  const CString& sch_place_module,
			  const CString& sch_pick_module)
{
	// ...
	{
		Datalog__Placing_Material(place_arm,para_module,place_slot,1);
		Datalog__Picking_Material(pick_arm,para_module,pick_slot,1);

		xSCH_MATERIAL_CTRL->Transfer_Start__To_MODULE(place_arm,sch_place_module);
		xSCH_MATERIAL_CTRL->Transfer_Start__To_MODULE(sch_pick_module,pick_arm);
	}

	if(Fnc__Seq_SWAP_LBx(p_variable,
						 place_arm,
						 pick_arm,
						 para_module,
						 place_slot,
						 pick_slot) < 0)
	{
		return -1;
	}

	// ...
	{
		Datalog__Placed_Material(place_arm,para_module,place_slot,-1);
		Datalog__Picked_Material(pick_arm,para_module,pick_slot,-1);

		xSCH_MATERIAL_CTRL->Transfer_End__To_MODULE(place_arm,sch_place_module);
		xSCH_MATERIAL_CTRL->Transfer_End__To_MODULE(sch_pick_module,pick_arm);
	}
	

	// ...
	{
		xSCH_MATERIAL_CTRL->Place__To_MODULE(place_arm,sch_place_module);

		xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_pick_module,pick_arm);
	}

	// ...
	{
		Fnc__PUMP_LBi(p_variable,para_module);
	}

	return 1;
}
int CObj_Fnc__SINGLE_ARM_STD::
Fnc__Seq_SWAP_LBx(CII_OBJECT__VARIABLE *p_variable,
				  const CString& place_arm,
			      const CString& pick_arm,
				  const CString& para_module,
				  const CString& place_slot,
				  const CString& pick_slot)
{
	DECLARE__EXT_CTRL(p_variable);
	

	//.....
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(para_module);
	
	l_para.Add(place_arm);
	l_para.Add(place_slot);

	l_para.Add(pick_arm);
	l_para.Add(pick_slot);
	//

	return pATM_RB__OBJ_CTRL->Call__OBJ_MODE("SWAP_LBx",l_para);
}

int CObj_Fnc__SINGLE_ARM_STD::
Fnc__PLACE_LBx(CII_OBJECT__VARIABLE *p_variable,
			   CII_OBJECT__ALARM *p_alarm,
			   const bool ex_flag,
			   const CString& arm_type,
			   const CString& para_module,
			   const CString& para_slot)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "Fnc__PLACE_LBx()";

	// ...
	int ll_i = Get__LLx_INDEX(para_module);

	if(para_module.CompareNoCase(MODULE__LBA) == 0)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
		{
			NEXT__LOOP;
		}
	}
	else if(para_module.CompareNoCase(MODULE__LBB) == 0)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
		{
			NEXT__LOOP;
		}
	}

	// ...
	{
		CString sch_module;
		sch_module.Format("%s-%s",para_module,para_slot);

		if(SCH__PLACE_MODULE(p_variable,
							 p_alarm,
							 log_id,
							 ex_flag,
							 arm_type,
							 para_module,
							 para_slot,
							 sch_module) < 0)
		{
			return -1;
		}

		xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);
	}

	if(ll_i >= 0)
	{
		CString str_data;

		str_data.Format("%1d", ++iLLx_IN_COUNT);
		xEXT_CH__LLx__IN_COUNT[ll_i]->Set__DATA(str_data);			
	}

	if(ex_flag == true)
	{
		return 1;
	}

	if(ll_i >= 0)
	{
		if(LLx__Check_Empty__InSlot(ll_i) < 0)
		{
			if(SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "1") > 0)
			{
				xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
			}
		}
		else
		{
			if((ATM_RB__Check_Empty__Arm_Type() > 0)
			&& (AL1__Check_Empty__All_Slot()    > 0))
			{
				if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS() < 0)
				{
					if(SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "2") > 0)
					{
						xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
					}
				}
			}
		}

		NEXT__LOOP;
	}

	return 1;
}
int CObj_Fnc__SINGLE_ARM_STD::
Fnc__PICK_LBx(CII_OBJECT__VARIABLE *p_variable,
			  CII_OBJECT__ALARM *p_alarm,
		      const bool ex_flag,
			  const CString& arm_type,
			  const CString& para_module,
			  const CString& para_slot)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "Fnc__PICK_LBx()";

	// ...
	{
		int active__all_mode = -1;

		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ALL) > 0)
			{
				active__all_mode = 1;
			}
		}

		if(active__all_mode < 0)
		{
			NEXT__LOOP;
		}
	}

	// ...
	CString sch_module;
	sch_module.Format("%s-%s",para_module,para_slot);

	if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, ex_flag,arm_type,para_module,para_slot,sch_module) < 0)
	{
		return -1;
	}

	xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,arm_type);

	if(ex_flag == true)
	{
		return 1;
	}

	// LLx ...
	{
		int ll_i = Get__LLx_INDEX(para_module);

		if(ll_i >= 0)
		{
			if(LLx__Check_Empty__InSlot(ll_i) < 0)
			{
				if(SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "1") > 0)
				{
					xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
				}
			}
			else
			{
				if((ATM_RB__Check_Empty__Arm_Type() > 0)
				&& (AL1__Check_Empty__All_Slot() > 0))
				{
					if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS() < 0)
					{
						if(SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "2") > 0)
						{
							xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
						}
					}
				}
			}

			NEXT__LOOP;
		}
	}

	return 1;
}
int CObj_Fnc__SINGLE_ARM_STD::
Fnc__PLACE_LPx(CII_OBJECT__VARIABLE *p_variable,
			   CII_OBJECT__ALARM *p_alarm,
			   const CString& arm_type)
{
	CString log_id = "Fnc__PLACE_LPx()";

	// ...
	int trg_port_id;
	int trg_slot_id;

	if(xSCH_MATERIAL_CTRL->Get__TARGET_LPx_INFO(arm_type,trg_port_id,trg_slot_id) < 0)
	{
		NEXT__LOOP;
	}

	if(Fnc__Check_ARM_WAFER_INFO_MISMATCH(p_variable,p_alarm, arm_type) < 0)
	{
		NEXT__LOOP;
	}

	if(LPx__Check_Empty__Slot_Status(trg_port_id,trg_slot_id) < 0)
	{
		int lp_index   = trg_port_id - 1;
		int slot_index = trg_slot_id - 1;
		CString var_data;

		int alarm_id = ALID__LPx_MATERIAL_PLACE__JOB_ERROR;
		CString alm_msg;
		CString alm_bff;
		CString r_act;

		alm_bff.Format("Please, check LP(%1d) and slot(%1d)'s status.\n",
			           trg_port_id, trg_slot_id);
		alm_msg += alm_bff;

		if((lp_index >= 0) && (lp_index < CFG_LP_LIMIT))
		{
			xCH__LPx__PORT_STATUS[lp_index]->Get__DATA(var_data);
				
			alm_bff.Format("   1. Port Status     : \"%s\" \n", var_data);
			alm_msg += alm_bff;
			alm_msg += "       status must be \"BUSY\" or \"PAUSED\". \n";

			// 
			xCH__LPx__CST_STATUS[lp_index]->Get__DATA(var_data);
				
			alm_bff.Format("   2. Cassette Status : \"%s\" \n", var_data);
			alm_msg += alm_bff;
			alm_msg += "       status must be \"EXIST\". \n";
		}
		if((slot_index >= 0) && (slot_index < CFG_LP__SLOT_MAX))
		{
			xCH__LPx__SLOT_STATUS[lp_index][slot_index]->Get__DATA(var_data);
				
			alm_bff.Format("   3. Slot Status     : \"%s\" \n", var_data);
			alm_msg += alm_bff;
			alm_msg += "       status must be \"NONE\". \n";
		}

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);

		NEXT__LOOP;
	}

	// ...
	CString para_module;
	CString para_slot;

	para_module.Format("LP%1d",trg_port_id);
	para_slot.Format("%1d",trg_slot_id);

	// ...
	CString sch_module;
	sch_module.Format("%s-%s",para_module,para_slot);

	if(SCH__PLACE_MODULE(p_variable,
						 p_alarm,
						 log_id,
						 false,
						 arm_type,
						 para_module,
						 para_slot,
						 sch_module) < 0)
	{
		NEXT__LOOP;
	}

	xSCH_MATERIAL_CTRL->Place__To_LPx(arm_type,sch_module);
	xSCH_MATERIAL_CTRL->Clear__MATERIAL_INFO(sch_module);
	xSCH_MATERIAL_CTRL->Clear__MATERIAL_INFO(trg_port_id,trg_slot_id);

	if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS_IN_LPx(trg_port_id) < 0)
	{
		int lp_index = trg_port_id - 1;

		if((lp_index >= 0) && (lp_index < CFG_LP_LIMIT))
		{
			xCH__LPx__SIDE_BUFFER_USE_FLAG[lp_index]->Set__DATA("");
		}
	}

	return 1;
}

// LBo -> LPo
int CObj_Fnc__SINGLE_ARM_STD::
Fnc__LBo_To_LPx__ONLY_MODE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "Fnc__LBo_To_LPx__ONLY_MODE()";

	// ...
	// bool active_log = true;
	bool active_log = false;
	
	if(active_log)		printf("Fnc__LBo_To_LPx__ONLY_MODE() ... \n");

	// ...
	CString para_module;
	CString para_slot;
	int slot_id;

	// LLx ...
	{
		int active__only_output = -1;

		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
			{
				if(LLx__Is_Available(ll_i) < 0)			continue;
				if(LLx__Is_ATM(ll_i) < 0)				continue;

				if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") < 0)
				{
					continue;
				}

				// ...
				int material_flag = -1;

				int i_limit = iLLx_SLOT_MAX[ll_i];
				int i;

				for(i=0; i<i_limit; i++)
				{
					if(LLx__Check_Occupied__OutSlot(ll_i, i) < 0)
					{
						continue;
					}

					para_module = Get__LLx_NAME(ll_i);
					para_slot.Format("%1d", i+1);

					material_flag = 1;
					break;
				}

				if(material_flag < 0)		continue;

				active__only_output = 1;
				break;
			}
		}

		if(active__only_output < 0)
		{
			if(active_log)		printf(" * Next_Loop (1) ... \n");
			NEXT__LOOP;
		}
	}

	// ...
	CString arm_type;
	int loop = 1;

	while(loop > 0)
	{
		loop = -1;

		if(ATM_RB__Get_Empty__Arm_Type(arm_type) > 0)
		{
			bool ex_flag = false;

			if(SCH__CHECK_LBo_OCCUPIED() > 1)
			{
				ex_flag = true;
			}

			CString sch_module;
			sch_module.Format("%s-%s",para_module,para_slot);

			if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, ex_flag,arm_type,para_module,para_slot,sch_module) < 0)
			{
				if(active_log)		printf(" * Next_Loop (2) ... \n");
				NEXT__LOOP;
			}

			xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,arm_type);

			if(SCH__LBx_PUMP(p_variable,para_module, log_id) > 0)
			{
				int ll_i = Get__LLx_INDEX(para_module);
				if(ll_i >= 0)
				{
					xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
				}

				if(active_log)		printf(" * Next_Loop (3) ... \n");
				NEXT__LOOP;
			}
			
			Fnc__PLACE_LPx(p_variable,p_alarm,arm_type);
		}
		else
		{
			if(active_log)		printf(" * Next_Loop (4) ... \n");
			NEXT__LOOP;
		}

		// LLx ...
		{
			int ll_i = Get__LLx_INDEX(para_module);
			if(ll_i >= 0)
			{
				if(LLx__Get_Occupied__OutSlot(ll_i, slot_id) > 0)
				{
					para_slot.Format("%1d",slot_id);

					loop = 1;
					continue;
				}
			}
		}
	}

	if(active_log)		printf(" * Next_Loop (5) ... \n");
	NEXT__LOOP;
}
int CObj_Fnc__SINGLE_ARM_STD::
Fnc__LBo_To_LPx__ALL_MODE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "Fnc__LBo_To_LPx__ALL_MODE()";

	// ...
	if(ATM_RB__Check_Empty__Arm_Type() < 0)
	{
		NEXT__LOOP;
	}

	if(AL1__Check_Empty__All_Slot() < 0)
	{
		int lbx_check = -1;

		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(LLx__Is_Available(ll_i) > 0)
			{
				if((LLx__Get_Occupied__Total_OutSlot(ll_i) > 0)
				&& (LLx__Get_Occupied__Total_InSlot(ll_i)  > 0))
				{
					lbx_check = 1;
				}
			}
		}

		if(lbx_check < 0)
		{
			NEXT__LOOP;
		}
	}

	// ...
	CString para_module;
	CString para_slot;
	int slot_id;

	// LLx ...
	{
		int out_flag = -1;

		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(out_flag < 0)
			{
				if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
				{
					if((LLx__Is_ATM(ll_i) > 0)
					&& (LLx__Is_Available(ll_i) > 0))
					{
						if(LLx__Get_Occupied__OutSlot(ll_i, slot_id) > 0)
						{
							para_module = Get__LLx_NAME(ll_i);
							para_slot.Format("%1d",slot_id);

							out_flag = 1;
						}
					}
				}
			}
		}
	
		if(out_flag < 0)
		{
			NEXT__LOOP;
		}
	}

	// ...
	CString arm_type;

	if(ATM_RB__Get_Empty__Arm_Type(arm_type) < 0)
	{
		NEXT__LOOP;
	}

	// ...
	CString sch_module;
	sch_module.Format("%s-%s",para_module,para_slot);

	if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,arm_type,para_module,para_slot,sch_module) < 0)
	{
		NEXT__LOOP;
	}

	// ...
	{
		xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,arm_type);

		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) < 0)
		{
			CString pmc_name;
			CString pmc_rcp;

			if(xSCH_MATERIAL_CTRL->Get__Last_Processing_Info(arm_type,pmc_name,pmc_rcp) > 0)
			{
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(arm_type,"PROCESSED");
			}
			else
			{
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(arm_type,STR__TO_LP);
			}
		}
	}
	
	// LBA & LBB : InSlot Check ...
	{
		int ll_i = Get__LLx_INDEX(para_module);
		if(ll_i >= 0)
		{
			if(LLx__Is_Available(ll_i) > 0)
			{
				if((LLx__Get_Occupied__Total_OutSlot(ll_i) < 1)
				&& (LLx__Get_Occupied__Total_InSlot(ll_i)  > 0))
				{
					CString lb_sch_name;
					int lb_in_slot = -1;

					LLx__Get_Occupied__InSlot(ll_i, lb_in_slot);
					lb_sch_name.Format("%s-%1d", para_module,lb_in_slot);
					
					if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(lb_sch_name) > 0)
					{
						if(SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "1_X") > 0)
						{
							xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
						}
					}

					NEXT__LOOP;
				}
			}
		}
	}

	if(sEXT_CH__SCH_MODE_LLx_OUT->Check__DATA(_SCH_MODE__ROUTE) > 0)
	{
		IDS__SCH_MATERIAL_INFO ds_info;

		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(arm_type, ds_info) > 0)
		{
			int ll_ptn = ds_info.iSRC__PTN;

			int ll_i = Get__LLx_INDEX(para_module);
			if(ll_i >= 0)
			{
				if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
				{
					if(xSCH_MATERIAL_CTRL->Check__MATERIAL_OF_LLx_OUT(ll_ptn, 1, true) > 0)
					{
						xCH__ATM_RB__SCH_STS_TO_LLx[ll_i]->Set__DATA("YES");
						NEXT__LOOP;
					}
				}
			}
		}
	}

	if(xSCH_MATERIAL_CTRL->Check__MATERIAL_MORE_THAN_MOVE_COUNT(1) > 1)
	{
		// ...
		int port_id;
		int slot_id;

		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_FROM_LPx(port_id,slot_id) > 0)
		{
			if(SCH__LPx_TO_LLx_OF_ROUTE_TYPE(p_variable, port_id,slot_id) > 0)
			{
				NEXT__LOOP;
			}
		}

		// ...
		int in_check = -1;

		if(AL1__Check_Empty__All_Slot() < 0)
		{
			in_check = 1;			
		}

		if(in_check < 0)
		{
			if(SCH__LBx_PUMP(p_variable,para_module, log_id) > 0)
			{
				int ll_i = Get__LLx_INDEX(para_module);
				if(ll_i >= 0)
				{
					xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
				}
			}
		}
	}

	NEXT__LOOP;
}

int CObj_Fnc__SINGLE_ARM_STD::
Fnc__LBo_To_RB(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "Fnc__LBo_To_RB()";

	if(ATM_RB__Check_Empty__Arm_Type() < 0)
	{
		NEXT__LOOP;
	}

	// ...
	CString para_module;
	CString para_slot;
	int slot_id;

	// LLx ...
	{
		int out_flag = -1;

		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(out_flag < 0)
			{
				if((xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
				&& (LLx__Check_Empty__InSlot(ll_i) < 0))
				{
					if((LLx__Is_ATM(ll_i) > 0)
					&& (LLx__Is_Available(ll_i) > 0))
					{
						if(LLx__Get_Occupied__OutSlot(ll_i, slot_id) > 0)
						{
							para_module = Get__LLx_NAME(ll_i);
							para_slot.Format("%1d", slot_id);

							out_flag = 1;
						}
					}
				}
			}
		}

		if(out_flag < 0)
		{
			NEXT__LOOP;
		}
	}
	
	// ...
	CString arm_type;
	
	if(ATM_RB__Get_Empty__Arm_Type(arm_type) < 0)
	{
		NEXT__LOOP;
	}

	// ...
	CString sch_module;
	sch_module.Format("%s-%s",para_module,para_slot);

	if(Get__LPx_SideBuffer_Info_To_Use(sch_module) < 0)
	{
		NEXT__LOOP;
	}

	if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,arm_type,para_module,para_slot,sch_module) < 0)
	{
		NEXT__LOOP;
	}
	xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,arm_type);

	// ...
	{
		int pump_req = -1;

		int ll_i = Get__LLx_INDEX(para_module);
		if(ll_i >= 0)
		{
			if(LLx__Check_Empty__InSlot(ll_i) < 0)
			{
				pump_req = 1;
			}
		}
		
		if(pump_req < 0)
		{
			if(xSCH_MATERIAL_CTRL->Check__MATERIAL_MORE_THAN_MOVE_COUNT(1) > 1)
			{
				pump_req = 1;
			}
		}

		if(pump_req > 0)
		{
			if(SCH__LBx_PUMP(p_variable,para_module, log_id) > 0)
			{
				int ll_i = Get__LLx_INDEX(para_module);
				if(ll_i >= 0)
				{
					xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
				}
			}
		}
	}

	NEXT__LOOP;
}


// LBo -> BUFFERx
int CObj_Fnc__SINGLE_ARM_STD
::Fnc__LBo_To_BUFFERx__ONLY_MODE(CII_OBJECT__VARIABLE *p_variable,
							     CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "Fnc__LBo_To_BUFFERx__ONLY_MODE()";

	// ...
	// bool active_log = true;
	bool active_log = false;

	if(active_log)		printf("Fnc__LBo_To_BUFFERx__ONLY_MODE) ... \n");

	// ...
	CString para_module;

	// LLx ...
	{
		CString para_slot;
		int slot_id;

		//
		int active__only_output = -1;

		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
			{
				if(LLx__Is_Available(ll_i) < 0)			continue;
				if(LLx__Is_ATM(ll_i) < 0)				continue;

				if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") < 0)
				{
					continue;
				}

				// ...
				int material_flag = -1;

				int i_limit = iLLx_SLOT_MAX[ll_i];

				for(int i=0; i<i_limit; i++)
				{
					if(LLx__Check_Occupied__OutSlot(ll_i, i) < 0)
					{
						continue;
					}

					para_module = Get__LLx_NAME(ll_i);
					para_slot.Format("%1d", i+1);

					material_flag = 1;
					break;
				}

				if(material_flag < 0)
				{
					continue;
				}

				active__only_output = 1;
				break;
			}
		}

		if(active__only_output < 0)
		{
			if(active_log)		printf(" * Next_Loop (1) ... \n");
			NEXT__LOOP;
		}
	}

	// ...
	CStringArray l__ll_lot_id;
	CStringArray l__ll_slot_id;
	CUIntArray   l__st_check;

	// LLx ...
	{
		int ll_i = Get__LLx_INDEX(para_module);

		CUIntArray l_slot_id;
		LLx__Get_Occupied__Only_Output(ll_i, l_slot_id);

		int k_limit = l_slot_id.GetSize();
		int k;

		for(k=0; k<k_limit; k++)
		{
			int slot_id = l_slot_id[k];
			int stx_check = -1;

			//
			CString sch_name;
			CString sch_slot;

			sch_slot.Format("%1d", slot_id);
			sch_name.Format("%s-%s", para_module,sch_slot);
		
			IDS__SCH_MATERIAL_INFO ds_info;
			xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(sch_name,ds_info);
				
			CString sch_lotid = ds_info.sLOT_ID;

			int wfr__port_id = ds_info.iSRC__PTN;
			int wfr__slot_id = ds_info.iSRC__STN;

			if(Fnc__LPx_SideBuffer_Use_Flag_Check(wfr__port_id, wfr__slot_id) > 0)
			{
				stx_check =  1;
			}

			if(stx_check > 0)
			{
				if((dCH__SCH_DB_ST1_OUT_MODE_BUFFER_TO_LPo->Check__DATA(STR__LPx_OPTIMIZATION) > 0)
				|| (dCH__SCH_DB_ST2_OUT_MODE_BUFFER_TO_LPo->Check__DATA(STR__LPx_OPTIMIZATION) > 0))
				{
					if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS_IN_LPx(wfr__port_id) < 0)
					{
						stx_check = -1;
					}
				}
			}

			l__ll_lot_id.Add(sch_lotid);
			l__ll_slot_id.Add(sch_slot);
			l__st_check.Add(stx_check);
		}
	}

	//
	int t_limit = l__ll_lot_id.GetSize();

	for(int t=0; t<t_limit; t++)
	{
		// ...
		{
			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)			NEXT__LOOP;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)			NEXT__LOOP;
			if(xCH__ATM_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)		NEXT__LOOP;
		}

		// ...
		CString para_slot = l__ll_slot_id[t];

		// ...
		CString bff_lotid;
		CString bff_module;
		int bff_slot_id;

		int stx_check = -1;

		// ...
		{
			CString para_lotid = "";

			if(dCH__CFG_BUFFER_LOTID_CHECK->Check__DATA(STR__ENABLE) > 0)
			{
				stx_check  = l__st_check[t];
				para_lotid = l__ll_lot_id[t];
			}
			else if(l__st_check.GetSize() > 0)
			{
				stx_check  = l__st_check[0];
				
				// para_lotid = l__ll_lot_id[0];
				para_lotid = _Get__STx_LotID();
			}

			if(stx_check > 0)
			{
				if(_Get__LPx_SideBuffer_Info_To_Use(para_lotid, bff_module,bff_slot_id) < 0)
				{
					if(active_log)		printf(" * Next_Loop (2) ... \n");
					NEXT__LOOP;
				}

				bff_lotid = para_lotid;
			}
		}

		// ...
		CString arm_type;

		if(ATM_RB__Get_Empty__Arm_Type(arm_type) > 0)
		{
			bool ex_flag = false;

			if(SCH__CHECK_LBo_OCCUPIED() > 1)
			{
				ex_flag = true;
			}

			// ...
			CString sch_module;
			sch_module.Format("%s-%s", para_module,para_slot);

			if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, ex_flag, arm_type, para_module,para_slot,sch_module) < 0)
			{
				if(active_log)		printf(" * Next_Loop (3) ... \n");
				NEXT__LOOP;
			}

			xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,arm_type);

			if(stx_check < 0)
			{
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(arm_type, STR__TO_LP);
			}

			if(ex_flag == false)
			{
				if(SCH__LBx_PUMP(p_variable,para_module, log_id) > 0)
				{
					int ll_i = Get__LLx_INDEX(para_module);
					if(ll_i >= 0)
					{
						xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
					}
				}
			}

			if(stx_check > 0)
			{
				Fnc__PLACE_BUFFERx(p_variable,p_alarm,arm_type, bff_module,bff_slot_id, bff_lotid);
			}

			if(ex_flag == false)
			{
				if(active_log)		printf(" * Next_Loop (4) ... \n");
				NEXT__LOOP;
			}
		}
		else
		{
			if(active_log)		printf(" * Next_Loop (5) ... \n");
			NEXT__LOOP;
		}
	}

	if(active_log)		printf(" * Next_Loop (6) ... \n");
	NEXT__LOOP;
}
int CObj_Fnc__SINGLE_ARM_STD::
Fnc__LBo_To_BUFFERx__ALL_MODE(CII_OBJECT__VARIABLE *p_variable,
							  CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "Fnc__LBo_To_BUFFERx__ALL_MODE()";

	//
	if(ATM_RB__Check_Empty__Arm_Type() < 0)
	{
		NEXT__LOOP;
	}

	if(AL1__Check_Empty__All_Slot() < 0)
	{
		int lbx_check = -1;
		
		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(LLx__Is_Available(ll_i) > 0)
			{
				if((LLx__Get_Occupied__Total_OutSlot(ll_i) > 0)
				&& (LLx__Get_Occupied__Total_InSlot(ll_i)  > 0))
				{
					lbx_check = 1;
				}
			}
		}
		
		if(lbx_check < 0)
		{
			NEXT__LOOP;
		}
	}

	// ...
	CString para_module;
	CString para_slot;
	int slot_id;

	// LLx ...
	{
		int out_flag = -1;

		int ll_limit = iLLx_SIZE;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(out_flag < 0)
			{
				if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
				{
					if((LLx__Is_ATM(ll_i) > 0)
					&& (LLx__Is_Available(ll_i) > 0))
					{
						if(LLx__Get_Occupied__OutSlot(ll_i, slot_id) > 0)
						{
							para_module = Get__LLx_NAME(ll_i);
							para_slot.Format("%1d",slot_id);

							out_flag = 1;
						}
					}
				}
			}
		}

		if(out_flag < 0)
		{
			NEXT__LOOP;
		}
	}

	// ...
	int buffer_check_flag = -1;

	CString bff_module;
	int bff_slot_id;

	// ...
	{
		CString sch_name;
		sch_name.Format("%s-%s", para_module,para_slot);

		int r_flag = Get__LPx_SideBuffer_Info_To_Use(sch_name, bff_module,bff_slot_id);
		
			 if(r_flag >  0)			buffer_check_flag =  1;
		else if(r_flag == 0)			buffer_check_flag = -1;
		else if(r_flag <  0)			NEXT__LOOP;
	}

	// ...
	CString arm_type;
	
	if(ATM_RB__Get_Empty__Arm_Type(arm_type) < 0)
	{
		NEXT__LOOP;
	}

	// ...
	CString sch_module;
	sch_module.Format("%s-%s",para_module,para_slot);

	if(SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,arm_type,para_module,para_slot,sch_module) < 0)
	{
		NEXT__LOOP;
	}

	xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,arm_type);

	if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) < 0)
	{
		CString pmc_name;
		CString pmc_rcp;

		if(xSCH_MATERIAL_CTRL->Get__Last_Processing_Info(arm_type,pmc_name,pmc_rcp) > 0)
		{
			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(arm_type,"PROCESSED");
		}
		else
		{
			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(arm_type,STR__TO_LP);
		}
	}

	// LLx : InSlot Check ...
	{
		int ll_i = Get__LLx_INDEX(para_module);
		if(ll_i >= 0)
		{
			if(LLx__Is_Available(ll_i) > 0)
			{
				if((LLx__Get_Occupied__Total_OutSlot(ll_i) < 1)
				&& (LLx__Get_Occupied__Total_InSlot(ll_i)  > 0))
				{
					CString lb_sch_name;
					int lb_in_slot = -1;
					
					LLx__Get_Occupied__InSlot(ll_i, lb_in_slot);
					lb_sch_name.Format("%s-%1d", para_module,lb_in_slot);
					
					if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(lb_sch_name) > 0)
					{
						if(SCH_RUN__LLx_PUMP(ll_i, p_variable, log_id, "101") > 0)
						{
							xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
						}
					}
				}
			}
		}
	}

	// ...
	{
		int req__llx_pmp = 1;

		if(sEXT_CH__SCH_MODE_LLx_OUT->Check__DATA(_SCH_MODE__ROUTE) > 0)
		{
			IDS__SCH_MATERIAL_INFO ds_info;

			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(arm_type, ds_info) > 0)
			{
				int ll_ptn = ds_info.iSRC__PTN;

				int ll_i = Get__LLx_INDEX(para_module);
				if(ll_i >= 0)
				{
					if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
					{
						if(xSCH_MATERIAL_CTRL->Check__MATERIAL_OF_LLx_OUT(ll_ptn, 1, true) > 0)
						{
							xCH__ATM_RB__SCH_STS_TO_LLx[ll_i]->Set__DATA("YES");
							
							req__llx_pmp = -1;
						}
					}
				}
			}
		}

		if(req__llx_pmp > 0)
		{
			if(xSCH_MATERIAL_CTRL->Check__MATERIAL_MORE_THAN_MOVE_COUNT(1) > 1)
			{
				if((xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS() < 1)
				&& (AL1__Check_Empty__All_Slot() > 0))
				{
					if(SCH__LBx_PUMP(p_variable,para_module, log_id) > 0)
					{
						int ll_i = Get__LLx_INDEX(para_module);
						if(ll_i >= 0)
						{
							xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
						}
					}
				}
			}
		}
	}
	
	if(xSCH_MATERIAL_CTRL->Check__SYSTEM_ABORT()   > 0)			NEXT__LOOP;
	if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)			NEXT__LOOP;
	
	if(buffer_check_flag > 0)
	{
		Fnc__PLACE_BUFFERx(p_variable,p_alarm, arm_type, bff_module,bff_slot_id, "");
	}

	NEXT__LOOP;
}

int  CObj_Fnc__SINGLE_ARM_STD::
Fnc__LPx_SideBuffer_Use_Flag_Check(const int port_id,
								   const int slot_id)
{
	// bool active_log = true;
	bool active_log = false;
	
	if(active_log)		printf("Fnc__LPx_SideBuffer_Use_Flag_Check() ... \n");
	if(active_log)		printf(" * (portid, slotid) <- (%1d, %1d) \n", port_id,slot_id);

	// ...
	int db_index = port_id - 1;
	
	if((db_index >= 0) && (db_index < iLPx_SIZE))
	{
		int check_flag = -1;
		
		if(xCH__SCH_DB_STx_APPLY_MODE->Check__DATA(STR__ENABLE) > 0)
		{
			check_flag = 1;			

			if(active_log)		printf(" * STx_Apply_Mode <- (%s) \n", STR__ENABLE);
		}
		else if(xCH__SCH_DB_STx_APPLY_MODE->Check__DATA(STR__ROUTE) > 0)
		{
			if(active_log)		printf(" * STx_Apply_Mode <- (%s) \n", STR__ROUTE);

			if(xSCH_MATERIAL_CTRL->Check__EDIT_TYPE__STATE() > 0)
			{
				CStringArray l_id;
				CStringArray l_mode;
				CStringArray l_slot; 
				CStringArray l_sec;

				if(xSCH_MATERIAL_CTRL->Get__STx_OF_EDIT_TYPE(port_id,slot_id, l_id,l_mode,l_slot,l_sec) > 0)
				{
					if(l_id.GetSize() > 0)
					{
						check_flag = 1;
					}
				}
			}
			else
			{
				CString bff1_info;
				CString bff2_info;

				if(xSCH_MATERIAL_CTRL->Get__BUFFERx_INFO(port_id,slot_id, bff1_info,bff2_info) > 0)
				{
					if((bff1_info.CompareNoCase(STR__YES) == 0)
					|| (bff2_info.CompareNoCase(STR__YES) == 0))
					{
						check_flag = 1;
					}
				}

				if(active_log)		printf(" * bff1_info <- (%s) \n", bff1_info);
				if(active_log)		printf(" * bff2_info <- (%s) \n", bff2_info);
			}
		}
		
		if(check_flag > 0)
		{
			xCH__LPx__SIDE_BUFFER_USE_FLAG[db_index]->Set__DATA(STR__YES);
			return 1;
		}
		else
		{
			xCH__LPx__SIDE_BUFFER_USE_FLAG[db_index]->Set__DATA("");
			return -1;
		}
	}

	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
Fnc__LPx_SideBuffer_Use_Flag_Clear()
{
	int i;

	for(i=0; i<iLPx_SIZE; i++)
	{
		xCH__LPx__SIDE_BUFFER_USE_FLAG[i]->Set__DATA("");
	}
	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
Get__LPx_SideBuffer_Info_To_Use(const int port_id,
								const int slot_id)
{
	CString buffer_name;
	int buffer_slot;

	return Get__LPx_SideBuffer_Info_To_Use(port_id,slot_id, buffer_name,buffer_slot);
}
int  CObj_Fnc__SINGLE_ARM_STD::
Get__LPx_SideBuffer_Info_To_Use(const int port_id,
								const int slot_id,
								CString& buffer_name,
								int& buffer_slot)
{		
	CString sch_lotid;

	// ...
	{
		IDS__SCH_MATERIAL_INFO ds_info;
	
		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(port_id,slot_id, ds_info) > 0)
		{
			sch_lotid = ds_info.sLOT_ID;				
		}
		else
		{
			return -1;
		}

		if(Fnc__LPx_SideBuffer_Use_Flag_Check(port_id,slot_id) < 0)
		{
			return 0;
		}
	}

	return _Get__LPx_SideBuffer_Info_To_Use(sch_lotid, buffer_name,buffer_slot);
}
int  CObj_Fnc__SINGLE_ARM_STD::
Get__LPx_SideBuffer_Info_To_Use(const CString& pos_name)
{
	CString buffer_name;
	int buffer_slot;

	return Get__LPx_SideBuffer_Info_To_Use(pos_name, buffer_name,buffer_slot);
}
int  CObj_Fnc__SINGLE_ARM_STD::
Get__LPx_SideBuffer_Info_To_Use(const CString& pos_name,
								CString& buffer_name,
								int& buffer_slot)
{
	CString sch_lotid;
	
	// ...
	{
		IDS__SCH_MATERIAL_INFO ds_info;
		int port_id;
		int slot_id;
		
		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(pos_name, ds_info) > 0)
		{
			sch_lotid = ds_info.sLOT_ID;				

			port_id = ds_info.iSRC__PTN;
			slot_id = ds_info.iSRC__STN;
		}
		else
		{
			return -1;
		}

		if(Fnc__LPx_SideBuffer_Use_Flag_Check(port_id,slot_id) < 0)
		{
			return 0;
		}
	}

	return _Get__LPx_SideBuffer_Info_To_Use(sch_lotid, buffer_name,buffer_slot);
}
int  CObj_Fnc__SINGLE_ARM_STD::
_Get__LPx_SideBuffer_Info_To_Use(const CString& sch_lotid,
								 CString& buffer_name,
								 int& buffer_slot)
{
	CString bff1_lotid = Buffer1__Get_LotID();
	CString bff2_lotid = Buffer2__Get_LotID();

	// LotID Check ...
	{
		if(sCH__SCH_DB_ST1_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
		{
			if((bff1_lotid.GetLength() > 0)
			&& (sch_lotid.CompareNoCase(bff1_lotid) == 0))
			{
				if(Buffer1__Check_Empty__Slot_To_Process(buffer_slot) > 0)
				{
					buffer_name = MODULE__BUFFER1;
					return 11;
				}
			}
		}

		if(sCH__SCH_DB_ST2_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
		{
			if((bff2_lotid.GetLength() > 0)
			&& (sch_lotid.CompareNoCase(bff2_lotid) == 0))
			{
				if(Buffer2__Check_Empty__Slot_To_Process(buffer_slot) > 0)
				{
					buffer_name = MODULE__BUFFER2;
					return 12;
				}
			}
		}
	}

	// Full Empty Side_Storage Check ...
	{
		if(sCH__SCH_DB_ST1_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
		{
			if(bff1_lotid == "")
			{
				if(Buffer1__Check_Empty__Slot_To_Process(buffer_slot) > 0)
				{
					buffer_name = MODULE__BUFFER1;
					return 21;
				}
			}
		}

		if(sCH__SCH_DB_ST2_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
		{
			if(bff2_lotid == "")
			{
				if(Buffer2__Check_Empty__Slot_To_Process(buffer_slot) > 0)
				{
					buffer_name = MODULE__BUFFER2;
					return 22;
				}
			}
		}
	}
				
	return -11;
}
CString CObj_Fnc__SINGLE_ARM_STD::_Get__STx_LotID()
{
	CString bff1_lotid = Buffer1__Get_LotID();
	CString bff2_lotid = Buffer2__Get_LotID();

	if(sCH__SCH_DB_ST1_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
	{
		if(bff1_lotid.GetLength() > 0)		return bff1_lotid;
	}

	if(sCH__SCH_DB_ST2_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
	{
		if(bff2_lotid.GetLength() > 0)		return bff2_lotid;
	}

	return "";
}
