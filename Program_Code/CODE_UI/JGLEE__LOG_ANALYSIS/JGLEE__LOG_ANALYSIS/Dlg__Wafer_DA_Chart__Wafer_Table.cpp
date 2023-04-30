#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Wafer_DA_Chart.h"
#include "Macro_Function.h"


// ...
#define _CFG__TBL_COL_SIZE						5
#define _TBL_COL__NUMBER						0
#define _TBL_COL__SLOTID						1
#define _TBL_COL__MODULE						2
#define _TBL_COL__R_OFFSET						3
#define _TBL_COL__T_OFFSET						4


void CDlg__Wafer_DA_Chart
::_Make__Wafer_List(CListCtrl *p_table,
					CImageList *p_img)
{
	// ...
	{
		CBitmap cBit;
		cBit.LoadBitmap(IDB_DIGITAL_LIST_IMG);

		p_img->Create(1,20, ILC_COLOR4,1,1);
		p_img->Add(&cBit, RGB(0,0,0));	

		p_table->SetImageList(p_img, LVSIL_SMALL);

		// ...
		int list_view_stype;

		list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
		list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
		list_view_stype += LVS_EX_INFOTIP;

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
				l__col_name.Add("No.");
				l__col_width.Add(50);
			}
			else if(i == _TBL_COL__SLOTID)
			{
				l__col_name.Add("Slot");
				l__col_width.Add(80);
			}
			else if(i == _TBL_COL__MODULE)
			{
				l__col_name.Add("Module");
				l__col_width.Add(100);
			}
			else if(i == _TBL_COL__R_OFFSET)
			{
				l__col_name.Add("R (mm)");
				l__col_width.Add(120);
			}
			else if(i == _TBL_COL__T_OFFSET)
			{
				l__col_name.Add("T (deg)");
				l__col_width.Add(120);
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

void CDlg__Wafer_DA_Chart::
_Clear__Wafer_List()
{
	CListCtrl *p_table = &mCtrl__Wafer_Info;
	p_table->DeleteAllItems();
}
void CDlg__Wafer_DA_Chart::
_Add__Wafer_List(const CString& str_slotid,
			     const CStringArray& l_module,
				 const CStringArray& l_r_offset,
				 const CStringArray& l_t_offset)
{
	CListCtrl *p_table = &mCtrl__Wafer_Info;

	p_table->SetRedraw(FALSE);

	// ...
	int i_offset = p_table->GetItemCount();
	int r_count = 0;

	// ...
	int active__only_alarm = mCheck__Only_Alarm.GetCheck();
	double ref__err_range = 0.0;

	if(mCheck__Error_Range.GetCheck() > 0)
	{
		ref__err_range = atof(mStr__Error_Range);
	}
	else
	{
		active__only_alarm = -1;
	}

	// ...
	CString str_item;

	int i_limit = l_module.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_mdx = l_module[i];

		// PMx Check ...
		{
			int pm_id = MACRO__Get_PMx_ID(str_mdx);
			
			if(pm_id == 1)
			{
				if(mCheck_PM1.GetCheck() < 1)		continue;
			}
			else if(pm_id == 2)
			{
				if(mCheck_PM2.GetCheck() < 1)		continue;
			}
			else if(pm_id == 3)
			{
				if(mCheck_PM3.GetCheck() < 1)		continue;
			}
			else if(pm_id == 4)
			{
				if(mCheck_PM4.GetCheck() < 1)		continue;
			}
			else if(pm_id == 5)
			{
				if(mCheck_PM5.GetCheck() < 1)		continue;
			}
			else if(pm_id == 6)
			{
				if(mCheck_PM6.GetCheck() < 1)		continue;
			}
		}
		// LLx Check ...
		{
			int ll_id = MACRO__Get_LLx_ID(str_mdx);

			if(ll_id == 1)
			{
				if(mCheck_LL1.GetCheck() < 1)		continue;
			}
			else if(ll_id == 2)
			{
				if(mCheck_LL2.GetCheck() < 1)		continue;
			}
			else if(ll_id == 3)
			{
				if(mCheck_LL3.GetCheck() < 1)		continue;
			}
			else if(ll_id == 4)
			{
				if(mCheck_LL4.GetCheck() < 1)		continue;
			}
		}

		// ...
		CString str__r_off_mm  = l_r_offset[i];
		CString str__t_off_deg = l_t_offset[i];

		if(active__only_alarm > 0)
		{
			ref__err_range = atof(mStr__Error_Range);

			double cur__r_off_mm = atof(str__r_off_mm);
			if(cur__r_off_mm < 0)		cur__r_off_mm = -cur__r_off_mm;

			if(cur__r_off_mm < ref__err_range)		continue;
		}

		// ...
		int k_limit = _CFG__TBL_COL_SIZE;
		int k;

		for(k=0; k<k_limit; k++)
		{
				 if(k == _TBL_COL__NUMBER)			str_item.Format("%1d", r_count + 1 + i_offset);
			else if(k == _TBL_COL__SLOTID)			str_item = str_slotid;
			else if(k == _TBL_COL__MODULE)			str_item = str_mdx;
			else if(k == _TBL_COL__R_OFFSET)		str_item = str__r_off_mm;
			else if(k == _TBL_COL__T_OFFSET)		str_item = str__t_off_deg;
			else									break;

			if(k == 0)		p_table->InsertItem(r_count+i_offset, str_item, 0);
			else			p_table->SetItem(r_count+i_offset,k, LVIF_TEXT,str_item,0,0,0,0);
		}

		r_count++;
	}

	p_table->SetRedraw(TRUE);
}

void CDlg__Wafer_DA_Chart::
_Get__RT_Offset_Of_Wafer_List(CStringArray& l_r_offset,
							  CStringArray& l_t_offset)
{
	CListCtrl *p_table = &mCtrl__Wafer_Info;

	l_r_offset.RemoveAll();
	l_t_offset.RemoveAll();

	// ...
	CString str_item;
	int col;

	int i_limit =  p_table->GetItemCount();
	int i;

	for(i=0; i<i_limit; i++)
	{
		col = _TBL_COL__R_OFFSET;
		str_item = p_table->GetItemText(i,col);
		l_r_offset.Add(str_item);
		
		col = _TBL_COL__T_OFFSET;
		str_item = p_table->GetItemText(i,col);
		l_t_offset.Add(str_item);
	}
}
