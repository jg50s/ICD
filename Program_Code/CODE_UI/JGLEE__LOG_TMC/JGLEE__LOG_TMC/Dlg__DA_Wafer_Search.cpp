// Dlg__DA_Wafer_Search.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_TMC.h"
#include "Dlg__DA_Wafer_Search.h"


// CDlg__DA_Wafer_Search dialog

IMPLEMENT_DYNAMIC(CDlg__DA_Wafer_Search, CDialog)

CDlg__DA_Wafer_Search::CDlg__DA_Wafer_Search(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__DA_Wafer_Search::IDD, pParent)
{
	mStr__Wfr_LotID = _T("");
	mStr__Wfr_PPID  = _T("");

	mStr__Wfr_PortID = _T("");
	mStr__Wfr_SlotID = _T("");
}

CDlg__DA_Wafer_Search::~CDlg__DA_Wafer_Search()
{
}

void CDlg__DA_Wafer_Search::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK__PM1, mCheck__PM1);
	DDX_Control(pDX, IDC_CHECK__PM2, mCheck__PM2);
	DDX_Control(pDX, IDC_CHECK__PM3, mCheck__PM3);
	DDX_Control(pDX, IDC_CHECK__PM4, mCheck__PM4);
	DDX_Control(pDX, IDC_CHECK__PM5, mCheck__PM5);
	DDX_Control(pDX, IDC_CHECK__PM6, mCheck__PM6);

	DDX_Control(pDX, IDC_CHECK__LL1, mCheck__LL1);
	DDX_Control(pDX, IDC_CHECK__LL2, mCheck__LL2);
	DDX_Control(pDX, IDC_CHECK__LL3, mCheck__LL3);
	DDX_Control(pDX, IDC_CHECK__LL4, mCheck__LL4);

	DDX_Text(pDX, IDC_EDIT__WFR_LOTID, mStr__Wfr_LotID);
	DDX_Text(pDX, IDC_EDIT__WFR_PPID,  mStr__Wfr_PPID);

	DDX_Text(pDX, IDC_EDIT__WFR_PORTID, mStr__Wfr_PortID);
	DDX_Text(pDX, IDC_EDIT__WFR_SLOTID, mStr__Wfr_SlotID);
}


BEGIN_MESSAGE_MAP(CDlg__DA_Wafer_Search, CDialog)
	ON_BN_CLICKED(IDC_BTN__MDx_ALL,   &CDlg__DA_Wafer_Search::OnBnClickedBtn__MDx_All)
	ON_BN_CLICKED(IDC_BTN__MDx_CLEAR, &CDlg__DA_Wafer_Search::OnBnClickedBtn__MDx_Clear)
	ON_BN_CLICKED(IDC_BTN__MDx_PMx,   &CDlg__DA_Wafer_Search::OnBnClickedBtn__MDx_PMx)
	ON_BN_CLICKED(IDC_BTN__MDx_LLx,   &CDlg__DA_Wafer_Search::OnBnClickedBtn__MDx_LLx)

	ON_BN_CLICKED(IDC_BTN__WFR_SEARCH, &CDlg__DA_Wafer_Search::OnBnClickedBtn__Wfr_Search)
	ON_BN_CLICKED(IDC_BTN__CANCEL, &CDlg__DA_Wafer_Search::OnBnClickedBtn__Cancel)
END_MESSAGE_MAP()


// CDlg__DA_Wafer_Search message handlers

BOOL CDlg__DA_Wafer_Search::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	int i;

	// ...
	{
		CButton* p_ctrl;

		for(i=0; i<_CFG__PMx_SIZE; i++)
		{
				 if(i == 0)			p_ctrl = &mCheck__PM1;
			else if(i == 1)			p_ctrl = &mCheck__PM2;
			else if(i == 2)			p_ctrl = &mCheck__PM3;
			else if(i == 3)			p_ctrl = &mCheck__PM4;
			else if(i == 4)			p_ctrl = &mCheck__PM5;
			else if(i == 5)			p_ctrl = &mCheck__PM6;
			else					continue;

			pCheck__PMx[i] = p_ctrl;
		}

		for(i=0; i<_CFG__LLx_SIZE; i++)
		{
				 if(i == 0)			p_ctrl = &mCheck__LL1;
			else if(i == 1)			p_ctrl = &mCheck__LL2;
			else if(i == 2)			p_ctrl = &mCheck__LL3;
			else if(i == 3)			p_ctrl = &mCheck__LL4;
			else					continue;

			pCheck__LLx[i] = p_ctrl;
		}
	}

	// ...
	{
		mStr__Wfr_PortID.Format("%1d", iPara__PortID);
		mStr__Wfr_SlotID.Format("%1d", iPara__SlotID);

		mStr__Wfr_LotID = sPara__LotID;
		mStr__Wfr_PPID  = sPara__PPID;

		for(i=0; i<_CFG__PMx_SIZE; i++)
		{
			if(bPara__Check_PMx[i])			pCheck__PMx[i]->SetCheck(1);
			else							pCheck__PMx[i]->SetCheck(0);
		}
		for(i=0; i<_CFG__LLx_SIZE; i++)
		{
			if(bPara__Check_LLx[i])			pCheck__LLx[i]->SetCheck(1);
			else							pCheck__LLx[i]->SetCheck(0);
		}
	}

	UpdateData(FALSE);
	return TRUE; 
}

void CDlg__DA_Wafer_Search::OnBnClickedBtn__MDx_All()
{
	int i;

	// ...
	{
		for(i=0; i<_CFG__PMx_SIZE; i++)
			pCheck__PMx[i]->SetCheck(1);

		for(i=0; i<_CFG__LLx_SIZE; i++)
			pCheck__LLx[i]->SetCheck(1);
	}

	UpdateData(FALSE);
}
void CDlg__DA_Wafer_Search::OnBnClickedBtn__MDx_Clear()
{
	int i;

	// ...
	{
		for(i=0; i<_CFG__PMx_SIZE; i++)
			pCheck__PMx[i]->SetCheck(0);

		for(i=0; i<_CFG__LLx_SIZE; i++)
			pCheck__LLx[i]->SetCheck(0);
	}

	UpdateData(FALSE);
}
void CDlg__DA_Wafer_Search::OnBnClickedBtn__MDx_PMx()
{
	int i;

	// ...
	{
		for(i=0; i<_CFG__PMx_SIZE; i++)
			pCheck__PMx[i]->SetCheck(1);
	}

	UpdateData(FALSE);
}
void CDlg__DA_Wafer_Search::OnBnClickedBtn__MDx_LLx()
{
	int i;

	// ...
	{
		for(i=0; i<_CFG__LLx_SIZE; i++)
			pCheck__LLx[i]->SetCheck(1);
	}

	UpdateData(FALSE);
}

void CDlg__DA_Wafer_Search::OnBnClickedBtn__Wfr_Search()
{
	UpdateData(TRUE);

	// ...
	{
		int i;

		iPara__PortID = atoi(mStr__Wfr_PortID);
		iPara__SlotID = atoi(mStr__Wfr_SlotID);

		sPara__LotID = mStr__Wfr_LotID;
		sPara__PPID  = mStr__Wfr_PPID;

		for(i=0; i<_CFG__PMx_SIZE; i++)
		{
			if(pCheck__PMx[i]->GetCheck() > 0)		bPara__Check_PMx[i] = true;
			else									bPara__Check_PMx[i] = false;
		}
		for(i=0; i<_CFG__LLx_SIZE; i++)
		{
			if(pCheck__LLx[i]->GetCheck() > 0)		bPara__Check_LLx[i] = true;
			else									bPara__Check_LLx[i] = false;
		}
	}

	OnOK();
}
void CDlg__DA_Wafer_Search::OnBnClickedBtn__Cancel()
{

	OnCancel();
}
