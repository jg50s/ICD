// Dlg__GoTo_Step.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_STD.h"
#include "Dlg__GoTo_Step.h"


// CDlg__GoTo_Step dialog

IMPLEMENT_DYNAMIC(CDlg__GoTo_Step, CDialog)

CDlg__GoTo_Step::CDlg__GoTo_Step(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__GoTo_Step::IDD, pParent)
{

}

CDlg__GoTo_Step::~CDlg__GoTo_Step()
{
}

void CDlg__GoTo_Step::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST__STTEP_ID, mCtrl__Step_ID);
	DDX_Control(pDX, IDOK, mCtrl__OK);
}

BEGIN_MESSAGE_MAP(CDlg__GoTo_Step, CDialog)
	ON_BN_CLICKED(IDOK, &CDlg__GoTo_Step::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg__GoTo_Step message handlers

BOOL CDlg__GoTo_Step::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		mCtrl__Step_ID.ResetContent();

		for(int st_id = 1; st_id <= iPara__STEP_MAX; st_id++)
		{
			CString str_data;
			str_data.Format("%1d", st_id);

			mCtrl__Step_ID.AddString(str_data);
		}

		// ...
		int db_index = iPara__SEL_ID - 1;

		if((db_index < iPara__STEP_MAX) 
		&& (db_index >= 0))
		{
			mCtrl__Step_ID.SetCurSel(db_index);
			mCtrl__OK.EnableWindow(TRUE);
		}
		else
		{
			mCtrl__OK.EnableWindow(FALSE);
		}
	}

	return TRUE;
}

void CDlg__GoTo_Step::OnBnClickedOk()
{
	int sel_index = mCtrl__Step_ID.GetCurSel();
	if(sel_index < 0)		return;

	iPara__SEL_ID = sel_index + 1;

	OnOK();
}

