#include "stdafx.h"

#include "CLS__Wafer_Trace.h"
#include "Macro_Function.h"


void MACRO__Update__Wafer_Process(CTreeCtrl *p_tree, HTREEITEM h_node, CLS__MD_Info md_info)
{
	CString node_name;
	CString node_data;

	HTREEITEM h_name;
	HTREEITEM h_data;

	int img_id = 4;

	// 1.
	{
		node_name = "Name";
		h_name = p_tree->InsertItem(node_name, img_id,img_id, h_node, TVI_LAST);

		node_data = md_info.sPara__MODULE;
		p_tree->InsertItem(node_data, img_id,img_id, h_name, TVI_LAST);
	}
	// 2.
	{
		node_name = "R_T Offset";
		h_name = p_tree->InsertItem(node_name, img_id,img_id, h_node, TVI_LAST);

		node_data = md_info.sPara__RT_OFFSET;
		p_tree->InsertItem(node_data, img_id,img_id, h_name, TVI_LAST);
	}
	// 3.
	{
		node_name = "Recipe Name";
		h_name = p_tree->InsertItem(node_name, img_id,img_id, h_node, TVI_LAST);

		node_data = md_info.sPara__RECIPE;
		p_tree->InsertItem(node_data, img_id,img_id, h_name, TVI_LAST);
	}
	// 4.
	{
		node_name = "Log.Info";
		h_name = p_tree->InsertItem(node_name, img_id,img_id, h_node, TVI_LAST);

		node_data = md_info.sPara__LOG;
		p_tree->InsertItem(node_data, img_id,img_id, h_name, TVI_LAST);
	}
	// 5.
	{
		node_name = "Process Time";
		h_name = p_tree->InsertItem(node_name, img_id,img_id, h_node, TVI_LAST);

		// 1.
		{
			node_name = "Tack";
			h_data = p_tree->InsertItem(node_name, img_id,img_id, h_name, TVI_LAST);

			node_data = md_info.sPara__TIME_ACT;
			p_tree->InsertItem(node_data, img_id,img_id, h_data, TVI_LAST);
		}
		// 2.
		{
			node_name = "Start";
			h_data = p_tree->InsertItem(node_name, img_id,img_id, h_name, TVI_LAST);

			node_data = md_info.sPara__TIME_START;
			p_tree->InsertItem(node_data, img_id,img_id, h_data, TVI_LAST);
		}
		// 3.
		{
			node_name = "End";
			h_data = p_tree->InsertItem(node_name, img_id,img_id, h_name, TVI_LAST);

			node_data = md_info.sPara__TIME_END;
			p_tree->InsertItem(node_data, img_id,img_id, h_data, TVI_LAST);
		}
	}
	// 6.
	{
		node_name = "Process Result";
		h_name = p_tree->InsertItem(node_name, img_id,img_id, h_node, TVI_LAST);

		node_data = md_info.sPara__RESULT;
		p_tree->InsertItem(node_data, img_id,img_id, h_name, TVI_LAST);
	}
}

void MACRO__Update__Wafer_Action(CTreeCtrl *p_tree, HTREEITEM h_node, CLS__MD_Info md_info)
{
	CString node_name;
	CString node_data;

	HTREEITEM h_name;
	HTREEITEM h_data;

	int img_id = 3;

	// 1.
	{
		node_name = "Name";
		h_name = p_tree->InsertItem(node_name, img_id,img_id, h_node, TVI_LAST);

		node_data = md_info.sPara__MODULE;
		p_tree->InsertItem(node_data, img_id,img_id, h_name, TVI_LAST);
	}
	// 2.
	{
		node_name = "Time";
		h_name = p_tree->InsertItem(node_name, img_id,img_id, h_node, TVI_LAST);

		// 1.
		{
			node_name = "Tack";
			h_data = p_tree->InsertItem(node_name, img_id,img_id, h_name, TVI_LAST);

			node_data = md_info.sPara__TIME_ACT;
			p_tree->InsertItem(node_data, img_id,img_id, h_data, TVI_LAST);
		}			
		// 2.
		{
			node_name = "Start";
			h_data = p_tree->InsertItem(node_name, img_id,img_id, h_name, TVI_LAST);

			node_data = md_info.sPara__TIME_START;
			p_tree->InsertItem(node_data, img_id,img_id, h_data, TVI_LAST);
		}
		// 3.
		{
			node_name = "End";
			h_data = p_tree->InsertItem(node_name, img_id,img_id, h_name, TVI_LAST);

			node_data = md_info.sPara__TIME_END;
			p_tree->InsertItem(node_data, img_id,img_id, h_data, TVI_LAST);
		}
	}
	// 3.
	{
		node_name = "Result";
		h_name = p_tree->InsertItem(node_name, img_id,img_id, h_node, TVI_LAST);

		node_data = md_info.sPara__RESULT;
		p_tree->InsertItem(node_data, img_id,img_id, h_name, TVI_LAST);
	}
}

void MACRO__Update__Wafer_Tree(CTreeCtrl* p_tree, 
							   CLS__Wafer_Info* p_wfr_info,
							   bool active_move,
							   bool active_proc)
{	
	p_tree->DeleteAllItems();

	if(!p_wfr_info->Is_Active__WFR_INFO())
	{
		return;
	}

	// ...
	DS__Wafer_Info wfr_info;
	p_wfr_info->Get__WFR_INFO(wfr_info);

	// ...
	CString node_name;
	CString node_data;

	HTREEITEM h_root;
	HTREEITEM h_sub;
	HTREEITEM h_xxx;
	HTREEITEM h_yyy;
	HTREEITEM h_zzz;

	int img_id = 0;

	// Wafer ...
	{
		node_name = "Wafer";
		h_root = p_tree->InsertItem(node_name, img_id,img_id, TVI_ROOT, TVI_LAST);

		// 1. 
		{
			node_name = "ID";
			h_sub = p_tree->InsertItem(node_name, img_id,img_id, h_root, TVI_LAST);

			node_data.Format("P%1d:%02d", wfr_info.iPORTID,wfr_info.iSLOTID);
			p_tree->InsertItem(node_data, img_id,img_id, h_sub, TVI_LAST);
		}
		// 2.
		{
			node_name = "LotID";
			h_sub = p_tree->InsertItem(node_name, img_id,img_id, h_root, TVI_LAST);

			node_name = wfr_info.sLOTID;
			p_tree->InsertItem(node_name, img_id,img_id, h_sub, TVI_LAST);
		}
		// 3.
		{
			node_name = "PPID";
			h_sub = p_tree->InsertItem(node_name, img_id,img_id, h_root, TVI_LAST);

			node_data = wfr_info.sPPID;
			h_yyy = p_tree->InsertItem(node_data, img_id,img_id, h_sub, TVI_LAST);

			//
			int k_limit = wfr_info.sList__STEP_RCP.GetSize();
			int k;

			for(k=0; k<k_limit; k++)
			{
				node_data.Format("STEP_%02d - %s", k+1, wfr_info.sList__STEP_RCP[k]);
				p_tree->InsertItem(node_data, img_id,img_id, h_yyy, TVI_LAST);
			}

			node_data.Format("LOOP_%s - %s", wfr_info.sLOOP_ID,wfr_info.sLOOP_COUNT);
			p_tree->InsertItem(node_data, img_id,img_id, h_yyy, TVI_LAST);
		}
		// 4.
		{
			node_name = "Total Process Count";
			h_sub = p_tree->InsertItem(node_name, img_id,img_id, h_root, TVI_LAST);

			node_data.Format("%1d", wfr_info.sList__STEP_RCP.GetSize());
			p_tree->InsertItem(node_data, img_id,img_id, h_sub, TVI_LAST);
		}
		// 5.
		{
			node_name = "Current Process Count";
			h_sub = p_tree->InsertItem(node_name, img_id,img_id, h_root, TVI_LAST);

			node_data.Format("%1d", p_wfr_info->Get__CURRENT_PROCESS_SIZE());
			p_tree->InsertItem(node_data, img_id,img_id, h_sub, TVI_LAST);
		}
		// 6.
		if((active_move) || (active_proc))
		{
			node_name = "Process History";
			h_sub = p_tree->InsertItem(node_name, img_id,img_id, h_root, TVI_LAST);

			// ...
			int img_proc = 1;
			int img_move = 2;
			int n_cnt  = 0;

			int n_limit = p_wfr_info->Get__MD_SIZE();
			int n;

			for(n=0; n<n_limit; n++)
			{
				CLS__MD_Info md_info;
				if(p_wfr_info->Get__MD_INFO(n, md_info) < 0)		continue;

				if(md_info.bActive__PROCESS)
				{
					if(active_proc)
					{
						n_cnt++;

						node_name.Format("Module [%02d] - [%s] [%s] : [%s] [%s sec] [%s]", 
							n_cnt,
							md_info.sPara__RESULT,
							md_info.sPara__ACT,
							md_info.sPara__MODULE,
							md_info.sPara__TIME_ACT,
							md_info.sPara__RECIPE);

						h_xxx = p_tree->InsertItem(node_name, img_proc,img_proc, h_sub, TVI_LAST);

						MACRO__Update__Wafer_Process(p_tree, h_xxx, md_info);
					}
				}
				else
				{
					if(active_move)
					{
						n_cnt++;

						if(md_info.bActive__PICK)
						{
							node_name.Format("Module [%02d] - [%s] [%s] : [%s] <- [%s] : [%s sec]", 
								n_cnt,
								md_info.sPara__RESULT,
								md_info.sPara__ACT,
								md_info.sPara__ARM,
								md_info.sPara__MODULE,
								md_info.sPara__TIME_ACT);
						}
						else if(md_info.bActive__PLACE)
						{
							node_name.Format("Module [%02d] - [%s] [%s] : [%s] -> [%s] : [%s sec]", 
								n_cnt,
								md_info.sPara__RESULT,
								md_info.sPara__ACT,
								md_info.sPara__ARM,
								md_info.sPara__MODULE,
								md_info.sPara__TIME_ACT);
						}
						else
						{
							node_name.Format("Module [%02d] - [%s] [%s] : [%s][%s] & [%s] : [%s sec]", 
								n_cnt,
								md_info.sPara__RESULT,
								md_info.sPara__ACT,
								md_info.sPara__ROBOT,
								md_info.sPara__ARM,
								md_info.sPara__MODULE,
								md_info.sPara__TIME_ACT);
						}

						h_xxx = p_tree->InsertItem(node_name, img_move,img_move, h_sub, TVI_LAST);

						MACRO__Update__Wafer_Action(p_tree, h_xxx, md_info);
					}
				}
			}
		}

		// ...
	}
}


// ...
#define _CMMD_SIZE__WAFER					10
#define _CMMD_WFR__START					0
#define _CMMD_WFR__END					    1
#define _CMMD_WFR__PORTID					2
#define _CMMD_WFR__SLOTID					3
#define _CMMD_WFR__LOTID					4
#define _CMMD_WFR__PPID						5
#define _CMMD_WFR__MATERIALID				6
#define _CMMD_WFR__STEP_SIZE				7
#define _CMMD_WFR__STEP_XX					8
#define _CMMD_WFR__LOOP						9

#define _CMMD_SIZE__MDDULE					13
#define _CMMD_MD__START				        0
#define _CMMD_MD__END					    1
#define _CMMD_MD__ACT						2
#define _CMMD_MD__ROBOT						3
#define _CMMD_MD__ARM						4
#define _CMMD_MD__MD						5
#define _CMMD_MD__TIME_ACT					6
#define _CMMD_MD__TIME_START				7
#define _CMMD_MD__TIME_END					8
#define _CMMD_MD__RT_OFFSET                 9
#define _CMMD_MD__RECIPE                    10
#define _CMMD_MD__LOG                       11
#define _CMMD_MD__RESULT                    12


void MACRO__Update__Wafer_Info(const CString& file_path, CLS__Wafer_Info *p_wafer_info)
{
	p_wafer_info->Clear__ALL();

	// ...
	CString file_data;
	CStringArray l_line;

	MACRO__Get_File_Data(file_path, file_data);
	MACRO__Get_Line_List_From_File_Data(file_data, l_line);

	int t_limit = l_line.GetSize();
	int t;

	// Check Wafer ...
	{
		bool active__wafer_check = false;
		bool active__wafer_start = false;
		bool active__wafer_end   = false;

		DS__Wafer_Info ds_wfr;
		int step_size = 0;

		int line_start = 0;
		int line_end   = 0;

		for(t=0; t<t_limit; t++)
		{
			CString str_line = l_line[t];

			// ...
			{
				CString key_name;

				int k_limit = _CMMD_SIZE__WAFER;
				int k;

				for(k=0; k<k_limit; k++)
				{
						 if(k == _CMMD_WFR__START)			key_name = "#WAFER.START!";
					else if(k == _CMMD_WFR__END)			key_name = "#WAFER.END!";
					else if(k == _CMMD_WFR__PORTID)			key_name = "#PORTID=";
					else if(k == _CMMD_WFR__SLOTID)			key_name = "#SLOTID=";
					else if(k == _CMMD_WFR__LOTID)			key_name = "#LOTID=";
					else if(k == _CMMD_WFR__PPID)			key_name = "#PPID=";
					else if(k == _CMMD_WFR__MATERIALID)		key_name = "#MATERIALID=";
					else if(k == _CMMD_WFR__STEP_SIZE)		key_name = "#STEP_SIZE=";
					else if(k == _CMMD_WFR__LOOP)			key_name = "#LOOP=";
					else									continue;

					int s_index = str_line.Find(key_name);
					if(s_index < 0)			continue;

					CString str_data = str_line;
					str_data.Delete(0, s_index+key_name.GetLength());

					if(k == _CMMD_WFR__START)
					{
						active__wafer_start = true;
						active__wafer_end = false;

						line_start = t;
						break;
					}
					if(k == _CMMD_WFR__END)
					{
						if(active__wafer_start)
							active__wafer_check = true;

						active__wafer_start = false;
						active__wafer_end = true;

						line_end = t;
						break;
					}

					if(!active__wafer_start)
					{
						break;
					}

					if(k == _CMMD_WFR__LOTID)
					{
						ds_wfr.sLOTID = str_data;
						break;
					}
					if(k == _CMMD_WFR__PPID)
					{
						ds_wfr.sPPID = str_data;
						break;
					}
					if(k == _CMMD_WFR__PORTID)
					{
						ds_wfr.iPORTID = atoi(str_data);
						break;
					}
					if(k == _CMMD_WFR__SLOTID)
					{
						ds_wfr.iSLOTID = atoi(str_data);
						break;
					}
					if(k == _CMMD_WFR__MATERIALID)
					{
						ds_wfr.sMATERIALID = str_data;
						break;
					}
					if(k == _CMMD_WFR__STEP_SIZE)
					{
						step_size = atoi(str_data);
						break;
					}
					if(k == _CMMD_WFR__LOOP)
					{
						CStringArray l_para;
						MACRO__Convert__LIST(',', str_data, l_para);

						if(l_para.GetSize() > 0)		ds_wfr.sLOOP_ID    = l_para[0];
						if(l_para.GetSize() > 1)		ds_wfr.sLOOP_COUNT = l_para[1];
						break;
					}

					break;
				}
			}

			if(active__wafer_check)
			{
				break;
			}
		}

		// Check : Step_X ...
		if(active__wafer_check)
		{
			for(t=line_start; t<line_end; t++)
			{
				CString str_line = l_line[t];

				// ...
				CString key_name;

				int k_limit = step_size;
				int k;

				for(k=0; k<k_limit; k++)
				{
					key_name.Format("#STEP_%02d=", k+1);

					int s_index = str_line.Find(key_name);
					if(s_index < 0)			continue;

					CString str_data = str_line;
					str_data.Delete(0, s_index+key_name.GetLength());

					ds_wfr.sList__STEP_RCP.Add(str_data);
					break;
				}
			}
		}

		p_wafer_info->Load__WFR_INFO(ds_wfr);
	}

	// Check Module ...
	{
		bool active__wafer_start = false;
		bool active__wafer_end   = false;

		CLS__MD_Info md_info;

		for(t=0; t<t_limit; t++)
		{
			CString str_line = l_line[t];

			// ...
			CString key_name;

			int k_limit = _CMMD_SIZE__MDDULE;
			int k;

			for(k=0; k<k_limit; k++)
			{
					 if(k == _CMMD_MD__START)			key_name = "#ACT.START!";
				else if(k == _CMMD_MD__END)				key_name = "#ACT.END!";
				else if(k == _CMMD_MD__ACT)				key_name = "#ACT=";
				else if(k == _CMMD_MD__ROBOT)			key_name = "#ROBOT=";
				else if(k == _CMMD_MD__ARM)				key_name = "#ARM=";
				else if(k == _CMMD_MD__MD)				key_name = "#MD=";
				else if(k == _CMMD_MD__TIME_ACT)		key_name = "#TIME.ACT=";
				else if(k == _CMMD_MD__TIME_START)		key_name = "#TIME.START=";
				else if(k == _CMMD_MD__TIME_END)		key_name = "#TIME.END=";
				else if(k == _CMMD_MD__RT_OFFSET)		key_name = "#RT_OFFSET=";
				else if(k == _CMMD_MD__RECIPE)			key_name = "#RECIPE=";
				else if(k == _CMMD_MD__LOG)				key_name = "#LOG=";
				else if(k == _CMMD_MD__RESULT)			key_name = "#RESULT=";
				else									continue;

				int s_index = str_line.Find(key_name);
				if(s_index < 0)			continue;

				CString str_data = str_line;
				str_data.Delete(0, s_index+key_name.GetLength());

				if(k == _CMMD_MD__START)
				{
					active__wafer_start = true;
					active__wafer_end = false;

					md_info.Clear();
					break;
				}
				if(k == _CMMD_MD__END)
				{
					active__wafer_start = false;
					active__wafer_end = true;

					p_wafer_info->Load__MD_INFO(md_info);
					break;
				}

				if(!active__wafer_start)
				{
					break;
				}

				if(k == _CMMD_MD__ACT)
				{
					md_info.sPara__ACT = str_data;
					break;
				}
				if(k == _CMMD_MD__ROBOT)
				{
					md_info.sPara__ROBOT = str_data;
					break;
				}
				if(k == _CMMD_MD__ARM)
				{
					md_info.sPara__ARM = str_data;
					break;
				}
				if(k == _CMMD_MD__MD)
				{
					md_info.sPara__MODULE = str_data;
					break;
				}

				if(k == _CMMD_MD__TIME_ACT)
				{
					md_info.sPara__TIME_ACT = str_data;
					break;
				}
				if(k == _CMMD_MD__TIME_START)
				{
					md_info.sPara__TIME_START = str_data;
					break;
				}
				if(k == _CMMD_MD__TIME_END)
				{
					md_info.sPara__TIME_END = str_data;
					break;
				}

				if(k == _CMMD_MD__RT_OFFSET)
				{	
					md_info.sPara__RT_OFFSET = str_data;
					break;
				}
				if(k == _CMMD_MD__RECIPE)
				{
					md_info.sPara__RECIPE = str_data;
					break;
				}
				if(k == _CMMD_MD__LOG)
				{
					md_info.sPara__LOG = str_data;
					break;
				}
				if(k == _CMMD_MD__RESULT)
				{
					md_info.sPara__RESULT = str_data;
					break;
				}

				break;
			}
		}

		// ...
	}
}
