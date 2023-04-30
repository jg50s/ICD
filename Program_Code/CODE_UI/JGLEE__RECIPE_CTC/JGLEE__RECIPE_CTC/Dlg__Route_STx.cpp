// Dlg__Route_STx.cpp : implementation file
//

#include "stdafx.h"
#include "Interface_Header.h"

#include "JGLEE__RECIPE_CTC.h"
#include "Dlg__Route_STx.h"

#include "Dlg__Route_Mode_Select.h"


// CDlg__Route_STx dialog

IMPLEMENT_DYNAMIC(CDlg__Route_STx, CDialog)

CDlg__Route_STx::CDlg__Route_STx(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Route_STx::IDD, pParent)
	, mData_MODE(_T(""))
	, mData_SLOT(_T(""))
	, mData_SEC(_T(""))
{

}

CDlg__Route_STx::~CDlg__Route_STx()
{
}

void CDlg__Route_STx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT__MODE, mData_MODE);
	DDX_Text(pDX, IDC_EDIT__SLOT, mData_SLOT);
	DDX_Text(pDX, IDC_EDIT__SLOT_01, mData_SEC);

	DDX_Text(pDX, IDC_EDIT__N2_PURGE, mData_N2_PURGE);
	DDX_Control(pDX, IDC_BTN__N2_PURGE, mCtrl__N2_PURGE);
}


BEGIN_MESSAGE_MAP(CDlg__Route_STx, CDialog)
	ON_BN_CLICKED(IDC_BTN__MODE,      &CDlg__Route_STx::OnBnClickedBtn__MODE)
	ON_BN_CLICKED(IDC_BTN__SLOT_MODE, &CDlg__Route_STx::OnBnClickedBtn__SLOT)
	ON_BN_CLICKED(IDC_BTN__SEC,       &CDlg__Route_STx::OnBnClickedBtn__SEC)
	ON_BN_CLICKED(IDC_BTN__N2_PURGE,  &CDlg__Route_STx::OnBnClickedBtn__N2_PURGE)

	ON_BN_CLICKED(IDOK, &CDlg__Route_STx::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg__Route_STx message handlers

BOOL CDlg__Route_STx::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	CString str_title;

	str_title.Format("%s Option ...", sPARA_STx);
	SetWindowText(str_title);

	// ...
	{
		mData_MODE = sPARA_MODE;
		mData_SLOT = sPARA_SLOT;
		mData_SEC  = sPARA_SEC;
	}

	// ...
	{
		if(bACTIVE__STx_N2_PURGE)
		{
			mCtrl__N2_PURGE.EnableWindow(TRUE);
			mData_N2_PURGE = sPARA_N2_PURGE;
		}
		else
		{
			mCtrl__N2_PURGE.EnableWindow(FALSE);
			mData_N2_PURGE = "NO";
		}
	}

	UpdateData(FALSE);
	return TRUE;  
}

void CDlg__Route_STx::OnBnClickedBtn__MODE()
{
	CDlg__Route_Mode_Select dlg;

	dlg.sPARA__INFO = "STx Control Mode";

	dlg.sPARA__SEL_DATA = mData_MODE;

	dlg.sList__ITEM_DATA.Add("TIME");
	dlg.sList__ITEM_DATA.Add("LPx_EMPTY");
	dlg.sList__ITEM_DATA.Add("LPx_TIME");
	dlg.sList__ITEM_DATA.Add("LPx_OPTIMIZATION");

	if(dlg.DoModal() == IDOK)
	{
		mData_MODE = dlg.sPARA__SEL_DATA;

		UpdateData(FALSE);
	}
}
void CDlg__Route_STx::OnBnClickedBtn__SLOT()
{
	CDlg__Route_Mode_Select dlg;

	dlg.sPARA__INFO = "STx Slot Mode";

	dlg.sPARA__SEL_DATA = mData_SLOT;

	dlg.sList__ITEM_DATA.Add("BOTTOM_TO_UP");
	dlg.sList__ITEM_DATA.Add("UP_TO_BOTTOM");

	if(dlg.DoModal() == IDOK)
	{
		mData_SLOT = dlg.sPARA__SEL_DATA;

		UpdateData(FALSE);
	}
}
void CDlg__Route_STx::OnBnClickedBtn__SEC()
{
	CGX__UTILITY_CTRL x_pad_ctrl;

	CString str_name   = "STx Waiting Sec"; 
	CString min_value  = "10";
	CString max_value  = "600"; 
	CString init_data  = mData_SEC;
	CString str_result = init_data;

	if(x_pad_ctrl->Popup__ANALOG_PAD(str_name, min_value,max_value,init_data, str_result) > 0)
	{
		mData_SEC = str_result;

		UpdateData(FALSE);
	}
}
void CDlg__Route_STx::OnBnClickedBtn__N2_PURGE()
{
	CDlg__Route_Mode_Select dlg;

	dlg.sPARA__INFO = "STx N2_Purge";

	dlg.sPARA__SEL_DATA = mData_N2_PURGE;

	dlg.sList__ITEM_DATA.Add("NO");
	dlg.sList__ITEM_DATA.Add("YES");

	if(dlg.DoModal() == IDOK)
	{
		mData_N2_PURGE = dlg.sPARA__SEL_DATA;

		UpdateData(FALSE);
	}
}

void CDlg__Route_STx::OnBnClickedOk()
{
	UpdateData(TRUE);

	// ...
	{
		sPARA_MODE = mData_MODE;
		sPARA_SLOT = mData_SLOT;
		sPARA_SEC  = mData_SEC;
		sPARA_N2_PURGE = mData_N2_PURGE;
	}

	OnOK();
}
