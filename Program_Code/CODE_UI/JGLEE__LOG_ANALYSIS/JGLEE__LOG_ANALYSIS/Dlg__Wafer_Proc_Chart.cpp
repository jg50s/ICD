// Dlg__Wafer_Proc_Chart.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__Wafer_Proc_Chart.h"


// CDlg__Wafer_Proc_Chart dialog

IMPLEMENT_DYNAMIC(CDlg__Wafer_Proc_Chart, CDialog)

CDlg__Wafer_Proc_Chart::CDlg__Wafer_Proc_Chart(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Wafer_Proc_Chart::IDD, pParent)
{

}

CDlg__Wafer_Proc_Chart::~CDlg__Wafer_Proc_Chart()
{
}

void CDlg__Wafer_Proc_Chart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST__CHANNEL_TABLE, mList__Channel_Table);
	DDX_Control(pDX, IDC_LIST__CHANNEL_SEL, mList__Channel_Sel);
	DDX_Control(pDX, IDC__WAFER_PROC_CHART, m_ChartViewer);

	DDX_Control(pDX, IDC_BTN__CHART_SINGLE, mBtn__Chart_Single);
	DDX_Control(pDX, IDC_BTN__CHART_MULTI,  mBtn__Chart_Multi);
	DDX_Control(pDX, IDC_BTN__MULTI_ALL,    mBtn__Multi_All);
	DDX_Control(pDX, IDC_BTN__MULTI_CLEAR,  mBtn__Multi_Clear);
}


BEGIN_MESSAGE_MAP(CDlg__Wafer_Proc_Chart, CDialog)
	ON_WM_MEASUREITEM()

	ON_CONTROL(CVN_MouseMovePlotArea, IDC__WAFER_PROC_CHART, OnMouseMovePlotArea)

	ON_NOTIFY(NM_CLICK, IDC_LIST__CHANNEL_TABLE, &CDlg__Wafer_Proc_Chart::OnNMClickList__Channel_Table)
	ON_NOTIFY(NM_CLICK, IDC_LIST__CHANNEL_SEL, &CDlg__Wafer_Proc_Chart::OnNMClickList__Channel_Sel)

	ON_BN_CLICKED(IDC_BTN__CHART_SINGLE, &CDlg__Wafer_Proc_Chart::OnBnClickedBtn__Chart_Single)
	ON_BN_CLICKED(IDC_BTN__CHART_MULTI,  &CDlg__Wafer_Proc_Chart::OnBnClickedBtn__Chart_Multi)
	ON_BN_CLICKED(IDC_BTN__MULTI_ALL,    &CDlg__Wafer_Proc_Chart::OnBnClickedBtn__Multi_All)
	ON_BN_CLICKED(IDC_BTN__MULTI_CLEAR,  &CDlg__Wafer_Proc_Chart::OnBnClickedBtn__Multi_Clear)

END_MESSAGE_MAP()


// CDlg__Wafer_Proc_Chart message handlers

void CDlg__Wafer_Proc_Chart::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if(nIDCtl == IDC_LIST__CHANNEL_TABLE)
	{
		lpMeasureItemStruct->itemHeight = 21;
	}

	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

BOOL CDlg__Wafer_Proc_Chart::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Channel Table ...
	{
		CReportCtrl* p_table = &mList__Channel_Table;
		p_table->SetNoSort(false);

		// ...
		{
			int list_view_stype;

			list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
			list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
			list_view_stype += LVS_EX_INFOTIP;

			p_table->SetExtendedStyle(list_view_stype);
			p_table->ModifyStyle(LVS_OWNERDRAWFIXED, 0, 0);
		}

		_Make__Channel_List(p_table);
		_Add__Channel_List();
	}

	// ...
	{
		sPara__X_Axis_Title = "sec";
		sPara__Y_Axis_Title = "value";

		_Init__Proc_Chart();
	}

	// Channel Sel ...
	{
		CReportCtrl* p_table = &mList__Channel_Sel;
		p_table->SetNoSort(false);

		// ...
		{
			int list_view_stype;

			list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
			list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
			list_view_stype += LVS_EX_INFOTIP;
			list_view_stype += LVS_EX_CHECKBOXES;

			p_table->SetExtendedStyle(list_view_stype);
		}

		_Make__Channel_Sel(p_table);
		_Add__Channel_Sel();
	}

	// ...
	{
		_Fnc__Multi_All();
		OnBnClickedBtn__Chart_Multi();
	}

	return TRUE; 
}

void CDlg__Wafer_Proc_Chart::OnNMClickList__Channel_Table(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int r_index = pNMItemActivate->iItem;
	if(r_index >= 0)
	{
		_Make__Proc_Chart();
	}

	*pResult = 0;
}
void CDlg__Wafer_Proc_Chart::OnNMClickList__Channel_Sel(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int r_index = pNMItemActivate->iItem;
	if(r_index >= 0)
	{
		CListCtrl* p_table = &mList__Channel_Sel;

		if(p_table->GetCheck(r_index) > 0)		p_table->SetCheck(r_index, FALSE);
		else									p_table->SetCheck(r_index, TRUE);

		_Make__Proc_Chart();
	}

	*pResult = 0;
}

void CDlg__Wafer_Proc_Chart::OnBnClickedBtn__Chart_Single()
{
	mBtn__Chart_Multi.EnableWindow(TRUE);
	mBtn__Multi_All.EnableWindow(FALSE);
	mBtn__Multi_Clear.EnableWindow(FALSE);
	mBtn__Chart_Single.EnableWindow(FALSE);

	bActive__Chart_Single = true;
	mList__Channel_Sel.EnableWindow(FALSE);

	_Make__Proc_Chart();
}
void CDlg__Wafer_Proc_Chart::OnBnClickedBtn__Chart_Multi()
{
	mBtn__Chart_Multi.EnableWindow(FALSE);
	mBtn__Multi_All.EnableWindow(TRUE);
	mBtn__Multi_Clear.EnableWindow(TRUE);
	mBtn__Chart_Single.EnableWindow(TRUE);

	bActive__Chart_Single = false;
	mList__Channel_Sel.EnableWindow(TRUE);

	_Make__Proc_Chart();
}
void CDlg__Wafer_Proc_Chart::OnBnClickedBtn__Multi_All()
{
	_Fnc__Multi_All();

	_Make__Proc_Chart();
}
void CDlg__Wafer_Proc_Chart::_Fnc__Multi_All()
{
	CListCtrl* p_table = &mList__Channel_Sel;

	int i_limit = p_table->GetItemCount();
	for(int i=0; i<i_limit; i++)
	{
		p_table->SetCheck(i, 1);
	}
}
void CDlg__Wafer_Proc_Chart::OnBnClickedBtn__Multi_Clear()
{
	// ...
	{
		CListCtrl* p_table = &mList__Channel_Sel;

		int i_limit = p_table->GetItemCount();
		for(int i=0; i<i_limit; i++)
		{
			p_table->SetCheck(i, 0);
		}
	}

	_Make__Proc_Chart();
}


