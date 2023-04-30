#pragma once
#include "afxwin.h"


#define _CFG__PMx_SIZE				6
#define _CFG__LLx_SIZE				4


// CDlg__DA_Wafer_Search dialog

class CDlg__DA_Wafer_Search : public CDialog
{
	DECLARE_DYNAMIC(CDlg__DA_Wafer_Search)

public:
	CDlg__DA_Wafer_Search(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__DA_Wafer_Search();

// Dialog Data
	enum { IDD = IDD_DLG__DA_WFR_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtn__MDx_All();
	afx_msg void OnBnClickedBtn__MDx_Clear();
	afx_msg void OnBnClickedBtn__MDx_PMx();
	afx_msg void OnBnClickedBtn__MDx_LLx();

	afx_msg void OnBnClickedBtn__Wfr_Search();
	afx_msg void OnBnClickedBtn__Cancel();

	DECLARE_MESSAGE_MAP()

private:
	CButton mCheck__PM1;
	CButton mCheck__PM2;
	CButton mCheck__PM3;
	CButton mCheck__PM4;
	CButton mCheck__PM5;
	CButton mCheck__PM6;

	CButton mCheck__LL1;
	CButton mCheck__LL2;
	CButton mCheck__LL3;
	CButton mCheck__LL4;

	CButton* pCheck__PMx[_CFG__PMx_SIZE];
	CButton* pCheck__LLx[_CFG__LLx_SIZE];

	//
	CString mStr__Wfr_LotID;
	CString mStr__Wfr_PPID;

	CString mStr__Wfr_PortID;
	CString mStr__Wfr_SlotID;
	//

public:
	int iPara__PortID;
	int iPara__SlotID;

	CString sPara__LotID;
	CString sPara__PPID;

	bool bPara__Check_PMx[_CFG__PMx_SIZE];
	bool bPara__Check_LLx[_CFG__LLx_SIZE];
};
