#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Lot_Recipe_Log.h"

#include "Macro_Function.h"


// ...
#define _LIST__MODULE							0
#define _LIST__ALx								1
#define _LIST__LLx_IN							2
#define _LIST__PROCESSx							3
#define _LIST__LLx_OUT							4
#define _LIST__STx								5

#define _LIST__LLx_PROC							6
#define _LIST__LOOPx_PROC						7

// ...
#define _SEL_ID__ALx							100
#define _SEL_ID__LLx							200
#define _SEL_ID__PMx							300
#define _SEL_ID__STx							400

#define _SEL_ID__LLx_PROC						500
#define _SEL_ID__LOOPx_PROC						600


// ...
#define _ROUTE_CMMD__DESCRIPT                   101

#define _ROUTE_CMMD__PROCESS_START    			1
#define _ROUTE_CMMD__PROCESS_END    			2
#define _ROUTE_CMMD__LLx_PROC_START    			3
#define _ROUTE_CMMD__LLx_PROC_END    			4
#define _ROUTE_CMMD__LOOPx_PROC_START    		5
#define _ROUTE_CMMD__LOOPx_PROC_END    			6
#define _ROUTE_CMMD__BMx_IN						11
#define _ROUTE_CMMD__BMx_OUT					12
#define _ROUTE_CMMD__ALx						13
#define _ROUTE_CMMD__STx						14


#define _ROUTE_EDIT__PMx_MAX					6
#define _ROUTE_EDIT__PATH_MAX                   3


// ...
int CDlg__Lot_Recipe_Log
::_Upload__Route_File(const CString& file_path)
{
	CString file_data;

	if(MACRO__Get_File_Data(file_path, file_data) < 0)
	{
		CString str_msg;
		str_msg.Format("File Error : \"%s\" ", file_path);

		printf(str_msg);
		printf("\n");

		return -1;
	}

	// ...
	int max_count = _ROUTE_EDIT__PATH_MAX;
	int prc_count = 0;

	CDB__Category_Info prc_info[_ROUTE_EDIT__PATH_MAX];

	CStringArray l__al_id;
	CStringArray l__al_angle;
	CStringArray l__al_slot;

	CStringArray l__ll_in_id;
	CStringArray l__ll_in_mode;
	CStringArray l__ll_in_slot;

	CStringArray l__ll_out_id;
	CStringArray l__ll_out_mode;
	CStringArray l__ll_out_slot;

	CStringArray l__st_id;
	CStringArray l__st_mode;
	CStringArray l__st_slot;
	CStringArray l__st_sec;

	CStringArray l__ll_proc_id;
	CStringArray l__ll_proc_pre;
	CStringArray l__ll_proc_main;
	CStringArray l__ll_proc_post;

	CStringArray l__loop_proc_id;
	CStringArray l__loop_proc_repeat;

	//
	CString rcp_item__descript = "";

	CString rcp_item__al_id    = "";
	CString rcp_item__al_angle = "";
	CString rcp_item__al_slot  = "";

	CString rcp_item__ll_id   = "";
	CString rcp_item__ll_mode = "";
	CString rcp_item__ll_slot = "";

	CString rcp_item__st_id   = "";
	CString rcp_item__st_mode = "";
	CString rcp_item__st_slot = "";
	CString rcp_item__st_sec  = "";

	CString rcp_item__ll_proc_id   = "";
	CString rcp_item__ll_proc_pre  = "";
	CString rcp_item__ll_proc_main = "";
	CString rcp_item__ll_proc_post = "";

	CString rcp_item__loop_id     = "";
	CString rcp_item__loop_repeat = "";

	// ...
	CString	prc_module;
	CString	rcp_pre;
	CString	rcp_main;
	CString	rcp_post;

	CString	word;
	char ch;

	int command = 0;
	int para = 0;
	int check__ch_r = -1;

	int data_size = file_data.GetLength();
	int x;

	printf("** file_data : %1d ... \n", data_size);
	printf("================================================================== \n");
	printf("%s \n", file_data);
	printf("================================================================== \n");

	for(x=0; x<data_size; x++)
	{
		ch = file_data.GetAt(x);

		if((ch == '^')
		|| (ch == ',')
		|| (ch == ';')
		|| (ch == '(')
		|| (ch == ')')
		|| (ch == '\r')
		|| (ch == '\n')
		|| (ch == EOF))
		{
			if(ch == '\r')
			{
				check__ch_r = 1;
			}

			int new_cmmd = _Get__Route_Cmmd(word);
			if(new_cmmd > 0)
			{
				if(command != new_cmmd)		
				{
					command = new_cmmd;

					// ...
					{
						word = "";
						para = 0;
					}

					if((command == _ROUTE_CMMD__BMx_IN)
					|| (command == _ROUTE_CMMD__BMx_OUT))
					{
						rcp_item__ll_id   = "";
						rcp_item__ll_mode = "";
						rcp_item__ll_slot = "";
					}
					else if(command == _ROUTE_CMMD__ALx)
					{
						rcp_item__al_id    = "";
						rcp_item__al_angle = "";
						rcp_item__al_slot  = "";
					}
					else if(command == _ROUTE_CMMD__STx)
					{
						rcp_item__st_id   = "";
						rcp_item__st_mode = "";
						rcp_item__st_slot = "";
						rcp_item__st_sec  = "";
					}
					else if(command == _ROUTE_CMMD__PROCESS_START)
					{
						prc_module = "";
						rcp_pre  = "";
						rcp_main = "";
						rcp_post = "";
					}
					else if(command == _ROUTE_CMMD__PROCESS_END)
					{
						prc_count++;
					}
					else if(command == _ROUTE_CMMD__LLx_PROC_START)
					{
						rcp_item__ll_proc_id   = "";
						rcp_item__ll_proc_pre  = "";
						rcp_item__ll_proc_main = "";
						rcp_item__ll_proc_post = "";
					}
					else if(command == _ROUTE_CMMD__LOOPx_PROC_START)
					{
						rcp_item__loop_id     = "";
						rcp_item__loop_repeat = "";
					}

					continue;
				}
			}

			if(ch == '\n')
			{
				if(check__ch_r > 0)
				{
					check__ch_r = -1;

					if(word.GetLength() < 1)
					{
						word = "";
						continue;
					}
				}
			}

			if(command > 0)
			{
				if((ch == '^')||(ch == ',')||(ch == ';'))
				{
					para++;

					if(command == _ROUTE_CMMD__PROCESS_START)
					{
							 if(para == 1)		prc_module = word;
						else if(para == 2)		rcp_pre  = word;
						else if(para == 3)		rcp_main = word;
						else if(para == 4)		rcp_post = word;
					}
					else if(command == _ROUTE_CMMD__LLx_PROC_START)
					{
							 if(para == 1)		rcp_item__ll_proc_id   = word;
						else if(para == 2)		rcp_item__ll_proc_pre  = word;
						else if(para == 3)		rcp_item__ll_proc_main = word;
						else if(para == 4)		rcp_item__ll_proc_post = word;
					}
					else if(command == _ROUTE_CMMD__LOOPx_PROC_START)
					{
							 if(para == 1)		rcp_item__loop_id     = word;
						else if(para == 2)		rcp_item__loop_repeat = word;
					}
					else if((command == _ROUTE_CMMD__BMx_IN)
						 || (command == _ROUTE_CMMD__BMx_OUT))
					{
							 if(para == 1)		rcp_item__ll_id   = word;
						else if(para == 2)		rcp_item__ll_mode = word;
						else if(para == 3)		rcp_item__ll_slot = word;
					}
					else if(command == _ROUTE_CMMD__ALx)
					{
							 if(para == 1)		rcp_item__al_id    = word;
						else if(para == 2)		rcp_item__al_angle = word;
						else if(para == 3)		rcp_item__al_slot  = word;
					}
					else if(command == _ROUTE_CMMD__STx)
					{
							 if(para == 1)		rcp_item__st_id   = word;
						else if(para == 2)		rcp_item__st_mode = word;
						else if(para == 3)		rcp_item__st_slot = word;
						else if(para == 4)		rcp_item__st_sec  = word;
					}
					else if(command == _ROUTE_CMMD__DESCRIPT)
					{
						if(para == 1)
						{
							rcp_item__descript = word;
						} 
						else
						{
							rcp_item__descript += word;

							if(ch ==',')			rcp_item__descript += ",";
							else					rcp_item__descript += "\r\n";
						}
					}
				}

				if(ch == ';')
				{
					para = 0;

					if(command == _ROUTE_CMMD__PROCESS_START)
					{
						if(prc_count < max_count)
						{
							CDB__Module_Info db_info;

							db_info.sTitle = prc_module;
							db_info.sList_Item.Add(rcp_pre);
							db_info.sList_Item.Add(rcp_main);
							db_info.sList_Item.Add(rcp_post);

							prc_info[prc_count].Load__Module_Info(db_info);
						}
					}
					else if(command == _ROUTE_CMMD__LLx_PROC_START)
					{
						l__ll_proc_id.Add(rcp_item__ll_proc_id);
						l__ll_proc_pre.Add(rcp_item__ll_proc_pre);
						l__ll_proc_main.Add(rcp_item__ll_proc_main);
						l__ll_proc_post.Add(rcp_item__ll_proc_post);
					}
					else if(command == _ROUTE_CMMD__LOOPx_PROC_START)
					{
						l__loop_proc_id.Add(rcp_item__loop_id);
						l__loop_proc_repeat.Add(rcp_item__loop_repeat);
					}
					else if(command == _ROUTE_CMMD__BMx_IN)
					{
						l__ll_in_id.Add(rcp_item__ll_id);
						l__ll_in_mode.Add(rcp_item__ll_mode);
						l__ll_in_slot.Add(rcp_item__ll_slot);
					}
					else if(command == _ROUTE_CMMD__BMx_OUT)
					{
						l__ll_out_id.Add(rcp_item__ll_id);
						l__ll_out_mode.Add(rcp_item__ll_mode);
						l__ll_out_slot.Add(rcp_item__ll_slot);
					}
					else if(command == _ROUTE_CMMD__ALx)
					{
						l__al_id.Add(rcp_item__al_id);
						l__al_angle.Add(rcp_item__al_angle);
						l__al_slot.Add(rcp_item__al_slot);
					}
					else if(command == _ROUTE_CMMD__STx)
					{
						l__st_id.Add(rcp_item__st_id);
						l__st_mode.Add(rcp_item__st_mode);
						l__st_slot.Add(rcp_item__st_slot);
						l__st_sec.Add(rcp_item__st_sec);
					}
				}
				else if((ch == '\n') || (ch == '\r'))
				{
					if(command == _ROUTE_CMMD__PROCESS_START)
					{
						prc_module = "";
						rcp_pre  = "";
						rcp_main = "";
						rcp_post = "";
					}
					else if(command == _ROUTE_CMMD__LLx_PROC_START)
					{
						rcp_item__ll_proc_id   = "";
						rcp_item__ll_proc_pre  = "";
						rcp_item__ll_proc_main = "";
						rcp_item__ll_proc_post = "";
					}
					else if(command == _ROUTE_CMMD__LOOPx_PROC_START)
					{
						rcp_item__loop_id     = "";
						rcp_item__loop_repeat = "";
					}
					else
					{
						command = -1;
					}
				}
			}

			word = "";	
		}
		else
		{
			word += ch;
		}
	}

	// ...
	{
		CTreeCtrl *p_tree = &mTree__Lot_Recipe;

		HTREEITEM h_root = p_tree->InsertItem("ROUTE", 0, 0, TVI_ROOT, TVI_LAST);

		// ALx ...
		if(l__al_id.GetSize() > 0)
		{
			_Add__ALx_To_Tree_Route(p_tree, h_root, NULL, l__al_id,l__al_angle,l__al_slot);
		}

		// LLx_IN ...
		if(l__ll_in_id.GetSize() > 0)
		{
			_Add__LLx_To_Tree_Route(p_tree,h_root,NULL, 1,l__ll_in_id,l__ll_in_mode,l__ll_in_slot);
		}

		// PROCESS_X ...
		{
			int i_limit = prc_count;
			int i;

			for(i=0; i<i_limit; i++)
			{
				CStringArray l_pmx_name;
				CStringArray l_rcp_pre;
				CStringArray l_rcp_main;
				CStringArray l_rcp_post;

				int k_limit = prc_info[i].Get__Module_Size();
				int k;

				for(k=0; k<k_limit; k++)
				{
					CDB__Module_Info *p_md = prc_info[i].Get__Module_Info(k);

					CString prc_module = p_md->sTitle;
					CString rcp_pre  = "";
					CString rcp_main = "";
					CString rcp_post = "";

					int t_limit = p_md->sList_Item.GetSize();
					int t;

					for(t=0; t<t_limit; t++)
					{
						CString para_data = p_md->sList_Item[t];

						if(t == 0)			rcp_pre  = para_data;
						else if(t == 1)			rcp_main = para_data;
						else if(t == 2)			rcp_post = para_data;
					}

					l_pmx_name.Add(prc_module);
					l_rcp_pre.Add(rcp_pre);
					l_rcp_main.Add(rcp_main);
					l_rcp_post.Add(rcp_post);
				}

				_Add__PROCESSx_To_Tree_Route(p_tree, 
											h_root, 
											NULL, 
											l_pmx_name,
											l_rcp_pre,
											l_rcp_main,
											l_rcp_post);
			}
		}

		// LLx_PROC ...
		if(l__ll_proc_id.GetSize() > 0)
		{
			_Add__LLx_PROC_To_Tree_Route(p_tree, 
										h_root, 
										NULL, 
										l__ll_proc_id,
										l__ll_proc_pre,
										l__ll_proc_main,
										l__ll_proc_post);
		}

		// LOOPx_PROC ...
		if(l__loop_proc_id.GetSize() > 0)
		{
			_Add__LOOPx_PROC_To_Tree_Route(p_tree, 
											h_root, 
											NULL, 
											l__loop_proc_id,
											l__loop_proc_repeat);
		}

		// LLx_OUT ...
		if(l__ll_out_id.GetSize() > 0)
		{
			_Add__LLx_To_Tree_Route(p_tree,h_root,NULL, -1,l__ll_out_id,l__ll_out_mode,l__ll_out_slot);
		}

		// STx ...
		if(l__st_id.GetSize() > 0)
		{
			_Add__STx_To_Tree_Route(p_tree,h_root,NULL, l__st_id,l__st_mode,l__st_slot,l__st_sec);			
		}

		MACRO__Expand_All_Tree(p_tree);
	}

	UpdateData(FALSE);
	return 1;
}
int  CDlg__Lot_Recipe_Log
::_Get__Route_Cmmd(const CString& cmmd)
{
	if(cmmd.CompareNoCase("#PROCESS_START#") == 0)
	{
		return _ROUTE_CMMD__PROCESS_START;
	}
	if(cmmd.CompareNoCase("#PROCESS_END#") == 0)
	{
		return _ROUTE_CMMD__PROCESS_END;
	}

	if(cmmd.CompareNoCase("#LLx_PROC_START#") == 0)
	{
		return _ROUTE_CMMD__LLx_PROC_START;
	}
	if(cmmd.CompareNoCase("#LLx_PROC_END#") == 0)
	{
		return _ROUTE_CMMD__LLx_PROC_END;
	}

	if(cmmd.CompareNoCase("#LOOPx_PROC_START#") == 0)
	{
		return _ROUTE_CMMD__LOOPx_PROC_START;
	}
	if(cmmd.CompareNoCase("#LOOPx_PROC_END#") == 0)
	{
		return _ROUTE_CMMD__LOOPx_PROC_END;
	}

	if(cmmd.CompareNoCase("#ALx#") == 0)
	{
		return _ROUTE_CMMD__ALx;
	}
	if(cmmd.CompareNoCase("#LLx_IN#") == 0)
	{
		return _ROUTE_CMMD__BMx_IN;
	}
	if(cmmd.CompareNoCase("#LLx_OUT#") == 0)
	{
		return _ROUTE_CMMD__BMx_OUT;
	}
	if(cmmd.CompareNoCase("#STx#") == 0)
	{
		return _ROUTE_CMMD__STx;
	}

	if(cmmd.CompareNoCase("#DESCRIPT#") == 0)
	{
		return _ROUTE_CMMD__DESCRIPT;
	}

	return -1;
}

HTREEITEM CDlg__Lot_Recipe_Log
::_Add__PROCESSx_To_Tree_Route(CTreeCtrl* p_tree,
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

		int pm_id  = MACRO__Get_PMx_ID(pmx_name);
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
HTREEITEM CDlg__Lot_Recipe_Log
::_Add__LLx_PROC_To_Tree_Route(CTreeCtrl* p_tree,
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
HTREEITEM CDlg__Lot_Recipe_Log
::_Add__LOOPx_PROC_To_Tree_Route(CTreeCtrl* p_tree,
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

HTREEITEM CDlg__Lot_Recipe_Log
::_Add__ALx_To_Tree_Route(CTreeCtrl* p_tree,
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
HTREEITEM CDlg__Lot_Recipe_Log
::_Add__LLx_To_Tree_Route(CTreeCtrl* p_tree,
						  HTREEITEM h_root,
						  HTREEITEM h_after,
						  const int active_in_mode,
						  const CStringArray& l_bm_id,
						  const CStringArray& l_bm_mode,
						  const CStringArray& l_bm_slot)
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
			if((para__bm_mode.CompareNoCase("ALL") != 0)
			&& (para__bm_mode.CompareNoCase("ONLY_INPUT") != 0))
			{
				continue;
			}
		}
		else
		{
			if((para__bm_mode.CompareNoCase("ALL") != 0)
			&& (para__bm_mode.CompareNoCase("ONLY_OUTPUT")  != 0))
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
HTREEITEM CDlg__Lot_Recipe_Log
::_Add__STx_To_Tree_Route(CTreeCtrl* p_tree,
						  HTREEITEM h_root,
						  HTREEITEM h_after,
						  const CStringArray& l_st_id,
						  const CStringArray& l_st_mode,
						  const CStringArray& l_st_slot,
						  const CStringArray& l_st_sec)
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

	int i_limit = l_st_id.GetSize();
	int i;

	for(int i=0; i<i_limit; i++)
	{
		CString str_id = l_st_id[i];

		para__st_id.Format("ST%s", str_id);
		para__st_mode = l_st_mode[i];
		para__st_slot = l_st_slot[i];
		para__st_sec  = l_st_sec[i];

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
		}
	}

	return h_node;
}
