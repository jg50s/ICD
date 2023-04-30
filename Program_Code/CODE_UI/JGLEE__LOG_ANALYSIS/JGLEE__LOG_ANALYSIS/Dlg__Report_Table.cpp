// Dlg__Report_Table.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Report_Table.h"
#include "CObj__Report_Table__KEY_DEF.h"


// CDlg__Report_Table dialog

IMPLEMENT_DYNAMIC(CDlg__Report_Table, CDialog)

CDlg__Report_Table::CDlg__Report_Table(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Report_Table::IDD, pParent)
{
	bActive__Init_Table = false;
}

CDlg__Report_Table::~CDlg__Report_Table()
{
}

void CDlg__Report_Table::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST__REPORT_TABLE, mList__Report_Table);
}


BEGIN_MESSAGE_MAP(CDlg__Report_Table, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlg__Report_Table message handlers

BOOL CDlg__Report_Table::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		CListCtrl* p_table = &mList__Report_Table;
		CImageList* p_img  = &mImg__Report_Table;

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

		_Make__Report_Table(p_table);
	}

	if(iREAL_MODE > 0)
	{
		SetTimer(1, 500, NULL);
	}
	else
	{
		CListCtrl* p_table = &mList__Report_Table;

		CStringArray l_data;
		CString str_msg;
		
		int i_limit = iData__Table_Row_Max;
		int i;

		for(i=0; i<i_limit; i++)
		{
			str_msg.Format("Message (%2d) ... ", i+1);
			l_data.Add(str_msg);
		}

		_Add__Report_Table(p_table, l_data);
	}

	bActive__Init_Table = true;
	return TRUE;
}

void CDlg__Report_Table::OnTimer(UINT_PTR nIDEvent)
{
	// ...
	{
		CListCtrl *p_table = &mList__Report_Table;
		CStringArray l_data;

		CString ch_name;
		CString ch_data;

		int i_limit = iData__Table_Row_Max;
		int i;

		for(i=0; i<i_limit; i++)
		{
			ch_name.Format("%s%02d", pKEY__CH_MSG_X,i+1);
			ch_data = "";
			pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(ch_name, ch_data);

			l_data.Add(ch_data);
		}

		_Add__Report_Table(p_table, l_data);
	}

	CDialog::OnTimer(nIDEvent);
}
