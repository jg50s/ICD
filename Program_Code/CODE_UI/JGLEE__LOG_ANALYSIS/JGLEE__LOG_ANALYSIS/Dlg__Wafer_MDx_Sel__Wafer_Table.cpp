#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Wafer_MDx_Sel.h"
#include "Macro_Function.h"


// ...
#define _CFG__TBL_COL_SIZE						5
#define _TBL_COL__NUMBER						0
#define _TBL_COL__MODULE						1
#define _TBL_COL__TACK_TIME						2
#define _TBL_COL__RECIPE						3
#define _TBL_COL__LOG_PATH						4

// ...
void CDlg__Wafer_MDx_Sel::
_Make__MDx_List(CListCtrl *p_table)
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
			else if(i == _TBL_COL__MODULE)
			{
				l__col_name.Add("Module");
				l__col_width.Add(100);
			}
			else if(i == _TBL_COL__TACK_TIME)
			{
				l__col_name.Add("Time");
				l__col_width.Add(100);
			}
			else if(i == _TBL_COL__RECIPE)
			{
				l__col_name.Add("Recipe");
				l__col_width.Add(200);
			}
			else if(i == _TBL_COL__LOG_PATH)
			{
				l__col_name.Add("Path");
				l__col_width.Add(250);
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

void CDlg__Wafer_MDx_Sel::
_Add__MDx_List(CListCtrl *p_table)
{
	p_table->DeleteAllItems();
	p_table->SetRedraw(FALSE);

	// ...
	CStringArray l_md_info;
	CStringArray l_tack;
	CStringArray l_rcp;
	CStringArray l_log_info;

	pWfr_Info->Get__PROCESS_LOG(l_md_info,l_tack,l_rcp,l_log_info);

	// ...
	CString str_item;

	int i_limit = l_md_info.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_md   = l_md_info[i];
		CString str_tack = l_tack[i];
		CString str_rcp  = l_rcp[i];
		CString str_log  = l_log_info[i];
		int col;

		// NO.
		str_item.Format("%1d", i+1);
		p_table->InsertItem(i, str_item, 0);

		//
		col = _TBL_COL__MODULE;
		str_item = str_md;
		p_table->SetItem(i,col, LVIF_TEXT,str_item,0,0,0,0);

		col = _TBL_COL__TACK_TIME;
		str_item = str_tack;
		p_table->SetItem(i,col, LVIF_TEXT,str_item,0,0,0,0);

		col = _TBL_COL__RECIPE;
		str_item = str_rcp;
		p_table->SetItem(i,col, LVIF_TEXT,str_item,0,0,0,0);

		col = _TBL_COL__LOG_PATH;
		str_item = str_log;
		p_table->SetItem(i,col, LVIF_TEXT,str_item,0,0,0,0);
	}

	p_table->SetRedraw(TRUE);

	if(i_limit > 0)
	{
		int r_index = 0;

		p_table->SetSelectionMark(r_index);
		p_table->EnsureVisible(r_index, FALSE ); 
		p_table->SetItemState(r_index, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		p_table->SetFocus();
	}
}

CString CDlg__Wafer_MDx_Sel::
_Get__MDx_Name_Of_MDx_List()
{
	CListCtrl* p_table = &mList__MDx_Sel;

	int r_index = p_table->GetSelectionMark();
	if(r_index < 0)			return "";

	int col = _TBL_COL__MODULE;
	return p_table->GetItemText(r_index,col);
}
CString CDlg__Wafer_MDx_Sel::
_Get__Log_Path_Of_MDx_List()
{
	CListCtrl* p_table = &mList__MDx_Sel;

	int r_index = p_table->GetSelectionMark();
	if(r_index < 0)			return "";

	int col = _TBL_COL__LOG_PATH;
	return p_table->GetItemText(r_index,col);
}
