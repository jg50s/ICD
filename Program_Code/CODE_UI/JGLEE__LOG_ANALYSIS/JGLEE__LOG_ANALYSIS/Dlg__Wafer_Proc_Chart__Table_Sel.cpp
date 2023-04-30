#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Wafer_Proc_Chart.h"
#include "Macro_Function.h"


// ...
#define _CFG__TBL_COL_SIZE						2
#define _TBL_COL__COLOR							0
#define _TBL_COL__ID							1

// ...
void CDlg__Wafer_Proc_Chart::
_Make__Channel_Sel(CListCtrl *p_table)
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
			if(i == _TBL_COL__COLOR)
			{
				l__col_name.Add("Color");
				l__col_width.Add(60);
			}
			else if(i == _TBL_COL__ID)
			{
				l__col_name.Add("No.");
				l__col_width.Add(80);
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
_Add__Channel_Sel()
{
	CReportCtrl *p_table = &mList__Channel_Sel;
	p_table->DeleteAllItems();
	p_table->SetRedraw(FALSE);

	// ...
	CStringArray l_name;
	CStringArray l_channel;
	CStringArray l_log_ccnt;

	pLog_Proc->Get__Template_Interrval(l_name, l_channel, l_log_ccnt);

	// ...
	COLORREF t_color = RGB(0,0,0);

	CString log_type = "INTERVAL";
	CString str_item;
	int col;

	int i_limit = l_name.GetSize();
	int i;

	if(i_limit > _DEF__Y_SIZE)		i_limit = _DEF__Y_SIZE;

	for(i=0; i<i_limit; i++)
	{
		COLORREF b_color = cList__Channel_Color_RGB[i];

		// NO.
		str_item = ".";
		p_table->InsertItem(i, str_item, t_color,b_color);

		//
		col = _TBL_COL__ID;
		str_item.Format("%02d", i+1);
		p_table->SetItem(i,col, LVIF_TEXT,str_item,0,0,0,0);
	}

	p_table->SetRedraw(TRUE);
}

