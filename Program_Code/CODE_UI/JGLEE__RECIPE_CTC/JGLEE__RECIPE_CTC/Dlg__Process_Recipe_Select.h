#pragma once
#include "afxwin.h"


// CDlg__Process_Recipe_Select dialog

class CDlg__Process_Recipe_Select : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Process_Recipe_Select)

public:
	CDlg__Process_Recipe_Select(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Process_Recipe_Select();

// Dialog Data
	enum { IDD = IDD_DLG__PRC_RCP_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtn__PRE_RCP_CTRL();
	afx_msg void OnBnClickedBtn__MAIN_RCP_CTRL();
	afx_msg void OnBnClickedBtn__POST_RCP_CTRL();

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

	// ...
	CButton mData__PMx_Info;
	
	CButton mCtrl__PRE_RCP;
	CButton mData__PRE_RCP;
	
	CButton mCtrl__MAIN_RCP;
	CButton mData__MAIN_RCP;
	
	CButton mCtrl__POST_RCP;
	CButton mData__POST_RCP;

	// ...
	int _Fnc__Select_Recipe(const CString& para__dir_sub, 
							const CString& para__rcp_name,
							CString& para__sel_name);
	//

public:
	int iREAL_MODE;

	bool bActive__LLx;
	bool bActive__PRE_ISE;
	bool bActive__POST_ISE;

	CString sPara__PMx_Info;
	int iPara__PMx_ID;

	CString sPara__PRE_RCP;
	CString sPara__PRE_SUB_DIR;

	CString sPara__MAIN_RCP;
	CString sPara__MAIN_SUB_DIR;

	CString sPara__POST_RCP;
	CString sPara__POST_SUB_DIR;
};
