// Dlg__SaveAs.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_STD.h"
#include "Dlg__SaveAs.h"

#include "Interface_Code.h"
#include "CInfo__Rcp_Common.h"


// CDlg__SaveAs dialog

IMPLEMENT_DYNAMIC(CDlg__SaveAs, CDialog)

CDlg__SaveAs::CDlg__SaveAs(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__SaveAs::IDD, pParent)
{

}

CDlg__SaveAs::~CDlg__SaveAs()
{
}

void CDlg__SaveAs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK__RCP_PRE,  mCheck__PRE_RCP);
	DDX_Control(pDX, IDC_CHECK__RCP_MAIN, mCheck__MAIN_RCP);
	DDX_Control(pDX, IDC_CHECK__RCP_POST, mCheck__POST_RCP);

	DDX_Control(pDX, IDC_BTN__RCP_NAME_DATA, mData__Rcp_Name);

	DDX_Control(pDX, IDC_BTN__PMx_CTRL,  mCtrl__Sel_PMx);
	DDX_Control(pDX, IDC_BTN__PMx_DATA,  mData__Sel_PMx);
}


BEGIN_MESSAGE_MAP(CDlg__SaveAs, CDialog)
	ON_BN_CLICKED(IDC_CHECK__RCP_PRE,  &CDlg__SaveAs::OnBnClickedCheck__Rcp_Pre)
	ON_BN_CLICKED(IDC_CHECK__RCP_MAIN, &CDlg__SaveAs::OnBnClickedCheck__Rcp_Main)
	ON_BN_CLICKED(IDC_CHECK__RCP_POST, &CDlg__SaveAs::OnBnClickedCheck__Rcp_Post)

	ON_BN_CLICKED(IDC_BTN__RCP_NAME_CTRL, &CDlg__SaveAs::OnBnClickedBtn__Rcp_Name_Ctrl)
	ON_BN_CLICKED(IDC_BTN__PMx_CTRL,      &CDlg__SaveAs::OnBnClickedBtn__Sel_PMx)
	ON_BN_CLICKED(IDOK, &CDlg__SaveAs::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg__SaveAs message handlers

BOOL CDlg__SaveAs::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		_Change__Check_Rcp_Type();

		mData__Rcp_Name.SetWindowText(sPara__In_Data);
	}

	if(bActive_SEND)
	{
		mCheck__PRE_RCP.EnableWindow(FALSE);
		mCheck__MAIN_RCP.EnableWindow(FALSE);
		mCheck__POST_RCP.EnableWindow(FALSE);

		mCtrl__Sel_PMx.EnableWindow(TRUE);
		mData__Sel_PMx.EnableWindow(TRUE);
	}
	else
	{
		mCtrl__Sel_PMx.EnableWindow(FALSE);
		mData__Sel_PMx.EnableWindow(FALSE);
	}

	// ...
	{
		CString str_data;

		str_data.Format("PM%1d", iMODULE_ID-1);
		mData__Sel_PMx.SetWindowText(str_data);

		//
		iTMP_MODULE_ID = iMODULE_ID;

		sPara__Out_Data = sPara__In_Data;
	}
	return TRUE;
}

void CDlg__SaveAs::OnBnClickedBtn__Rcp_Name_Ctrl()
{
	CGX__UTILITY_CTRL x_utility_ctrl;

	CString str_title;
	CString in_data;
	CString out_data;

	str_title = "Input file name !";
	in_data = sPara__In_Data;

	if(x_utility_ctrl->Popup_Keyboard(str_title,in_data,out_data) < 0)
	{
		return;
	}

	mData__Rcp_Name.SetWindowText(out_data);
	sPara__Out_Data = out_data;
}

void CDlg__SaveAs::_Change__Check_Rcp_Type()
{
	if(bActive__Rcp_Pre)		mCheck__PRE_RCP.EnableWindow(TRUE);
	else						mCheck__PRE_RCP.EnableWindow(FALSE);

	if(bActive__Rcp_Main)		mCheck__MAIN_RCP.EnableWindow(TRUE);
	else						mCheck__MAIN_RCP.EnableWindow(FALSE);

	if(bActive__Rcp_Post)		mCheck__POST_RCP.EnableWindow(TRUE);
	else						mCheck__POST_RCP.EnableWindow(FALSE);

	if(iPara__Dir_Sub == _RCP_FOLDER__PRE)				mCheck__PRE_RCP.SetCheck(1);
	if(iPara__Dir_Sub == _RCP_FOLDER__MAIN)				mCheck__MAIN_RCP.SetCheck(1);
	if(iPara__Dir_Sub == _RCP_FOLDER__POST)				mCheck__POST_RCP.SetCheck(1);
}
void CDlg__SaveAs::OnBnClickedCheck__Rcp_Pre()
{
	mCheck__PRE_RCP.SetCheck(1);
	mCheck__MAIN_RCP.SetCheck(0);
	mCheck__POST_RCP.SetCheck(0);

	iPara__Dir_Sub =  _RCP_FOLDER__PRE;
}
void CDlg__SaveAs::OnBnClickedCheck__Rcp_Main()
{
	mCheck__PRE_RCP.SetCheck(0);
	mCheck__MAIN_RCP.SetCheck(1);
	mCheck__POST_RCP.SetCheck(0);

	iPara__Dir_Sub =  _RCP_FOLDER__MAIN;
}
void CDlg__SaveAs::OnBnClickedCheck__Rcp_Post()
{
	mCheck__PRE_RCP.SetCheck(0);
	mCheck__MAIN_RCP.SetCheck(0);
	mCheck__POST_RCP.SetCheck(1);

	iPara__Dir_Sub =  _RCP_FOLDER__POST;
}

void CDlg__SaveAs::OnBnClickedBtn__Sel_PMx()
{
	CDlg__Sel_PMx dlg;

	dlg.iPara__SEL_PMx = iMODULE_ID - 1;

	int i_limit = _CFG_PMx__SIZE;
	int i;

	for(i=0; i<i_limit; i++)
	{
		dlg.bActive__PMx[i] = bActive__PMx[i];
	}

	if(dlg.DoModal() != IDOK)		return;

	iTMP_MODULE_ID = dlg.iPara__SEL_PMx + 1;

	CString str_data;
	str_data.Format("PM%1d", iTMP_MODULE_ID - 1);

	mData__Sel_PMx.SetWindowText(str_data);
}

void CDlg__SaveAs::OnBnClickedOk()
{
	UpdateData(TRUE);

	// ...
	{
		if(mCheck__PRE_RCP.GetCheck() > 0)			iPara__Dir_Sub = _RCP_FOLDER__PRE;
		if(mCheck__MAIN_RCP.GetCheck() > 0)			iPara__Dir_Sub = _RCP_FOLDER__MAIN;
		if(mCheck__POST_RCP.GetCheck() > 0)			iPara__Dir_Sub = _RCP_FOLDER__POST;
	}

	iMODULE_ID = iTMP_MODULE_ID;

	OnOK();
}
