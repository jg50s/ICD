#include "stdafx.h"
#include "Dlg__Route_EDIT.h"
#include "Dlg__Route_EDIT__Def.h"

#include "CObj__Route_EDIT__KEY_DEF.h"
#include "Macro_Function.h"


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


#define _ROUTE_FILE_COL__NUMBER                 0
#define _ROUTE_FILE_COL__FILE                   1
#define _ROUTE_FILE_COL__DATE                   2

#define _ROUTE_EDIT_COL__RCP_SIZE               3
#define _ROUTE_EDIT_COL__PRE_RCP                0
#define _ROUTE_EDIT_COL__MAIN_RCP               1
#define _ROUTE_EDIT_COL__POST_RCP               2

#define _ROUTE_EDIT__PMx_MAX					6
#define _ROUTE_EDIT__PATH_MAX                   3

// ...
#define _PMx_RCP__NULL							"___"


// ...
void CDlg__Route_EDIT
::Change__Route_Edit_Mode(BOOL edit_mode)
{
	bActive__RouteEdit_Mode = edit_mode;

	// ...
	CTreeCtrl *p_tree_edit = &mTree__Route_Edit;

	if(edit_mode)
	{
		mCtrl__RouteEdit_Mode.SetWindowText("EDIT");
		p_tree_edit->EnableWindow(TRUE);

		mBtn__Rcp_Item_Delete.EnableWindow(TRUE);
		mBtn__Rcp_Item_Property.EnableWindow(TRUE);
	}
	else
	{
		mCtrl__RouteEdit_Mode.SetWindowText("VIEW");
		p_tree_edit->EnableWindow(FALSE);

		mBtn__Rcp_Item_Delete.EnableWindow(FALSE);
		mBtn__Rcp_Item_Property.EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

void CDlg__Route_EDIT
::Init__Route_Edit_Table()
{
	CDragDropTreeCtrl *p_tree = &mTree__Route_Edit;
	p_tree->DeleteAllItems();

	HTREEITEM h_top 
		= p_tree->InsertItem("ROUTE", _EDIT__ROUTE,_EDIT__ROUTE, TVI_ROOT, TVI_LAST);

	MACRO__Expand_All_Tree(p_tree);
}

int  CDlg__Route_EDIT
::Undo__Route_File(const CString& file_name,
				   const CString& file_date,
				   const BOOL edit_mode)
{
	// ...
	{
		bActive__Recipe_Changed = FALSE;

		printf(" * Recipe_Changed : FALSE \n");
	}

	// ...
	CButton *p_btn__file_name = &mCtrl__RouteEdit_FileName;
	CButton *p_btn__file_date = &mCtrl__RouteEdit_FileDate;

	p_btn__file_name->SetWindowText(file_name);
	p_btn__file_date->SetWindowText(file_date);

	Change__Route_Edit_Mode(edit_mode);

	if(file_name.GetLength() < 1)
	{
		Init__Route_Edit_Table();;
		return 1;
	}

	// ...
	CString dir_root  = "";
	CString dir_sub   = "ROUTE";
	CString file_ext  = "rte";
	CString file_data = "";

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		int eqp_id = 0;

		x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_root);
	}

	// ...
	{
		CString file_path;

		file_path.Format("%s\\%s\\%s.%s", dir_root,dir_sub,file_name,file_ext);
		printf("  * file_path : [%s] \n", file_path);

		if(MACRO__Get_File_Data(file_path, file_data) < 0)
		{
			CString str_msg;

			str_msg.Format("File Error : \"%s\" ", file_path);
			mStr__Sys_Msg = str_msg;

			printf(str_msg);
			printf("\n");

			Init__Route_Edit_Table();;
			UpdateData(FALSE);
			return -1;
		}
		
		if(MACRO__Check_Route_File_Edit_Type(file_data) < 0)
		{
			CString err_msg = "선택된 Route File이 Edit Type이 아닙니다 !";
			MessageBox(err_msg, "File Type Error !", MB_OK|MB_ICONERROR);

			mStr__Sys_Msg = err_msg;

			Init__Route_Edit_Table();;
			UpdateData(FALSE);
			return -1;
		}
	}

	// ...
	{
		p_btn__file_name->SetWindowText(file_name);
		p_btn__file_date->SetWindowText(file_date);

		Init__Route_Edit_Table();;
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
	CStringArray l__ll_in_cooling_sec;

	CStringArray l__ll_out_id;
	CStringArray l__ll_out_mode;
	CStringArray l__ll_out_slot;
	CStringArray l__ll_out_cooling_sec;

	CStringArray l__st_id;
	CStringArray l__st_mode;
	CStringArray l__st_slot;
	CStringArray l__st_sec;
	CStringArray l__st_n2_purge;

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
	CString rcp_item__ll_cooling_sec = "";

	CString rcp_item__st_id   = "";
	CString rcp_item__st_mode = "";
	CString rcp_item__st_slot = "";
	CString rcp_item__st_sec  = "";
	CString rcp_item__st_n2_purge = "";

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

			int new_cmmd = Get__Route_Cmmd(word);
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
						rcp_item__ll_cooling_sec = "";
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
						rcp_item__st_n2_purge = "";
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
						else if(para == 4)		rcp_item__ll_cooling_sec = word;
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
						else if(para == 5)		rcp_item__st_n2_purge = word;
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
						l__ll_in_cooling_sec.Add("__");
					}
					else if(command == _ROUTE_CMMD__BMx_OUT)
					{
						l__ll_out_id.Add(rcp_item__ll_id);
						l__ll_out_mode.Add(rcp_item__ll_mode);
						l__ll_out_slot.Add(rcp_item__ll_slot);
						l__ll_out_cooling_sec.Add(rcp_item__ll_cooling_sec);
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
						l__st_n2_purge.Add(rcp_item__st_n2_purge);
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
		CTreeCtrl *p_tree = &mTree__Route_Edit;
		HTREEITEM h_root = p_tree->GetRootItem();

		// ALx ...
		if(l__al_id.GetSize() > 0)
		{
			Add__ALx_To_Tree_Route(p_tree, h_root, NULL, l__al_id,l__al_angle,l__al_slot);
		}

		// LLx_IN ...
		if(l__ll_in_id.GetSize() > 0)
		{
			Add__LLx_To_Tree_Route(p_tree,h_root,NULL, 1,l__ll_in_id,l__ll_in_mode,l__ll_in_slot,l__ll_in_cooling_sec);
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

				Add__PROCESSx_To_Tree_Route(false,
											p_tree,
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
			Add__LLx_PROC_To_Tree_Route(p_tree, 
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
			Add__LOOPx_PROC_To_Tree_Route(p_tree, 
										  h_root, 
										  NULL, 
										  l__loop_proc_id,
										  l__loop_proc_repeat);
		}

		// LLx_OUT ...
		if(l__ll_out_id.GetSize() > 0)
		{
			Add__LLx_To_Tree_Route(p_tree,h_root,NULL, -1,l__ll_out_id,l__ll_out_mode,l__ll_out_slot,l__ll_out_cooling_sec);
		}

		// STx ...
		if(l__st_id.GetSize() > 0)
		{
			Add__STx_To_Tree_Route(p_tree,h_root,NULL, l__st_id,l__st_mode,l__st_slot,l__st_sec,l__st_n2_purge);			
		}

		MACRO__Expand_All_Tree(p_tree);
	}

	// ...
	{
		CString str_msg;

		str_msg.Format("File Upload : \"%s\" ...", file_name);
		mStr__Sys_Msg = str_msg;

		printf(str_msg);
		printf("\n");
	}

	mStr_Edit__Error_Msg = "";
	
	UpdateData(FALSE);
	return 1;
}
int  CDlg__Route_EDIT
::Get__Route_Cmmd(const CString& cmmd)
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
