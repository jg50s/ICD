#pragma once
#include "afxwin.h"


// CDlg__GoTo_Step dialog

class CDlg__GoTo_Step : public CDialog
{
	DECLARE_DYNAMIC(CDlg__GoTo_Step)

public:
	CDlg__GoTo_Step(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__GoTo_Step();

// Dialog Data
	enum { IDD = IDD_DLG__GOTO_STEP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:
	CListBox mCtrl__Step_ID;
	CButton mCtrl__OK;

public:
	int iPara__STEP_MAX;
	int iPara__SEL_ID;
};
