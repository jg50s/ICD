// Dlg__Summary_Report.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_STD.h"
#include "Dlg__Summary_Report.h"


// CDlg__Summary_Report dialog

IMPLEMENT_DYNAMIC(CDlg__Summary_Report, CDialog)

CDlg__Summary_Report::CDlg__Summary_Report(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Summary_Report::IDD, pParent)
{

}

CDlg__Summary_Report::~CDlg__Summary_Report()
{
}

void CDlg__Summary_Report::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST__REPORT, mCtrl__Report_List);
}


BEGIN_MESSAGE_MAP(CDlg__Summary_Report, CDialog)
	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()


// CDlg__Summary_Report message handlers

void CDlg__Summary_Report::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if(nIDCtl == IDC_LIST__REPORT)
	{
		lpMeasureItemStruct->itemHeight = 25;
	}

	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

BOOL CDlg__Summary_Report::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		CListCtrl *p_table = &mCtrl__Report_List;

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

		_Make__INFO_List();
		_Add__INFO_List();
	}
	return TRUE;
}
