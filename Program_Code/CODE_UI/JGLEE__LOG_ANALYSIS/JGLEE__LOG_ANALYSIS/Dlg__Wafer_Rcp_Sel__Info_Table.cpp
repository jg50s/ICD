#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Wafer_Rcp_Sel.h"
#include "Macro_Function.h"



// ...
#define _CFG__TBL_COL_SIZE						2
#define _TBL_COL__MAIN_ITEM						0
#define _TBL_COL__SUB_ITEM						1

// ...
void CDlg__Wafer_Rcp_Sel::
_Clear__INFO_List()
{
	CListCtrl *p_table = &mList__RCP_INFO;

	p_table->DeleteAllItems();

	int i_limit = iRCP_INFO__Column_Size;
	for(int i=0; i<i_limit; i++)
	{
		p_table->DeleteColumn(_CFG__TBL_COL_SIZE);
	}

	iRCP_INFO__Column_Size = 0;
}

void CDlg__Wafer_Rcp_Sel::
_Make__INFO_List()
{
	CListCtrl *p_table = &mList__RCP_INFO;

	// ...
	CStringArray l__col_name;
	CUIntArray   l__col_width;

	// ...
	{
		int i_limit = _CFG__TBL_COL_SIZE + iRCP_INFO__Column_Size;

		for(int i=0; i<i_limit; i++)
		{
			p_table->DeleteColumn(0);
		}
	}

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
		int st_limit = mRcp_Info.Get__Step_Size();
		iRCP_INFO__Column_Size = st_limit;

		for(int i=0; i<st_limit; i++)
		{
			CStep_Info *p_step = mRcp_Info.Get__Step_Info(i);

			CString col_name;
			col_name.Format("Step_%02d", p_step->iStep_ID);

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

void CDlg__Wafer_Rcp_Sel::
_Add__INFO_List()
{
	CListCtrl* p_table = &mList__RCP_INFO;
	p_table->DeleteAllItems();
	p_table->SetRedraw(FALSE);

	// ...
	CString str_item;
	int col;

	int i_limit = mPara_Info.sList__Para_Channel.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString ch_name      = mPara_Info.sList__Para_Channel[i];
		CString str_title    = mPara_Info.sList__Para_Title[i];
		CString str_category = mPara_Info.sList__Para_Category[i];
		CString ch_title     = mPara_Info.sList__Para_Ch_Title[i];

		//
		CString str_main;
		CString str_sub;

		if(str_category.GetLength() > 0)
		{
			if(ch_name.GetLength() > 0)			str_sub  = str_title;
			else								str_main = str_category;

			if((str_main == "") && (str_sub == ""))
			{
				str_sub = ch_title;
			}
		}
		else
		{
			str_main = str_title;
		}

		// 
		// col = _TBL_COL__MAIN_ITEM;
		str_item = str_main;
		p_table->InsertItem(i, str_item, 0);

		//
		col = _TBL_COL__SUB_ITEM;
		str_item = str_sub;
		p_table->SetItem(i,col, LVIF_TEXT,str_item,0,0,0,0);
	}

	//
	int st_limit = mRcp_Info.Get__Step_Size();
	int st_i;

	for(st_i=0; st_i<st_limit; st_i++)
	{
		CStep_Info *p_step = mRcp_Info.Get__Step_Info(st_i);

		//
		i_limit = mPara_Info.sList__Para_Channel.GetSize();

		for(i=0; i<i_limit; i++)
		{
			CString ch_name = mPara_Info.sList__Para_Channel[i];
			CString ch_data = "";
		
			if(ch_name.GetLength() < 1)			continue;

			//
			int k_limit = p_step->sList__Channe_Name.GetSize();
			
			for(int k=0; k<k_limit; k++)
			{
				if(ch_name.CompareNoCase(p_step->sList__Channe_Name[k]) != 0)
					continue;
				
				col = _CFG__TBL_COL_SIZE + st_i;
				str_item = p_step->sList__Channe_Data[k];
				p_table->SetItem(i,col, LVIF_TEXT,str_item,0,0,0,0);
				break;
			}
		}
	}

	p_table->SetRedraw(TRUE);
}

