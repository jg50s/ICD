#include "StdAfx.h"
#include "CObj_Fnc__DUAL_ARM_STD.h"


#include "CMacro_Log.h"
extern CMacro_Log  mMacro_Log;


#define ROBOT_NAME			"VAC_RB1"


// ...
void CObj_Fnc__DUAL_ARM_STD
::Fnc__LOG_INFO(const CString& fnc_id,
				const CString& log_id,
				const CString& para_info)
{
	CString log_msg;
	CString log_bff;

	log_msg = "Fnc__LOG_INFO() ...\n";
	log_bff.Format(" * fnc_id <- [%s] \n", fnc_id);
	log_msg += log_bff;
	log_bff.Format(" * log_id <- [%s] \n", log_id);
	log_msg += log_bff;
	log_bff.Format(" * para_info <- [%s] \n", para_info);
	log_msg += log_bff;

	xAPP_LOG_CTRL->WRITE__LOG(log_msg);
}
void CObj_Fnc__DUAL_ARM_STD::
Fnc__LOG_PROC(const CString& fnc_id,
			  const CString& log_id,
			  const CString& sch_name,
			  const bool active_next)
{
	CString log_msg;
	CString log_bff;

	log_msg = "Fnc__LOG_PROC() ...\n";
	log_bff.Format(" * fnc_id <- [%s] \n", fnc_id);
	log_msg += log_bff;
	log_bff.Format(" * log_id <- [%s] \n", log_id);
	log_msg += log_bff;
	log_msg += " * Current Process Info ... \n";

	log_bff.Format("sch_name <- [%s] \n", sch_name);
	log_msg += log_bff;

	// ...
	CStringArray l_pm_name;
	CStringArray l_pm_rcp;

	if(active_next)		xSCH_MATERIAL_CTRL->Get__NEXT_PROCESS_INFO(sch_name, l_pm_name,l_pm_rcp);
	else				xSCH_MATERIAL_CTRL->Get__CUR_PROCESS_INFO(sch_name, l_pm_name,l_pm_rcp);

	// ...
	{
		int i_limit = l_pm_name.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			log_bff.Format(" ** %1d) [%s][%s] \n", i+1,l_pm_name[i],l_pm_rcp[i]);
			log_msg += log_bff;
		}
	}

	xAPP_LOG_CTRL->WRITE__LOG(log_msg);
}

void CObj_Fnc__DUAL_ARM_STD::
Datalog__Picking_Material(const CString& arm_type,
						  const CString& para_module,
						  const CString& para_slot,
						  const int ex_flag)
{
	/*
	CString sch_name;
	sch_name.Format("%s-%s",para_module,para_slot);

	IDS__SCH_MATERIAL_INFO db_info;
	xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(sch_name,db_info);

	// ...
	CString log_arm;
	CString log_module;
	CString material;
	CString lotid;
	CString recipe;

	log_arm.Format("%s_%s",ROBOT_NAME,arm_type);

	int ll_i = Get__LLx_INDEX(para_module);
	if(ll_i >= 0)		log_module.Format("%s_%s", para_module,para_slot);
	else				log_module = para_module;

	material.Format("P%1d:%002d",db_info.iSRC__PTN,db_info.iSRC__STN);
	lotid  = db_info.sLOT_ID;
	recipe = "";

	mMacro_Log.Log_Material_Picking(log_arm,log_module,material,lotid,recipe,ex_flag);
	*/
}
void CObj_Fnc__DUAL_ARM_STD::
Datalog__Picked_Material(const CString& arm_type,
						 const CString& para_module,
						 const CString& para_slot,
						 const int ex_flag)
{
	/*
	CString sch_name;
	sch_name.Format("%s-%s",para_module,para_slot);

	IDS__SCH_MATERIAL_INFO db_info;
	xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(sch_name,db_info);

	CString log_arm;
	CString log_module;
	CString material;
	CString lotid;
	CString recipe;

	log_arm.Format("%s_%s",ROBOT_NAME,arm_type);

	int ll_i = Get__LLx_INDEX(para_module);
	if(ll_i >= 0)			log_module.Format("%s_%s", para_module,para_slot);
	else					log_module = para_module;

	material.Format("P%1d:%002d",db_info.iSRC__PTN,db_info.iSRC__STN);
	lotid  = db_info.sLOT_ID;
	recipe = "";

	mMacro_Log.Log_Material_Pick(log_arm,log_module,material,lotid,recipe,ex_flag);
	*/
}

void CObj_Fnc__DUAL_ARM_STD::
Datalog__Placing_Material(const CString& arm_type,
						  const CString& para_module,
						  const CString& para_slot,
						  const int ex_flag)
{
	/*
	IDS__SCH_MATERIAL_INFO db_info;
	xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(arm_type,db_info);

	CString log_arm;
	CString log_module;
	CString material;
	CString lotid;
	CString recipe;

	log_arm.Format("%s_%s",ROBOT_NAME,arm_type);

	int ll_i = Get__LLx_INDEX(para_module);
	if(ll_i >= 0)			log_module.Format("%s_%s", para_module,para_slot);
	else					log_module = para_module;

	material.Format("P%1d:%002d",db_info.iSRC__PTN,db_info.iSRC__STN);
	lotid  = db_info.sLOT_ID;
	recipe = db_info.sCUR_RECIPE;

	mMacro_Log.Log_Material_Placing(log_arm,log_module,material,lotid,recipe,ex_flag);
	*/
}
void CObj_Fnc__DUAL_ARM_STD::
Datalog__Placed_Material(const CString& arm_type,
						 const CString& para_module,
						 const CString& para_slot,
						 const int ex_flag)
{
	/*
	IDS__SCH_MATERIAL_INFO db_info;
	xSCH_MATERIAL_CTRL->Get__MATERIAL_INFO(arm_type,db_info);

	CString log_arm;
	CString log_module;
	CString material;
	CString lotid;
	CString recipe;

	log_arm.Format("%s_%s",ROBOT_NAME,arm_type);

	int ll_i = Get__LLx_INDEX(para_module);
	if(ll_i >= 0)			log_module.Format("%s_%s", para_module,para_slot);
	else					log_module = para_module;

	material.Format("P%1d:%002d",db_info.iSRC__PTN,db_info.iSRC__STN);
	lotid  = db_info.sLOT_ID;
	recipe = db_info.sCUR_RECIPE;

	mMacro_Log.Log_Material_Place(log_arm,log_module,material,lotid,recipe,ex_flag);
	*/
}
