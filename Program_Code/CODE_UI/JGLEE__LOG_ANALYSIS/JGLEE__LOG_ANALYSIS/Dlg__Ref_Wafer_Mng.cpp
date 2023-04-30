// Dlg__Ref_Wafer_Mng.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__Ref_Wafer_Mng.h"


// CDlg__Ref_Wafer_Mng dialog

IMPLEMENT_DYNAMIC(CDlg__Ref_Wafer_Mng, CDialog)

CDlg__Ref_Wafer_Mng::CDlg__Ref_Wafer_Mng(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Ref_Wafer_Mng::IDD, pParent)
{

}

CDlg__Ref_Wafer_Mng::~CDlg__Ref_Wafer_Mng()
{
}

void CDlg__Ref_Wafer_Mng::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN__DIR_INFO_DATA, mBtn__DIR_INFO_DATA);
	DDX_Control(pDX, IDC_BTN__JOBID_DATA,    mBtn__JOBID_DATA);
	DDX_Control(pDX, IDC_BTN__JOBID_DATA2,   mBtn__CSTID_DATA);
	DDX_Control(pDX, IDC_BTN__LOTID_DATA,    mBtn__LOTID_DATA);
	DDX_Control(pDX, IDC_BTN__START_DATA,    mBtn__START_TIME_DATA);
	DDX_Control(pDX, IDC_BTN__PORTID_DATA,   mBtn__PORTID_DATA);
	DDX_Control(pDX, IDC_BTN__SLOTID_DATA,   mBtn__SLOTID_DATA);
}


BEGIN_MESSAGE_MAP(CDlg__Ref_Wafer_Mng, CDialog)
END_MESSAGE_MAP()


// CDlg__Ref_Wafer_Mng message handlers

BOOL CDlg__Ref_Wafer_Mng::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		mBtn__DIR_INFO_DATA.SetWindowText(sPara__DIR_INFO_DATA);
		mBtn__JOBID_DATA.SetWindowText(sPara__JOBID_DATA);
		mBtn__CSTID_DATA.SetWindowText(sPara__CSTID_DATA);
		mBtn__LOTID_DATA.SetWindowText(sPara__LOTID_DATA);
		mBtn__START_TIME_DATA.SetWindowText(sPara__START_TIME_DATA);
		mBtn__PORTID_DATA.SetWindowText(sPara__PORTID_DATA);
		mBtn__SLOTID_DATA.SetWindowText(sPara__SLOTID_DATA);
	}

	return TRUE;  
}
