#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Report_Table.h"

#include "CObj__Report_Table__KEY_DEF.h"


// ...
#define _CFG__TBL_COL_SIZE						2
#define _TBL_COL__NUMBER						0
#define _TBL_COL__MESSAGE    					1


void CDlg__Report_Table
::_Make__Report_Table(CListCtrl *p_table)
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
				l__col_width.Add(iData__Col_Width_Index);
			}
			else if(i == _TBL_COL__MESSAGE)
			{
				l__col_name.Add("Message");
				l__col_width.Add(iData__Col_Width_Msg);
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

			if(col_cx < 1)
			{
				col_cx = 10 + (col_name.GetLength() * 10);
			}

			p_table->InsertColumn(i, col_name, LVCFMT_CENTER, col_cx);
		}		
	}
}

void CDlg__Report_Table
::_Add__Report_Table(CListCtrl *p_table,
					 CStringArray& l_data)
{
	bool active_update = false;

	// ...
	int i_limit = l_data.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString new_data = l_data[i];
		CString cur_data = p_table->GetItemText(i, _TBL_COL__MESSAGE);

		if(cur_data.CompareNoCase(new_data) == 0)
			continue;

		active_update = true;
		break;
	}

	if(!active_update)		return;
	
	// ...
	CString str_item;

	i_limit = l_data.GetSize();

	for(i=0; i<i_limit; i++)
	{
		CString new_data = l_data[i];

		if(i >= p_table->GetItemCount())
		{
			str_item.Format("%02d", i+1);
			p_table->InsertItem(i, str_item, 0);
		}

		p_table->SetItem(i, _TBL_COL__MESSAGE, LVIF_TEXT, new_data, 0,0,0,0);
	}
}

