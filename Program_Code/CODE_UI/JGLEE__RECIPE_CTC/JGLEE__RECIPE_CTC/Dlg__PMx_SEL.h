#pragma once
#include "afxwin.h"


// CDlg__PMx_SEL dialog

class CDlg__PMx_SEL : public CDialog
{
	DECLARE_DYNAMIC(CDlg__PMx_SEL)

public:
	CDlg__PMx_SEL(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__PMx_SEL();

// Dialog Data
	enum { IDD = IDD_DLG__PMx_SEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtn__MDx_01();
	afx_msg void OnBnClickedBtn__MDx_02();
	afx_msg void OnBnClickedBtn__MDx_03();
	afx_msg void OnBnClickedBtn__MDx_04();
	afx_msg void OnBnClickedBtn__MDx_05();
	afx_msg void OnBnClickedBtn__MDx_06();
	afx_msg void OnBnClickedCancel();

	DECLARE_MESSAGE_MAP()

	// ...
	CButton mBtn__MDx_01;
	CButton mBtn__MDx_02;
	CButton mBtn__MDx_03;
	CButton mBtn__MDx_04;
	CButton mBtn__MDx_05;
	CButton mBtn__MDx_06;

	void _Click__MDx(CButton* p_btn);
	//

public:
	CString sPara__Win_Title;

	bool bActive__PMx_SEL;
	int iPara__PMx_SEL;
	CString sPara__PMx_TITLE;

	CStringArray sList__PMx_ID;
	CStringArray sList__PMx_TITLE;

	bool bActive__CFG_TYPE;
	CString sPara__CFG_TYPE_SEL;
	CStringArray sList__CFG_TYPE;
};
