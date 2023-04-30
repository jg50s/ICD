// Dlg__MDx_SEL.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__MDx_SEL.h"


// CDlg__MDx_SEL dialog

IMPLEMENT_DYNAMIC(CDlg__MDx_SEL, CDialog)

CDlg__MDx_SEL::CDlg__MDx_SEL(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__MDx_SEL::IDD, pParent)
{

}

CDlg__MDx_SEL::~CDlg__MDx_SEL()
{
}

void CDlg__MDx_SEL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO__MDx_LIST, mList__MDx_SEL);
}


BEGIN_MESSAGE_MAP(CDlg__MDx_SEL, CDialog)
	ON_BN_CLICKED(IDOK, &CDlg__MDx_SEL::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg__MDx_SEL message handlers

BOOL CDlg__MDx_SEL::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		int sel_index = -1;

		int i_limit = sList__MDx_SEL.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CString str_md = sList__MDx_SEL[i];
			mList__MDx_SEL.AddString(str_md);

			if(str_md.CompareNoCase(sCur__MDx_SEL) == 0)
				sel_index = i;
		}

		if(sel_index >= 0)
		{
			mList__MDx_SEL.SetCurSel(sel_index);
		}
	}

	if(sPara__Dlg_Title.GetLength() > 0)
	{
		SetWindowText(sPara__Dlg_Title);
	}

	return TRUE; 
}

void CDlg__MDx_SEL::OnBnClickedOk()
{
	UpdateData(FALSE);

	int r_index = mList__MDx_SEL.GetCurSel();
	mList__MDx_SEL.GetLBText(r_index, sCur__MDx_SEL);

	OnOK();
}
