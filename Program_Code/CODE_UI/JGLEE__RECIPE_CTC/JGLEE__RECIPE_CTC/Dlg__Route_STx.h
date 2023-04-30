#pragma once
#include "afxwin.h"


// CDlg__Route_STx dialog

class CDlg__Route_STx : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Route_STx)

public:
	CDlg__Route_STx(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Route_STx();

// Dialog Data
	enum { IDD = IDD_DLG__ROUTE_STx };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtn__MODE();
	afx_msg void OnBnClickedBtn__SLOT();
	afx_msg void OnBnClickedBtn__SEC();
	afx_msg void OnBnClickedBtn__N2_PURGE();

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

	CString mData_MODE;
	CString mData_SLOT;
	CString mData_SEC;

	CString mData_N2_PURGE;
	CButton mCtrl__N2_PURGE;

public:
	CString sPARA_STx;
	CString sPARA_MODE;
	CString sPARA_SLOT;
	CString sPARA_SEC;

	bool bACTIVE__STx_N2_PURGE;
	CString sPARA_N2_PURGE;
};
