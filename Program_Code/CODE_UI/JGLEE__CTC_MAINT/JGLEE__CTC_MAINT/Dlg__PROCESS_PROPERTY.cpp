// Dlg__PROCESS_PROPERTY.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__CTC_MAINT.h"
#include "Dlg__PROCESS_PROPERTY.h"

#include "Macro_Function.h"


// CDlg__PROCESS_PROPERTY dialog

IMPLEMENT_DYNAMIC(CDlg__PROCESS_PROPERTY, CDialog)

CDlg__PROCESS_PROPERTY::CDlg__PROCESS_PROPERTY(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__PROCESS_PROPERTY::IDD, pParent)
{

}

CDlg__PROCESS_PROPERTY::~CDlg__PROCESS_PROPERTY()
{
}

void CDlg__PROCESS_PROPERTY::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT__STN_SRC,  mSTR_STN_SRC);
	DDX_Text(pDX, IDC_EDIT__STN_TRG,  mSTR_STN_TRG);
	DDX_Text(pDX, IDC_EDIT__CYCLE,    mSTR_CYCLE);
	DDX_Text(pDX, IDC_EDIT__PROCESS,  mSTR_PROCESS);
	DDX_Text(pDX, IDC_EDIT__ACT_NAME, mSTR_ACT_NAME);
}

BOOL CDlg__PROCESS_PROPERTY::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		sPARA__PROCESS = MACRO__Get_Quotation_String(sPARA__ACT_NAME);

		printf(" * act_name <- [%s] \n", sPARA__ACT_NAME);
		printf(" ** %s \n", sPARA__PROCESS);

		mSTR_STN_SRC = sPARA__STN_SRC;
		mSTR_STN_TRG = sPARA__STN_TRG;
		mSTR_CYCLE   = sPARA__CYCLE;
		mSTR_PROCESS = sPARA__PROCESS;

		mSTR_ACT_NAME = sPARA__ACT_NAME;
	}

	UpdateData(FALSE);
	return TRUE;
}


BEGIN_MESSAGE_MAP(CDlg__PROCESS_PROPERTY, CDialog)
	ON_BN_CLICKED(IDC_BTN__STN_SRC, &CDlg__PROCESS_PROPERTY::OnBnClickedBtn_STN_SRC)
	ON_BN_CLICKED(IDC_BTN__STN_TRG, &CDlg__PROCESS_PROPERTY::OnBnClickedBtn_STN_TRG)
	ON_BN_CLICKED(IDC_BTN__CYCLE,   &CDlg__PROCESS_PROPERTY::OnBnClickedBtn_CYCLE)
	ON_BN_CLICKED(IDC_BTN__PROCESS, &CDlg__PROCESS_PROPERTY::OnBnClickedBtn_PROCESS)
	ON_BN_CLICKED(IDOK, &CDlg__PROCESS_PROPERTY::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg__PROCESS_PROPERTY message handlers

void CDlg__PROCESS_PROPERTY::OnBnClickedBtn_STN_SRC()
{
	UIX__ANALOG_PAD_CTRL x_pad;

	CString str_name = "Select STN.SRC";
	CString str_min  = "1";
	CString str_max  = "25";
	CString str_init = mSTR_STN_SRC;
	CString str_unit = "ID";
	CString str_data;

	int r_flag = x_pad->Popup(str_name,str_min,str_max,str_init,str_unit, str_data);
	if(r_flag < 0)			return;

	mSTR_STN_SRC = str_data;

	UpdateData(FALSE);
}

void CDlg__PROCESS_PROPERTY::OnBnClickedBtn_STN_TRG()
{
	UIX__ANALOG_PAD_CTRL x_pad;

	CString str_name = "Select STN.TRG";
	CString str_min  = "1";
	CString str_max  = "25";
	CString str_init = mSTR_STN_TRG;
	CString str_unit = "ID";
	CString str_data;

	int r_flag = x_pad->Popup(str_name,str_min,str_max,str_init,str_unit, str_data);
	if(r_flag < 0)			return;

	mSTR_STN_TRG = str_data;

	UpdateData(FALSE);
}

void CDlg__PROCESS_PROPERTY::OnBnClickedBtn_CYCLE()
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

void CDlg__PROCESS_PROPERTY::OnBnClickedBtn_PROCESS()
{
	int para__pm_id = iPARA__PMx_ID;
	// CString para__dir_sub  = "MAIN";
	CString para__dir_sub  = "PRC";
	CString para__rcp_name = "";

	// ...
	CGX__SYSTEM_CTRL  x_sys_ctrl;
	CString dir_root;
	int eqp_id = -1;

	eqp_id = para__pm_id + 1;
	x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_root);

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
		CString para__sel_name;

		if(sel_file.GetLength() > 0)		para__sel_name.Format("%s\\%s", para__dir_sub,sel_file);
		else								para__sel_name = "";

		mSTR_PROCESS = para__sel_name;

		printf(" * para__sel_name <- [%s] \n", para__sel_name);
	}

	UpdateData(FALSE);
	return;
}

void CDlg__PROCESS_PROPERTY::OnBnClickedOk()
{
	UpdateData(TRUE);

	// ...
	{
		sPARA__STN_SRC = mSTR_STN_SRC;
		sPARA__STN_TRG = mSTR_STN_TRG;
		sPARA__CYCLE   = mSTR_CYCLE;

		sPARA__PROCESS = mSTR_PROCESS;
	}

	OnOK();
}
