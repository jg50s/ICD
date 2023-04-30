// Dlg__Wafer_Trace_Sel.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__Wafer_Trace_Sel.h"

#include "Macro_Function.h"


// CDlg__Wafer_Trace_Sel dialog

IMPLEMENT_DYNAMIC(CDlg__Wafer_Trace_Sel, CDialog)

CDlg__Wafer_Trace_Sel::CDlg__Wafer_Trace_Sel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Wafer_Trace_Sel::IDD, pParent)
{

}

CDlg__Wafer_Trace_Sel::~CDlg__Wafer_Trace_Sel()
{
}

void CDlg__Wafer_Trace_Sel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST__WAFER_INFO, mCtrl__Wafer_Info);

	DDX_Control(pDX, IDC_CHECK__LP1, mCheck_LP1);
	DDX_Control(pDX, IDC_CHECK__LP2, mCheck_LP2);
	DDX_Control(pDX, IDC_CHECK__LP3, mCheck_LP3);
	DDX_Control(pDX, IDC_CHECK__LP4, mCheck_LP4);
	DDX_Control(pDX, IDC_CHECK__LP5, mCheck_LP5);

	DDX_Control(pDX, IDC_CHECK__1DAY, mCheck__1_Day_Before);
	DDX_Control(pDX, IDC_CHECK__LOTID, mCheck__LotID);
	DDX_Control(pDX, IDC_LIST__SLOT_INFO, mList__Slot_Info);
	DDX_Control(pDX, IDOK, mBtn_OK);
}


BEGIN_MESSAGE_MAP(CDlg__Wafer_Trace_Sel, CDialog)
	ON_BN_CLICKED(IDOK, &CDlg__Wafer_Trace_Sel::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN__WAFER_REFRESH, &CDlg__Wafer_Trace_Sel::OnBnClickedBtn__Wafer_Refresh)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CDlg__Wafer_Trace_Sel::OnHdnItemclickList)
	ON_NOTIFY(NM_CLICK, IDC_LIST__WAFER_INFO, &CDlg__Wafer_Trace_Sel::OnNMClickList__Wafer_Info)
	ON_LBN_SELCHANGE(IDC_LIST__SLOT_INFO, &CDlg__Wafer_Trace_Sel::OnLbnSelchangeList)
END_MESSAGE_MAP()


// CDlg__Wafer_Trace_Sel message handlers

BOOL CDlg__Wafer_Trace_Sel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		mCheck__1_Day_Before.SetCheck(0);
		mCheck__LotID.SetCheck(1);
	}

	// ...
	{
		mCheck_LP1.EnableWindow(FALSE);
		mCheck_LP2.EnableWindow(FALSE);
		mCheck_LP3.EnableWindow(FALSE);
		mCheck_LP4.EnableWindow(FALSE);
		mCheck_LP5.EnableWindow(FALSE);

		for(int i=0; i<iPara__LPx_SIZE; i++)
		{
			if(i == 0)
			{
				mCheck_LP1.EnableWindow(TRUE);
				mCheck_LP1.SetCheck(1);
			}
			else if(i == 1)
			{
				mCheck_LP2.EnableWindow(TRUE);
				mCheck_LP2.SetCheck(1);
			}
			else if(i == 2)
			{
				mCheck_LP3.EnableWindow(TRUE);
				mCheck_LP3.SetCheck(1);
			}
			else if(i == 3)
			{
				mCheck_LP4.EnableWindow(TRUE);
				mCheck_LP4.SetCheck(1);
			}
			else if(i == 4)
			{
				mCheck_LP5.EnableWindow(TRUE);
				mCheck_LP5.SetCheck(1);
			}
		}
	}

	// ...
	{
		CImageList *p_img = &mImg_List;

		// ...
		{
			CBitmap cBit;
			cBit.LoadBitmap(IDB_DIGITAL_LIST_IMG);

			p_img->Create(1,20, ILC_COLOR4,1,1);
			p_img->Add(&cBit, RGB(0,0,0));	
		}

		CListCtrl* p_table = &mCtrl__Wafer_Info;

		// ...
		{
			p_table->SetImageList(p_img, LVSIL_SMALL);

			// ...
			int list_view_stype;

			list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
			list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
			list_view_stype += LVS_EX_INFOTIP;

			p_table->SetExtendedStyle(list_view_stype);
		}

		_Make__Wafer_List(p_table);
		_Add__Wafer_List(p_table);
	}

	UpdateData(FALSE);
	return TRUE; 
}

void CDlg__Wafer_Trace_Sel::OnBnClickedOk()
{
	_Get__SEL_INFO();

	OnOK();
}

void CDlg__Wafer_Trace_Sel::OnBnClickedBtn__Wafer_Refresh()
{
	UpdateData(TRUE);

	// ...
	{
		CListCtrl* p_table = &mCtrl__Wafer_Info;

		_Add__Wafer_List(p_table);		
	}
}

void CDlg__Wafer_Trace_Sel::OnHdnItemclickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

	*pResult = 0;
}

void CDlg__Wafer_Trace_Sel::OnNMClickList__Wafer_Info(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int r_index = pNMItemActivate->iItem;
	if(r_index >= 0)
	{
		CListCtrl* p_table = &mCtrl__Wafer_Info;

		_Add__Slot_Info(p_table, r_index);
	}

	*pResult = 0;
}

void CDlg__Wafer_Trace_Sel::OnLbnSelchangeList()
{
	mBtn_OK.EnableWindow(TRUE);
}
