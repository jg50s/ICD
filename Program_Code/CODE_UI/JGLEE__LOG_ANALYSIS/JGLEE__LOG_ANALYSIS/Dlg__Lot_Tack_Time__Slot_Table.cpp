#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Lot_Tack_Time.h"


// ...
#define _CFG__TBL_COL_SIZE						3
#define _TBL_COL__NUMBER						0
#define _TBL_COL__SLOTID						1
#define _TBL_COL__ACT_CNT						2


void CDlg__Lot_Tack_Time
::_Make__Slot_List()
{
	CReportCtrl* p_table = &mList__Slot_Info;

	p_table->SetNoSort(true);

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
				l__col_width.Add(60);
			}
			else if(i == _TBL_COL__ACT_CNT)
			{
				l__col_name.Add("Count");
				l__col_width.Add(60);
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

void CDlg__Lot_Tack_Time
::_Add__Slot_List(const CStringArray& l_slot)
{
	CReportCtrl* p_table = &mList__Slot_Info;
	p_table->DeleteAllItems();
	p_table->SetRedraw(FALSE);

	// ...
	COLORREF t_color = RGB(0,0,0);

	int i_limit = l_slot.GetSize();
	if(i_limit > _CFG__SLOT_MAX)		i_limit = _CFG__SLOT_MAX;

	for(int i=0; i<i_limit; i++)
	{
		COLORREF b_color = cPara__Slot_Color_RGB[i];
		CString str_item;

		// ...
		int k_limit = _CFG__TBL_COL_SIZE;
		int k;

		for(k=0; k<k_limit; k++)
		{
				 if(k == _TBL_COL__NUMBER)			str_item = "";
			else if(k == _TBL_COL__SLOTID)			str_item = l_slot[i];
			else if(k == _TBL_COL__ACT_CNT)			str_item = "";
			else									break;

			if(k == 0)
			{
				p_table->InsertItem(i, str_item, t_color,b_color);
			}
			else
			{
				p_table->SetItem(i,k, LVIF_TEXT,str_item,0,0,0,0);
			}
		}
	}

	p_table->SetRedraw(TRUE);
}
void CDlg__Lot_Tack_Time
::_Update__Slot_Act_Cnt()
{
	CListCtrl* p_table = &mList__Slot_Info;

	CString str_data;
	int col;
	
	int i_limit = p_table->GetItemCount();
	int i;

	for(i=0; i<i_limit; i++)
	{
		col = _TBL_COL__SLOTID;
		CString str_id = p_table->GetItemText(i, col);

		str_data.Format("%1d", mSlot_Tack.Get__Tack_Count(str_id));
		col = _TBL_COL__ACT_CNT;
		p_table->SetItem(i,col, LVIF_TEXT,str_data,0,0,0,0);
	}
}
CString CDlg__Lot_Tack_Time
::_Get__ID_Of_Slot_List(const int r_index)
{
	return mList__Slot_Info.GetItemText(r_index, _TBL_COL__SLOTID);
}

int  CDlg__Lot_Tack_Time
::_Get__Selected_Index_Of_Slot_List()
{
	CListCtrl* p_table = &mList__Slot_Info;

	return p_table->GetSelectionMark();
}
int  CDlg__Lot_Tack_Time
::_Get__Checked_Count_Of_Slot_List()
{
	CListCtrl* p_table = &mList__Slot_Info;

	int i_count = 0;

	int i_limit = p_table->GetItemCount();
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(p_table->GetCheck(i) < 1)		
			continue;

		i_count++;
	}
	return i_count;
}
