// Dlg__Rcp_Type_Selection.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_CTC.h"
#include "Dlg__Rcp_Type_Selection.h"


// CDlg__Rcp_Type_Selection dialog

IMPLEMENT_DYNAMIC(CDlg__Rcp_Type_Selection, CDialog)

CDlg__Rcp_Type_Selection::CDlg__Rcp_Type_Selection(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Rcp_Type_Selection::IDD, pParent)
{

}

CDlg__Rcp_Type_Selection::~CDlg__Rcp_Type_Selection()
{
}

void CDlg__Rcp_Type_Selection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN__PRE_NAME, mCtrl__Pre_Name);
	DDX_Control(pDX, IDC_BTN__MAIN_NAME, mCtrl__Main_Name);
	DDX_Control(pDX, IDC_BTN__POST_NAME, mCtrl__Post_Name);
}


BEGIN_MESSAGE_MAP(CDlg__Rcp_Type_Selection, CDialog)
	ON_BN_CLICKED(IDC_BTN__PRE_TITLE,  &CDlg__Rcp_Type_Selection::OnBnClickedBtn__Pre_Type)
	ON_BN_CLICKED(IDC_BTN__MAIN_TITLE, &CDlg__Rcp_Type_Selection::OnBnClickedBtn__Main_Type)
	ON_BN_CLICKED(IDC_BTN__POST_TITLE, &CDlg__Rcp_Type_Selection::OnBnClickedBtn__Post_Type)
	ON_BN_CLICKED(IDCANCEL, &CDlg__Rcp_Type_Selection::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlg__Rcp_Type_Selection message handlers

BOOL CDlg__Rcp_Type_Selection::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		mCtrl__Pre_Name.SetWindowText(sPara__Pre_Sub_Dir);
		mCtrl__Main_Name.SetWindowText(sPara__Main_Sub_Dir);
		mCtrl__Post_Name.SetWindowText(sPara__Post_Sub_Dir);
	}

	return TRUE; 
}

void CDlg__Rcp_Type_Selection::OnBnClickedBtn__Pre_Type()
{
	sPara__Type_SEL = sPara__Pre_Sub_Dir;
	OnOK();
}
void CDlg__Rcp_Type_Selection::OnBnClickedBtn__Main_Type()
{
	sPara__Type_SEL = sPara__Main_Sub_Dir;
	OnOK();
}
void CDlg__Rcp_Type_Selection::OnBnClickedBtn__Post_Type()
{
	sPara__Type_SEL = sPara__Post_Sub_Dir;
	OnOK();
}

void CDlg__Rcp_Type_Selection::OnBnClickedCancel()
{
	OnCancel();
}
