// Dlg__MDx_Info.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_CTC.h"
#include "Dlg__MDx_Info.h"


// CDlg__MDx_Info dialog

IMPLEMENT_DYNAMIC(CDlg__MDx_Info, CDialog)

CDlg__MDx_Info::CDlg__MDx_Info(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__MDx_Info::IDD, pParent)
{

}

CDlg__MDx_Info::~CDlg__MDx_Info()
{
}

void CDlg__MDx_Info::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST__REF_FILE, mCtrl__Info_Table);
}


BEGIN_MESSAGE_MAP(CDlg__MDx_Info, CDialog)
	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()


// CDlg__MDx_Info message handlers

void CDlg__MDx_Info::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if(nIDCtl == IDC_LIST__REF_FILE)
	{
		lpMeasureItemStruct->itemHeight = 21;
	}

	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

BOOL CDlg__MDx_Info::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Info Table ...
	{
		CListCtrl* p_table = &mCtrl__Info_Table;

		// ...
		{
			int list_view_stype;

			list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
			list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
			list_view_stype += LVS_EX_INFOTIP;
			// list_view_stype += LVS_EX_DOUBLEBUFFER;

			p_table->SetExtendedStyle(list_view_stype);
			p_table->ModifyStyle(LVS_OWNERDRAWFIXED, 0, 0);
		}

		Make__Info_List(p_table);
		Add__Info_List(p_table, sList__MDx_Info);
	}

	return TRUE;  
}


// ...
#define _FILE_COL__NUMBER					0
#define _FILE_COL__INFO						1


void CDlg__MDx_Info::Make__Info_List(CListCtrl *p_table)
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
			else if(i == _FILE_COL__INFO)
			{
				l__col_name.Add("Info");
				l__col_width.Add(670);
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
void CDlg__MDx_Info::Add__Info_List(CListCtrl *p_table, 
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
			else if(k == _FILE_COL__INFO)		str_item = l_cfg_name[i];
			else								break;

			if(k == 0)		p_table->InsertItem(i, str_item, 0);
			else			p_table->SetItem(i,k, LVIF_TEXT,str_item,0,0,0,0);
		}
	}
}
