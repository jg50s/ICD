// Dlg__TRANSFER_PROPERTY.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__CTC_MAINT.h"
#include "Dlg__TRANSFER_PROPERTY.h"


// CDlg__TRANSFER_PROPERTY dialog

IMPLEMENT_DYNAMIC(CDlg__TRANSFER_PROPERTY, CDialog)

CDlg__TRANSFER_PROPERTY::CDlg__TRANSFER_PROPERTY(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__TRANSFER_PROPERTY::IDD, pParent)
{

}

CDlg__TRANSFER_PROPERTY::~CDlg__TRANSFER_PROPERTY()
{
}

void CDlg__TRANSFER_PROPERTY::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT__STN_SRC,  mSTR_STN_SRC);
	DDX_Text(pDX, IDC_EDIT__STN_TRG,  mSTR_STN_TRG);
	DDX_Text(pDX, IDC_EDIT__CYCLE,    mSTR_CYCLE);
	DDX_Text(pDX, IDC_EDIT__ACT_NAME, mSTR_ACT_NAME);
}

BOOL CDlg__TRANSFER_PROPERTY::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		mSTR_STN_SRC = sPARA__STN_SRC;
		mSTR_STN_TRG = sPARA__STN_TRG;
		mSTR_CYCLE   = sPARA__CYCLE;

		mSTR_ACT_NAME = sPARA__ACT_NAME;
	}

	UpdateData(FALSE);
	return TRUE;
}


BEGIN_MESSAGE_MAP(CDlg__TRANSFER_PROPERTY, CDialog)
	ON_BN_CLICKED(IDC_BTN__STN_SRC, &CDlg__TRANSFER_PROPERTY::OnBnClickedBtn_STN_SRC)
	ON_BN_CLICKED(IDC_BTN__STN_TRG, &CDlg__TRANSFER_PROPERTY::OnBnClickedBtn_STN_TRG)
	ON_BN_CLICKED(IDC_BTN__CYCLE,   &CDlg__TRANSFER_PROPERTY::OnBnClickedBtn_CYCLE)
	ON_BN_CLICKED(IDOK, &CDlg__TRANSFER_PROPERTY::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg__TRANSFER_PROPERTY message handlers

void CDlg__TRANSFER_PROPERTY::OnBnClickedBtn_STN_SRC()
{
	UIX__ANALOG_PAD_CTRL x_pad;

	CString str_name = "Select STN.SRC";
	CString str_min  = "1";
	CString str_max  = "25";
	CString str_init = mSTR_STN_SRC;;
	CString str_unit = "ID";
	CString str_data;

	int r_flag = x_pad->Popup(str_name,str_min,str_max,str_init,str_unit, str_data);
	if(r_flag < 0)			return;

	mSTR_STN_SRC = str_data;

	UpdateData(FALSE);
}

void CDlg__TRANSFER_PROPERTY::OnBnClickedBtn_STN_TRG()
{
	UIX__ANALOG_PAD_CTRL x_pad;

	CString str_name = "Select STN.TRG";
	CString str_min  = "1";
	CString str_max  = "25";
	CString str_init = mSTR_STN_TRG;;
	CString str_unit = "ID";
	CString str_data;

	int r_flag = x_pad->Popup(str_name,str_min,str_max,str_init,str_unit, str_data);
	if(r_flag < 0)			return;

	mSTR_STN_TRG = str_data;

	UpdateData(FALSE);
}

void CDlg__TRANSFER_PROPERTY::OnBnClickedBtn_CYCLE()
{
	UIX__ANALOG_PAD_CTRL x_pad;

	CString str_name = "Select Cycle Count";
	CString str_min  = "1";
	CString str_max  = "100";
	CString str_init = mSTR_CYCLE;
	CString str_unit = "count";
	CString str_data;

	int r_flag = x_pad->Popup(str_name,str_min,str_max,str_init,str_unit, str_data);
	if(r_flag < 0)			return;

	mSTR_CYCLE = str_data;

	UpdateData(FALSE);
}

void CDlg__TRANSFER_PROPERTY::OnBnClickedOk()
{
	UpdateData(TRUE);

	// ...
	{
		sPARA__STN_SRC = mSTR_STN_SRC;
		sPARA__STN_TRG = mSTR_STN_TRG;
		sPARA__CYCLE   = mSTR_CYCLE;
	}

	OnOK();
}
