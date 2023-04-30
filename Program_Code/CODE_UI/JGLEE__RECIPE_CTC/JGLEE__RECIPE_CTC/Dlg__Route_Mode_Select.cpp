// Dlg__Route_Mode_Select.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_CTC.h"
#include "Dlg__Route_Mode_Select.h"


// CDlg__Route_Mode_Select dialog

IMPLEMENT_DYNAMIC(CDlg__Route_Mode_Select, CDialog)

CDlg__Route_Mode_Select::CDlg__Route_Mode_Select(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Route_Mode_Select::IDD, pParent)
	, mData_Info(_T(""))
{

}

CDlg__Route_Mode_Select::~CDlg__Route_Mode_Select()
{
}

void CDlg__Route_Mode_Select::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST__ITEM, mCtrl__Item_List);
	DDX_Text(pDX, IDC_EDIT__INFO, mData_Info);
	DDX_Control(pDX, IDC_BTN__SEL_ITEM, mCtrl__Sel_Item);
}


BEGIN_MESSAGE_MAP(CDlg__Route_Mode_Select, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST__ITEM, &CDlg__Route_Mode_Select::OnLbnSelchangeList)
	ON_BN_CLICKED(IDOK, &CDlg__Route_Mode_Select::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg__Route_Mode_Select message handlers

BOOL CDlg__Route_Mode_Select::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		mData_Info.Format("%s", sPARA__INFO);
	}

	// ...
	{
		mCtrl__Item_List.ResetContent();

		int i_limit = sList__ITEM_DATA.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			mCtrl__Item_List.AddString(sList__ITEM_DATA[i]);
		}

		if(i_limit > 0)
		{
			if(mCtrl__Item_List.FindString(0, sPARA__SEL_DATA) < 0)
			{
				sPARA__SEL_DATA = sList__ITEM_DATA[0];
			}

			mCtrl__Item_List.SelectString(0, sPARA__SEL_DATA);
		}

		mCtrl__Sel_Item.SetWindowText(sPARA__SEL_DATA);
	}

	UpdateData(FALSE);
	return TRUE; 
}

void CDlg__Route_Mode_Select::OnLbnSelchangeList()
{
	UpdateData(TRUE);

	int i_index = mCtrl__Item_List.GetCurSel();
	if(i_index >= 0)
	{
		CString str_data;
		mCtrl__Item_List.GetText(i_index, str_data);

		mCtrl__Sel_Item.SetWindowText(str_data);
	}

	UpdateData(FALSE);
}

void CDlg__Route_Mode_Select::OnBnClickedOk()
{
	UpdateData(TRUE);

	CString str_data;
	mCtrl__Sel_Item.GetWindowText(str_data);
	sPARA__SEL_DATA = str_data;

	OnOK();
}
