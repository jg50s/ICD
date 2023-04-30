// Dlg__PARTICLE_TABLE.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__CTC_MAINT.h"
#include "Dlg__PARTICLE_TABLE.h"

#include "PARTICLE_TABLE__COMMON_RES.h"
extern CPARTICLE_TABLE__COMMON_RES mRes_Common;


// CDlg__PARTICLE_TABLE dialog

IMPLEMENT_DYNAMIC(CDlg__PARTICLE_TABLE, CDialog)

CDlg__PARTICLE_TABLE::CDlg__PARTICLE_TABLE(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__PARTICLE_TABLE::IDD, pParent)
{
	bActive__Init_Page = false;
}

CDlg__PARTICLE_TABLE::~CDlg__PARTICLE_TABLE()
{
}

void CDlg__PARTICLE_TABLE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB__PARTICLE_TABLE, m_mainTab);
}


BOOL CDlg__PARTICLE_TABLE::OnInitDialog()
{
	CDialog::OnInitDialog();

	printf(" * CDlg__PARTICLE_TABLE::OnInitDialog() \n");

	// ...
	CString str_tab;
	int i;

	str_tab = _T("Transfer Part");
	m_mainTab.InsertItem(_MainTAB_ID__TRANSFER_PART, str_tab);

	str_tab = _T("Process Part");
	m_mainTab.InsertItem(_MainTAB_ID__PROCESS_PART, str_tab);

	//
	CRect rect;
	m_mainTab.GetClientRect(&rect);

	// Res.Common ...
	{
		mRes_Common.pGObj_Res = pGObj_Res;

		mRes_Common.Init__CTRL_STATE();
	}
	// Dlg ...
	{
		pDlg_subTab__Transfer_Part = new CDlg__PARTICLE_TABLE__TRANSFER_PART;
		pDlg_subTab__Process_Part  = new CDlg__PARTICLE_TABLE__PROCESS_PART;

		//
		pDlg_subTab__Transfer_Part->iREAL_MODE = iREAL_MODE;
		pDlg_subTab__Transfer_Part->pGObj_Res  = pGObj_Res;

		pDlg_subTab__Transfer_Part->iLLx__SLOT_SIZE = iLLx__SLOT_SIZE;
		pDlg_subTab__Transfer_Part->bLLx__PIN_USE   = bLLx__PIN_USE;

		pDlg_subTab__Transfer_Part->iSTx__MD_SIZE = iSTx__MD_SIZE;

		//
		pDlg_subTab__Process_Part->iREAL_MODE = iREAL_MODE;
		pDlg_subTab__Process_Part->pGObj_Res  = pGObj_Res;

		pDlg_subTab__Process_Part->iPMx__MD_SIZE = iPMx__MD_SIZE;

		//
		pDlg_subTab__Transfer_Part->Create(IDD_PARTICLE_TABLE__TRANSFER_PART, &m_mainTab);
		pDlg_subTab__Process_Part->Create(IDD_PARTICLE_TABLE__PROCESS_PART,   &m_mainTab);

		//
		pDlg_subTab__Transfer_Part->ShowWindow(SW_SHOW);
		pDlg_subTab__Process_Part->ShowWindow(SW_HIDE);
	}

	// ...
	{
		iMainTAB_ID = _MainTAB_ID__TRANSFER_PART;
		m_pwndShow  = pDlg_subTab__Transfer_Part;
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDlg__PARTICLE_TABLE, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB__PARTICLE_TABLE, &CDlg__PARTICLE_TABLE::OnTcnSelchangeTab)
END_MESSAGE_MAP()


// CDlg__PARTICLE_TABLE message handlers

void CDlg__PARTICLE_TABLE::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	iMainTAB_ID = -1;

	if(m_pwndShow != NULL)
	{
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = NULL;
	}

	int tab_index = m_mainTab.GetCurSel();

	switch(tab_index)
	{
		case _MainTAB_ID__TRANSFER_PART:
			pDlg_subTab__Transfer_Part->Update_Table();
			pDlg_subTab__Transfer_Part->ShowWindow(SW_SHOW);
			m_pwndShow = pDlg_subTab__Transfer_Part;
			break;

		case _MainTAB_ID__PROCESS_PART:
			pDlg_subTab__Process_Part->Update_Table();
			pDlg_subTab__Process_Part->ShowWindow(SW_SHOW);
			m_pwndShow = pDlg_subTab__Process_Part;
			break;
	}

	iMainTAB_ID = tab_index;
	*pResult = 0;
}
