#include "stdafx.h"
#include "CObj__Route_EDIT__KEY_DEF.h"

#include "Dlg__Route_EDIT.h"
#include "Dlg__Route_EDIT__Def.h"

#include "Macro_Function.h"


// ...
HTREEITEM CDlg__Route_EDIT
::Add__XXX_To_Tree_Route(CTreeCtrl* p_tree_src,
						 HTREEITEM h_src_xx,
						 CTreeCtrl* p_tree_trg,
						 HTREEITEM h_root,
						 HTREEITEM h_after)
{
	// Source ...
	int src_img;
	int src_sel;

	HTREEITEM h_src = Get__Tree_Module(p_tree_trg, h_src_xx);
	if(h_src == NULL)		h_src = h_src_xx;

	CString src_name = p_tree_src->GetItemText(h_src);
	p_tree_src->GetItemImage(h_src, src_img,src_sel);

	// Target ...
	int trg_img;
	int trg_sel;

	CString trg_name = p_tree_trg->GetItemText(h_after);
	p_tree_trg->GetItemImage(h_after, trg_img,trg_sel);

	//
	return _Add__XXX_To_Tree_Route(p_tree_src,h_src, p_tree_trg,h_root,h_after, src_img,src_sel, trg_img,trg_sel);
}
HTREEITEM CDlg__Route_EDIT
::_Add__XXX_To_Tree_Route(CTreeCtrl* p_tree_src,
						  HTREEITEM h_src, 
						  CTreeCtrl* p_tree_trg,
						  HTREEITEM h_root,
						  HTREEITEM h_after,
						  const int src_img,
						  const int src_sel,
						  const int trg_img,
						  const int trg_sel)
{
	CString err_title;
	int add_img = -1;
	int add_sel = -1;

	if(src_img == _EDIT__ALx)
	{
		add_img = _EDIT__ALx;
		add_sel = _SEL_ID__ALx;

		err_title = "Add ALx - Error !!!";
	}
	else if(src_img == _EDIT__LLx_IN)
	{
		add_img = _EDIT__LLx_IN;
		add_sel = _SEL_ID__LLx;

		err_title = "Add LLx_IN - Error !!!";
	}
	else if(src_img == _EDIT__PROCESS_XX)
	{
		add_img = _EDIT__PROCESS_XX;
		add_sel = _SEL_ID__PMx;

		err_title = "Add PROCESSx - Error !!!";
	}
	else if(src_img == _EDIT__LLx_OUT)
	{
		add_img = _EDIT__LLx_OUT;
		add_sel = _SEL_ID__LLx;

		err_title = "Add LLx_OUT - Error !!!";
	}
	else if(src_img == _EDIT__STx_XX)
	{
		add_img = _EDIT__STx_XX;
		add_sel = _SEL_ID__STx;

		err_title = "Add STx - Error !!!";
	}
	else if(src_img == _EDIT__LLx_PROC)
	{
		add_img = _EDIT__LLx_PROC;
		add_sel = _SEL_ID__LLx_PROC;

		err_title = "Add LLx_PROC - Error !!!";
	}
	else if(src_img == _EDIT__LOOPx_PROC)
	{
		add_img = _EDIT__LOOPx_PROC;
		add_sel = _SEL_ID__LOOPx_PROC;

		err_title = "Add LOOPx_PROC - Error !!!";
	}

	if(add_img < 0)
	{
		return NULL;
	}

	if(src_img == add_img)
	{
		int src_md = src_sel - add_sel;

		if(trg_img == add_img)
		{
			if(src_md > 0)
			{
				if(Check__Tree_Sub_Module(p_tree_trg, h_after, add_img, src_md) > 0)
				{
					CString str_msg;

					str_msg.Format("Already Exist - Module(%1d) !!!", src_md);
					MessageBox(str_msg, err_title);
					return NULL;		
				}

				// ...
				CString str_data;

				if(src_img == _EDIT__ALx)
				{
					CStringArray l_al_id;
					CStringArray l_al_angle;
					CStringArray l_al_slot;

					str_data.Format("%1d", src_md);
					l_al_id.Add(str_data);
					l_al_angle.Add("0");
					l_al_slot.Add("11");

					return Add__ALx_To_Tree_Route(p_tree_trg, NULL,h_after, l_al_id,l_al_angle,l_al_slot);
				}
				else if((src_img == _EDIT__LLx_IN) 
					 || (src_img == _EDIT__LLx_OUT))
				{
					CStringArray l_bm_id;
					CStringArray l_bm_mode;
					CStringArray l_bm_slot;
					CStringArray l_bm_cooling_sec;

					str_data.Format("%1d", src_md);
					l_bm_id.Add(str_data);
					
					if(iLLx_MODE == _LLx_MODE__ALL)
					{
						l_bm_mode.Add("ALL");
					}
					else
					{
							 if(src_img == _EDIT__LLx_IN)			l_bm_mode.Add(STR__ONLY_INPUT);
						else if(src_img == _EDIT__LLx_OUT)			l_bm_mode.Add(STR__ONLY_OUTPUT);
					}

					l_bm_slot.Add("11");
					l_bm_cooling_sec.Add("0");

					if(src_img == _EDIT__LLx_IN) 
						return Add__LLx_To_Tree_Route(p_tree_trg, NULL,h_after,  1, l_bm_id,l_bm_mode,l_bm_slot,l_bm_cooling_sec);
					else
						return Add__LLx_To_Tree_Route(p_tree_trg, NULL,h_after, -1, l_bm_id,l_bm_mode,l_bm_slot,l_bm_cooling_sec);
				}
				else if(src_img == _EDIT__PROCESS_XX) 
				{
					return Add__PMx_To_Tree_Route(p_tree_trg, NULL,h_after, src_md);
				}
				else if(src_img == _EDIT__LLx_PROC) 
				{
					return Add__LLx_PROC_To_Tree_Route(p_tree_trg, NULL,h_after);
				}
				else if(src_img == _EDIT__LOOPx_PROC) 
				{
					return Add__LOOPx_PROC_To_Tree_Route(p_tree_trg, NULL,h_after);
				}
				else if(src_img == _EDIT__STx_XX) 
				{
					CStringArray l_st_id;
					CStringArray l_st_mode;
					CStringArray l_st_slot;
					CStringArray l_st_sec;
					CStringArray l_st_n2_purge;

					str_data.Format("%1d", src_md);
					l_st_id.Add(str_data);
					l_st_mode.Add("TIME");
					l_st_slot.Add("BOTTOM_UP");	
					l_st_sec.Add("60");
					l_st_n2_purge.Add("NO");

					return Add__STx_To_Tree_Route(p_tree_trg, NULL,h_after, l_st_id,l_st_mode,l_st_slot,l_st_sec,l_st_n2_purge);
				}

				return NULL;
			}
			else
			{
				CStringArray l_md;
				Get__Tree_Sub_Module(p_tree_trg, h_after, l_md);

				if(l_md.GetSize() > 0)
				{
					if(src_img != _EDIT__PROCESS_XX)
					{					
						CString str_msg;

						str_msg.Format("Already Exist - List !!!");
						MessageBox(str_msg, err_title);
						return NULL;
					}
				}

				if(src_img == _EDIT__ALx)
				{
					return Add__ALx_To_Tree_Route(p_tree_trg, NULL,h_after);
				}
				else if(src_img == _EDIT__LLx_IN)
				{
					return Add__LLx_IN_To_Tree_Route(p_tree_trg, NULL,h_after);
				}
				else if(src_img == _EDIT__PROCESS_XX)
				{
					return Add__PMx_To_Tree_Route(p_tree_trg, h_root,h_after);
				}
				else if(src_img == _EDIT__LLx_PROC)
				{
					return Add__LLx_PROC_To_Tree_Route(p_tree_trg, h_root,h_after);
				}
				else if(src_img == _EDIT__LOOPx_PROC)
				{
					return Add__LOOPx_PROC_To_Tree_Route(p_tree_trg, h_root,h_after);
				}
				else if(src_img == _EDIT__LLx_OUT)
				{
					return Add__LLx_OUT_To_Tree_Route(p_tree_trg, NULL,h_after);
				}
				else if(src_img == _EDIT__STx_XX)
				{
					return Add__STx_To_Tree_Route(p_tree_trg, NULL,h_after);
				}

				return NULL;
			}

			if(src_img == _EDIT__ALx)
			{
				return Add__ALx_To_Tree_Route(p_tree_trg, h_root,h_after);
			}
			else if(src_img == _EDIT__LLx_IN)
			{
				return Add__LLx_IN_To_Tree_Route(p_tree_trg, h_root,h_after);
			}
			else if(src_img == _EDIT__PROCESS_XX)
			{
				return Add__PMx_To_Tree_Route(p_tree_trg, h_root,h_after);
			}
			else if(src_img == _EDIT__LLx_PROC)
			{
				return Add__LLx_PROC_To_Tree_Route(p_tree_trg, h_root,h_after);
			}
			else if(src_img == _EDIT__LOOPx_PROC)
			{
				return Add__LOOPx_PROC_To_Tree_Route(p_tree_trg, h_root,h_after);
			}
			else if(src_img == _EDIT__LLx_OUT)
			{
				return Add__LLx_OUT_To_Tree_Route(p_tree_trg, h_root,h_after);
			}
			else if(src_img == _EDIT__STx_XX)
			{
				return Add__STx_To_Tree_Route(p_tree_trg, h_root,h_after);
			}

			return NULL;
		}
		else if(src_img == _EDIT__PROCESS_XX)
		{
			if(src_md > 0)
			{
				if(Check__Tree_Sub_Module(p_tree_trg, h_after, add_img, src_md) > 0)
				{
					CString str_msg;

					str_msg.Format("Already Exist - Module(%1d) !!!", src_md);
					MessageBox(str_msg, err_title);
					return NULL;		
				}

				return Add__PMx_To_Tree_Route(p_tree_trg, NULL,h_after, src_img);
			}
		}
		else if(src_img == _EDIT__LLx_PROC)
		{
			if(src_md > 0)
			{
				if(Check__Tree_Sub_Module(p_tree_trg, h_after, add_img, src_md) > 0)
				{
					CString str_msg;

					str_msg.Format("Already Exist - Module(%1d) !!!", src_md);
					MessageBox(str_msg, err_title);
					return NULL;		
				}

				return Add__LLx_PROC_To_Tree_Route(p_tree_trg, NULL,h_after);
			}
		}
		else if(src_img == _EDIT__LOOPx_PROC)
		{
			if(src_md > 0)
			{
				if(Check__Tree_Sub_Module(p_tree_trg, h_after, add_img, src_md) > 0)
				{
					CString str_msg;

					str_msg.Format("Already Exist - Module(%1d) !!!", src_md);
					MessageBox(str_msg, err_title);
					return NULL;		
				}

				return Add__LOOPx_PROC_To_Tree_Route(p_tree_trg, NULL,h_after);
			}
		}
		
		if(Check__Tree_Main_Module(p_tree_trg, src_img) < 0)
		{
			HTREEITEM h_xxx = p_tree_trg->GetRootItem();

			if(src_img == _EDIT__ALx)
			{
				return Add__ALx_To_Tree_Route(p_tree_trg, h_xxx,TVI_FIRST);
			}
			else if(src_img == _EDIT__LLx_IN)
			{
				HTREEITEM h_alx = Get__Tree_Pos_Of_ALx(p_tree_trg);
				if(h_alx != NULL)		
					return Add__LLx_IN_To_Tree_Route(p_tree_trg, h_root,h_alx);

				return Add__LLx_IN_To_Tree_Route(p_tree_trg, h_xxx,TVI_FIRST);
			}
			else if(src_img == _EDIT__PROCESS_XX)
			{
				// Check : LLx_IN ...
				{
					HTREEITEM h_pre = Get__Tree_Pos_Of_LLx_IN(p_tree_trg);
					if(h_pre != NULL)		
						return Add__PMx_To_Tree_Route(p_tree_trg, h_root,h_pre);
				}
				// Check : ALx ...
				{
					HTREEITEM h_pre = Get__Tree_Pos_Of_ALx(p_tree_trg);
					if(h_pre != NULL)		
						return Add__PMx_To_Tree_Route(p_tree_trg, h_root,h_pre);
				}

				return Add__PMx_To_Tree_Route(p_tree_trg, h_xxx,TVI_FIRST);
			}
			else if(src_img == _EDIT__LLx_PROC)
			{
				// Check : PROCESSx ...
				{
					HTREEITEM h_pre = Get__Tree_Pos_Of_PROCESSx(p_tree_trg, 1);
					if(h_pre != NULL)		
						return Add__LLx_PROC_To_Tree_Route(p_tree_trg, h_root,h_pre);
				}

				return Add__LLx_PROC_To_Tree_Route(p_tree_trg, h_xxx,TVI_FIRST);
			}
			else if(src_img == _EDIT__LOOPx_PROC)
			{
				// Check : LLx_PROC ...
				{
					HTREEITEM h_pre = Get__Tree_Pos_Of_LLx_PROC(p_tree_trg);
					if(h_pre != NULL)		
						return Add__LOOPx_PROC_To_Tree_Route(p_tree_trg, h_root,h_pre);
				}
				// Check : PROCESSx ...
				{
					HTREEITEM h_pre = Get__Tree_Pos_Of_PROCESSx(p_tree_trg, 1);
					if(h_pre != NULL)		
						return Add__LOOPx_PROC_To_Tree_Route(p_tree_trg, h_root,h_pre);
				}

				return Add__LOOPx_PROC_To_Tree_Route(p_tree_trg, h_xxx,TVI_FIRST);
			}
			else if(src_img == _EDIT__LLx_OUT)
			{
				// Check : PROCESSx ...
				{
					HTREEITEM h_pre = Get__Tree_Pos_Of_PROCESSx(p_tree_trg, 1);
					if(h_pre != NULL)		
						return Add__LLx_OUT_To_Tree_Route(p_tree_trg, h_root,h_pre);
				}
				// Check : LLx_IN ...
				{
					HTREEITEM h_pre = Get__Tree_Pos_Of_LLx_IN(p_tree_trg);
					if(h_pre != NULL)		
						return Add__LLx_OUT_To_Tree_Route(p_tree_trg, h_root,h_pre);
				}
				// Check : ALx ...
				{
					HTREEITEM h_pre = Get__Tree_Pos_Of_ALx(p_tree_trg);
					if(h_pre != NULL)		
						return Add__LLx_OUT_To_Tree_Route(p_tree_trg, h_root,h_pre);
				}

				return Add__LLx_OUT_To_Tree_Route(p_tree_trg, h_xxx,TVI_FIRST);
			}
			else if(src_img == _EDIT__STx_XX)
			{
				return Add__STx_To_Tree_Route(p_tree_trg, h_xxx,TVI_LAST);
			}
		}
		return NULL;
	}

	MessageBox("Error !!!", err_title);
	return NULL;
}
int CDlg__Route_EDIT
::_Change__Tree_Category(CTreeCtrl* p_tree, 
						 HTREEITEM h_src_category, 
						 HTREEITEM h_trg_category)
{
	CDB__Category_Info db_src;
	CDB__Category_Info db_trg;

	// Get Info ...
	{
		CDB__Category_Info *p_db;
		HTREEITEM h_category;

		int i_limit = 2;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == 0)				// Source ...
			{
				p_db = &db_src;
				h_category = h_src_category;
			}
			else if(i == 1)			// Target ...
			{
				p_db = &db_trg;
				h_category = h_trg_category;
			}
			else
			{
				break;
			}

			//
			CString str__category = p_tree->GetItemText(h_category);
			HTREEITEM h_main = p_tree->GetChildItem(h_category);	
		
			while(h_main != NULL)
			{
				CDB__Module_Info db_md;

				db_md.sTitle = p_tree->GetItemText(h_main);
				p_tree->GetItemImage(h_main, db_md.iImg_ID,db_md.iSel_ID);

				HTREEITEM h_child = p_tree->GetChildItem(h_main);
				while(h_child != NULL)
				{
					CString str_data = p_tree->GetItemText(h_child);

					int i_img, i_sel;
					p_tree->GetItemImage(h_child, i_img,i_sel);

					db_md.sList_Item.Add(str_data);
					db_md.iList_ImgID.Add(i_img);
					db_md.iList_SelID.Add(i_sel);
	
					h_child = p_tree->GetNextSiblingItem(h_child);
				}

				p_db->Load__Module_Info(db_md);

				h_main = p_tree->GetNextSiblingItem(h_main);
			}
		}
	}

	// Source Delete ...
	{
		HTREEITEM h_main = p_tree->GetChildItem(h_src_category);	
		while(h_main != NULL)
		{
			HTREEITEM h_del = h_main;

			h_main = p_tree->GetNextSiblingItem(h_main);
			p_tree->DeleteItem(h_del);
		}
	}
	// Target Delete ...
	{
		HTREEITEM h_main = p_tree->GetChildItem(h_trg_category);	
		while(h_main != NULL)
		{
			HTREEITEM h_del = h_main;

			h_main = p_tree->GetNextSiblingItem(h_main);
			p_tree->DeleteItem(h_del);
		}
	}

	// Add Info ...
	{
		HTREEITEM h_category;
		CDB__Category_Info *p_db;

		int t_limit = 2;
		int t;

		for(t=0; t<t_limit; t++)
		{
			if(t == 0)			// Target -> Source
			{
				h_category = h_src_category;
				p_db = &db_trg;
			}
			else if(t == 1)		// Source -> Target
			{
				h_category = h_trg_category;
				p_db = &db_src;
			}
			else
			{
				break;
			}

			//
			CDB__Module_Info *p_info;

			int i_limit = p_db->Get__Module_Size();
			int i;

			for(i=0; i<i_limit; i++)
			{
				p_info = (CDB__Module_Info *) p_db->Get__Module_Info(i);
				if(p_info == NULL)		break;

				int img_id = p_info->iImg_ID;
				int sel_id = p_info->iSel_ID;
				
				HTREEITEM h_main = p_tree->InsertItem(p_info->sTitle, img_id,sel_id, h_category, TVI_LAST);

				int k_limit = p_info->sList_Item.GetSize();
				int k;

				for(k=0; k<k_limit; k++)
				{
					CString str_title = p_info->sList_Item[k];
					int img_id = p_info->iList_ImgID[k];
					int sel_id = p_info->iList_SelID[k];

					p_tree->InsertItem(str_title, img_id,sel_id, h_main, TVI_LAST);
				}
			}
		}
	}

	return 1;
}

HTREEITEM CDlg__Route_EDIT
::Add__ALx_To_Tree_Route(CTreeCtrl* p_tree,HTREEITEM h_root,HTREEITEM h_after)
{
	CString str_title  = "ALx";
	CString str_module = "AL";
	
	int img_id   = _LIST__ALx;
	int lst_id   = _SEL_ID__ALx;
	int lst_size = _DEF_ALx__MAX;

	return Add__MODULEx_To_Tree_Route(p_tree,h_root,h_after, str_title,str_module,img_id,lst_id,lst_size);
}
HTREEITEM CDlg__Route_EDIT
::Add__LLx_IN_To_Tree_Route(CTreeCtrl* p_tree,HTREEITEM h_root,HTREEITEM h_after)
{
	CString str_title  = "LLx_IN";
	CString str_module = "LL";

	int img_id   = _LIST__LLx_IN;
	int lst_id   = _SEL_ID__LLx;

	int lst_size = iSIZE__LLx_IN;
	CStringArray l__ll_name;

	for(int i=0; i<lst_size; i++)
	{
		if(!bACTIVE__LLx_IN[i])
		{
			continue;
		}

		CString ll_name;
		ll_name.Format("LL%1d", i+1);
		l__ll_name.Add(ll_name);
	}

	return Add__MODULEx_To_Tree_Route(p_tree,h_root,h_after, str_title,str_module,img_id,lst_id,lst_size,l__ll_name);
}
HTREEITEM CDlg__Route_EDIT
::Add__PMx_To_Tree_Route(CTreeCtrl* p_tree,
						 HTREEITEM h_root,
						 HTREEITEM h_after, 
						 const int pm_id,
						 const bool active_init)
{
	if(active_init)
	{
		mDB__PMx_TREE_CTRL.Clear_INFO();
	}

	// ...
	CStringArray l_pmx_name;
	CStringArray l_pre_rcp;
	CStringArray l_main_rcp;
	CStringArray l_post_rcp;

	CString str_module;

	if(pm_id > 0)
	{
		if(sPMx_NAME[pm_id-1].GetLength() > 0)		
			str_module.Format("PM%1d  (%s)", pm_id,sPMx_NAME[pm_id-1]);
		else
			str_module.Format("PM%1d", pm_id);
		
		//
		l_pmx_name.Add(str_module);
		l_pre_rcp.Add("");
		l_main_rcp.Add("");
		l_post_rcp.Add("");

		return Add__PROCESSx_To_Tree_Route(false, p_tree,h_root,h_after, l_pmx_name,l_pre_rcp,l_main_rcp,l_post_rcp);
	}
	
	// ...
	int i_limit = iPMx_SIZE;
	int i;

	for(i=0; i<i_limit; i++)
	{
		int id = i + 1;

		if(sPMx_NAME[i].GetLength() > 0)		
			str_module.Format("PM%1d  (%s)", id,sPMx_NAME[i]);
		else
			str_module.Format("PM%1d", id);

		//
		l_pmx_name.Add(str_module);
		l_pre_rcp.Add("");
		l_main_rcp.Add("");
		l_post_rcp.Add("");
	}

	return Add__PROCESSx_To_Tree_Route(active_init, p_tree,h_root,h_after, l_pmx_name,l_pre_rcp,l_main_rcp,l_post_rcp);
}
HTREEITEM CDlg__Route_EDIT
::Add__LLx_PROC_To_Tree_Route(CTreeCtrl* p_tree,HTREEITEM h_root,HTREEITEM h_after)
{
	CStringArray l_pmx_name;
	CStringArray l_pre_rcp;
	CStringArray l_main_rcp;
	CStringArray l_post_rcp;

	// ...
	int i_limit = iSIZE__ACTIVE_LLx_PROC;
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(!bACTIVE__ACTIVE_LLx_PROC[i])
		{
			continue;
		}

		CString ll_name;
		ll_name.Format("LL%1d", i+1);

		l_pmx_name.Add(ll_name);
		l_pre_rcp.Add("");
		l_main_rcp.Add("");
		l_post_rcp.Add("");
	}

	return Add__LLx_PROC_To_Tree_Route(p_tree,h_root,h_after, l_pmx_name,l_pre_rcp,l_main_rcp,l_post_rcp);
}
HTREEITEM CDlg__Route_EDIT
::Add__LOOPx_PROC_To_Tree_Route(CTreeCtrl* p_tree,HTREEITEM h_root,HTREEITEM h_after)
{
	CStringArray l_loop_name;
	CStringArray l_loop_repeat;

	CString str_module;

	// ...
	int i_limit = 1;
	int i;

	for(i=0; i<i_limit; i++)
	{
		str_module.Format("LOOP%1d", i+1);

		l_loop_name.Add(str_module);
		l_loop_repeat.Add("");
	}

	return Add__LOOPx_PROC_To_Tree_Route(p_tree,h_root,h_after, l_loop_name,l_loop_repeat);
}
HTREEITEM CDlg__Route_EDIT
::Add__LLx_OUT_To_Tree_Route(CTreeCtrl* p_tree,HTREEITEM h_root,HTREEITEM h_after)
{
	CString str_title  = "LLx_OUT";
	CString str_module = "LL";

	int img_id   = _LIST__LLx_OUT;
	int lst_id   = _SEL_ID__LLx;

	int lst_size = iSIZE__LLx_OUT;
	CStringArray l__ll_name;

	for(int i=0; i<lst_size; i++)
	{
		if(!bACTIVE__LLx_OUT[i])
		{
			continue;
		}

		CString ll_name;
		ll_name.Format("LL%1d", i+1);
		l__ll_name.Add(ll_name);
	}

	return Add__MODULEx_To_Tree_Route(p_tree,h_root,h_after, str_title,str_module,img_id,lst_id,lst_size,l__ll_name);
}
HTREEITEM CDlg__Route_EDIT
::Add__STx_To_Tree_Route(CTreeCtrl* p_tree,HTREEITEM h_root,HTREEITEM h_after)
{
	CString str_title  = "SIDE_STORAGEx";
	CString str_module = "ST";

	int img_id   = _LIST__STx;
	int lst_id   = _SEL_ID__STx;
	int lst_size = iSTx_SIZE;

	return Add__MODULEx_To_Tree_Route(p_tree,h_root,h_after, str_title,str_module,img_id,lst_id,lst_size);
}

HTREEITEM CDlg__Route_EDIT
::Add__MODULEx_To_Tree_Route(CTreeCtrl* p_tree,
							 HTREEITEM h_root,
							 HTREEITEM h_after,
							 const CString& str_title,
							 const CString& str_module,
							 const int img_id,
							 const int lst_id,
							 const int lst_size)
{
	CStringArray l_ll_name;

	return Add__MODULEx_To_Tree_Route(p_tree,h_root,h_after,str_title,str_module,img_id,lst_id,lst_size,l_ll_name);
}
HTREEITEM CDlg__Route_EDIT
::Add__MODULEx_To_Tree_Route(CTreeCtrl* p_tree,
							 HTREEITEM h_root,
							 HTREEITEM h_after,
							 const CString& str_title,
							 const CString& str_module,
							 const int img_id,
							 const int lst_id,
							 const int lst_size,
							 const CStringArray& l_ll_name)
{
	HTREEITEM h_node;
	CString str_name;

	if(h_root == NULL)
	{
		h_node = h_after;
	}
	else
	{
		if(h_after == NULL)		h_node = p_tree->InsertItem(str_title, img_id,img_id, h_root, TVI_LAST);
		else					h_node = p_tree->InsertItem(str_title, img_id,img_id, h_root, h_after);
	}

	if((img_id == _LIST__LLx_IN)
	|| (img_id == _LIST__LLx_OUT))
	{
		int i_limit = l_ll_name.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			str_name = l_ll_name[i];

			int ll_id  = Get__LLx_ID(str_name);
			int sel_id = lst_id + ll_id;

			HTREEITEM h_xxx = p_tree->InsertItem(str_name, img_id,sel_id, h_node, TVI_SORT);
			CString str_xxx;

			if(ll_id > 0)
			{
				int ll_index = ll_id - 1;

				str_xxx = "MODE : ";
				if(img_id == _LIST__LLx_IN)						str_xxx += STR__ONLY_INPUT;
				if(img_id == _LIST__LLx_OUT)					str_xxx += STR__ONLY_OUTPUT;
				p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

				str_xxx = "SLOT : ";
				if(bACTIVE_DEFAULT__LLx_SLOT01[ll_index])		str_xxx += "1";
				else											str_xxx += "0";
				if(bACTIVE_DEFAULT__LLx_SLOT02[ll_index])		str_xxx += "1";
				else											str_xxx += "0";
				p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

				if(img_id == _LIST__LLx_OUT)
				{
					if(bACTIVE__LLx_OUT_COOLING)
					{
						str_xxx = "COOLING : 0";
						p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	
					}
				}
			}
		}
	}
	else
	{
		int i_limit = lst_size;
		int i;

		for(i=0; i<i_limit; i++)
		{
			int pm_id  = i + 1;
			int sel_id = lst_id + pm_id;

			str_name.Format("%s%1d", str_module,pm_id);

			HTREEITEM h_xxx = p_tree->InsertItem(str_name, img_id,sel_id, h_node, TVI_SORT);
			CString str_xxx;

			switch(img_id)
			{
				case _LIST__ALx:
					{
						if(bACTIVE_DEFAULT__AL1_CTRL_CFG)			str_xxx = "ANGLE : CONFIG";
						else										str_xxx = "ANGLE : DISABLE";
						p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);

						str_xxx = "SLOT : ";
						if(bACTIVE_DEFAULT__AL1_SLOT01)				str_xxx += "1";
						else										str_xxx += "0";
						if(bACTIVE_DEFAULT__AL1_SLOT02)				str_xxx += "1";
						else										str_xxx += "0";
						p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	
					}
					break;

				case _LIST__PROCESSx:
					{
						str_xxx = "PRE_.RCP";
						p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

						str_xxx = "MAIN.RCP";
						p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

						str_xxx = "POST.RCP";
						p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	
					}
					break;

				case _LIST__STx:
					{
						str_xxx = "MODE : TIME";
						p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

						str_xxx = "SLOT : BOTTOM_TO_UP";
						p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

						str_xxx = "SEC : 30";
						p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	

						str_xxx = "N2_PURGE : NO";
						p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	
					}
					break;
			}
		}
	}

	return h_node;
}

HTREEITEM CDlg__Route_EDIT
::Add__PROCESSx_To_Tree_Route(const bool active_init,
							  CTreeCtrl* p_tree,
							  HTREEITEM h_root,
							  HTREEITEM h_after,
							  const CStringArray& l_pmx_name,
							  const CStringArray& l_pre_rcp,
							  const CStringArray& l_main_rcp,
							  const CStringArray& l_post_rcp)
{
	CString str_title  = "PROCESSx";

	int img_id = _LIST__PROCESSx;
	int lst_id = _SEL_ID__PMx;

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

		int pm_index = pm_id - 1;
		if((pm_index >= 0) && (pm_index < iPMx_SIZE))
		{
			if(sPMx_NAME[pm_index].GetLength() > 0)
				pmx_name.Format("PM%1d  (%s)", pm_id,sPMx_NAME[pm_index]);
		}

		HTREEITEM h_xxx = p_tree->InsertItem(pmx_name, img_id,sel_id, h_node, TVI_SORT);

		if(active_init)
		{
			mDB__PMx_TREE_CTRL.Add_INFO(h_xxx, pm_id);
		}

		// ...
		{
			CString str_xxx;

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
HTREEITEM CDlg__Route_EDIT
::Add__LLx_PROC_To_Tree_Route(CTreeCtrl* p_tree,
							  HTREEITEM h_root,
							  HTREEITEM h_after,
							  const CStringArray& l_llx_id,
							  const CStringArray& l_pre_rcp,
							  const CStringArray& l_main_rcp,
							  const CStringArray& l_post_rcp)
{
	CString str_title  = "LLx_PROC";

	int img_id = _LIST__LLx_PROC;
	int lst_id = _SEL_ID__LLx_PROC;

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
	CString llx_name;
	CString rcp_pre;
	CString rcp_main;
	CString rcp_post;

	int i_limit = l_llx_id.GetSize();
	int i;

	for(int i=0; i<i_limit; i++)
	{
		llx_name = l_llx_id[i];
		rcp_pre  = l_pre_rcp[i];
		rcp_main = l_main_rcp[i];
		rcp_post = l_post_rcp[i];

		int sel_id = lst_id + (i + 1);

		HTREEITEM h_xxx = p_tree->InsertItem(llx_name, img_id,sel_id, h_node, TVI_SORT);
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
HTREEITEM CDlg__Route_EDIT
::Add__LOOPx_PROC_To_Tree_Route(CTreeCtrl* p_tree,
							    HTREEITEM h_root,
							    HTREEITEM h_after,
							    const CStringArray& l_loop_id,
							    const CStringArray& l_loop_repeat)
{
	CString str_title  = "LOOPx_PROC";

	int img_id = _LIST__LOOPx_PROC;
	int lst_id = _SEL_ID__LOOPx_PROC;

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
	CString loop_name;
	CString rcp_repeat;

	int i_limit = l_loop_id.GetSize();
	int i;

	for(int i=0; i<i_limit; i++)
	{
		loop_name  = l_loop_id[i];
		rcp_repeat = l_loop_repeat[i];

		int sel_id = lst_id + (i + 1);

		HTREEITEM h_xxx = p_tree->InsertItem(loop_name, img_id,sel_id, h_node, TVI_SORT);
		CString str_xxx;

		// ...
		{
			str_xxx.Format("REPEAT : %s", rcp_repeat);
			p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	
		}
	}
	return h_node;
}

HTREEITEM CDlg__Route_EDIT
::Add__ALx_To_Tree_Route(CTreeCtrl* p_tree,
						 HTREEITEM h_root,
						 HTREEITEM h_after,
						 const CStringArray& l_al_id,
						 const CStringArray& l_al_angle,
						 const CStringArray& l_al_slot)
{
	CString str_title  = "ALx";

	int img_id = _LIST__ALx;
	int lst_id = _SEL_ID__ALx;

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
HTREEITEM CDlg__Route_EDIT
::Add__LLx_To_Tree_Route(CTreeCtrl* p_tree,
						 HTREEITEM h_root,
						 HTREEITEM h_after,
						 const int active_in_mode,
						 const CStringArray& l_bm_id,
						 const CStringArray& l_bm_mode,
						 const CStringArray& l_bm_slot,
						 const CStringArray& l_bm_cooling_sec)
{
	CString str_title  = "LLx";

	int img_id;
	int lst_id = _SEL_ID__LLx;

	if(active_in_mode > 0)
	{
		str_title  = "LL_IN";
		img_id = _LIST__LLx_IN;
	}
	else
	{
		str_title  = "LL_OUT";
		img_id = _LIST__LLx_OUT;
	}

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
	CString para__bm_cooling_sec;

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
			para__bm_cooling_sec = "__";

			if((para__bm_mode.CompareNoCase(STR__ALL) != 0)
			&& (para__bm_mode.CompareNoCase(STR__ONLY_INPUT) != 0))
			{
				continue;
			}
		}
		else
		{
			if(i < l_bm_cooling_sec.GetSize())			para__bm_cooling_sec = l_bm_cooling_sec[i];
			else										para__bm_cooling_sec = "0";

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

		if(active_in_mode < 0)
		{
			if(bACTIVE__LLx_OUT_COOLING)
			{
				str_xxx.Format("COOLING : %s", para__bm_cooling_sec);
				p_tree->InsertItem(str_xxx, img_id,lst_id, h_xxx, TVI_LAST);	
			}
		}
	}

	return h_node;
}
HTREEITEM CDlg__Route_EDIT
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

	int img_id = _LIST__STx;
	int lst_id = _SEL_ID__STx;

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

int CDlg__Route_EDIT
::Check__Tree_Category(const int i_img)
{
	if(i_img == _EDIT__ALx)				return 1;
	if(i_img == _EDIT__LLx_IN)			return 1;
	if(i_img == _EDIT__LLx_OUT)			return 1;
	if(i_img == _EDIT__PROCESS_XX)		return 1;
	if(i_img == _EDIT__LLx_PROC)		return 1;
	if(i_img == _EDIT__LOOPx_PROC)		return 1;
	if(i_img == _EDIT__STx_XX)			return 1;

	return -1;
}
int CDlg__Route_EDIT
::Get__Tree_ModuleID(const int i_img,const int i_sel)
{
	if(i_img == _EDIT__ALx)				return (i_sel - _SEL_ID__ALx);
	if(i_img == _EDIT__LLx_IN)			return (i_sel - _SEL_ID__LLx);
	if(i_img == _EDIT__LLx_OUT)			return (i_sel - _SEL_ID__LLx);
	if(i_img == _EDIT__PROCESS_XX)		return (i_sel - _SEL_ID__PMx);
	if(i_img == _EDIT__LLx_PROC)		return (i_sel - _SEL_ID__LLx_PROC);
	if(i_img == _EDIT__LOOPx_PROC)		return (i_sel - _SEL_ID__LOOPx_PROC);
	if(i_img == _EDIT__STx_XX)			return (i_sel - _SEL_ID__STx);

	return -1;
}

HTREEITEM CDlg__Route_EDIT
::Get__Tree_Module(CTreeCtrl* p_tree)
{
	HTREEITEM h_cur = p_tree->GetSelectedItem();				
	if(h_cur == NULL)			return NULL;

	// ...
	HTREEITEM h_root = p_tree->GetRootItem();
	HTREEITEM h_node = h_cur;

	HTREEITEM h_upper  = h_node;
	HTREEITEM h_module = NULL;

	while((h_node != NULL) && (h_node != h_root))
	{
		h_upper = h_node;
		h_node  = p_tree->GetParentItem(h_upper);

		// ... 
		int c_img;
		int c_sel;

		if(p_tree->GetItemImage(h_upper, c_img,c_sel) > 0)
		{
			int c_dif = Get__Tree_ModuleID(c_img,c_sel);

			if(c_dif > 0)		h_module = h_upper;
		}
	}

	if(h_module != NULL)
	{
		printf(" * CDlg__Route_EDIT::Get__Tree_Module() ... \n");
		printf("  ** h_module <- [%s] \n", p_tree->GetItemText(h_module));
	}
	return h_module;
}
HTREEITEM CDlg__Route_EDIT
::Get__Tree_Module(CTreeCtrl* p_tree, HTREEITEM s_node)
{
	HTREEITEM h_node = s_node;

	int c_img;
	int c_sel;

	while(h_node != NULL)
	{
		p_tree->GetItemImage(h_node, c_img,c_sel);

		if(c_img == c_sel)			return NULL;

		int c_md = Get__Tree_ModuleID(c_img, c_sel);
		if(c_md > 0)				return h_node;

		h_node = p_tree->GetParentItem(h_node);
	}
	return NULL;
}

HTREEITEM CDlg__Route_EDIT
::Get__Tree_Category(CTreeCtrl* p_tree)
{
	HTREEITEM h_module = Get__Tree_Module(p_tree);

	if(h_module == NULL)
	{
		HTREEITEM h_cur = p_tree->GetSelectedItem();

		int c_img;
		int c_sel;

		if(p_tree->GetItemImage(h_cur, c_img,c_sel) > 0)
		{
			if(Check__Tree_Category(c_img) > 0)
			{
				return h_cur;
			}
		}
		return NULL;
	}
	return p_tree->GetParentItem(h_module);
}
HTREEITEM CDlg__Route_EDIT
::Get__Tree_Category(CTreeCtrl* p_tree, HTREEITEM h_node)
{
	HTREEITEM h_xxx = h_node;
	int i_img, i_sel;

	while(1)
	{
		p_tree->GetItemImage(h_xxx, i_img,i_sel);
		
		if(Check__Tree_Category(i_img) > 0)
		{
			if(i_img == i_sel)		return h_xxx;
		}

		h_xxx = p_tree->GetParentItem(h_xxx);
	}
	return NULL;
}
HTREEITEM CDlg__Route_EDIT
::Get__Tree_Pre_Category_Of_Process_X(CTreeCtrl* p_tree, 
									  HTREEITEM h_category)
{
	HTREEITEM h_root = p_tree->GetRootItem();
	HTREEITEM h_pre  = NULL;

	HTREEITEM h_sub  = p_tree->GetChildItem(h_root);

	while(h_sub)
	{
		if(h_category == h_sub)
		{
			return h_pre;
		}

		// ...
		{
			int i_img, i_sel;
			p_tree->GetItemImage(h_sub, i_img,i_sel);
		
			if(i_img == _EDIT__PROCESS_XX)
				h_pre = h_sub;
		}

		h_sub = p_tree->GetNextSiblingItem(h_sub);
	}
	return NULL;
}

int CDlg__Route_EDIT
::Check__Tree_Main_Module(CTreeCtrl* p_tree, const int img_id)
{
	HTREEITEM h_root = p_tree->GetRootItem();
	HTREEITEM h_sub = NULL;

	h_sub = p_tree->GetChildItem(h_root);
	while(h_sub != NULL)
	{
		int i_img, i_sel;

		p_tree->GetItemImage(h_sub, i_img,i_sel);
		if(i_img == img_id)		return 1;

		h_sub = p_tree->GetNextSiblingItem(h_sub);
	}
	return -1;
}
int CDlg__Route_EDIT
::Check__Tree_Sub_Module(CTreeCtrl* p_tree,
						 HTREEITEM h_main,
						 const int img_id, 
						 const int md_id)
{
	HTREEITEM h_sub = p_tree->GetChildItem(h_main);
	
	while(h_sub != NULL)
	{
		int i_img;
		int i_sel;

		p_tree->GetItemImage(h_sub, i_img,i_sel);
		if(i_img == img_id)
		{
			int i_md = Get__Tree_ModuleID(i_img,i_sel);					
			if(i_md == md_id)		return 1;
		}

		h_sub = p_tree->GetNextSiblingItem(h_sub);
	}
	return -1;
}
int CDlg__Route_EDIT
::Get__Tree_Sub_Module(CTreeCtrl* p_tree, 
					   HTREEITEM h_main, 
					   CStringArray& l_md)
{
	l_md.RemoveAll();

	HTREEITEM h_sub = p_tree->GetChildItem(h_main);

	while(h_sub != NULL)
	{
		l_md.Add(p_tree->GetItemText(h_sub));

		h_sub = p_tree->GetNextSiblingItem(h_sub);
	}
	return 1;
}

HTREEITEM CDlg__Route_EDIT
::Get__Tree_Pos_Of_ALx(CTreeCtrl* p_tree)
{
	HTREEITEM h_root = p_tree->GetRootItem();
	HTREEITEM h_sub = NULL;

	h_sub = p_tree->GetChildItem(h_root);
	while(h_sub != NULL)
	{
		int i_img, i_sel;

		p_tree->GetItemImage(h_sub, i_img,i_sel);
		if(i_img == _EDIT__ALx)			return h_sub;

		h_sub = p_tree->GetNextSiblingItem(h_sub);
	}
	return NULL;
}
HTREEITEM CDlg__Route_EDIT
::Get__Tree_Pos_Of_PROCESSx(CTreeCtrl* p_tree,
							const int last_index)
{
	HTREEITEM h_root = p_tree->GetRootItem();
	HTREEITEM h_sub  = NULL;
	HTREEITEM h_last = NULL;

	h_sub = p_tree->GetChildItem(h_root);
	while(h_sub != NULL)
	{
		int i_img, i_sel;

		p_tree->GetItemImage(h_sub, i_img,i_sel);
		if(i_img == _EDIT__PROCESS_XX)
		{
			if(last_index < 0)			return h_sub;

			h_last = h_sub;
		}
		h_sub = p_tree->GetNextSiblingItem(h_sub);
	}
	return h_last;
}
HTREEITEM CDlg__Route_EDIT
::Get__Tree_Pos_Of_LLx_PROC(CTreeCtrl* p_tree)
{
	HTREEITEM h_root = p_tree->GetRootItem();
	HTREEITEM h_sub = NULL;

	h_sub = p_tree->GetChildItem(h_root);
	while(h_sub != NULL)
	{
		int i_img, i_sel;

		p_tree->GetItemImage(h_sub, i_img,i_sel);
		if(i_img == _EDIT__LLx_PROC)		return h_sub;

		h_sub = p_tree->GetNextSiblingItem(h_sub);
	}
	return NULL;
}
HTREEITEM CDlg__Route_EDIT
::Get__Tree_Pos_Of_LLx_IN(CTreeCtrl* p_tree)
{
	HTREEITEM h_root = p_tree->GetRootItem();
	HTREEITEM h_sub = NULL;

	h_sub = p_tree->GetChildItem(h_root);
	while(h_sub != NULL)
	{
		int i_img, i_sel;

		p_tree->GetItemImage(h_sub, i_img,i_sel);
		if(i_img == _EDIT__LLx_IN)		return h_sub;

		h_sub = p_tree->GetNextSiblingItem(h_sub);
	}
	return NULL;
}
