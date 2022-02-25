#include "StdAfx.h"
#include "CObj_Fnc__SINGLE_ARM_STD.h"


// ...
MODULE__IS_AVAILABLE(CObj_Fnc__SINGLE_ARM_STD, ATM_RB, xCH__ATM_RB__OBJ_STATUS,xCH__ATM_RB__OBJ_CTRL);
MODULE__IS_AVAILABLE(CObj_Fnc__SINGLE_ARM_STD, AL1, xCH__AL1__OBJ_STATUS,xCH__AL1__OBJ_CTRL);

MODULEx__IS_AVAILABLE_WITH_USE_INDEX(CObj_Fnc__SINGLE_ARM_STD, LLx, xEXT_CH__LLx__OBJ_STATUS,xEXT_CH__LLx__OBJ_CTRL,xEXT_CH__SCH_DB_LLx_USE_FLAG);
MODULEx__IS_AVAILABLE(CObj_Fnc__SINGLE_ARM_STD,LPx,xCH__LPx__OBJ_STATUS,xCH__LPx__OBJ_CTRL);

// ...
MODULE__SET_OBJ_STATUS(CObj_Fnc__SINGLE_ARM_STD,ATM_RB,xCH__ATM_RB__OBJ_STATUS);
MODULE__SET_OBJ_STATUS(CObj_Fnc__SINGLE_ARM_STD,AL1, xCH__AL1__OBJ_STATUS);

MODULEx__SET_OBJ_STATUS_WITH_INDEX(CObj_Fnc__SINGLE_ARM_STD, LLx, xEXT_CH__LLx__OBJ_STATUS);
MODULEx__SET_OBJ_STATUS(CObj_Fnc__SINGLE_ARM_STD, LPx, xCH__LPx__OBJ_STATUS);

//.....
MODULEx__IS_ATM_WITH_INDEX(CObj_Fnc__SINGLE_ARM_STD, LLx, xEXT_CH__LLx__PRESSURE_STATUS);
MODULEx__IS_VAC_WITH_INDEX(CObj_Fnc__SINGLE_ARM_STD, LLx, xEXT_CH__LLx__PRESSURE_STATUS);


//---------------------------------------------------------------------------------------
int  CObj_Fnc__SINGLE_ARM_STD:: 
LPx__Check_Occupied__Slot_Status(const int lp_id,const int slot_id)
{
	//.....
	int lp_i = lp_id - 1;

	if(lp_i <  0)						return -1;
	if(lp_i >= CFG_LP_LIMIT)			return -1;

	//.....
	int slot_i = slot_id - 1;

	if(slot_i <  0)						return -1;
	if(slot_i >= CFG_LP__SLOT_MAX)		return -1;

	//.....
	{
		if(xCH__LPx__PORT_STATUS[lp_i]->Check__DATA("BUSY") < 0)			return -11;
		if(xCH__LPx__CST_STATUS[lp_i]->Check__DATA("EXIST") < 0)			return -12;
		if(xCH__LPx__SLOT_STATUS[lp_i][slot_i]->Check__DATA("NONE") > 0)	return -13;
	}

	return 1;
}
int  CObj_Fnc__SINGLE_ARM_STD:: 
LPx__Check_Empty__Slot_Status(const int lp_id,const int slot_id)
{
	//.....
	int lp_i = lp_id - 1;

	if(lp_i <  0)						return -1;
	if(lp_i >= CFG_LP_LIMIT)			return -1;

	//.....
	int slot_i = slot_id - 1;

	if(slot_i <  0)						return -1;
	if(slot_i >= CFG_LP__SLOT_MAX)		return -1;

	//.....
	{
		CString var_Data;

		// ...
		{
			xCH__LPx__PORT_STATUS[lp_i]->Get__DATA(var_Data);

			if((var_Data.CompareNoCase("BUSY")   != 0)
				&& (var_Data.CompareNoCase("PAUSED") != 0))
			{
				return -11;
			}
		}

		if(xCH__LPx__CST_STATUS[lp_i]->Check__DATA("EXIST") < 0)			return -11;
		if(xCH__LPx__SLOT_STATUS[lp_i][slot_i]->Check__DATA("NONE") < 0)	return -12;
	}

	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
Fnc__GET_DUMMY_PORT()
{
	int i;

	for(i=0;i<iLPx_SIZE;i++)
	{
		if(xCH__LPx__CFG_USE_TYPE[i]->Check__DATA(STR__DUMMY) < 0)
		{
			continue;
		}

		return (i + 1);
	}
	return -1;
}


//---------------------------------------------------------------------------------------
int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Check_Venting(const int ll_index)
{
	CString obj_ctrl;
	CString obj_mode;
	CString obj_sts;

	xEXT_CH__LLx__OBJ_CTRL[ll_index]->Get__DATA(obj_ctrl);
	xEXT_CH__LLx__OBJ_MODE[ll_index]->Get__DATA(obj_mode);
	xEXT_CH__LLx__OBJ_STATUS[ll_index]->Get__DATA(obj_sts);

	if((obj_sts.CompareNoCase("STANDBY")  != 0)
	&& (obj_sts.CompareNoCase("CTCINUSE") != 0))
	{
		return -1;
	}
	if(obj_ctrl.CompareNoCase("RUN") != 0)
	{
		return -1;
	}
	if(obj_mode.CompareNoCase("VENT") != 0)
	{
		return -1;
	}

	return 1;
}

// ...
CString CObj_Fnc__SINGLE_ARM_STD::
Get__LLx_NAME(const int ll_index)
{
	if(ll_index == _LLx_INDEX__LBA)			return MODULE__LBA;
	if(ll_index == _LLx_INDEX__LBB)			return MODULE__LBB;
	if(ll_index == _LLx_INDEX__LBC)			return MODULE__LBC;
	if(ll_index == _LLx_INDEX__LBD)			return MODULE__LBD;

	return MODULE__LBX;
}
int CObj_Fnc__SINGLE_ARM_STD::
Get__LLx_INDEX(const CString& ll_name)
{
	int i_limit = iLLx_SIZE;
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_name = Get__LLx_NAME(i);

		if(str_name.CompareNoCase(ll_name) == 0)
			return i;
	}
	return -1;
}

void CObj_Fnc__SINGLE_ARM_STD::
LLx__Update_PRESSURE(const int ll_index)
{
	CString var_data;

	xEXT_CH__CFG__REF_ATM_PRESSURE->Get__DATA(var_data);
	double ref_atm_press = atof(var_data);

	xEXT_CH__CFG__REF_VAC_PRESSURE->Get__DATA(var_data);
	double ref_vac_press = atof(var_data);

	xEXT_CH__LLx__PRESSURE_VALUE[ll_index]->Get__DATA(var_data);
	double cur_press = atof(var_data);

	if(cur_press <= ref_vac_press)
	{
		xEXT_CH__LLx__PRESSURE_STATUS[ll_index]->Set__DATA("VAC");
	}
	else if(cur_press >= ref_atm_press)
	{
		xEXT_CH__LLx__PRESSURE_STATUS[ll_index]->Set__DATA("ATM");
	}
	else
	{
		xEXT_CH__LLx__PRESSURE_STATUS[ll_index]->Set__DATA("BTW");
	}
}


//---------------------------------------------------------------------------------------
int  CObj_Fnc__SINGLE_ARM_STD::
Set__TMC_CtcInUse_To_Standby()
{
	int i;

	// ...
	{
		ATM_RB__Set_CtcInUse_To_Standby();
		AL1__Set_CtcInUse_To_Standby();
	}

	// LLx ...
	{
		for(i=0; i<iLLx_SIZE; i++)
		{
			LLx__Set_CtcInUse_To_Standby(i);
		}
	}

	// LPx ...
	{
		for(i=0; i<iLPx_SIZE; i++)
		{
			LPx__Set_CtcInUse_To_Standby(i);
		}
	}

	return 1;
}

//---------------------------------------------------------------------------------------
int  CObj_Fnc__SINGLE_ARM_STD::
AL1__Check_Empty__All_Slot()
{
	int flag = -1;

	if(xEXT_CH__SCH_DB_AL1_SLOT01_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__AL1__SLOT01_STATUS->Check__DATA(SLOT_STS__NONE) < 0)
		{
			return -1;
		}

		flag = 1;
	}
	if(xEXT_CH__SCH_DB_AL1_SLOT02_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__AL1__SLOT02_STATUS->Check__DATA(SLOT_STS__NONE) < 0)
		{
			return -1;
		}

		flag = 1;
	}

	return flag;
}

int  CObj_Fnc__SINGLE_ARM_STD::
AL1__Get_Empty__SlotID(int& slot_id)
{
	if(xEXT_CH__SCH_DB_AL1_SLOT01_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__AL1__SLOT01_STATUS->Check__DATA(SLOT_STS__NONE) > 0)
		{
			slot_id = 1;
			return 1;
		}
	}
	if(xEXT_CH__SCH_DB_AL1_SLOT02_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__AL1__SLOT02_STATUS->Check__DATA(SLOT_STS__NONE) > 0)
		{
			slot_id = 2;
			return 1;
		}
	}

	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
AL1__Get_Occupied__SlotID(int& slot_id)
{
	if(xEXT_CH__SCH_DB_AL1_SLOT01_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__AL1__SLOT01_STATUS->Check__DATA(SLOT_STS__NONE) < 0)
		{
			slot_id = 1;
			return 1;
		}
	}
	if(xEXT_CH__SCH_DB_AL1_SLOT02_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__AL1__SLOT02_STATUS->Check__DATA(SLOT_STS__NONE) < 0)
		{
			slot_id = 2;
			return 1;
		}
	}

	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD:: 
AL1__Get_Occupied__Total_Count()
{
	int count = 0;

	if(xEXT_CH__SCH_DB_AL1_SLOT01_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__AL1__SLOT01_STATUS->Check__DATA(SLOT_STS__NONE) < 0)
		{
			count++;
		}
	}
	if(xEXT_CH__SCH_DB_AL1_SLOT02_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__AL1__SLOT02_STATUS->Check__DATA(SLOT_STS__NONE) < 0)
		{
			count++;
		}
	}

	return count;
}

int  CObj_Fnc__SINGLE_ARM_STD::
AL1__Check_Occupied__SlotStatus(const int slot_id)
{
	switch(slot_id)
	{
		case 1:
			if(xEXT_CH__SCH_DB_AL1_SLOT01_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
			{
				if(xCH__AL1__SLOT01_STATUS->Check__DATA(SLOT_STS__NONE) < 0)
				{
					return 1;
				}
			}
			return -1;

		case 2:
			if(xEXT_CH__SCH_DB_AL1_SLOT02_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
			{
				if(xCH__AL1__SLOT02_STATUS->Check__DATA(SLOT_STS__NONE) < 0)
				{
					return 1;
				}
			}
			return -1;
	}

	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
AL1__Check_Occupied__SlotStatus(const int slot_id,CString& title)
{
	switch(slot_id)
	{
		case 1:
			if(xEXT_CH__SCH_DB_AL1_SLOT01_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
			{
				if(xCH__AL1__SLOT01_STATUS->Check__DATA(SLOT_STS__NONE) < 0)
				{
					xCH__AL1__SLOT01_TITLE->Get__DATA(title);
					return 1;
				}
			}
			return -1;

		case 2:
			if(xEXT_CH__SCH_DB_AL1_SLOT02_USE_FLAG->Check__DATA(STR__ENABLE) > 0)
			{
				if(xCH__AL1__SLOT02_STATUS->Check__DATA(SLOT_STS__NONE) < 0)
				{
					xCH__AL1__SLOT02_TITLE->Get__DATA(title);
					return 1;
				}
			}
			return -1;
	}

	return -1;
}


//---------------------------------------------------------------------------------------
int  CObj_Fnc__SINGLE_ARM_STD::
ATM_RB__Check_Empty__Arm_Type()
{
	if(xCH__ATM_RB__CFG_A_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__ATM_RB__SLOT01_STATUS->Check__DATA(SLOT_STS__NONE) > 0)			return 1;
	}
	else if(xCH__ATM_RB__CFG_B_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__ATM_RB__SLOT02_STATUS->Check__DATA(SLOT_STS__NONE) > 0)			return 1;
	}

	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
ATM_RB__Check_Occupied__Arm_Type()
{
	if(xCH__ATM_RB__CFG_A_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__ATM_RB__SLOT01_STATUS->Check__DATA(SLOT_STS__NONE) < 0)			return 1;
	}
	else if(xCH__ATM_RB__CFG_B_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__ATM_RB__SLOT02_STATUS->Check__DATA(SLOT_STS__NONE) < 0)			return 1;
	}

	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
ATM_RB__Get_Empty__Arm_Type(CString& arm_type)
{
	if(xCH__ATM_RB__CFG_A_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__ATM_RB__SLOT01_STATUS->Check__DATA(SLOT_STS__NONE) > 0)
		{
			arm_type = "A";
			return 1;
		}
	}
	else if(xCH__ATM_RB__CFG_B_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__ATM_RB__SLOT02_STATUS->Check__DATA(SLOT_STS__NONE) > 0)
		{
			arm_type = "B";
			return 1;
		}
	}

	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
ATM_RB__Get_Occupied__Arm_Type(CString& arm_type)
{
	if(xCH__ATM_RB__CFG_A_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__ATM_RB__SLOT01_STATUS->Check__DATA(SLOT_STS__NONE) < 0)
		{
			arm_type = STR__A;
			return 1;
		}
	}
	else if(xCH__ATM_RB__CFG_B_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__ATM_RB__SLOT02_STATUS->Check__DATA(SLOT_STS__NONE) < 0)
		{
			arm_type = STR__B;
			return 1;
		}
	}

	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
ATM_RB__Get_Occupied__Wfr_Title_Of_Arm_Type(const CString& arm_type, CString& wfr_title)
{
	if(arm_type.CompareNoCase(STR__A) == 0)
	{
		if(xCH__ATM_RB__CFG_A_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
		{
			if(xCH__ATM_RB__SLOT01_STATUS->Check__DATA(SLOT_STS__NONE) > 0)		return -1;
	
			xCH__ATM_RB__SLOT01_TITLE->Get__DATA(wfr_title);
			return 1;
		}
	}
	else if(arm_type.CompareNoCase(STR__B) == 0)
	{
		if(xCH__ATM_RB__CFG_B_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
		{
			if(xCH__ATM_RB__SLOT02_STATUS->Check__DATA(SLOT_STS__NONE) > 0)		return -1;

			xCH__ATM_RB__SLOT02_TITLE->Get__DATA(wfr_title);
			return 1;
		}
	}

	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
ATM_RB__Check_Occupied__Wfr_Title_Of_Arm_Type(CString& wfr_title)
{
	if(xCH__ATM_RB__CFG_A_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__ATM_RB__SLOT01_STATUS->Check__DATA(SLOT_STS__NONE) > 0)		return -1;

		xCH__ATM_RB__SLOT01_TITLE->Get__DATA(wfr_title);
		return 1;
	}
	else if(xCH__ATM_RB__CFG_B_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__ATM_RB__SLOT02_STATUS->Check__DATA(SLOT_STS__NONE) > 0)		return -1;

		xCH__ATM_RB__SLOT02_TITLE->Get__DATA(wfr_title);
		return 1;
	}

	return -1;
}

//---------------------------------------------------------------------------------------
int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Check_All_Empty(const int ll_index)
{
	int slot_max = iLLx_SLOT_MAX[ll_index];
	int i;

	for(i=0; i<slot_max; i++)
	{
		if(xEXT_CH__SCH_DB_LLx_SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__ENABLE) < 0)
		{
			continue;
		}

		if(xEXT_CH__LLx__SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__NONE) < 0)
		{
			return -1;
		}
	}
	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Check_Empty__SlotStatus(const int ll_index,const int slot_id)
{
	int slot_max = iLLx_SLOT_MAX[ll_index];
	int slot_index = slot_id - 1;

	if(slot_index <  0)					return -1;
	if(slot_index >= slot_max)			return -1;

	if(xEXT_CH__LLx__SLOT_STATUS[ll_index][slot_index]->Check__DATA(SLOT_STS__NONE) < 0)
	{
		return -1;
	}
	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Check__Slot_Enable(const int ll_index,const int slot_id)
{
	int slot_max = iLLx_SLOT_MAX[ll_index];
	int slot_index = slot_id - 1;

	if(slot_index <  0)					return -1;
	if(slot_index >= slot_max)			return -1;

	if(xEXT_CH__SCH_DB_LLx_SLOT_STATUS[ll_index][slot_index]->Check__DATA(SLOT_STS__ENABLE) < 0)
	{
		return -1;
	}
	return 1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Get_Empty__Total_InSlot(const int ll_index)
{
	if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
	{
		return -1;
	}

	// ...
	int count = 0;

	int slot_max = iLLx_SLOT_MAX[ll_index];
	int i;

	for(i=0; i<slot_max; i++)
	{
		if(xEXT_CH__SCH_DB_LLx_SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__ENABLE) < 0)
		{
			continue;
		}

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ALL) > 0)
		{
			CString ch_data = xEXT_CH__SCH_DB_LLx_SLOT_MODE[ll_index][i]->Get__STRING();

			if((ch_data.CompareNoCase(SLOT_STS__INPUT) != 0)
			&& (ch_data.CompareNoCase(SLOT_STS__ALL)   != 0))
			{
				continue;
			}
		}

		if(xEXT_CH__LLx__SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__NONE) > 0)
		{
			count++;
		}
	}
	return count;
}

int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Get_Empty__InSlot(const int ll_index,int& slot_id)
{
	if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
	{
		return -1;
	}

	// ...
	int slot_max = iLLx_SLOT_MAX[ll_index];
	int i;

	for(i=0; i<slot_max; i++)
	{
		if(xEXT_CH__SCH_DB_LLx_SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__ENABLE) < 0)
		{
			continue;
		}

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ALL) > 0)
		{
			CString ch_data = xEXT_CH__SCH_DB_LLx_SLOT_MODE[ll_index][i]->Get__STRING();

			if((ch_data.CompareNoCase(SLOT_STS__INPUT) != 0)
			&& (ch_data.CompareNoCase(SLOT_STS__ALL)   != 0))
			{
				continue;
			}
		}

		if(xEXT_CH__LLx__SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__NONE) > 0)
		{
			slot_id = i + 1;
			return 1;
		}
	}
	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Get_Occupied__InSlot(const int ll_index,int& slot_id)
{
	if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
	{
		return -1;
	}

	// ...
	int slot_max = iLLx_SLOT_MAX[ll_index];
	int i;

	for(i=0; i<slot_max; i++)
	{
		if(xEXT_CH__SCH_DB_LLx_SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__ENABLE) < 0)
		{
			continue;
		}

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ALL) > 0)
		{
			CString ch_data = xEXT_CH__SCH_DB_LLx_SLOT_MODE[ll_index][i]->Get__STRING();

			if((ch_data.CompareNoCase(SLOT_STS__INPUT) != 0)
			&& (ch_data.CompareNoCase(SLOT_STS__ALL)   != 0))
			{
				continue;
			}
		}

		if(xEXT_CH__LLx__SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__NONE) < 0)
		{
			slot_id = i + 1;
			return 1;
		}
	}
	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Check_Empty__InSlot(const int ll_index)
{
	if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
	{
		return -1;
	}

	// ...
	int slot_max = iLLx_SLOT_MAX[ll_index];
	int i;

	for(i=0; i<slot_max; i++)
	{
		if(xEXT_CH__SCH_DB_LLx_SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__ENABLE) < 0)
		{
			continue;
		}

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ALL) > 0)
		{
			CString ch_data = xEXT_CH__SCH_DB_LLx_SLOT_MODE[ll_index][i]->Get__STRING();

			if((ch_data.CompareNoCase(SLOT_STS__INPUT) != 0)
			&& (ch_data.CompareNoCase(SLOT_STS__ALL)   != 0))
			{
				continue;
			}
		}

		if(xEXT_CH__LLx__SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__NONE) > 0)
		{
			int slot_id = i + 1;
			return slot_id;
		}
	}
	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Get_Occupied__Total_OutSlot(const int ll_index)
{
	if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
	{
		return -1;
	}

	// ...
	int count = 0;

	int i_limit = iLLx_SLOT_MAX[ll_index];
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(xEXT_CH__SCH_DB_LLx_SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__ENABLE) < 0)
		{
			continue;
		}

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ALL) > 0)
		{
			CString ch_data = xEXT_CH__SCH_DB_LLx_SLOT_MODE[ll_index][i]->Get__STRING();

			if((ch_data.CompareNoCase(SLOT_STS__OUTPUT) != 0)
			&& (ch_data.CompareNoCase(SLOT_STS__ALL)    != 0))
			{
				continue;
			}
		}

		if(xEXT_CH__LLx__SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__NONE) < 0)
		{
			count++;
		}
	}
	return count;
}

int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Get_Occupied__Total_InSlot(const int ll_index,const int prc_check)
{
	if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
	{
		return -1;
	}

	// ...
	int count = 0;

	int i_limit = iLLx_SLOT_MAX[ll_index];
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(xEXT_CH__SCH_DB_LLx_SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__ENABLE) < 0)
		{
			continue;
		}

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ALL) > 0)
		{
			CString ch_data = xEXT_CH__SCH_DB_LLx_SLOT_MODE[ll_index][i]->Get__STRING();

			if((ch_data.CompareNoCase(SLOT_STS__INPUT) != 0)
			&& (ch_data.CompareNoCase(SLOT_STS__ALL)   != 0))
			{
				continue;
			}
		}

		if(xEXT_CH__LLx__SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__NONE) < 0)
		{
			if(prc_check > 0)
			{
				IDS__SCH_MATERIAL_STATUS ds_info;

				CString lb_sch_name;
				int lb_in_slotid = i + 1;

				CString ll_name = Get__LLx_NAME(ll_index);
				lb_sch_name.Format("%s-%1d", ll_name,lb_in_slotid);

				if(xSCH_MATERIAL_CTRL->Get__MATERIAL_STATUS(lb_sch_name,ds_info) > 0)
				{
					count++;		
				}
			}
			else
			{
				count++;
			}
		}
	}
	return count;
}

int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Check_Occupied__OutSlot(const int ll_index,const int slot_index)
{
	if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
	{
		return -1;
	}

	// ...
	int slot_size = iLLx_SLOT_MAX[ll_index];

	if(slot_index <  0)					return -1;
	if(slot_index >= slot_size)			return -1;

	if(xEXT_CH__SCH_DB_LLx_SLOT_STATUS[ll_index][slot_index]->Check__DATA(SLOT_STS__ENABLE) < 0)
	{
		return -1;
	}

	if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ALL) > 0)
	{
		CString ch_data = xEXT_CH__SCH_DB_LLx_SLOT_MODE[ll_index][slot_index]->Get__STRING();

		if(ch_data.CompareNoCase(SLOT_STS__OUTPUT) != 0)
		{
			if(ch_data.CompareNoCase(SLOT_STS__ALL) == 0)
			{
				CString sch_name;
				CString ll_name = Get__LLx_NAME(ll_index);

				sch_name.Format("%s-%1d", ll_name,slot_index+1);

				if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_name) > 0)
				{
					return -1;
				}
			}
			else
			{
				return -1;
			}
		}
	}

	if(xEXT_CH__LLx__SLOT_STATUS[ll_index][slot_index]->Check__DATA(SLOT_STS__NONE) < 0)
	{
		return  1;
	}
	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Check_Occupied__InSlot(const int ll_index)
{
	if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
	{
		return -1;
	}

	// ...
	int i_limit = iLLx_SLOT_MAX[ll_index];
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(xEXT_CH__SCH_DB_LLx_SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__ENABLE) < 0)
		{
			continue;
		}

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ALL) > 0)
		{
			CString ch_data = xEXT_CH__SCH_DB_LLx_SLOT_MODE[ll_index][i]->Get__STRING();

			if(ch_data.CompareNoCase(SLOT_STS__INPUT) != 0)
			{
				if(ch_data.CompareNoCase(SLOT_STS__ALL) == 0)
				{
					CString sch_name;
					CString ll_name = Get__LLx_NAME(ll_index);

					sch_name.Format("%s-%1d", ll_name,i+1);

					if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_name) < 0)
					{
						continue;
					}
				}
				else
				{
					continue;
				}
			}
		}

		if(xEXT_CH__LLx__SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__NONE) < 0)
		{
			return  1;
		}
	}
	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Get_Occupied__OutSlot(const int ll_index,int& slot_id)
{
	if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
	{
		return -1;
	}

	// ...
	int i_limit = iLLx_SLOT_MAX[ll_index];
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(xEXT_CH__SCH_DB_LLx_SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__ENABLE) < 0)
		{
			continue;
		}

		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ALL) > 0)
		{
			CString ch_data = xEXT_CH__SCH_DB_LLx_SLOT_MODE[ll_index][i]->Get__STRING();

			if(ch_data.CompareNoCase(SLOT_STS__OUTPUT) != 0)
			{
				if(ch_data.CompareNoCase(SLOT_STS__INPUT) == 0)
				{
					continue;
				}
				else if(ch_data.CompareNoCase(SLOT_STS__ALL) == 0)
				{
					CString sch_name;
					CString ll_name = Get__LLx_NAME(ll_index);

					sch_name.Format("%s-%1d", ll_name,i+1);

					if(xSCH_MATERIAL_CTRL->Check__NEXT_PROCESS(sch_name) > 0)
					{
						continue;
					}
				}
			}
		}

		if(xEXT_CH__LLx__SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__NONE) < 0)
		{
			slot_id = i + 1;
			return 1;
		}
	}
	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Get_Occupied__Only_Output(const int ll_index,CUIntArray& l_slot_id)
{
	l_slot_id.RemoveAll();

	if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_index]->Check__DATA(LBx_MODE__ONLY_OUTPUT) < 0)
	{
		return -1;
	}

	// ...
	int i_limit = iLLx_SLOT_MAX[ll_index];

	for(int i=0; i<i_limit; i++)
	{
		if(xEXT_CH__SCH_DB_LLx_SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__ENABLE) < 0)
		{
			continue;
		}

		if(xEXT_CH__LLx__SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__NONE) < 0)
		{
			int slot_id = i + 1;
			l_slot_id.Add(slot_id);
		}
	}
	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Get_Occupied__Slot(const int ll_index, int& slot_id,CString& title)
{
	int i_limit = iLLx_SLOT_MAX[ll_index];
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(xEXT_CH__SCH_DB_LLx_SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__ENABLE) < 0)		continue;
		if(xEXT_CH__LLx__SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__NONE) > 0)				continue;

		slot_id = i + 1;
		xEXT_CH__LLx__SLOT_TITLE[ll_index][i]->Get__DATA(title);
		return 1;
	}
	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
LLx__Get_Occupied__TotalSlot(const int ll_index)
{
	int count = 0;

	int i_limit = iLLx_SLOT_MAX[ll_index];
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(xEXT_CH__SCH_DB_LLx_SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__ENABLE) < 0)
		{
			continue;
		}

		if(xEXT_CH__LLx__SLOT_STATUS[ll_index][i]->Check__DATA(SLOT_STS__NONE) < 0)
		{
			count++;
		}
	}
	return count;
}


//---------------------------------------------------------------------------------------
int  CObj_Fnc__SINGLE_ARM_STD::
Buffer1__Get_Occupied__Slot(int& slot_id,CString& title)
{
	CString var_data;
	xEXT_CH__BUFFER1__CFG_SLOT_MAX->Get__DATA(var_data);

	int slot_size = atoi(var_data);
	int i;

	if(xCH__SCH_DB_ST1_WAFER_PICK_MODE->Check__DATA(STR__BOTTOM_TO_UP) > 0)
	{
		for(i=0;i<slot_size;i++)
		{
			if(xEXT_CH__BUFFER1__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				continue;
			}

			// ...
			{
				slot_id = i + 1;
				xEXT_CH__BUFFER1__SLOT_TITLE[i]->Get__DATA(title);
			}
			return 1;
		}
	}
	else
	{
		for(i=slot_size-1;i>=0;i--)
		{
			if(xEXT_CH__BUFFER1__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				continue;
			}

			// ...
			{
				slot_id = i + 1;
				xEXT_CH__BUFFER1__SLOT_TITLE[i]->Get__DATA(title);
			}
			return 1;
		}
	}
	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
Buffer1__Get_Occupied__Slot_To_Process(int& slot_id)
{
	CString var_data;
	xEXT_CH__BUFFER1__CFG_SLOT_MAX->Get__DATA(var_data);

	int slot_size = atoi(var_data);
	int i;

	// ...
	{
		xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PICK->Get__DATA(var_data);
		int s_index = atoi(var_data) - 1;
		if(s_index < 0)		s_index = 0;

		if(xCH__SCH_DB_ST1_WAFER_PICK_MODE->Check__DATA(STR__BOTTOM_TO_UP) > 0)
		{
			for(i=s_index;i<slot_size;i++)
			{
				if(xEXT_CH__BUFFER1__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
				{
					continue;
				}

				// ...
				{
					slot_id = i + 1;

					var_data.Format("%1d", slot_id);
					xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PICK->Set__DATA(var_data);
				}
				return 1;
			}
		}
		else
		{
			for(i=s_index;i>=0;i--)
			{
				if(xEXT_CH__BUFFER1__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
				{
					continue;
				}

				// ...
				{
					slot_id = i + 1;

					var_data.Format("%1d", slot_id);
					xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PICK->Set__DATA(var_data);
				}
				return 1;
			}
		}
	}

	//
	if(xCH__SCH_DB_ST1_WAFER_PICK_MODE->Check__DATA(STR__BOTTOM_TO_UP) > 0)
	{
		for(i=0;i<slot_size;i++)
		{
			if(xEXT_CH__BUFFER1__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				continue;
			}

			// ...
			{
				slot_id = i + 1;

				var_data.Format("%1d", slot_id);
				xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PICK->Set__DATA(var_data);
			}
			return 1;
		}
	}
	else
	{
		for(i=slot_size-1;i>=0;i--)
		{
			if(xEXT_CH__BUFFER1__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				continue;
			}

			// ...
			{
				slot_id = i + 1;

				var_data.Format("%1d", slot_id);
				xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PICK->Set__DATA(var_data);
			}
			return 1;
		}
	}
	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
Buffer1__Check_Empty_Slot(int& slot_id)
{
	CString var_data;
	xEXT_CH__BUFFER1__CFG_SLOT_MAX->Get__DATA(var_data);

	int slot_size = atoi(var_data);
	int i;

	if(xCH__SCH_DB_ST1_WAFER_PICK_MODE->Check__DATA(STR__BOTTOM_TO_UP) > 0)
	{
		for(i=0;i<slot_size;i++)
		{
			if(xEXT_CH__BUFFER1__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				slot_id = i + 1;
				return 1;
			}
		}
	}
	else
	{
		for(i=slot_size-1;i>=0;i--)
		{
			if(xEXT_CH__BUFFER1__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				slot_id = i + 1;
				return 1;
			}
		}
	}
	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
Buffer1__Check_Empty__Slot_To_Process(int& slot_id)
{
	CString var_data;
	xEXT_CH__BUFFER1__CFG_SLOT_MAX->Get__DATA(var_data);

	int slot_size = atoi(var_data);
	int i;

	if(Buffer1__Check_Empty__All_Slot() > 0)
	{
		if(xCH__SCH_DB_ST1_WAFER_PICK_MODE->Check__DATA(STR__BOTTOM_TO_UP) > 0)
		{
			xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PLACE->Set__VALUE(1);
			xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PICK->Set__VALUE(1);
		}
		else
		{
			xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PLACE->Set__VALUE(slot_size);
			xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PICK->Set__VALUE(slot_size);
		}
	}

	// ...
	{
		xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PLACE->Get__DATA(var_data);
		int s_index = atoi(var_data) - 1;
		if(s_index < 0)		s_index = 0;

		if(xCH__SCH_DB_ST1_WAFER_PICK_MODE->Check__DATA(STR__BOTTOM_TO_UP) > 0)
		{
			for(i=s_index;i<slot_size;i++)
			{
				if(xEXT_CH__BUFFER1__SLOT_STATUS[i]->Check__DATA(STR__NONE) < 0)
				{
					continue;
				}

				// ...
				{
					slot_id = i + 1;

					var_data.Format("%1d", slot_id);
					xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PLACE->Set__DATA(var_data);
				}
				return 1;
			}
		}
		else
		{
			for(i=s_index;i>=0;i--)
			{
				if(xEXT_CH__BUFFER1__SLOT_STATUS[i]->Check__DATA(STR__NONE) < 0)
				{
					continue;
				}

				// ...
				{
					slot_id = i + 1;

					var_data.Format("%1d", slot_id);
					xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PLACE->Set__DATA(var_data);
				}
				return 1;
			}
		}
	}

	//
	if(xCH__SCH_DB_ST1_WAFER_PICK_MODE->Check__DATA(STR__BOTTOM_TO_UP) > 0)
	{
		for(i=0;i<slot_size;i++)
		{
			if(xEXT_CH__BUFFER1__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				// ...
				{
					slot_id = i + 1;

					var_data.Format("%1d", slot_id);
					xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PLACE->Set__DATA(var_data);
				}
				return 1;
			}
		}
	}
	else
	{
		for(i=slot_size-1;i>=0;i--)
		{
			if(xEXT_CH__BUFFER1__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				// ...
				{
					slot_id = i + 1;

					var_data.Format("%1d", slot_id);
					xEXT_CH__BUFFER1__APP_NEXT_SLOT_TO_PLACE->Set__DATA(var_data);
				}
				return 1;
			}
		}
	}

	return -1;
}
CString CObj_Fnc__SINGLE_ARM_STD::
Buffer1__Get_LotID()
{
	CString str_lotid = "";

	if(Buffer1__Check_Empty__All_Slot() < 0)
	{
		int slot_id;

		if(Buffer1__Get_Occupied__Slot_To_Process(slot_id) > 0)
		{
			CString sch_name;
			sch_name.Format("%s-%1d", MODULE__BUFFER1,slot_id);

			IDS__SCH_MATERIAL_INFO ds_info;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(sch_name,ds_info) > 0)
			{
				str_lotid = ds_info.sLOT_ID;
			}
			else
			{
				str_lotid = "!!!";
			}
		}
		else
		{
			str_lotid = "???";
		}
	}

	xEXT_CH__BUFFER1__APP_CUR_LOTID->Set__DATA(str_lotid);
	return str_lotid;
}
int  CObj_Fnc__SINGLE_ARM_STD::
Buffer1__Check_Empty__All_Slot()
{
	CString var_data;
	xEXT_CH__BUFFER1__CFG_SLOT_MAX->Get__DATA(var_data);

	int slot_size = atoi(var_data);
	int i;

	for(i=0;i<slot_size;i++)
	{
		if(xEXT_CH__BUFFER1__SLOT_STATUS[i]->Check__DATA(STR__NONE) < 0)
		{
			return -1;
		}
	}
	return 1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
Buffer1__Check_Empty__Any_Slot()
{
	CString var_data;
	xEXT_CH__BUFFER1__CFG_SLOT_MAX->Get__DATA(var_data);

	int slot_size = atoi(var_data);
	int i;

	for(i=0;i<slot_size;i++)
	{
		if(xEXT_CH__BUFFER1__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
		{
			return 1;
		}
	}
	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
Buffer1__Check_Wait_Sec(const int slot_id)
{		
	int db_index = slot_id - 1;

	if(db_index < 0)						return -1;
	if(db_index >= CFG_LP__SLOT_MAX)		return -1;

	CString var_data;
	xEXT_CH__BUFFER1__SLOT_WAIT_SEC[db_index]->Get__DATA(var_data);

	if(atoi(var_data) > 0)
	{
		return 1;
	}
	return -1;
}

int  CObj_Fnc__SINGLE_ARM_STD::
Buffer2__Get_Occupied__Slot(int& slot_id,CString& title)
{
	CString var_data;
	xEXT_CH__BUFFER2__CFG_SLOT_MAX->Get__DATA(var_data);

	int slot_size = atoi(var_data);
	int i;

	if(xCH__SCH_DB_ST2_WAFER_PICK_MODE->Check__DATA(STR__BOTTOM_TO_UP) > 0)
	{
		for(i=0;i<slot_size;i++)
		{
			if(xEXT_CH__BUFFER2__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				continue;
			}

			// ...
			{
				slot_id = i + 1;
				xEXT_CH__BUFFER2__SLOT_TITLE[i]->Get__DATA(title);
			}
			return 1;
		}
	}
	else
	{
		for(i=slot_size-1;i>=0;i--)
		{
			if(xEXT_CH__BUFFER2__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				continue;
			}

			// ...
			{
				slot_id = i + 1;
				xEXT_CH__BUFFER2__SLOT_TITLE[i]->Get__DATA(title);
			}
			return 1;
		}
	}
	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
Buffer2__Get_Occupied__Slot_To_Process(int& slot_id)
{
	CString var_data;
	xEXT_CH__BUFFER2__CFG_SLOT_MAX->Get__DATA(var_data);

	int slot_size = atoi(var_data);
	int i;

	// ...
	{
		xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PICK->Get__DATA(var_data);
		int s_index = atoi(var_data) - 1;
		if(s_index < 0)		s_index = 0;

		if(xCH__SCH_DB_ST2_WAFER_PICK_MODE->Check__DATA(STR__BOTTOM_TO_UP) > 0)
		{
			for(i=s_index;i<slot_size;i++)
			{
				if(xEXT_CH__BUFFER2__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
				{
					continue;
				}

				// ...
				{
					slot_id = i + 1;

					var_data.Format("%1d", slot_id);
					xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PICK->Set__DATA(var_data);
				}
				return 1;
			}
		}
		else
		{
			for(i=s_index;i>=0;i--)
			{
				if(xEXT_CH__BUFFER2__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
				{
					continue;
				}

				// ...
				{
					slot_id = i + 1;

					var_data.Format("%1d", slot_id);
					xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PICK->Set__DATA(var_data);
				}
				return 1;
			}
		}
	}

	//
	if(xCH__SCH_DB_ST2_WAFER_PICK_MODE->Check__DATA(STR__BOTTOM_TO_UP) > 0)
	{
		for(i=0;i<slot_size;i++)
		{
			if(xEXT_CH__BUFFER2__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				continue;
			}

			// ...
			{
				slot_id = i + 1;

				var_data.Format("%1d", slot_id);
				xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PICK->Set__DATA(var_data);
			}
			return 1;
		}
	}
	else
	{
		for(i=slot_size-1;i>=0;i--)
		{
			if(xEXT_CH__BUFFER2__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				continue;
			}

			// ...
			{
				slot_id = i + 1;

				var_data.Format("%1d", slot_id);
				xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PICK->Set__DATA(var_data);
			}
			return 1;
		}
	}

	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
Buffer2__Check_Empty_Slot(int& slot_id)
{
	CString var_data;
	xEXT_CH__BUFFER2__CFG_SLOT_MAX->Get__DATA(var_data);

	int slot_size = atoi(var_data);
	int i;

	if(xCH__SCH_DB_ST2_WAFER_PICK_MODE->Check__DATA(STR__BOTTOM_TO_UP) > 0)
	{
		for(i=0;i<slot_size;i++)
		{
			if(xEXT_CH__BUFFER2__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				slot_id = i + 1;
				return 1;
			}
		}
	}
	else
	{
		for(i=slot_size-1;i>=0;i--)
		{
			if(xEXT_CH__BUFFER2__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				slot_id = i + 1;
				return 1;
			}
		}
	}
	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
Buffer2__Check_Empty__Slot_To_Process(int& slot_id)
{
	CString var_data;
	xEXT_CH__BUFFER2__CFG_SLOT_MAX->Get__DATA(var_data);

	int slot_size = atoi(var_data);
	int i;

	if(Buffer2__Check_Empty__All_Slot() > 0)
	{
		if(xCH__SCH_DB_ST2_WAFER_PICK_MODE->Check__DATA(STR__BOTTOM_TO_UP) > 0)
		{
			xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PLACE->Set__VALUE(1);
			xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PICK->Set__VALUE(1);
		}
		else
		{
			xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PLACE->Set__VALUE(slot_size);
			xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PICK->Set__VALUE(slot_size);
		}
	}

	// ...
	{
		xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PLACE->Get__DATA(var_data);
		int s_index = atoi(var_data) - 1;
		if(s_index < 0)		s_index = 0;

		if(xCH__SCH_DB_ST2_WAFER_PICK_MODE->Check__DATA(STR__BOTTOM_TO_UP) > 0)
		{
			for(i=s_index;i<slot_size;i++)
			{
				if(xEXT_CH__BUFFER2__SLOT_STATUS[i]->Check__DATA(STR__NONE) < 0)
				{
					continue;
				}

				// ...
				{
					slot_id = i + 1;

					var_data.Format("%1d", slot_id);
					xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PLACE->Set__DATA(var_data);
				}
				return 1;
			}
		}
		else
		{
			for(i=s_index;i>=0;i--)
			{
				if(xEXT_CH__BUFFER2__SLOT_STATUS[i]->Check__DATA(STR__NONE) < 0)
				{
					continue;
				}

				// ...
				{
					slot_id = i + 1;

					var_data.Format("%1d", slot_id);
					xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PLACE->Set__DATA(var_data);
				}
				return 1;
			}
		}
	}

	//
	if(xCH__SCH_DB_ST2_WAFER_PICK_MODE->Check__DATA(STR__BOTTOM_TO_UP) > 0)
	{
		for(i=0;i<slot_size;i++)
		{
			if(xEXT_CH__BUFFER2__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				// ...
				{
					slot_id = i + 1;

					var_data.Format("%1d", slot_id);
					xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PLACE->Set__DATA(var_data);
				}
				return 1;
			}
		}
	}
	else
	{
		for(i=slot_size-1;i>=0;i--)
		{
			if(xEXT_CH__BUFFER2__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
			{
				// ...
				{
					slot_id = i + 1;

					var_data.Format("%1d", slot_id);
					xEXT_CH__BUFFER2__APP_NEXT_SLOT_TO_PLACE->Set__DATA(var_data);
				}
				return 1;
			}
		}
	}
	return -1;
}
CString CObj_Fnc__SINGLE_ARM_STD::
Buffer2__Get_LotID()
{
	CString str_lotid = "";

	if(Buffer2__Check_Empty__All_Slot() < 0)
	{
		int slot_id;

		if(Buffer2__Get_Occupied__Slot_To_Process(slot_id) > 0)
		{
			CString sch_name;
			sch_name.Format("%s-%1d", MODULE__BUFFER2,slot_id);

			IDS__SCH_MATERIAL_INFO ds_info;
			if(xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(sch_name,ds_info) > 0)
			{
				str_lotid = ds_info.sLOT_ID;
			}
			else
			{
				str_lotid = "!!!";
			}
		}
		else
		{
			str_lotid = "???";
		}
	}

	xEXT_CH__BUFFER2__APP_CUR_LOTID->Set__DATA(str_lotid);
	return str_lotid;
}
int  CObj_Fnc__SINGLE_ARM_STD::
Buffer2__Check_Empty__All_Slot()
{
	CString var_data;
	xEXT_CH__BUFFER2__CFG_SLOT_MAX->Get__DATA(var_data);

	int slot_size = atoi(var_data);
	int i;

	for(i=0;i<slot_size;i++)
	{
		if(xEXT_CH__BUFFER2__SLOT_STATUS[i]->Check__DATA(STR__NONE) < 0)
		{
			return -1;
		}
	}
	return 1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
Buffer2__Check_Empty__Any_Slot()
{
	CString var_data;
	xEXT_CH__BUFFER2__CFG_SLOT_MAX->Get__DATA(var_data);

	int slot_size = atoi(var_data);
	int i;

	for(i=0;i<slot_size;i++)
	{
		if(xEXT_CH__BUFFER2__SLOT_STATUS[i]->Check__DATA(STR__NONE) > 0)
		{
			return 1;
		}
	}
	return -1;
}
int  CObj_Fnc__SINGLE_ARM_STD::
Buffer2__Check_Wait_Sec(const int slot_id)
{		
	// ...
	int db_index = slot_id - 1;

	if(db_index < 0)						return -1;
	if(db_index >= CFG_LP__SLOT_MAX)		return -1;

	// ...
	CString var_data;
	xEXT_CH__BUFFER2__SLOT_WAIT_SEC[db_index]->Get__DATA(var_data);

	if(atoi(var_data) > 0)
	{
		return 1;
	}
	return -1;
}


