#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Lot_Recipe_Log.h"
#include "Macro_Function.h"


// ...
#define _CFG__TBL_COL_SIZE						9
#define _TBL_COL__SLOTID						0
#define _TBL_COL__PM1							1
#define _TBL_COL__PM2							2
#define _TBL_COL__PM3							3
#define _TBL_COL__PM4							4
#define _TBL_COL__PM5							5
#define _TBL_COL__PM6							6
#define _TBL_COL__LL1							7
#define _TBL_COL__LL2							8


void CDlg__Lot_Recipe_Log
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
		// list_view_stype += LVS_EX_CHECKBOXES;

		p_table->SetExtendedStyle(list_view_stype);
		p_table->ModifyStyle(LVS_OWNERDRAWFIXED, 0, 0);
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
			CString col_name;
			
				 if(i == _TBL_COL__SLOTID)			col_name = "Slot";
			else if(i == _TBL_COL__PM1)				col_name = "PM1";
			else if(i == _TBL_COL__PM2)				col_name = "PM2";
			else if(i == _TBL_COL__PM3)				col_name = "PM3";
			else if(i == _TBL_COL__PM4)				col_name = "PM4";
			else if(i == _TBL_COL__PM5)				col_name = "PM5";
			else if(i == _TBL_COL__PM6)				col_name = "PM6";
			else if(i == _TBL_COL__LL1)				col_name = "LL1";
			else if(i == _TBL_COL__LL2)				col_name = "LL2";
			else									break;

			l__col_name.Add(col_name);
			l__col_width.Add(75);
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

void CDlg__Lot_Recipe_Log
::_Add__Slot_List(const CStringArray& l_slot)
{
	CReportCtrl* p_table = &mList__Slot_Info;
	p_table->DeleteAllItems();
	p_table->SetRedraw(FALSE);

	// ...
	COLORREF t_color = RGB(0,0,255);
	COLORREF b_color = RGB(255,255,255);
	COLORREF gray_color = RGB(215,215,215);

	int i_limit = l_slot.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CString str_item;

		// ...
		int k_limit = _CFG__TBL_COL_SIZE;
		int k;

		for(k=0; k<k_limit; k++)
		{
			if(k == _TBL_COL__SLOTID)			str_item = l_slot[i];

			if(k == 0)
			{
				p_table->InsertItem(i, str_item, t_color,b_color);
			}
			else
			{
				p_table->SetItemText(i,k, "", t_color,gray_color);
			}
		}
	}

	p_table->SetRedraw(TRUE);
}

void CDlg__Lot_Recipe_Log
::_Update__MDx_Of_Slot_List()
{
	CReportCtrl* p_table = &mList__Slot_Info;

	CStringArray l__md_name;

	// ...
	COLORREF t_color = RGB(255,255,255);
	COLORREF b_color = RGB(50,50,210);

	int i_limit = p_table->GetItemCount();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_id = p_table->GetItemText(i, _TBL_COL__SLOTID);

		CLS__Slot_Process_Info *p_slot_db = mSlot_Proc.Get_Addr__Slot_Process_Info(str_id);
		CStringArray l__slot_md;

		int k_limit = p_slot_db->sList__Module.GetSize();
		for(int k=0; k<k_limit; k++)
		{
			CString md_name = p_slot_db->sList__Module[k];

			if(MACRO__Check_Stringarray(md_name, l__md_name) < 0)
			{
				l__md_name.Add(md_name);
			}
			if(MACRO__Check_Stringarray(md_name, l__slot_md) > 0)
			{
				continue;
			}
			l__slot_md.Add(md_name);

			int col_id = _Get__MDx_ID_Of_Slot_List(md_name);
			if(col_id < 0)			continue;

			CString str_data = "Y";
			
			int i_count = MACRO__Get_Count_Of_Stringarray(md_name, p_slot_db->sList__Module);;
			// if(i_count > 1)		str_data.Format("%1d", i_count);
			str_data.Format("%1d", i_count);

			p_table->SetItemText(i,col_id, str_data, t_color,b_color);
		}
	}

	// ...
	{
		// ...
		{
			mCheck_PM1.EnableWindow(FALSE);
			mCheck_PM2.EnableWindow(FALSE);
			mCheck_PM3.EnableWindow(FALSE);
			mCheck_PM4.EnableWindow(FALSE);
			mCheck_PM5.EnableWindow(FALSE);
			mCheck_PM6.EnableWindow(FALSE);

			mCheck_LL1.EnableWindow(FALSE);
			mCheck_LL2.EnableWindow(FALSE);
		}

		i_limit = l__md_name.GetSize();

		for(i=0; i<i_limit; i++)
		{
			CString md_name = l__md_name[i];

			int pm_id = MACRO__Get_PMx_ID(md_name);
			if(pm_id == 1)		mCheck_PM1.EnableWindow(TRUE);
			if(pm_id == 2)		mCheck_PM2.EnableWindow(TRUE);
			if(pm_id == 3)		mCheck_PM3.EnableWindow(TRUE);
			if(pm_id == 4)		mCheck_PM4.EnableWindow(TRUE);
			if(pm_id == 5)		mCheck_PM5.EnableWindow(TRUE);
			if(pm_id == 6)		mCheck_PM6.EnableWindow(TRUE);
			
			int ll_id = MACRO__Get_LLx_ID(md_name);
			if(ll_id == 1)		mCheck_LL1.EnableWindow(TRUE);
			if(ll_id == 2)		mCheck_LL2.EnableWindow(TRUE);
		}

		if(i_limit > 0)			mBtn__SAVE_ALL_CSV.EnableWindow(TRUE);
		else					mBtn__SAVE_ALL_CSV.EnableWindow(FALSE);
	}
}
int  CDlg__Lot_Recipe_Log
::_Get__MDx_ID_Of_Slot_List(const CString& md_name)
{
	int pm_id = MACRO__Get_PMx_ID(md_name);
	if(pm_id > 0)		return (_TBL_COL__PM1 + (pm_id - 1));

	int ll_id = MACRO__Get_LLx_ID(md_name);
	if(ll_id > 0)		return (_TBL_COL__LL1 + (ll_id - 1));
	
	return -1;
}

CString CDlg__Lot_Recipe_Log
::_Get__ID_Of_Slot_List(const int r_index)
{
	return mList__Slot_Info.GetItemText(r_index, _TBL_COL__SLOTID);
}
