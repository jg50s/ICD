#include "stdafx.h"
#include "JGLEE__RECIPE_STD.h"

#include "Dlg__Summary_Report.h"
#include "Macro_Function.h"


// ...
#define _CFG__TBL_COL_SIZE						2
#define _TBL_COL__MAIN_ITEM						0
#define _TBL_COL__SUB_ITEM						1


void CDlg__Summary_Report::
_Make__INFO_List()
{
	CListCtrl *p_table = &mCtrl__Report_List;

	// ...
	CStringArray l__col_name;
	CUIntArray   l__col_width;

	// ...
	{
		int i_limit = _CFG__TBL_COL_SIZE;

		for(int i=0; i<i_limit; i++)
		{
			if(i == _TBL_COL__MAIN_ITEM)
			{
				l__col_name.Add("Main-Item");
				l__col_width.Add(120);
			}
			else if(i == _TBL_COL__SUB_ITEM)
			{
				l__col_name.Add("Sub-Item");
				l__col_width.Add(180);
			}
		}
	}
	// ...
	{
		int i_limit = pAddr__Rcp_File->Get__Step_Size();
	
		for(int i=0; i<i_limit; i++)
		{
			CString col_name;
			col_name.Format("Step_%02d", i+1);

			l__col_name.Add(col_name);
			l__col_width.Add(120);
		}
	}

	// ...
	{
		int limit = l__col_name.GetSize();

		for(int i=0; i<limit; i++)
		{
			CString col_name = l__col_name[i];
			int col_cx = (int) l__col_width[i];

			p_table->InsertColumn(i, col_name, LVCFMT_CENTER, col_cx);
		}		
	}
}

void CDlg__Summary_Report::
_Add__INFO_List()
{
	CListCtrl* p_table = &mCtrl__Report_List;

	p_table->DeleteAllItems();
	p_table->SetRedraw(FALSE);

	// ...
	CString sub_para__main_title = pAddr__Rcp_Item->Get__TITLE_OF_SUB_PARA();

	CStringArray l__sub_title;
	CStringArray l__sub_data;

	pI_Rcp_Interlock_Ctrl->Get__SUMMARY_INFO(iMODULE_ID,1, l__sub_title,l__sub_data);

	// ...
	CStringArray l__ch_name;

	int item_count = 0;

	int i_limit = iList__Item_ID.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		int db_index = iList__Item_ID[i];

		CDS__Rcp_Item m_item;
		if(pAddr__Rcp_Item->Get__ITEM_INFO(db_index, &m_item) < 0)
		{
			continue;
		}

		// ...
		CString ch_title = m_item.sPara__RCP_TITLE;
		
		CString ch_name  = m_item.sPara__CH_NAME;
		l__ch_name.Add(ch_name);

		//
		CString str_main;
		CString str_sub;

		if(m_item.bPara__CATEGORY_ACTIVE)
		{
			str_main = m_item.sPara__CATEGORY_NAME;
		}
		else if(m_item.bPara__CHILD_ACTIVE)
		{
			str_main = m_item.sPara__CATEGORY_NAME;
			str_sub  = ch_title;
		}
		else
		{
			str_main = ch_title;
		}

		// 
		p_table->InsertItem(i, str_main, 0);

		int col = _TBL_COL__SUB_ITEM;
		p_table->SetItem(i,col, LVIF_TEXT,str_sub,0,0,0,0);

		item_count++;
	}

	//
	i_limit = l__sub_title.GetSize();

	if(i_limit > 0)
	{
		for(i=0; i<i_limit; i++)
		{
			CString str_main = sub_para__main_title;
			CString str_sub  = l__sub_title[i];

			// 
			p_table->InsertItem(item_count + i, str_main, 0);

			int col = _TBL_COL__SUB_ITEM;
			p_table->SetItem(item_count + i,col, LVIF_TEXT,str_sub,0,0,0,0);
		}
	}
	else
	{
		CString str_main = sub_para__main_title;
		CString str_sub  = "???";

		// 
		p_table->InsertItem(item_count, str_main, 0);

		int col = _TBL_COL__SUB_ITEM;
		p_table->SetItem(item_count,col, LVIF_TEXT,str_sub,0,0,0,0);
	}

	// ...
	int st_limit = pAddr__Rcp_File->Get__Step_Size();
	int st_i;

	for(st_i=0; st_i<st_limit; st_i++)
	{
		i_limit = l__ch_name.GetSize();

		for(i=0; i<i_limit; i++)
		{
			CString ch_name = l__ch_name[i];
			CString ch_data = pAddr__Rcp_File->Get__Step_Data(st_i+1, ch_name);

			int col = _CFG__TBL_COL_SIZE + st_i;
			p_table->SetItem(i,col, LVIF_TEXT,ch_data,0,0,0,0);
		}
	}

	//
	for(st_i=0; st_i<st_limit; st_i++)
	{
		CStringArray l__sub_data;
		pI_Rcp_Interlock_Ctrl->Get__SUMMARY_INFO(iMODULE_ID, st_i+1, l__sub_title,l__sub_data);

		//
		i_limit = l__sub_data.GetSize();

		for(i=0; i<i_limit; i++)
		{
			CString ch_data = l__sub_data[i];

			int col = _CFG__TBL_COL_SIZE + st_i;
			p_table->SetItem(item_count+i,col, LVIF_TEXT,ch_data,0,0,0,0);
		}
	}

	// ...
	p_table->SetRedraw(TRUE);
}
