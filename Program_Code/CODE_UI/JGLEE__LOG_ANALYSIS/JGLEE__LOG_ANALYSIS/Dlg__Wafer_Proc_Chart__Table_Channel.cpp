#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Wafer_Proc_Chart.h"
#include "Macro_Function.h"


// ...
#define _CFG__TBL_COL_SIZE						5
#define _TBL_COL__NUMBER						0
#define _TBL_COL__NAME							1
#define _TBL_COL__LOG_TYPE						2
#define _TBL_COL__LOG_COUNT						3
#define _TBL_COL__CHANNEL						4

// ...
void CDlg__Wafer_Proc_Chart::
_Make__Channel_List(CListCtrl *p_table)
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
			else if(i == _TBL_COL__NAME)
			{
				l__col_name.Add("Name");
				l__col_width.Add(250);
			}
			else if(i == _TBL_COL__LOG_TYPE)
			{
				l__col_name.Add("Log Type");
				l__col_width.Add(100);
			}
			else if(i == _TBL_COL__LOG_COUNT)
			{
				l__col_name.Add("Log Count");
				l__col_width.Add(100);
			}
			else if(i == _TBL_COL__CHANNEL)
			{
				l__col_name.Add("Channel");
				l__col_width.Add(300);
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

void CDlg__Wafer_Proc_Chart::
_Add__Channel_List()
{
	CListCtrl *p_table = &mList__Channel_Table;
	p_table->DeleteAllItems();
	p_table->SetRedraw(FALSE);

	// ...
	CStringArray l_name;
	CStringArray l_channel;
	CStringArray l_log_ccnt;

	pLog_Proc->Get__Template_Interrval(l_name, l_channel, l_log_ccnt);

	// ...
	CString log_type = "INTERVAL";
	CString str_item;

	int i_limit = l_name.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_name    = l_name[i];
		CString str_channel = l_channel[i];
		CString str_count   = l_log_ccnt[i];
		int col;

		// NO.
		str_item.Format("%02d", i+1);
		p_table->InsertItem(i, str_item, 0);

		//
		col = _TBL_COL__NAME;
		str_item = str_name;
		p_table->SetItem(i,col, LVIF_TEXT,str_item,0,0,0,0);

		col = _TBL_COL__LOG_TYPE;
		str_item = log_type;
		p_table->SetItem(i,col, LVIF_TEXT,str_item,0,0,0,0);

		col = _TBL_COL__LOG_COUNT;
		str_item = str_count;
		p_table->SetItem(i,col, LVIF_TEXT,str_item,0,0,0,0);

		col = _TBL_COL__CHANNEL;
		str_item = str_channel;
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

int CDlg__Wafer_Proc_Chart::
_Get__Selected_Index_Of_Channel_List()
{
	CListCtrl* p_table = &mList__Channel_Table;

	return p_table->GetSelectionMark();
}
CString CDlg__Wafer_Proc_Chart::
_Get__Name_Of_Channel_List(const int r_index)
{
	CListCtrl* p_table = &mList__Channel_Table;

	int col = _TBL_COL__NAME;
	return p_table->GetItemText(r_index,col);
}
CString CDlg__Wafer_Proc_Chart::
_Get__Channel_Of_Channel_List(const int r_index)
{
	CListCtrl* p_table = &mList__Channel_Table;

	int col = _TBL_COL__CHANNEL;
	return p_table->GetItemText(r_index,col);
}
CString CDlg__Wafer_Proc_Chart::
_Get__ID_Of_Channel_List(const int r_index)
{
	CListCtrl* p_table = &mList__Channel_Table;

	int col = _TBL_COL__NUMBER;
	return p_table->GetItemText(r_index,col);
}
