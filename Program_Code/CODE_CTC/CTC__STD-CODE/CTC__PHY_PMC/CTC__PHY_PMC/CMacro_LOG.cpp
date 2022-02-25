#include "StdAfx.h"
#include "CMacro_LOG.h"


CMacro_LOG  mMacro_LOG;


// ...
CMacro_LOG::CMacro_LOG()
{
	//.....
	iINIT_LOG = -1;
}
CMacro_LOG::~CMacro_LOG()
{

}

// ...
int CMacro_LOG::Init_LOG()
{
	if(iINIT_LOG > 0)		return 1;
	iINIT_LOG = 1;

	xI_LOT_SUMMARY->Link__SERVICE_DB("");
	xI_MATERIAL_LOG->Link__SERVICE_DB("");

	return 1;
}

// ...
int CMacro_LOG::Get_DateTime(CString &date,CString &time)
{
	CTime t = CTime::GetCurrentTime();

	date.Format("%00004d_%002d_%002d", t.GetYear(),t.GetMonth(),t.GetDay());
	time.Format("%002d%002d%002d", t.GetHour(),t.GetMinute(),t.GetSecond());
	return 1;
}
int CMacro_LOG::Get_ArmType(const CString& arm)
{
	if(arm.CompareNoCase("ATM_RB1_A") == 0)		return 1;
	if(arm.CompareNoCase("ATM_RB1_B") == 0)		return 2;
	if(arm.CompareNoCase("ATM_RB2_A") == 0)		return 3;
	if(arm.CompareNoCase("ATM_RB2_B") == 0)		return 4;

	if(arm.CompareNoCase("VAC_RB1_A") == 0)		return 11;
	if(arm.CompareNoCase("VAC_RB1_B") == 0)		return 12;
	if(arm.CompareNoCase("VAC_RB2_A") == 0)		return 13;
	if(arm.CompareNoCase("VAC_RB2_B") == 0)		return 14;

	if(arm.CompareNoCase("EXT_ROBOT") == 0)		return 101;

	return -1;
}
int CMacro_LOG::Get_ModuleType(const CString& module)
{
	CString str_module;
	int	i;

	// PM1 ~ PM6 
	for(i=0;i<SCH_DB__PM_LIMIT;i++)
	{
		str_module.Format("PM%1d",i+1);
		if(str_module.CompareNoCase(module) == 0)		return (i+1);
	}

	// AL
	if((module.CompareNoCase("AL")  == 0)				
	|| (module.CompareNoCase("AL1") == 0))
	{
		return 11;
	}
	if(module.CompareNoCase("AL2") == 0)				return 12;

	// CL
	if(module.CompareNoCase("CL1") == 0)				return 21;
	if(module.CompareNoCase("CL2") == 0)				return 22;

	// LP1 ~ LP5
	for(i=0;i<SCH_DB__LP_LIMIT;i++)
	{
		str_module.Format("LP%1d",i+1);
		if(str_module.CompareNoCase(module) == 0)		return (i+31);
	}

	// LA & LB
	if(module.CompareNoCase("LA") == 0)					return 41;
	if(module.CompareNoCase("LB") == 0)					return 42;

	// LBA & LBB
	for(i=0;i<SCH_DB__LLx_SLOT_LIMIT;i++)
	{
		str_module.Format("LBA_%1d",i+1);
		if(str_module.CompareNoCase(module) == 0)		return (51+i);
	}
	for(i=0;i<SCH_DB__LLx_SLOT_LIMIT;i++)
	{
		str_module.Format("LBB_%1d",i+1);
		if(str_module.CompareNoCase(module) == 0)		return (61+i);
	}
	for(i=0;i<SCH_DB__LLx_SLOT_LIMIT;i++)
	{
		str_module.Format("LBC_%1d",i+1);
		if(str_module.CompareNoCase(module) == 0)		return (71+i);
	}
	for(i=0;i<SCH_DB__LLx_SLOT_LIMIT;i++)
	{
		str_module.Format("LBD_%1d",i+1);
		if(str_module.CompareNoCase(module) == 0)		return (81+i);
	}

	// EXTERNAL-ROBOT
	if(module.CompareNoCase("EXT_ROBOT") == 0)			return 101;

	return -1;
}

// ...
int CMacro_LOG
::Log_Material_Picking(const CString& arm,const CString& str_module,
					   const CString& material,const CString& lotid,const CString& recipe,
					   int ex_flag)
{
	int arm_type = Get_ArmType(arm);
	int module   = Get_ModuleType(str_module);
	int action;

	if(ex_flag < 0)		action = 1;
	else				action = 3;

	xI_MATERIAL_LOG->Write__LOG(arm_type,action,module,material,lotid,recipe);
	return 1;
}
int CMacro_LOG
::Log_Material_Pick(const CString& arm,const CString& str_module,
				    const CString& material,const CString& lotid,const CString& recipe,
				    int ex_flag)
{
	int arm_type = Get_ArmType(arm);
	int module   = Get_ModuleType(str_module);
	int action;

	if(ex_flag < 0)		action = 2;
	else				action = 4;

	xI_MATERIAL_LOG->Write__LOG(arm_type,action,module,material,lotid,recipe);
	return 1;
}

int CMacro_LOG
::Log_Material_Placing(const CString& arm,const CString& str_module,
					   const CString& material,const CString& lotid,const CString& recipe,
					   int ex_flag)
{
	int arm_type = Get_ArmType(arm);
	int module   = Get_ModuleType(str_module);
	int action;

	if(ex_flag < 0)		action = 11;
	else				action = 13;

	xI_MATERIAL_LOG->Write__LOG(arm_type,action,module,material,lotid,recipe);
	return 1;
}
int CMacro_LOG
::Log_Material_Place(const CString& arm,const CString& str_module,
					 const CString& material,const CString& lotid,const CString& recipe,
					 int  ex_flag)
{
	int arm_type = Get_ArmType(arm);
	int module   = Get_ModuleType(str_module);
	int action;

	if(ex_flag < 0)		action = 12;
	else				action = 14;

	xI_MATERIAL_LOG->Write__LOG(arm_type,action,module,material,lotid,recipe);
	return 1;
}

int CMacro_LOG
::Lot_Write(const CString& lotid,const CString& portid)
{
	xI_LOT_SUMMARY->Clear__LOT_LOG(lotid,portid);
	xI_LOT_SUMMARY->Write__LOT_LOG(lotid,portid);

	xI_MATERIAL_LOG->Start__LOG(lotid,portid);
	return 1;
}

int CMacro_LOG
::Lot_End_Write(const CString& lotid,const CString& portid)
{
	xI_LOT_SUMMARY->Write__LOT_LOG(lotid,portid);

	xI_MATERIAL_LOG->End__LOG(lotid,portid);
	return 1;
}

int CMacro_LOG
::Lot_Slot_Write(const CString& lotid,const CString& portid,int slot,
				 const CString& module,const CString& recipeid,const CString& log)
{
	xI_LOT_SUMMARY->Write__SLOT_LOG(lotid,portid,slot,module,recipeid,log);
	return 1;
}

int CMacro_LOG
::Lot_Slot_End_Write(const CString& lotid,const CString& portid,int slot)
{
	xI_LOT_SUMMARY->End__SLOT_LOG(lotid,portid,slot);
	return 1;
}

int CMacro_LOG
::Lot_Slot_AlarmPost(const CString& lotid,const CString& portid,int slot,int alarmid)
{
	CString prcid = "AAA";

	xI_LOT_SUMMARY->Alarm_Post__LOT_SLOT(lotid,portid,slot,alarmid,prcid);
	return 1;	
}

int CMacro_LOG
::Lot_Slot_AlarmClear(const CString& lotid,const CString& portid,int slot,int alarmid)
{
	xI_LOT_SUMMARY->Alarm_Clear__LOT_SLOT(lotid,portid,slot,alarmid);
	return 1;	
}
