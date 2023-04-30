#pragma once

#include "resource.h"
#include "afxwin.h"


// CDlg__MDx_SEL dialog

class CDlg__MDx_SEL : public CDialog
{
	DECLARE_DYNAMIC(CDlg__MDx_SEL)

public:
	CDlg__MDx_SEL(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__MDx_SEL();

// Dialog Data
	enum { IDD = IDD_DLG__MDx_SEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

	CComboBox mList__MDx_SEL;

public:
	CString sPara__Dlg_Title;

	CString sCur__MDx_SEL;
	CStringArray sList__MDx_SEL;
};
