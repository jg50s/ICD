#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Wafer_DA_Chart.h"


// ...
#define _CFG__TBL_COL_SIZE						2
#define _TBL_COL__NUMBER						0
#define _TBL_COL__SLOTID						1


void CDlg__Wafer_DA_Chart
::_Make__Slot_List()
{
	CListCtrl* p_table = &mList__Slot_Info;

	// ...
	{
		int list_view_stype;

		list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
		list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
		list_view_stype += LVS_EX_INFOTIP;
		list_view_stype += LVS_EX_CHECKBOXES;

		p_table->SetExtendedStyle(list_view_stype);
	}

	// ...
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
				l__col_name.Add("Sel.");
				l__col_width.Add(30);
			}
			else if(i == _TBL_COL__SLOTID)
			{
				l__col_name.Add("Slot");
				l__col_width.Add(80);
			}
			else
			{
				break;
			}
		}
	}

	// ...
	{
		p_table->DeleteAllItems();

		int i_limit = _CFG__TBL_COL_SIZE;
		int i;

		for(i=0; i<i_limit; i++)
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

void CDlg__Wafer_DA_Chart
::_Add__Slot_List(const CStringArray& l_slot)
{
	CListCtrl* p_table = &mList__Slot_Info;
	p_table->DeleteAllItems();
	p_table->SetRedraw(FALSE);

	// ...
	CString str_item;

	int i_limit = l_slot.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		int k_limit = _CFG__TBL_COL_SIZE;
		int k;

		for(k=0; k<k_limit; k++)
		{
			     if(k == _TBL_COL__NUMBER)			str_item = "";
			else if(k == _TBL_COL__SLOTID)			str_item = l_slot[i];
			else									break;

			if(k == 0)		p_table->InsertItem(i, str_item, 0);
			else			p_table->SetItem(i,k, LVIF_TEXT,str_item,0,0,0,0);
		}
	}

	p_table->SetRedraw(TRUE);
}
CString CDlg__Wafer_DA_Chart::
_Get__ID_Of_Slot_List(const int r_index)
{
	return mList__Slot_Info.GetItemText(r_index, _TBL_COL__SLOTID);
}
