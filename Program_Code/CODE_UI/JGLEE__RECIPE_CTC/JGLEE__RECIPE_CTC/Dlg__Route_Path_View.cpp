// Dlg__Route_Path_View.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_CTC.h"

#include "CObj__Route_EDIT__KEY_DEF.h"
#include "Dlg__Route_Path_View.h"

#include "Macro_Function.h"


#define _TREE_IMG__MODULE				0
#define _TREE_IMG__ALx					1
#define _TREE_IMG__LLx_IN				2
#define _TREE_IMG__PROCESSx				3
#define _TREE_IMG__LLx_OUT				4
#define _TREE_IMG__STx					5
#define _TREE_IMG__LLx_PROC				6
#define _TREE_IMG__LOOPx_PROC			7


// CDlg__Route_Path_View dialog

IMPLEMENT_DYNAMIC(CDlg__Route_Path_View, CDialog)

CDlg__Route_Path_View::CDlg__Route_Path_View(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Route_Path_View::IDD, pParent)
{

}

CDlg__Route_Path_View::~CDlg__Route_Path_View()
{
}

void CDlg__Route_Path_View::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE__ROUTE_PATH, mTree__Route_Path);
}


BEGIN_MESSAGE_MAP(CDlg__Route_Path_View, CDialog)
END_MESSAGE_MAP()


// CDlg__Route_Path_View message handlers

BOOL CDlg__Route_Path_View::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		CTreeCtrl* p_tree = &mTree__Route_Path;

		// ...
		CBitmap bmp;
		bmp.LoadBitmap(IDB_IMAGE_LIST);

		mImageList__Module_List.Create(16, 16, ILC_COLORDDB|ILC_MASK, 9, 9);
		mImageList__Module_List.Add(&bmp, RGB(0, 0, 0)); 
		p_tree->SetImageList(&mImageList__Module_List, TVSIL_NORMAL);

		//
		HTREEITEM h_route = p_tree->InsertItem("ROUTE", 0, 0, TVI_ROOT, TVI_LAST);

		// ALx ...
		if(Para_ALx__List_ID.GetSize() > 0)
		{
			Add__ALx_To_Tree_Route(p_tree,
								   h_route,
								   NULL, 
				                   Para_ALx__List_ID,
								   Para_ALx__List_ANGLE,
								   Para_ALx__List_SLOT);
		}
		// LLx_IN ...
		if(Para_BMx_IN__List_ID.GetSize() > 0)
		{
			Add__LLx_To_Tree_Route(p_tree,
								   h_route,
								   NULL,  
								   1, 
								   Para_BMx_IN__List_ID,
								   Para_BMx_IN__List_MODE,
								   Para_BMx_IN__List_SLOT);
		}

		// PROCESS_PATH ...
		{
			CString str_category;
			int path_count = 0;

			int i_limit = iPara_PATH__SIZE;
			int i;

			for(i=0; i<i_limit; i++)
			{
				if(Para_PATHx__List_PMx_ID[i].GetSize() < 1)
				{
					continue;
				}

				path_count++;
				str_category.Format("PROCESS_%1d", path_count);

				Add__PROCESSx_To_Tree_Route(p_tree,
											h_route,
											NULL, 
											str_category,
											Para_PATHx__List_PMx_ID[i],
											Para_PATHx__List_RCP_PRE[i],
											Para_PATHx__List_RCP_MAIN[i],
											Para_PATHx__List_RCP_POST[i]);
			}
		}
		// LLx_PRC ...
		if(Para_LLx_PRC__List_ID.GetSize() > 0)
		{
			Add__LLx_PRC_To_Tree_Route(p_tree,
									   h_route,
									   NULL, 
									   -1, 
									   Para_LLx_PRC__List_ID,
									   Para_LLx_PRC__List_PRE,
									   Para_LLx_PRC__List_MAIN,
									   Para_LLx_PRC__List_POST);
		}
		// LOOPx_PRC ...
		if(Para_LOOPx_PRC__List_ID.GetSize() > 0)
		{
			Add__LOOPx_PRC_To_Tree_Route(p_tree,
										 h_route,
										 NULL, 
										 -1, 
										 Para_LOOPx_PRC__List_ID,
										 Para_LOOPx_PRC__List_REPEAT);
		}

		// LLx_OUT ...
		if(Para_BMx_OUT__List_ID.GetSize() > 0)
		{
			Add__LLx_To_Tree_Route(p_tree,
								   h_route,
								   NULL, 
								   -1, 
								   Para_BMx_OUT__List_ID,
								   Para_BMx_OUT__List_MODE,
								   Para_BMx_OUT__List_SLOT);
		}
		// STx ...
		if(Para_STx__List_ID.GetSize() > 0)
		{
			Add__STx_To_Tree_Route(p_tree,
								   h_route,
								   NULL, 
								   Para_STx__List_ID,
								   Para_STx__List_MODE,
								   Para_STx__List_SLOT,
								   Para_STx__List_SEC,
								   Para_STx__List_N2_PURGE);
		}

		MACRO__Expand_All_Tree(p_tree);
	}

	return TRUE;
}

HTREEITEM CDlg__Route_Path_View
::Add__ALx_To_Tree_Route(CTreeCtrl* p_tree,
						 HTREEITEM h_root,
						 HTREEITEM h_after,
						 const CStringArray& l_al_id,
						 const CStringArray& l_al_angle,
						 const CStringArray& l_al_slot)
{
	CString str_title  = "ALx";

	int img_id = _TREE_IMG__ALx;
	int lst_id = img_id;

	// ...
	HTREEITEM h_node;

	if(h_root == NULL)
	{
		h_node = h_after;
	}
	else
	{
		if(h_after == NULL)		h_node = p_tree->InsertItem(str_title, img_id,img_id, h_root, TVI_LAST);
		else					h_node = p_tree->InsertItem(str_title, img_id,img_id, h_root, h_after);
	}

	// ...
	CString para__al_id;
	CString para__al_angle;
	CString para__al_slot;

	int i_limit = l_al_id.GetSize();
	int i;

	for(int i=0; i<i_limit; i++)
	{
		CString str_id = l_al_id[i];

		para__al_id.Format("AL%s", str_id);
		para__al_angle = l_al_angle[i];
		para__al_slot  = l_al_slot[i];

		// ...
		int sel_id = lst_id + atoi(str_id);

		HTREEITEM h_xxx = p_tree->InsertItem(para__al_id, img_id,sel_id, h_node, TVI_SORT);
		CString str_xxx;

		// ...
		{
			str_xxx.Format("ANGLE : %s", para__al_angle);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

			str_xxx.Format("SLOT : %s", para__al_slot);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	
		}
	}

	return h_node;
}
HTREEITEM CDlg__Route_Path_View
::Add__LLx_To_Tree_Route(CTreeCtrl* p_tree,
						 HTREEITEM h_root,
						 HTREEITEM h_after,
						 const int active_in_mode,
						 const CStringArray& l_bm_id,
						 const CStringArray& l_bm_mode,
						 const CStringArray& l_bm_slot)
{
	CString str_title  = "LLx";

	int img_id;

	if(active_in_mode > 0)
	{
		str_title  = "LL_IN";
		img_id = _TREE_IMG__LLx_IN;
	}
	else
	{
		str_title  = "LL_OUT";
		img_id = _TREE_IMG__LLx_OUT;
	}

	int lst_id = img_id;

	// ...
	HTREEITEM h_node;

	if(h_root == NULL)
	{
		h_node = h_after;
	}
	else
	{
		if(h_after == NULL)		h_node = p_tree->InsertItem(str_title, img_id,img_id, h_root, TVI_LAST);
		else					h_node = p_tree->InsertItem(str_title, img_id,img_id, h_root, h_after);
	}

	// ...
	CString para__bm_id;
	CString para__bm_mode;
	CString para__bm_slot;

	int i_limit = l_bm_id.GetSize();
	int i;

	for(int i=0; i<i_limit; i++)
	{
		CString str_id = l_bm_id[i];

		para__bm_id.Format("LL%s", str_id);
		para__bm_mode = l_bm_mode[i];
		para__bm_slot = l_bm_slot[i];

		if(active_in_mode > 0)
		{
			if((para__bm_mode.CompareNoCase(STR__ALL) != 0)
			&& (para__bm_mode.CompareNoCase(STR__ONLY_INPUT) != 0))
			{
				continue;
			}
		}
		else
		{
			if((para__bm_mode.CompareNoCase(STR__ALL) != 0)
			&& (para__bm_mode.CompareNoCase(STR__ONLY_OUTPUT) != 0))
			{
				continue;
			}
		}

		// ...
		int module_id = lst_id + atoi(str_id);

		HTREEITEM h_xxx = p_tree->InsertItem(para__bm_id, img_id,module_id, h_node, TVI_SORT);
		CString str_xxx;

		// ...
		{
			str_xxx.Format("MODE : %s", para__bm_mode);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

			str_xxx.Format("SLOT : %s", para__bm_slot);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	
		}
	}

	return h_node;
}

HTREEITEM CDlg__Route_Path_View
::Add__PROCESSx_To_Tree_Route(CTreeCtrl* p_tree,
							  HTREEITEM h_root,
							  HTREEITEM h_after,
							  const CString& str_category,
							  const CStringArray& l_pmx_name,
							  const CStringArray& l_pre_rcp,
							  const CStringArray& l_main_rcp,
							  const CStringArray& l_post_rcp)
{
	CString str_title  = str_category;

	int img_id = _TREE_IMG__PROCESSx;
	int lst_id = img_id;

	// ...
	HTREEITEM h_node;

	if(h_root == NULL)
	{
		h_node = h_after;
	}
	else
	{
		if(h_after == NULL)		h_node = p_tree->InsertItem(str_title, img_id,img_id, h_root, TVI_LAST);
		else					h_node = p_tree->InsertItem(str_title, img_id,img_id, h_root, h_after);
	}

	// ...
	CString pmx_name;
	CString rcp_pre;
	CString rcp_main;
	CString rcp_post;

	int i_limit = l_pmx_name.GetSize();
	int i;

	for(int i=0; i<i_limit; i++)
	{
		pmx_name = l_pmx_name[i];
		rcp_pre  = l_pre_rcp[i];
		rcp_main = l_main_rcp[i];
		rcp_post = l_post_rcp[i];

		int pm_id  = MACRO__Get__PMC_ID(pmx_name);
		int sel_id = lst_id + pm_id;

		HTREEITEM h_xxx = p_tree->InsertItem(pmx_name, img_id,sel_id, h_node, TVI_SORT);
		CString str_xxx;

		// ...
		{
			str_xxx.Format("PRE_.RCP : %s", rcp_pre);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

			str_xxx.Format("MAIN.RCP : %s", rcp_main);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

			str_xxx.Format("POST.RCP : %s", rcp_post);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	
		}
	}
	return h_node;
}
HTREEITEM CDlg__Route_Path_View
::Add__LLx_PRC_To_Tree_Route(CTreeCtrl* p_tree,
							 HTREEITEM h_root,
							 HTREEITEM h_after,
							 const int active_in_mode,
							 const CStringArray& l_ll_prc_id,
							 const CStringArray& l_ll_prc_pre,
							 const CStringArray& l_ll_prc_main,
							 const CStringArray& l_ll_prc_post)
{
	CString str_title  = "LLx_PROC";
	CString str_module = "LL";

	int img_id = _TREE_IMG__LLx_PROC;
	int lst_id = img_id;

	// ...
	HTREEITEM h_node;

	if(h_root == NULL)
	{
		h_node = h_after;
	}
	else
	{
		if(h_after == NULL)		h_node = p_tree->InsertItem(str_title, img_id,img_id, h_root, TVI_LAST);
		else					h_node = p_tree->InsertItem(str_title, img_id,img_id, h_root, h_after);
	}

	// ...
	CString para__ll_prc_id;
	CString para__ll_prc_pre;
	CString para__ll_prc_main;
	CString para__ll_prc_post;

	int i_limit = l_ll_prc_id.GetSize();
	int i;

	for(int i=0; i<i_limit; i++)
	{
		CString str_id = l_ll_prc_id[i];

		para__ll_prc_id.Format("LL%s", str_id);
		para__ll_prc_pre  = l_ll_prc_pre[i];
		para__ll_prc_main = l_ll_prc_main[i];
		para__ll_prc_post = l_ll_prc_post[i];

		// ...
		int module_id = lst_id + atoi(str_id);

		HTREEITEM h_xxx = p_tree->InsertItem(para__ll_prc_id, img_id,module_id, h_node, TVI_SORT);
		CString str_xxx;

		// ...
		{
			str_xxx.Format("PRE_ : %s", para__ll_prc_pre);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

			str_xxx.Format("MAIN : %s", para__ll_prc_main);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

			str_xxx.Format("POST : %s", para__ll_prc_post);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	
		}
	}

	return h_node;
}
HTREEITEM CDlg__Route_Path_View
::Add__LOOPx_PRC_To_Tree_Route(CTreeCtrl* p_tree,
							   HTREEITEM h_root,
							   HTREEITEM h_after,
							   const int active_in_mode,
							   const CStringArray& l_loop_prc_id,
							   const CStringArray& l_loop_prc_repeat)
{
	CString str_title  = "LOOPx_PROC";
	CString str_module = "LOOP";

	int img_id = _TREE_IMG__LOOPx_PROC;
	int lst_id = img_id;

	// ...
	HTREEITEM h_node;

	if(h_root == NULL)
	{
		h_node = h_after;
	}
	else
	{
		if(h_after == NULL)		h_node = p_tree->InsertItem(str_title, img_id,img_id, h_root, TVI_LAST);
		else					h_node = p_tree->InsertItem(str_title, img_id,img_id, h_root, h_after);
	}

	// ...
	CString para__loop_prc_id;
	CString para__loop_prc_repeat;

	int i_limit = l_loop_prc_id.GetSize();
	int i;

	for(int i=0; i<i_limit; i++)
	{
		CString str_id = l_loop_prc_id[i];

		para__loop_prc_id.Format("LOOP%s", str_id);
		para__loop_prc_repeat = l_loop_prc_repeat[i];

		// ...
		int module_id = lst_id + atoi(str_id);

		HTREEITEM h_xxx = p_tree->InsertItem(para__loop_prc_id, img_id,module_id, h_node, TVI_SORT);
		CString str_xxx;

		// ...
		{
			str_xxx.Format("REPEAT : %s", para__loop_prc_repeat);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	
		}
	}

	return h_node;
}

HTREEITEM CDlg__Route_Path_View
::Add__STx_To_Tree_Route(CTreeCtrl* p_tree,
						 HTREEITEM h_root,
						 HTREEITEM h_after,
						 const CStringArray& l_st_id,
						 const CStringArray& l_st_mode,
						 const CStringArray& l_st_slot,
						 const CStringArray& l_st_sec,
						 const CStringArray& l_st_n2_purge)
{
	CString str_title  = "SIDE_STORAGEx";
	CString str_module = "ST";

	int img_id = _TREE_IMG__STx;
	int lst_id = img_id;

	// ...
	HTREEITEM h_node;

	if(h_root == NULL)
	{
		h_node = h_after;
	}
	else
	{
		if(h_after == NULL)		h_node = p_tree->InsertItem(str_title, img_id,img_id, h_root, TVI_LAST);
		else					h_node = p_tree->InsertItem(str_title, img_id,img_id, h_root, h_after);
	}

	// ...
	CString para__st_id;
	CString para__st_mode;
	CString para__st_slot;
	CString para__st_sec;
	CString para__st_n2_purge;

	int i_limit = l_st_id.GetSize();
	int i;

	for(int i=0; i<i_limit; i++)
	{
		CString str_id = l_st_id[i];

		para__st_id.Format("ST%s", str_id);
		para__st_mode = l_st_mode[i];
		para__st_slot = l_st_slot[i];
		para__st_sec  = l_st_sec[i];
		para__st_n2_purge = l_st_n2_purge[i];

		// ...
		int module_id = lst_id + atoi(str_id);

		HTREEITEM h_xxx = p_tree->InsertItem(para__st_id, img_id,module_id, h_node, TVI_SORT);
		CString str_xxx;

		// ...
		{
			str_xxx.Format("MODE : %s", para__st_mode);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

			str_xxx.Format("SLOT : %s", para__st_slot);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

			str_xxx.Format("SEC : %s", para__st_sec);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

			str_xxx.Format("N2_PURGE : %s", para__st_n2_purge);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	
		}
	}

	return h_node;
}
