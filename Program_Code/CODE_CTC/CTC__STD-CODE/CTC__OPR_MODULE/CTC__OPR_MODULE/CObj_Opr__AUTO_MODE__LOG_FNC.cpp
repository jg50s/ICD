#include "StdAfx.h"
#include "CObj_Opr__AUTO_MODE.h"


#include "CMacro_LOG.h"
extern CMacro_LOG  mMacro_LOG;


// ...
void CObj_Opr__AUTO_MODE::Datalog__Write_Lot(const int ptn)
{
	IDS__SCH_MATERIAL_INFO ds_info;
	CString lotid;
	CString portid;

	xSCH_MATERIAL_CTRL->Get__PORT_FIRST_SLOT_INFO(ptn,ds_info);
	portid.Format("PORT%1d",ptn);
	lotid = ds_info.sLOT_ID;

	CString user_id;
	CString user_level;

	xEXT_CH__USER_ID->Get__DATA(user_id);
	xEXT_CH__USER_LEVEL->Get__DATA(user_level);

	mMacro_LOG.Lot_Write_Ex(lotid,portid,user_id,user_level);
}
