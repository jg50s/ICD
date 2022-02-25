#include "StdAfx.h"
#include "CObj_Phy__VIS_STD.h"

#include "Macro_Function.h"


// ...
int  CObj_Phy__VIS_STD::Call__PLACE_READY(CII_OBJECT__VARIABLE* p_variable)
{
	return xI_Module_Obj->Connect__Module_Obj("PLACE_READY");
}
int  CObj_Phy__VIS_STD::Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE* p_variable)
{
	return xI_Module_Obj->Connect__Module_Obj("PLACE_COMPLETE");
}

int  CObj_Phy__VIS_STD::Call__PICK_READY(CII_OBJECT__VARIABLE* p_variable)
{
	return xI_Module_Obj->Connect__Module_Obj("PICK_READY");
}
int  CObj_Phy__VIS_STD::Call__PICK_COMPLETE(CII_OBJECT__VARIABLE* p_variable)
{
	return xI_Module_Obj->Connect__Module_Obj("PICK_COMPLETE");
}

int  CObj_Phy__VIS_STD::Call__PRO_READY(CII_OBJECT__VARIABLE* p_variable)
{
	Set__Prc_Ready_Parameter(p_variable);

	return xI_Module_Obj->Connect__Module_Obj("PRO_READY");
}

int  Check__PM_ID(const CString& str_name)
{
	CString pmc_name;
	int i;

	for(i=0; i<CFG_PM_LIMIT; i++)
	{
		pmc_name.Format("PM%1d",i+1);

		if(str_name.Find(pmc_name,0) == 0)
		{
			return (i+1);
		}
	}
	return -1;
}
int  CObj_Phy__VIS_STD::Call__PRO_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	xI_SCH_MATERIAL_CTRL->Report__VIS_PROC_START(iVIS_ID);

	int flag = Sub__PRO_START(p_variable,p_alarm);

	xI_SCH_MATERIAL_CTRL->Report__VIS_PROC_END(iVIS_ID);
	return flag;
}
int  CObj_Phy__VIS_STD::Sub__PRO_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CStringArray l_sch_name;

	if(sSCH_NAME.GetLength() > 0)
	{
		CString sch_name;
		CString material_sts;
		int i;

		l_sch_name.RemoveAll();

		for(i=0; i<CFG_VIS__SLOT_MAX; i++)
		{
			xCH__SLOT_STATUS[i]->Get__DATA(material_sts);
			
			if(Macro__Check_Material_Status(material_sts) < 0)
			{
				continue;
			}

			sch_name.Format("%s-%1d",sSCH_NAME,i+1);
			l_sch_name.Add(sch_name);

			xI_SCH_MATERIAL_CTRL->Start__ACT_COMMAND(sch_name,"PROCESSING");
		}
	}

	int flag = xI_Module_Obj->Connect__Module_Obj("PRO_START");

	if(sSCH_NAME.GetLength() > 0)
	{
		int limit = l_sch_name.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			xI_SCH_MATERIAL_CTRL->End__ACT_COMMAND(l_sch_name[i],"PROCESSING");
		}
	}

	if(xI_SCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)		
	{
		return flag;
	}

	if(xCH__JUDGMENT->Check__DATA("OK") < 0)
	{
		CString data_result;
		xCH__JUDGMENT->Get__DATA(data_result);

		if(xCH_CFG__ALARM_BLOCKING_FLAG->Check__DATA("ENABLE") > 0)
		{
			CString pm_name;
			xCH__PM_NAME->Get__DATA(pm_name);

			CString msg;
			CString bff;

			msg.Format("Vision Judgment : %s\n\n",data_result);

			bff.Format("  [%s] : Abort All PMs\n",STR__ALL_ABORT);
			msg += bff;

			bff.Format("  [%s] : Abort \"%s\"\n",STR__PMx_ABORT,pm_name);
			msg += bff;

			bff.Format("  [%s]\n",STR__IGNORE);
			msg += bff;

			CString r_act;
			p_alarm->Popup__ALARM_With_MESSAGE(ALID__MATERIAL_JUDGEMENT,msg,r_act);

			if(r_act.CompareNoCase(STR__ALL_ABORT) == 0)
			{
				xI_SCH_MATERIAL_CTRL->Set__ALL_PMx_GoTo_MAINT();
			}
			else if(r_act.CompareNoCase(STR__PMx_ABORT) == 0)
			{
				int pm_id = Check__PM_ID(pm_name);

				xI_SCH_MATERIAL_CTRL->Set__PMx_GoTo_MAINT(pm_id);
			}
		}
		else
		{
			CString msg;
			CString r_act;

			msg.Format("Vision Judgment : %s\n",data_result);

			p_alarm->Check__ALARM(ALID__MATERIAL_JUDGEMENT_NON_BLOCKING,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(ALID__MATERIAL_JUDGEMENT_NON_BLOCKING,msg);
		}
	}

	return flag;
}

int CObj_Phy__VIS_STD
::Call__AUTO_PRO(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(Call__PRO_READY(p_variable) < 0)				return -1;
	if(Call__PRO_START(p_variable,p_alarm) < 0)		return -1;

	return 1;
}
int CObj_Phy__VIS_STD
::Call__AUTO_PRO_EX(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(Call__PLACE_COMPLETE(p_variable) < 0)		return -1;
	if(Call__PRO_READY(p_variable) < 0)				return -1;
	if(Call__PRO_START(p_variable,p_alarm) < 0)		return -1;

	if(xCH__CFG_DUAL_SLOT_USE_FLAG->Check__DATA("ENABLE") > 0)
	{
		if(Call__EXCHANGE_READY(p_variable,p_alarm) > 0)
		{
			xCH__PICK_READY_FLAG->Set__DATA("YES");
		}
	}
	else
	{
		if(Call__PICK_READY(p_variable) > 0)
		{
			xCH__PICK_READY_FLAG->Set__DATA("YES");
		}
	}
	return 1;
}

int  CObj_Phy__VIS_STD
::Call__EXCHANGE_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return xI_Module_Obj->Connect__Module_Obj("EXCHANGE_READY");
}
void CObj_Phy__VIS_STD
::Set__Prc_Ready_Parameter(CII_OBJECT__VARIABLE *p_variable)
{
	CStringArray l_para;
	CString para_data;

	int limit;
	int i;

	p_variable->Get__FNC_PARAMETER(l_para);
	limit = l_para.GetSize();

	for(i=0;i<limit;i++)
	{
		para_data = l_para[i];

		switch(i)
		{
			case 0:		// RECIPE
				xCH__RECIPE->Set__DATA(para_data);
				break;

			case 1:		// LOT ID
				xCH__LOTID->Set__DATA(para_data);
				break;

			case 2:		// MATERIAL ID
				xCH__MATERIALID->Set__DATA(para_data);
				break;

			case 3:		// PORT ID
				xCH__PORTID->Set__DATA(para_data);
				break;

			case 4:		// SLOT ID
				xCH__SLOTID->Set__DATA(para_data);
				break;

			case 5:		// PM ID
				xCH__PM_NAME->Set__DATA(para_data);

				// ...
				{
					CString str_pm_id;
					int pm_id = Check__PM_ID(para_data);

					str_pm_id.Format("%1d",pm_id);
					xCH__PM_ID->Set__DATA(str_pm_id);
				}
				break;
		}
	}

	// ...
	{
		CString log_msg;
		CString log_bff;
		CString var_data;

		log_msg = "Process Info\n";

		xCH__RECIPE->Get__DATA(var_data);
		log_bff.Format("Recipe : [%s]\n",var_data);
		log_msg += log_bff;

		xCH__LOTID->Get__DATA(var_data);
		log_bff.Format("LotId : [%s]\n",var_data);
		log_msg += log_bff;

		xCH__MATERIALID->Get__DATA(var_data);
		log_bff.Format("Material-ID : [%s]\n",var_data);
		log_msg += log_bff;

		xCH__PORTID->Get__DATA(var_data);
		log_bff.Format("Port-ID : [%s]\n",var_data);
		log_msg += log_bff;

		xCH__SLOTID->Get__DATA(var_data);
		log_bff.Format("Slot-ID : [%s]\n",var_data);
		log_msg += log_bff;

		xCH__PM_NAME->Get__DATA(var_data);
		log_bff.Format("PM Name : [%s]\n",var_data);
		log_msg += log_bff;

		xCH__PM_ID->Get__DATA(var_data);
		log_bff.Format("PM ID : [%s]\n",var_data);
		log_msg += log_bff;

		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}
}
