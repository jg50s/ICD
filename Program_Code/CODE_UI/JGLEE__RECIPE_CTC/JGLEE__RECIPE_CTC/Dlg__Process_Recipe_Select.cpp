// Dlg__Process_Recipe_Select.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_CTC.h"
#include "Dlg__Process_Recipe_Select.h"

#include "Interface_Header.h"
#include "Dlg__Route_Mode_Select.h"

#include "Macro_Function.h"


// CDlg__Process_Recipe_Select dialog

IMPLEMENT_DYNAMIC(CDlg__Process_Recipe_Select, CDialog)

CDlg__Process_Recipe_Select::CDlg__Process_Recipe_Select(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Process_Recipe_Select::IDD, pParent)
{
	bActive__LLx = false;

	bActive__PRE_ISE  = true;
	bActive__POST_ISE = true;
}

CDlg__Process_Recipe_Select::~CDlg__Process_Recipe_Select()
{
}

void CDlg__Process_Recipe_Select::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN__PMC_INFO, mData__PMx_Info);
	
	DDX_Control(pDX, IDC_BTN__PRE_RCP_CTRL, mCtrl__PRE_RCP);
	DDX_Control(pDX, IDC_BTN__PRE_RCP_NAME, mData__PRE_RCP);
	
	DDX_Control(pDX, IDC_BTN__MAIN_RCP_CTRL, mCtrl__MAIN_RCP);
	DDX_Control(pDX, IDC_BTN__MAIN_RCP_NAME, mData__MAIN_RCP);
	
	DDX_Control(pDX, IDC_BTN__POST_RCP_CTRL, mCtrl__POST_RCP);
	DDX_Control(pDX, IDC_BTN__POST_RCP_NAME, mData__POST_RCP);
}


BEGIN_MESSAGE_MAP(CDlg__Process_Recipe_Select, CDialog)
	ON_BN_CLICKED(IDC_BTN__PRE_RCP_CTRL,  &CDlg__Process_Recipe_Select::OnBnClickedBtn__PRE_RCP_CTRL)
	ON_BN_CLICKED(IDC_BTN__MAIN_RCP_CTRL, &CDlg__Process_Recipe_Select::OnBnClickedBtn__MAIN_RCP_CTRL)
	ON_BN_CLICKED(IDC_BTN__POST_RCP_CTRL, &CDlg__Process_Recipe_Select::OnBnClickedBtn__POST_RCP_CTRL)

	ON_BN_CLICKED(IDOK, &CDlg__Process_Recipe_Select::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg__Process_Recipe_Select message handlers

BOOL CDlg__Process_Recipe_Select::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		mData__PMx_Info.SetWindowText(sPara__PMx_Info);

		mData__PRE_RCP.SetWindowText(sPara__PRE_RCP);
		mData__MAIN_RCP.SetWindowText(sPara__MAIN_RCP);
		mData__POST_RCP.SetWindowText(sPara__POST_RCP);
	}

	// ...
	{
		mCtrl__PRE_RCP.EnableWindow(bActive__PRE_ISE);
		mData__PRE_RCP.EnableWindow(bActive__PRE_ISE);

		mCtrl__POST_RCP.EnableWindow(bActive__POST_ISE);
		mData__POST_RCP.EnableWindow(bActive__POST_ISE);
	}
	return TRUE;  
}

void CDlg__Process_Recipe_Select::OnBnClickedBtn__PRE_RCP_CTRL()
{
	CString para__dir_sub  = sPara__PRE_SUB_DIR;
	CString para__rcp_name = sPara__PRE_RCP;
	CString para__sel_name;

	if(_Fnc__Select_Recipe(para__dir_sub,para__rcp_name, para__sel_name) > 0)
	{
		sPara__PRE_RCP = para__sel_name;
		mData__PRE_RCP.SetWindowText(para__sel_name);
	}
}
void CDlg__Process_Recipe_Select::OnBnClickedBtn__MAIN_RCP_CTRL()
{
	CString para__dir_sub  = sPara__MAIN_SUB_DIR;
	CString para__rcp_name = sPara__MAIN_RCP;
	CString para__sel_name;

	if(_Fnc__Select_Recipe(para__dir_sub,para__rcp_name, para__sel_name) > 0)
	{
		sPara__MAIN_RCP = para__sel_name;
		mData__MAIN_RCP.SetWindowText(para__sel_name);
	}
}
void CDlg__Process_Recipe_Select::OnBnClickedBtn__POST_RCP_CTRL()
{
	CString para__dir_sub  = sPara__POST_SUB_DIR;
	CString para__rcp_name = sPara__POST_RCP;
	CString para__sel_name;

	if(_Fnc__Select_Recipe(para__dir_sub,para__rcp_name, para__sel_name) > 0)
	{
		sPara__POST_RCP = para__sel_name;
		mData__POST_RCP.SetWindowText(para__sel_name);
	}
}
int CDlg__Process_Recipe_Select::
_Fnc__Select_Recipe(const CString& para__dir_sub, 
					const CString& para__rcp_name,
					CString& para__sel_name)
{
	CGX__SYSTEM_CTRL  x_sys_ctrl;
	CString dir_root;
	int eqp_id = -1;

	if(bActive__LLx)
	{
		eqp_id = iPara__PMx_ID;
		x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_root);
	}
	else
	{
		eqp_id = iPara__PMx_ID + 1;
		x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_root);
	}

	// ...
	CString dir_rcp;
	dir_rcp.Format("%s\\%s", dir_root,para__dir_sub);

	printf(" * EqpID(%1d) <- [%s] \n", eqp_id,dir_rcp);

	CString file_ext  = "rcp";
	CString file_name = MACRO__Get_ITEM_DATA(para__rcp_name, '\\');

	CStringArray l_file;
	CStringArray l_date;
	MACRO__Get_File_List(dir_rcp,file_ext, l_file,l_date);

	//
	CGX__UTILITY_CTRL x_pad_ctrl;
	CString sel_file;

	if(x_pad_ctrl->Popup__FILE_SELECT(file_name,l_file,l_date, sel_file) > 0)
	{
		if(sel_file.GetLength() > 0)		para__sel_name.Format("%s\\%s", para__dir_sub,sel_file);
		else								para__sel_name = "";
		
		return 1;
	}
	return -1;
}

void CDlg__Process_Recipe_Select::OnBnClickedOk()
{
	OnOK();
}
