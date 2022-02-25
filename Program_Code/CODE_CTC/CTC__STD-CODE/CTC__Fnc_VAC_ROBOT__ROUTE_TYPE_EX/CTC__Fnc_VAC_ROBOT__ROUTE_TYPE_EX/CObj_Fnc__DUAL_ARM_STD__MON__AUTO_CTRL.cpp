#include "StdAfx.h"
#include "CObj_Fnc__DUAL_ARM_STD.h"

#include "Macro_Function.h"


#define  NEXT__LOOP					throw 1

#define STR__ROBOT_NAME				"VAC_RB1"


// ...
void CObj_Fnc__DUAL_ARM_STD::
Mon__AUTO_CTRL(CII_OBJECT__VARIABLE *p_variable,
			   CII_OBJECT__ALARM *p_alarm)
{
	// ...
	{
		xSCH_MATERIAL_CTRL->Link__SERVICE_DB("");

		xSCH_MATERIAL_CTRL->Define__ROBOT_NAME(STR__ROBOT_NAME);
		xSCH_MATERIAL_CTRL->Define__ROBOT_ARM("A");
		xSCH_MATERIAL_CTRL->Define__ROBOT_ARM("B");

		xSCH_MATERIAL_CTRL->Register__SYSTEM_NAME(sObject_Name);
	}

	// ...
	{
		iFRONT_PMx_FLAG = -1;
		iFRONT_WAC_FLAG = -1;
	
		iJOB_FLAG = -1;
		iLBx_OUT_COUNT = 0;
	}

	// ...
	SCX__ASYNC_TIMER_CTRL x_timer__sys_idle;
	x_timer__sys_idle->REGISTER__COUNT_CHANNEL_NAME(sEXT_CH__SYSTEM_IDLE_CUR_TIME_SEC->Get__CHANNEL_NAME());

	// ...
	int loop_count =  0;
	int idle_flag  =  0;
	int abort_flag = -1;

	while(1)
	{
		while(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)
		{
			if(idle_flag <= 0)
			{
				printf(" * CObj_Fnc__DUAL_ARM_STD::Mon__AUTO_CTRL) ... \n");
				printf(" ** Idle Start ... \n");

				// ...
				{
					xSCH_MATERIAL_CTRL->Set__ROBOT_IDLE(STR__ROBOT_NAME);

					Set__TMC_CtcInUse_To_Standby();
					Set__PMx_CtcInUse_To_Standby();
				}

				// ...
				{
					xTIMER_CTRL__LLx_PICK_DELAY->STOP();

					xCH_CFG__PICK_DELAY_TIME->Set__DATA("0");
					xCH_CFG__PICK_COUNT_FROM_LBx->Set__DATA("0");
				}

				/*
				// Job End Ready ...
				if(dEXT_CH__CFG_JOB_END_READY_PMx_USE->Check__DATA(STR__ENABLE) > 0)
				{
					SCH__PMx_JOB_END_READY();
				}
				*/

				x_timer__sys_idle->START__COUNT_UP(99999);

				// Robot Home ...
				if(idle_flag < 0)
				{
					if(VAC_RB__Is_Available() > 0)
					{
						printf(" ** VAC_RB <- Init ... \n");

						pVAC_RB__OBJ_CTRL->Run__OBJECT("INIT");			
					}
				}
			}

			// ...
			{
				SCH__SYSTEM_INIT();
				iJOB_FLAG = -1;
			
				SCH__MATERIAL_CHECK();
				SCH__PMC_CHECK();
				SCH__MODULE_CHECK();
			}

			// System Idle ...
			{
				CString ch_data;

				ch_data = sEXT_CH__SYSTEM_IDLE_CUR_TIME_SEC->Get__STRING();
				double cur_sys_sec = atof(ch_data);
				double cfg_sys_sec = aEXT_CH__SYSTEM_IDLE_CFG_TIME_SEC->Get__VALUE();

				if(cur_sys_sec >= cfg_sys_sec)
				{
					int i_limit = iPMx_SIZE;
					int i;

					for(i=0; i<i_limit; i++)
					{
						if(dEXT_CH__SYSTEM_IDLE_CFG_PMx_USE[i]->Check__DATA(STR__YES) < 0)
							continue;

						ch_data = xCH__PMx__IDLE_TIME[i]->Get__STRING();
						double cur_pmc_sec = atof(ch_data);
						double cfg_pmc_sec = aEXT_CH__SYSTEM_IDLE_CFG_PMx_SEC[i]->Get__VALUE();

						if(cur_pmc_sec < cfg_pmc_sec)
							continue;
						
						if(PMx__Is_Available(i) < 0)
							continue;

						pPMx__OBJ_CTRL[i]->Run__OBJECT("IDLE_START");
					}
				}
			}

			// ...
			{
				Check_Alarm__Scheduler_Config(p_alarm);
			}

			sCH__SCH_LOOP_ID->Set__DATA("101");

			Sleep(100);
		
			// ...
			{
				idle_flag = 1;
				loop_count = 0;
			}
		}
		iJOB_FLAG = 1;

		
		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("102");

			Sleep(1);
	
			if(VAC_RB__Is_Available() < 0)	
			{
				continue;
			}
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)
			{
				continue;
			}
		}


		if(idle_flag > 0)
		{
			idle_flag = -1;
			loop_count = 0;

			x_timer__sys_idle->STOP_ZERO();

			// ...
			{
				sCH__SCH_LOOP_ID->Set__DATA("111");

				SCH__SYSTEM_INIT();
			}

			// ...
			{
				int i;

				for(i=0;i<iPMx_SIZE;i++)
				{
					xCH__PMx__FIRST_WAFER_FLAG[i]->Set__DATA(STR__YES);
				}
			}

			// ...
			{
				xSCH_MATERIAL_CTRL->Set__ROBOT_BUSY(STR__ROBOT_NAME);
			
				iFRONT_PMx_FLAG = -1;
				iFRONT_WAC_FLAG = -1;
			}

			try
			{
				sCH__SCH_LOOP_ID->Set__DATA("113");

				AUTO_CTRL__TMC_PUMP(p_variable);
			}
			catch(int err_flag)
			{

			}
		}

		// ...
		{
			loop_count++;

			if(loop_count > 10)
			{
				loop_count = 0;

				Check_Alarm__Scheduler_Config(p_alarm);
			}
		}

		if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
		if(xCH__VAC_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;

		//  LBi -> VAC_RB
		try
		{
			int delay_flag = -1;

			if(xCH_CFG__PICK_DELAY_FLAG->Check__DATA("ENABLE") > 0)
			{
				CString var_data;
				double delay_time;

				xCH_CFG__PICK_DELAY_TIME->Get__DATA(var_data);
				delay_time = atof(var_data);

				if(delay_time >= 1)		delay_flag = 1;
			}

			if(delay_flag < 0)
			{
				if(SCH__LBx__CHECK_ONLY_MODE() > 0)
				{
					sCH__SCH_LOOP_ID->Set__DATA("121");

					AUTO_CTRL__LBi_RB__ONLY_MODE(p_variable,p_alarm);
				}
				else
				{
					if(SCH__LBx__CHECK_1_SLOT_ALL_MODE(-1) > 0)
					{
						sCH__SCH_LOOP_ID->Set__DATA("122");

						AUTO_CTRL__LBi_RB__1_SLOT_ALL_MODE_NEW(p_variable,p_alarm);
					}
					else
					{
						if(xCH_CFG__SCH_PMC_RECIPE_TYPE->Check__DATA(STR__PRC_CLN) > 0)
						{
							sCH__SCH_LOOP_ID->Set__DATA("123");

							AUTO_CTRL__LBi_To_RB_With_Ready_PMC__ALL_MODE(p_variable,p_alarm);
						}
						else
						{
							sCH__SCH_LOOP_ID->Set__DATA("124");

							AUTO_CTRL__LBi_RB__ALL_MODE(p_variable,p_alarm);
						}
					}
				}
			}
		}
		catch(int err_flag)
		{

		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("131");

			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__VAC_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}
		
		//  VAC_RB : WAC Position
		try
		{
			if(iFRONT_WAC_FLAG < 0)
			{
				sCH__SCH_LOOP_ID->Set__DATA("132");

				AUTO_CTRL__FRONT_WAC_POS(p_variable);
			}
		}
		catch(int err_flag)
		{
			
		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("141");

			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__VAC_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		//  LBi -> PMx
		try
		{
			int delay_flag = -1;

			if(xCH_CFG__PICK_DELAY_FLAG->Check__DATA("ENABLE") > 0)
			{
				CString var_data;
				double delay_time;

				xCH_CFG__PICK_DELAY_TIME->Get__DATA(var_data);
				delay_time = atof(var_data);

				if(delay_time >= 1)		delay_flag = 1;
			}

			if(delay_flag < 0)
			{
				if(SCH__LBx__CHECK_ONLY_MODE() > 0)
				{
					sCH__SCH_LOOP_ID->Set__DATA("142");

					AUTO_CTRL__LBi_PMx__ONLY_MODE(p_variable,p_alarm);
				}
				else
				{
					if(SCH__LBx__CHECK_1_SLOT_ALL_MODE(-1) > 0)
					{
						sCH__SCH_LOOP_ID->Set__DATA("143");

						AUTO_CTRL__LBi_PMx__1_SLOT_ALL_MODE(p_variable,p_alarm);
					}
					else
					{
						if(xCH_CFG__SCH_PMC_RECIPE_TYPE->Check__DATA(STR__PRC_CLN) > 0)
						{
							sCH__SCH_LOOP_ID->Set__DATA("144");

							AUTO_CTRL__LBi_To_Ready_PMx__ALL_MODE(p_variable,p_alarm);
						}
						else
						{
							sCH__SCH_LOOP_ID->Set__DATA("145");

							AUTO_CTRL__LBi_PMx__ALL_MODE(p_variable,p_alarm);
						}
					}
				}
			}
		}
		catch(int err_flag)
		{

		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("151");

			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__VAC_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		//  VAC_RB -> PMx
		try
		{
			sCH__SCH_LOOP_ID->Set__DATA("152");

			AUTO_CTRL__RB_PMx(p_variable,p_alarm);
		}
		catch(int err_flag)
		{

		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("161");

			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__VAC_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		//  VAC_RB -> LLx_PROC
		try
		{
			sCH__SCH_LOOP_ID->Set__DATA("153.1");

			AUTO_CTRL__RB_TO_LLx_PROC(p_variable,p_alarm);
		}
		catch(int err_flag)
		{

		}

		//  LLx_PROC -> VAC_RB
		try
		{
			sCH__SCH_LOOP_ID->Set__DATA("153.2");

			AUTO_CTRL__LLx_PROC_TO_RB(p_variable,p_alarm);
		}
		catch(int err_flag)
		{

		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("154");

			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__VAC_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		//  PMo -> VAC_RB
		try
		{
			sCH__SCH_LOOP_ID->Set__DATA("162");

			AUTO_CTRL__PMo_RB(p_variable,p_alarm);
		}
		catch(int err_flag)
		{

		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("171");

			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__VAC_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		//  PMx -> VAC_RB
		try
		{
			sCH__SCH_LOOP_ID->Set__DATA("172");

			AUTO_CTRL__PMx_RB(p_variable,p_alarm);
		}
		catch(int err_flag)
		{

		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("181");

			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__VAC_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		//  VAC_RB -> LBo
		try
		{
			if(SCH__LBx__CHECK_ONLY_MODE() > 0)
			{
				sCH__SCH_LOOP_ID->Set__DATA("191");

				AUTO_CTRL__RB_LBo__ONLY_MODE(p_variable,p_alarm);
			}
			else
			{
				if(SCH__LBx__CHECK_1_SLOT_ALL_MODE(-1) > 0)
				{
					sCH__SCH_LOOP_ID->Set__DATA("192");

					AUTO_CTRL__RB_LBo__1_SLOT_ALL_MODE(p_variable,p_alarm);
				}
				else
				{
					sCH__SCH_LOOP_ID->Set__DATA("193");

					AUTO_CTRL__RB_LBo__ALL_MODE(p_variable,p_alarm,loop_count);
				}
			}
		}
		catch(int err_flag)
		{

		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("201");

			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__VAC_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		//  VAC_RB : WAC Position
		try
		{
			if(iFRONT_WAC_FLAG < 0)
			{
				sCH__SCH_LOOP_ID->Set__DATA("202");

				AUTO_CTRL__FRONT_WAC_POS(p_variable);
			}
		}
		catch(int err_flag)
		{

		}

		/*
		//.....
		if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
		if(xCH__VAC_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;

		//  VAC_RB : PMi
		try
		{
			if(iFRONT_PMx_FLAG < 0)
			{
				AUTO_CTRL__FRONT_PMi(p_variable);
			}
		}
		catch(int err_flag)
		{

		}
		*/

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("211");

			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__VAC_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		//  VAC_RB : PMo
		try
		{
			if(iFRONT_PMx_FLAG < 0)
			{
				sCH__SCH_LOOP_ID->Set__DATA("212");

				AUTO_CTRL__FRONT_PMo(p_variable);
			}
		}
		catch(int err_flag)
		{

		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("221");

			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__VAC_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		// LLx : Exception 1
		try
		{
			if(loop_count == 3)
			{
				sCH__SCH_LOOP_ID->Set__DATA("222");

				AUTO_CTRL__LLx_Exception_Proc1(p_variable,p_alarm);
			}
		}
		catch(int err_flag)
		{
			
		}

		// ...
		{
			sCH__SCH_LOOP_ID->Set__DATA("231");

			if(xSCH_MATERIAL_CTRL->Check__SYSTEM_PAUSE() > 0)		continue;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		continue;
			if(xCH__VAC_RB_PAUSE_FLAG->Check__DATA(STR__YES) > 0)	continue;
		}

		// LLx : Exception 2
		try
		{
			if(loop_count == 3)
			{
				sCH__SCH_LOOP_ID->Set__DATA("232");

				AUTO_CTRL__LLx_Exception_Proc2(p_variable,p_alarm);
			}
		}
		catch(int err_flag)
		{
			
		}
	}
}

//-----------------------------------------------------------------------------------------
void CObj_Fnc__DUAL_ARM_STD::
SCH__SYSTEM_INIT()
{
	int i;

	// ...
	{
		iLBx_OUT_COUNT = 0;
		iPMx_IN_COUNT = 0;
	}
	
	for(i=0;i<CFG_PM_LIMIT;i++)
	{
		xCH__PMx__IN_COUNT[i]->Set__DATA("0");
	}

	for(i=0;i<iPMx_SIZE;i++)
	{
		xCH__PMx__X_PICK_FLAG[i]->Set__DATA("");
		xCH__PMx__X_PLACE_FLAG[i]->Set__DATA("");

		xCH__PMx__NEXT_PROCESS[i]->Set__DATA("");
	}
}

void CObj_Fnc__DUAL_ARM_STD::SCH__MATERIAL_CHECK()
{
	if(VAC_RB__Check_Occupied__A_Arm() > 0)
	{
		xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MATERIAL_STS(sObject_Name,"VAC_RB-A");		
	}
	else
	{
		xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__MATERIAL_STS(sObject_Name,"VAC_RB-A");
	}
	if(VAC_RB__Check_Occupied__B_Arm() > 0)
	{
		xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MATERIAL_STS(sObject_Name,"VAC_RB-B");		
	}
	else
	{
		xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__MATERIAL_STS(sObject_Name,"VAC_RB-B");
	}

	// ...
	{
		CString pm_name;
		int i;
		
		for(i=0; i<iPMx_SIZE; i++)
		{
			pm_name.Format("PM%1d",i+1);

			if(xEXT_CH__CFG__PMx_USE[i]->Check__DATA(STR__ENABLE) < 0)
			{
				if(PMx__Check_Occupied__SlotStatus(i) < 0)
				{
					xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__MATERIAL_STS(sObject_Name,pm_name);		
				}
				continue;
			}

			if(PMx__Check_Occupied__SlotStatus(i) > 0)
			{
				xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MATERIAL_STS(sObject_Name,pm_name);		
			}
			else
			{
				xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__MATERIAL_STS(sObject_Name,pm_name);		
			}
		}
	}
}
void CObj_Fnc__DUAL_ARM_STD::SCH__PMC_CHECK()
{
	//.....
	CString pm_name;
	CString obj_sts;
	int i;
		
	for(i=0;i<iPMx_SIZE;i++)
	{
		pm_name.Format("PM%1d",i+1);

		//.....
		xCH__PMx__OBJ_STATUS[i]->Get__DATA(obj_sts);
			
		if(((obj_sts.CompareNoCase("CTCINUSE") == 0)||(obj_sts.CompareNoCase("STANDBY") == 0))
		&& (xEXT_CH__CFG__PMx_USE[i]->Check__DATA("ENABLE") > 0))
		{
			xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__PMC_STS(sObject_Name,pm_name);
		}
		else
		{
			xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__PMC_STS(sObject_Name,pm_name);
		}
	}
}
void CObj_Fnc__DUAL_ARM_STD::SCH__MODULE_CHECK()
{
	if(TMC_CHM__Is_Available() > 0)
	{
		xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MODULE_AVAILABLE(sObject_Name,"TMC_CHM");		
	}
	else
	{
		xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MODULE_NOT_AVAILABLE(sObject_Name,"TMC_CHM");		
	}

	if(VAC_RB__Is_Available() > 0)
	{
		xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MODULE_AVAILABLE(sObject_Name,"VAC_RB");		
	}
	else
	{
		xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__MODULE_NOT_AVAILABLE(sObject_Name,"VAC_RB");		
	}
}


//-----------------------------------------------------------------------------------------
int  CObj_Fnc__DUAL_ARM_STD::
Fnc__Get_PMx_List(const CString& sch_name, CStringArray& l_pm_name)
{
	CStringArray l_pm_rcp;

	return Fnc__Get_PMx_List(sch_name, l_pm_name,l_pm_rcp);
}
int  CObj_Fnc__DUAL_ARM_STD::
Fnc__Get_PMx_List(const CString& sch_name, CStringArray& l_pm_name,CStringArray& l_pm_rcp)
{
	l_pm_name.RemoveAll();
	l_pm_rcp.RemoveAll();

	// ...
	CStringArray l_pm;
	CStringArray l_rcp;

	xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_name, l_pm,l_rcp);

	// ...
	CString pm_name;

	int i_limit = l_pm.GetSize();
	for(int i=0; i<i_limit; i++)
	{
		int pm_i = SCH__CHECK_PM_INDEX(l_pm[i]);

		if(pm_i <  0)				continue;
		if(pm_i >= iPMx_SIZE)		continue;

		if(PMx__Is_Available(pm_i) < 0)				continue;
		if(PMx__Check_Empty__SlotStatus(pm_i) < 0)	continue;

		pm_name.Format("PM%1d", pm_i+1);
		l_pm_name.Add(pm_name);
		l_pm_rcp.Add(l_rcp[i]);
	}

	if(l_pm_name.GetSize() < 1)		return -1;
	return 1;
}

CString CObj_Fnc__DUAL_ARM_STD::
Fnc__Get_PM_Rcp(const CString& pm_name, const CStringArray& l_pm_name,const CStringArray& l_pm_rcp)
{
	int i_limit = l_pm_name.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(pm_name.CompareNoCase(l_pm_name[i]) != 0)		continue;

		return l_pm_rcp[i];
	}
	return "";
}

int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__LBi_RB__ONLY_MODE(CII_OBJECT__VARIABLE *p_variable,
							 CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CString log_id = "AUTO_CTRL__LBi_RB__ONLY_MODE()";

	// ...
	CString para_module;
	CString para_slot;
	int slot_id;

	CUIntArray l__para_slot_id;

	// LLx ...
	{
		CUIntArray   l__ll_cnt;
		CStringArray l__ll_name;
		CStringArray l__ll_slot;

		int ll_limit = iLLx_LIMIT;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) < 0)
			{
				continue;
			}

			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") < 0)
			{
				continue;
			}

			if(LLx__Is_Available(ll_i) < 0)							continue;
			if(LLx__Get_Occupied__InSlot(ll_i, slot_id) < 0)		continue;

			if(SCH__LLx_CHECK_PRESSURE(ll_i, p_variable,p_alarm,1) < 0)
			{
				continue;
			}

			// LBi -> RB : ONLY_MODE
			if(xCH_CFG__LLx_CTRL_ONLY_INPUT_OUTPUT_MODE->Check__DATA(STR__DUAL) > 0)
			{
				CString ch_data;

				ch_data = xEXT_CH__LLx__IN_COUNT[ll_i]->Get__STRING();
				l__ll_cnt.Add(atoi(ch_data));

				ch_data = Get__LLx_NAME(ll_i);
				l__ll_name.Add(ch_data);

				ch_data.Format("%1d",slot_id);
				l__ll_slot.Add(ch_data);

				LLx__Get_Occupied__InSlot(ll_i, l__para_slot_id);
			}
			else
			{
				CString ch_data;

				ch_data = xEXT_CH__LLx__IN_COUNT[ll_i]->Get__STRING();
				l__ll_cnt.Add(atoi(ch_data));

				ch_data = Get__LLx_NAME(ll_i);
				l__ll_name.Add(ch_data);
	
				ch_data.Format("%1d",slot_id);
				l__ll_slot.Add(ch_data);
			}
		}

		if(l__ll_name.GetSize() < 1)
		{
			NEXT__LOOP;
		}

		Change_Order__In_Count_Of_LLx(l__ll_cnt, l__ll_name, l__ll_slot);

		if(l__ll_name.GetSize() > 0)
		{
			para_module = l__ll_name[0];
			para_slot   = l__ll_slot[0];
		}
	}

	if(xCH_CFG__SCH_LLx_EXCHANGE_WHEN_PMC_EMPTY->Check__DATA(STR__ENABLE) > 0)
	{
		if(VAC_RB__Check_Empty__Dual_Arm() < 0)
		{
			CString sch_name;
			sch_name.Format("%s-%s", para_module,para_slot);

			CStringArray l_pm_name;
			if(Fnc__Get_PMx_List(sch_name, l_pm_name) < 0)
			{
				NEXT__LOOP;
			}
		}
	}
	else
	{
		CString arm_type;

		if(VAC_RB__Get_Occupied__Arm_Type(arm_type) > 0)
		{
			IDS__SCH_MATERIAL_STATUS ds_info;

			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info) < 0)
			{
				NEXT__LOOP;
			}

			// jglee : 2021.03.12
			// if(ds_info.sMATERIAL_STS.CompareNoCase("PROCESSED") != 0)
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				NEXT__LOOP;
			}
		}
	}

	// ...
	{
		CString arm_type;

		if(VAC_RB__Get_Occupied__Arm_Type(arm_type) > 0)
		{
			CStringArray l_pm_name;
			if(Fnc__Get_PMx_List(arm_type, l_pm_name) > 0)
			{
				NEXT__LOOP;
			}
		}
	}
	
	if(VAC_RB__Check_Dual_Arm_Enable() < 0)
	{
		CString sch_name;
		sch_name.Format("%s-%s",para_module,para_slot);

		CStringArray l_pm_name;
		if(Fnc__Get_PMx_List(sch_name, l_pm_name) < 0)
		{
			NEXT__LOOP;
		}
	}

	// ...
	CString empty_arm;

	if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
	{
		NEXT__LOOP;
	}

	// LBi -> RB : ONLY_MODE
	if(xCH_CFG__LLx_CTRL_ONLY_INPUT_OUTPUT_MODE->Check__DATA(STR__DUAL) > 0)
	{
		CStringArray l_pm_name_x[10];
		int ll_slot_count = 0;

		CString sch_module;

		int i_size = l__para_slot_id.GetSize();
		int i;

		for(i=0; i<i_size; i++)
		{
			para_slot.Format("%1d", l__para_slot_id[i]);
			sch_module.Format("%s-%s", para_module,para_slot);

			if(Fnc__Get_PMx_List(sch_module, l_pm_name_x[i]) > 0)
			{
				ll_slot_count++;
			}
		}
		if(ll_slot_count < 1)
		{
			NEXT__LOOP;
		}

		if(xCH_CFG__DUAL_ARM_CURRENT_BEHAVIOR->Check__DATA(STR__ENABLE) > 0)
		{
			bool active_dual_arm =  false;
			CString dual_check_arm;

			if(ll_slot_count > 1)
			{
				if(VAC_RB__Get_Empty__Arm_Type_With_PMx_Constraint(dual_check_arm, l_pm_name_x[0]) > 0)
				{
					if(VAC_RB__Check_Empty__Arm_Type_With_PMx_Constraint(dual_check_arm, l_pm_name_x[1]) > 0)
					{
						active_dual_arm = true;

						empty_arm = "AB";
					}
					else
					{
						NEXT__LOOP;
					}
				}
			}

			if(active_dual_arm)
			{
				int slot_id = l__para_slot_id[0];

				para_slot.Format("%1d", slot_id);
				sch_module.Format("%s-%s", para_module,para_slot);

				int act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, false, empty_arm, para_module,para_slot,sch_module);
				int move_flag = -1;

				if(act_flag < 0)		move_flag = SCH__Check_Material_Pick(empty_arm);
				else					move_flag = 1;

				if(move_flag > 0) 
				{
					CString sch_01;
					CString sch_02;

					sch_01.Format("%s-%1d", para_module,slot_id);
					sch_02.Format("%s-%1d", para_module,slot_id+1);

					if(dual_check_arm.CompareNoCase("A") == 0)
					{
						xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_01, "A");
						xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_02, "B");
					}
					else
					{
						xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_01, "B");
						xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_02, "A");
					}
				}
				if(act_flag < 0)		NEXT__LOOP;
			}
			else
			{
				for(i=0; i<i_size; i++)
				{
					if(VAC_RB__Get_Empty__Arm_Type_With_PMx_Constraint(empty_arm, l_pm_name_x[i]) < 0)
					{
						NEXT__LOOP;
					}

					// ...
					bool ex_active = false;
					if(ll_slot_count > 1)
					{
						if(VAC_RB__Check_Empty__Arm_Type_With_PMx_Constraint(empty_arm, l_pm_name_x[i_size-1]) > 0)
						{
							if(i < (i_size - 1))		ex_active = true;
						}
					}

					int slot_id = l__para_slot_id[i];

					para_slot.Format("%1d", slot_id);
					sch_module.Format("%s-%s", para_module,para_slot);

					//
					int act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, ex_active, empty_arm, para_module,para_slot,sch_module);
					int move_flag = -1;

					if(act_flag < 0)		move_flag = SCH__Check_Material_Pick(empty_arm);
					else					move_flag = 1;

					if(move_flag > 0)		xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module, empty_arm);
					if(act_flag < 0)		NEXT__LOOP;

					if(!ex_active)			break;
				}
			}
		}
		else 
		{
			for(int i=0; i<i_size; i++)
			{
				if(VAC_RB__Get_Empty__Arm_Type_With_PMx_Constraint(empty_arm, l_pm_name_x[i]) < 0)
				{
					NEXT__LOOP;
				}

				// ...
				bool ex_active = false;
				if(ll_slot_count > 1)
				{
					if(VAC_RB__Check_Empty__Arm_Type_With_PMx_Constraint(empty_arm, l_pm_name_x[i_size-1]) > 0)
					{
						if(i < (i_size - 1))		ex_active = true;
					}
				}

				para_slot.Format("%1d", l__para_slot_id[i]);
				sch_module.Format("%s-%s", para_module,para_slot);

				int act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, ex_active, empty_arm, para_module,para_slot,sch_module);
				int move_flag = -1;

				if(act_flag < 0)		move_flag = SCH__Check_Material_Pick(empty_arm);
				else					move_flag = 1;

				if(move_flag > 0)		xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module, empty_arm);
				if(act_flag < 0)		NEXT__LOOP;

				if(!ex_active)			break;
			}
		}
	}
	else
	{
		CString sch_module;
		sch_module.Format("%s-%s",para_module,para_slot);

		int act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, false, empty_arm, para_module,para_slot,sch_module);
		int move_flag = -1;

		if(act_flag < 0)			move_flag = SCH__Check_Material_Pick(empty_arm);
		else						move_flag = 1;

		if(move_flag > 0)			xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module, empty_arm);
		if(act_flag  < 0)			NEXT__LOOP;
	}

	// ...
	int ll_i = Get__LLx_INDEX(para_module);
	if(ll_i >= 0)
	{
		if(LLx__Check_All_Empty(ll_i) > 0)
		{
			if(SCH_RUN__LLx_VENT(ll_i, log_id, "1") > 0)
			{
				xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
			}
		}
	}

	NEXT__LOOP;
}

int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__LBi_To_RB_With_Ready_PMC__ALL_MODE(CII_OBJECT__VARIABLE *p_variable,
											  CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);
	
	// ...
	{
		CString arm_type;
			
		// Arm : A ...
		if(VAC_RB__Check_Occupied__A_Arm() > 0)
		{
			arm_type = "A";
				
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				NEXT__LOOP;
			}
		}
		// Arm : B ...
		if(VAC_RB__Check_Occupied__B_Arm() > 0)
		{
			arm_type = "B";
				
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				NEXT__LOOP;
			}
		}
	}

	// ...
	{
		IDS__SCH_MATERIAL_STATUS ds_sts;
		CString sch_name;	
		int lb_slotid;

		int lba_portid = -1;
		int lba_slotid = -1;
		int lbb_portid = -1;
		int lbb_slotid = -1;
		CStringArray l_lba_pmc;
		CStringArray l_lba_rcp;
		CStringArray l_lbb_pmc;
		CStringArray l_lbb_rcp;

		int ll_a = _LLx_INDEX__LBA;
		int ll_b = _LLx_INDEX__LBB;

		if((xEXT_CH__LLx__IN_OUT_FLAG[ll_a]->Check__DATA("OUT") > 0)
		&& (LLx__Is_Available(ll_a) > 0)
		&& (LLx__Is_VAC(ll_a) > 0))
		{
			if(LLx__Get_Occupied__InSlot(ll_a, lb_slotid) > 0)
			{
				sch_name.Format("%s-%1d", MODULE__LBA,lb_slotid);
				
				if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_name) > 0)
				{
					if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(sch_name,ds_sts) > 0)
					{
						lba_portid = ds_sts.iPORT_ID;	
						lba_slotid = ds_sts.iSLOT_ID;	

						xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_name,l_lba_pmc,l_lba_rcp);
					}
				}
			}
		}

		if((xEXT_CH__LLx__IN_OUT_FLAG[ll_b]->Check__DATA("OUT") > 0)
		&& (LLx__Is_Available(ll_b) > 0)
		&& (LLx__Is_VAC(ll_b) > 0))
		{
			if(LLx__Get_Occupied__InSlot(ll_b, lb_slotid) > 0)
			{
				sch_name.Format("%s-%1d", MODULE__LBB,lb_slotid);
				
				if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_name) > 0)
				{
					if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(sch_name,ds_sts) > 0)
					{
						lbb_portid = ds_sts.iPORT_ID;	
						lbb_slotid = ds_sts.iSLOT_ID;	

						xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_name,l_lbb_pmc,l_lbb_rcp);
					}
				}
			}
		}

		// ...
		int dual_check = -1;
		int lb_order = 1;

		CStringArray l_lba_pmc_name;
		CStringArray l_lba_pmc_rcp;
		CStringArray l_lbb_pmc_name;
		CStringArray l_lbb_pmc_rcp;

		// ...
		{
			l_lba_pmc_name.RemoveAll();
			l_lba_pmc_rcp.RemoveAll();
			l_lbb_pmc_name.RemoveAll();
			l_lbb_pmc_rcp.RemoveAll();

			l_lba_pmc_name.Copy(l_lba_pmc);
			l_lba_pmc_rcp.Copy(l_lba_rcp);
			l_lbb_pmc_name.Copy(l_lbb_pmc);
			l_lbb_pmc_rcp.Copy(l_lbb_rcp);
		}

		if((lba_portid > 0) && (lbb_portid > 0))
		{
			// ...
			{
				int lba__lp_i = lba_portid - 1;
				int lbb__lp_i = lbb_portid - 1;

				int lba__proc_flag = LPx__Check_Process_Type__Normal(lba__lp_i);
				int lbb__proc_flag = LPx__Check_Process_Type__Normal(lbb__lp_i);

				if(lba__proc_flag != lbb__proc_flag)
				{
					dual_check = 1;
				}
			}

			if(dual_check < 0)
			{
				if(Macro__Check_Equal__Any_String(l_lba_pmc,l_lbb_pmc) < 0)
				{
					// 경로가 독립적인 경우 ...
					{
						dual_check = 1;
					}
				}
			}

			if(dual_check < 0)
			{
				if(xEXT_CH__SCH_CONCURRENT_ALWAYS_APPLY->Check__DATA(STR__DISABLE) < 0)
				{
					if(lba_portid != lbb_portid)
					{
						lb_order = -1;

						// ...
						{	
							CUIntArray l_job_lp;
							SCH__Get_Job_LP_List(l_job_lp);

							if(l_job_lp.GetSize() > 1)
							{
								int cur_lp = l_job_lp[0];
	
								if(lba_portid == cur_lp)
								{
									lb_order = 1;
								}
								else if(lbb_portid == cur_lp)
								{
									lb_order = 2;
								}	
							}
						}

						if(lb_order > 0)
						{
							if(xEXT_CH__SCH_CONCURRENT_ALWAYS_APPLY->Check__DATA(STR__PPID_CHECK) > 0)
							{
								l_lba_pmc_name.RemoveAll();
								l_lba_pmc_rcp.RemoveAll();
								l_lbb_pmc_name.RemoveAll();
								l_lbb_pmc_rcp.RemoveAll();

								if(lb_order == 1)
								{
									l_lba_pmc_name.Copy(l_lba_pmc);
									l_lba_pmc_rcp.Copy(l_lba_rcp);

									Macro__Delete_Trg_With_Src(l_lba_pmc,
															   l_lba_rcp,
															   l_lbb_pmc,
															   l_lbb_rcp,
															   l_lbb_pmc_name,
															   l_lbb_pmc_rcp);

									if(l_lbb_pmc_name.GetSize() < 1)
									{
										l_lbb_pmc_name.Copy(l_lbb_pmc);
										l_lbb_pmc_rcp.Copy(l_lbb_rcp);
									}
								}
								else if(lb_order == 2)
								{
									l_lbb_pmc_name.Copy(l_lbb_pmc);
									l_lbb_pmc_rcp.Copy(l_lbb_rcp);

									Macro__Delete_Trg_With_Src(l_lbb_pmc,
															   l_lbb_rcp,
															   l_lba_pmc,
															   l_lba_rcp,
															   l_lba_pmc_name,
															   l_lba_pmc_rcp);

									if(l_lba_pmc_name.GetSize() < 1)
									{
										l_lba_pmc_name.Copy(l_lba_pmc);
										l_lba_pmc_rcp.Copy(l_lba_rcp);
									}
								}
							}
	
							dual_check = 1;
						}
					}
				}
			}
		}

		if((dual_check < 0)
		&& (xEXT_CH__SCH_CONCURRENT_ALWAYS_APPLY->Check__DATA(STR__PPID_CHECK) > 0))
		{
			int ppid_check = -1;

			if(ppid_check < 0)
			{
				if((lba_portid > 0)	&& (lbb_portid < 0))
				{
					ppid_check = 1;
				}
				else if((lba_portid < 0) && (lbb_portid > 0))
				{
					ppid_check = 1;
				}
			}

			if(ppid_check > 0)
			{
				// ...
				CUIntArray l_job_lp;
				SCH__Get_Job_LP_List(l_job_lp);

				if(l_job_lp.GetSize() > 1)
				{
					// ...
					CStringArray l_job1_pmc;
					CStringArray l_job2_pmc;

					int cur_job1_lp = l_job_lp[0];
					int cur_job2_lp = l_job_lp[1];

					xSCH_MATERIAL_CTRL->Get__ALL_PRC_MODULE_In_LPx(cur_job1_lp,l_job1_pmc);
					xSCH_MATERIAL_CTRL->Get__ALL_PRC_MODULE_In_LPx(cur_job2_lp,l_job2_pmc);

					if((Macro__Check_Equal__Any_String(l_job1_pmc,l_job2_pmc) > 0)
					&& (Macro__Check_Equal__All_String(l_job1_pmc,l_job2_pmc) < 0))
					{
						lb_order = -1;

						// ...
						{
							l_lba_pmc_name.RemoveAll();
							l_lba_pmc_rcp.RemoveAll();

							l_lbb_pmc_name.RemoveAll();
							l_lbb_pmc_rcp.RemoveAll();
						}

						if((lba_portid > 0) && (lba_portid != cur_job1_lp))	
						{
							// ...
							{
								lb_order = 1;
														
								xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(lba_portid,lba_slotid, l_lba_pmc_name,l_lba_pmc_rcp);
							}
						}
						else if((lbb_portid > 0) && (lbb_portid != cur_job1_lp))
						{
							// ...
							{
								lb_order = 2;
							
								xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(lbb_portid,lbb_slotid, l_lbb_pmc_name,l_lbb_pmc_rcp);
							}
						}

						if(lb_order > 0)
						{
							if(lb_order == 1)
							{
								Macro__Delete_Trg_With_Src(l_job1_pmc,
														   l_lba_pmc_name,
														   l_lba_pmc_rcp);

								if(l_lba_pmc_name.GetSize() < 1)
								{
									l_lba_pmc_name.Copy(l_lba_pmc);
									l_lba_pmc_rcp.Copy(l_lba_rcp);
								}
							}
							else if(lb_order == 2)
							{
								Macro__Delete_Trg_With_Src(l_job1_pmc,
														   l_lbb_pmc_name,
														   l_lbb_pmc_rcp);

								if(l_lbb_pmc_name.GetSize() < 1)
								{
									l_lbb_pmc_name.Copy(l_lbb_pmc);
									l_lbb_pmc_rcp.Copy(l_lbb_rcp);
								}
							}
							
							dual_check = 1;
						}
					}
				}
			}
		}

		if(dual_check > 0)
		{
			if(lb_order != 2)
			{
				try
				{
					Fnc__LBi_To_RB_With_Ready_PMC__ALL_MODE(p_variable,
															p_alarm, 
															STR__LBA,
															l_lba_pmc_name,
															l_lba_pmc_rcp,
															l_lbb_pmc_name,
															l_lbb_pmc_rcp);
				}
				catch(int err_flag)
				{
	
				}
	
				try
				{
					Fnc__LBi_To_RB_With_Ready_PMC__ALL_MODE(p_variable,
															p_alarm, 
															STR__LBB,
															l_lba_pmc_name,
															l_lba_pmc_rcp,
															l_lbb_pmc_name,
															l_lbb_pmc_rcp);
				}
				catch(int err_flag)
				{
	
				}
			}
			else if(lb_order == 2)
			{				
				try
				{
					Fnc__LBi_To_RB_With_Ready_PMC__ALL_MODE(p_variable,
														    p_alarm, 
															STR__LBB,
															l_lba_pmc_name,
															l_lba_pmc_rcp,
															l_lbb_pmc_name,
															l_lbb_pmc_rcp);
				}
				catch(int err_flag)
				{
					
				}

				try
				{
					Fnc__LBi_To_RB_With_Ready_PMC__ALL_MODE(p_variable,
															p_alarm, 
															STR__LBA,
															l_lba_pmc_name,
															l_lba_pmc_rcp,
															l_lbb_pmc_name,
															l_lbb_pmc_rcp);
				}
				catch(int err_flag)
				{
					
				}
			}
		}
		else
		{
			Fnc__LBi_To_RB_With_Ready_PMC__ALL_MODE(p_variable,
													p_alarm, 
													STR__ALL,
													l_lba_pmc_name,
													l_lba_pmc_rcp,
													l_lbb_pmc_name,
													l_lbb_pmc_rcp);
		}
	}

	NEXT__LOOP;
}

int  CObj_Fnc__DUAL_ARM_STD::
Get__First_Wafer_In_LBi(CII_OBJECT__VARIABLE *p_variable,
						CII_OBJECT__ALARM    *p_alarm,						 
						const CString& check_lbx_type,
						int& lba_flag,
						int& lbb_flag)
{
	int ll_a = _LLx_INDEX__LBA;
	int ll_b = _LLx_INDEX__LBB;

	// ...
	{
		CString var_data;
		int lba_count = 0;
		int lbb_count = 0;
		
		if((check_lbx_type.CompareNoCase(STR__ALL) == 0)
		|| (check_lbx_type.CompareNoCase(STR__LBA) == 0))
		{
			if((xEXT_CH__LLx__IN_OUT_FLAG[ll_a]->Check__DATA("OUT") > 0)
			&& (LLx__Is_Available(ll_a) > 0)
			&& (LLx__Check_Occupied__InSlot(ll_a) > 0))
			{
				if(SCH__LLx_CHECK_PRESSURE(ll_a, p_variable,p_alarm,1) < 0)
				{
					NEXT__LOOP;
				}
				
				xEXT_CH__LLx__IN_COUNT[ll_a]->Get__DATA(var_data);
				lba_count = atoi(var_data);
			}
		}
		
		if((check_lbx_type.CompareNoCase(STR__ALL) == 0)
		|| (check_lbx_type.CompareNoCase(STR__LBB) == 0))
		{
			if((xEXT_CH__LLx__IN_OUT_FLAG[ll_b]->Check__DATA("OUT") > 0)
			&& (LLx__Is_Available(ll_b) > 0)
			&& (LLx__Check_Occupied__InSlot(ll_b) > 0))
			{
				if(SCH__LLx_CHECK_PRESSURE(ll_b, p_variable,p_alarm,1) < 0)
				{
					NEXT__LOOP;
				}
				
				xEXT_CH__LLx__IN_COUNT[ll_b]->Get__DATA(var_data);
				lbb_count = atoi(var_data);
			}
		}
		
		CString para_module;
		CString para_slot;
		int slot_id;
		
		if((lba_count > 0)&&(lbb_count > 0))
		{
			if(lba_count <= lbb_count)
			{
				if(LLx__Get_Occupied__InSlot(ll_a, slot_id) < 0)
				{
					NEXT__LOOP;
				}
				
				para_module = MODULE__LBA;
				para_slot.Format("%1d",slot_id);
				
				lba_flag = 1;
			}
			else
			{
				if(LLx__Get_Occupied__InSlot(ll_b, slot_id) < 0)
				{
					NEXT__LOOP;
				}

				para_module = MODULE__LBB;
				para_slot.Format("%1d",slot_id);
				
				lbb_flag = 1;
			}
		}
		else if(lba_count > 0)
		{
			if(LLx__Get_Occupied__InSlot(ll_a, slot_id) < 0)	
			{
				NEXT__LOOP;
			}

			para_module = MODULE__LBA;
			para_slot.Format("%1d",slot_id);
			
			lba_flag = 1;
		}
		else if(lbb_count > 0)
		{
			if(LLx__Get_Occupied__InSlot(ll_b, slot_id) < 0)
			{
				NEXT__LOOP;
			}

			para_module = MODULE__LBB;
			para_slot.Format("%1d",slot_id);
			
			lbb_flag = 1;
		}
		else
		{
			NEXT__LOOP;
		}
	}

	return 1;
}
int  CObj_Fnc__DUAL_ARM_STD::
Check__First_Wafer_In_LBi(CII_OBJECT__VARIABLE *p_variable,
						  CII_OBJECT__ALARM    *p_alarm,						 
						  int& llx_id)
{
	int llx_count[CFG_LLx_LIMIT];
	int ll_i;

	for(ll_i=0; ll_i<iLLx_LIMIT; ll_i++)
	{
		llx_count[ll_i] = 0;

		if((xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
		&& (LLx__Is_Available(ll_i) > 0)
		&& (LLx__Check_Occupied__InSlot(ll_i) > 0))
		{
			if(SCH__LLx_CHECK_PRESSURE(ll_i, p_variable,p_alarm,1) < 0)
			{
				return -1;
			}

			CString var_data = xEXT_CH__LLx__IN_COUNT[ll_i]->Get__STRING();
			llx_count[ll_i] = atoi(var_data);
		}
	}

	// llx_count : Ascending Order Sort ...
	{
		for(ll_i=0; ll_i<iLLx_LIMIT; ll_i++)
		{
			int cmp_count = llx_count[ll_i];

			for(int ll_c=ll_i+1; ll_c<iLLx_LIMIT; ll_c++)
			{
				int cur_count = llx_count[ll_c];

				if(cur_count < cmp_count)		
				{
					llx_count[ll_i] = cur_count;
					llx_count[ll_c] = cmp_count;

					cmp_count = cur_count;
				}
			}
		}
	}

	// llx_count : Check ( > 0) ...
	{
		int llx_active = -1;

		for(ll_i=0; ll_i<iLLx_LIMIT; ll_i++)
		{
			int cur_count = llx_count[ll_i];

			if(cur_count > 0)
			{
				int slot_id;
				if(LLx__Get_Occupied__InSlot(ll_i, slot_id) < 0)
				{
					return -1;
				}

				llx_active = 1;
				llx_id = ll_i + 1;
			}

			if(llx_active > 0)
			{
				break;
			}
		}

		if(llx_active < 0)
		{
			return -1;
		}
	}

	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD::
Get__Arm_List_To_Process(CStringArray& l_arm)
{
	return _Get__Arm_List(l_arm, 1);
}
int  CObj_Fnc__DUAL_ARM_STD::
Get__Arm_List_To_LPx(CStringArray& l_arm)
{
	return _Get__Arm_List(l_arm, -1);
}
int  CObj_Fnc__DUAL_ARM_STD::
_Get__Arm_List(CStringArray& l_arm, const int proc_check)
{
	l_arm.RemoveAll();

	// ...
	CUIntArray l_portid;
	CUIntArray l_slotid;
	CString arm_type;

	int i_limit = 2;
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(i == 0)
		{
			if(VAC_RB__Check_Occupied__A_Arm() > 0)		arm_type = "A";
			else										continue;
		}
		else if(i == 1)
		{
			if(VAC_RB__Check_Occupied__B_Arm() > 0)		arm_type = "B";
			else										continue;
		}
		else
		{
			continue;
		}

		if(proc_check > 0)
		{
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) < 0)
				continue;
		}
		else
		{
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
				continue;
		}

		// ...
		IDS__SCH_MATERIAL_INFO db_info;

		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(arm_type, db_info) > 0)
		{
			l_arm.Add(arm_type);
			l_portid.Add(db_info.iSRC__PTN);
			l_slotid.Add(db_info.iSRC__STN);
		}
	}

	// Change Order ...
	i_limit = l_portid.GetSize();

	for(i=0; i<i_limit; i++)
	{
		int cmp_portid  = l_portid[i];
		int cmp_slotid  = l_slotid[i];
		CString cmp_arm = l_arm[i];

		for(int k=i+1; k<i_limit; k++)
		{
			int cur_portid  = l_portid[k];
			int cur_slotid  = l_slotid[k];
			CString cur_arm = l_arm[k];

			if(cur_portid != cmp_portid)		continue;
			if(cur_slotid >= cmp_slotid)		continue;

			// ...
			{
				l_portid[i] = cur_portid;
				l_slotid[i] = cur_slotid;
				l_arm[i] = cur_arm;

				l_portid[k] = cmp_portid;
				l_slotid[k] = cmp_slotid;
				l_arm[k] = cmp_arm;
			}

			cmp_portid = cur_portid;
			cmp_slotid = cur_slotid;
			cmp_arm = cur_arm;
		}
	}

	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD::
Change_Order__In_Count_Of_LLx(CUIntArray& l_count,
							  CStringArray& l_name,
							  CStringArray& l_slot)
{
	int i_limit = l_count.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		int cmp_count = l_count[i];
		
		CString cmp_name = l_name[i];
		CString cmp_slot = l_slot[i];

		for(int k=i+1; k<i_limit; k++)
		{
			int cur_count = l_count[k];

			CString cur_name = l_name[k];
			CString cur_slot = l_slot[k];

			if(cur_count < cmp_count)		
			{
				l_count[i] = cur_count;
				l_name[i]  = cur_name;
				l_slot[i]  = cur_slot;

				l_count[k] = cmp_count;
				l_name[k]  = cmp_name;
				l_slot[k]  = cmp_slot;

				cmp_count = cur_count;
			}
		}
	}

	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD::
Fnc__LBi_To_RB_With_Ready_PMC__ALL_MODE(CII_OBJECT__VARIABLE *p_variable,
										CII_OBJECT__ALARM *p_alarm,
										const CString& check_lbx_type,
										const CStringArray& l_lba_pmc_name,
										const CStringArray& l_lba_pmc_rcp,
										const CStringArray& l_lbb_pmc_name,
										const CStringArray& l_lbb_pmc_rcp)
{
	DECLARE__EXT_CTRL(p_variable);
	
	
	// ...
	CString log_id = "Fnc__LBi_To_RB_With_Ready_PMC__ALL_MODE()";

	// ...
	int lba_flag = -1;
	int lbb_flag = -1;

	if(Get__First_Wafer_In_LBi(p_variable,p_alarm,check_lbx_type,lba_flag,lbb_flag) < 0)
	{
		NEXT__LOOP;
	}

	// ...
	CString para_module;
	CString para_in_slot;
	CString para_out_slot;
	int slot_id;

	CStringArray l_change_pmc_name;
	CStringArray l_change_pmc_rcp;
	CStringArray l_change_pmc_stage;

	// ...
	{
		int lbx_flag = -1;

		int ll_limit = iLLx_LIMIT;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(ll_i == 0)		
			{
				if(lba_flag < 0)		continue;
			}
			else if(ll_i == 1)		
			{
				if(lbb_flag < 0)		continue;
			}
			else
			{
				continue;
			}

			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
			{
				if((SCH__LLx_CHECK_PRESSURE(ll_i, p_variable,p_alarm) > 0)
				&& (LLx__Is_Available(ll_i) > 0))
				{
					para_module = Get__LLx_NAME(ll_i);

					if(LLx__Get_Occupied__InSlot(ll_i, slot_id) > 0)
					{
						para_in_slot.Format("%1d", slot_id);

						// ...
						CString sch_name;
						sch_name.Format("%s-%s", para_module,para_in_slot);

						if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_name) > 0)
						{
							lbx_flag = 1;
						}
					}
					if(LLx__Get_Empty__OutSlot(ll_i, slot_id) > 0)
					{
						para_out_slot.Format("%1d",slot_id);	
					}
				}
			}
		}

		if(lbx_flag < 0)
		{
			NEXT__LOOP;
		}
	}

	// ...
	CString arm_type;
	bool ex_flag = false;

	// if(xCH_CFG__SCH_LLx_EXCHANGE_WHEN_PMC_EMPTY->Check__DATA(STR__ENABLE) > 0)
	{
		if(VAC_RB__Get_Occupied__Arm_Type(arm_type) > 0)
		{
			IDS__SCH_MATERIAL_STATUS ds_sts;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_sts) < 0)
			{
				NEXT__LOOP;
			}

			if(ds_sts.sMATERIAL_STS.CompareNoCase("PROCESSED") == 0)
			{
				if((para_in_slot.GetLength()  > 0)
				&& (para_out_slot.GetLength() > 0))
				{
					if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) < 0)
					{
						ex_flag = true;
					}
				}
			}
		}
	}

	// if((xCH_CFG__PICK_ARM_TYPE_FROM_LBX->Check__DATA("ALL") < 0)
	// || (xCH_CFG__PICK_ARM_TYPE_FROM_PMC->Check__DATA("ALL") < 0))
	// ...
	{
		int flag__wafer_ex = -1;

		if(ex_flag == true)
		{
			CString sch_name;
			sch_name.Format("%s-%s",para_module,para_in_slot);

			if(SCH__LBx_CAN_VENT(sch_name) < 0)
			{
				flag__wafer_ex = 1;
			}
		}	

		if(flag__wafer_ex < 0)
		{
			ex_flag = false;
			para_out_slot = "";

			if(xCH_CFG__SCH_LLx_EXCHANGE_WHEN_PMC_EMPTY->Check__DATA(STR__ENABLE) > 0)
			{
				if(VAC_RB__Check_All_Empty() < 0)
				{
					NEXT__LOOP;
				}
			}

			if(para_in_slot.GetLength() < 1)
			{
				NEXT__LOOP;
			}
		}

		// ...
		{
			CString empty_arm;
			
			if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
			{
				NEXT__LOOP;
			}
			
			// ...
			CStringArray l_pmc_name;
			CStringArray l_pmc_rcp;

			CString sch_name;
			sch_name.Format("%s-%s",para_module,para_in_slot);

			if(xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_name,l_pmc_name,l_pmc_rcp) > 0)
			{
				if((check_lbx_type.CompareNoCase(STR__LBA) == 0)
				&& (para_module.CompareNoCase(STR__LBA)    == 0))	
				{	
					if(Macro__Check__Src_Item_Included(l_lba_pmc_name,l_pmc_name) > 0)
					{
						l_pmc_name.Copy(l_lba_pmc_name);
						l_pmc_rcp.Copy(l_lba_pmc_rcp);

						// ...
						{
							int t_limit = l_pmc_name.GetSize();
							int t;
	
							for(t=0;t<t_limit;t++)
							{
								l_change_pmc_name.Add(l_pmc_name[t]);
								l_change_pmc_rcp.Add(l_pmc_rcp[t]);
								l_change_pmc_stage.Add("");
							}
						}
					}
				}
				else if((check_lbx_type.CompareNoCase(STR__LBB) == 0)
					 && (para_module.CompareNoCase(STR__LBB)    == 0))	
				{	
					if(Macro__Check__Src_Item_Included(l_lbb_pmc_name,l_pmc_name) > 0)
					{
						l_pmc_name.Copy(l_lbb_pmc_name);
						l_pmc_rcp.Copy(l_lbb_pmc_rcp);

						// ...
						{
							int t_limit = l_pmc_name.GetSize();
							int t;
							
							for(t=0;t<t_limit;t++)
							{
								l_change_pmc_name.Add(l_pmc_name[t]);
								l_change_pmc_rcp.Add(l_pmc_rcp[t]);
								l_change_pmc_stage.Add("");
							}
						}
					}
				}

				// ...
				int flag__lp_normal = 1;
				
				if(LPx__Get_Process_Type__Normal(sch_name,flag__lp_normal) < 0)
				{
					return -1;
				}

				// ...
				int pm_check = -1;
				int pm_i;

				int limit;
				int i;

				if(l_change_pmc_name.GetSize() > 0)
				{
					limit = l_change_pmc_name.GetSize();
				
					for(i=0;i<limit;i++)
					{
						pm_i = SCH__CHECK_PM_INDEX(l_change_pmc_name[i]);
						
						if(pm_i < 0)				continue;
						if(pm_i >= iPMx_SIZE)		continue;
						
						if(Fnc__PMx_Empty_Ready_Check(flag__lp_normal,pm_i,1,1) < 0)
						{
							continue;
						}
						
						pm_check = 1;
						break;
					}
				}
				else
				{
					limit = l_pmc_name.GetSize();

					for(i=0;i<limit;i++)
					{
						pm_i = SCH__CHECK_PM_INDEX(l_pmc_name[i]);
					
						if(pm_i < 0)				continue;
						if(pm_i >= iPMx_SIZE)		continue;
					
						if(Fnc__PMx_Empty_Ready_Check(flag__lp_normal,pm_i,1,1) < 0)
						{
							continue;
						}
					
						pm_check = 1;
						break;
					}
				}

				if(pm_check < 0)
				{
					// ...
					{
						int pm_check = -1;
						int pm_i;
						
						int limit;
						int i;

						if(l_change_pmc_name.GetSize() > 0)
						{
							limit = l_change_pmc_name.GetSize();

							for(i=0;i<limit;i++)
							{
								pm_i = SCH__CHECK_PM_INDEX(l_change_pmc_name[i]);
								
								if(pm_i < 0)				continue;
								if(pm_i >= iPMx_SIZE)		continue;
								
								if(flag__lp_normal > 0)
								{
									if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__NORMAL) < 0)
									{
										continue;
									}
								}
								else
								{
									if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__TEST) < 0)
									{
										continue;
									}
								}
								
								pm_check = 1;
								break;
							}
						}
						else
						{
							limit = l_pmc_name.GetSize();
						
							for(i=0;i<limit;i++)
							{
								pm_i = SCH__CHECK_PM_INDEX(l_pmc_name[i]);
							
								if(pm_i < 0)				continue;
								if(pm_i >= iPMx_SIZE)		continue;
							
								if(flag__lp_normal > 0)
								{
									if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__NORMAL) < 0)
									{
										continue;
									}
								}
								else
								{
									if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__TEST) < 0)
									{
										continue;
									}
								}
							
								pm_check = 1;
								break;
							}
						}

						// ...
						int pmc_count = 0;

						if(l_change_pmc_name.GetSize() > 0)
						{
							pmc_count = l_change_pmc_name.GetSize();
						}
						else
						{
							pmc_count = l_pmc_name.GetSize();
						}

						if((pm_check < 0) && (pmc_count > 0))	
						{
							int alarm_id = ALID__JOB_ERROR__MATERIAL_AND_PMC_PROC_TYPE_MISMATCH;

							CString alm_msg;
							CString alm_bff;
							CString r_act;

							// ...
							{
								CString str__proc_type;

								if(flag__lp_normal > 0)
								{
									str__proc_type = "NORMAL";
								}
								else
								{
									str__proc_type = "TEST";
								}	

								alm_bff.Format("The process type of material in \"%s\" is \"%s\". \n", sch_name,str__proc_type);
								alm_msg  = alm_bff;
								alm_bff.Format("At least, one PMC with \"%s\" process type must exist. \n", str__proc_type);
								alm_msg += alm_bff;
	
								alm_bff.Format("PMC List To Visit ...\n");
								alm_msg += alm_bff;

								if(l_change_pmc_name.GetSize() > 0)
								{
									int limit = l_change_pmc_name.GetSize();
									int i;
									
									for(i=0;i<limit;i++)
									{
										alm_bff.Format("   %1d) %s \n", i+1, l_change_pmc_name[i]);
										alm_msg += alm_bff;
									}
								}
								else
								{
									int limit = l_pmc_name.GetSize();
									int i;

									for(i=0;i<limit;i++)
									{
										alm_bff.Format("   %1d) %s \n", i+1, l_pmc_name[i]);
										alm_msg += alm_bff;
									}
								}
							}
							
							p_alarm->Check__ALARM(alarm_id,r_act);
							p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
						}
					}

					NEXT__LOOP;
				}
			}
		}
	}

	if(ex_flag == true)
	{
		CString empty_arm;
		
		if(VAC_RB__Get__Arm_Type_From_LBx(empty_arm) < 0)
		{
			NEXT__LOOP;
		}

		// ...
		{
			CString sch_module;

			// ...
			{
				int act_flag  = -1;
				int move_flag = -1;

				// ...
				sch_module.Format("%s-%s",para_module,para_out_slot);

				act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, ex_flag,arm_type,para_module,para_out_slot,sch_module);

				if(act_flag < 0)
				{
					move_flag = SCH__Check_Material_Place(arm_type);
				}
				else
				{
					move_flag = 1;
				}

				if(move_flag > 0)
				{
					xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);
				}

				if(act_flag < 0)
				{
					NEXT__LOOP;
				}
			}

			// ...
			if(xCH_CFG__PICK_ARM_TYPE_FROM_LBX->Check__DATA("ALL") > 0)
			{
				if(xCH_CFG__ROBOT_ARM_DIRECTION_TYPE->Check__DATA(STR__BI_DIRECTION) > 0)
				{
					empty_arm = arm_type;
				}
			}
			else
			{
				CString vac__arm_type;

				if(VAC_RB__Get_Empty__Arm_Type_From_LBx(vac__arm_type) > 0)
				{
					empty_arm = vac__arm_type;
				}
				else 
				{
					if(xCH_CFG__ROBOT_ARM_DIRECTION_TYPE->Check__DATA(STR__BI_DIRECTION) > 0)
					{
						empty_arm = arm_type;
					}
				}
			}

			// ...
			{
				int act_flag  = -1;
				int move_flag = -1;

				// ...
				sch_module.Format("%s-%s",para_module,para_in_slot);

				act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,empty_arm,para_module,para_in_slot,sch_module);

				if(act_flag < 0)
				{
					move_flag = SCH__Check_Material_Pick(empty_arm);
				}
				else
				{
					move_flag = 1;
				}
				
				if(move_flag > 0)
				{
					xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,empty_arm);

					// ...
					{
						SCH__Change_Current_Route_Step(p_variable,p_alarm, empty_arm);
					}
				}

				// ...
				{
					CString log_msg;
					CString log_bff;

					log_msg  = "\n";

					log_msg += "Fnc__LBi_To_RB_With_Ready_PMC__ALL_MODE() - CHECK1";
					log_msg += "\n";
				
					log_msg += "Action : SCH__PICK_MODULE()";
					log_msg += "\n";

					// ...
					{
						IDS__SCH_MATERIAL_STATUS ds_sts;
						xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(empty_arm,ds_sts);

						log_bff.Format("wafer <- [P%1d:%1d] \n", 
									   ds_sts.iPORT_ID,
									   ds_sts.iSLOT_ID);
						log_msg += log_bff;
					}

					log_bff.Format("arm_type <- [%s] \n", empty_arm);
					log_msg += log_bff;

					log_bff.Format("para_module  <- [%s] \n", para_module);
					log_msg += log_bff;

					log_bff.Format("para_in_slot <- [%s] \n", para_in_slot);
					log_msg += log_bff;

					log_bff.Format("act_flag  <- [%1d] \n", act_flag);
					log_msg += log_bff;

					log_bff.Format("move_flag <- [%1d] \n", move_flag);
					log_msg += log_bff;

					// ...
					{
						log_bff.Format("lbx_type <- [%s] \n", check_lbx_type);
						log_msg += log_bff;

						// ...
						int limit;
						int i;

						// lba info
						{
							log_msg += "lba info \n";

							// 
							limit = l_lba_pmc_name.GetSize();

							for(i=0;i<limit;i++)
							{
								log_bff.Format("   %1d) [%s][%s] \n",
									           i+1,
											   l_lba_pmc_name[i],
											   l_lba_pmc_rcp[i]);
								log_msg += log_bff;
							}
						}
						// lbb info
						{
							log_msg += "lbb info \n";
								
							// 
							limit = l_lbb_pmc_name.GetSize();
							
							for(i=0;i<limit;i++)
							{
								log_bff.Format("   %1d) [%s][%s] \n",
											   i+1,
											   l_lbb_pmc_name[i],
											   l_lbb_pmc_rcp[i]);
								log_msg += log_bff;
							}
						}
					}

					Fnc__LOG_CTRL(log_msg);
				}

				if(act_flag < 0)
				{
					NEXT__LOOP;
				}
			}
		}
	}
	else
	{
		if(para_in_slot.GetLength() > 0)
		{
			// ...
			CString empty_arm;

			if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
			{
				NEXT__LOOP;
			}

			// ...
			int act_flag  = -1;
			int move_flag = -1;

			// ...
			CString sch_module;
			sch_module.Format("%s-%s",para_module,para_in_slot);

			act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,empty_arm,para_module,para_in_slot,sch_module);

			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Pick(empty_arm);
			}
			else
			{
				move_flag = 1;
			}

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,empty_arm);	

				// ...
				{
					SCH__Change_Current_Route_Step(p_variable,p_alarm, empty_arm);
				}
			}

			// ...
			{
				CString log_msg;
				CString log_bff;
				
				log_msg  = "\n";
				
				log_msg += "Fnc__LBi_To_RB_With_Ready_PMC__ALL_MODE() - CHECK2";
				log_msg += "\n";
				
				log_msg += "Action : SCH__PICK_MODULE()";
				log_msg += "\n";

				log_bff.Format("arm_type <- [%s] \n", empty_arm);
				log_msg += log_bff;
				
				// ...
				{
					IDS__SCH_MATERIAL_STATUS ds_sts;
					xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(empty_arm,ds_sts);
					
					log_bff.Format("wafer <- [P%1d:%1d] \n", 
								   ds_sts.iPORT_ID,
								   ds_sts.iSLOT_ID);
					log_msg += log_bff;
				}

				log_bff.Format("para_module  <- [%s] \n", para_module);
				log_msg += log_bff;
				
				log_bff.Format("para_in_slot <- [%s] \n", para_in_slot);
				log_msg += log_bff;
				
				log_bff.Format("act_flag  <- [%1d] \n", act_flag);
				log_msg += log_bff;
				
				log_bff.Format("move_flag <- [%1d] \n", move_flag);
				log_msg += log_bff;
				
				// ...
				{
					log_bff.Format("lbx_type <- [%s] \n", check_lbx_type);
					log_msg += log_bff;
					
					// ...
					int limit;
					int i;
					
					// lba info
					{
						log_msg += "lba info \n";
						
						// 
						limit = l_lba_pmc_name.GetSize();
						
						for(i=0;i<limit;i++)
						{
							log_bff.Format("   %1d) [%s][%s] \n",
										   i+1,
										   l_lba_pmc_name[i],
										   l_lba_pmc_rcp[i]);
							log_msg += log_bff;
						}
					}
					// lbb info
					{
						log_msg += "lbb info \n";
						
						// 
						limit = l_lbb_pmc_name.GetSize();
						
						for(i=0;i<limit;i++)
						{
							log_bff.Format("   %1d) [%s][%s] \n",
										   i+1,
										   l_lbb_pmc_name[i],
										   l_lbb_pmc_rcp[i]);
							log_msg += log_bff;
						}
					}
				}

				Fnc__LOG_CTRL(log_msg);
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}
		else if((para_out_slot.GetLength() > 0)
			 && (arm_type.GetLength() > 0))
		{
			int act_flag  = -1;
			int move_flag = -1;

			// ...
			CString sch_module;
			sch_module.Format("%s-%s",para_module,para_out_slot);

			act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, ex_flag,arm_type,para_module,para_out_slot,sch_module);

			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Place(arm_type);
			}
			else
			{
				move_flag = 1;
			}

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);
			}

			// ...
			{
				CString log_msg;
				CString log_bff;
				
				log_msg  = "\n";
				
				log_msg += "Fnc__LBi_To_RB_With_Ready_PMC__ALL_MODE() - CHECK3";
				log_msg += "\n";
				
				log_msg += "Action : SCH__PLACE_MODULE()";
				log_msg += "\n";
				
				log_bff.Format("arm_type <- [%s] \n", arm_type);
				log_msg += log_bff;
				
				// ...
				{
					IDS__SCH_MATERIAL_STATUS ds_sts;
					xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_sts);
					
					log_bff.Format("wafer <- [P%1d:%1d] \n", 
								   ds_sts.iPORT_ID,
								   ds_sts.iSLOT_ID);
					log_msg += log_bff;
				}

				log_bff.Format("para_module  <- [%s] \n", para_module);
				log_msg += log_bff;
				
				log_bff.Format("para_out_slot <- [%s] \n", para_out_slot);
				log_msg += log_bff;
				
				log_bff.Format("act_flag  <- [%1d] \n", act_flag);
				log_msg += log_bff;
				
				log_bff.Format("move_flag <- [%1d] \n", move_flag);
				log_msg += log_bff;
				
				// ...
				{
					log_bff.Format("lbx_type <- [%s] \n", check_lbx_type);
					log_msg += log_bff;
					
					// ...
					int limit;
					int i;
					
					// lba info
					{
						log_msg += "lba info \n";
						
						// 
						limit = l_lba_pmc_name.GetSize();
						
						for(i=0;i<limit;i++)
						{
							log_bff.Format("   %1d) [%s][%s] \n",
										   i+1,
										   l_lba_pmc_name[i],
										   l_lba_pmc_rcp[i]);
							log_msg += log_bff;
						}
					}
					// lbb info
					{
						log_msg += "lbb info \n";
						
						// 
						limit = l_lbb_pmc_name.GetSize();
						
						for(i=0;i<limit;i++)
						{
							log_bff.Format("   %1d) [%s][%s] \n",
										   i+1,
										   l_lbb_pmc_name[i],
										   l_lbb_pmc_rcp[i]);
							log_msg += log_bff;
						}
					}
				}

				Fnc__LOG_CTRL(log_msg);
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}
		else
		{
			NEXT__LOOP;
		}
	}	

	// LLx Check ...
	{
		int ll_i = Get__LLx_INDEX(para_module);
		if(ll_i >= 0)
		{
			if(LLx__Check_Empty__InSlot(ll_i) > 0)
			{
				if(SCH_RUN__LLx_VENT(ll_i, log_id, "1") > 0)
				{
					xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
				}
			}
		}
	}

	NEXT__LOOP;
}

int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__LBi_RB__ALL_MODE(CII_OBJECT__VARIABLE *p_variable,
							CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "AUTO_CTRL__LBi_RB__ALL_MODE()";

	// ...
	{
		CString arm_type;
			
		// Arm : A ...
		if(VAC_RB__Check_Occupied__A_Arm() > 0)
		{
			arm_type = "A";
				
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				NEXT__LOOP;
			}
		}
		// Arm : B ...
		if(VAC_RB__Check_Occupied__B_Arm() > 0)
		{
			arm_type = "B";
				
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				NEXT__LOOP;
			}
		}
	}

	// ...
	int llx_active_id = -1;

	// ...
	{
		int llx_count[CFG_LLx_LIMIT];
		int ll_i;

		// LLx : State Check ...
		{
			for(ll_i=0; ll_i<iLLx_LIMIT; ll_i++)
			{
				llx_count[ll_i] = 0;

				if((xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
				&& (LLx__Is_Available(ll_i) > 0)
				&& (LLx__Check_Occupied__InSlot(ll_i) > 0))
				{
					if(SCH__LLx_CHECK_PRESSURE(ll_i, p_variable,p_alarm,1) < 0)
					{
						NEXT__LOOP;
					}

					CString var_data = xEXT_CH__LLx__IN_COUNT[ll_i]->Get__STRING();
					llx_count[ll_i] = atoi(var_data);
				}
			}
		}

		// llx_count : Ascending Order Sort ...
		{
			for(ll_i=0; ll_i<iLLx_LIMIT; ll_i++)
			{
				int cmp_count = llx_count[ll_i];

				for(int ll_c=ll_i+1; ll_c<iLLx_LIMIT; ll_c++)
				{
					int cur_count = llx_count[ll_c];

					if(cur_count < cmp_count)		
					{
						llx_count[ll_i] = cur_count;
						llx_count[ll_c] = cmp_count;

						cmp_count = cur_count;
					}
				}
			}
		}

		// ...
		CString para_module;
		CString para_slot;

		// LLx ...
		{		
			for(ll_i=0; ll_i<iLLx_LIMIT; ll_i++)
			{
				int cur_count = llx_count[ll_i];

				if(cur_count > 0)
				{
					int slot_id;

					if(LLx__Get_Occupied__InSlot(ll_i, slot_id) < 0)
					{
						NEXT__LOOP;
					}

					// ...
					llx_active_id = ll_i + 1;

					para_module = Get__LLx_NAME(ll_i);
					para_slot.Format("%1d",slot_id);
				}

				if(llx_active_id > 0)
				{
					break;
				}
			}

			if(llx_active_id < 0)
			{
				NEXT__LOOP;
			}
		}

		if(VAC_RB__Check_Dual_Arm_Enable() > 0)
		{
			CString arm_type;

			if(VAC_RB__Get_Occupied__Arm_Type(arm_type) > 0)
			{
				IDS__SCH_MATERIAL_STATUS ds_sts;
				xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_sts);

				int material_check = -1;
	
				if(ds_sts.sMATERIAL_STS.CompareNoCase("ALIGNED") == 0)
				{
					material_check = 1;
				}
				else if(ds_sts.sMATERIAL_STS.CompareNoCase("PROCESSED") == 0)
				{
					if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
					{
						material_check = 1;
					}
				}

				if(material_check > 0)
				{
					CString empty_arm;
					
					if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
					{
						NEXT__LOOP;
					}

					// ...
					{
						CStringArray l_pm;
						CStringArray l_rcp;

						if(xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type,l_pm,l_rcp) > 0)
						{
							int flag__lp_normal = 1;
							
							if(LPx__Get_Process_Type__Normal(arm_type,flag__lp_normal) < 0)
							{
								return -1;
							}

							// ...
							int pm_i;
	
							int limit = l_pm.GetSize();
							int i;

							for(i=0;i<limit;i++)
							{
								pm_i = SCH__CHECK_PM_INDEX(l_pm[i]);
					
								if(pm_i < 0)				continue;
								if(pm_i >= iPMx_SIZE)		continue;

								if(flag__lp_normal > 0)
								{
									if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__NORMAL) > 0)
									{
										if(PMx__Is_Available(pm_i) < 0)
										{
											continue;
										}
									}
								}
								else
								{
									if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__TEST) > 0)
									{
										if(PMx__Is_Available(pm_i) < 0)
										{
											continue;
										}
									}
								}

								NEXT__LOOP;
							}
						}
					}

					// ...
					CString sch_module;
					sch_module.Format("%s-%s",para_module,para_slot);

					CStringArray l_pm;
					CStringArray l_rcp;
					xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_module,l_pm,l_rcp);

					// ...
					int flag__lp_normal = 1;
					
					if(LPx__Get_Process_Type__Normal(sch_module,flag__lp_normal) < 0)
					{
						return -1;
					}

					// ...
					int pm_i;

					int limit = l_pm.GetSize();
					int i;

					for(i=0;i<limit;i++)
					{
						pm_i = SCH__CHECK_PM_INDEX(l_pm[i]);
						
						if(pm_i < 0)				continue;
						if(pm_i >= iPMx_SIZE)		continue;

						if(Fnc__PMx_Empty_Ready_Check(flag__lp_normal,pm_i,1) < 0)
						{
							continue;
						}

						// ...
						{
							CString pm_name = l_pm[i];
							CString pm_slot = "1";
							CString pm_rcp  = l_rcp[i];

							Seq__LBi_PMx(p_variable,
										 p_alarm,
										 empty_arm,
										 para_module,para_slot,
										 pm_i,pm_name,pm_slot,pm_rcp);
						}
						
						NEXT__LOOP;
					}

					NEXT__LOOP;
				}
			}
		}
		else
		{
			CString empty_arm;
			
			if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
			{
				NEXT__LOOP;
			}

			// ...
			CString sch_module;
			sch_module.Format("%s-%s",para_module,para_slot);

			CStringArray l_pm;
			CStringArray l_rcp;
			xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_module,l_pm,l_rcp);

			// ...
			int flag__lp_normal = 1;
			
			if(LPx__Get_Process_Type__Normal(sch_module,flag__lp_normal) < 0)
			{
				return -1;
			}

			// ...
			int pm_i;

			int limit = l_pm.GetSize();
			int i;

			for(i=0;i<limit;i++)
			{
				pm_i = SCH__CHECK_PM_INDEX(l_pm[i]);
					
				if(pm_i < 0)				continue;
				if(pm_i >= iPMx_SIZE)		continue;

				if(Fnc__PMx_Empty_Ready_Check(flag__lp_normal,pm_i,1) < 0)
				{
					continue;
				}

				// ...
				{
					CString pm_name = l_pm[i];
					CString pm_slot = "1";
					CString pm_rcp  = l_rcp[i];

					Seq__LBi_PMx(p_variable,
								 p_alarm,
								 empty_arm,
								 para_module,para_slot,
								 pm_i,pm_name,pm_slot,pm_rcp);
				}

				NEXT__LOOP;
			}

			NEXT__LOOP;
		}
	}

	// ...
	int lbx_flag = -1;

	CString para_module;
	CString para_in_slot;
	CString para_out_slot;
	int slot_id;

	if(llx_active_id > 0)
	{
		int ll_i = llx_active_id - 1;

		if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
		{
			if((SCH__LLx_CHECK_PRESSURE(ll_i, p_variable,p_alarm) > 0)
			&& (LLx__Is_Available(ll_i) > 0))
			{
				para_module = Get__LLx_NAME(ll_i);

				if(LLx__Get_Occupied__InSlot(ll_i, slot_id) > 0)
				{
					para_in_slot.Format("%1d", slot_id);
					lbx_flag = 1;
				}
				if(LLx__Get_Empty__OutSlot(ll_i, slot_id) > 0)
				{
					para_out_slot.Format("%1d", slot_id);
				}
			}
		}
	}

	if(lbx_flag < 0)
	{
		NEXT__LOOP;
	}

	// ...
	CString arm_type;
	bool ex_flag = false;

	if(VAC_RB__Get_Occupied__Arm_Type(arm_type) > 0)
	{
		IDS__SCH_MATERIAL_STATUS ds_sts;
		
		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_sts) < 0)
		{
			NEXT__LOOP;
		}

		if(ds_sts.sMATERIAL_STS.CompareNoCase("PROCESSED") == 0)
		{
			if((para_in_slot.GetLength()  > 0)
			&& (para_out_slot.GetLength() > 0))
			{
				CStringArray l_pm;
				CStringArray l_rcp;

				if(xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type,l_pm,l_rcp) < 0)
				{
					ex_flag = true;
				}
			}
		}
		else
		{
			arm_type = "";
		}
	}

	if(ex_flag == true)
	{
		CString empty_arm;
		if(VAC_RB__Get__Arm_Type_From_LBx(empty_arm) < 0)
		{
			NEXT__LOOP;
		}

		if(xCH_CFG__LBx_SWAP_FLAG->Check__DATA("ENABLE") > 0)
		{
			CString sch_place_arm;
			CString sch_place_module;

			CString sch_pick_arm;
			CString sch_pick_module;

			sch_place_arm = arm_type;
			sch_place_module.Format("%s-%s",para_module,para_out_slot);

			sch_pick_arm = empty_arm;
			sch_pick_module.Format("%s-%s",para_module,para_in_slot);

			if(SCH__SWAP_LBx(p_variable,
							 p_alarm,
							 para_module,
							 arm_type,
							 para_out_slot,
							 empty_arm,
							 para_in_slot,
							 sch_place_module,
							 sch_pick_module) < 0)
			{
				xEXT_CH__JOB_CTRL->Set__DATA("Abort");

				// ...
				int alarm_id = ALID__SWAP_ERROR;
				CString alarm_msg;
				CString r_act;

				alarm_msg.Format("Swap Error occured when Vac-Robot is swaping with %s.\n",para_module);

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alarm_msg);

				Sleep(990);
				xSCH_MATERIAL_CTRL->Clear__ALL_MATERIAL_INFO();

				NEXT__LOOP;
			}

			xSCH_MATERIAL_CTRL->Place__To_MODULE(sch_place_arm,sch_place_module);
			xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_pick_module,sch_pick_arm);
		}
		else
		{
			CString sch_module;

			// ...
			{
				int act_flag  = -1;
				int move_flag = -1;

				sch_module.Format("%s-%s",para_module,para_out_slot);

				act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, ex_flag,arm_type,para_module,para_out_slot,sch_module);

				if(act_flag < 0)
				{
					move_flag = SCH__Check_Material_Place(arm_type);
				}
				else
				{
					move_flag = 1;
				}

				if(move_flag > 0)
				{
					xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);
				}

				if(act_flag < 0)
				{
					NEXT__LOOP;
				}
			}

			if(xCH_CFG__PICK_ARM_TYPE_FROM_LBX->Check__DATA("ALL") > 0)
			{
				if(xCH_CFG__ROBOT_ARM_DIRECTION_TYPE->Check__DATA(STR__BI_DIRECTION) > 0)
				{
					empty_arm = arm_type;
				}
			}
			else
			{
				CString vac__arm_type;

				if(VAC_RB__Get_Empty__Arm_Type_From_LBx(vac__arm_type) > 0)
				{
					empty_arm = vac__arm_type;
				}
				else 
				{
					if(xCH_CFG__ROBOT_ARM_DIRECTION_TYPE->Check__DATA(STR__BI_DIRECTION) > 0)
					{
						empty_arm = arm_type;
					}
				}
			}

			// ...
			{
				int act_flag  = -1;
				int move_flag = -1;

				sch_module.Format("%s-%s",para_module,para_in_slot);

				act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,empty_arm,para_module,para_in_slot,sch_module);
	
				if(act_flag < 0)
				{
					move_flag = SCH__Check_Material_Pick(empty_arm);
				}
				else
				{
					move_flag = 1;
				}

				if(move_flag > 0)
				{
					xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,empty_arm);
				}

				if(act_flag < 0)
				{
					NEXT__LOOP;
				}
			}
		}
	}
	else
	{
		if(para_in_slot.GetLength() > 0)
		{
			CString empty_arm;
			
			if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
			{
				NEXT__LOOP;
			}

			// ....
			{
				int act_flag  = -1;
				int move_flag = -1;

				CString sch_module;
				sch_module.Format("%s-%s",para_module,para_in_slot);

				act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,empty_arm,para_module,para_in_slot,sch_module);

				if(act_flag < 0)
				{
					move_flag = SCH__Check_Material_Pick(empty_arm);
				}
				else
				{
					move_flag = 1;
				}

				if(move_flag > 0)
				{
					xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,empty_arm);	
				}

				if(act_flag < 0)
				{
					NEXT__LOOP;
				}
			}
		}
		else if((para_out_slot.GetLength() > 0)
			 && (arm_type.GetLength() > 0))
		{
			int act_flag  = -1;
			int move_flag = -1;

			CString sch_module;
			sch_module.Format("%s-%s",para_module,para_out_slot);

			act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, ex_flag,arm_type,para_module,para_out_slot,sch_module);

			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Place(arm_type);
			}
			else
			{
				move_flag = 1;
			}

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}
		else
		{
			NEXT__LOOP;
		}
	}	

	// LLx Check ...
	{
		int ll_i = Get__LLx_INDEX(para_module);
		if(ll_i >= 0)
		{
			if(LLx__Check_Empty__InSlot(ll_i) > 0)
			{
				if(SCH_RUN__LLx_VENT(ll_i, log_id, "1") > 0)
				{
					xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
				}
			}
		}
	}

	NEXT__LOOP;
}

int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__LBi_RB__1_SLOT_ALL_MODE_NEW(CII_OBJECT__VARIABLE *p_variable,
								       CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CString log_id = "AUTO_CTRL__LBi_RB__1_SLOT_ALL_MODE_NEW()";

	// ...
	int ll_a = _LLx_INDEX__LBA;
	int ll_b = _LLx_INDEX__LBB;

	// ...
	int lba_flag = -1;
	int lbb_flag = -1;

	CString para_module;
	CString para_slot;

	// ...
	{
		CString var_data;
		int lba_count = 0;
		int lbb_count = 0;

		if((xEXT_CH__LLx__IN_OUT_FLAG[ll_a]->Check__DATA("OUT") > 0)
		&& (LLx__Is_Available(ll_a) > 0)
		&& (LLx__Check_Occupied__InSlot_With_1_Slot_All_Mode(ll_a) > 0))
		{
			if(SCH__LLx_CHECK_PRESSURE(ll_a, p_variable,p_alarm,1) < 0)
			{
				NEXT__LOOP;
			}

			xEXT_CH__LLx__IN_COUNT[ll_a]->Get__DATA(var_data);
			lba_count = atoi(var_data);
		}

		if((xEXT_CH__LLx__IN_OUT_FLAG[ll_b]->Check__DATA("OUT") > 0)
		&& (LLx__Is_Available(ll_b) > 0)
		&& (LLx__Check_Occupied__InSlot_With_1_Slot_All_Mode(ll_b) > 0))
		{
			if(SCH__LLx_CHECK_PRESSURE(ll_b, p_variable,p_alarm,1) < 0)
			{
				NEXT__LOOP;
			}

			xEXT_CH__LLx__IN_COUNT[ll_b]->Get__DATA(var_data);
			lbb_count = atoi(var_data);
		}

		// ...
		int slot_id;

		if((lba_count > 0)&&(lbb_count > 0))
		{
			if(lba_count <= lbb_count)
			{
				if(LLx__Get_Occupied__InSlot_With_1_Slot_All_Mode(ll_a, slot_id) < 0)
				{
					NEXT__LOOP;
				}

				para_module = MODULE__LBA;
				para_slot.Format("%1d",slot_id);

				lba_flag = 1;
			}
			else
			{
				if(LLx__Get_Occupied__InSlot_With_1_Slot_All_Mode(ll_b, slot_id) < 0)
				{
					NEXT__LOOP;
				}

				para_module = MODULE__LBB;
				para_slot.Format("%1d",slot_id);

				lbb_flag = 1;
			}
		}
		else if(lba_count > 0)
		{
			if(LLx__Get_Occupied__InSlot_With_1_Slot_All_Mode(ll_a, slot_id) < 0)
			{
				NEXT__LOOP;
			}

			para_module = MODULE__LBA;
			para_slot.Format("%1d",slot_id);

			lba_flag = 1;
		}
		else if(lbb_count > 0)
		{
			if(LLx__Get_Occupied__InSlot_With_1_Slot_All_Mode(ll_b, slot_id) < 0)
			{
				NEXT__LOOP;
			}

			para_module = MODULE__LBB;
			para_slot.Format("%1d",slot_id);

			lbb_flag = 1;
		}
		else
		{
			NEXT__LOOP;
		}
	}

	// ...
	CString para_in_slot;
	CString para_out_slot;
	int slot_id;

	if(lba_flag > 0)
	{
		if(xEXT_CH__LLx__IN_OUT_FLAG[ll_a]->Check__DATA("OUT") > 0)
		{
			if((SCH__LLx_CHECK_PRESSURE(ll_a, p_variable,p_alarm) > 0)
			&& (LLx__Is_Available(ll_a) > 0))
			{
				if(LLx__Get_Occupied__InSlot_With_1_Slot_All_Mode(ll_a, slot_id) > 0)
				{
					para_in_slot.Format("%1d",slot_id);
					para_out_slot.Format("%1d",slot_id);
				}
			}
		}
	}
	if(lbb_flag > 0)
	{	
		if(xEXT_CH__LLx__IN_OUT_FLAG[ll_b]->Check__DATA("OUT") > 0)
		{
			if((SCH__LLx_CHECK_PRESSURE(ll_b, p_variable,p_alarm) > 0)
			&& (LLx__Is_Available(ll_b) > 0))
			{
				para_module = MODULE__LBB;

				if(LLx__Get_Occupied__InSlot_With_1_Slot_All_Mode(ll_b, slot_id) > 0)
				{
					para_in_slot.Format("%1d",slot_id);
					para_out_slot.Format("%1d",slot_id);
				}
			}
		}
	}

	// ...
	CString arm_type = "";
	bool ex_flag = false;

	if(VAC_RB__Get_Occupied__Arm_Type(arm_type) > 0)
	{
		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) < 0)
		{
			int active__sch_mode = -1;
			int active__sch_ll   = -1;

			// ...
			CStringArray l_ll_id;
			CStringArray l_ll_mode;
			CStringArray l_ll_slot;

			xSCH_MATERIAL_CTRL->Get__LLx_OUT_OF_EDIT_TYPE(arm_type, l_ll_id,l_ll_mode,l_ll_slot);

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

			if((para_in_slot.GetLength()  > 0)
			&& (para_out_slot.GetLength() > 0))
			{
				CStringArray l_pm;
				CStringArray l_rcp;

				if(xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type,l_pm,l_rcp) < 0)
				{
					if(active__sch_mode < 0)
					{
						ex_flag = true;
					}
					else
					{
						// LBA
						if((active__sch_ll == 1)
						&& (para_module.CompareNoCase(MODULE__LBA) == 0))
						{
							ex_flag = true;
						}
						
						// LBB
					    if((active__sch_ll == 2)				
						&& (para_module.CompareNoCase(MODULE__LBB) == 0))
						{
							ex_flag = true;
						}
					}
				}
			}
		}

		// ...
	}

	if(ex_flag == true)
	{
		CString sch_module;

		// ...
		{
			CString empty_arm;

			if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
			{
				NEXT__LOOP;
			}

			// ...
			int act_flag  = -1;
			int move_flag = -1;

			sch_module.Format("%s-%s",para_module,para_in_slot);

			act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, ex_flag,empty_arm,para_module,para_in_slot,sch_module);

			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Pick(empty_arm);
			}
			else
			{
				move_flag = 1;
			}

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,empty_arm);
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}

		// ...
		{
			int act_flag  = -1;
			int move_flag = -1;

			sch_module.Format("%s-%s",para_module,para_out_slot);

			act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, false,arm_type,para_module,para_out_slot,sch_module);

			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Place(arm_type);
			}
			else
			{
				move_flag = 1;
			}

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}

		// LLx Check ...
		{
			int ll_i = Get__LLx_INDEX(para_module);
			if(ll_i >= 0)
			{
				if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") < 0)
				{
					if(SCH_RUN__LLx_VENT(ll_i, log_id, "1") > 0)
					{
						xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
					}
				}
			}
		}
	}
	else
	{
		CString empty_arm;

		if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
		{
			NEXT__LOOP;
		}

		// LBo -> PMx ...
		{
			CString arm_type;

			if(VAC_RB__Get_Occupied__Arm_Type(arm_type) > 0)
			{
				IDS__SCH_MATERIAL_STATUS ds_sts;
				xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_sts);

				int material_check = -1;

				if(ds_sts.sMATERIAL_STS.CompareNoCase("ALIGNED") == 0)
				{
					material_check = 1;
				}
				else if(ds_sts.sMATERIAL_STS.CompareNoCase("PROCESSED") == 0)
				{
					if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
					{
						material_check = 1;
					}
				}

				if(material_check > 0)
				{
					CStringArray l_pmx__rb;
					CStringArray l_rcp__rb;

					if(xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type, l_pmx__rb,l_rcp__rb) > 0)
					{
						int limit = l_pmx__rb.GetSize();
						int i;

						for(i=0; i<limit; i++)
						{
							int pm_i = SCH__CHECK_PM_INDEX(l_pmx__rb[i]);

							if(pm_i < 0)				continue;
							if(pm_i >= iPMx_SIZE)		continue;

							if(PMx__Is_Available(pm_i) < 0)
							{
								continue;
							}

							NEXT__LOOP;
						}
					}

					// ...
					CStringArray l_pmx__ll;
					CStringArray l_rcp__ll;

					CString sch_module;
					sch_module.Format("%s-%s", para_module,para_slot);

					xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_module, l_pmx__ll,l_rcp__ll);

					if(Macro__Check_Equal__Any_String(l_pmx__rb, l_pmx__ll) > 0)
					{
						NEXT__LOOP;
					}

					int limit = l_pmx__ll.GetSize();
					int i;

					for(i=0; i<limit; i++)
					{
						int pm_i = SCH__CHECK_PM_INDEX(l_pmx__ll[i]);

						if(pm_i < 0)				continue;
						if(pm_i >= iPMx_SIZE)		continue;

						if(PMx__Is_Available(pm_i) < 0)				continue;
						if(PMx__Check_Empty__SlotStatus(pm_i) < 0)	continue;

						// ...
						CString pm_name = l_pmx__ll[i];
						CString pm_slot = "1";
						CString pm_rcp  = l_rcp__ll[i];

						Seq__LBi_PMx(p_variable,
									 p_alarm,
									 empty_arm,
									 para_module,para_slot,
									 pm_i,pm_name,pm_slot,pm_rcp);

						NEXT__LOOP;
					}

					NEXT__LOOP;
				}
			}
		}
	}

	NEXT__LOOP;
}

int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__LBi_PMx__ONLY_MODE(CII_OBJECT__VARIABLE *p_variable,
							  CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CString para_module;
	CString para_slot;
	int slot_id;
	int loop = 1;
	int db_count = 0;

	while(loop > 0)
	{
		loop = -1;

		// LLx ...
		{
			int active__only_input = -1;

			int ll_limit = iLLx_LIMIT;
			int ll_i;

			for(ll_i=0; ll_i<ll_limit; ll_i++)
			{
				if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
				{
					active__only_input = 1;

					if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") < 0)
					{
						NEXT__LOOP;
					}

					if(LLx__Is_Available(ll_i)   < 0)
					{
						NEXT__LOOP;
					}
					if(LLx__Get_Occupied__InSlot(ll_i, db_count,slot_id) < 0)
					{
						NEXT__LOOP;
					}

					if(SCH__LLx_CHECK_PRESSURE(ll_i, p_variable,p_alarm,1) < 0)
					{
						NEXT__LOOP;
					}

					db_count++;

					para_module = Get__LLx_NAME(ll_i);
					para_slot.Format("%1d",slot_id);
				}
			}

			if(active__only_input < 0)
			{
				NEXT__LOOP;
			}
		}

		// ...
		CString empty_arm;

		if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
		{
			NEXT__LOOP;
		}

		// ...
		CString arm_type;

		if(VAC_RB__Get_Occupied__Arm_Type(arm_type) > 0)
		{
			IDS__SCH_MATERIAL_STATUS ds_sts;
			xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_sts);

			int material_check = -1;

			if(ds_sts.sMATERIAL_STS.CompareNoCase("ALIGNED") == 0)
			{
				material_check = 1;
			}
			else if(ds_sts.sMATERIAL_STS.CompareNoCase("PROCESSED") == 0)
			{
				if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
				{
					material_check = 1;
				}
			}

			if(material_check > 0)
			{
				// ...
				{
					CStringArray l_pm;
					CStringArray l_rcp;

					if(xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type,l_pm,l_rcp) > 0)
					{
						int pm_i;

						int limit = l_pm.GetSize();
						int i;

						for(i=0;i<limit;i++)
						{
							pm_i = SCH__CHECK_PM_INDEX(l_pm[i]);
					
							if(pm_i < 0)				continue;
							if(pm_i >= iPMx_SIZE)		continue;

							if(PMx__Is_Available(pm_i) < 0)		continue;

							NEXT__LOOP;
						}
					}
				}

				// ...
				CString sch_module;
				sch_module.Format("%s-%s",para_module,para_slot);

				CStringArray l_pm;
				CStringArray l_rcp;
				xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_module,l_pm,l_rcp);

				int pm_i;
				int limit = l_pm.GetSize();
				int i;

				for(i=0;i<limit;i++)
				{
					pm_i = SCH__CHECK_PM_INDEX(l_pm[i]);
					
					if(pm_i < 0)				continue;
					if(pm_i >= iPMx_SIZE)		continue;

					if(PMx__Is_Available(pm_i) < 0)				continue;
					if(PMx__Check_Empty__SlotStatus(pm_i) < 0)	continue;

					// ...
					CString pm_name = l_pm[i];
					CString pm_slot = "1";
					CString pm_rcp  = l_rcp[i];

					Seq__LBi_PMx(p_variable,
								 p_alarm,
								 empty_arm,
								 para_module,para_slot,
								 pm_i,pm_name,pm_slot,pm_rcp);

					NEXT__LOOP;
				}
			}
		}
	}

	NEXT__LOOP;
}
int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__LBi_PMx__ALL_MODE(CII_OBJECT__VARIABLE *p_variable,
							CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	if(VAC_RB__Check_All_Empty() > 0)
	{
		NEXT__LOOP;
	}

	if(VAC_RB__Check_Dual_Arm_Enable() < 0)
	{
		if(VAC_RB__Check_All_Empty() < 0)
		{
			NEXT__LOOP;
		}
	}

	// ...
	{
		CString arm_type;
		
		// Arm : A ...
		if(VAC_RB__Check_Occupied__A_Arm() > 0)
		{
			arm_type = "A";
			
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				if(xCH_CFG__SCH_EXCHANGE_PRIORITY->Check__DATA(STR__PMC) > 0)
				{
					if(Fnc__PMC_Empty_Ready_Check(arm_type) > 0)
					{
						NEXT__LOOP;
					}
				}
			}
		}
		// Arm : B ...
		if(VAC_RB__Check_Occupied__B_Arm() > 0)
		{
			arm_type = "B";
			
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				if(xCH_CFG__SCH_EXCHANGE_PRIORITY->Check__DATA(STR__PMC) > 0)
				{
					if(Fnc__PMC_Empty_Ready_Check(arm_type) > 0)
					{
						NEXT__LOOP;
					}
				}
			}
		}
	}

	// ...
	CString para_module;
	CString para_slot;
	int slot_id;

	CString var_data;

	int ll_limit = iLLx_LIMIT;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if((xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
		&& (LLx__Is_Available(ll_i) > 0)
		&& (LLx__Check_Occupied__InSlot(ll_i) > 0))
		{
			if(SCH__LLx_CHECK_PRESSURE(ll_i, p_variable,p_alarm,1) < 0)
			{
				continue;
			}

			if(LLx__Get_Occupied__InSlot(ll_i, slot_id) < 0)
			{
				continue;
			}

			para_module = Get__LLx_NAME(ll_i);
			para_slot.Format("%1d",slot_id);
		}

		// ...
		CString empty_arm;

		if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
		{
			// ...
			{
				CString cfg__arm_from_lbx;
				CString cfg__arm_from_pmc;

				xCH_CFG__PICK_ARM_TYPE_FROM_LBX->Get__DATA(cfg__arm_from_lbx);
				xCH_CFG__PICK_ARM_TYPE_FROM_PMC->Get__DATA(cfg__arm_from_pmc);

				// Alarm Report ...
				
			}

			NEXT__LOOP;
		}

		// ...
		CString arm_type;

		if(VAC_RB__Get_Occupied__Arm_Type(arm_type) > 0)
		{
			IDS__SCH_MATERIAL_STATUS ds_sts;
			xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_sts);

			int material_check = -1;

			if(ds_sts.sMATERIAL_STS.CompareNoCase("ALIGNED") == 0)
			{
				material_check = 1;
			}
			else if(ds_sts.sMATERIAL_STS.CompareNoCase("PROCESSED") == 0)
			{
				if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
				{
					material_check = 1;
				}
			}

			if(material_check > 0)
			{
				CStringArray l_pm;
				CStringArray l_rcp;

				if(xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type,l_pm,l_rcp) > 0)
				{
					int flag__lp_normal = 1;
					
					if(LPx__Get_Process_Type__Normal(arm_type,flag__lp_normal) < 0)
					{
						return -1;
					}

					// ...
					int limit = l_pm.GetSize();
					int i;

					for(i=0; i<limit; i++)
					{
						int pm_i = SCH__CHECK_PM_INDEX(l_pm[i]);
				
						if(pm_i < 0)				continue;
						if(pm_i >= iPMx_SIZE)		continue;

						if(flag__lp_normal > 0)
						{
							if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__NORMAL) > 0)
							{
								if(PMx__Is_Available(pm_i) < 0)
								{
									continue;
								}
							}
						}
						else
						{
							if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__TEST) > 0)
							{
								if(PMx__Is_Available(pm_i) < 0)
								{
									continue;
								}
							}
						}

						NEXT__LOOP;
					}
				}

				// ...
				CString sch_module;
				sch_module.Format("%s-%s",para_module,para_slot);

				l_pm.RemoveAll();
				l_rcp.RemoveAll();
				xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_module,l_pm,l_rcp);

				// ...
				int flag__lp_normal = 1;
				
				if(LPx__Get_Process_Type__Normal(sch_module,flag__lp_normal) < 0)
				{
					return -1;
				}

				// ...
				int limit = l_pm.GetSize();
				int i;

				for(i=0;i<limit;i++)
				{
					int pm_i = SCH__CHECK_PM_INDEX(l_pm[i]);
					
					if(pm_i < 0)				continue;
					if(pm_i >= iPMx_SIZE)		continue;

					if(Fnc__PMx_Empty_Ready_Check(flag__lp_normal,pm_i,1) < 0)
					{
						continue;
					}

					// ...
					{
						CString pm_name = l_pm[i];
						CString pm_slot = "1";
						CString pm_rcp  = l_rcp[i];

						Seq__LBi_PMx(p_variable,
									 p_alarm,
									 empty_arm,
									 para_module,para_slot,
									 pm_i,pm_name,pm_slot,pm_rcp);
					}

					NEXT__LOOP;
				}
			}
		}
	}

	NEXT__LOOP;
}
int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__LBi_To_Ready_PMx__ALL_MODE(CII_OBJECT__VARIABLE *p_variable,
									  CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	if(VAC_RB__Check_All_Empty() > 0)
	{
		NEXT__LOOP;
	}

	// ...
	{
		CString arm_type;
		
		// Arm : A ...
		if(VAC_RB__Check_Occupied__A_Arm() > 0)
		{
			arm_type = "A";
			
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				if(Fnc__PMC_Empty_Ready_Check(arm_type) > 0)
				{
					NEXT__LOOP;
				}
			}
		}
		// Arm : B ...
		if(VAC_RB__Check_Occupied__B_Arm() > 0)
		{
			arm_type = "B";
			
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				if(Fnc__PMC_Empty_Ready_Check(arm_type) > 0)
				{
					NEXT__LOOP;
				}
			}
		}
	}

	// ...
	int ll_a = _LLx_INDEX__LBA;
	int ll_b = _LLx_INDEX__LBB;

	int lba_flag = -1;
	int lbb_flag = -1;
	int lb_order =  1;

	CStringArray l_lba_pmc_name;
	CStringArray l_lba_pmc_rcp;
	CStringArray l_lbb_pmc_name;
	CStringArray l_lbb_pmc_rcp;

	// ...
	{
		IDS__SCH_MATERIAL_STATUS ds_sts;
		CString sch_name;	
		int lb_slotid;
		
		int lba_portid = -1;
		int lbb_portid = -1;
		CStringArray l_lba_pmc;
		CStringArray l_lbb_pmc;
		CStringArray l_lba_rcp;
		CStringArray l_lbb_rcp;

		if((xEXT_CH__LLx__IN_OUT_FLAG[ll_a]->Check__DATA("OUT") > 0)
		&& (LLx__Is_Available(ll_a) > 0)
		&& (LLx__Is_VAC(ll_a) > 0))
		{
			if(LLx__Get_Occupied__InSlot(ll_a, lb_slotid) > 0)
			{
				sch_name.Format("%s-%1d", MODULE__LBA,lb_slotid);
				
				if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(sch_name,ds_sts) > 0)
				{
					lba_portid = ds_sts.iPORT_ID;	
					
					xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_name,l_lba_pmc,l_lba_rcp);
				}
			}
		}
		
		if((xEXT_CH__LLx__IN_OUT_FLAG[ll_b]->Check__DATA("OUT") > 0)
		&& (LLx__Is_Available(ll_b) > 0)
		&& (LLx__Is_VAC(ll_b) > 0))
		{
			if(LLx__Get_Occupied__InSlot(ll_b, lb_slotid) > 0)
			{
				sch_name.Format("%s-%1d", MODULE__LBB,lb_slotid);
				
				if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(sch_name,ds_sts) > 0)
				{
					lbb_portid = ds_sts.iPORT_ID;	
					
					xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_name,l_lbb_pmc,l_lbb_rcp);
				}
			}
		}
		
		// ...
		int dual_check = -1;

		// ...
		{
			l_lba_pmc_name.RemoveAll();
			l_lba_pmc_rcp.RemoveAll();
			l_lbb_pmc_name.RemoveAll();
			l_lbb_pmc_rcp.RemoveAll();
			
			l_lba_pmc_name.Copy(l_lba_pmc);
			l_lba_pmc_rcp.Copy(l_lba_rcp);
			l_lbb_pmc_name.Copy(l_lbb_pmc);
			l_lbb_pmc_rcp.Copy(l_lbb_rcp);
		}

		if((lba_portid > 0) && (lbb_portid > 0))
		{
			// ...
			{
				int lba__lp_i = lba_portid - 1;
				int lbb__lp_i = lbb_portid - 1;
				
				int lba__proc_flag = LPx__Check_Process_Type__Normal(lba__lp_i);
				int lbb__proc_flag = LPx__Check_Process_Type__Normal(lbb__lp_i);
				
				if(lba__proc_flag != lbb__proc_flag)
				{
					dual_check = 1;
				}
			}

			if(dual_check < 0)
			{
				if(Macro__Check_Equal__Any_String(l_lba_pmc,l_lbb_pmc) < 0)
				{
					if(Macro__Check_Equal__All_String(l_lba_pmc,l_lbb_pmc) < 0)
					{
						dual_check = 1;

						// ...
						CUIntArray l_job_lp;
						SCH__Get_Job_LP_List(l_job_lp);

						if(l_job_lp.GetSize() > 1)
						{
							int cur_lp = l_job_lp[0];

								 if(lba_portid == cur_lp)		lb_order = 1;
							else if(lbb_portid == cur_lp)		lb_order = 2;
						}
					}
				}
			}

			if(dual_check < 0)
			{
				if(xEXT_CH__SCH_CONCURRENT_ALWAYS_APPLY->Check__DATA(STR__DISABLE) < 0)
				{
					if(lba_portid != lbb_portid)
					{
						lb_order = -1;

						// ...
						{
							CUIntArray l_job_lp;
							SCH__Get_Job_LP_List(l_job_lp);
						
							if(l_job_lp.GetSize() > 1)
							{
								int cur_lp = l_job_lp[0];
							
									 if(lba_portid == cur_lp)			lb_order = 1;
								else if(lbb_portid == cur_lp)			lb_order = 2;
							}
						}
						
						if(lb_order > 0)
						{
							if(xEXT_CH__SCH_CONCURRENT_ALWAYS_APPLY->Check__DATA(STR__PPID_CHECK) > 0)
							{
								l_lba_pmc_name.RemoveAll();
								l_lba_pmc_rcp.RemoveAll();
								l_lbb_pmc_name.RemoveAll();
								l_lbb_pmc_rcp.RemoveAll();
								
								if(lb_order == 1)
								{
									l_lba_pmc_name.Copy(l_lba_pmc);
									l_lba_pmc_rcp.Copy(l_lba_rcp);
									
									Macro__Delete_Trg_With_Src(l_lba_pmc,
																	  l_lba_rcp,
																	  l_lbb_pmc,
																	  l_lbb_rcp,
																	  l_lbb_pmc_name,
																	  l_lbb_pmc_rcp);
								}
								else if(lb_order == 2)
								{
									l_lbb_pmc_name.Copy(l_lbb_pmc);
									l_lbb_pmc_rcp.Copy(l_lbb_rcp);
									
									Macro__Delete_Trg_With_Src(l_lbb_pmc,
																	  l_lbb_rcp,
																	  l_lba_pmc,
																	  l_lba_rcp,
																	  l_lba_pmc_name,
																	  l_lba_pmc_rcp);
								}
							}
							
							dual_check = 1;
						}

						/*
						// ...
						{
							CString msg;
							CString bff;
							
							int limit = l_job_lp.GetSize();
							int i;
							
							msg = "Job LPx ...\n";
							
							for(i=0;i<limit;i++)
							{
								bff.Format("   %1d) LP%1d \n", i+1,l_job_lp[i]);
								msg += bff;
							}
							
							bff.Format("lba_portid <- [%1d] \n", lba_portid);
							msg += bff;
							
							bff.Format("lbb_portid <- [%1d] \n", lbb_portid);
							msg += bff;
							
							bff.Format("lb_order   <- [%1d] \n", lb_order);
							msg += bff;
							
							bff.Format("dual_check <- [%1d] \n", dual_check);
							msg += bff;
							
							MessageBox(NULL,msg,"CHECK - AUTO_CTRL__LBi_To_PMx",MB_OK|MB_TOPMOST);
						}
						*/
					}	
				}
			}
		}
		
		if(dual_check > 0)
		{
			lba_flag = 1;
			lbb_flag = 1;
		}
		else
		{
			lb_order = 1;

			// ...
			CString check_lbx_type = STR__ALL;

			if(Get__First_Wafer_In_LBi(p_variable,p_alarm,check_lbx_type,lba_flag,lbb_flag) < 0)
			{
				NEXT__LOOP;
			}
		}
	}

	// ...
	CString para_module;
	CString para_slot;
	int slot_id;

	CString var_data;
	int kk;
	int cmp1_kk;
	int cmp2_kk;

	for(kk=0;kk<2;kk++)
	{
		// ...
		{
			cmp1_kk = -1;
			cmp2_kk = -1;

			if(lb_order != 2)
			{
				cmp1_kk == 1;
				cmp2_kk == 0;
			}
			else 
			{
				cmp1_kk == 0;
				cmp2_kk == 1;
			}
		}

		if(kk == cmp1_kk)
		{
			if(lba_flag < 0)
			{
				continue;	
			}

			if((xEXT_CH__LLx__IN_OUT_FLAG[ll_a]->Check__DATA("OUT") > 0)
			&& (LLx__Is_Available(ll_a) > 0)
			&& (LLx__Check_Occupied__InSlot(ll_a) > 0))
			{
				if(SCH__LLx_CHECK_PRESSURE(ll_a, p_variable,p_alarm,1) < 0)
				{
					continue;
				}

				if(LLx__Get_Occupied__InSlot(ll_a, slot_id) < 0)
				{
					continue;
				}

				para_module = MODULE__LBA;
				para_slot.Format("%1d",slot_id);
			}
		}
		else if(kk == cmp2_kk)
		{
			if(lbb_flag < 0)
			{
				continue;
			}

			if((xEXT_CH__LLx__IN_OUT_FLAG[ll_b]->Check__DATA("OUT") > 0)
			&& (LLx__Is_Available(ll_b) > 0)
			&& (LLx__Check_Occupied__InSlot(ll_b) > 0))
			{
				if(SCH__LLx_CHECK_PRESSURE(ll_b, p_variable,p_alarm,1) < 0)
				{
					continue;
				}

				if(LLx__Get_Occupied__InSlot(ll_b, slot_id) < 0)
				{
					continue;
				}

				para_module = MODULE__LBB;
				para_slot.Format("%1d",slot_id);
			}
		}
		else
		{
			continue;
		}

		// ...
		CString empty_arm;

		if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
		{
			CString cfg__arm_from_lbx;
			CString cfg__arm_from_pmc;

			xCH_CFG__PICK_ARM_TYPE_FROM_LBX->Get__DATA(cfg__arm_from_lbx);
			xCH_CFG__PICK_ARM_TYPE_FROM_PMC->Get__DATA(cfg__arm_from_pmc);

			// Alarm Report ...
			{

			}				

			NEXT__LOOP;
		}

		// ...
		{
			CString sch_module;
			sch_module.Format("%s-%s",para_module,para_slot);

			// ...
			CStringArray l_pm;
			CStringArray l_rcp;

			xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_module,l_pm,l_rcp);

			// ...
			int flag__lp_normal = 1;
			
			if(LPx__Get_Process_Type__Normal(sch_module,flag__lp_normal) < 0)
			{
				return -1;
			}

			// ...
			int limit = l_pm.GetSize();
			int i;

			for(i=0;i<limit;i++)
			{
				int pm_i = SCH__CHECK_PM_INDEX(l_pm[i]);
					
				if(pm_i < 0)				continue;
				if(pm_i >= iPMx_SIZE)		continue;

				if(Fnc__PMx_Empty_Ready_Check(flag__lp_normal,pm_i,1) < 0)
				{
					continue;
				}

				// ...
				{
					CString pm_name = l_pm[i];
					CString pm_slot = "1";
					CString pm_rcp  = l_rcp[i];

					Seq__LBi_PMx(p_variable,
								 p_alarm,
								 empty_arm,
								 para_module,para_slot,
								 pm_i,pm_name,pm_slot,pm_rcp);
				}

				NEXT__LOOP;
			}
		}
	}

	NEXT__LOOP;
}
int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__LBi_PMx__1_SLOT_ALL_MODE(CII_OBJECT__VARIABLE *p_variable,
									CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CString para_module;
	CString para_slot;
	int slot_id;

	CString var_data;

	int ll_limit = iLLx_LIMIT;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if((xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
		&& (LLx__Is_Available(ll_i) > 0)
		&& (LLx__Check_Occupied__InSlot_With_1_Slot_All_Mode(ll_i) > 0))
		{
			if(SCH__LLx_CHECK_PRESSURE(ll_i, p_variable,p_alarm,1) < 0)
			{
				continue;
			}

			if(LLx__Get_Occupied__InSlot_With_1_Slot_All_Mode(ll_i, slot_id) < 0)
			{
				continue;
			}

			para_module = Get__LLx_NAME(ll_i);
			para_slot.Format("%1d",slot_id);
		}

		// ...
		CString empty_arm;

		if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
		{
			NEXT__LOOP;
		}

		// ...
		CString arm_type;

		if(VAC_RB__Get_Occupied__Arm_Type(arm_type) > 0)
		{
			IDS__SCH_MATERIAL_STATUS ds_sts;
			xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_sts);

			int material_check = -1;

			if(ds_sts.sMATERIAL_STS.CompareNoCase("ALIGNED") == 0)
			{
				material_check = 1;
			}
			else if(ds_sts.sMATERIAL_STS.CompareNoCase("PROCESSED") == 0)
			{
				if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
				{
					material_check = 1;
				}
			}

			if(material_check > 0)
			{
				CStringArray l_pm;
				CStringArray l_rcp;

				if(xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type,l_pm,l_rcp) > 0)
				{
					int limit = l_pm.GetSize();
					int i;

					for(i=0;i<limit;i++)
					{
						int pm_i = SCH__CHECK_PM_INDEX(l_pm[i]);
					
						if(pm_i < 0)				continue;
						if(pm_i >= iPMx_SIZE)		continue;

						if(PMx__Is_Available(pm_i) < 0)	
						{
							continue;
						}

						NEXT__LOOP;
					}
				}
			}
		}

		// ...
		{
			CString sch_module;
			sch_module.Format("%s-%s",para_module,para_slot);

			CStringArray l_pm;
			CStringArray l_rcp;
			xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_module,l_pm,l_rcp);

			int limit = l_pm.GetSize();
			int i;

			for(i=0;i<limit;i++)
			{
				int pm_i = SCH__CHECK_PM_INDEX(l_pm[i]);
				
				if(pm_i < 0)				continue;
				if(pm_i >= iPMx_SIZE)		continue;

				if(PMx__Is_Available(pm_i) < 0)				continue;
				if(PMx__Check_Empty__SlotStatus(pm_i) < 0)	continue;

				CString pm_name = l_pm[i];
				CString pm_slot = "1";
				CString pm_rcp  = l_rcp[i];

				Seq__LBi_PMx(p_variable,
							 p_alarm,
							 empty_arm,
							 para_module,para_slot,
							 pm_i,
							 pm_name,
							 pm_slot,
							 pm_rcp);

				NEXT__LOOP;
			}
		}
	}

	NEXT__LOOP;
}


int  CObj_Fnc__DUAL_ARM_STD::
Seq__LBi_PMx(CII_OBJECT__VARIABLE *p_variable,
			 CII_OBJECT__ALARM *p_alarm,
			 const CString& arm_type,
			 const CString& lbx_name,
			 const CString& lbx_slot,
			 const int pm_i,
			 const CString& pm_name,
			 const CString& pm_slot,
			 const CString& pm_rcp)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "Seq__LBi_PMx()";

	// ...
	{
		int act_flag  = -1;
		int move_flag = -1;

		CString sch_module;
		sch_module.Format("%s-%s",lbx_name,lbx_slot);

		act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,arm_type,lbx_name,lbx_slot,sch_module);

		if(act_flag < 0)
		{
			move_flag = SCH__Check_Material_Pick(arm_type);
		}
		else
		{
			move_flag = 1;
		}

		if(move_flag > 0)
		{
			xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,arm_type);	
		}

		if(act_flag < 0)
		{
			NEXT__LOOP;
		}
	}

	// ...
	{
		int active_pump = 1;

		// ...
		{
			int macterial_check = -1;
			CString check_arm;

			if(VAC_RB__Check_Occupied__A_Arm() > 0)
			{
				check_arm = "A";

				if(check_arm.CompareNoCase(arm_type) != 0)
				{
					if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(check_arm) < 0)
					{
						macterial_check = 1;			
					}
				}
			}
			if(VAC_RB__Check_Occupied__B_Arm() > 0)
			{
				check_arm = "B";

				if(check_arm.CompareNoCase(arm_type) != 0)
				{
					if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(check_arm) > 0)
					{
						macterial_check = 1;
					}
				}
			}

			if(macterial_check > 0)
			{
				int active__sch_mode = -1;
				int active__sch_ll   = -1;

				// ...
				CStringArray l_ll_id;
				CStringArray l_ll_mode;
				CStringArray l_ll_slot;

				xSCH_MATERIAL_CTRL->Get__LLx_OUT_OF_EDIT_TYPE(arm_type, l_ll_id,l_ll_mode,l_ll_slot);

				if(l_ll_id.GetSize() == 1)
				{
					int index_ll = 0;
					int ll_id = atoi(l_ll_id[index_ll]);

					CString str_mode = l_ll_mode[index_ll];
					CString str_slot = l_ll_slot[index_ll];

					if(str_mode.CompareNoCase("ALL") == 0)
					{
						int ll_i = ll_id - 1;

						if((ll_i >= 0) && (ll_i < iLLx_LIMIT))						
						{
							if(LLx__Check_Empty__InSlot(ll_i) > 0)
							{
								active_pump = -1;
							}
						}
					}
				}
			}
		}

		if(active_pump > 0)
		{
			int ll_i = Get__LLx_INDEX(lbx_name);
			if(ll_i >= 0)
			{
				if(LLx__Check_Empty__InSlot(ll_i) > 0)
				{
					if(SCH_RUN__LLx_VENT(ll_i, log_id, "1") > 0)
					{
						xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
					}
				}
			}
		}
	}

	// jglee : 2020.10.20
	if(SCH__PMx_CHECK_PRESSURE(pm_i,p_variable,p_alarm) < 0)
	{
		NEXT__LOOP;		
	}

	if((PMx__Is_Available(pm_i) > 0)
	&& (PMx__Check_Empty__SlotStatus(pm_i) > 0))
	{
		int act_flag  = -1;
		int move_flag = -1;

		CString sch_name;
		sch_name.Format("%s-%s",pm_name,pm_slot);
		
		xSCH_MATERIAL_CTRL->Set__CURRENT_RECIPE(arm_type,pm_rcp);

		act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, false,arm_type,pm_name,pm_slot,sch_name);

		if(act_flag < 0)
		{
			move_flag = SCH__Check_Material_Place(arm_type);
		}
		else
		{
			move_flag = 1;
		}

		if(move_flag > 0)
		{
			xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_name);

			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_name,"PROCESSING");
			xSCH_MATERIAL_CTRL->Goto__NEXT_PROCESS(sch_name);
		}

		if(act_flag < 0)
		{
			NEXT__LOOP;
		}
	}

	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__RB_PMx(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	CStringArray l_arm;	
	Get__Arm_List_To_Process(l_arm);

	if(l_arm.GetSize() > 1)
	{
		_AUTO_CTRL__RB_PMx_WITH_DUAL_TYPE(p_variable, p_alarm);
	}

	// ...
	{
		int i_limit = l_arm.GetSize();
		for(int i=0; i<i_limit; i++)
		{
			CString arm_type = l_arm[i];

			_AUTO_CTRL__RB_PMx(p_variable,p_alarm,arm_type);
		}
	}

	return 1;
}
int  CObj_Fnc__DUAL_ARM_STD::
_AUTO_CTRL__RB_PMx_WITH_DUAL_TYPE(CII_OBJECT__VARIABLE *p_variable,
								  CII_OBJECT__ALARM* p_alarm)
{

	if(xCH_CFG__LLx_CTRL_ONLY_INPUT_OUTPUT_MODE->Check__DATA(STR__DUAL) < 0)		return -1;
	if(xCH_CFG__DUAL_ARM_CURRENT_BEHAVIOR->Check__DATA(STR__ENABLE) < 0)			return -2;

	CString log_id = "_AUTO_CTRL__RB_PMx_WITH_DUAL_TYPE()";

	// ...
	CString arm_a = "A";
	CStringArray l_pmc_a;
	CStringArray l_rcp_a;
	Fnc__Get_PMx_List(arm_a, l_pmc_a,l_rcp_a);

	CString arm_b = "B";
	CStringArray l_pmc_b;
	CStringArray l_rcp_b;
	Fnc__Get_PMx_List(arm_b, l_pmc_b,l_rcp_b);

	// Check : PM1 & PM2 
	if((_Check__PM_Name("PM1", l_pmc_a) > 0)
	&& (_Check__PM_Name("PM2", l_pmc_b) > 0))
	{
		CString name_pm1 = "PM1";
		CString name_pm2 = "PM2";

		CString pm1_rcp = Fnc__Get_PM_Rcp(name_pm1, l_pmc_a,l_rcp_a);
		CString pm2_rcp = Fnc__Get_PM_Rcp(name_pm2, l_pmc_b,l_rcp_b);

		xSCH_MATERIAL_CTRL->Set__CURRENT_RECIPE("A", pm1_rcp);
		xSCH_MATERIAL_CTRL->Set__CURRENT_RECIPE("B", pm2_rcp);

		//
		CString arm_type = "AB";
		CString sch_pm1;
		CString sch_pm2;

		sch_pm1.Format("%s-1", name_pm1);
		sch_pm2.Format("%s-1", name_pm2);

		int act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, false, arm_type, "PM12", "1", sch_pm1,sch_pm2);
		int move_flag = -1;

		if(act_flag < 0)		move_flag = SCH__Check_Material_Place(arm_a);
		else					move_flag = 1;

		if(move_flag > 0) 
		{
			xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_a, sch_pm1);
			xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_b, sch_pm2);

			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_pm1,"PROCESSING");
			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_pm2,"PROCESSING");

			xSCH_MATERIAL_CTRL->Goto__NEXT_PROCESS(sch_pm1);
			xSCH_MATERIAL_CTRL->Goto__NEXT_PROCESS(sch_pm2);
		}
		if(act_flag < 0)		NEXT__LOOP;

		NEXT__LOOP;
	}

	// Check : PM3 & PM4
	if((_Check__PM_Name("PM3", l_pmc_a) > 0)
	&& (_Check__PM_Name("PM4", l_pmc_b) > 0))
	{
		CString name_pm3 = "PM3";
		CString name_pm4 = "PM4";

		CString pm3_rcp = Fnc__Get_PM_Rcp(name_pm3, l_pmc_a,l_rcp_a);
		CString pm4_rcp = Fnc__Get_PM_Rcp(name_pm4, l_pmc_b,l_rcp_b);

		xSCH_MATERIAL_CTRL->Set__CURRENT_RECIPE("A", pm3_rcp);
		xSCH_MATERIAL_CTRL->Set__CURRENT_RECIPE("B", pm4_rcp);

		//
		CString arm_type = "AB";
		CString sch_pm3;
		CString sch_pm4;

		sch_pm3.Format("%s-1", name_pm3);
		sch_pm4.Format("%s-1", name_pm4);

		int act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, false, arm_type, "PM34", "1", sch_pm3,sch_pm4);
		int move_flag = -1;

		if(act_flag < 0)		move_flag = SCH__Check_Material_Place(arm_a);
		else					move_flag = 1;

		if(move_flag > 0) 
		{
			xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_a, sch_pm3);
			xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_b, sch_pm4);

			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_pm3,"PROCESSING");
			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_pm4,"PROCESSING");

			xSCH_MATERIAL_CTRL->Goto__NEXT_PROCESS(sch_pm3);
			xSCH_MATERIAL_CTRL->Goto__NEXT_PROCESS(sch_pm4);
		}
		if(act_flag < 0)		NEXT__LOOP;

		NEXT__LOOP;
	}

	return -11;
}
int  CObj_Fnc__DUAL_ARM_STD::
_AUTO_CTRL__RB_PMx(CII_OBJECT__VARIABLE *p_variable,
				   CII_OBJECT__ALARM* p_alarm,
				   const CString& arm_type)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CString log_id = "_AUTO_CTRL__RB_PMx()";

	// ...
	CStringArray l_pmc;
	CStringArray l_pmc_rcp;

	CString pm_name;
	CString pm_slot = "1";

	// ...
	{
		SCH__Change_Current_Route_Step(p_variable,p_alarm, arm_type);
	}

	if(xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type,l_pmc,l_pmc_rcp) < 0)
	{
		return 1;
	}

	// ...
	int flag__lp_normal = 1;

	if(LPx__Get_Process_Type__Normal(arm_type,flag__lp_normal) < 0)
	{
		return -1;
	}

	// ...
	{
		int pm_count = 0;

		int pmc_check = -1;
		int pm_i;

		int limit = l_pmc.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			CString pm_name = l_pmc[i];

			if(xCH_CFG__LLx_CTRL_ONLY_INPUT_OUTPUT_MODE->Check__DATA(STR__DUAL) > 0)
			{
				if(VAC_RB__Check__Arm_Type_With_PMx_Constraint(arm_type, pm_name) < 0)
				{
					continue;
				}
			}

			pm_i = SCH__CHECK_PM_INDEX(pm_name);
			if(pm_i < 0)
			{
				continue;
			}
			pm_count++;

			if(PMx__Check_CtcInUse_Or_Standby(pm_i) < 0)
			{
				continue;
			}

			/*
			if(PMx__Check_Empty__SlotStatus(pm_i) > 0)
			{
				if(xCH__PMx__NEXT_PROCESS[pm_i]->Check__DATA(STR__LEAK_CHECK) > 0)
				{
					continue;
				}
			}
			*/

			if(flag__lp_normal > 0)
			{
				if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__NORMAL) < 0)
				{
					continue;
				}
			}
			else
			{
				if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__TEST) < 0)
				{
					continue;
				}
			}

			if((xEXT_CH__CFG__PMx_USE[pm_i]->Check__DATA(STR__ENABLE) < 0)
			&& (PMx__Check_Empty__SlotStatus(pm_i) > 0))
			{
				continue;
			}

			pmc_check = 1;
			break;
		}

		if(pm_count < 1)
		{
			return 1;
		}

		if(pmc_check < 0)
		{
			int alarm_id = ALID__PMC__NOT_AVAILABLE;
			CString alarm_msg;
			CString r_act;

			// ...
			{
				if(flag__lp_normal > 0)
				{
					alarm_msg = "There is no PMC with \"NORMAL\" process type. \n";
				}
				else
				{
					alarm_msg = "There is no PMC with \"TEST\" process type. \n";				
				}
				
				alarm_msg += "At least, one PM's status must be CtcInUse or Standby among the following PMs;\n";

				// ...
				int limit = l_pmc.GetSize();
				int i;
			
				for(i=0;i<limit;i++)
				{
					alarm_msg += l_pmc[i];
					alarm_msg += ", ";
				}

				alarm_msg += "\n";
			}

			// ..
			{
				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alarm_msg);
			}
			return 1;
		}
	}

	// ...
	CStringArray l_module;
	CStringArray l_recipe;
	CStringArray l_pmx_incount;

	// ...
	{
		CString var_data;
		int pm_i;

		int limit = l_pmc.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			pm_i = SCH__CHECK_PM_INDEX(l_pmc[i]);
			if(pm_i < 0)
			{
				continue;
			}

			if(xEXT_CH__CFG__PMx_USE[pm_i]->Check__DATA(STR__ENABLE) > 0)
			{
				if(PMx__Is_Available(pm_i) < 0)
				{
					continue;
				}
			}
			else
			{
				if(PMx__Is_Idle(pm_i) < 0)
				{
					continue;
				}
				if(PMx__Check_Empty__SlotStatus(pm_i) > 0)
				{
					continue;
				}
			}
			
			if(SCH__PMx_CHECK_PRESSURE(pm_i,p_variable,p_alarm) < 0)
			{
				continue;
			}

			if(flag__lp_normal > 0)
			{
				if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__NORMAL) < 0)
				{
					continue;
				}
			}
			else
			{
				if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__TEST) < 0)
				{
					continue;
				}
			}

			if(xCH_CFG__SCH_EXCHANGE_PRIORITY->Check__DATA(STR__WAFER) > 0)
			{
				if(PMx__Check_Occupied__SlotStatus(pm_i) > 0)
				{
					xCH__PMx__IN_COUNT[pm_i]->Get__DATA(var_data);
				}
				else
				{
					var_data = "1000000";
				}
			}
			else
			{
				if(PMx__Check_Occupied__SlotStatus(pm_i) > 0)
				{
					int cur_in_count;
					int cur_idle_sec;
					CString cur_data;

					xCH__PMx__IN_COUNT[pm_i]->Get__DATA(cur_data);
					cur_in_count = atoi(cur_data);

					/*
					xCH__PMx__IDLE_TIME[pm_i]->Get__DATA(cur_data);
					cur_idle_sec = atoi(cur_data);
					*/
					cur_idle_sec = 0;

					var_data.Format("%1d", (1000000 + cur_in_count+cur_idle_sec));
				}
				else
				{
					if(xCH__PMx__FIRST_WAFER_FLAG[pm_i]->Check__DATA(STR__YES) > 0)
					{
						int cur_pmc_sec = - (10 - pm_i);
	
						var_data.Format("%1d", cur_pmc_sec);	
					}
					else
					{
						xCH__PMx__IDLE_TIME[pm_i]->Get__DATA(var_data);
						int cur_idle_sec = atoi(var_data);
						int cur_pmc_sec = 1000000 - cur_idle_sec;

						if(cur_pmc_sec < 1)
						{
							cur_pmc_sec = 1;
						}

						var_data.Format("%1d", cur_pmc_sec);	
					}
				}				
			}

			l_pmx_incount.Add(var_data);
			l_module.Add(l_pmc[i]);
			l_recipe.Add(l_pmc_rcp[i]);
		}
	}

	// Order Check ...
	{
		int k_limit = l_pmx_incount.GetSize();
		int k;

		for(k=0; k<k_limit; k++)
		{
			int count_cur = atoi(l_pmx_incount[k]);				

			CString incount_cur = l_pmx_incount[k];
			CString moudle_cur  = l_module[k];
			CString recipe_cur  = l_recipe[k];

			for(int t = k+1; t<k_limit; t++)
			{
				int count_chk = atoi(l_pmx_incount[t]);

				if(count_chk >= count_cur)
				{
					continue;
				}

				CString incount_chk = l_pmx_incount[t];
				CString moudle_chk  = l_module[t];
				CString recipe_chk  = l_recipe[t];

				count_cur = count_chk;

				l_pmx_incount[k] = incount_chk; 
				l_module[k] = moudle_chk; 
				l_recipe[k] = recipe_chk;

				l_pmx_incount[t] = incount_cur; 
				l_module[t] = moudle_cur; 
				l_recipe[t] = recipe_cur;
			}
		}
	}

	// ...
	IDS__SCH_MATERIAL_STATUS ds_sts;

	CString sch_name;
	CString pm_rcp;
	int pm_i;

	int limit = l_module.GetSize();
	int i;

	for(i=0; i<limit; i++)
	{
		pm_i = SCH__CHECK_PM_INDEX(l_module[i]);
		if(pm_i < 0)
		{
			continue;
		}

		// ...
		{
			pm_name.Format("PM%1d",pm_i+1);
			sch_name.Format("%s-%s",pm_name,pm_slot);
		
			pm_rcp = l_recipe[i];
		}
	
		if(xEXT_CH__CFG__PMx_USE[pm_i]->Check__DATA(STR__ENABLE) > 0)
		{
			if(PMx__Is_Available(pm_i) < 0)	
			{
				continue;
			}
		}
		else
		{
			if(PMx__Is_Idle(pm_i) < 0)
			{
				continue;
			}
		}

		if(flag__lp_normal > 0)
		{
			if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__NORMAL) < 0)
			{
				continue;
			}
		}
		else
		{
			if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__TEST) < 0)
			{
				continue;
			}
		}

		if(PMx__Check_Empty__SlotStatus(pm_i) > 0)
		{
			int act_flag  = -1;
			int move_flag = -1;

			// ...
			{
				xSCH_MATERIAL_CTRL->Set__CURRENT_RECIPE(arm_type,pm_rcp);

				act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, false,arm_type,pm_name,pm_slot,sch_name);

				if(act_flag < 0)
				{
					move_flag = SCH__Check_Material_Place(arm_type);
				}
				else
				{
					move_flag = 1;
				}
			}

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_name);
			
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_name,"PROCESSING");
				xSCH_MATERIAL_CTRL->Goto__NEXT_PROCESS(sch_name);
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
			return 1;
		}
	}

	// ...
	{
		CString arm_type;
		
		// Arm : A ...
		if(VAC_RB__Check_Occupied__A_Arm() > 0)
		{
			arm_type = "A";
			
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				if(xCH_CFG__SCH_EXCHANGE_PRIORITY->Check__DATA(STR__PMC) > 0)
				{
					if(Fnc__PMC_Empty_Ready_Check(arm_type) > 0)
					{
						return 1;
					}
				}
			}
		}
		// Arm : B ...
		if(VAC_RB__Check_Occupied__B_Arm() > 0)
		{
			arm_type = "B";
			
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				if(xCH_CFG__SCH_EXCHANGE_PRIORITY->Check__DATA(STR__PMC) > 0)
				{
					if(Fnc__PMC_Empty_Ready_Check(arm_type) > 0)
					{
						return 1;
					}
				}
			}
		}
	}

	// ...
	limit = l_module.GetSize();

	for(i=0; i<limit; i++)
	{
		pm_i = SCH__CHECK_PM_INDEX(l_module[i]);
		if(pm_i < 0)
		{
			continue;
		}

		// ...
		{
			pm_name.Format("PM%1d",pm_i+1);
			sch_name.Format("%s-%s",pm_name,pm_slot);
		
			pm_rcp = l_recipe[i];
		}
		
		if(xEXT_CH__CFG__PMx_USE[pm_i]->Check__DATA(STR__ENABLE) > 0)
		{
			if(PMx__Is_Available(pm_i) < 0)	
			{
				continue;
			}
		}
		else
		{
			if(PMx__Is_Idle(pm_i) < 0)
			{
				continue;
			}
		}
		
		if(flag__lp_normal > 0)
		{
			if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__NORMAL) < 0)
			{
				continue;
			}
		}
		else
		{
			if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__TEST) < 0)
			{
				continue;
			}
		}

		if(PMx__Check_Empty__SlotStatus(pm_i) > 0)
		{
			return 1;
		}
		else
		{
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(sch_name,ds_sts) < 0)
			{
				continue;
			}
		}
	
		if(VAC_RB__Check_Empty__Arm_Type() < 0)
		{
			continue;
		}
		
		if((PMx__Check_Next_Process(pm_i,p_alarm) < 0)
		&& (xSCH_MATERIAL_CTRL->Check__POST_CLN_In_PMC(sch_name,pm_i+1) < 0)
		&& (xEXT_CH__CFG__PMx_USE[pm_i]->Check__DATA(STR__ENABLE) > 0))
		{
			CString empty_arm;

			if(VAC_RB__Get_Empty__Arm_Type_From_All(empty_arm) < 0)
			{
				return 1;
			}
			
			if(xCH_CFG__PMx_SWAP_FLAG->Check__DATA(STR__ENABLE) > 0)
			{
				xSCH_MATERIAL_CTRL->Set__CURRENT_RECIPE(arm_type,pm_rcp);

				if(SCH__SWAP_PMx(p_variable,p_alarm,empty_arm,arm_type,pm_name,pm_slot,sch_name) < 0)
				{
					xEXT_CH__JOB_CTRL->Set__DATA("Abort");

					// ...
					int alarm_id = ALID__SWAP_ERROR;
					CString alarm_msg;
					CString r_act;

					alarm_msg.Format("Swap Error occured when Vac-Robot is swaping with %s.\n",pm_name);

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alarm_msg);

					Sleep(990);
					xSCH_MATERIAL_CTRL->Clear__ALL_MATERIAL_INFO();

					NEXT__LOOP;
				}

				// ...
				{
					xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_name,empty_arm);
					
					xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(empty_arm,"PROCESSED");
				}

				// ...
				{
					xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_name);

					xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_name,"PROCESSING");
					xSCH_MATERIAL_CTRL->Goto__NEXT_PROCESS(sch_name);
				}
			}
			else
			{
				if(xCH_CFG__LLx_CTRL_ONLY_INPUT_OUTPUT_MODE->Check__DATA(STR__DUAL) > 0)
				{
					if(VAC_RB__Get_Empty__Arm_Type_With_PMx_Constraint(empty_arm, pm_name) < 0)
					{
						NEXT__LOOP;
					}
				}

				// PICK ...
				{
					int act_flag  = -1;
					int move_flag = -1;

					act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, true,empty_arm,pm_name,pm_slot,sch_name);

					if(act_flag < 0)
					{
						move_flag = SCH__Check_Material_Pick(empty_arm);
					}
					else
					{
						move_flag = 1;
					}

					if(move_flag > 0)
					{
						xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_name,empty_arm);

						xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(empty_arm,"PROCESSED");
					}

					if(act_flag < 0)
					{
						NEXT__LOOP;
					}
				}

				// PLACE ...
				{
					int act_flag  = -1;
					int move_flag = -1;

					xSCH_MATERIAL_CTRL->Set__CURRENT_RECIPE(arm_type,pm_rcp);

					act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, false,arm_type,pm_name,pm_slot,sch_name);

					if(act_flag < 0)
					{
						move_flag = SCH__Check_Material_Place(arm_type);
					}
					else
					{
						move_flag = 1;
					}

					if(move_flag > 0)
					{
						xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_name);
					
						xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(sch_name,"PROCESSING");
						xSCH_MATERIAL_CTRL->Goto__NEXT_PROCESS(sch_name);
					}

					if(act_flag < 0)
					{
						NEXT__LOOP;
					}
				}
			}
		}
		else
		{
			int act_flag  = -1;
			int move_flag = -1;

			CString empty_arm;

			if(xCH_CFG__LLx_CTRL_ONLY_INPUT_OUTPUT_MODE->Check__DATA(STR__DUAL) > 0)
			{
				if(VAC_RB__Get_Empty__Arm_Type_With_PMx_Constraint(empty_arm, pm_name) < 0)
				{
					NEXT__LOOP;
				}
			}
			else 
			{
				if(VAC_RB__Get_Empty__Arm_Type_From_All(empty_arm) < 0)
				{
					NEXT__LOOP;
				}
			}

			act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,empty_arm,pm_name,pm_slot,sch_name);

			// ...
			{
				CString log_msg;
				CString log_bff;

				log_msg  = "\n";
				log_msg += "# PM Order Check ... \n";

				int k_limmit = l_module.GetSize();
				int k;

				for(k=0; k<k_limmit; k++)
				{
					log_bff.Format(" ** [%s][%s] - [%s] \n", 
								   l_module[k],
								   l_pmx_incount[k],
								   l_recipe[k]);
					log_msg += log_bff;
				}

				xAPP_LOG_CTRL->WRITE__LOG(log_msg);
			}

			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Pick(empty_arm);
			}
			else
			{
				move_flag = 1;
			}

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_name,empty_arm);
			
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(empty_arm,"PROCESSED");
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}
	}

	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__RB_TO_LLx_PROC(CII_OBJECT__VARIABLE *p_variable,
				          CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CStringArray l_arm;	
	Get__Arm_List_To_Process(l_arm);

	int i_limit = l_arm.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString arm_type = l_arm[i];

		_AUTO_CTRL__RB_TO_LLx_PROC(p_variable,p_alarm, arm_type);
	}
}
int  CObj_Fnc__DUAL_ARM_STD::
_AUTO_CTRL__RB_TO_LLx_PROC(CII_OBJECT__VARIABLE *p_variable,
				           CII_OBJECT__ALARM* p_alarm,
				           const CString& arm_type)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CString log_id = "_AUTO_CTRL__RB_TO_LLx_PROC()";

	// ...
	CStringArray l_ll;
	CStringArray l_ll_rcp;

	CString ll_name;
	CString ll_slot = "1";

	// ...
	{
		SCH__Change_Current_Route_Step(p_variable,p_alarm, arm_type);
	}

	if(xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type,l_ll,l_ll_rcp) < 0)
	{
		return 1;
	}

	// ...
	int flag__lp_normal = 1;

	if(LPx__Get_Process_Type__Normal(arm_type,flag__lp_normal) < 0)
	{
		return -1;
	}

	// ...
	{
		int ll_check = -1;
		int ll_i;

		int limit = l_ll.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			ll_i = Get__LLx_INDEX(l_ll[i]);
			if(ll_i < 0)
			{
				continue;
			}

			if(LLx__Check_CtcInUse_Or_Standby(ll_i) < 0)
			{
				continue;
			}

			/*
			if(LLx__Check_Empty__SlotStatus(ll_i) > 0)
			{
				if(xCH__LLx__NEXT_PROCESS[ll_i]->Check__DATA(STR__LEAK_CHECK) > 0)
				{
					continue;
				}
			}
			*/

			/*
			if(flag__lp_normal > 0)
			{
				if(xEXT_CH__LLx_PROCESS_TYPE[ll_i]->Check__DATA(STR__NORMAL) < 0)
				{
					continue;
				}
			}
			else
			{
				if(xEXT_CH__LLx_PROCESS_TYPE[ll_i]->Check__DATA(STR__TEST) < 0)
				{
					continue;
				}
			}
			*/

			if((xEXT_CH__SCH_DB_LLx_USE_FLAG[ll_i]->Check__DATA(STR__ENABLE) < 0)
			&& (LLx__Check_All_Empty(ll_i) > 0))
			{
				continue;
			}

			ll_check = 1;
			break;
		}

		if(ll_check < 0)
		{
			/*
			int alarm_id = ALID__LLx__NOT_AVAILABLE;
			CString alarm_msg;
			CString r_act;

			// ...
			{
				if(flag__lp_normal > 0)
				{
					alarm_msg = "There is no LLx with \"NORMAL\" process type. \n";
				}
				else
				{
					alarm_msg = "There is no LLx with \"TEST\" process type. \n";				
				}
				
				alarm_msg += "At least, one LL's status must be CtcInUse or Standby among the following LLs;\n";

				// ...
				int limit = l_ll.GetSize();
				int i;
			
				for(i=0; i<limit; i++)
				{
					alarm_msg += l_ll[i];
					alarm_msg += ", ";
				}

				alarm_msg += "\n";
			}

			// ..
			{
				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alarm_msg);
			}
			*/
			return 1;
		}
	}

	// ...
	CStringArray l_module;
	CStringArray l_recipe;
	CStringArray l_ll_incount;

	// ...
	{
		CString var_data;
		int ll_i;

		int limit = l_ll.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			ll_i = Get__LLx_INDEX(l_ll[i]);
			if(ll_i < 0)
			{
				continue;
			}

			if(xEXT_CH__SCH_DB_LLx_USE_FLAG[ll_i]->Check__DATA(STR__ENABLE) > 0)
			{
				if(LLx__Is_Available(ll_i) < 0)
				{
					continue;
				}
			}
			else
			{
				if(LLx__Is_Idle(ll_i) < 0)
				{
					continue;
				}
				if(LLx__Check_All_Empty(ll_i) > 0)
				{
					continue;
				}
			}
			
			if(SCH__LLx_CHECK_PRESSURE(ll_i,p_variable,p_alarm) < 0)
			{
				continue;
			}

			/*
			if(flag__lp_normal > 0)
			{
				if(xEXT_CH__LLx_PROCESS_TYPE[ll_i]->Check__DATA(STR__NORMAL) < 0)
				{
					continue;
				}
			}
			else
			{
				if(xEXT_CH__LLx_PROCESS_TYPE[ll_i]->Check__DATA(STR__TEST) < 0)
				{
					continue;
				}
			}
			*/

			/*
			if(xCH_CFG__SCH_EXCHANGE_PRIORITY->Check__DATA(STR__WAFER) > 0)
			{
				if(LLx__Check_Occupied__SlotStatus(ll_i) > 0)
				{
					xCH__LLx__IN_COUNT[ll_i]->Get__DATA(var_data);
				}
				else
				{
					var_data = "1000000";
				}
			}
			else
			{
				if(LLx__Check_Occupied__SlotStatus(ll_i) > 0)
				{
					int cur_in_count;
					int cur_idle_sec;
					CString cur_data;

					xCH__LLx__IN_COUNT[ll_i]->Get__DATA(cur_data);
					cur_in_count = atoi(cur_data);

					cur_idle_sec = 0;
					var_data.Format("%1d", (1000000 + cur_in_count+cur_idle_sec));
				}
				else
				{
					if(xCH__LLx__FIRST_WAFER_FLAG[ll_i]->Check__DATA(STR__YES) > 0)
					{
						int cur_pmc_sec = - (10 - ll_i);
	
						var_data.Format("%1d", cur_pmc_sec);	
					}
					else
					{
						xCH__LLx__IDLE_TIME[ll_i]->Get__DATA(var_data);
						int cur_idle_sec = atoi(var_data);
						int cur_pmc_sec = 1000000 - cur_idle_sec;

						if(cur_pmc_sec < 1)
						{
							cur_pmc_sec = 1;
						}

						var_data.Format("%1d", cur_pmc_sec);	
					}
				}				
			}
			*/

			// ...
			CString ll_name = Get__LLx_NAME(ll_i);

			l_ll_incount.Add(var_data);
			l_module.Add(ll_name);
			l_recipe.Add(l_ll_rcp[i]);
		}
	}

	/*
	// Order Check ...
	{
		int k_limit = l_ll_incount.GetSize();
		int k;

		for(k=0; k<k_limit; k++)
		{
			int count_cur = atoi(l_ll_incount[k]);				

			CString incount_cur = l_ll_incount[k];
			CString moudle_cur  = l_module[k];
			CString recipe_cur  = l_recipe[k];

			for(int t = k+1; t<k_limit; t++)
			{
				int count_chk = atoi(l_ll_incount[t]);

				if(count_chk >= count_cur)
				{
					continue;
				}

				CString incount_chk = l_ll_incount[t];
				CString moudle_chk  = l_module[t];
				CString recipe_chk  = l_recipe[t];

				count_cur = count_chk;

				l_ll_incount[k] = incount_chk; 
				l_module[k] = moudle_chk; 
				l_recipe[k] = recipe_chk;

				l_ll_incount[t] = incount_cur; 
				l_module[t] = moudle_cur; 
				l_recipe[t] = recipe_cur;
			}
		}
	}
	*/

	// ...
	IDS__SCH_MATERIAL_STATUS ds_sts;

	CString sch_name;
	CString ll_rcp;
	int ll_i;

	int limit = l_module.GetSize();
	int i;

	for(i=0; i<limit; i++)
	{
		ll_name = l_module[i];

		ll_i = Get__LLx_INDEX(ll_name);
		if(ll_i < 0)
		{
			continue;
		}

		// ...
		{
			sch_name.Format("%s-%s", ll_name,ll_slot);	
			ll_rcp = l_recipe[i];
		}
	
		if(xEXT_CH__SCH_DB_LLx_USE_FLAG[ll_i]->Check__DATA(STR__ENABLE) > 0)
		{
			if(LLx__Is_Available(ll_i) < 0)	
			{
				continue;
			}
		}
		else
		{
			if(LLx__Is_Idle(ll_i) < 0)
			{
				continue;
			}
		}

		/*
		if(flag__lp_normal > 0)
		{
			if(xEXT_CH__LLx_PROCESS_TYPE[ll_i]->Check__DATA(STR__NORMAL) < 0)
			{
				continue;
			}
		}
		else
		{
			if(xEXT_CH__LLx_PROCESS_TYPE[ll_i]->Check__DATA(STR__TEST) < 0)
			{
				continue;
			}
		}
		*/

		if(LLx__Check_All_Empty(ll_i) > 0)
		{
			int act_flag  = -1;
			int move_flag = -1;

			// ...
			{
				xSCH_MATERIAL_CTRL->Set__CURRENT_RECIPE(arm_type,ll_rcp);

				act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, false,arm_type,ll_name,ll_slot,sch_name);

				if(act_flag < 0)
				{
					move_flag = SCH__Check_Material_Place(arm_type);
				}
				else
				{
					move_flag = 1;
				}
			}

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type, sch_name);
			
				SCH__LLx_PROC(p_variable,p_alarm, ll_name,sch_name, ll_rcp, _CMMD_LLx__PROC_MAIN);
			}

			/*
			// PROC_LOOPx ...
			if(move_flag > 0)
			{
				CString loop_id;
				int loop_count;

				xSCH_MATERIAL_CTRL->Get__PROC_LOOPx_OF_EDIT_TYPE(sch_name, loop_id,loop_count) ;

			}
			*/

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
			return 1;
		}
	}

	/*
	// ...
	{
		CString arm_type;
		
		// Arm : A ...
		if(VAC_RB__Check_Occupied__A_Arm() > 0)
		{
			arm_type = "A";
			
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				if(xCH_CFG__SCH_EXCHANGE_PRIORITY->Check__DATA(STR__PMC) > 0)
				{
					if(Fnc__LLx_Empty_Ready_Check(arm_type) > 0)
					{
						return 1;
					}
				}
			}
		}
		// Arm : B ...
		if(VAC_RB__Check_Occupied__B_Arm() > 0)
		{
			arm_type = "B";
			
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				if(xCH_CFG__SCH_EXCHANGE_PRIORITY->Check__DATA(STR__PMC) > 0)
				{
					if(Fnc__LLx_Empty_Ready_Check(arm_type) > 0)
					{
						return 1;
					}
				}
			}
		}
	}
	*/

	// ...
	limit = l_module.GetSize();

	for(i=0; i<limit; i++)
	{
		ll_name = l_module[i];

		ll_i = Get__LLx_INDEX(ll_name);
		if(ll_i < 0)
		{
			continue;
		}

		// ...
		{
			sch_name.Format("%s-%s", ll_name,ll_slot);
			ll_rcp = l_recipe[i];
		}
		
		if(xEXT_CH__SCH_DB_LLx_USE_FLAG[ll_i]->Check__DATA(STR__ENABLE) > 0)
		{
			if(LLx__Is_Available(ll_i) < 0)	
			{
				continue;
			}
		}
		else
		{
			if(LLx__Is_Idle(ll_i) < 0)
			{
				continue;
			}
		}
		
		/*
		if(flag__lp_normal > 0)
		{
			if(xEXT_CH__LLx_PROCESS_TYPE[ll_i]->Check__DATA(STR__NORMAL) < 0)
			{
				continue;
			}
		}
		else
		{
			if(xEXT_CH__LLx_PROCESS_TYPE[lli]->Check__DATA(STR__TEST) < 0)
			{
				continue;
			}
		}
		*/

		if(LLx__Check_All_Empty(ll_i) > 0)
		{
			return 1;
		}
		else
		{
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(sch_name, ds_sts) < 0)
			{
				continue;
			}
		}
	
		if(VAC_RB__Check_Empty__Arm_Type() < 0)
		{
			continue;
		}

		// ...
		{
			int act_flag  = -1;
			int move_flag = -1;

			CString empty_arm;
			if(VAC_RB__Get_Empty__Arm_Type_From_All(empty_arm) < 0)
			{
				NEXT__LOOP;
			}

			act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,empty_arm,ll_name,ll_slot,sch_name);

			/*
			// ...
			{
				CString log_msg;
				CString log_bff;

				log_msg  = "\n";
				log_msg += "# LLx Order Check ... \n";

				int k_limmit = l_module.GetSize();
				int k;

				for(k=0; k<k_limmit; k++)
				{
					log_bff.Format(" ** [%s][%s] - [%s] \n", 
								   l_module[k],
								   l_ll_incount[k],
								   l_recipe[k]);
					log_msg += log_bff;
				}

				xAPP_LOG_CTRL->WRITE__LOG(log_msg);
			}
			*/

			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Pick(empty_arm);
			}
			else
			{
				move_flag = 1;
			}

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_name,empty_arm);
			
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(empty_arm,"PROCESSED");
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}
	}

	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__LLx_PROC_TO_RB(CII_OBJECT__VARIABLE *p_variable,
				          CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	if(VAC_RB__Is_Available() < 0)
	{
		NEXT__LOOP;
	}

	if(VAC_RB__Check_Empty__Dual_Arm() < 0)
	{
		NEXT__LOOP;

	}

	_AUTO_CTRL__LLx_PROC_TO_RB(p_variable,p_alarm);
	return 1;
}
int  CObj_Fnc__DUAL_ARM_STD::
_AUTO_CTRL__LLx_PROC_TO_RB(CII_OBJECT__VARIABLE *p_variable,
				           CII_OBJECT__ALARM* p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CString log_id = "_AUTO_CTRL__LLx_PROC_TO_RB()";

	int ll_limit = iLLx_LIMIT;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) < 0)
			continue;

		if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") < 0)
			continue;

		if(LLx__Is_Available(ll_i) < 0)
			continue;

		if(LLx__Check_Occupied__OutSlot(ll_i) < 0)
			continue;

		// ...
		CString ll_name;
		CString ll_slot;
		
		ll_name = Get__LLx_NAME(ll_i);
		ll_slot.Format("%1d", LLx__Check_Occupied__OutSlot(ll_i));

		CString sch_name;
		sch_name.Format("%s-%s", ll_name,ll_slot);

		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_name) < 0)
			continue;

		// ...
		int act_flag  = -1;
		int move_flag = -1;

		CString empty_arm;
		if(VAC_RB__Get_Empty__Arm_Type_From_All(empty_arm) < 0)
		{
			NEXT__LOOP;
		}

		act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,empty_arm,ll_name,ll_slot,sch_name);

		if(act_flag < 0)
		{
			move_flag = SCH__Check_Material_Pick(empty_arm);
		}
		else
		{
			move_flag = 1;
		}

		if(move_flag > 0)
		{
			xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_name,empty_arm);

			xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(empty_arm,"PROCESSED");
		}

		NEXT__LOOP;
	}

	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD::
SCH__Change_Current_Route_Step(CII_OBJECT__VARIABLE* p_variable,
							   CII_OBJECT__ALARM* p_alarm,
							   const CString& arm_type)
{
	IDS__SCH_MATERIAL_STATUS ds_sts;
	CString sch_name;	
	
	int arm_portid = -1;
	CStringArray l_arm_pmc;
	CStringArray l_arm_rcp;
	
	// ...
	if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_sts) > 0)
	{
		arm_portid = ds_sts.iPORT_ID;	
		
		xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type,l_arm_pmc,l_arm_rcp);
	}
	
	if(arm_portid > 0)
	{
		CUIntArray l_job_lp;
		SCH__Get_Job_LP_List(l_job_lp);
								
		if(l_job_lp.GetSize() > 1)
		{
			int cur_lp = l_job_lp[0];
			
			if(arm_portid != cur_lp)
			{
				if(xEXT_CH__SCH_CONCURRENT_ALWAYS_APPLY->Check__DATA(STR__PPID_CHECK) > 0)
				{
					CStringArray l_change_pmc_name;
					CStringArray l_change_pmc_rcp;
					CStringArray l_lp_pmc;
					
					if(xSCH_MATERIAL_CTRL->Get__ALL_PRC_MODULE_In_LPx(cur_lp,l_lp_pmc) > 0)
					{
						Macro__Change_Order__Trg_With_Src(l_lp_pmc,
														  l_arm_pmc,
														  l_arm_rcp,
														  l_change_pmc_name,
														  l_change_pmc_rcp);
					}
					
					/*
					// ...
					{
						CString log_msg;
						CString log_bff;
						
						int limit = l_change_pmc_name.GetSize();
						int i;
						
						for(i=0;i<limit;i++)
						{
							log_bff.Format("%1d) [%s][%s] \n", i+1,l_change_pmc_name[i],l_change_pmc_rcp[i]);
							log_msg += log_bff;
						}
						
						MessageBox(NULL,log_msg,"CHECK - SCH__Change_Current_Route_Step()",MB_OK|MB_TOPMOST);
					}
					*/
					
					if(l_change_pmc_name.GetSize() > 0)
					{
						CStringArray l_change_pmc_stage;
						
						l_change_pmc_stage.SetSize(l_change_pmc_name.GetSize());
						
						xSCH_MATERIAL_CTRL->SCH_DB_INFO__Change_Current_Route_Step(arm_type,
																				   l_change_pmc_name,
																				   l_change_pmc_rcp,
																				   l_change_pmc_stage);
					}
				}
			}
		}
	}

	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD::
Fnc__PMC_Empty_Ready_Check(const CString& arm_type,
						   const int ex_pick_check)
{
	// ...
	CStringArray l_prc_module;
	CStringArray l_prc_recipe;
				
	xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type, l_prc_module,l_prc_recipe);
				
	// ...
	int flag__lp_normal = 1;
	
	if(LPx__Get_Process_Type__Normal(arm_type,flag__lp_normal) < 0)
	{
		return -1;
	}

	// ...
	{
		IDS__SCH_MATERIAL_STATUS ds_sts;

		xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_sts);
		int sch_lp_id = ds_sts.iPORT_ID;

		// ...
		CUIntArray l_job_lp;
		SCH__Get_Job_LP_List(l_job_lp);
								
		if(l_job_lp.GetSize() > 1)
		{
			int cur_lp = l_job_lp[0];

			if(sch_lp_id != cur_lp)
			{
				CStringArray l_lp_pmc;

				if(xSCH_MATERIAL_CTRL->Get__ALL_PRC_MODULE_In_LPx(cur_lp,l_lp_pmc) > 0)
				{
					CStringArray l_sch_pmc;
					CStringArray l_sch_rcp;

					l_sch_pmc.Copy(l_prc_module);
					l_sch_rcp.Copy(l_prc_recipe);

					Macro__Delete_Trg_With_Src(l_lp_pmc, l_sch_pmc,l_sch_rcp);

					if(l_sch_pmc.GetSize() > 0)
					{
						l_prc_module.RemoveAll();
						l_prc_recipe.RemoveAll();

						l_prc_module.Copy(l_sch_pmc);
						l_prc_recipe.Copy(l_sch_rcp);
					}
				}
			}
		}
	}

	// ...
	int limit = l_prc_module.GetSize();
	int i;
				
	/*
	if(xCH__SCH_DB_CHECK->Check__DATA(STR__YES) > 0)
	{
		xCH__SCH_DB_CHECK->Set__DATA("");

		// ...
		CString msg;
		CString bff;

		msg.Format("Arm Type : [%s] \n", arm_type);

		for(i=0;i<limit;i++)
		{
			bff.Format("%1d)  [%s] \n", i+1,l_prc_module[i]);
			msg += bff;
		}

		MessageBox(NULL,msg,"CHECK - Fnc__PMC_Empty_Ready_Check()",MB_OK|MB_TOPMOST);
	}
	*/

	for(i=0;i<limit;i++)
	{
		int pm_i = SCH__CHECK_PM_INDEX(l_prc_module[i]);					
		if(pm_i < 0)
		{
			continue;
		}
					
		if(xEXT_CH__CFG__PMx_USE[pm_i]->Check__DATA(STR__ENABLE) < 0)
		{
			continue;
		}

		if(flag__lp_normal > 0)
		{
			if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__NORMAL) < 0)
			{
				continue;
			}
		}
		else
		{
			if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__TEST) < 0)
			{
				continue;
			}
		}

		if(PMx__Check_Empty__SlotStatus(pm_i) > 0)
		{
			if(PMx__Is_Available(pm_i) > 0)
			{
				return 1;
			}
			else
			{
				if(PMx__Check_CtcInUse_Or_Standby(pm_i) > 0)
				{
					if(ex_pick_check > 0)
					{
						if(xCH_CFG__SCH_LLx_EXCHANGE_WHEN_PMC_EMPTY->Check__DATA(STR__ENABLE) > 0)
						{
							return 1;
						}
					}

					// ...
					{
						CString var_data;
						double  cur_sec;

						CString cur_sts;
						xCH__PMx__PROC_INFO__PROCESS_STATUS[pm_i]->Get__DATA(cur_sts);
					
						if(cur_sts.CompareNoCase("PROCESS.START") == 0)
						{
							if(xCH__PMx__PROCESS_STATUS[pm_i]->Check__DATA("WAIT") > 0)
							{
								return 1;
							}

							xCH__PMx__CURRENT_PRC_TIME[pm_i]->Get__DATA(var_data);
							cur_sec = atof(var_data);

							if(cur_sec < 1)
							{
								return 1;
							}
						}
						if((cur_sts.CompareNoCase("PROCESS.END")  == 0)
						|| (cur_sts.CompareNoCase("PROCESS.COMP") == 0))
						{
							xCH__PMx__IDLE_TIME[pm_i]->Get__DATA(var_data);
							cur_sec = atof(var_data);

							if(cur_sec < 1)
							{
								return 1;
							}
						}
					}
				}
			}
		}
	}

	return -1;
}
int  CObj_Fnc__DUAL_ARM_STD::
Fnc__PMx_Empty_Ready_Check(const int flag__lp_normal,
						   const int pm_i,
						   const int only_available_flag,
						   const int ex_pick_check)
{
	// ...
	if(xEXT_CH__CFG__PMx_USE[pm_i]->Check__DATA(STR__ENABLE) < 0)
	{
		return -1;
	}

	// ...
	if(flag__lp_normal > 0)
	{
		if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__NORMAL) < 0)
		{
			return -1;
		}
	}
	else
	{
		if(xEXT_CH__PMx_PROCESS_TYPE[pm_i]->Check__DATA(STR__TEST) < 0)
		{
			return -1;
		}
	}
					
	// ...
	if(PMx__Check_Empty__SlotStatus(pm_i) > 0)
	{
		if(PMx__Is_Available(pm_i) > 0)
		{
			return 1;
		}
		else
		{
			if(ex_pick_check > 0)
			{
				if(PMx__Check_CtcInUse_Or_Standby(pm_i) > 0)
				{
					if(xCH_CFG__SCH_LLx_EXCHANGE_WHEN_PMC_EMPTY->Check__DATA(STR__ENABLE) > 0)
					{
						return 1;
					}
				}
			}

			if(only_available_flag < 0)
			{
				if(PMx__Check_CtcInUse_Or_Standby(pm_i) > 0)
				{
					CString var_data;
					double  cur_sec;

					CString cur_sts;
					xCH__PMx__PROC_INFO__PROCESS_STATUS[pm_i]->Get__DATA(cur_sts);
					
					if(cur_sts.CompareNoCase("PROCESS.START") == 0)
					{
						// ...
						if(xCH__PMx__PROCESS_STATUS[pm_i]->Check__DATA("WAIT") > 0)
						{
							return 1;
						}

						// ...
						xCH__PMx__CURRENT_PRC_TIME[pm_i]->Get__DATA(var_data);
						cur_sec = atof(var_data);

						if(cur_sec < 1)
						{
							return 1;
						}
					}
					if((cur_sts.CompareNoCase("PROCESS.END")  == 0)
					|| (cur_sts.CompareNoCase("PROCESS.COMP") == 0))
					{
						/*
						// ...
						xCH__PMx__IDLE_TIME[pm_i]->Get__DATA(var_data);
						cur_sec = atof(var_data);

						if(cur_sec < 1)
						{
							return 1;
						}
						*/
						return 1;
					}
				}
			}
			else if(only_available_flag > 0)
			{
				if(PMx__Check_CtcInUse_Or_Standby(pm_i) > 0)
				{
					CString var_data;
					double  cur_sec;
					
					CString cur_sts;
					xCH__PMx__PROC_INFO__PROCESS_STATUS[pm_i]->Get__DATA(cur_sts);
					
					if(cur_sts.CompareNoCase("PROCESS.START") == 0)
					{
						// ...
						xCH__PMx__CURRENT_PRC_TIME[pm_i]->Get__DATA(var_data);
						cur_sec = atof(var_data);
						
						xCH_CFG__PMC_CLN_PROC_TIME_FOR_LBx_PICK->Get__DATA(var_data);
						double cfg_cln_sec = atof(var_data);

						if((cur_sec > 1) && (cur_sec < cfg_cln_sec))
						{
							return 1;
						}
					}
					if((cur_sts.CompareNoCase("PROCESS.END")  == 0)
					|| (cur_sts.CompareNoCase("PROCESS.COMP") == 0))
					{
						/*
						// ...
						xCH__PMx__IDLE_TIME[pm_i]->Get__DATA(var_data);
						cur_sec = atof(var_data);
						
						if(cur_sec < 1)
						{
							return 1;
						}
						*/
						return 1;
					}
				}
			}
			else if(only_available_flag == 0)
			{
				if(PMx__Check_CtcInUse_Or_Standby(pm_i) > 0)
				{
					return 1;
				}
			}
		}
	}

	return -1;
}

int  CObj_Fnc__DUAL_ARM_STD::
_SCH_CHECK__PMo_RB()
{
	CString empty_arm;

	if(VAC_RB__Get_Empty__Arm_Type_From_All(empty_arm) < 0)
	{
		return -11;
	}

	// ...
	CString sch_name;
	CString pm_name;
	CString pm_slot = "1";

	for(int i=0; i<iPMx_SIZE; i++)
	{
		pm_name.Format("PM%1d",i+1);
		sch_name.Format("%s-%s", pm_name,pm_slot);

		if(PMx__Check_Empty__SlotStatus(i) > 0)
		{
			continue;
		}
		if(PMx__Is_Ready(i) < 0)
		{
			continue;
		}

		return 1;
	}
	
	return -1;
}

int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__PMo_RB(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	_AUTO_CTRL__PMo_RB_WITH_DUAL_TYPE(p_variable, p_alarm);
	_AUTO_CTRL__PMo_RB(p_variable, p_alarm);

	NEXT__LOOP;
}
int  CObj_Fnc__DUAL_ARM_STD::
_AUTO_CTRL__PMo_RB_WITH_DUAL_TYPE(CII_OBJECT__VARIABLE *p_variable,
								  CII_OBJECT__ALARM *p_alarm)
{
	if(xCH_CFG__LLx_CTRL_ONLY_INPUT_OUTPUT_MODE->Check__DATA(STR__DUAL) < 0)		return -1;
	if(xCH_CFG__DUAL_ARM_CURRENT_BEHAVIOR->Check__DATA(STR__ENABLE) < 0)			return -2;
	if(VAC_RB__Check_Empty__Dual_Arm() < 0)											return -3;

	CString log_id = "_AUTO_CTRL__PMo_RB_WITH_DUAL_TYPE()";

	// ...
	IDS__SCH_MATERIAL_STATUS ds_sts;

	int pm_min_index = -1;
	int pm_min_count = -1;
	int pm_cur_count = -1;

	for(int i=0; i<iPMx_SIZE; i++)
	{
		CString pm_name;
		CString sch_name;

		pm_name.Format("PM%1d",  i+1);
		sch_name.Format("%s-1", pm_name);

		if(PMx__Check_Empty__SlotStatus(i) > 0)
		{
			continue;
		}

		if(xEXT_CH__CFG__PMx_USE[i]->Check__DATA("ENABLE") > 0)
		{
			if(PMx__Is_Available(i) < 0)
			{
				continue;
			}
		}
		else
		{
			if(PMx__Is_Idle(i) < 0)
			{
				continue;
			}
		}

		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(sch_name,ds_sts) < 0)
		{
			continue;
		}

		if(SCH__PMx_CHECK_PRESSURE(i,p_variable,p_alarm) < 0)
		{
			continue;
		}

		CString var_data = xCH__PMx__IN_COUNT[i]->Get__STRING();
		pm_cur_count = atoi(var_data);
		
		if(pm_cur_count < 1)
		{
			continue;
		}

		if((pm_min_count < 1)		
		|| (pm_cur_count < pm_min_count))
		{
			pm_min_count = pm_cur_count;
			pm_min_index = i;
		}
	}

	if((pm_min_index % 2) != 0)
	{
		NEXT__LOOP;
	}

	if(pm_min_index >= 0)
	{
		CString sch_left;
		CString sch_right;

		CString pm_left;
		CString pm_right;

		int id_left  = pm_min_index + 1;
		int id_right = pm_min_index + 2;

		pm_left.Format("PM%1d",  id_left);
		pm_right.Format("PM%1d", id_right);

		sch_left.Format("%s-1",  pm_left);
		sch_right.Format("%s-1", pm_right);

		if(PMx__Check_Empty__SlotStatus(id_left  - 1) > 0)					NEXT__LOOP;
		if(PMx__Check_Empty__SlotStatus(id_right - 1) > 0)					NEXT__LOOP;

		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_left)  > 0)			NEXT__LOOP;
		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_right) > 0)			NEXT__LOOP;

		// ...
		{
			CString log_xxx;
			log_xxx.Format("%s - check_pmc_pick[%1d & %1d] \n", log_id, id_left, id_right);

			// ...
			int act_flag  = -1;
			int move_flag = -1;

			CString empty_arm = "AB";
			CString para_pmc;

			para_pmc.Format("PM%1d%1d", id_left,id_right);
			
			CStringArray l_from_sch;
			l_from_sch.Add(sch_left);
			l_from_sch.Add(sch_right);

			act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_xxx, false, empty_arm, para_pmc,"1", l_from_sch);

			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Pick(empty_arm);
			}
			else
			{
				move_flag = 1;
			}

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_left,  "A");
				xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_right, "B");
		
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS("A", "PROCESSED");
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS("B", "PROCESSED");
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}

		// Post Clean .....
		{
			CString cln_module;
			CString cln_recipe;

			xSCH_MATERIAL_CTRL->Get__POST_CLN_In_PMC(pm_left, id_left,  cln_module,cln_recipe);
			xSCH_MATERIAL_CTRL->Get__POST_CLN_In_PMC(pm_right,id_right, cln_module,cln_recipe);
		}
		return 1;
	}

	NEXT__LOOP;
}
int  CObj_Fnc__DUAL_ARM_STD::
_AUTO_CTRL__PMo_RB(CII_OBJECT__VARIABLE *p_variable,
				   CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "AUTO_CTRL__PMo_RB()";

	// ...
	CString empty_arm;

	if(xCH_CFG__LLx_CTRL_ONLY_INPUT_OUTPUT_MODE->Check__DATA(STR__DUAL) > 0)
	{

	}
	else
	{
		if(VAC_RB__Get_Empty__Arm_Type_From_PMx(empty_arm) < 0)
		{
			NEXT__LOOP;
		}
	}

	// ...
	{
		CString arm_type;

		// Arm : A ...
		if(VAC_RB__Check_Occupied__A_Arm() > 0)
		{
			arm_type = "A";

			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) < 0)
			{
				if(SCH__LBx__CHECK_ONLY_MODE() < 0)
				{
					NEXT__LOOP;
				}
			}

			if(xCH_CFG__SCH_EXCHANGE_PRIORITY->Check__DATA(STR__PMC) > 0)
			{
				if(Fnc__PMC_Empty_Ready_Check(arm_type) > 0)
				{
					NEXT__LOOP;
				}
			}
		}
		// Arm : B ...
		if(VAC_RB__Check_Occupied__B_Arm() > 0)
		{
			arm_type = "B";
			
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) < 0)
			{
				if(SCH__LBx__CHECK_ONLY_MODE() < 0)
				{
					NEXT__LOOP;
				}
			}

			if(xCH_CFG__SCH_EXCHANGE_PRIORITY->Check__DATA(STR__PMC) > 0)
			{
				if(Fnc__PMC_Empty_Ready_Check(arm_type) > 0)
				{
					NEXT__LOOP;
				}
			}
		}
	}

	// ...
	IDS__SCH_MATERIAL_STATUS ds_sts;

	CString sch_name;
	CString pm_name;
	CString pm_slot = "1";

	CString var_data;
	int pm_min_index = -1;
	int pm_min_count = -1;
	int pm_cur_count = -1;
	int i;

	for(i=0; i<iPMx_SIZE; i++)
	{
		pm_name.Format("PM%1d",i+1);
		sch_name.Format("%s-%s",pm_name,pm_slot);

		if(PMx__Check_Empty__SlotStatus(i) > 0)
		{
			continue;
		}

		if(xEXT_CH__CFG__PMx_USE[i]->Check__DATA("ENABLE") > 0)
		{
			if(PMx__Is_Available(i) < 0)
			{
				continue;
			}

			/*
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_name) > 0)
			{
				continue;
			}
			*/
		}
		else
		{
			if(PMx__Is_Idle(i) < 0)
			{
				continue;
			}
		}

		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(sch_name,ds_sts) < 0)
		{
			continue;
		}

		if(SCH__PMx_CHECK_PRESSURE(i,p_variable,p_alarm) < 0)
		{
			continue;
		}

		xCH__PMx__IN_COUNT[i]->Get__DATA(var_data);
		pm_cur_count = atoi(var_data);
		
		if(pm_cur_count < 1)
		{
			continue;
		}

		if((pm_min_count < 1)		
		|| (pm_cur_count < pm_min_count))
		{
			pm_min_count = pm_cur_count;
			pm_min_index = i;
		}
	}

	if(pm_min_index >= 0)
	{
		CString sch_name;
		CString pm_name;
		CString pm_slot = "1";
		int pmc_id = pm_min_index+1;

		pm_name.Format("PM%1d",pm_min_index+1);
		sch_name.Format("%s-%s",pm_name,pm_slot);

		int check__pmc_pick = -1;

		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_name) < 0)
		{
			int ll_limit = iLLx_LIMIT;
			int ll_i;

			for(ll_i=0; ll_i<ll_limit; ll_i++)
			{
				if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
				{
					if((LLx__Is_Available(ll_i) > 0)
					&& (LLx__Check_Empty__OutSlot(ll_i) > 0))
					{
						check__pmc_pick = 1;
					}
				}
			}
		}
		else
		{
			CStringArray l_pm_name;
			CStringArray l_pm_rcp;

			if(xSCH_MATERIAL_CTRL->Get__NEXT_PROCESS_INFO(sch_name, l_pm_name,l_pm_rcp) > 0)
			{
				int i_limit = l_pm_name.GetSize();
				int i;

				for(i=0; i<i_limit; i++)
				{
					int pm_i = Macro__Get_PMC_ID(l_pm_name[i]) - 1;
					if(pm_i < 0)		continue;;
					
					if(xEXT_CH__CFG__PMx_USE[pm_i]->Check__DATA("ENABLE") < 0)
					{
						continue;
					}

					if(PMx__Is_Available(pm_i) < 0)
					{
						continue;
					}
					if(PMx__Check_Empty__SlotStatus(pm_i) < 0)
					{
						continue;
					}

					check__pmc_pick = 2;
					break;
				}
			}
		}

		// ...
		{
			CString arm_type;

			if(VAC_RB__Get_Occupied__Arm_Type(arm_type) > 0)
			{
				if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) < 0)
				{
					int ll_limit = iLLx_LIMIT;
					int ll_i;

					for(ll_i=0; ll_i<ll_limit; ll_i++)
					{
						if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
						{
							if((LLx__Is_Available(ll_i) > 0)
							&& (LLx__Check_Empty__OutSlot(ll_i) > 0))
							{
								NEXT__LOOP;
							}
						}
					}

					if(check__pmc_pick < 0)
					{
						NEXT__LOOP;
					}
				}
				else
				{
					CStringArray l_pm_name;
					CStringArray l_pm_rcp;
					int i_limit;
					int i;

					if(xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type,l_pm_name,l_pm_rcp) > 0)
					{
						// Robot_Arm Wafer & PM Wafer ...
						i_limit = l_pm_name.GetSize();

						for(i=0; i<i_limit; i++)
						{
							if(pm_name.CompareNoCase(l_pm_name[i]) != 0)
							{
								continue;
							}

							NEXT__LOOP;
						}

						// PM Empty Check ...
						i_limit = l_pm_name.GetSize();

						for(i=0; i<i_limit; i++)
						{
							int i_pmx = Macro__Get_PMC_ID(l_pm_name[i]) - 1;
							if(i_pmx < 0)		continue;

							if(xEXT_CH__CFG__PMx_USE[i_pmx]->Check__DATA("ENABLE") < 0)
							{
								continue;
							}

							if(PMx__Is_Available(i_pmx) < 0)
							{
								continue;
							}
							if(PMx__Check_Empty__SlotStatus(i_pmx) < 0)
							{
								continue;
							}

							NEXT__LOOP;
						}
					}

					if(check__pmc_pick < 0)
					{
						NEXT__LOOP;
					}
				}

				// ...
			}
		}

		if(xCH_CFG__LLx_CTRL_ONLY_INPUT_OUTPUT_MODE->Check__DATA(STR__DUAL) > 0)
		{
			if(VAC_RB__Get_Empty__Arm_Type_With_PMx_Constraint(empty_arm, pm_name) < 0)
			{
				NEXT__LOOP;
			}
		}

		// ...
		{
			CString log_xxx;

			log_xxx.Format("%s - check_pmc_pick[%1d] \n", log_id,check__pmc_pick);

			// ...
			int act_flag  = -1;
			int move_flag = -1;

			act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_xxx, false,empty_arm,pm_name,pm_slot,sch_name);

			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Pick(empty_arm);
			}
			else
			{
				move_flag = 1;
			}

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_name, empty_arm);
		
				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(empty_arm, "PROCESSED");
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}

		// Post Clean .....
		{
			CString cln_module;
			CString cln_recipe;

			int flag 
				= xSCH_MATERIAL_CTRL->Get__POST_CLN_In_PMC(pm_name,
														   pmc_id,
														   cln_module,
														   cln_recipe);
			
			if(flag > 0)
			{

			}
		}

		return 1;
	}

	NEXT__LOOP;
}

int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__PMx_RB(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	bool active__output_dual = false;

	// PMx -> RB
	if(xCH_CFG__LLx_CTRL_ONLY_INPUT_OUTPUT_MODE->Check__DATA(STR__DUAL) > 0)
	{
		if(SCH__LBx__CHECK_EMPTY_OF_ONLY_OUTPUT() > 0)		active__output_dual = true;
	}

	_AUTO_CTRL__PMx_RB(p_variable, p_alarm, active__output_dual);
	return 1;
}
int  CObj_Fnc__DUAL_ARM_STD::
_AUTO_CTRL__PMx_RB(CII_OBJECT__VARIABLE *p_variable,
				   CII_OBJECT__ALARM *p_alarm,
				   const bool active_all)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "_AUTO_CTRL__PMx_RB()";

	// ...
	CString arm_type;

	if(active_all)
	{
		if(VAC_RB__Get_Empty__Arm_Type_From_All(arm_type) < 0)		NEXT__LOOP;
	}
	else
	{
		if(VAC_RB__Check_Empty__Dual_Arm() < 0)						NEXT__LOOP;
		if(VAC_RB__Get_Empty__Arm_Type_From_PMx(arm_type) < 0)		NEXT__LOOP;
	}

	// ...
	IDS__SCH_MATERIAL_STATUS ds_sts;
	int i;

	for(i=0; i<iPMx_SIZE; i++)
	{
		if(PMx__Check_Empty__SlotStatus(i) > 0)		continue;
		if(PMx__Is_Available(i) < 0)				continue;

		if(SCH__PMx_CHECK_PRESSURE(i,p_variable,p_alarm) < 0)
		{
			continue;
		}

		// ...
		CString sch_name;
		CString pm_name;
		CString pm_slot = "1";

		pm_name.Format("PM%1d", i+1);
		sch_name.Format("%s-%s", pm_name,pm_slot);

		if(xCH_CFG__LLx_CTRL_ONLY_INPUT_OUTPUT_MODE->Check__DATA(STR__DUAL) > 0)
		{
			if(VAC_RB__Get_Empty__Arm_Type_With_PMx_Constraint(arm_type, pm_name) < 0)
			{
				NEXT__LOOP;
			}
		}

		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(sch_name,ds_sts) < 0)
		{
			continue;
		}

		// ...
		{
			int act_flag  = -1;
			int move_flag = -1;

			act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,arm_type,pm_name,pm_slot,sch_name);

			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Pick(arm_type);
			}
			else
			{
				move_flag = 1;
			}

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_name,arm_type);

				xSCH_MATERIAL_CTRL->Set__MATERIAL_STATUS(arm_type, "PROCESSED");
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}

		NEXT__LOOP;
	}

	NEXT__LOOP;
}

int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__RB_LBo__ONLY_MODE(CII_OBJECT__VARIABLE *p_variable,
							 CII_OBJECT__ALARM *p_alarm)
{
	_AUTO_CTRL__RB_LBo__ONLY_MODE_WITH_DUAL_TYPE(p_variable, p_alarm);
	_AUTO_CTRL__RB_LBo__ONLY_MODE(p_variable, p_alarm);

	NEXT__LOOP;
}
int  CObj_Fnc__DUAL_ARM_STD::
_AUTO_CTRL__RB_LBo__ONLY_MODE_WITH_DUAL_TYPE(CII_OBJECT__VARIABLE *p_variable,
											 CII_OBJECT__ALARM *p_alarm)
{

	if(xCH_CFG__LLx_CTRL_ONLY_INPUT_OUTPUT_MODE->Check__DATA(STR__DUAL) < 0)		return -1;
	if(xCH_CFG__DUAL_ARM_CURRENT_BEHAVIOR->Check__DATA(STR__ENABLE) < 0)			return -2;
	if(VAC_RB__Check_Occupied__Dual_Arm() < 0)										return -3;

	// ...
	CString log_id = "_AUTO_CTRL__RB_LBo__ONLY_MODE_WITH_DUAL_TYPE()";

	// ...
	CStringArray l_arm;	
	Get__Arm_List_To_LPx(l_arm);

	if(l_arm.GetSize() < 1)
	{
		NEXT__LOOP;
	}

	// ...
	int sch_ll_id = -1;
	CUIntArray l__sch_ll_slot;

	// Check : LLx ...
	if(sEXT_CH__SCH_MODE_LLx_OUT->Check__DATA(_SCH_MODE__ROUTE) > 0)
	{
		int i_limit = l_arm.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CString arm_type = l_arm[i];

			// ...
			CStringArray l_ll_id;
			CStringArray l_ll_mode;
			CStringArray l_ll_slot;

			xSCH_MATERIAL_CTRL->Get__LLx_OUT_OF_EDIT_TYPE(arm_type, l_ll_id,l_ll_mode,l_ll_slot);

			int k_limit = l_ll_id.GetSize();
			int k;

			for(k=0; k<k_limit; k++)
			{
				int ll_i = atoi(l_ll_id[k]) - 1;

				if(ll_i <  0)				continue;
				if(ll_i >= iLLx_LIMIT)		continue;

				// ...
				CString str_mode = l_ll_mode[k];
				CString str_slot = l_ll_slot[k];

				if(str_mode.CompareNoCase("ONLY_OUTPUT") != 0)
					continue;

				if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) < 0)
					continue;

				// ...
				CUIntArray l_slot;
				int slot_id;

				if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") < 0)			continue;
				if(LLx__Is_Available(ll_i) < 0)										continue;
				if(LLx__Get_Empty__OutSlot(ll_i, slot_id) < 0)						continue;

				if(str_slot.CompareNoCase("11") == 0)
				{
					slot_id = 1;
					if(LLx__Check_Empty__OutSlot(ll_i, slot_id) > 0)		l_slot.Add(slot_id);

					slot_id = 2;
					if(LLx__Check_Empty__OutSlot(ll_i, slot_id) > 0)		l_slot.Add(slot_id);
				}
				else if(str_slot.CompareNoCase("10") == 0)
				{
					slot_id = 1;
					if(LLx__Check_Empty__OutSlot(ll_i, slot_id) > 0)		l_slot.Add(slot_id);
				}	
				else if(str_slot.CompareNoCase("01") == 0)
				{
					slot_id = 2;
					if(LLx__Check_Empty__OutSlot(ll_i, slot_id) > 0)		l_slot.Add(slot_id);
				}

				if(l_slot.GetSize() < 1)			
				{
					continue;
				}

				sch_ll_id = ll_i + 1;
				l__sch_ll_slot.Copy(l_slot);
				break;
			}

			if(sch_ll_id > 0)
			{
				break;
			}
		}
	}
	else
	{
		int active__only_output = -1;

		int i_limit = iLLx_LIMIT;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) < 0)
			{
				continue;
			}

			// ...
			int eixt_flag = -1;
			int slot_id;

			if(xEXT_CH__LLx__IN_OUT_FLAG[i]->Check__DATA("IN") < 0)			eixt_flag = 1;
			if(LLx__Is_Available(i) < 0)									eixt_flag = 2;
			if(LLx__Get_Empty__OutSlot(i, slot_id) < 0)						eixt_flag = 3;

			if(SCH__LLx_CHECK_PRESSURE(i, p_variable,p_alarm,1) < 0)
			{
				eixt_flag = 11;
			}

			if(eixt_flag > 0)
			{
				continue;
			}

			// ...
			{
				sch_ll_id = i + 1;
				l__sch_ll_slot.Add(slot_id);
			}

			active__only_output = 1;
			break;
		}

		if(active__only_output < 0)
		{
			NEXT__LOOP;
		}
	}

	if(sch_ll_id < 0)
	{
		NEXT__LOOP;
	}

	// ...
	{
		int sch_ll_i = sch_ll_id - 1;
		int slot_max = l__sch_ll_slot.GetSize();

		int i_limit = l_arm.GetSize();
		int i;

		if(slot_max < i_limit)
		{
			i_limit = slot_max;
		}

		if(i_limit < 2)
		{
			NEXT__LOOP;
		}

		// ...
		{
			CString arm_type = "AB";
			int slot_id = l__sch_ll_slot[0];

			// ...
			CString sch_01;
			CString sch_02;
			CString para_module;
			CString para_slot;

			para_module = Get__LLx_NAME(sch_ll_i);
			para_slot.Format("%1d", slot_id);

			sch_01.Format("%s-%1d", para_module,slot_id);
			sch_02.Format("%s-%1d", para_module,slot_id+1);

			// ...
			int act_flag  = -1;
			int move_flag = -1;

			act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, false,arm_type,para_module,para_slot,sch_01,sch_02);

			if(act_flag < 0)
			{
				move_flag = 1;

				if(SCH__Check_Material_Place("A") < 0)		move_flag = -1;
				if(SCH__Check_Material_Place("B") < 0)		move_flag = -1;
			}
			else
			{
				move_flag = 1;
			}		

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Place__To_MODULE("A", sch_01);
				xSCH_MATERIAL_CTRL->Place__To_MODULE("B", sch_02);
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}

		if(LLx__Is_Available(sch_ll_i) > 0)
		{
			if(LLx__Check_Empty__OutSlot(sch_ll_i) < 0)
			{
				SCH_RUN__LLx_VENT(sch_ll_i, log_id, "1");

				xEXT_CH__LLx__IN_OUT_FLAG[sch_ll_i]->Set__DATA("OUT");
			}
			else
			{
				if(SCH__CHECK_MATERIAL_CLEAR() > 0)
				{
					SCH_RUN__LLx_VENT(sch_ll_i, log_id, "2");

					xEXT_CH__LLx__IN_OUT_FLAG[sch_ll_i]->Set__DATA("OUT");
				}
			}
		}
		else
		{
			if(LLx__Check_Empty__OutSlot(sch_ll_i) < 0)
			{
				sEXT_CH__LLx__NEXT_CTRL_REQ[sch_ll_i]->Set__DATA("VENTING");
				xEXT_CH__LLx__IN_OUT_FLAG[sch_ll_i]->Set__DATA("OUT");
			}
		}
	}

	NEXT__LOOP;
}
int  CObj_Fnc__DUAL_ARM_STD::
_AUTO_CTRL__RB_LBo__ONLY_MODE(CII_OBJECT__VARIABLE *p_variable,
							  CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "_AUTO_CTRL__RB_LBo__ONLY_MODE()";

	// RB -> LBo : ONLY_MODE
	if(xCH_CFG__LLx_CTRL_ONLY_INPUT_OUTPUT_MODE->Check__DATA(STR__DUAL) > 0)
	{
		if(_SCH_CHECK__PMo_RB() > 0)		NEXT__LOOP;
	}

	// ...
	CStringArray l_arm;	
	Get__Arm_List_To_LPx(l_arm);

	if(l_arm.GetSize() < 1)
	{
		NEXT__LOOP;
	}

	// ...
	int sch_ll_id = -1;
	CUIntArray l__sch_ll_slot;

	// Check : LLx ...
	if(sEXT_CH__SCH_MODE_LLx_OUT->Check__DATA(_SCH_MODE__ROUTE) > 0)
	{
		int i_limit = l_arm.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CString arm_type = l_arm[i];

			// ...
			CStringArray l_ll_id;
			CStringArray l_ll_mode;
			CStringArray l_ll_slot;

			xSCH_MATERIAL_CTRL->Get__LLx_OUT_OF_EDIT_TYPE(arm_type, l_ll_id,l_ll_mode,l_ll_slot);

			int k_limit = l_ll_id.GetSize();
			int k;

			for(k=0; k<k_limit; k++)
			{
				int ll_i = atoi(l_ll_id[k]) - 1;

				if(ll_i <  0)				continue;
				if(ll_i >= iLLx_LIMIT)		continue;

				// ...
				CString str_mode = l_ll_mode[k];
				CString str_slot = l_ll_slot[k];

				if(str_mode.CompareNoCase("ONLY_OUTPUT") != 0)
					continue;

				if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) < 0)
					continue;

				// ...
				CUIntArray l_slot;
				int slot_id;

				if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") < 0)			continue;
				if(LLx__Is_Available(ll_i) < 0)										continue;
				if(LLx__Get_Empty__OutSlot(ll_i, slot_id) < 0)						continue;
				
				if(str_slot.CompareNoCase("11") == 0)
				{
					slot_id = 1;
					if(LLx__Check_Empty__OutSlot(ll_i, slot_id) > 0)		l_slot.Add(slot_id);

					slot_id = 2;
					if(LLx__Check_Empty__OutSlot(ll_i, slot_id) > 0)		l_slot.Add(slot_id);
				}
				else if(str_slot.CompareNoCase("10") == 0)
				{
					slot_id = 1;
					if(LLx__Check_Empty__OutSlot(ll_i, slot_id) > 0)		l_slot.Add(slot_id);
				}	
				else if(str_slot.CompareNoCase("01") == 0)
				{
					slot_id = 2;
					if(LLx__Check_Empty__OutSlot(ll_i, slot_id) > 0)		l_slot.Add(slot_id);
				}

				if(l_slot.GetSize() < 1)			
				{
					continue;
				}

				sch_ll_id = ll_i + 1;
				l__sch_ll_slot.Copy(l_slot);
				break;
			}

			if(sch_ll_id > 0)
			{
				break;
			}
		}
	}
	else
	{
		int active__only_output = -1;

		int i_limit = iLLx_LIMIT;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) < 0)
			{
				continue;
			}

			// ...
			int eixt_flag = -1;
			int slot_id;

			if(xEXT_CH__LLx__IN_OUT_FLAG[i]->Check__DATA("IN") < 0)			eixt_flag = 1;
			if(LLx__Is_Available(i) < 0)									eixt_flag = 2;
			if(LLx__Get_Empty__OutSlot(i, slot_id) < 0)						eixt_flag = 3;

			if(SCH__LLx_CHECK_PRESSURE(i, p_variable,p_alarm,1) < 0)
			{
				eixt_flag = 11;
			}

			if(eixt_flag > 0)
			{
				continue;
			}

			// ...
			{
				sch_ll_id = i + 1;
				l__sch_ll_slot.Add(slot_id);
			}

			active__only_output = 1;
			break;
		}

		if(active__only_output < 0)
		{
			NEXT__LOOP;
		}
	}

	if(sch_ll_id < 0)
	{
		NEXT__LOOP;
	}

	// ...
	{
		int sch_ll_i = sch_ll_id - 1;
		int slot_max = l__sch_ll_slot.GetSize();

		int i_limit = l_arm.GetSize();
		int i;

		if(slot_max < i_limit)
		{
			i_limit = slot_max;
		}
		
		for(i=0; i<i_limit; i++)
		{
			CString arm_type = l_arm[i];
			int slot_id = l__sch_ll_slot[i];

			// ...
			CString sch_module;
			CString para_module;
			CString para_slot;

			para_module = Get__LLx_NAME(sch_ll_i);
			para_slot.Format("%1d", slot_id);
			sch_module.Format("%s-%s", para_module,para_slot);

			// ...
			int act_flag  = -1;
			int move_flag = -1;

			if((i+1) == i_limit)
			{
				act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, false,arm_type,para_module,para_slot,sch_module);
			}
			else
			{
				act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, true,arm_type,para_module,para_slot,sch_module);
			}

			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Place(arm_type);
			}
			else
			{
				move_flag = 1;
			}		

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}

		if(LLx__Is_Available(sch_ll_i) > 0)
		{
			if(LLx__Check_Empty__OutSlot(sch_ll_i) < 0)
			{
				SCH_RUN__LLx_VENT(sch_ll_i, log_id, "1");

				xEXT_CH__LLx__IN_OUT_FLAG[sch_ll_i]->Set__DATA("OUT");
			}
			else
			{
				if(SCH__CHECK_MATERIAL_CLEAR() > 0)
				{
					SCH_RUN__LLx_VENT(sch_ll_i, log_id, "2");

					xEXT_CH__LLx__IN_OUT_FLAG[sch_ll_i]->Set__DATA("OUT");
				}
			}
		}
		else
		{
			if(LLx__Check_Empty__OutSlot(sch_ll_i) < 0)
			{
				sEXT_CH__LLx__NEXT_CTRL_REQ[sch_ll_i]->Set__DATA("VENTING");
				xEXT_CH__LLx__IN_OUT_FLAG[sch_ll_i]->Set__DATA("OUT");
			}
		}
	}

	NEXT__LOOP;
}
int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__RB_LBo__1_SLOT_ALL_MODE(CII_OBJECT__VARIABLE *p_variable,
								   CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "AUTO_CTRL__RB_LBo__1_SLOT_ALL_MODE()";

	// LLx ...
	{
		int active__all_mode = -1;
		
		int ll_limit = iLLx_LIMIT;
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

	if(VAC_RB__Check_Empty__Dual_Arm() > 0)
	{
		NEXT__LOOP;
	}

	// ...
	int out_flag = -1;

	CString para_module;
	CString para_in_slot;
	CString para_slot;
	int slot_id;

	// ...
	int active__sch_mode = -1;
	int active__sch_ll = -1;
	
	CString check_arm = "";

	if(sEXT_CH__SCH_MODE_LLx_OUT->Check__DATA(_SCH_MODE__ROUTE) > 0)
	{
		for(int i=0; i<2; i++)
		{
			if(i == 0)
			{
				if(VAC_RB__Check_Occupied__A_Arm() < 0)
					continue;

				check_arm = "A";
			}
			else if(i == 1)
			{
				if(VAC_RB__Check_Occupied__B_Arm() < 0)
					continue;

				check_arm = "B";
			}
			else
			{
				continue;
			}

			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(check_arm) > 0)
			{
				check_arm = "";
				continue;
			}

			break;
		}

		if(check_arm.GetLength() > 0)
		{
			CStringArray l_ll_id;
			CStringArray l_ll_mode;
			CStringArray l_ll_slot;

			xSCH_MATERIAL_CTRL->Get__LLx_OUT_OF_EDIT_TYPE(check_arm, l_ll_id,l_ll_mode,l_ll_slot);

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
		else
		{
			NEXT__LOOP;
		}
	}

	if(active__sch_mode > 0)
	{
		IDS__SCH_MATERIAL_INFO ds_info;
		int ll_ptn = -1;

		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(check_arm, ds_info) > 0)
		{
			ll_ptn = ds_info.iSRC__PTN;
		}

		// LLx ...
		if(active__sch_ll > 0)					
		{
			int ll_i = active__sch_ll - 1;

			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
			{
				if((SCH__LLx_CHECK_PRESSURE(ll_i, p_variable,p_alarm) > 0)
				&& (LLx__Is_Available(ll_i) > 0))
				{
					if(LLx__Get_Occupied__InSlot_With_1_Slot_All_Mode(ll_i, slot_id) > 0)
					{
						para_module = Get__LLx_NAME(ll_i);
						para_slot.Format("%1d",slot_id);
						para_in_slot.Format("%1d",slot_id);

						out_flag = 1;
					}
					else if(LLx__Get_Empty__InSlot_With_1_Slot_All_Mode(ll_i, slot_id) > 0)
					{
						para_module = Get__LLx_NAME(ll_i);
						para_slot.Format("%1d",slot_id);

						out_flag = 1;
					}
				}
			}
			else if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
			{
				if(xEXT_CH__ATM_RB__SCH_STS_TO_LLx[ll_i]->Check__DATA("") < 0)
				{
					NEXT__LOOP;
				}

				// ....
				{
					bool active__ll_out = false;

					if(VAC_RB__Check_Occupied__A_Arm() > 0)		
					{
						CString vac_arm = "A";
						if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(vac_arm) < 0)		active__ll_out = true;
					}
					if(VAC_RB__Check_Occupied__B_Arm() > 0)		
					{
						CString vac_arm = "B";
						if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(vac_arm) < 0)		active__ll_out = true;
					}

					if(!active__ll_out)			NEXT__LOOP;
				}

				if((LLx__Is_Available(ll_i) > 0)
				&& (LLx__Is_ATM(ll_i) > 0))
				{
					if(LLx__Get_Empty__InSlot_With_1_Slot_All_Mode(ll_i, slot_id) > 0)
					{
						para_module = Get__LLx_NAME(ll_i);
						para_slot.Format("%1d",slot_id);

						out_flag = 1;

						if(SCH_RUN__LLx_PUMP(ll_i, log_id, "") > 0)
						{
							xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
						}
						NEXT__LOOP;
					}
				}
			}

			// ...
		}
	}
	else
	{
		int ll_limit = iLLx_LIMIT;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(out_flag < 0)
			{
				if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
				{
					if((SCH__LLx_CHECK_PRESSURE(ll_i, p_variable,p_alarm) > 0)
					&& (LLx__Is_Available(ll_i) > 0))
					{
						if(LLx__Get_Occupied__InSlot_With_1_Slot_All_Mode(ll_i, slot_id) > 0)
						{
							para_module = Get__LLx_NAME(ll_i);
							para_slot.Format("%1d",slot_id);
							para_in_slot.Format("%1d",slot_id);

							out_flag = 1;
						}
						else if(LLx__Get_Empty__InSlot_With_1_Slot_All_Mode(ll_i, slot_id) > 0)
						{
							para_module = Get__LLx_NAME(ll_i);
							para_slot.Format("%1d",slot_id);

							out_flag = 1;
						}
					}
				}
			}
		}

		// ...
	}

	if(out_flag < 0)
	{
		NEXT__LOOP;
	}

	// ...
	{
		printf(" * CObj_Fnc__DUAL_ARM_STD::AUTO_CTRL__RB_LBo__1_SLOT_ALL_MODE() ... \n");

		printf("  * active__sch_mode <- [%1d] \n", active__sch_mode);
		printf("  * active__sch_ll   <- [%1d] \n", active__sch_ll);

		printf("  * para_module  <- [%s] \n", para_module);
		printf("  * para_slot    <- [%s] \n", para_slot);
		printf("  * para_in_slot <- [%s] \n", para_in_slot);
	}

	// ...
	CString arm_type;
	int i;

	for(i=0; i<2; i++)
	{
		if(i == 0)
		{
			if(VAC_RB__Check_Occupied__A_Arm() < 0)	
			{
				continue;
			}

			arm_type = "A";
		}
		else if(i == 1)
		{
			if(VAC_RB__Check_Occupied__B_Arm() < 0)
			{
				continue;
			}

			arm_type = "B";
		}
		else
		{
			continue;
		}

		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
		{
			continue;
		}

		IDS__SCH_MATERIAL_STATUS ds_info;
		if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info) < 0)
		{
			continue;
		}
		if(ds_info.sMATERIAL_STS.CompareNoCase("PROCESSED") != 0)
		{
			continue;
		}

		// ...
		bool lbx_ex_flag = false;
		CString sch_module;
		CString empty_arm;

		if(para_in_slot.GetLength() > 0)
		{
			if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
			{
				NEXT__LOOP;
			}

			lbx_ex_flag = true;	
		}

		if(lbx_ex_flag == true)
		{
			int act_flag  = -1;
			int move_flag = -1;

			sch_module.Format("%s-%s",para_module,para_in_slot);

			act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, lbx_ex_flag,empty_arm,para_module,para_in_slot,sch_module);

			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Pick(empty_arm);
			}
			else
			{
				move_flag = 1;
			}

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,empty_arm);
			}

			// ...
			{
				CString log_msg;
				CString log_bff;

				log_msg = "AUTO_CTRL__RB_LBo__1_SLOT_ALL_MODE() ... \n";
				log_bff.Format(" sch_module : [%s] \n", sch_module);
				log_msg += log_bff;
				log_bff.Format(" empty_arm : [%s] \n", empty_arm);
				log_msg += log_bff;
				log_bff.Format(" act_flag : [%1d] \n", act_flag);
				log_msg += log_bff;

				printf(" * %s\n", log_msg);
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}

		// ...
		{
			int act_flag  = -1;
			int move_flag = -1;

			sch_module.Format("%s-%s",para_module,para_slot);	

			act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, false,arm_type,para_module,para_slot,sch_module);

			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Place(arm_type);
			}
			else
			{
				move_flag = 1;
			}
			
			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}

		// ...
		int ll_i = Get__LLx_INDEX(para_module);
		if(ll_i >= 0)
		{
			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") < 0)
			{
				if(SCH_RUN__LLx_VENT(ll_i, log_id, "1") > 0)
				{
					xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
				}
			}
		}

		NEXT__LOOP;
	}

	NEXT__LOOP;
}

int  CObj_Fnc__DUAL_ARM_STD::
Fnc__Get_LLx__Empty_Out_Slot(CII_OBJECT__VARIABLE* p_variable,
							 CII_OBJECT__ALARM* p_alarm,
							 const int ok_check,
							 const int ll_i,
							 CString& ll_name,
							 CString& ll_slot)
{
	if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
	{
		if((SCH__LLx_CHECK_PRESSURE(ll_i, p_variable,p_alarm) > 0)
		&& (LLx__Is_Available(ll_i) > 0))
		{
			int lbx_ok = -1;
			int slot_id;

			if(ok_check > 0)
			{
				if(LLx__Check_All_Empty(ll_i) > 0)
				{
					lbx_ok = 1;
				}
				else if(VAC_RB__Check_Occupied__Dual_Arm() > 0)		
				{
					lbx_ok = 1;
				}
			}
			else
			{
				lbx_ok = 1;
			}

			if(lbx_ok > 0)
			{
				if(LLx__Get_Empty__OutSlot(ll_i, slot_id) > 0)
				{
					ll_name = Get__LLx_NAME(ll_i);
					ll_slot.Format("%1d",slot_id);
					return 1;
				}
			}
		}
	}
	return -1;
}

int  CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__RB_LBo__ALL_MODE(CII_OBJECT__VARIABLE *p_variable,
							CII_OBJECT__ALARM *p_alarm,
							const int loop_count)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "AUTO_CTRL__RB_LBo__ALL_MODE()";

	// LLx ...
	{
		int ll_limit = iLLx_LIMIT;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ALL) < 0)
			{
				NEXT__LOOP;
			}
		}
	}

	if(xCH_CFG__SCH_PMC_RECIPE_TYPE->Check__DATA(STR__PRC_CLN) > 0)
	{

	}
	else
	{
		if(VAC_RB__Check_Dual_Arm_Enable() > 0)
		{
			if(VAC_RB__Check_Empty__Dual_Arm() > 0)	
			{
				NEXT__LOOP;
			}
		}
		else
		{
			if(VAC_RB__Check_All_Empty() > 0)
			{
				NEXT__LOOP;
			}
		}
	}

	// ...
	{
		CString arm_type;
		
		// Arm : A ...
		if(VAC_RB__Check_Occupied__A_Arm() > 0)
		{
			arm_type = "A";
			
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				if(xCH_CFG__SCH_EXCHANGE_PRIORITY->Check__DATA(STR__PMC) > 0)
				{
					if(Fnc__PMC_Empty_Ready_Check(arm_type) > 0)
					{
						NEXT__LOOP;
					}
				}
			}
		}
		// Arm : B ...
		if(VAC_RB__Check_Occupied__B_Arm() > 0)
		{
			arm_type = "B";
			
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				if(xCH_CFG__SCH_EXCHANGE_PRIORITY->Check__DATA(STR__PMC) > 0)
				{
					if(Fnc__PMC_Empty_Ready_Check(arm_type) > 0)
					{
						NEXT__LOOP;
					}
				}
			}
		}
	}

	// ...
	int active__sch_mode = -1;
	int active__sch_ll = -1;

	if(sEXT_CH__SCH_MODE_LLx_OUT->Check__DATA(_SCH_MODE__ROUTE) > 0)
	{
		CString check_arm = "";
		int i;

		for(i=0; i<2; i++)
		{
			if(i == 0)
			{
				if(VAC_RB__Check_Occupied__A_Arm() < 0)
					continue;

				check_arm = "A";
			}
			else if(i == 1)
			{
				if(VAC_RB__Check_Occupied__B_Arm() < 0)
					continue;

				check_arm = "B";
			}
			else
			{
				continue;
			}

			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(check_arm) > 0)
			{
				check_arm = "";
				continue;
			}

			break;
		}

		if(check_arm.GetLength() > 0)
		{
			CStringArray l_ll_id;
			CStringArray l_ll_mode;
			CStringArray l_ll_slot;

			xSCH_MATERIAL_CTRL->Get__LLx_OUT_OF_EDIT_TYPE(check_arm, l_ll_id,l_ll_mode,l_ll_slot);

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
		else
		{
			NEXT__LOOP;
		}
	}

	// ...
	int out_flag = -1;

	CString para_module;
	CString para_slot;

	// ...
	int lba_in_count = 0;
	int lbb_in_count = 0;

	// ...
	int ok_check = 1;

	if(xCH_CFG__SCH_PMC_RECIPE_TYPE->Check__DATA(STR__PRC_CLN) > 0)
	{
		ok_check = -1;	
	}

	// LLx : In_Count ...
	{
		CString var_data;

		int ll_limit = iLLx_LIMIT;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			xEXT_CH__LLx__IN_COUNT[ll_i]->Get__DATA(var_data);

				 if(ll_i == 0)		lba_in_count = atoi(var_data);
			else if(ll_i == 1)		lbb_in_count = atoi(var_data);
		}
	}

	if(active__sch_mode > 0)
	{
		// LLx ...
		if(active__sch_ll > 0)
		{
			int ll_i = active__sch_ll - 1;

				 if(ll_i == 0)		lbb_in_count = -1;
			else if(ll_i == 1)		lba_in_count = -1;

			if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") > 0)
			{
				if(xEXT_CH__ATM_RB__SCH_STS_TO_LLx[ll_i]->Check__DATA("") < 0)
				{
					NEXT__LOOP;
				}

				if((LLx__Is_Available(ll_i) > 0)
				&& (LLx__Is_ATM(ll_i) > 0))
				{
					int slot_id;

					if(LLx__Get_Empty__OutSlot(ll_i, slot_id) > 0)
					{
						para_module = Get__LLx_NAME(ll_i);
						para_slot.Format("%1d",slot_id);

						out_flag = 1;

						if(SCH_RUN__LLx_PUMP(ll_i, log_id, "") > 0)
						{
							xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
						}
						NEXT__LOOP;
					}
				}
			}
		}
	}
	else
	{
		int lba_in_flag = -1;
		int lbb_in_flag = -1;
	
		int lb_slotid;
		CString lb_sch_name;
		
		// LLx ...
		int ll_limit = iLLx_LIMIT;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(LLx__Get_Occupied__InSlot(ll_i, lb_slotid) > 0)
			{
				CString ll_name = Get__LLx_NAME(ll_i);
				lb_sch_name.Format("%s-%1d", ll_name,lb_slotid);

				if(Fnc__PMC_Empty_Ready_Check(lb_sch_name,1) > 0)
				{
						 if(ll_i == 0)		lba_in_flag = 1;
					else if(ll_i == 1)		lbb_in_flag = 1;
				}
			}
		}

		if((lba_in_flag > 0) && (lbb_in_flag < 0))
		{
			lbb_in_count = -1;
		}
		if((lba_in_flag < 0) && (lbb_in_flag > 0))
		{
			lba_in_count = -1;
		}
	}

	// ...
	int ll_a = _LLx_INDEX__LBA;
	int ll_b = _LLx_INDEX__LBB;

	if((lba_in_count > 0)&&(lbb_in_count > 0))
	{
		if(lba_in_count < lbb_in_count)
		{
			out_flag 
				= Fnc__Get_LLx__Empty_Out_Slot(p_variable,
											   p_alarm,
											   ok_check,
											   ll_a,
											   para_module,
											   para_slot);
		}
		else 
		{
			out_flag 
				= Fnc__Get_LLx__Empty_Out_Slot(p_variable,
											   p_alarm,
											   ok_check,
											   ll_b,
											   para_module,
											   para_slot);
		}
	}
	else if(lba_in_count > 0)
	{
		out_flag 
			= Fnc__Get_LLx__Empty_Out_Slot(p_variable,
										   p_alarm,
										   ok_check,
										   ll_a,
										   para_module,
										   para_slot);
	}
	else if(lbb_in_count > 0)
	{
		out_flag 
			= Fnc__Get_LLx__Empty_Out_Slot(p_variable,
										   p_alarm,
										   ok_check,
										   ll_b,
										   para_module,
										   para_slot);
	}

	if(active__sch_mode < 0)
	{
		if(out_flag < 0)
		{
			out_flag 
				= Fnc__Get_LLx__Empty_Out_Slot(p_variable,
											   p_alarm,
											   ok_check,
											   ll_a,
											   para_module,
											   para_slot);
		}
		if(out_flag < 0)
		{
			out_flag 
				= Fnc__Get_LLx__Empty_Out_Slot(p_variable,
											   p_alarm,
											   ok_check,
											   ll_b,
											   para_module,
											   para_slot);
		}
	}

	if(out_flag < 0)
	{
		NEXT__LOOP;
	}


	// ...
	bool ex_lb_flag = false;
	CString lb_in_slot;
	CString empty_arm;

	if(xCH_CFG__SCH_LLx_EXCHANGE_WHEN_PMC_EMPTY->Check__DATA(STR__ENABLE) > 0)
	{
		int ll_i = Get__LLx_INDEX(para_module);
		if(ll_i >= 0)
		{
			int lb_slotid;

			if(LLx__Get_Occupied__InSlot(ll_i, lb_slotid) > 0)
			{
				CString lb_sch_name;
				lb_sch_name.Format("%s-%1d", para_module,lb_slotid);

				if(Fnc__PMC_Empty_Ready_Check(lb_sch_name,1) > 0)
				{
					ex_lb_flag = true;
					lb_in_slot.Format("%1d", lb_slotid);
				}
			}
		}

		if(ex_lb_flag == true)
		{
			if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
			{
				ex_lb_flag = false;
			}
		}
	}
	else
	{
		int ll_i = Get__LLx_INDEX(para_module);
		if(ll_i >= 0)
		{
			int lb_slotid;

			if(LLx__Get_Occupied__InSlot(ll_i, lb_slotid) > 0)
			{
				ex_lb_flag = true;
				lb_in_slot.Format("%1d", lb_slotid);
			}
		}

		if(ex_lb_flag == true)
		{
			if(VAC_RB__Get_Empty__Arm_Type_From_LBx(empty_arm) < 0)
			{
				ex_lb_flag = false;
			}
		}
	}

	// ...
	CString arm_type;
	int i;

	for(i=0; i<2; i++)
	{
		if(i == 0)
		{
			if(VAC_RB__Check_Occupied__A_Arm() < 0)
			{
				continue;
			}

			arm_type = "A";
		}
		else if(i == 1)
		{
			if(VAC_RB__Check_Occupied__B_Arm() < 0)
			{
				continue;
			}

			arm_type = "B";
		}
		else
		{
			continue;
		}

		if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
		{
			continue;
		}

		/*
		// ...
		{
			IDS__SCH_MATERIAL_STATUS ds_info;
		
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info) < 0)
			{
				continue;
			}
			if(ds_info.sMATERIAL_STS != "PROCESSED")
			{
				continue;
			}
		}
		*/

		// ...
		CString sch_module;

		// ...
		{
			int act_flag  = -1;
			int move_flag = -1;

			sch_module.Format("%s-%s",para_module,para_slot);	

			act_flag = SCH__PLACE_MODULE(p_variable,p_alarm, log_id, ex_lb_flag,arm_type,para_module,para_slot,sch_module);

			// ...
			{
				CString log_msg;
				CString log_bff;

				log_msg.Format("%s ... \n", log_id);
				log_bff.Format("  SCH__PLACE_MODULE() : act_flag [%1d] \n", act_flag);
				log_msg += log_bff;
				log_bff.Format("  arm_type : [%s] \n", arm_type);
				log_msg += log_bff;
				log_bff.Format("  sch_module : [%s] \n", sch_module);
				log_msg += log_bff;
				log_bff.Format("  ex_lb_flag : [%1d] \n", ex_lb_flag);
				log_msg += log_bff;

				printf(" * %s \n", log_msg);
			}

			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Place(arm_type);
			}
			else
			{
				move_flag = 1;
			}

			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Place__To_MODULE(arm_type,sch_module);
			}

			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}

		if(ex_lb_flag == true)
		{
			int act_flag  = -1;
			int move_flag = -1;
			
			sch_module.Format("%s-%s",para_module,lb_in_slot);	

			act_flag = SCH__PICK_MODULE(p_variable,p_alarm, log_id, false,empty_arm,para_module,lb_in_slot,sch_module);
			
			if(act_flag < 0)
			{
				move_flag = SCH__Check_Material_Pick(empty_arm);
			}
			else
			{
				move_flag = 1;
			}
			
			if(move_flag > 0)
			{
				xSCH_MATERIAL_CTRL->Pick__From_MODULE(sch_module,empty_arm);
			}
			
			if(act_flag < 0)
			{
				NEXT__LOOP;
			}
		}

		// ...
		int ll_i = Get__LLx_INDEX(para_module);
		if(ll_i >= 0)
		{
			CString ll_name = Get__LLx_NAME(ll_i);

			int in_slot  = LLx__Check_Occupied__InSlot(ll_i);
			int out_slot = LLx__Check_Occupied__OutSlot(ll_i);

			// ...
			{
				CString log_msg;
				CString log_bff;

				log_msg.Format("AUTO_CTRL__RB_LBo__ALL_MODE() : %s-Venting ??? \n", ll_name);
				log_bff.Format("  in_slot  : [%1d] \n", in_slot);
				log_msg += log_bff;
				log_bff.Format("  out_slot : [%1d] \n", out_slot);
				log_msg += log_bff;

				printf(" * %s \n", log_msg);
			}

			if((LLx__Check_Occupied__InSlot(ll_i)  < 0)
			&& (LLx__Check_Occupied__OutSlot(ll_i) > 0))
			{
				printf(" * AUTO_CTRL__RB_LBo__ALL_MODE() : %s-Venting !!! \n", ll_name);

				if(SCH_RUN__LLx_VENT(ll_i, log_id, "1") > 0)
				{
					xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
				}
			}
		}

		NEXT__LOOP;
	}

	NEXT__LOOP;
}

void CObj_Fnc__DUAL_ARM_STD::AUTO_CTRL__FRONT_WAC_POS(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	if(xEXT_CH__SCH__WAC_WAFER_POSITION->Check__DATA(STR__PMx) > 0)
	{
		NEXT__LOOP;
	}
	if(VAC_RB__Check_All_Empty() > 0)
	{
		NEXT__LOOP;
	}

	// ...
	CString arm_type;

	//...
	{
		IDS__SCH_MATERIAL_STATUS ds_info;
		int pmi_flag = -1;
	
		if(pmi_flag < 0)
		{
			if(VAC_RB__Check_Occupied__A_Arm() > 0)
			{
				arm_type = "A";

				if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info) > 0)
				{
					if(ds_info.sMATERIAL_STS == "ALIGNED")		pmi_flag = 1;
				}
			}
		}
		if(pmi_flag < 0)
		{
			if(VAC_RB__Check_Occupied__B_Arm() > 0)
			{
				arm_type = "B";
	
				if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info) > 0)
				{
					if(ds_info.sMATERIAL_STS == "ALIGNED")		pmi_flag = 1;
				}	
			}
		}

		if(pmi_flag < 0)
		{
			NEXT__LOOP;
		}
	}

	//.....
	{
		CStringArray l_pmx;
		CStringArray l_rcp;

		if(xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type,l_pmx,l_rcp) < 0)
		{
			NEXT__LOOP;
		}

		//.....
		int pm_index;
		int material_check = -1;

		int limit = l_pmx.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			pm_index = SCH__CHECK_PM_INDEX(l_pmx[i]);
			if(pm_index < 0)
			{
				continue;
			}

			//.....
			if(PMx__Check_Empty__SlotStatus(pm_index) < 0)
			{
				if(PMx__Check_CtcInUse_Or_Standby(pm_index) > 0)
				{
					material_check = 1;
					break;
				}
			}

			//.....
			if(PMx__Is_Available(pm_index) < 0)
			{
				continue;
			}			
			if(PMx__Check_Empty__SlotStatus(pm_index) < 0)
			{
				continue;
			}

			return;
		}
	
		// ...		
		if(material_check < 0)
		{
			iFRONT_PMx_FLAG = 1;	
		}
		iFRONT_WAC_FLAG = 1;
		

		// ...
		{
			CString cur_pos;
			xCH__VAC_RB__TRG_ROTE->Get__DATA(cur_pos);

			if((cur_pos.CompareNoCase(MODULE__LBA) == 0)
			|| (cur_pos.CompareNoCase(MODULE__LBB) == 0))
			{
				return;
			}
		}

		// ...
		{
			CStringArray l_para;
			CString pos_name = MODULE__LBB;

			l_para.Add(arm_type);
			l_para.Add(pos_name);
			l_para.Add("1");

			pVAC_RB__OBJ_CTRL->Call__OBJ_MODE(CMMD__ROTATE,l_para);
		}
	}
}
void CObj_Fnc__DUAL_ARM_STD::AUTO_CTRL__FRONT_PMi(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	if(VAC_RB__Check_All_Empty() > 0)
	{
		NEXT__LOOP;
	}

	// ...
	CString arm_type;

	//...
	{
		IDS__SCH_MATERIAL_STATUS ds_info;
		int pmi_flag = -1;
	
		if(pmi_flag < 0)
		{
			if(VAC_RB__Check_Occupied__A_Arm() > 0)
			{
				arm_type = "A";

				if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info) > 0)
				{
					if(ds_info.sMATERIAL_STS == "ALIGNED")		pmi_flag = 1;
				}
			}
		}
		if(pmi_flag < 0)
		{
			if(VAC_RB__Check_Occupied__B_Arm() > 0)
			{
				arm_type = "B";
	
				if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(arm_type,ds_info) > 0)
				{
					if(ds_info.sMATERIAL_STS == "ALIGNED")		pmi_flag = 1;
				}	
			}
		}

		if(pmi_flag < 0)		NEXT__LOOP;
	}

	// ...
	{
		CStringArray l_pmx;
		CStringArray l_rcp;

		if(xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type,l_pmx,l_rcp) < 0)
		{
			NEXT__LOOP;
		}

		CString para_pm;
		int pm_index;
		int matreial_flag = -1;

		int limit = l_pmx.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			pm_index = SCH__CHECK_PM_INDEX(l_pmx[i]);
			if(pm_index < 0)
			{
				continue;
			}

			if(xCH__PMx__PROCESS_STATUS[pm_index]->Check__DATA("WAIT") < 0)
			{
				continue;
			}
			if(PMx__Check_Empty__SlotStatus(pm_index) < 0)
			{
				if(VAC_RB__Check_Empty__Arm_Type() < 0)
				{
					continue;
				}
			}

			//.....
			{
				para_pm = l_pmx[i];

				if(PMx__Check_Empty__SlotStatus(pm_index) < 0)
				{
					matreial_flag = 1;
				}
				else
				{
					matreial_flag = -1;
				}
			}
			break;
		}
	
		if(para_pm.GetLength() < 1)
		{
			NEXT__LOOP;
		}

		iFRONT_PMx_FLAG = 1;

		if(xCH__VAC_RB__TRG_ROTE->Check__DATA(para_pm) > 0)
		{
			NEXT__LOOP;
		}

		// ...
		CStringArray l_para;

		if(matreial_flag > 0)
		{
			if(VAC_RB__Get_Empty__Arm_Type_From_PMx(arm_type) < 0)
			{
				if(VAC_RB__Get_Empty__Arm_Type_From_All(arm_type) < 0)
				{
					NEXT__LOOP;
				}
			}
		}	
		
		l_para.Add(arm_type);
		l_para.Add(para_pm);
		l_para.Add("1");

		pVAC_RB__OBJ_CTRL->Call__OBJ_MODE(CMMD__ROTATE,l_para);
	}
}
void CObj_Fnc__DUAL_ARM_STD::AUTO_CTRL__FRONT_PMo(CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	//.....
	CString arm_type;

	if(SCH__LBi__CHECK_InSLOT_OCCUPIED() > 0)
	{
		NEXT__LOOP;
	}
	
	if(VAC_RB__Check_Empty__Dual_Arm() < 0)
	{
		NEXT__LOOP;
	}
	if(VAC_RB__Get_Empty__Arm_Type_From_PMx(arm_type) < 0)
	{
		NEXT__LOOP;
	}

	//.....
	{
		CString para_pm;
		int i;

		for(i=0;i<iPMx_SIZE;i++)
		{
			if(xCH__PMx__PROCESS_STATUS[i]->Check__DATA("WAIT") < 0)
			{
				continue;
			}

			para_pm.Format("PM%1d",i+1);
			break;
		}
	
		if(para_pm.GetLength() < 1)
		{
			NEXT__LOOP;
		}
		
		iFRONT_PMx_FLAG = 1;

		if(xCH__VAC_RB__TRG_ROTE->Check__DATA(para_pm) > 0)
		{
			NEXT__LOOP;
		}

		//.....
		CStringArray l_para;

		l_para.Add(arm_type);
		l_para.Add(para_pm);
		l_para.Add("1");

		pVAC_RB__OBJ_CTRL->Call__OBJ_MODE(CMMD__ROTATE,l_para);
	}
}

void CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__LLx_Exception_Proc1(CII_OBJECT__VARIABLE *p_variable,
							   CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	CString log_id = "AUTO_CTRL__LLx_Exception_Proc1()";

	// ...
	{
		int material_count = 0;
		int i;

		// PMx
		for(i=0;i<iPMx_SIZE;i++)
		{
			if((PMx__Check_CtcInUse_Or_Standby(i) > 0)
			&& (PMx__Check_Empty__SlotStatus(i)   < 0))
			{
				material_count++;
			}
		}	
		
		// Arm : A & B
		if(VAC_RB__Check_Occupied__A_Arm() > 0)
		{
			material_count++;
		}
		if(VAC_RB__Check_Occupied__B_Arm() > 0)
		{
			material_count++;
		}
		
		if(material_count < 1)
		{
			int ll_limit = iLLx_LIMIT;
			int ll_i;

			for(ll_i=0; ll_i<ll_limit; ll_i++)
			{
				if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
				{
			
				}
				else
				{
					CString ch_data;

					xEXT_CH__LLx__IDLE_COUNT[ll_i]->Get__DATA(ch_data);
					int i_count = atoi(ch_data);

					if(i_count >= 20)
					{
						if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("ATM") > 0)
						{
							if((LLx__Is_Available(ll_i) > 0)
							&& (LLx__Is_ATM(ll_i) < 0)
							&& (LLx__Check_All_Empty(ll_i) > 0))
							{
								if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") < 0)
								{
									if(SCH_RUN__LLx_VENT(ll_i, log_id, "1") > 0)
									{
										xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
									}
								}
							}
						}
						else
						{
							if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
							{
								if((LLx__Is_Available(ll_i) > 0)
								&& (LLx__Is_VAC(ll_i) < 0)
								&& (LLx__Check_All_Empty(ll_i) > 0))
								{
									// if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") < 0)
									{
										if(SCH_RUN__LLx_PUMP(ll_i, log_id, "2") > 0)
										{
											xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
										}
									}
								}
							}
							else
							{
								if((LLx__Is_Available(ll_i) > 0)
								&& (LLx__Is_ATM(ll_i) < 0)
								&& (LLx__Check_All_Empty(ll_i) > 0))
								{
									if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") < 0)
									{
										if(SCH_RUN__LLx_VENT(ll_i, log_id, "3") > 0)
										{
											xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
										}
									}
								}
							}
						}
					}
				}

				// ...
			}
		}
		else if(material_count < 2)
		{
			int lb_count = 0;

			int ll_limit = iLLx_LIMIT;
			int ll_i;

			for(ll_i=0; ll_i<ll_limit; ll_i++)
			{
				if((LLx__Is_Available(ll_i) > 0)
				&& (LLx__Is_ATM(ll_i) < 0)
				&& (LLx__Check_All_Empty(ll_i) > 0))
				{
					lb_count++;
				}
			}

			if(lb_count > 1)
			{
				int lb_check = -1;

				for(ll_i=0; ll_i<ll_limit; ll_i++)
				{
					if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
					{

					}
					else
					{
						CString ch_data;

						xEXT_CH__LLx__IDLE_COUNT[ll_i]->Get__DATA(ch_data);
						int i_count = atoi(ch_data);

						if(i_count >= 200)
						{
							if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("ATM") > 0)
							{
								if(lb_check < 0)
								{
									if((LLx__Is_Available(ll_i) > 0)
									&& (LLx__Is_ATM(ll_i) < 0)
									&& (LLx__Check_All_Empty(ll_i) > 0))
									{
										if(SCH_RUN__LLx_VENT(ll_i, log_id, "21") > 0)
										{
											xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
										}

										lb_check = 1;
									}
								}
							}
							else
							{
								if(lb_check < 0)
								{
									if((LLx__Is_Available(ll_i) > 0)
									&& (LLx__Is_VAC(ll_i) < 0)
									&& (LLx__Check_All_Empty(ll_i) > 0))
									{
										if(SCH_RUN__LLx_PUMP(ll_i, log_id, "22") > 0)
										{
											xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
										}

										lb_check = 1;
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

	// ...
	{
		int arm_wafer = -1;

		if(xCH_CFG__SCH_PMC_RECIPE_TYPE->Check__DATA(STR__PRC_CLN) > 0)
		{
			arm_wafer = 1;
		}
		else
		{
			if(VAC_RB__Check_Empty__Dual_Arm() < 0)
			{
				arm_wafer = 1;
			}
		}

		if(arm_wafer > 0)
		{
			int ll_limit = iLLx_LIMIT;
			int ll_i;

			for(ll_i=0; ll_i<ll_limit; ll_i++)
			{
				if(LLx__Is_Available(ll_i) > 0)
				{
					if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
					{

					}
					else if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
					{

					}
					else
					{
						CString sch_name;
						int lb_slot;

						if((LLx__Is_ATM(ll_i) < 0)
						&& (LLx__Check_Empty__InSlot(ll_i) > 0)
						&& (LLx__Get_Occupied__OutSlot(ll_i, lb_slot) > 0))
						{
							CString ll_name = Get__LLx_NAME(ll_i);
							sch_name.Format("%s-%1d", ll_name,lb_slot);

							// ...
							IDS__SCH_MATERIAL_STATUS ds_sts;
							
							if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(sch_name,ds_sts) > 0)
							{
								int port_id = ds_sts.iPORT_ID;
								int pump_req_flag = -1;

								if(xSCH_MATERIAL_CTRL->Check__MATERIAL_TO_PROCESS_WITH_PMC_IN_LPx(port_id) < 0)
								{
									pump_req_flag = 1;
								}
								else
								{
									int lb_in_slot;
									
									if(LLx__Get_Occupied__InSlot(ll_i, lb_in_slot) > 0)
									{
										CString sch_lb_name;
										sch_lb_name.Format("%s-%1d", ll_name,lb_in_slot);

										if(SCH__LBx_CAN_VENT(sch_lb_name) > 0)
										{
											pump_req_flag = 1;
										}
									}
								}

								if(pump_req_flag > 0)
								{
									if(SCH_RUN__LLx_VENT(ll_i, log_id, "41") > 0)
									{
										xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
									}
								}
							}

							// ...
						}
					}
				}
			}

			// ...
		}
	}

	/*
	// VAC Robot - Check ...
	{
		if(VAC_RB__Check_Empty__Arm_Type() > 0)
		{
			NEXT__LOOP;
		}

		// ...
		CString arm_type;

		int limit = 2;
		int i;

		for(i=0;i<limit;i++)
		{
			     if(i == 0)		arm_type = "A";
			else if(i == 1)		arm_type = "B";
			else				continue;

			// ...
			{
				CStringArray l_pmc;
				CStringArray l_rcp;

				xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(arm_type,l_pmc,l_rcp);

				// ...
				int pm_i;

				int k_limit = l_pmc.GetSize();
				int k;

				for(k=0;k<k_limit;k++)
				{
					pm_i = SCH__CHECK_PM_INDEX(l_pmc[k]);
					if(pm_i < 0)
					{
						continue;
					}

					if(PMx__Check_CtcInUse_Or_Standby(pm_i) < 0)
					{
						continue;
					}

					if(xEXT_CH__CFG__PMx_USE[pm_i]->Check__DATA(STR__ENABLE) < 0)
					{
						continue;
					}

					if(PMx__Check_Empty__SlotStatus(pm_i) < 0)
					{
						continue;
					}
					
					NEXT__LOOP;
				}
			}
		}
	}
	*/

	// ...
}

void CObj_Fnc__DUAL_ARM_STD::
AUTO_CTRL__LLx_Exception_Proc2(CII_OBJECT__VARIABLE *p_variable,
							   CII_OBJECT__ALARM *p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CString log_id = "AUTO_CTRL__LLx_Exception_Proc2()";
	
	if(VAC_RB__Is_Available() < 0)
	{
		NEXT__LOOP;
	}

	// LLx - Check ...
	{
		int check_flag = -1;

		int ll_limit = iLLx_LIMIT;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
			{
				if(LLx__Check_All_Empty(ll_i) > 0)
				{
					if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") < 0)		continue;
					if(LLx__Is_Available(ll_i) < 0)			continue;
					if(LLx__Is_VAC(ll_i) > 0)				continue;

					SCH_RUN__LLx_PUMP(ll_i, log_id, "12");
					continue;
				}

				// ...
				CString ll_name = Get__LLx_NAME(ll_i);
				int ll_slot = LLx__Check_Occupied__OutSlot(ll_i);

				CString sch_name;
				sch_name.Format("%s-%1d", ll_name,ll_slot);

				if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_name) > 0)
				{
					continue;
				}

				// ...
				check_flag = 1;

				if(LLx__Is_Available(ll_i) > 0)
				{
					if(LLx__Check_Empty__OutSlot(ll_i) < 0)
					{
						CString ch_data;

						xEXT_CH__LLx__IDLE_COUNT[ll_i]->Get__DATA(ch_data);
						int i_count = atoi(ch_data);

						if(i_count >= 20)
						{
							if(LLx__Is_ATM(ll_i) < 0)
							{
								SCH_RUN__LLx_VENT(ll_i, log_id, "1");

								xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
							}
						}
					}
				}
			}
		}

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
			{
				check_flag = 1;

				if((LLx__Check_Empty__InSlot(ll_i) < 0)
				&& (LLx__Is_Available(ll_i) > 0))
				{
					CString ch_data;

					xEXT_CH__LLx__IDLE_COUNT[ll_i]->Get__DATA(ch_data);
					int i_count = atoi(ch_data);

					if(i_count >= 20)
					{
						if(xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("OUT") > 0)
						{
							if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
							{
								if(LLx__Is_VAC(ll_i) < 0)
								{	
									SCH_RUN__LLx_PUMP(ll_i, log_id, "11");
								}
							}
						}
						else
						{
							if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("ATM") > 0)
							{
								if(LLx__Is_ATM(ll_i) > 0)		xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
							}
							else
							{
								if(LLx__Is_VAC(ll_i) > 0)		xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("OUT");
							}
						}
					}
				}
			}
		}

		if(check_flag > 0)
		{
			NEXT__LOOP;
		}
	}
	
	// Robot Arm - Check ...
	{
		CString arm_type;

		if(VAC_RB__Check_Occupied__A_Arm() > 0)
		{
			arm_type = STR__A;
	
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				NEXT__LOOP;
			}
		}
		else if(VAC_RB__Check_Occupied__B_Arm() > 0)
		{
			arm_type = STR__B;
		
			if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(arm_type) > 0)
			{
				NEXT__LOOP;
			}
		}
		else
		{
			NEXT__LOOP;
		}
	}

	// LLx - Check ...
	{
		int ll_limit = iLLx_LIMIT;
		int ll_i;

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(LLx__Is_Available(ll_i) > 0)
			{
				if((LLx__Is_VAC(ll_i) > 0)
				&& (LLx__Check_Empty__OutSlot(ll_i) > 0))
				{
					NEXT__LOOP;
				}
			}

			if(LLx__Check_CtcInUse_Or_Standby(ll_i) > 0)
			{
				if(xEXT_CH__LLx__VENTING_FLAG[ll_i]->Check__DATA(STR__YES) > 0)
				{
					NEXT__LOOP;
				}
			}
		}

		for(ll_i=0; ll_i<ll_limit; ll_i++)
		{
			if(LLx__Is_Available(ll_i) > 0)
			{
				if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
				{

				}
				else if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
				{

				}
				else
				{
					if((xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Check__DATA("IN") < 0)
					|| (LLx__Is_ATM(ll_i) < 0))
					{
						if((LLx__Check_Empty__InSlot(ll_i)     > 0)
						&& (LLx__Check_Occupied__OutSlot(ll_i) > 0))
						{
							SCH_RUN__LLx_VENT(ll_i, log_id, "31");

							xEXT_CH__LLx__IN_OUT_FLAG[ll_i]->Set__DATA("IN");
						}
					}
				}
			}
		}

		// ...
	}

	// ...
}

int  CObj_Fnc__DUAL_ARM_STD::SCH__LBx_CAN_VENT(const CString& sch_lbx_name)
{
	// ...
	CStringArray l_pmc_name;
	CStringArray l_pmc_rcp;
	
	xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_lbx_name,l_pmc_name,l_pmc_rcp);
	
	// ...
	int flag__lp_normal = 1;
	
	if(LPx__Get_Process_Type__Normal(sch_lbx_name,flag__lp_normal) < 0)
	{
		return -1;
	}

	// ...
	int pm_i;
	
	int limit = l_pmc_name.GetSize();
	int i;
	
	for(i=0;i<limit;i++)
	{
		pm_i = SCH__CHECK_PM_INDEX(l_pmc_name[i]);
		if(pm_i < 0)
		{
			continue;
		}
		
		if(Fnc__PMx_Empty_Ready_Check(flag__lp_normal,pm_i,0,1) > 0)
		{
			return -1;
		}
	}
	return 1;
}

int CObj_Fnc__DUAL_ARM_STD
::Check_Alarm__Scheduler_Config(CII_OBJECT__ALARM* p_alarm)
{
	// VAC Robot - Arm Check ...
	{
		// A & B Arm ...
		if((xCH__VAC_RB__CFG_A_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
		&& (xCH__VAC_RB__CFG_B_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0))
		{			
			int err_flag = -1;
			CString ch_data;

			if(err_flag > 0)
			{
				/*
				int alarm_id = ALID__PICK_ARM__CONFIG_ERROR;
				CString alm_msg;
				CString alm_bff;
				CString r_act;
				*/
			}	
		}

		// No Arm ...
		else if((xCH__VAC_RB__CFG_A_ARM_USE_MODE->Check__DATA(STR__ENABLE) < 0)
			 && (xCH__VAC_RB__CFG_B_ARM_USE_MODE->Check__DATA(STR__ENABLE) < 0))
		{
			CString ch_data;

			// ...
			{
				int alarm_id = ALID__NO_ARM__CONFIG_ERROR;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				//
				alm_msg  = "VAC Robot can not use any arm. \n";
				alm_msg += "Current ctc scheduler config setting \n";
				
				xCH__VAC_RB__CFG_A_ARM_USE_MODE->Get__DATA(ch_data);
				alm_bff.Format("   A Arm Use <- %s \n", ch_data);
				alm_msg += alm_bff;

				xCH__VAC_RB__CFG_B_ARM_USE_MODE->Get__DATA(ch_data);
				alm_bff.Format("   B Arm Use <- %s \n", ch_data);
				alm_msg += alm_bff;

				//
				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
			}	
		}
		
		// A Arm ...
		else if((xCH__VAC_RB__CFG_A_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
			 && (xCH__VAC_RB__CFG_B_ARM_USE_MODE->Check__DATA(STR__ENABLE) < 0))
		{
			int err_flag = -1;
			CString ch_data;

			if(err_flag < 0)
			{	
				xCH_CFG__PICK_ARM_TYPE_FROM_LBX->Get__DATA(ch_data);

				if((ch_data.CompareNoCase(STR__ALL) != 0)
				&& (ch_data.CompareNoCase(STR__A)   != 0))
				{
					err_flag = 1;
				}
			}
			if(err_flag < 0)
			{
				xCH_CFG__PICK_ARM_TYPE_FROM_PMC->Get__DATA(ch_data);

				if((ch_data.CompareNoCase(STR__ALL) != 0)
				&& (ch_data.CompareNoCase(STR__B)   != 0))
				{
					err_flag = 1;
				}
			}

			if(err_flag > 0)
			{
				int alarm_id = ALID__A_ARM__CONFIG_ERROR;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				//
				alm_msg = "Current VAC Robot's Arm Config state. \n";
							
				xCH__VAC_RB__CFG_A_ARM_USE_MODE->Get__DATA(ch_data);
				alm_bff.Format("   A Arm Use <- %s \n", ch_data);
				alm_msg += alm_bff;

				xCH_CFG__PICK_ARM_TYPE_FROM_LBX->Get__DATA(ch_data);
				alm_bff.Format("   Pick Arm Type From LBx <- %s \n", ch_data);
				alm_msg += alm_bff;

				xCH_CFG__PICK_ARM_TYPE_FROM_PMC->Get__DATA(ch_data);
				alm_bff.Format("   Pick Arm Type From PMC <- %s \n", ch_data);
				alm_msg += alm_bff;

				alm_msg += "If you use only A-Arm, \n";
				alm_msg += "   Pick Arm Type From LBx is \"ALL\" or \"A\". \n";
				alm_msg += "   Pick Arm Type From PMC is \"ALL\" or \"A\". \n";

				//
				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
			}
		}

		// B Arm ...
		else if((xCH__VAC_RB__CFG_A_ARM_USE_MODE->Check__DATA(STR__ENABLE) < 0)
			 && (xCH__VAC_RB__CFG_B_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0))
		{
			int err_flag = -1;
			CString ch_data;
						
			if(err_flag < 0)
			{	
				xCH_CFG__PICK_ARM_TYPE_FROM_LBX->Get__DATA(ch_data);
							
				if((ch_data.CompareNoCase(STR__ALL) != 0)
				&& (ch_data.CompareNoCase(STR__B)   != 0))
				{
					err_flag = 1;
				}
			}
			if(err_flag < 0)
			{
				xCH_CFG__PICK_ARM_TYPE_FROM_PMC->Get__DATA(ch_data);
							
				if((ch_data.CompareNoCase(STR__ALL) != 0)
				&& (ch_data.CompareNoCase(STR__B)   != 0))
				{
					err_flag = 1;
				}
			}
						
			if(err_flag > 0)
			{
				int alarm_id = ALID__B_ARM__CONFIG_ERROR;
				CString alm_msg;
				CString alm_bff;
				CString r_act;
							
				//
				alm_msg = "Current VAC Robot's Arm Config state. \n";
							
				xCH__VAC_RB__CFG_B_ARM_USE_MODE->Get__DATA(ch_data);
				alm_bff.Format("   B Arm Use <- %s \n", ch_data);
				alm_msg += alm_bff;
							
				xCH_CFG__PICK_ARM_TYPE_FROM_LBX->Get__DATA(ch_data);
				alm_bff.Format("   Pick Arm Type From LBx <- %s \n", ch_data);
				alm_msg += alm_bff;
							
				xCH_CFG__PICK_ARM_TYPE_FROM_PMC->Get__DATA(ch_data);
				alm_bff.Format("   Pick Arm Type From PMC <- %s \n", ch_data);
				alm_msg += alm_bff;
							
				alm_msg += "If you use only B-Arm, \n";
				alm_msg += "   Pick Arm Type From LBx is \"ALL\" or \"B\". \n";
				alm_msg += "   Pick Arm Type From PMC is \"ALL\" or \"B\". \n";
							
				//
				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);							
			}
		}
	}	

	return 1;
}

