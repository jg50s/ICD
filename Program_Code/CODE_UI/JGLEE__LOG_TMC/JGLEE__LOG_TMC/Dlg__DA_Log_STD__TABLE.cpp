#include "stdafx.h"
#include "JGLEE__LOG_TMC.h"

#include "CObj__DA_Log_STD.h"
#include "Macro_Function.h"


// ...
#define _TBL_TYPE__DIR							1
#define _TBL_TYPE__LOTID						2

#define _TBL_COL__DIR_NUMBER					0
#define _TBL_COL__DIR_NAME						1
#define _TBL_COL__DIR_DATE						2

#define _TBL_COL__LOTID_NUMBER					0
#define _TBL_COL__LOTID_PORTID					1
#define _TBL_COL__LOTID_NAME					2
#define _TBL_COL__LOTID_HEADER					3


void CDlg__DA_Log_STD
::_Make__Table_Dir_List(CListCtrl *p_table)
{
	_Make__Table_List(p_table, _TBL_TYPE__DIR);
}
void CDlg__DA_Log_STD
::_Make__Table_LotID_List(CListCtrl *p_table)
{
	_Make__Table_List(p_table, _TBL_TYPE__LOTID);
}

void CDlg__DA_Log_STD
::_Make__Table_List(CListCtrl *p_table, 
					const int tbl_type)
{
	CStringArray l__col_name;
	CUIntArray   l__col_width;

	// ...
	{
		l__col_name.RemoveAll();
		l__col_width.RemoveAll();

		int i_limit = 10;
		int i;

		if(tbl_type == _TBL_TYPE__DIR)
		{
			for(i=0; i<i_limit; i++)
			{
				if(i == _TBL_COL__DIR_NUMBER)
				{
					l__col_name.Add("No.");
					l__col_width.Add(50);
				}
				else if(i == _TBL_COL__DIR_NAME)
				{
					l__col_name.Add("Directory");
					l__col_width.Add(160);
				}
				else if(i == _TBL_COL__DIR_DATE)
				{
					l__col_name.Add("Date");
					l__col_width.Add(120);
				}
				else
				{
					break;
				}
			}
		}
		else if(tbl_type == _TBL_TYPE__LOTID)
		{
			for(i=0; i<i_limit; i++)
			{
				if(i == _TBL_COL__LOTID_NUMBER)
				{
					l__col_name.Add("No.");
					l__col_width.Add(50);
				}
				else if(i == _TBL_COL__LOTID_PORTID)
				{
					l__col_name.Add("PortID");
					l__col_width.Add(80);
				}
				else if(i == _TBL_COL__LOTID_NAME)
				{
					l__col_name.Add("LotID");
					l__col_width.Add(200);
				}
				else if(i == _TBL_COL__LOTID_HEADER)
				{
					l__col_name.Add("Log.Type");
					l__col_width.Add(120);
				}
				else
				{
					break;
				}
			}
		}
	}

	// ...
	{
		p_table->DeleteAllItems();

		for(int i=0; i<10; i++)
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
void CDlg__DA_Log_STD
::_Add__Table_List(CListCtrl *p_table, 
				   const int col_size,
				   const CStringArray& l_data1,
				   const CStringArray& l_data2,
				   const CStringArray& l_data3)
{
	p_table->DeleteAllItems();

	// ...
	CString str_item;

	int i_limit = l_data1.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		int k_limit = col_size;
		int k;

		for(k=0; k<k_limit; k++)
		{
				 if(k == 0)			str_item.Format("%1d", i+1);
			else if(k == 1)			str_item = l_data1[i];
			else if(k == 2)			str_item = l_data2[i];
			else if(k == 3)			str_item = l_data3[i];
			else					break;

			if(k == 0)		p_table->InsertItem(i, str_item, 0);
			else			p_table->SetItem(i,k, LVIF_TEXT,str_item,0,0,0,0);
		}
	}
}

void CDlg__DA_Log_STD
::_Fnc__Log_View(const int db_index)
{
	CString dir_name  = "";
	CString file_name = "";
	CString file_portid = "?";

	// Log_Date ...
	{
		CListCtrl* p_table = &mCtrl__Log_Date;

		int r_index = p_table->GetSelectionMark();
		if(r_index >= 0)
		{
			int c_index = 1;

			dir_name = p_table->GetItemText(r_index,c_index);
		}
	}
	// Log_File ...
	{
		CListCtrl* p_table = &mCtrl__Log_File;

		int r_index = db_index;
		if(r_index < 0)		r_index = p_table->GetSelectionMark();

		if(r_index >= 0)
		{
			CString str_portid = p_table->GetItemText(r_index, _TBL_COL__LOTID_PORTID);
			CString str_lotid  = p_table->GetItemText(r_index, _TBL_COL__LOTID_NAME);
			CString str_header = p_table->GetItemText(r_index, _TBL_COL__LOTID_HEADER);

			file_name.Format("%s+%s+%s", str_header, str_portid,str_lotid);
			file_portid = str_portid;
		}
	}

	if((dir_name.GetLength()  > 0)
	&& (file_name.GetLength() > 0))
	{
		CString file_path;
		file_path.Format("%s\\%s\\%s.log", sDir_Root,dir_name,file_name);

		_Upload__DA_File(file_path, file_portid);

		printf(" * file_path <- [%s] \n", file_path);
		printf(" * file_portid <- [%s] \n", file_portid);
		printf("\n");
	}
}
