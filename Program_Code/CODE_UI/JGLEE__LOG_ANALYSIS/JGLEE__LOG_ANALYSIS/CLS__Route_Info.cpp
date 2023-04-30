#include "stdafx.h"
#include "CLS__Route_Info.h"

#include "Macro_Function.h"


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


// ...
CDB__Route_Info::CDB__Route_Info()
{
	InitializeCriticalSection(&mCS_LOCK);

}
CDB__Route_Info::~CDB__Route_Info()
{
	CDB__Category_Info *p_info;

	int i_limit = pList_Category.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		p_info = (CDB__Category_Info *) pList_Category[i];
		delete p_info;
	}
	pList_Category.RemoveAll();

	DeleteCriticalSection(&mCS_LOCK);
}

int CDB__Route_Info
::Load__Category_Info(const CString& category_name, 
					  const int category_imgid,
					  const int category_selid)
{
	EnterCriticalSection(&mCS_LOCK);

	CDB__Category_Info *p_info = new CDB__Category_Info;
	pList_Category.Add(p_info);

	p_info->sTitle  = category_name;
	p_info->iImg_ID = category_imgid;
	p_info->iSel_ID = category_selid;

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}
int CDB__Route_Info
::Load__Module_Info(const CDB__Module_Info& db_info)
{
	EnterCriticalSection(&mCS_LOCK);

	int db_index = pList_Category.GetSize() - 1;
	if(db_index >= 0)
	{
		CDB__Category_Info *p_category 
			= (CDB__Category_Info *) pList_Category[db_index];

		p_category->Load__Module_Info(db_info);
	}

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}

int CDB__Route_Info
::Get__Category_Size()
{
	EnterCriticalSection(&mCS_LOCK);

	int i_size = pList_Category.GetSize();

	LeaveCriticalSection(&mCS_LOCK);
	return i_size;
}
CDB__Category_Info* CDB__Route_Info
::Get__Category_Info(const int c_index)
{
	EnterCriticalSection(&mCS_LOCK);

	CDB__Category_Info *p_info = NULL;

	if(c_index < pList_Category.GetSize())
	{
		p_info = (CDB__Category_Info *) pList_Category[c_index];
	}

	LeaveCriticalSection(&mCS_LOCK);
	return p_info;
}

CString CDB__Route_Info
::Get__ALx_Of_Route_Info()
{
	EnterCriticalSection(&mCS_LOCK);

	CString file_data = "";
	CString str_data  = "";

	int i_limit = pList_Category.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CDB__Category_Info *p_info 
			= (CDB__Category_Info *) pList_Category[i];

		if(p_info->iImg_ID != _EDIT__ALx)
			continue;

		int k_limit = p_info->Get__Module_Size();
		int k;

		for(k=0; k<k_limit; k++)
		{
			CDB__Module_Info *p_md  
				= p_info->Get__Module_Info(k);

			CString md_id;
			CString md_mode = "DISABLE";
			CString md_slot = "11";

			md_id.Format("%1d", (p_md->iSel_ID - _SEL_ID__ALx));

			int p_limit = p_md->sList_Item.GetSize();
			int p;

			for(p=0; p<p_limit; p++)
			{
				CString para_data = p_md->sList_Item[p];
				para_data = MACRO__Get_ITEM_DATA(para_data, ':');

					 if(p == 0)		md_mode = para_data;
				else if(p == 1)		md_slot = para_data;
			}

			str_data.Format("#ALx#,%s,%s,%s;\n",
							md_id, 
							md_mode, 
							md_slot);
			file_data += str_data;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return file_data;
}
CString CDB__Route_Info
::Get__LLx_Of_Route_Info(const int ll_type)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	CString md_type = "";
	int check_img = -1;
	int check_sel = -1;

	if(ll_type == _ROUTE_TYPE__LLx_IN)		
	{
		md_type = "#LLx_IN#";
		check_img = _EDIT__LLx_IN;
		check_sel = _SEL_ID__LLx;
	}
	else if(ll_type == _ROUTE_TYPE__LLx_OUT)		
	{
		md_type = "#LLx_OUT#";
		check_img = _EDIT__LLx_OUT;
		check_sel = _SEL_ID__LLx;
	}

	// ...
	CString file_data = "";
	CString str_data  = "";

	int i_limit = pList_Category.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CDB__Category_Info *p_info 
			= (CDB__Category_Info *) pList_Category[i];

		if(p_info->iImg_ID != check_img)
			continue;

		int k_limit = p_info->Get__Module_Size();
		int k;

		for(k=0; k<k_limit; k++)
		{
			CDB__Module_Info *p_md  
				= p_info->Get__Module_Info(k);

			CString md_id;
			CString md_mode = "ALL";
			CString md_slot = "11";

			md_id.Format("%1d", (p_md->iSel_ID - check_sel));

			int p_limit = p_md->sList_Item.GetSize();
			int p;

			for(p=0; p<p_limit; p++)
			{
				CString para_data = p_md->sList_Item[p];
				para_data = MACRO__Get_ITEM_DATA(para_data, ':');

					if(p == 0)		md_mode = para_data;
				else if(p == 1)		md_slot = para_data;
			}

			str_data.Format("%s,%s,%s,%s;\n",
							md_type,
							md_id, 
							md_mode, 
							md_slot);
			file_data += str_data;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return file_data;
}
CString CDB__Route_Info
::Get__STx_Of_Route_Info()
{
	EnterCriticalSection(&mCS_LOCK);

	CString file_data = "";
	CString str_data  = "";

	int i_limit = pList_Category.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CDB__Category_Info *p_info 
			= (CDB__Category_Info *) pList_Category[i];

		if(p_info->iImg_ID != _EDIT__STx_XX)
			continue;

		int k_limit = p_info->Get__Module_Size();
		int k;

		for(k=0; k<k_limit; k++)
		{
			CDB__Module_Info *p_md  
				= p_info->Get__Module_Info(k);

			CString md_id;
			CString md_mode = "TIME";
			CString md_slot = "BOTTOM_TO_UP";
			CString md_sec  = "60";

			md_id.Format("%1d", (p_md->iSel_ID - _SEL_ID__STx));

			int p_limit = p_md->sList_Item.GetSize();
			int p;

			for(p=0; p<p_limit; p++)
			{
				CString para_data = p_md->sList_Item[p];
				para_data = MACRO__Get_ITEM_DATA(para_data, ':');

					 if(p == 0)		md_mode = para_data;
				else if(p == 1)		md_slot = para_data;
				else if(p == 2)		md_sec  = para_data;
			}

			str_data.Format("#STx#,%s,%s,%s,%s;\n",
							md_id, 
							md_mode, 
							md_slot, 
							md_sec);
			file_data += str_data;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return file_data;
}

CString CDB__Route_Info
::Get__PROCESSx_Of_Route_Info()
{
	EnterCriticalSection(&mCS_LOCK);

	CString file_data = "";
	CString str_data  = "";

	int i_limit = pList_Category.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CDB__Category_Info *p_info 
			= (CDB__Category_Info *) pList_Category[i];

		if(p_info->iImg_ID != _EDIT__PROCESS_XX)
		{
			continue;
		}

		file_data += "#PROCESS_START#";
		file_data += "\n";

		// ...
		int k_limit = p_info->Get__Module_Size();
		int k;

		for(k=0; k<k_limit; k++)
		{
			CDB__Module_Info *p_md  
				= p_info->Get__Module_Info(k);

			CString pm_name  = "";
			CString rcp_pre  = "";
			CString rcp_main = "";
			CString rcp_post = "";

			pm_name = p_md->sTitle;

			int p_limit = p_md->sList_Item.GetSize();
			int p;

			for(p=0; p<p_limit; p++)
			{
				CString para_data = p_md->sList_Item[p];
				para_data = MACRO__Get_ITEM_DATA(para_data, ':');

					 if(p == 0)		rcp_pre  = para_data;
				else if(p == 1)		rcp_main = para_data;
				else if(p == 2)		rcp_post = para_data;
			}

			str_data.Format("%s,%s,%s,%s;\n",
							pm_name,
							rcp_pre,
							rcp_main,
							rcp_post);
			file_data += str_data;
		}

		file_data += "#PROCESS_END#";
		file_data += "\n";
	}

	LeaveCriticalSection(&mCS_LOCK);
	return file_data;
}

CString CDB__Route_Info
::Get__LLx_PROC_Of_Route_Info()	
{
	EnterCriticalSection(&mCS_LOCK);

	CString file_data = "";
	CString str_data  = "";

	int i_limit = pList_Category.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CDB__Category_Info *p_info 
			= (CDB__Category_Info *) pList_Category[i];

		if(p_info->iImg_ID != _EDIT__LLx_PROC)
		{
			continue;
		}

		file_data += "#LLx_PROC_START#";
		file_data += "\n";

		// ...
		int k_limit = p_info->Get__Module_Size();
		int k;

		for(k=0; k<k_limit; k++)
		{
			CDB__Module_Info *p_md  
				= p_info->Get__Module_Info(k);

			CString pm_name  = "";
			CString rcp_pre  = "";
			CString rcp_main = "";
			CString rcp_post = "";

			pm_name = p_md->sTitle;

			int p_limit = p_md->sList_Item.GetSize();
			int p;

			for(p=0; p<p_limit; p++)
			{
				CString para_data = p_md->sList_Item[p];
				para_data = MACRO__Get_ITEM_DATA(para_data, ':');

					 if(p == 0)		rcp_pre  = para_data;
				else if(p == 1)		rcp_main = para_data;
				else if(p == 2)		rcp_post = para_data;
			}

			str_data.Format("%s,%s,%s,%s;\n",
							pm_name,
							rcp_pre,
							rcp_main,
							rcp_post);
			file_data += str_data;
		}

		file_data += "#LLx_PROC_END#";
		file_data += "\n";
	}

	LeaveCriticalSection(&mCS_LOCK);
	return file_data;
}
CString CDB__Route_Info
::Get__LOOPx_PROC_Of_Route_Info()	
{
	EnterCriticalSection(&mCS_LOCK);

	CString file_data = "";
	CString str_data  = "";

	int i_limit = pList_Category.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CDB__Category_Info *p_info 
			= (CDB__Category_Info *) pList_Category[i];

		if(p_info->iImg_ID != _EDIT__LOOPx_PROC)
		{
			continue;
		}

		file_data += "#LOOPx_PROC_START#";
		file_data += "\n";

		// ...
		int k_limit = p_info->Get__Module_Size();
		int k;

		for(k=0; k<k_limit; k++)
		{
			CDB__Module_Info *p_md  
				= p_info->Get__Module_Info(k);

			CString pm_name    = "";
			CString rcp_repeat = "";

			pm_name = p_md->sTitle;

			int p_limit = p_md->sList_Item.GetSize();
			int p;

			for(p=0; p<p_limit; p++)
			{
				CString para_data = p_md->sList_Item[p];
				para_data = MACRO__Get_ITEM_DATA(para_data, ':');

				if(p == 0)		rcp_repeat = para_data;
			}

			str_data.Format("%s,%s;\n",
							pm_name,
							rcp_repeat);
			file_data += str_data;
		}

		file_data += "#LOOPx_PROC_END#";
		file_data += "\n";
	}

	LeaveCriticalSection(&mCS_LOCK);
	return file_data;
}

