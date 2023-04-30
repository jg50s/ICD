#pragma once
#include "afxwin.h"


// CDlg__Route_LLx dialog

class CDlg__Route_LLx : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Route_LLx)

public:
	CDlg__Route_LLx(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Route_LLx();

// Dialog Data
	enum { IDD = IDD_DLG__ROUTE_LLx };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtn__MODE();
	afx_msg void OnBnClickedBtn__SLOT01();
	afx_msg void OnBnClickedBtn__SLOT02();
	afx_msg void OnBnClickedBtn__COOLING_SEC();

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

	CString mData_Mode;
	CString mData_Slot02;
	CString mData_Slot01;

	CButton mCtrl__Cooling_Sec;
	CString mData__Cooling_Sec;

	CButton mCtrl__Slot_01;
	CButton mCtrl__Slot_02;

public:
	int iLLx_IN__ACTIVE;
	bool bACTIVE__LLx_SLOT_FIXED;
	bool bACTIVE__LLx_MODE_ALL;
	bool bACTIVE__LLx_OUT_COOLING;

	CString sPARA_LLx;
	CString sPARA_MODE;
	CString sPARA_SLOT;

	CString sPARA__COOLING_SEC;
};
