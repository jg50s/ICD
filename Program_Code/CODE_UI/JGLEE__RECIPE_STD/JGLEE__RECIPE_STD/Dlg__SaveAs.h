#pragma once

#include "afxwin.h"
#include "Dlg__Sel_PMx.h"


// CDlg__SaveAs dialog

class CDlg__SaveAs : public CDialog
{
	DECLARE_DYNAMIC(CDlg__SaveAs)

public:
	CDlg__SaveAs(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__SaveAs();

// Dialog Data
	enum { IDD = IDD_DLG__SAVEAS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedCheck__Rcp_Pre();
	afx_msg void OnBnClickedCheck__Rcp_Main();
	afx_msg void OnBnClickedCheck__Rcp_Post();

	afx_msg void OnBnClickedBtn__Rcp_Name_Ctrl();
	afx_msg void OnBnClickedBtn__Sel_PMx();

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

	CButton mCheck__PRE_RCP;
	CButton mCheck__MAIN_RCP;
	CButton mCheck__POST_RCP;

	CButton mData__Rcp_Name;

	CButton mCtrl__Sel_PMx;
	CButton mData__Sel_PMx;

	void _Change__Check_Rcp_Type();

	int  iTMP_MODULE_ID;

public:
	int  iMODULE_ID;
	bool bActive_SEND;

	bool bActive__PMx[_CFG_PMx__SIZE];

	bool bActive__Rcp_Pre;
	bool bActive__Rcp_Main;
	bool bActive__Rcp_Post;

	int iPara__Dir_Sub;
	CString sPara__In_Data;
	CString sPara__Out_Data;
};
