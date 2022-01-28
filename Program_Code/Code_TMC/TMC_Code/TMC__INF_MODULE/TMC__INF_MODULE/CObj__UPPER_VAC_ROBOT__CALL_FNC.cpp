#include "StdAfx.h"
#include "CObj__UPPER_VAC_ROBOT.h"
#include "CObj__UPPER_VAC_ROBOT__DEF.h"

#include "Macro_Function.h"


//----------------------------------------------------------------------------------------------------
int  CObj__UPPER_VAC_ROBOT
::Call__SWAP_LBx(CII_OBJECT__VARIABLE* p_variable)
{
	CString para_module;
	CString para_pick_arm;
	CString para_pick_slot;
	CString para_place_arm;
	CString para_place_slot;

	xCH__PARA_MODULE->Get__DATA(para_module);
	xCH__PARA_PICK_ARM->Get__DATA(para_pick_arm);
	xCH__PARA_PICK_SLOT->Get__DATA(para_pick_slot);
	xCH__PARA_PLACE_ARM->Get__DATA(para_place_arm);
	xCH__PARA_PLACE_SLOT->Get__DATA(para_place_slot);

	// ...
	int state = 1;

	CII_EXT_OBJECT__CTRL  *pobj_lbx_ctrl;
	CII__VAR_DIGITAL_CTRL *pch_lbx_obj_sts;
	CII__VAR_DIGITAL_CTRL *pch_lbx_para_slot;

	// LLx ...
	int ll_i = Macro__CHECK_LLx_INDEX(para_module);
	if(ll_i >= 0)
	{
		pobj_lbx_ctrl = pLLx__OBJ_CTRL[ll_i];

		pch_lbx_obj_sts   = xEXT_CH__LLx__OBJ_STATUS[ll_i].Get__PTR();
		pch_lbx_para_slot = xEXT_CH__LLx__PREMATERIAL_SLOT[ll_i].Get__PTR();
	}
	else
	{
		return -1;
	}

	// VAC_ROBOT
	if(state > 0)
	{
		if((dEXT_CH__VAC_ROBOT__OBJ_STATUS->Check__DATA("STANDBY")  < 0)
		&& (dEXT_CH__VAC_ROBOT__OBJ_STATUS->Check__DATA("CTCINUSE") < 0))
		{
			state = -1;

			/*
			//----------------------------------------------
			CString title;
			CString msg;
			CString act_result;
	
			title = "VAC_RB's status is not CtcInUse  (1)";
			msg   = "VAC_RB's status must be CtcInUse (1)";

			ch_vac_status->Popup__ALARM_BOX(title,msg,"ABORT",act_result);
			//----------------------------------------------
			*/
		}
		else
		{
			dEXT_CH__VAC_ROBOT__OBJ_STATUS->Set__DATA("CTCINUSE");
		}
	}

	// LBx
	if(state > 0)
	{
		if((pch_lbx_obj_sts->Check__DATA("STANDBY")  < 0)
		&& (pch_lbx_obj_sts->Check__DATA("CTCINUSE") < 0))
		{
			state = -1;

			/*
			//----------------------------------------------
			CString title;
			CString msg;
			CString act_result;
	
			title = "LBA's status is not CtcInUse  (1)";
			msg   = "LBA's status must be CtcInUse (1)";

			pch_lbx_obj_sts->Popup__ALARM_BOX(title,msg,"ABORT",act_result);
			//----------------------------------------------
			*/
		}
		else
		{
			pch_lbx_obj_sts->Set__DATA("CTCINUSE");
		}
	}

	if(state > 0)
	{
		CString sub_mode;
		CString sub_log;

		//------------------------------------------------
		// PLACE SEQ
					
		// LBx : PREPMATER
		if(state > 0)
		{
			CString sub_module;
			CString sub_slot;

			pch_lbx_para_slot->Set__DATA(para_place_slot);
							
			//.....
			sub_mode   = "PREPMATER";
			sub_module = para_module;
			sub_slot   = para_place_slot;
							
			sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : %s] [%s] Started ... (%s)\n",
						   sub_module,sub_mode,sub_slot);

			xLOG_CTRL->WRITE__LOG(sub_log);
			//

			//.....
			state = pobj_lbx_ctrl->Call__OBJECT(sub_mode);

			if(state > 0)
			{
				sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : %s] [%s] Completed ... (%s)\n",
							   sub_module,sub_mode,sub_slot);
			}
			else
			{
				sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : %s] [%s] Aborted ... (%s)\n",
							   sub_module,sub_mode,sub_slot);
			}

			xLOG_CTRL->WRITE__LOG(sub_log);
		}
					
		// VAC_RB : X_PLACE
		if(state > 0)
		{
			CString sub_module;
			CString sub_slot;

			//.....
			dEXT_CH__VAC_ROBOT__PARA_ARM->Set__DATA(para_place_arm);
			dEXT_CH__VAC_ROBOT__PARA_MODULE->Set__DATA(para_module);
			dEXT_CH__VAC_ROBOT__PARA_SLOT->Set__DATA(para_place_slot);
						
			//.....
			sub_mode   = "XPLACE";
			sub_module = para_module;
			sub_slot   = para_place_slot;
							
			sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : VAC_RB] [%s] Started ... (%s,%s)\n",
						   sub_mode,sub_module,sub_slot);

			xLOG_CTRL->WRITE__LOG(sub_log);
			//

			//.....
			state = pVAC_ROBOT__OBJ_CTRL->Call__OBJECT(sub_mode);

			if(state > 0)
			{
				sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : VAC_RB] [%s] Completed ... (%s,%s)\n",
							   sub_mode,sub_module,sub_slot);
			}
			else
			{
				sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : VAC_RB] [%s] Aborted ... (%s,%s)\n",
							   sub_mode,sub_module,sub_slot);
			}

			xLOG_CTRL->WRITE__LOG(sub_log);
		}
					
		// LBx : COMPMATER 
		if(state > 0)
		{
			CString sub_module;
			CString sub_slot;

			pch_lbx_para_slot->Set__DATA(para_place_slot);
							
			//.....
			sub_mode   = "COMPMATER";
			sub_module = para_module;
			sub_slot   = para_place_slot;
							
			sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : %s] [%s] Started ... (%s)\n",
						   sub_module,sub_mode,sub_slot);

			xLOG_CTRL->WRITE__LOG(sub_log);
			//

			//.....
			state = pobj_lbx_ctrl->Call__OBJECT(sub_mode);

			if(state > 0)
			{
				sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : %s] [%s] Completed ... (%s)\n",
							   sub_module,sub_mode,sub_slot);
			}
			else
			{
				sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : %s] [%s] Aborted ... (%s)\n",
							   sub_module,sub_mode,sub_slot);
			}

			xLOG_CTRL->WRITE__LOG(sub_log);
		}
		//------------------------------------------------

		//------------------------------------------------
		// PICK SEQ

		// LBx : PREPMATER
		if(state > 0)
		{
			CString sub_module;
			CString sub_slot;

			pch_lbx_para_slot->Set__DATA(para_pick_slot);
							
			//.....
			sub_mode   = "PREPMATER";
			sub_module = para_module;
			sub_slot   = para_pick_slot;
							
			sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : %s] [%s] Started ... (%s)\n",
						   sub_module,sub_mode,sub_slot);

			xLOG_CTRL->WRITE__LOG(sub_log);
			//

			//.....
			state = pobj_lbx_ctrl->Call__OBJECT(sub_mode);

			if(state > 0)
			{
				sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : %s] [%s] Completed ... (%s)\n",
							   sub_module,sub_mode,sub_slot);
			}
			else
			{
				sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : %s] [%s] Aborted ... (%s)\n",
							   sub_module,sub_mode,sub_slot);
			}

			xLOG_CTRL->WRITE__LOG(sub_log);
		}
					
		// VAC_RB : PICK
		if(state > 0)
		{
			CString sub_module;
			CString sub_slot;

			//.....
			dEXT_CH__VAC_ROBOT__PARA_ARM->Set__DATA(para_pick_arm);
			dEXT_CH__VAC_ROBOT__PARA_MODULE->Set__DATA(para_module);
			dEXT_CH__VAC_ROBOT__PARA_SLOT->Set__DATA(para_pick_slot);
						
			//.....
			sub_mode   = "PICK";
			sub_module = para_module;
			sub_slot   = para_pick_slot;
							
			sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : VAC_RB] [%s] Started ... (%s,%s)\n",
						   sub_mode,sub_module,sub_slot);

			xLOG_CTRL->WRITE__LOG(sub_log);
			//

			//.....
			state = pVAC_ROBOT__OBJ_CTRL->Call__OBJECT(sub_mode);

			if(state > 0)
			{
				sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : VAC_RB] [%s] Completed ... (%s,%s)\n",
							   sub_mode,sub_module,sub_slot);
			}
			else
			{
				sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : VAC_RB] [%s] Aborted ... (%s,%s)\n",
							   sub_mode,sub_module,sub_slot);
			}

			xLOG_CTRL->WRITE__LOG(sub_log);
		}

		// LBx : COMPMATER
		if(state > 0)
		{
			CString sub_module;
			CString sub_slot;

			pch_lbx_para_slot->Set__DATA(para_pick_slot);
							
			//.....
			sub_mode   = "COMPMATER";
			sub_module = para_module;
			sub_slot   = para_pick_slot;
							
			sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : %s] [%s] Started ... (%s)\n",
						   sub_module,sub_mode,sub_slot);

			xLOG_CTRL->WRITE__LOG(sub_log);
			//

			//.....
			state = pobj_lbx_ctrl->Call__OBJECT(sub_mode);

			if(state > 0)
			{
				sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : %s] [%s] Completed ... (%s)\n",
							   sub_module,sub_mode,sub_slot);
			}
			else
			{
				sub_log.Format("[VAC_RB-LBx : SUB_INTERFACE : %s] [%s] Aborted ... (%s)\n",
							   sub_module,sub_mode,sub_slot);
			}

			xLOG_CTRL->WRITE__LOG(sub_log);
		}

		if(state < 0)
		{
			CString obj_status = "MAINTMODE";

			dEXT_CH__VAC_ROBOT__OBJ_STATUS->Set__DATA(obj_status);
			pch_lbx_obj_sts->Set__DATA(obj_status);
		}
		else
		{
			CString obj_status = "STANDBY";

			if(dEXT_CH__VAC_ROBOT__OBJ_STATUS->Check__DATA("CTCINUSE") > 0)
			{
				dEXT_CH__VAC_ROBOT__OBJ_STATUS->Set__DATA(obj_status);
			}

			if(pch_lbx_obj_sts->Check__DATA("CTCINUSE") > 0)
			{
				pch_lbx_obj_sts->Set__DATA(obj_status);
			}
		}
	}

	return state;
}

