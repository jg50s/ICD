#pragma once
#include "afxwin.h"


// CDlg__PMx_Selection dialog

class CDlg__PMx_Selection : public CDialog
{
	DECLARE_DYNAMIC(CDlg__PMx_Selection)

public:
	CDlg__PMx_Selection(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__PMx_Selection();

// Dialog Data
	enum { IDD = IDD_DLG__PMx_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtn_PM1();
	afx_msg void OnBnClickedBtn_PM2();
	afx_msg void OnBnClickedBtn_PM3();
	afx_msg void OnBnClickedBtn_PM4();
	afx_msg void OnBnClickedBtn_PM5();
	afx_msg void OnBnClickedBtn_PM6();
	afx_msg void OnBnClickedCancel();

	// ...
	CButton mCtrl__PM1_Tittle;
	CButton mCtrl__PM2_Tittle;
	CButton mCtrl__PM3_Tittle;
	CButton mCtrl__PM4_Tittle;
	CButton mCtrl__PM5_Tittle;
	CButton mCtrl__PM6_Tittle;

	CButton mCtrl__PM1_Name;
	CButton mCtrl__PM2_Name;
	CButton mCtrl__PM3_Name;
	CButton mCtrl__PM4_Name;
	CButton mCtrl__PM5_Name;
	CButton mCtrl__PM6_Name;

	void Set__PMx_SEL(const int pm_id);

public:
	int iPara__PMx_Size;
	CString sPara__PMx_Name[10];

	int iPara__PMx_SEL;
	CString sPara__PMx_SEL;
};
