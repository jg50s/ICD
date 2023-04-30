#include "stdafx.h"
#include "Dlg__Compare_CFG.h"


// ...
#define _FILE_COL__NUMBER					0
#define _FILE_COL__FILE						1


void CDlg__Compare_CFG
::Make__File_List(CListCtrl *p_table)
{
	CStringArray l__col_name;
	CUIntArray   l__col_width;

	// ...
	{
		l__col_name.RemoveAll();
		l__col_width.RemoveAll();

		int i_limit = 10;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == _FILE_COL__NUMBER)
			{
				l__col_name.Add("No.");
				l__col_width.Add(50);
			}
			else if(i == _FILE_COL__FILE)
			{
				l__col_name.Add("Config Page");
				l__col_width.Add(250);
			}
			else
			{
				break;
			}
		}
	}

	// ...
	{
		int i;

		p_table->DeleteAllItems();

		for(i=0; i<10; i++)
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
void CDlg__Compare_CFG
::Add__File_List(CListCtrl *p_table, 
				 const CStringArray& l_cfg_name)
{
	p_table->DeleteAllItems();

	// ...
	CString str_item;

	int i_limit = l_cfg_name.GetSize();
	for(int i=0; i<i_limit; i++)
	{
		int k_limit = 5;
		int k;

		for(k=0; k<k_limit; k++)
		{
			     if(k == _FILE_COL__NUMBER)		str_item.Format("%1d", i+1);
			else if(k == _FILE_COL__FILE)		str_item = l_cfg_name[i];
			else								break;

			if(k == 0)		p_table->InsertItem(i, str_item, 0);
			else			p_table->SetItem(i,k, LVIF_TEXT,str_item,0,0,0,0);
		}
	}
}
