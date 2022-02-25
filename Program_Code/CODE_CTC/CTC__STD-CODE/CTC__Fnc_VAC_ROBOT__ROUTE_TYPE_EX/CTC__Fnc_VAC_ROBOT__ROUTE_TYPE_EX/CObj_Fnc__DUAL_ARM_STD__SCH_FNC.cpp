#include "StdAfx.h"
#include "CObj_Fnc__DUAL_ARM_STD.h"

#include "Macro_Function.h"


// ...
int  CObj_Fnc__DUAL_ARM_STD::
SCH__Check_Material_Place(const CString& arm_type)
{
	if(arm_type.CompareNoCase("A") == 0)
	{
		if(VAC_RB__Check_Empty__A_Arm() > 0)
		{
			return 1;
		}
	}
	else if(arm_type.CompareNoCase("B") == 0)
	{
		if(VAC_RB__Check_Empty__B_Arm() > 0)
		{
			return 1;
		}
	}

	return -1;
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__Check_Material_Pick(const CString& arm_type)
{
	if(arm_type.CompareNoCase("A") == 0)
	{
		if(VAC_RB__Check_Occupied__A_Arm() > 0)
		{
			return 1;
		}
	}
	else if(arm_type.CompareNoCase("B") == 0)
	{
		if(VAC_RB__Check_Occupied__B_Arm() > 0)
		{
			return 1;
		}
	}
	
	return -1;
}


// ...
int  CObj_Fnc__DUAL_ARM_STD::
SCH__SWAP_PMx(CII_OBJECT__VARIABLE *p_variable,
			  CII_OBJECT__ALARM *p_alarm,
			  const CString& pick_arm,
			  const CString& place_arm,
			  const CString& para_module,
			  const CString& para_slot,
			  const CString& sch_pmc)
{
	//.....
	int pm_i = SCH__CHECK_PM_INDEX(para_module);
	if(pm_i < 0)		return -1;

	//.....
	try
	{
		xCH__PMx__MOVE_FLAG[pm_i]->Set__DATA("YES");

		//.....
		int flag = 
		_SCH__SWAP_PMx(p_variable,
					   p_alarm,
					   pick_arm,
					   place_arm,
					   para_module,
					   para_slot,
					   sch_pmc);

		xCH__PMx__MOVE_FLAG[pm_i]->Set__DATA("NO");
		//

		if(flag < 0)		return -1;
	}
	catch(const int err_flag)
	{
		xCH__PMx__MOVE_FLAG[pm_i]->Set__DATA("NO");
		return -1;
	}
	//
	
	return 1;
}
int  CObj_Fnc__DUAL_ARM_STD::
_SCH__SWAP_PMx(CII_OBJECT__VARIABLE *p_variable,
			   CII_OBJECT__ALARM *p_alarm,
			   const CString& pick_arm,
			   const CString& place_arm,
			   const CString& para_module,
			   const CString& para_slot,
			   const CString& sch_pmc)
{
	int maint_flag = -1;

	if(SCH__CHECK_PICK_MODULE__READY(p_variable,true,
									 para_module,
									 para_slot,
									 maint_flag) < 0)
	{
		return -1;
	}

	if(maint_flag < 0)
	{
		Datalog__Picking_Material(pick_arm,para_module,para_slot,1);
		Datalog__Placing_Material(place_arm,para_module,para_slot,1);

		xSCH_MATERIAL_CTRL->Transfer_Start__To_MODULE(sch_pmc,pick_arm);
		xSCH_MATERIAL_CTRL->Transfer_Start__To_MODULE(place_arm,sch_pmc);
	}

	iFRONT_PMx_FLAG = -1;
	iFRONT_WAC_FLAG = -1;

	if(SCH__Seq_SWAP_PMx(p_variable,
						 pick_arm,
						 para_module,
						 para_slot) < 0)
	{
		return -1;
	}

	if(maint_flag < 0)
	{
		Datalog__Picked_Material(pick_arm,para_module,para_slot,-1);
		Datalog__Placed_Material(place_arm,para_module,para_slot,-1);

		xSCH_MATERIAL_CTRL->Transfer_End__To_MODULE(sch_pmc,pick_arm);
		xSCH_MATERIAL_CTRL->Transfer_End__To_MODULE(place_arm,sch_pmc);
	}
	
	if(SCH__CHECK_PLACE_MODULE__COMPLETE(p_variable,
										 false,
										 place_arm,
										 para_module,
										 para_slot,
										 maint_flag) < 0)	
	{

	}

	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD::
SCH__SWAP_LBx(CII_OBJECT__VARIABLE *p_variable,
			  CII_OBJECT__ALARM    *p_alarm,
			  const CString& para_module,
			  const CString& place_arm,
			  const CString& place_slot,
			  const CString& pick_arm,
			  const CString& pick_slot,
			  const CString& sch_place_module,
			  const CString& sch_pick_module)
{
	int ll_i = Get__LLx_INDEX(para_module);
	if(ll_i >= 0)
	{
		if(LLx__Is_Available(ll_i) < 0)
		{
			return -1;
		}

		xEXT_CH__LLx__MOVE_FLAG[ll_i]->Set__DATA("YES");
	}

	try
	{
		int flag = 
			_SCH__SWAP_LBx(p_variable,
						   p_alarm,
						   para_module,
						   place_arm,
						   place_slot,
						   pick_arm,
						   pick_slot,
						   sch_place_module,
						   sch_pick_module);

		if(ll_i >= 0)
		{
			CString var_data;
			
			var_data.Format("%1d", ++iLBx_OUT_COUNT);
			xEXT_CH__LLx__OUT_COUNT[ll_i]->Set__DATA(var_data);
			xEXT_CH__LLx__MOVE_FLAG[ll_i]->Set__DATA("NO");
		}

		if(flag < 0)
		{
			return -1;
		}
	}
	catch(const int err_flag)
	{
		if(ll_i >= 0)
		{
			xEXT_CH__LLx__MOVE_FLAG[ll_i]->Set__DATA("NO");
		}		
		return -1;
	}

	return 1;
}
int  CObj_Fnc__DUAL_ARM_STD::
_SCH__SWAP_LBx(CII_OBJECT__VARIABLE *p_variable,
			   CII_OBJECT__ALARM    *p_alarm,
			   const CString& para_module,
			   const CString& place_arm,
			   const CString& place_slot,
			   const CString& pick_arm,
			   const CString& pick_slot,
			   const CString& sch_place_module,
			   const CString& sch_pick_module)
{
	int maint_flag = -1;

	if(maint_flag < 0)
	{
		Datalog__Placing_Material(place_arm,para_module,place_slot,1);
		Datalog__Picking_Material(pick_arm,para_module,pick_slot,1);

		xSCH_MATERIAL_CTRL->Transfer_Start__To_MODULE(place_arm,sch_place_module);
		xSCH_MATERIAL_CTRL->Transfer_Start__To_MODULE(sch_pick_module,pick_arm);
	}

	iFRONT_PMx_FLAG = -1;
	iFRONT_WAC_FLAG = -1;

	if(SCH__Seq_SWAP_LBx(p_variable,
						 place_arm,
						 pick_arm,
						 para_module,
						 place_slot,
						 pick_slot) < 0)
	{
		return -1;
	}

	if(maint_flag < 0)
	{
		Datalog__Placed_Material(place_arm,para_module,place_slot,-1);
		Datalog__Picked_Material(pick_arm,para_module,pick_slot,-1);

		xSCH_MATERIAL_CTRL->Transfer_End__To_MODULE(place_arm,sch_place_module);
		xSCH_MATERIAL_CTRL->Transfer_End__To_MODULE(sch_pick_module,pick_arm);
	}

	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD::
SCH__PICK_MODULE(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm,
				 const CString& log_xx,
				 const bool ex_flag,
			     const CString& arm_type,const CString& para_module,const CString& para_slot,
				 const CString& from_sch,
				 const int maint_flag)
{
	CStringArray l_from_sch;

	l_from_sch.Add(from_sch);

	return SCH__PICK_MODULE(p_variable,
							p_alarm,
							log_xx,
							ex_flag,
							arm_type,para_module,para_slot,
							l_from_sch,
							maint_flag);
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__PICK_MODULE(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm,
				 const CString& log_xx,
				 const bool ex_flag,
				 const CString& arm_type,const CString& para_module,const CString& para_slot,
				 const CStringArray& l_from_sch,
				 const int maint_flag)
{
	CString log_id = log_xx;
	log_id += " -> ";
	log_id += "SCH__PICK_MODULE()";

	// ...
	int ll_i = Get__LLx_INDEX(para_module);
	int pm_i = SCH__CHECK_PM_INDEX(para_module);

	try
	{
		if(ll_i >= 0)
		{
			CString str__sch_name;
			str__sch_name.Format("%s-%s", para_module,para_slot);

			CStringArray l_prc_module;
			CStringArray l_prc_recipe;

			xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(str__sch_name, l_prc_module,l_prc_recipe);

			int k_limit = l_prc_module.GetSize();
			int k;

			for(k=0; k<k_limit; k++)
			{
				int pm_i = SCH__CHECK_PM_INDEX(l_prc_module[k]);

				if((pm_i >= 0) && (pm_i < iPMx_SIZE))
				{
					/*
					xCH__PMx__HEADER_TEMP_CHECK_RECIPE[pm_i]->Set__DATA(l_prc_recipe[k]);
					xCH__PMx__HEADER_TEMP_CHECK_FLAG[pm_i]->Set__DATA(STR__YES);
					*/
				}	
			}
		}

		if(pm_i >= 0)
		{
			xCH__PMx__MOVE_FLAG[pm_i]->Set__DATA("YES");
		}
		else if(ll_i >= 0)
		{
			xEXT_CH__LLx__MOVE_FLAG[ll_i]->Set__DATA("YES");
		}

		int flag = 
			_SCH__PICK_MODULE(p_variable,p_alarm,
							  log_id,
							  ex_flag,
							  arm_type,para_module,para_slot,
							  l_from_sch,
							  maint_flag);

		if((flag > 0) && (!ex_flag))
		{
			if(pm_i >= 0)
			{
				xCH__PMx__MOVE_FLAG[pm_i]->Set__DATA("NO");
			}
			else if(ll_i >= 0)
			{
				xEXT_CH__LLx__MOVE_FLAG[ll_i]->Set__DATA("NO");
			}
		}

		if(flag < 0)
		{
			if(pm_i >= 0)
			{
				xCH__PMx__MOVE_FLAG[pm_i]->Set__DATA("NO");
			}
			else if(ll_i >= 0)
			{
				xEXT_CH__LLx__MOVE_FLAG[ll_i]->Set__DATA("NO");
			}

			return -1;
		}
	}
	catch(const int err_flag)
	{
		if(pm_i >= 0)
		{
			xCH__PMx__MOVE_FLAG[pm_i]->Set__DATA("NO");
		}
		else if(ll_i >= 0)
		{
			xEXT_CH__LLx__MOVE_FLAG[ll_i]->Set__DATA("NO");
		}

		return -1;
	}
	
	return 1;
}
int  CObj_Fnc__DUAL_ARM_STD::
_SCH__PICK_MODULE(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm,
				  const CString& log_id,
				  const bool ex_flag,
			      const CString& arm_type,const CString& para_module,const CString& para_slot,
				  const CStringArray& l_from_sch,
				  const int maint_flag)
{
	CString fnc_id = "_SCH__PICK_MODULE()";

	if(SCH__CHECK_PICK_MODULE__READY(p_variable,
									 ex_flag,
									 para_module,para_slot,maint_flag) < 0)
	{
		return -1;
	}

	if(maint_flag < 0)
	{
		Datalog__Picking_Material(arm_type,para_module,para_slot,ex_flag);

		int i_limit = l_from_sch.GetSize();
		for(int i=0; i<i_limit; i++)
		{
			CString sch_name = l_from_sch[i];
			xSCH_MATERIAL_CTRL->Transfer_Start__To_MODULE(sch_name, arm_type);
		}
	}

	iFRONT_PMx_FLAG = -1;
	iFRONT_WAC_FLAG = -1;

	if(SCH__PICK_FROM(p_variable,
					  p_alarm,
					  ex_flag,
					  arm_type,
					  para_module,
					  para_slot) < 0)
	{
		return -1;
	}

	// ...
	{
		CString para_info;
		para_info.Format("%s <- %s(%s) : ex_flag(%1d)", arm_type,para_module,para_slot,ex_flag);

		Fnc__LOG_INFO(fnc_id, log_id, para_info);
	}

	if(maint_flag < 0)
	{
		Datalog__Picked_Material(arm_type,para_module,para_slot,ex_flag);

		int i_limit = l_from_sch.GetSize();
		for(int i=0; i<i_limit; i++)
		{
			CString sch_name = l_from_sch[i];
			xSCH_MATERIAL_CTRL->Transfer_End__To_MODULE(sch_name, arm_type);
		}
	}
	
	if(SCH__CHECK_PICK_MODULE__COMPLETE(p_variable,
										p_alarm,
										ex_flag,
										para_module,
										para_slot,
										l_from_sch,
										maint_flag) < 0)
	{
		return -1;
	}

	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD::
SCH__PLACE_MODULE(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm,
				  const CString& log_id,
				  const bool ex_flag,
 			      const CString& arm_type,const CString& para_module,const CString& para_slot,
				  const CString& to_sch,
				  const int maint_flag)
{
	return SCH__PLACE_MODULE(p_variable,p_alarm,
							 log_id,
							 ex_flag, 
							 arm_type,para_module,para_slot, 
							 to_sch,to_sch, 
							 maint_flag);
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__PLACE_MODULE(CII_OBJECT__VARIABLE *p_variable,
				  CII_OBJECT__ALARM *p_alarm,
				  const CString& log_id,
				  const bool ex_flag,
				  const CString& arm_type,const CString& para_module,const CString& para_slot,
				  const CString& to_sch_01,
				  const CString& to_sch_02,
				  const int maint_flag)
{
	int ll_i = Get__LLx_INDEX(para_module);
	int pm_i = SCH__CHECK_PM_INDEX(para_module);

	try
	{
		if(pm_i >= 0)
		{
			xCH__PMx__MOVE_FLAG[pm_i]->Set__DATA("YES");
		}
		else if(ll_i >= 0)
		{
			xEXT_CH__LLx__MOVE_FLAG[ll_i]->Set__DATA("YES");
		}

		int flag = 
			_SCH__PLACE_MODULE(p_variable,p_alarm,
							   log_id,
			                   ex_flag,
 						       arm_type,para_module,para_slot,
							   to_sch_01,
							   to_sch_02,
							   maint_flag);

		if((flag > 0) && (!ex_flag))
		{
			if(pm_i >= 0)
			{
				xCH__PMx__FIRST_WAFER_FLAG[pm_i]->Set__DATA("");
				xCH__PMx__MOVE_FLAG[pm_i]->Set__DATA("NO");
			}
			else if(ll_i >= 0)
			{
				xEXT_CH__LLx__MOVE_FLAG[ll_i]->Set__DATA("NO");
			}
		}

		if(flag < 0)
		{
			if(pm_i >= 0)
			{
				xCH__PMx__FIRST_WAFER_FLAG[pm_i]->Set__DATA("");
				xCH__PMx__MOVE_FLAG[pm_i]->Set__DATA("NO");
			}
			else if(ll_i >= 0)
			{
				xEXT_CH__LLx__MOVE_FLAG[ll_i]->Set__DATA("NO");
			}

			return -1;
		}
	}
	catch(const int err_flag)
	{
		if(pm_i >= 0)
		{
			xCH__PMx__MOVE_FLAG[pm_i]->Set__DATA("NO");
		}
		else if(ll_i >= 0)
		{
			xEXT_CH__LLx__MOVE_FLAG[ll_i]->Set__DATA("NO");
		}

		return -1;
	}

	return 1;
}
int  CObj_Fnc__DUAL_ARM_STD::
_SCH__PLACE_MODULE(CII_OBJECT__VARIABLE *p_variable,
				   CII_OBJECT__ALARM *p_alarm,
				   const CString& log_id,
				   const bool ex_flag,
 			       const CString& arm_type,const CString& para_module,const CString& para_slot,
				   const CString& to_sch_01, 
				   const CString& to_sch_02,
				   const int maint_flag)
{
	CString fnc_id = "_SCH__PLACE_MODULE()";

	if(SCH__CHECK_PLACE_MODULE__READY(p_variable,
									  ex_flag,
									  arm_type,
									  para_module,
									  para_slot,
									  maint_flag) < 0)
	{
		return -1;
	}

	if(maint_flag < 0)
	{	
		if(arm_type.CompareNoCase("AB") == 0)
		{
			Datalog__Placing_Material("A", para_module,para_slot,ex_flag);
			Datalog__Placing_Material("B", para_module,para_slot,ex_flag);

			xSCH_MATERIAL_CTRL->Transfer_Start__To_MODULE("A", to_sch_01);
			xSCH_MATERIAL_CTRL->Transfer_Start__To_MODULE("B", to_sch_02);
		}
		else
		{
			Datalog__Placing_Material(arm_type,para_module,para_slot,ex_flag);

			xSCH_MATERIAL_CTRL->Transfer_Start__To_MODULE(arm_type, to_sch_01);
		}
	}

	// ...
	SCX__ASYNC_TIMER_CTRL x_async_timer_ctrl;
	x_async_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(xEXT_CH__SCH__WAC_WAFER_DELAY_COUNT->Get__CHANNEL_NAME());

	// ...
	{
		iFRONT_PMx_FLAG = -1;

		if(iFRONT_WAC_FLAG > 0)
		{
			iFRONT_WAC_FLAG = -1;

			// ...
			CString var_data;
			double delay_sec = 0;

			xEXT_CH__SCH__WAC_WAFER_APPLY->Set__DATA(STR__YES);
			xEXT_CH__SCH__WAC_WAFER_DELAY_SEC->Get__DATA(var_data);
			delay_sec = atof(var_data);

			x_async_timer_ctrl->START__COUNT_DOWN(delay_sec);
		}
		else
		{
			xEXT_CH__SCH__WAC_WAFER_APPLY->Set__DATA("");
		}
	}

	if(SCH__PLACE_TO(p_variable,
					 p_alarm,
					 ex_flag,
					 arm_type,
					 para_module,
					 para_slot) < 0)			
	{
		xEXT_CH__SCH__WAC_WAFER_APPLY->Set__DATA("");
		x_async_timer_ctrl->STOP();
		return -1;
	}
	else
	{
		xEXT_CH__SCH__WAC_WAFER_APPLY->Set__DATA("");
		x_async_timer_ctrl->STOP();
	}

	// ...
	{
		CString para_info;
		para_info.Format("%s -> %s(%s) : ex_flag(%1d)", arm_type,para_module,para_slot,ex_flag);

		Fnc__LOG_INFO(fnc_id, log_id, para_info);
	}

	if(maint_flag < 0)
	{
		if(arm_type.CompareNoCase("AB") == 0)
		{
			Datalog__Placed_Material("A", para_module,para_slot,ex_flag);
			Datalog__Placed_Material("B", para_module,para_slot,ex_flag);

			xSCH_MATERIAL_CTRL->Transfer_End__To_MODULE("A", to_sch_01);
			xSCH_MATERIAL_CTRL->Transfer_End__To_MODULE("B", to_sch_02);

		}
		else
		{
			Datalog__Placed_Material(arm_type,para_module,para_slot,ex_flag);

			xSCH_MATERIAL_CTRL->Transfer_End__To_MODULE(arm_type,to_sch_01);
		}
	}

	if(SCH__CHECK_PLACE_MODULE__COMPLETE(p_variable,
										 ex_flag,
										 arm_type,
										 para_module,
										 para_slot,
										 maint_flag) < 0)	
	{

	}
	
	return 1;
}


//-----------------------------------------------------------------------------------------
int  CObj_Fnc__DUAL_ARM_STD::
SCH__Seq_SWAP_PMx(CII_OBJECT__VARIABLE *p_variable,
			      const CString& arm_type,
				  const CString& para_module,
				  const CString& para_slot)
{
	DECLARE__EXT_CTRL(p_variable);
	
	// ...
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(arm_type);
	l_para.Add(para_module);
	l_para.Add(para_slot);

	return pVAC_RB__OBJ_CTRL->Call__OBJ_MODE(CMMD__SWAP_PMx,l_para);
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__Seq_SWAP_LBx(CII_OBJECT__VARIABLE *p_variable,
				  const CString& place_arm,
			      const CString& pick_arm,
				  const CString& para_module,
				  const CString& place_slot,
				  const CString& pick_slot)
{
	DECLARE__EXT_CTRL(p_variable);
	
	// ...
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(para_module);
	
	l_para.Add(place_arm);
	l_para.Add(place_slot);

	l_para.Add(pick_arm);
	l_para.Add(pick_slot);

	return pVAC_RB__OBJ_CTRL->Call__OBJ_MODE(CMMD__SWAP_LBx,l_para);
}

int  CObj_Fnc__DUAL_ARM_STD::
SCH__PICK_FROM(CII_OBJECT__VARIABLE *p_variable,
			   CII_OBJECT__ALARM *p_alarm,
			   const bool ex_flag,
			   const CString& arm_type,
			   const CString& str_module,
			   const CString& str_slot)
{
	DECLARE__EXT_CTRL(p_variable);
	
	// ...
	CStringArray l_para;

	CString x_module = str_module;
	int ll_i = Get__LLx_INDEX(x_module);
	if(ll_i >= 0)		x_module = Get__LLx_NAME(ll_i);

	l_para.RemoveAll();
	l_para.Add(arm_type);
	l_para.Add(x_module);
	l_para.Add(str_slot);

	// ...
	int flag;

	if(ex_flag == false)
	{
		flag = pVAC_RB__OBJ_CTRL->Call__OBJ_MODE(CMMD__PICK,l_para);
	}
	else
	{
		flag = pVAC_RB__OBJ_CTRL->Call__OBJ_MODE(CMMD__XPICK,l_para);
	}

	if(flag < 0)
	{
		// ...
		{
			int alarm_id = ALID__MOVE_ERROR__WAFER_CONFIRM;
			CString str_msg;
			CString r_act;
		
			// ...
			{
				str_msg = "GUI와 실제 정보가 일치하는가? \n";
			}
			
			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,str_msg,r_act);
		
			if(r_act.CompareNoCase(STR__ABORT) == 0)
			{
				return -1001;
			}
		}

		// ...
		{
			int alarm_id = ALID__USER_CHECK__WAFER_CONFIRM;
			CString str_msg;
			CString str_bff;
			CString r_act;

			// ...
			{
				str_bff.Format("다시 한번, GUI상의 Wafer 정보와 실제 Wafer 정보가 일치하는지 확인하십시요.\n");
				str_msg += str_bff;

				str_msg += "만약, 일치하지 않는다면 아래와 같이 처리해 주십시요.\n";
			
				str_msg += "   1. 현재 실행 중인 Job을 Abort시킨다. \n";
				str_msg += "   2. CTC Resync-Page에서 Wafer 정보를 실제와 일치시킨다. \n";
				str_msg += "   3. Tool-Clear를 실행시킨다. \n";
			}

			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,str_msg,r_act);
		}
	}
	else if(flag > 0)
	{
LOOP__RETRY_CHECK:
	
		// Material Pick : Check ...
		CString slot_status;
		CString slot_title;
		int check_flag = -1;

		int slot_index = atoi(str_slot) - 1;

		if(str_module.CompareNoCase(MODULE__LBA) == 0)
		{
			int ll_i = _LLx_INDEX__LBA;
			int slot_max = iLLx_SLOT_MAX[ll_i];

			if((slot_index >= 0)
			&& (slot_index <  slot_max))	
			{
				check_flag = 1;

				xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Get__DATA(slot_status);
				xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Get__DATA(slot_title);
			}
		}
		else if(str_module.CompareNoCase(MODULE__LBB) == 0)
		{
			int ll_i = _LLx_INDEX__LBB;
			int slot_max = iLLx_SLOT_MAX[ll_i];

			if((slot_index >= 0)
			&& (slot_index <  slot_max))	
			{
				check_flag = 1;

				xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Get__DATA(slot_status);
				xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Get__DATA(slot_title);
			}
		}
		else
		{
			int lp_index = SCH__CHECK_PM_INDEX(str_module);

			if(lp_index >= 0)
			{
				check_flag = 1;

				//
				xCH__PMx__SLOT_STATUS[lp_index]->Get__DATA(slot_status);
				xCH__PMx__SLOT_TITLE[lp_index]->Get__DATA(slot_title);
			}
		}

		if(check_flag > 0)
		{
			CString arm_status;
			CString arm_title;

			if(arm_type.CompareNoCase(STR__A) == 0)
			{
				xCH__VAC_RB__SLOT01_STATUS->Get__DATA(arm_status);
				xCH__VAC_RB__SLOT01_TITLE->Get__DATA(arm_title);
			}	
			else if(arm_type.CompareNoCase(STR__B) == 0)
			{
				xCH__VAC_RB__SLOT02_STATUS->Get__DATA(arm_status);
				xCH__VAC_RB__SLOT02_TITLE->Get__DATA(arm_title);
			}
			
			if((arm_status.CompareNoCase(STR__NONE)  == 0)
			|| (slot_status.CompareNoCase(STR__NONE) != 0))	
			{
				int alarm_id;
				CString str_msg;
				CString str_bff;
				CString r_act;
				
				alarm_id = ALID__PICK_ERROR__WAFER_MITMATCH;
				
				str_bff.Format("아래와 같이 PICK 명령을 처리 후 Wafer 정보에 문제가 발생 했습니다. \n");
				str_msg += str_bff;
				
				str_bff.Format("   PICK 명령은 %s(%s) -> Arm(%s) 입니다. \n", 
							   str_module,str_slot, arm_type);
				str_msg += str_bff;

				str_bff.Format("   현재, GUI Wafer 상태는 Robot(%s) <- %s(%s)이고 %s(%s) <- %s(%s)입니다. \n",
					           arm_type, arm_status,arm_title,
							   str_module,str_slot, slot_status,slot_title);
				str_msg += str_bff;
				
				str_msg += "GUI 정보와 실제 Wafer가 일치하는지 확인 부탁합니다.\n";
				str_msg += "   1. 만약, PICK 명령이 제대로 수행되지 않았다면 \n";
				str_msg += "      ABORT를 선택하시고 JOB를 Abort해 주십시요. \n";
				str_msg += "      Robot은 Pause 됩니다. \n";
				str_msg += "   2. 실제 Wafer가 PICK 명령처럼 정상처리 되었다면, RETRY 선택하십시요. \n";
				str_msg += "      GUI 정보가 모두 정상이면 정상적으로 JOB을 진행할 것입니다. \n";
				
				p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,str_msg,r_act);
				
				if(r_act.CompareNoCase(STR__RETRY) == 0)
				{
					goto LOOP__RETRY_CHECK;
				}

				// ...
				{
					xCH__VAC_RB_PAUSE_FLAG->Set__DATA(STR__YES);
				}
				return -1;
			}
		}
	}

	return flag;
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__PLACE_TO(CII_OBJECT__VARIABLE *p_variable,
			  CII_OBJECT__ALARM *p_alarm,
			  const bool ex_flag,
			  const CString& arm_type,
			  const CString& str_module,
			  const CString& str_slot)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CStringArray l_para;

	CString x_module = str_module;
	int ll_i = Get__LLx_INDEX(x_module);
	if(ll_i >= 0)		x_module = Get__LLx_NAME(ll_i);

	l_para.RemoveAll();
	l_para.Add(arm_type);
	l_para.Add(x_module);
	l_para.Add(str_slot);
	
	// ...
	int flag;

	if(ex_flag == false)
	{
		flag = pVAC_RB__OBJ_CTRL->Call__OBJ_MODE(CMMD__PLACE,l_para);
	}
	else
	{
		flag = pVAC_RB__OBJ_CTRL->Call__OBJ_MODE(CMMD__XPLACE,l_para);
	}

	if(flag < 0)
	{
		// ...
		{
			int alarm_id = ALID__MOVE_ERROR__WAFER_CONFIRM;
			CString str_msg;
			CString r_act;
			
			// ...
			{
				str_msg = "GUI와 실제 정보가 일치하는가? \n";
			}
			
			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,str_msg,r_act);
			
			if(r_act.CompareNoCase(STR__ABORT) == 0)
			{
				return -1001;
			}
		}

		// ...
		{
			int alarm_id = ALID__USER_CHECK__WAFER_CONFIRM;
			CString str_msg;
			CString str_bff;
			CString r_act;
						
			str_bff.Format("다시 한번, GUI상의 Wafer 정보와 실제 Wafer 정보가 일치하는지 확인하십시요.\n");
			str_msg += str_bff;
			
			str_msg += "만약, 일치하지 않는다면 아래와 같이 처리해 주십시요.\n";
			
			str_msg += "   1. 현재 실행 중인 Job을 Abort시킨다. \n";
			str_msg += "   2. CTC Resync-Page에서 Wafer 정보를 실제와 일치시킨다. \n";
			str_msg += "   3. Tool-Clear를 실행시킨다. \n";
			
			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,str_msg,r_act);
		}
	}
	else if(flag > 0)
	{
LOOP__RETRY_CHECK:
	
		// Material Place : Check ...
		CString slot_status;
		CString slot_title;
		int check_flag = -1;

		int slot_index = atoi(str_slot) - 1;

		if(str_module.CompareNoCase(MODULE__LBA) == 0)
		{
			int ll_i = _LLx_INDEX__LBA;
			int slot_max = iLLx_SLOT_MAX[ll_i];

			if((slot_index >= 0)
			&& (slot_index <  slot_max))	
			{
				check_flag = 1;

				xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Get__DATA(slot_status);
				xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Get__DATA(slot_title);
			}
		}
		else if(str_module.CompareNoCase(MODULE__LBB) == 0)
		{
			int ll_i = _LLx_INDEX__LBB;
			int slot_max = iLLx_SLOT_MAX[ll_i];

			if((slot_index >= 0)
			&& (slot_index <  slot_max))	
			{
				check_flag = 1;

				xEXT_CH__LLx__SLOT_STATUS[ll_i][slot_index]->Get__DATA(slot_status);
				xEXT_CH__LLx__SLOT_TITLE[ll_i][slot_index]->Get__DATA(slot_title);
			}
		}
		else
		{
			int lp_index = SCH__CHECK_PM_INDEX(str_module);

			if(lp_index >= 0)
			{
				check_flag = 1;

				xCH__PMx__SLOT_STATUS[lp_index]->Get__DATA(slot_status);
				xCH__PMx__SLOT_TITLE[lp_index]->Get__DATA(slot_title);
			}
		}

		if(check_flag > 0)
		{
			CStringArray l_arm_type;

			if(arm_type.CompareNoCase("AB") == 0)
			{
				l_arm_type.Add("A");
				l_arm_type.Add("B");
			}
			else
			{
				l_arm_type.Add(arm_type);
			}

			int k_limit = l_arm_type.GetSize();
			for(int k=0; k<k_limit; k++)
			{
				CString check_arm = l_arm_type[k];

				// 
				CString arm_status;
				CString arm_title;

				if(check_arm.CompareNoCase(STR__A) == 0)
				{
					xCH__VAC_RB__SLOT01_STATUS->Get__DATA(arm_status);
					xCH__VAC_RB__SLOT01_TITLE->Get__DATA(arm_title);
				}	
				else if(check_arm.CompareNoCase(STR__B) == 0)
				{
					xCH__VAC_RB__SLOT02_STATUS->Get__DATA(arm_status);
					xCH__VAC_RB__SLOT02_TITLE->Get__DATA(arm_title);
				}
			
				if((arm_status.CompareNoCase(STR__NONE)  != 0)
				|| (slot_status.CompareNoCase(STR__NONE) == 0))	
				{
					// ...
					int alarm_id;
					CString str_msg;
					CString str_bff;
					CString r_act;
					
					alarm_id = ALID__PLACE_ERROR__WAFER_MITMATCH;
					
					str_bff.Format("아래와 같이 PLACE 명령을 처리 후 Wafer 정보에 문제가 발생 했습니다. \n");
					str_msg += str_bff;
					
					str_bff.Format("   PLACE 명령은 Arm(%s) -> %s(%s) 입니다. \n", 
								   arm_type, str_module,str_slot);
					str_msg += str_bff;

					str_bff.Format("   현재, GUI Wafer 상태는 Robot(%s) <- %s(%s)이고 %s(%s) <- %s(%s)입니다. \n",
								   arm_type, arm_status,arm_title,
								   str_module,str_slot, slot_status,slot_title);
					str_msg += str_bff;
					
					str_msg += "GUI 정보와 실제 Wafer가 일치하는지 확인 부탁합니다.\n";
					str_msg += "   1. 만약, PICK 명령이 제대로 수행되지 않았다면 \n";
					str_msg += "      ABORT를 선택하시고 JOB를 Abort해 주십시요. \n";
					str_msg += "      Robot은 Pause 됩니다. \n";
					str_msg += "   2. 실제 Wafer가 PICK 명령처럼 정상처리 되었다면, RETRY 선택하십시요. \n";
					str_msg += "      GUI 정보가 모두 정상이면 정상적으로 JOB을 진행할 것입니다. \n";
					
					p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,str_msg,r_act);
					
					if(r_act.CompareNoCase(STR__RETRY) == 0)
					{
						goto LOOP__RETRY_CHECK;
					}

					// ...
					{
						xCH__VAC_RB_PAUSE_FLAG->Set__DATA(STR__YES);
					}
					return -1;
				}
			}
		}
	}

	return flag;
}


//-----------------------------------------------------------------------------------------
int  CObj_Fnc__DUAL_ARM_STD
::SCH_RUN__LLx_VENT(const int ll_index,
					const CString& log_id,
					const CString& sub_id)
{
	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "SCH_RUN__LLx_VENT() ... \n";
		log_bff.Format(" * llx_id <- [%1d] \n", ll_index+1);
		log_msg += log_bff;
		log_bff.Format(" * log_id <- [%s] \n", log_id);
		log_msg += log_bff;
		log_bff.Format(" * sub_id <- [%s] \n", sub_id);
		log_msg += log_bff;

		Fnc__LOG_CTRL(log_msg);
	}

	sEXT_CH__LLx__UPPER_OBJ_MSG[ll_index]->Set__DATA(log_id);

	pLLx__OBJ_CTRL[ll_index]->Run__OBJECT(CMMD__VENT);
	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD
::SCH_CALL__LLx_VENT(const int ll_index, 
					 const CString& log_id)
{
	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "SCH_CALL__LLx_VENT() ... \n";
		log_bff.Format(" * llx_id <- [%1d] \n", ll_index+1);
		log_msg += log_bff;
		log_bff.Format(" * log_id <- [%s] \n", log_id);
		log_msg += log_bff;

		Fnc__LOG_CTRL(log_msg);
	}

	sEXT_CH__LLx__UPPER_OBJ_MSG[ll_index]->Set__DATA(log_id);

	return pLLx__OBJ_CTRL[ll_index]->Call__OBJECT(CMMD__VENT);
}

//-----------------------------------------------------------------------------------------
int  CObj_Fnc__DUAL_ARM_STD
::SCH_RUN__LLx_PUMP(const int ll_index,
					const CString& log_id,
					const CString& sub_id)
{
	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "SCH_RUN__LBB_PUMP() ... \n";
		log_bff.Format(" * llx_id <- [%1d] \n", ll_index+1);
		log_msg += log_bff;
		log_bff.Format(" * log_id <- [%s] \n", log_id);
		log_msg += log_bff;
		log_bff.Format(" * sub_id <- [%s] \n", sub_id);
		log_msg += log_bff;

		Fnc__LOG_CTRL(log_msg);
	}

	sEXT_CH__LLx__UPPER_OBJ_MSG[ll_index]->Set__DATA(log_id);

	pLLx__OBJ_CTRL[ll_index]->Run__OBJECT(CMMD__PUMP);
	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD
::SCH_CALL__LLx_PUMP(const int ll_index,
					 const CString& log_id)
{
	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "SCH_CALL__LLx_PUMP() ... \n";
		log_bff.Format(" * llx_id <- [%1d] \n", ll_index+1);
		log_msg += log_bff;
		log_bff.Format(" * log_id <- [%s] \n", log_id);
		log_msg += log_bff;

		Fnc__LOG_CTRL(log_msg);
	}

	sEXT_CH__LLx__UPPER_OBJ_MSG[ll_index]->Set__DATA(log_id);

	return pLLx__OBJ_CTRL[ll_index]->Call__OBJECT(CMMD__PUMP);
}


//-----------------------------------------------------------------------------------------
int  CObj_Fnc__DUAL_ARM_STD::
SCH__CHECK_PICK_MODULE__READY(CII_OBJECT__VARIABLE* p_variable,
							  const bool ex_flag,
					          const CString& para_module,const CString& para_slot,
							  const int maint_flag)
{
	DECLARE__EXT_CTRL(p_variable);

	// TMC CHM ...
	{
		if(TMC_CHM__Is_Available() < 0)
		{
			return -1;
		}

		if(maint_flag > 0)
		{
			if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
			{
				if(TMC_CHM__Is_VAC() < 0)
				{
					if(pTMC_CHM__OBJ_CTRL->Call__OBJECT(CMMD__PUMP) < 0)
					{
						return -1;
					}
				}
			}
			else
			{
				if(TMC_CHM__Is_ATM() < 0)
				{
					if(pTMC_CHM__OBJ_CTRL->Call__OBJECT(CMMD__VENT) < 0)
					{
						return -1;
					}
				}
			}
		}
	}

	// ...
	int ll_i = Get__LLx_INDEX(para_module);
	if(ll_i >= 0)
	{
		CString log_id = "SCH__CHECK_PICK_MODULE__READY()";

		CString sch_name;
		sch_name.Format("%s-%s", para_module,para_slot);

		if(SCH__PMx_JOB_START_READY(sch_name, log_id) < 0)
		{
			return -1;
		}

		if(LLx__Is_Available(ll_i) < 0)
		{
			return -1;
		}

		if(maint_flag > 0)
		{
			SCH__LLx_PUMP(ll_i, p_variable,1);
		}

		if(SCH__LLx_PREPMATER(ll_i, para_slot) < 0)
		{
			return -1;
		}
	}
	else
	{
		int i = SCH__CHECK_PM_INDEX(para_module);

		if(i >= 0)
		{
			if(PMx__Is_Idle(i) < 0)
			{

				return -1;
			}

			if(maint_flag > 0)
			{
				if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
				{
					if(PMx__Is_VAC(i) < 0)
					{
						if(pPMx__OBJ_CTRL[i]->Call__OBJECT(CMMD__PUMP) < 0)
						{
							return -1;
						}
					}
				}
				else 
				{
					if(PMx__Is_ATM(i) < 0)
					{
						if(pPMx__OBJ_CTRL[i]->Call__OBJECT(CMMD__VENT) < 0)
						{
							return -1;
						}
					}
				}
			}

			if(ex_flag == false)
			{
				if(maint_flag < 0)
				{
					if(xCH__PMx__X_PICK_FLAG[i]->Check__DATA("YES") < 0)
					{
						if(SCH__PMx_PICK_READY(i,para_slot) < 0)
						{
							return -1;
						}
					}
				}
				else
				{
					if(SCH__PMx_PICK_READY(i,para_slot) < 0)
					{
						return -1;
					}
				}
			}
			else
			{
				if(maint_flag < 0)
				{
					if(xCH__PMx__X_PICK_FLAG[i]->Check__DATA("YES") < 0)
					{
						if(SCH__PMx_XPICK_READY(i,para_slot) < 0)
						{
							return -1;
						}
					}
				}
				else
				{
					if(SCH__PMx_XPICK_READY(i,para_slot) < 0)
					{
						return -1;
					}
				}
			}
		}
	}

	return 1;
}
int  CObj_Fnc__DUAL_ARM_STD:: 
SCH__CHECK_PICK_MODULE__COMPLETE(CII_OBJECT__VARIABLE* p_variable,
								 CII_OBJECT__ALARM* p_alarm,
								 const bool ex_flag,
						         const CString& para_module,
								 const CString& para_slot,
								 const CString& from_sch_name,
								 const int maint_flag)
{
	CStringArray l_from_sch;
	l_from_sch.Add(from_sch_name);

	return SCH__CHECK_PICK_MODULE__COMPLETE(p_variable,
											p_alarm,
											ex_flag,
											para_module,
											para_slot,
											l_from_sch,
											maint_flag);
}
int  CObj_Fnc__DUAL_ARM_STD:: 
SCH__CHECK_PICK_MODULE__COMPLETE(CII_OBJECT__VARIABLE* p_variable,
								 CII_OBJECT__ALARM* p_alarm,
								 const bool ex_flag,
								 const CString& para_module,
								 const CString& para_slot,
								 const CStringArray& l_from_sch,
								 const int maint_flag)
{
	DECLARE__EXT_CTRL(p_variable);

	int ll_i = Get__LLx_INDEX(para_module);
	if(ll_i >= 0)
	{
		if(xEXT_CH__SCH__WAC_WAFER_POSITION->Check__DATA(STR__PMx) < 0)
		{
			iFRONT_WAC_FLAG = 1;
		}

		if(SCH__LLx_COMPMATER(ll_i, para_slot, maint_flag) < 0)
		{
			return -1;
		}

		SCH__LBx__DLEAY_TIME();

		if(maint_flag < 0)
		{
			int i_limit = l_from_sch.GetSize();
			for(int i=0; i<i_limit; i++)
			{
				CStringArray l_llx;
				CStringArray l_prc;

				CString sch_name = l_from_sch[i];
				xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_name, l_llx,l_prc);

				if(Check__LLx_NAME(l_llx) > 0)
				{
					xSCH_MATERIAL_CTRL->Clear__CURRENT_PROCESS(sch_name);
				}
			}
		}
	}
	else
	{
		int k_limit = l_from_sch.GetSize();
		for(int k=0; k<k_limit; k++)
		{
			CString from_sch = l_from_sch[k];

			int pm_i = SCH__CHECK_PM_INDEX(from_sch);
			if(pm_i < 0)		continue;

			if(ex_flag == false)
			{
				if(SCH__PMx_PICK_COMPLETE(pm_i, para_slot) < 0)
				{
					return -1;
				}

				if(maint_flag < 0)
				{
					if(xCH__PMx__NEXT_PROCESS[pm_i]->Check__DATA("GOTO_MAINT") > 0)
					{
						SCH__PMx_NEXT_PROC_START(pm_i);
					}
					else
					{						
						int pmc_id = pm_i + 1;
						CString cln_module;
						CString cln_recipe;

						int cln_flag 
							= xSCH_MATERIAL_CTRL->Get__POST_CLN_In_PMC(from_sch,
																	   pmc_id,
																	   cln_module,
																	   cln_recipe);

						if(cln_recipe.GetLength() < 1)
						{
							cln_flag = -1;
						}

						if(cln_flag > 0)
						{
							// POST-RCP ...
							if(dEXT_CH__POST_RCP_CFG_PMx_USE[pm_i]->Check__DATA(STR__YES) > 0)
							{
								int active__pmx_post = -1;
								int cur_count = -1;

								CString ch_data = sEXT_CH__PMx__CUR_POST_COUNT[pm_i]->Get__STRING();
								if(ch_data.GetLength() > 0)			
								{
									cur_count = atoi(ch_data);
								}
	
								if(cur_count < 0)
								{
									active__pmx_post = 1;
								}
								else
								{
									int cfg_count = (int) aEXT_CH__POST_RCP_CFG_PMx_WAFER_COUNT[pm_i]->Get__VALUE();

									if(cfg_count == 0)
									{
										if(cur_count == 0)
										{
											active__pmx_post = 1;
										}
									}
									else if(cfg_count == 1)
									{
										active__pmx_post = 1;
									}
									else if(cfg_count > 1)
									{
										if(cur_count >= cfg_count)
										{
											active__pmx_post = 1;
										}
									}
								}

								if(active__pmx_post > 0)
								{
									cln_flag = 1;

									sEXT_CH__PMx__CUR_POST_COUNT[pm_i]->Set__DATA("0");
								}
								else
								{
									cln_flag = -1;
								}
							}
							else
							{
								cln_flag = -1;
							}
						}

						if(cln_flag > 0)
						{
							int flag = SCH__PMx_POST_CLN_START(pm_i, cln_recipe);
							if(flag < 0)		return -1;
						}
						else
						{
							if(PMx__Check_Next_Process(pm_i, p_alarm) > 0)
							{
								int flag = SCH__PMx_NEXT_PROC_START(pm_i);
								if(flag < 0)		return -1;
							}
						}

						// ...
					}
				}
			}
			else
			{
				if(SCH__PMx_XPICK_COMPLETE(pm_i, para_slot) < 0)
				{
					return -1;
				}

				if(maint_flag < 0)
				{
					if(xCH__PMx__NEXT_PROCESS[pm_i]->Check__DATA("GOTO_MAINT") > 0)
					{
						SCH__PMx_NEXT_PROC_START(pm_i);
					}
				}
			}

			if(maint_flag < 0)
			{
				xSCH_MATERIAL_CTRL->Clear__CURRENT_PROCESS(from_sch);
			}

			// POST-COUNT ...
			{
				CString var_data = sEXT_CH__PMx__CUR_POST_COUNT[pm_i]->Get__STRING();
				int cur_count = atoi(var_data) + 1;
					
				var_data.Format("%1d", cur_count);
				sEXT_CH__PMx__CUR_POST_COUNT[pm_i]->Set__DATA(var_data);
			}
		}
	}

	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD:: 
SCH__CHECK_PLACE_MODULE__READY(CII_OBJECT__VARIABLE* p_variable,
							   const bool ex_flag,
							   const CString& arm_type,
							   const CString& para_module,
							   const CString& para_slot,
							   const int maint_flag)
{
	DECLARE__EXT_CTRL(p_variable);

	// TMC CHM ...
	{
		if(TMC_CHM__Is_Available() < 0)
		{
			return -1;
		}

		if(maint_flag > 0)
		{
			if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
			{
				if(TMC_CHM__Is_VAC() < 0)
				{
					if(pTMC_CHM__OBJ_CTRL->Call__OBJECT(CMMD__PUMP) < 0)
					{
						return -1;
					}
				}
			}
			else
			{
				if(TMC_CHM__Is_ATM() < 0)
				{
					if(pTMC_CHM__OBJ_CTRL->Call__OBJECT(CMMD__VENT) < 0)
					{
						return -1;
					}
				}
			}
		}
	}

	// ...
	int ll_i = Get__LLx_INDEX(para_module);
	if(ll_i >= 0)
	{
		if(LLx__Is_Available(ll_i) < 0)
		{
			return -1;
		}

		if(maint_flag > 0)
		{
			SCH__LLx_PUMP(ll_i, p_variable,1);
		}

		if(SCH__LLx_PREPMATER(ll_i, para_slot) < 0)
		{
			return -1;
		}
	}
	else
	{
		int i = SCH__CHECK_PM_INDEX(para_module);

		if(i >= 0)
		{
			if(PMx__Is_Available(i) < 0)
			{
				return -1;
			}

			if(maint_flag > 0)
			{
				if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
				{
					if(PMx__Is_VAC(i) < 0)
					{
						if(pPMx__OBJ_CTRL[i]->Call__OBJECT(CMMD__PUMP) < 0)	
						{
							return -1;
						}
					}
				}
				else 
				{
					if(PMx__Is_ATM(i) < 0)
					{
						if(pPMx__OBJ_CTRL[i]->Call__OBJECT(CMMD__VENT) < 0)
						{
							return -1;
						}
					}
				}
			}

			if(maint_flag < 0)
			{
				CString log_id = "SCH__CHECK_PLACE_MODULE__READY()";

				if(SCH__PMx_JOB_START_READY(i, arm_type,log_id) < 0)
				{
					return -1;
				}
			}

			// ...
			CString lpx_portid;
			CString lpx_slotid;
			CString lpx_cid;

			if(maint_flag < 0)
			{
				IDS__SCH_MATERIAL_INFO db_info;
				xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(arm_type,db_info);

				int port_id = db_info.iSRC__PTN;
				int slot_id = db_info.iSRC__STN;

				lpx_portid.Format("%1d", port_id);
				lpx_slotid.Format("%1d", slot_id);
				xSCH_MATERIAL_CTRL->Get__LPx_CID(port_id, lpx_cid);

				// PRE-RCP ...
				if(dEXT_CH__PRE_RCP_CFG_PMx_USE[i]->Check__DATA(STR__YES) > 0)
				{
					int active__pmx_pre = -1;
					int cur_count = -1;

					CString ch_data = sEXT_CH__PMx__CUR_PRE_COUNT[i]->Get__STRING();
					if(ch_data.GetLength() > 0)			
					{
						cur_count = atoi(ch_data);
					}
					
					if(cur_count < 0)
					{
						active__pmx_pre = 1;
					}
					else
					{
						int cfg_count = (int) aEXT_CH__PRE_RCP_CFG_PMx_WAFER_COUNT[i]->Get__VALUE();

						if(cfg_count == 0)
						{
							if(cur_count == 0)
							{
								active__pmx_pre = 1;
							}
						}
						else if(cfg_count == 1)
						{
							active__pmx_pre = 1;
						}
						else if(cfg_count > 1)
						{
							if(cur_count >= cfg_count)
							{
								active__pmx_pre = 1;
							}
						}
					}

					if(active__pmx_pre > 0)
					{
						CStringArray l_pre_pmc;
						CStringArray l_pre_rcp;

						xSCH_MATERIAL_CTRL->Get__PRE_RCP_INFO(port_id,slot_id, l_pre_pmc,l_pre_rcp);

						int t_limit = l_pre_pmc.GetSize();
						int t;

						for(t=0; t<t_limit; t++)
						{
							CString rcp_pmc = l_pre_pmc[t];
							CString rcp_pre = l_pre_rcp[t];

							if(para_module.CompareNoCase(rcp_pmc) != 0)
							{
								continue;
							}
							if(rcp_pre.GetLength() < 1)
							{
								break;;
							}

							// ...
							xCH__PMx__PRC_PRE_RECIPE[i]->Set__DATA(rcp_pre);
							xCH__PMx__PROCESS_RECIPE[i]->Set__DATA(rcp_pre);

							if(pPMx__OBJ_CTRL[i]->Call__OBJECT("AUTO_PRE_RCP") < 0)
							{
								return -1;
							}

							sEXT_CH__PMx__CUR_PRE_COUNT[i]->Set__DATA("0");
							break;
						}
					}
				}
			}

			if(ex_flag == false)
			{
				if(maint_flag < 0)
				{
					if(xCH__PMx__X_PLACE_FLAG[i]->Check__DATA("YES") < 0)
					{
						if(SCH__PMx_PLACE_READY(i,para_slot,lpx_portid,lpx_slotid,lpx_cid) < 0)
						{
							return -1;
						}
					}
				}
				else
				{
					if(SCH__PMx_PLACE_READY(i,para_slot,lpx_portid,lpx_slotid,lpx_cid) < 0)
					{
						return -1;
					}
				}
			}
			else
			{
				if(maint_flag < 0)
				{
					if(xCH__PMx__X_PLACE_FLAG[i]->Check__DATA("YES") < 0)
					{
						if(SCH__PMx_XPLACE_READY(i,para_slot,lpx_portid,lpx_slotid,lpx_cid) < 0)
						{
							return -1;
						}
					}
				}
				else
				{
					if(SCH__PMx_XPLACE_READY(i,para_slot,lpx_portid,lpx_slotid,lpx_cid) < 0)
					{
						return -1;
					}
				}
			}
		}
	}

	return 1;
}
int  CObj_Fnc__DUAL_ARM_STD:: 
SCH__CHECK_PLACE_MODULE__COMPLETE(CII_OBJECT__VARIABLE* p_variable,
								  const bool ex_flag,
								  const CString& arm_type,
								  const CString& para_module,
								  const CString& para_slot,
								  const int maint_flag)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	int act_check = -1;

	// LLx ....
	if(act_check < 0)
	{
		CString var_data;

		int ll_i = Get__LLx_INDEX(para_module);
		if(ll_i >= 0)
		{
			act_check = 1;

			var_data.Format("%1d", ++iLBx_OUT_COUNT);
			xEXT_CH__LLx__OUT_COUNT[ll_i]->Set__DATA(var_data);

			if(SCH__LLx_COMPMATER(ll_i, para_slot, maint_flag) < 0)
			{
				return -1;
			}
		}
	}

	// PMx ...
	if(act_check < 0)
	{
		CStringArray l_arm_name;
		CUIntArray   l_pm_index;

		if(para_module.CompareNoCase("PM12") == 0)
		{
			l_arm_name.Add("A");
			l_arm_name.Add("B");

			l_pm_index.Add(0);
			l_pm_index.Add(1);
		}
		else if(para_module.CompareNoCase("PM34") == 0)
		{
			l_arm_name.Add("A");
			l_arm_name.Add("B");

			l_pm_index.Add(2);
			l_pm_index.Add(3);
		}
		else if(para_module.CompareNoCase("PM56") == 0)
		{
			l_arm_name.Add("A");
			l_arm_name.Add("B");

			l_pm_index.Add(4);
			l_pm_index.Add(5);
		}
		else
		{
			l_arm_name.Add(arm_type);

			int pm_i = SCH__CHECK_PM_INDEX(para_module);
			if(pm_i >= 0)		l_pm_index.Add(pm_i);
		}

		int i_limit = l_pm_index.GetSize();
		for(int i=0; i<i_limit; i++)
		{			
			int pm_i = l_pm_index[i];
			if(pm_i < 0)		continue;

			CString arm_name = l_arm_name[i];

			_SCH__PROC_PMC_START(p_variable, arm_name, para_slot, pm_i, maint_flag);

			act_check = 1;
		}
	}

	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD::
_SCH__PROC_PMC_START(CII_OBJECT__VARIABLE* p_variable, 
					 const CString& arm_type, 
					 const CString& para_slot,
					 const int pm_i, 
					 const int maint_flag)
{
	CString var_data;

	if(maint_flag < 0)
	{
		IDS__SCH_MATERIAL_INFO ds_info;
		xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(arm_type, ds_info);

		// ...
		int ptn = ds_info.iSRC__PTN;
		int dummy_cln_flag = -1;

		if(xSCH_MATERIAL_CTRL->Check__DUMMY_PORT(ptn) > 0)
		{
			if(ds_info.sLOT_ID.CompareNoCase("DUMMY_PROCESS") != 0)
			{
				dummy_cln_flag = 1;
			}
		}

		if(dummy_cln_flag > 0)
		{
			if(SCH__PMx_PLACE_COMPLETE(pm_i, para_slot) < 0)
			{
				return -1;
			}

			if(ds_info.sLOT_ID.CompareNoCase("DUMMY_CLEAN") == 0)
			{
				SCH__PMx_DUMMY_CLN_START(pm_i);
			}
			else
			{
				SCH__PMx_CLN_START(pm_i);
			}
		}
		else
		{
			int pmc_id = pm_i + 1;
			int lp_slotid  = ds_info.iSRC__STN;
			CString recipe = ds_info.sCUR_RECIPE;

			// ...
			{
				xSCH_MATERIAL_CTRL->Clear__MATERIAL_INFO__INTO_PMC(pmc_id);

				xSCH_MATERIAL_CTRL->Set__MATERIAL_INFO__INTO_PMC(pmc_id,
																 1,
																 ptn,
																 lp_slotid);
			}

			// ...
			var_data.Format("%1d", ++iPMx_IN_COUNT);
			xCH__PMx__IN_COUNT[pm_i]->Set__DATA(var_data);

			// PRE-COUNT ...
			{
				var_data = sEXT_CH__PMx__CUR_PRE_COUNT[pm_i]->Get__STRING();
				int cur_count = atoi(var_data) + 1;
				var_data.Format("%1d", cur_count);
				sEXT_CH__PMx__CUR_PRE_COUNT[pm_i]->Set__DATA(var_data);
			}

			int flag = SCH__PMx_PRO_START_EX(pm_i,
											 para_slot,
											 recipe,
											 ds_info.sLOT_ID,
											 ds_info.sMATERIAL_ID);

			if(flag < 0)
			{
				return -1;
			}
		}
	}
	else
	{
		if(SCH__PMx_PLACE_COMPLETE(pm_i, para_slot) < 0)
		{
			return -1;
		}
	}
	
	return 1;
}


//------------------------------------------------------------------------------------------------
int  CObj_Fnc__DUAL_ARM_STD::SCH__LBx__DLEAY_TIME()
{
	if(xCH_CFG__PICK_DELAY_FLAG->Check__DATA("ENABLE") > 0)
	{
		CString var_data;
		int count;

		xCH_CFG__PICK_COUNT_FROM_LBx->Get__DATA(var_data);
		count = atoi(var_data) + 1;
		var_data.Format("%1d",count);
		xCH_CFG__PICK_COUNT_FROM_LBx->Set__DATA(var_data);

		//
		double delay_time = 0;

		switch(count)
		{
			case 1:
				xCH_CFG__PICK_DELAY_FIRST_TIME->Get__DATA(var_data);
				delay_time = atof(var_data);
				break;

			case 2:
				xCH_CFG__PICK_DELAY_SECOND_TIME->Get__DATA(var_data);
				delay_time = atof(var_data);
				break;

			case 3:
				xCH_CFG__PICK_DELAY_THIRD_TIME->Get__DATA(var_data);
				delay_time = atof(var_data);
				break;

			default:
				xCH_CFG__PICK_DELAY_REMAIN_TIME->Get__DATA(var_data);
				delay_time = atof(var_data);
				break;
		}

		xTIMER_CTRL__LLx_PICK_DELAY->START__COUNT_DOWN(delay_time);
	}
	else
	{
		xTIMER_CTRL__LLx_PICK_DELAY->STOP();

		xCH_CFG__PICK_DELAY_TIME->Set__DATA("0");
	}

	return 1;
}

int  CObj_Fnc__DUAL_ARM_STD::
SCH__LBx__CHECK_1_SLOT_ALL_MODE(const int llx_id)
{
	int ref_i = llx_id - 1;
	int ll_i;

	for(ll_i=0; ll_i<iLLx_LIMIT; ll_i++)
	{
		if(llx_id > 0)
		{
			if(ref_i != ll_i)
			{
				continue;
			}
		}

		if(xEXT_CH__SCH_DB_LLx_USE_FLAG[ll_i]->Check__DATA(STR__ENABLE) > 0)
		{
			if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ALL) > 0)	
			{
				int slot_count = LLx__Get_Size__All_Slot_Status(ll_i);

				if(slot_count == 1)		return 1;
				return -1;
			}
		}
	}

	return -1;
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__LBx__CHECK_ONLY_MODE()
{
	for(int ll_i=0; ll_i<iLLx_LIMIT; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_INPUT) > 0)
		{
			return 1;
		}
	}
	return -1;
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__LBx__CHECK_EMPTY_OF_ONLY_OUTPUT()
{
	for(int ll_i=0; ll_i<iLLx_LIMIT; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) < 0)
			continue;

		if(LLx__Check_Empty__OutSlot(ll_i) > 0)
			return 1;
	}
	return -1;
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__LBi__CHECK_InSLOT_OCCUPIED()
{
	for(int ll_i=0; ll_i<iLLx_LIMIT; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) < 0)
		{
			int ll_id = ll_i + 1;
			int slot_id;

			if(SCH__LBx__CHECK_1_SLOT_ALL_MODE(ll_id) > 0)
			{
				if(LLx__Get_Occupied__InSlot_With_1_Slot_All_Mode(ll_i, slot_id) > 0)
				{
					return 1;
				}
			}
			else
			{
				if(LLx__Get_Occupied__InSlot(ll_i, slot_id) > 0)
				{
					return 1;
				}
			}
		}
	}

	return -1;
}

//
int  CObj_Fnc__DUAL_ARM_STD::
SCH__LLx_CHECK_PRESSURE(const int ll_index,
						CII_OBJECT__VARIABLE *p_variable,
						CII_OBJECT__ALARM *p_alarm,
						const int check_mode)
{
	if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
	{
		if(LLx__Is_VAC(ll_index) > 0)		return 1;

		LLx__Update_PRESSURE(ll_index);

		if(LLx__Is_VAC(ll_index) > 0)		return 1;
	}
	else
	{
		if(LLx__Is_ATM(ll_index) > 0)		return 1;

		LLx__Update_PRESSURE(ll_index);
		
		if(LLx__Is_ATM(ll_index) > 0)		return 1;
	}

	if(check_mode > 0)
	{
		CString cfg_mode;
		xEXT_CH__CFG__PRESSURE_CHECK_MODE->Get__DATA(cfg_mode);

		if((cfg_mode.CompareNoCase(STR__ALARM)    == 0)
		|| (cfg_mode.CompareNoCase(STR__RECOVERY) == 0)
		|| (cfg_mode.CompareNoCase(STR__ONLY_RECOVERY) == 0))
		{
			if(cfg_mode.CompareNoCase(STR__ONLY_RECOVERY) != 0)
			{
				int alm_id = ALID__JOB_ERROR__LLx__CHECK_VAC_PRESSURE;
				CString alm_msg;
				CString r_act;

				alm_msg.Format("Please, check the pressure of LL%1d !", ll_index+1);

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
			}

			if((cfg_mode.CompareNoCase(STR__RECOVERY) == 0)
			|| (cfg_mode.CompareNoCase(STR__ONLY_RECOVERY) == 0))
			{
				SCH__LLx_PUMP(ll_index, p_variable);		
			}
		}
	}
	return -1;
}

int  CObj_Fnc__DUAL_ARM_STD::
SCH__LLx_PUMP(const int ll_index,
			  CII_OBJECT__VARIABLE *p_variable,
			  const int seq_flag)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	CString log_id;
	log_id.Format("SCH__LLx_PUMP(%1d) ...", ll_index);

	if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
	{
		if(LLx__Is_VAC(ll_index) < 0)
		{
			if(seq_flag < 0)
			{
				SCH_RUN__LLx_PUMP(ll_index, log_id, "1");
			}
			else
			{
				if(SCH_CALL__LLx_PUMP(ll_index, log_id) < 0)
				{
					return -1;
				}
			}
		}
	}
	else
	{
		if(LLx__Is_ATM(ll_index) < 0)
		{
			if(seq_flag < 0)
			{
				SCH_RUN__LLx_VENT(ll_index, log_id, "11");
			}
			else
			{
				if(SCH_CALL__LLx_VENT(ll_index, log_id) < 0)
				{
					return -1;
				}
			}
		}
	}

	return 1;
}


//------------------------------------------------------------------------------------------------
int  CObj_Fnc__DUAL_ARM_STD::
SCH__LLx_PREPMATER(const int ll_index, const CString& str_slot)
{
	if(xCH_CFG__SCH_LLx_PREPMATER_USE->Check__DATA(STR__ENABLE) < 0)
	{
		return 1;
	}
	if(xEXT_CH__LLx__CFG_PREPMATER_USE[ll_index]->Check__DATA(STR__ENABLE) < 0)
	{
		return 1;
	}

	if(pLLx__OBJ_CTRL[ll_index] == NULL)
	{
		return -1;
	}

	// ...
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(str_slot);

	return pLLx__OBJ_CTRL[ll_index]->Call__OBJ_MODE("PREPMATER", l_para);
}

int  CObj_Fnc__DUAL_ARM_STD::
SCH__LLx_COMPMATER(const int ll_index, const CString& str_slot, const int main_flag)
{
	if(xCH_CFG__SCH_LLx_COMPMATER_USE->Check__DATA(STR__ENABLE) < 0)
	{
		return 1;
	}
	if(xEXT_CH__LLx__CFG_COMPMATER_USE[ll_index]->Check__DATA(STR__ENABLE) < 0)
	{
		return 1;
	}

	if(pLLx__OBJ_CTRL[ll_index] == NULL)
	{
		return -1;
	}

	// ...
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(str_slot);

	if(main_flag > 0)
	{
		return pLLx__OBJ_CTRL[ll_index]->Call__OBJ_MODE(CMMD__COMPMATER_EX, l_para);
	}
	return pLLx__OBJ_CTRL[ll_index]->Run__OBJ_MODE(CMMD__COMPMATER_EX, l_para);
}


//------------------------------------------------------------------------------------------------
int  CObj_Fnc__DUAL_ARM_STD::
SCH__LLx_PROC(CII_OBJECT__VARIABLE *p_variable,
			  CII_OBJECT__ALARM *p_alarm,
			  const CString& ll_name,
			  const CString& ll_sch_name,
			  const CString& ll_rcp,
			  const CString& cmmd_proc)
{
	int ll_i = Get__LLx_INDEX(ll_name);
	if(ll_i < 0)		return -1;

	// COMPMATER CHECK ...
	{
		if(xCH_CFG__SCH_LLx_COMPMATER_USE->Check__DATA(STR__ENABLE) > 0)
			return 1;

		if(xEXT_CH__LLx__CFG_COMPMATER_USE[ll_i]->Check__DATA(STR__ENABLE) > 0)
			return 1;
	}

	// ...
	xSCH_MATERIAL_CTRL->Goto__NEXT_PROCESS(ll_sch_name);

	sEXT_CH__LLx__PARA_PROC_RECIPE_NAME[ll_i]->Set__DATA(ll_rcp);
	sEXT_CH__LLx__PARA_PROC_SCH_NAME[ll_i]->Set__DATA(ll_sch_name);

	return pLLx__OBJ_CTRL[ll_i]->Run__OBJECT(cmmd_proc);
}


//------------------------------------------------------------------------------------------------
#define  CODE__PMx_ERROR_CHECK									\
if(pm_i <  0)				return -1;							\
if(pm_i >= iPMx_SIZE)		return -1;							\
if(pPMx__OBJ_CTRL[pm_i] == NULL)	return -1;					\
if(PMx__Is_Idle(pm_i) < 0)			return -1;


int  CObj_Fnc__DUAL_ARM_STD::
SCH__PMx_PICK_READY(const int pm_i,const CString& str_slot)
{
	//.....
	CODE__PMx_ERROR_CHECK;

	//.....
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(str_slot);
	//
	
	return pPMx__OBJ_CTRL[pm_i]->Call__OBJ_MODE("PICK_READY",l_para);
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__PMx_XPICK_READY(const int pm_i,const CString& str_slot)
{
	//.....
	CODE__PMx_ERROR_CHECK;

	//.....
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(str_slot);
	//

	return pPMx__OBJ_CTRL[pm_i]->Call__OBJ_MODE("PICK_X_READY",l_para);
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__PMx_PICK_COMPLETE(const int pm_i,const CString& str_slot)
{
	//.....
	CODE__PMx_ERROR_CHECK;

	//.....
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(str_slot);
	//

	return pPMx__OBJ_CTRL[pm_i]->Call__OBJ_MODE("PICK_COMPLETE",l_para);
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__PMx_XPICK_COMPLETE(const int pm_i,const CString& str_slot)
{
	//.....
	CODE__PMx_ERROR_CHECK;

	//.....
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(str_slot);
	//

	return pPMx__OBJ_CTRL[pm_i]->Call__OBJ_MODE("PICK_X_COMPLETE",l_para);
}

//.....
int  CObj_Fnc__DUAL_ARM_STD::
SCH__PMx_PLACE_READY(const int pm_i,
					 const CString& str_slot,
					 const CString& lpx_port_id,
					 const CString& lpx_slot_id,
					 const CString& lpx_cid)
{
	//.....
	CODE__PMx_ERROR_CHECK;

	//.....
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(str_slot);
	l_para.Add(lpx_port_id);
	l_para.Add(lpx_slot_id);
	l_para.Add(lpx_cid);
	//

	return pPMx__OBJ_CTRL[pm_i]->Call__OBJ_MODE("PLACE_READY",l_para);
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__PMx_XPLACE_READY(const int pm_i,
					  const CString& str_slot,
					  const CString& lpx_port_id,
					  const CString& lpx_slot_id,
					  const CString& lpx_cid)
{
	//.....
	CODE__PMx_ERROR_CHECK;

	//.....
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(str_slot);
	l_para.Add(lpx_port_id);
	l_para.Add(lpx_slot_id);
	l_para.Add(lpx_cid);
	//

	return pPMx__OBJ_CTRL[pm_i]->Call__OBJ_MODE("PLACE_X_READY",l_para);
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__PMx_PLACE_COMPLETE(const int pm_i,const CString& str_slot)
{
	//.....
	CODE__PMx_ERROR_CHECK;

	//.....
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(str_slot);
	//

	return pPMx__OBJ_CTRL[pm_i]->Call__OBJ_MODE("PLACE_COMPLETE",l_para);
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__PMx_XPLACE_COMPLETE(const int pm_i,const CString& str_slot)
{
	//.....
	CODE__PMx_ERROR_CHECK;

	//.....
	CStringArray l_para;

	l_para.RemoveAll();
	l_para.Add(str_slot);
	//

	return pPMx__OBJ_CTRL[pm_i]->Call__OBJ_MODE("PLACE_X_COMPLETE",l_para);
}


// ...
int  CObj_Fnc__DUAL_ARM_STD:: 
SCH__PMx_PRO_START(const int pm_i,
				   const CString& recipe,
				   const CString& lot_id,
				   const CString& material_id)
{
	CODE__PMx_ERROR_CHECK;

	// ...
	CStringArray l_para;

	l_para.RemoveAll();

	l_para.Add(recipe);
	l_para.Add(lot_id);
	l_para.Add(material_id);

	return pPMx__OBJ_CTRL[pm_i]->Run__OBJ_MODE("AUTO_PRO",l_para);
}
int  CObj_Fnc__DUAL_ARM_STD:: 
SCH__PMx_PRO_START_EX(const int pm_i,
					  const CString& para_slot,
				      const CString& recipe,
				      const CString& lot_id,
				      const CString& material_id)
{
	CODE__PMx_ERROR_CHECK;

	//.....
	CStringArray l_para;

	//
	l_para.RemoveAll();

	l_para.Add(para_slot);
	l_para.Add(recipe);
	l_para.Add(lot_id);
	l_para.Add(material_id);
	//

	return pPMx__OBJ_CTRL[pm_i]->Run__OBJ_MODE("AUTO_PRO_EX",l_para);
}

int  CObj_Fnc__DUAL_ARM_STD:: 
SCH__PMx_POST_CLN_START(const int pm_i,
						const CString& cln_recipe)
{
	CODE__PMx_ERROR_CHECK;

	//.....
	CStringArray l_para;

	xCH__PMx__POST_CLEAN_RECIPE[pm_i]->Set__DATA(cln_recipe);
	xCH__PMx__PROCESS_RECIPE[pm_i]->Set__DATA(cln_recipe);
	return pPMx__OBJ_CTRL[pm_i]->Run__OBJ_MODE("POST_CLN",l_para);
}
int  CObj_Fnc__DUAL_ARM_STD:: 
SCH__PMx_CLN_START(const int pm_i)
{
	CODE__PMx_ERROR_CHECK;

	//.....
	CStringArray l_para;

	return pPMx__OBJ_CTRL[pm_i]->Run__OBJ_MODE("AUTO_CLN",l_para);
}
int  CObj_Fnc__DUAL_ARM_STD:: 
SCH__PMx_DUMMY_CLN_START(const int pm_i)
{
	CODE__PMx_ERROR_CHECK;

	//.....
	CStringArray l_para;

	return pPMx__OBJ_CTRL[pm_i]->Run__OBJ_MODE("AUTO_DUMMY_CLN",l_para);
}
int  CObj_Fnc__DUAL_ARM_STD:: 
SCH__PMx_NEXT_PROC_START(const int pm_i)
{
	CODE__PMx_ERROR_CHECK;

	//.....
	CStringArray l_para;

	return pPMx__OBJ_CTRL[pm_i]->Run__OBJ_MODE("NEXT_PROC",l_para);
}

int CObj_Fnc__DUAL_ARM_STD::  
SCH__CHECK_PM_INDEX(const CString& module_name)
{
	CString pm_name;
	int i;

	for(i=0;i<iPMx_SIZE;i++)
	{
		pm_name.Format("PM%1d",i+1);

		if(module_name.Find(pm_name) == 0)			return i;
	}
	return -1;
}

int CObj_Fnc__DUAL_ARM_STD::  
SCH__PMx_CHECK_PRESSURE(const int pm_i,
						CII_OBJECT__VARIABLE *p_variable,
						CII_OBJECT__ALARM *p_alarm)
{
	if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
	{
		if(PMx__Is_VAC(pm_i) > 0)		return 1;

		PMx__Update_PRESSURE(pm_i);
		if(PMx__Is_VAC(pm_i) > 0)		return 1;
	}
	else
	{
		if(PMx__Is_ATM(pm_i) > 0)		return 1;

		PMx__Update_PRESSURE(pm_i);
		if(PMx__Is_ATM(pm_i) > 0)		return 1;
	}

	// ...
	CString cfg_mode;
	xEXT_CH__CFG__PRESSURE_CHECK_MODE->Get__DATA(cfg_mode);

	if((cfg_mode.CompareNoCase(STR__ALARM)    == 0)
	|| (cfg_mode.CompareNoCase(STR__RECOVERY) == 0)
	|| (cfg_mode.CompareNoCase(STR__ONLY_RECOVERY) == 0))
	{
		if(cfg_mode.CompareNoCase(STR__ONLY_RECOVERY) != 0)
		{
			CString alarm_msg;
			CString r_act;

			alarm_msg.Format("Please, check PM%1d's vacuum pressure.",pm_i+1);

			p_alarm->Check__ALARM(ALID__JOB_ERROR__PMx__CHECK_VAC_PRESSURE,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(ALID__JOB_ERROR__PMx__CHECK_VAC_PRESSURE,alarm_msg);
		}

		if((cfg_mode.CompareNoCase(STR__RECOVERY) == 0)
	    || (cfg_mode.CompareNoCase(STR__ONLY_RECOVERY) == 0))
		{
			SCH__PMx_PUMP(pm_i,p_variable);
		}
	}

	return -1;
}
int  CObj_Fnc__DUAL_ARM_STD::
SCH__PMx_PUMP(const int pm_i,CII_OBJECT__VARIABLE *p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
	{
		if(PMx__Is_VAC(pm_i) < 0)
		{
			pPMx__OBJ_CTRL[pm_i]->Run__OBJECT(CMMD__PUMP);
		}
	}
	else
	{
		if(PMx__Is_ATM(pm_i) < 0)
		{
			pPMx__OBJ_CTRL[pm_i]->Run__OBJECT(CMMD__VENT);
		}
	}

	return 1;
}

int CObj_Fnc__DUAL_ARM_STD::  
SCH__CHECK_MATERIAL_CLEAR()
{
	// VAC_RB -> LBx
	if(VAC_RB__Check_Occupied__A_Arm() > 0)			return -1;
	if(VAC_RB__Check_Occupied__B_Arm() > 0)			return -1;

	// PMx -> LBx
	int i;

	for(i=0;i<iPMx_SIZE;i++)
	{
		if(xEXT_CH__CFG__PMx_USE[i]->Check__DATA("ENABLE") < 0)
		{
			continue;
		}

		if(PMx__Check_Occupied__SlotStatus(i) > 0)
		{
			return -1;
		}
	}

	return 1;
}

int CObj_Fnc__DUAL_ARM_STD::  
SCH__Get_Job_LP_List(CUIntArray& l_job_lp)
{
	CUIntArray l_db_lp;
	CUIntArray l_db_slot;

	// ...
	{
		xSCH_MATERIAL_CTRL->Get__ALL_LPx_INFO_FROM_DB(l_db_lp,l_db_slot);
		Macro__Get_Job_List_From_DB_List(l_db_lp,l_job_lp);
	}
	return 1;
}

