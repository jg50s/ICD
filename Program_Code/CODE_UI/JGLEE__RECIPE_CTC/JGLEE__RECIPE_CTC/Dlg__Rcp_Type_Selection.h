#pragma once
#include "afxwin.h"


// CDlg__Rcp_Type_Selection dialog

class CDlg__Rcp_Type_Selection : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Rcp_Type_Selection)

public:
	CDlg__Rcp_Type_Selection(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Rcp_Type_Selection();

// Dialog Data
	enum { IDD = IDD_DLG__RCP_TYPE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtn__Pre_Type();
	afx_msg void OnBnClickedBtn__Main_Type();
	afx_msg void OnBnClickedBtn__Post_Type();
	afx_msg void OnBnClickedCancel();

	// ...
	CButton mCtrl__Pre_Name;
	CButton mCtrl__Main_Name;
	CButton mCtrl__Post_Name;

public:
	CString sPara__Pre_Sub_Dir;
	CString sPara__Main_Sub_Dir;
	CString sPara__Post_Sub_Dir;

	CString sPara__Type_SEL;
};
