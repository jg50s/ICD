#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Wafer_MDx_Sel.h"
#include "Macro_Function.h"

#include "CLS__Proc_Log.h"


// ...
#define _CFG__TBL_COL_SIZE						4
#define _TBL_COL__NUMBER						0
#define _TBL_COL__NAME							1
#define _TBL_COL__LOG_TYPE						2
#define _TBL_COL__CHANNEL						3

// ...
void CDlg__Wafer_MDx_Sel::
_Make__Template_List(CListCtrl *p_table)
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
				l__col_width.Add(200);
			}
			else if(i == _TBL_COL__LOG_TYPE)
			{
				l__col_name.Add("Type");
				l__col_width.Add(100);
			}
			else if(i == _TBL_COL__CHANNEL)
			{
				l__col_name.Add("Channel");
				l__col_width.Add(200);
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
_Add__Template_List(const CString& str_mdx, const CString& str_template)
{
	CListCtrl* p_table = &mList__MDx_Template;
	p_table->DeleteAllItems();
	p_table->SetRedraw(FALSE);

	// ...
	CStringArray l__event_name;
	CStringArray l__event_channel;

	CStringArray l__interval_name;
	CStringArray l__interval_channel;

	// ...
	{
		int eqp_id = -1;

		int pm_id = MACRO__Get_PMx_ID(str_mdx);
		if(pm_id > 0)		eqp_id = pm_id + 1;

		int ll_id = MACRO__Get_LLx_ID(str_mdx);
		if(ll_id > 0)		eqp_id = 1;

		// ...
		CGX__SYSTEM_CTRL x_sys_ctrl;
		CString dir_log;

		x_sys_ctrl->Get__SEQ_DIR_ROOT(eqp_id, dir_log);
		dir_log += "\\EQP_LOG\\Datalog";

		CString file_path;
		file_path.Format("%s\\%s", dir_log,str_template);

		// ...
		CLS__Proc_Log x_log;
		x_log.Update__Template_File(m_hWnd, file_path);

		x_log.Get__Template_Event(l__event_name, l__event_channel);
		x_log.Get__Template_Interrval(l__interval_name, l__interval_channel);
	}

	// ...
	int r_count = 0;

	// Event Table ...
	{
		CString log_type = "EVENT";

		CString str_item;
		int col;

		int i_limit = l__event_name.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			// NO.
			str_item.Format("%1d", r_count+1);
			p_table->InsertItem(r_count, str_item, 0);

			//
			col = _TBL_COL__NAME;
			str_item = l__event_name[i];
			p_table->SetItem(r_count,col, LVIF_TEXT,str_item,0,0,0,0);

			col = _TBL_COL__LOG_TYPE;
			str_item = log_type;
			p_table->SetItem(r_count,col, LVIF_TEXT,str_item,0,0,0,0);

			col = _TBL_COL__CHANNEL;
			str_item = l__event_channel[i];
			p_table->SetItem(r_count,col, LVIF_TEXT,str_item,0,0,0,0);

			r_count++;
		}
	}
	// Interval Table ...
	{
		CString log_type = "INTERVAL";

		CString str_item;
		int col;

		int i_limit = l__interval_name.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			// NO.
			str_item.Format("%1d", r_count+1);
			p_table->InsertItem(r_count, str_item, 0);

			//
			col = _TBL_COL__NAME;
			str_item = l__interval_name[i];
			p_table->SetItem(r_count,col, LVIF_TEXT,str_item,0,0,0,0);

			col = _TBL_COL__LOG_TYPE;
			str_item = log_type;
			p_table->SetItem(r_count,col, LVIF_TEXT,str_item,0,0,0,0);

			col = _TBL_COL__CHANNEL;
			str_item = l__interval_channel[i];
			p_table->SetItem(r_count,col, LVIF_TEXT,str_item,0,0,0,0);

			r_count++;
		}
	}

	p_table->SetRedraw(TRUE);
}

