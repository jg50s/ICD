#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Wafer_Trace_Sel.h"
#include "Macro_Function.h"


// ...
#define _CFG__TBL_COL_SIZE						4
#define _TBL_COL__NUMBER						0
#define _TBL_COL__PORTID						1
#define _TBL_COL__LOTID							2
#define _TBL_COL__PATH							3


void CDlg__Wafer_Trace_Sel
::_Make__Wafer_List(CListCtrl *p_table)
{
	CStringArray l__col_name;
	CUIntArray   l__col_width;

	// ...
	{
		l__col_name.RemoveAll();
		l__col_width.RemoveAll();

		int i_limit = _CFG__TBL_COL_SIZE;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == _TBL_COL__NUMBER)
			{
				l__col_name.Add("No.");
				l__col_width.Add(50);
			}
			else if(i == _TBL_COL__PORTID)
			{
				l__col_name.Add("LPx");
				l__col_width.Add(50);
			}
			else if(i == _TBL_COL__LOTID)
			{
				l__col_name.Add("LotID");
				l__col_width.Add(300);
			}
			else if(i == _TBL_COL__PATH)
			{
				l__col_name.Add("Path");
				l__col_width.Add(0);
			}
			else
			{
				continue;
			}
		}
	}

	// ...
	{
		p_table->DeleteAllItems();

		for(int i=0; i<_CFG__TBL_COL_SIZE; i++)
		{
			p_table->DeleteColumn(0);
		}
	}

	// ...
	{
		CString col_name;
		int col_cx;

		int limit = l__col_name.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			col_name = l__col_name[i];
			col_cx   = (int) l__col_width[i];

			p_table->InsertColumn(i, col_name, LVCFMT_CENTER, col_cx);
		}		
	}
}

void CDlg__Wafer_Trace_Sel
::_Add__Wafer_List(CListCtrl *p_table)
{
	p_table->DeleteAllItems();
	p_table->SetRedraw(FALSE);

	// ...
	iIndex__Lot_Table = -1;

	mList__Slot_Info.ResetContent();
	sList__Slot_Path.RemoveAll();

	mBtn_OK.EnableWindow(FALSE);

	// ...
	CStringArray l_log_history;

	// ...
	{
		CStringArray l_log_xxxx;

		MACRO__Get_Dir_Date_List(sPara__DIR_ROOT, l_log_history,l_log_xxxx);
		MACRO__Change_Order(l_log_history, true);
	}

	// ...
	CStringArray l_portid;
	CStringArray l_slotid;
	CStringArray l_lotid;
	CStringArray l_lot_path;
	
	CString cur_date;
	CString pre_date;

	int loop_count = 0;
	
	int active__1day_before = mCheck__1_Day_Before.GetCheck();
	int active__lotid_check = mCheck__LotID.GetCheck();

	while(1)
	{
		CStringArray l_dir_name;
		CStringArray l_dir_date;

		CString dir_log;
		CString dir_sub;

		if(loop_count == 0)
		{
			cur_date = MACRO__Get_Current_Date(); 
			dir_sub = cur_date;
		}
		else
		{
			dir_sub = pre_date;
		}

		dir_log  = sPara__DIR_ROOT;
		dir_log += "\\";
		dir_log += dir_sub;

		MACRO__Get_Dir_Date_List(dir_log, l_dir_name,l_dir_date);

		// ...
		CString dir_sub_org = dir_sub;

		for(int i=0; i<iPara__LPx_SIZE; i++)
		{
			int i_portid = i + 1;

			if(i_portid == 1)		
			{
				if(mCheck_LP1.GetCheck() < 1)		continue;
			}
			else if(i_portid == 2)
			{
				if(mCheck_LP2.GetCheck() < 1)		continue;
			}
			else if(i_portid == 3)
			{
				if(mCheck_LP3.GetCheck() < 1)		continue;
			}
			else if(i_portid == 4)
			{
				if(mCheck_LP4.GetCheck() < 1)		continue;
			}
			else if(i_portid == 5)
			{
				if(mCheck_LP5.GetCheck() < 1)		continue;
			}
			else
			{
				continue;
			}

			// ...
			CString lp_lotid = "";

			if(active__lotid_check > 0)
			{
				if(i < iPara__LPx_SIZE)
				{
					if(i < sPara__LOTID.GetSize())
						lp_lotid = sPara__LOTID[i];
				}
			}
			
			// ...
			int k_limit = l_dir_name.GetSize();
			int k;
			
			for(k=0; k<k_limit; k++)
			{
				CString check__dir_name = l_dir_name[k];

				// ...
				CString para_portid;
				CString para_lotid;

				// ...
				{
					CStringArray l_para;
					MACRO__Convert__LIST('+', check__dir_name, l_para);		

					if(l_para.GetSize() > 1)		para_portid = l_para[1];
					if(l_para.GetSize() > 2)		para_lotid  = l_para[2];
				}

				// PortID Check ...
				{
					int check_portid = atoi(para_portid);

					if(i_portid != check_portid)
						continue;
				}

				if(active__lotid_check > 0)
				{
					if(lp_lotid.CompareNoCase(para_lotid) != 0)
						continue;
				}
				
				dir_sub  = dir_sub_org;
				dir_sub += "\\";
				dir_sub += check__dir_name;

				l_portid.Add(para_portid);
				l_lotid.Add(para_lotid);
				l_lot_path.Add(dir_sub);
			}
		}

		if(active__1day_before > 0)
		{
			loop_count++;
			if(loop_count > 1)					break;
			
			if(l_log_history.GetSize() > 0)
			{
				pre_date = l_log_history[0];

				if(pre_date != cur_date)		continue;
			}
			if(l_log_history.GetSize() > 1)
			{
				pre_date = l_log_history[1];

				if(pre_date != cur_date)		continue;
			}
		}
		break;
	}

	// ...
	CString str_item;

	int i_limit = l_portid.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		int k_limit = _CFG__TBL_COL_SIZE;
		int k;

		for(k=0; k<k_limit; k++)
		{
				 if(k == _TBL_COL__NUMBER)			str_item.Format("%1d", i+1);
			else if(k == _TBL_COL__PORTID)			str_item = l_portid[i];
			else if(k == _TBL_COL__LOTID)			str_item = l_lotid[i];
			else if(k == _TBL_COL__PATH)			str_item = l_lot_path[i];
			else									continue;

			if(k == _TBL_COL__NUMBER)		p_table->InsertItem(i, str_item, 0);
			else							p_table->SetItem(i,k, LVIF_TEXT,str_item,0,0,0,0);
		}
	}

	p_table->SetRedraw(TRUE);

	if(i_limit > 0)
	{
		int r_index = 0;

		p_table->SetSelectionMark(r_index);
		p_table->EnsureVisible(r_index, FALSE ); 
		p_table->SetItemState(r_index, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		p_table->SetFocus();

		// _Add__Slot_Info(p_table, r_index, true);
		_Add__Slot_Info(p_table, r_index);
	}
}

void CDlg__Wafer_Trace_Sel
::_Add__Slot_Info(CListCtrl *p_table, 
				  const int r_index,
				  const bool active_focus)
{
	if((iIndex__Lot_Table <  0)
	|| (iIndex__Lot_Table != r_index))
	{
		mList__Slot_Info.ResetContent();
		sList__Slot_Path.RemoveAll();
	}
	if(iIndex__Lot_Table == r_index)
	{
		return;
	}
	iIndex__Lot_Table = r_index;

	// ...
	CString str_ptn = p_table->GetItemText(r_index, _TBL_COL__PORTID);
	CString dir_log = p_table->GetItemText(r_index, _TBL_COL__PATH);

	printf("CDlg__Wafer_Trace_Sel::_Add__Slot_Info() \n");
	printf(" * rindex  <- [%1d] \n", r_index);
	printf(" * str_ptn <- [%s] \n",  str_ptn);
	printf(" * dir_wfr <- [%s] \n",  dir_log);

	// ...
	CString dir_wfr;
	CStringArray l_file_name;
	CStringArray l_file_date;
	CString file_ext = "wfr";

	dir_wfr.Format("%s\\%s", sPara__DIR_ROOT,dir_log);
	MACRO__Get_File_List(dir_wfr,file_ext, l_file_name,l_file_date);
	MACRO__Change_Order(l_file_name, false, true);

	int t_limit = l_file_name.GetSize();
	int t;

	for(t=0; t<t_limit; t++)
	{
		CString file_name   = l_file_name[t];					
		CString para_slotid = file_name;

		printf(" ?? %1d) [%s] \n", t+1,file_name);

		CString lp_name;
		lp_name.Format("P%s_", str_ptn);
		int s_index = para_slotid.Find(lp_name);
		if(s_index < 0)		continue;
		para_slotid.Delete(0, s_index+lp_name.GetLength());

		printf(" !! %1d) [%s] \n", t+1,para_slotid);

		mList__Slot_Info.AddString(para_slotid);

		file_name += ".";
		file_name += file_ext;
		sList__Slot_Path.Add(file_name);
	}

	if(active_focus)
	{
		mList__Slot_Info.SetCurSel(r_index);

		mBtn_OK.EnableWindow(TRUE);
	}
	else
	{
		mBtn_OK.EnableWindow(FALSE);
	}
}

void CDlg__Wafer_Trace_Sel::_Get__SEL_INFO()
{
	UpdateData(TRUE);

	// ...
	{
		iSel__PortID = -1;
		iSel__SlotID = -1;
		sSel__LotID  = "";
	}

	// ...
	CListCtrl* p_table = &mCtrl__Wafer_Info;
	CString ch_data;

	int r_index = p_table->GetSelectionMark();
	if(r_index < 0)		return;

	ch_data = p_table->GetItemText(r_index, _TBL_COL__PORTID);
	iSel__PortID = atoi(ch_data);

	sSel__LotID = p_table->GetItemText(r_index, _TBL_COL__LOTID);

	CString dir_log = p_table->GetItemText(r_index, _TBL_COL__PATH);

	// ...
	r_index = mList__Slot_Info.GetCurSel();
	if(r_index >= 0)
	{
		mList__Slot_Info.GetText(r_index, ch_data);
		iSel__SlotID = atoi(ch_data);

		CString file_name = sList__Slot_Path[r_index];
		sSel__Path.Format("%s\\%s", dir_log,file_name);
	}
	else
	{
		iSel__SlotID = -1;
		sSel__Path = "";
	}

	printf("CDlg__Wafer_Trace_Sel::_Get__SEL_INFO() \n");
	printf(" * SlotID   <- [%1d] \n", iSel__SlotID);
	printf(" * Wfr_Path <- [%s] \n",  sSel__Path);
}
