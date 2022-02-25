#include "StdAfx.h"
#include "CObj_Phy__ALx_STD.h"
#include "CObj_Phy__ALx_STD__DEF.h"

#include "Macro_Function.h"


//-------------------------------------------------------------------------
int  CObj_Phy__ALx_STD::Call__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__INIT);
}
int  CObj_Phy__ALx_STD::Call__ALIGN(CII_OBJECT__VARIABLE* p_variable)
{
	Set__PARAMETER(p_variable);

	// ...
	CStringArray l_sch_name;

	if(sSCH_NAME.GetLength() > 0)
	{
		CString sch_name;
		CString material_sts;
		int i;

		l_sch_name.RemoveAll();

		for(i=0; i<CFG_AL__SLOT_MAX; i++)
		{
			xCH__SLOT_STATUS[i]->Get__DATA(material_sts);
			
			if(Macro__Check_Material_Status(material_sts) < 0)
			{
				continue;
			}

			sch_name.Format("%s-%1d",sSCH_NAME,i+1);
			l_sch_name.Add(sch_name);

			xI_SCH_MATERIAL_CTRL->Start__ACT_COMMAND(sch_name,"ALIGN");
		}
	}

	// ...
	int flag = Fnc__MODULE_OBJ(p_variable, _CMMD__ALIGN);

	if((flag < 0)||(xCH__OBJ_STATUS->Check__DATA("MAINTMODE") > 0))
	{
		xCH__ALIGN_RETRY_FLAG->Set__DATA("YES");
	}

	if(sSCH_NAME.GetLength() > 0)
	{
		int limit = l_sch_name.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			xI_SCH_MATERIAL_CTRL->End__ACT_COMMAND(l_sch_name[i], "ALIGN");
		}
	}

	return flag;
}

int  CObj_Phy__ALx_STD::Call__PICK_READY(CII_OBJECT__VARIABLE* p_variable)
{
	Set__PARAMETER(p_variable);

	return Fnc__MODULE_OBJ(p_variable, _CMMD__PICK_READY);
}
int  CObj_Phy__ALx_STD::Call__PICK_COMPLETE(CII_OBJECT__VARIABLE* p_variable)
{
	Set__PARAMETER(p_variable);

	return Fnc__MODULE_OBJ(p_variable, _CMMD__PICK_COMPLETE);
}

int  CObj_Phy__ALx_STD::Call__PLACE_READY(CII_OBJECT__VARIABLE* p_variable)
{
	Set__PARAMETER(p_variable);

	return Fnc__MODULE_OBJ(p_variable, _CMMD__PLACE_READY);
}
int  CObj_Phy__ALx_STD::Call__PLACE_COMPLETE(CII_OBJECT__VARIABLE* p_variable)
{
	Set__PARAMETER(p_variable);

	return Fnc__MODULE_OBJ(p_variable, _CMMD__PLACE_COMPLETE);
}


//-------------------------------------------------------------------------
void CObj_Phy__ALx_STD::Set__PARAMETER(CII_OBJECT__VARIABLE* p_variable)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	{
		xCH__PARA_SLOT->Set__DATA("1");
		xCH__PARA_MATERIAL_TYPE->Set__DATA("UNKNOWN");
		xCH__PARA_MODULE_TYPE->Set__DATA("UNKNOWN");
	}

	// ...
	CStringArray l_para;
	CString para_data;

	p_ext_mode_ctrl->Get__FNC_PARAMETER(l_para);

	int limit = l_para.GetSize();
	int i;

	for(i=0; i<limit; i++)
	{
		para_data = l_para[i];
		
		if(para_data.GetLength() < 1)
		{
			continue;
		}

		if(i == 0)
		{
			xCH__PARA_SLOT->Set__DATA(para_data);
		}
		else if(i == 1)
		{
			xCH__PARA_MATERIAL_TYPE->Set__DATA(para_data);
		}
		else if(i == 2)
		{
			xCH__PARA_MODULE_TYPE->Set__DATA(para_data);
		}
	}
}
