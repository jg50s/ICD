// Dlg__Route_LOOPx.cpp : implementation file
//

#include "stdafx.h"
#include "Interface_Header.h"

#include "JGLEE__RECIPE_CTC.h"
#include "Dlg__Route_LOOPx.h"


// CDlg__Route_LOOPx dialog

IMPLEMENT_DYNAMIC(CDlg__Route_LOOPx, CDialog)

CDlg__Route_LOOPx::CDlg__Route_LOOPx(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Route_LOOPx::IDD, pParent)
	, mData_Repeat(_T(""))
{

}

CDlg__Route_LOOPx::~CDlg__Route_LOOPx()
{
}

void CDlg__Route_LOOPx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT__REPEAT, mData_Repeat);
}


BEGIN_MESSAGE_MAP(CDlg__Route_LOOPx, CDialog)
	ON_BN_CLICKED(IDC_BTN__REPEAT, &CDlg__Route_LOOPx::OnBnClickedBtn_Repeat)
	ON_BN_CLICKED(IDOK, &CDlg__Route_LOOPx::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg__Route_LOOPx message handlers

BOOL CDlg__Route_LOOPx::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	CString str_title;

	str_title.Format("%s Option ...", sPARA_MODULE);
	SetWindowText(str_title);

	// 1. 
	{
		mData_Repeat = sPARA_REPEAT;
	}

	UpdateData(FALSE);
	return TRUE;  
}

void CDlg__Route_LOOPx::OnBnClickedBtn_Repeat()
{
	CGX__UTILITY_CTRL x_pad_ctrl;

	CString str_name   = "Loop Repeat"; 
	CString min_value  = "0";
	CString max_value  = "100"; 
	CString init_data  = mData_Repeat;
	CString str_result = init_data;

	if(x_pad_ctrl->Popup__ANALOG_PAD(str_name, min_value,max_value,init_data, str_result) > 0)
	{
		mData_Repeat = str_result;

		UpdateData(FALSE);
	}
}

void CDlg__Route_LOOPx::OnBnClickedOk()
{
	UpdateData(TRUE);

	// ...
	{
		sPARA_REPEAT = mData_Repeat;
	}

	OnOK();
}
