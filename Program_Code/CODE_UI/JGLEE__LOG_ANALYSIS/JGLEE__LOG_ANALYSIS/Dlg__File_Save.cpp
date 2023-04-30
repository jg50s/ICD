// Dlg__File_Save.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__File_Save.h"


// CDlg__File_Save dialog

IMPLEMENT_DYNAMIC(CDlg__File_Save, CDialog)

CDlg__File_Save::CDlg__File_Save(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__File_Save::IDD, pParent)
{

}

CDlg__File_Save::~CDlg__File_Save()
{
}

void CDlg__File_Save::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK__LEFT_ALIGN,  mCheck__Left_Align);
	DDX_Control(pDX, IDC_CHECK__RIGHT_ALIGN, mCheck__Right_Align);
	DDX_Control(pDX, IDC_LIST__FILE_OUTPUT, mList__File_Output);
}


BEGIN_MESSAGE_MAP(CDlg__File_Save, CDialog)
	ON_BN_CLICKED(IDOK, &CDlg__File_Save::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg__File_Save message handlers

BOOL CDlg__File_Save::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		_Upload__Hard_Drive();

		mCheck__Left_Align.SetCheck(1);
		mCheck__Right_Align.SetCheck(0);
	}

	return TRUE;
}

int  CDlg__File_Save::_Upload__Hard_Drive() 
{
	char root_dir[256];

	for(char ch = 'A'; ch <= 'Z'; ch++)
	{
		sprintf(root_dir, "%1c:\\", ch);
		int flag = GetDriveType(root_dir);

		if((flag != DRIVE_UNKNOWN)
		&& (flag != DRIVE_NO_ROOT_DIR)
		&& (flag != DRIVE_CDROM))
		{
			sprintf(root_dir,"%sPROCESS_DATALOG\\",root_dir);

			mList__File_Output.AddString(root_dir);
		}
	}

	if(mList__File_Output.GetCount() > 0)
	{
		mList__File_Output.SetCurSel(0);
	}

	return 1;
}

void CDlg__File_Save::OnBnClickedOk()
{
	int r_index = mList__File_Output.GetCurSel();
	if(r_index < 0)		return;

	CString dir_output;
	
	mList__File_Output.GetText(r_index, dir_output);
	CreateDirectory(dir_output, NULL);

	sPara__SEL_DIR = dir_output;

	bActive__ALIGN_LEFT  = mCheck__Left_Align.GetCheck();
	bActive__ALIGN_RIGHT = mCheck__Right_Align.GetCheck();

	OnOK();
}
