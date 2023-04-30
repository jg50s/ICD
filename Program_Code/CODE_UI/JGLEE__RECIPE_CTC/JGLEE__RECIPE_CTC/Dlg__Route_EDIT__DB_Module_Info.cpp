#include "stdafx.h"
#include "Dlg__Route_EDIT.h"
#include "Dlg__Route_EDIT__Def.h"


// ...
CDB__Category_Info::CDB__Category_Info()
{
	InitializeCriticalSection(&mCS_LOCK);

}
CDB__Category_Info::~CDB__Category_Info()
{
	CDB__Module_Info *p_info;

	int i_limit = pList_Module.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		p_info = (CDB__Module_Info *) pList_Module[i];
		delete p_info;
	}
	pList_Module.RemoveAll();

	DeleteCriticalSection(&mCS_LOCK);
}

int CDB__Category_Info
::Load__Module_Info(const CDB__Module_Info& db_info)
{
	EnterCriticalSection(&mCS_LOCK);

	CDB__Module_Info *p_info = new CDB__Module_Info;
	pList_Module.Add(p_info);

	p_info->sTitle  = db_info.sTitle;
	p_info->iImg_ID = db_info.iImg_ID;
	p_info->iSel_ID = db_info.iSel_ID;

	p_info->sList_Item.Copy(db_info.sList_Item);
	p_info->iList_ImgID.Copy(db_info.iList_ImgID);
	p_info->iList_SelID.Copy(db_info.iList_SelID);

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}
int CDB__Category_Info
::Get__Module_Size()
{
	EnterCriticalSection(&mCS_LOCK);

	int i_size = pList_Module.GetSize();

	LeaveCriticalSection(&mCS_LOCK);
	return i_size;
}
CDB__Module_Info* CDB__Category_Info
::Get__Module_Info(const int db_index)
{
	EnterCriticalSection(&mCS_LOCK);

	CDB__Module_Info *p_info = NULL;

	if(db_index < pList_Module.GetSize())
	{
		p_info = (CDB__Module_Info *) pList_Module[db_index];
	}

	LeaveCriticalSection(&mCS_LOCK);
	return p_info;
}

