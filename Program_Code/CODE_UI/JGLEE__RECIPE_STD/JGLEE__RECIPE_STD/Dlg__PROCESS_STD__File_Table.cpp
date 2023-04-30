#include "stdafx.h"
#include "JGLEE__RECIPE_STD.h"

#include "Dlg__PROCESS_STD.h"
#include "Macro_Function.h"


// ...
#define _CFG__FILE_COL_SIZE						3
#define _FILE_COL__NUMBER						0
#define _FILE_COL__NAME	    					1
#define _FILE_COL__DATE	    					2


void CDlg__PROCESS_STD
::_Make__File_Table(CReportCtrl *p_table)
{
	CStringArray l__col_name;
	CUIntArray   l__col_width;

	// ...
	{
		l__col_name.RemoveAll();
		l__col_width.RemoveAll();

		int i_limit = _CFG__FILE_COL_SIZE;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == _FILE_COL__NUMBER)
			{
				l__col_name.Add("No.");
				l__col_width.Add(35);
			}
			else if(i == _FILE_COL__NAME)
			{
				l__col_name.Add("Name");
				l__col_width.Add(200);
			}
			else if(i == _FILE_COL__DATE)
			{
				l__col_name.Add("Date");
				l__col_width.Add(120);
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

		for(int i=0; i<_CFG__FILE_COL_SIZE; i++)
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

void CDlg__PROCESS_STD::
_Add__File_Table(CReportCtrl *p_table, 
				 const CStringArray& l_name,
				 const CStringArray& l_date)
{
	COLORREF t_color = RGB(0,0,0);
	COLORREF b_color = RGB(255,255,255);

	// ...
	p_table->DeleteAllItems();
	p_table->SetRedraw(FALSE);

	// ...
	int i_limit = l_name.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_data;
		int col;

		str_data.Format("%1d", i+1);
		p_table->InsertItem(i, str_data, t_color,b_color);

		//
		col = _FILE_COL__NAME;
		str_data = l_name[i];
		p_table->SetItem(i,col, LVIF_TEXT,str_data,0,0,0,0);

		col = _FILE_COL__DATE;
		str_data = l_date[i];
		p_table->SetItem(i,col, LVIF_TEXT,str_data,0,0,0,0);
	}

	p_table->SetRedraw(TRUE);
}

CString CDlg__PROCESS_STD::_Get__Name_Of_File_Talbe(const int r_index)
{
	return mCtrl__File_Table.GetItemText(r_index, _FILE_COL__NAME);		
}

// ...
int  CDlg__PROCESS_STD::_Upload__File_List(const CString& dir_sub)
{
	sCur__Rcp__Folder = dir_sub;

	// ...
	CString dir_root;
	dir_root.Format("%s\\%s\\", sDir__ROOT_EQP,dir_sub);

	CString file_ext = "rcp";
	CStringArray l_file_name;
	CStringArray l_file_date;

	MACRO__Get_File_List(dir_root,file_ext, l_file_name,l_file_date);
	
	// ...
	CReportCtrl *p_table = &mCtrl__File_Table;
	_Add__File_Table(p_table, l_file_name,l_file_date);

	return l_file_name.GetSize();
}

void CDlg__PROCESS_STD::_Change__Rcp_Folder(const int rcp_folder)
{
	mCheck__Rcp_Pre.SetCheck(0);
	mCheck__Rcp_Main.SetCheck(0);
	mCheck__Rcp_Post.SetCheck(0);
	
	if(rcp_folder == _RCP_FOLDER__PRE)			mCheck__Rcp_Pre.SetCheck(1);
	if(rcp_folder == _RCP_FOLDER__MAIN)			mCheck__Rcp_Main.SetCheck(1);
	if(rcp_folder == _RCP_FOLDER__POST)			mCheck__Rcp_Post.SetCheck(1);
}
int  CDlg__PROCESS_STD::_Get__Rcp_Folder()
{
	if(mCheck__Rcp_Pre.GetCheck()  > 0)			return _RCP_FOLDER__PRE;
	if(mCheck__Rcp_Main.GetCheck() > 0)			return _RCP_FOLDER__MAIN;
	if(mCheck__Rcp_Post.GetCheck() > 0)			return _RCP_FOLDER__POST;

	return -1;
}
CString CDlg__PROCESS_STD::
_Get__Rcp_Folder(const int rcp_folder)
{
	if(rcp_folder == _RCP_FOLDER__PRE)			return sDef__Rcp_Pre_Folder;
	if(rcp_folder == _RCP_FOLDER__POST)			return sDef__Rcp_Post_Folder;

	return sDef__Rcp_Main_Folder;
}
CString CDlg__PROCESS_STD::
_Get__Rcp_Folder(const CString& rcp_folder)
{
	if(rcp_folder.CompareNoCase("PRE")  == 0)	return sDef__Rcp_Pre_Folder;
	if(rcp_folder.CompareNoCase("POST") == 0)	return sDef__Rcp_Post_Folder;

	return sDef__Rcp_Main_Folder;
}
